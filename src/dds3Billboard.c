#include "types.h"
#include "TNEFFECT_BLEND.h"
#include "dds3billboard.h"
#include "eff.h"
#include "effect.h"
#include "sdf_vu0.h"
#include "sdfdraw.h"
#include "sdfmat.h"
#include "sdfsystem.h"
#include "sdftex.h"
#include "sdfvsync.h"

#define meshCount 100

typedef struct BillTable_t BillTable_t;
typedef struct MeshJobD MeshJobD;
typedef struct dds3BillAnimResource_t dds3BillAnimResource_t;
typedef struct dds3BillAnim_t dds3BillAnim_t;
typedef struct dds3BillResource_t dds3BillResource_t;
typedef struct dds3BillboardDirect_Param_t dds3BillboardDirect_Param_t;
typedef struct dds3Billboard_Basic_t dds3Billboard_Basic_t;
typedef struct dds3Billboard_Normal_t dds3Billboard_Normal_t;
typedef struct dds3Billboard_P2A_t dds3Billboard_P2A_t;
typedef struct dds3Billboard_Tex_t dds3Billboard_Tex_t;
typedef struct dds3EffectTable_t dds3EffectTable_t;
typedef struct sdfGrOt_t sdfGrOt_t;

BillTable_t *BillboardTable;
dds3Billboard_Basic_t *hGeneralBillboard;
static dds3BillResource_t *hDrawListTop;
static sdfGrOt_t **pOt_Table;
static dds3EffectTable_t *EffBillboardTable;
static sdfVector4_t move;

static dds3BillResource_t *LoadTex(void *pTex);
static void FreeTex(dds3BillResource_t *hResource);
static void TagLink(dds3Billboard_Basic_t *hBillboard, dds3BillResource_t *hResource, dds3BillResource_t *hResourceB);
static void BasicInit(dds3Billboard_Basic_t *pBasic);
static void NormalDelete(void *handle);
static void NormalDraw(void *handle);
static dds3Billboard_P2A_t *P2ACopy(dds3Billboard_P2A_t *pCopyP2A);
static void P2ADelete(void *handle);
static dds3BillResource_t *P2AAnimDraw(dds3Billboard_P2A_t *pP2A, dds3BillAnim_t *pBillAnim);
static void P2ADraw(void *handle);
static void P2ASetAnim(dds3BillAnimResource_t *hBillAnimRes, s32 number, dds3BillAnim_t *pBillAnim);
static void P2ASetNumber(dds3Billboard_P2A_t *pP2A, s32 number);
static dds3BillAnimResource_t *AnimLoadP2A(void *pData);
static void AnimFreeP2A(dds3BillAnimResource_t *hBillAnimRes, BILL_MODE mode);

// 0x194ff90
dds3Billboard_Basic_t *dds3BillboardGeneralCreate(u32 index) {
  u32 v4;

  v4 = index;
  return dds3BillboardGeneral(v4);
}

// 0x1950150
void dds3BillboardSetBlend(dds3Billboard_Basic_t *handle, TNEFFECT_BLEND blend) {
  u16 v3;
  dds3Billboard_Basic_t *v6;
  u16 v7;

  v3 = blend;
  v6 = handle;
  v7 = v3;
  dds3BillboardSetMode(v6, v7);
}

// 0x1950460
void *dds3BillboardTexHandleAndUVGet(dds3Billboard_Basic_t *handle, dds3Billboard_Tex_t *pTex) {
  dds3Billboard_Basic_t *v6;
  dds3Billboard_Tex_t *v7;

  v6 = handle;
  v7 = pTex;
  return dds3BillboardGetAnimTex(v6, v7);
}

// 0x1950650
void dds3BillboardManagerInit(void) {
  dds3Billboard_Basic_t *v3;
  void *v5;
  s64 v7;
  s64 i;
  s64 v9;
  void *name;
  dds3Billboard_Basic_t *hGeneralBillboard_local;
  dds3Billboard_Basic_t *v14;
  Il2CppClass *v15;
  u64 *v17;

  hDrawListTop = 0;
  v3 = NewSpecific(dds3Billboard_Basic_t, BillboardTable->max_length);
  hGeneralBillboard = v3;
  v5 = Allocate(Project_libsdf_sdfResourceUnit_Texture);
  _ctor(v5, 0);
  v7 = 0;
  for (i = 32; ; i += 8)
  {
    if (v7 >= SLODWORD(hGeneralBillboard->max_length))
      break;
    name = (*(Il2CppClass **)((char *)&BillboardTable->obj.klass + i))->_1.name;
    v5->texture = name;
    hGeneralBillboard_local = hGeneralBillboard;
    v14 = dds3BillboardCreate((u16)(*(Il2CppClass **)((char *)&BillboardTable->obj.klass + i))->_1.namespaze, v5);
    v15 = v14;
    *(Il2CppClass **)((char *)&hGeneralBillboard_local->obj.klass + i) = v15;
    v17 = *(Il2CppClass **)((char *)&hGeneralBillboard->obj.klass + i);
    ++v7;
    v9 = *(s64 *)((char *)&BillboardTable->obj.klass + i);
    *(float32x2_t *)(v17[12] + 48) = vmul_n_f32(*(float32x2_t *)(v17[12] + 48), *(f32 *)(v9 + 28));
  }
}

// 0x1950a00
void dds3BillboardManagerExit(void) {
  hDrawListTop = 0;
  hGeneralBillboard = 0;
}

// 0x1950a80
static dds3BillResource_t *LoadTex(void *pTex) {
  dds3BillResource_t *v3;
  s32 *v5;
  s64 v6;
  s64 v7;
  void *v8;
  void *v9;
  f32 v11;
  void *v12;
  f32 v13;
  s32 v14;
  void *v15;

  v3 = Allocate(dds3BillResource_t);
  _ctor(v3);
  v3->next = v3;
  v3->count = 1;
  v3->type = 0;
  v3->hTex = pTex;
  v5 = v3->draw;
  if (v5[6] >= 1)
  {
    v6 = 0;
    v7 = 8;
    do
    {
      v8 = NewSpecific(Draw, 2u);
      v9 = v8;
      if (v8)
        QueryInterface(v8, *(void **)(*(u64 *)v5 + 64));
      *(u64 *)&v5[v7] = v9;
      v5 = v3->draw;
      ++v6;
      v7 += 2;
    }
    while (v6 < v5[6]);
  }
  *(u64 *)((u64)v3->uv + 32) = 0x3F80000000000000LL;
  *(u64 *)((u64)v3->uv + 40) = 1065353216;
  v11 = sdfTexScaleMulF4(pTex);
  v12 = v3->hTex;
  *(u64 *)&v3->cx = 0;
  v13 = v11;
  v14 = (*(*(u64 *)v12 + 392))(v12, *(u64 *)(*(u64 *)v12 + 400)) >> 1;
  v15 = v3->hTex;
  v3->width = (f32)v14 / v13;
  v3->height = (f32)((*(*(u64 *)v15 + 424))(v15, *(u64 *)(*(u64 *)v15 + 432)) >> 1)
                      / v13;
  return v3;
}

// 0x1950cf0
static void FreeTex(dds3BillResource_t *hResource) {
  u32 v3;
  void *hTex;

  v3 = hResource->count - 1;
  hResource->count = v3;
  if (!v3)
  {
    hTex = hResource->hTex;
    sdfTexFreeDelayed(hTex);
  }
}

// 0x1950d80
static void TagLink(dds3Billboard_Basic_t *hBillboard, dds3BillResource_t *hResource, dds3BillResource_t *hResourceB) {
  s64 mode;
  Draw *v8;
  sdfDrawTag_t *p_pBillTag;
  char **v10;
  char *v11;
  void *v12;
  void *transform;
  void *v15;
  void *v16;
  void *v17;
  void *hTex;
  void *v19;
  void *Material;
  void *v23;
  dds3Billboard_MeshJob *p_pMesh;
  void *v25;
  dds3Billboard_MeshJob *pMesh;
  s64 camID;
  Draw *v29;
  Il2CppClass **v30;
  sdfDrawTag_t *v31;

  if (hResourceB)
    mode = 4;
  else
    mode = hBillboard->mode;
  v8 = hResource->draw[mode][hBillboard->camID];
  if (v8)
  {
    p_pBillTag = &v8->pBillTag;
    if (v8->pBillTag)
      goto LABEL_33;
    goto LABEL_28;
  }
  v8 = Allocate(Draw);
  _ctor(v8, 0);
  v10 = &"effect";
  if (hResourceB)
    v10 = &"multibill";
  v11 = *v10;
  v12 = Make(v11, 0);
  transform = get_transform(v12, 0);
  v15 = get_transform(hook, 0);
  SetParent_61042560(transform, v15, 0, 0);
  v16 = get_transform(v12, 0);
  set_localPosition(v16, zeroVector, 0);
  v17 = get_transform(v12, 0);
  set_localRotation(v17, identityQuaternion, 0);
  SetAutoHide(v12, 1, 0);
  hTex = hResource->hTex;
  if (hResourceB)
  {
    v19 = Allocate(Project_dds3Billboard_MeshJobM);
    _ctor(v19);
    (v12->klass[1]._1.declaringType)(v12, v19->edit, v12->klass[1]._1.parent);
    Material = get_Material(v12, 0);
    SetTexture_60817760(Material, ID_multiTexture, hTex, 0);
    hTex = hResourceB->hTex;
    v23 = v19;
    v8->pMesh = (dds3Billboard_MeshJob *)v19;
    p_pMesh = &v8->pMesh;
  }
  else
  {
    v25 = Allocate(Project_dds3Billboard_MeshJobS);
    _ctor(v25);
    (v12->klass[1]._1.declaringType)(v12, v25->edit, v12->klass[1]._1.parent);
    v23 = v25;
    v8->pMesh = (dds3Billboard_MeshJob *)v25;
    p_pMesh = &v8->pMesh;
  }
  (v12->klass[1]._1.this_arg.data)(v12, hTex, *(u64 *)&v12->klass[1]._1.this_arg.bits);
  SetOption(v12, hBillboard->option, 0);
  SetColor(v12, oneVector);
  pMesh = v8->pMesh;
  pMesh->mesh = (void *)v12;
  camID = hBillboard->camID;
  v29 = hResource->draw[mode];
  v30 = &v29->obj.klass + camID;
  v30[4] = v8;
  p_pBillTag = &v8->pBillTag;
  if (!v8->pBillTag)
  {
LABEL_28:
    v31 = Allocate(sdfDrawTag_t);
    _ctor(v31, 0);
    v8->pBillTag = v31;
    sdfDrawTagInit(v8->pBillTag);
    sdfDrawTagLink(v8->pBillTag, v8->pMesh->mesh->packet);
    if (hResource->next == hResource)
    {
      hResource->next = hDrawListTop;
      hDrawListTop = hResource;
    }
    (v8->pMesh->klass->vtable._7_unknown.methodPtr)(v8->pMesh, 100, v8->pMesh->klass->vtable._7_unknown.method);
    (v8->pMesh->klass[1]._1.image)(v8->pMesh, (u32)hBillboard->camID, v8->pMesh->klass[1]._1.gc_desc);
  }
LABEL_33:
  (v8->pMesh->klass->vtable._8_SetSource.methodPtr)(v8->pMesh, hBillboard, hResource, v8->pMesh->klass->vtable._8_SetSource.method);
}

// 0x19513f0
void dds3BillboardLinkOt(void) {
  dds3BillResource_t *hDrawListTop_local;
  dds3BillResource_t *next;
  s64 i;
  Draw **draw;
  s64 v7;
  sdfDrawTag_t *v8;
  s64 v10;
  sdfDrawTag_t *v11;
  s64 v13;
  sdfDrawTag_t *v14;
  s64 v16;
  sdfDrawTag_t *v17;
  s64 v19;
  sdfDrawTag_t *v20;

  hDrawListTop_local = hDrawListTop;
  if (!hDrawListTop_local)
    goto LABEL_4;
  goto LABEL_10;
  if (!hDrawListTop_local)
  {
LABEL_4:
    goto LABEL_5;
  }
  do
  {
LABEL_10:
    for (i = 32; i != 48; i += 8)
    {
      draw = hDrawListTop_local->draw;
      v7 = *(s64 *)((char *)&draw[0]->obj.klass + i);
      if (v7)
      {
        v8 = (v7 + 24);
        if (*(u64 *)(v7 + 24))
        {
          (*(**(u64 **)(v7 + 32) + 392))(*(u64 *)(v7 + 32), *(u64 *)(**(u64 **)(v7 + 32) + 400));
          sdfDrawTagLinkOt(*(sdfGrOt_t *)((char *)&pOt_Table[0]->obj.klass + i), v8);
          v8 = 0;
          draw = hDrawListTop_local->draw;
        }
      }
      v10 = *(s64 *)((char *)&draw[1]->obj.klass + i);
      if (v10)
      {
        v11 = (v10 + 24);
        if (*(u64 *)(v10 + 24))
        {
          (*(**(u64 **)(v10 + 32) + 392))(*(u64 *)(v10 + 32), *(u64 *)(**(u64 **)(v10 + 32) + 400));
          sdfDrawTagLinkOt(*(sdfGrOt_t *)((char *)&pOt_Table[1]->obj.klass + i), v11);
          v11 = 0;
          draw = hDrawListTop_local->draw;
        }
      }
      v13 = *(s64 *)((char *)&draw[2]->obj.klass + i);
      if (v13)
      {
        v14 = (v13 + 24);
        if (*(u64 *)(v13 + 24))
        {
          (*(**(u64 **)(v13 + 32) + 392))(*(u64 *)(v13 + 32), *(u64 *)(**(u64 **)(v13 + 32) + 400));
          sdfDrawTagLinkOt(*(sdfGrOt_t *)((char *)&pOt_Table[2]->obj.klass + i), v14);
          v14 = 0;
          draw = hDrawListTop_local->draw;
        }
      }
      v16 = *(s64 *)((char *)&draw[3]->obj.klass + i);
      if (v16)
      {
        v17 = (v16 + 24);
        if (*(u64 *)(v16 + 24))
        {
          (*(**(u64 **)(v16 + 32) + 392))(*(u64 *)(v16 + 32), *(u64 *)(**(u64 **)(v16 + 32) + 400));
          sdfDrawTagLinkOt(*(sdfGrOt_t *)((char *)&pOt_Table[3]->obj.klass + i), v17);
          v17 = 0;
          draw = hDrawListTop_local->draw;
        }
      }
      v19 = *(s64 *)((char *)&draw[4]->obj.klass + i);
      if (v19)
      {
        v20 = (v19 + 24);
        if (*(u64 *)(v19 + 24))
        {
          (*(**(u64 **)(v19 + 32) + 392))(*(u64 *)(v19 + 32), *(u64 *)(**(u64 **)(v19 + 32) + 400));
          sdfDrawTagLinkOt(*(sdfGrOt_t *)((char *)&pOt_Table[4]->obj.klass + i), v20);
          v20 = 0;
        }
      }
    }
    next = hDrawListTop_local->next;
    hDrawListTop_local->next = hDrawListTop_local;
    hDrawListTop_local = next;
  }
  while (next);
LABEL_5:
  hDrawListTop = 0;
}

// 0x1951700
static void BasicInit(dds3Billboard_Basic_t *pBasic) {
  s32 v5;

  v5 = (u8)byte_5756171;
  pBasic->rot = 0.0;
  pBasic->pos = zeroVector;
  pBasic->scale = (struct sdfVector4_t)xmmword_3D06BB0;
  pBasic->mode = 0;
  pBasic->abgr = oneVector;
}

// 0x19517a0
dds3Billboard_Normal_t *dds3BillboardNormalCreate(void *pData) {
  Il2CppObject *v3;
  void *v5;
  dds3BillResource_t *Tex;

  v3 = Allocate(dds3Billboard_Normal_t);
  _ctor(v3, 0);
  if (pData)
  {
    v5 = (pData->klass->vtable._7_GetTexture.methodPtr)(pData, pData->klass->vtable._7_GetTexture.method);
    Tex = LoadTex(v5);
  }
  else
  {
    Tex = 0;
  }
  v3[6].klass = Tex;
  return (dds3Billboard_Normal_t *)v3;
}

// 0x1951870
static void NormalDelete(void *handle) {
  Project_dds3EffectHandle_t_c *klass;
  s32 v6;
  void *name;

  klass = handle[6].klass;
  if (klass)
  {
    if (LOBYTE(handle[6].monitor))
    {
      DecDraw(handle[6].klass, WORD1(handle[5].klass), HIDWORD(handle[5].klass));
      klass = handle[6].klass;
      LOBYTE(handle[6].monitor) = 0;
    }
    v6 = HIDWORD(klass->_1.namespaze) - 1;
    HIDWORD(klass->_1.namespaze) = v6;
    if (v6)
      return;
    name = klass->_1.name;
    sdfTexFreeDelayed(klass->_1.name);
    return;
  }
}

// 0x1951af0
static void NormalDraw(void *handle) {
  s32 klass_high;
  Project_dds3EffectHandle_t_c *klass;
  Project_dds3EffectHandle_t_c *v9;
  s64 v11;
  s64 v12;

  klass_high = HIDWORD(handle[5].klass);
  if (klass_high == camID)
  {
    klass = handle[6].klass;
    goto LABEL_9;
  }
  if (LOBYTE(handle[6].monitor))
  {
    v9 = handle[6].klass;
    LOBYTE(handle[6].monitor) = 0;
    DecDraw(v9, WORD1(handle[5].klass), HIDWORD(handle[5].klass));
  }
  HIDWORD(handle[5].klass) = camID;
  klass = handle[6].klass;
LABEL_9:
  TagLink(handle, klass, 0);
  if (LOBYTE(handle[6].monitor))
    return;
  v11 = WORD1(handle[5].klass);
  LOBYTE(handle[6].monitor) = 1;
  v12 = *(u64 *)(*(u64 *)(*(u64 *)&handle[6].klass->_1.this_arg.bits + 8 * v11 + 32) + 8 * SHIDWORD(handle[5].klass) + 32);
  ++*(u32 *)(v12 + 16);
  return;
}

// 0x1951ce0
dds3Billboard_P2A_t *dds3BillboardP2ACreate(void *pData) {
  dds3Billboard_P2A_t *v3;
  void *v5;
  s32 **v6;
  s32 *v8;
  s64 v9;
  s64 v10;
  Il2CppObject *v11;

  v3 = Allocate(dds3Billboard_P2A_t);
  if (pData)
  {
    pData = AnimLoadP2A(pData);
  }
  v3->hResource = pData;
  v5 = NewSpecific(dds3BillAnim_t, (u32)pData[1].monitor);
  v3->pAnim = v5;
  v6 = &v3->pAnim;
  v8 = v3->pAnim;
  if (v8[6] >= 1)
  {
    v9 = 0;
    v10 = 8;
    do
    {
      v11 = Allocate(dds3BillAnim_t);
      _ctor(v11, 0);
      if (v11)
        QueryInterface(v11, *(void **)(*(u64 *)v8 + 64));
      *(u64 *)&v8[v10] = v11;
      v8 = *v6;
      ++v9;
      v10 += 2;
    }
    while (v9 < (*v6)[6]);
  }
  v3->drawType = 0;
  v3->state = 1;
  P2ASetNumber(v3, 0);
  return v3;
}

// 0x1952220
static dds3Billboard_P2A_t *P2ACopy(dds3Billboard_P2A_t *pCopyP2A) {
  dds3Billboard_P2A_t *v3;
  dds3BillAnimResource_t *hResource;
  void *v5;
  s32 **v6;
  s32 *v8;
  s64 v9;
  s64 v10;
  Il2CppObject *v11;

  v3 = Allocate(dds3Billboard_P2A_t);
  hResource = pCopyP2A->hResource;
  ++hResource->count;
  v3->hResource = hResource;
  v5 = NewSpecific(dds3BillAnim_t, hResource->AnimNum);
  v3->pAnim = v5;
  v6 = &v3->pAnim;
  v8 = v3->pAnim;
  if (v8[6] >= 1)
  {
    v9 = 0;
    v10 = 8;
    do
    {
      v11 = Allocate(dds3BillAnim_t);
      _ctor(v11, 0);
      if (v11)
        QueryInterface(v11, *(void **)(*(u64 *)v8 + 64));
      *(u64 *)&v8[v10] = v11;
      v8 = *v6;
      ++v9;
      v10 += 2;
    }
    while (v9 < (*v6)[6]);
  }
  v3->state = 1;
  P2ASetNumber(v3, 0);
  return v3;
}

// 0x19523c0
static void P2ADelete(void *handle) {
  u64 *monitor;
  s64 v6;
  s64 v7;
  s64 v8;
  s64 v9;
  s64 v10;
  s64 v11;
  s64 v12;
  s64 klass_high;
  s64 v14;
  s64 v15;
  s32 v16;
  bool v17;
  void *v18;
  s64 v19;
  void *gameObject;
  Project_dds3EffectHandle_t_c *klass;
  u64 *v22;

  if (handle)
  {
    LOWORD() = (u16)dds3Billboard_P2A_t;
  }
  monitor = handle[7].monitor;
  v6 = monitor[3];
  if ((s32)v6 >= 1)
  {
    v7 = 0;
    v22 = handle[7].monitor;
    do
    {
      v8 = monitor[v7 + 4];
      v9 = *(u64 *)(v8 + 40);
      if (*(s32 *)(v9 + 24) >= 1)
      {
        v10 = 0;
        do
        {
          if (*(u8 *)(v9 + v10 + 32))
          {
            v12 = *(u16 *)(v8 + 32);
            klass_high = SHIDWORD(handle[5].klass);
            v14 = *((u64 *)handle[6].klass->_1.byval_arg.data + v10 + 4);
            v15 = *(u64 *)(*(u64 *)(*(u64 *)(v14 + 56) + 8 * v12 + 32) + 8 * klass_high + 32);
            if (v15)
            {
              v16 = *(u32 *)(v15 + 16) - 1;
              v17 = *(u32 *)(v15 + 16) == 1;
              *(u32 *)(v15 + 16) = v16;
              if (v16 < 0 || v17)
              {
                v19 = *(u64 *)(v15 + 32);
                v18 = (v15 + 32);
                gameObject = get_gameObject(*(void *)(v19 + 40), 0);
                DestroyImmediate_61008224(gameObject, 0);
                Destroy(v18);
                v18 = 0;
                v11 = *(u64 *)(*(u64 *)(v14 + 56) + 8 * v12 + 32) + 8 * klass_high;
                *(u64 *)(v11 + 32) = 0;
              }
            }
            v9 = *(u64 *)(v8 + 40);
            *(u8 *)(v9 + v10 + 32) = 0;
          }
          ++v10;
        }
        while (v10 < *(s32 *)(v9 + 24));
        monitor = v22;
        v6 = v22[3];
      }
      ++v7;
    }
    while (v7 < (s32)v6);
  }
  klass = handle[6].klass;
  AnimFreeP2A(klass, (u16)method);
}

// 0x1952720
static dds3BillResource_t *P2AAnimDraw(dds3Billboard_P2A_t *pP2A, dds3BillAnim_t *pBillAnim) {
  int8x16_t v3;
  s32 wait;
  dds3BillAnimResource_t *hResource;
  P2A_ANIMATION_t *pAnim;
  s32 attr;
  s64 key;
  P2A_TEXANIM_t *v11;
  s32 v12;
  P2A_TEXANIM_t *spranm;
  il2cpp_array_size_t max_length;
  dds3BillResource_t *v15;
  float32x4_t oneVector_local;
  u32 v17;
  int8x16_t v18;
  uint32x4_t v19;
  float32x4_t v20;
  u16 mode;
  void *hTex;
  f32 v24;
  f32 v25;
  f32 v27;
  f32 v28;
  f32 v29;
  s32 sx;
  s32 u2;
  f32 v32;
  s32 cy;
  f32 v34;
  f32 v35;
  f32 cx;
  f32 *uv;
  f32 v38;

  wait = pBillAnim->wait;
  hResource = pP2A->hResource;
  pAnim = pBillAnim->pAnim;
  if (wait <= 0)
  {
    v12 = pBillAnim->key + 1;
    spranm = pAnim->spranm;
    max_length = spranm->max_length;
    pBillAnim->key = v12;
    if (v12 >= (s64)(u32)max_length)
    {
      if ((pAnim->mode & 0x10) != 0)
      {
        v12 = max_length - 1;
        pP2A->state = 0;
      }
      else
      {
        v12 = 0;
      }
      pBillAnim->key = v12;
    }
    key = v12;
    v11 = spranm[v12];
    attr = v11->attr;
  }
  else
  {
    attr = wait - 1;
    key = pBillAnim->key;
    v11 = pAnim->spranm[key];
  }
  pBillAnim->wait = attr;
  v15 = hResource->pResList[v11->texid];
  if ((pAnim->mode & 1) != 0)
  {
    v17 = pAnim->alpha[key];
    v3.n128_u32[0] = v17;
    v18.n128_u64[0] = 0xFF000000FFLL;
    v18.n128_u64[1] = 0xFF000000FFLL;
    v3.n128_u32[1] = v17 >> 8;
    v3.n128_u32[2] = HIWORD(v17);
    v19 = vandq_s8(v3, v18);
    v19.n128_u32[3] = vshrq_n_u32(vdupq_n_s32(v17), 0x18u).n128_u32[3];
    v20.n128_u64[0] = 0x3C0000003C000000LL;
    v20.n128_u64[1] = 0x3C0000003C000000LL;
    oneVector_local = vmulq_f32(vcvtq_f32_u32(v19), v20);
  }
  else
  {
    oneVector_local = oneVector;
  }
  pP2A->abgr = (struct sdfVector4_t)oneVector_local;
  mode = pBillAnim->mode;
  hTex = v15->hTex;
  pP2A->mode = mode;
  v24 = sdfTexScaleDivF4(hTex);
  v25 = v24
      / (f32)(v15->hTex->klass->vtable._5_get_width.methodPtr)(v15->hTex, v15->hTex->klass->vtable._5_get_width.method);
  v27 = v24
      / (f32)(v15->hTex->klass->vtable._7_get_height.methodPtr)(v15->hTex, v15->hTex->klass->vtable._7_get_height.method);
  v28 = v11->v1;
  v29 = v11->v2;
  sx = v11->sx;
  u2 = v11->u2;
  pP2A->rot = v11->angle;
  v32 = u2;
  cy = v11->cy;
  v34 = (f32)sx * 0.5;
  v35 = (f32)v11->sy * 0.5;
  cx = v11->cx;
  uv = v15->uv;
  v38 = v25 * (f32)v11->u1;
  v15->width = v34;
  v15->height = v35;
  v15->cx = v34 - cx;
  v15->cy = v35 - (f32)cy;
  uv[8] = v38;
  uv[9] = 1.0 - (f32)(v27 * v28);
  uv[10] = v25 * v32;
  uv[11] = 1.0 - (f32)(v27 * v29);
  return v15;
}

// 0x19529d0
static void P2ADraw(void *handle) {
  s32 klass_high;
  s32 monitor_high;
  dds3BillAnim_t *v9;
  dds3BillResource_t *v11;
  u64 *v13;
  s64 v14;
  s64 v15;
  s64 v16;
  s64 v17;
  s64 v18;
  u8 *v19;
  s32 v20;
  Project_dds3EffectHandle_t_c *klass;
  dds3BillAnim_t *v22;
  dds3BillResource_t *v23;
  dds3BillResource_t *v26;
  int8x16_t v27;
  float32x4_t v28;
  float32x4_t v29;
  float32x4_t v30;
  u64 *monitor;
  s64 v32;
  dds3BillResource_t *v33;
  f32 v34;
  dds3BillResource_t *v36;
  int8x16_t v37;
  float32x4_t v38;
  float32x4_t v39;
  char *v41;
  s64 v42;
  s64 v43;
  s64 v44;
  u8 *v45;
  s32 v46;
  s64 v47;
  f32 v48;
  int8x16_t v49;

  if (LOWORD(handle[6].monitor) && (HIBYTE(handle[6].monitor) & 0x10) == 0)
  {
    v48 = *(f32 *)&handle[3].klass;
    v49 = *(int8x16_t *)((char *)&handle[3] + 4);
    klass_high = HIDWORD(handle[5].klass);
    if (klass_high == camID)
    {
      monitor_high = HIDWORD(handle[6].monitor);
      if ((monitor_high & 0x40) == 0)
      {
LABEL_11:
        v9 = *((dds3BillAnim_t *)handle[7].monitor + 4);
        if ((monitor_high & 0x80) != 0)
        {
          v33 = P2AAnimDraw(handle, v9);
          v34 = vmuls_lane_f32(*(f32 *)&handle[4].klass, v49, 3);
          v36 = P2AAnimDraw(handle, *((dds3BillAnim_t *)handle[7].monitor + 5));
          v37 = handle[3];
          *(f32 *)&handle[4].klass = v34;
          v38 = vextq_s8(v37, v49, 0xCu);
          v39 = vmulq_f32(v38, v37);
          v38.n128_f32[0] = v48;
          v39.n128_u32[0] = vaddq_f32(v38, v37).n128_u32[0];
          handle[3] = (Project_dds3EffectHandle_t_o)v39;
          TagLink(handle, v36, v33);
          monitor = handle[7].monitor;
          v32 = monitor[3];
          if ((s32)v32 < 1)
            goto LABEL_37;
          goto LABEL_33;
        }
        v11 = P2AAnimDraw(handle, v9);
        *(float32x4_t *)((char *)&handle[3] + 4) = vmulq_f32(v49, *(float32x4_t *)((char *)&handle[3] + 4));
        *(f32 *)&handle[3].klass = v48 + *(f32 *)&handle[3].klass;
LABEL_28:
        TagLink(handle, v11, 0);
        monitor = handle[7].monitor;
        v32 = monitor[3];
        if ((s32)v32 < 1)
        {
LABEL_37:
          *(f32 *)&handle[3].klass = v48;
          *(int8x16_t *)((char *)handle + 52) = v49;
          return;
        }
LABEL_33:
        v32 = (u32)v32;
        v41 = (monitor + 4);
        do
        {
          v42 = *(u64 *)v41;
          v43 = *(s16 *)(*(u64 *)(*(u64 *)(*(u64 *)(*(u64 *)v41 + 24) + 16) + 8 * *(s32 *)(*(u64 *)v41 + 16) + 32) + 32);
          v44 = *(u64 *)(*(u64 *)v41 + 40) + v43;
          v46 = *(u8 *)(v44 + 32);
          v45 = (v44 + 32);
          if (!v46)
          {
            *v45 = 1;
            v47 = *(u64 *)(*(u64 *)(*(u64 *)(*((u64 *)handle[6].klass->_1.byval_arg.data + v43 + 4) + 56) + 8 * *(u16 *)(v42 + 32) + 32) + 8 * SHIDWORD(handle[5].klass) + 32);
            ++*(u32 *)(v47 + 16);
          }
          v41 += 8;
          --v32;
        }
        while (v32);
        goto LABEL_37;
      }
LABEL_25:
      v22 = *((dds3BillAnim_t *)handle[7].monitor + 4);
      v23 = P2AAnimDraw(handle, v22);
      *(float32x4_t *)((char *)&handle[3] + 4) = vmulq_f32(v49, *(float32x4_t *)((char *)&handle[3] + 4));
      *(f32 *)&handle[3].klass = v48 + *(f32 *)&handle[3].klass;
      TagLink(handle, v23, 0);
      v26 = P2AAnimDraw(handle, *((dds3BillAnim_t *)handle[7].monitor + 5));
      v27.n128_u32[0] = (u32)handle[4].klass;
      v11 = v26;
      v28 = handle[3];
      v29 = vextq_s8(v27, v49, 0xCu);
      *(f32 *)&handle[4].klass = vmuls_lane_f32(v27.n128_f32[0], v49, 3);
      v30 = vmulq_f32(v29, v28);
      v29.n128_f32[0] = v48;
      v30.n128_u32[0] = vaddq_f32(v29, v28).n128_u32[0];
      handle[3] = (Project_dds3EffectHandle_t_o)v30;
      goto LABEL_28;
    }
    v13 = handle[7].monitor;
    v14 = v13[3];
    if ((s32)v14 >= 1)
    {
      v15 = 0;
      do
      {
        v16 = v13[v15 + 4];
        v17 = *(s16 *)(*(u64 *)(*(u64 *)(*(u64 *)(v16 + 24) + 16) + 8 * *(s32 *)(v16 + 16) + 32) + 32);
        v18 = *(u64 *)(v16 + 40) + v17;
        v20 = *(u8 *)(v18 + 32);
        v19 = (v18 + 32);
        if (v20)
        {
          klass = handle[6].klass;
          *v19 = 0;
          DecDraw(*((dds3BillResource_t *)klass->_1.byval_arg.data + v17 + 4), *(u16 *)(v16 + 32), HIDWORD(handle[5].klass));
          v14 = v13[3];
        }
        ++v15;
      }
      while (v15 < (s32)v14);
    }
    HIDWORD(handle[5].klass) = camID;
    monitor_high = HIDWORD(handle[6].monitor);
    if ((monitor_high & 0x40) == 0)
      goto LABEL_11;
    goto LABEL_25;
  }
}

// 0x1952dc0
static void P2ASetAnim(dds3BillAnimResource_t *hBillAnimRes, s32 number, dds3BillAnim_t *pBillAnim) {
  P2A_ANIMATION_t *v7;
  u32 mode;
  P2A_TEXANIM_t *v10;
  u16 v11;
  s32 attr;
  bool *v13;
  bool **p_useDraw;

  v7 = hBillAnimRes->pAnimTable[number];
  pBillAnim->pAnim = v7;
  mode = pBillAnim->pAnim->mode;
  v10 = pBillAnim->pAnim->spranm[0];
  if ((mode & 4) != 0)
    v11 = 3;
  else
    v11 = 1;
  if ((mode & 2) != 0)
    v11 = 2;
  pBillAnim->mode = v11;
  attr = v10->attr;
  pBillAnim->key = 0;
  pBillAnim->wait = attr;
  v13 = NewSpecific(bool, hBillAnimRes->pResList->max_length);
  pBillAnim->useDraw = v13;
  p_useDraw = &pBillAnim->useDraw;
  if ((s32)(*p_useDraw)->max_length >= 1)
    sub_188E3B0((*p_useDraw), 0, (u32)(*p_useDraw)->max_length);
}

// 0x19520d0
static void P2ASetNumber(dds3Billboard_P2A_t *pP2A, s32 number) {
  dds3BillAnimResource_t *hResource;
  P2A_ANIMATION_t *v7;
  u32 attr;
  dds3BillAnim_t *v9;
  s32 v10;
  dds3BillAnimResource_t *v11;
  dds3BillAnim_t *v12;
  dds3BillAnim_t *v13;

  hResource = pP2A->hResource;
  v7 = hResource->pAnimTable[number];
  if (LODWORD(v7->spranm->max_length))
  {
    pP2A->number = number;
    if ((v7->mode & 0x10000000) != 0)
    {
      pP2A->animMode = 0x10000000;
      pP2A->state = 1;
    }
    else
    {
      attr = v7->attr;
      if ((attr & 0xC0) != 0)
      {
        pP2A->animMode = attr;
        pP2A->Anim_n = 2;
        v9 = pP2A->pAnim[0];
        P2ASetAnim(hResource, number, v9);
        v10 = number + 1;
        v11 = hResource;
        v12 = pP2A->pAnim[1];
      }
      else
      {
        pP2A->animMode = 0;
        pP2A->Anim_n = 1;
        v13 = pP2A->pAnim[0];
        v11 = hResource;
        v10 = number;
        v12 = v13;
      }
      P2ASetAnim(v11, v10, v12);
      pP2A->state = 1;
    }
  }
  else
  {
    pP2A->state = 0;
  }
}

// 0x1951ea0
static dds3BillAnimResource_t *AnimLoadP2A(void *pData) {
  Il2CppObject *v4;
  Il2CppClass *v5;
  s32 **v6;
  s32 *klass;
  s64 v9;
  s64 v10;
  void *v11;
  dds3BillResource_t *Tex;
  Project_libsdf_sdfResourceUnit_c *v15;
  s64 namespaze;
  s64 p_byval_arg;

  v4 = Allocate(dds3BillAnimResource_t);
  _ctor(v4, 0);
  v5 = NewSpecific(dds3BillResource_t, *((u32 *)pData[1].monitor + 6));
  v4[2].klass = v5;
  v6 = &v4[2];
  klass = v4[2].klass;
  if (klass[6] >= 1)
  {
    v9 = 0;
    v10 = 8;
    do
    {
      v11 = *(void *)((char *)pData[1].monitor + v10 * 4);
      Tex = LoadTex(*(void *)((char *)pData[1].monitor + v10 * 4));
      if (Tex)
      {
        QueryInterface(Tex, *(void **)(*(u64 *)klass + 64));
      }
      *(u64 *)&klass[v10] = Tex;
      klass = *v6;
      ++v9;
      v10 += 2;
    }
    while (v9 < (*v6)[6]);
  }
  v15 = pData[1].klass;
  v4[1].klass = v15;
  v4[1].monitor = 0x100000001LL;
  if ((s32)v4[1].klass->_1.namespaze >= 1)
  {
    namespaze = (u32)v4[1].klass->_1.namespaze;
    p_byval_arg = &v4[1].klass->_1.byval_arg;
    do
    {
      if ((*(u8 *)(*(u64 *)p_byval_arg + 39) & 0x10) == 0 && (*(u8 *)(*(u64 *)p_byval_arg + 32) & 0xC0) != 0)
      {
        LODWORD(v4[1].monitor) = 2;
      }
      p_byval_arg += 8;
      --namespaze;
    }
    while (namespaze);
  }
  return (dds3BillAnimResource_t *)v4;
}

// 0x19525f0
static void AnimFreeP2A(dds3BillAnimResource_t *hBillAnimRes, BILL_MODE mode) {
  s32 v4;
  dds3BillResource_t *pResList;
  s64 i;
  dds3BillResource_t *v7;
  s32 v8;
  s32 v9;
  void *hTex;

  v4 = hBillAnimRes->count - 1;
  hBillAnimRes->count = v4;
  if (!v4)
  {
    pResList = hBillAnimRes->pResList;
    if (SLODWORD(pResList->max_length) >= 1)
    {
      for (i = 0; i < SLODWORD(pResList->max_length); ++i)
      {
        v7 = pResList[i];
        v8 = v7->count - 1;
        v7->count = v8;
        if (!v8)
          goto LABEL_15;
        continue;
        if (!v9)
        {
LABEL_15:
          hTex = v7->hTex;
          sdfTexFreeDelayed(hTex);
        }
      }
    }
  }
}

// 0x19504f0
void *dds3BillboardGetAnimTex(dds3Billboard_Basic_t *hBillboard, dds3Billboard_Tex_t *pTex) {
  s32 type;
  s64 v6;
  dds3BillAnim_t *v7;
  char *klass;
  s64 naturalAligment;
  sdfVector2_t *v10;

  type = hBillboard->type;
  if (!hBillboard->type || type == 3)
  {
    if (hBillboard->klass->_2.naturalAligment >= (u32)naturalAligment && (dds3Billboard_Normal_t *)hBillboard->klass->_2.typeHierarchy[naturalAligment - 1] == dds3Billboard_Normal_t)
    {
      klass = hBillboard[1].klass;
LABEL_14:
      v10 = *((sdfVector2_t *)klass + 4);
      *(_OWORD *)&pTex->cx = *(_OWORD *)(klass + 40);
      pTex->uv0 = v10[4];
      pTex->uv1 = *(sdfVector2_t *)(*((u64 *)klass + 4) + 40);
      return *((void *)klass + 2);
    }
LABEL_16:
  }
  if (type == 1)
  {
    if (hBillboard->klass->_2.naturalAligment >= (u32)v6 && (dds3Billboard_P2A_t *)hBillboard->klass->_2.typeHierarchy[v6 - 1] == dds3Billboard_P2A_t)
    {
      v7 = *(dds3BillAnim_t *)(*(u64 *)&hBillboard[1].pos.z + 32);
      klass = P2AAnimDraw(hBillboard, v7);
      goto LABEL_14;
    }
    goto LABEL_16;
  }
  return 0;
}

// 0x1950870
dds3Billboard_Basic_t *dds3BillboardCreate(DDS3BILLBOARD type, void *pData) {
  dds3EffectHandle_t_CreateFunc Create;
  dds3Billboard_Basic_t *v7;
  dds3Billboard_Basic_t *v8;
  s32 v12;
  dds3EffectHandle_t_DrawFunc Draw;

  Create = EffBillboardTable[type]->Create;
  v7 = (Create->invoke_impl)(Create->method_code, pData, Create->method);
  v8 = v7;
  v12 = (u8)byte_5756171;
  v8->rot = 0.0;
  v8->pos = zeroVector;
  v8->scale = (struct sdfVector4_t)xmmword_3D06BB0;
  v8->mode = 0;
  v8->type = type;
  v8->abgr = oneVector;
  Draw = EffBillboardTable[type]->Draw;
  v8->Draw = Draw;
  return v8;
}

// 0x1952ed0
dds3Billboard_Basic_t *dds3BillboardCopy(void *handle) {
  s64 naturalAligment;
  s64 v5;
  s64 v6;
  struct sdfVector4_t v8;
  s32 v9;
  void *v10;
  u16 v11;
  s64 v12;
  s32 v15;
  void *monitor;
  u16 klass;
  s64 v18;
  Project_dds3EffectHandle_t_c *v19;
  void *v20;

  if (handle)
  {
    if (handle->klass->_2.naturalAligment < (u32)naturalAligment || handle->klass->_2.typeHierarchy[naturalAligment - 1] != dds3Billboard_Basic_t)
    {
      goto LABEL_29;
    }
  }
  if (LOWORD(handle[5].klass) != 1)
  {
LABEL_19:
    v6 = Allocate(dds3Billboard_Normal_t);
    *(u64 *)(v6 + 96) = 0;
    v12 = v6 + 96;
    v15 = (u8)byte_5756171;
    *(u32 *)(v6 + 48) = 0;
    *(sdfVector4_t *)(v6 + 16) = zeroVector;
    *(_OWORD *)(v6 + 32) = xmmword_3D06BB0;
    *(sdfVector4_t *)(v6 + 52) = oneVector;
    monitor = handle[4].monitor;
    klass = handle[5].klass;
    *(u64 *)(v6 + 72) = monitor;
    *(u32 *)(v6 + 80) = klass;
    if (handle->klass->_2.naturalAligment >= (u32)v18 && (dds3Billboard_Normal_t *)handle->klass->_2.typeHierarchy[v18 - 1] == dds3Billboard_Normal_t)
    {
      v19 = handle[6].klass;
      *(u64 *)v12 = v19;
      ++*(u32 *)(*(u64 *)v12 + 28);
      goto LABEL_26;
    }
LABEL_29:
    goto LABEL_19;
  }
  if (handle->klass->_2.naturalAligment < (u32)v5 || handle->klass->_2.typeHierarchy[v5 - 1] != dds3Billboard_P2A_t)
  {
    goto LABEL_29;
  }
  v6 = P2ACopy(handle);
  v8 = zeroVector;
  v9 = (u8)byte_5756171;
  *(u32 *)(v6 + 48) = 0;
  *(sdfVector4_t *)(v6 + 16) = v8;
  *(_OWORD *)(v6 + 32) = xmmword_3D06BB0;
  *(sdfVector4_t *)(v6 + 52) = oneVector;
  v10 = handle[4].monitor;
  v11 = handle[5].klass;
  *(u64 *)(v6 + 72) = v10;
  *(u32 *)(v6 + 80) = v11;
LABEL_26:
  v20 = handle[5].monitor;
  *(u64 *)(v6 + 88) = v20;
  return (dds3Billboard_Basic_t *)v6;
}

// 0x19531e0
void dds3BillboardDelete(void *handle) {
  dds3EffectHandle_t_DeleteFunc Delete;

  Delete = EffBillboardTable[LOWORD(handle[5].klass)]->Delete;
  (Delete->invoke_impl)(Delete->method_code, handle, Delete->method);
}

// 0x19532b0
void dds3BillboardDraw(void *handle) {
  if (drawSkip)
    return;
  (*(handle[4].monitor + 3))(*((u64 *)handle[4].monitor + 8), handle, *((u64 *)handle[4].monitor + 5));
}

// 0x1950010
dds3Billboard_Basic_t *dds3BillboardGeneral(s32 number) {
  dds3Billboard_Basic_t *v5;
  dds3Billboard_Basic_t *v6;
  dds3Billboard_Basic_t *klass;

  v5 = dds3BillboardCreate(BillboardTable[number]->type, 0);
  v6 = v5;
  klass = v5[1].klass;
  v6[1].klass = klass;
  ++HIDWORD(v6[1].klass->_1.namespaze);
  return v6;
}

// 0x19533f0
void *dds3BillboardGetGeneralTex(s32 number) {
  dds3Billboard_Basic_t *v4;

  v4 = hGeneralBillboard[number];
  if (!v4)
    return v4[1].klass->_1.name;
  return v4[1].klass->_1.name;
}

// 0x19534e0
void dds3BillboardSetPosition(void *handle, const sdfVector4_t *pPos) {
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

// 0x1953590
void dds3BillboardSetRotate(void *handle, f32 rot) {
  *(f32 *)&handle[3].klass = rot;
}

// 0x1953620
void dds3BillboardSetScale(void *handle, f32 x, f32 y) {
  *(f32 *)&handle[2].klass = x;
  *((f32 *)&handle[2].klass + 1) = y;
}

// 0x19536b0
void dds3BillboardSetRGBA(void *handle, u32 abgr) {
  int8x16_t v3;
  int8x16_t v9;
  uint32x4_t v10;
  float32x4_t v11;

  if (!handle)
  v3.n128_u32[0] = abgr;
  v9.n128_u64[0] = 0xFF000000FFLL;
  v9.n128_u64[1] = 0xFF000000FFLL;
  v3.n128_u32[1] = abgr >> 8;
  v3.n128_u32[2] = HIWORD(abgr);
  v10 = vandq_s8(v3, v9);
  v10.n128_u32[3] = vshrq_n_u32(vdupq_n_s32(abgr), 0x18u).n128_u32[3];
  v11.n128_u64[0] = 0x3C0000003C000000LL;
  v11.n128_u64[1] = 0x3C0000003C000000LL;
  *(float32x4_t *)((char *)&handle[3] + 4) = vmulq_f32(vcvtq_f32_u32(v10), v11);
}

// 0x1953800
void SetRGBA(void *handle, const sdfVector4_t *abgr) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;

  w = abgr->w;
  z = abgr->z;
  y = abgr->y;
  x = abgr->x;
  *((f32 *)&handle[3].monitor + 1) = z;
  *(f32 *)&handle[4].klass = w;
  *((f32 *)&handle[3].klass + 1) = x;
  *(f32 *)&handle[3].monitor = y;
}

// 0x19501e0
void dds3BillboardSetMode(dds3Billboard_Basic_t *hBillboard, BILL_MODE mode) {
  s32 type;
  s64 naturalAligment;
  s64 v8;
  s64 y_low;
  s64 v10;
  s32 v11;
  s64 v12;
  s64 v13;
  s64 v14;
  s64 v15;
  s64 v16;
  s64 camID;
  s64 v18;
  s64 v19;
  s32 v20;
  bool v21;
  void *v22;
  s64 v23;
  void *gameObject;
  u16 v25;

  type = hBillboard->type;
  if (type == 3)
    goto LABEL_6;
  if (type != 1)
  {
    if (hBillboard->type)
      return;
LABEL_6:
    if (hBillboard->klass->_2.naturalAligment >= (u32)naturalAligment && (dds3Billboard_Normal_t *)hBillboard->klass->_2.typeHierarchy[naturalAligment - 1] == dds3Billboard_Normal_t)
    {
      if (LOBYTE(hBillboard[1].monitor))
      {
        DecDraw(hBillboard[1].klass, hBillboard->mode, hBillboard->camID);
        LOBYTE(hBillboard[1].monitor) = 0;
      }
      hBillboard->mode = mode;
      return;
    }
LABEL_31:
  }
  if (hBillboard->klass->_2.naturalAligment < (u32)v8 || hBillboard->klass->_2.typeHierarchy[v8 - 1] != dds3Billboard_P2A_t)
  {
    goto LABEL_31;
  }
  y_low = LODWORD(hBillboard[1].pos.y);
  if ((u32)y_low)
  {
    v10 = 0;
    v11 = 0;
    v25 = mode;
    do
    {
      v12 = *(u64 *)(*(u64 *)&hBillboard[1].pos.z + 8 * v10 + 32);
      v13 = *(u64 *)(v12 + 40);
      if (*(s32 *)(v13 + 24) >= 1)
      {
        v14 = 0;
        do
        {
          if (*(u8 *)(v13 + v14 + 32))
          {
            v16 = *(u16 *)(v12 + 32);
            camID = hBillboard->camID;
            v18 = *((u64 *)hBillboard[1].klass->_1.byval_arg.data + v14 + 4);
            v19 = *(u64 *)(*(u64 *)(*(u64 *)(v18 + 56) + 8 * v16 + 32) + 8 * camID + 32);
            if (v19)
            {
              v20 = *(u32 *)(v19 + 16) - 1;
              v21 = *(u32 *)(v19 + 16) == 1;
              *(u32 *)(v19 + 16) = v20;
              if (v20 < 0 || v21)
              {
                v23 = *(u64 *)(v19 + 32);
                v22 = (v19 + 32);
                gameObject = get_gameObject(*(void *)(v23 + 40), 0);
                DestroyImmediate_61008224(gameObject, 0);
                Destroy(v22);
                v22 = 0;
                v15 = *(u64 *)(*(u64 *)(v18 + 56) + 8 * v16 + 32) + 8 * camID;
                *(u64 *)(v15 + 32) = 0;
              }
            }
            v13 = *(u64 *)(v12 + 40);
            *(u8 *)(v13 + v14 + 32) = 0;
          }
          ++v14;
        }
        while (v14 < *(s32 *)(v13 + 24));
        y_low = LODWORD(hBillboard[1].pos.y);
        mode = v25;
      }
      ++v11;
      *(u16 *)(v12 + 32) = mode;
      v10 = v11;
    }
    while (v11 < y_low);
  }
}

// 0x19538b0
void dds3BillboardSetAnimKey(dds3Billboard_Basic_t *hBillboard, s32 frame, s32 wait) {
  s64 y_low;
  s64 v9;
  s64 v10;
  s32 v11;
  s64 *v12;
  s64 v13;
  s64 v14;
  s64 v15;
  s32 v16;
  s32 v17;
  s64 v18;

  if (hBillboard->type == 1)
  {
    y_low = LODWORD(hBillboard[1].pos.y);
    if ((u32)y_low)
    {
      v9 = *(u64 *)&hBillboard[1].pos.z;
      if ((u32)y_low == 1)
      {
        v10 = 0;
        v11 = 0;
LABEL_14:
        v17 = v11 + 1;
        do
        {
          v18 = *(u64 *)(v9 + 8 * v10 + 32);
          *(u32 *)(v18 + 16) = frame % *(u32 *)(*(u64 *)(*(u64 *)(v18 + 24) + 16) + 24);
          *(u32 *)(v18 + 20) = wait;
          v10 = v17++;
        }
        while (v10 < y_low);
        return;
      }
      v11 = 0;
      v10 = 0;
      if ((u32)(y_low - 1) > 0x7FFFFFFE)
        goto LABEL_14;
      if ((u64)(y_low - 1) >> 31)
        goto LABEL_14;
      v10 = (u32)y_low & 0xFFFFFFFE;
      v12 = (v9 + 40);
      v11 = y_low & 0xFFFFFFFE;
      v13 = v10;
      do
      {
        v14 = *(v12 - 1);
        v15 = *v12;
        v12 += 2;
        v13 -= 2;
        v16 = *(u32 *)(*(u64 *)(*(u64 *)(v15 + 24) + 16) + 24);
        *(u32 *)(v14 + 16) = frame % *(u32 *)(*(u64 *)(*(u64 *)(v14 + 24) + 16) + 24);
        *(u32 *)(v14 + 20) = wait;
        *(u32 *)(v15 + 16) = frame % v16;
        *(u32 *)(v15 + 20) = wait;
      }
      while (v13);
      if (v10 != y_low)
        goto LABEL_14;
    }
  }
}

// 0x1953a20
void SetAnimKey(dds3Billboard_Basic_t *hBillboard, s32 frame) {
  s64 y_low;
  s64 v8;
  s64 v9;
  s32 v10;
  s64 *v11;
  s64 v12;
  s64 v13;
  s64 v14;
  s32 v15;
  s32 v16;

  if (hBillboard->type != 1)
    return;
  y_low = LODWORD(hBillboard[1].pos.y);
  if ((u32)y_low)
  {
    v8 = *(u64 *)&hBillboard[1].pos.z;
    if ((u32)y_low == 1)
    {
      v9 = 0;
      v10 = 0;
LABEL_19:
      v16 = v10 + 1;
      do
      {
        *(u64 *)(*(u64 *)(v8 + 8 * v9 + 32) + 16) = (u32)(frame % *(u32 *)(*(u64 *)(*(u64 *)(*(u64 *)(v8 + 8 * v9 + 32) + 24) + 16) + 24));
        v9 = v16++;
      }
      while (v9 < y_low);
      return;
    }
    v10 = 0;
    v9 = 0;
    if ((u32)(y_low - 1) > 0x7FFFFFFE)
      goto LABEL_19;
    if ((u64)(y_low - 1) >> 31)
      goto LABEL_19;
    v9 = (u32)y_low & 0xFFFFFFFE;
    v11 = (v8 + 40);
    v10 = y_low & 0xFFFFFFFE;
    v12 = v9;
    do
    {
      v13 = *(v11 - 1);
      v14 = *v11;
      v11 += 2;
      v12 -= 2;
      v15 = *(u32 *)(*(u64 *)(*(u64 *)(v14 + 24) + 16) + 24);
      *(u64 *)(v13 + 16) = (u32)(frame % *(u32 *)(*(u64 *)(*(u64 *)(v13 + 24) + 16) + 24));
      *(u64 *)(v14 + 16) = (u32)(frame % v15);
    }
    while (v12);
    if (v9 != y_low)
      goto LABEL_19;
  }
}

// 0x1953bf0
void dds3BillboardSetAnimKey2(dds3Billboard_Basic_t *hBillboard, s32 frame) {
  s64 y_low;
  s64 v8;
  s64 v9;
  s32 v10;
  s64 *v11;
  s64 v12;
  s64 v13;
  s64 v14;
  s32 v15;
  s32 v16;
  s64 v17;

  if (hBillboard->type != 1)
    return;
  y_low = LODWORD(hBillboard[1].pos.y);
  if ((u32)y_low)
  {
    v8 = *(u64 *)&hBillboard[1].pos.z;
    if ((u32)y_low == 1)
    {
      v9 = 0;
      v10 = 0;
LABEL_19:
      v16 = v10 + 1;
      do
      {
        v17 = *(u64 *)(v8 + 8 * v9 + 32);
        *(u32 *)(v17 + 16) = frame % *(u32 *)(*(u64 *)(*(u64 *)(v17 + 24) + 16) + 24);
        *(u32 *)(v17 + 20) = 1;
        v9 = v16++;
      }
      while (v9 < y_low);
      return;
    }
    v10 = 0;
    v9 = 0;
    if ((u32)(y_low - 1) > 0x7FFFFFFE)
      goto LABEL_19;
    if ((u64)(y_low - 1) >> 31)
      goto LABEL_19;
    v9 = (u32)y_low & 0xFFFFFFFE;
    v11 = (v8 + 40);
    v10 = y_low & 0xFFFFFFFE;
    v12 = v9;
    do
    {
      v13 = *(v11 - 1);
      v14 = *v11;
      v11 += 2;
      v12 -= 2;
      v15 = *(u32 *)(*(u64 *)(*(u64 *)(v14 + 24) + 16) + 24);
      *(u32 *)(v13 + 16) = frame % *(u32 *)(*(u64 *)(*(u64 *)(v13 + 24) + 16) + 24);
      *(u32 *)(v13 + 20) = 1;
      *(u32 *)(v14 + 16) = frame % v15;
      *(u32 *)(v14 + 20) = 1;
    }
    while (v12);
    if (v9 != y_low)
      goto LABEL_19;
  }
}

// 0x1953dc0
s32 dds3BillboardGetAnimFrame(dds3Billboard_Basic_t *hBillboard) {
  if (hBillboard->type != 1)
    return 0;
  return *(u32 *)(*(u64 *)(*(u64 *)(*(u64 *)(*(u64 *)&hBillboard[1].pos.z + 32) + 24) + 16) + 24);
}

// 0x1953e70
f32 dds3BillboardGetDirectionRotate(const sdfVector4_t *pPos, const sdfVector4_t *pVec) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  f32 v7;
  f32 v8;
  f32 v9;
  f32 v10;
  sdf3DScreenParam_t *SelScreenParam;
  __int128 v14;
  long f64 *p_x;
  long f64 v17;
  __int128 v18;
  f32 *v20;
  struct sdfVector4_t scale;
  struct sdfVector4_t trans;
  float32x2_t v26;
  f32 *v27;
  struct sdfVector4_t move_local;
  struct sdfVector4_t v34;
  struct sdfVector4_t v35;
  float32x2_t v36;
  float32x2_t v37;
  float32x2_t *v38;
  s64 v39;
  long f64 v41;
  long f64 v42;
  sdfMatrix4_t v56;
  __int128 v57;
  __int128 v58;
  long f64 v59;
  __int128 v60;
  sdfMatrix4_t v61;
  sdfMatrix4_t v62;
  sdfVector4_t v63;
  sdfVector4_t v64;
  sdfVector4_t v66;

  w = pVec->w;
  z = pVec->z;
  y = pVec->y;
  x = pVec->x;
  v7 = pPos->w;
  v8 = pPos->z;
  v9 = pPos->y;
  v10 = pPos->x;
  SelScreenParam = effGetSelScreenParam();
  effGetSelCameraTM(&v56, 0);
  v57 = *(_OWORD *)&v56.m00;
  v58 = *(_OWORD *)&v56.m01;
  v59 = *(long f64 *)&v56.m02;
  v60 = *(_OWORD *)&v56.m03;
  v14 = v58;
  p_x = (long f64 *)&vf00.x;
  *((_OWORD *)p_x + 4) = v57;
  *((_OWORD *)p_x + 5) = v14;
  v17 = v59;
  v18 = v60;
  p_x[6] = v59;
  *((_OWORD *)p_x + 7) = v18;
  sub_19636F0(&SelScreenParam->TM, 0, v17);
  v20 = &vf00.x;
  v20[4] = v10;
  v20[5] = v9;
  v20[6] = v8;
  v20[7] = v7;
  vct_C = vct_A;
  vct_A.w = 1.0;
  get_transpose(&v62, &mtx_A, 0);
  v61 = v62;
  v63 = op_Multiply_60923920(&v61, vct_A, 0);
  vct_A.x = v63.x * (f32)(1.0 / v63.w);
  vct_A.y = v63.y * (f32)(1.0 / v63.w);
  vct_A.z = v63.z * (f32)(1.0 / v63.w);
  vct_A.w = 1.0 / v63.w;
  scale = SelScreenParam->scale;
  vct_B = scale;
  vct_A = (struct sdfVector4_t)vmulq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  trans = SelScreenParam->trans;
  vct_B = trans;
  vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  v26.n64_u64[0] = *(u64 *)&vct_A.x;
  v27 = &vf00.x;
  v27[4] = x;
  v27[5] = y;
  v27[6] = z;
  v27[7] = w;
  move_local = move;
  vct_B = move_local;
  vct_A = (struct sdfVector4_t)vmulq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  vct_B = vct_C;
  vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  vct_A.w = 1.0;
  get_transpose(&v62, &mtx_A, 0);
  v66 = vct_A;
  v61 = v62;
  v64 = op_Multiply_60923920(&v61, v66, 0);
  vct_A.x = v64.x * (f32)(1.0 / v64.w);
  vct_A.y = v64.y * (f32)(1.0 / v64.w);
  vct_A.z = v64.z * (f32)(1.0 / v64.w);
  vct_A.w = 1.0 / v64.w;
  v34 = SelScreenParam->scale;
  vct_B = v34;
  vct_A = (struct sdfVector4_t)vmulq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  v35 = SelScreenParam->trans;
  vct_B = v35;
  vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  v36.n64_u64[0] = *(u64 *)&vct_A.x;
  v37.n64_u64[0] = vsub_f32(v26, v36).n64_u64[0];
  v38[2].n64_u64[0] = v37.n64_u64[0];
  v38[3].n64_u64[0] = 0;
  sub_1949110(0);
  v41 = sub_18E6660(0, v39);
  return *(f32 *)&v41;
}

// 0x1954840
f32 dds3BillboardGetDirectionScale(const sdfVector4_t *pVec) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  f32 *p_x;
  u64 v11;
  sdfVector4_t SelCameraTargetPos;
  sdfVector4_t SelCameraEyePos;

  w = pVec->w;
  z = pVec->z;
  y = pVec->y;
  x = pVec->x;
  SelCameraTargetPos = effGetSelCameraTargetPos();
  vct_A = SelCameraTargetPos;
  SelCameraEyePos = effGetSelCameraEyePos();
  vct_B = SelCameraEyePos;
  vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  sub_1949110(0);
  vct_B = vct_A;
  p_x = &vf00.x;
  p_x[4] = x;
  p_x[5] = y;
  p_x[6] = z;
  p_x[7] = w;
  v11 = vmul_f32(*(float32x2_t *)&vct_A.y, *(float32x2_t *)&vct_B.y).n64_u64[0];
  return 1.0
       - fabsf(*((f32 *)&v11 + 1) + (f32)((f32)(vct_A.x * vct_B.x) + *(f32 *)&v11));
}

// 0x1954b60
MeshJobD *dds3BillboardDirectInit(s32 billCount, s32 frameCount) {
  void *v5;
  MeshEditD *v6;
  void *Material;
  void *Materials;
  void *_36130192;
  void *transform;
  void *v14;

  v5 = Allocate(MeshJobD);
  __ctor(v5);
  v6 = Allocate(MeshEditD);
  _ctor_26562064(v6, billCount, frameCount);
  v5->edit = v6;
  Material = GetMaterial(Instance, "effect", 0);
  Materials = GetMaterials(Material, frameCount, 0);
  _36130192 = Make_36130192(Materials, 0);
  transform = get_transform(_36130192, 0);
  v14 = get_transform(hook, 0);
  SetParent_61042560(transform, v14, 0, 0);
  (_36130192->klass[1]._1.declaringType)(_36130192, v5->edit, _36130192->klass[1]._1.parent);
  SetColor(_36130192, oneVector);
  SetAutoHide(_36130192, 1, 0);
  v5->mesh = (void *)_36130192;
  return (MeshJobD *)v5;
}

// 0x1955050
void dds3BillboardDirectDraw(sdfGrOt_t *pOt, dds3BillboardDirect_Param_t *pBillboard) {
  MeshJobD *mesh;
  MeshEditD *edit;
  dds3BillboardDirect_Param_t *v7;
  sdfDrawTag_t *v8;

  mesh = pBillboard->mesh;
  edit = mesh->edit;
  if (edit->boundsJob.result.m_AllocatorLabel)
  {
    v7 = pBillboard;
    goto LABEL_4;
  }
  v8 = Allocate(sdfDrawTag_t);
  _ctor(v8, 0);
  sdfDrawTagInit(v8);
  sdfDrawTagLink(v8, mesh->mesh->packet);
  sdfDrawTagLinkOt(pOt, v8);
  *(u64 *)&mesh->edit->vertexCount = 0;
  (mesh->klass->vtable._9_SetCamID.methodPtr)(mesh, camID, mesh->klass->vtable._9_SetCamID.method);
  edit = mesh->edit;
  v7 = pBillboard;
LABEL_4:
  SetSource(edit, v7);
}
