#include "types.h"
#include "enemypath.h"
#include "sbtl.h"
#include "sbtlactai.h"
#include "sbtlpath.h"
#include "sbtlscene.h"
#include "sdf_vu0.h"
#include "smnr.h"

typedef struct SBTLENMY_ACTDATA SBTLENMY_ACTDATA;
typedef struct SBTLENMY_PATHDATA SBTLENMY_PATHDATA;
typedef struct SBTLUNIT_WORK SBTLUNIT_WORK;

// 0x20c9070
bool sBtlSetNextPathData(SBTLUNIT_WORK *wk) {
  SBTLACTAI_WORK *actaiwk;
  s64 path_datap;
  SBTLENMY_ACTDATA *v6;
  s32 pathid;
  SBTLACTAI_WORK *v8;
  SBTLENMY_PATHDATA *v9;
  u32 flg;
  bool v11;
  s32 *p_path_cnt;
  s32 path_cnt;
  s32 v14;
  f32 y;
  f32 x;
  f32 w;
  f32 z;
  f32 *p_x;
  f32 v24;
  SBTLACTAI_WORK *v25;
  f32 offset_z;
  f32 v28;
  f32 v29;
  f32 v30;
  s32 type;
  s32 frame;
  struct sdfVector4_t nowpos;
  sdfVector4_t pos;

  actaiwk = wk->actaiwk;
  *(u64 *)&pos.x = 0;
  *(u64 *)&pos.z = 0;
  path_datap = actaiwk->path_datap;
  v6 = data[0][path_datap];
  pathid = v6->pathid;
  v8 = wk->actaiwk;
  v9 = pathdata[(s16)pathid];
  flg = v6->flg;
  if ((flg & 0x10) == 0)
  {
    v8->path_mode = 1;
    goto LABEL_20;
  }
  if (v8->path_mode != 1)
  {
    if (!v8->path_mode)
    {
      v8->path_cnt = GetIntervalRand(0, v6->frame);
      v11 = 0;
      wk->actaiwk->path_mode = 1;
      return v11;
    }
LABEL_20:
    v8->path_cnt = 0;
    v8->path_mode = 0;
    v8->path_datap = v6->jmpid;
    if ((flg & 2) == 0)
    {
      x = v9->nextpos.x;
      y = v9->nextpos.y;
      z = v9->nextpos.z;
      w = v9->nextpos.w;
      p_x = &vf00.x;
      p_x[4] = x;
      p_x[5] = y;
      p_x[6] = z;
      p_x[7] = w;
      goto LABEL_31;
    }
    nowpos = v9->nowpos;
    vct_A = nowpos;
LABEL_31:
    pos = vct_A;
    v24 = vct_A.x;
    v25 = wk->actaiwk;
    offset_z = main_data->offset_z;
    v28 = main_data->offset_x + v25->path_ofspos.x;
    v29 = v24 + v28;
    v30 = pos.z + (f32)(offset_z + v25->path_ofspos.z);
    pos.x = v29;
    pos.z = v30;
    if (!(u32)main_data)
    pos.y = pos.y + sBtlGetGroundPos(v29, v30);
    type = v6->type;
    frame = v6->frame;
    v11 = 1;
    sBtlSetNormalAction(wk, type, 1, frame, &pos);
    return v11;
  }
  path_cnt = v8->path_cnt;
  p_path_cnt = &v8->path_cnt;
  *p_path_cnt = path_cnt + 1;
  v14 = v6->frame;
  LimitRange(p_path_cnt, 0, v14);
  v8 = wk->actaiwk;
  v11 = 0;
  if (v8->path_cnt >= v6->frame)
  {
    flg = v6->flg;
    goto LABEL_20;
  }
  return v11;
}

// 0x20c9570
s16 sBtlGetPathDataCount(s16 id) {
  return tbldatacnt[id];
}

// 0x20c9480
SBTLENMY_ACTDATA *sBtlGetPathACTData(s16 id, s16 no) {
  return data[id][no];
}

// 0x20c9500
SBTLENMY_PATHDATA *sBtlGetPathData(s16 id) {
  return pathdata[id];
}
