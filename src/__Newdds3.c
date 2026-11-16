#include "types.h"
#include "__newdds3.h"
#include "dds3kerneldraw.h"
#include "sdf_vu0.h"

typedef struct __BTLCAM_QUAKEWORK __BTLCAM_QUAKEWORK;

bool Newdds3_QuakeID;
__BTLCAM_QUAKEWORK *btlqwk;

static void __BtlCAM_QuakeProc(void);
static void __BtlCAM_QuakeExit(void);

// 0x22a0f90
bool SetQuake(s32 frame, s16 range, s32 fadeintime, s32 fadeouttime) {
  Il2CppObject *v9;
  s32 v12;
  f32 z;

  if (range)
  {
    if (Newdds3_QuakeID)
      __BtlCAM_QuakeExit();
    v9 = Allocate(__BTLCAM_QUAKEWORK);
    _ctor(v9, 0);
    btlqwk = (__BTLCAM_QUAKEWORK *)v9;
    if (frame)
      v12 = frame;
    else
      v12 = -1;
    btlqwk[3].n64_u32[1] = fadeouttime;
    btlqwk[2].n64_u32[1] = v12;
    btlqwk[3].n64_u32[0] = fadeintime;
    z = oneVector.z;
    btlqwk[4].n64_u64[0] = vmul_n_f32(*(float32x2_t *)&oneVector.x, (f32)range).n64_u64[0];
    btlqwk[5].n64_f32[0] = z * (f32)range;
    Newdds3_QuakeID = 1;
  }
  return range != 0;
}

// 0x22a12e0
bool QuakeRun(void) {
  s32 frame_rate;

  if (!Newdds3_QuakeID)
    return Newdds3_QuakeID;
  frame_rate = btlqwk->frame_rate;
  if (frame_rate == -1 || frame_rate > btlqwk->frame_cnt)
  {
    __BtlCAM_QuakeProc();
    return Newdds3_QuakeID;
  }
  __BtlCAM_QuakeExit();
  return Newdds3_QuakeID;
}

// 0x22a1370
static void __BtlCAM_QuakeProc(void) {
  s64 v1;
  f32 y;
  f32 x;
  f32 z;
  u32 status;
  s32 v7;
  s32 frame_cnt;
  f32 fadein_time;
  f32 v10;
  f32 v11;
  s32 frame_rate;
  s32 v13;
  f32 v14;
  s64 v15;
  f32 v16;
  s32 v17;
  f32 v18;
  s32 v19;
  f32 v20;
  f32 v22;
  s64 v23;
  f32 v24;
  s32 v25;
  f32 v26;
  s32 v27;
  f32 v28;
  f32 v31;
  f32 v32;
  s32 v33;
  f32 v34;
  s32 v35;
  f32 v36;
  f32 v38;
  __BTLCAM_QUAKEWORK *v39;
  f32 v40;

  x = btlqwk->range.x;
  y = btlqwk->range.y;
  z = btlqwk->range.z;
  status = btlqwk->status;
  if (status == 2)
  {
    v10 = (btlqwk->frame_rate - btlqwk->frame_cnt);
    fadein_time = btlqwk->fadein_time;
    goto LABEL_9;
  }
  if (status == 1)
  {
    frame_rate = btlqwk->frame_rate;
    if (frame_rate == -1 || frame_rate - btlqwk->fadeout_time > btlqwk->frame_cnt)
      goto LABEL_15;
    v13 = 2;
  }
  else
  {
    if (status)
      goto LABEL_15;
    v7 = btlqwk->fadein_time;
    frame_cnt = btlqwk->frame_cnt;
    if (v7 > frame_cnt)
    {
      fadein_time = v7;
      v10 = (frame_cnt + 1);
LABEL_9:
      v11 = v10 / fadein_time;
      x = x * v11;
      y = y * v11;
      z = z * v11;
      goto LABEL_15;
    }
    v13 = 1;
  }
  btlqwk->status = v13;
LABEL_15:
  if ((btlqwk->frame_cnt & 1) != 0)
    v14 = 1.0;
  else
    v14 = -1.0;
  v16 = sub_1B34D00(0, v1);
  v17 = (f32)(x * 100.0);
  if ((f32)(x * 100.0) == INFINITY)
    v17 = 0x80000000;
  if (v17)
  {
    v18 = v16 * 100.0;
    if (v18 == INFINITY)
      v19 = 0x80000000;
    else
      v19 = v18;
    v20 = (v19 % v17);
  }
  else
  {
    v20 = 0.0;
  }
  if (fabsf((f32)((f32)(v14 * v20) * 0.1) + CameraOffset.x) >= x)
    v22 = v14 * x;
  else
    v22 = (f32)((f32)(v14 * v20) * 0.1) + CameraOffset.x;
  CameraOffset.x = v22;
  v24 = sub_1B34D00(0, v15);
  v25 = (f32)(y * 100.0);
  if ((f32)(y * 100.0) == INFINITY)
    v25 = 0x80000000;
  if (v25)
  {
    v26 = v24 * 100.0;
    if (v26 == INFINITY)
      v27 = 0x80000000;
    else
      v27 = v26;
    v28 = (v27 % v25);
  }
  else
  {
    v28 = 0.0;
  }
  if (fabsf((f32)((f32)(v14 * v28) * 0.1) + CameraOffset.y) >= y)
    v31 = v14 * y;
  else
    v31 = (f32)((f32)(v14 * v28) * 0.1) + CameraOffset.y;
  if ((DrawFlag & 0x20000000) == 0)
  {
    if ((f32)(v31 + CameraTargetPos.y) > -11.0)
      v31 = 0.0;
  }
  CameraOffset.y = v31;
  v32 = sub_1B34D00(0, v23);
  v33 = (f32)(z * 100.0);
  if ((f32)(z * 100.0) == INFINITY)
    v33 = 0x80000000;
  if (v33)
  {
    v34 = v32 * 100.0;
    if (v34 == INFINITY)
      v35 = 0x80000000;
    else
      v35 = v34;
    v36 = (v35 % v33);
LABEL_64:
    v38 = CameraOffset.z;
    goto LABEL_65;
  }
  else
  {
    v36 = 0.0;
    goto LABEL_64;
  }
  v38 = CameraOffset.z;
LABEL_65:
  v39 = btlqwk;
  v40 = (f32)((f32)(v14 * v36) * 0.1) + v38;
  if (fabsf(v40) >= z)
    v40 = v14 * z;
  CameraOffset.z = v40;
  ++v39->frame_cnt;
}

// 0x22a17b0
void QuakeEnd(void) {
  __BtlCAM_QuakeExit();
}

// 0x22a10d0
static void __BtlCAM_QuakeExit(void) {
  sdfVector4_t *p_CameraOffset;

  if (Newdds3_QuakeID)
  {
    btlqwk = 0;
    Newdds3_QuakeID = 0;
    vct_A = vf00;
    vct_A.w = 0.0;
    p_CameraOffset = &CameraOffset;
    *p_CameraOffset = vct_A;
    return;
  }
}
