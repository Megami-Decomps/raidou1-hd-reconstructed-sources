#include "types.h"
#include "sdf_vu0.h"
#include "shpdrawmisc.h"

typedef struct sdfIVector2_t sdfIVector2_t;

static f32 gVecX[128];
static f32 *gVecY;
static f32 *gPosX;
static f32 *gPosY;
static s16 *gFrame;
static s32 gBreakNum;

static void Box(s32 *X, s32 *Y, u32 Z, u32 *Col, u32 OtNo);
static s32 FloatToSprX(f32 a_x);
static s32 FloatToSprY(f32 a_y);
static void LineWide(f32 a_x0, f32 a_y0, f32 a_x1, f32 a_y1, u32 a_z, u32 *a_col, f32 a_w);
static void GetPosBezierCurve(f32 *a_px, f32 *a_py, s32 a_tx0, s32 a_ty0, s32 a_tx1, s32 a_ty1, s32 a_dx0, s32 a_dy0, s32 a_dx1, s32 a_dy1, f32 a_rate);
static void _BreakLineWide(f32 *a_x, f32 *a_y, u32 a_z, u32 *a_col, f32 a_w, s32 a_cnt);

// 0x217c8b0
static void Box(s32 *X, s32 *Y, u32 Z, u32 *Col, u32 OtNo) {
  ;
}

// 0x217c8c0
static s32 FloatToSprX(f32 a_x) {
  f32 v2;
  f32 v3;

  v2 = (s32)a_x;
  if (a_x == INFINITY)
    v2 = -2147500000.0;
  v3 = a_x - v2;
  if (v3 == INFINITY)
    return 0x80000000;
  else
    return (s32)v3;
}

// 0x217c900
static s32 FloatToSprY(f32 a_y) {
  f32 v2;
  f32 v3;

  v2 = (s32)a_y;
  if (a_y == INFINITY)
    v2 = -2147500000.0;
  v3 = a_y - v2;
  if (v3 == INFINITY)
    return 0x80000000;
  else
    return (s32)v3;
}

// 0x217c940
static void LineWide(f32 a_x0, f32 a_y0, f32 a_x1, f32 a_y1, u32 a_z, u32 *a_col, f32 a_w) {
  sdfVector4_t *v12;
  f32 *v14;
  s32 *v15;
  s32 *v16;
  u32 *v17;
  struct sdfVector4_t v22;
  s64 v28;
  char v29;
  s64 v30;
  char v31;
  sdfVector4_t *v32;
  sdfVector4_t *v33;
  struct sdfVector4_t v34;
  f32 *p_x;
  f32 v37;
  f32 v38;
  int32x2_t v41;
  int32x2_t v42;
  float32x2_t v43;
  float32x2_t v44;
  struct sdfVector4_t v46;
  int32x2_t v50;
  int32x2_t v51;
  float32x2_t v52;
  float32x2_t v53;
  struct sdfVector4_t v55;
  f32 v58;
  f32 v60;
  f32 v61;
  f32 v62;
  f32 v63;
  s32 v64;
  f32 v65;
  f32 v66;
  s32 v67;
  f32 v68;
  f32 v69;
  f32 v70;
  f32 v71;
  s32 v72;
  f32 v73;
  f32 v74;
  s32 v75;
  f32 v76;
  f32 v77;
  f32 v78;
  f32 v79;
  s32 v80;
  f32 v81;
  f32 v82;
  s32 v83;
  f32 v84;
  f32 v85;
  f32 v86;
  s32 v87;
  f32 v88;
  f32 v89;
  s32 v90;
  u32 *v91;
  u32 *v92;
  sdfVector4_t *v93;
  s64 v95;
  sdfVector4_t *v96;
  struct sdfVector4_t v97;

  v12 = NewSpecific(sdfVector4_t, 2u);
  *(_OWORD *)&v12[0] = 0u;
  *(_OWORD *)&v12[1] = 0u;
  v93 = NewSpecific(sdfVector4_t, 4u);
  *(_OWORD *)&v93[1] = 0u;
  *(_OWORD *)&v93[2] = 0u;
  *(_OWORD *)&v93[0] = 0u;
  v14 = &v93[0];
  *(_OWORD *)&v93[3] = 0u;
  v15 = NewSpecific(s32, 4u);
  v16 = NewSpecific(s32, 4u);
  v17 = NewSpecific(uint, 4u);
  *(u64 *)&v15[2] = 0;
  v92 = v17;
  *(u64 *)&v15[0] = 0;
  *(u64 *)&v16[2] = 0;
  v95 = v12;
  v96 = &v12[0];
  *(u64 *)&v16[0] = 0;
  *(u64 *)&v17[0] = 0;
  *(u64 *)&v17[2] = 0;
  v12[0].y = a_y0;
  v12[0].x = a_x0;
  v12[1].x = a_x1;
  v12[1].y = a_y1;
  *(u64 *)&v12[0].z = 0x3F80000000000000LL;
  *(u64 *)&v12[1].z = 0x3F80000000000000LL;
  vct_A.x = a_x1;
  vct_A.y = a_y1;
  *(u64 *)&vct_A.z = 0x3F80000000000000LL;
  v22 = *v96;
  vct_B = v22;
  vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  v91 = v15;
  __asm { FMOV            V8.2S, #1.0 }
  v28 = 0;
  vct_C = vct_A;
  v29 = 1;
  do
  {
    v31 = v29;
    v32 = (v95 + 16 * v28);
    v34 = v32[2];
    v33 = v32 + 2;
    v97 = v34;
    vct_B = v97;
    p_x = &v96[v28].x;
    v37 = *p_x;
    v38 = p_x[1];
    vct_A.x = v37;
    vct_A.y = v38;
    *(u64 *)&vct_A.z = _D8;
    vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    vct_B = vct_C;
    v41.n64_u64[0] = *(u64 *)&vct_B.y;
    v42.n64_u64[0] = *(u64 *)&vct_A.y;
    v43.n64_u32[0] = vdup_lane_s32(v41, 1).n64_u32[0];
    v44.n64_u32[0] = vdup_lane_s32(v42, 1).n64_u32[0];
    v43.n64_u32[1] = LODWORD(vct_B.x);
    v44.n64_u32[1] = LODWORD(vct_A.x);
    vct_A.z = (f32)(v44.n64_f32[1] * v41.n64_f32[0]) - (f32)(v43.n64_f32[1] * v42.n64_f32[0]);
    *(float32x2_t *)&vct_A.x = vsub_f32(vmul_f32(v42, v43), vmul_f32(v44, v41));
    sub_1949110(0);
    vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, a_w);
    v46 = *v33;
    vct_B = v46;
    vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    *(sdfVector4_t *)&v14[8 * v28] = vct_A;
    vct_A.x = v37;
    vct_A.y = v38;
    *(u64 *)&vct_A.z = 0x3F800000BF800000LL;
    vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    vct_B = vct_C;
    v50.n64_u64[0] = *(u64 *)&vct_B.y;
    v51.n64_u64[0] = *(u64 *)&vct_A.y;
    v52.n64_u32[0] = vdup_lane_s32(v50, 1).n64_u32[0];
    v53.n64_u32[0] = vdup_lane_s32(v51, 1).n64_u32[0];
    v52.n64_u32[1] = LODWORD(vct_B.x);
    v53.n64_u32[1] = LODWORD(vct_A.x);
    vct_A.z = (f32)(v53.n64_f32[1] * v50.n64_f32[0]) - (f32)(v52.n64_f32[1] * v51.n64_f32[0]);
    *(float32x2_t *)&vct_A.x = vsub_f32(vmul_f32(v51, v52), vmul_f32(v53, v50));
    sub_1949110(0);
    vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, a_w);
    v55 = *v33;
    vct_B = v55;
    vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    v29 = 0;
    v30 = 2 * v28;
    v28 = 1;
    *(sdfVector4_t *)((char *)v14 + ((16 * v30) | 0x10)) = vct_A;
  }
  while ((v31 & 1) != 0);
  v58 = *v14;
  v60 = -2147500000.0;
  v61 = (s32)v58;
  if (v58 == INFINITY)
    v61 = -2147500000.0;
  v62 = v58 - v61;
  v63 = v93[1].x;
  v64 = v62;
  _ZF = v62 == INFINITY;
  v65 = v93[0].y;
  if (_ZF)
    v64 = 0x80000000;
  v15[0] = v64;
  if (v65 != INFINITY)
    v60 = (s32)v65;
  v66 = v65 - v60;
  if (v66 == INFINITY)
    v67 = 0x80000000;
  else
    v67 = v66;
  v16[0] = v67;
  v68 = -2147500000.0;
  v69 = (s32)v63;
  if (v63 == INFINITY)
    v69 = -2147500000.0;
  v70 = v63 - v69;
  v71 = v93[2].x;
  v72 = v70;
  _ZF = v70 == INFINITY;
  v73 = v93[1].y;
  if (_ZF)
    v72 = 0x80000000;
  v91[9] = v72;
  if (v73 != INFINITY)
    v68 = (s32)v73;
  v74 = v73 - v68;
  if (v74 == INFINITY)
    v75 = 0x80000000;
  else
    v75 = v74;
  v16[1] = v75;
  v76 = -2147500000.0;
  v77 = (s32)v71;
  if (v71 == INFINITY)
    v77 = -2147500000.0;
  v78 = v71 - v77;
  v79 = v93[3].x;
  v80 = v78;
  _ZF = v78 == INFINITY;
  v81 = v93[2].y;
  if (_ZF)
    v80 = 0x80000000;
  v91[10] = v80;
  if (v81 != INFINITY)
    v76 = (s32)v81;
  v82 = v81 - v76;
  if (v82 == INFINITY)
    v83 = 0x80000000;
  else
    v83 = v82;
  v16[2] = v83;
  v84 = -2147500000.0;
  v85 = (s32)v79;
  if (v79 == INFINITY)
    v85 = -2147500000.0;
  v86 = v79 - v85;
  _ZF = v86 == INFINITY;
  v87 = v86;
  v88 = v93[3].y;
  if (_ZF)
    v87 = 0x80000000;
  v91[11] = v87;
  if (v88 != INFINITY)
    v84 = (s32)v88;
  v89 = v88 - v84;
  v90 = v89;
  if (v89 == INFINITY)
    v90 = 0x80000000;
  v16[3] = v90;
  v92[8] = a_col[0];
  v92[9] = a_col[0];
  v92[10] = a_col[1];
  v92[11] = a_col[1];
}

// 0x217d4f0
static void GetPosBezierCurve(f32 *a_px, f32 *a_py, s32 a_tx0, s32 a_ty0, s32 a_tx1, s32 a_ty1, s32 a_dx0, s32 a_dy0, s32 a_dx1, s32 a_dy1, f32 a_rate) {
  f32 v12;
  f32 v13;
  f32 v14;
  f32 v15;
  f32 v16;
  f32 v17;
  f32 v18;

  v12 = 0.0;
  if (a_rate >= 0.0)
  {
    v12 = 1.0;
    if (a_rate <= 1.0)
      v12 = a_rate;
  }
  v13 = 1.0 - v12;
  v14 = v12 * v12;
  v15 = v12 * (f32)(v12 * v12);
  v16 = v13 * (f32)(v13 * v13);
  v17 = v12 * (f32)((f32)(v13 * v13) * 3.0);
  v18 = v14 * (f32)(v13 * 3.0);
  *a_px = (f32)(v15 * (f32)a_tx1)
        + (f32)((f32)(v18 * (f32)a_dx1) + (f32)((f32)(v16 * (f32)a_tx0) + (f32)(v17 * (f32)a_dx0)));
  *a_py = (f32)(v15 * (f32)a_ty1)
        + (f32)((f32)(v18 * (f32)a_dy1) + (f32)((f32)(v16 * (f32)a_ty0) + (f32)(v17 * (f32)a_dy0)));
}

// 0x217d5b0
void shpDrawBezierCurveWide(s32 a_x0, s32 a_y0, s32 a_x1, s32 a_y1, s32 a_xt, s32 a_yt, u32 a_z, s32 a_div, s32 a_num, u32 a_col, f32 a_w) {
  u32 *v18;
  s32 v20;
  f32 v21;
  s32 v22;
  u32 *v23;
  f32 v24;
  s32 v25;
  s32 v26;
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
  f32 v41;
  f32 v42;
  f32 a_wb;
  f32 v46;

  v18 = NewSpecific(uint, 2u);
  if (a_div <= 1)
    v20 = 1;
  else
    v20 = a_div;
  v21 = a_x0;
  if (v20 >= a_num)
    v22 = a_num;
  else
    v22 = a_div;
  v23 = v18;
  v24 = a_y0;
  if (v22 <= 1)
    v25 = 1;
  else
    v25 = v22;
  v26 = 0;
  v27 = a_yt;
  v18[0] = a_col;
  v18[1] = a_col;
  v28 = v24;
  v46 = v20;
  v29 = 1.0;
  if (a_w >= 0.0)
    v29 = a_w;
  a_wb = v29;
  do
  {
    v41 = (f32)++v26 / v46;
    v42 = 0.0;
    if (v41 >= 0.0)
    {
      v42 = 1.0;
      if (v41 <= 1.0)
        v42 = (f32)v26 / v46;
    }
    v30 = v42 * v42;
    v31 = 1.0 - v42;
    v32 = v42 * (f32)(v42 * v42);
    v33 = v31 * (f32)(v31 * v31);
    v34 = (f32)(v31 * v31) * 3.0;
    v35 = (f32)(1.0 - v42) * 3.0;
    v36 = v42 * v34;
    v37 = v30 * v35;
    v38 = (f32)(v32 * (f32)a_x1)
        + (f32)((f32)(v37 * (f32)a_xt) + (f32)((f32)(v33 * (f32)a_x0) + (f32)(v36 * (f32)a_xt)));
    v39 = (f32)(v32 * (f32)a_y1) + (f32)((f32)(v37 * v27) + (f32)((f32)(v33 * v28) + (f32)(v36 * v27)));
    LineWide(v21, v24, v38, v39, (u32)shpDrawMisc, v23, a_wb);
    v21 = v38;
    v24 = v39;
  }
  while (v25 != v26);
}

// 0x217d7c0
void shpDrawStraightLineWide(sdfIVector2_t *a_pPos, u32 a_z, s32 a_div, s32 a_top, s32 a_num, u32 a_col, s32 a_alphaType, f32 a_w) {
  sdfVector4_t *v14;
  f32 *v15;
  u32 *v16;
  s32 v17;
  s32 v18;
  s32 v19;
  sdfIVector2_t m_Items;
  s32 v21;
  s32 v22;
  s32 v23;
  s32 Item;
  s64 v25;
  f32 v26;
  s64 v27;
  u64 v28;
  sdfVector4_t *v29;
  s64 v30;
  f32 v31;
  s32 v32;
  s32 v33;
  s32 v34;
  s32 v35;
  f32 *p_x;
  f32 x;
  f32 y;
  f32 z;
  f32 v46;
  s32 v47;
  int32x2_t v48;
  f32 v49;
  signed s32 v50;
  s32 v51;
  s32 v53;
  s32 v54;
  s32 v56;
  f32 *v60;
  f32 v61;
  f32 v62;
  f32 v63;
  f32 v65;
  s32 v67;
  s32 v68;
  struct sdfVector4_t v71;
  f32 v75;
  f32 v76;
  int32x2_t v77;
  float32x2_t v78;
  int8x8_t v79;
  int8x8_t v80;
  sdfIVector2_t v82;
  s32 v83;
  int32x2_t v84;
  int32x2_t v85;
  f32 v86;
  s32 v88;
  signed s32 v89;
  u32 *a_cola;
  s64 v91;
  struct sdfVector4_t v93;
  u64 v96;
  f32 v97;

  v14 = NewSpecific(sdfVector4_t, 4u);
  v15 = NewSpecific(f32, 4u);
  v16 = NewSpecific(uint, 2u);
  *(u64 *)&v16[0] = 0;
  a_cola = v16;
  *(u64 *)(NewSpecific(f32, 2u) + 32) = 0;
  if (!a_pPos || a_num < 0)
    return;
  v17 = -1;
  if (a_div <= 1)
    v18 = 1;
  else
    v18 = a_div;
  if (v18 >= a_top)
    v19 = a_top;
  else
    v19 = a_div;
  m_Items = (sdfIVector2_t)a_pPos;
  a_cola[0] = a_col;
  a_cola[1] = a_col;
  if (v19 <= 1)
    v21 = 1;
  else
    v21 = v19;
  if ((u32)a_num <= 1)
    v22 = 1;
  else
    v22 = a_num;
  if (v18 >= (u32)a_num)
    v23 = v22;
  else
    v23 = v18;
  do
  {
    Item = get_Item((sdfIVector2_t)(*(u64 *)&m_Items + 8 * (v17 + 2)), 0, 0);
    ++v17;
  }
  while ((Item & 0x80000000) == 0);
  if (a_w <= 0.0)
    a_w = 1.0;
  if (v17 < 1)
    return;
  if ((u32)v17 >= 4)
    v25 = 4;
  else
    v25 = v17;
  v88 = v23;
  v96 = v25;
  v26 = 0.0;
  v27 = 0x3DCCCCCD00000000LL;
  v83 = v21;
  v91 = v14;
  v28 = 0;
  v29 = &v14[0];
  v30 = &v15[0];
  v82 = (sdfIVector2_t)a_pPos;
  do
  {
    v32 = get_Item(m_Items, 0, 0);
    v33 = get_Item(m_Items, 1, 0);
    v34 = get_Item((sdfIVector2_t)(*(u64 *)&m_Items + 8), 0, 0);
    v35 = get_Item((sdfIVector2_t)(*(u64 *)&m_Items + 8), 1, 0);
    *(u64 *)&vct_A.z = 0x3DCCCCCD00000000LL;
    vct_A.x = (f32)v34;
    vct_A.y = (f32)v35;
    *(u64 *)&vct_B.z = 0x3F80000000000000LL;
    vct_B.x = (f32)v32;
    vct_B.y = (f32)v33;
    vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    p_x = &vf00.x;
    x = p_x[4];
    y = p_x[5];
    z = p_x[6];
    *(f32 *)(v30 + 4 * v28) = sqrtf((f32)((f32)(x * x) + (f32)(y * y)) + (f32)(z * z));
    sub_1949110(0);
    *(u64 *)&m_Items += 8;
    *v29++ = vct_A;
    v31 = *(f32 *)(v30 + 4 * v28++);
    v26 = v26 + v31;
  }
  while (v28 < v96);
  if (v26 > 0.0)
  {
    v86 = (u8)a_col;
    v97 = v26 / (f32)v18;
    v46 = get_Item(v82, 0, 0);
    v47 = get_Item(v82, 1, 0);
    v48.n64_f32[0] = (f32)v83;
    v49 = v47;
    v50 = 0;
    v51 = 0;
    v89 = v83 + ~v88;
    v84.n64_u64[0] = vdup_lane_s32(v48, 0).n64_u64[0];
    v85.n64_u64[0] = vdup_n_s32(a_col & 0xFFFFFF00).n64_u64[0];
    do
    {
      v53 = v51 + 1;
      v54 = get_Item((sdfIVector2_t)(*(u64 *)&v82 + 8 * (v51 + 1)), 0, 0);
      v56 = get_Item((sdfIVector2_t)(*(u64 *)&v82 + 8 * (v51 + 1)), 1, 0);
      *(u64 *)&vct_A.z = v27;
      vct_A.x = (f32)v54;
      vct_A.y = (f32)v56;
      vct_B.x = v46;
      vct_B.y = v49;
      *(u64 *)&vct_B.z = 0x3F80000000000000LL;
      vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
      v60 = &vf00.x;
      v61 = v60[4];
      v62 = v60[5];
      v63 = v60[6];
      v65 = sqrtf((f32)((f32)(v61 * v61) + (f32)(v62 * v62)) + (f32)(v63 * v63));
      if (v65 <= v97)
        goto LABEL_59;
      v93 = *(sdfVector4_t *)(v91 + 16 * v51 + 32);
      vct_A = v93;
      vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v97);
      vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
      if (v50 >= v89)
      {
        v75 = vct_A.x;
        v76 = vct_A.y;
        v27 = *(u64 *)&vct_A.z;
        if (a_alphaType == 1)
        {
          v77.n64_u32[0] = v50;
          v77.n64_u32[1] = v50 + 1;
          v78.n64_u64[0] = vdiv_f32(vmul_n_f32(vcvt_f32_s32(v77), v86), v84).n64_u64[0];
          v79.n64_u64[0] = vcltz_f32(v78).n64_u64[0];
          v80.n64_u64[0] = vcvt_s32_f32(v78).n64_u64[0];
          *(int8x8_t *)a_cola = vorr_s8(v85, vand_s8(vbsl_s8(v79, v80, v80), (int8x8_t)0xFF000000FFLL));
        }
        LineWide(v46, v49, v75, v76, (u32)shpDrawMisc, a_cola, a_w);
        goto LABEL_59;
      }
      v67 = get_Item((sdfIVector2_t)(*(u64 *)&v82 + 8 * v53), 0, 0);
      v68 = get_Item((sdfIVector2_t)(*(u64 *)&v82 + 8 * v53), 1, 0);
      *(u64 *)&vct_B.z = 0x3F80000000000000LL;
      vct_B.x = (f32)v67;
      vct_B.y = (f32)v68;
      v71 = *(sdfVector4_t *)(v91 + 16 * v53 + 32);
      vct_A = v71;
      vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v97 - v65);
      vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
      v51 = v53;
      v27 = *(u64 *)&vct_A.z;
      v46 = vct_A.x;
      v49 = vct_A.y;
LABEL_59:
      ++v50;
    }
    while (v83 != v50);
  }
}

// 0x217e340
void shpDrawParticleDiffusion(s32 a_x, s32 a_y, u32 a_z, u32 a_col, f32 a_w, s32 a_cnt) {
  s64 j;
  f32 *v13;
  f32 v14;
  s64 v15;
  s64 v16;
  f32 v17;
  s64 i;
  s64 v20;
  s16 v25;
  char *v26;

  if (!a_cnt)
  {
    v17 = a_x;
    for (i = 0; i != 128; ++i)
    {
      v20 = i;
      gPosX[i] = v17;
      gPosY[i] = (f32)a_y;
      gVecX[v20] = (f32)((f32)((u32)sub_1905740(30, 0) + 1) * 0.1) + -1.5;
      gVecY[v20] = (f32)((f32)((u32)sub_1905740(30, 0) + 1) * 0.1) + -1.5;
      v25 = sub_1905740(16, 0);
      v26 = (char *)gFrame + 2 * i;
      *((u16 *)v26 + 16) = v25 + 1;
    }
  }
  for (j = 0; j != 128; ++j)
  {
    if (gFrame[j] <= a_cnt)
      continue;
    v13 = gVecY;
    v14 = gVecX[j];
    v15 = (s64)gPosX + 4 * j;
    v16 = (s64)gPosY + 4 * j;
    *(f32 *)(v15 + 32) = *(f32 *)(v15 + 32) + v14;
    *(f32 *)(v16 + 32) = *(f32 *)(v16 + 32) + v13[j];
  }
}

// 0x217e540
static void _BreakLineWide(f32 *a_x, f32 *a_y, u32 a_z, u32 *a_col, f32 a_w, s32 a_cnt) {
  s32 *v10;
  s64 v11;
  s32 *v12;
  s64 v14;
  f32 *v15;
  s64 v16;
  f32 v17;
  f32 *v18;
  f32 *gPosX_local;
  f32 v20;
  f32 v21;
  f32 v22;
  f32 v23;
  bool v24;
  s32 v25;
  f32 v26;
  f32 v27;
  s32 v28;
  s32 v29;
  s32 v30;
  f32 v32;
  f32 v33;
  f32 v34;
  f32 v35;
  f32 *p_x;
  f32 z;
  f32 x;
  f32 y;
  f32 v44;
  f32 v45;
  f32 v47;
  f32 v48;
  f32 *v49;
  f32 v51;
  f32 v52;
  f32 v53;
  f32 v54;
  f32 v55;
  s32 v56;
  f32 *v61;
  float32x4_t *v62;
  f32 v66;
  f32 v67;
  s32 v71;
  u32 v74;
  f32 v76;
  f32 *v79;
  s64 v80;
  s64 v82;
  f32 *v83;
  f32 *v84;
  s32 v85;
  f32 *v87;
  f32 v91;
  f32 v92;

  v10 = NewSpecific(s32, 4u);
  *(u64 *)&v10[0] = 0;
  *(u64 *)&v10[2] = 0;
  v11 = v10;
  v12 = NewSpecific(s32, 4u);
  *(u64 *)&v12[0] = 0;
  *(u64 *)&v12[2] = 0;
  if (a_cnt)
  {
    goto LABEL_5;
  }
  v33 = a_x[0];
  v32 = a_x[1];
  v35 = a_y[0];
  v34 = a_y[1];
  vct_A.x = v32;
  vct_A.y = v34;
  *(u64 *)&vct_A.z = 0x3F80000000000000LL;
  vct_B.x = v33;
  vct_B.y = v35;
  *(u64 *)&vct_B.z = 0x3F80000000000000LL;
  vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  p_x = &vf00.x;
  z = p_x[6];
  x = p_x[4];
  y = p_x[5];
  v44 = z * z;
  v45 = (f32)(x * x) + (f32)(y * y);
  sub_1949110(0);
  v47 = v45 + v44;
  v48 = sqrtf(v47);
  v49 = &vf00.x;
  v51 = v49[4];
  v52 = v49[5];
  v53 = v49[6];
  v54 = v49[7];
  v55 = v48 / (f32)(a_w + a_w);
  if (v55 == INFINITY)
    v56 = 0x80000000;
  else
    v56 = v55;
  gBreakNum = v56;
  if (v56 >= 129)
  {
    gBreakNum = 128;
LABEL_41:
    goto LABEL_42;
  }
  goto LABEL_41;
LABEL_42:
  vct_A.x = v33;
  vct_A.y = v35;
  *(u64 *)&vct_A.z = 0x3F80000000000000LL;
  v61 = &vf00.x;
  v61[8] = v51;
  v61[9] = v52;
  v61[10] = v53;
  v61[11] = v54;
  v62[2] = vmulq_n_f32(v62[2], a_w);
  if (gBreakNum >= 1)
  {
    vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    v66 = vct_A.x;
    v67 = vct_A.y;
    gPosX[0] = v66;
    gPosY[0] = v67;
    v71 = sub_1905740(20, 0);
    gVecX[0] = (f32)((f32)(u32)(v71 + 1) * 0.1) + -1.0;
    v74 = sub_1905740(20, 0) + 1;
    v76 = (f32)v74 * 0.1;
    gVecY[0] = v76 + -1.0;
    v79 = &vf00.x;
    v79[8] = v51;
    v79[9] = v52;
    v79[10] = v53;
    v79[11] = v54;
LABEL_61:
    v80 = 9;
    vct_B = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_B, a_w + a_w);
    while (1)
    {
      if (v80 - 8 >= gBreakNum)
        goto LABEL_5;
      vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
      v91 = vct_A.x;
      v92 = vct_A.y;
      v82 = 4 * v80;
      v83 = gPosY;
      v84 = gVecX;
      *(f32 *)((char *)&gPosX->obj.klass + v82) = v91;
      *(f32 *)((char *)&v83->obj.klass + v82) = v92;
      v85 = sub_1905740(20, 0);
      *((f32 *)&v84->obj.klass + v80) = (f32)((f32)(u32)(v85 + 1) * 0.1) + -1.0;
      v87 = gVecY;
      ++v80;
      *(f32 *)((char *)&v87->obj.klass + v82) = (f32)((f32)((u32)sub_1905740(20, 0) + 1) * 0.1)
                                                + -1.0;
    }
    goto LABEL_61;
  }
LABEL_5:
  v14 = 8;
  while (1)
  {
    if (v14 - 8 >= gBreakNum)
      break;
    v15 = gVecY;
    v16 = 4 * v14++;
    v17 = *(f32 *)((char *)&gVecX->obj.klass + v16);
    gPosX_local = gPosX;
    v18 = gPosY;
    *(f32 *)((char *)&gPosX_local->obj.klass + v16) = *(f32 *)((char *)&gPosX_local->obj.klass + v16) + v17;
    v20 = *(f32 *)((char *)&v18->obj.klass + v16) + *(f32 *)((char *)&v15->obj.klass + v16);
    *(f32 *)((char *)&v18->obj.klass + v16) = v20;
    v21 = *(f32 *)((char *)&gPosX_local->obj.klass + v16);
    v22 = v21 - a_w;
    v23 = v21 + a_w;
    v24 = v22 == INFINITY;
    v25 = v22;
    v26 = v20 - a_w;
    v27 = v20 + a_w;
    if (v24)
      v25 = 0x80000000;
    *(u32 *)(v11 + 32) = v25;
    v28 = v26;
    if (v26 == INFINITY)
      v28 = 0x80000000;
    v12[0] = v28;
    v29 = v23;
    if (v23 == INFINITY)
      v29 = 0x80000000;
    *(u32 *)(v11 + 36) = v29;
    v30 = v27;
    if (v27 == INFINITY)
      v30 = 0x80000000;
    v12[1] = v30;
  }
}

// 0x217eed0
void shpDrawStraightBreakLineWide(sdfIVector2_t *a_pPos, u32 a_z, s32 a_div, s32 a_top, s32 a_num, u32 a_col, f32 a_w) {
  u32 *v13;
  s64 v14;
  f32 *v15;
  f32 *v16;
  f32 *v17;
  s32 v18;
  s32 Item;
  u32 v20;
  u32 v21;
  u32 *v22;
  s32 v24;
  sdfIVector2_t v25;

  v13 = NewSpecific(uint, 2u);
  *(u64 *)&v13[0] = 0;
  v14 = v13;
  v15 = NewSpecific(f32, 2u);
  *(u64 *)&v15[0] = 0;
  v16 = NewSpecific(f32, 2u);
  *(u64 *)&v16[0] = 0;
  if (a_pPos)
  {
    if ((a_num & 0x80000000) == 0)
    {
      v17 = v16;
      *(u32 *)(v14 + 32) = a_col;
      *(u32 *)(v14 + 36) = a_col;
      v18 = -1;
      do
      {
        Item = get_Item((sdfIVector2_t)&a_pPos[v18 + 2], 0, 0);
        ++v18;
      }
      while ((Item & 0x80000000) == 0);
      if (v18 >= 1)
      {
        if ((u32)v18 >= 4)
          v20 = 4;
        else
          v20 = v18;
        v15[0] = (f32)get_Item((sdfIVector2_t)a_pPos, 0, 0);
        v17[0] = (f32)get_Item((sdfIVector2_t)a_pPos, 1, 0);
        v15[1] = (f32)get_Item((sdfIVector2_t)&a_pPos[1], 0, 0);
        v17[1] = (f32)get_Item((sdfIVector2_t)&a_pPos[1], 1, 0);
        _BreakLineWide(v15, v17, v21, v22, a_w, a_top);
        if (v20 >= 2)
        {
          v15[0] = (f32)get_Item((sdfIVector2_t)&a_pPos[1], 0, 0);
          v17[0] = (f32)get_Item((sdfIVector2_t)&a_pPos[1], 1, 0);
          v15[1] = (f32)get_Item((sdfIVector2_t)&a_pPos[2], 0, 0);
          v17[1] = (f32)get_Item((sdfIVector2_t)&a_pPos[2], 1, 0);
          if (v20 >= 3)
          {
            v15[0] = (f32)get_Item((sdfIVector2_t)&a_pPos[2], 0, 0);
            v17[0] = (f32)get_Item((sdfIVector2_t)&a_pPos[2], 1, 0);
            v15[1] = (f32)get_Item((sdfIVector2_t)&a_pPos[3], 0, 0);
            v17[1] = (f32)get_Item((sdfIVector2_t)&a_pPos[3], 1, 0);
            if (v20 != 3)
            {
              v15[0] = (f32)get_Item((sdfIVector2_t)&a_pPos[3], 0, 0);
              v24 = get_Item((sdfIVector2_t)&a_pPos[3], 1, 0);
              v25 = (sdfIVector2_t)&a_pPos[4];
              v17[0] = (f32)v24;
              v15[1] = (f32)get_Item(v25, 0, 0);
              v17[1] = (f32)get_Item(v25, 1, 0);
            }
          }
        }
      }
    }
  }
}
