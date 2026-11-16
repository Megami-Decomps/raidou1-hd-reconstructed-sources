#include "types.h"
#include "SBTL_MODE.h"
#include "SKLID.h"
#include "aw_approach.h"
#include "aw_approachatk.h"
#include "aw_down.h"
#include "aw_slashunitex.h"
#include "dds3kerneldraw.h"
#include "fld.h"
#include "mdl.h"
#include "sbtl.h"
#include "sbtldmg.h"
#include "sbtlskill.h"
#include "sbtlsound.h"
#include "sbtlsub.h"
#include "sbtlunit.h"
#include "sbtlunitex.h"
#include "sndmanager.h"

#define COMMAND_NULL 0
#define COMMAND_SECTION_ST 1
#define COMMAND_SECTION_ED 2
#define COMMAND_HIT_RANGE_F 8
#define COMMAND_EFF_SLASH 11
#define COMMAND_SE_A 20
#define COMMAND_SE_TUKI 21
#define COMMAND_SE_KIRI 22
#define COMMAND_MSE_RND2 23
#define COMMAND_MSE_RND3 24
#define COMMAND_MSE_RND4 25
#define COMMAND_MSE_RND5 26
#define COMMAND_VOICE 27
#define COMMAND_V_RND2 28
#define COMMAND_V_RND3 29
#define COMMAND_V_RND4 30
#define COMMAND_V_RND5 31
#define COMMAND_QUAKE 40
#define COMMAND_PADVIB 41
#define COMMAND_EFF_APPROACH 105
#define COMMAND_EFF_APPROACHA 106
#define COMMAND_EFF_DOWN 109
#define COMMAND_EFF_FOOT 130
#define COMMAND_SE_FOOT_EFF 200
#define COMMAND_SE_FOOT_SE 201
#define COMMAND_FLG_NULL 0

typedef struct SBTLSKILLHIT_TBL SBTLSKILLHIT_TBL;
typedef struct SBTLUNIT_WORK SBTLUNIT_WORK;
typedef struct sBtlUnitEx_EX_TABLE_t sBtlUnitEx_EX_TABLE_t;
typedef struct sBtlUnitEx_HDEFF_TABLE_t sBtlUnitEx_HDEFF_TABLE_t;

struct sBtlUnitEx_EX_TABLE_t {
    s32 Command;
    SBTL_MODE battlemode;
    s32 MotionNo;
    s32 MotionFrame;
    f32 deltaTime;
    s32 Variation;
    s32 SkillNum;
    s32 QuakeTime;
    u32 QuakePow;
    s32 VibIn;
    s32 VibLife;
    s32 VibOut;
    s32 VibPow;
    u32 SE;
    s32 MSE1;
    s32 MSE2;
    s32 MSE3;
    s32 MSE4;
    s32 MSE5;
    char *VoiceName1;
    char *VoiceName2;
    char *VoiceName3;
    char *VoiceName4;
    char *VoiceName5;
    s32 LifeTime;
    f32 ActerOfsY;
    f32 RootPosDir;
    f32 RootPosLen;
    f32 RootPosY;
    f32 Size;
    s32 Flg;
};

static sBtlUnitEx_EX_TABLE_t *gExTable_T_TOKIKUM[17];
static sBtlUnitEx_EX_TABLE_t *gExTable_BS_TUTIGU;
static sBtlUnitEx_EX_TABLE_t *gExTable_BS_ITIMOK;
static sBtlUnitEx_EX_TABLE_t *gExTable_BS_RASUPU;
static sBtlUnitEx_EX_TABLE_t *gExTable_BS_LASTB1;
static sBtlUnitEx_EX_TABLE_t *gExTable_BS_CHOURI;
sBtlUnitEx_HDEFF_TABLE_t *gHDEffTable;
static SBTLSKILLHIT_TBL *gHittbl_Range_M;
static s32 LastBossTestCnt;
static s32 LastBossTestVer;

static void FootEff(SBTLUNIT_WORK *wk, f32 _DirOfs, f32 _PosLen, f32 _PosY, f32 _EffSize);
static void Update_Boss(SBTLUNIT_WORK *wk);

// 0x212c080
s32 sBtlUnitGetHDEffTable_SKLID(s32 _devilid, SKLID _SkillId, s32 _SkillNum) {
  s64 v7;
  s32 v8;
  sBtlUnitEx_HDEFF_TABLE_t *v10;

  v7 = 0;
  v8 = -1;
  while (1)
  {
    if (v7 >= SLODWORD(gHDEffTable->max_length))
      return v8;
    v10 = gHDEffTable[v7];
    if (v10->SkillId == SkillId)
    {
      if (v10->SkillNum == SkillNum)
        return v7;
    }
    ++v7;
  }
}

// 0x212c170
void sBtlUnitInit(SBTLUNIT_WORK *wk) {
  bool *UnitEx_DoneWork;

  UnitEx_DoneWork = wk->UnitEx_DoneWork;
  *(u64 *)&wk->UnitEx_Old_MotionNo = 0;
  wk->UnitEx_Old_MotionSerialNo = 0;
  if ((s32)UnitEx_DoneWork->max_length >= 1)
    sub_188E3B0(UnitEx_DoneWork, 0, (u32)UnitEx_DoneWork->max_length);
  wk->UnitEx_TableIndexTop = 9999;
}

// 0x212c1c0
bool sBtlUnitChkOverMotionSe(SBTLUNIT_WORK *wk) {
  return (wk->side & 0x80) == 0 && wk->hModel && wk->para->devilid == 257;
}

// 0x212c1f0
static void FootEff(SBTLUNIT_WORK *wk, f32 _DirOfs, f32 _PosLen, f32 _PosY, f32 _EffSize) {
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

// 0x212c340
void sBtlUnitUpdate(SBTLUNIT_WORK *wk) {
  s32 devilid;
  sBtlUnitEx_EX_TABLE_t *gExTable_T_TOKIKUM_local;
  struct sBtlUnitEx *p_gExTable_BS_LASTB1;
  dds3ModelHandle_t *hModel;
  f32 MotionFrameF;
  s32 UnitEx_Old_MotionNo;
  f32 v17;
  s32 motionID;
  s32 motionno;
  bool *UnitEx_DoneWork;
  il2cpp_array_size_t max_length;
  s64 v22;
  sBtlUnitEx_EX_TABLE_t *v23;
  s32 UnitEx_TableIndexTop;
  s32 v25;
  sBtlSub **v26;
  sbtl **v27;
  bool *v28;
  s64 v29;
  s64 v30;
  s64 v31;
  s64 *v32;
  s64 v33;
  bool *v34;
  s32 v35;
  f32 v36;
  f32 v37;
  f32 v38;
  f32 v39;
  s32 v40;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  s32 v45;
  u32 v46;
  s32 v47;
  f32 v48;
  f32 v49;
  f32 v50;
  f32 v51;
  f32 v52;
  f32 v53;
  SBTLSKILLHIT_TBL *v54;
  s64 v56;
  s32 v57;
  SBTLSKILLHIT_TBL *gHittbl_Range_M_local;
  f32 v59;
  SBTLDMG_CYLINDERWORK *cy;
  f32 v61;
  f32 Dir180;
  sbtl *v63;
  s32 ListID;
  s32 acterside;
  SBTLDMG_HITLISTWORK *hitList;
  s32 use_skillid;
  f32 v68;
  s32 v69;
  s32 v70;
  s64 v72;
  sBtlUnitEx_HDEFF_TABLE_t *v74;
  s32 v75;
  sBtlUnitEx_HDEFF_TABLE_t *v76;
  u32 v77;
  s32 v78;
  s32 v79;
  s32 v80;
  s32 v81;
  char *v82;
  s32 v83;
  sbtl **v84;
  sBtlSub **v85;
  s32 v86;
  u32 v87;
  void **v88;
  s32 v89;
  s32 v90;
  s32 v91;
  s32 v92;
  s32 motion_serialno;
  s32 acterID;
  SBTLSKILLP_TBL *tbl;
  sdfVector4_t v96;

  if ((wk->side & 0x80) != 0 || !wk->hModel)
    return;
  Update_Boss(wk);
  devilid = wk->para->devilid;
  if (devilid > 293)
    goto LABEL_7;
  if ((s16)devilid > 184)
  {
    gExTable_T_TOKIKUM_local = 0;
    switch (devilid)
    {
      case 257:
        p_gExTable_BS_LASTB1 = &gExTable_BS_LASTB1;
        goto LABEL_40;
      case 258:
      case 261:
        return;
      case 259:
        p_gExTable_BS_LASTB1 = &gExTable_BS_CHOURI;
        goto LABEL_40;
      case 260:
        goto LABEL_41;
      case 262:
        goto LABEL_18;
      default:
        if ((u16)devilid == 290)
          goto LABEL_34;
        if ((u16)devilid == 293)
          goto LABEL_31;
        return;
    }
  }
  if ((u16)devilid != 102)
  {
    if ((u16)devilid != 184)
      return;
    goto LABEL_26;
  }
LABEL_31:
  p_gExTable_BS_LASTB1 = &gExTable_BS_TUTIGU;
  goto LABEL_40;
LABEL_7:
  if ((u32)devilid <= 0x12C)
  {
    if (devilid == 297)
    {
LABEL_34:
      p_gExTable_BS_LASTB1 = &gExTable_BS_ITIMOK;
    }
    else
    {
      if ((u16)devilid != 300)
        return;
LABEL_18:
      p_gExTable_BS_LASTB1 = &gExTable_BS_RASUPU;
    }
    goto LABEL_40;
  }
  if ((devilid & 0xFFFFFFFE) != 0x13A)
  {
    if (devilid != 316)
    {
      if ((u16)devilid != 475)
        return;
LABEL_26:
LABEL_40:
      gExTable_T_TOKIKUM_local = gExTable_T_TOKIKUM;
      goto LABEL_41;
    }
    goto LABEL_31;
  }
  gExTable_T_TOKIKUM_local = 0;
LABEL_41:
  hModel = wk->hModel;
  MotionFrameF = mdlGetMotionFrameF(hModel);
  UnitEx_Old_MotionNo = wk->UnitEx_Old_MotionNo;
  v17 = MotionFrameF;
  if (UnitEx_Old_MotionNo == wk->motionno && MotionFrameF < wk->UnitEx_Old_MotionFrame && wk->UnitEx_Old_MotionSerialNo != wk->motion_serialno)
  {
    motionID = wk->motionID;
    if (sBtlCheckLoopMotion(wk, motionID))
    {
      UnitEx_Old_MotionNo = wk->UnitEx_Old_MotionNo;
    }
    else
    {
      UnitEx_Old_MotionNo = 0;
      wk->UnitEx_Old_MotionNo = 0;
    }
  }
  motionno = wk->motionno;
  if (UnitEx_Old_MotionNo != motionno && gExTable_T_TOKIKUM_local)
  {
    UnitEx_DoneWork = wk->UnitEx_DoneWork;
    if ((s32)UnitEx_DoneWork->max_length >= 1)
      sub_188E3B0(UnitEx_DoneWork, 0, (u32)UnitEx_DoneWork->max_length);
    max_length = gExTable_T_TOKIKUM_local->max_length;
    wk->UnitEx_TableIndexTop = 9999;
    if ((s32)max_length >= 1)
    {
      v22 = 0;
      while (1)
      {
        v23 = gExTable_T_TOKIKUM_local[v22];
        if (v23->Command == 1 && v23->MotionNo == motionno)
          break;
        if ((u32)max_length == ++v22)
          goto LABEL_61;
      }
      wk->UnitEx_TableIndexTop = v22;
    }
  }
LABEL_61:
  if (UnitEx_Old_MotionNo == motionno)
  {
    if (gExTable_T_TOKIKUM_local)
    {
      UnitEx_TableIndexTop = wk->UnitEx_TableIndexTop;
      motionno = UnitEx_Old_MotionNo;
      v25 = gExTable_T_TOKIKUM_local->max_length;
      if (UnitEx_TableIndexTop < v25)
      {
        v26 = &sBtlSub;
        v27 = &sbtl;
        v28 = wk->UnitEx_DoneWork;
        while (1)
        {
          v29 = (s64)gExTable_T_TOKIKUM_local + 8 * UnitEx_TableIndexTop;
          v30 = UnitEx_TableIndexTop - wk->UnitEx_TableIndexTop;
          v33 = *(u64 *)(v29 + 32);
          v32 = (v29 + 32);
          v31 = v33;
          v34 = &v28[v30];
          v35 = *(u32 *)(v33 + 16);
          if (*v34)
          {
            if (v35 == 200 && v17 < wk->UnitEx_Old_MotionFrame)
              *v34 = 0;
          }
          else
          {
            if (v35 <= 41)
            {
              switch (v35)
              {
                case 1:
                  *v34 = 1;
                  goto LABEL_190;
                case 2:
                  goto LABEL_191;
                case 8:
                  if (v17 < (f32)*(s32 *)(v31 + 28))
                    goto LABEL_190;
                  tbl = sBtlGetSkilltbl(wk->actwk->use_skillid);
                  v54 = Allocate(SBTLSKILLHIT_TBL);
                  _ctor(v54, 0);
                  v56 = *v32;
                  v57 = wk->motionno;
                  gHittbl_Range_M_local = gHittbl_Range_M;
                  gHittbl_Range_M_local->lifetime = *(u32 *)(*v32 + 136);
                  v59 = *(f32 *)(v56 + 156);
                  cy = gHittbl_Range_M_local->cy;
                  gHittbl_Range_M_local->motionno = v57;
                  v61 = *(f32 *)(v56 + 144);
                  gHittbl_Range_M_local->area_r = v59;
                  cy->area_r = v59;
                  Dir180 = sBtlGetDir180(v61);
                  sBtlGetMoveXZ(0.0, 0.0, Dir180, *(f32 *)(*v32 + 148), &gHittbl_Range_M_local->x, &gHittbl_Range_M_local->z);
                  v63 = *v27;
                  v63 = *v27;
                  ListID = wk->ListID;
                  acterside = wk->side;
                  hitList = wk->hitList;
                  use_skillid = wk->actwk->use_skillid;
                  acterID = wk->ListID;
                  ListID = acterID;
                  sBtlCreateHitC_New(hitList, wk, 0, ListID, use_skillid, tbl, gHittbl_Range_M_local, 0, acterside, -1);
                  sBtlAddSerialID2();
                  v68 = *(f32 *)(*v32 + 140);
                  v28 = wk->UnitEx_DoneWork;
                  wk->hstatus &= ~0x20000u;
                  wk->damage_ActerOfsY = v68;
                  goto LABEL_173;
                case 11:
                  if (v17 < (f32)*(s32 *)(v31 + 28))
                    goto LABEL_190;
                  v69 = *(u32 *)(v31 + 40);
                  v70 = wk->actwk->use_skillid;
                  v72 = 0;
                  while (2)
                  {
                    if (v72 < SLODWORD(gHDEffTable->max_length))
                    {
                      v74 = gHDEffTable[v72];
                      if (v74->SkillId != v70 || v74->SkillNum != v69)
                      {
                        ++v72;
                        continue;
                      }
                      if (v72 != 0xFFFFFFFFLL)
                      {
                        v75 = wk->ListID;
                        wk->SlashSkillID = wk->actwk->use_skillid;
                        v76 = gHDEffTable[v72];
                        wk->SlashUID = AW_SlashAdd(v75, v76->RootPosDir, v76->RootPosLen, v76->RootPosY, v76->RootRotX, v76->RootRotY, v76->RootRotZ, v76->Speed, v76->Size, v76->PrefabIdx);
                      }
                    }
                    break;
                  }
                  v28 = wk->UnitEx_DoneWork;
                  v28[v30] = 1;
                  v25 = UnitEx_TableIndexTop;
                  v26 = &sBtlSub;
                  v27 = &sbtl;
                  goto LABEL_191;
                case 20:
                  if (v17 < (f32)*(s32 *)(v31 + 28))
                    goto LABEL_190;
                  v77 = *(u32 *)(v31 + 68);
                  x = wk->pos.x;
                  y = wk->pos.y;
                  z = wk->pos.z;
                  w = wk->pos.w;
                  v46 = v77;
                  goto LABEL_87;
                case 21:
                  if (v17 < (f32)*(s32 *)(v31 + 28))
                    goto LABEL_190;
                  x = wk->pos.x;
                  y = wk->pos.y;
                  z = wk->pos.z;
                  w = wk->pos.w;
                  v46 = 65553;
                  goto LABEL_87;
                case 22:
                  if (v17 < (f32)*(s32 *)(v31 + 28))
                    goto LABEL_190;
                  v78 = sub_1905740(4, 0);
                  x = wk->pos.x;
                  y = wk->pos.y;
                  z = wk->pos.z;
                  w = wk->pos.w;
                  v79 = v78;
                  v46 = v79 + 65634;
                  goto LABEL_87;
                case 23:
                  if (v17 < (f32)*(s32 *)(v31 + 28))
                    goto LABEL_190;
                  v80 = sub_1905740(2, 0);
                  if (v80 == 1)
                    goto LABEL_174;
                  goto LABEL_143;
                case 24:
                  if (v17 < (f32)*(s32 *)(v31 + 28))
                    goto LABEL_190;
                  v80 = sub_1905740(3, 0);
                  if (v80 == 2)
                  {
LABEL_176:
                    v81 = *(u32 *)(*v32 + 80);
                  }
                  else if (v80 == 1)
                  {
LABEL_174:
                    v81 = *(u32 *)(*v32 + 76);
                  }
                  else
                  {
LABEL_143:
                    if (v80)
                      break;
LABEL_149:
                    v81 = *(u32 *)(*v32 + 72);
                  }
LABEL_181:
                  sBtlPlayMotionSE(wk, v81, 0);
                  break;
                case 25:
                  if (v17 < (f32)*(s32 *)(v31 + 28))
                    goto LABEL_190;
                  switch ((u32)sub_1905740(4, 0))
                  {
                    case 0u:
                      goto LABEL_149;
                    case 1u:
                      goto LABEL_174;
                    case 2u:
                      goto LABEL_176;
                    case 3u:
                      goto LABEL_178;
                    default:
                      goto LABEL_188;
                  }
                  break;
                case 26:
                  if (v17 < (f32)*(s32 *)(v31 + 28))
                    goto LABEL_190;
                  switch ((u32)sub_1905740(5, 0))
                  {
                    case 0u:
                      goto LABEL_149;
                    case 1u:
                      goto LABEL_174;
                    case 2u:
                      goto LABEL_176;
                    case 3u:
LABEL_178:
                      v81 = *(u32 *)(*v32 + 84);
                      goto LABEL_181;
                    case 4u:
                      v81 = *(u32 *)(*v32 + 88);
                      goto LABEL_181;
                    default:
                      goto LABEL_188;
                  }
                  break;
                case 27:
                  if (v17 < (f32)*(s32 *)(v31 + 28))
                    goto LABEL_190;
                  v82 = *(char **)(v31 + 96);
                  goto LABEL_185;
                case 28:
                  if (v17 < (f32)*(s32 *)(v31 + 28))
                    goto LABEL_190;
                  v83 = sub_1905740(2, 0);
                  if (v83 == 1)
                    goto LABEL_175;
                  goto LABEL_158;
                case 29:
                  if (v17 < (f32)*(s32 *)(v31 + 28))
                    goto LABEL_190;
                  v83 = sub_1905740(3, 0);
                  if (v83 == 2)
                  {
LABEL_177:
                    v82 = *(char **)(*v32 + 112);
                  }
                  else if (v83 == 1)
                  {
LABEL_175:
                    v82 = *(char **)(*v32 + 104);
                  }
                  else
                  {
LABEL_158:
                    if (v83)
                      break;
LABEL_164:
                    v82 = *(char **)(*v32 + 96);
                  }
LABEL_185:
                  sndVoicePlayFile(v82, 0);
                  break;
                case 30:
                  if (v17 < (f32)*(s32 *)(v31 + 28))
                    goto LABEL_190;
                  switch ((u32)sub_1905740(4, 0))
                  {
                    case 0u:
                      goto LABEL_164;
                    case 1u:
                      goto LABEL_175;
                    case 2u:
                      goto LABEL_177;
                    case 3u:
                      goto LABEL_179;
                    default:
                      goto LABEL_188;
                  }
                  break;
                case 31:
                  if (v17 < (f32)*(s32 *)(v31 + 28))
                    goto LABEL_190;
                  switch ((u32)sub_1905740(5, 0))
                  {
                    case 0u:
                      goto LABEL_164;
                    case 1u:
                      goto LABEL_175;
                    case 2u:
                      goto LABEL_177;
                    case 3u:
LABEL_179:
                      v82 = *(char **)(*v32 + 120);
                      goto LABEL_185;
                    case 4u:
                      v82 = *(char **)(*v32 + 128);
                      goto LABEL_185;
                    default:
                      goto LABEL_188;
                  }
                  break;
                case 40:
                  if (v17 < (f32)*(s32 *)(v31 + 28))
                    goto LABEL_190;
                  v84 = v27;
                  v85 = v26;
                  v86 = *(u32 *)(v31 + 44);
                  v87 = *(u32 *)(v31 + 48);
                  dds3SetQuake(v86, v87);
                  v28 = wk->UnitEx_DoneWork;
                  v26 = v85;
                  v27 = v84;
                  goto LABEL_189;
                case 41:
                  if (v17 < (f32)*(s32 *)(v31 + 28))
                    goto LABEL_190;
                  v88 = v26;
                  v89 = *(u32 *)(v31 + 52);
                  v90 = *(u32 *)(v31 + 56);
                  v91 = *(u32 *)(v31 + 60);
                  v92 = *(u32 *)(v31 + 64);
                  if (!*((u32 *)*v88 + 56))
                  SetVibe(v89, v90, v91, v92);
                  v28 = wk->UnitEx_DoneWork;
LABEL_173:
                  v28[v30] = 1;
                  v26 = &sBtlSub;
                  v27 = &sbtl;
                  v25 = UnitEx_TableIndexTop;
                  goto LABEL_191;
                default:
                  goto LABEL_190;
              }
            }
            else
            {
              if ((u32)v35 <= 0x82)
              {
                v25 = UnitEx_TableIndexTop;
                switch (v35)
                {
                  case 105:
                    if (v17 < (f32)*(s32 *)(v31 + 28))
                      goto LABEL_190;
                    Add_Kaya(wk->ListID);
                    goto LABEL_188;
                  case 106:
                    if (v17 < (f32)*(s32 *)(v31 + 28))
                      goto LABEL_190;
                    v47 = wk->ListID;
                    v48 = *(f32 *)(v31 + 144);
                    v49 = *(f32 *)(v31 + 148);
                    wk->SlashSkillID = wk->actwk->use_skillid;
                    wk->SlashUID = AW_ApproachAdd_Kaya(v47, v48, v49);
                    goto LABEL_188;
                  case 107:
                  case 108:
                  case 110:
                  case 111:
                  case 112:
                  case 113:
                  case 114:
                  case 115:
                  case 116:
                  case 117:
                  case 118:
                  case 119:
                  case 120:
                  case 121:
                  case 122:
                  case 123:
                  case 124:
                  case 125:
                  case 126:
                  case 127:
                  case 128:
                  case 129:
                    goto LABEL_191;
                  case 109:
                    if (v17 < (f32)*(s32 *)(v31 + 28))
                      goto LABEL_190;
                    Add(wk->ListID, *(f32 *)(v31 + 144), *(f32 *)(v31 + 148), *(f32 *)(v31 + 156), 0);
                    goto LABEL_188;
                  case 130:
                    if (v17 < (f32)*(s32 *)(v31 + 28))
                      goto LABEL_190;
                    v50 = *(f32 *)(v31 + 144);
                    v51 = *(f32 *)(v31 + 148);
                    v52 = *(f32 *)(v31 + 152);
                    v53 = *(f32 *)(v31 + 156);
                    FootEff(wk, v50, v51, v52);
                    goto LABEL_188;
                  default:
                    goto LABEL_190;
                }
              }
              if (v35 == 200)
              {
                if (v17 < (f32)*(s32 *)(v31 + 28))
                  goto LABEL_190;
                v36 = *(f32 *)(v31 + 144);
                v37 = *(f32 *)(v31 + 148);
                v38 = *(f32 *)(v31 + 152);
                v39 = *(f32 *)(v31 + 156);
                FootEff(wk, v36, v37, v38);
              }
              else if (v35 != 201 || v17 < (f32)*(s32 *)(v31 + 28))
              {
                goto LABEL_190;
              }
              v40 = sub_1905740(4, 0);
              x = wk->pos.x;
              y = wk->pos.y;
              z = wk->pos.z;
              w = wk->pos.w;
              v45 = v40;
              v46 = v45 + 65542;
LABEL_87:
              v96.x = x;
              v96.y = y;
              v96.z = z;
              v96.w = w;
              sBtlPlay3DSE(v46, v96);
            }
LABEL_188:
            v28 = wk->UnitEx_DoneWork;
LABEL_189:
            v28[v30] = 1;
          }
LABEL_190:
          v25 = UnitEx_TableIndexTop;
LABEL_191:
          UnitEx_TableIndexTop = v25 + 1;
          v25 = gExTable_T_TOKIKUM_local->max_length;
          if (UnitEx_TableIndexTop >= v25)
          {
            motionno = wk->motionno;
            break;
          }
        }
      }
    }
  }
  motion_serialno = wk->motion_serialno;
  wk->UnitEx_Old_MotionNo = motionno;
  wk->UnitEx_Old_MotionFrame = v17;
  wk->UnitEx_Old_MotionSerialNo = motion_serialno;
}

// 0x212d080
static void Update_Boss(SBTLUNIT_WORK *wk) {
  dds3ModelHandle_t *hModel;
  f32 MotionFrameF;
  s32 devilid;
  s32 v6;
  f32 *v7;
  f32 *v8;
  f32 *v9;
  s32 v10;
  bool *SubCylinder_Use;
  s32 motionno;
  SBATTLE_WORK *v14;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 playerID;
  SBTLUNIT_WORK *v17;
  SBTLUNIT_WORK *UnitFromDevilID;
  SBTLUNIT_WORK *v19;
  s32 v20;
  u32 status;
  f32 *v22;
  f32 *v23;
  u32 v24;
  f32 *v25;
  f32 *v26;
  s32 v27;
  f32 *SubCylinder_PosDir;
  f32 *SubCylinder_PosLen;
  f32 *SubCylinder_Size;
  s32 v31;
  f32 v32;
  u32 v33;
  f32 *v34;
  f32 *v35;
  f32 *v36;
  f32 *v37;
  f32 *v38;
  f32 *v39;
  f32 *v40;
  f32 *v41;
  bool *v42;

  if ((wk->side & 0x80) != 0)
    return;
  hModel = wk->hModel;
  if (!hModel)
    return;
  MotionFrameF = mdlGetMotionFrameF(hModel);
  devilid = wk->para->devilid;
  if (devilid != 184)
  {
    switch (wk->para->devilid)
    {
      case 0x101:
      case 0x104:
        return;
      case 0x102:
        SubCylinder_Use = wk->SubCylinder_Use;
        *(u16 *)SubCylinder_Use = 0;
        motionno = wk->motionno;
        if (motionno != 22)
        {
          if (motionno == 24)
          {
            if (MotionFrameF >= 34.0)
              return;
          }
          else if (motionno != 23 || MotionFrameF <= 90.0)
          {
            return;
          }
        }
        v27 = 1122369536;
        *(u16 *)SubCylinder_Use = 257;
        SubCylinder_PosDir = wk->SubCylinder_PosDir;
        SubCylinder_PosLen = wk->SubCylinder_PosLen;
        SubCylinder_PosDir[0] = 145.0;
        SubCylinder_PosLen[0] = 1250.0;
        SubCylinder_Size = wk->SubCylinder_Size;
        SubCylinder_Size[0] = 115.0;
        SubCylinder_PosDir[1] = 208.0;
        v31 = 1150435328;
        goto LABEL_48;
      case 0x103:
        v14 = wk;
        UnitMng = v14->UnitMng;
        playerID = v14->playerID;
        v17 = sBtlSearchUnit_ID(UnitMng, playerID);
        UnitFromDevilID = sBtlGetUnitFromDevilID(312);
        v19 = sBtlGetUnitFromDevilID(313);
        v20 = wk->motionno;
        if (v20 == 20 && MotionFrameF >= 27.0 && MotionFrameF < 100.0)
        {
          if (UnitFromDevilID)
          {
            UnitFromDevilID->status |= 1u;
            *(u16 *)UnitFromDevilID->SubCylinder_Use = 0;
          }
          if (!v19)
            return;
          status = v19->status;
        }
        else
        {
          if (v20 == 20 && MotionFrameF > 25.0 && MotionFrameF < 140.0)
          {
            if (UnitFromDevilID)
            {
              UnitFromDevilID->status &= ~1u;
              *(u16 *)UnitFromDevilID->SubCylinder_Use = 0;
            }
            if (!v19)
              return;
            v24 = v19->status & 0xFFFFFFFE;
LABEL_60:
            v19->status = v24;
            *(u16 *)v19->SubCylinder_Use = 0;
            return;
          }
          v32 = v17->pos.y + v17->JumpOfsPos.y;
          if (UnitFromDevilID)
          {
            v33 = UnitFromDevilID->status;
            if (UnitFromDevilID->pos.y >= (f32)(v32 + -250.0))
            {
              UnitFromDevilID->status = v33 & 0xFFFFFFFE;
              *(u16 *)UnitFromDevilID->SubCylinder_Use = 257;
              v35 = UnitFromDevilID->SubCylinder_PosDir;
              v36 = UnitFromDevilID->SubCylinder_PosLen;
              v35[0] = 135.0;
              v36[0] = 350.0;
              v37 = UnitFromDevilID->SubCylinder_Size;
              v37[0] = 300.0;
              v35[1] = 148.0;
              v36[1] = 800.0;
              v37[1] = 300.0;
            }
            else
            {
              UnitFromDevilID->status = v33 | 1;
              *(u16 *)UnitFromDevilID->SubCylinder_Use = 0;
            }
          }
          if (!v19)
            return;
          status = v19->status;
          if (v19->pos.y >= (f32)(v32 + -250.0))
          {
            v19->status = status & 0xFFFFFFFE;
            v27 = 1133903872;
            *(u16 *)v19->SubCylinder_Use = 257;
            v38 = v19->SubCylinder_PosDir;
            SubCylinder_PosLen = v19->SubCylinder_PosLen;
            v38[0] = 220.0;
            SubCylinder_PosLen[0] = 350.0;
            SubCylinder_Size = v19->SubCylinder_Size;
            SubCylinder_Size[0] = 300.0;
            v38[1] = 210.0;
            v31 = 1143111680;
            goto LABEL_48;
          }
        }
        v24 = status | 1;
        goto LABEL_60;
      default:
        if (devilid == 475)
          break;
        return;
    }
  }
  v6 = wk->motionno;
  if (v6 == 12)
    goto LABEL_53;
  if (v6 != 6)
  {
    if (v6 == 2)
    {
      *(u16 *)wk->SubCylinder_Use = 257;
      v7 = wk->SubCylinder_PosDir;
      v8 = wk->SubCylinder_PosLen;
      v7[0] = 205.0;
      v8[0] = 160.0;
      v9 = wk->SubCylinder_Size;
      v9[0] = 70.0;
      v10 = 1129906176;
LABEL_16:
      LODWORD(v7[1]) = v10;
      v8[1] = 250.0;
      v9[1] = 40.0;
      return;
    }
LABEL_15:
    *(u16 *)wk->SubCylinder_Use = 257;
    v7 = wk->SubCylinder_PosDir;
    v8 = wk->SubCylinder_PosLen;
    v7[0] = 190.0;
    v8[0] = 160.0;
    v9 = wk->SubCylinder_Size;
    v9[0] = 75.0;
    v10 = 1129119744;
    goto LABEL_16;
  }
  if (MotionFrameF < 1.0)
    goto LABEL_15;
  if (MotionFrameF < 4.0)
  {
    *(u16 *)wk->SubCylinder_Use = 1;
    v22 = wk->SubCylinder_PosLen;
    wk->SubCylinder_PosDir[0] = 190.0;
    v23 = wk->SubCylinder_Size;
    v22[0] = 160.0;
    v23[0] = 75.0;
    return;
  }
  if (MotionFrameF < 10.0)
  {
    *(u16 *)wk->SubCylinder_Use = 1;
    v25 = wk->SubCylinder_PosLen;
    wk->SubCylinder_PosDir[0] = 200.0;
    v26 = wk->SubCylinder_Size;
    v25[0] = 155.0;
    v26[0] = 40.0;
    return;
  }
  if (MotionFrameF < 35.0)
    goto LABEL_53;
  if (MotionFrameF < 42.0)
  {
    v27 = 1117782016;
    *(u16 *)wk->SubCylinder_Use = 257;
    v34 = wk->SubCylinder_PosDir;
    SubCylinder_PosLen = wk->SubCylinder_PosLen;
    v34[0] = 3.0;
    SubCylinder_PosLen[0] = 180.0;
    SubCylinder_Size = wk->SubCylinder_Size;
    SubCylinder_Size[0] = 80.0;
    v34[1] = 4.0;
    v31 = 1135542272;
LABEL_48:
    LODWORD(SubCylinder_PosLen[1]) = v31;
    LODWORD(SubCylinder_Size[1]) = v27;
    return;
  }
  if (MotionFrameF < 50.0)
  {
LABEL_53:
    *(u16 *)wk->SubCylinder_Use = 0;
    return;
  }
  v39 = wk->SubCylinder_PosDir;
  v40 = wk->SubCylinder_PosLen;
  v39[0] = 190.0;
  v41 = wk->SubCylinder_Size;
  v40[0] = 160.0;
  v42 = wk->SubCylinder_Use;
  v42[0] = 1;
  v41[0] = 75.0;
  if (MotionFrameF >= 55.0)
  {
    v42[1] = 1;
    v39[1] = 205.0;
    v40[1] = 250.0;
    v41[1] = 40.0;
  }
  else
  {
    v42[1] = 0;
  }
}
