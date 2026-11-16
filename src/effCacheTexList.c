#include "types.h"
#include "effcachetexlist.h"

typedef struct ctexlHandle_t ctexlHandle_t;
typedef struct ctexlHandle_t_Resource ctexlHandle_t_Resource;
typedef struct effCacheTexList_Anim_t effCacheTexList_Anim_t;

static u32 AllFrameGet(ctexlHandle_t *hCTexList);

// 0x1972ed0
static u32 AllFrameGet(ctexlHandle_t *hCTexList) {
  u32 *pItemList_wait;
  u64 max_length;
  s64 v4;
  u32 result;
  int8x16_t v6;
  int32x4_t *v7;
  s64 v8;
  int8x16_t v9;
  int8x16_t v10;
  int8x16_t v11;
  int32x4_t v12;
  int32x4_t v13;
  int32x4_t v14;
  int32x4_t v15;
  u64 v16;
  u32 *v17;
  s32 v18;

  pItemList_wait = hCTexList->pItemList_wait;
  if ((s32)pItemList_wait->max_length < 1)
    return 0;
  max_length = (u32)pItemList_wait->max_length;
  if (max_length < 0x10)
  {
    v4 = 0;
    result = 0;
LABEL_8:
    v16 = max_length - v4;
    v17 = &pItemList_wait[v4];
    do
    {
      v18 = *v17++;
      --v16;
      result += v18 + 1;
    }
    while (v16);
    return result;
  }
  v6 = 0u;
  v4 = pItemList_wait->max_length & 0xFFFFFFF0;
  v7 = &pItemList_wait[12];
  v8 = v4;
  v9 = 0u;
  v10 = 0u;
  v11 = 0u;
  do
  {
    v12 = v7[-3];
    v13 = v7[-2];
    v14 = v7[-1];
    v15 = *v7;
    v7 += 4;
    v8 -= 16;
    v9 = vsubq_s32(v13, vmvnq_s8(v9));
    v11 = vsubq_s32(v15, vmvnq_s8(v11));
    v6 = vsubq_s32(v12, vmvnq_s8(v6));
    v10 = vsubq_s32(v14, vmvnq_s8(v10));
  }
  while (v8);
  result = vaddvq_s32(vaddq_s32(vaddq_s32(v11, v10), vaddq_s32(v9, v6)));
  if ((pItemList_wait->max_length & 0xF) != 0)
    goto LABEL_8;
  return result;
}

// 0x1972fa0
ctexlHandle_t *effCacheTexCreate(ctexlHandle_t_Resource *pTLP) {
  ctexlHandle_t *v3;
  u32 *pItemList_wait;
  u32 header_flag;
  void *v6;
  s32 **v7;
  s32 *v8;
  s64 v9;
  s64 v10;
  void *v11;
  effCtexHandle_t *v12;
  int32x4_t *v13;
  u64 v14;
  s64 v15;
  s32 v16;
  int8x16_t v17;
  int32x4_t *v18;
  s64 v19;
  int8x16_t v20;
  int8x16_t v21;
  int8x16_t v22;
  int32x4_t v23;
  int32x4_t v24;
  int32x4_t v25;
  int32x4_t v26;
  u64 v27;
  s32 *v28;
  s32 v29;
  s32 v31;
  s64 v33;

  v3 = Allocate(ctexlHandle_t);
  pItemList_wait = pTLP->pItemList_wait;
  header_flag = pTLP->header_flag;
  v3->pItemList_wait = pItemList_wait;
  v3->header_flag = header_flag;
  v33 = &v3->pItemList_wait;
  v6 = NewSpecific(effCtexHandle_t, pTLP->texture->max_length);
  v3->phCtex = v6;
  v7 = &v3->phCtex;
  v8 = v3->phCtex;
  *(u64 *)&v3->use = 0xFFFFFFFF00000000LL;
  if (v8[6] >= 1)
  {
    v9 = 0;
    v10 = 8;
    do
    {
      v11 = *(Il2CppClass **)((char *)&pTLP->texture->obj.klass + v10 * 4);
      v12 = Allocate(effCtexHandle_t);
      v12->pPixel = v11;
      v12->use = 1;
      QueryInterface(v12, *(void **)(*(u64 *)v8 + 64));
      *(u64 *)&v8[v10] = v12;
      v8 = *v7;
      ++v9;
      v10 += 2;
    }
    while (v9 < (*v7)[6]);
  }
  v13 = *(int32x4_t **)v33;
  if ((s32)*(u64 *)(*(u64 *)v33 + 24) < 1)
  {
    v16 = 0;
    goto LABEL_18;
  }
  v14 = (u32)*(u64 *)(*(u64 *)v33 + 24);
  if (v14 < 0x10)
  {
    v15 = 0;
    v16 = 0;
LABEL_16:
    v27 = v14 - v15;
    v28 = (s32 *)&v13[2] + v15;
    do
    {
      v29 = *v28++;
      --v27;
      v16 += v29 + 1;
    }
    while (v27);
    goto LABEL_18;
  }
  v17 = 0u;
  v15 = *(u64 *)(*(u64 *)v33 + 24) & 0xFFFFFFF0LL;
  v18 = v13 + 5;
  v19 = v15;
  v20 = 0u;
  v21 = 0u;
  v22 = 0u;
  do
  {
    v23 = v18[-3];
    v24 = v18[-2];
    v25 = v18[-1];
    v26 = *v18;
    v18 += 4;
    v19 -= 16;
    v20 = vsubq_s32(v24, vmvnq_s8(v20));
    v22 = vsubq_s32(v26, vmvnq_s8(v22));
    v17 = vsubq_s32(v23, vmvnq_s8(v17));
    v21 = vsubq_s32(v25, vmvnq_s8(v21));
  }
  while (v19);
  v16 = vaddvq_s32(vaddq_s32(vaddq_s32(v22, v21), vaddq_s32(v20, v17)));
  if ((*(u64 *)(*(u64 *)v33 + 24) & 0xF) != 0)
    goto LABEL_16;
LABEL_18:
  v31 = v3->use + 1;
  v3->frameAll = v16;
  v3->use = v31;
  return v3;
}

// 0x1973220
void effCacheTexDelete(ctexlHandle_t *hCTexList) {
  u32 v2;
  effCtexHandle_t *phCtex;
  s64 max_length;
  s64 v5;
  s64 v6;
  s64 v7;
  Il2CppClass **v8;
  Il2CppClass *v9;
  Il2CppClass *v10;

  v2 = hCTexList->use - 1;
  hCTexList->use = v2;
  if (!v2)
  {
    phCtex = hCTexList->phCtex;
    if ((s32)phCtex->max_length >= 1)
    {
      max_length = (u32)phCtex->max_length;
      v5 = phCtex->max_length & 1;
      if (max_length == 1)
      {
        v6 = 0;
      }
      else
      {
        v6 = 0;
        v7 = max_length - v5;
        do
        {
          v8 = &phCtex->obj.klass + v6;
          v6 += 2;
          v10 = v8[4];
          v9 = v8[5];
          --LODWORD(v10->_1.namespaze);
          --LODWORD(v9->_1.namespaze);
        }
        while (v7 != v6);
      }
      if (v5)
        --phCtex[v6]->use;
    }
  }
}

// 0x19732b0
ctexlHandle_t *Copy(ctexlHandle_t *hCTexList) {
  ++hCTexList->use;
  return hCTexList;
}

// 0x19732c0
void effCacheTexAnimGet(ctexlHandle_t *hCTexList, u32 frame, effCacheTexList_Anim_t *pAnim) {
  il2cpp_array_size_t max_length;
  u32 header_flag;
  s32 v6;
  u32 frameAll;
  s64 v8;
  u32 v9;
  u32 v10;
  f32 v11;
  f32 *scale;

  max_length = hCTexList->phCtex->max_length;
  header_flag = hCTexList->header_flag;
  v6 = max_length - 1;
  if ((u32)max_length != 1)
  {
    frameAll = hCTexList->frameAll;
    if ((header_flag & 1) != 0)
    {
      frame %= frameAll;
    }
    else if (frameAll <= frame)
    {
      if ((u32)max_length)
        goto LABEL_14;
      frame = 0;
    }
    if ((s32)max_length < 1)
    {
      v6 = -1;
    }
    else
    {
      v8 = 0;
      v9 = 0;
      v6 = -1;
      while (1)
      {
        v10 = hCTexList->pItemList_wait[v8] + v9;
        if (frame <= v10)
          break;
        ++v8;
        v9 = v10 + 1;
        if ((u32)max_length == (u32)v8)
          goto LABEL_14;
      }
      v6 = v8;
    }
  }
LABEL_14:
  v11 = 2.0;
  scale = pAnim->scale;
  if ((header_flag & 4) == 0)
    v11 = 1.0;
  scale[0] = 1.0;
  scale[1] = v11;
  pAnim->rotate = 0.0;
  pAnim->frame = v6;
}

// 0x1973380
void *effCacheTexImageLoadLinkOt(ctexlHandle_t *hCTexList, effCacheTexList_Anim_t *pAnim) {
  return hCTexList->phCtex[pAnim->frame]->pPixel;
}
