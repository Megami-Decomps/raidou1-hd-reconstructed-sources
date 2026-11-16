#include "types.h"
#include "dds3kerneldraw.h"
#include "egl.h"
#include "kernel.h"
#include "sbtlmain.h"
#include "sbtlsound.h"
#include "sdf3d.h"
#include "sdf_vu0.h"
#include "sdfdraw.h"
#include "sdfmat.h"
#include "sdfmodel.h"
#include "sdfquat.h"
#include "sdfsystem.h"
#include "sdfvsync.h"

#define BISTA_TALKEVENT_ALPHA 0.4296875

typedef struct Blur2Anime Blur2Anime;
typedef struct DistBlurAnime DistBlurAnime;
typedef struct FIL_t FIL_t;
typedef struct Filter2Anime Filter2Anime;
typedef struct MFilterAnime MFilterAnime;
typedef struct MultiBlurAnime MultiBlurAnime;
typedef struct RipBlurAnime RipBlurAnime;
typedef struct SDF_GS_TEST SDF_GS_TEST;
typedef struct dds3DrawEnv_t dds3DrawEnv_t;
typedef struct sdf3DFogParam_t sdf3DFogParam_t;
typedef struct sdf3DLight_t sdf3DLight_t;
typedef struct sdf3DScreenParam_t sdf3DScreenParam_t;
typedef struct sdfGrOt_t sdfGrOt_t;
typedef struct sdfIVector2_t sdfIVector2_t;
typedef struct sdfModelOt_t sdfModelOt_t;

s16 TOP;
s16 BTM;

sdfGrOt_t *Ot;
sdfModelOt_t *ModelOt;
dds3DrawEnv_t *DrawEnv;
sdfVector4_t CameraOffset;
static f32 finishBrightness;
static f32 finishContrast;
sdf3DScreenParam_t *ScreenParam;
void *cameraObject;
sdfMatrix4_t CameraTM;
sdfVector4_t CameraTargetPos;
sdfVector4_t CameraEyePos;
sdfVector4_t CameraUpVector;
sdf3DLight_t *DirLight0;
sdf3DLight_t *DirLight1;
sdf3DLight_t *DirLight2;
sdf3DLight_t *DirLights;
sdfVector4_t Ambient;
sdfVector4_t BackColor;
sdf3DFogParam_t *FogParam;
static sdf3DScreenParam_t *push_ScreenParam;
static sdfMatrix4_t push_CameraTM;
static sdfVector4_t push_CameraTargetPos;
static sdfVector4_t push_CameraEyePos;
static sdfVector4_t push_CameraUpVector;
static sdf3DLight_t *push_DirLight0;
static sdf3DLight_t *push_DirLight1;
static sdf3DLight_t *push_DirLight2;
static sdfVector4_t push_Ambient;
static sdfVector4_t push_BackColor;
static sdf3DFogParam_t *push_FogParam;
static bool push_sdf3DGlobalParamFlag;
static f32 push_sdf3DGlobalParamScaleX;
static f32 push_sdf3DGlobalParamScaleY;
static f32 push_sdf3DGlobalParamTransX;
static f32 push_sdf3DGlobalParamTransY;
sdf3DScreenParam_t *HScreenParam;
void *HcameraObject;
sdfMatrix4_t HCameraTM;
sdfVector4_t HCameraTargetPos;
sdfVector4_t HCameraEyePos;
sdfVector4_t HCameraUpVector;
sdf3DLight_t *HDirLight0;
sdf3DLight_t *HDirLight1;
sdf3DLight_t *HDirLight2;
sdf3DLight_t *HDirLights;
sdfVector4_t HAmbient;
bool HDrawSync;
DDS3_DRAWFLAG DrawFlag;
DDS3_DRAWFLAG2 DrawFlag2;
bool ScreenBlurFlag;
s16 ScreenBlurAlpha;
s16 ScreenBlurScale;
sdfIVector2_t ScreenBlurPnt;
static s32 blurnow;
static s32 blurmax;
static s16 bluralphabase;
static s16 blurscalebase;
static s16 bluralphatarget;
static s16 blurscaletarget;
bool QuakeFlag;
static s16 QuakeFrame;
static u16 QuakeXRange;
static u16 QuakeYRange;
f32 Zoom;
sdfVector4_t fadergba;
DDS3_FADEMODE fademode;
static DDS3_FADETYPE fadetype;
static u16 fadenow;
static u16 fademax;
static sdfVector4_t fadeColor;
static u16 bistanow;
static u16 bistamax;
static BISTA_MODE s_bistamode;
static bool s_bista_bustup;
static s16 s_top_mod;
static s16 s_down_mod;
static s32 s_bista_harf_cnt;
static f32 bistaAlpha;
static void *bistaFadeMesh;
static f32 PostEsp_Alpha;
static u16 PostEsp_now;
static u16 PostEsp_max;
static f32 PostSlow_Alpha;
static u16 PostSlow_now;
static u16 PostSlow_max;
static f32 PostHitFlash_Alpha;
static u16 PostHitFlash_now;
static u16 PostHitFlash_max;
static s32 *lightrgbnow;
static s32 *lightrgbmax;
static sdfVector4_t *lightrgbbase;
static sdfVector4_t *lightrgbtarget;
static s32 *lightdirnow;
static s32 *lightdirmax;
static sdfVector4_t *lightdirbase;
static sdfVector4_t *lightdirquat;
static s32 ambientnow;
static s32 ambientmax;
static sdfVector4_t ambientbase;
static sdfVector4_t ambienttarget;
MultiBlurAnime *MultiBlur;
DistBlurAnime *DistBlur;
RipBlurAnime *RipBlur;
Blur2Anime *Blur2;
Filter2Anime *Filter2;
MFilterAnime *MFilter;
static FIL_t *gFilterBuff;
s32 gFilterAlpha;
s32 gFilterFilterAlpOfs;
static s32 gFilterMode;
static s32 gFilterAnime;
static f32 gFilterAnimeCntF;
static s32 gFilterAnimeOfsA;
static s32 gFilterNowIdx;
static s32 gFilterBlendIdx;
static f32 gFilterBlend;
static f32 gFilterBlendSpd;
static s32 gFilterCursor;
static void *filterMesh;
static bool gOverwrite_ScreenParam_sensorSize;
static sdfVector2_t gOverwrite_ScreenParam_sensorSize_XY;
bool gShaderUVScroll;
f32 gShaderUV_Time_Time;
static f32 *cycle;
static sdfVector4_t uq;
static f32 **FilterCalcTable;
static SDF_GS_TEST *FilterDrawTest;
static f32 rendering_Resolution;
static f32 old_rendering_Resolution;
static s32 renderFrameInterval;
static s32 old_renderFrameInterval;

static void FadeTypeSet(DDS3_FADETYPE eType);
static void SetFinish(void);

// 0x22879c0
void dds3InitDrawEnvSub(s32 i) {
  dds3DrawEnv_t *v4;
  sdf3DViewportPacket_t *ViewportPacket;
  void *v14;

  v4 = DrawEnv[i];
  goto LABEL_8;
LABEL_13:
  Update();
  _Redraw_k__BackingField = 1;
  goto LABEL_18;
LABEL_8:
  if (firstFrame)
    goto LABEL_13;
LABEL_18:
  sdfDrawTagInit(v4->DrawTag);
  if (!op_Inequality(cameraObject, 0, 0))
  {
    ViewportPacket = v4->ViewportPacket;
    goto LABEL_22;
  }
  set_backgroundColor(cameraObject->_camera, (sdfColor_t)BackColor, 0);
  ViewportPacket = v4->ViewportPacket;
LABEL_22:
  v14 = cameraObject;
  sdf3MakeViewportPacket(ViewportPacket, ScreenParam, &CameraTM, v14);
  sdfDrawTagLink(v4->DrawTag, v4->ViewportPacket);
  sdf3MakeLightParallelPacket(v4->DirLightPacket, DirLights, Ambient, 1);
  sdfDrawTagLink(v4->DrawTag, v4->DirLightPacket);
  sdfDrawTagInit(v4->HighDrawTag);
  sdf3MakeViewportPacket(v4->HighViewportPacket, HScreenParam, &HCameraTM, HcameraObject);
  sdfDrawTagLink(v4->HighDrawTag, v4->HighViewportPacket);
  sdf3MakeLightParallelPacket(v4->HighDirLightPacket, HDirLights, HAmbient, 1);
  sdfDrawTagLink(v4->HighDrawTag, v4->HighDirLightPacket);
}

// 0x2287d50
void dds3InitDrawEnv(void) {
  void *v5;
  dds3DrawEnv_t *v11;
  dds3DrawEnv_t *v14;
  dds3DrawEnv_t *v15;
  struct dds3KernelDraw *v19;
  sdfGrOt_t *v23;
  sdfGrOt_t *v24;
  sdfGrOt_t *v25;
  void *v26;
  Il2CppObject *v27;
  void *scaler;
  void *transform;
  void *Image_133_0;
  void *v34;
  void *v35;
  void *p_fadeImage;
  void *v37;
  void *v39;
  void *p_fadeTex;
  void *v42;
  void *v43;
  void *v44;
  Project_Kernel_dds3KernelDraw___c__DisplayClass133_0_o target;
  sdfVector2_t v48;

  target.scaler = 0;
  gShaderUVScroll = 1;
  gShaderUV_Time_Time = 0.0;
  sdf3MakeScreenParam(ScreenParam);
  v5 = Allocate(Project_libsdf_sdfCameraScreen);
  _ctor(v5, 2048, 2048, 512, 224, 32, 0);
  defaultCameraScreen = v5;
  GlobalParamFlag = 0;
  sdf3MakeScreenParam(HScreenParam);
  v11 = Allocate(dds3DrawEnv_t);
  _ctor(v11, 0);
  DrawEnv[0] = v11;
  dds3InitDrawEnvSub(0);
  v14 = DrawEnv;
  v15 = Allocate(dds3DrawEnv_t);
  _ctor(v15, 0);
  v14[1] = v15;
  dds3InitDrawEnvSub(1);
  eglInit();
  sdfModelOtInit(ModelOt, Ot[44], Ot[48], Ot[64], Ot[66]);
  sdfModelOtInit(&ModelOt[1], Ot[47], Ot[49], Ot[65], Ot[67]);
  sdfModelOtInit(&ModelOt[9], Ot[42], Ot[48], Ot[51], Ot[50]);
  sdfModelOtInit(&ModelOt[10], Ot[73], Ot[74], Ot[75], Ot[76]);
  sdfModelOtInit(&ModelOt[11], Ot[85], Ot[86], Ot[87], Ot[88]);
  sdfModelOtInit(&ModelOt[3], Ot[13], Ot[14], Ot[15], Ot[16]);
  sdfModelOtInit(&ModelOt[4], Ot[18], Ot[19], Ot[20], Ot[21]);
  sdfModelOtInit(&ModelOt[5], Ot[23], Ot[24], Ot[25], Ot[26]);
  sdfModelOtInit(&ModelOt[6], Ot[28], Ot[29], Ot[30], Ot[31]);
  sdfModelOtInit(&ModelOt[7], Ot[53], Ot[54], Ot[55], Ot[56]);
  sdfModelOtInit(&ModelOt[8], Ot[33], Ot[34], Ot[35], Ot[36]);
  sdfModelOtInit(&ModelOt[12], Ot[58], Ot[59], Ot[62], Ot[63]);
  sdfModelOtInit(&ModelOt[13], Ot[94], Ot[95], Ot[98], Ot[99]);
  ModelOt[13]->camID = 1;
  v23 = Ot[40];
  Ot[39]->renderQueue = 2100;
  v23->renderQueue = 2100;
  Ot[43]->renderQueue = 2100;
  Ot[93]->renderQueue = 2100;
  Ot[92]->renderQueue = 2100;
  v24 = Ot[47];
  Ot[46]->renderQueue = 3100;
  v25 = Ot[72];
  v24->renderQueue = 3100;
  v25->renderQueue = 3100;
  if ((u32)v19)
  {
    if (!op_Equality(canvas, 0, 0))
      return;
  }
  else
  {
    if (!op_Equality(canvas, 0, 0))
      return;
  }
  v26 = Allocate(UnityEngine_GameObject);
  _ctor_60987488(v26, 0);
  v27 = AddComponent_object_(v26);
  target.scaler = AddComponent_object_(v26);
  sdfSetScene(v26);
  set_renderMode(v27, 0, 0);
  set_sortingOrder(v27, 500, 0);
  scaler = target.scaler;
  target.scaler->m_UiScaleMode = 1;
  v48.x = 1920.0;
  v48.y = 1080.0;
  set_referenceResolution(scaler, v48, 0);
  transform = get_transform(v26, 0);
  canvas = transform;
  Image_133_0 = _InitDrawEnv_g__GetImage_133_0(&target);
  (*&Image_133_0->klass[1]._2.naturalAligment)(Image_133_0, Image_133_0->klass[1].vtable._0_Equals.methodPtr, zeroVector.x, zeroVector.y, zeroVector.z, zeroVector.w);
  v34 = get_transform(Image_133_0, 0);
  v35 = get_transform(v26, 0);
  SetParent_61042560(v34, v35, 0, 0);
  p_fadeImage = &fadeImage;
  p_fadeImage = Image_133_0;
  v37 = get_transform(Image_133_0, 0);
  canvas_2D_NORMAL2 = v37;
  v39 = Allocate(UnityEngine_Texture2D);
  _ctor_60858704(v39, 1, 1, 4, 0, 0, 0);
  p_fadeTex = &fadeTex;
  p_fadeTex = v39;
  set_wrapMode(fadeTex, 0, 0);
  set_filterMode(fadeTex, 0, 0);
  v42 = _InitDrawEnv_g__GetImage_133_0(&target);
  get_gameObject(v42, 0);
  (v42->klass[2]._1.parent)(v42, finishMat, v42->klass[2]._1.generic_class);
  (*&v42->klass[1]._2.naturalAligment)(v42, v42->klass[1].vtable._0_Equals.methodPtr, oneVector.x, oneVector.y, oneVector.z, oneVector.w);
  v43 = get_transform(v42, 0);
  v44 = get_transform(v26, 0);
  SetParent_61042560(v43, v44, 0, 0);
  SetFinish();
}

// 0x2288930
void dds3DrawEnvPush(void) {
  sdf3DScreenParam_t *v2;
  sdf3DScreenParam_t *p_push_ScreenParam;
  __int128 v6;
  __int128 v7;
  sdf3DLight_t *v8;
  sdf3DLight_t *p_push_DirLight0;
  sdf3DLight_t *v10;
  sdf3DLight_t *p_push_DirLight1;
  sdf3DLight_t *v12;
  sdf3DLight_t *p_push_DirLight2;
  sdf3DFogParam_t *v15;
  sdf3DFogParam_t *p_push_FogParam;
  __int128 v20;

  v2 = Clone(ScreenParam, 0);
  p_push_ScreenParam = &push_ScreenParam;
  p_push_ScreenParam = v2;
  v6 = *(_OWORD *)&CameraTM.m01;
  *(_OWORD *)&push_CameraTM.m00 = *(_OWORD *)&CameraTM.m00;
  *(_OWORD *)&push_CameraTM.m01 = v6;
  v7 = *(_OWORD *)&CameraTM.m03;
  *(_OWORD *)&push_CameraTM.m02 = *(_OWORD *)&CameraTM.m02;
  *(_OWORD *)&push_CameraTM.m03 = v7;
  push_CameraTargetPos = CameraTargetPos;
  push_CameraEyePos = CameraEyePos;
  push_CameraUpVector = CameraUpVector;
  v8 = Clone(DirLight0, 0);
  p_push_DirLight0 = &push_DirLight0;
  p_push_DirLight0 = v8;
  v10 = Clone(DirLight1, 0);
  p_push_DirLight1 = &push_DirLight1;
  p_push_DirLight1 = v10;
  v12 = Clone(DirLight2, 0);
  p_push_DirLight2 = &push_DirLight2;
  p_push_DirLight2 = v12;
  push_Ambient = Ambient;
  push_BackColor = BackColor;
  v15 = Clone(FogParam, 0);
  p_push_FogParam = &push_FogParam;
  p_push_FogParam = v15;
  v20 = *(_OWORD *)&GlobalParamScaleX;
  push_sdf3DGlobalParamFlag = GlobalParamFlag;
  *(_OWORD *)&push_sdf3DGlobalParamScaleX = v20;
}

// 0x2288b10
void dds3DrawEnvPop(void) {
  sdf3DScreenParam_t *v2;
  __int128 v6;
  __int128 v7;
  sdf3DLight_t *v8;
  sdf3DLight_t *v10;
  sdf3DLight_t *v12;
  sdf3DFogParam_t *v15;
  sdf3DFogParam_t *p_FogParam;

  v2 = Clone(push_ScreenParam, 0);
  ScreenParam = v2;
  v6 = *(_OWORD *)&push_CameraTM.m00;
  *(_OWORD *)&CameraTM.m01 = *(_OWORD *)&push_CameraTM.m01;
  *(_OWORD *)&CameraTM.m00 = v6;
  v7 = *(_OWORD *)&push_CameraTM.m02;
  *(_OWORD *)&CameraTM.m03 = *(_OWORD *)&push_CameraTM.m03;
  *(_OWORD *)&CameraTM.m02 = v7;
  CameraTargetPos = push_CameraTargetPos;
  CameraEyePos = push_CameraEyePos;
  CameraUpVector = push_CameraUpVector;
  v8 = Clone(push_DirLight0, 0);
  DirLight0 = v8;
  v10 = Clone(push_DirLight1, 0);
  DirLight1 = v10;
  v12 = Clone(push_DirLight2, 0);
  DirLight2 = v12;
  Ambient = push_Ambient;
  BackColor = push_BackColor;
  v15 = Clone(push_FogParam, 0);
  p_FogParam = &FogParam;
  p_FogParam = v15;
  GlobalParamFlag = push_sdf3DGlobalParamFlag;
  *(_OWORD *)&GlobalParamScaleX = *(_OWORD *)&push_sdf3DGlobalParamScaleX;
}

// 0x2288cf0
void dds3RunQuake(void) {
  s64 v3;
  f32 *v4;
  u32 v5;
  u32 v6;
  s64 v9;
  s64 v10;
  f32 *p_w;
  f32 v13;
  f32 v14;
  f32 v15;
  f32 *p_y;
  f32 v18;
  f32 v19;
  f32 *p_x;
  f32 v23;
  f32 v24;
  f32 *p_z;
  f32 v27;
  u32 v28;
  f32 v29;
  f32 *v30;
  s32 v33;
  s32 v34;
  s32 v35;
  void *v36;
  void *v37;
  char *v38;
  void *v39;
  void *v40;
  void *v41;
  char *v42;
  void *v43;

  if (!QuakeFlag)
  {
    vct_A = vf00;
    vct_A.w = 0.0;
    return;
  }
  if (!QuakeFrame)
  {
    QuakeFlag = 0;
    return;
  }
  if (sBtlIsEnemyLastDeadStop())
    return;
  v4 = NewSpecific(f32, 2u);
  v9 = 0;
  LOWORD(v5) = QuakeXRange;
  LOWORD(v6) = QuakeYRange;
  v4[0] = (f32)v5 * 0.01;
  v4[1] = (f32)v6 * 0.01;
  v10 = &v4[0];
  do
  {
    if (*(f32 *)(v10 + 4 * v9) != 0.0)
    {
      v13 = sub_1B34D00(0, v3);
      v14 = v13;
      v15 = *(f32 *)(v10 + 4 * v9);
      if ((u32)v9)
      {
        if ((u32)v9 != 1)
          goto LABEL_107;
        p_y = &CameraOffset.y;
LABEL_28:
        v18 = (f32)(v15 * 0.5) + (f32)((f32)(v14 * v15) * 0.5);
        v19 = *p_y;
        if (fabsf(v19) < (f32)(*(f32 *)(v10 + 4 * v9) * cycle[v9]))
        {
          if ((u32)v9 != 1)
          {
            if ((u32)v9)
              goto LABEL_107;
            p_x = &CameraOffset.x;
            goto LABEL_44;
          }
          p_x = &CameraOffset.y;
LABEL_44:
          v23 = *p_x;
          v24 = sub_1B34D00(0, v3);
          *p_x = v23 + (f32)((f32)(v18 * (f32)(v24 + -0.5)) + (f32)(v18 * (f32)(v24 + -0.5)));
LABEL_46:
          p_z = &CameraOffset.x;
          switch ((s32)v9)
          {
            case 0:
              goto LABEL_50;
            case 1:
              v27 = -*(f32 *)(v10 + 4 * v9);
              if (CameraOffset.y >= v27)
                goto LABEL_55;
              goto LABEL_51;
            case 2:
              p_z = &CameraOffset.z;
LABEL_50:
              v27 = -*(f32 *)(v10 + 4 * v9);
              v29 = *p_z;
              if (v29 < v27)
                goto LABEL_51;
              goto LABEL_55;
            case 3:
              v27 = -*(f32 *)(v10 + 4 * v9);
              if (CameraOffset.w >= v27)
              {
LABEL_55:
                v30 = &CameraOffset.x;
                switch ((s32)v9)
                {
                  case 0:
                    goto LABEL_68;
                  case 1:
                    v27 = *(f32 *)(v10 + 4 * v9);
                    if (CameraOffset.y > v27)
                      goto LABEL_71;
                    goto LABEL_20;
                  case 2:
                    v30 = &CameraOffset.z;
LABEL_68:
                    v27 = *(f32 *)(v10 + 4 * v9);
                    if (*v30 > v27)
                      goto LABEL_71;
                    goto LABEL_20;
                  case 3:
                    v27 = *(f32 *)(v10 + 4 * v9);
                    if (CameraOffset.w > v27)
                    {
LABEL_71:
                      v27 = *(f32 *)(v10 + 4 * v9);
                      p_w = &CameraOffset.x;
                      switch ((s32)v9)
                      {
                        case 0:
                          break;
                        case 1:
LABEL_18:
                          p_w = &CameraOffset.y;
                          break;
                        case 2:
LABEL_74:
                          p_w = &CameraOffset.z;
                          break;
                        case 3:
LABEL_75:
                          p_w = &CameraOffset.w;
                          break;
                        default:
LABEL_108:
                          v40 = InitializedMetadata(&System_IndexOutOfRangeException);
                          v41 = Allocate(v40);
                          v42 = InitializedMetadata(&"Invalid Vector4 index!");
                          v43 = InitializedMetadata(&Method_UnityEngine_Vector4_set_Item__);
                      }
LABEL_19:
                      *p_w = v27;
                    }
                    goto LABEL_20;
                  default:
                    goto LABEL_107;
                }
              }
LABEL_51:
              if (!v28)
              {
                v27 = -*(f32 *)(v10 + 4 * v9);
              }
              p_w = &CameraOffset.x;
              switch ((s32)v9)
              {
                case 0:
                  goto LABEL_19;
                case 1:
                  goto LABEL_18;
                case 2:
                  goto LABEL_74;
                case 3:
                  goto LABEL_75;
                default:
                  goto LABEL_108;
              }
            default:
              break;
          }
LABEL_107:
          v36 = InitializedMetadata(&System_IndexOutOfRangeException);
          v37 = Allocate(v36);
          v38 = InitializedMetadata(&"Invalid Vector4 index!");
          v39 = InitializedMetadata(&Method_UnityEngine_Vector4_get_Item__);
        }
        if ((u32)v9)
        {
          if ((u32)v9 != 1)
            goto LABEL_107;
          if (CameraOffset.y <= 0.0)
          {
LABEL_37:
            switch ((s32)v9)
            {
              case 0:
                CameraOffset.x = v18 + CameraOffset.x;
                goto LABEL_46;
              case 1:
                CameraOffset.y = v18 + CameraOffset.y;
                goto LABEL_46;
              case 2:
                CameraOffset.z = v18 + CameraOffset.z;
                goto LABEL_46;
              case 3:
                CameraOffset.w = v18 + CameraOffset.w;
                goto LABEL_46;
              default:
                goto LABEL_107;
            }
          }
LABEL_62:
          switch ((s32)v9)
          {
            case 0:
              CameraOffset.x = CameraOffset.x - v18;
              goto LABEL_46;
            case 1:
              CameraOffset.y = CameraOffset.y - v18;
              goto LABEL_46;
            case 2:
              CameraOffset.z = CameraOffset.z - v18;
              goto LABEL_46;
            case 3:
              CameraOffset.w = CameraOffset.w - v18;
              goto LABEL_46;
            default:
              goto LABEL_107;
          }
        }
        if (CameraOffset.x <= 0.0)
          goto LABEL_37;
        goto LABEL_62;
      }
      p_y = &CameraOffset.x;
      goto LABEL_28;
    }
LABEL_20:
    ++v9;
  }
  while (v9 != 2);
  if (QuakeFrame >= -4)
  {
    LOWORD(QuakeFrame) = QuakeFrame;
    v33 = (s16)QuakeFrame + 5;
    v34 = QuakeXRange - QuakeXRange / v33;
    v35 = QuakeYRange - QuakeYRange / v33;
    QuakeXRange = v34;
    QuakeYRange = v35;
  }
  --QuakeFrame;
}

// 0x2289470
void dds3SetQuake(s32 frame, u32 range) {
  u32 v11;

  if (!range)
  {
    QuakeFlag = 0;
    return;
  }
  QuakeFlag = 1;
  if (frame)
  {
    QuakeFrame = frame;
    goto LABEL_18;
  }
  if (!v11)
  {
    QuakeFrame = -5;
    goto LABEL_18;
  }
  QuakeFrame = -5;
LABEL_18:
  QuakeYRange = 10 * range;
  QuakeXRange = (429496730 * (u64)(4 * ((10 * range) & 0xFFFE))) >> 32;
  if (!frame)
    return;
  if (QuakeFrame <= QuakeFrame)
    return;
}

// 0x2289650
void dds3StopQuake(void) {
  QuakeFlag = 0;
  QuakeFrame = 0;
  *(u64 *)&CameraOffset.x = 0;
  *(u64 *)&CameraOffset.z = 0;
}

// 0x22896c0
bool dds3CheckQuake(void) {
  return QuakeFlag;
}

// 0x2289740
void dds3FadeClear(void) {
  DrawFlag &= 0xFFFFFFFC;
  fadergba = zeroVector;
}

// 0x22897f0
void dds3FadeSet(const sdfVector4_t *rgba) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  f32 *static_fields;
  s32 v8;

  w = rgba->w;
  z = rgba->z;
  y = rgba->y;
  x = rgba->x;
  static_fields[180] = z;
  v8 = *((u32 *)static_fields + 165);
  static_fields[181] = w;
  static_fields[178] = x;
  static_fields[179] = y;
  *((u32 *)static_fields + 165) = v8 & 0xFFFFFFFC;
}

// 0x2289890
void dds3FadeSet_2(u32 r, u32 g, u32 b, u32 a) {
  f32 v10;
  f32 *static_fields;
  f32 v12;
  char v13;
  f32 v14;
  f32 v15;

  v10 = (f32)r / 255.0;
  static_fields[178] = v10;
  v12 = (f32)g / 255.0;
  v13 = byte_575950C;
  static_fields[179] = v12;
  v14 = (f32)b / 255.0;
  v15 = (f32)a * 0.0078125;
  static_fields[181] = v15;
  static_fields[180] = v14;
  fadergba.x = v10;
  fadergba.y = v12;
  fadergba.z = v14;
  fadergba.w = v15;
  DrawFlag = DrawFlag & 0xFFFFFFFC;
}

// 0x22899b0
sdfVector4_t dds3GetFadeParam(void) {
  f32 *static_fields;
  sdfVector4_t result;

  result.x = static_fields[178];
  result.y = static_fields[179];
  result.z = static_fields[180];
  result.w = static_fields[181];
  return result;
}

// 0x2289a20
void dds3FadeModeSet(DDS3_FADEMODE mode) {
  fademode = mode;
  return;
}

// 0x2289ab0
DDS3_FADETYPE dds3FadeTypeGet(void) {
  return fadetype;
}

// 0x2289b30
static void FadeTypeSet(DDS3_FADETYPE eType) {
  fadetype = eType;
  return;
}

// 0x2289bc0
void dds3FadeIn(u32 r, u32 g, u32 b, u32 frame) {
  float32x2_t *static_fields;

  static_fields[89].n64_u64[0] = vdiv_f32(vcvt_f32_u32((uint32x2_t)__PAIR64__(g, r)), vdup_n_s32(0x437F0000u)).n64_u64[0];
  static_fields[90].n64_f32[0] = (f32)b / 255.0;
  dds3FadeIn2(frame);
  if (!frame)
  {
    DrawFlag &= 0xFFFFFFFC;
    fadergba = zeroVector;
    return;
  }
}

// 0x2289d40
void dds3FadeIn2(u32 frame) {
  fadergba.w = 1.0;
  fadenow = frame;
  fademax = frame;
  if (frame)
  {
    DrawFlag = DrawFlag & 0xFFFFFFFC | 1;
  }
  else
  {
    *(u32 *)&fadenow = 0;
    fadergba.w = 0.0;
    DrawFlag = DrawFlag & 0xFFFFFFFC;
    DrawFlag &= 0xFFFFFFFC;
    fadergba = zeroVector;
  }
  fadetype = 1;
}

// 0x2289ef0
void dds3FadeOut(u32 r, u32 g, u32 b, u32 frame) {
  float32x2_t *static_fields;

  static_fields[89].n64_u64[0] = vdiv_f32(vcvt_f32_u32((uint32x2_t)__PAIR64__(g, r)), vdup_n_s32(0x437F0000u)).n64_u64[0];
  static_fields[90].n64_f32[0] = (f32)b / 255.0;
  dds3FadeOut2(frame);
}

// 0x2289fa0
void dds3FadeOut2(u32 frame) {
  fadergba.w = 0.0;
  fadenow = 0;
  fademax = frame;
  if (!frame)
  {
    fadergba.w = 1.0;
    DrawFlag &= 0xFFFFFFFC;
    goto LABEL_8;
  }
  DrawFlag = DrawFlag & 0xFFFFFFFC | 2;
LABEL_8:
  fadetype = 2;
}

// 0x228a0f0
bool dds3FadeCheck(void) {
  return (DrawFlag & 3) != 0;
}

// 0x228a160
bool dds3FadeOutCheck2(void) {
  if ((DrawFlag & 3) != 0)
    return 1;
  if (fadergba.w == 1.0)
    return 1;
  return 0;
}

// 0x228a240
bool dds3IsPMV_Fade(void) {
  return fadergba.w != 0.0;
}

// 0x228a2b0
void dds3FadeUpdate(void) {
  u32 v1;
  s32 fademax_local;
  u32 v10;

  if ((DrawFlag & 3) == 0)
    return;
  if ((DrawFlag & 1) == 0)
  {
    fademax_local = fademax;
    ++fadenow;
    goto LABEL_22;
  }
  fademax_local = 0;
  --fadenow;
LABEL_22:
  LOWORD(v1) = fademax;
  fadergba.w = (f32)fadenow / (f32)v1;
  if (fademax_local == fadenow)
  {
    v10 = DrawFlag;
    *(u32 *)&fadenow = 0;
    DrawFlag = v10 & 0xFFFFFFFC;
  }
}

// 0x228a450
void dds3DrawFade(void) {
  float32x2_t *static_fields;
  float32x2_t v3;
  int32x2_t v4;
  float32x2_t v5;
  int32x2_t v6;
  sdfColor_t Pixel;

  v3.n64_u64[0] = vsub_f32(static_fields[94], static_fields[89]).n64_u64[0];
  v4.n64_u64[0] = vmul_f32(v3, v3).n64_u64[0];
  v5.n64_u64[0] = vsub_f32(static_fields[95], static_fields[90]).n64_u64[0];
  v6.n64_u64[0] = vmul_f32(v5, v5).n64_u64[0];
  if (vadd_f32(vdup_lane_s32(v6, 1), vadd_f32(v6, vadd_f32(v4, vdup_lane_s32(v4, 1)))).n64_f32[0] >= 9.9999994e-11)
  {
    *(_OWORD *)static_fields[94].n64_u64 = *(_OWORD *)static_fields[89].n64_u64;
    set_enabled(fadeImage, fadergba.w > 0.0, 0);
    (fadeImage->klass->vtable._23_set_color.methodPtr)(fadeImage, fadeImage->klass->vtable._23_set_color.fadergba.x, fadergba.y, fadergba.z, fadergba.w);
LABEL_7:
    if (fadergba.w == 1.0)
      goto LABEL_8;
    return;
  }
  {
    goto LABEL_7;
  }
  if (fadergba.w == 1.0)
  {
LABEL_8:
    Pixel = GetPixel(fadeTex, 0, 0, 0);
    fadergba = (sdfColor_t)fadergba;
    if ((f32)((f32)((f32)(Pixel.a - fadergba.a) * (f32)(Pixel.a - fadergba.a)) + (f32)((f32)((f32)(Pixel.b - fadergba.b) * (f32)(Pixel.b - fadergba.b)) + (f32)((f32)((f32)(Pixel.r - fadergba.r) * (f32)(Pixel.r - fadergba.r)) + (f32)((f32)(Pixel.g - fadergba.g) * (f32)(Pixel.g - fadergba.g))))) >= 9.9999994e-11)
    {
      fadergba = (sdfColor_t)fadergba;
      SetPixel(fadeTex, 0, 0, fadergba, 0);
      Apply_60860784(fadeTex, 0);
LABEL_12:
      goto LABEL_13;
    }
    {
      goto LABEL_12;
    }
LABEL_13:
    _Alternative_k__BackingField = fadeTex;
    return;
  }
}

// 0x228a750
void dds3BistaClear(void) {
  struct DDS3_DRAW_BISTA v4;

  bistaAlpha = 0.0;
  DrawFlag &= 0xF3FFFFFF;
  v4 = TOP;
  s_bistamode = 0;
  s_bista_harf_cnt = 0;
  s_bista_bustup = 0;
  *(struct DDS3_DRAW_BISTA *)&s_top_mod = v4;
}

// 0x228a810
void dds3BistaIn(u32 frame) {
  struct DDS3_DRAW_BISTA v8;

  if (bistaAlpha == 0.0)
    return;
  if (frame)
  {
    bistanow = frame;
    bistamax = frame;
    bistaAlpha = 1.0;
    DrawFlag = DrawFlag & 0xF3FFFFFF | 0x4000000;
    goto LABEL_12;
  }
  *(u32 *)&bistanow = 0;
  bistaAlpha = 0.0;
  bistaAlpha = 0.0;
  DrawFlag &= 0xF3FFFFFF;
  v8 = TOP;
  s_bistamode = 0;
  s_bista_harf_cnt = 0;
  s_bista_bustup = 0;
  *(struct DDS3_DRAW_BISTA *)&s_top_mod = v8;
LABEL_12:
  ScreenParam->oy = 2048.0;
  return;
}

// 0x228a9f0
void dds3BistaOutEx(u32 frame, u32 btm_h) {
  u32 v10;

  if (s_bistamode == 3)
  {
    goto LABEL_5;
  }
  bistaAlpha = 0.0;
LABEL_5:
  if (btm_h >= 0x80)
    LOWORD(btm_h) = 128;
  bistanow = 0;
  bistamax = frame;
  s_bista_bustup = 0;
  v10 = 128 - (u16)btm_h;
  BTM = btm_h;
  TOP = 128 - btm_h;
  if (v10 >= (u16)btm_h)
  {
    TOP = btm_h;
    if (frame)
      goto LABEL_13;
LABEL_25:
    bistaAlpha = 1.0;
    *(u32 *)&bistanow = 0;
    *(u32 *)&s_top_mod = 0;
    DrawFlag &= 0xF3FFFFFF;
    goto LABEL_17;
  }
  LOWORD(v10) = TOP;
  BTM = v10;
  if (!frame)
    goto LABEL_25;
LABEL_13:
  DrawFlag = DrawFlag & 0xF3FFFFFF | 0x8000000;
LABEL_17:
  ScreenParam->oy = 2048.0;
}

// 0x228ac20
void dds3BistaOut(u32 frame) {
  u32 v5;

  v5 = frame;
  dds3BistaOutEx(v5, 0x4Fu);
}

// 0x228acb0
bool dds3BistaCheck(void) {
  s32 v4;

  if ((DrawFlag & 0xC000000) != 0)
    return 1;
  if (s_bistamode > 5)
    return 1;
  v4 = 1 << s_bistamode;
  if ((v4 & 0x26) == 0)
  {
    if ((v4 & 9) == 0)
      return 0;
    return bistaAlpha > 0.0;
  }
  s_top_mod = (u16)s_top_mod;
  return s_top_mod != TOP;
}

// 0x228ae40
bool dds3IsEventBista(void) {
  return 0;
}

// 0x228ae50
void dds3SetBistaBustUp(void) {
  s_bista_bustup = 1;
  return;
}

// 0x228aee0
bool dds3IsBistaZBufferClear(void) {
  return s_bistamode == 4;
}

// 0x228af50
void dds3ChangeBistaMode(BISTA_MODE bistamode) {
  s_bistamode = bistamode;
  if ((u32)bistamode > 5)
    return;
  if (((1 << bistamode) & 0x26) != 0)
  {
    bistaAlpha = 1.0;
  }
  else if (((1 << bistamode) & 9) != 0)
  {
    *(u32 *)&s_top_mod = 0;
  }
}

// 0x228b090
void dds3BistaUpdate(void) {
  u32 v1;
  u32 v2;
  s16 v6;
  f32 v10;
  f32 v11;
  f32 v13;
  s32 v14;
  bool v15;
  f32 v16;
  u32 v17;
  s32 v18;
  u32 v19;

  if ((DrawFlag & 0xC000000) == 0)
    return;
  if ((DrawFlag & 0x4000000) != 0)
    v6 = -1;
  else
    v6 = 1;
  bistanow += v6;
  LOWORD(v1) = bistanow;
  LOWORD(v2) = bistamax;
  v10 = (f32)v1 / (f32)v2;
  v11 = 1.0 - v10;
  bistaAlpha = v10;
  v13 = v11 * (f32)TOP;
  v14 = v13;
  v15 = v13 == INFINITY;
  v16 = v11 * (f32)BTM;
  if (v15)
    LOWORD(v14) = 0;
  s_top_mod = v14;
  v18 = v16;
  if (v16 == INFINITY)
    LOWORD(v18) = 0;
  s_down_mod = v18;
  v19 = DrawFlag;
  if ((v19 & 0x4000000) != 0)
  {
    if (v17)
    {
      if (bistanow)
        return;
    }
    else
    {
      if (bistanow)
        return;
    }
    goto LABEL_39;
  }
  if (v17)
  {
    if ((v19 & 0x8000000) == 0)
      goto LABEL_39;
  }
  else
  {
    if ((DrawFlag & 0x8000000) == 0)
      goto LABEL_39;
  }
  if (bistanow != bistamax)
    return;
LABEL_39:
  *(u32 *)&bistanow = 0;
  DrawFlag &= 0xF3FFFFFF;
}

// 0x228b2f0
void dds3DrawBista(void) {
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  s32 v9;
  s32 v15;
  s32 v17;
  void *v21;
  void *p_bistaFadeMesh;
  struct DDS3_DRAW_BISTA v31;
  sdfVector4_t v32;
  sdfVector4_t v33;
  sdfVector4_t v34;
  sdfVector4_t v35;

  x = zeroVector.x;
  y = zeroVector.y;
  z = zeroVector.z;
  w = zeroVector.w;
  if (s_bistamode <= 5)
  {
    v9 = 1 << s_bistamode;
    if ((v9 & 0x26) != 0)
    {
      s_top_mod = (u16)s_top_mod;
      TOP = (u16)TOP;
      if (s_top_mod == TOP)
      {
LABEL_26:
        DelMesh(bistaFadeMesh);
        return;
      }
      w = 1.0;
      v15 = s_top_mod;
      goto LABEL_36;
    }
    if ((v9 & 9) == 0)
      return;
    w = bistaAlpha;
    if (w <= 0.0)
      goto LABEL_26;
    v15 = 0;
    w = bistaAlpha;
    goto LABEL_36;
  }
  v15 = 0;
LABEL_36:
  v17 = s_bistamode;
  switch (v17)
  {
    case 5:
      w = (f32)((f32)((f32)(TOP - v15) * 0.4296875) / (f32)TOP) * 1.5;
LABEL_44:
      if (op_Equality(bistaFadeMesh, 0, 0))
      {
        v21 = eglNewMesh2D(0);
        p_bistaFadeMesh = &bistaFadeMesh;
        p_bistaFadeMesh = v21;
        bistaFadeMesh->type = 0;
LABEL_54:
        eglSetOt(85);
        eglLinkAlpha(0);
        eglLinkTest(SET_10AADD11);
        eglLinkMesh(bistaFadeMesh);
        v34.x = x;
        v34.y = y;
        v34.z = z;
        v35.x = x;
        v35.y = y;
        v35.z = z;
        v34.w = w;
        v35.w = w;
        *(u64 *)&v32.x = 0;
        LinkBox(0, 0, 512, 448, v34, v35, v32, v33, __PAIR64__(LODWORD(y), LODWORD(x)));
        return;
      }
      goto LABEL_54;
    case 3:
LABEL_42:
      goto LABEL_44;
    case 2:
      w = (f32)((f32)(TOP - v15) * 0.4296875) / (f32)TOP;
      goto LABEL_42;
  }
  DrawFlag &= 0xF3FFFFFF;
  bistaAlpha = 0.0;
  v31 = TOP;
  s_bistamode = 0;
  s_bista_harf_cnt = 0;
  s_bista_bustup = 0;
  *(struct DDS3_DRAW_BISTA *)&s_top_mod = v31;
}

// 0x228b8b0
void dds3SetScreenFovy(f32 fovy) {
  ScreenParam->fovy = fovy;
}

// 0x228b920
void dds3SetAmbient(const sdfVector4_t *ambient) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  f32 *static_fields;

  w = ambient->w;
  z = ambient->z;
  y = ambient->y;
  x = ambient->x;
  static_fields[60] = z;
  static_fields[61] = w;
  static_fields[58] = x;
  static_fields[59] = y;
}

// 0x228b9b0
void dds3SetFog(sdf3DFogParam_t *fog) {
  sdf3DFogParam_t *v3;

  v3 = Clone(fog, 0);
  FogParam = v3;
}

// 0x228ba30
void dds3SetLight(sdf3DLight_t *light, u32 no) {
  sdf3DLight_t *DirLights_local;
  sdf3DLight_t *v7;
  sdf3DLight_t *v8;
  Il2CppClass **v9;

  DirLights_local = DirLights;
  v7 = Clone(light, 0);
  v8 = v7;
  v9 = &DirLights_local->obj.klass + no;
  v9[4] = v8;
}

// 0x228bae0
void dds3SetBlur(u32 frame, s32 alpha, s32 scale) {
  if (frame)
  {
    bluralphatarget = alpha;
    blurscaletarget = scale;
    blurnow = 0;
    blurmax = frame;
    *(u32 *)&bluralphabase = *(u32 *)&ScreenBlurAlpha;
    DrawFlag |= 0x800u;
  }
  else
  {
    ScreenBlurAlpha = alpha;
    ScreenBlurScale = scale;
    ScreenBlurFlag = (scale | alpha) != 0;
    DrawFlag &= ~0x800u;
  }
}

// 0x228bbf0
void dds3BlurUpdate(void) {
  s32 v3;
  s32 v7;
  s32 v8;
  bool v9;

  if ((DrawFlag & 0x800) == 0)
    goto LABEL_16;
  v3 = blurnow + 1;
  v7 = (bluralphatarget - bluralphabase) * v3;
  blurnow = v3;
  LOWORD(bluralphabase) = bluralphabase + v7 / blurmax;
  ScreenBlurAlpha = bluralphabase;
  v8 = blurscalebase + (blurscaletarget - blurscalebase) * v3 / blurmax;
  ScreenBlurScale = v8;
  if ((u16)bluralphabase)
  {
    v9 = 1;
    goto LABEL_12;
  }
  v9 = (u16)v8 != 0;
LABEL_12:
  ScreenBlurFlag = v9;
  if (blurnow >= blurmax)
  {
    DrawFlag &= ~0x800u;
  }
LABEL_16:
  _Update(Blur2);
  _Update(MultiBlur);
  _Update(DistBlur);
  _Update(RipBlur);
  _Update(Filter2);
  _Update(MFilter);
}

// 0x228be70
void dds3RotationArc(void) {
  struct sdfVector4_t v8;
  u64 v10;
  f32 v11;
  f32 *p_x;
  f32 v16;
  f32 v17;
  f32 v18;
  f32 v19;
  f32 v20;
  f32 v21;
  f32 v22;
  f32 v23;
  f32 v25;
  f32 v26;
  int32x2_t v27;
  int32x2_t v28;
  float32x2_t v29;
  f32 v30;
  float32x2_t v31;
  f32 v32;
  u32 v35;
  f32 z;
  f32 x;
  f32 v39;
  f32 *v43;
  f32 v44;
  f32 v45;
  f32 v46;
  f32 v47;
  f32 v48;
  f32 v49;
  f32 v50;
  f32 v51;
  f32 v53;
  f32 v54;
  int32x2_t v55;
  int32x2_t v56;
  float32x2_t v57;
  f32 v58;
  float32x2_t v59;
  f32 v60;

  vct_A.w = 0.0;
  sub_1949110(0);
  vct_A = vct_B;
  vct_B = vct_A;
  vct_A.w = 0.0;
  sub_1949110(0);
  v8 = vct_A;
  vct_A = vct_B;
  vct_B = v8;
  v10 = vmul_f32(*(float32x2_t *)&vct_A.y, *(float32x2_t *)&vct_B.y).n64_u64[0];
  v11 = *((f32 *)&v10 + 1) + (f32)((f32)(vct_A.x * vct_B.x) + *(f32 *)&v10);
  if (v11 >= 0.9999)
  {
    vct_A = uq;
    return;
  }
  if (v11 > -0.9999)
  {
    vct_C = vct_A;
    vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    sub_1949110(0);
    vct_B = vct_C;
    p_x = &vf00.x;
    v16 = p_x[6];
    v17 = p_x[4];
    v18 = p_x[5];
    v19 = p_x[10];
    v20 = p_x[8];
    v21 = p_x[9];
    v22 = v17 * v20;
    v23 = v18 * v21;
    v25 = v22 + v23;
    v26 = v16 * v19;
    v27.n64_u64[0] = *(u64 *)&vct_B.y;
    v28.n64_u64[0] = *(u64 *)&vct_A.y;
    v29.n64_u32[0] = vdup_lane_s32(v27, 1).n64_u32[0];
    v29.n64_u32[1] = LODWORD(vct_B.x);
    v30 = v29.n64_f32[1] * v28.n64_f32[0];
    v31.n64_u64[0] = vmul_f32(v28, v29).n64_u64[0];
    v28.n64_u32[0] = vdup_lane_s32(v28, 1).n64_u32[0];
    v28.n64_u32[1] = LODWORD(vct_A.x);
    vct_A.z = (f32)(v28.n64_f32[1] * v27.n64_f32[0]) - v30;
    *(float32x2_t *)&vct_A.x = vsub_f32(v31, vmul_f32(v28, v27));
    v32 = v26 + v25;
    vct_A.w = v32;
    Normalize();
    return;
  }
  if (fabsf(vct_A.y) < 0.9999)
  {
    if (v35)
    {
      goto LABEL_52;
    }
    else
    {
LABEL_52:
      goto LABEL_53;
    }
LABEL_53:
    z = vct_A.z;
    x = vct_A.x;
    v39 = -z;
    vct_A.x = v39;
    vct_A.y = 0.0;
    vct_A.z = x;
    vct_A.w = 0.0;
    sub_1949110(0);
    goto LABEL_72;
  }
  if (v35)
  {
    goto LABEL_65;
  }
  else
  {
LABEL_65:
    goto LABEL_66;
  }
LABEL_66:
  vct_A = vf00;
  vct_A.w = 0.0;
  vct_A.z = -1.0;
LABEL_72:
  v43 = &vf00.x;
  v44 = v43[6];
  v45 = v43[4];
  v46 = v43[5];
  v47 = v43[10];
  v48 = v43[8];
  v49 = v43[9];
  v50 = v45 * v48;
  v51 = v46 * v49;
  v53 = v50 + v51;
  v54 = v44 * v47;
  v55.n64_u64[0] = *(u64 *)&vct_B.y;
  v56.n64_u64[0] = *(u64 *)&vct_A.y;
  v57.n64_u32[0] = vdup_lane_s32(v55, 1).n64_u32[0];
  v57.n64_u32[1] = LODWORD(vct_B.x);
  v58 = v57.n64_f32[1] * v56.n64_f32[0];
  v59.n64_u64[0] = vmul_f32(v56, v57).n64_u64[0];
  v56.n64_u32[0] = vdup_lane_s32(v56, 1).n64_u32[0];
  v56.n64_u32[1] = LODWORD(vct_A.x);
  vct_A.z = (f32)(v56.n64_f32[1] * v55.n64_f32[0]) - v58;
  *(float32x2_t *)&vct_A.x = vsub_f32(v59, vmul_f32(v56, v55));
  v60 = v54 + v53;
  vct_A.w = v60;
}

// 0x228c850
void dds3SetLightColor(u32 frame, u32 no, const sdfVector4_t *col) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  sdf3DLight_t *v12;
  s64 v13;
  s32 v14;
  s64 v16;
  s64 v17;
  f32 *p_x;
  sdf3DLight_t *p_fields;
  f32 *v22;

  w = col->w;
  z = col->z;
  y = col->y;
  x = col->x;
  v12 = DirLights[no];
  if (!v12)
    return;
  v13 = no;
  v14 = 4 << (2 * (no & 0xF));
  if (frame)
  {
    v12 = DirLights[v13];
    DrawFlag |= v14;
    lightrgbnow[v13] = 0;
    v16 = (s64)lightrgbmax + 4 * v13;
    v17 = (s64)lightrgbbase + 16 * v13;
    *(u32 *)(v16 + 32) = frame;
    *(sdfVector4_t *)(v17 + 32) = v12->color;
    p_x = &vf00.x;
    p_x[4] = x;
    p_x[5] = y;
    p_x[6] = z;
    p_x[7] = w;
    vct_A.w = 0.0;
    p_fields = &lightrgbtarget[v13];
    goto LABEL_17;
  }
  DrawFlag &= ~v14;
  v22 = &vf00.x;
  v22[4] = x;
  v22[5] = y;
  v22[6] = z;
  v22[7] = w;
  vct_A.w = 0.0;
  p_fields = &DirLights[v13]->fields;
LABEL_17:
  p_fields->color = vct_A;
  return;
}

// 0x228cbe0
void dds3SetLightDir(u32 frame, u32 no, const sdfVector4_t *dir) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  s64 v12;
  s32 v13;
  s64 v15;
  s64 v16;
  f32 *p_x;
  struct sdfVector4_t v;
  Il2CppObject *v21;
  Il2CppObject *v23;
  sdfVector4_t *p_v;
  f32 *v26;

  w = dir->w;
  z = dir->z;
  y = dir->y;
  x = dir->x;
  if (!DirLights[no])
    return;
  v12 = no;
  v13 = 8 << (2 * (no & 0xF));
  if (frame)
  {
    DrawFlag |= v13;
    v15 = (s64)lightdirnow + 4 * v12;
    v16 = (s64)lightdirmax + 4 * v12;
    *(u32 *)(v15 + 32) = 0;
    *(u32 *)(v16 + 32) = frame;
    p_x = &vf00.x;
    p_x[4] = x;
    p_x[5] = y;
    p_x[6] = z;
    p_x[7] = w;
    vct_A.w = 0.0;
    sub_1949110(0);
    vct_B = vct_A;
    v = DirLights[v12]->v;
    vct_A = v;
    vct_A.w = 0.0;
    sub_1949110(0);
    v21 = &lightdirbase->obj + v12;
    v23 = v21 + 2;
    *v23 = *((Il2CppObject *)*((MethodInfo *)SDF_VU0 + 2).virtualMethodPointer + 1);
    dds3RotationArc();
    p_v = &lightdirquat[v12];
    goto LABEL_39;
  }
  DrawFlag &= ~v13;
  v26 = &vf00.x;
  v26[4] = x;
  v26[5] = y;
  v26[6] = z;
  v26[7] = w;
  sub_1949110(0);
  vct_A.w = 0.0;
  p_v = &DirLights[v12]->v;
LABEL_39:
  *p_v = vct_A;
}

// 0x228d0d0
void dds3SetAmbientColor(u32 frame, const sdfVector4_t *col) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  f32 *p_x;
  sdfVector4_t *p_ambienttarget;
  f32 *v19;

  w = col->w;
  z = col->z;
  y = col->y;
  x = col->x;
  if (frame)
  {
    ambientnow = 0;
    ambientmax = frame;
    DrawFlag = DrawFlag | 0x100;
    ambientbase = Ambient;
    p_x = &vf00.x;
    p_x[4] = x;
    p_x[5] = y;
    p_x[6] = z;
    p_x[7] = w;
    vct_A.w = 1.0;
    p_ambienttarget = &ambienttarget;
    goto LABEL_13;
  }
  DrawFlag &= ~0x100u;
  v19 = &vf00.x;
  v19[4] = x;
  v19[5] = y;
  v19[6] = z;
  v19[7] = w;
  vct_A.w = 1.0;
  p_ambienttarget = &Ambient;
LABEL_13:
  *p_ambienttarget = vct_A;
}

// 0x228d3b0
void dds3SceneLightUpdateFirst(void) {
  s64 v1;
  s32 v3;
  s64 (__fastcall **v4)();
  s64 v7;
  s32 v9;
  char *v10;
  s32 v11;
  s32 v12;
  sdfVector4_t v14;
  sdf3DLight_t *v15;
  s64 (__fastcall **v19)();
  char *v20;
  s32 v21;
  s32 v22;
  sdfVector4_t v24;
  sdfVector4_t v25;
  sdf3DLight_t *v28;
  s32 v31;
  f32 v34;
  f32 v36;
  f32 v37;
  struct sdfVector4_t ambienttarget_local;
  sdfVector4_t *p_Ambient;
  struct sdfVector4_t v49;
  f32 v50;
  f32 v56;
  sdfMatrix4_t v57;
  sdfMatrix4_t v58;
  sdfVector4_t v59;

  v1 = 0;
  v3 = 4;
  v4 = off_5755000;
  do
  {
    if (!DirLights[v1])
    {
      v9 = v3 | (2 * v3);
LABEL_58:
      DrawFlag &= ~v9;
      goto LABEL_4;
    }
    v7 = v1;
    if ((DrawFlag & v3) == 0)
      goto LABEL_36;
    v10 = (char *)lightrgbnow + v7 * 4;
    v11 = *((u32 *)v10 + 8) + 1;
    *((u32 *)v10 + 8) = v11;
    v12 = lightrgbmax[v7];
    v49 = lightrgbbase[v1];
    vct_A = v49;
    v50 = (f32)v11 / (f32)v12;
    vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, 1.0 - v50);
    vct_B = vct_A;
    v14 = lightrgbtarget[v1];
    vct_A = v14;
    vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v50);
    vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    v15 = DirLights[v1];
    if (*((u8 *)v4 + 3830))
    {
      goto LABEL_32;
    }
    else
    {
      *((u8 *)v4 + 3830) = 1;
      goto LABEL_32;
    }
LABEL_32:
    v15->color = vct_A;
    if (lightrgbnow[v7] >= lightrgbmax[v7])
    {
      DrawFlag &= ~v3;
    }
LABEL_36:
    v9 = 2 * v3;
    if ((DrawFlag & (2 * v3)) == 0)
      goto LABEL_4;
    v19 = v4;
    v20 = (char *)lightdirnow + v7 * 4;
    v21 = *((u32 *)v20 + 8) + 1;
    *((u32 *)v20 + 8) = v21;
    v22 = lightdirmax[v7];
    vct_A = vf00;
    vct_A.w = 1.0;
    v24 = lightdirquat[v1];
    vct_B = v24;
    Lerp((f32)v21 / (f32)v22);
    ToMatrix();
    v25 = lightdirbase[v1];
    v4 = v19;
    vct_A = v25;
    get_transpose(&v58, &mtx_A, 0);
    v57 = v58;
    v59 = op_Multiply_60923920(&v57, vct_A, 0);
    vct_A = v59;
    v28 = DirLights[v1];
    if (*((u8 *)v4 + 3830))
    {
LABEL_55:
      v28->v = vct_A;
      if (lightdirnow[v7] < lightdirmax[v7])
        goto LABEL_4;
      goto LABEL_58;
    }
    else
    {
      *((u8 *)v4 + 3830) = 1;
      goto LABEL_55;
    }
    goto LABEL_55;
LABEL_4:
    ++v1;
    v3 *= 4;
  }
  while (v1 != 3);
  if ((DrawFlag & 0x100) == 0)
    return;
  v31 = ambientnow + 1;
  ambientnow = v31;
  v34 = v31;
  v36 = ambientmax;
  vct_A = ambientbase;
  v56 = v34 / v36;
  v37 = 1.0 - (f32)(v34 / v36);
  goto LABEL_98;
LABEL_99:
  goto LABEL_100;
LABEL_98:
  vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v37);
  goto LABEL_99;
LABEL_100:
  vct_B = vct_A;
  ambienttarget_local = ambienttarget;
  goto LABEL_102;
LABEL_103:
  goto LABEL_104;
LABEL_102:
  vct_A = ambienttarget_local;
  goto LABEL_103;
LABEL_104:
  vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v56);
  goto LABEL_106;
LABEL_107:
  goto LABEL_108;
LABEL_106:
  vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  goto LABEL_107;
LABEL_108:
  vct_A.w = 1.0;
  if (*((u8 *)v4 + 3830))
  {
    p_Ambient = &Ambient;
LABEL_110:
    *p_Ambient = vct_A;
    if (ambientnow >= ambientmax)
    {
      DrawFlag &= ~0x100u;
    }
    return;
  }
  else
  {
    *((u8 *)v4 + 3830) = 1;
    p_Ambient = &Ambient;
    goto LABEL_110;
  }
  goto LABEL_110;
}

// 0x228df30
void dds3FilterDefaultLoad(void *objList) {
  void *Asset_object;
  s64 naturalAligment;
  FIL_t *v5;
  FIL_t **p_gFilterBuff;
  s64 i;
  s32 *gFilterBuff_local;
  FIL_t *v11;
  s32 *v12;
  s64 v13;
  s32 v14;
  s64 v15;
  int8x16_t v17;
  uint32x4_t v18;
  il2cpp_array_size_t v19;
  float32x4_t v20;
  sdfVector4_t *rgba;
  u32 v22;
  int8x16_t v23;

  Asset_object = GetAsset_object_(objList, "filter.fld");
  if (Asset_object)
    LOBYTE(Asset_object[7]._size) < (u32)naturalAligment || *((Project_dds3FilterData_c **)(Asset_object)[5].klass + naturalAligment - 1) != Project_dds3FilterData;
  v5 = NewSpecific(FIL_t, Asset_object[3]->_size);
  p_gFilterBuff = &gFilterBuff;
  *p_gFilterBuff = v5;
  for (i = 0; ; ++i)
  {
    gFilterBuff_local = gFilterBuff;
    if (i >= gFilterBuff_local[6])
      break;
    gFilterBuff_local = gFilterBuff;
    v11 = Allocate(FIL_t);
    _ctor(v11, 0);
    if (v11)
      QueryInterface(v11, *(void **)(*(u64 *)gFilterBuff_local + 64));
    v12 = &gFilterBuff_local[2 * i];
    *((u64 *)v12 + 4) = v11;
    v13 = 0;
    v14 = 0;
    v15 = 0;
    goto LABEL_25;
    while (1)
    {
      while (1)
      {
LABEL_25:
        rgba = gFilterBuff[i]->rgba;
        v22 = *((u32 *)&_get_Item(Asset_object[3], i)[1].klass->_1.byval_arg.data + v14 + (s32)v15);
        v23.n128_u32[0] = v22;
        v17.n128_u64[0] = 0xFF000000FFLL;
        v17.n128_u64[1] = 0xFF000000FFLL;
        v23.n128_u32[1] = v22 >> 8;
        v23.n128_u32[2] = HIWORD(v22);
        v18 = vandq_s8(v23, v17);
        v19 = v15 + v13 * rgba->bounds[1].length;
        ++v15;
        v18.n128_u32[3] = vshrq_n_u32(vdupq_n_s32(v22), 0x18u).n128_u32[3];
        v20.n128_u64[0] = 0x3C0000003C000000LL;
        v20.n128_u64[1] = 0x3C0000003C000000LL;
        rgba[v19] = (sdfVector4_t)vmulq_f32(vcvtq_f32_u32(v18), v20);
        if (v15 == 9)
          break;
      }
      ++v13;
      v14 += 9;
      if (v13 == 8)
        break;
      v15 = 0;
    }
  }
}

// 0x228e280
s32 dds3GetFilterTableCount(void) {
  return gFilterBuff->max_length;
}

// 0x228e310
void dds3FilterClear(void) {
  *(_OWORD *)&gFilterAnime = 0u;
  *(_OWORD *)&gFilterBlendIdx = 0u;
  gFilterMode = 1;
  *(u64 *)&gFilterAlpha = sub_80;
  dds3FilterDrawOnOff(0);
}

// 0x228e570
void dds3FilterSet(s32 idx, s32 mode, s32 hokan) {
  if (hokan)
  {
    gFilterBlend = 0.0;
    gFilterBlendIdx = gFilterNowIdx;
    gFilterBlendSpd = (f32)hokan;
  }
  else
  {
    gFilterBlend = 1.0;
    gFilterBlendIdx = idx;
    gFilterBlendSpd = 1.0;
  }
  gFilterNowIdx = idx;
  gFilterMode = mode;
  dds3FilterDrawOnOff(1);
}

// 0x228e650
void dds3FilterSetAnime(s32 type) {
  gFilterAnime = type;
  *(u64 *)&gFilterAnimeCntF = 0;
}

// 0x228e6c0
void dds3FilterSetAlpha(s32 alp) {
  gFilterAlpha = alp;
  return;
}

// 0x228e750
s32 dds3FilterGetAlpha(void) {
  return gFilterAlpha;
}

// 0x228e7d0
void dds3FilterSetAlphaOfs(s32 alp) {
  gFilterFilterAlpOfs = alp;
  return;
}

// 0x228e860
s32 dds3FilterGetAlphaOfs(void) {
  return gFilterFilterAlpOfs;
}

// 0x228e390
void dds3FilterDrawOnOff(s32 on_off) {
  void *v9;
  void *p_filterMesh;

  if (!on_off)
  {
LABEL_12:
    DelMesh(filterMesh);
    return;
  }
  if (!gFilterNowIdx)
    goto LABEL_12;
  if (!op_Equality(filterMesh, 0, 0))
    return;
  v9 = eglNewMesh2D(0);
  p_filterMesh = &filterMesh;
  p_filterMesh = v9;
  filterMesh->type = 0;
}

// 0x228e8e0
void dds3FilterCalc(void) {
  f32 *v7;
  f32 v8;
  f32 v9;
  f32 v10;
  f32 v11;
  f32 v12;
  f32 v13;
  f32 v14;
  f32 v15;
  s32 v16;

  if (!op_Inequality(filterMesh, 0, 0))
    return;
  v7 = FilterCalcTable[gFilterAnime];
  v8 = gFilterAnimeCntF + v7[0];
  v9 = v8 * 0.15915494;
  gFilterAnimeCntF = v8;
  v10 = -2147500000.0;
  if (v9 != INFINITY)
    v10 = (s32)v9;
  v11 = v9 - v10;
  v12 = 0.5;
  if (v11 <= 0.5)
  {
    if (v11 >= -0.5)
      goto LABEL_18;
    v13 = 1.0;
  }
  else
  {
    v13 = -1.0;
  }
  v11 = v11 + v13;
LABEL_18:
  if (v11 > 0.25)
  {
LABEL_21:
    v11 = v12 - v11;
    goto LABEL_22;
  }
  if (v11 < -0.25)
  {
    v12 = -0.5;
    goto LABEL_21;
  }
LABEL_22:
  v14 = v11 * 4.0;
  v15 = v7[1]
      * (f32)((f32)((f32)((f32)((f32)(v14 * 1.5707963) + (f32)((f32)(v14 * (f32)(v14 * v14)) * -0.6459637)) + (f32)((f32)((f32)(v14 * v14) * (f32)(v14 * (f32)(v14 * v14))) * 0.07968968)) + (f32)((f32)((f32)(v14 * v14) * (f32)((f32)(v14 * v14) * (f32)(v14 * (f32)(v14 * v14)))) * -0.0046737655)) + (f32)((f32)((f32)(v14 * v14) * (f32)((f32)(v14 * v14) * (f32)((f32)(v14 * v14) * (f32)(v14 * (f32)(v14 * v14))))) * 0.00015148419));
  v16 = v15;
  if (v15 == INFINITY)
    v16 = 0x80000000;
  gFilterAnimeOfsA = v16;
}

// 0x228eb20
void dds3FilterDraw(void) {
  f32 v9;
  f32 v11;
  s32 *v12;
  s32 v13;
  f32 v14;
  f32 v16;
  s64 v17;
  f32 v18;
  s64 v19;
  s32 v20;
  s64 v21;
  char v23;
  sdfVector4_t *rgba;
  float32x2_t *v25;
  f32 v26;
  float32x2_t v27;
  f32 v28;
  f32 v29;
  f32 v30;
  char v31;
  sdfVector4_t *v32;
  s64 v33;
  f32 v34;
  f32 v35;
  f32 v36;
  f32 v37;
  char v38;
  sdfVector4_t *v39;
  char v42;
  s64 v44;
  s64 v45;
  s64 v46;
  f32 v47;
  f32 v48;
  f32 v49;
  f32 v50;
  f32 v51;
  f32 v52;
  char v53;
  s64 v55;
  s64 v56;
  s64 v57;
  f32 v58;
  f32 v59;
  f32 v60;
  bool v61;
  f32 v62;
  f32 v63;
  f32 v64;
  f32 v65;
  float32x2_t v66;
  char v67;
  f32 v69;
  f32 v70;
  float32x2_t v71;
  f32 v72;
  float32x2_t v73;
  float32x2_t v74;
  float32x2_t v75;
  f32 v76;
  f32 v77;
  f32 v78;
  f64 v79;
  f32 v80;
  f64 v81;
  s64 v84;
  f32 v85;
  f32 v86;
  f32 v87;
  float32x2_t v88;
  f32 v89;
  f32 v90;
  f32 v91;
  f32 v92;
  f32 v93;
  f32 v94;
  f32 v95;
  float32x2_t v96;
  f32 v97;
  u64 v98;
  float32x2_t v99;
  f64 v100;
  f32 v101;
  f32 v102;
  float32x2_t v103;
  f32 v104;
  sdfVector4_t v105;
  sdfVector4_t v106;
  sdfVector4_t v107;
  sdfVector4_t v108;

  if (op_Equality(filterMesh, 0, 0))
    return;
  v9 = 1.0;
  if (gFilterBlend < 1.0)
  {
    v11 = gFilterBlend + (f32)(v9 / gFilterBlendSpd);
    gFilterBlend = v11;
    if (v11 > v9)
    {
      gFilterBlendIdx = gFilterNowIdx;
      gFilterBlend = 1.0;
    }
  }
  v13 = v12[249] + v12[253];
  v14 = v12[248];
  v94 = v14 * 0.0078125;
  eglSetOt(79);
  v16 = (f32)v13 * 0.0078125;
  eglLinkTest(SET_10AADD11);
  eglLinkAlpha(gFilterMode);
  eglLinkMesh(filterMesh);
  v17 = 0;
  v18 = 2.0;
  v19 = 1;
  v95 = v16;
  while (2)
  {
    v20 = 0;
    v84 = v17 + 1;
    v21 = 0;
    do
    {
      v23 = 1;
      rgba = gFilterBuff[gFilterNowIdx]->rgba;
      v25 = (&rgba->obj + v21 + v17 * rgba->bounds[1].length);
      v26 = v25[5].n64_f32[0];
      v27.n64_u64[0] = v25[4].n64_u64[0];
      v28 = v16 + v25[5].n64_f32[1];
      if (v28 <= v18)
        v29 = v16 + v25[5].n64_f32[1];
      else
        v29 = v18;
      if (v28 >= 0.0)
        v30 = v29;
      else
        v30 = 0.0;
      v97 = v30;
      v31 = 1;
      v32 = gFilterBuff[gFilterNowIdx]->rgba;
      v33 = &(&(&v32->bounds)[2 * v21])[2 * v17 * v32->bounds[1].length];
      v96.n64_u64[0] = *(u64 *)(v33 + 32);
      v34 = *(f32 *)(v33 + 40);
      v35 = v16 + *(f32 *)(v33 + 44);
      if (v35 <= v18)
        v36 = v16 + *(f32 *)(v33 + 44);
      else
        v36 = v18;
      if (v35 >= 0.0)
        v37 = v36;
      else
        v37 = 0.0;
      v38 = 1;
      v39 = gFilterBuff[gFilterNowIdx]->rgba;
      v99.n64_u64[0] = *(u64 *)&v39[v21 + v19 * v39->bounds[1].length].x;
      v103.n64_u64[0] = v27.n64_u64[0];
      v101 = v26;
      if (gFilterBlend >= v9)
      {
        goto LABEL_118;
      }
      v42 = 1;
      v44 = (s64)gFilterBuff + 8 * gFilterBlendIdx;
      v45 = gFilterBlendIdx;
      v46 = *(u64 *)(*(u64 *)(v44 + 32) + 16)
          + 16 * (v21 + v17 * *(u64 *)(*(u64 *)(*(u64 *)(*(u64 *)(v44 + 32) + 16) + 16) + 16));
      v47 = v16 + *(f32 *)(v46 + 44);
      if (v47 <= v18)
        v48 = v16 + *(f32 *)(v46 + 44);
      else
        v48 = v18;
      if (v47 >= 0.0)
        v49 = v48;
      else
        v49 = 0.0;
      v90 = v49;
      v91 = *(f32 *)(v46 + 40);
      v50 = gFilterBlend;
      if (v50 <= v9)
        v51 = gFilterBlend;
      else
        v51 = v9;
      if (v50 >= 0.0)
        v52 = v51;
      else
        v52 = 0.0;
      v89 = v52;
      v88.n64_u64[0] = *(u64 *)(v46 + 32);
      v92 = v37;
      v93 = v34;
      v53 = 1;
      v55 = (s64)gFilterBuff + 8 * v45;
      v56 = gFilterBlendIdx;
      v57 = *(u64 *)(*(u64 *)(v55 + 32) + 16)
          + 16
          + 16 * (v21 + v17 * *(u64 *)(*(u64 *)(*(u64 *)(*(u64 *)(v55 + 32) + 16) + 16) + 16));
      v58 = *(f32 *)(v57 + 40);
      v59 = v16 + *(f32 *)(v57 + 44);
      if (v59 <= v18)
        v60 = v16 + *(f32 *)(v57 + 44);
      else
        v60 = v18;
      v61 = v59 < 0.0;
      v62 = gFilterBlend;
      if (v61)
        v63 = 0.0;
      else
        v63 = v60;
      if (v62 <= v9)
        v64 = gFilterBlend;
      else
        v64 = v9;
      if (v62 >= 0.0)
        v65 = v64;
      else
        v65 = 0.0;
      v66.n64_u64[0] = *(u64 *)(v57 + 32);
      v87 = v65;
      v67 = 1;
      v69 = gFilterBlend;
      if (v69 <= v9)
        v70 = gFilterBlend;
      else
        v70 = v9;
      v71.n64_u64[0] = *(u64 *)&gFilterBuff[v56]->rgba[v21
                                                                                                + v19
                                                                                                * gFilterBuff[v56]->rgba->bounds[1].length].x;
      if (v69 >= 0.0)
        v72 = v70;
      else
        v72 = 0.0;
      if ((v67 & 1) == 0)
      {
        v85 = v72;
        v72 = v85;
      }
      v86 = v72;
      v72 = v86;
      v103.n64_u64[0] = vadd_f32(v88, vmul_n_f32(vsub_f32(v27, v88), v89)).n64_u64[0];
      v101 = v91 + (f32)((f32)(v26 - v91) * v89);
      v97 = v90 + (f32)((f32)(v97 - v90) * v89);
      v96.n64_u64[0] = vadd_f32(v66, vmul_n_f32(vsub_f32(v96, v66), v87)).n64_u64[0];
      v34 = v58 + (f32)((f32)(v93 - v58) * v87);
      v37 = v63 + (f32)((f32)(v92 - v63) * v87);
      v99.n64_u64[0] = vadd_f32(v71, vmul_n_f32(vsub_f32(v99, v71), v72)).n64_u64[0];
LABEL_118:
      v73.n64_u64[0] = vmul_n_f32(v103, v94).n64_u64[0];
      v74.n64_u64[0] = vmul_n_f32(v96, v94).n64_u64[0];
      v75.n64_u64[0] = vmul_n_f32(v99, v94).n64_u64[0];
      if (gFilterAlpha == 128)
        v76 = v37;
      else
        v76 = v94 * v37;
      if (gFilterAlpha == 128)
        v77 = v97;
      else
        v77 = v94 * v97;
      if (gFilterAlpha == 128)
        v78 = v101;
      else
        v78 = v94 * v101;
      if (gFilterAlpha == 128)
        v79 = v99.n64_f64[0];
      else
        v79 = v75.n64_f64[0];
      if (gFilterAlpha == 128)
      {
        v73.n64_u64[0] = v103.n64_u64[0];
        v80 = v34;
      }
      else
      {
        v80 = v94 * v34;
      }
      if (gFilterAlpha == 128)
        v81 = v96.n64_f64[0];
      else
        v81 = v74.n64_f64[0];
      v102 = v80;
      v104 = v76;
      v98 = v73.n64_u64[0];
      v100 = v81;
      v73.n64_u64[0] = v98;
      v81 = v100;
      v80 = v102;
      v76 = v104;
      *(u64 *)&v105.x = 0;
      ++v21;
      *(float32x2_t *)&v107.x = v73;
      v107.z = v78;
      v107.w = v77;
      *(f64 *)&v108.x = v81;
      v108.z = v80;
      v108.w = v76;
      LinkBox(v20, (u32)v17 << 6, 64, 64, v107, v108, v105, v106);
      v16 = v95;
      v9 = 1.0;
      v18 = 2.0;
      v20 += 64;
    }
    while (v21 != 8);
    ++v17;
    ++v19;
    if (v84 != 7)
      continue;
    break;
  }
  eglLinkTest(FilterDrawTest);
  eglLinkAlpha(0);
}

// 0x228f600
void dds3PostEspClear(void) {
  void *Instance;
  void *mDof;

  if ((DrawFlag2 & 3) == 0)
  {
    if (PostEsp_Alpha <= 0.0)
      goto LABEL_14;
  }
  Instance = get_Instance(0);
  if (!op_Inequality(Instance, 0, 0))
    goto LABEL_14;
  RestoreVignetteSetting(Instance, 0);
  RestoreFilmGrainSetting(Instance, 0);
  RestoreChromaticAberrationSetting(Instance, 0);
  RestoreLensDistortionSetting(Instance, 0);
  RestoreColorAdjustmentsSetting(Instance, 0);
  RestoreWhiteBalanceSetting(Instance, 0);
  RestoreBloomSetting(Instance, 0);
  mDof = Instance->mDof;
  if (!op_Inequality(Instance->mDof, 0, 0))
    goto LABEL_21;
  goto LABEL_9002;
  if (!op_Inequality(mDof, 0, 0))
  {
LABEL_21:
    SetForceActiveDofSetting(Instance, 0, 0);
    goto LABEL_15;
  }
LABEL_9002:
  RestoreDofSetting(Instance, 0);
  goto LABEL_21;
LABEL_14:
LABEL_15:
  *(u64 *)&PostEsp_Alpha = 0;
  DrawFlag2 &= 0xFFFFFFFC;
}

// 0x228f840
void dds3PostEspOff(u32 frame) {
  if (PostEsp_Alpha == 0.0)
    return;
  if (frame)
  {
    PostEsp_now = frame;
    PostEsp_max = frame;
    PostEsp_Alpha = 1.0;
    DrawFlag2 = DrawFlag2 & 0xFFFFFFFC | 2;
    sBtlStopSE(0x1010Au);
    sBtlPlaySE(0x1010Bu);
  }
  else
  {
    dds3PostEspClear();
  }
}

// 0x228f980
void dds3PostEspOn(u32 frame) {
  if (s_bistamode == 3)
  {
    goto LABEL_5;
  }
  PostEsp_Alpha = 0.0;
LABEL_5:
  PostEsp_now = 0;
  PostEsp_max = frame;
  if (frame)
  {
    DrawFlag2 = DrawFlag2 & 0xFFFFFFFC | 1;
    sBtlPlaySE(0x10109u);
    return;
  }
  *(u64 *)&PostEsp_Alpha = 1065353216;
  DrawFlag2 &= 0xFFFFFFFC;
}

// 0x228fb00
bool dds3PostEspCheck(void) {
  if ((DrawFlag2 & 3) != 0)
    return 1;
  if (PostEsp_Alpha > 0.0)
    return 1;
  return 0;
}

// 0x228fbd0
bool dds3PostEspCheck2(void) {
  if ((DrawFlag2 & 1) != 0)
    return 1;
  if ((DrawFlag2 & 2) != 0)
    return 0;
  if (PostEsp_Alpha > 0.0)
    return 1;
  return 0;
}

// 0x228fcc0
void dds3PostEspUpdate(void) {
  u32 v1;
  s16 v5;
  u32 v9;

  if ((DrawFlag2 & 3) == 0)
    return;
  if ((DrawFlag2 & 2) != 0)
    v5 = -1;
  else
    v5 = 1;
  PostEsp_now += v5;
  LOWORD(v1) = PostEsp_max;
  v9 = DrawFlag2;
  PostEsp_Alpha = (f32)PostEsp_now / (f32)v1;
  if ((v9 & 2) != 0)
  {
    if (PostEsp_now)
      return;
  }
  else
  {
    if ((v9 & 1) == 0)
      goto LABEL_38;
    if (PostEsp_now != PostEsp_max)
      return;
    {
      sBtlPlaySE(0x1010Au);
    }
  }
LABEL_38:
  if ((DrawFlag2 & 2) == 0)
    return;
  dds3PostEspClear();
}

// 0x228ff10
void dds3PostEspDraw(void) {
  void *Instance;
  void *mVign;
  f32 v6;
  void *mFilmG;
  void *mChro;
  void *mColorAdjustments;
  sdfColor_t v14;
  int32x2_t v15;
  float32x2_t v16;
  void *v18;
  f32 v19;
  f32 v20;
  f32 v21;
  void *v22;
  void *v23;
  void *v24;
  void *v25;
  void *v26;
  void *v27;
  void *v28;
  void *type;
  void *v30;
  void *response;
  void *v32;
  void *v34;
  f32 v35;
  f32 v36;
  f32 v37;
  void *v38;
  void *v40;
  f32 v41;
  f32 v42;
  f32 v43;
  void *v44;
  f32 v48;
  f32 v49;
  f32 v50;
  f32 v51;
  f32 v52;
  void *postExposure;
  void *v54;
  void *mBloom;
  void *mWhiteBalance;
  f32 v59;
  intptr_t m_CachedPtr;
  f32 v61;
  f32 v62;
  f32 v63;
  f32 v64;
  f32 v65;
  f32 v66;
  void *v67;
  UnityEngine_Object_c *klass;
  void *v69;
  void *monitor;
  void *v71;
  void *temperature;
  f32 v74;
  f32 v75;
  f32 v76;
  void *v77;
  void *mDof;
  sdfColor_t value;
  sdfVector2_t v80[2];
  sdfVector2_t v81;
  f32 scatter;
  s64 threshold;
  f32 smoothness;
  f32 intensity;
  sdfColor_t color;
  sdfVector2_t center;

  *(u64 *)&color.r = 0;
  *(u64 *)&color.b = 0;
  center = 0;
  intensity = 0.0;
  smoothness = 0.0;
  threshold = 0;
  scatter = 0.0;
  if (PostEsp_Alpha <= 0.0)
    return;
  Instance = get_Instance(0);
  if (op_Equality(Instance, 0, 0))
  {
    if (PostEsp_Alpha == 0.0)
      return;
    dds3PostEspClear();
    return;
  }
  mVign = Instance->mVign;
  v6 = 1.0;
  if (!op_Inequality(Instance->mVign, 0, 0))
    goto LABEL_19;
  goto LABEL_9002;
  if (!op_Inequality(mVign, 0, 0))
  {
LABEL_19:
    mFilmG = Instance->mFilmG;
    goto LABEL_20;
  }
LABEL_9002:
  if (!mVign->active)
    mVign->active = 1;
  GetVignetteSetting(Instance, &color, &center, &intensity, &smoothness, 0);
  v14 = color;
  *(sdfColor_t *)&v80[0].x = color;
  v14 = *(sdfColor_t *)&v80[0].x;
  v15.n64_u64[0] = 0;
  v16.n64_u64[0] = vsub_f32((float32x2_t)0x3F0000003F000000LL, (float32x2_t)center).n64_u64[0];
  v18 = mVign->color;
  if (PostEsp_Alpha <= v6)
    v19 = PostEsp_Alpha;
  else
    v19 = v6;
  if (PostEsp_Alpha >= 0.0)
    v15.n64_f32[0] = v19;
  value = (sdfColor_t)vaddq_f32((float32x4_t)v14, vmulq_n_f32(vsubq_f32((float32x4_t)xmmword_3CF8990, (float32x4_t)v14), v15.n64_f32[0]));
  v81 = (sdfVector2_t)vadd_f32((float32x2_t)center, vmul_f32(v16, (float32x2_t)vdupq_lane_s32(v15, 0).n128_u64[0])).n64_u64[0];
  v20 = intensity + (f32)(v15.n64_f32[0] * (f32)(0.7 - intensity));
  v21 = smoothness + (f32)(v15.n64_f32[0] * (f32)(0.3 - smoothness));
  v22 = Allocate(UnityEngine_Rendering_ColorParameter);
  _ctor(v22, value, 1, 0);
  (v18->klass->vtable._8_SetValue.methodPtr)(v18, v22, v18->klass->vtable._8_SetValue.method);
  v23 = mVign->center;
  v24 = Allocate(UnityEngine_Rendering_Vector2Parameter);
  _ctor(v24, v81, 1, 0);
  (v23->klass->vtable._8_SetValue.methodPtr)(v23, v24, v23->klass->vtable._8_SetValue.method);
  v25 = mVign->intensity;
  v26 = Allocate(UnityEngine_Rendering_FloatParameter);
  _ctor(v26, v20, 1, 0);
  (v25->klass->vtable._8_SetValue.methodPtr)(v25, v26, v25->klass->vtable._8_SetValue.method);
  v27 = mVign->smoothness;
  v28 = Allocate(UnityEngine_Rendering_FloatParameter);
  _ctor(v28, v21, 1, 0);
  (v27->klass->vtable._8_SetValue.methodPtr)(v27, v28, v27->klass->vtable._8_SetValue.method);
  mFilmG = Instance->mFilmG;
LABEL_20:
  if (!op_Inequality(mFilmG, 0, 0))
  {
    mChro = Instance->mChro;
    goto LABEL_22;
  }
  if (!mFilmG->active)
    mFilmG->active = 1;
  type = mFilmG->type;
  v30 = Allocate(UnityEngine_Rendering_Universal_FilmGrainLookupParameter);
  _ctor(v30, 9, 1, 0);
  (type->klass->vtable._8_SetValue.methodPtr)(type, v30, type->klass->vtable._8_SetValue.method);
  response = mFilmG->response;
  v32 = Allocate(UnityEngine_Rendering_FloatParameter);
  _ctor(v32, 0.5, 1, 0);
  (response->klass->vtable._8_SetValue.methodPtr)(response, v32, response->klass->vtable._8_SetValue.method);
  v34 = mFilmG->intensity;
  v35 = PostEsp_Alpha;
  v36 = v35 + 0.0;
  if (v35 > v6)
    v36 = v6;
  if (v35 >= 0.0)
    v37 = v36;
  else
    v37 = 0.0;
  v38 = Allocate(UnityEngine_Rendering_FloatParameter);
  _ctor(v38, v37, 1, 0);
  (v34->klass->vtable._8_SetValue.methodPtr)(v34, v38, v34->klass->vtable._8_SetValue.method);
  mChro = Instance->mChro;
LABEL_22:
  if (!op_Inequality(mChro, 0, 0))
  {
    mColorAdjustments = Instance->mColorAdjustments;
    goto LABEL_24;
  }
  if (!mChro->active)
    mChro->active = 1;
  v40 = mChro->intensity;
  v41 = PostEsp_Alpha;
  v42 = v41 + 0.0;
  if (v41 > v6)
    v42 = v6;
  if (v41 >= 0.0)
    v43 = v42;
  else
    v43 = 0.0;
  v44 = Allocate(UnityEngine_Rendering_FloatParameter);
  _ctor(v44, v43, 1, 0);
  (v40->klass->vtable._8_SetValue.methodPtr)(v40, v44, v40->klass->vtable._8_SetValue.method);
  mColorAdjustments = Instance->mColorAdjustments;
LABEL_24:
  if (!op_Inequality(mColorAdjustments, 0, 0))
    goto LABEL_91;
  if ((DrawFlag2 & 1) != 0)
  {
    if (!mColorAdjustments->active)
      mColorAdjustments->active = 1;
    v51 = PostEsp_Alpha;
    v52 = 3.0 - (f32)(v51 * 3.0);
    if (v51 > v6)
      v52 = 0.0;
    if (v51 >= 0.0)
      v50 = v52;
    else
      v50 = 3.0;
    goto LABEL_90;
  }
  if ((DrawFlag2 & 2) != 0)
  {
    if (!mColorAdjustments->active)
      mColorAdjustments->active = 1;
    v48 = PostEsp_Alpha;
    v49 = 3.0;
    if (v48 <= v6)
      v49 = (f32)(v48 * 3.0) + 0.0;
    if (v48 >= 0.0)
      v50 = v49;
    else
      v50 = 0.0;
LABEL_90:
    postExposure = mColorAdjustments->postExposure;
    v54 = Allocate(UnityEngine_Rendering_FloatParameter);
    _ctor(v54, v50, 1, 0);
    (postExposure->klass->vtable._8_SetValue.methodPtr)(postExposure, v54, postExposure->klass->vtable._8_SetValue.method);
  }
LABEL_91:
  mBloom = Instance->mBloom;
  if (!op_Inequality(Instance->mBloom, 0, 0))
    goto LABEL_93;
  goto LABEL_9003;
  if (!op_Inequality(mBloom, 0, 0))
  {
LABEL_93:
    mWhiteBalance = Instance->mWhiteBalance;
    goto LABEL_94;
  }
LABEL_9003:
  GetBloomSetting(Instance, (f32 *)&threshold + 1, &threshold, &scatter, 0);
  v59 = *((f32 *)&threshold + 1);
  m_CachedPtr = mBloom[2].m_CachedPtr;
  v61 = PostEsp_Alpha;
  if (v61 <= v6)
    v62 = PostEsp_Alpha;
  else
    v62 = v6;
  if (v61 >= 0.0)
    v63 = v62;
  else
    v63 = 0.0;
  v64 = v59 + (f32)((f32)(0.0 - v59) * v63);
  v65 = *(f32 *)&threshold + (f32)((f32)(3.0 - *(f32 *)&threshold) * v63);
  v66 = scatter + (f32)((f32)(0.4 - scatter) * v63);
  v67 = Allocate(UnityEngine_Rendering_FloatParameter);
  _ctor(v67, v64, 1, 0);
  (*(*(u64 *)m_CachedPtr + 440))(m_CachedPtr, v67, *(u64 *)(*(u64 *)m_CachedPtr + 448));
  klass = mBloom[3].klass;
  v69 = Allocate(UnityEngine_Rendering_FloatParameter);
  _ctor(v69, v65, 1, 0);
  (*(klass->_1.image + 55))(klass, v69, *((u64 *)klass->_1.image + 56));
  monitor = mBloom[3].monitor;
  v71 = Allocate(UnityEngine_Rendering_FloatParameter);
  _ctor(v71, v66, 1, 0);
  (*(*(u64 *)monitor + 440))(monitor, v71, *(u64 *)(*(u64 *)monitor + 448));
  mWhiteBalance = Instance->mWhiteBalance;
LABEL_94:
  if (!!op_Inequality(mWhiteBalance, 0, 0))
  {
    if (!mWhiteBalance->active)
      mWhiteBalance->active = 1;
    temperature = mWhiteBalance->temperature;
    v74 = PostEsp_Alpha;
    v75 = -80.0;
    if (v74 <= v6)
      v75 = (f32)(v74 * -80.0) + 0.0;
    if (v74 >= 0.0)
      v76 = v75;
    else
      v76 = 0.0;
    v77 = Allocate(UnityEngine_Rendering_FloatParameter);
    _ctor(v77, v76, 1, 0);
    (temperature->klass->vtable._8_SetValue.methodPtr)(temperature, v77, temperature->klass->vtable._8_SetValue.method);
  }
  RestoreLensDistortionSetting(Instance, 0);
  mDof = Instance->mDof;
  if (op_Inequality(mDof, 0, 0))
    RestoreDofSetting(Instance, 0);
  SetForceActiveDofSetting(Instance, 0, 0);
}

// 0x2290960
void dds3PostSlowClear(void) {
  void *Instance;
  void *mDof;

  if ((DrawFlag2 & 4) == 0)
  {
    if (PostSlow_Alpha <= 0.0)
      goto LABEL_14;
  }
  Instance = get_Instance(0);
  if (!op_Inequality(Instance, 0, 0))
    goto LABEL_14;
  RestoreVignetteSetting(Instance, 0);
  RestoreFilmGrainSetting(Instance, 0);
  RestoreChromaticAberrationSetting(Instance, 0);
  RestoreLensDistortionSetting(Instance, 0);
  RestoreColorAdjustmentsSetting(Instance, 0);
  RestoreWhiteBalanceSetting(Instance, 0);
  RestoreBloomSetting(Instance, 0);
  mDof = Instance->mDof;
  if (!op_Inequality(Instance->mDof, 0, 0))
    goto LABEL_22;
  goto LABEL_9000;
  if (!op_Inequality(mDof, 0, 0))
  {
LABEL_22:
    SetForceActiveDofSetting(Instance, 0, 0);
    goto LABEL_16;
  }
LABEL_9000:
  RestoreDofSetting(Instance, 0);
  goto LABEL_22;
LABEL_14:
LABEL_16:
  *(u64 *)&PostSlow_Alpha = 0;
  DrawFlag2 &= ~4u;
}

// 0x2290b90
void dds3PostSlowStart(u32 frame) {
  u16 v2;

  v2 = frame;
  PostSlow_Alpha = 1.0;
  PostSlow_now = v2;
  PostSlow_max = v2;
  DrawFlag2 = DrawFlag2 | 4;
}

// 0x2290c10
void dds3PostSlowStart2(u32 frame_now, u32 frame_max) {
  u16 v3;
  u16 v4;

  v3 = frame_max;
  v4 = frame_now;
  PostSlow_Alpha = 1.0;
  PostSlow_now = v4;
  PostSlow_max = v3;
  DrawFlag2 = DrawFlag2 | 4;
}

// 0x2290ca0
bool dds3PostSlowCheck(void) {
  if ((DrawFlag2 & 4) != 0)
    return 1;
  if (PostSlow_Alpha > 0.0)
    return 1;
  return 0;
}

// 0x2290d60
void dds3PostSlowUpdate(void) {
  u32 v1;
  u32 v4;

  if ((DrawFlag2 & 4) == 0)
    return;
  LOWORD(v1) = PostSlow_max;
  v4 = --PostSlow_now;
  PostSlow_Alpha = (f32)v4 / (f32)v1;
  if (!v4)
  {
    dds3PostSlowClear();
  }
}

// 0x2290e40
void dds3PostSlowDraw(void) {
  u32 v3;
  void *Instance;
  void *mChro;
  f32 v8;
  void *mLensDistortion;
  void *mBloom;
  void *mDof;
  void *v16;
  f32 v18;
  f32 v19;
  void *v20;
  void *v22;
  f32 v23;
  f32 v24;
  f32 v25;
  void *v26;
  f32 v28;
  intptr_t m_CachedPtr;
  f32 v30;
  f32 v31;
  f32 v32;
  f32 v33;
  f32 v34;
  f32 v35;
  void *v36;
  UnityEngine_Object_c *klass;
  void *v38;
  void *monitor;
  void *v40;
  f32 scatter;
  f32 intensity;
  f32 threshold;

  threshold = 0.0;
  intensity = 0.0;
  scatter = 0.0;
  goto LABEL_3;
  if (v3)
  {
LABEL_3:
    if (PostSlow_Alpha <= 0.0)
      return;
    goto LABEL_7;
  }
  if (PostSlow_Alpha <= 0.0)
    return;
LABEL_7:
  Instance = get_Instance(0);
  goto LABEL_9;
LABEL_15:
  RestoreVignetteSetting(Instance, 0);
  RestoreFilmGrainSetting(Instance, 0);
  RestoreColorAdjustmentsSetting(Instance, 0);
  RestoreWhiteBalanceSetting(Instance, 0);
  mChro = Instance->mChro;
  v8 = 1.0;
  if (!op_Inequality(Instance->mChro, 0, 0))
    goto LABEL_17;
  goto LABEL_9001;
  if (!op_Inequality(mChro, 0, 0))
  {
LABEL_17:
    mLensDistortion = Instance->mLensDistortion;
    goto LABEL_18;
  }
LABEL_9001:
  if (!mChro->active)
    mChro->active = 1;
  v16 = mChro->intensity;
  v18 = PostSlow_Alpha + 0.0;
  if (PostSlow_Alpha > v8)
    v18 = v8;
  if (PostSlow_Alpha >= 0.0)
    v19 = v18;
  else
    v19 = 0.0;
  v20 = Allocate(UnityEngine_Rendering_FloatParameter);
  _ctor(v20, v19, 1, 0);
  (v16->klass->vtable._8_SetValue.methodPtr)(v16, v20, v16->klass->vtable._8_SetValue.method);
  mLensDistortion = Instance->mLensDistortion;
LABEL_18:
  if (!op_Inequality(mLensDistortion, 0, 0))
  {
    mBloom = Instance->mBloom;
    goto LABEL_20;
  }
  if (!mLensDistortion->active)
    mLensDistortion->active = 1;
  v22 = mLensDistortion->intensity;
  v23 = PostSlow_Alpha;
  v24 = -0.4;
  if (v23 <= v8)
    v24 = (f32)(v23 * -0.4) + 0.0;
  if (v23 >= 0.0)
    v25 = v24;
  else
    v25 = 0.0;
  v26 = Allocate(UnityEngine_Rendering_FloatParameter);
  _ctor(v26, v25, 1, 0);
  (v22->klass->vtable._8_SetValue.methodPtr)(v22, v26, v22->klass->vtable._8_SetValue.method);
  mBloom = Instance->mBloom;
LABEL_20:
  if (!op_Inequality(mBloom, 0, 0))
  {
    mDof = Instance->mDof;
    goto LABEL_22;
  }
  GetBloomSetting(Instance, &threshold, &intensity, &scatter, 0);
  v28 = threshold;
  m_CachedPtr = mBloom[2].m_CachedPtr;
  v30 = PostSlow_Alpha;
  if (v30 <= v8)
    v31 = PostSlow_Alpha;
  else
    v31 = v8;
  if (v30 >= 0.0)
    v32 = v31;
  else
    v32 = 0.0;
  v33 = v28 + (f32)((f32)(0.0 - v28) * v32);
  v34 = intensity + (f32)((f32)(2.0 - intensity) * v32);
  v35 = scatter + (f32)((f32)(0.4 - scatter) * v32);
  v36 = Allocate(UnityEngine_Rendering_FloatParameter);
  _ctor(v36, v33, 1, 0);
  (*(*(u64 *)m_CachedPtr + 440))(m_CachedPtr, v36, *(u64 *)(*(u64 *)m_CachedPtr + 448));
  klass = mBloom[3].klass;
  v38 = Allocate(UnityEngine_Rendering_FloatParameter);
  _ctor(v38, v34, 1, 0);
  (*(klass->_1.image + 55))(klass, v38, *((u64 *)klass->_1.image + 56));
  monitor = mBloom[3].monitor;
  v40 = Allocate(UnityEngine_Rendering_FloatParameter);
  _ctor(v40, v35, 1, 0);
  (*(*(u64 *)monitor + 440))(monitor, v40, *(u64 *)(*(u64 *)monitor + 448));
  mDof = Instance->mDof;
LABEL_22:
  if (!op_Inequality(mDof, 0, 0))
  {
LABEL_24:
    SetForceActiveDofSetting(Instance, 0, 0);
    return;
  }
  RestoreDofSetting(Instance, 0);
  goto LABEL_24;
LABEL_9:
  if (!op_Equality(Instance, 0, 0))
    goto LABEL_15;
  dds3PostSlowClear();
}

// 0x2291390
void dds3PostHitFlashClear(void) {
  void *Instance;
  void *mDof;

  if ((DrawFlag2 & 8) == 0)
  {
    if (PostHitFlash_Alpha <= 0.0)
      goto LABEL_14;
  }
  Instance = get_Instance(0);
  if (!op_Inequality(Instance, 0, 0))
    goto LABEL_14;
  RestoreVignetteSetting(Instance, 0);
  RestoreFilmGrainSetting(Instance, 0);
  RestoreChromaticAberrationSetting(Instance, 0);
  RestoreLensDistortionSetting(Instance, 0);
  RestoreColorAdjustmentsSetting(Instance, 0);
  RestoreWhiteBalanceSetting(Instance, 0);
  RestoreBloomSetting(Instance, 0);
  mDof = Instance->mDof;
  if (!op_Inequality(Instance->mDof, 0, 0))
    goto LABEL_22;
  goto LABEL_9000;
  if (!op_Inequality(mDof, 0, 0))
  {
LABEL_22:
    SetForceActiveDofSetting(Instance, 0, 0);
    goto LABEL_16;
  }
LABEL_9000:
  RestoreDofSetting(Instance, 0);
  goto LABEL_22;
LABEL_14:
LABEL_16:
  *(u64 *)&PostHitFlash_Alpha = 0;
  DrawFlag2 &= ~8u;
}

// 0x22915c0
void dds3PostHitFlashStart(u32 frame) {
  u16 v2;

  v2 = frame;
  if ((DrawFlag2 & 3) != 0)
    return;
  if (PostEsp_Alpha > 0.0)
    return;
  if ((DrawFlag2 & 4) != 0)
    return;
  if (PostSlow_Alpha <= 0.0)
  {
    if ((DrawFlag2 & 8) != 0)
      return;
    if (PostHitFlash_Alpha <= 0.0)
    {
      PostHitFlash_Alpha = 1.0;
      PostHitFlash_now = v2;
      PostHitFlash_max = v2;
      DrawFlag2 = DrawFlag2 | 8;
    }
    return;
  }
}

// 0x2291830
bool dds3PostHitFlashCheck(void) {
  if ((DrawFlag2 & 8) != 0)
    return 1;
  if (PostHitFlash_Alpha > 0.0)
    return 1;
  return 0;
}

// 0x22918f0
void dds3PostHitFlashUpdate(void) {
  u32 v1;
  u32 v4;

  if ((DrawFlag2 & 8) == 0)
    return;
  LOWORD(v1) = PostHitFlash_max;
  v4 = --PostHitFlash_now;
  PostHitFlash_Alpha = (f32)v4 / (f32)v1;
  if (!v4)
  {
    dds3PostHitFlashClear();
  }
}

// 0x22919d0
void dds3PostHitFlashDraw(void) {
  u32 v3;
  void *Instance;
  void *mBloom;
  void *mDof;
  f32 v11;
  f32 v12;
  intptr_t m_CachedPtr;
  f32 v15;
  f32 v16;
  f32 v17;
  f32 v18;
  void *v19;
  UnityEngine_Object_c *klass;
  void *v21;
  void *monitor;
  void *v23;
  f32 scatter;
  f32 intensity;
  f32 threshold;

  threshold = 0.0;
  intensity = 0.0;
  scatter = 0.0;
  goto LABEL_3;
  if (v3)
  {
LABEL_3:
    if (PostHitFlash_Alpha <= 0.0)
      return;
    goto LABEL_7;
  }
  if (PostHitFlash_Alpha <= 0.0)
    return;
LABEL_7:
  Instance = get_Instance(0);
  goto LABEL_9;
LABEL_15:
  RestoreVignetteSetting(Instance, 0);
  RestoreFilmGrainSetting(Instance, 0);
  RestoreChromaticAberrationSetting(Instance, 0);
  RestoreLensDistortionSetting(Instance, 0);
  RestoreColorAdjustmentsSetting(Instance, 0);
  RestoreWhiteBalanceSetting(Instance, 0);
  mBloom = Instance->mBloom;
  if (!op_Inequality(Instance->mBloom, 0, 0))
    goto LABEL_17;
  goto LABEL_9001;
  if (!op_Inequality(mBloom, 0, 0))
  {
LABEL_17:
    mDof = Instance->mDof;
    goto LABEL_18;
  }
LABEL_9001:
  GetBloomSetting(Instance, &threshold, &intensity, &scatter, 0);
  v11 = threshold;
  v12 = 1.0;
  m_CachedPtr = mBloom[2].m_CachedPtr;
  if (PostHitFlash_Alpha <= 1.0)
    v12 = PostHitFlash_Alpha;
  if (PostHitFlash_Alpha >= 0.0)
    v15 = v12;
  else
    v15 = 0.0;
  v16 = v11 + (f32)((f32)(0.0 - v11) * v15);
  v17 = intensity + (f32)((f32)(3.0 - intensity) * v15);
  v18 = scatter + (f32)((f32)(0.4 - scatter) * v15);
  v19 = Allocate(UnityEngine_Rendering_FloatParameter);
  _ctor(v19, v16, 1, 0);
  (*(*(u64 *)m_CachedPtr + 440))(m_CachedPtr, v19, *(u64 *)(*(u64 *)m_CachedPtr + 448));
  klass = mBloom[3].klass;
  v21 = Allocate(UnityEngine_Rendering_FloatParameter);
  _ctor(v21, v17, 1, 0);
  (*(klass->_1.image + 55))(klass, v21, *((u64 *)klass->_1.image + 56));
  monitor = mBloom[3].monitor;
  v23 = Allocate(UnityEngine_Rendering_FloatParameter);
  _ctor(v23, v18, 1, 0);
  (*(*(u64 *)monitor + 440))(monitor, v23, *(u64 *)(*(u64 *)monitor + 448));
  mDof = Instance->mDof;
LABEL_18:
  if (!op_Inequality(mDof, 0, 0))
  {
LABEL_20:
    SetForceActiveDofSetting(Instance, 0, 0);
    return;
  }
  RestoreDofSetting(Instance, 0);
  goto LABEL_20;
LABEL_9:
  if (!op_Equality(Instance, 0, 0))
    goto LABEL_15;
  dds3PostHitFlashClear();
}

// 0x2291d90
void dds3FinishInit(void *objList) {
  Il2CppObject *Asset_object;
  void *v4;

  Asset_object = GetAsset_object_(objList, "colorctrl");
  v4 = Instantiate_61006432(Asset_object, 0);
  if (!v4)
  {
    finishMat = 0;
    return;
  }
}

// 0x2291f30
void dds3FinishBrightness(f32 lv) {
  if (finishBrightness == lv)
    return;
  finishBrightness = lv;
  SetFinish();
}

// 0x2292000
void dds3FinishContrast(f32 lv) {
  if (finishContrast == lv)
    return;
  finishContrast = lv;
  SetFinish();
}

// 0x2288660
static void SetFinish(void) {
  f32 v5;
  f32 v6;
  f32 v7;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  f32 v13;
  f32 v14;
  f32 v15;
  f32 v16;
  f32 v17;
  f32 v18;
  f32 v19;
  f32 v20;
  f32 v21;
  f32 v28;
  f32 v29;
  sdfVector4_t v30;
  sdfVector4_t v31;
  sdfVector4_t v32;

  v5 = finishContrast * finishBrightness;
  v6 = finishBrightness - (f32)(finishContrast * finishBrightness);
  v7 = v6 * 0.5;
  x = oneVector.x;
  y = oneVector.y;
  z = oneVector.z;
  w = oneVector.w;
  v13 = v7 * x;
  v14 = v7 * y;
  v15 = v7 * z;
  v16 = v7 * w;
  v18 = zeroVector.x;
  v17 = zeroVector.y;
  v20 = zeroVector.z;
  v19 = zeroVector.w;
  if (v7 >= 0.0)
  {
    v28 = v15;
    v29 = v16;
LABEL_23:
    goto LABEL_24;
  }
  if (v13 <= v18)
    v13 = zeroVector.x;
  if (v14 <= v17)
    v14 = zeroVector.y;
  if (v15 <= v20)
    v15 = zeroVector.z;
  if (v16 <= v19)
    v16 = zeroVector.w;
  v28 = v15;
  v29 = v16;
  v21 = (f32)-v7 / v5;
  v5 = v5 + v7;
  v18 = v21 * oneVector.x;
  v17 = v21 * oneVector.y;
  v20 = v21 * oneVector.z;
  v19 = v21 * oneVector.w;
  goto LABEL_23;
LABEL_24:
  v30.y = (f32)(v5 * 0.5) * oneVector.y;
  v30.x = (f32)(v5 * 0.5) * oneVector.x;
  v30.z = (f32)(v5 * 0.5) * oneVector.z;
  v30.w = (f32)(v5 * 0.5) * oneVector.w;
  SetVector_60817376(finishMat, ID_Mul, v30, 0);
  v31.x = v13;
  v31.y = v14;
  v31.z = v28;
  v31.w = v29;
  SetVector_60817376(finishMat, ID_Add, v31, 0);
  v32.x = v18;
  v32.y = v17;
  v32.z = v20;
  v32.w = v19;
  SetVector_60817376(finishMat, ID_Sub, v32, 0);
}

// 0x22921e0
void dds3UpdateRenderingResolution(void) {
  void *currentRenderPipeline;

  if (old_rendering_Resolution == rendering_Resolution)
    return;
  currentRenderPipeline = get_currentRenderPipeline(0);
  if (!currentRenderPipeline)
    goto LABEL_13;
  goto LABEL_9000;
  if (!currentRenderPipeline)
  {
LABEL_13:
    set_renderScale(currentRenderPipeline, rendering_Resolution, 0);
    old_rendering_Resolution = rendering_Resolution;
    return;
  }
LABEL_9000:
  goto LABEL_13;
}

// 0x2292430
void dds3UpdateRenderFrameInterval(void) {
  if (old_renderFrameInterval == renderFrameInterval)
    return;
  set_renderFrameInterval(renderFrameInterval, 0);
  old_renderFrameInterval = renderFrameInterval;
  return;
}

// 0x2292540
void dds3SetOverwrite_ScreenParam_sensorSize(bool _OnOff, f32 _X, f32 _Y) {
  gOverwrite_ScreenParam_sensorSize = OnOff;
  gOverwrite_ScreenParam_sensorSize_XY.x = X;
  gOverwrite_ScreenParam_sensorSize_XY.y = Y;
}

// 0x22925d0
bool dds3ChkOverwrite_ScreenParam_sensorSize(f32 *_X, f32 *_Y) {
  bool result;

  result = gOverwrite_ScreenParam_sensorSize;
  *X = gOverwrite_ScreenParam_sensorSize_XY.x;
  *Y = gOverwrite_ScreenParam_sensorSize_XY.y;
  return result;
}

// 0x2292650
void dds3UpdateShaderUVScroll(void) {
  f32 time;
  f32 gShaderUV_Time_Time_local;

  if (gShaderUVScroll)
  {
    time = get_time(0);
    gShaderUV_Time_Time_local = time;
    gShaderUV_Time_Time = gShaderUV_Time_Time_local;
    goto LABEL_12;
  }
  gShaderUV_Time_Time_local = gShaderUV_Time_Time;
LABEL_12:
  SetGlobalFloat("_GlobalTime", gShaderUV_Time_Time_local, 0);
}

// 0x2292740
void dds3SetShaderUVScroll(bool _OnOff) {
  gShaderUVScroll = OnOff;
}

// 0x22927b0
bool dds3GetShaderUVScroll(void) {
  return gShaderUVScroll;
}
