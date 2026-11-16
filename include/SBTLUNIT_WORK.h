#pragma once
#include "types.h"
#include "MODELTYPE.h"
#include "SBTLMODEL_SIZE.h"
#include "SBTLUNIT_EX.h"
#include "SBTLUNIT_HST.h"
#include "SBTLUNIT_MODE.h"
#include "SBTLUNIT_MOTION.h"
#include "SBTLUNIT_SIDE.h"
#include "SBTLUNIT_ST.h"
#include "SBTLUNIT_VST.h"
#include "SKLID.h"

typedef enum {
    SBTLDRAWGAUGETYPE_NONE = 0,
    SBTLDRAWGAUGETYPE_BARRIER = 1,
    SBTLDRAWGAUGETYPE_ENCHANT = 2,
    SBTLDRAWGAUGETYPE_BULLET = 3,
    SBTLDRAWGAUGETYPE_AURA = 4,
    SBTLDRAWGAUGETYPE_TETRAKARN = 5,
} SBTLDRAWGAUGETYPE;

typedef enum {
    SBTLUNIT_FLG_RUNAWAY = 1,
    SBTLUNIT_FLG_MUTEKI = 2,
    SBTLUNIT_FLG_DIRECTSKL = 8,
    SBTLUNIT_FLG_DAMAGEZERO = 16,
    SBTLUNIT_FLG_NOWAITMOT = 32,
    SBTLUNIT_FLG_NOHITBACK = 64,
    SBTLUNIT_FLG_NODMGROT = 128,
    SBTLUNIT_FLG_NoMVSupport = 256,
    SBTLUNIT_FLG_NONAMEMENU = 512,
    SBTLUNIT_FLG_STLS = 1024,
    SBTLUNIT_FLG_KAIHIMUTEKI = 2048,
    SBTLUNIT_FLG_SETSUMA1_J = 4096,
    SBTLUNIT_FLG_SETSUMA2_J = 8192,
    SBTLUNIT_FLG_SETSUMA3_J = 16384,
    SBTLUNIT_FLG_SETSUMA1_I = 32768,
    SBTLUNIT_FLG_SETSUMA2_I = 65536,
    SBTLUNIT_FLG_SETSUMA3_I = 131072,
    SBTLUNIT_FLG_JUMP_MUTEKI = 262144,
    SBTLUNIT_FLG_OIUCHI_MUTEKI = 524288,
    SBTLUNIT_FLG_SETSUMA_B_MUTEKI = 1048576,
    SBTLUNIT_FLG_SETSUMA_A_MUTEKI = 2097152,
    SBTLUNIT_FLG_SETSUMA1_J_LASTB3 = 4194304,
} SBTLUNIT_FLG;

typedef enum {
    SBTLACTION_EFFECT_NONE = 0,
    SBTLACTION_EFFECT_BLACKOUT = 1,
    SBTLACTION_EFFECT_WHITEOUT = 2,
    SBTLACTION_EFFECT_KILLSELF = 4,
    SBTLACTION_EFFECT_KILLALL = 8,
} SBTLACTION_EFFECT;

typedef enum {
    SBTLUNIT_CMST_TURN_R = 1,
    SBTLUNIT_CMST_TURN_B = 2,
    SBTLUNIT_CMST_TURN_L = 4,
    SBTLUNIT_CMST_TURN_ED = 8,
    SBTLUNIT_CMST_RUN_TO_IDLE = 16,
    SBTLUNIT_CMST_RUN_R = 32,
    SBTLUNIT_CMST_RUN_L = 64,
    SBTLUNIT_CMST_RUN_C = 128,
    SBTLUNIT_CMST_RUN_R2 = 256,
    SBTLUNIT_CMST_RUN_L2 = 512,
    SBTLUNIT_CMST_ZEN_TO_RUN = 1024,
    SBTLUNIT_CMST_TO_CHAGE = 16384,
    SBTLUNIT_CMST_CHAGE_TO_IDLE = 32768,
    SBTLUNIT_CMST_CHAGE_MF = 65536,
    SBTLUNIT_CMST_CHAGE_MR = 131072,
    SBTLUNIT_CMST_CHAGE_MB = 262144,
    SBTLUNIT_CMST_CHAGE_ML = 524288,
    SBTLUNIT_CMST_CAMLOCKON_MF = 1048576,
    SBTLUNIT_CMST_CAMLOCKON_MR = 2097152,
    SBTLUNIT_CMST_CAMLOCKON_MB = 4194304,
    SBTLUNIT_CMST_CAMLOCKON_ML = 8388608,
} SBTLUNIT_CMST;

typedef enum {
    SBTLUNIT_MOTIONST_INIT = 0,
    SBTLUNIT_MOTIONST_ACT = 1,
    SBTLUNIT_MOTIONST_CHNG = 2,
    SBTLUNIT_MOTIONST_INIT_EX = 4,
} SBTLUNIT_MOTIONST;

typedef enum {
    NakamaSignType_None = 0,
    NakamaSignType_EnemyWeek = 1,
    NakamaSignType_HpDown = 2,
    NakamaSignType_NoPlan = 4,
} NakamaSignType;

typedef struct HpCallCtrl HpCallCtrl;
typedef struct SBTLACTAI_WORK SBTLACTAI_WORK;
typedef struct SBTLACTION_WORK SBTLACTION_WORK;
typedef struct SBTLAISYO_DATAWORK SBTLAISYO_DATAWORK;
typedef struct SBTLAI_WORK SBTLAI_WORK;
typedef struct SBTLSKLHIT_PACLIST SBTLSKLHIT_PACLIST;
typedef struct SBTLSKL_KAJA_WORK SBTLSKL_KAJA_WORK;
typedef struct SBTLSOUND_DEVILWORK SBTLSOUND_DEVILWORK;
typedef struct SBTLSOUND_FOOTWORK SBTLSOUND_FOOTWORK;
typedef struct SBTLUNIT_WORK SBTLUNIT_WORK;
typedef struct dds3Basic_t dds3Basic_t;
typedef struct dds3ModelHandle_t dds3ModelHandle_t;
typedef struct effCtexHandle_t effCtexHandle_t;
typedef struct evtUnitHandle_t evtUnitHandle_t;
typedef struct fileHandle_t fileHandle_t;
typedef struct mapLightParam_t mapLightParam_t;
typedef struct pacFileHandle_t pacFileHandle_t;
typedef struct sbtldvltk_unitworktag sbtldvltk_unitworktag;
typedef struct sdatParaWork_t sdatParaWork_t;
typedef struct sdatUnitWork_t sdatUnitWork_t;
typedef struct tagSBTLSKL_AURA_WORK tagSBTLSKL_AURA_WORK;
typedef struct tagSBTLSKL_KARN_WORK tagSBTLSKL_KARN_WORK;

struct SBTLACTION_WORK {
    u32 status;
    s32 framecnt;
    s32 framecntB;
    s32 framecntC;
    s32 cmpframecnt;
    s32 cmpframecnt2;
    s32 cmpframecnt3;
    s32 effectTime;
    SKLID use_skillid;
    u32 next_st;
    SKLID order_skillid;
    s32 order_targetID;
    s32 order_stockID;
    SKLID order_sklidbk;
    s8 order_setflg;
    s8 action_flg;
    s32 action_count;
    s32 counter;
    s32 gravcnt;
    s32 tok_st;
    s32 tok_datap;
    SBTLACTION_EFFECT effect_flg;
    u32 quake_flg;
    f32 total_homing;
    bool no_homing;
    SKLID sklcng_use_skillid;
    s32 sklcng_next_motiontime;
    s32 exStep;
    s32 exStepNext;
    s32 exWait;
    s32 exSkillNext;
    s32 exSeWait;
    s32 exAutoDead;
    s32 genArg[4];
};

struct SBTLSOUND_DEVILWORK {
    s32 boss_seid;
    s32 flag;
    s32 dead_seid;
    s32 at3gstat;
    s32 at3Size;
    u8 *pBossAt3Data;
    s32 bossAt3gstat;
    s32 bossAt3Size;
    s32 mot_SMGID;
    s32 mot_SMGID2;
    s32 mot_SMGID3;
    s32 mot_status;
    s32 mot_nowcnt;
    s32 mot_startcnt;
    s32 mot_seid;
    s32 mot_vol;
    s32 mot_step;
    s32 mot_motionID;
    SBTLSOUND_FOOTWORK *footwk;
};

struct sbtldvltk_unitworktag {
    fileHandle_t *hFile;
    u8 *pData;
    bool LB_Load;
    bool LB_Load2;
    u8 dmy;
    effCtexHandle_t *CacheTex;
    effCtexHandle_t *CacheTexIcon;
};

struct tagSBTLSKL_KARN_WORK {
    SKLID m_skillid;
    s32 m_cnt;
};

struct tagSBTLSKL_AURA_WORK {
    SKLID auraskl;
    s32 auracnt;
    s32 aurapara;
};

struct SBTLUNIT_WORK {
    sdfVector4_t vPosCmbMov0;
    sdfVector4_t vPosCmbMov1;
    sdfVector4_t vPosBfrCmb;
    sdfVector4_t vRotBfrCmb;
    sdfVector4_t vDmgPosBfrCmb;
    sdfVector4_t scale;
    sdfVector4_t mv_spd;
    sdfVector4_t max_mvspd;
    sdfVector4_t mv_spdbk;
    f32 disp_offy;
    sdfVector4_t pos;
    sdfVector4_t rot;
    sdfVector4_t rot_p;
    sdfVector4_t nextpos;
    sdfVector4_t rotbk;
    sdfVector4_t ofspos;
    sdfVector4_t koteipos;
    sdfVector4_t effpos;
    sdfVector4_t namatuba_goal_pos;
    sdfVector4_t namatuba_1st_pos;
    bool namatuba_homing_on;
    s32 namatuba_cnt;
    f32 namatuba_1st_spdnml;
    mapLightParam_t *light;
    SBTLSOUND_DEVILWORK *sewk;
    pacFileHandle_t *pacHandle;
    s32 GroupID;
    s32 ListID;
    s32 UID;
    SBTLUNIT_MODE mode;
    sdatUnitWork_t *para;
    SKLID *haveskill[19];
    s32 oldhp;
    SBTLAISYO_DATAWORK *aisyo_bkup;
    s16 paraupcnt;
    sdatParaWork_t *kajyapara;
    s8 kajyaflg;
    SBTLSKL_KAJA_WORK *wkKaja[3];
    tagSBTLSKL_KARN_WORK *wkKarn[1];
    SBTLDRAWGAUGETYPE drawgaugetype;
    s32 rejyenecounter;
    s32 rejyenecnt;
    s32 rejyenecmpcnt;
    s32 rejyenehelper;
    s32 rejyenepara;
    s32 slipcounter;
    s32 slipcnt;
    s32 slipcmpcnt;
    SKLID slip_sklid;
    s32 slippara;
    SBTLUNIT_SIDE side_given_slip;
    u32 barrierstatus;
    u32 barrieradv;
    s32 barriercnt;
    void *wkBarrier;
    SKLID barriersklid;
    s32 tdancounter;
    s32 tdancnt;
    s32 tdanhitcnt;
    s32 tdancmpcnt;
    s32 tdan_acterid;
    SKLID tdan_sklid;
    s32 tdanhelper;
    s32 tdanpara;
    s32 autoreccnt;
    s32 enchantcnt;
    SKLID swordskl;
    s32 bulletcnt;
    SKLID bulletskl;
    tagSBTLSKL_AURA_WORK *wkAura[3];
    u32 aurakind;
    SKLID koufunskl;
    bool revival;
    s32 o_def_dn_time;
    s32 o_def_dn_rate;
    s32 o_atk_up_time;
    s32 o_atk_up_rate;
    MODELTYPE major;
    s32 minor;
    s32 motionno;
    SBTLUNIT_MOTION motionID;
    f32 m_rate;
    SBTLMODEL_SIZE size;
    s16 motion_setno;
    f32 m_BlendTree1D;
    bool m_BlendTree1DFlg;
    f32 m_BlendTree2DX;
    f32 m_BlendTree2DY;
    bool m_BlendTree2DFlg;
    s16 fade_sttime;
    s16 fadecnt;
    s32 fadepara;
    s32 cmpfade;
    u32 color;
    u32 chgcolor;
    u32 dstcolor;
    s32 fadergb;
    bool ditherAlpha;
    f32 dissolveAlpha;
    u32 color_chroma;
    bool stoneUse;
    u32 abgr;
    u32 abgr2;
    bool Itimoku_CloseEye;
    s16 Itimoku_CloseCnt;
    s16 framecnt;
    SBTLUNIT_MOTIONST motionst;
    s32 next_motionno;
    SBTLUNIT_MOTION next_motionID;
    s16 beforeframe;
    s16 afterframe;
    s32 motion_serialno;
    bool motion_UseWait2;
    SBTLUNIT_MOTION motion_NoUseMSE_motionID;
    s32 req_skill_motion;
    bool motion_EndNoCng;
    bool motion_SetSkip;
    s16 motion_FrameSkip;
    bool motion_SeSkep;
    s16 motion_WeakDmg2;
    s16 motion_WeakStopF;
    dds3Basic_t *pBasic;
    evtUnitHandle_t *hEveUnit;
    dds3ModelHandle_t *hModel;
    s8 gstat;
    s8 changeflg;
    s32 minor_d;
    s32 bunriid;
    s16 aisyoid;
    s16 criticalflg;
    s16 criticalcol;
    dds3Basic_t *pBasic_d;
    evtUnitHandle_t *hEveUnit_d;
    dds3ModelHandle_t *hModel_d;
    SBTLUNIT_SIDE side;
    s8 mvflg;
    SBTLUNIT_ST status;
    SBTLUNIT_EX exsts;
    SBTLUNIT_VST vstatus;
    SBTLUNIT_HST hstatus;
    SBTLUNIT_HST hstatus_old;
    SBTLUNIT_CMST cmstatus;
    f32 mv_rot;
    f32 max_mvrot;
    f32 mv_rotbk;
    f32 deg;
    s16 degcnt;
    f32 front_deg;
    f32 front_time;
    f32 turn_start;
    f32 turn_goal;
    SBTLUNIT_MOTION turn_ed_motionID;
    SBTLACTION_WORK *actwk;
    SBTLACTAI_WORK *actaiwk;
    SBTLAI_WORK *aiwk;
    s32 exflg;
    s16 actcounter;
    s16 actcounter_max;
    s16 hithelperno;
    s16 hithelperID;
    s16 hithelperreqID;
    s16 effhelperno;
    s16 hithelpercsrno;
    s16 hitsliphelper;
    s32 huttobiID;
    s16 damagecnt;
    s32 yuka_damagecnt;
    s32 damage_serialID;
    s32 damage_workID;
    s16 damage_actionf;
    s16 damage_actionf_cnt;
    s16 damage_hitcnt;
    s16 nguard_dmgcnt;
    s32 damage_guncnt;
    s16 damage_gunnum;
    s32 damage_1stmotcnt;
    s16 damage_1stmotnum;
    f32 damage_ActerOfsY;
    s16 eventno;
    s32 tenmetu_cnt;
    s32 tenmetu_color;
    s32 bst_effserialID2;
    f32 width;
    f32 height;
    f32 ground;
    sbtldvltk_unitworktag *dvltkwk;
    s16 dvltk_gstat;
    s32 lightcnt;
    s8 light_buff[3];
    s8 light_sw;
    SBTLSKLHIT_PACLIST *hitwk;
    s32 getMag;
    s16 yure;
    s16 yurecnt;
    f32 yure_x;
    f32 yure_y;
    f32 yure_z;
    s32 noWeakStfCnt;
    SBTLUNIT_MOTION waitwalkMot;
    bool bOldDispOff;
    bool bOldNotHitDmg;
    bool bOldHitNone;
    bool bOldMuteki;
    bool bOldScrWarp;
    bool bShibouEnshutsu;
    bool bOldNotMapHit;
    SKLID nakama_skill_name;
    f32 hitlight_x;
    f32 hitlight_z;
    s32 hitlight_cnt;
    bool hitlight_Critical;
    u32 hitlight_r;
    u32 hitlight_g;
    u32 hitlight_b;
    f32 fMotStart;
    bool aMagOut[3];
    s32 deadEvent;
    SBTLUNIT_FLG flg;
    s32 byctCnt;
    s32 motStopCnt;
    f32 moveSpdMul;
    bool bMdlEffClr;
    s32 mdlEffClr;
    s32 mdlEffClrTgt;
    s32 mdlEffClrBgn;
    s32 mdlEffClrFrm;
    s8 talkInochigoiFlg;
    s8 talkBreakDownFlg;
    s32 enc_posid;
    SKLID loseEventBgn;
    bool bYobidousa;
    s32 timeStopID;
    s32 yobidousaCnt;
    bool bYobi2Nml;
    bool bStop;
    f32 h_attack_move_len;
    s32 dmg_hpdraw_cnt;
    f32 nakama_asimoto_anim;
    s32 hangeki_on;
    s32 hangeki_renzokudmg;
    s32 hangeki_nokezoranai;
    s32 hangeki_notjyakuten;
    s32 hangeki_endcnt;
    bool hangeki_st_done;
    s32 mawari_lr;
    f32 mawari_pos_x;
    f32 mawari_pos_z;
    s32 kaifuku_skl_cnt;
    s32 mag_on1;
    s32 mag_on2;
    s32 mag_on3;
    s32 dead_on;
    s32 no_dead_se;
    s32 asimoto_mode;
    f32 asimoto_pos_x;
    f32 asimoto_pos_z;
    f32 asimoto_pos_x2;
    f32 asimoto_pos_z2;
    f32 asimoto_pos_x3;
    f32 asimoto_pos_z3;
    f32 asimoto_pos_x4;
    f32 asimoto_pos_z4;
    f32 asimoto_pos_vx;
    f32 asimoto_pos_vz;
    s32 miusinai;
    s32 kuramasi;
    s32 not_hitmode;
    s32 mukou_damage_cnt;
    u32 warp_bk_color;
    s32 total_damage;
    s32 total_recover;
    s32 katana_hit_cnt;
    f32 lu_start_y;
    s32 not_tatezan;
    s32 L2_muteki;
    s32 next_motion_not_hokan;
    s32 damage_eff_tgt_cnt;
    s32 damage_eff_rai_cnt;
    s32 damage_fuka_tgt_cnt;
    s32 eff_wait_mukou;
    s32 eff_wait_kyushu;
    s32 eff_wait_kaisin;
    s32 eff_wait_guard;
    s32 bk_cmbret_mot_Locked;
    SBTLUNIT_MOTION bk_cmbret_mot_setmotionno;
    s32 bk_cmbret_mot_bframe;
    s32 bk_cmbret_mot_aframe;
    s32 bk_cmbret_mot_flg;
    s32 bk_action_use;
    s32 bk_action_status;
    s32 bk_action_actaiwk_stat;
    s32 bk_action_actaiwk_mode;
    s32 bk_action_actaiwk_cmpframe;
    s32 bk_action_aiwk_stat;
    s32 bk_action_aiwk_mode;
    SKLID bk_action_actwk_use_skillid;
    s32 cap_skillname_x;
    s32 cap_skillname_y;
    s32 cap_skillname_z;
    f32 cap_skillpos_x;
    f32 cap_skillpos_y;
    f32 cap_skillpos_z;
    void *gageUI;
    s32 bossHpGageAnimState;
    s32 bossHpGaugeNo;
    bool bossHpGageSolo;
    sdfVector2_t hpPosition;
    void *weakGageUI;
    bool hpGageDamageFlag;
    void *nameUI;
    s32 stpflg;
    s32 weak_cnt;
    s32 weak_shild;
    s32 weak_shild_max;
    s32 weak_shild_config;
    s32 weak_shild_next;
    s32 weak_shild_timer;
    s32 weak_attrinvtime_max;
    s32 weak_attrinvtime_cnt;
    sdfVector2_t weak_shild_pos;
    s32 atk_raito;
    bool wince_stop;
    s32 s_wince_now;
    s32 l_wince_now;
    s32 s_wince_old;
    s32 l_wince_old;
    s32 s_wince_0;
    s32 l_wince_0;
    s32 s_wince_max;
    s32 l_wince_max;
    s32 l_wince_time;
    s32 wince_type;
    s32 wince_SuperArmor;
    u32 wince_SuperArmorStatus;
    s32 vice_kaisin_cnt;
    bool vice_kaisin_flg;
    s32 kaya_skill_req;
    f32 MHitStop_Speed;
    f32 MHitStop_Time;
    f32 MHitStop_TimeLeft;
    f32 MHitStop_StFrame;
    f32 EHitStop_Speed;
    f32 EHitStop_Time;
    f32 EHitStop_TimeLeft;
    f32 EHitStop_StTime;
    f32 EHitStop_StTimeLeft;
    f32 MSlow_Speed;
    sdfVector4_t JumpOfsPos;
    s32 JumpAfterCnt;
    f32 Bounce_Spd;
    s32 Bounce_Cnt;
    s32 Bounce_HitStopWait;
    s32 Bounce_HitStopCnt;
    s32 Bounce_ReBound;
    bool UnitHitPushUse;
    f32 UnitHitPushDir;
    f32 UnitHitPushLen;
    bool SubCylinder_Use[2];
    f32 SubCylinder_PosDir[2];
    f32 SubCylinder_PosLen[2];
    f32 SubCylinder_Size[2];
    s32 SlashUID;
    SKLID SlashSkillID;
    s32 setsuma_b_muteki_cnt;
    s32 setsuma_a_muteki_cnt;
    SKLID setsuma_rowhit_skillid;
    bool setsuma_rowhit_done;
    bool setsuma_rowhit_hirameki;
    s32 WeakAtkCnt;
    s32 WeakReceiveFlg;
    s32 WeakReceiveCnt;
    u32 uniq_code;
    s32 continue_timer;
    bool initHuuma;
    s32 huuma_get_max;
    s32 *huuma_get_cnt;
    s32 *huuma_get_flg;
    s32 *huuma_get_rnd;
    HpCallCtrl *hpCallCtrl;
    HpCallCtrl *weekAct;
    bool IsMagAtk;
    s32 YukaDamageSkipCnt;
    bool GunMotionEnd;
    s32 AutoTgtDmgCnt;
    s32 MoveL_Cnt;
    s32 MoveR_Cnt;
    s32 MoveU_Cnt;
    bool DoneCameraTgtSelect1;
    bool LoadOnlyTgtSelect;
    s32 TgtCngDead_Cnt;
    bool DeadEventDone;
    bool BossXAtk;
    bool NakamaAtkFormationUse;
    sdfVector4_t NakamaAtkFormationPos;
    s32 UnitEx_Old_MotionNo;
    f32 UnitEx_Old_MotionFrame;
    s32 UnitEx_Old_MotionSerialNo;
    bool UnitEx_DoneWork[32];
    s32 UnitEx_TableIndexTop;
    s32 kuisibariFlag;
    s32 Action_HUTTOBI_Cnt;
    bool UnitMotBugfix_RetryUse;
    s32 UnitMotBugfix_RetryCnt;
    f32 UnitMotBugfix_OldFrame;
    s32 UnitMotBugfix_Timeout;
};

struct HpCallCtrl {
    void *hpGauge;
    NakamaSignType callIconFlag;
    s32 weekCnt;
};
