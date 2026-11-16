#include "types.h"
#include "basic.h"
#include "dds3pathbasic.h"
#include "dds3scenebasic.h"
#include "sdf_vu0.h"
#include "sdfquat.h"

typedef struct dds3BasicFunction_t dds3BasicFunction_t;
typedef struct dds3Basic_t dds3Basic_t;
typedef struct dds3PathBasicControl_t dds3PathBasicControl_t;
typedef struct fldResourceLightPath_t fldResourceLightPath_t;
typedef struct fldResourcePathData_t fldResourcePathData_t;

dds3BasicFunction_t *Function;

// 0x2302a80
void GetElement(u32 *segment, f32 *weight, fldResourcePathData_t *pData, f32 frame) {
  u32 *pKey;
  u32 nKey;
  f32 v11;
  s64 v12;
  u32 v13;
  u32 v14;
  s64 v15;
  u32 v16;

  pKey = pData->pKey;
  if (get_nKey(pData, 0) == 1)
  {
LABEL_2:
    nKey = get_nKey(pData, 0);
    v11 = 1.0;
    *segment = nKey - 2;
  }
  else
  {
    v12 = 0;
    while (1)
    {
      v14 = pKey[v12];
      v15 = v12 + 1;
      if ((f32)v14 <= frame)
      {
        v16 = pKey[(s32)v15];
        if ((f32)v16 > frame)
          break;
      }
      v13 = get_nKey(pData, 0);
      v12 = v15;
      if ((u32)v15 >= v13 - 1)
        goto LABEL_2;
    }
    *segment = v12;
    v11 = (f32)(1.0 / (f32)(v16 - v14)) * (f32)(frame - (f32)pKey[v12]);
  }
  *weight = v11;
}

// 0x2302b70
dds3Basic_t *dds3PathBasicAdd(u32 serialID, void *pData, char *pName) {
  dds3Basic_t *v7;

  v7 = dds3SceneBasicAdd(15);
  v7->serialID = serialID;
  v7->name = pName;
  v7->workdata = pData;
  return v7;
}

// 0x2300570
dds3PathBasicControl_t *dds3PathBasicMakeControl(dds3Basic_t *pBasic) {
  void *workdata;
  s64 naturalAligment;
  dds3PathBasicControl_t *v5;
  s64 v6;
  fldResourcePathTable_t *v7;
  fldResourcePathData_t *pData;
  u64 *v9;
  s64 v11;
  s64 v13;
  s64 v15;
  s64 v17;
  u32 *pKey;
  f32 v19;

  workdata = pBasic->workdata;
  if (!get_nPathTable(workdata, 0))
    return 0;
  v5 = Allocate(dds3PathBasicControl_t);
  v5->pTransrate = 0;
  *(u64 *)&v5->mode = 0;
  *(u64 *)&v5->frameMax = 0;
  v5->pRotation = 0;
  v5->pFovy = 0;
  v5->pLight = 0;
  v5->mode = 0;
  *(u64 *)&v5->frameMax = 0;
  if (get_nPathTable(workdata, 0))
  {
    v6 = 0;
    while (2)
    {
      v7 = workdata->pPathTable[v6];
      pData = v7->pData;
      switch (v7->type)
      {
        case 0u:
          v9 = &v5->pTransrate;
          v5->flag |= 1u;
          if (!pData)
            goto LABEL_35;
          if (pData->klass->_2.naturalAligment < (u32)v11)
            goto LABEL_41;
          if (pData->klass->_2.typeHierarchy[v11 - 1] != Trans)
            goto LABEL_41;
          v5->pTransrate = pData;
          if (pData->klass->_2.naturalAligment < (u32)v11)
            goto LABEL_41;
          v9 = &v5->pTransrate;
          if (pData->klass->_2.typeHierarchy[v11 - 1] != Trans)
            goto LABEL_41;
          goto LABEL_36;
        case 2u:
          v9 = &v5->pRotation;
          v5->flag |= 2u;
          if (!pData)
            goto LABEL_35;
          if (pData->klass->_2.naturalAligment < (u32)v13)
            goto LABEL_41;
          if (pData->klass->_2.typeHierarchy[v13 - 1] != Rot)
            goto LABEL_41;
          v5->pRotation = pData;
          if (pData->klass->_2.naturalAligment < (u32)v13)
            goto LABEL_41;
          v9 = &v5->pRotation;
          if (pData->klass->_2.typeHierarchy[v13 - 1] != Rot)
            goto LABEL_41;
          goto LABEL_36;
        case 4u:
          v9 = &v5->pFovy;
          v5->flag |= 4u;
          if (!pData)
            goto LABEL_35;
          if (pData->klass->_2.naturalAligment < (u32)v15)
            goto LABEL_41;
          if (pData->klass->_2.typeHierarchy[v15 - 1] != Camera)
            goto LABEL_41;
          v5->pFovy = pData;
          if (pData->klass->_2.naturalAligment < (u32)v15)
            goto LABEL_41;
          v9 = &v5->pFovy;
          if (pData->klass->_2.typeHierarchy[v15 - 1] != Camera)
            goto LABEL_41;
          goto LABEL_36;
        case 5u:
          v9 = &v5->pLight;
          v5->flag |= 0x10u;
          if (pData)
          {
            if (pData->klass->_2.naturalAligment < (u32)v17 || pData->klass->_2.typeHierarchy[v17 - 1] != Light || (v5->pLight = pData, pData->klass->_2.naturalAligment < (u32)v17) || (v9 = &v5->pLight, pData->klass->_2.typeHierarchy[v17 - 1] != Light))
            {
LABEL_41:
            }
          }
          else
          {
LABEL_35:
            *v9 = 0;
          }
LABEL_36:
LABEL_37:
          pKey = pData->pKey;
          v19 = pKey[get_nKey(pData, 0) - 1];
          if (v5->frameMax < v19)
            v5->frameMax = v19;
          if (++v6 < (u64)get_nPathTable(workdata, 0))
            continue;
          return v5;
        default:
          goto LABEL_37;
      }
    }
  }
  return v5;
}

// 0x2300560
void dds3PathBasicFreeControl(dds3PathBasicControl_t *pControl) {
  ;
}

// 0x22fe660
void dds3PathBasicControlGetPos(dds3PathBasicControl_t *pControl) {
  dds3PathBasicControl_t *v3;
  f32 frame;
  fldResourcePathData_t *pTransrate;
  u32 *pKey;
  u32 v8;
  f32 *klass;
  s64 v10;
  f32 v11;
  signed s32 v12;
  u32 nKey;
  u32 v14;
  s64 v15;
  f32 v16;
  u32 v17;
  f32 v18;
  u32 *v19;
  f32 *v20;
  f32 *v21;
  f32 v22;
  f32 v23;
  f32 v24;
  f32 z;
  f32 y;
  f32 x;
  f32 v30;
  f32 v32;

  v3 = pControl;
  if ((pControl->flag & 1) == 0)
  {
    vct_A = vf00;
    return;
  }
  frame = v3->frame;
  pTransrate = v3->pTransrate;
  pKey = pTransrate->pKey;
  if (get_nKey(pTransrate, 0) != 1)
  {
    v10 = 0;
    while (1)
    {
      v14 = pKey[v10];
      v15 = v10 + 1;
      v16 = v14;
      if (frame >= (f32)v14)
      {
        v17 = pKey[(s32)v15];
        if (frame < (f32)v17)
          break;
      }
      nKey = get_nKey(pTransrate, 0);
      v10 = v15;
      if ((u32)v15 >= nKey - 1)
        goto LABEL_11;
    }
    v12 = v10 + 1;
    v18 = (v17 - v14);
    klass = pTransrate[1].klass;
    v11 = (f32)(frame - v16) * (f32)(1.0 / v18);
LABEL_18:
    v32 = v11;
    v19 = klass + 8;
    v20 = &v19[3 * v12];
    v21 = &v19[3 * v10];
    v23 = *v20;
    v22 = v20[1];
    v24 = v20[2];
    y = v21[1];
    z = v21[2];
    x = *v21;
    goto LABEL_19;
  }
LABEL_11:
  v8 = get_nKey(pTransrate, 0);
  klass = pTransrate[1].klass;
  v10 = v8 - 2;
  if (v8 != 1)
  {
    v11 = 1.0;
    v12 = v8 - 1;
    goto LABEL_18;
  }
  v23 = klass[8];
  v22 = klass[9];
  v24 = klass[10];
  v32 = 1.0;
  y = zeroVector.y;
  z = zeroVector.z;
  x = zeroVector.x;
LABEL_19:
  vct_A.x = v23;
  vct_A.y = v22;
  vct_A.z = v24;
  vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v32);
  vct_B = vct_A;
  vct_A.x = x;
  vct_A.y = y;
  vct_A.z = z;
  v30 = 1.0 - v32;
  vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v30);
  vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  vct_A.w = 0.0;
}

// 0x22fec50
void dds3PathBasicControlGetRot(dds3PathBasicControl_t *pControl) {
  dds3PathBasicControl_t *v3;
  f32 frame;
  fldResourcePathData_t *pRotation;
  u32 *pKey;
  u32 nKey;
  fldResourcePathData_t *klass;
  s64 v10;
  f32 v11;
  __int128 v14;
  __int128 *static_fields;
  u32 v16;
  u32 v17;
  u32 v18;
  __int128 v20;
  struct sdfVector4_t v21;

  v3 = pControl;
  if ((pControl->flag & 2) == 0)
  {
    vct_A = vf00;
    return;
  }
  frame = v3->frame;
  pRotation = v3->pRotation;
  pKey = pRotation->pKey;
  if (get_nKey(pRotation, 0) != 1)
  {
    v10 = 0;
    while (1)
    {
      v16 = pKey[v10];
      v17 = v10 + 1;
      if (frame >= (f32)v16)
      {
        v18 = pKey[v17];
        if (frame < (f32)v18)
          break;
      }
      ++v10;
      if (v17 >= get_nKey(pRotation, 0) - 1)
        goto LABEL_15;
    }
    klass = pRotation[1].klass;
    v11 = (f32)(frame - (f32)v16) * (f32)(1.0 / (f32)(v18 - v16));
    v20 = *((_OWORD *)&klass->_1.byval_arg + v10);
LABEL_18:
    v14 = v20;
    goto LABEL_32;
LABEL_17:
    goto LABEL_18;
  }
LABEL_15:
  nKey = get_nKey(pRotation, 0);
  klass = pRotation[1].klass;
  v10 = nKey - 2;
  if (nKey != 1)
  {
    v11 = 1.0;
    v20 = *((_OWORD *)&klass->_1.byval_arg + v10);
    goto LABEL_17;
  }
  v11 = 1.0;
  LODWORD(v10) = -1;
  v14 = *static_fields;
LABEL_32:
  static_fields[1] = v14;
  v21 = *((sdfVector4_t *)&klass->_1.this_arg + (s32)v10);
  vct_B = v21;
  Lerp(v11);
}

// 0x22ff180
void dds3PathBasicControlGetLight(dds3PathBasicControl_t *pControl, fldResourceLightPath_t *resource) {
  dds3PathBasicControl_t *v5;
  fldResourceLightPath_t *v6;
  fldResourcePathData_t *pLight;
  f32 frame;
  u32 *pKey;
  u32 nKey;
  f32 v11;
  s64 v12;
  s64 v13;
  fldResourcePathData_t *klass;
  void **v15;
  char *v16;
  f32 *v17;
  f32 v18;
  f32 v20;
  f32 v21;
  f32 v22;
  void **v23;
  char *v24;
  f32 *v25;
  f32 v26;
  f32 v27;
  f32 v28;
  f32 v29;
  s32 v30;
  s32 v31;
  s32 v32;
  f32 v33;
  s32 v34;
  f32 v35;
  f32 v36;
  f32 v37;
  f32 v38;
  f32 v39;
  s32 v40;
  s32 v41;
  f32 v42;
  s32 v43;
  f32 v44;
  f32 v45;
  f32 v46;
  f32 v47;
  f32 v48;
  s32 v49;
  s32 v50;
  u32 v51;
  signed s32 v52;
  u32 v53;
  s32 v54;
  s32 v55;
  s32 v56;
  s32 v57;
  s32 v58;
  s32 v59;
  s32 v60;
  f32 v61;
  f32 v62;

  v5 = pControl;
  if ((pControl->flag & 0x10) != 0)
  {
    v6 = resource;
    pLight = v5->pLight;
    frame = v5->frame;
    pKey = pLight->pKey;
    if (get_nKey(pLight, 0) == 1)
    {
LABEL_7:
      nKey = get_nKey(pLight, 0);
      v11 = 1.0;
      LODWORD(v12) = nKey - 2;
      v13 = (s32)(nKey - 1);
    }
    else
    {
      v12 = 0;
      while (1)
      {
        v51 = pKey[v12];
        v52 = v12 + 1;
        if (frame >= (f32)v51)
        {
          v53 = pKey[v52];
          if (frame < (f32)v53)
            break;
        }
        ++v12;
        if (v52 >= get_nKey(pLight, 0) - 1)
          goto LABEL_7;
      }
      v13 = v52;
      v11 = (f32)(frame - (f32)v51) * (f32)(1.0 / (f32)(v53 - v51));
    }
    klass = pLight[1].klass;
    v15 = &klass->_1.image + v13;
    v62 = v11;
    v17 = v15[4];
    v16 = (v15 + 4);
    v18 = v17[4];
    vct_A.x = v18;
    v20 = *(f32 *)(*(u64 *)v16 + 20);
    vct_A.y = v20;
    v21 = *(f32 *)(*(u64 *)v16 + 24);
    vct_A.z = v21;
    v22 = *(f32 *)(*(u64 *)v16 + 28);
    vct_A.w = v22;
    vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v62);
    v23 = &klass->_1.image + (u32)v12;
    vct_B = vct_A;
    v25 = v23[4];
    v24 = (v23 + 4);
    v26 = v25[4];
    vct_A.x = v26;
    v27 = *(f32 *)(*(u64 *)v24 + 20);
    vct_A.y = v27;
    v28 = *(f32 *)(*(u64 *)v24 + 24);
    vct_A.z = v28;
    v29 = *(f32 *)(*(u64 *)v24 + 28);
    vct_A.w = v29;
    v61 = 1.0 - v62;
    vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v61);
    vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    v30 = (u8)byte_57594F4;
    v6->InsideR = vct_A.x;
    if (v30)
      goto LABEL_36;
    goto LABEL_127;
    if (v54)
    {
LABEL_36:
      goto LABEL_37;
    }
LABEL_127:
LABEL_37:
    v31 = (u8)byte_5756436;
    v6->OutsideR = vct_A.y;
    if (v31)
      goto LABEL_38;
    goto LABEL_129;
    if (v55)
    {
LABEL_38:
      goto LABEL_39;
    }
LABEL_129:
LABEL_39:
    v32 = (u8)byte_5759934;
    v6->Soften = vct_A.z;
    if (v32)
      goto LABEL_40;
    goto LABEL_131;
    if (v56)
    {
LABEL_40:
LABEL_41:
      v33 = *(f32 *)(*(u64 *)v16 + 32);
      v34 = (u8)byte_5756437;
      v6->Bias = vct_A.w;
      if (v34)
      {
        goto LABEL_43;
      }
      else
      {
LABEL_43:
        vct_A.x = v33;
        v35 = *(f32 *)(*(u64 *)v16 + 36);
        goto LABEL_44;
      }
      vct_A.x = v33;
      v35 = *(f32 *)(*(u64 *)v16 + 36);
LABEL_44:
      vct_A.y = v35;
      v36 = *(f32 *)(*(u64 *)v16 + 40);
      vct_A.z = v36;
      vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v62);
      vct_B = vct_A;
      v37 = *(f32 *)(*(u64 *)v24 + 32);
      vct_A.x = v37;
      v38 = *(f32 *)(*(u64 *)v24 + 36);
      vct_A.y = v38;
      v39 = *(f32 *)(*(u64 *)v24 + 40);
      vct_A.z = v39;
      vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v61);
      vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
      v40 = (u8)byte_57594F4;
      v6->DiffuseR = vct_A.x;
      if (v40)
        goto LABEL_64;
      goto LABEL_155;
      if (v57)
      {
LABEL_64:
        goto LABEL_65;
      }
LABEL_155:
LABEL_65:
      v41 = (u8)byte_5756436;
      v6->DiffuseG = vct_A.y;
      if (v41)
        goto LABEL_66;
      goto LABEL_157;
      if (v58)
      {
LABEL_66:
LABEL_67:
        v42 = *(f32 *)(*(u64 *)v16 + 44);
        v43 = (u8)byte_5756437;
        v6->DiffuseB = vct_A.z;
        if (v43)
        {
          goto LABEL_69;
        }
        else
        {
LABEL_69:
          vct_A.x = v42;
          v44 = *(f32 *)(*(u64 *)v16 + 48);
          goto LABEL_70;
        }
        vct_A.x = v42;
        v44 = *(f32 *)(*(u64 *)v16 + 48);
LABEL_70:
        vct_A.y = v44;
        v45 = *(f32 *)(*(u64 *)v16 + 52);
        vct_A.z = v45;
        vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v62);
        vct_B = vct_A;
        v46 = *(f32 *)(*(u64 *)v24 + 44);
        vct_A.x = v46;
        v47 = *(f32 *)(*(u64 *)v24 + 48);
        vct_A.y = v47;
        v48 = *(f32 *)(*(u64 *)v24 + 52);
        vct_A.z = v48;
        vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v61);
        vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
        v49 = (u8)byte_57594F4;
        v6->AmbientR = vct_A.x;
        if (v49)
          goto LABEL_90;
        goto LABEL_181;
        if (v59)
        {
LABEL_90:
          goto LABEL_91;
        }
LABEL_181:
LABEL_91:
        v50 = (u8)byte_5756436;
        v6->AmbientG = vct_A.y;
        if (v50)
          goto LABEL_92;
        goto LABEL_183;
        if (v60)
        {
LABEL_92:
LABEL_93:
          v6->AmbientB = vct_A.z;
          return;
        }
LABEL_183:
        goto LABEL_93;
      }
LABEL_157:
      goto LABEL_67;
    }
LABEL_131:
    goto LABEL_41;
  }
}

// 0x22fefc0
f32 dds3PathBasicControlGetFovy(dds3PathBasicControl_t *pControl) {
  dds3PathBasicControl_t *v3;
  f32 result;
  fldResourcePathData_t *pFovy;
  f32 frame;
  u32 *pKey;
  u32 v8;
  fldResourcePathData_t *klass;
  s64 v10;
  f32 v11;
  s64 v12;
  u32 nKey;
  u32 v14;
  s64 v15;
  f32 v16;
  u32 v17;
  f32 v18;

  v3 = pControl;
  result = 0.0;
  if ((pControl->flag & 4) == 0)
    return result;
LABEL_5:
  pFovy = v3->pFovy;
  frame = v3->frame;
  pKey = pFovy->pKey;
  if (get_nKey(pFovy, 0) != 1)
  {
    v10 = 0;
    while (1)
    {
      v14 = pKey[v10];
      v15 = v10 + 1;
      v16 = v14;
      if (frame >= (f32)v14)
      {
        v17 = pKey[(s32)v15];
        if (frame < (f32)v17)
          break;
      }
      nKey = get_nKey(pFovy, 0);
      v10 = v15;
      if ((u32)v15 >= nKey - 1)
        goto LABEL_9;
    }
    v18 = (v17 - v14);
    klass = pFovy[1].klass;
    v12 = (s32)v15;
    v11 = (f32)(frame - v16) * (f32)(1.0 / v18);
    return (f32)((f32)(1.0 - v11) * *((f32 *)&klass->_1.byval_arg.data + v10))
         + (f32)(v11 * *((f32 *)&klass->_1.byval_arg.data + v12));
  }
LABEL_9:
  v8 = get_nKey(pFovy, 0);
  klass = pFovy[1].klass;
  v10 = v8 - 2;
  if (v8 == 1)
    return *(f32 *)&klass->_1.byval_arg.data + 0.0;
  v11 = 1.0;
  v12 = (s32)(v8 - 1);
  return (f32)((f32)(1.0 - v11) * *((f32 *)&klass->_1.byval_arg.data + v10))
       + (f32)(v11 * *((f32 *)&klass->_1.byval_arg.data + v12));
  v3 = pControl;
  result = 0.0;
  if ((pControl->flag & 4) != 0)
    goto LABEL_5;
  return result;
}

// 0x23000f0
bool dds3PathBasicControlNextStep(dds3PathBasicControl_t *pControl) {
  u32 flag;
  s32 mode;
  f32 v4;
  f32 frameMax;
  f32 frame;

  flag = pControl->flag;
  if ((flag & 8) != 0)
    return 1;
  mode = pControl->mode;
  if (mode == 1)
  {
    frame = pControl->frame;
    if (frame <= 0.0)
    {
      if ((flag & 0x20) == 0)
        return 0;
      frameMax = pControl->frameMax;
    }
    else
    {
      frameMax = frame + -1.0;
    }
    goto LABEL_14;
  }
  if (mode)
    return 1;
  v4 = pControl->frame;
  if (pControl->frameMax > v4)
  {
    frameMax = v4 + 1.0;
LABEL_14:
    pControl->frame = frameMax;
    return 1;
  }
  if ((flag & 0x20) == 0)
    return 0;
  pControl->frame = 0.0;
  return 1;
}

// 0x2302c80
void dds3PathBasicControlAlterMode(dds3PathBasicControl_t *pControl, DDS3_PATHBASIC_CONTROL mode) {
  pControl->mode = mode;
}

// 0x2302c90
DDS3_PATHBASIC_CONTROL dds3PathBasicPathControlGetMode(dds3PathBasicControl_t *pControl) {
  return pControl->mode;
}

// 0x2302ca0
void dds3PathBasicControlSetRatio(dds3PathBasicControl_t *pControl, f32 ratio) {
  pControl->frame = pControl->frameMax * ratio;
}

// 0x2302cc0
f32 dds3PathBasicControlGetRatio(dds3PathBasicControl_t *pControl) {
  return pControl->frame / pControl->frameMax;
}

// 0x2302cd0
void dds3PathBasicPause(dds3PathBasicControl_t *pControl) {
  pControl->flag |= 8u;
}

// 0x2302cf0
void dds3PathBasicPauseOff(dds3PathBasicControl_t *pControl) {
  pControl->flag &= ~8u;
}

// 0x2302d10
void dds3PathBasicLoopOn(dds3PathBasicControl_t *pControl) {
  pControl->flag |= 0x20u;
}

// 0x2302d30
void dds3PathBasicLoopOff(dds3PathBasicControl_t *pControl) {
  pControl->flag &= ~0x20u;
}
