#pragma once
#include "types.h"

typedef struct SBTLUNIT_WORK SBTLUNIT_WORK;

extern sdfVector4_t nakama_pos;
extern sdfVector4_t nakama_rot;
extern f32 nakama_mv_rotbk;

void sBtlBackUpCamera(void);
void sBtlReturnCamera(void);
void sBtlBackUpCharTsf(void);
void sBtlReturnCharTsf(void);
void sBtlSetRndEncBg(s32 rnd_enc_id, bool isSymbolEncount);
void sBtlInitSceneRndEnc_IDFlag(void);
bool Init(void);
void sBtlDrawON(void);
bool Draw(void);
f32 sBtlGetGroundPos(f32 x, f32 z);
bool sBtlFree(void);
bool sBtlFreeBgScene(void);
bool sBtlReLoadFldScene(void);
void sBtlFldMapDisp(bool flg, char *sName);
bool sBtlFreeUIScene(void);
void sBtlFreeUISceneEnd(void);
bool sBtlSetScrollID(s32 id);
bool sBtlRestart_Scene(void);
bool sBtlReLoadMap(void);
void sBtlSetCutScroll(const sdfVector4_t *pos);
void sBtlDefaultCutScroll(void);
bool sBtlSetZoom(f32 x, f32 y, f32 z, f32 per, s32 time, u32 flg);
bool sBtlSetZoomLock(SBTLUNIT_WORK *wk, f32 per);
bool sBtlResetZoomLock(void);
bool sBtlCheckZoom(void);
s32 sBtlGetScrollID(void);
void sBtlSetZoom2(const sdfVector4_t *pos, f32 size, s32 frame);
void sBtlDefaultZoom2(s32 frame);
bool sBtlCheckZoom2(f32 *_ZoomScale);
void sBtlSetScroll(const sdfVector4_t *pos);
void sBtlDefaultScroll(void);
void sBtlSetUnitScroll(s32 unitID);
void sBtlDefaultUnitScroll(void);
s32 sBtlGetBgmID(s32 encountid);
void sBtlMapColorSet(u32 rgba);
void sBtlMapVisiblerSet(s32 mode);
void sBtlGetZeroPos(f32 *_ZeroX, f32 *_ZeroY, f32 *_ZeroZ);
f32 sBtlGetYukaEffY(void);
