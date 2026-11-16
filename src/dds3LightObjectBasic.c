#include "types.h"
#include "dds3basic.h"
#include "dds3kerneldraw.h"
#include "dds3lightobjectbasic.h"
#include "dds3objectbase.h"
#include "dds3scenebasic.h"
#include "evt.h"
#include "sdf_vu0.h"

typedef struct dds3BasicFunction_t dds3BasicFunction_t;
typedef struct dds3Basic_t dds3Basic_t;
typedef struct dds3ObjectBaseControlWorkData_t dds3ObjectBaseControlWorkData_t;
typedef struct fldResourceLightPath_t fldResourceLightPath_t;
typedef struct fldResourceLight_t fldResourceLight_t;

dds3BasicFunction_t *Function;

static bool lightconstructor(dds3Basic_t *basic);
static void lightdestructor(dds3Basic_t *basic);
static bool lightmainprocedure(dds3Basic_t *basic);
static bool lightdrawprocedure(dds3Basic_t *basic);

// 0x22f9570
static bool lightconstructor(dds3Basic_t *basic) {
  dds3LightObjectBasicWorkData_t *v3;
  dds3ObjectBaseControlWorkData_t *inited;
  sdf3DLight_t *v5;
  sdf3DLightParallelPacket_t *v7;
  dds3Basic_t *basica;

  basica = basic;
  dds3InitPoseSet(basica);
  v3 = Allocate(dds3LightObjectBasicWorkData_t);
  _ctor(v3, 0);
  basic->workdata = (void *)v3;
  inited = dds3ObjectBaseInitControlWorkData(basica);
  v3->ObjectBaseControlWorkData = inited;
  dds3ObjectBaseOnFlag(basica, 0x62u);
  v5 = v3->Light;
  v3->Flag = 0;
  *(_OWORD *)&v5->color = xmmword_3D05D20;
  *(_OWORD *)&v5->v = xmmword_3D064D0;
  *(_OWORD *)&v3->Ambient = xmmword_3CF97B0;
  *(_OWORD *)&v3->InsideR = xmmword_3D027C0;
  v7 = Allocate(sdf3DLightParallelPacket_t);
  _ctor(v7, 0);
  v3->LightPacket = v7;
  return 1;
}

// 0x22f96c0
static void lightdestructor(dds3Basic_t *basic) {
  dds3ObjectBaseControlWorkData_t *workdata;
  s64 naturalAligment;
  dds3PoseSet_t *p_poseset;
  dds3PoseSet_t *poseset;

  workdata = basic->workdata;
  if (workdata)
  {
    LOBYTE(workdata[2].sdwid) < (u32)naturalAligment || *(dds3LightObjectBasicWorkData_t **)(*(u64 *)&workdata[1].sdwid + 8 * naturalAligment - 8) != dds3LightObjectBasicWorkData_t;
    dds3ObjectBaseFreeControlWorkData(workdata + 10);
    basic->workdata = 0;
    poseset = basic->poseset;
    p_poseset = &basic->poseset;
    if (poseset)
    {
      p_poseset = 0;
    }
  }
}

// 0x22f97c0
static bool lightmainprocedure(dds3Basic_t *basic) {
  sdf3DLight_t *v3;
  int8x16_t v4;
  void *workdata;
  u64 *v6;
  s32 monitor_high;
  struct sdfVector4_t v10;
  u32 monitor_low;
  f32 v13;
  u32 klass;
  int8x16_t v15;
  uint32x4_t v16;
  float32x4_t v17;
  struct sdfVector4_t v18;
  int8x16_t *v19;
  int8x16_t vct_A_local;
  u32 klass_high;
  f32 w;
  f32 x;
  u32 v25;
  u32 v26;
  u8 v27;
  u8 v28;
  bool v29;
  float32x2_t v30;
  float32x2_t v31;
  int32x2_t v32;
  uint32x2_t v33;
  u64 v34;
  int8x16_t v35;
  uint32x4_t v36;
  float32x4_t v37;
  struct sdfVector4_t v38;
  f32 v40;
  f32 v41;
  u32 v42;
  u32 v43;
  u8 v44;
  u8 v45;
  float32x2_t v46;
  float32x2_t v47;
  int32x2_t v48;
  uint32x2_t v49;
  u64 v50;
  sdf3DLight_t *v51;
  sdfVector4_t *p_color;
  sdfVector4_t *p_Ambient;
  Project_Basic_dds3Basic_t_WORK_c *v57;
  f32 v63;
  struct sdfVector4_t v66;
  f32 v69;

  v3 = NewSpecific(sdf3DLight_t, 3u);
  workdata = basic->workdata;
  v6 = v3;
  monitor_high = HIDWORD(workdata[3].monitor);
  if ((monitor_high & 1) != 0)
  {
    if ((monitor_high & 2) == 0)
    {
      v66 = *(sdfVector4_t *)&workdata[1].klass->_1.name;
      vct_A = v66;
      v10 = *(sdfVector4_t *)&workdata[1].monitor;
      vct_B = v10;
LABEL_64:
      v51 = DirLights[0];
      p_color = &v51->color;
      *p_color = vct_A;
      p_Ambient = &Ambient;
      *p_Ambient = vct_B;
      goto LABEL_70;
    }
    monitor_low = LOWORD(workdata[4].monitor);
    if (LOWORD(workdata[4].monitor))
    {
      LOWORD(workdata[4].monitor) = monitor_low - 1;
      v13 = 1.0 / (f32)monitor_low;
    }
    else
    {
      v13 = 1.0;
      HIDWORD(workdata[3].monitor) = monitor_high & 0xFFFFFFFD;
    }
    v69 = v13;
    klass = workdata[4].klass;
    v4.n128_u32[0] = klass;
    v15.n128_u64[0] = 0xFF000000FFLL;
    v15.n128_u64[1] = 0xFF000000FFLL;
    v4.n128_u32[1] = klass >> 8;
    v4.n128_u32[2] = HIWORD(klass);
    v16 = vandq_s8(v4, v15);
    v16.n128_u32[3] = vshrq_n_u32(vdupq_n_s32(klass), 0x18u).n128_u32[3];
    v17.n128_u64[0] = 0x3C0000003C000000LL;
    v17.n128_u64[1] = 0x3C0000003C000000LL;
    vct_A = (struct sdfVector4_t)vmulq_f32(vcvtq_f32_u32(v16), v17);
    v63 = 1.0 - v69;
    vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v63);
    v18 = *(sdfVector4_t *)&workdata[1].klass->_1.name;
    vct_B = v18;
    vct_B = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_B, v69);
    vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    vct_A_local = v19[1];
    v19[3] = vct_A_local;
    klass_high = HIDWORD(workdata[4].klass);
    w = vct_A.w;
    x = vct_A.x;
    v25 = vcvts_n_s32_f32(w, 7u);
    v26 = vcvts_n_u32_f32(w, 7u);
    v27 = vcvts_n_s32_f32(x, 7u);
    if ((f32)(w * 128.0) >= 0.0)
      v25 = v26;
    v28 = vcvts_n_u32_f32(x, 7u);
    v29 = (f32)(x * 128.0) < 0.0;
    v30.n64_u64[0] = *(u64 *)&vct_A.y;
    v31.n64_u64[0] = vmul_f32(v30, (float32x2_t)0x4300000043000000LL).n64_u64[0];
    v32.n64_u64[0] = vcvt_n_s32_f32(v30, 7u).n64_u64[0];
    v33.n64_u64[0] = vcvt_n_u32_f32(v30, 7u).n64_u64[0];
    if (v29)
      v28 = v27;
    v34 = vand_s8(vshl_u32(vbsl_s8(vcltz_f32(v31), v32, v33), (uint32x2_t)0x1000000008LL), (int8x8_t)0xFF00000000FF00LL).n64_u64[0];
    LODWORD(workdata[4].klass) = v28 | (v25 << 24) | v34 | HIDWORD(v34);
    vct_A_local.n128_u32[0] = klass_high;
    v35.n128_u64[0] = 0xFF000000FFLL;
    v35.n128_u64[1] = 0xFF000000FFLL;
    vct_A_local.n128_u32[1] = klass_high >> 8;
    vct_A_local.n128_u32[2] = HIWORD(klass_high);
    v36 = vandq_s8(vct_A_local, v35);
    v36.n128_u32[3] = vshrq_n_u32(vdupq_n_s32(klass_high), 0x18u).n128_u32[3];
    v37.n128_u64[0] = 0x3C0000003C000000LL;
    v37.n128_u64[1] = 0x3C0000003C000000LL;
    vct_A = (struct sdfVector4_t)vmulq_f32(vcvtq_f32_u32(v36), v37);
    vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v63);
    v38 = *(sdfVector4_t *)&workdata[1].monitor;
    vct_B = v38;
    vct_B = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_B, v69);
    vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    vct_B = vct_A;
    v40 = vct_A.w;
    v41 = vct_A.x;
    v42 = vcvts_n_s32_f32(v40, 7u);
    v43 = vcvts_n_u32_f32(v40, 7u);
    if ((f32)(v40 * 128.0) >= 0.0)
      v42 = v43;
    v44 = vcvts_n_s32_f32(v41, 7u);
    v45 = vcvts_n_u32_f32(v41, 7u);
    v29 = (f32)(v41 * 128.0) < 0.0;
    v46.n64_u64[0] = *(u64 *)&vct_A.y;
    v47.n64_u64[0] = vmul_f32(v46, (float32x2_t)0x4300000043000000LL).n64_u64[0];
    v48.n64_u64[0] = vcvt_n_s32_f32(v46, 7u).n64_u64[0];
    v49.n64_u64[0] = vcvt_n_u32_f32(v46, 7u).n64_u64[0];
    if (v29)
      v45 = v44;
    v50 = vand_s8(vshl_u32(vbsl_s8(vcltz_f32(v47), v48, v49), (uint32x2_t)0x1000000008LL), (int8x8_t)0xFF00000000FF00LL).n64_u64[0];
    HIDWORD(workdata[4].klass) = v45 | (v42 << 24) | v50 | HIDWORD(v50);
    vct_A = vct_C;
    goto LABEL_64;
  }
LABEL_70:
  v57 = workdata[1].klass;
  if (v57)
    QueryInterface(v57, *(void **)(*v6 + 64));
  v6[4] = v57;
  return 1;
}

// 0x22fa170
static bool lightdrawprocedure(dds3Basic_t *basic) {
  return 1;
}

// 0x22fa180
dds3ObjectBaseControlWorkData_t *dds3LightObjectBasicGetControlWorkData(dds3Basic_t *basic) {
  dds3ObjectBaseControlWorkData_t *workdata;
  s64 naturalAligment;

  workdata = (dds3ObjectBaseControlWorkData_t *)basic->workdata;
  if (workdata)
  {
    LOBYTE(workdata[2].sdwid) < (u32)naturalAligment || *(dds3LightObjectBasicWorkData_t **)(*(u64 *)&workdata[1].sdwid + 8 * naturalAligment - 8) != dds3LightObjectBasicWorkData_t;
  }
  return workdata[10];
}

// 0x22fa200
dds3Basic_t *Add(u32 serial) {
  dds3Basic_t *pObjectBasic;

  pObjectBasic = dds3SceneBasicAdd(9);
  pObjectBasic->serialID = serial;
  dds3ObjectBaseCreateMover(pObjectBasic);
  return pObjectBasic;
}

// 0x22fa280
void Delete(dds3Basic_t *basic) {
  dds3SceneBasicDelete(basic);
}

// 0x22fa310
void dds3LinkSceneLight(dds3Basic_t *basic, u32 frame) {
  void *workdata;
  s32 monitor_high;
  f32 w;
  f32 x;
  u32 v13;
  u32 v14;
  u8 v15;
  bool v16;
  u8 v17;
  float32x2_t v18;
  float32x2_t v19;
  int32x2_t v20;
  uint32x2_t v21;
  int32x2_t v22;
  u64 v23;
  struct sdfVector4_t Ambient_local;
  f32 v26;
  f32 v27;
  u32 v28;
  u32 v29;
  u8 v30;
  u8 v31;
  float32x2_t v32;
  float32x2_t v33;
  int32x2_t v34;
  uint32x2_t v35;
  int32x2_t v36;
  u64 v37;
  struct sdfVector4_t color;

  workdata = basic->workdata;
  monitor_high = HIDWORD(workdata[3].monitor);
  if (!frame)
  {
    HIDWORD(workdata[3].monitor) = monitor_high & 0xFFFFFFFC | 1;
    return;
  }
  HIDWORD(workdata[3].monitor) = monitor_high | 3;
  LOWORD(workdata[4].monitor) = frame;
  color = DirLights[0]->color;
  vct_A = color;
  w = vct_A.w;
  x = vct_A.x;
  v13 = vcvts_n_s32_f32(w, 7u);
  v14 = vcvts_n_u32_f32(w, 7u);
  v15 = vcvts_n_u32_f32(x, 7u);
  if ((f32)(w * 128.0) >= 0.0)
    v13 = v14;
  v16 = (f32)(x * 128.0) < 0.0;
  v17 = vcvts_n_s32_f32(x, 7u);
  v18.n64_u64[0] = *(u64 *)&vct_A.y;
  v19.n64_u64[0] = vmul_f32(v18, (float32x2_t)0x4300000043000000LL).n64_u64[0];
  v20.n64_u64[0] = vcvt_n_s32_f32(v18, 7u).n64_u64[0];
  v21.n64_u64[0] = vcvt_n_u32_f32(v18, 7u).n64_u64[0];
  v22.n64_u64[0] = vcltz_f32(v19).n64_u64[0];
  if (!v16)
    v17 = v15;
  v23 = vand_s8(vshl_u32(vbsl_s8(v22, v20, v21), (uint32x2_t)0x1000000008LL), (int8x8_t)0xFF00000000FF00LL).n64_u64[0];
  LODWORD(workdata[4].klass) = v17 | (v13 << 24) | v23 | HIDWORD(v23);
  Ambient_local = Ambient;
  vct_A = Ambient_local;
  v26 = vct_A.w;
  v27 = vct_A.x;
  v28 = vcvts_n_s32_f32(v26, 7u);
  v29 = vcvts_n_u32_f32(v26, 7u);
  v30 = vcvts_n_u32_f32(v27, 7u);
  if ((f32)(v26 * 128.0) >= 0.0)
    v28 = v29;
  v16 = (f32)(v27 * 128.0) < 0.0;
  v31 = vcvts_n_s32_f32(v27, 7u);
  v32.n64_u64[0] = *(u64 *)&vct_A.y;
  v33.n64_u64[0] = vmul_f32(v32, (float32x2_t)0x4300000043000000LL).n64_u64[0];
  v34.n64_u64[0] = vcvt_n_s32_f32(v32, 7u).n64_u64[0];
  v35.n64_u64[0] = vcvt_n_u32_f32(v32, 7u).n64_u64[0];
  v36.n64_u64[0] = vcltz_f32(v33).n64_u64[0];
  if (!v16)
    v31 = v30;
  v37 = vand_s8(vshl_u32(vbsl_s8(v36, v34, v35), (uint32x2_t)0x1000000008LL), (int8x8_t)0xFF00000000FF00LL).n64_u64[0];
  HIDWORD(workdata[4].klass) = v31 | (v28 << 24) | v37 | HIDWORD(v37);
}

// 0x22fa680
void dds3UnlinkSceneLight(dds3Basic_t *basic) {
  void *workdata;

  workdata = basic->workdata;
  HIDWORD(workdata[3].monitor) &= 0xFFFFFFFC;
}

// 0x22fa710
void dds3LinkLightObjectToUnitObject(dds3Basic_t *lightbasic, dds3Basic_t *unitbasic, u32 frame) {
  void *workdata;
  evtUnitHandle_t *klass;
  dds3Basic_t *light;

  light = lightbasic;
  workdata = unitbasic->workdata;
  klass = workdata[2].klass;
  evtLinkLightObjectBasic(klass, light, frame);
}

// 0x22fa7e0
void dds3UnlinkLightObjectFromUnitObject(dds3Basic_t *unitbasic, u32 frame) {
  void *workdata;
  evtUnitHandle_t *klass;

  workdata = unitbasic->workdata;
  klass = workdata[2].klass;
  evtUnlinkLightObjectBasic(klass, frame);
}

// 0x22fa8a0
void dds3SetLightObjectResoruce(dds3Basic_t *basic, fldResourceLight_t *resource) {
  void *workdata;
  __int128 v7;
  Project_Basic_dds3Basic_t_WORK_c *klass;

  if (basic)
  {
    workdata = basic->workdata;
    if (workdata)
    {
      HIDWORD(workdata[3].monitor) = resource->Flag & 1 | (4 * ((resource->Flag >> 1) & 1));
      v7 = *(_OWORD *)&resource->InsideR;
      LODWORD(workdata[3].monitor) = resource->AnimeType;
      klass = workdata[1].klass;
      *(_OWORD *)&workdata[2].monitor = v7;
      *(f32 *)&klass->_1.name = resource->DiffuseR;
      HIDWORD(klass->_1.name) = LODWORD(resource->DiffuseG);
      *(f32 *)&v7 = resource->DiffuseB;
      HIDWORD(klass->_1.namespaze) = 0;
      LODWORD(klass->_1.namespaze) = v7;
      *(f32 *)&workdata[1].monitor = resource->AmbientR;
      HIDWORD(workdata[1].monitor) = LODWORD(resource->AmbientG);
      *(f32 *)&v7 = resource->AmbientB;
      HIDWORD(workdata[2].klass) = 1065353216;
      LODWORD(workdata[2].klass) = v7;
    }
  }
}

// 0x22fa9a0
void dds3SetLightObjectPathResoruce(dds3Basic_t *basic, fldResourceLightPath_t *resource) {
  void *workdata;
  Project_Basic_dds3Basic_t_WORK_c *klass;
  f32 DiffuseB;
  f32 AmbientB;

  workdata = basic->workdata;
  *(void *)((char *)workdata + 40) = *(void *)&resource->InsideR;
  klass = workdata[1].klass;
  *(f32 *)&klass->_1.name = resource->DiffuseR;
  HIDWORD(klass->_1.name) = LODWORD(resource->DiffuseG);
  DiffuseB = resource->DiffuseB;
  HIDWORD(klass->_1.namespaze) = 0;
  *(f32 *)&klass->_1.namespaze = DiffuseB;
  *(f32 *)&workdata[1].monitor = resource->AmbientR;
  HIDWORD(workdata[1].monitor) = LODWORD(resource->AmbientG);
  AmbientB = resource->AmbientB;
  HIDWORD(workdata[2].klass) = 1065353216;
  *(f32 *)&workdata[2].klass = AmbientB;
}
