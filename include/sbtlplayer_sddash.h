#pragma once
#include "types.h"
#include "SKLID.h"

typedef struct SBTLUNIT_WORK SBTLUNIT_WORK;

void sBtlPlayerRSdDash_Init(void);
void sBtlPlayerRSdDash_Hit(SBTLUNIT_WORK *wkDmg, s32 _SerialID);
bool sBtlPlayerRSdDash_ChkHit(SBTLUNIT_WORK *wkDmg, s32 _SerialID);
s32 sBtlPlayerRSdDashInit(SBTLUNIT_WORK *wk, SKLID _SklID, s32 _ClearIndex);
void sBtlPlayerSetDamage(SBTLUNIT_WORK *wk_player, SBTLUNIT_WORK *wk_enemy);
f32 sBtlPlayerGetMoveSdDash(SBTLUNIT_WORK *wk);
void sBtlPlayerGetCamSdDash(f32 _NewCamX, f32 _NewCamY, f32 _NewCamZ, f32 *_OutX, f32 *_OutY, f32 *_OutZ);
s32 sBtlPlayerRSdDashProc(SBTLUNIT_WORK *wk, s16 mode);
