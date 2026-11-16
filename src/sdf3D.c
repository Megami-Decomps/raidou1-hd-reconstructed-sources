#include "types.h"
#include "sdf3d.h"
#include "sdf_vu0.h"

typedef struct sdf3DFogPacket_t sdf3DFogPacket_t;
typedef struct sdf3DLightParallelPacket_t sdf3DLightParallelPacket_t;
typedef struct sdf3DLight_t sdf3DLight_t;
typedef struct sdf3DScreenParam_t sdf3DScreenParam_t;
typedef struct sdf3DViewportPacket_t sdf3DViewportPacket_t;

sdfMatrix4_t ScreenTm;
sdfMatrix4_t CameraTm;
sdf3DLightParallelPacket_t *LightDefault;
sdf3DFogPacket_t *FogDefault;
void *cameraObj;
bool GlobalParamFlag;
f32 GlobalParamScaleX;
f32 GlobalParamScaleY;
f32 GlobalParamTransX;
f32 GlobalParamTransY;
static sdfVector3_t vbDef;

// 0x225a120
void sdf3MakeViewportPacket(sdf3DViewportPacket_t *aPacket, sdf3DScreenParam_t *aParam, sdfMatrix4_t *aCamera, void *cameraObject) {
  if (op_Equality(cameraObject, 0, 0))
    return;
  SetCamera(cameraObject, aParam, aCamera, 0);
  aPacket->cameraObject = cameraObject;
  return;
}

// 0x225a200
void sdf3SetCamera(sdf3DScreenParam_t *aParam, sdfMatrix4_t *aCamera, void *cameraObject) {
  _OWORD *p_x;
  _OWORD *p_m00;
  _OWORD *v13;
  __int128 v14;
  __int128 v15;
  __int128 v16;
  __int128 v19;
  __int128 v20;
  __int128 v21;
  __int128 v22;

  if (op_Equality(cameraObject, 0, 0))
    return;
  v19 = *(_OWORD *)&aCamera->m00;
  v20 = *(_OWORD *)&aCamera->m01;
  v21 = *(_OWORD *)&aCamera->m02;
  v22 = *(_OWORD *)&aCamera->m03;
  p_x = &vf00.x;
  p_x[4] = v19;
  p_x[5] = v20;
  p_x[6] = v21;
  p_x[7] = v22;
  p_m00 = &CameraTm.m00;
  v13 = &vf00.x;
  v14 = v13[5];
  v15 = v13[6];
  v16 = v13[7];
  *p_m00 = v13[4];
  p_m00[1] = v14;
  p_m00[2] = v15;
  p_m00[3] = v16;
  cameraObj = cameraObject;
  SetDrawMatrix(cameraObj, aCamera, 0);
  return;
}

// 0x225a410
void sdf3SetDefaultLight(sdf3DLightParallelPacket_t *aLight) {
  LightDefault = aLight;
}

// 0x225a480
void sdf3SetDefaultFog(sdf3DFogPacket_t *aFog) {
  FogDefault = aFog;
}

// 0x225a4f0
void sdf3MakeScreenParam(sdf3DScreenParam_t *aParam) {
  f32 width;
  f32 height;
  f32 v5;
  f32 v6;
  f32 farClip;
  f32 nearClip;
  f32 v9;
  f32 v10;
  f32 v11;
  f32 v12;
  __int128 v14;
  __int128 v15;
  __int128 v16;
  f32 zMax;
  f32 zMin;
  s64 v20;
  f32 v22;
  f32 x;
  f32 v25;
  f32 y;
  f32 v27;

  width = aParam->width;
  height = aParam->height;
  v5 = sub_188E480(aParam->fovy * 0.5);
  v6 = v5 + v5;
  nearClip = aParam->nearClip;
  farClip = aParam->farClip;
  v9 = height * 0.5;
  v10 = height / v6;
  v11 = width * 0.5;
  v12 = farClip - nearClip;
  v14 = *(_OWORD *)&identityMatrix.m02;
  v15 = *(_OWORD *)&identityMatrix.m03;
  v16 = *(_OWORD *)&identityMatrix.m01;
  *(_OWORD *)&aParam->TM.m00 = *(_OWORD *)&identityMatrix.m00;
  *(_OWORD *)&aParam->TM.m01 = v16;
  *(_OWORD *)&aParam->TM.m02 = v14;
  *(_OWORD *)&aParam->TM.m03 = v15;
  set_Item_60922352(&aParam->TM, 0, v10 / (f32)(v11 * aParam->aspect), 0);
  set_Item_60922352(&aParam->TM, 5, v10 / v9, 0);
  set_Item_60922352(&aParam->TM, 10, (f32)-(f32)(farClip + nearClip) / v12, 0);
  set_Item_60922352(&aParam->TM, 14, 1.0, 0);
  set_Item_60922352(&aParam->TM, 11, (f32)((f32)(farClip * nearClip) + (f32)(farClip * nearClip)) / v12, 0);
  set_Item_60922352(&aParam->TM, 15, 0.0, 0);
  zMin = aParam->zMin;
  zMax = aParam->zMax;
  v20 = *(u64 *)&aParam->ox;
  aParam->scale.w = 1.0;
  aParam->sensorSize.y = 2.0;
  aParam->scale.x = v11;
  aParam->scale.y = v9 * 0.5;
  *(u64 *)&aParam->trans.x = v20;
  *(u64 *)&aParam->trans.w = 0x4000000000000000LL;
  v22 = (f32)(zMax - zMin) * 0.5;
  aParam->scale.z = v22;
  aParam->trans.z = zMin + v22;
  if (GlobalParamFlag)
  {
    x = aParam->scale.x;
    aParam->scale.x = x * GlobalParamScaleX;
    v25 = aParam->trans.x;
    y = aParam->trans.y;
    aParam->scale.y = aParam->scale.y * GlobalParamScaleY;
    aParam->trans.x = v25 + GlobalParamTransX;
    aParam->trans.y = y + GlobalParamTransY;
    v27 = aParam->sensorSize.y;
    aParam->sensorSize.x = aParam->sensorSize.x / GlobalParamScaleX;
    aParam->sensorSize.y = v27 / GlobalParamScaleY;
  }
  aParam->dispAspect = (f32)(aParam->width / aParam->height) * aParam->aspect;
}

// 0x225a780
void sdf3MakeLightParallelPacket(sdf3DLightParallelPacket_t *aPacket, sdf3DLight_t *aLights, const sdfVector4_t *aAmbient, bool sceneColor) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  sdfVector4_t *color;
  s64 v12;
  char v13;
  s64 v14;
  __int128 v16;
  __int128 v17;
  f32 *v18;
  sdf3DLight_t *v19;
  f32 v20;
  f32 v21;
  f32 v22;
  f32 v24;
  f32 v25;
  f32 v26;
  f32 v27;
  sdfVector3_t *normal;
  u32 *v29;
  struct sdfVector3_t *v30;
  f32 v31;
  s64 v32;
  sdfVector4_t *v33;
  sdfVector4_t *v35;
  f32 v40;
  f32 *v44;
  f32 v45;
  f32 v46;
  f32 v47;
  f32 v48;
  f32 v49;
  f32 v50;
  f32 v51;
  f32 v52;
  f32 v53;
  f32 v54;
  f32 v55;
  f32 v56;
  f32 v57;
  f32 v58;
  f32 v59;
  f32 v60;
  f32 v62;
  f32 v63;
  f32 v64;
  f32 v65;
  f32 v66;
  f32 v67;
  f32 v68;
  f32 v69;
  f32 v70;
  f32 v75;
  f32 v76;
  f32 v77;
  f32 v78;
  __int128 v82;
  __int128 v83;
  __int128 v84;
  sdfMatrix4_t v86;
  sdfMatrix4_t v87;
  sdfVector4_t Row;
  sdfVector4_t Column;
  sdfVector4_t v90;
  sdfVector4_t v91;
  sdfVector4_t v92;
  sdfVector4_t v93;

  w = aAmbient->w;
  z = aAmbient->z;
  y = aAmbient->y;
  x = aAmbient->x;
  color = aPacket->color;
  v12 = 0;
  v13 = 0;
  v14 = 40;
  v16 = *(_OWORD *)&identityMatrix.m01;
  *(_OWORD *)&v87.m00 = *(_OWORD *)&identityMatrix.m00;
  *(_OWORD *)&v87.m01 = v16;
  v17 = *(_OWORD *)&identityMatrix.m03;
  *(_OWORD *)&v87.m02 = *(_OWORD *)&identityMatrix.m02;
  *(_OWORD *)&v87.m03 = v17;
  color[3].x = x;
  color[3].y = y;
  color[3].z = z;
  color[3].w = w;
  do
  {
    while (1)
    {
      v19 = aLights[v12];
      if (!v19)
        break;
      v20 = v19->v.x;
      v21 = v19->v.y;
      v22 = v19->v.z;
      v24 = sqrtf((f32)(v22 * v22) + (f32)((f32)(v20 * v20) + (f32)(v21 * v21)));
      if (v24 <= 0.00001)
      {
        v25 = zeroVector.x;
        v26 = zeroVector.y;
        v27 = zeroVector.z;
        if ((v13 & 1) != 0)
          goto LABEL_6;
LABEL_22:
        v90.w = 0.0;
        v90.x = v25;
        v90.y = v26;
        v90.z = v27;
        SetRow(&v87, 2, v90, 0);
        goto LABEL_6;
      }
      v25 = v20 / v24;
      v26 = v21 / v24;
      v27 = v22 / v24;
      if ((v13 & 1) == 0)
        goto LABEL_22;
LABEL_6:
      v13 = 1;
      v18 = ((char *)aPacket->normal + v14);
      *(v18 - 2) = v25;
      *(v18 - 1) = v26;
      *v18 = v27;
      aPacket->color[v12] = v19->color;
      y = y + v19->color.y;
      w = w + v19->color.w;
      x = x + v19->color.x;
      z = z + v19->color.z;
      v14 += 12;
      ++v12;
      if (v14 == 76)
        goto LABEL_25;
    }
    normal = aPacket->normal;
    v29 = ((char *)normal + v14);
    v31 = zeroVector.z;
    v32 = *(u64 *)&zeroVector.x;
    LODWORD(v30) = (u8)byte_5755D31;
    *((u64 *)v29 - 1) = v32;
    *(f32 *)v29 = v31;
    v33 = aPacket->color;
    v33[v12] = zeroVector;
    v14 += 12;
    ++v12;
  }
  while (v14 != 76);
LABEL_25:
  v35 = aPacket->color;
  __asm { FMOV            V0.4S, #1.0 }
  v35[4].x = x;
  v35[4].y = y;
  v35[4].z = z;
  v35[4].w = w;
  aPacket->rim = _Q0;
  if ((v13 & 1) != 0)
  {
    Row = GetRow(&v87, 2, 0);
    v40 = fabsf(Row.z);
    if (fabsf(Row.x) < Epsilon && v40 < Epsilon)
    {
      v45 = -Row.y;
      v47 = 0.0;
      v46 = 0.0;
    }
    else
    {
      v45 = v44[51];
      v46 = v44[52];
      v47 = v44[53];
    }
    v48 = Row.y * v47;
    v49 = Row.x * v47;
    v50 = Row.x * v46;
    v51 = Row.y * v45;
    v52 = Row.z * v46;
    v53 = Row.z * v45;
    v54 = v48 - v52;
    v55 = v53 - v49;
    v56 = v50 - v51;
    v57 = sqrtf((f32)(v56 * v56) + (f32)((f32)(v54 * v54) + (f32)(v55 * v55)));
    if (v57 <= 0.00001)
    {
      v58 = zeroVector.x;
      v59 = zeroVector.y;
      v60 = zeroVector.z;
    }
    else
    {
      v58 = v54 / v57;
      v59 = v55 / v57;
      v60 = v56 / v57;
    }
    v91.w = 0.0;
    v91.x = v58;
    v91.y = v59;
    v91.z = v60;
    SetRow(&v87, 0, v91, 0);
    v62 = Row.y * v60;
    v63 = Row.x * v60;
    v64 = Row.x * v59;
    v65 = Row.y * v58;
    v66 = Row.z * v58;
    v67 = v62 - (f32)(Row.z * v59);
    v68 = v66 - v63;
    v69 = v64 - v65;
    v70 = sqrtf((f32)(v69 * v69) + (f32)((f32)(v67 * v67) + (f32)(v68 * v68)));
    if (v70 <= 0.00001)
    {
      v92.x = zeroVector.x;
      v92.y = zeroVector.y;
      v92.z = zeroVector.z;
    }
    else
    {
      v92.x = v67 / v70;
      v92.y = v68 / v70;
      v92.z = v69 / v70;
    }
    v92.w = 0.0;
    SetRow(&v87, 1, v92, 0);
    get_transpose(&v86, &v87, 0);
    v87 = v86;
    Column = GetColumn(&CameraTm, 2, 0);
    v75 = Row.x + Column.x;
    v76 = Row.y + Column.y;
    v77 = Row.z + Column.z;
    v78 = sqrtf((f32)(v77 * v77) + (f32)((f32)(v75 * v75) + (f32)(v76 * v76)));
    if (v78 <= 0.00001)
    {
      v93.x = zeroVector.x;
      v93.y = zeroVector.y;
      v93.z = zeroVector.z;
    }
    else
    {
      v93.x = (f32)-v75 / v78;
      v93.y = (f32)-v76 / v78;
      v93.z = (f32)-v77 / v78;
    }
    v93.w = 0.0;
    SetRow(&v87, 3, v93, 0);
  }
  v82 = *(_OWORD *)&v87.m01;
  *(_OWORD *)&aPacket->TM.m00 = *(_OWORD *)&v87.m00;
  *(_OWORD *)&aPacket->TM.m01 = v82;
  v83 = *(_OWORD *)&v87.m02;
  v84 = *(_OWORD *)&v87.m03;
  aPacket->sceneColor = sceneColor;
  *(_OWORD *)&aPacket->TM.m02 = v83;
  *(_OWORD *)&aPacket->TM.m03 = v84;
}

// 0x225ae40
void sdf3MakeSpecular(void) {
  void *static_fields;
  void *specular_tex_local;
  sdfColor_t *v6;
  void *v7;
  s64 v8;
  f32 *v9;
  f32 v10;
  s32 v11;
  s32 v12;
  s32 v13;
  s32 v14;
  f32 v15;
  f32 v16;
  u64 v17;

  specular_tex_local = static_fields;
  if (!op_Equality(specular_tex_local, 0, 0))
  {
    goto LABEL_6;
  }
  v6 = NewSpecific(sdfColor_t, 0x100u);
  v7 = Allocate(UnityEngine_Texture2D);
  _ctor_60858704(v7, 128, 64, 1, 0, 0, 0);
  set_wrapMode(v7, 1, 0);
  set_filterMode(v7, 1, 0);
  if (*(s32 *)((char *)v6 + 24) >= 1)
  {
    v8 = 0;
    v9 = &v6[0].a;
    do
    {
      v10 = (s32)v8;
      *(u64 *)(v9 - 3) = 0;
      *(v9 - 1) = 0.0;
      ++v8;
      *v9 = v10 / 255.0;
      v9 += 4;
    }
    while (v8 < *(s32 *)((char *)v6 + 24));
  }
  SetPixel(v7, 0, 63, v6[0], 0);
  if ((v7->klass->vtable._5_get_width.methodPtr)(v7, v7->klass->vtable._5_get_width.method) > 1)
  {
    v11 = 1;
    do
      SetPixel(v7, v11++, 63, v6[255], 0);
    while (v11 < (v7->klass->vtable._5_get_width.methodPtr)(v7, v7->klass->vtable._5_get_width.method));
  }
  if ((v7->klass->vtable._5_get_width.methodPtr)(v7, v7->klass->vtable._5_get_width.method) >= 1)
  {
    v12 = 0;
    do
    {
      if ((v7->klass->vtable._7_get_height.methodPtr)(v7, v7->klass->vtable._7_get_height.method) >= 2)
      {
        v13 = 1;
        v14 = 62;
        v15 = (f32)v12 * 0.007874016;
        do
        {
          v16 = (f32)(v15 * 255.0) + 0.5;
          v17 = (s32)v16;
          if (v16 == INFINITY)
            v17 = 0xFFFFFFFF80000000LL;
          SetPixel(v7, v12, v14, v6[v17], 0);
          v15 = (f32)((f32)v12 * 0.007874016) * v15;
          ++v13;
          --v14;
        }
        while (v13 < (v7->klass->vtable._7_get_height.methodPtr)(v7, v7->klass->vtable._7_get_height.method));
      }
      ++v12;
    }
    while (v12 < (v7->klass->vtable._5_get_width.methodPtr)(v7, v7->klass->vtable._5_get_width.method));
  }
  Apply_60860784(v7, 0);
  specular_tex = v7;
LABEL_6:
  SetGlobalTexture("_SDF_SPECULAR_MAP", **((void ***)sdf3D + 23), 0);
}

// 0x225b200
void sdf3MakeSpecular2(u8 *data) {
  void *v8;
  s32 v9;
  s32 v10;
  u32 v11;
  s32 v12;
  sdfColor_t v15;

  if (!op_Equality(specular_tex2, 0, 0))
  {
    goto LABEL_6;
  }
  v8 = Allocate(UnityEngine_Texture2D);
  _ctor_60858704(v8, 64, 64, 1, 0, 0, 0);
  set_wrapMode(v8, 0, 0);
  set_filterMode(v8, 1, 0);
  if ((v8->klass->vtable._7_get_height.methodPtr)(v8, v8->klass->vtable._7_get_height.method) >= 1)
  {
    v9 = 0;
    v10 = 0;
    do
    {
      if ((v8->klass->vtable._5_get_width.methodPtr)(v8, v8->klass->vtable._5_get_width.method) >= 1)
      {
        v12 = 0;
        do
        {
          v15.b = 0.0;
          LOBYTE(v11) = data[v9 + v12];
          v15.a = (f32)v11 / 255.0;
          v15.r = 0.0;
          v15.g = 0.0;
          SetPixel(v8, v12++, 63 - v10, v15, 0);
        }
        while (v12 < (v8->klass->vtable._5_get_width.methodPtr)(v8, v8->klass->vtable._5_get_width.method));
        v9 += v12;
      }
      ++v10;
    }
    while (v10 < (v8->klass->vtable._7_get_height.methodPtr)(v8, v8->klass->vtable._7_get_height.method));
  }
  Apply_60860784(v8, 0);
  specular_tex2 = v8;
LABEL_6:
  SetGlobalTexture("_SDF_SPECULAR_MAP2", specular_tex2, 0);
}

// 0x225b4a0
void sdf3MakeSpecular3(void) {
  u64 *v6;
  u32 *v7;
  void *v8;
  void *v9;
  void *v10;
  void *v11;
  s32 v12;
  s32 v13;
  u64 *v14;
  f32 v15;
  f32 *v16;
  f32 *v17;
  f32 v18;
  f32 v19;
  f32 v20;
  f32 v21;
  f32 v22;
  f32 v23;
  f32 v24;
  s32 v25;
  f32 v26;
  f32 v27;
  f32 v28;
  f32 v29;
  s32 v30;
  f32 v31;
  f32 v32;
  f32 v35;
  sdfColor_t v36;

  if (!op_Equality(specular_tex3, 0, 0))
  {
    goto LABEL_6;
  }
  v6 = NewSpecific(float__, 4u);
  v7 = NewSpecific(f32, 4u);
  v6[4] = v7;
  v7[10] = 1065353216;
  v8 = NewSpecific(f32, 4u);
  InitializeArray_55364416(v8, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__6313E9CC4DD9CBA003B3A97A4717977E8AE7B4A9D86073F2E7A24C2262F666CA, 0);
  v6[5] = v8;
  v9 = NewSpecific(f32, 4u);
  InitializeArray_55364416(v9, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__731185390A20A5CD399D53041B8816FA8786D877531660881A9EE11E5443BF42, 0);
  v6[6] = v9;
  v10 = NewSpecific(f32, 4u);
  InitializeArray_55364416(v10, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__5762C777C2B0C34DD03E450A01C2D8097B02355FA6FAA1E24C10FE3EB73806A6, 0);
  v6[7] = v10;
  v11 = Allocate(UnityEngine_Texture2D);
  _ctor_60858704(v11, 512, 128, 1, 0, 0, 0);
  set_wrapMode(v11, 1, 0);
  set_filterMode(v11, 1, 0);
  if ((v11->klass->vtable._7_get_height.methodPtr)(v11, v11->klass->vtable._7_get_height.method) >= 1)
  {
    v12 = 0;
    v13 = 0;
    v14 = v6 + 4;
    do
    {
      v15 = (f32)v13
          / (f32)(s32)((v11->klass->vtable._7_get_height.methodPtr)(v11, v11->klass->vtable._7_get_height.method) - 1);
      if (*(f32 *)(v14[v12 + 1] + 32) < v15)
        ++v12;
      v16 = v14[v12];
      v17 = v14[v12 + 1];
      v18 = v16[10];
      v19 = v16[11];
      v21 = v16[8];
      v20 = v16[9];
      v23 = v17[8];
      v22 = v17[9];
      v24 = v17[10];
      v35 = v17[11];
      if ((v11->klass->vtable._5_get_width.methodPtr)(v11, v11->klass->vtable._5_get_width.method) >= 1)
      {
        v25 = 0;
        v26 = (f32)(v15 - v21) / (f32)(v23 - v21);
        v27 = v20 + (f32)((f32)(v22 - v20) * v26);
        v28 = v18 + (f32)((f32)(v26 * (f32)(v24 - v18)) - v27);
        v29 = v19 + (f32)(v26 * (f32)(v35 - v19));
        do
        {
          v30 = (v11->klass->vtable._5_get_width.methodPtr)(v11, v11->klass->vtable._5_get_width.method);
          v36.a = 0.0;
          v31 = (f32)((f32)v25 / (f32)(v30 - 1)) - v27;
          if (v31 >= 0.0)
          {
            v32 = 1.0;
            if (v31 < v28)
              v32 = v31 / v28;
            v36.a = v29 * (f32)(v32 * (f32)(v32 * (f32)(v32 * v32)));
          }
          v36.r = 0.0;
          v36.g = 0.0;
          v36.b = 0.0;
          SetPixel(v11, v25++, v13, v36, 0);
        }
        while (v25 < (v11->klass->vtable._5_get_width.methodPtr)(v11, v11->klass->vtable._5_get_width.method));
      }
      ++v13;
    }
    while (v13 < (v11->klass->vtable._7_get_height.methodPtr)(v11, v11->klass->vtable._7_get_height.method));
  }
  Apply_60860784(v11, 0);
  specular_tex3 = v11;
LABEL_6:
  SetGlobalTexture("_SDF_SPECULAR_MAP3", specular_tex3, 0);
}

// 0x225b930
void sdf3MakeRefmap(u8 *data) {
  sdfColor_t *v8;
  void *v9;
  float32x4_t v10;
  f32 *v11;
  u8 *m_Items;
  float32x4_t v13;
  s64 v14;
  int32x4_t v15;
  float32x4_t v16;
  float32x4_t v17;
  s64 v18;
  int32x4_t v19;
  const char *v20;
  f32 *v21;
  f32 *v22;
  f32 *v23;
  float32x4_t v24;
  s32 v25;
  s32 v26;
  s32 v27;
  float32x4x4_t v30;
  float32x4x4_t v31;
  int8x16x4_t v32;
  float32x4x4_t v33;
  float32x4x4_t v34;

  if (!op_Equality(refmap_tex, 0, 0))
  {
    goto LABEL_6;
  }
  v8 = NewSpecific(sdfColor_t, 0x100u);
  v9 = Allocate(UnityEngine_Texture2D);
  _ctor_60858704(v9, 128, 128, 4, 0, 0, 0);
  set_wrapMode(v9, 1, 0);
  set_filterMode(v9, 1, 0);
  v11 = &v8[0];
  m_Items = data;
  if ((s64)&v8[0] >= (u64)&data[1024] || (u64)m_Items >= (s64)&v8[256])
  {
    v18 = 0;
    v19 = vdupq_n_s32(0x437F0000u);
    do
    {
      v20 = &m_Items[v18];
      v18 += 64;
      v32 = vld4q_s8(v20);
      v21 = v11;
      v22 = v11 + 32;
      v23 = v11 + 48;
      v11 += 64;
      v30.val[0] = vdivq_f32(vcvtq_f32_u32(vqtbl1q_s8(v32.val[0], (int8x16_t)xmmword_3CF91C0)), v19);
      v30.val[1] = vdivq_f32(vcvtq_f32_u32(vqtbl1q_s8(v32.val[1], (int8x16_t)xmmword_3CF91C0)), v19);
      v30.val[2] = vdivq_f32(vcvtq_f32_u32(vqtbl1q_s8(v32.val[2], (int8x16_t)xmmword_3CF91C0)), v19);
      v31.val[0] = vdivq_f32(vcvtq_f32_u32(vqtbl1q_s8(v32.val[0], (int8x16_t)xmmword_3D02F00)), v19);
      v24.n128_u64[0] = 0x3C0000003C000000LL;
      v24.n128_u64[1] = 0x3C0000003C000000LL;
      v30.val[3] = vmulq_f32(vcvtq_f32_u32(vqtbl1q_s8(v32.val[3], (int8x16_t)xmmword_3CF91C0)), v24);
      v31.val[1] = vdivq_f32(vcvtq_f32_u32(vqtbl1q_s8(v32.val[1], (int8x16_t)xmmword_3D02F00)), v19);
      v31.val[2] = vdivq_f32(vcvtq_f32_u32(vqtbl1q_s8(v32.val[2], (int8x16_t)xmmword_3D02F00)), v19);
      v33.val[0] = vdivq_f32(vcvtq_f32_u32(vqtbl1q_s8(v32.val[0], (int8x16_t)xmmword_3D066B0)), v19);
      v31.val[3] = vmulq_f32(vcvtq_f32_u32(vqtbl1q_s8(v32.val[3], (int8x16_t)xmmword_3D02F00)), v24);
      v34.val[0] = vdivq_f32(vcvtq_f32_u32(vqtbl1q_s8(v32.val[0], (int8x16_t)xmmword_3CFF7B0)), v19);
      v34.val[1] = vdivq_f32(vcvtq_f32_u32(vqtbl1q_s8(v32.val[1], (int8x16_t)xmmword_3CFF7B0)), v19);
      v34.val[2] = vdivq_f32(vcvtq_f32_u32(vqtbl1q_s8(v32.val[2], (int8x16_t)xmmword_3CFF7B0)), v19);
      v34.val[3] = vmulq_f32(vcvtq_f32_u32(vqtbl1q_s8(v32.val[3], (int8x16_t)xmmword_3CFF7B0)), v24);
      vst4q_f32(v21, v34);
      v33.val[1] = vdivq_f32(vcvtq_f32_u32(vqtbl1q_s8(v32.val[1], (int8x16_t)xmmword_3D066B0)), v19);
      vst4q_f32(v22, v31);
      vst4q_f32(v23, v30);
      v33.val[2] = vdivq_f32(vcvtq_f32_u32(vqtbl1q_s8(v32.val[2], (int8x16_t)xmmword_3D066B0)), v19);
      v33.val[3] = vmulq_f32(vcvtq_f32_u32(vqtbl1q_s8(v32.val[3], (int8x16_t)xmmword_3D066B0)), v24);
      vst4q_f32(v21 + 16, v33);
    }
    while (v18 != 1024);
  }
  else
  {
    v13.n128_u64[0] = 0x3C0000003C000000LL;
    v13.n128_u64[1] = 0x3C0000003C000000LL;
    v14 = 0;
    v15 = vdupq_n_s32(0x437F0000u);
    do
    {
      v10.n128_u32[0] = *(u32 *)&data[4 * v14];
      v16 = vcvtq_f32_u32(vmovl_u16((uint16x4_t)vmovl_u8((uint8x8_t)v10.n128_u64[0]).n128_u64[0]));
      v17 = vdivq_f32(v16, v15);
      v10 = vmulq_f32(v16, v13);
      v17.n128_u32[3] = v10.n128_u32[3];
      *(float32x4_t *)((s64)&v8[0] + 16 * v14++) = v17;
    }
    while (v14 != 256);
  }
  if ((v9->klass->vtable._7_get_height.methodPtr)(v9, v9->klass->vtable._7_get_height.method) >= 1)
  {
    v25 = 0;
    v26 = 1024;
    do
    {
      if ((v9->klass->vtable._5_get_width.methodPtr)(v9, v9->klass->vtable._5_get_width.method) >= 1)
      {
        v27 = 0;
        do
        {
          SetPixel(v9, v27, 127 - v25, *(sdfColor_t *)((s64)(char *)v8 + 16 * data[v26 + v27] + 32), 0);
          ++v27;
        }
        while (v27 < (v9->klass->vtable._5_get_width.methodPtr)(v9, v9->klass->vtable._5_get_width.method));
        v26 += v27;
      }
      ++v25;
    }
    while (v25 < (v9->klass->vtable._7_get_height.methodPtr)(v9, v9->klass->vtable._7_get_height.method));
  }
  Apply_60860784(v9, 0);
  refmap_tex = v9;
LABEL_6:
  SetGlobalTexture("_SDF_REFMAP", refmap_tex, 0);
}

// 0x225bdc0
void sdf3Init(void) {
  sdf3MakeSpecular();
  sdf3MakeSpecular3();
}

// 0x225be30
void Init(void *list) {
  Il2CppObject *Asset_object;
  Il2CppObject *v5;
  u8 *monitor;
  Il2CppObject *v7;
  Il2CppObject *v9;

  Asset_object = GetAsset_object_(list, "sdfSpecularTex.dat");
    v5 = Asset_object;
  else
    v5 = 0;
  monitor = v5[1].monitor;
  sdf3MakeSpecular2(monitor);
  v7 = GetAsset_object_(list, "sdfRefmapTex.dat");
    v9 = v7;
  else
    v9 = 0;
  sdf3MakeRefmap(v9[1].monitor);
}
