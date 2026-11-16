#pragma once
#include "types.h"

extern sdfMatrix4_t IdentityMatrix;
extern sdfVector4_t AllOneVector;

void sdfVu0LoadMatrix(sdfMatrix4_t *aMatrix);
void LoadMatrix_B(sdfMatrix4_t *aMatrix);
void sdfVu0StoreMatrix(sdfMatrix4_t *aMatrix);
void StoreMatrix_B(sdfMatrix4_t *aMatrix);
void CopyMatrixAtoB(void);
void CopyMatrixAtoC(void);
void CopyMatrixBtoA(void);
void CopyMatrixBtoC(void);
void CopyMatrixCtoA(void);
void CopyMatrixCtoB(void);
void LoadIdentity(void);
void LoadIdentity_B(void);
void StoreIdentity(sdfMatrix4_t *aMatrix);
void DiagMatrix(void);
void sdfVu0ReverseMatrix(void);
void InversMatrix(void);
void sdfVu0StoreRotateMatrixX(f32 aAngle, sdfMatrix4_t *aMtx);
void sdfVu0StoreRotateMatrixY(f32 aAngle, sdfMatrix4_t *aMtx);
void sdfVu0StoreRotateMatrixZ(f32 aAngle, sdfMatrix4_t *aMtx);
void SetRotateMatrixX(f32 aAngle);
void sdfVu0SetRotateMatrixY(f32 aAngle);
void SetRotateMatrixZ(f32 aAngle);
void StoreRotateMatrixAxis(f32 aAngle, const sdfVector4_t *aAxis, sdfMatrix4_t *aMtx);
void sdfVu0SetRotateMatrixAxis(f32 aAngle, const sdfVector4_t *aAxis);
void sdfVu0SetRotateMatrixX_B(f32 aAngle);
void SetRotateMatrixY_B(f32 aAngle);
void sdfVu0SetRotateMatrixZ_B(f32 aAngle);
void SetRotateMatrixAxis_B(f32 aAngle, const sdfVector4_t *aAxis);
void RotateMatrixX(f32 aAngle);
void RotateMatrixY(f32 aAngle);
void RotateMatrixZ(f32 aAngle);
void sdfVu0SetRotateMatrixXYZ(f32 *aAngles);
void sdfVu0MultMatrixNoArg(void);
void sdfVu0MultMatrixRevNoArg(void);
void MultMatrixNoArg_C(void);
void MultMatrixRevNoArg_C(void);
void MultMatrix(sdfMatrix4_t *aMatrix);
void MultMatrixRev(sdfMatrix4_t *aMatrix);
void sdfVu0LookAtMatrix(const sdfVector4_t *aTarget, const sdfVector4_t *aEye, const sdfVector4_t *aDown);
void Init(void);
