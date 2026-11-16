#include "types.h"
#include "SBTLUNIT_MARK.h"
#include "SKLID.h"
#include "aw_sbattle.h"
#include "dat.h"
#include "fld.h"
#include "sbtl.h"
#include "sbtlactai.h"
#include "sbtlaction.h"
#include "sbtlai.h"
#include "sbtlcalc.h"
#include "sbtlcommand.h"
#include "sbtldmg.h"
#include "sbtleff.h"
#include "sbtlencount.h"
#include "sbtlmain.h"
#include "sbtlplayer.h"
#include "sbtlscene.h"
#include "sbtlscript.h"
#include "sbtlskill.h"
#include "sbtlsub.h"
#include "sbtlunit.h"
#include "sbtlvisual.h"
#include "scr.h"
#include "sdf_vu0.h"
#include "sdfmodel.h"
#include "sdfquat.h"

#define WARP_FADE_VALUE 4
#define WARP_WAIT_VALUE 15
#define BLOCKER_R 140
#define TABLE_POS 0
#define MATO_R 300
#define MATO_R2 100
#define MATO_SHUFFLE_FRAME0 150
#define MAOT_SHUFFLE_FRAME0_F 90
#define MATO_SHUFFLE_FRAME1 15
#define MATO_SHUFFLE_FRAME2 10
#define MATO_KAITEN_FRAME 900
#define HITO_R 200
#define HITO_FRAME 120

typedef struct EFFPDATA_WORK EFFPDATA_WORK;
typedef struct SBTLUNIT_WORK SBTLUNIT_WORK;
typedef struct SB_ENCOUNTPAC SB_ENCOUNTPAC;
typedef struct sdfModelNode_t sdfModelNode_t;
typedef struct strDat strDat;

struct strDat {
    s32 Group;
    u32 DevilID;
};

f32 sbtlscpt_jumpacc;

static SBTLUNIT_WORK *GetData(void);
static s32 Support_RunWarpProcess(void);
static s32 Support_RunWarpProcess_Skip(SBTLUNIT_WORK *wk);
static s32 Support_RunDownProcess(void);
static SBTLUNIT_WORK *Support_GetNakamaData(s32 idx);
static SBTLUNIT_WORK *Support_GetUserData(void);
static void Support_SetAisyo(s32 listID, s32 aisyoID);
static void Support_MovePos(SBTLUNIT_WORK *wk, const sdfVector4_t *pos);
static s32 CheckLoadData(void);
static void Support_RunZoomProcess(void);
static s32 Support_RunWaitProcess(void);
static void Support_MovePos2(SBTLUNIT_WORK *wk, const sdfVector4_t *pos, f32 frame, s32 motion_no);
static s32 btlBoss_CERBER_ModelNodeFadeOut(SBTLUNIT_WORK *wk, char *pName);

// 0x2118af0
static SBTLUNIT_WORK *GetData(void) {
  return wk->scrunit;
}

// 0x2118b80
static s32 Support_RunWarpProcess(void) {
  SBTLUNIT_LISTWORK *UnitMng;
  s32 playerID;
  SBTLUNIT_WORK *v5;
  SBATTLE_WORK *v7;
  SBTLUNIT_WORK *scrunit;
  SBTLAI_WORK *aiwk;
  s32 vstatus;
  u32 scrflag;
  s32 v12;
  sdfVector4_t *p_pos;
  SBTLACTAI_WORK *actaiwk;
  struct sdfVector4_t scrRot;
  sdfVector4_t *p_rot;
  u32 v20;
  bool v21;
  s64 v22;
  f32 x;
  f32 y;
  f32 w;
  f32 z;
  long f64 v28;
  s32 v29;
  u32 *p_flg;
  SBTLAI_WORK *v31;
  s32 scrcnt;
  f32 *v33;
  f32 v34;
  f32 v35;
  f32 v36;
  f32 v37;
  long f64 v38;
  SBTLAI_WORK *v39;
  u32 v40;
  f32 v41;
  f32 v42;
  f32 v43;
  f32 v44;
  long f64 v45;
  s64 v46;
  long f64 v47;
  f32 v48;
  long f64 v49;
  f32 v50;
  f32 v51;
  s32 wrap_after_dir;
  long f64 v53;
  s32 scrSkillID;
  s32 motionno;
  struct sdfVector4_t scrPos;
  s64 v60;
  s64 v61;

  v60 = 0;
  v61 = 0;
  UnitMng = wk->UnitMng;
  playerID = wk->playerID;
  v5 = sBtlSearchUnit_ID(UnitMng, playerID);
  v7 = wk;
  scrunit = v7->scrunit;
  aiwk = scrunit->aiwk;
  vstatus = scrunit->vstatus;
  scrflag = aiwk->scrflag;
  aiwk->scr_actcheckflg = 1;
  if ((scrflag & 8) == 0)
    return 0;
  if ((vstatus & 1) != 0)
  {
LABEL_35:
    v12 = 1;
    scrSetIntReturnValue(1);
    scrunit->aiwk->scr_actcheckflg = 1;
    return v12;
  }
  if ((vstatus & 2) != 0)
  {
    ++aiwk->scrcnt;
    goto LABEL_35;
  }
  if ((scrflag & 4) != 0)
  {
    aiwk->scrflag = scrflag & 0xFFFFFFF3;
    scrunit->status &= ~1u;
    v20 = (u16)scrunit->para->devilid - 268;
    v21 = v20 > 0x25;
    v22 = (1 << v20) & 0x3000000003LL;
    if (v21 || v22 == 0)
      goto LABEL_93;
    v7 = wk;
    if (v7->scrStep != 3)
    {
LABEL_93:
      sBtlStatusBitOff(scrunit, 0xFFFFBFFF);
      p_flg = &scrunit->flg;
      v29 = -3;
    }
    else
    {
      if ((scrunit->aiwk->scrflag & 0x1000) == 0)
        goto LABEL_54;
      scrunit->status |= 0x80000u;
      x = scrunit->pos.x;
      y = scrunit->pos.y;
      z = scrunit->pos.z;
      w = scrunit->pos.w;
      *(__n128 *)&v28 = sub_1B332C0(0, x, y, z, w);
      sub_1B335A0(&scrunit->koteipos, 0, v28);
      v29 = -4097;
      p_flg = &scrunit->aiwk->scrflag;
    }
    *p_flg &= v29;
LABEL_54:
    scrunit->aisyoid = scrunit->para->devilid;
    if ((scrflag & 2) != 0)
      goto LABEL_55;
    return 0;
  }
  if ((scrflag & 1) != 0)
  {
    scrflag = scrflag & 0xFFFFFFFC | 2;
    aiwk->scrflag = scrflag;
    *(u64 *)&aiwk->scrcnt = 0xF00000000LL;
    scrPos = scrunit->actaiwk->scrPos;
    vct_A = scrPos;
    p_pos = &scrunit->pos;
    actaiwk = scrunit->actaiwk;
    *p_pos = vct_A;
    scrRot = actaiwk->scrRot;
    vct_A = scrRot;
    p_rot = &scrunit->rot;
    *p_rot = vct_A;
  }
  if ((scrflag & 2) == 0)
    return 0;
LABEL_55:
  v31 = scrunit->aiwk;
  scrcnt = v31->scrcnt;
  if (scrcnt < v31->cmpscrcnt)
  {
    v31->scrcnt = scrcnt + 1;
    v33 = scrunit->actaiwk;
    v34 = v33[25];
    v35 = v33[26];
    v37 = v33[27];
    v36 = v33[28];
    sub_1B332C0(0, v34, v35, v37, v36);
    sub_1B33360(0, scrunit->actaiwk->scrPos2.x, scrunit->actaiwk->scrPos2.y, scrunit->actaiwk->scrPos2.z, scrunit->actaiwk->scrPos2.w);
    sub_1B33400(0);
    sub_1B33480(0, (f32)scrunit->aiwk->scrcnt / (f32)scrunit->aiwk->cmpscrcnt);
    sub_1B33360(0, scrunit->actaiwk->scrPos2.x, scrunit->actaiwk->scrPos2.y, scrunit->actaiwk->scrPos2.z, scrunit->actaiwk->scrPos2.w);
    *(__n128 *)&v38 = sub_1B33520(0);
    sub_1B335A0(&scrunit->pos, 0, v38);
    v39 = scrunit->aiwk;
    goto LABEL_77;
  }
  v40 = v31->scrflag;
  if ((v40 & 0x200000) != 0)
  {
    v42 = scrunit->pos.x;
    v41 = scrunit->pos.y;
    if (v42 != v5->pos.x || v41 != v5->pos.y || scrunit->pos.z != v5->pos.z)
    {
      v44 = scrunit->pos.z;
      v43 = scrunit->pos.w;
      sub_1B332C0(0, v42, v41, v44, v43);
      sub_1B33360(0, v5->pos.x, v5->pos.y, v5->pos.z, v5->pos.w);
      sub_1B33400(0);
      sub_1B335A0(&v60, 0, v45);
      v47 = sub_18E6660(0, v46);
      v48 = *(f32 *)&v47;
      FromEuler(0.0, *(f32 *)&v47, 0.0);
      sub_1B335A0(&scrunit->rot, 0, v49);
      v50 = scrunit->rot.z;
      v51 = scrunit->rot.w;
      scrunit->mv_rotbk = v48 * 57.29578;
      sub_1B332C0(0, scrunit->rot.x, scrunit->rot.y, v50, v51);
      v31 = scrunit->aiwk;
      v40 = v31->scrflag;
    }
    v31->scrflag = v40 & 0xFFDFFFFF;
  }
  wrap_after_dir = v31->wrap_after_dir;
  if (wrap_after_dir != -1)
  {
    FromEuler(0.0, (f32)wrap_after_dir * 0.017453292, 0.0);
    sub_1B335A0(&scrunit->rot, 0, v53);
    scrunit->mv_rotbk = (f32)scrunit->aiwk->wrap_after_dir;
  }
  sBtlSetFade(scrunit, 1, 0, 0, 4);
  scrSkillID = scrunit->aiwk->scrSkillID;
  if (scrSkillID == -1)
  {
    motionno = 11;
    goto LABEL_76;
  }
  sBtlSetSkill_EffectData(scrunit, scrSkillID, 0);
  motionno = sBtlGetSklVisualTbl(scrunit->aiwk->scrSkillID)->motionno;
LABEL_76:
  sBtlSetMotion(scrunit, motionno, 0, 0, 0);
  v39 = scrunit->aiwk;
  v39->scrflag = v39->scrflag & 0xFFFFFFF9 | 4;
LABEL_77:
  v39->scr_actcheckflg = 1;
  v12 = 1;
  scrSetIntReturnValue(1);
  return v12;
}

// 0x21193f0
static s32 Support_RunWarpProcess_Skip(SBTLUNIT_WORK *wk) {
  SBATTLE_WORK *v4;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 playerID;
  SBTLUNIT_WORK *v7;
  s64 v8;
  SBTLAI_WORK *aiwk;
  u32 scrflag;
  f32 *v11;
  sdfVector4_t *p_pos;
  SBTLACTAI_WORK *actaiwk;
  struct sdfVector4_t scrRot;
  sdfVector4_t *p_rot;
  SBTLAI_WORK *v17;
  struct sdfVector4_t v18;
  struct sdfVector4_t scrPos2;
  SBTLAI_WORK *v20;
  f32 cmpscrcnt;
  f32 scrcnt;
  f32 v23;
  struct sdfVector4_t v24;
  SBTLAI_WORK *v25;
  u32 v26;
  s32 wrap_after_dir;
  u32 status;
  u32 v30;
  struct sdfVector4_t pos;
  sdfVector4_t *p_koteipos;
  s32 v35;
  u32 *p_scrflag;
  f32 y;
  f32 x;
  s64 v39;
  struct sdfVector4_t v42;
  long f64 v43;
  f32 v44;
  s32 v46;
  struct sdfVector4_t rot;
  SBTLAI_WORK *v49;
  s32 vstatus;
  struct sdfVector4_t scrPos;
  struct sdfVector4_t v59;
  struct sdfVector4_t v63;
  struct sdfVector4_t v66;

  v4 = wk;
  UnitMng = v4->UnitMng;
  playerID = v4->playerID;
  v7 = sBtlSearchUnit_ID(UnitMng, playerID);
  aiwk = wk->aiwk;
  aiwk->scr_actcheckflg = 1;
  scrflag = aiwk->scrflag;
  if ((scrflag & 8) != 0)
  {
    v11 = v7;
    aiwk->scrflag = scrflag & 0xFFFFFFFC | 2;
    *(u64 *)&aiwk->scrcnt = 0xF0000000FLL;
    scrPos = wk->actaiwk->scrPos;
    vct_A = scrPos;
    p_pos = &wk->pos;
    actaiwk = wk->actaiwk;
    *p_pos = vct_A;
    scrRot = actaiwk->scrRot;
    vct_A = scrRot;
    p_rot = &wk->rot;
    v17 = wk->aiwk;
    *p_rot = vct_A;
    ++v17->scrcnt;
    v18 = wk->actaiwk->scrPos;
    vct_A = v18;
    scrPos2 = wk->actaiwk->scrPos2;
    vct_B = scrPos2;
    vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    v20 = wk->aiwk;
    cmpscrcnt = v20->cmpscrcnt;
    scrcnt = v20->scrcnt;
    v23 = scrcnt / cmpscrcnt;
    vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v23);
    v24 = wk->actaiwk->scrPos2;
    vct_B = v24;
    vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    v25 = wk->aiwk;
    *p_pos = vct_A;
    v26 = v25->scrflag;
    if ((v26 & 0x200000) == 0)
    {
      wrap_after_dir = v25->wrap_after_dir;
      if (wrap_after_dir == -1)
        goto LABEL_51;
      goto LABEL_93;
    }
    x = wk->pos.x;
    y = wk->pos.y;
    if (x == v11[41] && y == v11[42] && wk->pos.z == v11[43])
    {
LABEL_92:
      v25->scrflag = v26 & 0xFFDFFFFF;
      wrap_after_dir = v25->wrap_after_dir;
      if (wrap_after_dir == -1)
      {
LABEL_51:
LABEL_52:
        sBtlSetFade(wk, 1, 0, 0, 256);
        sBtlSetMotion(wk, 0, 0, 0, 0);
        status = wk->status;
        wk->aiwk->scrflag &= 0xFFFFFFF1;
        wk->status = status & 0xFFFFFFFE;
        v30 = (u16)wk->para->devilid - 268;
        if (v30 <= 0x25 && ((1 << v30) & 0x3000000003LL) != 0)
        {
          if (wk->scrStep == 3)
          {
            if ((wk->aiwk->scrflag & 0x1000) == 0)
            {
LABEL_103:
              vstatus = wk->vstatus;
              wk->aisyoid = wk->para->devilid;
              wk->vstatus = vstatus & 0xFFFFFBFC;
              HIBYTE(wk->color) = 0x80;
              return 0;
            }
            pos = wk->pos;
            wk->status |= 0x80000u;
            v59 = pos;
            vct_A = v59;
            p_koteipos = &wk->koteipos;
            v35 = -4097;
            p_scrflag = &wk->aiwk->scrflag;
            *p_koteipos = vct_A;
LABEL_102:
            *p_scrflag &= v35;
            goto LABEL_103;
          }
        }
        sBtlStatusBitOff(wk, 0xFFFFBFFF);
        p_scrflag = &wk->flg;
        v35 = -3;
        goto LABEL_102;
      }
LABEL_93:
      FromEuler(0.0, (f32)wrap_after_dir * 0.017453292, 0.0);
      v49 = wk->aiwk;
      *p_rot = vct_A;
      wk->mv_rotbk = (f32)v49->wrap_after_dir;
      goto LABEL_52;
    }
    v39 = *(u64 *)&wk->pos.z;
    vct_A.x = x;
    vct_A.y = y;
    *(u64 *)&vct_A.z = v39;
    v42 = *(sdfVector4_t *)(v11 + 41);
    vct_B = v42;
    vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    v43 = sub_18E6660(0, v8);
    v44 = *(f32 *)&v43;
    FromEuler(0.0, *(f32 *)&v43, 0.0);
    *p_rot = vct_A;
    v46 = (u8)byte_5755EF5;
    wk->mv_rotbk = v44 * 57.29578;
    rot = wk->rot;
    if (v46)
    {
LABEL_91:
      vct_A = rot;
      v25 = wk->aiwk;
      v26 = v25->scrflag;
      goto LABEL_92;
    }
    else
    {
      v66 = wk->rot;
      rot = v66;
      goto LABEL_91;
    }
    v63 = rot;
    rot = v63;
    goto LABEL_91;
  }
  return 0;
}

// 0x2119f10
static s32 Support_RunDownProcess(void) {
  SBTLUNIT_WORK *scrunit;
  SBTLAI_WORK *aiwk;
  u32 scrflag;
  s32 scrcnt;

  scrunit = wk->scrunit;
  aiwk = scrunit->aiwk;
  scrflag = aiwk->scrflag;
  if ((scrflag & 0x10) == 0)
    return 0;
  if ((scrflag & 0x60) != 0)
  {
    if ((scrflag & 0x20) != 0)
    {
      if (!sBtlCheckMotionEnd(scrunit))
        return 1;
      *(u64 *)&scrunit->aiwk->scrflag = scrunit->aiwk->scrflag & 0xFFFFFF9F | 0x40;
      sBtlSetMotion(scrunit, 2, 4, 0, 0);
      return 1;
    }
    else
    {
      scrcnt = aiwk->scrcnt;
      if (scrcnt < aiwk->cmpscrcnt)
      {
        aiwk->scrcnt = scrcnt + 1;
        return 1;
      }
      aiwk->cmpscrcnt = 0;
      *(u64 *)&aiwk->scrflag = scrflag & 0xFFFFFFAF;
      ResetAction(scrunit, 1, 0);
      sBtlSetAIWkStat(scrunit, 1);
      sBtlSetAction(scrunit, 0, 0);
      return 2;
    }
  }
  else
  {
    if (!sBtlCheckMotionNo(scrunit, 14))
      return 1;
    scrunit->aiwk->scrflag |= 0x20u;
    return 1;
  }
}

// 0x211a180
static SBTLUNIT_WORK *Support_GetNakamaData(s32 idx) {
  s8 v2;
  SBTLUNIT_WORK *Nakama;
  SBTLUNIT_WORK *v5;

  v2 = idx;
  if (wk->member_num < 1)
    return 0;
  Nakama = sBtlGetNakama(v2);
  if (Nakama)
  {
    v5 = Nakama;
    if (sBtlCheckDamageTarget(Nakama))
      return v5;
  }
  return 0;
}

// 0x2119350
static SBTLUNIT_WORK *Support_GetUserData(void) {
  SBTLUNIT_LISTWORK *UnitMng;
  s32 playerID;

  UnitMng = wk->UnitMng;
  playerID = wk->playerID;
  return sBtlSearchUnit_ID(UnitMng, playerID);
}

// 0x211a290
static void Support_SetAisyo(s32 listID, s32 aisyoID) {
  SBTLUNIT_WORK *scrunit;
  __int128 v8;
  s32 *v9;
  s32 v10;
  s16 v11;
  DEVILDATA_WORK *v12;
  s32 v13;
  SBTLAISYO_DATAWORK *v14;
  s32 devilid;
  s16 v16;
  DEVILDATA_WORK *DevilData;
  s32 aishou;
  SBTLAISYO_DATAWORK *Aisyotbl;
  s32 *para;
  unsigned __int128 v21;
  unsigned __int128 v22;

  if (listID != -1)
  {
    scrunit = wk->scrUnitList[listID];
    if (!scrunit)
      return;
LABEL_13:
    if (aisyoID)
    {
      if (aisyoID == 2)
      {
        devilid = scrunit->para->devilid;
        v16 = scrunit->para->devilid;
        DevilData = sBtlGetDevilData(devilid, -1);
        scrunit->aisyoid = v16;
        aishou = DevilData->aishou;
        Aisyotbl = sBtlGetAisyotbl(aishou);
        ClassCopy(scrunit->para->aisyo, Aisyotbl, 0);
        para = scrunit->para->aisyo->para;
        v21 = *(_OWORD *)&para[4] | __PAIR128__(0x800000008000LL, 0x800000008000LL);
        *(_OWORD *)para |= __PAIR128__(0x800000008000LL, 0x800000008000LL);
        *(_OWORD *)&para[4] = v21;
        v22 = *(_OWORD *)&para[12] | __PAIR128__(0x800000008000LL, 0x800000008000LL);
        *(_OWORD *)&para[8] |= __PAIR128__(0x800000008000LL, 0x800000008000LL);
        *(_OWORD *)&para[12] = v22;
      }
      else if (aisyoID == 1)
      {
        *(u64 *)&v8 = 0x100000001000LL;
        *((u64 *)&v8 + 1) = 0x100000001000LL;
        v9 = scrunit->para->aisyo->para;
        *(_OWORD *)v9 = v8;
        *(_OWORD *)&v9[4] = v8;
        *(_OWORD *)&v9[8] = v8;
        *(_OWORD *)&v9[12] = v8;
      }
    }
    else
    {
      v10 = scrunit->para->devilid;
      v11 = scrunit->para->devilid;
      v12 = sBtlGetDevilData(v10, -1);
      scrunit->aisyoid = v11;
      v13 = v12->aishou;
      v14 = sBtlGetAisyotbl(v13);
      ClassCopy(scrunit->para->aisyo, v14, 0);
    }
    return;
  }
  scrunit = wk->scrunit;
  if (scrunit)
    goto LABEL_13;
}

// 0x211a4e0
void sBtlSupport_StopAction(SBTLUNIT_WORK *wk) {
  SBTLDMG_HITLISTWORK *hitList;
  SBTLEFF_LISTWORK *effList;

  if (wk->mode >= 5 && (wk->status & 0x800) == 0)
  {
    hitList = wk->hitList;
    sBtlClearHitC(hitList, wk);
    effList = wk->effList;
    sBtlForceReset(effList, wk);
    sBtlResetAAI(wk);
    wk->actaiwk->dataflg = 0;
    sBtlResetAction_Flag(wk);
    if (wk->ListID == wk->playerID)
    {
      sBtlResetAction(wk);
    }
    else
    {
      sBtlResetMode(wk);
      wk->aiwk->mode = 0;
      ResetAction(wk, 0, 0);
    }
  }
}

// 0x211a700
static void Support_MovePos(SBTLUNIT_WORK *wk, const sdfVector4_t *pos) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  SBTLACTAI_WORK *actaiwk;
  sdfVector4_t *p_mv_spdbk;
  s32 v12;
  f32 *p_x;
  SBTLACTAI_WORK *v14;
  sdfVector4_t *p_ppos;
  struct sdfVector4_t v16;
  f32 *v17;
  f32 v18;
  f32 v19;
  f32 v20;
  SBTLACTAI_WORK *v21;
  f32 v23;
  s32 v24;
  s32 v25;
  struct sdfVector4_t max_mvspd;

  w = pos->w;
  z = pos->z;
  y = pos->y;
  x = pos->x;
  actaiwk = wk->actaiwk;
  actaiwk->status = actaiwk->status & 0xFFFFFDE0 | 0x14;
  actaiwk->mode = 2;
  max_mvspd = wk->max_mvspd;
  vct_A = max_mvspd;
  p_mv_spdbk = &wk->mv_spdbk;
  v12 = (u8)byte_5755EF5;
  *p_mv_spdbk = vct_A;
  if (v12)
    goto LABEL_9;
  goto LABEL_33;
  if (v25)
  {
LABEL_9:
    goto LABEL_10;
  }
LABEL_33:
LABEL_10:
  p_x = &vf00.x;
  p_x[4] = x;
  p_x[5] = y;
  p_x[6] = z;
  p_x[7] = w;
  v14 = wk->actaiwk;
  p_ppos = &v14->ppos;
  *p_ppos = vct_A;
  v16 = wk->pos;
  vct_B = v16;
  vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  v17 = &vf00.x;
  v18 = v17[6];
  v19 = v17[4];
  v20 = v17[5];
  v21 = wk->actaiwk;
  v21->frame = 0;
  v23 = sqrtf((f32)((f32)(v19 * v19) + (f32)(v20 * v20)) + (f32)(v18 * v18)) / wk->mv_spdbk.z;
  v24 = v23;
  if (v23 == INFINITY)
    v24 = 0x80000000;
  v21->cmpframe = v24;
  sBtlSetMotion(wk, 5, 4, 0, 0);
  sBtlSetAction(wk, 2, 0);
  wk->actaiwk->stat = 2;
  wk->aiwk->stat = 2;
}

// 0x211ab50
void sBtlSupport_BattleStop(s32 motionFlag, s32 effectFlag, s32 SEFlag) {
  s64 i;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  u32 uniq_code;
  s32 devilid;
  s32 StockDevilIndex;
  u32 status;
  u32 v16;
  u32 v17;
  s32 side;
  SBTLACTION_WORK *actwk;
  s32 flg;
  u32 v22;
  s64 v24;
  SBTLUNIT_LISTWORK *v25;
  SBTLUNIT_WORK *v26;
  u32 v28;
  u32 v29;
  s32 ListID;
  s64 v33;
  SBTLUNIT_LISTWORK *v34;
  SBTLUNIT_WORK *v35;
  u32 v37;
  u32 v38;
  s32 v41;
  s64 v42;
  SBTLUNIT_LISTWORK *v43;
  SBTLUNIT_WORK *v44;
  u32 v45;
  s32 v46;
  s32 v47;
  u32 v48;
  u32 v50;
  u32 v51;
  SBTLDMG_HITLISTWORK *hitList;

  StopBattle();
  wk->scrFlag |= 1u;
  switch (motionFlag)
  {
    case 1:
      for (i = 0; ; ++i)
      {
        UnitMng = wk->UnitMng;
        if (i >= UnitMng->number)
          goto LABEL_195;
        pUnit = UnitMng->pUnitL[i]->pUnit;
        if (!pUnit)
          goto LABEL_9;
        uniq_code = pUnit->uniq_code;
        devilid = pUnit->para->devilid;
        StockDevilIndex = datGetStockDevilIndex(devilid, uniq_code);
        status = pUnit->actwk->status;
        if (status != 10 && status != 34 && (pUnit->side & 0x80) != 0)
          goto LABEL_9;
        if ((pUnit->side & 0x18) == 0 && (pUnit->status & 0x10) == 0)
        {
          if (!sBtlCheckReturn_Unit(pUnit))
          {
            v16 = pUnit->actwk->status;
            if (v16 != 10 && (pUnit->status & 0x800) == 0 && pUnit->mode >= 5 && v16 != 34 && v16 != 40)
            {
              side = pUnit->side;
              if ((side & 0x81) != 1)
                goto LABEL_47;
              if (wk->summonflg[StockDevilIndex] == 2)
              {
                side = pUnit->side;
LABEL_47:
                if ((side & 1) != 0)
                {
                  actwk = pUnit->actwk;
                  if (actwk->status == 57)
                  {
                    if (actwk->framecnt <= 24)
                    {
                      sBtlSetFade(pUnit, 1, 0, 0, 32);
                    }
                    flg = pUnit->flg;
                    pUnit->asimoto_mode = 0;
                    v22 = pUnit->status;
                    pUnit->flg = flg & 0xFFFFFFFD;
                    pUnit->status = v22 & 0xFFFFFFDE;
                  }
                }
                sBtlSupport_StopAction(pUnit);
                sBtlSetAction(pUnit, 1, 0);
                pUnit->vstatus |= 0x2000000u;
                pUnit->actaiwk->scrMotion = 0;
                sBtlSetMotion(pUnit, 0, 4, 0, 0);
                pUnit->vstatus &= ~0x800u;
                goto LABEL_9;
              }
            }
          }
        }
        if (sBtlCheckReturn_Unit(pUnit))
          goto LABEL_6;
        v17 = pUnit->actwk->status;
        if ((pUnit->side & 1) != 0 && v17 == 40 || v17 == 34 || v17 == 10)
        {
LABEL_6:
          sBtlStatusBitOn(pUnit, 0x10u);
        }
LABEL_9:
      }
    case 2:
      v24 = 0;
      while (2)
      {
        v25 = wk->UnitMng;
        if (v24 >= v25->number)
          goto LABEL_195;
        v26 = v25->pUnitL[v24]->pUnit;
        if (!v26)
          goto LABEL_66;
        goto LABEL_9001;
        if (!v26)
        {
LABEL_66:
          ++v24;
          continue;
        }
LABEL_9001:
        break;
      }
      if ((v26->side & 0x18) != 0 || (v26->status & 0x10) != 0)
        goto LABEL_84;
      if (sBtlCheckReturn_Unit(v26))
        goto LABEL_84;
      if ((v26->status & 0x800) == 0 && v26->mode >= 5)
      {
        v28 = v26->actwk->status;
        if (v28 != 34 && v28 != 40)
        {
          if ((v26->side & 0x81) != 1)
            goto LABEL_96;
          if (wk->summonflg[wk->summonindex[0]] == 2)
          {
LABEL_96:
            sBtlSupport_StopAction(v26);
            sBtlSetAction(v26, 1, 0);
            ListID = v26->ListID;
            v26->vstatus |= 0x2000000u;
            if (ListID == wk->playerID)
            {
              sBtlSetMotion(v26, 14, 4, 0, 0);
              v26->actaiwk->scrMotion = 2;
              sBtlSetAction(v26, 42, 0);
            }
            else
            {
              v26->actaiwk->scrMotion = 0;
              sBtlSetMotion(v26, 0, 4, 0, 0);
            }
            goto LABEL_66;
          }
        }
      }
LABEL_84:
      if (!sBtlCheckReturn_Unit(v26))
      {
        v29 = v26->actwk->status;
        if (((v26->side & 1) == 0 || v29 != 40) && v29 != 10)
          goto LABEL_66;
      }
      sBtlStatusBitOn(v26, 0x10u);
      goto LABEL_66;
    case 3:
      v33 = 0;
      while (2)
      {
        v34 = wk->UnitMng;
        if (v33 >= v34->number)
          goto LABEL_195;
        v35 = v34->pUnitL[v33]->pUnit;
        if (!v35)
          goto LABEL_113;
        goto LABEL_9002;
        if (!v35)
        {
LABEL_113:
          ++v33;
          continue;
        }
LABEL_9002:
        break;
      }
      if ((v35->side & 0x18) != 0 || (v35->status & 0x10) != 0)
        goto LABEL_131;
      if (sBtlCheckReturn_Unit(v35))
        goto LABEL_131;
      if ((v35->status & 0x800) == 0 && v35->mode >= 5)
      {
        v37 = v35->actwk->status;
        if (v37 != 34 && v37 != 40)
        {
          if ((v35->side & 0x81) != 1)
            goto LABEL_144;
          if (wk->summonflg[wk->summonindex[0]] == 2)
          {
LABEL_144:
            sBtlSupport_StopAction(v35);
            sBtlSetAction(v35, 1, 0);
            v41 = v35->ListID;
            v35->vstatus |= 0x2000000u;
            v35->actaiwk->scrMotion = 0;
            if (v41 == wk->scrEventUnit->ListID)
            {
              sBtlSetMotion(v35, 1, 0, 0, 0);
            }
            v35->vstatus &= ~0x800u;
            goto LABEL_113;
          }
        }
      }
LABEL_131:
      if (!sBtlCheckReturn_Unit(v35))
      {
        v38 = v35->actwk->status;
        if (((v35->side & 1) == 0 || v38 != 40) && v38 != 34 && v38 != 10)
          goto LABEL_113;
      }
      sBtlStatusBitOn(v35, 0x10u);
      goto LABEL_113;
    case 4:
      v42 = 0;
      while (2)
      {
        v43 = wk->UnitMng;
        if (v42 < v43->number)
        {
          v44 = v43->pUnitL[v42]->pUnit;
          if (!v44)
            goto LABEL_157;
          v45 = v44->uniq_code;
          v46 = v44->para->devilid;
          v47 = datGetStockDevilIndex(v46, v45);
          v48 = v44->actwk->status;
          if (v48 != 10 && v48 != 34 && (v44->side & 0x80) != 0)
            goto LABEL_157;
          if ((v44->side & 0x18) != 0 || (v44->status & 0x10) != 0)
            goto LABEL_181;
          if (sBtlCheckReturn_Unit(v44))
            goto LABEL_181;
          v50 = v44->actwk->status;
          if (v50 == 10 || (v44->status & 0x800) != 0 || v44->mode < 5 || v50 == 34 || v50 == 40)
            goto LABEL_181;
          if ((v44->side & 0x81) == 1)
          {
            if (wk->summonflg[v47] != 2)
            {
LABEL_181:
              if (!sBtlCheckReturn_Unit(v44))
              {
                v51 = v44->actwk->status;
                if (((v44->side & 1) == 0 || v51 != 40) && v51 != 34 && v51 != 10)
                  goto LABEL_157;
              }
              sBtlStatusBitOn(v44, 0x10u);
              goto LABEL_157;
            }
          }
          sBtlSupport_StopAction(v44);
          v44->vstatus = v44->vstatus & 0xFDFFF7FF | 0x2000000;
LABEL_157:
          ++v42;
          continue;
        }
        break;
      }
LABEL_195:
      if (effectFlag != 1)
      {
        if (!effectFlag)
        {
          StopBattle();
          sBtlSetNSTOP();
          StopBattle_StopUV();
        }
        return;
      }
      sBtlForceDeleteAll(0);
      hitList = wk->hitList;
      sBtlReleaseHitC_List(hitList, 1u);
      wk->scrFlag |= 0x40000u;
      DeleteAll_Event();
      sBtlDeleteEffList(wk->effList);
      return;
    default:
      goto LABEL_195;
  }
}

// 0x211b8d0
static s32 CheckLoadData(void) {
  s32 mode;
  s64 i;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;

  mode = wk->mode;
  if (mode == 6)
    return 1;
  if (mode == 13)
    return 1;
  for (i = 0; ; ++i)
  {
    UnitMng = wk->UnitMng;
    if (i >= UnitMng->number)
      break;
    pUnit = UnitMng->pUnitL[i]->pUnit;
    if (!pUnit)
      continue;
    if ((u32)(pUnit->mode - 1) <= 1)
    {
      if (!sBtlSearchReturn_Unit(pUnit))
        return 1;
    }
  }
  return 0;
}

// 0x211ba80
bool sBtlCreateAIScript(void) {
  SBATTLE_WORK *wk_local;
  scrHandle_t *v6;

  wk_local = wk;
  v6 = scrRegistScript2(ai_scr);
  wk_local->hAIScript = v6;
  return 1;
}

// 0x211bb60
void sBtlAllInit(void) {
  SBATTLE_WORK *wk_local;
  s32 encountno;
  s32 *scrCnt;
  SBTLUNIT_WORK *scrUnitList;
  SBTLUNIT_WORK *v10;
  SBTLUNIT_WORK *v12;
  SBTLUNIT_WORK *v14;
  SBTLUNIT_WORK *v16;
  SBTLUNIT_WORK *v18;
  SBTLUNIT_WORK *v20;
  SBTLUNIT_WORK *v22;
  SBTLUNIT_WORK *v24;
  SBTLUNIT_WORK *v26;
  SBTLUNIT_WORK *v28;
  SBTLUNIT_WORK *v30;
  SBTLUNIT_WORK *v32;
  SBTLUNIT_WORK *v34;
  SBTLUNIT_WORK *v36;
  SBTLUNIT_WORK *v38;
  SBATTLE_WORK *v40;
  s32 *scrData;
  s32 *scrWarp;
  s32 v43;
  s32 *EventBit;

  wk_local = wk;
  encountno = wk_local->encountno;
  wk_local->scrStep = 0;
  *(u64 *)&wk_local->scrLoadStat = 0;
  wk_local->scrEncountNo = encountno;
  scrCnt = wk_local->scrCnt;
  scrCnt[0] = 0;
  scrCnt[1] = 0;
  scrCnt[2] = 0;
  scrCnt[3] = 0;
  wk_local->scrCmpCnt = 0x7FFFFFFF;
  scrUnitList = wk_local->scrUnitList;
  scrUnitList[0] = 0;
  v10 = wk->scrUnitList;
  v10[1] = 0;
  v12 = wk->scrUnitList;
  v12[2] = 0;
  v14 = wk->scrUnitList;
  v14[3] = 0;
  v16 = wk->scrUnitList;
  v16[4] = 0;
  v18 = wk->scrUnitList;
  v18[5] = 0;
  v20 = wk->scrUnitList;
  v20[6] = 0;
  v22 = wk->scrUnitList;
  v22[7] = 0;
  v24 = wk->scrUnitList;
  v24[8] = 0;
  v26 = wk->scrUnitList;
  v26[9] = 0;
  v28 = wk->scrUnitList;
  v28[10] = 0;
  v30 = wk->scrUnitList;
  v30[11] = 0;
  v32 = wk->scrUnitList;
  v32[12] = 0;
  v34 = wk->scrUnitList;
  v34[13] = 0;
  v36 = wk->scrUnitList;
  v36[14] = 0;
  v38 = wk->scrUnitList;
  v38[15] = 0;
  v40 = wk;
  scrData = v40->scrData;
  scrData[0] = 0;
  scrData[1] = 0;
  scrData[2] = 0;
  scrData[3] = 0;
  scrData[4] = 0;
  scrData[5] = 0;
  scrData[6] = 0;
  scrData[7] = 0;
  scrWarp = v40->scrWarp;
  scrWarp[0] = -1;
  scrWarp[1] = -1;
  scrWarp[2] = -1;
  scrWarp[3] = 0;
  v43 = (u8)byte_5755E7B;
  v40->geirinstep = 0;
  v40->geirincnt = 0;
  v40->EscOdds = 0;
  v40->scrFlag = 0;
  if (!v43)
  {
    goto LABEL_63;
  }
LABEL_63:
  EventBit = GBWK->EventBit;
  EventBit[69] &= ~0x80000000;
}

// 0x211c210
void Init(SBTLUNIT_WORK *pUnit) {
  SBTLAI_WORK *aiwk;
  s16 *scrMagHp;
  SBTLAI_WORK *v5;
  s16 *scrMagNum;
  s16 *v7;
  s8 *scrMagFlg;
  SBTLAI_WORK *v9;
  s16 *v10;
  s16 *v11;
  s8 *v12;
  SBTLAI_WORK *v13;
  s16 *v14;
  s16 *v15;
  s8 *v16;
  SBTLAI_WORK *v17;
  s16 *v18;
  s16 *v19;
  s8 *v20;

  aiwk = pUnit->aiwk;
  aiwk->scrListID = -1;
  aiwk->scrflag = 0;
  aiwk->act_p = 0;
  *(u64 *)&aiwk->scrStep = 0;
  aiwk->scrStep3 = 0;
  scrMagHp = aiwk->scrMagHp;
  aiwk->scrMagNum[0] = 0;
  scrMagHp[0] = 0;
  *(u64 *)&aiwk->scrTargetCode = 0xFFFFFFFF00020000LL;
  aiwk->scrMagFlg[0] = 0;
  v5 = pUnit->aiwk;
  v7 = v5->scrMagHp;
  scrMagNum = v5->scrMagNum;
  scrMagFlg = v5->scrMagFlg;
  scrMagNum[1] = 0;
  v7[1] = 0;
  scrMagFlg[1] = 0;
  v9 = pUnit->aiwk;
  v11 = v9->scrMagHp;
  v10 = v9->scrMagNum;
  v12 = v9->scrMagFlg;
  v10[2] = 0;
  v11[2] = 0;
  v12[2] = 0;
  v13 = pUnit->aiwk;
  v15 = v13->scrMagHp;
  v14 = v13->scrMagNum;
  v16 = v13->scrMagFlg;
  v14[3] = 0;
  v15[3] = 0;
  v16[3] = 0;
  v17 = pUnit->aiwk;
  v19 = v17->scrMagHp;
  v18 = v17->scrMagNum;
  v20 = v17->scrMagFlg;
  v18[4] = 0;
  v19[4] = 0;
  v20[4] = 0;
  if ((wk->scrFlag & 0x40000) != 0)
    return;
  if ((pUnit->side & 0x81) == 1)
  {
    if (wk->battlemode != 3)
      goto LABEL_12;
    goto LABEL_9000;
    if (wk->battlemode != 3)
LABEL_12:
      pUnit->vstatus |= 0x2000000u;
LABEL_9000:
  }
}

// 0x211c390
bool sBtlCheckSetHITNONE(s32 Group, u32 DevilID) {
  return 0;
}

// 0x211c3a0
void sBtlEncountInit(SBTLUNIT_WORK *wk, s32 EffMode) {
  sdatUnitWork_t *p_para;
  s32 devilid;
  u32 v8;
  bool v9;
  s32 v10;
  s32 v12;

  if (EffMode == 2)
  {
    wk->status |= 1u;
    wk->LoadOnlyTgtSelect = 1;
    sBtlStatusBitOn(wk, 0x4000u);
    devilid = (u16)wk->para->devilid;
    if (devilid == 309 || devilid == 288)
    {
      p_para = &wk->para;
      wk->hstatus |= 8u;
      goto LABEL_11;
    }
  }
  else
  {
    devilid = (u16)wk->para->devilid;
  }
  p_para = &wk->para;
  if ((s16)devilid > 272)
  {
LABEL_11:
    v8 = devilid - 278;
    v9 = v8 > 0x10;
    v10 = (1 << v8) & 0x14003;
    if (!v9 && v10 != 0)
      goto LABEL_15;
    goto LABEL_16;
  }
  if (devilid == 168)
  {
    if (!wk->scrStep)
    {
      sBtlStatusBitOn(wk, 0x10u);
    }
  }
  else if (devilid == 182 || devilid == 272)
  {
LABEL_15:
    wk->hstatus |= 8u;
  }
LABEL_16:
  v12 = (u16)(p_para)->devilid;
  if (v12 == 302 || v12 == 263)
  {
    if (wk->scrStep)
      return;
    sBtlStatusBitOn(wk, 0x10u);
  }
}

// 0x211c590
void sBtlDeath(SBTLUNIT_WORK *wk) {
  s32 devilid;
  u32 v4;
  SBATTLE_WORK *v6;
  s32 scrStep;
  SBATTLE_WORK *v9;
  SBTLUNIT_WORK *v10;
  s32 v11;
  SBTLAI_WORK *aiwk;
  SBTLAI_WORK *v13;
  SBTLAI_WORK *v14;

  wk->aiwk->scrflag |= 0x1000000u;
  devilid = wk->para->devilid;
  if (devilid <= 273)
  {
    if (devilid != 169)
    {
      switch (wk->para->devilid)
      {
        case 0x101:
        case 0x102:
        case 0x104:
        case 0x106:
        case 0x10B:
        case 0x111:
          goto LABEL_11;
        case 0x10C:
          goto LABEL_16;
        case 0x10D:
          goto LABEL_25;
        case 0x10E:
        case 0x10F:
          sBtlStatusBitOn(wk, 0x4000u);
          break;
        default:
          return;
      }
      return;
    }
LABEL_11:
    v6 = wk;
    goto LABEL_14;
  }
  v4 = devilid - 288;
  if (v4 > 0x19)
    return;
  if (((1 << v4) & 0x3601A1D) != 0)
    goto LABEL_11;
  if (v4 == 16)
  {
LABEL_25:
    v6 = wk;
    scrStep = v6->scrStep;
    if (!scrStep)
      goto LABEL_48;
    v6 = wk;
    scrStep = v6->scrStep;
    if (scrStep == 3)
    {
LABEL_48:
      v9 = wk;
      v10 = v9->scrUnitList[1];
      v11 = 6;
      goto LABEL_34;
    }
  }
  else
  {
    if (v4 != 17)
      return;
LABEL_16:
    v6 = wk;
    scrStep = v6->scrStep;
    if (!scrStep)
      goto LABEL_49;
    v6 = wk;
    scrStep = v6->scrStep;
    if (scrStep == 3)
    {
LABEL_49:
      v9 = wk;
      v10 = v9->scrUnitList[2];
      v11 = 5;
LABEL_34:
      v9->scrStep = v11;
      aiwk = wk->aiwk;
      *(u64 *)&aiwk->scrStep = 0;
      aiwk->scrStep3 = 0;
      v13 = v10->aiwk;
      *(u64 *)&v13->scrStep = 0;
      v13->scrStep3 = 0;
      v9->status |= 0x42000000u;
      sBtlStatusBitOff(wk, 0xFFFFBFFF);
      sBtlStatusBitOff(v10, 0xFFFFBFFF);
      return;
    }
  }
  v6 = wk;
  scrStep = v6->scrStep;
  if (scrStep == 2)
  {
    v6 = wk;
    v6->scrStep = 4;
    v14 = wk->aiwk;
    *(u64 *)&v14->scrStep = 0;
    v14->scrStep3 = 0;
LABEL_14:
    v6->status |= 0x42000000u;
  }
}

// 0x211c860
void Delete(SBTLUNIT_WORK *wk) {
  s64 scrListID;
  s64 v5;
  s32 devilid;
  SBATTLE_WORK *v8;
  SBTLUNIT_WORK *v9;
  SBTLAI_WORK *aiwk;
  s32 scrStep3;
  s32 *m_Items;

  scrListID = wk->aiwk->scrListID;
  if ((u32)scrListID != -1)
  {
    v5 = (s64)wk->scrUnitList + 8 * scrListID;
    *(u64 *)(v5 + 32) = 0;
    --wk->scrUnitNum;
  }
  devilid = (u16)wk->para->devilid;
  if (devilid == 301 || devilid == 261)
  {
    v8 = wk;
    v9 = v8->scrUnitList[0];
    if (v9)
    {
      aiwk = v9->aiwk;
      scrStep3 = aiwk->scrStep3;
      if (scrStep3 == 2)
      {
        aiwk->scrStep3 = 3;
        v8 = wk;
        m_Items = &v8->scrCnt[2];
      }
      else if (scrStep3 == 1)
      {
        aiwk->scrStep3 = 2;
        v8 = wk;
        m_Items = &v8->scrCnt[1];
      }
      else
      {
        if (scrStep3)
          return;
        aiwk->scrStep3 = 1;
        v8 = wk;
        m_Items = v8->scrCnt;
      }
      *m_Items = 0;
    }
  }
}

// 0x211c9f0
void sBtlBattleStart(SB_ENCOUNTPAC *encpac, bool _EnemySummonWait) {
  s32 v4;
  s32 v5;

  if ((encpac->flag & 0x20) != 0)
  {
    if (EnemySummonWait)
    {
      v4 = 4;
      v5 = 2;
    }
    else
    {
      v4 = 1;
      v5 = 1;
    }
    sBtlSupport_BattleStop(v4, v5, (s32)method);
  }
}

// 0x211ca20
u32 sBtlSetAttr(SBTLUNIT_WORK *wk, u32 attr) {
  u32 v3;

  v3 = (wk->aiwk->scrflag >> 1) & 0x8000;
  if (wk->actwk->status - 7 < 2)
    v3 = 0x8000;
  return v3 | attr;
}

// 0x211ca50
s32 sBtlCheckHuttobi(SBTLUNIT_WORK *wk) {
  s32 devilid;
  u32 status;

  if ((wk->aiwk->scrflag & 0x10000) != 0)
    return 0;
  devilid = wk->para->devilid;
  if (sBtlDevilCheck_YASO(devilid))
    return 0;
  status = wk->actwk->status;
  if (status == 7)
    return 0;
  return status != 8;
}

// 0x211cb10
s32 CheckBadStatus(SBTLUNIT_WORK *wk) {
  s32 devilid;
  s32 scrStep;
  u32 scrflag;

  devilid = wk->para->devilid;
  if (devilid <= 290)
  {
    if (devilid <= 262)
    {
      if (devilid != 258)
      {
        if (wk->para->devilid != 262)
          return 1;
        return (wk->aiwk->scrflag & 0x10000) == 0;
      }
      return 0;
    }
    if ((devilid & 0xFFFFFFFE) == 0x10C)
    {
LABEL_10:
      if (!wk->scrStep)
        return (wk->aiwk->scrflag & 0x10000) == 0;
      return 0;
    }
    if (devilid != 290)
      return 1;
    goto LABEL_20;
  }
  if ((u32)devilid <= 0x129)
  {
    if (devilid == 291)
    {
      scrflag = wk->aiwk->scrflag;
      if ((scrflag & 0x10000) == 0)
        return ((scrflag >> 22) & 1) == 0;
      return 0;
    }
    if (wk->para->devilid != 297)
      return 1;
LABEL_20:
    scrStep = wk->scrStep;
    if (scrStep == 6)
      return 0;
    if (scrStep == 7)
      return 0;
    return (wk->aiwk->scrflag & 0x10000) == 0;
  }
  if (devilid != 300)
  {
    if ((devilid & 0xFFFFFFFE) != 0x130)
      return 1;
    goto LABEL_10;
  }
  return (wk->aiwk->scrflag & 0x10000) == 0;
}

// 0x211ccd0
bool sBtlCheckSkillCancel(SBTLUNIT_WORK *wk, SKLID skillID) {
  SBTLEFF_LISTWORK *effList;
  SBTLEFF_LISTWORK *v8;
  SBTLEFF_LISTWORK *v10;
  s32 v11;
  s64 i;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  u32 v16;
  bool v17;
  s64 v18;
  bool v19;
  SBTLAI_WORK *aiwk;
  s32 v21;
  u32 scrflag;
  s32 devilid;

  if (skillID != 435)
    return 0;
  effList = wk->effList;
  if (sBtlSearchEffect_SAB(effList, 434, 1u))
    goto LABEL_19;
  v8 = wk->effList;
  if (sBtlSearchEffect_SAB(v8, 434, 2u))
    goto LABEL_19;
  v10 = wk->effList;
  if (sBtlSearchEffect_SAB(v10, 434, 5u))
    goto LABEL_19;
  v11 = 0;
  goto LABEL_20;
LABEL_19:
  v11 = 1;
LABEL_20:
  for (i = 0; ; ++i)
  {
    UnitMng = wk->UnitMng;
    if (i >= UnitMng->number)
      break;
    pUnit = UnitMng->pUnitL[i]->pUnit;
    if (!pUnit)
      continue;
    if (pUnit->actwk->status != 10)
    {
      v16 = (u16)pUnit->para->devilid - 261;
      v17 = v16 > 0x29;
      v18 = (1 << v16) & 0x30000000005LL;
      v19 = v17 || v18 == 0;
      if (!v19 && pUnit->mode >= 5)
        v11 += HIWORD(pUnit->aiwk->scrflag) & 1;
    }
  }
  if (v11 < 4)
    return 0;
  aiwk = wk->aiwk;
  v21 = -66049;
  scrflag = aiwk->scrflag;
  aiwk->scrAutoCnt = 0;
  aiwk->scrflag = scrflag & 0xFFFEFFFF;
  devilid = (u16)wk->para->devilid;
  if ((s16)devilid <= 285)
  {
    if (devilid == 262)
      goto LABEL_45;
    if (devilid != 285)
      return 1;
  }
  else if (devilid != 308)
  {
    if (devilid != 300)
      return 1;
LABEL_45:
    v21 = -67174401;
  }
  aiwk->scrflag = v21 & scrflag;
  return 1;
}

// 0x211d0c0
bool sBtlCheckEnshutuSummonUnit(SBTLUNIT_WORK *wk) {
  SBATTLE_WORK *v4;

  if (!wk)
    return 0;
  v4 = wk;
  if ((v4->scrFlag & 0x40000) == 0)
    return 0;
  if ((wk->side & 0x81) != 1)
    return 0;
  if (v4->battlemode == 3)
    return 0;
  return 1;
}

// 0x211d1a0
void sBtlDamage(SBTLUNIT_WORK *wk, SKLID skillid, s32 damage) {
  s32 devilid;

  if ((sBtlGetSkilltbl(skillid)->flg & 1) != 0)
  {
    devilid = (u16)wk->para->devilid;
    if (devilid == 309 || devilid == 288)
      wk->aiwk->scrflag |= 0x200u;
  }
}

// 0x211d040
void sBtlEndAction(SBTLUNIT_WORK *wk) {
  SBTLAI_WORK *aiwk;
  u32 scrflag;
  s32 devilid;

  aiwk = wk->aiwk;
  aiwk->scrAutoCnt = 0;
  scrflag = aiwk->scrflag;
  aiwk->scrflag = scrflag & 0xFFFEFFFF;
  devilid = (u16)wk->para->devilid;
  if ((s16)devilid > 285)
  {
    if (devilid != 308)
    {
      if (devilid != 300)
        return;
LABEL_9:
      aiwk->scrflag = scrflag & 0xFBFEFFFF;
      return;
    }
    goto LABEL_7;
  }
  if (devilid == 262)
    goto LABEL_9;
  if (devilid == 285)
LABEL_7:
    aiwk->scrflag = scrflag & 0xFFFEFDFF;
}

// 0x211d200
void sBtlStartDeadEvent(SBTLUNIT_WORK *wk) {
  SBTLAI_WORK *aiwk;

  aiwk = wk->aiwk;
  *(u64 *)&aiwk->scrStep = 0;
  aiwk->scrSkillID = -1;
  aiwk->scrStep3 = 0;
  aiwk = wk->aiwk;
  wk->enshutuCnt[3] = 0;
  aiwk->scrflag |= 0x40000u;
  sBtlSupport_StopAction(wk);
}

// 0x211d2a0
s32 sBtlGetPointLast(SBTLUNIT_WORK *wk, SKLID skillID) {
  SBATTLE_WORK *v6;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 playerID;
  SBTLUNIT_WORK *v9;
  SBTLUNIT_WORK *PointNums;
  s32 v13;
  s32 sklid_BS14_target_local;
  SBTLAI_WORK *aiwk;
  s64 scrStep3;
  s32 *scrData;

  v6 = wk;
  UnitMng = v6->UnitMng;
  playerID = v6->playerID;
  v9 = sBtlSearchUnit_ID(UnitMng, playerID);
  Support_GetNakamaData(0);
  NewSpecific(s32, 0x10u);
  PointNums = mapEncGetPointNums();
  if (skillID > 229)
  {
    if ((u32)skillID > 0x1CC)
    {
      if (skillID != 465)
      {
        if (skillID != 474)
          return 0;
        return sBtlGetNearPosHD(PointNums, v9->pos);
      }
      return sklid_BS14_target;
    }
    sklid_BS14_target_local = 0;
    if (skillID <= 458)
    {
      if (skillID == 235)
        return sBtlGetNearPosHD(PointNums, v9->pos);
      if (skillID != 458)
        return sklid_BS14_target_local;
    }
    sklid_BS14_target_local = sklid_BS14_target;
    aiwk = wk->aiwk;
    scrStep3 = aiwk->scrStep3;
    scrData = wk->scrData;
    aiwk->scrStep3 = scrStep3 + 1;
    scrData[scrStep3] = sklid_BS14_target_local;
    return sklid_BS14_target_local;
  }
  if (skillID != 73)
  {
    if ((u32)(skillID - 80) <= 0xFFFFFFFA)
    {
      if ((skillID & 0xFFFFFFFE) != 0xE4)
        return 0;
      return sBtlGetNearPosHD(PointNums, v9->pos);
    }
    sklid_BS14_target_local = sklid_BS14_target;
    wk->scrData[wk->aiwk->scrStep3] = sklid_BS14_target_local;
    return sklid_BS14_target_local;
  }
  v13 = wk->aiwk->scrStep3;
  return sBtlBS14_CHOUSIN_TargetGet(v13);
}

// 0x211d6e0
s32 sBtlGetNearPosHD(SBTLUNIT_WORK *wk, const sdfVector4_t *unit_pos) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  s32 PointNums;
  s32 v8;
  f32 v9;
  s32 v10;
  s32 v11;
  f32 v12;
  f32 *p_x;
  f32 *v15;
  f32 v16;
  f32 v17;
  f32 v18;
  struct sdfVector4_t v22;
  sdfVector4_t rot;
  sdfVector4_t pos;

  w = unit_pos->w;
  z = unit_pos->z;
  y = unit_pos->y;
  x = unit_pos->x;
  PointNums = mapEncGetPointNums();
  *(u64 *)&pos.x = 0;
  *(u64 *)&pos.z = 0;
  if (PointNums == -1)
    v8 = 1;
  else
    v8 = PointNums;
  *(u64 *)&rot.x = 0;
  *(u64 *)&rot.z = 0;
  if (v8 >= 1)
  {
    v9 = 1000000.0;
    v10 = 0;
    v11 = 0;
    while (1)
    {
      sBtlGetPointData(v11, &pos, &rot);
      v22 = pos;
      vct_A = v22;
      p_x = &vf00.x;
      p_x[8] = x;
      p_x[9] = y;
      p_x[10] = z;
      p_x[11] = w;
      vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
      v15 = &vf00.x;
      v16 = v15[4];
      v17 = v15[5];
      v18 = v15[6];
      v12 = sqrtf((f32)((f32)(v16 * v16) + (f32)(v17 * v17)) + (f32)(v18 * v18));
      if (v12 < v9)
      {
        v9 = v12;
        v10 = v11;
      }
      if (v8 == ++v11)
        return v10;
    }
  }
  return 0;
}

// 0x211da20
bool GetUnitHelperMatrix(SBTLUNIT_WORK *wk, SBTLUNIT_MARK mark) {
  s32 v5;
  s64 v7;
  long f64 v9;
  f32 v10;
  struct sdfVector4_t scrPos3;
  struct sdfMatrix4_t v15;

  if (wk->para->devilid != 259)
    return 0;
  if (mark == 302)
  {
    v5 = 102;
LABEL_14:
    sBtlGetUnitHelperPos(wk, v5);
    scrPos3 = wk->actaiwk->scrPos3;
    vct_B = scrPos3;
    vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    v9 = sub_18E6660(0, v7);
    v10 = *(f32 *)&v9;
    mtx_A = identityMatrix;
    sub_19493E0(0, -v10);
    return 1;
  }
  if (mark != 301)
  {
    if (mark == 300)
    {
      v5 = 101;
      goto LABEL_14;
    }
    return 0;
  }
  v15 = identityMatrix;
  mtx_A = v15;
  return 1;
}

// 0x211ddf0
bool sBtlCheckEffectCancel(SBTLUNIT_WORK *wk, SKLID skillID, EFFPDATA_WORK *effpdwork) {
  bool result;
  u32 v8;
  s32 v9;
  s32 scrStep;

  result = 0;
  if (wk && skillID == 465)
  {
    if (effpdwork->iti < 0x10u)
      return 0;
    if (wk->para->devilid != 259)
      return 0;
    result = 0;
    v8 = effpdwork->iti_no - 101;
    if (v8 <= 0xC)
    {
      v9 = 1 << v8;
      if ((v9 & 0x38D) != 0)
      {
        scrStep = wk->scrStep;
        if (scrStep == 1)
          return 1;
      }
      else
      {
        if ((v9 & 0x1C32) == 0)
          return result;
        scrStep = wk->scrStep;
        if (scrStep == 2)
          return 1;
      }
      scrStep = wk->scrStep;
      return scrStep == 3;
    }
  }
  return result;
}

// 0x211df70
static void Support_RunZoomProcess(void) {
  SBTLVISUAL_DATA *v1;
  SBTLUNIT_WORK *scrunit;
  SBATTLE_WORK *v5;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 playerID;
  SBTLUNIT_WORK *v8;
  struct sdfVector4_t v10;
  f32 *p_x;
  f32 z;
  f32 y;
  f32 x;
  struct sdfVector4_t v16;
  struct sdfVector4_t v18;
  f32 v19;
  f32 v20;
  f32 v21;
  f32 v22;
  float32x4_t v23;
  f32 v24;
  f32 v25;
  f32 v27;
  f32 v29;
  f32 v30;
  f32 w;
  f32 v32;
  f32 v33;
  struct sdfVector4_t pos;
  sdfVector4_t v41;

  v1 = Allocate(SBTLVISUAL_DATA);
  _ctor(v1, 0);
  if ((wk->scrFlag & 4) != 0)
    return;
  scrunit = wk->scrunit;
  if (scrunit->para->devilid == 291)
  {
    wk->scrFlag |= 8u;
    v5 = wk;
    UnitMng = v5->UnitMng;
    playerID = v5->playerID;
    v8 = sBtlSearchUnit_ID(UnitMng, playerID);
    pos = scrunit->pos;
    vct_A = pos;
    v10 = v8->pos;
    vct_B = v10;
    vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    p_x = &vf00.x;
    z = p_x[6];
    x = p_x[4];
    y = p_x[5];
    v16 = scrunit->pos;
    vct_A = v16;
    v18 = v8->pos;
    vct_B = v18;
    v19 = x * x;
    v20 = y * y;
    vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    v21 = v19 + v20;
    v22 = z * z;
    v23.n128_u64[0] = 0x3F0000003F000000LL;
    v23.n128_u64[1] = 0x3F0000003F000000LL;
    v24 = v21 + v22;
    vct_A = (struct sdfVector4_t)vmulq_f32((float32x4_t)vct_A, v23);
    v25 = sqrtf(v24);
    if (v25 > 400.0)
    {
      v27 = 0.8;
LABEL_68:
      v29 = vct_A.x;
      v30 = vct_A.y;
      v32 = vct_A.z;
      w = vct_A.w;
      sBtlGetCylinderData(scrunit, v1);
      v33 = v30 + (f32)(v1->height * -0.5);
      v41.x = v29;
      v41.y = v33;
      v41.z = v32;
      v41.w = w;
      sBtlSetZoom2(v41, v27, 0);
      return;
    }
    if (v25 >= 200.0)
      v27 = (f32)((f32)((f32)(400.0 - v25) / 200.0) * 0.3) + 0.8;
    else
      v27 = 1.1;
    goto LABEL_68;
  }
}

// 0x211e660
static s32 Support_RunWaitProcess(void) {
  SBTLUNIT_WORK *scrunit;
  SBTLAI_WORK *aiwk;
  u32 scrflag;
  s32 cmpscrcnt;
  bool v7;
  s32 scrcnt;

  scrunit = wk->scrunit;
  aiwk = scrunit->aiwk;
  scrflag = aiwk->scrflag;
  if ((scrflag & 0x100) == 0)
    return 0;
  cmpscrcnt = aiwk->cmpscrcnt;
  if (cmpscrcnt == -2)
  {
    if (!scrunit->motionno)
    {
LABEL_16:
      aiwk->scrflag = scrflag & 0xFBFEFEFF;
      return 0;
    }
    v7 = sBtlCheckMotionEnd(scrunit);
    aiwk = scrunit->aiwk;
    if (v7)
    {
      scrflag = aiwk->scrflag;
      goto LABEL_16;
    }
    scrcnt = aiwk->scrcnt;
  }
  else
  {
    scrcnt = aiwk->scrcnt;
    if ((cmpscrcnt & 0x80000000) == 0 && scrcnt >= cmpscrcnt)
      goto LABEL_16;
  }
  aiwk->scrcnt = scrcnt + 1;
  return 1;
}

// 0x211e7d0
static void Support_MovePos2(SBTLUNIT_WORK *wk, const sdfVector4_t *pos, f32 frame, s32 motion_no) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  u16 major;
  s32 minor;
  VISUALDATA_WORK *VisualData;
  MOTIONDATA_WORK *MotionVisualData;
  u16 flg;
  f32 *p_m_speed;
  f32 *v19;
  f32 v20;
  SBTLACTAI_WORK *actaiwk;
  f32 *p_x;
  SBTLACTAI_WORK *v24;
  sdfVector4_t *p_ppos;
  struct sdfVector4_t v26;
  f32 *v27;
  f32 v28;
  f32 v29;
  f32 v30;
  f32 v32;
  f32 v33;
  struct sdfVector4_t max_mvspd;
  f32 v36;
  f32 v37;
  f32 v38;
  f32 v39;
  f32 v40;
  SBTLACTAI_WORK *v41;
  s32 v44;

  w = pos->w;
  z = pos->z;
  y = pos->y;
  x = pos->x;
  major = wk->major;
  minor = wk->minor;
  VisualData = sBtlGetVisualData(major, minor);
  MotionVisualData = sBtlGetMotionVisualData(wk->major, wk->minor, wk->next_motionno);
  flg = MotionVisualData->flg;
  p_m_speed = &MotionVisualData->m_speed;
  if ((flg & 1) != 0)
    v19 = p_m_speed;
  else
    v19 = &VisualData->m_speed;
  v20 = *v19;
  actaiwk = wk->actaiwk;
  actaiwk->status = actaiwk->status & 0xFFFFFDE0 | 0x14;
  actaiwk->mode = 2;
  p_x = &vf00.x;
  p_x[4] = x;
  p_x[5] = y;
  p_x[6] = z;
  p_x[7] = w;
  v24 = wk->actaiwk;
  p_ppos = &v24->ppos;
  *p_ppos = vct_A;
  v26 = wk->pos;
  vct_B = v26;
  vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  v27 = &vf00.x;
  v28 = v27[6];
  v29 = v27[4];
  v30 = v27[5];
  v32 = v29 * v29;
  v33 = v30 * v30;
  max_mvspd = wk->max_mvspd;
  v36 = v32 + v33;
  v37 = v28 * v28;
  v38 = v36 + v37;
  vct_A = max_mvspd;
  v39 = frame / v20;
  v40 = sqrtf(v38);
  v41 = wk->actaiwk;
  v44 = (f32)(v39 + 5.0);
  if ((f32)(v39 + 5.0) == INFINITY)
    v44 = 0x80000000;
  wk->mv_spdbk = vct_A;
  v41->frame = 0;
  v41->cmpframe = v44;
  wk->mv_spdbk.z = v40 / (f32)(v39 + 5.0);
  sBtlSetMotion(wk, motion_no, 5, 0, 0);
  sBtlSetAction(wk, 2, 0);
  wk->actaiwk->stat = 2;
  wk->aiwk->stat = 2;
}

// 0x211ecb0
void btlBoss_CERBER_ModelNodeFadeOutSub(sdfModelNode_t *pNode, const sdfVector4_t *rootColor) {
  f32 z;
  f32 y;
  f32 x;
  Il2CppObject *Component_object;

  z = rootColor->z;
  y = rootColor->y;
  x = rootColor->x;
  Component_object = GetComponent_object_(pNode);
  if (!op_Inequality(Component_object, 0, 0))
    return;
  *((f32 *)&Component_object[3].monitor + 1) = x;
  *(f32 *)&Component_object[4].klass = y;
  *((f32 *)&Component_object[4].klass + 1) = z;
  LOBYTE(Component_object[3].monitor) = 1;
  LODWORD(Component_object[4].monitor) = 0;
  return;
}

// 0x211eda0
static s32 btlBoss_CERBER_ModelNodeFadeOut(SBTLUNIT_WORK *wk, char *pName) {
  sdfModelRootNode_t *modelRoot;
  s32 NodeIndexByName;
  void *v5;
  f32 z;
  sdfModelNode_t *v7;
  Il2CppObject *Component_object;

  modelRoot = wk->hModel->modelRoot;
  NodeIndexByName = sdfModelGetNodeIndexByName(modelRoot, pName);
  if (NodeIndexByName != -1)
  {
    v5 = *(void **)&modelRoot->color.x;
    z = modelRoot->color.z;
    v7 = modelRoot->nodeList->items[NodeIndexByName];
    Component_object = GetComponent_object_(v7);
    if (!op_Inequality(Component_object, 0, 0))
      return 1;
    goto LABEL_6;
    if (op_Inequality(Component_object, 0, 0))
    {
LABEL_6:
      *(void **)((char *)&Component_object[3].monitor + 4) = v5;
      *((f32 *)&Component_object[4].klass + 1) = z;
      LOBYTE(Component_object[3].monitor) = 1;
      LODWORD(Component_object[4].monitor) = 0;
    }
  }
  return 1;
}

// 0x211eea0
s32 sBtlModelNodeFadeout(SBTLUNIT_WORK *wk, char *pName) {
  btlBoss_CERBER_ModelNodeFadeOut(wk, pName);
  return 1;
}
