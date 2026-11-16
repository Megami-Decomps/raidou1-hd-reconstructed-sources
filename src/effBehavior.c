#include "types.h"
#include "EFFBEHAVIOR_TYPE.h"
#include "eff.h"
#include "effbehavior.h"
#include "sdf_vu0.h"

typedef struct bhvrHandle_t bhvrHandle_t;
typedef struct effBehavior_AlphaParams_t effBehavior_AlphaParams_t;
typedef struct effBehavior_Params_Basic_t effBehavior_Params_Basic_t;
typedef struct effBehavior_RGBParams_t effBehavior_RGBParams_t;
typedef struct effBehavior_SR_Params_t effBehavior_SR_Params_t;
typedef struct effPosture_t effPosture_t;
typedef struct sdfBinary sdfBinary;

static void PostureInit(bhvrHandle_t *hBehavior);

// 0x19692a0
static void PostureInit(bhvrHandle_t *hBehavior) {
  s32 *pPosture;
  s64 v4;
  s64 v5;
  effPosture_t *v6;

  pPosture = hBehavior->pPosture;
  if (pPosture[6] >= 1)
  {
    v4 = 0;
    v5 = 8;
    do
    {
      v6 = Allocate(effPosture_t);
      v6->frame = -1;
      QueryInterface(v6, *(void **)(*(u64 *)pPosture + 64));
      *(u64 *)&pPosture[v5] = v6;
      pPosture = hBehavior->pPosture;
      ++v4;
      v5 += 2;
    }
    while (v4 < pPosture[6]);
  }
}

// 0x1969390
sdfVector4_t effColorAnimation(effBehavior_RGBParams_t *pRGB, effBehavior_AlphaParams_t *pAlpha, s32 frame, s32 life) {
  float32x2_t v5;
  f32 v8;
  f32 v9;
  f32 v10;
  float32x2_t v11;
  f32 z;
  u32 type;
  Color *point;
  Color *v15;
  f32 v16;
  f32 v17;
  u64 v18;
  f32 v19;
  Color *v20;
  f32 v21;
  f32 v22;
  f32 v23;
  f32 v24;
  float32x2_t v25;
  f32 v26;
  f32 v27;
  f32 v28;
  f32 v29;
  sdfVector4_t result;

  v5.n64_u64[0] = *(u64 *)&pRGB->start.x;
  result.z = pRGB->start.z;
  result.w = pAlpha->transparency;
  if (!life)
    goto LABEL_22;
  v8 = life;
  v9 = 0.0;
  v10 = frame;
  v11.n64_u64[0] = *(u64 *)&pRGB->end.x;
  z = pRGB->end.z;
  type = pRGB->type;
  if (type > 2)
  {
    v19 = 0.0;
  }
  else if (pRGB->type)
  {
    point = pRGB->point;
    v15 = point[0];
    v16 = v15->color.z;
    v17 = v15->rate * v8;
    v18 = *(u64 *)&v15->color.x;
    if (v17 <= v10)
    {
      if (type == 2)
      {
        v20 = point[1];
        v21 = v20->rate * v8;
        if (v21 > v10)
        {
          v22 = v10 - v17;
          v23 = v21 - v17;
          z = v20->color.z;
          result.z = v15->color.z;
          v5.n64_u64[0] = *(u64 *)&v15->color.x;
          v11.n64_u64[0] = *(u64 *)&v20->color.x;
          v19 = v22 / v23;
          goto LABEL_13;
        }
        v17 = v20->rate * v8;
        v16 = v20->color.z;
        v18 = *(u64 *)&v20->color.x;
      }
      v5.n64_u64[0] = v18;
      result.z = v16;
      v19 = (f32)(v10 - v17) / (f32)(v8 - v17);
      goto LABEL_13;
    }
    z = v15->color.z;
    v11.n64_u64[0] = *(u64 *)&v15->color.x;
    v19 = v10 / v17;
  }
  else
  {
    v19 = v10 / v8;
  }
LABEL_13:
  v24 = 1.0;
  v25.n64_u64[0] = vsub_f32(v11, v5).n64_u64[0];
  v26 = z - result.z;
  if (v19 <= 1.0)
    v24 = v19;
  if (v19 >= 0.0)
    v9 = v24;
  result.z = result.z + (f32)(v9 * v26);
  v5.n64_u64[0] = vadd_f32(v5, vmul_n_f32(v25, v9)).n64_u64[0];
  v27 = pAlpha->fadeInRate * v8;
  if (v27 > v10)
  {
    v28 = v10 / v27;
LABEL_21:
    result.w = result.w * v28;
    goto LABEL_22;
  }
  v29 = pAlpha->fadeOutRate * v8;
  if (v29 < v10)
  {
    v28 = (f32)(v8 - v10) / (f32)(v8 - v29);
    goto LABEL_21;
  }
LABEL_22:
  LODWORD(result.y) = v5.n64_u32[1];
  result.x = v5.n64_f32[0];
  return result;
}

// 0x19694e0
f32 effSRAnimation(effBehavior_SR_Params_t *pSR, f32 frame, f32 life) {
  f32 result;
  f32 end;
  u32 type;
  Float *point;
  Float *v9;
  f32 sr;
  f32 v11;
  f32 v12;
  Float *v13;
  f32 v14;
  f32 v15;
  f32 v16;

  result = pSR->start;
  if (life == 0.0)
    return result;
  end = pSR->end;
  type = pSR->type;
  if (type > 2)
  {
    v12 = 0.0;
    goto LABEL_13;
  }
  if (!pSR->type)
  {
LABEL_12:
    v12 = frame / life;
    goto LABEL_13;
  }
  point = pSR->point;
  v9 = point[0];
  sr = v9->sr;
  v11 = v9->rate * life;
  if (v11 <= frame)
  {
    if (type == 2)
    {
      v13 = point[1];
      v14 = v13->rate * life;
      if (v14 > frame)
      {
        end = v13->sr;
        result = v9->sr;
        v12 = (f32)(frame - v11) / (f32)(v14 - v11);
        goto LABEL_13;
      }
      v11 = v13->rate * life;
      sr = v13->sr;
    }
    frame = frame - v11;
    life = life - v11;
    result = sr;
    goto LABEL_12;
  }
  end = v9->sr;
  v12 = frame / v11;
LABEL_13:
  v15 = 1.0;
  if (v12 <= 1.0)
    v15 = v12;
  if (v12 >= 0.0)
    v16 = v15;
  else
    v16 = 0.0;
  return result + (f32)((f32)(end - result) * v16);
}

// 0x19695b0
void effAnimation(effPosture_t *pPosture, effBehavior_Params_Basic_t *pParams, s32 frame, const sdfVector4_t *pOldPos) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  effBehavior_SR_Params_t *scale;
  u32 life;
  f32 start;
  f32 v16;
  f32 v17;
  f32 v18;
  f32 end;
  u32 type;
  Float *point;
  Float *v22;
  f32 sr;
  f32 v24;
  f32 v25;
  effBehavior_SR_Params_t *v26;
  f32 v27;
  Float *v28;
  f32 v29;
  f32 v30;
  f32 v31;
  effBehavior_SR_Params_t *rotate;
  _OWORD *p_x;
  __int128 v35;
  __int128 v36;
  __int128 v38;
  _OWORD *v39;
  __int128 v40;
  sdfMatrix4_t *p_TM;
  long f64 v42;
  struct sdfVector4_t pos;
  f32 *v48;
  float32x4_t *v52;
  float32x4_t v53;
  f32 v55;
  f32 v56;
  u32 v57;
  Float *v58;
  Float *v59;
  f32 v60;
  f32 v61;
  f32 v62;
  _OWORD *v66;
  __int128 v67;
  __int128 v68;
  f32 v69;
  Float *v70;
  f32 v71;
  f32 v72;
  f32 v73;
  sdfMatrix4_t v76;
  sdfMatrix4_t v77;
  sdfMatrix4_t v78;
  sdfMatrix4_t v79;
  sdfVector4_t v80;
  sdfVector4_t v81;
  sdfVector4_t v83;

  w = pOldPos->w;
  z = pOldPos->z;
  y = pOldPos->y;
  x = pOldPos->x;
  pPosture->abgr = effColorAnimation(pParams->rgb, pParams->alpha, frame, pParams->life);
  scale = pParams->scale;
  life = pParams->life;
  start = scale->start;
  if (life)
  {
    v16 = frame;
    v17 = 0.0;
    v18 = life;
    end = scale->end;
    type = scale->type;
    if (type > 2)
    {
      v25 = 0.0;
      goto LABEL_17;
    }
    if (!scale->type)
    {
      v25 = v16 / v18;
      goto LABEL_17;
    }
    point = scale->point;
    v22 = point[0];
    sr = v22->sr;
    v24 = v22->rate * v18;
    if (v24 > v16)
    {
      end = v22->sr;
      v25 = v16 / v24;
      goto LABEL_17;
    }
    if (type == 2)
    {
      v28 = point[1];
      v29 = v28->rate * v18;
      if (v29 > v16)
      {
        end = v28->sr;
        start = v22->sr;
        v25 = (f32)(v16 - v24) / (f32)(v29 - v24);
        goto LABEL_17;
      }
      v24 = v28->rate * v18;
      sr = v28->sr;
    }
    start = sr;
    v25 = (f32)(v16 - v24) / (f32)(v18 - v24);
LABEL_17:
    v30 = end - start;
    if (v25 <= 1.0)
      v31 = v25;
    else
      v31 = 1.0;
    if (v25 >= 0.0)
      v17 = v31;
    pPosture->scale = start + (f32)(v30 * v17);
    rotate = pParams->rotate;
    if (rotate->dir == 2)
    {
LABEL_23:
      p_x = &vf00.x;
      v35 = p_x[5];
      p_x[12] = p_x[4];
      p_x[13] = v35;
      v36 = p_x[7];
      p_x[14] = p_x[6];
      p_x[15] = v36;
      effGetSelCameraTM(&v76, 0);
      v77 = v76;
      v38 = *(_OWORD *)&v77.m01;
      v39 = &vf00.x;
      v39[4] = *(_OWORD *)&v77.m00;
      v39[5] = v38;
      v40 = *(_OWORD *)&v77.m03;
      v39[6] = *(_OWORD *)&v77.m02;
      v39[7] = v40;
      p_TM = &effGetSelScreenParam()->TM;
      sub_19636F0(p_TM, 0, v42);
      pos = pPosture->pos;
      vct_A = pos;
      vct_A.w = 1.0;
      get_transpose(&v79, &mtx_A, 0);
      v78 = v79;
      v80 = op_Multiply_60923920(&v78, vct_A, 0);
      vct_A.x = v80.x * (f32)(1.0 / v80.w);
      vct_A.y = v80.y * (f32)(1.0 / v80.w);
      vct_A.z = v80.z * (f32)(1.0 / v80.w);
      vct_A.w = 1.0 / v80.w;
      vct_B = vct_A;
      v48 = &vf00.x;
      v48[4] = x;
      v48[5] = y;
      v48[6] = z;
      v48[7] = w;
      vct_A.w = 1.0;
      get_transpose(&v79, &mtx_A, 0);
      v83 = vct_A;
      v78 = v79;
      v81 = op_Multiply_60923920(&v78, v83, 0);
      vct_A.x = v81.x * (f32)(1.0 / v81.w);
      vct_A.y = v81.y * (f32)(1.0 / v81.w);
      vct_A.z = v81.z * (f32)(1.0 / v81.w);
      vct_A.w = 1.0 / v81.w;
      v53 = vsubq_f32(v52[1], v52[2]);
      v52[1] = v53;
      v53.n128_u32[0] = LODWORD(vct_A.y);
      if (vct_A.x == 0.0)
      {
        if (v53.n128_f32[0] == 0.0)
        {
          goto LABEL_73;
        }
      }
      v69 = sub_188E410(*(long f64 *)&v53);
      pPosture->rotate = v69;
LABEL_74:
      v66 = &vf00.x;
      v67 = v66[13];
      v66[4] = v66[12];
      v66[5] = v67;
      v68 = v66[15];
      v66[6] = v66[14];
      v66[7] = v68;
      return;
LABEL_73:
      goto LABEL_74;
    }
    v56 = rotate->start;
    v55 = rotate->end;
    v57 = rotate->type;
    if (v57 > 2)
    {
      v62 = 0.0;
      goto LABEL_88;
    }
    if (!rotate->type)
    {
LABEL_87:
      v62 = v16 / v18;
      goto LABEL_88;
    }
    v58 = rotate->point;
    v59 = v58[0];
    v60 = v59->sr;
    v61 = v59->rate * v18;
    if (v61 > v16)
    {
      v55 = v59->sr;
      v62 = v16 / v61;
LABEL_88:
      if (v62 <= 1.0)
        v72 = v62;
      else
        v72 = 1.0;
      if (v62 >= 0.0)
        v73 = v72;
      else
        v73 = 0.0;
      v27 = v56 + (f32)((f32)(v55 - v56) * v73);
      goto LABEL_95;
    }
    if (v57 == 2)
    {
      v70 = v58[1];
      v71 = v70->rate * v18;
      if (v71 > v16)
      {
        v16 = v16 - v61;
        v18 = v71 - v61;
        v55 = v70->sr;
LABEL_86:
        v56 = v60;
        goto LABEL_87;
      }
      v61 = v70->rate * v18;
      v60 = v70->sr;
    }
    v16 = v16 - v61;
    v18 = v18 - v61;
    goto LABEL_86;
  }
  pPosture->scale = start;
  v26 = pParams->rotate;
  if (v26->dir == 2)
    goto LABEL_23;
  v27 = v26->start;
LABEL_95:
  pPosture->rotate = v27;
}

// 0x1969ce0
void effAnimation_Init(effPosture_t *pPosture, effBehavior_Params_Basic_t *pParams, s32 frame, const sdfVector4_t *pOldPos) {
  pPosture->rotate = 0.0;
  effAnimation(pPosture, pParams, frame, pOldPos);
}

// 0x1969cf0
void effBlurInit(bhvrHandle_t *hBehavior, s32 number) {
  s64 v5;
  effPosture_t *pPosture;
  s64 v7;
  s64 v8;
  bool v9;
  s64 v10;
  s32 v11;
  s32 v12;
  s64 v13;
  effPosture_t *v14;
  s64 v15;
  s64 v16;
  effPosture_t *v17;

  v5 = hBehavior->pParams->blur->length * hBehavior->pParams->blur->accurate;
  if ((u32)v5)
  {
    pPosture = hBehavior->pPosture;
    v7 = v5 * number;
    v8 = hBehavior->number;
    if ((u32)v5 < 4 || ((u32)(v5 - 1) <= 0x7FFFFFFE ? (v9 = (u64)(v5 - 1) >> 31 == 0) : (v9 = 0), !v9))
    {
      v10 = 0;
      v11 = 0;
LABEL_10:
      v12 = v11 + 1;
      do
      {
        *(u32 *)(*((u64 *)&pPosture[v10] + v7 + v8) + 32) = -1;
        v10 = v12++;
      }
      while (v10 < v5);
      return;
    }
    v10 = (u32)v5 & 0xFFFFFFFC;
    v11 = v5 & 0xFFFFFFFC;
    v13 = v10;
    v14 = &pPosture[v7 + 3] + v8;
    do
    {
      v15 = *(v14 - 2);
      v13 -= 4;
      v16 = *(v14 - 1);
      (*(v14 - 3))->frame = -1;
      *(u32 *)(v15 + 32) = -1;
      v17 = v14;
      v14 += 4;
      *(u32 *)(v16 + 32) = -1;
      v17->frame = -1;
    }
    while (v13);
    if (v10 != v5)
      goto LABEL_10;
  }
}

// 0x1969e00
void effBlurReset(bhvrHandle_t *hBehavior, s32 number) {
  s64 v5;
  effPosture_t *m_Items;
  s64 v7;
  effPosture_t *v8;
  s64 v9;

  v5 = hBehavior->pParams->blur->length * hBehavior->pParams->blur->accurate;
  if ((u32)v5)
  {
    m_Items = hBehavior->pPosture;
    v7 = *(&m_Items[hBehavior->number] + v5 * number);
    v8 = m_Items[number];
    *(sdfVector4_t *)(v7 + 16) = v8->pos;
    *(u32 *)(v7 + 32) = v8->frame;
    *(sdfVector4_t *)(v7 + 36) = v8->abgr;
    v9 = *(u64 *)&v8->scale;
    *(u32 *)(v7 + 32) = -1;
    *(u64 *)(v7 + 52) = v9;
  }
}

// 0x1969ed0
void effBlur(bhvrHandle_t *hBehavior, s32 number) {
  effBehavior_Blur_Params_t *blur;
  u32 length;
  s64 accurate;
  s64 v8;
  effPosture_t *m_Items;
  s64 v10;
  s64 v11;
  effPosture_t *v12;
  s32 frame;
  effPosture_t *v14;
  s64 v15;
  f32 v16;
  f32 w;
  f32 v18;
  s64 v19;
  s32 v20;
  s64 v21;
  f32 v22;
  s64 *v23;
  s64 v24;
  s64 v25;
  f32 v26;
  s64 v27;
  s64 v28;
  struct sdfVector4_t abgr;
  f32 scale;
  f32 rotate;
  effPosture_t *v32;
  s64 v33;
  sdfVector4_t *p_pos;
  s64 v35;
  f32 v36;
  s64 v37;
  f32 v38;
  sdfVector4_t *v39;
  __int128 v40;
  s64 v41;
  u64 v42;
  f32 v43;
  struct sdfVector4_t v44;
  s64 v45;
  s32 v46;
  float32x4_t v47;
  s64 v48;
  s64 v49;
  effPosture_t *pPosture;
  bool v51;
  s64 v52;
  s32 v53;
  s32 v54;
  f32 v55;
  s64 v56;
  s64 v57;
  s32 v58;
  s64 v61;
  s64 v62;
  struct sdfVector4_t v63;
  float32x4_t *static_fields;
  float32x4_t v65;
  float32x4_t v66;
  f32 v67;
  s64 v68;
  effPosture_t *v69;
  s64 v70;
  s64 v71;
  effPosture_t *v72;
  struct sdfVector4_t v73;
  f32 v76;
  f32 v77;
  f32 v78;
  f32 v79;
  float32x4_t v80;
  float32x4_t v81;
  sdfVector4_t v82;

  blur = hBehavior->pParams->blur;
  length = blur->length;
  accurate = blur->accurate;
  v8 = length * (u32)accurate;
  if ((u32)v8)
  {
    m_Items = hBehavior->pPosture;
    v10 = hBehavior->number;
    v11 = v10 + v8 * number;
    v12 = m_Items[number];
    frame = v12->frame;
    v14 = m_Items[v11];
    if (!frame)
    {
      v14->pos = v12->pos;
      v14->frame = v12->frame;
      v14->abgr = v12->abgr;
      pPosture = hBehavior->pPosture;
      *(u64 *)&v14->scale = *(u64 *)&v12->scale;
      if ((u32)v8 >= 4 && ((u32)(v8 - 1) <= 0x7FFFFFFE ? (v51 = (u64)(v8 - 1) >> 31 == 0) : (v51 = 0), v51))
      {
        v52 = (u32)v8 & 0xFFFFFFFC;
        v53 = v8 & 0xFFFFFFFC;
        v68 = v52;
        v69 = &pPosture[v11 + 3];
        do
        {
          v70 = *(v69 - 2);
          v68 -= 4;
          v71 = *(v69 - 1);
          (*(v69 - 3))->frame = -1;
          *(u32 *)(v70 + 32) = -1;
          v72 = v69;
          v69 += 4;
          *(u32 *)(v71 + 32) = -1;
          v72->frame = -1;
        }
        while (v68);
        if (v52 == v8)
          return;
      }
      else
      {
        v52 = 0;
        v53 = 0;
      }
      v54 = v53 + 1;
      do
      {
        *(u32 *)(*((u64 *)&pPosture[v52] + v11) + 32) = -1;
        v52 = v54++;
      }
      while (v52 < v8);
      return;
    }
    v14->frame = frame - 1;
    v15 = (u32)(v8 - accurate);
    if ((u32)v8 != (u32)accurate)
    {
      v16 = (u32)v8;
      w = v12->abgr.w;
      v18 = 0.0;
      v19 = 8 * (v8 + v8 * number) + 8 * v10;
      v20 = 1;
      v21 = v19 + 24;
      v22 = 1.0 / v16;
      do
      {
        v23 = ((char *)hBehavior->pPosture + v21);
        v21 -= 8;
        v24 = *v23;
        v25 = v23[-accurate];
        *(_OWORD *)(v24 + 16) = *(_OWORD *)(v25 + 16);
        *(u32 *)(v24 + 32) = *(u32 *)(v25 + 32);
        *(_OWORD *)(v24 + 36) = *(_OWORD *)(v25 + 36);
        v26 = w * v18;
        v18 = v22 + v18;
        v27 = *(u64 *)(v25 + 52);
        v28 = v20++;
        *(f32 *)(v24 + 48) = v26;
        *(u64 *)(v24 + 52) = v27;
      }
      while (v28 < v15);
    }
    v14->pos = v12->pos;
    v14->frame = v12->frame;
    abgr = v12->abgr;
    v14->frame = -1;
    v14->abgr = abgr;
    scale = v12->scale;
    rotate = v12->rotate;
    v14->scale = scale;
    v14->rotate = rotate;
    if ((u32)accurate != 1 && length >= 2)
    {
      v32 = hBehavior->pPosture;
      v33 = v11 + accurate;
      p_pos = &v14->pos;
      v35 = *((u64 *)&v32[v11] + accurate);
      v36 = *(f32 *)(v35 + 56);
      v77 = scale - *(f32 *)(v35 + 52);
      v78 = *(f32 *)(v35 + 52);
      v76 = rotate - v36;
      v79 = 1.0 / (f32)(u32)(accurate + 1);
      v80 = vmulq_n_f32(vsubq_f32((float32x4_t)v14->abgr, *(float32x4_t *)(v35 + 36)), v79);
      v81 = *(float32x4_t *)(v35 + 36);
      if (length != 2 && frame > 1)
      {
        v37 = v11 + (u32)(2 * accurate);
        if ((v32[v37]->frame & 0x80000000) == 0)
        {
          v38 = 0.0;
          v39 = NewSpecific(sdfVector4_t, 4u);
          v39[0] = hBehavior->pPosture[v37]->pos;
          v40 = *(_OWORD *)(v35 + 16);
          v41 = 8 * v33 + 24;
          *(_OWORD *)&v39[1] = v40;
          v42 = *(u64 *)((char *)v81.n128_u64 + 4);
          v43 = v81.n128_f32[3];
          v39[2] = *p_pos;
          v44 = *p_pos;
          v45 = (u32)(accurate - 1);
          v46 = 1;
          v39[3] = v44;
          do
          {
            v49 = *(s64 *)((char *)&hBehavior->pPosture->obj.klass + v41);
            v38 = v79 + v38;
            v82 = effHermitianSpline(v39, v38);
            *(f32 *)(v49 + 16) = v82.x;
            *(f32 *)(v49 + 20) = v82.y;
            v47 = v81;
            *(f32 *)(v49 + 24) = v82.z;
            v43 = v80.n128_f32[3] + v43;
            v48 = v46;
            v41 -= 8;
            ++v46;
            v47.n128_f32[0] = v80.n128_f32[0] + v81.n128_f32[0];
            *(u32 *)(v49 + 32) = frame;
            *(f32 *)(v49 + 28) = v82.w;
            *(f32 *)(v49 + 40) = v80.n128_f32[1] + *(f32 *)&v42;
            *(f32 *)(v49 + 44) = v80.n128_f32[2] + *((f32 *)&v42 + 1);
            *(f32 *)(v49 + 48) = v43;
            *(f32 *)(v49 + 36) = v80.n128_f32[0] + v81.n128_f32[0];
            v81 = v47;
            *(f32 *)(v49 + 52) = v78 + (f32)(v77 * v38);
            *(f32 *)(v49 + 56) = v36 + (f32)(v76 * v38);
            v42 = __PAIR64__(v80.n128_f32[2] + *((f32 *)&v42 + 1), v80.n128_f32[1] + *(f32 *)&v42);
          }
          while (v48 < v45);
        }
        return;
      }
      if (frame < 1 || (*(u32 *)(v35 + 32) & 0x80000000) != 0)
        return;
      v55 = 0.0;
      v56 = (u32)(accurate - 1);
      v57 = 8 * v33 + 24;
      v58 = 1;
      do
      {
        v73 = *(sdfVector4_t *)(v35 + 16);
        v62 = *(s64 *)((char *)&hBehavior->pPosture->obj.klass + v57);
        vct_A = v73;
        v63 = *p_pos;
        vct_B = v63;
        v55 = v79 + v55;
        v65 = static_fields[1];
        v66 = vsubq_f32(static_fields[2], v65);
        if (v55 <= 1.0)
          v67 = v55;
        else
          v67 = 1.0;
        if (v55 < 0.0)
          v67 = 0.0;
        static_fields[1] = vaddq_f32(v65, vmulq_n_f32(v66, v67));
        v57 -= 8;
        *(u32 *)(v62 + 32) = frame;
        *(sdfVector4_t *)(v62 + 16) = vct_A;
        v61 = v58++;
        v81 = vaddq_f32(v80, v81);
        *(float32x4_t *)(v62 + 36) = v81;
        *(f32 *)(v62 + 52) = v78 + (f32)(v77 * v55);
        *(f32 *)(v62 + 56) = v36 + (f32)(v76 * v55);
      }
      while (v61 < v56);
    }
  }
}

// 0x196a500
bhvrHandle_t *effCreate(EFFBEHAVIOR_TYPE type, u32 number, effBehavior_Params_Basic_t *pParams) {
  bhvrHandle_t *v7;
  effBehavior_Blur_Params_t *blur;
  u32 length;
  u32 v11;
  void *v12;
  void *v13;
  s64 v14;
  void *v15;
  s64 v17;
  s64 v18;
  s32 v19;
  s64 v20;
  s64 v21;
  void *v22;
  void *v23;
  sdfVector4_t *v25;
  sdfVector4_t *v27;
  sdfVector4_t *v28;

  v7 = Allocate(bhvrHandle_t);
  blur = pParams->blur;
  v7->type = type;
  length = blur->length;
  LODWORD(blur) = blur->accurate;
  *(u64 *)&v7->frame = 0;
  v7->flag = 0;
  v11 = number + length * number * (u32)blur;
  v7->number = number;
  v7->numall = v11;
  v12 = NewSpecific(effPosture_t, v11);
  v7->pPosture = v12;
  v13 = (pParams->klass->vtable._4_GetCopy.methodPtr)(pParams, pParams->klass->vtable._4_GetCopy.method);
  v7->pParams = v13;
  v14 = &v7->pParams;
  v7->pParamsBase = pParams;
  v15 = NewSpecific(effBehavior_Physics_t, number);
  v7->pPhysics = v15;
  if (number)
  {
    v17 = 0;
    v18 = number;
    v19 = 1;
    do
    {
      v21 = v7->pPhysics;
      v22 = (pParams->klass->vtable._5_NewPhysics.methodPtr)(pParams, pParams->klass->vtable._5_NewPhysics.method);
      v23 = v22;
      if (v22)
        QueryInterface(v22, *(void **)(*(u64 *)v21 + 64));
      v20 = v21 + 8 * v17;
      *(u64 *)(v20 + 32) = v23;
      v17 = v19++;
    }
    while (v17 < v18);
  }
  v25 = *(sdfVector4_t *)(*(u64 *)v14 + 16);
  v27 = v25 + 1;
  *v27 = vf00;
  v28 = (*(u64 *)(*(u64 *)v14 + 16) + 32);
  *v28 = vf00;
  if (!pParams->offset)
    goto LABEL_20;
  goto LABEL_19;
  if (pParams->offset)
LABEL_19:
    v7->flag |= 1u;
LABEL_20:
  PostureInit(v7);
  return v7;
}

// 0x196a800
void Delete(bhvrHandle_t *hBehavior) {
  ;
}

// 0x196a820
void effCalc(bhvrHandle_t *hBehavior) {
  Calc(hBehavior->pParams);
  ++hBehavior->frame;
}

// 0x196af50
void effEmitterPositionGet(bhvrHandle_t *hBehavior, sdfVector4_t *pPos) {
  *pPos = hBehavior->pParams->emitter->pos;
}

// 0x196af70
void effEmitterPositionSet(bhvrHandle_t *hBehavior, const sdfVector4_t *pPos) {
  hBehavior->pParams->emitter->pos = pPos;
}

// 0x196af90
void effEmitterRotateGet(bhvrHandle_t *hBehavior, sdfVector4_t *pRot) {
  *pRot = hBehavior->pParams->emitter->rot;
}

// 0x196afb0
void effEmitterRotateSet(bhvrHandle_t *hBehavior, const sdfVector4_t *pRot) {
  hBehavior->pParams->emitter->rot = pRot;
}

// 0x196afd0
void ScaleSet(bhvrHandle_t *hBehavior, f32 scale) {
  effBehavior_Params_Basic_t *pParams;
  effBehavior_SR_Params_t *v5;
  effBehavior_SR_Params_t *v6;
  float32x2_t v7;
  Float *point;
  Float *v9;
  Float *v10;
  Float *v11;
  Float *v12;
  Float *v13;
  Float *v14;
  Float *v15;

  pParams = hBehavior->pParams;
  v5 = pParams->scale;
  v6 = hBehavior->pParamsBase->scale;
  v7.n64_u64[0] = *(u64 *)&v6->start;
  point = v6->point;
  v9 = point[0];
  v10 = point[1];
  v11 = point[2];
  *(float32x2_t *)&v5->start = vmul_n_f32(v7, scale);
  v12 = v5->point;
  v7.n64_f32[0] = v9->sr * scale;
  v13 = v12[0];
  v14 = v12[1];
  v15 = v12[2];
  LODWORD(v13->sr) = v7.n64_u32[0];
  v14->sr = v10->sr * scale;
  v15->sr = v11->sr * scale;
  (pParams->klass->vtable._10__Scale.methodPtr)(pParams);
}

// 0x196b0a0
effBehavior_Params_Basic_t *effCreateParams(EFFBEHAVIOR_TYPE type, sdfBinary *bin) {
  void *v5;
  effBehavior_Params_Basic_t *result;
  void *v8;
  void *v10;
  void *v12;
  void *v14;
  void *v16;

  switch (type)
  {
    case 1u:
      v5 = Allocate(Project_effBehavior_Params_Smoke_t);
      _ctor_26653424(v5, bin);
      result = (effBehavior_Params_Basic_t *)v5;
      break;
    case 2u:
      v8 = Allocate(Project_effBehavior_Params_Spark_t);
      BasicBinRead(v8, bin);
      v8->radius = ReadFloat(bin, 0);
      v8->radius_r = ReadFloat(bin, 0);
      v8->speed = ReadFloat(bin, 0);
      v8->speed_r = ReadFloat(bin, 0);
      v8->accele = ReadFloat(bin, 0);
      v8->gravity = ReadFloat(bin, 0);
      result = (effBehavior_Params_Basic_t *)v8;
      break;
    case 3u:
      v10 = Allocate(Project_effBehavior_Params_Spiral_t);
      _ctor_26653808(v10, bin);
      result = (effBehavior_Params_Basic_t *)v10;
      break;
    case 4u:
      v12 = Allocate(Project_effBehavior_Params_Sphere_t);
      _ctor_26654048(v12, bin);
      result = (effBehavior_Params_Basic_t *)v12;
      break;
    case 5u:
      v14 = Allocate(Project_effBehavior_Params_HemiSpark_t);
      _ctor_26654240(v14, bin);
      result = (effBehavior_Params_Basic_t *)v14;
      break;
    case 6u:
      v16 = Allocate(Project_effBehavior_Params_AngleSpark_t);
      _ctor_26654240(v16, bin);
      v16->angle = ReadS32(bin, 0);
      result = (effBehavior_Params_Basic_t *)v16;
      break;
    default:
      result = 0;
      break;
  }
  return result;
}
