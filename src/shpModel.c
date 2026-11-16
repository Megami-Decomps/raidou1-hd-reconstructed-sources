#include "types.h"
#include "MODELTYPE.h"
#include "dds3areabasic.h"
#include "dds3basic.h"
#include "dds3cameraobjectbasic.h"
#include "dds3kerneldraw.h"
#include "dds3objectbase.h"
#include "dds3scenebasic.h"
#include "dds3unitobjectbasic.h"
#include "dds3worldbasic.h"
#include "mdl.h"
#include "sdf3d.h"
#include "sdf_vu0.h"
#include "sdfquat.h"
#include "shpmain.h"
#include "shpmisc.h"
#include "shpmodel.h"

typedef struct dds3Basic_t dds3Basic_t;
typedef struct sdf3DLightParallelPacket_t sdf3DLightParallelPacket_t;
typedef struct tagSHP_CAMERA_WK tagSHP_CAMERA_WK;
typedef struct tagSHP_MODEL_CB tagSHP_MODEL_CB;
typedef struct tagSHP_MODEL_WK tagSHP_MODEL_WK;

struct tagSHP_CAMERA_WK {
    dds3Basic_t *camera;
    f32 transX;
    f32 transY;
    f32 ratio;
    s32 count;
    s32 frame;
    s32 updateType;
};

struct tagSHP_MODEL_WK {
    tagSHP_MODEL_CB *cb[16];
    tagSHP_CAMERA_WK *cam;
    s32 stat;
    s16 shoptype;
};

static tagSHP_MODEL_WK *s_wk;
static sdfVector4_t g_vertical;
static sdfVector4_t g_cameraPos;
static sdfVector4_t g_targetPos;
static f32 g_fov;
static sdf3DLightParallelPacket_t *g_pLightPacket;
static sdf3DLightParallelPacket_t *g_pLightPacket_new;
static void *ShpLightPacketPar;
static sdfVector4_t shpModelGetCameraPos_targetPos;
static sdfVector4_t shpModelGetCameraPos_cameraPos;

static void SetLight(s32 a_shoptype);
static void Reset3DGlobal(void);
static void ResetGlobal(void);
static bool ChkMotionEnd(s32 a_no);
static void CreateModel(tagSHP_MODEL_CB *cb);

// 0x21a9700
void shpCreateScene(void) {
  u32 v1;
  dds3Basic_t *scene;

  scene = dds3AddScene();
  dds3SetControlScene(scene);
  dds3SetActiveScene(scene);
  v1 = dds3SerializeID();
  dds3AreaBasicAdd(v1, "shop_area");
}

// 0x21a9800
void shpDeleteScene(void) {
  dds3Basic_t *scene;

  scene = dds3GetControlScene();
  if (!scene)
    return;
  dds3DeleteScene(scene);
}

// 0x21a98b0
void shpMakeLightPacket(void) {
  sdfVector4_t *v1;
  _OWORD *v2;
  sdfVector4_t *v3;
  _OWORD *v4;
  sdf3DLight_t *v5;
  sdf3DLight_t *v6;
  sdf3DLight_t *v7;
  sdf3DLight_t *v8;
  sdf3DLight_t *m_Items;
  sdf3DLight_t *v10;
  sdf3DLight_t *v11;
  sdf3DLight_t *v13;
  sdfVector4_t *p_color;
  s32 v15;
  struct sdfVector4_t v16;
  sdf3DLight_t *v17;
  sdfVector4_t *p_v;
  sdf3DLight_t *v20;
  sdfVector4_t *v21;
  s32 v22;
  struct sdfVector4_t v23;
  sdf3DLight_t *v24;
  sdfVector4_t *v25;
  sdf3DLight_t *v27;
  sdfVector4_t *v28;
  s32 v29;
  struct sdfVector4_t v30;
  sdf3DLight_t *v31;
  sdfVector4_t *v32;
  s64 v37;
  sdfVector4_t *Col;
  sdfVector4_t *Dir;
  LightPacketClass *Tbl;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  sdf3DLight_t *v45;
  sdf3DLight_t *v46;
  sdf3DLight_t *v47;
  sdfVector4_t *v49;
  struct sdfVector4_t v50;
  sdfVector4_t *v51;
  sdfVector4_t *v53;
  struct sdfVector4_t v54;
  sdfVector4_t *v55;
  sdfVector4_t *v57;
  struct sdfVector4_t v58;
  sdf3DLight_t *v59;
  sdf3DLightParallelPacket_t *v62;
  struct sdfVector4_t v64;
  struct sdfVector4_t v65;
  struct sdfVector4_t v66;
  struct sdfVector4_t v73;
  struct sdfVector4_t v74;
  struct sdfVector4_t v75;
  sdf3DLight_t *v76;
  struct sdfVector4_t v77;
  struct sdfVector4_t v78;
  struct sdfVector4_t v79;
  struct sdfVector4_t v80;
  struct sdfVector4_t v81;
  struct sdfVector4_t v82;
  sdfVector4_t v83;
  sdfVector4_t v84;

  v1 = NewSpecific(sdfVector4_t, 3u);
  *(u64 *)&v1[2].y = 0;
  v2 = v1;
  *(u64 *)&v1[1].w = 0;
  *(u32 *)&v1[2].w = 0;
  *(_OWORD *)&v1[0] = xmmword_3D01E40;
  *(u32 *)&v1[1].z = 1065353216;
  *(u64 *)&v1[1] = 0x3F8CCCCD3F99999ALL;
  v3 = NewSpecific(sdfVector4_t, 3u);
  *(u64 *)&v3[2].y = 0;
  *(u64 *)&v3[1].w = 0;
  *(u32 *)&v3[2].w = 0;
  v4 = v3;
  *(_OWORD *)&v3[0] = xmmword_3D06C00;
  *(u32 *)&v3[1].z = -1089344635;
  *(u64 *)&v3[1] = 0x3F4CCCCD3E4CCCCDLL;
  v5 = Allocate(sdf3DLight_t);
  _ctor(v5, 0);
  v6 = Allocate(sdf3DLight_t);
  _ctor(v6, 0);
  v7 = Allocate(sdf3DLight_t);
  _ctor(v7, 0);
  v8 = NewSpecific(sdf3DLight_t, 3u);
  v8[2] = v7;
  v11 = &v8[2];
  if (!g_pLightPacket)
    return;
  v73 = (struct sdfVector4_t)v2[2];
  vct_A = v73;
  v13 = m_Items;
  p_color = &v13->color;
  v15 = (u8)byte_5755EF5;
  *p_color = vct_A;
  v16 = (struct sdfVector4_t)v4[2];
  if (v15)
  {
    goto LABEL_20;
  }
  else
  {
    v77 = (struct sdfVector4_t)v4[2];
    v16 = v77;
LABEL_20:
    vct_A = v16;
    v17 = m_Items;
    goto LABEL_21;
  }
  v78 = v16;
  vct_A = v78;
  v17 = m_Items;
LABEL_21:
  p_v = &v17->v;
  *p_v = vct_A;
  v74 = (struct sdfVector4_t)v2[3];
  vct_A = v74;
  v20 = v10;
  v21 = &v20->color;
  v22 = (u8)byte_5755EF5;
  *v21 = vct_A;
  v23 = (struct sdfVector4_t)v4[3];
  if (v22)
  {
    goto LABEL_29;
  }
  else
  {
    v79 = (struct sdfVector4_t)v4[3];
    v23 = v79;
LABEL_29:
    vct_A = v23;
    v24 = v10;
    goto LABEL_30;
  }
  v80 = v23;
  vct_A = v80;
  v24 = v10;
LABEL_30:
  v25 = &v24->v;
  *v25 = vct_A;
  v75 = (struct sdfVector4_t)v2[4];
  vct_A = v75;
  v27 = v11;
  v28 = &v27->color;
  v29 = (u8)byte_5755EF5;
  *v28 = vct_A;
  v30 = (struct sdfVector4_t)v4[4];
  if (v29)
  {
    goto LABEL_38;
  }
  else
  {
    v81 = (struct sdfVector4_t)v4[4];
    v30 = v81;
LABEL_38:
    vct_A = v30;
    v31 = v11;
    goto LABEL_39;
  }
  v82 = v30;
  vct_A = v82;
  v31 = v11;
LABEL_39:
  v32 = &v31->v;
  *v32 = vct_A;
  v83.y = 0.2;
  v83.x = 0.3;
  v83.w = 0.1;
  v83.z = 0.2;
  sdf3MakeLightParallelPacket(g_pLightPacket, v8, v83, 1);
  v37 = 5;
  v76 = v8;
  while (1)
  {
    Col = GetTbl(ShpLightPacketPar, (s32)v37 - 5, 0)->Col;
    Dir = GetTbl(ShpLightPacketPar, (s32)v37 - 5, 0)->Dir;
    Tbl = GetTbl(ShpLightPacketPar, (s32)v37 - 5, 0);
    x = Tbl->Ambient.x;
    y = Tbl->Ambient.y;
    z = Tbl->Ambient.z;
    w = Tbl->Ambient.w;
    v45 = Allocate(sdf3DLight_t);
    _ctor(v45, 0);
    v46 = Allocate(sdf3DLight_t);
    _ctor(v46, 0);
    v47 = Allocate(sdf3DLight_t);
    _ctor(v47, 0);
    m_Items = v45;
    v10 = v46;
    v11 = v47;
    if (*((u64 *)&g_pLightPacket_new->obj.klass + v37))
      break;
LABEL_45:
    if (++v37 == 17)
      return;
  }
  v64 = Col[0];
  vct_A = v64;
  v49 = m_Items;
  v49[1] = vct_A;
  v50 = Dir[0];
  vct_A = v50;
  v51 = m_Items;
  v51[2] = vct_A;
  v65 = Col[1];
  vct_A = v65;
  v53 = v10;
  v53[1] = vct_A;
  v54 = Dir[1];
  vct_A = v54;
  v55 = v10;
  v55[2] = vct_A;
  v66 = Col[2];
  vct_A = v66;
  v57 = v11;
  v57[1] = vct_A;
  v58 = Dir[2];
  vct_A = v58;
  v59 = v11;
  v59->v = vct_A;
  v62 = *((sdf3DLightParallelPacket_t *)&g_pLightPacket_new->obj.klass + v37);
  v84.x = x;
  v84.y = y;
  v84.z = z;
  v84.w = w;
  sdf3MakeLightParallelPacket(v62, v76, v84, 1);
  goto LABEL_45;
}

// 0x21aa710
static void SetLight(s32 a_shoptype) {
  sdfVector4_t *v3;
  f32 *v4;
  sdfVector4_t *v5;
  sdfVector4_t *v6;
  sdfVector4_t *v7;
  f32 *v8;
  sdfVector4_t *v9;
  sdfVector4_t *v10;
  f32 v12;
  f32 v13;
  f32 v14;
  f32 v15;
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
  f32 v27;
  f32 v28;
  f32 v29;
  f32 v30;
  f32 v31;
  f32 v32;
  f32 v33;
  f32 v34;
  f32 v35;
  f32 v36;
  f32 v37;
  f32 v38;
  f32 v39;
  f32 v40;
  sdfVector4_t v41;
  sdfVector4_t v42;
  sdfVector4_t v43;
  sdfVector4_t v44;
  sdfVector4_t v45;
  sdfVector4_t v46;
  sdfVector4_t v47;

  v3 = NewSpecific(sdfVector4_t, 3u);
  *(u32 *)&v3[1].z = 1045220557;
  *(u64 *)&v3[2].y = 0;
  *(u64 *)&v3[1].w = 0;
  v4 = v3;
  *(u32 *)&v3[2].w = 0;
  *(_OWORD *)&v3[0] = xmmword_3CF8980;
  *(u64 *)&v3[1] = 0x3E8000003E99999ALL;
  v5 = NewSpecific(sdfVector4_t, 3u);
  *(u64 *)&v5[2].y = 0;
  v6 = v5;
  *(u64 *)&v5[1].w = 0;
  *(u32 *)&v5[2].w = 0;
  *(_OWORD *)&v5[0] = xmmword_3D00740;
  *(u32 *)&v5[1].z = -1138501878;
  *(u64 *)&v5[1] = 0xBE428F5C3F7AE148LL;
  v7 = NewSpecific(sdfVector4_t, 3u);
  *(u32 *)&v7[1].z = 1045220557;
  v8 = v7;
  *(u64 *)&v7[2].y = 0;
  *(u64 *)&v7[1].w = 0;
  *(u32 *)&v7[2].w = 0;
  *(_OWORD *)&v7[0] = xmmword_3D01E40;
  *(int32x2_t *)&v7[1] = vdup_n_s32(0x3E4CCCCDu);
  v9 = NewSpecific(sdfVector4_t, 3u);
  *(u64 *)&v9[2] = 0;
  *(u64 *)&v9[2].z = 0;
  v10 = v9;
  *(u64 *)&v9[1].z = 0;
  *(_OWORD *)&v9[0] = xmmword_3CFE8E0;
  *(u64 *)&v9[1] = 0x3F000000BF4CCCCDLL;
  if (a_shoptype)
  {
    v12 = v8[8];
    v13 = v8[9];
    v14 = v8[10];
    v15 = v8[11];
    v41.x = v12;
    v41.y = v13;
    v41.z = v14;
    v41.w = v15;
    dds3SetLightColor(0, 0, v41);
    dds3SetLightDir(0, 0, v10[2]);
    v16 = v8[12];
    v17 = v8[13];
    v18 = v8[14];
    v19 = v8[15];
    v42.x = v16;
    v42.y = v17;
    v42.z = v18;
    v42.w = v19;
    dds3SetLightColor(0, 1u, v42);
    dds3SetLightDir(0, 1u, v10[3]);
    v20 = v8[16];
    v21 = v8[17];
    v22 = v8[18];
    v23 = v8[19];
    v43.x = v20;
    v43.y = v21;
    v43.z = v22;
    v43.w = v23;
    dds3SetLightColor(0, 2u, v43);
    dds3SetLightDir(0, 2u, v10[4]);
    v25 = 0.2;
    v26 = 0.3;
    v27 = 1.0;
    v28 = 0.2;
  }
  else
  {
    v29 = v4[8];
    v30 = v4[9];
    v31 = v4[10];
    v32 = v4[11];
    v45.x = v29;
    v45.y = v30;
    v45.z = v31;
    v45.w = v32;
    dds3SetLightColor(0, 0, v45);
    dds3SetLightDir(0, 0, v6[2]);
    v33 = v4[12];
    v34 = v4[13];
    v35 = v4[14];
    v36 = v4[15];
    v46.x = v33;
    v46.y = v34;
    v46.z = v35;
    v46.w = v36;
    dds3SetLightColor(0, 1u, v46);
    dds3SetLightDir(0, 1u, v6[3]);
    v37 = v4[16];
    v38 = v4[17];
    v39 = v4[18];
    v40 = v4[19];
    v47.x = v37;
    v47.y = v38;
    v47.z = v39;
    v47.w = v40;
    dds3SetLightColor(0, 2u, v47);
    dds3SetLightDir(0, 2u, v6[4]);
    v28 = 0.3;
    v25 = 0.35;
    v26 = 0.4;
    v27 = 1.0;
  }
  v44.y = v25;
  v44.w = v27;
  v44.x = v26;
  v44.z = v28;
  dds3SetAmbientColor(0, v44);
}

// 0x21aaad0
void shpResetCamera(void) {
  struct sdfVector4_t g_cameraPos_local;
  f32 *static_fields;

  g_cameraPos_local = g_cameraPos;
  CameraEyePos = g_cameraPos_local;
  CameraTargetPos = g_targetPos;
  CameraUpVector = g_vertical;
  ScreenParam->fovy = static_fields[14] * 0.017453292;
  SetLight(*(s16 *)(*(u64 *)static_fields + 36));
}

// 0x21aac30
void shpSetCamera(s32 a_type) {
  s16 shoptype;
  struct sdfVector4_t konnouyaTgt;
  void *v7;
  f32 *p_x;
  f32 *p_y;
  f32 *p_z;
  f32 *p_w;
  struct sdfVector4_t milkHallTgt;
  void *shpCameraPar_local;
  f32 v14;
  f32 v15;
  f32 v16;
  f32 v17;
  tagSHP_CAMERA_WK *cam;
  u32 v21;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  dds3Basic_t *v30;
  dds3Basic_t *ControlScene;
  dds3Basic_t *camera;
  dds3Basic_t *v33;
  f32 v35;
  f32 v36;
  f32 v37;
  struct sdfVector4_t v38;
  struct sdfVector4_t v39;
  f32 v40;
  sdfVector4_t v41;
  sdfVector4_t v43;

  shoptype = a_type;
  s_wk->shoptype = shoptype;
  g_fov = shpCameraPar->konnnouyaFov;
  if (shoptype == 1)
  {
    milkHallTgt = shpCameraPar->milkHallTgt;
    v39 = shpCameraPar->milkHallTgt;
    milkHallTgt = v39;
    g_targetPos = milkHallTgt;
    shpCameraPar_local = shpCameraPar;
    p_x = &shpCameraPar_local->milkHallPos.x;
    p_y = &shpCameraPar_local->milkHallPos.y;
    p_z = &shpCameraPar_local->milkHallPos.z;
    p_w = &shpCameraPar_local->milkHallPos.w;
    goto LABEL_19;
  }
  if (shoptype)
    goto LABEL_20;
  konnouyaTgt = shpCameraPar->konnouyaTgt;
  v38 = shpCameraPar->konnouyaTgt;
  konnouyaTgt = v38;
  g_targetPos = konnouyaTgt;
  v7 = shpCameraPar;
  p_x = &v7->konnouyaPos.x;
  p_y = &v7->konnouyaPos.y;
  p_z = &v7->konnouyaPos.z;
  p_w = &v7->konnouyaPos.w;
LABEL_19:
  v14 = *p_z;
  v15 = *p_y;
  v16 = *p_x;
  v17 = *p_w;
  g_cameraPos.x = v16;
  g_cameraPos.y = v15;
  g_cameraPos.z = v14;
  g_cameraPos.w = v17;
LABEL_20:
  cam = s_wk->cam;
  v21 = dds3SerializeID();
  x = g_targetPos.x;
  y = g_targetPos.y;
  z = g_targetPos.z;
  w = g_targetPos.w;
  v37 = g_cameraPos.y;
  v40 = g_cameraPos.x;
  v35 = g_cameraPos.w;
  v36 = g_cameraPos.z;
  g_cameraPos.w = v35;
  g_cameraPos.z = v36;
  g_cameraPos.y = v37;
  g_cameraPos.x = v40;
  v43.x = x;
  v43.y = y;
  v43.z = z;
  v43.w = w;
  *(u64 *)&v41.x = 0;
  v30 = dds3CameraObjectBasicAddTypeLookAt(v21, g_cameraPos, v43, v41);
  cam->camera = v30;
  dds3SetBasicName(s_wk->cam->camera, "shop_camera");
  dds3CameraObjectBasicSetFovy(&s_wk->cam->camera, g_fov * 0.017453292);
  ControlScene = dds3GetControlScene();
  camera = s_wk->cam->camera;
  v33 = SetActiveCamera(ControlScene, camera, 0);
  shpResetCamera();
  shpMakeLightPacket();
}

// 0x21ab040
void shpUpdataCameraPar(void) {
  s32 shoptype;
  struct sdfVector4_t konnouyaTgt;
  f32 *p_konnnouyaFov;
  struct sdfVector4_t milkHallTgt;
  struct sdfVector4_t g_cameraPos_local;

  if (!s_wk)
    return;
  shoptype = (u16)s_wk->shoptype;
  if (shoptype != 1)
  {
    if (shoptype)
      goto LABEL_20;
    konnouyaTgt = shpCameraPar->konnouyaTgt;
    g_targetPos = konnouyaTgt;
    g_cameraPos = shpCameraPar->konnouyaPos;
    p_konnnouyaFov = &shpCameraPar->konnnouyaFov;
LABEL_19:
    g_fov = *p_konnnouyaFov;
LABEL_20:
    g_cameraPos_local = g_cameraPos;
    CameraEyePos = g_cameraPos_local;
    CameraTargetPos = g_targetPos;
    CameraUpVector = g_vertical;
    ScreenParam->fovy = g_fov * 0.017453292;
    return;
  }
  milkHallTgt = shpCameraPar->milkHallTgt;
  g_targetPos = milkHallTgt;
  g_cameraPos = shpCameraPar->milkHallPos;
  p_konnnouyaFov = &shpCameraPar->milkHallFov;
  goto LABEL_19;
}

// 0x21ab370
void shpShpUpdateModelPos(void) {
  f32 KnyMasterPosZ;
  f32 KnyMasterPosX;
  f32 KnyMasterPosY;

  if (!s_wk)
    return;
  if (s_wk->shoptype)
    return;
  KnyMasterPosZ = SMDP->KnyMasterPosZ;
  KnyMasterPosX = SMDP->KnyMasterPosX;
  KnyMasterPosY = SMDP->KnyMasterPosY;
  shpSetPosModel(0, KnyMasterPosX, KnyMasterPosY, KnyMasterPosZ);
  return;
}

// 0x21ab5e0
void shpGetCameraPos(s32 a_type, f32 *a_px, f32 *a_py, f32 *a_pz) {
  tagSHP_CAMERA_WK *cam;
  dds3Basic_t *p_camera;
  f32 y;
  f32 *p_z;

  cam = s_wk->cam;
  if (!cam->camera)
    return;
  p_camera = &s_wk->cam->camera;
  dds3CameraObjectBasicGetTgtCam(p_camera, &shpModelGetCameraPos_targetPos, &shpModelGetCameraPos_cameraPos);
  if (a_type == 2)
  {
    *a_px = shpModelGetCameraPos_targetPos.x;
    y = shpModelGetCameraPos_targetPos.y;
    p_z = &shpModelGetCameraPos_targetPos.z;
    goto LABEL_20;
  }
  if (a_type == 1)
  {
    *a_px = shpModelGetCameraPos_cameraPos.x;
    y = shpModelGetCameraPos_cameraPos.y;
    p_z = &shpModelGetCameraPos_cameraPos.z;
LABEL_20:
    *a_py = y;
    *a_pz = *p_z;
  }
}

// 0x21ab790
void shpAddCameraPos(s32 a_type, f32 a_x, f32 a_y, f32 a_z) {

}

// 0x21ab7f0
static void Reset3DGlobal(void) {
  GlobalParamFlag = 0;
  *(_OWORD *)&GlobalParamScaleX = xmmword_3CFEE20;
}

// 0x21ab860
static void ResetGlobal(void) {
  tagSHP_CAMERA_WK *cam;

  GlobalParamFlag = 0;
  *(_OWORD *)&GlobalParamScaleX = xmmword_3CFEE20;
  cam = s_wk->cam;
  cam->ratio = 0.0;
  *(u64 *)&cam->transX = 0;
  cam->updateType = 0;
}

// 0x21ab960
void shpSetMove3D(f32 a_tgtx, f32 a_tgty, f32 a_tgtz, f32 a_ratio, s32 a_frame) {
  f32 v13;
  f32 v14;
  tagSHP_CAMERA_WK *cam;
  s64 y2;

  y2 = 0;
  shpPoint3To2(a_tgtx, a_tgty, a_tgtz, (f32 *)&y2 + 1, &y2);
  v13 = 2048.0 - *((f32 *)&y2 + 1);
  v14 = 2048.0 - *(f32 *)&y2;
  cam = s_wk->cam;
  cam->ratio = a_ratio;
  cam->count = 0;
  cam->frame = a_frame;
  cam->transX = v13;
  cam->transY = v14;
  cam->updateType = 1;
}

// 0x21aba50
void shpSetMove3DDef(s32 a_frame) {
  tagSHP_CAMERA_WK *cam;

  cam = s_wk->cam;
  cam->count = 0;
  cam->frame = a_frame;
  cam->updateType = 2;
}

// 0x21abad0
static bool ChkMotionEnd(s32 a_no) {
  dds3ModelHandle_t *v3;
  tagSHP_MODEL_CB *v5;
  u32 stat;
  dds3ModelHandle_t *ModelHandle;

  v3 = Allocate(dds3ModelHandle_t);
  _ctor(v3, 0);
  if ((u32)a_no > 0xF)
    return 0;
  v5 = s_wk->cb[a_no];
  stat = v5->stat;
  if ((stat & 2) == 0)
    return 0;
  if ((stat & 0x10) == 0)
    return 0;
  v5 = s_wk->cb[a_no];
  ModelHandle = dds3ObjectBaseGetModelHandle(&v5->unit);
  return mdlChkMotionEnd(ModelHandle);
}

// 0x21abc60
void shpUpdateCamera(void) {
  tagSHP_CAMERA_WK *cam;
  s32 frame;
  s32 count;
  f32 v9;
  f32 v10;
  s64 i;
  s32 *v15;
  s64 v17;
  s32 *m_Items;
  tagSHP_MODEL_CB *v19;
  dds3Basic_t *unit;
  evtUnitHandle_t *UnitHandle;
  sdf3DLightParallelPacket_t *v22;
  tagSHP_CAMERA_WK *v23;
  f32 v24;
  f32 v25;
  s32 updateType;
  f32 v28;
  f32 v29;
  float32x2_t *v32;
  u32 v33;
  u32 v34;
  f32 v37;
  f32 v39;

  cam = s_wk->cam;
  count = cam->count;
  frame = cam->frame;
  if ((s_wk->stat & 1) == 0)
  v9 = frame;
  v10 = count;
  for (i = 0; i != 16; ++i)
  {
    if (!ChkMotionEnd(i))
      continue;
    shpSetSmoothLoopMotion(i, s_wk->cb[i]->switchMotionNo);
  }
  v15 = shpGets_wk_CharID();
  v17 = 0;
  m_Items = v15;
  while (2)
  {
    v19 = s_wk->cb[v17];
    if ((v19->stat & 2) != 0)
    {
      unit = v19->unit;
      UnitHandle = dds3UnitObjectBasicGetUnitHandle(unit);
      v22 = g_pLightPacket_new[m_Items[v17]];
      if (!v22)
        goto LABEL_37;
      v22 = g_pLightPacket_new[m_Items[v17]];
      UnitHandle->PublicLightPacket = v22;
    }
LABEL_37:
    if (++v17 != 9)
      continue;
    break;
  }
  v23 = s_wk->cam;
  if (v23->updateType >= 1)
  {
    v23 = s_wk->cam;
    if ((v23->count & 0x80000000) == 0)
    {
      v24 = v10 + 1.0;
      v25 = v24 / v9;
      updateType = v23->updateType;
      if (updateType == 1)
        goto LABEL_57;
      v28 = 0.0;
      if (updateType != 2)
        goto LABEL_69;
      v39 = v25;
      v25 = v39;
      v23 = s_wk->cam;
      v29 = v23->ratio + (f32)(v25 * (f32)(1.0 - v23->ratio));
      v25 = (f32)(v9 - v24) / v9;
      v28 = 1.0 / v29;
      if ((f32)(1.0 / v29) >= 0.0)
      {
LABEL_69:
        GlobalParamScaleX = v28;
        GlobalParamScaleY = v28;
        GlobalParamFlag = 1;
        v32 = s_wk->cam;
        v33 = v32[4].n64_u32[1];
        v34 = v32[5].n64_u32[0];
        *(float32x2_t *)&GlobalParamTransX = vmul_n_f32(vmul_n_f32(v32[3], v28), v25);
        v32[4].n64_u32[1] = v33 + 1;
        if (v33 + 1 == v34)
        {
          v32 = s_wk->cam;
          v32[5].n64_u32[1] = 0;
          v32[4].n64_u32[1] = -1;
        }
        return;
      }
      goto LABEL_9001;
LABEL_57:
      v37 = v25;
      v25 = v37;
      v23 = s_wk->cam;
      v28 = 1.0 / (f32)(1.0 - (f32)(v25 * (f32)(1.0 - v23->ratio)));
      if (v28 >= 0.0)
        goto LABEL_69;
LABEL_9001:
    }
  }
}

// 0x21ac390
void shpDeleteModel(tagSHP_MODEL_CB *cb) {
  tagSHP_MODEL_CB *v3;
  dds3Basic_t *unit;
  tagSHP_MODEL_CB *v5;

  v3 = cb;
  if (cb)
  {
    unit = v3->unit;
    if (unit)
    {
      dds3UnitObjectBasicDelete(unit);
      v5 = cb;
      v5->unit = 0;
      v3 = cb;
    }
    v3->stat &= ~1u;
  }
}

// 0x21ac420
static void CreateModel(tagSHP_MODEL_CB *cb) {
  tagSHP_MODEL_CB *v4;
  u32 v5;
  dds3Basic_t *v7;
  sdfVector4_t v8;
  sdfVector4_t v9;

  v4 = cb;
  v5 = dds3SerializeID();
  v8.w = 1.0;
  v8.x = 0.0;
  v8.y = 0.0;
  v8.z = 0.0;
  v9.x = 0.0;
  v9.y = 0.0;
  v9.z = 0.0;
  v9.w = 1.0;
  v7 = dds3UnitObjectBasicAdd(v5, v8, v9);
  v4->unit = v7;
  cb->stat |= 1u;
}

// 0x21ac530
void shpSetModel(s32 a_objId, MODELTYPE a_majorNo, s32 a_minorNo) {
  tagSHP_MODEL_CB *v8;
  u32 v9;
  dds3Basic_t *unit;
  tagSHP_MODEL_CB *cb;
  u64 v13;
  dds3ModelHandle_t *v14;

  if ((u32)a_objId <= 0xF)
  {
    v8 = s_wk->cb[a_objId];
    if ((v8->stat & 1) != 0)
    {
      dds3ObjectBaseMakeUnit(v8->unit, a_majorNo, a_minorNo);
      dds3ObjectBaseOnFlag(&v8->unit, 1u);
      dds3ObjectBaseOnFlag(&v8->unit, 0x400u);
      if ((u32)(a_objId - 3) >= 6 && a_objId)
      {
        if (a_objId != 1)
          goto LABEL_11;
        v8->ot = 23;
        v9 = v8->stat | 8;
      }
      else
      {
        v8->ot = 28;
        v9 = v8->stat & 0xFFFFFFF7;
      }
      v8->stat = v9;
LABEL_11:
      unit = v8->unit;
      dds3UnitObjectBasicSetOt(unit, 0);
      v8->stat = v8->stat & 0xFFFFFFF9 | 2;
      cb = s_wk->cb;
      v13 = a_objId;
      cb[v13] = v8;
      v14 = Allocate(dds3ModelHandle_t);
      _ctor(v14, 0);
      dds3ObjectBaseGetModelHandle(&s_wk->cb[v13]->unit);
    }
  }
}

// 0x21ac740
void shpSetMotion(s32 a_no, s32 a_motNo) {
  dds3ModelHandle_t *v5;
  tagSHP_MODEL_CB *v7;
  s64 v8;
  Il2CppObject *ModelHandle;
  tagSHP_MODEL_CB *v12;

  v5 = Allocate(dds3ModelHandle_t);
  _ctor(v5, 0);
  if ((u32)a_no <= 0xF)
  {
    v7 = s_wk->cb[a_no];
    if ((v7->stat & 2) != 0)
    {
      v8 = a_no;
      ModelHandle = dds3ObjectBaseGetModelHandle(&v7->unit);
      if (!ModelHandle)
        goto LABEL_13;
      goto LABEL_9000;
      if (!ModelHandle)
      {
LABEL_13:
        mdlLoopMotion(ModelHandle, 0, a_motNo);
        Link(ModelHandle, ModelOt[0]);
        v12 = s_wk->cb[v8];
        v12->stat |= 0x10u;
        return;
      }
LABEL_9000:
      goto LABEL_13;
    }
  }
}

// 0x21ac920
void shpSetMotionSpeed(s32 a_no, f32 a_motSpeed) {
  dds3ModelHandle_t *v5;
  tagSHP_MODEL_CB *v7;
  Il2CppObject *ModelHandle;

  v5 = Allocate(dds3ModelHandle_t);
  _ctor(v5, 0);
  if ((u32)a_no <= 0xF)
  {
    v7 = s_wk->cb[a_no];
    if ((v7->stat & 2) != 0)
    {
      v7 = s_wk->cb[a_no];
      ModelHandle = dds3ObjectBaseGetModelHandle(&v7->unit);
      if (!ModelHandle)
        goto LABEL_16;
      goto LABEL_9000;
      if (!ModelHandle)
      {
LABEL_16:
        mdlSetMotionSpeed(ModelHandle, a_motSpeed);
        return;
      }
LABEL_9000:
      goto LABEL_16;
    }
  }
}

// 0x21aca90
void shpSetSingleMotion(s32 a_no, s32 a_motNo) {
  dds3ModelHandle_t *v5;
  tagSHP_MODEL_CB *v7;
  Il2CppObject *ModelHandle;

  v5 = Allocate(dds3ModelHandle_t);
  _ctor(v5, 0);
  if ((u32)a_no <= 0xF)
  {
    v7 = s_wk->cb[a_no];
    if ((v7->stat & 2) != 0)
    {
      v7 = s_wk->cb[a_no];
      ModelHandle = dds3ObjectBaseGetModelHandle(&v7->unit);
      if (!ModelHandle)
        goto LABEL_16;
      goto LABEL_9000;
      if (!ModelHandle)
      {
LABEL_16:
        mdlSingleMotion(ModelHandle, 0, a_motNo);
        return;
      }
LABEL_9000:
      goto LABEL_16;
    }
  }
}

// 0x21ac210
void shpSetSmoothLoopMotion(s32 a_no, s32 a_motNo) {
  dds3ModelHandle_t *v5;
  tagSHP_MODEL_CB *v7;
  Il2CppObject *ModelHandle;

  v5 = Allocate(dds3ModelHandle_t);
  _ctor(v5, 0);
  if ((u32)a_no <= 0xF)
  {
    v7 = s_wk->cb[a_no];
    if ((v7->stat & 2) != 0)
    {
      v7 = s_wk->cb[a_no];
      ModelHandle = dds3ObjectBaseGetModelHandle(&v7->unit);
      if (!ModelHandle)
        goto LABEL_16;
      goto LABEL_9000;
      if (!ModelHandle)
      {
LABEL_16:
        mdlSmoothLoopMotion(ModelHandle, 0, a_motNo, 10.0, 10.0, 0.0);
        return;
      }
LABEL_9000:
      goto LABEL_16;
    }
  }
}

// 0x21acc00
void shpSetSmoothSingleMotion(s32 a_no, s32 a_motNo) {
  dds3ModelHandle_t *v5;
  tagSHP_MODEL_CB *v7;
  Il2CppObject *ModelHandle;

  v5 = Allocate(dds3ModelHandle_t);
  _ctor(v5, 0);
  if ((u32)a_no <= 0xF)
  {
    v7 = s_wk->cb[a_no];
    if ((v7->stat & 2) != 0)
    {
      v7 = s_wk->cb[a_no];
      ModelHandle = dds3ObjectBaseGetModelHandle(&v7->unit);
      if (!ModelHandle)
        goto LABEL_16;
      goto LABEL_9000;
      if (!ModelHandle)
      {
LABEL_16:
        mdlSmoothSingleMotion(ModelHandle, 0, a_motNo, 10.0, 10.0, 0.0);
        return;
      }
LABEL_9000:
      goto LABEL_16;
    }
  }
}

// 0x21acd80
void shpSetSwitchMotion(s32 a_no, s32 a_motNo) {
  tagSHP_MODEL_CB *v6;

  if ((u32)a_no <= 0xF)
  {
    v6 = s_wk->cb[a_no];
    if ((v6->stat & 2) != 0)
    {
      v6 = s_wk->cb[a_no];
      v6->switchMotionNo = a_motNo;
    }
  }
}

// 0x21ace40
void shpSetMotionPause(s32 a_no, bool a_bPause) {
  dds3ModelHandle_t *v5;
  tagSHP_MODEL_CB *v7;
  Il2CppObject *ModelHandle;

  v5 = Allocate(dds3ModelHandle_t);
  _ctor(v5, 0);
  if ((u32)a_no <= 0xF)
  {
    v7 = s_wk->cb[a_no];
    if ((v7->stat & 2) != 0)
    {
      ModelHandle = dds3ObjectBaseGetModelHandle(&v7->unit);
      if (!ModelHandle)
      {
LABEL_14:
        if (a_bPause)
        {
          mdlMotionPause(ModelHandle);
        }
        else
        {
          mdlMotionPauseOff(ModelHandle);
        }
        return;
      }
      goto LABEL_14;
    }
  }
}

// 0x21ab4b0
void shpSetPosModel(s32 a_no, f32 a_x, f32 a_y, f32 a_z) {
  tagSHP_MODEL_CB *v10;
  tagSHP_MODEL_CB *p_fields;
  sdfVector4_t v13;

  if ((u32)a_no <= 0xF)
  {
    v10 = s_wk->cb[a_no];
    if ((v10->stat & 1) != 0)
    {
      p_fields = &v10->fields;
      v13.y = a_y;
      v13.z = a_z;
      v13.w = 1.0;
      v13.x = a_x;
      dds3SetPosPoseSet(&p_fields->unit, v13);
      return;
    }
  }
}

// 0x21ad010
void shpSetRotModel(s32 a_no, f32 a_x, f32 a_y, f32 a_z) {
  s64 v11;
  dds3Basic_t *p_unit;
  sdfVector3_t v16;

  if ((u32)a_no <= 0xF)
  {
    if ((s_wk->cb[a_no]->stat & 1) != 0)
    {
      v16.x = (f32)(a_x * 0.017453292) * 0.017453292;
      v16.y = (f32)(a_y * 0.017453292) * 0.017453292;
      v16.z = (f32)(a_z * 0.017453292) * 0.017453292;
      Internal_FromEulerRad(v16, 0);
      v11 = a_no;
      vct_B = vct_A;
      p_unit = &s_wk->cb[v11]->unit;
      dds3GetRotPoseSet(p_unit);
      dds3SetRotPoseSet(&s_wk->cb[v11]->unit, vct_A);
      return;
    }
  }
}

// 0x21ad280
void shpSetRotYModel(s32 a_no, f32 a_y) {
  s64 v4;
  f32 *p_x;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  dds3Basic_t *p_unit;
  sdfVector4_t v16;

  LODWORD(v4) = a_no;
  if ((u32)v4 <= 0xF)
  {
    if ((s_wk->cb[(u32)v4]->stat & 1) != 0)
    {
      vct_A = (struct sdfVector4_t)xmmword_3D015F0;
      FromRotation(a_y * 0.017453292);
      v4 = (u32)v4;
      p_x = &vf00.x;
      x = p_x[4];
      y = p_x[5];
      z = p_x[6];
      w = p_x[7];
      p_unit = &s_wk->cb[v4]->unit;
      v16.x = x;
      v16.y = y;
      v16.z = z;
      v16.w = w;
      dds3SetRotPoseSet(p_unit, v16);
      return;
    }
  }
}

// 0x21ad4b0
void shpSetSclModel(s32 a_no, f32 a_x, f32 a_y, f32 a_z) {
  tagSHP_MODEL_CB *v10;
  tagSHP_MODEL_CB *p_fields;
  sdfVector4_t v13;

  if ((u32)a_no <= 0xF)
  {
    v10 = s_wk->cb[a_no];
    if ((v10->stat & 1) != 0)
    {
      p_fields = &v10->fields;
      v13.y = a_y;
      v13.z = a_z;
      v13.w = 1.0;
      v13.x = a_x;
      dds3SetSclPoseSet(&p_fields->unit, v13);
      return;
    }
  }
}

// 0x21ad5e0
void shpSetSclModelEx(s32 a_no, f32 a_scale) {
  shpSetSclModel(a_no, a_scale, a_scale, a_scale);
}

// 0x21ad660
void shpSetDrwModel(s32 a_no, bool a_draw) {
  tagSHP_MODEL_CB *v6;

  if ((u32)a_no <= 0xF)
  {
    v6 = s_wk->cb[a_no];
    if ((v6->stat & 1) != 0)
    {
      if (a_draw)
      {
        v6 = s_wk->cb[a_no];
        dds3ObjectBaseOffFlag(&v6->unit, 1u);
      }
      else
      {
        v6 = s_wk->cb[a_no];
        dds3ObjectBaseOnFlag(&v6->unit, 1u);
      }
    }
  }
}

// 0x21ad770
void shpSetDrwModelAll(bool a_bDraw) {
  bool v4;
  bool v8;
  bool v12;
  bool v16;
  bool v20;
  bool v24;
  bool v28;
  bool v32;

  v4 = a_bDraw;
  shpSetDrwModel(0, a_bDraw);
  shpSetDrwModel(1, v4);
  v8 = a_bDraw;
  shpSetDrwModel(2, a_bDraw);
  shpSetDrwModel(3, v8);
  v12 = a_bDraw;
  shpSetDrwModel(4, a_bDraw);
  shpSetDrwModel(5, v12);
  v16 = a_bDraw;
  shpSetDrwModel(6, a_bDraw);
  shpSetDrwModel(7, v16);
  v20 = a_bDraw;
  shpSetDrwModel(8, a_bDraw);
  shpSetDrwModel(9, v20);
  v24 = a_bDraw;
  shpSetDrwModel(10, a_bDraw);
  shpSetDrwModel(11, v24);
  v28 = a_bDraw;
  shpSetDrwModel(12, a_bDraw);
  shpSetDrwModel(13, v28);
  v32 = a_bDraw;
  shpSetDrwModel(14, v32);
  shpSetDrwModel(15, v32);
}

// 0x21ada80
void shpSetColor(s32 a_no, u32 a_col) {
  dds3ModelHandle_t *v5;
  tagSHP_MODEL_CB *v7;
  Il2CppObject *ModelHandle;

  v5 = Allocate(dds3ModelHandle_t);
  _ctor(v5, 0);
  if ((u32)a_no <= 0xF)
  {
    v7 = s_wk->cb[a_no];
    if ((v7->stat & 2) != 0)
    {
      v7 = s_wk->cb[a_no];
      ModelHandle = dds3ObjectBaseGetModelHandle(&v7->unit);
      if (!ModelHandle)
        goto LABEL_16;
      goto LABEL_9000;
      if (!ModelHandle)
      {
LABEL_16:
        mdlSetColor(ModelHandle, a_col);
        return;
      }
LABEL_9000:
      goto LABEL_16;
    }
  }
}

// 0x21adbf0
void shpSetParamInit(s32 a_objId, MODELTYPE a_majorNo, s32 a_minorNo, s32 a_motionNo, f32 a_posx, f32 a_posy, f32 a_posz, f32 a_roty) {
  tagSHP_MODEL_CB *v25;

  if ((u32)a_objId <= 0xF)
  {
    CreateModel(&s_wk->cb[a_objId]);
    shpSetModel(a_objId, a_majorNo, a_minorNo);
    if ((a_motionNo & 0x80000000) == 0)
    {
      shpSetMotion(a_objId, a_motionNo);
      shpSetMotionSpeed(a_objId, 0.5);
    }
    shpSetPosModel(a_objId, a_posx, a_posy, a_posz);
    shpSetRotYModel(a_objId, a_roty);
    shpSetSclModel(a_objId, 1.0, 1.0, 1.0);
    v25 = s_wk->cb[a_objId];
    if ((v25->stat & 1) != 0)
    {
      v25 = s_wk->cb[a_objId];
      dds3ObjectBaseOnFlag(&v25->unit, 1u);
      v25 = s_wk->cb[a_objId];
    }
    v25->switchMotionNo = a_motionNo;
  }
}

// 0x21addd0
void shpSetTrans(bool a_bTrans) {
  if (!s_wk)
    return;
  if (a_bTrans)
  {
    s_wk->stat |= 1u;
  }
  else
  {
    s_wk->stat &= ~1u;
  }
}

// 0x21adec0
void shpSetDebugPrint(bool a_bPrint) {
  if (!s_wk)
    return;
  if (a_bPrint)
  {
    s_wk->stat |= 2u;
  }
  else
  {
    s_wk->stat &= ~2u;
  }
}

// 0x21adfb0
void shpDrawFieldLine(void) {
  ;
}

// 0x21adfc0
dds3Basic_t *shpGetBasic(s32 a_objId) {
  if ((u32)a_objId > 0xF)
    return 0;
  if (!s_wk)
    return 0;
  return s_wk->cb[a_objId]->unit;
}

// 0x21ae090
bool shpGetExist(s32 a_objId) {
  if ((u32)a_objId > 0xF)
    return 1;
  if (!s_wk)
    return 1;
  return s_wk->cb[a_objId]->stat & 1;
}

// 0x21ae170
void Init(void) {
  tagSHP_MODEL_WK *v1;
  s64 i;
  s64 v5;
  dds3Basic_t *v6;
  tagSHP_MODEL_CB *cb;
  Il2CppObject *v9;
  sdf3DLightParallelPacket_t *v13;
  s64 j;
  sdf3DLightParallelPacket_t *g_pLightPacket_new_local;
  sdf3DLightParallelPacket_t *v18;
  void *Asset;
  s64 naturalAligment;
  void *v26;
  void *p_ShpLightPacketPar;
  void *v30;

  v1 = Allocate(tagSHP_MODEL_WK);
  _ctor(v1);
  s_wk = v1;
  for (i = 32; i != 160; i += 8)
  {
    cb = s_wk->cb;
    v9 = Allocate(tagSHP_MODEL_CB);
    _ctor(v9, 0);
    *(Il2CppClass **)((char *)&cb->obj.klass + i) = v9;
    v5 = *(s64 *)((char *)&s_wk->cb->obj.klass + i);
    v6 = Allocate(dds3Basic_t);
    _ctor(v6, 0);
    *(u64 *)(v5 + 16) = v6;
  }
  shpCreateScene();
  ResetGlobal();
  s_wk->stat |= 1u;
  v13 = Allocate(sdf3DLightParallelPacket_t);
  _ctor(v13, 0);
  g_pLightPacket = v13;
  for (j = 32; j != 136; j += 8)
  {
    g_pLightPacket_new_local = g_pLightPacket_new;
    v18 = Allocate(sdf3DLightParallelPacket_t);
    _ctor(v18, 0);
    *(Il2CppClass **)((char *)&g_pLightPacket_new_local->obj.klass + j) = v18;
  }
  Load(Dependent, "shop_scr", "shop_scr");
  LoadSyncAll(_Ctrl_k__BackingField, 0);
  Asset = LoadAsset(_Ctrl_k__BackingField, "shop_scr", "shpLightPacketPar", 0);
  if (!Asset)
  {
    ShpLightPacketPar = 0;
    return;
  }
  if (Asset->klass->_2.naturalAligment >= (u32)naturalAligment)
  {
    if (Asset->klass->_2.typeHierarchy[naturalAligment - 1] == Project_shpLightPacketPar)
      v26 = Asset;
    else
      v26 = 0;
  }
  else
  {
    v26 = 0;
  }
  ShpLightPacketPar = (void *)v26;
  p_ShpLightPacketPar = &ShpLightPacketPar;
  if (Asset->klass->_2.naturalAligment >= (u32)naturalAligment)
  {
    if (Asset->klass->_2.typeHierarchy[naturalAligment - 1] == Project_shpLightPacketPar)
      v30 = Asset;
    else
      v30 = 0;
  }
  else
  {
    v30 = 0;
  }
}

// 0x21ae5b0
void End(void) {
  dds3Basic_t *ControlScene;
  dds3Basic_t *scene;

  Unload(Dependent, "shop_scr", 0);
  ControlScene = dds3GetControlScene();
  scene = ControlScene;
  if (!ControlScene)
  {
    ResetGlobal();
    if (!g_pLightPacket)
      goto LABEL_10;
    goto LABEL_19;
  }
  dds3DeleteScene(scene);
  ResetGlobal();
  if (!g_pLightPacket)
  {
LABEL_10:
    goto LABEL_11;
  }
LABEL_19:
  g_pLightPacket = 0;
LABEL_11:
  if (!s_wk)
    return;
  s_wk = 0;
}
