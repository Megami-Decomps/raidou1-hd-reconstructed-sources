#include "types.h"
#include "BST.h"
#include "SBTLUNIT_MOTION.h"
#include "dds3effect_blend.h"
#include "dds3kernelcore.h"
#include "dds3kerneldraw.h"
#include "dds3objectbase.h"
#include "fclmisc.h"
#include "fclmsg.h"
#include "fld.h"
#include "kernel.h"
#include "mdl.h"
#include "meslogmain.h"
#include "sbtl.h"
#include "sbtlaction.h"
#include "sbtlai.h"
#include "sbtlbossevent.h"
#include "sbtlcalc.h"
#include "sbtlcamera.h"
#include "sbtlcmbskl.h"
#include "sbtldmg.h"
#include "sbtleff.h"
#include "sbtlencount.h"
#include "sbtlevent.h"
#include "sbtlexp.h"
#include "sbtlmain.h"
#include "sbtlmenu.h"
#include "sbtlplayer.h"
#include "sbtlscript.h"
#include "sbtlskill.h"
#include "sbtlsound.h"
#include "sbtlstp.h"
#include "sbtlsub.h"
#include "sbtlsupport.h"
#include "sbtlunit.h"
#include "sbtlvisual.h"
#include "sbtlweapon.h"
#include "scr.h"
#include "sdf_vu0.h"
#include "sdfmodel.h"
#include "sdfquat.h"
#include "sndat3.h"
#include "tips.h"

#define BOSSEVENT_X_POS 0
#define BOSSEVENT_Y_POS 0
#define BOSSEVENT_Z_POS 0
#define BTLBOSS_BMD_SYS_FILE "btlbossevent.bmd"
#define BOSS_EVENT_SCR_FILE "boss_scr.bf"
#define BOSSEVEPOSCNT 20
#define SBTL_BOSSEVENT_MAINPROC_NAME "sbtlbossevent_main"
#define BOSS_203_START1 0
#define BOSS_203_START2 1
#define BOSS_203_START2_sel 2
#define BOSS_203_START2_1 3
#define BOSS_203_START2_2 4
#define BOSS_205_START1 5
#define BOSS_ALP_START1 6
#define BOSS_ALP_START2 7
#define BOSS_ALP_START3 8
#define BOSS_MUNAKA_IMAD1 9
#define BOSS_MUNAKA_IMAD2 10
#define BOSS_MUNAKA_DAMS 11
#define BOSS_ASURA_QUEST_44_00 12
#define BOSS_ASURA_QUEST_44_01 13

typedef enum {
    sBtlBossEvent_BattleStart_BOSSEVE_BTLSTART_INIT = 0,
    sBtlBossEvent_BattleStart_BOSSEVE_BTLSTART_INIT_F = 1,
    sBtlBossEvent_BattleStart_BOSSEVE_BTLSTART_FADE_W = 2,
    sBtlBossEvent_BattleStart_BOSSEVE_BTLSTART_SET = 3,
    sBtlBossEvent_BattleStart_BOSSEVE_BTLSTART_FADE_IN_W = 4,
    sBtlBossEvent_BattleStart_BOSSEVE_BTLSTART_TUWAIT = 5,
    sBtlBossEvent_BattleStart_BOSSEVE_BTLSTART_MSG = 6,
    sBtlBossEvent_BattleStart_BOSSEVE_BTLSTART_MSGUPDATE = 7,
    sBtlBossEvent_BattleStart_BOSSEVE_BTLSTART_MSGUPDATE_GOUTO = 8,
    sBtlBossEvent_BattleStart_BOSSEVE_BTLSTART_WAIT1 = 9,
    sBtlBossEvent_BattleStart_BOSSEVE_BTLSTART_WAIT1B = 10,
    sBtlBossEvent_BattleStart_BOSSEVE_BTLSTART_MOTIONSTART = 11,
    sBtlBossEvent_BattleStart_BOSSEVE_BTLSTART_SE = 12,
    sBtlBossEvent_BattleStart_BOSSEVE_BTLSTART_WAIT2 = 13,
    sBtlBossEvent_BattleStart_BOSSEVE_BTLSTART_RESET = 14,
    sBtlBossEvent_BattleStart_BOSSEVE_BTLSTART_FADE_W3 = 15,
    sBtlBossEvent_BattleStart_BOSSEVE_BTLSTART_WAIT3 = 16,
    sBtlBossEvent_BattleStart_BOSSEVE_BTLSTART_TIPS = 17,
    sBtlBossEvent_BattleStart_BOSSEVE_BTLSTART_TIPS_WAIT = 18,
    sBtlBossEvent_BattleStart_BOSSEVE_BTLSTART_END = 19,
} sBtlBossEvent_BattleStart_BOSSEVE_BTLSTART;

typedef enum {
    BOSSEVE_BTLRESTART_INIT = 0,
    BOSSEVE_BTLRESTART_FADE_IN_W = 1,
    BOSSEVE_BTLRESTART_MSG = 2,
    BOSSEVE_BTLRESTART_MSGUPDATE = 3,
    BOSSEVE_BTLRESTART_WAIT1 = 4,
    BOSSEVE_BTLRESTART_MOTIONSTART = 5,
    BOSSEVE_BTLRESTART_SE = 6,
    BOSSEVE_BTLRESTART_WAIT2 = 7,
    BOSSEVE_BTLRESTART_RESET = 8,
    BOSSEVE_BTLRESTART_FADE_W3 = 9,
    BOSSEVE_BTLRESTART_WAIT3 = 10,
    BOSSEVE_BTLRESTART_END = 11,
} BOSSEVE_BTLRESTART;

typedef enum {
    BOSSEVE_BTLMAG_INIT = 0,
    BOSSEVE_BTLMAG_INIT_SKILL = 1,
    BOSSEVE_BTLMAG_SKILLEND_W = 2,
    BOSSEVE_BTLMAG_SKILL = 3,
    BOSSEVE_BTLMAG_SKILLEND_W2 = 4,
    BOSSEVE_BTLMAG_MSGWAIT = 5,
    BOSSEVE_BTLMAG_TUWAIT = 6,
    BOSSEVE_BTLMAG_MSG = 7,
    BOSSEVE_BTLMAG_MSGUPDATE = 8,
    BOSSEVE_BTLMAG_MSGUPDATE_EX = 9,
    BOSSEVE_BTLMAG_WAIT1 = 10,
    BOSSEVE_BTLMAG_MOTIONSTART = 11,
    BOSSEVE_BTLMAG_SE = 12,
    BOSSEVE_BTLMAG_WAIT2 = 13,
    BOSSEVE_BTLMAG_FADE_W2 = 14,
    BOSSEVE_BTLMAG_RESET = 15,
    BOSSEVE_BTLMAG_FADE_W3 = 16,
    BOSSEVE_BTLMAG_WAIT3 = 17,
    BOSSEVE_BTLMAG_END = 18,
} BOSSEVE_BTLMAG;

typedef enum {
    BOSSEVE_BTLDEAD_INIT = 0,
    BOSSEVE_BTLDEAD_MOTIONDOWN = 1,
    BOSSEVE_BTLDEAD_WAIT1 = 2,
    BOSSEVE_BTLDEAD_MSG = 3,
    BOSSEVE_BTLDEAD_MSGUPDATE = 4,
    BOSSEVE_BTLDEAD_MSGUPDATE_GOUTO = 5,
    BOSSEVE_BTLDEAD_WAIT2 = 6,
    BOSSEVE_BTLDEAD_CAMERASTART = 7,
    BOSSEVE_BTLDEAD_CAMERAWAIT = 8,
    BOSSEVE_BTLDEAD_MOTIONSTART = 9,
    BOSSEVE_BTLDEAD_WAIT3 = 10,
    BOSSEVE_BTLDEAD_RAIDOMOTIONSTART = 11,
    BOSSEVE_BTLDEAD_WAIT4 = 12,
    BOSSEVE_BTLDEAD_RESET = 13,
    BOSSEVE_BTLDEAD_LOADWAIT = 14,
    BOSSEVE_BTLDEAD_END = 15,
} BOSSEVE_BTLDEAD;

typedef enum {
    BOSSEVE_BTLTIME_INIT = 0,
    BOSSEVE_BTLTIME_MOTIONDOWN = 1,
    BOSSEVE_BTLTIME_WAIT1 = 2,
    BOSSEVE_BTLTIME_MSG = 3,
    BOSSEVE_BTLTIME_MSGUPDATE = 4,
    BOSSEVE_BTLTIME_WAIT2 = 5,
    BOSSEVE_BTLTIME_CAMERASTART = 6,
    BOSSEVE_BTLTIME_CAMERAWAIT = 7,
    BOSSEVE_BTLTIME_MOTIONSTART = 8,
    BOSSEVE_BTLTIME_WAIT3 = 9,
    BOSSEVE_BTLTIME_RAIDOMOTIONSTART = 10,
    BOSSEVE_BTLTIME_WAIT4 = 11,
    BOSSEVE_BTLTIME_RESET = 12,
    BOSSEVE_BTLTIME_END = 13,
} BOSSEVE_BTLTIME;

typedef enum {
    BOSSEVE_BTLSMN_INIT = 0,
    BOSSEVE_BTLSMN_001 = 1,
    BOSSEVE_BTLSMN_002 = 2,
    BOSSEVE_BTLSMN_003 = 3,
    BOSSEVE_BTLSMN_004 = 4,
    BOSSEVE_BTLSMN_005 = 5,
    BOSSEVE_BTLSMN_006 = 6,
    BOSSEVE_BTLSMN_006_B = 7,
    BOSSEVE_BTLSMN_006_B2 = 8,
    BOSSEVE_BTLSMN_006_B3 = 9,
    BOSSEVE_BTLSMN_006_C = 10,
    BOSSEVE_BTLSMN_007 = 11,
    BOSSEVE_BTLSMN_008 = 12,
    BOSSEVE_BTLSMN_009 = 13,
    BOSSEVE_BTLSMN_010 = 14,
    BOSSEVE_BTLSMN_011 = 15,
    BOSSEVE_BTLSMN_012 = 16,
    BOSSEVE_BTLSMN_013 = 17,
    BOSSEVE_BTLSMN_014 = 18,
    BOSSEVE_BTLSMN_015 = 19,
    BOSSEVE_BTLSMN_016 = 20,
    BOSSEVE_BTLSMN_017 = 21,
    BOSSEVE_BTLSMN_018 = 22,
    BOSSEVE_BTLSMN_019 = 23,
    BOSSEVE_BTLSMN_020 = 24,
    BOSSEVE_BTLSMN_END = 25,
} BOSSEVE_BTLSMN;

typedef enum {
    BOSSEVE_BTLLOSE_INIT = 0,
    BOSSEVE_BTLLOSE_01 = 1,
    BOSSEVE_BTLLOSE_02 = 2,
    BOSSEVE_BTLLOSE_03 = 3,
    BOSSEVE_BTLLOSE_04 = 4,
    BOSSEVE_BTLLOSE_05 = 5,
    BOSSEVE_BTLLOSE_06 = 6,
    BOSSEVE_BTLLOSE_07 = 7,
    BOSSEVE_BTLLOSE_08 = 8,
    BOSSEVE_BTLLOSE_09 = 9,
    BOSSEVE_BTLLOSE_10 = 10,
    BOSSEVE_BTLLOSE_11 = 11,
    BOSSEVE_BTLLOSE_END = 12,
} BOSSEVE_BTLLOSE;

typedef enum {
    BOSSEVE_BTLRDYING_INIT = 0,
    BOSSEVE_BTLRDYING_MOTIONDOWN = 1,
    BOSSEVE_BTLRDYING_WAIT1 = 2,
    BOSSEVE_BTLRDYING_DOWN_M = 3,
    BOSSEVE_BTLRDYING_DOWN_W = 4,
    BOSSEVE_BTLRDYING_MSG = 5,
    BOSSEVE_BTLRDYING_MSG2 = 6,
    BOSSEVE_BTLRDYING_MSGUPDATE = 7,
    BOSSEVE_BTLRDYING_MSGUPDATE_EX = 8,
    BOSSEVE_BTLRDYING_WAIT2 = 9,
    BOSSEVE_BTLRDYING_CAMERASTART = 10,
    BOSSEVE_BTLRDYING_CAMERAWAIT = 11,
    BOSSEVE_BTLRDYING_MOTIONSTART = 12,
    BOSSEVE_BTLRDYING_WAIT3 = 13,
    BOSSEVE_BTLRDYING_RAIDOMOTIONSTART = 14,
    BOSSEVE_BTLRDYING_WAIT4 = 15,
    BOSSEVE_BTLRDYING_RESET = 16,
    BOSSEVE_BTLRDYING_END = 17,
} BOSSEVE_BTLRDYING;

typedef enum {
    BOSSEVE_BTLDYING_INIT = 0,
    BOSSEVE_BTLDYING_MOTIONDOWN = 1,
    BOSSEVE_BTLDYING_WAIT1 = 2,
    BOSSEVE_BTLDYING_DOWN_M = 3,
    BOSSEVE_BTLDYING_DOWN_W = 4,
    BOSSEVE_BTLDYING_MSG = 5,
    BOSSEVE_BTLDYING_MSGUPDATE = 6,
    BOSSEVE_BTLDYING_MSGUPDATE_EX = 7,
    BOSSEVE_BTLDYING_WAIT2 = 8,
    BOSSEVE_BTLDYING_CAMERASTART = 9,
    BOSSEVE_BTLDYING_CAMERAWAIT = 10,
    BOSSEVE_BTLDYING_MOTIONSTART = 11,
    BOSSEVE_BTLDYING_WAIT3 = 12,
    BOSSEVE_BTLDYING_RAIDOMOTIONSTART = 13,
    BOSSEVE_BTLDYING_WAIT4 = 14,
    BOSSEVE_BTLDYING_RESET = 15,
    BOSSEVE_BTLDYING_END = 16,
} BOSSEVE_BTLDYING;

typedef enum {
    BOSSEVE_BTLDYING_SINADO1_INIT = 0,
    BOSSEVE_BTLDYING_SINADO1_MOTIONDOWN = 1,
    BOSSEVE_BTLDYING_SINADO1_WAIT1 = 2,
    BOSSEVE_BTLDYING_SINADO1_DOWN_W = 3,
    BOSSEVE_BTLDYING_SINADO1_MSG = 4,
    BOSSEVE_BTLDYING_SINADO1_MSGUPDATE = 5,
    BOSSEVE_BTLDYING_SINADO1_MSGUPDATE_EX = 6,
    BOSSEVE_BTLDYING_SINADO1_WAIT2 = 7,
    BOSSEVE_BTLDYING_SINADO1_CAMERASTART = 8,
    BOSSEVE_BTLDYING_SINADO1_CAMERAWAIT = 9,
    BOSSEVE_BTLDYING_SINADO1_RAIDOMOTIONSTART = 10,
    BOSSEVE_BTLDYING_SINADO1_WAIT4 = 11,
    BOSSEVE_BTLDYING_SINADO1_RESET = 12,
    BOSSEVE_BTLDYING_SINADO1_END = 13,
} BOSSEVE_BTLDYING_SINADO1;

typedef enum {
    APO_INIT = 0,
    APO_INIT_F = 1,
    APO_FADE_W = 2,
    APO_SET = 3,
    APO_FADE_IN_W = 4,
    APO_MSG = 5,
    APO_MSGUPDATE = 6,
    APO_WAIT1 = 7,
    APO_WAIT1B = 8,
    APO_MOTIONSTART = 9,
    APO_MSG2 = 10,
    APO_MSG2UPDATE = 11,
    APO_WAIT2 = 12,
    APO_FADE_W2 = 13,
    APO_RESET = 14,
    APO2_INIT = 15,
    APO2_INIT_SKILL = 16,
    APO2_SKILLEND_W = 17,
    APO2_SKILL = 18,
    APO2_SKILLEND_W2 = 19,
    APO2_MSG = 20,
    APO2_MSGUPDATE = 21,
    APO2_WAIT1 = 22,
    APO2_MSG2 = 23,
    APO2_MSG2UPDATE = 24,
    APO2_MOTIONSTART = 25,
    APO2_SE = 26,
    APO2_WAIT2 = 27,
    APO2_FADE_W2 = 28,
    APO2_RESET = 29,
    APO2_FADE_W3 = 30,
    APO2_WAIT3 = 31,
    APO2_END = 32,
} sBtlBossEvent_BattleStartApo_BOSSEVE_BTLSTART;

typedef enum {
    sBtlBossEvent_MUNAKA_MessageEvent_BOSSEVE_BTLSTART_INIT = 0,
    sBtlBossEvent_MUNAKA_MessageEvent_BOSSEVE_BTLSTART_INIT_F = 1,
    sBtlBossEvent_MUNAKA_MessageEvent_BOSSEVE_BTLSTART_FADE_W = 2,
    sBtlBossEvent_MUNAKA_MessageEvent_BOSSEVE_BTLSTART_SET = 3,
    sBtlBossEvent_MUNAKA_MessageEvent_BOSSEVE_BTLSTART_FADE_IN_W = 4,
    sBtlBossEvent_MUNAKA_MessageEvent_BOSSEVE_BTLSTART_TUWAIT = 5,
    sBtlBossEvent_MUNAKA_MessageEvent_BOSSEVE_BTLSTART_MSG = 6,
    sBtlBossEvent_MUNAKA_MessageEvent_BOSSEVE_BTLSTART_MSGUPDATE = 7,
    sBtlBossEvent_MUNAKA_MessageEvent_BOSSEVE_BTLSTART_END = 8,
} sBtlBossEvent_MUNAKA_MessageEvent_BOSSEVE_BTLSTART;

typedef enum {
    BOSSEVENT_CAMERA_SMALL = 0,
    BOSSEVENT_CAMERA_MIDDLE = 1,
    BOSSEVENT_CAMERA_MUSHI = 2,
    BOSSEVENT_CAMERA_BIG = 3,
    BOSSEVENT_CAMERA_SPBIG = 4,
    BOSSEVENT_CAMERA_TENTO = 5,
    BOSSEVENT_CAMERA_SINADO = 6,
    BOSSEVENT_CAMERA_SMALL_HD = 7,
    BOSSEVENT_CAMERA_BIG_HD = 8,
    BOSSEVENT_CAMERA_SPBIG_HD = 9,
} BOSSEVENT_CAMERA;

typedef enum {
    SBTL_BOSSEVENT_STEP_INIT_0 = 0,
    SBTL_BOSSEVENT_STEP_INIT_1 = 1,
    SBTL_BOSSEVENT_STEP_INIT_2 = 2,
    SBTL_BOSSEVENT_STEP_MAIN = 3,
    SBTL_BOSSEVENT_STEP_END = 4,
} SBTL_BOSSEVENT_STEP;

typedef struct SBTLUNIT_WORK SBTLUNIT_WORK;
typedef struct TYPE_BOSS_NML_EVENT TYPE_BOSS_NML_EVENT;
typedef struct dds3ProcessID_t dds3ProcessID_t;
typedef struct sBtlBossEvent_t sBtlBossEvent_t;

struct sBtlBossEvent_t {
    dds3ProcessID_t *listPID;
    u8 *pDatScr;
    s32 scrReq;
    dds3ProcessID_t *scrPID;
    SBTL_BOSSEVENT_STEP step;
    u8 flag;
    s8 end_mode;
    s8 end_enemypos_no_reset;
    s16 fade_count;
    SBTLBOSSEVENT eventtype;
    s16 cdstep;
    u32 cdwaitcnt;
    s16 mvstep;
    s16 mvwaitcnt;
    s16 msgofs;
    s16 motionchkflg;
    s32 tipsOfs;
    TYPE_BOSS_NML_EVENT *pTypeBossNmlEvent;
    s32 bossTalkType;
};

struct TYPE_BOSS_NML_EVENT {
    s32 enc_id;
    s32 devil_id;
    s32 bossCnt;
    s32 bossIdx;
    BOSSEVENT_CAMERA cam_size;
    s32 skill_id;
    s32 start_on;
    s32 mag_on1;
    s32 mag_on2;
    s32 mag_on3;
    s32 dead_on;
    s32 lose_on;
    s32 dying_on;
    s32 time_on;
    s32 mag_se_dead;
    s32 mag_se_kikan;
    SBTLUNIT_MOTION yaruki_motion_id;
    s32 yaruki_se_syokan;
    s32 lbl_start[3];
    s32 lbl_mag1[3];
    s32 lbl_mag2[3];
    s32 lbl_mag3[3];
    s32 lbl_dead[3];
    s32 lbl_lose[3];
    s32 lbl_dying[3];
    s32 lbl_time[3];
    s32 lbl_sum[3];
    s32 lbl_restart[3];
    s32 lbl_tips[3];
};

static f32 startf;
static s32 hdown_a;
static s32 hdown_on;
static s32 hdown_wait;

static f32 startf;

static f32 startf;
static s32 hdown_a;
static s32 hdown_on;
static s32 hdown_wait;

static SBTLUNIT_WORK *summonwk;

static SBTLUNIT_WORK *summonwk;

static f32 startf;

f32 *sbBossRaidouPos[10];
static dds3ProcessID_t *g_mainPID;
static TYPE_BOSS_NML_EVENT *arrBossEveTable;
static s32 arrBossEveTable_Size;
static s32 g_timedrawf;
static s32 g_bosseventhpflg;
bool preMenuEvent;
static s32 start_on_r1;
static s32 start_on_tips;
static s32 start_on_esw;
static s32 **cameraInitNo;
static s32 *cameraStartNo;
static s32 *cameraMagNo;
static s32 *cameraDeadNo;
static s32 *cameraTimeNo;
static s32 *cameraLoseNo;
static s32 *cameraDyingNo;

static bool CamBreakCheck(sBtlBossEvent_t *_wk);
static s32 sBtlBossEventModelMove(SBTLUNIT_WORK *unitwk);
static bool _CheckMotionEnd(SBTLUNIT_WORK *wk);
static void ResetBadStatusAll(BST IgnoreBstNo);
static void CameraPosSet(s32 hpos);
static void PosSet(void);
static void PosReSet(void);
static void CameraSet(void);
static void ReStartBattle(void);
static TYPE_BOSS_NML_EVENT *GetTable(SBTLUNIT_WORK *unit);
static dds3ProcessFunc_t Process(dds3ProcessID_t *PID);
static void Shutdown(dds3ProcessID_t *PID);

// 0x1da5a00
static bool CamBreakCheck(sBtlBossEvent_t *_wk) {
  return (u32)(wk->pTypeBossNmlEvent->cam_size - 10) < 0xFFFFFFFE;
}

// 0x1d9ece0
s32 sBtlEffect(void) {
  Il2CppObject *ProcessData;
  Il2CppObject *v4;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 boss_eventID;
  SBTLUNIT_WORK *v11;
  s32 hdown_a_local;
  s32 v15;
  SBATTLE_WORK *v21;
  s32 timedrawflg;
  s32 v24;
  s32 hdown_wait_local;
  SBATTLE_WORK *v29;
  s32 encountno;
  s64 v31;
  u32 klass_high;
  s32 v35;
  f32 ActionTime;
  S_CameraMoveDt *CamMovePtn;
  u32 v40;
  s16 v42;
  u32 v43;
  s64 v44;
  s32 v45;
  s64 v51;
  s32 v52;
  s16 v53;
  SBATTLE_WORK *v59;
  u32 v60;
  s64 v61;
  s32 v62;
  u8 *v63;
  s32 v65;
  u8 *v66;
  s32 v67;
  s32 v69;
  u8 *monitor;
  dds3ProcessID_t *started;

  ProcessData = dds3GetProcessData(g_mainPID);
  v4 = ProcessData;
  UnitMng = wk->UnitMng;
  boss_eventID = wk->boss_eventID;
  v11 = sBtlSearchUnit_ID(UnitMng, boss_eventID);
  switch (LOWORD(v4[4].klass))
  {
    case 0:
      sndSeLoadId(184);
      LOWORD(v4[4].klass) = 1;
      hdown_a = 0;
      hdown_on = 0;
      hdown_a_local = hdown_a;
      if (hdown_on)
        goto LABEL_189;
      goto LABEL_201;
    case 1:
      if (sndSeStatus() != 2)
        goto LABEL_188;
      sndSePlay(0);
      dds3FadeOut(0xFFu, 0xFFu, 0xFFu, 0x3Cu);
      LOWORD(v4[3].monitor) = 0;
      LOWORD(v4[4].klass) = 2;
      hdown_a_local = hdown_a;
      if (!hdown_on)
        goto LABEL_201;
      goto LABEL_189;
    case 2:
      v15 = (s16)LOWORD(v4[3].monitor)++;
      if (v15 < 61)
        goto LABEL_188;
      PosSet();
      LOWORD(v4[4].klass) = 3;
      hdown_a_local = hdown_a;
      if (!hdown_on)
        goto LABEL_201;
      goto LABEL_189;
    case 3:
      CameraPosSet(1);
      CameraSet();
      v21 = wk;
      v21->kaiwapaneldisp1 = 0;
      v21->status4 &= ~0x10u;
      timedrawflg = v21->timedrawflg;
      v21->timedrawflg = 0;
      g_timedrawf = timedrawflg;
      *(u16 *)&v21->kaiwaflg = 1;
      sBtlStatusBitOn(v11, 0x10u);
      LOWORD(v4[3].monitor) = 0;
      dds3FadeIn2(0x1Eu);
      LOWORD(v4[4].klass) = 4;
      hdown_a_local = hdown_a;
      if (!hdown_on)
        goto LABEL_201;
      goto LABEL_189;
    case 4:
      v24 = (s16)LOWORD(v4[3].monitor)++;
      if (v24 < 61)
        goto LABEL_188;
      WORD2(v4[4].monitor) = 0;
      LOWORD(v4[4].klass) = 6;
      hdown_a_local = hdown_a;
      if (!hdown_on)
        goto LABEL_201;
      goto LABEL_189;
    case 5:
      hdown_wait_local = hdown_wait - 1;
      hdown_wait = hdown_wait_local;
      if (hdown_on && hdown_wait_local == 4)
      {
        SE(27);
        hdown_wait_local = hdown_wait;
      }
      if ((hdown_wait_local & 0x80000000) == 0)
        goto LABEL_188;
      LOWORD(v4[4].klass) = 6;
      hdown_a_local = hdown_a;
      if (!hdown_on)
        goto LABEL_201;
      goto LABEL_189;
    case 6:
      if ((*(u32 *)(*((u64 *)v4[5].monitor + 11) + 4 * SWORD2(v4[4].monitor) + 32) & 0x80000000) != 0)
      {
        v52 = WORD2(v4[4].monitor) + 1;
        WORD2(v4[4].monitor) = v52;
        if (v52 << 16 < 196608)
          goto LABEL_188;
        goto LABEL_155;
      }
      v29 = wk;
      encountno = v29->encountno;
      if (encountno == 515 && WORD2(v4[4].monitor) == 1)
      {
        v31 = 1;
        v69 = *(u32 *)(*((u64 *)v4[5].monitor + 11) + 4 * v31 + 32);
        LODWORD(v4[2].klass) = 1;
        monitor = v4[1].monitor;
        v29->scrMsgID = v69;
        v66 = monitor;
        v67 = 1;
      }
      else
      {
        v29 = wk;
        encountno = v29->encountno;
        if (encountno != 536 || WORD2(v4[4].monitor))
        {
          fclStart1(*(u32 *)(*((u64 *)v4[5].monitor + 11) + 4 * SWORD2(v4[4].monitor) + 32), 1);
          fclSkipNoEnd(g_mainPID, 1);
          v53 = 7;
          goto LABEL_200;
        }
        v51 = 0;
        v63 = v4[1].monitor;
        v65 = *(u32 *)(*((u64 *)v4[5].monitor + 11) + 4 * v51 + 32);
        LODWORD(v4[2].klass) = 2;
        v29->scrMsgID = v65;
        v66 = v63;
        v67 = 2;
      }
      started = scrStartScript2(11027, v66, v67, 1);
      v4[2].monitor = started;
      v53 = 8;
LABEL_200:
      LOWORD(v4[4].klass) = v53;
      ++WORD2(v4[4].monitor);
      hdown_a_local = hdown_a;
      if (hdown_on)
        goto LABEL_189;
      goto LABEL_201;
    case 7:
      if (Update())
        goto LABEL_188;
      if (SWORD2(v4[4].monitor) > 2)
      {
        if (hdown_on)
          *(u64 *)&hdown_on = 0x3200000000LL;
LABEL_155:
        v42 = 9;
        goto LABEL_187;
      }
      LOWORD(v4[4].klass) = 6;
      if (!hdown_on)
        goto LABEL_188;
      LOWORD(v4[4].klass) = 5;
      *(u64 *)&hdown_on = 0x3200000000LL;
      hdown_a_local = hdown_a;
      if (!hdown_on)
        goto LABEL_201;
      goto LABEL_189;
    case 8:
      if (!v4[2].monitor)
        goto LABEL_188;
      if (dds3GetProcessStat(&v4[2].monitor) != 3)
      {
        if (dds3GetProcessStat(&v4[2].monitor))
          goto LABEL_188;
      }
      v4[2].monitor = 0;
      LODWORD(v4[2].klass) = -1;
      goto LABEL_155;
    case 9:
      scrEventSkipEnd(0, 0);
      scrLogEnd(g_mainPID);
      sndSeLoadId(184);
      LOWORD(v4[4].klass) = 10;
      hdown_a_local = hdown_a;
      if (!hdown_on)
        goto LABEL_201;
      goto LABEL_189;
    case 0xA:
      klass_high = HIDWORD(v4[4].klass);
      HIDWORD(v4[4].klass) = klass_high + 1;
      if (klass_high < 0x3D)
        goto LABEL_188;
      if (sndSeStatus() != 2)
        goto LABEL_188;
      LOWORD(v4[4].klass) = 11;
      hdown_a_local = hdown_a;
      if (!hdown_on)
        goto LABEL_201;
      goto LABEL_189;
    case 0xB:
      v11->vstatus |= 0x2000000u;
      v35 = *((u32 *)v4[5].monitor + 20);
      sBtlSetMotion(v11, v35, 6, 0, 2);
      ActionTime = sBtlGetActionTime(v11, 0);
      startf = ActionTime;
      sBtlSetMode(13);
      sBtlSetCmbBfrPos();
      CamMovePtn = sBtlGetCamMovePtn(cameraStartNo[*((s32 *)v4[5].monitor + 8)]);
      sBtlSetMove(CamMovePtn, 1);
      HIDWORD(v4[4].klass) = 0;
      LOWORD(v4[4].klass) = 13;
      hdown_a_local = hdown_a;
      if (!hdown_on)
        goto LABEL_201;
      goto LABEL_189;
    case 0xD:
      v40 = HIDWORD(v4[4].klass);
      if (v40 == 45)
      {
        sndSePlay(0);
        dds3SetQuake(110, 0x96u);
        dds3FadeOut(0xFFu, 0xFFu, 0xFFu, 0x3Cu);
        v40 = HIDWORD(v4[4].klass);
      }
      if (v40 != 60)
        goto LABEL_104;
      if ((u32)(*((u32 *)v4[5].monitor + 8) - 10) >= 0xFFFFFFFE)
      {
        HIDWORD(v4[4].klass) = 61;
        hdown_a_local = hdown_a;
        if (hdown_on)
          goto LABEL_189;
      }
      else
      {
        sBtlSetMoveEnd();
        v40 = HIDWORD(v4[4].klass);
LABEL_104:
        HIDWORD(v4[4].klass) = v40 + 1;
        if (v40 < 0x70)
          goto LABEL_188;
        sBtlSetMode(4);
        LOWORD(v4[3].monitor) = 0;
        LOWORD(v4[4].klass) = 14;
        hdown_a_local = hdown_a;
        if (hdown_on)
          goto LABEL_189;
      }
      goto LABEL_201;
    case 0xE:
      v11->vstatus |= 0x2000000u;
      sBtlSetMotion(v11, 0, 6, 0, 2);
      v42 = 16;
      goto LABEL_187;
    case 0x10:
      v43 = HIDWORD(v4[4].klass);
      if (v43 != 1)
      {
        if (v43 != 2)
          goto LABEL_114;
        goto LABEL_173;
      }
      if ((wk->status2 & 0x800000) == 0)
      {
        goto LABEL_145;
      }
      sBtlSetMode(2);
LABEL_145:
      if (wk->bBfrBtlEnd)
        sBtlSetMode(2);
      BYTE6(v4[3].klass) = 1;
      PosReSet();
      v43 = HIDWORD(v4[4].klass);
      if (v43 != 2)
      {
LABEL_114:
        if (v43 != 45)
          goto LABEL_115;
        goto LABEL_176;
      }
LABEL_173:
      dds3FadeIn2(0x1Eu);
      v43 = HIDWORD(v4[4].klass);
      if (v43 != 45)
      {
LABEL_115:
        HIDWORD(v4[4].klass) = v43 + 1;
        if (v43 < 0x5B)
          goto LABEL_188;
        goto LABEL_181;
      }
LABEL_176:
      v59 = wk;
      *(u16 *)&v59->kaiwaflg = 256;
      v59->kaiwapaneldisp1 = 1;
      v59->timedrawflg = g_timedrawf;
      v60 = HIDWORD(v4[4].klass);
      HIDWORD(v4[4].klass) = v60 + 1;
      if (v60 < 0x5B)
        goto LABEL_188;
LABEL_181:
      v61 = *((u64 *)v4[5].monitor + 21);
      if (v61 && *(u32 *)(v61 + 32) != -1)
      {
        LODWORD(v4[5].klass) = 0;
LABEL_184:
        LOWORD(v4[4].klass) = 17;
        hdown_a_local = hdown_a;
        if (hdown_on)
          goto LABEL_189;
        goto LABEL_201;
      }
      v42 = 19;
LABEL_187:
      LOWORD(v4[4].klass) = v42;
      HIDWORD(v4[4].klass) = 0;
LABEL_188:
      hdown_a_local = hdown_a;
      if (hdown_on)
      {
LABEL_189:
        v62 = hdown_a_local + 2;
        if (v62 >= 80)
          v62 = 80;
        goto LABEL_205;
      }
LABEL_201:
      if (hdown_a_local < 1)
        return 1;
      if (hdown_a_local <= 2)
        hdown_a_local = 2;
      v62 = hdown_a_local - 2;
LABEL_205:
      hdown_a = v62;
      return 1;
    case 0x11:
      v44 = *((u64 *)v4[5].monitor + 21);
      if (!v44)
        goto LABEL_133;
      v45 = *(u32 *)(v44 + 4 * SLODWORD(v4[5].klass) + 32);
      tipsTIPSStart(v45);
      if (*(u32 *)(*((u64 *)v4[5].monitor + 21) + 4 * SLODWORD(v4[5].klass) + 32) == 8)
      {
        if (!tutorialFlag)
        {
          tutorialFlag = 1;
        }
      }
      LOWORD(v4[4].klass) = 18;
      ++LODWORD(v4[5].klass);
      hdown_a_local = hdown_a;
      if (!hdown_on)
        goto LABEL_201;
      goto LABEL_189;
    case 0x12:
      if (tipsProcessCheck())
        goto LABEL_188;
      if (*(u32 *)(*((u64 *)v4[5].monitor + 21) + 4 * SLODWORD(v4[5].klass) + 32) != -1)
        goto LABEL_184;
LABEL_133:
      LOWORD(v4[4].klass) = 19;
      hdown_a_local = hdown_a;
      if (!hdown_on)
        goto LABEL_201;
      goto LABEL_189;
    case 0x13:
      sBtlEndWaitALL(0, 0);
      v11->aiwk->bWait2 = 0;
      BYTE5(v4[3].klass) = (wk->status2 & 0x800000) == 0;
      return 0;
    default:
      goto LABEL_188;
  }
}

// 0x1d9dd20
s32 sBtlEffectPreMenu(void) {
  Il2CppObject *ProcessData;
  Il2CppObject *v4;
  SBTLUNIT_WORK *v6;
  u32 *monitor;
  SBTLUNIT_WORK *v8;
  s64 v9;
  s64 v10;
  s64 v11;
  SBTLUNIT_WORK *v12;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 boss_eventID;
  SBTLUNIT_WORK *v17;
  s16 v22;
  s32 v23;
  SBATTLE_WORK *v25;
  s32 timedrawflg;
  SBTLUNIT_WORK *v29;
  s64 v30;
  SBTLUNIT_WORK *v31;
  s32 v32;
  u32 klass_high;
  SBTLUNIT_WORK *v34;
  SBTLUNIT_WORK *v35;
  s32 v37;
  u32 v39;
  SBTLUNIT_WORK *v40;
  SBTLUNIT_WORK *v41;
  s32 v45;
  SBTLUNIT_WORK *v47;
  s64 v48;
  SBTLUNIT_WORK *v49;
  u64 *v52;
  s64 v53;
  s64 v54;
  SBTLUNIT_WORK *v55;
  f32 ActionTime;
  S_CameraMoveDt *CamMovePtn;
  s16 v60;
  u64 *v61;
  s64 v62;
  s64 v63;
  SBATTLE_WORK *v66;
  u32 v67;
  SBTLUNIT_WORK *v69;
  SBTLUNIT_WORK *v70;
  u32 v71;
  s32 v72;
  s32 hdown_a_local;

  ProcessData = dds3GetProcessData(g_mainPID);
  v4 = ProcessData;
  v6 = NewSpecific(SBTLUNIT_WORK, 5u);
  monitor = v4[5].monitor;
  v8 = v6;
  v9 = monitor[6];
  v10 = monitor[7];
  if ((s32)v9 >= 1)
  {
    v11 = 0;
    v12 = &v6[0];
    do
    {
      UnitMng = wk->UnitMng;
      boss_eventID = wk->boss_eventID;
      v17 = sBtlSearchUnit_ID(UnitMng, (s32)v11 + boss_eventID);
      if (v17)
      {
        QueryInterface(v17, *(void **)&v8->vRotBfrCmb.x);
      }
      v12 = v17;
      ++v11;
      ++v12;
    }
    while (v9 != v11);
  }
  switch (LOWORD(v4[4].klass))
  {
    case 0:
      LOWORD(v4[4].klass) = 1;
      hdown_a = 0;
      hdown_on = 0;
      preMenuEvent = 1;
      goto LABEL_143;
    case 1:
      LOWORD(v4[3].monitor) = 60;
      v22 = 2;
      goto LABEL_139;
    case 2:
      v23 = (s16)LOWORD(v4[3].monitor)++;
      if (v23 < 61)
        goto LABEL_143;
      v22 = 3;
      goto LABEL_139;
    case 3:
      v25 = wk;
      timedrawflg = v25->timedrawflg;
      v25->status4 &= ~0x10u;
      v25 = wk;
      v25->timedrawflg = 0;
      v25->kaiwapaneldisp1 = 0;
      g_timedrawf = timedrawflg;
      *(u16 *)&v25->kaiwaflg = 1;
      if ((s32)v9 >= 1)
      {
        v29 = v8 + 4;
        v30 = v10;
        do
        {
          if ((u32)v10 == -1 || !v30)
          {
            v31 = v29;
            sBtlProcScript(v31);
          }
          --v30;
          ++v29;
          --v9;
        }
        while (v9);
      }
      LOWORD(v4[3].monitor) = 0;
      v22 = 4;
      goto LABEL_139;
    case 4:
      sBtlSetMode(2);
      WORD2(v4[4].monitor) = 0;
      LOWORD(v4[4].klass) = 16;
      goto LABEL_143;
    case 6:
      v32 = *(u32 *)(*((u64 *)v4[5].monitor + 11) + 4 * SWORD2(v4[4].monitor) + 32);
      if (v32 < 0)
      {
        v72 = WORD2(v4[4].monitor) + 1;
        WORD2(v4[4].monitor) = v72;
        if (v72 << 16 >= 196608)
        {
LABEL_141:
          v60 = 9;
LABEL_142:
          LOWORD(v4[4].klass) = v60;
          HIDWORD(v4[4].klass) = 0;
        }
      }
      else
      {
        fclStart1(v32, 0);
        LOWORD(v4[4].klass) = 7;
        ++WORD2(v4[4].monitor);
      }
      goto LABEL_143;
    case 7:
      if (Update())
        goto LABEL_143;
      if (SWORD2(v4[4].monitor) > 2)
        goto LABEL_141;
      v22 = 6;
      goto LABEL_139;
    case 8:
      if (!v4[2].monitor)
        goto LABEL_143;
      if (dds3GetProcessStat(&v4[2].monitor) != 3)
      {
        if (dds3GetProcessStat(&v4[2].monitor))
          goto LABEL_143;
      }
      v4[2].monitor = 0;
      LODWORD(v4[2].klass) = -1;
      goto LABEL_141;
    case 9:
      v22 = 10;
      goto LABEL_139;
    case 0xA:
      klass_high = HIDWORD(v4[4].klass);
      HIDWORD(v4[4].klass) = klass_high + 1;
      if (klass_high < 0x3D)
        goto LABEL_143;
      v22 = 11;
      goto LABEL_139;
    case 0xB:
      if ((s32)v9 >= 1)
      {
        v34 = v8 + 4;
        do
        {
          v35 = v34;
          v37 = *((u32 *)v4[5].monitor + 20);
          v34->vstatus |= 0x2000000u;
          sBtlSetMotion(v35, v37, 6, 0, 2);
          ++v34;
          --v9;
        }
        while (v9);
      }
      v55 = v8[4];
      ActionTime = sBtlGetActionTime(v55, 0);
      startf = ActionTime;
      sBtlSetMode(13);
      sBtlSetCmbBfrPos();
      CamMovePtn = sBtlGetCamMovePtn(cameraStartNo[*((s32 *)v4[5].monitor + 8)]);
      sBtlSetMove(CamMovePtn, 1);
      HIDWORD(v4[4].klass) = 0;
      LOWORD(v4[4].klass) = 13;
      goto LABEL_143;
    case 0xD:
      v39 = HIDWORD(v4[4].klass);
      if (v39 == 45)
      {
        dds3SetQuake(120, 0x258u);
        if ((s32)v9 >= 1)
        {
          v69 = v8 + 4;
          do
          {
            v70 = v69++;
            sBtlSetSkill_EffectData(v70, 1012, 0);
            --v9;
          }
          while (v9);
        }
        v39 = HIDWORD(v4[4].klass);
        if (v39 != 60)
        {
LABEL_67:
          HIDWORD(v4[4].klass) = v39 + 1;
          if (v39 < 0x70)
            goto LABEL_143;
          goto LABEL_136;
        }
      }
      else if (v39 != 60)
      {
        goto LABEL_67;
      }
      sBtlSetMoveEnd();
      v71 = HIDWORD(v4[4].klass);
      HIDWORD(v4[4].klass) = v71 + 1;
      if (v71 < 0x70)
        goto LABEL_143;
LABEL_136:
      sBtlSetMode(4);
      LOWORD(v4[3].monitor) = 0;
      v22 = 14;
LABEL_139:
      LOWORD(v4[4].klass) = v22;
LABEL_143:
      hdown_a_local = hdown_a;
      if (hdown_a_local >= 1)
      {
        if (hdown_a_local <= 2)
          hdown_a_local = 2;
        hdown_a = hdown_a_local - 2;
      }
      return 1;
    case 0xE:
      if ((s32)v9 >= 1)
      {
        v40 = v8 + 4;
        do
        {
          v41 = v40;
          v40->vstatus |= 0x2000000u;
          sBtlSetMotion(v41, 0, 6, 0, 2);
          ++v40;
          --v9;
        }
        while (v9);
      }
      v60 = 16;
      goto LABEL_142;
    case 0x10:
      if (HIDWORD(v4[4].klass) == 1)
      {
        BYTE6(v4[3].klass) = 1;
        if ((u32)(wk->encountno - 61) <= 0xFFFFFFFD)
        {
          PosReSet();
        }
        v45 = *((u32 *)v4[5].monitor + 10);
        if (v45 != start_on_esw && (s32)v9 >= 1)
        {
          v47 = v8 + 4;
          v48 = v9;
          do
          {
            v49 = v47;
            v47->vstatus |= 0x2000000u;
            sBtlSetMotion(v49, 0, 6, 0, 2);
            ++v47;
            --v48;
          }
          while (v48);
        }
      }
      if ((s32)v9 >= 1)
      {
        v61 = v8 + 4;
        v62 = v10;
        do
        {
          if ((u32)v10 == -1 || !v62)
          {
            v63 = *(u64 *)(*v61 + 920);
            *(u8 *)(*(u64 *)(*v61 + 912) + 16) = 1;
            *(u8 *)(v63 + 237) = 0;
          }
          --v62;
          ++v61;
          --v9;
        }
        while (v9);
      }
      v66 = wk;
      v67 = HIDWORD(v4[4].klass);
      if ((v66->scrFlag & 2) == 0 && v67 >= 0x5B)
      {
        v66 = wk;
        *(u16 *)&v66->kaiwaflg = 256;
        v66->kaiwapaneldisp1 = 1;
        v67 = 0;
        v66->timedrawflg = g_timedrawf;
        LOWORD(v4[4].klass) = 19;
      }
      HIDWORD(v4[4].klass) = v67 + 1;
      goto LABEL_143;
    case 0x13:
      sBtlEndWaitALL(0, 0);
      preMenuEvent = 0;
      if ((s32)v9 >= 1)
      {
        v52 = v8 + 4;
        v53 = v10;
        do
        {
          if ((u32)v10 == -1 || !v53)
          {
            v54 = *(u64 *)(*v52 + 920);
            *(u8 *)(*(u64 *)(*v52 + 912) + 16) = 0;
            *(u8 *)(v54 + 237) = 0;
          }
          --v53;
          ++v52;
          --v9;
        }
        while (v9);
      }
      BYTE5(v4[3].klass) = 1;
      return 0;
    default:
      goto LABEL_143;
  }
}

// 0x1d9e780
s32 sBtlTips(void) {
  Il2CppObject *ProcessData;
  Il2CppObject *v4;
  SBTLUNIT_WORK *v6;
  u32 *monitor;
  s64 *v8;
  s64 v9;
  s64 v10;
  s64 v11;
  SBTLUNIT_WORK *v12;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 boss_eventID;
  SBTLUNIT_WORK *v17;
  s32 result;
  s64 v23;
  s64 v24;
  SBATTLE_WORK *v26;
  s32 timedrawflg;
  s16 v30;
  s32 v31;
  s32 v32;
  s16 v33;
  s64 v34;
  s32 v35;
  s64 v36;
  s64 *v37;
  s64 v38;
  s64 v39;
  s64 v40;
  s64 v41;
  s64 v42;
  s64 v43;
  s64 v44;
  s64 v45;
  s64 *v46;
  s64 v47;
  s64 v48;
  s64 v49;
  s64 v50;
  s64 *v51;
  s64 v52;
  s64 v53;
  s64 v54;
  s64 v55;
  s64 v56;

  ProcessData = dds3GetProcessData(g_mainPID);
  v4 = ProcessData;
  v6 = NewSpecific(SBTLUNIT_WORK, 5u);
  monitor = v4[5].monitor;
  v8 = v6;
  v9 = monitor[6];
  v10 = monitor[7];
  if ((s32)v9 >= 1)
  {
    v11 = 0;
    v12 = &v6[0];
    do
    {
      UnitMng = wk->UnitMng;
      boss_eventID = wk->boss_eventID;
      v17 = sBtlSearchUnit_ID(UnitMng, (s32)v11 + boss_eventID);
      if (v17)
      {
        QueryInterface(v17, *(void **)(*v8 + 64));
      }
      v12 = v17;
      ++v11;
      ++v12;
    }
    while (v9 != v11);
  }
  result = 1;
  switch (LOWORD(v4[4].klass))
  {
    case 0:
      WORD2(v4[4].monitor) = 0;
      preMenuEvent = 1;
      LOWORD(v4[4].klass) = 3;
      return 1;
    case 1:
    case 2:
    case 5:
      return result;
    case 3:
      v26 = wk;
      timedrawflg = v26->timedrawflg;
      v26->status4 &= ~0x10u;
      v26 = wk;
      v26->timedrawflg = 0;
      g_timedrawf = timedrawflg;
      *(u16 *)&v26->kaiwapaneldisp0 = 0;
      LOWORD(v4[3].monitor) = 0;
      v30 = 4;
      goto LABEL_41;
    case 4:
      sBtlSetMode(2);
      WORD2(v4[4].monitor) = 0;
      LOWORD(v4[4].klass) = 6;
      v31 = *(u32 *)(*((u64 *)v4[5].monitor + 11) + 32);
      v32 = v31;
      goto LABEL_47;
    case 6:
      if (tipsProcessCheck())
        return 1;
      v33 = WORD2(v4[4].monitor) + 1;
      v34 = *((u64 *)v4[5].monitor + 11);
      WORD2(v4[4].monitor) = v33;
      v35 = *(u32 *)(v34 + 4 * v33 + 32);
      if (v35 == -1)
      {
        v30 = 19;
LABEL_41:
        LOWORD(v4[4].klass) = v30;
        return 1;
      }
      else
      {
        v32 = v35;
LABEL_47:
        tipsTIPSStart(v32);
        return 1;
      }
    default:
      if (LOWORD(v4[4].klass) != 19)
        return 1;
      sBtlEndWaitALL(0, 0);
      preMenuEvent = 0;
      if ((s32)v9 < 1)
        goto LABEL_67;
      if ((u32)v10 == -1)
      {
        if ((u32)v9 >= 2)
        {
          v36 = (u32)v9 & 0xFFFFFFFE;
          v37 = v8 + 5;
          v38 = v36;
          do
          {
            v39 = *(v37 - 1);
            v40 = *v37;
            v37 += 2;
            v38 -= 2;
            v41 = *(u64 *)(v39 + 912);
            v42 = *(u64 *)(v40 + 912);
            v43 = *(u64 *)(v39 + 920);
            v44 = *(u64 *)(v40 + 920);
            *(u8 *)(v41 + 16) = 0;
            *(u8 *)(v42 + 16) = 0;
            *(u8 *)(v43 + 237) = 0;
            *(u8 *)(v44 + 237) = 0;
          }
          while (v38);
          if (v36 == v9)
            goto LABEL_67;
        }
        else
        {
          v36 = 0;
        }
        v45 = ~v36;
        if ((v9 & 1) != 0)
        {
          v46 = &v8[v36];
          v36 |= 1u;
          v47 = v46[4];
          v48 = *(u64 *)(v47 + 912);
          v49 = *(u64 *)(v47 + 920);
          *(u8 *)(v48 + 16) = 0;
          *(u8 *)(v49 + 237) = 0;
        }
        if (v45 + v9)
        {
          v50 = v9 - v36;
          v51 = &v8[v36 + 5];
          do
          {
            v52 = *(v51 - 1);
            v53 = *v51;
            v50 -= 2;
            v51 += 2;
            v54 = *(u64 *)(v52 + 912);
            v55 = *(u64 *)(v53 + 912);
            *(u8 *)(*(u64 *)(v52 + 920) + 237) = 0;
            v56 = *(u64 *)(v53 + 920);
            *(u8 *)(v54 + 16) = 0;
            *(u8 *)(v55 + 16) = 0;
            *(u8 *)(v56 + 237) = 0;
          }
          while (v50);
        }
      }
      else
      {
        v23 = &v8[(u32)v10 + 4];
        do
        {
          if (!v10)
          {
            v24 = *(u64 *)(*(u64 *)v23 + 920);
            *(u8 *)(*(u64 *)(*(u64 *)v23 + 912) + 16) = 0;
            *(u8 *)(v24 + 237) = 0;
          }
          --v10;
          --v9;
        }
        while (v9);
      }
LABEL_67:
      BYTE5(v4[3].klass) = 1;
      return 0;
  }
}

// 0x1dcc9a0
s32 BattleRestart_Effect(void) {
  Il2CppObject *ProcessData;
  Il2CppObject *v4;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 boss_eventID;
  SBTLUNIT_WORK *v10;
  SBTLUNIT_WORK *v11;
  SBATTLE_WORK *v15;
  s32 timedrawflg;
  s32 v19;
  s16 v20;
  s32 v21;
  u32 klass_high;
  s32 v24;
  f32 ActionTime;
  S_CameraMoveDt *CamMovePtn;
  u32 v29;
  s16 v31;
  u32 v32;
  SBATTLE_WORK *v35;
  u32 v36;
  s32 v39;

  ProcessData = dds3GetProcessData(g_mainPID);
  v4 = ProcessData;
  UnitMng = wk->UnitMng;
  boss_eventID = wk->boss_eventID;
  v10 = sBtlSearchUnit_ID(UnitMng, boss_eventID);
  v11 = sBtlSearchUnit_ID(wk->UnitMng, wk->playerID);
  switch (LOWORD(v4[4].klass))
  {
    case 0:
      v11->flg &= ~0x20u;
      PosSet();
      CameraPosSet(1);
      CameraSet();
      v15 = wk;
      v15->kaiwapaneldisp1 = 0;
      timedrawflg = v15->timedrawflg;
      v15->timedrawflg = 0;
      g_timedrawf = timedrawflg;
      *(u16 *)&v15->kaiwaflg = 1;
      sBtlStatusBitOn(v10, 0x10u);
      LOWORD(v4[3].monitor) = 0;
      dds3FadeIn2(0x1Eu);
      LOWORD(v4[4].klass) = 1;
      return 1;
    case 1:
      v19 = (s16)LOWORD(v4[3].monitor)++;
      if (v19 < 61)
        return 1;
      v20 = 2;
      WORD2(v4[4].monitor) = 0;
      goto LABEL_76;
    case 2:
      v21 = *(u32 *)(*((u64 *)v4[5].monitor + 20) + 4 * SWORD2(v4[4].monitor) + 32);
      if ((v21 & 0x80000000) == 0)
      {
        fclStart1(v21, 0);
        ++WORD2(v4[4].monitor);
        v20 = 3;
        goto LABEL_76;
      }
      v39 = WORD2(v4[4].monitor) + 1;
      WORD2(v4[4].monitor) = v39;
      if (v39 << 16 < 196608)
        return 1;
LABEL_73:
      v31 = 4;
LABEL_74:
      LOWORD(v4[4].klass) = v31;
      HIDWORD(v4[4].klass) = 0;
      return 1;
    case 3:
      if (Update())
        return 1;
      if (SWORD2(v4[4].monitor) > 2)
        goto LABEL_73;
      v20 = 2;
      goto LABEL_76;
    case 4:
      klass_high = HIDWORD(v4[4].klass);
      HIDWORD(v4[4].klass) = klass_high + 1;
      if (klass_high < 0x5B)
        return 1;
      v20 = 5;
      goto LABEL_76;
    case 5:
      v10->vstatus |= 0x2000000u;
      v24 = *((u32 *)v4[5].monitor + 20);
      sBtlSetMotion(v10, v24, 6, 0, 2);
      ActionTime = sBtlGetActionTime(v10, 0);
      startf = ActionTime;
      sBtlSetMode(13);
      sBtlSetCmbBfrPos();
      CamMovePtn = sBtlGetCamMovePtn(cameraStartNo[*((s32 *)v4[5].monitor + 8)]);
      sBtlSetMove(CamMovePtn, 1);
      v20 = 7;
      HIDWORD(v4[4].klass) = 0;
      goto LABEL_76;
    case 7:
      v29 = HIDWORD(v4[4].klass);
      if (v29 == 45)
      {
        dds3SetQuake(120, 0x258u);
        sBtlSetSkill_EffectData(v10, 1012, 0);
        v29 = HIDWORD(v4[4].klass);
        if (v29 != 60)
        {
LABEL_45:
          HIDWORD(v4[4].klass) = v29 + 1;
          if (v29 >= 0x70)
            goto LABEL_65;
          return 1;
        }
      }
      else if (v29 != 60)
      {
        goto LABEL_45;
      }
      sBtlSetMoveEnd();
      v36 = HIDWORD(v4[4].klass);
      HIDWORD(v4[4].klass) = v36 + 1;
      if (v36 < 0x70)
        return 1;
LABEL_65:
      sBtlSetMode(2);
      LOWORD(v4[3].monitor) = 0;
      wk->camSlpMode = 2;
      v20 = 8;
LABEL_76:
      LOWORD(v4[4].klass) = v20;
      return 1;
    case 8:
      v10->vstatus |= 0x2000000u;
      sBtlSetMotion(v10, 0, 6, 0, 2);
      v31 = 10;
      goto LABEL_74;
    case 0xA:
      v32 = HIDWORD(v4[4].klass);
      if (v32 == 45)
      {
        BYTE6(v4[3].klass) = 1;
        PosReSet();
        v35 = wk;
        *(u16 *)&v35->kaiwaflg = 256;
        v35->kaiwapaneldisp1 = 1;
        v35->timedrawflg = g_timedrawf;
        v32 = HIDWORD(v4[4].klass);
      }
      HIDWORD(v4[4].klass) = v32 + 1;
      if (v32 < 0x5B)
        return 1;
      v31 = 11;
      goto LABEL_74;
    case 0xB:
      sBtlEndWaitALL(0, 0);
      v10->aiwk->bWait2 = 0;
      return 0;
    default:
      return 1;
  }
}

// 0x1dcd0e0
s32 BattleMag_Effect(void) {
  Il2CppObject *ProcessData;
  Il2CppObject *v4;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 boss_eventID;
  SBTLUNIT_WORK *v10;
  SBTLUNIT_WORK *v11;
  s16 v13;
  u32 klass_high;
  s64 v16;
  s32 v17;
  s32 vstatus;
  u32 v20;
  u32 v21;
  s32 hdown_wait_local;
  s32 monitor_high;
  s64 v28;
  s32 v29;
  s32 v30;
  s16 v31;
  s32 v32;
  u32 v33;
  S_CameraMoveDt *v34;
  u32 v36;
  s32 v37;
  SBATTLE_WORK *v39;
  s64 v41;
  SBTLUNIT_LISTWORK *v42;
  SBTLUNIT_WORK *pUnit;
  s32 v44;
  SBATTLE_WORK *v48;
  u32 v49;
  SBATTLE_WORK *v54;
  s32 timedrawflg;
  S_CameraMoveDt *CamMovePtn;
  u32 v58;
  SBTLUNIT_WORK *Nakama;
  SBTLUNIT_WORK *v60;
  s32 v63;
  u32 v69;
  s32 v71;
  s32 v72;
  s32 hdown_a_local;
  s64 v74;
  s32 v75;

  ProcessData = dds3GetProcessData(g_mainPID);
  v4 = ProcessData;
  UnitMng = wk->UnitMng;
  boss_eventID = wk->boss_eventID;
  v10 = sBtlSearchUnit_ID(UnitMng, boss_eventID);
  v11 = sBtlSearchUnit_ID(wk->UnitMng, wk->playerID);
  if (!HIWORD(v4[4].monitor))
    goto LABEL_22;
  if (!_CheckMotionEnd(v10))
    goto LABEL_22;
  v10->vstatus |= 0x2000000u;
  sBtlSetMotion(v10, 2, 6, 0, 2);
  HIWORD(v4[4].monitor) = 0;
LABEL_22:
  switch (LOWORD(v4[4].klass))
  {
    case 0:
      v13 = 1;
      goto LABEL_180;
    case 1:
      sBtlBgnWaitALL(0);
      sBtlStatusBitOn(v10, 0x10u);
      v10->aiwk->bWait2 = 1;
      sBtlSetSkill_EffectData(v10, 1012, 0);
      HIDWORD(v4[4].klass) = 0;
      v13 = 2;
      goto LABEL_180;
    case 2:
      klass_high = HIDWORD(v4[4].klass);
      if (klass_high == 66)
      {
        sBtlStatusBitOn(v10, 0x10u);
        PosSet();
        klass_high = HIDWORD(v4[4].klass);
        if (klass_high != 68)
        {
LABEL_33:
          HIDWORD(v4[4].klass) = klass_high + 1;
          if (klass_high < 0x79)
            goto LABEL_181;
          goto LABEL_137;
        }
      }
      else if (klass_high != 68)
      {
        goto LABEL_33;
      }
      CameraPosSet(1);
      CameraSet();
      if ((v10->status & 0x80000000) != 0)
      {
        g_bosseventhpflg = 1;
LABEL_133:
        v54 = wk;
        timedrawflg = v54->timedrawflg;
        goto LABEL_134;
      }
      else
      {
        goto LABEL_133;
      }
      v54 = wk;
      timedrawflg = v54->timedrawflg;
LABEL_134:
      v54->timedrawflg = 0;
      g_timedrawf = timedrawflg;
      v54->kaiwaflg = 2;
      v54->kaiwapaneldisp1 = 0;
      sBtlSetMode(13);
      CamMovePtn = sBtlGetCamMovePtn(cameraMagNo[*((s32 *)v4[5].monitor + 8)]);
      sBtlSetMove(CamMovePtn, 1);
      v11->vstatus |= 0x1000u;
      v58 = HIDWORD(v4[4].klass);
      HIDWORD(v4[4].klass) = v58 + 1;
      if (v58 >= 0x79)
      {
LABEL_137:
        v13 = 3;
        goto LABEL_180;
      }
      goto LABEL_181;
    case 3:
      v10->vstatus |= 0x2000000u;
      sBtlSetMotion(v10, 14, 4, 0, 0);
      v16 = *((s32 *)v4[5].monitor + 8);
      if ((u32)v16 > 8)
        v17 = 1277;
      else
        v17 = dword_3E632EC[v16];
      sBtlSetSkill_EffectData(v10, v17, 0);
      sBtlGetUnitHelperPos(v10, 0);
      if (sdfModelGetMarkPos(v10->hEveUnit->Model->modelRoot, 1))
      {
        goto LABEL_166;
      }
      else
      {
        sdfModelGetMarkPos(v10->hEveUnit->Model->modelRoot, 0);
LABEL_166:
        goto LABEL_167;
      }
LABEL_167:
      dds3SetQuake(120, 0x3E8u);
      HIDWORD(v4[4].klass) = 0;
      LOWORD(v4[4].klass) = 4;
      HIWORD(v4[4].monitor) = 1;
      goto LABEL_181;
    case 4:
      if (!_CheckMotionEnd(v10))
      {
        v69 = HIDWORD(v4[4].klass);
        HIDWORD(v4[4].klass) = v69 + 1;
        if (v69 < 0x97)
          goto LABEL_181;
        goto LABEL_179;
      }
      vstatus = v10->vstatus;
      HIWORD(v4[4].monitor) = 0;
      v10->vstatus = vstatus | 0x2000000;
      sBtlSetMotion(v10, 2, 6, 0, 2);
      LOWORD(v4[4].klass) = 5;
      v20 = HIDWORD(v4[4].klass);
      HIDWORD(v4[4].klass) = v20 + 1;
      if (v20 >= 0x97)
      {
LABEL_179:
        v13 = 5;
        goto LABEL_180;
      }
LABEL_181:
      if (hdown_on)
        v71 = 0;
      else
        v71 = 58;
      if (v71 != 58)
      {
        v72 = hdown_a + 2;
        if (v72 >= 80)
          v72 = 80;
LABEL_191:
        hdown_a = v72;
        return 1;
      }
      hdown_a_local = hdown_a;
      if (hdown_a_local >= 1)
      {
        if (hdown_a_local <= 2)
          hdown_a_local = 2;
        v72 = hdown_a_local - 2;
        goto LABEL_191;
      }
      return 1;
    case 5:
      v21 = HIDWORD(v4[4].klass);
      HIDWORD(v4[4].klass) = v21 + 1;
      if (v21 < 0x97)
        goto LABEL_181;
      sBtlEndWaitALL(0, 0);
      WORD2(v4[4].monitor) = 0;
      wk->kaiwapaneldisp0 = 0;
      v13 = 7;
      goto LABEL_180;
    case 6:
      hdown_wait_local = hdown_wait - 1;
      hdown_wait = hdown_wait_local;
      if (hdown_on && hdown_wait_local == 4)
      {
        SE(27);
        hdown_wait_local = hdown_wait;
      }
      if ((hdown_wait_local & 0x80000000) == 0)
        goto LABEL_181;
      v13 = 7;
      goto LABEL_180;
    case 7:
      monitor_high = HIDWORD(v4[3].monitor);
      switch (monitor_high)
      {
        case 3:
          v74 = *((u64 *)v4[5].monitor + 14);
          break;
        case 2:
          v74 = *((u64 *)v4[5].monitor + 13);
          break;
        case 1:
          v28 = SWORD2(v4[4].monitor);
          v29 = *(u32 *)(*((u64 *)v4[5].monitor + 12) + 4 * v28 + 32);
          if ((v29 & 0x80000000) == 0)
          {
            fclStart1(v29, 0);
            ++WORD2(v4[4].monitor);
            v13 = 8;
            goto LABEL_180;
          }
          goto LABEL_200;
        default:
          goto LABEL_181;
      }
      v28 = SWORD2(v4[4].monitor);
      v75 = *(u32 *)(v74 + 4 * v28 + 32);
      if ((v75 & 0x80000000) == 0)
      {
        fclStart1(v75, 0);
        LOWORD(v4[4].klass) = 8;
        ++WORD2(v4[4].monitor);
        goto LABEL_181;
      }
LABEL_200:
      v32 = (u16)v28 + 1;
      WORD2(v4[4].monitor) = v32;
      if (v32 << 16 >= 196608)
      {
        HIDWORD(v4[4].klass) = 0;
        LOWORD(v4[4].klass) = 10;
      }
      v32 = (u16)v32;
      goto LABEL_210;
    case 8:
      if (Update())
        goto LABEL_181;
      v30 = HIDWORD(v4[3].monitor);
      if (v30 != 1 && v30 != 2 && v30 != 3)
        goto LABEL_75;
      if (SWORD2(v4[4].monitor) <= 2)
      {
        v32 = WORD2(v4[4].monitor);
        LOWORD(v4[4].klass) = 7;
        if (hdown_on)
        {
          LOWORD(v4[4].klass) = 6;
          *(u64 *)&hdown_on = 0x3200000000LL;
        }
LABEL_210:
        if (v32 == 1)
        {
          v10->vstatus |= 0x2000000u;
          sBtlSetMotion(v10, 0, 6, 0, 2);
        }
      }
      else
      {
        v31 = 10;
LABEL_124:
        LOWORD(v4[4].klass) = v31;
        HIDWORD(v4[4].klass) = 0;
      }
      goto LABEL_181;
    case 9:
      if (!v4[2].monitor)
        goto LABEL_181;
      if (dds3GetProcessStat(&v4[2].monitor) != 3)
      {
        if (dds3GetProcessStat(&v4[2].monitor))
          goto LABEL_181;
      }
      v4[2].monitor = 0;
      LODWORD(v4[2].klass) = -1;
      HIDWORD(v4[4].klass) = 0;
      LOWORD(v4[4].klass) = 10;
LABEL_75:
      v32 = WORD2(v4[4].monitor);
      goto LABEL_210;
    case 0xA:
      v33 = HIDWORD(v4[4].klass);
      HIDWORD(v4[4].klass) = v33 + 1;
      if (v33 < 0x1F)
        goto LABEL_181;
      v13 = 11;
      goto LABEL_180;
    case 0xB:
      if (HIDWORD(v4[3].monitor) == 2 && *((u32 *)v4[5].monitor + 12) == 2)
      {
        CameraPosSet(1);
        CameraSet();
        sBtlSetBossMode(5);
        sBtlSetMode(13);
        v34 = sBtlGetCamMovePtn(139);
        sBtlSetMove(v34, 1);
        v11->vstatus &= ~0x1000u;
        sBtlStatusBitOn(v10, 0x10u);
        LOWORD(v4[3].monitor) = 0;
        sBtlBgnWaitALL(0);
        HIDWORD(v4[3].monitor) = 8;
        v13 = 4;
      }
      else
      {
        v10->vstatus |= 0x2000000u;
        if ((wk->status2 & 0x40000000) == 0)
        {
          v63 = *((u32 *)v4[5].monitor + 20);
          sBtlSetMotion(v10, v63, 6, 0, 2);
          startf = sBtlGetActionTime(v10, 0);
        }
        HIDWORD(v4[4].klass) = 0;
        v13 = 13;
      }
      goto LABEL_180;
    case 0xD:
      v36 = HIDWORD(v4[4].klass);
      if (v36 == 55)
      {
        dds3SetQuake(150, 0x320u);
        v36 = HIDWORD(v4[4].klass);
      }
      HIDWORD(v4[4].klass) = v36 + 1;
      if (v36 < 0x3D)
        goto LABEL_181;
      dds3FadeOut(0xFFu, 0xFFu, 0xFFu, 0x3Cu);
      LOWORD(v4[3].monitor) = 0;
      v13 = 14;
      goto LABEL_180;
    case 0xE:
      v37 = (s16)LOWORD(v4[3].monitor)++;
      if (v37 < 61)
        goto LABEL_181;
      v13 = 15;
      goto LABEL_180;
    case 0xF:
      v39 = wk;
      v41 = 0;
      v39->timedrawflg = g_timedrawf;
      while (2)
      {
        v42 = wk->UnitMng;
        if (v41 >= v42->number)
        {
          Nakama = sBtlGetNakama(0);
          if (Nakama)
            Nakama->vstatus &= ~0x1000u;
          v60 = sBtlGetNakama(1);
          if (v60)
            v60->vstatus &= ~0x1000u;
          sBtlSetMode(2);
          BYTE6(v4[3].klass) = 1;
          PosReSet();
          LOWORD(v4[3].monitor) = 0;
          dds3FadeIn2(0x1Eu);
          dds3SetQuake(60, 0x96u);
          v13 = 16;
LABEL_180:
          LOWORD(v4[4].klass) = v13;
          goto LABEL_181;
        }
        pUnit = v42->pUnitL[v41]->pUnit;
        if (!pUnit)
          goto LABEL_102;
        goto LABEL_9001;
        if (!pUnit)
        {
LABEL_102:
          ++v41;
          continue;
        }
LABEL_9001:
        break;
      }
      if (pUnit != wk->pCamSklUser2 && !pUnit->bOldDispOff)
        pUnit->vstatus &= ~0x1000u;
      goto LABEL_102;
    case 0x10:
      v44 = (s16)LOWORD(v4[3].monitor)++;
      if (v44 >= 31)
      {
        HIDWORD(v4[4].klass) = 0;
        LOWORD(v4[4].klass) = 17;
        v48 = wk;
        *(u16 *)&v48->kaiwaflg = 256;
        v48->kaiwapaneldisp1 = 1;
        if (g_bosseventhpflg)
          v10->status |= 0x80000000;
      }
      goto LABEL_181;
    case 0x11:
      v49 = HIDWORD(v4[4].klass);
      HIDWORD(v4[4].klass) = v49 + 1;
      if (v49 < 0x1F)
        goto LABEL_181;
      v31 = 18;
      goto LABEL_124;
    case 0x12:
      v10->aiwk->bWait2 = 0;
      sBtlStatusBitOff(v10, 0xFFFFFFEF);
      v10->vstatus &= ~0x2000000u;
      return 0;
    default:
      goto LABEL_181;
  }
}

// 0x1dce0b0
s32 BattleDead_Effect(void) {
  Il2CppObject *ProcessData;
  Il2CppObject *v4;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 boss_eventID;
  SBTLUNIT_WORK *v10;
  SBTLUNIT_WORK *v11;
  s32 result;
  s32 klass_high;
  u32 v15;
  u32 v16;
  s32 v17;
  u32 v18;
  s16 v19;
  S_CameraMoveDt *CamMovePtn;
  SBATTLE_WORK *v25;
  bool v26;
  s32 vstatus;
  s64 v28;
  s32 v29;
  u32 v30;
  u32 v31;
  s16 v32;
  u32 v33;
  char dead_on;
  s32 v35;
  SBATTLE_WORK *v39;
  SBATTLE_WORK *v42;
  s32 v43;
  u32 v47;
  s32 v48;
  bool v49;
  SBATTLE_WORK *v51;
  SBTLUNIT_WORK *v54;
  SBATTLE_WORK *v56;
  s32 ListID;
  SBTLUNIT_WORK *v58;
  TYPE_BOSS_NML_EVENT *v59;

  ProcessData = dds3GetProcessData(g_mainPID);
  v4 = ProcessData;
  UnitMng = wk->UnitMng;
  boss_eventID = wk->boss_eventID;
  v10 = sBtlSearchUnit_ID(UnitMng, boss_eventID);
  v11 = sBtlSearchUnit_ID(wk->UnitMng, wk->playerID);
  switch (LOWORD(v4[4].klass))
  {
    case 0:
      LOWORD(v4[4].klass) = 1;
      return 1;
    case 1:
      v10->vstatus = v10->vstatus & 0xFDFFEFFF | 0x2000000;
      sBtlSetMotion(v10, 14, 6, 0, 2);
      sBtlSetSkill_EffectData(v11, 1012, 0);
      HIDWORD(v4[4].klass) = 0;
      LOWORD(v4[4].klass) = 2;
      return 1;
    case 2:
      klass_high = HIDWORD(v4[4].klass);
      if (klass_high == 66)
      {
        PosSet();
        if (*((u32 *)v4[5].monitor + 18))
        {
          sBtlPlayDeadVoice(v10);
        }
        if (HIDWORD(v4[4].klass) != 67)
        {
LABEL_27:
          v15 = HIDWORD(v4[4].klass);
          if (v15 == 70)
            goto LABEL_28;
          goto LABEL_127;
        }
      }
      else if (klass_high != 67)
      {
        goto LABEL_27;
      }
      v10->vstatus |= 0x2000000u;
      sBtlSetMotion(v10, 2, 6, 0, 2);
      v42 = wk;
      *(u16 *)&v42->kaiwaflg = 1;
      v42->timedrawflg = 0;
      v42->kaiwapaneldisp1 = 0;
      if ((u32)(*((u32 *)v4[5].monitor + 8) - 7) >= 0xFFFFFFFD)
        v43 = 240;
      else
        v43 = 120;
      dds3SetQuake(v43, 0x514u);
      v15 = HIDWORD(v4[4].klass);
      if (v15 == 70)
      {
LABEL_28:
        CameraPosSet(1);
        CameraSet();
        v16 = HIDWORD(v4[4].klass);
        HIDWORD(v4[4].klass) = v16 + 1;
        if (v16 < 0x79)
          return 1;
LABEL_128:
        WORD2(v4[4].monitor) = 0;
        goto LABEL_129;
      }
LABEL_127:
      HIDWORD(v4[4].klass) = v15 + 1;
      if (v15 < 0x79)
        return 1;
      goto LABEL_128;
    case 3:
      v17 = *(u32 *)(*((u64 *)v4[5].monitor + 15) + 4 * SWORD2(v4[4].monitor) + 32);
      if ((v17 & 0x80000000) == 0)
      {
        fclStart1(v17, 0);
        LOWORD(v4[4].klass) = 4;
        ++WORD2(v4[4].monitor);
        return 1;
      }
      v48 = WORD2(v4[4].monitor) + 1;
      WORD2(v4[4].monitor) = v48;
      if (v48 << 16 < 196608)
        return 1;
LABEL_151:
      v32 = 6;
LABEL_152:
      LOWORD(v4[4].klass) = v32;
      HIDWORD(v4[4].klass) = 0;
      return 1;
    case 4:
      if (Update())
        return 1;
      if (SWORD2(v4[4].monitor) > 2)
        goto LABEL_151;
LABEL_129:
      v19 = 3;
      goto LABEL_169;
    case 5:
      if (!v4[2].monitor)
        return 1;
      if (dds3GetProcessStat(&v4[2].monitor) != 3)
      {
        if (dds3GetProcessStat(&v4[2].monitor))
          return 1;
      }
      v4[2].monitor = 0;
      LODWORD(v4[2].klass) = -1;
      goto LABEL_151;
    case 6:
      v18 = HIDWORD(v4[4].klass);
      HIDWORD(v4[4].klass) = v18 + 1;
      if (v18 < 0x1F)
        return 1;
      v19 = 7;
      goto LABEL_169;
    case 7:
      if ((u32)(*((u32 *)v4[5].monitor + 8) - 7) >= 0xFFFFFFFD)
      {
        dds3SetQuake(350, 0x12Cu);
      }
      sBtlSetMode(13);
      sBtlSetCmbBfrPos();
      CamMovePtn = sBtlGetCamMovePtn(cameraDeadNo[*((s32 *)v4[5].monitor + 8)]);
      sBtlSetMove(CamMovePtn, 1);
      v25 = wk;
      v11->vstatus |= 0x2000000u;
      v25->bNoEndCam = 1;
      sBtlSetMotion(v11, 12, 4, 6, 0);
      v11->flg |= 0x20u;
      v19 = 8;
      goto LABEL_169;
    case 8:
      v26 = _CheckMotionEnd(v11);
      result = 1;
      if (!v26)
        return result;
      goto LABEL_62;
      if (v49)
      {
LABEL_62:
        vstatus = v11->vstatus;
        v10->no_dead_se = 1;
        v11->vstatus = vstatus & 0xFDFFFFFF;
        LOWORD(v4[4].klass) = 9;
      }
      return result;
    case 9:
      sBtlBgnWaitALL(0);
      sBtlStatusBitOn(v10, 0x10u);
      v10->aiwk->bWait2 = 1;
      v10->vstatus |= 0x2000000u;
      sBtlSetMotion(v10, 13, 4, 0, 0);
      v28 = *((s32 *)v4[5].monitor + 8);
      if ((u32)v28 > 8)
        v29 = 1277;
      else
        v29 = dword_3E632EC[v28];
      sBtlSetSkill_EffectData(v10, v29, 0);
      sBtlGetUnitHelperPos(v10, 0);
      if (sdfModelGetMarkPos(v10->hEveUnit->Model->modelRoot, 1))
      {
        goto LABEL_138;
      }
      else
      {
        sdfModelGetMarkPos(v10->hEveUnit->Model->modelRoot, 0);
LABEL_138:
        goto LABEL_139;
      }
LABEL_139:
      if ((u32)(*((u32 *)v4[5].monitor + 8) - 7) >= 0xFFFFFFFD)
        v47 = 800;
      else
        v47 = 1300;
      dds3SetQuake(240, v47);
      HIDWORD(v4[4].klass) = 0;
      v19 = 10;
LABEL_169:
      LOWORD(v4[4].klass) = v19;
      return 1;
    case 0xA:
      v30 = HIDWORD(v4[4].klass);
      HIDWORD(v4[4].klass) = v30 + 1;
      if (v30 < 0x29)
        return 1;
      v19 = 11;
      goto LABEL_169;
    case 0xB:
      HIDWORD(v4[4].klass) = 0;
      v19 = 12;
      goto LABEL_169;
    case 0xC:
      v31 = HIDWORD(v4[4].klass);
      HIDWORD(v4[4].klass) = v31 + 1;
      if (v31 <= 0x14A)
      {
        if (!_CheckMotionEnd(v11))
          return 1;
      }
      sBtlSetSkill_EffectData(v10, 1012, 0);
      dds3SetQuake(160, 0x3E8u);
      v32 = 13;
      goto LABEL_152;
    case 0xD:
      v33 = HIDWORD(v4[4].klass);
      if (v33 == 67)
      {
        sBtlCheckDrop_Normal(v10);
        v10->actwk->action_flg = 0;
        sBtlSetAction(v10, 10, 0);
        if (v10->dead_on >= 0)
          dead_on = v10->dead_on;
        else
          dead_on = *((u32 *)v4[5].monitor + 14);
        if ((dead_on & 0x10) == 0)
        {
          sBtlSetFade(v10, 2, 0, 0, 4);
        }
        if ((dead_on & 2) != 0)
        {
          dds3FadeOut(0xFFu, 0xFFu, 0xFFu, 1u);
        }
        v33 = HIDWORD(v4[4].klass);
      }
      HIDWORD(v4[4].klass) = v33 + 1;
      if (v33 < 0xBE)
        return 1;
      v35 = *((u32 *)v4[5].monitor + 14);
      if (v10 && v10->dead_on >= 0)
        LOBYTE(v35) = v10->dead_on;
      if ((v35 & 2) != 0)
      {
        v51 = wk;
        v51->bNoEndCam = 0;
        sBtlSetBossMode(0);
        wk->bosseveloadflg = 1;
        v54 = sBtlSetEncountData4(0, 0, 0, 0);
        summonwk = v54;
        v56 = wk;
        ListID = summonwk->ListID;
        v56->boss_devilID = 0;
        v56->boss_eventID = ListID;
        summonwk->para->now->hp /= 2;
        *(u16 *)summonwk->aMagOut = 257;
        sBtlStatusBitOff(summonwk, 0xFFFFFFEF);
        summonwk->vstatus |= 0x1000u;
        sBtlBgnWaitALL(0);
        v58 = summonwk;
        v59 = arrBossEveTable[sBtlCheck(v58, 2, 0)];
        v4[5].monitor = v59;
        v19 = 14;
      }
      else
      {
        HIDWORD(v4[4].klass) = 0;
        v19 = 15;
      }
      goto LABEL_169;
    case 0xE:
      if (summonwk->mode != 8)
        return 1;
      LOWORD(v4[4].klass) = 0;
      wk->bosseveloadflg = 0;
      HIDWORD(v4[3].monitor) = 9;
      return 1;
    case 0xF:
      sBtlEndWaitALL(0, 0);
      if (!sBtlCheckUnit_Exec())
        return 1;
      v39 = wk;
      *(u16 *)&v39->kaiwaflg = 256;
      v39->kaiwapaneldisp1 = 1;
      *(int8x8_t *)&v39->status = vorr_s8(*(int8x8_t *)&v39->status, (int8x8_t)0x1000000000000008LL);
      v39->endcnt = 0;
      sBtlCheckBattleWin();
      sBtlGetAutoSkillPoint();
      sBtlGetChuuseiPoint();
      sBtlSetEndData();
      return 0;
    default:
      return 1;
  }
}

// 0x1dcef20
s32 BattleTime_Effect(void) {
  Il2CppObject *ProcessData;
  Il2CppObject *v4;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 boss_eventID;
  SBTLUNIT_WORK *v10;
  SBTLUNIT_WORK *v11;
  SBTLUNIT_WORK *v13;
  u32 klass_high;
  u32 v16;
  s32 v17;
  s16 v18;
  u32 v19;
  S_CameraMoveDt *CamMovePtn;
  s16 v23;
  u32 v24;
  u32 v25;
  u32 v26;
  s32 v27;
  SBATTLE_WORK *v29;
  s64 v30;
  s32 v32;
  SBATTLE_WORK *v33;

  ProcessData = dds3GetProcessData(g_mainPID);
  v4 = ProcessData;
  UnitMng = wk->UnitMng;
  boss_eventID = wk->boss_eventID;
  v10 = sBtlSearchUnit_ID(UnitMng, boss_eventID);
  v11 = sBtlSearchUnit_ID(wk->UnitMng, wk->playerID);
  switch (LOWORD(v4[4].klass))
  {
    case 0:
      LOWORD(v4[4].klass) = 1;
      return 1;
    case 1:
      v13 = v11;
      v10->vstatus |= 0x2000000u;
      sBtlSetMotion(v10, 0, 6, 0, 2);
      sBtlSetSkill_EffectData(v13, 1012, 0);
      HIDWORD(v4[4].klass) = 0;
      LOWORD(v4[4].klass) = 2;
      return 1;
    case 2:
      klass_high = HIDWORD(v4[4].klass);
      if (klass_high == 66)
      {
        PosSet();
        klass_high = HIDWORD(v4[4].klass);
        if (klass_high != 67)
        {
LABEL_23:
          if (klass_high == 70)
            goto LABEL_24;
LABEL_80:
          HIDWORD(v4[4].klass) = klass_high + 1;
          if (klass_high < 0x79)
            return 1;
          goto LABEL_81;
        }
      }
      else if (klass_high != 67)
      {
        goto LABEL_23;
      }
      klass_high = 67;
      v33 = wk;
      v33->timedrawflg = 0;
      *(u16 *)&v33->kaiwaflg = 1;
      v33->kaiwapaneldisp1 = 0;
      if (klass_high != 70)
        goto LABEL_80;
LABEL_24:
      CameraPosSet(1);
      CameraSet();
      v16 = HIDWORD(v4[4].klass);
      HIDWORD(v4[4].klass) = v16 + 1;
      if (v16 >= 0x79)
      {
LABEL_81:
        WORD2(v4[4].monitor) = 0;
        goto LABEL_82;
      }
      return 1;
    case 3:
      v17 = *(u32 *)(*((u64 *)v4[5].monitor + 18) + 4 * SWORD2(v4[4].monitor) + 32);
      if ((v17 & 0x80000000) == 0)
      {
        fclStart1(v17, 0);
        ++WORD2(v4[4].monitor);
        v18 = 4;
LABEL_83:
        LOWORD(v4[4].klass) = v18;
        return 1;
      }
      v32 = WORD2(v4[4].monitor) + 1;
      WORD2(v4[4].monitor) = v32;
      if (v32 << 16 < 0x20000)
        return 1;
LABEL_76:
      v23 = 5;
      HIDWORD(v4[4].klass) = 0;
LABEL_77:
      LOWORD(v4[4].klass) = v23;
      return 1;
    case 4:
      if (Update())
        return 1;
      if (SWORD2(v4[4].monitor) > 1)
        goto LABEL_76;
LABEL_82:
      v18 = 3;
      goto LABEL_83;
    case 5:
      v19 = HIDWORD(v4[4].klass);
      HIDWORD(v4[4].klass) = v19 + 1;
      if (v19 < 0x1F)
        return 1;
      v18 = 6;
      goto LABEL_83;
    case 6:
      sBtlSetMode(13);
      sBtlSetCmbBfrPos();
      CamMovePtn = sBtlGetCamMovePtn(cameraTimeNo[*((s32 *)v4[5].monitor + 8)]);
      sBtlSetMove(CamMovePtn, 1);
      wk->bNoEndCam = 1;
      v23 = 7;
      goto LABEL_77;
    case 7:
      v18 = 8;
      goto LABEL_83;
    case 8:
      sBtlBgnWaitALL(0);
      sBtlStatusBitOn(v10, 0x10u);
      v10->aiwk->bWait2 = 1;
      v10->vstatus |= 0x2000000u;
      sBtlSetMotion(v10, 7, 4, 0, 0);
      v23 = 9;
      HIDWORD(v4[4].klass) = 0;
      goto LABEL_77;
    case 9:
      v24 = HIDWORD(v4[4].klass);
      HIDWORD(v4[4].klass) = v24 + 1;
      if (v24 < 0x3D)
        return 1;
      v10->chgcolor = -2139062144;
      sBtlChangeModelColor(v10);
      HIDWORD(v4[4].klass) = 0;
      v18 = 10;
      goto LABEL_83;
    case 0xA:
      v25 = 0x80000000 - (HIDWORD(v4[4].klass) << 25);
      v10->chgcolor = v25;
      sBtlChangeModelColor(v10);
      v26 = HIDWORD(v4[4].klass);
      HIDWORD(v4[4].klass) = v26 + 1;
      if (v26 < 0x3D)
        return 1;
      v10->chgcolor = 0;
      sBtlChangeModelColor(v10);
      v18 = 11;
      goto LABEL_83;
    case 0xB:
      v10->vstatus |= 0x1000u;
      v27 = *(u32 *)(*((u64 *)v4[5].monitor + 18) + 40);
      if (v27 < 0)
        goto LABEL_59;
      fclStart1(v27, 0);
      v18 = 12;
      goto LABEL_83;
    case 0xC:
      if (Update())
        return 1;
LABEL_59:
      v18 = 13;
      goto LABEL_83;
    case 0xD:
      sBtlEndWaitALL(0, 0);
      if (!sBtlCheckUnit_Exec())
        return 1;
      v29 = wk;
      *(u16 *)&v29->kaiwaflg = 256;
      v29->kaiwapaneldisp1 = 1;
      LODWORD(v30) = *(u64 *)&v29->status | 8;
      HIDWORD(v30) = (*(u64 *)&v29->status & 0xEFFFFFFFEFFFFFFFLL) >> 32;
      *(u64 *)&v29->status = v30;
      v29->endcnt = 0;
      sBtlCheckBattleWin();
      sBtlGetAutoSkillPoint();
      sBtlGetChuuseiPoint();
      sBtlSetEndData();
      return 0;
    default:
      return 1;
  }
}

// 0x1dcf6b0
s32 BattleSummon_Effect(void) {
  Il2CppObject *ProcessData;
  Il2CppObject *v4;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 boss_eventID;
  SBTLUNIT_WORK *v10;
  SBTLUNIT_WORK *v11;
  s32 v12;
  s32 v13;
  SBTLUNIT_WORK *v15;
  S_CameraMoveDt *CamMovePtn;
  SBATTLE_WORK *v20;
  s32 timedrawflg;
  s32 v23;
  s32 v24;
  s16 v25;
  u32 klass_high;
  u8 *monitor;
  SBATTLE_WORK *v31;
  s32 v33;
  dds3ProcessID_t *started;
  void **p_monitor;
  u32 v36;
  f32 x;
  f32 y;
  f32 v42;
  f32 v43;
  f32 w;
  f32 v45;
  f32 z;
  f32 v47;
  SBTLUNIT_WORK *v48;
  s16 v50;
  SBATTLE_WORK *v54;
  s32 v55;
  s32 devilid;
  u32 DevilSESub;
  s32 v59;
  SBTLUNIT_WORK *v62;
  SBTLUNIT_WORK *v63;
  s32 v64;
  SBTLUNIT_WORK *v66;
  S_CameraMoveDt *v70;
  s32 v71;
  SBTLUNIT_WORK *v75;
  s32 v76;
  SBATTLE_WORK *v80;
  s64 i;
  SBTLUNIT_LISTWORK *v83;
  SBTLUNIT_WORK *pUnit;
  struct sdfVector4_t pos;
  sdfVector4_t v87;
  sdfVector4_t v88;

  ProcessData = dds3GetProcessData(g_mainPID);
  v4 = ProcessData;
  UnitMng = wk->UnitMng;
  boss_eventID = wk->boss_eventID;
  v10 = sBtlSearchUnit_ID(UnitMng, boss_eventID);
  v11 = sBtlSearchUnit_ID(wk->UnitMng, wk->playerID);
  v12 = 1;
  switch (LOWORD(v4[4].klass))
  {
    case 0:
      LOWORD(v4[4].klass) = 1;
      return v12;
    case 1:
      dds3FadeOut(0xFFu, 0xFFu, 0xFFu, 0x3Cu);
      LOWORD(v4[3].monitor) = 0;
      LOWORD(v4[4].klass) = 2;
      return v12;
    case 2:
      v13 = (s16)LOWORD(v4[3].monitor)++;
      if (v13 >= 61)
      {
        LOWORD(v4[4].klass) = 3;
        PosSet();
      }
      return v12;
    case 3:
      v15 = v11;
      CameraPosSet(1);
      CameraSet();
      sBtlSetMode(13);
      CamMovePtn = sBtlGetCamMovePtn(139);
      sBtlSetMove(CamMovePtn, 1);
      v20 = wk;
      v20->kaiwapaneldisp1 = 0;
      v20->status4 &= ~0x10u;
      v15->vstatus &= ~0x1000u;
      timedrawflg = v20->timedrawflg;
      v20->timedrawflg = 0;
      g_timedrawf = timedrawflg;
      *(u16 *)&v20->kaiwaflg = 1;
      sBtlStatusBitOn(v10, 0x10u);
      LOWORD(v4[3].monitor) = 0;
      dds3FadeIn2(0x1Eu);
      LOWORD(v4[4].klass) = 4;
      return v12;
    case 4:
      v23 = (s16)LOWORD(v4[3].monitor)++;
      if (v23 >= 61)
      {
        WORD2(v4[4].monitor) = 0;
        LOWORD(v4[4].klass) = 5;
      }
      return v12;
    case 5:
      v24 = *(u32 *)(*((u64 *)v4[5].monitor + 19) + 4 * SWORD2(v4[4].monitor) + 32);
      if (v24 < 0)
        goto LABEL_39;
      fclStart1(v24, 0);
      LOWORD(v4[4].klass) = 6;
      return v12;
    case 6:
      if (!Update())
      {
LABEL_39:
        v25 = 11;
        goto LABEL_169;
      }
      return v12;
    case 7:
      klass_high = HIDWORD(v4[4].klass);
      HIDWORD(v4[4].klass) = klass_high + 1;
      if (klass_high >= 0x1F)
      {
        WORD2(v4[4].monitor) = 1;
        HIDWORD(v4[4].klass) = 0;
        LOWORD(v4[4].klass) = 8;
      }
      return v12;
    case 8:
      monitor = v4[1].monitor;
      v31 = wk;
      v33 = *(u32 *)(*((u64 *)v4[5].monitor + 11) + 4 * SWORD2(v4[4].monitor) + 32);
      LODWORD(v4[2].klass) = 0;
      v31->scrMsgID = v33;
      started = scrStartScript2(11027, monitor, 0, 1);
      v4[2].monitor = started;
      p_monitor = &v4[2].monitor;
      *((u16 *)p_monitor + 12) = 9;
      return v12;
    case 9:
      if (v4[2].monitor)
      {
        if (dds3GetProcessStat(&v4[2].monitor) == 3)
          goto LABEL_54;
        if (!dds3GetProcessStat(&v4[2].monitor))
        {
LABEL_54:
          v4[2].monitor = 0;
          LODWORD(v4[2].klass) = -1;
          v25 = 10;
          goto LABEL_169;
        }
      }
      return v12;
    case 0xA:
      v36 = HIDWORD(v4[4].klass);
      HIDWORD(v4[4].klass) = v36 + 1;
      if (v36 >= 0x1F)
      {
        HIDWORD(v4[4].klass) = 0;
        LOWORD(v4[4].klass) = 5;
        WORD2(v4[4].monitor) = 2;
      }
      return v12;
    case 0xB:
      LOWORD(v4[4].klass) = 12;
      return v12;
    case 0xC:
      wk->bosseveloadflg = 1;
      pos = v10->pos;
      vct_A = pos;
      x = v10->rot.x;
      y = v10->rot.y;
      v42 = vct_A.x;
      v43 = vct_A.y;
      w = vct_A.w;
      z = v10->rot.z;
      v45 = v10->rot.w;
      v47 = vct_A.z + 400.0;
      v87.x = v42;
      v87.y = v43;
      v87.z = v47;
      v87.w = w;
      v88.x = x;
      v88.y = y;
      v88.z = z;
      v88.w = v45;
      sBtlSetExPos(v87, v88);
      v48 = sBtlSetEncountData4(0, 100, 0, 0);
      summonwk = v48;
      summonwk->vstatus |= 0x1000u;
      sBtlBgnWaitALL(0);
      HIDWORD(v4[4].klass) = 0;
      v50 = 13;
      goto LABEL_167;
    case 0xD:
      if (summonwk->mode == 8)
      {
        v54 = wk;
        v10->vstatus |= 0x2000000u;
        v54->bosseveloadflg = 0;
        sBtlSetMotion(v10, 20, 6, 0, 2);
        HIDWORD(v4[4].klass) = 0;
        LOWORD(v4[4].klass) = 14;
      }
      return v12;
    case 0xE:
      if (_CheckMotionEnd(v10))
        return v12;
      v55 = *(u32 *)(*((u64 *)v4[5].monitor + 19) + 36);
      if ((v55 & 0x80000000) == 0)
      {
        fclStart1(v55, 0);
        LOWORD(v4[4].klass) = 15;
        return v12;
      }
      v25 = 16;
      goto LABEL_169;
    case 0xF:
      if (!Update())
        LOWORD(v4[4].klass) = 16;
      return v12;
    case 0x10:
      if (_CheckMotionEnd(v10))
      {
        v10->vstatus |= 0x2000000u;
        v10->status |= 1u;
        sBtlSetMotion(v10, 16, 6, 0, 2);
        devilid = v10->para->devilid;
        DevilSESub = sBtlGetDevilSESub(devilid, 11);
        sBtlPlaySE(DevilSESub);
        HIDWORD(v4[4].klass) = 0;
        LOWORD(v4[4].klass) = 17;
      }
      return v12;
    case 0x11:
      v59 = HIDWORD(v4[4].klass) + 1;
      HIDWORD(v4[4].klass) = v59;
      if (v59 == 84)
      {
        sBtlSetFade(v10, 2, 0, 0, 8);
        v59 = HIDWORD(v4[4].klass);
        if (v59 != 310)
        {
LABEL_95:
          if (v59 == 130)
            goto LABEL_96;
          goto LABEL_147;
        }
      }
      else if (v59 != 310)
      {
        goto LABEL_95;
      }
      dds3SetQuake(120, 0x258u);
      sBtlPlaySE(0x10019u);
      v59 = HIDWORD(v4[4].klass);
      if (v59 == 130)
      {
LABEL_96:
        summonwk->vstatus |= 0x2000000u;
        sBtlStatusBitOn(summonwk, 0x10u);
        v62 = summonwk;
        v62->aiwk->bWait2 = 1;
        sBtlSetSkillTarget(v62, 865, 0x60000u);
        v59 = HIDWORD(v4[4].klass);
        if (v59 == 131)
          goto LABEL_99;
        goto LABEL_148;
      }
LABEL_147:
      if (v59 == 131)
      {
LABEL_99:
        v12 = 1;
        summonwk->vstatus &= ~0x1000u;
        return v12;
      }
LABEL_148:
      if (v59 != 470)
        return 1;
      for (i = 0; ; ++i)
      {
        v83 = wk->UnitMng;
        if (i >= v83->number)
          break;
        v83 = wk->UnitMng;
        pUnit = v83->pUnitL[i]->pUnit;
        if (pUnit && *((u32 *)v4[5].monitor + 5) == pUnit->para->devilid)
        {
          pUnit->mode = 9;
          pUnit->color = 0;
          sBtlDeath(pUnit);
        }
      }
      v50 = 18;
LABEL_167:
      LOWORD(v4[4].klass) = v50;
      return 1;
    case 0x12:
      v63 = summonwk;
      if (sBtlCheckNextAction(v63))
        LOWORD(v4[4].klass) = 19;
      return v12;
    case 0x13:
      v64 = *(u32 *)(*((u64 *)v4[5].monitor + 19) + 40);
      if (v64 < 0)
      {
        v25 = 21;
LABEL_169:
        LOWORD(v4[4].klass) = v25;
        HIDWORD(v4[4].klass) = 0;
      }
      else
      {
        fclStart1(v64, 0);
        LOWORD(v4[4].klass) = 20;
      }
      return v12;
    case 0x14:
      if (!Update())
        LOWORD(v4[4].klass) = 21;
      return v12;
    case 0x15:
      v66 = summonwk;
      v66->vstatus |= 0x2000000u;
      sBtlSetMotion(v66, 24, 6, 0, 2);
      wk->boss_eventID = summonwk->ListID;
      CameraPosSet(1);
      sBtlSetMode(13);
      v70 = sBtlGetCamMovePtn(138);
      v12 = 1;
      sBtlSetMove(v70, 1);
      HIDWORD(v4[4].klass) = 0;
      LOWORD(v4[4].klass) = 22;
      return v12;
    case 0x16:
      v71 = HIDWORD(v4[4].klass);
      HIDWORD(v4[4].klass) = v71 + 1;
      if (v71 == 50)
      {
        SetPara(Blur2, 0.0, 0.965, SEMI, 0);
        _SetRGBA(Blur2, 0x60808080u);
        SetArea(Blur2, 0, 0, 0);
        _On(Blur2, 0);
        dds3SetQuake(120, 0x258u);
      }
      v75 = summonwk;
      if (!_CheckMotionEnd(v75))
        return 1;
      dds3FadeOut(0xFFu, 0xFFu, 0xFFu, 0x3Cu);
      LOWORD(v4[3].monitor) = 0;
      v12 = 1;
      LOWORD(v4[4].klass) = 23;
      return v12;
    case 0x17:
      v76 = (u16)LOWORD(v4[3].monitor)++ + 1;
      if (v76 == 61)
      {
        _Off(Blur2, 0);
        sBtlSetMode(2);
        PosReSet();
        v80 = wk;
        *(u16 *)&v80->kaiwaflg = 256;
        v80->kaiwapaneldisp1 = 1;
        v80->timedrawflg = g_timedrawf;
        dds3FadeIn2(0x1Eu);
        LOWORD(v76) = v4[3].monitor;
      }
      if ((s16)v76 >= 101)
        LOWORD(v4[4].klass) = 25;
      return v12;
    case 0x19:
      sBtlEndWaitALL(0, 0);
      v12 = 0;
      summonwk->aiwk->bWait2 = 0;
      return v12;
    default:
      return v12;
  }
}

// 0x1dd06d0
s32 BattleLose_Effect(void) {
  Il2CppObject *ProcessData;
  Il2CppObject *v4;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 boss_eventID;
  SBTLUNIT_WORK *v10;
  SBTLUNIT_WORK *v11;
  s32 v13;
  SBTLUNIT_WORK *v14;
  s16 v15;
  u32 klass_high;
  u32 v19;
  s32 flg;
  s32 v22;
  u8 *monitor;
  SBATTLE_WORK *v27;
  s32 v29;
  dds3ProcessID_t *started;
  void **p_monitor;
  S_CameraMoveDt *v33;
  u32 v34;
  u32 v36;
  u32 v37;
  SBATTLE_WORK *v39;
  s64 v40;
  s32 v42;
  S_CameraMoveDt *CamMovePtn;
  SBATTLE_WORK *v45;

  ProcessData = dds3GetProcessData(g_mainPID);
  v4 = ProcessData;
  UnitMng = wk->UnitMng;
  boss_eventID = wk->boss_eventID;
  v10 = sBtlSearchUnit_ID(UnitMng, boss_eventID);
  v11 = sBtlSearchUnit_ID(wk->UnitMng, wk->playerID);
  v13 = 1;
  v14 = v11;
  switch (LOWORD(v4[4].klass))
  {
    case 0:
      LOWORD(v4[4].klass) = 1;
      return v13;
    case 1:
      sBtlSetSkill_EffectData(v11, 1012, 0);
      dds3SetQuake(240, 0x514u);
      v15 = 2;
      HIDWORD(v4[4].klass) = 0;
      goto LABEL_91;
    case 2:
      klass_high = HIDWORD(v4[4].klass);
      if (klass_high == 66)
      {
        PosSet();
        v10->vstatus |= 0x2001000u;
        sBtlSetMotion(v10, 0, 6, 0, 2);
        klass_high = HIDWORD(v4[4].klass);
        if (klass_high != 67)
        {
LABEL_25:
          if (klass_high == 70)
            goto LABEL_26;
LABEL_89:
          HIDWORD(v4[4].klass) = klass_high + 1;
          if (klass_high < 0x79)
            return v13;
          goto LABEL_90;
        }
      }
      else if (klass_high != 67)
      {
        goto LABEL_25;
      }
      klass_high = 67;
      v45 = wk;
      v45->timedrawflg = 0;
      *(u16 *)&v45->kaiwaflg = 1;
      v45->kaiwapaneldisp1 = 0;
      if (klass_high != 70)
        goto LABEL_89;
LABEL_26:
      CameraPosSet(1);
      CameraSet();
      LOWORD(v4[4].monitor) = 0;
      sBtlBossEventModelMove(v14);
      v19 = HIDWORD(v4[4].klass);
      HIDWORD(v4[4].klass) = v19 + 1;
      if (v19 >= 0x79)
      {
LABEL_90:
        v15 = 3;
        WORD2(v4[4].monitor) = 0;
        goto LABEL_91;
      }
      return v13;
    case 3:
      v14->vstatus |= 0x2000000u;
      sBtlSetMotion(v14, 13, 4, 6, 0);
      flg = v14->flg;
      LOWORD(v4[4].klass) = 4;
      v13 = 1;
      v14->flg = flg | 0x20;
      return v13;
    case 4:
      sBtlBossEventModelMove(v11);
      if (!_CheckMotionEnd(v14))
        return v13;
      v15 = 5;
      goto LABEL_91;
    case 5:
      v22 = *(u32 *)(*((u64 *)v4[5].monitor + 16) + 4 * SWORD2(v4[4].monitor) + 32);
      if (v22 < 0)
      {
        v42 = WORD2(v4[4].monitor) + 1;
        WORD2(v4[4].monitor) = v42;
        if (v42 << 16 >= 196608)
        {
          sBtlSetMode(13);
          sBtlSetCmbBfrPos();
          CamMovePtn = sBtlGetCamMovePtn(cameraLoseNo[*((s32 *)v4[5].monitor + 8)]);
          sBtlSetMove(CamMovePtn, 1);
          v15 = 7;
          HIDWORD(v4[4].klass) = 0;
LABEL_91:
          LOWORD(v4[4].klass) = v15;
        }
      }
      else
      {
        fclStart1(v22, 0);
        monitor = v4[1].monitor;
        v27 = wk;
        v29 = *(u32 *)(*((u64 *)v4[5].monitor + 16) + 4 * SWORD2(v4[4].monitor) + 32);
        LODWORD(v4[2].klass) = 0;
        v27->scrMsgID = v29;
        started = scrStartScript2(11027, monitor, 0, 1);
        v4[2].monitor = started;
        p_monitor = &v4[2].monitor;
        ++*((u16 *)p_monitor + 18);
        *((u16 *)p_monitor + 12) = 6;
      }
      return v13;
    case 6:
      if (v4[2].monitor)
      {
        if (dds3GetProcessStat(&v4[2].monitor) == 3)
          goto LABEL_50;
        if (!dds3GetProcessStat(&v4[2].monitor))
        {
LABEL_50:
          v4[2].monitor = 0;
          LODWORD(v4[2].klass) = -1;
          LOWORD(v4[4].klass) = 7;
          HIDWORD(v4[4].klass) = 0;
          sBtlSetMode(13);
          sBtlSetCmbBfrPos();
          v33 = sBtlGetCamMovePtn(cameraLoseNo[*((s32 *)v4[5].monitor + 8)]);
          sBtlSetMove(v33, 1);
        }
      }
      return v13;
    case 7:
      v34 = HIDWORD(v4[4].klass);
      HIDWORD(v4[4].klass) = v34 + 1;
      if (v34 < 0x1F)
        return v13;
      v15 = 8;
      goto LABEL_91;
    case 8:
      ++HIDWORD(v4[4].klass);
      wk->bNoEndCam = 1;
      v15 = 9;
      goto LABEL_91;
    case 9:
      v36 = HIDWORD(v4[4].klass);
      HIDWORD(v4[4].klass) = v36 + 1;
      if (v36 < 0xB5)
        return v13;
      dds3FadeOut(0, 0, 0, 0xB4u);
      v15 = 10;
      HIDWORD(v4[4].klass) = 0;
      goto LABEL_91;
    case 0xA:
      v37 = HIDWORD(v4[4].klass);
      HIDWORD(v4[4].klass) = v37 + 1;
      if (v37 < 0xB5)
        return v13;
      v15 = 12;
      HIDWORD(v4[4].klass) = 0;
      goto LABEL_91;
    case 0xC:
      sBtlEndWaitALL(0, 0);
      if (sBtlCheckUnit_Exec())
      {
        v39 = wk;
        *(u16 *)&v39->kaiwaflg = 256;
        v39->kaiwapaneldisp1 = 1;
        LODWORD(v40) = *(u64 *)&v39->status | 8;
        HIDWORD(v40) = (*(u64 *)&v39->status & 0xEFFFFFFFEFFFFFFFLL) >> 32;
        *(u64 *)&v39->status = v40;
        v39->endcnt = 0;
        sBtlCheckBattleWin();
        sBtlGetAutoSkillPoint();
        sBtlGetChuuseiPoint();
        sBtlSetEndData();
        return 0;
      }
      return v13;
    default:
      return v13;
  }
}

// 0x1dd0ea0
static s32 sBtlBossEventModelMove(SBTLUNIT_WORK *unitwk) {
  Il2CppObject *ProcessData;
  s16 monitor;
  f32 z;
  f32 v9;
  s32 v10;
  dds3ModelHandle_t *hModel;
  struct sdfVector4_t rot;
  struct sdfVector4_t pos;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    goto LABEL_11;
  goto LABEL_9;
  if (!ProcessData)
LABEL_9:
LABEL_11:
  monitor = ProcessData[4].monitor;
  if (monitor == 1)
  {
    v9 = unitwk->pos.z + -25.0;
    v10 = (s16)WORD1(ProcessData[4].monitor)++;
    unitwk->pos.z = v9;
    if (v10 >= 20)
      LOWORD(ProcessData[4].monitor) = monitor + 1;
LABEL_16:
    pos = unitwk->pos;
    vct_A = pos;
    hModel = unitwk->hModel;
    mdlSetPosition(hModel);
    rot = unitwk->rot;
    vct_A = rot;
    mdlSetRotate(unitwk->hModel);
    return 1;
  }
  if (!LOWORD(ProcessData[4].monitor))
  {
    z = unitwk->pos.z;
    LODWORD(ProcessData[4].monitor) = (u16)(monitor + 1);
    unitwk->pos.z = z + 500.0;
    goto LABEL_16;
  }
  return 1;
}

// 0x1dd11f0
s32 BattleRaidoDying_Effect(void) {
  Il2CppObject *ProcessData;
  Il2CppObject *v4;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 boss_eventID;
  SBTLUNIT_WORK *v10;
  SBTLUNIT_WORK *v11;
  s32 v12;
  SBTLUNIT_WORK *v13;
  u32 klass_high;
  sdatUnitWork_t *para;
  sdatParaWork_t *now;
  u32 v18;
  s16 v19;
  s32 v20;
  s32 v21;
  u8 *monitor;
  SBATTLE_WORK *v26;
  s32 v28;
  dds3ProcessID_t *started;
  void **p_monitor;
  u32 v31;
  u32 v32;
  SBTLAI_WORK *aiwk;
  u32 v34;
  u32 v35;
  u32 v36;
  SBATTLE_WORK *v38;
  s64 v39;
  s32 v41;
  SBATTLE_WORK *v43;

  ProcessData = dds3GetProcessData(g_mainPID);
  v4 = ProcessData;
  UnitMng = wk->UnitMng;
  boss_eventID = wk->boss_eventID;
  v10 = sBtlSearchUnit_ID(UnitMng, boss_eventID);
  v11 = sBtlSearchUnit_ID(wk->UnitMng, wk->playerID);
  v12 = 1;
  v13 = v11;
  switch (LOWORD(v4[4].klass))
  {
    case 0:
      sBtlForceDeleteAll(2);
      LOWORD(v4[4].klass) = 1;
      return v12;
    case 1:
      sBtlSetSkill_EffectData(v11, 1012, 0);
      HIDWORD(v4[4].klass) = 0;
      LOWORD(v4[4].klass) = 2;
      return v12;
    case 2:
      klass_high = HIDWORD(v4[4].klass);
      if (klass_high == 66)
      {
        sBtlRestartMotion(v10);
        v10->status &= ~0x20u;
        v10->hstatus &= ~0x10u;
        PosSet();
        para = v10->para;
        now = para->now;
        para->badstatus = 0;
        now->hp = now->maxhp;
        v10->vstatus |= 0x2000000u;
        sBtlSetMotion(v10, 0, 6, 0, 2);
        klass_high = HIDWORD(v4[4].klass);
        if (klass_high != 67)
        {
LABEL_25:
          if (klass_high == 70)
            goto LABEL_26;
LABEL_93:
          HIDWORD(v4[4].klass) = klass_high + 1;
          if (klass_high < 0x79)
            return v12;
          goto LABEL_94;
        }
      }
      else if (klass_high != 67)
      {
        goto LABEL_25;
      }
      klass_high = 67;
      v43 = wk;
      v43->timedrawflg = 0;
      *(u16 *)&v43->kaiwaflg = 1;
      v43->kaiwapaneldisp1 = 0;
      if (klass_high != 70)
        goto LABEL_93;
LABEL_26:
      CameraPosSet(1);
      CameraSet();
      v18 = HIDWORD(v4[4].klass);
      HIDWORD(v4[4].klass) = v18 + 1;
      if (v18 >= 0x79)
      {
LABEL_94:
        WORD2(v4[4].monitor) = 0;
        LOWORD(v4[4].klass) = 3;
      }
      return v12;
    case 3:
      v19 = 4;
      goto LABEL_89;
    case 4:
      v20 = HIDWORD(v4[4].klass) + 1;
      HIDWORD(v4[4].klass) = v20;
      if (v20 != 60)
        return v12;
      goto LABEL_50;
    case 5:
      v21 = *(u32 *)(*((u64 *)v4[5].monitor + 16) + 4 * SWORD2(v4[4].monitor) + 32);
      if (v21 < 0)
      {
        v41 = WORD2(v4[4].monitor) + 1;
        WORD2(v4[4].monitor) = v41;
        if (v41 << 16 >= 196608)
        {
LABEL_88:
          v19 = 9;
LABEL_89:
          LOWORD(v4[4].klass) = v19;
          HIDWORD(v4[4].klass) = 0;
        }
      }
      else
      {
        fclStart1(v21, 0);
        monitor = v4[1].monitor;
        v26 = wk;
        v28 = *(u32 *)(*((u64 *)v4[5].monitor + 16) + 4 * SWORD2(v4[4].monitor) + 32);
        LODWORD(v4[2].klass) = 0;
        v26->scrMsgID = v28;
        started = scrStartScript2(11027, monitor, 0, 1);
        v4[2].monitor = started;
        p_monitor = &v4[2].monitor;
        ++*((u16 *)p_monitor + 18);
        *((u16 *)p_monitor + 12) = 6;
      }
      return v12;
    case 6:
      if (!v4[2].monitor)
        return 1;
      if (dds3GetProcessStat(&v4[2].monitor) != 3)
      {
        if (dds3GetProcessStat(&v4[2].monitor))
          return 1;
      }
      v4[2].monitor = 0;
      LODWORD(v4[2].klass) = -1;
      HIDWORD(v4[4].klass) = 0;
      v12 = 1;
      LOWORD(v4[4].klass) = 7;
      return v12;
    case 7:
      if (SWORD2(v4[4].monitor) > 2)
        goto LABEL_88;
      goto LABEL_50;
    case 8:
      v31 = HIDWORD(v4[4].klass) + 1;
      HIDWORD(v4[4].klass) = v31;
      if (v31 >= 0x79)
LABEL_50:
        LOWORD(v4[4].klass) = 5;
      return v12;
    case 9:
      v32 = HIDWORD(v4[4].klass);
      HIDWORD(v4[4].klass) = v32 + 1;
      if (v32 >= 0x1F)
        LOWORD(v4[4].klass) = 10;
      return v12;
    case 0xA:
      LOWORD(v4[4].klass) = 12;
      return v12;
    case 0xC:
      sBtlBgnWaitALL(0);
      sBtlStatusBitOn(v10, 0x10u);
      aiwk = v10->aiwk;
      HIDWORD(v4[4].klass) = 0;
      aiwk->bWait2 = 1;
      LOWORD(v4[4].klass) = 13;
      return v12;
    case 0xD:
      v34 = HIDWORD(v4[4].klass);
      HIDWORD(v4[4].klass) = v34 + 1;
      if (v34 >= 0x29)
        LOWORD(v4[4].klass) = 14;
      return v12;
    case 0xE:
      HIDWORD(v4[4].klass) = 0;
      LOWORD(v4[4].klass) = 15;
      return v12;
    case 0xF:
      v35 = HIDWORD(v4[4].klass);
      HIDWORD(v4[4].klass) = v35 + 1;
      if (v35 <= 0x14A)
      {
        if (!_CheckMotionEnd(v13))
          return v12;
      }
      sBtlSetSkill_EffectData(v10, 1012, 0);
      v19 = 16;
      goto LABEL_89;
    case 0x10:
      v36 = HIDWORD(v4[4].klass);
      if (v36 == 67)
      {
        dds3FadeOut(0xFFu, 0xFFu, 0xFFu, 1u);
        v36 = HIDWORD(v4[4].klass);
      }
      HIDWORD(v4[4].klass) = v36 + 1;
      if (v36 >= 0xBE)
      {
        HIDWORD(v4[4].klass) = 0;
        LOWORD(v4[4].klass) = 17;
      }
      return v12;
    case 0x11:
      sBtlEndWaitALL(0, 0);
      if (sBtlCheckUnit_Exec())
      {
        v38 = wk;
        *(u16 *)&v38->kaiwaflg = 256;
        v38->kaiwapaneldisp1 = 1;
        LODWORD(v39) = *(u64 *)&v38->status | 8;
        HIDWORD(v39) = (*(u64 *)&v38->status & 0xEFFFFFFFEFFFFFFFLL) >> 32;
        *(u64 *)&v38->status = v39;
        v38->endcnt = 0;
        sBtlCheckBattleWin();
        sBtlGetAutoSkillPoint();
        sBtlGetChuuseiPoint();
        sBtlSetEndData();
        return 0;
      }
      return v12;
    default:
      return v12;
  }
}

// 0x1dd1a10
s32 BattleDying_Effect(void) {
  Il2CppObject *ProcessData;
  Il2CppObject *v4;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 boss_eventID;
  SBTLUNIT_WORK *v10;
  SBTLUNIT_WORK *v11;
  s32 v12;
  SBTLUNIT_WORK *v13;
  u32 klass_high;
  s32 v17;
  u32 v18;
  u32 v19;
  S_CameraMoveDt *CamMovePtn;
  SBTLAI_WORK *aiwk;
  u32 v24;
  u32 v25;
  s16 v26;
  u32 v27;
  SBATTLE_WORK *v29;
  sdatUnitWork_t *para;
  sdatParaWork_t *now;
  SBATTLE_WORK *v34;
  u32 v35;
  s32 v36;

  ProcessData = dds3GetProcessData(g_mainPID);
  v4 = ProcessData;
  UnitMng = wk->UnitMng;
  boss_eventID = wk->boss_eventID;
  v10 = sBtlSearchUnit_ID(UnitMng, boss_eventID);
  v11 = sBtlSearchUnit_ID(wk->UnitMng, wk->playerID);
  v12 = 1;
  v13 = v11;
  switch (LOWORD(v4[4].klass))
  {
    case 0:
      LOWORD(v4[4].klass) = 1;
      return v12;
    case 1:
      sBtlSetSkill_EffectData(v11, 1012, 0);
      HIDWORD(v4[4].klass) = 0;
      LOWORD(v4[4].klass) = 2;
      return v12;
    case 2:
      klass_high = HIDWORD(v4[4].klass);
      if (klass_high == 66)
      {
        sBtlRestartMotion(v10);
        v10->status &= ~0x20u;
        v10->hstatus &= ~0x10u;
        PosSet();
        para = v10->para;
        now = para->now;
        para->badstatus = 0;
        now->hp = now->maxhp;
        v10->vstatus |= 0x2000000u;
        sBtlSetMotion(v10, 0, 6, 0, 2);
        klass_high = HIDWORD(v4[4].klass);
        if (klass_high != 67)
        {
LABEL_19:
          if (klass_high != 70)
            goto LABEL_20;
          goto LABEL_88;
        }
      }
      else if (klass_high != 67)
      {
        goto LABEL_19;
      }
      v34 = wk;
      v34->timedrawflg = 0;
      *(u16 *)&v34->kaiwaflg = 1;
      v34->kaiwapaneldisp1 = 0;
      dds3SetQuake(120, 0x514u);
      klass_high = HIDWORD(v4[4].klass);
      if (klass_high != 70)
      {
LABEL_20:
        HIDWORD(v4[4].klass) = klass_high + 1;
        if (klass_high < 0x79)
          return v12;
        goto LABEL_91;
      }
LABEL_88:
      CameraPosSet(1);
      CameraSet();
      v35 = HIDWORD(v4[4].klass);
      HIDWORD(v4[4].klass) = v35 + 1;
      if (v35 >= 0x79)
      {
LABEL_91:
        WORD2(v4[4].monitor) = 0;
        LOWORD(v4[4].klass) = 3;
      }
      return v12;
    case 3:
      if (*((u32 *)v4[5].monitor + 8) != 6)
      {
        v10->vstatus |= 0x2000000u;
        sBtlSetMotion(v10, 14, 6, 0, 2);
      }
      LOWORD(v4[4].klass) = 4;
      return v12;
    case 4:
      if (_CheckMotionEnd(v10))
      {
        v10->vstatus |= 0x2000000u;
        sBtlSetMotion(v10, 0, 6, 0, 2);
        goto LABEL_93;
      }
      return v12;
    case 5:
      v17 = *(u32 *)(*((u64 *)v4[5].monitor + 17) + 4 * SWORD2(v4[4].monitor) + 32);
      if (v17 < 0)
      {
        v36 = WORD2(v4[4].monitor) + 1;
        WORD2(v4[4].monitor) = v36;
        if (v36 << 16 >= 196608)
          goto LABEL_95;
      }
      else
      {
        fclStart1(v17, 0);
        ++WORD2(v4[4].monitor);
        LOWORD(v4[4].klass) = 6;
      }
      return v12;
    case 6:
      if (!Update())
      {
        if (SWORD2(v4[4].monitor) <= 2)
          goto LABEL_93;
LABEL_95:
        v26 = 8;
        goto LABEL_96;
      }
      return v12;
    case 7:
      v18 = HIDWORD(v4[4].klass) + 1;
      HIDWORD(v4[4].klass) = v18;
      if (v18 == 80)
      {
        v10->vstatus |= 0x1000u;
      }
      else if (v18 >= 0x79)
      {
LABEL_93:
        LOWORD(v4[4].klass) = 5;
      }
      return v12;
    case 8:
      v19 = HIDWORD(v4[4].klass);
      HIDWORD(v4[4].klass) = v19 + 1;
      if (v19 >= 0x1F)
        LOWORD(v4[4].klass) = 9;
      return v12;
    case 9:
      sBtlSetMode(13);
      sBtlSetCmbBfrPos();
      CamMovePtn = sBtlGetCamMovePtn(cameraDyingNo[*((s32 *)v4[5].monitor + 8)]);
      sBtlSetMove(CamMovePtn, 1);
      wk->bNoEndCam = 1;
      LOWORD(v4[4].klass) = 11;
      return v12;
    case 0xB:
      sBtlBgnWaitALL(0);
      sBtlStatusBitOn(v10, 0x10u);
      aiwk = v10->aiwk;
      HIDWORD(v4[4].klass) = 0;
      aiwk->bWait2 = 1;
      LOWORD(v4[4].klass) = 12;
      return v12;
    case 0xC:
      v24 = HIDWORD(v4[4].klass);
      HIDWORD(v4[4].klass) = v24 + 1;
      if (v24 >= 0x29)
        LOWORD(v4[4].klass) = 13;
      return v12;
    case 0xD:
      HIDWORD(v4[4].klass) = 0;
      LOWORD(v4[4].klass) = 14;
      return v12;
    case 0xE:
      v25 = HIDWORD(v4[4].klass);
      HIDWORD(v4[4].klass) = v25 + 1;
      if (v25 > 0x14A)
        goto LABEL_59;
      if (_CheckMotionEnd(v13))
      {
LABEL_59:
        sBtlSetSkill_EffectData(v10, 1012, 0);
        v26 = 15;
LABEL_96:
        LOWORD(v4[4].klass) = v26;
        HIDWORD(v4[4].klass) = 0;
      }
      return v12;
    case 0xF:
      v27 = HIDWORD(v4[4].klass);
      if (v27 == 67)
      {
        dds3FadeOut(0xFFu, 0xFFu, 0xFFu, 1u);
        v27 = HIDWORD(v4[4].klass);
      }
      HIDWORD(v4[4].klass) = v27 + 1;
      if (v27 >= 0xBE)
      {
        HIDWORD(v4[4].klass) = 0;
        LOWORD(v4[4].klass) = 16;
      }
      return v12;
    case 0x10:
      sBtlEndWaitALL(0, 0);
      if (sBtlCheckUnit_Exec())
      {
        v29 = wk;
        *(u16 *)&v29->kaiwaflg = 256;
        v29->kaiwapaneldisp1 = 1;
        *(int8x8_t *)&v29->status = vorr_s8(*(int8x8_t *)&v29->status, (int8x8_t)0x1000000000000008LL);
        v29->endcnt = 0;
        sBtlCheckBattleWin();
        sBtlGetAutoSkillPoint();
        sBtlGetChuuseiPoint();
        sBtlSetEndData();
        return 0;
      }
      return v12;
    default:
      return v12;
  }
}

// 0x1dd2260
s32 BattleDyingSinado1_Effect(void) {
  Il2CppObject *ProcessData;
  Il2CppObject *v4;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 boss_eventID;
  SBTLUNIT_WORK *v10;
  SBTLUNIT_WORK *v11;
  s32 v12;
  s16 v13;
  u32 klass_high;
  sdatUnitWork_t *para;
  sdatParaWork_t *now;
  u32 v18;
  u32 v19;
  s64 v20;
  s32 v21;
  u8 *monitor;
  dds3ProcessID_t *started;
  void **p_monitor;
  u32 v27;
  u32 v28;
  S_CameraMoveDt *CamMovePtn;
  u32 v32;
  s16 v33;
  u32 v34;
  SBATTLE_WORK *v36;
  SBATTLE_WORK *v38;

  ProcessData = dds3GetProcessData(g_mainPID);
  v4 = ProcessData;
  UnitMng = wk->UnitMng;
  boss_eventID = wk->boss_eventID;
  v10 = sBtlSearchUnit_ID(UnitMng, boss_eventID);
  v11 = sBtlSearchUnit_ID(wk->UnitMng, wk->playerID);
  v12 = 1;
  switch (LOWORD(v4[4].klass))
  {
    case 0:
      LOWORD(v4[4].klass) = 1;
      return v12;
    case 1:
      sBtlSetSkill_EffectData(v11, 1012, 0);
      v13 = 2;
      HIDWORD(v4[4].klass) = 0;
      goto LABEL_95;
    case 2:
      klass_high = HIDWORD(v4[4].klass);
      if (klass_high == 66)
      {
        sBtlRestartMotion(v10);
        v10->status &= ~0x20u;
        v10->hstatus &= ~0x10u;
        sBtlShugouKaijyo();
        PosSet();
        para = v10->para;
        now = para->now;
        para->badstatus = 0;
        now->hp = now->maxhp;
        v10->vstatus |= 0x2000000u;
        sBtlSetMotion_ID(v10, 12, 6, 0, 2);
        sBtlSetSkill_EffectData(v10, 1223, 0);
        klass_high = HIDWORD(v4[4].klass);
        if (klass_high != 67)
        {
LABEL_25:
          if (klass_high == 70)
            goto LABEL_26;
LABEL_84:
          HIDWORD(v4[4].klass) = klass_high + 1;
          if (klass_high < 0x79)
            return v12;
          goto LABEL_85;
        }
      }
      else if (klass_high != 67)
      {
        goto LABEL_25;
      }
      v38 = wk;
      v38->timedrawflg = 0;
      *(u16 *)&v38->kaiwaflg = 1;
      v38->kaiwapaneldisp1 = 0;
      dds3SetQuake(120, 0x514u);
      klass_high = HIDWORD(v4[4].klass);
      if (klass_high != 70)
        goto LABEL_84;
LABEL_26:
      CameraPosSet(1);
      CameraSet();
      v18 = HIDWORD(v4[4].klass);
      HIDWORD(v4[4].klass) = v18 + 1;
      if (v18 >= 0x79)
      {
LABEL_85:
        WORD2(v4[4].monitor) = 0;
        v33 = 3;
        goto LABEL_92;
      }
      return v12;
    case 3:
      v19 = HIDWORD(v4[4].klass);
      HIDWORD(v4[4].klass) = v19 + 1;
      if (v19 < 0xB5)
        return v12;
      goto LABEL_87;
    case 4:
      v20 = SWORD2(v4[4].monitor);
      v21 = *(u32 *)(*((u64 *)v4[5].monitor + 17) + 4 * v20 + 32);
      if (v21 < 0)
      {
        WORD2(v4[4].monitor) = v20 + 1;
        if (((u16)v20 + 1) << 16 >= 196608)
        {
          v33 = 7;
LABEL_92:
          LOWORD(v4[4].klass) = v33;
          HIDWORD(v4[4].klass) = 0;
        }
      }
      else
      {
        v21 = *(u32 *)(*((u64 *)v4[5].monitor + 17) + 4 * SWORD2(v4[4].monitor) + 32);
        LODWORD(v4[2].klass) = 0;
        wk->scrMsgID = v21;
        monitor = v4[1].monitor;
        started = scrStartScript2(11027, monitor, 0, 1);
        v4[2].monitor = started;
        p_monitor = &v4[2].monitor;
        ++*((u16 *)p_monitor + 18);
        *((u16 *)p_monitor + 12) = 5;
      }
      return v12;
    case 5:
      if (!v4[2].monitor)
        return 1;
      if (dds3GetProcessStat(&v4[2].monitor) != 3)
      {
        if (dds3GetProcessStat(&v4[2].monitor))
          return 1;
      }
      v4[2].monitor = 0;
      LODWORD(v4[2].klass) = -1;
      if (SWORD2(v4[4].monitor) <= 2)
      {
        v13 = 4;
      }
      else
      {
        v13 = 7;
        HIDWORD(v4[4].klass) = 0;
      }
      v12 = 1;
      goto LABEL_95;
    case 6:
      v27 = HIDWORD(v4[4].klass) + 1;
      HIDWORD(v4[4].klass) = v27;
      if (v27 == 80)
      {
        v10->vstatus |= 0x1000u;
      }
      else if (v27 >= 0x79)
      {
LABEL_87:
        v13 = 4;
LABEL_95:
        LOWORD(v4[4].klass) = v13;
      }
      return v12;
    case 7:
      v28 = HIDWORD(v4[4].klass);
      HIDWORD(v4[4].klass) = v28 + 1;
      if (v28 < 0x1F)
        return v12;
      v13 = 8;
      goto LABEL_95;
    case 8:
      sBtlSetMode(13);
      sBtlSetCmbBfrPos();
      CamMovePtn = sBtlGetCamMovePtn(cameraDyingNo[*((s32 *)v4[5].monitor + 8)]);
      sBtlSetMove(CamMovePtn, 1);
      wk->bNoEndCam = 1;
      v13 = 10;
      goto LABEL_95;
    case 0xA:
      v13 = 11;
      HIDWORD(v4[4].klass) = 0;
      goto LABEL_95;
    case 0xB:
      v32 = HIDWORD(v4[4].klass);
      HIDWORD(v4[4].klass) = v32 + 1;
      if (v32 < 0x14B)
        return v12;
      sBtlSetSkill_EffectData(v10, 1012, 0);
      v33 = 12;
      goto LABEL_92;
    case 0xC:
      v34 = HIDWORD(v4[4].klass);
      if (v34 == 67)
      {
        dds3FadeOut(0xFFu, 0xFFu, 0xFFu, 1u);
        v34 = HIDWORD(v4[4].klass);
      }
      HIDWORD(v4[4].klass) = v34 + 1;
      if (v34 < 0xBE)
        return v12;
      v13 = 13;
      HIDWORD(v4[4].klass) = 0;
      goto LABEL_95;
    case 0xD:
      sBtlEndWaitALL(0, 0);
      if (sBtlCheckUnit_Exec())
      {
        v36 = wk;
        *(u16 *)&v36->kaiwaflg = 256;
        v36->kaiwapaneldisp1 = 1;
        *(int8x8_t *)&v36->status = vorr_s8(*(int8x8_t *)&v36->status, (int8x8_t)0x1000000000000008LL);
        v36->endcnt = 0;
        sBtlCheckBattleWin();
        sBtlGetAutoSkillPoint();
        sBtlGetChuuseiPoint();
        sBtlSetEndData();
        return 0;
      }
      return v12;
    default:
      return v12;
  }
}

// 0x1dd2aa0
s32 BattleStartApo_Effect(void) {
  Il2CppObject *ProcessData;
  Il2CppObject *v4;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 boss_eventID;
  SBTLUNIT_WORK *v10;
  s32 v11;
  SBTLUNIT_WORK *v12;
  s16 v13;
  s32 v14;
  SBATTLE_WORK *v19;
  s32 timedrawflg;
  s32 v22;
  s32 v23;
  s16 v24;
  s16 v25;
  u32 klass_high;
  s32 v28;
  S_CameraMoveDt *CamMovePtn;
  u32 v31;
  u32 v32;
  SBTLAI_WORK *aiwk;
  u32 v35;
  u32 status;
  SBATTLE_WORK *v40;
  s32 v41;
  S_CameraMoveDt *v43;
  u32 v44;
  u32 v50;
  s32 v52;
  u32 v53;
  s32 v54;
  u8 *monitor;
  dds3ProcessID_t *started;
  void **p_monitor;
  s32 v61;
  f32 ActionTime;
  u32 v63;
  s32 v64;
  SBATTLE_WORK *v66;
  s64 v68;
  SBTLUNIT_LISTWORK *v69;
  SBTLUNIT_WORK *pUnit;
  s32 v71;
  SBATTLE_WORK *v75;
  u32 v76;
  SBTLUNIT_WORK *Nakama;
  SBTLUNIT_WORK *v78;

  ProcessData = dds3GetProcessData(g_mainPID);
  v4 = ProcessData;
  UnitMng = wk->UnitMng;
  boss_eventID = wk->boss_eventID;
  v10 = sBtlSearchUnit_ID(UnitMng, boss_eventID);
  v11 = 1;
  v12 = sBtlSearchUnit_ID(wk->UnitMng, wk->playerID);
  switch (LOWORD(v4[4].klass))
  {
    case 0:
      LOWORD(v4[4].klass) = 1;
      return v11;
    case 1:
      dds3FadeOut(0xFFu, 0xFFu, 0xFFu, 0x3Cu);
      v13 = 2;
      LOWORD(v4[3].monitor) = 0;
      goto LABEL_197;
    case 2:
      v14 = (s16)LOWORD(v4[3].monitor)++;
      if (v14 >= 61)
      {
        LOWORD(v4[4].klass) = 3;
        PosSet();
      }
      return v11;
    case 3:
      CameraPosSet(1);
      CameraSet();
      v19 = wk;
      v19->kaiwapaneldisp1 = 0;
      v19->status4 &= ~0x10u;
      timedrawflg = v19->timedrawflg;
      v19->timedrawflg = 0;
      g_timedrawf = timedrawflg;
      *(u16 *)&v19->kaiwaflg = 1;
      sBtlStatusBitOn(v10, 0x10u);
      LOWORD(v4[3].monitor) = 0;
      dds3FadeIn2(0x1Eu);
      v13 = 4;
      goto LABEL_197;
    case 4:
      v22 = (s16)LOWORD(v4[3].monitor)++;
      if (v22 < 61)
        return v11;
      v13 = 5;
      WORD2(v4[4].monitor) = 0;
      goto LABEL_197;
    case 5:
      v23 = *(u32 *)(*((u64 *)v4[5].monitor + 11) + 4 * SWORD2(v4[4].monitor) + 32);
      if (v23 < 0)
        return v11;
      fclStart1(v23, 0);
      v24 = 6;
      goto LABEL_105;
    case 6:
      if (Update())
        return v11;
      v25 = 7;
      goto LABEL_165;
    case 7:
      v13 = 8;
      goto LABEL_197;
    case 8:
      klass_high = HIDWORD(v4[4].klass);
      if (klass_high != 30)
        goto LABEL_45;
      v12->next_motion_not_hokan = 2;
      if (sBtlDat()->m_type == 1)
      {
        v28 = 29;
LABEL_43:
        sBtlSetMotion(v12, v28, 4, 0, 0);
        goto LABEL_44;
      }
      if (sBtlDat()->m_type == 2)
      {
        v28 = 40;
        goto LABEL_43;
      }
      if (sBtlDat()->m_type == 3)
      {
        v28 = 41;
        goto LABEL_43;
      }
LABEL_44:
      klass_high = HIDWORD(v4[4].klass);
LABEL_45:
      HIDWORD(v4[4].klass) = klass_high + 1;
      if (klass_high >= 0x3D)
      {
        v13 = 9;
LABEL_197:
        LOWORD(v4[4].klass) = v13;
      }
      return v11;
    case 9:
      sBtlSetMode(13);
      sBtlSetCmbBfrPos();
      CamMovePtn = sBtlGetCamMovePtn(cameraStartNo[*((s32 *)v4[5].monitor + 8)]);
      sBtlSetMove(CamMovePtn, 1);
      v13 = 12;
      HIDWORD(v4[4].klass) = 0;
      goto LABEL_197;
    case 0xC:
      v31 = HIDWORD(v4[4].klass);
      if (v31)
      {
        if (v31 == 15)
          goto LABEL_54;
LABEL_188:
        HIDWORD(v4[4].klass) = v31 + 1;
        if (v31 < 0x5A)
          return v11;
        goto LABEL_189;
      }
      dds3SetQuake(120, 0x258u);
      sBtlSetSkill_EffectData(v10, 1012, 0);
      v31 = HIDWORD(v4[4].klass);
      if (v31 != 15)
        goto LABEL_188;
LABEL_54:
      sBtlSetMoveEnd();
      v32 = HIDWORD(v4[4].klass);
      HIDWORD(v4[4].klass) = v32 + 1;
      if (v32 >= 0x5A)
      {
LABEL_189:
        sBtlSetMode(4);
        v13 = 14;
        LOWORD(v4[3].monitor) = 0;
        goto LABEL_197;
      }
      return v11;
    case 0xE:
      v10->vstatus |= 0x2000000u;
      sBtlSetMotion(v10, 0, 6, 0, 2);
      v25 = 15;
      goto LABEL_165;
    case 0xF:
      v13 = 16;
      goto LABEL_197;
    case 0x10:
      sBtlStatusBitOn(v10, 0x10u);
      aiwk = v10->aiwk;
      HIDWORD(v4[4].klass) = 0;
      aiwk->bWait2 = 1;
      v13 = 17;
      goto LABEL_197;
    case 0x11:
      v35 = HIDWORD(v4[4].klass);
      if (v35)
      {
        if (v35 == 1)
          goto LABEL_67;
      }
      else
      {
        PosSet();
        v35 = HIDWORD(v4[4].klass);
        if (v35 == 1)
        {
LABEL_67:
          CameraPosSet(1);
          CameraSet();
          status = v10->status;
          if ((status & 0x80000000) != 0)
          {
            status = v10->status;
            v10->status = status & 0x7FFFFFFF;
            g_bosseventhpflg = 1;
LABEL_71:
            v40 = wk;
            v41 = v40->timedrawflg;
LABEL_72:
            v40->timedrawflg = 0;
            g_timedrawf = v41;
            v40->kaiwaflg = 2;
            v40->kaiwapaneldisp1 = 0;
            sBtlSetMode(13);
            v43 = sBtlGetCamMovePtn(cameraMagNo[*((s32 *)v4[5].monitor + 8)]);
            sBtlSetMove(v43, 1);
            v12->vstatus |= 0x1000u;
            v44 = HIDWORD(v4[4].klass);
            HIDWORD(v4[4].klass) = v44 + 1;
            if (v44 < 0x3D)
              return v11;
LABEL_196:
            v13 = 18;
            goto LABEL_197;
          }
          else
          {
            goto LABEL_71;
          }
          v40 = wk;
          v41 = v40->timedrawflg;
          goto LABEL_72;
        }
      }
      HIDWORD(v4[4].klass) = v35 + 1;
      if (v35 < 0x3D)
        return v11;
      goto LABEL_196;
    case 0x12:
      v10->vstatus |= 0x2000000u;
      sBtlSetMotion(v10, 11, 4, 0, 0);
      sBtlGetUnitHelperPos(v10, 0);
      if (sdfModelGetMarkPos(v10->hEveUnit->Model->modelRoot, 1))
      {
        goto LABEL_85;
      }
      else
      {
        sdfModelGetMarkPos(v10->hEveUnit->Model->modelRoot, 0);
LABEL_85:
        goto LABEL_86;
      }
LABEL_86:
      dds3SetQuake(120, 0x3E8u);
      v11 = 1;
      HIDWORD(v4[4].klass) = 0;
      LOWORD(v4[4].klass) = 19;
      HIWORD(v4[4].monitor) = 1;
      return v11;
    case 0x13:
      v50 = HIDWORD(v4[4].klass);
      if (v50 == 20 || v50 == 100 || v50 == 60)
      {
        dds3FadeIn(0xFFu, 0xFFu, 0xFFu, 0x28u);
        sBtlPlaySE(0x10019u);
        v50 = HIDWORD(v4[4].klass);
      }
      HIDWORD(v4[4].klass) = v50 + 1;
      if (v50 < 0x97)
        return v11;
      sBtlEndWaitALL(0, 0);
      wk->kaiwapaneldisp0 = 0;
      v13 = 20;
      goto LABEL_197;
    case 0x14:
      v52 = *(u32 *)(*((u64 *)v4[5].monitor + 11) + 4 * SWORD2(v4[4].monitor) + 32);
      if (v52 < 0)
        return v11;
      fclStart1(v52, 0);
      v24 = 21;
LABEL_105:
      LOWORD(v4[4].klass) = v24;
      ++WORD2(v4[4].monitor);
      return v11;
    case 0x15:
      if (Update())
        return v11;
      v25 = 22;
      goto LABEL_165;
    case 0x16:
      v53 = HIDWORD(v4[4].klass);
      HIDWORD(v4[4].klass) = v53 + 1;
      if (v53 < 0x3D)
        return v11;
      v13 = 23;
      goto LABEL_197;
    case 0x17:
      v54 = *(u32 *)(*((u64 *)v4[5].monitor + 11) + 4 * SWORD2(v4[4].monitor) + 32);
      if ((v54 & 0x80000000) == 0)
      {
        v54 = *(u32 *)(*((u64 *)v4[5].monitor + 11) + 4 * SWORD2(v4[4].monitor) + 32);
        LODWORD(v4[2].klass) = 0;
        wk->scrMsgID = v54;
        monitor = v4[1].monitor;
        started = scrStartScript2(11027, monitor, 0, 1);
        v4[2].monitor = started;
        p_monitor = &v4[2].monitor;
        ++*((u16 *)p_monitor + 18);
        *((u16 *)p_monitor + 12) = 24;
      }
      return v11;
    case 0x18:
      if (!v4[2].monitor)
        return v11;
      if (dds3GetProcessStat(&v4[2].monitor) != 3)
      {
        if (dds3GetProcessStat(&v4[2].monitor))
          return v11;
      }
      v4[2].monitor = 0;
      LODWORD(v4[2].klass) = -1;
      v25 = 25;
      goto LABEL_165;
    case 0x19:
      v10->vstatus |= 0x2000000u;
      v61 = *((u32 *)v4[5].monitor + 20);
      sBtlSetMotion(v10, v61, 6, 0, 2);
      ActionTime = sBtlGetActionTime(v10, 0);
      HIDWORD(v4[4].klass) = 0;
      startf = ActionTime;
      v13 = 27;
      goto LABEL_197;
    case 0x1B:
      v63 = HIDWORD(v4[4].klass);
      if (v63 == 55)
      {
        dds3SetQuake(150, 0x320u);
        v63 = HIDWORD(v4[4].klass);
      }
      HIDWORD(v4[4].klass) = v63 + 1;
      if (v63 < 0x3D)
        return v11;
      dds3FadeOut(0xFFu, 0xFFu, 0xFFu, 0x3Cu);
      v13 = 28;
      LOWORD(v4[3].monitor) = 0;
      goto LABEL_197;
    case 0x1C:
      v64 = (s16)LOWORD(v4[3].monitor)++;
      if (v64 < 61)
        return v11;
      v13 = 29;
      goto LABEL_197;
    case 0x1D:
      v66 = wk;
      v68 = 0;
      v66->timedrawflg = g_timedrawf;
      while (1)
      {
        v69 = wk->UnitMng;
        if (v68 >= v69->number)
          break;
        v69 = wk->UnitMng;
        pUnit = v69->pUnitL[v68]->pUnit;
        if (pUnit)
        {
          if (pUnit != wk->pCamSklUser2 && !pUnit->bOldDispOff)
            pUnit->vstatus &= ~0x1000u;
        }
        ++v68;
      }
      Nakama = sBtlGetNakama(0);
      if (Nakama)
        Nakama->vstatus &= ~0x1000u;
      v78 = sBtlGetNakama(1);
      if (v78)
        v78->vstatus &= ~0x1000u;
      sBtlSetMode(2);
      BYTE6(v4[3].klass) = 1;
      PosReSet();
      LOWORD(v4[3].monitor) = 0;
      dds3FadeIn2(0x1Eu);
      dds3SetQuake(60, 0x96u);
      LOWORD(v4[4].klass) = 30;
      return 1;
    case 0x1E:
      v71 = (s16)LOWORD(v4[3].monitor)++;
      if (v71 >= 31)
      {
        HIDWORD(v4[4].klass) = 0;
        LOWORD(v4[4].klass) = 31;
        v75 = wk;
        *(u16 *)&v75->kaiwaflg = 256;
        v75->kaiwapaneldisp1 = 1;
        if (g_bosseventhpflg)
          v10->status |= 0x80000000;
      }
      return v11;
    case 0x1F:
      v76 = HIDWORD(v4[4].klass);
      HIDWORD(v4[4].klass) = v76 + 1;
      if (v76 < 0x1F)
        return v11;
      v25 = 32;
LABEL_165:
      LOWORD(v4[4].klass) = v25;
      HIDWORD(v4[4].klass) = 0;
      return v11;
    case 0x20:
      sBtlEndWaitALL(0, 0);
      v11 = 0;
      v10->aiwk->bWait2 = 0;
      BYTE5(v4[3].klass) = 1;
      return v11;
    default:
      return v11;
  }
}

// 0x1dd3ae0
s32 sBtlTalkEvent(void) {
  Il2CppObject *ProcessData;
  Il2CppObject *v4;
  SBTLUNIT_WORK *v6;
  u32 *monitor;
  s64 *v8;
  s64 v9;
  s64 v10;
  s64 v11;
  SBTLUNIT_WORK *v12;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 boss_eventID;
  SBTLUNIT_WORK *v17;
  s32 v19;
  SBATTLE_WORK *v21;
  s32 timedrawflg;
  s32 klass;
  s32 v26;
  s64 v28;
  s64 v29;
  s64 v30;
  s64 *v31;
  s64 v32;
  s64 v33;
  s64 v34;
  s64 v35;
  s64 v36;
  s64 v37;
  s64 v38;
  s64 v39;
  s64 *v40;
  s64 v41;
  s64 v42;
  s64 v43;
  s64 v44;
  s64 *v45;
  s64 v46;
  s64 v47;
  s64 v48;
  s64 v49;
  s64 v50;

  ProcessData = dds3GetProcessData(g_mainPID);
  v4 = ProcessData;
  v6 = NewSpecific(SBTLUNIT_WORK, 5u);
  monitor = v4[5].monitor;
  v8 = v6;
  v9 = monitor[6];
  v10 = monitor[7];
  if ((s32)v9 >= 1)
  {
    v11 = 0;
    v12 = &v6[0];
    do
    {
      UnitMng = wk->UnitMng;
      boss_eventID = wk->boss_eventID;
      v17 = sBtlSearchUnit_ID(UnitMng, (s32)v11 + boss_eventID);
      if (v17)
      {
        QueryInterface(v17, *(void **)(*v8 + 64));
      }
      v12 = v17;
      ++v11;
      ++v12;
    }
    while (v9 != v11);
  }
  v19 = 1;
  switch (LOWORD(v4[4].klass))
  {
    case 0:
      WORD2(v4[4].monitor) = 0;
      LOWORD(v4[4].klass) = 3;
      return v19;
    case 3:
      v21 = wk;
      timedrawflg = v21->timedrawflg;
      v21->status4 &= ~0x10u;
      v21 = wk;
      v21->timedrawflg = 0;
      v19 = 1;
      g_timedrawf = timedrawflg;
      *(u16 *)&v21->kaiwapaneldisp0 = 0;
      LOWORD(v4[3].monitor) = 0;
      LOWORD(v4[4].klass) = 4;
      return v19;
    case 4:
      sBtlSetMode(2);
      WORD2(v4[4].monitor) = 0;
      goto LABEL_31;
    case 6:
      klass = v4[6].klass;
      if (klass == 1)
      {
        fclStart1(11, 1);
      }
      else
      {
        if (klass)
          return v19;
        fclStart1(SWORD2(v4[4].monitor) + 9, 1);
        v26 = WORD2(v4[4].monitor);
        SetNoSkipEnd(v26 == 0);
      }
      LOWORD(v4[4].klass) = 7;
      ++WORD2(v4[4].monitor);
      return v19;
    case 7:
      if (!Update())
      {
        if (LODWORD(v4[6].klass) || SWORD2(v4[4].monitor) > 1)
        {
          HIDWORD(v4[4].klass) = 0;
          LOWORD(v4[4].klass) = 8;
        }
        else
        {
LABEL_31:
          LOWORD(v4[4].klass) = 6;
        }
      }
      return v19;
    case 8:
      sBtlEndWaitALL(0, 0);
      preMenuEvent = 0;
      if ((s32)v9 < 1)
        goto LABEL_63;
      if ((u32)v10 == -1)
      {
        if ((u32)v9 >= 2)
        {
          v30 = (u32)v9 & 0xFFFFFFFE;
          v31 = v8 + 5;
          v32 = v30;
          do
          {
            v33 = *(v31 - 1);
            v34 = *v31;
            v31 += 2;
            v32 -= 2;
            v35 = *(u64 *)(v33 + 912);
            v36 = *(u64 *)(v34 + 912);
            v37 = *(u64 *)(v33 + 920);
            v38 = *(u64 *)(v34 + 920);
            *(u8 *)(v35 + 16) = 0;
            *(u8 *)(v36 + 16) = 0;
            *(u8 *)(v37 + 237) = 0;
            *(u8 *)(v38 + 237) = 0;
          }
          while (v32);
          if (v30 == v9)
            goto LABEL_63;
        }
        else
        {
          v30 = 0;
        }
        v39 = ~v30;
        if ((v9 & 1) != 0)
        {
          v40 = &v8[v30];
          v30 |= 1u;
          v41 = v40[4];
          v42 = *(u64 *)(v41 + 912);
          v43 = *(u64 *)(v41 + 920);
          *(u8 *)(v42 + 16) = 0;
          *(u8 *)(v43 + 237) = 0;
        }
        if (v39 + v9)
        {
          v44 = v9 - v30;
          v45 = &v8[v30 + 5];
          do
          {
            v46 = *(v45 - 1);
            v47 = *v45;
            v44 -= 2;
            v45 += 2;
            v48 = *(u64 *)(v46 + 912);
            v49 = *(u64 *)(v47 + 912);
            *(u8 *)(*(u64 *)(v46 + 920) + 237) = 0;
            v50 = *(u64 *)(v47 + 920);
            *(u8 *)(v48 + 16) = 0;
            *(u8 *)(v49 + 16) = 0;
            *(u8 *)(v50 + 237) = 0;
          }
          while (v44);
        }
      }
      else
      {
        v28 = &v8[(u32)v10 + 4];
        do
        {
          if (!v10)
          {
            v29 = *(u64 *)(*(u64 *)v28 + 920);
            *(u8 *)(*(u64 *)(*(u64 *)v28 + 912) + 16) = 0;
            *(u8 *)(v29 + 237) = 0;
          }
          --v10;
          --v9;
        }
        while (v9);
      }
LABEL_63:
      v19 = 0;
      BYTE5(v4[3].klass) = 1;
      return v19;
    default:
      return v19;
  }
}

// 0x1d98bd0
static bool _CheckMotionEnd(SBTLUNIT_WORK *wk) {
  return 1;
}

// 0x1d98be0
static void ResetBadStatusAll(BST IgnoreBstNo) {
  SBTLUNIT_WORK *v3;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 boss_eventID;
  SBTLUNIT_WORK *v8;
  SBTLUNIT_WORK *v9;
  SBTLUNIT_WORK *v10;
  SBTLUNIT_WORK *Nakama;
  SBTLUNIT_WORK *v12;
  SBTLUNIT_WORK *v13;
  SBTLUNIT_WORK *v14;
  s64 v15;
  s64 v16;
  u32 BadStatus;
  s64 v21;
  sdatUnitWork_t *v22;
  char v23;
  SBTLUNIT_WORK *v24;
  u32 *v25;

  v3 = NewSpecific(SBTLUNIT_WORK, 4u);
  UnitMng = wk->UnitMng;
  boss_eventID = wk->boss_eventID;
  v8 = sBtlSearchUnit_ID(UnitMng, boss_eventID);
  if (v8)
  {
    if (!QueryInterface(v8, *(void **)(*(u64 *)v3 + 64)))
      goto LABEL_37;
  }
  v3[0] = v8;
  v9 = sBtlSearchUnit_ID(wk->UnitMng, wk->playerID);
  v10 = v9;
  if (v9 && !QueryInterface(v9, *(void **)(*(u64 *)v3 + 64)))
    goto LABEL_37;
  v3[1] = v10;
  Nakama = sBtlGetNakama(0);
  v12 = Nakama;
  if (Nakama)
  {
    if (!QueryInterface(Nakama, *(void **)(*(u64 *)v3 + 64)))
      goto LABEL_37;
  }
  v3[2] = v12;
  v13 = sBtlGetNakama(1);
  v14 = v13;
  if (v13)
  {
    if (!QueryInterface(v13, *(void **)(*(u64 *)v3 + 64)))
    {
LABEL_37:
    }
  }
  v3[3] = v14;
  if (*(s32 *)((char *)v3 + 24) >= 1)
  {
    v15 = 0;
    v16 = &v3[0];
    do
    {
      v21 = *(u64 *)(v16 + 8 * v15);
      if (v21)
      {
        v22 = *(sdatUnitWork_t *)(v21 + 376);
        BadStatus = sBtlGetBadStatus(v22);
        if (BadStatus != 16 && BadStatus != 22 && BadStatus <= 0x10 && BadStatus != IgnoreBstNo)
        {
          v23 = BadStatus;
          v24 = *(SBTLUNIT_WORK *)(v16 + 8 * v15);
          sBtlResetBadStatus(v24, 1 << v23);
          v25 = *(u32 **)(v16 + 8 * v15);
          v25[266] = 0;
          v25[210] &= ~0x20u;
          v25[213] &= ~0x10u;
        }
      }
      ++v15;
    }
    while (v15 < *(s32 *)((char *)v3 + 24));
  }
}

// 0x1d98ea0
static void CameraPosSet(s32 hpos) {
  Il2CppObject *ProcessData;
  Il2CppObject *v6;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 boss_eventID;
  SBTLUNIT_WORK *v12;
  f32 x;
  f32 y;
  f32 w;
  f32 z;
  SBATTLE_WORK *v21;
  s32 encountno;
  f32 v23;
  f32 v24;
  f32 v25;

  ProcessData = dds3GetProcessData(g_mainPID);
  v6 = ProcessData;
  UnitMng = wk->UnitMng;
  boss_eventID = wk->boss_eventID;
  v12 = sBtlSearchUnit_ID(UnitMng, boss_eventID);
  sBtlGetUnitHelperPos(v12, hpos);
  goto LABEL_16;
LABEL_24:
  if (*((u32 *)v6[5].monitor + 8) != 4)
    goto LABEL_31;
  sBtlGetUnitHelperPos(v12, 2);
  y = y + (f32)((f32)(vct_A.y - y) * 0.5);
  goto LABEL_31;
LABEL_16:
  x = vct_A.x;
  y = vct_A.y;
  z = vct_A.z;
  w = vct_A.w;
  if (HIDWORD(v6[3].monitor) != 4)
    goto LABEL_24;
LABEL_31:
  v21 = wk;
  encountno = v21->encountno;
  v23 = 0.0;
  v24 = -180.0;
  v25 = 130.0;
  if (encountno != 536)
    v23 = z;
  v21->vPosBossEvent.z = v23;
  v21->vPosBossEvent.w = w;
  if (encountno != 536)
  {
    v24 = y;
    v25 = x;
  }
  v21->vPosBossEvent.x = v25;
  v21->vPosBossEvent.y = v24;
}

// 0x1d99230
static void PosSet(void) {
  Il2CppObject *ProcessData;
  Il2CppObject *v4;
  sbtl **v6;
  SB_ENCOUNTPAC *EncountPac;
  s16 start_playerpos;
  SBTLDMG_HITLISTWORK *hitList;
  SBTLEFF_LISTWORK *effList;
  SBTLEFF_LISTWORK *v14;
  SBTLEFF_LISTWORK *v16;
  SBTLEFF_LISTWORK *v18;
  SBTLEFF_LISTWORK *v20;
  SBTLEFF_LISTWORK *v22;
  SBTLEFF_LISTWORK *v24;
  SBTLEFF_LISTWORK *v26;
  dds3Basic_t *apMarkerUnit;
  dds3Basic_t *v30;
  dds3Basic_t *v31;
  dds3Basic_t *v32;
  dds3Basic_t *v33;
  dds3Basic_t *v34;
  dds3Basic_t *v35;
  dds3Basic_t *v36;
  sBtlUnit **v37;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 boss_eventID;
  SBTLUNIT_WORK *v42;
  sdatUnitWork_t *para;
  SBTLUNIT_WORK *v45;
  u32 BadStatus;
  sdatParaWork_t *now;
  SBATTLE_WORK *v49;
  SBTLUNIT_LISTWORK *v50;
  s32 playerID;
  SBTLUNIT_WORK *v52;
  SBTLUNIT_WORK *v53;
  f32 *v55;
  f32 v56;
  f32 v57;
  f32 v58;
  sdfVector4_t *p_rot;
  s32 v61;
  sdfVector4_t *p_rot_p;
  s32 v64;
  struct sdfVector4_t pos;
  dds3ModelHandle_t *hModel;
  struct sdfVector4_t v67;
  sdatUnitWork_t *v69;
  SBTLUNIT_WORK *Nakama;
  s32 v72;
  u64 v75;
  SBTLUNIT_WORK *v76;
  f32 v77;
  f32 v78;
  f32 v79;
  sdfVector4_t *v81;
  s32 v82;
  sdfVector4_t *v83;
  struct sdfVector4_t v84;
  s32 v85;
  struct sdfVector4_t v86;
  dds3ModelHandle_t *v87;
  struct sdfVector4_t v88;
  sdatUnitWork_t *v90;
  SBTLUNIT_WORK *v92;
  u64 v94;
  SBTLUNIT_WORK *v95;
  f32 v96;
  f32 v97;
  f32 v98;
  s32 v99;
  sdfVector4_t *v101;
  s32 v102;
  sdfVector4_t *v103;
  struct sdfVector4_t v104;
  s32 v105;
  struct sdfVector4_t v106;
  dds3ModelHandle_t *v107;
  struct sdfVector4_t v108;
  sdatUnitWork_t *v110;
  SBTLUNIT_LISTWORK *tgtList;
  SBTLUNIT_LISTWORK *p_tgtList;
  struct sbtl *static_fields;
  SBATTLE_WORK *v118;
  SBTLUNIT_LISTWORK *TargetList_Talk;
  s32 i;
  sbtl *v121;
  SBTLUNIT_LISTWORK *v122;
  sBtlUnit *v123;
  SBTLUNIT_WORK *v124;
  SBTLUNIT_WORK *v125;
  sdatUnitWork_t *v126;
  u32 v127;
  sdatParaWork_t *v128;
  s32 enc_posid;
  sbtl **v130;
  Il2CppObject *v131;
  sBtlUnit **v132;
  sdfVector4_t *v133;
  struct sdfVector4_t v135;
  dds3ModelHandle_t *v136;
  struct sdfVector4_t v137;
  s64 j;
  SBATTLE_WORK *v141;
  SBTLUNIT_LISTWORK *v142;
  SBTLUNIT_WORK *pUnit;
  sBtlUnit *v144;
  s32 v145;
  SBTLUNIT_WORK *v146;
  SBATTLE_WORK *v147;
  SBTLUNIT_WORK *v148;
  s32 v149;
  sdfVector4_t *v151;
  s32 v152;
  sdfVector4_t *v153;
  struct sdfVector4_t v154;
  s32 v155;
  struct sdfVector4_t v156;
  dds3ModelHandle_t *v157;
  struct sdfVector4_t v158;
  f32 v160;
  sdfVector4_t *v162;
  s32 v163;
  sdfVector4_t *v164;
  struct sdfVector4_t v165;
  s32 v166;
  struct sdfVector4_t v167;
  dds3ModelHandle_t *v168;
  struct sdfVector4_t v169;
  sBtlUnit *v171;
  s32 v173;
  s32 v174;
  s32 v175;
  struct sdfVector4_t v176;
  struct sdfVector4_t v177;
  struct sdfVector4_t v180;
  struct sdfVector4_t v181;
  struct sdfVector4_t v184;
  struct sdfVector4_t v188;
  struct sdfVector4_t v189;
  struct sdfVector4_t v190;
  struct sdfVector4_t v193;
  struct sdfVector4_t v194;
  struct sdfVector4_t v197;
  struct sdfVector4_t v198;
  f32 r;
  f32 z;
  u64 y;

  ProcessData = dds3GetProcessData(g_mainPID);
  v4 = ProcessData;
  v6 = &sbtl;
  y = 0;
  z = 0.0;
  r = 0.0;
  EncountPac = sBtlGetEncountPac(-1);
  start_playerpos = EncountPac[wk->encountno]->start_playerpos;
  mapEncPointGet(start_playerpos, (f32 *)&y + 1, &y, &z, &r);
  sBtlForceDeleteAll(1);
  hitList = wk->hitList;
  sBtlReleaseHitC_List(hitList, 1u);
  wk->scrFlag |= 0x40000u;
  sBtlAnimListClr();
  effList = wk->effList;
  sBtlDeleteEffectData_SkillIDType(effList, 301, 1u);
  v14 = wk->effList;
  sBtlDeleteEffectData_SkillIDType(v14, 302, 1u);
  v16 = wk->effList;
  sBtlDeleteEffectData_SkillIDType(v16, 303, 1u);
  v18 = wk->effList;
  sBtlDeleteEffectData_SkillIDType(v18, 304, 1u);
  v20 = wk->effList;
  sBtlDeleteEffectData_SkillIDType(v20, 305, 1u);
  v22 = wk->effList;
  sBtlDeleteEffectData_SkillIDType(v22, 306, 1u);
  v24 = wk->effList;
  sBtlDeleteEffectData_SkillIDType(v24, 307, 1u);
  v26 = wk->effList;
  sBtlDeleteEffectData_SkillIDType(v26, 308, 1u);
  apMarkerUnit = wk->apMarkerUnit;
  if (apMarkerUnit[0])
  {
    apMarkerUnit = wk->apMarkerUnit;
    dds3ObjectBaseOnFlag(apMarkerUnit, 1u);
  }
  v30 = wk->apMarkerUnit;
  if (v30[1])
  {
    v30 = wk->apMarkerUnit;
    dds3ObjectBaseOnFlag(&v30[1], 1u);
  }
  v31 = wk->apMarkerUnit;
  if (v31[2])
  {
    v31 = wk->apMarkerUnit;
    dds3ObjectBaseOnFlag(&v31[2], 1u);
  }
  v32 = wk->apMarkerUnit;
  if (v32[3])
  {
    v32 = wk->apMarkerUnit;
    dds3ObjectBaseOnFlag(&v32[3], 1u);
  }
  v33 = wk->apMarkerUnit;
  if (v33[4])
  {
    v33 = wk->apMarkerUnit;
    dds3ObjectBaseOnFlag(&v33[4], 1u);
  }
  v34 = wk->apMarkerUnit;
  if (v34[5])
  {
    v34 = wk->apMarkerUnit;
    dds3ObjectBaseOnFlag(&v34[5], 1u);
  }
  v35 = wk->apMarkerUnit;
  if (v35[6])
  {
    v35 = wk->apMarkerUnit;
    dds3ObjectBaseOnFlag(&v35[6], 1u);
  }
  v36 = wk->apMarkerUnit;
  if (v36[7])
  {
    v36 = wk->apMarkerUnit;
    dds3ObjectBaseOnFlag(&v36[7], 1u);
  }
  v37 = &sBtlUnit;
  wk->bNoEnemyName = 1;
  if ((u32)(HIDWORD(v4[3].monitor) - 1) <= 2)
  {
    UnitMng = wk->UnitMng;
    boss_eventID = wk->boss_eventID;
    v42 = sBtlSearchUnit_ID(UnitMng, boss_eventID);
    if (!v42)
      goto LABEL_120;
    para = v42->para;
    v45 = v42;
    BadStatus = sBtlGetBadStatus(para);
    if ((v45->hstatus & 0x10) != 0 || BadStatus == 17)
    {
      now = v45->para->now;
      if (now->hp <= 0)
      {
        now->hp = 1;
        if (v45->deadEvent >= 1)
          v45->deadEvent = 0;
        if (BadStatus == 17)
        {
          sBtlCheckResetBadStatus(v45);
        }
      }
    }
  }
LABEL_120:
  ResetBadStatusAll(0x16u);
  sBtlReleaseSTP_List(wk->stpList, 1u);
  v49 = wk;
  v50 = v49->UnitMng;
  playerID = v49->playerID;
  v52 = sBtlSearchUnit_ID(v50, playerID);
  if (!v52)
    goto LABEL_141;
  v53 = v52;
  v55 = sbBossRaidouPos[*((s32 *)v4[5].monitor + 8)];
  v56 = v55[8];
  v53->pos.x = v56;
  v57 = v55[9];
  v53->pos.y = v57;
  v58 = v55[10];
  y = __PAIR64__(LODWORD(v56), LODWORD(v57));
  r = 180.0;
  v53->pos.z = v58;
  z = v58;
  FromEuler(0.0, 3.1415927, 0.0);
  p_rot = &v53->rot;
  v61 = (u8)byte_5755EF5;
  *p_rot = vct_A;
  if (v61)
    goto LABEL_131;
  goto LABEL_148;
  if (v72)
  {
LABEL_131:
    goto LABEL_132;
  }
LABEL_148:
LABEL_132:
  vct_A = (struct sdfVector4_t)xmmword_3CFD5C0;
  p_rot_p = &v53->rot_p;
  v64 = (u8)byte_5755EF5;
  v53->mv_rotbk = r;
  pos = v53->pos;
  *p_rot_p = vct_A;
  if (v64)
  {
    goto LABEL_136;
  }
  else
  {
    v176 = pos;
    pos = v176;
    goto LABEL_136;
  }
  v177 = pos;
  pos = v177;
LABEL_136:
  vct_A = pos;
  hModel = v53->hModel;
  mdlSetPosition(v53->hModel);
  v67 = *p_rot;
  vct_A = v67;
  mdlSetRotate(v53->hModel);
  v69 = v53->para;
  if (sBtlGetBadStatus(v69) != 17)
    goto LABEL_158;
LABEL_141:
  Nakama = sBtlGetNakama(1);
  if (!Nakama)
    goto LABEL_191;
  goto LABEL_163;
LABEL_158:
  v53->vstatus |= 0x2000000u;
  sBtlResetAction(v53);
  sBtlSetMotion(v53, 0, 1, 0, 2);
  sBtlSetAction(v53, 1, 0);
  Nakama = sBtlGetNakama(1);
  if (!Nakama)
  {
LABEL_191:
    v92 = sBtlGetNakama(0);
    if (!v92)
      goto LABEL_238;
    goto LABEL_200;
  }
LABEL_163:
  v75 = y;
  v76 = Nakama;
  Nakama->pos.x = *((f32 *)&y + 1);
  LODWORD(Nakama->pos.y) = v75;
  v77 = r;
  v78 = z;
  Nakama->pos.z = z;
  if (v77 <= -45.0 || v77 >= 45.0)
  {
    if (v77 >= -45.0 || v77 <= -135.0)
    {
      if (v77 <= 45.0 || v77 >= 135.0)
      {
        Nakama->pos.x = *((f32 *)&v75 + 1) + 300.0;
        v79 = -200.0;
      }
      else
      {
        v79 = 500.0;
      }
    }
    else
    {
      v79 = -500.0;
    }
    Nakama->pos.z = v78 + v79;
  }
  else
  {
    Nakama->pos.x = *((f32 *)&v75 + 1) + -400.0;
  }
  FromEuler(0.0, v77 * 0.017453292, 0.0);
  v81 = &v76->rot;
  v82 = (u8)byte_5755EF5;
  *v81 = vct_A;
  if (v82)
    goto LABEL_180;
  goto LABEL_209;
  if (v99)
  {
LABEL_180:
    goto LABEL_181;
  }
LABEL_209:
LABEL_181:
  vct_A = (struct sdfVector4_t)xmmword_3CFD5C0;
  v83 = &v76->rot_p;
  v84 = vct_A;
  v85 = (u8)byte_5755EF5;
  v76->mv_rotbk = r;
  v86 = v76->pos;
  *v83 = v84;
  if (v85)
  {
    goto LABEL_185;
  }
  else
  {
    v180 = v86;
    v86 = v180;
    goto LABEL_185;
  }
  v181 = v86;
  v86 = v181;
LABEL_185:
  vct_A = v86;
  v87 = v76->hModel;
  mdlSetPosition(v76->hModel);
  v88 = *v81;
  vct_A = v88;
  mdlSetRotate(v76->hModel);
  if (*((u32 *)v4[5].monitor + 8) == 6)
  {
    v90 = v76->para;
    goto LABEL_190;
  }
  else
  {
    v76->vstatus |= 0x1000u;
    v90 = v76->para;
LABEL_190:
    if ((sBtlGetBadStatus(v90) & 0xFFFFFFFE) == 0x10)
      goto LABEL_191;
    goto LABEL_195;
  }
  if ((sBtlGetBadStatus(v90) & 0xFFFFFFFE) == 0x10)
    goto LABEL_191;
LABEL_195:
  v76->vstatus |= 0x2000000u;
  sBtlSetMotion(v76, 0, 1, 0, 2);
  sBtlSetAction(v76, 1, 0);
  v92 = sBtlGetNakama(0);
  if (!v92)
  {
LABEL_238:
    goto LABEL_240;
  }
LABEL_200:
  v94 = y;
  v95 = v92;
  v92->pos.x = *((f32 *)&y + 1);
  LODWORD(v92->pos.y) = v94;
  v96 = r;
  v97 = z;
  v92->pos.z = z;
  if (v96 <= -45.0 || v96 >= 45.0)
  {
    if (v96 >= -45.0 || v96 <= -135.0)
    {
      if (v96 <= 45.0 || v96 >= 135.0)
      {
        v92->pos.x = *((f32 *)&v94 + 1) + -300.0;
        v98 = -200.0;
      }
      else
      {
        v98 = -500.0;
      }
    }
    else
    {
      v98 = 500.0;
    }
    v92->pos.z = v97 + v98;
  }
  else
  {
    v92->pos.x = *((f32 *)&v94 + 1) + 400.0;
  }
  FromEuler(0.0, v96 * 0.017453292, 0.0);
  v101 = &v95->rot;
  v102 = (u8)byte_5755EF5;
  *v101 = vct_A;
  if (v102)
    goto LABEL_227;
  goto LABEL_365;
  if (v173)
  {
LABEL_227:
    goto LABEL_228;
  }
LABEL_365:
LABEL_228:
  vct_A = (struct sdfVector4_t)xmmword_3CFD5C0;
  v103 = &v95->rot_p;
  v104 = vct_A;
  v105 = (u8)byte_5755EF5;
  v95->mv_rotbk = r;
  v106 = v95->pos;
  *v103 = v104;
  if (v105)
  {
    goto LABEL_232;
  }
  else
  {
    v189 = v106;
    v106 = v189;
    goto LABEL_232;
  }
  v190 = v106;
  v106 = v190;
LABEL_232:
  vct_A = v106;
  v107 = v95->hModel;
  mdlSetPosition(v95->hModel);
  v108 = *v101;
  vct_A = v108;
  mdlSetRotate(v95->hModel);
  if (*((u32 *)v4[5].monitor + 8) == 6)
  {
    v110 = v95->para;
    goto LABEL_237;
  }
  else
  {
    v95->vstatus |= 0x1000u;
    v110 = v95->para;
LABEL_237:
    if ((sBtlGetBadStatus(v110) & 0xFFFFFFFE) == 0x10)
      goto LABEL_238;
    goto LABEL_356;
  }
  if ((sBtlGetBadStatus(v110) & 0xFFFFFFFE) == 0x10)
    goto LABEL_238;
LABEL_356:
  v95->vstatus |= 0x2000000u;
  sBtlSetMotion(v95, 0, 1, 0, 2);
  sBtlSetAction(v95, 1, 0);
LABEL_240:
  tgtList = wk->tgtList;
  if (tgtList)
  {
    tgtList = wk->tgtList;
    sBtlDeleteUnitList(tgtList, 0);
    p_tgtList = &wk->tgtList;
    p_tgtList = 0;
  }
  v118 = wk;
  TargetList_Talk = sBtlCreateTargetList_Talk(2);
  v118->tgtList = TargetList_Talk;
  for (i = 0; ; ++i)
  {
    v121 = *v6;
    v121 = *v6;
    v122 = wk->tgtList;
    if (i >= v122->count)
      break;
    v123 = *v37;
    v124 = sBtlSearchUnit_ID(v122, i);
    if (!v124)
      continue;
    v125 = v124;
    if ((u32)(HIDWORD(v4[3].monitor) - 1) > 2)
      goto LABEL_271;
    v126 = v124->para;
    v127 = sBtlGetBadStatus(v124->para);
    if ((v125->hstatus & 0x10) == 0)
    {
      if (v127 != 17)
        goto LABEL_271;
    }
    v128 = v125->para->now;
    if (v128->hp <= 0)
    {
      v128->hp = 1;
      if (v125->deadEvent >= 1)
        v125->deadEvent = 0;
      if (v127 == 17)
      {
        sBtlCheckResetBadStatus(v125);
      }
    }
LABEL_271:
    sBtlZakoWarpReset(v125);
    enc_posid = v125->enc_posid;
    v125->vstatus |= 0x1000u;
    if (enc_posid)
    {
      v130 = v6;
      v131 = v4;
      v132 = v37;
      v133 = &v125->rot;
      sBtlGetPointData(enc_posid, &v125->pos, &v125->rot);
      v184 = v125->pos;
      goto LABEL_278;
LABEL_279:
      vct_A = v184;
      goto LABEL_280;
LABEL_278:
      goto LABEL_279;
LABEL_280:
      v125->koteipos = vct_A;
      v135 = v125->pos;
      vct_A = v135;
      v136 = v125->hModel;
      mdlSetPosition(v125->hModel);
      v137 = *v133;
      v37 = v132;
      v188 = v137;
      v137 = v188;
      v4 = v131;
      vct_A = v137;
      mdlSetRotate(v125->hModel);
      v6 = v130;
      continue;
    }
  }
  for (j = 0; ; ++j)
  {
    v121 = *v6;
    v141 = wk;
    v142 = v141->UnitMng;
    if (j >= v142->number)
      break;
    pUnit = v142->pUnitL[j]->pUnit;
    if (!pUnit)
      continue;
    if ((pUnit->side & 0x3F) == 2)
      pUnit->vstatus |= 0x1000u;
  }
  v147 = (*v6)->static_fields->wk;
  v142 = v147->UnitMng;
  v144 = *v37;
  v145 = v147->boss_eventID;
  v146 = sBtlSearchUnit_ID(v142, v145);
  if (!v146)
    return;
  v148 = v146;
  sBtlBossWarpReset(v148);
  v149 = *((u32 *)v4[5].monitor + 8);
  if ((u32)(v149 - 4) < 3)
  {
LABEL_332:
    if (v149 != 6)
    {
LABEL_348:
      v171 = *v37;
      v148->vstatus = v148->vstatus & 0xFDFFEFFF | 0x2000000;
      sBtlSetMotion(v148, 0, 0, 0, 2);
      sBtlSetAction(v148, 1, 0);
      return;
    }
    mapEncPointGet(1, (f32 *)&y + 1, &y, &z, &r);
    v160 = *(f32 *)&y;
    r = 0.0;
    v148->pos.x = *((f32 *)&y + 1);
    v148->pos.y = v160;
    v148->pos.z = z;
    FromEuler(0.0, 0.0, 0.0);
    v162 = &v148->rot;
    v163 = (u8)byte_5755EF5;
    *v162 = vct_A;
    if (v163)
      goto LABEL_339;
    goto LABEL_391;
    if (v175)
    {
LABEL_339:
      goto LABEL_340;
    }
LABEL_391:
LABEL_340:
    vct_A = (struct sdfVector4_t)xmmword_3CFD5C0;
    v164 = &v148->rot_p;
    v165 = vct_A;
    v166 = (u8)byte_5755EF5;
    v148->mv_rotbk = r;
    v167 = v148->pos;
    *v164 = v165;
    if (v166)
    {
      goto LABEL_344;
    }
    else
    {
      v197 = v167;
      v167 = v197;
      goto LABEL_344;
    }
    v198 = v167;
    v167 = v198;
LABEL_344:
    vct_A = v167;
    v168 = v148->hModel;
    mdlSetPosition(v148->hModel);
    v169 = *v162;
    vct_A = v169;
    mdlSetRotate(v148->hModel);
    goto LABEL_348;
  }
  *(u64 *)&v148->pos.y = 0;
  v148->pos.x = 0.0;
  r = 0.0;
  FromEuler(0.0, 0.0, 0.0);
  v151 = &v148->rot;
  v152 = (u8)byte_5755EF5;
  *v151 = vct_A;
  if (v152)
    goto LABEL_323;
  goto LABEL_379;
  if (v174)
  {
LABEL_323:
    goto LABEL_324;
  }
LABEL_379:
LABEL_324:
  vct_A = (struct sdfVector4_t)xmmword_3CFD5C0;
  v153 = &v148->rot_p;
  v154 = vct_A;
  v155 = (u8)byte_5755EF5;
  v148->mv_rotbk = r;
  v156 = v148->pos;
  *v153 = v154;
  if (v155)
  {
    goto LABEL_328;
  }
  else
  {
    v193 = v156;
    v156 = v193;
    goto LABEL_328;
  }
  v194 = v156;
  v156 = v194;
LABEL_328:
  vct_A = v156;
  v157 = v148->hModel;
  mdlSetPosition(v148->hModel);
  v158 = *v151;
  vct_A = v158;
  mdlSetRotate(v148->hModel);
  v149 = *((u32 *)v4[5].monitor + 8);
  goto LABEL_332;
}

// 0x1d9b360
static void PosReSet(void) {
  Il2CppObject *ProcessData;
  Il2CppObject *v3;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 playerID;
  SBTLUNIT_WORK *v9;
  SB_ENCOUNTPAC *EncountPac;
  s16 start_playerpos;
  f32 v13;
  sdfVector4_t *v15;
  s32 v16;
  sdfVector4_t *p_rot_p;
  s32 v19;
  struct sdfVector4_t pos;
  dds3ModelHandle_t *v21;
  struct sdfVector4_t v22;
  SBTLUNIT_WORK *Nakama;
  SBTLUNIT_WORK *v25;
  f32 x;
  f32 Dir180;
  f32 PosToDir;
  f32 v30;
  f32 LenXZ;
  f32 v32;
  f32 v33;
  f32 w;
  f32 v35;
  sdfVector4_t *p_rot;
  dds3ModelHandle_t *hModel;
  struct sdfVector4_t v41;
  SBTLUNIT_WORK *v43;
  SBTLUNIT_WORK *v44;
  f32 v46;
  f32 v47;
  f32 v48;
  f32 v49;
  f32 v50;
  f32 v51;
  f32 v52;
  f32 v53;
  f32 v54;
  sdfVector4_t *v58;
  dds3ModelHandle_t *v59;
  struct sdfVector4_t v60;
  SBATTLE_WORK *v63;
  SBTLUNIT_LISTWORK *v64;
  s32 boss_eventID;
  SBTLUNIT_WORK *v66;
  s32 enc_posid;
  SBTLUNIT_WORK *v68;
  s64 v69;
  SBATTLE_WORK *v70;
  s64 v71;
  SB_ENCOUNTPAC *v72;
  SB_ENCOUNTPAC *v74;
  s32 v76;
  SB_ENCOUNTPAC *v77;
  sdfVector4_t *p_pos;
  sdfVector4_t *v80;
  sdfVector4_t *p_koteipos;
  s32 v83;
  struct sdfVector4_t v84;
  dds3ModelHandle_t *v85;
  struct sdfVector4_t v86;
  s64 i;
  SBTLUNIT_LISTWORK *v89;
  SBTLUNIT_WORK *pUnit;
  s64 j;
  SBTLUNIT_LISTWORK *v93;
  SBTLUNIT_WORK *v94;
  SBTLACTAI_WORK *actaiwk;
  s32 v96;
  s32 v97;
  struct sdfVector4_t v98;
  struct sdfVector4_t v99;
  struct sdfVector4_t v106;
  struct sdfVector4_t v107;
  struct sdfVector4_t v110;
  s64 v111;
  s64 ToZ;
  f32 r;
  f32 z;
  s64 y;

  HIDWORD(y) = 0;
  v111 = 0;
  ToZ = 0;
  ProcessData = dds3GetProcessData(g_mainPID);
  v3 = ProcessData;
  y = 0;
  z = 0.0;
  r = 0.0;
  if (*((u32 *)ProcessData[5].monitor + 4) != 51)
  {
    UnitMng = wk->UnitMng;
    playerID = wk->playerID;
    v9 = sBtlSearchUnit_ID(UnitMng, playerID);
    if (!v9)
    {
LABEL_39:
      Nakama = sBtlGetNakama(0);
      if (Nakama)
      {
        v25 = Nakama;
        Nakama->pos.x = v9->pos.x;
        Nakama->pos.y = v9->pos.y;
        Nakama->pos.z = v9->pos.z;
        x = wk->scene->camera->followUpAngle.x;
        Dir180 = sBtlGetDir180(x);
        PosToDir = sBtlGetPosToDir(0.0, 0.0, -200.0, 200.0);
        v30 = sBtlGet360(Dir180 + PosToDir);
        LenXZ = sBtlGetLenXZ(0.0, 0.0, -200.0, 200.0);
        sBtlGetMoveXZ(0.0, 0.0, v30, LenXZ, (f32 *)&ToZ + 1, &ToZ);
        v32 = v25->pos.y;
        v33 = v25->pos.x + *((f32 *)&ToZ + 1);
        w = v25->pos.w;
        v35 = v25->pos.z + *(f32 *)&ToZ;
        v25->pos.x = v33;
        v25->pos.z = v35;
        v25->rot = v9->rot;
        v25->rot_p = v9->rot;
        v25->mv_rotbk = v9->mv_rotbk;
        p_rot = &v25->rot;
        vct_A.x = v33;
        vct_A.y = v32;
        vct_A.z = v35;
        vct_A.w = w;
        hModel = v25->hModel;
        mdlSetPosition(v25->hModel);
        v41 = *p_rot;
        vct_A = v41;
        mdlSetRotate(v25->hModel);
        v25->vstatus &= ~0x1000u;
      }
      v43 = sBtlGetNakama(1);
      if (!v43)
        goto LABEL_63;
      v44 = v43;
      v43->pos.x = v9->pos.x;
      v43->pos.y = v9->pos.y;
      v43->pos.z = v9->pos.z;
      v46 = wk->scene->camera->followUpAngle.x;
      v47 = sBtlGetDir180(v46);
      v48 = sBtlGetPosToDir(0.0, 0.0, 200.0, 200.0);
      v49 = sBtlGet360(v47 + v48);
      v50 = sBtlGetLenXZ(0.0, 0.0, 200.0, 200.0);
      sBtlGetMoveXZ(0.0, 0.0, v49, v50, (f32 *)&v111 + 1, &v111);
      v51 = v44->pos.y;
      v52 = v44->pos.x + *((f32 *)&v111 + 1);
      v53 = v44->pos.w;
      v54 = v44->pos.z + *(f32 *)&v111;
      v44->pos.x = v52;
      v44->pos.z = v54;
      v44->rot = v9->rot;
      v44->rot_p = v9->rot;
      v44->mv_rotbk = v9->mv_rotbk;
      v58 = &v44->rot;
      vct_A.x = v52;
      vct_A.y = v51;
      vct_A.z = v54;
      vct_A.w = v53;
      v59 = v44->hModel;
      mdlSetPosition(v44->hModel);
      v60 = *v58;
      vct_A = v60;
      mdlSetRotate(v44->hModel);
      v44->vstatus &= ~0x1000u;
      goto LABEL_63;
    }
    EncountPac = sBtlGetEncountPac(-1);
    start_playerpos = EncountPac[wk->encountno]->start_playerpos;
    mapEncPointGet(start_playerpos, (f32 *)&y + 1, &y, &z, &r);
    v13 = *(f32 *)&y;
    v9->pos.x = *((f32 *)&y + 1);
    v9->pos.y = v13;
    v9->pos.z = z;
    FromEuler(0.0, r * 0.017453292, 0.0);
    v15 = &v9->rot;
    v16 = (u8)byte_5755EF5;
    *v15 = vct_A;
    if (v16)
      goto LABEL_24;
    goto LABEL_89;
    if (v76)
    {
LABEL_24:
      goto LABEL_25;
    }
LABEL_89:
LABEL_25:
    vct_A = (struct sdfVector4_t)xmmword_3CFD5C0;
    p_rot_p = &v9->rot_p;
    v19 = (u8)byte_5755EF5;
    v9->mv_rotbk = r;
    pos = v9->pos;
    *p_rot_p = vct_A;
    if (v19)
    {
      goto LABEL_29;
    }
    else
    {
      v98 = pos;
      pos = v98;
      goto LABEL_29;
    }
    v99 = pos;
    pos = v99;
LABEL_29:
    vct_A = pos;
    v21 = v9->hModel;
    mdlSetPosition(v9->hModel);
    v22 = *v15;
    vct_A = v22;
    mdlSetRotate(v9->hModel);
    sBtlResetAction(v9);
    sBtlSetAction(v9, 1, 0);
    sBtlStatusBitOff(v9, 0xFFFFFFEF);
    goto LABEL_39;
  }
LABEL_63:
  sBtlShugouKaijyo();
  if (BYTE6(v3[3].klass) != 1)
    goto LABEL_142;
  v63 = wk;
  v64 = v63->UnitMng;
  boss_eventID = v63->boss_eventID;
  v66 = sBtlSearchUnit_ID(v64, boss_eventID);
  if (!v66)
    goto LABEL_129;
  enc_posid = v66->enc_posid;
  v68 = v66;
  if (enc_posid)
    goto LABEL_116;
  v69 = 0;
  do
  {
    v72 = sBtlGetEncountPac(-1);
    if (v69 >= SLODWORD(v72[wk->encountno]->enc1->max_length))
    {
      enc_posid = 0;
      goto LABEL_116;
    }
    v74 = sBtlGetEncountPac(-1);
    v70 = wk;
    v71 = (s64)v74[v70->encountno]->enc1 + 8 * v69++;
  }
  while (v70->boss_devilID != *(s16 *)(*(u64 *)(v71 + 32) + 22));
  v77 = sBtlGetEncountPac(-1);
  enc_posid = *(char *)(*(&v77[wk->encountno]->enc1->max_length + v69) + 20);
LABEL_116:
  p_pos = &v68->pos;
  v80 = &v68->rot;
  sBtlGetPointData(enc_posid, &v68->pos, &v68->rot);
  v106 = *p_pos;
  vct_A = v106;
  p_koteipos = &v68->koteipos;
  v83 = (u8)byte_5755EF5;
  *p_koteipos = vct_A;
  v84 = *p_pos;
  if (v83)
    goto LABEL_124;
  goto LABEL_161;
  if (v97)
  {
LABEL_124:
LABEL_125:
    vct_A = v84;
    v85 = v68->hModel;
    mdlSetPosition(v68->hModel);
    v86 = *v80;
LABEL_128:
    vct_A = v86;
    mdlSetRotate(v68->hModel);
LABEL_129:
    for (i = 0; ; ++i)
    {
      v89 = wk->UnitMng;
      if (i >= v89->number)
        goto LABEL_142;
      pUnit = v89->pUnitL[i]->pUnit;
      if (!pUnit)
        continue;
      if ((pUnit->side & 0x3F) == 2)
      {
        pUnit->vstatus &= ~0x1000u;
        sBtlStatusBitOff(pUnit, 0xFFFFFFEF);
      }
    }
    v110 = v86;
    v86 = v110;
    goto LABEL_128;
  }
LABEL_161:
  v107 = v84;
  v84 = v107;
  goto LABEL_125;
LABEL_142:
  for (j = 0; ; ++j)
  {
    v93 = wk->UnitMng;
    if (j >= v93->number)
      break;
    v94 = v93->pUnitL[j]->pUnit;
    if (!v94)
      continue;
    if ((v94->side & 2) != 0)
    {
      *(u64 *)&v94->hangeki_nokezoranai = 0xC8000000F0LL;
    }
    else if ((v94->side & 0x81) == 1)
    {
      actaiwk = v94->actaiwk;
      v96 = sub_1905740(30, 0) + 40;
      actaiwk->target_frame = v96;
    }
  }
}

// 0x1d9c2e0
static void CameraSet(void) {
  s32 *ProcessData;
  s32 *v4;
  s64 v6;
  s64 v7;
  S_CameraMoveDt *CamMovePtn;

  ProcessData = dds3GetProcessData(g_mainPID);
  v4 = ProcessData;
  v6 = ProcessData[15];
  if ((u32)v6 >= 7)
  {
    if ((u32)v6 == 7)
      v7 = 5;
    else
      v7 = 0;
    goto LABEL_18;
  }
  else
  {
    v7 = qword_3E630C0[v6];
    goto LABEL_18;
  }
LABEL_18:
  sBtlSetMode(13);
  sBtlSetCmbBfrPos();
  CamMovePtn = sBtlGetCamMovePtn(cameraInitNo[v7][*(s32 *)(*((u64 *)v4 + 11) + 32)]);
  sBtlSetMove(CamMovePtn, 1);
}

// 0x1d9c4a0
static void ReStartBattle(void) {
  SBTLUNIT_LISTWORK *tgtList;
  SBATTLE_WORK *wk_local;
  SBTLUNIT_LISTWORK *TargetList_Analyze;
  s32 i;
  SBTLUNIT_WORK *v8;
  SBATTLE_WORK *v11;
  SBTLUNIT_LISTWORK *v12;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 playerID;
  SBTLUNIT_WORK *v17;
  SBTLUNIT_WORK *v18;
  SBTLUNIT_WORK *v19;
  SBTLUNIT_LISTWORK *p_tgtList;
  SBTLUNIT_WORK *Nakama;
  SBTLUNIT_WORK *v24;
  SBTLUNIT_WORK *v25;
  SBTLUNIT_WORK *v26;
  SBATTLE_WORK *v28;

  tgtList = wk->tgtList;
  if (!tgtList)
  {
    goto LABEL_5;
  }
  sBtlDeleteUnitList(tgtList, 0);
  p_tgtList = &wk->tgtList;
  p_tgtList = 0;
LABEL_5:
  wk_local = wk;
  TargetList_Analyze = sBtlCreateTargetList_Analyze(2);
  wk_local->tgtList = TargetList_Analyze;
  for (i = 0; ; ++i)
  {
    v11 = wk;
    v12 = v11->tgtList;
    if (i >= v12->count)
      break;
    v8 = sBtlSearchUnit_ID(v12, i);
    v8->vstatus &= 0xFDFFEFFF;
  }
  UnitMng = v11->UnitMng;
  playerID = v11->playerID;
  v17 = sBtlSearchUnit_ID(UnitMng, playerID);
  v17->vstatus &= 0xFDFFEFFF;
  v18 = sBtlSearchUnit_ID(wk->UnitMng, wk->boss_eventID);
  if (v18)
  {
    v19 = v18;
    v18->vstatus &= ~0x2000000u;
    sBtlStatusBitOff(v19, 0xFFFFFFEF);
  }
  if (!wk->bNoEndCam)
  {
    Nakama = sBtlGetNakama(0);
    if (Nakama)
    {
      v24 = Nakama;
      Nakama->vstatus &= 0xFDFFEFFF;
      sBtlStatusBitOff(v24, 0xFFFFFFEF);
    }
    v25 = sBtlGetNakama(1);
    if (v25)
    {
      v26 = v25;
      v25->vstatus &= 0xFDFFEFFF;
      sBtlStatusBitOff(v26, 0xFFFFFFEF);
    }
  }
  v28 = wk;
  v28->bEffNoDraw = 0;
  v28->scrFlag &= ~0x40000u;
}

// 0x1d9c860
static TYPE_BOSS_NML_EVENT *GetTable(SBTLUNIT_WORK *unit) {
  s32 v3;
  s32 devilid;
  TYPE_BOSS_NML_EVENT *v6;
  TYPE_BOSS_NML_EVENT *v7;
  s32 enc_id;

  if (!unit)
    return 0;
  v3 = 0;
  devilid = unit->para->devilid;
  while (1)
  {
    v7 = arrBossEveTable[v3];
    if (v7->devil_id < 0)
      return 0;
    enc_id = v7->enc_id;
    if (enc_id)
    {
      if (enc_id != wk->encountno)
        goto LABEL_6;
    }
    v6 = arrBossEveTable[v3];
    if (v6->devil_id == devilid)
      break;
LABEL_6:
    ++v3;
  }
  return v6;
}

// 0x1d9ca60
s32 sBtlCheck(SBTLUNIT_WORK *unit, SBTLBOSSEVENT type, s16 skillid) {
  s32 v7;
  s32 devilid;
  s32 mag_on1;
  TYPE_BOSS_NML_EVENT *v11;
  s32 encountno;
  TYPE_BOSS_NML_EVENT *v13;
  s32 dead_on;
  s32 skill_id;
  s32 playerID;
  SBTLUNIT_WORK *PlayerUnit;
  s32 v20;
  s16 v21;

  if (unit)
  {
    v20 = skillid;
    v7 = 0;
    v21 = skillid;
    devilid = unit->para->devilid;
    while (1)
    {
      v11 = arrBossEveTable[v7];
      if (v11->devil_id == -1)
        return -1;
      if (v11->enc_id)
        goto LABEL_16;
      goto LABEL_9000;
      if (arrBossEveTable[v7]->enc_id)
      {
LABEL_16:
        encountno = wk->encountno;
        if (encountno != arrBossEveTable[v7]->enc_id)
          goto LABEL_8;
      }
LABEL_9000:
      v13 = arrBossEveTable[v7];
      switch (type)
      {
        case 0:
          v13 = arrBossEveTable[v7];
          if (!v13->start_on)
            break;
          if (wk->boss_devilID != devilid)
            return v7;
          break;
        case 1:
          mag_on1 = unit->mag_on1;
          if (mag_on1 < 0)
          {
            v13 = arrBossEveTable[v7];
            mag_on1 = v13->mag_on1;
          }
          goto LABEL_7;
        case 2:
          mag_on1 = unit->mag_on2;
          if (mag_on1 < 0)
          {
            v13 = arrBossEveTable[v7];
            mag_on1 = v13->mag_on2;
          }
          goto LABEL_7;
        case 3:
          mag_on1 = unit->mag_on3;
          if (mag_on1 < 0)
          {
            v13 = arrBossEveTable[v7];
            mag_on1 = v13->mag_on3;
          }
LABEL_7:
          if (mag_on1 < 1)
            break;
          return v7;
        case 4:
          dead_on = unit->dead_on;
          if (dead_on < 0)
          {
            v13 = arrBossEveTable[v7];
            dead_on = v13->dead_on;
          }
          if (dead_on < 1 || (dead_on & 3) == 0)
            break;
          if ((dead_on & 4) == 0)
            return v7;
          if (sBtlIsEnemyLastOne(unit))
            return v7;
          break;
        case 5:
          v13 = arrBossEveTable[v7];
          if (!v13->lose_on)
            break;
          if (v21)
          {
            v13 = arrBossEveTable[v7];
            skill_id = v13->skill_id;
            if (!skill_id)
              return v7;
            if (skill_id == v20)
              return v7;
          }
          else
          {
            playerID = wk->playerID;
            PlayerUnit = sBtlGetPlayerUnit(playerID);
            if (PlayerUnit)
            {
              if (PlayerUnit->para->now->hp < 2)
                return v7;
              if ((wk->scrFlag & 0x200000) != 0)
                return v7;
            }
          }
          break;
        case 6:
          if (v13->dying_on)
            return v7;
          break;
        case 7:
          if (v13->time_on)
            return v7;
          break;
        case 10:
          return v7;
        default:
          break;
      }
LABEL_8:
      ++v7;
    }
  }
  return -1;
}

// 0x1d9cf90
bool sBtlCheck_Start_EnemySummonWait(SBTLUNIT_WORK *unit) {
  s32 v3;
  s32 devilid;
  TYPE_BOSS_NML_EVENT *v6;
  s32 devil_id;
  s32 encountno;

  if (unit)
  {
    v3 = 0;
    devilid = unit->para->devilid;
    while (1)
    {
      v6 = arrBossEveTable[v3];
      devil_id = v6->devil_id;
      LOBYTE(unit) = devil_id != -1;
      if (devil_id == -1)
        return (char)unit;
      if (v6->enc_id)
        goto LABEL_14;
      goto LABEL_9000;
      if (arrBossEveTable[v3]->enc_id)
      {
LABEL_14:
        encountno = wk->encountno;
        if (encountno != arrBossEveTable[v3]->enc_id)
          goto LABEL_6;
      }
LABEL_9000:
      if (arrBossEveTable[v3]->devil_id == devilid)
      {
        if (arrBossEveTable[v3]->start_on == start_on_esw)
        {
          if (wk->boss_devilID != devilid)
            return (char)unit;
        }
      }
LABEL_6:
      ++v3;
    }
  }
  return (char)unit;
}

// 0x1d9d190
s32 sBtlCheck_StartLoad(void) {
  s32 i;
  s32 encountno;
  TYPE_BOSS_NML_EVENT *v6;
  SB_ENCOUNTPAC *EncountPac;

  for (i = 0; ; ++i)
  {
    if (arrBossEveTable[i]->devil_id == -1)
      break;
    encountno = wk->encountno;
    if (!encountno)
      continue;
    v6 = arrBossEveTable[i];
    if (encountno != v6->enc_id)
      continue;
    if (!v6->start_on)
      continue;
    EncountPac = sBtlGetEncountPac(-1);
    if ((EncountPac[wk->encountno]->flag & 0x20) != 0)
      return i;
  }
  return -1;
}

// 0x1d9d380
static dds3ProcessFunc_t Process(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  void *Instance;
  void *v6;
  void *v7;
  SBATTLE_WORK *wk_local;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 boss_eventID;
  s32 devilid;
  SBATTLE_WORK *v14;
  s32 scrFlag;
  char *v18;
  void *Asset;
  sdfBinary *v23;
  u8 *data;
  SBATTLE_WORK *v27;
  u32 v29;
  SBATTLE_WORK *v30;
  u32 status2;
  u32 v32;
  u32 status4;
  u32 status;
  dds3ProcessFunc_t v35;
  s32 v36;
  s32 v39;
  s32 v40;
  SBATTLE_WORK *v42;
  s32 v43;
  void *v44;
  void *v45;
  void *v46;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
  switch (LODWORD(ProcessData[3].klass))
  {
    case 0:
      Instance = get_Instance(0);
      CharaIconActive(Instance, 0, 0);
      v6 = get_Instance(0);
      AllInOut(v6, 0, 1, 1, 1, 0);
      v7 = get_Instance(0);
      DevilHPactive(v7, 0, 0);
      StopBattle();
      wk_local = wk;
      *(u16 *)&wk_local->bosseveloadflg = 256;
      UnitMng = wk_local->UnitMng;
      boss_eventID = wk_local->boss_eventID;
      devilid = sBtlSearchUnit_ID(UnitMng, boss_eventID)->para->devilid;
      v14 = wk;
      v14->boss_devilID = devilid;
      scrFlag = v14->scrFlag;
      v14->effNoStop = 1;
      v14->kaiwa_gstat = 0;
      v14->scrFlag = scrFlag | 0x80000;
      v14->status2 |= 0x20u;
      LOWORD(ProcessData[4].klass) = 0;
      LODWORD(ProcessData[3].klass) = 1;
      g_bosseventhpflg = 0;
      return 0;
    case 1:
      if (sBtlCheckSummon_LoadExecOk(0))
      {
        LODWORD(ProcessData[3].klass) = 2;
        v18 = "bossevent";
        Load(Dependent, v18, v18);
        LoadSyncAll(_Ctrl_k__BackingField, 0);
        Create(0);
        fclLoadData("btlbossevent.bmd", v18, 1);
        Reset(0);
        Asset = LoadAsset(_Ctrl_k__BackingField, "battle", "boss_scr.bf", 0);
        v23 = Allocate(sdfBinary);
        _ctor(v23, Asset, 0);
        data = v23->data;
        ProcessData[1].monitor = data;
        Unload(Dependent, v18, 0);
        return 0;
      }
      return 0;
    case 2:
      LOWORD(ProcessData[4].klass) = 0;
      v27 = wk;
      v27->status4 &= ~0x20000u;
      v27->status2 |= 0x80u;
      LODWORD(ProcessData[3].klass) = 3;
      return 0;
    case 3:
      switch (HIDWORD(ProcessData[3].monitor))
      {
        case 0:
          v36 = *((u32 *)ProcessData[5].monitor + 10);
          if (v36 == 4)
          {
            if (!BattleStartApo_Effect())
              goto LABEL_95;
            return 0;
          }
          if (v36 == 2)
          {
            HIDWORD(ProcessData[3].monitor) = 8;
            goto LABEL_65;
          }
          if (v36 == start_on_r1)
            goto LABEL_120;
          v39 = *((u32 *)ProcessData[5].monitor + 10);
          if (v39 == start_on_tips)
          {
            if (!sBtlTips())
              goto LABEL_95;
            return 0;
          }
          v40 = *((u32 *)ProcessData[5].monitor + 10);
          if (v40 == start_on_esw)
          {
LABEL_120:
            if (!sBtlEffectPreMenu())
              goto LABEL_95;
          }
          else if (!sBtlEffect())
          {
            goto LABEL_95;
          }
          break;
        case 1:
        case 2:
        case 3:
          if (!BattleMag_Effect())
            goto LABEL_95;
          break;
        case 4:
          if (!BattleDead_Effect())
            goto LABEL_95;
          break;
        case 5:
          if (!BattleLose_Effect())
            goto LABEL_95;
          break;
        case 6:
          if (!BattleDying_Effect())
            goto LABEL_95;
          break;
        case 7:
          if (!BattleTime_Effect())
            goto LABEL_95;
          break;
        case 8:
LABEL_65:
          if (!BattleSummon_Effect())
            goto LABEL_95;
          break;
        case 9:
          if (!BattleRestart_Effect())
            goto LABEL_95;
          break;
        case 0xA:
          if (!BattleRaidoDying_Effect())
            goto LABEL_95;
          break;
        case 0xB:
          if (!sBtlTalkEvent())
            goto LABEL_95;
          break;
        default:
LABEL_95:
          v42 = wk;
          v43 = v42->scrFlag;
          v42->effNoStop = 0;
          v42->scrFlag = v43 & 0xFFF7FFFF;
          if (*((u32 *)ProcessData[5].monitor + 10) != 3 || HIDWORD(ProcessData[3].monitor))
          {
            v44 = get_Instance(0);
            CharaIconActive(v44, 1, 0);
            v45 = get_Instance(0);
            AllInOut(v45, 1, 1, 1, 1, 0);
            v46 = get_Instance(0);
            DevilHPactive(v46, 1, 0);
            ReStartBattle();
            if (!BYTE5(ProcessData[3].klass))
            {
              RestartBattle();
            }
          }
          LODWORD(ProcessData[3].klass) = 4;
          wk->status2 &= ~0x80u;
          fclEndMessage();
          break;
      }
      return 0;
    case 4:
      if (HIDWORD(ProcessData[3].monitor) != 4)
      {
        wk->boss_eventID = 0;
      }
      v30 = wk;
      v30->bBfrBtlEnd = 1;
      status2 = v30->status2;
      v30->bosseventflg = 0;
      v32 = status2 & 0xFFFFFFCD;
      status4 = v30->status4;
      v30->status2 = v32;
      v30->status4 = status4 & 0xFFFCFFFF;
      if (!v29)
      {
        v30 = wk;
        v32 = v30->status2;
      }
      if ((v32 & 0x100000) == 0 && BYTE5(ProcessData[3].klass) == 1)
      {
        v30 = wk;
        v32 = v30->status2;
        status = v30->status;
        v30->bBfrBtlEnd = 0;
        v30->status = status | 0x80000000;
        v30->status2 = v32 | 0x80000;
        RestartBattle();
        sBtlSetStartEx(1);
      }
      v35 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
      _ctor(v35, 0, Method_Project_Kernel_DDS3_PROC_END__, 0);
      return v35;
    default:
      return 0;
  }
}

// 0x1d9fb60
static void Shutdown(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  Delete(0);
  if (ProcessData[2].monitor)
  {
    dds3KillProcess(&ProcessData[2].monitor, 0);
    ProcessData[2].monitor = 0;
  }
  ProcessData[1].monitor = 0;
  g_mainPID = 0;
}

// 0x1d9fcd0
void sBtlProcessStart(SBTLBOSSEVENT type, s16 eventno) {
  sBtlBossEvent_t *v5;
  dds3ProcessFunc_t v6;
  shutdownfuncDelegate v7;
  dds3ProcessID_t *started;
  TYPE_BOSS_NML_EVENT *v11;

  v5 = Allocate(sBtlBossEvent_t);
  v6 = Allocate(dds3ProcessFunc_t);
  _ctor(v6, 0, Method_Project_sBtlBossEvent_Process__, 0);
  v7 = Allocate(shutdownfuncDelegate);
  _ctor(v7, 0, Method_Project_sBtlBossEvent_Shutdown__, 0);
  started = dds3StartProcess("sbtlbossevent_main", 1023, 0, 0, v6, v7, v5);
  g_mainPID = started;
  v11 = arrBossEveTable[eventno];
  v5->pTypeBossNmlEvent = v11;
  v5->eventtype = type;
  if (type == 11)
    v5->bossTalkType = eventno;
  *(u16 *)&v5->end_mode = 0;
  v5->step = 0;
  wk->status4 |= 0x10000u;
  StopBattle();
}

// 0x1d9ff20
bool sBtlProcessCheck(void) {
  if (!g_mainPID)
    return 0;
  if (dds3GetProcessStat(g_mainPID) != 3)
  {
    if (dds3GetProcessStat(g_mainPID))
    {
      return !preMenuEvent;
    }
  }
  g_mainPID = 0;
  return 0;
}

// 0x1da00c0
bool sBtlCheckDeadEventMag(SBTLUNIT_WORK *a_pBtlUnit) {
  s32 dead_on;
  TYPE_BOSS_NML_EVENT *Table;
  bool v5;
  s32 v6;

  if (!a_pBtlUnit)
  {
    LOBYTE(Table) = 0;
    return (char)Table;
  }
  dead_on = a_pBtlUnit->dead_on;
  if ((dead_on & 0x80000000) == 0)
    goto LABEL_9;
  Table = GetTable(a_pBtlUnit);
  if (Table)
  {
    dead_on = Table->dead_on;
LABEL_9:
    v5 = dead_on < 1;
    v6 = ((u32)dead_on >> 3) & 1;
    if (v5)
      LOBYTE(Table) = 0;
    else
      LOBYTE(Table) = v6;
  }
  return (char)Table;
}

// 0x1da0150
void datLoadTable(void) {
  void *lbl_mag1;
  void *lbl_mag2;
  void *lbl_mag3;
  void *lbl_dead;
  void *lbl_lose;
  void *lbl_dying;
  void *lbl_time;
  void *lbl_sum;
  void *lbl_restart;
  TYPE_BOSS_NML_EVENT *v11;
  void *v12;
  void *v13;
  void *v14;
  void *v15;
  void *v16;
  void *v17;
  void *v18;
  void *v19;
  void *v20;
  TYPE_BOSS_NML_EVENT *v21;
  void *v22;
  void *v23;
  void *v24;
  void *v25;
  void *v26;
  void *v27;
  void *v28;
  void *v29;
  void *v30;
  TYPE_BOSS_NML_EVENT *v31;
  void *v32;
  void *v33;
  void *v34;
  void *v35;
  void *v36;
  void *v37;
  void *v38;
  void *v39;
  void *v40;
  TYPE_BOSS_NML_EVENT *v41;
  void *v42;
  void *v43;
  void *v44;
  void *v45;
  void *v46;
  void *v47;
  void *v48;
  void *v49;
  void *v50;
  TYPE_BOSS_NML_EVENT *v51;
  void *v52;
  void *v53;
  void *v54;
  void *v55;
  void *v56;
  void *v57;
  void *v58;
  void *v59;
  void *v60;
  TYPE_BOSS_NML_EVENT *v61;
  void *v62;
  void *v63;
  void *v64;
  void *v65;
  void *v66;
  void *v67;
  void *v68;
  void *v69;
  void *v70;
  TYPE_BOSS_NML_EVENT *v71;
  void *v72;
  void *v73;
  void *v74;
  void *v75;
  void *v76;
  void *v77;
  void *v78;
  void *v79;
  void *v80;
  TYPE_BOSS_NML_EVENT *v81;
  void *v82;
  void *v83;
  void *v84;
  void *v85;
  void *v86;
  void *v87;
  void *v88;
  void *v89;
  void *v90;
  TYPE_BOSS_NML_EVENT *v91;
  void *v92;
  void *v93;
  void *v94;
  void *v95;
  void *v96;
  void *v97;
  void *v98;
  void *v99;
  void *v100;
  TYPE_BOSS_NML_EVENT *v101;
  void *v102;
  void *v103;
  void *v104;
  void *v105;
  void *v106;
  void *v107;
  void *v108;
  void *v109;
  void *v110;
  TYPE_BOSS_NML_EVENT *v111;
  void *v112;
  void *v113;
  void *v114;
  void *v115;
  void *v116;
  void *v117;
  void *v118;
  void *v119;
  void *v120;
  TYPE_BOSS_NML_EVENT *v121;
  void *v122;
  void *v123;
  void *v124;
  void *v125;
  void *v126;
  void *v127;
  void *v128;
  void *v129;
  void *v130;
  TYPE_BOSS_NML_EVENT *v131;
  void *v132;
  void *v133;
  void *v134;
  void *v135;
  void *v136;
  void *v137;
  void *v138;
  void *v139;
  void *v140;
  TYPE_BOSS_NML_EVENT *v141;
  void *v142;
  void *v143;
  void *v144;
  void *v145;
  void *v146;
  void *v147;
  void *v148;
  void *v149;
  void *v150;
  TYPE_BOSS_NML_EVENT *v151;
  void *v152;
  void *v153;
  void *v154;
  void *v155;
  void *v156;
  void *v157;
  void *v158;
  void *v159;
  void *v160;
  TYPE_BOSS_NML_EVENT *v161;
  void *v162;
  void *v163;
  void *v164;
  void *v165;
  void *v166;
  void *v167;
  void *v168;
  void *v169;
  void *v170;
  TYPE_BOSS_NML_EVENT *v171;
  void *v172;
  void *v173;
  void *v174;
  void *v175;
  void *v176;
  void *v177;
  void *v178;
  void *v179;
  void *v180;
  TYPE_BOSS_NML_EVENT *v181;
  void *v182;
  void *v183;
  void *v184;
  void *v185;
  void *v186;
  void *v187;
  void *v188;
  void *v189;
  void *v190;
  TYPE_BOSS_NML_EVENT *v191;
  void *v192;
  void *v193;
  void *v194;
  void *v195;
  void *v196;
  void *v197;
  void *v198;
  void *v199;
  void *v200;
  TYPE_BOSS_NML_EVENT *v201;
  void *v202;
  void *v203;
  void *v204;
  void *v205;
  void *v206;
  void *v207;
  void *v208;
  void *v209;
  void *v210;
  TYPE_BOSS_NML_EVENT *v211;
  void *v212;
  void *v213;
  void *v214;
  void *v215;
  void *v216;
  void *v217;
  void *v218;
  void *v219;
  void *v220;
  TYPE_BOSS_NML_EVENT *v221;
  void *v222;
  void *v223;
  void *v224;
  void *v225;
  void *v226;
  void *v227;
  void *v228;
  void *v229;
  void *v230;
  TYPE_BOSS_NML_EVENT *v231;
  void *v232;
  void *v233;
  void *v234;
  void *v235;
  void *v236;
  void *v237;
  void *v238;
  void *v239;
  void *v240;
  TYPE_BOSS_NML_EVENT *v241;
  void *v242;
  void *v243;
  void *v244;
  void *v245;
  void *v246;
  void *v247;
  void *v248;
  void *v249;
  void *v250;
  TYPE_BOSS_NML_EVENT *v251;
  void *v252;
  void *v253;
  void *v254;
  void *v255;
  void *v256;
  void *v257;
  void *v258;
  void *v259;
  void *v260;
  TYPE_BOSS_NML_EVENT *v261;
  void *v262;
  void *v263;
  void *v264;
  void *v265;
  void *v266;
  void *v267;
  void *v268;
  void *v269;
  void *v270;
  TYPE_BOSS_NML_EVENT *v271;
  void *v272;
  void *v273;
  void *v274;
  void *v275;
  void *v276;
  void *v277;
  void *v278;
  void *v279;
  void *v280;
  TYPE_BOSS_NML_EVENT *v281;
  void *v282;
  void *v283;
  void *v284;
  void *v285;
  void *v286;
  void *v287;
  void *v288;
  void *v289;
  void *v290;
  TYPE_BOSS_NML_EVENT *v291;
  void *v292;
  void *v293;
  void *v294;
  void *v295;
  void *v296;
  void *v297;
  void *v298;
  void *v299;
  void *v300;
  TYPE_BOSS_NML_EVENT *v301;
  void *v302;
  void *v303;
  void *v304;
  void *v305;
  void *v306;
  void *v307;
  void *v308;
  void *v309;
  void *v310;
  TYPE_BOSS_NML_EVENT *v311;
  void *v312;
  void *v313;
  void *v314;
  void *v315;
  void *v316;
  void *v317;
  void *v318;
  void *v319;
  void *v320;
  TYPE_BOSS_NML_EVENT *v321;
  void *v322;
  void *v323;
  void *v324;
  void *v325;
  void *v326;
  void *v327;
  void *v328;
  void *v329;
  void *v330;
  TYPE_BOSS_NML_EVENT *v331;
  void *v332;
  void *v333;
  void *v334;
  void *v335;
  void *v336;
  void *v337;
  void *v338;
  void *v339;
  void *lbl_Tips;
  TYPE_BOSS_NML_EVENT *v341;
  void *v342;
  void *v343;
  void *v344;
  void *v345;
  void *v346;
  void *v347;
  void *v348;
  void *v349;
  void *v350;
  TYPE_BOSS_NML_EVENT *v351;
  void *v352;
  void *v353;
  void *v354;
  void *v355;
  void *v356;
  void *v357;
  void *v358;
  void *v359;
  void *v360;
  TYPE_BOSS_NML_EVENT *v361;
  void *v362;
  void *v363;
  void *v364;
  void *v365;
  void *v366;
  void *v367;
  void *v368;
  void *v369;
  void *v370;
  TYPE_BOSS_NML_EVENT *v371;
  void *v372;
  void *v373;
  void *v374;
  void *v375;
  void *v376;
  void *v377;
  void *v378;
  void *v379;
  void *v380;
  TYPE_BOSS_NML_EVENT *v381;
  void *v382;
  void *v383;
  void *v384;
  void *v385;
  void *v386;
  void *v387;
  void *v388;
  void *v389;
  void *v390;
  TYPE_BOSS_NML_EVENT *v391;
  void *v392;
  void *v393;
  void *v394;
  void *v395;
  void *v396;
  void *v397;
  void *v398;
  void *v399;
  void *v400;
  TYPE_BOSS_NML_EVENT *v401;
  void *v402;
  void *v403;
  void *v404;
  void *v405;
  void *v406;
  void *v407;
  void *v408;
  void *v409;
  void *v410;
  TYPE_BOSS_NML_EVENT *v411;
  void *v412;
  void *v413;
  void *v414;
  void *v415;
  void *v416;
  void *v417;
  void *v418;
  void *v419;
  void *v420;
  TYPE_BOSS_NML_EVENT *v421;
  void *v424;
  void *v425;
  void *lbl_start;
  void *v427;
  void *v428;
  void *v429;
  void *v430;
  void *v431;
  void *v432;
  void *v433;
  void *v434;
  void *v435;
  void *v436;
  void *v437;
  void *v438;
  void *v439;
  void *v440;
  void *v441;
  void *v442;
  void *v443;
  void *v444;
  void *v445;
  void *v446;
  void *v447;
  void *v448;
  void *v449;
  void *v450;
  void *v451;
  void *v452;
  void *v453;
  void *v454;
  void *v455;
  void *v456;
  void *v457;
  void *v458;
  void *v459;
  void *v460;
  void *v461;
  void *v462;
  void *v463;
  void *v464;
  void *v465;
  void *v466;
  s32 v468;
  s32 v469;
  s32 v470;
  s32 v471;
  s32 v472;
  s32 v473;
  s32 v474;
  s32 v475;
  s32 v476;
  s32 v477;
  s32 v478;
  s32 v479;
  s32 v480;
  s32 v481;
  s32 v482;
  s32 v483;
  s32 v484;
  s32 v485;
  s32 v486;
  s32 v487;
  s32 v488;
  s32 v489;
  s32 v490;
  s32 v491;
  s32 v492;
  s32 v493;
  s32 v494;
  s32 v495;
  s32 v496;
  s32 v498;
  s32 v499;
  s32 *v500;
  s32 v501;
  s32 v502;
  void *v503;
  s32 v505;
  s32 v506;
  s32 v507;
  void *v508;
  TYPE_BOSS_NML_EVENT *v509;

  v509 = NewSpecific(TYPE_BOSS_NML_EVENT, 0x2Au);
  lbl_start = NewSpecific(s32, 3u);
  InitializeArray_55364416(lbl_start, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  lbl_mag1 = NewSpecific(s32, 3u);
  InitializeArray_55364416(lbl_mag1, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  lbl_mag2 = NewSpecific(s32, 3u);
  InitializeArray_55364416(lbl_mag2, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  lbl_mag3 = NewSpecific(s32, 3u);
  InitializeArray_55364416(lbl_mag3, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  lbl_dead = NewSpecific(s32, 3u);
  InitializeArray_55364416(lbl_dead, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  lbl_lose = NewSpecific(s32, 3u);
  InitializeArray_55364416(lbl_lose, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  lbl_dying = NewSpecific(s32, 3u);
  InitializeArray_55364416(lbl_dying, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  lbl_time = NewSpecific(s32, 3u);
  InitializeArray_55364416(lbl_time, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  lbl_sum = NewSpecific(s32, 3u);
  InitializeArray_55364416(lbl_sum, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  lbl_restart = NewSpecific(s32, 3u);
  InitializeArray_55364416(lbl_restart, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v11 = Allocate(TYPE_BOSS_NML_EVENT);
  _ctor_31277632(v11, 26, 278, 2, -1, 0, 0, start_on_r1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 4, 1, lbl_start, lbl_mag1, lbl_mag2, lbl_mag3, lbl_dead, lbl_lose, lbl_dying, lbl_time, lbl_sum, lbl_restart, 0);
  v509[0] = v11;
  v468 = start_on_r1;
  v427 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v427, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v12 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v12, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v13 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v13, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v14 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v14, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v15 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v15, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v16 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v16, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v17 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v17, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v18 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v18, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v19 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v19, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v20 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v20, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v21 = Allocate(TYPE_BOSS_NML_EVENT);
  _ctor_31277632(v21, 449, 117, 1, -1, 0, 0, v468, 0, 0, 0, 0, 0, 0, 0, 1, 1, 4, 1, v427, v12, v13, v14, v15, v16, v17, v18, v19, v20, 0);
  v509[1] = v21;
  v469 = start_on_r1;
  v428 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v428, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v22 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v22, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v23 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v23, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v24 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v24, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v25 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v25, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v26 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v26, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v27 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v27, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v28 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v28, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v29 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v29, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v30 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v30, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v31 = Allocate(TYPE_BOSS_NML_EVENT);
  _ctor_31277632(v31, 22, 164, 1, 0, 0, 0, v469, 0, 0, 0, 0, 0, 0, 0, 1, 1, 4, 1, v428, v22, v23, v24, v25, v26, v27, v28, v29, v30, 0);
  v509[2] = v31;
  v470 = start_on_r1;
  v429 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v429, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v32 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v32, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v33 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v33, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v34 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v34, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v35 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v35, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v36 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v36, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v37 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v37, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v38 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v38, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v39 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v39, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v40 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v40, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v41 = Allocate(TYPE_BOSS_NML_EVENT);
  _ctor_31277632(v41, 23, 316, 1, -1, 0, 0, v470, 0, 0, 0, 0, 0, 0, 0, 1, 1, 4, 1, v429, v32, v33, v34, v35, v36, v37, v38, v39, v40, 0);
  v509[3] = v41;
  v471 = start_on_r1;
  v430 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v430, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v42 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v42, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v43 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v43, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v44 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v44, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v45 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v45, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v46 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v46, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v47 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v47, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v48 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v48, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v49 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v49, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v50 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v50, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v51 = Allocate(TYPE_BOSS_NML_EVENT);
  _ctor_31277632(v51, 24, 165, 1, 0, 0, 0, v471, 0, 0, 0, 0, 0, 0, 0, 1, 1, 4, 1, v430, v42, v43, v44, v45, v46, v47, v48, v49, v50, 0);
  v509[4] = v51;
  v472 = start_on_r1;
  v431 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v431, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v52 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v52, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v53 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v53, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v54 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v54, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v55 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v55, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v56 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v56, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v57 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v57, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v58 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v58, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v59 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v59, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v60 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v60, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v61 = Allocate(TYPE_BOSS_NML_EVENT);
  _ctor_31277632(v61, 48, 290, 1, 0, 0, 0, v472, 0, 0, 0, 0, 0, 0, 0, 1, 1, 4, 1, v431, v52, v53, v54, v55, v56, v57, v58, v59, v60, 0);
  v509[5] = v61;
  v473 = start_on_r1;
  v432 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v432, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v62 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v62, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v63 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v63, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v64 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v64, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v65 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v65, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v66 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v66, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v67 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v67, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v68 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v68, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v69 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v69, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v70 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v70, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v71 = Allocate(TYPE_BOSS_NML_EVENT);
  _ctor_31277632(v71, 28, 281, 2, 0, 0, 0, v473, 0, 0, 0, 0, 0, 0, 0, 1, 1, 4, 1, v432, v62, v63, v64, v65, v66, v67, v68, v69, v70, 0);
  v509[6] = v71;
  v474 = start_on_r1;
  v433 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v433, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v72 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v72, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v73 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v73, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v74 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v74, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v75 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v75, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v76 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v76, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v77 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v77, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v78 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v78, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v79 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v79, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v80 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v80, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v81 = Allocate(TYPE_BOSS_NML_EVENT);
  _ctor_31277632(v81, 29, 183, 1, 0, 0, 0, v474, 0, 0, 0, 0, 0, 0, 0, 1, 1, 4, 1, v433, v72, v73, v74, v75, v76, v77, v78, v79, v80, 0);
  v509[7] = v81;
  v475 = start_on_r1;
  v434 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v434, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v82 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v82, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v83 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v83, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v84 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v84, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v85 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v85, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v86 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v86, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v87 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v87, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v88 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v88, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v89 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v89, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v90 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v90, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v91 = Allocate(TYPE_BOSS_NML_EVENT);
  _ctor_31277632(v91, 30, 273, 1, 0, 0, 0, v475, 0, 0, 0, 0, 0, 0, 0, 1, 1, 4, 1, v434, v82, v83, v84, v85, v86, v87, v88, v89, v90, 0);
  v509[8] = v91;
  v476 = start_on_r1;
  v435 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v435, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v92 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v92, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v93 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v93, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v94 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v94, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v95 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v95, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v96 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v96, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v97 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v97, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v98 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v98, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v99 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v99, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v100 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v100, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v101 = Allocate(TYPE_BOSS_NML_EVENT);
  _ctor_31277632(v101, 34, 289, 1, 0, 0, 0, v476, 0, 0, 0, 0, 0, 0, 0, 1, 1, 4, 1, v435, v92, v93, v94, v95, v96, v97, v98, v99, v100, 0);
  v509[9] = v101;
  v477 = start_on_r1;
  v436 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v436, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v102 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v102, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v103 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v103, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v104 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v104, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v105 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v105, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v106 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v106, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v107 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v107, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v108 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v108, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v109 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v109, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v110 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v110, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v111 = Allocate(TYPE_BOSS_NML_EVENT);
  _ctor_31277632(v111, 36, 174, 1, 0, 0, 0, v477, 0, 0, 0, 0, 0, 0, 0, 1, 1, 4, 1, v436, v102, v103, v104, v105, v106, v107, v108, v109, v110, 0);
  v509[10] = v111;
  v478 = start_on_r1;
  v437 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v437, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v112 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v112, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v113 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v113, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v114 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v114, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v115 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v115, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v116 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v116, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v117 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v117, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v118 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v118, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v119 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v119, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v120 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v120, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v121 = Allocate(TYPE_BOSS_NML_EVENT);
  _ctor_31277632(v121, 38, 176, 1, 0, 0, 0, v478, 0, 0, 0, 0, 0, 0, 0, 1, 1, 4, 1, v437, v112, v113, v114, v115, v116, v117, v118, v119, v120, 0);
  v509[11] = v121;
  v479 = start_on_r1;
  v438 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v438, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v122 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v122, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v123 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v123, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v124 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v124, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v125 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v125, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v126 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v126, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v127 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v127, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v128 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v128, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v129 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v129, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v130 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v130, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v131 = Allocate(TYPE_BOSS_NML_EVENT);
  _ctor_31277632(v131, 40, 168, 1, 0, 0, 0, v479, 0, 0, 0, 0, 0, 0, 0, 1, 1, 4, 1, v438, v122, v123, v124, v125, v126, v127, v128, v129, v130, 0);
  v509[12] = v131;
  v480 = start_on_r1;
  v439 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v439, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v132 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v132, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v133 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v133, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v134 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v134, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v135 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v135, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v136 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v136, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v137 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v137, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v138 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v138, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v139 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v139, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v140 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v140, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v141 = Allocate(TYPE_BOSS_NML_EVENT);
  _ctor_31277632(v141, 41, 267, 1, 0, 0, 0, v480, 0, 0, 0, 0, 0, 0, 0, 1, 1, 4, 1, v439, v132, v133, v134, v135, v136, v137, v138, v139, v140, 0);
  v509[13] = v141;
  v481 = start_on_r1;
  v440 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v440, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v142 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v142, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v143 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v143, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v144 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v144, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v145 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v145, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v146 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v146, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v147 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v147, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v148 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v148, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v149 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v149, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v150 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v150, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v151 = Allocate(TYPE_BOSS_NML_EVENT);
  _ctor_31277632(v151, 45, 264, 1, 0, 0, 0, v481, 0, 0, 0, 0, 0, 0, 0, 1, 1, 4, 1, v440, v142, v143, v144, v145, v146, v147, v148, v149, v150, 0);
  v509[14] = v151;
  v482 = start_on_r1;
  v441 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v441, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v152 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v152, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v153 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v153, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v154 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v154, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v155 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v155, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v156 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v156, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v157 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v157, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v158 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v158, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v159 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v159, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v160 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v160, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v161 = Allocate(TYPE_BOSS_NML_EVENT);
  _ctor_31277632(v161, 46, 268, 2, -1, 0, 0, v482, 0, 0, 0, 0, 0, 0, 0, 1, 1, 4, 1, v441, v152, v153, v154, v155, v156, v157, v158, v159, v160, 0);
  v509[15] = v161;
  v483 = start_on_r1;
  v442 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v442, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v162 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v162, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v163 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v163, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v164 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v164, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v165 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v165, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v166 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v166, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v167 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v167, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v168 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v168, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v169 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v169, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v170 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v170, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v171 = Allocate(TYPE_BOSS_NML_EVENT);
  _ctor_31277632(v171, 47, 178, 1, 0, 0, 0, v483, 0, 0, 0, 0, 0, 0, 0, 1, 1, 4, 1, v442, v162, v163, v164, v165, v166, v167, v168, v169, v170, 0);
  v509[16] = v171;
  v484 = start_on_r1;
  v443 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v443, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v172 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v172, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v173 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v173, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v174 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v174, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v175 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v175, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v176 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v176, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v177 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v177, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v178 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v178, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v179 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v179, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v180 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v180, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v181 = Allocate(TYPE_BOSS_NML_EVENT);
  _ctor_31277632(v181, 50, 291, 1, 0, 0, 0, v484, 0, 0, 0, 0, 0, 0, 0, 1, 1, 4, 1, v443, v172, v173, v174, v175, v176, v177, v178, v179, v180, 0);
  v509[17] = v181;
  v485 = start_on_r1;
  v444 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v444, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v182 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v182, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v183 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v183, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v184 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v184, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v185 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v185, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v186 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v186, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v187 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v187, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v188 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v188, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v189 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v189, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v190 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v190, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v191 = Allocate(TYPE_BOSS_NML_EVENT);
  _ctor_31277632(v191, 51, 292, 1, 0, 0, 0, v485, 0, 0, 0, 0, 0, 0, 0, 1, 1, 4, 1, v444, v182, v183, v184, v185, v186, v187, v188, v189, v190, 0);
  v509[18] = v191;
  v486 = start_on_r1;
  v445 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v445, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v192 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v192, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v193 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v193, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v194 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v194, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v195 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v195, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v196 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v196, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v197 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v197, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v198 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v198, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v199 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v199, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v200 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v200, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v201 = Allocate(TYPE_BOSS_NML_EVENT);
  _ctor_31277632(v201, 52, 297, 1, 0, 0, 0, v486, 0, 0, 0, 0, 0, 0, 0, 1, 1, 4, 1, v445, v192, v193, v194, v195, v196, v197, v198, v199, v200, 0);
  v509[19] = v201;
  v487 = start_on_r1;
  v446 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v446, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v202 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v202, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v203 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v203, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v204 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v204, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v205 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v205, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v206 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v206, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v207 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v207, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v208 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v208, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v209 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v209, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v210 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v210, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v211 = Allocate(TYPE_BOSS_NML_EVENT);
  _ctor_31277632(v211, 55, 305, 2, -1, 0, 0, v487, 0, 0, 0, 0, 0, 0, 0, 1, 1, 4, 1, v446, v202, v203, v204, v205, v206, v207, v208, v209, v210, 0);
  v509[20] = v211;
  v488 = start_on_r1;
  v447 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v447, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v212 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v212, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v213 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v213, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v214 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v214, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v215 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v215, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v216 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v216, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v217 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v217, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v218 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v218, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v219 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v219, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v220 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v220, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v221 = Allocate(TYPE_BOSS_NML_EVENT);
  _ctor_31277632(v221, 56, 306, 1, 0, 0, 0, v488, 0, 0, 0, 0, 0, 0, 0, 1, 1, 4, 1, v447, v212, v213, v214, v215, v216, v217, v218, v219, v220, 0);
  v509[21] = v221;
  v489 = start_on_r1;
  v448 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v448, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v222 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v222, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v223 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v223, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v224 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v224, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v225 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v225, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v226 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v226, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v227 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v227, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v228 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v228, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v229 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v229, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v230 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v230, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v231 = Allocate(TYPE_BOSS_NML_EVENT);
  _ctor_31277632(v231, 57, 310, 1, 0, 0, 0, v489, 0, 0, 0, 0, 0, 0, 0, 1, 1, 4, 1, v448, v222, v223, v224, v225, v226, v227, v228, v229, v230, 0);
  v509[22] = v231;
  v490 = start_on_r1;
  v449 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v449, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v232 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v232, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v233 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v233, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v234 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v234, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v235 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v235, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v236 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v236, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v237 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v237, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v238 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v238, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v239 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v239, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v240 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v240, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v241 = Allocate(TYPE_BOSS_NML_EVENT);
  _ctor_31277632(v241, 59, 258, 1, 0, 0, 0, v490, 0, 0, 0, 0, 0, 0, 0, 1, 1, 4, 1, v449, v232, v233, v234, v235, v236, v237, v238, v239, v240, 0);
  v509[23] = v241;
  v491 = start_on_r1;
  v450 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v450, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v242 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v242, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v243 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v243, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v244 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v244, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v245 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v245, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v246 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v246, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v247 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v247, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v248 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v248, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v249 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v249, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v250 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v250, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v251 = Allocate(TYPE_BOSS_NML_EVENT);
  _ctor_31277632(v251, 60, 259, 1, 0, 0, 0, v491, 0, 0, 0, 0, 0, 0, 0, 1, 1, 4, 1, v450, v242, v243, v244, v245, v246, v247, v248, v249, v250, 0);
  v509[24] = v251;
  v492 = start_on_r1;
  v451 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v451, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v252 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v252, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v253 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v253, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v254 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v254, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v255 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v255, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v256 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v256, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v257 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v257, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v258 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v258, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v259 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v259, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v260 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v260, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v261 = Allocate(TYPE_BOSS_NML_EVENT);
  _ctor_31277632(v261, 199, 145, 1, 0, 0, 0, v492, 0, 0, 0, 0, 0, 0, 0, 1, 1, 4, 1, v451, v252, v253, v254, v255, v256, v257, v258, v259, v260, 0);
  v509[25] = v261;
  v493 = start_on_r1;
  v452 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v452, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v262 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v262, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v263 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v263, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v264 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v264, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v265 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v265, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v266 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v266, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v267 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v267, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v268 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v268, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v269 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v269, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v270 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v270, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v271 = Allocate(TYPE_BOSS_NML_EVENT);
  _ctor_31277632(v271, 493, 145, 1, 0, 0, 0, v493, 0, 0, 0, 0, 0, 0, 0, 1, 1, 4, 1, v452, v262, v263, v264, v265, v266, v267, v268, v269, v270, 0);
  v509[26] = v271;
  v494 = start_on_r1;
  v453 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v453, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v272 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v272, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v273 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v273, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v274 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v274, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v275 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v275, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v276 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v276, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v277 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v277, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v278 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v278, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v279 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v279, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v280 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v280, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v281 = Allocate(TYPE_BOSS_NML_EVENT);
  _ctor_31277632(v281, 494, 145, 1, 0, 0, 0, v494, 0, 0, 0, 0, 0, 0, 0, 1, 1, 4, 1, v453, v272, v273, v274, v275, v276, v277, v278, v279, v280, 0);
  v509[27] = v281;
  v495 = start_on_r1;
  v454 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v454, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v282 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v282, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v283 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v283, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v284 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v284, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v285 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v285, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v286 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v286, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v287 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v287, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v288 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v288, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v289 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v289, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v290 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v290, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v291 = Allocate(TYPE_BOSS_NML_EVENT);
  _ctor_31277632(v291, 495, 145, 1, 0, 0, 0, v495, 0, 0, 0, 0, 0, 0, 0, 1, 1, 4, 1, v454, v282, v283, v284, v285, v286, v287, v288, v289, v290, 0);
  v509[28] = v291;
  v496 = start_on_r1;
  v455 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v455, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v292 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v292, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v293 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v293, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v294 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v294, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v295 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v295, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v296 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v296, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v297 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v297, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v298 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v298, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v299 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v299, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v300 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v300, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v301 = Allocate(TYPE_BOSS_NML_EVENT);
  _ctor_31277632(v301, 496, 145, 1, 0, 0, 0, v496, 0, 0, 0, 0, 0, 0, 0, 1, 1, 4, 1, v455, v292, v293, v294, v295, v296, v297, v298, v299, v300, 0);
  v509[29] = v301;
  v456 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v456, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__9B5A7ADC4BB87958578A651781D7D03A7A9309CB9144CDAF260CA17A6C907769, 0);
  v302 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v302, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v303 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v303, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v304 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v304, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v305 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v305, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v306 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v306, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v307 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v307, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v308 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v308, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v309 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v309, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v310 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v310, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v311 = Allocate(TYPE_BOSS_NML_EVENT);
  _ctor_31277632(v311, 512, 464, 1, 0, 0, 0, start_on_tips, 0, 0, 0, 0, 0, 0, 0, 1, 1, 4, 1, v456, v302, v303, v304, v305, v306, v307, v308, v309, v310, 0);
  v509[30] = v311;
  v498 = start_on_tips;
  v457 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v457, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__D48C52AA933ACFB6A07E852D370FAEED0B65CE244F10928B0431717BF149D2D4, 0);
  v312 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v312, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v313 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v313, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v314 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v314, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v315 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v315, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v316 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v316, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v317 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v317, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v318 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v318, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v319 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v319, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v320 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v320, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v321 = Allocate(TYPE_BOSS_NML_EVENT);
  _ctor_31277632(v321, 513, 465, 1, 0, 0, 0, v498, 0, 0, 0, 0, 0, 0, 0, 1, 1, 4, 1, v457, v312, v313, v314, v315, v316, v317, v318, v319, v320, 0);
  v509[31] = v321;
  v499 = start_on_tips;
  v458 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v458, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__35DDF5C90EB41B8CEA336554434D1A1A047B4F49338ADCB74F118301553FFF8A, 0);
  v322 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v322, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v323 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v323, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v324 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v324, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v325 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v325, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v326 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v326, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v327 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v327, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v328 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v328, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v329 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v329, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v330 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v330, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v331 = Allocate(TYPE_BOSS_NML_EVENT);
  _ctor_31277632(v331, 514, 476, 1, 0, 0, 0, v499, 0, 0, 0, 0, 0, 0, 0, 1, 1, 4, 1, v458, v322, v323, v324, v325, v326, v327, v328, v329, v330, 0);
  v509[32] = v331;
  v500 = NewSpecific(s32, 3u);
  *(u64 *)&v500[1] = 0xFFFFFFFF00000001LL;
  v459 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v459, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v332 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v332, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v333 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v333, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v334 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v334, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v335 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v335, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v336 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v336, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v337 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v337, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v338 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v338, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v339 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v339, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  lbl_Tips = NewSpecific(s32, 3u);
  InitializeArray_55364416(lbl_Tips, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__0C5789F72DB8AFFC0549C50FD55B7A9101D4C65CDDCD55EBA8CFAEFEA145608C, 0);
  v341 = Allocate(TYPE_BOSS_NML_EVENT);
  _ctor_31278544(
v341,
515,
469,
1,
-1,
7,
0,
1,
0,
0,
0,
0,
0,
0,
0,
1,
1,
4,
1,
v500,
v459,
v332,
v333,
v334,
v335,
v336,
v337,
v338,
v339,
lbl_Tips,
    0);
  v509[33] = v341;
  v501 = start_on_tips;
  v460 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v460, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__904A30B0DE910D0308978FCBF462E7BA530495036D7C2FE560BCED342BDF6E09, 0);
  v424 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v424, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v342 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v342, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v343 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v343, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v344 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v344, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v345 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v345, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v346 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v346, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v347 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v347, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v348 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v348, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v349 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v349, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v350 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v350, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v351 = Allocate(TYPE_BOSS_NML_EVENT);
  _ctor_31278544(
v351,
517,
474,
1,
0,
8,
0,
v501,
0,
0,
0,
0,
0,
0,
0,
1,
1,
4,
1,
v460,
v424,
v342,
v343,
v344,
v345,
v346,
v347,
v348,
v349,
v350,
    0);
  v509[34] = v351;
  v502 = start_on_r1;
  v461 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v461, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v425 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v425, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v352 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v352, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v353 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v353, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v354 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v354, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v355 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v355, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v356 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v356, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v357 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v357, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v358 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v358, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v359 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v359, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v360 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v360, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v361 = Allocate(TYPE_BOSS_NML_EVENT);
  _ctor_31278544(
v361,
529,
533,
1,
-1,
7,
0,
v502,
0,
0,
0,
0,
0,
0,
0,
1,
1,
4,
1,
v461,
v425,
v352,
v353,
v354,
v355,
v356,
v357,
v358,
v359,
v360,
    0);
  v509[35] = v361;
  v503 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v503, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__040E3412FAEE8E0462CD22AAE0AE42A449B497E67BF4C6445200466ACC7BD47B, 0);
  v462 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v462, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v362 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v362, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v363 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v363, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v364 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v364, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v365 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v365, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v366 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v366, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v367 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v367, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v368 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v368, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v369 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v369, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v370 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v370, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v371 = Allocate(TYPE_BOSS_NML_EVENT);
  _ctor_31278544(
v371,
536,
526,
1,
-1,
1,
0,
1,
0,
0,
0,
0,
0,
0,
0,
1,
1,
4,
0,
v503,
v462,
v362,
v363,
v364,
v365,
v366,
v367,
v368,
v369,
v370,
    0);
  v509[36] = v371;
  v463 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v463, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v372 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v372, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v373 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v373, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v374 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v374, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v375 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v375, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v376 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v376, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v377 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v377, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v378 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v378, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v379 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v379, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v380 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v380, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v381 = Allocate(TYPE_BOSS_NML_EVENT);
  _ctor_31277632(v381, 488, 221, 1, -1, 1, 0, start_on_esw, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, v463, v372, v373, v374, v375, v376, v377, v378, v379, v380, 0);
  v509[37] = v381;
  v505 = start_on_esw;
  v464 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v464, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v382 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v382, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v383 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v383, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v384 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v384, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v385 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v385, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v386 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v386, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v387 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v387, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v388 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v388, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v389 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v389, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v390 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v390, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v391 = Allocate(TYPE_BOSS_NML_EVENT);
  _ctor_31277632(v391, 489, 223, 1, -1, 1, 0, v505, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, v464, v382, v383, v384, v385, v386, v387, v388, v389, v390, 0);
  v509[38] = v391;
  v506 = start_on_esw;
  v465 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v465, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v392 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v392, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v393 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v393, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v394 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v394, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v395 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v395, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v396 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v396, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v397 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v397, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v398 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v398, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v399 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v399, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v400 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v400, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v401 = Allocate(TYPE_BOSS_NML_EVENT);
  _ctor_31277632(v401, 490, 228, 1, -1, 1, 0, v506, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, v465, v392, v393, v394, v395, v396, v397, v398, v399, v400, 0);
  v509[39] = v401;
  v507 = start_on_r1;
  v466 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v466, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v402 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v402, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v403 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v403, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v404 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v404, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v405 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v405, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v406 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v406, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v407 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v407, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v408 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v408, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v409 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v409, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v410 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v410, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v411 = Allocate(TYPE_BOSS_NML_EVENT);
  _ctor_31277632(v411, 53, 299, 1, 0, 0, 0, v507, 0, 0, 0, 0, 0, 0, 0, 1, 1, 4, 1, v466, v402, v403, v404, v405, v406, v407, v408, v409, v410, 0);
  v509[40] = v411;
  v508 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v508, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v412 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v412, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v413 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v413, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v414 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v414, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v415 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v415, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v416 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v416, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v417 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v417, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v418 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v418, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v419 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v419, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v420 = NewSpecific(s32, 3u);
  InitializeArray_55364416(v420, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__8688D249E9D047B4FC2FB89CE05AFE9EC89252FFCCDD969DE6EEF260DD7FFB21, 0);
  v421 = Allocate(TYPE_BOSS_NML_EVENT);
  _ctor_31277632(v421, -1, -1, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, v508, v412, v413, v414, v415, v416, v417, v418, v419, v420, 0);
  v509[41] = v421;
  arrBossEveTable = v509;
}
