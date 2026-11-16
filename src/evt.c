#include "types.h"
#include "ActionDelegate.h"
#include "EVT_UNIT_MOVE_TYPE.h"
#include "MODELTYPE.h"
#include "dat.h"
#include "dds3areabasic.h"
#include "dds3basic.h"
#include "dds3cameraobjectbasic.h"
#include "dds3effect.h"
#include "dds3kernelcore.h"
#include "dds3kerneldraw.h"
#include "dds3moverbasic.h"
#include "dds3objectbase.h"
#include "dds3pathbasic.h"
#include "dds3scenebasic.h"
#include "dds3unitobjectbasic.h"
#include "dds3worldbasic.h"
#include "egl.h"
#include "event.h"
#include "evt.h"
#include "evtbit.h"
#include "evtpmv.h"
#include "evtsound.h"
#include "evtviewer.h"
#include "fld.h"
#include "itf.h"
#include "itfmisc.h"
#include "kernel.h"
#include "mdl.h"
#include "scr.h"
#include "sdf3d.h"
#include "sdf_gs_alpha.h"
#include "sdf_vu0.h"
#include "sdfdraw.h"
#include "sdfmodel.h"
#include "sdfprim.h"
#include "sdfquat.h"
#include "sdftex.h"

#define EVT_BEFORE_FRAME 0
#define EVT_SMOOTH_FRAME 10
#define EVT_MOVEEND_R 20
#define EVT_PATH_TARGET_LENGTH 40

typedef enum {
    EVT_RAIN_FLAG_NONE = 0,
    EVT_RAIN_FLAG_LOAD = 1,
    EVT_RAIN_FLAG_END = 2,
    EVT_RAIN_FLAG_DRAW_OFF = 4,
    EVT_RAIN_FLAG_LOAD_BLOCKMODE = 8,
} EVT_RAIN_FLAG;

typedef struct BUSTUP_POS_TBL_t BUSTUP_POS_TBL_t;
typedef struct CustomSceneLightInfo CustomSceneLightInfo;
typedef struct dds3Basic_t dds3Basic_t;
typedef struct dds3ModelHandle_t dds3ModelHandle_t;
typedef struct dds3PathBasicControl_t dds3PathBasicControl_t;
typedef struct dds3PoseSet_t dds3PoseSet_t;
typedef struct dds3ProcessID_t dds3ProcessID_t;
typedef struct evtBustupLight_t evtBustupLight_t;
typedef struct evtCrossFade_t evtCrossFade_t;
typedef struct evtFrameInfo_t evtFrameInfo_t;
typedef struct evtRain_t evtRain_t;
typedef struct evtUnitHandle_t evtUnitHandle_t;
typedef struct evtViewerInfo_t evtViewerInfo_t;
typedef struct evtViewerObject_t evtViewerObject_t;
typedef struct pmdDataInfo_t pmdDataInfo_t;
typedef struct pmdObjectTable_t pmdObjectTable_t;
typedef struct pmdProcessWork_t pmdProcessWork_t;
typedef struct pmdSceneLightTable_t pmdSceneLightTable_t;
typedef struct pmdTmxData_t pmdTmxData_t;
typedef struct sdf3DLightParallelPacket_t sdf3DLightParallelPacket_t;
typedef struct sdf3DLight_t sdf3DLight_t;
typedef struct sdfBinary sdfBinary;
typedef struct sdfIVector2_t sdfIVector2_t;
typedef struct sdfIVector4_t sdfIVector4_t;

struct evtCrossFade_t {
    u32 Stat;
    s32 Timer;
    s32 Length;
    void *mesh;
};

struct evtRain_t {
    EVT_RAIN_FLAG Flag;
};

struct CustomSceneLightInfo {
    SCENELIGHT LightType;
    evtUnitHandle_t *UnitHandle;
    sdfVector4_t Color[3];
    sdfVector4_t Dir[3];
    sdfVector4_t Ambient;
    f32 Soften;
    f32 Bias;
};

s32 NextEventNo;
BUSTUP_POS_TBL_t *bustup_pos_tbl;
evtBustupLight_t *bustup_light_tbl;
static sdfIVector4_t dtex_pos;
static sdfIVector4_t dtex_uv;
static sdfColor32_t dtex_color;
static dds3ProcessID_t *evtCrossFadePID;
static s32 evtCrossFadeProcCnt;
static dds3ProcessID_t *evtRainPID;
static s32 bustup_pos_Size;
static sdf3DLight_t *fld_default_light;
static sdfVector4_t fld_default_ambient;
static char *evtStartEvent_path;
s32 *bustup_lightno;
s32 bustup_sid0;
s32 bustup_sid1;
static CustomSceneLightInfo *CustomSceneLightArray;
bool IsEvtMoveCollisionCheck;

static void SetSlightDefaultValue(sdfVector4_t *Color, sdfVector4_t *Dir, sdfVector4_t *Ambient, f32 *pSoften, f32 *pBias);
static void SetDefaultTmxData(pmdTmxData_t *out_tmxdata);
static void FindNearFrameAndAfterFrame(evtViewerObject_t *obj, s32 nowframe, evtFrameInfo_t *out_nearframe, evtFrameInfo_t *out_frame);
static void *GetScreen(void);
static void ReleaseScreen(void *mesh);
static void DrawPrimitive2Core(const sdfVector4_t *Col, void *mesh, DDS3_OT OtNo);
static dds3ProcessFunc_t CrossFadeProcess(dds3ProcessID_t *PID);
static dds3ProcessFunc_t CrossFadeCreateTexProcess(dds3ProcessID_t *PID);
static void CrossFadeShutdown(dds3ProcessID_t *PID);
static dds3ProcessFunc_t RainProcess(dds3ProcessID_t *PID);
static dds3ProcessFunc_t RainLoadProcess(dds3ProcessID_t *PID);
static void DestroyRain(dds3ProcessID_t *PID);
static PMD_OBJTYPE GetFrameObjectType(pmdProcessWork_t *wdata, s32 index);
static s16 GetFrameNameIndex(pmdProcessWork_t *wdata, s32 index);
static u16 GetFrameFrameNo(pmdProcessWork_t *wdata, s32 index);
static u16 GetFrameLength(pmdProcessWork_t *wdata, s32 index);
static pmdDataInfo_t *GetFrameData(pmdProcessWork_t *wdata, s32 index);
static void Vu0SubVectorXZAxis(const sdfVector4_t *a, const sdfVector4_t *b);
static void GetUnitDirVector(evtUnitHandle_t *h);
static bool CheckMoveEnd(evtUnitHandle_t *h);
static bool GetNextMovePos(evtUnitHandle_t *h);
static f32 GetSplineLength(dds3PathBasicControl_t *path);
static void GetBaseLightRGB(evtUnitHandle_t *h);
static void GetBaseLightRGB1(evtUnitHandle_t *h);
static void GetBaseLightRGB2(evtUnitHandle_t *h);
static void GetBaseLightRGB_2(evtUnitHandle_t *h, u32 col, const sdfVector4_t *col1);
static void GetBaseAmbientRGB(evtUnitHandle_t *h);
static void GetBaseLightDir(evtUnitHandle_t *h);
static void GetBaseLightDir1(evtUnitHandle_t *h);
static void GetBaseLightDir2(evtUnitHandle_t *h);
static void GetBaseLightDir_2(evtUnitHandle_t *h, const sdfVector4_t *col1, const sdfVector4_t *col2);
static void MakeLightPacket(evtUnitHandle_t *h);
static bool CheckMoveEndBustup(evtUnitHandle_t *h);
static bool UnitMoveTypeBustup(evtUnitHandle_t *h);
static CustomSceneLightInfo *NewCustomSceneLight(void);
static CustomSceneLightInfo *GetCustomSLightIndex(evtUnitHandle_t *h);

// 0x19b2880
void evtAllObjectAdjustFrame(evtViewerInfo_t *pInfo, s32 addvalue, s32 nowframe) {
  s32 v4;
  s32 v8;
  s32 v9;
  evtViewerObject_t *firstobjinfo;
  evtFrameInfo_t *firstframeinfo;
  s32 frame;
  s32 Offset;
  s32 v14;
  s32 v15;
  s32 type;
  s32 totalframe;
  pmdDataInfo_t **p_data;
  DataS *v19;
  s16 v20;
  s32 v21;
  s32 v22;
  DataS *s;
  s16 Item;
  s32 v25;

  if (pInfo->objcnt >= 1)
  {
    v4 = pInfo->nowframe;
    v8 = pInfo->lastframe + addvalue;
    if (v8 < 0)
      v8 = 10;
    pInfo->lastframe = v8;
    v9 = pInfo->totalframe + addvalue;
    if (v9 < 0)
      v9 = 10;
    pInfo->totalframe = v9;
    if (v4 > v9)
      pInfo->nowframe = v9;
    firstobjinfo = pInfo->firstobjinfo;
    if (!firstobjinfo)
    {
LABEL_9:
      --pInfo->oldframe;
      return;
    }
    while (1)
    {
      firstframeinfo = firstobjinfo->firstframeinfo;
      if (firstframeinfo)
        break;
LABEL_11:
      firstobjinfo = firstobjinfo->next;
      if (!firstobjinfo)
        goto LABEL_9;
    }
    while (1)
    {
      frame = firstframeinfo->frame;
      Offset = firstobjinfo->object_data->Offset;
      v14 = Offset + frame;
      if (Offset + frame < nowframe)
        goto LABEL_14;
      v15 = v14 + addvalue;
      if (v14 + addvalue >= Offset)
      {
        totalframe = pInfo->totalframe;
        if (totalframe >= v15)
        {
          firstframeinfo->frame = frame + addvalue;
          type = firstobjinfo->type;
          if (type <= 18)
          {
LABEL_21:
            if (type == 3)
              goto LABEL_27;
            goto LABEL_14;
          }
        }
        else
        {
          firstframeinfo->frame = totalframe + ~(u16)Offset;
          type = firstobjinfo->type;
          if (type <= 18)
            goto LABEL_21;
        }
      }
      else
      {
        firstframeinfo->frame = 0;
        type = firstobjinfo->type;
        if (type <= 18)
          goto LABEL_21;
      }
      if ((type & 0xFFFFFFFE) != 0x14)
      {
        if (type == 33)
        {
          p_data = &firstframeinfo->data;
          if (!get_Item(firstframeinfo->data[0]->s, 0, 0))
            goto LABEL_14;
          s = (*p_data)[0]->s;
          Item = get_Item(s, 0, 0);
          set_Item(s, 0, Item + addvalue, 0);
          if (get_Item((*p_data)[0]->s, 0, 0) < 0)
            set_Item((*p_data)[0]->s, 0, 0, 0);
          v25 = pInfo->totalframe;
          v22 = 0;
          if (v25 >= addvalue + get_Item((*p_data)[0]->s, 0, 0))
            goto LABEL_14;
LABEL_36:
          set_Item((*p_data)[0]->s, v22, LOWORD(pInfo->totalframe) - 1, 0);
          goto LABEL_14;
        }
        if (type == 26)
        {
LABEL_27:
          p_data = &firstframeinfo->data;
          if (!get_Item(firstframeinfo->data[0]->s, 1, 0))
            goto LABEL_14;
          v19 = (*p_data)[0]->s;
          v20 = get_Item(v19, 1, 0);
          set_Item(v19, 1, v20 + addvalue, 0);
          if (get_Item((*p_data)[0]->s, 1, 0) < 0)
            set_Item((*p_data)[0]->s, 1, 0, 0);
          v21 = pInfo->totalframe;
          v22 = 1;
          if (v21 >= addvalue + get_Item((*p_data)[0]->s, 1, 0))
            goto LABEL_14;
          goto LABEL_36;
        }
      }
LABEL_14:
      firstframeinfo = firstframeinfo->next;
      if (!firstframeinfo)
        goto LABEL_11;
    }
  }
}

// 0x19b2b70
static void SetSlightDefaultValue(sdfVector4_t *Color, sdfVector4_t *Dir, sdfVector4_t *Ambient, f32 *pSoften, f32 *pBias) {
  Color[0] = (sdfVector4_t)xmmword_3D05D20;
  Dir[0] = (sdfVector4_t)xmmword_3CFCD20;
  Color[1] = (sdfVector4_t)xmmword_3D05D20;
  Dir[1] = (sdfVector4_t)xmmword_3CFCD20;
  Color[2] = (sdfVector4_t)xmmword_3D05D20;
  Dir[2] = (sdfVector4_t)xmmword_3CFCD20;
  *Ambient = (sdfVector4_t)xmmword_3CF97B0;
  *pSoften = 7.0;
  *pBias = 0.0;
}

// 0x19b2bc0
void evtGetValueNewSLightFrame(evtViewerInfo_t *pInfo, evtViewerObject_t *obj, s32 nowframe, pmdSceneLightTable_t *sl, f32 *out_soften, f32 *out_bias) {
  pmdSceneLightTable_t *v12;
  f32 f;
  f32 v15;
  s32 v16;
  pmdSceneLightTable_t *v17;
  pmdSceneLightTable_t *v19;
  pmdSceneLightTable_t *v20;
  sdfVector4_t *Color;
  pmdSceneLightTable_t *v22;
  f32 v23;
  f32 v24;
  f32 v25;
  s32 v26;
  s32 v27;
  _BOOL4 v29;
  sdfVector4_t *v30;
  sdfVector4_t *Dir;
  f32 v32;
  f32 v33;
  s64 v34;
  s64 v35;
  pmdSceneLightTable_t *d;

  d = sl;
  v34 = 0;
  v35 = 0;
  (loc_19D0200)(obj, nowframe, &v35, &v34, 0, out_bias);
  if (v35)
  {
    v12 = *(pmdSceneLightTable_t *)(v35 + 40);
    f = get_f(*(pmdDataInfo_t *)(*(u64 *)(v35 + 24) + 32), 0);
    v15 = get_f(*(pmdDataInfo_t *)(*(u64 *)(v35 + 24) + 40), 0);
    if (!v34 || (v16 = *(u32 *)(v35 + 20)) == 0)
    {
      v19 = d;
      sl->Color[0] = v12->Color[0];
      v20 = d;
      d->Dir[0] = v12->Dir[0];
      v20->Color[1] = v12->Color[1];
      v20->Dir[1] = v12->Dir[1];
      Color = v19->Color;
      v22 = d;
      Color[2] = v12->Color[2];
      d->Dir[2] = v12->Dir[2];
      v22->Ambient = v12->Ambient;
      *out_soften = f;
      goto LABEL_39;
    }
    v17 = *(pmdSceneLightTable_t *)(v34 + 40);
    if (v17)
    {
LABEL_17:
      v23 = get_f(*(pmdDataInfo_t *)(*(u64 *)(v34 + 24) + 32), 0);
      v24 = get_f(*(pmdDataInfo_t *)(*(u64 *)(v34 + 24) + 40), 0);
      v25 = 0.0;
      v26 = *(u16 *)(v35 + 16);
      v27 = *(u16 *)(v34 + 16) - v26;
      if (v27)
        v25 = (f32)(nowframe - v26) / (f32)v27;
      evtHokanSceneLight(v16, v25, v12, v17, d);
      v29 = 0;
      v32 = 1.0;
      if (v25 <= 1.0)
        v32 = v25;
      if (v25 >= 0.0)
        v33 = v32;
      else
        v33 = 0.0;
      *out_soften = f + (f32)((f32)(v23 - f) * v33);
      v15 = v15 + (f32)((f32)(v24 - v15) * v33);
      goto LABEL_39;
    }
    if (v12)
      goto LABEL_17;
  }
  v30 = sl->Color;
  Dir = sl->Dir;
  v15 = 0.0;
  v30[0] = (sdfVector4_t)xmmword_3D05D20;
  Dir[0] = (sdfVector4_t)xmmword_3CFCD20;
  v30[1] = (sdfVector4_t)xmmword_3D05D20;
  Dir[1] = (sdfVector4_t)xmmword_3CFCD20;
  v30[2] = (sdfVector4_t)xmmword_3D05D20;
  Dir[2] = (sdfVector4_t)xmmword_3CFCD20;
  sl->Ambient = (struct sdfVector4_t)xmmword_3CF97B0;
  *out_soften = 7.0;
LABEL_39:
  *out_bias = v15;
}

// 0x19b2f80
static void SetDefaultTmxData(pmdTmxData_t *out_tmxdata) {
  pmdTmxData_t *v3;
  pmdTmxData_t *v4;

  v3 = Allocate(pmdTmxData_t);
  _ctor(v3, 0);
  out_tmxdata = v3;
  v4 = out_tmxdata;
  __asm { FMOV            V0.2S, #1.0 }
  *(u64 *)&v4->scaleh = _D0;
  *(u32 *)&v4->r = -2139062144;
  v4->priority = 0;
  *(u64 *)&v4->x = 0xE000000100LL;
  *(u64 *)&v4->hokan = 1;
}

// 0x19b3020
void evtGetValueNewTMXFrame(evtViewerInfo_t *pInfo, evtViewerObject_t *obj, s32 nowframe, pmdTmxData_t *out_tmxdata) {
  evtFrameInfo_t *v9;
  evtFrameInfo_t *v10;
  f32 v11;
  s32 v12;
  evtFrameInfo_t *v13;
  s32 v14;
  pmdTmxData_t *v15;
  pmdTmxData_t *v16;
  evtFrameInfo_t *frame;
  evtFrameInfo_t *nearframe;

  frame = 0;
  nearframe = 0;
  (loc_19D0200)(obj, nowframe, &nearframe, &frame, 0);
  v9 = nearframe;
  if (!nearframe)
  {
    v15 = Allocate(pmdTmxData_t);
    _ctor(v15, 0);
    out_tmxdata = v15;
    v16 = out_tmxdata;
    __asm { FMOV            V0.2S, #1.0 }
    *(u64 *)&v16->scaleh = _D0;
    *(u32 *)&v16->r = -2139062144;
    v16->priority = 0;
    *(u64 *)&v16->x = 0xE000000100LL;
    *(u64 *)&v16->hokan = 1;
    return;
  }
  v10 = frame;
  v11 = 0.0;
  v12 = nearframe->frame;
  if (frame)
    v13 = frame;
  else
    v13 = nearframe;
  v14 = v13->frame - v12;
  if (v14)
    v11 = (f32)(nowframe - v12) / (f32)v14;
  evtHokanTmx(v11, v9, v10, out_tmxdata);
}

// 0x19b31c0
void evtHokanTmx(f32 ratio, evtFrameInfo_t *nearframe, evtFrameInfo_t *frame, pmdTmxData_t *out_tmxdata) {
  bool v9;
  pmdTmxData_t *v10;
  pmdTmxData_t *v11;
  s32 v17;
  pmdTmxData_t *v19;
  pmdTmxData_t *v20;
  s16 Item;
  s16 v22;
  s16 v23;
  pmdTmxData_t *v24;
  f32 v25;
  s32 v26;
  s16 v27;
  s16 v28;
  s16 v29;
  s32 v30;
  pmdTmxData_t *v31;
  f32 v32;
  s32 v33;
  u32 v34;
  u8 v35;
  u8 v36;
  f32 v37;
  pmdTmxData_t *v38;
  u32 v39;
  u8 v40;
  u8 v41;
  f32 v42;
  pmdTmxData_t *v43;
  u8 v44;
  u8 v45;
  f32 v46;
  pmdTmxData_t *v47;
  u8 v48;
  s32 v49;
  pmdTmxData_t *v50;
  f32 f;
  f32 v52;
  f32 v53;
  pmdDataInfo_t *v54;
  pmdTmxData_t *v55;
  f32 v56;
  f32 v57;
  f32 v58;
  pmdTmxData_t *v59;
  pmdTmxData_t *v60;
  pmdTmxData_t *v61;
  pmdTmxData_t *v62;
  u8 v63;
  pmdDataInfo_t *data;
  pmdTmxData_t *v65;
  u8 v66;
  pmdDataInfo_t *v67;
  pmdTmxData_t *v68;
  u8 v69;
  pmdDataInfo_t *v70;
  pmdTmxData_t *v71;
  u8 v72;
  pmdDataInfo_t *v73;
  pmdTmxData_t *v74;
  f32 v75;
  pmdDataInfo_t *v76;
  pmdDataInfo_t *v77;
  pmdTmxData_t *v78;
  pmdTmxData_t *v79;
  s8 v80;

  if (frame)
  {
    v9 = get_Item(nearframe->data[5]->c, 0, 0) != 3
      || get_Item(frame->data[5]->c, 0, 0) == 3;
    if (get_Item(nearframe->data[5]->c, 0, 0) != 3 && get_Item(frame->data[5]->c, 0, 0) == 3)
    {
      v9 = 0;
    }
    if (ratio != 0.0 && get_Item(nearframe->data[0]->s, 0, 0) && v9)
    {
      v19 = Allocate(pmdTmxData_t);
      _ctor(v19, 0);
      out_tmxdata = v19;
      v20 = out_tmxdata;
      Item = get_Item(nearframe->data[1]->s, 0, 0);
      v22 = get_Item(frame->data[1]->s, 0, 0);
      v23 = get_Item(nearframe->data[1]->s, 0, 0);
      v24 = out_tmxdata;
      v25 = (f32)(v22 - v23) * ratio;
      v26 = v25;
      if (v25 == INFINITY)
        v26 = 0x80000000;
      v20->x = v26 + Item;
      v27 = get_Item(nearframe->data[1]->s, 1, 0);
      v28 = get_Item(frame->data[1]->s, 1, 0);
      v29 = get_Item(nearframe->data[1]->s, 1, 0);
      v30 = v28;
      v31 = out_tmxdata;
      v32 = (f32)(v30 - v29) * ratio;
      v33 = v32;
      if (v32 == INFINITY)
        v33 = 0x80000000;
      v24->y = v33 + v27;
      v34 = get_Item(nearframe->data[2]->uc, 0, 0);
      v35 = get_Item(frame->data[2]->uc, 0, 0);
      v36 = get_Item(nearframe->data[2]->uc, 0, 0);
      v37 = v34;
      v38 = out_tmxdata;
      v31->r = (s32)(f32)((f32)((f32)(v35 - v36) * ratio) + v37);
      v39 = get_Item(nearframe->data[2]->uc, 1, 0);
      v40 = get_Item(frame->data[2]->uc, 1, 0);
      v41 = get_Item(nearframe->data[2]->uc, 1, 0);
      v42 = v39;
      v43 = out_tmxdata;
      v38->g = (s32)(f32)((f32)((f32)(v40 - v41) * ratio) + v42);
      LODWORD(v38) = get_Item(nearframe->data[2]->uc, 2, 0);
      v44 = get_Item(frame->data[2]->uc, 2, 0);
      v45 = get_Item(nearframe->data[2]->uc, 2, 0);
      v46 = (u32)v38;
      v47 = out_tmxdata;
      v43->b = (s32)(f32)((f32)((f32)(v44 - v45) * ratio) + v46);
      LODWORD(v43) = get_Item(nearframe->data[2]->uc, 3, 0);
      v48 = get_Item(frame->data[2]->uc, 3, 0);
      v49 = v48 - get_Item(nearframe->data[2]->uc, 3, 0);
      v50 = out_tmxdata;
      v47->a = (s32)(f32)((f32)((f32)v49 * ratio) + (f32)(u32)v43);
      f = get_f(nearframe->data[3], 0);
      v52 = get_f(frame->data[3], 0);
      v53 = get_f(nearframe->data[3], 0);
      v54 = nearframe->data[4];
      v50->scalew = f + (f32)((f32)(v52 - v53) * ratio);
      v55 = out_tmxdata;
      v56 = get_f(v54, 0);
      v57 = get_f(frame->data[4], 0);
      v58 = v56
          + (f32)((f32)(v57 - get_f(nearframe->data[4], 0)) * ratio);
      goto LABEL_27;
    }
LABEL_26:
    v59 = Allocate(pmdTmxData_t);
    _ctor(v59, 0);
    out_tmxdata = v59;
    v60 = out_tmxdata;
    v60->x = get_Item(nearframe->data[1]->s, 0, 0);
    v61 = out_tmxdata;
    v61->y = get_Item(nearframe->data[1]->s, 1, 0);
    v62 = out_tmxdata;
    v63 = get_Item(nearframe->data[2]->uc, 0, 0);
    data = nearframe->data;
    v62->r = v63;
    v65 = out_tmxdata;
    v66 = get_Item(data[2]->uc, 1, 0);
    v67 = nearframe->data;
    v65->g = v66;
    v68 = out_tmxdata;
    v69 = get_Item(v67[2]->uc, 2, 0);
    v70 = nearframe->data;
    v68->b = v69;
    v71 = out_tmxdata;
    v72 = get_Item(v70[2]->uc, 3, 0);
    v73 = nearframe->data;
    v71->a = v72;
    v74 = out_tmxdata;
    v75 = get_f(v73[3], 0);
    v76 = nearframe->data;
    v74->scalew = v75;
    v55 = out_tmxdata;
    v58 = get_f(v76[4], 0);
LABEL_27:
    v77 = nearframe->data;
    v78 = out_tmxdata;
    v55->scaleh = v58;
    v78->hokan = get_Item(v77[0]->c, 0, 0);
    v79 = out_tmxdata;
    v80 = get_Item(nearframe->data[0]->c, 1, 0);
    v11 = out_tmxdata;
    v79->transmode = v80;
    v17 = get_Item(nearframe->data[5]->c, 0, 0);
    goto LABEL_28;
  }
  if (nearframe)
    goto LABEL_26;
  v10 = Allocate(pmdTmxData_t);
  _ctor(v10, 0);
  out_tmxdata = v10;
  v11 = out_tmxdata;
  __asm { FMOV            V0.2S, #1.0 }
  v17 = 0;
  *(u64 *)&v11->scaleh = _D0;
  *(u32 *)&v11->r = -2139062144;
  *(u64 *)&v11->x = 0xE000000100LL;
  *(u64 *)&v11->hokan = 1;
LABEL_28:
  v11->priority = v17;
}

// 0x19b38d0
static void FindNearFrameAndAfterFrame(evtViewerObject_t *obj, s32 nowframe, evtFrameInfo_t *out_nearframe, evtFrameInfo_t *out_frame) {
  evtFrameInfo_t *firstframeinfo;
  evtFrameInfo_t *lastframeinfo;
  evtFrameInfo_t *v11;
  s32 Offset;
  evtFrameInfo_t *next;
  evtFrameInfo_t *prev;
  evtFrameInfo_t *i;
  s16 Item;
  evtFrameInfo_t *v17;

  if (!obj)
  {
    out_nearframe = 0;
    out_frame = 0;
    return;
  }
  firstframeinfo = obj->firstframeinfo;
  out_frame = firstframeinfo;
  lastframeinfo = obj->lastframeinfo;
  out_nearframe = lastframeinfo;
  v11 = out_frame;
  if (!out_frame)
  {
LABEL_8:
    if (obj->type != 2)
      return;
    goto LABEL_12;
  }
  Offset = obj->object_data->Offset;
  while (v11->frame + Offset <= nowframe)
  {
    next = v11->next;
    out_frame = next;
    v11 = out_frame;
    if (!out_frame)
      goto LABEL_8;
  }
  prev = v11->prev;
  out_nearframe = prev;
  if (obj->type == 2)
  {
LABEL_12:
    for (i = out_nearframe; out_nearframe; i = out_nearframe)
    {
      Item = get_Item(i->data[1]->s, 0, 0);
      if (evtCompareCutResultValue(Item))
        break;
      v17 = out_nearframe->prev;
      out_nearframe = v17;
    }
  }
}

// 0x19b3a50
bool evtFindInputBranchMessage(evtViewerInfo_t *pInfo) {
  return 0;
}

// 0x19b3a60
void evtGetMessageDataAndTypeFromFrame(evtFrameInfo_t *frame, s32 *pMesNo, s32 *pMesType) {
  *pMesNo = get_Item(frame->data[0]->s, 0, 0) & 0xFFF;
  *pMesType = (u16)get_Item(frame->data[0]->s, 0, 0) >> 12;
}

// 0x19b3ad0
s32 evtFindNameTableIdxFromPM2NameTableIdx(pmdProcessWork_t *wdata, evtViewerInfo_t *pInfo, s32 pm2nametable_idx) {
  evtViewerObject_t *firstobjinfo;
  s64 v7;
  s32 v8;
  s64 nameindex;

  firstobjinfo = pInfo->firstobjinfo;
  if (!firstobjinfo)
    return -1;
  v7 = pm2nametable_idx;
  v8 = -1;
  while (1)
  {
    nameindex = (u32)firstobjinfo->nameindex;
    if ((nameindex & 0x80000000) == 0 && Equals_54828784(pInfo->nametable[nameindex]->Name, wdata->pm2->NameTable2[v7]->Name, 0))
    {
      break;
    }
    firstobjinfo = firstobjinfo->next;
    if (!firstobjinfo)
      return v8;
  }
  return firstobjinfo->nameindex;
}

// 0x19b3b80
evtViewerObject_t *evtFindObjectFromName(evtViewerInfo_t *pInfo, char *objname) {
  evtViewerObject_t *i;
  s64 nameindex;

  for (i = pInfo->firstobjinfo; i; i = i->next)
  {
    nameindex = (u32)i->nameindex;
    if ((nameindex & 0x80000000) == 0 && Equals_54828848(pInfo->nametable[nameindex]->Name, objname, 4, 0))
    {
      break;
    }
  }
  return i;
}

// 0x19b3bf0
void evtDrawTexture(void *tex, pmdTmxData_t *tmxdata, bool mask, sdfIVector2_t maskofs, void *mesh) {
  f32 v11;
  _BOOL4 v12;
  void *v14;
  void *v16;
  s32 v22;
  f32 v23;
  f32 v25;
  f32 v27;
  s32 v28;
  s32 v30;
  f32 v33;
  f32 v35;
  f32 v36;
  s32 v37;
  f32 v39;
  s32 v40;
  s32 transmode;
  sdfDrawTag_t *pdrawtag;
  s64 v46;
  s32 Item;
  s32 v48;
  sdfIVector4_t *p_dtex_pos;
  s32 v52;
  s32 v53;
  sdfIVector4_t *v55;
  s32 v57;
  s32 v58;
  sdfIVector4_t *v60;
  s32 v62;
  s32 v63;
  s32 priority;
  u32 v66;
  s64 v70;
  s64 v71;
  s64 v72;
  s64 v73;
  sdfColor32_t rgba;
  void *v75;
  sdfIVector2_t v77;
  sdfIVector4_t v78;
  sdfIVector4_t v79;
  sdfIVector4_t v80;
  sdfIVector4_t v81;
  sdfIVector4_t v82;
  sdfIVector4_t v83;
  sdfIVector4_t v84;
  sdfIVector4_t v85;
  sdfIVector4_t v86;
  sdfIVector4_t v87;
  sdfIVector4_t v88;
  sdfIVector4_t v89;
  sdfIVector4_t v90;
  sdfIVector4_t v91;
  sdfIVector4_t v92;
  sdfIVector4_t v93;
  sdfIVector4_t v94;
  sdfIVector4_t v95;
  sdfIVector4_t v96;

  v77 = maskofs;
  if (op_Equality(tex, 0, 0))
    return;
  if (!tmxdata->a)
    return;
  v11 = sdfTexScale(tex);
  if ((tex->klass->vtable._5_get_width.methodPtr)(tex, tex->klass->vtable._5_get_width.method) != 1920)
  {
    v12 = 0;
    v14 = mesh;
LABEL_14:
    if (!op_Equality(v14, 0, 0))
      goto LABEL_20;
    goto LABEL_15;
  }
  v12 = (tex->klass->vtable._7_get_height.methodPtr)(tex, tex->klass->vtable._7_get_height.method) == 1080;
  v14 = mesh;
  goto LABEL_14;
  if (!op_Equality(v14, 0, 0))
  {
LABEL_20:
    if (v12)
      goto LABEL_21;
    goto LABEL_24;
  }
LABEL_15:
  v16 = eglNewMesh2D(0);
  mesh = v16;
  InitSquare(mesh, 1, 0);
  if (v12)
  {
    mesh->type = 0;
LABEL_21:
    *(u64 *)&v78.z = 0;
    *(u64 *)&v78.x = &dtex_pos;
    set_Item(v78, 0, 0);
    *(u64 *)&v79.z = 1;
    *(u64 *)&v79.x = &dtex_pos;
    set_Item(v79, 0, 0);
    *(u64 *)&v80.z = 2;
    *(u64 *)&v80.x = &dtex_pos;
    set_Item(v80, 0x2000, 0);
    *(u64 *)&v81.z = 3;
    v22 = 3584;
    *(u64 *)&v81.x = &dtex_pos;
    goto LABEL_33;
  }
LABEL_24:
  v23 = (f32)(tmxdata->scalew * (f32)(tex->klass->vtable._5_get_width.methodPtr)(tex, tex->klass->vtable._5_get_width.method))
      / v11;
  v25 = tmxdata->scaleh
      * (f32)(tex->klass->vtable._7_get_height.methodPtr)(tex, tex->klass->vtable._7_get_height.method);
  v27 = v25 / v11;
  *(u64 *)&v82.x = &dtex_pos;
  if (v23 == INFINITY)
    v28 = -1073741824;
  else
    v28 = (s32)v23 / 2;
  *(u64 *)&v82.z = 0;
  set_Item(v82, 16 * (tmxdata->x - v28), 0);
  if (v27 == INFINITY)
    v30 = -1073741824;
  else
    v30 = (s32)v27 / 2;
  *(u64 *)&v83.z = 1;
  *(u64 *)&v83.x = &dtex_pos;
  set_Item(v83, 8 * (tmxdata->y - v30), 0);
  *(u64 *)&v84.z = 2;
  *(u64 *)&v84.x = &dtex_pos;
  set_Item(v84, 16 * (tmxdata->x + v28), 0);
  *(u64 *)&v81.z = 3;
  v22 = 8 * (tmxdata->y + v30);
  *(u64 *)&v81.x = &dtex_pos;
LABEL_33:
  set_Item(v81, v22, 0);
  v33 = 16.0 / v11;
  LOBYTE(dtex_color.rgba) = tmxdata->r;
  BYTE1(dtex_color.rgba) = tmxdata->g;
  BYTE2(dtex_color.rgba) = tmxdata->b;
  HIBYTE(dtex_color.rgba) = tmxdata->a;
  v35 = (tex->klass->vtable._5_get_width.methodPtr)(tex, tex->klass->vtable._5_get_width.method);
  *(u64 *)&v85.z = 2;
  v36 = v33 * v35;
  if (v36 == INFINITY)
    v37 = 0x80000000;
  else
    v37 = v36;
  *(u64 *)&v85.x = &dtex_uv;
  set_Item(v85, v37, 0);
  v86.x = (tex->klass->vtable._7_get_height.methodPtr)(tex, tex->klass->vtable._7_get_height.method);
  *(u64 *)&v86.z = 3;
  v39 = v33 * (f32)v86.x;
  if (v39 == INFINITY)
    v40 = 0x80000000;
  else
    v40 = v39;
  *(u64 *)&v86.x = &dtex_uv;
  set_Item(v86, v40, 0);
  transmode = tmxdata->transmode;
  pdrawtag = Allocate(sdfDrawTag_t);
  _ctor(pdrawtag, 0);
  sdfDrawTagInit(pdrawtag);
  if (transmode == 2)
  {
    transmode = 2;
    goto LABEL_51;
  }
  if (transmode == 1)
  {
    transmode = 1;
    goto LABEL_51;
  }
  if (transmode)
    goto LABEL_52;
  transmode = 0;
LABEL_51:
  itfMiscDrawAlphaPrim(pdrawtag, transmode, 0);
LABEL_52:
  if (mask)
  {
    *(u64 *)&v87.z = 0;
    *(u64 *)&v87.x = &dtex_pos;
    v46 = *(u64 *)&v87.x;
    Item = get_Item(v87, 0);
    v48 = get_Item((sdfIVector2_t)&v77, 0, 0) + Item;
    *(u64 *)&v88.x = v46;
    *(u64 *)&v88.z = 0;
    set_Item(v88, v48, 0);
    *(u64 *)&v89.z = 1;
    p_dtex_pos = &dtex_pos;
    *(u64 *)&v89.x = p_dtex_pos;
    v52 = get_Item(v89, 0);
    v53 = get_Item((sdfIVector2_t)&v77, 1, 0) + v52;
    *(u64 *)&v90.x = p_dtex_pos;
    *(u64 *)&v90.z = 1;
    set_Item(v90, v53, 0);
    *(u64 *)&v91.z = 2;
    v55 = &dtex_pos;
    *(u64 *)&v91.x = v55;
    v57 = get_Item(v91, 0);
    v58 = get_Item((sdfIVector2_t)&v77, 0, 0) + v57;
    *(u64 *)&v92.x = v55;
    *(u64 *)&v92.z = 2;
    set_Item(v92, v58, 0);
    *(u64 *)&v93.z = 3;
    v60 = &dtex_pos;
    *(u64 *)&v93.x = v60;
    v62 = get_Item(v93, 0);
    v63 = get_Item((sdfIVector2_t)&v77, 1, 0) + v62;
    *(u64 *)&v94.x = v60;
    *(u64 *)&v94.z = 3;
    set_Item(v94, v63, 0);
  }
  else
  {
    priority = tmxdata->priority;
    if (priority == 1)
    {
      v66 = 39;
      goto LABEL_61;
    }
    if (priority != 2)
    {
      if (priority == 100)
        v66 = 92;
      else
        v66 = 109;
      goto LABEL_61;
    }
  }
  v66 = 72;
LABEL_61:
  eglSetOt(v66);
  eglLinkTest(SET_10AADD11);
  v70 = *(u64 *)&dtex_pos.x;
  v71 = *(u64 *)&dtex_pos.z;
  v72 = *(u64 *)&dtex_uv.x;
  v73 = *(u64 *)&dtex_uv.z;
  rgba = (sdfColor32_t)(u32)dtex_color.rgba;
  v75 = mesh;
  *(u64 *)&v95.x = v70;
  *(u64 *)&v95.z = v71;
  *(u64 *)&v96.x = v72;
  *(u64 *)&v96.z = v73;
  itfMiscDrawSpritePrim(v95, v96, rgba, 0xFFu, tex, 0, pdrawtag, v75);
  sdfDrawTagLinkOt(Ot[v66], pdrawtag);
}

// 0x19b43c0
void evtCreateZikkiEventMes(evtViewerInfo_t *pInfo) {
  ;
}

// 0x19b43d0
void evtDeleteZikkiEventMes(evtViewerInfo_t *pInfo) {
  ;
}

// 0x19b43e0
void evtRenderTexStart(evtViewerInfo_t *pInfo) {
  ;
}

// 0x19b43f0
void evtRenderTexManager(evtViewerInfo_t *pInfo) {
  ;
}

// 0x19b4400
void evtSetBistaMode(evtViewerInfo_t *pInfo, s32 bistamode) {
  pInfo->cutVal = pInfo->cutVal & 0xFFFFFFFC | bistamode & 3;
}

// 0x19b4410
s32 evtGetBistaMode(evtViewerInfo_t *pInfo) {
  return pInfo->cutVal & 3;
}

// 0x19b4420
void evtSetSkipMode(evtViewerInfo_t *pInfo, s32 skipmode) {
  pInfo->cutVal = pInfo->cutVal & 0xFFFFFFF3 | (4 * (skipmode & 3));
}

// 0x19b4430
s32 evtGetSkipMode(evtViewerInfo_t *pInfo) {
  return ((u32)pInfo->cutVal >> 2) & 3;
}

// 0x19b4440
void evtEventRegistBGM(evtViewerInfo_t *pInfo, s32 regbgm_no) {
  s32 callBgmNo;
  s64 v4;
  s32 *m_Items;
  s32 v6;

  callBgmNo = pInfo->callBgmNo;
  if (callBgmNo < 1)
  {
LABEL_6:
    pInfo->callBgmArray[callBgmNo] = regbgm_no;
    ++pInfo->callBgmNo;
  }
  else
  {
    v4 = (u32)pInfo->callBgmNo;
    m_Items = pInfo->callBgmArray;
    while (1)
    {
      v6 = *m_Items++;
      if (v6 == regbgm_no)
        break;
      if (!--v4)
      {
        if (callBgmNo > 19)
          return;
        goto LABEL_6;
      }
    }
  }
}

// 0x19b44a0
void evtEventFadeOutAllBgm(evtViewerInfo_t *pInfo) {
  s64 v3;

  if (pInfo->callBgmNo >= 1)
  {
    v3 = 0;
    do
      evtFadeOutBgm(pInfo->workdata->EventNo, pInfo->callBgmArray[v3++]);
    while (v3 < pInfo->callBgmNo);
  }
  pInfo->callBgmNo = 0;
}

// 0x19b4500
void evtBezierGetPoint(f32 T, s32 *pCX, s32 *pCY, s32 *pX, s32 *pY) {
  f32 v6;
  f32 v7;
  f32 v8;
  f32 v9;
  f32 v10;
  f32 v11;
  s32 v12;
  f32 v13;
  s32 v14;

  v6 = 1.0 - T;
  v7 = v6 * (f32)(v6 * v6);
  v8 = (f32)((f32)(v6 * v6) * 3.0) * T;
  v9 = (f32)(T * T) * (f32)((f32)(1.0 - T) * 3.0);
  v10 = (f32)(T * T) * T;
  v11 = (f32)((f32)((f32)(v7 * (f32)pCX[0]) + (f32)(v8 * (f32)pCX[1])) + (f32)(v9 * (f32)pCX[2]))
      + (f32)(v10 * (f32)pCX[3]);
  v12 = v11;
  if (v11 == INFINITY)
    v12 = 0x80000000;
  *pX = v12;
  v13 = (f32)((f32)((f32)(v7 * (f32)pCY[0]) + (f32)(v8 * (f32)pCY[1])) + (f32)(v9 * (f32)pCY[2]))
      + (f32)(v10 * (f32)pCY[3]);
  v14 = v13;
  if (v13 == INFINITY)
    v14 = 0x80000000;
  *pY = v14;
}

// 0x19b45d0
s32 evtBezierGetPointY(s32 TargetX, s32 *pCX, s32 *pCY) {
  s32 v7;
  s32 v8;
  s32 v9;
  s32 v10;
  f32 v11;
  f32 v12;
  f32 v13;
  f32 v14;
  f32 v15;
  s32 v16;
  f32 v17;
  f32 v18;
  f32 v19;
  f32 v20;
  f32 v21;
  s32 result;
  f32 v24;
  f32 v25;
  f32 v26;
  f32 v27;
  f32 v28;
  f32 v29;
  f32 v30;
  f32 v31;
  f32 v32;
  s32 v33;
  f32 v34;
  f32 v35;
  f32 v36;
  f32 v37;
  f32 v38;
  s32 v39;
  f32 v40;
  f32 v41;
  f32 v42;
  f32 v43;
  f32 v44;
  f32 v45;
  s32 v46;
  f32 v47;
  f32 v48;
  f32 v49;
  f32 v50;
  f32 v51;
  s32 v52;
  f32 v53;
  f32 v54;
  f32 v55;
  f32 v56;
  f32 v57;
  f32 v58;
  s32 v59;
  f32 v60;
  f32 v61;
  f32 v62;
  f32 v63;
  f32 v64;
  s32 v65;
  f32 v66;
  f32 v67;
  f32 v68;
  f32 v69;
  f32 v70;
  f32 v71;
  s32 v72;
  f32 v73;
  f32 v74;
  f32 v75;
  f32 v76;
  f32 v84;

  v7 = pCX[0];
  v8 = pCX[1];
  v9 = pCX[2];
  v10 = pCX[3];
  v11 = v7;
  v12 = v8;
  v13 = v9;
  v14 = v10;
  v15 = (f32)((f32)((f32)((f32)v7 * 0.125) + (f32)((f32)v8 * 0.375)) + (f32)((f32)v9 * 0.375))
      + (f32)((f32)v10 * 0.125);
  v16 = v15;
  if (v15 == INFINITY)
    v16 = 0x80000000;
  v17 = pCY[0];
  v18 = pCY[1];
  v19 = pCY[2];
  v20 = pCY[3];
  v21 = (f32)((f32)((f32)(v17 * 0.125) + (f32)(v18 * 0.375)) + (f32)(v19 * 0.375)) + (f32)(v20 * 0.125);
  if (v21 == INFINITY)
    result = 0x80000000;
  else
    result = (s32)v21;
  if (v16 != TargetX)
  {
    v24 = 0.5;
    if (v16 < TargetX)
      v24 = 0.75;
    v25 = 0.25;
    if (v16 <= TargetX)
      v25 = 0.0;
    v26 = v24 - v25;
    v27 = 1.0 - (f32)(v24 - v25);
    v28 = v27 * (f32)(v27 * v27);
    v29 = v26 * (f32)((f32)(v27 * v27) * 3.0);
    v30 = (f32)(v26 * v26) * (f32)(v27 * 3.0);
    v31 = v26 * (f32)(v26 * v26);
    v32 = (f32)((f32)((f32)(v28 * v11) + (f32)(v29 * v12)) + (f32)(v30 * v13)) + (f32)(v31 * v14);
    v33 = v32;
    if (v32 == INFINITY)
      v33 = 0x80000000;
    if (v33 != TargetX)
    {
      v34 = -0.0;
      if (v33 <= TargetX)
        v35 = 0.0;
      else
        v35 = 0.125;
      if (v33 < TargetX)
        v34 = 0.125;
      v36 = (f32)(v26 + v34) - v35;
      v37 = 1.0 - v36;
      v28 = v37 * (f32)(v37 * v37);
      v29 = v36 * (f32)((f32)(v37 * v37) * 3.0);
      v30 = (f32)(v36 * v36) * (f32)((f32)(1.0 - v36) * 3.0);
      v31 = v36 * (f32)(v36 * v36);
      v38 = (f32)((f32)((f32)(v28 * v11) + (f32)(v29 * v12)) + (f32)(v30 * v13)) + (f32)(v31 * v14);
      if (v38 == INFINITY)
        v39 = 0x80000000;
      else
        v39 = v38;
      if (v39 != TargetX)
      {
        v40 = -0.0;
        v41 = 0.0625;
        if (v39 < TargetX)
          v40 = 0.0625;
        v42 = v36 + v40;
        if (v39 <= TargetX)
          v41 = 0.0;
        v43 = v42 - v41;
        v44 = 1.0 - (f32)(v42 - v41);
        v28 = v44 * (f32)(v44 * v44);
        v29 = v43 * (f32)((f32)(v44 * v44) * 3.0);
        v30 = (f32)(v43 * v43) * (f32)(v44 * 3.0);
        v31 = v43 * (f32)(v43 * v43);
        v45 = (f32)((f32)((f32)(v28 * v11) + (f32)(v29 * v12)) + (f32)(v30 * v13)) + (f32)(v31 * v14);
        v46 = v45;
        if (v45 == INFINITY)
          v46 = 0x80000000;
        if (v46 != TargetX)
        {
          v47 = -0.0;
          v48 = 0.03125;
          if (v46 < TargetX)
            v47 = 0.03125;
          if (v46 <= TargetX)
            v48 = 0.0;
          v49 = (f32)(v43 + v47) - v48;
          v50 = 1.0 - v49;
          v28 = v50 * (f32)(v50 * v50);
          v29 = v49 * (f32)((f32)(v50 * v50) * 3.0);
          v30 = (f32)(v49 * v49) * (f32)((f32)(1.0 - v49) * 3.0);
          v31 = v49 * (f32)(v49 * v49);
          v51 = (f32)((f32)((f32)(v28 * v11) + (f32)(v29 * v12)) + (f32)(v30 * v13)) + (f32)(v31 * v14);
          if (v51 == INFINITY)
            v52 = 0x80000000;
          else
            v52 = v51;
          if (v52 != TargetX)
          {
            v53 = -0.0;
            v54 = 0.015625;
            if (v52 < TargetX)
              v53 = 0.015625;
            v55 = v49 + v53;
            if (v52 <= TargetX)
              v54 = 0.0;
            v56 = v55 - v54;
            v57 = 1.0 - (f32)(v55 - v54);
            v28 = v57 * (f32)(v57 * v57);
            v29 = v56 * (f32)((f32)(v57 * v57) * 3.0);
            v30 = (f32)(v56 * v56) * (f32)(v57 * 3.0);
            v31 = v56 * (f32)(v56 * v56);
            v58 = (f32)((f32)((f32)(v28 * v11) + (f32)(v29 * v12)) + (f32)(v30 * v13)) + (f32)(v31 * v14);
            v59 = v58;
            if (v58 == INFINITY)
              v59 = 0x80000000;
            if (v59 != TargetX)
            {
              v60 = -0.0;
              v61 = 0.0078125;
              if (v59 < TargetX)
                v60 = 0.0078125;
              if (v59 <= TargetX)
                v61 = 0.0;
              v62 = (f32)(v56 + v60) - v61;
              v63 = 1.0 - v62;
              v28 = v63 * (f32)(v63 * v63);
              v29 = v62 * (f32)((f32)(v63 * v63) * 3.0);
              v30 = (f32)(v62 * v62) * (f32)((f32)(1.0 - v62) * 3.0);
              v31 = v62 * (f32)(v62 * v62);
              v64 = (f32)((f32)((f32)(v28 * v11) + (f32)(v29 * v12)) + (f32)(v30 * v13))
                  + (f32)(v31 * v14);
              if (v64 == INFINITY)
                v65 = 0x80000000;
              else
                v65 = v64;
              if (v65 != TargetX)
              {
                v66 = -0.0;
                v67 = 0.00390625;
                if (v65 < TargetX)
                  v66 = 0.00390625;
                v68 = v62 + v66;
                if (v65 <= TargetX)
                  v67 = 0.0;
                v69 = v68 - v67;
                v70 = 1.0 - (f32)(v68 - v67);
                v28 = v70 * (f32)(v70 * v70);
                v29 = v69 * (f32)((f32)(v70 * v70) * 3.0);
                v30 = (f32)(v69 * v69) * (f32)(v70 * 3.0);
                v31 = v69 * (f32)(v69 * v69);
                v71 = (f32)((f32)((f32)(v28 * v11) + (f32)(v29 * v12)) + (f32)(v30 * v13))
                    + (f32)(v31 * v14);
                v72 = v71;
                if (v71 == INFINITY)
                  v72 = 0x80000000;
                if (v72 != TargetX)
                {
                  v73 = -0.0;
                  v74 = 0.001953125;
                  if (v72 < TargetX)
                    v73 = 0.001953125;
                  if (v72 <= TargetX)
                    v74 = 0.0;
                  v75 = (f32)(v69 + v73) - v74;
                  v76 = 1.0 - v75;
                  v31 = v75 * (f32)(v75 * v75);
                  v28 = v76 * (f32)(v76 * v76);
                  v29 = v75 * (f32)((f32)(v76 * v76) * 3.0);
                  v30 = (f32)(v75 * v75) * (f32)((f32)(1.0 - v75) * 3.0);
                }
              }
            }
          }
        }
      }
    }
    v84 = (f32)((f32)((f32)(v28 * v17) + (f32)(v29 * v18)) + (f32)(v30 * v19)) + (f32)(v31 * v20);
    if (v84 == INFINITY)
      return 0x80000000;
    else
      return (s32)v84;
  }
  return result;
}

// 0x19b4bd0
static void *GetScreen(void) {
  void *v1;
  void *DispTexture;

  v1 = eglNewMesh2D(0);
  DispTexture = GetDispTexture(captureTexture, 0);
  captureTexture = DispTexture;
  (v1->klass->vtable._7_SetTexture.methodPtr)(v1, captureTexture, v1->klass->vtable._7_SetTexture.method);
  InitSquare(v1, 1, 0);
  (v1->edit->klass->vtable._4_unknown.methodPtr)(v1->edit, v1->edit->klass->vtable._4_unknown.method);
  SetSquarePos(v1, 0, -1.0, 1.0, 1.0, -1.0, 0);
  SetSquareCol_36172464(v1, 0, oneVector, 0);
  SetSquareUV_36173248(v1, 0, 0);
  SetSquareIndex_36173424(v1, 0);
  SetMarker(v1, 0);
  (v1->edit->klass->vtable._5_unknown.methodPtr)(v1->edit, v1->edit->klass->vtable._5_unknown.method);
  v1->type = 0;
  SetActive(v1, 0, 0);
  return v1;
}

// 0x19b4dc0
static void ReleaseScreen(void *mesh) {
  void *v8;
  void *gameObject;

  if (!op_Inequality(captureTexture, 0, 0))
  {
    v8 = mesh;
    goto LABEL_6;
  }
  Release(captureTexture);
  v8 = mesh;
LABEL_6:
  if (!op_Inequality(v8, 0, 0))
    return;
  gameObject = get_gameObject(mesh, 0);
  DestroyImmediate_61008224(gameObject, 0);
  mesh = 0;
}

// 0x19b4f60
static void DrawPrimitive2Core(const sdfVector4_t *Col, void *mesh, DDS3_OT OtNo) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  sdfDrawTag_t *v10;
  sdfDrawTag_t *v11;
  sdfPrimTransPacket_t *v12;
  void **p_SET_01010;
  void *v15;
  SDF_GS_TEST *v16;
  sdfVector4_t v18;

  w = Col->w;
  z = Col->z;
  y = Col->y;
  x = Col->x;
  v10 = sdfPrimAllocDrawTag();
  v18.x = x;
  v18.y = y;
  v11 = v10;
  v18.z = z;
  v18.w = w;
  SetColor(mesh, v18);
  v12 = Allocate(sdfPrimTransPacket_t);
  _ctor(v12, 0);
  p_SET_01010 = &SET_01010;
  v15 = *p_SET_01010;
  v12->alpha = (SDF_GS_ALPHA *)*p_SET_01010;
  v16 = Allocate(SDF_GS_TEST);
  _ctor(v16, 2, 1, 4, 0);
  v12->test = v16;
  sdfDrawTagLink(v11, v12);
  sdfDrawTagLink(v11, mesh->packet);
  sdfDrawTagLinkOt(Ot[OtNo], v11);
}

// 0x19b5100
dds3ProcessID_t *evtStartScreenBreak(dds3ProcessID_t *ParentPID, DDS3_PRIORITY Priority, s32 Type) {
  return 0;
}

// 0x19b5110
static dds3ProcessFunc_t CrossFadeProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  s32 monitor;
  s32 klass_high;
  dds3ProcessFunc_t v8;
  void *klass;
  f32 v11;
  dds3ProcessID_t *id;
  sdfVector4_t v13;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  klass_high = HIDWORD(ProcessData[1].klass);
  monitor = ProcessData[1].monitor;
  HIDWORD(ProcessData[1].klass) = klass_high + 1;
  if (klass_high == monitor)
  {
    v8 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
    _ctor(v8, 0, Method_Project_Kernel_DDS3_PROC_END__, 0);
    return v8;
  }
  else
  {
    klass = ProcessData[2].klass;
    v11 = (f32)(monitor - (klass_high + 1)) / (f32)monitor;
    v13.x = 1.0;
    v13.w = v11;
    v13.y = 1.0;
    v13.z = 1.0;
    DrawPrimitive2Core(v13, klass, 109);
    LODWORD(ProcessData[1].klass) = -1;
    return 0;
  }
}

// 0x19b52c0
static dds3ProcessFunc_t CrossFadeCreateTexProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  s32 klass;
  s32 v6;
  void *Screen;
  Il2CppObject *v11;
  dds3ProcessFunc_t v12;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  klass = ProcessData[1].klass;
  if (klass == 2)
  {
    DrawFlag |= 0x2000000u;
    Screen = GetScreen();
    ProcessData[2].klass = Screen;
    v11 = ProcessData + 2;
    ++LODWORD(v11[-1].klass);
    goto LABEL_18;
  }
  if (klass == 1)
  {
    v6 = 2;
    goto LABEL_20;
  }
  if (klass)
  {
LABEL_18:
    v12 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
    _ctor(v12, 0, Method_Project_evt_CrossFadeProcess__, 0);
    return v12;
  }
  v6 = 1;
LABEL_20:
  LODWORD(ProcessData[1].klass) = v6;
  return 0;
}

// 0x19b54a0
static void CrossFadeShutdown(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  void *v6;
  s32 v9;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  v6 = &ProcessData[2];
  ReleaseScreen(v6);
  v9 = evtCrossFadeProcCnt - 1;
  evtCrossFadeProcCnt = v9;
  if (!v9)
  {
    evtCrossFadePID = 0;
  }
}

// 0x19b55f0
dds3ProcessID_t *evtStartCrossFade(dds3ProcessID_t *ParentPID, DDS3_PRIORITY Priority, s32 Length) {
  evtCrossFade_t *v7;
  dds3ProcessFunc_t v9;
  shutdownfuncDelegate v10;
  dds3ProcessID_t *started;
  dds3ProcessID_t *v12;
  dds3ProcessID_t *result;
  void *object;
  dds3ProcessID_t *parent;

  parent = ParentPID;
  v7 = Allocate(evtCrossFade_t);
  _ctor(v7, 0);
  v7->Length = Length;
  v9 = Allocate(dds3ProcessFunc_t);
  _ctor(v9, 0, Method_Project_evt_CrossFadeCreateTexProcess__, 0);
  v10 = Allocate(shutdownfuncDelegate);
  _ctor(v10, 0, Method_Project_evt_CrossFadeShutdown__, 0);
  started = dds3StartProcess("evtCrossFade", Priority, 0, 0, v9, v10, v7);
  object = started;
  if (!ParentPID)
  {
    v12 = started;
    goto LABEL_10;
  }
  dds3LinkProcess(parent, object);
  v12 = object;
LABEL_10:
  evtCrossFadePID = v12;
  result = evtCrossFadePID;
  ++evtCrossFadeProcCnt;
  return result;
}

// 0x19b5800
s32 evtCrossFadeGetStat(void) {
  Il2CppObject *ProcessData;

  if (!evtCrossFadePID)
    return 0;
  goto LABEL_6;
LABEL_13:
  goto LABEL_15;
LABEL_6:
  ProcessData = dds3GetProcessData(evtCrossFadePID);
  if (ProcessData)
    goto LABEL_13;
LABEL_15:
  if (LODWORD(ProcessData[1].klass) == -1)
    return 2;
  else
    return 1;
}

// 0x19b5950
static dds3ProcessFunc_t RainProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  dds3ProcessFunc_t v6;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  if (((s64)ProcessData[1].klass & 2) == 0)
    return 0;
  v6 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
  _ctor(v6, 0, Method_Project_Kernel_DDS3_PROC_END__, 0);
  return v6;
}

// 0x19b5a90
static dds3ProcessFunc_t RainLoadProcess(dds3ProcessID_t *PID) {
  dds3ProcessFunc_t v2;

  v2 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
  _ctor(v2, 0, Method_Project_evt_RainProcess__, 0);
  return v2;
}

// 0x19b5b10
static void DestroyRain(dds3ProcessID_t *PID) {
  ;
}

// 0x19b5b20
void evtStartRain(s32 Type) {
  evtRain_t *v3;
  dds3ProcessFunc_t v4;
  shutdownfuncDelegate v5;
  dds3ProcessID_t *started;

  if (evtRainPID)
    return;
  v3 = Allocate(evtRain_t);
  _ctor(v3, 0);
  v4 = Allocate(dds3ProcessFunc_t);
  _ctor(v4, 0, Method_Project_evt_RainLoadProcess__, 0);
  v5 = Allocate(shutdownfuncDelegate);
  _ctor(v5, 0, Method_Project_evt_DestroyRain__, 0);
  started = dds3StartProcess("evtRainProcess", 11010, 0, 1, v4, v5, v3);
  evtRainPID = started;
}

// 0x19b5ce0
void evtEndRain(void) {
  Il2CppObject *ProcessData;

  if (!evtRainPID)
    return;
  ProcessData = dds3GetProcessData(evtRainPID);
  if (!ProcessData)
    goto LABEL_15;
  goto LABEL_13;
  if (!ProcessData)
  {
LABEL_15:
    LODWORD(ProcessData[1].klass) |= 2u;
    return;
  }
LABEL_13:
  goto LABEL_15;
}

// 0x19b5e30
s32 evtCheckRain(void) {
  return 2 * (evtRainPID != 0);
}

// 0x19b5ea0
static PMD_OBJTYPE GetFrameObjectType(pmdProcessWork_t *wdata, s32 index) {
  return wdata->pm2->FrameTable[index]->ObjectType;
}

// 0x19b5ec0
static s16 GetFrameNameIndex(pmdProcessWork_t *wdata, s32 index) {
  return wdata->pm2->FrameTable[index]->NameIndex;
}

// 0x19b5ee0
static u16 GetFrameFrameNo(pmdProcessWork_t *wdata, s32 index) {
  return wdata->pm2->FrameTable[index]->Frame;
}

// 0x19b5f00
static u16 GetFrameLength(pmdProcessWork_t *wdata, s32 index) {
  return wdata->pm2->FrameTable[index]->Length;
}

// 0x19b5f20
static pmdDataInfo_t *GetFrameData(pmdProcessWork_t *wdata, s32 index) {
  return wdata->pm2->FrameTable[index]->Data;
}

// 0x19b5f40
void evtModifySLightLinkObjIndex(pmdProcessWork_t *wdata, evtViewerInfo_t *pInfo, pmdObjectTable_t *pObjData) {
  evtViewerObject_t *firstobjinfo;
  s32 v8;

  if (pObjData->union0 == 3)
  {
    if (wdata->pm2->ObjectCount >= 1)
    {
      firstobjinfo = pInfo->firstobjinfo;
      if (firstobjinfo)
      {
        v8 = 0;
        do
        {
LABEL_5:
          if (Equals_54828784(pInfo->nametable[firstobjinfo->nameindex]->Name, wdata->pm2->NameTable2[pObjData->union1]->Name, 0))
          {
            pObjData->union1 = firstobjinfo->nameindex;
            return;
          }
          firstobjinfo = firstobjinfo->next;
        }
        while (firstobjinfo);
        while (++v8 < wdata->pm2->ObjectCount)
        {
          firstobjinfo = pInfo->firstobjinfo;
          if (firstobjinfo)
            goto LABEL_5;
        }
      }
    }
    set_LinkType(pObjData, 0, 0);
  }
  pObjData->union1 = 0;
}

// 0x19b6040
s32 evtSetGameData1(pmdProcessWork_t *wdata, evtViewerInfo_t *pInfo) {
  void **v6;
  pmdPM1_t *pm1;
  pmdStageTable_t *StageTable;
  s32 MinorNum;
  s32 MajorNum;
  void *StageF1;
  void *StageF2;
  sdfBinary *StageTB;
  evtViewerObject_t *v14;
  s32 v15;
  pmdDataInfo_t *data;
  void *workdata;
  s64 naturalAligment;
  dds3Basic_t *i;
  pmdPM1_t *v20;
  s32 v21;
  bool v22;
  s64 v23;
  dds3Basic_t *v24;
  struct sdfVector4_t pos;
  pmdUnitTable_t *v26;
  u16 v27;
  s32 v28;
  void *v29;
  void **v31;
  u32 v32;
  evtViewerObject_t *v33;
  dds3Basic_t *v34;
  s32 v35;
  dds3Basic_t *basic;
  char *Name;
  s64 v38;
  pmdLoadScene *loadScene;
  dds3ModelHandle_t *image;
  s64 max_length;
  pmdLoadScene *m_Items;
  void *model;
  evtViewerObject_t *v45;
  dds3Basic_t *p_basic;
  s64 v47;
  pmdDataInfo_t *v48;
  Il2CppObject *v49;
  s64 v50;
  s32 v51;
  evtViewerObject_t *v53;
  char *v54;
  s64 v55;
  evtViewerObject_t *v56;
  s32 v57;
  void *v58;
  s64 v59;
  dds3Basic_t *j;
  evtViewerObject_t *v61;
  dds3Basic_t *v62;
  dds3Basic_t *v63;
  u64 *monitor;
  dds3Basic_t *v65;
  dds3Basic_t *v66;
  dds3Basic_t *next;
  char *v68;
  char *v69;
  dds3ObjectBaseControlWorkData_t *v70;
  dds3Basic_t *v71;
  char *v72;
  char *v73;
  dds3ObjectBaseControlWorkData_t *v74;
  dds3Basic_t *v75;
  char *v76;
  char *v77;
  dds3ObjectBaseControlWorkData_t *BaseControlWorkData;
  dds3Basic_t *v79;
  void *v81;
  struct sdfVector4_t v82;
  dds3Basic_t *pBasic;
  dds3Basic_t *pObjectBasic;

  v6 = &evt;
  pm1 = wdata->pm1;
  pBasic = 0;
  StageTable = pm1->StageTable;
  if (StageTable)
  {
    MajorNum = StageTable->MajorNum;
    MinorNum = StageTable->MinorNum;
    StageF1 = pm1->StageF1;
    StageF2 = pm1->StageF2;
    StageTB = pm1->StageTB;
    evtLoadArea_FromMemory(MajorNum, MinorNum, StageF1, StageF2, StageTB, 0);
    v14 = evtAddObject(0, pInfo);
    v15 = evtAddNameTable(wdata->pm1->NameTable1[wdata->pm1->StageTable->NameIndex]->Name, pInfo);
    data = v14->data;
    v14->nameindex = v15;
    set_Item(data->s, 0, MajorNum, 0);
    set_Item(v14->data->s, 1, MinorNum, 0);
  }
  workdata = dds3GetControlScene()->workdata;
  if (!workdata)
    goto LABEL_15;
  if (workdata->klass->_2.naturalAligment < (u32)naturalAligment || workdata->klass->_2.typeHierarchy[naturalAligment - 1] != dds3SceneBasic_t)
  {
LABEL_151:
  }
LABEL_15:
  v81 = workdata;
  for (i = *(dds3Basic_t *)(*((u64 *)workdata[1].monitor + 8) + 24); i; i = i->next)
  {
    if (i->name)
    {
      v45 = evtAddObject(2, pInfo);
      v45->basic = i;
      p_basic = &v45->basic;
      *((u32 *)p_basic - 2) = evtAddNameTable(i->name, pInfo);
    }
  }
  v20 = wdata->pm1;
  if (v20->UnitCount >= 1)
  {
    v21 = 2;
    while (v20->UnitCount < 1)
    {
LABEL_18:
      v22 = __OFSUB__(v21--, 1);
      if (v21 < 0 != v22)
        goto LABEL_65;
    }
    v23 = 0;
    while (1)
    {
      v26 = v20->UnitTable[v23];
      if (v26->FilePriority == v21)
        break;
LABEL_25:
      if (++v23 >= v20->UnitCount)
        goto LABEL_18;
    }
    v27 = v26->MajorNum;
    v28 = v26->MinorNum;
    v29 = v26->Data;
    mdlPackDecode(v27, v28, 259, v29, 0);
    if (!*((u32 *)*v6 + 56))
    v31 = v6;
    v32 = evtSetRegistUnit(v27, v28);
    v33 = evtAddObject(1, pInfo);
    pBasic = dds3GetControlScene();
    v34 = dds3SceneBasicSearch(pBasic, v32, 5u);
    v33->basic = v34;
    v35 = evtAddNameTable(wdata->pm1->NameTable1[wdata->pm1->UnitTable[v23]->NameIndex]->Name, pInfo);
    v33->nameindex = v35;
    basic = v33->basic;
    Name = pInfo->nametable[v35]->Name;
    basic->name = Name;
    set_Item(v33->data->s, 0, v27, 0);
    set_Item(v33->data->s, 1, v28, 0);
    pObjectBasic = dds3GetActiveScene();
    workdata = dds3SceneBasicSearch(pObjectBasic, v32, 5u)->workdata;
    if (workdata)
    {
      if (workdata->klass->_2.naturalAligment < (u32)v38 || workdata->klass->_2.typeHierarchy[v38 - 1] != Project_Basic_dds3UnitObjectBasicWorkData_t)
      {
        goto LABEL_151;
      }
    }
    loadScene = wdata->loadScene;
    image = workdata[2].klass[1]._1.image;
    if (loadScene && (s32)loadScene->max_length >= 1)
    {
      max_length = (u32)loadScene->max_length;
      m_Items = loadScene;
      while (v23 != m_Items->unitNo)
      {
        ++m_Items;
        if (!--max_length)
          goto LABEL_51;
      }
      model = m_Items->model;
      Change_36155280(model, &image->modelRoot, 0);
      if (mdlHasMotion(image))
      {
LABEL_58:
        mdlSmoothSingleMotion(image, 0, 0, 0.0, 0.0, 0.0);
        mdlSetMotionSpeed(image, 0.5);
      }
LABEL_22:
      v24 = v33->basic;
      pos = v24->poseset->pos;
      v82 = v24->poseset->pos;
      pos = v82;
      v24 = v33->basic;
      v33->orgPos = pos;
      v33->orgRot = v24->poseset->rot;
      v6 = v31;
      v20 = wdata->pm1;
      goto LABEL_25;
    }
    else
    {
LABEL_51:
    }
    if (mdlHasMotion(image))
      goto LABEL_58;
    goto LABEL_22;
  }
LABEL_65:
  if (v20->EffectCount >= 1)
  {
    v47 = 4;
    while (2)
    {
      switch (*(u32 *)(*((u64 *)&v20->EffectTable->obj.klass + v47) + 24))
      {
        case 0:
          v51 = 3;
          goto LABEL_85;
        case 1:
          v51 = 18;
          goto LABEL_85;
        case 2:
          v51 = 20;
          goto LABEL_85;
        case 3:
          v51 = 21;
          goto LABEL_85;
        case 4:
          v51 = 26;
LABEL_85:
          v53 = evtAddObject(v51, pInfo);
          v54 = wdata->pm1->NameTable1[*(s32 *)(*((u64 *)&wdata->pm1->EffectTable->obj.klass + v47) + 16)]->Name;
          v53->nameindex = evtAddNameTable(v54, pInfo);
          v48 = v53->data;
          v49 = *(Il2CppObject **)(*((u64 *)&wdata->pm1->EffectTable->obj.klass + v47) + 32);
          v48->p = v49;
          v20 = wdata->pm1;
LABEL_68:
          v50 = v47 - 3;
          ++v47;
          if (v50 < v20->EffectCount)
            continue;
          goto LABEL_87;
        default:
          goto LABEL_68;
      }
    }
  }
LABEL_87:
  if (v20->TmxCount >= 1)
  {
    v55 = 4;
    do
    {
      v56 = evtAddObject(24, pInfo);
      v57 = evtAddNameTable(wdata->pm1->NameTable1[*(s32 *)(*((u64 *)&wdata->pm1->TmxTable->obj.klass + v55) + 16)]->Name, pInfo);
      v58 = *(void *)(*((u64 *)&wdata->pm1->TmxTable->obj.klass + v55) + 32);
      v56->hTex = v58;
      v56 = ((char *)v56 + 64);
      LODWORD(v56[-1].firstframeinfo) = v57;
      v59 = v55 - 3;
      ++v55;
    }
    while (v59 < wdata->pm1->TmxCount);
  }
  for (j = *(dds3Basic_t *)(*((u64 *)v81[1].monitor + 13) + 24); j; j = j->next)
  {
    if (j->name)
    {
      v61 = evtAddObject(9, pInfo);
      v61->basic = j;
      v62 = &v61->basic;
      *((u32 *)v62 - 2) = evtAddNameTable(j->name, pInfo);
    }
  }
  pInfo->activecamera = 0;
  v63 = *(dds3Basic_t *)(*((u64 *)v81[1].monitor + 19) + 24);
  if (v63)
  {
LABEL_102:
    if (!v63->name)
      goto LABEL_101;
    monitor = v81[1].monitor;
    v65 = *(dds3Basic_t *)(monitor[8] + 24);
    if (!v65)
    {
      v66 = *(dds3Basic_t *)(monitor[13] + 24);
      if (!v66)
      {
LABEL_105:
        next = *(dds3Basic_t *)(monitor[11] + 24);
        if (!next)
          goto LABEL_101;
        while (1)
        {
LABEL_139:
          v76 = next->name;
          if (!v76)
            goto LABEL_138;
          v77 = Concat_54766928(v76, "_MOTION", 0);
          if (!Equals_54828784(v63->name, v77, 0))
            goto LABEL_138;
          pObjectBasic = next;
          BaseControlWorkData = dds3GetBaseControlWorkData(pObjectBasic);
          if (BaseControlWorkData)
          {
            v79 = BaseControlWorkData->pBasic[1];
            if (v79)
            {
              dds3MoverBasicSetPath(v79, v63);
              dds3MoverBasicMakePath(v79);
            }
          }
LABEL_138:
          next = next->next;
          if (!next)
            goto LABEL_101;
        }
      }
      while (1)
      {
LABEL_124:
        v72 = v66->name;
        if (!v72)
          goto LABEL_123;
        v73 = Concat_54766928(v72, "_MOTION", 0);
        if (!Equals_54828784(v63->name, v73, 0))
          goto LABEL_123;
        pObjectBasic = v66;
        v74 = dds3GetBaseControlWorkData(pObjectBasic);
        if (v74)
        {
          v75 = v74->pBasic[1];
          if (v75)
          {
            dds3MoverBasicSetPath(v75, v63);
            dds3MoverBasicMakePath(v75);
          }
        }
LABEL_123:
        v66 = v66->next;
        if (!v66)
        {
          next = *(dds3Basic_t *)(*((u64 *)v81[1].monitor + 11) + 24);
          if (next)
            goto LABEL_139;
LABEL_101:
          v63 = v63->next;
          if (!v63)
            return 1;
          goto LABEL_102;
        }
      }
    }
    while (1)
    {
      v68 = v65->name;
      if (!v68)
        goto LABEL_108;
      v69 = Concat_54766928(v68, "_MOTION", 0);
      if (!Equals_54828784(v63->name, v69, 0))
        goto LABEL_108;
      pObjectBasic = v65;
      v70 = dds3GetBaseControlWorkData(pObjectBasic);
      if (v70)
      {
        v71 = v70->pBasic[1];
        if (v71)
        {
          dds3MoverBasicSetPath(v71, v63);
          dds3MoverBasicMakePath(v71);
        }
      }
LABEL_108:
      v65 = v65->next;
      if (!v65)
      {
        monitor = v81[1].monitor;
        v66 = *(dds3Basic_t *)(monitor[13] + 24);
        if (v66)
          goto LABEL_124;
        goto LABEL_105;
      }
    }
  }
  return 1;
}

// 0x19b7400
void *oldEventSceneUnload(char *sName) {
  char *name;
  bool IsNullOrEmpty;
  void *result;
  s32 m_Handle;

  m_Handle = GetSceneByName(sName, 0).m_Handle;
  name = get_name((UnityEngine_SceneManagement_Scene_o)&m_Handle, 0);
  IsNullOrEmpty = IsNullOrEmpty(name, 0);
  result = 0;
  if (!IsNullOrEmpty)
  {
    return UnloadSceneAsync(sName, 0);
  }
  return result;
}

// 0x19b74b0
s32 evtSetGameData2and3(pmdProcessWork_t *wdata, evtViewerInfo_t *pInfo, s32 mode) {
  pmdPM2_t *pm2;
  pmdPM2_t *p_pm2;
  pmdCutInfo_t *CutInfo;
  s32 TotalFrame;
  s32 v10;
  s64 v11;
  s64 v12;
  s64 FrameCount;
  evtViewerObject_t *firstobjinfo;
  s16 v15;
  pmdDataInfo_t *v16;
  s16 v17;
  DataS *s;
  s16 v19;
  pmdDataInfo_t *v20;
  f32 f;
  DataS *v22;
  s16 v23;
  pmdDataInfo_t *v24;
  s32 v25;
  char *Name;
  pmdPM2_t *v27;
  pmdNameTable_t *NameTable2;
  s32 Frame;
  s64 v30;
  evtFrameInfo_t *v31;
  DataC *c;
  s8 Item;
  pmdDataInfo_t *v34;
  s32 i;
  s32 v36;
  pmdDataInfo_t *data;
  pmdPM2_t *v38;
  pmdNameTable_t *v39;
  char *v40;
  pmdPM2_t *v41;
  pmdNameTable_t *v42;
  char *v43;
  s64 j;
  s64 v45;
  evtViewerObject_t *next;
  char *v47;
  pmdPM2_t *v48;
  pmdNameTable_t *v49;
  s32 v50;
  evtFrameInfo_t *v51;
  pmdDataInfo_t *v52;
  f32 v53;
  DataS *v54;
  s16 v55;
  DataS *v56;
  s16 v57;
  s32 v58;
  pmdDataInfo_t *v59;
  f32 v60;
  s64 v61;
  s64 v62;
  s32 ObjectType;
  bool v64;
  s32 v65;
  evtViewerObject_t *v68;
  DataS *v69;
  s16 v70;
  s16 v71;
  DataS *v72;
  char *v73;
  pmdPM2_t *v74;
  pmdNameTable_t *v75;
  s32 v76;
  evtFrameInfo_t *v77;
  pmdFrameTable_t *v78;
  s32 v79;
  DataS *v80;
  s16 v81;
  pmdFrameTable_t *v83;
  s8 v84;
  DataC *v85;
  pmdPM2_t *v86;
  pmdNameTable_t *v87;
  char *v88;
  s8 v89;
  DataS *v90;
  s16 v91;
  DataC *v92;
  s8 v93;
  s16 v94;
  pmdDataInfo_t *v95;
  pmdPM2_t *v96;
  pmdNameTable_t *v97;
  char *v98;
  DataS *v99;
  s16 v100;
  s64 v101;
  DataC *v102;
  s8 v103;
  s16 v104;
  DataS *v105;
  pmdPM2_t *v106;
  pmdNameTable_t *v107;
  char *v108;
  s16 v109;
  pmdPM2_t *v110;
  DataC *v111;
  s8 v112;
  DataC *v113;
  s8 v114;
  pmdPM2_t *v115;
  u16 Length;
  DataC *v117;
  s8 v118;
  s8 v119;
  DataC *v120;
  pmdPM2_t *v121;
  pmdNameTable_t *v122;
  char *v123;
  s8 v124;
  s8 v125;
  DataC *v126;
  pmdPM2_t *v127;
  pmdNameTable_t *v128;
  char *v129;
  s8 v130;
  s8 v131;
  DataC *v132;
  pmdPM2_t *v133;
  pmdNameTable_t *v134;
  char *v135;
  s8 v136;
  DataC *v137;
  s8 v138;
  DataC *v139;
  s8 v140;
  DataC *v141;
  s8 v142;
  s64 v143;
  evtViewerObject_t *v144;
  s16 v145;
  char *v146;
  pmdPM2_t *v147;
  pmdNameTable_t *v148;
  s32 v149;
  evtFrameInfo_t *v150;
  pmdFrameTable_t *v151;
  u16 v152;
  pmdDataInfo_t *v153;
  DataS *v154;
  s16 v155;
  s16 v156;
  DataS *v157;
  pmdPM2_t *v158;
  pmdNameTable_t *v159;
  char *v160;
  s32 k;
  evtViewerObject_t *v162;
  pmdPM2_t *v163;
  evtViewerObject_t *v164;
  s64 m;
  DataS *v166;
  s16 v167;
  pmdFrameTable_t *v168;
  s32 v169;
  evtFrameInfo_t *v170;
  pmdDataInfo_t *v171;
  f32 v172;
  pmdDataInfo_t *v173;
  f32 v174;
  DataS *v175;
  s16 v176;
  DataS *v177;
  s16 v178;
  DataS *v179;
  s16 v180;
  DataS *v181;
  s16 v182;
  DataS *v183;
  s16 v184;
  DataC *v185;
  s8 v186;
  DataC *v187;
  s8 v188;
  DataC *v189;
  s8 v190;
  pmdPM2_t *v191;
  pmdFrameTable_t *v194;
  s32 NameIndex;
  pmdDataInfo_t *v196;
  s16 v197;
  pmdSceneLightTable_t *p;
  s64 naturalAligment;
  evtViewerObject_t *v200;
  pmdPM2_t *v201;
  evtViewerObject_t *v202;
  s64 v203;
  s64 v204;
  s64 v205;
  s32 v207;
  evtFrameInfo_t *v208;
  DataS *v209;
  s16 v210;
  s64 v211;
  evtViewerObject_t *v212;
  pmdPM2_t *v213;
  evtViewerObject_t *v214;
  s64 v215;
  DataS *v216;
  s16 v217;
  s64 v218;
  s64 v219;
  s32 v221;
  evtFrameInfo_t *v222;
  s64 v223;
  u16 v224;
  s64 v225;
  DataS *v226;
  s16 v227;
  DataS *v228;
  s16 v229;
  pmdDataInfo_t *v230;
  s32 v231;
  s32 Version;
  DataS *v233;
  s16 v234;
  evtViewerObject_t *v235;
  pmdPM2_t *v236;
  evtViewerObject_t *v237;
  s64 v238;
  s32 v240;
  DataS *v241;
  s16 v242;
  s64 v243;
  s64 v244;
  evtViewerObject_t *v245;
  pmdPM2_t *v246;
  evtViewerObject_t *v247;
  s64 v248;
  s32 v250;
  evtFrameInfo_t *v251;
  DataS *v252;
  s16 v253;
  pmdBlur2Table_t *Blur2Table;
  pmdBlur2Table_t *v255;
  pmdBlur2Table_t *v256;
  s64 v257;
  s64 v258;
  evtViewerObject_t *v259;
  pmdPM2_t *v260;
  evtViewerObject_t *v261;
  s64 n;
  s16 v263;
  DataS *v264;
  pmdFrameTable_t *v265;
  s32 v267;
  evtFrameInfo_t *v268;
  DataS *v269;
  s16 v270;
  pmdMultBlurTable_t *MBlurTable;
  pmdMultBlurTable_t *v272;
  pmdMultBlurTable_t *v273;
  DataS *v274;
  s16 v275;
  s16 v276;
  evtViewerObject_t *v277;
  s64 v278;
  s64 v279;
  s32 v280;
  evtViewerObject_t *v281;
  pmdPM2_t *v282;
  evtViewerObject_t *v283;
  s64 ii;
  s16 v285;
  DataS *v286;
  pmdFrameTable_t *v287;
  s32 v289;
  evtFrameInfo_t *v290;
  DataS *v291;
  s16 v292;
  pmdDistBlurTable_t *DBlurTable;
  pmdDistBlurTable_t *v294;
  pmdDistBlurTable_t *v295;
  DataS *v296;
  s16 v297;
  s16 v298;
  evtViewerObject_t *v299;
  s64 v300;
  s64 v301;
  s32 v302;
  evtViewerObject_t *v303;
  pmdPM2_t *v304;
  evtViewerObject_t *v305;
  s64 jj;
  s16 v307;
  DataS *v308;
  pmdFrameTable_t *v309;
  s32 v311;
  evtFrameInfo_t *v312;
  DataS *v313;
  s16 v314;
  pmdRipBlurTable_t *RBlurTable;
  pmdRipBlurTable_t *v316;
  pmdRipBlurTable_t *v317;
  DataS *v318;
  s16 v319;
  s16 v320;
  evtViewerObject_t *v321;
  s64 v322;
  s64 v323;
  s32 v324;
  evtViewerObject_t *v325;
  pmdPM2_t *v326;
  evtViewerObject_t *v327;
  s64 v328;
  s32 v330;
  evtFrameInfo_t *v331;
  DataS *v332;
  s16 v333;
  pmdHeikouBlurTable_t *HBlurTable;
  pmdHeikouBlurTable_t *v335;
  pmdHeikouBlurTable_t *v336;
  s64 v337;
  s64 v338;
  evtViewerObject_t *v339;
  pmdPM2_t *v340;
  evtViewerObject_t *v341;
  s64 v342;
  s32 v344;
  evtFrameInfo_t *v345;
  DataS *v346;
  s16 v347;
  pmdFilterTable_t *FilterTable;
  pmdFilterTable_t *v349;
  pmdFilterTable_t *v350;
  DataS *v351;
  s16 v352;
  s64 v353;
  s64 v354;
  evtViewerObject_t *v355;
  pmdPM2_t *v356;
  evtViewerObject_t *v357;
  s64 kk;
  s16 v359;
  DataS *v360;
  DataS *v361;
  s16 v362;
  pmdFrameTable_t *v363;
  s32 v365;
  evtFrameInfo_t *v366;
  DataS *v367;
  s16 v368;
  pmdMultFilterTable_t *MFilterTable;
  pmdMultFilterTable_t *v370;
  pmdMultFilterTable_t *v371;
  DataS *v372;
  s16 v373;
  s16 v374;
  evtViewerObject_t *v375;
  s64 v376;
  s64 v377;
  s32 v378;
  s32 MesHandle;
  evtViewerObject_t *v380;
  pmdPM2_t *v381;
  evtViewerObject_t *v382;
  s64 v383;
  s32 v385;
  evtFrameInfo_t *v386;
  s64 v387;
  u16 v388;
  s64 v389;
  DataS *v390;
  s16 v391;
  DataS *v392;
  s16 v393;
  DataC *v394;
  s8 v395;
  DataC *v396;
  s8 v397;
  DataC *v398;
  s8 v399;
  s64 v400;
  s64 v401;
  evtViewerObject_t *v402;
  s64 SoundFrameCount;
  char v404;
  evtViewerObject_t *v405;
  s64 v406;
  u64 v407;
  s64 v408;
  evtFrameInfo_t *v409;
  DataS *v410;
  s16 v411;
  DataS *v412;
  s16 v413;
  DataC *v414;
  s8 v415;
  pmdFrameTable_t *v416;
  s32 v417;
  pmdFrameTable_t *v418;
  s32 v420;
  evtFrameInfo_t *v421;
  DataS *v422;
  s16 v423;
  DataS *v424;
  s16 v425;
  u64 v426;
  s64 v427;
  evtFrameInfo_t *v428;
  DataS *v429;
  s16 v430;
  DataS *v431;
  s16 v432;
  DataS *v433;
  s16 v434;
  DataC *v435;
  s8 v436;
  DataC *v437;
  s8 v438;
  DataC *v439;
  s8 v440;
  pmdFrameTable_t *v441;
  s32 v442;
  pmdFrameTable_t *v443;
  s32 v445;
  evtFrameInfo_t *v446;
  DataS *v447;
  s16 v448;
  DataS *v449;
  s16 v450;
  DataS *v451;
  s16 v452;
  evtViewerObject_t *v453;
  pmdPM2_t *v454;
  evtViewerObject_t *v455;
  s64 v456;
  s32 v458;
  evtFrameInfo_t *v459;
  s64 v460;
  u16 v461;
  s64 v462;
  DataS *v463;
  s16 v464;
  DataC *v465;
  s8 v466;
  DataC *v467;
  s8 v468;
  DataC *v469;
  s8 v470;
  DataC *v471;
  s8 v472;
  s64 v473;
  s64 v474;
  evtViewerObject_t *v475;
  pmdPM2_t *v476;
  evtViewerObject_t *v477;
  s64 v478;
  s32 v480;
  evtFrameInfo_t *v481;
  s64 v482;
  u16 v483;
  s64 v484;
  DataS *v485;
  s16 v486;
  s64 v487;
  s64 v488;
  evtViewerObject_t *v489;
  pmdPM2_t *v490;
  evtViewerObject_t *v491;
  s64 v492;
  s32 v494;
  evtFrameInfo_t *v495;
  DataS *v496;
  s16 v497;
  DataS *v498;
  s16 v499;
  DataS *v500;
  s16 v501;
  s64 v502;
  s64 v503;
  s64 v504;
  s64 mm;
  evtViewerObject_t *v506;
  evtFrameInfo_t *v507;
  DataC *v508;
  s8 v509;
  DataC *v510;
  s8 v511;
  DataS *v512;
  s16 v513;
  DataS *v514;
  s16 v515;
  DataUC *uc;
  u8 v517;
  DataUC *v518;
  u8 v519;
  DataUC *v520;
  u8 v521;
  DataUC *v522;
  u8 v523;
  pmdDataInfo_t *v524;
  f32 v525;
  pmdDataInfo_t *v526;
  f32 v527;
  DataC *v528;
  s8 v529;
  s64 v530;
  char *v531;
  pmdPM2_t *v532;
  pmdNameTable_t *v533;
  s32 v534;
  evtViewerObject_t *v535;
  pmdPM2_t *v536;
  evtViewerObject_t *v537;
  s64 v538;
  s32 v540;
  evtFrameInfo_t *v541;
  s64 v542;
  u16 v543;
  s64 v544;
  DataS *v545;
  s16 v546;
  DataS *v547;
  s16 v548;
  s64 v549;
  s64 v550;
  evtViewerObject_t *v551;
  pmdPM2_t *v552;
  evtViewerObject_t *v553;
  s64 v554;
  s32 v556;
  evtFrameInfo_t *v557;
  s64 v558;
  u16 v559;
  s64 v560;
  DataS *v561;
  s16 v562;
  DataC *v563;
  s8 v564;
  DataC *v565;
  s8 v566;
  s64 v567;
  s64 v568;
  evtViewerObject_t *v569;
  pmdPM2_t *v570;
  evtViewerObject_t *v571;
  s64 v572;
  s32 v574;
  evtFrameInfo_t *v575;
  s64 v576;
  u16 v577;
  s64 v578;
  DataS *v579;
  s16 v580;
  s64 v581;
  s64 v582;
  evtViewerObject_t *v583;
  pmdPM2_t *v584;
  evtViewerObject_t *v585;
  s64 nn;
  s32 v588;
  evtFrameInfo_t *v589;
  DataS *v590;
  s16 v591;
  DataS *v592;
  s16 v593;
  DataS *v594;
  s16 v595;
  DataS *v596;
  s16 v597;
  DataC *v598;
  s8 v599;
  DataC *v600;
  s8 v601;
  pmdFrameTable_t *v602;
  evtViewerObject_t *v603;
  pmdPM2_t *v604;
  evtViewerObject_t *v605;
  s64 v606;
  s32 v608;
  DataC *v609;
  s8 v610;
  s64 v611;
  s64 v612;
  evtViewerObject_t *v613;
  pmdPM2_t *v614;
  evtViewerObject_t *v615;
  s64 v616;
  s32 v618;
  evtFrameInfo_t *v619;
  s64 v620;
  s64 v621;
  evtViewerObject_t *v622;
  pmdPM2_t *v623;
  evtViewerObject_t *v624;
  s64 i1;
  s32 v627;
  evtFrameInfo_t *v628;
  DataC *v629;
  s8 v630;
  DataC *v631;
  s8 v632;
  DataS *v633;
  s16 v634;
  DataS *v635;
  s16 v636;
  DataS *v637;
  s16 v638;
  DataUC *v639;
  u8 v640;
  DataUC *v641;
  u8 v642;
  DataUC *v643;
  u8 v644;
  DataUC *v645;
  u8 v646;
  pmdDataInfo_t *v647;
  f32 v648;
  pmdDataInfo_t *v649;
  f32 v650;
  DataC *v651;
  s8 v652;
  pmdFrameTable_t *v653;
  evtViewerObject_t *v654;
  pmdPM2_t *v655;
  evtViewerObject_t *v656;
  s64 i2;
  s8 v658;
  pmdFrameTable_t *v659;
  s32 v661;
  evtFrameInfo_t *v662;
  pmdDataInfo_t *v663;
  pmdFrameTable_t *v664;
  s32 v665;
  pmdDataInfo_t *v666;
  s32 v667;
  pmdDataInfo_t *v668;
  s32 v669;
  pmdDataInfo_t *v670;
  s32 v671;
  pmdDataInfo_t *v672;
  s32 v673;
  pmdDataInfo_t *v674;
  s32 v675;
  pmdDataInfo_t *v676;
  s32 v677;
  DataC *v678;
  evtViewerObject_t *v679;
  pmdPM2_t *v680;
  evtViewerObject_t *v681;
  s64 v682;
  s32 v684;
  pmdDataInfo_t *v685;
  s32 v686;
  s64 v687;
  s64 v688;
  evtViewerObject_t *v689;
  pmdPM2_t *v690;
  evtViewerObject_t *v691;
  s64 v692;
  s32 v694;
  pmdDataInfo_t *v695;
  s32 v696;
  s64 v697;
  s64 v698;
  evtViewerObject_t *v699;
  pmdPM2_t *v700;
  evtViewerObject_t *v701;
  s64 v702;
  s32 v704;
  pmdDataInfo_t *v705;
  s32 v706;
  s64 v707;
  s64 v708;
  evtViewerObject_t *v709;
  pmdPM2_t *v710;
  evtViewerObject_t *v711;
  s64 v712;
  s32 v714;
  evtFrameInfo_t *v715;
  pmdDataInfo_t *v716;
  s32 v717;
  pmdDataInfo_t *v718;
  s32 v719;
  s64 v720;
  s64 v721;
  evtViewerObject_t *v722;
  pmdPM2_t *v723;
  evtViewerObject_t *v724;
  s64 i3;
  s32 v726;
  pmdFrameTable_t *v727;
  s32 v729;
  evtFrameInfo_t *v730;
  pmdDataInfo_t *v731;
  s32 v732;
  pmdDataInfo_t *v733;
  s32 v734;
  pmdDataInfo_t *v735;
  s32 v736;
  pmdDataInfo_t *v737;
  s32 v738;
  pmdDataInfo_t *v739;
  s32 v740;
  pmdDataInfo_t *v741;
  s32 v742;
  pmdDataInfo_t *v743;
  s32 v744;
  pmdDataInfo_t *v745;
  evtViewerObject_t *v746;
  pmdPM2_t *v747;
  evtViewerObject_t *v748;
  s64 i4;
  s32 v750;
  pmdFrameTable_t *v751;
  s32 v753;
  evtFrameInfo_t *v754;
  pmdDataInfo_t *v755;
  s32 v756;
  pmdDataInfo_t *v757;
  s32 v758;
  pmdDataInfo_t *v759;
  s32 v760;
  pmdDataInfo_t *v761;
  s32 v762;
  pmdDataInfo_t *v763;
  s32 v764;
  pmdDataInfo_t *v765;
  s32 v766;
  pmdDataInfo_t *v767;
  s32 v768;
  pmdDataInfo_t *v769;
  evtViewerObject_t *v770;
  pmdPM2_t *v771;
  evtViewerObject_t *v772;
  s64 v773;
  s32 v775;
  pmdDataInfo_t *v776;
  s32 v777;
  s64 v778;
  s64 v779;
  s64 v780;
  s32 v781;
  evtViewerObject_t *v782;
  pmdObjectTable_t *v783;
  s16 Offset;
  s32 union0;
  s64 v786;
  pmdNameTable_t *nametable;
  pmdObjectTable_t *object_data;
  pmdObjectTable_t *v789;
  s16 v790;
  s32 type;
  s32 v792;
  s32 ObjectNo;
  pmdObjectTable_t *v794;
  s16 v795;
  s32 v796;
  pmdObjectTable_t *v797;
  evtViewerObject_t *v799;
  s32 v800;
  s32 *IntVariable;
  u32 v804;
  pmdProcessWork_t *v807;
  dds3Basic_t *scene;

  scene = 0;
  v807 = wdata;
  p_pm2 = &wdata->pm2;
  pm2 = wdata->pm2;
  CutInfo = pm2->CutInfo;
  if (CutInfo)
  {
    TotalFrame = CutInfo->TotalFrame;
    pInfo->totalframe = TotalFrame;
    v10 = TotalFrame - 1;
    v11 = *(u64 *)&CutInfo->FirstFrame;
    *(u64 *)&pInfo->firstframe = v11;
    pInfo->cutVal = CutInfo->val;
    if ((v11 & (u32)~((s32)v11 >> 31)) < v10)
      v10 = v11 & ~((s32)v11 >> 31);
    pInfo->nowframe = v10;
    pm2 = p_pm2;
  }
  if (pm2->FrameCount < 1)
    goto LABEL_208;
  v12 = 0;
  do
  {
    if (pm2->FrameTable[v12]->ObjectType != 1)
      goto LABEL_10;
    firstobjinfo = pInfo->firstobjinfo;
    if (firstobjinfo)
    {
      while (1)
      {
        Name = pInfo->nametable[firstobjinfo->nameindex]->Name;
        v27 = p_pm2;
        NameTable2 = p_pm2->NameTable2;
        v27 = p_pm2;
        if (!Equals_54828784(Name, NameTable2[v27->FrameTable[v12]->NameIndex]->Name, 0))
          goto LABEL_22;
        if (get_Item(p_pm2->FrameTable[v12]->Data[6]->c, 0, 0))
        {
          if (pInfo->useFrameNum != get_Item(p_pm2->FrameTable[v12]->Data[6]->c, 0, 0))
            goto LABEL_22;
        }
        Frame = p_pm2->FrameTable[v12]->Frame;
        v30 = v12;
        v31 = evtAddFrameInfo(firstobjinfo, Frame, pInfo);
        c = v31->data[0]->c;
        Item = get_Item(p_pm2->FrameTable[v12]->Data[0]->c, 0, 0);
        set_Item(c, 0, Item, 0);
        v34 = v31->data[1];
        i = get_i(p_pm2->FrameTable[v12]->Data[1], 0);
        set_i(v34, i, 0);
        v36 = evtAddNameTable(p_pm2->NameTable2[p_pm2->FrameTable[v12]->NameIndex]->Name, pInfo);
        data = v31->data;
        v31->nameindex = v36;
        if (get_Item(data[0]->c, 0, 0) == 7)
        {
          if (get_Item(p_pm2->FrameTable[v12]->Data[1]->s, 0, 0) != -1)
            break;
        }
LABEL_19:
        s = v31->data[2]->s;
        v19 = get_Item(p_pm2->FrameTable[v30]->Data[2]->s, 0, 0);
        set_Item(s, 0, v19, 0);
        v20 = v31->data[3];
        f = get_f(p_pm2->FrameTable[v30]->Data[3], 0);
        set_f(v20, f, 0);
        v22 = v31->data[4]->s;
        v23 = get_Item(p_pm2->FrameTable[v30]->Data[4]->s, 0, 0);
        set_Item(v22, 0, v23, 0);
        v24 = v31->data[5];
        v25 = get_i(p_pm2->FrameTable[v30]->Data[5], 0);
        set_i(v24, v25, 0);
LABEL_22:
        firstobjinfo = firstobjinfo->next;
        if (!firstobjinfo)
        {
          pm2 = p_pm2;
          goto LABEL_10;
        }
      }
      scene = dds3GetActiveScene();
      v38 = p_pm2;
      v39 = p_pm2->NameTable2;
      v38 = p_pm2;
      v40 = v39[get_Item(v38->FrameTable[v12]->Data[1]->s, 0, 0)]->Name;
      if (dds3SceneBasicSearchName(scene, v40))
      {
        v41 = p_pm2;
        v42 = p_pm2->NameTable2;
        v41 = p_pm2;
        v43 = v42[get_Item(v41->FrameTable[v12]->Data[1]->s, 0, 0)]->Name;
        v15 = evtAddNameTable(v43, pInfo);
        v16 = v31->data;
        v17 = v15;
        goto LABEL_18;
      }
      v16 = v31->data;
      v17 = -1;
LABEL_18:
      set_Item(v16[1]->s, 0, v17, 0);
      goto LABEL_19;
    }
LABEL_10:
    FrameCount = pm2->FrameCount;
    ++v12;
  }
  while (v12 < FrameCount);
  if ((s32)FrameCount < 1)
    goto LABEL_208;
  for (j = 0; j < v45; ++j)
  {
    if (pm2->FrameTable[j]->ObjectType == 2)
    {
      next = pInfo->firstobjinfo;
      if (next)
      {
        do
        {
          v47 = pInfo->nametable[next->nameindex]->Name;
          v48 = p_pm2;
          v49 = p_pm2->NameTable2;
          v48 = p_pm2;
          if (Equals_54828784(v47, v49[v48->FrameTable[j]->NameIndex]->Name, 0))
          {
            v50 = p_pm2->FrameTable[j]->Frame;
            v51 = evtAddFrameInfo(next, v50, pInfo);
            v52 = v51->data[0];
            v53 = get_f(p_pm2->FrameTable[j]->Data[0], 0);
            set_f(v52, v53, 0);
            v54 = v51->data[1]->s;
            v55 = get_Item(p_pm2->FrameTable[j]->Data[1]->s, 0, 0);
            set_Item(v54, 0, v55, 0);
            v56 = v51->data[1]->s;
            v57 = get_Item(p_pm2->FrameTable[j]->Data[1]->s, 1, 0);
            set_Item(v56, 1, v57, 0);
            v58 = evtAddNameTable(p_pm2->NameTable2[p_pm2->FrameTable[j]->NameIndex]->Name, pInfo);
            v59 = v51->data;
            v51->nameindex = v58;
            v60 = get_f(v59[0], 0);
            dds3CameraObjectBasicSetFovy(&next->basic, v60);
          }
          next = next->next;
        }
        while (next);
        pm2 = p_pm2;
      }
    }
    v45 = pm2->FrameCount;
  }
  if ((s32)v45 >= 1)
  {
    v61 = 0;
    while (1)
    {
      ObjectType = pm2->FrameTable[v61]->ObjectType;
      if (ObjectType <= 18)
      {
        if (ObjectType != 3 && ObjectType != 18)
          goto LABEL_76;
        goto LABEL_91;
      }
      v64 = (u32)ObjectType > 0x1A;
      v65 = (1 << ObjectType) & 0x4300000;
      if (v64 || v65 == 0)
        goto LABEL_76;
LABEL_91:
      v68 = pInfo->firstobjinfo;
      if (v68)
      {
        while (1)
        {
          v73 = pInfo->nametable[v68->nameindex]->Name;
          v74 = p_pm2;
          v75 = p_pm2->NameTable2;
          v74 = p_pm2;
          if (!Equals_54828784(v73, v75[v74->FrameTable[v61]->NameIndex]->Name, 0))
            goto LABEL_98;
          v76 = p_pm2->FrameTable[v61]->Frame;
          v77 = evtAddFrameInfo(v68, v76, pInfo);
          v78 = p_pm2->FrameTable[v61];
          v79 = v78->ObjectType;
          if (v79 <= 18)
            break;
          if ((v79 & 0xFFFFFFFE) == 0x14)
          {
            v80 = v77->data[0]->s;
            v78 = p_pm2->FrameTable[v61];
            v81 = get_Item(v78->Data[0]->s, 1, 0);
            set_Item(v80, 1, v81, 0);
            v83 = p_pm2->FrameTable[v61];
            v77->length = v83->Length;
            v83 = p_pm2->FrameTable[v61];
            v84 = get_Item(v83->Data[1]->c, 0, 0);
            v85 = v77->data[1]->c;
            if (v84 < 0)
            {
              v89 = -1;
            }
            else
            {
              v86 = p_pm2;
              v87 = p_pm2->NameTable2;
              v86 = p_pm2;
              v88 = v87[get_Item(v86->FrameTable[v61]->Data[1]->c, 0, 0)]->Name;
              v89 = evtAddNameTable(v88, pInfo);
            }
            set_Item(v85, 0, v89, 0);
            v119 = get_Item(p_pm2->FrameTable[v61]->Data[1]->c, 1, 0);
            v120 = v77->data[1]->c;
            if (v119 < 0)
            {
              v124 = -1;
            }
            else
            {
              v121 = p_pm2;
              v122 = p_pm2->NameTable2;
              v121 = p_pm2;
              v123 = v122[get_Item(v121->FrameTable[v61]->Data[1]->c, 1, 0)]->Name;
              v124 = evtAddNameTable(v123, pInfo);
            }
            set_Item(v120, 1, v124, 0);
            v125 = get_Item(p_pm2->FrameTable[v61]->Data[1]->c, 2, 0);
            v126 = v77->data[1]->c;
            if (v125 < 0)
            {
              v130 = -1;
            }
            else
            {
              v127 = p_pm2;
              v128 = p_pm2->NameTable2;
              v127 = p_pm2;
              v129 = v128[get_Item(v127->FrameTable[v61]->Data[1]->c, 2, 0)]->Name;
              v130 = evtAddNameTable(v129, pInfo);
            }
            set_Item(v126, 2, v130, 0);
            v131 = get_Item(p_pm2->FrameTable[v61]->Data[1]->c, 3, 0);
            v132 = v77->data[1]->c;
            if (v131 < 0)
            {
              v136 = -1;
            }
            else
            {
              v133 = p_pm2;
              v134 = p_pm2->NameTable2;
              v133 = p_pm2;
              v135 = v134[get_Item(v133->FrameTable[v61]->Data[1]->c, 3, 0)]->Name;
              v136 = evtAddNameTable(v135, pInfo);
            }
            set_Item(v132, 3, v136, 0);
            v137 = v77->data[0]->c;
            v138 = get_Item(p_pm2->FrameTable[v61]->Data[0]->c, 1, 0);
            set_Item(v137, 1, v138, 0);
            v139 = v77->data[0]->c;
            v140 = get_Item(p_pm2->FrameTable[v61]->Data[2]->c, 0, 0);
            set_Item(v139, 2, v140, 0);
            v141 = v77->data[2]->c;
            v142 = get_Item(p_pm2->FrameTable[v61]->Data[2]->c, 0, 0);
            set_Item(v141, 0, v142, 0);
            if (p_pm2->Header2->Version <= 8)
              v77->length = 0;
            goto LABEL_98;
          }
          if (v79 == 26)
            goto LABEL_129;
LABEL_98:
          v68 = v68->next;
          if (!v68)
          {
            pm2 = p_pm2;
            goto LABEL_76;
          }
        }
        if (v79 != 3)
        {
          if (v79 != 18)
            goto LABEL_98;
          v90 = v77->data[0]->s;
          v78 = p_pm2->FrameTable[v61];
          v91 = get_Item(v78->Data[0]->s, 0, 0);
          set_Item(v90, 0, v91, 0);
          v92 = v77->data[1]->c;
          v93 = get_Item(p_pm2->FrameTable[v61]->Data[1]->c, 0, 0);
          set_Item(v92, 0, v93, 0);
          v94 = get_Item(p_pm2->FrameTable[v61]->Data[0]->s, 1, 0);
          v95 = v77->data[0];
          v69 = v95->s;
          if (v94 < 0)
          {
            v72 = v95->s;
            v71 = -1;
          }
          else
          {
            v96 = p_pm2;
            v97 = p_pm2->NameTable2;
            v96 = p_pm2;
            v98 = v97[get_Item(v96->FrameTable[v61]->Data[0]->s, 1, 0)]->Name;
            v70 = evtAddNameTable(v98, pInfo);
LABEL_96:
            v71 = v70;
            v72 = v69;
          }
          set_Item(v72, 1, v71, 0);
          goto LABEL_98;
        }
LABEL_129:
        v99 = v77->data[0]->s;
        v78 = p_pm2->FrameTable[v61];
        v100 = get_Item(v78->Data[0]->s, 1, 0);
        set_Item(v99, 1, v100, 0);
        v101 = v61;
        v102 = v77->data[1]->c;
        v103 = get_Item(p_pm2->FrameTable[v61]->Data[1]->c, 1, 0);
        set_Item(v102, 1, v103, 0);
        v104 = get_Item(p_pm2->FrameTable[v61]->Data[1]->s, 1, 0);
        v105 = v77->data[1]->s;
        if (v104 < 0)
        {
          v109 = -1;
        }
        else
        {
          v106 = p_pm2;
          v107 = p_pm2->NameTable2;
          v106 = p_pm2;
          v108 = v107[get_Item(v106->FrameTable[v61]->Data[1]->s, 1, 0)]->Name;
          v109 = evtAddNameTable(v108, pInfo);
        }
        set_Item(v105, 1, v109, 0);
        v111 = v77->data[1]->c;
        v112 = get_Item(p_pm2->FrameTable[v101]->Data[1]->c, 0, 0);
        set_Item(v111, 0, v112, 0);
        v113 = v77->data[1]->c;
        v114 = get_Item(p_pm2->FrameTable[v101]->Data[2]->c, 0, 0);
        set_Item(v113, 1, v114, 0);
        v115 = p_pm2;
        if (p_pm2->Header2->Version < 4)
        {
          Length = 0;
        }
        else
        {
          v115 = p_pm2;
          Length = v115->FrameTable[v61]->Length;
        }
        v77->length = Length;
        v117 = v77->data[2]->c;
        v115 = p_pm2;
        v118 = get_Item(v115->FrameTable[v61]->Data[2]->c, 0, 0);
        set_Item(v117, 0, v118, 0);
        v110 = p_pm2;
        if (p_pm2->Header2->Version <= 8)
          v77->length = 0;
        v69 = v77->data[3]->s;
        v110 = p_pm2;
        v70 = get_Item(v110->FrameTable[v61]->Data[3]->s, 1, 0);
        goto LABEL_96;
      }
LABEL_76:
      v62 = pm2->FrameCount;
      if (++v61 >= v62)
      {
        if ((s32)v62 >= 1)
        {
          v143 = 0;
          while (1)
          {
            if (pm2->FrameTable[v143]->ObjectType == 9)
              goto LABEL_190;
            goto LABEL_9001;
            if (p_pm2->FrameTable[v143]->ObjectType == 9)
            {
LABEL_190:
              v144 = pInfo->firstobjinfo;
              if (v144)
              {
                do
                {
                  v146 = pInfo->nametable[v144->nameindex]->Name;
                  v147 = p_pm2;
                  v148 = p_pm2->NameTable2;
                  v147 = p_pm2;
                  if (Equals_54828784(v146, v148[v147->FrameTable[v143]->NameIndex]->Name, 0))
                  {
                    v149 = p_pm2->FrameTable[v143]->Frame;
                    v150 = evtAddFrameInfo(v144, v149, pInfo);
                    v151 = p_pm2->FrameTable[v143];
                    v152 = v151->Length;
                    v153 = v151->Data;
                    v150->length = v152;
                    v154 = v150->data[0]->s;
                    v155 = get_Item(v153[0]->s, 1, 0);
                    set_Item(v154, 1, v155, 0);
                    v156 = get_Item(p_pm2->FrameTable[v143]->Data[0]->s, 0, 0);
                    v157 = v150->data[0]->s;
                    if (v156 < 0)
                    {
                      v145 = -1;
                    }
                    else
                    {
                      v158 = p_pm2;
                      v159 = p_pm2->NameTable2;
                      v158 = p_pm2;
                      v160 = v159[get_Item(v158->FrameTable[v143]->Data[0]->s, 0, 0)]->Name;
                      v145 = evtAddNameTable(v160, pInfo);
                    }
                    set_Item(v157, 0, v145, 0);
                  }
                  v144 = v144->next;
                }
                while (v144);
                pm2 = p_pm2;
              }
            }
LABEL_9001:
            if (++v143 >= pm2->FrameCount)
              goto LABEL_208;
          }
        }
        break;
      }
    }
  }
LABEL_208:
  for (k = 0; k != 7; ++k)
  {
    v162 = evtAddObject(10, pInfo);
    v163 = p_pm2;
    v162->myno = k;
    if (v163->FrameCount >= 1)
    {
      v164 = v162;
      for (m = 0; m < p_pm2->FrameCount; ++m)
      {
        v168 = v163->FrameTable[m];
        if (v168->ObjectType != 10)
          goto LABEL_215;
        v168 = p_pm2->FrameTable[m];
        if (k == get_Item(v168->Data[2]->s, 0, 0))
        {
          v169 = p_pm2->FrameTable[m]->Frame;
          v170 = evtAddFrameInfo(v164, v169, pInfo);
          v171 = v170->data[0];
          v172 = get_f(p_pm2->FrameTable[m]->Data[0], 0);
          set_f(v171, v172, 0);
          v173 = v170->data[1];
          v174 = get_f(p_pm2->FrameTable[m]->Data[1], 0);
          set_f(v173, v174, 0);
          v175 = v170->data[2]->s;
          v176 = get_Item(p_pm2->FrameTable[m]->Data[2]->s, 0, 0);
          set_Item(v175, 0, v176, 0);
          v177 = v170->data[3]->s;
          v178 = get_Item(p_pm2->FrameTable[m]->Data[3]->s, 0, 0);
          set_Item(v177, 0, v178, 0);
          v179 = v170->data[3]->s;
          v180 = get_Item(p_pm2->FrameTable[m]->Data[3]->s, 1, 0);
          set_Item(v179, 1, v180, 0);
          v181 = v170->data[4]->s;
          v182 = get_Item(p_pm2->FrameTable[m]->Data[4]->s, 0, 0);
          set_Item(v181, 0, v182, 0);
          v183 = v170->data[4]->s;
          v184 = get_Item(p_pm2->FrameTable[m]->Data[4]->s, 1, 0);
          set_Item(v183, 1, v184, 0);
          v185 = v170->data[5]->c;
          v186 = get_Item(p_pm2->FrameTable[m]->Data[5]->c, 0, 0);
          set_Item(v185, 0, v186, 0);
          v187 = v170->data[5]->c;
          v188 = get_Item(p_pm2->FrameTable[m]->Data[5]->c, 1, 0);
          set_Item(v187, 1, v188, 0);
          v189 = v170->data[5]->c;
          v190 = get_Item(p_pm2->FrameTable[m]->Data[5]->c, 2, 0);
          set_Item(v189, 2, v190, 0);
          v191 = p_pm2;
          if (p_pm2->Header2->Version <= 6)
          {
            v191 = p_pm2;
            v170->length = get_Item(v191->FrameTable[m]->Data[2]->s, 1, 0);
          }
          else
          {
            v191 = p_pm2;
            v170->length = v191->FrameTable[m]->Length;
          }
          v194 = p_pm2->FrameTable[m];
          NameIndex = v194->NameIndex;
          v196 = v194->Data[2];
          v170->nameindex = NameIndex;
          v197 = get_Item(v196->s, 1, 0);
          p = v170->p;
          if (p)
          {
            if (p->klass->_2.naturalAligment < (u32)naturalAligment || p->klass->_2.typeHierarchy[naturalAligment - 1] != pmdSceneLightTable_t)
            {
LABEL_239:
            }
          }
          ClassCopy(p, p_pm2->SLightTable[v197], 0);
          v166 = v170->data[3]->s;
          v167 = get_Item(p_pm2->FrameTable[m]->Data[3]->s, 0, 0);
          set_Item(v166, 0, v167, 0);
        }
LABEL_215:
        v163 = p_pm2;
      }
    }
  }
  v200 = evtAddObject(11, pInfo);
  v201 = p_pm2;
  if (p_pm2->FrameCount >= 1)
  {
    v202 = v200;
    v203 = 4;
    do
    {
      v205 = *((u64 *)&v201->FrameTable->obj.klass + v203);
      if (*(u32 *)(v205 + 16) == 11)
      {
        v207 = *(u16 *)(v205 + 20);
        v208 = evtAddFrameInfo(v202, v207, pInfo);
        v209 = v208->data[0]->s;
        v210 = get_Item(*(DataS *)(*(u64 *)(*(u64 *)(*((u64 *)&p_pm2->FrameTable->obj.klass + v203) + 32) + 32) + 40), 0, 0);
        set_Item(v209, 0, v210, 0);
        p = v208->p;
        if (p)
        {
          if (p->klass->_2.naturalAligment < (u32)v211 || p->klass->_2.typeHierarchy[v211 - 1] != pmdSceneFogTable_t)
          {
            goto LABEL_239;
          }
        }
        ClassCopy(p, p_pm2->SFogTable[*(u16 *)(*((u64 *)&p_pm2->FrameTable->obj.klass + v203) + 22)], 0);
        v201 = p_pm2;
      }
      v204 = v203 - 3;
      ++v203;
    }
    while (v204 < v201->FrameCount);
  }
  v212 = evtAddObject(12, pInfo);
  v213 = p_pm2;
  if (p_pm2->FrameCount >= 1)
  {
    v214 = v212;
    v215 = 4;
    do
    {
      v219 = *((u64 *)&v213->FrameTable->obj.klass + v215);
      if (*(u32 *)(v219 + 16) == 12)
      {
        v221 = *(u16 *)(v219 + 20);
        v222 = evtAddFrameInfo(v214, v221, pInfo);
        v223 = *((u64 *)&p_pm2->FrameTable->obj.klass + v215);
        v224 = *(u16 *)(v223 + 22);
        v225 = *(u64 *)(v223 + 32);
        v222->length = v224;
        v226 = v222->data[0]->s;
        v227 = get_Item(*(DataS *)(*(u64 *)(v225 + 32) + 40), 0, 0);
        set_Item(v226, 0, v227, 0);
        v228 = v222->data[0]->s;
        v229 = get_Item(*(DataS *)(*(u64 *)(*(u64 *)(*((u64 *)&p_pm2->FrameTable->obj.klass + v215) + 32) + 32) + 40), 1, 0);
        set_Item(v228, 1, v229, 0);
        v230 = v222->data[1];
        v231 = get_i(*(pmdDataInfo_t *)(*(u64 *)(*((u64 *)&p_pm2->FrameTable->obj.klass + v215) + 32) + 40), 0);
        set_i(v230, v231, 0);
        Version = p_pm2->Header2->Version;
        if (Version == 1)
        {
          set_Item(v222->data[0]->s, 1, 0, 0);
          Version = p_pm2->Header2->Version;
        }
        if (Version == 2)
        {
          v233 = v222->data[0]->s;
          v234 = get_Item(v233, 1, 0);
          set_Item(v233, 1, v234 - 128, 0);
          if (get_Item(v222->data[0]->s, 1, 0) <= -256)
            set_Item(v222->data[0]->s, 1, 65281, 0);
          if (get_Item(v222->data[0]->s, 1, 0) >= 256)
            set_Item(v222->data[0]->s, 1, 255, 0);
        }
        v216 = v222->data[3]->s;
        v217 = get_Item(*(DataS *)(*(u64 *)(*(u64 *)(*((u64 *)&p_pm2->FrameTable->obj.klass + v215) + 32) + 56) + 40), 0, 0);
        set_Item(v216, 0, v217, 0);
        v213 = p_pm2;
        goto LABEL_265;
      }
LABEL_265:
      v218 = v215 - 3;
      ++v215;
    }
    while (v218 < v213->FrameCount);
  }
  v235 = evtAddObject(22, pInfo);
  v236 = p_pm2;
  if (p_pm2->FrameCount >= 1)
  {
    v237 = v235;
    v238 = 4;
    do
    {
      v244 = *((u64 *)&v236->FrameTable->obj.klass + v238);
      if (*(u32 *)(v244 + 16) == 22)
      {
        v240 = *(u16 *)(v244 + 20);
        v241 = evtAddFrameInfo(v237, v240, pInfo)->data[0]->s;
        v242 = get_Item(*(DataS *)(*(u64 *)(*(u64 *)(*((u64 *)&p_pm2->FrameTable->obj.klass + v238) + 32) + 32) + 40), 0, 0);
        set_Item(v241, 0, v242, 0);
        v236 = p_pm2;
      }
      v243 = v238 - 3;
      ++v238;
    }
    while (v243 < v236->FrameCount);
  }
  v245 = evtAddObject(13, pInfo);
  v246 = p_pm2;
  if (p_pm2->FrameCount >= 1)
  {
    v247 = v245;
    v248 = 4;
    do
    {
      v258 = *((u64 *)&v246->FrameTable->obj.klass + v248);
      if (*(u32 *)(v258 + 16) == 13)
      {
        v250 = *(u16 *)(v258 + 20);
        v251 = evtAddFrameInfo(v247, v250, pInfo);
        v252 = v251->data[0]->s;
        v253 = get_Item(*(DataS *)(*(u64 *)(*(u64 *)(*((u64 *)&p_pm2->FrameTable->obj.klass + v248) + 32) + 32) + 40), 0, 0);
        set_Item(v252, 0, v253, 0);
        Blur2Table = p_pm2->Blur2Table;
        v255 = Blur2Table[get_Item(*(DataS *)(*(u64 *)(*(u64 *)(*((u64 *)&p_pm2->FrameTable->obj.klass + v248) + 32) + 32) + 40), 1, 0)];
        v256 = Allocate(pmdBlur2Table_t);
        _ctor_27153280(v256, v255, 0);
        v251->p = v256;
        v246 = p_pm2;
      }
      v257 = v248 - 3;
      ++v248;
    }
    while (v257 < v246->FrameCount);
  }
  v259 = evtAddObject(14, pInfo);
  v260 = p_pm2;
  if (p_pm2->FrameCount >= 1)
  {
    v261 = v259;
    for (n = 0; n < p_pm2->FrameCount; ++n)
    {
      v265 = v260->FrameTable[n];
      if (v265->ObjectType == 14)
      {
        v267 = v265->Frame;
        v268 = evtAddFrameInfo(v261, v267, pInfo);
        v269 = v268->data[0]->s;
        v270 = get_Item(p_pm2->FrameTable[n]->Data[0]->s, 0, 0);
        set_Item(v269, 0, v270, 0);
        MBlurTable = p_pm2->MBlurTable;
        v272 = MBlurTable[get_Item(p_pm2->FrameTable[n]->Data[0]->s, 1, 0)];
        v273 = Allocate(pmdMultBlurTable_t);
        _ctor_27153344(v273, v272, 0);
        v268->p = v273;
        v274 = v268->data[2]->s;
        v275 = get_Item(p_pm2->FrameTable[n]->Data[2]->s, 0, 0);
        set_Item(v274, 0, v275, 0);
        if (get_Item(p_pm2->FrameTable[n]->Data[2]->s, 0, 0))
        {
          if (get_Item(p_pm2->FrameTable[n]->Data[2]->s, 0, 0) != 1)
          {
            v276 = get_Item(p_pm2->FrameTable[n]->Data[2]->s, 0, 0);
            v277 = pInfo->firstobjinfo;
            if (!v277)
              goto LABEL_313;
            v278 = v276 - 2;
            while (1)
            {
              v279 = (u32)v277->nameindex;
              if ((v279 & 0x80000000) == 0 && Equals_54828784(pInfo->nametable[v279]->Name, p_pm2->NameTable2[v278]->Name, 0))
              {
                break;
              }
              v277 = v277->next;
              if (!v277)
                goto LABEL_313;
            }
            v280 = v277->nameindex;
            if (v280 == -1)
            {
LABEL_313:
              v263 = 0;
              v264 = v268->data[2]->s;
            }
            else
            {
              v263 = v280 + 2;
              v264 = v268->data[2]->s;
            }
            set_Item(v264, 0, v263, 0);
          }
        }
        goto LABEL_315;
      }
LABEL_315:
      v260 = p_pm2;
    }
  }
  v281 = evtAddObject(15, pInfo);
  v282 = p_pm2;
  if (p_pm2->FrameCount >= 1)
  {
    v283 = v281;
    for (ii = 0; ii < p_pm2->FrameCount; ++ii)
    {
      v287 = v282->FrameTable[ii];
      if (v287->ObjectType == 15)
      {
        v289 = v287->Frame;
        v290 = evtAddFrameInfo(v283, v289, pInfo);
        v291 = v290->data[0]->s;
        v292 = get_Item(p_pm2->FrameTable[ii]->Data[0]->s, 0, 0);
        set_Item(v291, 0, v292, 0);
        DBlurTable = p_pm2->DBlurTable;
        v294 = DBlurTable[get_Item(p_pm2->FrameTable[ii]->Data[0]->s, 1, 0)];
        v295 = Allocate(pmdDistBlurTable_t);
        _ctor_27153408(v295, v294, 0);
        v290->p = v295;
        v296 = v290->data[2]->s;
        v297 = get_Item(p_pm2->FrameTable[ii]->Data[2]->s, 0, 0);
        set_Item(v296, 0, v297, 0);
        if (get_Item(p_pm2->FrameTable[ii]->Data[2]->s, 0, 0))
        {
          if (get_Item(p_pm2->FrameTable[ii]->Data[2]->s, 0, 0) != 1)
          {
            v298 = get_Item(p_pm2->FrameTable[ii]->Data[2]->s, 0, 0);
            v299 = pInfo->firstobjinfo;
            if (!v299)
              goto LABEL_341;
            v300 = v298 - 2;
            while (1)
            {
              v301 = (u32)v299->nameindex;
              if ((v301 & 0x80000000) == 0 && Equals_54828784(pInfo->nametable[v301]->Name, p_pm2->NameTable2[v300]->Name, 0))
              {
                break;
              }
              v299 = v299->next;
              if (!v299)
                goto LABEL_341;
            }
            v302 = v299->nameindex;
            if (v302 == -1)
            {
LABEL_341:
              v285 = 0;
              v286 = v290->data[2]->s;
            }
            else
            {
              v285 = v302 + 2;
              v286 = v290->data[2]->s;
            }
            set_Item(v286, 0, v285, 0);
          }
        }
        goto LABEL_343;
      }
LABEL_343:
      v282 = p_pm2;
    }
  }
  v303 = evtAddObject(23, pInfo);
  v304 = p_pm2;
  if (p_pm2->FrameCount >= 1)
  {
    v305 = v303;
    for (jj = 0; jj < p_pm2->FrameCount; ++jj)
    {
      v309 = v304->FrameTable[jj];
      if (v309->ObjectType == 23)
      {
        v311 = v309->Frame;
        v312 = evtAddFrameInfo(v305, v311, pInfo);
        v313 = v312->data[0]->s;
        v314 = get_Item(p_pm2->FrameTable[jj]->Data[0]->s, 0, 0);
        set_Item(v313, 0, v314, 0);
        RBlurTable = p_pm2->RBlurTable;
        v316 = RBlurTable[get_Item(p_pm2->FrameTable[jj]->Data[0]->s, 1, 0)];
        v317 = Allocate(pmdRipBlurTable_t);
        _ctor_27153472(v317, v316, 0);
        v312->p = v317;
        v318 = v312->data[2]->s;
        v319 = get_Item(p_pm2->FrameTable[jj]->Data[2]->s, 0, 0);
        set_Item(v318, 0, v319, 0);
        if (get_Item(p_pm2->FrameTable[jj]->Data[2]->s, 0, 0))
        {
          if (get_Item(p_pm2->FrameTable[jj]->Data[2]->s, 0, 0) != 1)
          {
            v320 = get_Item(p_pm2->FrameTable[jj]->Data[2]->s, 0, 0);
            v321 = pInfo->firstobjinfo;
            if (!v321)
              goto LABEL_369;
            v322 = v320 - 2;
            while (1)
            {
              v323 = (u32)v321->nameindex;
              if ((v323 & 0x80000000) == 0 && Equals_54828784(pInfo->nametable[v323]->Name, p_pm2->NameTable2[v322]->Name, 0))
              {
                break;
              }
              v321 = v321->next;
              if (!v321)
                goto LABEL_369;
            }
            v324 = v321->nameindex;
            if (v324 == -1)
            {
LABEL_369:
              v307 = 0;
              v308 = v312->data[2]->s;
            }
            else
            {
              v307 = v324 + 2;
              v308 = v312->data[2]->s;
            }
            set_Item(v308, 0, v307, 0);
          }
        }
        goto LABEL_371;
      }
LABEL_371:
      v304 = p_pm2;
    }
  }
  v325 = evtAddObject(27, pInfo);
  v326 = p_pm2;
  if (p_pm2->FrameCount >= 1)
  {
    v327 = v325;
    v328 = 4;
    do
    {
      v338 = *((u64 *)&v326->FrameTable->obj.klass + v328);
      if (*(u32 *)(v338 + 16) == 27)
      {
        v330 = *(u16 *)(v338 + 20);
        v331 = evtAddFrameInfo(v327, v330, pInfo);
        v332 = v331->data[0]->s;
        v333 = get_Item(*(DataS *)(*(u64 *)(*(u64 *)(*((u64 *)&p_pm2->FrameTable->obj.klass + v328) + 32) + 32) + 40), 0, 0);
        set_Item(v332, 0, v333, 0);
        HBlurTable = p_pm2->HBlurTable;
        v335 = HBlurTable[get_Item(*(DataS *)(*(u64 *)(*(u64 *)(*((u64 *)&p_pm2->FrameTable->obj.klass + v328) + 32) + 32) + 40), 1, 0)];
        v336 = Allocate(pmdHeikouBlurTable_t);
        _ctor_27153536(v336, v335, 0);
        v331->p = v336;
        v326 = p_pm2;
      }
      v337 = v328 - 3;
      ++v328;
    }
    while (v337 < v326->FrameCount);
  }
  v339 = evtAddObject(16, pInfo);
  v340 = p_pm2;
  if (p_pm2->FrameCount >= 1)
  {
    v341 = v339;
    v342 = 4;
    do
    {
      v354 = *((u64 *)&v340->FrameTable->obj.klass + v342);
      if (*(u32 *)(v354 + 16) == 16)
      {
        v344 = *(u16 *)(v354 + 20);
        v345 = evtAddFrameInfo(v341, v344, pInfo);
        v346 = v345->data[0]->s;
        v347 = get_Item(*(DataS *)(*(u64 *)(*(u64 *)(*((u64 *)&p_pm2->FrameTable->obj.klass + v342) + 32) + 32) + 40), 0, 0);
        set_Item(v346, 0, v347, 0);
        FilterTable = p_pm2->FilterTable;
        v349 = FilterTable[get_Item(*(DataS *)(*(u64 *)(*(u64 *)(*((u64 *)&p_pm2->FrameTable->obj.klass + v342) + 32) + 32) + 40), 1, 0)];
        v350 = Allocate(pmdFilterTable_t);
        _ctor_27153600(v350, v349, 0);
        v345->p = v350;
        v351 = v345->data[3]->s;
        v352 = get_Item(*(DataS *)(*(u64 *)(*(u64 *)(*((u64 *)&p_pm2->FrameTable->obj.klass + v342) + 32) + 56) + 40), 0, 0);
        set_Item(v351, 0, v352, 0);
        v340 = p_pm2;
      }
      v353 = v342 - 3;
      ++v342;
    }
    while (v353 < v340->FrameCount);
  }
  v355 = evtAddObject(17, pInfo);
  v356 = p_pm2;
  if (p_pm2->FrameCount >= 1)
  {
    v357 = v355;
    for (kk = 0; kk < v356->FrameCount; ++kk)
    {
      v363 = v356->FrameTable[kk];
      if (v363->ObjectType == 17)
      {
        v365 = v363->Frame;
        v366 = evtAddFrameInfo(v357, v365, pInfo);
        v367 = v366->data[0]->s;
        v368 = get_Item(p_pm2->FrameTable[kk]->Data[0]->s, 0, 0);
        set_Item(v367, 0, v368, 0);
        MFilterTable = p_pm2->MFilterTable;
        v370 = MFilterTable[get_Item(p_pm2->FrameTable[kk]->Data[0]->s, 1, 0)];
        v371 = Allocate(pmdMultFilterTable_t);
        _ctor_27153664(v371, v370, 0);
        v366->p = v371;
        v372 = v366->data[2]->s;
        v373 = get_Item(p_pm2->FrameTable[kk]->Data[2]->s, 0, 0);
        set_Item(v372, 0, v373, 0);
        if (get_Item(p_pm2->FrameTable[kk]->Data[2]->s, 0, 0))
        {
          if (get_Item(p_pm2->FrameTable[kk]->Data[2]->s, 0, 0) != 1)
          {
            v374 = get_Item(p_pm2->FrameTable[kk]->Data[2]->s, 0, 0);
            v375 = pInfo->firstobjinfo;
            if (!v375)
              goto LABEL_425;
            v376 = v374 - 2;
            while (1)
            {
              v377 = (u32)v375->nameindex;
              if ((v377 & 0x80000000) == 0 && Equals_54828784(pInfo->nametable[v377]->Name, p_pm2->NameTable2[v376]->Name, 0))
              {
                break;
              }
              v375 = v375->next;
              if (!v375)
                goto LABEL_425;
            }
            v378 = v375->nameindex;
            if (v378 == -1)
            {
LABEL_425:
              v359 = 0;
              v360 = v366->data[2]->s;
            }
            else
            {
              v359 = v378 + 2;
              v360 = v366->data[2]->s;
            }
            set_Item(v360, 0, v359, 0);
          }
        }
        v361 = v366->data[3]->s;
        v362 = get_Item(p_pm2->FrameTable[kk]->Data[3]->s, 0, 0);
        set_Item(v361, 0, v362, 0);
        v356 = p_pm2;
      }
    }
  }
  MesHandle = v807->MesHandle;
  if (MesHandle != -1)
  {
    if (itfGetMessageNo(MesHandle) >= 1)
    {
      v380 = evtAddObject(4, pInfo);
      v381 = p_pm2;
      if (p_pm2->FrameCount >= 1)
      {
        v382 = v380;
        v383 = 4;
        do
        {
          v401 = *((u64 *)&v381->FrameTable->obj.klass + v383);
          if (*(u32 *)(v401 + 16) == 4)
          {
            v385 = *(u16 *)(v401 + 20);
            v386 = evtAddFrameInfo(v382, v385, pInfo);
            v387 = *((u64 *)&p_pm2->FrameTable->obj.klass + v383);
            v388 = *(u16 *)(v387 + 22);
            v389 = *(u64 *)(v387 + 32);
            v386->length = v388;
            v390 = v386->data[0]->s;
            v391 = get_Item(*(DataS *)(*(u64 *)(v389 + 32) + 40), 0, 0);
            set_Item(v390, 0, v391, 0);
            v392 = v386->data[0]->s;
            v393 = get_Item(*(DataS *)(*(u64 *)(*(u64 *)(*((u64 *)&p_pm2->FrameTable->obj.klass + v383) + 32) + 32) + 40), 1, 0);
            set_Item(v392, 1, v393, 0);
            v394 = v386->data[1]->c;
            v395 = get_Item(*(DataC *)(*(u64 *)(*(u64 *)(*((u64 *)&p_pm2->FrameTable->obj.klass + v383) + 32) + 40) + 32), 0, 0);
            set_Item(v394, 0, v395, 0);
            v396 = v386->data[2]->c;
            v397 = get_Item(*(DataC *)(*(u64 *)(*(u64 *)(*((u64 *)&p_pm2->FrameTable->obj.klass + v383) + 32) + 48) + 32), 0, 0);
            set_Item(v396, 0, v397, 0);
            v398 = v386->data[2]->c;
            v399 = get_Item(*(DataC *)(*(u64 *)(*(u64 *)(*((u64 *)&p_pm2->FrameTable->obj.klass + v383) + 32) + 48) + 32), 1, 0);
            set_Item(v398, 1, v399, 0);
            v381 = p_pm2;
          }
          v400 = v383 - 3;
          ++v383;
        }
        while (v400 < v381->FrameCount);
      }
    }
  }
  v402 = evtAddObject(5, pInfo);
  if (p_pm2->Header2->Version <= 5)
  {
    SoundFrameCount = (u32)(p_pm2)->FrameCount;
    if ((s32)SoundFrameCount < 1)
      goto LABEL_474;
    goto LABEL_481;
  }
  SoundFrameCount = (u32)v807->pm3->SoundFrameCount;
  if ((s32)SoundFrameCount >= 1)
  {
LABEL_481:
    v407 = 0;
    v404 = 0;
    v408 = 8 * SoundFrameCount;
    while (1)
    {
      if (p_pm2->Header2->Version > 5)
      {
        v416 = v807->pm3->SoundFrameTable[v407 / 8];
        if (v416->ObjectType == 5)
        {
          v417 = v416->Frame;
          v409 = evtAddFrameInfo(v402, v417, pInfo);
          v410 = v409->data[0]->s;
          v411 = get_Item(v807->pm3->SoundFrameTable[v407 / 8]->Data[0]->s, 0, 0);
          set_Item(v410, 0, v411, 0);
          v412 = v409->data[0]->s;
          v413 = get_Item(v807->pm3->SoundFrameTable[v407 / 8]->Data[0]->s, 1, 0);
          set_Item(v412, 1, v413, 0);
          v414 = v409->data[1]->c;
          v415 = get_Item(v807->pm3->SoundFrameTable[v407 / 8]->Data[1]->c, 0, 0);
          set_Item(v414, 0, v415, 0);
          v404 |= get_Item(v409->data[1]->c, 0, 0) == 0;
        }
        goto LABEL_483;
      }
      v418 = p_pm2->FrameTable[v407 / 8];
      if (v418->ObjectType == 5)
      {
        v420 = v418->Frame;
        v421 = evtAddFrameInfo(v402, v420, pInfo);
        v422 = v421->data[0]->s;
        v423 = get_Item(p_pm2->FrameTable[v407 / 8]->Data[0]->s, 0, 0);
        set_Item(v422, 0, v423, 0);
        v404 = 1;
        v424 = v421->data[0]->s;
        v425 = get_Item(p_pm2->FrameTable[v407 / 8]->Data[0]->s, 1, 0);
        set_Item(v424, 1, v425, 0);
        goto LABEL_483;
      }
LABEL_483:
      v407 += 8;
      if (v408 == v407)
        goto LABEL_475;
    }
  }
LABEL_474:
  v404 = 0;
LABEL_475:
  v405 = evtAddObject(19, pInfo);
  if (p_pm2->Header2->Version > 5)
  {
    v406 = (u32)v807->pm3->SoundFrameCount;
    if ((s32)v406 < 1)
      goto LABEL_514;
    goto LABEL_498;
  }
  v406 = (u32)(p_pm2)->FrameCount;
  if ((s32)v406 >= 1)
  {
LABEL_498:
    v426 = 0;
    v427 = 8 * v406;
    do
    {
      if (p_pm2->Header2->Version > 5)
      {
        v441 = v807->pm3->SoundFrameTable[v426 / 8];
        if (v441->ObjectType == 19)
        {
          v442 = v441->Frame;
          v428 = evtAddFrameInfo(v405, v442, pInfo);
          v429 = v428->data[0]->s;
          v430 = get_Item(v807->pm3->SoundFrameTable[v426 / 8]->Data[0]->s, 0, 0);
          set_Item(v429, 0, v430, 0);
          v431 = v428->data[0]->s;
          v432 = get_Item(v807->pm3->SoundFrameTable[v426 / 8]->Data[0]->s, 1, 0);
          set_Item(v431, 1, v432, 0);
          v433 = v428->data[1]->s;
          v434 = get_Item(v807->pm3->SoundFrameTable[v426 / 8]->Data[1]->s, 0, 0);
          set_Item(v433, 0, v434, 0);
          v435 = v428->data[1]->c;
          v436 = get_Item(v807->pm3->SoundFrameTable[v426 / 8]->Data[1]->c, 2, 0);
          set_Item(v435, 2, v436, 0);
          v437 = v428->data[2]->c;
          v438 = get_Item(v807->pm3->SoundFrameTable[v426 / 8]->Data[2]->c, 0, 0);
          set_Item(v437, 0, v438, 0);
          v439 = v428->data[2]->c;
          v440 = get_Item(v807->pm3->SoundFrameTable[v426 / 8]->Data[2]->c, 1, 0);
          set_Item(v439, 1, v440, 0);
          v404 |= get_Item(v428->data[1]->c, 2, 0) == 0;
        }
        goto LABEL_500;
      }
      v443 = p_pm2->FrameTable[v426 / 8];
      if (v443->ObjectType == 19)
      {
        v445 = v443->Frame;
        v446 = evtAddFrameInfo(v405, v445, pInfo);
        v447 = v446->data[0]->s;
        v448 = get_Item(p_pm2->FrameTable[v426 / 8]->Data[0]->s, 0, 0);
        set_Item(v447, 0, v448, 0);
        v404 = 1;
        v449 = v446->data[0]->s;
        v450 = get_Item(p_pm2->FrameTable[v426 / 8]->Data[0]->s, 1, 0);
        set_Item(v449, 1, v450, 0);
        v451 = v446->data[1]->s;
        v452 = get_Item(p_pm2->FrameTable[v426 / 8]->Data[1]->s, 0, 0);
        set_Item(v451, 0, v452, 0);
        goto LABEL_500;
      }
LABEL_500:
      v426 += 8;
    }
    while (v427 != v426);
  }
LABEL_514:
  v453 = evtAddObject(6, pInfo);
  v454 = p_pm2;
  if (p_pm2->FrameCount >= 1)
  {
    v455 = v453;
    v456 = 4;
    do
    {
      v474 = *((u64 *)&v454->FrameTable->obj.klass + v456);
      if (*(u32 *)(v474 + 16) == 6)
      {
        v458 = *(u16 *)(v474 + 20);
        v459 = evtAddFrameInfo(v455, v458, pInfo);
        v460 = *((u64 *)&p_pm2->FrameTable->obj.klass + v456);
        v461 = *(u16 *)(v460 + 22);
        v462 = *(u64 *)(v460 + 32);
        v459->length = v461;
        v463 = v459->data[0]->s;
        v464 = get_Item(*(DataS *)(*(u64 *)(v462 + 32) + 40), 0, 0);
        set_Item(v463, 0, v464, 0);
        v465 = v459->data[1]->c;
        v466 = get_Item(*(DataC *)(*(u64 *)(*(u64 *)(*((u64 *)&p_pm2->FrameTable->obj.klass + v456) + 32) + 40) + 32), 0, 0);
        set_Item(v465, 0, v466, 0);
        v467 = v459->data[1]->c;
        v468 = get_Item(*(DataC *)(*(u64 *)(*(u64 *)(*((u64 *)&p_pm2->FrameTable->obj.klass + v456) + 32) + 40) + 32), 1, 0);
        set_Item(v467, 1, v468, 0);
        v469 = v459->data[1]->c;
        v470 = get_Item(*(DataC *)(*(u64 *)(*(u64 *)(*((u64 *)&p_pm2->FrameTable->obj.klass + v456) + 32) + 40) + 32), 2, 0);
        set_Item(v469, 2, v470, 0);
        v471 = v459->data[1]->c;
        v472 = get_Item(*(DataC *)(*(u64 *)(*(u64 *)(*((u64 *)&p_pm2->FrameTable->obj.klass + v456) + 32) + 40) + 32), 3, 0);
        set_Item(v471, 3, v472, 0);
        v454 = p_pm2;
      }
      v473 = v456 - 3;
      ++v456;
    }
    while (v473 < v454->FrameCount);
  }
  v475 = evtAddObject(7, pInfo);
  v476 = p_pm2;
  if (p_pm2->FrameCount >= 1)
  {
    v477 = v475;
    v478 = 4;
    do
    {
      v488 = *((u64 *)&v476->FrameTable->obj.klass + v478);
      if (*(u32 *)(v488 + 16) == 7)
      {
        v480 = *(u16 *)(v488 + 20);
        v481 = evtAddFrameInfo(v477, v480, pInfo);
        v482 = *((u64 *)&p_pm2->FrameTable->obj.klass + v478);
        v483 = *(u16 *)(v482 + 22);
        v484 = *(u64 *)(v482 + 32);
        v481->length = v483;
        v485 = v481->data[0]->s;
        v486 = get_Item(*(DataS *)(*(u64 *)(v484 + 32) + 40), 0, 0);
        set_Item(v485, 0, v486, 0);
        v476 = p_pm2;
      }
      v487 = v478 - 3;
      ++v478;
    }
    while (v487 < v476->FrameCount);
  }
  v489 = evtAddObject(8, pInfo);
  v490 = p_pm2;
  if (p_pm2->FrameCount < 1)
    goto LABEL_576;
  v491 = v489;
  v492 = 4;
  do
  {
    v504 = *((u64 *)&v490->FrameTable->obj.klass + v492);
    if (*(u32 *)(v504 + 16) == 8)
    {
      v494 = *(u16 *)(v504 + 20);
      v495 = evtAddFrameInfo(v491, v494, pInfo);
      v496 = v495->data[0]->s;
      v497 = get_Item(*(DataS *)(*(u64 *)(*(u64 *)(*((u64 *)&p_pm2->FrameTable->obj.klass + v492) + 32) + 32) + 40), 0, 0);
      set_Item(v496, 0, v497, 0);
      v498 = v495->data[0]->s;
      v499 = get_Item(*(DataS *)(*(u64 *)(*(u64 *)(*((u64 *)&p_pm2->FrameTable->obj.klass + v492) + 32) + 32) + 40), 1, 0);
      set_Item(v498, 1, v499, 0);
      v500 = v495->data[1]->s;
      v501 = get_Item(*(DataS *)(*(u64 *)(*(u64 *)(*((u64 *)&p_pm2->FrameTable->obj.klass + v492) + 32) + 40) + 40), 0, 0);
      set_Item(v500, 0, v501, 0);
      v490 = p_pm2;
    }
    v502 = v490->FrameCount;
    v503 = v492 - 3;
    ++v492;
  }
  while (v503 < v502);
  if ((s32)v502 >= 1)
  {
    for (mm = 0; mm < v490->FrameCount; ++mm)
    {
      if (v490->FrameTable[mm]->ObjectType == 24)
        goto LABEL_564;
      goto LABEL_9010;
      if (p_pm2->FrameTable[mm]->ObjectType == 24)
      {
LABEL_564:
        v506 = pInfo->firstobjinfo;
        if (v506)
        {
          do
          {
            v530 = (u32)v506->nameindex;
            if ((v530 & 0x80000000) == 0)
            {
              v531 = pInfo->nametable[v530]->Name;
              v532 = p_pm2;
              v533 = p_pm2->NameTable2;
              v532 = p_pm2;
              if (Equals_54828784(v531, v533[v532->FrameTable[mm]->NameIndex]->Name, 0))
              {
                v534 = p_pm2->FrameTable[mm]->Frame;
                v507 = evtAddFrameInfo(v506, v534, pInfo);
                v508 = v507->data[0]->c;
                v509 = get_Item(p_pm2->FrameTable[mm]->Data[0]->c, 0, 0);
                set_Item(v508, 0, v509, 0);
                v510 = v507->data[0]->c;
                v511 = get_Item(p_pm2->FrameTable[mm]->Data[0]->c, 1, 0);
                set_Item(v510, 1, v511, 0);
                v512 = v507->data[1]->s;
                v513 = get_Item(p_pm2->FrameTable[mm]->Data[1]->s, 0, 0);
                set_Item(v512, 0, v513, 0);
                v514 = v507->data[1]->s;
                v515 = get_Item(p_pm2->FrameTable[mm]->Data[1]->s, 1, 0);
                set_Item(v514, 1, v515, 0);
                uc = v507->data[2]->uc;
                v517 = get_Item(p_pm2->FrameTable[mm]->Data[2]->uc, 0, 0);
                set_Item(uc, 0, v517, 0);
                v518 = v507->data[2]->uc;
                v519 = get_Item(p_pm2->FrameTable[mm]->Data[2]->uc, 1, 0);
                set_Item(v518, 1, v519, 0);
                v520 = v507->data[2]->uc;
                v521 = get_Item(p_pm2->FrameTable[mm]->Data[2]->uc, 2, 0);
                set_Item(v520, 2, v521, 0);
                v522 = v507->data[2]->uc;
                v523 = get_Item(p_pm2->FrameTable[mm]->Data[2]->uc, 3, 0);
                set_Item(v522, 3, v523, 0);
                v524 = v507->data[3];
                v525 = get_f(p_pm2->FrameTable[mm]->Data[3], 0);
                set_f(v524, v525, 0);
                v526 = v507->data[4];
                v527 = get_f(p_pm2->FrameTable[mm]->Data[4], 0);
                set_f(v526, v527, 0);
                v528 = v507->data[5]->c;
                v529 = get_Item(p_pm2->FrameTable[mm]->Data[5]->c, 0, 0);
                set_Item(v528, 0, v529, 0);
              }
            }
            v506 = v506->next;
          }
          while (v506);
          v490 = p_pm2;
        }
      }
LABEL_9010:
    }
  }
LABEL_576:
  v535 = evtAddObject(28, pInfo);
  v536 = p_pm2;
  if (p_pm2->FrameCount >= 1)
  {
    v537 = v535;
    v538 = 4;
    do
    {
      v550 = *((u64 *)&v536->FrameTable->obj.klass + v538);
      if (*(u32 *)(v550 + 16) == 28)
      {
        v540 = *(u16 *)(v550 + 20);
        v541 = evtAddFrameInfo(v537, v540, pInfo);
        v542 = *((u64 *)&p_pm2->FrameTable->obj.klass + v538);
        v543 = *(u16 *)(v542 + 22);
        v544 = *(u64 *)(v542 + 32);
        v541->length = v543;
        v545 = v541->data[0]->s;
        v546 = get_Item(*(DataS *)(*(u64 *)(v544 + 32) + 40), 0, 0);
        set_Item(v545, 0, v546, 0);
        v547 = v541->data[0]->s;
        v548 = get_Item(*(DataS *)(*(u64 *)(*(u64 *)(*((u64 *)&p_pm2->FrameTable->obj.klass + v538) + 32) + 32) + 40), 1, 0);
        set_Item(v547, 1, v548, 0);
        v536 = p_pm2;
      }
      v549 = v538 - 3;
      ++v538;
    }
    while (v549 < v536->FrameCount);
  }
  v551 = evtAddObject(29, pInfo);
  v552 = p_pm2;
  if (p_pm2->FrameCount >= 1)
  {
    v553 = v551;
    v554 = 4;
    do
    {
      v568 = *((u64 *)&v552->FrameTable->obj.klass + v554);
      if (*(u32 *)(v568 + 16) == 29)
      {
        v556 = *(u16 *)(v568 + 20);
        v557 = evtAddFrameInfo(v553, v556, pInfo);
        v558 = *((u64 *)&p_pm2->FrameTable->obj.klass + v554);
        v559 = *(u16 *)(v558 + 22);
        v560 = *(u64 *)(v558 + 32);
        v557->length = v559;
        v561 = v557->data[0]->s;
        v562 = get_Item(*(DataS *)(*(u64 *)(v560 + 32) + 40), 0, 0);
        set_Item(v561, 0, v562, 0);
        v563 = v557->data[1]->c;
        v564 = get_Item(*(DataC *)(*(u64 *)(*(u64 *)(*((u64 *)&p_pm2->FrameTable->obj.klass + v554) + 32) + 40) + 32), 0, 0);
        set_Item(v563, 0, v564, 0);
        v565 = v557->data[1]->c;
        v566 = get_Item(*(DataC *)(*(u64 *)(*(u64 *)(*((u64 *)&p_pm2->FrameTable->obj.klass + v554) + 32) + 40) + 32), 1, 0);
        set_Item(v565, 1, v566, 0);
        v552 = p_pm2;
      }
      v567 = v554 - 3;
      ++v554;
    }
    while (v567 < v552->FrameCount);
  }
  v569 = evtAddObject(32, pInfo);
  v570 = p_pm2;
  if (p_pm2->FrameCount >= 1)
  {
    v571 = v569;
    v572 = 4;
    do
    {
      v582 = *((u64 *)&v570->FrameTable->obj.klass + v572);
      if (*(u32 *)(v582 + 16) == 32)
      {
        v574 = *(u16 *)(v582 + 20);
        v575 = evtAddFrameInfo(v571, v574, pInfo);
        v576 = *((u64 *)&p_pm2->FrameTable->obj.klass + v572);
        v577 = *(u16 *)(v576 + 22);
        v578 = *(u64 *)(v576 + 32);
        v575->length = v577;
        v579 = v575->data[0]->s;
        v580 = get_Item(*(DataS *)(*(u64 *)(v578 + 32) + 40), 0, 0);
        set_Item(v579, 0, v580, 0);
        v570 = p_pm2;
      }
      v581 = v572 - 3;
      ++v572;
    }
    while (v581 < v570->FrameCount);
  }
  v583 = evtAddObject(33, pInfo);
  v584 = p_pm2;
  if (p_pm2->FrameCount >= 1)
  {
    v585 = v583;
    for (nn = 0; nn < v584->FrameCount; ++nn)
    {
      v602 = v584->FrameTable[nn];
      if (v602->ObjectType != 33)
        continue;
      v588 = v602->Frame;
      v589 = evtAddFrameInfo(v585, v588, pInfo);
      v590 = v589->data[0]->s;
      v591 = get_Item(p_pm2->FrameTable[nn]->Data[0]->s, 0, 0);
      set_Item(v590, 0, v591, 0);
      v592 = v589->data[0]->s;
      v593 = get_Item(p_pm2->FrameTable[nn]->Data[0]->s, 1, 0);
      set_Item(v592, 1, v593, 0);
      v594 = v589->data[1]->s;
      v595 = get_Item(p_pm2->FrameTable[nn]->Data[1]->s, 0, 0);
      set_Item(v594, 0, v595, 0);
      v596 = v589->data[1]->s;
      v597 = get_Item(p_pm2->FrameTable[nn]->Data[1]->s, 1, 0);
      set_Item(v596, 1, v597, 0);
      v598 = v589->data[2]->c;
      v599 = get_Item(p_pm2->FrameTable[nn]->Data[2]->c, 0, 0);
      set_Item(v598, 0, v599, 0);
      v600 = v589->data[2]->c;
      v601 = get_Item(p_pm2->FrameTable[nn]->Data[2]->c, 1, 0);
      set_Item(v600, 1, v601, 0);
      v584 = p_pm2;
    }
  }
  v603 = evtAddObject(34, pInfo);
  v604 = p_pm2;
  if (p_pm2->FrameCount >= 1)
  {
    v605 = v603;
    v606 = 4;
    do
    {
      v612 = *((u64 *)&v604->FrameTable->obj.klass + v606);
      if (*(u32 *)(v612 + 16) == 34)
      {
        v608 = *(u16 *)(v612 + 20);
        v609 = evtAddFrameInfo(v605, v608, pInfo)->data[0]->c;
        v610 = get_Item(*(DataC *)(*(u64 *)(*(u64 *)(*((u64 *)&p_pm2->FrameTable->obj.klass + v606) + 32) + 32) + 32), 0, 0);
        set_Item(v609, 0, v610, 0);
        v604 = p_pm2;
      }
      v611 = v606 - 3;
      ++v606;
    }
    while (v611 < v604->FrameCount);
  }
  v613 = evtAddObject(35, pInfo);
  v614 = p_pm2;
  if (p_pm2->FrameCount >= 1)
  {
    v615 = v613;
    v616 = 4;
    do
    {
      v621 = *((u64 *)&v614->FrameTable->obj.klass + v616);
      if (*(u32 *)(v621 + 16) == 35)
      {
        v618 = *(u16 *)(v621 + 20);
        v619 = evtAddFrameInfo(v615, v618, pInfo);
        v614 = p_pm2;
        v619->length = *(u16 *)(*((u64 *)&p_pm2->FrameTable->obj.klass + v616) + 22);
      }
      v620 = v616 - 3;
      ++v616;
    }
    while (v620 < v614->FrameCount);
  }
  v622 = evtAddObject(36, pInfo);
  v623 = p_pm2;
  if (p_pm2->FrameCount >= 1)
  {
    v624 = v622;
    for (i1 = 0; i1 < v623->FrameCount; ++i1)
    {
      v653 = v623->FrameTable[i1];
      if (v653->ObjectType != 36)
        continue;
      v627 = v653->Frame;
      v628 = evtAddFrameInfo(v624, v627, pInfo);
      v629 = v628->data[0]->c;
      v630 = get_Item(p_pm2->FrameTable[i1]->Data[0]->c, 0, 0);
      set_Item(v629, 0, v630, 0);
      v631 = v628->data[0]->c;
      v632 = get_Item(p_pm2->FrameTable[i1]->Data[0]->c, 1, 0);
      set_Item(v631, 1, v632, 0);
      v633 = v628->data[0]->s;
      v634 = get_Item(p_pm2->FrameTable[i1]->Data[0]->s, 1, 0);
      set_Item(v633, 1, v634, 0);
      v635 = v628->data[1]->s;
      v636 = get_Item(p_pm2->FrameTable[i1]->Data[1]->s, 0, 0);
      set_Item(v635, 0, v636, 0);
      v637 = v628->data[1]->s;
      v638 = get_Item(p_pm2->FrameTable[i1]->Data[1]->s, 1, 0);
      set_Item(v637, 1, v638, 0);
      v639 = v628->data[2]->uc;
      v640 = get_Item(p_pm2->FrameTable[i1]->Data[2]->uc, 0, 0);
      set_Item(v639, 0, v640, 0);
      v641 = v628->data[2]->uc;
      v642 = get_Item(p_pm2->FrameTable[i1]->Data[2]->uc, 1, 0);
      set_Item(v641, 1, v642, 0);
      v643 = v628->data[2]->uc;
      v644 = get_Item(p_pm2->FrameTable[i1]->Data[2]->uc, 2, 0);
      set_Item(v643, 2, v644, 0);
      v645 = v628->data[2]->uc;
      v646 = get_Item(p_pm2->FrameTable[i1]->Data[2]->uc, 3, 0);
      set_Item(v645, 3, v646, 0);
      v647 = v628->data[3];
      v648 = get_f(p_pm2->FrameTable[i1]->Data[3], 0);
      set_f(v647, v648, 0);
      v649 = v628->data[4];
      v650 = get_f(p_pm2->FrameTable[i1]->Data[4], 0);
      set_f(v649, v650, 0);
      v651 = v628->data[5]->c;
      v652 = get_Item(p_pm2->FrameTable[i1]->Data[5]->c, 0, 0);
      set_Item(v651, 0, v652, 0);
      v623 = p_pm2;
    }
  }
  v654 = evtAddObject(37, pInfo);
  v655 = p_pm2;
  if (p_pm2->FrameCount >= 1)
  {
    v656 = v654;
    for (i2 = 0; i2 < v655->FrameCount; ++i2)
    {
      v659 = v655->FrameTable[i2];
      if (v659->ObjectType == 37)
      {
        v661 = v659->Frame;
        v662 = evtAddFrameInfo(v656, v661, pInfo);
        v663 = v662->data[0];
        v664 = p_pm2->FrameTable[i2];
        v662->length = v664->Length;
        v664 = p_pm2->FrameTable[i2];
        v665 = get_i(v664->Data[0], 0);
        set_i(v663, v665, 0);
        v666 = v662->data[1];
        v667 = get_i(p_pm2->FrameTable[i2]->Data[1], 0);
        set_i(v666, v667, 0);
        v668 = v662->data[2];
        v669 = get_i(p_pm2->FrameTable[i2]->Data[2], 0);
        set_i(v668, v669, 0);
        v670 = v662->data[3];
        v671 = get_i(p_pm2->FrameTable[i2]->Data[3], 0);
        set_i(v670, v671, 0);
        v672 = v662->data[4];
        v673 = get_i(p_pm2->FrameTable[i2]->Data[4], 0);
        set_i(v672, v673, 0);
        v674 = v662->data[5];
        v675 = get_i(p_pm2->FrameTable[i2]->Data[5], 0);
        set_i(v674, v675, 0);
        v676 = v662->data[6];
        v677 = get_i(p_pm2->FrameTable[i2]->Data[6], 0);
        set_i(v676, v677, 0);
        v678 = v662->data[7]->c;
        v658 = get_Item(p_pm2->FrameTable[i2]->Data[7]->c, 0, 0);
        set_Item(v678, 0, v658, 0);
        v655 = p_pm2;
        continue;
      }
    }
  }
  v679 = evtAddObject(38, pInfo);
  v680 = p_pm2;
  if (p_pm2->FrameCount >= 1)
  {
    v681 = v679;
    v682 = 4;
    do
    {
      v688 = *((u64 *)&v680->FrameTable->obj.klass + v682);
      if (*(u32 *)(v688 + 16) == 38)
      {
        v684 = *(u16 *)(v688 + 20);
        v685 = evtAddFrameInfo(v681, v684, pInfo)->data[0];
        v686 = get_i(*(pmdDataInfo_t *)(*(u64 *)(*((u64 *)&p_pm2->FrameTable->obj.klass + v682) + 32) + 32), 0);
        set_i(v685, v686, 0);
        v680 = p_pm2;
      }
      v687 = v682 - 3;
      ++v682;
    }
    while (v687 < v680->FrameCount);
  }
  v689 = evtAddObject(39, pInfo);
  v690 = p_pm2;
  if (p_pm2->FrameCount >= 1)
  {
    v691 = v689;
    v692 = 4;
    do
    {
      v698 = *((u64 *)&v690->FrameTable->obj.klass + v692);
      if (*(u32 *)(v698 + 16) == 39)
      {
        v694 = *(u16 *)(v698 + 20);
        v695 = evtAddFrameInfo(v691, v694, pInfo)->data[0];
        v696 = get_i(*(pmdDataInfo_t *)(*(u64 *)(*((u64 *)&p_pm2->FrameTable->obj.klass + v692) + 32) + 32), 0);
        set_i(v695, v696, 0);
        v690 = p_pm2;
      }
      v697 = v692 - 3;
      ++v692;
    }
    while (v697 < v690->FrameCount);
  }
  v699 = evtAddObject(40, pInfo);
  v700 = p_pm2;
  if (p_pm2->FrameCount >= 1)
  {
    v701 = v699;
    v702 = 4;
    do
    {
      v708 = *((u64 *)&v700->FrameTable->obj.klass + v702);
      if (*(u32 *)(v708 + 16) == 40)
      {
        v704 = *(u16 *)(v708 + 20);
        v705 = evtAddFrameInfo(v701, v704, pInfo)->data[0];
        v706 = get_i(*(pmdDataInfo_t *)(*(u64 *)(*((u64 *)&p_pm2->FrameTable->obj.klass + v702) + 32) + 32), 0);
        set_i(v705, v706, 0);
        v700 = p_pm2;
      }
      v707 = v702 - 3;
      ++v702;
    }
    while (v707 < v700->FrameCount);
  }
  v709 = evtAddObject(41, pInfo);
  v710 = p_pm2;
  if (p_pm2->FrameCount >= 1)
  {
    v711 = v709;
    v712 = 4;
    do
    {
      v721 = *((u64 *)&v710->FrameTable->obj.klass + v712);
      if (*(u32 *)(v721 + 16) == 41)
      {
        v714 = *(u16 *)(v721 + 20);
        v715 = evtAddFrameInfo(v711, v714, pInfo);
        v716 = v715->data[0];
        v717 = get_i(*(pmdDataInfo_t *)(*(u64 *)(*((u64 *)&p_pm2->FrameTable->obj.klass + v712) + 32) + 32), 0);
        set_i(v716, v717, 0);
        v718 = v715->data[1];
        v719 = get_i(*(pmdDataInfo_t *)(*(u64 *)(*((u64 *)&p_pm2->FrameTable->obj.klass + v712) + 32) + 40), 0);
        set_i(v718, v719, 0);
        v710 = p_pm2;
      }
      v720 = v712 - 3;
      ++v712;
    }
    while (v720 < v710->FrameCount);
  }
  v722 = evtAddObject(42, pInfo);
  v723 = p_pm2;
  if (p_pm2->FrameCount >= 1)
  {
    v724 = v722;
    for (i3 = 0; i3 < v723->FrameCount; ++i3)
    {
      v727 = v723->FrameTable[i3];
      if (v727->ObjectType == 42)
      {
        v729 = v727->Frame;
        v730 = evtAddFrameInfo(v724, v729, pInfo);
        v731 = v730->data[0];
        v732 = get_i(p_pm2->FrameTable[i3]->Data[0], 0);
        set_i(v731, v732, 0);
        v733 = v730->data[1];
        v734 = get_i(p_pm2->FrameTable[i3]->Data[1], 0);
        set_i(v733, v734, 0);
        v735 = v730->data[2];
        v736 = get_i(p_pm2->FrameTable[i3]->Data[2], 0);
        set_i(v735, v736, 0);
        v737 = v730->data[3];
        v738 = get_i(p_pm2->FrameTable[i3]->Data[3], 0);
        set_i(v737, v738, 0);
        v739 = v730->data[4];
        v740 = get_i(p_pm2->FrameTable[i3]->Data[4], 0);
        set_i(v739, v740, 0);
        v741 = v730->data[5];
        v742 = get_i(p_pm2->FrameTable[i3]->Data[5], 0);
        set_i(v741, v742, 0);
        v743 = v730->data[6];
        v744 = get_i(p_pm2->FrameTable[i3]->Data[6], 0);
        set_i(v743, v744, 0);
        v745 = v730->data[7];
        v726 = get_i(p_pm2->FrameTable[i3]->Data[7], 0);
        set_i(v745, v726, 0);
        v723 = p_pm2;
        continue;
      }
    }
  }
  v746 = evtAddObject(44, pInfo);
  v747 = p_pm2;
  if (p_pm2->FrameCount >= 1)
  {
    v748 = v746;
    for (i4 = 0; i4 < v747->FrameCount; ++i4)
    {
      v751 = v747->FrameTable[i4];
      if (v751->ObjectType == 44)
      {
        v753 = v751->Frame;
        v754 = evtAddFrameInfo(v748, v753, pInfo);
        v755 = v754->data[0];
        v756 = get_i(p_pm2->FrameTable[i4]->Data[0], 0);
        set_i(v755, v756, 0);
        v757 = v754->data[1];
        v758 = get_i(p_pm2->FrameTable[i4]->Data[1], 0);
        set_i(v757, v758, 0);
        v759 = v754->data[2];
        v760 = get_i(p_pm2->FrameTable[i4]->Data[2], 0);
        set_i(v759, v760, 0);
        v761 = v754->data[3];
        v762 = get_i(p_pm2->FrameTable[i4]->Data[3], 0);
        set_i(v761, v762, 0);
        v763 = v754->data[4];
        v764 = get_i(p_pm2->FrameTable[i4]->Data[4], 0);
        set_i(v763, v764, 0);
        v765 = v754->data[5];
        v766 = get_i(p_pm2->FrameTable[i4]->Data[5], 0);
        set_i(v765, v766, 0);
        v767 = v754->data[6];
        v768 = get_i(p_pm2->FrameTable[i4]->Data[6], 0);
        set_i(v767, v768, 0);
        v769 = v754->data[7];
        v750 = get_i(p_pm2->FrameTable[i4]->Data[7], 0);
        set_i(v769, v750, 0);
        v747 = p_pm2;
        continue;
      }
    }
  }
  v770 = evtAddObject(43, pInfo);
  v771 = p_pm2;
  if (p_pm2->FrameCount >= 1)
  {
    v772 = v770;
    v773 = 4;
    do
    {
      v779 = *((u64 *)&v771->FrameTable->obj.klass + v773);
      if (*(u32 *)(v779 + 16) == 43)
      {
        v775 = *(u16 *)(v779 + 20);
        v776 = evtAddFrameInfo(v772, v775, pInfo)->data[0];
        v777 = get_i(*(pmdDataInfo_t *)(*(u64 *)(*((u64 *)&p_pm2->FrameTable->obj.klass + v773) + 32) + 32), 0);
        set_i(v776, v777, 0);
        v771 = p_pm2;
      }
      v778 = v773 - 3;
      ++v773;
    }
    while (v778 < v771->FrameCount);
  }
  if (v771->ObjectTable && v771->ObjectCount >= 1)
  {
    v780 = 0;
    while (1)
    {
      v782 = pInfo->firstobjinfo;
      v783 = v771->ObjectTable[v780];
      if (v783->NameIndex != -1)
      {
        for (; v782; v782 = v782->next)
        {
          v786 = (u32)v782->nameindex;
          if ((v786 & 0x80000000) == 0)
          {
            nametable = pInfo->nametable;
            if ((s32)v786 < SLODWORD(nametable->max_length) && Equals_54828784(nametable[v786]->Name, p_pm2->NameTable2[p_pm2->ObjectTable[v780]->NameIndex]->Name, 0))
            {
              object_data = v782->object_data;
              v789 = p_pm2->ObjectTable[v780];
              v790 = v789->NameIndex;
              object_data->ObjectType = v789->ObjectType;
              type = v782->type;
              object_data->NameIndex = v790;
              if (type == 2)
                Offset = 0;
              else
                Offset = v789->Offset;
              union0 = v789->union0;
              object_data->Offset = Offset;
              set_LinkType(object_data, union0, 0);
              v782->object_data->union1 = p_pm2->ObjectTable[v780]->union1;
            }
          }
        }
        goto LABEL_839;
      }
      if (v782)
        break;
LABEL_839:
      v771 = p_pm2;
      if (++v780 >= p_pm2->ObjectCount)
        goto LABEL_870;
    }
    v792 = v783->ObjectType;
    while (1)
    {
      if (v782->type == v792)
      {
        ObjectNo = v783->ObjectNo;
        if (v782->myno == ObjectNo)
          break;
      }
      v782 = v782->next;
      if (!v782)
        goto LABEL_839;
    }
    v794 = v782->object_data;
    v794->ObjectType = v792;
    v795 = v783->Offset;
    v796 = v783->union0;
    v794->ObjectNo = ObjectNo;
    v794->NameIndex = -1;
    v794->Offset = v795;
    set_LinkType(v794, v796, 0);
    v797 = v782->object_data;
    v797->union1 = p_pm2->ObjectTable[v780]->union1;
    if (v797->union0 != 3)
    {
      LOBYTE(v781) = 0;
      goto LABEL_9014;
    }
    if (p_pm2->ObjectCount >= 1)
    {
      v799 = pInfo->firstobjinfo;
      if (v799)
      {
        v800 = 0;
        do
        {
LABEL_863:
          if (Equals_54828784(pInfo->nametable[v799->nameindex]->Name, p_pm2->NameTable2[v797->union1]->Name, 0))
          {
            v781 = v799->nameindex;
            goto LABEL_838;
          }
          v799 = v799->next;
        }
        while (v799);
        while (++v800 < p_pm2->ObjectCount)
        {
          v799 = pInfo->firstobjinfo;
          if (v799)
            goto LABEL_863;
        }
      }
    }
    set_LinkType(v797, 0, 0);
    LOBYTE(v781) = 0;
LABEL_9014:
LABEL_838:
    v797->union1 = v781;
    goto LABEL_839;
  }
LABEL_870:
  IntVariable = GBWK->IntVariable;
  IntVariable[200] = -1;
  IntVariable[201] = -1;
  goto LABEL_874;
LABEL_875:
  IntVariable[203] = -1;
  goto LABEL_876;
LABEL_877:
  IntVariable[205] = -1;
  goto LABEL_878;
LABEL_879:
  IntVariable[207] = -1;
  goto LABEL_880;
LABEL_881:
  IntVariable[209] = -1;
  if ((v404 & 1) == 0)
    goto LABEL_894;
  evtLoad(v807->pm1->StageTable->MajorNum);
  while (!CheckLoad(v807->pm1->StageTable->MajorNum))
    ;
  goto LABEL_894;
LABEL_874:
  IntVariable[202] = -1;
  goto LABEL_875;
LABEL_876:
  IntVariable[204] = -1;
  goto LABEL_877;
LABEL_878:
  IntVariable[206] = -1;
  goto LABEL_879;
LABEL_880:
  IntVariable[208] = -1;
  goto LABEL_881;
LABEL_894:
  if ((pInfo->cutVal & 3) == 0)
  {
    if (!v804)
    dds3ChangeBistaMode(1);
    dds3BistaOut(0);
    goto LABEL_9015;
  }
  if (v804)
  {
    dds3BistaIn(0);
  }
  else
  {
    dds3BistaIn(0);
  }
LABEL_9015:
  evtStopFrame(pInfo);
  evtRunFrame(pInfo->nowframe, pInfo);
  evtStopFrame(pInfo);
  return 1;
}

// 0x19bdf50
void evtSetTestCamera(void) {
  u32 v1;
  dds3Basic_t *ControlScene;
  dds3Basic_t *v3;
  dds3Basic_t *pBasic;
  sdfVector4_t v5;
  sdfVector4_t v6;

  v1 = dds3SerializeID();
  v6.w = 1.0;
  v5.y = -100.0;
  v5.z = -600.0;
  v5.x = 0.0;
  v5.w = 0.0;
  v6.x = 0.0;
  v6.y = 0.0;
  v6.z = 0.0;
  pBasic = dds3CameraObjectBasicAddTypeFree(v1, v5, v6);
  dds3SetRadiusPoseSet(pBasic, 10.0);
  dds3ObjectBaseCreateMover(pBasic);
  ControlScene = dds3GetControlScene();
  v3 = pBasic;
  SetActiveCamera(ControlScene, v3, 0);
  dds3ObjectBaseSetPadControl(pBasic, 0);
}

// 0x19b6fa0
s32 evtSetRegistUnit(MODELTYPE major, s32 minor) {
  u32 v6;
  dds3ModelHandle_t *ModelHandle;
  dds3ModelHandle_t *v9;
  dds3Basic_t *pObjectBasic;
  sdfVector4_t v14;
  sdfVector4_t v15;

  v6 = dds3SerializeID();
  v14.w = 1.0;
  v14.x = 0.0;
  v14.y = 0.0;
  v14.z = 0.0;
  v15.x = 0.0;
  v15.y = 0.0;
  v15.z = 0.0;
  v15.w = 1.0;
  pObjectBasic = dds3UnitObjectBasicAdd(v6, v14, v15);
  dds3ObjectBaseOnFlag(pObjectBasic, 0x20u);
  dds3SetRadiusPoseSet(pObjectBasic, 10.0);
  dds3ObjectBaseMakeUnit(pObjectBasic, major, minor);
  ModelHandle = dds3ObjectBaseGetModelHandle(pObjectBasic);
  v9 = ModelHandle;
  itfCriLipSyncManagerOff(ModelHandle);
  if (!!mdlHasMotion(v9))
    mdlLoopMotion(v9, 0, 0);
  dds3ObjectBaseSetPadControl(pObjectBasic, 0);
  return v6;
}

// 0x19be0b0
s32 evtLoadUnit(MODELTYPE major, s32 minor) {
  u32 v6;
  dds3ModelHandle_t *ModelHandle;
  dds3ModelHandle_t *v9;
  s64 naturalAligment;
  s64 v11;
  dds3Basic_t *v14;
  dds3Basic_t *pBasic;
  dds3Basic_t *pObjectBasic;
  sdfVector4_t v17;
  sdfVector4_t v18;

  v14 = 0;
  pBasic = 0;
  v6 = dds3SerializeID();
  v17.w = 1.0;
  v17.x = 0.0;
  v17.y = 0.0;
  v17.z = 0.0;
  v18.x = 0.0;
  v18.y = 0.0;
  v18.z = 0.0;
  v18.w = 1.0;
  pObjectBasic = dds3UnitObjectBasicAdd(v6, v17, v18);
  dds3ObjectBaseOnFlag(pObjectBasic, 0x20u);
  dds3SetRadiusPoseSet(pObjectBasic, 10.0);
  dds3ObjectBaseMakeUnit(pObjectBasic, major, minor);
  ModelHandle = dds3ObjectBaseGetModelHandle(pObjectBasic);
  v9 = ModelHandle;
  if (ModelHandle)
  {
    if (ModelHandle->klass->_2.naturalAligment < (u32)naturalAligment || ModelHandle->klass->_2.typeHierarchy[naturalAligment - 1] != dds3ModelHandle_t)
    {
LABEL_27:
    }
  }
  itfCriLipSyncManagerOff(v9);
  mdlLoopMotion(v9, 0, 0);
  mdlSetMotionSpeedEx(v9, 0, 0.5);
  mdlSetMotionSpeedEx(v9, 1, 0.5);
  mdlSetMotionSpeedEx(v9, 2, 0.5);
  ModelHandle = pObjectBasic->workdata;
  if (ModelHandle)
  {
    if (ModelHandle->klass->_2.naturalAligment < (u32)v11 || ModelHandle->klass->_2.typeHierarchy[v11 - 1] != Project_Basic_dds3UnitObjectBasicWorkData_t)
    {
      goto LABEL_27;
    }
  }
  *(u32 *)(&ModelHandle->prev[4].motionMinorNum + 1) = 1056964608;
  pBasic = dds3GetControlScene();
  v14 = dds3SceneBasicSearch(pBasic, 0x10000u, 2u);
  dds3ObjectBaseSetControlBasic(pObjectBasic, v14);
  dds3ObjectBaseRegistArea(pObjectBasic);
  dds3ObjectBaseSetPadControl(pObjectBasic, 0);
  dds3ObjectBaseOnFlag(pObjectBasic, 0x400u);
  return v6;
}

// 0x19be510
evtBustupLight_t *evtGetBustupLightTable(void) {
  return bustup_light_tbl;
}

// 0x19be590
f32 evtEuclid(f32 variable1, f32 variable2) {
  f32 v4;
  f32 v6;

  v4 = sub_188E3E0(variable1);
  if (v4 == 0.0)
    return variable2;
  do
  {
    v6 = v4;
    v4 = sub_188E3E0(variable2);
    variable2 = v6;
  }
  while (v4 != 0.0);
  return v6;
}

// 0x19be5f0
f32 evtGetWidthDiv(void) {
  f32 v1;
  f32 v2;
  f32 v3;

  v1 = 1080.0;
  v2 = 840.0;
  do
  {
    v3 = v1;
    v1 = v2;
    v2 = sub_188E3E0(v3);
  }
  while (v2 != 0.0);
  return (f32)((f32)(1920.0 / v1) * (f32)((f32)(540.0 / v1) / (f32)(1080.0 / v1))) / (f32)(720.0 / v1);
}

// 0x19be6c0
s32 evtGetDefaultPosBustUp(MODELTYPE major, BUSTUP_POS_TBL_t *tbl, s32 type, sdfVector4_t *pos, sdfVector4_t *rot, sdfVector4_t *defpos) {
  f32 v14;
  f32 v15;
  f32 v16;
  f32 v17;
  f32 PosLX;
  f32 *p_AngL;
  f32 v20;
  f32 Scale;
  f32 v22;
  f32 v23;

  v14 = 1080.0;
  v15 = 840.0;
  do
  {
    v16 = v14;
    v14 = v15;
    v15 = sub_188E3E0(v16);
  }
  while (v15 != 0.0);
  v17 = (f32)((f32)(1920.0 / v14) * (f32)((f32)(540.0 / v14) / (f32)(1080.0 / v14))) / (f32)(720.0 / v14);
  switch (type)
  {
    case 0:
    case 2:
      PosLX = tbl->PosLX;
      p_AngL = &tbl->AngL;
      goto LABEL_14;
    case 1:
    case 3:
      PosLX = tbl->PosRX;
      p_AngL = &tbl->AngR;
LABEL_14:
      pos->x = v17 * PosLX;
      rot->y = *p_AngL * -0.017453292;
      break;
    default:
      break;
  }
  pos->z = 0.0;
  v20 = 1.0;
  Scale = tbl->Scale;
  if (Scale != 1.0)
  {
    v22 = 0.0;
    if (v17 >= 1.2)
      v22 = v17 / 10.0;
    v20 = (f32)(v22 + Scale) * 1.1;
  }
  pos->y = tbl->PosY * v20;
  defpos->x = pos->x;
  defpos->y = pos->y;
  defpos->z = pos->z;
  if (!type)
  {
    v23 = -150.0;
    goto LABEL_23;
  }
  if (type == 1)
  {
    v23 = 150.0;
LABEL_23:
    pos->x = pos->x + v23;
  }
  return 1;
}

// 0x19be900
s32 evtLoadUnitBustUp(MODELTYPE major, s32 minor, s32 type) {
  u32 v8;
  f32 v11;
  f32 v12;
  f32 v13;
  u32 v16;
  BUSTUP_POS_TBL_t *v18;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  f32 v23;
  f32 v24;
  f32 v25;
  dds3ModelHandle_t *ModelHandle;
  dds3ModelHandle_t *v27;
  s64 naturalAligment;
  s64 v29;
  f32 Scale;
  f32 v31;
  f32 v32;
  f32 v34;
  void *gameObject;
  dds3Basic_t *prev;
  s64 v37;
  sdfVector4_t *p_color;
  s64 v41;
  f32 aRot;
  dds3Basic_t *pBasic;
  dds3Basic_t *pItemBasic;
  dds3Basic_t *pObjectBasic;
  sdfVector4_t defpos;
  sdfVector4_t rot;
  sdfVector4_t pos;
  sdfVector4_t v57;
  sdfVector4_t v58;
  sdfVector4_t v59;

  pItemBasic = 0;
  pObjectBasic = 0;
  pBasic = 0;
  *(u64 *)&defpos.x = 0;
  *(u64 *)&defpos.z = 0;
  rot = (sdfVector4_t)xmmword_3CFD5C0;
  pos = (sdfVector4_t)xmmword_3CFD5C0;
  v8 = dds3SerializeID();
  v11 = 1080.0;
  v12 = 840.0;
  do
  {
    v13 = v11;
    v11 = v12;
    v12 = sub_188E3E0(v13);
  }
  while (v12 != 0.0);
  if (SLODWORD(bustup_pos_tbl->max_length) <= minor)
  {
    if (v16)
    {
      v18 = bustup_pos_tbl[0];
      goto LABEL_17;
    }
    v18 = bustup_pos_tbl[0];
  }
  else
  {
    v18 = bustup_pos_tbl[minor];
  }
LABEL_17:
  evtGetDefaultPosBustUp((u16)evt, v18, type, &pos, &rot, &defpos);
  x = pos.x;
  y = pos.y;
  z = pos.z;
  w = pos.w;
  v23 = rot.x;
  v24 = rot.y;
  v25 = rot.z;
  v59.w = rot.w;
  aRot = rot.w;
  v59.w = aRot;
  v57.x = x;
  v57.y = y;
  v57.z = z;
  v57.w = w;
  v59.x = v23;
  v59.y = v24;
  v59.z = v25;
  pObjectBasic = dds3UnitObjectBasicAdd(v8, v57, v59);
  dds3UnitObjectBasicSetOt(pObjectBasic, 13);
  dds3ObjectBaseOnFlag(pObjectBasic, 0x20u);
  dds3SetRadiusPoseSet(pObjectBasic, 10.0);
  dds3ObjectBaseMakeUnit(pObjectBasic, major, minor);
  ModelHandle = dds3ObjectBaseGetModelHandle(pObjectBasic);
  v27 = ModelHandle;
  if (ModelHandle)
  {
    if (ModelHandle->klass->_2.naturalAligment < (u32)naturalAligment || ModelHandle->klass->_2.typeHierarchy[naturalAligment - 1] != dds3ModelHandle_t)
    {
      goto LABEL_73;
    }
  }
  v27->IsBustUp = 1;
  mdlLoopMotion(v27, 0, 0);
  mdlSetMotionSpeedEx(v27, 0, 0.5);
  mdlSetMotionSpeedEx(v27, 1, 0.5);
  mdlSetMotionSpeedEx(v27, 2, 0.5);
  ModelHandle = pObjectBasic->workdata;
  if (ModelHandle)
  {
    if (ModelHandle->klass->_2.naturalAligment < (u32)v29 || ModelHandle->klass->_2.typeHierarchy[v29 - 1] != Project_Basic_dds3UnitObjectBasicWorkData_t)
    {
LABEL_73:
    }
  }
  *(u32 *)(&ModelHandle->prev[4].motionMinorNum + 1) = 1056964608;
  Scale = v18->Scale;
  v31 = (f32)((f32)(1920.0 / v11) * (f32)((f32)(540.0 / v11) / (f32)(1080.0 / v11))) / (f32)(720.0 / v11);
  if (v31 >= 1.2)
  {
    v32 = (f32)(v31 / 10.0) + Scale;
    v34 = v32;
    goto LABEL_36;
  }
  else
  {
    v32 = Scale + 0.0;
    v34 = Scale + 0.0;
    goto LABEL_36;
  }
LABEL_36:
  v58.w = 1.0;
  v58.x = v32;
  v58.y = v32;
  v58.z = v34;
  dds3SetSclPoseSet(pObjectBasic, v58);
  gameObject = get_gameObject(v27->modelRoot->modelObj, 0);
  AddComponent_object_(gameObject);
  prev = pObjectBasic;
  if (pObjectBasic)
  {
    ModelHandle = prev->workdata;
    if (ModelHandle)
    {
      if (ModelHandle->klass->_2.naturalAligment < (u32)v37 || ModelHandle->klass->_2.typeHierarchy[v37 - 1] != Project_Basic_dds3UnitObjectBasicWorkData_t)
      {
        goto LABEL_73;
      }
    }
    prev = ModelHandle->prev;
  }
  p_color = &prev[4].color;
  *p_color = defpos;
  pBasic = dds3GetControlScene();
  pItemBasic = dds3SceneBasicSearch(pBasic, 0x10000u, 2u);
  dds3ObjectBaseSetControlBasic(pObjectBasic, pItemBasic);
  dds3ObjectBaseRegistArea(pObjectBasic);
  dds3ObjectBaseSetPadControl(pObjectBasic, 0);
  ModelHandle = pObjectBasic->workdata;
  if (ModelHandle)
  {
    if (ModelHandle->klass->_2.naturalAligment < (u32)v41 || ModelHandle->klass->_2.typeHierarchy[v41 - 1] != Project_Basic_dds3UnitObjectBasicWorkData_t)
    {
      goto LABEL_73;
    }
  }
  HIDWORD(ModelHandle->prev[4].prev) |= 0x300u;
  evtSetLightBustup(v8, 0, 0, 0);
  if ((type | 2) == 2)
  {
    bustup_lightno[0] = 0;
    bustup_sid0 = v8;
  }
  else
  {
    bustup_lightno[1] = 1;
    bustup_sid1 = v8;
  }
  *(u64 *)&HCameraTargetPos.x = 0;
  HCameraTargetPos.z = 0.0;
  *(u64 *)&HCameraEyePos.x = 0;
  HCameraEyePos.z = -400.0;
  HScreenParam->fovy = 0.2617994;
  return v8;
}

// 0x19bf0a0
void evtSetLightBustup(s32 unitID, s32 frame, s32 lightNo, evtBustupLight_t *org_tbl) {
  dds3Basic_t *v13;
  void *workdata;
  evtUnitHandle_t *klass;
  f32 x;
  float32x2_t v18;
  f32 w;
  int32x2_t v20;
  u32 v21;
  u32 v22;
  f32 v23;
  f32 v24;
  f32 v25;
  u32 v26;
  float32x2_t v27;
  float32x2_t v28;
  float32x2_t v29;
  s32 v30;
  bool v31;
  u32 v32;
  int8x8_t v33;
  int32x2_t v34;
  int32x2_t v35;
  uint32x2_t v36;
  u32 v37;
  f32 v38;
  u32 v39;
  s32 v40;
  int8x8_t v41;
  int32x2_t v42;
  int32x2_t v43;
  uint32x2_t v44;
  int8x8_t v45;
  f32 v46;
  s32 v47;
  u32 v48;
  u32 v49;
  uint32x2_t v50;
  uint32x2_t v51;
  u64 v52;
  u64 v53;
  s32 v54;
  f32 v55;
  int8x8_t v56;
  s32 v57;
  u32 v58;
  f32 v59;
  u32 v60;
  u32 v61;
  u32 v62;
  s32 v63;
  float32x2_t v64;
  u32 v65;
  u32 v66;
  int32x2_t v67;
  u32 v68;
  int32x2_t v69;
  uint32x2_t v70;
  u64 v71;
  struct sdfVector4_t DirL2;
  struct sdfVector4_t DirL3;
  struct sdfVector4_t DirR2;
  struct sdfVector4_t DirL1;
  struct sdfVector4_t v88;
  struct sdfVector4_t v89;
  struct sdfVector4_t DirR1;
  struct sdfVector4_t v91;
  struct sdfVector4_t v92;
  struct sdfVector4_t v94;
  dds3Basic_t *pBasic;
  dds3Basic_t *v96;

  pBasic = 0;
  v96 = 0;
  if (!org_tbl)
    org_tbl = bustup_light_tbl[lightNo];
  pBasic = dds3GetControlScene();
  v96 = dds3SceneBasicSearch(pBasic, unitID, 5u);
  if (!v96)
    return;
  if (SLODWORD(bustup_light_tbl->max_length) <= lightNo)
    return;
  v13 = v96;
  if (!v96)
  {
    klass = 0;
    goto LABEL_26;
  }
  workdata = v13->workdata;
  klass = workdata[2].klass;
LABEL_26:
  x = org_tbl->Col1.x;
  v18.n64_u64[0] = *(u64 *)&org_tbl->Col1.y;
  w = org_tbl->Col1.w;
  v20.n64_u64[0] = vdup_n_s32(0x42FE0000u).n64_u64[0];
  v21 = vcvts_n_s32_f32(w, 7u);
  v22 = vcvts_n_u32_f32(w, 7u);
  v23 = x * 127.0;
  v24 = org_tbl->Col2.x * 127.0;
  v25 = org_tbl->Col2.w;
  v26 = vcvts_n_s32_f32(v25, 7u);
  v27.n64_u64[0] = vmul_f32(v18, v20).n64_u64[0];
  v28.n64_u64[0] = vmul_f32(*(float32x2_t *)&org_tbl->Col2.y, v20).n64_u64[0];
  v29.n64_u64[0] = vmul_f32(*(float32x2_t *)&org_tbl->Col3.y, v20).n64_u64[0];
  if ((f32)(w * 128.0) >= 0.0)
    v21 = v22;
  v30 = v23;
  v31 = v23 < 0.0;
  v32 = v23;
  v33.n64_u64[0] = vbsl_s8(vcltz_f32(v27), vcvt_s32_f32(v27), vcvt_u32_f32(v27)).n64_u64[0];
  v34.n64_u64[0] = vcltz_f32(v28).n64_u64[0];
  v35.n64_u64[0] = vcvt_s32_f32(v28).n64_u64[0];
  v36.n64_u64[0] = vcvt_u32_f32(v28).n64_u64[0];
  v37 = vcvts_n_u32_f32(v25, 7u);
  v38 = v25 * 128.0;
  if (!v31)
    LOBYTE(v30) = v32;
  v39 = v24;
  v40 = (u8)v30 | (v21 << 24);
  v41.n64_u64[0] = vbsl_s8(v34, v35, v36).n64_u64[0];
  v42.n64_u64[0] = vcltz_f32(v29).n64_u64[0];
  v43.n64_u64[0] = vcvt_s32_f32(v29).n64_u64[0];
  v44.n64_u64[0] = vcvt_u32_f32(v29).n64_u64[0];
  if (v38 < 0.0)
    v37 = v26;
  v45.n64_u64[0] = vbsl_s8(v42, v43, v44).n64_u64[0];
  v46 = org_tbl->Col3.w;
  if (v24 < 0.0)
    LOBYTE(v39) = (s32)v24;
  v47 = (u8)v39 | (v37 << 24);
  v48 = vcvts_n_s32_f32(v46, 7u);
  v49 = vcvts_n_u32_f32(v46, 7u);
  v50.n64_u64[0] = vshl_u32(v41, (uint32x2_t)0x1000000008LL).n64_u64[0];
  v51.n64_u64[0] = vshl_u32(v33, (uint32x2_t)0x1000000008LL).n64_u64[0];
  if ((f32)(v46 * 128.0) < 0.0)
    v49 = v48;
  v52 = vand_s8(v50, (int8x8_t)0xFF00000000FF00LL).n64_u64[0];
  v53 = vand_s8(v51, (int8x8_t)0xFF00000000FF00LL).n64_u64[0];
  v54 = v52;
  *(f32 *)&v52 = org_tbl->Col3.x * 127.0;
  v55 = org_tbl->Amb.x * 127.0;
  v56.n64_u64[0] = vand_s8(vshl_u32(v45, (uint32x2_t)0x1000000008LL), (int8x8_t)0xFF00000000FF00LL).n64_u64[0];
  v57 = *(f32 *)&v52;
  v58 = *(f32 *)&v52;
  v31 = *(f32 *)&v52 < 0.0;
  v59 = org_tbl->Amb.w;
  v60 = v40 | v53 | HIDWORD(v53);
  v61 = v47 | v54 | HIDWORD(v52);
  v62 = vcvts_n_u32_f32(v59, 7u);
  if (!v31)
    LOBYTE(v57) = v58;
  v63 = v55;
  v64.n64_u64[0] = vmul_f32(*(float32x2_t *)&org_tbl->Amb.y, v20).n64_u64[0];
  v65 = (u8)v57 | (v49 << 24) | v56.n64_u32[0] | v56.n64_u32[1];
  v66 = vcvts_n_s32_f32(v59, 7u);
  v67.n64_u64[0] = vcltz_f32(v64).n64_u64[0];
  v68 = v55;
  if ((f32)(v59 * 128.0) < 0.0)
    v62 = v66;
  v31 = v55 < 0.0;
  v69.n64_u64[0] = vcvt_s32_f32(v64).n64_u64[0];
  v70.n64_u64[0] = vcvt_u32_f32(v64).n64_u64[0];
  if (!v31)
    LOBYTE(v63) = v68;
  v71 = vand_s8(vshl_u32(vbsl_s8(v67, v69, v70), (uint32x2_t)0x1000000008LL), (int8x8_t)0xFF00000000FF00LL).n64_u64[0];
  evtSetUnitLightAndAmbient3(klass, frame, v60, v61, v65, (u8)v63 | (v62 << 24) | v71 | HIDWORD(v71));
  dds3GetPosPoseSet(v96);
  if (vct_A.x < 0.0)
  {
    bustup_lightno[0] = lightNo;
    DirL1 = org_tbl->DirL1;
    vct_A = DirL1;
    evtSetUnitLightDir(klass, frame);
    DirL2 = org_tbl->DirL2;
    v88 = org_tbl->DirL2;
    DirL2 = v88;
    v89 = DirL2;
    DirL2 = v89;
    vct_A = DirL2;
    evtSetUnitLightDir1(klass, frame);
    DirL3 = org_tbl->DirL3;
    goto LABEL_73;
  }
  bustup_lightno[1] = lightNo;
  DirR1 = org_tbl->DirR1;
  vct_A = DirR1;
  evtSetUnitLightDir(klass, frame);
  DirR2 = org_tbl->DirR2;
  v91 = org_tbl->DirR2;
  DirR2 = v91;
  v92 = DirR2;
  DirR2 = v92;
  vct_A = DirR2;
  evtSetUnitLightDir1(klass, frame);
  DirL3 = org_tbl->DirR3;
LABEL_73:
  v94 = DirL3;
  DirL3 = v94;
  vct_A = DirL3;
  evtSetUnitLightDir2(klass, frame);
}

// 0x19c0490
s32 evtGetDrawBustupNums(void) {
  dds3BasicArrayHandle_t *v1;
  s32 BasicArrayCount;
  s32 v5;
  void *workdata;
  dds3Basic_t *pBasic;
  dds3BasicArrayHandle_t *hndl;

  v1 = Allocate(dds3BasicArrayHandle_t);
  _ctor(v1, 0);
  pBasic = dds3GetActiveScene();
  if (!pBasic)
    return 0;
  hndl = dds3SceneBasicGetList(pBasic, 5u);
  if (!hndl)
    return 0;
  BasicArrayCount = dds3GetBasicArrayCount(hndl);
  if (!BasicArrayCount)
  {
    v5 = 0;
    goto LABEL_34;
  }
  v5 = 0;
  if (!dds3SetFirstBasicArray(hndl))
    goto LABEL_32;
  while (1)
  {
LABEL_22:
    workdata = dds3GetBasicArray(hndl)->workdata;
    if (HIDWORD(workdata[3].klass) == 13)
      ++v5;
    if (!dds3SetNextBasicArray(hndl))
      goto LABEL_32;
  }
  v5 = 0;
  if (dds3SetFirstBasicArray(hndl))
    goto LABEL_22;
LABEL_32:
LABEL_34:
  dds3FreeBasicArrayHandle(hndl);
  return v5;
}

// 0x19c06f0
void evtSetUnitPos(s32 unitID, s32 posID) {
  dds3Basic_t *v7;
  void *workdata;
  f32 v10;
  f32 v11;
  f32 v12;
  f32 v13;
  struct sdfVector4_t v15;
  dds3PoseSet_t *poseset;
  sdfVector4_t *p_pos2;
  dds3Basic_t *pBasic;
  dds3Basic_t *v24;
  sdfVector4_t v25;

  pBasic = dds3GetControlScene();
  v24 = dds3SceneBasicSearch(pBasic, unitID, 5u);
  if (!v24)
    return;
  v7 = dds3SceneBasicSearch(pBasic, posID, 0x10u);
  if (!v7)
    return;
  workdata = v7->workdata;
  v10 = *(f32 *)&workdata[1].klass;
  v11 = *((f32 *)&workdata[1].klass + 1);
  v13 = *(f32 *)&workdata[1].monitor;
  v12 = *((f32 *)&workdata[1].monitor + 1);
  v25.x = v10;
  v25.y = v11;
  v25.z = v13;
  v25.w = v12;
  dds3SetPosPoseSet(v24, v25);
  vct_A = (struct sdfVector4_t)xmmword_3D015F0;
  FromRotation(3.1415927);
  v15 = (struct sdfVector4_t)workdata[2];
  vct_B = v15;
  Mult();
  dds3SetRotPoseSet(v24, vct_A);
  dds3GetPosPoseSet(v24);
  poseset = v24->poseset;
  p_pos2 = &poseset->pos2;
  *p_pos2 = vct_A;
}

// 0x19c0a90
void evtSetUnitPosCustom(s32 unitID, s32 posID, f32 posX, f32 posY, f32 posZ) {
  dds3Basic_t *v13;
  void *workdata;
  f32 v16;
  f32 v17;
  f32 v18;
  f32 v19;
  struct sdfVector4_t v21;
  dds3PoseSet_t *poseset;
  sdfVector4_t *p_pos2;
  dds3Basic_t *pBasic;
  dds3Basic_t *v30;
  sdfVector4_t v31;

  pBasic = dds3GetControlScene();
  v30 = dds3SceneBasicSearch(pBasic, unitID, 5u);
  if (!v30)
    return;
  v13 = dds3SceneBasicSearch(pBasic, posID, 0x10u);
  if (!v13)
    return;
  workdata = v13->workdata;
  v16 = *((f32 *)&workdata[1].monitor + 1);
  v17 = *((f32 *)&workdata[1].klass + 1) + posY;
  v18 = *(f32 *)&workdata[1].klass + posX;
  v19 = *(f32 *)&workdata[1].monitor + posZ;
  v31.x = v18;
  v31.y = v17;
  v31.z = v19;
  v31.w = v16;
  dds3SetPosPoseSet(v30, v31);
  vct_A = (struct sdfVector4_t)xmmword_3D015F0;
  FromRotation(3.1415927);
  v21 = (struct sdfVector4_t)workdata[2];
  vct_B = v21;
  Mult();
  dds3SetRotPoseSet(v30, vct_A);
  dds3GetPosPoseSet(v30);
  poseset = v30->poseset;
  p_pos2 = &poseset->pos2;
  *p_pos2 = vct_A;
}

// 0x19c0e40
void evtFreeStage(void) {
  dds3Basic_t *scene;

  scene = dds3GetControlScene();
  if (!scene)
    return;
  dds3DeleteScene(scene);
}

// 0x19c0ef0
void evtFreeAllUnit(void) {
  dds3Basic_t *ControlScene;
  void *workdata;
  dds3Basic_t *i;

  ControlScene = dds3GetControlScene();
  if (!ControlScene)
    return;
  workdata = ControlScene->workdata;
  for (i = *(dds3Basic_t *)(*((u64 *)workdata[1].monitor + 9) + 24); i; i = *(dds3Basic_t *)(*((u64 *)workdata[1].monitor + 9) + 24))
  {
    dds3SceneBasicDelete(i);
  }
}

// 0x19c1020
s32 evtLoadMap(s32 fld, s32 flor) {
  s32 v8;
  u32 v9;
  dds3Basic_t *v10;
  struct sdfVector4_t fld_default_ambient_local;
  struct sdfVector4_t v15;
  dds3Basic_t *scene;
  dds3Basic_t *ControlScene;

  scene = 0;
  ControlScene = dds3GetControlScene();
  if (!ControlScene)
  {
    goto LABEL_7;
  }
  dds3DeleteScene(ControlScene);
LABEL_7:
  scene = dds3AddScene();
  dds3SetControlScene(scene);
  dds3SetActiveScene(scene);
  v8 = flor + (fld << 16);
  dds3SetMapNo(scene, v8);
  dds3SetActiveScene(0);
  v9 = dds3SerializeID();
  dds3AreaBasicAdd(v9, "1st_area");
  v10 = dds3GetControlScene();
  dds3SetActiveScene(v10);
  dds3SceneBasicMakeScene(scene, "");
  evtSetTestCamera();
  dds3SetScreenFovy(0.7539823);
  dds3SetLight(fld_default_light[0], 0);
  dds3SetLight(fld_default_light[1], 1u);
  dds3SetLight(fld_default_light[2], 2u);
  fld_default_ambient_local = fld_default_ambient;
  v15 = fld_default_ambient;
  fld_default_ambient_local = v15;
  Ambient = fld_default_ambient_local;
  return 1;
}

// 0x19b6cb0
s32 evtLoadArea_FromMemory(s32 fld, s32 area, void *pF1, void *pF2, sdfBinary *pTB, sdfBinary *pBF) {
  struct sdfVector4_t fld_default_ambient_local;
  struct sdfVector4_t v20;
  dds3Basic_t *scene;
  dds3Basic_t *ControlScene;

  scene = 0;
  ControlScene = dds3GetControlScene();
  if (!ControlScene)
  {
    goto LABEL_7;
  }
  dds3DeleteScene(ControlScene);
LABEL_7:
  scene = dds3AddScene();
  dds3SetControlScene(scene);
  dds3SetActiveScene(scene);
  dds3SetMapNo(scene, area + (fld << 16));
  dds3SceneBasicMakeScene_FromMemory(scene, fld, area, pF1, pF2, pTB, pBF);
  evtSetTestCamera();
  dds3SetScreenFovy(0.7539823);
  dds3SetLight(fld_default_light[0], 0);
  dds3SetLight(fld_default_light[1], 1u);
  dds3SetLight(fld_default_light[2], 2u);
  fld_default_ambient_local = fld_default_ambient;
  v20 = fld_default_ambient;
  fld_default_ambient_local = v20;
  Ambient = fld_default_ambient_local;
  return 1;
}

// 0x19c1380
void evtStartEvent(s32 no) {
  char *v2;
  char *v3;
  char *v6;
  char *v7;
  s32 v9;

  v9 = no;
  v2 = ToString_55996800((s32)&v9, "d3", 0);
  v3 = Concat_54831728("e", v2, ".bf", 0);
  evtStartEvent_path = v3;
  v6 = ToString_55996800((s32)&v9, "d3", 0);
  v7 = Concat_54766928("e", v6, 0);
  scrStartScript3(1003, v7, evtStartEvent_path, 0, 1);
}

// 0x19c14d0
void evtKillFieldScript(void) {
  s32 v1;
  dds3ProcessID_t *v2;
  s32 priority;
  s32 v4;
  dds3ProcessID_t *v5;
  s32 v6;
  dds3ProcessID_t *id;

  v1 = 0;
  id = 0;
  {
    if (v1 >= dds3GetProcessCount(1u))
      goto LABEL_15;
LABEL_9:
    v2 = dds3SearchProcessNumber(1u, v1);
    priority = v2->priority;
    ++v1;
    id = v2;
    if (priority == 1002)
    {
      dds3KillProcess(id, 0);
      v1 = 0;
    }
  }
  if (v1 < dds3GetProcessCount(1u))
    goto LABEL_9;
LABEL_15:
  v4 = 0;
  while (1)
  {
    if (v4 >= dds3GetProcessCount(2u))
      break;
    v5 = dds3SearchProcessNumber(2u, v4);
    v6 = v5->priority;
    ++v4;
    id = v5;
    if (v6 == 1002)
    {
      dds3KillProcess(id, 0);
      goto LABEL_15;
    }
  }
}

// 0x19c1640
void evtPathStop(dds3Basic_t *basic) {
  dds3PathBasicControl_t *pControl;
  dds3Basic_t *pObjectBasic;

  pObjectBasic = basic;
  pControl = dds3ObjectBaseGetPathControl(pObjectBasic);
  if (pControl)
  {
    dds3PathBasicPause(pControl);
  }
}

// 0x19c16c0
void evtPathStart(dds3Basic_t *basic) {
  dds3PathBasicControl_t *pControl;
  dds3Basic_t *pObjectBasic;

  pObjectBasic = basic;
  pControl = dds3ObjectBaseGetPathControl(pObjectBasic);
  if (pControl)
  {
    dds3PathBasicPauseOff(pControl);
  }
}

// 0x19c1740
void evtPathRate(dds3Basic_t *basic, f32 rate) {
  f32 v4;
  f32 v5;
  dds3PathBasicControl_t *PathControl;
  dds3Basic_t *pObjectBasic;

  pObjectBasic = basic;
  PathControl = dds3ObjectBaseGetPathControl(pObjectBasic);
  if (PathControl)
  {
    v4 = 0.0;
    if (rate >= 0.0)
      v4 = rate;
    if (v4 <= 1.0)
      v5 = v4;
    else
      v5 = 1.0;
    dds3PathBasicControlSetRatio(PathControl, v5);
  }
}

// 0x19c17f0
void evtPathDir(dds3Basic_t *basic, s32 dir) {
  dds3PathBasicControl_t *PathControl;
  dds3Basic_t *pObjectBasic;

  pObjectBasic = basic;
  PathControl = dds3ObjectBaseGetPathControl(pObjectBasic);
  if (PathControl)
  {
    dds3PathBasicControlAlterMode(PathControl, dir);
  }
}

// 0x19b7340
bool evtPathLinkAndMake(dds3Basic_t *path, dds3Basic_t *obj) {
  dds3ObjectBaseControlWorkData_t *BaseControlWorkData;
  dds3Basic_t *v5;
  dds3Basic_t *pObjectBasic;

  pObjectBasic = obj;
  if (!path)
    goto LABEL_10;
  BaseControlWorkData = dds3GetBaseControlWorkData(pObjectBasic);
  if (!BaseControlWorkData)
    return (char)BaseControlWorkData;
  v5 = BaseControlWorkData->pBasic[1];
  if (v5)
  {
    dds3MoverBasicSetPath(v5, path);
    dds3MoverBasicMakePath(v5);
    LOBYTE(BaseControlWorkData) = 1;
  }
  else
  {
LABEL_10:
    LOBYTE(BaseControlWorkData) = 0;
  }
  return (char)BaseControlWorkData;
}

// 0x19c1880
s32 evtCheckPathStat(dds3Basic_t *obj) {
  dds3Basic_t *ControlBasic;
  dds3Basic_t *v4;
  s32 Mode;
  f32 v6;
  dds3PathBasicControl_t *pControl;
  dds3Basic_t *pObjectBasic;

  pObjectBasic = obj;
  if (!obj)
    return -1;
  ControlBasic = dds3ObjectBaseGetControlBasic(pObjectBasic, 1u);
  if (!ControlBasic)
    return -1;
  v4 = ControlBasic;
  pControl = dds3MoverBasicGetPathControl(ControlBasic);
  if (!pControl)
    return -1;
  Mode = dds3PathBasicPathControlGetMode(pControl);
  if (Mode)
  {
    if (Mode == 1)
    {
      v6 = 0.0;
      return dds3PathBasicControlGetRatio(pControl) != v6;
    }
    return -1;
  }
  v6 = 1.0;
  return dds3PathBasicControlGetRatio(pControl) != v6;
}

// 0x19c19d0
void evtPathLoop(dds3Basic_t *basic, bool sw) {
  dds3PathBasicControl_t *PathControl;
  dds3Basic_t *pObjectBasic;

  pObjectBasic = basic;
  PathControl = dds3ObjectBaseGetPathControl(pObjectBasic);
  if (PathControl)
  {
    if (sw)
    {
      dds3PathBasicLoopOn(PathControl);
    }
    else
    {
      dds3PathBasicLoopOff(PathControl);
    }
  }
}

// 0x19c1a80
dds3Basic_t *evtAddCamera(const sdfVector4_t *eye, const sdfVector4_t *rot) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  f32 v7;
  f32 v8;
  f32 v9;
  f32 v10;
  u32 v12;
  dds3Basic_t *result;
  dds3Basic_t *pBasic;
  sdfVector4_t v16;
  sdfVector4_t v17;

  w = rot->w;
  z = rot->z;
  y = rot->y;
  x = rot->x;
  v7 = eye->w;
  v8 = eye->z;
  v9 = eye->y;
  v10 = eye->x;
  v12 = dds3SerializeID();
  v16.x = v10;
  v16.y = v9;
  v16.z = v8;
  v16.w = v7;
  v17.x = x;
  v17.y = y;
  v17.z = z;
  v17.w = w;
  result = dds3CameraObjectBasicAddTypeFree(v12, v16, v17);
  pBasic = result;
  if (result)
  {
    dds3SetRadiusPoseSet(pBasic, 1.0);
    return pBasic;
  }
  return result;
}

// 0x19c1bd0
void evtEffectLoopControl(dds3Basic_t *eff, bool sw) {
  effHandle_t *v5;
  void *workdata;
  u32 monitor_high;
  bool v9;
  s32 v10;
  effHandle_t *klass;

  v5 = Allocate(effHandle_t);
  _ctor(v5, 0);
  workdata = eff->workdata;
  monitor_high = HIDWORD(workdata[1].monitor);
  v9 = monitor_high > 8;
  v10 = (1 << monitor_high) & 0x182;
  if (!v9 && v10 != 0)
  {
    klass = workdata[2].klass;
    if (!sw)
    {
      dds3EffectSetLoop(klass, 0);
    }
  }
}

// 0x19c1d20
s32 evtStageAnimeControl(s32 type, s32 mode) {
  dds3Basic_t *ActiveScene;
  void *workdata;
  s32 v9;
  dds3Basic_t *pObjectBasic;

  ActiveScene = dds3GetActiveScene();
  if (!ActiveScene)
    return (s32)ActiveScene;
  workdata = ActiveScene->workdata;
  pObjectBasic = *(dds3Basic_t *)(*((u64 *)workdata[1].monitor + 10) + 24);
  if (pObjectBasic)
  {
    v9 = 3 * type + mode;
    do
    {
      dds3ObjectBaseMatterAnimeSpeed(pObjectBasic, v9);
      pObjectBasic = pObjectBasic->next;
    }
    while (pObjectBasic);
  }
  LODWORD(ActiveScene) = 1;
  return (s32)ActiveScene;
}

// 0x19c1e50
static void Vu0SubVectorXZAxis(const sdfVector4_t *a, const sdfVector4_t *b) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  f32 v7;
  f32 v8;
  f32 v9;
  f32 v10;
  f32 *p_x;
  f32 *v14;

  w = b->w;
  z = b->z;
  y = b->y;
  x = b->x;
  v7 = a->w;
  v8 = a->z;
  v9 = a->y;
  v10 = a->x;
  p_x = &vf00.x;
  p_x[4] = v10;
  p_x[5] = v9;
  p_x[6] = v8;
  p_x[7] = v7;
  v14 = &vf00.x;
  v14[8] = x;
  v14[9] = y;
  v14[10] = z;
  v14[11] = w;
  vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  vct_A.y = 0.0;
}

// 0x19c2050
static void GetUnitDirVector(evtUnitHandle_t *h) {
  struct sdfVector4_t rot;
  sdfVector4_t Row;

  rot = h->Owner->poseset->rot;
  vct_A = rot;
  ToMatrix();
  Row = GetRow(&mtx_A, 2, 0);
  vct_A.x = Row.x;
  vct_A.y = 0.0;
  vct_A.z = Row.z;
  vct_A.w = 1.0;
  sub_1949110(0);
  vct_A = (struct sdfVector4_t)vnegq_f32((float32x4_t)vct_A);
}

// 0x19c2250
static bool CheckMoveEnd(evtUnitHandle_t *h) {
  u32 MoveType;
  f32 Ratio;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  dds3PoseSet_t *poseset;
  f32 v10;
  f32 v11;
  f32 v12;
  f32 v13;
  f32 *p_x;
  f32 v16;
  f32 v17;
  f32 v18;

  MoveType = (u16)h->MoveType;
  if (MoveType < 3)
  {
    x = h->PosTarget.x;
    y = h->PosTarget.y;
    z = h->PosTarget.z;
    w = h->PosTarget.w;
    poseset = h->Owner->poseset;
    v10 = poseset->pos.x;
    v11 = poseset->pos.y;
    v13 = poseset->pos.z;
    v12 = poseset->pos.w;
    (loc_19D0380)(0, x, y, z, w, v10, v11, v13, v12);
    p_x = &vf00.x;
    v16 = p_x[6];
    v17 = p_x[4];
    v18 = p_x[5];
    return sqrtf((f32)((f32)(v17 * v17) + (f32)(v18 * v18)) + (f32)(v16 * v16)) <= 20.0;
  }
  if (MoveType != 3)
    return 0;
  Ratio = dds3PathBasicControlGetRatio(&h->Path);
  if ((h->Flag & 4) == 0)
    return Ratio == 1.0;
  return Ratio == 0.0;
}

// 0x19c24a0
static bool GetNextMovePos(evtUnitHandle_t *h) {
  f32 Ratio;
  f32 v4;
  f32 v6;
  f32 v7;
  sdfVector4_t *p_PosTarget;

  if (h->Stat != 1 || h->TargetType != 2)
    return 0;
  Ratio = dds3PathBasicControlGetRatio(&h->Path);
  v4 = 1.0;
  if ((h->Flag & 4) != 0)
  {
    if (Ratio == 0.0)
      return 0;
    goto LABEL_11;
  }
  if (Ratio == v4)
    return 0;
LABEL_11:
  v6 = Ratio + h->PathStep;
  if (v6 < 0.0)
    v6 = 0.0;
  if (v6 <= v4)
    v7 = v6;
  else
    v7 = v4;
  dds3PathBasicControlSetRatio(&h->Path, v7);
  dds3PathBasicControlGetPos(&h->Path);
  p_PosTarget = &h->PosTarget;
  *p_PosTarget = vct_A;
  return 1;
}

// 0x19c2650
static f32 GetSplineLength(dds3PathBasicControl_t *path) {
  f32 Ratio;
  f32 v4;
  f32 v6;
  f32 *p_x;
  f32 x;
  f32 y;
  f32 z;

  Ratio = dds3PathBasicControlGetRatio(path);
  v4 = 0.0;
  dds3PathBasicControlSetRatio(path, 0.0);
  dds3PathBasicControlGetPos(path);
  v6 = 0.05;
  do
  {
    vct_B = vct_A;
    dds3PathBasicControlSetRatio(path, v6);
    dds3PathBasicControlGetPos(path);
    vct_C = vct_A;
    vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    p_x = &vf00.x;
    x = p_x[4];
    y = p_x[5];
    z = p_x[6];
    v4 = v4 + sqrtf((f32)((f32)(x * x) + (f32)(y * y)) + (f32)(z * z));
    vct_A = vct_C;
    v6 = v6 + 0.05;
  }
  while (v6 <= 1.0);
  dds3PathBasicControlSetRatio(path, Ratio);
  return v4;
}

// 0x19c29e0
void UnitAnime(evtUnitHandle_t *h) {
  u32 v3;
  s32 Flag;
  f32 dissolveAlphaMove;
  s32 v7;
  f32 v8;
  struct sdfVector4_t v10;
  f32 v11;
  f32 v12;
  f32 *v13;
  f32 v14;
  f32 v15;
  f32 v16;
  dds3ModelHandle_t *v17;
  u32 ModelRGBAnimeFrame;
  s32 v19;
  f32 v20;
  struct sdfVector4_t BaseModelRGBA;
  f32 v23;
  f32 v24;
  dds3ModelHandle_t *Model;
  f32 w;
  u32 ModelAAnimeFrame;
  f32 v28;
  f32 v29;
  dds3ModelHandle_t *v30;
  dds3Basic_t *BasicLight;
  dds3Basic_t *p_BasicLight2;
  dds3Basic_t *v33;
  dds3Basic_t *v34;
  f32 x;
  f32 *v36;
  f32 y;
  s32 v38;
  f32 z;
  f32 v40;
  f32 v41;
  s32 v42;
  f32 v43;
  f32 *workdata;
  void *v46;
  Project_Basic_dds3Basic_t_WORK_c *klass;
  dds3Basic_t *p_BasicLight;
  struct sdfVector4_t pos;
  f32 *p_x;
  f32 *v54;
  f32 v55;
  f32 v56;
  f32 v57;
  f32 v59;
  f32 v60;
  f32 v61;
  struct sdfVector4_t v63;
  f32 *v64;
  f32 v65;
  f32 v66;
  f32 v67;
  f32 v68;
  f32 v69;
  f32 v70;
  f32 *v73;
  s32 v74;
  u32 BasicLightAnimeMaxFrame;
  u32 BasicLightAnimeFrame;
  f32 v77;
  u16 v78;
  f32 v79;
  s32 v85;
  evtUnitHandle_t *v86;
  sdfVector4_t *p_BaseLightDir;
  struct sdfVector4_t v88;
  sdfVector4_t *p_WorkLightDir;
  s32 v93;
  sdfVector4_t *p_BaseLightDir1;
  struct sdfVector4_t BaseLightDir1;
  struct sdfVector4_t TargetLightDir1;
  struct sdfVector4_t v98;
  sdfVector4_t *p_WorkLightDir1;
  s32 v103;
  sdfVector4_t *p_BaseLightDir2;
  struct sdfVector4_t BaseLightDir2;
  struct sdfVector4_t TargetLightDir2;
  struct sdfVector4_t v108;
  sdfVector4_t *p_WorkLightDir2;
  s32 LightDirAnimeFrame;
  s32 v114;
  sdfVector4_t *v116;
  sdfVector4_t *v118;
  dds3ModelHandle_t *v119;
  f32 v122;
  sdf3DLight_t *v124;
  evtUnitHandle_t *v126;
  sdfVector4_t *v127;
  sdfVector4_t *v132;
  sdfVector4_t *v136;
  bool v137;
  evtUnitHandle_t *v138;
  s32 v139;
  f32 *v141;
  struct sdfVector4_t v143;
  struct sdfVector4_t v150;
  int8x16_t *p_NowLightDir;
  int8x16_t WorkLightDir1;
  s32 v158;
  f32 v159;
  struct sdfVector4_t WorkLightDir;
  struct sdfVector4_t WorkLightDir2;
  sdf3DLight_t *v163;
  struct sdfVector4_t v165;
  u32 BaseLightRGB;
  int8x16_t v169;
  uint32x4_t v170;
  float32x4_t v171;
  int8x16_t *v172;
  int8x16_t v173;
  struct sdfVector4_t color;
  u32 TargetLightRGB;
  int8x16_t v179;
  uint32x4_t v180;
  float32x4_t v181;
  float32x4_t *v183;
  float32x4_t v184;
  f32 *v185;
  u32 BaseLightRGB1;
  f32 v187;
  f32 v188;
  f32 v189;
  f32 v190;
  u8 v191;
  u8 v192;
  u32 v193;
  u8 v194;
  u8 v195;
  f32 v196;
  u32 v197;
  u8 v198;
  u8 v199;
  f32 v200;
  s32 v201;
  s32 v202;
  int8x16_t v203;
  uint32x4_t v204;
  float32x4_t v205;
  int8x16_t *v206;
  int8x16_t v207;
  struct sdfVector4_t v209;
  u32 TargetLightRGB1;
  int8x16_t v213;
  uint32x4_t v214;
  float32x4_t v215;
  float32x4_t *v217;
  float32x4_t v218;
  evtUnitHandle_t *v219;
  f32 *v220;
  u32 BaseLightRGB2;
  f32 v222;
  f32 v223;
  f32 v224;
  f32 v225;
  u8 v226;
  u8 v227;
  u32 v228;
  u8 v229;
  u8 v230;
  f32 v231;
  u32 v232;
  u8 v233;
  u8 v234;
  f32 v235;
  s32 v236;
  s32 v237;
  int8x16_t v238;
  uint32x4_t v239;
  float32x4_t v240;
  int8x16_t *v241;
  int8x16_t v242;
  struct sdfVector4_t v244;
  u32 TargetLightRGB2;
  int8x16_t v249;
  uint32x4_t v250;
  float32x4_t v251;
  float32x4_t *v253;
  float32x4_t v254;
  f32 *v255;
  u32 BaseAmbientRGB;
  f32 v257;
  f32 v258;
  f32 v259;
  f32 v260;
  u8 v261;
  u8 v262;
  u32 v263;
  u8 v264;
  u8 v265;
  f32 v266;
  u32 v267;
  u8 v268;
  u8 v269;
  f32 v270;
  s32 v271;
  s32 v272;
  int8x16_t v273;
  uint32x4_t v274;
  float32x4_t v275;
  int8x16_t *v276;
  int8x16_t v277;
  struct sdfVector4_t Ambient_local;
  u32 TargetAmbientRGB;
  int8x16_t v283;
  uint32x4_t v284;
  float32x4_t v285;
  float32x4_t *v287;
  f32 *v288;
  f32 v289;
  f32 v290;
  f32 v291;
  f32 v292;
  u8 v293;
  u8 v294;
  u8 v295;
  u8 v296;
  u32 v297;
  u8 v298;
  u32 v299;
  u8 v300;
  s32 v301;
  s32 LightRGBAnimeFrame;
  u32 v303;
  evtUnitHandle_t *v304;
  u32 v305;
  u32 WorkLightRGB1;
  u32 WorkLightRGB2;
  void *Instance;
  s32 v310;
  f32 v314;
  f32 v315;
  u32 v316;
  bool v317;
  u32 v318;
  f32 v319;
  u8 v320;
  u8 v321;
  float32x2_t v322;
  float32x2_t v323;
  int32x2_t v324;
  uint32x2_t v325;
  int32x2_t v326;
  u64 v327;
  f32 v332;
  f32 v333;
  u32 v334;
  u32 v335;
  u8 v336;
  u8 v337;
  float32x2_t v338;
  float32x2_t v339;
  int32x2_t v340;
  uint32x2_t v341;
  int32x2_t v342;
  u64 v343;
  f32 v347;
  f32 v348;
  u32 v349;
  u32 v350;
  u8 v351;
  u8 v352;
  float32x2_t v353;
  float32x2_t v354;
  int32x2_t v355;
  uint32x2_t v356;
  int32x2_t v357;
  u64 v358;
  f32 v363;
  f32 v364;
  u32 v365;
  u32 v366;
  u8 v367;
  u8 v368;
  float32x2_t v369;
  float32x2_t v370;
  int32x2_t v371;
  uint32x2_t v372;
  int32x2_t v373;
  u64 v374;
  u32 WorkLightRGB;
  int8x16_t v377;
  uint32x4_t v378;
  float32x4_t v379;
  struct sdfVector4_t v380;
  float32x4_t *v381;
  float32x4_t v382;
  u32 v383;
  int8x16_t v384;
  int8x16_t v385;
  uint32x4_t v386;
  float32x4_t v387;
  f32 v388;
  struct sdfVector4_t v389;
  f32 v390;
  float32x4_t *v391;
  u32 WorkAmbientRGB;
  f32 v395;
  f32 v396;
  u32 v397;
  u32 v398;
  u8 v399;
  u8 v400;
  float32x2_t v401;
  float32x2_t v402;
  int32x2_t v403;
  uint32x2_t v404;
  u64 v405;
  int8x16_t v406;
  uint32x4_t v407;
  float32x4_t v408;
  struct sdfVector4_t v409;
  u32 v410;
  int8x16_t v411;
  int8x16_t v412;
  uint32x4_t v413;
  float32x4_t v414;
  f32 v415;
  struct sdfVector4_t v416;
  f32 v417;
  f32 v420;
  f32 v421;
  u32 v422;
  u32 v423;
  u8 v424;
  u8 v425;
  float32x2_t v426;
  float32x2_t v427;
  int32x2_t v428;
  uint32x2_t v429;
  int32x2_t v430;
  u64 v431;
  struct sdfVector4_t v433;
  dds3Basic_t *target;
  void *targeth[2];
  void *targeti[2];
  void *targetn[2];
  void *targeto[2];
  void *targeta[2];
  void *targetb[2];
  void *targetc[2];
  void *targetd[2];
  void *targete[2];
  f32 v460;
  struct sdfVector4_t v461;
  struct sdfVector4_t v462;
  f32 v463;
  struct sdfVector4_t v464;
  f32 v467;
  f32 aRatio;
  void *object;
  struct sdfVector4_t v470;
  struct sdfVector4_t TargetModelRGBA;
  struct sdfVector4_t BaseLightDir;
  struct sdfVector4_t v;
  struct sdfVector4_t v484;
  struct sdfVector4_t v485;
  struct sdfVector4_t v486;
  struct sdfVector4_t v487;
  struct sdfVector4_t v488;
  struct sdfVector4_t v489;
  f32 v490;
  struct sdfVector4_t v491;
  struct sdfVector4_t v492;
  struct sdfVector4_t v493;
  f32 v494;
  f32 v499;
  f32 v500;
  f32 *v501;
  struct sdfVector4_t v505;
  dds3Basic_t *ActiveScene;
  dds3Basic_t *scene;
  s64 pBias;
  evtUnitHandle_t *ha;
  sdfMatrix4_t v512;
  sdfMatrix4_t v513;
  sdfVector4_t v514;
  sdfVector4_t v515;
  sdfVector4_t v516;
  sdfVector4_t v517;
  sdfVector4_t v518;
  sdfVector4_t v519;
  sdfVector4_t v520;
  sdfVector4_t v521;
  sdfVector4_t v522;
  sdfVector4_t v523;
  sdfVector4_t v524;
  sdfVector4_t v525;
  sdfVector4_t v526;

  ha = h;
  ActiveScene = 0;
  scene = 0;
  pBias = 0;
  if (h)
  {
    Flag = h->Flag;
    if ((Flag & 0x8000) == 0)
    {
      if ((Flag & 0x10000) == 0)
        goto LABEL_6;
LABEL_31:
      if (h->ModelAAnimeMaxFrame)
      {
        LOWORD(v3) = h->ModelAAnimeFrame;
        v20 = (f32)v3 / (f32)h->ModelAAnimeMaxFrame;
      }
      else
      {
        v20 = 1.0;
      }
      v500 = v20;
      TargetModelRGBA = h->TargetModelRGBA;
      vct_B = TargetModelRGBA;
      BaseModelRGBA = h->BaseModelRGBA;
      v23 = 1.0;
      vct_A = BaseModelRGBA;
      v24 = v23 - v500;
      vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v24);
      vct_B = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_B, v500);
      vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
      Model = h->Model;
      w = vct_A.w;
      mdlSetDitherAlpha(Model, w);
      ModelAAnimeFrame = h->ModelAAnimeFrame;
      if (ModelAAnimeFrame >= h->ModelAAnimeMaxFrame)
      {
        h->Flag &= ~0x10000u;
        dissolveAlphaMove = h->dissolveAlphaMove;
        if (dissolveAlphaMove != 0.0)
          goto LABEL_66;
      }
      else
      {
        h->ModelAAnimeFrame = ModelAAnimeFrame + 1;
        dissolveAlphaMove = h->dissolveAlphaMove;
        if (dissolveAlphaMove != 0.0)
          goto LABEL_66;
      }
LABEL_7:
      v7 = h->Flag;
      if ((v7 & 0x40000) == 0)
        goto LABEL_95;
LABEL_87:
      if (!h->BasicLight)
      {
LABEL_94:
        h->Flag = v7 & 0xFFFBFFFF;
        goto LABEL_95;
      }
      scene = dds3GetActiveScene();
      BasicLight = h->BasicLight;
      if (!dds3SceneBasicExistBasicFromType(scene, 9, BasicLight))
      {
        h->BasicLight = 0;
        h->BasicLight2 = 0;
        v7 = h->Flag;
        goto LABEL_94;
      }
LABEL_95:
      p_BasicLight2 = &h->BasicLight2;
      if (h->BasicLight2)
      {
        ActiveScene = dds3GetActiveScene();
        v33 = p_BasicLight2;
        if (dds3SceneBasicExistBasicFromType(ActiveScene, 9, v33))
          goto LABEL_101;
        goto LABEL_100;
        if (!dds3SceneBasicExistBasicFromType(ActiveScene, 9, p_BasicLight2))
        {
LABEL_100:
          p_BasicLight2 = 0;
        }
      }
LABEL_101:
      v34 = h->BasicLight;
      x = 0.0;
      if (!v34 || (h->Flag & 0x40000) == 0)
      {
        v461 = (struct sdfVector4_t)0;
        v36 = 0;
        y = 0.0;
        object = 0;
        v38 = 1;
        z = 0.0;
        v40 = 0.0;
        v41 = 0.0;
        v460 = 0.0;
        goto LABEL_104;
      }
      workdata = v34->workdata;
      if (p_BasicLight2)
      {
        v46 = p_BasicLight2->workdata;
        if (v46)
        {
          object = p_BasicLight2->workdata;
          klass = v46->klass;
          if (sdfModelGetMarkPos(h->Model->modelRoot, 0))
          {
LABEL_115:
            goto LABEL_116;
          }
        }
        else
        {
          object = 0;
          if (sdfModelGetMarkPos(h->Model->modelRoot, 0))
            goto LABEL_115;
        }
      }
      else
      {
        object = 0;
        if (sdfModelGetMarkPos(h->Model->modelRoot, 0))
          goto LABEL_115;
      }
      v119 = h->Model;
      mdlGetPosition(v119);
LABEL_116:
      p_BasicLight = &h->BasicLight;
      pos = p_BasicLight->poseset->pos;
      vct_B = pos;
      vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
      target = p_BasicLight;
      p_x = &vf00.x;
      x = p_x[4];
      y = p_x[5];
      z = p_x[6];
      v40 = p_x[7];
      v54 = &vf00.x;
      v55 = v54[6];
      v56 = v54[4];
      v57 = v54[5];
      v59 = workdata[10];
      v60 = sqrtf((f32)((f32)(v56 * v56) + (f32)(v57 * v57)) + (f32)(v55 * v55));
      if (v60 <= v59)
      {
        v41 = 1.0;
        v460 = 0.0;
        if (object)
          goto LABEL_132;
      }
      else
      {
        v61 = workdata[11];
        v41 = 0.0;
        if (v60 < v61)
          v41 = 1.0 - (f32)((f32)(v60 - v59) / (f32)(v61 - v59));
        v460 = 0.0;
        if (object)
        {
LABEL_132:
          v63 = p_BasicLight2->poseset->pos;
          vct_B = v63;
          vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
          v461 = vct_A;
          v64 = &vf00.x;
          v36 = workdata;
          v65 = v64[4];
          v66 = v64[5];
          v67 = v64[6];
          v68 = *(f32 *)&object[2].monitor;
          v69 = sqrtf((f32)((f32)(v65 * v65) + (f32)(v66 * v66)) + (f32)(v67 * v67));
          if (v69 <= v68)
          {
            v460 = 1.0;
            vct_A.x = x;
            vct_A.y = y;
            vct_A.z = z;
            vct_A.w = v40;
            if (((u8)v36[15] & 8) != 0)
            {
LABEL_289:
              v116 = *((sdfVector4_t *)v36 + 2);
              v118 = v116 + 2;
              v38 = 0;
              *v118 = vct_A;
LABEL_104:
              aRatio = 0.0;
              v42 = h->Flag;
              v501 = v36;
              if ((v42 & 0x6000) != 0)
                goto LABEL_105;
              goto LABEL_333;
            }
LABEL_155:
            v74 = h->Flag;
            if ((v74 & 0x180000) != 0)
            {
              BasicLightAnimeMaxFrame = h->BasicLightAnimeMaxFrame;
              if (h->BasicLightAnimeMaxFrame)
              {
                BasicLightAnimeFrame = h->BasicLightAnimeFrame;
                v77 = BasicLightAnimeFrame;
                v78 = BasicLightAnimeFrame + 1;
                h->BasicLightAnimeFrame = v78;
                v79 = v77 / (f32)BasicLightAnimeMaxFrame;
                if ((v74 & 0x100000) != 0)
                  v79 = 1.0 - v79;
                aRatio = v79;
                if (BasicLightAnimeMaxFrame <= v78)
                {
                  if ((v74 & 0x100000) != 0)
                  {
                    h->Flag = v74 & 0xFFFBFFFF;
                    h->BasicLight = 0;
                    v74 = h->Flag;
                  }
                  h->BasicLight2 = 0;
                  h->Flag = v74 & 0xFFE7FFFF;
                }
LABEL_332:
                v38 = 1;
                v42 = h->Flag;
                v501 = v36;
                if ((v42 & 0x6000) != 0)
                {
LABEL_105:
                  if (h->LightDirAnimeFrame)
                    v43 = 1.0 / (f32)h->LightDirAnimeFrame;
                  else
                    v43 = 1.0;
                  BaseLightDir = h->BaseLightDir;
                  vct_A = BaseLightDir;
                  if ((h->Flag & 0x2000) == 0)
                  {
                    if ((v38 & 1) != 0)
                    {
                      v = DirLights[0]->v;
                    }
                    else
                    {
                      v = *(sdfVector4_t *)(*((u64 *)v36 + 2) + 32);
                    }
LABEL_180:
                    vct_B = v;
                    dds3RotationArc();
                    vct_B = vct_A;
                    v85 = v38;
                    vct_A = (struct sdfVector4_t)xmmword_3CFD5C0;
                    Lerp(v43);
                    ToMatrix();
                    v86 = ha;
                    p_BaseLightDir = &ha->BaseLightDir;
                    v88 = ha->BaseLightDir;
                    vct_A = v88;
                    get_transpose(&v513, &mtx_A, 0);
                    v520 = vct_A;
                    v512 = v513;
                    v514 = op_Multiply_60923920(&v512, v520, 0);
                    vct_A = v514;
                    p_WorkLightDir = &v86->WorkLightDir;
                    *p_WorkLightDir = vct_A;
                    v93 = (u8)byte_5755EF5;
                    *p_BaseLightDir = vct_A;
                    p_BaseLightDir1 = &v86->BaseLightDir1;
                    BaseLightDir1 = v86->BaseLightDir1;
                    if (v93)
                    {
                      goto LABEL_213;
                    }
                    else
                    {
                      *(sdfVector4_t *)targeth = v86->BaseLightDir1;
                      BaseLightDir1 = *(sdfVector4_t *)targeth;
LABEL_213:
                      vct_A = BaseLightDir1;
                      TargetLightDir1 = v86->TargetLightDir1;
                      goto LABEL_214;
                    }
                    *(sdfVector4_t *)targeti = BaseLightDir1;
                    vct_A = *(sdfVector4_t *)targeti;
                    TargetLightDir1 = v86->TargetLightDir1;
LABEL_214:
                    vct_B = TargetLightDir1;
                    dds3RotationArc();
                    vct_B = vct_A;
                    vct_A = (struct sdfVector4_t)xmmword_3CFD5C0;
                    Lerp(v43);
                    ToMatrix();
                    v98 = *p_BaseLightDir1;
                    vct_A = v98;
                    get_transpose(&v513, &mtx_A, 0);
                    v521 = vct_A;
                    v512 = v513;
                    v515 = op_Multiply_60923920(&v512, v521, 0);
                    vct_A = v515;
                    p_WorkLightDir1 = &v86->WorkLightDir1;
                    *p_WorkLightDir1 = vct_A;
                    v103 = (u8)byte_5755EF5;
                    *p_BaseLightDir1 = vct_A;
                    p_BaseLightDir2 = &v86->BaseLightDir2;
                    BaseLightDir2 = v86->BaseLightDir2;
                    if (v103)
                    {
                      goto LABEL_245;
                    }
                    else
                    {
                      *(sdfVector4_t *)targetn = v86->BaseLightDir2;
                      BaseLightDir2 = *(sdfVector4_t *)targetn;
LABEL_245:
                      vct_A = BaseLightDir2;
                      TargetLightDir2 = v86->TargetLightDir2;
                      goto LABEL_246;
                    }
                    *(sdfVector4_t *)targeto = BaseLightDir2;
                    vct_A = *(sdfVector4_t *)targeto;
                    TargetLightDir2 = v86->TargetLightDir2;
LABEL_246:
                    vct_B = TargetLightDir2;
                    dds3RotationArc();
                    vct_B = vct_A;
                    vct_A = (struct sdfVector4_t)xmmword_3CFD5C0;
                    Lerp(v43);
                    ToMatrix();
                    v108 = *p_BaseLightDir2;
                    vct_A = v108;
                    get_transpose(&v513, &mtx_A, 0);
                    v522 = vct_A;
                    v512 = v513;
                    v516 = op_Multiply_60923920(&v512, v522, 0);
                    vct_A = v516;
                    p_WorkLightDir2 = &v86->WorkLightDir2;
                    *p_WorkLightDir2 = vct_A;
                    v38 = v85;
                    v36 = v501;
                    LightDirAnimeFrame = v86->LightDirAnimeFrame;
                    *p_BaseLightDir2 = vct_A;
                    if (LightDirAnimeFrame)
                    {
                      v86->LightDirAnimeFrame = LightDirAnimeFrame - 1;
                    }
                    else
                    {
                      v114 = v86->Flag;
                      if ((v114 & 0x4000) != 0)
                        v114 &= 0xFFFF9BFF;
                      v86->Flag = v114 & 0xFFFF9FFF;
                    }
LABEL_381:
                    v137 = v36 == 0;
                    v138 = ha;
                    if (v137)
                      v139 = 0;
                    else
                      v139 = v38;
                    if (v139 != 1)
                    {
                      WorkLightDir = ha->WorkLightDir;
                      v488 = ha->WorkLightDir;
                      WorkLightDir = v488;
                      v138->NowLightDir = WorkLightDir;
                      WorkLightDir1 = v138->WorkLightDir1;
                      WorkLightDir2 = v138->WorkLightDir2;
                      v138->NowLightDir1 = (struct sdfVector4_t)WorkLightDir1;
                      v138->NowLightDir2 = WorkLightDir2;
                      v158 = v138->Flag;
                      if ((v158 & 0x1800) != 0)
                      {
LABEL_433:
                        if (v138->LightRGBAnimeFrame)
                          v159 = 1.0 / (f32)v138->LightRGBAnimeFrame;
                        else
                          v159 = 1.0;
                        v490 = v159;
                        BaseLightRGB = v138->BaseLightRGB;
                        WorkLightDir1.n128_u32[0] = BaseLightRGB;
                        v169.n128_u64[0] = 0xFF000000FFLL;
                        v169.n128_u64[1] = 0xFF000000FFLL;
                        WorkLightDir1.n128_u32[1] = BaseLightRGB >> 8;
                        WorkLightDir1.n128_u32[2] = HIWORD(BaseLightRGB);
                        v170 = vandq_s8(WorkLightDir1, v169);
                        v170.n128_u32[3] = vshrq_n_u32(vdupq_n_s32(BaseLightRGB), 0x18u).n128_u32[3];
                        v171.n128_u64[0] = 0x3C0000003C000000LL;
                        v171.n128_u64[1] = 0x3C0000003C000000LL;
                        vct_A = (struct sdfVector4_t)vmulq_f32(vcvtq_f32_u32(v170), v171);
                        v463 = 1.0 - v490;
                        vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v463);
                        v173 = v172[1];
                        v172[2] = v173;
                        if ((v138->Flag & 0x800) == 0)
                        {
                          if ((v38 & 1) != 0)
                          {
                            color = DirLights[0]->color;
                            *(sdfVector4_t *)targetb = color;
LABEL_499:
                            vct_A = color;
LABEL_502:
                            vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v490);
                            v184 = vaddq_f32(v183[1], v183[2]);
                            v183[1] = v184;
                            vct_A.w = 0.0;
                            v185 = &vf00.x;
                            BaseLightRGB1 = v138->BaseLightRGB1;
                            v187 = v185[4];
                            v188 = v185[5];
                            v189 = v185[6];
                            v190 = v185[7];
                            v191 = vcvts_n_s32_f32(v188, 7u);
                            v192 = vcvts_n_u32_f32(v188, 7u);
                            v193 = vcvts_n_s32_f32(v190, 7u);
                            v194 = vcvts_n_s32_f32(v189, 7u);
                            v195 = vcvts_n_u32_f32(v189, 7u);
                            v196 = v189 * 128.0;
                            v197 = vcvts_n_u32_f32(v190, 7u);
                            if ((f32)(v188 * 128.0) >= 0.0)
                              v191 = v192;
                            v198 = vcvts_n_s32_f32(v187, 7u);
                            if (v196 >= 0.0)
                              v194 = v195;
                            v199 = vcvts_n_u32_f32(v187, 7u);
                            v200 = v187 * 128.0;
                            if ((f32)(v190 * 128.0) >= 0.0)
                              v193 = v197;
                            if (v200 >= 0.0)
                              v198 = v199;
                            v201 = v198
                                 | (v193 << 24)
                                 | (u16)(v191 << 8)
                                 | (v194 << 16);
                            v202 = (u8)byte_57564C4;
                            v138->BaseLightRGB = v201;
                            v138->WorkLightRGB = v201;
                            if (v202)
                            {
                              goto LABEL_520;
                            }
                            else
                            {
                              goto LABEL_520;
                            }
LABEL_520:
                            v184.n128_u32[0] = BaseLightRGB1;
                            v203.n128_u64[0] = 0xFF000000FFLL;
                            v203.n128_u64[1] = 0xFF000000FFLL;
                            v184.n128_u32[1] = BaseLightRGB1 >> 8;
                            v184.n128_u32[2] = HIWORD(BaseLightRGB1);
                            v204 = vandq_s8(v184, v203);
                            v204.n128_u32[3] = vshrq_n_u32(vdupq_n_s32(BaseLightRGB1), 0x18u).n128_u32[3];
                            v205.n128_u64[0] = 0x3C0000003C000000LL;
                            v205.n128_u64[1] = 0x3C0000003C000000LL;
                            vct_A = (struct sdfVector4_t)vmulq_f32(vcvtq_f32_u32(v204), v205);
                            vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v463);
                            v207 = v206[1];
                            v206[2] = v207;
                            if ((v138->Flag & 0x800) == 0)
                            {
                              if ((v38 & 1) != 0)
                              {
                                v209 = DirLights[1]->color;
                                *(sdfVector4_t *)targetc = v209;
LABEL_551:
                                vct_A = v209;
LABEL_554:
                                vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v490);
                                v218 = vaddq_f32(v217[1], v217[2]);
                                v217[1] = v218;
                                vct_A.w = 0.0;
                                v219 = ha;
                                v220 = &vf00.x;
                                BaseLightRGB2 = v219->BaseLightRGB2;
                                v222 = v220[4];
                                v223 = v220[5];
                                v224 = v220[6];
                                v225 = v220[7];
                                v226 = vcvts_n_s32_f32(v223, 7u);
                                v227 = vcvts_n_u32_f32(v223, 7u);
                                v228 = vcvts_n_s32_f32(v225, 7u);
                                v229 = vcvts_n_s32_f32(v224, 7u);
                                v230 = vcvts_n_u32_f32(v224, 7u);
                                v231 = v224 * 128.0;
                                v232 = vcvts_n_u32_f32(v225, 7u);
                                if ((f32)(v223 * 128.0) >= 0.0)
                                  v226 = v227;
                                v233 = vcvts_n_s32_f32(v222, 7u);
                                if (v231 >= 0.0)
                                  v229 = v230;
                                v234 = vcvts_n_u32_f32(v222, 7u);
                                v235 = v222 * 128.0;
                                if ((f32)(v225 * 128.0) >= 0.0)
                                  v228 = v232;
                                if (v235 >= 0.0)
                                  v233 = v234;
                                v236 = v233
                                     | (v228 << 24)
                                     | (u16)(v226 << 8)
                                     | (v229 << 16);
                                v237 = (u8)byte_57564C4;
                                v219->BaseLightRGB1 = v236;
                                v219->WorkLightRGB1 = v236;
                                if (v237)
                                {
                                  goto LABEL_572;
                                }
                                else
                                {
                                  goto LABEL_572;
                                }
LABEL_572:
                                v218.n128_u32[0] = BaseLightRGB2;
                                v238.n128_u64[0] = 0xFF000000FFLL;
                                v238.n128_u64[1] = 0xFF000000FFLL;
                                v218.n128_u32[1] = BaseLightRGB2 >> 8;
                                v218.n128_u32[2] = HIWORD(BaseLightRGB2);
                                v239 = vandq_s8(v218, v238);
                                v239.n128_u32[3] = vshrq_n_u32(vdupq_n_s32(BaseLightRGB2), 0x18u).n128_u32[3];
                                v240.n128_u64[0] = 0x3C0000003C000000LL;
                                v240.n128_u64[1] = 0x3C0000003C000000LL;
                                vct_A = (struct sdfVector4_t)vmulq_f32(vcvtq_f32_u32(v239), v240);
                                vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v463);
                                v242 = v241[1];
                                v241[2] = v242;
                                if ((v219->Flag & 0x800) == 0)
                                {
                                  if ((v38 & 1) != 0)
                                  {
                                    v244 = DirLights[2]->color;
                                    *(sdfVector4_t *)targetd = v244;
LABEL_603:
                                    vct_A = v244;
LABEL_606:
                                    vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v490);
                                    v254 = vaddq_f32(v253[1], v253[2]);
                                    v253[1] = v254;
                                    vct_A.w = 0.0;
                                    v255 = &vf00.x;
                                    BaseAmbientRGB = v219->BaseAmbientRGB;
                                    v257 = v255[4];
                                    v258 = v255[5];
                                    v259 = v255[6];
                                    v260 = v255[7];
                                    v261 = vcvts_n_s32_f32(v258, 7u);
                                    v262 = vcvts_n_u32_f32(v258, 7u);
                                    v263 = vcvts_n_s32_f32(v260, 7u);
                                    v264 = vcvts_n_s32_f32(v259, 7u);
                                    v265 = vcvts_n_u32_f32(v259, 7u);
                                    v266 = v259 * 128.0;
                                    v267 = vcvts_n_u32_f32(v260, 7u);
                                    if ((f32)(v258 * 128.0) >= 0.0)
                                      v261 = v262;
                                    v268 = vcvts_n_s32_f32(v257, 7u);
                                    if (v266 >= 0.0)
                                      v264 = v265;
                                    v269 = vcvts_n_u32_f32(v257, 7u);
                                    v270 = v257 * 128.0;
                                    if ((f32)(v260 * 128.0) >= 0.0)
                                      v263 = v267;
                                    if (v270 >= 0.0)
                                      v268 = v269;
                                    v271 = v268 | (v263 << 24) | (u16)(v261 << 8) | (v264 << 16);
                                    v272 = (u8)byte_57564C4;
                                    v219->BaseLightRGB2 = v271;
                                    v219->WorkLightRGB2 = v271;
                                    if (v272)
                                    {
                                      goto LABEL_624;
                                    }
                                    else
                                    {
                                      goto LABEL_624;
                                    }
LABEL_624:
                                    v254.n128_u32[0] = BaseAmbientRGB;
                                    v273.n128_u64[0] = 0xFF000000FFLL;
                                    v273.n128_u64[1] = 0xFF000000FFLL;
                                    v254.n128_u32[1] = BaseAmbientRGB >> 8;
                                    v254.n128_u32[2] = HIWORD(BaseAmbientRGB);
                                    v274 = vandq_s8(v254, v273);
                                    v274.n128_u32[3] = vshrq_n_u32(vdupq_n_s32(BaseAmbientRGB), 0x18u).n128_u32[3];
                                    v275.n128_u64[0] = 0x3C0000003C000000LL;
                                    v275.n128_u64[1] = 0x3C0000003C000000LL;
                                    vct_A = (struct sdfVector4_t)vmulq_f32(vcvtq_f32_u32(v274), v275);
                                    vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v463);
                                    v277 = v276[1];
                                    v276[2] = v277;
                                    if ((v219->Flag & 0x800) == 0)
                                    {
                                      if ((v38 & 1) != 0)
                                      {
                                        Ambient_local = Ambient;
                                        v464 = Ambient_local;
                                        goto LABEL_653;
                                      }
                                      else
                                      {
                                        Ambient_local = *(sdfVector4_t *)(v501 + 6);
                                        v464 = Ambient_local;
LABEL_653:
                                        vct_A = Ambient_local;
LABEL_657:
                                        vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v490);
                                        WorkLightDir1 = vaddq_f32(v287[1], v287[2]);
                                        v287[1] = WorkLightDir1;
                                        vct_A.w = 1.0;
                                        v288 = &vf00.x;
                                        v289 = v288[4];
                                        v290 = v288[5];
                                        v291 = v288[6];
                                        v292 = v288[7];
                                        v293 = vcvts_n_s32_f32(v290, 7u);
                                        v294 = vcvts_n_u32_f32(v290, 7u);
                                        v295 = vcvts_n_s32_f32(v291, 7u);
                                        if ((f32)(v290 * 128.0) >= 0.0)
                                          v293 = v294;
                                        v296 = vcvts_n_u32_f32(v291, 7u);
                                        v297 = vcvts_n_u32_f32(v292, 7u);
                                        v298 = vcvts_n_u32_f32(v289, 7u);
                                        if ((f32)(v291 * 128.0) < 0.0)
                                          v296 = v295;
                                        v299 = vcvts_n_s32_f32(v292, 7u);
                                        if ((f32)(v292 * 128.0) >= 0.0)
                                          v299 = v297;
                                        v300 = vcvts_n_s32_f32(v289, 7u);
                                        if ((f32)(v289 * 128.0) >= 0.0)
                                          v300 = v298;
                                        v301 = v300 | (v299 << 24) | (v293 << 8);
                                        LightRGBAnimeFrame = v219->LightRGBAnimeFrame;
                                        v303 = v301 & 0xFF00FFFF | (v296 << 16);
                                        v219->BaseAmbientRGB = v303;
                                        v219->WorkAmbientRGB = v303;
                                        if (LightRGBAnimeFrame)
                                        {
                                          v219->LightRGBAnimeFrame = LightRGBAnimeFrame - 1;
                                          if (!v139)
                                            goto LABEL_675;
LABEL_803:
                                          v304 = ha;
                                          WorkLightRGB = ha->WorkLightRGB;
                                          WorkLightDir1.n128_u32[0] = WorkLightRGB;
                                          v377.n128_u64[0] = 0xFF000000FFLL;
                                          v377.n128_u64[1] = 0xFF000000FFLL;
                                          WorkLightDir1.n128_u32[1] = WorkLightRGB >> 8;
                                          WorkLightDir1.n128_u32[2] = HIWORD(WorkLightRGB);
                                          v378 = vandq_s8(WorkLightDir1, v377);
                                          v378.n128_u32[3] = vshrq_n_u32(vdupq_n_s32(WorkLightRGB), 0x18u).n128_u32[3];
                                          v379.n128_u64[0] = 0x3C0000003C000000LL;
                                          v379.n128_u64[1] = 0x3C0000003C000000LL;
                                          vct_A = (struct sdfVector4_t)vmulq_f32(vcvtq_f32_u32(v378), v379);
                                          v494 = v41 * aRatio;
                                          v467 = 1.0 - (f32)(v41 * aRatio);
                                          vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v467);
                                          v380 = *(sdfVector4_t *)(*((u64 *)v501 + 2) + 16);
                                          vct_B = v380;
                                          vct_B = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_B, v494);
                                          v382 = vaddq_f32(v381[1], v381[2]);
                                          v381[1] = v382;
                                          if (object)
                                          {
                                            v383 = v304->WorkLightRGB;
                                            v384 = vct_A;
                                            *(int8x16_t *)targete = v384;
                                            v384.n128_u32[0] = v383;
                                            v385.n128_u64[0] = 0xFF000000FFLL;
                                            v385.n128_u64[1] = 0xFF000000FFLL;
                                            v384.n128_u32[1] = v383 >> 8;
                                            v384.n128_u32[2] = HIWORD(v383);
                                            v386 = vandq_s8(v384, v385);
                                            v386.n128_u32[3] = vshrq_n_u32(vdupq_n_s32(v383), 0x18u).n128_u32[3];
                                            v387.n128_u64[0] = 0x3C0000003C000000LL;
                                            v387.n128_u64[1] = 0x3C0000003C000000LL;
                                            vct_A = (struct sdfVector4_t)vmulq_f32(vcvtq_f32_u32(v386), v387);
                                            v388 = 1.0 - v460;
                                            vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v388);
                                            v389 = *(sdfVector4_t *)&object[1].klass->_1.name;
                                            vct_B = v389;
                                            vct_B = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_B, v460);
                                            vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
                                            v390 = 1.0 - aRatio;
                                            vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v390);
                                            vct_B = *(sdfVector4_t *)targete;
                                            vct_B = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_B, aRatio);
                                            v382 = vaddq_f32(v391[1], v391[2]);
                                            v391[1] = v382;
LABEL_856:
                                            vct_A.w = 0.0;
                                            WorkAmbientRGB = v304->WorkAmbientRGB;
                                            v395 = vct_A.w;
                                            v396 = vct_A.x;
                                            v397 = vcvts_n_s32_f32(v395, 7u);
                                            v398 = vcvts_n_u32_f32(v395, 7u);
                                            v399 = vcvts_n_s32_f32(v396, 7u);
                                            if ((f32)(v395 * 128.0) >= 0.0)
                                              v397 = v398;
                                            v400 = vcvts_n_u32_f32(v396, 7u);
                                            v317 = (f32)(v396 * 128.0) < 0.0;
                                            v401.n64_u64[0] = *(u64 *)&vct_A.y;
                                            v402.n64_u64[0] = vmul_f32(v401, (float32x2_t)0x4300000043000000LL).n64_u64[0];
                                            v403.n64_u64[0] = vcvt_n_s32_f32(v401, 7u).n64_u64[0];
                                            v404.n64_u64[0] = vcvt_n_u32_f32(v401, 7u).n64_u64[0];
                                            if (v317)
                                              v400 = v399;
                                            v405 = vand_s8(vshl_u32(vbsl_s8(vcltz_f32(v402), v403, v404), (uint32x2_t)0x1000000008LL), (int8x8_t)0xFF00000000FF00LL).n64_u64[0];
                                            v304->NowLightRGB = v400 | (v397 << 24) | v405 | HIDWORD(v405);
                                            v382.n128_u32[0] = WorkAmbientRGB;
                                            v406.n128_u64[0] = 0xFF000000FFLL;
                                            v406.n128_u64[1] = 0xFF000000FFLL;
                                            v382.n128_u32[1] = WorkAmbientRGB >> 8;
                                            v382.n128_u32[2] = HIWORD(WorkAmbientRGB);
                                            v407 = vandq_s8(v382, v406);
                                            v407.n128_u32[3] = vshrq_n_u32(vdupq_n_s32(WorkAmbientRGB), 0x18u).n128_u32[3];
                                            v408.n128_u64[0] = 0x3C0000003C000000LL;
                                            v408.n128_u64[1] = 0x3C0000003C000000LL;
                                            vct_A = (struct sdfVector4_t)vmulq_f32(vcvtq_f32_u32(v407), v408);
                                            vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v467);
                                            v409 = *(sdfVector4_t *)(v501 + 6);
                                            vct_B = v409;
                                            vct_B = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_B, v494);
                                            vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
                                            if (object)
                                            {
                                              v410 = v304->WorkAmbientRGB;
                                              v411 = vct_A;
                                              v505 = (struct sdfVector4_t)v411;
                                              v411.n128_u32[0] = v410;
                                              v412.n128_u64[0] = 0xFF000000FFLL;
                                              v412.n128_u64[1] = 0xFF000000FFLL;
                                              v411.n128_u32[1] = v410 >> 8;
                                              v411.n128_u32[2] = HIWORD(v410);
                                              v413 = vandq_s8(v411, v412);
                                              v413.n128_u32[3] = vshrq_n_u32(vdupq_n_s32(v410), 0x18u).n128_u32[3];
                                              v414.n128_u64[0] = 0x3C0000003C000000LL;
                                              v414.n128_u64[1] = 0x3C0000003C000000LL;
                                              vct_A = (struct sdfVector4_t)vmulq_f32(vcvtq_f32_u32(v413), v414);
                                              v415 = 1.0 - v460;
                                              vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v415);
                                              v416 = *(sdfVector4_t *)&object[1].monitor;
                                              vct_B = v416;
                                              vct_B = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_B, v460);
                                              vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
                                              v417 = 1.0 - aRatio;
                                              vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v417);
                                              vct_B = v505;
                                              vct_B = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_B, aRatio);
                                              vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
LABEL_898:
                                              vct_A.w = 0.0;
                                              v420 = vct_A.w;
                                              v421 = vct_A.x;
                                              v422 = vcvts_n_s32_f32(v420, 7u);
                                              v423 = vcvts_n_u32_f32(v420, 7u);
                                              v424 = vcvts_n_u32_f32(v421, 7u);
                                              if ((f32)(v420 * 128.0) >= 0.0)
                                                v422 = v423;
                                              v317 = (f32)(v421 * 128.0) < 0.0;
                                              v425 = vcvts_n_s32_f32(v421, 7u);
                                              v426.n64_u64[0] = *(u64 *)&vct_A.y;
                                              v427.n64_u64[0] = vmul_f32(v426, (float32x2_t)0x4300000043000000LL).n64_u64[0];
                                              v428.n64_u64[0] = vcvt_n_s32_f32(v426, 7u).n64_u64[0];
                                              v429.n64_u64[0] = vcvt_n_u32_f32(v426, 7u).n64_u64[0];
                                              v430.n64_u64[0] = vcltz_f32(v427).n64_u64[0];
                                              if (!v317)
                                                v425 = v424;
                                              v431 = vand_s8(vshl_u32(vbsl_s8(v430, v428, v429), (uint32x2_t)0x1000000008LL), (int8x8_t)0xFF00000000FF00LL).n64_u64[0];
                                              v304->NowAmbientRGB = v425 | (v422 << 24) | v431 | HIDWORD(v431);
                                              goto LABEL_677;
                                            }
                                            goto LABEL_898;
                                          }
                                          goto LABEL_856;
                                        }
                                        v310 = v219->Flag;
                                        if ((v310 & 0x1000) != 0)
                                          v310 &= 0xFFFFE4FF;
                                        v219->Flag = v310 & 0xFFFFE7FF;
                                        if (v139)
                                          goto LABEL_803;
LABEL_675:
                                        v304 = ha;
                                        v305 = ha->WorkAmbientRGB;
                                        WorkLightRGB1 = ha->WorkLightRGB1;
                                        ha->NowLightRGB = ha->WorkLightRGB;
                                        WorkLightRGB2 = v304->WorkLightRGB2;
                                        v304->NowAmbientRGB = v305;
                                        v304->NowLightRGB1 = WorkLightRGB1;
                                        v304->NowLightRGB2 = WorkLightRGB2;
                                        if (v501)
                                        {
LABEL_677:
                                          Instance = get_Instance(0);
                                          DrawBustUp_BG(Instance, v304, 0);
                                          return;
                                        }
                                        else
                                        {
                                          evtGetCustomSLight_SoftenAndBias(ha, (f32 *)&pBias + 1, &pBias);
                                          goto LABEL_677;
                                        }
                                        goto LABEL_677;
                                      }
                                      Ambient_local = v464;
                                      goto LABEL_653;
                                    }
                                    TargetAmbientRGB = v219->TargetAmbientRGB;
                                    v277.n128_u32[0] = TargetAmbientRGB;
                                    v283.n128_u64[0] = 0xFF000000FFLL;
                                    v283.n128_u64[1] = 0xFF000000FFLL;
                                    v277.n128_u32[1] = TargetAmbientRGB >> 8;
                                    v277.n128_u32[2] = HIWORD(TargetAmbientRGB);
                                    v284 = vandq_s8(v277, v283);
                                    v284.n128_u32[3] = vshrq_n_u32(vdupq_n_s32(TargetAmbientRGB), 0x18u).n128_u32[3];
                                    v285.n128_u64[0] = 0x3C0000003C000000LL;
                                    v285.n128_u64[1] = 0x3C0000003C000000LL;
                                    vct_A = (struct sdfVector4_t)vmulq_f32(vcvtq_f32_u32(v284), v285);
                                    goto LABEL_657;
                                  }
                                  else
                                  {
                                    v244 = *(sdfVector4_t *)(*((u64 *)v501 + 2) + 16);
                                    *(sdfVector4_t *)targetd = v244;
                                    goto LABEL_603;
                                  }
                                  v244 = *(sdfVector4_t *)targetd;
                                  goto LABEL_603;
                                }
                                TargetLightRGB2 = v219->TargetLightRGB2;
                                v242.n128_u32[0] = TargetLightRGB2;
                                v249.n128_u64[0] = 0xFF000000FFLL;
                                v249.n128_u64[1] = 0xFF000000FFLL;
                                v242.n128_u32[1] = TargetLightRGB2 >> 8;
                                v242.n128_u32[2] = HIWORD(TargetLightRGB2);
                                v250 = vandq_s8(v242, v249);
                                v250.n128_u32[3] = vshrq_n_u32(vdupq_n_s32(TargetLightRGB2), 0x18u).n128_u32[3];
                                v251.n128_u64[0] = 0x3C0000003C000000LL;
                                v251.n128_u64[1] = 0x3C0000003C000000LL;
                                vct_A = (struct sdfVector4_t)vmulq_f32(vcvtq_f32_u32(v250), v251);
                                goto LABEL_606;
                              }
                              else
                              {
                                v209 = *(sdfVector4_t *)(*((u64 *)v501 + 2) + 16);
                                *(sdfVector4_t *)targetc = v209;
                                goto LABEL_551;
                              }
                              v209 = *(sdfVector4_t *)targetc;
                              goto LABEL_551;
                            }
                            TargetLightRGB1 = v138->TargetLightRGB1;
                            v207.n128_u32[0] = TargetLightRGB1;
                            v213.n128_u64[0] = 0xFF000000FFLL;
                            v213.n128_u64[1] = 0xFF000000FFLL;
                            v207.n128_u32[1] = TargetLightRGB1 >> 8;
                            v207.n128_u32[2] = HIWORD(TargetLightRGB1);
                            v214 = vandq_s8(v207, v213);
                            v214.n128_u32[3] = vshrq_n_u32(vdupq_n_s32(TargetLightRGB1), 0x18u).n128_u32[3];
                            v215.n128_u64[0] = 0x3C0000003C000000LL;
                            v215.n128_u64[1] = 0x3C0000003C000000LL;
                            vct_A = (struct sdfVector4_t)vmulq_f32(vcvtq_f32_u32(v214), v215);
                            goto LABEL_554;
                          }
                          else
                          {
                            color = *(sdfVector4_t *)(*((u64 *)v501 + 2) + 16);
                            *(sdfVector4_t *)targetb = color;
                            goto LABEL_499;
                          }
                          color = *(sdfVector4_t *)targetb;
                          goto LABEL_499;
                        }
                        TargetLightRGB = v138->TargetLightRGB;
                        v173.n128_u32[0] = TargetLightRGB;
                        v179.n128_u64[0] = 0xFF000000FFLL;
                        v179.n128_u64[1] = 0xFF000000FFLL;
                        v173.n128_u32[1] = TargetLightRGB >> 8;
                        v173.n128_u32[2] = HIWORD(TargetLightRGB);
                        v180 = vandq_s8(v173, v179);
                        v180.n128_u32[3] = vshrq_n_u32(vdupq_n_s32(TargetLightRGB), 0x18u).n128_u32[3];
                        v181.n128_u64[0] = 0x3C0000003C000000LL;
                        v181.n128_u64[1] = 0x3C0000003C000000LL;
                        vct_A = (struct sdfVector4_t)vmulq_f32(vcvtq_f32_u32(v180), v181);
                        goto LABEL_502;
                      }
LABEL_438:
                      if ((v158 & 0x100) != 0)
                      {
                        if ((v158 & 0x200) != 0)
                          goto LABEL_802;
                        goto LABEL_444;
                      }
                      if ((v38 & 1) != 0)
                      {
                        v163 = DirLights[0];
                      }
                      else
                      {
                        v163 = *((sdf3DLight_t *)v501 + 2);
                      }
                      v491 = v163->color;
                      vct_A = v491;
                      v314 = vct_A.w;
                      v315 = vct_A.x;
                      v316 = vcvts_n_s32_f32(v314, 7u);
                      v317 = (f32)(v314 * 128.0) < 0.0;
                      v318 = vcvts_n_u32_f32(v314, 7u);
                      v319 = v315 * 128.0;
                      v320 = vcvts_n_u32_f32(v315, 7u);
                      if (!v317)
                        v316 = v318;
                      v321 = vcvts_n_s32_f32(v315, 7u);
                      v322.n64_u64[0] = *(u64 *)&vct_A.y;
                      v317 = v319 < 0.0;
                      v323.n64_u64[0] = vmul_f32(v322, (float32x2_t)0x4300000043000000LL).n64_u64[0];
                      v324.n64_u64[0] = vcvt_n_s32_f32(v322, 7u).n64_u64[0];
                      v325.n64_u64[0] = vcvt_n_u32_f32(v322, 7u).n64_u64[0];
                      v326.n64_u64[0] = vcltz_f32(v323).n64_u64[0];
                      if (!v317)
                        v321 = v320;
                      v327 = vand_s8(vshl_u32(vbsl_s8(v326, v324, v325), (uint32x2_t)0x1000000008LL), (int8x8_t)0xFF00000000FF00LL).n64_u64[0];
                      v138->WorkLightRGB = v321
                                                | (v316 << 24)
                                                | v327
                                                | HIDWORD(v327);
                      if ((v38 & 1) != 0)
                      {
                        v492 = DirLights[1]->color;
LABEL_776:
                        vct_A = v492;
                        v347 = vct_A.w;
                        v348 = vct_A.x;
                        v349 = vcvts_n_s32_f32(v347, 7u);
                        v350 = vcvts_n_u32_f32(v347, 7u);
                        v351 = vcvts_n_u32_f32(v348, 7u);
                        if ((f32)(v347 * 128.0) >= 0.0)
                          v349 = v350;
                        v317 = (f32)(v348 * 128.0) < 0.0;
                        v352 = vcvts_n_s32_f32(v348, 7u);
                        v353.n64_u64[0] = *(u64 *)&vct_A.y;
                        v354.n64_u64[0] = vmul_f32(v353, (float32x2_t)0x4300000043000000LL).n64_u64[0];
                        v355.n64_u64[0] = vcvt_n_s32_f32(v353, 7u).n64_u64[0];
                        v356.n64_u64[0] = vcvt_n_u32_f32(v353, 7u).n64_u64[0];
                        v357.n64_u64[0] = vcltz_f32(v354).n64_u64[0];
                        if (!v317)
                          v352 = v351;
                        v358 = vand_s8(vshl_u32(vbsl_s8(v357, v355, v356), (uint32x2_t)0x1000000008LL), (int8x8_t)0xFF00000000FF00LL).n64_u64[0];
                        v138->WorkLightRGB1 = v352
                                                   | (v349 << 24)
                                                   | v358
                                                   | HIDWORD(v358);
                        if ((v38 & 1) != 0)
                        {
                          v493 = DirLights[2]->color;
LABEL_792:
                          WorkLightDir1.n128_u32[3] = LODWORD(v493.w);
                          vct_A = v493;
                          v363 = vct_A.w;
                          v364 = vct_A.x;
                          v365 = vcvts_n_s32_f32(v363, 7u);
                          v366 = vcvts_n_u32_f32(v363, 7u);
                          v367 = vcvts_n_u32_f32(v364, 7u);
                          if ((f32)(v363 * 128.0) >= 0.0)
                            v365 = v366;
                          v317 = (f32)(v364 * 128.0) < 0.0;
                          v368 = vcvts_n_s32_f32(v364, 7u);
                          v369.n64_u64[0] = *(u64 *)&vct_A.y;
                          v370.n64_u64[0] = vmul_f32(v369, (float32x2_t)0x4300000043000000LL).n64_u64[0];
                          v371.n64_u64[0] = vcvt_n_s32_f32(v369, 7u).n64_u64[0];
                          v372.n64_u64[0] = vcvt_n_u32_f32(v369, 7u).n64_u64[0];
                          v373.n64_u64[0] = vcltz_f32(v370).n64_u64[0];
                          if (!v317)
                            v368 = v367;
                          v374 = vand_s8(vshl_u32(vbsl_s8(v373, v371, v372), (uint32x2_t)0x1000000008LL), (int8x8_t)0xFF00000000FF00LL).n64_u64[0];
                          v138->WorkLightRGB2 = v368
                                                     | (v365 << 24)
                                                     | v374
                                                     | HIDWORD(v374);
                          if ((v138->Flag & 0x200) != 0)
                          {
LABEL_802:
                            if (v139)
                              goto LABEL_803;
                            goto LABEL_675;
                          }
LABEL_444:
                          if ((v38 & 1) != 0)
                          {
                            v165 = Ambient;
                            v489 = v165;
LABEL_763:
                            WorkLightDir1.n128_u32[3] = LODWORD(v489.w);
                            vct_A = v489;
                            v332 = vct_A.w;
                            v333 = vct_A.x;
                            v334 = vcvts_n_s32_f32(v332, 7u);
                            v335 = vcvts_n_u32_f32(v332, 7u);
                            v336 = vcvts_n_u32_f32(v333, 7u);
                            if ((f32)(v332 * 128.0) >= 0.0)
                              v334 = v335;
                            v317 = (f32)(v333 * 128.0) < 0.0;
                            v337 = vcvts_n_s32_f32(v333, 7u);
                            v338.n64_u64[0] = *(u64 *)&vct_A.y;
                            v339.n64_u64[0] = vmul_f32(v338, (float32x2_t)0x4300000043000000LL).n64_u64[0];
                            v340.n64_u64[0] = vcvt_n_s32_f32(v338, 7u).n64_u64[0];
                            v341.n64_u64[0] = vcvt_n_u32_f32(v338, 7u).n64_u64[0];
                            v342.n64_u64[0] = vcltz_f32(v339).n64_u64[0];
                            if (!v317)
                              v337 = v336;
                            v343 = vand_s8(vshl_u32(vbsl_s8(v342, v340, v341), (uint32x2_t)0x1000000008LL), (int8x8_t)0xFF00000000FF00LL).n64_u64[0];
                            v138->WorkAmbientRGB = v337 | (v334 << 24) | v343 | HIDWORD(v343);
                            if (v139)
                              goto LABEL_803;
                            goto LABEL_675;
                          }
                          else
                          {
                            v489 = *(sdfVector4_t *)(v501 + 6);
                            goto LABEL_763;
                          }
                          goto LABEL_763;
                        }
                        else
                        {
                          v493 = *(sdfVector4_t *)(*((u64 *)v501 + 2) + 16);
                          goto LABEL_792;
                        }
                        goto LABEL_792;
                      }
                      else
                      {
                        v492 = *(sdfVector4_t *)(*((u64 *)v501 + 2) + 16);
                        goto LABEL_776;
                      }
                      goto LABEL_776;
                    }
                    v487 = ha->WorkLightDir;
                    vct_A = v487;
                    v141 = &vf00.x;
                    v141[8] = x;
                    v141[9] = y;
                    v141[10] = z;
                    v141[11] = v40;
                    dds3RotationArc();
                    vct_B = vct_A;
                    vct_A = (struct sdfVector4_t)xmmword_3CFD5C0;
                    Lerp(aRatio);
                    ToMatrix();
                    v143 = v138->WorkLightDir;
                    vct_A = v143;
                    get_transpose(&v513, &mtx_A, 0);
                    v523 = vct_A;
                    v512 = v513;
                    v517 = op_Multiply_60923920(&v512, v523, 0);
                    vct_A = v517;
                    if (object)
                    {
                      v433 = v138->WorkLightDir;
                      *(sdfVector4_t *)targeta = vct_A;
                      vct_A = v433;
                      vct_B = v461;
                      dds3RotationArc();
                      vct_B = vct_A;
                      vct_A = (struct sdfVector4_t)xmmword_3CFD5C0;
                      Lerp(1.0);
                      ToMatrix();
                      v150 = v138->WorkLightDir;
                      vct_A = v150;
                      get_transpose(&v513, &mtx_A, 0);
                      v524 = vct_A;
                      v512 = v513;
                      v518 = op_Multiply_60923920(&v512, v524, 0);
                      vct_A = v518;
                      v462 = vct_A;
                      vct_B = *(sdfVector4_t *)targeta;
                      dds3RotationArc();
                      vct_B = vct_A;
                      vct_A = (struct sdfVector4_t)xmmword_3CFD5C0;
                      Lerp(aRatio);
                      ToMatrix();
                      vct_A = v462;
                      get_transpose(&v513, &mtx_A, 0);
                      v525 = vct_A;
                      v512 = v513;
                      v519 = op_Multiply_60923920(&v512, v525, 0);
                      vct_A = v519;
                      goto LABEL_430;
                    }
LABEL_430:
                    p_NowLightDir = &v138->NowLightDir;
                    WorkLightDir1 = vct_A;
                    *p_NowLightDir = WorkLightDir1;
                    v158 = v138->Flag;
                    if ((v158 & 0x1800) != 0)
                      goto LABEL_433;
                    goto LABEL_438;
                  }
                  v = h->TargetLightDir;
                  goto LABEL_180;
                }
LABEL_333:
                if ((v42 & 0x400) != 0)
                  goto LABEL_381;
                if ((v38 & 1) != 0)
                {
                  v124 = DirLights[0];
                }
                else
                {
                  v124 = *((sdf3DLight_t *)v36 + 2);
                }
                v484 = v124->v;
                v126 = ha;
                vct_A = v484;
                v127 = &v126->WorkLightDir;
                *v127 = vct_A;
                if ((v38 & 1) != 0)
                {
                  v485 = DirLights[1]->v;
LABEL_358:
                  vct_A = v485;
                  v132 = &v126->WorkLightDir1;
                  *v132 = vct_A;
                  if ((v38 & 1) != 0)
                  {
                    v486 = DirLights[2]->v;
LABEL_375:
                    vct_A = v486;
                    v136 = &v126->WorkLightDir2;
                    *v136 = vct_A;
                    goto LABEL_381;
                  }
                  v486 = *(sdfVector4_t *)(*((u64 *)v36 + 2) + 32);
                  goto LABEL_375;
                }
                v485 = *(sdfVector4_t *)(*((u64 *)v36 + 2) + 32);
                goto LABEL_358;
              }
              v122 = 0.0;
              if ((v74 & 0x100000) == 0)
                v122 = 1.0;
            }
            else
            {
              v122 = 1.0;
            }
            aRatio = v122;
            goto LABEL_332;
LABEL_154:
            v73 = &vf00.x;
            v73[4] = x;
            v73[5] = y;
            v73[6] = z;
            v73[7] = v40;
            if (((u8)v36[15] & 8) != 0)
              goto LABEL_289;
            goto LABEL_155;
LABEL_153:
            goto LABEL_154;
          }
          else
          {
            v70 = *((f32 *)&object[2].monitor + 1);
            if (v69 < v70)
            {
              v460 = 1.0 - (f32)((f32)(v69 - v68) / (f32)(v70 - v68));
            }
          }
LABEL_152:
          goto LABEL_153;
        }
      }
      v36 = workdata;
      v461 = (struct sdfVector4_t)0;
      goto LABEL_152;
    }
    if (h->ModelRGBAnimeMaxFrame)
    {
      LOWORD(v3) = h->ModelRGBAnimeFrame;
      v8 = (f32)v3 / (f32)h->ModelRGBAnimeMaxFrame;
    }
    else
    {
      v8 = 1.0;
    }
    v499 = v8;
    v470 = h->TargetModelRGBA;
    vct_B = v470;
    v10 = h->BaseModelRGBA;
    v11 = 1.0;
    vct_A = v10;
    v12 = v11 - v499;
    vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v12);
    vct_B = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_B, v499);
    vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    v13 = &vf00.x;
    v14 = v13[4];
    v15 = v13[5];
    v16 = v13[6];
    v17 = h->Model;
    v526.w = mdlGetColor(v17).w;
    v526.x = v14;
    v526.y = v15;
    v526.z = v16;
    SetColor(h->Model, v526);
    ModelRGBAnimeFrame = h->ModelRGBAnimeFrame;
    if (ModelRGBAnimeFrame >= h->ModelRGBAnimeMaxFrame)
    {
      v19 = h->Flag & 0xFFFF7FFF;
      h->Flag = v19;
      if ((v19 & 0x10000) != 0)
        goto LABEL_31;
    }
    else
    {
      h->ModelRGBAnimeFrame = ModelRGBAnimeFrame + 1;
      if ((h->Flag & 0x10000) != 0)
        goto LABEL_31;
    }
LABEL_6:
    dissolveAlphaMove = h->dissolveAlphaMove;
    if (dissolveAlphaMove == 0.0)
      goto LABEL_7;
LABEL_66:
    v28 = dissolveAlphaMove + h->dissolveAlpha;
    h->dissolveAlpha = v28;
    if (dissolveAlphaMove <= 0.0)
    {
      v29 = 0.0;
      if (v28 > 0.0)
        goto LABEL_84;
    }
    else
    {
      v29 = 1.0;
      if (v28 < 1.0)
      {
LABEL_84:
        v30 = h->Model;
        mdlSetDissolveAlpha(v30, v28);
        v7 = h->Flag;
        if ((v7 & 0x40000) == 0)
          goto LABEL_95;
        goto LABEL_87;
      }
    }
    v28 = v29;
    h->dissolveAlpha = v29;
    h->dissolveAlphaMove = 0.0;
    goto LABEL_84;
  }
}

// 0x19c7a90
static void GetBaseLightRGB(evtUnitHandle_t *h) {
  u32 NowLightRGB;
  f32 *v6;
  f32 v7;
  f32 v8;
  f32 v9;
  f32 v10;
  sdfVector4_t v11;

  NowLightRGB = h->NowLightRGB;
  v6 = DirLights[0];
  v7 = v6[4];
  v8 = v6[5];
  v9 = v6[6];
  v10 = v6[7];
  v11.x = v7;
  v11.y = v8;
  v11.z = v9;
  v11.w = v10;
  GetBaseLightRGB_2(h, NowLightRGB, v11);
}

// 0x19c7e10
static void GetBaseLightRGB1(evtUnitHandle_t *h) {
  u32 NowLightRGB1;
  f32 *v6;
  f32 v7;
  f32 v8;
  f32 v9;
  f32 v10;
  sdfVector4_t v11;

  NowLightRGB1 = h->NowLightRGB1;
  v6 = DirLights[1];
  v7 = v6[4];
  v8 = v6[5];
  v9 = v6[6];
  v10 = v6[7];
  v11.x = v7;
  v11.y = v8;
  v11.z = v9;
  v11.w = v10;
  GetBaseLightRGB_2(h, NowLightRGB1, v11);
}

// 0x19c7ee0
static void GetBaseLightRGB2(evtUnitHandle_t *h) {
  u32 NowLightRGB2;
  f32 *v6;
  f32 v7;
  f32 v8;
  f32 v9;
  f32 v10;
  sdfVector4_t v11;

  NowLightRGB2 = h->NowLightRGB2;
  v6 = DirLights[2];
  v7 = v6[4];
  v8 = v6[5];
  v9 = v6[6];
  v10 = v6[7];
  v11.x = v7;
  v11.y = v8;
  v11.z = v9;
  v11.w = v10;
  GetBaseLightRGB_2(h, NowLightRGB2, v11);
}

// 0x19c7b60
static void GetBaseLightRGB_2(evtUnitHandle_t *h, u32 col, const sdfVector4_t *col1) {
  f32 w;
  f32 x;
  dds3Basic_t *BasicLight;
  void *workdata;
  bool v10;
  s32 Flag;
  f32 v14;
  Project_Basic_dds3Basic_t_WORK_c *klass;
  f32 z;
  f32 y;
  f32 v19;
  s64 v20;

  w = col1->w;
  x = col1->x;
  z = col1->z;
  y = col1->y;
  col1->y = y;
  BasicLight = h->BasicLight;
  workdata = 0;
  v10 = 1;
  Flag = h->Flag;
  if (BasicLight && (Flag & 0x40000) != 0)
  {
    workdata = BasicLight->workdata;
    v10 = (BYTE4(workdata[3].monitor) & 8) == 0;
  }
  if ((Flag & 0x100) != 0)
  {
    w = (f32)HIBYTE(col) * 0.0078125;
    x = (f32)(u8)col * 0.0078125;
    *(float32x2_t *)&col1->y = vmul_f32(vcvt_f32_u32(vand_s8(vshl_u32(vdup_n_s32(col), (uint32x2_t)0xFFFFFFF0FFFFFFF8LL), (int8x8_t)0xFF000000FFLL)), (float32x2_t)0x3C0000003C000000LL);
    goto LABEL_22;
  }
  if (!v10)
  {
    klass = workdata[1].klass;
    x = *(f32 *)&klass->_1.name;
    *(u64 *)&col1->y = *(const char **)((char *)&klass->_1.name + 4);
    w = *((f32 *)&klass->_1.namespaze + 1);
    v20 = *(u64 *)&col1->y;
    goto LABEL_22;
  }
  v19 = col1->y;
  v14 = z;
LABEL_22:
  vct_A.x = x;
  vct_A.w = w;
  *(u64 *)&vct_A.y = *(u64 *)&col1->y;
}

// 0x19c7fb0
static void GetBaseAmbientRGB(evtUnitHandle_t *h) {
  int8x16_t v2;
  dds3Basic_t *BasicLight;
  void *workdata;
  bool v6;
  s32 Flag;
  float32x4_t Ambient_local;
  u32 NowAmbientRGB;
  int8x16_t v14;
  uint32x4_t v15;
  float32x4_t v16;
  float32x4_t v17;

  BasicLight = h->BasicLight;
  workdata = 0;
  v6 = 1;
  Flag = h->Flag;
  if (BasicLight && (Flag & 0x40000) != 0)
  {
    workdata = BasicLight->workdata;
    v6 = (BYTE4(workdata[3].monitor) & 8) == 0;
  }
  if ((Flag & 0x200) == 0)
  {
    if (v6)
    {
      Ambient_local = Ambient;
      v17 = Ambient_local;
LABEL_21:
      goto LABEL_23;
    }
    else
    {
      Ambient_local = *(float32x4_t *)&workdata[1].monitor;
      v17 = Ambient_local;
      goto LABEL_21;
    }
    Ambient_local = v17;
    goto LABEL_21;
  }
  NowAmbientRGB = h->NowAmbientRGB;
  v2.n128_u32[0] = NowAmbientRGB;
  v14.n128_u64[0] = 0xFF000000FFLL;
  v14.n128_u64[1] = 0xFF000000FFLL;
  v2.n128_u32[1] = NowAmbientRGB >> 8;
  v2.n128_u32[2] = HIWORD(NowAmbientRGB);
  v15 = vandq_s8(v2, v14);
  v15.n128_u32[3] = vshrq_n_u32(vdupq_n_s32(NowAmbientRGB), 0x18u).n128_u32[3];
  v16.n128_u64[0] = 0x3C0000003C000000LL;
  v16.n128_u64[1] = 0x3C0000003C000000LL;
  Ambient_local = vmulq_f32(vcvtq_f32_u32(v15), v16);
LABEL_23:
  vct_A = (struct sdfVector4_t)Ambient_local;
}

// 0x19c81e0
static void GetBaseLightDir(evtUnitHandle_t *h) {
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  f32 *v8;
  f32 v9;
  f32 v10;
  f32 v11;
  f32 v12;
  sdfVector4_t v13;
  sdfVector4_t v14;

  x = h->NowLightDir.x;
  y = h->NowLightDir.y;
  z = h->NowLightDir.z;
  w = h->NowLightDir.w;
  v8 = DirLights[0];
  v9 = v8[8];
  v10 = v8[9];
  v11 = v8[10];
  v12 = v8[11];
  v13.x = x;
  v13.y = y;
  v13.z = z;
  v13.w = w;
  v14.x = v9;
  v14.y = v10;
  v14.z = v11;
  v14.w = v12;
  GetBaseLightDir_2(h, v13, v14);
}

// 0x19c8490
static void GetBaseLightDir1(evtUnitHandle_t *h) {
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  f32 *v8;
  f32 v9;
  f32 v10;
  f32 v11;
  f32 v12;
  sdfVector4_t v13;
  sdfVector4_t v14;

  x = h->NowLightDir1.x;
  y = h->NowLightDir1.y;
  z = h->NowLightDir1.z;
  w = h->NowLightDir1.w;
  v8 = DirLights[1];
  v9 = v8[8];
  v10 = v8[9];
  v11 = v8[10];
  v12 = v8[11];
  v13.x = x;
  v13.y = y;
  v13.z = z;
  v13.w = w;
  v14.x = v9;
  v14.y = v10;
  v14.z = v11;
  v14.w = v12;
  GetBaseLightDir_2(h, v13, v14);
}

// 0x19c8580
static void GetBaseLightDir2(evtUnitHandle_t *h) {
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  f32 *v8;
  f32 v9;
  f32 v10;
  f32 v11;
  f32 v12;
  sdfVector4_t v13;
  sdfVector4_t v14;

  x = h->NowLightDir1.x;
  y = h->NowLightDir1.y;
  z = h->NowLightDir1.z;
  w = h->NowLightDir1.w;
  v8 = DirLights[2];
  v9 = v8[8];
  v10 = v8[9];
  v11 = v8[10];
  v12 = v8[11];
  v13.x = x;
  v13.y = y;
  v13.z = z;
  v13.w = w;
  v14.x = v9;
  v14.y = v10;
  v14.z = v11;
  v14.w = v12;
  GetBaseLightDir_2(h, v13, v14);
}

// 0x19c82d0
static void GetBaseLightDir_2(evtUnitHandle_t *h, const sdfVector4_t *col1, const sdfVector4_t *col2) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  f32 v8;
  f32 v9;
  f32 v11;
  f32 v12;
  dds3Basic_t *BasicLight;
  bool v14;
  s32 Flag;
  void *workdata;
  f32 *p_x;

  w = col2->w;
  z = col2->z;
  y = col2->y;
  x = col2->x;
  v8 = col1->w;
  v9 = col1->z;
  v11 = col1->y;
  v12 = col1->x;
  BasicLight = h->BasicLight;
  v14 = 1;
  Flag = h->Flag;
  if (BasicLight && (Flag & 0x40000) != 0)
  {
    workdata = BasicLight->workdata;
    v14 = (BYTE4(workdata[3].monitor) & 8) == 0;
  }
  if ((Flag & 0x400) == 0 && v14)
  {
    v12 = x;
    v11 = y;
    v9 = z;
    v8 = w;
    goto LABEL_19;
  }
LABEL_19:
  p_x = &vf00.x;
  p_x[4] = v12;
  p_x[5] = v11;
  p_x[6] = v9;
  p_x[7] = v8;
}

// 0x19c8670
static void MakeLightPacket(evtUnitHandle_t *h) {
  sdf3DLight_t *v3;
  sdf3DLight_t *v4;
  s64 v5;
  sdf3DLight_t *v6;
  sdf3DLight_t *v7;
  int8x16_t v10;
  u32 NowLightRGB;
  int8x16_t v13;
  uint32x4_t v14;
  float32x4_t v15;
  sdf3DLight_t *v16;
  sdfVector4_t *p_color;
  s32 v19;
  u32 NowLightRGB1;
  int8x16_t v21;
  uint32x4_t v22;
  float32x4_t v23;
  sdf3DLight_t *v24;
  sdfVector4_t *v25;
  struct sdfVector4_t v26;
  s32 v27;
  u32 NowLightRGB2;
  int8x16_t v29;
  uint32x4_t v30;
  float32x4_t v31;
  sdf3DLight_t *v32;
  sdfVector4_t *v33;
  struct sdfVector4_t NowLightDir;
  sdf3DLight_t *v35;
  sdfVector4_t *p_v;
  s32 v37;
  struct sdfVector4_t NowLightDir1;
  sdf3DLight_t *v39;
  sdfVector4_t *v40;
  s32 v41;
  struct sdfVector4_t NowLightDir2;
  sdf3DLight_t *v43;
  sdfVector4_t *v44;
  struct sdfVector4_t v45;
  s32 v46;
  u32 NowAmbientRGB;
  int8x16_t v48;
  uint32x4_t v49;
  float32x4_t v50;
  f32 *p_x;
  sdf3DLightParallelPacket_t *PrivateLightPacket;
  f32 v53;
  f32 v54;
  f32 v55;
  f32 x;
  sdf3DLightParallelPacket_t *v57;
  s32 v58;
  s32 v59;
  s32 v60;
  s32 v61;
  s32 v62;
  struct sdfVector4_t v65;
  struct sdfVector4_t v67;
  sdfVector4_t v69;

  v3 = NewSpecific(sdf3DLight_t, 3u);
  v4 = v3;
  if (*(s32 *)((char *)v3 + 24) >= 1)
  {
    v5 = 0;
    v6 = &v3[0];
    do
    {
      v7 = Allocate(sdf3DLight_t);
      _ctor(v7, 0);
      v6 = v7;
      ++v5;
      ++v6;
    }
    while (v5 < SLODWORD(v4->max_length));
  }
  if ((h->Flag & 0x20000) == 0)
  {
    h->PublicLightPacket = 0;
    if ((h->Flag & 0x40700) != 0)
    {
      NowLightRGB = h->NowLightRGB;
      v10.n128_u32[0] = NowLightRGB;
      v13.n128_u64[0] = 0xFF000000FFLL;
      v13.n128_u64[1] = 0xFF000000FFLL;
      v10.n128_u32[1] = NowLightRGB >> 8;
      v10.n128_u32[2] = HIWORD(NowLightRGB);
      v14 = vandq_s8(v10, v13);
      v14.n128_u32[3] = vshrq_n_u32(vdupq_n_s32(NowLightRGB), 0x18u).n128_u32[3];
      v15.n128_u64[0] = 0x3C0000003C000000LL;
      v15.n128_u64[1] = 0x3C0000003C000000LL;
      vct_A = (struct sdfVector4_t)vmulq_f32(vcvtq_f32_u32(v14), v15);
      v16 = v4[0];
      p_color = &v16->color;
      v19 = (u8)byte_57564C4;
      *p_color = vct_A;
      NowLightRGB1 = h->NowLightRGB1;
      if (v19)
        goto LABEL_17;
      goto LABEL_61;
      if (v58)
      {
LABEL_17:
LABEL_18:
        LODWORD(vct_A.x) = NowLightRGB1;
        v21.n128_u64[0] = 0xFF000000FFLL;
        v21.n128_u64[1] = 0xFF000000FFLL;
        LODWORD(vct_A.y) = NowLightRGB1 >> 8;
        LODWORD(vct_A.z) = HIWORD(NowLightRGB1);
        v22 = vandq_s8((int8x16_t)vct_A, v21);
        v22.n128_u32[3] = vshrq_n_u32(vdupq_n_s32(NowLightRGB1), 0x18u).n128_u32[3];
        v23.n128_u64[0] = 0x3C0000003C000000LL;
        v23.n128_u64[1] = 0x3C0000003C000000LL;
        vct_A = (struct sdfVector4_t)vmulq_f32(vcvtq_f32_u32(v22), v23);
        v24 = v4[1];
        v25 = &v24->color;
        v26 = vct_A;
        v27 = (u8)byte_57564C4;
        *v25 = v26;
        NowLightRGB2 = h->NowLightRGB2;
        if (v27)
          goto LABEL_21;
        goto LABEL_65;
        if (v59)
        {
LABEL_21:
LABEL_22:
          LODWORD(v26.x) = NowLightRGB2;
          v29.n128_u64[0] = 0xFF000000FFLL;
          v29.n128_u64[1] = 0xFF000000FFLL;
          LODWORD(v26.y) = NowLightRGB2 >> 8;
          LODWORD(v26.z) = HIWORD(NowLightRGB2);
          v30 = vandq_s8((int8x16_t)v26, v29);
          v30.n128_u32[3] = vshrq_n_u32(vdupq_n_s32(NowLightRGB2), 0x18u).n128_u32[3];
          v31.n128_u64[0] = 0x3C0000003C000000LL;
          v31.n128_u64[1] = 0x3C0000003C000000LL;
          vct_A = (struct sdfVector4_t)vmulq_f32(vcvtq_f32_u32(v30), v31);
          v32 = v4[2];
          v33 = &v32->color;
          *v33 = vct_A;
          NowLightDir = h->NowLightDir;
          vct_A = NowLightDir;
          v35 = v4[0];
          p_v = &v35->v;
          v37 = (u8)byte_5755EF5;
          *p_v = vct_A;
          NowLightDir1 = h->NowLightDir1;
          if (v37)
            goto LABEL_29;
          goto LABEL_73;
          if (v60)
          {
LABEL_29:
            goto LABEL_30;
          }
LABEL_73:
          v65 = NowLightDir1;
          NowLightDir1 = v65;
LABEL_30:
          vct_A = NowLightDir1;
          v39 = v4[1];
          v40 = &v39->v;
          v41 = (u8)byte_5755EF5;
          *v40 = vct_A;
          NowLightDir2 = h->NowLightDir2;
          if (v41)
            goto LABEL_33;
          goto LABEL_77;
          if (v61)
          {
LABEL_33:
            goto LABEL_34;
          }
LABEL_77:
          v67 = NowLightDir2;
          NowLightDir2 = v67;
LABEL_34:
          vct_A = NowLightDir2;
          v43 = v4[2];
          v44 = &v43->v;
          v45 = vct_A;
          v46 = (u8)byte_57564C4;
          *v44 = v45;
          NowAmbientRGB = h->NowAmbientRGB;
          if (v46)
            goto LABEL_37;
          goto LABEL_81;
          if (v62)
          {
LABEL_37:
LABEL_38:
            LODWORD(v45.x) = NowAmbientRGB;
            v48.n128_u64[0] = 0xFF000000FFLL;
            v48.n128_u64[1] = 0xFF000000FFLL;
            LODWORD(v45.y) = NowAmbientRGB >> 8;
            LODWORD(v45.z) = HIWORD(NowAmbientRGB);
            v49 = vandq_s8((int8x16_t)v45, v48);
            v49.n128_u32[3] = vshrq_n_u32(vdupq_n_s32(NowAmbientRGB), 0x18u).n128_u32[3];
            v50.n128_u64[0] = 0x3C0000003C000000LL;
            v50.n128_u64[1] = 0x3C0000003C000000LL;
            vct_A = (struct sdfVector4_t)vmulq_f32(vcvtq_f32_u32(v49), v50);
            p_x = &vf00.x;
            PrivateLightPacket = h->PrivateLightPacket;
            if (p_x[4] <= 1.0)
              v53 = p_x[4];
            else
              v53 = 1.0;
            if (p_x[5] <= 1.0)
              v54 = p_x[5];
            else
              v54 = 1.0;
            if (p_x[6] <= 1.0)
              v55 = p_x[6];
            else
              v55 = 1.0;
            v69.w = 1.0;
            v69.x = v53;
            v69.y = v54;
            v69.z = v55;
            sdf3MakeLightParallelPacket(PrivateLightPacket, v4, v69, 1);
            x = h->NowRim.x;
            v57 = h->PrivateLightPacket;
            h->PublicLightPacket = v57;
            v57->rim.x = x;
            v57->rim.y = h->NowRim.y;
            v57->rim.z = h->NowRim.z;
            v57->rim.w = h->NowRim.w;
            return;
          }
LABEL_81:
          goto LABEL_38;
        }
LABEL_65:
        goto LABEL_22;
      }
LABEL_61:
      goto LABEL_18;
    }
    evtMakeCustomSLightPacket(h);
  }
}

// 0x19c9210
void evtLinkLightObjectBasic(evtUnitHandle_t *h, dds3Basic_t *light, s32 frame) {
  dds3Basic_t *BasicLight;
  dds3Basic_t *p_BasicLight2;
  dds3Basic_t *v9;
  s32 Flag;
  s32 v11;

  BasicLight = h->BasicLight;
  p_BasicLight2 = &h->BasicLight2;
  if (BasicLight)
    p_BasicLight2 = BasicLight;
  else
    p_BasicLight2 = 0;
  v9 = light;
  h->BasicLight = light;
  Flag = h->Flag;
  h->BasicLightAnimeFrame = 0;
  v11 = Flag | 0x40000;
  if (frame)
  {
    h->BasicLightAnimeMaxFrame = frame;
    h->Flag = v11 & 0xFFE7FFFF | 0x80000;
  }
  else
  {
    h->BasicLightAnimeMaxFrame = 0;
    h->Flag = v11 & 0xFFE7FFFF;
    h->BasicLight2 = 0;
  }
}

// 0x19c92e0
void evtUnlinkLightObjectBasic(evtUnitHandle_t *h, s32 frame) {
  s32 Flag;
  s32 v5;

  if (h->BasicLight)
  {
    if (frame)
    {
      Flag = h->Flag;
      h->BasicLightAnimeFrame = 0;
      h->BasicLightAnimeMaxFrame = frame;
      v5 = Flag & 0xFFE7FFFF | 0x100000;
    }
    else
    {
      h->BasicLight = 0;
      v5 = h->Flag & 0xFFE3FFFF;
    }
    h->Flag = v5;
  }
}

// 0x19c9340
void evtLinkExternalLightPacket(evtUnitHandle_t *h, sdf3DLightParallelPacket_t *packet) {
  h->PublicLightPacket = packet;
  h->Flag |= 0x20000u;
}

// 0x19c9380
void evtUnlinkExternalLightPacket(evtUnitHandle_t *h) {
  evtUnitHandle_t *v4;

  h->Flag &= ~0x20000u;
  v4 = h;
  MakeLightPacket(v4);
}

// 0x19c9420
void evtSetUnitLightAndAmbient(evtUnitHandle_t *h, u32 frame, u32 lrgb, u32 argb) {
  u16 v7;
  u32 NowLightRGB;
  f32 *v13;
  f32 v14;
  f32 v15;
  f32 v16;
  f32 v17;
  f32 w;
  f32 x;
  u32 v23;
  bool v24;
  u32 v25;
  f32 v26;
  u8 v27;
  u8 v28;
  float32x2_t v29;
  float32x2_t v30;
  int32x2_t v31;
  uint32x2_t v32;
  int32x2_t v33;
  u64 v34;
  f32 *p_x;
  f32 v37;
  f32 v38;
  f32 v39;
  f32 v40;
  u8 v41;
  u8 v42;
  u8 v43;
  u8 v44;
  f32 v45;
  u32 v46;
  u32 v47;
  u8 v48;
  u8 v49;
  u32 v50;
  s32 v51;
  u32 v52;
  sdfVector4_t v53;

  v7 = frame;
  h->LightRGBAnimeFrame = frame;
  h->TargetLightRGB = lrgb;
  h->TargetAmbientRGB = argb;
  goto LABEL_3;
  if (v52)
  {
LABEL_3:
    goto LABEL_4;
  }
LABEL_4:
  NowLightRGB = h->NowLightRGB;
  v13 = DirLights[0];
  v14 = v13[4];
  v15 = v13[5];
  v16 = v13[6];
  v17 = v13[7];
  v53.x = v14;
  v53.y = v15;
  v53.z = v16;
  v53.w = v17;
  GetBaseLightRGB_2(h, NowLightRGB, v53);
  w = vct_A.w;
  x = vct_A.x;
  v23 = vcvts_n_s32_f32(w, 7u);
  v24 = (f32)(w * 128.0) < 0.0;
  v25 = vcvts_n_u32_f32(w, 7u);
  v26 = x * 128.0;
  v27 = vcvts_n_u32_f32(x, 7u);
  if (!v24)
    v23 = v25;
  v28 = vcvts_n_s32_f32(x, 7u);
  v29.n64_u64[0] = *(u64 *)&vct_A.y;
  v24 = v26 < 0.0;
  v30.n64_u64[0] = vmul_f32(v29, (float32x2_t)0x4300000043000000LL).n64_u64[0];
  v31.n64_u64[0] = vcvt_n_s32_f32(v29, 7u).n64_u64[0];
  v32.n64_u64[0] = vcvt_n_u32_f32(v29, 7u).n64_u64[0];
  v33.n64_u64[0] = vcltz_f32(v30).n64_u64[0];
  if (!v24)
    v28 = v27;
  v34 = vand_s8(vshl_u32(vbsl_s8(v33, v31, v32), (uint32x2_t)0x1000000008LL), (int8x8_t)0xFF00000000FF00LL).n64_u64[0];
  h->BaseLightRGB = v28 | (v23 << 24) | v34 | HIDWORD(v34);
  GetBaseAmbientRGB(h);
  p_x = &vf00.x;
  v38 = p_x[4];
  v37 = p_x[5];
  v39 = p_x[6];
  v40 = p_x[7];
  v41 = vcvts_n_s32_f32(v37, 7u);
  v42 = vcvts_n_u32_f32(v37, 7u);
  v43 = vcvts_n_s32_f32(v39, 7u);
  v44 = vcvts_n_u32_f32(v39, 7u);
  v45 = v39 * 128.0;
  v46 = vcvts_n_s32_f32(v40, 7u);
  if ((f32)(v37 * 128.0) >= 0.0)
    v41 = v42;
  v47 = vcvts_n_u32_f32(v40, 7u);
  if (v45 >= 0.0)
    v43 = v44;
  v48 = vcvts_n_s32_f32(v38, 7u);
  if ((f32)(v40 * 128.0) < 0.0)
    v47 = v46;
  v49 = vcvts_n_u32_f32(v38, 7u);
  if ((f32)(v38 * 128.0) >= 0.0)
    v48 = v49;
  v50 = v48 | (v47 << 24) | (u16)(v41 << 8) | (v43 << 16);
  v51 = h->Flag & 0xFFFFE7FF | 0x800;
  h->BaseAmbientRGB = v50;
  h->Flag = v51;
}

// 0x19bf7a0
void evtSetUnitLightAndAmbient3(evtUnitHandle_t *h, u32 frame, u32 lrgb0, u32 lrgb1, u32 lrgb2, u32 argb) {
  u16 v11;
  u32 NowLightRGB;
  f32 *v17;
  f32 v18;
  f32 v19;
  f32 v20;
  f32 v21;
  f32 w;
  f32 x;
  u32 v27;
  u32 v28;
  u8 v29;
  u8 v30;
  bool v31;
  float32x2_t v32;
  float32x2_t v33;
  int32x2_t v34;
  uint32x2_t v35;
  u64 v36;
  u32 NowLightRGB1;
  f32 *v39;
  f32 v40;
  f32 v41;
  f32 v42;
  f32 v43;
  f32 v47;
  f32 v48;
  u32 v49;
  u32 v50;
  u8 v51;
  u8 v52;
  float32x2_t v53;
  float32x2_t v54;
  int32x2_t v55;
  uint32x2_t v56;
  u64 v57;
  u32 NowLightRGB2;
  f32 *v60;
  f32 v61;
  f32 v62;
  f32 v63;
  f32 v64;
  f32 v68;
  f32 v69;
  u32 v70;
  u32 v71;
  f32 v72;
  u8 v73;
  u8 v74;
  float32x2_t v75;
  float32x2_t v76;
  int32x2_t v77;
  uint32x2_t v78;
  int32x2_t v79;
  u64 v80;
  f32 *p_x;
  f32 v83;
  f32 v84;
  f32 v85;
  f32 v86;
  u8 v87;
  u8 v88;
  u8 v89;
  u8 v90;
  f32 v91;
  u32 v92;
  u32 v93;
  u8 v94;
  u8 v95;
  u32 v96;
  s32 v97;
  sdfVector4_t v98;
  sdfVector4_t v99;
  sdfVector4_t v100;

  v11 = frame;
  h->LightRGBAnimeFrame = v11;
  h->TargetLightRGB = lrgb0;
  h->TargetAmbientRGB = argb;
  h->TargetLightRGB1 = lrgb1;
  h->TargetLightRGB2 = lrgb2;
  NowLightRGB = h->NowLightRGB;
  v17 = DirLights[0];
  v18 = v17[4];
  v19 = v17[5];
  v20 = v17[6];
  v21 = v17[7];
  v98.x = v18;
  v98.y = v19;
  v98.z = v20;
  v98.w = v21;
  GetBaseLightRGB_2(h, NowLightRGB, v98);
  w = vct_A.w;
  x = vct_A.x;
  v27 = vcvts_n_s32_f32(w, 7u);
  v28 = vcvts_n_u32_f32(w, 7u);
  v29 = vcvts_n_s32_f32(x, 7u);
  if ((f32)(w * 128.0) >= 0.0)
    v27 = v28;
  v30 = vcvts_n_u32_f32(x, 7u);
  v31 = (f32)(x * 128.0) < 0.0;
  v32.n64_u64[0] = *(u64 *)&vct_A.y;
  v33.n64_u64[0] = vmul_f32(v32, (float32x2_t)0x4300000043000000LL).n64_u64[0];
  v34.n64_u64[0] = vcvt_n_s32_f32(v32, 7u).n64_u64[0];
  v35.n64_u64[0] = vcvt_n_u32_f32(v32, 7u).n64_u64[0];
  if (v31)
    v30 = v29;
  v36 = vand_s8(vshl_u32(vbsl_s8(vcltz_f32(v33), v34, v35), (uint32x2_t)0x1000000008LL), (int8x8_t)0xFF00000000FF00LL).n64_u64[0];
  h->BaseLightRGB = v30 | (v27 << 24) | v36 | HIDWORD(v36);
  NowLightRGB1 = h->NowLightRGB1;
  v39 = DirLights[1];
  v40 = v39[4];
  v41 = v39[5];
  v42 = v39[6];
  v43 = v39[7];
  v99.x = v40;
  v99.y = v41;
  v99.z = v42;
  v99.w = v43;
  GetBaseLightRGB_2(h, NowLightRGB1, v99);
  v47 = vct_A.w;
  v48 = vct_A.x;
  v49 = vcvts_n_s32_f32(v47, 7u);
  v50 = vcvts_n_u32_f32(v47, 7u);
  if ((f32)(v47 * 128.0) >= 0.0)
    v49 = v50;
  v51 = vcvts_n_s32_f32(v48, 7u);
  v52 = vcvts_n_u32_f32(v48, 7u);
  v31 = (f32)(v48 * 128.0) < 0.0;
  v53.n64_u64[0] = *(u64 *)&vct_A.y;
  v54.n64_u64[0] = vmul_f32(v53, (float32x2_t)0x4300000043000000LL).n64_u64[0];
  v55.n64_u64[0] = vcvt_n_s32_f32(v53, 7u).n64_u64[0];
  v56.n64_u64[0] = vcvt_n_u32_f32(v53, 7u).n64_u64[0];
  if (v31)
    v52 = v51;
  v57 = vand_s8(vshl_u32(vbsl_s8(vcltz_f32(v54), v55, v56), (uint32x2_t)0x1000000008LL), (int8x8_t)0xFF00000000FF00LL).n64_u64[0];
  h->BaseLightRGB1 = v52 | (v49 << 24) | v57 | HIDWORD(v57);
  NowLightRGB2 = h->NowLightRGB2;
  v60 = DirLights[2];
  v61 = v60[4];
  v62 = v60[5];
  v63 = v60[6];
  v64 = v60[7];
  v100.x = v61;
  v100.y = v62;
  v100.z = v63;
  v100.w = v64;
  GetBaseLightRGB_2(h, NowLightRGB2, v100);
  v68 = vct_A.w;
  v69 = vct_A.x;
  v70 = vcvts_n_s32_f32(v68, 7u);
  v31 = (f32)(v68 * 128.0) < 0.0;
  v71 = vcvts_n_u32_f32(v68, 7u);
  v72 = v69 * 128.0;
  v73 = vcvts_n_u32_f32(v69, 7u);
  if (!v31)
    v70 = v71;
  v74 = vcvts_n_s32_f32(v69, 7u);
  v75.n64_u64[0] = *(u64 *)&vct_A.y;
  v31 = v72 < 0.0;
  v76.n64_u64[0] = vmul_f32(v75, (float32x2_t)0x4300000043000000LL).n64_u64[0];
  v77.n64_u64[0] = vcvt_n_s32_f32(v75, 7u).n64_u64[0];
  v78.n64_u64[0] = vcvt_n_u32_f32(v75, 7u).n64_u64[0];
  v79.n64_u64[0] = vcltz_f32(v76).n64_u64[0];
  if (!v31)
    v74 = v73;
  v80 = vand_s8(vshl_u32(vbsl_s8(v79, v77, v78), (uint32x2_t)0x1000000008LL), (int8x8_t)0xFF00000000FF00LL).n64_u64[0];
  h->BaseLightRGB2 = v74 | (v70 << 24) | v80 | HIDWORD(v80);
  GetBaseAmbientRGB(h);
  p_x = &vf00.x;
  v84 = p_x[4];
  v83 = p_x[5];
  v85 = p_x[6];
  v86 = p_x[7];
  v87 = vcvts_n_s32_f32(v83, 7u);
  v88 = vcvts_n_u32_f32(v83, 7u);
  v89 = vcvts_n_s32_f32(v85, 7u);
  v90 = vcvts_n_u32_f32(v85, 7u);
  v91 = v85 * 128.0;
  v92 = vcvts_n_s32_f32(v86, 7u);
  if ((f32)(v83 * 128.0) >= 0.0)
    v87 = v88;
  v93 = vcvts_n_u32_f32(v86, 7u);
  if (v91 >= 0.0)
    v89 = v90;
  v94 = vcvts_n_s32_f32(v84, 7u);
  if ((f32)(v86 * 128.0) < 0.0)
    v93 = v92;
  v95 = vcvts_n_u32_f32(v84, 7u);
  if ((f32)(v84 * 128.0) >= 0.0)
    v94 = v95;
  v96 = v94 | (v93 << 24) | (u16)(v87 << 8) | (v89 << 16);
  v97 = h->Flag & 0xFFFFE7FF | 0x800;
  h->BaseAmbientRGB = v96;
  h->Flag = v97;
}

// 0x19c9740
void evtSetUnitRim(evtUnitHandle_t *h, f32 _R, f32 _G, f32 _B, f32 _Pow) {
  h->NowRim.x = R;
  h->NowRim.y = G;
  h->NowRim.z = B;
  h->NowRim.w = Pow;
}

// 0x19bfd60
void evtSetUnitLightDir(evtUnitHandle_t *h, s32 frame) {
  u16 v3;
  sdfVector4_t *p_TargetLightDir;
  f32 x;
  f32 y;
  f32 w;
  f32 z;
  f32 *v17;
  f32 v18;
  f32 v19;
  f32 v20;
  f32 v21;
  sdfVector4_t v24;
  sdfVector4_t v25;

  v3 = frame;
  h->LightDirAnimeFrame = frame;
  vct_A.w = 0.0;
  sub_1949110(0);
  p_TargetLightDir = &h->TargetLightDir;
  *p_TargetLightDir = vct_A;
  x = h->NowLightDir.x;
  y = h->NowLightDir.y;
  z = h->NowLightDir.z;
  w = h->NowLightDir.w;
  v17 = DirLights[0];
  v18 = v17[8];
  v19 = v17[9];
  v20 = v17[10];
  v21 = v17[11];
  v24.x = x;
  v24.y = y;
  v24.z = z;
  v24.w = w;
  v25.x = v18;
  v25.y = v19;
  v25.z = v20;
  v25.w = v21;
  GetBaseLightDir_2(h, v24, v25);
  h->Flag = h->Flag & 0xFFFF9BFF | 0x2400;
  h->BaseLightDir = vct_A;
}

// 0x19c0000
void evtSetUnitLightDir1(evtUnitHandle_t *h, s32 frame) {
  u16 v3;
  sdfVector4_t *p_TargetLightDir1;
  f32 x;
  f32 y;
  f32 w;
  f32 z;
  f32 *v17;
  f32 v18;
  f32 v19;
  f32 v20;
  f32 v21;
  sdfVector4_t v24;
  sdfVector4_t v25;

  v3 = frame;
  h->LightDirAnimeFrame = frame;
  vct_A.w = 0.0;
  sub_1949110(0);
  p_TargetLightDir1 = &h->TargetLightDir1;
  *p_TargetLightDir1 = vct_A;
  x = h->NowLightDir1.x;
  y = h->NowLightDir1.y;
  z = h->NowLightDir1.z;
  w = h->NowLightDir1.w;
  v17 = DirLights[1];
  v18 = v17[8];
  v19 = v17[9];
  v20 = v17[10];
  v21 = v17[11];
  v24.x = x;
  v24.y = y;
  v24.z = z;
  v24.w = w;
  v25.x = v18;
  v25.y = v19;
  v25.z = v20;
  v25.w = v21;
  GetBaseLightDir_2(h, v24, v25);
  h->Flag = h->Flag & 0xFFFF9BFF | 0x2400;
  h->BaseLightDir1 = vct_A;
}

// 0x19c02a0
void evtSetUnitLightDir2(evtUnitHandle_t *h, s32 frame) {
  u16 v3;
  sdfVector4_t *p_TargetLightDir2;

  v3 = frame;
  h->LightDirAnimeFrame = frame;
  vct_A.w = 0.0;
  sub_1949110(0);
  p_TargetLightDir2 = &h->TargetLightDir2;
  *p_TargetLightDir2 = vct_A;
  GetBaseLightDir2(h);
  h->Flag = h->Flag & 0xFFFF9BFF | 0x2400;
  h->BaseLightDir2 = vct_A;
}

// 0x19c9760
void evtSetUnitColorRGB(evtUnitHandle_t *h, u32 frame, u32 rgb) {
  sdfVector4_t v9;

  v9.x = (f32)(u8)rgb * 0.0078125;
  *(float32x2_t *)&v9.y = vmul_f32(vcvt_f32_u32(vand_s8(vshl_u32(vdup_n_s32(rgb), (uint32x2_t)0xFFFFFFF0FFFFFFF8LL), (int8x8_t)0xFF000000FFLL)), (float32x2_t)0x3C0000003C000000LL);
  v9.w = (f32)HIBYTE(rgb) * 0.0078125;
  SetUnitColorRGB(h, frame, v9);
}

// 0x19c9860
void SetUnitColorRGB(evtUnitHandle_t *h, u32 frame, const sdfVector4_t *rgb) {
  f32 z;
  f32 y;
  f32 x;
  dds3ModelHandle_t *Model;
  s32 Flag;
  s32 v12;
  f32 v13;
  dds3ModelHandle_t *v14;
  s32 v15;
  f32 v16;
  f32 v17;
  f32 v18;
  f32 w;
  sdfVector4_t v20;
  sdfVector4_t v22;

  z = rgb->z;
  y = rgb->y;
  x = rgb->x;
  Model = h->Model;
  v20 = mdlGetColor(Model);
  v16 = v20.x;
  v17 = v20.y;
  v18 = v20.z;
  w = v20.w;
  h->ModelRGBAnimeMaxFrame = frame;
  h->ModelRGBAnimeFrame = 0;
  if (frame)
  {
    Flag = h->Flag;
    h->BaseModelRGBA.x = v16;
    h->BaseModelRGBA.y = v17;
    v12 = Flag | 0x8000;
    h->BaseModelRGBA.z = v18;
    h->TargetModelRGBA.x = x;
    h->TargetModelRGBA.y = y;
    h->TargetModelRGBA.z = z;
    goto LABEL_10;
  }
  v13 = w;
  v14 = h->Model;
  v22.x = x;
  v22.y = y;
  v22.z = z;
  v22.w = v13;
  SetColor(v14, v22);
  v15 = h->Flag;
  h->BaseModelRGBA.x = x;
  h->BaseModelRGBA.y = y;
  v12 = v15 & 0xFFFF7FFF;
  h->BaseModelRGBA.z = z;
LABEL_10:
  h->Flag = v12;
}

// 0x19c9990
void evtSetUnitColorA(evtUnitHandle_t *h, u32 frame, u32 a) {
  SetUnitColorA(h, frame, (f32)HIBYTE(a) * 0.0078125);
}

// 0x19c9a60
void SetUnitColorA(evtUnitHandle_t *h, u32 frame, f32 a) {
  dds3ModelHandle_t *Model;
  s32 Flag;
  s32 v10;
  f32 v11;
  f32 v12;
  dds3ModelHandle_t *v13;
  f32 v14;
  s32 v15;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  sdfVector4_t v20;
  sdfVector4_t v22;

  Model = h->Model;
  v20 = mdlGetColor(Model);
  x = v20.x;
  y = v20.y;
  z = v20.z;
  w = v20.w;
  h->ModelAAnimeMaxFrame = frame;
  h->ModelAAnimeFrame = 0;
  if (frame)
  {
    Flag = h->Flag;
    h->BaseModelRGBA.w = w;
    h->TargetModelRGBA.w = a;
    v10 = Flag | 0x10000;
    goto LABEL_10;
  }
  v11 = x;
  v12 = y;
  v13 = h->Model;
  v14 = z;
  v22.x = v11;
  v22.y = v12;
  v22.z = v14;
  v22.w = a;
  SetColor(v13, v22);
  mdlSetDitherAlphaUse(h->Model, 1);
  v15 = h->Flag;
  h->BaseModelRGBA.w = a;
  v10 = v15 & 0xFFFEFFFF;
LABEL_10:
  h->Flag = v10;
}

// 0x19c9b90
bool evtUnitLightAnimeStat(evtUnitHandle_t *h) {
  return (h->Flag & 0x7800) != 0;
}

// 0x19bf090
void evtUnitLightOn(evtUnitHandle_t *h) {
  h->Flag |= 0x300u;
}

// 0x19c9ba0
void evtUnitLightOff(evtUnitHandle_t *h, s32 frame) {
  if (frame)
  {
    evtSetUnitLightAndAmbient(h, frame, 0, 0);
    h->Flag = h->Flag & 0xFFFFE7FF | 0x1000;
    vct_A = vf00;
    evtSetUnitLightDir(h, frame);
    h->Flag = h->Flag & 0xFFFF9FFF | 0x4000;
    return;
  }
  h->Flag &= 0xFFFF80FF;
}

// 0x19b71f0
evtUnitHandle_t *evtGetUnitHandle(s32 serialID) {
  evtUnitHandle_t *result;
  evtUnitHandle_t *v6;
  s64 naturalAligment;
  dds3Basic_t *pBasic;

  pBasic = dds3GetActiveScene();
  result = (evtUnitHandle_t *)dds3SceneBasicSearch(pBasic, serialID, 5u);
  if (!result)
    return result;
  v6 = *(evtUnitHandle_t ***)&result->BaseLightDir.x;
  if (v6)
  {
    LOBYTE(v6->TargetModelRGBA.x) < (u32)naturalAligment || *(Project_Basic_dds3UnitObjectBasicWorkData_t_c **)(*(u64 *)&v6->NowLightDir2.z + 8 * naturalAligment - 8) != Project_Basic_dds3UnitObjectBasicWorkData_t;
  }
  return v6[4];
}

// 0x19be470
evtUnitHandle_t *evtGetUnitHandle2(dds3Basic_t *unit) {
  evtUnitHandle_t *workdata;
  s64 naturalAligment;

  if (!unit)
    return 0;
  workdata = (evtUnitHandle_t *)(unit)->workdata;
  if (workdata)
  {
    LOBYTE(workdata->TargetModelRGBA.x) < (u32)naturalAligment || *(Project_Basic_dds3UnitObjectBasicWorkData_t_c **)(*(u64 *)&workdata->NowLightDir2.z + 8 * naturalAligment - 8) != Project_Basic_dds3UnitObjectBasicWorkData_t;
  }
  return workdata[4];
}

// 0x19c9ce0
evtUnitHandle_t *evtCreateUnitHandle(dds3Basic_t *owner, dds3ModelHandle_t *model) {
  evtUnitHandle_t *v5;
  dds3Basic_t *v6;
  s32 v8;
  sdfVector4_t *v9;
  sdfVector4_t *v10;
  s32 v11;
  s32 v13;
  sdfVector4_t *v14;
  sdfVector4_t *v15;
  s32 v17;
  sdfVector4_t *v18;
  struct sdfVector4_t v23;
  sdf3DLightParallelPacket_t *v24;

  v5 = Allocate(evtUnitHandle_t);
  _ctor(v5, 0);
  *(u32 *)&v5->Stat = 0x10000;
  *(u32 *)&v5->WaitSpeed = 1056964608;
  *(u32 *)&v5->WaitBefore = 655360;
  *(u32 *)&v5->NowBefore = 655360;
  v6 = owner;
  v5->Owner = owner;
  v5->Model = model;
  v8 = (u8)byte_5755EF6;
  vct_A = (struct sdfVector4_t)xmmword_3D064D0;
  if (v8)
  {
    v9 = &v5->NowLightDir;
    goto LABEL_9;
  }
  else
  {
    v9 = &v5->NowLightDir;
LABEL_9:
    *v9 = vct_A;
    v10 = &v5->WorkLightDir;
    goto LABEL_18;
  }
  v11 = (u8)byte_5755EF6;
  *v9 = vct_A;
  if (v11)
  {
    v10 = &v5->WorkLightDir;
    goto LABEL_18;
  }
  v10 = &v5->WorkLightDir;
LABEL_18:
  v5->WorkAmbientRGB = -2144325584;
  v5->NowAmbientRGB = -2144325584;
  v5->WorkLightRGB = 11711154;
  v5->NowLightRGB = 11711154;
  v13 = (u8)byte_5755EF5;
  *v10 = vct_A;
  if (v13)
  {
    goto LABEL_20;
  }
  else
  {
LABEL_20:
    vct_A = (struct sdfVector4_t)xmmword_3D004F0;
    goto LABEL_21;
  }
  vct_A = (struct sdfVector4_t)xmmword_3D004F0;
LABEL_21:
  v14 = &v5->NowLightDir1;
  goto LABEL_22;
LABEL_29:
  v17 = (u8)byte_5755EF5;
  *v15 = vct_A;
  if (!v17)
    goto LABEL_39;
LABEL_31:
  vct_A = (struct sdfVector4_t)xmmword_3CFE6D0;
  v18 = &v5->NowLightDir2;
  *v18 = vct_A;
  goto LABEL_45;
LABEL_22:
  *v14 = vct_A;
  v15 = &v5->WorkLightDir1;
  goto LABEL_29;
LABEL_39:
  goto LABEL_31;
LABEL_45:
  v23 = vct_A;
  v5->WorkLightRGB1 = 0;
  v5->NowLightRGB1 = 0;
  v5->WorkLightRGB2 = 0;
  v5->NowLightRGB2 = 0;
  v5->WorkLightDir2 = v23;
  v24 = Allocate(sdf3DLightParallelPacket_t);
  _ctor(v24, 0);
  v5->PrivateLightPacket = v24;
  v5->PublicLightPacket = 0;
  __asm { FMOV            V0.4S, #1.0 }
  *(u64 *)&v5->LookRotFlag = 0;
  v5->MapLightUse = 0;
  *(_OWORD *)&v5->NowRim = _Q0;
  return v5;
}

// 0x19ca180
bool evtDeleteUnitHandle(evtUnitHandle_t *h) {
  dds3ModelHandle_t *Model;
  evtUnitHandle_t *v4;
  dds3PathBasicControl_t *p_Path;
  dds3PathBasicControl_t *v6;

  if (h)
  {
    Model = h->Model;
    mdlSetLight(Model, 0);
    v4 = h;
    if (h->PrivateLightPacket)
    {
      v4->PrivateLightPacket = 0;
      v4 = h;
    }
    if (v4->Path)
    {
      p_Path = &v4->Path;
      dds3PathBasicFreeControl(p_Path);
      v6 = &h->Path;
      v6 = 0;
    }
  }
  return 1;
}

// 0x19ca270
EVT_UNIT_STAT evtGetUnitStat(evtUnitHandle_t *h) {
  return h->Stat;
}

// 0x19ca280
EVT_UNIT_STAT evtSetUnitStat(evtUnitHandle_t *h, EVT_UNIT_STAT stat) {
  h->Stat = stat;
  return stat;
}

// 0x19ca290
void evtSetWaitMotion(evtUnitHandle_t *h, s32 motion) {
  h->WaitMotion = motion;
}

// 0x19ca2a0
void evtSetWaitMotionSpeed(evtUnitHandle_t *h, f32 sp) {
  h->WaitSpeed = sp;
}

// 0x19ca2b0
void evtSetWaitHokanFrame(evtUnitHandle_t *h, s32 before, s32 smooth) {
  h->WaitBefore = before;
  h->WaitSmooth = smooth;
}

// 0x19ca2c0
bool evtCheckUnitWait(evtUnitHandle_t *h) {
  s32 Stat;
  dds3ModelHandle_t *Model;

  Stat = (u16)h->Stat;
  if (!h->Stat)
    return 1;
  if (Stat == 2 && h->Frame >= 1)
  {
    Model = h->Model;
    if (mdlChkMotionEnd(Model))
      return 1;
  }
  return 0;
}

// 0x19ca3c0
void evtSetUnitKutiMotion(evtUnitHandle_t *h, s32 group, s32 motion) {
  h->KutiGroup = group;
  h->KutiMotion = motion;
}

// 0x19ca3d0
void evtRunUnitKutiMotion(evtUnitHandle_t *h) {
  ;
}

// 0x19ca3e0
void evtSetUnitExMotion(evtUnitHandle_t *h, s32 group, s32 motion, s32 before, s32 smooth, EVT_MOT mode, s32 frameLimit) {
  u64 v8;
  char *v9;
  s16 *ExSmooth;

  h->ExFlags[group] = 3;
  v8 = group;
  v9 = (char *)h->ExBefore + v8 * 2;
  h->ExNowMotion[v8] = motion;
  ExSmooth = h->ExSmooth;
  *((u16 *)v9 + 16) = before;
  ExSmooth[v8] = smooth;
  if (frameLimit < 1)
  {
    h->ExLoopEndTime[group] = 0.0;
    if ((u32)mode > 4)
      return;
  }
  else
  {
    h->ExLoopEndTime[group] = (f32)frameLimit / 60.0;
    if ((u32)mode > 4)
      return;
  }
  if (((0x17u >> mode) & 1) != 0)
    h->ExFlags[group] |= 0x2004100804uLL >> (8 * (u8)mode);
}

// 0x19ca4a0
void evtSetUnitMotion(evtUnitHandle_t *h, s32 motion, s32 before, s32 smooth, EVT_MOT mode, s32 frameLimit) {
  s16 v10;
  s16 v11;
  f32 v12;
  s32 Flag;
  u32 v14;

  h->Frame = 0;
  h->Stat = 2;
  h->NowMotion = motion;
  v10 = smooth;
  v11 = before;
  h->Action = 0;
  h->NowBefore = v11;
  h->NowSmooth = v10;
  if (frameLimit < 1)
    v12 = 0.0;
  else
    v12 = (f32)frameLimit / 60.0;
  Flag = h->Flag;
  h->LoopEndTime = v12;
  v14 = Flag & 0xFD3FFF1E;
  h->Flag = v14 | 0x80;
  if ((u32)mode <= 4 && ((0x1Bu >> mode) & 1) != 0)
    h->Flag = v14 | dword_3E60998[mode];
}

// 0x19ca570
bool evtUnitRotationTarget(evtUnitHandle_t *h, const sdfVector4_t *pos, f32 radio) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  s32 v15;
  int32x2_t v17;
  int32x2_t v18;
  float32x2_t v19;
  float32x2_t v20;
  float32x2_t v23;
  f32 v24;
  f32 v25;
  f32 v26;
  float32x2_t v28;
  f32 v29;
  f32 v30;
  f32 v31;
  f32 v32;
  f32 v33;
  f32 v35;
  f32 v36;
  f32 v37;
  f32 v39;
  dds3Basic_t *p_Owner;
  f32 *p_x;
  f32 v45;
  f32 v46;
  f32 v47;
  f32 v48;
  sdfVector4_t v52;

  w = pos->w;
  z = pos->z;
  y = pos->y;
  x = pos->x;
  (loc_19D0580)(h, 0);
  vct_C = vct_A;
  (loc_19D0380)(0, x, y, z, w, h->Owner->poseset->pos.x, h->Owner->poseset->pos.y, h->Owner->poseset->pos.z, h->Owner->poseset->pos.w);
  sub_1949110(0);
  v15 = (u8)byte_5756431;
  vct_B = (struct sdfVector4_t)xmmword_3D015F0;
  if (v15)
  {
    goto LABEL_14;
  }
  else
  {
    goto LABEL_14;
  }
LABEL_14:
  v17.n64_u64[0] = *(u64 *)&vct_B.y;
  v18.n64_u64[0] = *(u64 *)&vct_A.y;
  v19.n64_u32[0] = vdup_lane_s32(v17, 1).n64_u32[0];
  v20.n64_u32[0] = vdup_lane_s32(v18, 1).n64_u32[0];
  v19.n64_u32[1] = LODWORD(vct_B.x);
  v20.n64_u32[1] = LODWORD(vct_A.x);
  vct_A.z = (f32)(v20.n64_f32[1] * v17.n64_f32[0]) - (f32)(v19.n64_f32[1] * v18.n64_f32[0]);
  *(float32x2_t *)&vct_A.x = vsub_f32(vmul_f32(v18, v19), vmul_f32(v20, v17));
  sub_1949110(0);
  vct_B = vct_C;
  v23.n64_u64[0] = vmul_f32(*(float32x2_t *)&vct_A.y, *(float32x2_t *)&vct_B.y).n64_u64[0];
  v24 = v23.n64_f32[1] + (f32)((f32)(vct_A.x * vct_B.x) + v23.n64_f32[0]);
  if (v24 <= 1.0)
    v25 = v23.n64_f32[1] + (f32)((f32)(vct_A.x * vct_B.x) + v23.n64_f32[0]);
  else
    v25 = 1.0;
  if (v24 >= -1.0)
    v26 = v25;
  else
    v26 = -1.0;
  v28.n64_u64[0] = vmul_f32(*(float32x2_t *)&vct_A.y, *(float32x2_t *)&vct_B.y).n64_u64[0];
  v29 = v28.n64_f32[1] + (f32)((f32)(vct_A.x * vct_B.x) + v28.n64_f32[0]);
  if (v29 <= 1.0)
    v30 = v28.n64_f32[1] + (f32)((f32)(vct_A.x * vct_B.x) + v28.n64_f32[0]);
  else
    v30 = 1.0;
  if (v29 >= -1.0)
    v31 = v30;
  else
    v31 = -1.0;
  if (v31 >= 0.9998)
    return v31 >= 0.9998;
  v32 = fabsf(v31);
  v33 = vabds_f32(-1.0, v31);
  if (v32 <= 1.0)
    v35 = 0.000001;
  else
    v35 = v32 * 0.000001;
  if (v35 <= (f32)(Epsilon * 8.0))
    v36 = Epsilon * 8.0;
  else
    v36 = v35;
  v37 = sub_188E3F0(v31);
  if (v33 < v36 || v26 > 0.0)
    v37 = -v37;
  v39 = v37 * radio;
  if ((h->Flag & 0x200000) == 0)
  {
    if (v39 < -0.15707964)
      v39 = -0.15707964;
    if (v39 > 0.15707964)
      v39 = 0.15707964;
  }
  vct_A = (struct sdfVector4_t)xmmword_3D015F0;
  FromRotation(v39);
  p_Owner = &h->Owner;
  p_x = &vf00.x;
  v45 = p_x[4];
  v46 = p_x[5];
  v47 = p_x[6];
  v48 = p_x[7];
  v52.x = v45;
  v52.y = v46;
  v52.z = v47;
  v52.w = v48;
  dds3AddRotPoseSet(p_Owner, v52);
  return v31 >= 0.9998;
}

// 0x19cac40
bool evtUnitRotationQuat(evtUnitHandle_t *h, const sdfVector4_t *rot, f32 radio) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  f32 *p_x;
  struct sdfVector4_t pos;
  f32 *v18;
  f32 v20;
  f32 v21;
  f32 v22;
  f32 v23;
  sdfVector4_t Row;
  sdfVector4_t v29;

  w = rot->w;
  z = rot->z;
  y = rot->y;
  x = rot->x;
  p_x = &vf00.x;
  p_x[4] = x;
  p_x[5] = y;
  p_x[6] = z;
  p_x[7] = w;
  ToMatrix();
  Row = GetRow(&mtx_A, 2, 0);
  vct_A = Row;
  vct_A.y = 0.0;
  vct_A.w = 0.0;
  sub_1949110(0);
  vct_A = (struct sdfVector4_t)vnegq_f32((float32x4_t)vct_A);
  pos = h->Owner->poseset->pos;
  vct_B = pos;
  vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  v18 = &vf00.x;
  v20 = v18[4];
  v21 = v18[5];
  v22 = v18[6];
  v23 = v18[7];
  v29.x = v20;
  v29.y = v21;
  v29.z = v22;
  v29.w = v23;
  return evtUnitRotationTarget(h, v29, radio);
}

// 0x19cb000
bool evtUnitMoveType0(evtUnitHandle_t *h) {
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  s16 MovePara2;
  s16 MovePara1;
  f32 v10;
  f32 v12;
  f32 *p_x;
  dds3Basic_t *p_Owner;
  f32 v15;
  f32 v16;
  f32 v17;
  f32 v18;
  dds3PoseSet_t *poseset;
  s64 v21;
  s64 v22;
  void *v23;
  struct sdfVector4_t pos;
  struct sdfVector4_t PosTarget;
  sdfVector3_t v32;
  sdfVector4_t v33;
  sdfVector4_t v34;

  x = h->PosTarget.x;
  y = h->PosTarget.y;
  z = h->PosTarget.z;
  w = h->PosTarget.w;
  MovePara2 = h->MovePara2;
  v33.z = z;
  v33.w = w;
  v33.x = x;
  v33.y = y;
  evtUnitRotationTarget(h, v33, (f32)MovePara2 * 0.01);
  if (h->MovePara2)
  {
    (loc_19D0580)(h, 0);
    MovePara1 = h->MovePara1;
    goto LABEL_10;
  }
  PosTarget = h->PosTarget;
  vct_A = PosTarget;
  pos = h->Owner->poseset->pos;
  vct_B = pos;
  vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  sub_1949110(0);
  MovePara1 = h->MovePara1;
LABEL_10:
  v10 = MovePara1;
  v12 = v10 * 0.1;
  vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v12);
  p_x = &vf00.x;
  p_Owner = &h->Owner;
  v15 = p_x[4];
  v16 = p_x[5];
  v17 = p_x[6];
  v18 = p_x[7];
  v34.x = v15;
  v34.y = v16;
  v34.z = v17;
  v34.w = v18;
  dds3AddPosPoseSet(&h->Owner, v34);
  if (IsEvtMoveCollisionCheck)
  {
    poseset = p_Owner->poseset;
    v21 = *((u64 *)Method_AtlUtil_AtSingleton_AtlFieldCollisionManager__get_Instance__ + 4);
    if ((*(u16 *)(v21 + 309) & 1) == 0)
      v21 = sub_42269C(v21);
    v22 = *(u64 *)(*(u64 *)(v21 + 192) + 16);
    if ((*(u16 *)(v22 + 309) & 1) == 0)
      v22 = sub_42269C(v22);
    v23 = **(void ***)(v22 + 184);
    v32 = *(sdfVector3_t *)&p_Owner->poseset->pos.x;
    if (v23)
      v32 = CalcGroundPos(v23, v32, 0);
    *(sdfVector3_t *)&poseset->pos.x = v32;
    poseset->pos.w = 0.0;
  }
  if (GBWK->GameFileInfo->chapter != 9)
    return 1;
  if (evtBitCheck(176) && !evtBitCheck(177))
  {
    evtUnitHeightCorrection(h);
  }
  return 1;
}

// 0x19cb4a0
void evtUnitHeightCorrection(evtUnitHandle_t *h) {
  dds3PoseSet_t *poseset;
  f32 x;
  f32 y;
  f32 z;
  dds3PoseSet_t *v7;
  f32 v8;
  f32 v9;

  poseset = h->Owner->poseset;
  x = poseset->pos.x;
  y = poseset->pos.y;
  z = poseset->pos.z;
  if (y <= mapGetY(x, z))
    return;
  v7 = h->Owner->poseset;
  v8 = v7->pos.x;
  v9 = v7->pos.z;
  v7->pos.y = mapGetY(v8, v9);
}

// 0x19cb5a0
s32 evtCalcFrame_UnitMoveType0(evtUnitHandle_t *org_h) {
  evtUnitHandle_t *v3;
  dds3PoseSet_t *poseset;
  f32 y;
  f32 x;
  f32 z;
  f32 w;
  evtUnitHandle_t *v10;
  s32 i;
  dds3PoseSet_t *v13;
  struct sdfVector4_t v15;
  f32 v16;
  f32 v17;
  struct sdfVector4_t pos;
  struct sdfVector4_t PosTarget;

  v3 = Allocate(evtUnitHandle_t);
  _ctor(v3, 0);
  poseset = org_h->Owner->poseset;
  x = poseset->rot.x;
  y = poseset->rot.y;
  z = poseset->rot.z;
  w = poseset->rot.w;
  pos = poseset->pos;
  v10 = Clone(org_h, 0);
  for (i = 0; ; ++i)
  {
    if (CheckMoveEnd(v10))
      break;
    evtUnitMoveType0(v10);
  }
  v13 = org_h->Owner->poseset;
  v13->rot.x = x;
  v13->rot.y = y;
  v13->rot.z = z;
  v13->pos = pos;
  v13->rot.w = w;
  if (!i)
  {
    org_h->YMoveFrameMax = 0;
    v17 = 0.0;
    goto LABEL_22;
  }
  PosTarget = org_h->PosTarget;
  vct_A = PosTarget;
  v15 = org_h->Owner->poseset->pos;
  vct_B = v15;
  vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  v16 = vct_A.y;
  org_h->YMoveFrameMax = i;
  v17 = v16 / (f32)i;
LABEL_22:
  org_h->YMoveAddValue = v17;
  return i;
}

// 0x19cb870
bool evtUnitMoveTypePathTrace(evtUnitHandle_t *h) {
  dds3PathBasicControl_t *Path;
  f32 *p_x;
  f32 v6;
  f32 v7;
  f32 v8;
  f32 v9;
  f32 *v13;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  sdfVector4_t v21;
  sdfVector4_t v22;

  Path = h->Path;
  dds3PathBasicControlNextStep(Path);
  dds3PathBasicControlGetPos(&h->Path);
  p_x = &vf00.x;
  v6 = p_x[4];
  v7 = p_x[5];
  v8 = p_x[6];
  v9 = p_x[7];
  v21.x = v6;
  v21.y = v7;
  v21.z = v8;
  v21.w = v9;
  dds3SetPosPoseSet(&h->Owner, v21);
  if ((h->Flag & 0x10) != 0)
  {
    dds3PathBasicControlGetRot(&h->Path);
    vct_B = vct_A;
    FromEuler(0.0, 3.1415927, 0.0);
    Mult();
    v13 = &vf00.x;
    x = v13[4];
    y = v13[5];
    z = v13[6];
    w = v13[7];
    v22.x = x;
    v22.y = y;
    v22.z = z;
    v22.w = w;
    dds3SetRotPoseSet(&h->Owner, v22);
    return 1;
  }
  return 1;
}

// 0x19cbb40
void evtSetUnitMovePos(evtUnitHandle_t *h, const sdfVector4_t *pos) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;

  w = pos->w;
  z = pos->z;
  y = pos->y;
  x = pos->x;
  h->PosTarget.z = z;
  h->PosTarget.w = w;
  h->PosTarget.x = x;
  h->PosTarget.y = y;
}

// 0x19cbbd0
void evtSetUnitRot1(evtUnitHandle_t *h, const sdfVector4_t *rot, s32 para1) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;

  w = rot->w;
  z = rot->z;
  y = rot->y;
  x = rot->x;
  if ((u32)(para1 - 1) > 0x63)
    return;
  h->Stat = 3;
  h->MoveTarget = 0;
  h->PosTarget.x = x;
  h->PosTarget.y = y;
  h->PosTarget.z = z;
  h->PosTarget.w = w;
  h->MovePara1 = para1;
  h->MovePara2 = 0;
  h->Action = 0;
  h->Frame = 0;
}

// 0x19cbcd0
void evtSetUnitRot2(evtUnitHandle_t *h, s32 posID, s32 para1) {
  dds3Basic_t *v9;
  dds3Basic_t *v10;
  void *workdata;
  struct sdfVector4_t v13;
  dds3Basic_t *pBasic;

  pBasic = dds3GetControlScene();
  v9 = dds3SceneBasicSearch(pBasic, posID, 0x10u);
  if (!v9)
    return;
  v10 = v9;
  workdata = v9->workdata;
  v13 = (struct sdfVector4_t)workdata[2];
  if ((u32)(para1 - 1) > 0x63)
    goto LABEL_21;
  goto LABEL_18;
  if ((u32)(para1 - 1) > 0x63)
  {
LABEL_21:
    h->MoveTarget = v10;
    return;
  }
LABEL_18:
  h->MoveTarget = 0;
  h->Stat = 3;
  h->MovePara1 = para1;
  h->MovePara2 = 0;
  h->Action = 0;
  h->PosTarget = v13;
  h->Frame = 0;
  goto LABEL_21;
}

// 0x19cbf10
void evtSetUnitMove1(evtUnitHandle_t *h, EVT_UNIT_MOVE_TYPE movetype, const sdfVector4_t *pos, s32 motion, s32 para1, s32 para2, ActionDelegate func, void *data) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  s16 v14;
  s16 v15;

  w = pos->w;
  z = pos->z;
  y = pos->y;
  x = pos->x;
  v14 = para2;
  v15 = para1;
  h->counter = 0;
  *(u32 *)&h->Stat = 1;
  h->MoveType = movetype;
  h->MoveTarget = 0;
  h->PosTarget.x = x;
  h->PosTarget.y = y;
  h->PosTarget.z = z;
  h->PosTarget.w = w;
  h->MovePara1 = v15;
  h->MovePara2 = v14;
  h->Action = func;
  h->Frame = 0;
}

// 0x19cc000
void evtSetUnitMove2(evtUnitHandle_t *h, EVT_UNIT_MOVE_TYPE movetype, s32 posID, s32 motion, s32 para1, s32 para2, ActionDelegate func, void *data) {
  s16 v10;
  s16 v11;
  dds3Basic_t *v17;
  dds3Basic_t *v18;
  void *workdata;
  struct sdfVector4_t v21;
  dds3Basic_t *pBasic;

  v10 = para2;
  v11 = para1;
  pBasic = dds3GetControlScene();
  v17 = dds3SceneBasicSearch(pBasic, posID, 0x10u);
  if (!v17)
    return;
  v18 = v17;
  workdata = v17->workdata;
  v21 = (struct sdfVector4_t)workdata[1];
  h->MoveType = movetype;
  h->counter = 0;
  *(u32 *)&h->Stat = 1;
  h->MoveTarget = 0;
  h->MovePara1 = v11;
  h->MovePara2 = v10;
  h->Action = func;
  h->PosTarget = v21;
  h->Frame = 0;
  h->TargetType = 1;
  h->MoveTarget = v18;
}

// 0x19cc240
void evtSetUnitMove3(evtUnitHandle_t *h, s32 pathID, s32 para1, s32 para2, s32 movesys, s32 movedir, s32 rotsys) {
  s16 v11;
  s16 v12;
  dds3PathBasicControl_t *Control;
  f32 SplineLength;
  s16 v22;
  s32 v23;
  s32 v24;
  dds3Basic_t *v25;
  sdfVector4_t *p_PosTarget;
  void *object;
  dds3Basic_t *pBasic;
  dds3PathBasicControl_t *path;

  v11 = para2;
  v12 = para1;
  path = 0;
  pBasic = dds3GetControlScene();
  object = dds3SceneBasicSearch(pBasic, pathID, 0xFu);
  if (!object)
    return;
  if (h->Path)
  {
    dds3PathBasicFreeControl(&h->Path);
  }
  Control = dds3PathBasicMakeControl(object);
  path = Control;
  h->Path = Control;
  SplineLength = GetSplineLength(path);
  h->PathStep = 40.0 / SplineLength;
  if (!movedir)
  {
    dds3PathBasicControlSetRatio(path, 0.0);
    dds3PathBasicControlAlterMode(path, 0);
    if (movesys != 1)
      goto LABEL_18;
LABEL_26:
    h->Flag |= 2u;
    v22 = 3;
    goto LABEL_27;
  }
  dds3PathBasicControlSetRatio(path, 1.0);
  dds3PathBasicControlAlterMode(path, 1);
  h->PathStep = -h->PathStep;
  if (movesys == 1)
    goto LABEL_26;
LABEL_18:
  if (movesys)
    goto LABEL_28;
  v22 = 0;
  h->Flag &= ~2u;
LABEL_27:
  h->MoveType = v22;
LABEL_28:
  if (movedir)
  {
    if (movedir != 1)
      goto LABEL_33;
    v23 = h->Flag | 4;
  }
  else
  {
    v23 = h->Flag & 0xFFFFFFFB;
  }
  h->Flag = v23;
LABEL_33:
  if (rotsys == 2)
  {
    v24 = h->Flag & 0xFFFFFFE7 | 0x10;
  }
  else if (rotsys == 1)
  {
    v24 = h->Flag & 0xFFFFFFE7 | 8;
  }
  else
  {
    if (rotsys)
      goto LABEL_40;
    v24 = h->Flag & 0xFFFFFFE7;
  }
  h->Flag = v24;
LABEL_40:
  v25 = object;
  *(u32 *)&h->Stat = 131073;
  h->counter = 0;
  h->MoveTarget = v25;
  dds3PathBasicControlGetPos(path);
  p_PosTarget = &h->PosTarget;
  h->MovePara1 = v12;
  h->MovePara2 = v11;
  h->Action = 0;
  *p_PosTarget = vct_A;
  h->Frame = 0;
}

// 0x19cc600
static bool CheckMoveEndBustup(evtUnitHandle_t *h) {
  return h->MovePara1 == 0;
}

// 0x19cc610
static bool UnitMoveTypeBustup(evtUnitHandle_t *h) {
  s32 MovePara1;
  struct sdfVector4_t PosTarget;
  s16 MovePara2;
  struct sdfVector4_t MoveStartPos;
  f32 v8;
  f32 v9;
  struct sdfVector4_t v10;
  f32 *p_x;
  dds3Basic_t *p_Owner;
  f32 v13;
  f32 v14;
  f32 v15;
  f32 v16;
  struct sdfVector4_t v18;
  sdfVector4_t v24;

  MovePara1 = (u16)h->MovePara1;
  if (h->MovePara1)
  {
    PosTarget = h->PosTarget;
    h->MovePara1 = MovePara1 - 1;
    MovePara2 = h->MovePara2;
    v18 = PosTarget;
    vct_A = v18;
    MoveStartPos = h->MoveStartPos;
    vct_B = MoveStartPos;
    vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    v8 = (f32)(s16)(MovePara1 - 1) / (f32)MovePara2;
    v9 = 1.0 - v8;
    vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v9);
    v10 = h->MoveStartPos;
    vct_B = v10;
    vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    p_x = &vf00.x;
    p_Owner = &h->Owner;
    v13 = p_x[4];
    v14 = p_x[5];
    v15 = p_x[6];
    v16 = p_x[7];
    v24.x = v13;
    v24.y = v14;
    v24.z = v15;
    v24.w = v16;
    dds3SetPosPoseSet(p_Owner, v24);
    return MovePara1 != 0;
  }
  return MovePara1 != 0;
}

// 0x19cc990
void evtSetUnitMoveBustup(evtUnitHandle_t *h, const sdfVector4_t *start_pos, const sdfVector4_t *pos, f32 rate, s32 motion, s32 frame, s32 outmode) {
  f32 z;
  f32 y;
  f32 x;
  f32 v11;
  f32 v12;
  f32 v13;
  f32 v14;
  s32 Flag;
  f32 v18;
  s32 v19;
  f32 w;

  w = pos->w;
  z = pos->z;
  y = pos->y;
  x = pos->x;
  v11 = start_pos->w;
  v12 = start_pos->z;
  v13 = start_pos->y;
  v14 = start_pos->x;
  Flag = h->Flag;
  *(u32 *)&h->TargetType = 0;
  h->MoveTarget = 0;
  h->Flag = Flag | 0x1000000;
  h->MoveStartPos.x = v14;
  h->MoveStartPos.y = v13;
  h->MoveStartPos.z = v12;
  h->MoveStartPos.w = v11;
  v18 = (f32)(1.0 - rate) * (f32)frame;
  h->PosTarget.x = x;
  h->PosTarget.y = y;
  h->PosTarget.z = z;
  h->MovePara2 = frame;
  h->Action = 0;
  v19 = v18;
  h->PosTarget.w = w;
  if (v18 == INFINITY)
    LOWORD(v19) = 0;
  h->MovePara1 = v19;
  h->Frame = 0;
}

// 0x19ccad0
bool evtSetUnitAction(evtUnitHandle_t *h, ActionDelegate func, void *data) {
  if (func)
  {
    h->Frame = 0;
    h->Stat = 4;
    h->Action = func;
  }
  return func != 0;
}

// 0x19ccb20
bool evtUnitManagerPrimaryFunc(dds3PoseSet_t *pose, dds3Basic_t *basic) {
  dds3Basic_t *v3;
  void *workdata;
  evtUnitHandle_t *klass;
  dds3ModelHandle_t *Model;
  s32 fieldID;
  s32 Light;
  s32 Flag;
  s32 WaitMotion;
  s32 v14;
  sdfMotionCtrlr_t *motions;
  s32 v17;
  s16 WaitBefore;
  s16 WaitSmooth;
  dds3Basic_t *Owner;
  dds3PoseSet_t *poseset;
  f32 v22;
  f32 v23;
  s32 v24;
  s32 v25;
  s32 MotionFrame;
  f32 LoopEndTime;
  sdfMotionCtrlr_t *v28;
  s32 v30;
  s16 v31;
  s16 v32;
  s32 v33;
  u32 v34;
  ActionDelegate v35;
  s32 NowBefore;
  s32 NowMotion;
  s32 NowSmooth;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  s16 MovePara1;
  s32 v46;
  u32 MoveType;
  bool v48;
  u32 v49;
  s32 v50;
  s16 v51;
  s16 v52;
  u32 v53;
  s32 v54;
  s16 v55;
  s16 v56;
  u32 v57;
  bool v58;
  f32 YMoveAddValue;
  ActionDelegate Action;
  f32 v61;
  s64 i;
  char *v63;
  s32 v64;
  s32 v65;
  u32 v66;
  s32 v67;
  s32 v69;
  bool v70;
  EVT_EXMOT *ExFlags;
  s32 v73;
  s16 v74;
  s16 v75;
  s64 v76;
  f32 *ExLoopEndTime;
  s64 v78;
  f32 v79;
  s32 v81;
  s16 v82;
  s16 v83;
  s64 v84;
  f32 v85;
  s32 Frame;
  s32 MoveTimer;
  s32 StopTimer;
  s32 v92;
  s32 v94;
  s16 v95;
  s16 v96;
  s32 v97;
  sdfVector4_t v98;
  sdfVector4_t v99;

  v3 = basic;
  workdata = v3->workdata;
  klass = workdata[2].klass;
  if (!klass)
    return 0;
  Model = klass->Model;
  if (klass->MapLightUse)
  {
    fieldID = fldGb->fieldID;
    Light = mapGetLight(v3->poseset->pos.x, v3->poseset->pos.z);
    if (GetFldLightTable(LightDataTbl, fieldID, Light, 0))
    {
      mapUnitSetLight(v3, Light, 0);
    }
  }
  UnitAnime(klass);
  switch (klass->Stat)
  {
    case 0:
    case 3:
      Flag = klass->Flag;
      if ((Flag & 0x80) != 0)
      {
        NowBefore = klass->NowBefore;
        NowMotion = klass->NowMotion;
        NowSmooth = klass->NowSmooth;
        if ((Flag & 1) != 0)
        {
          mdlSmoothLoopMotion(Model, 0, NowMotion, (f32)NowBefore, (f32)NowSmooth, 0.0);
        }
        else
        {
          mdlSmoothSingleMotion(Model, 0, NowMotion, (f32)NowBefore, (f32)NowSmooth, 0.0);
        }
        klass->Flag &= ~0x80u;
        goto LABEL_67;
      }
      if ((Flag & 0x20) == 0)
        goto LABEL_67;
      WaitMotion = (u16)klass->WaitMotion;
      if (WaitMotion == (u16)Model->motionMinorNum)
      {
        v14 = (u16)klass->WaitMotion;
LABEL_24:
        if (v14 == (u16)Model->motionMinorNum)
        {
          if (mdlChkMotionEnd(Model))
          {
            motions = Model->motions;
            v17 = klass->WaitMotion;
            WaitBefore = klass->WaitBefore;
            WaitSmooth = klass->WaitSmooth;
LABEL_111:
            motions[0]->isWaitMot = 1;
            mdlSmoothLoopMotion(Model, 0, v17, (f32)WaitBefore, (f32)WaitSmooth, 0.0);
            mdlSetMotionSpeed(Model, klass->WaitSpeed);
            klass->Frame = 0;
            v33 = ((u32)klass->Flag >> 6) & 1;
            if (klass->Stat != 3)
              goto LABEL_71;
LABEL_68:
            x = klass->PosTarget.x;
            y = klass->PosTarget.y;
            z = klass->PosTarget.z;
            w = klass->PosTarget.w;
            MovePara1 = klass->MovePara1;
            v98.z = z;
            v98.w = w;
            v98.x = x;
            v98.y = y;
            if (evtUnitRotationQuat(klass, v98, (f32)MovePara1 / 100.0))
              goto LABEL_86;
LABEL_71:
            v97 = 0;
            v34 = klass->Flag;
            if ((v34 & 0x1000000) == 0)
              goto LABEL_130;
            goto LABEL_88;
          }
        }
LABEL_67:
        v33 = ((u32)klass->Flag >> 6) & 1;
        if (klass->Stat != 3)
          goto LABEL_71;
        goto LABEL_68;
      }
      else
      {
        v58 = mdlChkMotionEnd(Model);
        v17 = klass->WaitMotion;
        if (v58)
        {
          motions = Model->motions;
          WaitBefore = klass->WaitBefore;
          WaitSmooth = klass->WaitSmooth;
          goto LABEL_111;
        }
        v14 = (u16)klass->WaitMotion;
        goto LABEL_24;
      }
      goto LABEL_24;
    case 1:
      if (klass->MapLightUse)
      {
        if (dds3SearchProcessName("fldProcSequence"))
        {
          Owner = klass->Owner;
          poseset = Owner->poseset;
          v22 = poseset->pos.x;
          v23 = poseset->pos.z;
          v24 = mapGetLight(v22, v23);
          mapUnitSetLight(Owner, v24, 6);
        }
      }
      if (!!CheckMoveEnd(klass))
      {
        if (!GetNextMovePos(klass))
          goto LABEL_85;
      }
      v46 = (u16)klass->NowMotion;
      if (v46 == (u16)Model->motionMinorNum)
        goto LABEL_79;
      v54 = klass->NowMotion;
      v55 = klass->NowBefore;
      v56 = klass->NowSmooth;
      if ((klass->Flag & 1) != 0)
      {
        if (!v57)
        mdlSmoothLoopMotion(Model, 0, v54, (f32)v55, (f32)v56, 0.0);
        MoveType = klass->MoveType;
        v48 = MoveType == 2;
        if (MoveType >= 2)
          goto LABEL_80;
      }
      else
      {
        if (!v57)
        mdlSmoothSingleMotion(Model, 0, v54, (f32)v55, (f32)v56, 0.0);
        MoveType = klass->MoveType;
        v48 = MoveType == 2;
        if (MoveType >= 2)
          goto LABEL_80;
      }
LABEL_118:
      evtUnitMoveType0(klass);
      if (klass->MoveType == 1)
      {
        YMoveAddValue = klass->YMoveAddValue;
        v99.x = 0.0;
        v99.z = 0.0;
        v99.w = 0.0;
        v99.y = YMoveAddValue;
        dds3AddPosPoseSet(&klass->Owner, v99);
      }
      goto LABEL_124;
LABEL_79:
      MoveType = klass->MoveType;
      v48 = MoveType == 2;
      if (MoveType < 2)
        goto LABEL_118;
LABEL_80:
      if (v48)
      {
        v97 = 0;
      }
      else
      {
        if (MoveType == 3)
        {
          evtUnitMoveTypePathTrace(klass);
LABEL_124:
          v97 = 1;
          goto LABEL_127;
        }
        v97 = 0;
        klass->Stat = 0;
      }
LABEL_127:
      Action = klass->Action;
      if (Action)
      {
        v33 = 0;
        if (((Action->invoke_impl)(Action->method_code, klass, 0, Action->method) & 1) != 0)
          goto LABEL_87;
        v34 = klass->Flag;
        if ((v34 & 0x1000000) == 0)
        {
LABEL_130:
          if (!(v34 & 0x400000 | v33))
            goto LABEL_134;
LABEL_131:
          v61 = klass->Sin + 0.10471976;
          klass->Owner->poseset->flag = klass->Owner->poseset->flag
                                                           & 0xFFFFFFFC
                                                           | 1;
          if (v61 >= 6.2831855)
            v61 = v61 + -6.2831855;
          klass->Sin = v61;
          goto LABEL_134;
        }
      }
      else
      {
        v33 = 0;
        v34 = klass->Flag;
        if ((v34 & 0x1000000) == 0)
          goto LABEL_130;
      }
LABEL_88:
      if (klass->MovePara1)
      {
        (loc_19D0780)(klass, 0);
        if (!(klass->Flag & 0x400000 | v33))
          goto LABEL_134;
        goto LABEL_131;
      }
      v49 = klass->Flag & 0xFEFFFFFF;
      klass->Flag = v49;
      if (v49 & 0x400000 | v33)
        goto LABEL_131;
LABEL_134:
      for (i = 0; i != 11; ++i)
      {
        v63 = (char *)klass->ExFlags + i;
        if ((v63[33] & 1) == 0)
          continue;
        if ((v63[33] & 2) == 0)
          goto LABEL_142;
        v63[33] &= ~2u;
        v64 = klass->ExNowMotion[i + 1];
        v65 = klass->ExBefore[i + 1];
        v67 = klass->ExSmooth[i + 1];
        if ((klass->ExFlags[i + 1] & 0x28) != 0)
        {
          if (!v66)
          mdlSmoothLoopMotion(Model, i + 1, v64, (f32)v65, (f32)v67, 0.0);
LABEL_142:
          goto LABEL_144;
        }
        if (!v66)
        mdlSmoothSingleMotion(Model, i + 1, v64, (f32)v65, (f32)v67, 0.0);
LABEL_144:
        v69 = i + 1;
        v70 = mdlChkMotionEndEx(Model, i + 1);
        ExFlags = klass->ExFlags;
        if (v70 && (ExFlags[i + 1] & 4) != 0)
        {
          v73 = klass->ExWaitMotion[i + 1];
          v74 = klass->ExWaitBefore[i + 1];
          v75 = klass->ExNowSmooth[i + 1];
          Model->motions[i + 1]->isWaitMot = 1;
          mdlSmoothLoopMotion(Model, v69, v73, (f32)v74, (f32)v75, 0.0);
          ExFlags = klass->ExFlags;
        }
        v76 = (s64)ExFlags + i;
        if ((ExFlags[i + 1] & 0x20) != 0)
        {
          ExLoopEndTime = klass->ExLoopEndTime;
          v78 = (s64)ExLoopEndTime + 4 * i;
          v79 = *(f32 *)(v78 + 36);
          if (v79 <= 0.0)
          {
            *(u32 *)(v78 + 36) = 0;
            *(u8 *)(v76 + 33) &= ~0x20u;
            v81 = klass->ExWaitMotion[i + 1];
            v82 = klass->ExWaitBefore[i + 1];
            v83 = klass->ExNowSmooth[i + 1];
            Model->motions[i + 1]->isWaitMot = 1;
            mdlSmoothLoopMotion(Model, v69, v81, (f32)v82, (f32)v83, 0.0);
            ExLoopEndTime = klass->ExLoopEndTime;
            v79 = ExLoopEndTime[i + 1];
          }
          if (v79 > 0.0)
          {
            v84 = (s64)ExLoopEndTime + 4 * i;
            v85 = *(f32 *)(v84 + 36);
            *(f32 *)(v84 + 36) = v85 - get_deltaTime(0);
          }
        }
      }
      MakeLightPacket(klass);
      Frame = (u16)klass->Frame;
      if (Frame != 0x7FFF)
        goto LABEL_167;
      if (v97)
        goto LABEL_163;
LABEL_168:
      StopTimer = klass->StopTimer;
      if (StopTimer == 0x7FFF || (klass->StopTimer = StopTimer + 1, StopTimer >= 5))
      {
        klass->MoveTimer = 0;
        return 0;
      }
      return 0;
LABEL_167:
      klass->Frame = Frame + 1;
      if (!v97)
        goto LABEL_168;
LABEL_163:
      MoveTimer = (u16)klass->MoveTimer;
      if (MoveTimer != 0x7FFF)
        klass->MoveTimer = MoveTimer + 1;
      klass->StopTimer = 0;
      return 1;
    case 2:
      if (klass->Frame)
      {
        if (!mdlChkMotionEnd(Model))
        {
          v25 = klass->Flag;
          if ((v25 & 0x800000) == 0)
            goto LABEL_52;
          MotionFrame = mdlGetMotionFrame(Model);
          v25 = klass->Flag;
          if (MotionFrame >= klass->MotEndFrame)
          {
            klass->Flag = v25 & 0xFF7FFFFF;
            v92 = (u16)klass->WaitMotion;
            klass->Stat = 4;
            if (v92 != (u16)Model->motionMinorNum)
            {
              v94 = klass->WaitMotion;
              v95 = klass->WaitBefore;
              v96 = klass->WaitSmooth;
              Model->motions[0]->isWaitMot = 1;
              mdlSmoothLoopMotion(Model, 0, v94, (f32)v95, (f32)v96, 0.0);
              mdlSetMotionSpeed(Model, klass->WaitSpeed);
              v33 = 0;
              v97 = 0;
              klass->Frame = 0;
              v34 = klass->Flag;
              if ((v34 & 0x1000000) == 0)
                goto LABEL_130;
              goto LABEL_88;
            }
          }
          else
          {
LABEL_52:
            if ((v25 & 0x2000000) != 0)
            {
              LoopEndTime = klass->LoopEndTime;
              if (LoopEndTime <= 0.0)
              {
                v28 = Model->motions;
                klass->Flag = v25 & 0xFDFFFFFF;
                klass->LoopEndTime = 0.0;
                v30 = klass->WaitMotion;
                v31 = klass->WaitBefore;
                v32 = klass->WaitSmooth;
                v28[0]->isWaitMot = 1;
                mdlSmoothLoopMotion(Model, 0, v30, (f32)v31, (f32)v32, 0.0);
                mdlSetMotionSpeed(Model, klass->WaitSpeed);
                LoopEndTime = klass->LoopEndTime;
              }
              if (LoopEndTime > 0.0)
              {
                v33 = 0;
                v97 = 0;
                klass->LoopEndTime = LoopEndTime - get_deltaTime(0);
                v34 = klass->Flag;
                if ((v34 & 0x1000000) == 0)
                  goto LABEL_130;
                goto LABEL_88;
              }
            }
          }
LABEL_57:
          v33 = 0;
          v97 = 0;
          v34 = klass->Flag;
          if ((v34 & 0x1000000) == 0)
            goto LABEL_130;
          goto LABEL_88;
        }
LABEL_85:
        v33 = 0;
LABEL_86:
        v97 = 0;
LABEL_87:
        klass->Stat = 0;
        v34 = klass->Flag;
        if ((v34 & 0x1000000) == 0)
          goto LABEL_130;
      }
      else
      {
        v50 = klass->NowMotion;
        v51 = klass->NowBefore;
        v52 = klass->NowSmooth;
        if ((klass->Flag & 0x2000001) != 0)
        {
          if (!v53)
          mdlSmoothLoopMotion(Model, 0, v50, (f32)v51, (f32)v52, 0.0);
        }
        else
        {
          if (!v53)
          mdlSmoothSingleMotion(Model, 0, v50, (f32)v51, (f32)v52, 0.0);
        }
        v33 = 0;
        v97 = 0;
        v34 = klass->Flag & 0xFFFFFF7F;
        klass->Flag = v34;
        if ((v34 & 0x1000000) == 0)
          goto LABEL_130;
      }
      goto LABEL_88;
    case 4:
      v35 = klass->Action;
      if (v35 && ((v35->invoke_impl)(v35->method_code, klass, 0, v35->method) & 1) == 0)
      {
        goto LABEL_57;
      }
      goto LABEL_85;
    default:
      return 0;
  }
}

// 0x19cd840
static CustomSceneLightInfo *NewCustomSceneLight(void) {
  CustomSceneLightInfo *v1;
  CustomSceneLightInfo *v2;
  CustomSceneLightInfo *v3;
  CustomSceneLightInfo *v4;
  CustomSceneLightInfo *v5;
  CustomSceneLightInfo *v6;
  CustomSceneLightInfo *v7;
  CustomSceneLightInfo *v8;

  v1 = (CustomSceneLightInfo *)NewSpecific(CustomSceneLightInfo, 7u);
  v2 = Allocate(CustomSceneLightInfo);
  _ctor(v2, 0);
  v1[0] = v2;
  v3 = Allocate(CustomSceneLightInfo);
  _ctor(v3, 0);
  v1[1] = v3;
  v4 = Allocate(CustomSceneLightInfo);
  _ctor(v4, 0);
  v1[2] = v4;
  v5 = Allocate(CustomSceneLightInfo);
  _ctor(v5, 0);
  v1[3] = v5;
  v6 = Allocate(CustomSceneLightInfo);
  _ctor(v6, 0);
  v1[4] = v6;
  v7 = Allocate(CustomSceneLightInfo);
  _ctor(v7, 0);
  v1[5] = v7;
  v8 = Allocate(CustomSceneLightInfo);
  _ctor(v8, 0);
  v1[6] = v8;
  return v1;
}

// 0x19cda60
void evtInitCustomSceneLight(void) {
  s64 v3;
  CustomSceneLightInfo *v4;
  sdfVector4_t *Color;
  sdfVector4_t *Dir;

  if (SLODWORD(CustomSceneLightArray->max_length) < 1)
    return;
  v3 = 0;
  do
  {
    v4 = CustomSceneLightArray[v3];
    Color = v4->Color;
    Dir = v4->Dir;
    v4->UnitHandle = 0;
    v4->LightType = 0;
    Color[0] = (sdfVector4_t)xmmword_3D05D20;
    Dir[0] = (sdfVector4_t)xmmword_3CFCD20;
    Color[1] = (sdfVector4_t)xmmword_3D05D20;
    Dir[1] = (sdfVector4_t)xmmword_3CFCD20;
    Color[2] = (sdfVector4_t)xmmword_3D05D20;
    Dir[2] = (sdfVector4_t)xmmword_3CFCD20;
    *(u64 *)&v4->Soften = 1088421888;
    v4->Ambient = (struct sdfVector4_t)xmmword_3CF97B0;
    ++v3;
  }
  while (v3 < SLODWORD(CustomSceneLightArray->max_length));
}

// 0x19cdbc0
void evtSetCustomSceneLightData(s32 index, SCENELIGHT LightType, evtUnitHandle_t *h, sdfVector4_t *Color, sdfVector4_t *Dir, const sdfVector4_t *Ambient) {
  f32 z;
  f32 y;
  f32 x;
  evtUnitHandle_t *v16;
  CustomSceneLightInfo *v17;
  sdfVector4_t *v18;
  f32 *v19;
  f32 v20;
  f32 v21;
  f32 v22;

  z = Ambient->z;
  y = Ambient->y;
  x = Ambient->x;
  if (index > 6)
    return;
  if (LightType == 3)
    v16 = h;
  else
    v16 = 0;
  v17 = CustomSceneLightArray[index];
  v18 = v17->Color;
  v19 = v17->Dir;
  v18[0].x = Color[0].x;
  v18[0].y = Color[0].y;
  v20 = Color[0].z;
  v18[0].w = 0.0;
  v18[0].z = v20;
  v19[8] = Dir[0].x;
  v19[9] = Dir[0].y;
  v19[10] = Dir[0].z;
  v19[11] = Dir[0].w;
  v18[1].x = Color[1].x;
  v18[1].y = Color[1].y;
  v21 = Color[1].z;
  v18[1].w = 0.0;
  v18[1].z = v21;
  v19[12] = Dir[1].x;
  v19[13] = Dir[1].y;
  v19[14] = Dir[1].z;
  v19[15] = Dir[1].w;
  v18[2].x = Color[2].x;
  v18[2].y = Color[2].y;
  v22 = Color[2].z;
  v18[2].w = 0.0;
  v18[2].z = v22;
  v19[16] = Dir[2].x;
  v19[17] = Dir[2].y;
  v19[18] = Dir[2].z;
  v19[19] = Dir[2].w;
  v17->Ambient.x = x;
  v17->Ambient.y = y;
  v17->Ambient.z = z;
  v17->Ambient.w = 1.0;
  v17->UnitHandle = v16;
  v17 = ((char *)v17 + 24);
  LODWORD(v17[-1].Soften) = LightType;
}

// 0x19cdd70
void evtSetCustomSceneLightData_SoftenAndBias(s32 index, f32 soften, f32 bias) {
  CustomSceneLightInfo *v8;

  if (index > 6)
    return;
  v8 = CustomSceneLightArray[index];
  v8->Soften = soften;
  v8->Bias = bias;
}

// 0x19cde10
bool evtGetCustomSLightData(evtUnitHandle_t *h, sdfVector4_t *lightv) {
  il2cpp_array_size_t max_length;
  CustomSceneLightInfo *v9;
  CustomSceneLightInfo *m_Items;
  CustomSceneLightInfo *v11;
  s32 LightType;
  f32 *Dir;

  max_length = CustomSceneLightArray->max_length;
  if ((s32)max_length < 1)
    return 0;
  v9 = 0;
  max_length = (u32)max_length;
  m_Items = CustomSceneLightArray;
  do
  {
    v11 = m_Items;
    LightType = m_Items->LightType;
    if (LightType == 3)
    {
      if (v11->UnitHandle == h)
        goto LABEL_20;
    }
    else if (!v9)
    {
      if (LightType == 2)
        v9 = m_Items;
      else
        v9 = 0;
    }
    --max_length;
    ++m_Items;
  }
  while (max_length);
  v11 = v9;
  if (!v9)
    return 0;
LABEL_20:
  Dir = v11->Dir;
  lightv->x = Dir[8];
  lightv->y = Dir[9];
  lightv->z = Dir[10];
  return 1;
}

// 0x19c8e90
void evtMakeCustomSLightPacket(evtUnitHandle_t *h) {
  il2cpp_array_size_t max_length;
  CustomSceneLightInfo *v7;
  CustomSceneLightInfo *m_Items;
  CustomSceneLightInfo *v9;
  s32 LightType;
  sdf3DLight_t *v11;
  sdf3DLight_t *v12;
  sdfVector4_t *Color;
  sdfVector4_t *Dir;
  f32 z;
  f32 v16;
  sdf3DLight_t *v17;
  sdfVector4_t *v18;
  sdfVector4_t *v19;
  f32 v20;
  f32 v21;
  sdf3DLight_t *v22;
  sdfVector4_t *v23;
  sdfVector4_t *v24;
  f32 v25;
  f32 v26;
  sdf3DLightParallelPacket_t *PrivateLightPacket;
  f32 x;
  f32 y;
  f32 v30;
  sdf3DLightParallelPacket_t *v31;
  sdfVector4_t v33;

  max_length = CustomSceneLightArray->max_length;
  if ((s32)max_length < 1)
    return;
  v7 = 0;
  max_length = (u32)max_length;
  m_Items = CustomSceneLightArray;
  do
  {
    v9 = m_Items;
    LightType = m_Items->LightType;
    if (LightType == 3)
    {
      if (v9->UnitHandle == h)
        goto LABEL_20;
    }
    else if (!v7)
    {
      if (LightType == 2)
        v7 = m_Items;
      else
        v7 = 0;
    }
    --max_length;
    ++m_Items;
  }
  while (max_length);
  v9 = v7;
  if (!v7)
    return;
LABEL_20:
  v11 = NewSpecific(sdf3DLight_t, 3u);
  v12 = Allocate(sdf3DLight_t);
  Color = v9->Color;
  Dir = v9->Dir;
  v12->color.x = Color[0].x;
  v12->color.y = Color[0].y;
  z = Color[0].z;
  *(u32 *)&v12->color.w = 0;
  v12->color.z = z;
  v12->v.x = Dir[0].x;
  v12->v.y = Dir[0].y;
  v16 = Dir[0].z;
  *(u32 *)&v12->v.w = 0;
  v12->v.z = v16;
  v11[0] = v12;
  v17 = Allocate(sdf3DLight_t);
  v18 = v9->Color;
  v19 = v9->Dir;
  v17->color.x = v18[1].x;
  v17->color.y = v18[1].y;
  v20 = v18[1].z;
  *(u32 *)&v17->color.w = 0;
  v17->color.z = v20;
  v17->v.x = v19[1].x;
  v17->v.y = v19[1].y;
  v21 = v19[1].z;
  *(u32 *)&v17->v.w = 0;
  v17->v.z = v21;
  v11[1] = v17;
  v22 = Allocate(sdf3DLight_t);
  v23 = v9->Color;
  v24 = v9->Dir;
  v22->color.x = v23[2].x;
  v22->color.y = v23[2].y;
  v25 = v23[2].z;
  *(u32 *)&v22->color.w = 0;
  v22->color.z = v25;
  v22->v.x = v24[2].x;
  v22->v.y = v24[2].y;
  v26 = v24[2].z;
  *(u32 *)&v22->v.w = 0;
  v22->v.z = v26;
  v11[2] = v22;
  PrivateLightPacket = h->PrivateLightPacket;
  if (v9->Ambient.x <= 1.0)
    x = v9->Ambient.x;
  else
    x = 1.0;
  if (v9->Ambient.y <= 1.0)
    y = v9->Ambient.y;
  else
    y = 1.0;
  if (v9->Ambient.z <= 1.0)
    v30 = v9->Ambient.z;
  else
    v30 = 1.0;
  v33.w = 1.0;
  v33.x = x;
  v33.y = y;
  v33.z = v30;
  sdf3MakeLightParallelPacket(PrivateLightPacket, v11, v33, 1);
  v31 = h->PrivateLightPacket;
  h->PublicLightPacket = v31;
}

// 0x19c7910
bool evtGetCustomSLight_SoftenAndBias(evtUnitHandle_t *h, f32 *pSoften, f32 *pBias) {
  evtUnitHandle_t *v8;
  il2cpp_array_size_t max_length;
  CustomSceneLightInfo *v12;
  CustomSceneLightInfo *m_Items;
  CustomSceneLightInfo *v14;
  s32 LightType;

  v8 = h;
  max_length = CustomSceneLightArray->max_length;
  if ((s32)max_length < 1)
    return 0;
  v12 = 0;
  max_length = (u32)max_length;
  m_Items = CustomSceneLightArray;
  do
  {
    v14 = m_Items;
    LightType = m_Items->LightType;
    if (LightType == 3)
    {
      if (v14->UnitHandle == v8)
        goto LABEL_20;
    }
    else if (!v12)
    {
      if (LightType == 2)
        v12 = m_Items;
      else
        v12 = 0;
    }
    --max_length;
    ++m_Items;
  }
  while (max_length);
  v14 = v12;
  if (!v12)
    return 0;
LABEL_20:
  *pSoften = v14->Soften;
  *pBias = v14->Bias;
  return 1;
}

// 0x19cdf80
static CustomSceneLightInfo *GetCustomSLightIndex(evtUnitHandle_t *h) {
  il2cpp_array_size_t max_length;
  CustomSceneLightInfo *v6;
  CustomSceneLightInfo *m_Items;
  CustomSceneLightInfo *result;
  s32 LightType;

  max_length = CustomSceneLightArray->max_length;
  if ((s32)max_length < 1)
    return 0;
  v6 = 0;
  max_length = (u32)max_length;
  m_Items = CustomSceneLightArray;
  do
  {
    result = m_Items;
    LightType = m_Items->LightType;
    if (LightType == 3)
    {
      if (result->UnitHandle == h)
        return result;
    }
    else if (!v6)
    {
      if (LightType == 2)
        v6 = m_Items;
      else
        v6 = 0;
    }
    ++m_Items;
    --max_length;
    result = v6;
  }
  while (max_length);
  return result;
}
