#include "types.h"
#include "dds3billboard.h"
#include "dds3kerneldraw.h"
#include "eff.h"
#include "effbehavior.h"
#include "efflensflare.h"
#include "effparts.h"
#include "sdf_gs_alpha.h"
#include "sdf_vu0.h"
#include "sdfdraw.h"
#include "sdfmat.h"
#include "sdfsystem.h"

#define EFFLENSFLARE_PARTS_WIDTH 128
#define SCREEN_WIDTH 341.33325
#define SCREEN_HEIGHT 224
#define SCREEN_OX 2048
#define SCREEN_OY 2048

typedef struct Standard Standard;
typedef struct SubTable SubTable;
typedef struct effLensFlare_Params_t effLensFlare_Params_t;
typedef struct effLensFlare_Parts_t effLensFlare_Parts_t;
typedef struct effPartsHandle_t effPartsHandle_t;
typedef struct flareHandle_t flareHandle_t;

struct effLensFlare_Parts_t {
    f32 dist;
    f32 width;
    s32 sub;
    sdfVector4_t abgr;
};

struct SubTable {
    s32 tex;
    s32 count;
    f32 u;
    f32 v;
};

static void *effLensFlare_PartsList;
static void *subTable;
static f32 dist_max;

static flareHandle_t *Create(effLensFlare_Params_t *pParams);

// 0x1973f10
static flareHandle_t *Create(effLensFlare_Params_t *pParams) {
  flareHandle_t *v3;

  v3 = Allocate(flareHandle_t);
  v3->pos = vf00;
  v3->param = pParams;
  return v3;
}

// 0x1974020
flareHandle_t *PartsCreate(Standard *pParts) {
  u8 *v3;
  sdfBinary *v4;
  effLensFlare_Params_t *v5;

  v3 = effParamsGet(pParts);
  v4 = Allocate(sdfBinary);
  _ctor_36176832(v4, v3, 0);
  v5 = Allocate(effLensFlare_Params_t);
  _ctor_26689840(v5, v4);
  return Create(v5);
}

// 0x1974280
void Delete(effPartsHandle_t *handle) {
  effPartsHandle_t *v4;
  void *v5;
  effPartsHandle_t *klass;
  void *gameObject;

  klass = handle[3].klass;
  v5 = &handle[3];
  v4 = klass;
  if (klass)
  {
    gameObject = get_gameObject(*(void *)&v4->_1.byval_arg.bits, 0);
    DestroyImmediate_61008224(gameObject, 0);
    Destroy(v5);
    v5 = 0;
  }
}

// 0x1974380
flareHandle_t *Copy(effPartsHandle_t *handle) {
  effOption *option;
  effLensFlare_Params_t *v5;

  option = handle[2].option;
  v5 = Allocate(effLensFlare_Params_t);
  _ctor_26690672(v5, option);
  return Create(v5);
}

// 0x19745e0
void Draw(effPartsHandle_t *handle) {
  s32 *p_fields;
  s32 option;
  f32 v12;
  f32 v13;
  s32 w_low;
  f32 v19;
  f32 *klass;
  effPartsHandle_t *v21;
  effLensFlare_MeshJob *v22;
  s64 klass_low;
  s64 v25;
  s64 v26;
  void *v27;
  void *Material;
  void *Materials;
  void *_36166016;
  MeshEditPCU *v32;
  void *transform;
  void *v35;
  void *v36;
  s32 v37;
  void *v38;
  s64 v39;
  s32 v40;
  s32 v41;
  s64 v42;
  s64 i;
  s32 v45;
  void *v46;
  u32 *v47;
  s32 v49;
  void *GeneralTex;
  s32 v52;
  s32 m_Length;
  char *v56;
  effOption *v58;
  effBehavior_RGBParams_t *v59;
  effBehavior_AlphaParams_t *v60;
  sdfDrawTag_t *v61;
  void *v62;
  Il2CppClass *v66;
  void *v67;
  s32 v68;
  effPartsHandle_t *target;
  s32 *v70;
  effPartsHandle_t *v71;
  s32 v72;
  Il2CppClass *v73;
  effPartsHandle_t *v74;
  struct sdfVector4_t v75;
  Il2CppClass *v76;

  v75 = *(sdfVector4_t *)&handle[1].klass;
  vct_A = v75;
  if (effScreenOffsetClipGet())
    goto LABEL_11;
  p_fields = &handle[1].fields;
LABEL_57:
  option = *p_fields;
LABEL_58:
  *p_fields = option + 1;
  return;
LABEL_11:
  p_fields = &handle[1].fields;
  option = handle[1].option;
  v12 = vct_A.x + -2048.0;
  v13 = (f32)(vct_A.y + -2048.0) + (f32)(vct_A.y + -2048.0);
  if (v13 < -224.0 || v12 > 341.33325 || v12 < -341.33325 || v13 > 224.0)
    goto LABEL_58;
  w_low = LODWORD(handle[2].option->adjustRGBA.w);
  if (w_low > option || w_low < 1)
  {
    v19 = sqrtf((f32)(v12 * v12) + (f32)(v13 * v13));
    if (v19 > 0.0)
    {
      v21 = handle + 3;
      klass = handle[3].klass;
      if (!klass)
      {
        v22 = Allocate(effLensFlare_MeshJob);
        _ctor(v22, 0);
        SetSquare(&v22->indexJob, 0);
        v74 = v22;
        Set(&v22->markerJob);
        klass_low = SLODWORD(handle[2].option[1].klass);
        v25 = (s64)subTable + 16 * klass_low;
        v26 = (s64)effLensFlare_PartsList + 16 * klass_low;
        v27 = *(void **)(v25 + 40);
        v76 = *(Il2CppClass **)(v25 + 32);
        v72 = option;
        v73 = *(Il2CppClass **)(v26 + 40);
        v66 = *(Il2CppClass **)(v26 + 32);
        Material = GetMaterial(Instance, "effect", 0);
        v68 = w_low;
        Materials = GetMaterials(Material, (s32)v27, 0);
        _36166016 = Make_36166016(Materials, 0);
        v32 = Allocate(MeshEditPCU);
        _ctor(v32, 0);
        transform = get_transform(_36166016, 0);
        v70 = &handle[1].fields;
        v71 = handle;
        target = handle + 3;
        v35 = get_transform(hook, 0);
        SetParent_61042560(transform, v35, 0, 0);
        (_36166016->klass[1]._1.declaringType)(_36166016, v32, _36166016->klass[1]._1.parent);
        InitSquare(_36166016, 4 * (u32)v73, 0);
        SetAutoHide(_36166016, 1, 0);
        *(u64 *)&v74->_1.byval_arg.bits = _36166016;
        v74->_1.this_arg.data = v32;
        v36 = get_Materials(*(void *)&v74->_1.byval_arg.bits, 0);
        v67 = v27;
        if ((s32)v27 <= 1)
          v37 = 1;
        else
          v37 = v27;
        v38 = v36;
        v39 = 0;
        v40 = 0;
        v41 = 0;
        v42 = 16 * (u32)(v37 - 1);
        for (i = 32; ; i += 8)
        {
          v45 = *(u32 *)((char *)&v76->_1.image + v39 + 4);
          v46 = *(void *)((char *)&v38->obj.klass + i);
          v47 = *(u32 **)(*((u64 *)v74->_1.this_arg.data + 8) + i);
          v47[4] = v41;
          v47[5] = 16 * v45;
          v47[6] = v40;
          v47[7] = 24 * v45;
          v49 = *(u32 *)((char *)&v76->_1.image + v39);
          GeneralTex = dds3BillboardGetGeneralTex(v49);
          SetTexture_60817760(v46, ID_texture, GeneralTex, 0);
          if (v42 == v39)
            break;
          v39 += 16;
          v41 += v47[5];
          v40 += v47[7];
        }
        v52 = v47[5];
        option = v72;
        v21 = target;
        m_Length = marker.m_Length;
        w_low = v68;
        p_fields = v70;
        handle = v71;
        v47[5] = m_Length + v52;
        v47[7] += m_Length;
        v74->_1.castClass = v66;
        v74->_1.declaringType = v73;
        v74->_1.parent = v76;
        v74->_1.generic_class = v67;
        target->klass = v74;
        klass = target->klass;
      }
      klass[26] = v12;
      klass[27] = v13;
      v56 = klass;
      v58 = handle[2].option;
      v59 = *(effBehavior_RGBParams_t *)&v58->FieldOt;
      v60 = *(effBehavior_AlphaParams_t *)&v58->adjustRGBA.x;
      klass[28] = (f32)((f32)(dist_max - v19) / dist_max) * v58->adjustRGBA.z;
      *(float32x4_t *)(v56 + 116) = vmulq_f32((float32x4_t)effColorAnimation(v59, v60, option, w_low), *(float32x4_t *)((char *)&handle[1].option + 4));
      (*(handle[3].klass->_1.image + 49))(handle[3].klass, *((u64 *)handle[3].klass->_1.image + 50));
      v61 = Allocate(sdfDrawTag_t);
      _ctor(v61, 0);
      sdfDrawTagInit(v61);
      v62 = Allocate(Project_libsdf_sdfPrimAlphaPacket_t);
      _ctor(v62, 0);
      v62->alpha = SET_02010;
      sdfDrawTagLink(v61, v62);
      sdfDrawTagLink(v61, *(sdfGrPacketHeader_t *)(*(u64 *)&v21->klass->_1.byval_arg.bits + 64));
      sdfDrawTagLinkOt(Ot[109], v61);
      goto LABEL_57;
    }
  }
}

// 0x1974e20
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

// 0x1974ed0
void ColorSet(effPartsHandle_t *handle, const sdfVector4_t *abgr) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;

  w = abgr->w;
  z = abgr->z;
  y = abgr->y;
  x = abgr->x;
  *((f32 *)&handle[2].klass + 1) = z;
  *(f32 *)&handle[2].monitor = w;
  *((f32 *)&handle[1].option + 1) = x;
  *(f32 *)&handle[2].klass = y;
}
