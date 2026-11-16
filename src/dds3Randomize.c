#include "types.h"
#include "dds3randomize.h"
#include "sdfrand.h"

typedef struct sdfRandCB_t sdfRandCB_t;

sdfRandCB_t *CB;

// 0x22996f0
u32 dds3GetRandA(void) {
  u32 *v;
  u32 v4;
  s32 v5;
  u32 v6;
  s32 v7;

  v = sdfDefaultRandCB->v;
  v4 = v[0];
  v5 = *(u64 *)v >> 30;
  v6 = v[2];
  v7 = *(u64 *)&v[2] >> 31;
  v[2] = v[1];
  v[3] = v6;
  v[0] = v7 ^ v5;
  v[1] = v4;
  return v7 ^ v5;
}

// 0x22997d0
u32 dds3GetRandB(void) {
  sdfRandCB_t *CB_local;
  u32 *v;
  u32 v5;
  u32 v6;
  s32 v7;
  s32 v8;

  CB_local = CB;
  if (!CB_local)
    CB_local = sdfDefaultRandCB;
  v = CB_local->v;
  v5 = v[0];
  v6 = v[2];
  v7 = *(u64 *)v >> 30;
  v8 = *(u64 *)&v[2] >> 31;
  v[2] = v[1];
  v[3] = v6;
  v[0] = v8 ^ v7;
  v[1] = v5;
  return v8 ^ v7;
}

// 0x22998e0
f32 dds3GetRandFloatA(void) {
  u32 *v;
  u32 v5;
  s32 v6;
  u32 v7;
  s32 v8;
  s32 v9;

  v = sdfDefaultRandCB->v;
  v5 = v[0];
  v6 = *(u64 *)v >> 30;
  v7 = v[2];
  v8 = *(u64 *)&v[2] >> 31;
  v[2] = v[1];
  v[3] = v7;
  v9 = v8 ^ v6;
  v[0] = v9;
  v[1] = v5;
  return (f32)(v9 & 0xFFFFFF) * 5.9604645e-08;
}

// 0x2299a10
f32 dds3GetRandFloatB(void) {
  sdfRandCB_t *CB_local;
  u32 *v;
  u32 v6;
  u32 v7;
  s32 v8;
  s32 v9;
  s32 v10;

  CB_local = CB;
  if (!CB_local)
    CB_local = sdfDefaultRandCB;
  v = CB_local->v;
  v6 = v[0];
  v7 = v[2];
  v8 = *(u64 *)v >> 30;
  v9 = *(u64 *)&v[2] >> 31;
  v[2] = v[1];
  v[3] = v7;
  v10 = v9 ^ v8;
  v[0] = v10;
  v[1] = v6;
  return (f32)(v10 & 0xFFFFFF) * 5.9604645e-08;
}

// 0x2299b70
u32 dds3GetRandIntA(u32 aLimit) {
  u32 *v;
  u32 v7;
  u32 v8;
  s32 v9;
  s32 v10;
  u32 v11;

  v = sdfDefaultRandCB->v;
  v7 = v[0];
  v8 = v[2];
  v9 = *(u64 *)v >> 30;
  v10 = *(u64 *)&v[2] >> 31;
  v[2] = v[1];
  v[3] = v8;
  v11 = v10 ^ v9;
  v[0] = v11;
  v[1] = v7;
  return v11 % aLimit;
}

// 0x2299ca0
u32 dds3GetRandIntB(u32 aLimit) {
  sdfRandCB_t *CB_local;
  u32 *v;
  u32 v8;
  s32 v9;
  u32 v10;
  s32 v11;
  u32 v12;

  CB_local = CB;
  if (!CB_local)
    CB_local = sdfDefaultRandCB;
  v = CB_local->v;
  v8 = v[0];
  v9 = *(u64 *)v >> 30;
  v10 = v[2];
  v11 = *(u64 *)&v[2] >> 31;
  v[2] = v[1];
  v[3] = v10;
  v12 = v11 ^ v9;
  v[0] = v12;
  v[1] = v8;
  return v12 % aLimit;
}

// 0x2299e00
s32 dds3Choose(f32 *probs) {
  il2cpp_array_size_t max_length;
  u64 v4;
  u64 v5;
  f32 v6;
  f32 *v7;
  u64 v8;
  f32 v9;
  f32 v10;
  f32 v11;
  f32 v12;
  char v13;
  u64 v14;
  f32 v15;
  u64 v16;
  f32 *v17;
  f32 v18;
  f32 v19;
  f32 value;
  il2cpp_array_size_t v21;
  s32 result;
  f32 v23;
  s64 v24;
  f32 v25;

  max_length = probs->max_length;
  if ((s32)max_length < 1)
  {
    v6 = 0.0;
    goto LABEL_13;
  }
  v4 = (u32)probs->max_length;
  if (v4 >= 4)
  {
    v6 = 0.0;
    v7 = &probs[3];
    v5 = v4 - (probs->max_length & 3);
    v8 = v5;
    do
    {
      v9 = *(v7 - 3);
      v10 = *(v7 - 2);
      v8 -= 4;
      v11 = *(v7 - 1);
      v12 = *v7;
      v7 += 4;
      v6 = (f32)((f32)((f32)(v6 + v9) + v10) + v11) + v12;
    }
    while (v8);
    if ((max_length & 3) == 0)
      goto LABEL_13;
  }
  else
  {
    v5 = 0;
    v6 = 0.0;
  }
  v13 = max_length - v5;
  v14 = v5 + 1;
  if ((v13 & 1) != 0)
  {
    v15 = probs[v5++];
    v6 = v6 + v15;
  }
  if (v4 != v14)
  {
    v16 = v4 - v5;
    v17 = &probs[v5 + 1];
    do
    {
      v18 = *(v17 - 1);
      v19 = *v17;
      v16 -= 2;
      v17 += 2;
      v6 = (f32)(v6 + v18) + v19;
    }
    while (v16);
  }
LABEL_13:
  value = get_value(0);
  v21 = probs->max_length;
  result = v21 - 1;
  if ((s32)v21 >= 1)
  {
    v23 = v6 * value;
    v24 = 0;
    while (1)
    {
      v25 = probs[v24];
      if (v23 < v25)
        break;
      v23 = v23 - v25;
      if ((u32)probs->max_length == ++v24)
        return result;
    }
    return v24;
  }
  return result;
}

// 0x2295620
void dds3InitRandCB(void) {
  sdfRandCB_t *v1;

  v1 = Allocate(sdfRandCB_t);
  _ctor(v1, 0);
  CB = v1;
  Init(CB, 0x12345678u, 0);
}
