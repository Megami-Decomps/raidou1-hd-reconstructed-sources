#pragma once
#include "types.h"
#include "SKLID.h"

#define HADAKA_ID 321
#define SE_MAX 256
#define LARGE_F 100000
#define MIN_VOL 96
#define MAXLEN 2000
#define MINLEN 1000
#define NML_DMG_WORK_MAX 32
#define DEBUG_X 380
#define DEBUG_Y 5
#define DEBUG_BGCOLOR 805306368
#define SBTL_MIN_VOL 48
#define SBTL_MAX_VOL 127
#define SBTL_MAXLEN 3000
#define SBTL_MINLEN 50

typedef struct DVLFOOTSE_WORK DVLFOOTSE_WORK;
typedef struct SBTLEFF_PACLIST SBTLEFF_PACLIST;
typedef struct SBTLSOUND_FOOTWORK SBTLSOUND_FOOTWORK;
typedef struct SBTLUNIT_WORK SBTLUNIT_WORK;

void sBtlPlaySESub(u32 no, s32 vol);
void sBtlPlaySESub_VolAngle(u32 no, s32 vol, f32 Angle);
s32 sBtlGetSpDevilID(s32 id);
void sBtlGetMemoryStatus(void);
void sBtlInitUnitSE(SBTLUNIT_WORK *wk);
void sBtlInitDevilFootSE(SBTLSOUND_FOOTWORK *fwk);
void sBtlDeleteUnitSE(SBTLUNIT_WORK *wk);
DVLFOOTSE_WORK *sBtlGetDevilFootSEData(s32 devilID);
void sBtlSMGLock(u32 SMGID);
void sBtlSMGUnLock(u32 SMGID);
void sBtlSMGClearLock(void);
void sBtlPlaySE(u32 no);
s32 sBtlSEVolCalc(const sdfVector4_t *pos, f32 maxlen, f32 minlen, s32 basevol, s32 minvol);
s32 sBtlSEVolAngleCalc(const sdfVector4_t *pos, f32 maxlen, f32 minlen, s32 basevol, s32 minvol, s32 *_Vol, f32 *_Angle);
void sBtlPlaySEEx(u32 no, const sdfVector4_t *pos, s32 flg);
s32 sBtlCheckDevilFootSE(SBTLSOUND_FOOTWORK *fwk, s32 devilID, f32 motionFrame);
void sBtlPlayMotionSE(SBTLUNIT_WORK *wk, s32 motionID, s32 startcnt);
void sBtlPlayDamageSE(const sdfVector4_t *pos, s32 damageType);
void sBtlPlayDamageSE_SEID(const sdfVector4_t *pos, u32 seid);
void sBtlPlay3DSE(u32 seid, const sdfVector4_t *pos);
void sBtlPlay3DSE_BaseVol(u32 seid, s32 _BaseVol, const sdfVector4_t *pos);
void sBtlPlaySpecialSE(const sdfVector4_t *pos, s32 specialType);
void sBtlStopSE(u32 no);
void Proc(void);
u32 sBtlGetDevilSESub(s32 devilID, s32 motionID);
u32 sBtlGetBossSE(s32 devilID, s32 motionID);
u32 sBtlGetViceSE(s32 devilID);
s32 sBtlLoadDevilSE(SBTLUNIT_WORK *wk);
bool sBtlLoadDevilSE_English(u32 SMGID_e);
s32 sBtlLoadSkillSE(SBTLEFF_PACLIST *ewk);
void sBtlPlaySkillSE(const sdfVector4_t *pos, SKLID skillID, s32 type);
void sBtlPlayViceSE(SBTLUNIT_WORK *wk, s32 type);
s32 sBtlLoadBossAtrac3(SBTLUNIT_WORK *wk);
void sBtlPlayBossAtrac3(SBTLUNIT_WORK *wk);
s32 sBtlLoadDeadVoice(SBTLUNIT_WORK *wk);
void sBtlPlayDeadVoice(SBTLUNIT_WORK *wk);
void sBtlPlayDeadVoice2D(SBTLUNIT_WORK *wk);
void Init(void);
void sBtlStopSEAll(s32 flag);
void sBtlStopSkillSE(s32 skillID, s32 type);
void sBtlStopMotionSE(s32 devilID, s32 motionID);
void sBtlDrawDebug(void);
