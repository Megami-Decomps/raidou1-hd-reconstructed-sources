#include "types.h"
#include "SBTLACTION_ST.h"
#include "SKLID.h"
#include "aw_decoy.h"
#include "aw_groundflame.h"
#include "aw_mat_bomb.h"
#include "aw_plasmalaser.h"
#include "aw_prediction.h"
#include "aw_sbattle.h"
#include "aw_summonng.h"
#include "aw_xatk.h"
#include "bsflow.h"
#include "dds3basic.h"
#include "dds3effect_blend.h"
#include "dds3kerneldraw.h"
#include "dds3unitobjectbasic.h"
#include "mdl.h"
#include "sbtl.h"
#include "sbtlactai.h"
#include "sbtlaction.h"
#include "sbtlai.h"
#include "sbtlbossevent.h"
#include "sbtlcalc.h"
#include "sbtlcamera.h"
#include "sbtlcmbskl.h"
#include "sbtldmg.h"
#include "sbtleff.h"
#include "sbtlencount.h"
#include "sbtlexp.h"
#include "sbtlmain.h"
#include "sbtlplayer.h"
#include "sbtlplayer_common.h"
#include "sbtlplayer_spirit.h"
#include "sbtlplayertbl.h"
#include "sbtlscript.h"
#include "sbtlskill.h"
#include "sbtlsm.h"
#include "sbtlsound.h"
#include "sbtlsub.h"
#include "sbtlsupport.h"
#include "sbtlunit.h"
#include "sbtlvisual.h"
#include "scr.h"
#include "sdf_vu0.h"
#include "sdfquat.h"
#include "smnr.h"
#include "sndmanager.h"
#include "sndsmghd.h"
#include "tips.h"

#define THON_cylinder 125
#define TBOB_cylinder 250
#define TYUK_cylinder 450
#define ICI_MOVESPD_H 45
#define ICI_MOVESPD_L 35
#define ICI_MOVE_WAIT0 60
#define ICI_MOVE_WAIT1 60
#define ICI_MOVE_WAIT2 0
#define ICI_MOVE_WAIT3 120
#define ICI_LPMSPD 0.5
#define ICI_STMSPD 0.5
#define DANG_WAIT_MOTION 60
#define LASER_TIME 7
#define LASER_MAX 30
#define MUNAKA_WAIT_HALF 30
#define MUNAKA_WAIT_TIME1 60
#define MUNAKA_WAIT_TIME1_HALF 90
#define MUNAKA_WAIT_TIME2 120
#define MUNAKA_WAIT_TIME3 180
#define MUNAKA_WAIT_TIME5 300
#define EXPLOSION_R 1000
#define EFF_OFF_TIME 89
#define SBTLMAP_COLOR_LAST_SHIKAI 2151694400
#define SBTLMAP_COLOR_LAST_DEAD 2149128473

typedef enum {
    UNIT_MOT_WAIT = 0,
    UNIT_MOT_DAMAGE = 1,
    UNIT_MOT_BST_W = 2,
    UNIT_MOT_TADANOTUKI = 3,
    UNIT_MOT_HUUMAOK = 4,
    UNIT_MOT_WALK = 5,
    UNIT_MOT_GUN = 6,
    UNIT_MOT_HGUNN = 7,
    UNIT_MOT_IAITATE = 8,
    UNIT_MOT_MAWASIKERI = 9,
    UNIT_MOT_RAINPIKE = 10,
    UNIT_MOT_RENDUKI = 11,
    UNIT_MOT_SORDR = 12,
    UNIT_MOT_DEAD = 13,
    UNIT_MOT_DOWN = 14,
    UNIT_MOT_BWALK = 15,
    UNIT_MOT_KAIT_C = 16,
    UNIT_MOT_KAIT_CM = 17,
    UNIT_MOT_MEIREI = 18,
    UNIT_MOT_HGUNR = 19,
    UNIT_MOT_NSORD1 = 20,
    UNIT_MOT_NSORD2 = 21,
    UNIT_MOT_NSORD3 = 22,
    UNIT_MOT_SUMMON = 23,
    UNIT_MOT_OIUCHI = 24,
    UNIT_MOT_HIKOUT = 25,
    UNIT_MOT_SD_COMBO4 = 26,
    UNIT_MOT_GUN_C = 27,
    UNIT_MOT_ORENKEI = 30,
    UNIT_MOT_SD_GUARD = 29,
    UNIT_MOT_RETURN = 31,
    UNIT_MOT_DYWAIT = 32,
    UNIT_MOT_DYMOVE = 33,
    UNIT_MOT_MAGTUKI = 34,
    UNIT_MOT_HUUMA = 35,
    UNIT_MOT_BAKUTEN = 36,
    UNIT_MOT_ZENTEN = 37,
    UNIT_MOT_YOBIYO = 38,
    UNIT_MOT_ITEMU = 39,
    UNIT_MOT_LC_GUARD = 40,
    UNIT_MOT_AX_GUARD = 41,
    UNIT_MOT_LOOKUP_IN = 42,
    UNIT_MOT_LOOKUP_LOOP = 43,
    UNIT_MOT_RESV_2C = 44,
    UNIT_MOT_RESV_2D = 45,
    UNIT_MOT_RESV_2E = 46,
    UNIT_MOT_RESV_2F = 47,
    UNIT_MOT_RESV_30 = 48,
    UNIT_MOT_SD_COMBI1 = 49,
    UNIT_MOT_LC_COMBI1 = 50,
    UNIT_MOT_AX_COMBI1 = 51,
    UNIT_MOT_COMBI_KAI = 52,
    UNIT_MOT_LC_COMBO5 = 53,
    UNIT_MOT_CHG_WALK = 54,
    UNIT_MOT_CHG_WAIT = 55,
    UNIT_MOT_CHG_ST = 56,
    UNIT_MOT_CHG_ED = 57,
    UNIT_MOT_SD_COMBI2 = 58,
    UNIT_MOT_LC_COMBI2 = 59,
    UNIT_MOT_AX_COMBI2 = 60,
    UNIT_MOT_RESV_3D = 61,
    UNIT_MOT_RESV_3E = 62,
    UNIT_MOT_RESV_3F = 63,
    UNIT_MOT_RESV_40 = 64,
    UNIT_MOT_RESV_41 = 65,
    UNIT_MOT_RESV_42 = 66,
    UNIT_MOT_RESV_43 = 67,
    UNIT_MOT_RESV_44 = 68,
    UNIT_MOT_RESV_45 = 69,
    UNIT_MOT_RESV_46 = 70,
    UNIT_MOT_RESV_47 = 71,
    UNIT_MOT_RESV_48 = 72,
    UNIT_MOT_RESV_49 = 73,
    UNIT_MOT_GUN_TYUSHYOT = 74,
    UNIT_MOT_GUN_DAISHYOT = 75,
    UNIT_MOT_GUN_CHG = 76,
    UNIT_MOT_GUN_CHG_ST = 77,
    UNIT_MOT_GUN_CHG_ED = 78,
    UNIT_MOT_GUN_CHG_MF = 79,
    UNIT_MOT_GUN_CHG_MR = 80,
    UNIT_MOT_GUN_CHG_MB = 81,
    UNIT_MOT_GUN_CHG_ML = 82,
    UNIT_MOT_SETSUMA1 = 83,
    UNIT_MOT_SETSUMA2 = 84,
    UNIT_MOT_SETSUMA3 = 85,
    UNIT_MOT_SETSUMA4 = 86,
    UNIT_MOT_JUMPATK1L = 87,
    UNIT_MOT_JUMPATK2A = 88,
    UNIT_MOT_JUMPATK1 = 89,
    UNIT_MOT_JUMPATK2 = 90,
    UNIT_MOT_JUMP_U = 91,
    UNIT_MOT_JUMP_D = 92,
    UNIT_MOT_JUMP_L = 93,
    UNIT_MOT_APPROACH = 94,
    UNIT_MOT_APPROACHATK = 95,
    UNIT_MOT_APPROACH_ED = 96,
    UNIT_MOT_SCOMBO1 = 97,
    UNIT_MOT_SCOMBO2 = 98,
    UNIT_MOT_SCOMBO3 = 99,
    UNIT_MOT_SCOMBO4 = 100,
    UNIT_MOT_SCOMBO5 = 101,
    UNIT_MOT_SCOMBO1A = 102,
    UNIT_MOT_N_RUN = 103,
    UNIT_MOT_RUN_TO_IDLE = 104,
    UNIT_MOT_RUN_R = 105,
    UNIT_MOT_RUN_L = 106,
    UNIT_MOT_TURN_R = 107,
    UNIT_MOT_TURN_B = 108,
    UNIT_MOT_TURN_L = 109,
    UNIT_MOT_TURN_ED = 110,
    UNIT_MOT_SD_GUARD_ST = 111,
    UNIT_MOT_SD_GUARD_ED = 112,
    UNIT_MOT_SD_GUARD_H = 113,
    UNIT_MOT_LC_GUARD_ST = 114,
    UNIT_MOT_LC_GUARD_ED = 115,
    UNIT_MOT_LC_GUARD_H = 116,
    UNIT_MOT_AX_GUARD_ST = 117,
    UNIT_MOT_AX_GUARD_ED = 118,
    UNIT_MOT_AX_GUARD_H = 119,
    UNIT_MOT_CAMLOCKON_MF = 120,
    UNIT_MOT_CAMLOCKON_MR = 121,
    UNIT_MOT_CAMLOCKON_MB = 122,
    UNIT_MOT_CAMLOCKON_ML = 123,
    UNIT_MOT_JUMPHATK1 = 124,
    UNIT_MOT_JUMPHATK1L = 125,
    UNIT_MOT_SETSUMA1_D = 126,
    UNIT_MOT_SETSUMA1_R = 127,
    UNIT_MOT_BAD_ST = 128,
    UNIT_MOT_BAD_ED = 129,
    UNIT_MOT_WAIT_CLOAK = 130,
    UNIT_MOT_DOWN_S = 131,
    UNIT_MOT_HUUMA_KUDA = 132,
    UNIT_MOT_RUN_R2 = 133,
    UNIT_MOT_RUN_L2 = 134,
    UNIT_MOT_ZEN_TO_RUN = 135,
    UNIT_MOT_HUUMA_ED = 136,
    UNIT_MOT_HUUMA_ST = 137,
    UNIT_MOT_BAD2_ST = 138,
    UNIT_MOT_BAD2_LOOP = 139,
    UNIT_MOT_BAD2_ED = 140,
    UNIT_MOT_RESV_8D = 141,
    UNIT_MOT_RESV_8E = 142,
    UNIT_MOT_RESV_8F = 143,
    UNIT_MOT_SD_HCOMBO_S1 = 144,
    UNIT_MOT_SD_HCOMBO_S2 = 145,
    UNIT_MOT_SD_HCOMBO_S3 = 146,
    UNIT_MOT_SD_HCOMBO_S4 = 147,
    UNIT_MOT_SD_HCOMBO_S5 = 148,
    UNIT_MOT_SD_HCOMBO_L1 = 149,
    UNIT_MOT_SD_HCOMBO_L2 = 150,
    UNIT_MOT_SD_HCOMBO_L3 = 151,
    UNIT_MOT_SD_HCOMBO_L4 = 152,
    UNIT_MOT_SD_HCOMBO_L5 = 153,
    UNIT_MOT_LC_HCOMBO_L1 = 154,
    UNIT_MOT_LC_HCOMBO_L2 = 155,
    UNIT_MOT_LC_HCOMBO_L3 = 156,
    UNIT_MOT_LC_HCOMBO_L4 = 157,
    UNIT_MOT_LC_HCOMBO_L5 = 158,
    UNIT_MOT_LC_HCOMBO_L6 = 159,
    UNIT_MOT_AX_HCOMBO_S1 = 160,
    UNIT_MOT_AX_HCOMBO_S2 = 161,
    UNIT_MOT_AX_HCOMBO_S3 = 162,
    UNIT_MOT_AX_HCOMBO_S4 = 163,
    UNIT_MOT_AX_HCOMBO_L1 = 164,
    UNIT_MOT_AX_HCOMBO_L2 = 165,
    UNIT_MOT_AX_HCOMBO_L3 = 166,
    UNIT_MOT_AX_HCOMBO_L4 = 167,
    UNIT_MOT_R_SD_SHOT = 168,
    UNIT_MOT_R_GUN_SHOT = 169,
    UNIT_MOT_R_MAGIC = 170,
    UNIT_MOT_R_JIGENKIRI = 171,
    UNIT_MOT_R_GROUND_S = 172,
    UNIT_MOT_R_GROUND_L = 173,
    UNIT_MOT_R_GROUND_E = 174,
    UNIT_MOT_R_SDDASH_S = 175,
    UNIT_MOT_R_SDDASH_L = 176,
    UNIT_MOT_R_SDDASH_E = 177,
    UNIT_MOT_R_SDDASH_T = 178,
    UNIT_MOT_R_MAGIC2 = 179,
    UNIT_MOT_R_MAGIC3 = 180,
    UNIT_MOT_R_MAGIC4 = 181,
    UNIT_MOT_R_MAGIC5 = 182,
    UNIT_MOT_R_MAGIC6 = 183,
    UNIT_MOT_R_NULL = 255,
    UNIT_MOT_RESV_B8 = 184,
    UNIT_MOT_RESV_B9 = 185,
    UNIT_MOT_LOOK_R_IN = 186,
    UNIT_MOT_LOOK_R_LOOP = 187,
    UNIT_MOT_LOOK_L_IN = 188,
    UNIT_MOT_LOOK_L_LOOP = 189,
    UNIT_MOT_EISYO = 6,
    UNIT_MOT_KIKAN = 7,
    UNIT_MOT_BRESS = 8,
    UNIT_MOT_ZAN = 10,
    UNIT_MOT_ATTACK = 3,
    UNIT_MOT_MAGIC = 4,
    UNIT_MOT_FADEIN = 9,
    UNIT_MOT_WPOUT = 10,
    UNIT_MOT_WPIN = 11,
    UNIT_MOT_BATTACK = 16,
    UNIT_MOT_YOBIA = 17,
    UNIT_MOT_TBUTU = 17,
    UNIT_MOT_KAITEN = 18,
    UNIT_MOT_SATTACK1 = 18,
    UNIT_MOT_SATTACK2 = 19,
    UNIT_MOT_SATTACK3 = 20,
    UNIT_MOT_SATTACK4 = 21,
    UNIT_MOT_SATTACK5 = 22,
    UNIT_MOT_SATTACK6 = 23,
    UNIT_MOT_SATTACK7 = 24,
    UNIT_MOT_REV1 = 25,
    UNIT_MOT_SATTACK8 = 34,
    UNIT_MOT_SATTACK9 = 36,
    UNIT_MOT_YOMIKS = 36,
    UNIT_MOT_MISHAS = 37,
    UNIT_MOT_SATTACKA = 37,
    UNIT_MOT_SATTACKB = 38,
    UNIT_MOT_GUADEH = 28,
    UNIT_MOT_N_GUARD = 29,
    UNIT_MOT_BOSSHANYO_BA = 12,
    UNIT_MOT_BOSSHANYO_03 = 11,
    UNIT_MOT_BOSSHANYO_0D = 13,
    UNIT_MOT_BOSSHANYO_10 = 16,
    UNIT_MOT_BOSSHANYO_11 = 17,
    UNIT_MOT_BOSSHANYO_12 = 18,
    UNIT_MOT_BOSSHANYO_13 = 19,
    UNIT_MOT_BOSSHANYO_14 = 20,
    UNIT_MOT_BOSSHANYO_15 = 21,
    UNIT_MOT_BOSSHANYO_16 = 22,
    UNIT_MOT_BOSSHANYO_17 = 23,
    UNIT_MOT_BOSSHANYO_18 = 24,
    UNIT_MOT_BOSSHANYO_19 = 25,
    UNIT_MOT_BOSSHANYO_1A = 26,
    UNIT_MOT_BOSSHANYO_1B = 27,
    UNIT_MOT_BOSSHANYO_1C = 28,
    UNIT_MOT_BOSSHANYO_1D = 29,
    UNIT_MOT_BOSSHANYO_1E = 30,
    UNIT_MOT_BOSSHANYO_1F = 31,
    UNIT_MOT_BOSSHANYO_20 = 32,
    UNIT_MOT_BOSSHANYO_21 = 33,
    UNIT_MOT_BOSSHANYO_22 = 34,
    UNIT_MOT_BOSSHANYO_23 = 35,
    UNIT_MOT_BOSSHANYO_24 = 36,
} UNIT_MOT;

typedef enum {
    MUNAKA_STEP_START = 0,
    MUNAKA_STEP_WARP_WAIT = 250,
    MUNAKA_STEP_BONDAGE_START = 500,
    MUNAKA_STEP_BONDAGE_START_WAIT = 1000,
    MUNAKA_STEP_ACT_BRANCH = 1100,
    MUNAKA_STEP_BONDAGE_END = 2000,
    MUNAKA_STEP_DAMASHI_START = 3000,
    MUNAKA_STEP_ROTATION_CUT = 3100,
    MUNAKA_STEP_ENERGY_SAVE = 3200,
    MUNAKA_STEP_EXPLOSION = 3300,
    MUNAKA_STEP_RESTART = 4000,
} MUNAKA_STEP;

typedef struct SBTLUNIT_WORK SBTLUNIT_WORK;
typedef struct S_CameraMoveDt S_CameraMoveDt;
typedef struct S_PosMove S_PosMove;
typedef struct S_TIMESTOPSKL S_TIMESTOPSKL;

struct S_TIMESTOPSKL {
    SKLID sklID;
    UNIT_MOT tameMot;
    SKLID tameEff;
    s32 cam;
    s32 wait;
    s32 ptn;
    s32 wait2;
};

bool pauseSe;
static s32 *bs_se_stock;
static sdfVector4_t taxi_pos;
static sdfVector4_t taxi_mov;
static sdfVector3_t taxi_rot;
SBTLUNIT_WORK *bs_akama2_wk;
static f32 BS_AKAMA2_ypos;
static s32 BS_ITIMOK_SkillType;
static s32 BS_ITIMOK_SkillCntNow;
static s32 BS_ITIMOK_SkillCntMax;
static s32 BS_ITIMOK_SkillSpd;
static s32 BS_ITIMOK_SkillDbg;
static s32 *BS_ITIMOK_SkillOld;
static s32 gTimeOutCnt;
static S_PosMove *g_aTgtMoveDsmn0;
static S_PosMove *g_aCamMoveDsmn0;
static S_PosMove *g_aTgtMoveDsmn1;
static S_PosMove *g_aCamMoveDsmn1;
static S_PosMove *g_aTgtMoveDsmn2;
static S_PosMove *g_aCamMoveDsmn2;
static S_PosMove *g_aTgtMoveDsmn3;
static S_PosMove *g_aCamMoveDsmn3;
static S_CameraMoveDt *g_CamMovDsmn0;
static S_CameraMoveDt *g_CamMovDsmn1;
static S_CameraMoveDt *g_CamMovDsmn2;
static S_CameraMoveDt *g_CamMovDsmn3;
static f32 gDofNml;
static s32 gGurd_TimeOutCnt;
static s32 gBstp_TomiOutCnt;
static s32 **BS_LASTB1_Action_Tbl;
static s32 laser_cnt;
static s32 laser_wait;
static s32 laser_se_wait;
static f32 bomb_cylinder;
static f32 yuka_cylinder;
static bool DamashiFlag;
static bool KaitenDameFlag;
static bool ExplosionDameFlag;
static bool EventFlag;
static f32 MUNAKA_KAITEN_DISTANCE;
static bool END_PREVIOUS_SKILL;
static f32 eff_timer;
static s32 gTimeoutCnt;
static S_TIMESTOPSKL *g_aTimeStopSkl;
static S_PosMove *g_aCamMoveSkl0;
static S_PosMove *g_aTgtMoveSkl0;
static S_PosMove *g_aCamMoveSkl1;
static S_PosMove *g_aTgtMoveSkl1;
static S_PosMove *g_aCamMoveHoukou;
static S_PosMove *g_aTgtMoveHoukou;
static S_PosMove *g_aCamMoveMaou;
static S_PosMove *g_aCamMoveMaou1;
static S_PosMove *g_aTgtMoveMaou;
static S_PosMove *g_aCamMoveTensi;
static S_PosMove *g_aCamMoveTensi1;
static S_PosMove *g_aTgtMoveTensi;
static S_PosMove *g_aCamMoveTenbatu;
static S_PosMove *g_aTgtMoveTenbatu;
static S_PosMove *g_aCamMoveExo;
static S_PosMove *g_aTgtMoveExo;
static S_PosMove *g_aCamMoveMagS0;
static S_PosMove *g_aTgtMoveMagS0;
static S_PosMove *g_aCamMoveNirami;
static S_PosMove *g_aTgtMoveNirami;
static S_PosMove *g_aCamMoveAll;
static S_PosMove *g_aTgtMoveAll;
static S_CameraMoveDt *g_CamMovAll;
static S_CameraMoveDt *g_CamMovMagS0;
static S_CameraMoveDt *g_CamMovSkl0;
static S_CameraMoveDt *g_CamMovSkl1;
static S_CameraMoveDt *g_CamMovHoukou;
static S_CameraMoveDt *g_CamMovMaou;
static S_CameraMoveDt *g_CamMovTensi;
static S_CameraMoveDt *g_CamMovMaou1;
static S_CameraMoveDt *g_CamMovTensi1;
static S_CameraMoveDt *g_CamMovTenbatu;
static S_CameraMoveDt *g_CamMovExo;
static S_CameraMoveDt *g_CamMovNirami;
static S_CameraMoveDt *g_apCamMovSkl;
static S_PosMove *g_aTgtMove_LASTDEAD_L1_0;
static S_PosMove *g_aCamMove_LASTDEAD_L1_0;
static S_CameraMoveDt *g_CamMov_LASTDEAD_L1_0;
static S_PosMove *g_aTgtMove_LASTDEAD_R1_0;
static S_PosMove *g_aCamMove_LASTDEAD_R1_0;
static S_CameraMoveDt *g_CamMov_LASTDEAD_R1_0;
static S_PosMove *g_aTgtMove_LASTDEAD_0;
static S_PosMove *g_aCamMove_LASTDEAD_0;
static S_CameraMoveDt *g_CamMov_LASTDEAD_0;
static s32 gAmatobiMoveCnt;
static s32 sinacnt;
static s32 gEisyoNasiWaitTime;
static s32 gAttackwaitNasiWaitTime;

static void WarpPosSet(SBTLUNIT_WORK *wk);
static void TaxiMoveInit(SBTLUNIT_WORK *wk);
static void TaxiMove(SBTLUNIT_WORK *wk);
static void TaxiMoveEnd(SBTLUNIT_WORK *wk);
static bool BS_AKAMA2_HitSub(SBTLUNIT_WORK *wk, SBTLUNIT_WORK *pu, SKLID skillid, const sdfVector4_t *beffPos);
static void BS_AKAMA2_Dmg(SBTLUNIT_WORK *wk, SBTLUNIT_WORK *pu, SKLID skillid);
static void BS_ITIMOK_Motion(SBTLUNIT_WORK *wk, s32 type);
static f32 DirSet(SBTLUNIT_WORK *wk, const sdfVector4_t *pos, bool wk_rot_set);
static void DirSetHokanInit(SBTLUNIT_WORK *wk);
static f32 DirSetHokan(SBTLUNIT_WORK *wk, const sdfVector4_t *pos, f32 spd);
static void MoveSet(SBTLUNIT_WORK *wk, f32 spd);
static void BS_ITIMOK_LoopMove(SBTLUNIT_WORK *wk, SBTLUNIT_WORK *pu, bool motion_set);
static SKLID RandomSet_NBS_ICI(void);
static void BS_ITIMOK_Hit(SBTLUNIT_WORK *wk);
static bool BS_ITIMOK_HitSub(SBTLUNIT_WORK *wk, SBTLUNIT_WORK *pu);
static void BS_ITIMOK_Dmg(SBTLUNIT_WORK *wk, SBTLUNIT_WORK *pu);
static f32 BS_LASTB1_PuDis(SBTLUNIT_WORK *pu, SBTLUNIT_WORK *wk);
static f32 BS_LASTB1_PuDis2(SBTLUNIT_WORK *pu, SBTLUNIT_WORK *wk);
static void BS_MATORY_Explosion_Hit(SBTLUNIT_WORK *wk, SBTLUNIT_WORK *user, SKLID skillid, const sdfVector4_t *beffPos);
static bool BS_MATORY_Explosion_HitSub(SBTLUNIT_WORK *user, const sdfVector4_t *beffPos);
static bool BS_MISHAK_HitSub(SBTLUNIT_WORK *wk, SBTLUNIT_WORK *pu, SKLID skillid, const sdfVector4_t *beffPos);
static bool BS_MISHAK_HitKaihi(SBTLUNIT_WORK *wk, SBTLUNIT_WORK *pu);
static void BS_MISHAK_Dmg(SBTLUNIT_WORK *wk, SBTLUNIT_WORK *pu, SKLID skillid);
static void BS_MUNAKA_Kaiten_Hit(SBTLUNIT_WORK *wk, bool _hutto);
static bool BS_MUNAKA_Kaiten_HitSub(SBTLUNIT_WORK *wk, SBTLUNIT_WORK *pu);
static void BS_MUNAKA_Explosion_Hit(SBTLUNIT_WORK *wk, bool _hutto);
static bool BS_MUNAKA_Explosion_HitSub(SBTLUNIT_WORK *wk, SBTLUNIT_WORK *pu);
static void BS_MUNAKA_Dmg(SBTLUNIT_WORK *wk, SBTLUNIT_WORK *pu, bool _hutto);
static void MatyStopOff(void);
static s32 GetTimeStopID(SKLID sklID);
static void SetAction_ProgramSkill(SBTLUNIT_WORK *wk, SKLID skillID);
static void ResetAction(SBTLUNIT_WORK *wk);
static void SetAtkDirHD(SBTLUNIT_WORK *wk, SBTLUNIT_WORK *pTgt, f32 kakudo, f32 raito);
static void WeakAfterScrflag(SBTLUNIT_WORK *wk);
static void SklCameraEnd(SBTLUNIT_WORK *wk);
static void FrcSklEnd(SBTLUNIT_WORK *wk);
static void ChkSklCamEnd(SBTLUNIT_WORK *wk);
static void CheckSkillMessage(SBTLUNIT_WORK *wk, SKLID sklid);
static void StartSklProc(s32 unitID, s32 timeStopID);
static void RunBlur(void);
static bool EisyoEndCheck(SBTLUNIT_WORK *wk);
static bool AttackwaitEndCheck(SBTLUNIT_WORK *wk);
static s32 RaidoAttackCheck(void);
SBTLUNIT_WORK *Support_GetUserData(void);
SBTLUNIT_WORK *GetData(void);

// macros
// 0x1ea4320: void BS_AKAMA2_SE(SBTLUNIT_WORK *wk, s32 seno)
#define BS_AKAMA2_SE(wk, seno) do { \
    s32 encountno; \
    f32 x; \
    f32 y; \
    f32 z; \
    f32 w; \
    s32 v14; \
    sdfVector4_t v15; \
    encountno = wk->encountno; \
    x = wk->pos.x; \
    y = wk->pos.y; \
    z = wk->pos.z; \
    w = wk->pos.w; \
    v15.x = x; \
    if (encountno == 30) \
    v14 = 85000192; \
    else \
    v14 = 86704128; \
    v15.y = y; \
    v15.z = z; \
    v15.w = w; \
    sBtlBsSoundPlayPos(v15, v14 + seno); \
} while (0)

// 0x1ea5710: void BS_AKAMA2_SE_POS(const sdfVector4_t *pos, s32 seno)
#define BS_AKAMA2_SE_POS(pos, seno) do { \
    f32 w; \
    f32 z; \
    f32 y; \
    f32 x; \
    s32 encountno; \
    s32 v12; \
    sdfVector4_t v13; \
    w = pos->w; \
    z = pos->z; \
    y = pos->y; \
    x = pos->x; \
    encountno = wk->encountno; \
    v13.z = z; \
    if (encountno == 30) \
    v12 = 85000192; \
    else \
    v12 = 86704128; \
    v13.w = w; \
    v13.x = x; \
    v13.y = y; \
    sBtlBsSoundPlayPos(v13, v12 + seno); \
} while (0)

// 0x1ea7560: s32 AI_BS_ITIMOK_NBS(void)
static inline s32 AI_BS_ITIMOK_NBS(void) {
  s32 IntPara;
  s32 v4;
  SBTLUNIT_WORK *Data;
  s32 v9;

  IntPara = scrGetIntPara(0);
  BS_ITIMOK_SkillType = IntPara;
  BS_ITIMOK_SkillCntNow = 0;
  BS_ITIMOK_SkillCntMax = scrGetIntPara(1);
  BS_ITIMOK_SkillSpd = scrGetIntPara(2);
  v4 = scrGetIntPara(3);
  BS_ITIMOK_SkillDbg = v4;
  *(u64 *)BS_ITIMOK_SkillOld = 0;
  Data = GetData();
  if (!BS_ITIMOK_SkillType)
  {
    v9 = 1536;
    goto LABEL_22;
  }
  if (BS_ITIMOK_SkillType == 1)
  {
    v9 = 1537;
    goto LABEL_22;
  }
  if (BS_ITIMOK_SkillType != 2)
  {
    v9 = 0;
    goto LABEL_22;
  }
  if (GetPercentage() <= 0x31u)
    v9 = 1536;
  else
    v9 = 1537;
LABEL_22:
  sBtlSetSkillTarget(Data, v9, 0x20000u);
  return 1;
}

// 0x1ea6b10: void BS_ITIMOK_SE(SBTLUNIT_WORK *wk, s32 seno)
#define BS_ITIMOK_SE(wk, seno) do { \
    s32 encountno; \
    f32 x; \
    f32 y; \
    f32 z; \
    f32 w; \
    s32 v14; \
    sdfVector4_t v15; \
    encountno = wk->encountno; \
    x = wk->pos.x; \
    y = wk->pos.y; \
    z = wk->pos.z; \
    w = wk->pos.w; \
    v15.x = x; \
    if (encountno == 48) \
    v14 = 86114304; \
    else \
    v14 = 86573056; \
    v15.y = y; \
    v15.z = z; \
    v15.w = w; \
    sBtlBsSoundPlayPos(v15, v14 + seno); \
} while (0)

// 0x1eabde0: void BS_MATORY_SE(SBTLUNIT_WORK *wk, s32 seno)
#define BS_MATORY_SE(wk, seno) do { \
    s32 encountno; \
    f32 x; \
    f32 y; \
    f32 z; \
    f32 w; \
    s32 v14; \
    sdfVector4_t v15; \
    encountno = wk->encountno; \
    x = wk->pos.x; \
    y = wk->pos.y; \
    z = wk->pos.z; \
    w = wk->pos.w; \
    v15.x = x; \
    if (encountno == 43) \
    v14 = 84344832; \
    else \
    v14 = 86900736; \
    v15.y = y; \
    v15.z = z; \
    v15.w = w; \
    sBtlBsSoundPlayPos(v15, v14 + seno); \
} while (0)

// 0x1eac7b0: void BS_MATORY_DELETE(void)
static inline void BS_MATORY_DELETE(void) {
  s32 encountno;
  s64 i;
  SBATTLE_WORK *wk_local;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  sdatUnitWork_t *para;
  void *Instance;
  void *v10;
  SBTLUNIT_WORK *pLoadingUnit;
  sdatUnitWork_t *v12;
  void *v13;
  void *v14;

  encountno = wk->encountno;
  if (encountno != 54)
  {
    if (encountno != 43)
      return;
  }
  for (i = 0; ; ++i)
  {
    wk_local = wk;
    UnitMng = wk_local->UnitMng;
    if (i >= UnitMng->number)
      break;
    pUnit = UnitMng->pUnitL[i]->pUnit;
    if (!pUnit)
      continue;
    if ((pUnit->side & 2) != 0)
    {
      para = pUnit->para;
      if (para)
      {
        if (para->devilid == 323)
        {
          Instance = get_Instance(0);
          if (op_Inequality(Instance, 0, 0))
          {
            v10 = get_Instance(0);
            Stop(v10, 0, 0);
          }
          pUnit->mode = 9;
          continue;
        }
      }
    }
  }
  wk_local = wk;
  pLoadingUnit = wk_local->pLoadingUnit;
  if (pLoadingUnit)
  {
    wk_local = wk;
    pLoadingUnit = wk_local->pLoadingUnit;
    v12 = pLoadingUnit->para;
    if (v12 && v12->devilid == 323)
    {
      wk_local = wk;
      wk_local->pLoadingUnit = 0;
    }
  }
  v13 = get_Instance(0);
  if (op_Inequality(v13, 0, 0))
  {
    v14 = get_Instance(0);
    LeffEndAll(v14, 0);
  }
}

// 0x1ead1c0: void BS_MISHAK_SE(SBTLUNIT_WORK *wk, s32 seno)
#define BS_MISHAK_SE(wk, seno) do { \
    s32 encountno; \
    f32 x; \
    f32 y; \
    f32 z; \
    f32 w; \
    s32 v14; \
    sdfVector4_t v15; \
    encountno = wk->encountno; \
    x = wk->pos.x; \
    y = wk->pos.y; \
    z = wk->pos.z; \
    w = wk->pos.w; \
    v15.x = x; \
    if (encountno == 41) \
    v14 = 84606976; \
    else \
    v14 = 87425024; \
    v15.y = y; \
    v15.z = z; \
    v15.w = w; \
    sBtlBsSoundPlayPos(v15, v14 + seno); \
} while (0)

// 0x1eaee10: void BS_MUNAKA_SE(SBTLUNIT_WORK *wk, s32 seno)
#define BS_MUNAKA_SE(wk, seno) do { \
    f32 x; \
    f32 y; \
    f32 z; \
    f32 w; \
    sdfVector4_t v11; \
    x = wk->pos.x; \
    y = wk->pos.y; \
    z = wk->pos.z; \
    w = wk->pos.w; \
    v11.x = x; \
    v11.y = y; \
    v11.z = z; \
    v11.w = w; \
    sBtlBsSoundPlayPos(v11, seno + 86179840); \
} while (0)

// 0x1eac430: void BS_RASUPU_SE(SBTLUNIT_WORK *wk, s32 seno)
#define BS_RASUPU_SE(wk, seno) do { \
    s32 encountno; \
    f32 x; \
    f32 y; \
    f32 z; \
    f32 w; \
    s32 v14; \
    sdfVector4_t v15; \
    encountno = wk->encountno; \
    x = wk->pos.x; \
    y = wk->pos.y; \
    z = wk->pos.z; \
    w = wk->pos.w; \
    v15.x = x; \
    if (encountno == 43) \
    v14 = 84279296; \
    else \
    v14 = 86769664; \
    v15.y = y; \
    v15.z = z; \
    v15.w = w; \
    sBtlBsSoundPlayPos(v15, v14 + seno); \
} while (0)

// 0x1ea2680
bool sBtlProcParticle(void *particle, void *gobj, bool wnonclr, bool *nostop_eff) {
  _BOOL4 v6;
  s64 v9;
  void *v10;
  void *v11;
  bool v12;
  void *v13;
  _BOOL4 v15;
  void *v16;
  void *v17;
  _BOOL4 v18;
  s64 v19;
  char v21;
  s32 *bs_se_stock_local;
  void *v23;
  bool IsSceanStop;
  void *v27;
  void *Instance;
  s64 v33;
  void *v34;
  void *v36;
  void *gameObject;
  bool v38;
  void *v40;
  void *v41;
  void *v42;
  void *v43;
  void *v45;
  void *v46;
  bool *m_Items;
  s32 v48;

  v6 = wnonclr;
  if (SLODWORD(particle->max_length) >= 1)
  {
    if (gobj)
    {
      v9 = 0;
      if (nostop_eff)
      {
        v48 = 0;
        m_Items = nostop_eff;
        v10 = gobj;
        v11 = particle;
        while (1)
        {
          v13 = v11[v9];
          if (op_Inequality(v11[v9], 0, 0))
            goto LABEL_13;
          goto LABEL_9000;
          if (op_Inequality(v13, 0, 0))
          {
LABEL_13:
            v15 = v6;
            v16 = v10[v9];
            v17 = v11[v9];
            v18 = m_Items[v9];
            v12 = v18;
            v6 = v15;
            v48 |= sBtlProcParticleSub(v17, v16, v15, v12);
          }
LABEL_9000:
          if (++v9 >= SLODWORD(particle->max_length))
            goto LABEL_16;
        }
      }
      v48 = 0;
      v41 = particle;
      v42 = gobj;
      while (1)
      {
        v43 = v41[v9];
        if (op_Inequality(v41[v9], 0, 0))
          goto LABEL_83;
        goto LABEL_9001;
        if (op_Inequality(v43, 0, 0))
        {
LABEL_83:
          v45 = v42[v9];
          v46 = v41[v9];
          v48 |= sBtlProcParticleSub(v46, v45, v6, 0);
        }
LABEL_9001:
        if (++v9 >= SLODWORD(particle->max_length))
          goto LABEL_16;
      }
    }
    v48 = 0;
    v33 = 0;
    v34 = particle;
    while (1)
    {
      v36 = v34[v33];
      if (!op_Inequality(v34[v33], 0, 0))
        goto LABEL_66;
      gameObject = get_gameObject(v34[v33], 0);
      if (nostop_eff)
      {
        v38 = nostop_eff[v33];
        v40 = v34[v33];
        goto LABEL_65;
      }
      else
      {
        v38 = 0;
        v40 = v34[v33];
        goto LABEL_65;
      }
LABEL_65:
      v48 |= sBtlProcParticleSub(v40, gameObject, v6, v38);
LABEL_66:
      if (++v33 >= SLODWORD(particle->max_length))
        goto LABEL_16;
    }
  }
  LOBYTE(v48) = 0;
LABEL_16:
  v19 = 8;
  while (1)
  {
    bs_se_stock_local = bs_se_stock;
    if (v19 - 8 >= SLODWORD(bs_se_stock_local->max_length))
      return v48 & 1;
    if (*((u32 *)&bs_se_stock_local->obj.klass + v19) != -1)
      goto LABEL_28;
    goto LABEL_9002;
    if (*((u32 *)&bs_se_stock->obj.klass + v19) != -1)
    {
LABEL_28:
      if (wk->cmbSkl->bRun)
        goto LABEL_34;
      if (sBtlCheckSetsuma())
        goto LABEL_34;
      IsSceanStop = IsSceanStop();
      if (IsSceanStop)
        goto LABEL_46;
      if (pauseSe)
      {
        Instance = get_Instance(0);
        PausePlayerAll(Instance, 0, *((u32 *)&bs_se_stock->obj.klass + v19), 0);
      }
      v21 = 0;
      goto LABEL_19;
LABEL_42:
      v21 = 0;
LABEL_19:
      pauseSe = v21;
      goto LABEL_20;
LABEL_46:
      if (!pauseSe)
      {
LABEL_48:
        v27 = get_Instance(0);
        PausePlayerAll(v27, 1, *((u32 *)&bs_se_stock->obj.klass + v19), 0);
LABEL_18:
        v21 = 1;
        goto LABEL_19;
      }
LABEL_37:
      goto LABEL_18;
LABEL_36:
      if (!pauseSe)
        goto LABEL_48;
      goto LABEL_37;
LABEL_34:
      if (!v6)
      {
        v23 = get_Instance(0);
        StopPlayerAll(v23, *((u32 *)&bs_se_stock->obj.klass + v19), 0);
        goto LABEL_42;
      }
      goto LABEL_36;
    }
LABEL_9002:
LABEL_20:
    ++v19;
  }
}

// 0x1ea2c30
bool sBtlProcParticleSub(void *particle, void *gobj, bool wnonclr, bool nostop) {
  if (op_Equality(particle, 0, 0))
    return 0;
  if (!op_Equality(gobj, 0, 0))
  {
    if (!get_activeSelf(gobj, 0))
      return 0;
    goto LABEL_13;
  }
  gobj = get_gameObject(particle, 0);
  if (!get_activeSelf(gobj, 0))
    return 0;
LABEL_13:
  if (!wk->cmbSkl->bRun)
  {
    if (sBtlCheckSetsuma())
      goto LABEL_19;
    if (!IsSceanStop())
    {
      if (get_isPaused(particle, 0))
        Play(particle, 1, 0);
      return 0;
    }
    if (!nostop)
      goto LABEL_20;
    return 0;
  }
LABEL_19:
  if (wnonclr)
  {
LABEL_20:
    if (!get_isPaused(particle, 0))
      Pause(particle, 1, 0);
    return 0;
  }
  if (get_activeSelf(gobj, 0))
  {
    Stop_61441216(particle, 1, 0);
    SetActive(gobj, 0, 0);
    return 1;
  }
  return 0;
}

// 0x1ea2eb0
void sBtlBsSoundInit(void) {
  s64 i;
  char *v3;

  for (i = 0; ; ++i)
  {
    if (i >= SLODWORD(bs_se_stock->max_length))
      break;
    v3 = (char *)bs_se_stock + 4 * i;
    *((u32 *)v3 + 8) = -1;
  }
}

// 0x1ea2f60
void sBtlBsSoundPlayPos(const sdfVector4_t *pos, u32 smgno) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  u32 DevilEnglish;
  s64 i;
  s32 *bs_se_stock_local;
  s32 v12;
  sdfVector4_t v14;

  w = pos->w;
  z = pos->z;
  y = pos->y;
  x = pos->x;
  DevilEnglish = sndGetDevilEnglish(smgno);
  v14.x = x;
  v14.y = y;
  v14.z = z;
  v14.w = w;
  sBtlPlay3DSE(DevilEnglish, v14);
  for (i = 8; ; ++i)
  {
    bs_se_stock_local = bs_se_stock;
    if (i - 8 >= SLODWORD(bs_se_stock_local->max_length))
      break;
    bs_se_stock_local = bs_se_stock;
    v12 = *((u32 *)&bs_se_stock_local->obj.klass + i);
    if (v12 == -1)
    {
      *((u32 *)&bs_se_stock->obj.klass + i) = DevilEnglish;
      return;
    }
    if (*((u32 *)&bs_se_stock->obj.klass + i) == -1)
      continue;
    if (*((u32 *)&bs_se_stock->obj.klass + i) == DevilEnglish)
      return;
  }
}

// 0x1ea3100
void sBtlBsSoundPlay(SBTLUNIT_WORK *wk, u32 smgno) {
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  sdfVector4_t v9;

  x = wk->pos.x;
  y = wk->pos.y;
  z = wk->pos.z;
  w = wk->pos.w;
  v9.x = x;
  v9.y = y;
  v9.z = z;
  v9.w = w;
  sBtlBsSoundPlayPos(v9, smgno);
}

// 0x1ea3190
void sBtlEnemyPush(SBTLUNIT_WORK *wk, bool is_setuma) {
  SBTLUNIT_WORK *PChara;
  SBTLACTION_WORK *actwk;
  s32 devilid;
  SBATTLE_WORK *v9;
  SBTLEFF_LISTWORK *effList;
  SBTLUNIT_WORK *v12;
  SBTLACTAI_WORK *actaiwk;
  s32 vstatus;
  s32 v16;
  s32 v17;

  if (wk && (wk->side & 2) != 0)
  {
    PChara = sBtlGetPChara();
    actwk = wk->actwk;
    switch (actwk->status)
    {
      case '\'':
        devilid = (u16)wk->para->devilid;
        if (devilid != 269 && devilid != 304)
        {
          actwk = wk->actwk;
          actwk->status = 0;
          v9 = wk;
          effList = v9->effList;
          v12 = v9->scrUnitList[2];
          v12->actwk->status = 0;
          sBtlDeleteEffectData_SkillIDType(effList, 441, 1u);
          sBtlEndAction(wk);
          wk->aiwk->scrStep = 7;
          wk->status &= 0xFBFFBFFE;
          v12->status &= 0xFBFFBFFE;
        }
        break;
      case '>':
        wk->flg &= ~2u;
        sBtlStatusBitOff(wk, 0xFFFFFF7F);
        goto LABEL_22;
      case '?':
        actaiwk = PChara->actaiwk;
        if (actaiwk->targetID == -1)
          actaiwk->targetID = wk->ListID;
        sBtlSetFade(wk, 1, 0, 0, 128);
        sBtlStatusBitOff(wk, 0xFFFFBFFF);
        sBtlStatusBitOff(wk, 0xFFFFFFFE);
        sBtlStatusBitOff(wk, 0xFFFFFF7F);
        vstatus = wk->vstatus;
        wk->pos.y = 0.0;
        wk->nextpos.y = 0.0;
        wk->vstatus = vstatus & 0xFF7FFFFF;
LABEL_22:
        sBtlEndAction(wk);
        ClrAction();
        break;
      case '@':
        v16 = wk->flg & 0xFFFFFFBF;
        wk->status &= 0xFBFFBFFE;
        wk->flg = v16;
        sBtlEndAction(wk);
        break;
      case 'A':
        v17 = wk->vstatus;
        wk->mode = 9;
        wk->vstatus = v17 | 0x1000;
        sBtlEndAction(wk);
        break;
      case 'B':
        sBtlStatusBitOff(wk, 0xFFFFBFFF);
        sBtlStatusBitOff(wk, 0xFFFFFFFE);
        sBtlSetFade(wk, 1, 0, 0, 128);
        sBtlNBS_AisyoSet(wk, 0);
        sBtlEndAction(wk);
        break;
      default:
        return;
    }
  }
}

// 0x1ea35d0
void sBtlEnemyPop(SBTLUNIT_WORK *wk, bool is_setuma) {
  s32 encountno;
  s32 devilid;

  if (wk && (wk->side & 2) != 0)
  {
    encountno = wk->encountno;
    if (encountno != 48)
    {
      encountno = wk->encountno;
      if (encountno != 52)
        return;
    }
    devilid = (u16)wk->para->devilid;
    if (devilid == 166 || devilid == 297 || devilid == 290)
    {
      sBtlStatusBitOff(wk, 0xFFFFBFFF);
      sBtlStatusBitOff(wk, 0xFFFFFF7F);
    }
  }
}

// 0x1ea34e0
void sBtlNBS_AisyoSet(SBTLUNIT_WORK *wk, bool _mukou) {
  sdatUnitWork_t *para;
  __int128 v6;
  s32 *v7;
  s32 devilid;
  s32 aishou;
  SBTLAISYO_DATAWORK *Aisyotbl;

  para = wk->para;
  if (mukou)
  {
    *(u64 *)&v6 = 0x100000001000LL;
    *((u64 *)&v6 + 1) = 0x100000001000LL;
    v7 = para->aisyo->para;
    *(_OWORD *)v7 = v6;
    *(_OWORD *)&v7[4] = v6;
    *(_OWORD *)&v7[8] = v6;
    *(_OWORD *)&v7[12] = v6;
    return;
  }
  devilid = para->devilid;
  aishou = sBtlGetDevilData(devilid, -1)->aishou;
  Aisyotbl = sBtlGetAisyotbl(aishou);
  ClassCopy(wk->para->aisyo, Aisyotbl, 0);
}

// 0x1ea36f0
void sBtlBS_AKAMA2_Init_Taxi(SBTLUNIT_WORK *wk) {
  SBTLACTION_WORK *actwk;
  void *Instance;
  s64 i;
  char *v9;

  actwk = wk->actwk;
  actwk->status = 63;
  actwk->exStep = 0;
  actwk->exWait = 0;
  Instance = get_Instance(0);
  TaxiMoveEnd(Instance);
  bs_akama2_wk = wk;
  for (i = 0; ; ++i)
  {
    if (i >= SLODWORD(bs_se_stock->max_length))
      break;
    v9 = (char *)bs_se_stock + 4 * i;
    *((u32 *)v9 + 8) = -1;
  }
}

// 0x1ea3820
bool sBtlBS_AKAMA2_Action_Taxi(SBTLUNIT_WORK *wk, const sdfVector4_t *oldpos) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  SBTLUNIT_WORK *PChara;
  SBTLACTION_WORK *actwk;
  SBTLUNIT_WORK *v13;
  s32 exStep;
  s32 v15;
  bool v16;
  s32 v17;
  s32 exSeWait;
  s32 v19;
  SBTLACTION_WORK *v21;
  s32 v22;
  void *v24;
  void *v25;
  s32 exWait;
  s32 v27;
  void *Instance;
  SBTLACTION_WORK *v29;
  SBTLACTION_WORK *v33;
  s32 v34;
  SBTLACTION_WORK *v35;
  s32 v36;
  SBTLACTION_WORK *v39;
  f32 v40;
  f32 v41;
  f32 v42;
  f32 v43;
  char v44;
  void *v56;
  void *v57;
  f32 v58;
  f32 v59;
  f32 v60;
  void *v61;
  SBTLACTION_WORK *v63;
  f32 v64;
  f32 v65;
  f32 v66;
  f32 v67;
  s32 v68;
  s32 v69;
  f32 v70;
  f32 v71;
  f32 v72;
  f32 v73;
  f32 v74;
  SBTLACTION_WORK *v75;
  u32 v76;
  dds3ModelHandle_t *hModel;
  SBTLACTION_WORK *v79;
  s32 gNowPlayerIndex;
  void *v82;
  void *v83;
  void *v84;
  SBTLACTION_WORK *v85;
  sdfVector4_t Pos;
  sdfVector4_t v87;
  sdfVector4_t v88;
  sdfVector4_t v89;
  sdfVector4_t v90;
  sdfVector4_t v91;
  sdfVector4_t v92;
  sdfVector4_t v93;
  sdfVector4_t v94;

  w = oldpos->w;
  z = oldpos->z;
  y = oldpos->y;
  x = oldpos->x;
  if (!sBtlHDloadChk(426))
    return 1;
  PChara = sBtlGetPChara();
  actwk = wk->actwk;
  v13 = PChara;
  exStep = actwk->exStep;
  if (exStep <= 200)
  {
    if (exStep <= 50)
    {
      if (exStep)
      {
        if (exStep == 50)
        {
          exWait = actwk->exWait;
          if (exWait)
          {
            v27 = exWait - 1;
            actwk->exWait = v27;
            if (v27 <= 0)
            {
              Instance = get_Instance(0);
              Play(Instance, 4, 0);
            }
          }
          if (sBtlCheckMotionEnd(wk))
          {
            sBtlSetFade(wk, 2, 0, 0, 128);
            wk->status |= 0x4001u;
            v29 = wk->actwk;
            v29->exStep = 100;
            v29->exWait = 60;
            sBtlSetSkill_EffectData(wk, 426, 0);
            BS_AKAMA2_SE(wk, 26);
          }
        }
      }
      else
      {
        sBtlSetMotion(wk, 34, 0, 2, 0);
        wk->status |= 0x4001u;
        v33 = wk->actwk;
        v33->exWait = 96;
        v33->exStep = 50;
        BS_AKAMA2_SE(wk, 28);
      }
      goto LABEL_70;
    }
    switch (exStep)
    {
      case 100:
        v36 = actwk->exWait - 1;
        actwk->exWait = v36;
        if (v36 <= 0)
        {
          SetAction(2);
          WarpPosSet(wk);
          sBtlSetFade(wk, 1, 0, 0, 4);
          sBtlSetMotion(wk, 32, 0, 0, 0);
          sBtlSetSkill_EffectData(wk, 426, 0);
          BS_AKAMA2_SE(wk, 27);
          v39 = wk->actwk;
          v39->exWait = 30;
          v39->exStep = 150;
        }
        v40 = v13->pos.x;
        v41 = v13->pos.y;
        v42 = v13->pos.z;
        v43 = v13->pos.w;
        v87.x = v40;
        v87.y = v41;
        v87.z = v42;
        v87.w = v43;
        wk->mv_rotbk = DirSet(wk, v87, 1);
        if (v36 < 1)
          goto LABEL_101;
        break;
      case 150:
        if ((wk->vstatus & 1) == 0)
        {
          actwk->exWait = 120;
          actwk->exStep = 200;
          *(u64 *)&taxi_rot.x = 0;
          taxi_rot.z = 0.0;
          v56 = get_Instance(0);
          SetRot(v56, 0, taxi_rot, 0);
          v57 = get_Instance(0);
          Play(v57, 0, 0);
          v58 = wk->pos.x;
          v59 = wk->pos.z;
          v60 = BS_AKAMA2_ypos + -330.0;
          v61 = get_Instance(0);
          v90.w = 0.0;
          v90.x = v58;
          v90.y = v60;
          v90.z = v59;
          SetPos(v61, 0, v90, 0);
          wk->actwk->exSeWait = 60;
        }
        goto LABEL_101;
      case 200:
        exSeWait = actwk->exSeWait;
        if (exSeWait)
        {
          v19 = exSeWait - 1;
          actwk->exSeWait = v19;
          if (v19 <= 0)
          {
            BS_AKAMA2_SE(wk, 24);
          }
        }
        wk->vstatus |= 0x800000u;
        v21 = wk->actwk;
        v22 = v21->exWait;
        wk->pos.y = BS_AKAMA2_ypos;
        v21->exWait = --v22;
        if (v22 <= 0)
          v21->exStep = 400;
        goto LABEL_98;
    }
LABEL_70:
    v17 = 0;
    goto LABEL_71;
  }
  if ((u32)exStep > 0x226)
  {
    if (exStep != 600)
    {
      if (exStep == 700)
      {
        v17 = 1;
        actwk->exStep = 10000;
        goto LABEL_71;
      }
      if (exStep == 1000)
      {
        v15 = actwk->exWait - 1;
        v16 = actwk->exWait == 1;
        actwk->exWait = v15;
        if (v15 < 0 || v16)
        {
          v17 = 0;
          actwk->exStep = 0;
          goto LABEL_71;
        }
      }
      goto LABEL_70;
    }
    v34 = actwk->exWait - 1;
    v16 = actwk->exWait == 1;
    actwk->exWait = v34;
    if (v34 < 0 || v16)
    {
      sBtlSetFade(wk, 1, 0, 0, 4);
      sBtlSetMotion(wk, 0, 0, 0, 0);
      sBtlSetSkill_EffectData(wk, 426, 0);
      v35 = wk->actwk;
      v17 = 0;
      v35->exStep = 700;
      v35->exWait = 1200;
LABEL_71:
      v44 = 0;
      wk->vstatus &= ~0x800000u;
      goto LABEL_73;
    }
    goto LABEL_101;
  }
  if (exStep == 400)
  {
    wk->next_motion_not_hokan = 1;
    sBtlSetMotion(wk, 33, 0, 0, 0);
    wk->next_motion_not_hokan = 1;
    sBtlSetMotion(wk, 33, 0, 0, 0);
    v63 = wk->actwk;
    v63->exStep = 500;
    v63->exWait = 40;
LABEL_98:
    v64 = v13->pos.x;
    v65 = v13->pos.y;
    v66 = v13->pos.z;
    v67 = v13->pos.w;
    v91.x = v64;
    v91.y = v65;
    v91.z = v66;
    v91.w = v67;
    wk->mv_rotbk = DirSet(wk, v91, 1);
    goto LABEL_101;
  }
  if (exStep == 500)
  {
    v68 = actwk->exWait;
    if (v68)
    {
      v69 = v68 - 1;
      actwk->exWait = v69;
      if (v69 <= 0)
      {
        TaxiMoveInit(wk);
        v79 = wk->actwk;
        v79->exWait = 0;
        v79->exStep = 550;
      }
      else
      {
        v70 = PChara->pos.x;
        v71 = PChara->pos.y;
        v72 = PChara->pos.z;
        v73 = PChara->pos.w;
        v92.x = v70;
        v92.y = v71;
        v92.z = v72;
        v92.w = v73;
        v74 = DirSet(wk, v92, 1);
        v75 = wk->actwk;
        wk->mv_rotbk = v74;
        v76 = v75->exWait;
        if (v76 <= 0x25 && ((1 << v76) & 0x2220000000LL) != 0)
        {
          if (wk->motionno != 33)
            goto LABEL_113;
          hModel = wk->hModel;
          if (mdlGetMotionFrameF(hModel) <= 0.0)
          {
LABEL_113:
            wk->next_motion_not_hokan = 1;
            sBtlSetMotion(wk, 33, 0, 0, 0);
          }
        }
      }
    }
    goto LABEL_101;
  }
  if (exStep != 550)
    goto LABEL_70;
  if (!actwk->exWait)
  {
    taxi_rot.x = taxi_rot.x + 6.0;
    v24 = get_Instance(0);
    SetRot(v24, 0, taxi_rot, 0);
    v25 = get_Instance(0);
    Pos = GetPos(v25, 0, 0);
    if (Pos.y >= 0.0)
    {
      ClrAction();
      BS_AKAMA2_SE(v13, 25);
      gNowPlayerIndex = get_Instance(0)->gNowPlayerIndex;
      v82 = get_Instance(0);
      TaxiMoveEnd(v82);
      v83 = get_Instance(0);
      v93.y = 0.0;
      v93.x = Pos.x;
      v93.z = Pos.z;
      v93.w = Pos.w;
      PlayBEFF(v83, 0, v93, gNowPlayerIndex, 0);
      v84 = get_Instance(0);
      v94.y = 0.0;
      v94.x = Pos.x;
      v94.z = Pos.z;
      v94.w = Pos.w;
      PlayBEFF(v84, 1, v94, gNowPlayerIndex, 0);
      wk->actwk->exWait = 1;
    }
    else if (!wk->actwk->exWait)
    {
      goto LABEL_101;
    }
  }
  if (sBtlCheckMotionEnd(wk))
  {
    sBtlSetFade(wk, 2, 0, 0, 4);
    wk->status |= 0x4001u;
    sBtlSetSkill_EffectData(wk, 426, 0);
    v85 = wk->actwk;
    v85->exStep = 600;
    v85->exWait = 60;
  }
LABEL_101:
  v17 = 0;
  v44 = 1;
  wk->vstatus |= 0x800000u;
LABEL_73:
  v88.x = 0.0;
  v88.y = 0.0;
  v88.z = 0.0;
  v88.w = 0.0;
  sBtlBS_AKAMA2_Hit(wk, 1539, v88);
  Proc(wk);
  sBtlProc(wk);
  sBtlMVSupport(wk);
  UnitMV(wk);
  v89.x = x;
  v89.y = y;
  v89.z = z;
  v89.w = w;
  CheckMapHit(wk, v89);
  if ((v44 & 1) != 0)
  {
    wk->pos.y = BS_AKAMA2_ypos;
    wk->nextpos.y = BS_AKAMA2_ypos;
    goto LABEL_84;
  }
  else
  {
    wk->pos.y = 0.0;
    wk->nextpos.y = 0.0;
    goto LABEL_84;
  }
LABEL_84:
  UnitMV_To_Basic(wk);
  if (v17)
  {
    wk->status &= 0xFFFFBFFE;
    ResetAction(wk);
    sBtlSetAction(wk, 2, 0);
    sBtlEndAction(wk);
  }
  return 1;
}

// 0x1ea4480
static void WarpPosSet(SBTLUNIT_WORK *wk) {
  f32 v2;
  SBTLUNIT_WORK *UserData;
  s32 v4;
  s32 i;
  f32 v6;
  s64 v7;
  f32 z;
  struct sdfVector4_t v11;
  f32 *p_x;
  f32 x;
  f32 y;
  f32 v15;
  struct sdfVector4_t v21;
  sdfVector4_t rot;
  sdfVector4_t pos;
  SBTLUNIT_WORK *v24;

  v24 = wk;
  *(u64 *)&pos.x = 0;
  *(u64 *)&pos.z = 0;
  *(u64 *)&rot.x = 0;
  *(u64 *)&rot.z = 0;
  v2 = -1.0;
  UserData = Support_GetUserData();
  v4 = 3;
  for (i = 2; i != 6; ++i)
  {
    sBtlGetPointData(i, &pos, &rot);
    pos.w = 0.0;
    v7 = *(u64 *)&pos.x;
    z = pos.z;
    *(u64 *)&vct_A.x = v7;
    vct_A.z = z;
    vct_A.w = 0.0;
    v11 = UserData->pos;
    vct_B = v11;
    vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    p_x = &vf00.x;
    x = p_x[4];
    y = p_x[5];
    v15 = p_x[6];
    v6 = sqrtf((f32)((f32)(x * x) + (f32)(y * y)) + (f32)(v15 * v15));
    if (v6 >= (f32)(v6 + 10.0))
      v6 = v6 + 10.0;
    if (v6 >= v2)
    {
      v2 = v6;
      v4 = i;
    }
  }
  sBtlGetPointData(v4, &pos, &rot);
  v21 = pos;
  goto LABEL_38;
LABEL_39:
  vct_A = v21;
  goto LABEL_40;
LABEL_38:
  goto LABEL_39;
LABEL_40:
  v24->pos = vct_A;
}

// 0x1ea4b30
static void TaxiMoveInit(SBTLUNIT_WORK *wk) {
  SBTLUNIT_WORK *UserData;
  f32 x;
  f32 v6;
  f32 *p_pauseSe;
  f32 z;
  f32 v9;
  f32 v10;
  f32 v11;
  f32 v12;
  void *Instance;
  sdfVector3_t v14;
  sdfVector3_t v15;

  UserData = Support_GetUserData();
  x = wk->pos.x;
  v6 = wk->pos.y + -330.0;
  p_pauseSe = &pauseSe;
  z = wk->pos.z;
  p_pauseSe[6] = z;
  v9 = UserData->pos.z;
  p_pauseSe[4] = x;
  p_pauseSe[5] = v6;
  v10 = x + (f32)((f32)(UserData->pos.x - x) * 0.9);
  v11 = v6 + (f32)((f32)(UserData->pos.y - v6) * 0.9);
  v12 = z + (f32)((f32)(v9 - z) * 0.9);
  Instance = get_Instance(0);
  v14.x = x;
  v14.y = v6;
  v14.z = z;
  v15.x = v10;
  v15.y = v11;
  v15.z = v12;
  TaxiMoveSet(Instance, v14, v15, 0.0, 0);
}

// 0x1ea53c0
static void TaxiMove(SBTLUNIT_WORK *wk) {
  ;
}

// 0x1ea3800
static void TaxiMoveEnd(SBTLUNIT_WORK *wk) {
  void *Instance;

  Instance = get_Instance(0);
  TaxiMoveEnd(Instance);
}

// 0x1ea4c40
void sBtlBS_AKAMA2_Hit(SBTLUNIT_WORK *wk, SKLID skillid, const sdfVector4_t *beffPos) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  SBATTLE_WORK *v11;
  SBTLUNIT_WORK *PChara;
  SBTLUNIT_WORK *v19;
  sdatUnitWork_t *para;
  SBTLUNIT_WORK *Nakama;
  SBTLUNIT_WORK *v26;
  sdfVector4_t v29;
  sdfVector4_t v30;
  sdfVector4_t v31;

  w = beffPos->w;
  z = beffPos->z;
  y = beffPos->y;
  x = beffPos->x;
  v11 = wk;
  if (!v11)
    return;
  if (v11->cmbSkl->bRun)
    return;
  if (sBtlCheckSetsuma())
    return;
  if (!wk->enemy_zenmetu)
  {
    if (!IsSceanStop())
    {
      if (wk->mode != 5)
      {
        sBtlGetPChara();
        PChara = sBtlGetPChara();
        v29.x = x;
        v29.y = y;
        v29.z = z;
        v29.w = w;
        if (BS_AKAMA2_HitSub(sBtlAction, PChara, skillid, v29))
        {
          BS_AKAMA2_Dmg(wk, PChara, skillid);
LABEL_28:
          if (wk->NakamaShugouOn)
            return;
LABEL_34:
          v19 = sBtlGetPChara();
          if (v19)
          {
            para = v19->para;
            if (para)
            {
              if (para->now->hp >= 1)
              {
                Nakama = sBtlGetNakama(0);
                v30.x = x;
                v30.y = y;
                v30.z = z;
                v30.w = w;
                if (BS_AKAMA2_HitSub(sBtlAction, Nakama, skillid, v30))
                {
                  BS_AKAMA2_Dmg(wk, Nakama, skillid);
                }
                v26 = sBtlGetNakama(1);
                v31.x = x;
                v31.y = y;
                v31.z = z;
                v31.w = w;
                if (BS_AKAMA2_HitSub(sBtlAction, v26, skillid, v31))
                {
                  BS_AKAMA2_Dmg(wk, v26, skillid);
                }
              }
            }
          }
          return;
        }
        else
        {
          goto LABEL_28;
        }
        if (wk->NakamaShugouOn)
          return;
        goto LABEL_34;
      }
    }
  }
}

// 0x1ea53d0
static bool BS_AKAMA2_HitSub(SBTLUNIT_WORK *wk, SBTLUNIT_WORK *pu, SKLID skillid, const sdfVector4_t *beffPos) {
  f32 z;
  f32 x;
  sdatUnitWork_t *para;
  bool result;
  void *Instance;
  u16 major;
  s32 minor;
  VISUALDATA_WORK *VisualData;
  f32 v15;
  void *v16;
  bool IsActive;
  void *v18;
  void *v19;
  f32 v20;
  sdfVector4_t Pos;

  z = beffPos->z;
  x = beffPos->x;
  if (!pu)
    return 0;
  para = pu->para;
  if (!para || pu->damagecnt > 0 || pu->yuka_damagecnt > 0 || para->now->hp < 1)
    return 0;
  Instance = get_Instance(0);
  if (op_Equality(Instance, 0, 0))
    return 0;
  major = pu->major;
  minor = pu->minor;
  VisualData = sBtlGetVisualData(major, minor);
  if (skillid != 1539)
  {
    if (skillid != 1540)
    {
      if (skillid == 1541)
      {
        v15 = 450.0;
      }
      else
      {
        v15 = 50.0;
        z = 0.0;
        x = 0.0;
      }
LABEL_30:
      v20 = v15 + (f32)(VisualData->nml->cylinder * 0.5);
      return (loc_1EBBA80)(0, x, z, pu->pos.x, pu->pos.z) < v20;
    }
    if ((pu->flg & 0x3C0802) == 0)
    {
      v15 = 250.0;
      goto LABEL_30;
    }
    return 0;
  }
  v16 = get_Instance(0);
  IsActive = IsActive(v16, 0, 0);
  result = 0;
  if (IsActive)
  {
    if ((pu->flg & 0x3C0802) == 0)
    {
      v18 = get_Instance(0);
      if (IsTaxiMove(v18, 0))
      {
        v19 = get_Instance(0);
        Pos = GetPos(v19, 0, 0);
        x = Pos.x;
        z = Pos.z;
        v15 = 125.0;
        goto LABEL_30;
      }
    }
    return 0;
  }
  return result;
}

// 0x1ea56f0
bool sBtlBS_AKAMA2_HitKaihi(SBTLUNIT_WORK *pu) {
  return (pu->flg & 0x3C0802) == 0;
}

// 0x1ea5630
static void BS_AKAMA2_Dmg(SBTLUNIT_WORK *wk, SBTLUNIT_WORK *pu, SKLID skillid) {
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  sdfVector4_t v11;

  x = pu->pos.x;
  y = pu->pos.y;
  z = pu->pos.z;
  w = pu->pos.w;
  v11.x = x;
  v11.y = y;
  v11.z = z;
  v11.w = w;
  SetDamageProc(pu, wk, skillid, v11);
  if (skillid == 1541)
    pu->yuka_damagecnt = pu->damagecnt;
}

// 0x1ea5820
void sBtlBS_ITIMOK_Init_Kaiten(SBTLUNIT_WORK *wk) {
  SBTLACTION_WORK *actwk;
  s64 i;
  char *v7;

  actwk = wk->actwk;
  actwk->status = 62;
  actwk->exStep = 0;
  actwk->exWait = 0;
  sBtlSetWince_Full(wk);
  gTimeOutCnt = 0;
  for (i = 0; ; ++i)
  {
    if (i >= SLODWORD(bs_se_stock->max_length))
      break;
    v7 = (char *)bs_se_stock + 4 * i;
    *((u32 *)v7 + 8) = -1;
  }
}

// 0x1ea5980
bool sBtlBS_ITIMOK_Action_Kaiten(SBTLUNIT_WORK *wk, const sdfVector4_t *oldpos) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  SBTLUNIT_WORK *PChara;
  SBTLACTION_WORK *actwk;
  SBTLUNIT_WORK *v12;
  s32 exStep;
  f32 v14;
  f32 v15;
  f32 v16;
  f32 v17;
  SBTLACTION_WORK *v20;
  s32 v21;
  bool v22;
  u32 v24;
  s32 v26;
  f32 v27;
  f32 v28;
  f32 v29;
  f32 v30;
  bool v33;
  SBTLACTION_WORK *v35;
  s32 v36;
  SBTLUNIT_WORK *v39;
  bool v46;
  f32 v48;
  f32 v49;
  f32 v51;
  f32 v52;
  u32 status;
  SBTLACTION_WORK *v55;
  s32 v56;
  s32 v57;
  SBTLACTION_WORK *v59;
  s32 v60;
  s32 v64;
  SBTLACTION_WORK *v65;
  f32 v67;
  f32 v68;
  f32 v69;
  f32 v70;
  SBTLACTION_WORK *v72;
  s32 v73;
  SBTLACTION_WORK *v77;
  bool v79;
  SBTLACTION_WORK *v80;
  SBTLACTION_WORK *v82;
  s32 v83;
  s32 v87;
  s32 v88;
  s32 exSeWait;
  s32 v90;
  s32 v92;
  s32 gTimeOutCnt_local;
  dds3ModelHandle_t *hModel;
  f32 MotionFrameF;
  bool v99;
  f32 v107;
  s32 use_skillid;
  void *v109;
  SBTLACTION_WORK *v111;
  s32 v112;
  void *Instance;
  f32 v117;
  f32 v118;
  f32 v119;
  f32 v120;
  void *v122;
  SBTLACTION_WORK *v125;
  s32 flg;
  s32 v130;
  sdfVector4_t v131;
  sdfVector4_t v132;
  sdfVector4_t v133;
  sdfVector4_t v134;
  sdfVector4_t v135;
  sdfVector4_t v136;
  sdfVector4_t v137;

  w = oldpos->w;
  z = oldpos->z;
  y = oldpos->y;
  x = oldpos->x;
  PChara = sBtlGetPChara();
  actwk = wk->actwk;
  v12 = PChara;
  exStep = actwk->exStep;
  if (exStep <= 360)
  {
    if (exStep <= 200)
    {
      if (exStep)
      {
        if (exStep == 100)
        {
          exSeWait = actwk->exSeWait;
          if (exSeWait)
          {
            v90 = exSeWait - 1;
            actwk->exSeWait = v90;
            if (v90 <= 0)
            {
              if (BS_ITIMOK_SkillSpd)
                v92 = 16;
              else
                v92 = 19;
              BS_ITIMOK_SE(wk, v92);
            }
          }
          gTimeOutCnt_local = gTimeOutCnt + 1;
          gTimeOutCnt = gTimeOutCnt_local;
          if (gTimeOutCnt_local == 2)
            goto LABEL_149;
          gTimeOutCnt_local = gTimeOutCnt;
          if (gTimeOutCnt_local == 4)
            goto LABEL_149;
          gTimeOutCnt_local = gTimeOutCnt;
          if (gTimeOutCnt_local == 6)
            goto LABEL_149;
          gTimeOutCnt_local = gTimeOutCnt;
          if (gTimeOutCnt_local == 8)
            goto LABEL_149;
          gTimeOutCnt_local = gTimeOutCnt;
          if (gTimeOutCnt_local == 10)
          {
LABEL_149:
            if (wk->motionID != 32)
              goto LABEL_264;
            hModel = wk->hModel;
            MotionFrameF = mdlGetMotionFrameF(hModel);
            if (MotionFrameF >= 0.0 && MotionFrameF < 0.01)
            {
LABEL_264:
              sBtlSetMotion(wk, 32, 0, 0, 1);
              if (BS_ITIMOK_SkillSpd)
                wk->m_rate = wk->m_rate + wk->m_rate;
            }
          }
          v99 = sBtlCheckMotionEnd(wk);
          if (v99)
          {
            if (gTimeOutCnt > 10)
              goto LABEL_265;
          }
          if (!BS_ITIMOK_SkillSpd)
          {
            if (gTimeOutCnt > 96)
              goto LABEL_265;
          }
          if (BS_ITIMOK_SkillSpd)
          {
            if (gTimeOutCnt >= 52)
            {
LABEL_265:
              BS_ITIMOK_Motion(wk, 0);
              wk->actwk->exStep = 200;
              gTimeOutCnt = 0;
            }
          }
        }
        else
        {
          if (exStep != 200)
            goto LABEL_214;
          wk->status |= 1u;
          ++gTimeOutCnt;
          v46 = sBtlCheckMotionEnd(wk);
          if (v46)
            goto LABEL_266;
          if (gTimeOutCnt >= 60)
          {
LABEL_266:
            BS_ITIMOK_LoopMove(wk, v12, 1);
          }
        }
        v27 = v12->pos.x;
        v28 = v12->pos.y;
        v29 = v12->pos.z;
        v30 = v12->pos.w;
LABEL_179:
        v133.x = v27;
        v133.y = v28;
        v39 = wk;
        v133.z = v29;
        v133.w = v30;
        goto LABEL_180;
LABEL_178:
        goto LABEL_179;
      }
      wk->flg |= 2u;
      sBtlSetMotion(wk, 32, 0, 0, 1);
      wk->actwk->exStep = 100;
      gTimeOutCnt = 0;
      if (BS_ITIMOK_SkillSpd)
      {
        v87 = 15;
        v88 = 1;
        wk->m_rate = wk->m_rate + wk->m_rate;
      }
      else
      {
        v88 = 0;
        v87 = 20;
      }
      Instance = get_Instance(0);
      Play(Instance, v88, 0);
      wk->actwk->exSeWait = v87;
      wk->status &= ~0x80000u;
      v117 = v12->pos.x;
      v118 = v12->pos.y;
      v119 = v12->pos.z;
      v120 = v12->pos.w;
      v136.x = v117;
      v136.y = v118;
      v136.z = v119;
      v136.w = v120;
      wk->mv_rotbk = DirSet(wk, v136, 1);
      MoveSet(wk, 0.0);
      if (wk->actwk->use_skillid != 1536)
        goto LABEL_214;
      v122 = get_Instance(0);
      ReqCallMark(v122, 180, 0);
      v56 = 0;
      goto LABEL_215;
    }
    if (exStep == 300)
    {
      BS_ITIMOK_Hit(wk);
      v59 = wk->actwk;
      v60 = v59->exWait - 1;
      v22 = v59->exWait == 1;
      v59->exWait = v60;
      if (v60 >= 0 && !v22)
        goto LABEL_214;
      v64 = BS_ITIMOK_SkillCntNow + 1;
      BS_ITIMOK_SkillCntNow = v64;
      v65 = wk->actwk;
      if (v64 >= BS_ITIMOK_SkillCntMax)
      {
        v56 = 0;
        v65->exStep = 600;
        v65->exWait = 120;
      }
      else
      {
        v65->exWait = 60;
        v65->exStep = 350;
        MoveSet(wk, 0.0);
        DirSetHokanInit(wk);
        v56 = 0;
      }
      goto LABEL_215;
    }
    if (exStep != 350)
    {
      if (exStep != 360)
        goto LABEL_214;
      BS_ITIMOK_Hit(wk);
      ++gTimeOutCnt;
      v33 = sBtlCheckMotionEnd(wk);
      if (!v33)
      {
        if (gTimeOutCnt < 70)
          goto LABEL_214;
      }
      goto LABEL_104;
    }
    BS_ITIMOK_Hit(wk);
    v67 = v12->pos.x;
    v68 = v12->pos.y;
    v69 = v12->pos.z;
    v70 = v12->pos.w;
    v134.x = v67;
    v134.y = v68;
    v134.z = v69;
    v134.w = v70;
    sBtlGetRotate(wk, v134);
    v135.x = v67;
    v135.y = v68;
    v135.z = v69;
    v135.w = v70;
    sBtlCheckRotSpd(wk, v135);
    v72 = wk->actwk;
    v73 = v72->exWait - 1;
    v22 = v72->exWait == 1;
    v72->exWait = v73;
    if (v73 >= 0 && !v22)
      goto LABEL_214;
    v72 = wk->actwk;
    BS_ITIMOK_SkillOld[1] = BS_ITIMOK_SkillOld[0];
    BS_ITIMOK_SkillOld[0] = v72->use_skillid;
    if (BS_ITIMOK_SkillType != 2)
    {
      use_skillid = wk->actwk->use_skillid;
      if (use_skillid != 1536)
        goto LABEL_253;
      goto LABEL_199;
    }
    if (BS_ITIMOK_SkillCntNow == 1)
    {
      v77 = wk->actwk;
    }
    else
    {
      v77 = wk->actwk;
      if (BS_ITIMOK_SkillOld[0] == BS_ITIMOK_SkillOld[1])
      {
        if (v77->use_skillid == 1536)
        {
          v77->use_skillid = 1537;
          use_skillid = wk->actwk->use_skillid;
          if (use_skillid != 1536)
            goto LABEL_253;
        }
        else
        {
          v77->use_skillid = 1536;
          use_skillid = wk->actwk->use_skillid;
          if (use_skillid != 1536)
            goto LABEL_253;
        }
        goto LABEL_199;
      }
    }
    if (GetPercentage() <= 0x31u)
      v130 = 1536;
    else
      v130 = 1537;
    v77->use_skillid = v130;
    use_skillid = wk->actwk->use_skillid;
    if (use_skillid != 1536)
    {
LABEL_253:
      goto LABEL_254;
    }
LABEL_199:
    v109 = get_Instance(0);
    ReqCallMark(v109, 180, 0);
    use_skillid = wk->actwk->use_skillid;
LABEL_254:
    v111 = wk->actwk;
    if (use_skillid == BS_ITIMOK_SkillOld[0])
    {
      v56 = 0;
      v111->exStep = 370;
      v111->exWait = 60;
      goto LABEL_215;
    }
    v112 = v111->use_skillid;
    if (v112 == 1537)
    {
      BS_ITIMOK_Motion(wk, 3);
      v55 = wk->actwk;
      v56 = 0;
      v57 = 360;
    }
    else
    {
      BS_ITIMOK_Motion(wk, 4);
      v55 = wk->actwk;
      v56 = 0;
      v57 = 361;
    }
LABEL_259:
    v55->exStep = v57;
    gTimeOutCnt = 0;
    goto LABEL_215;
  }
  if ((u32)exStep <= 0x258)
  {
    if (exStep != 361)
    {
      if (exStep != 370)
      {
        if (exStep != 600)
          goto LABEL_214;
        BS_ITIMOK_Hit(wk);
        v35 = wk->actwk;
        v36 = v35->exWait - 1;
        v22 = v35->exWait == 1;
        v35->exWait = v36;
        if (v36 >= 0 && !v22)
          goto LABEL_214;
        v35->exStep = 610;
        v133.x = 0.0;
        v133.y = 0.0;
        v39 = wk;
        v133.z = 0.0;
        v133.w = 0.0;
LABEL_180:
        v56 = 0;
        wk->mv_rotbk = DirSet(v39, v133, 1);
        goto LABEL_215;
      }
      BS_ITIMOK_Hit(wk);
      v82 = wk->actwk;
      v83 = v82->exWait - 1;
      v22 = v82->exWait == 1;
      v82->exWait = v83;
      if (v83 >= 0 && !v22)
        goto LABEL_214;
      BS_ITIMOK_LoopMove(wk, v12, 1);
      v56 = 0;
      goto LABEL_215;
    }
    BS_ITIMOK_Hit(wk);
    ++gTimeOutCnt;
    v79 = sBtlCheckMotionEnd(wk);
    if (!v79)
    {
      if (gTimeOutCnt < 69)
        goto LABEL_214;
    }
LABEL_104:
    v80 = wk->actwk;
    v80->exStep = 370;
    v80->exWait = 0;
    BS_ITIMOK_Motion(wk, 1);
    v56 = 0;
    goto LABEL_215;
  }
  if ((u32)exStep > 0x26C)
  {
    if (exStep == 630)
    {
      ++gTimeOutCnt;
      if (sBtlCheckMotionEnd(wk))
        goto LABEL_189;
      if (gTimeOutCnt >= 69)
      {
LABEL_189:
        wk->actwk->exStep = 10000;
        ClrAction();
        v56 = 1;
        goto LABEL_215;
      }
      goto LABEL_214;
    }
    if (exStep == 1000)
    {
      v14 = PChara->pos.x;
      v15 = PChara->pos.y;
      v17 = PChara->pos.z;
      v16 = PChara->pos.w;
      v131.x = v14;
      v131.y = v15;
      v131.z = v17;
      v131.w = v16;
      sBtlGetRotate(wk, v131);
      v132.x = v14;
      v132.y = v15;
      v132.z = v17;
      v132.w = v16;
      sBtlCheckRotSpd(wk, v132);
      v20 = wk->actwk;
      v21 = v20->exWait - 1;
      v22 = v20->exWait == 1;
      v20->exWait = v21;
      if (v21 >= 0 && !v22)
        goto LABEL_214;
      if (!v24)
      {
        v20 = wk->actwk;
      }
      v20->exStep = 0;
      BS_ITIMOK_SkillCntNow = 0;
      if (v20->use_skillid == 1536)
        v26 = 1537;
      else
        v26 = 1536;
      v20->use_skillid = v26;
      v27 = v12->pos.x;
      v28 = v12->pos.y;
      v29 = v12->pos.z;
      v30 = v12->pos.w;
      if (v24)
        goto LABEL_179;
      goto LABEL_178;
    }
LABEL_214:
    v56 = 0;
    goto LABEL_215;
  }
  if (exStep != 610)
  {
    if (exStep != 620)
      goto LABEL_214;
    BS_ITIMOK_Hit(wk);
    v48 = wk->pos.x;
    v49 = wk->pos.z;
    v51 = sqrtf((f32)(v48 * v48) + (f32)(v49 * v49));
    v52 = 45.0;
    if (!BS_ITIMOK_SkillSpd)
      v52 = 35.0;
    if (v51 > v52)
      goto LABEL_214;
    status = wk->status;
    wk->pos.x = 0.0;
    wk->pos.z = 0.0;
    wk->status = status & 0xFFFFFFFE;
    MoveSet(wk, 0.0);
    BS_ITIMOK_Motion(wk, 2);
    v55 = wk->actwk;
    v56 = 0;
    v57 = 630;
    goto LABEL_259;
  }
  BS_ITIMOK_Hit(wk);
  if (BS_ITIMOK_SkillSpd)
    v107 = 45.0;
  else
    v107 = 35.0;
  MoveSet(wk, v107);
  v56 = 0;
  wk->actwk->exStep = 620;
  wk->status |= 1u;
LABEL_215:
  Proc(wk);
  sBtlProc(wk);
  if ((wk->status & 1) == 0)
    sBtlMVSupport(wk);
  UnitMV(wk);
  v137.x = x;
  v137.y = y;
  v137.z = z;
  v137.w = w;
  if (CheckMapHit(wk, v137))
  {
    v125 = wk->actwk;
    if (v125->exStep == 300)
      v125->exWait = 1;
  }
  UnitMV_To_Basic(wk);
  if (!v56)
    return 1;
  ResetAction(wk);
  sBtlSetAction(wk, 2, 0);
  sBtlEndAction(wk);
  flg = wk->flg;
  wk->pos.x = 0.0;
  wk->pos.z = 0.0;
  wk->flg = flg & 0xFFFFFFFD;
  return 1;
}

// 0x1ea6c70
static void BS_ITIMOK_Motion(SBTLUNIT_WORK *wk, s32 type) {
  s32 v5;
  void *Instance;
  void *v7;
  void *v8;
  s32 use_skillid;
  void *v11;
  void *v13;
  void *v14;
  void *v15;
  void *v16;
  void *v17;
  void *v18;

  switch (type)
  {
    case 0:
      if (wk->actwk->use_skillid == 1536)
        v5 = 33;
      else
        v5 = 36;
      Instance = get_Instance(0);
      Stop(Instance, 2, 0);
      v7 = get_Instance(0);
      Stop(v7, 3, 0);
      if (wk->actwk->use_skillid != 1536)
        goto LABEL_27;
      v8 = get_Instance(0);
      ReqCallMark(v8, 180, 0);
      break;
    case 1:
      use_skillid = wk->actwk->use_skillid;
      v11 = get_Instance(0);
      if (use_skillid == 1536)
      {
        Play(v11, 2, 0);
        BS_ITIMOK_SE(wk, 17);
        v5 = 34;
      }
      else
      {
        Play(v11, 3, 0);
        BS_ITIMOK_SE(wk, 18);
        v5 = 37;
      }
      break;
    case 2:
      if (wk->actwk->use_skillid == 1536)
        v5 = 35;
      else
        v5 = 38;
      v13 = get_Instance(0);
      Stop(v13, 2, 0);
      v14 = get_Instance(0);
      Stop(v14, 3, 0);
      break;
    case 3:
      v15 = get_Instance(0);
      Stop(v15, 2, 0);
      v16 = get_Instance(0);
      Stop(v16, 3, 0);
      v5 = 39;
      break;
    case 4:
      v17 = get_Instance(0);
      Stop(v17, 2, 0);
      v18 = get_Instance(0);
      Stop(v18, 3, 0);
      v5 = 40;
LABEL_27:
      break;
    default:
      v5 = 0;
      break;
  }
  sBtlSetMotion(wk, v5, 0, 0, 1);
}

// 0x1ea4890
static f32 DirSet(SBTLUNIT_WORK *wk, const sdfVector4_t *pos, bool wk_rot_set) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  f32 *p_x;
  long f64 v13;
  f32 v14;
  sdfVector4_t *p_rot;
  struct sdfVector4_t v19;

  w = pos->w;
  z = pos->z;
  y = pos->y;
  x = pos->x;
  v19 = wk->pos;
  vct_A = v19;
  p_x = &vf00.x;
  p_x[8] = x;
  p_x[9] = y;
  p_x[10] = z;
  p_x[11] = w;
  vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  v13 = sub_18E6660(0, wk_rot_set);
  v14 = *(f32 *)&v13;
  FromEuler(0.0, *(f32 *)&v13, 0.0);
  if (wk_rot_set)
  {
    p_rot = &wk->rot;
    *p_rot = vct_A;
    return v14;
  }
  return v14;
}

// 0x1ea7380
static void DirSetHokanInit(SBTLUNIT_WORK *wk) {
  struct sdfVector4_t rot;

  rot = wk->rot;
  vct_A = rot;
  wk->mv_rotbk = -EulerAngleAxisY();
}

// 0x1ea7470
static f32 DirSetHokan(SBTLUNIT_WORK *wk, const sdfVector4_t *pos, f32 spd) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  sdfVector4_t v10;
  sdfVector4_t v11;

  w = pos->w;
  z = pos->z;
  y = pos->y;
  x = pos->x;
  v10.x = x;
  v10.y = y;
  v10.z = z;
  v10.w = w;
  sBtlGetRotate(wk, v10);
  v11.x = x;
  v11.y = y;
  v11.z = z;
  v11.w = w;
  sBtlCheckRotSpd(wk, v11);
  return 0.0;
}

// 0x1ea69c0
static void MoveSet(SBTLUNIT_WORK *wk, f32 spd) {
  f32 w;

  *(u64 *)&wk->mv_spd.x = 0;
  wk->mv_spd.z = spd;
  w = wk->mv_spd.w;
  *(u64 *)&vct_A.x = 0;
  vct_A.z = spd;
  vct_A.w = w;
  wk->mv_spdbk = vct_A;
}

// 0x1ea6f20
static void BS_ITIMOK_LoopMove(SBTLUNIT_WORK *wk, SBTLUNIT_WORK *pu, bool motion_set) {
  f32 v9;
  SBTLACTION_WORK *actwk;

  if (motion_set)
    BS_ITIMOK_Motion(wk, 1);
  v9 = 45.0;
  if (!BS_ITIMOK_SkillSpd)
    v9 = 35.0;
  MoveSet(wk, v9);
  actwk = wk->actwk;
  actwk->exWait = 300;
  actwk->exStep = 300;
  SetAction(1);
  wk->mv_rotbk = DirSet(wk, pu->pos, 1);
}

// 0x1ea7530
static SKLID RandomSet_NBS_ICI(void) {
  if (GetPercentage() <= 0x31u)
    return 1536;
  else
    return 1537;
}

// 0x1ea7040
static void BS_ITIMOK_Hit(SBTLUNIT_WORK *wk) {
  SBTLUNIT_WORK *PChara;
  s32 use_skillid;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  SBTLUNIT_WORK *Nakama;
  SBTLUNIT_WORK *v17;
  sdfVector4_t v19;

  if (wk->cmbSkl->bRun)
    return;
  if (sBtlCheckSetsuma())
    return;
  if (IsSceanStop())
    return;
  if (wk->mode == 5)
    return;
  sBtlGetPChara();
  PChara = sBtlGetPChara();
  if (!BS_ITIMOK_HitSub(wk, PChara))
  {
    goto LABEL_22;
  }
  use_skillid = wk->actwk->use_skillid;
  x = PChara->pos.x;
  y = PChara->pos.y;
  z = PChara->pos.z;
  w = PChara->pos.w;
  v19.x = x;
  v19.y = y;
  v19.z = z;
  v19.w = w;
  SetDamageProc(PChara, wk, use_skillid, v19);
LABEL_22:
  if (wk->NakamaShugouOn)
    return;
  Nakama = sBtlGetNakama(0);
  if (BS_ITIMOK_HitSub(wk, Nakama))
  {
    BS_ITIMOK_Dmg(wk, Nakama);
  }
  v17 = sBtlGetNakama(1);
  if (BS_ITIMOK_HitSub(wk, v17))
  {
    BS_ITIMOK_Dmg(wk, v17);
  }
}

// 0x1ea7700
static bool BS_ITIMOK_HitSub(SBTLUNIT_WORK *wk, SBTLUNIT_WORK *pu) {
  u16 major;
  s32 minor;
  VISUALDATA_WORK *VisualData;
  VISUALDATA_WORK *v9;
  s64 v10;
  VISUALDATA_WORK *v12;
  f32 v13;
  f32 x;
  f32 z;
  f32 v16;
  f32 v17;
  f32 v18;
  f32 v19;
  f32 v20;
  f32 v25;
  f32 w;
  f32 per;
  f32 Radian;
  f32 v29;
  f32 v30;
  f32 v31;
  f32 v32;
  f32 y;
  f32 v34;
  sdfVector4_t v35;
  sdfVector4_t pos;
  sdfVector4_t v37;

  if (!pu || pu->damagecnt > 0 || pu->para->now->hp < 1)
    return 0;
  major = pu->major;
  minor = pu->minor;
  VisualData = sBtlGetVisualData(major, minor);
  v9 = sBtlGetVisualData(wk->major, wk->minor);
  v12 = v9;
  if (wk->actwk->use_skillid == 1536)
    v13 = 350.0;
  else
    v13 = (f32)(v9->nml->cylinder * 0.5) + 100.0;
  x = pu->pos.x;
  z = pu->pos.z;
  v16 = wk->pos.x;
  v17 = wk->pos.z;
  v18 = VisualData->nml->cylinder * 0.5;
  v19 = v13 + v18;
  v20 = sqrtf((f32)((f32)(v16 - x) * (f32)(v16 - x)) + (f32)((f32)(v17 - z) * (f32)(v17 - z)));
  if (v20 >= v19)
    return 0;
  if (wk->actwk->use_skillid != 1536)
  {
    if ((pu->flg & 0x3C0802) == 0)
    {
      pos = wk->pos;
      v37.x = wk->rot.x;
      v37.y = wk->rot.y;
      v25 = wk->rot.z;
      w = wk->rot.w;
      per = pu->pos.x;
      y = wk->pos.y;
      v34 = wk->pos.x;
      v31 = wk->pos.w;
      v32 = wk->pos.z;
      v29 = wk->rot.y;
      v30 = wk->rot.x;
      v37.y = v29;
      v37.x = v30;
      pos.w = v31;
      pos.z = v32;
      pos.y = y;
      pos.x = v34;
      v37.z = v25;
      v37.w = w;
      *(u64 *)&v35.x = 0;
      *(u64 *)&v35.z = v10;
      Radian = sBtlGetRadian(pos, v37, v35, per);
      if (v20 <= (f32)(v12->nml->cylinder * 0.5) || Radian >= -20.0 && Radian <= 20.0)
        return 1;
      if (Radian <= -160.0 && Radian >= 160.0)
        return 1;
    }
    return 0;
  }
  return pu->JumpOfsPos.y > -10.0;
}

// 0x1ea79c0
static void BS_ITIMOK_Dmg(SBTLUNIT_WORK *wk, SBTLUNIT_WORK *pu) {
  s32 use_skillid;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  sdfVector4_t v10;

  use_skillid = wk->actwk->use_skillid;
  x = pu->pos.x;
  y = pu->pos.y;
  z = pu->pos.z;
  w = pu->pos.w;
  v10.x = x;
  v10.y = y;
  v10.z = z;
  v10.w = w;
  SetDamageProc(pu, wk, use_skillid, v10);
}

// 0x1ea7a60
void sBtlBS_LASTB1_Init_Setu(SBTLUNIT_WORK *wk) {
  SBTLACTION_WORK *actwk;
  s64 i;
  char *v7;

  actwk = wk->actwk;
  actwk->status = 68;
  actwk->exStep = 0;
  actwk->exWait = 0;
  sBtlSetWinceStop(wk, 1);
  sBtlSetWince_Full(wk);
  for (i = 0; ; ++i)
  {
    if (i >= SLODWORD(bs_se_stock->max_length))
      break;
    v7 = (char *)bs_se_stock + 4 * i;
    *((u32 *)v7 + 8) = -1;
  }
  gDofNml = 0.0;
}

// 0x1ea7bb0
bool sBtlBS_LASTB1_Action_Setu(SBTLUNIT_WORK *wk, const sdfVector4_t *oldpos) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  SBTLUNIT_WORK *PChara;
  SBTLACTION_WORK *actwk;
  s32 exStep;
  f32 *v12;
  void *Instance;
  f32 v15;
  f32 v16;
  f32 v17;
  f32 v18;
  s32 v19;
  s32 v20;
  SBTLACTION_WORK *v21;
  s32 v22;
  f32 v23;
  f32 v24;
  f32 v25;
  f32 v26;
  f32 v27;
  SBTLACTION_WORK *v28;
  sdfVector4_t v31;
  sdfVector4_t v32;
  sdfVector4_t v33;

  w = oldpos->w;
  z = oldpos->z;
  y = oldpos->y;
  x = oldpos->x;
  PChara = sBtlGetPChara();
  actwk = wk->actwk;
  exStep = actwk->exStep;
  if (exStep <= 2100)
  {
    v12 = PChara;
    if (exStep != 2100)
    {
      if (exStep)
        goto LABEL_27;
      Instance = get_Instance(0);
      SetumaButton_Kaya_GoutoVoive(Instance, 1, 0);
      sBtlSetMotion(wk, 37, 0, 2, 1);
      v15 = v12[41];
      v16 = v12[42];
      v18 = v12[43];
      v17 = v12[44];
      v31.x = v15;
      v31.y = v16;
      v31.z = v18;
      v31.w = v17;
      wk->mv_rotbk = DirSet(wk, v31, 1);
      v19 = 50;
      v20 = 2100;
      goto LABEL_13;
    }
    v22 = actwk->exWait - 1;
    actwk->exWait = v22;
    if (!v22)
    {
      sBtlSetSetsuma_EnemyUse(wk);
    }
    v23 = v12[41];
    v24 = v12[42];
    v26 = v12[43];
    v25 = v12[44];
    v32.x = v23;
    v32.y = v24;
    v32.z = v26;
    v32.w = v25;
    v27 = DirSet(wk, v32, 1);
    v28 = wk->actwk;
    wk->mv_rotbk = v27;
    if (v28->exWait <= 0)
    {
      if (sBtlCheckMotionEnd(wk))
      {
        sBtlSetMotion(wk, 38, 0, 0, 1);
        v19 = 60;
        v20 = 2200;
LABEL_13:
        v21 = wk->actwk;
        v21->exStep = v20;
        v21->exWait = v19;
      }
    }
  }
LABEL_27:
  Proc(wk);
  sBtlProc(wk);
  sBtlMVSupport(wk);
  UnitMV(wk);
  v33.x = x;
  v33.y = y;
  v33.z = z;
  v33.w = w;
  CheckMapHit(wk, v33);
  UnitMV_To_Basic(wk);
  return 1;
}

// 0x1ea7ed0
void sBtlBS_LASTB1_Action_Setu_ResetWince(SBTLUNIT_WORK *wk) {
  sBtlSetWinceStop(wk, 0);
}

// 0x1ea7f40
void sBtlBS_LASTB1_Action_Setu_End(SBTLUNIT_WORK *wk) {
  SBTLACTION_WORK *actwk;

  actwk = wk->actwk;
  actwk->exStep = 0;
  actwk->exWait = 0;
  ResetAction(wk);
  sBtlSetAction(wk, 2, 0);
  sBtlEndAction(wk);
}

// 0x1ea7fd0
void sBtlBS_LASTB1_Init_Setr(SBTLUNIT_WORK *wk) {
  SBTLACTION_WORK *actwk;
  s64 i;
  char *v7;

  actwk = wk->actwk;
  actwk->status = 69;
  actwk->exStep = 0;
  actwk->exWait = 0;
  for (i = 0; ; ++i)
  {
    if (i >= SLODWORD(bs_se_stock->max_length))
      break;
    v7 = (char *)bs_se_stock + 4 * i;
    *((u32 *)v7 + 8) = -1;
  }
}

// 0x1ea80d0
bool sBtlBS_LASTB1_Action_Setr(SBTLUNIT_WORK *wk, const sdfVector4_t *oldpos) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  SBTLACTION_WORK *actwk;
  s32 exStep;
  sdfVector4_t v14;

  w = oldpos->w;
  z = oldpos->z;
  y = oldpos->y;
  x = oldpos->x;
  actwk = wk->actwk;
  exStep = actwk->exStep;
  if (exStep == 1)
  {
    actwk->exStep = 0;
    actwk->exWait = 60;
  }
  Proc(wk);
  sBtlProc(wk);
  sBtlMVSupport(wk);
  UnitMV(wk);
  v14.x = x;
  v14.y = y;
  v14.z = z;
  v14.w = w;
  CheckMapHit(wk, v14);
  UnitMV_To_Basic(wk);
  if (exStep == 1)
  {
    ResetAction(wk);
    sBtlSetAction(wk, 2, 0);
    sBtlEndAction(wk);
  }
  return 1;
}

// 0x1ea8290
void sBtlBS_LASTB1_Action_Setr_End(SBTLUNIT_WORK *wk) {
  SBTLACTION_WORK *actwk;

  actwk = wk->actwk;
  actwk->exStep = 0;
  actwk->exWait = 0;
  ResetAction(wk);
  sBtlSetAction(wk, 2, 0);
  sBtlEndAction(wk);
}

// 0x1ea8320
void sBtlBS_LASTB1_Init_Dang(SBTLUNIT_WORK *wk) {
  SBTLACTION_WORK *actwk;
  s64 i;
  char *v7;

  actwk = wk->actwk;
  actwk->status = 70;
  actwk->exStep = 0;
  actwk->exWait = 0;
  for (i = 0; ; ++i)
  {
    if (i >= SLODWORD(bs_se_stock->max_length))
      break;
    v7 = (char *)bs_se_stock + 4 * i;
    *((u32 *)v7 + 8) = -1;
  }
}

// 0x1ea8420
bool sBtlBS_LASTB1_Action_Dang(SBTLUNIT_WORK *wk, const sdfVector4_t *oldpos) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  SBTLACTION_WORK *actwk;
  s32 v9;
  s32 v11;
  s32 v12;
  bool v13;
  void *Instance;
  sdfVector4_t v18;

  w = oldpos->w;
  z = oldpos->z;
  y = oldpos->y;
  x = oldpos->x;
  sBtlGetPChara();
  actwk = wk->actwk;
  switch (actwk->exStep)
  {
    case 0:
      v9 = 0;
      actwk->exStep = 1;
      goto LABEL_12;
    case 1:
      sBtlSetMotion(wk, 36, 0, 0, 0);
      actwk = wk->actwk;
      v9 = 0;
      v11 = 2;
      goto LABEL_24;
    case 2:
      v12 = actwk->exWait - 1;
      v13 = actwk->exWait == 1;
      actwk->exWait = v12;
      if (v12 >= 0 && !v13)
        goto LABEL_10;
      v9 = 0;
      v11 = 3;
LABEL_24:
      actwk->exStep = v11;
      actwk->exWait = 60;
      goto LABEL_12;
    case 3:
      Instance = get_Instance(0);
      Stop(Instance, 2, 0);
      v9 = 1;
      wk->actwk->exStep = 0;
      goto LABEL_12;
    default:
LABEL_10:
      v9 = 0;
LABEL_12:
      Proc(wk);
      sBtlProc(wk);
      sBtlMVSupport(wk);
      UnitMV(wk);
      v18.x = x;
      v18.y = y;
      v18.z = z;
      v18.w = w;
      CheckMapHit(wk, v18);
      UnitMV_To_Basic(wk);
      if (v9)
      {
        ResetAction(wk);
        sBtlSetAction(wk, 2, 0);
        sBtlEndAction(wk);
      }
      return 1;
  }
}

// 0x1ea86a0
bool sBtlBS_LASTB1_Action_DangCheck(SBTLUNIT_WORK *wk) {
  return wk->actwk->status < 3;
}

// 0x1ea86c0
bool BS_LASTB1_Action_DangCheck(SBTLUNIT_WORK *_wk, SKLID _sklID) {
  if (wk->encountno != 58)
    return 0;
  return (sklID & 0xFFFFFFFE) == 0x510 && wk->para->devilid == 257;
}

// 0x1ea8790
void sBtlBS_LASTB1_Init_Dsmn(SBTLUNIT_WORK *wk) {
  SBTLACTION_WORK *actwk;
  s64 i;
  char *v7;

  actwk = wk->actwk;
  actwk->status = 72;
  actwk->exStep = 0;
  actwk->exWait = 0;
  for (i = 0; ; ++i)
  {
    if (i >= SLODWORD(bs_se_stock->max_length))
      break;
    v7 = (char *)bs_se_stock + 4 * i;
    *((u32 *)v7 + 8) = -1;
  }
}

// 0x1ea8890
bool sBtlBS_LASTB1_Action_Dsmn(SBTLUNIT_WORK *wk, const sdfVector4_t *oldpos) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  SBTLACTION_WORK *actwk;
  s32 exStep;
  _BOOL4 v10;
  s32 v11;
  bool v12;
  SBTLACTION_WORK *v13;
  s64 v14;
  s32 v16;
  SBTLACTION_WORK *v19;
  s32 exWait;
  s32 v22;
  SBTLSM_LISTWORK *v24;
  s32 v25;
  s32 v26;
  s32 v27;
  bool v28;
  SBTLACTION_WORK *v29;
  s32 v30;
  SBTLACTION_WORK *v35;
  void *v37;
  s32 v38;
  void *Instance;
  void *v40;
  SBATTLE_WORK *v44;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 playerID;
  SBTLUNIT_WORK *v47;
  s32 v48;
  s32 v49;
  s32 v50;
  SBTLSM_LISTWORK *sysmsgList;
  SBATTLE_WORK *v53;
  SBTLUNIT_LISTWORK *v54;
  s32 v55;
  SBTLUNIT_WORK *v56;
  s32 v59;
  SBTLSM_LISTWORK *v61;
  SBTLUNIT_WORK *Nakama;
  SBTLUNIT_WORK *v63;
  SBATTLE_WORK *v67;
  u32 *p_stock_mask;
  s32 v69;
  SBTLUNIT_WORK *v70;
  SBTLUNIT_WORK *v71;
  SBATTLE_WORK *v75;
  u32 *v76;
  s32 v77;
  s32 v78;
  void *v79;
  SBATTLE_WORK *v83;
  SBTLUNIT_LISTWORK *v84;
  s32 v85;
  SBTLUNIT_WORK *v86;
  s32 v87;
  SBTLSM_LISTWORK *v93;
  sdfVector4_t v94;

  w = oldpos->w;
  z = oldpos->z;
  y = oldpos->y;
  x = oldpos->x;
  sBtlGetPChara();
  actwk = wk->actwk;
  exStep = actwk->exStep;
  if (exStep > 2003)
  {
    v10 = 0;
    if (exStep > 2199)
    {
      switch (exStep)
      {
        case 2200:
          v11 = actwk->exWait - 1;
          v12 = actwk->exWait == 1;
          actwk->exWait = v11;
          if (v11 >= 0 && !v12)
            goto LABEL_145;
          dds3FadeOut(0xFFu, 0xFFu, 0xFFu, 0x1Eu);
          v13 = wk->actwk;
          v14 = 32;
          v13->exWait = 30;
          v13->exStep = 2201;
          do
          {
            v10 = 0;
            *(u32 *)((char *)&wk->summonID->obj.klass + v14) = 0;
            v14 += 4;
          }
          while (v14 != 160);
          goto LABEL_146;
        case 2201:
          v38 = actwk->exWait - 1;
          v12 = actwk->exWait == 1;
          actwk->exWait = v38;
          if (v38 >= 0 && !v12)
            goto LABEL_145;
          Instance = get_Instance(0);
          Stop(Instance, 6, 0);
          v40 = get_Instance(0);
          Stop(v40, 7, 0);
          DeleteAll();
          sBtlClearDof2Bokah();
          sBtlSetMode(2);
          sBtlNoHokan();
          v44 = wk;
          v44->battlStopEff = 0;
          UnitMng = v44->UnitMng;
          playerID = v44->playerID;
          v47 = sBtlSearchUnit_ID(UnitMng, playerID);
          sBtlSetBadStatus_No(v47, 0, 0x10u, 0, -1);
          sBtlResetAction(v47);
          sBtlStatusBitOff(v47, 0xFFFFFFEF);
          sBtlKudaHuuin_AllOn(1);
          MOON_IN_PROGRAM();
          actwk = wk->actwk;
          v10 = 0;
          actwk->exWait = 4;
          v25 = 2202;
          goto LABEL_160;
        case 2202:
          v48 = actwk->exWait - 1;
          v12 = actwk->exWait == 1;
          actwk->exWait = v48;
          if (v48 >= 0 && !v12)
            goto LABEL_145;
          dds3FadeIn2(0x1Eu);
          actwk = wk->actwk;
          v10 = 0;
          v25 = 2203;
          actwk->exWait = 30;
          goto LABEL_160;
        case 2203:
          v49 = actwk->exWait - 1;
          v12 = actwk->exWait == 1;
          actwk->exWait = v49;
          if (v49 >= 0 && !v12)
            goto LABEL_145;
          v10 = 0;
          actwk->exWait = 10;
          v25 = 2300;
          goto LABEL_160;
        default:
          if (exStep != 2300)
            goto LABEL_146;
          v27 = actwk->exWait - 1;
          v28 = actwk->exWait - 2 < 0;
          actwk->exWait = v27;
          v10 = v28 != __OFSUB__(v27, 1);
          goto LABEL_147;
      }
    }
    switch (exStep)
    {
      case 2100:
        v50 = actwk->exWait - 1;
        v12 = actwk->exWait == 1;
        actwk->exWait = v50;
        if (v50 >= 0 && !v12)
          goto LABEL_145;
        sysmsgList = wk->sysmsgList;
        sBtlReleaseSM_List(sysmsgList, 1u);
        v53 = wk;
        v54 = v53->UnitMng;
        v55 = v53->playerID;
        v56 = sBtlSearchUnit_ID(v54, v55);
        sBtlSetMotion(v56, 131, 0, 0, 0);
        Add(0);
        sBtlPlaySE(0x501001Bu);
        sBtlSetMove(g_CamMovDsmn3, 1);
        sBtlSetDof2Bokah(1.0, 5.0, 65.0, 4.0, 5.0, 65.0, 4.0);
        sBtlSetMode(13);
        Proc(0);
        actwk = wk->actwk;
        v10 = 0;
        actwk->exWait = 90;
        v25 = 2101;
        break;
      case 2101:
        v59 = actwk->exWait - 1;
        v12 = actwk->exWait == 1;
        actwk->exWait = v59;
        if (v59 >= 0 && !v12)
          goto LABEL_145;
        v61 = wk->sysmsgList;
        sBtlCreateSM(v61, wk, 173, 0, 0, 120);
        Exit3Set();
        Nakama = sBtlGetNakama(0);
        if (Nakama)
        {
          v63 = Nakama;
          wk->battlStopEff = 1;
          sBtlStatusBitOn(v63, 0x10u);
          SetReturn(wk->summonindex[0], 0);
          v67 = wk;
          p_stock_mask = &v67->stock_mask;
          v69 = v67->summonindex[0];
          sBtlResetBit(p_stock_mask, v69);
        }
        v70 = sBtlGetNakama(1);
        if (v70)
        {
          v71 = v70;
          wk->battlStopEff = 1;
          sBtlStatusBitOn(v71, 0x10u);
          SetReturn(wk->summonindex[1], 0);
          v75 = wk;
          v76 = &v75->stock_mask;
          v77 = v75->summonindex[1];
          sBtlResetBit(v76, v77);
        }
        actwk = wk->actwk;
        v10 = 0;
        actwk->exWait = 30;
        v25 = 2102;
        break;
      case 2102:
        v26 = actwk->exWait - 1;
        v12 = actwk->exWait == 1;
        actwk->exWait = v26;
        if (v26 >= 0 && !v12)
        {
LABEL_145:
          v10 = 0;
LABEL_146:
          goto LABEL_147;
        }
        v10 = 0;
        actwk->exWait = 90;
        v25 = 2200;
        break;
      default:
        goto LABEL_146;
    }
    goto LABEL_160;
  }
  v10 = 0;
  if (exStep > 999)
  {
    switch (exStep)
    {
      case 2000:
        exWait = actwk->exWait;
        if (exWait == 55)
        {
          sBtlSetDof2Bokah(90.0, 0.5, 30.0, 4.0, 3.0, 52.0, 4.0);
          actwk = wk->actwk;
          exWait = actwk->exWait;
        }
        v22 = exWait - 1;
        actwk->exWait = v22;
        if (v22 > 0)
          goto LABEL_145;
        v24 = wk->sysmsgList;
        sBtlCreateSM(v24, wk, 11, 0, 0, 120);
        actwk = wk->actwk;
        v10 = 0;
        v25 = 2001;
        actwk->exWait = 0;
        break;
      case 2001:
        v10 = 0;
        actwk->exWait = 146;
        v25 = 2002;
        break;
      case 2002:
        v78 = actwk->exWait - 1;
        v12 = actwk->exWait == 1;
        actwk->exWait = v78;
        if (v78 >= 0 && !v12)
          goto LABEL_145;
        v79 = get_Instance(0);
        Play(v79, 7, 0);
        sBtlPlaySE(0x501001Au);
        sBtlSetMove(g_CamMovDsmn2, 1);
        sBtlSetDof2Bokah(1.0, 3.0, 55.0, 4.0, 3.0, 55.0, 4.0);
        sBtlSetMode(13);
        Proc(0);
        v83 = wk;
        v84 = v83->UnitMng;
        v85 = v83->playerID;
        v86 = sBtlSearchUnit_ID(v84, v85);
        sBtlStatusBitOn(v86, 0x10u);
        actwk = wk->actwk;
        v10 = 0;
        actwk->exWait = 40;
        v25 = 2003;
        break;
      case 2003:
        v87 = actwk->exWait - 1;
        v12 = actwk->exWait == 1;
        actwk->exWait = v87;
        if (v87 >= 0 && !v12)
          goto LABEL_145;
        v93 = wk->sysmsgList;
        sBtlCreateSM(v93, wk, 172, 0, 0, 120);
        actwk = wk->actwk;
        v10 = 0;
        actwk->exWait = 85;
        v25 = 2100;
        break;
      default:
        if (exStep != 1000)
          goto LABEL_146;
        wk->next_motion_not_hokan = 1;
        sBtlSetMotion(wk, 43, 0, 0, 0);
        v37 = get_Instance(0);
        Play(v37, 6, 0);
        sBtlPlaySE(0x5010019u);
        actwk = wk->actwk;
        v10 = 0;
        actwk->exWait = 60;
        v25 = 2000;
        break;
    }
LABEL_160:
    actwk->exStep = v25;
    goto LABEL_147;
  }
  if (exStep)
  {
    if (exStep == 1)
    {
      v30 = actwk->exWait - 1;
      actwk->exWait = v30;
      if (v30)
        goto LABEL_145;
      wk->boss_eventID = wk->ListID;
      sBtlSetMove(g_CamMovDsmn0, 1);
      sBtlSetDof2Bokah(1.0, 0.5, 30.0, 4.0, 0.5, 30.0, 4.0);
      sBtlSetMode(13);
      Proc(0);
      v35 = wk->actwk;
      v10 = 0;
      v35->exStep = 2;
      v35->exWait = 10;
    }
    else
    {
      if (exStep != 2)
        goto LABEL_146;
      v16 = actwk->exWait - 1;
      actwk->exWait = v16;
      if (v16)
        goto LABEL_145;
      sBtlSetMove(g_CamMovDsmn1, 1);
      sBtlSetDof2Bokah(1.0, 0.5, 30.0, 4.0, 0.5, 30.0, 4.0);
      sBtlSetMode(13);
      Proc(0);
      v19 = wk->actwk;
      v10 = 0;
      v19->exStep = 1000;
      v19->exWait = 0;
    }
  }
  else
  {
    sBtlSetMotion(wk, 0, 0, 0, 0);
    v29 = wk->actwk;
    v10 = 0;
    v29->exStep = 1;
    v29->exWait = 5;
  }
LABEL_147:
  Proc(wk);
  sBtlProc(wk);
  sBtlMVSupport(wk);
  UnitMV(wk);
  v94.x = x;
  v94.y = y;
  v94.z = z;
  v94.w = w;
  CheckMapHit(wk, v94);
  UnitMV_To_Basic(wk);
  if (v10)
  {
    ResetAction(wk);
    sBtlSetAction(wk, 2, 0);
    sBtlEndAction(wk);
  }
  return 1;
}

// 0x1ea9720
void sBtlBS_LASTB1_Init_Gurd(SBTLUNIT_WORK *wk) {
  SBTLACTION_WORK *actwk;
  s64 i;
  char *v6;

  actwk = wk->actwk;
  actwk->status = 73;
  actwk->exStep = 0;
  actwk->exWait = 0;
  gGurd_TimeOutCnt = 0;
  for (i = 0; ; ++i)
  {
    if (i >= SLODWORD(bs_se_stock->max_length))
      break;
    v6 = (char *)bs_se_stock + 4 * i;
    *((u32 *)v6 + 8) = -1;
  }
}

// 0x1ea9830
bool sBtlBS_LASTB1_Action_Gurd(SBTLUNIT_WORK *wk, const sdfVector4_t *oldpos) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  SBTLUNIT_WORK *PChara;
  SBTLACTION_WORK *actwk;
  SBTLUNIT_WORK *v11;
  s32 exStep;
  _BOOL4 v13;
  s32 v14;
  f32 v15;
  f32 v16;
  f32 v17;
  f32 v18;
  f32 v19;
  s32 v23;
  bool v24;
  sdfVector4_t v30;
  sdfVector4_t v31;

  w = oldpos->w;
  z = oldpos->z;
  y = oldpos->y;
  x = oldpos->x;
  PChara = sBtlGetPChara();
  actwk = wk->actwk;
  v11 = PChara;
  exStep = actwk->exStep;
  if (exStep != 2000)
  {
    if (exStep == 1000)
    {
      v15 = PChara->pos.x;
      v16 = PChara->pos.y;
      v17 = PChara->pos.z;
      v18 = PChara->pos.w;
      v30.x = v15;
      v30.y = v16;
      v30.z = v17;
      v30.w = v18;
      v19 = DirSet(wk, v30, 1);
      wk->mv_rotbk = v19;
      sBtlSetMotion(wk, 36, 0, 0, 0);
      v13 = 0;
      wk->status |= 0x100u;
      wk->actwk->exStep = 2000;
    }
    else
    {
      v13 = 0;
      if (!exStep)
      {
        actwk->exStep = 1000;
        actwk->exWait = 60;
      }
    }
    goto LABEL_32;
  }
  if (!sBtlCheckMotionEnd(wk))
  {
    v14 = 0;
    if (wk->next_motionID == 36)
      goto LABEL_19;
    goto LABEL_18;
  }
  v14 = 1;
  wk->status &= ~0x100u;
  wk->actwk->exStep = 0;
  if (wk->next_motionID != 36)
  {
LABEL_18:
    v14 = 1;
    wk->status &= ~0x100u;
    wk->actwk->exStep = 0;
  }
LABEL_19:
  v23 = gGurd_TimeOutCnt + 1;
  v24 = gGurd_TimeOutCnt - 64 < 0;
  gGurd_TimeOutCnt = v23;
  if (v24 == __OFSUB__(v23, 65))
    goto LABEL_26;
LABEL_23:
  v13 = v14 != 0;
  if (v23 < 13)
    goto LABEL_32;
  goto LABEL_28;
LABEL_26:
  v14 = 1;
  wk->status &= ~0x100u;
  wk->actwk->exStep = 0;
  goto LABEL_23;
LABEL_28:
  if (sBtlChkReJump(v11))
  {
    v13 = 1;
    wk->status &= ~0x100u;
    wk->actwk->exStep = 0;
  }
LABEL_32:
  Proc(wk);
  sBtlProc(wk);
  sBtlMVSupport(wk);
  UnitMV(wk);
  v31.x = x;
  v31.y = y;
  v31.z = z;
  v31.w = w;
  CheckMapHit(wk, v31);
  UnitMV_To_Basic(wk);
  if (v13)
  {
    ResetAction(wk);
    sBtlSetAction(wk, 2, 0);
    sBtlEndAction(wk);
  }
  return 1;
}

// 0x1ea9c00
static f32 BS_LASTB1_PuDis(SBTLUNIT_WORK *pu, SBTLUNIT_WORK *wk) {
  f32 x;
  f32 z;
  f32 v5;
  f32 v6;

  x = pu->pos.x;
  z = pu->pos.z;
  v5 = wk->pos.x;
  v6 = wk->pos.z;
  return sqrtf((f32)((f32)(v5 - x) * (f32)(v5 - x)) + (f32)((f32)(v6 - z) * (f32)(v6 - z)));
}

// 0x1ea9ca0
static f32 BS_LASTB1_PuDis2(SBTLUNIT_WORK *pu, SBTLUNIT_WORK *wk) {
  f32 x;
  f32 z;
  f32 v7;
  f32 v8;

  x = pu->pos.x;
  z = pu->pos.z;
  v7 = wk->pos.x;
  v8 = wk->pos.z;
  return (f32)(sBtlGetLenXZ(x, z, v7, v8) - pu->actaiwk->hit_area_r)
       - wk->actaiwk->hit_area_r;
}

// 0x1ea9d50
void sBtlBS_LASTB1_Init_Bstp(SBTLUNIT_WORK *wk) {
  SBTLACTION_WORK *actwk;
  s64 i;
  char *v6;

  actwk = wk->actwk;
  actwk->status = 74;
  actwk->exStep = 0;
  actwk->exWait = 0;
  gBstp_TomiOutCnt = 0;
  for (i = 0; ; ++i)
  {
    if (i >= SLODWORD(bs_se_stock->max_length))
      break;
    v6 = (char *)bs_se_stock + 4 * i;
    *((u32 *)v6 + 8) = -1;
  }
}

// 0x1ea9e60
bool sBtlBS_LASTB1_Action_Bstp(SBTLUNIT_WORK *wk, const sdfVector4_t *oldpos) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  SBTLUNIT_WORK *PChara;
  SBTLACTION_WORK *actwk;
  SBTLUNIT_WORK *v12;
  s32 exStep;
  s32 v15;
  bool v20;
  f32 v21;
  f32 v22;
  f32 v23;
  f32 v24;
  f32 v25;
  SBTLACTION_WORK *v27;
  f32 v28;
  s32 v33;
  SBTLACTION_WORK *v34;
  s32 exWait;
  s32 v36;
  sdfVector4_t v38;
  sdfVector4_t v39;

  w = oldpos->w;
  z = oldpos->z;
  y = oldpos->y;
  x = oldpos->x;
  PChara = sBtlGetPChara();
  actwk = wk->actwk;
  v12 = PChara;
  exStep = actwk->exStep;
  if (exStep != 1500)
  {
    if (exStep != 1000)
    {
      if (!exStep)
      {
        wk->flg |= 0x800u;
        actwk = wk->actwk;
        v15 = 0;
        gBstp_TomiOutCnt = 0;
        actwk->exStep = 1000;
        actwk->exWait = 60;
        goto LABEL_21;
      }
LABEL_19:
      v15 = 0;
      goto LABEL_21;
    }
    v21 = PChara->pos.x;
    v22 = PChara->pos.y;
    v23 = PChara->pos.z;
    v24 = PChara->pos.w;
    v38.x = v21;
    v38.y = v22;
    v38.z = v23;
    v38.w = v24;
    v25 = DirSet(wk, v38, 1);
    wk->mv_rotbk = v25;
    sBtlSetMotion(wk, 44, 0, 0, 0);
    v27 = wk->actwk;
    v28 = -10.0;
    v27->exStep = 1500;
    v27->exWait = 30;
LABEL_18:
    MoveSet(wk, v28);
    goto LABEL_19;
  }
  v33 = gBstp_TomiOutCnt + 1;
  v20 = gBstp_TomiOutCnt - 64 < 0;
  gBstp_TomiOutCnt = v33;
  if (v20 == __OFSUB__(v33, 65))
    goto LABEL_46;
  v34 = wk->actwk;
  if (wk->motionID != 44)
    goto LABEL_47;
  exWait = v34->exWait;
  if (exWait)
  {
    v36 = exWait - 1;
    v34->exWait = v36;
    if (v36 > 0)
      goto LABEL_19;
    v28 = 0.0;
    goto LABEL_18;
  }
  if (sBtlChkNowJump_OrAtk(v12))
  {
    goto LABEL_41;
  }
  wk->flg &= ~0x800u;
LABEL_41:
  if (!sBtlCheckMotionEnd(wk))
    goto LABEL_19;
LABEL_46:
  v34 = wk->actwk;
LABEL_47:
  v34->exStep = 0;
  v15 = 1;
  wk->flg &= ~0x800u;
LABEL_21:
  Proc(wk);
  sBtlProc(wk);
  sBtlMVSupport(wk);
  UnitMV(wk);
  v39.x = x;
  v39.y = y;
  v39.z = z;
  v39.w = w;
  CheckMapHit(wk, v39);
  UnitMV_To_Basic(wk);
  if (v15)
  {
    ResetAction(wk);
    sBtlSetAction(wk, 2, 0);
    sBtlEndAction(wk);
  }
  return 1;
}

// 0x1eaa230
void sBtlBS_LASTB1_Init_Quik(SBTLUNIT_WORK *wk) {
  SBTLACTION_WORK *actwk;
  s64 i;
  char *v7;

  actwk = wk->actwk;
  actwk->status = 75;
  actwk->exStep = 0;
  actwk->exWait = 0;
  for (i = 0; ; ++i)
  {
    if (i >= SLODWORD(bs_se_stock->max_length))
      break;
    v7 = (char *)bs_se_stock + 4 * i;
    *((u32 *)v7 + 8) = -1;
  }
}

// 0x1eaa330
bool sBtlBS_LASTB1_Action_Quik(SBTLUNIT_WORK *wk, const sdfVector4_t *oldpos) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  SBTLUNIT_WORK *PChara;
  SBTLACTION_WORK *actwk;
  SBTLUNIT_WORK *v12;
  s32 exStep;
  s32 v14;
  s32 v15;
  bool v16;
  f32 v18;
  f32 v19;
  f32 v20;
  f32 v21;
  f32 v22;
  f32 v23;
  SBTLACTION_WORK *v26;
  s32 v27;
  f32 v28;
  f32 v29;
  f32 v30;
  f32 v31;
  f32 v33;
  s32 v34;
  bool v35;
  f32 v36;
  f32 v37;
  f32 v38;
  f32 v39;
  f32 v40;
  sdfVector4_t *p_rot;
  f32 v43;
  f32 v44;
  f32 v45;
  f32 v46;
  f32 v48;
  SBTLACTION_WORK *v50;
  s32 v51;
  s32 v52;
  s32 v53;
  sdfVector4_t *v54;
  f32 v55;
  f32 v56;
  f32 v57;
  f32 v58;
  f32 v59;
  f32 PosToDir;
  f32 AtoB_LR;
  f32 v62;
  f32 v63;
  f32 Dir180;
  f32 v67;
  f32 v68;
  f32 v69;
  f32 v70;
  f32 RotToDir;
  sdfVector4_t *p_rotbk;
  f32 v75;
  f32 v76;
  f32 v78;
  SBTLACTION_WORK *v79;
  s32 v80;
  f32 v81;
  f32 v82;
  f32 v83;
  f32 v84;
  f32 v85;
  f32 v86;
  f32 v87;
  f32 v88;
  f32 v89;
  f32 v97;
  SBTLUNIT_WORK *v98;
  f32 v100;
  f32 v101;
  struct sdfVector4_t v102;
  f32 v103;
  f32 v105;
  f32 v106;
  f32 v107;
  sdfVector4_t v108;
  sdfVector4_t v109;
  sdfVector4_t v110;
  sdfVector4_t v111;
  sdfVector4_t v112;
  sdfVector4_t v113;
  sdfVector4_t v114;

  w = oldpos->w;
  z = oldpos->z;
  y = oldpos->y;
  x = oldpos->x;
  PChara = sBtlGetPChara();
  actwk = wk->actwk;
  v12 = PChara;
  exStep = actwk->exStep;
  if (exStep <= 1000)
  {
    if (exStep)
    {
      if (exStep != 1000)
        goto LABEL_122;
      v19 = PChara->pos.x;
      v20 = PChara->pos.y;
      v21 = PChara->pos.z;
      v22 = PChara->pos.w;
      v110.x = v19;
      v110.y = v20;
      v110.z = v21;
      v110.w = v22;
      v23 = DirSet(wk, v110, 1);
      wk->mv_rotbk = v23;
      wk->next_motion_not_hokan = 1;
      sBtlSetMotion(wk, 45, 0, 0, 0);
      MoveSet(wk, 50.0);
      v26 = wk->actwk;
      v14 = 0;
      v26->exStep = 1500;
      v27 = 38;
LABEL_154:
      v26->exWait = v27;
      goto LABEL_124;
    }
    v36 = PChara->pos.x;
    v37 = PChara->pos.y;
    v38 = PChara->pos.z;
    v39 = PChara->pos.w;
    v111.x = v36;
    v111.y = v37;
    v111.z = v38;
    v111.w = v39;
    v40 = DirSet(wk, v111, 1);
    wk->mv_rotbk = v40;
    FromEuler(0.0, v40 * 0.017453292, 0.0);
    p_rot = &wk->rot;
    *p_rot = vct_A;
    v67 = wk->rot.x;
    v68 = wk->rot.y;
    wk->rotbk = vct_A;
    v70 = wk->rot.z;
    v69 = wk->rot.w;
    v113.x = v67;
    v113.y = v68;
    v113.z = v70;
    v113.w = v69;
    RotToDir = sBtlGetRotToDir(v113);
    v26 = wk->actwk;
    v14 = 0;
    wk->front_deg = RotToDir;
    v52 = 1000;
LABEL_86:
    v26->exStep = v52;
    v27 = 60;
    goto LABEL_154;
  }
  v14 = 0;
  if (exStep <= 2000)
  {
    if (exStep != 1500)
    {
      if (exStep != 2000)
        goto LABEL_123;
      v28 = v12->pos.x;
      v29 = v12->pos.z;
      v30 = wk->pos.x;
      v31 = wk->pos.z;
      if ((f32)((f32)(sBtlGetLenXZ(v28, v29, v30, v31) - v12->actaiwk->hit_area_r) - wk->actaiwk->hit_area_r) >= 50.0)
        v33 = 20.0;
      else
        v33 = 0.0;
      MoveSet(wk, v33);
      v26 = wk->actwk;
      v34 = v26->exWait - 1;
      v35 = v26->exWait == 1;
      v26->exWait = v34;
      if (v34 < 0 || v35)
      {
        v14 = 0;
        v26->exStep = 2001;
        v27 = 10;
        goto LABEL_154;
      }
LABEL_122:
      v14 = 0;
LABEL_123:
      goto LABEL_124;
    }
    v55 = wk->rot.x;
    v56 = wk->rot.y;
    v54 = &wk->rot;
    v57 = wk->rot.z;
    v58 = wk->rot.w;
    v112.x = v55;
    v112.y = v56;
    v112.z = v57;
    v112.w = v58;
    v59 = sBtlGetRotToDir(v112);
    PosToDir = sBtlGetPosToDir(wk->pos.x, wk->pos.z, v12->pos.x, v12->pos.z);
    AtoB_LR = sBtlGetAtoB_LR(v59, PosToDir);
    if (AtoB_LR < -1.0)
      AtoB_LR = -1.0;
    if (AtoB_LR <= 1.0)
      v62 = AtoB_LR;
    else
      v62 = 1.0;
    v63 = sBtlGet360(v59 + v62);
    Dir180 = sBtlGetDir180(v63);
    wk->mv_rotbk = Dir180;
    FromEuler(0.0, Dir180 * 0.017453292, 0.0);
    *v54 = vct_A;
    p_rotbk = &wk->rotbk;
    v75 = wk->rot.z;
    v76 = wk->rot.w;
    wk->hstatus |= 0x1000u;
    *p_rotbk = vct_A;
    v108.x = wk->rot.x;
    v108.y = wk->rot.y;
    v108.z = v75;
    v108.w = v76;
    v78 = sBtlGetRotToDir(v108);
    v79 = wk->actwk;
    wk->front_deg = v78;
    v80 = v79->exWait - 1;
    v35 = v79->exWait == 1;
    v79->exWait = v80;
    if (v80 < 0 || v35)
    {
      wk->next_motion_not_hokan = 1;
      sBtlSetMotion(wk, 47, 0, 0, 0);
      v97 = 15.0;
      v98 = wk;
      goto LABEL_153;
    }
    v106 = PosToDir;
    v107 = v59;
    v81 = v12->pos.x;
    v82 = v12->pos.z;
    v83 = wk->pos.x;
    v84 = wk->pos.z;
    v85 = (f32)(sBtlGetLenXZ(v81, v82, v83, v84) - v12->actaiwk->hit_area_r)
        - wk->actaiwk->hit_area_r;
    if (v85 >= 200.0)
      goto LABEL_122;
    v86 = sBtlGetAtoB_LR(v107, v106);
    if (v86 < -10.0)
      v86 = -10.0;
    if (v86 <= 10.0)
      v87 = v86;
    else
      v87 = 10.0;
    v88 = sBtlGet360(v107 + v87);
    v89 = sBtlGetDir180(v88);
    wk->mv_rotbk = v89;
    FromEuler(0.0, v89 * 0.017453292, 0.0);
    *v54 = vct_A;
    v100 = wk->rot.z;
    v101 = wk->rot.w;
    v102 = vct_A;
    wk->hstatus |= 0x1000u;
    *p_rotbk = v102;
    v109.x = wk->rot.x;
    v109.y = wk->rot.y;
    v109.z = v100;
    v109.w = v101;
    v103 = sBtlGetRotToDir(v109);
    wk->front_deg = v103;
    wk->next_motion_not_hokan = 1;
    sBtlSetMotion(wk, 47, 0, 0, 0);
    if (v85 >= 50.0)
      v105 = 20.0;
    else
      v105 = 0.0;
    v98 = wk;
    v97 = v105;
LABEL_153:
    MoveSet(v98, v97);
    v26 = wk->actwk;
    v14 = 0;
    v26->exStep = 2000;
    v27 = 20;
    goto LABEL_154;
  }
  if (exStep == 2001)
  {
    v43 = v12->pos.x;
    v44 = v12->pos.z;
    v45 = wk->pos.x;
    v46 = wk->pos.z;
    if ((f32)((f32)(sBtlGetLenXZ(v43, v44, v45, v46) - v12->actaiwk->hit_area_r) - wk->actaiwk->hit_area_r) >= 50.0)
      v48 = 15.0;
    else
      v48 = 0.0;
    MoveSet(wk, v48);
    v50 = wk->actwk;
    v51 = v50->exWait - 1;
    v35 = v50->exWait == 1;
    v50->exWait = v51;
    if (v51 >= 0 && !v35)
      goto LABEL_122;
    MoveSet(wk, 0.0);
    v26 = wk->actwk;
    v14 = 0;
    v52 = 2002;
    goto LABEL_86;
  }
  if (exStep == 2002)
  {
    v53 = actwk->exWait - 1;
    v16 = actwk->exWait - 2 < 0;
    actwk->exWait = v53;
    if (v16 != __OFSUB__(v53, 1))
      goto LABEL_92;
    goto LABEL_90;
  }
  if (exStep != 3000)
    goto LABEL_123;
  v15 = actwk->exWait - 1;
  v16 = actwk->exWait - 14 < 0;
  actwk->exWait = v15;
  if (v16 == __OFSUB__(v15, 13))
  {
    v18 = 20.0;
    goto LABEL_89;
  }
  if (v15 >= 9)
  {
    v18 = 10.0;
  }
  else
  {
    if (v15 >= 5)
      v18 = 5.0;
    else
      v18 = 0.0;
  }
LABEL_89:
  MoveSet(wk, v18);
  if (sBtlCheckMotionEnd(wk))
    goto LABEL_91;
  goto LABEL_122;
LABEL_90:
  if (!sBtlCheckMotionEnd(wk))
    goto LABEL_122;
LABEL_91:
  actwk = wk->actwk;
LABEL_92:
  v14 = 1;
  actwk->exStep = 0;
  Proc(wk);
  goto LABEL_125;
LABEL_124:
  Proc(wk);
LABEL_125:
  sBtlProc(wk);
  sBtlMVSupport(wk);
  UnitMV(wk);
  v114.x = x;
  v114.y = y;
  v114.z = z;
  v114.w = w;
  CheckMapHit(wk, v114);
  UnitMV_To_Basic(wk);
  if (v14)
  {
    ResetAction(wk);
    sBtlSetAction(wk, 2, 0);
    sBtlEndAction(wk);
  }
  return 1;
}

// 0x1eaaed0
void sBtlBS_LASTB1_Action_Req(void) {
  SBTLUNIT_WORK *v3;
  SBTLUNIT_WORK *v4;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 playerID;
  SBTLUNIT_WORK *v9;
  SBTLACTION_WORK *actwk;
  u32 status;
  s32 v12;
  s32 use_skillid;

  if (wk->encountno != 58)
    return;
  v3 = sBtlSearchDeivl(257);
  if (v3)
  {
    v4 = v3;
    UnitMng = wk->UnitMng;
    playerID = wk->playerID;
    v9 = sBtlSearchUnit_ID(UnitMng, playerID);
    if (sBtlCheckIsDamage(v9))
      goto LABEL_26;
    if (!sBtlCheckMove_BadStatus(v9))
      goto LABEL_26;
    if (!IsSceanStop())
    {
      actwk = v4->actwk;
      status = actwk->status;
      if (status != 68)
      {
        if ((v4->aiwk->scrflag & 0x10000) == 0)
        {
          v4->kaya_skill_req = 1;
          return;
        }
        if (status == 3)
        {
          use_skillid = actwk->use_skillid;
          v12 = 1;
          if ((u32)(use_skillid - 453) < 5 || use_skillid == 74)
          {
LABEL_27:
            v4->kaya_skill_req = v12;
            return;
          }
        }
      }
    }
LABEL_26:
    v12 = 0;
    goto LABEL_27;
  }
}

// 0x1eab2a0
void sBtlBS_LASTB1_Action_Set(SBTLUNIT_WORK *wk) {
  SBTLUNIT_WORK *PChara;
  SBTLUNIT_WORK *v4;
  f32 x;
  f32 z;
  f32 v8;
  f32 v9;
  void *Instance;
  s32 HitCount;
  s32 max_length;
  s64 v14;
  s32 v16;

  if (wk)
  {
    if (wk->para->devilid == 257)
    {
      PChara = sBtlGetPChara();
      if (wk->kaya_skill_req)
      {
        v4 = PChara;
        if (wk->mode != 11)
        {
          x = v4->pos.x;
          z = v4->pos.z;
          v8 = wk->pos.x;
          v9 = wk->pos.z;
          if (sqrtf((f32)((f32)(v8 - x) * (f32)(v8 - x)) + (f32)((f32)(v9 - z) * (f32)(v9 - z))) <= 300.0 && wk->actwk->status - 1 <= 2)
          {
            Instance = get_Instance(0);
            HitCount = GetHitCount(Instance, 0);
            max_length = BS_LASTB1_Action_Tbl->max_length;
            if (HitCount < max_length)
            {
LABEL_20:
              v14 = BS_LASTB1_Action_Tbl[HitCount][0];
              if ((u32)v14 != -1 && (u32)sub_1905740(100, 0) < v14)
              {
                v16 = BS_LASTB1_Action_Tbl[HitCount][1];
                if (v16)
                {
                  sBtlSetSkillTarget(wk, v16, 0x20000u);
                  wk->kaya_skill_req = 0;
                }
              }
              return;
            }
            max_length = BS_LASTB1_Action_Tbl->max_length;
            HitCount = max_length - 1;
            goto LABEL_20;
          }
        }
      }
    }
  }
}

// 0x1eab500
void sBtlBS_MATORY_Init_Nenr(SBTLUNIT_WORK *wk) {
  s32 encountno;
  s32 v7;
  SBTLUNIT_WORK *v8;
  SBTLACTION_WORK *actwk;
  SBTLAI_WORK *aiwk;
  s32 scrStep2;
  s32 v12;
  s32 v13;

  encountno = wk->encountno;
  if (encountno == 43)
    v7 = 262;
  else
    v7 = 300;
  v8 = sBtlSearchDeivl(v7);
  actwk = wk->actwk;
  actwk->status = 65;
  aiwk = v8->aiwk;
  actwk->exStep = 0;
  actwk->exWait = 0;
  actwk->exAutoDead = 0;
  scrStep2 = aiwk->scrStep2;
  if (scrStep2 == 30)
    v12 = 1546;
  else
    v12 = 1544;
  if (scrStep2 == 20)
    v13 = 1545;
  else
    v13 = v12;
  actwk->use_skillid = v13;
}

// 0x1eab620
bool sBtlBS_MATORY_Action_Nenr(SBTLUNIT_WORK *wk, const sdfVector4_t *oldpos) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  SBTLUNIT_WORK *PChara;
  s32 v11;
  SBTLUNIT_WORK *v13;
  SBTLUNIT_WORK *v15;
  SBTLACTION_WORK *actwk;
  s32 exStep;
  void *Instance;
  s32 v23;
  bool v24;
  void *v25;
  void *v26;
  void *v27;
  void *v28;
  s32 v32;
  bool v33;
  s32 v35;
  s32 v36;
  s32 v37;
  SBTLACTION_WORK *v38;
  s32 v39;
  s32 scrStep2;
  s32 v43;
  s32 v44;
  SBTLACTION_WORK *v45;
  s32 v46;
  s32 v47;
  s32 v48;
  u32 status;
  s32 use_skillid;
  void *v53;
  SBTLACTION_WORK *v54;
  SBTLACTION_WORK *v57;
  f32 *v59;
  f32 v60;
  f32 v61;
  f32 v62;
  s32 v64;
  f32 v65;
  f32 v66;
  f32 v67;
  f32 v68;
  SBTLACTION_WORK *v70;
  SBTLACTION_WORK *v72;
  sdfVector4_t v75;
  sdfVector4_t v76;

  w = oldpos->w;
  z = oldpos->z;
  y = oldpos->y;
  x = oldpos->x;
  PChara = sBtlGetPChara();
  if (wk->encountno == 43)
    v11 = 262;
  else
    v11 = 300;
  v13 = sBtlSearchDeivl(v11);
  v15 = sBtlSearchDeivl(323);
  actwk = wk->actwk;
  exStep = actwk->exStep;
  if (exStep <= 2500)
  {
    if (exStep > 1000)
    {
      if (exStep == 1500)
      {
        v48 = actwk->exWait + 1;
        status = v13->actwk->status;
        actwk->exWait = v48;
        if (status == 64 || v48 < 60)
          goto LABEL_109;
        v46 = 2000;
        goto LABEL_108;
      }
      if (exStep == 2000)
      {
        use_skillid = actwk->use_skillid;
        if (use_skillid == 1545)
        {
          sBtlSetMotion(wk, 34, 0, 0, 1);
          v57 = wk->actwk;
          v57->exStep = 2800;
          v57->exWait = 0;
          BS_MATORY_SE(wk, 28);
          goto LABEL_109;
        }
        if (use_skillid != 1544)
        {
          v59 = v15;
          sBtlSetMotion(wk, 35, 0, 0, 1);
          v60 = wk->pos.x;
          v61 = wk->pos.y;
          v62 = wk->pos.z;
          wk->actwk->exStep = 3000;
          Add(v60, v61, v62, 0);
          v64 = wk->actwk->use_skillid;
          v65 = v59[41];
          v66 = v59[42];
          v67 = v59[43];
          v68 = v59[44];
          v75.x = v65;
          v75.y = v66;
          v75.z = v67;
          v75.w = v68;
          BS_MATORY_Explosion_Hit(v13, PChara, v64, v75);
          goto LABEL_109;
        }
        actwk = wk->actwk;
        laser_se_wait = 1;
        *(u64 *)&laser_cnt = 0x1E00000000LL;
        v46 = 2500;
        goto LABEL_108;
      }
      if (exStep != 2500)
        goto LABEL_109;
      Instance = get_Instance(0);
      RotateGun(Instance, 0);
      if (laser_se_wait)
      {
        laser_se_wait = laser_se_wait - 1;
      }
      v23 = laser_wait - 1;
      v24 = laser_wait == 1;
      laser_wait = v23;
      if (v23 >= 0 && !v24)
        goto LABEL_109;
      laser_wait = 7;
      v25 = get_Instance(0);
      SetMuzzleFlashPos(v25, 0);
      v26 = get_Instance(0);
      SetMuzzleFlashRot(v26, 0);
      v27 = get_Instance(0);
      Play(v27, 6, 0);
      v28 = get_Instance(0);
      LaserStart(v28, 0);
      v32 = laser_cnt + 1;
      v33 = laser_cnt - 29 < 0;
      laser_cnt = v32;
      if (v33 == __OFSUB__(v32, 30))
      {
        sBtlSetMotion(wk, 34, 0, 0, 1);
        v70 = wk->actwk;
        v70->exStep = 2800;
        v70->exWait = 0;
        BS_MATORY_SE(wk, 28);
        if (laser_se_wait)
          goto LABEL_109;
        goto LABEL_101;
      }
      if (laser_se_wait)
        goto LABEL_109;
LABEL_101:
      BS_RASUPU_SE(v13, 26);
      laser_se_wait = 240;
      goto LABEL_109;
    }
    if (!exStep)
    {
      scrStep2 = v13->aiwk->scrStep2;
      if (scrStep2 == 30)
        v43 = 1546;
      else
        v43 = 1544;
      if (scrStep2 == 20)
        v44 = 1545;
      else
        v44 = v43;
      actwk->use_skillid = v44;
      sBtlSetMotion(wk, 33, 0, 0, 1);
      v45 = wk->actwk;
      v45->exStep = 1000;
      v45->exWait = 1;
      goto LABEL_109;
    }
    if (exStep != 1000)
      goto LABEL_109;
    v36 = actwk->exWait - 1;
    v24 = actwk->exWait == 1;
    actwk->exWait = v36;
    if (v36 >= 0 && !v24)
      goto LABEL_109;
    v37 = actwk->use_skillid;
    switch (v37)
    {
      case 1546:
        v72 = v13->actwk;
        v72->exStep = 4000;
        v72->exWait = 60;
        break;
      case 1545:
        v38 = v13->actwk;
        v39 = 3000;
        goto LABEL_106;
      case 1544:
        v38 = v13->actwk;
        v39 = 2000;
LABEL_106:
        v38->exStep = v39;
        break;
    }
    v46 = 1500;
    actwk->exWait = 0;
    goto LABEL_108;
  }
  if ((u32)exStep > 0xB54)
  {
    if (exStep != 3000)
    {
      if (exStep != 3100)
      {
        if (exStep != 10000)
          goto LABEL_109;
        goto LABEL_15;
      }
      v47 = actwk->exWait - 1;
      v24 = actwk->exWait == 1;
      actwk->exWait = v47;
      if (v47 < 0 || v24)
      {
        actwk->exStep = 10000;
        wk->vstatus |= 0x1000u;
      }
      goto LABEL_109;
    }
    if (!sBtlCheckMotionEnd(wk))
      goto LABEL_109;
    actwk = wk->actwk;
    actwk->exWait = 120;
    v46 = 3100;
LABEL_108:
    actwk->exStep = v46;
    goto LABEL_109;
  }
  if (exStep == 2800)
  {
    ++actwk->exWait;
    if (sBtlCheckMotionEnd(wk))
      goto LABEL_82;
    goto LABEL_9000;
    if (sBtlCheckMotionEnd(wk))
    {
LABEL_82:
      v53 = get_Instance(0);
      Stop(v53, 0, 0);
      v54 = wk->actwk;
      v54->exStep = 2900;
      v54->exWait = 30;
      sBtlSetFade(wk, 2, 0, 0, 16);
      sBtlSetSkill_EffectData(wk, 426, 0);
      goto LABEL_109;
    }
LABEL_9000:
    if (wk->actwk->exWait < 120)
      goto LABEL_109;
    goto LABEL_82;
  }
  if (exStep == 2900)
  {
    v35 = actwk->exWait - 1;
    v24 = actwk->exWait == 1;
    actwk->exWait = v35;
    if (v35 < 0 || v24)
    {
      actwk->exStep = 10000;
      if (actwk->use_skillid == 1544)
LABEL_15:
        wk->mode = 9;
    }
  }
LABEL_109:
  Proc(wk);
  sBtlProc(wk);
  sBtlMVSupport(wk);
  UnitMV(wk);
  v76.x = x;
  v76.y = y;
  v76.z = z;
  v76.w = w;
  CheckMapHit(wk, v76);
  UnitMV_To_Basic(wk);
  return 1;
}

// 0x1eabf40
static void BS_MATORY_Explosion_Hit(SBTLUNIT_WORK *wk, SBTLUNIT_WORK *user, SKLID skillid, const sdfVector4_t *beffPos) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  f32 v15;
  f32 v16;
  f32 v17;
  f32 v18;
  SBTLUNIT_WORK *Nakama;
  SBTLUNIT_WORK *v23;
  SBTLUNIT_WORK *v25;
  SBTLUNIT_WORK *v27;
  s64 i;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  f32 v33;
  f32 v34;
  f32 v35;
  f32 v36;
  sdfVector4_t v37;
  sdfVector4_t v38;
  sdfVector4_t v39;
  sdfVector4_t v40;
  sdfVector4_t v41;
  sdfVector4_t v42;

  w = beffPos->w;
  z = beffPos->z;
  y = beffPos->y;
  x = beffPos->x;
  if (wk->cmbSkl->bRun)
    return;
  if (sBtlCheckSetsuma())
    return;
  if (!IsSceanStop())
  {
    if (wk->mode != 5)
    {
      v37.x = x;
      v37.y = y;
      v37.z = z;
      v37.w = w;
      if (!BS_MATORY_Explosion_HitSub(user, v37))
        goto LABEL_31;
      if (!wk)
        goto LABEL_31;
      goto LABEL_27;
      if (!wk)
      {
LABEL_31:
        if (!wk->NakamaShugouOn)
        {
          Nakama = sBtlGetNakama(0);
          v39.x = x;
          v39.y = y;
          v39.z = z;
          v39.w = w;
          if (BS_MATORY_Explosion_HitSub(Nakama, v39))
          {
            v23 = sBtlGetNakama(0);
            sBtlBS_MATORY_Dmg(wk, v23, skillid);
          }
          v25 = sBtlGetNakama(1);
          v40.x = x;
          v40.y = y;
          v40.z = z;
          v40.w = w;
          if (BS_MATORY_Explosion_HitSub(v25, v40))
          {
            v27 = sBtlGetNakama(1);
            sBtlBS_MATORY_Dmg(wk, v27, skillid);
          }
        }
        for (i = 0; ; ++i)
        {
          UnitMng = wk->UnitMng;
          if (i >= UnitMng->number)
            return;
          pUnit = UnitMng->pUnitL[i]->pUnit;
          if (!pUnit)
            continue;
          if (!CheckLiveTarget(pUnit))
            continue;
          if ((pUnit->side & 2) != 0 && pUnit->para->devilid != 323 && (pUnit->status & 0x4000000) == 0)
          {
            v42.x = x;
            v42.y = y;
            v42.z = z;
            v42.w = w;
            if (BS_MATORY_Explosion_HitSub(pUnit, v42))
              break;
          }
LABEL_48:
          ;
        }
        if (!wk)
          goto LABEL_48;
        v33 = pUnit->pos.x;
        v34 = pUnit->pos.y;
        v35 = pUnit->pos.z;
        v36 = pUnit->pos.w;
        v41.x = v33;
        v41.y = v34;
        v41.z = v35;
        v41.w = v36;
        SetDamageProc(pUnit, wk, skillid, v41);
        goto LABEL_48;
      }
LABEL_27:
      if (user)
      {
        v15 = user->pos.x;
        v16 = user->pos.y;
        v17 = user->pos.z;
        v18 = user->pos.w;
        v38.x = v15;
        v38.y = v16;
        v38.z = v17;
        v38.w = v18;
        SetDamageProc(user, wk, skillid, v38);
      }
      goto LABEL_31;
    }
  }
}

// 0x1eac590
static bool BS_MATORY_Explosion_HitSub(SBTLUNIT_WORK *user, const sdfVector4_t *beffPos) {
  f32 z;
  f32 x;
  u16 major;
  s32 minor;
  VISUALDATA_WORK *VisualData;
  f32 v10;
  f32 v11;
  f32 v12;
  f32 v13;

  z = beffPos->z;
  x = beffPos->x;
  if (!user || user->damagecnt > 0 || user->para->now->hp < 1)
    return 0;
  major = user->major;
  minor = user->minor;
  VisualData = sBtlGetVisualData(major, minor);
  v10 = user->pos.x;
  v11 = user->pos.z;
  v12 = VisualData->nml->cylinder * 0.5;
  v13 = v12 + 300.0;
  return sqrtf((f32)((f32)(x - v10) * (f32)(x - v10)) + (f32)((f32)(z - v11) * (f32)(z - v11))) < v13;
}

// 0x1eac6f0
void sBtlBS_MATORY_Dmg(SBTLUNIT_WORK *wk, SBTLUNIT_WORK *user, SKLID skillid) {
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  sdfVector4_t v11;

  if (wk && user)
  {
    x = user->pos.x;
    y = user->pos.y;
    z = user->pos.z;
    w = user->pos.w;
    v11.x = x;
    v11.y = y;
    v11.z = z;
    v11.w = w;
    SetDamageProc(user, wk, skillid, v11);
  }
}

// 0x1eaca50
void sBtlBS_MISHAK_Init_Hiru(SBTLUNIT_WORK *wk) {
  SBTLACTION_WORK *actwk;
  s64 i;
  char *v7;

  actwk = wk->actwk;
  actwk->status = 66;
  actwk->exStep = 0;
  actwk->exWait = 120;
  for (i = 0; ; ++i)
  {
    if (i >= SLODWORD(bs_se_stock->max_length))
      break;
    v7 = (char *)bs_se_stock + 4 * i;
    *((u32 *)v7 + 8) = -1;
  }
}

// 0x1eacb50
bool sBtlBS_MISHAK_Action_Hiru(SBTLUNIT_WORK *wk, const sdfVector4_t *oldpos) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  SBTLACTION_WORK *actwk;
  s32 exStep;
  s32 v11;
  bool v12;
  s32 v13;
  bool v14;
  SBTLACTION_WORK *v16;
  s32 v17;
  s32 v19;
  bool v20;
  SBTLACTION_WORK *v21;
  void *Instance;
  s32 exWait;
  s32 v25;
  SBTLACTION_WORK *v26;
  void *v27;
  void *v28;
  s32 v29;
  SBTLACTION_WORK *v30;
  s32 v31;
  __int128 v32;
  s32 *para;
  s32 v34;
  sdfVector4_t v40;

  w = oldpos->w;
  z = oldpos->z;
  y = oldpos->y;
  x = oldpos->x;
  sBtlGetPChara();
  if (!sBtlHDloadChk(426))
    return 1;
  actwk = wk->actwk;
  exStep = actwk->exStep;
  if (exStep <= 20)
  {
    if (!exStep)
    {
      sBtlSetMotion(wk, 0, 0, 0, 1);
      wk->status |= 0x4001u;
      *(u64 *)&v32 = 0x100000001000LL;
      *((u64 *)&v32 + 1) = 0x100000001000LL;
      para = wk->para->aisyo->para;
      *(_OWORD *)para = v32;
      *(_OWORD *)&para[4] = v32;
      *(_OWORD *)&para[8] = v32;
      *(_OWORD *)&para[12] = v32;
      sBtlSetFade(wk, 2, 0, 0, 16);
      sBtlSetSkill_EffectData(wk, 426, 0);
      v30 = wk->actwk;
      v17 = 0;
      v30->exStep = 10;
      v31 = 60;
      goto LABEL_71;
    }
    if (exStep == 10)
    {
      v34 = actwk->exWait - 1;
      v20 = actwk->exWait == 1;
      actwk->exWait = v34;
      if (v34 >= 0 && !v20)
        goto LABEL_59;
      *(u64 *)&wk->pos.y = 0;
      wk->pos.x = 0.0;
      sBtlSetFade(wk, 1, 0, 0, 4);
      sBtlSetSkill_EffectData(wk, 426, 0);
      v30 = wk->actwk;
      v17 = 0;
      v30->exStep = 20;
      v31 = 30;
      goto LABEL_71;
    }
    if (exStep != 20)
      goto LABEL_59;
    v19 = actwk->exWait - 1;
    v20 = actwk->exWait == 1;
    actwk->exWait = v19;
    if (v19 >= 0 && !v20)
      goto LABEL_59;
    sBtlSetMotion(wk, 32, 0, 0, 1);
    v21 = wk->actwk;
    v21->exStep = 1000;
    v21->exWait = 153;
    wk->status &= 0xFFFFBFFE;
    Instance = get_Instance(0);
    Play(Instance, 0, 0);
    BS_MISHAK_SE(wk, 19);
    v17 = 0;
    goto LABEL_60;
  }
  if (exStep == 1000)
  {
    exWait = actwk->exWait;
    v12 = __OFSUB__(exWait, 1);
    v25 = exWait - 1;
    if (v25 < 0 == v12)
      actwk->exWait = v25;
    if (!sBtlCheckMotionEnd(wk) && wk->actwk->exWait)
    {
LABEL_59:
      v17 = 0;
      goto LABEL_60;
    }
    sBtlSetMotion(wk, 33, 0, 0, 1);
    v26 = wk->actwk;
    v26->exStep = 1100;
    v26->exWait = 10;
    dds3SetQuake(90, 0xFAu);
    v27 = get_Instance(0);
    HirukoStart(v27, 0);
    v28 = get_Instance(0);
    Play(v28, 1, 0);
    v17 = 0;
    goto LABEL_60;
  }
  if (exStep == 1100)
  {
    v29 = actwk->exWait - 1;
    v20 = actwk->exWait == 1;
    actwk->exWait = v29;
    if (v29 >= 0 && !v20)
      goto LABEL_59;
    sBtlSetMotion(wk, 34, 0, 0, 0);
    v30 = wk->actwk;
    v17 = 0;
    v30->exStep = 1200;
    v31 = 112;
LABEL_71:
    v30->exWait = v31;
    goto LABEL_60;
  }
  if (exStep != 1200)
    goto LABEL_59;
  v11 = actwk->exWait;
  v12 = __OFSUB__(v11, 1);
  v13 = v11 - 1;
  if (v13 < 0 == v12)
    actwk->exWait = v13;
  v14 = sBtlCheckMotionEnd(wk);
  v16 = wk->actwk;
  if (!v14)
  {
    if (v16->exWait)
      goto LABEL_59;
  }
  v16->exStep = 10000;
  v16->exWait = 60;
  wk->status &= 0xFFFFBFFE;
  sBtlNBS_AisyoSet(wk, 0);
  sBtlSetWinceStop(wk, 0);
  v17 = 1;
LABEL_60:
  Proc(wk);
  sBtlProc(wk);
  sBtlMVSupport(wk);
  UnitMV(wk);
  v40.x = x;
  v40.y = y;
  v40.z = z;
  v40.w = w;
  CheckMapHit(wk, v40);
  UnitMV_To_Basic(wk);
  if (v17)
  {
    ResetAction(wk);
    sBtlSetAction(wk, 2, 0);
    sBtlEndAction(wk);
  }
  return 1;
}

// 0x1ead320
void sBtlBS_MISHAK_Hit(SBTLUNIT_WORK *wk, SKLID skillid, const sdfVector4_t *beffPos) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  SBTLUNIT_WORK *PChara;
  SBTLUNIT_WORK *v17;
  sdatUnitWork_t *para;
  SBTLUNIT_WORK *Nakama;
  SBTLUNIT_WORK *v24;
  sdfVector4_t v27;
  sdfVector4_t v28;
  sdfVector4_t v29;

  w = beffPos->w;
  z = beffPos->z;
  y = beffPos->y;
  x = beffPos->x;
  if (wk->cmbSkl->bRun)
    return;
  if (sBtlCheckSetsuma())
    return;
  if (wk->enemy_zenmetu)
    return;
  if (!IsSceanStop())
  {
    if (wk->mode != 5)
    {
      sBtlGetPChara();
      PChara = sBtlGetPChara();
      v27.x = x;
      v27.y = y;
      v27.z = z;
      v27.w = w;
      if (BS_MISHAK_HitSub(sBtlAction, PChara, skillid, v27))
      {
        BS_MISHAK_Dmg(wk, PChara, skillid);
LABEL_25:
        if (wk->NakamaShugouOn)
          return;
LABEL_31:
        v17 = sBtlGetPChara();
        if (v17)
        {
          para = v17->para;
          if (para)
          {
            if (para->now->hp >= 1)
            {
              Nakama = sBtlGetNakama(0);
              v28.x = x;
              v28.y = y;
              v28.z = z;
              v28.w = w;
              if (BS_MISHAK_HitSub(sBtlAction, Nakama, skillid, v28))
              {
                BS_MISHAK_Dmg(wk, Nakama, skillid);
              }
              v24 = sBtlGetNakama(1);
              v29.x = x;
              v29.y = y;
              v29.z = z;
              v29.w = w;
              if (BS_MISHAK_HitSub(sBtlAction, v24, skillid, v29))
              {
                BS_MISHAK_Dmg(wk, v24, skillid);
              }
            }
          }
        }
        return;
      }
      else
      {
        goto LABEL_25;
      }
      if (wk->NakamaShugouOn)
        return;
      goto LABEL_31;
    }
  }
}

// 0x1ead670
static bool BS_MISHAK_HitSub(SBTLUNIT_WORK *wk, SBTLUNIT_WORK *pu, SKLID skillid, const sdfVector4_t *beffPos) {
  f32 z;
  f32 x;
  sdatUnitWork_t *para;
  u16 major;
  s32 minor;
  VISUALDATA_WORK *VisualData;
  f32 yuka_cylinder_local;
  f32 v17;
  f32 v18;
  f32 v19;
  f32 v20;

  z = beffPos->z;
  x = beffPos->x;
  if (!pu)
    return 0;
  para = pu->para;
  if (!para || pu->damagecnt > 0 || pu->yuka_damagecnt > 0 || para->now->hp < 1)
    return 0;
  major = pu->major;
  minor = pu->minor;
  VisualData = sBtlGetVisualData(major, minor);
  if (skillid == 1554)
  {
    if ((pu->flg & 0x3C0802) != 0)
      return 0;
    yuka_cylinder_local = yuka_cylinder;
  }
  else
  {
    yuka_cylinder_local = bomb_cylinder;
    if (skillid == 1553)
    {
      if ((pu->flg & 0x3C0802) != 0)
        return 0;
    }
    else
    {
      z = 0.0;
      x = 0.0;
    }
  }
  v17 = pu->pos.x;
  v18 = pu->pos.z;
  v19 = VisualData->nml->cylinder * 0.5;
  v20 = yuka_cylinder_local + v19;
  return sqrtf((f32)((f32)(x - v17) * (f32)(x - v17)) + (f32)((f32)(z - v18) * (f32)(z - v18))) < v20;
}

// 0x1ead970
static bool BS_MISHAK_HitKaihi(SBTLUNIT_WORK *wk, SBTLUNIT_WORK *pu) {
  return (pu->flg & 0x3C0802) == 0;
}

// 0x1ead870
static void BS_MISHAK_Dmg(SBTLUNIT_WORK *wk, SBTLUNIT_WORK *pu, SKLID skillid) {
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  sdfVector4_t v12;

  if (wk && pu)
  {
    x = pu->pos.x;
    y = pu->pos.y;
    z = pu->pos.z;
    w = pu->pos.w;
    v12.x = x;
    v12.y = y;
    v12.z = z;
    v12.w = w;
    SetDamageProc(pu, wk, skillid, v12);
    if (skillid == 1554)
      pu->yuka_damagecnt = pu->damagecnt;
    BS_MISHAK_SE(pu, 21);
  }
}

// 0x1ead990
void sBtlBS_MISHAK_Action_Hiru_Cancel(void) {
  s32 encountno;
  s32 v3;
  SBTLUNIT_WORK *UnitFromDevilID;
  SBTLUNIT_WORK *v6;

  encountno = wk->encountno;
  if (encountno == 57)
  {
    v3 = 310;
    goto LABEL_6;
  }
  if (encountno != 41)
    return;
  v3 = 267;
LABEL_6:
  UnitFromDevilID = sBtlGetUnitFromDevilID(v3);
  if (!UnitFromDevilID)
    return;
  v6 = UnitFromDevilID;
  if (UnitFromDevilID->actwk->status == 66)
  {
    UnitFromDevilID->status &= 0xFFFFBFFE;
    if ((UnitFromDevilID->vstatus & 0x403) != 0)
    {
      sBtlFadeProc(v6);
      if ((v6->vstatus & 0x403) != 0)
      {
        sBtlFadeProc(v6);
        if ((v6->vstatus & 0x403) != 0)
        {
          sBtlFadeProc(v6);
          if ((v6->vstatus & 0x403) != 0)
          {
            sBtlFadeProc(v6);
            if ((v6->vstatus & 0x403) != 0)
            {
              sBtlFadeProc(v6);
              if ((v6->vstatus & 0x403) != 0)
              {
                sBtlFadeProc(v6);
                if ((v6->vstatus & 0x403) != 0)
                {
                  sBtlFadeProc(v6);
                  if ((v6->vstatus & 0x403) != 0)
                  {
                    sBtlFadeProc(v6);
                    if ((v6->vstatus & 0x403) != 0)
                    {
                      sBtlFadeProc(v6);
                      if ((v6->vstatus & 0x403) != 0)
                      {
                        sBtlFadeProc(v6);
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
    sBtlSetFade(v6, 1, 0, 0, 128);
    if ((v6->vstatus & 0x403) != 0)
    {
      sBtlFadeProc(v6);
      if ((v6->vstatus & 0x403) != 0)
      {
        sBtlFadeProc(v6);
      }
    }
    sBtlNBS_AisyoSet(v6, 0);
    sBtlSetWinceStop(v6, 0);
  }
}

// 0x1eadd40
void sBtlBS_MISHAK_Action_Hiru_DamageMotion(SBTLUNIT_WORK *wk) {
  s32 devilid;

  devilid = (u16)wk->para->devilid;
  if (devilid == 310 || devilid == 267)
  {
    wk->status &= 0xFFFFBFFE;
    sBtlNBS_AisyoSet(wk, 0);
  }
}

// 0x1eaddf0
void sBtlBS_MUNAKA_Init_Imad(SBTLUNIT_WORK *wk) {
  SBTLACTION_WORK *actwk;
  s64 i;
  char *v6;

  actwk = wk->actwk;
  actwk->status = 67;
  actwk->exStep = 0;
  actwk->exWait = 1;
  EventFlag = 0;
  for (i = 0; ; ++i)
  {
    if (i >= SLODWORD(bs_se_stock->max_length))
      break;
    v6 = (char *)bs_se_stock + 4 * i;
    *((u32 *)v6 + 8) = -1;
  }
}

// 0x1eadf00
void sBtlBS_MUNAKA_Init_Imad_Restart(SBTLUNIT_WORK *wk) {
  SBTLACTION_WORK *actwk;
  s64 i;
  char *v6;

  actwk = wk->actwk;
  actwk->use_skillid = 1549;
  actwk->status = 67;
  actwk->exStep = 4000;
  actwk->exWait = 1;
  EventFlag = 0;
  for (i = 0; ; ++i)
  {
    if (i >= SLODWORD(bs_se_stock->max_length))
      break;
    v6 = (char *)bs_se_stock + 4 * i;
    *((u32 *)v6 + 8) = -1;
  }
}

// 0x1eae020
bool sBtlBS_MUNAKA_Action_Imad(SBTLUNIT_WORK *wk, const sdfVector4_t *oldpos) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  SBTLUNIT_WORK *PChara;
  SBTLACTION_WORK *actwk;
  s32 exStep;
  void *v13;
  SBTLACTION_WORK *v14;
  s32 v16;
  SBTLACTION_WORK *v19;
  s32 v20;
  s32 v21;
  void *v23;
  void *v24;
  void *v25;
  s32 v27;
  SBTLAI_WORK *aiwk;
  SBTLACTION_WORK *v29;
  SBTLACTION_WORK *v30;
  s32 v31;
  SBTLACTION_WORK *v32;
  s32 use_skillid;
  s32 exWait;
  void *v38;
  void *v39;
  SBTLACTION_WORK *v43;
  s32 v44;
  bool v45;
  bool v47;
  SBTLACTION_WORK *v48;
  s32 v49;
  void *Instance;
  SBTLACTION_WORK *v53;
  bool v55;
  SBTLACTION_WORK *v56;
  void *v57;
  void *v58;
  s32 v59;
  void *v60;
  void *v64;
  bool v66;
  void *v67;
  SBTLACTION_WORK *v68;
  s32 v70;
  bool v71;
  f32 v72;
  f32 v73;
  f32 v74;
  f32 v75;
  void *v76;
  SBTLACTION_WORK *v77;
  void *v83;
  SBTLACTION_WORK *v84;
  sdfVector4_t v85;

  w = oldpos->w;
  z = oldpos->z;
  y = oldpos->y;
  x = oldpos->x;
  PChara = sBtlGetPChara();
  if (!sBtlHDloadChk(426))
    return 1;
  actwk = wk->actwk;
  exStep = actwk->exStep;
  if (exStep <= 1100)
  {
    if (exStep <= 250)
    {
      if (exStep)
      {
        if (exStep == 250)
        {
          v27 = actwk->exWait - 1;
          v71 = actwk->exWait == 1;
          actwk->exWait = v27;
          if (v27 < 0 || v71)
          {
            *(u64 *)&wk->rot.y = 0;
            wk->pos.z = 3000.0;
            wk->koteipos.z = 3000.0;
            aiwk = wk->aiwk;
            wk->rot.x = 0.0;
            LODWORD(aiwk) = aiwk->scrStep3;
            wk->pos.x = 0.0;
            wk->koteipos.x = 0.0;
            if ((u32)aiwk != 10)
              wk->status &= 0xFFFFBFFE;
            sBtlSetFade(wk, 1, 0, 0, 4);
            sBtlSetSkill_EffectData(wk, 426, 0);
            v29 = wk->actwk;
            v16 = 0;
            v29->exWait = 90;
            v29->exStep = 500;
            goto LABEL_149;
          }
        }
      }
      else
      {
        sBtlSetWinceStop(wk, 1);
        v30 = wk->actwk;
        v31 = v30->exWait - 1;
        v71 = v30->exWait == 1;
        v30->exWait = v31;
        if (v31 < 0 || v71)
        {
          sBtlSetMotion(wk, 0, 0, 0, 1);
          wk->status |= 0x4001u;
          sBtlSetFade(wk, 2, 0, 0, 16);
          sBtlSetSkill_EffectData(wk, 426, 0);
          v32 = wk->actwk;
          v32->exWait = 60;
          v32->exStep = 250;
          use_skillid = v32->use_skillid;
          if (use_skillid == 1549)
          {
            v16 = 0;
            DamashiFlag = 1;
          }
          else
          {
            v16 = 0;
            DamashiFlag = 0;
          }
          goto LABEL_149;
        }
      }
      goto LABEL_148;
    }
    if (exStep == 500)
    {
      wk->status |= 0x80000u;
      v49 = actwk->exWait - 1;
      v71 = actwk->exWait == 1;
      actwk->exWait = v49;
      if (v49 < 0 || v71)
      {
        sBtlSetMotion(wk, 36, 0, 0, 1);
        wk->actwk->exStep = 1000;
        BS_MUNAKA_SE(wk, 19);
        v16 = 0;
        wk->actwk->exWait = 0;
        goto LABEL_149;
      }
      goto LABEL_148;
    }
    if (exStep == 1000)
    {
      ++actwk->exWait;
      if (sBtlCheckMotionEnd(wk) || wk->actwk->exWait >= 65)
      {
        sBtlSetMotion(wk, 37, 0, 0, 1);
        Instance = get_Instance(0);
        Play(Instance, 0, 0);
        v53 = wk->actwk;
        v16 = 0;
        v53->exStep = 1100;
        v53->exWait = 300;
        if (wk->aiwk->scrStep3 == 10)
        {
          sBtlProcessStart(11, 0);
          dds3PostEspOn(0x1Eu);
          v16 = 0;
          wk->status &= 0xFFFFBFFE;
        }
        goto LABEL_149;
      }
      goto LABEL_148;
    }
    if (exStep != 1100)
      goto LABEL_148;
    if (dds3PostEspCheck2())
    {
      dds3PostEspOff(0x1Eu);
      goto LABEL_136;
    }
LABEL_136:
    v68 = wk->actwk;
    v70 = v68->exWait - 1;
    v71 = v68->exWait == 1;
    v68->exWait = v70;
    if (DamashiFlag)
    {
      if (v70 < 0 || v71)
        goto LABEL_172;
      v72 = PChara->pos.x;
      v73 = PChara->pos.y;
      v75 = PChara->pos.z;
      v74 = PChara->pos.w;
      sub_1B332C0(0, v72, v73, v75, v74);
      sub_1B33360(0, wk->pos.x, wk->pos.y, wk->pos.z, wk->pos.w);
      sub_1B33400(0);
      if ((loc_1CDE880)(0) < 250.0)
      {
LABEL_172:
        sBtlSetMotion(wk, 39, 0, 0, 1);
        v76 = get_Instance(0);
        Stop(v76, 0, 0);
        v77 = wk->actwk;
        v16 = 0;
        v77->exStep = 3000;
        v77->exWait = 30;
        wk->flg |= 2u;
        goto LABEL_149;
      }
    }
    else if (v70 < 0 || v71)
    {
      sBtlSetMotion(wk, 38, 0, 0, 1);
      BS_MUNAKA_SE(wk, 12);
      v83 = get_Instance(0);
      Play(v83, 1, 0);
      v84 = wk->actwk;
      v16 = 0;
      v84->exStep = 2000;
      v84->exWait = 0;
      goto LABEL_149;
    }
    goto LABEL_148;
  }
  if ((u32)exStep > 0xC1C)
  {
    if (exStep == 3200)
    {
      exWait = actwk->exWait - 1;
      v71 = actwk->exWait == 1;
      actwk->exWait = exWait;
      if (exWait < 0 || v71)
      {
        actwk->exWait = 120;
        actwk->exStep = 3300;
        sndVoicePlayFile("PVA18B_03_000", 0);
        ExplosionDameFlag = 1;
        v38 = get_Instance(0);
        Stop(v38, 4, 0);
        v39 = get_Instance(0);
        Play(v39, 5, 0);
        DeleteAll();
        exWait = wk->actwk->exWait;
      }
      if (exWait <= 59)
      {
        if (!EventFlag)
        {
          EventFlag = 1;
          if (wk->aiwk->scrStep3 == 210)
          {
            sBtlProcessStart(11, 1);
          }
        }
      }
      goto LABEL_148;
    }
    if (exStep != 3300)
    {
      if (exStep == 4000)
      {
        sBtlSetMotion(wk, 37, 5, 5, 1);
        v13 = get_Instance(0);
        Play(v13, 0, 0);
        v14 = wk->actwk;
        v14->exStep = 1100;
        v14->exWait = 30;
        v16 = 0;
        DamashiFlag = 1;
        goto LABEL_149;
      }
      goto LABEL_148;
    }
    if (ExplosionDameFlag)
    {
      BS_MUNAKA_Explosion_Hit(wk, 1);
    }
    v43 = wk->actwk;
    v44 = v43->exWait - 1;
    v45 = v43->exWait - 60 < 0;
    v43->exWait = v44;
    if (v45 ^ __OFSUB__(v44, 59) | (v44 == 59))
    {
      ExplosionDameFlag = 0;
LABEL_89:
      v47 = sBtlCheckMotionEnd(wk);
      v48 = wk->actwk;
      if (v47)
        goto LABEL_133;
LABEL_132:
      if (v48->exWait <= -10)
        goto LABEL_133;
      goto LABEL_148;
    }
    else
    {
      goto LABEL_89;
    }
    v66 = sBtlCheckMotionEnd(wk);
    v48 = wk->actwk;
    if (v66)
    {
LABEL_133:
      v48->exStep = 10000;
      ClrAction();
      wk->status &= ~0x80000u;
      wk->flg &= ~2u;
      v67 = get_Instance(0);
      Stop(v67, 5, 0);
      v16 = 1;
      goto LABEL_149;
    }
    goto LABEL_132;
  }
  if (exStep != 2000)
  {
    if (exStep == 3000)
    {
      v59 = actwk->exWait - 1;
      v71 = actwk->exWait == 1;
      actwk->exWait = v59;
      if (v59 < 0 || v71)
      {
        actwk = wk->actwk;
        v16 = 0;
        KaitenDameFlag = 0;
        actwk->exWait = 90;
        actwk->exStep = 3100;
        goto LABEL_149;
      }
      if ((u32)v59 <= 7)
      {
        v60 = get_Instance(0);
        Play(v60, 2, 0);
        BS_MUNAKA_SE(wk, 20);
      }
      goto LABEL_148;
    }
    if (exStep == 3100)
    {
      if (KaitenDameFlag)
      {
        BS_MUNAKA_Kaiten_Hit(wk, 0);
      }
      v19 = wk->actwk;
      v20 = v19->exWait;
      if (v20 == 70)
      {
        BS_MUNAKA_SE(wk, 21);
        v19 = wk->actwk;
        v21 = v19->exWait - 1;
        v71 = v19->exWait == 1;
        v19->exWait = v21;
        if (v21 >= 0 && !v71)
        {
LABEL_121:
          if (v21 > 29)
            goto LABEL_148;
LABEL_122:
          if (!KaitenDameFlag)
          {
            KaitenDameFlag = 1;
            v64 = get_Instance(0);
            Play(v64, 3, 0);
          }
          goto LABEL_148;
        }
      }
      else
      {
        v21 = v20 - 1;
        v19->exWait = v21;
        if (v21 > 0)
          goto LABEL_121;
      }
      v19->exWait = 90;
      v19->exStep = 3200;
      KaitenDameFlag = 0;
      v23 = get_Instance(0);
      Stop(v23, 2, 0);
      v24 = get_Instance(0);
      Stop(v24, 3, 0);
      v25 = get_Instance(0);
      Play(v25, 4, 0);
      BS_MUNAKA_SE(wk, 22);
      Add(wk->pos, 1000.0, -1.0, 0, 0);
      if (wk->actwk->exWait > 29)
        goto LABEL_148;
      goto LABEL_122;
    }
LABEL_148:
    v16 = 0;
    goto LABEL_149;
  }
  ++actwk->exWait;
  v55 = sBtlCheckMotionEnd(wk);
  v56 = wk->actwk;
  if (!v55 && v56->exWait < 126)
    goto LABEL_148;
  v56->exStep = 10000;
  ClrAction();
  wk->status &= ~0x80000u;
  v57 = get_Instance(0);
  Stop(v57, 0, 0);
  v58 = get_Instance(0);
  v16 = 1;
  Stop(v58, 1, 0);
LABEL_149:
  Proc(wk);
  sBtlProc(wk);
  sBtlMVSupport(wk);
  UnitMV(wk);
  v85.x = x;
  v85.y = y;
  v85.z = z;
  v85.w = w;
  CheckMapHit(wk, v85);
  UnitMV_To_Basic(wk);
  if (v16)
  {
    ResetAction(wk);
    sBtlSetAction(wk, 2, 0);
    sBtlEndAction(wk);
    sBtlSetWinceStop(wk, 0);
  }
  return 1;
}

// 0x1eaef00
static void BS_MUNAKA_Kaiten_Hit(SBTLUNIT_WORK *wk, bool _hutto) {
  SBTLUNIT_WORK *PChara;
  f32 x;
  f32 y;
  s32 v13;
  s32 use_skillid;
  f32 w;
  f32 z;
  SBTLUNIT_WORK *Nakama;
  SBTLUNIT_WORK *v19;
  SBTLUNIT_WORK *v21;
  SBTLUNIT_WORK *v23;
  sdfVector4_t v25;

  if (wk->cmbSkl->bRun)
    return;
  if (sBtlCheckSetsuma())
    return;
  if (!IsSceanStop())
  {
    if (wk->mode != 5)
    {
      PChara = sBtlGetPChara();
      if (!BS_MUNAKA_Kaiten_HitSub(wk, PChara))
      {
        goto LABEL_20;
      }
      if (wk)
      {
        if (PChara)
        {
          x = PChara->pos.x;
          y = PChara->pos.y;
          if (wk->actwk->use_skillid == 1548)
            v13 = 1559;
          else
            v13 = 1560;
          if (hutto)
            use_skillid = v13;
          else
            use_skillid = wk->actwk->use_skillid;
          z = PChara->pos.z;
          w = PChara->pos.w;
          v25.x = x;
          v25.y = y;
          v25.z = z;
          v25.w = w;
          SetDamageProc(PChara, wk, use_skillid, v25);
        }
      }
      PChara->damagecnt = 60;
LABEL_20:
      if (wk->NakamaShugouOn)
        return;
      Nakama = sBtlGetNakama(0);
      if (Nakama)
      {
        v19 = Nakama;
        if (BS_MUNAKA_Kaiten_HitSub(wk, v19))
        {
          BS_MUNAKA_Dmg(wk, v19, hutto);
          v19->damagecnt = 60;
        }
      }
      v21 = sBtlGetNakama(1);
      if (v21)
      {
        v23 = v21;
        if (BS_MUNAKA_Kaiten_HitSub(wk, v23))
        {
          BS_MUNAKA_Dmg(wk, v23, hutto);
          v23->damagecnt = 60;
        }
      }
      return;
    }
  }
}

// 0x1eaf5d0
static bool BS_MUNAKA_Kaiten_HitSub(SBTLUNIT_WORK *wk, SBTLUNIT_WORK *pu) {
  u16 major;
  s32 minor;
  VISUALDATA_WORK *VisualData;
  VISUALDATA_WORK *v9;
  f32 cylinder;
  f32 v12;
  f32 x;
  f32 z;
  f32 v15;
  f32 v16;
  f32 v17;
  f32 v18;
  f32 v19;

  if (!wk || !pu || pu->damagecnt > 0 || pu->para->now->hp < 1)
    return 0;
  major = wk->major;
  minor = wk->minor;
  VisualData = sBtlGetVisualData(major, minor);
  v9 = sBtlGetVisualData(pu->major, pu->minor);
  cylinder = VisualData->nml->cylinder;
  v12 = cylinder * 0.5;
  x = pu->pos.x;
  z = pu->pos.z;
  v15 = wk->pos.x;
  v16 = wk->pos.z;
  v17 = v12 + (f32)(MUNAKA_KAITEN_DISTANCE * 100.0);
  v18 = v9->nml->cylinder * 0.5;
  v19 = v17 + v18;
  return sqrtf((f32)((f32)(v15 - x) * (f32)(v15 - x)) + (f32)((f32)(v16 - z) * (f32)(v16 - z))) < v19;
}

// 0x1eaf250
static void BS_MUNAKA_Explosion_Hit(SBTLUNIT_WORK *wk, bool _hutto) {
  SBTLUNIT_WORK *PChara;
  f32 x;
  f32 y;
  s32 v12;
  s32 use_skillid;
  f32 w;
  f32 z;
  SBTLUNIT_WORK *Nakama;
  SBTLUNIT_WORK *v18;
  f32 v19;
  f32 v20;
  f32 v21;
  f32 v22;
  s32 v23;
  s32 v24;
  SBTLUNIT_WORK *v25;
  SBTLUNIT_WORK *v27;
  sdfVector4_t v29;
  sdfVector4_t v30;

  if (wk->cmbSkl->bRun)
    return;
  if (sBtlCheckSetsuma())
    return;
  PChara = sBtlGetPChara();
  if (!BS_MUNAKA_Explosion_HitSub(wk, PChara))
  {
    goto LABEL_14;
  }
  if (wk)
  {
    if (PChara)
    {
      x = PChara->pos.x;
      y = PChara->pos.y;
      if (wk->actwk->use_skillid == 1548)
        v12 = 1559;
      else
        v12 = 1560;
      if (hutto)
        use_skillid = v12;
      else
        use_skillid = wk->actwk->use_skillid;
      z = PChara->pos.z;
      w = PChara->pos.w;
      v29.x = x;
      v29.y = y;
      v29.z = z;
      v29.w = w;
      SetDamageProc(PChara, wk, use_skillid, v29);
    }
  }
  PChara->damagecnt = 121;
LABEL_14:
  if (wk->NakamaShugouOn)
    return;
  Nakama = sBtlGetNakama(0);
  if (!Nakama)
    goto LABEL_55;
  v18 = Nakama;
  if (!BS_MUNAKA_Explosion_HitSub(wk, v18))
    goto LABEL_55;
  if (wk)
  {
    v19 = v18->pos.x;
    v20 = v18->pos.y;
    v21 = v18->pos.z;
    v22 = v18->pos.w;
    if (wk->actwk->use_skillid == 1548)
      v23 = 1559;
    else
      v23 = 1560;
    if (hutto)
      v24 = v23;
    else
      v24 = wk->actwk->use_skillid;
    v30.x = v19;
    v30.y = v20;
    v30.z = v21;
    v30.w = v22;
    SetDamageProc(v18, wk, v24, v30);
  }
  v18->damagecnt = 121;
LABEL_55:
  v25 = sBtlGetNakama(1);
  if (v25)
  {
    v27 = v25;
    if (BS_MUNAKA_Explosion_HitSub(wk, v27))
    {
      BS_MUNAKA_Dmg(wk, v27, hutto);
      v27->damagecnt = 121;
    }
  }
}

// 0x1eaf860
static bool BS_MUNAKA_Explosion_HitSub(SBTLUNIT_WORK *wk, SBTLUNIT_WORK *pu) {
  u16 major;
  s32 minor;
  VISUALDATA_WORK *VisualData;
  f32 x;
  f32 z;
  f32 v11;
  f32 v12;
  f32 v13;
  f32 v14;

  if (!wk || !pu || pu->damagecnt > 0 || pu->para->now->hp < 1)
    return 0;
  major = wk->major;
  minor = wk->minor;
  sBtlGetVisualData(major, minor);
  VisualData = sBtlGetVisualData(pu->major, pu->minor);
  x = pu->pos.x;
  z = pu->pos.z;
  v11 = wk->pos.x;
  v12 = wk->pos.z;
  v13 = VisualData->nml->cylinder * 0.5;
  v14 = v13 + 1000.0;
  return sqrtf((f32)((f32)(v11 - x) * (f32)(v11 - x)) + (f32)((f32)(v12 - z) * (f32)(v12 - z))) < v14;
}

// 0x1eaf780
static void BS_MUNAKA_Dmg(SBTLUNIT_WORK *wk, SBTLUNIT_WORK *pu, bool _hutto) {
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  s32 v11;
  s32 use_skillid;
  sdfVector4_t v13;

  if (wk && pu)
  {
    x = pu->pos.x;
    y = pu->pos.y;
    z = pu->pos.z;
    w = pu->pos.w;
    if (wk->actwk->use_skillid == 1548)
      v11 = 1559;
    else
      v11 = 1560;
    if (hutto)
      use_skillid = v11;
    else
      use_skillid = wk->actwk->use_skillid;
    v13.x = x;
    v13.y = y;
    v13.z = z;
    v13.w = w;
    SetDamageProc(pu, wk, use_skillid, v13);
  }
}

// 0x1eaf9c0
bool sBtlChk_BS_MUNAKA_SetsumaNG(void) {
  SBTLUNIT_WORK *UnitFromDevilID;
  SBTLACTION_WORK *actwk;
  u32 status;
  s32 exStep;

  if (wk->encountno != 50)
    goto LABEL_25;
  UnitFromDevilID = sBtlGetUnitFromDevilID(291);
  if (!UnitFromDevilID)
    return (char)UnitFromDevilID;
  actwk = UnitFromDevilID->actwk;
  status = actwk->status;
  if (status == 43)
  {
    if ((UnitFromDevilID->status & 0x4000) != 0)
    {
      LOBYTE(UnitFromDevilID) = 1;
      return (char)UnitFromDevilID;
    }
    goto LABEL_25;
  }
  if (status != 67)
  {
LABEL_25:
    LOBYTE(UnitFromDevilID) = 0;
    return (char)UnitFromDevilID;
  }
  exStep = actwk->exStep;
  LOBYTE(UnitFromDevilID) = 1;
  if (exStep <= 250)
  {
    if (!exStep || exStep == 250)
      return (char)UnitFromDevilID;
  }
  else if (exStep == 500 || exStep == 1000)
  {
    return (char)UnitFromDevilID;
  }
  if (!dds3PostEspCheck())
    goto LABEL_25;
  LOBYTE(UnitFromDevilID) = 1;
  return (char)UnitFromDevilID;
}

// 0x1eafb30
void sBtlBS_RASUPU_Init_Nenr(SBTLUNIT_WORK *wk) {
  SBTLACTION_WORK *actwk;
  s64 i;
  char *v6;
  SBTLUNIT_WORK *v8;

  actwk = wk->actwk;
  actwk->status = 64;
  actwk->exStep = 0;
  actwk->exWait = 0;
  eff_timer = 0.0;
  for (i = 0; ; ++i)
  {
    if (i >= SLODWORD(bs_se_stock->max_length))
      break;
    v6 = (char *)bs_se_stock + 4 * i;
    *((u32 *)v6 + 8) = -1;
  }
  v8 = sBtlSearchDeivl(323);
  if (v8)
  {
    END_PREVIOUS_SKILL = 0;
    wk->actwk->exStep = 1200;
  }
  else
  {
    END_PREVIOUS_SKILL = 1;
  }
  wk->status &= 0xFBFFBFFE;
  wk->flg |= 0x40u;
  wk->aiwk->scrflag |= 0x4000000u;
}

// 0x1eafcc0
bool sBtlBS_RASUPU_Action_Nenr(SBTLUNIT_WORK *wk, const sdfVector4_t *oldpos) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  SBTLUNIT_WORK *PChara;
  SBTLUNIT_WORK *v11;
  f32 v14;
  SBTLACTION_WORK *actwk;
  s32 exStep;
  s32 exWait;
  s32 v18;
  s32 v19;
  SBTLACTION_WORK *v23;
  s32 v25;
  bool v26;
  s32 v29;
  SBTLACTION_WORK *v33;
  SBTLUNIT_WORK *v36;
  s32 v38;
  s32 v39;
  SBTLACTION_WORK *v40;
  SBTLACTION_WORK *v42;
  s32 v43;
  s32 v44;
  f32 v48;
  f32 v49;
  f32 v50;
  f32 v51;
  void *Instance;
  void *v56;
  void *v57;
  SBTLSKILLP_TBL *Skilltbl;
  SBTLSKL_KAJA_WORK *v63;
  SBTLACTION_WORK *v66;
  s32 v67;
  SBTLUNIT_WORK *v69;
  s32 v70;
  sdfVector4_t v78;
  sdfVector4_t v79;

  w = oldpos->w;
  z = oldpos->z;
  y = oldpos->y;
  x = oldpos->x;
  if (!sBtlHDloadChk(426))
    return 1;
  if (!sBtlHDloadChk(128))
    return 1;
  PChara = sBtlGetPChara();
  v11 = sBtlSearchDeivl(323);
  actwk = wk->actwk;
  exStep = actwk->exStep;
  if (exStep <= 2000)
  {
    if (exStep <= 1100)
    {
      if (exStep)
      {
        if (exStep != 100)
        {
          if (exStep == 1100)
          {
            v29 = actwk->exWait - 1;
            v26 = actwk->exWait == 1;
            actwk->exWait = v29;
            if (v29 < 0 || v26)
            {
              actwk->exStep = 1200;
              MatyStopOff();
              v19 = 0;
              goto LABEL_200;
            }
          }
          goto LABEL_198;
        }
        v44 = actwk->exWait + 1;
        actwk->exWait = v44;
        if (v44 == 65)
        {
          BS_RASUPU_SE(wk, 24);
          AI_SET_SUMMON_POINT_SUB(wk, 323, -300, 0, 0, 0);
        }
        else
        {
          v48 = PChara->pos.x;
          v49 = PChara->pos.y;
          v50 = PChara->pos.z;
          v51 = PChara->pos.w;
          v78.x = v48;
          v78.y = v49;
          v78.z = v50;
          v78.w = v51;
          DirSetHokan(wk, v78, v14);
          wk->status &= 0xFBFFBFFE;
        }
        if (wk->actwk->exWait == 140)
        {
          BS_MATORY_SE(wk, 27);
        }
        ++gTimeoutCnt;
        if (wk->actwk->exWait < 141)
          goto LABEL_198;
        if (!sBtlCheckMotionEnd(wk))
        {
          if (gTimeoutCnt < 229)
            goto LABEL_198;
        }
        v42 = wk->actwk;
        v19 = 0;
        v43 = 1500;
      }
      else
      {
        sBtlSetWinceStop(wk, 1);
        wk->status |= 0x4004001u;
        sBtlSetMotion(wk, 32, 0, 0, 1);
        v42 = wk->actwk;
        v19 = 0;
        v43 = 100;
      }
      v42->exStep = v43;
      v42->exWait = 0;
      goto LABEL_200;
    }
    if (exStep != 1200)
    {
      if (exStep == 1500)
      {
        v19 = 0;
        ++actwk->exWait;
        goto LABEL_200;
      }
      if (exStep == 2000)
      {
        sBtlSetWinceStop(wk, 0);
        sBtlSetMotion(wk, 33, 0, 0, 1);
        v23 = wk->actwk;
        v23->exStep = 2100;
        v23->exWait = 60;
        BS_RASUPU_SE(wk, 25);
        v19 = 0;
        gTimeoutCnt = 0;
        goto LABEL_200;
      }
      goto LABEL_198;
    }
    v36 = v11;
    if (v11 && v11->actwk->use_skillid != 1544)
    {
      if (END_PREVIOUS_SKILL)
      {
        if (v36->actwk->exStep == 10000)
        {
          v19 = 1;
          wk->actwk->exStep = 10000;
          goto LABEL_200;
        }
        goto LABEL_198;
      }
      actwk = wk->actwk;
    }
    v19 = 1;
    actwk->exStep = 10000;
    goto LABEL_200;
  }
  if ((u32)exStep > 0xBEA)
  {
    if ((u32)exStep <= 0xFA0)
    {
      if (exStep == 3100)
      {
        if (sBtlCheckMotionNo(wk, 34))
        {
          eff_timer = eff_timer + 1.0;
        }
        else
        {
          sBtlSetMotion(wk, 34, 0, 0, 1);
          eff_timer = 0.0;
        }
        if (eff_timer == 15.0)
        {
          Instance = get_Instance(0);
          Play(Instance, 4, 0);
          BS_RASUPU_SE(wk, 29);
        }
        if (eff_timer == 209.0)
        {
          BS_RASUPU_SE(wk, 28);
        }
        if (eff_timer == 349.0)
        {
          BS_RASUPU_SE(wk, 30);
        }
        if (eff_timer >= 89.0)
        {
          v56 = get_Instance(0);
          if (op_Inequality(v56, 0, 0))
          {
            v57 = get_Instance(0);
            Stop(v57, 1, 0);
          }
        }
        ++gTimeoutCnt;
        if (eff_timer > 349.0)
        {
          if (sBtlCheckMotionEnd(wk))
            goto LABEL_171;
          if (gTimeoutCnt >= 451)
          {
LABEL_171:
            Skilltbl = sBtlGetSkilltbl(1545);
            v63 = wk->wkKaja[0];
            sBtlRegistKaja(wk, v63, Skilltbl);
            sBtlRegistKaja(wk, wk->wkKaja[1], Skilltbl);
            sBtlSetSkill_EffectData(wk, 128, 1);
            MatyStopOff();
            wk->actwk->exStep = 1200;
            eff_timer = 0.0;
            sBtlSetMotion(wk, 0, 0, 0, 1);
            sBtlSetWinceStop(wk, 0);
            v19 = 0;
            goto LABEL_200;
          }
        }
      }
      else if (exStep == 4000)
      {
        --actwk->exWait;
        if (sBtlCheckMotionEnd(wk) || wk->actwk->exWait <= 0)
        {
          sBtlSetWinceStop(wk, 0);
          sBtlSetMotion(wk, 35, 0, 0, 1);
          v33 = wk->actwk;
          v33->exStep = 4100;
          v33->exWait = 60;
          BS_RASUPU_SE(wk, 32);
          BS_RASUPU_SE(wk, 31);
          v19 = 0;
          goto LABEL_200;
        }
      }
    }
    else if (exStep == 4100)
    {
      exWait = actwk->exWait;
      if (exWait)
      {
        v18 = exWait - 1;
        actwk->exWait = v18;
        if (v18 <= 0)
        {
          if (sBtlCheckMotionEnd(wk))
          {
            sBtlSetMotion(wk, 35, 0, 0, 1);
            v19 = 0;
            wk->actwk->exWait = 60;
            goto LABEL_200;
          }
          MatyStopOff();
          v69 = wk;
          v70 = 14;
          goto LABEL_218;
        }
      }
    }
    goto LABEL_198;
  }
  switch (exStep)
  {
    case 2100:
      v38 = actwk->exWait;
      if (v38)
      {
        v39 = v38 - 1;
        actwk->exWait = v39;
        if (v39 <= 0)
        {
          if (sBtlCheckMotionEnd(wk))
          {
            sBtlSetMotion(wk, 33, 0, 0, 1);
            wk->actwk->exWait = 60;
          }
          else
          {
            MatyStopOff();
          }
        }
      }
      ++gTimeoutCnt;
      if (!wk->actwk->exWait)
      {
        if (sBtlCheckMotionEnd(wk))
          goto LABEL_223;
        if (gTimeoutCnt >= 281)
        {
LABEL_223:
          v69 = wk;
          v70 = 0;
LABEL_218:
          sBtlSetMotion(v69, v70, 0, 0, 1);
          v66 = wk->actwk;
          v19 = 0;
          v67 = 1200;
LABEL_219:
          v66->exStep = v67;
          goto LABEL_200;
        }
      }
      break;
    case 3000:
      sBtlSetMotion(wk, 34, 0, 0, 1);
      v40 = wk->actwk;
      v40->exWait = 2;
      *(u64 *)&v40->exStep = 3050;
      v19 = 0;
      gTimeoutCnt = 0;
      goto LABEL_200;
    case 3050:
      v25 = actwk->exWait - 1;
      v26 = actwk->exWait == 1;
      actwk->exWait = v25;
      if (v25 < 0 || v26)
      {
        if (sBtlCheckMotionEnd(wk))
        {
          sBtlSetMotion(wk, 34, 0, 0, 1);
LABEL_183:
          BS_RASUPU_SE(wk, 27);
          v66 = wk->actwk;
          v19 = 0;
          v67 = 3100;
          goto LABEL_219;
        }
        goto LABEL_183;
      }
      break;
  }
LABEL_198:
  v19 = 0;
LABEL_200:
  Proc(wk);
  sBtlProc(wk);
  sBtlMVSupport(wk);
  UnitMV(wk);
  v79.x = x;
  v79.y = y;
  v79.z = z;
  v79.w = w;
  CheckMapHit(wk, v79);
  UnitMV_To_Basic(wk);
  if (v19)
  {
    wk->flg &= ~0x40u;
    wk->aiwk->scrflag &= ~0x4000000u;
    ResetAction(wk);
    sBtlSetAction(wk, 2, 0);
    sBtlEndAction(wk);
  }
  return 1;
}

// 0x1eb0b80
static void MatyStopOff(void) {
  SBTLUNIT_WORK *v3;
  SBTLACTION_WORK *actwk;

  v3 = sBtlSearchDeivl(323);
  if (!v3)
    return;
  actwk = v3->actwk;
  if (actwk->exStep == 1500)
    actwk->exStep = 2000;
}

// 0x1eab110
SBTLUNIT_WORK *sBtlSearchDeivl(s32 devilID) {
  SBTLUNIT_WORK *wk_local;
  s64 i;
  SBTLUNIT_LISTWORK *UnitMng;
  sdatUnitWork_t *para;

  wk_local = (SBTLUNIT_WORK *)wk;
  if (!wk_local)
    return wk_local;
  wk_local = *(SBTLUNIT_WORK *)&wk_local->GroupID;
  if (!wk_local)
    return wk_local;
  wk_local = (SBTLUNIT_WORK *)wk->UnitMng;
  wk_local = *(SBTLUNIT_WORK *)&wk_local->vPosCmbMov0.z;
  if (!wk_local)
    return wk_local;
  for (i = 0; ; ++i)
  {
    UnitMng = wk->UnitMng;
    if (i >= UnitMng->number)
      break;
    wk_local = UnitMng->pUnitL[i]->pUnit;
    if (!wk_local)
      continue;
    para = wk_local->para;
    if (para && para->devilid == devilID)
      return wk_local;
  }
  return 0;
}

// 0x1eb0c20
void sBtlBS_RASUPU_Dead_EffStop0(void) {
  void *Instance;
  void *v3;

  Instance = get_Instance(0);
  if (!op_Inequality(Instance, 0, 0))
    return;
  goto LABEL_4;
  if (op_Inequality(Instance, 0, 0))
  {
LABEL_4:
    v3 = get_Instance(0);
    Stop(v3, 2, 0);
  }
}

// 0x1eb0ce0
void sBtlBS_RASUPU_Dead_EffStop(void) {
  void *Instance;
  void *v3;

  Instance = get_Instance(0);
  if (!op_Inequality(Instance, 0, 0))
    return;
  goto LABEL_4;
  if (op_Inequality(Instance, 0, 0))
  {
LABEL_4:
    v3 = get_Instance(0);
    Stop(v3, 4, 0);
  }
}

// 0x1eb0da0
void sBtlBS_YOMI_Init_Gun(SBTLUNIT_WORK *wk) {
  SBTLACTION_WORK *actwk;
  s64 i;
  char *v7;

  actwk = wk->actwk;
  actwk->status = 76;
  actwk->exStep = 0;
  actwk->exWait = 0;
  for (i = 0; ; ++i)
  {
    if (i >= SLODWORD(bs_se_stock->max_length))
      break;
    v7 = (char *)bs_se_stock + 4 * i;
    *((u32 *)v7 + 8) = -1;
  }
}

// 0x1eb0ea0
bool sBtlBS_YOMI_Action_Gun(SBTLUNIT_WORK *wk, const sdfVector4_t *oldpos) {
  sBtlGetPChara();
  Proc(wk);
  sBtlProc(wk);
  if ((wk->status & 1) == 0)
  {
    sBtlMVSupport(wk);
  }
  UnitMV(wk);
  UnitMV_To_Basic(wk);
  return 1;
}

// 0x1eb0fd0
static s32 GetTimeStopID(SKLID sklID) {
  s32 v4;
  s32 v5;

  v4 = 0;
  while (1)
  {
    v5 = g_aTimeStopSkl[v4]->sklID;
    if (!v5)
      return -1;
    v5 = g_aTimeStopSkl[v4]->sklID;
    if (v5 == sklID)
      return v4;
    ++v4;
  }
}

// 0x1eb10a0
s32 sBtlGetSklTimeStop(SKLID sklID) {
  s32 v4;
  S_TIMESTOPSKL *v5;
  s32 v6;
  s64 v7;

  v4 = 0;
  do
  {
    v5 = g_aTimeStopSkl[v4];
    v6 = v5->sklID;
    if (!v6)
      return 0;
    v7 = v4;
    v5 = g_aTimeStopSkl[v4];
    v6 = v5->sklID;
    ++v4;
  }
  while (v6 != sklID);
  return v5->wait;
}

// 0x1eb11b0
static void SetAction_ProgramSkill(SBTLUNIT_WORK *wk, SKLID skillID) {
  SBTLACTION_WORK *actwk;
  char v6;
  SBTLUNIT_WORK *UnitFromDevilID;
  sdatUnitWork_t *para;
  s32 v9;
  __int128 v10;
  s32 v11;
  SBTLDMG_HITLISTWORK *hitList;
  SBTLEFF_LISTWORK *effList;

  actwk = wk->actwk;
  actwk->total_homing = 0.0;
  actwk->no_homing = 0;
  actwk->action_flg = 0;
  *(u64 *)&actwk->framecntC = 0;
  *(u64 *)&actwk->framecnt = 0;
  actwk->effectTime = 0xFFFFFFF;
  if (skillID > 1535)
  {
    switch (skillID)
    {
      case 1536:
      case 1537:
        sBtlBS_ITIMOK_Init_Kaiten(wk);
        break;
      case 1538:
        sBtlBS_AKAMA2_Init_Taxi(wk);
        break;
      case 1542:
        sBtlBS_RASUPU_Init_Nenr(wk);
        break;
      case 1543:
      case 1544:
      case 1545:
      case 1546:
        sBtlBS_MATORY_Init_Nenr(wk);
        break;
      case 1547:
        sBtlBS_MISHAK_Init_Hiru(wk);
        break;
      case 1548:
      case 1549:
        sBtlBS_MUNAKA_Init_Imad(wk);
        break;
      case 1550:
        sBtlBS_LASTB1_Init_Setu(wk);
        break;
      case 1551:
        sBtlBS_LASTB1_Init_Setr(wk);
        break;
      case 1552:
        sBtlBS_LASTB1_Init_Dang(wk);
        break;
      case 1555:
        sBtlBS_LASTB1_Init_Dsmn(wk);
        break;
      case 1556:
        sBtlBS_LASTB1_Init_Gurd(wk);
        break;
      case 1557:
        sBtlBS_LASTB1_Init_Bstp(wk);
        break;
      case 1558:
        sBtlBS_LASTB1_Init_Quik(wk);
        break;
      case 1561:
        sBtlBS_YOMI_Init_Gun(wk);
        break;
      default:
        goto LABEL_82;
    }
  }
  else
  {
    if (skillID <= 440)
    {
      v6 = skillID + 28;
      if ((u32)(skillID - 228) <= 0xA)
      {
        if (((1 << v6) & 0x83) != 0)
        {
LABEL_28:
          v11 = 51;
          goto LABEL_29;
        }
        if (((1 << v6) & 0x300) != 0)
        {
LABEL_19:
          sBtlResetGunMode_Eve();
          hitList = wk->hitList;
          sBtlClearHitC(hitList, wk);
          effList = wk->effList;
          sBtlForceResetDecAlpha(effList, wk, 8);
          actwk = wk->actwk;
          v11 = 44;
          goto LABEL_29;
        }
        if (skillID == 238)
        {
          v11 = 52;
          goto LABEL_29;
        }
      }
      if ((u32)(skillID - 75) < 5)
      {
        actwk->status = 50;
        UnitFromDevilID = sBtlGetUnitFromDevilID(260);
        switch (skillID)
        {
          case 'K':
            para = UnitFromDevilID->para;
            v9 = 0;
            v10 = xmmword_3D00650;
            goto LABEL_43;
          case 'L':
            para = UnitFromDevilID->para;
            v9 = 1;
            v10 = xmmword_3CFFEA0;
            goto LABEL_43;
          case 'M':
            para = UnitFromDevilID->para;
            v9 = 2;
            v10 = xmmword_3D026B0;
            goto LABEL_43;
          case 'N':
            para = UnitFromDevilID->para;
            v9 = 3;
            v10 = xmmword_3CFA100;
LABEL_43:
            *(_OWORD *)&para->aisyo->para[2] = v10;
            Add(wk->ListID, v9, 0);
            break;
          default:
            return;
        }
        return;
      }
      if (skillID == 74)
        v11 = 47;
      else
LABEL_82:
        v11 = 6;
LABEL_29:
      actwk->status = v11;
      return;
    }
    switch (skillID)
    {
      case 441:
        v11 = 39;
        goto LABEL_29;
      case 447:
        actwk->status = 48;
        CheckSkillMessage(wk, 447);
        break;
      case 464:
      case 466:
        v11 = 38;
        goto LABEL_29;
      case 467:
        v11 = 49;
        goto LABEL_29;
      case 474:
        goto LABEL_28;
      case 498:
      case 499:
        goto LABEL_19;
      default:
        goto LABEL_82;
    }
  }
}

// 0x1ea4fa0
static void ResetAction(SBTLUNIT_WORK *wk) {
  SBTLACTAI_WORK *actaiwk;
  s32 status;
  SBTLUNIT_WORK *v6;
  SBTLUNIT_WORK *v7;

  actaiwk = wk->actaiwk;
  status = actaiwk->status;
  if ((status & 0x4000) != 0 && (wk->side & 1) != 0)
  {
    actaiwk->status = status & 0xFFFFBFFF;
    sBtlStatusBitOff(wk, 0xFFFFBFEF);
    v6 = sBtlSearchUnit_ID(wk->UnitMng, wk->playerID);
    if (v6)
    {
      v7 = v6;
      sBtlResetAction(v7);
    }
  }
  if ((wk->side & 2) != 0)
    wk->flg &= ~0x800u;
}

// 0x1eb19f0
SBTLUNIT_WORK *sBtlGetAnotherEnemy(SBTLUNIT_WORK *wk) {
  s64 i;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  bool v7;

  for (i = 0; ; ++i)
  {
    UnitMng = wk->UnitMng;
    if (i >= UnitMng->number)
      break;
    UnitMng = wk->UnitMng;
    pUnit = UnitMng->pUnitL[i]->pUnit;
    if (pUnit)
      v7 = pUnit == wk;
    else
      v7 = 1;
    if (!v7 && (pUnit->side & 2) != 0)
      return pUnit;
  }
  return 0;
}

// 0x1eb1ae0
void sBtlLockOnFree(SBTLUNIT_WORK *wk) {
  SBTLUNIT_WORK *Nakama;
  SBTLUNIT_WORK *v4;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 targetID;
  SBTLUNIT_WORK *v8;
  SBTLUNIT_WORK *v9;
  SBTLUNIT_LISTWORK *v11;
  s32 v12;

  Nakama = sBtlGetNakama(0);
  if (Nakama)
  {
    v4 = Nakama;
    UnitMng = wk->UnitMng;
    targetID = v4->actaiwk->targetID;
    if (sBtlSearchUnit_ID(UnitMng, targetID) != wk)
      goto LABEL_8;
    v4->actaiwk->targetID = -1;
    v8 = sBtlGetNakama(1);
    if (!v8)
      return;
    goto LABEL_9;
  }
LABEL_8:
  v8 = sBtlGetNakama(1);
  if (!v8)
    return;
LABEL_9:
  v9 = v8;
  v11 = wk->UnitMng;
  v12 = v9->actaiwk->targetID;
  if (sBtlSearchUnit_ID(v11, v12) != wk)
    return;
  v9->actaiwk->targetID = -1;
  return;
}

// 0x1e94f30
bool Proc(SBTLUNIT_WORK *wk) {
  SBTLVISUAL_DATA *v3;
  s32 motionno;
  s32 v5;
  s32 side;
  u16 major;
  s32 minor;
  MOTIONDATA_WORK *MotionVisualData;
  sdfVector4_t *p_mv_spd;
  s32 battlemode;
  f32 *p_x;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  sdfVector4_t *p_nextpos;
  f32 *v23;
  SBTLACTION_WORK *p_actwk;
  s32 mode;
  s32 targetID;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v33;
  SBTLUNIT_WORK *v34;
  f32 mawari_pos_x;
  f32 mawari_pos_z;
  f32 v37;
  f32 v38;
  f32 v39;
  bool v40;
  f32 v42;
  f32 v43;
  f32 v44;
  f32 v45;
  f32 v46;
  f32 v47;
  long f64 v48;
  long f64 v49;
  f32 v50;
  f32 v51;
  f32 v52;
  f32 v53;
  s32 damage_eff_tgt_cnt;
  bool v56;
  s32 v57;
  s32 damage_eff_rai_cnt;
  s32 v59;
  s32 damage_fuka_tgt_cnt;
  s32 v61;
  s32 v62;
  SBTLACTION_WORK *actwk;
  SBATTLE_WORK *v65;
  u64 v66;
  s32 *p_framecnt;
  f32 *v70;
  f32 v71;
  f32 v72;
  f32 v73;
  f32 v74;
  f32 mv_rotbk;
  SBATTLE_WORK *v77;
  s32 yobidousaCnt;
  SBATTLE_WORK *v80;
  SBTLUNIT_LISTWORK *v81;
  s32 playerID;
  f32 v83;
  f32 v84;
  f32 v85;
  s32 v87;
  SBATTLE_WORK *v89;
  s32 katana_hit_cnt;
  s32 v91;
  s32 v92;
  s32 yuka_damagecnt;
  s32 v94;
  s32 nguard_dmgcnt;
  s32 v96;
  s32 hangeki_nokezoranai;
  s32 v98;
  s32 hangeki_notjyakuten;
  s32 v100;
  s32 motionID;
  s32 devilid;
  u32 DevilSESub;
  u32 v104;
  SBTLAI_WORK *aiwk;
  s32 *p_syscnt_stop;
  s32 syscnt_stop;
  s32 damage_guncnt;
  s32 v110;
  s32 damage_1stmotcnt;
  s32 v112;
  s32 eff_wait_mukou;
  s32 v114;
  s32 eff_wait_kyushu;
  s32 v116;
  s32 eff_wait_guard;
  s32 v118;
  s32 eff_wait_kaisin;
  s32 v120;
  s32 vice_kaisin_cnt;
  s32 v122;
  SBTLSKL_KAJA_WORK **wkKaja;
  SBTLSKL_KAJA_WORK *v124;
  SBTLSKL_KAJA_WORK *v125;
  s32 m_cnt;
  s32 v127;
  SBTLSKL_KAJA_WORK *v128;
  s32 v129;
  s32 v130;
  SBTLSKL_KAJA_WORK *v131;
  SBTLSKL_KAJA_WORK *v132;
  s32 v133;
  s32 v134;
  SBTLSKL_KAJA_WORK *v135;
  s32 v136;
  s32 v137;
  SBTLSKL_KAJA_WORK *v138;
  SBTLSKL_KAJA_WORK *v139;
  s32 v140;
  s32 v141;
  SBTLSKL_KAJA_WORK *v142;
  s32 v143;
  s32 v144;
  s32 o_atk_up_time;
  s32 v146;
  s32 o_def_dn_time;
  s32 v148;
  tagSBTLSKL_KARN_WORK *v149;
  s32 v150;
  s32 v151;
  u32 v153;
  s32 m_skillid;
  s32 v156;
  SBTLUNIT_WORK *AnotherEnemy;
  SBTLACTION_WORK *v160;
  s32 sklID;
  SBTLACTAI_WORK *actaiwk;
  SBTLSM_LISTWORK *v165;
  SBTLACTION_WORK *v166;
  SBTLSM_LISTWORK *v169;
  s32 v172;
  SBTLAI_WORK *v175;
  SBTLAI_WORK *v176;
  u32 cmndFrm;
  SBATTLE_WORK *v180;
  SBTLUNIT_WORK *Nakama;
  SBTLUNIT_WORK *v182;
  SBTLUNIT_WORK *v183;
  f32 v184;
  f32 v185;
  f32 v186;
  f32 v187;
  f32 v188;
  f32 v189;
  f32 v190;
  f32 v191;
  f32 v192;
  f32 v193;
  f32 v194;
  f32 v195;
  s32 v196;
  SBTLUNIT_LISTWORK *v198;
  SBTLUNIT_WORK *v199;
  s64 v200;
  f32 per;
  f32 v206;
  f32 v207;
  f32 v208;
  f32 v209;
  f32 Radian;
  long f64 v211;
  long f64 v212;
  f32 RotToDir;
  bool v214;
  s32 ListID;
  s32 timeStopID;
  SBTLSM_LISTWORK *sysmsgList;
  s32 v219;
  s32 hstatus;
  s32 noWeakStfCnt;
  s32 v222;
  SBATTLE_WORK *v224;
  u32 status;
  s32 v226;
  SBATTLE_WORK *v228;
  SBTLUNIT_LISTWORK *v229;
  s32 v230;
  SBTLUNIT_WORK *v231;
  f32 v232;
  f32 v233;
  f32 v234;
  f32 v235;
  f32 v236;
  SBTLACTION_WORK *v237;
  f32 *p_asimoto_pos_x;
  f32 v239;
  s32 v242;
  SBTLACTION_WORK *v243;
  s32 v244;
  SBTLACTION_WORK *v246;
  SBATTLE_WORK *v248;
  s32 use_skillid;
  SBTLSKILLP_TBL *Skilltbl;
  s32 v251;
  s32 v252;
  SBTLUNIT_LISTWORK *v254;
  SBTLUNIT_WORK *v255;
  SBTLUNIT_WORK *v256;
  f32 v257;
  f32 v258;
  f32 v259;
  f32 v260;
  f32 v261;
  f32 h_attack_move_len;
  f32 v263;
  f32 v264;
  s32 v265;
  SBTLACTION_WORK *v266;
  f32 v267;
  s32 v268;
  f32 v269;
  s32 v270;
  f32 v271;
  char v272;
  u32 v273;
  s32 v274;
  f32 v275;
  char v276;
  s32 v277;
  SBTLACTION_WORK *v278;
  SBTLAI_WORK *v279;
  s32 v280;
  f32 v281;
  f32 v282;
  f32 v283;
  f32 v284;
  f32 v285;
  f32 v286;
  f32 v287;
  f32 v289;
  SBATTLE_WORK *v290;
  SBTLUNIT_LISTWORK *v291;
  s32 v292;
  SBTLUNIT_WORK *v293;
  f32 v294;
  f32 v295;
  f32 v296;
  s32 vstatus;
  f32 v298;
  s32 v300;
  u32 v302;
  s32 v305;
  s32 v306;
  f32 v307;
  s32 v308;
  s32 v309;
  s32 action_flg;
  f32 v311;
  s32 v312;
  s32 v313;
  f32 v314;
  f32 v315;
  f32 v316;
  f32 v317;
  f32 v319;
  f32 v320;
  f32 v321;
  f32 v322;
  s32 v323;
  f32 v324;
  SBTLUNIT_WORK *v325;
  s32 v326;
  SBTLUNIT_LISTWORK *v328;
  s32 hithelperID;
  SBTLUNIT_WORK *v330;
  SBTLUNIT_WORK *v331;
  s32 v332;
  SBTLUNIT_LISTWORK *v334;
  s32 v335;
  SBTLUNIT_WORK *v336;
  SBTLUNIT_WORK *v337;
  s32 hithelperno;
  long f64 v339;
  s32 v341;
  f32 v342;
  s32 v343;
  SBTLACTION_WORK *v344;
  s32 v345;
  s32 v346;
  s32 v347;
  SBTLACTION_WORK *v349;
  SBATTLE_WORK *v350;
  s32 v352;
  bool v353;
  s32 v354;
  s32 v355;
  f32 v356;
  SBTLACTION_WORK *v357;
  s32 effect_flg;
  u32 cmpframecnt3;
  u32 v360;
  u32 v361;
  u32 v362;
  s32 v364;
  f32 v365;
  s32 v366;
  SBTLACTION_WORK *v367;
  s32 v368;
  s32 v369;
  s32 v370;
  s32 v371;
  f32 v372;
  s32 v373;
  s32 v375;
  SBTLUNIT_WORK *v376;
  s32 v377;
  SBTLACTION_WORK *v378;
  s32 v379;
  s32 v380;
  s32 v381;
  bool v382;
  f32 v383;
  SBTLACTION_WORK *v384;
  s32 v385;
  f32 v386;
  SBTLACTION_WORK *v387;
  s32 v388;
  s32 v389;
  s32 v390;
  SBTLACTION_WORK *v391;
  s32 v392;
  s32 v393;
  s32 v394;
  f32 v395;
  SBTLACTION_WORK *v396;
  s32 v397;
  s32 v398;
  f32 v399;
  f32 v400;
  f32 v401;
  f32 v402;
  SBTLACTION_WORK *v403;
  s64 v404;
  s32 v405;
  s32 v406;
  f32 v407;
  s32 v408;
  SBTLACTION_WORK *v409;
  s32 v410;
  s32 v411;
  s32 v412;
  f32 v413;
  f32 v414;
  sdatUnitWork_t *v415;
  u32 v416;
  char v417;
  u32 v418;
  s32 v419;
  SBATTLE_WORK *v421;
  SBTLUNIT_LISTWORK *v422;
  s32 v423;
  s32 v424;
  f32 v425;
  SBTLACTION_WORK *v426;
  s32 v427;
  SBATTLE_WORK *v429;
  SBTLUNIT_LISTWORK *v430;
  s32 v431;
  f32 v432;
  s32 v433;
  SBTLACTION_WORK *v434;
  s32 v435;
  SBATTLE_WORK *v437;
  SBTLUNIT_LISTWORK *v438;
  s32 v439;
  SBTLUNIT_WORK *v440;
  f32 v441;
  SBTLACTION_WORK *v442;
  f32 v443;
  f32 v444;
  f32 v445;
  f32 v446;
  SBTLACTAI_WORK *v447;
  f32 v448;
  f32 v449;
  f32 v450;
  f32 LenXZ;
  SBTLACTAI_WORK *v452;
  f32 v453;
  f32 v454;
  SBTLACTAI_WORK *v455;
  s32 v456;
  f32 v457;
  SBTLACTION_WORK *v458;
  s32 v459;
  s32 v460;
  SBTLUNIT_LISTWORK *v462;
  s32 v463;
  SBTLUNIT_WORK *v464;
  SBTLUNIT_WORK *v465;
  s32 v466;
  s32 v467;
  f32 v468;
  SBTLUNIT_LISTWORK *v470;
  s32 v471;
  SBTLUNIT_WORK *v472;
  SBTLUNIT_WORK *v473;
  f32 v474;
  s32 v475;
  SBTLUNIT_LISTWORK *v477;
  SBTLUNIT_WORK *v478;
  SBTLUNIT_WORK *v479;
  f32 v480;
  f32 v481;
  f32 v482;
  f32 v483;
  f32 v484;
  SBTLACTION_WORK *v485;
  s32 mawari_lr;
  u32 v487;
  bool v488;
  f32 v489;
  f32 v490;
  f32 v491;
  f32 v492;
  f32 v493;
  f32 v494;
  f32 v495;
  s32 v496;
  s32 v497;
  f32 v498;
  f32 v499;
  f32 v500;
  f32 v501;
  f32 v502;
  f32 v503;
  f32 v504;
  f32 v505;
  f32 v506;
  u32 v507;
  s32 v508;
  f32 v509;
  f32 v510;
  f32 v511;
  f32 v512;
  f32 v513;
  f32 v514;
  f32 v515;
  f32 v516;
  f32 v517;
  f32 v518;
  u32 v519;
  sdatUnitWork_t *v522;
  s32 v523;
  int8x8_t v524;
  int8x8_t *p_status;
  u64 v528;
  s32 v529;
  SBTLACTAI_WORK *v531;
  f32 v532;
  f32 v533;
  f32 v534;
  f32 v535;
  f32 v536;
  s32 v537;
  f32 v538;
  f32 v539;
  f32 v540;
  long f64 v541;
  SBTLACTAI_WORK *v546;
  f32 v547;
  f32 v548;
  f32 v549;
  f32 v550;
  f32 v551;
  f32 v552;
  f32 v553;
  long f64 v554;
  s32 v555;
  s32 v556;
  SBTLACTAI_WORK *v557;
  f32 v558;
  f32 v559;
  f32 v560;
  f32 v561;
  f32 v562;
  f32 v563;
  f32 v564;
  long f64 v565;
  u32 v567;
  u32 color;
  u32 v569;
  s32 v570;
  uint32x2_t v571;
  s32 v572;
  int8x8_t v573;
  f32 v574;
  SBTLACTAI_WORK *v575;
  f32 v576;
  f32 v577;
  f32 v578;
  f32 v579;
  f32 v580;
  s32 v581;
  float32x2_t v582;
  sdatUnitWork_t *v583;
  f32 v584;
  f32 v585;
  f32 v586;
  long f64 v587;
  s32 v588;
  f32 v590;
  f32 v591;
  SBTLUNIT_LISTWORK *v592;
  s32 v593;
  SBTLUNIT_WORK *v594;
  SBTLUNIT_WORK *v595;
  s32 v596;
  dds3ModelHandle_t *hModel;
  f32 v598;
  s32 v599;
  SBTLACTION_WORK *v600;
  s32 v601;
  f32 v603;
  f32 v604;
  f32 v605;
  SBTLUNIT_LISTWORK *v606;
  s32 v607;
  SBTLUNIT_WORK *v608;
  f32 v609;
  f32 v610;
  f32 v611;
  f32 v612;
  f32 PosToDir;
  f32 Dir180;
  long f64 v615;
  long f64 v616;
  SBTLACTION_WORK *v617;
  SBTLACTION_WORK *v618;
  s32 v619;
  s32 v620;
  s32 v621;
  s32 v622;
  S_CameraMoveDt *g_CamMov_LASTDEAD_R1_0_local;
  __int128 v625;
  f32 v626;
  f32 v627;
  s64 v628;
  f32 v629;
  f32 v630;
  float32x2_t v631;
  __int128 v632;
  f32 v633;
  f32 v634;
  s64 v635;
  f32 v636;
  f32 v637;
  s32 v638;
  f32 v639;
  f32 v640;
  f32 v641;
  f32 v642;
  f32 v643;
  f32 v644;
  f32 v645;
  SBTLUNIT_LISTWORK *v648;
  s32 v649;
  SBTLUNIT_WORK *v650;
  SBTLUNIT_WORK *v651;
  s32 v653;
  SBTLUNIT_LISTWORK *v655;
  SBTLUNIT_WORK *v656;
  SBTLUNIT_WORK *v657;
  s32 v658;
  SBTLUNIT_LISTWORK *v660;
  SBTLUNIT_WORK *v661;
  SBTLUNIT_WORK *v662;
  SBTLUNIT_LISTWORK *v664;
  s32 v665;
  SBTLUNIT_WORK *v666;
  SBTLUNIT_WORK *v667;
  f32 v668;
  f32 v669;
  f32 v670;
  f32 v671;
  f32 v672;
  f32 v673;
  f32 v674;
  s32 v675;
  f32 v676;
  f32 v677;
  SBTLACTAI_WORK *v678;
  f32 v679;
  f32 v680;
  f32 v681;
  s32 v682;
  f32 v684;
  f32 v685;
  long f64 v686;
  f32 v688;
  SBTLACTAI_WORK *v689;
  f32 v691;
  SBTLACTION_WORK *v692;
  s32 v693;
  s32 v694;
  f32 v695;
  SBTLACTAI_WORK *v696;
  f32 v697;
  f32 v698;
  f32 v699;
  s32 v700;
  f32 v702;
  f32 v703;
  long f64 v704;
  s32 v706;
  f32 v707;
  SBTLACTAI_WORK *v708;
  s32 z_low;
  f32 v710;
  s32 v711;
  f32 v712;
  s32 v713;
  f32 v714;
  SBTLACTAI_WORK *v715;
  f32 *v716;
  f32 v717;
  f32 v718;
  f32 v719;
  f32 v720;
  f32 v721;
  f32 v722;
  f32 *p_y;
  f32 *p_z;
  SBTLACTION_WORK *v725;
  s32 v726;
  f32 v727;
  f32 v728;
  s32 v729;
  s32 v730;
  SBTLUNIT_WORK *UnitFromDevilID;
  SBTLACTION_WORK *v732;
  s32 v733;
  s32 v734;
  SBTLACTION_WORK *v735;
  s32 v736;
  s32 v737;
  s32 v738;
  s32 v739;
  s32 v740;
  SBTLUNIT_LISTWORK *v742;
  SBTLUNIT_WORK *v743;
  f32 v744;
  f32 v745;
  s32 v746;
  SBTLUNIT_LISTWORK *v748;
  s32 v749;
  SBTLUNIT_WORK *v750;
  s64 v751;
  f32 v756;
  f32 v757;
  f32 v758;
  f32 v759;
  f32 v760;
  long f64 v761;
  f32 v762;
  s32 v763;
  s32 v764;
  s32 v765;
  SBTLACTION_WORK *v767;
  s32 v768;
  f32 v769;
  f32 v770;
  f32 v771;
  f32 v772;
  f32 v773;
  f32 v774;
  f32 v775;
  s32 v777;
  f32 v778;
  f32 v779;
  f32 v780;
  f32 v781;
  f32 v782;
  f32 v783;
  f32 v784;
  SBTLACTION_WORK *v786;
  s32 v787;
  SBTLSCENE_WORK *scene;
  SBTLCAMERA_WORK *camera;
  S_PosMove *v793;
  S_PosMove *v794;
  f32 v796;
  s32 v797;
  SBTLACTION_WORK *v798;
  SBTLACTION_WORK *v800;
  s32 v801;
  f32 v802;
  u32 v804;
  u32 v805;
  u32 v806;
  u32 v807;
  u32 v808;
  u32 v809;
  s32 v811;
  SBATTLE_WORK *v814;
  SBTLACTION_WORK *v815;
  s32 v817;
  SBTLEFF_LISTWORK *v819;
  s32 v820;
  s32 v821;
  int32x2_t v822;
  u64 v823;
  f32 v824;
  f32 v825;
  f32 v826;
  f32 v827;
  f32 v828;
  f32 v829;
  f32 v830;
  SBTLACTAI_WORK *v831;
  f32 v832;
  f32 v833;
  f32 v834;
  f32 v835;
  f32 v836;
  f32 v837;
  f32 v838;
  f32 v841;
  f32 v842;
  f32 v843;
  long f64 v844;
  long f64 v845;
  SBTLACTAI_WORK *v846;
  f32 v847;
  f32 v848;
  f32 v849;
  f32 v850;
  f32 v851;
  f32 v852;
  f32 v853;
  long f64 v854;
  SBTLUNIT_LISTWORK *v856;
  s32 v857;
  SBTLUNIT_WORK *v858;
  s64 v859;
  f32 v864;
  f32 v865;
  f32 v866;
  f32 v867;
  f32 v868;
  f32 v869;
  long f64 v870;
  long f64 v871;
  s32 v872;
  u32 v873;
  s32 flg;
  u32 v875;
  u32 v876;
  uint32x2_t v877;
  u32 v878;
  int8x8_t v879;
  f32 v880;
  u32 warp_bk_color;
  int32x2_t v882;
  u32 v883;
  u32 v884;
  uint32x2_t v885;
  u64 v886;
  SBTLUNIT_LISTWORK *v888;
  s32 v889;
  SBTLUNIT_WORK *v890;
  SBTLUNIT_WORK *v891;
  SBTLACTION_WORK *v893;
  s32 PointLast;
  f32 v895;
  f32 v896;
  f32 v897;
  f32 v898;
  long f64 v899;
  s64 v900;
  long f64 v901;
  f32 v902;
  long f64 v903;
  long f64 v904;
  SBTLACTION_WORK *v905;
  s32 v906;
  f32 v907;
  f32 v908;
  f32 v909;
  f32 v910;
  long f64 v911;
  s64 v912;
  long f64 v913;
  f32 v914;
  long f64 v915;
  long f64 v916;
  SBTLACTION_WORK *v917;
  s32 v918;
  f32 v919;
  f32 v920;
  f32 v921;
  f32 v922;
  long f64 v923;
  s64 v924;
  long f64 v925;
  f32 v926;
  long f64 v927;
  long f64 v928;
  SBTLACTION_WORK *v929;
  s32 v930;
  f32 v931;
  f32 v932;
  f32 v933;
  f32 v934;
  long f64 v935;
  s64 v936;
  long f64 v937;
  f32 v938;
  long f64 v939;
  long f64 v940;
  SBTLACTION_WORK *v941;
  s32 v942;
  f32 v943;
  f32 v944;
  f32 v945;
  f32 v946;
  long f64 v947;
  s64 v948;
  long f64 v949;
  f32 v950;
  long f64 v951;
  long f64 v952;
  SBTLACTION_WORK *v953;
  SBTLUNIT_WORK *v955;
  SBTLACTION_WORK *v958;
  s32 v959;
  s32 v960;
  s32 v961;
  s64 v963;
  s32 v966;
  s32 v967;
  s32 v969;
  s32 GroupID;
  s16 v971;
  s64 v972;
  f32 v973;
  long f64 v974;
  long f64 v975;
  f32 v976;
  f32 v977;
  f32 v978;
  f32 v979;
  f32 v980;
  f32 v981;
  f32 v982;
  s32 v983;
  SBTLUNIT_LISTWORK *v985;
  SBTLUNIT_WORK *v986;
  s64 v987;
  f32 v992;
  f32 v993;
  f32 v994;
  f32 v995;
  f32 v996;
  f32 v997;
  long f64 v998;
  long f64 v999;
  f32 v1000;
  bool v1003;
  SBTLACTION_WORK *v1004;
  s32 v1005;
  u32 v1006;
  s32 v1007;
  SBTLUNIT_WORK *v1009;
  u32 v1012;
  SBATTLE_WORK *v1013;
  SBTLUNIT_LISTWORK *v1014;
  s32 v1015;
  SBTLUNIT_WORK *v1016;
  SBTLUNIT_WORK *v1017;
  f32 v1018;
  f32 v1019;
  f32 v1020;
  s32 v1022;
  SBATTLE_WORK *v1023;
  u32 *p_stock_mask;
  s32 v1025;
  SBTLSM_LISTWORK *v1027;
  s32 v1028;
  s32 v1029;
  s32 v1030;
  char v1031;
  u32 v1032;
  s32 next_motionID;
  u32 v1043;
  s32 v1044;
  SBATTLE_WORK *v1046;
  SBTLUNIT_LISTWORK *v1047;
  s32 v1048;
  SBTLUNIT_WORK *v1049;
  s32 v1051;
  SBTLSM_LISTWORK *v1052;
  SBATTLE_WORK *v1053;
  s64 v1054;
  SBTLACTION_WORK *v1055;
  s32 v1056;
  s32 v1058;
  SBTLSKILLP_TBL *v1060;
  SBTLEFF_LISTWORK *v1062;
  s32 v1063;
  SBTLEFF_LISTWORK *v1065;
  s32 v1066;
  SBTLEFF_LISTWORK *v1068;
  s32 v1069;
  SBTLSM_LISTWORK *v1071;
  s64 i;
  SBTLUNIT_LISTWORK *v1074;
  SBTLUNIT_WORK *pUnit;
  SBTLSM_LISTWORK *v1077;
  s32 v1078;
  SBTLACTION_WORK *v1079;
  f32 ActionTime;
  s32 v1081;
  s32 sklcng_next_motiontime;
  f32 v1083;
  char v1084;
  u32 v1085;
  s32 framecnt;
  f32 v1087;
  char v1088;
  s32 v1089;
  SBTLACTION_WORK *v1090;
  s32 v1091;
  s32 v1092;
  char v1093;
  s32 v1095;
  s32 v1098;
  SBTLSKILLP_TBL *v1099;
  s32 v1101;
  s32 v1102;
  s32 v1103;
  s32 v1105;
  f32 v1106;
  s32 v1107;
  SBTLSKILLP_TBL *v1110;
  SBTLAI_WORK *v1111;
  s32 cancelCnt;
  s32 v1113;
  s32 v1114;
  f32 v1115;
  f32 v1116;
  f32 v1117;
  f32 v1118;
  f32 v1119;
  f32 v1120;
  f32 v1121;
  SBTLACTION_WORK *v1122;
  bool v1123;
  s32 v1125;
  f32 v1126;
  SBTLEFF_LISTWORK *v1128;
  SBTLACTION_WORK *v1129;
  bool v1130;
  SBATTLE_WORK *v1134;
  SBTLUNIT_LISTWORK *v1135;
  s32 v1136;
  SBTLUNIT_WORK *v1137;
  f32 v1138;
  f32 v1139;
  f32 v1140;
  f32 v1141;
  long f64 v1142;
  s32 *scrCnt;
  s32 v1145;
  s64 v1146;
  s64 v1147;
  long f64 v1148;
  sdfVector4_t *p_scrPos2;
  s64 v1150;
  s64 v1151;
  long f64 v1152;
  SBTLACTAI_WORK *v1153;
  f32 v1154;
  f32 v1155;
  f32 v1156;
  long f64 v1157;
  f32 v1158;
  s64 v1159;
  s64 v1160;
  long f64 v1161;
  SBTLACTAI_WORK *v1162;
  f32 v1163;
  f32 v1164;
  f32 v1165;
  long f64 v1166;
  long f64 v1167;
  f32 v1168;
  s32 v1170;
  s32 v1172;
  SBTLACTAI_WORK *v1173;
  f32 v1174;
  f32 v1175;
  f32 v1176;
  f32 v1177;
  SBTLACTAI_WORK *v1179;
  f32 v1180;
  f32 v1181;
  f32 v1182;
  f32 v1183;
  long f64 v1185;
  s32 v1187;
  SBATTLE_WORK *v1189;
  SBTLACTAI_WORK *v1190;
  SBTLEFF_LISTWORK *effList;
  SBTLACTAI_WORK *v1192;
  f32 v1193;
  f32 v1194;
  f32 v1195;
  f32 v1196;
  long f64 v1197;
  long f64 v1198;
  f32 v1199;
  f32 v1200;
  f32 v1201;
  f32 v1202;
  s64 v1204;
  s64 v1205;
  SBTLACTAI_WORK *v1208;
  f32 v1209;
  f32 v1210;
  f32 v1211;
  f32 v1212;
  char v1224;
  s32 v1225;
  SBTLACTAI_WORK *v1226;
  f32 v1227;
  f32 v1228;
  f32 v1229;
  f32 v1230;
  s32 v1232;
  f32 v1233;
  f32 v1234;
  f32 v1235;
  f32 v1236;
  SBTLSKILLP_TBL *v1238;
  sdatUnitWork_t *para;
  sdatUnitWork_t *v1240;
  u32 BadStatus;
  SBTLUNIT_LISTWORK *v1243;
  s32 v1244;
  SBTLUNIT_WORK *v1245;
  s64 v1246;
  SBTLUNIT_WORK *v1248;
  f32 v1249;
  f32 v1250;
  f32 v1251;
  f32 v1252;
  SBTLACTAI_WORK *v1253;
  f32 v1254;
  f32 v1255;
  f32 v1256;
  f32 v1257;
  long f64 v1258;
  SBTLACTAI_WORK *v1259;
  f32 v1260;
  f32 v1261;
  f32 v1264;
  f32 v1265;
  f32 v1266;
  f32 v1267;
  long f64 v1269;
  s64 v1270;
  long f64 v1271;
  long f64 v1272;
  f32 v1273;
  f32 v1274;
  f32 v1275;
  f32 v1276;
  s64 v1277;
  s64 v1278;
  s32 v1279;
  s64 j;
  SBTLUNIT_LISTWORK *v1282;
  SBTLUNIT_WORK *v1283;
  long f64 v1284;
  long f64 v1285;
  f32 v1286;
  f32 v1287;
  f32 v1288;
  f32 v1289;
  f32 v1290;
  f32 v1291;
  f32 v1292;
  f32 v1293;
  f32 v1294;
  f32 v1295;
  f32 v1296;
  f32 v1297;
  f32 v1298;
  f32 v1299;
  f32 v1300;
  f32 v1301;
  f32 v1302;
  f32 v1303;
  f32 v1304;
  f32 v1305;
  f32 v1306;
  f32 v1307;
  f32 v1308;
  f32 v1309;
  f32 v1310;
  f32 v1311;
  f32 v1312;
  f32 v1313;
  f32 v1314;
  f32 v1315;
  f32 v1316;
  f32 v1317;
  f32 v1318;
  f32 v1319;
  f32 v1320;
  f32 v1321;
  f32 v1322;
  f32 v1323;
  f32 v1324;
  f32 v1325;
  f32 v1326;
  f32 v1327;
  f32 v1328;
  f32 v1329;
  f32 v1330;
  f32 v1331;
  f32 v1332;
  f32 v1333;
  f32 t1;
  f32 t1a;
  f32 t1b;
  f32 t1c;
  f32 t1d;
  f32 t1e;
  f32 t1f;
  f32 t1g;
  f32 t1h;
  f32 t1i;
  f32 t1j;
  struct sdfVector4_t t1_4;
  f32 t1_4a;
  f32 t1_4b;
  s32 t1_4j;
  s32 t1_4k;
  f32 t1_4c;
  f32 t1_4d;
  f32 t1_4e;
  f32 t1_4f;
  f32 t1_4g;
  f32 t1_4h;
  f32 t1_4i;
  struct sdfVector4_t oldpos;
  struct sdfVector4_t oldposa;
  f32 oldposb;
  s64 GetZ;
  sdfVector4_t v1361;
  sdfVector4_t v1362;
  sdfVector4_t rot;
  sdfVector4_t pos;
  s64 v1365;
  s64 v1366;
  s64 v1367;
  s64 v1368;
  sdfVector4_t v1369;
  sdfVector4_t v1370;
  sdfVector4_t v1371;
  sdfVector4_t v1372;
  sdfVector4_t v1373;
  sdfVector4_t v1374;
  sdfVector4_t v1375;
  sdfVector4_t v1376;
  sdfVector4_t v1377;
  sdfVector4_t v1378;
  sdfVector4_t v1379;
  sdfVector4_t v1380;
  sdfVector4_t v1381;
  sdfVector4_t v1382;
  sdfVector4_t v1383;
  sdfVector4_t v1384;
  sdfVector4_t v1385;
  sdfVector4_t v1386;
  sdfVector4_t v1387;
  sdfVector4_t v1388;
  sdfVector4_t v1389;
  sdfVector4_t v1390;
  sdfVector4_t v1391;
  sdfVector4_t v1392;
  sdfVector4_t v1393;
  sdfVector4_t v1394;
  sdfVector4_t v1395;
  sdfVector4_t v1396;
  sdfVector4_t v1397;
  sdfVector4_t v1398;
  sdfVector4_t v1399;
  sdfVector4_t v1400;
  sdfVector4_t v1401;
  sdfVector4_t v1402;
  sdfVector4_t v1403;
  sdfVector4_t v1404;
  sdfVector4_t v1405;
  sdfVector4_t v1406;
  sdfVector4_t v1407;
  sdfVector4_t v1408;
  sdfVector4_t v1409;
  sdfVector4_t v1410;
  sdfVector4_t v1411;
  sdfVector4_t v1412;
  sdfVector4_t v1413;
  sdfVector4_t v1414;
  sdfVector4_t v1415;
  sdfVector4_t v1416;
  sdfVector4_t v1417;
  sdfVector4_t v1418;
  sdfVector4_t v1419;
  sdfVector4_t v1420;
  sdfVector4_t v1421;
  sdfVector4_t v1422;
  sdfVector4_t v1423;
  sdfVector4_t v1424;
  sdfVector4_t v1425;
  sdfVector4_t v1426;
  sdfVector4_t v1427;
  sdfVector4_t v1428;
  sdfVector4_t v1429;
  sdfVector4_t v1430;
  sdfVector4_t v1431;
  sdfVector4_t v1432;
  sdfVector4_t v1433;
  sdfVector4_t v1434;
  sdfVector4_t v1435;
  sdfVector4_t v1436;
  sdfVector4_t v1437;
  sdfVector4_t v1438;
  sdfVector4_t v1439;
  sdfVector4_t v1440;
  sdfVector4_t v1441;
  sdfVector4_t v1442;
  sdfVector4_t v1443;
  sdfVector4_t v1444;
  sdfVector4_t v1445;
  sdfVector4_t v1446;
  sdfVector4_t v1447;
  sdfVector4_t v1448;
  sdfVector4_t v1449;
  sdfVector4_t v1450;
  sdfVector4_t v1451;
  sdfVector4_t v1452;
  sdfVector4_t v1453;
  sdfVector4_t v1454;

  *(u64 *)&v1362.x = 0;
  *(u64 *)&v1362.z = 0;
  GetZ = 0;
  *(u64 *)&v1361.x = 0;
  *(u64 *)&v1361.z = 0;
  v1367 = 0;
  v1368 = 0;
  v1365 = 0;
  v1366 = 0;
  *(u64 *)&pos.x = 0;
  *(u64 *)&pos.z = 0;
  *(u64 *)&rot.x = 0;
  *(u64 *)&rot.z = 0;
  v3 = Allocate(SBTLVISUAL_DATA);
  _ctor(v3, 0);
  motionno = sBtlGetSklVisualTbl(wk->actwk->use_skillid)->motionno;
  v5 = 0;
  if (motionno != 255)
  {
    side = wk->side;
    v5 = sBtlGetMotionNo(wk, side, motionno);
  }
  major = wk->major;
  minor = wk->minor;
  MotionVisualData = sBtlGetMotionVisualData(major, minor, v5);
  if ((wk->side & 0x80) == 0 && (wk->status & 0x800000) == 0 && (wk->vstatus & 0x4000) == 0)
  {
    *(u64 *)&vct_A.x = 0;
    *(u64 *)&vct_A.z = 0;
    p_mv_spd = &wk->mv_spd;
    *p_mv_spd = vct_A;
    goto LABEL_18;
  }
LABEL_18:
  battlemode = (u16)wk->battlemode;
  if (battlemode == 3 || (wk->side & 0x80) == 0)
  {
    if (battlemode != 3)
    {
LABEL_27:
      oldpos = wk->pos;
      vct_A = oldpos;
      p_x = &vf00.x;
      x = p_x[4];
      y = p_x[5];
      z = p_x[6];
      w = p_x[7];
      p_nextpos = &wk->nextpos;
      *p_nextpos = vct_A;
      goto LABEL_49;
    }
    if ((wk->side & 1) == 0)
      goto LABEL_27;
  }
  oldposa = wk->pos;
  vct_A = oldposa;
  v23 = &vf00.x;
  x = v23[4];
  y = v23[5];
  z = v23[6];
  w = v23[7];
LABEL_49:
  p_actwk = &wk->actwk;
  if (!IsSceanStop())
    goto LABEL_101;
  if ((wk->side & 0x80) != 0 && sBtlIsSetsumaPadStop())
  {
    mode = wk->mode;
    if (mode == 14)
      goto LABEL_72;
    mode = wk->mode;
    if (mode == 15)
    {
LABEL_72:
      if (p_actwk->status != 56)
      {
        sBtlCheckMotionMove(wk);
        sBtlMVSupport(wk);
        goto LABEL_420;
      }
      if ((u32)(p_actwk->framecnt - 21) < 0xFFFFFFEF)
        goto LABEL_404;
      targetID = wk->actaiwk->targetID;
      if (targetID == -1)
        goto LABEL_404;
      targetID = wk->actaiwk->targetID;
      UnitMng = wk->UnitMng;
      v33 = sBtlSearchUnit_ID(UnitMng, targetID);
      if (!v33 || (v34 = v33, v33 == wk))
      {
LABEL_404:
        v196 = wk->actaiwk->targetID;
        if (v196 != -1)
        {
          v196 = wk->actaiwk->targetID;
          v198 = wk->UnitMng;
          v199 = sBtlSearchUnit_ID(v198, v196);
          if (v199 && v199 != wk)
          {
            v1448 = wk->rot;
            v1327 = w;
            t1 = x;
            t1_4b = z;
            per = v199->pos.x;
            v206 = wk->pos.x;
            v207 = wk->pos.y;
            v208 = wk->pos.z;
            v209 = wk->pos.w;
            v1309 = wk->rot.y;
            v1316 = wk->rot.x;
            v1295 = wk->rot.w;
            v1302 = wk->rot.z;
            v1448.w = v1295;
            v1448.z = v1302;
            v1448.y = v1309;
            v1448.x = v1316;
            v1377.x = v206;
            v1377.y = v207;
            v1377.z = v208;
            v1377.w = v209;
            *(u64 *)&v1370.x = 0;
            *(u64 *)&v1370.z = v200;
            Radian = sBtlGetRadian(v1377, v1448, v1370, per);
            sBtlAddUnitDeg(wk, Radian);
            *(__n128 *)&v212 = sub_1B335A0(&wk->rot, 0, v211);
            sub_1B335A0(&wk->rotbk, 0, v212);
            RotToDir = sBtlGetRotToDir(wk->rot);
            x = t1;
            z = t1_4b;
            wk->mv_rotbk = sBtlGetDir180(RotToDir);
            w = v1327;
          }
        }
        sBtlMVSupport(wk);
LABEL_420:
        UnitMV(wk);
        v1378.x = x;
        v1378.y = y;
        v1378.z = z;
        v1378.w = w;
        CheckMapHit(wk, v1378);
LABEL_421:
        UnitMV_To_Basic(wk);
        return 0;
      }
      mawari_pos_x = wk->mawari_pos_x;
      HIDWORD(v1367) = 0;
      mawari_pos_z = wk->mawari_pos_z;
      v37 = x;
      v38 = wk->pos.x - mawari_pos_x;
      v39 = wk->pos.z - mawari_pos_z;
      HIDWORD(v1368) = 1065353216;
      v40 = wk->mawari_lr < 0;
      v42 = sqrtf((f32)(v38 * v38) + (f32)(v39 * v39));
      v43 = v38 / v42;
      v44 = v39 / v42;
      v45 = v33->pos.y;
      v46 = v33->pos.w;
      pos.x = mawari_pos_x;
      pos.y = v45;
      pos.z = mawari_pos_z;
      pos.w = v46;
      if (v40)
        v47 = -0.0034906585;
      else
        v47 = 0.0034906585;
      *(f32 *)&v1367 = v43;
      *(f32 *)&v1368 = v44;
      sub_1949280(0, v47);
      *(__n128 *)&v48 = sub_1B332C0(0, v43, 0.0, v44, 1.0);
      v49 = (loc_1EA2510)(0, v48);
      sub_1B335A0(&v1365, 0, v49);
      x = v37;
      v50 = v34->actaiwk->hit_area_r + 50.0;
      v51 = 10.0 - (f32)(v42 - v50);
      if ((f32)(v42 - v50) >= 0.0)
        v51 = -0.0;
      v52 = (f32)(v42 - v50) + v51;
      if (v52 <= 30.0)
      {
        if (v52 <= 14.0)
        {
LABEL_403:
          v193 = v50 + v52;
          v194 = pos.x + (f32)(v193 * *(f32 *)&v1365);
          v195 = pos.z + (f32)(v193 * *(f32 *)&v1366);
          wk->pos.x = v194;
          wk->pos.z = v195;
          goto LABEL_404;
        }
        v53 = -5.0;
      }
      else
      {
        v53 = -10.0;
      }
      v52 = v52 + v53;
      goto LABEL_403;
    }
  }
  if (sBtlIsEnemyLastDeadStop())
  {
    if ((wk->hstatus & 0x8000000) != 0)
      wk->mv_spd.z = -0.5;
    sBtlMVSupport(wk);
    UnitMV(wk);
    goto LABEL_421;
  }
  if ((wk->status & 0x810) == 0)
  {
    wk->mv_rot = 0.0;
    sBtlMVSupport(wk);
    UnitMV(wk);
    if ((wk->side & 2) != 0)
    {
      if (sBtlIsHuuma())
      {
        v80 = wk;
        v81 = v80->UnitMng;
        playerID = v80->playerID;
        if (wk->ListID == sBtlSearchUnit_ID(v81, playerID)->actaiwk->targetID)
        {
          v1375.x = x;
          v1375.y = y;
          v1375.z = z;
          v1375.w = w;
          CheckMapHit(wk, v1375);
        }
      }
    }
    if ((~wk->side & 0x81) == 0)
    {
      if (get_Instance(0)->sc_pause)
        goto LABEL_2973;
      v156 = wk->mode;
      if (v156 == 12 || v156 == 5)
      {
LABEL_2973:
        v1376.x = x;
        v1376.y = y;
        v1376.z = z;
        v1376.w = w;
        CheckMapHit(wk, v1376);
        v83 = x;
        v84 = wk->pos.z;
        v85 = wk->pos.x;
        if (sBtlGetLenXZ(v85, v84, v83, z) < 1.0)
        {
          wk->pos.x = v83;
          wk->pos.z = z;
        }
      }
    }
    goto LABEL_421;
  }
LABEL_101:
  if (wk->bStop)
    return 0;
  if (IsSceanStop())
  {
    goto LABEL_105;
  }
  damage_eff_tgt_cnt = wk->damage_eff_tgt_cnt;
  v56 = __OFSUB__(damage_eff_tgt_cnt, 1);
  v57 = damage_eff_tgt_cnt - 1;
  if (v57 < 0 == v56)
    wk->damage_eff_tgt_cnt = v57;
  damage_eff_rai_cnt = wk->damage_eff_rai_cnt;
  v56 = __OFSUB__(damage_eff_rai_cnt, 1);
  v59 = damage_eff_rai_cnt - 1;
  if (v59 < 0 == v56)
    wk->damage_eff_rai_cnt = v59;
  damage_fuka_tgt_cnt = wk->damage_fuka_tgt_cnt;
  v56 = __OFSUB__(damage_fuka_tgt_cnt, 1);
  v61 = damage_fuka_tgt_cnt - 1;
  if (v61 < 0 == v56)
    wk->damage_fuka_tgt_cnt = v61;
  wk->YukaDamageSkipCnt = (wk->YukaDamageSkipCnt - 1) & ~((wk->YukaDamageSkipCnt - 1) >> 31);
LABEL_105:
  if ((wk->status2 & 0x80000) != 0)
    goto LABEL_119;
  if (!tipsProcessCheck())
  {
    if (!IsSceanStop())
    {
      if (wk->cmbSkl->bRun)
      {
        if (wk->damagecnt >= 1)
        {
          v87 = (u16)wk->damagecnt - 1;
          wk->damagecnt = v87;
          if (!v87)
          {
            wk->damagecnt = 0;
            wk->damage_hitcnt = 0;
          }
        }
        goto LABEL_119;
      }
    }
    if (!IsSceanStop())
    {
      v89 = wk;
      if (!v89->sklProc->bRun)
      {
        v89 = wk;
        if (!v89->cmbSkl->bRun)
        {
          v89 = wk;
          if (!v89->kaiwaflg)
            goto LABEL_222;
        }
      }
    }
    if (sBtlCheckPlayerDead())
    {
LABEL_222:
      katana_hit_cnt = wk->katana_hit_cnt;
      v56 = __OFSUB__(katana_hit_cnt, 1);
      v91 = katana_hit_cnt - 1;
      if (v91 < 0 == v56)
        wk->katana_hit_cnt = v91;
      if (wk->damagecnt >= 1)
      {
        v92 = (u16)wk->damagecnt - 1;
        wk->damagecnt = v92;
        if (!v92)
        {
          wk->damagecnt = 0;
          wk->damage_hitcnt = 0;
        }
      }
      yuka_damagecnt = wk->yuka_damagecnt;
      v56 = __OFSUB__(yuka_damagecnt, 1);
      v94 = yuka_damagecnt - 1;
      if (v94 < 0 == v56)
        wk->yuka_damagecnt = v94;
      nguard_dmgcnt = wk->nguard_dmgcnt;
      v56 = __OFSUB__(nguard_dmgcnt, 1);
      v96 = nguard_dmgcnt - 1;
      if (v96 < 0 == v56)
        wk->nguard_dmgcnt = v96;
      hangeki_nokezoranai = wk->hangeki_nokezoranai;
      v56 = __OFSUB__(hangeki_nokezoranai, 1);
      v98 = hangeki_nokezoranai - 1;
      if (v98 < 0 == v56)
        wk->hangeki_nokezoranai = v98;
      hangeki_notjyakuten = wk->hangeki_notjyakuten;
      v56 = __OFSUB__(hangeki_notjyakuten, 1);
      v100 = hangeki_notjyakuten - 1;
      if (v100 < 0 == v56)
        wk->hangeki_notjyakuten = v100;
      if (wk->hangeki_endcnt < 1)
        goto LABEL_247;
      motionID = wk->motionID;
      if (motionID == 1 || motionID == 14)
        goto LABEL_247;
      if (!wk->hangeki_st_done)
      {
        devilid = wk->para->devilid;
        DevilSESub = sBtlGetDevilSESub(devilid, 14);
        sBtlPlay3DSE(DevilSESub, wk->pos);
        wk->hangeki_st_done = 1;
      }
      if ((wk->hstatus & 0x10) != 0 || (v104 = p_actwk->status, v104 <= 0x1F) && ((1 << v104) & 0x80000048) != 0)
      {
        if (wk->hangeki_endcnt)
          goto LABEL_247;
      }
      else
      {
        v226 = wk->hangeki_endcnt - 1;
        wk->hangeki_endcnt = v226;
        if (v226)
        {
LABEL_247:
          if ((wk->side & 1) != 0 && wk->damagecnt >= 1)
          {
            sBtlMutekiProc(wk);
          }
          aiwk = wk->aiwk;
          syscnt_stop = aiwk->syscnt_stop;
          p_syscnt_stop = &aiwk->syscnt_stop;
          *p_syscnt_stop = syscnt_stop + 1;
          LimitRange(p_syscnt_stop, 0, 99999);
          damage_guncnt = wk->damage_guncnt;
          v110 = damage_guncnt - 1;
          if (damage_guncnt >= 1)
          {
            --damage_guncnt;
            wk->damage_guncnt = v110;
          }
          if (!damage_guncnt)
            wk->damage_gunnum = 0;
          damage_1stmotcnt = wk->damage_1stmotcnt;
          v112 = damage_1stmotcnt - 1;
          if (damage_1stmotcnt >= 1)
          {
            --damage_1stmotcnt;
            wk->damage_1stmotcnt = v112;
          }
          if (!damage_1stmotcnt)
            wk->damage_1stmotnum = 0;
          eff_wait_mukou = wk->eff_wait_mukou;
          v56 = __OFSUB__(eff_wait_mukou, 1);
          v114 = eff_wait_mukou - 1;
          if (v114 < 0 == v56)
            wk->eff_wait_mukou = v114;
          eff_wait_kyushu = wk->eff_wait_kyushu;
          v56 = __OFSUB__(eff_wait_kyushu, 1);
          v116 = eff_wait_kyushu - 1;
          if (v116 < 0 == v56)
            wk->eff_wait_kyushu = v116;
          eff_wait_guard = wk->eff_wait_guard;
          v56 = __OFSUB__(eff_wait_guard, 1);
          v118 = eff_wait_guard - 1;
          if (v118 < 0 == v56)
            wk->eff_wait_guard = v118;
          eff_wait_kaisin = wk->eff_wait_kaisin;
          v56 = __OFSUB__(eff_wait_kaisin, 1);
          v120 = eff_wait_kaisin - 1;
          if (v120 < 0 == v56)
            wk->eff_wait_kaisin = v120;
          vice_kaisin_cnt = wk->vice_kaisin_cnt;
          v56 = __OFSUB__(vice_kaisin_cnt, 1);
          v122 = vice_kaisin_cnt - 1;
          if (v122 < 0 == v56)
          {
            wk->vice_kaisin_cnt = v122;
            if (!v122)
              wk->vice_kaisin_flg = 0;
          }
          wkKaja = wk->wkKaja;
          v124 = wkKaja[0];
          v125 = v124[0];
          m_cnt = v125->m_cnt;
          v56 = __OFSUB__(m_cnt, 1);
          v127 = m_cnt - 1;
          if (v127 < 0 == v56)
          {
            v125->m_cnt = v127;
            if (!v127)
              v125->m_fPara = 0.0;
          }
          v128 = v124[1];
          v129 = v128->m_cnt;
          v56 = __OFSUB__(v129, 1);
          v130 = v129 - 1;
          if (v130 < 0 == v56)
          {
            v128->m_cnt = v130;
            if (!v130)
              v128->m_fPara = 0.0;
          }
          v131 = wkKaja[1];
          v132 = v131[0];
          v133 = v132->m_cnt;
          v56 = __OFSUB__(v133, 1);
          v134 = v133 - 1;
          if (v134 < 0 == v56)
          {
            v132->m_cnt = v134;
            if (!v134)
              v132->m_fPara = 0.0;
          }
          v135 = v131[1];
          v136 = v135->m_cnt;
          v56 = __OFSUB__(v136, 1);
          v137 = v136 - 1;
          if (v137 < 0 == v56)
          {
            v135->m_cnt = v137;
            if (!v137)
              v135->m_fPara = 0.0;
          }
          v138 = wkKaja[2];
          v139 = v138[0];
          v140 = v139->m_cnt;
          v56 = __OFSUB__(v140, 1);
          v141 = v140 - 1;
          if (v141 < 0 == v56)
          {
            v139->m_cnt = v141;
            if (!v141)
              v139->m_fPara = 0.0;
          }
          v142 = v138[1];
          v143 = v142->m_cnt;
          v56 = __OFSUB__(v143, 1);
          v144 = v143 - 1;
          if (v144 < 0 == v56)
          {
            v142->m_cnt = v144;
            if (!v144)
              v142->m_fPara = 0.0;
          }
          o_atk_up_time = wk->o_atk_up_time;
          v56 = __OFSUB__(o_atk_up_time, 1);
          v146 = o_atk_up_time - 1;
          if (v146 < 0 == v56)
            wk->o_atk_up_time = v146;
          o_def_dn_time = wk->o_def_dn_time;
          v56 = __OFSUB__(o_def_dn_time, 1);
          v148 = o_def_dn_time - 1;
          if (v148 < 0 == v56)
            wk->o_def_dn_time = v148;
          v149 = wk->wkKarn[0];
          v150 = v149->m_cnt;
          v56 = __OFSUB__(v150, 1);
          v151 = v150 - 1;
          if (v151 < 0 == v56)
          {
            v149->m_cnt = v151;
            if (!v151)
            {
              v149->m_skillid = 0;
              if ((wk->side & 1) != 0)
              {
                if (v153)
                {
                  m_skillid = 0;
                }
                else
                {
                  m_skillid = wk->wkKarn[0]->m_skillid;
                }
                sysmsgList = wk->sysmsgList;
                t1_4k = m_skillid;
                m_skillid = t1_4k;
                v219 = 150;
              }
              else
              {
                if (v153)
                {
                  m_skillid = 0;
                }
                else
                {
                  m_skillid = wk->wkKarn[0]->m_skillid;
                }
                sysmsgList = wk->sysmsgList;
                t1_4j = m_skillid;
                m_skillid = t1_4j;
                v219 = 151;
              }
              sBtlCreateSM(sysmsgList, wk, v219, m_skillid, 0, 120);
            }
          }
          hstatus = wk->hstatus;
          if ((hstatus & 0x200000) != 0)
            ++wk->WeakAtkCnt;
          if ((hstatus & 0x10) == 0 && wk->WeakReceiveFlg)
          {
            ++wk->WeakReceiveCnt;
            ++wk->weak_attrinvtime_cnt;
          }
          noWeakStfCnt = wk->noWeakStfCnt;
          if (noWeakStfCnt)
          {
            v222 = noWeakStfCnt - 1;
            wk->noWeakStfCnt = v222;
            if (!v222)
            {
              wk->getMag = 0;
              wk->hstatus = hstatus & 0xFFFFFFEF;
            }
          }
          if (CheckLiveTarget(wk))
          {
            v224 = wk;
            status = v224->status;
            if ((status & 8) == 0 && (wk->actaiwk->status & 0x4000) == 0 && (wk->status & 0x5000) != 0x4000)
            {
              v224 = wk;
              status = v224->status;
              if ((status & 0x1000000) == 0)
              {
                v224 = wk;
                if ((v224->status2 & 2) == 0 && p_actwk->status != 42)
                {
                  CalcBadStatus(wk);
                  if (wk->para->now->hp >= 1)
                  {
                    CalcBtlMagicStatus(wk);
                  }
                }
              }
            }
          }
          goto LABEL_119;
        }
      }
      wk->hangeki_st_done = 0;
      *(_OWORD *)&wk->hangeki_on = 0u;
      goto LABEL_247;
    }
  }
LABEL_119:
  v62 = (u16)wk->damage_actionf - 1;
  if (v62 << 16 <= 0)
    LOWORD(v62) = 0;
  wk->damage_actionf = v62;
  actwk = wk->actwk;
  if (actwk->status != 9)
    goto LABEL_132;
  v65 = wk;
  if (!v65->cmbSkl->bRun)
  {
    v65 = wk;
    if (!v65->sklProc->bRun)
    {
      v65 = wk;
      if (!v65->kaiwaflg)
      {
        actwk = p_actwk;
LABEL_132:
        v66 = vadd_s32(*(int32x2_t *)&actwk->framecnt, (int32x2_t)0x100000001LL).n64_u64[0];
        ++actwk->framecntC;
        *(u64 *)&actwk->framecnt = v66;
      }
    }
  }
  p_framecnt = &p_actwk->framecnt;
  LimitRange(p_framecnt, 0, 0x7FFF);
  LimitRange(&wk->actwk->framecntB, 0, 0x7FFF);
  LimitRange(&wk->actwk->framecntC, 0, 0x7FFF);
  t1_4 = wk->rot;
  vct_A = t1_4;
  oldposb = y;
  v70 = &vf00.x;
  v71 = v70[4];
  v72 = v70[5];
  v73 = v70[6];
  v74 = v70[7];
  if ((wk->side & 0x81) == 1 && wk->aiwk->mode != 17)
    wk->status &= ~0x100u;
  mv_rotbk = wk->mv_rotbk;
  if (p_actwk->status != 56)
  {
    sBtlCheckMotionMove(wk);
  }
  if (!wk->bYobidousa)
    goto LABEL_344;
  v77 = wk;
  if (v77->sklProc->bRun)
    goto LABEL_344;
  v77 = wk;
  v77->status4 &= ~0x1000u;
  yobidousaCnt = wk->yobidousaCnt;
  if (yobidousaCnt >= 178)
  {
    yobidousaCnt = wk->yobidousaCnt;
    v77 = wk;
    v77->NotCnt_R1R2 = 6;
    if (yobidousaCnt >= 180)
    {
      if (g_aTimeStopSkl[wk->timeStopID]->sklID == 890)
      {
        AnotherEnemy = sBtlGetAnotherEnemy(wk);
        sBtlForceDelete_SkillFlag_Acter(AnotherEnemy, 0x400u);
      }
      if (g_aTimeStopSkl[wk->timeStopID]->ptn == 3)
      {
        sBtlForceDelete_SkillFlag_Acter(wk, 0x400u);
        wk->actcounter = wk->actcounter_max;
        v160 = wk->actwk;
        sklID = g_aTimeStopSkl[wk->timeStopID]->sklID;
        v160->use_skillid = sklID;
        sBtlSetAIMode(wk);
        actaiwk = wk->actaiwk;
        actaiwk->stat = 2;
        wk->aiwk->stat = 2;
        actaiwk->mode = 15;
        v165 = wk->sysmsgList;
        v165->bLock = 0;
        sBtlReleaseSM_List(v165, 1u);
        v166 = wk->actwk;
        wk->bYobi2Nml = 1;
        sBtlSetUseSkill(wk, v166->use_skillid, 0);
        wk->bYobidousa = 0;
        sBtlCreateSM(wk->sysmsgList, wk, 10, g_aTimeStopSkl[wk->timeStopID]->sklID, 0, 120);
        wk->sysmsgList->bLock = 1;
        goto LABEL_334;
      }
      if (sBtlCheckPlayerDead())
      {
        wk->timeStopID = 0;
LABEL_331:
        v169 = wk->sysmsgList;
        v169->bLock = 0;
        sBtlReleaseSM_List(v169, 1u);
        goto LABEL_334;
      }
      ListID = wk->ListID;
      timeStopID = wk->timeStopID;
      StartSklProc(ListID, timeStopID);
      wk->timeStopID = 0;
      goto LABEL_331;
    }
  }
  if ((p_actwk->use_skillid | 0x80) == 0x3EA)
  {
    if (sBtlCheckMotionEnd(wk))
    {
      sBtlSetMotion(wk, 29, 4, 0, 0);
    }
  }
LABEL_334:
  if (!wk->cmbSkl->bRun)
  {
    if (!IsSceanStop())
    {
      if (!wk->kaiwaflg)
        ++wk->yobidousaCnt;
    }
  }
LABEL_344:
  if (p_actwk->status == 10 && (wk->aiwk->scrflag & 0x60000) == 0x20000)
  {
    sBtlStartDeadEvent(wk);
    wk->actwk->action_flg = 1;
    wk->DeadEventDone = 1;
    if (sBtlCheckSetsuma() && (wk->motionID | 2) == 2)
    {
      sBtlSetMotion(wk, 14, 0, 0, 0);
    }
    if (sBtlPlayerCheckRSpirit())
    {
      if ((wk->hstatus & 0x8000000) != 0 || (v172 = (u16)wk->para->devilid, v172 == 291) || v172 == 169)
      {
        wk->BtlEnd_Boss_Sprit = 1;
      }
    }
  }
  if ((wk->side & 0x82) == 2)
  {
    if (!wk->cmbSkl->bRun)
    {
      v175 = wk->aiwk;
      if (!v175->bWait && !v175->bWait2 && !wk->bYobidousa && !wk->bYobi2Nml)
      {
        sBtlProcScript(wk);
      }
    }
  }
  v176 = wk->aiwk;
  cmndFrm = v176->cmndFrm;
  if (cmndFrm && v176->bCmndEnd)
    v176->cmndFrm = cmndFrm - 1;
  if ((wk->status2 & 0x80000) == 0)
  {
    if (!IsSceanStop())
    {
      v180 = wk;
      if (!v180->cmbSkl->bRun)
      {
        v180 = wk;
        if (!v180->kaiwaflg)
        {
          v180 = wk;
          if (!v180->endcnt && (wk->side & 0x81) == 1)
          {
            if (sBtlGetNakama(0) && sBtlGetNakama(1) && p_actwk->status - 1 <= 1)
            {
              Nakama = sBtlGetNakama(0);
              v182 = sBtlGetNakama(Nakama == wk);
              v183 = v182;
              v1301 = v182->pos.w;
              v184 = wk->pos.x;
              t1_4a = v182->pos.x;
              v1308 = v182->pos.z;
              v1315 = v182->pos.y;
              v185 = t1_4a - v184;
              v186 = wk->pos.z;
              v187 = v1308 - v186;
              v188 = sqrtf((f32)(v185 * v185) + (f32)(v187 * v187));
              if (v188 > 1.0)
              {
                v189 = v182->actaiwk->hit_area_r + wk->actaiwk->hit_area_r;
                if (v188 < v189)
                {
                  v190 = v185 / v188;
                  v191 = v187 / v188;
                  if (wk->miusinai || (wk->aiwk->m_status & 0x40000) != 0)
                  {
                    if ((f32)(v189 - v188) > 10.0)
                    {
                      wk->pos.x = v184 - (f32)(v190 * 4.0);
                      wk->pos.z = v186 - (f32)(v191 * 4.0);
                    }
                  }
                  else
                  {
                    v192 = v191 + v191;
                    wk->pos.x = v184 - (f32)(v190 + v190);
                    wk->pos.z = v186 - v192;
                    v182->pos.x = (f32)(v190 + v190) + v182->pos.x;
                    v182->pos.z = v192 + v182->pos.z;
                  }
                }
              }
              v1379.y = oldposb;
              v1379.x = x;
              v1379.z = z;
              v1379.w = w;
              CheckMapHit(wk, v1379);
              v1380.x = t1_4a;
              v1380.z = v1308;
              v1380.y = v1315;
              v1380.w = v1301;
              CheckMapHit(v183, v1380);
            }
            if ((sBtlGetNakama(0) == wk || sBtlGetNakama(1) == wk) && p_actwk->status - 1 <= 1)
            {
              v228 = wk;
              v229 = v228->UnitMng;
              v230 = v228->playerID;
              v231 = sBtlSearchUnit_ID(v229, v230);
              v232 = wk->pos.x;
              v233 = v231->pos.x - v232;
              v234 = wk->pos.z;
              v235 = v231->pos.z - v234;
              v236 = sqrtf((f32)(v233 * v233) + (f32)(v235 * v235));
              if (v236 > 1.0 && v236 < (f32)(wk->actaiwk->hit_area_r + 50.0) && (!wk->miusinai && (wk->aiwk->m_status & 0x40000) == 0 || v236 < 40.0))
              {
                wk->pos.x = v232 - (f32)((f32)(v233 / v236) * 4.0);
                wk->pos.z = v234 - (f32)((f32)(v235 / v236) * 4.0);
              }
              v1381.y = oldposb;
              v1381.x = x;
              v1381.z = z;
              v1381.w = w;
              CheckMapHit(wk, v1381);
            }
          }
        }
      }
    }
  }
  v237 = p_actwk;
  v214 = 1;
  p_asimoto_pos_x = &wk->asimoto_pos_x;
  switch (p_actwk->status)
  {
    case 0u:
    case 1u:
    case 2u:
    case 0x2Au:
      Proc(wk);
      v239 = oldposb;
      goto LABEL_497;
    case 3u:
      use_skillid = v237->use_skillid;
      sBtlSetSuperArmor(wk, use_skillid, -2);
      Skilltbl = sBtlGetSkilltbl(wk->actwk->use_skillid);
      if (Skilltbl && (Skilltbl->flg2 & 0x80000) != 0)
        goto LABEL_1669;
      v251 = wk->side;
      if ((v251 & 0x81) == 1)
      {
        v252 = wk->actaiwk->targetID;
        if (v252 != -1)
        {
          v252 = wk->actaiwk->targetID;
          v254 = wk->UnitMng;
          v255 = sBtlSearchUnit_ID(v254, v252);
          if (v255)
          {
            v256 = v255;
            if (v255 != wk)
            {
              SetAtkDirHD(wk, v256, 45.0, 4.0);
              v257 = wk->pos.x;
              v258 = v256->pos.x - v257;
              v259 = wk->pos.z;
              v260 = v256->pos.z - v259;
              v261 = sqrtf((f32)(v258 * v258) + (f32)(v260 * v260));
              if ((f32)(v261 - (f32)(v256->actaiwk->hit_area_r + MotionVisualData->m_mv_area_r)) > 5.0)
              {
                h_attack_move_len = wk->h_attack_move_len;
                if (h_attack_move_len < 150.0)
                {
                  wk->pos.x = (f32)((f32)(v258 / v261) * 5.0) + v257;
                  wk->pos.z = (f32)((f32)(v260 / v261) * 5.0) + v259;
                  v263 = h_attack_move_len + 5.0;
LABEL_553:
                  wk->h_attack_move_len = v263;
                }
              }
            }
          }
        }
      }
      else if ((v251 & 2) != 0)
      {
        v600 = p_actwk;
        v601 = p_actwk->use_skillid;
        if ((u32)(v601 - 453) > 4)
        {
          if (wk->actaiwk->targetID != -1 && v601 != 1091 && v601 != 1110 && (u32)(v600->framecnt - 31) >= 0xFFFFFFE6)
          {
            v744 = x;
            if (!sBtlChkKaihiMawari(wk))
            {
              v1243 = wk->UnitMng;
              v1244 = wk->actaiwk->targetID;
              v1245 = sBtlSearchUnit_ID(v1243, v1244);
              if (v1245)
              {
                v1248 = v1245;
                if (v1245 != wk)
                {
                  t1_4i = wk->pos.x;
                  v1314 = wk->pos.z;
                  v1326 = wk->pos.y;
                  v1300 = wk->rot.x;
                  v1307 = wk->pos.w;
                  v1249 = wk->rot.w;
                  v1250 = v1245->pos.x;
                  v1293 = wk->rot.z;
                  v1294 = wk->rot.y;
                  v1446.x = t1_4i;
                  v1453.w = v1249;
                  v1446.z = v1314;
                  v1446.y = v1326;
                  v1453.x = v1300;
                  v1446.w = v1307;
                  v1453.z = v1293;
                  v1453.y = v1294;
                  *(u64 *)&v1374.x = 0;
                  *(u64 *)&v1374.z = v1246;
                  v1251 = sBtlGetRadian(v1446, v1453, v1374, v1250);
                  x = v744;
                  if (v1251 > -90.0 && v1251 < 90.0)
                  {
                    if (p_actwk->total_homing < 80.0)
                    {
                      if (v1251 < -40.0)
                        v1251 = -40.0;
                      if (v1251 <= 40.0)
                        v1252 = v1251 / 10.0;
                      else
                        v1252 = 4.0;
                      sBtlAddUnitDeg(wk, v1252);
                      *(__n128 *)&v1285 = sub_1B335A0(&wk->rot, 0, v1284);
                      sub_1B335A0(&wk->rotbk, 0, v1285);
                      v1286 = -v1252;
                      if (v1252 >= 0.0)
                        v1286 = v1252;
                      wk->actwk->total_homing = wk->actwk->total_homing + v1286;
                    }
                    v1287 = wk->pos.x;
                    x = v744;
                    v1288 = v1248->pos.x - v1287;
                    v1289 = wk->pos.z;
                    v1290 = v1248->pos.z - v1289;
                    v1291 = sqrtf((f32)(v1288 * v1288) + (f32)(v1290 * v1290));
                    if ((f32)(v1291 - (f32)(v1248->actaiwk->hit_area_r + MotionVisualData->m_mv_area_r)) > 10.0)
                    {
                      v1292 = wk->h_attack_move_len;
                      if (v1292 < 100.0)
                      {
                        wk->pos.x = (f32)((f32)(v1288 / v1291) * 5.0) + v1287;
                        wk->pos.z = (f32)((f32)(v1290 / v1291) * 5.0) + v1289;
                        v263 = v1292 + 5.0;
                        goto LABEL_553;
                      }
                    }
                  }
                }
              }
            }
          }
        }
        else if (v600->framecnt == 1)
        {
          if (!sBtlChkKaihiMawari(wk))
          {
            v603 = x;
            v604 = w;
            v605 = z;
            v606 = wk->UnitMng;
            v607 = wk->actaiwk->targetID;
            v608 = sBtlSearchUnit_ID(v606, v607);
            if (v608 && v608 != wk)
            {
              v609 = wk->pos.x;
              v610 = wk->pos.z;
              v611 = v608->pos.x;
              v612 = v608->pos.z;
              PosToDir = sBtlGetPosToDir(v609, v610, v611, v612);
              Dir180 = sBtlGetDir180(PosToDir);
              wk->mv_rotbk = Dir180;
              FromEuler(0.0, Dir180 * 0.017453292, 0.0);
              *(__n128 *)&v616 = sub_1B335A0(&wk->rot, 0, v615);
              sub_1B335A0(&wk->rotbk, 0, v616);
              wk->front_deg = PosToDir;
              z = v605;
              w = v604;
              x = v603;
            }
          }
        }
      }
LABEL_1669:
      v745 = oldposb;
      v746 = p_actwk->use_skillid;
      if ((v746 == 1110 || v746 == 1091) && (u32)(p_actwk->framecnt - 211) >= 0xFFFFFF73)
      {
        if (!sBtlChkKaihiMawari(wk))
        {
          v748 = wk->UnitMng;
          v749 = wk->actaiwk->targetID;
          v750 = sBtlSearchUnit_ID(v748, v749);
          if (v750)
          {
            t1b = x;
            v1417 = wk->pos;
            v756 = wk->rot.x;
            v757 = wk->rot.y;
            v758 = wk->rot.z;
            v759 = wk->rot.w;
            v760 = v750->pos.x;
            v1310 = wk->pos.y;
            v1317 = wk->pos.x;
            v1296 = wk->pos.w;
            v1303 = wk->pos.z;
            v1417.w = v1296;
            v1417.z = v1303;
            v1417.y = v1310;
            v1417.x = v1317;
            v1449.x = v756;
            v1449.y = v757;
            v1449.z = v758;
            v1449.w = v759;
            *(u64 *)&v1371.x = 0;
            *(u64 *)&v1371.z = v751;
            *(f32 *)&v761 = sBtlGetRadian(v1417, v1449, v1371, v760);
            x = t1b;
            v745 = oldposb;
            if (*(f32 *)&v761 > -90.0 && *(f32 *)&v761 < 90.0)
            {
              if (*(f32 *)&v761 < -20.0)
                *(f32 *)&v761 = -20.0;
              if (*(f32 *)&v761 <= 20.0)
                v762 = *(f32 *)&v761 / 3.0;
              else
                v762 = 6.6666665;
              sub_1B335A0(&wk->rot, 0, v761);
              sBtlAddUnitDeg(wk, v762);
            }
          }
        }
      }
      v1079 = p_actwk;
      if (p_actwk->framecnt <= 1)
      {
        v1079->sklcng_use_skillid = v1079->use_skillid;
        ActionTime = sBtlGetActionTime(wk, 0);
        v1081 = ActionTime;
        if (ActionTime == INFINITY)
          v1081 = 0x80000000;
        v1079->sklcng_next_motiontime = v1081;
        v1079 = wk->actwk;
      }
      if (v1079->sklcng_use_skillid != v1079->use_skillid)
        goto LABEL_2420;
      sklcng_next_motiontime = v1079->sklcng_next_motiontime;
      v1083 = sBtlGetActionTime(wk, 0);
      v1084 = 0;
      v1085 = v1083 == INFINITY ? 0x80000000 : (s32)v1083;
      if (sklcng_next_motiontime != v1085)
LABEL_2420:
        v1084 = 1;
      framecnt = p_actwk->framecnt;
      v1087 = sBtlGetActionTime(wk, 0);
      if (v1087 == INFINITY || framecnt >= (s32)v1087)
      {
        v1088 = p_actwk->action_flg ? 1 : v1084;
        if ((v1088 & 1) == 0)
        {
          v1089 = p_actwk->use_skillid;
          if (sBtlHDloadChk(v1089))
          {
            if ((wk->side & 0x81) == 1)
            {
              sBtlCheckCost(wk, 2);
            }
            v1090 = p_actwk;
            v1091 = p_actwk->use_skillid;
            if (v1091)
              wk->aiwk->usedSkl = v1091;
            v1090->action_flg = 1;
            CheckSkillMessage(wk, v1091);
            v1092 = wk->actwk->use_skillid;
            if (sBtlSearchEffectData(v1092) == -1)
            {
              sBtlForceDelete_SkillFlag_Acter(wk, 0x400u);
            }
            else
            {
              sBtlSetSkill_EffectData(wk, wk->actwk->use_skillid, 0);
              if (wk->actwk->use_skillid == 884)
              {
                sBtlSetFade(wk, 2, 0, 0, 16);
              }
            }
            if (p_actwk->use_skillid == 886)
            {
              sBtlSetFade(wk, 1, 0, 0, 16);
            }
          }
        }
      }
      Proc(wk);
      sBtlProc(wk);
      sBtlMVSupport(wk);
      UnitMV(wk);
      v1435.x = x;
      v1435.y = v745;
      v1435.z = z;
      v1435.w = w;
      CheckMapHit(wk, v1435);
      UnitMV_To_Basic(wk);
      if (!sBtlCheckNextAction(wk))
        return 1;
      v1093 = wk->side;
      wk->hangeki_notjyakuten = 0;
      if ((v1093 & 2) != 0)
      {
        wk->NotCmbSkl_Ex = 0;
      }
      v1095 = p_actwk->use_skillid;
      if (v1095 > 1089)
      {
        if ((u32)v1095 > 0x4CC)
        {
          if (v1095 != 1264)
          {
            if (v1095 == 1265)
            {
              wk->flg &= ~2u;
              wk->status &= 0xFEFFFFFE;
              sBtlSetBossMode(0);
              wk->not_tatezan = 0;
              *(u64 *)&wk->kuramasi = 0;
              sBtlLockOnFree(wk);
            }
            goto LABEL_2499;
          }
          wk->status |= 0x1000001u;
          v1098 = 1;
LABEL_2498:
          sBtlSetBossMode(v1098);
          *(u64 *)&wk->kuramasi = 0x100000001LL;
          goto LABEL_2499;
        }
        if (v1095 != 1090)
        {
          if (v1095 != 1109)
            goto LABEL_2499;
          goto LABEL_2489;
        }
LABEL_2488:
        wk->flg &= ~2u;
        wk->status &= 0xFEFFFFFE;
        *(u64 *)&wk->kuramasi = 0;
        wk->not_tatezan = 0;
LABEL_2489:
        sBtlSetBossMode(0);
        goto LABEL_2499;
      }
      if (v1095 <= 886)
      {
        if (v1095 != 868)
        {
          if (v1095 != 869)
          {
            if (v1095 == 886)
              wk->flg &= ~2u;
LABEL_2499:
            p_actwk->status = 2;
            ResetAction(wk);
            sBtlEndAction(wk);
            v1099 = sBtlGetSkilltbl(wk->actwk->use_skillid);
            if (v1099)
            {
              if ((v1099->flg2 & 0x100) != 0)
              {
                v214 = 1;
                wk->flg |= 0x20u;
              }
              else
              {
                sBtlSetUseSkill(wk, 0, 0);
                return 1;
              }
              return v214;
            }
            return 1;
          }
          goto LABEL_2488;
        }
      }
      else if (v1095 != 996)
      {
        if (v1095 == 997)
          goto LABEL_2488;
        if (v1095 != 1089)
          goto LABEL_2499;
      }
      wk->status |= 0x1000001u;
      v1098 = 2;
      goto LABEL_2498;
    case 6u:
      v264 = x;
      v265 = v237->use_skillid;
      sBtlSetSuperArmor(wk, v265, -2);
      if (wk->actwk->action_flg)
        goto LABEL_557;
      v588 = wk->side;
      if ((v588 & 1) != 0)
      {
        v658 = wk->actaiwk->targetID;
        if (v658 != -1)
        {
          v658 = wk->actaiwk->targetID;
          v660 = wk->UnitMng;
          v661 = sBtlSearchUnit_ID(v660, v658);
          if (v661)
          {
            v662 = v661;
            if (v661 != wk)
            {
              SetAtkDirHD(wk, v662, 45.0, 2.0);
            }
          }
        }
      }
      else
      {
        if ((wk->status & 0x100000) == 0)
        {
          if ((v588 & 2) == 0 || wk->actaiwk->targetID == -1)
            goto LABEL_557;
          if (sBtlChkKaihiMawari(wk))
            goto LABEL_557;
          v590 = w;
          v591 = z;
          v592 = wk->UnitMng;
          v593 = wk->actaiwk->targetID;
          v594 = sBtlSearchUnit_ID(v592, v593);
          if (!v594)
            goto LABEL_557;
          v595 = v594;
          if (v594 == wk)
            goto LABEL_557;
LABEL_1659:
          SetAtkDirHD(wk, v595, 45.0, 4.0);
          z = v591;
          w = v590;
          goto LABEL_557;
        }
        v740 = wk->actaiwk->targetID;
        if (v740 != -1)
        {
          v740 = wk->actaiwk->targetID;
          v742 = wk->UnitMng;
          v743 = sBtlSearchUnit_ID(v742, v740);
          if (v743)
          {
            v595 = v743;
            if (v743 != wk && (u32)(u16)wk->para->devilid - 259 >= 2)
            {
              v590 = w;
              v591 = z;
              if (!sBtlChkKaihiMawari(wk))
                goto LABEL_1659;
            }
          }
        }
      }
LABEL_557:
      if (p_actwk->action_flg)
        goto LABEL_558;
      v596 = p_actwk->use_skillid;
      if (v596 <= 18)
      {
        if (v596 != 3 && v596 != 18)
          goto LABEL_558;
      }
      else if ((v596 | 0x10) != 0x32)
      {
        goto LABEL_558;
      }
      if (wk->actaiwk->targetID != -1)
      {
        if (!sBtlChkKaihiMawari(wk))
        {
          v664 = wk->UnitMng;
          v665 = wk->actaiwk->targetID;
          v666 = sBtlSearchUnit_ID(v664, v665);
          if (v666)
          {
            v667 = v666;
            if (v666 != wk)
            {
              SetAtkDirHD(wk, v667, 45.0, 2.0);
              v668 = wk->pos.x;
              v669 = v667->pos.x - v668;
              v670 = wk->pos.z;
              v671 = v667->pos.z - v670;
              v672 = sqrtf((f32)(v669 * v669) + (f32)(v671 * v671));
              v673 = v672 - (f32)(v667->actaiwk->hit_area_r + MotionVisualData->m_mv_area_r);
              if (v673 > 10.0)
              {
                v674 = wk->h_attack_move_len;
                if (v674 < 300.0)
                {
                  wk->pos.x = (f32)((f32)(v669 / v672) * 10.0) + v668;
                  wk->pos.z = (f32)((f32)(v671 / v672) * 10.0) + v670;
                  wk->h_attack_move_len = v673 + v674;
                }
              }
            }
          }
        }
      }
LABEL_558:
      v266 = p_actwk;
      if (p_actwk->framecnt <= 1)
      {
        v266->sklcng_use_skillid = v266->use_skillid;
        v267 = sBtlGetActionTime(wk, 0);
        v268 = v267;
        if (v267 == INFINITY)
          v268 = 0x80000000;
        v266->sklcng_next_motiontime = v268;
        v266 = wk->actwk;
      }
      v269 = v264;
      if (v266->sklcng_use_skillid != v266->use_skillid)
        goto LABEL_571;
      v270 = v266->sklcng_next_motiontime;
      v271 = sBtlGetActionTime(wk, 0);
      v272 = 0;
      v273 = v271 == INFINITY ? 0x80000000 : (s32)v271;
      if (v270 != v273)
LABEL_571:
        v272 = 1;
      v274 = p_actwk->framecnt;
      v275 = sBtlGetActionTime(wk, 0);
      if (v275 != INFINITY && v274 < (s32)v275)
        goto LABEL_2535;
      v276 = p_actwk->action_flg ? 1 : v272;
      if ((v276 & 1) != 0)
        goto LABEL_2535;
      v277 = p_actwk->use_skillid;
      if (!sBtlHDloadChk(v277))
      {
LABEL_2535:
        if (wk->actaiwk->mahaskl_waitframe <= 0)
        {
          v1111 = wk->aiwk;
          v1106 = oldposb;
          cancelCnt = v1111->cancelCnt;
          if (cancelCnt)
          {
            v1113 = cancelCnt + 1;
            v1111->cancelCnt = v1113;
            if (v1113 >= 21)
            {
              sBtlResetAAI(wk);
              v1107 = 1;
              sBtlSetAIWkStat(wk, 1);
              goto LABEL_2539;
            }
          }
        }
        else
        {
          v1106 = oldposb;
        }
        v1107 = 0;
LABEL_2539:
        Proc(wk);
        sBtlProc(wk);
        sBtlMVSupport(wk);
        UnitMV(wk);
        v1436.x = v269;
        v1436.y = v1106;
        v1436.z = z;
        v1436.w = w;
        CheckMapHit(wk, v1436);
        UnitMV_To_Basic(wk);
        if (v1107 | sBtlCheckNextAction(wk))
        {
          if ((wk->side & 2) != 0)
          {
            wk->NotCmbSkl_Ex = 0;
          }
          ResetAction(wk);
          sBtlSetAction(wk, 2, 0);
          sBtlEndAction(wk);
          v1110 = sBtlGetSkilltbl(wk->actwk->use_skillid);
          if (v1110)
          {
            if ((v1110->flg2 & 0x100) != 0 || wk->para->devilid == 258)
            {
              wk->flg |= 0x20u;
            }
            else
            {
              sBtlSetUseSkill(wk, 0, 0);
            }
          }
        }
        return v214;
      }
      if ((wk->side & 0x81) == 1)
      {
        sBtlCheckCost(wk, 2);
      }
      v278 = wk->actwk;
      v279 = wk->aiwk;
      v280 = v278->use_skillid;
      if (v280)
        v279->usedSkl = v280;
      v278->action_flg = 1;
      wk->hangeki_notjyakuten = 0;
      if (v279->cmndFrm)
        v279->cancelCnt = 1;
      CheckSkillMessage(wk, v280);
      if (wk->actwk->use_skillid == 443)
      {
        v281 = wk->rot.x;
        v282 = wk->rot.y;
        v283 = w;
        v284 = z;
        v286 = wk->rot.z;
        v285 = wk->rot.w;
        v1383.x = v281;
        v1383.y = v282;
        v1383.z = v286;
        v1383.w = v285;
        v287 = sBtlGetRotToDir(v1383);
        v289 = v287;
        v290 = wk;
        v291 = v290->UnitMng;
        v292 = v290->playerID;
        v293 = sBtlSearchUnit_ID(v291, v292);
        v294 = sBtlGetPosToDir(wk->pos.x, wk->pos.z, v293->pos.x, v293->pos.z);
        if (sBtlGetAtoB_LR_ABS(v289, v294) <= 60.0)
        {
          wk->namatuba_cnt = 0;
          wk->namatuba_homing_on = 1;
        }
        else
        {
          v295 = wk->pos.x;
          v296 = wk->pos.z;
          sBtlGetMoveXZ(v295, v296, v289, 1200.0, &wk->namatuba_1st_pos.x, &wk->namatuba_1st_pos.z);
          wk->namatuba_homing_on = 0;
          *(u64 *)&wk->namatuba_cnt = 0x3F80000000000000LL;
        }
        z = v284;
        w = v283;
        v269 = v264;
      }
      v1028 = p_actwk->use_skillid;
      if (v1028 == 1472)
      {
        v1029 = p_actwk->genArg[0];
        if (v1029 != -1)
        {
          Add(v1029, wk, 0);
          wk->BossXAtk = 1;
        }
      }
      else
      {
        if (sBtlSearchEffectData(v1028) == -1)
        {
          sBtlForceDelete_SkillFlag_Acter(wk, 0x400u);
        }
        else
        {
          sBtlSetSkill_EffectData(wk, wk->actwk->use_skillid, 0);
          if (wk->actwk->use_skillid == 465)
          {
            v1030 = (loc_1EA25E0)(0);
            sBtlGetPointData(v1030, &v1362, &v1361);
            Add_Wait(v1362.x, v1362.y, v1362.z, 290);
            v269 = v264;
          }
        }
      }
      v1102 = p_actwk->use_skillid;
      if ((u32)(v1102 - 112) <= 9)
      {
        sBtlRecoverSpiritAdd(wk, 4, v1102);
      }
      v1103 = p_actwk->use_skillid;
      if ((u32)(v1103 - 134) > 0xFFFFFFF9 || (u32)(v1103 - 658) < 4 || v1103 == 1124)
      {
        sBtlRecoverSpiritAdd(wk, 3, v1103);
        v1103 = wk->actwk->use_skillid;
      }
      if ((u32)(v1103 - 83) > 0xFFFFFFFD || (u32)(v1103 - 96) < 5 || v1103 == 434)
      {
        wk->actaiwk->mahaskl_waitframe = 100;
      }
      else
      {
        if (v1103 > 1137)
        {
          if ((u32)v1103 > 0x48C)
          {
            v269 = v264;
            switch (v1103)
            {
              case 1233:
              case 1266:
              case 1267:
              case 1269:
                goto LABEL_2532;
              case 1268:
                v1105 = 300;
                goto LABEL_2534;
              default:
                goto LABEL_2535;
            }
            goto LABEL_2535;
          }
          if (v1103 != 1141)
          {
            v269 = v264;
            if (v1103 != 1164)
              goto LABEL_2535;
            v1105 = 150;
LABEL_2534:
            wk->NotCmbSkl_Cnt2 = v1105;
            goto LABEL_2535;
          }
LABEL_2956:
          v269 = v264;
          v1105 = 120;
          goto LABEL_2534;
        }
        v269 = v264;
        if (v1103 > 1131)
        {
          if (v1103 == 1136)
            goto LABEL_2956;
          v269 = v264;
          if (v1103 != 1137)
            goto LABEL_2535;
LABEL_2879:
          v1105 = 120;
          goto LABEL_2534;
        }
      }
      if (v1103 != 914)
      {
        if (v1103 != 1131)
          goto LABEL_2535;
LABEL_2532:
        v1105 = 180;
        goto LABEL_2534;
      }
      goto LABEL_2879;
    case 7u:
      vstatus = wk->vstatus;
      if ((vstatus & 4) != 0)
      {
        wk->vstatus = vstatus & 0xFFFFFFFB;
        v298 = oldposb;
        if ((wk->side & 0x80) == 0)
        {
LABEL_606:
          goto LABEL_607;
        }
      }
      else
      {
        v298 = oldposb;
        if ((wk->side & 0x80) == 0)
          goto LABEL_606;
      }
      wk->damagecnt = 30;
LABEL_607:
      sBtlMVSupport(wk);
      UnitMV(wk);
      v1384.x = x;
      v1384.y = v298;
      v1384.z = z;
      v1384.w = w;
      CheckMapHit(wk, v1384);
      UnitMV_To_Basic(wk);
      if (!sBtlCheckNextAction(wk))
        return v214;
      v300 = (u16)wk->para->devilid;
      if ((v300 == 302 || v300 == 263) && wk->aiwk->scrStep == 3)
        wk->color = 0;
      ResetAction(wk, 0, 0);
      sBtlResetAAI(wk);
      if ((wk->side & 1) == 0)
      {
        wk->damage_hitcnt = 0;
        goto LABEL_621;
      }
      wk->aiwk->mode = 0;
      wk->actcounter = wk->actcounter_max;
      wk->damage_hitcnt = 0;
LABEL_621:
      sBtlSetAction(wk, 2, 0);
      v302 = wk->status & 0xFFFFFFDF;
      goto LABEL_1127;
    case 8u:
      ++wk->Action_HUTTOBI_Cnt;
      wk->actaiwk->status |= 0x20u;
      sBtlMVSupport(wk);
      UnitMV(wk);
      v1385.x = x;
      v1385.y = oldposb;
      v1385.z = z;
      v1385.w = w;
      CheckMapHit(wk, v1385);
      UnitMV_To_Basic(wk);
      if ((wk->vstatus & 0x800) == 0)
      {
        if (sBtlCheckNextAction(wk))
        {
          ResetAction(wk, 0, 0);
          sBtlResetAAI(wk);
          ResetAction(wk);
          sBtlSetAction(wk, 2, 0);
          if ((wk->side & 1) != 0)
          {
            wk->aiwk->mode = 0;
            wk->actcounter = wk->actcounter_max;
          }
          sBtlEndAction(wk);
          wk->actaiwk->status &= ~0x20u;
          wk->status &= ~0x20u;
          v305 = (u16)wk->battlemode;
          if (v305 != 3 && (wk->side & 0x81) == 1)
            goto LABEL_646;
          v305 = (u16)wk->battlemode;
          v306 = wk->side;
          if (v305 == 3 && (v306 & 1) != 0)
          {
LABEL_646:
            wk->damagecnt = 60;
          }
          else if ((v306 & 2) != 0 && (wk->exsts & 1) != 0 && ((wk->status & 0x100000) != 0 || GetPercentage() <= 0x31u))
          {
            wk->hangeki_st_done = 1;
            wk->hangeki_nokezoranai = 180;
            wk->hangeki_on = 2;
            wk->hangeki_endcnt = 180;
            wk->damage_1stmotcnt = 0;
            wk->damage_1stmotnum = 0;
          }
        }
      }
      return v214;
    case 9u:
      v307 = x;
      if (v237->action_flg)
        goto LABEL_648;
      if ((wk->side & 1) == 0)
      {
        if (v237->framecntB < 2)
          goto LABEL_648;
        hModel = wk->hModel;
        v598 = 0.0;
        if (mdlGetMotionFrameFS(hModel) < (f32)wk->motion_WeakStopF)
        {
          if (wk->motion_WeakDmg2 < 1)
            goto LABEL_648;
          v598 = 0.2;
        }
        goto LABEL_1509;
      }
      v675 = v237->framecnt;
      v676 = sBtlGetActionTime(wk, 1);
      if (v676 != INFINITY && v675 < (s32)v676)
        goto LABEL_648;
      v598 = 0.0;
      if ((wk->side & 0x80) == 0)
        goto LABEL_1509;
      if (sBtlChkNowJump(wk))
      {
        sBtlMVSupport(wk);
        UnitMV(wk);
        v1009 = wk;
        v1432.x = v307;
        v1432.y = oldposb;
LABEL_2164:
        v1432.z = z;
        v1432.w = w;
LABEL_2165:
        CheckMapHit(v1009, v1432);
        UnitMV_To_Basic(wk);
        return v214;
      }
      if (wk->mode != 1)
      {
LABEL_2754:
        sBtlMVSupport(wk);
        UnitMV(wk);
        v1009 = wk;
        v1432.x = v307;
        v1432.y = oldposb;
        v1432.z = z;
        v1432.w = w;
        goto LABEL_2165;
      }
      v1101 = wk->motionno;
      if (v1101 > 137)
      {
        if (v1101 == 138)
          goto LABEL_2854;
        if (v1101 != 139)
          goto LABEL_648;
LABEL_2850:
        para = wk->para;
        if (sBtlGetBadStatus(para) == 6)
        {
LABEL_1509:
          wk->m_rate = v598;
          goto LABEL_648;
        }
        goto LABEL_648;
      }
      if (v1101 == 2)
        goto LABEL_2850;
      if (v1101 != 128)
        goto LABEL_648;
LABEL_2854:
      v1240 = wk->para;
      BadStatus = sBtlGetBadStatus(v1240);
      if (BadStatus <= 0x10)
      {
        if (((1 << BadStatus) & 0x14F20) != 0)
          goto LABEL_648;
        if (((1 << BadStatus) & 0xB0C0) != 0)
          goto LABEL_2859;
      }
      if (BadStatus - 23 <= 0xFFFFFFFD)
      {
LABEL_2859:
        wk->m_rate = 0.5;
        goto LABEL_2754;
      }
LABEL_648:
      sBtlMVSupport(wk);
      UnitMV(wk);
      v1386.x = v307;
      v1386.y = oldposb;
      v1386.z = z;
      v1386.w = w;
      CheckMapHit(wk, v1386);
      UnitMV_To_Basic(wk);
      if (wk->actwk->framecnt >= wk->actwk->cmpframecnt || wk->para->now->hp <= 0)
      {
        if (!IsSceanStop())
        {
          if (p_actwk->action_flg == 1)
          {
            if (sBtlCheckNextAction(wk))
            {
              ResetAction(wk, 0, 0);
              sBtlSetAction(wk, 2, 0);
              v308 = wk->side;
              wk->damage_hitcnt = 0;
              if ((v308 & 1) != 0)
              {
                sBtlResetAAI(wk);
                wk->aiwk->mode = 0;
                wk->actcounter = wk->actcounter_max;
                v308 = wk->side;
              }
              if ((v308 & 2) != 0)
              {
                v309 = wk->para->devilid;
                if (sBtlCheckScriptData(v309, wk))
                {
                  sBtlResetAAI(wk);
                  WeakAfterScrflag(wk);
                }
              }
            }
            return v214;
          }
          if (sBtlIsDeadBgn(wk) && (wk->side & 0x80) == 0)
          {
            sBtlRestartMotion(wk);
            if ((wk->side & 0x80) == 0)
            {
              sBtlSetDeadDamage(wk, 0, 0);
            }
            p_actwk->action_flg = 1;
LABEL_2094:
            if ((wk->side & 2) != 0)
            {
              WeakAfterScrflag(wk);
              if ((wk->status & 0x100000) != 0)
              {
                if ((wk->hstatus & 0x10) != 0)
                  v972 = 0xB4000000B4LL;
                else
                  v972 = 0xC8000000F0LL;
                *(u64 *)&wk->hangeki_nokezoranai = v972;
                wk->damagecnt = 1;
              }
            }
            return v214;
          }
          if (p_actwk->use_skillid != 1549)
          {
            sBtlRestartMotion(wk);
            wk->status &= ~0x20u;
            wk->hstatus &= ~0x10u;
            wk->getMag = 0;
            sBtlSetAIWkStat(wk, 1);
            if ((wk->status & 0x100000) != 0)
            {
              sBtlResetAAI(wk);
              sBtlResetMode(wk);
            }
            if ((wk->side & 2) != 0)
              v971 = 0;
            else
              v971 = 30;
            wk->damagecnt = v971;
            wk->actwk->action_flg = 1;
            if (wk->para->now->hp <= 0)
            {
              sBtlSetDeadDamage(wk, 0, 0);
            }
            goto LABEL_2094;
          }
          wk->status &= ~0x20u;
          wk->hstatus &= ~0x10u;
          wk->getMag = 0;
          sBtlBS_MUNAKA_Init_Imad_Restart(wk);
        }
      }
      return v214;
    case 0xAu:
      if ((wk->aiwk->scrflag & 0x20000) == 0)
      {
        action_flg = (u8)v237->action_flg;
        v311 = oldposb;
        if ((wk->status & 0x40) != 0)
        {
          if (action_flg != 1 && v237->framecnt >= 80)
          {
            v237->action_flg = 1;
            wk->m_rate = 0.0;
            sBtlSetFade(wk, 1026, 0, 0, 1);
          }
          goto LABEL_2812;
        }
        if (action_flg == 1)
          goto LABEL_2812;
        v312 = wk->hstatus;
        if ((v312 & 0x8000000) == 0)
        {
          if ((v312 & 0x10000000) == 0)
          {
            v313 = (u16)wk->para->devilid;
            if (v313 != 120)
            {
              v314 = oldposb;
              v315 = x;
              v316 = w;
              v317 = z;
              if (v313 != 264)
              {
                v237->action_flg = 1;
                v1224 = wk->side;
                wk->m_rate = 0.0;
                if ((v1224 & 2) != 0)
                {
                  sBtlSetFade(wk, 1026, 0, 0, 1);
                  v1225 = 32;
                  v311 = oldposb;
                  do
                  {
                    sBtlFadeProc(wk);
                    --v1225;
                  }
                  while (v1225);
                }
                goto LABEL_2812;
              }
              sBtlEndSetsumaPadStop();
              if (!sBtlCheckSetsuma())
                sBtlSetEnemyLastDeadStop(6, 80, 0.05, 0.05);
              wk->actwk->action_flg = 1;
              wk->m_rate = 0.5;
              sBtlSetFade(wk, 1026, 0, 0, 2);
              if (wk->motionID != 13 && wk->next_motionID != 13)
              {
                wk->next_motion_not_hokan = 1;
                sBtlSetMotion(wk, 13, 0, 0, 0);
                v319 = wk->pos.x;
                v320 = wk->pos.y;
                v322 = wk->pos.z;
                v321 = wk->pos.w;
                v1387.x = v319;
                v1387.y = v320;
                v1387.z = v322;
                v1387.w = v321;
                sBtlPlay3DSE_BaseVol(0x10021u, 159, v1387);
                dds3PostHitFlashStart(0x28u);
              }
              goto LABEL_2806;
            }
            v237->action_flg = 1;
            wk->m_rate = 0.0;
            if ((wk->side & 2) != 0)
            {
              sBtlSetFade(wk, 1026, 0, 0, 3);
              sBtlFadeProc(wk);
              sBtlFadeProc(wk);
              sBtlFadeProc(wk);
              sBtlFadeProc(wk);
              sBtlFadeProc(wk);
              sBtlFadeProc(wk);
              sBtlFadeProc(wk);
              sBtlFadeProc(wk);
              sBtlFadeProc(wk);
              sBtlFadeProc(wk);
              goto LABEL_2812;
            }
LABEL_2812:
            sBtlMVSupport(wk);
            UnitMV(wk);
            v1444.x = x;
            v1444.y = v311;
            v1444.z = z;
            v1444.w = w;
            CheckMapHit(wk, v1444);
            UnitMV_To_Basic(wk);
            if (wk->actwk->action_flg != 1)
              return 1;
            if ((wk->side & 1) != 0)
            {
              sBtlDeletePlayer(wk);
              return 1;
            }
            else
            {
              if ((wk->status & 0x40) != 0 || (wk->hstatus & 0x8000000) != 0)
              {
                if ((wk->vstatus & 0x402) != 0)
                  return 1;
              }
              else if ((wk->vstatus & 0x402) != 0)
              {
                return 1;
              }
              wk->mode = 9;
              DeleteHpGage(wk->bsc, wk, 0);
              return 1;
            }
          }
          v314 = oldposb;
          v315 = x;
          v237->action_flg = 1;
          v316 = w;
          v317 = z;
          v1031 = wk->side;
          wk->m_rate = 0.0;
          if ((v1031 & 2) == 0)
          {
LABEL_2278:
            if (wk->motionID != 13)
            {
              next_motionID = wk->next_motionID;
              wk->next_motion_not_hokan = 1;
              if (next_motionID == 13)
              {
                if (!v1043)
                sBtlSetMotion(wk, 13, 1, 0, 1);
              }
              else
              {
                if (!v1043)
                sBtlSetMotion(wk, 13, 0, 0, 0);
                v1233 = wk->pos.x;
                v1234 = wk->pos.y;
                v1236 = wk->pos.z;
                v1235 = wk->pos.w;
                v1443.x = v1233;
                v1443.y = v1234;
                v1443.z = v1236;
                v1443.w = v1235;
                sBtlPlay3DSE_BaseVol(0x10021u, 159, v1443);
              }
            }
LABEL_2806:
            z = v317;
            w = v316;
            x = v315;
            v311 = v314;
            if (!sBtlCheckSetsuma())
            {
              sBtlSetsuma_MagWaitDone();
              z = v317;
              w = v316;
              x = v315;
              v311 = v314;
            }
            goto LABEL_2812;
          }
          if (wk->para->devilid != 120)
          {
            if (!v1032)
            sBtlSetFade(wk, 1026, 0, 0, 1);
            v1232 = 32;
            do
            {
              sBtlFadeProc(wk);
              --v1232;
            }
            while (v1232);
            goto LABEL_2278;
          }
          if (!v1032)
          sBtlSetFade(wk, 1026, 0, 0, 3);
          sBtlFadeProc(wk);
          sBtlFadeProc(wk);
          sBtlFadeProc(wk);
          sBtlFadeProc(wk);
          sBtlFadeProc(wk);
          sBtlFadeProc(wk);
          sBtlFadeProc(wk);
          sBtlFadeProc(wk);
          sBtlFadeProc(wk);
          sBtlFadeProc(wk);
          goto LABEL_2278;
        }
        sBtlEndSetsumaPadStop();
        if (!sBtlCheckSetsuma())
          sBtlSetEnemyLastDeadStop(6, 80, 0.05, 0.05);
        wk->actwk->action_flg = 1;
        wk->m_rate = 0.5;
        v966 = (u16)wk->para->devilid;
        if (v966 == 120)
        {
          if ((wk->side & 2) != 0)
          {
            v967 = 3;
            goto LABEL_2049;
          }
        }
        else
        {
          if (v966 == 264)
          {
            v967 = 2;
LABEL_2049:
            sBtlSetFade(wk, 1026, 0, 0, v967);
            goto LABEL_2573;
          }
          if ((wk->side & 2) != 0)
          {
            v967 = 1;
            goto LABEL_2049;
          }
        }
LABEL_2573:
        if (wk->motionID != 13 && wk->next_motionID != 13)
        {
          wk->next_motion_not_hokan = 1;
          v1115 = x;
          v1116 = w;
          v1117 = z;
          sBtlSetMotion(wk, 13, 0, 0, 0);
          v1118 = wk->pos.x;
          v1119 = wk->pos.y;
          v1121 = wk->pos.z;
          v1120 = wk->pos.w;
          v1437.x = v1118;
          v1437.y = v1119;
          v1437.z = v1121;
          v1437.w = v1120;
          sBtlPlay3DSE_BaseVol(0x10021u, 159, v1437);
          dds3PostHitFlashStart(0x28u);
          z = v1117;
          w = v1116;
          x = v1115;
          v311 = oldposb;
        }
        if (!sBtlCheckSetsuma())
        {
          sBtlSetsuma_MagWaitDone();
        }
        goto LABEL_2812;
      }
      v239 = oldposb;
      if (sBtlCheckSetsuma())
        goto LABEL_1227;
      if (wk->cmbSkl->bRun)
        goto LABEL_1227;
      v739 = (u16)wk->para->devilid;
      if (wk->para->devilid <= 281)
      {
        v1012 = v739 - 264;
        if (v1012 > 0x11 || ((1 << v1012) & 0x30001) == 0)
          goto LABEL_2192;
      }
      else if (v739 != 293 && v739 != 526 && v739 != 533)
      {
LABEL_2192:
        sBtlProc(wk);
        sBtlPlayerEndRSpiritProc();
      }
LABEL_1227:
      if ((wk->aiwk->scrflag & 0x40000) == 0)
      {
        sBtlStartDeadEvent(wk);
        wk->actwk->action_flg = 1;
        wk->DeadEventDone = 1;
        if (sBtlCheckSetsuma() && !wk->motionID)
        {
          sBtlSetMotion(wk, 14, 0, 0, 0);
        }
      }
      goto LABEL_2159;
    case 0xCu:
      v323 = v237->use_skillid;
      v324 = sBtlGetActionTime(wk, 0);
      v239 = oldposb;
      if (v323 <= 701)
      {
        if ((u32)(v323 - 690) < 3 || v323 == 696 || v323 == 701)
          v323 = 0;
      }
      else
      {
        if ((u32)v323 > 0x530)
        {
          if ((v323 | 2) != 0x53F)
            goto LABEL_1354;
          goto LABEL_1353;
        }
        if (v323 == 1326 || v323 == 1328)
LABEL_1353:
          v323 = 1326;
      }
LABEL_1354:
      v617 = p_actwk;
      if (v324 != INFINITY && v617->framecnt < (s32)v324 || v617->action_flg)
        goto LABEL_2159;
      if (!sBtlHDloadChk(v323))
        goto LABEL_2159;
      v618 = p_actwk;
      v618->action_flg = 1;
      v619 = v618->use_skillid;
      CheckSkillMessage(wk, v619);
      if ((u32)(v323 - 1296) < 2)
        goto LABEL_1363;
      if (!v323)
        goto LABEL_2159;
      v1007 = p_actwk->use_skillid;
      if (sbtlplayertblGetHDEffTable_SKLID(v1007, 0) == -1)
      {
        if (sBtlSearchEffectData(v323) == -1)
        {
          sBtlForceDelete_SkillFlag_Acter(wk, 0x400u);
          goto LABEL_2161;
        }
LABEL_1363:
        sBtlSetSkill_EffectData(wk, v323, 0);
      }
      else
      {
LABEL_2159:
      }
LABEL_2161:
      sBtlMVSupport(wk);
LABEL_2163:
      UnitMV(wk);
      v1432.x = x;
      v1432.y = v239;
      v1009 = wk;
      goto LABEL_2164;
    case 0xEu:
      sBtlResetSummon_E(wk);
      return v214;
    case 0xFu:
    case 0x10u:
    case 0x19u:
    case 0x1Au:
      v242 = wk->mode;
      if (v242 == 22 && (v243 = p_actwk, p_actwk->use_skillid == 163))
      {
        if (v243->action_flg)
          goto LABEL_511;
        v244 = 163;
        v243->action_flg = 1;
        goto LABEL_505;
      }
      else
      {
        v242 = wk->mode;
        if (v242 != 25 || (v246 = p_actwk, p_actwk->use_skillid != 157) || v246->action_flg)
        {
LABEL_511:
          sBtlMVSupport(wk);
          UnitMV(wk);
          v1382.x = x;
          v1382.y = oldposb;
          v1382.z = z;
          v1382.w = w;
          CheckMapHit(wk, v1382);
          UnitMV_To_Basic(wk);
          v248 = wk;
          if (v248->battlemode != 3)
            goto LABEL_527;
          v248 = wk;
          if (v248->mode == 11)
          {
            if (sBtlCheckMotionEnd(wk))
            {
              sBtlSetMotion(wk, 29, 0, 0, 0);
            }
          }
          else
          {
LABEL_527:
            if (!sBtlPlayerIsRSkillCancel())
            {
              if (sBtlCheckMotionEnd(wk))
              {
                sBtlSetUseSkill(wk, 0, 0);
                sBtlResetAction(wk);
              }
            }
          }
          return v214;
        }
        v244 = 157;
        v246->action_flg = 1;
LABEL_505:
        CheckSkillMessage(wk, v244);
        goto LABEL_511;
      }
      goto LABEL_505;
    case 0x12u:
      wk->mode = 9;
      return v214;
    case 0x13u:
      sBtlProc(wk);
      sBtlMVSupport(wk);
      UnitMV(wk);
      v1388.x = x;
      v1388.y = oldposb;
      v1388.z = z;
      v1388.w = w;
      CheckMapHit(wk, v1388);
      UnitMV_To_Basic(wk);
      if (!sBtlCheckNextAction(wk))
        return v214;
      v325 = wk;
      v326 = 0;
      goto LABEL_2239;
    case 0x14u:
      v328 = wk->UnitMng;
      hithelperID = wk->hithelperID;
      v330 = sBtlSearchUnit_ID(v328, hithelperID);
      if (v330)
      {
        v331 = v330;
        v332 = wk->para->devilid;
        sBtlGetHelperPos(wk, v331, v332);
      }
      goto LABEL_750;
    case 0x15u:
      Proc(wk);
      sBtlProc(wk);
      sBtlMVSupport(wk);
      UnitMV(wk);
      v1389.x = x;
      v1389.y = oldposb;
      v1389.z = z;
      v1389.w = w;
      CheckMapHit(wk, v1389);
      UnitMV_To_Basic(wk);
      if (sBtlCheckNextAction(wk))
      {
        p_actwk->status = 2;
        ResetAction(wk);
      }
      return v214;
    case 0x16u:
      v334 = wk->UnitMng;
      v335 = wk->hithelperID;
      v336 = sBtlSearchUnit_ID(v334, v335);
      if (v336)
      {
        v337 = v336;
        hithelperno = wk->hithelperno;
        sBtlGetUnitHelperPos(v337, hithelperno);
        sub_1B335A0(&wk->pos, 0, v339);
      }
LABEL_750:
      sBtlMVSupport(wk);
      return v214;
    case 0x17u:
      sBtlMVSupport(wk);
      UnitMV(wk);
      v1390.x = x;
      v1390.y = oldposb;
      v1390.z = z;
      v1390.w = w;
      CheckMapHit(wk, v1390);
      UnitMV_To_Basic(wk);
      if (sBtlCheckMotionEnd(wk) && p_actwk->framecnt >= p_actwk->cmpframecnt)
      {
        sBtlSetAction(wk, 7, 0);
        wk->mv_rot = 0.0;
      }
      return v214;
    case 0x1Du:
      if ((wk->vstatus & 2) != 0)
        v237->status = 30;
      v239 = oldposb;
      goto LABEL_2161;
    case 0x1Fu:
      if ((v237->use_skillid & 0xFFFFFFFE) == 0x1A2 && !v237->action_flg)
      {
        v653 = wk->actaiwk->targetID;
        if (v653 != -1)
        {
          v653 = wk->actaiwk->targetID;
          v655 = wk->UnitMng;
          v656 = sBtlSearchUnit_ID(v655, v653);
          if (v656)
          {
            v657 = v656;
            if (v656 != wk)
            {
              SetAtkDirHD(wk, v657, 45.0, 2.0);
            }
          }
        }
      }
      v341 = p_actwk->framecnt;
      v342 = sBtlGetActionTime(wk, 0);
      if (v342 != INFINITY && v341 < (s32)v342 || p_actwk->action_flg)
        goto LABEL_2833;
      v343 = p_actwk->use_skillid;
      if (!sBtlHDloadChk(v343))
        goto LABEL_2833;
      if ((wk->side & 0x81) == 1)
      {
        sBtlCheckCost(wk, 2);
      }
      v344 = p_actwk;
      v345 = p_actwk->use_skillid;
      if (v345)
        wk->aiwk->usedSkl = v345;
      v344->action_flg = 1;
      CheckSkillMessage(wk, v345);
      v346 = wk->actwk->use_skillid;
      if (v346 == 458)
      {
        Add(66484, wk, 0);
        v346 = wk->actwk->use_skillid;
        if (v346 != 459)
        {
LABEL_788:
          if (v346 == 460)
            goto LABEL_789;
          goto LABEL_1637;
        }
      }
      else if (v346 != 459)
      {
        goto LABEL_788;
      }
      Add(66483, wk, 0);
      v346 = wk->actwk->use_skillid;
      if (v346 == 460)
      {
LABEL_789:
        Add(66482, wk, 0);
        v346 = wk->actwk->use_skillid;
        if (v346 > 462)
          goto LABEL_792;
        goto LABEL_1638;
      }
LABEL_1637:
      if (v346 > 462)
      {
LABEL_792:
        if (v346 == 488)
        {
          v347 = 65969;
          goto LABEL_2591;
        }
        if (v346 == 463)
        {
          v347 = 66481;
LABEL_2591:
          Add(v347, wk, 0);
          goto LABEL_2833;
        }
        goto LABEL_2596;
      }
LABEL_1638:
      if (v346 == 418)
      {
        v738 = 65985;
      }
      else
      {
        if (v346 != 419)
        {
LABEL_2596:
          if (sBtlSearchEffectData(v346) == -1)
          {
            sBtlForceDelete_SkillFlag_Acter(wk, 0x400u);
          }
          else
          {
            sBtlSetSkill_EffectData(wk, wk->actwk->use_skillid, 0);
          }
          goto LABEL_2833;
        }
        v738 = 65953;
      }
      Add(v738, wk, 0);
      wk->BossXAtk = 1;
LABEL_2833:
      sBtlMVSupport(wk);
      UnitMV(wk);
      v1445.x = x;
      v1445.y = oldposb;
      v1445.z = z;
      v1445.w = w;
      CheckMapHit(wk, v1445);
      UnitMV_To_Basic(wk);
      if (!sBtlCheckNextAction(wk))
        return v214;
      ResetAction(wk);
      sBtlSetAction(wk, 2, 0);
      sBtlEndAction(wk);
      v1238 = sBtlGetSkilltbl(wk->actwk->use_skillid);
      if (v1238)
      {
        if ((v1238->flg2 & 0x100) != 0)
        {
          wk->flg |= 0x20u;
        }
        else
        {
          sBtlSetUseSkill(wk, 0, 0);
        }
      }
LABEL_1998:
      sBtlEndAction(wk);
      return v214;
    case 0x21u:
      sBtlMVSupport(wk);
      UnitMV(wk);
      v1391.x = x;
      v1391.y = oldposb;
      v1391.z = z;
      v1391.w = w;
      CheckMapHit(wk, v1391);
      UnitMV_To_Basic(wk);
      if ((wk->para->badstatus & 0x1000) != 0)
        return v214;
      sBtlRestartMotion(wk);
      goto LABEL_1889;
    case 0x22u:
      v237->effect_flg = 1;
      v349 = p_actwk;
      v350 = wk;
      v352 = p_actwk->framecnt;
      v353 = v350->battlemode == 3;
      if (v350->battlemode == 3)
        v354 = 0;
      else
        v354 = 120;
      if (v353)
        v355 = 10;
      else
        v355 = 135;
      v349->effectTime = v354;
      v349->cmpframecnt2 = v355;
      v349->cmpframecnt3 = 90;
      v356 = sBtlGetActionTime(wk, 1);
      if (v356 == INFINITY || v352 >= (s32)v356)
      {
        wk->actwk->action_flg = 1;
        wk->m_rate = 0.0;
      }
      sBtlMVSupport(wk);
      UnitMV(wk);
      v1392.x = x;
      v1392.y = oldposb;
      v1392.z = z;
      v1392.w = w;
      CheckMapHit(wk, v1392);
      UnitMV_To_Basic(wk);
      if ((wk->side & 1) != 0)
      {
        sBtlDeletePlayer(wk);
      }
      v357 = p_actwk;
      if (p_actwk->framecnt != p_actwk->cmpframecnt2 + p_actwk->effectTime)
        goto LABEL_1369;
      effect_flg = v357->effect_flg;
      if ((effect_flg & 1) != 0)
      {
        cmpframecnt3 = v357->cmpframecnt3;
        v360 = 0;
        v361 = 0;
        v362 = 0;
      }
      else
      {
        if ((effect_flg & 2) == 0)
          goto LABEL_1369;
        cmpframecnt3 = v357->cmpframecnt3;
        v360 = 255;
        v361 = 255;
        v362 = 255;
      }
      dds3FadeOut(v360, v361, v362, cmpframecnt3);
LABEL_1369:
      if (p_actwk->framecnt >= p_actwk->cmpframecnt2 + p_actwk->effectTime + p_actwk->cmpframecnt3)
      {
        wk->para->badst_cnt = 0;
        sBtlResetBadStatus(wk, 0x20000);
      }
      return v214;
    case 0x23u:
      sBtlMVSupport(wk);
      v239 = oldposb;
      goto LABEL_2163;
    case 0x25u:
      v364 = v237->framecnt;
      v365 = sBtlGetActionTime(wk, 0);
      if (v365 != INFINITY && v364 < (s32)v365 || p_actwk->action_flg)
        goto LABEL_2141;
      v366 = p_actwk->use_skillid;
      if (!sBtlHDloadChk(v366))
        goto LABEL_2141;
      v367 = p_actwk;
      v367->action_flg = 1;
      v368 = v367->use_skillid;
      CheckSkillMessage(wk, v368);
      v369 = wk->actwk->use_skillid;
      if ((wk->vstatus & 0x4000) != 0 && v369 == 288)
      {
        v370 = 288;
      }
      else
      {
        if (sBtlSearchEffectData(v369) == -1)
        {
          sBtlForceDelete_SkillFlag_Acter(wk, 0x400u);
LABEL_2143:
          sBtlMVSupport(wk);
          UnitMV(wk);
          v1431.x = x;
          v1431.y = oldposb;
          v1431.z = z;
          v1431.w = w;
          CheckMapHit(wk, v1431);
          UnitMV_To_Basic(wk);
          v1003 = sBtlCheckNextAction(wk);
          v1004 = wk->actwk;
          if (v1003 || v1004->action_flg == 1)
          {
            v1005 = v1004->use_skillid;
            if (v1005 == 357)
            {
              if (!v1006)
              v325 = wk;
              v326 = 60;
            }
            else
            {
              if (!v1006)
LABEL_2238:
              v325 = wk;
              v326 = 2;
            }
LABEL_2239:
            v466 = 0;
LABEL_2240:
            sBtlSetAction(v325, v326, v466);
          }
          return v214;
        }
        v370 = wk->actwk->use_skillid;
      }
      sBtlSetSkill_EffectData(wk, v370, 0);
LABEL_2141:
      goto LABEL_2143;
    case 0x26u:
      v371 = v237->framecnt;
      v372 = sBtlGetActionTime(wk, 0);
      if ((v372 == INFINITY || v371 >= (s32)v372) && !p_actwk->action_flg)
      {
        if (sBtlHDloadChk(464))
        {
          if (sBtlHDloadChk(466))
          {
            p_actwk->action_flg = 1;
            if (sBtlSearchEffectData(466) == -1)
            {
              sBtlForceDelete_SkillFlag_Acter(wk, 0x400u);
            }
            else
            {
              sBtlSetSkill_EffectData(wk, 466, 0);
            }
          }
        }
      }
      v1122 = p_actwk;
      if (p_actwk->action_flg == 1)
      {
        v1123 = sBtlCheckMotionEnd(wk);
        v1122 = wk->actwk;
        if (v1123)
        {
          v1122->action_flg = 2;
          sBtlSetMotion_ID(wk, 21, 0, 0, 0);
          v1122 = wk->actwk;
          v1122->framecnt = 0;
          v1122->cmpframecnt = 0;
        }
      }
      v1125 = v1122->framecnt;
      if (v1122->action_flg == 2 && v1125 >= v1122->cmpframecnt)
      {
        v1122->action_flg = 3;
        sBtlSetMotion_ID(wk, 22, 0, 0, 0);
        v1125 = 0;
        wk->actwk->framecnt = 0;
      }
      v1126 = sBtlGetActionTime(wk, 0);
      if ((v1126 == INFINITY || v1125 >= (s32)v1126) && p_actwk->action_flg == 3)
      {
        p_actwk->action_flg = 4;
        CheckSkillMessage(wk, 464);
        if (sBtlSearchEffectData(464) == -1)
        {
          sBtlForceDelete_SkillFlag_Acter(wk, 0x400u);
        }
        else
        {
          sBtlSetSkill_EffectData(wk, 464, 0);
        }
      }
      Proc(wk);
      sBtlProc(wk);
      sBtlMVSupport(wk);
      UnitMV(wk);
      v1438.x = x;
      v1438.y = oldposb;
      v1438.z = z;
      v1438.w = w;
      CheckMapHit(wk, v1438);
      UnitMV_To_Basic(wk);
      if (wk->actwk->action_flg == 4)
        goto LABEL_1992;
      return v214;
    case 0x27u:
      v373 = (u16)wk->para->devilid;
      if (v373 == 269 || v373 == 304)
        return v214;
      v237 = p_actwk;
      v375 = v237->framecnt;
      v376 = wk->scrUnitList[2];
      if (sBtlGetActionTime(wk, 0) <= (f32)v375 && !p_actwk->action_flg)
      {
        v377 = p_actwk->use_skillid;
        if (sBtlHDloadChk(v377))
        {
          v378 = p_actwk;
          v378->action_flg = 1;
          v379 = v378->use_skillid;
          CheckSkillMessage(wk, v379);
          v380 = wk->actwk->use_skillid;
          if (sBtlSearchEffectData(v380) == -1)
          {
            sBtlForceDelete_SkillFlag_Acter(wk, 0x400u);
          }
          else
          {
            sBtlSetSkill_EffectData(wk, wk->actwk->use_skillid, 0);
          }
        }
      }
      v1129 = p_actwk;
      if (p_actwk->action_flg == 1)
      {
        v1130 = sBtlCheckMotionEnd(wk);
        v1129 = wk->actwk;
        if (v1130)
        {
          v1129->action_flg = 2;
          sBtlSetMotion_ID(wk, 22, 0, 0, 0);
          sBtlSetMotion_ID(v376, 22, 0, 0, 0);
          v1129 = wk->actwk;
          v1129->framecnt = 0;
          v1129 = p_actwk;
          *(u64 *)wk->scrCnt = 0;
        }
      }
      if ((u8)v1129->action_flg < 2u)
        return v214;
      v1134 = wk;
      v1135 = v1134->UnitMng;
      v1136 = v1134->playerID;
      v1137 = sBtlSearchUnit_ID(v1135, v1136);
      v1138 = v1137->pos.x;
      v1139 = v1137->pos.y;
      v1140 = v1137->pos.z;
      v1141 = v1137->pos.w;
      sub_1B332C0(0, v1138, v1139, v1140, v1141);
      sub_1B33360(0, wk->actaiwk->scrPos.x, wk->actaiwk->scrPos.y, wk->actaiwk->scrPos.z, wk->actaiwk->scrPos.w);
      sub_1B33400(0);
      sub_1B335A0(&v1367, 0, v1142);
      switch (wk->aiwk->scrStep2)
      {
        case 0:
          if (wk->scrCnt[0] > 14)
          {
            goto LABEL_2683;
          }
          gAmatobiMoveCnt = 0;
LABEL_2683:
          scrCnt = wk->scrCnt;
          v1145 = scrCnt[0];
          if (v1145 > 119)
          {
            scrCnt = wk->scrCnt;
            v1145 = scrCnt[0];
            if (v1145 == 120)
            {
              v1146 = v1367;
              v1147 = v1368;
              sub_1B332C0(0, *(f32 *)&v1146, *((f32 *)&v1146 + 1), *(f32 *)&v1147, *((f32 *)&v1147 + 1));
              sub_1949110(0);
              p_scrPos2 = &wk->actaiwk->scrPos2;
              goto LABEL_2707;
            }
            scrCnt = wk->scrCnt;
            v1145 = scrCnt[0];
            if (v1145 <= 149)
            {
              v1226 = wk->actaiwk;
              v1227 = v1226->scrPos2.x;
              v1228 = v1226->scrPos2.y;
              v1229 = v1226->scrPos2.z;
              v1230 = v1226->scrPos2.w;
              sub_1B332C0(0, v1227, v1228, v1229, v1230);
              v1168 = (f32)(wk->scrCnt[0] - 120) * 1.5;
LABEL_2706:
              sub_1B33480(0, v1168);
              sub_1B33360(0, wk->actaiwk->scrPos.x, wk->actaiwk->scrPos.y, wk->actaiwk->scrPos.z, wk->actaiwk->scrPos.w);
              *(__n128 *)&v1148 = sub_1B33520(0);
              p_scrPos2 = &wk->actaiwk->scrPos;
LABEL_2707:
              sub_1B335A0(p_scrPos2, 0, v1148);
              goto LABEL_2708;
            }
            scrCnt = wk->scrCnt;
            v1145 = scrCnt[0];
            if (v1145 > 219)
            {
              wk->aiwk->scrStep2 = 1;
LABEL_2945:
              scrCnt[0] = 0;
              goto LABEL_2708;
            }
            else
            {
              v1253 = wk->actaiwk;
              v1254 = v1253->scrPos2.x;
              v1255 = v1253->scrPos2.y;
              v1256 = v1253->scrPos2.z;
              v1257 = v1253->scrPos2.w;
              sub_1B332C0(0, v1254, v1255, v1256, v1257);
              sub_1B33480(0, 67.5);
              sub_1B33360(0, wk->actaiwk->scrPos.x, wk->actaiwk->scrPos.y, wk->actaiwk->scrPos.z, wk->actaiwk->scrPos.w);
              *(__n128 *)&v1258 = sub_1B33520(0);
              sub_1B335A0(&wk->actaiwk->scrPos, 0, v1258);
              v1259 = wk->actaiwk;
              v1260 = v1259->scrPos.z;
              if (v1260 <= 4700.0 && v1260 >= 1200.0)
              {
                v1261 = v1259->scrPos.x;
                if (v1261 >= -1600.0 && v1261 <= 1600.0)
                {
LABEL_2708:
                  v1170 = gAmatobiMoveCnt + 1;
                  v40 = gAmatobiMoveCnt - 25 < 0;
                  gAmatobiMoveCnt = v1170;
                  if (v40 == __OFSUB__(v1170, 26))
                    goto LABEL_2713;
                  goto LABEL_9011;
                  if (v40 == __OFSUB__(v1172, 26))
                  {
LABEL_2713:
                    v1173 = wk->actaiwk;
                    v1174 = v1173->scrPos.x;
                    v1175 = v1173->scrPos.y;
                    v1177 = v1173->scrPos.z;
                    v1176 = v1173->scrPos.w;
                    v1440.x = v1174;
                    v1440.y = v1175;
                    v1440.z = v1177;
                    v1440.w = v1176;
                    sBtlPlay3DSE(0x8B90003u, v1440);
                    gAmatobiMoveCnt = 0;
                  }
LABEL_9011:
LABEL_2732:
                  v1192 = wk->actaiwk;
                  v1193 = v1192->scrPos.x;
                  v1194 = v1192->scrPos.y;
                  v1195 = v1192->scrPos.z;
                  v1196 = v1192->scrPos.w;
                  *(__n128 *)&v1197 = sub_1B332C0(0, v1193, v1194, v1195, v1196);
                  *(__n128 *)&v1198 = sub_1B335A0(&wk->pos, 0, v1197);
                  sub_1B335A0(&v376->pos, 0, v1198);
                  wk->pos.x = wk->pos.x + 140.0;
                  v376->pos.x = v376->pos.x + -140.0;
                  v1199 = wk->pos.x;
                  v1200 = wk->pos.y;
                  v1202 = wk->pos.z;
                  v1201 = wk->pos.w;
                  v1441.x = v1199;
                  v1441.y = v1200;
                  v1441.z = v1202;
                  v1441.w = v1201;
                  dds3SetPosPoseSet(&wk->pBasic, v1441);
                  dds3SetPosPoseSet(&v376->pBasic, v376->pos);
                  return v214;
                }
              }
              wk->aiwk->scrStep2 = 1;
            }
            scrCnt = wk->scrCnt;
            goto LABEL_2945;
          }
          v1204 = v1367;
          v1205 = v1368;
          sub_1B332C0(0, *(f32 *)&v1204, *((f32 *)&v1204 + 1), *(f32 *)&v1205, *((f32 *)&v1205 + 1));
          sub_1949110(0);
          v1168 = -5.0;
          goto LABEL_2706;
        case 1:
          v1150 = v1367;
          v1151 = v1368;
          sub_1B332C0(0, *(f32 *)&v1150, *((f32 *)&v1150 + 1), *(f32 *)&v1151, *((f32 *)&v1151 + 1));
          sub_1B33480(0, 0.0005);
          sub_1B33360(0, wk->actaiwk->scrPos2.x, wk->actaiwk->scrPos2.y, wk->actaiwk->scrPos2.z, wk->actaiwk->scrPos2.w);
          *(__n128 *)&v1152 = sub_1B33520(0);
          sub_1B335A0(&wk->actaiwk->scrPos2, 0, v1152);
          v1153 = wk->actaiwk;
          v1154 = v1153->scrPos2.x;
          v1155 = v1153->scrPos2.z;
          v1156 = v1153->scrPos2.w;
          v1153->scrPos2.y = 0.0;
          *(__n128 *)&v1157 = sub_1B332C0(0, v1154, 0.0, v1155, v1156);
          if ((loc_1CDE880)(0, v1157) <= 16.0)
            goto LABEL_2703;
          sub_1949110(0);
          v1158 = 16.0;
          goto LABEL_2702;
        case 2:
          v1159 = v1367;
          v1160 = v1368;
          sub_1B332C0(0, *(f32 *)&v1159, *((f32 *)&v1159 + 1), *(f32 *)&v1160, *((f32 *)&v1160 + 1));
          sub_1B33480(0, 0.0015);
          sub_1B33360(0, wk->actaiwk->scrPos2.x, wk->actaiwk->scrPos2.y, wk->actaiwk->scrPos2.z, wk->actaiwk->scrPos2.w);
          *(__n128 *)&v1161 = sub_1B33520(0);
          sub_1B335A0(&wk->actaiwk->scrPos2, 0, v1161);
          v1162 = wk->actaiwk;
          v1163 = v1162->scrPos2.x;
          v1164 = v1162->scrPos2.z;
          v1165 = v1162->scrPos2.w;
          v1162->scrPos2.y = 0.0;
          *(__n128 *)&v1166 = sub_1B332C0(0, v1163, 0.0, v1164, v1165);
          if ((loc_1CDE880)(0, v1166) <= 7.0)
            goto LABEL_2703;
          sub_1949110(0);
          v1158 = 7.0;
LABEL_2702:
          *(__n128 *)&v1167 = sub_1B33480(0, v1158);
          sub_1B335A0(&wk->actaiwk->scrPos2, 0, v1167);
LABEL_2703:
          v1168 = 2.0;
          goto LABEL_2706;
        case 3:
          v1179 = wk->actaiwk;
          v1180 = v1179->movepos.x;
          v1181 = v1179->movepos.y;
          v1182 = v1179->movepos.z;
          v1183 = v1179->movepos.w;
          sub_1B332C0(0, v1180, v1181, v1182, v1183);
          sub_1B33360(0, wk->actaiwk->ppos.x, wk->actaiwk->ppos.y, wk->actaiwk->ppos.z, wk->actaiwk->ppos.w);
          sub_1B33400(0);
          sub_1B33480(0, (f32)(wk->scrCnt[1] - wk->scrCmpCnt) / 30.0);
          sub_1B33360(0, wk->actaiwk->ppos.x, wk->actaiwk->ppos.y, wk->actaiwk->ppos.z, wk->actaiwk->ppos.w);
          *(__n128 *)&v1185 = sub_1B33520(0);
          sub_1B335A0(&wk->actaiwk->scrPos, 0, v1185);
          v1187 = gAmatobiMoveCnt + 1;
          v40 = gAmatobiMoveCnt - 25 < 0;
          gAmatobiMoveCnt = v1187;
          if (v40 == __OFSUB__(v1187, 26))
          {
            v1208 = wk->actaiwk;
            v1209 = v1208->scrPos.x;
            v1210 = v1208->scrPos.y;
            v1212 = v1208->scrPos.z;
            v1211 = v1208->scrPos.w;
            v1442.x = v1209;
            v1442.y = v1210;
            v1442.z = v1212;
            v1442.w = v1211;
            sBtlPlay3DSE(0x8B90003u, v1442);
            gAmatobiMoveCnt = 0;
LABEL_2726:
            v1189 = wk;
            if (v1189->scrCnt[1] >= v1189->scrCmpCnt + 30)
            {
              v1190 = wk->actaiwk;
              *(u64 *)&v1190->scrPos.x = *(u64 *)&v1190->movepos.x;
              v1190->scrPos.z = v1190->movepos.z;
              wk->actwk->status = 0;
              v376->actwk->status = 0;
              v1189 = wk;
              effList = v1189->effList;
              sBtlDeleteEffectData_SkillIDType(effList, 441, 1u);
              sBtlEndAction(wk);
              wk->aiwk->scrStep = 7;
            }
            goto LABEL_2732;
          }
          goto LABEL_2726;
        default:
          goto LABEL_2732;
      }
    case 0x28u:
      v381 = v237->use_skillid;
      v382 = sBtlHDloadChk(v381);
      v383 = oldposb;
      v384 = p_actwk;
      if (!v382)
      {
        v214 = 0;
        --v384->framecnt;
        return v214;
      }
      if (v384->use_skillid != 470)
        goto LABEL_1380;
      v385 = v384->framecnt;
      if (v385 == 1)
      {
        SetAction(20);
        v384 = p_actwk;
        v385 = p_actwk->framecnt;
        if (v385 != 15)
          goto LABEL_887;
      }
      else if (v385 != 15)
      {
LABEL_887:
        if (v385 != 150)
        {
LABEL_888:
          if (v385 == 95)
            wk->m_rate = 0.8;
          goto LABEL_1380;
        }
LABEL_1377:
        sBtlSetFade(wk, 1026, 0, -1, 1);
        v384 = wk->actwk;
LABEL_1380:
        v620 = v384->use_skillid;
        if (v620 == 469)
        {
          if (v384->framecnt != 75)
            goto LABEL_1397;
          sBtlSetFade(wk, 1026, 0, -1, 1);
          v384 = wk->actwk;
          v620 = v384->use_skillid;
        }
        if (v620 == 475)
        {
          if (v384->framecnt != 15)
            goto LABEL_1397;
          sBtlSetEnemyLastDeadStop(1, 60, 0.05, 0.05);
          v384 = p_actwk;
          v620 = p_actwk->use_skillid;
        }
        if (v620 == 504)
        {
          v621 = v384->framecnt;
          if (v621 == 1)
          {
            SetAction(20);
            DeleteAll_BossDead();
            v384 = p_actwk;
            v621 = p_actwk->framecnt;
          }
          if (v621 == 15)
          {
            dds3PostHitFlashStart(0x28u);
            sBtlEndSetsumaPadStop();
            sBtlSetEnemyLastDeadStop(1, 80, 0.05, 0.05);
            v384 = p_actwk;
          }
        }
LABEL_1397:
        if (v384->use_skillid != 476)
          goto LABEL_1435;
        v622 = v384->framecnt;
        if (v622 == 1)
        {
          SetAction(20);
          DeleteAll_BossDead();
          v384 = p_actwk;
          v622 = p_actwk->framecnt;
          if (v622 != 15)
          {
LABEL_1402:
            if (v622 != 220)
              goto LABEL_1435;
            goto LABEL_1432;
          }
        }
        else if (v622 != 15)
        {
          goto LABEL_1402;
        }
        dds3PostHitFlashStart(0x28u);
        sBtlEndSetsumaPadStop();
        sBtlSetEnemyLastDeadStop(1, 80, 0.05, 0.05);
        v384 = p_actwk;
        if (p_actwk->framecnt != 220)
        {
LABEL_1435:
          if (v384->use_skillid != 493)
            goto LABEL_1691;
          v638 = v384->framecnt;
          if (v638 == 260)
          {
            sBtlSetFade(wk, 1026, 0, 0, 1);
LABEL_1691:
            if (p_actwk->use_skillid == 479)
            {
              v763 = p_actwk->framecnt;
              if (v763 == 150)
              {
                sBtlSetFade(wk, 1026, 0, 0, 1);
              }
              else if (v763 == 1)
              {
                if (!sBtlCheckSetsuma())
                {
                  sBtlSetsuma_MagWaitDone();
                }
              }
            }
            if (p_actwk->use_skillid == 480)
            {
              v764 = p_actwk->framecnt;
              if (v764 == 150)
              {
                sBtlSetFade(wk, 1026, 0, 0, 1);
              }
              else if (v764 == 1)
              {
                if (!sBtlCheckSetsuma())
                {
                  sBtlSetsuma_MagWaitDone();
                }
              }
            }
            if (p_actwk->use_skillid != 414)
              goto LABEL_1727;
            v765 = p_actwk->framecnt;
            if (v765 == 150)
            {
              sBtlSetFade(wk, 1026, 0, -1, 1);
              goto LABEL_1727;
            }
            if (v765 != 1)
            {
LABEL_1727:
              v767 = p_actwk;
              switch (p_actwk->use_skillid)
              {
                case 0x1E1:
                case 0x1E2:
                case 0x1E3:
                  if (v767->framecnt == 1)
                  {
                    DeleteAll_BossDead();
                  }
                  goto LABEL_1732;
                case 0x1E4:
                  v777 = v767->framecnt;
                  if (v777 == 150)
                  {
                    sBtlSetFade(wk, 1026, 0, 0, 2);
LABEL_1732:
                    if (p_actwk->use_skillid != 497)
                      goto LABEL_1756;
                    v768 = p_actwk->framecnt;
                    if (v768 == 110)
                    {
                      sBtlSetFade(wk, 1026, 0, -1, 1);
LABEL_1756:
                      v786 = p_actwk;
                      v787 = p_actwk->use_skillid;
                      if (v787 == 239)
                      {
                        if (v786->framecnt != 1)
                          goto LABEL_1771;
                        scene = wk->scene;
                        camera = scene->camera;
                        v793 = g_aTgtMove_LASTDEAD_0[0];
                        *(u64 *)&v793->m_vPos.x = *(u64 *)&camera->targetpos.x;
                        v793->m_vPos.z = camera->targetpos.z;
                        v794 = g_aCamMove_LASTDEAD_0[0];
                        *(u64 *)&v794->m_vPos.x = *(u64 *)&camera->camerapos.x;
                        v794->m_vPos.z = camera->camerapos.z;
                        sBtlSetMove(g_CamMov_LASTDEAD_0, 1);
                        sBtlSetMode(13);
                        v786 = p_actwk;
                        v787 = p_actwk->use_skillid;
                      }
                      if (v787 == 240 && (wk->side & 0x81) == 1 && v786->framecnt == 1)
                      {
                        wk->nakama_skill_name = 0;
                        sBtlDrawSkillNameOff(wk);
                      }
LABEL_1771:
                      v796 = sBtlGetActionTime(wk, 0);
                      if (v796 == INFINITY)
                        v797 = 0x80000000;
                      else
                        v797 = v796;
                      v798 = wk->actwk;
                      if (v798->framecnt < v797 || v798->action_flg)
                      {
                        wk->scrCnt[3] = 0;
                        goto LABEL_1781;
                      }
                      v811 = v798->use_skillid;
                      v798->action_flg = 1;
                      if (v811 == 891)
                      {
                        sBtlSetFade(wk, 2, 0, 0, 1);
                        v811 = wk->actwk->use_skillid;
                        if (v811 != 239)
                        {
LABEL_1798:
LABEL_1799:
                          CheckSkillMessage(wk, v811);
                          v814 = wk;
                          v814->scrCnt[3] = 0;
                          v814->enshutuCnt[3] = 0;
                          v815 = p_actwk;
                          v815->effectTime = v797;
                          v817 = v815->use_skillid;
                          if (sBtlSearchEffectData(v817) == -1)
                          {
                            sBtlForceDelete_SkillFlag_Acter(wk, 0x400u);
                          }
                          else
                          {
                            sBtlSetSkill_EffectData(wk, wk->actwk->use_skillid, 0);
                          }
LABEL_1781:
                          v800 = p_actwk;
                          if (p_actwk->framecnt != p_actwk->cmpframecnt2 + p_actwk->effectTime)
                            goto LABEL_2334;
                          v801 = v800->effect_flg;
                          if ((v801 & 1) != 0)
                          {
                            v809 = v800->cmpframecnt3;
                            dds3FadeOut(0, 0, 0, v809);
                            v802 = x;
                            v1013 = wk;
                            if (v1013->battlemode)
                              goto LABEL_2327;
                            v1013 = wk;
                            v1014 = v1013->UnitMng;
                            v1015 = v1013->playerID;
                            v1016 = sBtlSearchUnit_ID(v1014, v1015);
                            if (v1016->actwk->status == 42 || wk->para->devilid == 259)
                              goto LABEL_2327;
                            v1017 = v1016;
                            v1018 = oldposb;
                            v1019 = w;
                            v1020 = z;
                            sBtlSetMotion(v1017, 12, 0, 0, 0);
LABEL_2324:
                            sBtlSetAction(v1017, 42, 0);
                            z = v1020;
                            w = v1019;
                            v383 = v1018;
                            goto LABEL_2327;
                          }
                          v802 = x;
                          if ((v801 & 2) == 0)
                            goto LABEL_2327;
                          v804 = p_actwk->cmpframecnt3;
                          if (wk->encountno == 26)
                          {
                            if (!v805)
                            v806 = 96;
                            v807 = 96;
                            v808 = 32;
                          }
                          else
                          {
                            if (!v805)
                            v806 = 255;
                            v807 = 255;
                            v808 = 255;
                          }
                          dds3FadeOut(v806, v807, v808, v804);
                          v1044 = p_actwk->use_skillid;
                          if (v1044 == 504)
                          {
                            StopBattle();
                            sBtlStatusBitOn(wk, 0x10u);
                            if (wk->actwk->use_skillid != 230)
                            {
LABEL_2307:
                              goto LABEL_2308;
                            }
                          }
                          else if (v1044 != 230)
                          {
                            goto LABEL_2307;
                          }
                          StopBattle();
                          sBtlStatusBitOn(wk, 0x10u);
LABEL_2308:
                          v1046 = wk;
                          if (!v1046->battlemode)
                          {
                            v1018 = oldposb;
                            v1019 = w;
                            v1020 = z;
                            v1046 = wk;
                            v1047 = v1046->UnitMng;
                            v1048 = v1046->playerID;
                            v1049 = sBtlSearchUnit_ID(v1047, v1048);
                            if (v1049->actwk->status == 42 || wk->para->devilid == 259)
                              goto LABEL_2327;
                            v1017 = v1049;
                            goto LABEL_2324;
                          }
LABEL_2327:
                          v800 = p_actwk;
                          x = v802;
                          if (p_actwk->use_skillid == 410)
                          {
                            v1051 = 410;
                            v1052 = wk->sysmsgList;
                            sBtlCreateSM(v1052, wk, 72, v1051, 0, 120);
                            v1053 = wk;
                            v1053->status5 |= 0x40u;
                            v1053->status2 |= 1u;
                            sub_1A21FE0(2239, 0, v1054);
                            v800 = wk->actwk;
                          }
LABEL_2334:
                          if (v800->use_skillid != 240)
                          {
                            Proc(wk);
                            sBtlProc(wk);
                          }
                          sBtlMVSupport(wk);
                          UnitMV(wk);
                          v1434.x = x;
                          v1434.y = v383;
                          v1434.z = z;
                          v1434.w = w;
                          CheckMapHit(wk, v1434);
                          UnitMV_To_Basic(wk);
                          v1055 = wk->actwk;
                          v1056 = v1055->use_skillid;
                          if (v1056 == 487)
                          {
                            if (!sBtlCheckMotionEnd(wk) || p_actwk->action_flg != 1)
                              return v214;
                            p_actwk->action_flg = 2;
                            v1058 = 17;
                          }
                          else
                          {
                            if (v1056 != 494)
                            {
                              if (v1055->framecnt >= v1055->cmpframecnt2 + v1055->effectTime + v1055->cmpframecnt3)
                              {
                                v1060 = sBtlGetSkilltbl(v1056);
                                if ((v1060->type & 0x2FFF) != 0x2009)
                                  goto LABEL_2379;
                                v1062 = wk->effList;
                                v1063 = p_actwk->use_skillid;
                                if (!sBtlSearchEffect_SAB(v1062, v1063, 1u))
                                {
                                  v1065 = wk->effList;
                                  v1066 = p_actwk->use_skillid;
                                  if (!sBtlSearchEffect_SAB(v1065, v1066, 2u))
                                  {
                                    v1068 = wk->effList;
                                    v1069 = p_actwk->use_skillid;
                                    if (!sBtlSearchEffect_SAB(v1068, v1069, 5u))
                                    {
LABEL_2379:
                                      if (p_actwk->use_skillid == 240 && (wk->side & 0x81) == 1)
                                      {
                                        v1071 = wk->sysmsgList;
                                        sBtlCreateSM(v1071, wk, 71, 0, 0, 120);
                                      }
                                      if (wk->para->devilid == 259)
                                      {
                                        for (i = 0; ; ++i)
                                        {
                                          v1074 = wk->UnitMng;
                                          if (i >= v1074->number)
                                            break;
                                          v1074 = wk->UnitMng;
                                          pUnit = v1074->pUnitL[i]->pUnit;
                                          if (pUnit && pUnit->para->devilid == 260)
                                            goto LABEL_2648;
                                        }
                                        pUnit = 0;
LABEL_2648:
                                        pos.z = 2000.0;
                                        *(u64 *)&pos.x = 0x4416000000000000LL;
                                        v1128 = wk->effList;
                                        v1439.y = 600.0;
                                        v1439.z = 2000.0;
                                        v1439.x = 0.0;
                                        v1439.w = pos.w;
                                        sBtlCreateEff(v1128, pUnit, 14, 0, v1439, 0x80808080, 0, 1.0, 0);
                                      }
                                      else
                                      {
                                        v1114 = 285;
                                        switch (wk->para->devilid)
                                        {
                                          case 0x11D:
                                            v1114 = 288;
                                            goto LABEL_2897;
                                          case 0x11E:
                                            goto LABEL_2897;
                                          case 0x121:
                                            v1114 = 286;
                                            goto LABEL_2897;
                                          case 0x132:
                                            v1114 = 307;
                                            goto LABEL_2897;
                                          case 0x133:
                                            v1114 = 308;
                                            goto LABEL_2897;
                                          case 0x134:
                                            v1114 = 309;
LABEL_2897:
                                            v1264 = wk->pos.x;
                                            v1265 = wk->pos.y;
                                            v1266 = wk->pos.z;
                                            v1267 = wk->pos.w;
                                            sub_1B332C0(0, v1264, v1265, v1266, v1267);
                                            sub_1B33360(0, CameraEyePos.x, CameraEyePos.y, CameraEyePos.z, CameraEyePos.w);
                                            sub_1B33400(0);
                                            sub_1B335A0(&v1367, 0, v1269);
                                            v1271 = sub_18E6660(0, v1270);
                                            FromEuler(0.0, *(f32 *)&v1271, 0.0);
                                            sub_1B335A0(&v1365, 0, v1272);
                                            v1273 = wk->pos.x;
                                            v1274 = wk->pos.y;
                                            v1275 = wk->pos.z;
                                            v1276 = wk->pos.w;
                                            v1277 = v1365;
                                            v1278 = v1366;
                                            v1447.x = v1273;
                                            v1447.y = v1274;
                                            v1447.z = v1275;
                                            v1447.w = v1276;
                                            *(u64 *)&v1454.x = v1277;
                                            *(u64 *)&v1454.z = v1278;
                                            sBtlSetExPos(v1447, v1454);
                                            sBtlSetEncountData4(v1114, 100, 0, 0)->para->now->hp = wk->para->now->hp;
                                            break;
                                          default:
                                            break;
                                        }
                                      }
                                      sBtlEndAction(wk);
                                      v1279 = wk->actwk->effect_flg;
                                      if ((v1279 & 4) == 0)
                                      {
                                        if ((v1279 & 8) != 0)
                                        {
                                          for (j = 0; ; ++j)
                                          {
                                            v1282 = wk->UnitMng;
                                            if (j >= v1282->number)
                                              break;
                                            v1282 = wk->UnitMng;
                                            v1283 = v1282->pUnitL[j]->pUnit;
                                            if (v1283 && (v1283->side & 2) != 0)
                                              v1283->mode = 9;
                                          }
                                        }
                                        return 1;
                                      }
                                      if ((wk->side & 1) != 0)
                                      {
                                        sBtlDeletePlayer(wk);
                                        if (wk->next_motionID == 13)
                                          return 1;
                                        sBtlSetMotion(wk, 13, 0, 0, 0);
                                        return 1;
                                      }
                                      else if ((v1060->type & 0x2FFF) == 0x2009)
                                      {
                                        sBtlSetAction(wk, 10, 0);
                                        return 1;
                                      }
                                      else
                                      {
                                        wk->color = 0;
                                        v214 = 1;
                                        wk->mode = 9;
                                      }
                                    }
                                  }
                                }
                              }
                              return v214;
                            }
                            if (!sBtlCheckMotionEnd(wk) || p_actwk->action_flg != 1)
                              return v214;
                            p_actwk->action_flg = 2;
                            v1058 = 21;
                          }
                          sBtlSetMotion_ID(wk, v1058, 0, 0, 0);
                          return v214;
                        }
                      }
                      else if (v811 != 239)
                      {
                        goto LABEL_1798;
                      }
                      v819 = wk->effList;
                      sBtlForceResetDecAlpha(v819, wk, 4);
                      v811 = wk->actwk->use_skillid;
                      goto LABEL_1799;
                    }
                    if (v768 != 1)
                      goto LABEL_1756;
                    v769 = x;
                    v770 = w;
                    v771 = z;
                    sBtlEndSetsumaPadStop();
                    sBtlSetEnemyLastDeadStop(6, 80, 0.05, 0.05);
                    v772 = wk->pos.x;
                    v773 = wk->pos.y;
                    wk->m_rate = 0.5;
                    v775 = wk->pos.z;
                    v774 = wk->pos.w;
                    v1418.x = v772;
                    v1418.y = v773;
                    v1418.z = v775;
                    v1418.w = v774;
                    sBtlPlay3DSE_BaseVol(0x10021u, 159, v1418);
                    dds3PostHitFlashStart(0x28u);
                    z = v771;
                    w = v770;
                    x = v769;
                    if (sBtlCheckSetsuma())
                    {
LABEL_1742:
                      DeleteAll_BossDead();
                      goto LABEL_1756;
                    }
                    sBtlSetsuma_MagWaitDone();
                    goto LABEL_1742;
                  }
                  if (v777 != 1)
                    goto LABEL_1732;
                  v778 = x;
                  v779 = w;
                  v780 = z;
                  sBtlEndSetsumaPadStop();
                  sBtlSetEnemyLastDeadStop(6, 80, 0.05, 0.05);
                  v781 = wk->pos.x;
                  v782 = wk->pos.y;
                  wk->m_rate = 0.5;
                  v784 = wk->pos.z;
                  v783 = wk->pos.w;
                  v1419.x = v781;
                  v1419.y = v782;
                  v1419.z = v784;
                  v1419.w = v783;
                  sBtlPlay3DSE_BaseVol(0x10021u, 159, v1419);
                  dds3PostHitFlashStart(0x28u);
                  if (sBtlCheckSetsuma())
                  {
LABEL_1752:
                    DeleteAll_BossDead();
                    z = v780;
                    w = v779;
                    x = v778;
                    goto LABEL_1732;
                  }
                  sBtlSetsuma_MagWaitDone();
                  goto LABEL_1752;
                default:
                  goto LABEL_1732;
              }
            }
            sBtlEndSetsumaPadStop();
            sBtlSetEnemyLastDeadStop(10, 80, 0.05, 0.05);
            dds3PostHitFlashStart(0x28u);
            if (sBtlCheckSetsuma())
            {
LABEL_1723:
              DeleteAll_BossDead();
              goto LABEL_1727;
            }
            sBtlSetsuma_MagWaitDone();
            goto LABEL_1723;
          }
          if (v638 != 1)
            goto LABEL_1691;
          v639 = x;
          v640 = w;
          v641 = z;
          sBtlEndSetsumaPadStop();
          sBtlSetEnemyLastDeadStop(6, 80, 0.05, 0.05);
          v642 = wk->pos.x;
          v643 = wk->pos.y;
          wk->m_rate = 0.5;
          v645 = wk->pos.z;
          v644 = wk->pos.w;
          v1415.x = v642;
          v1415.y = v643;
          v1415.z = v645;
          v1415.w = v644;
          sBtlPlay3DSE_BaseVol(0x10021u, 159, v1415);
          dds3PostHitFlashStart(0x28u);
          z = v641;
          w = v640;
          x = v639;
          if (sBtlCheckSetsuma())
          {
LABEL_1445:
            DeleteAll_BossDead();
            goto LABEL_1691;
          }
          sBtlSetsuma_MagWaitDone();
          goto LABEL_1445;
        }
LABEL_1432:
        sBtlSetFade(wk, 1026, 0, 0, 1);
        v384 = wk->actwk;
        goto LABEL_1435;
      }
      dds3PostHitFlashStart(0x28u);
      sBtlEndSetsumaPadStop();
      sBtlSetEnemyLastDeadStop(1, 80, 0.05, 0.05);
      wk->m_rate = 0.5;
      v384 = wk->actwk;
      v385 = v384->framecnt;
      if (v385 != 150)
        goto LABEL_888;
      goto LABEL_1377;
    case 0x29u:
      v386 = sBtlGetActionTime(wk, 0);
      v387 = wk->actwk;
      if (v386 != INFINITY && v387->framecnt < (s32)v386 || v387->action_flg)
        goto LABEL_2054;
      v387->action_flg = 1;
      v388 = v387->use_skillid;
      CheckSkillMessage(wk, v388);
      v389 = (u16)wk->para->devilid;
      if (v389 == 297)
      {
        v390 = 298;
      }
      else
      {
        if (v389 != 290)
        {
          if (sBtlCheckMeshiyose(wk))
          {
            GroupID = wk->GroupID;
            sBtlGeneratorD_On(GroupID);
          }
          else
          {
            v1077 = wk->sysmsgList;
            v1078 = p_actwk->use_skillid;
            sBtlCreateSM(v1077, wk, 44, v1078, 0, 120);
          }
LABEL_2054:
          Proc(wk);
          sBtlProc(wk);
          sBtlMVSupport(wk);
          UnitMV(wk);
          v1428.x = x;
          v1428.y = oldposb;
          v1428.z = z;
          v1428.w = w;
          CheckMapHit(wk, v1428);
          UnitMV_To_Basic(wk);
          if (sBtlCheckLoopMotion(wk, wk->motionID))
          {
            if (p_actwk->action_flg != 1)
              return v214;
          }
          else
          {
            if (!sBtlCheckMotionEnd(wk))
              return v214;
          }
          sBtlSetAction(wk, 2, 0);
          sBtlEndAction(wk);
          v969 = wk->actwk->use_skillid;
          if (v969 == 506 || v969 == 221)
          {
            sBtlStatusBitOff(wk, 0xFFFFBFFF);
          }
          return v214;
        }
        v390 = 166;
      }
      sBtlSetEncountData(v390, 2, 1, 0);
      sBtlSetEncountData(v390, 3, 1, 0);
      goto LABEL_2054;
    case 0x2Bu:
      if (v237->framecnt <= 8)
      {
        v546 = wk->actaiwk;
        v547 = x;
        v548 = w;
        v549 = z;
        v550 = v546->scrRot.x;
        v551 = v546->scrRot.y;
        v552 = v546->scrRot.z;
        v553 = v546->scrRot.w;
        sub_1B332C0(0, v550, v551, v552, v553);
        sub_1B33360(0, wk->actaiwk->scrRot2.x, wk->actaiwk->scrRot2.y, wk->actaiwk->scrRot2.z, wk->actaiwk->scrRot2.w);
        Slerp((f32)wk->actwk->framecnt * 0.125, 0);
        sub_1B335A0(&wk->rot, 0, v554);
        sBtlSetRotateDeg(wk);
        v237 = wk->actwk;
        z = v549;
        w = v548;
        x = v547;
        if (v237->action_flg)
        {
LABEL_904:
          v391 = p_actwk;
          if ((u32)(p_actwk->framecnt - 25) < 0xFFFFFFEF)
            goto LABEL_905;
LABEL_1256:
          v557 = wk->actaiwk;
          v558 = x;
          v559 = w;
          v560 = z;
          v561 = v557->scrPos2.x;
          v562 = v557->scrPos2.y;
          v563 = v557->scrPos2.z;
          v564 = v557->scrPos2.w;
          sub_1B332C0(0, v561, v562, v563, v564);
          sub_1B33360(0, wk->actaiwk->scrPos.x, wk->actaiwk->scrPos.y, wk->actaiwk->scrPos.z, wk->actaiwk->scrPos.w);
          sub_1B33400(0);
          sub_1B33480(0, (f32)(wk->actwk->framecnt - 8) * 0.0625);
          sub_1B33360(0, wk->actaiwk->scrPos.x, wk->actaiwk->scrPos.y, wk->actaiwk->scrPos.z, wk->actaiwk->scrPos.w);
          *(__n128 *)&v565 = sub_1B33520(0);
          sub_1B335A0(&wk->pos, 0, v565);
          v391 = wk->actwk;
          z = v560;
          w = v559;
          x = v558;
          if (v391->action_flg == 1)
          {
LABEL_1259:
            if (v391->framecnt >= 24)
              v391->action_flg = 2;
          }
LABEL_1261:
          Proc(wk);
          sBtlProc(wk);
          sBtlMVSupport(wk);
          UnitMV(wk);
          v1413.x = x;
          v1413.y = oldposb;
          v1413.z = z;
          v1413.w = w;
          CheckMapHit(wk, v1413);
          UnitMV_To_Basic(wk);
          if (!sBtlCheckNextAction(wk) || p_actwk->framecnt < 24)
            return v214;
          wk->status &= 0xFFFFBFFE;
LABEL_1997:
          ResetAction(wk);
          sBtlSetAction(wk, 2, 0);
          goto LABEL_1998;
        }
      }
      else if (v237->action_flg)
      {
        goto LABEL_904;
      }
      wk->status |= 0x4001u;
      v237->action_flg = 1;
      v555 = v237->use_skillid;
      CheckSkillMessage(wk, v555);
      v556 = wk->actwk->use_skillid;
      if (sBtlSearchEffectData(v556) == -1)
      {
        sBtlForceDelete_SkillFlag_Acter(wk, 0x400u);
        v391 = p_actwk;
        if ((u32)(p_actwk->framecnt - 25) >= 0xFFFFFFEF)
          goto LABEL_1256;
      }
      else
      {
        sBtlSetSkill_EffectData(wk, wk->actwk->use_skillid, 0);
        v391 = p_actwk;
        if ((u32)(p_actwk->framecnt - 25) >= 0xFFFFFFEF)
          goto LABEL_1256;
      }
LABEL_905:
      if (v391->action_flg != 1)
        goto LABEL_1261;
      goto LABEL_1259;
    case 0x2Cu:
      v392 = v237->framecnt;
      if (v392 == 1)
      {
        dds3FadeOut(0xFFu, 0xFFu, 0xFFu, 4u);
        v237 = p_actwk;
        v392 = p_actwk->framecnt;
        if (v392 != 10)
        {
LABEL_911:
          if (v392 == 15)
            goto LABEL_912;
          goto LABEL_1200;
        }
      }
      else if (v392 != 10)
      {
        goto LABEL_911;
      }
      sBtlPlayerResetPlayerPosRot_Start_Boss(0);
      MOON_OUT();
      v237 = p_actwk;
      v392 = p_actwk->framecnt;
      if (v392 == 15)
      {
LABEL_912:
        v393 = v237->use_skillid;
        if (v393 <= 237)
        {
          if (v393 == 236)
          {
LABEL_1524:
            g_CamMov_LASTDEAD_R1_0_local = g_CamMov_LASTDEAD_R1_0;
LABEL_1527:
            sBtlSetMove(g_CamMov_LASTDEAD_R1_0_local, 1);
LABEL_1530:
            sBtlSetDof2Bokah(600.0, 10.0, 145.0, 8.0, 10.0, 145.0, 8.0);
            sBtlSetMode(13);
            v392 = p_actwk->framecnt;
            if (v392 != 18)
            {
LABEL_1533:
              if (v392 == 597)
                goto LABEL_1534;
              goto LABEL_1204;
            }
LABEL_1201:
            dds3FadeIn2(0xAu);
            v392 = p_actwk->framecnt;
            if (v392 == 597)
            {
LABEL_1534:
              dds3FadeOut(0xFFu, 0xFFu, 0xFFu, 8u);
              v392 = p_actwk->framecnt;
              if (v392 != 606)
              {
LABEL_1537:
                goto LABEL_1538;
              }
LABEL_1205:
              sBtlClearDof2Bokah();
              sBtlSetMode(2);
              v392 = p_actwk->framecnt;
LABEL_1538:
              v691 = sBtlGetActionTime(wk, 0);
              if (v691 == INFINITY || v392 >= (s32)v691)
              {
                v692 = p_actwk;
                if (!p_actwk->action_flg)
                {
                  v692->action_flg = 1;
                  v693 = v692->use_skillid;
                  CheckSkillMessage(wk, v693);
                  v694 = wk->actwk->use_skillid;
                  if (sBtlSearchEffectData(v694) == -1)
                  {
                    sBtlForceDelete_SkillFlag_Acter(wk, 0x400u);
                  }
                  else
                  {
                    sBtlSetSkill_EffectData(wk, wk->actwk->use_skillid, 0);
                  }
                }
              }
              Proc(wk);
              sBtlProc(wk);
              sBtlMVSupport(wk);
              UnitMV(wk);
              v1427.x = x;
              v1427.y = oldposb;
              v1427.z = z;
              v1427.w = w;
              CheckMapHit(wk, v1427);
              UnitMV_To_Basic(wk);
              if (!sBtlCheckNextAction(wk))
                return v214;
              v960 = p_actwk->use_skillid;
              if (v960 <= 237)
              {
                if (v960 == 236)
                {
LABEL_2027:
                  v961 = sBtlModelNodeFadeout(wk, "r arm root");
                  v963 = &wk->scrUnitList[1];
                  goto LABEL_2030;
                }
                if (v960 != 237)
                  goto LABEL_2032;
              }
              else if (v960 != 499)
              {
                if (v960 != 498)
                {
LABEL_2032:
                  v961 = -1;
                  if ((p_actwk->use_skillid & 0xFFFFFFFE) != 0x1F2)
                    goto LABEL_2036;
                  goto LABEL_2033;
                }
                goto LABEL_2027;
              }
              v961 = sBtlModelNodeFadeout(wk, "l arm root");
              v963 = &wk->scrUnitList[2];
LABEL_2030:
              *(u32 *)(*(u64 *)v963 + 372) = 9;
              if ((p_actwk->use_skillid & 0xFFFFFFFE) != 0x1F2)
                goto LABEL_2036;
LABEL_2033:
              wk->scrFlag &= ~0x80000u;
LABEL_2036:
              if ((u32)(v961 + 1) < 2)
                return v214;
              dds3FadeIn2(0xFu);
              goto LABEL_1997;
            }
LABEL_1204:
            if (v392 != 606)
              goto LABEL_1537;
            goto LABEL_1205;
          }
          if (v393 != 237)
            goto LABEL_1530;
        }
        else if (v393 != 499)
        {
          if (v393 != 498)
            goto LABEL_1530;
          goto LABEL_1524;
        }
        g_CamMov_LASTDEAD_R1_0_local = g_CamMov_LASTDEAD_L1_0;
        goto LABEL_1527;
      }
LABEL_1200:
      if (v392 != 18)
        goto LABEL_1533;
      goto LABEL_1201;
    case 0x2Du:
      v394 = v237->framecnt;
      v395 = sBtlGetActionTime(wk, 0);
      if (v395 == INFINITY || v394 >= (s32)v395)
      {
        v396 = p_actwk;
        if (!p_actwk->action_flg)
        {
          v396->action_flg = 1;
          v397 = v396->use_skillid;
          CheckSkillMessage(wk, v397);
          v398 = wk->actwk->use_skillid;
          if (sBtlSearchEffectData(v398) == -1)
          {
            sBtlForceDelete_SkillFlag_Acter(wk, 0x400u);
          }
          else
          {
            sBtlSetSkill_EffectData(wk, wk->actwk->use_skillid, 0);
          }
        }
      }
      Proc(wk);
      sBtlProc(wk);
      sBtlMVSupport(wk);
      UnitMV(wk);
      v1424.x = x;
      v1424.y = oldposb;
      v1424.z = z;
      v1424.w = w;
      CheckMapHit(wk, v1424);
      UnitMV_To_Basic(wk);
      if (sBtlCheckNextAction(wk) || p_actwk->use_skillid == 503 && p_actwk->framecnt >= 101)
      {
        goto LABEL_1995;
      }
      return v214;
    case 0x2Eu:
      sBtlGetCylinderData(wk, v3);
      if (wk->actwk->framecnt < 121)
        return v214;
      v399 = wk->pos.x;
      v400 = wk->pos.y + (f32)(v3->height / 150.0);
      wk->pos.y = v400;
      v402 = wk->pos.z;
      v401 = wk->pos.w;
      v1393.x = v399;
      v1393.y = v400;
      v1393.z = v402;
      v1393.w = v401;
      dds3SetPosPoseSet(&wk->pBasic, v1393);
      v403 = p_actwk;
      if (p_actwk->framecnt < 270 || v403->action_flg)
        return v214;
      v403->action_flg = 1;
      if (sBtlGetNakama(0) == wk)
      {
        v404 = 0;
      }
      else
      {
        v404 = 1;
        if (sBtlGetNakama(1) != wk)
          goto LABEL_2217;
      }
      v1022 = wk->summonindex[v404];
      SetReturn(v1022, 1);
      v1023 = wk;
      p_stock_mask = &v1023->stock_mask;
      v1025 = v1023->summonindex[v404];
      sBtlResetBit(p_stock_mask, v1025);
LABEL_2217:
      v1027 = wk->sysmsgList;
      sBtlCreateSM(v1027, wk, 35, 0, 0, 120);
      return v214;
    case 0x2Fu:
      v405 = v237->use_skillid;
      sBtlSetSuperArmor(wk, v405, -2);
      v406 = wk->actwk->framecnt;
      v407 = sBtlGetActionTime(wk, 0);
      if ((v407 == INFINITY || v406 >= (s32)v407) && !p_actwk->action_flg)
      {
        v408 = p_actwk->use_skillid;
        if (sBtlHDloadChk(v408))
        {
          v409 = p_actwk;
          v409->action_flg = 1;
          v410 = v409->use_skillid;
          CheckSkillMessage(wk, v410);
          v411 = wk->actwk->use_skillid;
          if (sBtlSearchEffectData(v411) == -1)
          {
            sBtlForceDelete_SkillFlag_Acter(wk, 0x400u);
          }
          else
          {
            sBtlSetSkill_EffectData(wk, wk->actwk->use_skillid, 0);
          }
        }
      }
      Proc(wk);
      sBtlProc(wk);
      sBtlMVSupport(wk);
      UnitMV(wk);
      v1433.x = x;
      v1433.y = oldposb;
      v1433.z = z;
      v1433.w = w;
      CheckMapHit(wk, v1433);
      UnitMV_To_Basic(wk);
      if (!sBtlCheckNextAction(wk))
        return v214;
      goto LABEL_2235;
    case 0x30u:
      v412 = v237->framecnt;
      v413 = sBtlGetActionTime(wk, 0);
      v414 = oldposb;
      if ((v413 == INFINITY || v412 >= (s32)v413) && !p_actwk->action_flg)
      {
        p_actwk->action_flg = 1;
        v415 = wk->para;
        v416 = sBtlGetBadStatus(v415);
        if (v416 != 17)
        {
          v417 = v416;
          if (v416 != 22)
          {
            sBtlResetBadStatus(wk, 1 << v417);
            sBtlRestartMotion(wk);
            v418 = wk->status;
            wk->getMag = 0;
            wk->status = v418 & 0xFFFFFFDF;
            wk->hstatus &= ~0x10u;
          }
        }
        v419 = p_actwk->use_skillid;
        sBtlSetBadStatus_No(wk, v419, 0xCu, 0, -1);
        sBtlEndAction(wk);
      }
      Proc(wk);
      goto LABEL_1989;
    case 0x31u:
      v421 = wk;
      v422 = v421->UnitMng;
      v423 = v421->playerID;
      sBtlSearchUnit_ID(v422, v423);
      v424 = p_actwk->framecnt;
      v425 = sBtlGetActionTime(wk, 0);
      if (v425 == INFINITY || v424 >= (s32)v425)
      {
        v426 = p_actwk;
        if (!p_actwk->action_flg)
        {
          v426->action_flg = 1;
          v427 = v426->use_skillid;
          if (sBtlSearchEffectData(v427) == -1)
          {
            sBtlForceDelete_SkillFlag_Acter(wk, 0x400u);
          }
          else
          {
            sBtlSetSkill_EffectData(wk, wk->actwk->use_skillid, 0);
            CheckSkillMessage(wk, 73);
          }
        }
      }
      v893 = p_actwk;
      if (p_actwk->framecnt >= 225 && v893->action_flg == 1)
      {
        v893->action_flg = 2;
        if (sBtlSearchEffectData(73) != -1)
        {
          v1329 = w;
          t1e = x;
          t1_4d = z;
          wk->aiwk->scrStep3 = 2;
          PointLast = sBtlGetPointLast(wk, 73);
          sBtlGetPointData(PointLast, &pos, &rot);
          v896 = wk->pos.x;
          v895 = wk->pos.y;
          v897 = wk->pos.z;
          v898 = wk->pos.w;
          v1320 = wk->pos.y;
          v895 = v1320;
          sub_1B332C0(0, v896, v895, v897, v898);
          sub_1B33360(0, pos.x, pos.y, pos.z, pos.w);
          sub_1B33400(0);
          sub_1B335A0(&v1367, 0, v899);
          v901 = sub_18E6660(0, v900);
          v902 = *(f32 *)&v901;
          FromEuler(0.0, *(f32 *)&v901, 0.0);
          sub_1B335A0(&wk->rot, 0, v903);
          wk->mv_rotbk = v902 * 57.29578;
          sBtlSetSkill_EffectData(wk, 73, 0);
          *(__n128 *)&v904 = sub_1B332C0(0, v71, v72, v73, v74);
          sub_1B335A0(&wk->rot, 0, v904);
          x = t1e;
          z = t1_4d;
          wk->mv_rotbk = mv_rotbk;
          w = v1329;
        }
      }
      v905 = p_actwk;
      if (p_actwk->framecnt >= 245 && v905->action_flg == 2)
      {
        v905->action_flg = 3;
        if (sBtlSearchEffectData(73) != -1)
        {
          v1330 = w;
          t1f = x;
          t1_4e = z;
          wk->aiwk->scrStep3 = 1;
          v906 = sBtlGetPointLast(wk, 73);
          sBtlGetPointData(v906, &pos, &rot);
          v908 = wk->pos.x;
          v907 = wk->pos.y;
          v909 = wk->pos.z;
          v910 = wk->pos.w;
          v1321 = wk->pos.y;
          v907 = v1321;
          sub_1B332C0(0, v908, v907, v909, v910);
          sub_1B33360(0, pos.x, pos.y, pos.z, pos.w);
          sub_1B33400(0);
          sub_1B335A0(&v1367, 0, v911);
          v913 = sub_18E6660(0, v912);
          v914 = *(f32 *)&v913;
          FromEuler(0.0, *(f32 *)&v913, 0.0);
          sub_1B335A0(&wk->rot, 0, v915);
          wk->mv_rotbk = v914 * 57.29578;
          sBtlSetSkill_EffectData(wk, 73, 0);
          *(__n128 *)&v916 = sub_1B332C0(0, v71, v72, v73, v74);
          sub_1B335A0(&wk->rot, 0, v916);
          x = t1f;
          z = t1_4e;
          wk->mv_rotbk = mv_rotbk;
          w = v1330;
        }
      }
      v917 = p_actwk;
      if (p_actwk->framecnt >= 265 && v917->action_flg == 3)
      {
        v917->action_flg = 4;
        if (sBtlSearchEffectData(73) != -1)
        {
          v1331 = w;
          t1g = x;
          t1_4f = z;
          wk->aiwk->scrStep3 = 3;
          v918 = sBtlGetPointLast(wk, 73);
          sBtlGetPointData(v918, &pos, &rot);
          v920 = wk->pos.x;
          v919 = wk->pos.y;
          v921 = wk->pos.z;
          v922 = wk->pos.w;
          v1322 = wk->pos.y;
          v919 = v1322;
          sub_1B332C0(0, v920, v919, v921, v922);
          sub_1B33360(0, pos.x, pos.y, pos.z, pos.w);
          sub_1B33400(0);
          sub_1B335A0(&v1367, 0, v923);
          v925 = sub_18E6660(0, v924);
          v926 = *(f32 *)&v925;
          FromEuler(0.0, *(f32 *)&v925, 0.0);
          sub_1B335A0(&wk->rot, 0, v927);
          wk->mv_rotbk = v926 * 57.29578;
          sBtlSetSkill_EffectData(wk, 73, 0);
          *(__n128 *)&v928 = sub_1B332C0(0, v71, v72, v73, v74);
          sub_1B335A0(&wk->rot, 0, v928);
          x = t1g;
          z = t1_4f;
          wk->mv_rotbk = mv_rotbk;
          w = v1331;
        }
      }
      v929 = p_actwk;
      if (p_actwk->framecnt >= 285 && v929->action_flg == 4)
      {
        v929->action_flg = 5;
        if (sBtlSearchEffectData(73) != -1)
        {
          v1332 = w;
          t1h = x;
          t1_4g = z;
          wk->aiwk->scrStep3 = 0;
          v930 = sBtlGetPointLast(wk, 73);
          sBtlGetPointData(v930, &pos, &rot);
          v932 = wk->pos.x;
          v931 = wk->pos.y;
          v933 = wk->pos.z;
          v934 = wk->pos.w;
          v1323 = wk->pos.y;
          v931 = v1323;
          sub_1B332C0(0, v932, v931, v933, v934);
          sub_1B33360(0, pos.x, pos.y, pos.z, pos.w);
          sub_1B33400(0);
          sub_1B335A0(&v1367, 0, v935);
          v937 = sub_18E6660(0, v936);
          v938 = *(f32 *)&v937;
          FromEuler(0.0, *(f32 *)&v937, 0.0);
          sub_1B335A0(&wk->rot, 0, v939);
          wk->mv_rotbk = v938 * 57.29578;
          sBtlSetSkill_EffectData(wk, 73, 0);
          *(__n128 *)&v940 = sub_1B332C0(0, v71, v72, v73, v74);
          sub_1B335A0(&wk->rot, 0, v940);
          x = t1h;
          z = t1_4g;
          wk->mv_rotbk = mv_rotbk;
          w = v1332;
        }
      }
      v941 = p_actwk;
      if (p_actwk->framecnt >= 305 && v941->action_flg == 5)
      {
        v941->action_flg = 6;
        if (sBtlSearchEffectData(73) != -1)
        {
          v1333 = w;
          t1i = x;
          t1_4h = z;
          wk->aiwk->scrStep3 = 4;
          v942 = sBtlGetPointLast(wk, 73);
          sBtlGetPointData(v942, &pos, &rot);
          v944 = wk->pos.x;
          v943 = wk->pos.y;
          v945 = wk->pos.z;
          v946 = wk->pos.w;
          v1324 = wk->pos.y;
          v943 = v1324;
          sub_1B332C0(0, v944, v943, v945, v946);
          sub_1B33360(0, pos.x, pos.y, pos.z, pos.w);
          sub_1B33400(0);
          sub_1B335A0(&v1367, 0, v947);
          v949 = sub_18E6660(0, v948);
          v950 = *(f32 *)&v949;
          FromEuler(0.0, *(f32 *)&v949, 0.0);
          sub_1B335A0(&wk->rot, 0, v951);
          wk->mv_rotbk = v950 * 57.29578;
          sBtlSetSkill_EffectData(wk, 73, 0);
          *(__n128 *)&v952 = sub_1B332C0(0, v71, v72, v73, v74);
          sub_1B335A0(&wk->rot, 0, v952);
          x = t1i;
          z = t1_4h;
          wk->mv_rotbk = mv_rotbk;
          w = v1333;
        }
      }
      v953 = p_actwk;
      if (p_actwk->framecnt >= 340 && v953->action_flg == 6)
        v953->action_flg = 7;
      Proc(wk);
      sBtlProc(wk);
      sBtlMVSupport(wk);
      UnitMV(wk);
      v1425.x = x;
      v1425.y = oldposb;
      v955 = wk;
      v1425.z = z;
      v1425.w = w;
      goto LABEL_2184;
    case 0x32u:
      v414 = oldposb;
      v429 = wk;
      v430 = v429->UnitMng;
      v431 = v429->playerID;
      sBtlSearchUnit_ID(v430, v431);
      v432 = sBtlGetActionTime(wk, 0);
      if (v432 == INFINITY)
        v433 = 0x80000000;
      else
        v433 = v432;
      v434 = wk->actwk;
      if (v434->framecnt >= v433 && !v434->action_flg)
      {
        v434->action_flg = 1;
        wk->aiwk->scrStep3 = 0;
        v435 = v434->use_skillid;
        if (sBtlSearchEffectData(v435) == -1)
        {
          sBtlForceDelete_SkillFlag_Acter(wk, 0x400u);
        }
        else
        {
          sBtlSetSkill_EffectData(wk, wk->actwk->use_skillid, 0);
        }
      }
      v958 = p_actwk;
      if (p_actwk->framecnt >= v433 + 30 && v958->action_flg == 1)
      {
        v958->action_flg = 2;
        wk->aiwk->scrStep3 = 1;
        v959 = v958->use_skillid;
        if (sBtlSearchEffectData(v959) == -1)
        {
          sBtlForceDelete_SkillFlag_Acter(wk, 0x400u);
        }
        else
        {
          sBtlSetSkill_EffectData(wk, wk->actwk->use_skillid, 0);
        }
      }
      Proc(wk);
LABEL_1989:
      sBtlProc(wk);
      sBtlMVSupport(wk);
      UnitMV(wk);
      v1426.x = x;
      v1426.y = v414;
      v1426.z = z;
      v1426.w = w;
      CheckMapHit(wk, v1426);
      UnitMV_To_Basic(wk);
LABEL_1992:
      if (!sBtlCheckNextAction(wk))
        return v214;
LABEL_1995:
      goto LABEL_1997;
    case 0x33u:
      v437 = wk;
      v438 = v437->UnitMng;
      v439 = v437->playerID;
      v440 = sBtlSearchUnit_ID(v438, v439);
      v441 = sBtlGetActionTime(wk, 0);
      v442 = wk->actwk;
      t1_4c = v441;
      if (v442->action_flg)
      {
        v443 = v440->pos.z;
        v444 = x;
        v445 = v440->pos.x;
        if (v443 > 760.0)
          v443 = 760.0;
        if (v443 >= -900.0)
          v446 = v443;
        else
          v446 = -900.0;
        if (v445 > 950.0)
          v445 = 950.0;
        v447 = wk->actaiwk;
        v448 = v447->scrPos2.x;
        v449 = v447->scrPos2.z;
        if (v445 >= -950.0)
          v450 = v445;
        else
          v450 = -950.0;
        LenXZ = sBtlGetLenXZ(v448, v449, v450, v446);
        x = v444;
        if (LenXZ > 8.0)
        {
          v452 = wk->actaiwk;
          v453 = v452->scrPos2.x;
          v454 = v452->scrPos2.z;
          sBtlGetMovePosToPos(v453, v454, v450, v446, 8.0, (f32 *)&GetZ + 1, &GetZ);
          x = v444;
          v455 = wk->actaiwk;
          v455->scrPos2.x = *((f32 *)&GetZ + 1);
          LODWORD(v455->scrPos2.z) = GetZ;
        }
        goto LABEL_1586;
      }
      v442->action_flg = 1;
      v599 = v442->use_skillid;
      if (v599 <= 229)
      {
        if (v599 != 228)
        {
          if (v599 != 229)
            goto LABEL_1577;
LABEL_1512:
          v677 = v440->pos.x;
          v678 = wk->actaiwk;
          v678->scrPos.y = 0.0;
          v679 = 760.0;
          v678->scrPos.x = v677;
          v680 = v440->pos.z;
          if (v680 <= 760.0)
          {
            v679 = v440->pos.z;
            if (v680 < -900.0)
              v679 = -900.0;
          }
          v681 = x;
          *(f32 *)&v682 = 950.0;
          if (v677 > 950.0 || (*(f32 *)&v682 = -950.0, v677 < -950.0))
          {
            v677 = *(f32 *)&v682;
            v678->scrPos.x = *(f32 *)&v682;
          }
          v684 = v678->scrPos.w;
          v685 = v679 + 50.0;
          v678->scrPos.z = v679 + 50.0;
          *(__n128 *)&v686 = sub_1B332C0(0, v677, 0.0, v685, v684);
          sub_1B335A0(&wk->actaiwk->scrPos2, 0, v686);
          wk->actaiwk->scrPos2.x = v440->pos.x + 700.0;
          sBtlGetPointData(17, &pos, &rot);
          x = v681;
          v688 = pos.x + -300.0;
          v689 = wk->actaiwk;
          if (v689->scrPos2.x <= (f32)(pos.x + -300.0))
          {
LABEL_1577:
            v706 = p_actwk->use_skillid;
            if ((u32)(v706 - 228) <= 7 && ((1 << (v706 + 28)) & 0x83) != 0 || v706 == 474)
            {
              v707 = v440->pos.x;
              v708 = wk->actaiwk;
              v708->scrPos2.y = 0.0;
              z_low = 1144913920;
              v708->scrPos2.x = v707;
              v710 = v440->pos.z;
              if (v710 <= 760.0)
              {
                z_low = LODWORD(v440->pos.z);
                if (v710 < -900.0)
                  z_low = -1000275968;
              }
              v711 = 1148026880;
              LODWORD(v708->scrPos2.z) = z_low;
              if (v707 > 950.0 || (v711 = -999456768, v707 < -950.0))
                LODWORD(v708->scrPos2.x) = v711;
            }
LABEL_1586:
            v712 = z;
            v1328 = w;
            t1a = x;
            v713 = (wk->actwk->framecnt - 120) & ~((wk->actwk->framecnt - 120) >> 31);
            if ((u32)v713 <= 0xC8)
              v714 = (f32)v713 / 200.0;
            else
              v714 = 1.0;
            v715 = wk->actaiwk;
            v716 = &v715->scrPos3.x;
            v717 = v715->scrPos.x;
            v718 = v715->scrPos.y;
            v719 = v715->scrPos.z;
            v720 = v715->scrPos2.x;
            v721 = v715->scrPos2.y;
            v722 = v715->scrPos2.z;
            p_y = &v715->scrPos3.y;
            p_z = &v715->scrPos3.z;
            sBtlGetNormalPosToPos(v717, v718, v719, v720, v721, v722, v714, v716, p_y, p_z);
            v725 = p_actwk;
            v726 = p_actwk->framecnt;
            if (v726 == 130)
            {
              Add(0.0, 0.0, 0.0, 0);
              v725 = p_actwk;
              v726 = p_actwk->framecnt;
              v727 = v1328;
              v728 = oldposb;
              if (v726 != 330)
                goto LABEL_1593;
            }
            else
            {
              v727 = v1328;
              v728 = oldposb;
              if (v726 != 330)
              {
LABEL_1593:
                if ((u32)(v726 - 330) < 0xFFFFFF38)
                  goto LABEL_1610;
LABEL_1597:
                v729 = v725->use_skillid;
                if (v729 <= 229)
                {
                  if (v729 == 228)
                  {
LABEL_1606:
                    v730 = 312;
LABEL_1609:
                    UnitFromDevilID = sBtlGetUnitFromDevilID(v730);
                    SetTgtPos(UnitFromDevilID->pos.x, UnitFromDevilID->pos.y, UnitFromDevilID->pos.z, wk->actaiwk->scrPos3.x, wk->actaiwk->scrPos3.y, wk->actaiwk->scrPos3.z);
                    goto LABEL_1610;
                  }
                  if (v729 != 229)
                    goto LABEL_1610;
                }
                else if (v729 != 474)
                {
                  if (v729 != 235)
                  {
LABEL_1610:
                    v732 = p_actwk;
                    v733 = p_actwk->framecnt;
                    if ((u32)(v733 - 330) >= 0xFFFFFFD8)
                    {
                      SetScale((f32)((f32)(v733 - 290) * -0.025) + 1.0);
                      v732 = p_actwk;
                      v733 = p_actwk->framecnt;
                    }
                    if ((t1_4c == INFINITY || v733 >= (s32)t1_4c) && v732->action_flg == 1)
                    {
                      v734 = v732->use_skillid;
                      if (sBtlHDloadChk(v734))
                      {
                        v735 = p_actwk;
                        v735->action_flg = 2;
                        v736 = v735->use_skillid;
                        CheckSkillMessage(wk, v736);
                        v737 = wk->actwk->use_skillid;
                        if (sBtlSearchEffectData(v737) == -1)
                        {
                          sBtlForceDelete_SkillFlag_Acter(wk, 0x400u);
                        }
                        else
                        {
                          sBtlSetSkill_EffectData(wk, wk->actwk->use_skillid, 0);
                        }
                      }
                    }
                    Proc(wk);
                    sBtlProc(wk);
                    sBtlMVSupport(wk);
                    UnitMV(wk);
                    v1425.x = t1a;
                    v1425.y = v728;
                    v1425.z = v712;
                    v1425.w = v727;
                    v955 = wk;
LABEL_2184:
                    CheckMapHit(v955, v1425);
                    UnitMV_To_Basic(wk);
                    if (sBtlCheckNextAction(wk))
                    {
                      ResetAction(wk);
                      sBtlSetAction(wk, 2, 0);
                      sBtlEndAction(wk);
                    }
                    return 1;
                  }
                  goto LABEL_1606;
                }
                v730 = 313;
                goto LABEL_1609;
              }
            }
            DeleteAll();
            v725 = p_actwk;
            if ((u32)(p_actwk->framecnt - 330) < 0xFFFFFF38)
              goto LABEL_1610;
            goto LABEL_1597;
          }
LABEL_1576:
          v689->scrPos2.x = v688;
          goto LABEL_1577;
        }
      }
      else if (v599 != 474)
      {
        if (v599 != 235)
          goto LABEL_1577;
        goto LABEL_1512;
      }
      v695 = v440->pos.x;
      v696 = wk->actaiwk;
      v696->scrPos.y = 0.0;
      v697 = 760.0;
      v696->scrPos.x = v695;
      v698 = v440->pos.z;
      if (v698 <= 760.0)
      {
        v697 = v440->pos.z;
        if (v698 < -900.0)
          v697 = -900.0;
      }
      v699 = x;
      *(f32 *)&v700 = 950.0;
      if (v695 > 950.0 || (*(f32 *)&v700 = -950.0, v695 < -950.0))
      {
        v695 = *(f32 *)&v700;
        v696->scrPos.x = *(f32 *)&v700;
      }
      v702 = v696->scrPos.w;
      v703 = v697 + 50.0;
      v696->scrPos.z = v697 + 50.0;
      *(__n128 *)&v704 = sub_1B332C0(0, v695, 0.0, v703, v702);
      sub_1B335A0(&wk->actaiwk->scrPos2, 0, v704);
      wk->actaiwk->scrPos2.x = v440->pos.x + -700.0;
      sBtlGetPointData(10, &pos, &rot);
      x = v699;
      v688 = pos.x + 300.0;
      v689 = wk->actaiwk;
      if (v689->scrPos2.x >= (f32)(pos.x + 300.0))
        goto LABEL_1577;
      goto LABEL_1576;
    case 0x34u:
      v456 = v237->framecnt;
      v457 = sBtlGetActionTime(wk, 0);
      v239 = oldposb;
      if (v457 == INFINITY || v456 >= (s32)v457)
      {
        v458 = p_actwk;
        if (!p_actwk->action_flg)
        {
          v458->action_flg = 1;
          v459 = v458->use_skillid;
          CheckSkillMessage(wk, v459);
          v460 = wk->actwk->use_skillid;
          if (sBtlSearchEffectData(v460) == -1)
          {
            sBtlForceDelete_SkillFlag_Acter(wk, 0x400u);
          }
          else
          {
            sBtlSetSkill_EffectData(wk, wk->actwk->use_skillid, 0);
          }
        }
      }
      Proc(wk);
LABEL_497:
      sBtlProc(wk);
      goto LABEL_2161;
    case 0x35u:
      if ((u32)(v237->framecnt - 55) >= 0xFFFFFFCF && wk->actaiwk->targetID != -1)
      {
        if (!sBtlChkKaihiMawari(wk))
        {
          v462 = wk->UnitMng;
          v463 = wk->actaiwk->targetID;
          v464 = sBtlSearchUnit_ID(v462, v463);
          if (v464)
          {
            v465 = v464;
            if (v464 != wk)
            {
              SetAtkDirHD(wk, v465, 45.0, 10.0);
            }
          }
        }
      }
      sBtlMVSupport(wk);
      UnitMV(wk);
      v1394.x = x;
      v1394.y = oldposb;
      v1394.z = z;
      v1394.w = w;
      CheckMapHit(wk, v1394);
      UnitMV_To_Basic(wk);
      if (wk->actwk->framecnt < wk->actwk->cmpframecnt)
        return v214;
      if (!EisyoEndCheck(wk))
        return v214;
      sBtlSetSkill_MotionData(wk, wk->actwk->use_skillid);
      v466 = 90;
      v325 = wk;
      v326 = 6;
      goto LABEL_2240;
    case 0x36u:
      v467 = v237->framecnt;
      if (v467 <= 1)
      {
        v468 = oldposb;
        v567 = wk->status | 1;
        wk->flg |= 2u;
        color = wk->color;
        wk->status = v567;
        wk->warp_bk_color = color;
        if (v467 == 1)
        {
          sBtlSetMotion(wk, 29, 8, 0, 0);
          v467 = wk->actwk->framecnt;
        }
      }
      else
      {
        v468 = oldposb;
      }
      if ((u32)(v467 - 20) >= 0xFFFFFFF0)
      {
        v569 = wk->color;
        v570 = (u8)v569;
        v571.n64_u64[0] = vdup_n_s32(v569).n64_u64[0];
        v572 = HIBYTE(v569);
        v573.n64_u64[0] = vand_s8(vshl_u32(v571, (uint32x2_t)0xFFFFFFF0FFFFFFF8LL), (int8x8_t)0xFF000000FFLL).n64_u64[0];
        switch (v467)
        {
          case 4:
            goto LABEL_1823;
          case 5:
            v574 = x;
            v570 -= 16;
            goto LABEL_1815;
          case 6:
          case 7:
            v574 = x;
            v570 -= 32;
LABEL_1815:
            v573.n64_u64[0] = vadd_s32(v573, (int32x2_t)0x1F0000001FLL).n64_u64[0];
            goto LABEL_1816;
          case 8:
          case 9:
            v574 = x;
            v570 -= 32;
            v573.n64_u64[0] = vadd_s32(v573, (int32x2_t)0x1F0000001FLL).n64_u64[0];
            goto LABEL_1559;
          default:
            if ((u32)v467 > 0x12)
            {
              v467 = 19;
              goto LABEL_1823;
            }
            v574 = x;
LABEL_1559:
            v572 -= 16;
LABEL_1816:
            v820 = v570 & ~(v570 >> 31);
            v821 = v572 & ~(v572 >> 31);
            v822.n64_u64[0] = vmax_s32(v573, 0).n64_u64[0];
            v823 = vshl_u32(v822, (uint32x2_t)0x1000000008LL).n64_u64[0];
            wk->chgcolor = v823 | v820 | HIDWORD(v823) | (v821 << 24);
            sBtlChangeModelColor(wk);
            x = v574;
            v467 = wk->actwk->framecnt;
            if (v467 == 10)
            {
              v824 = v574;
              v825 = w;
              v826 = wk->pos.x;
              v827 = wk->pos.y;
              v828 = z;
              v830 = wk->pos.z;
              v829 = wk->pos.w;
              v1420.x = v826;
              v1420.y = v827;
              v1420.z = v830;
              v1420.w = v829;
              sBtlPlay3DSE(0x1002Bu, v1420);
              z = v828;
              w = v825;
              x = v824;
              v467 = p_actwk->framecnt;
            }
            break;
        }
      }
      if ((u32)(v467 - 20) < 0xFFFFFFEF)
        goto LABEL_1833;
LABEL_1823:
      v831 = wk->actaiwk;
      v832 = wk->pos.x;
      v833 = wk->pos.z;
      v834 = v831->ppos.x - v832;
      v835 = v831->ppos.z - v833;
      v836 = sqrtf((f32)(v834 * v834) + (f32)(v835 * v835));
      if (v836 > 0.0)
      {
        *(f32 *)&v1367 = v834 / v836;
        *(f32 *)&v1368 = v835 / v836;
      }
      v837 = (f32)((f32)v467 * 1.2) + 4.0;
      if (v836 > v837)
      {
        v832 = v832 + (f32)(v837 * *(f32 *)&v1367);
        v833 = v833 + (f32)(v837 * *(f32 *)&v1368);
        wk->pos.x = v832;
        wk->pos.z = v833;
      }
      if (v836 > 10.0)
      {
        t1c = x;
        v838 = wk->pos.y;
        v1421.w = wk->pos.w;
        v1450.x = wk->rot.x;
        v1450.y = wk->rot.y;
        v1450.z = wk->rot.z;
        v841 = wk->rot.w;
        v842 = v831->ppos.x;
        v1311 = wk->rot.x;
        v1318 = wk->pos.w;
        v1297 = wk->rot.z;
        v1304 = wk->rot.y;
        v1450.z = v1297;
        v1450.y = v1304;
        v1450.x = v1311;
        v1421.w = v1318;
        v1421.x = v832;
        v1421.y = v838;
        v1421.z = v833;
        v1450.w = v841;
        *(u64 *)&v1369.x = 0;
        v843 = sBtlGetRadian(v1421, v1450, v1369, v842);
        sBtlAddUnitDeg(wk, v843 * 0.5);
        *(__n128 *)&v845 = sub_1B335A0(&wk->rot, 0, v844);
        sub_1B335A0(&wk->rotbk, 0, v845);
        x = t1c;
        v468 = oldposb;
        v467 = wk->actwk->framecnt;
LABEL_1833:
        if (v467 == 21)
        {
          v846 = wk->actaiwk;
          v847 = x;
          v848 = w;
          v849 = z;
          v850 = v846->ppos.x;
          v851 = v846->ppos.y;
          v852 = v846->ppos.z;
          v853 = v846->ppos.w;
          *(__n128 *)&v854 = sub_1B332C0(0, v850, v851, v852, v853);
          sub_1B335A0(&wk->pos, 0, v854);
          sBtlLockOnFree(wk);
          z = v849;
          w = v848;
          x = v847;
          sBtlSetMotion(wk, 9, 0, 0, 0);
          v467 = wk->actwk->framecnt;
        }
        if (v467 == 25)
        {
          wk->status &= ~1u;
          v856 = wk->UnitMng;
          v857 = wk->actaiwk->targetID;
          v858 = sBtlSearchUnit_ID(v856, v857);
          if (v858)
          {
            t1d = x;
            v1422 = wk->pos;
            v864 = wk->rot.x;
            v865 = wk->rot.y;
            v866 = wk->rot.z;
            v867 = wk->rot.w;
            v868 = v858->pos.x;
            v1312 = wk->pos.y;
            v1319 = wk->pos.x;
            v1298 = wk->pos.w;
            v1305 = wk->pos.z;
            v1422.w = v1298;
            v1422.z = v1305;
            v1422.y = v1312;
            v1422.x = v1319;
            v1451.x = v864;
            v1451.y = v865;
            v1451.z = v866;
            v1451.w = v867;
            *(u64 *)&v1372.x = 0;
            *(u64 *)&v1372.z = v859;
            v869 = sBtlGetRadian(v1422, v1451, v1372, v868);
            sBtlAddUnitDeg(wk, v869);
            *(__n128 *)&v871 = sub_1B335A0(&wk->rot, 0, v870);
            sub_1B335A0(&wk->rotbk, 0, v871);
            x = t1d;
            v468 = oldposb;
          }
        }
      }
      v872 = p_actwk->framecnt;
      if ((u32)(v872 - 40) >= 0xFFFFFFF1)
      {
        v875 = wk->color;
        v876 = (u8)v875;
        v877.n64_u64[0] = vdup_n_s32(v875).n64_u64[0];
        v878 = HIBYTE(v875);
        v879.n64_u64[0] = vand_s8(vshl_u32(v877, (uint32x2_t)0xFFFFFFF8FFFFFFF0LL), (int8x8_t)0xFF000000FFLL).n64_u64[0];
        if ((u32)v872 >= 0x1A)
        {
          v880 = x;
          v878 += 16;
          if ((u32)v872 >= 0x23)
          {
            v876 += 32;
            v879.n64_u64[0] = vadd_s32(v879, (int32x2_t)0x2000000020LL).n64_u64[0];
          }
        }
        else
        {
          v880 = x;
        }
        warp_bk_color = wk->warp_bk_color;
        v882.n64_u64[0] = vdup_n_s32(warp_bk_color).n64_u64[0];
        if (v876 >= (u8)warp_bk_color)
          v883 = (u8)wk->warp_bk_color;
        else
          v883 = v876;
        if (v878 >= HIBYTE(warp_bk_color))
          v884 = HIBYTE(warp_bk_color);
        else
          v884 = v878;
        v885.n64_u64[0] = vmin_u32(v879, vand_s8(vshl_u32(v882, (uint32x2_t)0xFFFFFFF8FFFFFFF0LL), (int8x8_t)0xFF000000FFLL)).n64_u64[0];
        v886 = vshl_u32(v885, (uint32x2_t)0x800000010LL).n64_u64[0];
        wk->chgcolor = v886 | (v884 << 24) | v883 | HIDWORD(v886);
        sBtlChangeModelColor(wk);
        x = v880;
        v872 = wk->actwk->framecnt;
        if (v872 == 40)
          goto LABEL_1854;
      }
      else if (v872 == 40)
      {
LABEL_1854:
        v873 = wk->warp_bk_color;
        wk->chgcolor = v873;
        sBtlChangeModelColor(wk);
        flg = wk->flg;
        wk->warp_bk_color = 0;
        wk->flg = flg & 0xFFFFFFFD;
        if (wk->actwk->framecnt >= 31)
        {
LABEL_1872:
          v888 = wk->UnitMng;
          v889 = wk->actaiwk->targetID;
          v890 = sBtlSearchUnit_ID(v888, v889);
          if (v890)
          {
            v891 = v890;
            SetAtkDirHD(wk, v891, 45.0, 3.0);
          }
        }
LABEL_1880:
        sBtlMVSupport(wk);
        UnitMV(wk);
        v1423.x = x;
        v1423.y = v468;
        v1423.z = z;
        v1423.w = w;
        CheckMapHit(wk, v1423);
        UnitMV_To_Basic(wk);
        if (wk->actwk->framecnt < wk->actwk->cmpframecnt)
          return v214;
        if (!sBtlCheckMotionEnd(wk) && p_actwk->framecnt < 181)
          return v214;
LABEL_1889:
LABEL_1890:
        sBtlSetAction(wk, 2, 0);
        wk->status &= ~0x20u;
        sBtlSetAIWkStat(wk, 1);
        return v214;
      }
      if (v872 < 31)
        goto LABEL_1880;
      goto LABEL_1872;
    case 0x37u:
      if ((u32)(v237->framecnt - 55) >= 0xFFFFFFCF && wk->actaiwk->targetID != -1)
      {
        if (!sBtlChkKaihiMawari(wk))
        {
          v470 = wk->UnitMng;
          v471 = wk->actaiwk->targetID;
          v472 = sBtlSearchUnit_ID(v470, v471);
          if (v472)
          {
            v473 = v472;
            if (v472 != wk)
            {
              SetAtkDirHD(wk, v473, 45.0, 10.0);
            }
          }
        }
      }
      sBtlMVSupport(wk);
      UnitMV(wk);
      v1395.x = x;
      v1395.y = oldposb;
      v1395.z = z;
      v1395.w = w;
      CheckMapHit(wk, v1395);
      UnitMV_To_Basic(wk);
      if (wk->actwk->framecnt < wk->actwk->cmpframecnt)
        return v214;
      if (!AttackwaitEndCheck(wk))
        return v214;
      sBtlSetSkill_MotionData(wk, wk->actwk->use_skillid);
      v466 = 90;
      v325 = wk;
      v326 = 3;
      goto LABEL_2240;
    case 0x38u:
      v474 = oldposb;
      if ((u32)(v237->framecnt - 21) < 0xFFFFFFEF)
        goto LABEL_2116;
      v475 = wk->actaiwk->targetID;
      if (v475 == -1)
        goto LABEL_2116;
      v475 = wk->actaiwk->targetID;
      v477 = wk->UnitMng;
      v478 = sBtlSearchUnit_ID(v477, v475);
      if (!v478)
        goto LABEL_2116;
      v479 = v478;
      if (v478 == wk)
        goto LABEL_2116;
      v480 = wk->mawari_pos_x;
      v481 = wk->mawari_pos_z;
      v482 = x;
      v483 = wk->pos.x - v480;
      v484 = wk->pos.z - v481;
      v485 = wk->actwk;
      HIDWORD(v1368) = 1065353216;
      mawari_lr = wk->mawari_lr;
      v488 = v485->framecnt <= 8;
      v489 = sqrtf((f32)(v483 * v483) + (f32)(v484 * v484));
      v490 = v483 / v489;
      v491 = v484 / v489;
      v492 = v478->pos.y;
      pos.x = v480;
      pos.y = v492;
      v493 = v478->pos.w;
      pos.z = v481;
      pos.w = v493;
      v1367 = LODWORD(v490);
      *(f32 *)&v1368 = v484 / v489;
      if (mawari_lr < 0)
      {
        v494 = -0.2617994;
        v495 = -0.17453292;
      }
      else
      {
        v494 = 0.2617994;
        v495 = 0.17453292;
      }
      if (v488)
        v973 = v494;
      else
        v973 = v495;
      if (!v487)
      sub_1949280(0, v973);
      *(__n128 *)&v974 = sub_1B332C0(0, v490, 0.0, v491, 1.0);
      v975 = (loc_1EA2510)(0, v974);
      sub_1B335A0(&v1365, 0, v975);
      x = v482;
      v976 = v479->actaiwk->hit_area_r + 50.0;
      v977 = 10.0 - (f32)(v489 - v976);
      if ((f32)(v489 - v976) >= 0.0)
        v977 = -0.0;
      v978 = (f32)(v489 - v976) + v977;
      if (v978 <= 30.0)
      {
        if (v978 <= 14.0)
          goto LABEL_2115;
        v979 = -5.0;
      }
      else
      {
        v979 = -10.0;
      }
      v978 = v978 + v979;
LABEL_2115:
      v980 = v976 + v978;
      v981 = pos.x + (f32)(v980 * *(f32 *)&v1365);
      v982 = pos.z + (f32)(v980 * *(f32 *)&v1366);
      wk->pos.x = v981;
      wk->pos.z = v982;
LABEL_2116:
      v983 = wk->actaiwk->targetID;
      if (v983 != -1)
      {
        v983 = wk->actaiwk->targetID;
        v985 = wk->UnitMng;
        v986 = sBtlSearchUnit_ID(v985, v983);
        if (v986 && v986 != wk)
        {
          t1j = x;
          v1429 = wk->pos;
          v992 = wk->rot.x;
          v993 = wk->rot.y;
          v994 = wk->rot.z;
          v995 = wk->rot.w;
          v996 = v986->pos.x;
          v1313 = wk->pos.y;
          v1325 = wk->pos.x;
          v1299 = wk->pos.w;
          v1306 = wk->pos.z;
          v1429.w = v1299;
          v1429.z = v1306;
          v1429.y = v1313;
          v1429.x = v1325;
          v1452.x = v992;
          v1452.y = v993;
          v1452.z = v994;
          v1452.w = v995;
          *(u64 *)&v1373.x = 0;
          *(u64 *)&v1373.z = v987;
          v997 = sBtlGetRadian(v1429, v1452, v1373, v996);
          sBtlAddUnitDeg(wk, v997);
          *(__n128 *)&v999 = sub_1B335A0(&wk->rot, 0, v998);
          sub_1B335A0(&wk->rotbk, 0, v999);
          v1000 = sBtlGetRotToDir(wk->rot);
          x = t1j;
          wk->mv_rotbk = sBtlGetDir180(v1000);
          v474 = oldposb;
        }
      }
      Proc(wk);
      sBtlProc(wk);
      sBtlMVSupport(wk);
      UnitMV(wk);
      v1430.x = x;
      v1430.y = v474;
      v1430.z = z;
      v1430.w = w;
      CheckMapHit(wk, v1430);
      UnitMV_To_Basic(wk);
      if (wk->actwk->framecnt < 42)
        return v214;
LABEL_2235:
      ResetAction(wk);
      goto LABEL_2238;
    case 0x39u:
      v496 = v237->framecnt;
      if (v496 == 1)
      {
        v497 = wk->flg;
        wk->damagecnt = 0;
        wk->flg = v497 | 2;
        if (wk->motionID == 5)
          goto LABEL_1209;
        sBtlSetMotion(wk, 5, 4, 0, 0);
        v496 = wk->actwk->framecnt;
      }
      if (v496 != 10)
      {
LABEL_1209:
        v505 = wk->pos.x;
        v506 = wk->pos.z;
      }
      else
      {
        v498 = x;
        v499 = w;
        v500 = z;
        sBtlSetFade(wk, 2, 0, 0, 21);
        v501 = wk->pos.x;
        v502 = wk->pos.y;
        v504 = wk->pos.z;
        v503 = wk->pos.w;
        v1396.x = v501;
        v1396.y = v502;
        v1396.z = v504;
        v1396.w = v503;
        sBtlPlay3DSE(0x1002Bu, v1396);
        v505 = wk->pos.x;
        z = v500;
        wk->asimoto_mode = 1;
        w = v499;
        v506 = wk->pos.z;
        x = v498;
        v507 = wk->status | 1;
        wk->asimoto_pos_x = v505;
        wk->asimoto_pos_z = v506;
        wk->asimoto_pos_x2 = v505;
        wk->asimoto_pos_z2 = v506;
        wk->asimoto_pos_x3 = v505;
        wk->asimoto_pos_z3 = v506;
        wk->asimoto_pos_x4 = v505;
        wk->asimoto_pos_z4 = v506;
        wk->status = v507;
      }
      v531 = wk->actaiwk;
      v532 = v531->ppos.x;
      v533 = v531->ppos.z;
      v534 = v532 - v505;
      v535 = v533 - v506;
      v536 = sqrtf((f32)(v534 * v534) + (f32)(v535 * v535));
      if (v536 > 1.0)
      {
        *(f32 *)&v1367 = v534 / v536;
        *(f32 *)&v1368 = v535 / v536;
      }
      v537 = p_actwk->framecnt;
      if (v537 >= 11)
      {
        if ((u32)v537 <= 0x10)
        {
          v625 = *(_OWORD *)p_asimoto_pos_x;
          v626 = v505 + (f32)(*(f32 *)&v1367 * 10.0);
          v627 = wk->pos.z + (f32)(*(f32 *)&v1368 * 10.0);
          v628 = *(u64 *)&wk->asimoto_pos_x3;
          wk->pos.x = v626;
          wk->pos.z = v627;
          v629 = v531->ppos.x;
          v630 = v531->ppos.z;
          *(u64 *)&wk->asimoto_pos_x4 = v628;
          *(_OWORD *)&wk->asimoto_pos_x2 = v625;
          wk->asimoto_pos_x = v626;
          wk->asimoto_pos_z = v627;
          wk->asimoto_pos_vx = (f32)(v629 - v626) / 7.0;
          wk->asimoto_pos_vz = (f32)(v630 - v627) / 7.0;
        }
        else if (v537 == 18)
        {
          v538 = x;
          v539 = v531->ppos.y;
          v540 = v531->ppos.w;
          *(__n128 *)&v541 = sub_1B332C0(0, v532, v539, v533, v540);
          sub_1B335A0(&wk->pos, 0, v541);
          x = v538;
          v537 = p_actwk->framecnt;
        }
      }
      if ((u32)(v537 - 27) < 0xFFFFFFF6)
      {
        if (v537 != 27)
          goto LABEL_1447;
        goto LABEL_1412;
      }
      *(_OWORD *)&wk->asimoto_pos_x3 = *(_OWORD *)&wk->asimoto_pos_x2;
      v631.n64_u64[0] = *(u64 *)&wk->asimoto_pos_x;
      *(float32x2_t *)&wk->asimoto_pos_x2 = v631;
      if ((u32)v537 <= 0x17)
      {
        *(float32x2_t *)&wk->asimoto_pos_x = vadd_f32(v631, *(float32x2_t *)&wk->asimoto_pos_vx);
      }
      else
      {
        wk->asimoto_pos_x = wk->pos.x;
        wk->asimoto_pos_z = wk->pos.z;
        if (v537 == 24)
        {
          sBtlSetFade(wk, 1, 0, 0, 32);
          wk->status &= ~1u;
          if (wk->actwk->framecnt == 27)
LABEL_1412:
            wk->asimoto_mode = 0;
        }
      }
LABEL_1447:
      v648 = wk->UnitMng;
      v649 = wk->actaiwk->targetID;
      v650 = sBtlSearchUnit_ID(v648, v649);
      if (v650)
      {
        v651 = v650;
        SetAtkDirHD(wk, v651, 45.0, 3.0);
      }
      sBtlMVSupport(wk);
      UnitMV(wk);
      v1416.x = x;
      v1416.y = oldposb;
      v1416.z = z;
      v1416.w = w;
      CheckMapHit(wk, v1416);
      UnitMV_To_Basic(wk);
      if (wk->actwk->framecnt < wk->actwk->cmpframecnt)
        return v214;
      wk->flg &= ~2u;
      goto LABEL_1890;
    case 0x3Au:
      if (v237->framecnt == 1)
      {
        v508 = wk->flg;
        wk->damagecnt = 0;
        v509 = x;
        v510 = wk->pos.x;
        v511 = wk->pos.y;
        v512 = w;
        v513 = z;
        wk->flg = v508 | 2;
        v514 = oldposb;
        v516 = wk->pos.z;
        v515 = wk->pos.w;
        v1397.x = v510;
        v1397.y = v511;
        v1397.z = v516;
        v1397.w = v515;
        sBtlPlay3DSE(0x1002Bu, v1397);
        v517 = wk->pos.x;
        z = v513;
        wk->asimoto_mode = 1;
        w = v512;
        v518 = wk->pos.z;
        x = v509;
        v519 = wk->status | 1;
        wk->asimoto_pos_x = v517;
        wk->asimoto_pos_z = v518;
        wk->asimoto_pos_x2 = v517;
        wk->asimoto_pos_z2 = v518;
        wk->asimoto_pos_x3 = v517;
        wk->asimoto_pos_z3 = v518;
        wk->asimoto_pos_x4 = v517;
        wk->asimoto_pos_z4 = v518;
        wk->status = v519;
      }
      else
      {
        v517 = wk->pos.x;
        v518 = wk->pos.z;
        v514 = oldposb;
      }
      v575 = wk->actaiwk;
      v576 = v575->ppos.x;
      v577 = v575->ppos.z;
      v578 = v576 - v517;
      v579 = v577 - v518;
      v580 = sqrtf((f32)(v578 * v578) + (f32)(v579 * v579));
      if (v580 > 1.0)
      {
        *(f32 *)&v1367 = v578 / v580;
        *(f32 *)&v1368 = v579 / v580;
      }
      v581 = p_actwk->framecnt;
      if (v581 >= 2)
      {
        if ((u32)v581 <= 4)
        {
          if (v580 <= 10.0)
          {
            *(u64 *)&wk->asimoto_pos_vx = 0;
          }
          else
          {
            v632 = *(_OWORD *)p_asimoto_pos_x;
            v633 = v517 + (f32)(*(f32 *)&v1367 * 10.0);
            v634 = wk->pos.z + (f32)(*(f32 *)&v1368 * 10.0);
            v635 = *(u64 *)&wk->asimoto_pos_x3;
            wk->pos.x = v633;
            wk->pos.z = v634;
            v636 = v575->ppos.x;
            v637 = v575->ppos.z;
            *(u64 *)&wk->asimoto_pos_x4 = v635;
            wk->asimoto_pos_x = v633;
            *(_OWORD *)&wk->asimoto_pos_x2 = v632;
            wk->asimoto_pos_z = v634;
            wk->asimoto_pos_vx = (f32)(v636 - v633) / 7.0;
            wk->asimoto_pos_vz = (f32)(v637 - v634) / 7.0;
          }
        }
        else if (v581 == 6)
        {
          v584 = x;
          v585 = v575->ppos.y;
          v586 = v575->ppos.w;
          *(__n128 *)&v587 = sub_1B332C0(0, v576, v585, v577, v586);
          sub_1B335A0(&wk->pos, 0, v587);
          x = v584;
          v581 = p_actwk->framecnt;
        }
      }
      if ((u32)(v581 - 13) >= 0xFFFFFFF8)
      {
        *(_OWORD *)&wk->asimoto_pos_x3 = *(_OWORD *)&wk->asimoto_pos_x2;
        v582.n64_u64[0] = *(u64 *)&wk->asimoto_pos_x;
        *(float32x2_t *)&wk->asimoto_pos_x2 = v582;
        if ((u32)v581 <= 9)
        {
          *(float32x2_t *)&wk->asimoto_pos_x = vadd_f32(v582, *(float32x2_t *)&wk->asimoto_pos_vx);
        }
        else
        {
          wk->asimoto_pos_x = wk->pos.x;
          wk->asimoto_pos_z = wk->pos.z;
          if (v581 == 10)
          {
            wk->vstatus &= 0xFFDFEFFC;
            wk->fadepara = 16;
            wk->color = -2139062144;
            v583 = wk->para;
            if (sBtlGetBadStatus(v583) == 11)
              wk->color = -2136655252;
            wk->status &= ~1u;
            v581 = wk->actwk->framecnt;
          }
          if (v581 == 11)
            wk->asimoto_mode = 0;
        }
      }
      sBtlMVSupport(wk);
      UnitMV(wk);
      v1414.x = x;
      v1414.y = v514;
      v1414.z = z;
      v1414.w = w;
      CheckMapHit(wk, v1414);
      UnitMV_To_Basic(wk);
      if (wk->actwk->framecnt >= wk->actwk->cmpframecnt)
        goto LABEL_1889;
      return v214;
    case 0x3Bu:
      wk->status |= 0x100u;
      sBtlMVSupport(wk);
      UnitMV(wk);
      v1398.x = x;
      v1398.y = oldposb;
      v1398.z = z;
      v1398.w = w;
      CheckMapHit(wk, v1398);
      UnitMV_To_Basic(wk);
      if (wk->actwk->framecnt < 41)
        return v214;
      ResetAction(wk, 0, 0);
      sBtlResetAAI(wk);
      if ((wk->side & 1) == 0)
      {
        wk->damage_hitcnt = 0;
        goto LABEL_1126;
      }
      wk->aiwk->mode = 0;
      wk->actcounter = wk->actcounter_max;
      wk->damage_hitcnt = 0;
LABEL_1126:
      sBtlSetAction(wk, 2, 0);
      v302 = wk->status & 0xFFFFFEFF;
LABEL_1127:
      wk->status = v302;
      v522 = wk->para;
      v523 = v522->badstatus;
      if ((v523 & 1) != 0)
        v522->badstatus = v523 & 0xFFFFFFFE;
      return v214;
    case 0x3Cu:
      if (v237->framecnt >= 40)
      {
        if (sBtlCheckUnit_Exec())
        {
          v524.n64_u32[0] = 1073741832;
          p_status = &wk->status;
          LODWORD(v528) = vorr_s8((int8x8_t)p_status->n64_u64[0], v524).n64_u32[0];
          HIDWORD(v528) = HIDWORD(p_status->n64_u64[0]) & 0xEFFFFFFF;
          p_status->n64_u64[0] = v528;
          sBtlInitDropWork();
          sBtlSetEndData();
        }
      }
      return v214;
    case 0x3Eu:
      v1399.y = oldposb;
      v1399.x = x;
      v1399.z = z;
      v1399.w = w;
      sBtlBS_ITIMOK_Action_Kaiten(wk, v1399);
      return v214;
    case 0x3Fu:
      v1400.y = oldposb;
      v1400.x = x;
      v1400.z = z;
      v1400.w = w;
      sBtlBS_AKAMA2_Action_Taxi(wk, v1400);
      return v214;
    case 0x40u:
      v1401.y = oldposb;
      v1401.x = x;
      v1401.z = z;
      v1401.w = w;
      sBtlBS_RASUPU_Action_Nenr(wk, v1401);
      return v214;
    case 0x41u:
      v1402.y = oldposb;
      v1402.x = x;
      v1402.z = z;
      v1402.w = w;
      sBtlBS_MATORY_Action_Nenr(wk, v1402);
      return v214;
    case 0x42u:
      v1403.y = oldposb;
      v1403.x = x;
      v1403.z = z;
      v1403.w = w;
      sBtlBS_MISHAK_Action_Hiru(wk, v1403);
      return v214;
    case 0x43u:
      v1404.y = oldposb;
      v1404.x = x;
      v1404.z = z;
      v1404.w = w;
      sBtlBS_MUNAKA_Action_Imad(wk, v1404);
      return v214;
    case 0x44u:
      sBtlSetSuperArmor(wk, 1550, -2);
      v1405.x = x;
      v1405.y = oldposb;
      v1405.z = z;
      v1405.w = w;
      sBtlBS_LASTB1_Action_Setu(wk, v1405);
      return v214;
    case 0x45u:
      sBtlSetSuperArmor(wk, 1550, -2);
      v1406.x = x;
      v1406.y = oldposb;
      v1406.z = z;
      v1406.w = w;
      sBtlBS_LASTB1_Action_Setr(wk, v1406);
      return v214;
    case 0x46u:
      v1407.y = oldposb;
      v1407.x = x;
      v1407.z = z;
      v1407.w = w;
      sBtlBS_LASTB1_Action_Dang(wk, v1407);
      return v214;
    case 0x47u:
      v239 = oldposb;
      if (!v237->action_flg)
      {
        v529 = v237->use_skillid;
        if (v529)
          wk->aiwk->usedSkl = v529;
        v237->action_flg = 1;
        CheckSkillMessage(wk, v529);
      }
      goto LABEL_2159;
    case 0x48u:
      v1408.y = oldposb;
      v1408.x = x;
      v1408.z = z;
      v1408.w = w;
      sBtlBS_LASTB1_Action_Dsmn(wk, v1408);
      return v214;
    case 0x49u:
      v1409.y = oldposb;
      v1409.x = x;
      v1409.z = z;
      v1409.w = w;
      sBtlBS_LASTB1_Action_Gurd(wk, v1409);
      return v214;
    case 0x4Au:
      v1410.y = oldposb;
      v1410.x = x;
      v1410.z = z;
      v1410.w = w;
      sBtlBS_LASTB1_Action_Bstp(wk, v1410);
      return v214;
    case 0x4Bu:
      sBtlSetSuperArmor(wk, 1558, -2);
      v1411.x = x;
      v1411.y = oldposb;
      v1411.z = z;
      v1411.w = w;
      sBtlBS_LASTB1_Action_Quik(wk, v1411);
      return v214;
    case 0x4Cu:
      v1412.y = oldposb;
      v1412.x = x;
      v1412.z = z;
      v1412.w = w;
      sBtlBS_YOMI_Action_Gun(wk, v1412);
      return v214;
    default:
      return v214;
  }
}

// 0x1eb1c80
static void SetAtkDirHD(SBTLUNIT_WORK *wk, SBTLUNIT_WORK *pTgt, f32 kakudo, f32 raito) {
  f32 x;
  f32 z;
  f32 v11;
  f32 v12;
  f32 PosToDir;
  sdfVector4_t *p_rot;
  f32 RotToDir;
  f32 AtoB_LR;
  f32 v17;
  f32 v18;
  f32 Dir180;
  f32 per;
  f32 v25;
  f32 y;
  f32 w;
  f32 Radian;
  f32 v29;
  sdfVector4_t *p_rotbk;
  f32 v34;
  f32 v35;
  f32 v36;
  f32 v37;
  f32 rot;
  sdfVector4_t v39;
  sdfVector4_t v40;
  sdfVector4_t v41;

  if (wk && wk->para->devilid == 291)
  {
    x = wk->pos.x;
    z = wk->pos.z;
    v11 = pTgt->pos.x;
    v12 = pTgt->pos.z;
    PosToDir = sBtlGetPosToDir(x, z, v11, v12);
    p_rot = &wk->rot;
    RotToDir = sBtlGetRotToDir(wk->rot);
    AtoB_LR = sBtlGetAtoB_LR(RotToDir, PosToDir);
    if (AtoB_LR < (f32)-kakudo)
      AtoB_LR = -kakudo;
    if (AtoB_LR > kakudo)
      AtoB_LR = kakudo;
    v17 = RotToDir + (f32)(AtoB_LR / raito);
    v18 = sBtlGet360(v17);
    Dir180 = sBtlGetDir180(v18);
    FromEuler(0.0, Dir180 * 0.017453292, 0.0);
LABEL_29:
    *p_rot = vct_A;
    p_rotbk = &wk->rotbk;
    *p_rotbk = vct_A;
    return;
  }
  p_rot = &wk->rot;
  v41 = wk->rot;
  per = pTgt->pos.x;
  v25 = wk->pos.x;
  y = wk->pos.y;
  v40.z = wk->pos.z;
  w = wk->pos.w;
  v37 = wk->rot.y;
  rot = wk->rot.x;
  v35 = wk->rot.w;
  v36 = wk->rot.z;
  v34 = wk->pos.z;
  v40.z = v34;
  v41.w = v35;
  v41.x = rot;
  v41.z = v36;
  v41.y = v37;
  v40.x = v25;
  v40.y = y;
  v40.w = w;
  *(u64 *)&v39.x = 0;
  *(u64 *)&v39.z = pTgt;
  Radian = sBtlGetRadian(v40, v41, v39, per);
  if (Radian < (f32)-kakudo)
    Radian = -kakudo;
  if (Radian > kakudo)
    Radian = kakudo;
  v29 = Radian / raito;
  if ((f32)(Radian / raito) <= -0.01 || v29 >= 0.01)
  {
    sBtlAddUnitDeg(wk, v29);
    goto LABEL_29;
  }
}

// 0x1eb1fa0
static void WeakAfterScrflag(SBTLUNIT_WORK *wk) {
  sdatUnitWork_t *para;
  SBTLAI_WORK *aiwk;
  u32 scrflag;
  s32 devilid;
  s32 *scrStepN;
  s32 v7;

  if (wk)
  {
    para = wk->para;
    if (para)
    {
      aiwk = wk->aiwk;
      scrflag = aiwk->scrflag;
      if ((scrflag & 0x10000) == 0)
        goto LABEL_15;
      devilid = (u16)para->devilid;
      if (devilid != 310 && devilid != 267)
        goto LABEL_15;
      scrStepN = aiwk->scrStepN;
      v7 = scrStepN[7];
      if (v7 > 309)
      {
        if (v7 != 310 && v7 != 510 && v7 != 410)
          goto LABEL_15;
      }
      else if (v7 != 10 && v7 != 110 && v7 != 210)
      {
        goto LABEL_15;
      }
      scrStepN[7] = v7 - 10;
      scrflag = aiwk->scrflag;
LABEL_15:
      aiwk->scrflag = scrflag & 0xFBFEFFFF;
    }
  }
}

// 0x1eb2030
static void SklCameraEnd(SBTLUNIT_WORK *wk) {
  SBATTLE_WORK *v4;
  SBTLUNIT_WORK *p_pCamSklUser2;
  SBATTLE_WORK *v8;
  SBATTLE_WORK *v9;
  SBTLUNIT_WORK *pCamSklUser2;
  s32 camSkl;
  s64 i;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;

  v4 = wk;
  v4->bCamSklNoWait = 0;
  if ((wk->side & 2) == 0)
    return;
  if (v4->pCamSklUser != wk)
    return;
  if (sBtlGetMode() != 2)
  {
    if (!wk->boss_eventID)
    {
      sBtlSetMode(2);
      v9 = wk;
      pCamSklUser2 = v9->pCamSklUser2;
      v9->camSlpMode = 2;
      if (pCamSklUser2)
      {
        v9 = wk;
        camSkl = v9->camSkl;
        if ((camSkl | 0x80) == 0x3EA || (u32)(camSkl - 1277) <= 2)
        {
          for (i = 0; ; ++i)
          {
            UnitMng = wk->UnitMng;
            if (i >= UnitMng->number)
              break;
            UnitMng = wk->UnitMng;
            pUnit = UnitMng->pUnitL[i]->pUnit;
            if (pUnit)
            {
              if (pUnit != wk->pCamSklUser2 && !pUnit->bOldDispOff)
                pUnit->vstatus &= ~0x1000u;
            }
          }
        }
      }
    }
    p_pCamSklUser2 = &wk->pCamSklUser2;
    p_pCamSklUser2 = 0;
    v8 = wk;
    v8->status2 &= ~0x20u;
    if (!v8->mapclr)
    {
      v8 = wk;
      *(u64 *)&v8->mapfadeclr = 0x120202020LL;
    }
  }
}

// 0x1eb2300
static void FrcSklEnd(SBTLUNIT_WORK *wk) {
  SBATTLE_WORK *v4;
  SBATTLE_WORK *v5;

  v4 = wk;
  if (v4->pCamSklUser != wk)
    return;
  v4 = wk;
  v4->pCamSklUser = 0;
  v5 = wk;
  if (v5->bEnemyFrcWait)
  {
    v5->bEnemyFrcWait = 0;
    sBtlEndWaitALL(0, 0);
    return;
  }
}

// 0x1eb2450
static void ChkSklCamEnd(SBTLUNIT_WORK *wk) {
  if (!wk->bCamSklNoWait)
    return;
  if (!sBtlIsMoveEnd())
    return;
  if (wk->pCamSklUser != wk)
    return;
  SklCameraEnd(wk);
}

// 0x1eb25b0
bool sBtlCheckNextAction(SBTLUNIT_WORK *wk) {
  SBTLACTAI_WORK *actaiwk;
  s32 mahaskl_waitframe;
  bool v5;
  s32 v6;
  bool result;
  SBATTLE_WORK *v10;
  s32 camSklCnt;
  s32 v12;
  s32 next_motionID;
  SBTLSM_LISTWORK *sysmsgList;
  s64 i;
  SBTLUNIT_WORK *pUnit;
  bool v23;
  u16 major;
  s32 minor;
  s32 motionno;
  s32 use_skillid;
  SBTLEFF_LISTWORK *effList;
  u32 v30;
  SBTLSM_LISTWORK *v34;

  actaiwk = wk->actaiwk;
  mahaskl_waitframe = actaiwk->mahaskl_waitframe;
  v5 = __OFSUB__(mahaskl_waitframe, 1);
  v6 = mahaskl_waitframe - 1;
  if (v6 < 0 == v5)
  {
    result = 0;
    actaiwk->mahaskl_waitframe = v6;
    return result;
  }
  ChkSklCamEnd(wk);
  v10 = wk;
  if (v10->pCamSklUser == wk)
  {
    camSklCnt = v10->camSklCnt;
    if (camSklCnt)
    {
      if (wk->actwk->action_flg)
      {
        v10 = wk;
        camSklCnt = v10->camSklCnt;
        v12 = camSklCnt - 1;
        v10->camSklCnt = v12;
        if (!v12)
        {
          SklCameraEnd(wk);
          FrcSklEnd(wk);
        }
      }
      return 0;
    }
  }
  next_motionID = wk->next_motionID;
  if (sBtlCheckLoopMotion(wk, next_motionID))
  {
    SklCameraEnd(wk);
    FrcSklEnd(wk);
    if (wk->bYobi2Nml)
    {
      wk->bYobi2Nml = 0;
      sysmsgList = wk->sysmsgList;
      sysmsgList->bLock = 0;
      sBtlReleaseSM_List(sysmsgList, 1u);
      if (g_aTimeStopSkl[wk->timeStopID]->sklID == 890)
      {
        for (i = 0; ; ++i)
        {
          pUnit = wk->UnitMng->pUnitL[i]->pUnit;
          v23 = !pUnit || pUnit == wk;
          if (!v23 && (pUnit->side & 2) != 0)
            break;
        }
        pUnit->bStop = 0;
      }
    }
    return 1;
  }
  major = wk->major;
  minor = wk->minor;
  motionno = wk->motionno;
  if (sBtlGetMotionVisualData(major, minor, motionno)->end_motionno != 1)
    goto LABEL_82;
  use_skillid = wk->actwk->use_skillid;
  if (!use_skillid && (wk->side & 2) != 0)
    goto LABEL_82;
  use_skillid = wk->actwk->use_skillid;
  effList = wk->effList;
  if (!sBtlSearchEffect_SAB_Acter(effList, wk, use_skillid, 1) || (result = 0, v30 = wk->actwk->use_skillid - 1328, v30 <= 0xF) && ((1 << v30) & 0x8021) != 0)
  {
LABEL_82:
    if (sBtlCheckMotionEnd(wk))
    {
      SklCameraEnd(wk);
      FrcSklEnd(wk);
      if (wk->bYobi2Nml)
      {
        wk->bYobi2Nml = 0;
        v34 = wk->sysmsgList;
        v34->bLock = 0;
        sBtlReleaseSM_List(v34, 1u);
        if (g_aTimeStopSkl[wk->timeStopID]->sklID == 890)
        {
          sBtlGetAnotherEnemy(wk)->bStop = 0;
        }
      }
      return 1;
    }
    return 0;
  }
  return result;
}

// 0x1eb2ad0
bool sBtlSetMotionHit(SBTLUNIT_WORK *wk, s32 motionno, SKLID skillid) {
  s32 devilid;
  SBTLSKLHIT_PACLIST *hitwk;
  s32 v9;
  s64 v10;
  s64 v11;
  s64 v12;
  s64 v13;
  SBTLSKILLP_TBL *Skilltbl;
  SBTLSKLHIT_PACDATAWORK *v16;
  SBTLSKILLHIT_TBL *v17;
  s32 ListID;
  s32 acterside;
  SBTLDMG_HITLISTWORK *hitList;
  s32 use_skillid;

  devilid = (u16)wk->para->devilid;
  if ((devilid == 475 || devilid == 184) && skillid == 149)
    return 0;
  hitwk = wk->hitwk;
  if (hitwk->num >= 1)
  {
    v9 = 0;
    v10 = 4;
    do
    {
      v12 = *((u64 *)&hitwk->pwk->obj.klass + v10);
      if (v12)
      {
        v13 = *(u64 *)(v12 + 40);
        if (v13)
        {
          if (*(u32 *)(v13 + 120) == motionno)
          {
            Skilltbl = sBtlGetSkilltbl(skillid);
            v16 = *((SBTLSKLHIT_PACDATAWORK *)&wk->hitwk->pwk->obj.klass + v10);
            v17 = v16->wk;
            v16 = *((SBTLSKLHIT_PACDATAWORK *)&wk->hitwk->pwk->obj.klass + v10);
            ListID = wk->ListID;
            acterside = wk->side;
            hitList = wk->hitList;
            use_skillid = wk->actwk->use_skillid;
            sBtlCreateHitC_New(hitList, wk, 0, ListID, use_skillid, Skilltbl, v17, v16, acterside, -1);
            hitwk = wk->hitwk;
            v9 = 1;
          }
        }
      }
      v11 = v10 - 3;
      ++v10;
    }
    while (v11 < hitwk->num);
    if (v9 == 1)
    {
      sBtlAddSerialID2();
    }
  }
  return 1;
}

// 0x1eb1750
static void CheckSkillMessage(SBTLUNIT_WORK *wk, SKLID sklid) {
  SBTLSKILLP_TBL *Skilltbl;
  SBATTLE_WORK *v7;
  s32 mode;
  _BOOL4 v9;
  bool v10;
  bool v11;
  s32 v12;
  s32 v13;
  bool v15;
  SBTLSM_LISTWORK *sysmsgList;
  s32 v17;

  Skilltbl = sBtlGetSkilltbl(sklid);
  v7 = wk;
  if ((v7->scrFlag & 0x100000) != 0)
    return;
  if ((~wk->side & 0x81) == 0)
  {
    mode = v7->mode;
    v9 = mode == 22;
    v10 = mode == 23;
    v11 = mode == 24;
    v12 = mode;
    v13 = mode;
    v15 = v13 == 27 || mode == 26 || v12 == 25;
    if (v15 || v11 || v10 || v9)
    {
      v7 = wk;
      sysmsgList = v7->sysmsgList;
      v17 = 10;
      goto LABEL_39;
    }
  }
  if ((Skilltbl->flg & 0x40000000) != 0 || (Skilltbl->flg2 & 0x10000) != 0 && (wk->status & 0x100000) != 0)
  {
    sysmsgList = wk->sysmsgList;
    v17 = 11;
LABEL_39:
    sBtlCreateSM(sysmsgList, wk, v17, 0, 0, 120);
  }
}

// 0x1eb2cc0
bool sBtlSetUseSkill(SBTLUNIT_WORK *wk, SKLID skillid, s32 after_frame) {
  SBATTLE_WORK *v7;
  _BOOL4 bNoUseSkl;
  SB_ENCOUNTPAC *EncountPac;
  SBATTLE_WORK *v12;
  SB_ENCOUNTPAC *v13;
  SBTLSKILLP_TBL *Skilltbl;
  s32 v17;
  s64 timeStopID;
  s32 sklID;
  u32 v20;
  s64 i;
  SBTLUNIT_WORK *pUnit;
  bool v24;
  SBATTLE_WORK *v27;
  SBATTLE_WORK *v30;
  s32 para2;
  SBATTLE_WORK *v33;
  long f64 v36;
  f32 v37;
  f32 v38;
  f32 v39;
  f32 v40;
  SBTLEFF_LISTWORK *effList;
  s32 NumOfEffect_SAB;
  s32 v43;
  SBTLEFF_LISTWORK *v45;
  s32 v46;
  s32 v47;
  SBTLEFF_LISTWORK *v49;
  s32 v50;
  s32 v51;
  SBTLEFF_LISTWORK *v53;
  s32 v54;
  S_CameraMoveDt *g_CamMovNirami_local;
  s32 tameMot;
  s32 tameEff;
  s32 side;
  SBTLSM_LISTWORK *sysmsgList;
  s32 v67;
  SBTLUNIT_WORK *AnotherEnemy;
  s64 v69;
  SBTLUNIT_WORK *v70;
  s32 v71;
  s32 v72;
  s32 v73;
  s64 k;
  SBTLUNIT_LISTWORK *v75;
  SBTLUNIT_WORK *v76;
  s64 m;
  SBTLUNIT_LISTWORK *v78;
  SBTLUNIT_WORK *v79;
  s32 v85;
  long f64 v88;
  f32 x;
  f32 y;
  f32 w;
  f32 z;
  SBTLUNIT_WORK *p_pCamSklUser2;
  s64 j;
  u32 v97;
  SBATTLE_WORK *v98;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v100;
  s32 vstatus;
  S_CameraMoveDt *g_CamMovMaou1_local;
  long f64 v109;
  f32 v110;
  f32 v111;
  f32 v112;
  f32 v113;
  SBTLUNIT_WORK *v115;
  SBTLUNIT_LISTWORK *v117;
  s32 targetID;
  SBTLUNIT_WORK *v119;
  s32 v120;
  s32 v123;
  s32 v124;
  s32 v127;
  u32 status;
  SBTLSM_LISTWORK *v131;
  s32 use_skillid;
  s32 v135;
  SBTLUNIT_WORK *v136;
  s32 v137;
  SBTLACTION_WORK *v138;
  SBTLACTION_WORK *v140;
  SBTLSM_LISTWORK *v142;
  s32 v143;
  s32 v144;
  SBTLSM_LISTWORK *v145;
  SBTLUNIT_WORK *v146;
  s32 flg;
  SBTLACTION_WORK *v148;
  SBATTLE_WORK *v150;
  s64 v151;
  SBTLACTION_WORK *v152;
  SBTLACTION_WORK *actwk;
  SBTLSM_LISTWORK *v155;
  SBTLACTION_WORK *v156;
  SBTLACTION_WORK *v160;
  s32 effect_flg;
  s64 n;
  SBTLUNIT_LISTWORK *v164;
  SBTLUNIT_WORK *v165;
  SBTLACTION_WORK *v166;
  SBTLACTION_WORK *v167;
  SBTLACTION_WORK *v168;
  SBTLACTION_WORK *v170;
  SBTLACTION_WORK *v171;
  SBTLACTION_WORK *v173;
  SBTLACTION_WORK *v174;
  SBATTLE_WORK *v176;
  s64 v177;
  SBTLACTION_WORK *v179;
  SBTLACTION_WORK *v180;
  SBTLACTION_WORK *v182;
  SBTLEFF_LISTWORK *v185;
  sdfVector4_t v190;
  sdfVector4_t v191;
  sdfVector4_t v192;
  sdfVector4_t v193;

  v7 = wk;
  bNoUseSkl = v7->bNoUseSkl;
  if (v7->bNoUseSkl)
    return !bNoUseSkl;
  wk->actwk->quake_flg = 0;
  if (skillid)
    wk->flg &= ~0x20u;
  EncountPac = sBtlGetEncountPac(-1);
  v12 = wk;
  v13 = EncountPac[v12->encountno];
  if ((v13->flag & 4) == 0 && (wk->side & 2) != 0)
  {
    if ((u32)(skillid - 1472) < 5 || skillid == 149)
    {
      Skilltbl = sBtlGetSkilltbl(skillid);
      if ((u32)(skillid - 1225) <= 2)
        goto LABEL_17;
LABEL_23:
      if ((Skilltbl->flg2 & 0x80) == 0)
        goto LABEL_252;
      goto LABEL_24;
    }
    v12 = wk;
    effList = v12->effList;
    NumOfEffect_SAB = sBtlGetNumOfEffect_SAB(effList, 0, 2);
    if (NumOfEffect_SAB > 15)
      return !bNoUseSkl;
    v43 = NumOfEffect_SAB;
    v45 = wk->effList;
    v46 = sBtlGetNumOfEffect_SAB(v45, 1u, 2);
    if (v46 > 15)
      return !bNoUseSkl;
    v47 = v46;
    v49 = wk->effList;
    v50 = sBtlGetNumOfEffect_SAB(v49, 2u, 2);
    if (v50 > 15)
      return !bNoUseSkl;
    v51 = v50;
    v53 = wk->effList;
    v54 = sBtlGetNumOfEffect_SAB(v53, 5u, 2);
    if (v54 > 15 || v47 + v43 + v51 + v54 >= 18)
      return !bNoUseSkl;
  }
  Skilltbl = sBtlGetSkilltbl(skillid);
  if (!skillid)
    goto LABEL_252;
  if ((u32)(skillid - 1225) > 2)
    goto LABEL_23;
LABEL_17:
  v190.x = 0.0;
  v190.w = 0.0;
  v190.y = -200.0;
  v190.z = -200.0;
  sBtlSetPosSlp(v190);
  sBtlBgnPosSlp();
  if ((Skilltbl->flg2 & 0x80) == 0)
    goto LABEL_252;
LABEL_24:
  if ((wk->side & 2) == 0)
    goto LABEL_252;
  v17 = 0;
  goto LABEL_36;
  while (1)
  {
LABEL_36:
    sklID = g_aTimeStopSkl[v17]->sklID;
    if (!sklID)
      goto LABEL_40;
    timeStopID = v17;
    sklID = g_aTimeStopSkl[v17]->sklID;
    if (sklID == skillid)
      break;
    ++v17;
  }
  if (v17 != -1 && !wk->bYobi2Nml)
  {
    if (!wk->bYobidousa)
    {
      wk->timeStopID = v17;
      wk->yobidousaCnt = 0;
      wk->bYobidousa = 1;
      timeStopID = wk->timeStopID;
      tameMot = g_aTimeStopSkl[timeStopID]->tameMot;
      sBtlSetMotion(wk, tameMot, 4, 0, 0);
      tameEff = g_aTimeStopSkl[wk->timeStopID]->tameEff;
      if (tameEff)
      {
        tameEff = g_aTimeStopSkl[wk->timeStopID]->tameEff;
        side = wk->side;
        sBtlCheckEffectData(wk, tameEff, 1u, 0, side, -1, 0);
      }
      sysmsgList = wk->sysmsgList;
      sBtlReleaseSM_List(sysmsgList, 1u);
      sBtlCreateSM(wk->sysmsgList, wk, 77, skillid, 0, 120);
      v67 = wk->flg | 0xD0;
      wk->status |= 0x100u;
      wk->flg = v67;
      wk->sysmsgList->bLock = 1;
      if (g_aTimeStopSkl[wk->timeStopID]->sklID == 890)
      {
        AnotherEnemy = sBtlGetAnotherEnemy(wk);
        v69 = wk->timeStopID;
        v70 = AnotherEnemy;
        AnotherEnemy->bStop = 1;
        v71 = g_aTimeStopSkl[v69]->tameMot;
        sBtlSetMotion(v70, v71, 4, 0, 0);
        v72 = g_aTimeStopSkl[wk->timeStopID]->tameEff;
        if (v72)
        {
          v72 = g_aTimeStopSkl[wk->timeStopID]->tameEff;
          v73 = wk->side;
          sBtlCheckEffectData(v70, v72, 1u, 0, v73, -1, 0);
        }
        v70->status |= 0x100u;
        v70->flg |= 0xD0u;
      }
      return !bNoUseSkl;
    }
    goto LABEL_252;
  }
LABEL_40:
  if (skillid == 890)
  {
    wk->rot = (struct sdfVector4_t)xmmword_3CFD5C0;
    if (!v20)
    for (i = 0; ; ++i)
    {
      pUnit = wk->UnitMng->pUnitL[i]->pUnit;
      v24 = !pUnit || pUnit == wk;
      if (!v24 && (pUnit->side & 2) != 0)
        break;
    }
    pUnit->rot = (struct sdfVector4_t)xmmword_3CFD5C0;
LABEL_56:
    v27 = wk;
    goto LABEL_57;
  }
  else
  {
    goto LABEL_56;
  }
  v27 = wk;
LABEL_57:
  v27->camSklCnt = sBtlGetSklTimeStop(skillid);
  if ((wk->side & 2) == 0)
    goto LABEL_252;
  v30 = wk;
  v30->bEnemyFrcWait = 1;
  v30->pCamSklUser = wk;
  para2 = Skilltbl->para2;
  v33 = wk;
  v33->camSkl = skillid;
  if (para2 <= 1)
  {
    LOWORD(para2) = Skilltbl->para2;
    g_CamMovNirami_local = g_apCamMovSkl[(s16)para2];
    goto LABEL_108;
  }
  if (para2 != 2)
    goto LABEL_252;
  if (skillid <= 1143)
  {
    if (skillid <= 1093)
    {
      if (skillid == 874 || skillid == 1002)
      {
        sBtlBgnWaitALL_TimeStopSkill(wk, 0);
        sBtlSetMove(g_CamMovHoukou, 1);
        sBtlSetMode(13);
        *(__n128 *)&v88 = sub_1B332C0(0, 0.0, 0.0, 0.0, 1.0);
        sub_1B335A0(&wk->rot, 0, v88);
        x = wk->rot.x;
        y = wk->rot.y;
        z = wk->rot.z;
        w = wk->rot.w;
        v192.x = x;
        v192.y = y;
        v192.z = z;
        v192.w = w;
        dds3SetRotPoseSet(&wk->pBasic, v192);
        p_pCamSklUser2 = &wk->pCamSklUser2;
        p_pCamSklUser2 = wk;
        for (j = 0; ; ++j)
        {
          v98 = wk;
          UnitMng = v98->UnitMng;
          if (j >= UnitMng->number)
            break;
          if (!v97)
          {
            UnitMng = wk->UnitMng;
          }
          v100 = UnitMng->pUnitL[j]->pUnit;
          if (v100)
          {
            if (v100 != wk->pCamSklUser2 && (v100->side & 3) != 0)
            {
              vstatus = v100->vstatus;
              v100->bOldDispOff = (vstatus & 0x1000) != 0;
              v100->vstatus = vstatus | 0x1000;
            }
          }
        }
        if (!v97)
        {
          v98 = wk;
        }
        v98->status2 |= 0x20u;
        v98->bCamSklNoWait = 1;
        goto LABEL_252;
      }
      if (skillid != 1093)
        goto LABEL_252;
    }
    else if (skillid != 1112)
    {
      if (skillid == 1143)
      {
        sBtlBgnWaitALL_TimeStopSkill(wk, 0);
        g_CamMovMaou1_local = g_CamMovMaou1;
      }
      else
      {
        if (skillid != 1142)
          goto LABEL_252;
        for (k = 0; ; ++k)
        {
          v75 = wk->UnitMng;
          if (k >= v75->number)
            break;
          v75 = wk->UnitMng;
          v76 = v75->pUnitL[k]->pUnit;
          if (v76 && (v76->side & 1) != 0)
          {
            sBtlBgnWait(v76);
          }
        }
        g_CamMovMaou1_local = g_CamMovMaou;
      }
      goto LABEL_243;
    }
    g_CamMovNirami_local = g_CamMovNirami;
LABEL_108:
    sBtlSetMove(g_CamMovNirami_local, 1);
    sBtlSetMode(13);
    sBtlBgnWaitALL_TimeStopSkill(wk, 0);
    goto LABEL_252;
  }
  if ((u32)skillid <= 0x4A2)
  {
    switch (skillid)
    {
      case 1186:
LABEL_180:
        sBtlBgnWaitALL_TimeStopSkill(wk, 0);
        *(u64 *)&wk->mapfadeclr = -2139062144;
        sBtlSetMove(g_CamMovExo, 1);
        sBtlSetMode(13);
        sBtlBgnWaitALL_TimeStopSkill(wk, 0);
        v85 = 9;
        goto LABEL_189;
      case 1149:
        sBtlBgnWaitALL_TimeStopSkill(wk, 0);
        g_CamMovMaou1_local = g_CamMovTensi1;
        break;
      case 1148:
        for (m = 0; ; ++m)
        {
          v78 = wk->UnitMng;
          if (m >= v78->number)
            break;
          v78 = wk->UnitMng;
          v79 = v78->pUnitL[m]->pUnit;
          if (v79 && (v79->side & 1) != 0)
          {
            sBtlBgnWait(v79);
          }
        }
        g_CamMovMaou1_local = g_CamMovTensi;
        break;
      default:
        goto LABEL_252;
    }
LABEL_243:
    sBtlSetMove(g_CamMovMaou1_local, 1);
    sBtlSetMode(13);
    *(__n128 *)&v109 = sub_1B332C0(0, 0.0, 0.0, 0.0, 1.0);
    sub_1B335A0(&wk->rot, 0, v109);
    v110 = wk->rot.x;
    v111 = wk->rot.y;
    v113 = wk->rot.z;
    v112 = wk->rot.w;
    v193.x = v110;
    v193.y = v111;
    v193.z = v113;
    v193.w = v112;
    dds3SetRotPoseSet(&wk->pBasic, v193);
    v115 = &wk->pCamSklUser2;
    v115 = wk;
    wk->status2 |= 0x20u;
    goto LABEL_252;
  }
  if ((u32)skillid <= 0x4C1)
  {
    if (skillid != 1206 && skillid != 1217)
      goto LABEL_252;
    goto LABEL_180;
  }
  if (skillid == 1234)
  {
    sBtlBgnWaitALL_TimeStopSkill(wk, 0);
    sBtlSetMove(g_CamMovTenbatu, 1);
    sBtlSetMode(13);
    *(__n128 *)&v36 = sub_1B332C0(0, 0.0, 0.0, 0.0, 1.0);
    sub_1B335A0(&wk->rot, 0, v36);
    v37 = wk->rot.x;
    v38 = wk->rot.y;
    v40 = wk->rot.z;
    v39 = wk->rot.w;
    v191.x = v37;
    v191.y = v38;
    v191.z = v40;
    v191.w = v39;
    dds3SetRotPoseSet(&wk->pBasic, v191);
    goto LABEL_252;
  }
  if ((u32)(skillid - 1277) <= 2)
  {
    v33 = wk;
    if (!v33->boss_eventID)
    {
      sBtlSetMove(g_CamMovMagS0, 1);
      v85 = 13;
LABEL_189:
      sBtlSetMode(v85);
    }
  }
LABEL_252:
  if ((v13->flag & 4) == 0 || !sBtlCheckSkillCancel(wk, skillid))
  {
    wk->actwk->use_skillid = skillid;
    SetUseskl(wk, skillid);
    v117 = wk->UnitMng;
    targetID = wk->actaiwk->targetID;
    v119 = sBtlSearchUnit_ID(v117, targetID);
    if ((wk->side & 2) != 0 && (wk->status & 0x100000) == 0 && ((v120 = Skilltbl->type & 0xFFF, v120 == 15) || v120 == 3))
    {
      sBtlSetMotion(wk, 29, 8, 0, 0);
    }
    else if (sBtlGetSklVisualTbl(wk->actwk->use_skillid)->motionno != 255)
    {
      sBtlSetSkill_MotionData(wk, wk->actwk->use_skillid);
    }
    sBtlSetHatData(wk, wk->actwk->use_skillid);
    if ((Skilltbl->flg & 0x10) != 0)
    {
      SetAction_ProgramSkill(wk, skillid);
      goto LABEL_379;
    }
    if (skillid > 996)
    {
      if ((u32)skillid > 0x442)
      {
        if ((u32)skillid <= 0x4CC)
        {
          if (skillid != 1109)
          {
LABEL_325:
            switch (Skilltbl->type & 0xFFF)
            {
              case 0:
                v136 = wk;
                v137 = 1;
                goto LABEL_377;
              case 1:
              case 0xC:
              case 0xD:
                if ((wk->side & 2) == 0 || (wk->status & 0x100000) != 0)
                  goto LABEL_343;
                if (!RaidoAttackCheck() || !v119)
                  goto LABEL_343;
                if (wk->playerID == wk->actaiwk->targetID)
                {
                  sBtlSetAction(wk, 55, 60);
                  sBtlSetMotion(wk, 0, 0, 0, 0);
                }
                else
                {
LABEL_343:
                  if ((wk->side & 0x80) == 0)
                  {
                    v136 = wk;
                    v137 = 3;
LABEL_377:
                    v135 = 0;
LABEL_378:
                    sBtlSetAction(v136, v137, v135);
                  }
                }
                goto LABEL_379;
              case 2:
              case 5:
              case 0xE:
                v135 = 90;
                v136 = wk;
                v137 = 31;
                goto LABEL_378;
              case 3:
                if ((wk->side & 2) == 0 || (wk->status & 0x100000) != 0)
                {
                  v135 = 90;
                  v136 = wk;
                  v137 = 6;
                }
                else
                {
                  v137 = 53;
                  v136 = wk;
                  v135 = 60;
                }
                goto LABEL_378;
              case 8:
                v137 = 37;
                goto LABEL_376;
              case 9:
                sBtlSetAction(wk, 40, 0);
                if (skillid <= 410)
                {
                  if (skillid > 239)
                  {
                    if (skillid == 240)
                    {
                      actwk = wk->actwk;
                      actwk->cmpframecnt2 = 0;
                      actwk->cmpframecnt3 = 0;
                      actwk->effect_flg = 4;
                      v155 = wk->sysmsgList;
                      v143 = 186;
                      v145 = v155;
                      v146 = wk;
                      v144 = 0;
                    }
                    else
                    {
                      if (skillid != 410)
                        goto LABEL_419;
                      v140 = wk->actwk;
                      v140->effect_flg = 4;
                      *(u64 *)&v140->cmpframecnt2 = 120;
                      wk->hstatus |= 8u;
                      v142 = wk->sysmsgList;
                      v143 = 11;
                      v144 = 410;
                      v145 = v142;
                      v146 = wk;
                    }
                    sBtlCreateSM(v145, v146, v143, v144, 0, 120);
                    goto LABEL_420;
                  }
                  if (skillid == 230)
                  {
                    v148 = wk->actwk;
                    v148->effect_flg = 10;
                    v148 = wk->actwk;
                    v151 = 0x3C0000012CLL;
LABEL_414:
                    v150 = wk;
                    goto LABEL_415;
                  }
                  if (skillid == 239)
                  {
                    v152 = wk->actwk;
                    v152->effect_flg = 6;
                    *(u64 *)&v152->cmpframecnt2 = 0xA00000082LL;
                    goto LABEL_420;
                  }
                }
                else
                {
                  if ((u32)skillid > 0x1A0)
                  {
                    switch (skillid)
                    {
                      case 469:
                        v167 = wk->actwk;
                        v167->effect_flg = 4;
                        *(u64 *)&v167->cmpframecnt2 = 0x3E800000000LL;
                        goto LABEL_420;
                      case 470:
                        v168 = wk->actwk;
                        v168->effect_flg = 8;
                        v168 = wk->actwk;
                        wk->status |= 0x40000000u;
                        *(u64 *)&v168->cmpframecnt2 = 0x3C000001AELL;
                        goto LABEL_420;
                      case 471:
                      case 472:
                      case 473:
                      case 474:
                      case 477:
                      case 478:
                      case 485:
                      case 488:
                      case 489:
                      case 490:
                      case 491:
                      case 496:
                      case 498:
                      case 499:
                      case 500:
                      case 502:
                      case 503:
                        goto LABEL_419;
                      case 475:
                        v170 = wk->actwk;
                        v170->effect_flg = 4;
                        *(u64 *)&v170->cmpframecnt2 = 150;
                        goto LABEL_420;
                      case 476:
                        v171 = wk->actwk;
                        v171->effect_flg = 4;
                        v171 = wk->actwk;
                        wk->status |= 0x40000000u;
                        *(u64 *)&v171->cmpframecnt2 = 0x3C0000012CLL;
                        goto LABEL_420;
                      case 479:
                      case 480:
                        sBtlResetGunMode_Eve();
                        v166 = wk->actwk;
                        v166->effect_flg = 4;
                        *(u64 *)&v166->cmpframecnt2 = 400;
                        goto LABEL_420;
                      case 481:
                      case 482:
                      case 483:
                        v138 = wk->actwk;
                        v138->effect_flg = 4;
                        *(u64 *)&v138->cmpframecnt2 = 0x10E00000000LL;
                        goto LABEL_420;
                      case 484:
                        v173 = wk->actwk;
                        v173->effect_flg = 4;
                        *(u64 *)&v173->cmpframecnt2 = 0x1A400000000LL;
                        goto LABEL_420;
                      case 486:
                        v174 = wk->actwk;
                        v174->effect_flg = 4;
                        v174 = wk->actwk;
                        v176 = wk;
                        v176->status |= 0x40000000u;
                        v177 = 0x3C000001A4LL;
                        goto LABEL_466;
                      case 487:
                        v148 = wk->actwk;
                        v148->effect_flg = 0;
                        v148 = wk->actwk;
                        v151 = 0x3C00000000LL;
                        goto LABEL_414;
                      case 492:
                        v179 = wk->actwk;
                        v179->effect_flg = 4;
                        *(u64 *)&v179->cmpframecnt2 = (char *)&qword_68 + 1;
                        goto LABEL_420;
                      case 493:
                        v180 = wk->actwk;
                        v180->effect_flg = 8;
                        v180 = wk->actwk;
                        wk->status |= 0x40000000u;
                        *(u64 *)&v180->cmpframecnt2 = 0x3C0000014ALL;
                        goto LABEL_420;
                      case 494:
                        v182 = wk->actwk;
                        v182->effect_flg = 0;
                        v182->cmpframecnt2 = 0;
                        v182->cmpframecnt3 = 0;
                        goto LABEL_420;
                      case 495:
                        v148 = wk->actwk;
                        v148->effect_flg = 10;
                        v148 = wk->actwk;
                        v151 = 0x3C00000276LL;
                        goto LABEL_414;
                      case 497:
                        v174 = wk->actwk;
                        v174->effect_flg = 8;
                        v174 = wk->actwk;
                        v176 = wk;
                        v176->status |= 0x40000000u;
                        v177 = 0x3C00000122LL;
LABEL_466:
                        *(u64 *)&v174->cmpframecnt2 = v177;
                        v185 = v176->effList;
                        sBtlForceResetDecAlpha(v185, wk, 4);
                        goto LABEL_420;
                      case 501:
                        v148 = wk->actwk;
                        v148->effect_flg = 10;
                        v148 = wk->actwk;
                        v151 = 0x3C0000010ELL;
                        goto LABEL_414;
                      case 504:
                        v148 = wk->actwk;
                        v148->effect_flg = 6;
                        v148 = wk->actwk;
                        v151 = 0x3C000000DCLL;
                        goto LABEL_414;
                      case 505:
                        v148 = wk->actwk;
                        v148->effect_flg = 6;
                        v148 = wk->actwk;
                        v150 = wk;
                        v151 = 0x3C000000F0LL;
                        wk->hstatus |= 8u;
                        goto LABEL_415;
                      default:
                        if (skillid == 867)
                        {
                          v148 = wk->actwk;
                          v148->effect_flg = 6;
                          v148 = wk->actwk;
                          v151 = 0x1E00000078LL;
                          goto LABEL_414;
                        }
                        if (skillid != 891)
                          goto LABEL_419;
                        v160 = wk->actwk;
                        v160->effect_flg = 4;
                        *(u64 *)&v160->cmpframecnt2 = 120;
                        wk->hstatus |= 8u;
                        break;
                    }
                    goto LABEL_420;
                  }
                  if (skillid == 414)
                  {
                    SetAction(10);
                    v156 = wk->actwk;
                    v156->effect_flg = 4;
                    v156 = wk->actwk;
                    wk->status |= 0x40000000u;
                    *(u64 *)&v156->cmpframecnt2 = 0x3C000001C2LL;
                    goto LABEL_420;
                  }
                  if (skillid == 416)
                  {
                    v148 = wk->actwk;
                    v148->effect_flg = 10;
                    v148 = wk->actwk;
                    v150 = wk;
                    v151 = 0x2D00000023LL;
                    wk->hstatus |= 8u;
LABEL_415:
                    v150->status |= 0x40000000u;
                    *(u64 *)&v148->cmpframecnt2 = v151;
                    v150->BtlEnd_BossFedeOut = 1;
LABEL_420:
                    effect_flg = wk->actwk->effect_flg;
                    if ((effect_flg & 4) != 0)
                    {
                      sBtlFadeOut_BadStatusEffect(wk, 4);
                      effect_flg = wk->actwk->effect_flg;
                    }
                    if ((effect_flg & 8) != 0)
                    {
                      for (n = 0; ; ++n)
                      {
                        v164 = wk->UnitMng;
                        if (n >= v164->number)
                          break;
                        v164 = wk->UnitMng;
                        v165 = v164->pUnitL[n]->pUnit;
                        if (v165 && (v165->side & 2) != 0)
                        {
                          sBtlFadeOut_BadStatusEffect(v165, 4);
                        }
                      }
                    }
LABEL_379:
                    wk->actwk->action_count = 0;
                    return !bNoUseSkl;
                  }
                }
LABEL_419:
                wk->actwk->effect_flg = 0;
                goto LABEL_420;
              case 0xA:
                v137 = 41;
                goto LABEL_376;
              case 0xB:
                v137 = 43;
                goto LABEL_376;
              case 0xF:
                v137 = 71;
                goto LABEL_376;
              case 0x10:
                v137 = 45;
LABEL_376:
                v136 = wk;
                goto LABEL_377;
              default:
                goto LABEL_379;
            }
          }
          wk->waitwalkMot = 0;
          v123 = 0;
LABEL_295:
          sBtlSetBossMode(v123);
          goto LABEL_325;
        }
        if ((u32)(skillid - 1257) < 4)
        {
          v123 = 4;
          goto LABEL_295;
        }
        if (skillid != 1264)
        {
          if (skillid != 1265)
            goto LABEL_325;
          status = wk->status;
          wk->waitwalkMot = 0;
          wk->status = status & 0xFEFFFFFE;
          wk->not_hitmode = 0;
LABEL_300:
          sBtlSetBossMode(0);
LABEL_302:
          wk->NotCmbSkl_Ex = 1;
          goto LABEL_325;
        }
        flg = wk->flg;
        wk->not_tatezan = 1;
        wk->flg = flg | 2;
        wk->waitwalkMot = 20;
        wk->status |= 1u;
        wk->not_hitmode = 1;
        goto LABEL_305;
      }
      if (skillid != 997)
      {
        if (skillid == 1089)
        {
          wk->flg |= 2u;
          wk->waitwalkMot = 18;
          goto LABEL_302;
        }
        if (skillid != 1090)
          goto LABEL_325;
      }
LABEL_298:
      wk->waitwalkMot = 0;
      wk->status &= ~0x1000000u;
      goto LABEL_300;
    }
    if (skillid <= 506)
    {
      switch (skillid)
      {
        case 221:
          goto LABEL_313;
        case 222:
        case 223:
        case 224:
        case 225:
        case 226:
        case 227:
        case 228:
        case 229:
        case 230:
          goto LABEL_325;
        case 231:
          v124 = 16;
          goto LABEL_323;
        case 232:
          v124 = 15;
          goto LABEL_323;
        case 233:
          v124 = 13;
LABEL_323:
          SetAction(v124);
          break;
        case 234:
          ClrAction();
          break;
        default:
          if (skillid == 506)
          {
LABEL_313:
            sBtlStatusBitOn(wk, 0x4000u);
            v131 = wk->sysmsgList;
            use_skillid = wk->actwk->use_skillid;
            sBtlCreateSM(v131, wk, 43, use_skillid, 0, 120);
          }
          break;
      }
      goto LABEL_325;
    }
    if ((u32)skillid <= 0x365)
    {
      if (skillid != 868)
      {
        if (skillid != 869)
          goto LABEL_325;
        goto LABEL_298;
      }
    }
    else
    {
      if (skillid == 884)
      {
        wk->flg |= 2u;
        goto LABEL_325;
      }
      if (skillid != 996)
        goto LABEL_325;
    }
    v127 = wk->flg;
    wk->not_tatezan = 1;
    wk->flg = v127 | 2;
    wk->status |= 1u;
    wk->waitwalkMot = 16;
    wk->not_hitmode = 1;
LABEL_305:
    wk->NotCmbSkl_Ex = 1;
    goto LABEL_325;
  }
  return !bNoUseSkl;
}

// 0x1eb4dd0
bool sBtlSetHangekiFlag(SBTLUNIT_WORK *wk) {
  SBATTLE_WORK *v5;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 playerID;
  SBTLUNIT_WORK *v8;
  sdatUnitWork_t *para;
  s32 hangeki_on;
  s32 level;
  s32 v12;
  s32 v13;
  u16 Percentage;
  u32 v15;

  if ((wk->side & 2) == 0 || (wk->exsts & 1) == 0)
    return 1;
  v5 = wk;
  UnitMng = v5->UnitMng;
  playerID = v5->playerID;
  v8 = sBtlSearchUnit_ID(UnitMng, playerID);
  para = wk->para;
  hangeki_on = wk->hangeki_on;
  level = para->level;
  v12 = v8->para->level;
  if (hangeki_on)
  {
    if ((wk->status & 0x100000) == 0)
      goto LABEL_12;
LABEL_23:
    if (wk->hangeki_renzokudmg < 8)
      return 1;
    if (!wk->hangeki_nokezoranai && GetPercentage() <= 0x4Fu && (wk->hstatus & 0x10) == 0)
    {
      wk->hangeki_nokezoranai = 120;
    }
    if (wk->hangeki_renzokudmg < 16 || wk->hangeki_on || GetPercentage() > 0x1Du)
      return 1;
    goto LABEL_31;
  }
  ++wk->hangeki_renzokudmg;
  if ((wk->status & 0x100000) != 0)
    goto LABEL_23;
LABEL_12:
  if ((f32)((f32)para->now->hp / (f32)para->now->maxhp) <= 0.25 || hangeki_on || wk->hangeki_renzokudmg < 9)
  {
    return 1;
  }
  v13 = level - v12;
  Percentage = GetPercentage();
  v15 = v13 <= -5 ? 5 : 30;
  if (v13 >= 5)
    v15 = 60;
  if (v15 <= Percentage)
    return 1;
LABEL_31:
  if ((wk->hstatus & 0x10) != 0)
    return 1;
  wk->hangeki_st_done = 0;
  wk->hangeki_nokezoranai = 120;
  wk->hangeki_endcnt = 180;
  wk->hangeki_on = 2;
  wk->damage_1stmotcnt = 0;
  wk->damage_1stmotnum = 0;
  return 1;
}

// 0x1ea50b0
bool sBtlSetAction(SBTLUNIT_WORK *wk, SBTLACTION_ST status, s32 cmpframe) {
  SBTLACTION_WORK *actwk;
  u32 v8;
  bool result;
  SBTLSKILLP_TBL *Skilltbl;
  u32 v12;
  sdatUnitWork_t *para;
  SBTLACTION_WORK *v14;

  actwk = wk->actwk;
  v8 = actwk->status;
  if (v8 == 46 && (wk->side & 0x81) == 1)
    return 0;
  Skilltbl = sBtlGetSkilltbl(actwk->use_skillid);
  if ((status == 53 || status == 6) && (wk->side & 2) != 0)
  {
    if (wk->para->devilid != 521 && wk->actwk->use_skillid != 1472 && (Skilltbl->flg & 0x20000) != 0)
    {
      wk->flg |= 2u;
    }
  }
  else if (v8 == 53 || v8 == 6)
  {
    if ((wk->side & 2) == 0)
      goto LABEL_33;
    if ((Skilltbl->flg & 0x20000) != 0)
      wk->flg &= ~2u;
  }
  else if ((wk->side & 2) == 0)
  {
    goto LABEL_33;
  }
  if ((u32)status < 3)
  {
LABEL_26:
    if ((u32)status <= 0x1F && ((1 << status) & 0x80000048) != 0 && wk->hangeki_on)
    {
      if (wk->hangeki_endcnt <= 119)
        wk->hangeki_endcnt = 120;
      if (wk->hangeki_nokezoranai <= 119)
        wk->hangeki_nokezoranai = 120;
    }
LABEL_33:
    v12 = status - 7;
    if ((u32)status > 0x3B || ((1 << status) & 0xEE0000000000780LL) == 0)
      goto LABEL_38;
    goto LABEL_35;
  }
  if (status != 7)
  {
    wk->hangeki_renzokudmg = 0;
    goto LABEL_26;
  }
  sBtlSetHangekiFlag(wk);
  v12 = 0;
LABEL_35:
  sBtlACTAIFLG_Clr(wk);
LABEL_38:
  if (v12 < 3 || status == 33 || status == 23)
  {
    sBtlEndAction(wk);
    wk->status &= ~0x100u;
  }
  para = wk->para;
  if (sBtlGetBadStatus(wk->para) != 12)
    goto LABEL_48;
  result = 0;
  if ((u32)status <= 0x28 && ((1 << status) & 0x10600000400LL) != 0)
  {
LABEL_48:
    v14 = wk->actwk;
    v14->status = status;
    v14->framecnt = 0;
    *(u64 *)&v14->framecntB = 0;
    v14->cmpframecnt = cmpframe;
    wk->Action_HUTTOBI_Cnt = 0;
    if ((wk->side & 2) != 0)
    {
      if (status == 1)
        goto LABEL_54;
      v14->total_homing = 0.0;
      if (status == 6 && v8 == 53)
        goto LABEL_54;
    }
    else
    {
      v14->total_homing = 0.0;
    }
    v14->no_homing = 0;
LABEL_54:
    v14->action_flg = 0;
    v14->effectTime = 0xFFFFFFF;
    wk->h_attack_move_len = 0.0;
    wk->motion_WeakDmg2 = 0;
    return 1;
  }
  return result;
}

// 0x1eb4fc0
bool sBtlCheckStatus_Move(SBTLUNIT_WORK *wk) {
  return wk->actwk->status < 3;
}

// 0x1eb4fe0
static void StartSklProc(s32 unitID, s32 timeStopID) {
  _SKLPROC *sklProc;

  sklProc = wk->sklProc;
  sklProc->unitID = unitID;
  sklProc->timeStopID = timeStopID;
  sklProc->bRun = 1;
  sklProc->cnt = 0;
  sklProc->stp = 0;
}

// 0x1eb5060
static void RunBlur(void) {
  ;
}

// 0x1eb5070
void sBtlRunSklProc(void) {
  _SKLPROC *sklProc;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 unitID;
  s32 sklID;
  SBTLUNIT_WORK *v10;
  SBTLSKLVISUAL_TBL *SklVisualTbl;
  _SKLPROC *v12;
  S_TIMESTOPSKL *v15;
  SBATTLE_WORK *v16;
  _SKLPROC *v17;
  SBTLDMG_HITLISTWORK *v19;
  _SKLPROC *v20;
  s32 v21;
  s64 j;
  SBTLUNIT_LISTWORK *v24;
  SBTLUNIT_WORK *v25;
  bool v26;
  SBTLDMG_HITLISTWORK *hitList;
  _SKLPROC *v29;
  s32 v30;
  s64 i;
  SBTLUNIT_LISTWORK *v33;
  SBTLUNIT_WORK *pUnit;
  bool v35;
  S_TIMESTOPSKL *v40;
  SBTLUNIT_WORK *AnotherEnemy;
  SBTLDMG_HITLISTWORK *v43;
  _SKLPROC *v44;
  s32 v45;
  s64 m;
  SBTLUNIT_LISTWORK *v48;
  SBTLUNIT_WORK *v49;
  bool v50;
  SBTLDMG_HITLISTWORK *v52;
  _SKLPROC *v53;
  s32 v54;
  s64 n;
  SBTLUNIT_LISTWORK *v57;
  SBTLUNIT_WORK *v58;
  bool v59;
  SBTLUNIT_WORK *v60;
  SBTLUNIT_WORK *v61;
  SBATTLE_WORK *v63;
  u32 status4;
  s32 v67;
  SBTLSM_LISTWORK *v68;
  SBATTLE_WORK *v72;
  _SKLPROC *v74;
  s32 v75;
  long f64 v76;
  SBATTLE_WORK *p_fields;
  S_CameraMoveDt *CamMovePtn;
  SBTLSM_LISTWORK *v80;
  SBATTLE_WORK *v82;
  SBTLUNIT_LISTWORK *v83;
  s32 v84;
  SBTLUNIT_WORK *v85;
  sdatUnitWork_t *v86;
  u32 v87;
  _SKLPROC *v89;
  s32 stp;
  s32 v91;
  f32 v92;
  s32 v96;
  _SKLPROC *v97;
  s32 v98;
  s32 cnt;
  f32 ActionTime;
  s32 v101;
  S_TIMESTOPSKL *v103;
  _SKLPROC *v107;
  s32 v109;
  s32 v110;
  S_TIMESTOPSKL *v114;
  S_TIMESTOPSKL *v119;
  SBTLUNIT_WORK *v120;
  s32 v122;
  s32 v123;
  s32 v126;
  SBATTLE_WORK *v130;
  SBTLUNIT_LISTWORK *v131;
  s32 playerID;
  SBTLUNIT_WORK *v133;
  sdatUnitWork_t *para;
  u32 BadStatus;
  _SKLPROC *v139;
  s32 v140;
  SBATTLE_WORK *v142;
  _SKLPROC *v144;
  u32 v145;
  s32 v146;
  long f64 v147;
  SBATTLE_WORK *v148;
  S_CameraMoveDt *v150;
  SBTLSM_LISTWORK *v151;
  SBATTLE_WORK *v153;
  _SKLPROC *v155;
  u32 v156;
  s32 v157;
  long f64 v158;
  SBATTLE_WORK *v159;
  SBTLUNIT_WORK *p_pCamSklUser;
  SBTLSM_LISTWORK *v161;
  s32 v163;
  s32 v165;
  u32 v166;
  s32 v168;
  u32 v169;
  s32 side;
  _SKLPROC *v174;
  s32 v175;
  s32 v177;
  SBTLSM_LISTWORK *sysmsgList;
  SBTLDMG_HITLISTWORK *v181;
  _SKLPROC *v182;
  s32 v183;
  s64 ii;
  SBTLUNIT_LISTWORK *v186;
  SBTLUNIT_WORK *v187;
  bool v188;
  SBATTLE_WORK *v190;
  _SKLPROC *v192;
  u32 v193;
  s32 v194;
  long f64 v195;
  SBATTLE_WORK *v196;
  S_CameraMoveDt *v198;
  SBTLSM_LISTWORK *v199;
  s32 v200;
  s32 v202;
  s32 v203;
  SBTLSM_LISTWORK *v204;
  SBATTLE_WORK *v206;
  SBTLUNIT_LISTWORK *v207;
  s32 v208;
  SBTLUNIT_WORK *v209;
  sdatUnitWork_t *v210;
  u32 v211;
  SBATTLE_WORK *v213;
  _SKLPROC *v214;
  s32 v215;
  SBATTLE_WORK *v217;
  _SKLPROC *v218;
  S_BLUR *sBlur;
  _SKLPROC *v222;
  s32 v223;
  s32 motionno;
  u32 v232;
  SBTLDMG_HITLISTWORK *v234;
  _SKLPROC *v235;
  s32 v236;
  s64 k;
  SBTLUNIT_LISTWORK *v239;
  SBTLUNIT_WORK *v240;
  bool v241;
  s32 v243;
  u32 v244;
  SBTLUNIT_WORK *v246;
  s32 v247;
  s32 v248;
  s32 v252;
  s32 v258;

  sklProc = wk->sklProc;
  UnitMng = wk->UnitMng;
  unitID = sklProc->unitID;
  sklID = g_aTimeStopSkl[sklProc->timeStopID]->sklID;
  v10 = sBtlSearchUnit_ID(UnitMng, unitID);
  SklVisualTbl = sBtlGetSklVisualTbl(sklID);
  v12 = wk->sklProc;
  if (v12->bRun)
  {
    if (v12->stp)
      goto LABEL_24;
    if (IsSceanStop())
    {
      goto LABEL_17;
    }
    StopBattle();
LABEL_17:
    if (!sBtlCheckSummon_LoadExecOk(1))
      return;
LABEL_24:
    if (!sBtlHDloadChk(sklID))
      return;
    v15 = g_aTimeStopSkl;
    v16 = wk;
    v17 = v16->sklProc;
    switch (v15[v17->timeStopID]->ptn)
    {
      case 0:
        v16 = wk;
        v17 = v16->sklProc;
        switch (v17->stp)
        {
          case 0:
            goto LABEL_166;
          case 1:
            v17 = wk->sklProc;
            if (v17->cnt >= 16)
            {
              RestartBattle();
              sBtlStatusBitOff(v10, 0xFFFFFFEF);
              sBtlForceDeleteAll_TimeStopSkill(v10, 0);
              hitList = wk->hitList;
              sBtlReleaseHitC_List(hitList, 1u);
              sBtlAnimListClr();
              sBtlNakamaWarpReset();
              v29 = wk->sklProc;
              v30 = v29->stp + 1;
              v29->cnt = 0;
              v29->stp = v30;
              sBtlSetCmbBfrPos();
              for (i = 0; ; ++i)
              {
                v33 = wk->UnitMng;
                if (i >= v33->number)
                  break;
                v33 = wk->UnitMng;
                pUnit = v33->pUnitL[i]->pUnit;
                if (pUnit)
                  v35 = pUnit == v10;
                else
                  v35 = 1;
                if (!v35)
                  pUnit->vstatus |= 0x1000u;
              }
              motionno = SklVisualTbl->motionno;
              v10->pos = (struct sdfVector4_t)xmmword_3CFD5C0;
              v10->rot = (struct sdfVector4_t)xmmword_3CFD5C0;
              v10->rotbk = (struct sdfVector4_t)xmmword_3CFD5C0;
              sBtlSetMotion(v10, motionno, 0, 0, 0);
              dds3SetQuake(300, 0x64u);
            }
            goto LABEL_529;
          case 2:
            goto LABEL_189;
          case 3:
            v17 = wk->sklProc;
            if (v17->cnt >= 16)
              goto LABEL_457;
            goto LABEL_529;
          case 4:
            if (!sBtlCheckMotionEnd(v10))
              goto LABEL_529;
            side = v10->side;
            v174 = wk->sklProc;
            v175 = v174->stp + 1;
            v174->cnt = 0;
            v174->stp = v175;
            sBtlCheckEffectData(v10, sklID, 1u, 0, side, -1, 0);
            sBtlSetMode(13);
            sBtlSetMove(g_CamMovAll, 1);
            sBtlSetPosCmbBfrPos();
            v10->bYobidousa = 0;
            goto LABEL_550;
          case 5:
            v17 = wk->sklProc;
            if (v17->cnt == 30)
              goto LABEL_401;
            goto LABEL_515;
          case 6:
            v16 = wk;
            v17 = v16->sklProc;
            if (v17->cnt < 16)
              goto LABEL_529;
            v16 = wk;
            v17 = v16->sklProc;
            v177 = v17->stp + 1;
            v17->cnt = 0;
            v17->stp = v177;
            sysmsgList = v16->sysmsgList;
            sBtlReleaseSM_List(sysmsgList, 1u);
            wk->sysmsgList->bLock = 0;
            goto LABEL_480;
          case 7:
            goto LABEL_204;
          default:
            goto LABEL_529;
        }
      case 1:
      case 2:
        v16 = wk;
        v17 = v16->sklProc;
        switch (v17->stp)
        {
          case 0:
            goto LABEL_166;
          case 1:
            v17 = wk->sklProc;
            if (v17->cnt < 16)
              goto LABEL_529;
            RestartBattle();
            sBtlStatusBitOff(v10, 0xFFFFFFEF);
            sBtlForceDeleteAll_TimeStopSkill(v10, 0);
            v19 = wk->hitList;
            sBtlReleaseHitC_List(v19, 1u);
            sBtlAnimListClr();
            sBtlNakamaWarpReset();
            v20 = wk->sklProc;
            v21 = v20->stp + 1;
            v20->cnt = 0;
            v20->stp = v21;
            sBtlSetCmbBfrPos();
            for (j = 0; ; ++j)
            {
              v24 = wk->UnitMng;
              if (j >= v24->number)
                break;
              v24 = wk->UnitMng;
              v25 = v24->pUnitL[j]->pUnit;
              if (v25)
                v26 = v25 == v10;
              else
                v26 = 1;
              if (!v26)
                v25->vstatus |= 0x1000u;
            }
            v168 = SklVisualTbl->motionno;
            v10->pos = (struct sdfVector4_t)xmmword_3CFD5C0;
            v10->rot = (struct sdfVector4_t)xmmword_3CFD5C0;
            v10->rotbk = (struct sdfVector4_t)xmmword_3CFD5C0;
            if (!v169)
            sBtlSetMotion(v10, v168, 0, 0, 0);
            dds3SetQuake(300, 0x64u);
            v10->bYobidousa = 0;
            goto LABEL_548;
          case 2:
            goto LABEL_189;
          case 3:
            v17 = wk->sklProc;
            cnt = v17->cnt;
            ActionTime = sBtlGetActionTime(v10, 0);
            if (ActionTime != INFINITY && cnt < (s32)ActionTime)
              goto LABEL_529;
            v101 = v10->side;
            sBtlCheckEffectData(v10, sklID, 1u, 0, v101, -1, 0);
            goto LABEL_523;
          case 4:
            v17 = wk->sklProc;
            if (v17->cnt == 40)
            {
              v103 = g_aTimeStopSkl;
              if (v103[wk->sklProc->timeStopID]->ptn == 2)
              {
                SetPara(Blur2, 0.0, 0.965, SEMI, 0);
                _SetRGBA(Blur2, 0x40808080u);
                SetArea(Blur2, 0, 0, 0);
                _On(Blur2, 0);
              }
            }
            v107 = wk->sklProc;
            v109 = v107->cnt;
            v107 = wk->sklProc;
            if (v109 < g_aTimeStopSkl[v107->timeStopID]->wait2)
              goto LABEL_529;
            v107 = wk->sklProc;
            v110 = v107->stp + 1;
            v107->cnt = 0;
            v107->stp = v110;
            sBtlSetMode(13);
            sBtlSetMove(g_CamMovAll, 1);
            goto LABEL_353;
          case 5:
            if (v17->cnt == 30)
            {
              dds3SetQuake(100, 0x258u);
              v114 = g_aTimeStopSkl;
              goto LABEL_508;
LABEL_507:
              v114 = g_aTimeStopSkl;
LABEL_508:
              v217 = wk;
              v218 = v217->sklProc;
              if (v114[v218->timeStopID]->ptn == 2)
              {
                v217 = wk;
                v218 = v217->sklProc;
                if (v218->cnt == 60)
                {
                  v217 = wk;
                  sBlur = v217->sBlur;
                  sBlur->bRun = 1;
                  *(u32 *)&sBlur->alpha = 64;
                  *(u64 *)&sBlur->frm = 30;
                }
              }
LABEL_515:
              v222 = wk->sklProc;
              v223 = v222->cnt;
              v222 = wk->sklProc;
              if (v223 <= g_aTimeStopSkl[v222->timeStopID]->wait)
                goto LABEL_529;
LABEL_520:
              dds3FadeOut(0x80u, 0x80u, 0x80u, 0xFu);
LABEL_523:
              goto LABEL_526;
            }
            goto LABEL_507;
          case 6:
            goto LABEL_176;
          case 7:
            goto LABEL_204;
          default:
            goto LABEL_529;
        }
      case 4:
        v16 = wk;
        v17 = v16->sklProc;
        switch (v17->stp)
        {
          case 0:
            StopBattle();
            v40 = g_aTimeStopSkl;
            if (v40[wk->sklProc->timeStopID]->sklID == 890)
            {
              AnotherEnemy = sBtlGetAnotherEnemy(v10);
            }
            else
            {
              AnotherEnemy = 0;
            }
            v60 = v10;
            v61 = AnotherEnemy;
LABEL_171:
            sBtlBgnWaitALL_TimeStopSkill(v60, v61);
            sBtlStatusBitOn(v10, 0x10u);
            v10->status &= ~0x100u;
            v10->flg &= 0xFFFFFF2F;
            v63 = wk;
            status4 = v63->status4;
            v63->NotCnt_R1R2 = 6;
            v63->status4 = status4 & 0xFFFFEFFF;
            dds3FadeOut(0x80u, 0x80u, 0x80u, 0xFu);
LABEL_526:
            v89 = wk->sklProc;
LABEL_527:
            stp = v89->stp;
            goto LABEL_528;
          case 1:
            v17 = wk->sklProc;
            if (v17->cnt >= 16)
            {
              RestartBattle();
              sBtlStatusBitOff(v10, 0xFFFFFFEF);
              v119 = g_aTimeStopSkl;
              if (v119[wk->sklProc->timeStopID]->sklID == 890)
              {
                v120 = sBtlGetAnotherEnemy(v10);
              }
              else
              {
                v120 = 0;
              }
              sBtlForceDeleteAll_TimeStopSkill(v10, v120);
              v234 = wk->hitList;
              sBtlReleaseHitC_List(v234, 1u);
              sBtlAnimListClr();
              sBtlNakamaWarpReset();
              v235 = wk->sklProc;
              v236 = v235->stp + 1;
              v235->cnt = 0;
              v235->stp = v236;
              sBtlSetCmbBfrPos();
              for (k = 0; ; ++k)
              {
                v239 = wk->UnitMng;
                if (k >= v239->number)
                  break;
                v239 = wk->UnitMng;
                v240 = v239->pUnitL[k]->pUnit;
                if (v240)
                  v241 = v240 == v10;
                else
                  v241 = 1;
                if (!v241)
                  v240->vstatus |= 0x1000u;
              }
              v243 = SklVisualTbl->motionno;
              v10->pos = (struct sdfVector4_t)xmmword_3CFD5C0;
              v10->rot = (struct sdfVector4_t)xmmword_3CFD5C0;
              v10->rotbk = (struct sdfVector4_t)xmmword_3CFD5C0;
              if (!v244)
              sBtlSetMotion(v10, v243, 0, 0, 0);
              dds3SetQuake(300, 0x64u);
              v10->bYobidousa = 0;
              if (sklID == 890)
              {
                v246 = sBtlGetAnotherEnemy(v10);
                v247 = SklVisualTbl->motionno;
                sBtlSetMotion(v246, v247, 0, 0, 0);
              }
            }
            goto LABEL_529;
          case 2:
LABEL_189:
            dds3FadeIn2(0xFu);
            v72 = wk;
            v74 = v72->sklProc;
            v75 = v74->stp + 1;
            v74->cnt = 0;
            v74->stp = v75;
            sBtlGetUnitHelperPos(v10, 1);
            p_fields = &wk->fields;
            sub_1B335A0(p_fields, 0, v76);
            sBtlSetMode(13);
            CamMovePtn = sBtlGetCamMovePtn(g_aTimeStopSkl[wk->sklProc->timeStopID]->cam);
            sBtlSetMove(CamMovePtn, 1);
            v80 = wk->sysmsgList;
            sBtlReleaseSM_List(v80, 1u);
            sBtlCreateSM(wk->sysmsgList, v10, 10, sklID, 0, 120);
            wk->sysmsgList->bLock = 1;
            goto LABEL_529;
          case 3:
            v17 = wk->sklProc;
            v122 = v17->cnt;
            v17 = wk->sklProc;
            if (v122 < g_aTimeStopSkl[v17->timeStopID]->wait2)
              goto LABEL_529;
            v17 = wk->sklProc;
            v123 = v17->stp + 1;
            v17->cnt = 0;
            v17->stp = v123;
            sBtlSetMode(13);
            sBtlSetMove(g_CamMovAll, 1);
            v126 = v10->side;
            sBtlCheckEffectData(v10, sklID, 1u, 0, v126, -1, 0);
            sBtlForceDelete_SkillFlag_Acter(v10, 0x400u);
            if (g_aTimeStopSkl[wk->sklProc->timeStopID]->sklID != 890)
              goto LABEL_353;
            v10 = sBtlGetAnotherEnemy(v10);
            goto LABEL_350;
          case 4:
            goto LABEL_223;
          case 5:
            goto LABEL_176;
          case 6:
            v17 = wk->sklProc;
            if (v17->cnt < 31)
              goto LABEL_529;
            sBtlEndWaitALL(0, 0);
            if (sBtlCheckPlayerDead())
              goto LABEL_327;
            v130 = wk;
            v131 = v130->UnitMng;
            playerID = v130->playerID;
            v133 = sBtlSearchUnit_ID(v131, playerID);
            para = v133->para;
            BadStatus = sBtlGetBadStatus(para);
            if (BadStatus <= 0x11 && ((1 << BadStatus) & 0x2305F) != 0)
            {
LABEL_327:
              goto LABEL_329;
            }
            sBtlResetAction(v133);
            sBtlSetUseSkill(v133, 0, v258);
            sBtlSetMotion(v133, 0, 0, 0, 0);
LABEL_329:
            v139 = wk->sklProc;
            v140 = v139->stp;
            v139->bRun = 0;
            v139->cnt = 0;
            v139->stp = v140 + 1;
            v139 = wk->sklProc;
            if (g_aTimeStopSkl[v139->timeStopID]->sklID == 890)
            {
              sBtlGetAnotherEnemy(v10)->bStop = 0;
            }
            goto LABEL_529;
          default:
            goto LABEL_529;
        }
      case 5:
        v16 = wk;
        v17 = v16->sklProc;
        switch (v17->stp)
        {
          case 0:
            goto LABEL_166;
          case 1:
            v17 = wk->sklProc;
            if (v17->cnt < 16)
              goto LABEL_529;
            RestartBattle();
            sBtlStatusBitOff(v10, 0xFFFFFFEF);
            sBtlForceDeleteAll_TimeStopSkill(v10, 0);
            v43 = wk->hitList;
            sBtlReleaseHitC_List(v43, 1u);
            sBtlAnimListClr();
            sBtlNakamaWarpReset();
            v44 = wk->sklProc;
            v45 = v44->stp + 1;
            v44->cnt = 0;
            v44->stp = v45;
            sBtlSetCmbBfrPos();
            for (m = 0; ; ++m)
            {
              v48 = wk->UnitMng;
              if (m >= v48->number)
                break;
              v48 = wk->UnitMng;
              v49 = v48->pUnitL[m]->pUnit;
              if (v49)
                v50 = v49 == v10;
              else
                v50 = 1;
              if (!v50)
                v49->vstatus |= 0x1000u;
            }
            goto LABEL_372;
          case 2:
            dds3FadeIn2(0xFu);
            v142 = wk;
            v144 = v142->sklProc;
            v146 = v144->stp + 1;
            v144->cnt = 0;
            v144->stp = v146;
            if (!v145)
            sBtlGetUnitHelperPos(v10, 1);
            v148 = &wk->fields;
            sub_1B335A0(v148, 0, v147);
            sBtlSetMode(13);
            v150 = sBtlGetCamMovePtn(g_aTimeStopSkl[wk->sklProc->timeStopID]->cam);
            sBtlSetMove(v150, 1);
            v151 = wk->sysmsgList;
            sBtlReleaseSM_List(v151, 1u);
            sBtlCreateSM(wk->sysmsgList, v10, 10, sklID, 0, 120);
            wk->sysmsgList->bLock = 1;
LABEL_350:
            sBtlForceDelete_SkillFlag_Acter(v10, 0x400u);
LABEL_353:
            sBtlSetPosCmbBfrPos();
            goto LABEL_529;
          case 3:
            goto LABEL_227;
          case 4:
            goto LABEL_223;
          case 5:
            goto LABEL_176;
          case 6:
LABEL_204:
            v17 = wk->sklProc;
            if (v17->cnt < 31)
              goto LABEL_529;
            sBtlEndWaitALL(0, 0);
            if (sBtlCheckPlayerDead())
              goto LABEL_220;
            v82 = wk;
            v83 = v82->UnitMng;
            v84 = v82->playerID;
            v85 = sBtlSearchUnit_ID(v83, v84);
            v86 = v85->para;
            v87 = sBtlGetBadStatus(v86);
            if (v87 <= 0x11 && ((1 << v87) & 0x2305F) != 0)
            {
LABEL_220:
              goto LABEL_222;
            }
            sBtlResetAction(v85);
            sBtlSetUseSkill(v85, 0, v248);
            sBtlSetMotion(v85, 0, 0, 0, 0);
LABEL_222:
            v89 = wk->sklProc;
            stp = v89->stp;
            v89->bRun = 0;
LABEL_528:
            v89->cnt = 0;
            v89->stp = stp + 1;
            goto LABEL_529;
          default:
            goto LABEL_529;
        }
      case 6:
        v16 = wk;
        v17 = v16->sklProc;
        switch (v17->stp)
        {
          case 0:
            goto LABEL_166;
          case 1:
            v17 = wk->sklProc;
            if (v17->cnt >= 16)
            {
              RestartBattle();
              sBtlStatusBitOff(v10, 0xFFFFFFEF);
              sBtlForceDeleteAll_TimeStopSkill(v10, 0);
              v52 = wk->hitList;
              sBtlReleaseHitC_List(v52, 1u);
              sBtlAnimListClr();
              sBtlNakamaWarpReset();
              v53 = wk->sklProc;
              v54 = v53->stp + 1;
              v53->cnt = 0;
              v53->stp = v54;
              sBtlSetCmbBfrPos();
              for (n = 0; ; ++n)
              {
                v57 = wk->UnitMng;
                if (n >= v57->number)
                  break;
                v57 = wk->UnitMng;
                v58 = v57->pUnitL[n]->pUnit;
                if (v58)
                  v59 = v58 == v10;
                else
                  v59 = 1;
                if (!v59)
                  v58->vstatus |= 0x1000u;
              }
LABEL_372:
              v165 = SklVisualTbl->motionno;
              v10->pos = (struct sdfVector4_t)xmmword_3CFD5C0;
              v10->rot = (struct sdfVector4_t)xmmword_3CFD5C0;
              v10->rotbk = (struct sdfVector4_t)xmmword_3CFD5C0;
              if (!v166)
              sBtlSetMotion(v10, v165, 0, 0, 0);
              dds3SetQuake(300, 0x64u);
              v10->bYobidousa = 0;
            }
            goto LABEL_529;
          case 2:
            dds3FadeIn2(0xFu);
            v153 = wk;
            v155 = v153->sklProc;
            v157 = v155->stp + 1;
            v155->cnt = 0;
            v155->stp = v157;
            if (!v156)
            sBtlGetUnitHelperPos(v10, 1);
            v159 = &wk->fields;
            sub_1B335A0(v159, 0, v158);
            p_pCamSklUser = &wk->pCamSklUser;
            p_pCamSklUser = v10;
            sBtlSetMode(9);
            v161 = wk->sysmsgList;
            sBtlReleaseSM_List(v161, 1u);
            sBtlCreateSM(wk->sysmsgList, v10, 10, sklID, 0, 120);
            wk->sysmsgList->bLock = 1;
            sBtlForceDelete_SkillFlag_Acter(v10, 0x400u);
            sBtlSetPosCmbBfrPos();
            v10->pos.x = 0.0;
            v10->pos.y = 0.0;
            v10->pos.z = 200.0;
            goto LABEL_529;
          case 3:
LABEL_227:
            v17 = wk->sklProc;
            v91 = v17->cnt;
            v92 = sBtlGetActionTime(v10, 0);
            if (v92 == INFINITY || v91 >= (s32)v92)
            {
              v96 = v10->side;
              v97 = wk->sklProc;
              v98 = v97->stp + 1;
              v97->cnt = 0;
              v97->stp = v98;
              sBtlCheckEffectData(v10, sklID, 1u, 0, v96, -1, 0);
            }
            goto LABEL_529;
          case 4:
LABEL_223:
            v17 = wk->sklProc;
            if (v17->cnt == 60)
            {
LABEL_401:
              dds3SetQuake(100, 0x258u);
            }
            goto LABEL_515;
          case 5:
LABEL_176:
            v16 = wk;
            v17 = v16->sklProc;
            if (v17->cnt < 16)
              goto LABEL_529;
            v16 = wk;
            v17 = v16->sklProc;
            v67 = v17->stp + 1;
            v17->cnt = 0;
            v17->stp = v67;
            v68 = v16->sysmsgList;
            sBtlReleaseSM_List(v68, 1u);
            wk->sysmsgList->bLock = 0;
            sBtlSetMode(2);
            sBtlNoHokan();
            wk->camSlpMode = 2;
            sBtlSetPosCmbBfrPos();
            _Off(Blur2, 0);
            break;
          case 6:
            v17 = wk->sklProc;
            v163 = v17->cnt;
            goto LABEL_488;
          default:
            goto LABEL_529;
        }
LABEL_188:
        dds3FadeIn2(0xFu);
        goto LABEL_529;
      case 7:
        v16 = wk;
        v17 = v16->sklProc;
        break;
      default:
        goto LABEL_529;
    }
    switch (v17->stp)
    {
      case 0:
LABEL_166:
        StopBattle();
        v60 = v10;
        v61 = 0;
        goto LABEL_171;
      case 1:
        v17 = wk->sklProc;
        if (v17->cnt >= 16)
        {
          sBtlForceDelete_SkillFlag(0x400u);
          RestartBattle();
          sBtlStatusBitOff(v10, 0xFFFFFFEF);
          sBtlForceDeleteAll_TimeStopSkill(v10, 0);
          v181 = wk->hitList;
          sBtlReleaseHitC_List(v181, 1u);
          sBtlAnimListClr();
          sBtlNakamaWarpReset();
          v182 = wk->sklProc;
          v183 = v182->stp + 1;
          v182->cnt = 0;
          v182->stp = v183;
          sBtlSetCmbBfrPos();
          for (ii = 0; ; ++ii)
          {
            v186 = wk->UnitMng;
            if (ii >= v186->number)
              break;
            v186 = wk->UnitMng;
            v187 = v186->pUnitL[ii]->pUnit;
            if (v187)
              v188 = v187 == v10;
            else
              v188 = 1;
            if (!v188)
              v187->vstatus |= 0x1000u;
          }
          v10->pos = (struct sdfVector4_t)xmmword_3CFD5C0;
          v10->rot = (struct sdfVector4_t)xmmword_3CFD5C0;
          v10->rotbk = (struct sdfVector4_t)xmmword_3CFD5C0;
          if (!v232)
          sBtlSetMotion(v10, 4, 0, 0, 0);
          dds3SetQuake(150, 0x32u);
LABEL_548:
LABEL_550:
          sBtlForceDelete_SkillFlag_Acter(v10, 0x400u);
        }
        goto LABEL_529;
      case 2:
        dds3FadeIn2(0xFu);
        v190 = wk;
        v192 = v190->sklProc;
        v194 = v192->stp + 1;
        v192->cnt = 0;
        v192->stp = v194;
        if (!v193)
        sBtlGetUnitHelperPos(v10, 1);
        v196 = &wk->fields;
        sub_1B335A0(v196, 0, v195);
        sBtlSetMode(13);
        v198 = sBtlGetCamMovePtn(g_aTimeStopSkl[wk->sklProc->timeStopID]->cam);
        sBtlSetMove(v198, 1);
        v199 = wk->sysmsgList;
        sBtlReleaseSM_List(v199, 1u);
        sBtlCreateSM(wk->sysmsgList, v10, 96, 0, 0, 120);
        wk->sysmsgList->bLock = 1;
        goto LABEL_529;
      case 3:
        v17 = wk->sklProc;
        if (v17->cnt >= 121)
        {
LABEL_457:
          v17 = wk->sklProc;
          v200 = v17->stp + 1;
          v17->cnt = 0;
          v17->stp = v200;
        }
        goto LABEL_529;
      case 4:
        v16 = wk;
        if ((v16->status2 & 0x1000) != 0)
          goto LABEL_529;
        v16 = wk;
        v89 = v16->sklProc;
        v10->bYobidousa = 0;
        goto LABEL_527;
      case 5:
        v17 = wk->sklProc;
        v202 = v17->cnt;
        v17 = wk->sklProc;
        if (v202 > g_aTimeStopSkl[v17->timeStopID]->wait)
          goto LABEL_520;
        goto LABEL_529;
      case 6:
        v16 = wk;
        v17 = v16->sklProc;
        if (v17->cnt < 16)
          goto LABEL_529;
        v16 = wk;
        v17 = v16->sklProc;
        v203 = v17->stp + 1;
        v17->cnt = 0;
        v17->stp = v203;
        v204 = v16->sysmsgList;
        sBtlReleaseSM_List(v204, 1u);
        wk->sysmsgList->bLock = 0;
        sBtlSetPosCmbBfrPos();
LABEL_480:
        sBtlSetMode(2);
        sBtlNoHokan();
        wk->camSlpMode = 2;
        sBtlSetPosCmbBfrPos();
        goto LABEL_188;
      case 7:
        if (v17->cnt > 2)
          goto LABEL_486;
        goto LABEL_9004;
        if (wk->sklProc->cnt > 2)
        {
LABEL_486:
          goto LABEL_487;
        }
LABEL_9004:
        sBtlSetMode(2);
        sBtlNoHokan();
LABEL_487:
        v163 = wk->sklProc->cnt;
LABEL_488:
        if (v163 < 31)
          goto LABEL_529;
        sBtlEndWaitALL(0, 0);
        if (sBtlCheckPlayerDead())
          goto LABEL_502;
        v206 = wk;
        v207 = v206->UnitMng;
        v208 = v206->playerID;
        v209 = sBtlSearchUnit_ID(v207, v208);
        v210 = v209->para;
        v211 = sBtlGetBadStatus(v210);
        if (v211 <= 0x11 && ((1 << v211) & 0x2305F) != 0)
        {
LABEL_502:
LABEL_504:
          v213 = wk;
          v214 = v213->sklProc;
          v213->pCamSklUser = 0;
          v215 = v214->stp;
          v214->bRun = 0;
          v214->cnt = 0;
          v214->stp = v215 + 1;
LABEL_529:
          ++wk->sklProc->cnt;
          return;
        }
        sBtlResetAction(v209);
        sBtlSetUseSkill(v209, 0, v252);
        sBtlSetMotion(v209, 0, 0, 0, 0);
        goto LABEL_504;
      default:
        goto LABEL_529;
    }
  }
}

// 0x1eb7db0
void sBtlEisyoWaitTask(void) {
  if ((wk->status & 0x40) != 0)
    return;
  if (gEisyoNasiWaitTime < 1)
    return;
  gEisyoNasiWaitTime = gEisyoNasiWaitTime - 1;
}

// 0x1eb7ec0
static bool EisyoEndCheck(SBTLUNIT_WORK *wk) {
  bool result;
  SBTLUNIT_LISTWORK *SideList;
  s64 count;
  SBTLUNIT_LISTWORK *v7;
  s32 v8;
  s64 m_Items;
  s64 v10;

  if (gEisyoNasiWaitTime > 0)
    return 0;
  SideList = sBtlCreateSideList(2, 0);
  count = (u32)SideList->count;
  v7 = SideList;
  if ((s32)count < 1)
  {
    v8 = 0;
  }
  else
  {
    v8 = 0;
    m_Items = SideList->pUnitL;
    do
    {
      v10 = *(u64 *)(*(u64 *)(*(u64 *)m_Items + 24) + 904);
      if (*(u32 *)(v10 + 16) == 53 && *(u32 *)(v10 + 20) > wk->actwk->framecnt)
        ++v8;
      m_Items += 8;
      --count;
    }
    while (count);
  }
  sBtlDeleteUnitList(v7, 0);
  result = 0;
  if (v8 <= 0)
  {
    gEisyoNasiWaitTime = 50;
    return 1;
  }
  return result;
}

// 0x1eb8060
void sBtlAttackwaitWaitTask(void) {
  if ((wk->status & 0x40) != 0)
    return;
  if (gAttackwaitNasiWaitTime < 1)
    return;
  gAttackwaitNasiWaitTime = gAttackwaitNasiWaitTime - 1;
}

// 0x1eb8170
static bool AttackwaitEndCheck(SBTLUNIT_WORK *wk) {
  bool result;
  SBTLUNIT_LISTWORK *SideList;
  s64 count;
  SBTLUNIT_LISTWORK *v7;
  s32 v8;
  s64 m_Items;
  s64 v10;

  if (gAttackwaitNasiWaitTime > 0)
    return 0;
  SideList = sBtlCreateSideList(2, 0);
  count = (u32)SideList->count;
  v7 = SideList;
  if ((s32)count < 1)
  {
    v8 = 0;
  }
  else
  {
    v8 = 0;
    m_Items = SideList->pUnitL;
    do
    {
      v10 = *(u64 *)(*(u64 *)(*(u64 *)m_Items + 24) + 904);
      if (*(u32 *)(v10 + 16) == 55 && *(u32 *)(v10 + 20) > wk->actwk->framecnt)
        ++v8;
      m_Items += 8;
      --count;
    }
    while (count);
  }
  sBtlDeleteUnitList(v7, 0);
  result = 0;
  if (v8 <= 0)
  {
    gAttackwaitNasiWaitTime = 50;
    return 1;
  }
  return result;
}

// 0x1eb4c20
static s32 RaidoAttackCheck(void) {
  SBTLUNIT_LISTWORK *SideList;
  s64 v2;
  s32 v3;
  SBTLUNIT_WORK *pUnit;
  u32 status;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 targetID;

  SideList = sBtlCreateSideList(2, 0);
  if (SideList->count >= 1)
  {
    v2 = 0;
    v3 = 0;
    while (1)
    {
      pUnit = SideList->pUnitL[v2]->pUnit;
      status = pUnit->actwk->status;
      if (status == 3)
      {
        UnitMng = wk->UnitMng;
        targetID = pUnit->actaiwk->targetID;
        if (sBtlSearchUnit_ID(UnitMng, targetID))
        {
          if (wk->playerID == pUnit->actaiwk->targetID)
            ++v3;
        }
      }
      else if (status == 55)
      {
        ++v3;
      }
      if (++v2 >= SideList->count)
        goto LABEL_22;
    }
  }
  v3 = 0;
LABEL_22:
  sBtlDeleteUnitList(SideList, 0);
  return v3;
}

// 0x1eb8310
void sBtlZakoRouletteSet(SBTLUNIT_WORK *wk) {
  ;
}

// 0x1eb8320
void sBtlZakoWarpReset(SBTLUNIT_WORK *wk) {
  u32 warp_bk_color;
  s32 vstatus;
  u32 v5;
  dds3Basic_t *pBasic;

  warp_bk_color = wk->warp_bk_color;
  if (warp_bk_color)
  {
    wk->chgcolor = warp_bk_color;
    sBtlChangeModelColor(wk);
    vstatus = wk->vstatus;
    wk->fadepara = 16;
    wk->vstatus = vstatus & 0xFFDFFFFC;
    v5 = wk->warp_bk_color;
    wk->warp_bk_color = 0;
    wk->color = v5;
  }
  if (wk->not_hitmode)
  {
    wk->yure = 0;
    pBasic = wk->pBasic;
    if (!pBasic)
      return;
    goto LABEL_9;
  }
  if (!sBtlCheckSetHITNONE(-1, wk->para->devilid))
    wk->status &= ~1u;
  wk->flg &= ~2u;
  wk->yure = 0;
  pBasic = wk->pBasic;
  if (pBasic)
  {
LABEL_9:
    dds3UnitObjectBasicSetDamageYure(pBasic, 0.0);
  }
}

// 0x1eb8460
void sBtlBossWarpReset(SBTLUNIT_WORK *wk) {
  sdatUnitWork_t *para;
  u32 BadStatus;
  u32 v5;
  s32 vstatus;
  u32 v8;
  dds3Basic_t *pBasic;

  para = wk->para;
  BadStatus = sBtlGetBadStatus(para);
  if (BadStatus == 11)
    v5 = -2136655252;
  else
    v5 = -2139062144;
  wk->chgcolor = v5;
  sBtlChangeModelColor(wk);
  vstatus = wk->vstatus;
  if (BadStatus == 11)
    v8 = -2136655252;
  else
    v8 = -2139062144;
  wk->fadepara = 16;
  wk->warp_bk_color = 0;
  wk->color = v8;
  wk->vstatus = vstatus & 0xFFDFFFFC;
  if (wk->not_hitmode)
  {
    wk->yure = 0;
    pBasic = wk->pBasic;
    goto LABEL_15;
  }
  if (!sBtlCheckSetHITNONE(-1, wk->para->devilid))
    wk->status &= ~1u;
  wk->flg &= ~2u;
  wk->yure = 0;
  pBasic = wk->pBasic;
LABEL_15:
  dds3UnitObjectBasicSetDamageYure(pBasic, 0.0);
}
