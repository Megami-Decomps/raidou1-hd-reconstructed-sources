#pragma once
#include "types.h"
#include "configgamepad.h"
#include "libsdf.h"

void SetBoostLoadingMode(bool isBoost);
bool IsOnEventFlag(s32 flag, s32 flagJ);
void InterpolateRotatePlayer(const sdfVector3_t *targetPos, const sdfVector3_t *playerPos, f32 *playerDir);
f32 InterpolateRotate(const sdfVector3_t *targetPos, const sdfVector3_t *pos, f32 currentDir, f32 rotateSpeed);
bool IsBehindAToB(const sdfVector3_t *aPos, f32 aDir, const sdfVector3_t *bPos);
f32 CalcDiffAngle(const sdfVector3_t *aPos, f32 aDir, const sdfVector3_t *bPos, bool isAbs);
sdfVector3_t CalcOffset(sdfVector3_t *offset, sdfQuaternion_t *quat);
bool IsActiveLMap(void);
bool IsOpenCamp(void);
bool IsFldKeyFree(bool isCheckSurprise);
bool IsBattling(void);
bool IsBattleKeyFree(void);
void CheckKeyFree(void);
bool IsNakamaMode(void);
void CallFieldResult(void);
char *CreateID16BaseString(s32 id);
bool IsPlayingFieldResult(void);
bool IsFadeSyncAttachEffect(s32 id);
bool IsVisibleKeyboardGuide(void);
void CalcPlatformButtonInfo(GamePadSet configKey, bool *isKeyboard, char **keyboardCodeName, void *sprite);
char *ConvertButtonToKeyName(GamePadSet configKey);
SDF_PADMAP ConvKeyIDToSDFPadMap(GamePadSet configKey);
bool IsKeyTrigger(GamePadSet configKey);
bool IsKeyTrigger_2(SDF_PADMAP keyID);
bool IsKeyPress(GamePadSet configKey);
bool IsKeyPress_2(SDF_PADMAP keyID);
bool IsPressAnyKey(void);
void PlayFieldBGM(s32 map, s32 area);
void PlayBGM(s32 id);
char *GetDevilName(bool isAttachID, s32 id);
s32 ConvDigit16To10(char *digit16Str);
char *ConvDigit10To16(s32 digit10Num, bool isAttach0x);
void *ConvertIntToShortChuusei(s32 intChuusei);
s32 ConvertShortToIntChuusei(s16 chuusei, s16 chuuseiHigh);
void RefreshAutoMap(const sdfVector3_t *pos);
