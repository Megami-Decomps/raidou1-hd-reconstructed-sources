#include "types.h"
#include "achievement.h"
#include "cfg.h"
#include "dat.h"
#include "dds3.h"
#include "dds3_pad.h"
#include "dds3basic.h"
#include "dds3cameraobjectbasic.h"
#include "dds3effect.h"
#include "dds3effectblur.h"
#include "dds3effectobjectbasic.h"
#include "dds3kernelcore.h"
#include "dds3kerneldraw.h"
#include "dds3objectbase.h"
#include "dds3padmanager.h"
#include "dds3pathbasic.h"
#include "dds3scenebasic.h"
#include "dds3worldbasic.h"
#include "ditectivebook.h"
#include "eve.h"
#include "event.h"
#include "evt.h"
#include "evtcutin.h"
#include "evtpmv.h"
#include "evtsky.h"
#include "evtsound.h"
#include "evttmxpreload.h"
#include "evtviewer.h"
#include "gohdirection.h"
#include "itf.h"
#include "kernel.h"
#include "mdl.h"
#include "mdleffect.h"
#include "movie.h"
#include "mviscrcmd.h"
#include "sbtlcontinue.h"
#include "scr.h"
#include "scrcommand.h"
#include "sdf_vu0.h"
#include "sdfmem.h"
#include "sdfmodel.h"
#include "sdfmotion.h"
#include "sdfsound.h"
#include "sdftex.h"
#include "sndat3.h"
#include "sndmanager.h"

#define EVENT_SKIP_DURATION_TIME 25
#define PLTMX3D_UNIT_UID 100

typedef struct NMESW NMESW;
typedef struct dds3Basic_t dds3Basic_t;
typedef struct dds3ModelHandle_t dds3ModelHandle_t;
typedef struct dds3ProcessID_t dds3ProcessID_t;
typedef struct evtFrameInfo_t evtFrameInfo_t;
typedef struct evtViewerInfo_t evtViewerInfo_t;
typedef struct evtViewerObject_t evtViewerObject_t;
typedef struct dds3Effect_Blur_t pmdBlur2Table_t;
typedef struct dds3Effect_DistortionBlurParam_t pmdDistBlurTable_t;
typedef struct dds3Effect_Filter_t pmdFilterTable_t;
typedef struct dds3Effect_ParallelBlur_t pmdHeikouBlurTable_t;
typedef struct pmdLoadScene pmdLoadScene;
typedef struct dds3Effect_PartialMultiBlurParam_t pmdMultBlurTable_t;
typedef struct dds3Effect_PartialMultiFilterParam_t pmdMultFilterTable_t;
typedef struct pmdProcessWork_t pmdProcessWork_t;
typedef struct dds3Effect_RippleBlurParam_t pmdRipBlurTable_t;
typedef struct pmdSceneFogTable_t pmdSceneFogTable_t;
typedef struct pmdSceneLightTable_t pmdSceneLightTable_t;
typedef struct sdfIVector2_t sdfIVector2_t;
typedef struct sdfMotionCtrlr_t sdfMotionCtrlr_t;

struct NMESW {
    evtViewerObject_t *obj;
    evtFrameInfo_t *frame;
    s32 nowframe;
    s32 length;
    evtViewerInfo_t *pInfo;
    NMESW *next;
};

u16 file_major;
u16 file_minor;
u16 file_seq;
s32 gAns;
bool start;
bool play;
bool skyFilterSet;
static s16 winoff_x;
static s16 winoff_y;
static dds3ProcessID_t *pmv_pid;
static s32 last_skip_stat;
static evtViewerObject_t *evt_camera;
static pmdSceneLightTable_t *rf2_sl;
static pmdSceneFogTable_t *rf2_sf;
static pmdBlur2Table_t *rf2_bl2;
static pmdMultBlurTable_t *rf2_mbl;
static pmdFilterTable_t *rf2_fl;
static pmdMultFilterTable_t *rf2_mfl;
static pmdDistBlurTable_t *rf2_dbl;
static pmdRipBlurTable_t *rf2_rbl;
static pmdHeikouBlurTable_t *rf2_hbl;
bool ButtonGuideFlag;
static s32 ButtonGuideCount;
static bool s_IsPause;
static sdfVector4_t _pos;
static sdfVector4_t _rot;
static sdfIVector2_t _maskofs;
static NMESW *nmesw_top;
static u8 *skip_filterrgba;

static void DelEffectTable(s32 no, evtViewerInfo_t *pInfo);
static void ValidatePathFrame(s32 nowframe, evtViewerInfo_t *pInfo);
static void ValidateUnitMotionFrame(s32 nowframe, evtViewerInfo_t *pInfo, s32 mode);
static evtFrameInfo_t *GetUnitMotionChangeFrame(evtViewerObject_t *obj, s32 nowframe, s32 groupno);
static void ValidateUnitPosChange(s32 nowframe, evtViewerInfo_t *pInfo);
static void ValidateEventSkip(evtViewerInfo_t *pInfo);
static void ValidateBlurAndMFilterTextureSet(s32 nowframe, evtViewerInfo_t *pInfo);
static void ValidateMovie(evtViewerInfo_t *pInfo);
static void ValidateRenderTex(evtViewerInfo_t *pInfo);
static bool CheckEventSkipDulationTime(evtViewerInfo_t *pInfo);
static void LinkFrameInfo(evtViewerObject_t *parent, evtFrameInfo_t *f);
static void UnlinkFrameInfo(evtViewerObject_t *parent, evtFrameInfo_t *f);
static void SortFrameInfo(evtViewerObject_t *parent);
static evtFrameInfo_t *AddFrameInfo2(evtViewerObject_t *parent, s32 frame, evtViewerInfo_t *pInfo);
static void DelFrameInfo(evtViewerObject_t *parent, evtFrameInfo_t *f);
static void LinkObject(evtViewerObject_t *obj, evtViewerInfo_t *pInfo);
static void UnlinkObject(evtViewerObject_t *obj, evtViewerInfo_t *pInfo);
static void DelViewerObject(evtViewerObject_t *obj, evtViewerInfo_t *pInfo);
static void SetFirstFrame(evtViewerInfo_t *pInfo);
static void SetLastFrame(evtViewerInfo_t *pInfo);
static void FreeInfo(evtViewerInfo_t *pInfo);
static s32 SearchNameTable(char *name, evtViewerInfo_t *pInfo);
static dds3Basic_t *SearchBasicFromNameIndex(s32 nameindex, evtViewerInfo_t *pInfo);
static void LinkEffectBasic(dds3Basic_t *eff, s32 nameindex, s32 posindex, s32 baseframe, evtViewerInfo_t *pInfo);
static s32 AddEffectTable2(s32 nowframe, evtViewerObject_t *obj, evtFrameInfo_t *f, evtViewerInfo_t *pInfo);
static dds3ModelHandle_t *GetModelHandleFromUID(s32 UID, dds3Basic_t *unit);
static sdfMotionCtrlr_t *CreateMotion(dds3ModelHandle_t *aHandle, s32 aGroup);
static bool DrawTmxTextureFrom2Frame(evtViewerInfo_t *pInfo, evtViewerObject_t *obj, evtFrameInfo_t *nearframe, evtFrameInfo_t *frame);
static void DrawTmxTexture(evtViewerInfo_t *pInfo);
static void DrawEffect(evtViewerInfo_t *pInfo);
static void SetActiveCamera(evtViewerInfo_t *pInfo);
static void ReqMessage(evtViewerObject_t *obj, evtFrameInfo_t *frame, s32 nowframe, s32 length, evtViewerInfo_t *pInfo);
static void RunFrame1(evtViewerObject_t *obj, evtFrameInfo_t *frame, s32 nowframe, s32 length, evtViewerInfo_t *pInfo);
static bool IsNextMesSet(void);
static void AddNextMesSet(evtViewerObject_t *obj, evtFrameInfo_t *frame, s32 nowframe, s32 length, evtViewerInfo_t *pInfo);
static void CalcNextMesSet(void);
static void InFrame1(evtViewerObject_t *obj, evtFrameInfo_t *frame, s32 nowframe, s32 length, evtViewerInfo_t *pInfo);
static void VisibleFrame1(evtViewerObject_t *obj, evtFrameInfo_t *frame, s32 nowframe, evtViewerInfo_t *pInfo);
static void ValidatePLTMX(evtViewerInfo_t *pInfo);
static bool ValidateAt3Bgm(evtViewerInfo_t *pInfo);
static bool Validate1stAt3Bgm(evtViewerInfo_t *pInfo);
static void OutFrame1(evtViewerObject_t *obj, evtFrameInfo_t *frame, s32 nowframe, s32 length, evtViewerInfo_t *pInfo);
static void CalcLightCycle(pmdSceneLightTable_t *sl, evtFrameInfo_t *frame, s32 nowframe, evtViewerInfo_t *pInfo);
static void RunFrame2(evtViewerObject_t *obj, evtFrameInfo_t *frame, evtFrameInfo_t *nearframe, s32 nowframe, s32 *l, evtViewerInfo_t *pInfo, s32 offset);
static void RunFrame3(s32 nowframe, evtViewerInfo_t *pInfo);
static void RunFrameUnit(evtViewerObject_t *obj, s32 nowframe);
static char *ChgVoiceLabel(char *lbl);
static evtFrameInfo_t *GetNearCameraFrame(evtViewerInfo_t *pInfo);
static bool ChkSkipIgnoreBgmFadeOutEvent(pmdProcessWork_t *wdata);
static void EventSkipStart(evtViewerInfo_t *pInfo);
static void EventSkipFilterManager(evtViewerInfo_t *pInfo);
static void MovieStop(evtViewerInfo_t *pInfo);
static void DrawNoSkiPrint(evtViewerInfo_t *pInfo);
static evtFrameInfo_t *GetNextNearCameraFrame(evtViewerInfo_t *pInfo);
static void MessageManager(evtViewerInfo_t *pInfo);
static s32 DrawMessage(evtViewerInfo_t *pInfo);
static void DelAllObjFrame(evtViewerInfo_t *pInfo);
static void UnitMotionChangeForWait(s32 nowframe, dds3Basic_t *b, evtViewerObject_t *obj, evtViewerInfo_t *pInfo);
static void evtValidateUnitMotionFrameForWait(s32 nowframe, evtViewerInfo_t *pInfo);
static dds3ProcessFunc_t Process3(dds3ProcessID_t *id);
static dds3ProcessFunc_t Process2(dds3ProcessID_t *id);
static bool ChkIgnoreBgmFadeOutEvent(pmdProcessWork_t *wdata);
static void End(evtViewerInfo_t *pInfo);

// 0x1a11cb0
void evtSetPause(bool isPause) {
  s_IsPause = isPause;
}

// 0x1a11d20
bool evtIsPause(void) {
  return s_IsPause;
}

// 0x1a11da0
static void DelEffectTable(s32 no, evtViewerInfo_t *pInfo) {
  dds3Basic_t *v5;
  Il2CppClass **v6;

  v5 = pInfo->efftable[no];
  if (v5)
  {
    dds3SceneBasicDelete(v5);
    v6 = &pInfo->efftable->obj.klass + no;
    v6[4] = 0;
  }
}

// 0x1a11e40
static void ValidatePathFrame(s32 nowframe, evtViewerInfo_t *pInfo) {
  dds3Basic_t *ActiveScene;
  void *workdata;
  u64 *monitor;
  dds3Basic_t *next;
  evtViewerObject_t *firstobjinfo;
  s32 Offset;
  evtViewerObject_t *v14;
  s32 Item;
  evtFrameInfo_t *v17;
  s32 v18;
  evtFrameInfo_t *firstframeinfo;
  s32 v20;
  s32 frame;
  s32 v22;
  evtFrameInfo_t *v23;

  ActiveScene = dds3GetActiveScene();
  if (!ActiveScene)
    return;
  workdata = ActiveScene->workdata;
  if (!workdata)
    return;
  monitor = workdata[1].monitor;
  if (!monitor)
    return;
  next = *(dds3Basic_t *)(monitor[7] + 24);
  if (!next)
    return;
  firstobjinfo = pInfo->firstobjinfo;
  if (!firstobjinfo)
  {
    do
      next = next->next;
    while (next);
    return;
  }
LABEL_17:
  while (!firstobjinfo->basic || next != dds3ObjectBaseGetControlBasic(&firstobjinfo->basic, 1u))
  {
    firstobjinfo = firstobjinfo->next;
    if (!firstobjinfo)
      goto LABEL_48;
  }
  if (firstobjinfo->type != 2)
  {
    Item = 0;
    Offset = firstobjinfo->object_data->Offset;
    goto LABEL_26;
  }
  if (firstobjinfo->framecnt)
  {
    Offset = firstobjinfo->firstframeinfo->frame;
    goto LABEL_22;
  }
  Offset = 0;
LABEL_22:
  v14 = pInfo->firstobjinfo;
  if (!v14)
    goto LABEL_46;
  v17 = 0;
  v18 = 99999;
  do
  {
    if (v14->type == 2)
    {
      firstframeinfo = v14->firstframeinfo;
      if (firstframeinfo)
      {
        v20 = pInfo->nowframe;
        do
        {
          frame = firstframeinfo->frame;
          v22 = v20 - frame;
          if (v18 <= v20 - frame)
            v23 = v17;
          else
            v23 = firstframeinfo;
          firstframeinfo = firstframeinfo->next;
          if (v18 < v22)
            v22 = v18;
          if (v20 >= frame)
          {
            v18 = v22;
            v17 = v23;
          }
        }
        while (firstframeinfo);
      }
    }
    v14 = v14->next;
  }
  while (v14);
  if (!v17)
  {
LABEL_46:
    Item = 0;
    goto LABEL_26;
  }
  Item = get_Item(v17->data[1]->s, 1, 0);
LABEL_26:
  evtMoverFrameSet(next, 0, Offset, nowframe, Item);
LABEL_48:
  while (1)
  {
    next = next->next;
    if (!next)
      break;
    firstobjinfo = pInfo->firstobjinfo;
    if (firstobjinfo)
      goto LABEL_17;
  }
}

// 0x1a12100
static void ValidateUnitMotionFrame(s32 nowframe, evtViewerInfo_t *pInfo, s32 mode) {
  dds3Basic_t *ActiveScene;
  void *workdata;
  dds3Basic_t *next;
  evtViewerObject_t *firstobjinfo;

  ActiveScene = dds3GetActiveScene();
  if (!ActiveScene)
    return;
  workdata = ActiveScene->workdata;
  next = *(dds3Basic_t *)(*((u64 *)workdata[1].monitor + 9) + 24);
  if (next)
  {
    firstobjinfo = pInfo->firstobjinfo;
    if (firstobjinfo)
    {
LABEL_12:
      while (firstobjinfo->basic != next)
      {
        firstobjinfo = firstobjinfo->next;
        if (!firstobjinfo)
          goto LABEL_18;
      }
      evtUnitMotionChange(nowframe, next, firstobjinfo, pInfo, mode);
LABEL_18:
      while (1)
      {
        next = next->next;
        if (!next)
          break;
        firstobjinfo = pInfo->firstobjinfo;
        if (firstobjinfo)
          goto LABEL_12;
      }
    }
    else
    {
      do
        next = next->next;
      while (next);
    }
  }
}

// 0x1a12820
static evtFrameInfo_t *GetUnitMotionChangeFrame(evtViewerObject_t *obj, s32 nowframe, s32 groupno) {
  char v4;
  evtFrameInfo_t *firstframeinfo;
  evtFrameInfo_t *v8;
  s32 v9;
  s32 frame;
  bool v11;
  u16 Item;

  v4 = groupno;
  firstframeinfo = obj->firstframeinfo;
  if (firstframeinfo)
  {
    v8 = 0;
    v9 = -1;
    while (1)
    {
      frame = firstframeinfo->frame;
      v11 = frame <= nowframe && v9 < frame;
      if (!v11 || get_Item(firstframeinfo->data[0]->c, 0, 0) != 5 || v4 != get_Item(firstframeinfo->data[1]->c, 0, 0))
      {
        goto LABEL_6;
      }
      Item = get_Item(firstframeinfo->data[2]->s, 0, 0);
      if (Item >= 0x1000u)
      {
        if (GBWK->IntVariable[(Item >> 12) + 199] != (Item & 0xFFF))
          goto LABEL_6;
      }
      v9 = firstframeinfo->frame;
      v8 = firstframeinfo;
LABEL_6:
      firstframeinfo = firstframeinfo->next;
      if (!firstframeinfo)
        return v8;
    }
  }
  return 0;
}

// 0x1a12a90
static void ValidateUnitPosChange(s32 nowframe, evtViewerInfo_t *pInfo) {
  evtViewerObject_t *firstobjinfo;
  evtFrameInfo_t *firstframeinfo;
  evtFrameInfo_t *v7;
  s32 frame;
  s16 Item;
  s16 v10;
  dds3Basic_t *ActiveScene;
  pmdNameTable_t *nametable;
  char *Name;
  u32 serialID;
  s32 v15;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  dds3PoseSet_t *poseset;
  dds3Basic_t *scene;
  sdfVector4_t v23;

  firstobjinfo = pInfo->firstobjinfo;
  for (scene = 0; firstobjinfo; firstobjinfo = firstobjinfo->next)
  {
    if (firstobjinfo->type != 1)
      continue;
    firstframeinfo = firstobjinfo->firstframeinfo;
    if (!firstframeinfo)
      goto LABEL_25;
    v7 = 0;
    frame = -1;
    do
    {
      if (get_Item(firstframeinfo->data[0]->c, 0, 0) == 7 && firstframeinfo->frame <= nowframe && frame < firstframeinfo->frame)
      {
        frame = firstframeinfo->frame;
        v7 = firstframeinfo;
      }
      firstframeinfo = firstframeinfo->next;
    }
    while (firstframeinfo);
    if (v7)
    {
      if (v7->frame != nowframe)
        continue;
      Item = get_Item(v7->data[1]->s, 0, 0);
      if (Item != -1)
      {
        v10 = Item;
        ActiveScene = dds3GetActiveScene();
        nametable = pInfo->nametable;
        scene = ActiveScene;
        Name = nametable[v10]->Name;
        serialID = dds3SceneBasicSearchName(scene, Name)->serialID;
        v15 = firstobjinfo->basic->serialID;
        evtSetUnitPos(v15, serialID);
        firstobjinfo->posChangeFlag = 1;
        continue;
      }
    }
    else
    {
LABEL_25:
      if (firstobjinfo->posChangeFlag != 1)
        continue;
    }
    x = firstobjinfo->orgPos.x;
    y = firstobjinfo->orgPos.y;
    z = firstobjinfo->orgPos.z;
    w = firstobjinfo->orgPos.w;
    v23.x = x;
    v23.y = y;
    v23.z = z;
    v23.w = w;
    dds3SetPosPoseSet(&firstobjinfo->basic, v23);
    dds3SetRotPoseSet(&firstobjinfo->basic, firstobjinfo->orgRot);
    dds3GetPosPoseSet(&firstobjinfo->basic);
    poseset = firstobjinfo->basic->poseset;
    poseset->pos2 = vct_A;
    firstobjinfo->posChangeFlag = 0;
  }
}

// 0x1a12d90
static void ValidateEventSkip(evtViewerInfo_t *pInfo) {
  if ((pInfo->stat & 0x10) == 0)
    return;
  ++pInfo->EventSkipCount;
  return;
}

// 0x1a12e30
static void ValidateBlurAndMFilterTextureSet(s32 nowframe, evtViewerInfo_t *pInfo) {
  evtViewerObject_t *firstobjinfo;
  void *DistortionBlur_local;
  s64 *v7;
  u32 type;
  evtFrameInfo_t *firstframeinfo;
  void *hTex;
  u16 Item;
  pmdNameTable_t *nametable;
  char *v15;
  u32 v16;
  void *v17;
  void *v18;
  void *v19;
  void *v20;
  bool v21;
  void *PartialMultiBlur_local;
  s64 *v25;
  bool v26;
  bool v29;
  bool v31;
  void *target;
  void *p_curDBlurTexHandle;
  void *p_curRBlurTexHandle;
  void *p_curMFilterTexHandle;

  firstobjinfo = pInfo->firstobjinfo;
  if (firstobjinfo)
  {
    p_curMFilterTexHandle = &pInfo->curMFilterTexHandle;
    p_curDBlurTexHandle = &pInfo->curDBlurTexHandle;
    p_curRBlurTexHandle = &pInfo->curRBlurTexHandle;
    target = &pInfo->curMBlurTexHandle;
    while (1)
    {
      type = firstobjinfo->type;
      if (type <= 0x17 && ((1 << type) & 0x82C000) != 0)
        break;
LABEL_9:
      firstobjinfo = firstobjinfo->next;
      if (!firstobjinfo)
        return;
    }
    firstframeinfo = firstobjinfo->firstframeinfo;
    if (!firstframeinfo)
    {
      hTex = 0;
      v16 = type - 14;
      goto LABEL_36;
    }
    hTex = 0;
    while (1)
    {
      if (firstobjinfo->type == 17)
      {
        Item = get_Item(firstframeinfo->data[3]->s, 0, 0);
        if (Item >= 0x1000u)
        {
          if (GBWK->IntVariable[(Item >> 12) + 199] != (Item & 0xFFF))
            goto LABEL_17;
        }
      }
      if (firstobjinfo->object_data->Offset + firstframeinfo->frame > nowframe)
      {
LABEL_33:
        v16 = firstobjinfo->type - 14;
        if (v16 > 9)
          goto LABEL_9;
LABEL_36:
        switch (v16)
        {
          case 0u:
            v17 = target;
            if (!op_Inequality(target, hTex, 0))
              goto LABEL_9;
            target = hTex;
            v21 = op_Equality(hTex, 0, 0);
            if (v21)
            {
              PartialMultiBlur_local = PartialMultiBlur;
              v25 = &Method_Project_Eve_CtrlTex_dds3Effect_PartialMultiBlurParam_t__SetDefTex__;
              goto LABEL_77;
            }
            DistortionBlur_local = PartialMultiBlur;
            v7 = &Method_Project_Eve_CtrlTex_dds3Effect_PartialMultiBlurParam_t__SetTex__;
            goto LABEL_8;
          case 1u:
            v18 = p_curDBlurTexHandle;
            if (!op_Inequality(p_curDBlurTexHandle, hTex, 0))
              goto LABEL_9;
            p_curDBlurTexHandle = hTex;
            v26 = op_Equality(hTex, 0, 0);
            if (v26)
            {
              PartialMultiBlur_local = DistortionBlur;
              v25 = &Method_Project_Eve_CtrlTex_dds3Effect_DistortionBlurParam_t__SetDefTex__;
              goto LABEL_77;
            }
            DistortionBlur_local = DistortionBlur;
            v7 = &Method_Project_Eve_CtrlTex_dds3Effect_DistortionBlurParam_t__SetTex__;
            goto LABEL_8;
          case 3u:
            v19 = p_curMFilterTexHandle;
            if (!op_Inequality(p_curMFilterTexHandle, hTex, 0))
              goto LABEL_9;
            p_curMFilterTexHandle = hTex;
            v29 = op_Equality(hTex, 0, 0);
            if (v29)
            {
              PartialMultiBlur_local = PartialMultiFilter;
              v25 = &Method_Project_Eve_CtrlTex_dds3Effect_PartialMultiFilterParam_t__SetDefTex__;
              goto LABEL_77;
            }
            DistortionBlur_local = PartialMultiFilter;
            v7 = &Method_Project_Eve_CtrlTex_dds3Effect_PartialMultiFilterParam_t__SetTex__;
            goto LABEL_8;
          case 9u:
            v20 = p_curRBlurTexHandle;
            if (!op_Inequality(p_curRBlurTexHandle, hTex, 0))
              goto LABEL_9;
            p_curRBlurTexHandle = hTex;
            v31 = op_Equality(hTex, 0, 0);
            if (v31)
            {
              PartialMultiBlur_local = RippleBlur;
              v25 = &Method_Project_Eve_CtrlTex_dds3Effect_RippleBlurParam_t__SetDefTex__;
LABEL_77:
              _SetDefTex(PartialMultiBlur_local, *v25);
            }
            else
            {
              DistortionBlur_local = RippleBlur;
              v7 = &Method_Project_Eve_CtrlTex_dds3Effect_RippleBlurParam_t__SetTex__;
LABEL_8:
              _SetTex(DistortionBlur_local, hTex, *v7);
            }
            goto LABEL_9;
          default:
            goto LABEL_9;
        }
      }
      if (get_Item(firstframeinfo->data[2]->s, 0, 0))
      {
        hTex = 0;
        if (get_Item(firstframeinfo->data[2]->s, 0, 0) != 1)
        {
          nametable = pInfo->nametable;
          v15 = *(char **)(*((u64 *)&nametable->bounds + get_Item(firstframeinfo->data[2]->s, 0, 0)) + 16);
          hTex = evtFindObjectFromName(pInfo, v15)->hTex;
        }
      }
LABEL_17:
      firstframeinfo = firstframeinfo->next;
      if (!firstframeinfo)
        goto LABEL_33;
    }
  }
}

// 0x1a13520
static void ValidateMovie(evtViewerInfo_t *pInfo) {
  s32 nowframe;
  s32 *p_MovieEndFrame;
  s32 MovieEndFrame;

  if (pInfo->nowMovieStat != 1)
    return;
  nowframe = pInfo->nowframe;
  if (pInfo->MovieStartFrame > nowframe)
  {
    movieStop(0);
    p_MovieEndFrame = &pInfo->MovieEndFrame;
LABEL_14:
    *(u64 *)&pInfo->nowMovieStat = 0;
    *p_MovieEndFrame = 0;
LABEL_15:
    pInfo->real_movie_last_frame = -1;
    return;
  }
  p_MovieEndFrame = &pInfo->MovieEndFrame;
  MovieEndFrame = pInfo->MovieEndFrame;
  if ((MovieEndFrame & 0x80000000) == 0)
  {
    if (MovieEndFrame > nowframe)
      return;
    movieStop(0);
    goto LABEL_14;
  }
  if (drawEnd)
    goto LABEL_15;
}

// 0x1a136e0
static void ValidateRenderTex(evtViewerInfo_t *pInfo) {
  evtViewerObject_t *firstobjinfo;
  s32 nowframe;
  evtFrameInfo_t *firstframeinfo;
  evtFrameInfo_t *lastframeinfo;
  evtFrameInfo_t *v7;
  s32 Offset;
  evtRenderInfo_t *renderTexInfo;
  s32 frame;
  f32 v11;
  s32 v12;
  evtRenderInfo_t *v13;
  s16 Item;
  s16 v15;
  f32 v17;
  f32 v18;
  s32 v19;

  firstobjinfo = pInfo->firstobjinfo;
  if (firstobjinfo)
  {
    while (firstobjinfo->type != 31)
    {
      firstobjinfo = firstobjinfo->next;
      if (!firstobjinfo)
        return;
    }
    nowframe = pInfo->nowframe;
    firstframeinfo = firstobjinfo->firstframeinfo;
    lastframeinfo = firstobjinfo->lastframeinfo;
    if (firstframeinfo)
    {
      v7 = 0;
      Offset = firstobjinfo->object_data->Offset;
      while (firstframeinfo->frame + Offset <= nowframe)
      {
        if (get_Item(firstframeinfo->data[0]->s, 0, 0) == 1)
          v7 = firstframeinfo;
        firstframeinfo = firstframeinfo->next;
        if (!firstframeinfo)
          goto LABEL_15;
      }
      lastframeinfo = firstframeinfo->prev;
      if (lastframeinfo)
      {
LABEL_18:
        if (nowframe == lastframeinfo->frame && !get_Item(lastframeinfo->data[0]->s, 0, 0))
        {
          evtRenderTexStart(pInfo);
        }
      }
    }
    else
    {
      v7 = 0;
LABEL_15:
      if (lastframeinfo)
        goto LABEL_18;
    }
    if (!v7)
    {
      pInfo->renderTexInfo->draw = 0;
      return;
    }
    if (get_Item(v7->data[0]->s, 1, 0) >= 1)
      pInfo->renderTexInfo->draw = 1;
    if (!firstframeinfo)
    {
LABEL_29:
      renderTexInfo = pInfo->renderTexInfo;
      renderTexInfo->alpha = get_Item(v7->data[0]->s, 1, 0);
      return;
    }
    while (get_Item(firstframeinfo->data[0]->s, 0, 0) != 1)
    {
      firstframeinfo = firstframeinfo->next;
      if (!firstframeinfo)
        goto LABEL_29;
    }
    frame = v7->frame;
    v11 = 0.0;
    v12 = firstframeinfo->frame - frame;
    if (v12)
      v11 = (f32)(nowframe - frame) / (f32)v12;
    v13 = pInfo->renderTexInfo;
    Item = get_Item(v7->data[0]->s, 1, 0);
    v15 = get_Item(firstframeinfo->data[0]->s, 1, 0);
    v17 = 1.0;
    if (v11 <= 1.0)
      v17 = v11;
    if (v11 < 0.0)
      v17 = 0.0;
    v18 = (f32)(v17 * (f32)((f32)v15 - (f32)Item)) + (f32)Item;
    v19 = v18;
    if (v18 == INFINITY)
      v19 = 0x80000000;
    v13->alpha = v19;
    return;
  }
}

// 0x1a13a10
static bool CheckEventSkipDulationTime(evtViewerInfo_t *pInfo) {
  return (LOBYTE(pInfo->stat) >> 4) & 1;
}

// 0x1a13a20
static void LinkFrameInfo(evtViewerObject_t *parent, evtFrameInfo_t *f) {
  evtFrameInfo_t *p_firstframeinfo;
  evtFrameInfo_t *next;
  evtFrameInfo_t *firstframeinfo;
  evtFrameInfo_t *lastframeinfo;
  evtFrameInfo_t *v9;
  evtFrameInfo_t *p_lastframeinfo;
  evtFrameInfo_t *v11;
  evtFrameInfo_t *prev;
  evtFrameInfo_t *v13;

  firstframeinfo = parent->firstframeinfo;
  p_firstframeinfo = &parent->firstframeinfo;
  next = firstframeinfo;
  if (firstframeinfo)
  {
    while (f->frame >= (u32)next->frame)
    {
      next = next->next;
      if (!next)
      {
        lastframeinfo = parent->lastframeinfo;
        lastframeinfo->next = f;
        v9 = parent->lastframeinfo;
        f->prev = v9;
        f->next = 0;
        p_lastframeinfo = &parent->lastframeinfo;
        parent->lastframeinfo = f;
LABEL_8:
        v11 = f;
        goto LABEL_9;
      }
    }
    prev = next->prev;
    if (prev)
    {
      prev->next = f;
      v13 = next->prev;
      f->prev = v13;
      f->next = next;
      next->prev = f;
      p_lastframeinfo = &next->prev;
      goto LABEL_8;
    }
    p_firstframeinfo = f;
    next->prev = f;
    f->prev = 0;
    f->next = next;
    p_lastframeinfo = &f->next;
    v11 = next;
  }
  else
  {
    parent->firstframeinfo = f;
    parent->lastframeinfo = f;
    f->next = 0;
    f->prev = 0;
    p_lastframeinfo = &f->prev;
    v11 = 0;
  }
LABEL_9:
  ++parent->framecnt;
}

// 0x1a13b90
static void UnlinkFrameInfo(evtViewerObject_t *parent, evtFrameInfo_t *f) {
  evtFrameInfo_t *prev;
  evtFrameInfo_t *p_prev;
  evtFrameInfo_t *next;
  evtFrameInfo_t *p_next;
  evtFrameInfo_t *p_firstframeinfo;
  evtFrameInfo_t *v9;
  evtFrameInfo_t *p_lastframeinfo;

  p_prev = &f->prev;
  prev = f->prev;
  p_next = &f->next;
  next = f->next;
  if (prev)
    p_firstframeinfo = &prev->next;
  else
    p_firstframeinfo = &parent->firstframeinfo;
  p_firstframeinfo = next;
  v9 = p_prev;
  if (p_next)
    p_lastframeinfo = &p_next->prev;
  else
    p_lastframeinfo = &parent->lastframeinfo;
  p_lastframeinfo = v9;
  p_prev = 0;
  p_next = 0;
  --parent->framecnt;
}

// 0x1a13c30
static void SortFrameInfo(evtViewerObject_t *parent) {
  evtFrameInfo_t *firstframeinfo;
  evtFrameInfo_t *next;
  evtFrameInfo_t *prev;
  void **p_prev;
  evtFrameInfo_t *v7;
  evtFrameInfo_t *p_next;
  evtFrameInfo_t *p_firstframeinfo;
  evtFrameInfo_t *v10;
  evtFrameInfo_t *p_lastframeinfo;

  if (parent)
  {
    firstframeinfo = parent->firstframeinfo;
    if (firstframeinfo)
    {
      next = parent->firstframeinfo;
      while (1)
      {
        next = next->next;
        if (!next)
          break;
        if (firstframeinfo->frame > (u32)next->frame)
        {
          p_prev = &next->prev;
          prev = next->prev;
          p_next = &next->next;
          v7 = next->next;
          if (prev)
            p_firstframeinfo = &prev->next;
          else
            p_firstframeinfo = &parent->firstframeinfo;
          p_firstframeinfo = v7;
          v10 = *p_prev;
          if (p_next)
            p_lastframeinfo = &p_next->prev;
          else
            p_lastframeinfo = &parent->lastframeinfo;
          p_lastframeinfo = v10;
          *p_prev = 0;
          p_next = 0;
          --parent->framecnt;
          sub_1A22140(parent, next, 0);
          firstframeinfo = next->next;
          if (!firstframeinfo)
            return;
LABEL_19:
          next = firstframeinfo;
        }
      }
      firstframeinfo = firstframeinfo->next;
      if (!firstframeinfo)
        return;
      goto LABEL_19;
    }
  }
}

// 0x1a13d70
evtFrameInfo_t *evtAddFrameInfo(evtViewerObject_t *parent, s32 frame, evtViewerInfo_t *pInfo) {
  evtFrameInfo_t *v7;
  s32 type;
  evtViewerObject_t *framelist_target;
  s32 nowframe;
  pmdSceneLightTable_t *v11;
  char *Name;
  s32 v15;
  pmdDataInfo_t *data;
  s32 priority;
  s32 v18;
  DataC *c;
  char *v21;
  char *v22;
  s32 v23;
  pmdDataInfo_t *v24;
  pmdDataInfo_t *v25;
  char *v26;
  s32 v27;
  pmdDataInfo_t *v28;
  s32 v29;
  s32 v30;
  pmdDataInfo_t *v31;
  s64 v32;
  evtFrameInfo_t *v34;
  __int128 v36;
  pmdMultBlurTable_t *v38;
  dds3Effect_PartialMultiBlurParam_t *Params;
  dds3Effect_DistortionBlurParam_t *v42;
  dds3Effect_PartialMultiFilterParam_t *v45;
  pmdDataInfo_t *v46;
  dds3Effect_RippleBlurParam_t *v48;
  char *v50;
  s32 v51;
  pmdDataInfo_t *v52;
  char *v53;
  s32 v54;
  pmdDataInfo_t *v55;
  Il2CppObject **p_p;
  s64 nameindex;
  pmdTmxData_t *out_tmxdata;
  s64 out_bias;

  v7 = (evtFrameInfo_t *)Allocate(evtFrameInfo_t);
  _ctor(v7, 0);
  type = parent->type;
  out_bias = 0;
  out_tmxdata = 0;
  if (type > 24)
  {
    if (type != 36)
      goto LABEL_11;
    goto LABEL_8;
  }
  if (type == 10)
  {
    v11 = Allocate(pmdSceneLightTable_t);
    _ctor(v11, 0);
    evtGetValueNewSLightFrame(pInfo, parent, frame, v11, (f32 *)&out_bias + 1, &out_bias);
    v7->frame = frame;
    v7->nameindex = -1;
    goto LABEL_13;
  }
  if (type == 24)
  {
LABEL_8:
    framelist_target = pInfo->framelist_target;
    nowframe = pInfo->nowframe;
    evtGetValueNewTMXFrame(pInfo, framelist_target, nowframe, out_tmxdata);
  }
LABEL_11:
  v11 = 0;
  v7->frame = frame;
  v7->nameindex = -1;
LABEL_13:
  sub_1A22140(parent, v7, 0);
  switch (parent->type)
  {
    case 1:
      Name = pInfo->nametable[parent->nameindex]->Name;
      v15 = evtAddNameTable(Name, pInfo);
      data = v7->data;
      v7->nameindex = v15;
      set_Item(data[0]->c, 0, 0, 0);
      set_Item(v7->data[1]->c, 2, 1, 0);
      LOBYTE(priority) = 20;
      v18 = 3;
      c = v7->data[1]->c;
      goto LABEL_59;
    case 2:
      set_f(v7->data[0], 0.5235988, 0);
      v21 = pInfo->nametable[parent->nameindex]->Name;
      v7->nameindex = evtAddNameTable(v21, pInfo);
      return v7;
    case 3:
      v22 = pInfo->nametable[parent->nameindex]->Name;
      v23 = evtAddNameTable(v22, pInfo);
      v24 = v7->data;
      v7->nameindex = v23;
      set_Item(v24[0]->c, 0, 255, 0);
      set_Item(v7->data[0]->s, 1, 0, 0);
      set_Item(v7->data[1]->c, 0, 0, 0);
      set_Item(v7->data[1]->c, 1, 255, 0);
      set_Item(v7->data[1]->s, 1, 0xFFFF, 0);
      v25 = v7->data;
      goto LABEL_42;
    case 9:
      v26 = pInfo->nametable[parent->nameindex]->Name;
      v27 = evtAddNameTable(v26, pInfo);
      v28 = v7->data;
      v7->nameindex = v27;
      set_Item(v28[0]->s, 0, 0xFFFF, 0);
      v29 = 1;
      LOWORD(v30) = 1;
      v31 = v7->data[0];
      goto LABEL_69;
    case 0xA:
      v7->p = v11;
      set_f(v7->data[0], *((f32 *)&out_bias + 1), 0);
      set_f(v7->data[1], *(f32 *)&out_bias, 0);
      set_Item(v7->data[2]->s, 0, parent->myno, 0);
      set_Item(v7->data[3]->s, 0, 0, 0);
      set_Item(v7->data[3]->s, 1, 0, 0);
      set_Item(v7->data[4]->s, 0, 0, 0);
      set_Item(v7->data[4]->s, 1, 0, 0);
      set_Item(v7->data[5]->c, 0, 0, 0);
      set_Item(v7->data[5]->c, 1, 0, 0);
      set_Item(v7->data[5]->c, 2, 0, 0);
      v7->nameindex = 0;
      return v7;
    case 0xB:
      v32 = Allocate(pmdSceneFogTable_t);
      v34 = v7;
      *(u64 *)&v36 = vrev64q_s32(FogParam[1]).n128_u64[0];
      *((u64 *)&v36 + 1) = FogParam[1].n128_u64[1];
      *(_OWORD *)(v32 + 16) = v36;
      *(u32 *)(v32 + 32) = FogParam[2].n128_u32[0];
      goto LABEL_67;
    case 0xC:
      set_Item(v7->data[0]->s, 0, 1, 0);
      set_Item(v7->data[0]->s, 1, 128, 0);
      set_i(v7->data[1], 0, 0);
      return v7;
    case 0xD:
      v32 = Allocate(pmdBlur2Table_t);
      _ctor(v32, 0);
      CopyTo(effEvent_Edit_Blur, v32, 0);
LABEL_66:
      v34 = v7;
LABEL_67:
      v34->p = v32;
      p_p = &v34->p;
      v46 = *(p_p - 2);
LABEL_68:
      v31 = v46[0];
      v29 = 0;
      LOWORD(v30) = 1;
LABEL_69:
      set_Item(v31->s, v29, v30, 0);
      return v7;
    case 0xE:
      v38 = Allocate(pmdMultBlurTable_t);
      _ctor(v38, 0);
      Params = EditorGetParams(PartialMultiBlur, 0);
      CopyTo(Params, v38, 0);
      v7->p = v38;
      set_Item(v7->data[0]->s, 0, 1, 0);
      v25 = v7->data;
LABEL_42:
      v31 = v25[2];
      v29 = 0;
      LOWORD(v30) = 0;
      goto LABEL_69;
    case 0xF:
      v32 = Allocate(pmdDistBlurTable_t);
      _ctor(v32, 0);
      v42 = EditorGetParams(DistortionBlur, 0);
      CopyTo(v42, v32, 0);
      goto LABEL_66;
    case 0x10:
      v32 = Allocate(pmdFilterTable_t);
      _ctor(v32, 0);
      CopyTo(Filter->param, v32, 0);
      goto LABEL_66;
    case 0x11:
      v32 = Allocate(pmdMultFilterTable_t);
      _ctor(v32, 0);
      v45 = EditorGetParams(PartialMultiFilter, 0);
      CopyTo(v45, v32, 0);
      goto LABEL_66;
    case 0x16:
      v46 = v7->data;
      goto LABEL_68;
    case 0x17:
      v32 = Allocate(pmdRipBlurTable_t);
      _ctor(v32, 0);
      v48 = EditorGetParams(RippleBlur, 0);
      CopyTo(v48, v32, 0);
      goto LABEL_66;
    case 0x18:
      v50 = pInfo->nametable[parent->nameindex]->Name;
      goto LABEL_58;
    case 0x1A:
      v53 = pInfo->nametable[parent->nameindex]->Name;
      v54 = evtAddNameTable(v53, pInfo);
      v55 = v7->data;
      v7->nameindex = v54;
      set_Item(v55[0]->c, 0, 255, 0);
      set_Item(v7->data[0]->s, 1, 0, 0);
      set_Item(v7->data[1]->c, 0, 0, 0);
      set_Item(v7->data[1]->c, 1, 255, 0);
      set_Item(v7->data[1]->s, 1, 0xFFFF, 0);
      set_Item(v7->data[2]->s, 0, 0, 0);
      v29 = 1;
      LOWORD(v30) = 0;
      v31 = v7->data[3];
      goto LABEL_69;
    case 0x1B:
      v32 = Allocate(pmdHeikouBlurTable_t);
      _ctor(v32, 0);
      CopyTo(ParallelBlur->param, v32, 0);
      goto LABEL_66;
    case 0x21:
      v29 = 0;
      v30 = pInfo->nowframe;
      v31 = v7->data[0];
      goto LABEL_69;
    case 0x24:
      nameindex = (u32)parent->nameindex;
      if ((nameindex & 0x80000000) != 0)
        return v7;
      v50 = pInfo->nametable[nameindex]->Name;
LABEL_58:
      v51 = evtAddNameTable(v50, pInfo);
      v52 = v7->data;
      v7->nameindex = v51;
      set_Item(v52[0]->c, 0, out_tmxdata->hokan, 0);
      set_Item(v7->data[0]->c, 1, out_tmxdata->transmode, 0);
      set_Item(v7->data[1]->s, 0, out_tmxdata->x, 0);
      set_Item(v7->data[1]->s, 1, out_tmxdata->y, 0);
      set_Item(v7->data[2]->uc, 0, out_tmxdata->r, 0);
      set_Item(v7->data[2]->uc, 1, out_tmxdata->g, 0);
      set_Item(v7->data[2]->uc, 2, out_tmxdata->b, 0);
      set_Item(v7->data[2]->uc, 3, out_tmxdata->a, 0);
      set_f(v7->data[3], out_tmxdata->scalew, 0);
      set_f(v7->data[4], out_tmxdata->scaleh, 0);
      v18 = 0;
      c = v7->data[5]->c;
      priority = out_tmxdata->priority;
LABEL_59:
      set_Item(c, v18, priority, 0);
      return v7;
    default:
      return v7;
  }
}

// 0x1a14b10
static evtFrameInfo_t *AddFrameInfo2(evtViewerObject_t *parent, s32 frame, evtViewerInfo_t *pInfo) {
  return evtAddFrameInfo(parent, frame, pInfo);
}

// 0x1a14b90
static void DelFrameInfo(evtViewerObject_t *parent, evtFrameInfo_t *f) {
  evtFrameInfo_t *prev;
  evtFrameInfo_t *p_prev;
  evtFrameInfo_t *next;
  evtFrameInfo_t *p_next;
  evtFrameInfo_t *p_firstframeinfo;
  evtFrameInfo_t *v10;
  evtFrameInfo_t *p_lastframeinfo;
  Il2CppObject **p_p;
  Il2CppObject *p;

  p_prev = &f->prev;
  prev = f->prev;
  p_next = &f->next;
  next = f->next;
  if (prev)
    p_firstframeinfo = &prev->next;
  else
    p_firstframeinfo = &parent->firstframeinfo;
  p_firstframeinfo = next;
  v10 = p_prev;
  if (p_next)
    p_lastframeinfo = &p_next->prev;
  else
    p_lastframeinfo = &parent->lastframeinfo;
  p_lastframeinfo = v10;
  p_prev = 0;
  p_next = 0;
  --parent->framecnt;
  p = f->p;
  p_p = &f->p;
  if (p)
  {
    *p_p = 0;
  }
}

// 0x1a14c90
static void LinkObject(evtViewerObject_t *obj, evtViewerInfo_t *pInfo) {
  evtViewerObject_t *p_firstobjinfo;
  evtViewerObject_t *firstobjinfo;
  evtViewerObject_t *lastobjinfo;
  evtViewerObject_t *v8;
  evtViewerObject_t *p_lastobjinfo;
  evtViewerObject_t *v10;
  evtViewerObject_t *prev;
  evtViewerObject_t *v12;

  p_firstobjinfo = &pInfo->firstobjinfo;
  firstobjinfo = pInfo->firstobjinfo;
  if (firstobjinfo)
  {
    while (obj->type >= firstobjinfo->type)
    {
      firstobjinfo = firstobjinfo->next;
      if (!firstobjinfo)
      {
        lastobjinfo = pInfo->lastobjinfo;
        lastobjinfo->next = obj;
        v8 = pInfo->lastobjinfo;
        obj->prev = v8;
        obj->next = 0;
        p_lastobjinfo = &pInfo->lastobjinfo;
        pInfo->lastobjinfo = obj;
LABEL_8:
        v10 = obj;
        goto LABEL_9;
      }
    }
    prev = firstobjinfo->prev;
    if (prev)
    {
      prev->next = obj;
      v12 = firstobjinfo->prev;
      obj->prev = v12;
      obj->next = firstobjinfo;
      firstobjinfo->prev = obj;
      p_lastobjinfo = &firstobjinfo->prev;
      goto LABEL_8;
    }
    p_firstobjinfo = obj;
    firstobjinfo->prev = obj;
    obj->prev = 0;
    obj->next = firstobjinfo;
    p_lastobjinfo = &obj->next;
    v10 = firstobjinfo;
  }
  else
  {
    pInfo->firstobjinfo = obj;
    pInfo->lastobjinfo = obj;
    obj->next = 0;
    obj->prev = 0;
    p_lastobjinfo = &obj->prev;
    v10 = 0;
  }
LABEL_9:
  ++pInfo->objcnt;
}

// 0x1a14e00
static void UnlinkObject(evtViewerObject_t *obj, evtViewerInfo_t *pInfo) {
  evtViewerObject_t *p_firstobjinfo;
  evtViewerObject_t *prev;
  evtViewerObject_t *p_prev;
  evtViewerObject_t *next;
  evtViewerObject_t *p_next;
  evtViewerObject_t *v9;
  evtViewerObject_t *v10;
  evtViewerObject_t *p_lastobjinfo;

  p_firstobjinfo = &pInfo->firstobjinfo;
  p_prev = &obj->prev;
  prev = obj->prev;
  p_next = &obj->next;
  next = obj->next;
  if (prev)
    v9 = &prev->next;
  else
    v9 = p_firstobjinfo;
  v9 = next;
  v10 = p_prev;
  if (p_next)
    p_lastobjinfo = &p_next->prev;
  else
    p_lastobjinfo = &pInfo->lastobjinfo;
  p_lastobjinfo = v10;
  p_prev = 0;
  p_next = 0;
  --pInfo->objcnt;
}

// 0x1a14ea0
evtViewerObject_t *evtAddObject(PMD_OBJTYPE type, evtViewerInfo_t *pInfo) {
  evtViewerObject_t *v5;

  v5 = Allocate(evtViewerObject_t);
  _ctor(v5, 0);
  if (v5)
  {
    v5->type = type;
    *(u64 *)&v5->nameindex = -1;
    sub_1A222B0(v5, pInfo, 0);
  }
  return v5;
}

// 0x1a14f50
s32 evtGetObjectTypeCount(PMD_OBJTYPE type, evtViewerInfo_t *pInfo) {
  evtViewerObject_t *firstobjinfo;
  s32 v4;
  s32 v5;

  firstobjinfo = pInfo->firstobjinfo;
  if (!firstobjinfo)
    return 0;
  v4 = 0;
  do
  {
    v5 = firstobjinfo->type;
    firstobjinfo = firstobjinfo->next;
    if (v5 == type)
      ++v4;
  }
  while (firstobjinfo);
  return v4;
}

// 0x1a14f90
s32 evtGetObjectNoCount(evtViewerInfo_t *pInfo) {
  evtViewerObject_t *firstobjinfo;
  s32 result;

  firstobjinfo = pInfo->firstobjinfo;
  if (!firstobjinfo)
    return 0;
  result = 0;
  do
  {
    firstobjinfo = firstobjinfo->next;
    ++result;
  }
  while (firstobjinfo);
  return result;
}

// 0x1a14fc0
s32 evtGetAllFrameInfoCount(s32 no, evtViewerInfo_t *pInfo) {
  evtViewerObject_t *firstobjinfo;
  s32 result;
  s32 type;
  s32 v7;

  firstobjinfo = pInfo->firstobjinfo;
  if (!firstobjinfo)
    return 0;
  if (no != 2)
  {
    if (no == 3)
    {
      result = 0;
      do
      {
        type = firstobjinfo->type;
        if (type == 19 || type == 5)
          result += firstobjinfo->framecnt;
        firstobjinfo = firstobjinfo->next;
      }
      while (firstobjinfo);
      return result;
    }
    do
      firstobjinfo = firstobjinfo->next;
    while (firstobjinfo);
    return 0;
  }
  result = 0;
  do
  {
    v7 = firstobjinfo->type;
    if (v7 != 5 && v7 != 19)
      result += firstobjinfo->framecnt;
    firstobjinfo = firstobjinfo->next;
  }
  while (firstobjinfo);
  return result;
}

// 0x1a15050
static void DelViewerObject(evtViewerObject_t *obj, evtViewerInfo_t *pInfo) {
  evtFrameInfo_t *firstframeinfo;
  s16 Item;
  void *hTex;
  void *p_mesh;
  void *mesh;
  evtViewerObject_t *p_prev;
  evtViewerObject_t *prev;
  evtViewerObject_t *v14;
  evtViewerObject_t *v15;
  evtViewerObject_t *p_next;
  evtViewerObject_t *p_firstobjinfo;
  evtViewerObject_t *v18;
  evtViewerObject_t *p_lastobjinfo;
  void *gameObject;

  firstframeinfo = obj->firstframeinfo;
  if (firstframeinfo)
  {
    while (obj->type != 33)
    {
LABEL_5:
      sub_1A22420(obj, firstframeinfo, 0);
      firstframeinfo = obj->firstframeinfo;
      if (!firstframeinfo)
        goto LABEL_13;
    }
    Item = get_Item(firstframeinfo->data[0]->s, 1, 0);
    evtDelProcess(Item);
    firstframeinfo = obj->firstframeinfo;
    goto LABEL_5;
  }
LABEL_13:
  if (obj->type == 24)
  {
    hTex = obj->hTex;
    sdfTexFree(hTex);
    obj->hTex = 0;
    p_mesh = &obj->mesh;
    mesh = obj->mesh;
    if (op_Inequality(mesh, 0, 0))
      goto LABEL_28;
  }
  goto LABEL_20;
LABEL_28:
  gameObject = get_gameObject(p_mesh, 0);
  DestroyImmediate_61008224(gameObject, 0);
  p_mesh = 0;
LABEL_20:
  prev = obj->prev;
  p_prev = &obj->prev;
  v15 = p_prev - 1;
  v14 = *(p_prev - 1);
  p_next = &prev->next;
  if (prev)
    p_firstobjinfo = p_next;
  else
    p_firstobjinfo = &pInfo->firstobjinfo;
  p_firstobjinfo = v14;
  v18 = p_prev;
  if (v15)
    p_lastobjinfo = &v15->prev;
  else
    p_lastobjinfo = &pInfo->lastobjinfo;
  p_lastobjinfo = v18;
  p_prev = 0;
  v15 = 0;
  --pInfo->objcnt;
}

// 0x1a152d0
static void SetFirstFrame(evtViewerInfo_t *pInfo) {
  s32 nowframe;
  s32 lastframe;

  lastframe = pInfo->lastframe;
  nowframe = pInfo->nowframe;
  pInfo->firstframe = nowframe;
  if (nowframe > lastframe)
    pInfo->lastframe = nowframe;
}

// 0x1a152f0
static void SetLastFrame(evtViewerInfo_t *pInfo) {
  s32 nowframe;

  nowframe = pInfo->nowframe;
  pInfo->lastframe = nowframe;
  if (nowframe < pInfo->firstframe)
    pInfo->firstframe = nowframe;
}

// 0x1a15310
static void FreeInfo(evtViewerInfo_t *pInfo) {
  evtViewerObject_t *i;
  pmdProcessWork_t *p_workdata;
  pmdProcessWork_t *v6;
  pmdProcessWork_t *workdata;

  _SetDefTex(PartialMultiBlur);
  _SetDefTex(DistortionBlur);
  _SetDefTex(RippleBlur);
  _SetDefTex(PartialMultiFilter);
  for (i = pInfo->firstobjinfo; i; i = pInfo->firstobjinfo)
  {
    sub_1A22530(i, pInfo, 0);
  }
  workdata = pInfo->workdata;
  p_workdata = &pInfo->workdata;
  v6 = workdata;
  if (workdata)
  {
    evtFreeWorkData1(v6);
    evtFreeWorkData2and3(p_workdata);
    p_workdata = 0;
  }
  dds3PadActAllStop();
}

// 0x1a15500
void evtUnRegistUnit(evtViewerInfo_t *pInfo) {
  pmdProcessWork_t *workdata;
  pmdPM1_t *pm1;
  s64 v5;
  pmdUnitTable_t *v6;
  u16 MajorNum;
  s32 MinorNum;

  workdata = pInfo->workdata;
  if (workdata)
  {
    pm1 = workdata->pm1;
    if (pm1->UnitCount >= 1)
    {
      v5 = 0;
      do
      {
        v6 = pm1->UnitTable[v5];
        MajorNum = v6->MajorNum;
        MinorNum = v6->MinorNum;
        mdlUnRegist(MajorNum, MinorNum);
        ++v5;
        pm1 = pInfo->workdata->pm1;
      }
      while (v5 < pm1->UnitCount);
    }
  }
}

// 0x1a155d0
static s32 SearchNameTable(char *name, evtViewerInfo_t *pInfo) {
  s64 v5;

  if (pInfo->nametablecnt < 1)
    return -1;
  v5 = 0;
  while (!Equals_54828848(name, pInfo->nametable[v5]->Name, 4, 0))
  {
    if (++v5 >= pInfo->nametablecnt)
      return -1;
  }
  return v5;
}

// 0x1a14970
s32 evtAddNameTable(char *name, evtViewerInfo_t *pInfo) {
  s64 v6;
  pmdNameTable_t *nametable;
  Il2CppClass **v8;
  pmdNameTable_t *v9;
  pmdNameTable_t *v10;
  pmdNameTable_t *v11;
  pmdNameTable_t *v12;
  s64 v13;
  Il2CppClass **v15;
  pmdNameTable_t *v16;

  LODWORD(v6) = pInfo->nametablecnt;
  if ((s32)v6 < 1)
  {
LABEL_11:
    nametable = pInfo->nametable;
    v8 = &nametable->obj.klass + (s32)v6;
    v11 = v8[4];
    v10 = (v8 + 4);
    v9 = v11;
    if (!v11)
      goto LABEL_12;
    goto LABEL_15;
  }
  v6 = 0;
  while (!Equals_54828848(name, pInfo->nametable[v6]->Name, 4, 0))
  {
    if (++v6 >= pInfo->nametablecnt)
    {
      LODWORD(v6) = pInfo->nametablecnt;
      goto LABEL_11;
    }
  }
  if ((v6 & 0x80000000) != 0)
  {
    LODWORD(v6) = pInfo->nametablecnt;
    nametable = pInfo->nametable;
    v15 = &nametable->obj.klass + (s32)v6;
    v16 = v15[4];
    v10 = (v15 + 4);
    v9 = v16;
    if (!v16)
    {
LABEL_12:
      v12 = Allocate(pmdNameTable_t);
      _ctor(v12, 0);
      v10 = v12;
      v13 = (s32)v6;
      v9 = pInfo->nametable[v13];
    }
LABEL_15:
    v9->Name = name;
    ++pInfo->nametablecnt;
  }
  return v6;
}

// 0x1a15680
static dds3Basic_t *SearchBasicFromNameIndex(s32 nameindex, evtViewerInfo_t *pInfo) {
  dds3Basic_t *ActiveScene;
  char *Name;

  if (nameindex < 0)
    return 0;
  ActiveScene = dds3GetActiveScene();
  Name = pInfo->nametable[nameindex]->Name;
  return dds3SceneBasicSearchNameAndType(ActiveScene, 7u, Name);
}

// 0x1a15750
static void LinkEffectBasic(dds3Basic_t *eff, s32 nameindex, s32 posindex, s32 baseframe, evtViewerInfo_t *pInfo) {
  s32 nowframe;
  dds3Basic_t *ActiveScene;
  pmdNameTable_t *nametable;
  char *Name;
  dds3Basic_t *v15;
  dds3Basic_t *v16;
  u32 v17;
  dds3Basic_t *v19;
  s32 stat;
  dds3Basic_t *target;
  dds3Basic_t *scene;
  dds3Basic_t *basic;

  basic = eff;
  if (eff && (nameindex & 0x80000000) == 0)
  {
    nowframe = pInfo->nowframe;
    ActiveScene = dds3GetActiveScene();
    nametable = pInfo->nametable;
    scene = ActiveScene;
    Name = nametable[nameindex]->Name;
    v15 = dds3SceneBasicSearchName(scene, Name);
    target = v15;
    if (v15)
    {
      v16 = v15;
      v17 = GETBASICTYPEL(v15);
      if (v17 <= 0x10)
      {
        if (((1 << v17) & 0x103D0) != 0)
        {
LABEL_14:
          dds3EffectObjectBasicLinkObject(basic, target);
          return;
        }
        if (v17 == 5)
        {
          if (posindex < 0)
          {
            goto LABEL_14;
          }
          dds3EffectObjectBasicLinkObjectIndex(basic, target, posindex);
        }
        else if (v17 == 15)
        {
          evtPathLinkAndMake(v16, eff);
          v19 = dds3GetBaseControlWorkData(basic)->pBasic[1];
          stat = pInfo->stat;
          evtStopMover(v19, (stat & 1) == 0, baseframe, nowframe);
        }
      }
    }
  }
}

// 0x1a159a0
static s32 AddEffectTable2(s32 nowframe, evtViewerObject_t *obj, evtFrameInfo_t *f, evtViewerInfo_t *pInfo) {
  dds3Basic_t *efftable;
  s64 v9;
  s32 v10;
  dds3Basic_t *v11;
  s32 type;
  Il2CppObject *v13;
  f32 *v15;
  f32 v16;
  f32 v17;
  f32 v18;
  f32 v19;
  f32 v20;
  f32 v21;
  f32 v22;
  f32 v23;
  Il2CppObject *p;
  s64 naturalAligment;
  void *v26;
  f32 *p_file_major;
  f32 v29;
  f32 v30;
  f32 v31;
  f32 v32;
  f32 v33;
  f32 v34;
  f32 v35;
  f32 v36;
  dds3Basic_t *v37;
  dds3Basic_t *v38;
  dds3Basic_t *v39;
  s64 v40;
  pmdObjectTable_t *object_data;
  s32 union0;
  s16 Item;
  s8 v45;
  s32 frame;
  Il2CppClass **v47;
  dds3Basic_t *basic;
  sdfVector4_t v51;
  sdfVector4_t v52;
  sdfVector4_t v53;
  sdfVector4_t v54;

  efftable = pInfo->efftable;
  v9 = 0;
  basic = 0;
  v10 = -1;
  v11 = &efftable[1];
  if (*(v11 - 1))
  {
    while (1)
    {
      if ((u32)v9 == 126)
        return v10;
      if (!v11)
        break;
      v9 += 2;
      v11 += 2;
      if (!*(v11 - 1))
        goto LABEL_7;
    }
    v10 = ++v9;
    type = obj->type;
    if (type != 3)
    {
LABEL_14:
      if (type != 26)
      {
        v38 = pInfo->efftable;
        v39 = 0;
        goto LABEL_37;
      }
      p = obj->data->p;
      {
        v26 = *((void *)p[1].monitor + 4);
        p_file_major = &file_major;
        v29 = p_file_major[33];
        v30 = p_file_major[34];
        v31 = p_file_major[35];
        v32 = p_file_major[36];
        v33 = p_file_major[37];
        v34 = p_file_major[38];
        v36 = p_file_major[39];
        v35 = p_file_major[40];
        v51.x = v29;
        v51.y = v30;
        v51.z = v31;
        v51.w = v32;
        v53.x = v33;
        v53.y = v34;
        v53.z = v36;
        v53.w = v35;
        v37 = dds3EffectObjectBasicAddEPL(v26, v51, v53);
        goto LABEL_28;
      }
LABEL_43:
    }
  }
  else
  {
LABEL_7:
    v10 = v9;
    type = obj->type;
    if (type != 3)
      goto LABEL_14;
  }
  v13 = obj->data->p;
  v15 = &file_major;
  v16 = v15[33];
  v17 = v15[34];
  v18 = v15[35];
  v19 = v15[36];
  v20 = v15[37];
  v21 = v15[38];
  v23 = v15[39];
  v22 = v15[40];
  if (v13)
  {
    if (v13->klass->_2.naturalAligment < (u32)v40 || v13->klass->_2.typeHierarchy[v40 - 1] != Project_libsdf_sdfResourcePack)
    {
      p = v13;
      goto LABEL_43;
    }
  }
  v52.x = v16;
  v52.y = v17;
  v52.z = v18;
  v52.w = v19;
  v54.x = v20;
  v54.y = v21;
  v54.z = v23;
  v54.w = v22;
  v37 = dds3EffectObjectBasicAddD3P2(v13, v52, v54);
LABEL_28:
  object_data = obj->object_data;
  basic = v37;
  v39 = v37;
  union0 = (u8)object_data->union0;
  Item = get_Item(f->data[1]->s, 1, 0);
  v45 = get_Item(f->data[1]->c, 1, 0);
  if (union0)
  {
    LinkEffectBasic(v39, Item, v45, 0, pInfo);
    v38 = pInfo->efftable;
    if (!v39)
      goto LABEL_37;
  }
  else
  {
    frame = f->frame;
    LinkEffectBasic(v39, Item, v45, frame, pInfo);
    v38 = pInfo->efftable;
    if (!v39)
      goto LABEL_37;
  }
LABEL_37:
  v47 = &v38->obj.klass + v9;
  v47[4] = v39;
  if (basic)
  {
    dds3EffectObjectBasicStatOn(basic, 1u);
  }
  return v10;
}

// 0x1a15d70
static dds3ModelHandle_t *GetModelHandleFromUID(s32 UID, dds3Basic_t *unit) {
  void *workdata;
  s64 naturalAligment;
  dds3Basic_t *next;
  s64 v9;
  dds3ModelHandle_t *v10;

  workdata = dds3GetActiveScene()->workdata;
  if (!workdata)
    goto LABEL_9;
  if (workdata->klass->_2.naturalAligment < (u32)naturalAligment || workdata->klass->_2.typeHierarchy[naturalAligment - 1] != dds3SceneBasic_t)
  {
LABEL_20:
  }
LABEL_9:
  next = *(dds3Basic_t *)(*((u64 *)workdata[1].monitor + 9) + 24);
  if (!next)
    return 0;
  while (1)
  {
    workdata = next->workdata;
    if (workdata)
    {
      if (workdata->klass->_2.naturalAligment < (u32)v9 || workdata->klass->_2.typeHierarchy[v9 - 1] != Project_Basic_dds3UnitObjectBasicWorkData_t)
      {
        goto LABEL_20;
      }
    }
    v10 = *((dds3ModelHandle_t *)workdata[2].monitor + 5);
    if (sdfModelGetUniqueID(v10->modelRoot) == UID)
      break;
    next = next->next;
    if (!next)
      return 0;
  }
  unit = next;
  return v10;
}

// 0x1a15f50
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

// 0x1a16010
static bool DrawTmxTextureFrom2Frame(evtViewerInfo_t *pInfo, evtViewerObject_t *obj, evtFrameInfo_t *nearframe, evtFrameInfo_t *frame) {
  s32 v9;
  f32 v10;
  s32 v11;
  bool v12;
  s32 type;
  void *hTex;
  pmdTmxData_t *v15;
  void *p_mesh;
  sdfIVector2_t maskofs;
  s32 EventNo;
  u32 v20;
  void *Tex;
  pmdTmxData_t *v22;
  void *v24;
  sdfIVector2_t v25;
  void *MaskTex;
  pmdTmxData_t *v28;
  sdfIVector2_t v29;
  pmdTmxData_t *out_tmxdata;

  out_tmxdata = 0;
  if (nearframe && frame)
  {
    v9 = nearframe->frame;
    v10 = 0.0;
    v11 = frame->frame - v9;
    if (v11)
      v10 = (f32)(pInfo->nowframe - v9 - obj->object_data->Offset) / (f32)v11;
  }
  else
  {
    v12 = 0;
    if (!nearframe)
      return v12;
    v10 = 0.0;
    if (frame)
      return v12;
  }
  evtHokanTmx(v10, nearframe, frame, out_tmxdata);
  type = obj->type;
  if (type != 36)
  {
    if (type != 24)
      return 0;
    hTex = obj->hTex;
    v15 = out_tmxdata;
    p_mesh = &obj->mesh;
    maskofs = _maskofs;
    evtDrawTexture(hTex, v15, 0, maskofs, p_mesh);
    return 0;
  }
  EventNo = pInfo->workdata->EventNo;
  v20 = get_Item(nearframe->data[0]->s, 1, 0)
      | (EventNo << 16);
  Tex = evtGetTex(v20);
  if (!op_Inequality(Tex, 0, 0))
  {
    Disp(pInfo->workdata->loadScene[0], 1, 0);
    return 0;
  }
  v12 = 0;
  if (get_Item(nearframe->data[5]->c, 0, 0) <= 2)
  {
    v22 = out_tmxdata;
    v24 = &obj->mesh;
    v25 = _maskofs;
    evtDrawTexture(Tex, v22, 0, v25, v24);
    MaskTex = evtGetMaskTex(v20);
    evtGetMaskOfs(v20, &_maskofs);
    if (op_Inequality(MaskTex, 0, 0))
    {
      v28 = out_tmxdata;
      v29 = _maskofs;
      v12 = 1;
      evtDrawTexture(MaskTex, v28, 1, v29, v24);
    }
    else
    {
      return 1;
    }
  }
  return v12;
}

// 0x1a16370
static void DrawTmxTexture(evtViewerInfo_t *pInfo) {
  evtViewerObject_t *firstobjinfo;
  bool v5;
  s32 nowframe;
  s32 type;
  evtFrameInfo_t *firstframeinfo;
  evtFrameInfo_t *lastframeinfo;

  firstobjinfo = pInfo->firstobjinfo;
  if (firstobjinfo)
  {
    v5 = 0;
    nowframe = pInfo->nowframe;
    while (1)
    {
      type = firstobjinfo->type;
      if (type != 36 && type != 24)
        goto LABEL_6;
      firstframeinfo = firstobjinfo->firstframeinfo;
      if (firstframeinfo)
        break;
LABEL_15:
      firstframeinfo = 0;
      lastframeinfo = firstobjinfo->lastframeinfo;
LABEL_5:
      v5 = DrawTmxTextureFrom2Frame(pInfo, firstobjinfo, lastframeinfo, firstframeinfo);
LABEL_6:
      firstobjinfo = firstobjinfo->next;
      if (!firstobjinfo)
        goto LABEL_20;
    }
    while (firstobjinfo->object_data->Offset + firstframeinfo->frame <= nowframe)
    {
      firstframeinfo = firstframeinfo->next;
      if (!firstframeinfo)
        goto LABEL_15;
    }
    lastframeinfo = firstframeinfo->prev;
    goto LABEL_5;
  }
  v5 = 0;
LABEL_20:
  Set(v5);
}

// 0x1a16470
static void DrawEffect(evtViewerInfo_t *pInfo) {
  void (*methodPtr)(void);
  evtViewerInfo_t *v19;

  if (pInfo->drawblur2)
  {
    dds3EffectExecute(effEvent_Edit_Blur);
    goto LABEL_9;
  }
LABEL_9:
  if (pInfo->drawmblur)
  {
    (PartialMultiBlur->klass->vtable._4_ON.methodPtr)(PartialMultiBlur, PartialMultiBlur->klass->vtable._4_ON.method);
    if (pInfo->drawmfilter)
      goto LABEL_13;
  }
  else
  {
    (PartialMultiBlur->klass->vtable._5_OFF.methodPtr)(PartialMultiBlur, PartialMultiBlur->klass->vtable._5_OFF.method);
    if (pInfo->drawmfilter)
    {
LABEL_13:
      (PartialMultiFilter->klass->vtable._4_ON.methodPtr)(PartialMultiFilter, PartialMultiFilter->klass->vtable._4_ON.method);
      if (pInfo->drawdblur)
        goto LABEL_16;
      goto LABEL_31;
    }
  }
  (PartialMultiFilter->klass->vtable._5_OFF.methodPtr)(PartialMultiFilter, PartialMultiFilter->klass->vtable._5_OFF.method);
  if (pInfo->drawdblur)
  {
LABEL_16:
    (DistortionBlur->klass->vtable._4_ON.methodPtr)(DistortionBlur, DistortionBlur->klass->vtable._4_ON.method);
    if (pInfo->drawrblur)
      goto LABEL_19;
LABEL_34:
    (RippleBlur->klass->vtable._5_OFF.methodPtr)(RippleBlur, RippleBlur->klass->vtable._5_OFF.method);
    if (pInfo->drawhblur)
      goto LABEL_22;
    goto LABEL_37;
  }
LABEL_31:
  (DistortionBlur->klass->vtable._5_OFF.methodPtr)(DistortionBlur, DistortionBlur->klass->vtable._5_OFF.method);
  if (!pInfo->drawrblur)
    goto LABEL_34;
LABEL_19:
  (RippleBlur->klass->vtable._4_ON.methodPtr)(RippleBlur, RippleBlur->klass->vtable._4_ON.method);
  if (pInfo->drawhblur)
  {
LABEL_22:
    methodPtr = ParallelBlur->klass->vtable._4_ON.methodPtr;
    goto LABEL_40;
  }
LABEL_37:
  methodPtr = ParallelBlur->klass->vtable._5_OFF.methodPtr;
LABEL_40:
  methodPtr();
  if (!pInfo->drawfilter)
  {
    (Filter->klass->vtable._5_OFF.methodPtr)(Filter, Filter->klass->vtable._5_OFF.method);
    goto LABEL_44;
  }
  (Filter->klass->vtable._4_ON.methodPtr)(Filter, Filter->klass->vtable._4_ON.method);
LABEL_44:
  v19 = pInfo;
  DrawTmxTexture(v19);
}

// 0x1a167a0
static void SetActiveCamera(evtViewerInfo_t *pInfo) {
  dds3Basic_t *activecamera;
  dds3Basic_t *ActiveScene;
  f32 Fovy;
  dds3Basic_t *pBasic;

  activecamera = pInfo->activecamera;
  pBasic = activecamera;
  if (activecamera || (activecamera = pInfo->gamecamera, (pBasic = activecamera) != 0))
  {
    ActiveScene = dds3GetActiveScene();
    SetActiveCamera(ActiveScene, activecamera, 0);
    Fovy = dds3CameraObjectBasicGetFovy(pBasic);
    dds3SetScreenFovy(Fovy);
  }
}

// 0x1a168c0
static void ReqMessage(evtViewerObject_t *obj, evtFrameInfo_t *frame, s32 nowframe, s32 length, evtViewerInfo_t *pInfo) {
  pmdProcessWork_t *workdata;
  pmdProcessWork_t *v10;
  s32 v11;
  u32 Item;
  s32 v13;
  s32 MesHandle;
  s32 v15;
  s32 v16;
  s32 v18;
  s32 v19;
  s16 v21;
  s8 v22;
  s32 v23;
  s32 v24;
  s32 pMesType;
  s32 pMesNo;

  workdata = pInfo->workdata;
  pMesNo = 0;
  pMesType = 0;
  if (workdata->MesHandle != -1)
  {
    if ((pInfo->stat & 0x10) != 0)
      return;
    evtGetMessageDataAndTypeFromFrame(frame, &pMesNo, &pMesType);
    pInfo->last_mestype = pMesType;
    if (frame->frame == nowframe)
    {
      v10 = pInfo->workdata;
      if (v10->EventNo == 651)
      {
        v11 = pMesNo;
        if (v10->CutNo == 1 && v10->now_mesno == pMesNo + 1)
          return;
      }
      else
      {
        v11 = pMesNo;
      }
      v10->now_mesno = v11 + 1;
      Item = (u8)get_Item(frame->data[1]->c, 0, 0);
      if (Item < 2)
      {
        MesHandle = pInfo->workdata->MesHandle;
        itfMesMngMarkBitStat(MesHandle, 0x200000u);
        itfMesMngClearBitStat(pInfo->workdata->MesHandle, 0xD00000u);
      }
      else if (Item == 2)
      {
        v13 = pInfo->workdata->MesHandle;
        itfMesMngMarkBitStat(v13, 0x200000u);
        itfMesMngMarkBitStat(pInfo->workdata->MesHandle, 0xD00000u);
      }
      pInfo->stat |= 0x100u;
      pInfo->last_meswin_mode = get_Item(frame->data[1]->c, 0, 0);
      v15 = pInfo->workdata->MesHandle;
      v16 = pMesNo;
      if (itfGetMessageType(v15, pMesNo))
      {
        v18 = pMesNo;
        pInfo->branch->var_idx = pMesType + 199;
        v19 = pInfo->workdata->MesHandle;
        itfMesMngRequestSelect(v19, v18);
        return;
      }
      v21 = get_Item(frame->data[0]->s, 1, 0);
      if (evtCompareCutResultValue(v21))
      {
        sndVoiceStatus(0);
        v22 = get_Item(frame->data[2]->c, 0, 0);
        if (v22 != 88)
          goto LABEL_39;
        if (cfgGetConfigGAME(8, 0))
        {
LABEL_39:
          v23 = pMesNo;
          v24 = pInfo->workdata->MesHandle;
          itfMesMngRequestMessage(v24, v23, 0, 0, v22 == 88);
        }
      }
    }
  }
}

// 0x1a16ca0
static void RunFrame1(evtViewerObject_t *obj, evtFrameInfo_t *frame, s32 nowframe, s32 length, evtViewerInfo_t *pInfo) {
  s32 type;
  DataC *c;
  s8 v15;
  u16 Item;
  s32 v18;
  s16 v19;
  u16 v20;
  s16 v21;
  u8 v22;
  u32 v23;
  s32 nowMovieStat;
  s8 v25;
  s8 v26;
  s16 v27;
  s32 v28;
  s32 v29;
  bool v30;
  s16 v32;
  s32 *v33;
  s16 v36;
  s16 v37;
  s32 v38;
  s16 v39;
  s8 v40;
  s8 v41;
  s16 v42;
  dds3ProcessID_t *v44;
  s8 v45;
  dds3ProcessID_t *v47;
  s32 v48;
  s32 i;
  s32 v50;
  s32 v51;
  s32 v52;
  s32 v53;
  s32 v54;
  s32 v55;
  s8 v56;
  s32 v58;
  pmdLoadScene *loadScene;
  void *model;
  s32 v61;
  s32 v62;
  s32 v63;
  char *v67;
  char *v68;
  char *v69;
  char *v70;
  char *v71;
  char *v72;
  char *v73;
  char *v75;
  char *v76;
  s32 v77;
  s32 v78;
  s16 v80;
  s32 v81;
  s32 v82;
  s32 v84;
  s32 v85;
  s8 v86;
  s32 At3BgmReqID;
  s32 At3BGMStartTime;
  s16 v92;
  pmdDataInfo_t *data;
  s32 v94;
  s16 v95;
  s32 v97;
  s16 v98;
  s16 v99;
  s32 v100;
  s32 v101;
  s32 v102;
  s16 v103;
  s32 v104;
  s32 v105;
  s32 v107;
  s16 v108;
  s32 v110;
  s16 v111;
  s32 v113;
  s16 v114;
  s32 v115;

  type = obj->type;
  v115 = 0;
  switch (type)
  {
    case 3:
    case 26:
      if (frame->frame <= nowframe && get_Item(frame->data[0]->c, 0, 0) < 0)
      {
        c = frame->data[0]->c;
        v15 = AddEffectTable2((s32)evtViewer, obj, frame, pInfo);
        set_Item(c, 0, v15, 0);
      }
      return;
    case 4:
      if (!drawEnd)
        return;
      if (get_Item(frame->data[2]->c, 1, 0) != 99)
        goto LABEL_128;
      if (sndVoiceStatus(0))
        goto LABEL_221;
      if (IsNextMesSet())
      {
LABEL_221:
        AddNextMesSet(obj, frame, nowframe, length, pInfo);
      }
      else
      {
LABEL_128:
        ReqMessage(evtViewer, frame, nowframe, v63, pInfo);
      }
      return;
    case 5:
      if ((pInfo->stat & 0x10) != 0)
        return;
      Item = get_Item(frame->data[0]->s, 1, 0);
      if (Item >= 0x1000u)
      {
        v77 = Item & 0xFFF;
        v78 = Item >> 12;
        if (GBWK->IntVariable[v78 + 199] != v77)
          return;
      }
      if (get_Item(frame->data[1]->c, 0, 0))
      {
        v80 = get_Item(frame->data[0]->s, 0, 0);
        sndSeLoadId(v80);
      }
      else
      {
        v92 = get_Item(frame->data[0]->s, 0, 0);
        evtPlaySe(file_major, v92);
        data = frame->data;
        v94 = 0;
LABEL_171:
        v95 = get_Item(data[0]->s, v94, 0);
        evtEventRegistBGM(pInfo, v95);
      }
      return;
    case 7:
      if (frame->length || get_Item(frame->data[0]->s, 0, 0))
      {
        if (frame->frame == nowframe)
        {
          pInfo->stat |= 2u;
          v18 = frame->length;
          v19 = get_Item(frame->data[0]->s, 0, 0);
          dds3SetQuake(v18, v19);
        }
      }
      else
      {
        pInfo->stat &= ~2u;
        dds3StopQuake();
      }
      return;
    case 19:
      if ((pInfo->stat & 0x10) != 0)
        return;
      v20 = get_Item(frame->data[1]->s, 0, 0);
      if (v20 < 0x1000u)
        goto LABEL_153;
      goto LABEL_150;
      if (v20 < 0x1000u)
      {
LABEL_153:
        v84 = (u8)get_Item(frame->data[1]->c, 2, 0);
        v85 = get_Item(frame->data[0]->s, 0, 0);
        if (!v84)
        {
          switch (v85)
          {
            case 0:
              v97 = file_major;
              v98 = get_Item(frame->data[0]->s, 1, 0);
              evtPlayBgm(v97, v98);
              goto LABEL_203;
            case 1:
              v107 = file_major;
              v108 = get_Item(frame->data[0]->s, 1, 0);
              evtFadeInBgm(v107, v108);
LABEL_203:
              data = frame->data;
              v94 = 1;
              goto LABEL_171;
            case 2:
              v110 = file_major;
              v111 = get_Item(frame->data[0]->s, 1, 0);
              evtFadeOutBgm(v110, v111);
              return;
            case 3:
              v113 = file_major;
              v114 = get_Item(frame->data[0]->s, 1, 0);
              evtTransBgm(v113, v114);
              return;
            case 4:
              p2sdBGMVolHalfDown();
              return;
            case 5:
              p2sdBGMVolHalfUp();
              return;
            case 6:
              p2sdBGMStopAll();
              return;
            default:
              return;
          }
        }
        switch (v85)
        {
          case 0:
            pInfo->At3BgmFlag |= 1u;
            pInfo->At3BgmReqID = get_Item(frame->data[0]->s, 1, 0);
            pInfo->At3BGMStartTime = get_Item(frame->data[2]->c, 0, 0);
            v86 = get_Item(frame->data[2]->c, 1, 0);
            pInfo->At3BGMPlaySkip = v86;
            if (v86 != 1)
              goto LABEL_159;
            if (scrGetAfterSkipBgmFlag() == 2)
            {
LABEL_159:
              At3BgmReqID = pInfo->At3BgmReqID;
              At3BGMStartTime = pInfo->At3BGMStartTime;
              sndBgmPlay(At3BgmReqID, 1000 * At3BGMStartTime);
            }
            break;
          case 1:
            pInfo->At3BgmFlag |= 2u;
            pInfo->At3BgmReqID = get_Item(frame->data[0]->s, 1, 0);
            break;
          case 2:
            pInfo->At3BgmFlag = 0;
            sndBgmFadeOut();
            v104 = pInfo->At3BgmReqID;
            p2sdSndStop(v104);
            break;
          case 6:
            v105 = pInfo->At3BgmReqID;
            p2sdSndStop(v105);
            sndBgmStop();
            sndBgmFree();
            pInfo->At3BgmFlag = 0;
            break;
          default:
            return;
        }
        return;
      }
LABEL_150:
      v81 = v20 & 0xFFF;
      v82 = v20 >> 12;
      if (GBWK->IntVariable[v82 + 199] == v81)
        goto LABEL_153;
      return;
    case 28:
      if (obj->object_data->Offset + frame->frame == nowframe)
      {
        v21 = get_Item(frame->data[0]->s, 0, 0);
        v22 = get_Item(frame->data[0]->s, 1, 0);
        v23 = frame->length;
        dds3PadAct(v21, v22, v23);
      }
      return;
    case 29:
      if ((pInfo->stat & 0x10) == 0 && frame->frame == nowframe)
      {
        if (!get_Item(frame->data[1]->c, 1, 0))
        {
          p2sdBGMStopAll();
        }
        nowMovieStat = pInfo->nowMovieStat;
        v25 = get_Item(frame->data[1]->c, 1, 0);
        if (nowMovieStat)
        {
          movieStop(v25);
          v26 = get_Item(frame->data[1]->c, 1, 0);
          movieNoMemoryAlloc();
          v27 = get_Item(frame->data[0]->s, 0, 0);
          moviePlay(v27, 0, v26 == 0);
          v28 = frame->frame;
          pInfo->nowMovieStat = 1;
          pInfo->MovieStartFrame = v28;
          if (frame->length)
            v29 = frame->length + v28;
          else
            v29 = -1;
          pInfo->MovieEndFrame = v29;
          pInfo->real_movie_last_frame = 0;
        }
        else
        {
          movieNoMemoryAlloc();
          v99 = get_Item(frame->data[0]->s, 0, 0);
          moviePlay(v99, 0, v25 == 0);
          v100 = frame->frame;
          pInfo->nowMovieStat = 1;
          pInfo->MovieStartFrame = v100;
          v101 = frame->length + v100;
          if (frame->length)
            v102 = v101;
          else
            v102 = -1;
          pInfo->MovieEndFrame = v102;
          v103 = get_Item(frame->data[0]->s, 0, 0);
          sBtlSelectStart(v103);
          pInfo->real_movie_last_frame = 0;
        }
      }
      return;
    case 32:
      if (frame->frame == nowframe)
      {
        v30 = get_Item(frame->data[0]->s, 0, 0) == 0;
        if (v30)
        {
          dds3ChangeBistaMode(1);
          dds3BistaIn(frame->length);
        }
        else
        {
          dds3ChangeBistaMode(1);
          dds3BistaOut(frame->length);
        }
      }
      return;
    case 33:
      v32 = get_Item(frame->data[0]->s, 1, 0);
      if (!evtChkUID(v32) && get_Item(frame->data[0]->s, 1, 0) >= 1)
      {
        v33 = NewSpecific(s32, 1u);
        v33[0] = pInfo->nowframe;
        v36 = get_Item(frame->data[1]->s, 0, 0);
        v37 = get_Item(frame->data[1]->s, 1, 0);
        v38 = frame->frame;
        v39 = get_Item(frame->data[0]->s, 0, 0);
        v40 = get_Item(frame->data[2]->c, 0, 0);
        v41 = get_Item(frame->data[2]->c, 1, 0);
        v42 = get_Item(frame->data[0]->s, 1, 0);
        evtStart(v33, pmv_pid, 16 * v36, 8 * v37, 0, v38, v39, (v41 + 1) | ((v40 << 16) + 0x10000), v42);
      }
      return;
    case 34:
      if ((pInfo->stat & 1) == 0)
      {
        v44 = pmv_pid;
        v45 = get_Item(frame->data[0]->c, 0, 0);
        evtStartScreenBreak(v44, 0, v45);
      }
      return;
    case 35:
      if ((pInfo->stat & 1) == 0)
      {
        v47 = pmv_pid;
        v48 = frame->length;
        evtStartCrossFade(v47, 0, v48);
      }
      return;
    case 37:
      ReceiptInit();
      i = get_i(frame->data[0], 0);
      ReceiptSet(i);
      v50 = get_i(frame->data[1], 0);
      ReceiptSet(v50);
      v51 = get_i(frame->data[2], 0);
      ReceiptSet(v51);
      v52 = get_i(frame->data[3], 0);
      ReceiptSet(v52);
      v53 = get_i(frame->data[4], 0);
      ReceiptSet(v53);
      v54 = get_i(frame->data[5], 0);
      ReceiptSet(v54);
      v55 = get_i(frame->data[6], 0);
      ReceiptSet(v55);
      v56 = get_Item(frame->data[7]->c, 0, 0);
      ReceiptStart(v56);
      return;
    case 38:
      if (!drawEnd)
        return;
      v67 = NewSpecific(string, 6u);
      v68 = "E";
      v67[0] = "E";
      v69 = ToString_55996800((u32)pInfo->workdata + 20, "d3", 0);
      v67[1] = v69;
      v70 = "_";
      v67[2] = "_";
      v71 = ToString_55996800((u32)pInfo->workdata + 24, "d3", 0);
      v67[3] = v71;
      v72 = "_L";
      v67[4] = "_L";
      v115 = get_i(frame->data[0], 0);
      v73 = ToString_55996800((s32)&v115, "d4", 0);
      v67[5] = v73;
      v75 = Concat_54832608(v67, 0);
      v76 = ChgVoiceLabel(v75);
      sndVoicePlayFile(v76, 0);
      return;
    case 39:
      v58 = get_i(frame->data[0], 0);
      if (v58 != 14)
        goto LABEL_222;
      if (cfgGetConfigGAME(1, 0) == 4)
      {
LABEL_222:
        Unlock(v58);
      }
      return;
    case 40:
      evtMessageDelete(pInfo, 1);
      return;
    case 41:
      loadScene = pInfo->workdata->loadScene;
      model = loadScene[get_i(frame->data[0], 0)]->model;
      v61 = get_i(frame->data[1], 0);
      SetParts(model, v61, 0);
      return;
    case 43:
      v62 = get_i(frame->data[0], 0);
      SE(v62);
      return;
    default:
      return;
  }
}

// 0x1a18350
static bool IsNextMesSet(void) {
  return nmesw_top != 0;
}

// 0x1a183c0
static void AddNextMesSet(evtViewerObject_t *obj, evtFrameInfo_t *frame, s32 nowframe, s32 length, evtViewerInfo_t *pInfo) {
  NMESW *v11;
  NMESW *nmesw_top_local;
  NMESW *v15;
  NMESW *p_nmesw_top;

  v11 = Allocate(NMESW);
  _ctor(v11, 0);
  v11->obj = obj;
  v11->frame = frame;
  v11->nowframe = nowframe;
  v11->length = length;
  v11->pInfo = pInfo;
  v11->next = 0;
  nmesw_top_local = nmesw_top;
  if (nmesw_top_local)
    goto LABEL_5;
  nmesw_top = v11;
  p_nmesw_top = &nmesw_top;
LABEL_12:
  return;
LABEL_5:
  while (1)
  {
    v15 = nmesw_top_local;
    if (nmesw_top_local->frame->frame == frame->frame)
      break;
    nmesw_top_local = nmesw_top_local->next;
    if (!nmesw_top_local)
    {
      v15->next = v11;
      p_nmesw_top = &v15->next;
      goto LABEL_12;
    }
  }
}

// 0x1a187e0
static void CalcNextMesSet(void) {
  s32 v2;
  evtFrameInfo_t *frame;
  s32 nowframe;
  evtViewerInfo_t *pInfo;
  NMESW *next;

  if (sndVoiceStatus(0))
    return;
  if (!nmesw_top)
    return;
  frame = nmesw_top->frame;
  nowframe = nmesw_top->nowframe;
  pInfo = nmesw_top->pInfo;
  ReqMessage(evtViewer, frame, nowframe, v2, pInfo);
  next = nmesw_top->next;
  nmesw_top = next;
}

// 0x1a18900
static void InFrame1(evtViewerObject_t *obj, evtFrameInfo_t *frame, s32 nowframe, s32 length, evtViewerInfo_t *pInfo) {
  u32 type;
  bool v10;
  s32 v11;
  s32 v13;
  u32 v14;
  dds3Basic_t *efftable;
  void *workdata;
  effHandle_t *klass;
  f32 v20;
  u32 v21;

  type = obj->type;
  v10 = type > 0x1A;
  v11 = (1 << type) & 0x4300008;
  if (!v10 && v11 != 0 && (get_Item(frame->data[0]->c, 0, 0) & 0x80) == 0)
  {
    if (get_Item(frame->data[2]->c, 0, 0))
    {
      v13 = pInfo->nowframe - frame->frame;
      v14 = frame->length;
      if (v13 <= (s32)v14)
      {
        efftable = pInfo->efftable;
        workdata = efftable[get_Item(frame->data[0]->c, 0, 0)]->workdata;
        klass = workdata[2].klass;
        if (!klass)
          goto LABEL_20;
        goto LABEL_9000;
        if (!klass)
        {
LABEL_20:
          v20 = (f32)(128.0 / (f32)v14) * (f32)v13;
          if (v20 == INFINITY)
            v21 = 8421504;
          else
            v21 = ((s32)v20 << 24) | 0x808080;
          dds3EffectSetRGBA(klass, v21);
          return;
        }
LABEL_9000:
        goto LABEL_20;
      }
    }
  }
}

// 0x1a18b00
static void VisibleFrame1(evtViewerObject_t *obj, evtFrameInfo_t *frame, s32 nowframe, evtViewerInfo_t *pInfo) {
  s32 type;
  dds3Basic_t *efftable;
  void **p_klass;
  effHandle_t *v13;
  s32 v15;
  u32 v16;

  if (get_Item(frame->data[3]->s, 1, 0))
  {
    if (frame->frame)
    {
      type = obj->type;
      if (type == 26 || type == 3)
      {
        efftable = pInfo->efftable;
        p_klass = &efftable[get_Item(frame->data[0]->c, 0, 0)]->workdata->klass;
        v13 = p_klass[4];
        v15 = frame->frame;
        if (v15 + get_Item(frame->data[3]->s, 1, 0) > nowframe)
        {
          v16 = 8421504;
LABEL_16:
          dds3EffectSetRGBA(v13, v16);
          return;
        }
        if (frame->frame < nowframe)
        {
          v16 = 1350598784;
          set_Item(frame->data[3]->s, 1, 0, 0);
          goto LABEL_16;
        }
      }
    }
  }
}

// 0x1a18d10
static void ValidatePLTMX(evtViewerInfo_t *pInfo) {
  evtViewerObject_t *firstobjinfo;
  evtFrameInfo_t *lastframeinfo;
  s32 v5;
  s32 v6;
  s32 Item;
  s32 EventNo;
  s16 v9;

  firstobjinfo = pInfo->firstobjinfo;
  if (firstobjinfo)
  {
    while (firstobjinfo->type != 36)
    {
      firstobjinfo = firstobjinfo->next;
      if (!firstobjinfo)
        return;
    }
    lastframeinfo = firstobjinfo->lastframeinfo;
    if (lastframeinfo)
    {
      while (pInfo->nowframe < lastframeinfo->frame)
      {
        lastframeinfo = lastframeinfo->prev;
        if (!lastframeinfo)
          goto LABEL_8;
      }
LABEL_9:
      v5 = 0;
      v6 = -1;
      while (1)
      {
        Item = get_Item(lastframeinfo->data[0]->s, 1, 0);
        if (v6 != Item)
        {
          EventNo = pInfo->workdata->EventNo;
          v9 = get_Item(lastframeinfo->data[0]->s, 1, 0);
          evtRequest(v9 | (EventNo << 16), lastframeinfo->frame);
          if (++v5 > 1)
            return;
          v6 = Item;
        }
        lastframeinfo = lastframeinfo->next;
        if (!lastframeinfo)
          return;
      }
    }
LABEL_8:
    lastframeinfo = firstobjinfo->firstframeinfo;
    if (lastframeinfo)
      goto LABEL_9;
  }
}

// 0x1a18e10
static bool ValidateAt3Bgm(evtViewerInfo_t *pInfo) {
  s32 stat;
  s32 At3BgmFlag;
  s32 At3BgmReqID;
  s32 v8;

  stat = pInfo->stat;
  if ((stat & 0x800) != 0)
    return 0;
  if ((stat & 1) != 0)
  {
    sndBgmStop();
    sndBgmFree();
    goto LABEL_14;
  }
  if (sndSeStatus() == 2)
  {
    sndSePlay(0);
    At3BgmFlag = pInfo->At3BgmFlag;
    if (!At3BgmFlag)
      return 0;
    goto LABEL_17;
  }
  At3BgmFlag = pInfo->At3BgmFlag;
  if (!At3BgmFlag)
    return 0;
LABEL_17:
  if ((At3BgmFlag & 4) != 0)
  {
    if (pInfo->At3Bgm1stLoad && pInfo->nowframe < pInfo->At3Bgm1stFrame)
      return 0;
    if (sndBgmStatus_XF() != 2)
      return 1;
    v8 = pInfo->At3BgmFlag;
    if ((v8 & 1) != 0)
    {
      sndBgmPlay(0, 0);
      v8 = pInfo->At3BgmFlag;
    }
    if ((v8 & 2) != 0)
    {
      sndBgmFadeIn(0, 0);
    }
LABEL_14:
    pInfo->At3BgmFlag = 0;
    pInfo->At3Bgm1stLoad = 0;
    return 0;
  }
  At3BgmReqID = pInfo->At3BgmReqID;
  sndBgmLoadId_XF(At3BgmReqID);
  pInfo->At3BgmFlag |= 4u;
  return 1;
}

// 0x1a18ff0
static bool Validate1stAt3Bgm(evtViewerInfo_t *pInfo) {
  bool result;
  evtViewerObject_t *firstobjinfo;
  evtFrameInfo_t *firstframeinfo;
  s32 Item;
  s16 v8;
  s32 frame;
  s32 v10;

  if ((pInfo->stat & 0x800) != 0)
    return 0;
  if (pInfo->At3BgmFlag)
  {
    if (sndBgmStatus_XF() >= 2)
    {
      result = 0;
      pInfo->At3BgmFlag |= 4u;
      return result;
    }
    return 1;
  }
  firstobjinfo = pInfo->firstobjinfo;
  if (!firstobjinfo)
    return 0;
  while (firstobjinfo->type != 19)
  {
    firstobjinfo = firstobjinfo->next;
    if (!firstobjinfo)
      return 0;
  }
  firstframeinfo = firstobjinfo->firstframeinfo;
  if (!firstframeinfo)
    return 0;
  while (1)
  {
    Item = (u16)get_Item(firstframeinfo->data[0]->s, 0, 0);
    if (!Item)
      break;
    if (Item == 1)
    {
      pInfo->At3BgmFlag |= 2u;
      goto LABEL_25;
    }
LABEL_18:
    firstframeinfo = firstframeinfo->next;
    result = 0;
    if (!firstframeinfo)
      return result;
  }
  if (get_Item(firstframeinfo->data[2]->c, 1, 0) == 1)
    goto LABEL_18;
  pInfo->At3BgmFlag |= 1u;
  sndBgmStop();
  sndBgmFree();
LABEL_25:
  v8 = get_Item(firstframeinfo->data[0]->s, 1, 0);
  frame = firstframeinfo->frame;
  v10 = v8;
  pInfo->At3BgmReqID = v8;
  pInfo->At3Bgm1stFrame = frame;
  pInfo->At3Bgm1stLoad = 1;
  sndBgmLoadId_XF(v10);
  return 1;
}

// 0x1a191f0
static void OutFrame1(evtViewerObject_t *obj, evtFrameInfo_t *frame, s32 nowframe, s32 length, evtViewerInfo_t *pInfo) {
  s32 type;
  s32 v11;
  s32 v12;
  s32 v13;
  s16 Item;
  s16 v15;
  s32 v16;
  s32 v17;
  dds3Basic_t *efftable;
  void *workdata;
  effHandle_t *klass;
  f32 v23;
  u32 v24;
  s64 v25;
  dds3Basic_t *v26;
  Il2CppClass **v27;

  type = obj->type;
  if (type <= 18)
  {
    if (type != 3)
      return;
    goto LABEL_9;
  }
  if ((type & 0xFFFFFFFE) == 0x14)
    return;
  if (type != 33)
  {
    if (type != 26)
      return;
LABEL_9:
    if ((get_Item(frame->data[0]->c, 0, 0) & 0x80) == 0)
    {
      v11 = 0;
      if (get_Item(frame->data[2]->c, 0, 0))
      {
        v12 = pInfo->nowframe;
        v13 = frame->frame;
        if (v12 < v13)
        {
LABEL_32:
          LOBYTE(v25) = get_Item(frame->data[0]->c, 0, 0);
          v26 = pInfo->efftable[(char)v25];
          if (!v26)
            goto LABEL_41;
          goto LABEL_38;
          if (!v26)
          {
LABEL_41:
            set_Item(frame->data[0]->c, 0, 255, 0);
            return;
          }
LABEL_38:
          v25 = (char)v25;
          dds3SceneBasicDelete(v26);
          v27 = &pInfo->efftable->obj.klass + v25;
          v27[4] = 0;
          goto LABEL_41;
        }
      }
      else
      {
        v11 = frame->length;
        v12 = pInfo->nowframe;
        v13 = frame->frame;
        if (v12 < v13)
          goto LABEL_32;
      }
      v16 = v11 + length + v13;
      v17 = v16 - v12;
      if (v16 <= v12)
        goto LABEL_32;
      efftable = pInfo->efftable;
      workdata = efftable[get_Item(frame->data[0]->c, 0, 0)]->workdata;
      klass = workdata[2].klass;
      v23 = (f32)(128.0 / (f32)v11) * (f32)v17;
      if (v23 == INFINITY)
        v24 = 8421504;
      else
        v24 = ((s32)v23 << 24) | 0x808080;
      dds3EffectSetRGBA(klass, v24);
    }
    return;
  }
  Item = get_Item(frame->data[0]->s, 1, 0);
  if (!evtChkUID(Item))
    return;
  v15 = get_Item(obj->firstframeinfo->data[0]->s, 1, 0);
  evtDelProcess(v15);
}

// 0x1a195d0
static void CalcLightCycle(pmdSceneLightTable_t *sl, evtFrameInfo_t *frame, s32 nowframe, evtViewerInfo_t *pInfo) {
  u16 *v8;
  f32 *v9;
  f32 *v10;
  s32 v11;
  s16 Item;
  pmdDataInfo_t *data;
  s16 v14;
  pmdDataInfo_t *v15;
  s16 v16;
  pmdDataInfo_t *v17;
  f32 v18;
  DataC *c;
  f32 v20;
  DataC *v21;
  s8 v22;
  u32 v23;
  sdfVector4_t *Color;
  f32 x;
  f32 v26;
  sdfVector4_t *v27;
  f32 v28;
  f32 v29;
  f32 y;
  sdfVector4_t *v31;
  f32 z;
  f32 v33;
  sdfVector4_t *v34;
  sdfVector4_t *v35;
  f32 v36;
  f32 v37;
  sdfVector4_t *v38;
  f32 v39;
  f32 v40;
  f32 v41;
  sdfVector4_t *v42;
  f32 v43;
  f32 v44;
  sdfVector4_t *v45;
  u32 v46;
  sdfVector4_t *v47;
  f32 v48;
  f32 v49;
  sdfVector4_t *v50;
  f32 v51;
  f32 v52;
  f32 v53;
  sdfVector4_t *v54;
  f32 v55;
  f32 v56;
  sdfVector4_t *v57;

  v8 = NewSpecific(ushort, 3u);
  v9 = NewSpecific(f32, 3u);
  if (frame)
  {
    v10 = v9;
    v11 = nowframe - frame->frame;
    Item = get_Item(frame->data[3]->s, 1, 0);
    data = frame->data;
    v8[16] = Item;
    v14 = get_Item(data[4]->s, 0, 0);
    v15 = frame->data;
    v8[17] = v14;
    v16 = get_Item(v15[4]->s, 1, 0);
    v17 = frame->data;
    v8[18] = v16;
    v18 = (f32)(u32)get_Item(v17[5]->c, 0, 0) / 100.0;
    c = frame->data[5]->c;
    v10[8] = v18;
    v20 = (u32)get_Item(c, 1, 0);
    v21 = frame->data[5]->c;
    v10[9] = v20 / 100.0;
    v22 = get_Item(v21, 2, 0);
    v23 = (u16)v8[16];
    v10[10] = (f32)(u32)v22 / 100.0;
    if (v23 && v10[8] != 0.0)
    {
      Color = sl->Color;
      x = Color[0].x;
      v26 = (f32)((f32)((f32)(v11 % (s32)v23) * 360.0) / (f32)v23) * 0.017453292;
      Color[0].x = x + (f32)((f32)(x * sub_188E3D0(v26)) * v10[8]);
      v27 = sl->Color;
      v28 = 0.0;
      v29 = v27[0].x;
      if (v29 < 0.0 || (v28 = 2.0, v29 > 2.0))
        v27[0].x = v28;
      y = v27[0].y;
      v27[0].y = y + (f32)((f32)(y * sub_188E3D0(v26)) * v10[8]);
      v31 = sl->Color;
      if (v31[0].y < 0.0)
        v31[0].y = 0.0;
      if (v31[0].y > 2.0)
        v31[0].y = 2.0;
      z = v31[0].z;
      v33 = sub_188E3D0(v26);
      v34 = sl->Color;
      v31[0].z = z + (f32)((f32)(z * v33) * v10[8]);
      if (v34[0].z < 0.0)
        v34[0].z = 0.0;
      if (v34[0].z > 2.0)
        v34[0].z = 2.0;
    }
    if (v8[17] && v10[9] != 0.0)
    {
      v35 = sl->Color;
      v36 = v35[1].x;
      v37 = (f32)((f32)((f32)(v11 % (u16)v8[17]) * 360.0) / (f32)(u16)v8[17])
          * 0.017453292;
      v35[1].x = v36 + (f32)((f32)(v36 * sub_188E3D0(v37)) * v10[9]);
      v38 = sl->Color;
      v39 = 0.0;
      v40 = v38[1].x;
      if (v40 < 0.0 || (v39 = 2.0, v40 > 2.0))
        v38[1].x = v39;
      v41 = v38[1].y;
      v38[1].y = v41 + (f32)((f32)(v41 * sub_188E3D0(v37)) * v10[9]);
      v42 = sl->Color;
      if (v42[1].y < 0.0)
        v42[1].y = 0.0;
      if (v42[1].y > 2.0)
        v42[1].y = 2.0;
      v43 = v42[1].z;
      v44 = sub_188E3D0(v37);
      v45 = sl->Color;
      v42[1].z = v43 + (f32)((f32)(v43 * v44) * v10[9]);
      if (v45[1].z < 0.0)
        v45[1].z = 0.0;
      if (v45[1].z > 2.0)
        v45[1].z = 2.0;
    }
    v46 = (u16)v8[18];
    if (v8[18] && v10[10] != 0.0)
    {
      v47 = sl->Color;
      v48 = v47[2].x;
      v49 = (f32)((f32)((f32)(v11 % (s32)v46) * 360.0) / (f32)v46) * 0.017453292;
      v47[2].x = v48 + (f32)((f32)(v48 * sub_188E3D0(v49)) * v10[10]);
      v50 = sl->Color;
      v51 = 0.0;
      v52 = v50[2].x;
      if (v52 < 0.0 || (v51 = 2.0, v52 > 2.0))
        v50[2].x = v51;
      v53 = v50[2].y;
      v50[2].y = v53 + (f32)((f32)(v53 * sub_188E3D0(v49)) * v10[10]);
      v54 = sl->Color;
      if (v54[2].y < 0.0)
        v54[2].y = 0.0;
      if (v54[2].y > 2.0)
        v54[2].y = 2.0;
      v55 = v54[2].z;
      v56 = sub_188E3D0(v49);
      v57 = sl->Color;
      v54[2].z = v55 + (f32)((f32)(v55 * v56) * v10[10]);
      if (v57[2].z < 0.0)
        v57[2].z = 0.0;
      if (v57[2].z > 2.0)
        v57[2].z = 2.0;
    }
  }
}

// 0x1a19ab0
static void RunFrame2(evtViewerObject_t *obj, evtFrameInfo_t *frame, evtFrameInfo_t *nearframe, s32 nowframe, s32 *l, evtViewerInfo_t *pInfo, s32 offset) {
  s32 firstframe;
  f32 v16;
  s32 v17;
  s32 type;
  s32 v19;
  evtViewerObject_t *v22;
  DepthOfFieldSetting *p_evt_camera;
  s32 stat;
  u32 length;
  f32 v26;
  s32 v27;
  long f64 v28;
  s64 v29;
  evtFrameInfo_t *next;
  s32 v31;
  s32 v32;
  s32 v33;
  s16 v34;
  s32 v35;
  s16 v36;
  f32 v37;
  f32 v38;
  Il2CppObject *p;
  s64 naturalAligment;
  f32 f;
  f32 v42;
  u32 nameindex;
  f32 v44;
  Il2CppObject *v45;
  s32 v47;
  s32 fldfilter;
  long f64 v49;
  s32 v50;
  s32 v51;
  s16 v52;
  Il2CppObject *v53;
  s32 v55;
  s64 v56;
  s32 v57;
  s64 v58;
  s32 v59;
  s64 v60;
  s32 v61;
  s64 v62;
  s32 v63;
  s64 v64;
  s32 v65;
  s64 v66;
  s32 v67;
  s64 v68;
  void *spPosTbl;
  s32 v70;
  void *transform;
  void *Instance;
  void *monitor;
  s32 v75;
  Il2CppObject *v79;
  s64 v81;
  Il2CppObject *v86;
  s64 v87;
  dds3Effect_Blur_t *v90;
  s64 v91;
  s64 v95;
  s64 v99;
  s64 v103;
  s64 v107;
  s64 v111;
  evtViewerInfo_t *v115;
  s32 union0;
  f32 *Color;
  f32 v121;
  f32 v122;
  f32 v123;
  f32 v124;
  f32 *v126;
  f32 v127;
  f32 v128;
  f32 v129;
  f32 v130;
  f32 *v132;
  f32 v133;
  f32 v134;
  f32 v135;
  f32 v136;
  f32 v139;
  f32 v140;
  f32 v141;
  f32 v142;
  s32 i;
  s16 v144;
  s32 v145;
  s32 v146;
  s16 v147;
  void *dofTbl;
  s32 v150;
  DepthOfFieldSetting *Par;
  evtFrameInfo_t *v152;
  pmdProcessWork_t *workdata;
  void *v154;
  s32 v155;
  DepthOfFieldSetting *v156;
  s32 v157;
  pmdProcessWork_t *v158;
  DepthOfFieldSetting *v159;
  pmdProcessWork_t *v160;
  dds3Basic_t *ActiveScene;
  char *Name;
  evtUnitHandle_t *UnitHandle2;
  DepthOfFieldSetting *hokanData;
  s32 v165;
  s32 myno;
  s32 v169;
  pmdSceneLightTable_t *v170;
  sdfVector4_t *v171;
  sdfVector4_t *Dir;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  s32 v177;
  long f64 v178;
  f32 v179;
  long f64 v180;
  u32 v181;
  s32 v182;
  s64 v183;
  u32 v184;
  f32 v185;
  u32 *v186;
  s32 Item;
  u32 *v189;
  long f64 v190;
  u32 v191;
  s64 v192;
  u32 *v193;
  s32 v194;
  u32 *v196;
  long f64 v197;
  u32 v198;
  s64 v199;
  u32 *v200;
  s32 v201;
  u32 *v203;
  long f64 v204;
  u32 v205;
  u32 *v206;
  s64 v207;
  u32 *v208;
  s32 v209;
  u32 *v211;
  long f64 v212;
  u32 v213;
  u32 *v214;
  s64 v215;
  u32 v216;
  bool v217;
  f32 v218;
  dds3Basic_t *unit;
  sdfVector3_t v220;
  sdfVector4_t v221;
  sdfVector4_t v222;
  sdfVector4_t v223;
  sdfVector4_t v224;
  sdfVector4_t v225;

  unit = 0;
  if (nearframe)
  {
    firstframe = nearframe->frame;
    if (frame)
      goto LABEL_5;
LABEL_10:
    v16 = 0.0;
    v17 = pInfo->lastframe - firstframe;
    if (!v17)
      goto LABEL_7;
    goto LABEL_6;
  }
  firstframe = pInfo->firstframe;
  if (!frame)
    goto LABEL_10;
LABEL_5:
  v16 = 0.0;
  v17 = frame->frame - firstframe;
  if (v17)
LABEL_6:
    v16 = (f32)(nowframe - firstframe) / (f32)v17;
LABEL_7:
  type = obj->type;
  switch (type)
  {
    case 1:
    case 3:
    case 4:
    case 5:
    case 7:
    case 9:
    case 18:
    case 19:
    case 20:
    case 21:
    case 24:
    case 25:
    case 26:
      return;
    case 2:
      if (!nearframe)
        return;
      v19 = nowframe - offset - nearframe->frame;
      if (v19 >= *l)
        return;
      *l = v19;
      v22 = obj;
      evt_camera = obj;
      p_evt_camera = &evt_camera;
      goto LABEL_290;
    case 6:
      stat = pInfo->stat;
      if ((stat & 0x200) == 0)
      {
        stat = pInfo->stat;
        if ((stat & 0x10) == 0)
        {
          if (nearframe)
          {
            length = nearframe->length;
            v26 = 1.0;
            if (nearframe->length)
            {
              v27 = nearframe->frame;
              if ((s32)(v27 + length) > nowframe)
                v26 = (f32)(nowframe - v27) / (f32)length;
            }
            switch (get_Item(nearframe->data[0]->s, 0, 0))
            {
              case 0:
                v29 = 0;
                goto LABEL_385;
              case 1:
                v183 = 0;
                goto LABEL_390;
              case 2:
                sub_1A22850(0, 0, v28);
                v181 = 0;
                v182 = 0;
                if (v26 == 1.0)
                  goto LABEL_398;
                v181 = 0;
                v184 = vcvts_n_s32_f32(1.0 - v26, 7u);
                v185 = (f32)(1.0 - v26) * 128.0;
                goto LABEL_342;
              case 3:
                sub_1A22850(0, 0, v28);
                v181 = 0;
                v182 = 128;
                if (v26 >= 0.95 || v26 == 1.0)
                  goto LABEL_398;
                v184 = vcvts_n_s32_f32(v26, 7u);
                v181 = 0;
                v185 = v26 * 128.0;
LABEL_342:
                if (v185 == INFINITY)
                  v182 = 0x80000000;
                else
                  v182 = v184;
                goto LABEL_398;
              case 4:
                sub_1A22850(0, 0, v28);
                if (v26 == 1.0)
                  goto LABEL_386;
                v186 = NewSpecific(s32, 4u);
                v186[9] = get_Item(nearframe->data[1]->c, 0, 0);
                Item = get_Item(nearframe->data[1]->c, 2, 0);
                v186[10] = Item;
                v186[11] = 128;
                v189 = NewSpecific(s32, 4u);
                v189[9] = get_Item(nearframe->data[1]->c, 1, 0);
                v189[10] = get_Item(nearframe->data[1]->c, 3, 0);
                v189[11] = 128;
                DWORD1(v190) = 1124073472;
                v191 = vcvts_n_s32_f32(v26, 7u);
                if ((f32)(v26 * 128.0) == INFINITY)
                  v192 = 0x80000000LL;
                else
                  v192 = v191;
                *(f32 *)&v190 = v26 * 128.0;
                v182 = 128 - ((s32)((u32)sub_1A228E0(v192, v186, v189, 0, v190) << 7) >> 7);
                goto LABEL_397;
              case 5:
                sub_1A22850(0, 0, v28);
                v182 = 128;
                if (v26 != 1.0)
                {
                  v193 = NewSpecific(s32, 4u);
                  v193[9] = get_Item(nearframe->data[1]->c, 0, 0);
                  v194 = get_Item(nearframe->data[1]->c, 2, 0);
                  v193[10] = v194;
                  v193[11] = 128;
                  v196 = NewSpecific(s32, 4u);
                  v196[9] = get_Item(nearframe->data[1]->c, 1, 0);
                  v196[10] = get_Item(nearframe->data[1]->c, 3, 0);
                  v196[11] = 128;
                  DWORD1(v197) = 1124073472;
                  v198 = vcvts_n_s32_f32(v26, 7u);
                  if ((f32)(v26 * 128.0) == INFINITY)
                    v199 = 0x80000000LL;
                  else
                    v199 = v198;
                  *(f32 *)&v197 = v26 * 128.0;
                  v182 = (s32)((u32)sub_1A228E0(v199, v193, v196, 0, v197) << 7) >> 7;
                }
                goto LABEL_397;
              case 6:
                sub_1A22850(0, 0, v28);
                v181 = 0;
                v182 = 0;
                if (v26 != 1.0)
                {
                  v200 = NewSpecific(s32, 4u);
                  v200[9] = get_Item(nearframe->data[1]->c, 0, 0);
                  v201 = get_Item(nearframe->data[1]->c, 2, 0);
                  v200[10] = v201;
                  v200[11] = 128;
                  v203 = NewSpecific(s32, 4u);
                  v203[9] = get_Item(nearframe->data[1]->c, 1, 0);
                  v203[10] = get_Item(nearframe->data[1]->c, 3, 0);
                  v203[11] = 128;
                  DWORD1(v204) = 1124073472;
                  v205 = vcvts_n_s32_f32(v26, 7u);
                  v206 = v203;
                  if ((f32)(v26 * 128.0) == INFINITY)
                    v207 = 0x80000000LL;
                  else
                    v207 = v205;
                  v181 = 0;
                  *(f32 *)&v204 = v26 * 128.0;
                  v182 = 128 - ((s32)((u32)sub_1A228E0(v207, v200, v206, 0, v204) << 7) >> 7);
                }
                goto LABEL_398;
              case 7:
                sub_1A22850(0, 0, v28);
                v181 = 0;
                v182 = 128;
                if (v26 < 0.95 && v26 != 1.0)
                {
                  v208 = NewSpecific(s32, 4u);
                  v208[9] = get_Item(nearframe->data[3]->c, 1, 0);
                  v209 = get_Item(nearframe->data[3]->c, 3, 0);
                  v208[10] = v209;
                  v208[11] = 128;
                  v211 = NewSpecific(s32, 4u);
                  v211[9] = get_Item(nearframe->data[3]->c, 0, 0);
                  v211[10] = get_Item(nearframe->data[3]->c, 2, 0);
                  v211[11] = 128;
                  DWORD1(v212) = 1124073472;
                  v213 = vcvts_n_s32_f32(v26, 7u);
                  v214 = v211;
                  if ((f32)(v26 * 128.0) == INFINITY)
                    v215 = 0x80000000LL;
                  else
                    v215 = v213;
                  v181 = 0;
                  *(f32 *)&v212 = v26 * 128.0;
                  v182 = (s32)((u32)sub_1A228E0(v215, v208, v214, 0, v212) << 7) >> 7;
                }
                goto LABEL_398;
              case 8:
                v29 = 1;
LABEL_385:
                sub_1A22850(v29, 0, v28);
                if (v26 == 1.0)
                {
LABEL_386:
                  v182 = 0;
                  goto LABEL_397;
                }
                v216 = vcvts_n_s32_f32(1.0 - v26, 7u);
                v217 = (f32)((f32)(1.0 - v26) * 128.0) == INFINITY;
                goto LABEL_394;
              case 9:
                v183 = 1;
LABEL_390:
                sub_1A22850(v183, 0, v28);
                if (v26 == 1.0)
                {
                  v182 = 128;
                }
                else
                {
                  v216 = vcvts_n_s32_f32(v26, 7u);
                  v217 = (f32)(v26 * 128.0) == INFINITY;
LABEL_394:
                  if (v217)
                    v182 = 0x80000000;
                  else
                    v182 = v216;
                }
LABEL_397:
                v181 = 255;
LABEL_398:
                pInfo->fadeAlpha = v182;
                dds3FadeSet_2(v181, v181, v181, v182);
                break;
              default:
                v181 = 0;
                v182 = 0;
                goto LABEL_398;
            }
          }
          else
          {
            pInfo->fadeAlpha = 0;
            dds3FadeClear();
          }
        }
      }
      return;
    case 8:
      if (nearframe)
      {
        if (get_Item(nearframe->data[1]->s, 0, 0) && (next = nearframe->next) != 0)
        {
          v31 = nearframe->frame;
          v32 = next->frame - v31;
          v33 = nowframe - v31;
          v34 = get_Item(nearframe->data[0]->s, 0, 0);
          v35 = ((v32 - v33) * v34 + v33 * get_Item(nearframe->next->data[0]->s, 0, 0))
              / v32;
          v36 = get_Item(nearframe->data[0]->s, 1, 0);
          LODWORD(nearframe) = ((v32 - v33) * v36 + v33 * get_Item(nearframe->next->data[0]->s, 1, 0))
                             / v32;
        }
        else
        {
          LOWORD(v35) = get_Item(nearframe->data[0]->s, 0, 0);
          LOWORD(nearframe) = get_Item(nearframe->data[0]->s, 1, 0);
        }
        v75 = pInfo->stat;
        if ((u16)v35 | (u16)nearframe)
        {
          pInfo->stat = v75 | 4;
          ScreenBlurFlag = 1;
          ScreenBlurAlpha = v35;
          ScreenBlurScale = (s16)nearframe;
          return;
        }
      }
      else
      {
        v75 = pInfo->stat;
      }
      pInfo->stat = v75 & 0xFFFFFFFB;
      ScreenBlurFlag = 0;
      return;
    case 10:
      v37 = 7.0;
      v38 = 0.0;
      if (nearframe)
      {
        p = nearframe->p;
        f = get_f(nearframe->data[0], 0);
        v42 = get_f(nearframe->data[1], 0);
        nameindex = nearframe->nameindex;
        v44 = v42;
      }
      else
      {
        p = 0;
        nameindex = 1;
        v44 = 0.0;
        f = 7.0;
      }
      if (frame)
      {
        v79 = frame->p;
        v37 = get_f(frame->data[0], 0);
        v38 = get_f(frame->data[1], 0);
      }
      else
      {
        v79 = 0;
      }
      if (!((u64)p | (u64)v79))
        return;
      evtHokanSceneLight(nameindex, v16, p, v79, rf2_sl);
      union0 = obj->object_data->union0;
      if (!obj->object_data->union0)
        return;
      if (union0 != 3)
      {
        if (union0 == 1)
        {
          CalcLightCycle(rf2_sl, nearframe, nowframe, v115);
          Color = rf2_sl->Color;
          v121 = Color[8];
          v122 = Color[9];
          v124 = Color[10];
          v123 = Color[11];
          v221.x = v121;
          v221.y = v122;
          v221.z = v124;
          v221.w = v123;
          dds3SetLightColor(0, 0, v221);
          dds3SetLightDir(0, 0, rf2_sl->Dir[0]);
          v126 = rf2_sl->Color;
          v127 = v126[12];
          v128 = v126[13];
          v129 = v126[14];
          v130 = v126[15];
          v222.x = v127;
          v222.y = v128;
          v222.z = v129;
          v222.w = v130;
          dds3SetLightColor(0, 1u, v222);
          dds3SetLightDir(0, 1u, rf2_sl->Dir[1]);
          v132 = rf2_sl->Color;
          v133 = v132[16];
          v134 = v132[17];
          v135 = v132[18];
          v136 = v132[19];
          v223.x = v133;
          v223.y = v134;
          v223.z = v135;
          v223.w = v136;
          dds3SetLightColor(0, 2u, v223);
          dds3SetLightDir(0, 2u, rf2_sl->Dir[2]);
          v139 = rf2_sl[8];
          v140 = rf2_sl[9];
          v141 = rf2_sl[10];
          v142 = rf2_sl[11];
          v224.x = v139;
          v224.y = v140;
          v224.z = v141;
          v224.w = v142;
          dds3SetAmbientColor(0, v224);
          return;
        }
        UnitHandle2 = 0;
        if (!nearframe || union0 != 2)
          goto LABEL_322;
        if (nearframe->frame != nowframe)
          goto LABEL_304;
        UnitHandle2 = 0;
        if (get_Item(nearframe->data[3]->s, 0, 0) != 1)
        {
LABEL_322:
          v218 = v44;
          CalcLightCycle(rf2_sl, nearframe, nowframe, v115);
          myno = obj->myno;
          v169 = obj->object_data->union0;
          v170 = rf2_sl;
          v171 = v170->Color;
          Dir = v170->Dir;
          x = v170->Ambient.x;
          y = v170->Ambient.y;
          z = v170->Ambient.z;
          w = v170->Ambient.w;
          v225.x = x;
          v225.y = y;
          v225.z = z;
          v225.w = w;
          evtSetCustomSceneLightData(myno, v169, UnitHandle2, v171, Dir, v225);
          v177 = obj->myno;
          v178 = sub_1A22EF0(nameindex, 0, v16, f, v37);
          v179 = *(f32 *)&v178;
          v180 = sub_1A22EF0(nameindex, 0, v16, v218, v38);
          evtSetCustomSceneLightData_SoftenAndBias(v177, v179, *(f32 *)&v180);
          return;
        }
        if ((pInfo->stat & 1) != 0)
        {
LABEL_304:
          UnitHandle2 = 0;
          goto LABEL_322;
        }
        goto LABEL_319;
      }
      ActiveScene = dds3GetActiveScene();
      Name = pInfo->nametable[obj->object_data->union1]->Name;
      unit = dds3SceneBasicSearchNameAndType(ActiveScene, 5u, Name);
      if (unit)
      {
        UnitHandle2 = evtGetUnitHandle2(unit);
      }
      else
      {
        UnitHandle2 = 0;
      }
      if (nearframe)
      {
        v165 = nearframe->frame;
        if (!nearframe->length || v165 + nearframe->length >= nowframe)
        {
          if (v165 != nowframe || get_Item(nearframe->data[3]->s, 0, 0) != 1 || (pInfo->stat & 1) != 0)
          {
            goto LABEL_322;
          }
LABEL_319:
          DrawFlag |= 0x2000000u;
          return;
        }
      }
      return;
    case 11:
      if (nearframe)
      {
        v45 = nearframe->p;
        v47 = get_Item(nearframe->data[0]->s, 0, 0);
      }
      else
      {
        v45 = 0;
        v47 = 1;
      }
      if (frame && (v53 = frame->p) != 0)
      {
        if (v53->klass->_2.naturalAligment < (u32)v81 || v53->klass->_2.typeHierarchy[v81 - 1] != pmdSceneFogTable_t)
        {
          goto LABEL_123;
        }
      }
      else
      {
        if (!v45)
          return;
        v53 = 0;
      }
      evtHokanSceneFog(v47, v16, v45, v53, rf2_sf);
      FogParam->color = rf2_sf->Color;
      return;
    case 12:
      fldfilter = pInfo->fldfilter;
      if (nearframe)
      {
        if (fldfilter == get_i(nearframe->data[1], 0))
        {
          if (!skyanime)
          {
            v50 = sub_1A227C0(0, v49);
            if (v50 != get_Item(nearframe->data[0]->s, 1, 0))
            {
              v51 = nearframe->length;
              v52 = get_Item(nearframe->data[0]->s, 1, 0);
              evtSetAlpha(v51, v52);
            }
          }
        }
        else
        {
          i = get_i(nearframe->data[1], 0);
          v144 = get_Item(nearframe->data[0]->s, 0, 0);
          v145 = nearframe->length;
          dds3FilterSet(i, v144, v145);
          v146 = nearframe->length;
          v147 = get_Item(nearframe->data[0]->s, 1, 0);
          evtSetAlpha(v146, v147);
          pInfo->fldfilter = get_i(nearframe->data[1], 0);
          skyFilterSet = 1;
        }
      }
      else if (fldfilter)
      {
        dds3FilterSet(0, 1, 0);
        pInfo->fldfilter = 0;
        skyFilterSet = 1;
      }
      return;
    case 13:
      if (nearframe)
      {
        v53 = nearframe->p;
        {
          v55 = get_Item(nearframe->data[0]->s, 0, 0);
          goto LABEL_140;
        }
LABEL_123:
      }
      v53 = 0;
      v55 = 1;
LABEL_140:
      if (frame && (v86 = frame->p) != 0)
      {
        if (v86->klass->_2.naturalAligment < (u32)v87 || v86->klass->_2.typeHierarchy[v87 - 1] != pmdBlur2Table_t)
        {
          goto LABEL_237;
        }
      }
      else
      {
        if (!v53)
          return;
        v86 = 0;
      }
      evtHokanBlur2(v55, v16, v53, v86, rf2_bl2);
      v90 = rf2_bl2;
      BlurSetParam2(v90);
      pInfo->drawblur2 = rf2_bl2->abgr.w != 0.0;
      return;
    case 14:
      if (nearframe)
      {
        v53 = nearframe->p;
        if (v53)
        {
          if (v53->klass->_2.naturalAligment < (u32)v56 || v53->klass->_2.typeHierarchy[v56 - 1] != pmdMultBlurTable_t)
          {
            goto LABEL_123;
          }
        }
        v57 = get_Item(nearframe->data[0]->s, 0, 0);
      }
      else
      {
        v53 = 0;
        v57 = 1;
      }
      if (frame && (v86 = frame->p) != 0)
      {
        if (v86->klass->_2.naturalAligment < (u32)v91 || v86->klass->_2.typeHierarchy[v91 - 1] != pmdMultBlurTable_t)
        {
          goto LABEL_237;
        }
      }
      else
      {
        if (!v53)
          return;
        v86 = 0;
      }
      evtHokanMultBlur(v57, v16, v53, v86, rf2_mbl);
      (PartialMultiBlur->klass->vtable._9_SetParam.methodPtr)(PartialMultiBlur, rf2_mbl, PartialMultiBlur->klass->vtable._9_SetParam.method);
      pInfo->drawmblur = rf2_mbl->Blur->abgr.w != 0.0;
      return;
    case 15:
      if (nearframe)
      {
        v53 = nearframe->p;
        if (v53)
        {
          if (v53->klass->_2.naturalAligment < (u32)v58 || v53->klass->_2.typeHierarchy[v58 - 1] != pmdDistBlurTable_t)
          {
            goto LABEL_123;
          }
        }
        v59 = get_Item(nearframe->data[0]->s, 0, 0);
      }
      else
      {
        v53 = 0;
        v59 = 1;
      }
      if (frame && (v86 = frame->p) != 0)
      {
        if (v86->klass->_2.naturalAligment < (u32)v95 || v86->klass->_2.typeHierarchy[v95 - 1] != pmdDistBlurTable_t)
        {
          goto LABEL_237;
        }
      }
      else
      {
        if (!v53)
          return;
        v86 = 0;
      }
      evtHokanDistBlur(v59, v16, v53, v86, rf2_dbl);
      (DistortionBlur->klass->vtable._9_SetParam.methodPtr)(DistortionBlur, rf2_dbl, DistortionBlur->klass->vtable._9_SetParam.method);
      pInfo->drawdblur = rf2_dbl->abgr.w != 0.0;
      return;
    case 16:
      if (nearframe)
      {
        v53 = nearframe->p;
        if (v53)
        {
          if (v53->klass->_2.naturalAligment < (u32)v60 || v53->klass->_2.typeHierarchy[v60 - 1] != pmdFilterTable_t)
          {
            goto LABEL_123;
          }
        }
        v61 = get_Item(nearframe->data[0]->s, 0, 0);
      }
      else
      {
        v53 = 0;
        v61 = 1;
      }
      if (frame && (v86 = frame->p) != 0)
      {
        if (v86->klass->_2.naturalAligment < (u32)v99 || v86->klass->_2.typeHierarchy[v99 - 1] != pmdFilterTable_t)
        {
          goto LABEL_237;
        }
      }
      else
      {
        if (!v53)
          return;
        v86 = 0;
      }
      evtHokanFilter(v61, v16, v53, v86, rf2_fl);
      (Filter->klass->vtable._9_SetParam.methodPtr)(Filter, rf2_fl, Filter->klass->vtable._9_SetParam.method);
      pInfo->drawfilter = rf2_fl->abgr.w != 0.0;
      return;
    case 17:
      if (nearframe)
      {
        v53 = nearframe->p;
        if (v53)
        {
          if (v53->klass->_2.naturalAligment < (u32)v62 || v53->klass->_2.typeHierarchy[v62 - 1] != pmdMultFilterTable_t)
          {
            goto LABEL_123;
          }
        }
        v63 = get_Item(nearframe->data[0]->s, 0, 0);
      }
      else
      {
        v53 = 0;
        v63 = 1;
      }
      if (frame && (v86 = frame->p) != 0)
      {
        if (v86->klass->_2.naturalAligment < (u32)v103 || v86->klass->_2.typeHierarchy[v103 - 1] != pmdMultFilterTable_t)
        {
          goto LABEL_237;
        }
      }
      else
      {
        if (!v53)
          return;
        v86 = 0;
      }
      evtHokanMultFilter(v63, v16, v53, v86, rf2_mfl);
      (PartialMultiFilter->klass->vtable._9_SetParam.methodPtr)(PartialMultiFilter, rf2_mfl, PartialMultiFilter->klass->vtable._9_SetParam.method);
      pInfo->drawmfilter = rf2_mfl->Filter->abgr.w != 0.0;
      return;
    case 22:
      if (nearframe)
      {
        if (get_Item(nearframe->data[0]->s, 0, 0))
        {
          fldbokasi = 1;
          return;
        }
      }
      fldbokasi = 0;
      return;
    case 23:
      if (nearframe)
      {
        v53 = nearframe->p;
        if (v53)
        {
          if (v53->klass->_2.naturalAligment < (u32)v64 || v53->klass->_2.typeHierarchy[v64 - 1] != pmdRipBlurTable_t)
          {
            goto LABEL_123;
          }
        }
        v65 = get_Item(nearframe->data[0]->s, 0, 0);
      }
      else
      {
        v53 = 0;
        v65 = 1;
      }
      if (frame && (v86 = frame->p) != 0)
      {
        if (v86->klass->_2.naturalAligment < (u32)v107 || v86->klass->_2.typeHierarchy[v107 - 1] != pmdRipBlurTable_t)
        {
          goto LABEL_237;
        }
      }
      else
      {
        if (!v53)
          return;
        v86 = 0;
      }
      evtHokanRipBlur(v65, v16, v53, v86, rf2_rbl);
      (RippleBlur->klass->vtable._9_SetParam.methodPtr)(RippleBlur, rf2_rbl, RippleBlur->klass->vtable._9_SetParam.method);
      pInfo->drawrblur = rf2_rbl->abgr.w != 0.0;
      return;
    case 27:
      if (nearframe)
      {
        v53 = nearframe->p;
        if (v53)
        {
          if (v53->klass->_2.naturalAligment < (u32)v66 || v53->klass->_2.typeHierarchy[v66 - 1] != pmdHeikouBlurTable_t)
          {
            goto LABEL_123;
          }
        }
        v67 = get_Item(nearframe->data[0]->s, 0, 0);
      }
      else
      {
        v53 = 0;
        v67 = 1;
      }
      if (frame && (v86 = frame->p) != 0)
      {
        if (v86->klass->_2.naturalAligment < (u32)v111 || v86->klass->_2.typeHierarchy[v111 - 1] != pmdHeikouBlurTable_t)
        {
LABEL_237:
        }
      }
      else
      {
        if (!v53)
          return;
        v86 = 0;
      }
      evtHokanHeikouBlur(v67, v16, v53, v86, rf2_hbl);
      (ParallelBlur->klass->vtable._9_SetParam.methodPtr)(ParallelBlur, rf2_hbl, ParallelBlur->klass->vtable._9_SetParam.method);
      pInfo->drawhblur = rf2_hbl->abgr.w != 0.0;
      return;
    case 42:
      if (!nearframe)
        return;
      Instance = get_Instance(0);
      monitor = 0;
      if (!op_Inequality(Instance, 0, 0))
      {
        goto LABEL_101;
      }
      monitor = Instance[2].monitor;
LABEL_101:
      if (op_Equality(monitor, 0, 0))
        return;
      dofTbl = pInfo->workdata->dofTbl;
      v150 = get_i(nearframe->data[0], 0);
      Par = GetPar(dofTbl, v150, 0);
      if (get_i(nearframe->data[1], 0) && (v152 = nearframe->next) != 0)
      {
        workdata = pInfo->workdata;
        if (nearframe->frame == nowframe)
        {
          v154 = workdata->dofTbl;
          v155 = get_i(v152->data[0], 0);
          v156 = GetPar(v154, v155, 0);
          v157 = nearframe->next->frame - nearframe->frame;
          SetParamToDepthOfField(Par, monitor, 0);
          v158 = pInfo->workdata;
          v159 = Allocate(DepthOfFieldSetting);
          _ctor(v159, 0);
          v158->hokanData = v159;
          ParamSetToDepthOfField(pInfo->workdata->hokanData, monitor, 0);
          SetHokanData(pInfo->workdata->hokanData, v156, v157, 0);
        }
        else
        {
          hokanData = workdata->hokanData;
          if (hokanData)
          {
            evtHokanDof(hokanData);
          }
        }
      }
      else
      {
        SetParamToDepthOfField(Par, monitor, 0);
        v160 = pInfo->workdata;
        v22 = 0;
        v160->hokanData = 0;
        p_evt_camera = &v160->hokanData;
LABEL_290:
      }
      return;
    default:
      if (nearframe && type == 44)
      {
        v68 = get_i(nearframe->data[0], 0);
        spPosTbl = pInfo->workdata->loadScene[v68]->bg->spPosTbl;
        v70 = get_i(nearframe->data[1], 0);
        v220 = _get_Item(spPosTbl, v70);
        transform = get_transform(pInfo->workdata->loadScene[v68]->bg->bg, 0);
        set_position(transform, v220, 0);
      }
      return;
  }
}

// 0x1a1bde0
static void RunFrame3(s32 nowframe, evtViewerInfo_t *pInfo) {
  dds3Basic_t *ActiveScene;
  dds3Basic_t *v7;
  void *workdata;
  dds3Basic_t *next;
  evtViewerObject_t *firstobjinfo;
  evtFrameInfo_t *v12;
  s32 v13;
  evtFrameInfo_t *i;
  pmdNameTable_t *nametable;
  char *Name;
  dds3Basic_t *v17;
  evtUnitHandle_t *UnitHandle2;
  s32 length;
  evtUnitHandle_t *v20;
  s32 v21;
  s32 v22;
  dds3Basic_t *basic;
  dds3Basic_t *unit;

  ActiveScene = dds3GetActiveScene();
  if (!ActiveScene)
    return;
  v7 = ActiveScene;
  workdata = ActiveScene->workdata;
  next = *(dds3Basic_t *)(*((u64 *)workdata[1].monitor + 9) + 24);
  unit = next;
  while (next)
  {
    if (!next->name)
      goto LABEL_13;
    firstobjinfo = pInfo->firstobjinfo;
    basic = 0;
    if (firstobjinfo)
    {
      v12 = 0;
      v13 = -1;
      do
      {
        if (firstobjinfo->type == 9)
        {
          for (i = firstobjinfo->firstframeinfo; i; i = i->next)
          {
            if (firstobjinfo->object_data->Offset + i->frame <= nowframe && (get_Item(i->data[0]->s, 0, 0) & 0x8000) == 0)
            {
              nametable = pInfo->nametable;
              Name = nametable[get_Item(i->data[0]->s, 0, 0)]->Name;
              v17 = dds3SceneBasicSearchNameAndType(v7, 5u, Name);
              if (unit == v17 && v13 < firstobjinfo->object_data->Offset + i->frame)
              {
                v12 = i;
                v13 = firstobjinfo->object_data->Offset + i->frame;
                basic = firstobjinfo->basic;
              }
            }
          }
        }
        firstobjinfo = firstobjinfo->next;
      }
      while (firstobjinfo);
    }
    else
    {
      v12 = 0;
    }
    UnitHandle2 = evtGetUnitHandle2(unit);
    if (v12)
    {
      if (get_Item(v12->data[0]->s, 1, 0))
      {
        if (UnitHandle2->BasicLight != basic || (UnitHandle2->Flag & 0x40000) == 0)
        {
          length = v12->length;
          evtLinkLightObjectBasic(UnitHandle2, basic, length);
        }
        goto LABEL_13;
      }
      if ((UnitHandle2->Flag & 0x140000) == 0x40000)
      {
        v22 = v12->length;
        v20 = UnitHandle2;
        v21 = v22;
LABEL_46:
        evtUnlinkLightObjectBasic(v20, v21);
        goto LABEL_13;
      }
      goto LABEL_13;
    }
    if (UnitHandle2->BasicLight)
    {
      v20 = UnitHandle2;
      v21 = 0;
      goto LABEL_46;
    }
LABEL_13:
    next = unit->next;
    unit = next;
  }
}

// 0x1a1c150
static void RunFrameUnit(evtViewerObject_t *obj, s32 nowframe) {
  evtFrameInfo_t *firstframeinfo;
  evtUnitHandle_t *UnitHandle2;
  s8 v7;
  u32 Item;
  s32 v9;
  u16 v10;
  u16 v11;
  evtFrameInfo_t *next;
  evtFrameInfo_t *v15;
  evtFrameInfo_t *v16;
  u16 v17;
  s8 v19;
  evtFrameInfo_t *v20;
  s8 v21;
  u16 v22;
  s32 v24;
  u32 v25;
  s32 v26;
  s32 v27;
  dds3Basic_t *p_basic;
  dds3Basic_t *v30;
  dds3Basic_t *basic;
  u8 v32;
  pmdDataInfo_t *data;
  f32 f;
  pmdDataInfo_t *v35;
  s32 v36;
  dds3Basic_t *v37;
  evtUnitHandle_t *v38;
  dds3Basic_t *v39;
  dds3Basic_t *v40;
  u8 v41;
  pmdDataInfo_t *v43;
  s32 v45;
  s32 v46;
  s32 v47;

  firstframeinfo = obj->firstframeinfo;
  if (!firstframeinfo)
  {
    v24 = 0;
    LODWORD(next) = 0;
    v25 = 0;
    v26 = 2;
    v27 = 8;
    basic = obj->basic;
    p_basic = &obj->basic;
    v30 = basic;
    goto LABEL_75;
  }
  v45 = 0;
  v46 = 8;
  v47 = 2;
  UnitHandle2 = 0;
  while (firstframeinfo->frame <= nowframe)
  {
    Item = get_Item(firstframeinfo->data[0]->c, 0, 0);
    if (Item <= 9)
    {
      v9 = 1 << Item;
      if ((v9 & 0x1C) != 0)
      {
        v10 = get_Item(firstframeinfo->data[2]->s, 0, 0);
        if (v10 >= 0x1000u)
        {
          if (GBWK->IntVariable[(v10 >> 12) + 199] != (v10 & 0xFFF))
            goto LABEL_8;
        }
        v7 = get_Item(firstframeinfo->data[0]->c, 0, 0);
        v47 = v7;
        UnitHandle2 = evtGetUnitHandle2(&obj->basic);
        goto LABEL_8;
      }
      if ((v9 & 3) == 0)
      {
        if ((v9 & 0x300) != 0)
          v46 = get_Item(firstframeinfo->data[0]->c, 0, 0);
        goto LABEL_8;
      }
      v11 = get_Item(firstframeinfo->data[2]->s, 0, 0);
      if (v11 >= 0x1000u)
      {
        if (GBWK->IntVariable[(v11 >> 12) + 199] != (v11 & 0xFFF))
          goto LABEL_8;
      }
      v45 = get_Item(firstframeinfo->data[0]->c, 0, 0);
    }
LABEL_8:
    firstframeinfo = firstframeinfo->next;
    if (!firstframeinfo)
      break;
  }
  next = obj->firstframeinfo;
  if (!next)
  {
LABEL_73:
    v25 = 0;
    v27 = v46;
    v26 = v47;
    v24 = v45;
    v37 = obj->basic;
    p_basic = &obj->basic;
    v30 = v37;
    goto LABEL_75;
  }
  v15 = 0;
  while (2)
  {
    while (get_Item(next->data[0]->c, 0, 0) != 3 && get_Item(next->data[0]->c, 0, 0) != 4)
    {
LABEL_50:
      next = next->next;
      if (!next)
        goto LABEL_51;
    }
    v17 = get_Item(next->data[2]->s, 0, 0);
    if (v17 >= 0x1000u)
    {
      if (GBWK->IntVariable[(v17 >> 12) + 199] != (v17 & 0xFFF))
        goto LABEL_50;
    }
    v16 = next;
    if (next->frame <= nowframe)
    {
      next = next->next;
      v15 = v16;
      if (next)
        continue;
    }
    break;
  }
LABEL_51:
  if (!v15)
  {
    LODWORD(next) = 0;
    goto LABEL_73;
  }
  v19 = get_Item(v15->data[0]->c, 0, 0);
  v20 = obj->firstframeinfo;
  if (!v20)
  {
LABEL_69:
    v32 = get_Item(v15->data[1]->uc, 1, 0);
    data = v15->data;
    UnitHandle2->ShadowAlpha = v32;
    f = get_f(data[3], 0);
    v27 = v46;
    v24 = v45;
    goto LABEL_70;
  }
  v21 = v19;
  while (2)
  {
    if (get_Item(v20->data[0]->c, 0, 0) != v21)
      goto LABEL_55;
    v22 = get_Item(v20->data[2]->s, 0, 0);
LABEL_59:
    if (v22 < 0x1000u)
      goto LABEL_54;
    if (GBWK->IntVariable[(v22 >> 12) + 199] == (v22 & 0xFFF))
      goto LABEL_54;
LABEL_55:
    v20 = v20->next;
    if (!v20)
      goto LABEL_69;
    continue;
  }
  goto LABEL_59;
LABEL_54:
  if (v20->frame <= nowframe)
    goto LABEL_55;
  if (get_Item(v20->data[1]->c, 0, 0))
    get_Item(v20->data[1]->c, 0, 0);
  v41 = get_Item(v15->data[1]->uc, 1, 0);
  get_Item(v20->data[1]->uc, 1, 0);
  v27 = v46;
  v24 = v45;
  v43 = v20->data;
  UnitHandle2->ShadowAlpha = v41;
  if (get_Item(v43[1]->c, 0, 0))
    get_Item(v20->data[1]->c, 0, 0);
  f = get_f(v15->data[3], 0);
  get_f(v20->data[3], 0);
LABEL_70:
  v35 = v15->data;
  UnitHandle2->ShadowY = f;
  if (((u8)get_Item(v35[1]->c, 0, 0) | 2) == 3)
  {
    LODWORD(next) = 0;
    v36 = 0x4000;
  }
  else
  {
    v36 = 0;
    LODWORD(next) = 0x4000;
  }
  v26 = v47;
  if ((get_Item(v15->data[1]->c, 0, 0) & 0xFE) == 2)
  {
    v25 = v36 | 0x8000;
  }
  else
  {
    LODWORD(next) = (u32)next | 0x8000;
    v25 = v36;
  }
  v40 = obj->basic;
  p_basic = &obj->basic;
  v30 = v40;
LABEL_75:
  evtRunUnitMode(v30, v24, 0, 0);
  evtRunUnitMode(p_basic, v26, v25, (u32)next);
  v38 = evtGetUnitHandle2(p_basic);
  if (sdfModelGetUniqueID(v38->Model->modelRoot) != 100)
  {
    v39 = p_basic;
    evtRunUnitMode(v39, v27, 0, 0);
  }
}

// 0x1a1ca00
void evtRunFrame(s32 nowframe, evtViewerInfo_t *pInfo) {
  s32 stat;
  evtViewerObject_t *firstobjinfo;
  evtViewerObject_t *next;
  evtFrameInfo_t *firstframeinfo;
  s32 type;
  pmdDataInfo_t *data;
  s32 v22;
  evtFrameInfo_t *v23;
  s32 v24;
  s32 length;
  s32 v27;
  s32 v28;
  s32 v29;
  s32 v32;
  signed s32 v33;
  s32 v34;
  bool v36;
  s32 Frame;
  u32 v39;
  s32 v41;
  char *v42;
  char *v43;
  char *v44;
  char *v45;
  char *v46;
  char *v47;
  char *v48;
  char *v50;
  char *v51;
  evtViewerObject_t *v55;
  evtFrameInfo_t *v57;
  s32 Offset;
  evtFrameInfo_t *prev;
  s32 v60;
  s32 v61;
  pmdDataInfo_t *v63;
  u16 v64;
  s64 v66;
  u16 v67;
  dds3Basic_t *basic;
  s32 v74;
  evtFrameInfo_t *lastframeinfo;
  s32 v77;
  s32 v78;
  s32 v79;
  s32 EventNo;
  s16 v81;
  evtViewerInfo_t *v82;
  s32 l;
  s32 i;

  stat = pInfo->stat;
  *(u32 *)&pInfo->drawblur2 = 0;
  *(u16 *)&pInfo->drawmfilter = 0;
  i = 0;
  l = 0;
  pInfo->drawhblur = 0;
  pInfo->stat = stat & 0xFFFFFFF9;
  evtInitCustomSceneLight();
  ValidatePathFrame(nowframe, pInfo);
  ValidateUnitMotionFrame(nowframe, pInfo, 0);
  ValidateUnitPosChange(nowframe, pInfo);
  if ((pInfo->stat & 0x10) == 0)
    goto LABEL_9;
  goto LABEL_8;
  if ((pInfo->stat & 0x10) != 0)
LABEL_8:
    ++pInfo->EventSkipCount;
LABEL_9:
  sub_1A22FB0(nowframe, pInfo, 0);
  ValidateMovie(pInfo);
  ValidateRenderTex(pInfo);
  firstobjinfo = pInfo->firstobjinfo;
  if (firstobjinfo)
  {
    while (firstobjinfo->type != 36)
    {
      firstobjinfo = firstobjinfo->next;
      if (!firstobjinfo)
        goto LABEL_12;
    }
    lastframeinfo = firstobjinfo->lastframeinfo;
    if (lastframeinfo)
    {
      while (pInfo->nowframe < lastframeinfo->frame)
      {
        lastframeinfo = lastframeinfo->prev;
        if (!lastframeinfo)
          goto LABEL_185;
      }
LABEL_186:
      v77 = 0;
      v78 = -1;
      while (1)
      {
        Item = get_Item(lastframeinfo->data[0]->s, 1, 0);
        v79 = (s16)Item;
        if (v78 != (s16)Item)
        {
          EventNo = pInfo->workdata->EventNo;
          v81 = get_Item(lastframeinfo->data[0]->s, 1, 0);
          Item = evtRequest(v81 | (EventNo << 16), lastframeinfo->frame);
          if (++v77 > 1)
            goto LABEL_12;
          v78 = v79;
        }
        lastframeinfo = lastframeinfo->next;
        if (!lastframeinfo)
          goto LABEL_12;
      }
    }
LABEL_185:
    lastframeinfo = firstobjinfo->firstframeinfo;
    if (lastframeinfo)
      goto LABEL_186;
  }
LABEL_12:
  frame = nowframe;
  CalcNextMesSet();
  next = pInfo->firstobjinfo;
  if (next)
  {
    while (1)
    {
      if (next->type == 1)
      {
        RunFrameUnit(next, nowframe);
        goto LABEL_17;
      }
      firstframeinfo = next->firstframeinfo;
      if (firstframeinfo)
        break;
LABEL_17:
      next = next->next;
      if (!next)
        goto LABEL_110;
    }
    while (1)
    {
      while (1)
      {
        type = next->type;
        if (type <= 9)
          break;
        if ((u32)type <= 0x15)
        {
          if (((1 << type) & 0x340000) != 0)
            goto LABEL_43;
LABEL_36:
          length = firstframeinfo->length;
          if (!firstframeinfo->length)
            goto LABEL_43;
          goto LABEL_50;
        }
        switch (type)
        {
          case 26:
            goto LABEL_38;
          case 33:
            data = firstframeinfo->data;
            v22 = 0;
            goto LABEL_40;
          case 34:
          case 35:
            goto LABEL_43;
          case 38:
            length = firstframeinfo->length;
            Frame = movieGetFrame();
            v39 = firstframeinfo->frame;
            if (get_i(firstframeinfo->data[1], 0) == -1000)
              break;
            if (drawEnd)
              break;
            v41 = v39 >> 1;
            if (!length && Frame == v41 || length && Frame >= v41 && Frame < v41 + length)
            {
              v42 = NewSpecific(string, 6u);
              v43 = "E";
              v42[0] = "E";
              v44 = ToString_55996800((u32)pInfo->workdata + 20, "d3", 0);
              v42[1] = v44;
              v45 = "_";
              v42[2] = "_";
              v46 = ToString_55996800((u32)pInfo->workdata + 24, "d3", 0);
              v42[3] = v46;
              v47 = "_L";
              v42[4] = "_L";
              i = get_i(firstframeinfo->data[0], 0);
              v48 = ToString_55996800((s32)&i, "d4", 0);
              v42[5] = v48;
              v50 = Concat_54832608(v42, 0);
              v51 = ChgVoiceLabel(v50);
              sndVoicePlayFile(v51, 0);
              set_i(firstframeinfo->data[1], -1000, 0);
            }
            break;
          default:
            goto LABEL_36;
        }
LABEL_102:
        if (!length)
          goto LABEL_43;
LABEL_50:
        if (length >= 1)
        {
          v27 = firstframeinfo->frame;
          if (v27 <= nowframe && length + v27 > nowframe)
            goto LABEL_53;
        }
LABEL_21:
        OutFrame1(next, firstframeinfo, (s32)length, pInfo);
        firstframeinfo = firstframeinfo->next;
        if (!firstframeinfo)
          goto LABEL_17;
      }
      if (type == 3)
      {
LABEL_38:
        if (!get_Item(firstframeinfo->data[0]->s, 1, 0))
        {
LABEL_42:
          length = pInfo->totalframe - firstframeinfo->frame;
          if (!length)
            goto LABEL_43;
          goto LABEL_50;
        }
        data = firstframeinfo->data;
        v22 = 1;
LABEL_40:
        length = get_Item(data[0]->s, v22, 0)
               - firstframeinfo->frame;
        if (length >= 0)
        {
LABEL_49:
          if (!length)
            goto LABEL_43;
          goto LABEL_50;
        }
      }
      else
      {
        if (type == 4)
        {
          length = firstframeinfo->length;
          goto LABEL_47;
LABEL_48:
          if (drawEnd)
            goto LABEL_49;
          goto LABEL_9002;
LABEL_47:
          goto LABEL_48;
LABEL_9002:
          v32 = movieGetFrame();
          v33 = ((u32)firstframeinfo->frame + 1) >> 1;
          if ((length || v32 != v33) && (!length || v32 < v33 || v32 >= v33 + length))
            goto LABEL_102;
          if (get_Item(firstframeinfo->data[2]->c, 1, 0) != 99)
          {
            goto LABEL_108;
          }
          v36 = sndVoiceStatus(0);
          if (!v36)
          {
            goto LABEL_73;
LABEL_74:
            if (!nmesw_top)
              goto LABEL_107;
            goto LABEL_9003;
LABEL_73:
            goto LABEL_74;
            if (!nmesw_top)
            {
LABEL_107:
LABEL_108:
              ReqMessage(evtViewer, firstframeinfo, 2 * v32, v34, pInfo);
              if (length)
                goto LABEL_50;
              goto LABEL_43;
            }
LABEL_9003:
          }
          AddNextMesSet(next, firstframeinfo, 2 * v32, length, pInfo);
          if (length)
            goto LABEL_50;
          goto LABEL_43;
        }
        v23 = firstframeinfo;
        if (type != 9)
          goto LABEL_36;
        do
        {
          v23 = v23->next;
          if (!v23)
            goto LABEL_42;
          v24 = (u16)get_Item(v23->data[0]->s, 0, 0);
        }
        while (v24 != (u16)get_Item(firstframeinfo->data[0]->s, 0, 0));
        length = v23->frame - firstframeinfo->frame;
        if (length)
          goto LABEL_50;
      }
LABEL_43:
      length = 0;
      if (firstframeinfo->frame != nowframe)
        goto LABEL_21;
LABEL_53:
      sub_1A236B0((s32)next, (s32)firstframeinfo, nowframe, length, pInfo);
      InFrame1(next, firstframeinfo, v28, v29, pInfo);
      VisibleFrame1(next, firstframeinfo, nowframe, pInfo);
      firstframeinfo = firstframeinfo->next;
      if (!firstframeinfo)
        goto LABEL_17;
    }
  }
LABEL_110:
  l = 20000;
  evt_camera = 0;
  v55 = pInfo->firstobjinfo;
  if (!v55)
    goto LABEL_163;
LABEL_119:
  v82 = pInfo;
LABEL_121:
  v57 = v55->firstframeinfo;
  Offset = v55->object_data->Offset;
  if (!v57)
  {
LABEL_122:
    v57 = 0;
    prev = v55->lastframeinfo;
    v60 = v55->type;
    if ((u32)(v60 - 16) >= 2)
      goto LABEL_145;
LABEL_147:
    v66 = 3;
    if (prev)
      goto LABEL_150;
LABEL_160:
    pInfo = v82;
    goto LABEL_161;
  }
  while (1)
  {
    v61 = v55->type;
    if ((u32)(v61 - 16) < 2 || v61 == 12)
    {
      v63 = v57->data[3];
    }
    else
    {
      if (v61 != 2)
        goto LABEL_124;
      v63 = v57->data[1];
    }
    v64 = get_Item(v63->s, 0, 0);
    if (v64 >= 0x1000u)
    {
      if (GBWK->IntVariable[(v64 >> 12) + 199] != (v64 & 0xFFF))
        goto LABEL_125;
    }
LABEL_124:
    if (v57->frame + Offset > nowframe)
    {
      prev = v57->prev;
      v60 = v55->type;
      if ((u32)(v60 - 16) < 2)
        goto LABEL_147;
LABEL_145:
      if (v60 != 2)
      {
        if (v60 == 12)
          goto LABEL_147;
LABEL_161:
        RunFrame2(v55, v57, prev, nowframe, &l, pInfo, Offset);
        v55 = v55->next;
        if (!v55)
          goto LABEL_163;
        goto LABEL_121;
      }
      v66 = 1;
      if (!prev)
        goto LABEL_160;
LABEL_150:
      while (2)
      {
        v67 = get_Item(prev->data[v66]->s, 0, 0);
        if (v67 < 0x1000u)
          goto LABEL_160;
        if (GBWK->IntVariable[(v67 >> 12) + 199] == (v67 & 0xFFF))
          goto LABEL_160;
        prev = prev->prev;
        if (!prev)
          goto LABEL_160;
        continue;
      }
    }
LABEL_125:
    v57 = v57->next;
    if (!v57)
      goto LABEL_122;
  }
  evt_camera = 0;
  v55 = pInfo->firstobjinfo;
  if (v55)
    goto LABEL_119;
LABEL_163:
  if (evt_camera)
    goto LABEL_165;
LABEL_172:
  RunFrame3(nowframe, pInfo);
  v74 = pInfo->stat;
  if ((v74 & 1) == 0)
    return;
  goto LABEL_173;
LABEL_165:
  basic = evt_camera->basic;
  pInfo->gamecamera = basic;
  SetActiveCamera(pInfo);
  goto LABEL_172;
LABEL_173:
  if ((v74 & 2) == 0)
  {
    dds3StopQuake();
    v74 = pInfo->stat;
  }
  if ((v74 & 4) == 0)
  {
    ScreenBlurFlag = 0;
  }
}

// 0x1a18530
static char *ChgVoiceLabel(char *lbl) {
  if (op_Equality(lbl, "E812_001_L0001", 0))
    return "E661_002_L0001";
  if (op_Equality(lbl, "E816_001_L0000", 0))
    return "E660_003_L0000";
  if (op_Equality(lbl, "E816_001_L0001", 0))
    return "E660_003_L0001";
  if (op_Equality(lbl, "E617_001_L0012", 0))
    return "E617_001_L0010_01";
  return lbl;
}

// 0x1a1d780
static evtFrameInfo_t *GetNearCameraFrame(evtViewerInfo_t *pInfo) {
  evtViewerObject_t *firstobjinfo;
  evtFrameInfo_t *result;
  s32 v5;
  evtFrameInfo_t *firstframeinfo;
  s32 nowframe;
  s32 frame;
  s32 v9;
  evtFrameInfo_t *v10;

  firstobjinfo = pInfo->firstobjinfo;
  if (!firstobjinfo)
    return 0;
  result = 0;
  v5 = 99999;
  do
  {
    if (firstobjinfo->type == 2)
    {
      firstframeinfo = firstobjinfo->firstframeinfo;
      if (firstframeinfo)
      {
        nowframe = pInfo->nowframe;
        do
        {
          frame = firstframeinfo->frame;
          v9 = nowframe - frame;
          if (v5 <= nowframe - frame)
            v10 = result;
          else
            v10 = firstframeinfo;
          firstframeinfo = firstframeinfo->next;
          if (v5 < v9)
            v9 = v5;
          if (nowframe >= frame)
          {
            v5 = v9;
            result = v10;
          }
        }
        while (firstframeinfo);
      }
    }
    firstobjinfo = firstobjinfo->next;
  }
  while (firstobjinfo);
  return result;
}

// 0x1a12280
void evtUnitMotionChange(s32 nowframe, dds3Basic_t *b, evtViewerObject_t *obj, evtViewerInfo_t *pInfo, s32 mode) {
  void *workdata;
  dds3ModelHandle_t *v10;
  void **v12;
  s32 v13;
  s64 v14;
  sdfMotionCtrlr_t *v15;
  u64 *v16;
  evtFrameInfo_t *v18;
  evtFrameInfo_t *v20;
  void **v21;
  s8 Item;
  s32 v23;
  s32 v24;
  s32 MotionLength;
  s32 v26;
  s32 v27;
  sdfMotionCtrlr_t *MotionCtrlr;
  s8 v29;
  s8 v30;
  s32 userId2;
  s8 v32;
  s32 v33;
  s32 v34;
  void *v35;
  sdfMotionCtrlr_t *v36;
  void *v37;
  s32 v38;
  sdfMotionCtrlr_t *v39;
  evtFrameInfo_t *motionchange_apply_frame;
  evtViewerObject_t *v42;
  s8 v44;

  workdata = b->workdata;
  v10 = *((dds3ModelHandle_t *)workdata[2].monitor + 5);
  v12 = &mdl;
  if (!mdlHasMotion(v10))
    return;
  goto LABEL_13;
  if (mdlHasMotion(v10))
  {
LABEL_13:
    v13 = 0;
    v14 = 32;
    v42 = obj;
    do
    {
      if (*((u32 *)*v12 + 56))
      {
        if (!mdlGetMotionCtrlr(v10, v13))
          goto LABEL_17;
      }
      else
      {
        if (!mdlGetMotionCtrlr(v10, v13))
          goto LABEL_17;
      }
      if (!*((u32 *)*v12 + 56))
      mdlGetMotionCtrlr(v10, v13)->speed = 0.5;
      v18 = GetUnitMotionChangeFrame(obj, nowframe, v13);
      if (!v18)
        goto LABEL_17;
      v20 = v18;
      v21 = v12;
      Item = get_Item(v18->data[1]->c, 2, 0);
      v23 = Item == 0;
      v24 = get_Item(v20->data[4]->s, 0, 0);
      if (Item)
      {
        if (!*((u32 *)*v12 + 56))
        MotionLength = mdlGetMotionLengthEx(v10, v13);
        v26 = mode;
        if (v24 + nowframe - v20->frame > 2 * MotionLength - 1)
          v26 = 1;
        mode = v26;
        v44 = Item;
        if (v24 >= 1)
        {
LABEL_34:
          mode = 1;
          if (get_Item(v20->data[1]->c, 3, 0) >= 1)
            v27 = -((u16)(v24 & 0xFFFE) >> 1);
          else
            v27 = 0;
LABEL_41:
          if (!*((u32 *)*v12 + 56))
          MotionCtrlr = mdlGetMotionCtrlr(v10, v13);
          v29 = get_Item(v20->data[1]->c, 1, 0);
          v30 = get_Item(v20->data[1]->c, 3, 0);
          sdfMotionChangeBlend(MotionCtrlr, v29, v23, (f32)v27, (f32)v30);
          userId2 = mdlGetMotionCtrlr(v10, v13)->userId2;
          mdlEffectStop(v10, userId2);
          v32 = get_Item(v20->data[1]->c, 1, 0);
          mdlEffectGen(v10, v32, userId2);
          if (mode == 1)
          {
            if (!*((u32 *)*v21 + 56))
            v33 = mdlGetMotionLengthEx(v10, v13);
            if (v44)
            {
              if (v24 + nowframe - v20->frame >= 2 * v33 - 1)
                v34 = 2 * v33 - 1;
              else
                v34 = v24 + nowframe - v20->frame;
              v35 = *v21;
              if (!*((u32 *)*v21 + 56))
LABEL_54:
            }
            else if (v33)
            {
              v34 = (v24 + nowframe - v20->frame) % (2 * v33);
              v35 = *v21;
              if (!*((u32 *)*v21 + 56))
                goto LABEL_54;
            }
            else
            {
              v34 = 0;
              v35 = *v21;
              if (!*((u32 *)*v21 + 56))
                goto LABEL_54;
            }
            v36 = mdlGetMotionCtrlr(v10, v13);
            sdfMotionSeek(v36, (f32)v34 * 0.5);
          }
          v37 = *v21;
          obj = v42;
          v38 = *((u32 *)*v21 + 56);
          if ((pInfo->stat & 1) != 0)
          {
            v12 = v21;
            if (!v38)
            v15 = mdlGetMotionCtrlr(v10, v13);
            sdfMotionPause(v15);
            v16 = ((char *)&v42->motionchange_apply_frame->obj.klass + v14);
            *v16 = 0;
          }
          else
          {
            if (!v38)
            v39 = mdlGetMotionCtrlr(v10, v13);
            sdfMotionPauseOff(v39);
            motionchange_apply_frame = v42->motionchange_apply_frame;
            *(Il2CppClass **)((char *)&motionchange_apply_frame->obj.klass + v14) = v20;
            v12 = v21;
          }
          goto LABEL_17;
        }
      }
      else
      {
        v44 = Item;
        if (v24 >= 1)
          goto LABEL_34;
      }
      if (mode)
      {
        v27 = 0;
        goto LABEL_41;
      }
      v27 = 0;
      mode = 0;
      if (*(evtFrameInfo_t *)((char *)&obj->motionchange_apply_frame->obj.klass + v14) != v20)
        goto LABEL_41;
LABEL_17:
      v14 += 8;
      ++v13;
    }
    while (v14 != 64);
  }
}

// 0x1a186a0
void evtMessageDelete(evtViewerInfo_t *pInfo, bool Mode) {
  pmdProcessWork_t *workdata;
  s32 MesHandle;
  s32 v7;

  workdata = pInfo->workdata;
  if (workdata)
  {
    MesHandle = workdata->MesHandle;
    if (MesHandle != -1)
    {
      if (Mode)
      {
        if ((pInfo->last_meswin_mode | 2) == 2)
        {
          itfMesMngMsgWndCls(MesHandle);
        }
      }
      else
      {
        itfMesMngRequestMessageRelease(MesHandle, 1);
        itfMesMngMsgWndCls(pInfo->workdata->MesHandle);
        itfMesMngClearCursor(pInfo->workdata->MesHandle);
      }
      pInfo->stat &= ~0x100u;
      v7 = pInfo->workdata->MesHandle;
      itfMesMngSetSelPhase(v7, 0);
      itfMesMngRequestSelectRelease(pInfo->workdata->MesHandle);
      *(u16 *)&pInfo->branch->branchfilter_count = 0;
    }
  }
}

// 0x1a1d800
static bool ChkSkipIgnoreBgmFadeOutEvent(pmdProcessWork_t *wdata) {
  return wdata->EventNo == 690 && wdata->CutNo == 1;
}

// 0x1a1d830
static void EventSkipStart(evtViewerInfo_t *pInfo) {
  s32 nowframe;
  bool v6;
  s32 v8;
  pmdProcessWork_t *workdata;
  s32 v11;

  if ((pInfo->stat & 0x10) != 0)
    return;
  if (evtFindInputBranchMessage(pInfo))
  {
LABEL_32:
    if (!pInfo->dontskip_messagetime)
      pInfo->dontskip_messagetime = 1;
    return;
  }
  if (!scrCheckEnableMovieCancel())
    goto LABEL_32;
  nowframe = pInfo->nowframe;
  if (nowframe < pInfo->lastframe - 30 && pInfo->firstframe + 20 < nowframe)
  {
    pInfo->stat |= 0x10u;
    last_skip_stat = 1;
    v6 = evtGetSkipMode(pInfo) == 2;
    if (v6)
      v8 = 23;
    else
      v8 = 0;
    pInfo->EventSkipCount = v8;
    evtEventFadeOutAllBgm(pInfo);
    if (sndVoiceStatus(0) || pInfo->nowMovieStat == 1)
    {
      sndVoiceStop(0);
      workdata = pInfo->workdata;
LABEL_29:
      if (workdata->EventNo != 690)
        goto LABEL_39;
      goto LABEL_38;
    }
    else
    {
      workdata = pInfo->workdata;
      goto LABEL_29;
    }
    if (workdata->EventNo != 690)
    {
LABEL_39:
      if (sndBgmStatus_XF() == 3)
      {
        sndBgmFadeOut();
      }
LABEL_45:
      if (scrGetAfterSkipBgmFlag() == 1)
      {
        sndBgmFadeOut();
        v11 = 2;
        goto LABEL_54;
      }
      else
      {
        v11 = 0;
LABEL_54:
        GBWK->afterSkipPlayBgm = v11;
        sndSeFadeOut();
        evtMessageDelete(pInfo, 0);
        scrLogEnd(0);
        return;
      }
      goto LABEL_54;
    }
LABEL_38:
    if (workdata->CutNo == 1)
      goto LABEL_45;
    goto LABEL_39;
  }
}

// 0x1a1dbf0
static void EventSkipFilterManager(evtViewerInfo_t *pInfo) {
  s32 EventSkipCount;
  s32 v6;
  f32 v7;
  s32 SkipMode;
  char v10;
  char v11;
  u32 v14;
  u8 *v15;
  u32 v16;
  u32 v17;
  u32 v18;

  EventSkipCount = pInfo->EventSkipCount;
  if (EventSkipCount == 25)
  {
    v6 = 0;
    goto LABEL_14;
  }
  v6 = 0;
  v7 = 128.0
     - (f32)((f32)((f32)((f32)(128.0 - (f32)pInfo->fadeAlpha) / 25.0) * (f32)EventSkipCount) + (f32)pInfo->fadeAlpha);
  if (v7 != INFINITY && ((s32)v7 & 0x80000000) == 0)
  {
    v6 = v7;
    if ((u32)(s32)v7 > 0x7F)
      return;
  }
LABEL_14:
  if ((pInfo->stat & 0x10) == 0)
    return;
  SkipMode = evtGetSkipMode(pInfo);
  if (SkipMode == 2)
    return;
  if (SkipMode == 1)
  {
    v10 = -1;
    v11 = -1;
    v11 = v10;
LABEL_28:
    skip_filterrgba[2] = v11;
    skip_filterrgba[1] = v11;
    skip_filterrgba[0] = v11;
    goto LABEL_29;
  }
  if (!SkipMode)
  {
    v10 = 0;
    v11 = 0;
    goto LABEL_28;
  }
LABEL_29:
  v14 = 128 - v6;
  v15 = skip_filterrgba;
  v16 = v15[32];
  v17 = v15[33];
  v18 = v15[34];
  dds3FadeSet_2(v16, v17, v18, v14);
}

// 0x1a1de70
static void MovieStop(evtViewerInfo_t *pInfo) {
  movieStop(0);
  *(u64 *)&pInfo->nowMovieStat = 0;
  pInfo->MovieEndFrame = 0;
}

// 0x1a1dee0
static void DrawNoSkiPrint(evtViewerInfo_t *pInfo) {
  s32 dontskip_messagetime;
  s32 v3;

  if (pInfo->nowframe < pInfo->lastframe - 3)
  {
    dontskip_messagetime = pInfo->dontskip_messagetime;
    if (dontskip_messagetime >= 1)
    {
      if (dontskip_messagetime + 1 < 30)
        v3 = dontskip_messagetime + 1;
      else
        v3 = 0;
      pInfo->dontskip_messagetime = v3;
    }
  }
}

// 0x1a1df10
void evtViewerStopFrame(bool sw, u32 nowframe, evtViewerInfo_t *pInfo) {
  dds3Basic_t *ActiveScene;
  void *workdata;
  s64 naturalAligment;
  u64 *monitor;
  dds3Basic_t *next;
  evtViewerObject_t *firstobjinfo;
  s64 v15;
  dds3PathBasicControl_t *v17;
  s64 v18;
  sdfMotionCtrlr_t *klass;
  s64 v20;
  dds3PathBasicControl_t *v21;
  sdfMotionCtrlr_t *v22;
  dds3Basic_t *v23;
  s64 v24;
  evtViewerObject_t *i;
  s32 type;
  bool v28;
  s32 v29;
  evtFrameInfo_t *firstframeinfo;
  s32 union0;
  s32 frame;
  s32 v34;
  u8 Item;
  dds3Basic_t *v36;
  dds3PathBasicControl_t *pControl;
  dds3Basic_t *pObjectBasic;

  pControl = 0;
  ActiveScene = dds3GetActiveScene();
  if (!ActiveScene)
    return;
  workdata = ActiveScene->workdata;
  if (workdata)
  {
    if (workdata->klass->_2.naturalAligment < (u32)naturalAligment || workdata->klass->_2.typeHierarchy[naturalAligment - 1] != dds3SceneBasic_t)
    {
      v17 = ActiveScene->workdata;
      goto LABEL_89;
    }
  }
  monitor = workdata[1].monitor;
  next = *(dds3Basic_t *)(monitor[9] + 24);
  if (next)
  {
    firstobjinfo = pInfo->firstobjinfo;
    if (firstobjinfo)
    {
LABEL_12:
      while (firstobjinfo->basic != next)
      {
        firstobjinfo = firstobjinfo->next;
        if (!firstobjinfo)
          goto LABEL_18;
      }
      evtUnitMotionChange(nowframe, next, firstobjinfo, pInfo, 1);
LABEL_18:
      while (1)
      {
        next = next->next;
        if (!next)
          break;
        firstobjinfo = pInfo->firstobjinfo;
        if (firstobjinfo)
          goto LABEL_12;
      }
      v15 = *(u64 *)(*((u64 *)workdata[1].monitor + 10) + 24);
      if (v15)
        goto LABEL_25;
      goto LABEL_39;
    }
    do
      next = next->next;
    while (next);
  }
  v15 = *(u64 *)(monitor[10] + 24);
  if (v15)
  {
LABEL_25:
    if (sw)
    {
      while (1)
      {
        v17 = *(dds3PathBasicControl_t ***)(v15 + 48);
        if (v17)
        {
          if (LOBYTE(v17[4].pFovy) < (u32)v18 || *((Project_Basic_dds3MatterObjectBasicWorkData_t_c **)(v17)[3].monitor + v18 - 1) != Project_Basic_dds3MatterObjectBasicWorkData_t)
          {
            break;
          }
        }
        klass = v17[2][1].klass;
        if (klass)
        {
          sdfMotionPauseOff(klass);
        }
        v15 = *(u64 *)(v15 + 64);
        if (!v15)
          goto LABEL_39;
      }
    }
    else
    {
      while (1)
      {
        v17 = *(dds3PathBasicControl_t ***)(v15 + 48);
        if (v17)
        {
          if (LOBYTE(v17[4].pFovy) < (u32)v20 || *((Project_Basic_dds3MatterObjectBasicWorkData_t_c **)(v17)[3].monitor + v20 - 1) != Project_Basic_dds3MatterObjectBasicWorkData_t)
          {
            break;
          }
        }
        v21 = v17[2];
        v22 = v21[1].klass;
        if (v22)
        {
          sdfMotionSeek(v21[1].klass, (f32)nowframe);
          sdfMotionPause(v22);
        }
        v15 = *(u64 *)(v15 + 64);
        if (!v15)
          goto LABEL_39;
      }
    }
LABEL_89:
  }
LABEL_39:
  v23 = *(dds3Basic_t *)(*((u64 *)workdata[1].monitor + 7) + 24);
  for (pObjectBasic = v23; v23; pObjectBasic = v23)
  {
    v17 = v23->workdata;
    if (v17)
    {
      if (LOBYTE(v17[4].pFovy) < (u32)v24 || *((Project_Basic_dds3MoverBasicWorkData_t_c **)(v17)[3].monitor + v24 - 1) != Project_Basic_dds3MoverBasicWorkData_t)
      {
        goto LABEL_89;
      }
    }
    pControl = v17[3];
    if (pControl)
    {
      if (sw)
      {
        dds3PathBasicPauseOff(pControl);
      }
      else
      {
        dds3PathBasicPause(pControl);
      }
    }
    v23 = v23->next;
  }
  for (i = pInfo->firstobjinfo; i; i = i->next)
  {
    type = i->type;
    if (type <= 18)
    {
      if (type != 3 && type != 18)
        continue;
    }
    else
    {
      v28 = (u32)type > 0x1A;
      v29 = (1 << type) & 0x4300000;
      if (v28 || v29 == 0)
        continue;
    }
    firstframeinfo = i->firstframeinfo;
    if (firstframeinfo)
    {
      union0 = 0;
      do
      {
        v34 = i->type;
        if (v34 <= 18)
        {
          if (v34 != 3)
          {
            if (v34 != 18)
              goto LABEL_69;
LABEL_76:
            if (pObjectBasic)
              goto LABEL_80;
            goto LABEL_69;
          }
        }
        else
        {
          if ((v34 & 0xFFFFFFFE) == 0x14)
            goto LABEL_76;
          if (v34 != 26)
            goto LABEL_69;
        }
        union0 = i->object_data->union0;
        Item = get_Item(firstframeinfo->data[0]->c, 0, 0);
        if ((Item & 0x80) == 0)
        {
          pObjectBasic = pInfo->efftable[Item];
          if (pObjectBasic)
          {
LABEL_80:
            v36 = dds3GetBaseControlWorkData(pObjectBasic)->pBasic[1];
            if (v36)
            {
              if (union0)
              {
                frame = 0;
              }
              else
              {
                frame = firstframeinfo->frame;
                union0 = 0;
              }
              evtStopMover(v36, sw, frame, nowframe);
            }
          }
        }
LABEL_69:
        firstframeinfo = firstframeinfo->next;
      }
      while (firstframeinfo);
    }
  }
}

// 0x1a1e3f0
void evtStopFrame(evtViewerInfo_t *pInfo) {
  s32 stat;
  u32 nowframe;

  stat = pInfo->stat;
  nowframe = pInfo->nowframe;
  evtViewerStopFrame((stat & 1) == 0, nowframe, pInfo);
}

// 0x1a1e470
static evtFrameInfo_t *GetNextNearCameraFrame(evtViewerInfo_t *pInfo) {
  evtViewerObject_t *firstobjinfo;
  evtFrameInfo_t *result;
  s32 v5;
  s32 v6;
  evtFrameInfo_t *next;
  s32 nowframe;
  s32 frame;
  bool v10;

  firstobjinfo = pInfo->firstobjinfo;
  if (!firstobjinfo)
    return 0;
  result = 0;
  v5 = 99999;
  do
  {
    if (firstobjinfo->type == 2 && (next = firstobjinfo->firstframeinfo) != 0)
    {
      nowframe = pInfo->nowframe;
      do
      {
        frame = next->frame;
        v6 = frame - nowframe;
        if (v5 < frame - nowframe)
          v6 = v5;
        if (frame <= nowframe)
          v6 = v5;
        v10 = v5 <= frame - nowframe || frame <= nowframe;
        v5 = v6;
        if (!v10)
          result = next;
        next = next->next;
      }
      while (next);
    }
    else
    {
      v6 = v5;
    }
    firstobjinfo = firstobjinfo->next;
    v5 = v6;
  }
  while (firstobjinfo);
  return result;
}

// 0x1a1e500
static void MessageManager(evtViewerInfo_t *pInfo) {
  pmdProcessWork_t *workdata;
  s32 MesHandle;
  s32 v5;
  s32 *IntVariable;
  s64 var_idx;

  workdata = pInfo->workdata;
  if (workdata)
  {
    MesHandle = workdata->MesHandle;
    if (MesHandle != -1)
    {
      if ((itfMesMngGetSelPhase(MesHandle) & 0x80000000) == 0)
        return;
      v5 = pInfo->workdata->MesHandle;
      itfMesMngSetSelPhase(v5, 0);
      IntVariable = GBWK->IntVariable;
      var_idx = pInfo->branch->var_idx;
      IntVariable[var_idx] = itfMesMngGetSelect(pInfo->workdata->MesHandle);
      itfMesMngRequestSelectRelease(pInfo->workdata->MesHandle);
    }
  }
}

// 0x1a129d0
bool evtCompareCutResultValue(s16 res_data) {
  s32 v4;
  s32 v5;

  if ((u16)res_data < 0x1000u)
    return 1;
  v4 = res_data & 0xFFF;
  v5 = (u16)res_data >> 12;
  return GBWK->IntVariable[v5 + 199] == v4;
}

// 0x1a1e630
static s32 DrawMessage(evtViewerInfo_t *pInfo) {
  s32 stat;
  s32 v5;
  pmdProcessWork_t *v7;
  s32 v8;
  s32 Frame;
  s32 real_movie_last_frame;
  s32 v11;
  s32 v12;
  s32 v13;
  s32 v14;
  pmdProcessWork_t *workdata;
  s32 MesHandle;

  stat = pInfo->stat;
  if ((stat & 1) != 0)
    return 0;
  if (pInfo->nowframe >= pInfo->lastframe)
    return 0;
  if (pInfo->nowMovieStat == 1)
  {
    if (drawStart != 2)
      return 0;
    if (pInfo->real_movie_last_frame < 0)
      goto LABEL_52;
    Frame = movieGetFrame();
    if (Frame >= movieGetFrameCount())
    {
      v12 = -1;
      goto LABEL_51;
    }
    real_movie_last_frame = pInfo->real_movie_last_frame;
    if (real_movie_last_frame >= 0)
      v11 = pInfo->real_movie_last_frame;
    else
      v11 = real_movie_last_frame + 1;
    if (Frame != v11 >> 1)
    {
      v12 = 2 * Frame;
      goto LABEL_51;
    }
    if ((real_movie_last_frame & 1) == 0)
    {
      v12 = (2 * Frame) | 1;
LABEL_51:
      pInfo->real_movie_last_frame = v12;
LABEL_52:
      workdata = pInfo->workdata;
      if (!workdata)
        return 1;
      MesHandle = workdata->MesHandle;
      if (MesHandle == -1)
        return 1;
      if (itfMesMngGetPhase(MesHandle) != -1)
        return 1;
      v5 = 1;
      goto LABEL_49;
    }
    return 0;
  }
  v7 = pInfo->workdata;
  if (v7)
  {
    v8 = v7->MesHandle;
    if (v8 != -1)
    {
      if ((stat & 0x100) == 0)
        goto LABEL_16;
      if (itfMesMngChkWaitTag(v8))
        goto LABEL_37;
      v13 = pInfo->workdata->MesHandle;
      if (itfMesMngGetSelPhase(v13) > 0)
LABEL_37:
        v5 = 0;
      else
LABEL_16:
        v5 = 1;
      v14 = pInfo->workdata->MesHandle;
      if (pInfo->last_mestype)
      {
        if (!itfMesMngGetSelPhase(v14))
          goto LABEL_47;
      }
      else
      {
        if (itfMesMngGetPhase(v14) == -1)
        {
LABEL_47:
LABEL_49:
          evtMessageDelete(pInfo, 1);
          return v5;
        }
      }
      return v5;
    }
  }
  return 1;
}

// 0x1a1e940
static void DelAllObjFrame(evtViewerInfo_t *pInfo) {
  evtViewerObject_t *firstobjinfo;
  u32 type;
  evtFrameInfo_t *firstframeinfo;
  s32 v6;
  evtFrameInfo_t *v7;
  s8 Item;
  dds3Basic_t *v9;
  evtFrameInfo_t *v12;
  evtFrameInfo_t *prev;
  void **p_prev;
  evtFrameInfo_t *p_next;
  evtFrameInfo_t *v16;
  evtFrameInfo_t *v17;
  evtFrameInfo_t *p_lastframeinfo;
  Il2CppObject **p_p;
  Il2CppObject *p;
  Il2CppClass **v21;
  evtViewerObject_t *next;

  _SetDefTex(PartialMultiBlur);
  _SetDefTex(DistortionBlur);
  _SetDefTex(RippleBlur);
  _SetDefTex(PartialMultiFilter);
  firstobjinfo = pInfo->firstobjinfo;
  if (firstobjinfo)
  {
    do
    {
      next = firstobjinfo->next;
      type = firstobjinfo->type;
      if (type)
      {
        if (type - 4 > 0xFFFFFFFC || type <= 0x1A && ((1 << type) & 0x5340000) != 0)
        {
          firstframeinfo = firstobjinfo->firstframeinfo;
          if (firstframeinfo)
          {
            do
            {
              v6 = firstobjinfo->type;
              v7 = firstframeinfo->next;
              if (v6 <= 18)
              {
                if (v6 != 3)
                  goto LABEL_26;
              }
              else if (v6 != 26)
              {
                goto LABEL_26;
              }
              if (get_Item(firstframeinfo->data[0]->c, 0, 0) < 0)
              {
LABEL_26:
                goto LABEL_27;
              }
              Item = get_Item(firstframeinfo->data[0]->c, 0, 0);
              v9 = pInfo->efftable[Item];
              if (!v9)
                goto LABEL_26;
              dds3SceneBasicDelete(v9);
              v21 = &pInfo->efftable->obj.klass + Item;
              v21[4] = 0;
LABEL_27:
              v12 = firstframeinfo->next;
              p_prev = &firstframeinfo->prev;
              prev = firstframeinfo->prev;
              if (prev)
                p_next = &prev->next;
              else
                p_next = &firstobjinfo->firstframeinfo;
              p_next = v12;
              v16 = firstframeinfo->next;
              v17 = *p_prev;
              if (v16)
                p_lastframeinfo = &v16->prev;
              else
                p_lastframeinfo = &firstobjinfo->lastframeinfo;
              p_lastframeinfo = v17;
              *p_prev = 0;
              firstframeinfo->next = 0;
              --firstobjinfo->framecnt;
              p = firstframeinfo->p;
              p_p = &firstframeinfo->p;
              if (p)
              {
                *p_p = 0;
              }
              firstframeinfo = v7;
            }
            while (v7);
          }
        }
        else
        {
          sub_1A22530(firstobjinfo, pInfo, 0);
        }
      }
      firstobjinfo = next;
    }
    while (next);
  }
  dds3PadActAllStop();
}

// 0x1a1ed40
static void UnitMotionChangeForWait(s32 nowframe, dds3Basic_t *b, evtViewerObject_t *obj, evtViewerInfo_t *pInfo) {
  dds3ModelHandle_t *v8;
  void *workdata;
  dds3ModelHandle_t *v11;
  s32 i;
  sdfMotionCtrlr_t *MotionCtrlr;
  s8 Item;
  s8 v16;
  evtFrameInfo_t *v18;
  evtFrameInfo_t *v20;
  s32 v21;

  v8 = Allocate(dds3ModelHandle_t);
  _ctor(v8, 0);
  workdata = b->workdata;
  v11 = *((dds3ModelHandle_t *)workdata[2].monitor + 5);
  if (!mdlHasMotion(v11))
    return;
  goto LABEL_13;
  if (mdlHasMotion(v11))
  {
LABEL_13:
    for (i = 0; i != 4; ++i)
    {
      if (!mdlGetMotionCtrlr(v11, i))
        continue;
      mdlGetMotionCtrlr(v11, i)->speed = 0.5;
      v18 = GetUnitMotionChangeFrame(obj, nowframe, i);
      if (v18)
      {
        v20 = v18;
        if (mdlGetMotionCtrlr(v11, i)->stat == 5 && get_Item(v20->data[5]->c, 0, 0))
        {
          v21 = get_Item(v20->data[5]->c, 2, 0) == 0;
          MotionCtrlr = mdlGetMotionCtrlr(v11, i);
          Item = get_Item(v20->data[5]->c, 1, 0);
          v16 = get_Item(v20->data[5]->c, 3, 0);
          sdfMotionChangeBlend(MotionCtrlr, Item, v21, 0.0, (f32)v16);
        }
      }
    }
  }
}

// 0x1a1f050
static void evtValidateUnitMotionFrameForWait(s32 nowframe, evtViewerInfo_t *pInfo) {
  void *workdata;
  evtViewerInfo_t *v7;
  dds3Basic_t *next;
  evtViewerObject_t *firstobjinfo;

  if (!dds3GetActiveScene())
    return;
  workdata = dds3GetActiveScene()->workdata;
  if (!workdata)
  next = *(dds3Basic_t *)(*((u64 *)workdata[1].monitor + 9) + 24);
  if (next)
  {
    firstobjinfo = pInfo->firstobjinfo;
    if (firstobjinfo)
    {
LABEL_15:
      while (firstobjinfo->basic != next)
      {
        firstobjinfo = firstobjinfo->next;
        if (!firstobjinfo)
          goto LABEL_21;
      }
      UnitMotionChangeForWait(nowframe, next, firstobjinfo, v7);
LABEL_21:
      while (1)
      {
        next = next->next;
        if (!next)
          break;
        firstobjinfo = pInfo->firstobjinfo;
        if (firstobjinfo)
          goto LABEL_15;
      }
    }
    else
    {
      do
        next = next->next;
      while (next);
    }
  }
}

// 0x1a1f1e0
static dds3ProcessFunc_t Process3(dds3ProcessID_t *id) {
  Il2CppObject *ProcessData;
  s32 monitor;
  s32 v8;
  void *v14;
  s32 v16;
  void *Instance;
  void *v18;
  s32 *v20;
  void *v22;
  s32 klass;
  u32 monitor_high;
  s32 v29;
  s32 v30;
  s32 v31;
  char v33;
  s32 v35;
  char v36;
  dds3ProcessFunc_t v37;
  long f64 v41;
  s32 v42;
  void *v46;
  s32 v47;
  s32 klass_high;
  pmdProcessWork_t *v53;
  pmdSeqData_t *Item;
  pmdSeqData_t *v55;
  pmdProcessWork_t *v56;
  u32 *v58;
  s64 v59;
  char *v60;
  dds3ProcessID_t *ida;

  ida = id;
  ProcessData = dds3GetProcessData(ida);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  winoff_x = 0;
  if ((BYTE1(ProcessData[1].klass) & 4) != 0)
    goto LABEL_22;
  if (SHIDWORD(ProcessData[2].monitor) >= LODWORD(ProcessData[2].monitor) - 3)
    goto LABEL_22;
  monitor = ProcessData[12].monitor;
  if (monitor >= 1)
  {
    if (monitor + 1 < 30)
      v8 = monitor + 1;
    else
      v8 = 0;
    LODWORD(ProcessData[12].monitor) = v8;
  }
LABEL_22:
  DrawEffect(ProcessData);
  evtGuideCtrl();
  if (!itfIsPmvSkipAndPause())
    goto LABEL_44;
  if (((s64)ProcessData[1].klass & 0x10) != 0)
    goto LABEL_44;
  if (scrCheckEnableMovieCancel())
    goto LABEL_45;
  if (is_Direction2)
    goto LABEL_45;
LABEL_44:
  if (skpStopEnable == 1)
    goto LABEL_45;
  Instance = get_Instance(0);
  if (!Is_uiOffGaugeDisp(Instance, 0))
    goto LABEL_62;
  v22 = get_Instance(0);
  uiOffGaugeOff(v22, 1, 0);
LABEL_62:
  v20 = (s32 *)&ProcessData[2].monitor + 1;
  if (HIDWORD(ProcessData[2].monitor) == HIDWORD(ProcessData[2].klass))
    goto LABEL_63;
  if (sBtlIsContiune())
    goto LABEL_81;
  if (sBtlIsLevelContiune())
    goto LABEL_81;
  if (sBtlIsGiveUp())
    goto LABEL_81;
  if (LODWORD(ProcessData[17].monitor) != 1)
    goto LABEL_98;
  goto LABEL_88;
LABEL_45:
  v14 = get_Instance(0);
  v16 = UIoffProc(v14, 1, 0);
  gAns = v16;
  if (v16 != 2)
    goto LABEL_62;
  v18 = get_Instance(0);
  uiOffGaugeOff(v18, 1, 0);
  v20 = (s32 *)&ProcessData[2].monitor + 1;
  if (HIDWORD(ProcessData[2].monitor) == HIDWORD(ProcessData[2].klass))
  {
LABEL_63:
    LODWORD(ProcessData[1].klass) &= ~1u;
    klass = ProcessData[1].klass;
    monitor_high = HIDWORD(ProcessData[2].monitor);
    evtViewerStopFrame((klass & 1) == 0, monitor_high, ProcessData);
    if (LODWORD(ProcessData[17].monitor) != 1)
      goto LABEL_98;
    goto LABEL_88;
  }
LABEL_81:
  EventSkipStart(ProcessData);
  if (LODWORD(ProcessData[17].monitor) != 1)
    goto LABEL_98;
LABEL_88:
  if (((s64)ProcessData[1].klass & 0x10) != 0)
    goto LABEL_98;
  if (!sndVoiceStatus(0))
  {
    v29 = HIDWORD(ProcessData[17].monitor);
    v30 = *((u32 *)ProcessData[1].monitor + 10);
    itfMesMngRequestMessage(v30, v29, 0, 0, 0);
    LODWORD(ProcessData[17].monitor) = 0;
  }
LABEL_98:
  v31 = HIDWORD(ProcessData[2].monitor);
  if (v31 == LODWORD(ProcessData[3].klass))
  {
    if (((s64)ProcessData[1].klass & 1) != 0)
    {
      goto LABEL_104;
    }
    evtValidateUnitMotionFrameForWait(v31, ProcessData);
LABEL_104:
    v33 = sub_1A24D60(ProcessData, 0);
    v35 = HIDWORD(ProcessData[2].monitor);
    if ((v33 & 1) == 0)
      goto LABEL_111;
    goto LABEL_110;
  }
  else
  {
    evtRunFrame(v31, ProcessData);
    goto LABEL_104;
  }
  v36 = sub_1A24D60(ProcessData, 0);
  v35 = HIDWORD(ProcessData[2].monitor);
  if ((v36 & 1) == 0)
    goto LABEL_111;
LABEL_110:
  v37 = 0;
  if (v35 < 2)
    return v37;
LABEL_111:
  LODWORD(ProcessData[3].klass) = v35;
  if (((s64)ProcessData[1].klass & 8) == 0)
  {
    goto LABEL_113;
  }
  SetActiveCamera(ProcessData);
LABEL_113:
  MessageManager(ProcessData);
  EventSkipFilterManager(ProcessData);
  v42 = ProcessData[1].klass;
  if ((v42 & 8) == 0)
    goto LABEL_126;
  if ((v42 & 0x20) != 0)
  {
    v37 = 0;
    if (evtChkLoad(1))
      return v37;
    v46 = get_Instance(0);
    uiOffGaugeOff(v46, 1, 0);
LABEL_133:
    v37 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
    _ctor(v37, 0, Method_Project_Kernel_DDS3_PROC_END__, 0);
    return v37;
  }
  if (SHIDWORD(ProcessData[2].monitor) >= SLODWORD(ProcessData[2].monitor))
  {
    v42 |= 0x80u;
    LODWORD(ProcessData[1].klass) = v42;
  }
  if ((v42 & 0x40) != 0)
  {
    if (LODWORD(ProcessData[13].klass) != 1)
    {
LABEL_147:
      LODWORD(ProcessData[1].klass) = v42 & 0xFFFFFF3F;
      klass_high = HIDWORD(ProcessData[18].klass);
      *((u32 *)ProcessData[1].monitor + 16) = klass_high;
      DelAllObjFrame(ProcessData);
      v53 = ProcessData[1].monitor;
      Item = get_Item(v53->pm2data, klass_high, 0);
      v55 = get_Item(*((pmdSeqTable_t *)ProcessData[1].monitor + 14), klass_high, 0);
      evtGetWorkData2and3(v53, Item, v55);
      v56 = ProcessData[1].monitor;
      evtSetGameData2and3(v56, ProcessData, 1);
      return 0;
    }
    movieStop(0);
    v42 = ProcessData[1].klass;
    ProcessData[13].klass = 0;
    LODWORD(ProcessData[13].monitor) = 0;
    LODWORD(ProcessData[19].klass) = -1;
    goto LABEL_147;
  }
  v42 = ProcessData[1].klass;
  if ((v42 & 0x10) != 0 && SLODWORD(ProcessData[9].monitor) >= 25)
  {
    v58 = ProcessData[1].monitor;
    if (v58[5] == 690 && v58[6] == 5)
    {
      v59 = sub_1A24F60(0, v41);
      v60 = sub_8360(1, Project_DefineAchievementID_string_, v59);
      Unlock_2(v60);
    }
    goto LABEL_133;
  }
LABEL_126:
  if (s_IsPause)
    return 0;
  v47 = *v20;
  v37 = 0;
  HIDWORD(ProcessData[2].monitor) = DrawMessage(ProcessData) + v47;
  return v37;
}

// 0x1a200d0
bool evtIsPMVGuideDraw(void) {
  return ButtonGuideFlag;
}

// 0x1a1fc90
void evtGuideCtrl(void) {
  if (itfIsPmvSkipAndPause())
  {
    if (is_Direction2)
    {
      if (is_CombineFlag)
      {
LABEL_17:
        itfPmvButtonGuideCtrl(1);
        itfSetGuideAnimPMV(0);
        ButtonGuideFlag = 1;
        return;
      }
      goto LABEL_17;
    }
    if (!CheckPlayerCtrl())
    {
      if (!CHECK_PRESS(36878, 1))
      {
        goto LABEL_43;
      }
    }
    itfPmvButtonGuideCtrl(1);
    itfMesGuideLineCtrl(1);
    itfSetGuideAnimPMV(0);
    ButtonGuideFlag = 1;
    ButtonGuideCount = 0;
    itfSetMesGuideLineAnimPMV(0);
    if (!ButtonGuideFlag)
      return;
    goto LABEL_51;
LABEL_43:
    if (!ButtonGuideFlag)
      return;
LABEL_51:
    if (ButtonGuideCount < 120)
    {
LABEL_54:
      ++ButtonGuideCount;
      return;
    }
    itfSetGuideAnimPMV(1);
    itfSetMesGuideLineAnimPMV(1);
    ButtonGuideFlag = 0;
    ButtonGuideCount = 0;
    goto LABEL_54;
  }
  itfPmvButtonGuideCtrl(0);
}

// 0x1a20150
static dds3ProcessFunc_t Process2(dds3ProcessID_t *id) {
  dds3ProcessID_t *v2;
  evtViewerInfo_t *ProcessData;
  s32 nowframe;
  s32 stat;
  u32 v10;
  long f64 v11;
  long f64 v16;
  s32 v17;
  dds3ProcessID_t *v21;
  void *Instance;
  dds3ProcessFunc_t v25;
  dds3ProcessID_t *ida;

  ida = id;
  v2 = Allocate(dds3ProcessID_t);
  _ctor(v2, 0);
  ProcessData = dds3GetProcessData(ida);
  if (!ProcessData)
  if (!evtProcessStart(0, 0))
  {
    nowframe = ProcessData->nowframe;
    evtRunFrame(nowframe, ProcessData);
    stat = ProcessData->stat;
    v10 = ProcessData->nowframe;
    evtViewerStopFrame((stat & 1) == 0, v10, ProcessData);
  }
  if (evtChkLoad(1))
  {
LABEL_17:
    DrawFlag |= 0x2000000u;
    return 0;
  }
  if ((sub_1A24FF0(ProcessData, 0, v11) & 1) != 0)
    goto LABEL_17;
  v17 = ProcessData->nowframe;
  evtRunFrame(v17, ProcessData);
  play = 1;
  v21 = ida;
  pmv_pid = ida;
  DrawFlag = DrawFlag | 0x2000000;
  last_skip_stat = 0;
  Instance = get_Instance(0);
  uiOffGaugeOff(Instance, 1, 0);
  v25 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
  _ctor(v25, 0, Method_Project_evtViewer_Process3__, 0);
  return v25;
}

// 0x1a204b0
dds3ProcessFunc_t evtProcess2_RealPlay(dds3ProcessID_t *id) {
  evtViewerInfo_t *ProcessData;
  pmdProcessWork_t *workdata;
  pmdProcessWork_t *v6;
  s32 flag;
  dds3ProcessFunc_t v9;
  pmdLoadScene *loadScene;
  s64 i;
  pmdLoadScene *v12;
  void *bg;
  void *v14;
  void *filterParam;
  s32 setting;
  dds3ProcessID_t *ida;

  ida = id;
  ProcessData = dds3GetProcessData(ida);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  workdata = ProcessData->workdata;
  evtCheckLoad(ProcessData->workdata);
  v6 = ProcessData->workdata;
  flag = v6->flag;
  if ((flag & 8) == 0)
  {
    v9 = 0;
    DrawFlag |= 0x2000000u;
    return v9;
  }
  if ((flag & 1) != 0)
    return 0;
  evtSetGameData1(v6, ProcessData);
  evtSetGameData2and3(ProcessData->workdata, ProcessData, 0);
  loadScene = ProcessData->workdata->loadScene;
  if (SLODWORD(loadScene->max_length) >= 1)
  {
    for (i = 0; i < SLODWORD(loadScene->max_length); ++i)
    {
      v12 = loadScene[i];
      bg = v12->bg;
      if (!op_Inequality(v12->bg, 0, 0))
        continue;
      v14 = v12->bg;
      filterParam = v14->filterParam;
      if (filterParam)
      {
        setting = filterParam->setting;
        if ((setting & 2) != 0)
          v14->filterEnable = 0;
        if ((setting & 4) != 0)
          v14->filterAnimEnable = 0;
      }
    }
  }
  DrawFlag |= 0x2000000u;
  v9 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
  _ctor(v9, 0, Method_Project_evtViewer_Process2__, 0);
  return v9;
}

// 0x1a207e0
bool evtFilterTempSetting(void *_bgStatus) {
  void *filterParam;
  s32 setting;

  filterParam = bgStatus->filterParam;
  if (filterParam)
  {
    setting = filterParam->setting;
    if ((setting & 2) != 0)
      bgStatus->filterEnable = 0;
    if ((setting & 4) != 0)
      bgStatus->filterAnimEnable = 0;
  }
  return filterParam != 0;
}

// 0x1a20810
void evtFilterTempSettingClear(pmdLoadScene *_loadScene) {
  void *bg;

  bg = loadScene->bg;
  if (!op_Inequality(bg, 0, 0))
    return;
  goto LABEL_4;
  if (op_Inequality(bg, 0, 0))
LABEL_4:
    FilterTempSettingAllClear(loadScene->bg, 0);
}

// 0x1a208c0
dds3ProcessFunc_t evtProcess1_RealPlay(dds3ProcessID_t *id) {
  evtViewerInfo_t *ProcessData;
  pmdProcessWork_t *workdata;
  s32 v8;
  s32 EventNo;
  s32 stat;
  u32 nowframe;
  s32 v14;
  dds3ProcessFunc_t v18;
  dds3ProcessID_t *ida;

  ida = id;
  start = 1;
  ProcessData = dds3GetProcessData(ida);
  if (!ProcessData)
    goto LABEL_11;
  goto LABEL_9;
  if (!ProcessData)
LABEL_9:
LABEL_11:
  workdata = ProcessData->workdata;
  v8 = 1;
  EventNo = workdata->EventNo;
  file_minor = workdata->CutNo;
  LODWORD(workdata) = ProcessData->stat;
  file_major = EventNo;
  ProcessData->stat = (u32)workdata | 1;
  stat = ProcessData->stat;
  v8 = stat & 1;
  nowframe = ProcessData->nowframe;
  evtViewerStopFrame(v8 == 0, nowframe, ProcessData);
  v14 = ProcessData->stat;
  ProcessData->framedisp = 0;
  ProcessData->stat = v14 | 8;
  DrawFlag |= 0x2000000u;
  v18 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
  _ctor(v18, 0, Method_Project_evtViewer_Process2_RealPlay__, 0);
  return v18;
}

// 0x1a20b00
static bool ChkIgnoreBgmFadeOutEvent(pmdProcessWork_t *wdata) {
  return 0;
}

// 0x1a20b10
static void End(evtViewerInfo_t *pInfo) {
  void *volume;
  void *v10;
  pmdProcessWork_t *workdata;
  Il2CppObject *Component_object;
  pmdProcessWork_t *v17;
  pmdPM1_t *pm1;
  s64 v19;
  pmdUnitTable_t *v20;
  u16 MajorNum;
  s32 MinorNum;

  volume = pInfo->workdata->volume;
  if (!op_Inequality(volume, 0, 0))
  {
    goto LABEL_6;
  }
  v10 = pInfo->workdata->volume;
  Destroy_61007920(v10, 0);
  workdata = pInfo->workdata;
  workdata->volume = 0;
  Component_object = GetComponent_object_(cameraObject->_camera);
  HIDWORD(Component_object[3].monitor) = op_Implicit_60988480(0, 0);
LABEL_6:
  evtInitCustomSceneLight();
  evtMessageDelete(pInfo, 0);
  evtDeleteZikkiEventMes(pInfo);
  dds3StopQuake();
  *(u64 *)&CameraOffset.x = 0;
  *(u64 *)&CameraOffset.z = 0;
  if (pInfo->nowMovieStat == 1)
  {
    if (pInfo->MovieEndFrame == -2)
    {
      if ((pInfo->stat & 0x10) == 0)
        goto LABEL_28;
      goto LABEL_9000;
      if ((pInfo->stat & 0x10) == 0)
      {
LABEL_28:
        pInfo->nowMovieStat = 0;
        goto LABEL_29;
      }
LABEL_9000:
    }
    movieStop(0);
    goto LABEL_28;
  }
LABEL_29:
  frame = 0x7FFFFFFF;
  evtFreeStage();
  v17 = pInfo->workdata;
  if (v17)
  {
    pm1 = v17->pm1;
    if (pm1->UnitCount >= 1)
    {
      v19 = 0;
      do
      {
        v20 = pm1->UnitTable[v19];
        MajorNum = v20->MajorNum;
        MinorNum = v20->MinorNum;
        mdlUnRegist(MajorNum, MinorNum);
        ++v19;
        pm1 = pInfo->workdata->pm1;
      }
      while (v19 < pm1->UnitCount);
    }
  }
  FreeInfo(pInfo);
  dds3ChangeBistaMode(0);
  DrawFlag |= 0x2000000u;
  dds3SetScreenFovy(0.62831855);
  *(u64 *)&ScreenParam->ox = 0x4500000045000000LL;
  evtProcessEnd();
  pmv_pid = 0;
  *(u16 *)&start = 0;
  skyFilterSet = 0;
  sdfMemRelease();
}

// 0x1a20f50
void evtShutdown_RealPlayMode(dds3ProcessID_t *id) {
  evtViewerInfo_t *ProcessData;
  dds3ProcessID_t *ida;

  ida = id;
  ProcessData = dds3GetProcessData(ida);
  if (!ProcessData)
  End(ProcessData, evtViewerInfo_t);
}

// 0x1a21040
void evtInitZikkiEvent(evtViewerInfo_t *pInfo) {
  evtCreateZikkiEventMes(pInfo);
}

// 0x1a0ec50
void evtEnd(dds3ProcessID_t *id) {
  Il2CppObject *ProcessData;
  dds3ProcessID_t *ida;

  ida = id;
  ProcessData = dds3GetProcessData(ida);
  if (!ProcessData)
    return;
  LODWORD(ProcessData[1].klass) |= 0x20u;
}

// 0x1a0eea0
void evtChgSeq(dds3ProcessID_t *id, s32 no, s32 ignoreNum) {
  Il2CppObject *ProcessData;
  s32 klass;
  dds3ProcessID_t *ida;

  ida = id;
  ProcessData = dds3GetProcessData(ida);
  if (!ProcessData)
    return;
  if (no)
  {
    klass = ProcessData[1].klass;
    LODWORD(ProcessData[19].monitor) = ignoreNum;
    HIDWORD(ProcessData[18].klass) = no - 1;
    LODWORD(ProcessData[1].klass) = klass & 0xFFFFFD3F | 0x40;
    HIDWORD(ProcessData[7].monitor) = -1;
  }
}

// 0x1a210d0
void evtIgnoreFade(dds3ProcessID_t *id) {
  Il2CppObject *ProcessData;
  dds3ProcessID_t *ida;

  ida = id;
  ProcessData = dds3GetProcessData(ida);
  if (!ProcessData)
    return;
  LODWORD(ProcessData[1].klass) |= 0x200u;
}

// 0x1a211c0
void evtNoSkipMes(dds3ProcessID_t *id) {
  Il2CppObject *ProcessData;
  dds3ProcessID_t *ida;

  ida = id;
  ProcessData = dds3GetProcessData(ida);
  if (!ProcessData)
    return;
  LODWORD(ProcessData[1].klass) |= 0x400u;
}

// 0x1a212b0
s32 evtCheckProcess(void) {
  return pmv_pid != 0;
}

// 0x1a21320
s32 evtCheckLastSkipStat(void) {
  return last_skip_stat;
}

// 0x1a213a0
void evtSkipStart(dds3ProcessID_t *id) {
  evtViewerInfo_t *ProcessData;
  dds3ProcessID_t *ida;

  ida = id;
  ProcessData = dds3GetProcessData(ida);
  if (!ProcessData)
  EventSkipStart(ProcessData);
}

// 0x1a21490
s32 evtSetFrame(dds3ProcessID_t *id, s32 Frame) {
  s32 *ProcessData;
  dds3ProcessID_t *ida;

  ida = id;
  ProcessData = dds3GetProcessData(ida);
  if (!ProcessData)
    return -1;
  if (Frame < 0)
    return ProcessData[11];
  ProcessData[11] = Frame;
  ProcessData[31] = -1;
  return Frame;
}

// 0x1a215b0
void evtIgnoreAtracPlay(dds3ProcessID_t *id) {
  Il2CppObject *ProcessData;
  dds3ProcessID_t *ida;

  ida = id;
  ProcessData = dds3GetProcessData(ida);
  if (!ProcessData)
    return;
  LODWORD(ProcessData[1].klass) |= 0x800u;
}
