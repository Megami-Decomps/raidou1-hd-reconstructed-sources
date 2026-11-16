#include "types.h"
#include "atlfieldaccessor.h"
#include "atlfieldtableresource.h"
#include "atlfieldutil.h"
#include "cfg.h"
#include "cmpmain.h"
#include "configgamepad.h"
#include "dat.h"
#include "dds3_pad.h"
#include "dds3adminiprocess.h"
#include "dds3basic.h"
#include "dds3padmanager.h"
#include "evtbit.h"
#include "fld.h"
#include "libsdf.h"
#include "lmap.h"
#include "localize.h"
#include "sbtl.h"
#include "sbtlsub.h"
#include "sdf_vu0.h"
#include "sdfquat.h"
#include "sndat3.h"
#include "switchsys.h"
#include "tips.h"

static bool _IsKeyFree_k__BackingField;
static bool s_IsBoosted;
static s32 s_LastLoadingPriority;
static char *c_SpriteIDToKeyboardKeyNames;

// 0x22b12d0
void SetBoostLoadingMode(bool isBoost) {
  _BOOL4 v4;
  s32 backgroundLoadingPriority;

  v4 = isBoost;
  if (s_IsBoosted == v4)
    return;
  if (!isBoost)
  {
    BoostEnd();
    set_backgroundLoadingPriority(s_LastLoadingPriority, 0);
    goto LABEL_16;
  }
  BoostBegin();
  backgroundLoadingPriority = get_backgroundLoadingPriority(0);
  s_LastLoadingPriority = backgroundLoadingPriority;
  set_backgroundLoadingPriority(4, 0);
LABEL_16:
  s_IsBoosted = v4;
  return;
}

// 0x22b14a0
bool IsOnEventFlag(s32 flag, s32 flagJ) {
  if (flag)
    return ((flagJ != 1) ^ evtBitCheck(flag)) & 1;
  else
    return 1;
}

// 0x22b14e0
void InterpolateRotatePlayer(const sdfVector3_t *targetPos, const sdfVector3_t *playerPos, f32 *playerDir) {
  f32 z;
  f32 x;
  f32 v6;
  f32 v7;
  f32 PosToDir;
  f32 DirZ180;
  f32 AtoB_LR_ABS;
  f32 v12;
  f32 v14;
  f32 v16;
  f32 v17;
  f32 Dir_Hokan;
  f32 v20;
  f32 v25;
  f32 *p_x;
  f32 v29;
  f32 y;
  f32 v31;
  f32 w;
  sdfVector4_t v34;

  z = playerPos->z;
  x = playerPos->x;
  v6 = targetPos->z;
  v7 = targetPos->x;
  PosToDir = sBtlGetPosToDir(x, z, v7, v6);
  DirZ180 = sBtlGetDirZ180(PosToDir);
  AtoB_LR_ABS = sBtlGetAtoB_LR_ABS(*playerDir, DirZ180);
  if (AtoB_LR_ABS >= 120.0)
  {
    v12 = 15.0;
    v14 = *playerDir;
    goto LABEL_11;
  }
  if (AtoB_LR_ABS < 90.0)
  {
    v12 = 5.0;
    v14 = *playerDir;
    goto LABEL_11;
  }
  v12 = 10.0;
  v14 = *playerDir;
LABEL_11:
  v16 = sBtlGetPosToDir(x, z, v7, v6);
  v17 = sBtlGetDirZ180(v16);
  Dir_Hokan = sBtlGetDir_Hokan(v14, v17, v12);
  v20 = Dir_Hokan;
  fldGb->PlayerKakudo = v20;
  fldGb->PlayerKakudoGoal = v20;
  *playerDir = v20;
  if ((u32)fldGb)
  {
    goto LABEL_17;
  }
LABEL_17:
  vct_A = (struct sdfVector4_t)xmmword_3D015F0;
  v25 = RAD(fldGb->PlayerKakudo);
  FromRotation(v25);
  p_x = &vf00.x;
  v29 = p_x[4];
  y = p_x[5];
  v31 = p_x[6];
  w = p_x[7];
  v34.x = v29;
  v34.y = y;
  v34.z = v31;
  v34.w = w;
  dds3SetRotPoseSet(playerBasic, v34);
}

// 0x22b1820
f32 InterpolateRotate(const sdfVector3_t *targetPos, const sdfVector3_t *pos, f32 currentDir, f32 rotateSpeed) {
  f32 z;
  f32 x;
  f32 v9;
  f32 v10;
  f32 PosToDir;
  f32 DirZ180;

  z = pos->z;
  x = pos->x;
  v9 = targetPos->z;
  v10 = targetPos->x;
  PosToDir = sBtlGetPosToDir(x, z, v10, v9);
  DirZ180 = sBtlGetDirZ180(PosToDir);
  return sBtlGetDir_Hokan(currentDir, DirZ180, rotateSpeed);
}

// 0x22b18d0
bool IsBehindAToB(const sdfVector3_t *aPos, f32 aDir, const sdfVector3_t *bPos) {
  f32 z;
  f32 y;
  f32 x;
  f32 v9;
  f32 v10;
  f32 v11;
  f32 v12;
  sdfVector3_t v14;
  sdfVector3_t v15;

  z = bPos->z;
  y = bPos->y;
  x = bPos->x;
  v9 = aPos->z;
  v10 = aPos->y;
  v11 = aPos->x;
  v14.x = v11;
  v14.y = v10;
  v14.z = v9;
  v15.x = x;
  v15.y = y;
  v15.z = z;
  v12 = CalcDiffAngle(v14, aDir, v15, 1);
  return v12 > GetConst(fldESConstTbl, 30, 0);
}

// 0x22b19c0
f32 CalcDiffAngle(const sdfVector3_t *aPos, f32 aDir, const sdfVector3_t *bPos, bool isAbs) {
  f32 x;
  f32 v7;
  f32 v9;
  f32 v10;
  f32 AtoB_LR;

  x = bPos->x;
  v7 = aPos->x;
  aPos->x = x - v7;
  v9 = sub_188E410(*(long f64 *)&aPos->x) * 57.29578;
  if (v9 < 0.0)
    v9 = v9 + 360.0;
  if (v9 <= 360.0)
    v10 = v9;
  else
    v10 = v9 + -360.0;
  AtoB_LR = sBtlGetAtoB_LR(aDir, v10);
  if (!isAbs)
    return AtoB_LR;
  return sBtlGetABS(AtoB_LR);
}

// 0x22a8400
sdfVector3_t CalcOffset(sdfVector3_t *offset, sdfQuaternion_t *quat) {
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  f32 v8;
  f32 v9;
  f32 v11;
  f32 v12;
  f32 v13;
  f32 v14;
  f32 v15;
  f32 v16;
  f32 v20;
  sdfVector3_t v21;
  sdfVector3_t v22;
  sdfVector3_t v23;
  sdfVector3_t result;
  sdfQuaternion_t v25;
  sdfQuaternion_t v26;

  x = quat->x;
  y = quat->y;
  z = quat->z;
  w = quat->w;
  v25.x = x;
  v25.y = y;
  v25.z = z;
  v25.w = w;
  v21 = op_Multiply_60935616(v25, forwardVector, 0);
  v23.y = 1.5707964;
  v23.x = 0.0;
  v23.z = 0.0;
  v26 = Internal_FromEulerRad(v23, 0);
  v22 = op_Multiply_60935616(v26, v21, 0);
  v20 = v22.x;
  v8 = v22.y;
  v9 = v22.z;
  v20 = v22.x;
  v11 = upVector.x;
  v12 = upVector.y;
  v13 = upVector.z;
  v14 = v20;
  v20 = v14;
  v8 = v22.y;
  v9 = v22.z;
  v15 = offset->z;
  v16 = offset->y;
  result.x = (f32)((f32)(zeroVector.x + (f32)(v21.x * v15)) + (f32)(v20 * offset->x))
                  - (f32)(v11 * v16);
  result.z = (f32)((f32)(zeroVector.z + (f32)(v21.z * v15)) + (f32)(v9 * offset->x))
                  - (f32)(v13 * v16);
  result.y = (f32)((f32)(zeroVector.y + (f32)(v21.y * v15)) + (f32)(v8 * offset->x))
                  - (f32)(v12 * v16);
  return result;
}

// 0x22afa90
bool IsActiveLMap(void) {
  return lmapwk != 0;
}

// 0x22af9b0
bool IsOpenCamp(void) {
  return cmpProcessCheck();
}

// 0x22b0a90
bool IsFldKeyFree(bool isCheckSurprise) {
  bool result;
  bool IsSurprise;

  if (!get_isPlaying(0))
    return 0;
  if (!GBWK)
    return 0;
  if (!fldGb)
    return 0;
  if (!playerBasic)
    return 0;
  if (dds3AdminiGetNextSequence() != -1)
    return 0;
  if (!!cmpProcessCheck())
    return 0;
  if (!fldProcCheckFlag(0x40u))
    return 0;
  if (fldGb->NoInpPlCnt)
    return 0;
  if (tipsProcessCheck())
    return 0;
  if ((u32)(SequenceControl->phase - 47) > 0xFFFFFFFD)
    return 0;
  if (!isCheckSurprise)
    return 1;
  IsSurprise = IsSurprise(0);
  result = 0;
  if (!IsSurprise)
    return 1;
  return result;
}

// 0x22b1260
bool IsBattling(void) {
  return CheckRun();
}

// 0x22b1b00
bool IsBattleKeyFree(void) {
  const MethodInfo_308BD40 *v1;
  char v4;
  SBATTLE_WORK *v5;
  const MethodInfo_308BD60 *v7;
  bool result;
  const MethodInfo_308BD60 *v9;
  const MethodInfo_308BD60 *v10;
  s64 v12;
  s64 v13;
  s64 v14;
  System_Nullable_T__o v15;
  System_Nullable_T__o v16;
  System_Nullable_T__o v17;
  System_Nullable_T__o v18;
  System_Nullable_T__o v19;

  v13 = 0;
  if (wk)
  {
    *(u64 *)&v15.hasValue = &v14;
    v15.value = wk->status;
    v14 = 0;
    __ctor(v15, Method_System_Nullable_SBTLMAIN___ctor__, v1);
    v4 = v14;
    goto LABEL_5;
  }
  v4 = 0;
  v14 = 0;
LABEL_5:
  v5 = wk;
  if (!v5)
    return 0;
  *(u64 *)&v16.hasValue = &v12;
  v16.value = v5->status2;
  v12 = 0;
  __ctor(v16, Method_System_Nullable_SBTLMAIN2___ctor__, v1);
  result = 0;
  v13 = v12;
  if (!v4 || !(u8)v12)
    return result;
  *(u64 *)&v17.hasValue = &v14;
  v17.value = Method_System_Nullable_SBTLMAIN__get_Value__;
  if ((_get_Value(v17, v7) & 8) != 0)
    return 0;
  v18.value = Method_System_Nullable_SBTLMAIN__get_Value__;
  *(u64 *)&v18.hasValue = &v14;
  if ((_get_Value(v18, v9) & 0x10000) == 0)
    return 0;
  *(u64 *)&v19.hasValue = &v13;
  v19.value = Method_System_Nullable_SBTLMAIN2__get_Value__;
  if ((_get_Value(v19, v10) & 0x20000000) != 0)
    return 0;
  if (tipsProcessCheck())
    return 0;
  if (tipsProcessCheck_tipsAll())
    return 0;
  if (IsSceanStop())
    return 0;
  return wk->mode != 5;
}

// 0x22af830
void CheckKeyFree(void) {
  bool v4;
  bool IsFldKeyFree;

  v4 = CheckRun();
  if (!v4)
  {
    IsFldKeyFree = IsFldKeyFree(0);
    goto LABEL_18;
  }
  IsFldKeyFree = IsBattleKeyFree();
LABEL_18:
  _IsKeyFree_k__BackingField = IsFldKeyFree;
}

// 0x22afa20
bool IsNakamaMode(void) {
  return fldGb->nakamaMode != 0;
}

// 0x22b1d80
void CallFieldResult(void) {
  fldCallFieldResult();
}

// 0x22b1df0
char *CreateID16BaseString(s32 id) {
  Il2CppObject *v3;
  s32 data;

  data = id;
  v3 = Box(s32, &data);
  return Format("0x{0:X3}", v3, 0);
}

// 0x22b07c0
bool IsPlayingFieldResult(void) {
  return (u32)(SequenceControl->phase - 87) < 3;
}

// 0x22b1e80
bool IsFadeSyncAttachEffect(s32 id) {
  return id == 359 || id == 499 || id == 423;
}

// 0x22b1eb0
bool IsVisibleKeyboardGuide(void) {
  return 0;
}

// 0x22b1ec0
void CalcPlatformButtonInfo(GamePadSet configKey, bool *isKeyboard, char **keyboardCodeName, void *sprite) {
  s32 ConfigGAMEPAD;
  void *Instance;
  void *ButtonImage;

  ConfigGAMEPAD = cfgGetConfigGAMEPAD(configKey, 0);
  *keyboardCodeName = 0;
  sprite = 0;
  *isKeyboard = 0;
  Instance = get_Instance(0);
  ButtonImage = 0;
  if (!Instance)
    goto LABEL_8;
  goto LABEL_7;
  if (Instance)
LABEL_7:
    ButtonImage = GetButtonImage(Instance, 0, ConfigGAMEPAD, 0);
LABEL_8:
  sprite = ButtonImage;
}

// 0x22b1fd0
char *ConvertButtonToKeyName(GamePadSet configKey) {
  return 0;
}

// 0x22b1fe0
SDF_PADMAP ConvKeyIDToSDFPadMap(GamePadSet configKey) {
  u16 ConfigGAMEPAD;

  ConfigGAMEPAD = cfgGetConfigGAMEPAD(configKey, 0);
  return keyid_to_padmap[ConfigGAMEPAD];
}

// 0x22b20e0
bool IsKeyTrigger(GamePadSet configKey) {
  s32 v3;

  v3 = ConvKeyIDToSDFPadMap(configKey);
  return CHECK_TRIG(v3, 0);
}

// 0x22b2150
bool IsKeyTrigger_2(SDF_PADMAP keyID) {
  return CHECK_TRIG(keyID, 0);
}

// 0x22b2160
bool IsKeyPress(GamePadSet configKey) {
  s32 v3;

  v3 = ConvKeyIDToSDFPadMap(configKey);
  return CHECK_PRESS(v3, 0);
}

// 0x22b21d0
bool IsKeyPress_2(SDF_PADMAP keyID) {
  return CHECK_PRESS(keyID, 0);
}

// 0x22b21e0
bool IsPressAnyKey(void) {
  return GetCurrentAny(0);
}

// 0x22b21f0
void PlayFieldBGM(s32 map, s32 area) {
  s32 BgmId;

  BgmId = mapSoundGetBgmId(map, area);
  sndBgmLoadId_XF(BgmId);
  sndBgmPlay(BgmId, 0);
}

// 0x22b0830
void PlayBGM(s32 id) {
  sndBgmLoadId_XF(id);
  sndBgmPlay(id, 0);
}

// 0x22b2300
char *GetDevilName(bool isAttachID, s32 id) {
  char *DevilNameFont;
  Il2CppObject *v6;
  char *v7;
  char *LocalizeText;
  s32 data;

  DevilNameFont = sBtlGetDevilNameFont(id, 1);
  if (isAttachID)
  {
    data = id;
    v6 = Box(s32, &data);
    v7 = Format("0x{0:X3}", v6, 0);
    LocalizeText = GetLocalizeText(DevilNameFont, 0);
    return Concat_54831728(v7, " : ", LocalizeText, 0);
  }
  else
  {
    return GetLocalizeText(DevilNameFont, 0);
  }
}

// 0x22b24a0
s32 ConvDigit16To10(char *digit16Str) {
  if (IsNullOrEmpty(digit16Str, 0))
    return 0;
  if (digit16Str->_stringLength >= 3 && get_Chars(digit16Str, 0, 0) == 48 && (get_Chars(digit16Str, 1, 0) == 120 || get_Chars(digit16Str, 1, 0) == 88))
  {
    digit16Str = Remove(digit16Str, 0, 2, 0);
  }
  return ToInt32_55009392(digit16Str, 16, 0);
}

// 0x22b2610
char *ConvDigit10To16(s32 digit10Num, bool isAttach0x) {
    return 0;
}

// 0x22b26d0
void *ConvertIntToShortChuusei(s32 intChuusei) {
  System_ValueTuple_short__short__o v3;

  v3 = 0;
  short____ctor((System_ValueTuple_short__short__o)&v3, intChuusei, SHIWORD(intChuusei));
  return v3;
}

// 0x22b2740
s32 ConvertShortToIntChuusei(s16 chuusei, s16 chuuseiHigh) {
  return (u16)chuusei | ((u16)chuuseiHigh << 16);
}

// 0x22b2750
void RefreshAutoMap(const sdfVector3_t *pos) {
  f32 z;
  f32 x;
  s32 AutoMapID;

  z = pos->z;
  x = pos->x;
  AutoMapID = mapGetAutoMapID(x, z);
  mapAM_MaskSetCurrent(fldGb->fieldID, fldGb->floorID);
  miniMapIconSet(fldGb->fieldID, fldGb->floorID, AutoMapID, 1);
}
