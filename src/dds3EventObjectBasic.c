#include "types.h"
#include "dds3basic.h"
#include "dds3eventobjectbasic.h"
#include "dds3objectbase.h"
#include "dds3scenebasic.h"

typedef struct dds3BasicFunction_t dds3BasicFunction_t;
typedef struct dds3Basic_t dds3Basic_t;
typedef struct dds3ObjectBaseControlWorkData_t dds3ObjectBaseControlWorkData_t;

dds3BasicFunction_t *Function;

static bool Constructor(dds3Basic_t *pBasic);
static void Destructor(dds3Basic_t *pBasic);
static bool MainProcuder(dds3Basic_t *pBasic);

// 0x22f8db0
static bool Constructor(dds3Basic_t *pBasic) {
  Il2CppObject *v3;
  void *v4;
  void *p_workdata;
  void *v6;
  dds3ObjectBaseControlWorkData_t *inited;
  Project_Basic_dds3Basic_t_WORK_c *klass;
  dds3Basic_t *basic;

  basic = pBasic;
  dds3InitPoseSet(basic);
  v3 = Allocate(dds3EventObjectBasicWorkData_t);
  v4 = NewSpecific(uint, 3u);
  v3[1].monitor = v4;
  _ctor(v3, 0);
  pBasic->workdata = (void *)v3;
  p_workdata = &pBasic->workdata;
  v6 = p_workdata;
  inited = dds3ObjectBaseInitControlWorkData(basic);
  klass = v6->klass;
  return 1;
}

// 0x22f8f80
static void Destructor(dds3Basic_t *pBasic) {
  dds3PoseSet_t *p_poseset;
  dds3ObjectBaseControlWorkData_t *workdata;
  s64 naturalAligment;

  if (pBasic)
  {
    p_poseset = &pBasic->poseset;
    if (pBasic->poseset)
    {
      p_poseset = 0;
    }
  }
  workdata = pBasic->workdata;
  if (workdata)
  {
    LOBYTE(workdata[2].sdwid) < (u32)naturalAligment || *(dds3EventObjectBasicWorkData_t **)(*(u64 *)&workdata[1].sdwid + 8 * naturalAligment - 8) != dds3EventObjectBasicWorkData_t;
  }
  dds3ObjectBaseFreeControlWorkData(workdata + 2);
}

// 0x22f9060
static bool MainProcuder(dds3Basic_t *pBasic) {
  dds3PoseSet_t *poseset;
  u32 flag;
  struct sdfVector4_t scl;
  struct sdfVector4_t rot;
  struct sdfVector4_t v9;

  poseset = pBasic->poseset;
  flag = poseset->flag;
  if ((flag & 1) == 0)
    return 1;
  flag = poseset->flag;
  poseset->flag = flag & 0xFFFFFFFE;
  scl = poseset->scl;
  v9 = poseset->scl;
  scl = v9;
  poseset->workscl = scl;
  rot = poseset->rot;
  poseset->workpos = poseset->pos;
  poseset->workrot = rot;
  return 1;
}

// 0x22f9170
dds3Basic_t *dds3EventObjectBasicAdd(u32 serialID, const sdfVector4_t *pos, const sdfVector4_t *rot) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  f32 v8;
  f32 v9;
  f32 v10;
  f32 v11;
  dds3Basic_t *v14;
  f32 *poseset;
  char v17;
  dds3PoseSet_t *v18;
  struct sdfVector4_t scl;
  dds3Basic_t *pBasic;
  sdfVector4_t v25;

  w = rot->w;
  z = rot->z;
  y = rot->y;
  x = rot->x;
  v8 = pos->w;
  v9 = pos->z;
  v10 = pos->y;
  v11 = pos->x;
  v14 = dds3SceneBasicAdd(8);
  pBasic = v14;
  v14->serialID = serialID;
  v25.x = v11;
  v25.y = v10;
  v25.z = v9;
  v25.w = v8;
  dds3SetPosPoseSet(pBasic, v25);
  poseset = v14->poseset;
  *((u32 *)poseset + 52) = (u32)poseset[52] & 0xFFFFFFFC | 1;
  poseset[24] = x;
  poseset[25] = y;
  v17 = byte_5759874;
  poseset[26] = z;
  poseset[27] = w;
  if ((v17 & 1) == 0)
  {
    v18 = v14->poseset;
    scl = v18->scl;
    goto LABEL_12;
  }
  v18 = v14->poseset;
  scl = v18->scl;
LABEL_12:
  v18->workscl = scl;
  v14->poseset->workrot = v14->poseset->rot;
  v14->poseset->workpos = v14->poseset->pos;
  return v14;
}

// 0x22f9350
dds3ObjectBaseControlWorkData_t *dds3EventObjectBasicGetControlWorkData(dds3Basic_t *pBasic) {
  dds3ObjectBaseControlWorkData_t *workdata;
  s64 naturalAligment;

  workdata = (dds3ObjectBaseControlWorkData_t *)pBasic->workdata;
  if (workdata)
  {
    LOBYTE(workdata[2].sdwid) < (u32)naturalAligment || *(dds3EventObjectBasicWorkData_t **)(*(u64 *)&workdata[1].sdwid + 8 * naturalAligment - 8) != dds3EventObjectBasicWorkData_t;
  }
  return workdata[2];
}
