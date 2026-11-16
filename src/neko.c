#include "types.h"
#include "ctn.h"
#include "dds3vrf.h"
#include "neko.h"
#include "sdf_vu0.h"
#include "sdfquat.h"
#include "sdfvu0.h"

#define NEKO_WAKEUP_DIST_2 16
#define NEKO_POINT_DIST_2 3
#define NEKO_EXIT_DIST_2 0.1
#define NEKO_VELOCITY 0.07
#define NEKO_EXIST_COUNT 180
#define NEKO_HIDE_COUNT 40
#define NEKO_HIDE_COUNT2 30

typedef struct nekoNeko_t nekoNeko_t;
typedef struct nekoWork_t nekoWork_t;

s32 gNekoFlag;
nekoWork_t *Work;

static s32 LoadData(char *filename);
static void UpdateTargetVelocity(nekoNeko_t *pNeko);
static void UpdateVelocity(nekoNeko_t *pNeko);
static void UpdatePosition(nekoNeko_t *pNeko);
static void UpdateRotation(nekoNeko_t *pNeko);
static void ComeHome(nekoNeko_t *pNeko);
static s32 CheckWakeup(nekoNeko_t *pNeko);
static void Wakeup(nekoNeko_t *pNeko);
static s32 CheckReachTarget(nekoNeko_t *pNeko);
static void ChooseNextTarget(nekoNeko_t *pNeko);
static void Hide(nekoNeko_t *pNeko);
static void StartFilename(char *filename);

// 0x18e6980
static s32 LoadData(char *filename) {
  bool IsLoad;
  void *Asset;
  sdfBinary *v8;
  s32 S32;
  sdfBinary *New;
  nekoWork_t *v14;
  s32 v15;
  sdfBinary *v16;
  nekoWork_t *v17;
  nekoHome_t *v18;
  nekoWork_t *v19;
  nekoPoint_t *v20;
  s64 v21;
  nekoHome_t *v23;
  f32 Float;
  f32 *rotateQuat;
  f32 *v26;
  f32 *v27;
  f32 *v28;
  s32 v29;
  s32 *connectedPointIndexArray;
  s64 v31;
  s32 v32;
  char *v33;
  nekoHome_t *homeArray;
  Il2CppClass **v36;
  s64 v37;
  nekoPoint_t *v38;
  f32 v39;
  f32 *v40;
  f32 *v41;
  f32 *v42;
  f32 *v43;
  s32 v44;
  s32 *v45;
  s64 v46;
  s32 v47;
  char *v48;
  s32 v49;
  nekoPoint_t *pointArray;
  Il2CppClass **v52;

  IsLoad = IsLoad(Dependent, "fld_01", 0);
  if (IsLoad)
  {
    goto LABEL_7;
  }
  Load(Dependent, "fld_01", "fld_01");
  LoadSyncAll(_Ctrl_k__BackingField, 0);
LABEL_7:
  Asset = LoadAsset(_Ctrl_k__BackingField, "fld_01", filename, 0);
  v8 = Allocate(sdfBinary);
  _ctor(v8, Asset, 0);
  if (!IsLoad)
  {
    Unload(Dependent, "fld_01", 0);
  }
  Work->homeNum = ReadS32(v8, 0);
  S32 = ReadS32(v8, 0);
  New = GetNew(v8, 0, S32, 0);
  v14 = Work;
  v14->pointNum = ReadS32(v8, 0);
  v15 = ReadS32(v8, 0);
  v16 = GetNew(v8, 0, v15, 0);
  v17 = Work;
  v18 = NewSpecific(nekoHome_t, v17->homeNum);
  v17->homeArray = v18;
  v19 = Work;
  v20 = NewSpecific(nekoPoint_t, v19->pointNum);
  v19->pointArray = v20;
  v21 = 0;
  while (v21 < Work->homeNum)
  {
    v23 = Allocate(nekoHome_t);
    _ctor(v23, 0);
    v23->x = ReadFloat(New, 0);
    v23->y = ReadFloat(New, 0);
    Float = ReadFloat(New, 0);
    rotateQuat = v23->rotateQuat;
    v23->angle = Float;
    rotateQuat[0] = ReadFloat(New, 0);
    v26 = v23->rotateQuat;
    v26[1] = ReadFloat(New, 0);
    v27 = v23->rotateQuat;
    v27[2] = ReadFloat(New, 0);
    v28 = v23->rotateQuat;
    v28[3] = ReadFloat(New, 0);
    v29 = ReadS32(New, 0);
    connectedPointIndexArray = v23->connectedPointIndexArray;
    v23->connectNum = v29;
    if (SLODWORD(connectedPointIndexArray->max_length) >= 1)
    {
      v31 = 0;
      do
      {
        v32 = ReadS32(New, 0);
        v33 = (char *)connectedPointIndexArray + 4 * v31;
        connectedPointIndexArray = v23->connectedPointIndexArray;
        ++v31;
        *((u32 *)v33 + 8) = v32;
      }
      while (v31 < SLODWORD(connectedPointIndexArray->max_length));
    }
    homeArray = Work->homeArray;
    v36 = &homeArray->obj.klass + v21;
    v36[4] = v23;
    ++v21;
  }
  v37 = 0;
  while (v37 < Work->pointNum)
  {
    v38 = Allocate(nekoPoint_t);
    _ctor(v38, 0);
    v38->x = ReadFloat(v16, 0);
    v38->y = ReadFloat(v16, 0);
    v38->type = ReadS32(v16, 0);
    v38->dirX = ReadFloat(v16, 0);
    v38->dirY = ReadFloat(v16, 0);
    v39 = ReadFloat(v16, 0);
    v40 = v38->rotateQuat;
    v38->angle = v39;
    v40[0] = ReadFloat(v16, 0);
    v41 = v38->rotateQuat;
    v41[1] = ReadFloat(v16, 0);
    v42 = v38->rotateQuat;
    v42[2] = ReadFloat(v16, 0);
    v43 = v38->rotateQuat;
    v43[3] = ReadFloat(v16, 0);
    v44 = ReadS32(v16, 0);
    v45 = v38->connectedPointIndexArray;
    v38->connectNum = v44;
    if (SLODWORD(v45->max_length) >= 1)
    {
      v46 = 0;
      do
      {
        v47 = ReadS32(v16, 0);
        v48 = (char *)v45 + 4 * v46;
        v45 = v38->connectedPointIndexArray;
        ++v46;
        *((u32 *)v48 + 8) = v47;
      }
      while (v46 < SLODWORD(v45->max_length));
    }
    v38->resv = ReadS32(v16, 0);
    switch ((u32)v37)
    {
      case 0xF:
        v49 = 1114112000;
        break;
      case 0xD:
        v49 = 1115160576;
        break;
      case 0xC:
        v49 = 1110389555;
        v38->x = 70.8;
        break;
      default:
        goto LABEL_39;
    }
    LODWORD(v38->y) = v49;
LABEL_39:
    pointArray = Work->pointArray;
    v52 = &pointArray->obj.klass + v37;
    v52[4] = v38;
    ++v37;
  }
  return 1;
}

// 0x18e7050
static void UpdateTargetVelocity(nekoNeko_t *pNeko) {
  f32 *v3;
  s32 state;
  f32 angle;
  f32 v7;
  f32 v8;
  f32 v9;
  f32 v10;
  f32 v11;
  f32 v12;
  f32 v13;
  f32 v14;
  f32 v15;
  f32 v16;
  f32 v17;
  float32x2_t *v18;
  nekoPoint_t *v20;
  float32x2_t *v22;
  f32 y;
  f32 *v24;
  u64 v25;
  f32 v26;

  v3 = NewSpecific(f32, 2u);
  state = pNeko->state;
  if (state == 2)
  {
    angle = Work->pointArray[pNeko->nextPointIndex]->angle;
    v7 = angle * 0.15915494;
    v8 = (f32)(angle + 1.5708) * 0.15915494;
    v9 = (s32)v7;
    if (v7 == INFINITY)
      v9 = -2147500000.0;
    v10 = v7 - v9;
    v11 = v10 + 1.0;
    if (v10 >= -0.5)
      v11 = v10;
    if (v10 > 0.5)
      v12 = v10 + -1.0;
    else
      v12 = v11;
    v13 = -0.5 - v12;
    if (v12 >= -0.25)
      v13 = v12;
    if (v12 > 0.25)
      v13 = 0.5 - v12;
    v14 = v13 * 4.0;
    v15 = v14 * v14;
    pNeko->targetVx = (f32)((f32)((f32)((f32)((f32)(v14 * 1.5708) + (f32)((f32)(v14 * (f32)(v14 * v14)) * -0.6459637)) + (f32)((f32)((f32)(v14 * v14) * (f32)(v14 * (f32)(v14 * v14))) * 0.07968968)) + (f32)((f32)(v15 * (f32)(v15 * (f32)(v14 * (f32)(v14 * v14)))) * -0.0046737655)) + (f32)((f32)(v15 * (f32)(v15 * (f32)(v15 * (f32)(v14 * (f32)(v14 * v14))))) * 0.00015148419))
                           * 0.07;
    if (v8 == INFINITY)
      v16 = -2147500000.0;
    else
      v16 = (s32)v8;
    v17 = v8 - v16;
    if (v17 <= 0.5)
    {
      if (v17 < -0.5)
        v17 = v17 + 1.0;
    }
    else
    {
      v17 = v17 + -1.0;
    }
    if (v17 <= 0.25)
    {
      if (v17 < -0.25)
        v17 = -0.5 - v17;
    }
    else
    {
      v17 = 0.5 - v17;
    }
    v26 = v17 * 4.0;
    pNeko->targetVy = (f32)((f32)((f32)((f32)((f32)(v26 * 1.5708) + (f32)((f32)(v26 * (f32)(v26 * v26)) * -0.6459637)) + (f32)((f32)((f32)(v26 * v26) * (f32)(v26 * (f32)(v26 * v26))) * 0.07968968)) + (f32)((f32)((f32)(v26 * v26) * (f32)((f32)(v26 * v26) * (f32)(v26 * (f32)(v26 * v26)))) * -0.0046737655)) + (f32)((f32)((f32)(v26 * v26) * (f32)((f32)(v26 * v26) * (f32)((f32)(v26 * v26) * (f32)(v26 * (f32)(v26 * v26))))) * 0.00015148419))
                           * -0.07;
  }
  else if (state)
  {
    v18 = v3;
    v20 = Work->pointArray[pNeko->nextPointIndex];
    v18[4].n64_f32[0] = v20->x - pNeko->x;
    v22 = v18 + 4;
    y = v20->y;
    v18[4].n64_f32[1] = y - pNeko->y;
    v24 = (f32 *)&v18[4] + 1;
    if (!(u32)v20)
    ctnNormalizeVec(v22, v24);
    v25 = vmul_f32((float32x2_t)v22->n64_u64[0], vdup_n_s32(0x3D8F5C29u)).n64_u64[0];
    v22->n64_u64[0] = v25;
    LODWORD(pNeko->targetVx) = v25;
    pNeko->targetVy = *v24;
  }
  else
  {
    pNeko->targetVx = 0.0;
    pNeko->targetVy = 0.0;
  }
}

// 0x18e73f0
static void UpdateVelocity(nekoNeko_t *pNeko) {
  s32 state;
  float32x2_t v4;
  float32x2_t v5;
  f32 v6;
  float32x2_t v7;
  float32x2_t v8;

  state = pNeko->state;
  if (state)
  {
    v5.n64_u64[0] = *(u64 *)&pNeko->vx;
    v4.n64_u64[0] = *(u64 *)&pNeko->targetVx;
    v6 = 0.0034999999;
    v7.n64_u64[0] = vsub_f32(v4, v5).n64_u64[0];
    if (state == 2)
      v6 = 0.0058333334;
    v8.n64_u64[0] = vmul_f32(v7, v7).n64_u64[0];
    if (state == 1)
      v6 = 0.0023333333;
    v8.n64_f32[0] = sqrtf(vaddv_f32(v8));
    if (v8.n64_f32[0] != 0.0)
    {
      if (v8.n64_f32[0] <= v6)
      {
        if (VRF >= 2.0)
          *(float32x2_t *)&pNeko->vx = vadd_f32(v4, v4);
        else
          *(float32x2_t *)&pNeko->vx = vmul_n_f32(v4, VRF);
      }
      else
      {
        *(float32x2_t *)&pNeko->vx = vadd_f32(vdiv_f32(vmul_n_f32(v7, v6), vdup_lane_s32(v8, 0)), v5);
      }
    }
  }
  else
  {
    *(u64 *)&pNeko->vx = 0;
  }
}

// 0x18e7500
static void UpdatePosition(nekoNeko_t *pNeko) {
  *(float32x2_t *)&pNeko->x = vadd_f32(*(float32x2_t *)&pNeko->x, *(float32x2_t *)&pNeko->vx);
}

// 0x18e7510
static void UpdateRotation(nekoNeko_t *pNeko) {
  long f64 v3;
  f32 v5;
  _OWORD *p_m00;
  __int128 v7;
  __int128 v8;
  __int128 v9;
  nekoNeko_t *p_fields;
  sdfMatrix4_t v14;
  sdfVector4_t Row;

  if (pNeko->state)
  {
    v3 = sub_18E6660(0);
    v5 = *(f32 *)&v3;
    p_m00 = &IdentityMatrix.m00;
    v7 = p_m00[2];
    v8 = p_m00[3];
    v9 = p_m00[1];
    *(_OWORD *)&v14.m00 = *p_m00;
    *(_OWORD *)&v14.m01 = v9;
    *(_OWORD *)&v14.m02 = v7;
    *(_OWORD *)&v14.m03 = v8;
    Row = GetRow(&v14, 1, 0);
    vct_A = Row;
    FromRotation(v5);
    p_fields = &pNeko->fields;
    p_fields->rotateQuat = vct_A;
    return;
  }
  pNeko->angle = Work->homeArray[pNeko->homeIndex]->angle;
}

// 0x18e7710
static void ComeHome(nekoNeko_t *pNeko) {
  s64 v6;
  s64 v7;
  s64 v8;
  s64 v9;

  pNeko->state = 0;
  v6 = (s64)Work->homeArray + 8 * pNeko->homeIndex;
  pNeko->fExist = 1;
  v7 = *(u64 *)(v6 + 32);
  v8 = *(u64 *)(v7 + 16);
  pNeko->vleng = 0.0;
  *(u64 *)&pNeko->vx = 0;
  *(u64 *)&pNeko->targetVx = 0;
  *(u64 *)&pNeko->x = v8;
  LODWORD(v8) = *(u32 *)(v7 + 24);
  v9 = *(u64 *)(v7 + 32);
  LODWORD(pNeko->angle) = v8;
  pNeko->rotateQuat.x = *(f32 *)(v9 + 32);
  pNeko->rotateQuat.y = *(f32 *)(v9 + 36);
  pNeko->rotateQuat.z = *(f32 *)(v9 + 40);
  LODWORD(v8) = *(u32 *)(v9 + 44);
  LODWORD(v9) = Work->nekoNum + 1;
  LODWORD(pNeko->rotateQuat.w) = v8;
  Work->nekoNum = v9;
  gNekoFlag = -1;
}

// 0x18e77f0
static s32 CheckWakeup(nekoNeko_t *pNeko) {
  float32x2_t v4;

  v4.n64_u64[0] = vsub_f32(*(float32x2_t *)&Work->playerX, *(float32x2_t *)&pNeko->x).n64_u64[0];
  return vaddv_f32(vmul_f32(v4, v4)) < 16.0;
}

// 0x18e7880
static void Wakeup(nekoNeko_t *pNeko) {
  pNeko->state = 1;
  pNeko->nextPointIndex = Work->homeArray[pNeko->homeIndex]->connectedPointIndexArray[0];
  pNeko->prevPointIndex = -1;
}

// 0x18e7910
static s32 CheckReachTarget(nekoNeko_t *pNeko) {
  nekoPoint_t *v4;
  f32 v5;

  v4 = Work->pointArray[pNeko->nextPointIndex];
  v5 = (f32)((f32)(v4->x - pNeko->x) * (f32)(v4->x - pNeko->x))
     + (f32)((f32)(v4->y - pNeko->y) * (f32)(v4->y - pNeko->y));
  if (v4->type)
  {
    if (v5 < 0.1)
      return 2;
    return 0;
  }
  return v5 < 3.0;
}

// 0x18e7a00
static void ChooseNextTarget(nekoNeko_t *pNeko) {
  s32 nextPointIndex;
  s32 *v4;
  nekoPoint_t *v6;
  s64 v7;
  s32 v8;
  s64 v9;
  s64 v10;
  s32 v11;
  s32 prevPointIndex;
  s32 v13;

  nextPointIndex = pNeko->nextPointIndex;
  v4 = NewSpecific(s32, 0x10u);
  v6 = Work->pointArray[pNeko->nextPointIndex];
  if (v6->connectNum < 1)
    goto LABEL_18;
  v7 = 0;
  v8 = 0;
  do
  {
    v9 = v6->connectedPointIndexArray[v7];
    if (Work->pointArray[v9]->type == 1)
    {
      v10 = (s64)(char *)v4 + 4 * v8++;
      *(u32 *)(v10 + 32) = v9;
    }
    ++v7;
  }
  while (v7 < v6->connectNum);
  if (v8)
  {
    pNeko->nextPointIndex = *(u32 *)((s64)(char *)v4 + 4 * ((s32)sub_1905740(0x7FFF, 0) % v8) + 32);
  }
  else
  {
LABEL_18:
    do
    {
      v11 = sub_1905740(0x7FFF, 0);
      prevPointIndex = pNeko->prevPointIndex;
      v13 = v6->connectedPointIndexArray[v11 % v6->connectNum];
      pNeko->nextPointIndex = v13;
    }
    while (v13 == prevPointIndex);
  }
  pNeko->prevPointIndex = nextPointIndex;
}

// 0x18e7b90
static void Hide(nekoNeko_t *pNeko) {
  s32 index;

  pNeko->fExist = 0;
  pNeko->existCnt = 180;
  if (pNeko->nextPointIndex != 13)
    return;
  index = pNeko->index;
  gNekoFlag = index;
}

// 0x18e7c50
static void StartFilename(char *filename) {
  nekoWork_t *v4;
  s64 v7;
  s64 v8;
  nekoNeko_t *v9;
  nekoHome_t *v14;
  s64 v15;
  f32 *rotateQuat;
  nekoNeko_t *nekoArray;

  gNekoFlag = -1;
  v4 = Allocate(nekoWork_t);
  _ctor(v4, 0);
  Work = v4;
  LoadData(filename);
  v7 = 0;
  v8 = 32;
  Work->nekoNum = 0;
  do
  {
    v9 = Allocate(nekoNeko_t);
    v9->homeIndex = v7;
    v9->index = v7;
    v9->fExist = 1;
    v9->state = 0;
    v14 = Work->homeArray[v9->homeIndex];
    v15 = *(u64 *)&v14->x;
    *(u64 *)&v9->vx = 0;
    *(u64 *)&v9->targetVx = 0;
    *(u32 *)&v9->vleng = 0;
    gNekoFlag = -1;
    *(u64 *)&v9->x = v15;
    *(f32 *)&v15 = v14->angle;
    rotateQuat = v14->rotateQuat;
    nekoArray = Work->nekoArray;
    *(u32 *)&v9->angle = v15;
    v9->rotateQuat.x = rotateQuat[0];
    v9->rotateQuat.y = rotateQuat[1];
    v9->rotateQuat.z = rotateQuat[2];
    *(f32 *)&v15 = rotateQuat[3];
    LODWORD(rotateQuat) = Work->nekoNum + 1;
    *(u32 *)&v9->rotateQuat.w = v15;
    Work->nekoNum = (s32)rotateQuat;
    *(Il2CppClass **)((char *)&nekoArray->obj.klass + v8) = v9;
    ++v7;
    v8 += 8;
  }
  while (v7 != 5);
}

// 0x18e7e80
void nekoStart(void) {
  char *v3;

  v3 = "neko.NEK";
  StartFilename(v3);
}

// 0x18e7f10
void nekoMemFree(void) {
  Work = 0;
}

// 0x18e7fa0
void nekoUpdate(f32 playerX, f32 playerY) {
  nekoNeko_t *v9;
  s32 hideCnt;
  s32 index;
  nekoNeko_t *v12;
  s32 v13;
  s32 v14;
  nekoNeko_t *v15;
  s32 v16;
  s32 v17;
  nekoNeko_t *v18;
  s32 v19;
  s32 v20;
  nekoNeko_t *v21;
  s32 v22;
  s32 v23;
  s64 i;
  s64 v25;
  s32 v26;
  bool v27;
  s32 v28;
  nekoWork_t *v30;
  nekoHome_t *v31;
  s64 v32;
  f32 *rotateQuat;
  s64 j;
  f32 v35;
  f32 v36;
  f32 v37;
  s64 v38;
  s32 v39;
  float32x2_t v40;
  s64 v41;
  nekoPoint_t *v42;
  f32 v43;
  s32 v45;
  f32 v47;
  f32 v48;
  f32 v49;
  f32 v50;
  f32 v51;
  f32 v52;

  Work->playerX = playerX;
  Work->playerY = playerY;
  v9 = Work->nekoArray[0];
  if (v9->fExist && v9->state == 2)
  {
    hideCnt = v9->hideCnt;
    if (hideCnt)
    {
      v9->hideCnt = hideCnt - 1;
    }
    else
    {
      v9->fExist = 0;
      v9->existCnt = 180;
      if (v9->nextPointIndex == 13)
      {
        index = v9->index;
        gNekoFlag = index;
      }
    }
  }
  v12 = Work->nekoArray[1];
  if (v12->fExist && v12->state == 2)
  {
    v13 = v12->hideCnt;
    if (v13)
    {
      v12->hideCnt = v13 - 1;
    }
    else
    {
      v12->fExist = 0;
      v12->existCnt = 180;
      if (v12->nextPointIndex == 13)
      {
        v14 = v12->index;
        gNekoFlag = v14;
      }
    }
  }
  v15 = Work->nekoArray[2];
  if (v15->fExist && v15->state == 2)
  {
    v16 = v15->hideCnt;
    if (v16)
    {
      v15->hideCnt = v16 - 1;
    }
    else
    {
      v15->fExist = 0;
      v15->existCnt = 180;
      if (v15->nextPointIndex == 13)
      {
        v17 = v15->index;
        gNekoFlag = v17;
      }
    }
  }
  v18 = Work->nekoArray[3];
  if (v18->fExist && v18->state == 2)
  {
    v19 = v18->hideCnt;
    if (v19)
    {
      v18->hideCnt = v19 - 1;
    }
    else
    {
      v18->fExist = 0;
      v18->existCnt = 180;
      if (v18->nextPointIndex == 13)
      {
        v20 = v18->index;
        gNekoFlag = v20;
      }
    }
  }
  v21 = Work->nekoArray[4];
  if (v21->fExist && v21->state == 2)
  {
    v22 = v21->hideCnt;
    if (v22)
    {
      v21->hideCnt = v22 - 1;
    }
    else
    {
      v21->fExist = 0;
      v21->existCnt = 180;
      if (v21->nextPointIndex == 13)
      {
        v23 = v21->index;
        gNekoFlag = v23;
      }
    }
  }
  for (i = 32; i != 72; i += 8)
  {
    v25 = *(s64 *)((char *)&Work->nekoArray->obj.klass + i);
    if (*(u32 *)(v25 + 32))
      continue;
    v26 = *(u32 *)(v25 + 92);
    v27 = __OFSUB__(v26, 1);
    v28 = v26 - 1;
    if (v28 < 0 == v27)
    {
      *(u32 *)(v25 + 92) = v28;
      continue;
    }
    *(u32 *)(v25 + 32) = 1;
    *(u32 *)(v25 + 72) = 0;
    v30 = Work;
    v31 = v30->homeArray[*(s32 *)(v25 + 76)];
    v32 = *(u64 *)&v31->x;
    *(u64 *)(v25 + 48) = 0;
    *(u64 *)(v25 + 56) = 0;
    *(u32 *)(v25 + 64) = 0;
    gNekoFlag = -1;
    *(u64 *)(v25 + 40) = v32;
    *(f32 *)&v32 = v31->angle;
    rotateQuat = v31->rotateQuat;
    *(u32 *)(v25 + 68) = v32;
    *(f32 *)(v25 + 16) = rotateQuat[0];
    *(f32 *)(v25 + 20) = rotateQuat[1];
    *(f32 *)(v25 + 24) = rotateQuat[2];
    *(f32 *)&v32 = rotateQuat[3];
    LODWORD(rotateQuat) = v30->nekoNum + 1;
    *(u32 *)(v25 + 28) = v32;
    v30->nekoNum = (s32)rotateQuat;
  }
  for (j = 32; j != 72; j += 8)
  {
    v38 = *(s64 *)((char *)&Work->nekoArray->obj.klass + j);
    if (*(u32 *)(v38 + 32))
    {
      v39 = *(u32 *)(v38 + 72);
      if (v39)
      {
        if (v39 != 1)
          goto LABEL_126;
LABEL_111:
        v41 = *(s32 *)(v38 + 80);
        v42 = Work->pointArray[v41];
        v43 = (f32)((f32)(v42->x - *(f32 *)(v38 + 40)) * (f32)(v42->x - *(f32 *)(v38 + 40)))
            + (f32)((f32)(v42->y - *(f32 *)(v38 + 44)) * (f32)(v42->y - *(f32 *)(v38 + 44)));
        if (v42->type)
        {
          if (v43 >= 0.1)
            goto LABEL_126;
          *(u32 *)(v38 + 72) = 2;
          if ((u32)v41 == 15)
          {
            *(u32 *)(v38 + 88) = 30;
          }
          else
          {
            *(u32 *)(v38 + 88) = 40;
          }
LABEL_127:
          UpdateTargetVelocity(v38);
          goto LABEL_128;
LABEL_92:
          v35 = 0.0;
          v36 = 0.0;
          *(u64 *)(v38 + 48) = 0;
        }
        else
        {
          if (v43 < 3.0)
          {
            ChooseNextTarget(v38);
          }
LABEL_126:
          goto LABEL_127;
LABEL_128:
          v45 = *(u32 *)(v38 + 72);
          if (!v45)
            goto LABEL_92;
          v48 = *(f32 *)(v38 + 56);
          v47 = *(f32 *)(v38 + 60);
          v36 = *(f32 *)(v38 + 48);
          v35 = *(f32 *)(v38 + 52);
          v49 = v47 - v35;
          v50 = v48 - v36;
          v51 = 0.0034999999;
          v52 = sqrtf((f32)(v50 * v50) + (f32)(v49 * v49));
          if (v45 == 2)
            v51 = 0.0058333334;
          if (v45 == 1)
            v51 = 0.0023333333;
          if (v52 != 0.0)
          {
            if (v52 <= v51)
            {
              if (VRF >= 2.0)
              {
                v36 = v48 + v48;
                v35 = v47 + v47;
              }
              else
              {
                v36 = v48 * VRF;
                v35 = v47 * VRF;
              }
            }
            else
            {
              v36 = v36 + (f32)((f32)(v51 * v50) / v52);
              v35 = v35 + (f32)((f32)(v51 * v49) / v52);
            }
            *(f32 *)(v38 + 48) = v36;
            *(f32 *)(v38 + 52) = v35;
          }
        }
        v37 = *(f32 *)(v38 + 44) + v35;
        *(f32 *)(v38 + 40) = *(f32 *)(v38 + 40) + v36;
        *(f32 *)(v38 + 44) = v37;
        UpdateRotation(v38);
        continue;
      }
      v40.n64_u64[0] = vsub_f32(*(float32x2_t *)&Work->playerX, *(float32x2_t *)(v38 + 40)).n64_u64[0];
      if (vaddv_f32(vmul_f32(v40, v40)) < 16.0)
      {
        *(u32 *)(v38 + 72) = 1;
        *(u32 *)(v38 + 80) = Work->homeArray[*(s32 *)(v38 + 76)]->connectedPointIndexArray[0];
        *(u32 *)(v38 + 84) = -1;
      }
      if (*(u32 *)(v38 + 72) != 1)
        goto LABEL_126;
      goto LABEL_111;
    }
  }
}
