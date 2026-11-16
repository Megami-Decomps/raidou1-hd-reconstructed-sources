#include "types.h"
#include "dds3billboard.h"
#include "dds3effect.h"
#include "dds3kernelcore.h"
#include "dds3kerneldraw.h"
#include "dds3particle.h"
#include "effcachetex.h"
#include "effect.h"
#include "eve.h"
#include "kernel.h"
#include "sdfdraw.h"
#include "sdfrand.h"
#include "tneffect.h"

#define DDS3EFFECT_VERSION_BETA 1
#define DDS3EFFECT_BETA_PARSIZE 172
#define DDS3EFFECT_BETA_POLYSIZE 32
#define DDS3EFFECT_VERSION_OLD 1.01
#define DDS3EFFECT_VERSION_OLD_M 1.02
#define DDS3EFFECT_VERSION 1.03
#define MAT_STANDARD "standard"
#define MAT_EFFECT "effect"
#define MAT_NORMAL "effect"
#define MAT_MULTI "multibill"

typedef struct dds3EffectMajorTable_t dds3EffectMajorTable_t;
typedef struct dds3ProcessID_t dds3ProcessID_t;
typedef struct effHandle_t effHandle_t;
typedef struct sdfDrawTag_t sdfDrawTag_t;
typedef struct sdfPrimTransPacket_t sdfPrimTransPacket_t;
typedef struct sdfRandCB_t sdfRandCB_t;

typedef void *(*MinorCreateFunc)(u16 type, void *pData);
typedef void (*MinorDrawFunc)(void *pData);
typedef void (*MinorDeleteFunc)(void *pData);
typedef void (*MinorResetFunc)(void *pData);
typedef u16 (*MinorGetStateFunc)(void *pData);
typedef void (*MinorSetPosFunc)(void *pData, const sdfVector4_t *pos);
typedef void (*MinorSetRotateMatrixFunc)(void *pData, const sdfMatrix4_t *mat);
typedef void (*MinorSetRGBAFunc)(void *pData, const sdfVector4_t *col);
typedef void (*MinorSetLoopFunc)(void *pData, u8 loop);
typedef u8 (*MinorGetLoopFunc)(void *pData);
typedef void *(*MinorCopyFunc)(void *pData);
typedef void (*MinorSetScaleFunc)(void *pData, f32 scale);

struct dds3EffectMajorTable_t {
    MinorCreateFunc Create;
    MinorDrawFunc Draw;
    MinorDeleteFunc Delete;
    MinorResetFunc Reset;
    MinorGetStateFunc GetState;
    MinorSetPosFunc SetPos;
    MinorSetRotateMatrixFunc SetRotateMatrix;
    MinorSetRGBAFunc SetRGBA;
    MinorSetLoopFunc SetLoop;
    MinorGetLoopFunc GetLoop;
    MinorCopyFunc Copy;
    MinorSetScaleFunc SetScale;
};

sdfRandCB_t *Rand;
static sdfDrawTag_t *pDrawTagSemi;
static sdfDrawTag_t *pDrawTagSub;
static sdfPrimTransPacket_t *pTransPktSemi;
static sdfPrimTransPacket_t *pTransPktSub;
static sdfDrawTag_t *pDrawTagHSemi;
static sdfDrawTag_t *pDrawTagHSub;
static dds3EffectMajorTable_t *defaultTable;
static dds3EffectMajorTable_t *EffMajorTable;

static void ManagerExit(dds3ProcessID_t *ProcessID);
static dds3ProcessFunc_t ManagerRunF(dds3ProcessID_t *ProcessID);
static dds3ProcessFunc_t ManagerRun(dds3ProcessID_t *ProcessID);
static void *DefaultCreate(u16 type, void *pData);
static void DefaultDelete(void *handle);
static void DefaultDraw(void *handle);
static void DefaultReset(void *hPart);
static void DefaultSetScale(void *handle, f32 scale);
static DDS3EFFECT_STATE DefaultGetState(void *hPart);
static void DefaultSetPosition(void *handle, const sdfVector4_t *pPos);
static void DefaultSetRotateMatrix(void *handle, const sdfMatrix4_t *pMatrix);
static void DefaultSetRGBA(void *handle, const sdfVector4_t *abgr);
static void DefaultSetLoop(void *hPart, u8 loop);
static u8 DefaultGetLoop(void *hPart);
static void *DefaultCopy(void *handle);

// 0x195b900
void dds3EffectManagerInit(void) {
  dds3ProcessFunc_t v6;
  dds3ProcessFunc_t v7;
  shutdownfuncDelegate v8;

  sdfInitByTime(Rand);
  tnInit();
  dds3BillboardManagerInit();
  sdfInitByTime(ParRand);
  v6 = Allocate(dds3ProcessFunc_t);
  _ctor(v6, 0, Method_Project_dds3Effect_ManagerRunF__, 0);
  dds3StartProcess("effect_f", 11010, 0, 0, v6, 0, 0);
  v7 = Allocate(dds3ProcessFunc_t);
  _ctor(v7, 0, Method_Project_dds3Effect_ManagerRun__, 0);
  v8 = Allocate(shutdownfuncDelegate);
  _ctor(v8, 0, Method_Project_dds3Effect_ManagerExit__, 0);
  dds3StartProcess("effect", 11030, 0, 0, v7, v8, 0);
  EffectInit();
}

// 0x195bcd0
static void ManagerExit(dds3ProcessID_t *ProcessID) {
  hDrawListTop = 0;
  hGeneralBillboard = 0;
}

// 0x195bdf0
static dds3ProcessFunc_t ManagerRunF(dds3ProcessID_t *ProcessID) {
  sdfDrawTagInit(pDrawTagSemi);
  sdfDrawTagLink(pDrawTagSemi, pTransPktSemi);
  sdfDrawTagLinkOt(Ot[60], pDrawTagSemi);
  sdfDrawTagInit(pDrawTagSub);
  sdfDrawTagLink(pDrawTagSub, pTransPktSub);
  sdfDrawTagLinkOt(Ot[61], pDrawTagSub);
  sdfDrawTagInit(pDrawTagHSemi);
  sdfDrawTagLink(pDrawTagHSemi, pTransPktSemi);
  sdfDrawTagLinkOt(Ot[96], pDrawTagHSemi);
  sdfDrawTagInit(pDrawTagHSub);
  sdfDrawTagLink(pDrawTagHSub, pTransPktSub);
  sdfDrawTagLinkOt(Ot[97], pDrawTagHSub);
  effEnvInit();
  return 0;
}

// 0x195bfb0
static dds3ProcessFunc_t ManagerRun(dds3ProcessID_t *ProcessID) {
  dds3BillboardLinkOt();
  EffectDraw();
  return 0;
}

// 0x195c070
effHandle_t *dds3EffectCreate(DDS3EFFECT major, u16 minor, void *pData) {
  u32 v5;
  effHandle_t *v7;
  MinorCreateFunc Create;
  void *v10;

  v5 = minor;
  v7 = Allocate(effHandle_t);
  v7->major = major;
  v7->minor = (u16)v5;
  *(u32 *)&v7->version = 1065604874;
  Create = EffMajorTable[major]->Create;
  v10 = (Create->invoke_impl)(Create->method_code, v5, pData, Create->method);
  v7->pwork = v10;
  return v7;
}

// 0x195c170
static void *DefaultCreate(u16 type, void *pData) {
  Il2CppObject *v3;

  v3 = Allocate(Project_dds3EffectHandle_t);
  _ctor(v3, 0);
  return (void *)v3;
}

// 0x195c1d0
void Delete(effHandle_t *hEffect) {
  MinorDeleteFunc Delete;

  Delete = EffMajorTable[hEffect->major]->Delete;
  (Delete->invoke_impl)(Delete->method_code, hEffect->pwork, Delete->method);
}

// 0x195c260
static void DefaultDelete(void *handle) {
  ;
}

// 0x195c270
void dds3EffectDraw(effHandle_t *hEffect) {
  MinorDrawFunc Draw;

  Draw = EffMajorTable[hEffect->major]->Draw;
  (Draw->invoke_impl)(Draw->method_code, hEffect->pwork, Draw->method);
}

// 0x195c300
static void DefaultDraw(void *handle) {
  ;
}

// 0x195c3a0
static void DefaultReset(void *hPart) {
  ;
}

// 0x195c3b0
void dds3EffectSetScale(effHandle_t *hEffect, f32 scale) {
  MinorSetScaleFunc SetScale;

  SetScale = EffMajorTable[hEffect->major]->SetScale;
  (SetScale->invoke_impl)(SetScale->method_code, hEffect->pwork, SetScale->scale);
}

// 0x195c450
static void DefaultSetScale(void *handle, f32 scale) {
  ;
}

// 0x195c460
DDS3EFFECT_STATE dds3EffectGetState(effHandle_t *hEffect) {
  MinorGetStateFunc GetState;

  GetState = EffMajorTable[hEffect->major]->GetState;
  return (GetState->invoke_impl)(GetState->method_code, hEffect->pwork, GetState->method);
}

// 0x195c4f0
static DDS3EFFECT_STATE DefaultGetState(void *hPart) {
  return 1;
}

// 0x195c500
void dds3EffectSetPosition(effHandle_t *hEffect, const sdfVector4_t *pPos) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  MinorSetPosFunc SetPos;

  w = pPos->w;
  z = pPos->z;
  y = pPos->y;
  x = pPos->x;
  SetPos = EffMajorTable[hEffect->major]->SetPos;
  (SetPos->invoke_impl)(SetPos->method_code, hEffect->pwork, SetPos->x, y, z, w);
}

// 0x195c5c0
static void DefaultSetPosition(void *handle, const sdfVector4_t *pPos) {
  ;
}

// 0x195c5d0
void dds3EffectSetRotateMatrix(effHandle_t *hEffect, const sdfMatrix4_t *pMatrix) {
  void *pwork;
  __int128 v7;
  MinorSetRotateMatrixFunc SetRotateMatrix;
  void (__fastcall *invoke_impl)(intptr_t, void *, _OWORD *, intptr_t);
  intptr_t method_code;
  __int128 v11;
  intptr_t v12;
  _OWORD v13[4];

  pwork = hEffect->pwork;
  v7 = *(_OWORD *)&pMatrix->m03;
  SetRotateMatrix = EffMajorTable[hEffect->major]->SetRotateMatrix;
  invoke_impl = SetRotateMatrix->invoke_impl;
  v13[2] = *(_OWORD *)&pMatrix->m02;
  v13[3] = v7;
  method_code = SetRotateMatrix->method_code;
  v11 = *(_OWORD *)&pMatrix->m01;
  v12 = SetRotateMatrix->method;
  v13[0] = *(_OWORD *)&pMatrix->m00;
  v13[1] = v11;
  invoke_impl(method_code, pwork, v13, v12);
}

// 0x195c680
static void DefaultSetRotateMatrix(void *handle, const sdfMatrix4_t *pMatrix) {
  ;
}

// 0x195c690
void dds3EffectSetRGBA(effHandle_t *hEffect, u32 abgr) {
  MinorSetRGBAFunc SetRGBA;
  f64 v9;

  SetRGBA = EffMajorTable[hEffect->major]->SetRGBA;
  v9 = vmul_f32(vcvt_f32_u32(vand_s8(vshl_u32(vdup_n_s32(abgr), (uint32x2_t)0xFFFFFFF0FFFFFFF8LL), (int8x8_t)0xFF000000FFLL)), (float32x2_t)0x3C0000003C000000LL).n64_f64[0];
  (SetRGBA->invoke_impl)(SetRGBA->method_code, hEffect->pwork, SetRGBA->(f32)(u8)abgr * 0.0078125, v9, *((f32 *)&v9 + 1), (f32)HIBYTE(abgr) * 0.0078125);
}

// 0x195c7f0
void SetRGBA(effHandle_t *hEffect, const sdfVector4_t *abgr) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  MinorSetRGBAFunc SetRGBA;

  w = abgr->w;
  z = abgr->z;
  y = abgr->y;
  x = abgr->x;
  SetRGBA = EffMajorTable[hEffect->major]->SetRGBA;
  (SetRGBA->invoke_impl)(SetRGBA->method_code, hEffect->pwork, SetRGBA->x, y, z, w);
}

// 0x195c8b0
static void DefaultSetRGBA(void *handle, const sdfVector4_t *abgr) {
  ;
}

// 0x195c8c0
void dds3EffectSetLoop(effHandle_t *hEffect, u8 loop) {
  u32 v3;
  MinorSetLoopFunc SetLoop;

  v3 = loop;
  SetLoop = EffMajorTable[hEffect->major]->SetLoop;
  (SetLoop->invoke_impl)(SetLoop->method_code, hEffect->pwork, v3, SetLoop->method);
}

// 0x195c950
static void DefaultSetLoop(void *hPart, u8 loop) {
  ;
}

// 0x195c960
u8 dds3EffectGetLoop(effHandle_t *hEffect) {
  MinorGetLoopFunc GetLoop;

  GetLoop = EffMajorTable[hEffect->major]->GetLoop;
  return (GetLoop->invoke_impl)(GetLoop->method_code, hEffect->pwork, GetLoop->method);
}

// 0x195c9f0
static u8 DefaultGetLoop(void *hPart) {
  return 1;
}

// 0x195ca00
effHandle_t *dds3EffectCopy(effHandle_t *hCopyEff) {
  effHandle_t *v3;
  MinorCopyFunc Copy;
  void *v6;

  v3 = Allocate(effHandle_t);
  v3->major = hCopyEff->major;
  v3->minor = hCopyEff->minor;
  Copy = EffMajorTable[hCopyEff->major]->Copy;
  v6 = (Copy->invoke_impl)(Copy->method_code, hCopyEff->pwork, Copy->method);
  v3->pwork = v6;
  return v3;
}

// 0x195cae0
static void *DefaultCopy(void *handle) {
  return handle;
}

// 0x195caf0
effHandle_t *dds3EffectLoad(void *pD3P) {
  Project_libsdf_sdfResource_c *klass;
  void *v6;
  u16 *data;
  u16 v8;
  s32 v9;

  klass = pD3P[1].klass;
  v6 = *(void *)&klass->_1.byval_arg.bits;
    data = klass->_1.byval_arg.data;
  else
    data = 0;
  v8 = data[8];
  v9 = *((u32 *)data + 5);
  return dds3EffectCreate(v8, v9, v6);
}

// 0x195cbf0
effHandle_t *dds3EffectLoadEPL(void *pEPL) {
  return dds3EffectCreate(5u, 0, pEPL);
}
