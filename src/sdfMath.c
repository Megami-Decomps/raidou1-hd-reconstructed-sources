#include "types.h"
#include "sdfmath.h"

#define sdfsin_1_p_pix2 0.15915494
#define sdfsin_pix3 4

f32 sdfSinTable[128];
static f32 *sdfTanTable;

static f32 TableInterpolation(f32 aValue, f32 *aTable);

// 0x225dcb0
f32 sdfDivSqrt(f32 aBase, f32 aValue) {
  return aBase / sqrtf(aValue);
}

// 0x225dd00
f32 sdfSin(f32 aRadius) {
  f32 v2;
  f32 v3;
  f32 v4;
  f32 v5;
  f32 v6;
  f32 v7;

  v2 = aRadius * 0.15915494;
  v3 = (s32)v2;
  if (v2 == INFINITY)
    v3 = -2147500000.0;
  v4 = v2 - v3;
  v5 = 0.5;
  if (v4 <= 0.5)
  {
    if (v4 >= -0.5)
      goto LABEL_8;
    v6 = 1.0;
  }
  else
  {
    v6 = -1.0;
  }
  v4 = v4 + v6;
LABEL_8:
  if (v4 > 0.25)
  {
LABEL_11:
    v4 = v5 - v4;
    goto LABEL_12;
  }
  if (v4 < -0.25)
  {
    v5 = -0.5;
    goto LABEL_11;
  }
LABEL_12:
  v7 = v4 * 4.0;
  return (f32)((f32)((f32)((f32)(v7 * 1.5707963) + (f32)((f32)(v7 * (f32)(v7 * v7)) * -0.6459637)) + (f32)((f32)((f32)(v7 * v7) * (f32)(v7 * (f32)(v7 * v7))) * 0.07968968)) + (f32)((f32)((f32)(v7 * v7) * (f32)((f32)(v7 * v7) * (f32)(v7 * (f32)(v7 * v7)))) * -0.0046737655))
       + (f32)((f32)((f32)(v7 * v7) * (f32)((f32)(v7 * v7) * (f32)((f32)(v7 * v7) * (f32)(v7 * (f32)(v7 * v7))))) * 0.00015148419);
}

// 0x225de00
f32 sdfCos(f32 aRadius) {
  f32 v2;
  f32 v3;
  f32 v4;
  f32 v5;
  f32 v6;
  f32 v7;

  v2 = (f32)(aRadius + 1.5708) * 0.15915494;
  v3 = (s32)v2;
  if (v2 == INFINITY)
    v3 = -2147500000.0;
  v4 = v2 - v3;
  v5 = 0.5;
  if (v4 <= 0.5)
  {
    if (v4 >= -0.5)
      goto LABEL_8;
    v6 = 1.0;
  }
  else
  {
    v6 = -1.0;
  }
  v4 = v4 + v6;
LABEL_8:
  if (v4 > 0.25)
  {
LABEL_11:
    v4 = v5 - v4;
    goto LABEL_12;
  }
  if (v4 < -0.25)
  {
    v5 = -0.5;
    goto LABEL_11;
  }
LABEL_12:
  v7 = v4 * 4.0;
  return (f32)((f32)((f32)((f32)(v7 * 1.5708) + (f32)((f32)(v7 * (f32)(v7 * v7)) * -0.6459637)) + (f32)((f32)((f32)(v7 * v7) * (f32)(v7 * (f32)(v7 * v7))) * 0.07968968)) + (f32)((f32)((f32)(v7 * v7) * (f32)((f32)(v7 * v7) * (f32)(v7 * (f32)(v7 * v7)))) * -0.0046737655))
       + (f32)((f32)((f32)(v7 * v7) * (f32)((f32)(v7 * v7) * (f32)((f32)(v7 * v7) * (f32)(v7 * (f32)(v7 * v7))))) * 0.00015148419);
}

// 0x225df10
static f32 TableInterpolation(f32 aValue, f32 *aTable) {
  s32 v3;
  s32 max_length;
  u32 v5;
  s32 v6;
  f32 v7;
  s32 v8;
  f32 v9;

  v3 = 0;
  max_length = aTable->max_length;
  do
  {
    v5 = max_length + v3;
    v6 = (max_length + v3) >> 1;
    v7 = aTable[v6];
    v8 = v6;
    if (v7 <= aValue)
    {
      v3 = v6 + 1;
      v8 = max_length;
    }
    max_length = v8;
  }
  while (v3 < v8);
  v9 = 0.0;
  if (v5 >= 2)
    v9 = *((f32 *)&aTable->max_length + ((s64)(s32)v5 >> 1) + 1);
  return (f32)((f32)(1.0 / (f32)SLODWORD(aTable->max_length)) * (f32)v6)
       + (f32)((f32)((f32)(1.0 / (f32)SLODWORD(aTable->max_length)) * (f32)(aValue - v9)) / (f32)(v7 - v9));
}

// 0x225dfa0
f32 sdfAtan(f32 aX) {
  f32 v3;
  _BOOL4 v4;
  _BOOL4 v5;
  s32 v6;
  s32 v7;
  f32 *sdfTanTable_local;
  s32 max_length;
  u32 v10;
  s32 v11;
  f32 v12;
  s32 v13;
  f32 result;
  f32 v15;

  if (aX >= 0.0)
    v3 = aX;
  else
    v3 = -aX;
  v4 = v3 > 1.0;
  if (v3 > 1.0)
    v3 = 1.0 / v3;
  v5 = v3 < 1.0 && aX < 0.0;
  v6 = v3 < 1.0 && v4;
  if (v3 < 1.0)
  {
    v7 = 0;
    sdfTanTable_local = sdfTanTable;
    max_length = sdfTanTable_local->max_length;
    do
    {
      v10 = max_length + v7;
      v11 = (max_length + v7) >> 1;
      v12 = sdfTanTable_local[v11];
      v13 = v11;
      if (v12 <= v3)
      {
        v7 = v11 + 1;
        v13 = max_length;
      }
      max_length = v13;
    }
    while (v7 < v13);
    v15 = 0.0;
    if (v10 >= 2)
      v15 = *((f32 *)&sdfTanTable_local->max_length + ((s64)(s32)v10 >> 1) + 1);
    result = (f32)((f32)((f32)(1.0 / (f32)SLODWORD(sdfTanTable_local->max_length)) * (f32)v11) + (f32)((f32)((f32)(1.0 / (f32)SLODWORD(sdfTanTable_local->max_length)) * (f32)(v3 - v15)) / (f32)(v12 - v15)))
           * 0.7853982;
  }
  else
  {
    result = 0.7853982;
    v6 = v4;
    v5 = aX < 0.0;
  }
  if (v6)
    result = 1.5707964 - result;
  if (v5)
    return -result;
  return result;
}

// 0x225e100
f32 sdfAtan2(f32 aY, f32 aX) {
  f32 result;
  f32 v6;
  f32 v7;
  f32 v8;
  f32 v9;
  _BOOL4 v10;
  _BOOL4 v11;
  s32 v12;
  s32 v13;
  f32 *v14;
  s32 v15;
  u32 v16;
  s32 v17;
  f32 v18;
  s32 v19;
  f32 v20;
  f32 v21;
  _BOOL4 v22;
  _BOOL4 v23;
  s32 v24;
  s32 v25;
  f32 *sdfTanTable_local;
  s32 max_length;
  u32 v28;
  s32 v29;
  f32 v30;
  s32 v31;
  f32 v32;
  f32 v33;
  f32 v34;

  if (aY != 0.0 || (result = 0.0, aX != 0.0))
  {
    v6 = -aX;
    v7 = -aY;
    if (aX >= 0.0)
      v6 = aX;
    if (aY >= 0.0)
      v7 = aY;
    if (v6 <= v7)
    {
      v20 = v6 / v7;
      if (v20 >= 0.0)
        v21 = v20;
      else
        v21 = -v20;
      v22 = v21 > 1.0;
      if (v21 > 1.0)
        v21 = 1.0 / v21;
      v23 = v21 < 1.0 && v20 < 0.0;
      v24 = v21 < 1.0 && v22;
      if (v21 < 1.0)
      {
        v25 = 0;
        sdfTanTable_local = sdfTanTable;
        max_length = sdfTanTable_local->max_length;
        do
        {
          v28 = max_length + v25;
          v29 = (max_length + v25) >> 1;
          v30 = sdfTanTable_local[v29];
          v31 = v29;
          if (v30 <= v21)
          {
            v25 = v29 + 1;
            v31 = max_length;
          }
          max_length = v31;
        }
        while (v25 < v31);
        v34 = 0.0;
        if (v28 >= 2)
          v34 = *((f32 *)&sdfTanTable_local->max_length + ((s64)(s32)v28 >> 1) + 1);
        v33 = (f32)((f32)((f32)(1.0 / (f32)SLODWORD(sdfTanTable_local->max_length)) * (f32)v29) + (f32)((f32)((f32)(1.0 / (f32)SLODWORD(sdfTanTable_local->max_length)) * (f32)(v21 - v34)) / (f32)(v30 - v34)))
            * 0.7853982;
      }
      else
      {
        v33 = 0.7853982;
        v24 = v22;
        v23 = v20 < 0.0;
      }
      if (v24)
        v33 = 1.5707964 - v33;
      if (v23)
        v33 = -v33;
      result = 1.5707964 - v33;
    }
    else
    {
      v8 = v7 / v6;
      if (v8 >= 0.0)
        v9 = v8;
      else
        v9 = -v8;
      v10 = v9 > 1.0;
      if (v9 > 1.0)
        v9 = 1.0 / v9;
      v11 = v9 < 1.0 && v8 < 0.0;
      v12 = v9 < 1.0 && v10;
      if (v9 < 1.0)
      {
        v13 = 0;
        v14 = sdfTanTable;
        v15 = v14->max_length;
        do
        {
          v16 = v15 + v13;
          v17 = (v15 + v13) >> 1;
          v18 = v14[v17];
          v19 = v17;
          if (v18 <= v9)
          {
            v13 = v17 + 1;
            v19 = v15;
          }
          v15 = v19;
        }
        while (v13 < v19);
        v32 = 0.0;
        if (v16 >= 2)
          v32 = *((f32 *)&v14->max_length + ((s64)(s32)v16 >> 1) + 1);
        result = (f32)((f32)((f32)(1.0 / (f32)SLODWORD(v14->max_length)) * (f32)v17) + (f32)((f32)((f32)(1.0 / (f32)SLODWORD(v14->max_length)) * (f32)(v9 - v32)) / (f32)(v18 - v32)))
               * 0.7853982;
      }
      else
      {
        result = 0.7853982;
        v12 = v10;
        v11 = v8 < 0.0;
      }
      if (v12)
        result = 1.5707964 - result;
      if (v11)
        result = -result;
    }
    if (aX < 0.0)
      result = 3.1415927 - result;
    if (aY < 0.0)
      return -result;
  }
  return result;
}

// 0x225e420
f32 sdfAcos(f32 aX) {
  f32 v3;
  f32 v4;
  s32 v5;
  f32 *sdfSinTable_local;
  s32 max_length;
  u32 v8;
  s32 v9;
  f32 v10;
  s32 v11;
  f32 v12;
  f32 result;

  v3 = 0.0;
  if (aX >= 0.0)
    v4 = aX;
  else
    v4 = -aX;
  if (v4 < 1.0)
  {
    v5 = 0;
    sdfSinTable_local = sdfSinTable;
    max_length = sdfSinTable_local->max_length;
    do
    {
      v8 = max_length + v5;
      v9 = (max_length + v5) >> 1;
      v10 = sdfSinTable_local[v9];
      v11 = v9;
      if (v10 <= v4)
      {
        v5 = v9 + 1;
        v11 = max_length;
      }
      max_length = v11;
    }
    while (v5 < v11);
    v12 = 0.0;
    if (v8 >= 2)
      v12 = *((f32 *)&sdfSinTable_local->max_length + ((s64)(s32)v8 >> 1) + 1);
    v3 = (f32)(1.0 - (f32)((f32)((f32)(1.0 / (f32)SLODWORD(sdfSinTable_local->max_length)) * (f32)v9) + (f32)((f32)((f32)(1.0 / (f32)SLODWORD(sdfSinTable_local->max_length)) * (f32)(v4 - v12)) / (f32)(v10 - v12))))
       * 1.5707964;
  }
  result = -v3;
  if (aX >= 0.0)
    return v3;
  return result;
}

// 0x225e540
f32 sdfClipAngleValuePI(f32 aValue) {
  f32 v2;
  f32 v3;
  f32 v4;

  if (aValue <= 3.1415927)
  {
    if (aValue >= -3.1415927)
      return aValue;
    v2 = aValue / 6.2831855;
    v3 = (f32)((s32)(f32)(aValue / 6.2831855) - 1) * 6.2831855;
    v4 = 13493038000.0;
  }
  else
  {
    v2 = aValue / 6.2831855;
    v3 = (f32)((s32)(f32)(aValue / 6.2831855) + 1) * 6.2831855;
    v4 = -13493038000.0;
  }
  if (v2 == INFINITY)
    v3 = v4;
  return aValue - v3;
}

// 0x225e5e0
sdfVector3_t sdfMultiply(void *mtx, const sdfVector3_t *vct) {
  u64 v3;
  sdfVector3_t result;

  v3 = vadd_f32(vadd_f32(vadd_f32(vmul_n_f32(*(float32x2_t *)&mtx->c0.x, vct->x), vmul_n_f32(*(float32x2_t *)&mtx->c1.x, vct->y)), vmul_n_f32(*(float32x2_t *)&mtx->c2.x, vct->z)), *(float32x2_t *)&mtx->c3.x).n64_u64[0];
  result.z = (f32)((f32)((f32)(vct->x * mtx->c0.z) + (f32)(vct->y * mtx->c1.z)) + (f32)(vct->z * mtx->c2.z))
                  + mtx->c3.z;
  result.y = *((f32 *)&v3 + 1);
  LODWORD(result.x) = v3;
  return result;
}

// 0x225e640
sdfVector3_t sdfTransposeMultiply(void *mtx, const sdfVector3_t *vct) {
  f32 v3;
  f32 v4;
  sdfVector3_t result;

  v3 = mtx->c0.w
     + (f32)((f32)((f32)(vct->x * mtx->c0.x) + (f32)(vct->y * mtx->c0.y)) + (f32)(vct->z * mtx->c0.z));
  v4 = mtx->c1.w
     + (f32)((f32)((f32)(vct->x * mtx->c1.x) + (f32)(vct->y * mtx->c1.y)) + (f32)(vct->z * mtx->c1.z));
  result.z = mtx->c2.w
                  + (f32)((f32)((f32)(vct->x * mtx->c2.x) + (f32)(vct->y * mtx->c2.y)) + (f32)(vct->z * mtx->c2.z));
  result.x = v3;
  result.y = v4;
  return result;
}

// 0x225e6b0
void Init(void *list) {
  Il2CppObject *Asset_object;
  Il2CppObject *v4;
  u8 *monitor;
  sdfBinary *v6;
  f32 *v7;
  s64 v9;
  f32 Float;
  f32 *v11;
  f32 *v12;
  s64 v15;
  f32 v16;
  f32 *v17;

  Asset_object = GetAsset_object_(list, "sdfTriFuncTable.dsm");
    v4 = Asset_object;
  else
    v4 = 0;
  monitor = v4[1].monitor;
  v6 = Allocate(sdfBinary);
  _ctor_36176832(v6, monitor, 0);
  v7 = NewSpecific(f32, 0x80u);
  sdfSinTable = v7;
  if (SLODWORD(sdfSinTable->max_length) >= 1)
  {
    v9 = 0;
    do
    {
      Float = ReadFloat(v6, 0);
      v11 = ((char *)sdfSinTable + 4 * v9++);
      v11[8] = Float;
    }
    while (v9 < SLODWORD(sdfSinTable->max_length));
  }
  v12 = NewSpecific(f32, 0x40u);
  sdfTanTable = v12;
  if (SLODWORD(sdfTanTable->max_length) >= 1)
  {
    v15 = 0;
    do
    {
      v16 = ReadFloat(v6, 0);
      v17 = ((char *)sdfTanTable + 4 * v15++);
      v17[8] = v16;
    }
    while (v15 < SLODWORD(sdfTanTable->max_length));
  }
}
