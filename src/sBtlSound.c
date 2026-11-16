#include "types.h"
#include "SKLID.h"
#include "cfg.h"
#include "dds3kerneldraw.h"
#include "mdl.h"
#include "p2sdplay.h"
#include "sbtl.h"
#include "sbtlskill.h"
#include "sbtlsound.h"
#include "sbtlsub.h"
#include "sbtlunit.h"
#include "sbtlvisual.h"
#include "sdf_vu0.h"
#include "sdfsound.h"
#include "sndat3.h"
#include "sndsmghd.h"

typedef struct DVLFOOTSE_WORK DVLFOOTSE_WORK;
typedef struct SBTLEFF_PACLIST SBTLEFF_PACLIST;
typedef struct SBTLSOUND_FOOTWORK SBTLSOUND_FOOTWORK;
typedef struct SBTLSOUND_SELISTITEM SBTLSOUND_SELISTITEM;
typedef struct SBTLUNIT_WORK SBTLUNIT_WORK;
typedef struct SE_DELAY_BSE_t SE_DELAY_BSE_t;
typedef struct SE_DELAY_MSE_t SE_DELAY_MSE_t;

struct SBTLSOUND_SELISTITEM {
    s32 nowCnt;
    s32 minCnt;
    s32 startCnt;
};

struct SE_DELAY_MSE_t {
    s32 mot_seid;
};

struct SE_DELAY_BSE_t {
    bool NowFramePlay;
    s32 Num;
    s32 NowCnt;
    s32 Cnt;
    s32 BufferMax;
    u32 *MidiNo;
    s32 *Volume;
    f32 *Angle;
};

static SBTLSOUND_SELISTITEM *sBtlSound_SETable[256];
static s32 gSeDelay_MSE_Max;
static SE_DELAY_MSE_t *gSeDelay_MSE;
static s32 gSeDelay_DAMAGE_Max;
static SE_DELAY_MSE_t *gSeDelay_DAMAGE;
static s32 gSeDelay_Skip_BSE_SE19;
static s32 gSeDelay_Skip_D10B_SE14;
static s32 gSeDelay_Skip_D10B_SE15;
static bool gSeDelay_DMG_GUARD;
static bool gSeDelay_DMG_GUARDHIT;
static bool gSeDelay_DMG_KYUSHU;
static bool gSeDelay_DMG_MUKOU;
static bool gSeDelay_DMG_NORMAL;
static bool gSeDelay_DMG_CRITICAL;
static bool gSeDelay_DMG_SWORD;
static bool gSeDelay_DMG_TUKI;
static SE_DELAY_BSE_t *gSeDelay_BSE_SE21;
static SE_DELAY_BSE_t *gSeDelay_BSE_SE73;
static s32 gDMG_SWORD_Cnt;
static s32 gDMG_TUKI_Cnt;
static s32 gDMG_GUN_Cnt;
static void *_newskillsmg;
static void *_r1combsmg;

static s32 GetFootSE_Devil(SBTLSOUND_FOOTWORK *fwk, s32 devilID);
static u32 GetDevilSE(s32 devilID, s32 motionID);
static f32 GetMotionSETime(SBTLUNIT_WORK *wk, s32 motionID);
static s32 GetBossAtrac3Filename(s32 devilID);
static void PlayMotionSENow(SBTLUNIT_WORK *wk, u32 no, s32 vol, s32 motionID);
static void DevilFootSEProc(SBTLUNIT_WORK *wk);
static u32 GetNewSklSmg(s32 skillID);
static u32 GetR1CombSklSmg(s32 skillID);
static u32 GetSkillSE(SKLID skillID, s32 type);

// 0x211fca0
void sBtlPlaySESub(u32 no, s32 vol) {
  p2sdPlaySE_Vol(no, vol);
}

// 0x211fcb0
void sBtlPlaySESub_VolAngle(u32 no, s32 vol, f32 Angle) {
  SE_DELAY_BSE_t *gSeDelay_BSE_SE21_local;
  s32 Num;
  s64 BufferMax;
  u32 *MidiNo;
  s64 v16;
  s64 v17;
  s32 Cnt;
  u32 *v19;
  s32 *Volume;
  f32 *v21;
  s64 v22;
  f32 *v23;
  s32 v24;

  if (no > 0x10073)
  {
    if (no >= 0x50B0016)
    {
      if (no != 87425044)
      {
        if (no != 87425045)
          goto LABEL_56;
        goto LABEL_17;
      }
    }
    else if (no != 84606996)
    {
      if (no != 84606997)
        goto LABEL_56;
LABEL_17:
      if (gSeDelay_Skip_D10B_SE15 >= 1)
        return;
      goto LABEL_44;
    }
    if (gSeDelay_Skip_D10B_SE14 >= 1)
      return;
    if (no < 0x50B0015)
    {
LABEL_51:
      gSeDelay_Skip_D10B_SE14 = 8;
      goto LABEL_56;
    }
LABEL_44:
    if (no != 87425044)
    {
      gSeDelay_Skip_D10B_SE15 = 8;
      goto LABEL_56;
    }
    goto LABEL_51;
  }
  if (no != 65561)
  {
    if (no == 65569)
    {
      gSeDelay_BSE_SE21_local = gSeDelay_BSE_SE21;
      if (!gSeDelay_BSE_SE21_local)
        goto LABEL_56;
    }
    else
    {
      if (no != 65651)
        goto LABEL_56;
      gSeDelay_BSE_SE21_local = gSeDelay_BSE_SE73;
      if (!gSeDelay_BSE_SE21_local)
        goto LABEL_56;
    }
    Num = gSeDelay_BSE_SE21_local->Num;
    if (Num)
    {
      BufferMax = (u32)gSeDelay_BSE_SE21_local->BufferMax;
      if (Num < (s32)BufferMax && (s32)BufferMax >= 1)
      {
        MidiNo = gSeDelay_BSE_SE21_local->MidiNo;
        v16 = -BufferMax;
        v17 = 8;
        while (*((u32 *)&MidiNo->obj.klass + v17))
        {
          ++v17;
          if (v16 + v17 == 8)
            return;
        }
        v22 = 4 * v17;
        *(u32 *)((char *)&MidiNo->obj.klass + v22) = no;
        v23 = gSeDelay_BSE_SE21_local->Angle;
        *(u32 *)((char *)&gSeDelay_BSE_SE21_local->Volume->obj.klass + v22) = 40 * vol / 100;
        v24 = gSeDelay_BSE_SE21_local->Num;
        *(f32 *)((char *)&v23->obj.klass + v22) = Angle;
        gSeDelay_BSE_SE21_local->Num = v24 + 1;
      }
      return;
    }
    if (gSeDelay_BSE_SE21_local->NowFramePlay)
    {
      if (gSeDelay_BSE_SE21_local->BufferMax > 0)
      {
        Cnt = gSeDelay_BSE_SE21_local->Cnt;
        gSeDelay_BSE_SE21_local->Num = 1;
        gSeDelay_BSE_SE21_local->NowCnt = Cnt;
        v19 = gSeDelay_BSE_SE21_local->MidiNo;
        Volume = gSeDelay_BSE_SE21_local->Volume;
        v21 = gSeDelay_BSE_SE21_local->Angle;
        v19[0] = no;
        v21[0] = Angle;
        Volume[0] = 50 * vol / 100;
      }
      return;
    }
    gSeDelay_BSE_SE21_local->Num = 0;
    gSeDelay_BSE_SE21_local->NowCnt = 0;
    gSeDelay_BSE_SE21_local->NowFramePlay = 1;
LABEL_56:
    p2sdPlaySE_VolAngle(no, vol, Angle);
    return;
  }
  if (gSeDelay_Skip_BSE_SE19 < 1)
  {
    gSeDelay_Skip_BSE_SE19 = 5;
    goto LABEL_56;
  }
}

// 0x2120050
static s32 GetFootSE_Devil(SBTLSOUND_FOOTWORK *fwk, s32 devilID) {
  s32 SpDevilID;
  DVLFOOTSE_WORK *foot;
  s64 sedataNum;
  s32 v10;
  s32 v11;
  u16 flg;
  s32 played;

  SpDevilID = sBtlGetSpDevilID(devilID);
  foot = sBtlGetVisualData(1u, devilID)->foot;
  sedataNum = foot->sedataNum;
  if (!foot->sedataNum)
    return -1;
  v10 = SpDevilID << 16;
  v11 = v10 + 0x4000000;
  flg = foot->flg;
  if ((flg & 2) == 0)
  {
    if ((flg & 4) == 0)
      return 0;
    played = fwk->played;
    return played + v11;
  }
  if (!fwk->prevSMGID)
    return sub_1905740(sedataNum, 0) + v11;
  if ((u32)sedataNum == 1)
    return v11;
  if ((u32)(sedataNum - 2) <= 2)
  {
    played = (s32)(sub_1905740((u32)(sedataNum - 1), 0) - v10 + fwk->prevSMGID - 0x3FFFFFF)
           % foot->sedataNum;
    return played + v11;
  }
  return 0;
}

// 0x2120270
static u32 GetDevilSE(s32 devilID, s32 motionID) {
  u32 result;
  u32 v8;

  result = (sBtlGetSpDevilID(devilID) << 16) + 0x4000000;
  if (motionID == -1)
    return result;
  if (motionID <= 199 && (u32)(motionID - 4) > 0x1B)
    return 0;
  v8 = result + motionID;
  return sndGetDevilEnglish(v8);
}

// 0x2120400
s32 sBtlGetSpDevilID(s32 id) {
  s32 v2;
  s32 result;

  v2 = id - 316;
  result = 132;
  switch (v2)
  {
    case 0:
      result = 293;
      break;
    case 160:
    case 215:
      return result;
    case 196:
      result = 428;
      break;
    case 197:
      result = 118;
      break;
    case 198:
      result = 417;
      break;
    case 199:
    case 212:
      result = 422;
      break;
    case 200:
      result = 150;
      break;
    case 201:
      result = 134;
      break;
    case 202:
      result = 129;
      break;
    case 203:
      result = 446;
      break;
    case 204:
      result = 91;
      break;
    case 205:
      result = 450;
      break;
    case 206:
    case 211:
      result = 93;
      break;
    case 207:
      result = 147;
      break;
    case 208:
      result = 121;
      break;
    case 209:
      result = 462;
      break;
    case 210:
      result = 418;
      break;
    case 213:
      result = 99;
      break;
    case 214:
      result = 109;
      break;
    case 216:
      result = 447;
      break;
    case 217:
      result = 102;
      break;
    default:
      if (id == 534)
        result = 429;
      else
        result = id;
      break;
  }
  return result;
}

// 0x21204e0
static f32 GetMotionSETime(SBTLUNIT_WORK *wk, s32 motionID) {
  return sBtlGetSETime(wk, motionID);
}

// 0x2120550
static s32 GetBossAtrac3Filename(s32 devilID) {
  char v2;

  if (devilID <= 269)
  {
    if (devilID != 262)
    {
      if ((devilID & 0xFFFFFFFE) != 0x10C)
        return 0;
      return 145;
    }
    return 144;
  }
  v2 = devilID - 29;
  if ((u32)(devilID - 285) <= 0x18)
  {
    if (((1 << v2) & 0x1C0000B) != 0)
      return 146;
    if (((1 << v2) & 0x180000) != 0)
      return 145;
    if (devilID == 300)
      return 144;
  }
  return 0;
}

// 0x21205d0
static void PlayMotionSENow(SBTLUNIT_WORK *wk, u32 no, s32 vol, s32 motionID) {
  s32 devilid;
  s32 scrStep;
  s32 ListID;
  SBATTLE_WORK *v15;
  s32 battlemode;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  s64 Angle;
  sdfVector4_t v24;

  devilid = wk->para->devilid;
  if (devilid > 286)
  {
    if (devilid != 288)
    {
      switch (wk->para->devilid)
      {
        case 0x12C:
          goto LABEL_47;
        case 0x12E:
          goto LABEL_60;
        case 0x130:
        case 0x131:
          goto LABEL_22;
        case 0x133:
        case 0x134:
        case 0x135:
          break;
        default:
          goto LABEL_16;
      }
    }
LABEL_6:
    if (motionID == 12)
    {
LABEL_57:
      sBtlPlayDeadVoice(wk);
    }
    else if (motionID == 13)
    {
LABEL_14:
      sndSeStop(-1, 0);
      sndSeLoadId(wk->sewk->boss_seid);
      sndSePlay(0);
    }
    goto LABEL_60;
  }
  switch (wk->para->devilid)
  {
    case 0x103:
    case 0x104:
    case 0x107:
      goto LABEL_60;
    case 0x105:
    case 0x108:
    case 0x109:
    case 0x10A:
    case 0x10B:
      goto LABEL_16;
    case 0x106:
LABEL_47:
      if (motionID != 22)
        goto LABEL_60;
      goto LABEL_57;
    case 0x10C:
    case 0x10D:
LABEL_22:
      if (motionID != 12)
        goto LABEL_60;
      scrStep = wk->scrStep;
      if (scrStep == 4)
      {
        goto LABEL_14;
      }
      scrStep = wk->scrStep;
      if (scrStep != 5)
      {
        scrStep = wk->scrStep;
        if (scrStep != 6)
          goto LABEL_60;
      }
      goto LABEL_57;
    default:
      if ((u32)(devilid - 287) >= 0xFFFFFFFE)
        goto LABEL_6;
LABEL_16:
      if ((u32)(motionID - 13) < 2)
      {
        if ((wk->side & 0x81) != 1)
          goto LABEL_60;
        p2sdSndStop(no);
        goto LABEL_60;
      }
      if (motionID == 12)
      {
        ListID = wk->ListID;
        v15 = wk;
        if (ListID != v15->playerID)
          goto LABEL_42;
        v15 = wk;
        battlemode = (u16)v15->battlemode;
        if (battlemode == 3)
          goto LABEL_42;
        battlemode = (u16)wk->battlemode;
        if (battlemode == 1)
        {
LABEL_42:
          if ((wk->sewk->flag & 1) == 0)
          {
            if (!wk->no_dead_se)
            {
              sBtlPlayDeadVoice(wk);
            }
            return;
          }
        }
      }
LABEL_60:
      if (wk->battlemode != 3)
        goto LABEL_66;
      if ((u16)no != 11 || (wk->side & 1) == 0)
      {
LABEL_66:
        x = wk->pos.x;
        y = wk->pos.y;
        z = wk->pos.z;
        w = wk->pos.w;
        Angle = 0;
        v24.x = x;
        v24.y = y;
        v24.z = z;
        v24.w = w;
        sBtlSEVolAngleCalc(v24, 3000.0, 50.0, 127, 48, (s32 *)&Angle + 1, &Angle);
        sBtlPlaySESub_VolAngle(no, SHIDWORD(Angle), *(f32 *)&Angle);
        return;
      }
      return;
  }
}

// 0x2120d90
void sBtlGetMemoryStatus(void) {
  ;
}

// 0x2120da0
void sBtlInitUnitSE(SBTLUNIT_WORK *wk) {
  SBTLSOUND_DEVILWORK *sewk;
  SBTLSOUND_FOOTWORK *footwk;

  sewk = wk->sewk;
  sewk->mot_step = 0;
  footwk = sewk->footwk;
  sewk->flag = 0;
  *(_OWORD *)&sewk->mot_SMGID = 0u;
  *(_OWORD *)&sewk->mot_nowcnt = 0u;
  sewk->at3gstat = 0;
  sewk->bossAt3gstat = 0;
  footwk->prevSMGID = 0;
  footwk->played = 0;
  footwk->prevFrame = 100000.0;
}

// 0x2120e30
void sBtlInitDevilFootSE(SBTLSOUND_FOOTWORK *fwk) {
  fwk->prevSMGID = 0;
  fwk->played = 0;
  fwk->prevFrame = 100000.0;
}

// 0x2120e50
void sBtlDeleteUnitSE(SBTLUNIT_WORK *wk) {
  SBTLSOUND_DEVILWORK *sewk;

  sewk = wk->sewk;
  if (sewk)
  {
    sewk = wk->sewk;
      if (!sewk->mot_SMGID3)
    {
      return;
    }
  }
}

// 0x2120390
DVLFOOTSE_WORK *sBtlGetDevilFootSEData(s32 devilID) {
  return sBtlGetVisualData(1u, devilID)->foot;
}

// 0x2120f20
void sBtlSMGLock(u32 SMGID) {
  ;
}

// 0x2120f10
void sBtlSMGUnLock(u32 SMGID) {
  ;
}

// 0x2120f30
void sBtlSMGClearLock(void) {
  ;
}

// 0x2120f40
void sBtlPlaySE(u32 no) {
  p2sdPlaySE_Vol(no, 127);
}

// 0x2120fb0
s32 sBtlSEVolCalc(const sdfVector4_t *pos, f32 maxlen, f32 minlen, s32 basevol, s32 minvol) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  f32 *p_x;
  f32 *v20;
  f32 v21;
  f32 v22;
  f32 v23;
  f32 v25;
  f32 v28;
  f32 v29;
  s32 v30;
  s32 v31;
  s32 v32;
  s32 v33;

  w = pos->w;
  z = pos->z;
  y = pos->y;
  x = pos->x;
  vct_A = CameraEyePos;
  p_x = &vf00.x;
  p_x[8] = x;
  p_x[9] = y;
  p_x[10] = z;
  p_x[11] = w;
  vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  v20 = &vf00.x;
  v21 = v20[6];
  v22 = v20[4];
  v23 = v20[5];
  v25 = sqrtf((f32)((f32)(v22 * v22) + (f32)(v23 * v23)) + (f32)(v21 * v21));
  if (v25 > maxlen)
    return minvol;
  v28 = v25 - minlen;
  if (v28 > maxlen)
    v28 = maxlen;
  if (v28 < 0.0)
    v28 = 0.0;
  v29 = maxlen - v28;
  v30 = v29;
  if (v29 == INFINITY)
    v30 = 0x80000000;
  v31 = v30 * (basevol - minvol);
  v32 = maxlen;
  if (maxlen == INFINITY)
    v32 = 0x80000000;
  v33 = v31 / v32 + minvol;
  if (v33 >= 127)
    v33 = 127;
  return v33 & ~(v33 >> 31);
}

// 0x2121340
s32 sBtlSEVolAngleCalc(const sdfVector4_t *pos, f32 maxlen, f32 minlen, s32 basevol, s32 minvol, s32 *_Vol, f32 *_Angle) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  f32 *p_x;
  f32 *v24;
  f32 v25;
  f32 v26;
  f32 v27;
  f32 v28;
  f32 v29;
  f32 v31;
  f32 v32;
  f32 v33;
  f32 PosToDir;
  f32 v35;
  f32 AtoB_LR;
  f32 v37;
  f32 v38;
  s32 v39;
  s32 v40;
  s32 v41;
  s32 v42;
  s32 result;

  w = pos->w;
  z = pos->z;
  y = pos->y;
  x = pos->x;
  vct_A = CameraEyePos;
  p_x = &vf00.x;
  p_x[8] = x;
  p_x[9] = y;
  p_x[10] = z;
  p_x[11] = w;
  vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  v24 = &vf00.x;
  v25 = v24[6];
  v26 = v24[4];
  v27 = v24[5];
  v28 = (f32)(v26 * v26) + (f32)(v27 * v27);
  v29 = v25 * v25;
  v31 = CameraEyePos.x;
  v32 = CameraEyePos.z;
  v33 = sqrtf(v28 + v29);
  PosToDir = sBtlGetPosToDir(v31, v32, x, z);
  v35 = sBtlGetPosToDir(CameraEyePos.x, CameraEyePos.z, CameraTargetPos.x, CameraTargetPos.z);
  AtoB_LR = sBtlGetAtoB_LR(v35, PosToDir);
  if (v33 <= maxlen)
  {
    v37 = v33 - minlen;
    if ((f32)(v33 - minlen) > maxlen)
      v37 = maxlen;
    if (v37 < 0.0)
      v37 = 0.0;
    v38 = maxlen - v37;
    v39 = v38;
    if (v38 == INFINITY)
      v39 = 0x80000000;
    v40 = v39 * (basevol - minvol);
    if (maxlen == INFINITY)
      v41 = 0x80000000;
    else
      v41 = maxlen;
    v42 = v40 / v41 + minvol;
    if (v42 >= 127)
      v42 = 127;
    minvol = v42 & ~(v42 >> 31);
  }
  *Vol = minvol;
  result = minvol;
  if (AtoB_LR < 70.0 && AtoB_LR > -70.0)
    AtoB_LR = AtoB_LR * 1.9;
  if (AtoB_LR < -180.0)
    AtoB_LR = -180.0;
  if (AtoB_LR > 180.0)
    AtoB_LR = 180.0;
  *Angle = AtoB_LR;
  return result;
}

// 0x21217b0
void sBtlPlaySEEx(u32 no, const sdfVector4_t *pos, s32 flg) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  char v8;
  s32 v10;
  sdfVector4_t v12;

  w = pos->w;
  z = pos->z;
  y = pos->y;
  x = pos->x;
  v8 = flg;
  if ((flg & 1) != 0)
  {
    v12.x = x;
    v12.y = y;
    v12.z = z;
    v12.w = w;
    v10 = sBtlSEVolCalc(v12, 2000.0, 1000.0, 127, 96);
    goto LABEL_10;
  }
  v10 = 127;
LABEL_10:
  p2sdPlaySE_Vol(no, v10);
}

// 0x21218a0
static void DevilFootSEProc(SBTLUNIT_WORK *wk) {
  s32 ListID;
  SBATTLE_WORK *v5;
  s32 devilid;
  SBTLSOUND_FOOTWORK *footwk;
  DVLFOOTSE_WORK *foot;
  dds3ModelHandle_t *hModel;
  f32 MotionFrame;
  f32 prevFrame;
  s64 v15;
  s32 v17;
  f32 v18;
  f32 v19;
  s32 v20;
  u64 v21;
  s32 FootSE_Devil;
  u32 v24;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  f32 v31;
  f32 v32;
  f32 v33;
  f32 v34;
  f32 v36;
  SBTLUNIT_WORK *v37;
  s64 Angle;
  sdfVector4_t v39;
  sdfVector4_t v40;

  ListID = wk->ListID;
  v5 = wk;
  if (ListID == v5->playerID)
  {
    if (v5->battlemode == 1)
      goto LABEL_8;
  }
  devilid = wk->para->devilid;
  footwk = wk->sewk->footwk;
LABEL_12:
  goto LABEL_13;
LABEL_8:
  devilid = 321;
  footwk = wk->sewk->footwk;
  goto LABEL_12;
LABEL_13:
  foot = sBtlGetVisualData(1u, devilid)->foot;
  hModel = wk->hModel;
  if (hModel)
  {
    MotionFrame = mdlGetMotionFrame(hModel);
    prevFrame = footwk->prevFrame;
    footwk->prevFrame = MotionFrame;
    if (prevFrame > MotionFrame)
      goto LABEL_18;
  }
  else
  {
    MotionFrame = 0.0;
    v36 = footwk->prevFrame;
    footwk->prevFrame = 0.0;
    if (v36 > 0.0)
LABEL_18:
      footwk->played = 0;
  }
  if (foot->frameNum)
  {
    v15 = 8;
    v37 = wk;
    do
    {
      if (v15 - 8 >= footwk->played && *((f32 *)&foot->frame->obj.klass + v15) <= MotionFrame)
      {
        FootSE_Devil = GetFootSE_Devil(footwk, devilid);
        if (FootSE_Devil)
        {
          v24 = FootSE_Devil;
          if ((wk->side & 1) != 0)
          {
            wk = v37;
            if (wk->battlemode == 3)
            {
              x = v37->pos.x;
              y = v37->pos.y;
              z = v37->pos.z;
              w = v37->pos.w;
              Angle = 0;
              v40.x = x;
              v40.y = y;
              v40.z = z;
              v40.w = w;
              sBtlSEVolAngleCalc(v40, 3000.0, 50.0, 127, 48, (s32 *)&Angle + 1, &Angle);
              v17 = HIDWORD(Angle);
              v18 = 0.62992126;
LABEL_24:
              v19 = (f32)v17 * v18;
              if (v19 == INFINITY)
                v20 = 0x80000000;
              else
                v20 = v19;
              sBtlPlaySESub_VolAngle(v24, v20, *(f32 *)&Angle);
              footwk->prevSMGID = v24;
              footwk->played = v15 - 7;
              goto LABEL_28;
            }
          }
          v31 = wk->pos.x;
          v32 = wk->pos.y;
          v33 = wk->pos.z;
          v34 = wk->pos.w;
          Angle = 0;
          v39.x = v31;
          v39.y = v32;
          v39.z = v33;
          v39.w = v34;
          sBtlSEVolAngleCalc(v39, 3000.0, 50.0, 127, 48, (s32 *)&Angle + 1, &Angle);
          v17 = HIDWORD(Angle);
          v18 = 0.33070865;
          goto LABEL_24;
        }
      }
LABEL_28:
      v21 = v15 - 7;
      ++v15;
    }
    while (v21 < foot->frameNum);
  }
}

// 0x2121e10
s32 sBtlCheckDevilFootSE(SBTLSOUND_FOOTWORK *fwk, s32 devilID, f32 motionFrame) {
  VISUALDATA_WORK *VisualData;
  f32 prevFrame;
  DVLFOOTSE_WORK *foot;
  s64 v13;
  s32 result;

  VisualData = sBtlGetVisualData(1u, devilID);
  prevFrame = fwk->prevFrame;
  fwk->prevFrame = motionFrame;
  foot = VisualData->foot;
  if (prevFrame > motionFrame)
    fwk->played = 0;
  if (!foot->frameNum)
    return -1;
  v13 = 0;
  result = -1;
  while (v13 < fwk->played || foot->frame[v13] > motionFrame)
  {
    if (foot->frameNum == ++v13)
      return result;
  }
  result = GetFootSE_Devil(fwk, devilID);
  fwk->prevSMGID = result;
  fwk->played = v13 + 1;
  return result;
}

// 0x2121fa0
void sBtlPlayMotionSE(SBTLUNIT_WORK *wk, s32 motionID, s32 startcnt) {
  SBATTLE_WORK *v7;
  s32 ListID;
  s32 battlemode;
  s32 devilid;
  u32 BossSE;
  f32 SETime;
  s32 v16;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  s32 v21;
  SBTLSOUND_DEVILWORK *sewk;
  bool v23;
  s32 v24;
  s32 v25;
  s32 v26;
  sdfVector4_t v27;

  v7 = wk;
  if ((v7->status5 & 8) != 0)
    return;
  ListID = wk->ListID;
  if (ListID != v7->playerID)
  {
LABEL_13:
    devilid = (u16)wk->para->devilid;
    if (devilid == 297 || devilid == 290)
    {
      BossSE = sBtlGetBossSE(devilid, motionID);
      goto LABEL_19;
    }
    LOWORD(devilid) = wk->para->devilid;
    if (wk->endcnt)
      v23 = motionID == 7;
    else
      v23 = 0;
    if (v23)
      v24 = 13;
    else
      v24 = motionID;
    v25 = (s16)devilid;
    v26 = v24;
LABEL_53:
    BossSE = GetDevilSE(v25, v26);
LABEL_19:
    SETime = sBtlGetSETime(wk, motionID);
    if (SETime == INFINITY)
      v16 = 0x80000000;
    else
      v16 = SETime;
    if (BossSE)
    {
      x = wk->pos.x;
      y = wk->pos.y;
      z = wk->pos.z;
      w = wk->pos.w;
      v27.x = x;
      v27.y = y;
      v27.z = z;
      v27.w = w;
      v21 = sBtlSEVolCalc(v27, 2000.0, 1000.0, 127, 96);
      sewk = wk->sewk;
      if (sewk->mot_status >= 2)
        sewk->mot_status = 3;
      sewk->mot_nowcnt = 0;
      sewk->mot_startcnt = v16;
      sewk->mot_seid = BossSE;
      sewk->mot_vol = v21;
    }
    else
    {
      sewk = wk->sewk;
      sewk->mot_status = 4;
      *(u64 *)&sewk->mot_nowcnt = 0;
      *(u64 *)&sewk->mot_seid = 0;
    }
    sewk->mot_motionID = motionID;
    return;
  }
  battlemode = (u16)v7->battlemode;
  if (battlemode == 3)
    goto LABEL_13;
  battlemode = (u16)wk->battlemode;
  if (battlemode == 1)
  {
    v25 = 321;
    v26 = motionID;
    goto LABEL_53;
  }
}

// 0x21226a0
void sBtlPlayDamageSE(const sdfVector4_t *pos, s32 damageType) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  u32 v10;
  u32 v14;
  u32 v18;
  f32 v23;
  s32 v24;
  f32 v27;
  s32 v28;
  u32 v30;
  s32 v31;
  f32 v34;
  s32 v35;
  u32 v38;
  s32 v39;
  u32 v42;
  s32 v43;
  s64 Angle;
  sdfVector4_t v48;
  sdfVector4_t v49;
  sdfVector4_t v50;
  sdfVector4_t v51;
  sdfVector4_t v52;
  sdfVector4_t v53;
  sdfVector4_t v54;
  sdfVector4_t v55;
  sdfVector4_t v56;

  w = pos->w;
  z = pos->z;
  y = pos->y;
  x = pos->x;
  Angle = 0;
  switch (damageType)
  {
    case 1:
      if (!gSeDelay_DMG_GUARD)
      {
        v10 = sub_1905740(4, 0) + 65604;
        p2sdSndStop(65604);
        p2sdSndStop(65605);
        p2sdSndStop(65606);
        p2sdSndStop(65607);
        v48.x = x;
        v48.y = y;
        v48.z = z;
        v48.w = w;
        sBtlSEVolAngleCalc(v48, 3000.0, 50.0, 127, 48, (s32 *)&Angle + 1, &Angle);
        sBtlPlaySESub_VolAngle(v10, SHIDWORD(Angle), *(f32 *)&Angle);
        gSeDelay_DMG_GUARD = 1;
      }
      break;
    case 2:
      if (!gSeDelay_DMG_NORMAL)
      {
        v14 = sub_1905740(3, 0) + 0x10000;
        p2sdSndStop(0x10000);
        p2sdSndStop(65537);
        p2sdSndStop(65538);
        v49.x = x;
        v49.y = y;
        v49.z = z;
        v49.w = w;
        sBtlSEVolAngleCalc(v49, 3000.0, 50.0, 127, 48, (s32 *)&Angle + 1, &Angle);
        sBtlPlaySESub_VolAngle(v14, SHIDWORD(Angle), *(f32 *)&Angle);
        gSeDelay_DMG_NORMAL = 1;
      }
      break;
    case 3:
      if (!gSeDelay_DMG_CRITICAL)
      {
        v18 = sub_1905740(2, 0) + 65539;
        p2sdSndStop(65539);
        p2sdSndStop(65540);
        v50.x = x;
        v50.y = y;
        v50.z = z;
        v50.w = w;
        sBtlSEVolAngleCalc(v50, 3000.0, 50.0, 127, 48, (s32 *)&Angle + 1, &Angle);
        sBtlPlaySESub_VolAngle(v18, SHIDWORD(Angle), *(f32 *)&Angle);
        gSeDelay_DMG_CRITICAL = 1;
      }
      break;
    case 4:
      if (!gSeDelay_DMG_MUKOU)
      {
        p2sdSndStop(65563);
        v51.x = x;
        v51.y = y;
        v51.z = z;
        v51.w = w;
        sBtlSEVolAngleCalc(v51, 3000.0, 50.0, 127, 48, (s32 *)&Angle + 1, &Angle);
        v23 = *(f32 *)&Angle;
        v24 = HIDWORD(Angle);
        p2sdPlaySE_VolAngle(65563, v24, v23);
        gSeDelay_DMG_MUKOU = 1;
      }
      break;
    case 5:
      if (!gSeDelay_DMG_KYUSHU)
      {
        p2sdSndStop(65562);
        v52.x = x;
        v52.y = y;
        v52.z = z;
        v52.w = w;
        sBtlSEVolAngleCalc(v52, 3000.0, 50.0, 127, 48, (s32 *)&Angle + 1, &Angle);
        v27 = *(f32 *)&Angle;
        v28 = HIDWORD(Angle);
        p2sdPlaySE_VolAngle(65562, v28, v27);
        gSeDelay_DMG_KYUSHU = 1;
      }
      break;
    case 6:
      switch (gDMG_GUN_Cnt)
      {
        case 0:
          v30 = 65616;
          p2sdSndStop(65616);
          v31 = 65617;
          goto LABEL_90;
        case 1:
          v30 = 65617;
          p2sdSndStop(65617);
          v31 = 65618;
          goto LABEL_90;
        case 2:
          v30 = 65618;
          p2sdSndStop(65618);
          v31 = 65619;
LABEL_90:
          p2sdSndStop(v31);
          ++gDMG_GUN_Cnt;
          goto LABEL_94;
        case 3:
          p2sdSndStop(65616);
          v30 = 65619;
          p2sdSndStop(65619);
          gDMG_GUN_Cnt = 0;
          goto LABEL_94;
        default:
          v30 = 0;
LABEL_94:
          v54.x = x;
          v54.y = y;
          v54.z = z;
          v54.w = w;
          sBtlSEVolAngleCalc(v54, 3000.0, 50.0, 127, 48, (s32 *)&Angle + 1, &Angle);
          sBtlPlaySESub_VolAngle(v30, SHIDWORD(Angle), *(f32 *)&Angle);
          break;
      }
      break;
    case 7:
      if (!gSeDelay_DMG_GUARDHIT)
      {
        p2sdSndStop(65541);
        v53.x = x;
        v53.y = y;
        v53.z = z;
        v53.w = w;
        sBtlSEVolAngleCalc(v53, 3000.0, 50.0, 127, 48, (s32 *)&Angle + 1, &Angle);
        v34 = *(f32 *)&Angle;
        v35 = HIDWORD(Angle);
        p2sdPlaySE_VolAngle(65541, v35, v34);
        gSeDelay_DMG_GUARDHIT = 1;
      }
      break;
    case 8:
      if (!gSeDelay_DMG_SWORD)
      {
        switch (gDMG_SWORD_Cnt)
        {
          case 0:
            v38 = 65590;
            p2sdSndStop(65590);
            p2sdSndStop(65591);
            v39 = 65592;
            goto LABEL_110;
          case 1:
            p2sdSndStop(65591);
            p2sdSndStop(65592);
            p2sdSndStop(65593);
            v38 = 65591;
            ++gDMG_SWORD_Cnt;
            break;
          case 2:
            p2sdSndStop(65590);
            v38 = 65592;
            p2sdSndStop(65592);
            v39 = 65593;
LABEL_110:
            p2sdSndStop(v39);
            ++gDMG_SWORD_Cnt;
            break;
          case 3:
            p2sdSndStop(65590);
            p2sdSndStop(65591);
            v38 = 65593;
            p2sdSndStop(65593);
            gDMG_SWORD_Cnt = 0;
            break;
          default:
            v38 = 0;
            break;
        }
        v55.x = x;
        v55.y = y;
        v55.z = z;
        v55.w = w;
        sBtlSEVolAngleCalc(v55, 3000.0, 50.0, 127, 48, (s32 *)&Angle + 1, &Angle);
        sBtlPlaySESub_VolAngle(v38, SHIDWORD(Angle), *(f32 *)&Angle);
        gSeDelay_DMG_SWORD = 1;
      }
      break;
    case 9:
      if (!gSeDelay_DMG_TUKI)
      {
        switch (gDMG_TUKI_Cnt)
        {
          case 0:
            v42 = 65594;
            p2sdSndStop(65594);
            v43 = 65595;
            goto LABEL_128;
          case 1:
            v42 = 65595;
            p2sdSndStop(65595);
            v43 = 65596;
            goto LABEL_128;
          case 2:
            v42 = 65596;
            p2sdSndStop(65596);
            v43 = 65597;
LABEL_128:
            p2sdSndStop(v43);
            ++gDMG_TUKI_Cnt;
            break;
          case 3:
            p2sdSndStop(65594);
            v42 = 65597;
            p2sdSndStop(65597);
            gDMG_TUKI_Cnt = 0;
            break;
          default:
            v42 = 0;
            break;
        }
        v56.x = x;
        v56.y = y;
        v56.z = z;
        v56.w = w;
        sBtlSEVolAngleCalc(v56, 3000.0, 50.0, 127, 48, (s32 *)&Angle + 1, &Angle);
        sBtlPlaySESub_VolAngle(v42, SHIDWORD(Angle), *(f32 *)&Angle);
        gSeDelay_DMG_TUKI = 1;
      }
      break;
    default:
      return;
  }
}

// 0x2123310
void sBtlPlayDamageSE_SEID(const sdfVector4_t *pos, u32 seid) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  s64 v10;
  s64 v11;
  s64 v16;
  s64 v17;
  s64 v18;
  s64 Angle;
  sdfVector4_t v21;

  w = pos->w;
  z = pos->z;
  y = pos->y;
  x = pos->x;
  v10 = 0;
  while (1)
  {
    if (v10 >= gSeDelay_DAMAGE_Max)
      break;
    v11 = (s64)gSeDelay_DAMAGE + 8 * v10++;
    if (*(u32 *)(*(u64 *)(v11 + 32) + 16) == (u64)seid)
      return;
  }
  Angle = 0;
  v21.x = x;
  v21.y = y;
  v21.z = z;
  v21.w = w;
  sBtlSEVolAngleCalc(v21, 3000.0, 50.0, 127, 48, (s32 *)&Angle + 1, &Angle);
  sBtlPlaySESub_VolAngle(seid, SHIDWORD(Angle), *(f32 *)&Angle);
  v16 = 0;
  while (1)
  {
    if (v16 >= gSeDelay_DAMAGE_Max)
      break;
    v17 = (s64)gSeDelay_DAMAGE + 8 * v16++;
    v18 = *(u64 *)(v17 + 32);
    if (!*(u32 *)(v18 + 16))
    {
      v18 = *(&gSeDelay_DAMAGE->max_length + v16);
      *(u32 *)(v18 + 16) = seid;
      return;
    }
  }
}

// 0x2120cc0
void sBtlPlay3DSE(u32 seid, const sdfVector4_t *pos) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  s64 Angle;
  sdfVector4_t v11;

  w = pos->w;
  z = pos->z;
  y = pos->y;
  x = pos->x;
  Angle = 0;
  v11.x = x;
  v11.y = y;
  v11.z = z;
  v11.w = w;
  sBtlSEVolAngleCalc(v11, 3000.0, 50.0, 127, 48, (s32 *)&Angle + 1, &Angle);
  sBtlPlaySESub_VolAngle(seid, SHIDWORD(Angle), *(f32 *)&Angle);
}

// 0x2121d10
void sBtlPlay3DSE_BaseVol(u32 seid, s32 _BaseVol, const sdfVector4_t *pos) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  f32 v12;
  s32 v13;
  s64 Angle;
  sdfVector4_t v15;

  w = pos->w;
  z = pos->z;
  y = pos->y;
  x = pos->x;
  Angle = 0;
  v15.x = x;
  v15.y = y;
  v15.z = z;
  v15.w = w;
  sBtlSEVolAngleCalc(v15, 3000.0, 50.0, 127, 48, (s32 *)&Angle + 1, &Angle);
  v12 = (f32)((f32)BaseVol / 127.0) * (f32)SHIDWORD(Angle);
  if (v12 == INFINITY)
    v13 = 0x80000000;
  else
    v13 = v12;
  sBtlPlaySESub_VolAngle(seid, v13, *(f32 *)&Angle);
}

// 0x21234d0
void sBtlPlaySpecialSE(const sdfVector4_t *pos, s32 specialType) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  s32 v10;
  s32 v11;
  u32 v12;
  s32 v14;
  f32 v17;
  s32 v18;
  s64 Angle;
  sdfVector4_t v20;
  sdfVector4_t v21;

  w = pos->w;
  z = pos->z;
  y = pos->y;
  x = pos->x;
  v10 = specialType - 1;
  v11 = 65556;
  v12 = 65561;
  switch (v10)
  {
    case 0:
      goto LABEL_5;
    case 1:
      v11 = 65557;
LABEL_5:
      goto LABEL_7;
    case 2:
      v11 = 65558;
LABEL_7:
      v20.x = x;
      v20.y = y;
      v20.z = z;
      v20.w = w;
      v14 = sBtlSEVolCalc(v20, 2000.0, 1000.0, 127, 96);
      p2sdPlaySE_Vol(v11, v14);
      return;
    case 3:
      goto LABEL_11;
    case 4:
      v12 = 65564;
LABEL_11:
      Angle = 0;
      v21.x = x;
      v21.y = y;
      v21.z = z;
      v21.w = w;
      sBtlSEVolAngleCalc(v21, 3000.0, 50.0, 127, 48, (s32 *)&Angle + 1, &Angle);
      v17 = (f32)SHIDWORD(Angle) * 0.70866144;
      if (v17 == INFINITY)
        v18 = 0x80000000;
      else
        v18 = v17;
      sBtlPlaySESub_VolAngle(v12, v18, *(f32 *)&Angle);
      return;
    default:
      return;
  }
}

// 0x2120c30
void sBtlStopSE(u32 no) {
  p2sdSndStop(no);
}

// 0x21236d0
void Proc(void) {
  s32 v1;
  s64 v5;
  s64 v7;
  s32 v8;
  s64 i;
  SBTLSOUND_DEVILWORK *sewk;
  SBATTLE_WORK *v12;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  s32 mode;
  bool v16;
  SBATTLE_WORK *v17;
  s64 v19;
  s64 v20;
  s32 v21;
  u32 mot_seid;
  s32 mot_motionID;
  s64 v26;
  s64 v27;
  s64 v28;
  s64 j;
  s64 v32;
  s64 k;
  s64 v35;
  SE_DELAY_BSE_t *gSeDelay_BSE_SE21_local;
  SE_DELAY_BSE_t *gSeDelay_BSE_SE73_local;
  s64 m;
  SBTLUNIT_LISTWORK *v49;
  SBTLUNIT_WORK *v50;
  s32 ListID;
  SBATTLE_WORK *v53;
  s32 battlemode;
  s32 Num;
  s32 v57;
  s64 BufferMax;
  s64 v59;
  s64 v60;
  s32 v61;
  s32 v62;
  s32 v63;
  s64 v64;
  s64 v65;
  s64 v66;
  s32 v67;
  s64 v68;
  s32 *Volume;
  s32 v70;
  s64 v71;
  s32 *v72;
  s32 v73;

  if (!wk)
    return;
  if (!wk->UnitMng)
    return;
  v5 = 32;
  do
  {
    v7 = *(s64 *)((char *)&sBtlSound_SETable->obj.klass + v5);
    v8 = *(u32 *)(v7 + 16) + 1;
    *(u32 *)(v7 + 16) = v8;
    if (v8 == 0x7FFFFFFF)
    {
      LODWORD((*(Il2CppClass **)((char *)&sBtlSound_SETable->obj.klass + v5))->_1.name) = 0x7FFFFFFF;
    }
    v5 += 8;
  }
  while (v5 != 2080);
  for (i = 0; ; ++i)
  {
    v12 = wk;
    UnitMng = v12->UnitMng;
    if (i >= UnitMng->number)
      break;
    pUnit = UnitMng->pUnitL[i]->pUnit;
    if (!pUnit)
      continue;
    if (pUnit->hModel)
    {
      mode = pUnit->mode;
      v16 = mode < 3 || mode == 9;
      if (!v16)
      {
        if ((v12->status & 0x40) == 0)
          goto LABEL_52;
        goto LABEL_9000;
        if ((wk->status & 0x40) == 0)
        {
LABEL_52:
          sewk = pUnit->sewk;
          if (sewk->mot_status == 3)
          {
            v19 = 0;
            while (1)
            {
              if (v19 >= gSeDelay_MSE_Max)
                break;
              v20 = (s64)gSeDelay_MSE + 8 * v19++;
              v21 = *(u32 *)(*(u64 *)(v20 + 32) + 16);
              sewk = pUnit->sewk;
              if (v21 == sewk->mot_seid)
              {
                if (sewk->mot_nowcnt >= sewk->mot_startcnt)
                  sewk->mot_status = 4;
                goto LABEL_22;
              }
            }
            sewk = pUnit->sewk;
            if (sewk->mot_nowcnt >= sewk->mot_startcnt)
            {
              sewk->mot_status = 4;
              mot_seid = sewk->mot_seid;
              mot_motionID = sewk->mot_motionID;
              PlayMotionSENow(pUnit, mot_seid, v1, mot_motionID);
              v26 = 0;
              do
              {
                if (v26 >= gSeDelay_MSE_Max)
                {
                  sewk = pUnit->sewk;
                  goto LABEL_22;
                }
                v27 = (s64)gSeDelay_MSE + 8 * v26++;
                v28 = *(u64 *)(v27 + 32);
              }
              while (*(u32 *)(v28 + 16));
              v28 = *(&gSeDelay_MSE->max_length + v26);
              sewk = pUnit->sewk;
              *(u32 *)(v28 + 16) = sewk->mot_seid;
            }
          }
LABEL_22:
          ++sewk->mot_nowcnt;
          continue;
        }
LABEL_9000:
        if ((pUnit->status & 0x10) != 0 || (pUnit->vstatus & 0x2000000) != 0)
          goto LABEL_52;
        v17 = wk;
        if ((v17->scrFlag & 0x40000) == 0)
          continue;
        if ((pUnit->side & 0x81) != 1)
          continue;
        v17 = wk;
        if (v17->battlemode == 3)
          continue;
        goto LABEL_52;
      }
    }
  }
  for (j = 0; ; ++j)
  {
    if (j >= gSeDelay_MSE_Max)
      break;
    v32 = (s64)gSeDelay_MSE + 8 * j;
    *(u32 *)(*(u64 *)(v32 + 32) + 16) = 0;
  }
  for (k = 0; ; ++k)
  {
    if (k >= gSeDelay_DAMAGE_Max)
      break;
    v35 = (s64)gSeDelay_DAMAGE + 8 * k;
    *(u32 *)(*(u64 *)(v35 + 32) + 16) = 0;
  }
  if (gSeDelay_Skip_BSE_SE19 >= 1)
  {
    gSeDelay_Skip_BSE_SE19 = gSeDelay_Skip_BSE_SE19 - 1;
  }
  if (gSeDelay_Skip_D10B_SE14 >= 1)
  {
    gSeDelay_Skip_D10B_SE14 = gSeDelay_Skip_D10B_SE14 - 1;
  }
  if (gSeDelay_Skip_D10B_SE15 >= 1)
  {
    gSeDelay_Skip_D10B_SE15 = gSeDelay_Skip_D10B_SE15 - 1;
  }
  *(u64 *)&gSeDelay_DMG_GUARD = 0;
  gSeDelay_BSE_SE21_local = gSeDelay_BSE_SE21;
  if (!gSeDelay_BSE_SE21_local)
    return;
  if (!gSeDelay_BSE_SE21_local->NowFramePlay)
  {
    Num = gSeDelay_BSE_SE21_local->Num;
    if (Num >= 1)
    {
      v57 = gSeDelay_BSE_SE21_local->NowCnt - 1;
      v16 = gSeDelay_BSE_SE21_local->NowCnt == 1;
      gSeDelay_BSE_SE21_local->NowCnt = v57;
      if (v57 < 0 || v16)
      {
        BufferMax = (u32)gSeDelay_BSE_SE21_local->BufferMax;
        if ((s32)BufferMax >= 1)
        {
          v59 = -BufferMax;
          v60 = 8;
          while (1)
          {
            v61 = *((u32 *)&gSeDelay_BSE_SE21_local->MidiNo->obj.klass + v60);
            if (v61)
              break;
            ++v60;
            if (v59 + v60 == 8)
              goto LABEL_166;
          }
          v68 = 4 * v60;
          p2sdPlaySE_VolAngle(v61, *((u32 *)&gSeDelay_BSE_SE21_local->Volume->obj.klass + v60), *((f32 *)&gSeDelay_BSE_SE21_local->Angle->obj.klass + v60));
          Volume = gSeDelay_BSE_SE21_local->Volume;
          *(u32 *)((char *)&gSeDelay_BSE_SE21_local->MidiNo->obj.klass + v68) = 0;
          *(u32 *)((char *)&Volume->obj.klass + v68) = 127;
          *(u32 *)((char *)&gSeDelay_BSE_SE21_local->Angle->obj.klass + v68) = 0;
          Num = gSeDelay_BSE_SE21_local->Num;
        }
LABEL_166:
        v70 = Num - 1;
        gSeDelay_BSE_SE21_local->Num = v70;
        if (v70 >= 1)
          gSeDelay_BSE_SE21_local->NowCnt = gSeDelay_BSE_SE21_local->Cnt;
      }
    }
  }
  gSeDelay_BSE_SE21_local->NowFramePlay = 0;
  gSeDelay_BSE_SE73_local = gSeDelay_BSE_SE73;
  if (!gSeDelay_BSE_SE73_local)
    return;
  if (!gSeDelay_BSE_SE73_local->NowFramePlay)
  {
    v62 = gSeDelay_BSE_SE73_local->Num;
    if (v62 >= 1)
    {
      v63 = gSeDelay_BSE_SE73_local->NowCnt - 1;
      v16 = gSeDelay_BSE_SE73_local->NowCnt == 1;
      gSeDelay_BSE_SE73_local->NowCnt = v63;
      if (v63 < 0 || v16)
      {
        v64 = (u32)gSeDelay_BSE_SE73_local->BufferMax;
        if ((s32)v64 >= 1)
        {
          v65 = -v64;
          v66 = 8;
          while (1)
          {
            v67 = *((u32 *)&gSeDelay_BSE_SE73_local->MidiNo->obj.klass + v66);
            if (v67)
              break;
            ++v66;
            if (v65 + v66 == 8)
              goto LABEL_169;
          }
          v71 = 4 * v66;
          p2sdPlaySE_VolAngle(v67, *((u32 *)&gSeDelay_BSE_SE73_local->Volume->obj.klass + v66), *((f32 *)&gSeDelay_BSE_SE73_local->Angle->obj.klass + v66));
          v72 = gSeDelay_BSE_SE73_local->Volume;
          *(u32 *)((char *)&gSeDelay_BSE_SE73_local->MidiNo->obj.klass + v71) = 0;
          *(u32 *)((char *)&v72->obj.klass + v71) = 127;
          *(u32 *)((char *)&gSeDelay_BSE_SE73_local->Angle->obj.klass + v71) = 0;
          v62 = gSeDelay_BSE_SE73_local->Num;
        }
LABEL_169:
        v73 = v62 - 1;
        gSeDelay_BSE_SE73_local->Num = v73;
        if (v73 >= 1)
          gSeDelay_BSE_SE73_local->NowCnt = gSeDelay_BSE_SE73_local->Cnt;
      }
    }
  }
  gSeDelay_BSE_SE73_local->NowFramePlay = 0;
  for (m = 0; ; ++m)
  {
    v49 = wk->UnitMng;
    if (m >= v49->number)
      return;
    v50 = v49->pUnitL[m]->pUnit;
    if (!v50)
      continue;
    if (!sBtlCheckDamageTarget(v50))
      continue;
    if (v50->motionno == 1)
      break;
LABEL_122:
    ;
  }
  ListID = v50->ListID;
  v53 = wk;
  if (ListID == v53->playerID)
  {
    battlemode = (u16)v53->battlemode;
    if (battlemode != 3)
    {
      if (battlemode != 1)
        goto LABEL_122;
    }
  }
  DevilFootSEProc(v50);
  goto LABEL_122;
}

// 0x2123fe0
u32 sBtlGetDevilSESub(s32 devilID, s32 motionID) {
  s32 v6;
  s32 v7;

  v6 = devilID;
  v7 = motionID;
  return GetDevilSE(v6, v7);
}

// 0x21222d0
u32 sBtlGetBossSE(s32 devilID, s32 motionID) {
  u32 result;

  result = 0;
  switch (motionID)
  {
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 26:
      if (devilID == 290)
      {
        return motionID + 86114304;
      }
      return (sBtlGetSpDevilID(devilID) << 16)
           + 0x4000000
           + motionID;
      return (sBtlGetSpDevilID(devilID) << 16)
           + 0x4000000
           + motionID;
      return (sBtlGetSpDevilID(devilID) << 16) + 0x4000000 + motionID;
    case 12:
      return (sBtlGetSpDevilID(devilID) << 16) + 67108865;
    case 13:
      return (sBtlGetSpDevilID(devilID) << 16) + 67108866;
    case 15:
      return (sBtlGetSpDevilID(devilID) << 16) + 67108868;
    case 16:
      return ((sBtlGetSpDevilID(devilID) << 16) + 67108865) | 4;
    default:
      return result;
  }
}

// 0x2124070
u32 sBtlGetViceSE(s32 devilID) {
  u32 v3;
  s32 v4;

  if ((u32)(devilID - 80) < 0xFFFFFFB1)
  {
    if ((u32)(devilID - 160) >= 0xFFFFFFB1)
    {
      v4 = 28311552;
      goto LABEL_11;
    }
    if ((u32)(devilID - 400) < 0xFFFFFFC0)
    {
      if ((u32)(devilID - 464) >= 0xFFFFFFC0)
      {
        v4 = 29360128;
        goto LABEL_11;
      }
      if ((u32)(devilID - 502) < 0xFFFFFFFA)
      {
        v3 = 0;
        goto LABEL_12;
      }
    }
  }
  v4 = 0x2000000;
LABEL_11:
  v3 = v4 + (devilID << 16);
LABEL_12:
  if (cfgGetConfigAUDIO(6, 0))
  {
    if (p2sdMidiRegister(v3 + 10))
      v3 += 10;
  }
  return v3;
}

// 0x2124180
s32 sBtlLoadDevilSE(SBTLUNIT_WORK *wk) {
  s32 ListID;
  s32 devilid;
  SBATTLE_WORK *v6;
  s32 v8;
  SBATTLE_WORK *v9;
  u32 ViceSE;
  s32 v12;
  s32 v13;
  s32 v15;
  s32 v16;
  s32 v17;
  s32 v19;
  SBTLSOUND_DEVILWORK *sewk;

  ListID = wk->ListID;
  devilid = wk->para->devilid;
  goto LABEL_3;
LABEL_7:
  if (v6->battlemode == 3)
    goto LABEL_11;
  return 1;
LABEL_3:
  v6 = wk;
  if (ListID == v6->playerID)
    goto LABEL_7;
LABEL_11:
  if ((wk->side & 1) == 0)
    goto LABEL_29;
  v8 = wk->ListID;
  v9 = wk;
  if (v8 == v9->playerID)
  {
    if (v9->battlemode != 3)
      goto LABEL_29;
  }
  ViceSE = sBtlGetViceSE(devilid);
  if (!ViceSE)
    goto LABEL_29;
  v12 = ViceSE;
  v13 = p2sdLoadCheckMidi(ViceSE);
  if (v13 == 2)
    return 0;
  if (!v13)
    goto LABEL_47;
LABEL_29:
  v15 = sBtlGetSpDevilID(devilid) << 16;
  v16 = v15 + 0x4000000;
  v17 = p2sdLoadCheckMidi(v16);
  if (v17 != 1)
  {
    if (!v17)
    {
      p2sdLoadSMGFile(v16);
      wk->sewk->mot_status = 1;
      return 0;
    }
    return 0;
  }
  v12 = v15 + 335544320;
  v19 = p2sdLoadCheckMidi(v12);
  if (v19 != 1)
  {
    if (v19)
      return 0;
LABEL_47:
    p2sdLoadSMGFile(v12);
    return 0;
  }
  sewk = wk->sewk;
  sewk->mot_SMGID = v16;
  sewk = wk->sewk;
  sewk->mot_status = 2;
  return 1;
}

// 0x2124590
bool sBtlLoadDevilSE_English(u32 SMGID_e) {
  u32 v4;
  s32 v5;

  v4 = SMGID_e & 0xFFFF0000;
  v5 = p2sdLoadCheckMidi(v4);
  if (v5)
  {
    if (v5 == 1)
      return v5;
    goto LABEL_11;
  }
  p2sdLoadSMGFile(v4);
LABEL_11:
  LOBYTE(v5) = 0;
  return v5;
}

// 0x2124660
static u32 GetNewSklSmg(s32 skillID) {
  if (!int___ContainsKey(_newskillsmg, skillID))
    return 0;
  return int___get_Item(_newskillsmg, skillID);
}

// 0x2124770
static u32 GetR1CombSklSmg(s32 skillID) {
  if (!int___ContainsKey(_r1combsmg, skillID))
    return 0;
  return int___get_Item(_r1combsmg, skillID);
}

// 0x2124880
static u32 GetSkillSE(SKLID skillID, s32 type) {
  s32 v5;
  SBTLSKILLP_TBL *Skilltbl;
  SBTLSKLVISUAL_TBL *SklVisualTbl;
  u32 result;

  if (skillID == 434)
    v5 = 79;
  else
    v5 = skillID;
  Skilltbl = sBtlGetSkilltbl(v5);
  SklVisualTbl = sBtlGetSklVisualTbl(v5);
  if ((Skilltbl->s_type & 4) != 0)
  {
    if ((u32)(type + 1) >= 4)
      return 0;
    else
      return dword_3CFCF30[type + 1];
  }
  if ((Skilltbl->type & 0xFFF) == 8)
  {
    if (v5 == 357)
      return 168951808;
    else
      return (v5 << 16) + 146800640;
  }
  if (v5 <= 529)
  {
    if (v5 == 312)
    {
      skillID = 112;
      goto LABEL_28;
    }
    if (v5 == 313)
    {
      skillID = 131;
      goto LABEL_28;
    }
    skillID = v5;
    if (v5 != 529)
    {
LABEL_21:
      if ((u32)skillID > 0x1FF)
        goto LABEL_22;
LABEL_28:
      result = GetR1CombSklSmg(skillID);
      if (!result)
        result = (skillID << 16) + 117440512;
      goto LABEL_32;
    }
LABEL_20:
    skillID = SklVisualTbl->SABno;
    goto LABEL_21;
  }
  if ((u32)(v5 - 545) <= 0x20 && ((1 << ((u8)v5 - 33)) & 0x100010001LL) != 0)
    goto LABEL_20;
LABEL_22:
  result = GetNewSklSmg(skillID);
  if (result)
  {
LABEL_32:
    switch (type)
    {
      case -1:
      case 1:
        return result;
      case 2:
        ++result;
        break;
      case 5:
        result += 2;
        break;
      default:
        return 0;
    }
  }
  return result;
}

// 0x2124a80
s32 sBtlLoadSkillSE(SBTLEFF_PACLIST *ewk) {
  s32 skillID;
  SBTLSKILLP_TBL *Skilltbl;
  s32 result;
  u32 SkillSE;

  skillID = ewk->skillID;
  Skilltbl = sBtlGetSkilltbl(skillID);
  result = 1;
  if (skillID != 287 && (Skilltbl->flg & 0x80000000) == 0 && skillID != 674 && !(Skilltbl->flg & 0x100 | Skilltbl->flg2 & 0x10))
  {
    SkillSE = GetSkillSE(skillID, -1);
    result = p2sdLoadCheckMidi(SkillSE);
    if (result != 1)
    {
      if (result)
        return 0;
      p2sdLoadSMGFile(SkillSE);
      return 0;
    }
    ewk->SMGID = SkillSE;
  }
  return result;
}

// 0x2124bd0
void sBtlPlaySkillSE(const sdfVector4_t *pos, SKLID skillID, s32 type) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  u32 flg;
  u32 SkillSE;
  SBTLUNIT_WORK *v16;
  s32 v19;
  s32 v21;
  SBTLUNIT_WORK *v23;
  s32 devilid;
  u32 v27;
  u32 v29;
  s64 Angle;
  sdfVector4_t v34;

  w = pos->w;
  z = pos->z;
  y = pos->y;
  x = pos->x;
  if (type == 1)
  {
    if (skillID != 896)
      goto LABEL_9;
    if (wk->encountno == 523)
      return;
  }
LABEL_9:
  flg = sBtlGetSkilltbl(skillID)->flg;
  if ((u32)(skillID - 669) >= 2)
  {
    if (skillID == 287 || (flg & 0x80000100) != 0)
      return;
  }
  else if ((flg & 0x100) != 0)
  {
    return;
  }
  switch (skillID)
  {
    case 230:
      v23 = wk->scrUnitList[0];
      devilid = v23->para->devilid;
      sndDeadSePlay_VolAngle(devilid, 127, 0.0);
      goto LABEL_43;
    case 231:
    case 232:
    case 233:
    case 234:
      SkillSE = GetSkillSE(skillID, type);
      if (!SkillSE)
        return;
      v21 = SkillSE;
      p2sdPlaySE_Vol(v21, 127);
      return;
    case 235:
    case 238:
      goto LABEL_43;
    case 236:
      goto LABEL_20;
    case 237:
      goto LABEL_24;
    case 239:
      sBtlPlayDeadVoice(wk->scrUnitList[0]);
      goto LABEL_45;
    default:
      if (skillID == 499)
      {
LABEL_24:
        v16 = wk->scrUnitList[2];
LABEL_28:
        v19 = v16->para->devilid;
        sndDeadSePlay_VolAngle(v19, 127, 0.0);
        return;
      }
      if (skillID == 498)
      {
LABEL_20:
        v16 = wk->scrUnitList[1];
        goto LABEL_28;
      }
LABEL_43:
LABEL_45:
      v27 = GetSkillSE(skillID, type);
      if (v27)
      {
        v29 = v27;
        Angle = 0;
        v34.x = x;
        v34.y = y;
        v34.z = z;
        v34.w = w;
        sBtlSEVolAngleCalc(v34, 3000.0, 50.0, 127, 48, (s32 *)&Angle + 1, &Angle);
        sBtlPlaySESub_VolAngle(v29, (s32)(f32)SHIDWORD(Angle), *(f32 *)&Angle);
        return;
      }
      return;
  }
}

// 0x2125110
void sBtlPlayViceSE(SBTLUNIT_WORK *wk, s32 type) {
  s32 devilid;
  u32 v7;
  u32 DevilEnglish;
  u32 v11;

  devilid = wk->para->devilid;
  if (type != 3)
  {
    if (type != 2)
    {
      if (type != 1)
        return;
      v7 = (sBtlGetSpDevilID(devilid) << 16) + 67108877;
      DevilEnglish = sndGetDevilEnglish(v7);
LABEL_28:
      p2sdSndStop(DevilEnglish);
      if (!DevilEnglish)
        return;
      goto LABEL_29;
    }
    v11 = (sBtlGetSpDevilID(devilid) << 16) + 67108878;
    DevilEnglish = sndGetDevilEnglish(v11);
    goto LABEL_28;
  }
  DevilEnglish = sBtlGetViceSE(devilid);
  if (DevilEnglish)
  {
LABEL_29:
    p2sdPlaySE_Vol(DevilEnglish, 127);
  }
}

// 0x21253c0
s32 sBtlLoadBossAtrac3(SBTLUNIT_WORK *wk) {
  SBTLSOUND_DEVILWORK *sewk;
  s32 bossAt3gstat;
  s32 devilid;
  char v6;
  s32 v7;

  sewk = wk->sewk;
  bossAt3gstat = sewk->bossAt3gstat;
  if (bossAt3gstat == 1)
  {
    sewk->bossAt3gstat = 2;
    return 1;
  }
  if (bossAt3gstat)
    return 0;
  devilid = wk->para->devilid;
  if (devilid > 269)
    goto LABEL_7;
  if (devilid != 262)
  {
    if ((devilid & 0xFFFFFFFE) == 0x10C)
    {
LABEL_18:
      v7 = 145;
      goto LABEL_19;
    }
LABEL_16:
    v7 = 0;
    goto LABEL_19;
  }
LABEL_14:
  v7 = 144;
  goto LABEL_19;
LABEL_7:
  v6 = devilid - 29;
  if ((u32)(devilid - 285) > 0x18)
    goto LABEL_16;
  if (((1 << v6) & 0x1C0000B) == 0)
  {
    if (((1 << v6) & 0x180000) != 0)
      goto LABEL_18;
    if (devilid != 300)
      goto LABEL_16;
    goto LABEL_14;
  }
  v7 = 146;
LABEL_19:
  sewk->boss_seid = v7;
  ++wk->sewk->bossAt3gstat;
  return 0;
}

// 0x2120ba0
void sBtlPlayBossAtrac3(SBTLUNIT_WORK *wk) {
  sndSeStop(-1, 0);
  sndSeLoadId(wk->sewk->boss_seid);
  sndSePlay(0);
}

// 0x2125500
s32 sBtlLoadDeadVoice(SBTLUNIT_WORK *wk) {
  sdatUnitWork_t *para;
  SBTLSOUND_DEVILWORK *sewk;

  para = wk->para;
  sewk = wk->sewk;
  sewk->dead_seid = para->devilid;
  return 1;
}

// 0x2120aa0
void sBtlPlayDeadVoice(SBTLUNIT_WORK *wk) {
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  f32 v8;
  s32 v9;
  s32 devilid;
  s64 Angle;
  sdfVector4_t v12;

  Angle = 0;
  x = wk->pos.x;
  y = wk->pos.y;
  z = wk->pos.z;
  w = wk->pos.w;
  v12.x = x;
  v12.y = y;
  v12.z = z;
  v12.w = w;
  sBtlSEVolAngleCalc(v12, 3000.0, 50.0, 127, 48, (s32 *)&Angle + 1, &Angle);
  v8 = *(f32 *)&Angle;
  v9 = HIDWORD(Angle);
  devilid = wk->para->devilid;
  sndDeadSePlay_VolAngle(devilid, v9, v8);
}

// 0x2125080
void sBtlPlayDeadVoice2D(SBTLUNIT_WORK *wk) {
  s32 devilid;

  devilid = wk->para->devilid;
  sndDeadSePlay_VolAngle(devilid, 127, 0.0);
}

// 0x2125520
void Init(void) {
  s64 v3;
  SBATTLE_WORK *wk_local;
  s64 v7;
  SBTLSOUND_SELISTITEM *sBtlSound_SETable_local;
  Il2CppObject *v9;
  s64 j;
  s64 v11;
  SE_DELAY_MSE_t *v14;
  s64 v16;
  s64 i;
  SE_DELAY_MSE_t *gSeDelay_MSE_local;
  Il2CppObject *v20;
  s64 m;
  s64 v22;
  u32 v24;
  SE_DELAY_MSE_t *v25;
  s64 v27;
  s64 k;
  SE_DELAY_MSE_t *gSeDelay_DAMAGE_local;
  Il2CppObject *v31;
  Il2CppObject *v33;
  SE_DELAY_BSE_t *gSeDelay_BSE_SE21_local;
  u32 *v37;
  s32 *v38;
  f32 *v39;
  s64 v40;
  s64 m_Items;
  s64 v42;
  s64 v43;
  s64 v44;
  Il2CppObject *v45;
  SE_DELAY_BSE_t *gSeDelay_BSE_SE73_local;
  u32 *v49;
  s32 *v50;
  f32 *v51;
  s64 v52;
  s64 v53;
  s64 v54;
  s64 v55;
  s64 v56;

  v3 = 32;
  wk_local = wk;
  *(u16 *)&wk_local->fSEDistance = 257;
  wk_local->fSEPan = 0;
  do
  {
    sBtlSound_SETable_local = sBtlSound_SETable;
    if (!*(Il2CppClass **)((char *)&sBtlSound_SETable_local->obj.klass + v3))
    {
      v9 = Allocate(SBTLSOUND_SELISTITEM);
      _ctor(v9, 0);
      *(Il2CppClass **)((char *)&sBtlSound_SETable_local->obj.klass + v3) = v9;
    }
    v7 = *(s64 *)((char *)&sBtlSound_SETable->obj.klass + v3);
    v3 += 8;
    *(u64 *)(v7 + 16) = 0x40FFFFFFFLL;
  }
  while (v3 != 2080);
  if (!gSeDelay_MSE)
  {
    v14 = NewSpecific(SE_DELAY_MSE_t, gSeDelay_MSE_Max);
    gSeDelay_MSE = v14;
    v16 = 0;
    for (i = 32; ; i += 8)
    {
      if (v16 >= gSeDelay_MSE_Max)
        break;
      gSeDelay_MSE_local = gSeDelay_MSE;
      v20 = Allocate(SE_DELAY_MSE_t);
      _ctor(v20, 0);
      *(Il2CppClass **)((char *)&gSeDelay_MSE_local->obj.klass + i) = v20;
      ++v16;
    }
  }
  for (j = 0; ; ++j)
  {
    if (j >= gSeDelay_MSE_Max)
      break;
    v11 = (s64)gSeDelay_MSE + 8 * j;
    *(u32 *)(*(u64 *)(v11 + 32) + 16) = 0;
  }
  if (!gSeDelay_DAMAGE)
  {
    v25 = NewSpecific(SE_DELAY_MSE_t, gSeDelay_DAMAGE_Max);
    gSeDelay_DAMAGE = v25;
    v27 = 0;
    for (k = 32; ; k += 8)
    {
      if (v27 >= gSeDelay_DAMAGE_Max)
        break;
      gSeDelay_DAMAGE_local = gSeDelay_DAMAGE;
      v31 = Allocate(SE_DELAY_MSE_t);
      _ctor(v31, 0);
      *(Il2CppClass **)((char *)&gSeDelay_DAMAGE_local->obj.klass + k) = v31;
      ++v27;
    }
  }
  for (m = 0; ; ++m)
  {
    if (m >= gSeDelay_DAMAGE_Max)
      break;
    v22 = (s64)gSeDelay_DAMAGE + 8 * m;
    *(u32 *)(*(u64 *)(v22 + 32) + 16) = 0;
  }
  if (v24)
  {
    if (!gSeDelay_BSE_SE21)
    {
LABEL_69:
      v33 = Allocate(SE_DELAY_BSE_t);
      _ctor(v33, 0);
      gSeDelay_BSE_SE21 = (SE_DELAY_BSE_t *)v33;
      gSeDelay_BSE_SE21_local = gSeDelay_BSE_SE21;
      gSeDelay_BSE_SE21_local->NowFramePlay = 0;
      *(_OWORD *)&gSeDelay_BSE_SE21_local->Num = xmmword_3CFE060;
      v37 = NewSpecific(uint, 6u);
      gSeDelay_BSE_SE21_local->MidiNo = v37;
      v38 = NewSpecific(s32, gSeDelay_BSE_SE21_local->BufferMax);
      gSeDelay_BSE_SE21_local->Volume = v38;
      v39 = NewSpecific(f32, gSeDelay_BSE_SE21_local->BufferMax);
      gSeDelay_BSE_SE21_local->Angle = v39;
      if (gSeDelay_BSE_SE21_local->BufferMax >= 1)
      {
        v40 = 0;
        m_Items = gSeDelay_BSE_SE21_local->Angle;
        v42 = gSeDelay_BSE_SE21_local->Volume;
        v43 = gSeDelay_BSE_SE21_local->MidiNo;
        do
        {
          v44 = 4 * v40++;
          *(u32 *)(v43 + v44) = 0;
          *(u32 *)(v42 + v44) = 127;
          *(u32 *)(m_Items + v44) = 0;
        }
        while (v40 < gSeDelay_BSE_SE21_local->BufferMax);
      }
    }
  }
  else
  {
    if (!gSeDelay_BSE_SE21)
      goto LABEL_69;
  }
  if (!gSeDelay_BSE_SE73)
  {
    v45 = Allocate(SE_DELAY_BSE_t);
    _ctor(v45, 0);
    gSeDelay_BSE_SE73 = (SE_DELAY_BSE_t *)v45;
    gSeDelay_BSE_SE73_local = gSeDelay_BSE_SE73;
    gSeDelay_BSE_SE73_local->NowFramePlay = 0;
    *(_OWORD *)&gSeDelay_BSE_SE73_local->Num = xmmword_3CFE060;
    v49 = NewSpecific(uint, 6u);
    gSeDelay_BSE_SE73_local->MidiNo = v49;
    v50 = NewSpecific(s32, gSeDelay_BSE_SE73_local->BufferMax);
    gSeDelay_BSE_SE73_local->Volume = v50;
    v51 = NewSpecific(f32, gSeDelay_BSE_SE73_local->BufferMax);
    gSeDelay_BSE_SE73_local->Angle = v51;
    if (gSeDelay_BSE_SE73_local->BufferMax >= 1)
    {
      v52 = 0;
      v53 = gSeDelay_BSE_SE73_local->Angle;
      v54 = gSeDelay_BSE_SE73_local->Volume;
      v55 = gSeDelay_BSE_SE73_local->MidiNo;
      do
      {
        v56 = 4 * v52++;
        *(u32 *)(v55 + v56) = 0;
        *(u32 *)(v54 + v56) = 127;
        *(u32 *)(v53 + v56) = 0;
      }
      while (v52 < gSeDelay_BSE_SE73_local->BufferMax);
    }
  }
}

// 0x2125c70
void sBtlStopSEAll(s32 flag) {
  sndSeStop(-1, 0);
  p2sdSndStopAll();
}

// 0x2125100
void sBtlStopSkillSE(s32 skillID, s32 type) {
  ;
}

// 0x2125d10
void sBtlStopMotionSE(s32 devilID, s32 motionID) {
  u32 DevilSE;

  DevilSE = GetDevilSE(devilID, motionID);
  p2sdSndStop(DevilSE);
}

// 0x2125dd0
void sBtlDrawDebug(void) {
  ;
}
