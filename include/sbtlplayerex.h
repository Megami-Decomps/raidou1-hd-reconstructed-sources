#pragma once
#include "types.h"
#include "SBWEAPON_TYPE.h"
#include "SKLID.h"

typedef struct SBTLUNIT_WORK SBTLUNIT_WORK;

void sBtlPlayerInit(void);
bool sBtlPlayerGetCamMv(f32 *_TX, f32 *_TY, f32 *_TZ, f32 *_CX, f32 *_CY, f32 *_CZ, f32 *_Fov, f32 *_UpV, f32 *_AngleX, const sdfVector4_t *_targetPos, const sdfVector4_t *_cameraPos);
void sBtlPlayerCamMvReset(SBTLUNIT_WORK *wk);
void sBtlPlayerCamMvSetToResultMode(bool _OnOff);
bool sBtlPlayerGetCamJump(f32 *_TY, f32 *_CY, const sdfVector4_t *_targetPos, const sdfVector4_t *_cameraPos);
bool sBtlPlayerGetCamJump2(f32 *_TY, f32 *_CY, const sdfVector4_t *_targetPos, const sdfVector4_t *_cameraPos);
void sBtlPlayerSetCamJump_To_CamJump2(void);
void sBtlPlayerResetCamJump(void);
void sBtlPlayerSetMantOnOff(SBTLUNIT_WORK *wk, bool _OnOff, s32 _Mode);
void sBtlPlayerKudaOpenEffUpdate(SBTLUNIT_WORK *wk);
void sBtlPlayerMagSdLcAxEffUpdate(SBTLUNIT_WORK *wk);
void sBtlPlayerMagSdLcAxEff_WeaponCng_FromMenu(SBWEAPON_TYPE _OldType, SBWEAPON_TYPE _NewType);
void sBtlPlayerSetTuugiZokusei(s32 _Variation);
s32 sBtlPlayerGetSkillNum(void);
void sBtlPlayerJyusoEffOnOff(SBTLUNIT_WORK *wk, bool _OnOff);
void sBtlPlayerSetDirectHitRangeTgt(SBTLUNIT_WORK *wkPlayer, SKLID _SkillID, s32 _LifeTime, f32 _ActerOfsY, f32 _Size, f32 _TargetX, f32 _TargetY, f32 _TargetZ);
void sBtlPlayerUpdate(SBTLUNIT_WORK *wk);
