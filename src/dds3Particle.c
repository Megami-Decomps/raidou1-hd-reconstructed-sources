#include "types.h"
#include "dds3billboard.h"
#include "dds3effect_rand.h"
#include "dds3particle.h"
#include "effect.h"
#include "effoption.h"
#include "sdf_vu0.h"
#include "sdfrand.h"

#define DDS3PARTICLE_BILL_EXP 4294967295
#define PAR_REFRESH -268435455

typedef struct dds3ParticleColorAnim_t dds3ParticleColorAnim_t;
typedef struct dds3Particle_Basic_t dds3Particle_Basic_t;
typedef struct dds3Particle_SmokeOffset_ValF dds3Particle_SmokeOffset_ValF;
typedef struct dds3Particle_SphereSpiral2_ValF dds3Particle_SphereSpiral2_ValF;
typedef struct physicsHandle_t physicsHandle_t;
typedef struct sdfRandCB_t sdfRandCB_t;

struct dds3Particle_SmokeOffset_ValF {
    f32 Amplitude;
    f32 Angle;
    f32 Dist;
    f32 Up;
};

struct dds3Particle_SphereSpiral2_ValF {
    sdfVector4_t Axis;
    f32 Radian_S;
};

sdfRandCB_t *ParRand;

static physicsHandle_t *PhysicsCreate(s32 number);
static void PhysicsDelete(physicsHandle_t *hPhysics);
static void SetColorTable(dds3ParticleColorAnim_t *pColAnim, s32 frame);
static sdfVector4_t ColorAnim(dds3ParticleColorAnim_t *pColAnim, s32 frame);

// macros
// 0x19620a0: f32 PAR_RANDOM(f32 r)
#define PAR_RANDOM(r) (FA(r))

// 0x195bc00
void dds3ParticleManagerInit(void) {
  sdfRandCB_t *p_ParRand;
  sdfRandCB_t *ParRand_local;

  p_ParRand = &ParRand;
  ParRand_local = p_ParRand;
  sdfInitByTime(ParRand_local);
}

// 0x195bde0
void dds3ParticleManagerExit(void) {
  ;
}

// 0x19620c0
static physicsHandle_t *PhysicsCreate(s32 number) {
  s64 v3;
  physicsHandle_t *v4;
  s64 v5;
  s64 v6;
  physicsHandle_t *v7;
  s64 v8;

  v3 = NewSpecific(physicsHandle_t, number);
  v4 = (physicsHandle_t *)v3;
  if (number >= 1)
  {
    v5 = 0;
    v6 = v3 + 32;
    do
    {
      v7 = Allocate(physicsHandle_t);
      _ctor(v7, 0);
      *(u64 *)(v6 + v5) = v7;
      v8 = *(u64 *)(v6 + v5);
      *(u32 *)(v8 + 48) = 0;
      v5 += 8;
      *(sdfVector4_t *)(v8 + 52) = zeroVector;
    }
    while (8 * (u32)number != v5);
  }
  return v4;
}

// 0x1962200
static void PhysicsDelete(physicsHandle_t *hPhysics) {
  ;
}

// 0x1962210
static void SetColorTable(dds3ParticleColorAnim_t *pColAnim, s32 frame) {
  sdfVector4_t *v5;
  sdfVector4_t **p_color;
  int8x16_t v7;
  sdfVector4_t *color;
  int8x16_t v9;
  float32x4_t v10;
  s64 v11;
  s64 v12;
  int8x16_t *v13;
  uint32x4_t v14;
  s64 max_length_low;
  u32 v16;
  u32 alpha_low;
  s32 alpha_s;
  f32 v19;
  s32 alpha_e;
  u32 type;
  bool v22;
  s32 v24;
  s64 v25;
  sdfVector4_t *v26;
  s32 frame_h;
  u64 v28;
  int32x2_t v29;
  int32x4_t v30;
  u64 v31;

  v5 = NewSpecific(sdfVector4_t, pColAnim->_color->max_length);
  pColAnim->color = v5;
  p_color = &pColAnim->color;
  color = pColAnim->color;
  if (SLODWORD(color->max_length) >= 1)
  {
    v9.n128_u64[0] = 0xFF000000FFLL;
    v9.n128_u64[1] = 0xFF000000FFLL;
    v10.n128_u64[0] = 0x3C0000003C000000LL;
    v10.n128_u64[1] = 0x3C0000003C000000LL;
    v11 = 0;
    v12 = 44;
    do
    {
      v16 = pColAnim->_color[v11];
      v10.n128_u64[0] = 0x3C0000003C000000LL;
      v10.n128_u64[1] = 0x3C0000003C000000LL;
      v9.n128_u64[0] = 0xFF000000FFLL;
      v9.n128_u64[1] = 0xFF000000FFLL;
      v7.n128_u32[0] = v16;
      v7.n128_u32[1] = v16 >> 8;
      v7.n128_u32[2] = HIWORD(v16);
      v13 = (&color->obj + v11++);
      v14 = vandq_s8(v7, v9);
      v14.n128_u32[3] = vshrq_n_u32(vdupq_n_s32(v16), 0x18u).n128_u32[3];
      v7 = vmulq_f32(vcvtq_f32_u32(v14), v10);
      v13[2] = v7;
      color = *p_color;
      max_length_low = SLODWORD((*p_color)->max_length);
      *(u32 *)((char *)&(*p_color)->obj.klass + v12) = 0;
      v12 += 16;
    }
    while (v11 < max_length_low);
  }
  alpha_low = LOBYTE(pColAnim->_alpha);
  alpha_s = pColAnim->alpha_s;
  v19 = (f32)alpha_low * 0.0078125;
  pColAnim->alpha = v19;
  pColAnim->alpha_s_add = v19;
  if (alpha_s >= 1)
    pColAnim->alpha_s_add = v19 / (f32)alpha_s;
  alpha_e = pColAnim->alpha_e;
  pColAnim->alpha_e_sub = v19;
  if (alpha_e >= 1)
    pColAnim->alpha_e_sub = v19 / (f32)alpha_e;
  type = pColAnim->type;
  pColAnim->frame_end = frame;
  if (type != 1)
  {
    v22 = type == 2;
    v24 = frame >> (type != 2);
    if (v22)
      v25 = 1;
    else
      v25 = 2;
    pColAnim->frame_h = v24;
    v26 = NewSpecific(sdfVector4_t, v25);
    pColAnim->add = v26;
    frame_h = pColAnim->frame_h;
    v28 = 0;
    v29.n64_f32[0] = (f32)frame_h;
    if (!frame_h)
      v29.n64_f32[0] = 1.0;
    v30 = vdupq_lane_s32(v29, 0);
    do
    {
      v31 = v28++;
      pColAnim->add[v31] = (sdfVector4_t)vdivq_f32(vsubq_f32((float32x4_t)(*p_color)[v31 + 1], (float32x4_t)(*p_color)[v31]), v30);
    }
    while (v25 != v28);
  }
}

// 0x1962450
static sdfVector4_t ColorAnim(dds3ParticleColorAnim_t *pColAnim, s32 frame) {
  float32x2_t *color;
  s32 frame_end;
  float32x2_t v5;
  bool v8;
  s32 v9;
  s32 frame_h;
  s32 v13;
  float32x2_t *add;
  float32x2_t *v15;
  sdfVector4_t result;

  color = pColAnim->color;
  frame_end = pColAnim->frame_end;
  v5.n64_u64[0] = color[4].n64_u64[0];
  LODWORD(result.z) = color[5].n64_u32[0];
  if (frame_end - pColAnim->alpha_e > frame)
  {
    if (pColAnim->alpha_s < frame)
    {
      result.w = pColAnim->alpha;
      if (pColAnim->type != 1)
        goto LABEL_13;
LABEL_11:
      LODWORD(result.y) = HIDWORD(color[4].n64_u64[0]);
      goto LABEL_17;
    }
    result.w = pColAnim->alpha_s_add * (f32)frame;
    if (pColAnim->type == 1)
      goto LABEL_11;
LABEL_13:
    frame_h = pColAnim->frame_h;
    v8 = __OFSUB__(frame, frame_h);
    v13 = frame - frame_h;
    if (v13 < 0 != v8)
    {
      add = pColAnim->add;
      v5.n64_u64[0] = vadd_f32(v5, vmul_n_f32(add[4], (f32)frame)).n64_u64[0];
      result.z = result.z + (f32)(add[5].n64_f32[0] * (f32)frame);
      result.w = result.w + (f32)(add[5].n64_f32[1] * (f32)frame);
    }
    else
    {
      v15 = pColAnim->add;
      v5.n64_u64[0] = vadd_f32(color[6], vmul_n_f32(v15[6], (f32)v13)).n64_u64[0];
      result.z = color[7].n64_f32[0] + (f32)(v15[7].n64_f32[0] * (f32)v13);
    }
    LODWORD(result.y) = v5.n64_u32[1];
    goto LABEL_17;
  }
  v8 = __OFSUB__(frame_end, frame);
  v9 = frame_end - frame;
  if (v9 < 0 == v8)
  {
    result.w = pColAnim->alpha_e_sub * (f32)v9;
    if (pColAnim->type == 1)
      goto LABEL_11;
    goto LABEL_13;
  }
  v5.n64_u64[0] = *(u64 *)&zeroVector.x;
  result.z = zeroVector.z;
  result.w = zeroVector.w;
  LODWORD(result.y) = HIDWORD(*(u64 *)&zeroVector.x);
LABEL_17:
  result.x = v5.n64_f32[0];
  return result;
}

// 0x1962590
dds3Particle_Basic_t *dds3ParticleCreate(u16 type, void *pData) {
  dds3Particle_Basic_t *v6;
  dds3Billboard_Basic_t *hBillboard;
  dds3Particle_Basic_t *v9;
  effOption_Resource *monitor;
  effOption *v11;

  v6 = Create(pData[1].klass, 0);
  v6->type = type;
  hBillboard = v6->hBillboard;
  v9 = v6;
  if (hBillboard)
  {
    monitor = pData[2].monitor;
    v11 = effGet(monitor);
    hBillboard->option = v11;
  }
  return v9;
}

// 0x1962680
void dds3ParticleDelete(void *handle) {
  (*(*(u64 *)handle[16].monitor + 392))(handle[16].monitor, handle, *(u64 *)(*(u64 *)handle[16].monitor + 400));
}

// 0x1962710
void dds3ParticleDraw(void *handle) {
  Project_dds3EffectHandle_t_c *klass;
  f32 v5;
  f32 v6;
  s32 monitor;
  s32 v8;
  s64 klass_low;
  s64 v12;
  s64 v13;
  f32 v14;
  s32 klass_high;
  s64 v16;
  s32 v17;
  Project_dds3EffectHandle_t_c *v18;
  _OWORD *v19;
  f32 v20;
  s64 v21;
  s32 v22;
  s32 v24;
  f32 v27;
  f32 v28;
  s64 v29;
  s32 v30;
  u64 *v31;
  f32 v32;
  f32 v33;
  s64 v34;
  s32 v35;
  s64 v36;
  f32 v37;
  s32 v38;
  s32 v39;
  s32 v40;

  klass = handle[5].klass;
  if (LOBYTE(klass->_1.byval_arg.data))
    v5 = -1.0;
  else
    v5 = 1.0;
  if (HIWORD(handle[16].klass))
  {
    v6 = *((f32 *)&klass->_1.name + 1) * 0.017453292;
    monitor = handle[3].monitor;
    if (LODWORD(handle[12].klass))
    {
      v8 = 1;
      do
      {
        (*(*(u64 *)handle[16].monitor + 376))(handle[16].monitor, handle, *(u64 *)(*(u64 *)handle[16].monitor + 384));
        klass_low = LODWORD(handle[12].klass);
        v12 = v8++;
      }
      while (v12 < klass_low);
      if (monitor == -1 && (u32)klass_low)
      {
        v29 = LODWORD(handle[3].klass);
        if (!(u32)v29)
        {
          if ((u32)klass_low >= 4)
          {
            v38 = 0;
            if ((u32)(klass_low - 1) <= 0x7FFFFFFE && !((u64)(klass_low - 1) >> 32))
            {
              v38 = klass_low & 0x7FFFFFFC;
              v39 = klass_low & 0xFFFFFFFC;
              do
                v39 -= 4;
              while (v39);
              if ((u32)klass_low == v38)
                goto LABEL_14;
            }
          }
          else
          {
            v38 = 0;
          }
          v40 = v38 + 1;
          while (klass_low > v40++)
            ;
          goto LABEL_14;
        }
        v30 = 0;
        v31 = handle[11].monitor;
        v32 = (f32)(*(f32 *)&handle[5].klass->_1.name - *(f32 *)&handle[2].klass)
            / (f32)SHIDWORD(handle[3].klass);
        do
        {
          v33 = 1.0;
          v34 = 0;
          v35 = 1;
          do
          {
            v36 = v31[v34 + 4];
            if ((*(u32 *)(v36 + 48) & 0x80000000) == 0)
            {
              v37 = *(f32 *)(v36 + 72);
              *(f32 *)(v36 + 68) = v32 + *(f32 *)(v36 + 68);
              *(f32 *)(v36 + 72) = (f32)(v6 * v33) + v37;
            }
            v33 = v5 * v33;
            v34 = v35++;
          }
          while (v34 < v29);
          ++v30;
        }
        while (klass_low > v30);
      }
LABEL_14:
      LODWORD(handle[12].klass) = 0;
      v13 = LODWORD(handle[3].klass);
      if (!(u32)v13)
        return;
      goto LABEL_17;
    }
    (*(*(u64 *)handle[16].monitor + 376))(handle[16].monitor, handle, *(u64 *)(*(u64 *)handle[16].monitor + 384));
    v13 = LODWORD(handle[3].klass);
    if ((u32)v13)
    {
LABEL_17:
      v14 = 1.0;
      klass_high = HIDWORD(handle[3].klass);
      v16 = 0;
      v17 = 1;
      v18 = handle[11].klass;
      v19 = ((char *)&v18->_1.this_arg.data + 4);
      v20 = (f32)(*(f32 *)&handle[5].klass->_1.name - *(f32 *)&handle[2].klass) / (f32)klass_high;
      do
      {
        v21 = *((u64 *)handle[11].monitor + v16 + 4);
        v22 = *(u32 *)(v21 + 48);
        if (klass_high <= v22 || v22 < 0)
          goto LABEL_19;
        *(_OWORD *)&v18->_1.name = *(_OWORD *)(v21 + 16);
        *v19 = *(_OWORD *)(v21 + 52);
        if (monitor == -1)
        {
          v24 = *(u32 *)(v21 + 68);
          LODWORD(v18->_1.this_arg.data) = *(u32 *)(v21 + 72);
          LODWORD(v18->_1.byval_arg.data) = v24;
          HIDWORD(v18->_1.byval_arg.data) = *(u32 *)(v21 + 68);
          v27 = (f32)(v6 * v14) + *(f32 *)(v21 + 72);
          v28 = v20 + *(f32 *)(v21 + 68);
          if (v28 < 0.0)
            v28 = 0.0;
          *(f32 *)(v21 + 68) = v28;
          *(f32 *)(v21 + 72) = v27;
          SetAnimKey(v18, v22);
          goto LABEL_18;
        }
LABEL_18:
        dds3BillboardDraw(v18);
        v13 = LODWORD(handle[3].klass);
LABEL_19:
        v14 = v5 * v14;
        v16 = v17++;
      }
      while (v16 < v13);
    }
  }
}

// 0x1962ac0
void *dds3ParticleCopy(void *handle) {
  Project_dds3EffectHandle_t_c *klass;
  s64 v6;
  Project_dds3EffectHandle_t_c *v7;
  dds3Billboard_Basic_t *v8;
  s64 v10;
  dds3Billboard_Basic_t *v11;
  u16 v13;
  s64 v14;
  Il2CppClass *parent;

  klass = handle->klass;
  v6 = (klass[1]._1.image)(handle, handle, klass[1]._1.gc_desc);
  *(u16 *)(v6 + 260) = WORD2(handle[16].klass);
  if (LODWORD(handle[3].monitor) == -1)
  {
    v7 = handle[11].klass;
    v8 = dds3BillboardCopy(v7);
    v10 = *(u64 *)(v6 + 32);
    v11 = v8;
    v13 = *(u16 *)(v6 + 60);
    *(u64 *)&v11->scale.x = v10;
    dds3BillboardSetMode(v11, v13);
    *(u64 *)(v6 + 176) = v11;
  }
  v14 = *(u64 *)(v6 + 176);
  parent = handle[11].klass->_1.parent;
  *(u64 *)(v14 + 88) = parent;
  return (void *)v6;
}

// 0x1962ce0
void dds3ParticleSetScale(void *handle, f32 scale) {
  s64 naturalAligment;
  Project_dds3EffectHandle_t_c *klass;
  s64 v9;

  if (handle)
  {
    if (handle->klass->_2.naturalAligment < (u32)naturalAligment || handle->klass->_2.typeHierarchy[naturalAligment - 1] != dds3Particle_Basic_t)
    {
LABEL_16:
    }
  }
  (*(*(u64 *)handle[16].monitor + 424))(handle[16].monitor, handle, *(u64 *)(*(u64 *)handle[16].monitor + 432), scale);
  if (LODWORD(handle[3].monitor) == -1)
  {
    *(f32 *)&handle[5].klass->_1.name = *(f32 *)&handle[5].klass->_1.name * scale;
LABEL_8:
    goto LABEL_9;
  }
  else
  {
    goto LABEL_8;
  }
LABEL_9:
  klass = handle->klass;
  if (handle->klass->_2.naturalAligment < (u32)v9)
    goto LABEL_16;
  if (klass->_2.typeHierarchy[v9 - 1] != dds3Particle_Basic_t)
    goto LABEL_16;
  (*(*(u64 *)handle[16].monitor + 408))(handle[16].monitor, handle, *(u64 *)(*(u64 *)handle[16].monitor + 416));
  LODWORD(handle[12].klass) = handle[5].monitor;
  HIWORD(handle[16].klass) = 1;
}

// 0x1962e70
DDS3EFFECT_STATE dds3ParticleGetState(void *handle) {
  return HIWORD(handle[16].klass);
}

// 0x1962ef0
void dds3ParticleSetPosition(void *handle, const sdfVector4_t *pPos) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;

  w = pPos->w;
  z = pPos->z;
  y = pPos->y;
  x = pPos->x;
  *(f32 *)&handle[1].monitor = z;
  *((f32 *)&handle[1].monitor + 1) = w;
  *(f32 *)&handle[1].klass = x;
  *((f32 *)&handle[1].klass + 1) = y;
}

// 0x1962fc0
void dds3ParticleSetRotateMatrix(void *handle, const sdfMatrix4_t *pMatrix) {
  __int128 v6;
  __int128 v8;
  __int128 v10;
  __int128 v12;
  __int128 v17;
  __int128 v18;
  __int128 v20;
  _OWORD *p_x;
  __int128 v23;
  _OWORD *v25;
  __int128 v26;
  __int128 v27;
  __int128 v28;
  __int128 v29;
  __int128 v32;
  __int128 v33;
  __int128 v34;
  __int128 v36;
  __int128 v37;
  __int128 v38;
  sdfMatrix4_t v39;
  sdfMatrix4_t v40;
  sdfMatrix4_t v41;

  v6 = *(_OWORD *)&pMatrix->m01;
  *(_OWORD *)&v41.m00 = *(_OWORD *)&pMatrix->m00;
  *(_OWORD *)&v41.m01 = v6;
  v8 = *(_OWORD *)&pMatrix->m03;
  *(_OWORD *)&v41.m02 = *(_OWORD *)&pMatrix->m02;
  *(_OWORD *)&v41.m03 = v8;
  v10 = *(_OWORD *)&v41.m01;
  *(_OWORD *)&mtx_A.m00 = *(_OWORD *)&v41.m00;
  *(_OWORD *)&mtx_A.m01 = v10;
  v12 = *(_OWORD *)&v41.m03;
  *(_OWORD *)&mtx_A.m02 = *(_OWORD *)&v41.m02;
  *(_OWORD *)&mtx_A.m03 = v12;
  if (!handle)
  v17 = *(__int128 *)((char *)&handle[13] + 4);
  *(void *)&v41.m00 = *(void *)((char *)handle + 196);
  *(_OWORD *)&v41.m01 = v17;
  v18 = *(__int128 *)((char *)&handle[15] + 4);
  *(void *)&v41.m02 = *(void *)((char *)handle + 228);
  *(_OWORD *)&v41.m03 = v18;
  v20 = *(_OWORD *)&v41.m01;
  p_x = &vf00.x;
  p_x[8] = *(_OWORD *)&v41.m00;
  p_x[9] = v20;
  v23 = *(_OWORD *)&v41.m03;
  p_x[10] = *(_OWORD *)&v41.m02;
  p_x[11] = v23;
  v25 = &vf00.x;
  v26 = v25[9];
  *(_OWORD *)&v40.m00 = v25[8];
  *(_OWORD *)&v40.m01 = v26;
  v27 = v25[11];
  *(_OWORD *)&v40.m02 = v25[10];
  *(_OWORD *)&v40.m03 = v27;
  v28 = v25[5];
  *(_OWORD *)&v39.m00 = v25[4];
  *(_OWORD *)&v39.m01 = v28;
  v29 = v25[7];
  *(_OWORD *)&v39.m02 = v25[6];
  *(_OWORD *)&v39.m03 = v29;
  op_Multiply(&v41, &v40, &v39, 0);
  v32 = *(_OWORD *)&v41.m01;
  v33 = *(_OWORD *)&v41.m02;
  v34 = *(_OWORD *)&v41.m03;
  *(_OWORD *)&mtx_A.m00 = *(_OWORD *)&v41.m00;
  *(_OWORD *)&mtx_A.m01 = v32;
  *(_OWORD *)&mtx_A.m02 = v33;
  *(_OWORD *)&mtx_A.m03 = v34;
  v36 = *(_OWORD *)&mtx_A.m00;
  v37 = *(_OWORD *)&mtx_A.m01;
  v38 = *(_OWORD *)&mtx_A.m02;
  *(void *)((char *)handle + 140) = *(void *)&mtx_A.m03;
  *(_OWORD *)((char *)&handle[6].monitor + 4) = v37;
  *(_OWORD *)((char *)&handle[7].monitor + 4) = v38;
  *(_OWORD *)((char *)&handle[5].monitor + 4) = v36;
}

// 0x1963280
void dds3ParticleSetRGBA(void *handle, const sdfVector4_t *abgr) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;

  w = abgr->w;
  z = abgr->z;
  y = abgr->y;
  x = abgr->x;
  *((f32 *)&handle[10].klass + 1) = z;
  *(f32 *)&handle[10].monitor = w;
  *((f32 *)&handle[9].monitor + 1) = x;
  *(f32 *)&handle[10].klass = y;
}

// 0x1963330
void dds3ParticleSetLoop(void *handle, u8 loop) {
  LOBYTE(handle[17].klass) = loop != 0;
  HIWORD(handle[16].klass) = 1;
}

// 0x19633d0
u8 dds3ParticleGetLoop(void *handle) {
  return (u8)handle[17].klass;
}

// 0x1963450
dds3Particle_Basic_t *dds3ParticleExpCreate(u16 type, void *pData) {
  dds3Particle_Basic_t *v6;
  Project_libsdf_sdfResourceUnit_c *klass;
  u16 monitor;
  void *v12;
  dds3Billboard_Basic_t *v14;
  effOption_Resource *v15;
  effOption *v16;
  s64 v18;
  u16 billmode;

  v6 = dds3ParticleCreate(type, pData);
  if (!pData)
    goto LABEL_9;
  goto LABEL_7;
  if (!pData)
LABEL_7:
LABEL_9:
  klass = pData[2].klass;
  if (klass)
  {
    monitor = pData[1].monitor;
    v12 = *(void *)((*(klass->_1.image + 49))(klass, *((u64 *)klass->_1.image + 50)) + 32);
    v14 = dds3BillboardCreate(monitor, v12);
    v15 = pData[2].monitor;
    v16 = effGet(v15);
    v14->option = v16;
    v6->hBillboard = v14;
    v18 = *(u64 *)&v6->scale.x;
    billmode = v6->billmode;
    *(u64 *)&v14->scale.x = v18;
    dds3BillboardSetMode(v14, billmode);
  }
  return v6;
}
