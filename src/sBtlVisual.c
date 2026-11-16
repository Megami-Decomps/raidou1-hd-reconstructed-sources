#include "types.h"
#include "MODELTYPE.h"
#include "fld.h"
#include "sbtl.h"
#include "sbtlmain.h"
#include "sbtlplayer.h"
#include "sbtlplayer_sddash.h"
#include "sbtlplayertbl.h"
#include "sbtlsub.h"
#include "sbtlvisual.h"
#include "sdf_vu0.h"
#include "sdfquat.h"

typedef struct MOTIONDATA_WORK MOTIONDATA_WORK;
typedef struct MOTIONMOVE_WORK MOTIONMOVE_WORK;
typedef struct SBTLUNIT_WORK SBTLUNIT_WORK;
typedef struct SBTLVISUAL_DATA SBTLVISUAL_DATA;
typedef struct VISUALDATA_WORK VISUALDATA_WORK;
typedef struct V_POSITION_WORK V_POSITION_WORK;

static VISUALDATA_WORK *sbtlvisual_tbldata_z[2];
V_POSITION_WORK *sbtleff_cylindertbl;
MOTIONMOVE_WORK *sbtlmotionmv_tbldata;
V_POSITION_WORK *sbtleff_cylindertbl_p;
static sdfVector4_t _rot;

// 0x2131aa0
MOTIONMOVE_WORK *sBtlGetMotionMoveData(MODELTYPE major, s32 minor) {
  MOTIONMOVE_WORK **p_sbtlmotionmv_tbldata;

  if (major)
  {
    p_sbtlmotionmv_tbldata = &sbtlmotionmv_tbldata;
  }
  else
  {
    p_sbtlmotionmv_tbldata = &sbtlmotionmove_tbldata_player;
  }
  return (*p_sbtlmotionmv_tbldata)[minor];
}

// 0x2131b60
f32 sBtlGetMotionMove(SBTLUNIT_WORK *wk, f32 now_frame) {
  s32 major;
  s64 minor;
  f32 v9;
  MOTIONMOVE_WORK *v10;
  f32 v12;
  s32 hstatus;
  MTIONMV_PARA *para;
  s64 max_length;
  s16 **i;
  s16 *v18;
  f32 JumpMoveSpeed;

  major = wk->major;
  minor = wk->minor;
  if (!major)
  {
    v9 = 0.0;
    v10 = sbtlmotionmove_tbldata_player[minor];
    if (!v10)
      return v9;
    goto LABEL_15;
  }
  v9 = 0.0;
  v10 = sbtlmotionmv_tbldata[minor];
  if (!v10)
    return v9;
LABEL_15:
  v12 = 1.0;
  if (!!IsSceanStop())
  {
    if ((wk->status & 0x10) == 0)
    {
      if ((wk->side & 0x80) == 0 || !sBtlIsSetsumaPadStop())
        return v9;
      if ((wk->mode & 0xFFFFFFFE) != 0xE)
        return v9;
      v12 = 0.05;
    }
  }
  if (wk->actwk->status == 9 || wk->motStopCnt || (wk->hstatus & 0x4000) != 0)
    return v9;
  if (sBtlChkSpace(wk))
    return v9;
  hstatus = wk->hstatus;
  if ((hstatus & 0x40000) != 0)
    v12 = 0.5;
  if ((hstatus & 0x80000) != 0)
  {
    JumpMoveSpeed = sBtlGetJumpMoveSpeed(wk);
    return v12 * JumpMoveSpeed;
  }
  if ((hstatus & 0x4000) != 0)
    return v9;
  if ((hstatus & 0x4000000) == 0)
  {
    para = v10->para;
    if ((s32)para->max_length >= 1)
    {
      max_length = (u32)para->max_length;
      for (i = para; ; ++i)
      {
        v18 = *i;
        if (wk->next_motionno == (*i)[8] && (f32)v18[9] <= now_frame && (f32)v18[10] >= now_frame)
          break;
        if (!--max_length)
          return v9;
      }
      JumpMoveSpeed = v18[11];
      return v12 * JumpMoveSpeed;
    }
    return v9;
  }
  return sBtlPlayerGetMoveSdDash(wk);
}

// 0x2131ea0
V_POSITION_WORK *sBtlGetEffCylinderData(MODELTYPE major, s32 id) {
  V_POSITION_WORK **p_sbtleff_cylindertbl;

  if (major)
  {
    p_sbtleff_cylindertbl = &sbtleff_cylindertbl;
  }
  else
  {
    p_sbtleff_cylindertbl = &sbtleff_cylindertbl_p;
  }
  return (*p_sbtleff_cylindertbl)[id];
}

// 0x2131f40
VISUALDATA_WORK *sBtlGetVisualData(MODELTYPE major, s32 id) {
  if (major)
  {
    return sBtlGetVisualDataZ(id);
  }
  else
  {
    return sbtlvisual_tbldata_player[id];
  }
}

// 0x2132010
VISUALDATA_WORK *sBtlGetVisualDataZ(s32 id) {
  s32 nowKiretsuIdx;
  s32 v4;
  s32 v5;
  s32 v6;
  _BOOL4 v10;

  nowKiretsuIdx = fldGb->nowKiretsuIdx;
  v4 = nowKiretsuIdx;
  v5 = nowKiretsuIdx;
  v6 = nowKiretsuIdx;
  v10 = (u32)(id - 400) < 0xFFFFFFC0 && (u32)(id - 76) < 0xFFFFFFB5 && id < 496;
  if (v6 != 53 && nowKiretsuIdx != 52 && v5 != 51 && v4 != 50)
    v10 = 0;
  return sbtlvisual_tbldata_z[v10][id];
}

// 0x21321d0
void sBtlSetVisualDataZInit(s32 index, void *tbl) {
  VISUALDATA_WORK **sbtlvisual_tbldata_z_local;
  s32 Length;
  Il2CppClass *v8;
  Il2CppClass *v9;
  Il2CppClass **v10;
  s32 v11;
  s64 v12;
  s64 v13;
  s64 v14;
  s64 i;
  VISUALDATA_WORK *v17;
  VISUALDATA_WORK *DEVILVISUALTBL;
  VISUALDATA_WORK *v19;
  VISUALDATA_WORK **v21;

  if (index)
  {
    goto LABEL_4;
  }
  v21 = NewSpecific(Project_VISUALDATA_WORK__, 2u);
  sbtlvisual_tbldata_z = v21;
LABEL_4:
  sbtlvisual_tbldata_z_local = sbtlvisual_tbldata_z;
  Length = GetLength(tbl, 0);
  v8 = NewSpecific(VISUALDATA_WORK, Length);
  v9 = v8;
  v10 = &sbtlvisual_tbldata_z_local->obj.klass + index;
  v10[4] = v9;
  v11 = GetLength(tbl, 0);
  if (v11 >= 1)
  {
    v12 = 0;
    v13 = index;
    v14 = v11;
    for (i = 32; ; i += 8)
    {
      v17 = sbtlvisual_tbldata_z[v13];
      DEVILVISUALTBL = GetDEVILVISUALTBL(tbl, v12, 0);
      v19 = DEVILVISUALTBL;
      if (DEVILVISUALTBL)
      {
          break;
      }
      *(Il2CppClass **)((char *)&v17->obj.klass + i) = v19;
      if (v14 == ++v12)
        return;
    }
  }
}

// 0x21323c0
VISUALDATA_WORK *sBtlGetVisualData_P(MODELTYPE major, s32 id) {
  if (major)
  {
    return sBtlGetVisualDataZ(id);
  }
  else
  {
    return sbtlvisual_tbldata_player[id];
  }
}

// 0x2132490
MOTIONDATA_WORK *sBtlGetMotionVisualData(MODELTYPE major, s32 id1, s32 id2) {
  VISUALDATA_WORK *VisualDataZ;

  if (major)
  {
    VisualDataZ = sBtlGetVisualDataZ(id1);
  }
  else
  {
    VisualDataZ = sbtlvisual_tbldata_player[id1];
  }
  return VisualDataZ->mwk[id2];
}

// 0x2132550
bool sBtlCheckMotionTiming(SBTLUNIT_WORK *wk) {
  s32 major;
  s64 minor;
  s64 next_motionno;
  VISUALDATA_WORK *VisualDataZ;

  major = wk->major;
  minor = wk->minor;
  next_motionno = wk->next_motionno;
  if (major)
  {
    VisualDataZ = sBtlGetVisualDataZ(minor);
    return (VisualDataZ->mwk[next_motionno]->flg & 2) == 0;
  }
  VisualDataZ = sbtlvisual_tbldata_player[minor];
  return (VisualDataZ->mwk[next_motionno]->flg & 2) == 0;
}

// 0x2132680
f32 sBtlGetActionTime(SBTLUNIT_WORK *wk, s32 flg) {
  s64 minor;
  VISUALDATA_WORK *VisualDataZ;
  s64 next_motionno;
  MOTIONDATA_WORK *v10;
  f32 v11;
  f32 *p_e_startrate;
  VISUALDATA_WORK *v14;
  MOTIONDATA_WORK *v15;
  f32 *p_m_stoprate;
  u16 v17;
  f32 *p_m_speed;
  f32 m_speed;
  f32 result;
  sdatUnitWork_t *para;
  s32 devilid;

  minor = wk->minor;
  if (!wk->major)
  {
    v14 = sbtlvisual_tbldata_player[minor];
    next_motionno = wk->next_motionno;
    v15 = v14->mwk[next_motionno];
    if (flg == 1)
    {
      p_m_stoprate = &v15->m_stoprate;
    }
    else
    {
      v11 = 0.0;
      if (flg)
        goto LABEL_30;
      p_m_stoprate = &v15->e_startrate;
    }
    v11 = *p_m_stoprate + (f32)wk->beforeframe;
LABEL_30:
    if ((v15->flg & 1) != 0)
    {
      m_speed = v15->m_speed;
      result = 0.0;
      if (m_speed <= 0.0)
        return result;
    }
    else
    {
      m_speed = v14->m_speed;
      result = 0.0;
      if (m_speed <= 0.0)
        return result;
    }
    goto LABEL_34;
  }
  VisualDataZ = sBtlGetVisualDataZ(minor);
  next_motionno = wk->next_motionno;
  v10 = VisualDataZ->mwk[next_motionno];
  if (flg == 1)
  {
    p_e_startrate = &v10->m_stoprate;
  }
  else
  {
    v11 = 0.0;
    if (flg)
      goto LABEL_21;
    p_e_startrate = &v10->e_startrate;
  }
  v11 = *p_e_startrate + (f32)wk->beforeframe;
LABEL_21:
  v17 = v10->flg;
  p_m_speed = &v10->m_speed;
  if ((v17 & 1) == 0)
    p_m_speed = &VisualDataZ->m_speed;
  m_speed = *p_m_speed;
  result = 0.0;
  if (*p_m_speed > 0.0)
  {
LABEL_34:
    result = v11 / m_speed;
    para = wk->para;
    if (para)
    {
      devilid = (u16)para->devilid;
      if ((devilid == 433 || devilid == 369) && (u32)next_motionno == 15)
        return result * 0.5;
    }
  }
  return result;
}

// 0x21328f0
f32 sBtlGetSETime(SBTLUNIT_WORK *wk, s32 motionID) {
  s64 minor;
  VISUALDATA_WORK *VisualDataZ;
  MOTIONDATA_WORK *v9;
  s32 se_rate;
  u16 flg;
  f32 *p_m_speed;
  f32 v13;
  f32 m_speed;
  f32 result;
  VISUALDATA_WORK *v17;
  MOTIONDATA_WORK *v18;

  minor = wk->minor;
  if (!wk->major)
  {
    v17 = sbtlvisual_tbldata_player[minor];
    v18 = v17->mwk[motionID];
    v13 = (f32)v18->se_rate + (f32)wk->beforeframe;
    if ((v18->flg & 1) != 0)
    {
      m_speed = v18->m_speed;
      result = 0.0;
      if (m_speed <= 0.0)
        return result;
    }
    else
    {
      m_speed = v17->m_speed;
      result = 0.0;
      if (m_speed <= 0.0)
        return result;
    }
    return v13 / m_speed;
  }
  VisualDataZ = sBtlGetVisualDataZ(minor);
  v9 = VisualDataZ->mwk[motionID];
  se_rate = v9->se_rate;
  flg = v9->flg;
  p_m_speed = &v9->m_speed;
  if ((flg & 1) == 0)
    p_m_speed = &VisualDataZ->m_speed;
  v13 = (f32)se_rate + (f32)wk->beforeframe;
  m_speed = *p_m_speed;
  result = 0.0;
  if (*p_m_speed > 0.0)
    return v13 / m_speed;
  return result;
}

// 0x2132af0
void sBtlGetBouncePow(SBTLUNIT_WORK *wk, f32 *_Pow, s32 *_Rebound) {
  s32 minor;
  VISUALDATA_WORK *VisualDataZ;
  MOTIONDATA_WORK *v10;
  f32 cancelrate;
  f32 v12;
  s32 v13;

  if (!wk->major)
  {
    *Pow = 0.0;
    *Rebound = 0;
    return;
  }
  minor = wk->minor;
  VisualDataZ = sBtlGetVisualDataZ(minor);
  v10 = VisualDataZ->mwk[3];
  cancelrate = VisualDataZ->mwk[4]->cancelrate;
  *Pow = cancelrate;
  v12 = v10->cancelrate;
  v13 = v12;
  if (v12 == INFINITY)
    v13 = 0x80000000;
  *Rebound = v13;
  if (cancelrate <= 1.0)
    *Pow = 0.0;
}

// 0x2132c30
bool sBtlGetCylinderData_ID(MODELTYPE major, s32 minor, SBTLVISUAL_DATA *data) {
  VISUALDATA_WORK *VisualDataZ;
  V_POSITION_WORK **p_sbtleff_cylindertbl;
  V_POSITION_WORK *v14;
  V_POSITION_WORK *nml;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  s64 v20;
  f32 v21;
  __int128 v26;
  sdfMatrix4_t v27;
  sdfMatrix4_t v28;
  sdfVector4_t v29;
  sdfVector4_t v30;

  if (!major)
  {
    VisualDataZ = sbtlvisual_tbldata_player[minor];
    goto LABEL_9;
  }
  VisualDataZ = sBtlGetVisualDataZ(minor);
LABEL_9:
  if (major)
  {
    p_sbtleff_cylindertbl = &sbtleff_cylindertbl;
  }
  else
  {
    p_sbtleff_cylindertbl = &sbtleff_cylindertbl_p;
  }
  v14 = (*p_sbtleff_cylindertbl)[minor];
  nml = VisualDataZ->nml;
  x = _rot.x;
  y = _rot.y;
  z = _rot.z;
  w = _rot.w;
  v20 = *(u64 *)&nml->x;
  v21 = nml->z;
  v30.x = x;
  v30.y = y;
  v30.z = z;
  v30.w = w;
  sBtlGetRotateDeg(v30, 180.0);
  ToMatrix();
  *(u64 *)&vct_A.x = v20;
  vct_A.z = v21;
  vct_A.w = 1.0;
  get_transpose(&v28, &mtx_A, 0);
  v27 = v28;
  v29 = op_Multiply_60923920(&v27, vct_A, 0);
  vct_A = v29;
  data->center = vct_A;
  data->hit_area_r = VisualDataZ->hit_area_r;
  *(u64 *)&v26 = *(u64 *)&VisualDataZ->nml->cylinder;
  *((u64 *)&v26 + 1) = *(u64 *)&v14->cylinder;
  *(_OWORD *)&data->width = v26;
  return 1;
}

// 0x2132fb0
bool sBtlGetCylinderData(SBTLUNIT_WORK *wk, SBTLVISUAL_DATA *data) {
  s32 major;
  s64 minor;
  VISUALDATA_WORK *VisualDataZ;
  s32 v9;
  s64 v10;
  V_POSITION_WORK **p_sbtleff_cylindertbl;
  V_POSITION_WORK *v15;
  V_POSITION_WORK *nml;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  s64 v21;
  f32 v22;
  f32 *p_x;
  f32 v28;
  f32 v29;
  __int128 v30;
  sdfMatrix4_t v31;
  sdfMatrix4_t v32;
  sdfVector4_t v33;
  sdfVector4_t v34;

  major = wk->major;
  minor = wk->minor;
  if (!major)
  {
    VisualDataZ = sbtlvisual_tbldata_player[minor];
    v9 = wk->major;
    v10 = wk->minor;
    goto LABEL_9;
  }
  VisualDataZ = sBtlGetVisualDataZ(minor);
  v9 = wk->major;
  v10 = wk->minor;
LABEL_9:
  if (v9)
  {
    p_sbtleff_cylindertbl = &sbtleff_cylindertbl;
  }
  else
  {
    p_sbtleff_cylindertbl = &sbtleff_cylindertbl_p;
  }
  v15 = (*p_sbtleff_cylindertbl)[v10];
  nml = VisualDataZ->nml;
  x = wk->rot.x;
  y = wk->rot.y;
  z = wk->rot.z;
  w = wk->rot.w;
  v21 = *(u64 *)&nml->x;
  v22 = nml->z;
  v34.x = x;
  v34.y = y;
  v34.z = z;
  v34.w = w;
  sBtlGetRotateDeg(v34, 180.0);
  ToMatrix();
  *(u64 *)&vct_A.x = v21;
  vct_A.z = v22;
  vct_A.w = 1.0;
  get_transpose(&v32, &mtx_A, 0);
  v31 = v32;
  v33 = op_Multiply_60923920(&v31, vct_A, 0);
  vct_A = v33;
  p_x = &vf00.x;
  v28 = p_x[6];
  v29 = p_x[5];
  data->center.x = p_x[4] + wk->pos.x;
  data->center.y = v29 + wk->pos.y;
  data->center.z = v28 + wk->pos.z;
  data->center.w = wk->pos.w;
  data->hit_area_r = VisualDataZ->hit_area_r;
  *(u64 *)&v30 = *(u64 *)&VisualDataZ->nml->cylinder;
  *((u64 *)&v30 + 1) = *(u64 *)&v15->cylinder;
  *(_OWORD *)&data->width = v30;
  return 1;
}
