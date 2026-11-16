#pragma once
#include "types.h"
#include "SBTLUNIT_MARK.h"
#include "SKLID.h"

typedef enum {
    PLAYER_LUCK_BEST__ = 0,
    PLAYER_LUCK_BETTER = 1,
    PLAYER_LUCK_GOOD__ = 2,
    PLAYER_LUCK_NORMAL = 3,
    PLAYER_LUCK_BAD___ = 4,
    PLAYER_LUCK_WORSE_ = 5,
    PLAYER_LUCK_WORST_ = 6,
    PLAYER_LUCK_NUM = 7,
} PLAYER_LUCK;

typedef struct DEVILDATA_WORK DEVILDATA_WORK;
typedef struct DEVIL_HUUMAITEM DEVIL_HUUMAITEM;
typedef struct SBTLANIM_HOKAN SBTLANIM_HOKAN;
typedef struct SBTLDMG_CYLINDERWORK SBTLDMG_CYLINDERWORK;
typedef struct SBTLUNIT_WORK SBTLUNIT_WORK;

struct DEVIL_HUUMAITEM {
    s32 gageNo;
    s32 failureRitu;
    s32 failureKind;
    s32 failureNum;
    s32 getItem[5];
    s32 getRitu[5];
};

extern u8 *wajutsu_namedata;
extern u8 *prank_namedata;
extern u8 *sbtlsysmsg_data;
extern u8 *player_namedata;
extern u8 *meirei_data;
extern u8 *num_data;
extern u8 *badst_namedata;
extern s32 nowSkillHelpID;
extern s32 nowItemHelpID;

bool sBtlSetVibeFadeIn(s32 index, s32 power, s32 frame);
bool sBtlSetVibeFadeOut(s32 index, s32 power, s32 frame);
void sBtlStopVibe(void);
void sBtlUpdateVibe(void);
bool SetVibe(s32 in, s32 life, s32 out, s32 power);
bool sBtlCalcVibe(void);
bool sBtlGetUnitHelperPos(SBTLUNIT_WORK *wk, SBTLUNIT_MARK mark);
bool sBtlGetUnitHelperMatrix(SBTLUNIT_WORK *wk, SBTLUNIT_MARK mark);
void sBtlGetQuatFromMatrix(const sdfMatrix4_t *mat);
void sBtlQuatFromVector(sdfVector4_t *qt, f32 x, f32 y, f32 z, f32 rad);
f32 sBtlGetUnitDeg(const sdfVector4_t *rot);
void sBtlAddUnitDeg(SBTLUNIT_WORK *wk, f32 deg);
bool sBtlGetRotateDeg(const sdfVector4_t *rot, f32 deg);
void sBtlSetRotateDeg(SBTLUNIT_WORK *wk);
bool sBtlGetRotateDegX(const sdfVector4_t *rot, f32 deg);
s32 sBtlCheckCrossBox(const sdfVector4_t *vector1, f32 r1, u8 side, const sdfVector4_t *vector2, f32 width, f32 height);
bool sBtlCheckCrossCircle(const sdfVector4_t *vector1, f32 r1, const sdfVector4_t *vector2, f32 r2);
bool sBtlCheckCrossCircle_Rot(const sdfVector4_t *vector1, const sdfVector4_t *rot1, f32 r1, const sdfVector4_t *vector2, f32 r2, f32 area);
bool sBtlCheckCrossCylinder_Circle(const sdfVector4_t *pos1, const sdfVector4_t *rot1, SBTLDMG_CYLINDERWORK *wk, const sdfVector4_t *pos2, f32 area);
f32 sBtlGetRadian(const sdfVector4_t *t1, const sdfVector4_t *rot, const sdfVector4_t *t2, f32 per);
f32 sBtlGetRadian_AndSet_New(SBTLUNIT_WORK *wk, const sdfVector4_t *t1, const sdfVector4_t *rot, const sdfVector4_t *t2, f32 per, f32 _Limit);
f32 sBtlGetChorikiDeg(const sdfVector4_t *t1, const sdfVector4_t *rot, const sdfVector4_t *tVec2, f32 per);
sdfVector4_t sBtlGetTargrtVec(SBTLUNIT_WORK *wk, SBTLUNIT_WORK *tgt);
bool sBtlGetRadian_X(const sdfVector4_t *t1, const sdfVector4_t *rot, const sdfVector4_t *rot2, const sdfVector4_t *t2, f32 per);
bool sBtlCheckInner(const sdfVector4_t *pos0, const sdfVector4_t *pos1, const sdfVector4_t *pos2, f32 rad);
bool sBtlCheckPos_Right(const sdfVector4_t *t1, const sdfVector4_t *rot, const sdfVector4_t *t2);
bool sBtlGetQuat(const sdfVector4_t *t1, const sdfVector4_t *t2);
bool sBtlGetNextPos(SBTLUNIT_WORK *wk);
bool sBtlGetPosforDistance(SBTLUNIT_WORK *wk, f32 distance);
bool sBtlSetPushPos(SBTLUNIT_WORK *wk1, f32 r1, SBTLUNIT_WORK *wk2, f32 r2, f32 ground);
bool sBtlSetPullPos(SBTLUNIT_WORK *wk1, f32 r1, SBTLUNIT_WORK *wk2, f32 r2, f32 ground);
bool sBtlCheckWorldtoScreen(const sdfVector4_t *pos);
bool sBtlChangeWorldtoScreen(sdfVector4_t *ppos);
bool sBtlChangeWorldtoScreenUnity(sdfVector4_t *ppos);
bool sBtlChangeWorldtoScreenUnity4(sdfVector4_t *ppos);
bool sBtlChangeWorldtoScreenUnity3(f32 x, f32 y, f32 z, sdfVector4_t *ppos);
bool sBtlChangeWorldtoScreen2(sdfVector4_t *ppos);
bool sBtlChkWorldtoScreenIn(f32 x, f32 y, f32 z);
s32 sBtlGetLargePara(s16 *adr, s32 max);
void sBtlParaAdd(s32 *para, s32 add, s32 max, s32 reset);
void sBtlParaAdd_16(s16 *para, s16 add, s16 max, s16 reset);
void sBtlParaAdd_8(s8 *para, s8 add, s8 max, s8 reset);
void sBtlParaDec(s32 *para, s32 dec, s32 max);
void sBtlParaDec_16(s16 *para, s16 dec, s16 max);
void sBtlParaDec_8(s8 *para, s8 dec, s8 max);
f32 sBtlGetBezier(f32 x0, f32 x1, f32 x2, f32 x3, f32 bt);
u8 sBtlGetMeireiFont(s32 id);
void sBtlDrawMeireiList(s32 x, s32 y, s32 z, u32 rgba, s32 id);
void sBtlDrawNum_Hex(s32 x, s32 y, s32 z, u32 rgba, char *str);
void sBtlDrawNum(s32 x, s32 y, s32 z, u32 rgba, s8 str);
char *sBtlGetRaceNameFont(s32 id);
void sBtlDrawRaceName(s32 x, s32 y, s32 z, u32 rgba, s32 id);
char *sBtlGetPlayerNameFont(s32 id);
void sBtlDrawPlayerName(s32 x, s32 y, s32 z, u32 rgba, s32 id);
char *sBtlGetDevilNameFont(s32 id, bool tagID);
bool sBtlIsDLCDevil(s32 id);
void sBtlDrawDevilName(s32 x, s32 y, s32 z, u32 rgba, s32 id);
void sBtlDrawDevilName2(SBTLUNIT_WORK *wk, s32 x, s32 y, s32 z, u32 rgba, s32 id);
void sBtlDrawNum_Font0(s32 x, s32 y, s32 z, u32 rgba, s32 num, s8 mode);
void sBtlDrawNum_X(s32 x, s32 y, s32 z, u32 rgba, s32 id);
char *sBtlGetSkillNameFont(s32 id);
char *sBtlGetSkillHelpFont(s32 id, bool tagID);
char *sBtlGetSkillHelpValue(s32 id, char *name);
void sBtlDrawSkillName(SBTLUNIT_WORK *wk, s32 x, s32 y, s32 z, u32 rgba, SKLID id);
void sBtlDrawSkillNameOff(SBTLUNIT_WORK *wk);
char *sBtlGetItemNameFont(s32 id);
char *sBtlGetItemHelpFont(s32 id, bool tagID);
char *sBtlGetItemHelpValue(s32 id, char *name);
char *sBtlGetParHelpFont(s32 id, bool tagID);
void sBtlDrawItemName(s32 x, s32 y, s32 z, u32 rgba, s32 id);
char *sBtlGetAisyoNameFont(s32 id);
char *sBtlGetAisyoHelpFont(s32 id);
void sBtlDrawAisyoName(s32 x, s32 y, s32 z, u32 rgba, s32 id);
char *sBtlGetWajutsuNameFont(s32 id);
char *sBtlGetPlayerRankNameFont(s32 id);
char *sBtlGetBSTNameFont(s32 id);
void sBtlDrawBSTName(s32 x, s32 y, s32 z, u32 rgba, s32 id);
void sBtlGetSkillMenu(SBTLUNIT_WORK *wk, u16 typeflg);
DEVILDATA_WORK *sBtlGetDevilData(s32 id, s32 encountno);
void sBtlSetDevilDataInit(s32 index, void *tbl);
void sBtlSetDevilHuumaItemInit(s32 index, void *tbl);
DEVIL_HUUMAITEM *sBtlGetDevilHuumaItem(s32 id);
bool sBtlCheckVerticalArea(const sdfVector4_t *pos0, const sdfVector4_t *rot, const sdfVector4_t *pos1, f32 area);
void sBtlGetVerticalVector(const sdfVector4_t *pos0, const sdfVector4_t *pos1, const sdfVector4_t *pos2);
f32 sBtlGetVerticalLength(const sdfVector4_t *pos0, const sdfVector4_t *pos1, const sdfVector4_t *pos2);
f32 sBtlGetVerticalLength_Point(const sdfVector4_t *pos0, const sdfVector4_t *pos1, const sdfVector4_t *pos2);
void sBtlInitOutInPara(SBTLANIM_HOKAN *hwk, f32 para);
f32 sBtlCalcOutInPara(SBTLANIM_HOKAN *hwk);
void sBtlInitInOutPara(SBTLANIM_HOKAN *hwk, f32 time);
f32 sBtlCalcInOutPara(SBTLANIM_HOKAN *hwk, f32 time);
s16 sBtlGetPlayerLuck(void);
PLAYER_LUCK sBtlGetPlayerLuckStep(void);
s16 sBtlGetCorrectionParamLuck(void);
void sBtlPurificationPlayerLuck(void);
void sBtlSetPlayerLuck(s32 num);
s32 sBtlUpdatePlayerLuck(s32 updown);
void sBtlDeadFlagOn(SBTLUNIT_WORK *wk);
f32 sBtlGetPosToDir(f32 _FromX, f32 _FromZ, f32 _ToX, f32 _ToZ);
void sBtlGetPosToVec(f32 _FromX, f32 _FromY, f32 _FromZ, f32 _ToX, f32 _ToY, f32 _ToZ, f32 *_VX, f32 *_VY, f32 *_VZ);
f32 sBtlGetVecToDir(f32 _VX, f32 _VZ);
void sBtlGetDirToVec(f32 _Dir, f32 *_VX, f32 *_VZ);
f32 sBtlGetMag(f32 _VX, f32 _VZ);
f32 sBtlGetAtoB_LR(f32 a, f32 b);
f32 sBtlGetAtoB_LR_ABS(f32 a, f32 b);
f32 sBtlGetDir_PosDirToPos(f32 _FromX, f32 _FromZ, f32 aDirFrom, f32 _ToX, f32 _ToZ);
f32 sBtlGetABS(f32 a);
s32 GetABS(s32 a);
s32 sBtlGetCeilToInt(f32 a, f32 b);
f32 sBtlGetRotToDir(const sdfVector4_t *rot);
void sBtlGetRotToVector(const sdfVector4_t *rot, sdfVector4_t *_Vec);
f32 sBtlGetDir180(f32 dir);
f32 sBtlGetDirZ180(f32 dir);
f32 sBtlGetLenXZ(f32 _FromX, f32 _FromZ, f32 _ToX, f32 _ToZ);
f32 sBtlGetLenXYZ(f32 _FromX, f32 _FromY, f32 _FromZ, f32 _ToX, f32 _ToY, f32 _ToZ);
f32 GetLenXYZ(const sdfVector3_t *_FromXYZ, const sdfVector3_t *_ToXYZ);
f32 sBtlGet360(f32 a);
void sBtlGetMoveXZ(f32 _FromX, f32 _FromZ, f32 _Dir, f32 _Len, f32 *_ToX, f32 *_ToZ);
void sBtlGetMovePosToPos(f32 _FromX, f32 _FromZ, f32 _ToX, f32 _ToZ, f32 _Len, f32 *_GetX, f32 *_GetZ);
void GetMovePosToPos(f32 _FromX, f32 _FromY, f32 _FromZ, f32 _ToX, f32 _ToY, f32 _ToZ, f32 _Len, f32 *_GetX, f32 *_GetY, f32 *_GetZ);
void sBtlGetMovePosToVec(f32 _FromX, f32 _FromY, f32 _FromZ, f32 _VX, f32 _VY, f32 _VZ, f32 _Len, f32 *_GetX, f32 *_GetY, f32 *_GetZ);
void sBtlGetNormalPosToPos(f32 _FromX, f32 _FromY, f32 _FromZ, f32 _ToX, f32 _ToY, f32 _ToZ, f32 _Nml, f32 *_GetX, f32 *_GetY, f32 *_GetZ);
f32 sBtlGetDir_Hokan(f32 nowdir, f32 goaldir, f32 rotspeed);
f32 sBtlGetDir_Hokan_Mul(f32 nowdir, f32 goaldir, f32 min, f32 mul);
f32 sBtlGetDirY(f32 _Len, f32 _Y);
void GetDirToVec(f32 _Dir, f32 _DirY, sdfVector3_t *_Vec);
s32 sBtlGetLineCircle(f32 _FromX, f32 _FromZ, f32 _ToX, f32 _ToZ, f32 _CX, f32 _CZ, f32 _CR, f32 *_HitX1, f32 *_HitZ1, f32 *_HitX2, f32 *_HitZ2);
f32 sBtlGetRandomRange(f32 _A, f32 _B);
bool sBtlRaycast_PS2(f32 _SX, f32 _SY, f32 _SZ, f32 _EX, f32 _EY, f32 _EZ, s32 _LayerMask, void *_Hit, f32 *_HitX, f32 *_HitY, f32 *_HitZ);
bool sBtlRaycastAll_PS2(f32 _SX, f32 _SY, f32 _SZ, f32 _EX, f32 _EY, f32 _EZ, s32 _LayerMask, void **_Hits);
bool sBtlRaycastInside_PS2(f32 _SX, f32 _SY, f32 _SZ, s32 _LayerMask, void **_HitColliders);
void sBtlDrawLine_PS2(f32 _SX, f32 _SY, f32 _SZ, f32 _EX, f32 _EY, f32 _EZ, u32 _RGBA);
void sBtlDrawLine_Unity(f32 _SX, f32 _SY, f32 _SZ, f32 _EX, f32 _EY, f32 _EZ, u32 _RGBA);
void sBtlDrawLineX_PS2(f32 _CX, f32 _CY, f32 _CZ, f32 _Size, u32 _RGBA);
void sBtlDrawLineX_Unity(f32 _CX, f32 _CY, f32 _CZ, f32 _Size, u32 _RGBA);
