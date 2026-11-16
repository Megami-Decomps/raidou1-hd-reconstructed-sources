#include "types.h"
#include "itfmisc.h"
#include "sdfdraw.h"
#include "sdftex.h"

typedef struct SDF_GS_ALPHA SDF_GS_ALPHA;
typedef struct itfMiscLinkHeader_t itfMiscLinkHeader_t;
typedef struct itfMiscLinkStack_t itfMiscLinkStack_t;
typedef struct sdfDrawTag_t sdfDrawTag_t;
typedef struct sdfIVector4_t sdfIVector4_t;

static s32 ITF_MISC_SCREEN_OFFSET_X;
static s32 ITF_MISC_SCREEN_OFFSET_Y;
static SDF_GS_ALPHA *palphadata;

// 0x1c93f40
void itfMiscLinkInitialize(itfMiscLinkStack_t *pstack, itfMiscLinkHeader_t *ptop, s32 numelem) {
  s64 v7;
  itfMiscLinkHeader_t *v8;
  Il2CppClass **v9;
  itfMiscLinkHeader_t *v10;
  s32 v11;
  itfMiscLinkHeader_t *v12;
  itfMiscLinkHeader_t *v13;
  itfMiscLinkHeader_t *v14;

  v7 = 0;
  v8 = 0;
  do
  {
    v9 = &ptop->obj.klass + v7;
    v10 = v8;
    v11 = v7;
    v8 = v9[4];
    v8->pprev = v10;
    v12 = v9[5];
    ++v7;
    v8->pnext = v12;
    --numelem;
    v8->id = v11;
  }
  while (numelem > 1);
  v13 = ptop[v7];
  v13->pprev = v8;
  v13->pnext = 0;
  v13->id = v7;
  pstack->puse_top = 0;
  pstack->puse_tail = 0;
  v14 = ptop[0];
  pstack->pdisuse_top = v14;
  pstack->pdisuse_tail = v13;
}

// 0x1c94030
itfMiscLinkHeader_t *itfMiscLinkTake(itfMiscLinkStack_t *pstack) {
  itfMiscLinkHeader_t *pdisuse_top;
  itfMiscLinkHeader_t *p_pdisuse_top;
  itfMiscLinkHeader_t *pnext;
  itfMiscLinkStack_t *p_fields;
  itfMiscLinkHeader_t *puse_tail;
  itfMiscLinkHeader_t *p_puse_tail;
  itfMiscLinkHeader_t *v9;

  p_pdisuse_top = &pstack->pdisuse_top;
  pdisuse_top = pstack->pdisuse_top;
  if (pdisuse_top)
  {
    pnext = pdisuse_top->pnext;
    p_fields = &pstack->fields;
    if (pstack->puse_top)
    {
      puse_tail = pstack->puse_tail;
      pdisuse_top->pprev = puse_tail;
      p_fields = &pstack->puse_tail->pnext;
    }
    else
    {
      pdisuse_top->pprev = 0;
    }
    p_fields->puse_top = pdisuse_top;
    pdisuse_top->pnext = 0;
    pstack->puse_tail = pdisuse_top;
    p_puse_tail = &pstack->puse_tail;
    if (pnext)
      v9 = &pnext->fields;
    else
      v9 = (p_puse_tail + 2);
    v9->pprev = 0;
    p_puse_tail[1] = pnext;
  }
  return pdisuse_top;
}

// 0x1c94110
void itfMiscLinkGive(itfMiscLinkHeader_t *pelem, itfMiscLinkStack_t *pstack) {
  itfMiscLinkHeader_t *pprev;
  itfMiscLinkHeader_t *p_fields;
  itfMiscLinkHeader_t *p_pnext;
  itfMiscLinkHeader_t *pnext;
  itfMiscLinkStack_t *v9;
  itfMiscLinkHeader_t *p_pprev;
  itfMiscLinkHeader_t *pdisuse_tail;
  itfMiscLinkHeader_t *p_pdisuse_top;
  itfMiscLinkHeader_t *pdisuse_top;

  p_fields = &pelem->fields;
  pprev = pelem->pprev;
  p_pnext = &pelem->pnext;
  pnext = pelem->pnext;
  if (pprev)
    v9 = &pprev->pnext;
  else
    v9 = &pstack->fields;
  v9->puse_top = pnext;
  if (pnext)
    p_pprev = &pnext->pprev;
  else
    p_pprev = &pstack->puse_tail;
  p_pprev = pprev;
  p_pnext = 0;
  pdisuse_tail = pstack->pdisuse_tail;
  p_fields->pprev = pdisuse_tail;
  if (pdisuse_tail)
  {
    pdisuse_tail->pnext = pelem;
  }
  pstack->pdisuse_tail = pelem;
  pdisuse_top = pstack->pdisuse_top;
  p_pdisuse_top = &pstack->pdisuse_top;
  if (!pdisuse_top)
  {
    p_pdisuse_top = pelem;
  }
}

// 0x1c94200
void itfMiscSetRatioRGB(sdfIVector4_t **pout, s32 off, s32 red, s32 green, s32 blue, s32 alpha, sdfIVector4_t *pratio, s32 num) {
  u32 v14;
  s64 v15;
  s32 v16;
  s32 v18;
  s32 v21;
  s32 v22;
  s32 v23;
  s32 v24;
  sdfIVector4_t *m_Items;
  sdfIVector4_t v30;
  sdfIVector4_t v31;
  sdfIVector4_t v32;
  sdfIVector4_t v33;
  sdfIVector4_t v34;
  sdfIVector4_t v35;
  sdfIVector4_t v36;

  if (num >= 1)
  {
    m_Items = pratio;
    v14 = num + 1;
    do
    {
      v15 = off;
      *(u64 *)&v30.z = 0;
      *(u64 *)&v30.x = &m_Items[v15];
      v16 = get_Item(v30, 0, *(const MethodInfo **)&green) * red;
      *(u64 *)&v31.x = &m_Items[v15];
      *(u64 *)&v31.z = 1;
      v18 = get_Item(v31, 0) * green;
      *(u64 *)&v32.x = &m_Items[v15];
      *(u64 *)&v32.z = 2;
      v21 = get_Item(v32, 0) * blue;
      if (v16 >= 16711680)
        v22 = 16711680;
      else
        v22 = v16;
      if (v18 >= 16711680)
        v23 = 16711680;
      else
        v23 = v18;
      *(u64 *)&v33.z = 0;
      if (v21 >= 16711680)
        v24 = 16711680;
      else
        v24 = v21;
      *(u64 *)&v33.x = &(*pout)[v15];
      set_Item(v33, v22 >> 16, 0);
      *(u64 *)&v34.z = 1;
      *(u64 *)&v34.x = &(*pout)[v15];
      set_Item(v34, v23 >> 16, 0);
      *(u64 *)&v35.z = 2;
      *(u64 *)&v35.x = &(*pout)[v15];
      set_Item(v35, v24 >> 16, 0);
      *(u64 *)&v36.z = 3;
      *(u64 *)&v36.x = &(*pout)[v15];
      set_Item(v36, alpha, 0);
      --v14;
      ++off;
    }
    while (v14 > 1);
  }
}

// 0x1c94360
void itfMiscDrawSpritePrim(sdfIVector4_t pos, sdfIVector4_t uv, const sdfColor32_t *color, u32 z, void *texhandle, s32 context, sdfDrawTag_t *pdrawtag, void *mesh) {
  u32 rgba;
  s32 Item;
  s32 v17;
  s32 v20;
  s32 v21;
  s32 v23;
  f32 v24;
  f32 v25;
  f32 v26;
  f32 v27;
  s32 v29;
  s32 v31;
  s32 v33;
  s32 v35;
  sdfIVector4_t v37;
  sdfIVector4_t v38;
  sdfIVector4_t v39;
  sdfIVector4_t v40;
  sdfIVector4_t v41;
  sdfIVector4_t v42;
  sdfIVector4_t v43;
  sdfIVector4_t v44;
  sdfIVector4_t v45;
  sdfIVector4_t v46;

  v38 = pos;
  rgba = color->rgba;
  v37 = uv;
  (mesh->edit->klass->vtable._4_unknown.methodPtr)(mesh->edit, mesh->edit->klass->vtable._4_unknown.*(u64 *)&uv.x, *(u64 *)&uv.z, color, *(u64 *)&z, texhandle, *(u64 *)&context);
  SetSquareCol(mesh, 0, (sdfColor32_t)rgba, 0);
  *(u64 *)&v39.x = &v38;
  *(u64 *)&v39.z = 0;
  Item = get_Item(v39, 0);
  *(u64 *)&v40.x = &v38;
  *(u64 *)&v40.z = 1;
  v17 = get_Item(v40, 0);
  *(u64 *)&v41.x = &v38;
  *(u64 *)&v41.z = 2;
  v20 = get_Item(v41, 0);
  *(u64 *)&v42.x = &v38;
  *(u64 *)&v42.z = 3;
  v21 = ITF_MISC_SCREEN_OFFSET_X;
  v23 = get_Item(v42, 0);
  SetSquarePos_36171728(mesh, 0, ITF_MISC_SCREEN_OFFSET_X + Item, ITF_MISC_SCREEN_OFFSET_Y + v17, v21 + v20, ITF_MISC_SCREEN_OFFSET_Y + v23, 0);
  v24 = sdfTexScaleDivF4(texhandle);
  v25 = v24
      / (f32)(texhandle->klass->vtable._5_get_width.methodPtr)(texhandle, texhandle->klass->vtable._5_get_width.method);
  v26 = (texhandle->klass->vtable._7_get_height.methodPtr)(texhandle, texhandle->klass->vtable._7_get_height.method);
  *(u64 *)&v43.x = &v37;
  *(u64 *)&v43.z = 0;
  v27 = v24 / v26;
  v29 = get_Item(v43, 0);
  *(u64 *)&v44.x = &v37;
  *(u64 *)&v44.z = 1;
  v31 = get_Item(v44, 0);
  *(u64 *)&v45.x = &v37;
  *(u64 *)&v45.z = 2;
  v33 = get_Item(v45, 0);
  *(u64 *)&v46.x = &v37;
  *(u64 *)&v46.z = 3;
  v35 = get_Item(v46, 0);
  SetSquareUV(mesh, 0, v25 * (f32)v29, 1.0 - (f32)(v27 * (f32)v31), v25 * (f32)v33, 1.0 - (f32)(v27 * (f32)v35), 0);
  SetRange_36166880(mesh, z, 0);
  SetSquareIndex_36173424(mesh, 0);
  SetMarker(mesh, 0);
  (mesh->edit->klass->vtable._5_unknown.methodPtr)(mesh->edit, mesh->edit->klass->vtable._5_unknown.method);
  (mesh->klass->vtable._7_SetTexture.methodPtr)(mesh, texhandle, mesh->klass->vtable._7_SetTexture.method);
  sdfDrawTagLink(pdrawtag, mesh->packet);
}

// 0x1c94610
void itfMiscDrawAlphaPrim(sdfDrawTag_t *pdrawtag, s32 tp, s32 context) {
  void *v6;
  SDF_GS_ALPHA *v8;

  v6 = Allocate(Project_libsdf_sdfPrimAlphaPacket_t);
  _ctor(v6, 0);
  v8 = palphadata[tp];
  v6->alpha = v8;
  sdfDrawTagLink(pdrawtag, v6);
}

// 0x1c946d0
s32 itfCamp(void) {
  return 1;
}
