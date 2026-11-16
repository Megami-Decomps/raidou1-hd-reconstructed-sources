#pragma once
#include "types.h"

void Mult(void);
void Inverse(void);
void Normalize(void);
f32 InnerProduct(void);
void FromRotation(f32 aAngle);
void FromRotation_B(f32 aAngle);
void ToMatrix(void);
void FromEulerXYZ(f32 aRotateX, f32 aRotateY, f32 aRotateZ);
void FromEuler(f32 aRotateX, f32 aRotateY, f32 aRotateZ);
void LookAt(f32 aFrontX, f32 aFrontZ);
void Slerp(f32 aRatio);
void Lerp(f32 aRatio);
f32 EulerAngleAxisY(void);
