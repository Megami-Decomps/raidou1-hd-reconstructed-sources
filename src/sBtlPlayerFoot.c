#include "types.h"
#include "SBTLUNIT_MOTION.h"
#include "fld.h"
#include "mdl.h"
#include "sbtl.h"
#include "sbtlmain.h"
#include "sbtlplayerfoot.h"
#include "sbtlsound.h"
#include "sbtlsub.h"

typedef struct SBTLUNIT_WORK SBTLUNIT_WORK;

static SBTLUNIT_MOTION gOld_MotionID;
static f32 gOld_MotionFrame;
static f32 gOld_Animator;
static s32 gRunSE_Idx;
static bool aEffStop;

static void FootSE(SBTLUNIT_WORK *wk);

// 0x20dcd30
void sBtlPlayerDeleteFootEff(void) {
  fldClrPlayerFootEffect();
}

// 0x20dcda0
void sBtlPlayerStopFootEff(void) {
  fldStopPlayerFootEffect();
}

// 0x20dce10
void sBtlPlayerReStartFootEff(void) {
  fldReStartPlayerFootEffect();
}

// 0x20dce80
void FootEff(SBTLUNIT_WORK *wk, f32 _DirOfs, f32 _PosLen, f32 _PosY, f32 _EffSize) {
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  f32 RotToDir;
  f32 Dir180;
  f32 v17;
  f32 v18;
  f32 v19;
  f32 v20;
  f32 v21;
  f32 ToX;
  f32 v23;
  f32 v24;
  sdfVector3_t v25;
  sdfVector4_t v26;

  x = wk->rot.x;
  y = wk->rot.y;
  z = wk->rot.z;
  w = wk->rot.w;
  v26.x = x;
  v26.y = y;
  v26.z = z;
  v26.w = w;
  RotToDir = sBtlGetRotToDir(v26);
  Dir180 = sBtlGetDir180(RotToDir);
  v17 = wk->pos.z;
  v18 = PosY + (f32)(wk->pos.y / -100.0);
  ToX = wk->pos.x / -100.0;
  v23 = v18;
  v24 = v17 / -100.0;
  sBtlGetMoveXZ(ToX, v17 / -100.0, Dir180 + DirOfs, PosLen, &ToX, &v24);
  v19 = ToX;
  v20 = v23;
  v21 = v24;
  v25.x = v19;
  v25.y = v20;
  v25.z = v21;
  addPlayerFootEffect_Pos(v25, EffSize);
}

// 0x20dcfd0
void FootEff_XYZ(f32 _UnityX, f32 _UnityY, f32 _UnityZ, f32 _EffSize) {
  sdfVector3_t v9;

  v9.z = UnityZ;
  v9.x = UnityX;
  v9.y = UnityY;
  addPlayerFootEffect_Pos(v9, EffSize);
}

// 0x20dd060
static void FootSE(SBTLUNIT_WORK *wk) {
  SBTLSCENE_WORK *scene;
  SBTLSCENE_WORK *v5;
  SBTLSCENE_WORK *v6;
  SBTLSCENE_WORK *v7;
  SBTLSCENE_WORK *v8;
  s32 v9;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  u32 v14;
  s32 v15;
  sdfVector4_t v16;

  scene = wk->scene;
  if (scene->major == 23)
  {
    if (scene->minor == 4)
      goto LABEL_40;
  }
  v5 = wk->scene;
  if (v5->major == 37)
  {
    if (v5->minor == 8)
      goto LABEL_40;
  }
  v6 = wk->scene;
  if (v6->major == 39)
  {
    if (v6->minor == 8)
      goto LABEL_40;
  }
  v7 = wk->scene;
  if (v7->major != 37)
    goto LABEL_34;
  if (wk->scene->minor != 9)
    goto LABEL_34;
LABEL_40:
  v9 = sub_1905740(4, 0);
  x = wk->pos.x;
  y = wk->pos.y;
  z = wk->pos.z;
  w = wk->pos.w;
  v14 = v9 + 65804;
  goto LABEL_47;
LABEL_34:
  v8 = wk->scene;
  if (v8->major == 39)
  {
    if (v8->minor == 9)
      goto LABEL_40;
  }
  v15 = sub_1905740(4, 0);
  x = wk->pos.x;
  y = wk->pos.y;
  z = wk->pos.z;
  w = wk->pos.w;
  v14 = v15 + 65542;
LABEL_47:
  v16.x = x;
  v16.y = y;
  v16.z = z;
  v16.w = w;
  sBtlPlay3DSE(v14, v16);
}

// 0x20dd3a0
void sBtlPlayerMotionEff(SBTLUNIT_WORK *wk) {
  bool IsSetsumaPadStop;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  f32 RotToDir;
  f32 Dir180;
  dds3ModelHandle_t *hModel;
  s32 MotionFrame;
  f32 MotionFrameF;
  f32 MotionFrameAnimator;
  f32 v22;
  f32 v23;
  f32 v24;
  f32 v26;
  s32 gOld_MotionID_local;
  f32 v29;
  f32 v30;
  s32 next_motionID;
  f32 v32;
  f32 v33;
  f32 v34;
  s32 v35;
  f32 v36;
  f32 v37;
  s32 v44;
  u32 v45;
  s64 v46;
  f32 v47;
  s32 v49;
  s32 v53;
  u32 v55;
  s64 v56;
  f32 v57;
  u32 v58;
  s64 v59;
  f32 v60;
  u32 v61;
  f32 v62;
  f32 v63;
  f32 v64;
  f32 v65;
  s32 v67;
  f32 v68;
  f32 v69;
  s32 v70;
  f32 v71;
  f32 v72;
  f32 v73;
  f32 v74;
  f32 v75;
  f32 v76;
  f32 v77;
  f32 v78;
  f32 v79;
  f32 v80;
  f32 v82;
  f32 v83;
  f32 v84;
  f32 v85;
  f32 v90;
  f32 v91;
  f32 v92;
  f32 v93;
  f32 v94;
  f32 v96;
  f32 v97;
  f32 v98;
  s32 v99;
  f32 v102;
  s32 v104;
  s32 v107;
  u32 v112;
  s64 v113;
  f32 v114;
  u32 v115;
  s64 v116;
  f32 v117;
  u32 v118;
  s64 v119;
  f32 v120;
  u32 v121;
  s64 v122;
  f32 v123;
  u32 v124;
  s64 v125;
  f32 v126;
  u32 v127;
  s64 v128;
  f32 v129;
  u32 v130;
  s64 v131;
  f32 v132;
  u32 v133;
  s64 v134;
  f32 v135;
  u32 v136;
  s64 v137;
  f32 v138;
  u32 v139;
  s32 v143;
  s32 v145;
  s32 v155;
  f32 v162;
  f32 v165;
  s64 v166;
  f32 v167;
  s64 v168;
  f32 v169;
  f32 v170;
  f32 v172;
  f32 v177;
  f32 v178;
  s64 ToX;
  f32 v180;
  sdfVector3_t v181;
  sdfVector3_t v182;
  sdfVector3_t v183;
  sdfVector3_t v184;
  sdfVector3_t v185;
  sdfVector3_t v186;
  sdfVector3_t v187;
  sdfVector3_t v188;
  sdfVector3_t v189;
  sdfVector3_t v190;
  sdfVector3_t v191;
  sdfVector3_t v192;
  sdfVector3_t v193;
  sdfVector3_t v194;
  sdfVector3_t v195;
  sdfVector3_t v196;
  sdfVector3_t v197;
  sdfVector3_t v198;
  sdfVector3_t v199;
  sdfVector4_t v200;
  sdfVector4_t v201;
  sdfVector4_t v202;
  sdfVector4_t v203;
  sdfVector4_t v204;
  sdfVector4_t v205;

  v180 = 0.0;
  ToX = 0;
  if (wk->mode == 5)
    return;
  IsSetsumaPadStop = sBtlIsSetsumaPadStop();
  if (IsSetsumaPadStop)
  {
    if (aEffStop)
      goto LABEL_23;
    aEffStop = 1;
    fldStopPlayerFootEffect();
    goto LABEL_23;
  }
  if (aEffStop)
  {
    aEffStop = 0;
    fldReStartPlayerFootEffect();
    goto LABEL_23;
  }
LABEL_23:
  x = wk->rot.x;
  y = wk->rot.y;
  z = wk->rot.z;
  w = wk->rot.w;
  v200.x = x;
  v200.y = y;
  v200.z = z;
  v200.w = w;
  RotToDir = sBtlGetRotToDir(v200);
  Dir180 = sBtlGetDir180(RotToDir);
  hModel = wk->hModel;
  MotionFrame = mdlGetMotionFrame(hModel);
  MotionFrameF = mdlGetMotionFrameF(wk->hModel);
  MotionFrameAnimator = mdlGetMotionFrameAnimator(wk->hModel);
  v22 = wk->pos.z;
  v23 = wk->pos.x;
  v24 = wk->pos.y;
  if (wk->battlemode == 1)
    return;
  v26 = v23 / -100.0;
  gOld_MotionID_local = gOld_MotionID;
  v29 = v24 / -100.0;
  v30 = v22 / -100.0;
  if (gOld_MotionID == wk->motionID && gOld_MotionID_local == wk->next_motionID)
  {
    if (gOld_MotionID_local <= 106)
    {
      if ((u32)(gOld_MotionID_local - 103) <= 3 && gOld_MotionID_local != 104)
        goto LABEL_64;
    }
    else if ((u32)(gOld_MotionID_local - 120) <= 0xE && ((1 << (gOld_MotionID_local - 120)) & 0x6001) != 0)
    {
      goto LABEL_64;
    }
    gOld_MotionID_local = wk->motionID;
    gRunSE_Idx = -1;
    if (gOld_MotionID_local > 36)
    {
      if (gOld_MotionID_local == 37)
      {
        if (gOld_MotionFrame != 0.0 && !MotionFrame)
        {
          FootEff(wk, 0.0, 0.01, 0.2, 4.0);
        }
        if (gOld_MotionFrame != 4.0 && MotionFrame == 4)
        {
          FootEff(wk, -10.0, 0.5, 0.05, 1.0);
        }
        if (gOld_MotionFrame != 6.0 && MotionFrame == 6)
        {
          FootEff(wk, 0.0, 0.1, 0.15, 3.0);
        }
        if (gOld_MotionFrame != 8.0 && MotionFrame == 8)
        {
          FootEff(wk, -80.0, 0.3, 0.1, 1.2);
          FootSE(wk);
        }
        if (gOld_MotionFrame != 10.0 && MotionFrame == 10)
        {
          FootEff(wk, 120.0, 0.3, 0.1, 1.2);
        }
        if (gOld_MotionFrame != 16.0 && MotionFrame == 16)
        {
          FootEff(wk, 160.0, 0.4, 0.05, 0.8);
          FootSE(wk);
        }
        if (gOld_MotionFrame == 17.0 || MotionFrame != 17)
          goto LABEL_98;
        *(f32 *)&v53 = -50.0;
LABEL_155:
        v33 = *(f32 *)&v53;
        v36 = 0.05;
        v34 = 0.2;
        v32 = 0.8;
        goto LABEL_58;
      }
LABEL_64:
      switch (gOld_MotionID_local)
      {
        case 54:
          if (gOld_Animator < 1.0 && MotionFrameAnimator >= 1.0)
          {
            FootEff(wk, -5.0, 0.35, 0.05, 1.2);
            FootSE(wk);
          }
          if (gOld_Animator < 31.0 && MotionFrameAnimator >= 31.0)
          {
            v96 = 10.0;
            v97 = 0.35;
            v98 = 0.05;
            *(f32 *)&v99 = 1.2;
            goto LABEL_1402;
          }
          goto LABEL_98;
        case 55:
          if (gOld_MotionFrame < -0.5 && MotionFrameF >= -0.5)
          {
            FootEff(wk, -15.0, 0.5, 0.1, 1.0);
            FootEff(wk, 150.0, 0.6, 0.1, 1.0);
          }
          goto LABEL_98;
        case 56:
          if (gOld_MotionFrame < 3.0 && MotionFrameF >= 3.0)
          {
            FootEff(wk, -15.0, 0.5, 0.1, 1.5);
            FootSE(wk);
          }
          if (gOld_MotionFrame < 7.0 && MotionFrameF >= 7.0)
          {
            v102 = 2.0;
            v96 = 150.0;
            v97 = 0.6;
            v98 = 0.1;
            goto LABEL_2044;
          }
          goto LABEL_98;
        case 57:
          if (gOld_MotionFrame < 5.0 && MotionFrameF >= 5.0)
          {
            FootEff(wk, -50.0, 0.2, 0.1, 1.5);
            FootSE(wk);
          }
          if (gOld_MotionFrame < 14.0 && MotionFrameF >= 14.0)
          {
            v96 = 143.0;
            v97 = 0.45;
            *(f32 *)&v104 = 0.1;
            goto LABEL_1580;
          }
          goto LABEL_98;
        case 58:
        case 59:
        case 60:
        case 61:
        case 62:
        case 63:
        case 64:
        case 65:
        case 66:
        case 67:
        case 68:
        case 69:
        case 70:
        case 71:
        case 72:
        case 73:
        case 74:
        case 75:
        case 76:
        case 77:
        case 78:
        case 84:
        case 85:
        case 86:
        case 89:
        case 90:
        case 91:
        case 92:
        case 111:
        case 113:
        case 114:
        case 115:
        case 116:
        case 117:
        case 118:
        case 119:
        case 124:
        case 126:
        case 127:
        case 128:
        case 129:
        case 130:
        case 131:
        case 132:
        case 135:
        case 136:
        case 137:
        case 138:
        case 139:
        case 140:
        case 141:
        case 142:
        case 143:
        case 156:
        case 157:
        case 158:
        case 159:
          goto LABEL_98;
        case 79:
        case 80:
        case 81:
        case 82:
          if (gOld_MotionFrame < 1.0 && MotionFrame >= 1)
          {
            FootSE(wk);
          }
          if (gOld_MotionFrame < 16.0 && MotionFrame >= 16)
          {
            FootSE(wk);
          }
          if (gOld_MotionFrame < 31.0 && MotionFrame >= 31)
          {
            FootSE(wk);
          }
          if (gOld_MotionFrame < 46.0 && MotionFrame >= 46)
          {
            FootSE(wk);
          }
          if (gOld_MotionFrame < 61.0 && MotionFrame >= 61)
          {
            FootSE(wk);
          }
          if (gOld_MotionFrame < 76.0 && MotionFrame >= 76)
          {
            goto LABEL_2045;
          }
          goto LABEL_98;
        case 83:
          if (gOld_MotionFrame < 26.0 && MotionFrame >= 26)
          {
            FootEff(wk, 0.0, 0.0, 0.3, 4.0);
          }
          if (gOld_MotionFrame < 27.0 && MotionFrame >= 27)
          {
            FootEff(wk, 0.0, 0.0, 0.5, 4.0);
          }
          if (gOld_MotionFrame < 28.0 && MotionFrame >= 28)
          {
            FootEff(wk, 0.0, 0.0, 0.5, 4.0);
          }
          if (gOld_MotionFrame < 30.0 && MotionFrame >= 30)
          {
            FootEff(wk, 170.0, 0.8, 0.1, 2.0);
          }
          if (gOld_MotionFrame < 32.0 && MotionFrame >= 32)
          {
            FootEff(wk, 170.0, 0.8, 0.1, 2.0);
          }
          if (gOld_MotionFrame < 34.0 && MotionFrame >= 34)
          {
            FootEff(wk, 170.0, 0.8, 0.1, 2.0);
          }
          if (gOld_MotionFrame < 35.0 && MotionFrame >= 35)
          {
            FootEff(wk, 75.0, 0.32, 0.05, 1.0);
          }
          if (gOld_MotionFrame < 36.0 && MotionFrame >= 36)
          {
            FootEff(wk, 170.0, 0.7, 0.1, 3.0);
          }
          if (gOld_MotionFrame < 37.0 && MotionFrame >= 37)
          {
            FootEff(wk, 75.0, 0.32, 0.05, 0.8);
            FootEff(wk, -165.0, 1.4, 0.05, 0.7);
            FootEff(wk, 170.0, 0.5, 0.05, 1.5);
          }
          if (gOld_MotionFrame < 65.0 && MotionFrame >= 65)
          {
            *(f32 *)&v107 = 0.2;
            goto LABEL_1812;
          }
          goto LABEL_98;
        case 87:
        case 93:
          if (gOld_MotionFrame < 0.5 && MotionFrameF >= 0.5)
          {
            FootEff(wk, -60.0, 0.25, 0.1, 3.0);
          }
          if (gOld_MotionFrame < 1.0 && MotionFrameF >= 1.0)
          {
            FootEff(wk, 178.0, 0.5, 0.1, 2.5);
          }
          if (gOld_MotionFrame < 2.0 && MotionFrameF >= 2.0)
          {
            FootEff(wk, 150.0, 0.15, 0.05, 1.5);
            FootSE(wk);
          }
          if (gOld_MotionFrame < 5.0 && MotionFrameF >= 5.0)
          {
            FootEff(wk, 0.0, 0.1, 0.05, 1.0);
          }
          if (gOld_MotionFrame < 8.0 && MotionFrameF >= 8.0)
          {
            FootEff(wk, 0.0, 0.1, 0.05, 0.8);
          }
          if (gOld_MotionFrame < 16.0 && MotionFrameF >= 16.0)
            goto LABEL_1435;
          goto LABEL_98;
        case 88:
          if (gOld_MotionFrame < 1.0 && MotionFrameF >= 1.0)
          {
            FootEff(wk, 10.0, 0.5, 0.1, 2.5);
          }
          if (gOld_MotionFrame < 1.5 && MotionFrameF >= 1.5)
          {
            FootEff(wk, 0.0, 0.0, 0.3, 4.0);
            FootEff(wk, 90.0, 0.6, 0.3, 2.0);
            FootEff(wk, -90.0, 0.6, 0.3, 2.0);
          }
          if (gOld_MotionFrame < 2.0 && MotionFrameF >= 2.0)
          {
            FootEff(wk, -165.0, 0.8, 0.1, 3.0);
            FootSE(wk);
          }
          if (gOld_MotionFrame < 3.0 && MotionFrameF >= 3.0)
          {
            FootEff(wk, 0.0, 1.1, 0.1, 3.0);
          }
          if (gOld_MotionFrame < 4.0 && MotionFrameF >= 4.0)
          {
            FootEff(wk, 0.0, 1.5, 0.2, 3.5);
          }
          if (gOld_MotionFrame < 24.0 && MotionFrameF >= 24.0)
          {
            FootEff(wk, 110.0, 0.1, 0.05, 0.8);
            FootSE(wk);
          }
          if (gOld_MotionFrame < 32.0 && MotionFrameF >= 32.0)
          {
            v33 = -45.0;
            v36 = 0.05;
            v34 = 0.3;
            v32 = 0.6;
            goto LABEL_58;
          }
          goto LABEL_98;
        case 94:
          v178 = MotionFrameAnimator;
          if (gOld_MotionFrame != 1.0 && MotionFrame == 1)
          {
            v180 = v30;
            *(f32 *)&ToX = v26;
            *((f32 *)&ToX + 1) = v29 + 0.3;
            if (!v112)
            sBtlGetMoveXZ(v26, v30, Dir180, 0.5, &ToX, &v180);
            v113 = ToX;
            v114 = v180;
            *(u64 *)&v188.x = v113;
            v188.z = v114;
            addPlayerFootEffect_Pos(v188, 5.0);
            MotionFrameAnimator = v178;
          }
          if (gOld_MotionFrame != 4.0 && MotionFrame == 4)
          {
            v180 = v30;
            *(f32 *)&ToX = v26;
            *((f32 *)&ToX + 1) = v29 + 0.3;
            if (!v115)
            sBtlGetMoveXZ(v26, v30, Dir180, 0.5, &ToX, &v180);
            v116 = ToX;
            v117 = v180;
            *(u64 *)&v189.x = v116;
            v189.z = v117;
            addPlayerFootEffect_Pos(v189, 5.0);
            MotionFrameAnimator = v178;
          }
          if (gOld_MotionFrame != 7.0 && MotionFrame == 7)
          {
            v180 = v30;
            *(f32 *)&ToX = v26;
            *((f32 *)&ToX + 1) = v29 + 0.3;
            if (!v118)
            sBtlGetMoveXZ(v26, v30, Dir180, 0.5, &ToX, &v180);
            v119 = ToX;
            v120 = v180;
            *(u64 *)&v190.x = v119;
            v190.z = v120;
            addPlayerFootEffect_Pos(v190, 5.0);
            MotionFrameAnimator = v178;
          }
          if (gOld_MotionFrame != 10.0 && MotionFrame == 10)
          {
            v180 = v30;
            *(f32 *)&ToX = v26;
            *((f32 *)&ToX + 1) = v29 + 0.3;
            if (!v121)
            sBtlGetMoveXZ(v26, v30, Dir180, 0.5, &ToX, &v180);
            v122 = ToX;
            v123 = v180;
            *(u64 *)&v191.x = v122;
            v191.z = v123;
            addPlayerFootEffect_Pos(v191, 5.0);
            MotionFrameAnimator = v178;
          }
          if (gOld_MotionFrame != 13.0 && MotionFrame == 13)
          {
            v180 = v30;
            *(f32 *)&ToX = v26;
            *((f32 *)&ToX + 1) = v29 + 0.3;
            if (!v124)
            sBtlGetMoveXZ(v26, v30, Dir180, 0.5, &ToX, &v180);
            v125 = ToX;
            v126 = v180;
            *(u64 *)&v192.x = v125;
            v192.z = v126;
            addPlayerFootEffect_Pos(v192, 5.0);
            MotionFrameAnimator = v178;
          }
          if (gOld_MotionFrame != 16.0 && MotionFrame == 16)
          {
            v180 = v30;
            *(f32 *)&ToX = v26;
            *((f32 *)&ToX + 1) = v29 + 0.3;
            if (!v127)
            sBtlGetMoveXZ(v26, v30, Dir180, 0.5, &ToX, &v180);
            v128 = ToX;
            v129 = v180;
            *(u64 *)&v193.x = v128;
            v193.z = v129;
            addPlayerFootEffect_Pos(v193, 5.0);
            MotionFrameAnimator = v178;
          }
          if (gOld_MotionFrame != 19.0 && MotionFrame == 19)
          {
            v180 = v30;
            *(f32 *)&ToX = v26;
            *((f32 *)&ToX + 1) = v29 + 0.3;
            if (!v130)
            sBtlGetMoveXZ(v26, v30, Dir180, 0.5, &ToX, &v180);
            v131 = ToX;
            v132 = v180;
            *(u64 *)&v194.x = v131;
            v194.z = v132;
            addPlayerFootEffect_Pos(v194, 5.0);
            MotionFrameAnimator = v178;
          }
          if (gOld_MotionFrame != 22.0 && MotionFrame == 22)
          {
            v180 = v30;
            *(f32 *)&ToX = v26;
            *((f32 *)&ToX + 1) = v29 + 0.3;
            if (!v133)
            sBtlGetMoveXZ(v26, v30, Dir180, 0.5, &ToX, &v180);
            v134 = ToX;
            v135 = v180;
            *(u64 *)&v195.x = v134;
            v195.z = v135;
            addPlayerFootEffect_Pos(v195, 5.0);
            MotionFrameAnimator = v178;
          }
          if (gOld_MotionFrame != 25.0 && MotionFrame == 25)
          {
            v180 = v30;
            *(f32 *)&ToX = v26;
            *((f32 *)&ToX + 1) = v29 + 0.3;
            if (!v136)
            sBtlGetMoveXZ(v26, v30, Dir180, 0.5, &ToX, &v180);
            v137 = ToX;
            v138 = v180;
            *(u64 *)&v196.x = v137;
            v196.z = v138;
            addPlayerFootEffect_Pos(v196, 5.0);
            MotionFrameAnimator = v178;
          }
          if (gOld_MotionFrame != 28.0 && MotionFrame == 28)
          {
            v180 = v30;
            *(f32 *)&ToX = v26;
            *((f32 *)&ToX + 1) = v29 + 0.3;
            if (!v139)
            sBtlGetMoveXZ(v26, v30, Dir180, 0.5, &ToX, &v180);
            v47 = v180;
            v46 = ToX;
            v37 = 5.0;
            goto LABEL_96;
          }
          goto LABEL_98;
        case 95:
          if (gOld_MotionFrame < 0.0 && (MotionFrame & 0x80000000) == 0)
          {
            FootEff(wk, 0.0, 0.1, 0.1, 2.0);
          }
          if (gOld_MotionFrame < 6.0 && MotionFrame >= 6)
          {
            FootEff(wk, 10.0, 0.5, 0.1, 1.5);
          }
          if (gOld_MotionFrame < 7.0 && MotionFrame >= 7)
          {
            FootEff(wk, -160.0, 0.7, 0.1, 1.5);
          }
          if (gOld_MotionFrame < 14.0 && MotionFrame >= 14)
          {
            FootEff(wk, 0.0, 0.1, 0.1, 2.0);
            FootEff(wk, 110.0, 0.3, 0.05, 1.0);
          }
          if (gOld_MotionFrame < 15.0 && MotionFrame >= 15)
          {
            FootEff(wk, 0.0, 0.0, 0.2, 4.0);
          }
          if (gOld_MotionFrame < 34.0 && MotionFrame >= 34)
          {
            FootEff(wk, 0.0, 0.1, 0.1, 2.0);
            FootEff(wk, 170.0, 0.3, 0.1, 1.5);
          }
          if (gOld_MotionFrame < 35.0 && MotionFrame >= 35)
          {
            FootEff(wk, -10.0, 0.6, 0.1, 1.5);
          }
          if (gOld_MotionFrame < 36.0 && MotionFrame >= 36)
          {
            FootEff(wk, 170.0, 0.7, 0.1, 1.5);
          }
          if (gOld_MotionFrame < 54.0 && MotionFrame >= 54)
          {
            FootEff(wk, -30.0, 0.2, 0.05, 0.7);
          }
          if (gOld_MotionFrame < 61.0 && MotionFrame >= 61)
            goto LABEL_2040;
          goto LABEL_98;
        case 96:
        case 104:
          if (gOld_MotionFrame < 0.0 && (MotionFrame & 0x80000000) == 0)
          {
            FootEff(wk, 110.0, 0.25, 0.05, 1.5);
          }
          if (gOld_MotionFrame < 4.0 && MotionFrame >= 4)
          {
            FootEff(wk, -10.0, 0.7, 0.05, 1.5);
          }
          if (gOld_MotionFrame < 8.0 && MotionFrame >= 8)
          {
            FootEff(wk, 130.0, 0.3, 0.05, 1.0);
          }
          if (gOld_MotionFrame < 12.0 && MotionFrame >= 12)
          {
            FootEff(wk, -10.0, 0.25, 0.05, 1.0);
          }
          if (gOld_MotionFrame < 1.0 && MotionFrame >= 1)
          {
            v32 = 1.5;
            v34 = 0.3;
            v36 = 0.1;
            goto LABEL_1971;
          }
          goto LABEL_98;
        case 97:
          if (gOld_MotionFrame < 2.0 && MotionFrameF >= 2.0)
          {
            FootEff(wk, -20.0, 0.6, 0.1, 1.5);
          }
          if (gOld_MotionFrame < 5.0 && MotionFrameF >= 5.0)
          {
            v33 = 10.0;
            goto LABEL_1317;
          }
          goto LABEL_98;
        case 98:
          if (gOld_MotionFrame < 6.0 && MotionFrameF >= 6.0)
          {
            v33 = -25.0;
            v34 = 0.55;
            v36 = 0.1;
            v32 = 1.5;
            goto LABEL_58;
          }
          goto LABEL_98;
        case 99:
          if (gOld_MotionFrame < 4.0 && MotionFrameF >= 4.0)
          {
            v32 = 2.0;
            v33 = 35.0;
            v34 = 0.7;
            *(f32 *)&v35 = 0.1;
            goto LABEL_57;
          }
          goto LABEL_98;
        case 100:
          if (gOld_MotionFrame < 5.0 && MotionFrameF >= 5.0)
          {
            v33 = -25.0;
            v34 = 0.55;
            v36 = 0.1;
            v32 = 2.5;
            goto LABEL_58;
          }
          goto LABEL_98;
        case 101:
          if (gOld_MotionFrame < 4.0 && MotionFrameF >= 4.0)
          {
            FootEff(wk, 0.0, 0.2, 0.3, 3.0);
          }
          if (gOld_MotionFrame < 16.0 && MotionFrameF >= 16.0)
          {
            FootEff(wk, 10.0, 0.1, 0.2, 2.5);
          }
          if (gOld_MotionFrame < 17.0 && MotionFrameF >= 17.0)
          {
            FootEff(wk, -40.0, 0.5, 0.2, 2.0);
          }
          if (gOld_MotionFrame < 19.0 && MotionFrameF >= 19.0)
          {
            FootEff(wk, -140.0, 0.5, 0.1, 1.5);
          }
          if (gOld_MotionFrame < 20.0 && MotionFrameF >= 20.0)
          {
            v33 = 10.0;
            v34 = 0.4;
            v36 = 0.1;
            v32 = 1.5;
            goto LABEL_58;
          }
          goto LABEL_98;
        case 102:
          if (gOld_MotionFrame < 1.0 && MotionFrameF >= 1.0)
          {
            FootEff(wk, -15.0, 0.6, 0.1, 1.5);
          }
          if (gOld_MotionFrame < 4.0 && MotionFrameF >= 4.0)
          {
            v33 = 5.0;
LABEL_1317:
            v36 = 0.1;
            v34 = 0.5;
            v32 = 2.0;
            goto LABEL_58;
          }
          goto LABEL_98;
        case 103:
        case 105:
        case 106:
        case 120:
        case 133:
        case 134:
          if (gOld_Animator < 15.0 && MotionFrameAnimator >= 15.0)
          {
            if (gRunSE_Idx != 1)
            {
              FootEff(wk, -10.0, 0.25, 0.05, 1.5);
              FootSE(wk);
              gRunSE_Idx = 1;
            }
          }
          if (gOld_Animator < 33.0 && MotionFrameAnimator >= 33.0)
          {
            if (gRunSE_Idx != 2)
            {
              FootEff(wk, 10.0, 0.25, 0.05, 1.5);
              FootSE(wk);
              gRunSE_Idx = 2;
            }
          }
          goto LABEL_98;
        case 107:
          if (gOld_MotionFrame < 1.0 && MotionFrame >= 1)
          {
            FootEff(wk, 110.0, 0.3, 0.02, 1.0);
            FootSE(wk);
          }
          if (gOld_MotionFrame < 2.0 && MotionFrame >= 2)
          {
            FootEff(wk, -90.0, 0.25, 0.02, 1.0);
          }
          if (gOld_MotionFrame < 4.0 && MotionFrame >= 4)
          {
            FootEff(wk, 30.0, 0.5, 0.05, 1.5);
          }
          if (gOld_MotionFrame < 5.0 && MotionFrame >= 5)
          {
            v96 = -160.0;
            *(f32 *)&v143 = 0.4;
            goto LABEL_1579;
          }
          goto LABEL_98;
        case 108:
          if (gOld_MotionFrame < 1.0 && MotionFrame >= 1)
          {
            FootEff(wk, -45.0, 0.25, 0.05, 0.8);
            FootSE(wk);
          }
          if (gOld_MotionFrame < 2.0 && MotionFrame >= 2)
          {
            FootEff(wk, 100.0, 0.5, 0.02, 0.8);
          }
          if (gOld_MotionFrame < 5.0 && MotionFrame >= 5)
          {
            FootEff(wk, -100.0, 0.25, 0.05, 1.2);
          }
          if (gOld_MotionFrame < 7.0 && MotionFrame >= 7)
          {
            v96 = 15.0;
            v97 = 0.2;
            *(f32 *)&v145 = 0.03;
            goto LABEL_2043;
          }
          goto LABEL_98;
        case 109:
          if (gOld_MotionFrame < 1.0 && MotionFrame >= 1)
          {
            FootEff(wk, -45.0, 0.25, 0.05, 0.8);
            FootSE(wk);
          }
          if (gOld_MotionFrame < 2.0 && MotionFrame >= 2)
          {
            FootEff(wk, 130.0, 0.3, 0.02, 0.8);
          }
          if (gOld_MotionFrame < 5.0 && MotionFrame >= 5)
          {
            FootEff(wk, -45.0, 0.1, 0.05, 1.0);
          }
          if (gOld_MotionFrame < 6.0 && MotionFrame >= 6)
          {
            v96 = 45.0;
            v98 = 0.02;
            *(f32 *)&v99 = 0.8;
            v97 = 0.1;
LABEL_1402:
            v102 = *(f32 *)&v99;
            goto LABEL_2044;
          }
          goto LABEL_98;
        case 110:
          if (gOld_MotionFrame < 0.5 && MotionFrameF >= 0.5)
          {
            FootEff(wk, 110.0, 0.2, 0.05, 1.0);
          }
          if (gOld_MotionFrame < 1.0 && MotionFrame >= 1)
          {
            FootEff(wk, -50.0, 0.3, 0.1, 1.5);
          }
          if (gOld_MotionFrame < 2.0 && MotionFrame >= 2)
          {
            FootEff(wk, 90.0, 0.2, 0.05, 0.8);
          }
          if (gOld_MotionFrame < 3.0 && MotionFrame >= 3)
          {
            FootEff(wk, -45.0, 0.3, 0.05, 1.0);
          }
          if (gOld_MotionFrame < 5.0 && MotionFrame >= 5)
          {
LABEL_1435:
            v32 = 1.5;
            v33 = 160.0;
            v34 = 0.4;
            *(f32 *)&v35 = 0.1;
            goto LABEL_57;
          }
          goto LABEL_98;
        case 112:
          if (gOld_MotionFrame < 3.0 && MotionFrame >= 3)
          {
            FootEff(wk, 70.0, 0.3, 0.02, 0.5);
          }
          if (gOld_MotionFrame < 4.0 && MotionFrame >= 4)
          {
            FootEff(wk, 90.0, 0.3, 0.05, 0.8);
          }
          if (gOld_MotionFrame < 15.0 && MotionFrame >= 15)
          {
            FootEff(wk, -60.0, 0.25, 0.02, 0.5);
          }
          if (gOld_MotionFrame < 16.0 && MotionFrame >= 16)
          {
            FootEff(wk, -40.0, 0.25, 0.05, 0.8);
          }
          if (gOld_MotionFrame < 25.0 && MotionFrame >= 25)
          {
            v33 = 150.0;
            v36 = 0.05;
            v34 = 0.35;
            v32 = 0.9;
            goto LABEL_58;
          }
          goto LABEL_98;
        case 121:
          if (gOld_MotionFrame < -2.0 && MotionFrame >= -2)
          {
            FootEff(wk, -15.0, 0.2, 0.05, 2.0);
            FootSE(wk);
          }
          if (gOld_MotionFrame < 8.0 && MotionFrame >= 8)
          {
            FootEff(wk, 110.0, 0.3, 0.05, 1.7);
            FootSE(wk);
          }
          if (gOld_MotionFrame < 20.0 && MotionFrame >= 20)
          {
            FootEff(wk, 60.0, 0.2, 0.05, 1.5);
            FootSE(wk);
          }
          if (gOld_MotionFrame < 30.0 && MotionFrame >= 30)
          {
            FootEff(wk, 110.0, 0.3, 0.05, 1.5);
            FootSE(wk);
          }
          if (gOld_MotionFrame < 42.0 && MotionFrame >= 42)
          {
            v96 = 60.0;
            *(f32 *)&v143 = 0.2;
            goto LABEL_1579;
          }
          goto LABEL_98;
        case 122:
          if (gOld_MotionFrame < -1.0 && MotionFrame >= -1)
          {
            FootEff(wk, -90.0, 0.1, 0.05, 2.0);
            FootSE(wk);
          }
          if (gOld_MotionFrame < 8.0 && MotionFrame >= 8)
          {
            FootEff(wk, 140.0, 0.25, 0.05, 1.7);
            FootSE(wk);
          }
          if (gOld_MotionFrame < 18.0 && MotionFrame >= 18)
          {
            FootEff(wk, -160.0, 0.2, 0.05, 1.5);
            FootSE(wk);
          }
          if (gOld_MotionFrame < 27.0 && MotionFrame >= 27)
          {
            FootEff(wk, 160.0, 0.3, 0.05, 1.5);
            FootSE(wk);
          }
          if (gOld_MotionFrame < 37.0 && MotionFrame >= 37)
          {
            *(f32 *)&v155 = -160.0;
            goto LABEL_1578;
          }
          goto LABEL_98;
        case 123:
          if (gOld_MotionFrame < -1.0 && MotionFrame >= -1)
          {
            FootEff(wk, -10.0, 0.2, 0.05, 2.0);
            FootSE(wk);
          }
          if (gOld_MotionFrame < 9.0 && MotionFrame >= 9)
          {
            FootEff(wk, -160.0, 0.15, 0.05, 1.7);
            FootSE(wk);
          }
          if (gOld_MotionFrame < 19.0 && MotionFrame >= 19)
          {
            FootEff(wk, -40.0, 0.3, 0.05, 1.5);
            FootSE(wk);
          }
          if (gOld_MotionFrame < 31.0 && MotionFrame >= 31)
          {
            FootEff(wk, -160.0, 0.15, 0.05, 1.5);
            FootSE(wk);
          }
          if (gOld_MotionFrame < 42.0 && MotionFrame >= 42)
          {
            *(f32 *)&v155 = -40.0;
LABEL_1578:
            v96 = *(f32 *)&v155;
            *(f32 *)&v143 = 0.3;
LABEL_1579:
            v97 = *(f32 *)&v143;
            *(f32 *)&v104 = 0.05;
LABEL_1580:
            v98 = *(f32 *)&v104;
            v102 = 1.5;
            goto LABEL_2044;
          }
          goto LABEL_98;
        case 125:
          if (gOld_MotionFrame < 1.0 && MotionFrame >= 1)
          {
            v197.y = v29 + 0.2;
            *(f32 *)&ToX = v26;
            *((f32 *)&ToX + 1) = v29 + 0.2;
            v180 = v30;
            v197.y = v29 + 0.2;
            v197.x = v26;
            v197.z = v30;
            addPlayerFootEffect_Pos(v197, 3.0);
          }
          if (gOld_MotionFrame < 1.0 && MotionFrame >= 1)
          {
            v198.y = v29 + 0.4;
            *(f32 *)&ToX = v26;
            *((f32 *)&ToX + 1) = v29 + 0.4;
            v180 = v30;
            v198.y = v29 + 0.4;
            v198.x = v26;
            v198.z = v30;
            addPlayerFootEffect_Pos(v198, 5.5);
          }
          if (gOld_MotionFrame < 5.0 && MotionFrame >= 5)
          {
            v199.y = v29 + 0.4;
            *(f32 *)&ToX = v26;
            *((f32 *)&ToX + 1) = v29 + 0.4;
            v180 = v30;
            v199.y = v29 + 0.4;
            v199.x = v26;
            v199.z = v30;
            addPlayerFootEffect_Pos(v199, 6.5);
          }
          if (gOld_MotionFrame < 7.0 && MotionFrame >= 7)
            goto LABEL_314;
          goto LABEL_98;
        case 144:
        case 151:
          if (gOld_MotionFrame < 3.0 && MotionFrame >= 3)
          {
            FootEff(wk, -110.0, 0.3, 0.05, 0.7);
          }
          if (gOld_MotionFrame < 4.0 && MotionFrame >= 4)
          {
            FootEff(wk, 30.0, 0.6, 0.05, 1.5);
            v62 = wk->pos.x;
            v63 = wk->pos.y;
            v65 = wk->pos.z;
            v64 = wk->pos.w;
            v201.x = v62;
            v201.y = v63;
            v201.z = v65;
            v201.w = v64;
            sBtlPlay3DSE(0x10059u, v201);
          }
          if (gOld_MotionFrame < 4.0 && MotionFrame >= 4)
          {
            FootEff(wk, -10.0, 0.9, 0.1, 1.5);
          }
          if (gOld_MotionFrame < 5.0 && MotionFrame >= 5)
          {
            FootEff(wk, -10.0, 1.3, 0.1, 2.0);
          }
          if (gOld_MotionFrame < 6.0 && MotionFrame >= 6)
          {
            FootEff(wk, -10.0, 1.9, 0.1, 3.0);
          }
          if (gOld_MotionFrame < 18.0 && MotionFrame >= 18)
          {
            FootEff(wk, -150.0, 0.4, 0.05, 0.7);
          }
          if (gOld_MotionFrame < 29.0 && MotionFrame >= 29)
          {
            FootEff(wk, -30.0, 0.1, 0.05, 0.7);
            FootSE(wk);
          }
          if (gOld_MotionFrame < 31.0 && MotionFrame >= 31)
          {
            v33 = 170.0;
            v36 = 0.05;
            v34 = 0.2;
            v32 = 0.7;
            goto LABEL_58;
          }
          goto LABEL_98;
        case 145:
        case 152:
          if (gOld_MotionFrame < 3.0 && MotionFrame >= 3)
          {
            FootEff(wk, -105.0, 0.2, 0.05, 1.0);
          }
          if (gOld_MotionFrame < 4.0 && MotionFrame >= 4)
          {
            FootEff(wk, -75.0, 1.0, 0.1, 1.5);
          }
          if (gOld_MotionFrame < 5.0 && MotionFrame >= 5)
          {
            FootEff(wk, -45.0, 1.0, 0.2, 2.0);
          }
          if (gOld_MotionFrame < 6.0 && MotionFrame >= 6)
          {
            FootEff(wk, 0.0, 1.1, 0.35, 3.0);
          }
          if (gOld_MotionFrame < 7.0 && MotionFrame >= 7)
          {
            FootEff(wk, 45.0, 1.2, 0.7, 3.5);
          }
          if (gOld_MotionFrame < 7.0 && MotionFrame >= 7)
          {
            FootEff(wk, -45.0, 0.5, 0.05, 1.5);
            v67 = sub_1905740(3, 0);
            v68 = wk->pos.x;
            v69 = wk->pos.y;
            v70 = v67;
            v72 = wk->pos.z;
            v71 = wk->pos.w;
            v202.x = v68;
            v202.y = v69;
            v202.z = v72;
            v202.w = v71;
            sBtlPlay3DSE(v70 + 65623, v202);
          }
          if (gOld_MotionFrame < 27.0 && MotionFrame >= 27)
          {
            FootEff(wk, 170.0, 0.2, 0.05, 1.0);
          }
          if (gOld_MotionFrame < 36.0 && MotionFrame >= 36)
            goto LABEL_1809;
          goto LABEL_98;
        case 146:
          if (gOld_MotionFrame < 5.0 && MotionFrameF >= 5.0)
          {
            FootEff(wk, -20.0, 0.3, 0.2, 2.0);
            FootEff(wk, 160.0, 0.4, 0.2, 2.0);
          }
          if (gOld_MotionFrame < 8.0 && MotionFrame >= 8)
          {
            FootEff(wk, 0.0, 0.1, 0.2, 3.0);
          }
          if (gOld_MotionFrame < 9.0 && MotionFrame >= 9)
          {
            FootEff(wk, 0.0, 0.3, 0.3, 2.0);
          }
          if (gOld_MotionFrame < 10.0 && MotionFrame >= 10)
          {
            FootEff(wk, 0.0, 0.5, 0.4, 1.0);
          }
          if (gOld_MotionFrame < 19.0 && MotionFrameF >= 19.0)
          {
            FootEff(wk, -20.0, 0.3, 0.2, 2.0);
            FootEff(wk, 160.0, 0.4, 0.2, 2.0);
          }
          if (gOld_MotionFrame < 20.0 && MotionFrame >= 20)
          {
            FootEff(wk, 0.0, 0.01, 0.5, 4.0);
          }
          if (gOld_MotionFrame < 34.0 && MotionFrameF >= 34.0)
          {
            FootEff(wk, -30.0, 0.1, 0.05, 0.7);
          }
          v162 = 41.0;
          if (gOld_MotionFrame < 41.0)
            goto LABEL_2039;
          goto LABEL_98;
        case 147:
          if (gOld_MotionFrame < 1.0 && MotionFrame >= 1)
          {
            FootEff(wk, 0.0, 0.01, 0.2, 4.0);
          }
          if (gOld_MotionFrame < 3.0 && MotionFrame >= 3)
          {
            FootEff(wk, 0.0, 0.01, 0.2, 4.0);
          }
          if (gOld_MotionFrame < 5.0 && MotionFrame >= 5)
          {
            FootEff(wk, 0.0, 0.01, 0.2, 4.0);
          }
          if (gOld_MotionFrame < 7.0 && MotionFrame >= 7)
          {
            FootEff(wk, 0.0, 0.01, 0.2, 4.0);
          }
          if (gOld_MotionFrame < 9.0 && MotionFrame >= 9)
          {
            FootEff(wk, 0.0, 0.01, 0.2, 4.0);
          }
          if (gOld_MotionFrame < 11.0 && MotionFrame >= 11)
          {
            FootEff(wk, 0.0, 0.01, 0.2, 4.0);
          }
          if (gOld_MotionFrame < 13.0 && MotionFrame >= 13)
          {
            FootEff(wk, 0.0, 0.5, 0.2, 3.0);
          }
          if (gOld_MotionFrame < 17.0 && MotionFrame >= 17)
          {
            FootEff(wk, 0.0, 0.8, 0.2, 3.0);
          }
          if (gOld_MotionFrame < 21.0 && MotionFrame >= 21)
          {
            FootEff(wk, 0.0, 1.1, 0.2, 3.0);
          }
          if (gOld_MotionFrame < 42.0 && MotionFrame >= 42)
          {
            FootEff(wk, 170.0, 0.2, 0.05, 1.0);
          }
          if (gOld_MotionFrame < 51.0 && MotionFrame >= 51)
            goto LABEL_1809;
          goto LABEL_98;
        case 148:
        case 153:
          if (gOld_MotionFrame < 1.0 && MotionFrame >= 1)
          {
            FootEff(wk, -45.0, 0.5, 0.05, 1.0);
          }
          if (gOld_MotionFrame < 2.0 && MotionFrame >= 2)
          {
            FootEff(wk, -100.0, 0.5, 0.05, 1.0);
          }
          if (gOld_MotionFrame < 3.0 && MotionFrame >= 3)
          {
            FootEff(wk, -170.0, 0.5, 0.05, 1.0);
            v73 = wk->pos.x;
            v74 = wk->pos.y;
            v76 = wk->pos.z;
            v75 = wk->pos.w;
            v203.x = v73;
            v203.y = v74;
            v203.z = v76;
            v203.w = v75;
            sBtlPlay3DSE(0x10054u, v203);
          }
          if (gOld_MotionFrame < 5.0 && MotionFrame >= 5)
          {
            FootEff(wk, 135.0, 0.5, 0.1, 1.5);
          }
          if (gOld_MotionFrame < 7.0 && MotionFrame >= 7)
          {
            FootEff(wk, 80.0, 0.5, 0.05, 1.0);
          }
          if (gOld_MotionFrame < 9.0 && MotionFrame >= 9)
          {
            FootEff(wk, 0.0, 0.7, 0.1, 1.8);
          }
          if (gOld_MotionFrame < 11.0 && MotionFrame >= 11)
          {
            FootEff(wk, -30.0, 0.8, 0.15, 2.5);
            v77 = wk->pos.x;
            v78 = wk->pos.y;
            v80 = wk->pos.z;
            v79 = wk->pos.w;
            v204.x = v77;
            v204.y = v78;
            v204.z = v80;
            v204.w = v79;
            sBtlPlay3DSE(0x10055u, v204);
          }
          if (gOld_MotionFrame < 12.0 && MotionFrame >= 12)
          {
            FootEff(wk, -30.0, 1.3, 0.3, 3.0);
          }
          if (gOld_MotionFrame < 49.0 && MotionFrame >= 49)
          {
            FootEff(wk, -30.0, 0.1, 0.05, 0.7);
          }
          if (gOld_MotionFrame < 57.0 && MotionFrame >= 57)
            goto LABEL_2040;
          goto LABEL_98;
        case 149:
          if (gOld_MotionFrame < 1.0 && MotionFrame >= 1)
          {
            FootEff(wk, 0.0, 0.01, 0.2, 4.0);
          }
          if (gOld_MotionFrame < 3.0 && MotionFrame >= 3)
          {
            FootEff(wk, 0.0, 0.01, 0.2, 4.0);
          }
          if (gOld_MotionFrame < 5.0 && MotionFrame >= 5)
          {
            FootEff(wk, 0.0, 0.01, 0.2, 4.0);
          }
          if (gOld_MotionFrame < 7.0 && MotionFrame >= 7)
          {
            FootEff(wk, 0.0, 0.01, 0.2, 4.0);
          }
          if (gOld_MotionFrame < 9.0 && MotionFrame >= 9)
          {
            FootEff(wk, 0.0, 0.01, 0.2, 4.0);
          }
          if (gOld_MotionFrame < 11.0 && MotionFrame >= 11)
          {
            FootEff(wk, 0.0, 0.01, 0.2, 4.0);
          }
          if (gOld_MotionFrame < 13.0 && MotionFrame >= 13)
          {
            FootEff(wk, 0.0, 0.5, 0.2, 3.0);
          }
          if (gOld_MotionFrame < 17.0 && MotionFrame >= 17)
          {
            FootEff(wk, 0.0, 0.8, 0.2, 3.0);
          }
          if (gOld_MotionFrame < 21.0 && MotionFrame >= 21)
          {
            FootEff(wk, 0.0, 1.1, 0.2, 3.0);
          }
          if (gOld_MotionFrame < 46.0 && MotionFrame >= 46)
          {
            FootEff(wk, 170.0, 0.2, 0.05, 1.0);
          }
          if (gOld_MotionFrame < 57.0 && MotionFrame >= 57)
          {
LABEL_1809:
            *(f32 *)&v107 = 0.1;
LABEL_1812:
            v97 = *(f32 *)&v107;
            v98 = 0.05;
            v102 = 0.7;
            v96 = -30.0;
            goto LABEL_2044;
          }
          goto LABEL_98;
        case 150:
          if (gOld_MotionFrame < 2.0 && MotionFrameF >= 2.0)
          {
            FootEff(wk, -20.0, 0.5, 0.2, 2.0);
            FootEff(wk, 140.0, 0.3, 0.2, 2.0);
          }
          if (gOld_MotionFrame < 5.0 && MotionFrame >= 5)
          {
            FootEff(wk, 0.0, 0.1, 0.2, 3.0);
          }
          if (gOld_MotionFrame < 6.0 && MotionFrame >= 6)
          {
            FootEff(wk, 0.0, 0.3, 0.3, 2.0);
          }
          if (gOld_MotionFrame < 7.0 && MotionFrame >= 7)
          {
            FootEff(wk, 0.0, 0.5, 0.4, 1.0);
          }
          if (gOld_MotionFrame < 17.0 && MotionFrameF >= 17.0)
          {
            FootEff(wk, -20.0, 0.5, 0.2, 2.0);
          }
          if (gOld_MotionFrame < 18.0 && MotionFrameF >= 18.0)
          {
            FootEff(wk, 160.0, 0.4, 0.2, 2.0);
          }
          if (gOld_MotionFrame < 18.0 && MotionFrame >= 18)
          {
            FootEff(wk, 0.0, 0.01, 0.5, 3.0);
          }
          if (gOld_MotionFrame < 33.0 && MotionFrameF >= 33.0)
          {
            FootEff(wk, -30.0, 0.1, 0.05, 0.7);
          }
          v162 = 40.0;
          if (gOld_MotionFrame < 40.0)
            goto LABEL_2039;
          goto LABEL_98;
        case 154:
          if (gOld_MotionFrame < 0.0 && (MotionFrame & 0x80000000) == 0)
          {
            FootEff(wk, -20.0, 0.6, 0.05, 0.7);
            FootEff(wk, 150.0, 0.4, 0.05, 1.0);
          }
          if (gOld_MotionFrame < 23.0 && MotionFrame >= 23)
          {
            FootEff(wk, 0.0, 0.01, 0.2, 4.0);
          }
          if (gOld_MotionFrame < 25.0 && MotionFrame >= 25)
          {
            FootEff(wk, 0.0, 0.01, 0.2, 4.0);
          }
          if (gOld_MotionFrame < 27.0 && MotionFrame >= 27)
          {
            FootEff(wk, 0.0, 0.01, 0.2, 4.0);
          }
          if (gOld_MotionFrame < 29.0 && MotionFrame >= 29)
          {
            FootEff(wk, 0.0, 0.01, 0.2, 4.0);
          }
          if (gOld_MotionFrame < 31.0 && MotionFrame >= 31)
          {
            FootEff(wk, 0.0, 0.01, 0.2, 4.0);
          }
          if (gOld_MotionFrame < 33.0 && MotionFrame >= 33)
          {
            FootEff(wk, 0.0, 0.01, 0.2, 4.0);
          }
          if (gOld_MotionFrame < 35.0 && MotionFrame >= 35)
          {
            FootEff(wk, 0.0, 0.01, 0.2, 4.0);
          }
          if (gOld_MotionFrame < 37.0 && MotionFrame >= 37)
          {
            FootEff(wk, 0.0, 0.01, 0.2, 4.0);
          }
          if (gOld_MotionFrame < 39.0 && MotionFrame >= 39)
          {
            FootEff(wk, 0.0, 0.01, 0.2, 4.0);
          }
          if (gOld_MotionFrame < 41.0 && MotionFrame >= 41)
          {
            FootEff(wk, 0.0, 0.5, 0.2, 3.0);
          }
          if (gOld_MotionFrame < 43.0 && MotionFrame >= 43)
          {
            FootEff(wk, 0.0, 0.8, 0.2, 3.0);
          }
          if (gOld_MotionFrame < 47.0 && MotionFrame >= 47)
          {
            v32 = 3.0;
            v34 = 1.1;
            v36 = 0.2;
            goto LABEL_1971;
          }
          goto LABEL_98;
        case 155:
          if (gOld_MotionFrame < 1.0 && MotionFrame >= 1)
          {
            v165 = sub_1B34D00(0);
            v167 = sub_1B34D00(0, v166);
            v169 = sub_1B34D00(0, v168);
            v34 = (f32)(v165 * 0.5) + 0.3;
            v36 = (f32)(v167 * 0.05) + 0.2;
            v32 = v169 + 3.0;
LABEL_1971:
            v33 = 0.0;
            goto LABEL_58;
          }
          goto LABEL_98;
        case 160:
        case 166:
          if (gOld_MotionFrame < 1.0 && MotionFrame >= 1)
          {
            FootEff(wk, -10.0, 0.3, 0.1, 2.0);
          }
          if (gOld_MotionFrame < 7.0 && MotionFrame >= 7)
          {
            FootEff(wk, -80.0, 0.1, 0.1, 2.0);
            FootSE(wk);
          }
          if (gOld_MotionFrame < 13.0 && MotionFrame >= 13)
          {
            FootEff(wk, 40.0, 0.5, 0.1, 2.0);
          }
          if (gOld_MotionFrame < 14.0 && MotionFrame >= 14)
          {
            FootEff(wk, 0.0, 0.1, 0.5, 3.0);
          }
          if (gOld_MotionFrame < 28.0 && MotionFrame >= 28)
          {
            FootEff(wk, -160.0, 0.2, 0.1, 2.0);
          }
          if (gOld_MotionFrame < 38.0 && MotionFrame >= 38)
          {
            FootEff(wk, 140.0, 0.5, 0.1, 2.0);
          }
          if (gOld_MotionFrame < 39.0 && MotionFrame >= 39)
          {
            FootEff(wk, 0.0, 0.1, 0.2, 3.0);
          }
          if (gOld_MotionFrame < 40.0 && MotionFrame >= 40)
          {
            FootEff(wk, 0.0, 1.0, 0.5, 3.0);
          }
          if (gOld_MotionFrame < 41.0 && MotionFrame >= 41)
          {
            FootEff(wk, -40.0, 0.5, 0.1, 2.0);
            v82 = wk->pos.x;
            v83 = wk->pos.y;
            v85 = wk->pos.z;
            v84 = wk->pos.w;
            v205.x = v82;
            v205.y = v83;
            v205.z = v85;
            v205.w = v84;
            sBtlPlay3DSE(0x10059u, v205);
          }
          if (gOld_MotionFrame < 42.0 && MotionFrame >= 42)
          {
            FootEff(wk, 0.0, 1.3, 0.5, 3.2);
          }
          if (gOld_MotionFrame < 66.0 && MotionFrame >= 66)
          {
            FootEff(wk, 150.0, 0.15, 0.05, 0.8);
          }
          if (gOld_MotionFrame < 70.0 && MotionFrame >= 70)
          {
            *(f32 *)&v53 = -60.0;
            goto LABEL_155;
          }
          goto LABEL_98;
        case 161:
          if (gOld_MotionFrame >= 2.0 || MotionFrameF < 2.0)
            goto LABEL_1987;
          v170 = 2.0;
          FootEff(wk, -140.0, 0.4, 0.2, 2.0);
          v172 = 20.0;
          goto LABEL_1986;
        case 162:
        case 164:
          if (gOld_MotionFrame < 5.0 && MotionFrame >= 5)
          {
            FootEff(wk, 0.0, 0.0, 0.2, 4.0);
          }
          if (gOld_MotionFrame < 7.0 && MotionFrame >= 7)
          {
            FootEff(wk, 0.0, 0.0, 0.2, 4.0);
          }
          if (gOld_MotionFrame < 9.0 && MotionFrame >= 9)
          {
            FootEff(wk, 0.0, 0.0, 0.2, 4.0);
          }
          if (gOld_MotionFrame < 11.0 && MotionFrame >= 11)
          {
            FootEff(wk, 0.0, 0.0, 0.2, 4.0);
          }
          if (gOld_MotionFrame < 13.0 && MotionFrame >= 13)
          {
            FootEff(wk, 0.0, 0.0, 0.2, 4.0);
          }
          if (gOld_MotionFrame < 15.0 && MotionFrame >= 15)
          {
            FootEff(wk, 0.0, 0.0, 0.2, 4.0);
          }
          if (gOld_MotionFrame < 17.0 && MotionFrame >= 17)
          {
            FootEff(wk, 0.0, 0.0, 0.2, 4.0);
          }
          if (gOld_MotionFrame < 19.0 && MotionFrame >= 19)
          {
            FootEff(wk, 0.0, 0.0, 0.2, 2.0);
          }
          if (gOld_MotionFrame >= 21.0 || MotionFrame < 21)
            goto LABEL_98;
          v32 = 1.0;
          goto LABEL_695;
        case 163:
        case 167:
          if (gOld_MotionFrame < 4.0 && MotionFrame >= 4)
          {
            FootEff(wk, 0.0, 0.1, 0.2, 2.0);
          }
          if (gOld_MotionFrame < 5.0 && MotionFrameF >= 5.0)
          {
            FootEff(wk, -15.0, 0.5, 0.2, 2.0);
            FootEff(wk, 130.0, 0.4, 0.2, 2.0);
          }
          if (gOld_MotionFrame < 6.0 && MotionFrame >= 6)
          {
            FootEff(wk, 0.0, 0.1, 1.0, 3.0);
          }
          if (gOld_MotionFrame < 7.0 && MotionFrame >= 7)
          {
            FootEff(wk, 0.0, 0.2, 1.5, 2.0);
          }
          if (gOld_MotionFrame < 8.0 && MotionFrame >= 8)
          {
            FootEff(wk, 0.0, 0.3, 2.0, 1.0);
          }
          if (gOld_MotionFrame < 48.0 && MotionFrameF >= 48.0)
          {
            FootEff(wk, -20.0, 0.6, 0.1, 3.0);
            FootEff(wk, 45.0, 0.25, 0.1, 2.0);
            FootEff(wk, 140.0, 0.25, 0.1, 3.0);
          }
          if (gOld_MotionFrame < 49.0 && MotionFrame >= 49)
          {
            FootEff(wk, 0.0, 0.3, 0.2, 4.0);
          }
          if (gOld_MotionFrame < 52.0 && MotionFrame >= 52)
          {
            FootEff(wk, 0.0, 0.5, 0.2, 3.0);
          }
          if (gOld_MotionFrame < 55.0 && MotionFrame >= 55)
          {
            FootEff(wk, 0.0, 0.8, 0.2, 3.0);
          }
          if (gOld_MotionFrame < 65.0 && MotionFrameF >= 65.0)
          {
            FootEff(wk, 140.0, 0.25, 0.05, 0.7);
          }
          if (gOld_MotionFrame < 67.0 && MotionFrame >= 67)
          {
            FootEff(wk, 0.0, 0.1, 1.0, 4.0);
          }
          if (gOld_MotionFrame < 68.0 && MotionFrameF >= 68.0)
          {
            FootEff(wk, 160.0, 0.45, 0.1, 1.0);
          }
          if (gOld_MotionFrame < 69.0 && MotionFrameF >= 69.0)
          {
            FootEff(wk, -20.0, 0.55, 0.05, 0.5);
          }
          if (gOld_MotionFrame < 71.0 && MotionFrameF >= 71.0)
          {
            FootEff(wk, -25.0, 0.45, 0.05, 0.7);
          }
          if (gOld_MotionFrame < 73.0 && MotionFrameF >= 73.0)
          {
            FootEff(wk, -30.0, 0.35, 0.05, 0.7);
          }
          if (gOld_MotionFrame < 75.0 && MotionFrameF >= 75.0)
          {
            FootEff(wk, -35.0, 0.25, 0.1, 0.8);
          }
          if (gOld_MotionFrame >= 77.0 || MotionFrameF < 77.0)
            goto LABEL_98;
          v32 = 1.0;
          v33 = -60.0;
          v34 = 0.2;
          *(f32 *)&v35 = 0.1;
          goto LABEL_57;
        case 165:
          if (gOld_MotionFrame < 2.0 && MotionFrameF >= 2.0)
          {
            v170 = 2.0;
            FootEff(wk, -140.0, 0.4, 0.2, 2.0);
            v172 = 30.0;
LABEL_1986:
            FootEff(wk, v172, 0.3, 0.2);
          }
LABEL_1987:
          if (gOld_MotionFrame < 4.0 && MotionFrame >= 4)
          {
            FootEff(wk, 0.0, 0.2, 0.05, 1.5);
          }
          if (gOld_MotionFrame < 6.0 && MotionFrame >= 6)
          {
            FootEff(wk, 0.0, 0.1, 0.2, 3.0);
          }
          if (gOld_MotionFrame < 7.0 && MotionFrame >= 7)
          {
            FootEff(wk, 0.0, 0.3, 0.3, 2.0);
          }
          if (gOld_MotionFrame < 8.0 && MotionFrame >= 8)
          {
            FootEff(wk, 0.0, 0.5, 0.5, 2.0);
          }
          if (gOld_MotionFrame < 18.0 && MotionFrame >= 18)
          {
            FootEff(wk, 0.0, 0.01, 0.2, 3.0);
          }
          if (gOld_MotionFrame < 20.0 && MotionFrame >= 20)
          {
            FootEff(wk, 0.0, 0.01, 0.2, 3.0);
          }
          if (gOld_MotionFrame < 24.0 && MotionFrameF >= 24.0)
          {
            FootEff(wk, 160.0, 0.4, 0.2, 2.0);
          }
          v162 = 43.0;
          if (gOld_MotionFrame < 43.0)
          {
LABEL_2039:
            if (MotionFrameF >= v162)
            {
LABEL_2040:
              v96 = 170.0;
              v97 = 0.2;
              *(f32 *)&v145 = 0.05;
LABEL_2043:
              v98 = *(f32 *)&v145;
              v102 = 1.0;
LABEL_2044:
              FootEff(wk, v96, v97, v98);
LABEL_2045:
              FootSE(wk);
            }
          }
          goto LABEL_98;
        default:
          switch (gOld_MotionID_local)
          {
            case 175:
              v90 = MotionFrameAnimator;
              if (gOld_MotionFrame < 5.0 && MotionFrame >= 5)
              {
                FootEff(wk, 170.0, 0.5, 0.02, 1.0);
              }
              if (gOld_MotionFrame < 6.0 && MotionFrame >= 6)
              {
                FootEff(wk, 170.0, 1.0, 0.02, 1.0);
                FootSE(wk);
              }
              if (gOld_MotionFrame < 21.0 && MotionFrame >= 21)
              {
                FootEff(wk, 0.0, 0.0, 0.2, 4.0);
              }
              if (gOld_MotionFrame >= 23.0 || MotionFrame < 23)
                goto LABEL_98;
              v94 = 30.0;
              v92 = 0.2;
              v91 = 4.0;
              v93 = 0.0;
              break;
            case 177:
              v90 = MotionFrameAnimator;
              if (gOld_MotionFrame < 1.0 && MotionFrame >= 1)
              {
                FootEff(wk, 180.0, 0.7, 0.2, 5.0);
              }
              if (gOld_MotionFrame < 2.0 && MotionFrame >= 2)
              {
                FootEff(wk, 150.0, 0.4, 0.02, 1.0);
                FootEff(wk, -25.0, 0.4, 0.02, 1.0);
              }
              if (gOld_MotionFrame < 3.0 && MotionFrame >= 3)
              {
                FootEff(wk, 180.0, 0.2, 0.1, 4.0);
              }
              if (gOld_MotionFrame < 4.0 && MotionFrame >= 4)
              {
                FootEff(wk, 0.0, 0.3, 0.1, 3.0);
              }
              if (gOld_MotionFrame < 5.0 && MotionFrame >= 5)
              {
                FootEff(wk, 150.0, 0.6, 0.02, 0.7);
                FootEff(wk, -25.0, 0.5, 0.02, 0.7);
              }
              if (gOld_MotionFrame < 7.0 && MotionFrame >= 7)
              {
                FootEff(wk, -30.0, 0.55, 0.02, 0.5);
              }
              if (gOld_MotionFrame < 9.0 && MotionFrame >= 9)
              {
                FootEff(wk, 160.0, 0.7, 0.02, 0.5);
              }
              if (gOld_MotionFrame < 22.0 && MotionFrame >= 22)
              {
                FootEff(wk, 160.0, 0.6, 0.02, 0.5);
              }
              if (gOld_MotionFrame < 32.0 && MotionFrame >= 32)
              {
                FootEff(wk, 150.0, 0.2, 0.02, 0.5);
                FootSE(wk);
              }
              if (gOld_MotionFrame >= 38.0 || MotionFrame < 38)
                goto LABEL_98;
              v93 = 170.0;
              v92 = 0.05;
              v94 = 0.2;
              v91 = 0.7;
              break;
            case 178:
              v90 = MotionFrameAnimator;
              if (gOld_MotionFrame < 1.0 && MotionFrame >= 1)
              {
                FootEff(wk, 0.0, 30.0, 0.2, 5.0);
              }
              if (gOld_MotionFrame >= 3.0 || MotionFrame < 3)
                goto LABEL_98;
              v91 = 4.0;
              v92 = 0.2;
              v93 = 0.0;
              v94 = 0.0;
              break;
            default:
              goto LABEL_98;
          }
          FootEff(wk, v93, v94, v92);
          MotionFrameAnimator = v90;
          goto LABEL_98;
      }
    }
    if (gOld_MotionID_local == 3)
    {
      if (gOld_MotionFrame < 1.0 && MotionFrame >= 1)
      {
        FootEff(wk, 0.0, 0.0, 0.2, 4.0);
      }
      if (gOld_MotionFrame < 3.0 && MotionFrame >= 3)
      {
        FootEff(wk, 0.0, 0.0, 0.2, 4.0);
      }
      if (gOld_MotionFrame < 5.0 && MotionFrame >= 5)
      {
        FootEff(wk, 0.0, 0.0, 0.2, 4.0);
      }
      if (gOld_MotionFrame < 7.0 && MotionFrame >= 7)
      {
        FootEff(wk, 0.0, 0.0, 0.2, 4.0);
      }
      if (gOld_MotionFrame < 9.0 && MotionFrame >= 9)
      {
        FootEff(wk, 0.0, 0.0, 0.2, 4.0);
      }
      if (gOld_MotionFrame < 11.0 && MotionFrame >= 11)
      {
        FootEff(wk, 0.0, 0.0, 0.2, 4.0);
      }
      if (gOld_MotionFrame < 13.0 && MotionFrame >= 13)
      {
        FootEff(wk, 0.0, 0.5, 0.2, 4.0);
      }
      if (gOld_MotionFrame < 17.0 && MotionFrame >= 17)
      {
        FootEff(wk, 0.0, 0.8, 0.2, 3.0);
      }
      if (gOld_MotionFrame >= 21.0 || MotionFrame < 21)
        goto LABEL_98;
      v32 = 2.0;
LABEL_695:
      v36 = 0.2;
      v33 = 0.0;
      v34 = 0.0;
      goto LABEL_58;
    }
    if (gOld_MotionID_local != 24)
    {
      if (gOld_MotionID_local != 36)
        goto LABEL_98;
      if (gOld_MotionFrame != 0.0 && !MotionFrame)
      {
        FootEff(wk, 0.0, 0.01, 0.05, 1.0);
      }
      if (gOld_MotionFrame != 1.0 && MotionFrame == 1)
      {
        FootEff(wk, 180.0, 0.15, 0.2, 3.0);
      }
      if (gOld_MotionFrame != 8.0 && MotionFrame == 8)
      {
        FootEff(wk, -90.0, 0.1, 0.1, 2.0);
      }
      if (gOld_MotionFrame != 9.0 && MotionFrame == 9)
      {
        FootEff(wk, -80.0, 0.1, 0.05, 1.0);
      }
      if (gOld_MotionFrame != 10.0 && MotionFrame == 10)
      {
        FootEff(wk, 150.0, 0.5, 0.1, 2.0);
        FootSE(wk);
      }
      if (gOld_MotionFrame == 11.0 || MotionFrame != 11)
        goto LABEL_98;
      v34 = 0.5;
      v32 = 1.0;
      v33 = 150.0;
      *(f32 *)&v35 = 0.05;
      goto LABEL_57;
    }
    v177 = MotionFrameAnimator;
    if (gOld_MotionFrame < 1.0 && MotionFrame >= 1)
    {
      v180 = v30;
      *(f32 *)&ToX = v26;
      *((f32 *)&ToX + 1) = v29 + 0.2;
      if (!v55)
      sBtlGetMoveXZ(v26, v30, Dir180 + 0.0, 0.3, &ToX, &v180);
      v56 = ToX;
      v57 = v180;
      *(u64 *)&v182.x = v56;
      v182.z = v57;
      addPlayerFootEffect_Pos(v182, 3.0);
      MotionFrameAnimator = v177;
    }
    if (gOld_MotionFrame < 4.0 && MotionFrame >= 4)
    {
      v180 = v30;
      *(f32 *)&ToX = v26;
      *((f32 *)&ToX + 1) = v29 + 0.3;
      if (!v58)
      sBtlGetMoveXZ(v26, v30, Dir180 + 0.0, 0.3, &ToX, &v180);
      v59 = ToX;
      v60 = v180;
      *(u64 *)&v183.x = v59;
      v183.z = v60;
      addPlayerFootEffect_Pos(v183, 4.5);
      MotionFrameAnimator = v177;
    }
    if (gOld_MotionFrame < 10.0 && MotionFrame >= 10)
    {
      *(f32 *)&ToX = v26;
      *((f32 *)&ToX + 1) = v29 + 0.5;
      v180 = v30;
      v184.x = v26;
      v184.y = v29 + 0.5;
      v184.z = v30;
      addPlayerFootEffect_Pos(v184, 6.0);
    }
    if (gOld_MotionFrame < 45.0 && MotionFrame >= 45)
    {
      *(f32 *)&ToX = v26;
      *((f32 *)&ToX + 1) = v29 + 0.2;
      v180 = v30;
      v185.x = v26;
      v185.y = v29 + 0.2;
      v185.z = v30;
      addPlayerFootEffect_Pos(v185, 3.0);
    }
    if (gOld_MotionFrame < 45.0 && MotionFrame >= 45)
    {
      *(f32 *)&ToX = v26;
      *((f32 *)&ToX + 1) = v29 + 0.4;
      v180 = v30;
      v186.x = v26;
      v186.y = v29 + 0.4;
      v186.z = v30;
      addPlayerFootEffect_Pos(v186, 5.5);
    }
    if (gOld_MotionFrame < 49.0 && MotionFrame >= 49)
    {
      *(f32 *)&ToX = v26;
      *((f32 *)&ToX + 1) = v29 + 0.4;
      v180 = v30;
      v187.x = v26;
      v187.y = v29 + 0.4;
      v187.z = v30;
      addPlayerFootEffect_Pos(v187, 6.5);
    }
    if (gOld_MotionFrame >= 51.0 || MotionFrame < 51)
      goto LABEL_98;
LABEL_314:
    v180 = v30;
    *(f32 *)&ToX = v26;
    *((f32 *)&ToX + 1) = v29 + 0.4;
    if (!v61)
    sBtlGetMoveXZ(v26, v30, Dir180 + 180.0, 0.6, &ToX, &v180);
    v47 = v180;
    v46 = ToX;
    v37 = 7.0;
    goto LABEL_96;
  }
  gRunSE_Idx = -1;
  next_motionID = wk->next_motionID;
  if (next_motionID > 36)
    goto LABEL_41;
  if (next_motionID)
  {
    if (next_motionID != 36)
      goto LABEL_98;
LABEL_59:
    *(f32 *)&ToX = v26;
    *((f32 *)&ToX + 1) = v29 + 0.2;
    v180 = v30;
    v37 = 4.0;
    v181.x = v26;
    v181.y = v29 + 0.2;
    v181.z = v30;
    goto LABEL_97;
  }
  v44 = gOld_MotionID;
  if (gOld_MotionID != 5)
  {
    v44 = gOld_MotionID;
    if (v44 != 103)
      goto LABEL_98;
  }
  v180 = v30;
  *(f32 *)&ToX = v26;
  *((f32 *)&ToX + 1) = v29 + 0.05;
  if (!v45)
  sBtlGetMoveXZ(v26, v30, Dir180 + 180.0, 0.3, &ToX, &v180);
  v46 = ToX;
  v47 = v180;
  v37 = 1.5;
LABEL_96:
  *(u64 *)&v181.x = v46;
  v181.z = v47;
LABEL_97:
  addPlayerFootEffect_Pos(v181, v37);
  goto LABEL_98;
LABEL_41:
  switch (next_motionID)
  {
    case 147:
    case 148:
    case 149:
    case 153:
      goto LABEL_59;
    case 150:
    case 151:
    case 152:
      goto LABEL_98;
    default:
      if (next_motionID == 37)
        goto LABEL_59;
      if (next_motionID != 93)
        goto LABEL_98;
      v32 = 0.5;
      v33 = 180.0;
      v34 = 0.15;
      *(f32 *)&v35 = 0.02;
      break;
  }
LABEL_57:
  v36 = *(f32 *)&v35;
LABEL_58:
  FootEff(wk, v33, v34, v36);
LABEL_98:
  v49 = wk->next_motionID;
  gOld_MotionID = v49;
  gOld_MotionFrame = MotionFrameF;
  gOld_Animator = MotionFrameAnimator;
}
