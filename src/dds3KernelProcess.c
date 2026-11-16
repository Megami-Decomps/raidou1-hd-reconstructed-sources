#include "types.h"
#include "__newdds3.h"
#include "dds3basic.h"
#include "dds3kerneldraw.h"
#include "dds3kernelmain.h"
#include "dds3kernelprocess.h"
#include "dds3worldbasic.h"
#include "egl.h"
#include "kernel.h"
#include "sdf3d.h"
#include "sdf_vu0.h"
#include "sdfdraw.h"
#include "sdfgr.h"
#include "sdfmodel.h"
#include "sdfvsync.h"

typedef struct dds3ProcessID_t dds3ProcessID_t;

void __BtlCAM_QuakeProc(void);
void __BtlCAM_QuakeExit(void);

// 0x22a1b40
dds3ProcessFunc_t dds3FirstProcess(dds3ProcessID_t *id) {
  sdfModelDrawEnv_t *ModelDrawEnv;
  s64 v8;

  sdfGrOtInit(Ot, 119);
  dds3InitDrawEnvSub(FrameID);
  ModelDrawEnv = DrawEnv[FrameID]->ModelDrawEnv;
  if (SLODWORD(ModelDrawEnv->max_length) >= 1)
  {
    v8 = 0;
    do
      sdfModelSetDrawEnv(ModelDrawEnv[v8++]);
    while (v8 < SLODWORD(ModelDrawEnv->max_length));
  }
  return 0;
}

// 0x22a1cb0
dds3ProcessFunc_t dds3DrawFirstProcess(dds3ProcessID_t *id) {
  s32 frame_rate;
  f32 x;
  f32 v13;
  f32 z;
  f32 w;
  sdf3DLightParallelPacket_t *DirLightPacket;
  bool v18;
  struct sdfVector4_t CameraEyePos_local;
  struct sdfVector4_t CameraOffset_local;
  f32 *p_x;
  struct sdfVector4_t v27;
  f32 *v28;
  f32 v29;
  f32 v30;
  f32 v31;
  f32 v32;
  f32 v34;
  f32 v35;
  f32 v36;
  f32 v37;
  _OWORD *p_m00;
  _OWORD *v41;
  __int128 v43;
  __int128 v44;
  __int128 v45;
  sdf3DScreenParam_t *v48;
  sdf3DViewportPacket_t *ViewportPacket;
  s64 v51;
  dds3DrawEnv_t *v54;
  sdf3DLightParallelPacket_t *HighDirLightPacket;
  sdf3DLightParallelPacket_t *v56;
  dds3DrawEnv_t *v57;
  sdf3DViewportPacket_t *HighViewportPacket;
  sdf3DViewportPacket_t *v59;
  sdf3DLightParallelPacket_t *v61;
  f32 v65;
  f32 v67;
  f32 v68;
  f32 v69;
  f32 v70;
  sdf3DLightParallelPacket_t *v72;
  f32 v77;
  f32 v78;
  f32 v79;
  f32 v80;
  f32 v81;
  f32 v82;
  f32 v83;
  f32 v84;
  f32 v85;
  f32 v86;
  f32 v87;
  f32 v88;
  _OWORD *v91;
  _OWORD *v92;
  __int128 v93;
  __int128 v94;
  __int128 v95;
  f32 v99;
  f32 v100;
  f32 v101;
  f32 v102;
  f32 v103;
  f32 v104;
  f32 v106;
  f32 v111;
  s64 Y;
  sdfVector4_t v113;
  sdfVector4_t v114;

  Y = 0;
  dds3RunQuake();
  if (Newdds3_QuakeID)
  {
    frame_rate = btlqwk->frame_rate;
    if (frame_rate == -1 || frame_rate > btlqwk->frame_cnt)
      __BtlCAM_QuakeProc();
    else
      __BtlCAM_QuakeExit();
  }
  dds3SceneLightUpdateFirst();
  x = Ambient.x;
  v13 = Ambient.y;
  z = Ambient.z;
  w = Ambient.w;
  DirLightPacket = DrawEnv[FrameID]->DirLightPacket;
  v113.x = x;
  v113.y = v13;
  v113.z = z;
  v113.w = w;
  sdf3MakeLightParallelPacket(DirLightPacket, DirLights, v113, 1);
  set_backgroundColor(cameraObject->_camera, (sdfColor_t)BackColor, 0);
  sdf3MakeScreenParam(ScreenParam);
  v18 = dds3ChkOverwrite_ScreenParam_sensorSize((f32 *)&Y + 1, &Y);
  if (v18)
  {
    v65 = *(f32 *)&Y;
    ScreenParam->sensorSize.x = *((f32 *)&Y + 1);
    ScreenParam->sensorSize.y = v65;
LABEL_23:
    goto LABEL_24;
  }
  {
    goto LABEL_23;
  }
LABEL_24:
  vct_A = CameraTargetPos;
  CameraEyePos_local = CameraEyePos;
  vct_B = CameraEyePos_local;
  vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  sub_1949110(0);
  vct_A = (struct sdfVector4_t)vmulq_f32((float32x4_t)vct_A, vdupq_n_s32(0x44160000u));
  vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  CameraOffset_local = CameraOffset;
  vct_B = CameraOffset_local;
  vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  p_x = &vf00.x;
  v103 = p_x[5];
  v106 = p_x[4];
  v99 = p_x[7];
  v101 = p_x[6];
  v27 = CameraEyePos;
  vct_A = v27;
  vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  v28 = &vf00.x;
  v29 = v28[4];
  v30 = v28[5];
  v31 = v28[6];
  v32 = v28[7];
  v34 = CameraUpVector.x;
  v35 = CameraUpVector.y;
  v36 = CameraUpVector.z;
  v37 = CameraUpVector.w;
  sub_1B33630(0, v106, v103, v101, v99, v29, v30, v31, v32, COERCE_DOUBLE(__PAIR64__(LODWORD(v35), LODWORD(v34))), COERCE_DOUBLE(__PAIR64__(LODWORD(v37), LODWORD(v36))));
  p_m00 = &CameraTM.m00;
  v41 = &vf00.x;
  v43 = v41[5];
  v44 = v41[6];
  v45 = v41[7];
  *p_m00 = v41[4];
  p_m00[1] = v43;
  p_m00[2] = v44;
  p_m00[3] = v45;
  v48 = ScreenParam;
  ViewportPacket = DrawEnv[FrameID]->ViewportPacket;
  sdf3MakeViewportPacket(ViewportPacket, v48, &CameraTM, cameraObject);
  sdf3SetCamera(ScreenParam, &CameraTM, cameraObject);
  sdfDrawTagLinkOt(Ot[7], DrawEnv[FrameID]->DrawTag);
  v51 = FrameID;
  if (HDrawSync)
  {
    v54 = DrawEnv[v51];
    HighDirLightPacket = v54->HighDirLightPacket;
    v56 = v54->DirLightPacket;
    HighDirLightPacket->traceSrc = v56;
    v57 = DrawEnv[v51];
    HighViewportPacket = v57->HighViewportPacket;
    v59 = v57->ViewportPacket;
    HighViewportPacket->traceSrc = v59;
    goto LABEL_65;
  }
  v67 = HAmbient.x;
  v68 = HAmbient.y;
  v69 = HAmbient.z;
  v70 = HAmbient.w;
  v72 = DrawEnv[FrameID]->HighDirLightPacket;
  v114.x = v67;
  v114.y = v68;
  v114.z = v69;
  v114.w = v70;
  sdf3MakeLightParallelPacket(v72, HDirLights, v114, 1);
  GlobalParamFlag = 0;
  sdf3MakeScreenParam(HScreenParam);
  v77 = HCameraTargetPos.x;
  v78 = HCameraTargetPos.y;
  v79 = HCameraTargetPos.z;
  v80 = HCameraTargetPos.w;
  v81 = HCameraEyePos.x;
  v82 = HCameraEyePos.y;
  v83 = HCameraEyePos.z;
  v84 = HCameraEyePos.w;
  v85 = HCameraUpVector.x;
  v86 = HCameraUpVector.y;
  v87 = HCameraUpVector.z;
  v88 = HCameraUpVector.w;
  v104 = HCameraTargetPos.y;
  v111 = HCameraTargetPos.x;
  v100 = HCameraTargetPos.w;
  v102 = HCameraTargetPos.z;
  v80 = v100;
  v79 = v102;
  v78 = v104;
  v77 = v111;
  sub_1B33630(0, v77, v78, v79, v80, v81, v82, v83, v84, COERCE_DOUBLE(__PAIR64__(LODWORD(v86), LODWORD(v85))), COERCE_DOUBLE(__PAIR64__(LODWORD(v88), LODWORD(v87))));
  v91 = &HCameraTM.m00;
  v92 = &vf00.x;
  v93 = v92[5];
  v94 = v92[6];
  v95 = v92[7];
  *v91 = v92[4];
  v91[1] = v93;
  v91[2] = v94;
  v91[3] = v95;
  sdf3MakeViewportPacket(DrawEnv[FrameID]->HighViewportPacket, HScreenParam, &HCameraTM, HcameraObject);
LABEL_65:
  sdfDrawTagLinkOt(Ot[90], DrawEnv[v51]->HighDrawTag);
  v61 = DrawEnv[v51]->DirLightPacket;
  LightDefault = v61;
  return 0;
}

// 0x22a27d0
dds3ProcessFunc_t dds3DrawProcess(dds3ProcessID_t *id) {
  s64 i;

  dds3UpdateRenderingResolution();
  dds3BistaUpdate();
  dds3DrawBista();
  dds3FadeUpdate();
  dds3DrawFade();
  dds3FilterCalc();
  dds3FilterDraw();
  dds3BlurUpdate();
  dds3PostEspUpdate();
  dds3PostEspDraw();
  dds3PostSlowUpdate();
  dds3PostSlowDraw();
  dds3PostHitFlashUpdate();
  dds3PostHitFlashDraw();
  for (i = 32; i != 152; i += 8)
  {
    sdfModelDrawEnvLinkOt(*(sdfModelOt_t *)((char *)&ModelOt->obj.klass + i), *(sdfModelDrawEnv_t *)((char *)&DrawEnv[FrameID]->ModelDrawEnv->obj.klass + i));
  }
  eglCloseMesh();
  if (!drawSkip)
  {
    sdfGrOtClose(Ot);
    if ((DrawFlag & 0x2000000) != 0)
    {
      DrawFlag = DrawFlag & 0xFDFFFFFF;
      goto LABEL_18;
    }
    _Redraw_k__BackingField = 0;
  }
LABEL_18:
  dds3UpdateShaderUVScroll();
  return 0;
}

// 0x22a2dc0
dds3ProcessFunc_t dds3BasicMainProcess(dds3ProcessID_t *id) {
  dds3CallMainProcuder(dds3TheWorld);
  return 0;
}

// 0x22a2e80
dds3ProcessFunc_t dds3BasicDrawProcess(dds3ProcessID_t *id) {
  dds3CallDrawProcuder(dds3TheWorld);
  return 0;
}
