#include "types.h"
#include "dds3billboard.h"
#include "dds3kerneldraw.h"
#include "eff2d.h"
#include "effbehavior.h"
#include "effcachetexlist.h"
#include "effparts.h"
#include "sdf_prim.h"
#include "sdfdraw.h"
#include "sdfsystem.h"
#include "sdftex.h"
#include "sdfvsync.h"

typedef struct Standard Standard;
typedef struct eff2dHandle_t eff2dHandle_t;
typedef struct effCacheTexList_Anim_t effCacheTexList_Anim_t;
typedef struct effPartsHandle_t effPartsHandle_t;

static effCacheTexList_Anim_t *temp_effCacheTexList_Anim_t;

// 0x1997cb0
eff2dHandle_t *eff2PartsCreate(Standard *pParts) {
  eff2dHandle_t *v3;
  u8 *v5;
  sdfBinary *v6;
  eff2D_Params_t *v7;
  ctexlHandle_t_Resource *v8;
  void *v9;
  u16 v10;
  void *v11;
  void *v12;
  dds3Billboard_Basic_t *v13;
  s64 naturalAligment;
  u32 header_flag;
  ctexlHandle_t *v16;
  void *p_hBillboard;
  s64 v18;

  v3 = (eff2dHandle_t *)Allocate(eff2dHandle_t);
  _ctor(v3, 0);
  v3->abgr = oneVector;
  v3->hBillboard = 0;
  v3->hCTexList = 0;
  if (pParts)
  {
    v3->type = pParts->param->type;
    v5 = effParamsGet(pParts);
    v6 = Allocate(sdfBinary);
    _ctor_36176832(v6, v5, 0);
    v7 = Allocate(eff2D_Params_t);
    _ctor_26636240(v7, v6, 0);
    v3->param = v7;
    v8 = effDataGet(pParts);
    if (v8)
    {
      v9 = v8;
      switch (pParts->data->type)
      {
        case 1u:
          v10 = 0;
          v11 = v9;
          goto LABEL_16;
        case 2u:
          v12 = *(void *)((v8->klass->vtable._5_GetExtUnits.methodPtr)(v8, v8->klass->vtable._5_GetExtUnits.method) + 32);
          v10 = 1;
          v11 = v12;
LABEL_16:
          v13 = dds3BillboardCreate(v10, v11);
          goto LABEL_22;
        case 4u:
          if (v8->klass->_2.naturalAligment < (u32)naturalAligment || v8->klass->_2.typeHierarchy[naturalAligment - 1] != Project_effPartsData_t_General)
          {
            goto LABEL_29;
          }
          header_flag = v8->header_flag;
          v13 = dds3BillboardGeneralCreate(header_flag);
LABEL_22:
          v16 = v13;
          v3->hBillboard = v13;
          p_hBillboard = &v3->hBillboard;
          goto LABEL_27;
        case 7u:
          v8 = *(ctexlHandle_t_Resource *)((v8->klass->vtable._5_GetExtUnits.methodPtr)(v8, v8->klass->vtable._5_GetExtUnits.method) + 32);
          if (v8)
          {
            if (v8->klass->_2.naturalAligment < (u32)v18 || v8->klass->_2.typeHierarchy[v18 - 1] != ctexlHandle_t_Resource)
            {
LABEL_29:
            }
          }
          v16 = effCacheTexCreate(v8);
          v3->hCTexList = v16;
          p_hBillboard = &v3->hCTexList;
LABEL_27:
          break;
        default:
          return v3;
      }
    }
  }
  return v3;
}

// 0x1997fd0
void eff2Delete(effPartsHandle_t *handle) {
  void *monitor;
  effOption *option;
  effPartsHandle_t *v6;
  void *v7;
  effPartsHandle_t *klass;
  void *gameObject;

  monitor = handle[2].monitor;
  if (monitor)
  {
    dds3BillboardDelete(monitor);
  }
  option = handle[2].option;
  if (option)
    effCacheTexDelete(option);
  klass = handle[3].klass;
  v7 = &handle[3];
  v6 = klass;
  if (klass)
  {
    gameObject = get_gameObject(*(void *)&v6->_1.byval_arg.bits, 0);
    DestroyImmediate_61008224(gameObject, 0);
    Destroy(v7);
    v7 = 0;
  }
}

// 0x1998110
eff2dHandle_t *Copy(effPartsHandle_t *handle) {
  effPartsHandle_t *v4;
  eff2D_Params_t *klass;
  eff2D_Params_t *v6;

  v4 = eff2PartsCreate(0);
  klass = handle[2].klass;
  v6 = Allocate(eff2D_Params_t);
  _ctor_26637744(v6, klass, 0);
  v4[2].klass = (effPartsHandle_t *)v6;
  eff2ResourceCopy(v4, handle);
  return (eff2dHandle_t *)v4;
}

// 0x1998220
void eff2ResourceCopy(effPartsHandle_t *dst, effPartsHandle_t *src) {
  void *monitor;
  effPartsHandle_t *p_monitor;
  void *v9;
  void *v10;
  effOption *v11;
  ctexlHandle_t *v12;
  effOption *option;

  monitor = src[2].monitor;
  if (monitor)
  {
    v10 = dst[2].monitor;
    p_monitor = &dst[2].monitor;
    v9 = v10;
    if (v10)
    {
      dds3BillboardDelete(v9);
      monitor = src[2].monitor;
    }
    v11 = dds3BillboardCopy(monitor);
  }
  else
  {
    option = dst[2].option;
    p_monitor = &dst[2].fields;
    v12 = option;
    if (option)
      effCacheTexDelete(v12);
    v11 = Copy(src[2].option);
  }
  p_monitor->option = v11;
}

// 0x19983f0
void eff2Draw(effPartsHandle_t *handle) {
  s32 option_high;
  s64 data_low;
  s64 klass;
  void *v9;
  void *transform;
  void *v12;
  MeshEdit *edit;
  void *v16;
  const MethodInfo_3013120 *v17;
  Unity_Collections_NativeArray_T__o v18;
  __int128 v19;
  __int128 v20;
  s32 v24;
  sdfGrOt_t *v26;
  f32 v27;
  f32 v28;
  dds3Billboard_Basic_t *monitor;
  f32 v30;
  void *LinkOt;
  effCacheTexList_Anim_t *p_temp_effCacheTexList_Anim_t;
  effCacheTexList_Anim_t *v34;
  f32 rotate;
  f32 v36;
  f32 v37;
  effPartsHandle_t *v38;
  f32 v39;
  f32 v40;
  f32 v41;
  s32 data_high;
  f32 v43;
  f32 v44;
  u32 bits;
  s32 v46;
  f32 v47;
  f32 v48;
  f32 v49;
  f32 v50;
  f32 v51;
  f32 v52;
  f32 v53;
  f32 v54;
  f32 v55;
  s32 v56;
  f32 v57;
  f32 v58;
  f32 v59;
  s32 v60;
  f32 v61;
  f32 v62;
  f32 v63;
  f32 v64;
  f32 v65;
  f32 v66;
  f32 v67;
  f32 v68;
  f32 v69;
  s32 v70;
  s32 v71;
  s32 v72;
  f32 v73;
  f32 v74;
  f32 v75;
  f32 v76;
  f32 v77;
  s32 v78;
  s32 v79;
  s32 v80;
  f32 v81;
  f32 v82;
  f32 v83;
  s32 v84;
  s32 v85;
  s32 v86;
  s32 v87;
  f32 v88;
  s32 v89;
  s32 v90;
  s64 v91;
  sdfDrawTag_t *v92;
  void *v93;
  SDF_GS_ALPHA *OPAQUE_ALPHA_ELEM_local;
  u64 **v96;
  u64 *p_image;
  f32 v100;
  f32 v101;
  f32 v102;
  __int128 v103;
  __int128 v104;
  Unity_Collections_NativeArray_T__o v105;
  __int128 v106;
  __int128 v107;
  Unity_Collections_NativeArray_T__o v108;
  Unity_Collections_NativeArray_Vector3__o v109;
  sdfVector4_t v110;

  v108 = (Unity_Collections_NativeArray_T__o)0;
  option_high = HIDWORD(handle[1].option);
  data_low = LODWORD(handle[2].klass->_1.this_arg.data);
  if ((u32)data_low && option_high >= data_low)
    return;
  klass = handle[3].klass;
  if (klass)
  {
    goto LABEL_10;
  }
  else
  {
    klass = Allocate(eff2dMesh);
    _ctor(klass, 0);
    v9 = Make("effect", 0);
    transform = get_transform(v9, 0);
    v12 = get_transform(hook, 0);
    SetParent_61042560(transform, v12, 0, 0);
    InitSquare(v9, 1, 0);
    v9->type = 0;
    SetOption(v9, handle->option, 0);
    SetAutoHide(v9, 1, 0);
    *(u64 *)(klass + 40) = v9;
    edit = v9->edit;
    if (!edit)
    {
      *(u64 *)(klass + 48) = 0;
      v16 = (klass + 48);
    }
    v109.m_Buffer = &v108;
    *(u64 *)&v109.m_Length = *(u32 *)(*(u64 *)(klass + 48) + 96);
    __ctor(v109, 4, 0, Method_Unity_Collections_NativeArray_Vector3___ctor__, v17);
    _Copy_50413344((Unity_Collections_NativeArray_T__o)marker, 0, v108, v108.m_Length - *(u64 *)&marker.m_Length, *(u64 *)&marker.m_Length);
    v18 = v108;
    v106 = *(_OWORD *)(klass + 120);
    v107 = *(_OWORD *)(klass + 136);
    v19 = *(_OWORD *)(klass + 56);
    v20 = *(_OWORD *)(klass + 72);
    *(void *)(klass + 152) = v108;
    v103 = v19;
    v104 = v20;
    v105 = v18;
    *(u64 *)(klass + 168) = 0;
    *(_OWORD *)(klass + 120) = v106;
    *(_OWORD *)(klass + 136) = v107;
    *(_OWORD *)(klass + 56) = v103;
    *(_OWORD *)(klass + 72) = v104;
    *(void *)(klass + 88) = v105;
    *(void *)(klass + 104) = indexSquare;
    v24 = (u8)byte_5755D39;
    *(sdfVector2_t *)(klass + 184) = zeroVector;
    *(sdfVector2_t *)(klass + 192) = oneVector;
    handle[3].klass = (effPartsHandle_t *)klass;
LABEL_10:
    goto LABEL_11;
  }
LABEL_11:
  if (drawSkip)
  {
    if (get_STOP(0))
      return;
    goto LABEL_14;
  }
  v26 = Ot[109];
  v110 = effColorAnimation(handle[2].klass->_1.name, handle[2].klass->_1.namespaze, option_high, data_low);
  v27 = effSRAnimation(handle[2].klass->_1.byval_arg.data, (f32)option_high, (f32)(u32)data_low);
  v28 = effSRAnimation(*(effBehavior_SR_Params_t *)&handle[2].klass->_1.byval_arg.bits, (f32)option_high, (f32)(u32)data_low);
  monitor = handle[2].monitor;
  v30 = v28;
  if (monitor)
  {
    SetAnimKey(monitor, option_high);
    LinkOt = dds3BillboardTexHandleAndUVGet(handle[2].monitor, (klass + 168));
  }
  else
  {
    p_temp_effCacheTexList_Anim_t = &temp_effCacheTexList_Anim_t;
    v34 = p_temp_effCacheTexList_Anim_t;
    effCacheTexAnimGet(handle[2].option, option_high, p_temp_effCacheTexList_Anim_t);
    LinkOt = effCacheTexImageLoadLinkOt(handle[2].option, v34);
    rotate = v34->rotate;
    v30 = v30 + rotate;
    v36 = sdfTexScaleMulF4(LinkOt);
    *(f32 *)(klass + 176) = (f32)(v34->scale[0] * (f32)((LinkOt->klass->vtable._5_get_width.methodPtr)(LinkOt, LinkOt->klass->vtable._5_get_width.method) >> 1))
                            / v36;
    *(f32 *)(klass + 180) = (f32)(v34->scale[1] * (f32)((LinkOt->klass->vtable._7_get_height.methodPtr)(LinkOt, LinkOt->klass->vtable._7_get_height.method) >> 1))
                            / v36;
  }
  (*(**(u64 **)(klass + 40) + 424))(*(u64 *)(klass + 40), LinkOt, *(u64 *)(**(u64 **)(klass + 40) + 432));
  v37 = -1.0;
  v38 = handle[2].klass;
  v39 = (f32)(v30 + 1.5708) * 0.15915494;
  v40 = (s32)v39;
  if (v39 == INFINITY)
    v40 = -2147500000.0;
  v41 = v39 - v40;
  if ((f32)(v39 - v40) <= 0.5)
  {
    if (v41 < -0.5)
      v41 = v41 + 1.0;
  }
  else
  {
    v41 = v41 + -1.0;
  }
  data_high = HIDWORD(v38->_1.this_arg.data);
  if (v41 <= 0.25)
  {
    if (v41 < -0.25)
      v41 = -0.5 - v41;
  }
  else
  {
    v41 = 0.5 - v41;
  }
  v43 = v27 * (f32)(*(f32 *)(klass + 176) * 16.0);
  v44 = v41 * 4.0;
  bits = v38->_1.this_arg.bits;
  v46 = 16 * data_high;
  v47 = v44 * v44;
  v48 = v44 * (f32)(v44 * v44);
  v49 = v48 * -0.6459637;
  v50 = v47 * v48;
  v51 = (f32)((f32)((f32)((f32)(v41 * 4.0) * 1.5708) + v49) + (f32)(v50 * 0.07968968))
      + (f32)((f32)(v47 * v50) * -0.0046737655);
  v52 = (f32)(v47 * (f32)(v47 * v50)) * 0.00015148419;
  v53 = (s32)(v30 * 0.15915494);
  if ((f32)(v30 * 0.15915494) == INFINITY)
    v53 = -2147500000.0;
  v54 = (f32)(v30 * 0.15915494) - v53;
  if (v54 <= 0.5)
  {
    if (v54 >= -0.5)
      goto LABEL_64;
    v37 = 1.0;
  }
  v54 = v54 + v37;
LABEL_64:
  v55 = -0.5 - v54;
  v56 = 8 * bits + 30976;
  v57 = 0.5 - v54;
  v58 = v51 + v52;
  v59 = (f32)(v27 * (f32)(*(f32 *)(klass + 172) * 16.0)) + (f32)(v27 * (f32)(*(f32 *)(klass + 180) * 16.0));
  v60 = v46 + 28672;
  if (v54 >= -0.25)
    v55 = v54;
  v61 = v27 * (f32)(*(f32 *)(klass + 168) * 16.0);
  if (v54 <= 0.25)
    v57 = v55;
  v62 = v61 + v43;
  v63 = v57 * 4.0;
  v100 = v27 * (f32)(*(f32 *)(klass + 180) * 16.0);
  v101 = v27 * (f32)(*(f32 *)(klass + 172) * 16.0);
  v64 = (f32)((f32)((f32)((f32)(v63 * 1.5708) + (f32)((f32)(v63 * (f32)(v63 * v63)) * -0.6459637)) + (f32)((f32)((f32)(v63 * v63) * (f32)(v63 * (f32)(v63 * v63))) * 0.07968968)) + (f32)((f32)((f32)(v63 * v63) * (f32)((f32)(v63 * v63) * (f32)(v63 * (f32)(v63 * v63)))) * -0.0046737655))
      + (f32)((f32)((f32)(v63 * v63) * (f32)((f32)(v63 * v63) * (f32)((f32)(v63 * v63) * (f32)(v63 * (f32)(v63 * v63))))) * 0.00015148419);
  v65 = v62 * v58;
  v66 = v59 * v64;
  v67 = v62 * v64;
  v68 = v59 * v58;
  v102 = v65;
  v69 = v65 - v66;
  v70 = v69;
  if (v69 == INFINITY)
    v70 = 0x80000000;
  v71 = v70 + v60;
  v72 = (s32)(f32)(v68 + v67) >> 1;
  if ((f32)(v68 + v67) == INFINITY)
    v72 = -1073741824;
  *(sdfVector3_t *)(*(u64 *)(klass + 152) + 36) = GetVertexPos_36166560(v71, v72 + v56, 0);
  v73 = v61 - v43;
  v74 = (f32)(v61 - v43) * v58;
  v75 = v74 - v66;
  v76 = v73 * v64;
  v77 = v68 + (f32)(v73 * v64);
  if (v75 == INFINITY)
    v78 = 0x80000000;
  else
    v78 = v75;
  v79 = v78 + v60;
  v80 = (s32)v77 >> 1;
  if (v77 == INFINITY)
    v80 = -1073741824;
  *(sdfVector3_t *)(*(u64 *)(klass + 152) + 24) = GetVertexPos_36166560(v79, v80 + v56, 0);
  v81 = (f32)(v101 - v100) * v64;
  v82 = (f32)(v101 - v100) * v58;
  v83 = v82 + v76;
  if ((f32)(v74 - v81) == INFINITY)
    v84 = 0x80000000;
  else
    v84 = (f32)(v74 - v81);
  v85 = v84 + v60;
  v86 = (s32)v83 >> 1;
  if (v83 == INFINITY)
    v86 = -1073741824;
  *(sdfVector3_t *)*(u64 *)(klass + 152) = GetVertexPos_36166560(v85, v86 + v56, 0);
  v87 = (f32)(v102 - v81);
  v88 = v82 + v67;
  if ((f32)(v102 - v81) == INFINITY)
    v87 = 0x80000000;
  v89 = v87 + v60;
  v90 = (s32)v88 >> 1;
  if (v88 == INFINITY)
    v90 = -1073741824;
  *(sdfVector3_t *)(*(u64 *)(klass + 152) + 12) = GetVertexPos_36166560(v89, v90 + v56, 0);
  SetRange_36166880(*(void *)(klass + 40), 0xFF0000u, 0);
  *(f32 *)(klass + 120) = v110.x;
  *(f32 *)(klass + 124) = v110.y;
  v91 = *(u64 *)klass;
  *(f32 *)(klass + 128) = v110.z;
  *(f32 *)(klass + 132) = v110.w;
  *(_OWORD *)(klass + 136) = *(_OWORD *)&handle[1].klass;
  (*(v91 + 392))(klass, *(u64 *)(v91 + 400));
  v92 = Allocate(sdfDrawTag_t);
  _ctor(v92, 0);
  sdfDrawTagInit(v92);
  v93 = Allocate(Project_libsdf_sdfPrimAlphaPacket_t);
  _ctor(v93, 0);
  switch (*((u32 *)handle[2].klass->_1.namespaze + 5))
  {
    case 0:
      OPAQUE_ALPHA_ELEM_local = OPAQUE_ALPHA_ELEM;
      goto LABEL_103;
    case 1:
      v96 = &SDF_PRIM;
      goto LABEL_94;
    case 2:
      OPAQUE_ALPHA_ELEM_local = ADDTRANS_ALPHA_ELEM;
      goto LABEL_103;
    case 3:
    case 4:
      OPAQUE_ALPHA_ELEM_local = SUBTRANS_ALPHA_ELEM;
      goto LABEL_103;
    case 5:
    case 6:
      v96 = &SDF_GS_ALPHA;
      p_image = *v96;
LABEL_94:
      OPAQUE_ALPHA_ELEM_local = *(SDF_GS_ALPHA *)(p_image[23] + 24);
LABEL_103:
      v93->alpha = OPAQUE_ALPHA_ELEM_local;
      break;
    default:
      break;
  }
  sdfDrawTagLink(v92, v93);
  sdfDrawTagLink(v92, *(sdfGrPacketHeader_t *)(*(u64 *)(klass + 40) + 64));
  sdfDrawTagLinkOt(v26, v92);
  if (!get_STOP(0))
LABEL_14:
    ++HIDWORD(handle[1].option);
}

// 0x1999000
void eff2ColorSet(effPartsHandle_t *handle, const sdfVector4_t *abgr) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;

  w = abgr->w;
  z = abgr->z;
  y = abgr->y;
  x = abgr->x;
  *(f32 *)&handle[1].monitor = z;
  *((f32 *)&handle[1].monitor + 1) = w;
  *(f32 *)&handle[1].klass = x;
  *((f32 *)&handle[1].klass + 1) = y;
}
