#include "types.h"
#include "TNEFFECT_BLEND.h"
#include "dds3billboard.h"
#include "dds3kerneldraw.h"
#include "eff.h"
#include "effbehavior.h"
#include "effcachetexlist.h"
#include "effpolygontex.h"
#include "sbtl.h"
#include "sdf_vu0.h"
#include "sdfbase.h"
#include "sdfdraw.h"
#include "sdfquat.h"
#include "sdfsystem.h"
#include "sdftex.h"
#include "sdfvsync.h"

#define EFFPTEX_FLAG_END 1

typedef struct Standard Standard;
typedef struct effCacheTexList_Anim_t effCacheTexList_Anim_t;
typedef struct effPartsHandle_t effPartsHandle_t;
typedef struct effPolygonTexTemp_t effPolygonTexTemp_t;
typedef struct ptexHandle_t ptexHandle_t;
typedef struct sdfGrOt_t sdfGrOt_t;

struct effPolygonTexTemp_t {
    sdfVector4_t color;
    f32 rotate;
    f32 scale;
    effCacheTexList_Anim_t *CTexAnim;
};

static void *ptexFaceIndex;
static sdfGrOt_t *pOt_Table_semi;
static effPolygonTexTemp_t *temp_effPolygonTexTemp_t;

static void Update(ptexHandle_t *hPolygon, effPolygonTexTemp_t *wk);
static bool CheckOT(void);
static sdfGrOt_t *GetOT(TNEFFECT_BLEND blend);
static void Render(ptexHandle_t *hPolygon, effPolygonTexTemp_t *wk);

// 0x198dc20
ptexHandle_t *PartsCreate(Standard *pParts) {
  ptexHandle_t *v3;
  sdfVector4_t *v5;
  sdfVector4_t *v6;
  s32 v9;
  dds3Billboard_Basic_t *v11;
  Standard *klass;
  s64 naturalAligment;
  u8 *v16;
  sdfBinary *v17;
  s32 v18;
  s64 v19;
  Standard *v23;
  s64 v24;
  void *pData;
  s64 v26;
  Project_libsdf_sdfResourceUnit_c *v27;
  s32 name_low;
  s64 v29;
  s64 v30;
  effPartsData_t *data;
  void *v32;
  u16 v33;
  f32 monitor_low;
  f32 v35;
  s32 v36;
  s32 v37;
  f32 v38;
  s32 v39;
  Project_libsdf_sdfResourceUnit_c *v40;
  s32 v41;
  s64 v42;
  f32 v43;
  s32 v44;
  dds3Billboard_Basic_t *v46;
  u32 v48;
  ctexlHandle_t *v49;
  void *v50;
  s64 v51;
  dds3Billboard_Basic_t *v52;
  s32 v53;

  v3 = Allocate(ptexHandle_t);
  v5 = &v3->pos;
  *v5 = vf00;
  v6 = &v3->rot;
  v9 = (u8)byte_5756171;
  *v6 = vf00;
  *(u32 *)&v3->scale = 1065353216;
  v3->hBillboard = 0;
  v11 = &v3->hBillboard;
  v3->abgr = oneVector;
  v3->hCTexList = 0;
  if (!pParts)
    return v3;
  v3->type = pParts->param->type;
  klass = pParts->klass;
  if (pParts->klass->_2.naturalAligment < (u32)naturalAligment)
    goto LABEL_22;
  goto LABEL_21;
  if (pParts->klass->_2.naturalAligment < (u32)naturalAligment)
  {
LABEL_22:
    v16 = 0;
    goto LABEL_23;
  }
LABEL_21:
  if (klass->_2.typeHierarchy[naturalAligment - 1] != Project_effParts_t_Resource_Common)
    goto LABEL_22;
  pData = pParts->param->pData;
  if (pData)
  {
    if (pData->klass->_2.naturalAligment < (u32)v30 || pData->klass->_2.typeHierarchy[v30 - 1] != Project_effPartsData_t_Default)
    {
      goto LABEL_92;
    }
  }
  v16 = pData[1].klass;
LABEL_23:
  v17 = Allocate(sdfBinary);
  _ctor_36176832(v17, v16, 0);
  v18 = v3->type;
  if (v18 == 2)
  {
    v19 = Allocate(Project_effPolygonTex_Params_Loop_t);
    _ctor_26805328(v19, v17);
    *(u32 *)(v19 + 56) = ReadU32(v17, 0);
    *(u32 *)(v19 + 60) = ReadU32(v17, 0);
    *(u32 *)(v19 + 64) = ReadU32(v17, 0);
  }
  else
  {
    if (v18 != 1)
      goto LABEL_28;
    v19 = Allocate(Project_effPolygonTex_Params_Normal_t);
    _ctor_26805328(v19, v17);
    *(u32 *)(v19 + 56) = ReadU32(v17, 0);
  }
  *(f32 *)(v19 + 48) = ReadFloat(v17, 0);
  *(u8 *)(v19 + 52) = ReadU8(v17, 0) != 0;
  v3->param = v19;
LABEL_28:
  v23 = pParts->klass;
  if (pParts->klass->_2.naturalAligment < (u32)v24)
    goto LABEL_35;
  if (v23->_2.typeHierarchy[v24 - 1] == Standard)
  {
    data = pParts->data;
    v32 = data->pData;
    if (v32)
    {
      switch (data->type)
      {
        case 1u:
          v33 = 0;
          goto LABEL_76;
        case 2u:
          v32 = *(void *)((v32->klass->vtable._5_GetExtUnits.methodPtr)(v32, v32->klass->vtable._5_GetExtUnits.method) + 32);
          v33 = 1;
LABEL_76:
          v46 = dds3BillboardCreate(v33, v32);
          goto LABEL_82;
        case 4u:
          v48 = v32[1].klass;
          v46 = dds3BillboardGeneralCreate(v48);
LABEL_82:
          v49 = v46;
          v11 = v46;
          v50 = &v3->hBillboard;
          goto LABEL_87;
        case 7u:
          pData = *(void *)((v32->klass->vtable._5_GetExtUnits.methodPtr)(v32, v32->klass->vtable._5_GetExtUnits.method) + 32);
          if (pData)
          {
            if (pData->klass->_2.naturalAligment < (u32)v51 || pData->klass->_2.typeHierarchy[v51 - 1] != ctexlHandle_t_Resource)
            {
              goto LABEL_92;
            }
          }
          v49 = effCacheTexCreate(pData);
          v3->hCTexList = v49;
          v50 = &v3->hCTexList;
LABEL_87:
LABEL_88:
          v52 = v11;
          if (v52)
          {
            v53 = *(u32 *)(*(u64 *)((u64)v3->param + 24) + 20);
            dds3BillboardSetBlend(v52, v53);
          }
          break;
        default:
          goto LABEL_88;
      }
    }
  }
LABEL_35:
  if (v3->type != 2)
    return v3;
  pData = v3->param;
  if (pData)
  {
    if (pData->klass->_2.naturalAligment < (u32)v26 || pData->klass->_2.typeHierarchy[v26 - 1] != Project_effPolygonTex_Params_Loop_t)
    {
LABEL_92:
    }
  }
  v27 = pData[1].klass;
  name_low = LOBYTE(v27->_1.name);
  if (name_low == 1)
  {
    v29 = 0;
LABEL_54:
    monitor_low = LODWORD(pData[3].monitor);
    v35 = (f32)(1.0 - *(f32 *)(*(u64 *)(*(u64 *)&v27->_1.this_arg.bits + 8 * v29 + 32) + 16)) * monitor_low;
    if (v35 == INFINITY)
      v36 = 0x80000000;
    else
      v36 = v35;
    v37 = v3->frame_out;
    if (v37 < v36)
    {
      v37 = v35;
      v3->frame_out = v36;
    }
    goto LABEL_60;
  }
  if (name_low == 2)
  {
    v29 = 1;
    goto LABEL_54;
  }
  v37 = v3->frame_out;
  monitor_low = LODWORD(pData[3].monitor);
LABEL_60:
  v38 = (f32)(1.0 - *((f32 *)pData[1].monitor + 7)) * monitor_low;
  v39 = v38;
  if (v38 == INFINITY)
    v39 = 0x80000000;
  if (v37 < v39)
    v3->frame_out = v39;
  v40 = pData[2].klass;
  v41 = LOBYTE(v40->_1.name);
  if (v41 == 1)
  {
    v42 = 0;
  }
  else
  {
    if (v41 != 2)
      return v3;
    v42 = 1;
  }
  v43 = (f32)(1.0 - *(f32 *)(*(u64 *)(*(u64 *)&v40->_1.byval_arg.bits + 8 * v42 + 32) + 16))
      * (f32)HIDWORD(pData[3].monitor);
  v44 = v43;
  if (v43 == INFINITY)
    v44 = 0x80000000;
  if (v3->frame_out < v44)
    v3->frame_out = v44;
  return v3;
}

// 0x198e520
void Delete(effPartsHandle_t *handle) {
  void *klass;
  ctexlHandle_t *monitor;
  void *v6;
  void *p_monitor;
  void *v8;
  void *gameObject;

  klass = handle[4].klass;
  if (klass)
  {
    dds3BillboardDelete(klass);
  }
  monitor = handle[4].monitor;
  if (monitor)
    effCacheTexDelete(monitor);
  v8 = handle[5].monitor;
  p_monitor = &handle[5].monitor;
  v6 = v8;
  if (v8)
  {
    gameObject = get_gameObject(v6[5], 0);
    DestroyImmediate_61008224(gameObject, 0);
    Destroy(p_monitor);
    p_monitor = 0;
  }
}

// 0x198e660
ptexHandle_t *Copy(effPartsHandle_t *handle) {
  ptexHandle_t *v4;
  effOption *option;

  v4 = PartsCreate(0);
  v4->type = HIDWORD(handle[3].klass);
  option = handle[3].option;
  v4->param = (effPolygonTex_Params_t *)option;
  ResourceCopy(v4, handle);
  return v4;
}

// 0x198e730
void ResourceCopy(effPartsHandle_t *dst, effPartsHandle_t *src) {
  void *klass;
  void *v8;
  dds3Billboard_Basic_t *v9;
  ctexlHandle_t *v10;
  u64 *p_monitor;
  ctexlHandle_t *monitor;
  ctexlHandle_t *v13;

  klass = src[4].klass;
  if (klass)
  {
    v8 = dst[4].klass;
    if (v8)
    {
      dds3BillboardDelete(v8);
      klass = src[4].klass;
    }
    v9 = dds3BillboardCopy(klass);
    dst[4].klass = (effPartsHandle_t *)v9;
    dds3BillboardSetBlend(dst[4].klass, *(u32 *)(*(u64 *)&dst[3].option->adjustRGBA.x + 20));
  }
  else
  {
    monitor = dst[4].monitor;
    p_monitor = &dst[4].monitor;
    v10 = monitor;
    if (monitor)
      effCacheTexDelete(v10);
    v13 = Copy(src[4].monitor);
    *p_monitor = v13;
  }
}

// 0x198e940
void Draw(effPartsHandle_t *handle) {
  Update(handle, temp_effPolygonTexTemp_t);
  if (drawSkip)
    return;
  Render(handle, temp_effPolygonTexTemp_t);
}

// 0x198fba0
void PositionSet(effPartsHandle_t *handle, const sdfVector4_t *pPos) {
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

// 0x198fc50
void RotateSet(effPartsHandle_t *handle, const sdfVector4_t *pRot) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;

  w = pRot->w;
  z = pRot->z;
  y = pRot->y;
  x = pRot->x;
  *(f32 *)&handle[2].klass = z;
  *((f32 *)&handle[2].klass + 1) = w;
  *(f32 *)&handle[1].option = x;
  *((f32 *)&handle[1].option + 1) = y;
}

// 0x198fd00
void ColorSet(effPartsHandle_t *handle, const sdfVector4_t *abgr) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;

  w = abgr->w;
  z = abgr->z;
  y = abgr->y;
  x = abgr->x;
  *((f32 *)&handle[2].option + 1) = z;
  *(f32 *)&handle[3].klass = w;
  *((f32 *)&handle[2].monitor + 1) = x;
  *(f32 *)&handle[2].option = y;
}

// 0x198fdb0
void ScaleSet(effPartsHandle_t *handle, f32 scale) {
  *(f32 *)&handle[2].monitor = scale;
}

// 0x198eac0
static void Update(ptexHandle_t *hPolygon, effPolygonTexTemp_t *wk) {
  effPolygonTexTemp_t *v3;
  u64 v6;
  f32 z;
  f32 w;
  u32 type;
  f32 v10;
  f32 v11;
  effPolygonTex_Params_t *param;
  s64 naturalAligment;
  s64 frame;
  s64 klass_low;
  f32 v16;
  effPolygonTex_Params_t *v17;
  effPolygonTexMesh *v18;
  void *v19;
  MeshEditPCU *v20;
  void *transform;
  void *v23;
  s64 v25;
  s64 v30;
  s32 v31;
  u32 flags;
  f32 v33;
  f32 v34;
  effBehavior_RGBParams_t *rgb;
  f32 frame_out;
  s32 v37;
  s64 v38;
  Color *point;
  f32 v40;
  f32 *v41;
  f32 v42;
  f32 v43;
  Color *v44;
  f32 v45;
  bool v46;
  f32 v47;
  f32 v48;
  Color *v49;
  f32 *alpha;
  f32 v51;
  f32 v52;
  effBehavior_SR_Params_t *scale;
  Float *v54;
  f32 klass_high;
  f32 rate;
  f32 v57;
  f32 v58;
  f32 v59;
  f32 start;
  f32 v61;
  effBehavior_SR_Params_t *rotate;
  f32 v63;
  s64 monitor_low;
  s64 v65;
  f32 v66;
  f32 v67;
  f32 v68;
  f32 v69;
  f32 v70;
  s32 v71;
  f32 v72;
  f32 v73;
  f32 v74;
  f64 v75;
  u64 v76;
  u64 v77;
  s64 v78;
  s32 v79;
  __int128 v80;
  __int128 v81;
  sdfVector4_t v82;

  v3 = wk;
  v6 = *(u64 *)&zeroVector.x;
  z = zeroVector.z;
  w = zeroVector.w;
  if (hPolygon->pMesh)
  {
    type = hPolygon->type;
    if (type != 2)
    {
LABEL_7:
      v10 = 0.0;
      v11 = 0.0;
      if (type != 1)
        goto LABEL_13;
      param = hPolygon->param;
      {
        frame = hPolygon->frame;
        klass_low = LODWORD(param[1].klass);
        if (frame >= klass_low)
          return;
        v82 = effColorAnimation(param->rgb, param->alpha, frame, klass_low);
        z = v82.z;
        w = v82.w;
        v16 = effSRAnimation(hPolygon->param->scale, (f32)hPolygon->frame, (f32)LODWORD(param[1].klass));
        v17 = hPolygon->param;
        v11 = v16 * (f32)(v17->area * hPolygon->scale);
        v10 = effSRAnimation(v17->rotate, (f32)hPolygon->frame, (f32)LODWORD(param[1].klass));
        v6 = *(u64 *)&v82.x;
LABEL_13:
        if (hPolygon->hBillboard)
          goto LABEL_14;
        goto LABEL_73;
      }
LABEL_88:
    }
  }
  else
  {
    v76 = *(u64 *)&zeroVector.x;
    v18 = Allocate(effPolygonTexMesh);
    _ctor(v18, 0);
    v19 = Make("effect", 0);
    v20 = Allocate(MeshEditPCU);
    _ctor(v20, 0);
    transform = get_transform(v19, 0);
    v23 = get_transform(hook, 0);
    SetParent_61042560(transform, v23, 0, 0);
    (v19->klass[1]._1.declaringType)(v19, v20, v19->klass[1]._1.parent);
    SetOption(v19, hPolygon->option, 0);
    SetAutoHide(v19, 1, 0);
    v20->vertexCount = 4;
    v20->indexCount = ptexFaceIndex.m_Length;
    v18->mesh = v19;
    v18->edit = v20;
    v78 = *(u64 *)&v18->job.texWidth;
    v25 = *(u64 *)&v18->job.tex.width;
    v79 = *(u32 *)((char *)v18 + 148);
    v80 = *(_OWORD *)&v18->job;
    v81 = *(_OWORD *)&v18->job.index;
    *(u32 *)&v18->job.mulF4 = 0;
    *(_OWORD *)&v18->job = v80;
    *(_OWORD *)&v18->job.index = v81;
    *(u64 *)&v18->job.texWidth = v78;
    *(u64 *)&v18->job.tex = 0;
    *(u64 *)&v18->job.tex.width = v25;
    *(u32 *)((char *)v18 + 148) = v79;
    v18->job.tex.uv0 = zeroVector;
    v18->job.tex.uv1 = oneVector;
    v18->job.table = ptexFaceIndex;
    hPolygon->pMesh = v18;
    v6 = v76;
    type = hPolygon->type;
    if (type != 2)
      goto LABEL_7;
  }
  param = hPolygon->param;
  if (param)
  {
    if (param->klass->_2.naturalAligment < (u32)v30 || param->klass->_2.typeHierarchy[v30 - 1] != Project_effPolygonTex_Params_Loop_t)
    {
      goto LABEL_88;
    }
  }
  v31 = hPolygon->frame;
  flags = hPolygon->flags;
  v33 = v31;
  v34 = (v31 - hPolygon->frame_end);
  rgb = param->rgb;
  frame_out = hPolygon->frame_out;
  v37 = rgb->type;
  if (v37 == 2)
  {
    v38 = 1;
  }
  else
  {
    if (v37 != 1)
    {
      if (!rgb->type)
      {
        v6 = *(u64 *)&rgb->start.x;
        z = rgb->start.z;
        w = rgb->start.w;
      }
      goto LABEL_52;
    }
    v38 = 0;
  }
  point = rgb->point;
  v40 = LODWORD(param[1].klass);
  v41 = point[v38];
  v42 = v41[4];
  if ((f32)(v42 * v40) <= v33)
  {
    if ((flags & 1) != 0 && (v48 = (f32)(1.0 - v42) * v40, (f32)(frame_out - v48) <= v34))
    {
      if (v34 >= frame_out)
      {
        v6 = *(u64 *)&rgb->end.x;
        z = rgb->end.z;
      }
      else
      {
        *(f32 *)&v75 = (f32)(v34 - (f32)(frame_out - v48)) / v48;
        LODWORD(v6) = (loc_19965E0)(0, wk, v41[5], v41[6], v41[7], v41[8], rgb->end.x, rgb->end.y, rgb->end.z, rgb->end.w, v75);
        z = v70;
        HIDWORD(v6) = v71;
        v40 = LODWORD(param[1].klass);
      }
    }
    else
    {
      v49 = point[0];
      v6 = *(u64 *)&v49->color.x;
      z = v49->color.z;
    }
  }
  else
  {
    v43 = v33 / (f32)(v42 * v40);
    v44 = point[0];
    if (v43 <= 1.0)
      v45 = v33 / (f32)(v42 * v40);
    else
      v45 = 1.0;
    v46 = v43 < 0.0;
    v47 = 0.0;
    if (!v46)
      v47 = v45;
    v6 = vadd_f32(*(float32x2_t *)&rgb->start.x, vmul_n_f32(vsub_f32(*(float32x2_t *)&v44->color.x, *(float32x2_t *)&rgb->start.x), v47)).n64_u64[0];
    z = rgb->start.z + (f32)(v47 * (f32)(v44->color.z - rgb->start.z));
  }
  alpha = param->alpha;
  v51 = alpha[6] * v40;
  if (v51 <= v33)
  {
    if ((flags & 1) != 0 && (v52 = (f32)(1.0 - alpha[7]) * v40, (f32)(frame_out - v52) <= v34))
    {
      w = 0.0;
      if (v34 < frame_out)
        w = (f32)(1.0 - (f32)((f32)(v34 - (f32)(frame_out - v52)) / v52)) * alpha[4];
    }
    else
    {
      w = alpha[4];
    }
  }
  else
  {
    w = alpha[4] * (f32)((f32)hPolygon->frame / v51);
  }
LABEL_52:
  scale = param->scale;
  if ((u32)scale->type - 1 >= 2)
  {
    start = 0.0;
    if (!scale->type)
      start = scale->start;
  }
  else
  {
    v54 = scale->point[0];
    klass_high = HIDWORD(param[1].klass);
    rate = v54->rate;
    if ((f32)(rate * klass_high) <= v33)
    {
      if ((flags & 1) != 0 && (v61 = (f32)(1.0 - rate) * klass_high, (f32)(frame_out - v61) <= v34))
      {
        if (v34 >= frame_out)
        {
          start = scale->end;
        }
        else
        {
          v72 = (f32)(v34 - (f32)(frame_out - v61)) / v61;
          if (v72 <= 1.0)
            v73 = v72;
          else
            v73 = 1.0;
          v46 = v72 < 0.0;
          v74 = 0.0;
          if (!v46)
            v74 = v73;
          start = v54->sr + (f32)(v74 * (f32)(scale->end - v54->sr));
        }
      }
      else
      {
        start = v54->sr;
      }
    }
    else
    {
      v57 = v33 / (f32)(rate * klass_high);
      if (v57 <= 1.0)
        v58 = v33 / (f32)(rate * klass_high);
      else
        v58 = 1.0;
      v46 = v57 < 0.0;
      v59 = 0.0;
      if (!v46)
        v59 = v58;
      start = scale->start + (f32)(v59 * (f32)(v54->sr - scale->start));
    }
  }
  rotate = param->rotate;
  v63 = rotate->start;
  monitor_low = LODWORD(param[1].monitor);
  if ((u32)monitor_low)
  {
    v65 = hPolygon->frame % monitor_low;
    v66 = (f32)v65 / (f32)(u32)monitor_low;
    if (v66 <= 1.0)
      v67 = (f32)v65 / (f32)(u32)monitor_low;
    else
      v67 = 1.0;
    v46 = v66 < 0.0;
    v68 = 0.0;
    if (!v46)
      v68 = v67;
    v63 = v63 + (f32)((f32)(rotate->end - v63) * v68);
  }
  v11 = start * (f32)(param->area * hPolygon->scale);
  v10 = v63 * 6.2831855;
  if (hPolygon->hBillboard)
  {
LABEL_14:
    *(u64 *)&v3->color.x = v6;
    v3->color.z = z;
    v3->color.w = w;
    v3->rotate = v10;
    v3->scale = v11;
    if (get_STOP(0))
      return;
    goto LABEL_15;
  }
LABEL_73:
  v77 = v6;
  effCacheTexAnimGet(hPolygon->hCTexList, hPolygon->frame, v3->CTexAnim);
  v69 = v10 + v3->CTexAnim->rotate;
  *(u64 *)&v3->color.x = v77;
  v3->color.z = z;
  v3->color.w = w;
  v3->rotate = v69;
  v3->scale = v11;
  if (!get_STOP(0))
LABEL_15:
    ++hPolygon->frame;
}

// 0x198fe40
static bool CheckOT(void) {
  if (!CheckRun())
    return 0;
  return epl_otchkflg;
}

// 0x198ff00
static sdfGrOt_t *GetOT(TNEFFECT_BLEND blend) {
  if (!!CheckRun())
  {
    if (epl_otchkflg)
      goto LABEL_13;
  }
  return effOtGet(blend);
LABEL_13:
  return pOt_Table_semi[blend];
}

// 0x198f290
static void Render(ptexHandle_t *hPolygon, effPolygonTexTemp_t *wk) {
  u32 type;
  effPolygonTexMesh *pMesh;
  u32 *param;
  sdfDrawTag_t *v9;
  f32 rotate;
  struct sdfVector4_t pos;
  f32 v14;
  _OWORD *p_x;
  f32 v17;
  __int128 v18;
  void *mesh;
  __int128 v20;
  void *transform;
  f32 *v23;
  void *v24;
  f32 v25;
  f32 v26;
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
  f32 v40;
  f32 v41;
  void *v42;
  f32 scale;
  dds3Billboard_Basic_t *hBillboard;
  s32 frame;
  void *LinkOt;
  f32 *v48;
  effOption *option;
  s32 FieldOt;
  sdfGrOt_t *OT;
  s32 v55;
  _BOOL4 zTest;
  s32 blend;
  struct sdfVector4_t rot;
  sdfMatrix4_t v62;
  sdfMatrix4_t v63;
  sdfMatrix4_t v64;
  sdfVector4_t Row;
  sdfQuaternion_t rotation;
  sdfVector3_t v67;
  sdfVector3_t v68;
  sdfQuaternion_t v69;

  type = hPolygon->type;
  pMesh = hPolygon->pMesh;
  memset(&v64, 0, sizeof(v64));
  memset(&v63, 0, sizeof(v63));
  if (type != 1)
    goto LABEL_8;
  param = hPolygon->param;
  if (hPolygon->frame < (s64)param[14])
  {
LABEL_8:
    v9 = Allocate(sdfDrawTag_t);
    _ctor(v9, 0);
    sdfDrawTagInit(v9);
    rotate = wk->rotate;
    rot = hPolygon->rot;
    vct_A = rot;
    ToMatrix();
    pos = hPolygon->pos;
    vct_A = pos;
    vct_A.w = 1.0;
    SetRow(&mtx_A, 3, vct_A, 0);
    v14 = 0.5;
    p_x = &vf00.x;
    v17 = rotate * v14;
    v18 = p_x[6];
    *(_OWORD *)&v64.m03 = p_x[7];
    *(_OWORD *)&v64.m02 = v18;
    mesh = pMesh->mesh;
    v20 = p_x[4];
    *(_OWORD *)&v64.m01 = p_x[5];
    *(_OWORD *)&v64.m00 = v20;
    transform = get_transform(mesh, 0);
    Row = GetRow(&v64, 3, 0);
    v23 = &modVec.x;
    v67.y = Row.y * v23[7];
    v67.x = Row.x * v23[6];
    v67.z = Row.z * v23[8];
    set_localPosition(transform, v67, 0);
    v24 = get_transform(pMesh->mesh, 0);
    get_transpose(&v62, &v64, 0);
    v63 = v62;
    rotation = get_rotation(&v63, 0);
    v25 = (s32)(v17 * 0.15915494);
    if ((f32)(v17 * 0.15915494) == INFINITY)
      v25 = -2147500000.0;
    v26 = -1.0;
    v27 = (f32)(v17 * 0.15915494) - v25;
    if (v27 <= v14)
    {
      if (v27 < -0.5)
        v27 = v27 + 1.0;
    }
    else
    {
      v27 = v27 + -1.0;
    }
    if (v27 <= 0.25)
    {
      if (v27 < -0.25)
        v27 = -0.5 - v27;
    }
    else
    {
      v27 = v14 - v27;
    }
    v28 = v27 * 4.0;
    v29 = v28 * v28;
    v30 = v28 * 1.5708;
    v31 = v28 * (f32)(v28 * v28);
    v32 = v31 * -0.6459637;
    v33 = v29 * v31;
    v34 = (f32)((f32)(v30 + v32) + (f32)(v33 * 0.07968968)) + (f32)((f32)(v29 * v33) * -0.0046737655);
    v35 = (f32)(v29 * (f32)(v29 * v33)) * 0.00015148419;
    v36 = (f32)(v17 + 1.5708) * 0.15915494;
    v37 = (s32)v36;
    if (v36 == INFINITY)
      v37 = -2147500000.0;
    v38 = v36 - v37;
    if (v38 <= v14)
    {
      if (v38 >= -0.5)
        goto LABEL_37;
      v26 = 1.0;
    }
    v38 = v38 + v26;
LABEL_37:
    v39 = v34 + v35;
    if (v38 <= 0.25)
    {
      if (v38 < -0.25)
        v38 = -0.5 - v38;
    }
    else
    {
      v38 = v14 - v38;
    }
    v40 = v38 * 4.0;
    v41 = (f32)((f32)((f32)((f32)(v40 * 1.5708) + (f32)((f32)(v40 * (f32)(v40 * v40)) * -0.6459637)) + (f32)((f32)((f32)(v40 * v40) * (f32)(v40 * (f32)(v40 * v40))) * 0.07968968)) + (f32)((f32)((f32)(v40 * v40) * (f32)((f32)(v40 * v40) * (f32)(v40 * (f32)(v40 * v40)))) * -0.0046737655))
        + (f32)((f32)((f32)(v40 * v40) * (f32)((f32)(v40 * v40) * (f32)((f32)(v40 * v40) * (f32)(v40 * (f32)(v40 * v40))))) * 0.00015148419);
    v69.z = (f32)((f32)((f32)(rotation.w * 0.0) + (f32)(rotation.z * v41)) - (f32)(rotation.x * v39))
                 - (f32)(rotation.y * 0.0);
    v69.y = (f32)((f32)(rotation.z * 0.0) + (f32)((f32)(rotation.y * v41) - (f32)(rotation.w * v39)))
                 - (f32)(rotation.x * 0.0);
    v69.w = (f32)((f32)(rotation.y * v39) + (f32)((f32)(rotation.w * v41) - (f32)(rotation.x * 0.0)))
                 - (f32)(rotation.z * 0.0);
    v69.x = (f32)(rotation.z * v39)
                 + (f32)((f32)(rotation.y * 0.0) + (f32)((f32)(rotation.w * 0.0) + (f32)(rotation.x * v41)));
    set_localRotation(v24, v69, 0);
    v42 = get_transform(pMesh->mesh, 0);
    scale = wk->scale;
    v68.y = modPos.y * scale;
    v68.x = modPos.x * scale;
    v68.z = modPos.z * scale;
    set_localScale(v42, v68, 0);
    SetColor(pMesh->mesh, (sdfVector4_t)vmulq_f32((float32x4_t)hPolygon->abgr, (float32x4_t)wk->color));
    hBillboard = hPolygon->hBillboard;
    if (hBillboard)
    {
      frame = hPolygon->frame;
      SetAnimKey(hBillboard, frame);
      LinkOt = dds3BillboardTexHandleAndUVGet(hPolygon->hBillboard, &pMesh->job.tex);
    }
    else
    {
      LinkOt = effCacheTexImageLoadLinkOt(hPolygon->hCTexList, wk->CTexAnim);
      v48 = wk->CTexAnim->scale;
      pMesh->job.tex.width = v48[0];
      pMesh->job.tex.height = v48[1];
      pMesh->job.mulF4 = sdfTexScaleMulF4(LinkOt);
      pMesh->job.texWidth = (LinkOt->klass->vtable._5_get_width.methodPtr)(LinkOt, LinkOt->klass->vtable._5_get_width.method);
      pMesh->job.texHeight = (LinkOt->klass->vtable._7_get_height.methodPtr)(LinkOt, LinkOt->klass->vtable._7_get_height.method);
    }
    (pMesh->mesh->klass->vtable._7_SetTexture.methodPtr)(pMesh->mesh, LinkOt, pMesh->mesh->klass->vtable._7_SetTexture.method);
    (pMesh->klass->vtable._5_PreUpdate.methodPtr)(pMesh, pMesh->klass->vtable._5_PreUpdate.method);
    option = hPolygon->option;
    if (!option || (FieldOt = option->FieldOt, FieldOt < 0))
    {
      blend = hPolygon->param->alpha->blend;
      OT = GetOT(blend);
      zTest = hPolygon->param->zTest;
      goto LABEL_71;
    }
    else
    {
      FieldOt = hPolygon->option->FieldOt;
      OT = Ot[FieldOt];
      v55 = hPolygon->param->alpha->blend;
      effSetAlphaPacket(v9, v55);
      zTest = hPolygon->param->zTest;
      goto LABEL_71;
    }
LABEL_71:
    effZTestOff(v9, zTest);
    sdfDrawTagLink(v9, pMesh->mesh->packet);
    effZTestOn(v9, hPolygon->param->zTest);
    sdfDrawTagLinkOt(OT, v9);
    return;
  }
}
