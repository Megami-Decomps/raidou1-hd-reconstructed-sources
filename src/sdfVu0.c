#include "types.h"
#include "sdf_vu0.h"
#include "sdfvu0.h"

sdfMatrix4_t IdentityMatrix;
sdfVector4_t AllOneVector;

// 0x226e0a0
void sdfVu0LoadMatrix(sdfMatrix4_t *aMatrix) {
  _OWORD *p_x;
  __int128 v6;
  __int128 v7;
  __int128 v8;
  __int128 v9;

  v6 = *(_OWORD *)&aMatrix->m00;
  v7 = *(_OWORD *)&aMatrix->m01;
  v8 = *(_OWORD *)&aMatrix->m02;
  v9 = *(_OWORD *)&aMatrix->m03;
  p_x = &vf00.x;
  p_x[4] = v6;
  p_x[5] = v7;
  p_x[6] = v8;
  p_x[7] = v9;
}

// 0x226e180
void LoadMatrix_B(sdfMatrix4_t *aMatrix) {
  _OWORD *p_x;
  __int128 v6;
  __int128 v7;
  __int128 v8;
  __int128 v9;

  v6 = *(_OWORD *)&aMatrix->m00;
  v7 = *(_OWORD *)&aMatrix->m01;
  v8 = *(_OWORD *)&aMatrix->m02;
  v9 = *(_OWORD *)&aMatrix->m03;
  p_x = &vf00.x;
  p_x[8] = v6;
  p_x[9] = v7;
  p_x[10] = v8;
  p_x[11] = v9;
}

// 0x226e260
void sdfVu0StoreMatrix(sdfMatrix4_t *aMatrix) {
  _OWORD *p_x;
  __int128 v6;
  __int128 v7;
  __int128 v8;

  p_x = &vf00.x;
  v6 = p_x[5];
  v7 = p_x[6];
  v8 = p_x[7];
  *(_OWORD *)&aMatrix->m00 = p_x[4];
  *(_OWORD *)&aMatrix->m01 = v6;
  *(_OWORD *)&aMatrix->m02 = v7;
  *(_OWORD *)&aMatrix->m03 = v8;
}

// 0x226e330
void StoreMatrix_B(sdfMatrix4_t *aMatrix) {
  _OWORD *p_x;
  __int128 v6;
  __int128 v7;
  __int128 v8;

  p_x = &vf00.x;
  v6 = p_x[9];
  v7 = p_x[10];
  v8 = p_x[11];
  *(_OWORD *)&aMatrix->m00 = p_x[8];
  *(_OWORD *)&aMatrix->m01 = v6;
  *(_OWORD *)&aMatrix->m02 = v7;
  *(_OWORD *)&aMatrix->m03 = v8;
}

// 0x226e400
void CopyMatrixAtoB(void) {
  _OWORD *p_x;
  __int128 v4;
  __int128 v5;

  p_x = &vf00.x;
  v4 = p_x[5];
  p_x[8] = p_x[4];
  p_x[9] = v4;
  v5 = p_x[7];
  p_x[10] = p_x[6];
  p_x[11] = v5;
}

// 0x226e4c0
void CopyMatrixAtoC(void) {
  _OWORD *p_x;
  __int128 v4;
  __int128 v5;

  p_x = &vf00.x;
  v4 = p_x[5];
  p_x[12] = p_x[4];
  p_x[13] = v4;
  v5 = p_x[7];
  p_x[14] = p_x[6];
  p_x[15] = v5;
}

// 0x226e580
void CopyMatrixBtoA(void) {
  _OWORD *p_x;
  __int128 v4;
  __int128 v5;

  p_x = &vf00.x;
  v4 = p_x[9];
  p_x[4] = p_x[8];
  p_x[5] = v4;
  v5 = p_x[11];
  p_x[6] = p_x[10];
  p_x[7] = v5;
}

// 0x226e640
void CopyMatrixBtoC(void) {
  _OWORD *p_x;
  __int128 v4;
  __int128 v5;

  p_x = &vf00.x;
  v4 = p_x[5];
  p_x[12] = p_x[4];
  p_x[13] = v4;
  v5 = p_x[7];
  p_x[14] = p_x[6];
  p_x[15] = v5;
}

// 0x226e700
void CopyMatrixCtoA(void) {
  _OWORD *p_x;
  __int128 v4;
  __int128 v5;

  p_x = &vf00.x;
  v4 = p_x[13];
  p_x[4] = p_x[12];
  p_x[5] = v4;
  v5 = p_x[15];
  p_x[6] = p_x[14];
  p_x[7] = v5;
}

// 0x226e7c0
void CopyMatrixCtoB(void) {
  _OWORD *p_x;
  __int128 v4;
  __int128 v5;

  p_x = &vf00.x;
  v4 = p_x[13];
  p_x[8] = p_x[12];
  p_x[9] = v4;
  v5 = p_x[15];
  p_x[10] = p_x[14];
  p_x[11] = v5;
}

// 0x226e880
void LoadIdentity(void) {
  mtx_A = identityMatrix;
}

// 0x226e990
void LoadIdentity_B(void) {
  mtx_B = identityMatrix;
}

// 0x226eaa0
void StoreIdentity(sdfMatrix4_t *aMatrix) {
  __int128 v5;
  __int128 v6;
  __int128 v7;

  v5 = *(_OWORD *)&identityMatrix.m01;
  v6 = *(_OWORD *)&identityMatrix.m02;
  v7 = *(_OWORD *)&identityMatrix.m03;
  *(_OWORD *)&aMatrix->m00 = *(_OWORD *)&identityMatrix.m00;
  *(_OWORD *)&aMatrix->m01 = v5;
  *(_OWORD *)&aMatrix->m02 = v6;
  *(_OWORD *)&aMatrix->m03 = v7;
}

// 0x226eb60
void DiagMatrix(void) {
  __int128 v3;
  __int128 v4;
  sdfMatrix4_t v5;

  get_transpose(&v5, &mtx_A, 0);
  v3 = *(_OWORD *)&v5.m01;
  *(_OWORD *)&mtx_A.m00 = *(_OWORD *)&v5.m00;
  *(_OWORD *)&mtx_A.m01 = v3;
  v4 = *(_OWORD *)&v5.m03;
  *(_OWORD *)&mtx_A.m02 = *(_OWORD *)&v5.m02;
  *(_OWORD *)&mtx_A.m03 = v4;
}

// 0x226ebf0
void sdfVu0ReverseMatrix(void) {
  f32 v4;
  __int128 v6;
  __int128 v7;
  sdfMatrix4_t v8;
  f32 x;
  f32 y;
  sdfVector4_t v11;
  sdfVector4_t v12;
  sdfVector4_t Column;
  sdfVector4_t v14;
  sdfVector4_t v15;
  sdfVector4_t v16;
  sdfVector4_t v17;

  Column = GetColumn(&mtx_A, 0, 0);
  x = Column.x;
  y = Column.y;
  v14 = GetColumn(&mtx_A, 1, 0);
  v15 = GetColumn(&mtx_A, 2, 0);
  v16.y = v14.x;
  v16.x = x;
  v17.x = y;
  *(u64 *)&v11.x = 0;
  v16.w = (f32)((f32)(zeroVector.x - (f32)(x * Column.w)) - (f32)(v14.x * v14.w))
               - (f32)(v15.x * v15.w);
  v4 = (f32)(zeroVector.y - (f32)(y * Column.w)) - (f32)(v14.y * v14.w);
  memset(&v8, 0, sizeof(v8));
  v17.w = v4 - (f32)(v15.y * v15.w);
  v17.y = v14.y;
  v16.z = v15.x;
  v17.z = v15.y;
  _ctor(&v8, v16, v17, v11, v12);
  v6 = *(_OWORD *)&v8.m01;
  *(_OWORD *)&mtx_A.m00 = *(_OWORD *)&v8.m00;
  *(_OWORD *)&mtx_A.m01 = v6;
  v7 = *(_OWORD *)&v8.m03;
  *(_OWORD *)&mtx_A.m02 = *(_OWORD *)&v8.m02;
  *(_OWORD *)&mtx_A.m03 = v7;
}

// 0x226ede0
void InversMatrix(void) {
  f32 v2;
  f32 v3;
  f32 v4;
  f32 v5;
  f32 v6;
  f32 v7;
  __int128 v10;
  __int128 v11;
  f32 v12;
  f32 v13;
  f32 v14;
  f32 v15;
  f32 v16;
  sdfMatrix4_t v17;
  sdfVector4_t v18;
  sdfVector4_t v19;
  sdfVector4_t Column;
  sdfVector4_t v21;
  sdfVector4_t v22;
  sdfVector4_t v23;
  sdfVector4_t v24;

  Column = GetColumn(&mtx_A, 0, 0);
  v21 = GetColumn(&mtx_A, 1, 0);
  v22 = GetColumn(&mtx_A, 2, 0);
  v2 = 1.0
     / (f32)((f32)(Column.z * Column.z) + (f32)((f32)(Column.x * Column.x) + (f32)(Column.y * Column.y)));
  v3 = 1.0
     / (f32)((f32)(v21.z * v21.z) + (f32)((f32)(v21.x * v21.x) + (f32)(v21.y * v21.y)));
  v15 = Column.x * v2;
  v16 = Column.y * v3;
  v4 = 1.0
     / (f32)((f32)(v22.z * v22.z) + (f32)((f32)(v22.x * v22.x) + (f32)(v22.y * v22.y)));
  v5 = v2 * v22.x;
  v6 = v22.y * v3;
  v7 = v21.x * v2;
  v13 = v21.y * v3;
  v14 = (f32)((f32)-(f32)((f32)(Column.x * v2) * Column.w) - (f32)(v21.w * (f32)(Column.y * v3)))
      - (f32)(v22.w * (f32)(Column.z * v4));
  v12 = (f32)((f32)-(f32)((f32)(v21.x * v2) * Column.w) - (f32)(v21.w * (f32)(v21.y * v3)))
      - (f32)(v22.w * (f32)(v21.z * v4));
  get_Item_60922080(&mtx_A, 15, 0);
  v24.x = v16;
  v23.w = v14;
  v23.x = v15;
  v23.z = v5;
  v24.w = v12;
  v24.y = v13;
  v24.z = v6;
  memset(&v17, 0, sizeof(v17));
  v23.y = v7;
  *(u64 *)&v18.x = 0;
  _ctor(&v17, v23, v24, v18, v19);
  v10 = *(_OWORD *)&v17.m01;
  *(_OWORD *)&mtx_A.m00 = *(_OWORD *)&v17.m00;
  *(_OWORD *)&mtx_A.m01 = v10;
  v11 = *(_OWORD *)&v17.m03;
  *(_OWORD *)&mtx_A.m02 = *(_OWORD *)&v17.m02;
  *(_OWORD *)&mtx_A.m03 = v11;
}

// 0x226eff0
void sdfVu0StoreRotateMatrixX(f32 aAngle, sdfMatrix4_t *aMtx) {
  f32 v4;
  s64 v5;
  s64 v6;
  s64 v7;
  f32 v8;
  __int128 v10;
  __int128 v11;
  __int128 v12;

  v4 = sub_188E3D0(aAngle);
  v8 = sub_188E3C0(v5, v6, v7);
  v10 = *(_OWORD *)&identityMatrix.m01;
  v11 = *(_OWORD *)&identityMatrix.m02;
  v12 = *(_OWORD *)&identityMatrix.m03;
  *(_OWORD *)&aMtx->m00 = *(_OWORD *)&identityMatrix.m00;
  *(_OWORD *)&aMtx->m01 = v10;
  *(_OWORD *)&aMtx->m02 = v11;
  *(_OWORD *)&aMtx->m03 = v12;
  set_Item_60922352(aMtx, 5, v8, 0);
  set_Item_60922352(aMtx, 9, v4, 0);
  set_Item_60922352(aMtx, 6, -v4, 0);
  set_Item_60922352(aMtx, 10, v8, 0);
}

// 0x226f0c0
void sdfVu0StoreRotateMatrixY(f32 aAngle, sdfMatrix4_t *aMtx) {
  f32 v4;
  s64 v5;
  s64 v6;
  s64 v7;
  f32 v8;
  __int128 v10;
  __int128 v11;
  __int128 v12;

  v4 = sub_188E3D0(aAngle);
  v8 = sub_188E3C0(v5, v6, v7);
  v10 = *(_OWORD *)&identityMatrix.m01;
  v11 = *(_OWORD *)&identityMatrix.m02;
  v12 = *(_OWORD *)&identityMatrix.m03;
  *(_OWORD *)&aMtx->m00 = *(_OWORD *)&identityMatrix.m00;
  *(_OWORD *)&aMtx->m01 = v10;
  *(_OWORD *)&aMtx->m02 = v11;
  *(_OWORD *)&aMtx->m03 = v12;
  set_Item_60922352(aMtx, 0, v8, 0);
  set_Item_60922352(aMtx, 8, -v4, 0);
  set_Item_60922352(aMtx, 2, v4, 0);
  set_Item_60922352(aMtx, 10, v8, 0);
}

// 0x226f190
void sdfVu0StoreRotateMatrixZ(f32 aAngle, sdfMatrix4_t *aMtx) {
  f32 v4;
  s64 v5;
  s64 v6;
  s64 v7;
  f32 v8;
  __int128 v10;
  __int128 v11;
  __int128 v12;

  v4 = sub_188E3D0(aAngle);
  v8 = sub_188E3C0(v5, v6, v7);
  v10 = *(_OWORD *)&identityMatrix.m01;
  v11 = *(_OWORD *)&identityMatrix.m02;
  v12 = *(_OWORD *)&identityMatrix.m03;
  *(_OWORD *)&aMtx->m00 = *(_OWORD *)&identityMatrix.m00;
  *(_OWORD *)&aMtx->m01 = v10;
  *(_OWORD *)&aMtx->m02 = v11;
  *(_OWORD *)&aMtx->m03 = v12;
  set_Item_60922352(aMtx, 0, v8, 0);
  set_Item_60922352(aMtx, 4, v4, 0);
  set_Item_60922352(aMtx, 1, -v4, 0);
  set_Item_60922352(aMtx, 5, v8, 0);
}

// 0x226f260
void SetRotateMatrixX(f32 aAngle) {
  f32 v6;
  s64 v7;
  s64 v8;
  s64 v9;
  f32 v10;
  __int128 v12;
  __int128 v13;
  __int128 v14;

  v6 = sub_188E3D0(aAngle);
  v10 = sub_188E3C0(v7, v8, v9);
  v12 = *(_OWORD *)&identityMatrix.m02;
  v13 = *(_OWORD *)&identityMatrix.m03;
  v14 = *(_OWORD *)&identityMatrix.m01;
  *(_OWORD *)&mtx_A.m00 = *(_OWORD *)&identityMatrix.m00;
  *(_OWORD *)&mtx_A.m01 = v14;
  *(_OWORD *)&mtx_A.m02 = v12;
  *(_OWORD *)&mtx_A.m03 = v13;
  set_Item_60922352(&mtx_A, 5, v10, 0);
  set_Item_60922352(&mtx_A, 9, v6, 0);
  set_Item_60922352(&mtx_A, 6, -v6, 0);
  set_Item_60922352(&mtx_A, 10, v10, 0);
}

// 0x226f3c0
void sdfVu0SetRotateMatrixY(f32 aAngle) {
  f32 v6;
  s64 v7;
  s64 v8;
  s64 v9;
  f32 v10;
  __int128 v12;
  __int128 v13;
  __int128 v14;

  v6 = sub_188E3D0(aAngle);
  v10 = sub_188E3C0(v7, v8, v9);
  v12 = *(_OWORD *)&identityMatrix.m02;
  v13 = *(_OWORD *)&identityMatrix.m03;
  v14 = *(_OWORD *)&identityMatrix.m01;
  *(_OWORD *)&mtx_A.m00 = *(_OWORD *)&identityMatrix.m00;
  *(_OWORD *)&mtx_A.m01 = v14;
  *(_OWORD *)&mtx_A.m02 = v12;
  *(_OWORD *)&mtx_A.m03 = v13;
  set_Item_60922352(&mtx_A, 0, v10, 0);
  set_Item_60922352(&mtx_A, 8, -v6, 0);
  set_Item_60922352(&mtx_A, 2, v6, 0);
  set_Item_60922352(&mtx_A, 10, v10, 0);
}

// 0x226f520
void SetRotateMatrixZ(f32 aAngle) {
  f32 v6;
  s64 v7;
  s64 v8;
  s64 v9;
  f32 v10;
  __int128 v12;
  __int128 v13;
  __int128 v14;

  v6 = sub_188E3D0(aAngle);
  v10 = sub_188E3C0(v7, v8, v9);
  v12 = *(_OWORD *)&identityMatrix.m02;
  v13 = *(_OWORD *)&identityMatrix.m03;
  v14 = *(_OWORD *)&identityMatrix.m01;
  *(_OWORD *)&mtx_A.m00 = *(_OWORD *)&identityMatrix.m00;
  *(_OWORD *)&mtx_A.m01 = v14;
  *(_OWORD *)&mtx_A.m02 = v12;
  *(_OWORD *)&mtx_A.m03 = v13;
  set_Item_60922352(&mtx_A, 0, v10, 0);
  set_Item_60922352(&mtx_A, 4, v6, 0);
  set_Item_60922352(&mtx_A, 1, -v6, 0);
  set_Item_60922352(&mtx_A, 5, v10, 0);
}

// 0x226f680
void StoreRotateMatrixAxis(f32 aAngle, const sdfVector4_t *aAxis, sdfMatrix4_t *aMtx) {
  f32 z;
  f32 y;
  f32 x;
  f32 v10;
  f32 v11;
  f32 v12;
  f32 v13;
  f32 v15;
  s64 v16;
  s64 v17;
  s64 v18;
  f32 v20;
  f32 v21;
  __int128 v22;
  __int128 v23;
  sdfMatrix4_t v24;
  sdfVector4_t v25;
  sdfVector4_t v26;
  sdfVector4_t v27;
  sdfVector4_t v28;

  z = aAxis->z;
  y = aAxis->y;
  x = aAxis->x;
  v10 = sqrtf((f32)(z * z) + (f32)((f32)(x * x) + (f32)(y * y)));
  if (v10 <= 0.00001)
  {
    v11 = zeroVector.x;
    v12 = zeroVector.y;
    v13 = zeroVector.z;
  }
  else
  {
    v11 = x / v10;
    v12 = y / v10;
    v13 = z / v10;
  }
  v15 = sub_188E3D0(aAngle);
  v20 = sub_188E3C0(v16, v17, v18);
  *(u64 *)&v25.x = 0;
  memset(&v24, 0, sizeof(v24));
  v21 = (f32)(v11 * v12) * (f32)(1.0 - v20);
  v28.z = (f32)((f32)(v12 * v13) * (f32)(1.0 - v20)) - (f32)(v11 * v15);
  v27.z = (f32)(v12 * v15) + (f32)((f32)(v11 * v13) * (f32)(1.0 - v20));
  v28.x = (f32)(v13 * v15) + v21;
  v27.y = v21 - (f32)(v13 * v15);
  v28.y = (f32)(v12 * v12) + (f32)((f32)(1.0 - (f32)(v12 * v12)) * v20);
  v27.w = 0.0;
  v27.x = (f32)(v11 * v11) + (f32)((f32)(1.0 - (f32)(v11 * v11)) * v20);
  v28.w = 0.0;
  _ctor(&v24, v27, v28, v25, v26);
  v22 = *(_OWORD *)&v24.m01;
  *(_OWORD *)&aMtx->m00 = *(_OWORD *)&v24.m00;
  *(_OWORD *)&aMtx->m01 = v22;
  v23 = *(_OWORD *)&v24.m03;
  *(_OWORD *)&aMtx->m02 = *(_OWORD *)&v24.m02;
  *(_OWORD *)&aMtx->m03 = v23;
}

// 0x226f8d0
void sdfVu0SetRotateMatrixAxis(f32 aAngle, const sdfVector4_t *aAxis) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;

  w = aAxis->w;
  z = aAxis->z;
  y = aAxis->y;
  x = aAxis->x;
  sub_197D860(&mtx_A, 0, aAngle, x, y, z, w);
}

// 0x226f9c0
void sdfVu0SetRotateMatrixX_B(f32 aAngle) {
  f32 v6;
  s64 v7;
  s64 v8;
  s64 v9;
  f32 v10;
  __int128 v12;
  __int128 v13;
  __int128 v14;

  v6 = sub_188E3D0(aAngle);
  v10 = sub_188E3C0(v7, v8, v9);
  v12 = *(_OWORD *)&identityMatrix.m02;
  v13 = *(_OWORD *)&identityMatrix.m03;
  v14 = *(_OWORD *)&identityMatrix.m01;
  *(_OWORD *)&mtx_B.m00 = *(_OWORD *)&identityMatrix.m00;
  *(_OWORD *)&mtx_B.m01 = v14;
  *(_OWORD *)&mtx_B.m02 = v12;
  *(_OWORD *)&mtx_B.m03 = v13;
  set_Item_60922352(&mtx_B, 5, v10, 0);
  set_Item_60922352(&mtx_B, 9, v6, 0);
  set_Item_60922352(&mtx_B, 6, -v6, 0);
  set_Item_60922352(&mtx_B, 10, v10, 0);
}

// 0x226fb20
void SetRotateMatrixY_B(f32 aAngle) {
  f32 v6;
  s64 v7;
  s64 v8;
  s64 v9;
  f32 v10;
  __int128 v12;
  __int128 v13;
  __int128 v14;

  v6 = sub_188E3D0(aAngle);
  v10 = sub_188E3C0(v7, v8, v9);
  v12 = *(_OWORD *)&identityMatrix.m02;
  v13 = *(_OWORD *)&identityMatrix.m03;
  v14 = *(_OWORD *)&identityMatrix.m01;
  *(_OWORD *)&mtx_B.m00 = *(_OWORD *)&identityMatrix.m00;
  *(_OWORD *)&mtx_B.m01 = v14;
  *(_OWORD *)&mtx_B.m02 = v12;
  *(_OWORD *)&mtx_B.m03 = v13;
  set_Item_60922352(&mtx_B, 0, v10, 0);
  set_Item_60922352(&mtx_B, 8, -v6, 0);
  set_Item_60922352(&mtx_B, 2, v6, 0);
  set_Item_60922352(&mtx_B, 10, v10, 0);
}

// 0x226fc80
void sdfVu0SetRotateMatrixZ_B(f32 aAngle) {
  f32 v6;
  s64 v7;
  s64 v8;
  s64 v9;
  f32 v10;
  __int128 v12;
  __int128 v13;
  __int128 v14;

  v6 = sub_188E3D0(aAngle);
  v10 = sub_188E3C0(v7, v8, v9);
  v12 = *(_OWORD *)&identityMatrix.m02;
  v13 = *(_OWORD *)&identityMatrix.m03;
  v14 = *(_OWORD *)&identityMatrix.m01;
  *(_OWORD *)&mtx_B.m00 = *(_OWORD *)&identityMatrix.m00;
  *(_OWORD *)&mtx_B.m01 = v14;
  *(_OWORD *)&mtx_B.m02 = v12;
  *(_OWORD *)&mtx_B.m03 = v13;
  set_Item_60922352(&mtx_B, 0, v10, 0);
  set_Item_60922352(&mtx_B, 4, v6, 0);
  set_Item_60922352(&mtx_B, 1, -v6, 0);
  set_Item_60922352(&mtx_B, 5, v10, 0);
}

// 0x226fde0
void SetRotateMatrixAxis_B(f32 aAngle, const sdfVector4_t *aAxis) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;

  w = aAxis->w;
  z = aAxis->z;
  y = aAxis->y;
  x = aAxis->x;
  sub_197D860(&mtx_B, 0, aAngle, x, y, z, w);
}

// 0x226fed0
void RotateMatrixX(f32 aAngle) {
  f32 v3;
  s64 v4;
  s64 v5;
  s64 v6;
  f32 v7;
  f32 v9;
  sdfVector4_t Row;
  sdfVector4_t v11;
  sdfVector4_t v12;
  sdfVector4_t v13;

  v3 = sub_188E3D0(aAngle);
  v7 = sub_188E3C0(v4, v5, v6);
  v9 = v7;
  Row = GetRow(&mtx_A, 1, 0);
  v11 = GetRow(&mtx_A, 2, 0);
  v12.x = (f32)(v9 * Row.x) + (f32)(v3 * v11.x);
  v12.y = (f32)(v9 * Row.y) + (f32)(v3 * v11.y);
  v12.z = (f32)(v9 * Row.z) + (f32)(v3 * v11.z);
  v12.w = (f32)(v9 * Row.w) + (f32)(v3 * v11.w);
  SetRow(&mtx_A, 1, v12, 0);
  v13.z = (f32)(v9 * v11.z) - (f32)(v3 * Row.z);
  v13.w = (f32)(v9 * v11.w) - (f32)(v3 * Row.w);
  v13.x = (f32)(v9 * v11.x) - (f32)(v3 * Row.x);
  v13.y = (f32)(v9 * v11.y) - (f32)(v3 * Row.y);
  SetRow(&mtx_A, 2, v13, 0);
}

// 0x2270050
void RotateMatrixY(f32 aAngle) {
  f32 v3;
  s64 v4;
  s64 v5;
  s64 v6;
  f32 v7;
  f32 v9;
  f32 v10;
  f32 v11;
  f32 v12;
  f32 v13;
  f32 v14;
  f32 v15;
  f32 v16;
  f32 v17;
  sdfVector4_t Row;
  sdfVector4_t v19;
  sdfVector4_t v20;
  sdfVector4_t v21;

  v3 = sub_188E3D0(aAngle);
  v7 = sub_188E3C0(v4, v5, v6);
  v9 = v7;
  Row = GetRow(&mtx_A, 0, 0);
  v19 = GetRow(&mtx_A, 2, 0);
  v10 = v9 * Row.x;
  v11 = v9 * Row.y;
  v12 = v9 * Row.z;
  v13 = v9 * Row.w;
  v14 = v3 * v19.x;
  v15 = v3 * v19.y;
  v16 = v3 * v19.z;
  v17 = v3 * v19.w;
  v20.x = v10 - v14;
  v20.y = v11 - v15;
  v20.z = v12 - v16;
  v20.w = v13 - v17;
  SetRow(&mtx_A, 0, v20, 0);
  v21.x = v10 + v14;
  v21.y = v11 + v15;
  v21.z = v12 + v16;
  v21.w = v13 + v17;
  SetRow(&mtx_A, 2, v21, 0);
}

// 0x2270190
void RotateMatrixZ(f32 aAngle) {
  f32 v3;
  s64 v4;
  s64 v5;
  s64 v6;
  f32 v7;
  f32 v9;
  sdfVector4_t Row;
  sdfVector4_t v11;
  sdfVector4_t v12;
  sdfVector4_t v13;

  v3 = sub_188E3D0(aAngle);
  v7 = sub_188E3C0(v4, v5, v6);
  v9 = v7;
  Row = GetRow(&mtx_A, 0, 0);
  v11 = GetRow(&mtx_A, 1, 0);
  v12.x = (f32)(v9 * Row.x) + (f32)(v3 * v11.x);
  v12.y = (f32)(v9 * Row.y) + (f32)(v3 * v11.y);
  v12.z = (f32)(v9 * Row.z) + (f32)(v3 * v11.z);
  v12.w = (f32)(v9 * Row.w) + (f32)(v3 * v11.w);
  SetRow(&mtx_A, 0, v12, 0);
  v13.z = (f32)(v9 * v11.z) - (f32)(v3 * Row.z);
  v13.w = (f32)(v9 * v11.w) - (f32)(v3 * Row.w);
  v13.x = (f32)(v9 * v11.x) - (f32)(v3 * Row.x);
  v13.y = (f32)(v9 * v11.y) - (f32)(v3 * Row.y);
  SetRow(&mtx_A, 1, v13, 0);
}

// 0x2270310
void sdfVu0SetRotateMatrixXYZ(f32 *aAngles) {
  f32 v3;
  _OWORD *p_x;
  __int128 v6;
  __int128 v7;
  __int128 v8;
  __int128 v9;
  __int128 v10;
  __int128 v12;
  _OWORD *v14;
  __int128 v15;
  __int128 v16;
  __int128 v17;
  __int128 v18;
  __int128 v19;
  __int128 v21;
  sdfMatrix4_t v22;
  sdfMatrix4_t v23;
  sdfMatrix4_t v24;

  v3 = aAngles[0];
  sub_1949540(0, v3);
  (loc_197D5D0)(0, aAngles[1]);
  p_x = &vf00.x;
  v6 = p_x[5];
  *(_OWORD *)&v23.m00 = p_x[4];
  *(_OWORD *)&v23.m01 = v6;
  v7 = p_x[7];
  *(_OWORD *)&v23.m02 = p_x[6];
  *(_OWORD *)&v23.m03 = v7;
  v8 = p_x[9];
  *(_OWORD *)&v22.m00 = p_x[8];
  *(_OWORD *)&v22.m01 = v8;
  v9 = p_x[11];
  *(_OWORD *)&v22.m02 = p_x[10];
  *(_OWORD *)&v22.m03 = v9;
  op_Multiply(&v24, &v23, &v22, 0);
  v10 = *(_OWORD *)&v24.m01;
  *(_OWORD *)&mtx_A.m00 = *(_OWORD *)&v24.m00;
  *(_OWORD *)&mtx_A.m01 = v10;
  v12 = *(_OWORD *)&v24.m03;
  *(_OWORD *)&mtx_A.m02 = *(_OWORD *)&v24.m02;
  *(_OWORD *)&mtx_A.m03 = v12;
  (loc_2279490)(0, aAngles[2]);
  v14 = &vf00.x;
  v15 = v14[5];
  *(_OWORD *)&v23.m00 = v14[4];
  *(_OWORD *)&v23.m01 = v15;
  v16 = v14[7];
  *(_OWORD *)&v23.m02 = v14[6];
  *(_OWORD *)&v23.m03 = v16;
  v17 = v14[9];
  *(_OWORD *)&v22.m00 = v14[8];
  *(_OWORD *)&v22.m01 = v17;
  v18 = v14[11];
  *(_OWORD *)&v22.m02 = v14[10];
  *(_OWORD *)&v22.m03 = v18;
  op_Multiply(&v24, &v23, &v22, 0);
  v19 = *(_OWORD *)&v24.m01;
  *(_OWORD *)&mtx_A.m00 = *(_OWORD *)&v24.m00;
  *(_OWORD *)&mtx_A.m01 = v19;
  v21 = *(_OWORD *)&v24.m03;
  *(_OWORD *)&mtx_A.m02 = *(_OWORD *)&v24.m02;
  *(_OWORD *)&mtx_A.m03 = v21;
}

// 0x22704f0
void sdfVu0MultMatrixNoArg(void) {
  _OWORD *p_x;
  __int128 v3;
  __int128 v4;
  __int128 v5;
  __int128 v6;
  __int128 v8;
  __int128 v9;
  sdfMatrix4_t v10;
  sdfMatrix4_t v11;
  sdfMatrix4_t v12;

  p_x = &vf00.x;
  v3 = p_x[9];
  *(_OWORD *)&v11.m00 = p_x[8];
  *(_OWORD *)&v11.m01 = v3;
  v4 = p_x[11];
  *(_OWORD *)&v11.m02 = p_x[10];
  *(_OWORD *)&v11.m03 = v4;
  v5 = p_x[5];
  *(_OWORD *)&v10.m00 = p_x[4];
  *(_OWORD *)&v10.m01 = v5;
  v6 = p_x[7];
  *(_OWORD *)&v10.m02 = p_x[6];
  *(_OWORD *)&v10.m03 = v6;
  op_Multiply(&v12, &v11, &v10, 0);
  v8 = *(_OWORD *)&v12.m01;
  *(_OWORD *)&mtx_A.m00 = *(_OWORD *)&v12.m00;
  *(_OWORD *)&mtx_A.m01 = v8;
  v9 = *(_OWORD *)&v12.m03;
  *(_OWORD *)&mtx_A.m02 = *(_OWORD *)&v12.m02;
  *(_OWORD *)&mtx_A.m03 = v9;
}

// 0x22705a0
void sdfVu0MultMatrixRevNoArg(void) {
  _OWORD *p_x;
  __int128 v3;
  __int128 v4;
  __int128 v5;
  __int128 v6;
  __int128 v8;
  __int128 v9;
  sdfMatrix4_t v10;
  sdfMatrix4_t v11;
  sdfMatrix4_t v12;

  p_x = &vf00.x;
  v3 = p_x[5];
  *(_OWORD *)&v11.m00 = p_x[4];
  *(_OWORD *)&v11.m01 = v3;
  v4 = p_x[7];
  *(_OWORD *)&v11.m02 = p_x[6];
  *(_OWORD *)&v11.m03 = v4;
  v5 = p_x[9];
  *(_OWORD *)&v10.m00 = p_x[8];
  *(_OWORD *)&v10.m01 = v5;
  v6 = p_x[11];
  *(_OWORD *)&v10.m02 = p_x[10];
  *(_OWORD *)&v10.m03 = v6;
  op_Multiply(&v12, &v11, &v10, 0);
  v8 = *(_OWORD *)&v12.m01;
  *(_OWORD *)&mtx_A.m00 = *(_OWORD *)&v12.m00;
  *(_OWORD *)&mtx_A.m01 = v8;
  v9 = *(_OWORD *)&v12.m03;
  *(_OWORD *)&mtx_A.m02 = *(_OWORD *)&v12.m02;
  *(_OWORD *)&mtx_A.m03 = v9;
}

// 0x2270650
void MultMatrixNoArg_C(void) {
  _OWORD *p_x;
  __int128 v3;
  __int128 v4;
  __int128 v5;
  __int128 v6;
  __int128 v8;
  __int128 v9;
  sdfMatrix4_t v10;
  sdfMatrix4_t v11;
  sdfMatrix4_t v12;

  p_x = &vf00.x;
  v3 = p_x[13];
  *(_OWORD *)&v11.m00 = p_x[12];
  *(_OWORD *)&v11.m01 = v3;
  v4 = p_x[15];
  *(_OWORD *)&v11.m02 = p_x[14];
  *(_OWORD *)&v11.m03 = v4;
  v5 = p_x[5];
  *(_OWORD *)&v10.m00 = p_x[4];
  *(_OWORD *)&v10.m01 = v5;
  v6 = p_x[7];
  *(_OWORD *)&v10.m02 = p_x[6];
  *(_OWORD *)&v10.m03 = v6;
  op_Multiply(&v12, &v11, &v10, 0);
  v8 = *(_OWORD *)&v12.m01;
  *(_OWORD *)&mtx_A.m00 = *(_OWORD *)&v12.m00;
  *(_OWORD *)&mtx_A.m01 = v8;
  v9 = *(_OWORD *)&v12.m03;
  *(_OWORD *)&mtx_A.m02 = *(_OWORD *)&v12.m02;
  *(_OWORD *)&mtx_A.m03 = v9;
}

// 0x2270700
void MultMatrixRevNoArg_C(void) {
  _OWORD *p_x;
  __int128 v3;
  __int128 v4;
  __int128 v5;
  __int128 v6;
  __int128 v8;
  __int128 v9;
  sdfMatrix4_t v10;
  sdfMatrix4_t v11;
  sdfMatrix4_t v12;

  p_x = &vf00.x;
  v3 = p_x[5];
  *(_OWORD *)&v11.m00 = p_x[4];
  *(_OWORD *)&v11.m01 = v3;
  v4 = p_x[7];
  *(_OWORD *)&v11.m02 = p_x[6];
  *(_OWORD *)&v11.m03 = v4;
  v5 = p_x[13];
  *(_OWORD *)&v10.m00 = p_x[12];
  *(_OWORD *)&v10.m01 = v5;
  v6 = p_x[15];
  *(_OWORD *)&v10.m02 = p_x[14];
  *(_OWORD *)&v10.m03 = v6;
  op_Multiply(&v12, &v11, &v10, 0);
  v8 = *(_OWORD *)&v12.m01;
  *(_OWORD *)&mtx_A.m00 = *(_OWORD *)&v12.m00;
  *(_OWORD *)&mtx_A.m01 = v8;
  v9 = *(_OWORD *)&v12.m03;
  *(_OWORD *)&mtx_A.m02 = *(_OWORD *)&v12.m02;
  *(_OWORD *)&mtx_A.m03 = v9;
}

// 0x22707b0
void MultMatrix(sdfMatrix4_t *aMatrix) {
  __int128 v4;
  __int128 v7;
  __int128 v8;
  _OWORD *p_x;
  __int128 v11;
  _OWORD *v13;
  __int128 v14;
  __int128 v15;
  __int128 v16;
  __int128 v17;
  __int128 v19;
  __int128 v20;
  sdfMatrix4_t v21;
  sdfMatrix4_t v22;
  sdfMatrix4_t v23;

  v4 = *(_OWORD *)&aMatrix->m01;
  *(_OWORD *)&v23.m00 = *(_OWORD *)&aMatrix->m00;
  *(_OWORD *)&v23.m01 = v4;
  v7 = *(_OWORD *)&aMatrix->m03;
  *(_OWORD *)&v23.m02 = *(_OWORD *)&aMatrix->m02;
  *(_OWORD *)&v23.m03 = v7;
  v8 = *(_OWORD *)&v23.m01;
  p_x = &vf00.x;
  p_x[8] = *(_OWORD *)&v23.m00;
  p_x[9] = v8;
  v11 = *(_OWORD *)&v23.m03;
  p_x[10] = *(_OWORD *)&v23.m02;
  p_x[11] = v11;
  v13 = &vf00.x;
  v14 = v13[9];
  *(_OWORD *)&v22.m00 = v13[8];
  *(_OWORD *)&v22.m01 = v14;
  v15 = v13[11];
  *(_OWORD *)&v22.m02 = v13[10];
  *(_OWORD *)&v22.m03 = v15;
  v16 = v13[5];
  *(_OWORD *)&v21.m00 = v13[4];
  *(_OWORD *)&v21.m01 = v16;
  v17 = v13[7];
  *(_OWORD *)&v21.m02 = v13[6];
  *(_OWORD *)&v21.m03 = v17;
  op_Multiply(&v23, &v22, &v21, 0);
  v19 = *(_OWORD *)&v23.m01;
  *(_OWORD *)&mtx_A.m00 = *(_OWORD *)&v23.m00;
  *(_OWORD *)&mtx_A.m01 = v19;
  v20 = *(_OWORD *)&v23.m03;
  *(_OWORD *)&mtx_A.m02 = *(_OWORD *)&v23.m02;
  *(_OWORD *)&mtx_A.m03 = v20;
}

// 0x2270950
void MultMatrixRev(sdfMatrix4_t *aMatrix) {
  __int128 v4;
  __int128 v7;
  __int128 v8;
  _OWORD *p_x;
  __int128 v11;
  _OWORD *v13;
  __int128 v14;
  __int128 v15;
  __int128 v16;
  __int128 v17;
  __int128 v19;
  __int128 v20;
  sdfMatrix4_t v21;
  sdfMatrix4_t v22;
  sdfMatrix4_t v23;

  v4 = *(_OWORD *)&aMatrix->m01;
  *(_OWORD *)&v23.m00 = *(_OWORD *)&aMatrix->m00;
  *(_OWORD *)&v23.m01 = v4;
  v7 = *(_OWORD *)&aMatrix->m03;
  *(_OWORD *)&v23.m02 = *(_OWORD *)&aMatrix->m02;
  *(_OWORD *)&v23.m03 = v7;
  v8 = *(_OWORD *)&v23.m01;
  p_x = &vf00.x;
  p_x[8] = *(_OWORD *)&v23.m00;
  p_x[9] = v8;
  v11 = *(_OWORD *)&v23.m03;
  p_x[10] = *(_OWORD *)&v23.m02;
  p_x[11] = v11;
  v13 = &vf00.x;
  v14 = v13[5];
  *(_OWORD *)&v22.m00 = v13[4];
  *(_OWORD *)&v22.m01 = v14;
  v15 = v13[7];
  *(_OWORD *)&v22.m02 = v13[6];
  *(_OWORD *)&v22.m03 = v15;
  v16 = v13[9];
  *(_OWORD *)&v21.m00 = v13[8];
  *(_OWORD *)&v21.m01 = v16;
  v17 = v13[11];
  *(_OWORD *)&v21.m02 = v13[10];
  *(_OWORD *)&v21.m03 = v17;
  op_Multiply(&v23, &v22, &v21, 0);
  v19 = *(_OWORD *)&v23.m01;
  *(_OWORD *)&mtx_A.m00 = *(_OWORD *)&v23.m00;
  *(_OWORD *)&mtx_A.m01 = v19;
  v20 = *(_OWORD *)&v23.m03;
  *(_OWORD *)&mtx_A.m02 = *(_OWORD *)&v23.m02;
  *(_OWORD *)&mtx_A.m03 = v20;
}

// 0x2270af0
void sdfVu0LookAtMatrix(const sdfVector4_t *aTarget, const sdfVector4_t *aEye, const sdfVector4_t *aDown) {
  f32 x;
  f32 w;
  f32 z;
  f32 y;
  f32 v8;
  f32 v9;
  f32 v10;
  f32 v11;
  f32 *p_x;
  f32 *v16;
  int32x2_t v21;
  int32x2_t v22;
  float32x2_t v23;
  float32x2_t v24;
  int32x2_t v29;
  int32x2_t v30;
  float32x2_t v31;
  float32x2_t v32;
  long f64 v33;
  s64 v36;
  s64 v37;
  sdfVector4_t Row;

  x = aTarget->x;
  w = aEye->w;
  z = aEye->z;
  y = aEye->y;
  v8 = aEye->x;
  v9 = aTarget->w;
  v10 = aTarget->z;
  v11 = aTarget->y;
  p_x = &vf00.x;
  p_x[4] = v8;
  p_x[5] = y;
  p_x[6] = z;
  p_x[7] = w;
  SetRow(&mtx_A, 3, vct_A, 0);
  vct_B = vct_A;
  v16 = &vf00.x;
  v16[4] = x;
  v16[5] = v11;
  v16[6] = v10;
  v16[7] = v9;
  vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  sub_1949110(0);
  SetRow(&mtx_A, 2, vct_A, 0);
  vct_B = vct_A;
  *(u64 *)&vct_A.x = v36;
  *(u64 *)&vct_A.z = v37;
  v21.n64_u64[0] = *(u64 *)&vct_B.y;
  v22.n64_u64[0] = *(u64 *)&vct_A.y;
  v23.n64_u32[0] = vdup_lane_s32(v21, 1).n64_u32[0];
  v24.n64_u32[0] = vdup_lane_s32(v22, 1).n64_u32[0];
  v23.n64_u32[1] = LODWORD(vct_B.x);
  v24.n64_u32[1] = LODWORD(vct_A.x);
  vct_A.z = (f32)(v24.n64_f32[1] * v21.n64_f32[0]) - (f32)(v23.n64_f32[1] * v22.n64_f32[0]);
  *(float32x2_t *)&vct_A.x = vsub_f32(vmul_f32(v22, v23), vmul_f32(v24, v21));
  sub_1949110(0);
  SetRow(&mtx_A, 0, vct_A, 0);
  vct_B = vct_A;
  Row = GetRow(&mtx_A, 2, 0);
  vct_A = Row;
  v29.n64_u64[0] = *(u64 *)&vct_A.y;
  v30.n64_u64[0] = *(u64 *)&vct_B.y;
  v31.n64_u32[0] = vdup_lane_s32(v30, 1).n64_u32[0];
  v32.n64_u32[0] = vdup_lane_s32(v29, 1).n64_u32[0];
  v31.n64_u32[1] = LODWORD(vct_B.x);
  v32.n64_u32[1] = LODWORD(vct_A.x);
  vct_A.z = (f32)(v32.n64_f32[1] * v30.n64_f32[0]) - (f32)(v31.n64_f32[1] * v29.n64_f32[0]);
  *(float32x2_t *)&vct_A.x = vsub_f32(vmul_f32(v29, v31), vmul_f32(v32, v30));
  SetRow(&mtx_A, 1, vct_A, 0);
  sub_1996630(0, v33);
}

// 0x2271150
void Init(void) {
  ;
}
