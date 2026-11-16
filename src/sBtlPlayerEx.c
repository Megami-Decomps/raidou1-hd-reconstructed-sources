#include "types.h"
#include "SBTL_MODE.h"
#include "SBWEAPON_TYPE.h"
#include "SKLID.h"
#include "aw_approach.h"
#include "aw_approachatk.h"
#include "aw_bulletmuzzle.h"
#include "aw_down.h"
#include "aw_jumpattack2l.h"
#include "aw_jumpkick1.h"
#include "aw_jumpkick2.h"
#include "aw_kudaopen.h"
#include "aw_magax.h"
#include "aw_magguardax.h"
#include "aw_magguardlc.h"
#include "aw_magguardsd.h"
#include "aw_maglc.h"
#include "aw_magsd.h"
#include "aw_mawasikeri.h"
#include "aw_sbattle.h"
#include "aw_setsuma1.h"
#include "aw_setsuma2.h"
#include "aw_shockwave1.h"
#include "aw_slash.h"
#include "aw_tame.h"
#include "dds3kerneldraw.h"
#include "dds3vrf.h"
#include "mdl.h"
#include "sbtl.h"
#include "sbtlcamera.h"
#include "sbtldmg.h"
#include "sbtleff.h"
#include "sbtlplayer.h"
#include "sbtlplayer_jigenkiri.h"
#include "sbtlplayer_spirit.h"
#include "sbtlplayerex.h"
#include "sbtlplayertbl.h"
#include "sbtlscene.h"
#include "sbtlskill.h"
#include "sbtlsound.h"
#include "sbtlstp.h"
#include "sbtlsub.h"
#include "sbtlunit.h"
#include "sbtlweapon.h"
#include "sdf_vu0.h"
#include "sdfquat.h"
#include "sndmanager.h"

#define COMMAND_NULL 0
#define COMMAND_SECTION_ST 1
#define COMMAND_SECTION_ED 2
#define COMMAND_HIT_SD 5
#define COMMAND_HIT_SD_F 6
#define COMMAND_HIT_RANGE 7
#define COMMAND_HIT_RANGE_F 8
#define COMMAND_HIT_RANGE_S 9
#define COMMAND_HIT_RANGE_T 10
#define COMMAND_HIT_PLUS 11
#define COMMAND_HIT_DELETE 12
#define COMMAND_EFF_SLASH 13
#define COMMAND_EFF_A 14
#define COMMAND_EFF_B 15
#define COMMAND_EFF_C 16
#define COMMAND_SE_A 20
#define COMMAND_SE_V 21
#define COMMAND_SE_2D 22
#define COMMAND_SE_TUKI 23
#define COMMAND_SE_KIRI 24
#define COMMAND_V_SORD 25
#define COMMAND_V_DMG 26
#define COMMAND_V_SETSUMA 27
#define COMMAND_V_HUUMA 28
#define COMMAND_V_LC_HCOMBO2 29
#define COMMAND_V_VICTORY 30
#define COMMAND_V_KAIHI 31
#define COMMAND_VOICE 32
#define COMMAND_QUAKE 40
#define COMMAND_QUAKESTOP 41
#define COMMAND_PADVIB 42
#define COMMAND_ROT180 50
#define COMMAND_COLLISION_ON 51
#define COMMAND_COLLISION_OFF 52
#define COMMAND_TGT_OFF 53
#define COMMAND_MANT_ON 55
#define COMMAND_MANT_OFF 56
#define COMMAND_OIUCHI_MUTEKI_ON 60
#define COMMAND_OIUCHI_MUTEKI_OFF 61
#define COMMAND_SETSUMA_BEGIN 62
#define COMMAND_SETSUMA_HIT 64
#define COMMAND_SETSUMA_TEON 65
#define COMMAND_SETSUMA_DOF_END 66
#define COMMAND_SETSUMA_JYUSO_OFF 67
#define COMMAND_SETSUMA_BAD_OFF 68
#define COMMAND_CAM_MV 70
#define COMMAND_CAM_BLAND 71
#define COMMAND_CAM_RESET 72
#define COMMAND_CAM_MV2 73
#define COMMAND_CAM_JUMP 75
#define COMMAND_CAM_JUMPSTOP 76
#define COMMAND_CAM_JUMPCONT 77
#define COMMAND_CAM_JUMP2 78
#define COMMAND_CAM_RECALC 79
#define COMMAND_COMBI_EOFF 82
#define COMMAND_COMBI_EON 83
#define COMMAND_COMBI_EPOS 84
#define COMMAND_COMBI_EHPOFF 85
#define COMMAND_COMBI_EHPON 86
#define COMMAND_COMBI_EFFDEL 87
#define COMMAND_COMBI_ENDMOT 88
#define COMMAND_COMBI_ENDMOT2 89
#define COMMAND_COMBI_NOFF 90
#define COMMAND_COMBI_NON 91
#define COMMAND_COMBI_NHPOFF 92
#define COMMAND_COMBI_NHPON 93
#define COMMAND_EFF_SHOCKWAVE1 100
#define COMMAND_EFF_JUMPKICK1 101
#define COMMAND_EFF_JUMPKICK1A 102
#define COMMAND_EFF_JUMPKICK2 103
#define COMMAND_EFF_JUMPKICK2A 104
#define COMMAND_EFF_JUMPHATK1 105
#define COMMAND_EFF_APPROACH 106
#define COMMAND_EFF_APPROACHA 107
#define COMMAND_EFF_MAWASIKERI 108
#define COMMAND_EFF_JUMPATK2L 109
#define COMMAND_EFF_DOWN 110
#define COMMAND_EFF_SETSUMA1ED 111
#define COMMAND_EFF_SETSUMA2 112
#define COMMAND_EFF_SETSUMA3 113
#define COMMAND_FLG_NULL 0
#define COMMAND_FLG_NOHOKAN 1
#define COMMAND_FLG_HTGT_OFF 2
#define COMMAND_FLG_FOV 4
#define COMMAND_FLG_CAMST_U 8
#define COMMAND_FLG_CAMST_E 16
#define COMMAND_FLG_CAMOFSY_U 32
#define COMMAND_FLG_CAMMV_PP 64
#define COMMAND_FLG_CAMMV_LL 128
#define COMMAND_FLG_CAMMV_DLY 256
#define COMMAND_FLG_TGTST_U 512
#define COMMAND_FLG_TGTST_UXZ 1024
#define COMMAND_FLG_TGTST_E 2048
#define COMMAND_FLG_TGTOFSY_U 4096
#define COMMAND_FLG_TGTMV_PP 8192
#define COMMAND_FLG_TGTMV_NE 16384
#define COMMAND_FLG_TGTMV_NPL 32768
#define COMMAND_FLG_TGTMV_PL 65536
#define COMMAND_FLG_ENC_03C 131072
#define COMMAND_FLG_ENC_03C_NO 262144
#define COMMAND_FLG_JIGENKIRI 524288
#define COMMAND_FLG_NOHITBK 16777216
#define COMMAND_FLG_NODMGMOT 33554432
#define COMMAND_FLG_SKLY70OVER 67108864
#define COMMAND_FLG_SKLY70UNDER 134217728
#define DONEWORK_MAX 64

typedef struct EX_CAMJUMP_t EX_CAMJUMP_t;
typedef struct EX_CAMMV_t EX_CAMMV_t;
typedef struct SBTLSKILLHIT_TBL SBTLSKILLHIT_TBL;
typedef struct SBTLUNIT_WORK SBTLUNIT_WORK;
typedef struct sBtlPlayerEx_EX_TABLE_t sBtlPlayerEx_EX_TABLE_t;

struct sBtlPlayerEx_EX_TABLE_t {
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
    s32 SE_Vol;
    char *VoiceName;
    s32 LifeTime;
    f32 ActerOfsY;
    f32 RootPosDir;
    f32 RootPosLen;
    f32 Size;
    f32 Speed;
    SKLID SklID;
    s32 Flg;
    f32 CamEFrame;
    f32 CamMode;
    f32 CamSX;
    f32 CamSY;
    f32 CamSZ;
    f32 CamEX;
    f32 CamEY;
    f32 CamEZ;
    f32 CamSFov;
    f32 CamEFov;
    f32 CamSUpV;
    f32 CamEUpV;
    f32 CamSLen;
    f32 CamELen;
    f32 CamSOfsY;
    f32 CamEOfsY;
    f32 CamSDir;
    f32 CamEDir;
    f32 CamEYDir;
    f32 CamTgtSX;
    f32 CamTgtSY;
    f32 CamTgtSZ;
    f32 CamTgtEX;
    f32 CamTgtEY;
    f32 CamTgtEZ;
    f32 CamTgtSOfsY;
    f32 CamTgtEOfsY;
    f32 CamJumpSpdS;
    f32 CamJumpSpdD;
};

struct EX_CAMMV_t {
    bool Use;
    s32 MotionNo;
    f32 TimeNomal;
    f32 SFrame;
    f32 EFrame;
    s32 Flg;
    bool BlandMode;
    f32 CamMode;
    f32 SX;
    f32 SY;
    f32 SZ;
    f32 EX;
    f32 EY;
    f32 EZ;
    f32 SFov;
    f32 EFov;
    f32 SUpV;
    f32 EUpV;
    f32 SLen;
    f32 ELen;
    f32 SOfsY;
    f32 EOfsY;
    f32 SDir;
    f32 EDir;
    f32 CamSYDir;
    f32 CamEYDir;
    f32 TgtSX;
    f32 TgtSY;
    f32 TgtSZ;
    f32 TgtEX;
    f32 TgtEY;
    f32 TgtEZ;
    s32 TgtUnitID;
    f32 TgtSOfsY;
    f32 TgtEOfsY;
    bool ToResultMode;
};

struct EX_CAMJUMP_t {
    bool Use;
    bool Pause;
    f32 Time;
    f32 Y;
    f32 Speed;
    f32 CamJumpSpdS;
    f32 CamJumpSpdD;
};

static s32 gOld_MotionNo;
static f32 gOld_MotionFrame;
static s32 gOld_MotionSerialNo;
static s32 gSame_MotionCount;
static sBtlPlayerEx_EX_TABLE_t *gExTable;
static SBTLSKILLHIT_TBL *gHittbl_Sd;
static SBTLSKILLHIT_TBL *gHittbl_Sd_f;
static SBTLSKILLHIT_TBL *gHittbl_Range;
static SBTLSKILLHIT_TBL *gHittbl_Range_M;
static SBTLSKILLHIT_TBL *gHittbl_Range_S;
static SBTLSKILLHIT_TBL *gHittbl_Range_T;
static SBTLSKILLHIT_TBL *gHittbl_Setsuma;
static bool *gDoneWork;
static s32 gTableIndexTop;
static f32 gTime;
static EX_CAMMV_t *gCamMv;
static EX_CAMJUMP_t *gCamJump;
static EX_CAMJUMP_t *gCamJump2;
static s32 gTuugiZokusei;
static s32 gDebug_Tuugizan_Zokusei;
static s32 gDebug_Tuugitotu_Zokusei;
static s32 gDebug_Tuugikai_Zokusei;
static s32 gDebug_Bg_Zokusei;
static s32 gSkillNum;

static void CamMvUpdate(SBTLUNIT_WORK *wk);
static void CamJumpUpdate(SBTLUNIT_WORK *wk);
static void CamJumpUpdate2(SBTLUNIT_WORK *wk);

// 0x20c95e0
void sBtlPlayerInit(void) {
  EX_CAMMV_t *gCamMv_local;

  *(u64 *)&gTableIndexTop = 9999;
  gCamMv_local = gCamMv;
  *(u64 *)&gOld_MotionNo = 0;
  *(u64 *)&gCamMv_local->MotionNo = 0;
  gCamMv_local->Use = 0;
  gCamMv_local->ToResultMode = 0;
  *(u16 *)&gCamJump->Use = 0;
  gCamJump2->Use = 0;
}

// 0x20c9670
static void CamMvUpdate(SBTLUNIT_WORK *wk) {
  EX_CAMMV_t *v8;
  f32 SFrame;
  f32 v10;
  f32 v11;

  if (!gCamMv->Use)
    return;
  if (!gCamMv->ToResultMode)
  {
    if (gCamMv->EFrame < gOld_MotionFrame)
    {
      gCamMv->Use = 0;
      return;
    }
  }
  v8 = gCamMv;
  SFrame = v8->SFrame;
  if (gOld_MotionFrame <= SFrame)
  {
    v8->TimeNomal = 0.0;
    return;
  }
  v8 = gCamMv;
  SFrame = v8->SFrame;
  v10 = v8->EFrame - SFrame;
  if (v10 != 0.0)
  {
    v11 = gOld_MotionFrame - SFrame;
    v8->TimeNomal = v11 / v10;
  }
}

// 0x20c9890
bool sBtlPlayerGetCamMv(f32 *_TX, f32 *_TY, f32 *_TZ, f32 *_CX, f32 *_CY, f32 *_CZ, f32 *_Fov, f32 *_UpV, f32 *_AngleX, const sdfVector4_t *_targetPos, const sdfVector4_t *_cameraPos) {
  f32 z;
  f32 y;
  f32 x;
  f32 v15;
  f32 v16;
  f32 v17;
  _BOOL4 Use;
  u32 v31;
  EX_CAMMV_t *v32;
  s32 Flg;
  EX_CAMMV_t *v34;
  s32 v35;
  f32 v36;
  EX_CAMMV_t *v37;
  u32 v38;
  EX_CAMMV_t *v39;
  f32 *v40;
  f32 *v41;
  f32 *v42;
  f32 *v43;
  f32 *v44;
  f32 *v45;
  f32 TgtSOfsY;
  f32 TimeNomal;
  f32 v48;
  f32 v50;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 playerID;
  SBTLUNIT_WORK *v54;
  EX_CAMMV_t *v55;
  f32 *v56;
  f32 *v57;
  f32 *v58;
  f32 *v59;
  f32 *v60;
  f32 *v61;
  SBATTLE_WORK *v63;
  SBTLUNIT_LISTWORK *v64;
  s32 v65;
  SBTLUNIT_WORK *v66;
  int8x16_t v67;
  int8x16_t v68;
  int8x16_t *v69;
  f32 v70;
  f32 v71;
  f32 v72;
  int8x16_t v73;
  f32 v74;
  f32 v75;
  f32 v76;
  f32 v77;
  f32 v78;
  u32 v79;
  EX_CAMMV_t *v80;
  f32 CamMode;
  f32 v82;
  f32 v83;
  f32 v84;
  f32 v85;
  f32 v86;
  f32 v87;
  u32 v88;
  f32 SLen;
  f32 v90;
  f32 v91;
  f32 CamSYDir;
  f32 v93;
  f32 SDir;
  f32 v95;
  f32 SOfsY;
  f32 v98;
  f32 v99;
  f32 v100;
  f32 v101;
  f32 v102;
  SBATTLE_WORK *v103;
  SBTLUNIT_LISTWORK *v104;
  s32 v105;
  f32 v106;
  f32 v107;
  f32 v108;
  f32 v109;
  f32 v110;
  SBTLUNIT_WORK *v111;
  EX_CAMMV_t *v112;
  f32 v113;
  f32 *v116;
  u32 v118;
  f32 v119;
  f32 v120;
  f32 v121;
  f32 v122;
  f32 v123;
  f32 v124;
  f32 v126;
  f32 v127;
  f32 v128;
  f32 v129;
  SBATTLE_WORK *v130;
  SBTLUNIT_LISTWORK *v131;
  s32 v132;
  f32 v133;
  f32 v134;
  f32 v135;
  SBTLUNIT_WORK *v136;
  f32 v137;
  f32 v138;
  SBTLUNIT_WORK *v139;
  f32 w;
  f32 v141;
  f32 v142;
  f32 v143;
  f32 v144;
  f32 v145;
  f32 v146;
  f32 v147;
  f32 v148;
  f32 v149;
  f32 v150;
  f32 v151;
  f32 v153;
  f32 v154;
  f32 v155;
  f32 v156;
  f32 v157;
  SBATTLE_WORK *v158;
  SBTLUNIT_LISTWORK *v159;
  s32 v160;
  f32 v161;
  f32 v162;
  f32 v163;
  f32 v164;
  SBTLUNIT_WORK *v165;
  EX_CAMMV_t *v166;
  f32 v167;
  f32 *v169;
  f32 *v170;
  f32 v171;
  f32 v172;
  f32 v173;
  s64 v174;
  s64 Len;
  s64 v176;
  s64 ToX;
  s64 ToZ;
  f32 ZeroY;
  f32 ZeroX;
  sdfVector4_t v181;

  z = cameraPos->z;
  y = cameraPos->y;
  x = cameraPos->x;
  v15 = targetPos->z;
  v16 = targetPos->y;
  v17 = targetPos->x;
  ZeroX = 0.0;
  ZeroY = 0.0;
  ToX = 0;
  ToZ = 0;
  Len = 0;
  v176 = 0;
  v174 = 0;
  v173 = 0.0;
  Use = gCamMv->Use;
  if (gCamMv->Use)
  {
    sBtlGetZeroPos(&ZeroX, &ZeroY, (f32 *)&ToZ + 1);
    v32 = gCamMv;
    if (v32->BlandMode)
    {
      if (!v31)
      {
        v32 = gCamMv;
      }
      *TX = v32->TgtSX + (f32)((f32)(v17 - v32->TgtSX) * v32->TimeNomal);
      *TY = v32->TgtSY + (f32)((f32)(v16 - v32->TgtSY) * v32->TimeNomal);
      *TZ = v32->TgtSZ + (f32)((f32)(v15 - v32->TgtSZ) * v32->TimeNomal);
      *CX = v32->SX + (f32)((f32)(x - v32->SX) * v32->TimeNomal);
      *CY = v32->SY + (f32)((f32)(y - v32->SY) * v32->TimeNomal);
      *CZ = v32->SZ + (f32)((f32)(z - v32->SZ) * v32->TimeNomal);
      return Use;
    }
    if (v31)
    {
      Flg = v32->Flg;
      if ((Flg & 1) == 0)
        goto LABEL_16;
    }
    else
    {
      v32 = gCamMv;
      Flg = v32->Flg;
      if ((Flg & 1) == 0)
      {
LABEL_16:
        goto LABEL_17;
      }
    }
    v32 = gCamMv;
    Flg = v32->Flg;
    v32->Flg = Flg & 0xFFFFFFFE;
    sBtlNoHokan();
LABEL_17:
    v34 = gCamMv;
    v35 = v34->Flg;
    if ((v35 & 2) == 0)
    {
      goto LABEL_19;
    }
    v34 = gCamMv;
    v35 = v34->Flg;
    v34->Flg = v35 & 0xFFFFFFFD;
    sBtlSetCameraHighTargetUse(0, -1);
LABEL_19:
    v36 = 0.0;
    v170 = TX;
    v37 = gCamMv;
    if ((v37->Flg & 0x8000) == 0)
    {
      goto LABEL_21;
    }
    v40 = TZ;
    v41 = CX;
    v42 = CY;
    v43 = CZ;
    v44 = Fov;
    v45 = UpV;
    v37 = gCamMv;
    TgtSOfsY = v37->TgtSOfsY;
    TimeNomal = v37->TimeNomal;
    v48 = v37->TgtEOfsY - TgtSOfsY;
    v50 = v48 * TimeNomal;
    UnitMng = wk->UnitMng;
    playerID = wk->playerID;
    v36 = TgtSOfsY + v50;
    v54 = sBtlSearchUnit_ID(UnitMng, playerID);
    UpV = v45;
    Fov = v44;
    CZ = v43;
    CY = v42;
    CX = v41;
    TZ = v40;
    TX = v170;
    v55 = gCamMv;
    v55->TgtEX = v54->pos.x;
    v55->TgtEZ = v54->pos.z;
LABEL_21:
    if ((gCamMv->Flg & 0x10000) == 0)
    {
      goto LABEL_23;
    }
    v56 = TZ;
    v57 = CX;
    v58 = CY;
    v59 = CZ;
    v60 = Fov;
    v61 = UpV;
    v63 = wk;
    v64 = v63->UnitMng;
    v65 = v63->playerID;
    v66 = sBtlSearchUnit_ID(v64, v65);
    v67.n128_u64[0] = *(u64 *)&v66->pos.x;
    v69 = gCamMv;
    v69[7].n128_u64[1] = v67.n128_u64[0];
    v70 = v69[9].n128_f32[1];
    v71 = v69[9].n128_f32[2];
    v72 = v69[1].n128_f32[2];
    v68.n128_u32[0] = LODWORD(v66->pos.z);
    UpV = v61;
    Fov = v60;
    CZ = v59;
    CY = v58;
    CX = v57;
    TZ = v56;
    TX = v170;
    v73 = vextq_s8(vextq_s8(v68, v68, 4u), v67, 0xCu);
    v73.n128_u32[3] = v73.n128_u32[0];
    v69[8] = v73;
    v36 = v70 + (f32)((f32)(v71 - v70) * v72);
LABEL_23:
    v39 = gCamMv;
    if ((v39->Flg & 0x2000) == 0)
    {
      if (!v38)
      {
        v39 = gCamMv;
      }
      *TX = v39->TgtSX + (f32)((f32)(v39->TgtEX - v39->TgtSX) * v39->TimeNomal);
      *TY = v39->TgtSY + (f32)((f32)(v39->TgtEY - v39->TgtSY) * v39->TimeNomal);
      *TZ = v39->TgtSZ + (f32)((f32)(v39->TgtEZ - v39->TgtSZ) * v39->TimeNomal);
      *TY = v36 + *TY;
LABEL_61:
      v80 = gCamMv;
      CamMode = v80->CamMode;
      if (CamMode == 0.0)
      {
        if (!v79)
        {
          v80 = gCamMv;
        }
        *CX = v80->SX + (f32)((f32)(v80->EX - v80->SX) * v80->TimeNomal);
        *CY = v80->SY + (f32)((f32)(v80->EY - v80->SY) * v80->TimeNomal);
        v82 = ZeroX;
        *CZ = v80->SZ + (f32)((f32)(v80->EZ - v80->SZ) * v80->TimeNomal);
        v83 = *CX + v82;
        v84 = ZeroY;
        *CX = v83;
        v85 = *CY + v84;
        v86 = *((f32 *)&ToZ + 1);
        *CY = v85;
        v87 = *CZ + v86;
      }
      else
      {
        if (!v79)
        {
          v80 = gCamMv;
          CamMode = v80->CamMode;
        }
        if (CamMode == 1.0)
        {
          if (!v88)
          {
            v80 = gCamMv;
          }
          SLen = v80->SLen;
          v90 = v80->TimeNomal;
          v91 = v80->ELen - SLen;
          CamSYDir = v80->CamSYDir;
          v93 = v80->CamEYDir - CamSYDir;
          SDir = v80->SDir;
          v95 = v80->EDir - SDir;
          SOfsY = v80->SOfsY;
          v98 = v80->EOfsY - SOfsY;
          v171 = v80->SLen;
          SLen = v171;
          v99 = v91 * v90;
          v100 = v90 * v93;
          v101 = v90 * v95;
          v102 = v90 * v98;
          v103 = wk;
          v104 = v103->UnitMng;
          v105 = v103->playerID;
          v106 = SLen;
          SLen = v106;
          v107 = SLen + v99;
          v108 = CamSYDir + v100;
          v109 = SDir + v101;
          v110 = SOfsY + v102;
          v111 = sBtlSearchUnit_ID(v104, v105);
          v112 = gCamMv;
          v112->EX = v111->pos.x;
          v113 = v111->pos.z;
          v112->EZ = v113;
          sBtlGetMoveXZ(0.0, 0.0, v108, v107, (f32 *)&ToX + 1, &ToZ);
          sBtlGetMoveXZ(gCamMv->EX, gCamMv->EZ, v109, *(f32 *)&ToZ, &ToX, (f32 *)&v176 + 1);
          *(u32 *)CX = ToX;
          v87 = *((f32 *)&v176 + 1);
        }
        else
        {
          if (!v88)
          {
            v80 = gCamMv;
            CamMode = v80->CamMode;
          }
          if (CamMode == 2.0)
          {
            v169 = UpV;
            if (!v118)
            {
              v80 = gCamMv;
            }
            v119 = v80->SDir;
            v120 = v80->TimeNomal;
            v121 = v80->EDir - v119;
            v122 = v80->SLen;
            v123 = v80->ELen - v122;
            v124 = v80->SOfsY;
            v126 = v80->EOfsY - v124;
            v127 = v121 * v120;
            v128 = v120 * v123;
            v129 = v120 * v126;
            v130 = wk;
            v131 = v130->UnitMng;
            v132 = v130->playerID;
            v133 = v119 + v127;
            v134 = v122 + v128;
            v135 = v124 + v129;
            v136 = sBtlSearchUnit_ID(v131, v132);
            v137 = v136->rot.x;
            v138 = v136->rot.y;
            v139 = v136;
            v141 = v136->rot.z;
            w = v136->rot.w;
            v181.x = v137;
            v181.y = v138;
            v181.z = v141;
            v181.w = w;
            v142 = v133 + sBtlGetRotToDir(v181);
            sBtlGetMoveXZ(v139->pos.x, v139->pos.z, v142, v134, &v176, (f32 *)&Len + 1);
            v143 = *((f32 *)&Len + 1);
            *(u32 *)CX = v176;
            *CY = v135;
            *CZ = v143;
            sBtlDrawLineX_PS2(*CX, *CY, v143, 150.0, 0x80008000);
            sBtlDrawLineX_PS2(*TX, *TY, *TZ, 150.0, 0x80008000);
            UpV = v169;
            *AngleX = sBtlGet360(v142);
            goto LABEL_79;
          }
          if (!v118)
          {
            v80 = gCamMv;
            CamMode = v80->CamMode;
          }
          if (CamMode != 3.0)
            goto LABEL_79;
          v80 = gCamMv;
          v144 = v80->SLen;
          v145 = v80->TimeNomal;
          v146 = v80->ELen - v144;
          v147 = v80->CamSYDir;
          v148 = v80->CamEYDir - v147;
          v149 = v80->SDir;
          v150 = v80->EDir - v149;
          v151 = v80->SOfsY;
          v153 = v80->EOfsY - v151;
          v172 = v80->SLen;
          v144 = v172;
          v154 = v146 * v145;
          v155 = v145 * v148;
          v156 = v145 * v150;
          v157 = v145 * v153;
          v158 = wk;
          v159 = v158->UnitMng;
          v160 = v158->playerID;
          v161 = v144;
          v144 = v161;
          v162 = v144 + v154;
          v163 = v147 + v155;
          v164 = v149 + v156;
          v110 = v151 + v157;
          v165 = sBtlSearchUnit_ID(v159, v160);
          v166 = gCamMv;
          v166->EX = v165->pos.x;
          v167 = v165->pos.z;
          v166->EZ = v167;
          sBtlGetMoveXZ(0.0, 0.0, v163, v162, (f32 *)&v174 + 1, &Len);
          sBtlGetMoveXZ(gCamMv->EX, gCamMv->EZ, v164, *(f32 *)&Len, &v174, &v173);
          *(u32 *)CX = v174;
          v87 = v173;
        }
        *CY = v110;
      }
      *CZ = v87;
LABEL_79:
      v116 = gCamMv;
      *Fov = v116[18] + (f32)((f32)(v116[19] - v116[18]) * v116[6]);
      *UpV = v116[20] + (f32)((f32)(v116[21] - v116[20]) * v116[6]);
      return Use;
    }
    if (!v38)
    {
      v39 = gCamMv;
    }
    *TX = v39->TgtSX + (f32)((f32)(v39->TgtEX - v39->TgtSX) * v39->TimeNomal);
    *TY = v39->TgtSY + (f32)((f32)(v39->TgtEY - v39->TgtSY) * v39->TimeNomal);
    v74 = ZeroX;
    *TZ = v39->TgtSZ + (f32)((f32)(v39->TgtEZ - v39->TgtSZ) * v39->TimeNomal);
    v75 = *TX + v74;
    v76 = ZeroY;
    *TX = v75;
    v77 = *TY + v76;
    v78 = *((f32 *)&ToZ + 1);
    *TY = v77;
    *TZ = *TZ + v78;
    goto LABEL_61;
  }
  return Use;
}

// 0x20ca500
void sBtlPlayerCamMvReset(SBTLUNIT_WORK *wk) {
  gCamMv->Use = 0;
  return;
}

// 0x20ca590
void sBtlPlayerCamMvSetToResultMode(bool _OnOff) {
  gCamMv->ToResultMode = OnOff;
}

// 0x20ca600
static void CamJumpUpdate(SBTLUNIT_WORK *wk) {
  f32 Y;
  f32 v6;
  f32 v7;
  f32 v8;

  if (!gCamJump->Use)
    return;
  if (!gCamJump->Pause)
  {
    if ((wk->hstatus & 0x4000) == 0)
    {
      Y = gCamJump->Y;
      v6 = gCamJump->Time + VRF_DeltaTime;
      v7 = gCamJump->Speed + (f32)((f32)(v6 * 9.8) * gCamJump->CamJumpSpdD);
      gCamJump->Speed = v7;
      v8 = Y + (f32)(v6 * v7);
      gCamJump->Time = v6;
      gCamJump->Y = v8;
      if (v8 >= 0.0)
      {
        gCamJump->Y = 0.0;
        gCamJump->Use = 0;
      }
    }
    return;
  }
  if (gCamJump->Speed >= 0.0)
    return;
  gCamJump->Speed = 0.0;
}

// 0x20ca7e0
bool sBtlPlayerGetCamJump(f32 *_TY, f32 *_CY, const sdfVector4_t *_targetPos, const sdfVector4_t *_cameraPos) {
  _BOOL4 Use;

  Use = gCamJump->Use;
  if (!gCamJump->Use)
    return Use;
  *TY = gCamJump->Y;
  *CY = gCamJump->Y;
  return Use;
}

// 0x20ca8c0
static void CamJumpUpdate2(SBTLUNIT_WORK *wk) {
  f32 JumpY;

  if (!gCamJump2->Use)
    return;
  if (wk->motionno != 95)
  {
    JumpY = sBtlGetJumpY(wk);
    gCamJump2->Y = JumpY;
    goto LABEL_16;
  }
  gCamJump2->Y = gCamJump->Y;
LABEL_16:
  if (!sBtlChkNowJump(wk))
  {
    gCamJump2->Use = 0;
  }
}

// 0x20caa40
bool sBtlPlayerGetCamJump2(f32 *_TY, f32 *_CY, const sdfVector4_t *_targetPos, const sdfVector4_t *_cameraPos) {
  _BOOL4 Use;

  Use = gCamJump2->Use;
  if (!gCamJump2->Use)
    return Use;
  *TY = gCamJump2->Y * 0.4;
  *CY = gCamJump2->Y * 0.4;
  return Use;
}

// 0x20cab30
void sBtlPlayerSetCamJump_To_CamJump2(void) {
  gCamJump->Use = 0;
  gCamJump2->Use = 1;
}

// 0x20caba0
void sBtlPlayerResetCamJump(void) {
  gCamJump->Use = 0;
  gCamJump2->Use = 0;
  gCamJump->Y = 0.0;
  gCamJump2->Y = 0.0;
}

// 0x20cac10
void sBtlPlayerSetMantOnOff(SBTLUNIT_WORK *wk, bool _OnOff, s32 _Mode) {
  void *MantObj;
  void *p_MantObj;
  void *gameObject;
  void *transform;
  void *v12;
  void *v13;
  void *MantObj2;
  void *p_MantObj2;
  void *v16;
  void *v17;
  void *v18;
  void *v19;
  void *v20;
  void *v22;
  bool v23;
  void *v24;
  bool v25;
  void *v26;

  MantObj = wk->MantObj;
  p_MantObj = &wk->MantObj;
  if (!op_Equality(MantObj, 0, 0))
    goto LABEL_14;
  gameObject = get_gameObject(wk->hModel->modelRoot->modelObj, 0);
  if (!op_Inequality(gameObject, 0, 0))
    goto LABEL_14;
  transform = get_transform(gameObject, 0);
  v12 = Find(transform, "program_ctrl/mant", 0);
  if (!op_Inequality(v12, 0, 0))
    goto LABEL_14;
  goto LABEL_13;
  if (op_Inequality(v12, 0, 0))
  {
LABEL_13:
    v13 = get_gameObject(v12, 0);
    p_MantObj = v13;
  }
LABEL_14:
  MantObj2 = wk->MantObj2;
  p_MantObj2 = &wk->MantObj2;
  if (!op_Equality(wk->MantObj2, 0, 0))
    goto LABEL_25;
  v16 = get_gameObject(wk->hModel->modelRoot->modelObj, 0);
  if (!op_Inequality(v16, 0, 0))
    goto LABEL_25;
  v17 = get_transform(v16, 0);
  v18 = Find(v17, "program_ctrl/mant2", 0);
  if (!op_Inequality(v18, 0, 0))
    goto LABEL_25;
  goto LABEL_24;
  if (op_Inequality(v18, 0, 0))
  {
LABEL_24:
    v19 = get_gameObject(v18, 0);
    p_MantObj2 = v19;
  }
LABEL_25:
  v20 = p_MantObj;
  if (!Mode)
  {
    if (OnOff)
    {
      if (!op_Inequality(v20, 0, 0) || get_activeSelf(p_MantObj, 0))
      {
        goto LABEL_43;
      }
      v22 = p_MantObj;
      v23 = 1;
      goto LABEL_42;
    }
LABEL_36:
    if (!op_Inequality(p_MantObj, 0, 0))
      goto LABEL_43;
    if (get_activeSelf(p_MantObj, 0))
    {
      v22 = p_MantObj;
      v23 = 0;
LABEL_42:
      SetActive(v22, v23, 0);
    }
LABEL_43:
    v24 = p_MantObj2;
    if (!op_Inequality(p_MantObj2, 0, 0))
      return;
    if (!get_activeSelf(p_MantObj2, 0))
      return;
    v25 = 0;
LABEL_63:
    SetActive(p_MantObj2, v25, 0);
    return;
  }
  if (!OnOff)
    goto LABEL_36;
  if (!!op_Inequality(p_MantObj, 0, 0))
  {
    if (get_activeSelf(p_MantObj, 0))
      SetActive(p_MantObj, 0, 0);
  }
  v26 = p_MantObj2;
  if (!op_Inequality(p_MantObj2, 0, 0))
    return;
  if (!get_activeSelf(p_MantObj2, 0))
  {
    v25 = 1;
    goto LABEL_63;
  }
}

// 0x20cb090
void sBtlPlayerKudaOpenEffUpdate(SBTLUNIT_WORK *wk) {
  void *KudaObj;
  void *p_KudaObj;
  void *gameObject;
  void *transform;
  void *v8;
  void *v9;
  Il2CppClass *klass;
  Il2CppObject *Component_object;
  void *v12;
  void *KudaOpenMesh;

  KudaObj = wk->KudaObj;
  p_KudaObj = &wk->KudaObj;
  if (!op_Equality(KudaObj, 0, 0))
    goto LABEL_14;
  gameObject = get_gameObject(wk->hModel->modelRoot->modelObj, 0);
  if (!op_Inequality(gameObject, 0, 0))
    goto LABEL_14;
  transform = get_transform(gameObject, 0);
  v8 = Find(transform, "program_ctrl/linknode", 0);
  if (!op_Inequality(v8, 0, 0))
    goto LABEL_14;
  goto LABEL_13;
  if (op_Inequality(v8, 0, 0))
  {
LABEL_13:
    v9 = get_gameObject(v8, 0);
    klass = GetComponent_object_(v9)[2].klass;
    wk->KudaObj = klass;
    Component_object = GetComponent_object_(wk->KudaObj);
    wk->KudaOpenMesh = Component_object;
  }
LABEL_14:
  v12 = p_KudaObj;
  if (!op_Inequality(v12, 0, 0))
    return;
  KudaOpenMesh = wk->KudaOpenMesh;
  if (!op_Inequality(wk->KudaOpenMesh, 0, 0))
    return;
  if (get_enabled(wk->KudaOpenMesh, 0))
    Add(wk->ListID, 0);
  else
    Del(0);
}

// 0x20cb320
void sBtlPlayerMagSdLcAxEffUpdate(SBTLUNIT_WORK *wk) {
  void *MagSdObj;
  void *p_MagSdObj;
  void *gameObject;
  void *transform;
  void *v8;
  void *v9;
  Il2CppObject *Component_object;
  void *monitor;
  Il2CppObject *v12;
  Il2CppObject *v13;
  void *klass;
  Il2CppObject *v15;
  void *v16;
  Il2CppObject *v17;
  void *v18;
  void *v19;
  s32 motionno;
  s32 v21;
  void *v22;
  void *v23;
  s32 v24;
  void *v25;
  void *v26;
  void *v27;
  void *v28;
  void *v29;
  void *v30;
  void *v31;
  void *v32;
  s32 v33;
  void *v34;
  void *v35;
  void *v36;
  void *v37;
  void *v38;
  void *v39;
  s32 m_type;
  void *v41;
  void *v42;
  dds3ModelHandle_t *hModel;
  s32 v44;
  void *v45;
  void *MagSdMesh;
  void *MagLcObj;
  void *MagLcMesh;
  void *MagAxObj;
  void *MagAxMesh;
  s32 v51;
  void *v52;
  void *v53;
  void *v54;
  void *v55;
  s32 v56;
  s32 v57;
  void *v58;
  void *v59;
  void *v60;
  void *v61;
  void *v62;
  void *v63;

  MagSdObj = wk->MagSdObj;
  p_MagSdObj = &wk->MagSdObj;
  if (!op_Equality(MagSdObj, 0, 0))
    goto LABEL_15;
  gameObject = get_gameObject(wk->hModel->modelRoot->modelObj, 0);
  if (!op_Inequality(gameObject, 0, 0))
    goto LABEL_15;
  transform = get_transform(gameObject, 0);
  v8 = Find(transform, "program_ctrl/linknode", 0);
  if (op_Inequality(v8, 0, 0))
  {
    v9 = get_gameObject(v8, 0);
    Component_object = GetComponent_object_(v9);
    monitor = Component_object[2].monitor;
    v12 = Component_object;
    wk->MagSdObj = monitor;
    v13 = GetComponent_object_(wk->MagSdObj);
    wk->MagSdMesh = v13;
    klass = v12[3].klass;
    wk->MagLcObj = klass;
    v15 = GetComponent_object_(wk->MagLcObj);
    wk->MagLcMesh = v15;
    v16 = v12[3].monitor;
    wk->MagAxObj = v16;
    v17 = GetComponent_object_(wk->MagAxObj);
    wk->MagAxMesh = v17;
  }
LABEL_15:
  switch (wk->motionno)
  {
    case 0xB:
      v45 = p_MagSdObj;
      if (op_Inequality(v45, 0, 0))
      {
        MagSdMesh = wk->MagSdMesh;
        if (op_Inequality(MagSdMesh, 0, 0))
          goto LABEL_23;
      }
      goto LABEL_158;
    case 0x2B:
      MagLcObj = wk->MagLcObj;
      if (!op_Inequality(MagLcObj, 0, 0))
        goto LABEL_158;
      MagLcMesh = wk->MagLcMesh;
      if (!op_Inequality(MagLcMesh, 0, 0))
        goto LABEL_158;
      goto LABEL_35;
    case 0x2C:
      MagAxObj = wk->MagAxObj;
      if (!op_Inequality(MagAxObj, 0, 0))
        goto LABEL_158;
      MagAxMesh = wk->MagAxMesh;
      if (!op_Inequality(MagAxMesh, 0, 0))
        goto LABEL_158;
      goto LABEL_157;
    case 0x31:
    case 0x32:
    case 0x33:
    case 0x3A:
    case 0x3B:
    case 0x3C:
      v25 = p_MagSdObj;
      if (op_Inequality(v25, 0, 0))
      {
        v26 = wk->MagSdMesh;
        if (op_Inequality(v26, 0, 0))
        {
          if (get_enabled(wk->MagSdMesh, 0))
            Add(wk->ListID, 0);
          else
            Del(0);
        }
      }
      v52 = wk->MagLcObj;
      if (op_Inequality(v52, 0, 0))
      {
        v53 = wk->MagLcMesh;
        if (op_Inequality(v53, 0, 0))
        {
          if (get_enabled(wk->MagLcMesh, 0))
            Add(wk->ListID, 0);
          else
            Del(0);
        }
      }
      goto LABEL_149;
    case 0x36:
    case 0x37:
      v34 = p_MagSdObj;
      if (op_Inequality(v34, 0, 0))
      {
        v35 = wk->MagSdMesh;
        if (op_Inequality(v35, 0, 0))
        {
          v36 = wk->MagLcObj;
          if (op_Inequality(v36, 0, 0))
          {
            v37 = wk->MagLcMesh;
            if (op_Inequality(v37, 0, 0))
            {
              v38 = wk->MagAxObj;
              if (op_Inequality(v38, 0, 0))
              {
                v39 = wk->MagAxMesh;
                if (op_Inequality(v39, 0, 0))
                  goto LABEL_94;
              }
            }
          }
        }
      }
      goto LABEL_158;
    case 0x6F:
    case 0x70:
    case 0x71:
    case 0x90:
    case 0x91:
    case 0x92:
    case 0x93:
    case 0x95:
    case 0x96:
    case 0x97:
    case 0x98:
      v18 = p_MagSdObj;
      if (op_Inequality(v18, 0, 0))
      {
        v19 = wk->MagSdMesh;
        if (op_Inequality(v19, 0, 0))
          goto LABEL_22;
      }
      goto LABEL_158;
    case 0x72:
    case 0x73:
    case 0x74:
    case 0x9A:
    case 0x9B:
    case 0x9C:
    case 0x9D:
    case 0x9E:
      v22 = wk->MagLcObj;
      if (!op_Inequality(v22, 0, 0))
        goto LABEL_158;
      v23 = wk->MagLcMesh;
      if (!op_Inequality(v23, 0, 0))
        goto LABEL_158;
      if (get_enabled(wk->MagLcMesh, 0))
        goto LABEL_35;
      Del(0);
      motionno = wk->motionno;
      if (motionno <= 43)
        v51 = 0;
      else
        v51 = 43;
      if (v51 == 43)
        goto LABEL_169;
      goto LABEL_162;
    case 0x75:
    case 0x76:
    case 0x77:
    case 0xA0:
    case 0xA1:
    case 0xA2:
    case 0xA3:
    case 0xA4:
    case 0xA5:
    case 0xA6:
    case 0xA7:
LABEL_149:
      v54 = wk->MagAxObj;
      if (!op_Inequality(wk->MagAxObj, 0, 0))
        goto LABEL_158;
      v55 = wk->MagAxMesh;
      if (!op_Inequality(v55, 0, 0))
        goto LABEL_158;
      if (get_enabled(wk->MagAxMesh, 0))
        goto LABEL_157;
      AW_MagDel();
      motionno = wk->motionno;
      if (motionno <= 43)
        v57 = 0;
      else
        v57 = 43;
      if (v57 == 43)
        goto LABEL_169;
      goto LABEL_162;
    case 0x94:
    case 0x99:
      v41 = p_MagSdObj;
      if (!op_Inequality(v41, 0, 0))
        goto LABEL_158;
      v42 = wk->MagSdMesh;
      if (!op_Inequality(v42, 0, 0))
        goto LABEL_158;
      hModel = wk->hModel;
      if (mdlGetMotionFrameF(hModel) <= 1.0)
        goto LABEL_23;
LABEL_22:
      if (get_enabled(wk->MagSdMesh, 0))
        goto LABEL_23;
      Del(0);
      motionno = wk->motionno;
      if (motionno <= 43)
        v44 = 0;
      else
        v44 = 43;
      if (v44 == 43)
        goto LABEL_169;
      goto LABEL_162;
    default:
      v27 = p_MagSdObj;
      if (!op_Inequality(v27, 0, 0))
        goto LABEL_158;
      v28 = wk->MagSdMesh;
      if (!op_Inequality(v28, 0, 0))
        goto LABEL_158;
      v29 = wk->MagLcObj;
      if (!op_Inequality(v29, 0, 0))
        goto LABEL_158;
      v30 = wk->MagLcMesh;
      if (!op_Inequality(v30, 0, 0))
        goto LABEL_158;
      v31 = wk->MagAxObj;
      if (!op_Inequality(v31, 0, 0))
        goto LABEL_158;
      v32 = wk->MagAxMesh;
      if (!op_Inequality(v32, 0, 0))
        goto LABEL_158;
      if (get_enabled(wk->MagSdMesh, 0) || get_enabled(wk->MagLcMesh, 0) || get_enabled(wk->MagAxMesh, 0))
      {
LABEL_94:
        m_type = sBtlDat()->m_type;
        if (m_type != 3)
        {
          if (m_type == 2)
          {
LABEL_35:
            Add(wk->ListID, 0);
            motionno = wk->motionno;
            if (motionno <= 43)
              v24 = 0;
            else
              v24 = 43;
            if (v24 != 43)
              goto LABEL_162;
          }
          else
          {
            if (m_type != 1)
            {
LABEL_158:
              motionno = wk->motionno;
              if (motionno <= 43)
                v56 = 0;
              else
                v56 = 43;
              if (v56 != 43)
                goto LABEL_162;
              goto LABEL_169;
            }
LABEL_23:
            Add(wk->ListID, 0);
            motionno = wk->motionno;
            if (motionno <= 43)
              v21 = 0;
            else
              v21 = 43;
            if (v21 != 43)
              goto LABEL_162;
          }
LABEL_169:
          switch (motionno)
          {
            case ',':
            case 'u':
            case 'v':
            case 'w':
              v58 = wk->MagAxObj;
              if (!op_Inequality(wk->MagAxObj, 0, 0))
                return;
              v63 = wk->MagAxMesh;
              if (op_Inequality(v63, 0, 0))
              {
                if (get_enabled(wk->MagAxMesh, 0))
                  Add(wk->ListID, 0);
                else
                  Del(0);
              }
              break;
            case 'o':
            case 'p':
            case 'q':
              goto LABEL_173;
            case 'r':
            case 's':
            case 't':
              goto LABEL_176;
            default:
              return;
          }
          return;
        }
LABEL_157:
        AW_MagAdd(wk->ListID);
        goto LABEL_158;
      }
      DeleteAll_MagWeapon();
      motionno = wk->motionno;
      if (motionno <= 43)
        v33 = 0;
      else
        v33 = 43;
      if (v33 == 43)
        goto LABEL_169;
LABEL_162:
      if (motionno == 11)
      {
LABEL_173:
        v59 = p_MagSdObj;
        if (!op_Inequality(v59, 0, 0))
          return;
        v61 = wk->MagSdMesh;
        if (!op_Inequality(wk->MagSdMesh, 0, 0))
          return;
        if (get_enabled(wk->MagSdMesh, 0))
          Add(wk->ListID, 0);
        else
          Del(0);
      }
      else
      {
        if (motionno != 43)
          return;
LABEL_176:
        v60 = wk->MagLcObj;
        if (!op_Inequality(wk->MagLcObj, 0, 0))
          return;
        v62 = wk->MagLcMesh;
        if (!op_Inequality(wk->MagLcMesh, 0, 0))
          return;
        if (get_enabled(wk->MagLcMesh, 0))
          Add(wk->ListID, 0);
        else
          Del(0);
      }
      return;
  }
}

// 0x20cbef0
void sBtlPlayerMagSdLcAxEff_WeaponCng_FromMenu(SBWEAPON_TYPE _OldType, SBWEAPON_TYPE _NewType) {
  SBTLUNIT_LISTWORK *UnitMng;
  s32 playerID;
  SBTLUNIT_WORK *v9;
  u32 motionno;
  SBTLUNIT_WORK *v11;
  bool v12;
  void *MagSdObj;
  void *MagSdMesh;
  void *MagLcObj;
  void *MagLcMesh;
  void *MagAxObj;
  void *MagAxMesh;
  SBATTLE_WORK *v20;

  UnitMng = wk->UnitMng;
  playerID = wk->playerID;
  v9 = sBtlSearchUnit_ID(UnitMng, playerID);
  motionno = v9->motionno;
  v11 = v9;
  v12 = motionno > 0x2C || ((1 << motionno) & 0x180000000800LL) == 0;
  if (!v12 || motionno - 111 <= 8)
  {
    MagSdObj = v9->MagSdObj;
    if (!op_Inequality(v9->MagSdObj, 0, 0))
      return;
    MagSdMesh = v11->MagSdMesh;
    if (!op_Inequality(v11->MagSdMesh, 0, 0))
      return;
    MagLcObj = v11->MagLcObj;
    if (!op_Inequality(v11->MagLcObj, 0, 0))
      return;
    MagLcMesh = v11->MagLcMesh;
    if (!op_Inequality(v11->MagLcMesh, 0, 0))
      return;
    MagAxObj = v11->MagAxObj;
    if (op_Inequality(MagAxObj, 0, 0))
    {
      MagAxMesh = v11->MagAxMesh;
      if (op_Inequality(MagAxMesh, 0, 0) && (v11->vstatus & 0x8000) == 0)
      {
        v11->hstatus &= 0xFC7FFFFF;
        v20 = wk;
        *(u64 *)&v20->chargeAxCnt = 0;
        *(_OWORD *)&v20->chargeSdCnt = 0u;
        DeleteAll();
        if (OldType == NewType)
        {
          goto LABEL_40;
        }
        else
        {
          DeleteAll_MagWeapon();
LABEL_40:
          sBtlSetPlayerDir_ToTarget(v11);
          if (NewType != 3)
            goto LABEL_41;
LABEL_51:
          v11->next_motion_not_hokan = 1;
          sBtlSetMotion(v11, 41, 0, 0, 0);
          AW_MagAdd(v11->ListID);
          return;
        }
        sBtlSetPlayerDir_ToTarget(v11);
        if (NewType != 3)
        {
LABEL_41:
          if (NewType == 2)
          {
            v11->next_motion_not_hokan = 1;
            sBtlSetMotion(v11, 40, 0, 0, 0);
            Add(v11->ListID, 0);
          }
          else if (NewType == 1)
          {
            v11->next_motion_not_hokan = 1;
            sBtlSetMotion(v11, 29, 0, 0, 0);
            Add(v11->ListID, 0);
          }
          return;
        }
        goto LABEL_51;
      }
    }
  }
}

// 0x20cc330
void sBtlPlayerSetTuugiZokusei(s32 _Variation) {
  gTuugiZokusei = -1;
  if ((u32)Variation > 4)
    return;
  switch (Variation)
  {
    case 0:
      gTuugiZokusei = 0;
      break;
    case 1:
      gTuugiZokusei = 1;
      break;
    case 2:
      gTuugiZokusei = 2;
      break;
    case 3:
      gTuugiZokusei = 3;
      break;
    case 4:
      gTuugiZokusei = 4;
      break;
    default:
      return;
  }
}

// 0x20cc4a0
s32 sBtlPlayerGetSkillNum(void) {
  return gSkillNum;
}

// 0x20cc520
void sBtlPlayerJyusoEffOnOff(SBTLUNIT_WORK *wk, bool _OnOff) {
  void *JyusoEffObj;
  void *p_JyusoEffObj;
  void *gameObject;
  void *transform;
  void *v10;
  void *v11;
  void *monitor;
  void *v13;
  bool activeSelf;

  if (!wk->is_jyuso)
    return;
  JyusoEffObj = wk->JyusoEffObj;
  p_JyusoEffObj = &wk->JyusoEffObj;
  if (!op_Equality(wk->JyusoEffObj, 0, 0))
    goto LABEL_19;
  gameObject = get_gameObject(wk->hModel->modelRoot->modelObj, 0);
  if (!op_Inequality(gameObject, 0, 0))
    goto LABEL_19;
  transform = get_transform(gameObject, 0);
  v10 = Find(transform, "program_ctrl/linknode", 0);
  if (op_Inequality(v10, 0, 0))
  {
    v11 = get_gameObject(v10, 0);
    monitor = GetComponent_object_(v11)[4].monitor;
    p_JyusoEffObj = monitor;
  }
LABEL_19:
  v13 = p_JyusoEffObj;
  if (!op_Inequality(v13, 0, 0))
    return;
  activeSelf = get_activeSelf(p_JyusoEffObj, 0);
  if (OnOff)
  {
    if (activeSelf)
      return;
  }
  else if (!activeSelf)
  {
    return;
  }
  SetActive(p_JyusoEffObj, OnOff, 0);
  return;
}

// 0x20cc770
void sBtlPlayerSetDirectHitRangeTgt(SBTLUNIT_WORK *wkPlayer, SKLID _SkillID, s32 _LifeTime, f32 _ActerOfsY, f32 _Size, f32 _TargetX, f32 _TargetY, f32 _TargetZ) {
  SBTLSKILLP_TBL *Skilltbl;
  SBTLSKILLHIT_TBL *v18;
  SBTLDMG_CYLINDERWORK *cy;
  s32 ListID;
  s32 acterside;
  SBTLDMG_HITLISTWORK *hitList;
  s32 hstatus;

  Skilltbl = sBtlGetSkilltbl(SkillID);
  v18 = Allocate(SBTLSKILLHIT_TBL);
  _ctor(v18, 0);
  gHittbl_Range_T->motionno = wkPlayer->motionno;
  cy = gHittbl_Range_T->cy;
  gHittbl_Range_T->lifetime = LifeTime;
  gHittbl_Range_T->area_r = Size;
  gHittbl_Range_T->x = TargetX;
  gHittbl_Range_T->y = TargetY;
  gHittbl_Range_T->z = TargetZ;
  cy->area_r = Size;
  ListID = wkPlayer->ListID;
  acterside = wkPlayer->side;
  hitList = wk->hitList;
  sBtlCreateHitC_New(hitList, wkPlayer, 0, ListID, SkillID, Skilltbl, gHittbl_Range_T, 0, acterside, -1);
  sBtlAddSerialID2();
  hstatus = wkPlayer->hstatus;
  wkPlayer->damage_ActerOfsY = ActerOfsY;
  wkPlayer->hstatus = hstatus & 0xFFFDFFFF;
}

// 0x20cc930
void sBtlPlayerUpdate(SBTLUNIT_WORK *wk) {
  u64 side;
  u64 p_rot;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  f32 RotToDir;
  f32 Dir180;
  s32 motionno;
  dds3ModelHandle_t *hModel;
  f32 MotionFrameF;
  f32 v19;
  s32 motionID;
  bool v23;
  s32 v26;
  bool *gDoneWork_local;
  EX_CAMMV_t *gCamMv_local;
  s64 v33;
  s32 v35;
  sBtlPlayerEx_EX_TABLE_t *v36;
  sBtlPlayerEx_EX_TABLE_t *gExTable_local;
  s32 v39;
  s32 gTableIndexTop_local;
  s32 v41;
  bool *v43;
  char *v44;
  s64 v46;
  sBtlPlayerEx_EX_TABLE_t *v47;
  sBtlPlayerEx_EX_TABLE_t *v48;
  f32 *v49;
  SBTLSKILLHIT_TBL *v50;
  SBTLSKILLHIT_TBL *gHittbl_Sd_local;
  SBTLSKILLHIT_TBL *v55;
  sBtlPlayerEx_EX_TABLE_t *v58;
  f32 Size;
  SBTLDMG_CYLINDERWORK *cy;
  SBTLDMG_HITLISTWORK *hitList;
  s32 use_skillid;
  s32 acterside;
  SBTLSKILLHIT_TBL *v66;
  f32 JumpY_SkillSt;
  SBTLSKILLP_TBL *Skilltbl;
  SBTLSKILLHIT_TBL *v70;
  SBTLSKILLHIT_TBL *gHittbl_Range_M_local;
  f32 *v74;
  SBTLDMG_CYLINDERWORK *v75;
  f32 v76;
  f32 v77;
  f32 v78;
  SBTLSKILLHIT_TBL *v81;
  f32 RootPosDir;
  f32 v85;
  f32 v86;
  SBTLSKILLP_TBL *v87;
  SBTLSKILLHIT_TBL *v88;
  SBTLSKILLHIT_TBL *v91;
  s32 ListID;
  SBTLDMG_HITLISTWORK *v98;
  f32 *v99;
  s32 v100;
  s32 SkillNum;
  s32 HDEffTable_SKLID;
  u32 SE;
  f32 v105;
  f32 v106;
  f32 v107;
  f32 v108;
  u32 v109;
  s32 SE_Vol;
  f32 v111;
  f32 v112;
  f32 v113;
  f32 v114;
  u32 v115;
  f32 v116;
  f32 v117;
  f32 v118;
  f32 v119;
  u32 v120;
  s32 v121;
  s32 v122;
  char **v124;
  s32 v125;
  s32 v126;
  char *VoiceName;
  u32 QuakePow;
  s32 QuakeTime;
  s32 v130;
  s32 VibIn;
  s32 VibLife;
  s32 VibPow;
  char *v134;
  f32 v135;
  f32 v136;
  f32 v137;
  f32 v138;
  f32 v139;
  f32 v140;
  f32 v141;
  SBTLSKILLHIT_TBL *v144;
  sBtlPlayerEx_EX_TABLE_t *v146;
  f32 v147;
  SBTLDMG_CYLINDERWORK *v148;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 targetID;
  SBTLUNIT_WORK *v152;
  SBTLDMG_HITLISTWORK *v153;
  s32 v154;
  s32 v155;
  s32 HitC_New;
  sBtlPlayerEx_EX_TABLE_t *v158;
  SBTLDMG_HITLISTWORK *v160;
  SBTLDMG_HITWORK *v161;
  SBTLDMG_HITLISTWORK *v164;
  SBTLDMG_HITWORK *v165;
  bool *v168;
  s32 v169;
  SBTLUNIT_LISTWORK *v171;
  SBTLUNIT_WORK *v172;
  SBTLUNIT_WORK *v173;
  s32 devilid;
  u32 color;
  SBTLCAMERA_WORK *camera;
  s64 v179;
  EX_CAMMV_t *v181;
  s64 v182;
  f32 EZ;
  s64 v184;
  f32 TgtEZ;
  sBtlPlayerEx_EX_TABLE_t *v186;
  s32 Flg;
  EX_CAMMV_t *v189;
  sBtlPlayerEx_EX_TABLE_t *v190;
  s64 v191;
  EX_CAMMV_t *v192;
  EX_CAMMV_t *v193;
  EX_CAMMV_t *v194;
  EX_CAMMV_t *v195;
  EX_CAMMV_t *v196;
  EX_CAMMV_t *v197;
  f32 v199;
  f32 v200;
  f32 v201;
  f32 v202;
  f32 v203;
  f32 v204;
  f32 v205;
  f32 LenXYZ;
  sBtlPlayerEx_EX_TABLE_t *v209;
  EX_CAMMV_t *v210;
  f32 v211;
  f32 DirY;
  EX_CAMMV_t *v214;
  f32 SX;
  f32 SZ;
  f32 PosToDir;
  f32 MotionFrame;
  EX_CAMMV_t *v220;
  f32 CamEFrame;
  SBTLCAMERA_WORK *v223;
  bool *v224;
  SBATTLE_WORK *v226;
  s32 encountno;
  s32 v228;
  SBTLUNIT_LISTWORK *v229;
  SBTLUNIT_WORK *v231;
  s32 v232;
  bool v234;
  EX_CAMJUMP_t *gCamJump_local;
  s64 v237;
  EX_CAMJUMP_t *v238;
  bool *v239;
  s32 Variation;
  bool v244;
  s32 v249;
  s32 v250;
  SBTLUNIT_WORK *v252;
  s32 v253;
  bool v254;
  f32 v256;
  f32 v257;
  f32 RootPosLen;
  f32 v259;
  f32 v260;
  f32 v261;
  f32 GroundPos;
  s32 v263;
  s32 v264;
  s32 v265;
  s32 v266;
  f32 v267;
  f32 v268;
  f32 v269;
  f32 v270;
  f32 v271;
  f32 v272;
  f32 v273;
  s32 v274;
  s32 v275;
  f32 v276;
  f32 v277;
  f32 v278;
  f32 v279;
  f32 v280;
  f32 v281;
  sBtlPlayerEx_EX_TABLE_t *v282;
  f32 v283;
  u32 v284;
  sBtlPlayerEx_EX_TABLE_t *v285;
  char v286;
  u32 v287;
  s32 v288;
  char v289;
  EX_CAMMV_t *v291;
  sBtlPlayerEx_EX_TABLE_t *v292;
  s32 v293;
  SBTLDMG_HITLISTWORK *v294;
  s32 v295;
  bool *v297;
  s32 SklID;
  u32 v299;
  sbtlplayertbl_Func FuncAdd;
  sBtlPlayerEx_EX_TABLE_t *v303;
  EX_CAMMV_t *v305;
  u32 v306;
  s32 v307;
  s32 v308;
  s32 v309;
  s64 v310;
  f32 v311;
  f32 v312;
  f32 v313;
  f32 v314;
  f32 v315;
  s64 v316;
  f32 v317;
  s64 v318;
  SBTLUNIT_WORK *UnitFromDevilID;
  s32 v320;
  s32 motion_serialno;
  SBTLSKILLP_TBL *tbl;
  SBTLSKILLP_TBL *tbla;
  SBTLSKILLP_TBL *tblb;
  s32 v331;
  s32 v332;
  sdfVector4_t *v333;
  s32 v334;
  s32 v335;
  s32 v336;
  f32 v337;
  s64 v338;
  s64 v339;
  f32 ToX;
  f32 ZeroZ;
  s64 ZeroY;
  sdfVector4_t v343;
  sdfVector4_t v344;
  sdfVector4_t v345;
  sdfVector4_t v346;
  sdfVector4_t v347;
  sdfVector4_t v348;

  x = wk->rot.x;
  y = wk->rot.y;
  p_rot = &wk->rot;
  ZeroY = 0;
  ZeroZ = 0.0;
  ToX = 0.0;
  v338 = 0;
  v339 = 0;
  v337 = 0.0;
  z = wk->rot.z;
  w = wk->rot.w;
  v343.x = x;
  v343.y = y;
  v343.z = z;
  v343.w = w;
  RotToDir = sBtlGetRotToDir(v343);
  Dir180 = sBtlGetDir180(RotToDir);
  motionno = wk->motionno;
  hModel = wk->hModel;
  MotionFrameF = mdlGetMotionFrameF(hModel);
  v19 = MotionFrameF;
  if (gOld_MotionNo == motionno)
  {
    goto LABEL_10;
  }
  gSame_MotionCount = 0;
LABEL_10:
  if (gOld_MotionNo != motionno)
    goto LABEL_31;
  if (v19 >= gOld_MotionFrame)
    goto LABEL_31;
  if (gOld_MotionSerialNo != wk->motion_serialno)
  {
    motionID = wk->motionID;
    v23 = sBtlCheckLoopMotion(wk, motionID);
    if (!v23)
    {
      gOld_MotionNo = 0;
      ++gSame_MotionCount;
    }
  }
LABEL_31:
  if (gOld_MotionNo == motionno)
    goto LABEL_33;
LABEL_36:
  gDoneWork_local = gDoneWork;
  *(_OWORD *)gDoneWork_local = 0u;
  *(_OWORD *)&gDoneWork_local[16] = 0u;
  *(_OWORD *)&gDoneWork_local[32] = 0u;
  *(_OWORD *)&gDoneWork_local[48] = 0u;
  *(u64 *)&gTableIndexTop = 9999;
  gSkillNum = -1;
  gCamMv_local = gCamMv;
  if (!gCamMv_local->ToResultMode)
  {
    gCamMv_local = gCamMv;
    if (gCamMv_local->Use)
    {
      gCamMv_local = gCamMv;
      gCamMv_local->Use = 0;
      *(u64 *)&gCamMv_local->MotionNo = 0;
    }
  }
  v33 = 4;
  if (wk->battlemode != 1)
  {
    while (1)
    {
      v35 = v33 - 4;
      gExTable_local = gExTable;
      if (v33 - 4 >= SLODWORD(gExTable_local->max_length))
        goto LABEL_90;
      if (*(u32 *)(*((u64 *)&gExTable_local->obj.klass + v33) + 16) != 1)
        goto LABEL_71;
      if (*(u32 *)(*((u64 *)&gExTable->obj.klass + v33) + 24) != motionno)
        goto LABEL_71;
      if (*(u16 *)(*((u64 *)&gExTable->obj.klass + v33) + 20) != 1)
      {
        goto LABEL_89;
      }
LABEL_71:
      ++v33;
    }
  }
  while (1)
  {
    v35 = v33 - 4;
    v36 = gExTable;
    if (v33 - 4 >= SLODWORD(v36->max_length))
    {
LABEL_90:
      v26 = 1;
      goto LABEL_92;
    }
    if (*(u32 *)(*((u64 *)&v36->obj.klass + v33) + 16) != 1)
      goto LABEL_56;
    if (*(u32 *)(*((u64 *)&gExTable->obj.klass + v33) + 24) != motionno)
      goto LABEL_56;
    if (*(u16 *)(*((u64 *)&gExTable->obj.klass + v33) + 20) == 1)
    {
LABEL_89:
      gTableIndexTop = v35;
      goto LABEL_90;
    }
LABEL_56:
    ++v33;
  }
  if (gOld_MotionNo != motionno)
    goto LABEL_36;
LABEL_33:
  v26 = 0;
LABEL_92:
  if (gOld_MotionNo == motionno)
    v39 = 1;
  else
    v39 = v26;
  if (v39)
  {
    v333 = &wk->rot;
    gTableIndexTop_local = gTableIndexTop;
    v41 = 0;
    while (1)
    {
      if (gTableIndexTop_local >= SLODWORD(gExTable->max_length))
        break;
      v46 = gTableIndexTop_local - gTableIndexTop;
      if (!gDoneWork[v46])
      {
        v47 = gExTable;
        v48 = v47[gTableIndexTop_local];
        v49 = side;
        side = gTableIndexTop_local;
        switch (v48->Command)
        {
          case 1:
            goto LABEL_378;
          case 2:
            v47 = gExTable;
            gTableIndexTop_local = v47->max_length;
            break;
          case 5:
            v48 = gExTable[gTableIndexTop_local];
            if (v19 < (f32)v48->MotionFrame)
              break;
            tbl = sBtlGetSkilltbl(wk->actwk->use_skillid);
            v50 = Allocate(SBTLSKILLHIT_TBL);
            _ctor(v50, 0);
            gHittbl_Sd_local = gHittbl_Sd;
            gHittbl_Sd_local->motionno = motionno;
            gHittbl_Sd_local->lifetime = gExTable[gTableIndexTop_local]->LifeTime;
            v331 = motionno;
            goto LABEL_129;
          case 6:
            v48 = gExTable[gTableIndexTop_local];
            if (v19 < (f32)v48->MotionFrame)
              break;
            tbl = sBtlGetSkilltbl(wk->actwk->use_skillid);
            v55 = Allocate(SBTLSKILLHIT_TBL);
            _ctor(v55, 0);
            gHittbl_Sd_local = gHittbl_Sd_f;
            gHittbl_Sd_local->motionno = motionno;
            v58 = gExTable[gTableIndexTop_local];
            gHittbl_Sd_local->lifetime = v58->LifeTime;
            Size = v58->Size;
            cy = gHittbl_Sd_local->cy;
            gHittbl_Sd_local->area_r = Size;
            cy->area_r = Size;
            v331 = motionno;
            goto LABEL_129;
          case 7:
            v48 = gExTable[gTableIndexTop_local];
            if (v19 < (f32)v48->MotionFrame)
              break;
            tbl = sBtlGetSkilltbl(wk->actwk->use_skillid);
            v66 = Allocate(SBTLSKILLHIT_TBL);
            _ctor(v66, 0);
            gHittbl_Sd_local = gHittbl_Range;
            gHittbl_Sd_local->motionno = motionno;
            v331 = motionno;
            goto LABEL_129;
          case 8:
            v48 = gExTable[gTableIndexTop_local];
            if (v19 < (f32)v48->MotionFrame)
              break;
            v48 = gExTable[gTableIndexTop_local];
            if ((v48->Flg & 0x8000000) != 0)
            {
              JumpY_SkillSt = sBtlGetJumpY_SkillSt(wk);
              if (JumpY_SkillSt <= -70.0)
                goto LABEL_803;
            }
            if ((gExTable[gTableIndexTop_local]->Flg & 0x4000000) != 0)
            {
              if (sBtlGetJumpY_SkillSt(wk) > -70.0)
                goto LABEL_802;
            }
            Skilltbl = sBtlGetSkilltbl(wk->actwk->use_skillid);
            v70 = Allocate(SBTLSKILLHIT_TBL);
            _ctor(v70, 0);
            tbla = Skilltbl;
            v332 = motionno;
            gHittbl_Range_M_local = gHittbl_Range_M;
            gHittbl_Range_M_local->motionno = motionno;
            v74 = gExTable[gTableIndexTop_local];
            gHittbl_Range_M_local->lifetime = (s32)v74[22];
            v75 = gHittbl_Range_M_local->cy;
            v76 = v74[26];
            gHittbl_Range_M_local->area_r = v76;
            v75->area_r = v76;
            v77 = v74[24];
            v78 = sBtlGetDir180(v77);
            sBtlGetMoveXZ(0.0, 0.0, v78, gExTable[gTableIndexTop_local]->RootPosLen, &gHittbl_Range_M_local->x, &gHittbl_Range_M_local->z);
            if ((gExTable[gTableIndexTop_local]->Flg & 0x80000) != 0)
            {
              sBtlGetMoveXZ(0.0, 0.0, v78, gDistLen, &gHittbl_Range_M_local->x, &gHittbl_Range_M_local->z);
            }
            goto LABEL_405;
          case 9:
            v48 = gExTable[gTableIndexTop_local];
            if (v19 < (f32)v48->MotionFrame)
              break;
            tbl = sBtlGetSkilltbl(wk->actwk->use_skillid);
            v81 = Allocate(SBTLSKILLHIT_TBL);
            _ctor(v81, 0);
            gHittbl_Sd_local = gHittbl_Range_S;
            gHittbl_Sd_local->motionno = motionno;
            RootPosDir = gExTable[gTableIndexTop_local]->RootPosDir;
            v85 = sBtlGetDir180(RootPosDir);
            sBtlGetMoveXZ(0.0, 0.0, v85, gExTable[gTableIndexTop_local]->RootPosLen, &gHittbl_Sd_local->x, &gHittbl_Sd_local->z);
            v331 = motionno;
LABEL_129:
            v334 = v41;
            p_rot = (u32)wk->ListID;
            hitList = wk->hitList;
            use_skillid = wk->actwk->use_skillid;
            acterside = wk->side;
            sBtlCreateHitC_New(hitList, wk, 0, p_rot, use_skillid, tbl, gHittbl_Sd_local, 0, acterside, -1);
            sBtlAddSerialID2();
            wk->hstatus &= ~0x20000u;
            wk->damage_ActerOfsY = gExTable[gTableIndexTop_local]->ActerOfsY;
            goto LABEL_809;
          case 0xA:
            v48 = gExTable[gTableIndexTop_local];
            if (v19 < (f32)v48->MotionFrame)
              break;
            v48 = gExTable[gTableIndexTop_local];
            if ((v48->Flg & 0x8000000) != 0)
            {
              v86 = sBtlGetJumpY_SkillSt(wk);
              if (v86 <= -70.0)
                goto LABEL_803;
            }
            if ((gExTable[gTableIndexTop_local]->Flg & 0x4000000) != 0)
            {
              if (sBtlGetJumpY_SkillSt(wk) > -70.0)
                goto LABEL_802;
            }
            v87 = sBtlGetSkilltbl(wk->actwk->use_skillid);
            v88 = Allocate(SBTLSKILLHIT_TBL);
            _ctor(v88, 0);
            tbla = v87;
            gHittbl_Range_M_local = gHittbl_Range_T;
            goto LABEL_398;
          case 0xB:
            v48 = gExTable[gTableIndexTop_local];
            if (v48->deltaTime > gTime)
              break;
            tblb = sBtlGetSkilltbl(wk->actwk->use_skillid);
            v91 = Allocate(SBTLSKILLHIT_TBL);
            _ctor(v91, 0);
            gHittbl_Range->motionno = motionno;
            gHittbl_Range->lifetime = gExTable[gTableIndexTop_local]->LifeTime;
            v331 = motionno;
            v334 = v41;
            p_rot = (u32)wk->ListID;
            v294 = wk->hitList;
            v295 = wk->actwk->use_skillid;
            side = (u32)wk->side;
            sBtlCreateHitC_New(v294, wk, 0, p_rot, v295, tblb, gHittbl_Range, 0, side, -1);
            sBtlAddSerialID2();
            wk->hstatus &= ~0x20000u;
LABEL_809:
            v297 = gDoneWork;
            motionno = v331;
            ++gSkillNum;
            v134 = (char *)v297 + v46;
            goto LABEL_810;
          case 0xC:
            v48 = gExTable[gTableIndexTop_local];
            if (v48->deltaTime > gTime)
              break;
            v336 = v41;
            ListID = wk->ListID;
            v98 = wk->hitList;
            v99 = p_rot;
            SklID = gExTable[gTableIndexTop_local]->SklID;
            sBtlDltHit_by_UnitSkl(v98, ListID, SklID);
            p_rot = v99;
            v41 = v336;
            v44 = (char *)gDoneWork + v46;
            goto LABEL_102;
          case 0xD:
            v48 = gExTable[gTableIndexTop_local];
            if (v19 < (f32)v48->MotionFrame)
              break;
            v100 = wk->actwk->use_skillid;
            SkillNum = v48->SkillNum;
            HDEffTable_SKLID = sbtlplayertblGetHDEffTable_SKLID(v100, SkillNum);
            if (HDEffTable_SKLID != -1)
            {
              v299 = HDEffTable_SKLID;
              FuncAdd = sbtlplayertblGetHDEffTable_Idx(v299)->FuncAdd;
              if (FuncAdd)
              {
                wk->SlashSkillID = wk->actwk->use_skillid;
                wk->SlashUID = (FuncAdd->invoke_impl)(FuncAdd->method_code, wk, v299, FuncAdd->method);
              }
            }
            v44 = (char *)gDoneWork + v46;
            goto LABEL_102;
          case 0x14:
            v48 = gExTable[gTableIndexTop_local];
            if (v19 < (f32)v48->MotionFrame)
              break;
            v48 = gExTable[gTableIndexTop_local];
            SE = v48->SE;
            v105 = wk->pos.x;
            v106 = wk->pos.y;
            v108 = wk->pos.z;
            v107 = wk->pos.w;
            v344.x = v105;
            v344.y = v106;
            v344.z = v108;
            v344.w = v107;
            sBtlPlay3DSE(SE, v344);
            goto LABEL_839;
          case 0x15:
            v48 = gExTable[gTableIndexTop_local];
            if (v19 < (f32)v48->MotionFrame)
              break;
            v48 = gExTable[gTableIndexTop_local];
            v109 = v48->SE;
            SE_Vol = v48->SE_Vol;
            v111 = wk->pos.x;
            v112 = wk->pos.y;
            v114 = wk->pos.z;
            v113 = wk->pos.w;
            v345.x = v111;
            v345.y = v112;
            v345.z = v114;
            v345.w = v113;
            sBtlPlay3DSE_BaseVol(v109, SE_Vol, v345);
            goto LABEL_839;
          case 0x16:
            v48 = gExTable[gTableIndexTop_local];
            if (v19 < (f32)v48->MotionFrame)
              break;
            v48 = gExTable[gTableIndexTop_local];
            v115 = v48->SE;
            sBtlPlaySE(v115);
            goto LABEL_839;
          case 0x17:
            v48 = gExTable[gTableIndexTop_local];
            if (v19 < (f32)v48->MotionFrame)
              break;
            v116 = wk->pos.x;
            v117 = wk->pos.y;
            v119 = wk->pos.z;
            v118 = wk->pos.w;
            v120 = 65553;
            goto LABEL_251;
          case 0x18:
            v48 = gExTable[gTableIndexTop_local];
            if (v19 < (f32)v48->MotionFrame)
              break;
            v121 = sub_1905740(4, 0);
            v116 = wk->pos.x;
            v117 = wk->pos.y;
            v122 = v121;
            v119 = wk->pos.z;
            v118 = wk->pos.w;
            v120 = v122 + 65634;
LABEL_251:
            v346.x = v116;
            v346.y = v117;
            v346.z = v119;
            v346.w = v118;
            sBtlPlay3DSE(v120, v346);
            goto LABEL_802;
          case 0x19:
            v48 = gExTable[gTableIndexTop_local];
            if (v19 < (f32)v48->MotionFrame)
              break;
            switch ((u32)sub_1905740(6, 0))
            {
              case 0u:
                goto LABEL_286;
              case 1u:
                v124 = &"PVA01A_22A_002";
                goto LABEL_801;
              case 2u:
                v124 = &"PVA01A_22A_003";
                goto LABEL_801;
              case 3u:
                v124 = &"PVA01A_22A_004";
                goto LABEL_801;
              case 4u:
                v124 = &"PVA01A_22A_006";
                goto LABEL_801;
              case 5u:
                v124 = &"PVA01A_22A_008";
                goto LABEL_801;
              default:
                goto LABEL_802;
            }
            goto LABEL_802;
          case 0x1A:
            v48 = gExTable[gTableIndexTop_local];
            if (v19 < (f32)v48->MotionFrame)
              break;
            v125 = sub_1905740(3, 0);
            if (v125 == 2)
            {
              v124 = &"PVA01A_20A_003";
              goto LABEL_801;
            }
            else if (v125 == 1)
            {
              v124 = &"PVA01A_20A_002";
              goto LABEL_801;
            }
            else
            {
              if (v125)
                goto LABEL_802;
              v124 = &"PVA01A_20A_001";
              goto LABEL_801;
            }
            goto LABEL_800;
          case 0x1B:
            v48 = gExTable[gTableIndexTop_local];
            if (v19 < (f32)v48->MotionFrame)
              break;
            v126 = sub_1905740(2, 0);
            if (v126 == 1)
            {
              v124 = &"PVA01A_25A_004";
            }
            else
            {
              if (v126)
                goto LABEL_802;
              v124 = &"PVA01A_22E_000";
LABEL_800:
            }
LABEL_801:
            sndVoicePlayFile(*v124, 0);
            goto LABEL_802;
          case 0x1C:
            v48 = gExTable[gTableIndexTop_local];
            if (v19 < (f32)v48->MotionFrame)
              break;
            switch ((u32)sub_1905740(4, 0))
            {
              case 0u:
                v124 = &"PVA01A_26C_001";
                goto LABEL_801;
              case 1u:
                v124 = &"PVA01A_25C_003";
                goto LABEL_801;
              case 2u:
                goto LABEL_799;
              case 3u:
                v124 = &"PVA01A_26B_000";
                goto LABEL_801;
              default:
                goto LABEL_802;
            }
            goto LABEL_802;
          case 0x1D:
            v48 = gExTable[gTableIndexTop_local];
            if (v19 < (f32)v48->MotionFrame)
              break;
            v48 = gExTable[gTableIndexTop_local];
            if (gSame_MotionCount == v48->SkillNum)
            {
              switch ((u32)sub_1905740(4, 0))
              {
                case 0u:
                  goto LABEL_846;
                case 1u:
LABEL_286:
                  v124 = &"PVA01A_22A_001";
                  goto LABEL_801;
                case 2u:
                  goto LABEL_840;
                case 3u:
                  goto LABEL_799;
                default:
                  goto LABEL_802;
              }
            }
            goto LABEL_802;
          case 0x1E:
            v48 = gExTable[gTableIndexTop_local];
            if (v19 < (f32)v48->MotionFrame)
              break;
            v48 = gExTable[gTableIndexTop_local];
            if (gSame_MotionCount == v48->SkillNum)
            {
              switch ((u32)sub_1905740(4, 0))
              {
                case 0u:
                  v124 = &"PVA01A_20B_000";
                  goto LABEL_801;
                case 1u:
LABEL_846:
                  v124 = &"PVA01A_22A_000";
                  goto LABEL_801;
                case 2u:
                  v124 = &"PVA01A_22D_004";
                  goto LABEL_801;
                case 3u:
                  v124 = &"PVA01A_41B_001";
                  goto LABEL_801;
                default:
                  goto LABEL_802;
              }
            }
            goto LABEL_802;
          case 0x1F:
            v48 = gExTable[gTableIndexTop_local];
            if (v19 < (f32)v48->MotionFrame)
              break;
            switch ((u32)sub_1905740(6, 0))
            {
              case 0u:
                v124 = &"PVA01A_22D_002";
                goto LABEL_801;
              case 1u:
                v124 = &"PVA01A_22D_000";
                goto LABEL_801;
              case 2u:
LABEL_840:
                v124 = &"PVA01A_26A_000";
                goto LABEL_801;
              case 3u:
                v124 = &"PVA01A_26A_001";
                goto LABEL_801;
              case 4u:
                v124 = &"PVA01A_26A_002";
                goto LABEL_801;
              case 5u:
LABEL_799:
                v124 = &"PVA01A_26A_003";
                goto LABEL_801;
              default:
                goto LABEL_802;
            }
            goto LABEL_802;
          case 0x20:
            v48 = gExTable[gTableIndexTop_local];
            if (v19 < (f32)v48->MotionFrame)
              break;
            v48 = gExTable[gTableIndexTop_local];
            VoiceName = v48->VoiceName;
            sndVoicePlayFile(VoiceName, 0);
            goto LABEL_839;
          case 0x28:
            v48 = gExTable[gTableIndexTop_local];
            if (v19 < (f32)v48->MotionFrame)
              break;
            v48 = gExTable[gTableIndexTop_local];
            QuakeTime = v48->QuakeTime;
            QuakePow = v48->QuakePow;
            dds3SetQuake(QuakeTime, QuakePow);
            goto LABEL_839;
          case 0x29:
            v48 = gExTable[gTableIndexTop_local];
            if (v19 < (f32)v48->MotionFrame)
              break;
            dds3StopQuake();
            goto LABEL_802;
          case 0x2A:
            v48 = gExTable[gTableIndexTop_local];
            if (v19 < (f32)v48->MotionFrame)
              break;
            v334 = v41;
            v130 = motionno;
            v48 = gExTable[gTableIndexTop_local];
            VibIn = v48->VibIn;
            VibLife = v48->VibLife;
            p_rot = (u32)v48->VibOut;
            VibPow = v48->VibPow;
            SetVibe(VibIn, VibLife, p_rot, VibPow);
            motionno = v130;
            v134 = (char *)gDoneWork + v46;
LABEL_810:
            v134[32] = 1;
            v41 = v334;
            break;
          case 0x32:
            v48 = gExTable[gTableIndexTop_local];
            if (v19 < (f32)v48->MotionFrame)
              break;
            v135 = wk->rot.x;
            v136 = wk->rot.y;
            v137 = wk->rot.z;
            v138 = wk->rot.w;
            v347.x = v135;
            v347.y = v136;
            v347.z = v137;
            v347.w = v138;
            v139 = sBtlGetRotToDir(v347) + 180.0;
            if (v139 <= 360.0)
              v140 = v139;
            else
              v140 = v139 + -360.0;
            v141 = sBtlGetDir180(v140);
            wk->mv_rotbk = v141;
            FromEuler(0.0, v141 * 0.017453292, 0.0);
            *v333 = vct_A;
            wk->rotbk = vct_A;
            goto LABEL_802;
          case 0x33:
            v48 = gExTable[gTableIndexTop_local];
            if (v19 < (f32)v48->MotionFrame)
              break;
            wk->status &= ~1u;
            goto LABEL_380;
          case 0x34:
            v48 = gExTable[gTableIndexTop_local];
            if (v19 < (f32)v48->MotionFrame)
              break;
            wk->status |= 1u;
            goto LABEL_380;
          case 0x35:
            v48 = gExTable[gTableIndexTop_local];
            if (v19 < (f32)v48->MotionFrame)
              break;
            wk->actaiwk->targetID = -1;
            goto LABEL_380;
          case 0x37:
            v48 = gExTable[gTableIndexTop_local];
            if (v19 < (f32)v48->MotionFrame)
              break;
            sBtlPlayerSetMantOnOff(wk, 1, 0);
            goto LABEL_641;
          case 0x38:
            v48 = gExTable[gTableIndexTop_local];
            if (v19 < (f32)v48->MotionFrame)
              break;
            sBtlPlayerSetMantOnOff(wk, 0, 0);
            goto LABEL_839;
          case 0x3C:
            v48 = gExTable[gTableIndexTop_local];
            if (v19 < (f32)v48->MotionFrame)
              break;
            wk->flg |= 0x80000u;
LABEL_378:
            goto LABEL_380;
          case 0x3D:
            v48 = gExTable[gTableIndexTop_local];
            if (v19 < (f32)v48->MotionFrame)
              break;
            wk->flg &= ~0x80000u;
LABEL_380:
            v43 = gDoneWork;
            goto LABEL_101;
          case 0x3E:
            v48 = gExTable[gTableIndexTop_local];
            if (v19 < (f32)v48->MotionFrame)
              break;
            sBtlBeginSetsuma_EX(wk);
            goto LABEL_802;
          case 0x40:
            v48 = gExTable[gTableIndexTop_local];
            if (v19 < (f32)v48->MotionFrame)
              break;
            tbla = sBtlGetSkilltbl(wk->actwk->use_skillid);
            v144 = Allocate(SBTLSKILLHIT_TBL);
            _ctor(v144, 0);
            gHittbl_Range_M_local = gHittbl_Setsuma;
LABEL_398:
            gHittbl_Range_M_local->motionno = motionno;
            v146 = gExTable[gTableIndexTop_local];
            gHittbl_Range_M_local->lifetime = v146->LifeTime;
            v147 = v146->Size;
            v148 = gHittbl_Range_M_local->cy;
            gHittbl_Range_M_local->area_r = v147;
            v148->area_r = v147;
            v332 = motionno;
            UnitMng = wk->UnitMng;
            targetID = wk->actaiwk->targetID;
            v152 = sBtlSearchUnit_ID(UnitMng, targetID);
            if (v152)
            {
              *(u64 *)&gHittbl_Range_M_local->x = *(u64 *)&v152->pos.x;
              gHittbl_Range_M_local->z = v152->pos.z;
            }
LABEL_405:
            v335 = v41;
            p_rot = (u32)wk->ListID;
            v153 = wk->hitList;
            v154 = wk->actwk->use_skillid;
            v155 = wk->side;
            HitC_New = sBtlCreateHitC_New(v153, wk, 0, p_rot, v154, tbla, gHittbl_Range_M_local, 0, v155, -1);
            sBtlAddSerialID2();
            wk->hstatus &= ~0x20000u;
            motionno = v332;
            v41 = v335;
            v158 = gExTable[gTableIndexTop_local];
            wk->damage_ActerOfsY = v158->ActerOfsY;
            if ((v158->Flg & 0x1000000) != 0)
            {
              v160 = wk->hitList;
              v161 = sBtlSearchHit_SerialID(v160, HitC_New);
              if (v161)
                v161->hitbk_rate = 0.0;
            }
            if ((gExTable[gTableIndexTop_local]->Flg & 0x2000000) != 0)
            {
              v164 = wk->hitList;
              v165 = sBtlSearchHit_SerialID(v164, HitC_New);
              if (v165)
                v165->skillflg |= 0x1000u;
            }
            v168 = gDoneWork;
            ++gSkillNum;
            v44 = (char *)v168 + v46;
            goto LABEL_102;
          case 0x41:
            v48 = gExTable[gTableIndexTop_local];
            if (v19 < (f32)v48->MotionFrame)
              break;
            side = p_rot;
            v169 = wk->actaiwk->targetID;
            if (v169 == -1)
              goto LABEL_888;
            v169 = wk->actaiwk->targetID;
            v171 = wk->UnitMng;
            v172 = sBtlSearchUnit_ID(v171, v169);
            if (!v172)
              goto LABEL_888;
            v173 = v172;
            devilid = (u16)v172->para->devilid;
            if (devilid == 258)
            {
LABEL_909:
              sBtlSetDevilID_EnemyDrawOnOff(258, 1);
              sBtlSetDevilID_EnemyRot(258, 180.0);
              sBtlSetDevilID_EnemyTheWorld(258, 1);
            }
            else
            {
              if (devilid == 267)
              {
LABEL_440:
                if ((v172->side & 2) != 0 && (v172->status & 0x4000000) == 0 && (v172->vstatus & 0x10000) == 0)
                {
                  if (sBtlCheckDamageTarget(v173))
                  {
                    color = v173->color;
                    v173->ditherAlpha = 1;
                    v173->dissolveAlpha = 1.0;
                    v173->color = color | 0xFF000000;
                    v173->vstatus &= 0xFFFFFFFC;
                  }
                }
LABEL_888:
                sBtlSetTargetEnemyDrawOnOff(wk, 1);
                sBtlSetTargetEnemyTheWorld(wk, 1);
                sBtlGetZeroPos((f32 *)&ZeroY + 1, &ZeroY, &ZeroZ);
                v309 = wk->actwk->use_skillid;
                if (v309 == 1301)
                {
                  v315 = ZeroZ;
                  v316 = ZeroY;
                  v317 = -100.0;
                  v313 = *(f32 *)&v316 + 0.0;
                  v312 = *((f32 *)&v316 + 1) + 100.0;
                }
                else
                {
                  if (v309 != 1300)
                  {
                    if (v309 == 1299)
                    {
                      v310 = ZeroY;
                      v311 = ZeroZ;
                      v312 = *((f32 *)&v310 + 1) + 0.0;
                      v313 = *(f32 *)&v310 + 0.0;
                      v314 = v311 + 0.0;
LABEL_905:
                      sBtlSetTargetEnemyPosRot(wk, v312, v313, v314, 180.0);
                    }
                    sBtlSetTargetEnemyMotion(wk, 0);
                    goto LABEL_802;
                  }
                  v318 = ZeroY;
                  v315 = ZeroZ;
                  v317 = -400.0;
                  v312 = *((f32 *)&v318 + 1) + 0.0;
                  v313 = *(f32 *)&v318 + 0.0;
                }
                v314 = v315 + v317;
                goto LABEL_905;
              }
              switch ((s16)devilid)
              {
                case 310:
                  goto LABEL_440;
                case 312:
                case 313:
                  sBtlSetDevilID_EnemyDrawOnOff(259, 1);
                  sBtlSetDevilID_EnemyRot(259, 180.0);
                  sBtlSetDevilID_EnemyTheWorld(259, 1);
                  v308 = 259;
                  break;
                case 314:
                  goto LABEL_909;
                case 315:
                  sBtlSetDevilID_EnemyDrawOnOff(260, 1);
                  sBtlSetDevilID_EnemyRot(260, 180.0);
                  sBtlSetDevilID_EnemyTheWorld(260, 1);
                  v308 = 260;
                  break;
                default:
                  goto LABEL_888;
              }
              UnitFromDevilID = sBtlGetUnitFromDevilID(v308);
              UnitFromDevilID->next_motion_not_hokan = 1;
              sBtlSetMotion(UnitFromDevilID, 0, 0, 0, 0);
            }
LABEL_802:
LABEL_803:
LABEL_100:
            v43 = gDoneWork;
LABEL_101:
            v44 = (char *)v43 + v46;
LABEL_102:
            v44[32] = 1;
            break;
          case 0x42:
            v48 = gExTable[gTableIndexTop_local];
            if (v19 < (f32)v48->MotionFrame)
              break;
            sBtlSetSetsuma_DofEnd(wk);
            goto LABEL_802;
          case 0x43:
            v48 = gExTable[gTableIndexTop_local];
            if (v19 < (f32)v48->MotionFrame)
              break;
            sBtlPlayerJyusoEffOnOff(wk, 0);
            goto LABEL_839;
          case 0x44:
            v48 = gExTable[gTableIndexTop_local];
            if (v19 < (f32)v48->MotionFrame)
              break;
            sBtlPlayerPlayer_Bad_Push(wk);
            goto LABEL_802;
          case 0x46:
            v48 = gExTable[gTableIndexTop_local];
            if (v19 < (f32)v48->MotionFrame)
              break;
            camera = wk->scene->camera;
            v179 = gTableIndexTop_local;
            v181 = gCamMv;
            v181->Use = 1;
            v181->MotionNo = motionno;
            v181->TimeNomal = 0.0;
            v182 = *(u64 *)&v181->EX;
            EZ = v181->EZ;
            v184 = *(u64 *)&v181->TgtEX;
            TgtEZ = v181->TgtEZ;
            v186 = gExTable[v179];
            v181->SFrame = (f32)v186->MotionFrame;
            v181->EFrame = v186->CamEFrame;
            Flg = v186->Flg;
            v181->BlandMode = 0;
            v181->Flg = Flg;
            *(_OWORD *)&v181->CamMode = *(_OWORD *)&v186->CamMode;
            *(_OWORD *)&v181->EX = *(_OWORD *)&v186->CamEX;
            *(u64 *)&v181->EFov = *(u64 *)&v186->CamEFov;
            v181->EUpV = v186->CamEUpV;
            *(_OWORD *)&v181->TgtSX = *(_OWORD *)&v186->CamTgtSX;
            v181->TgtEY = v186->CamTgtEY;
            v189 = gCamMv;
            v190 = gExTable[v179];
            v189->TgtEZ = v190->CamTgtEZ;
            *(u64 *)&v189->SOfsY = *(u64 *)&v190->CamSOfsY;
            v191 = *(u64 *)&v190->CamTgtSOfsY;
            LOBYTE(v190) = v189->Flg;
            *(u64 *)&v189->TgtSOfsY = v191;
            if (((u8)v190 & 8) != 0)
            {
              v189 = gCamMv;
              *(u64 *)&v189->SX = *(u64 *)&camera->camerapos.x;
              v189->SZ = camera->camerapos.z;
LABEL_474:
              v192 = gCamMv;
              if ((v192->Flg & 0x10) == 0)
                goto LABEL_475;
              goto LABEL_749;
            }
            {
              goto LABEL_474;
            }
            v192 = gCamMv;
            if ((v192->Flg & 0x10) == 0)
            {
LABEL_475:
              goto LABEL_476;
            }
LABEL_749:
            v192 = gCamMv;
            *(u64 *)&v192->SX = v182;
            v192->SZ = EZ;
LABEL_476:
            v193 = gCamMv;
            if ((v193->Flg & 0x20) == 0)
            {
              goto LABEL_478;
            }
            v193 = gCamMv;
            v193->SOfsY = camera->camerapos.y;
LABEL_478:
            v194 = gCamMv;
            if ((v194->Flg & 0x200) == 0)
            {
              goto LABEL_480;
            }
            v194 = gCamMv;
            *(u64 *)&v194->TgtSX = *(u64 *)&camera->targetpos.x;
            v194->TgtSZ = camera->targetpos.z;
LABEL_480:
            v195 = gCamMv;
            if ((v195->Flg & 0x400) == 0)
            {
              goto LABEL_482;
            }
            v195 = gCamMv;
            v283 = camera->targetpos.x;
            v195->TgtSY = 0.0;
            v195->TgtSX = v283;
            v195->TgtSZ = camera->targetpos.z;
LABEL_482:
            v196 = gCamMv;
            if ((v196->Flg & 0x1000) == 0)
            {
              goto LABEL_484;
            }
            v196 = gCamMv;
            v196->TgtSOfsY = camera->targetpos.y;
LABEL_484:
            v197 = gCamMv;
            if ((v197->Flg & 0x800) == 0)
            {
              goto LABEL_486;
            }
            v197 = gCamMv;
            *(u64 *)&v197->TgtSX = v184;
            v197->TgtSZ = TgtEZ;
LABEL_486:
            p_rot = gCamMv;
            v199 = *(f32 *)(p_rot + 44);
            if (v199 == 1.0)
            {
              v200 = camera->targetpos.x;
              v201 = camera->targetpos.y;
              v202 = camera->targetpos.z;
              p_rot = gCamMv;
              v203 = *(f32 *)(p_rot + 48);
              v204 = *(f32 *)(p_rot + 52);
              v205 = *(f32 *)(p_rot + 56);
              LenXYZ = sBtlGetLenXYZ(v203, v204, v205, v200, v201, v202);
              *(f32 *)(p_rot + 88) = LenXYZ;
              v209 = gExTable;
              v210 = gCamMv;
              v211 = v210->SY - v201;
              v210->ELen = v209[v179]->CamELen;
              DirY = sBtlGetDirY(v210->SLen, v211);
              v214 = gCamMv;
              v214->CamSYDir = DirY;
              SX = v214->SX;
              SZ = v214->SZ;
              v214->CamEYDir = gExTable[v179]->CamEYDir;
              PosToDir = sBtlGetPosToDir(v200, v202, SX, SZ);
              v214->SDir = PosToDir;
              gCamMv->EDir = gCamMv->SDir;
              goto LABEL_868;
            }
            p_rot = gCamMv;
            v199 = *(f32 *)(p_rot + 44);
            if (v199 == 2.0)
            {
              if (!v284)
              {
                p_rot = gCamMv;
              }
              v285 = gExTable[gTableIndexTop_local];
              *(u64 *)(p_rot + 104) = *(u64 *)&v285->CamSDir;
              *(u64 *)(p_rot + 88) = *(u64 *)&v285->CamSLen;
            }
            else
            {
              if (!v284)
              {
                p_rot = gCamMv;
                v199 = *(f32 *)(p_rot + 44);
              }
              if (v199 == 3.0)
              {
                p_rot = gCamMv;
                *(u32 *)(p_rot + 88) = *(u32 *)(p_rot + 92);
                v303 = gExTable[gTableIndexTop_local];
                *(f32 *)(p_rot + 92) = v303->CamELen;
                *(u32 *)(p_rot + 112) = *(u32 *)(p_rot + 116);
                *(f32 *)(p_rot + 116) = v303->CamEYDir;
              }
            }
LABEL_868:
            if (wk->CameraLockOn)
            {
              v305 = gCamMv;
              v305->TgtUnitID = wk->CameraLockOnTgtID;
            }
            else
            {
              if (wk->actaiwk->targetID == -1)
              {
                if (v306)
                {
                  v307 = -1;
                }
                else
                {
                  v307 = wk->actaiwk->targetID;
                }
                gCamMv->TgtUnitID = v307;
              }
              else
              {
                gCamMv->TgtUnitID = -1;
              }
            }
            goto LABEL_803;
          case 0x47:
            v48 = gExTable[gTableIndexTop_local];
            MotionFrame = v48->MotionFrame;
            if (v19 < MotionFrame)
              break;
            v48 = gExTable[gTableIndexTop_local];
            MotionFrame = v48->MotionFrame;
            v220 = gCamMv;
            v220->Use = 1;
            v220->MotionNo = motionno;
            v220->TimeNomal = 0.0;
            v220->SFrame = MotionFrame;
            CamEFrame = v48->CamEFrame;
            v220->BlandMode = 1;
            v220->EFrame = CamEFrame;
            v220 = gCamMv;
            v223 = wk->scene->camera;
            *(u64 *)&v220->SX = *(u64 *)&v223->camerapos.x;
            v220->SZ = v223->camerapos.z;
            *(u64 *)&v220->TgtSX = *(u64 *)&v223->targetpos.x;
            v220->TgtSZ = v223->targetpos.z;
            v224 = gDoneWork;
            goto LABEL_642;
          case 0x48:
            v48 = gExTable[gTableIndexTop_local];
            if (v19 < (f32)v48->MotionFrame)
              break;
            gCamMv->Use = 0;
            sBtlNoHokan();
            goto LABEL_839;
          case 0x49:
            v48 = gExTable[gTableIndexTop_local];
            if (v19 < (f32)v48->MotionFrame)
              break;
            v226 = wk;
            encountno = v226->encountno;
            if (encountno == 59)
            {
              v228 = wk->actaiwk->targetID;
              if (v228 == -1)
                goto LABEL_914;
              v229 = v226->UnitMng;
              v231 = sBtlSearchUnit_ID(v229, v228);
              if (!v231)
                goto LABEL_914;
LABEL_518:
              v232 = (u16)v231->para->devilid;
              v234 = v232 == 258 || v232 == 314;
              goto LABEL_783;
              if (!v231)
              {
LABEL_914:
                v234 = 0;
                goto LABEL_783;
              }
              goto LABEL_518;
            }
            encountno = wk->encountno;
            v234 = encountno == 60;
LABEL_783:
            v286 = !v234;
            v288 = gExTable[gTableIndexTop_local]->Flg;
            if ((v288 & 0x40000) == 0)
              v286 = 1;
            if ((v286 & 1) != 0)
            {
              if (!v287)
              {
                v288 = gExTable[gTableIndexTop_local]->Flg;
              }
              v289 = (v288 & 0x20000) == 0 || v234;
              if ((v289 & 1) != 0)
              {
                v291 = gCamMv;
                v291->Use = 1;
                v291->MotionNo = motionno;
                v291->TimeNomal = 0.0;
                v292 = gExTable[gTableIndexTop_local];
                v291->SFrame = (f32)v292->MotionFrame;
                v291->EFrame = v292->CamEFrame;
                v293 = v292->Flg;
                v291->BlandMode = 0;
                v291->Flg = v293;
                *(_OWORD *)&v291->CamMode = *(_OWORD *)&v292->CamMode;
                *(_OWORD *)&v291->TgtSX = *(_OWORD *)&v292->CamTgtSX;
                *(u64 *)&v291->TgtEY = *(u64 *)&v292->CamTgtEY;
                *(_OWORD *)&v291->EX = *(_OWORD *)&v292->CamEX;
                *(u64 *)&v291->EFov = *(u64 *)&v292->CamEFov;
                v291->EUpV = v292->CamEUpV;
                v239 = gDoneWork;
LABEL_551:
                v239[v46] = 1;
                break;
              }
              goto LABEL_100;
            }
            else if (v287)
            {
              goto LABEL_100;
            }
LABEL_839:
            goto LABEL_100;
          case 0x4B:
            v48 = gExTable[gTableIndexTop_local];
            if (v19 >= (f32)v48->MotionFrame)
            {
              v48 = gExTable[gTableIndexTop_local];
              gCamJump_local = gCamJump;
              gCamJump_local->Use = 1;
              gCamJump_local->Time = 0.0;
              gCamJump_local->Y = 0.0;
              v237 = *(u64 *)&v48->CamJumpSpdS;
              *(u64 *)&gCamJump_local->CamJumpSpdS = v237;
              gCamJump_local->Speed = -80.0 * *(f32 *)&v237;
              gDoneWork[v46] = 1;
            }
            break;
          case 0x4C:
            v48 = gExTable[gTableIndexTop_local];
            if (v19 < (f32)v48->MotionFrame)
              break;
            gCamJump->Pause = 1;
            goto LABEL_550;
          case 0x4D:
            v48 = gExTable[gTableIndexTop_local];
            if (v19 < (f32)v48->MotionFrame)
              break;
            v48 = gExTable[gTableIndexTop_local];
            v238 = gCamJump;
            v238->Pause = 0;
            v238->CamJumpSpdD = v48->CamJumpSpdD;
            v43 = gDoneWork;
            goto LABEL_101;
          case 0x4E:
            v48 = gExTable[gTableIndexTop_local];
            if (v19 < (f32)v48->MotionFrame)
              break;
            gCamJump2->Use = 1;
LABEL_550:
            v239 = gDoneWork;
            goto LABEL_551;
          case 0x4F:
            v48 = gExTable[gTableIndexTop_local];
            if (v19 >= (f32)v48->MotionFrame)
            {
              v41 = 1;
              gDoneWork[v46] = 1;
            }
            break;
          case 0x52:
            v48 = gExTable[gTableIndexTop_local];
            if (v19 < (f32)v48->MotionFrame)
              break;
            sBtlPlayerSetEnemyDrawOnOff(0);
            goto LABEL_802;
          case 0x53:
            v48 = gExTable[gTableIndexTop_local];
            if (v19 < (f32)v48->MotionFrame)
              break;
            sBtlPlayerSetEnemyDrawOnOff(1);
            goto LABEL_640;
          case 0x54:
            v48 = gExTable[gTableIndexTop_local];
            if (v19 < (f32)v48->MotionFrame)
              break;
            if (wk->encountno == 59)
            {
              if (gExTable[gTableIndexTop_local]->Variation == 2)
              {
                Variation = 4;
                goto LABEL_744;
              }
            }
            v282 = gExTable[gTableIndexTop_local];
            Variation = v282->Variation;
LABEL_744:
            sBtlPlayerSetEnemyPos(Variation);
            goto LABEL_802;
          case 0x55:
            v48 = gExTable[gTableIndexTop_local];
            if (v19 < (f32)v48->MotionFrame)
              break;
            v244 = 0;
            goto LABEL_597;
          case 0x56:
            v48 = gExTable[gTableIndexTop_local];
            if (v19 < (f32)v48->MotionFrame)
              break;
            if (wk->cmbSkl->bRun)
              goto LABEL_802;
            v244 = 1;
LABEL_597:
            sBtlPlayerSetEnemyHPDrawOnOff(v244);
            goto LABEL_802;
          case 0x57:
            v48 = gExTable[gTableIndexTop_local];
            if (v19 < (f32)v48->MotionFrame)
              break;
            sBtlReleaseSTP_List(wk->stpList, 2u);
            sBtlForceDeleteAll(0);
            DeleteAll();
LABEL_727:
            DeleteAll();
            goto LABEL_802;
          case 0x58:
            v48 = gExTable[gTableIndexTop_local];
            if (v19 < (f32)v48->MotionFrame)
              break;
            if (wk->cmbSkl->bRun)
              goto LABEL_802;
            v249 = gExTable[gTableIndexTop_local]->Variation;
            if (v249 == 2)
            {
              v250 = 60;
            }
            else if (v249 == 1)
            {
              v250 = 59;
            }
            else
            {
              if (v249)
                goto LABEL_802;
              v250 = 58;
            }
            v252 = wk;
            v253 = v250;
LABEL_626:
            sBtlSetMotion(v252, v253, 0, 0, 0);
            goto LABEL_802;
          case 0x59:
            v48 = gExTable[gTableIndexTop_local];
            if (v19 < (f32)v48->MotionFrame)
              break;
            v253 = 130;
            v252 = wk;
            goto LABEL_626;
          case 0x5A:
            v48 = gExTable[gTableIndexTop_local];
            if (v19 < (f32)v48->MotionFrame)
              break;
            sBtlPlayerSetNakamaDrawOnOff(0);
            goto LABEL_802;
          case 0x5B:
            v48 = gExTable[gTableIndexTop_local];
            if (v19 < (f32)v48->MotionFrame)
              break;
            sBtlPlayerSetNakamaDrawOnOff(1);
LABEL_640:
LABEL_641:
            v224 = gDoneWork;
LABEL_642:
            v224[v46] = 1;
            break;
          case 0x5C:
            v48 = gExTable[gTableIndexTop_local];
            if (v19 < (f32)v48->MotionFrame)
              break;
            v254 = 0;
            goto LABEL_658;
          case 0x5D:
            v48 = gExTable[gTableIndexTop_local];
            if (v19 < (f32)v48->MotionFrame)
              break;
            if (wk->cmbSkl->bRun)
              goto LABEL_802;
            v254 = 1;
LABEL_658:
            sBtlPlayerSetNakamaHPDrawOnOff(v254);
            goto LABEL_802;
          case 0x64:
            v48 = gExTable[gTableIndexTop_local];
            if (v19 < (f32)v48->MotionFrame)
              break;
            v256 = wk->pos.x;
            v257 = wk->pos.z;
            v48 = gExTable[gTableIndexTop_local];
            v259 = v48->RootPosDir;
            RootPosLen = v48->RootPosLen;
            sBtlGetMoveXZ(v256, v257, Dir180 + v259, RootPosLen, &ToX, (f32 *)&v339 + 1);
            v261 = *((f32 *)&v339 + 1);
            v260 = ToX;
            GroundPos = sBtlGetGroundPos(v260, v261);
            Add(ToX, GroundPos, *((f32 *)&v339 + 1), Dir180, gExTable[gTableIndexTop_local]->Variation, 0);
            goto LABEL_839;
          case 0x65:
            v48 = gExTable[gTableIndexTop_local];
            if (v19 < (f32)v48->MotionFrame)
              break;
            Add(wk->ListID, 0);
            goto LABEL_802;
          case 0x66:
            v48 = gExTable[gTableIndexTop_local];
            if (v19 < (f32)v48->MotionFrame)
              break;
            AW_JumpSetPosLinkOff(wk->ListID);
            goto LABEL_802;
          case 0x67:
            v48 = gExTable[gTableIndexTop_local];
            if (v19 < (f32)v48->MotionFrame)
              break;
            Add(wk->ListID, 0);
            goto LABEL_802;
          case 0x68:
            v48 = gExTable[gTableIndexTop_local];
            if (v19 < (f32)v48->MotionFrame)
              break;
            AW_JumpSetLanding(wk->ListID);
            goto LABEL_802;
          case 0x69:
            v48 = gExTable[gTableIndexTop_local];
            if (v19 < (f32)v48->MotionFrame)
              break;
            sBtlJumpHAtk1Start(wk);
            goto LABEL_802;
          case 0x6A:
            v48 = gExTable[gTableIndexTop_local];
            if (v19 < (f32)v48->MotionFrame)
              break;
            Add(wk->ListID, 0);
            goto LABEL_802;
          case 0x6B:
            v48 = gExTable[gTableIndexTop_local];
            if (v19 < (f32)v48->MotionFrame)
              break;
            v263 = wk->ListID;
            wk->SlashSkillID = wk->actwk->use_skillid;
            v48 = gExTable[gTableIndexTop_local];
            v264 = AW_ApproachAdd(v263, v48->RootPosDir, v48->RootPosLen);
            goto LABEL_707;
          case 0x6C:
            v48 = gExTable[gTableIndexTop_local];
            if (v19 < (f32)v48->MotionFrame)
              break;
            v265 = wk->ListID;
            v266 = wk->actwk->use_skillid;
            wk->SlashSkillID = v266;
            v266 = wk->actwk->use_skillid;
            v48 = gExTable[gTableIndexTop_local];
            v264 = Add(v265, v48->Speed, v48->Variation, v266, 0);
LABEL_707:
            wk->SlashUID = v264;
            goto LABEL_839;
          case 0x6D:
            v48 = gExTable[gTableIndexTop_local];
            if (v19 < (f32)v48->MotionFrame)
              break;
            v267 = wk->pos.x;
            v268 = wk->pos.z;
            v48 = gExTable[gTableIndexTop_local];
            v270 = v48->RootPosDir;
            v269 = v48->RootPosLen;
            sBtlGetMoveXZ(v267, v268, Dir180 + v270, v269, &v339, (f32 *)&v338 + 1);
            v272 = *((f32 *)&v338 + 1);
            v271 = *(f32 *)&v339;
            v273 = sBtlGetGroundPos(v271, v272);
            AW_JumpAdd(*(f32 *)&v339, v273, *((f32 *)&v338 + 1), Dir180);
            goto LABEL_839;
          case 0x6E:
            v48 = gExTable[gTableIndexTop_local];
            if (v19 < (f32)v48->MotionFrame)
              break;
            v274 = wk->ListID;
            v48 = gExTable[gTableIndexTop_local];
            Add(v274, v48->RootPosDir, v48->RootPosLen, v48->Size, 0);
            goto LABEL_839;
          case 0x6F:
            v48 = gExTable[gTableIndexTop_local];
            if (v19 >= (f32)v48->MotionFrame)
              goto LABEL_727;
            break;
          case 0x70:
            v48 = gExTable[gTableIndexTop_local];
            if (v19 < (f32)v48->MotionFrame)
              break;
            v275 = wk->ListID;
            v48 = gExTable[gTableIndexTop_local];
            Add(v275, v48->Variation, 0);
            goto LABEL_839;
          case 0x71:
            v48 = gExTable[gTableIndexTop_local];
            if (v19 < (f32)v48->MotionFrame)
              break;
            v276 = wk->rot.x;
            v277 = wk->rot.y;
            v278 = wk->rot.z;
            v279 = wk->rot.w;
            v348.x = v276;
            v348.y = v277;
            v348.z = v278;
            v348.w = v279;
            v280 = sBtlGetRotToDir(v348);
            v281 = wk->pos.y + -148.0;
            sBtlGetMoveXZ(wk->pos.x, wk->pos.z, v280 + 8.0, 79.0, &v338, &v337);
            AW_BulletAdd_Setsuma(*(f32 *)&v338, v281, v337, v280);
            goto LABEL_802;
          default:
            side = v49;
            break;
        }
      }
      ++gTableIndexTop_local;
    }
    v320 = v41;
  }
  else
  {
    v320 = 0;
  }
  gOld_MotionNo = motionno;
  motion_serialno = wk->motion_serialno;
  gOld_MotionFrame = v19;
  gOld_MotionSerialNo = motion_serialno;
  gTime = gTime + VRF_DeltaTime;
  CamMvUpdate(sBtlPlayerEx);
  CamJumpUpdate(wk);
  CamJumpUpdate2(wk);
  sBtlPlayerKudaOpenEffUpdate(wk);
  sBtlPlayerMagSdLcAxEffUpdate(wk);
  if (v320)
  {
    Proc(0);
  }
}
