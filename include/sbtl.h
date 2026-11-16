#pragma once
#include "types.h"
#include "BOSSACT.h"
#include "BTL_TIME.h"
#include "GaugeType.h"
#include "MODELTYPE.h"
#include "SBTLMAIN2.h"
#include "SBTLMAIN4.h"
#include "SBTLMAIN_MODE.h"
#include "SBTLPLAYER_MENUTYPE.h"
#include "SBTL_ACTAIFLG.h"
#include "SBTL_MODE.h"
#include "SKLID.h"
#include "kernel.h"
#include "sbtlmain.h"

#define HAVESKILL_NUM_USE 8
#define HAVESKILL_NUM 17
#define BATTLEUSESKILL_NUM 8
#define OMOIDE_SKL_MAX 6
#define OMOIDESKILL_NUM 8
#define RESERVESKILL_NUM 3
#define COMB_SKILL_NUM 2
#define SOUSA_SKILL_NUM 2
#define SKLGAUGE_MAX 65
#define PARAMAX 40
#define ITEMPARA_SHIFT 8
#define UITEMMASK 65280
#define DITEMMASK 255
#define FRAMERATE 60
#define MTION_DEFSPD 0.5
#define TIMERATE 2
#define DEFMOTION_FRAME 4
#define PLAYER_DUMMYTARGET -1
#define DROPITEM_NUM 12
#define DROPEITEM_NUM 4
#define HOMINGP1 0.5
#define HOMINGP2 0.7
#define SE_AREA_NUM 30
#define MAIN_DATA_TYPE_SYM 0
#define MAIN_DATA_TYPE_ENC 1
#define MAIN_DATA_TYPE2_SCRIPT 0
#define MAIN_DATA_TYPE2_NORMAL 1
#define MAIN_DATA_TYPE2_FATK 2
#define SKL_KAJA_STACK_MAX 2
#define HAVE_SKLNUM2 19
#define STOCK_NUM 32
#define DEADMOTION_FRAME 1
#define EFF_ONMEMORY_NUM 46
#define MAGMAX 999999
#define VICECOUNTER_MAX 999999
#define VICERANK_MAX 5
#define ITEM_FOUTTIME 1800
#define HUUMA_NUM 12
#define SCRIPT_UNIT_MAX 16
#define SABONMEM_NUM 150

typedef enum {
    E_SBTLMAIN_STEP_ZERO = 0,
    E_SBTLMAIN_STEP_CALL_NAKAMA = 1,
} E_SBTLMAIN_STEP;

typedef enum {
    EXIT_BGSCENE = 1,
    EXIT_FLSCENE = 2,
    EXIT_UISCENE = 4,
    NO_MOTVOICE = 8,
    EXIT_TIMEUP = 16,
    NKM_MARK_OFF = 32,
    WAIT_EXIT = 64,
    ALL_FREE = 128,
} SBTLMAIN5;

typedef enum {
    L_CRITICAL = 1,
    L_MAGUP = 2,
    L_EXPUP = 4,
    L_CHUUSEIUP = 8,
    L_MONEYUP = 16,
    L_ITEMUP = 32,
    L_TALKUP = 64,
    L_NORINORI = 128,
    L_TENBATU = 4096,
    U_SUKA = 65536,
    U_BOUDO = 131072,
    U_MAIGO = 262144,
    U_NOKUDA = 524288,
    U_NOITEM = 1048576,
    U_NOESCAPE = 2097152,
    U_TOUMEI = 4194304,
    U_BYCT = 8388608,
    U_MAKIZOE = 16777216,
    U_MAG2BAI = 33554432,
    U_DMGDOWN = 67108864,
    U_KAIFUKUDOWN = 134217728,
    U_ALLDEAD = 268435456,
    U_MASAKADOUS = 536870912,
    U_NAKAMADEAD = 1073741824,
    U_PARAMALL1 = 8192,
    U_DMGREF = 16384,
    L_ALLMASK = 4351,
    U_ALLMASK = 2147442688,
} SBTLMAIN3;

typedef enum {
    SBTLSCENE_ST_ZOOMIN = 1,
    SBTLSCENE_ST_ZOOMOUT = 2,
    SBTLSCENE_ST_ZOOMLOCK = 4,
    SBTLSCENE_ST_MAPFADE = 8,
    SBTLSCENE_ST_MAPFADE_P = 16,
    SBTLSCENE_ST_NAKAMAPOS = 32,
} SBTLSCENE_ST;

typedef struct CMBSKL CMBSKL;
typedef struct CROSS_MENU CROSS_MENU;
typedef struct CROSS_MENU_ONE CROSS_MENU_ONE;
typedef struct HITEFFLIST HITEFFLIST;
typedef struct RED_GUAGE RED_GUAGE;
typedef struct SBATTLE_WORK SBATTLE_WORK;
typedef struct SBATTLE_WORK2 SBATTLE_WORK2;
typedef struct SBATTLE_WORK3 SBATTLE_WORK3;
typedef struct SBTLANIM_HOKAN SBTLANIM_HOKAN;
typedef struct SBTLCAMERA_WORK SBTLCAMERA_WORK;
typedef struct SBTLDMG_HITLISTWORK SBTLDMG_HITLISTWORK;
typedef struct SBTLDMG_HITWORK SBTLDMG_HITWORK;
typedef struct SBTLDMG_LISTWORK SBTLDMG_LISTWORK;
typedef struct SBTLDROP_WORK SBTLDROP_WORK;
typedef struct SBTLDVLTK_LISTWORK SBTLDVLTK_LISTWORK;
typedef struct SBTLEFF_DATAWORK SBTLEFF_DATAWORK;
typedef struct SBTLEFF_DELLISTWORK SBTLEFF_DELLISTWORK;
typedef struct SBTLEFF_LISTWORK SBTLEFF_LISTWORK;
typedef struct SBTLEFF_PACFILE_EPL SBTLEFF_PACFILE_EPL;
typedef struct SBTLEFF_PACLIST SBTLEFF_PACLIST;
typedef struct SBTLEFF_WORK SBTLEFF_WORK;
typedef struct SBTLEXP_LISTWORK SBTLEXP_LISTWORK;
typedef struct SBTLITEM_LISTWORK SBTLITEM_LISTWORK;
typedef struct SBTLITEM_TBL SBTLITEM_TBL;
typedef struct SBTLMAIN_DATA SBTLMAIN_DATA;
typedef struct SBTLPACDATA_AT3 SBTLPACDATA_AT3;
typedef struct SBTLPACDATA_WORK SBTLPACDATA_WORK;
typedef struct SBTLPANEL_WORK SBTLPANEL_WORK;
typedef struct SBTLSCENE_WORK SBTLSCENE_WORK;
typedef struct SBTLSKLHIT_PACLIST SBTLSKLHIT_PACLIST;
typedef struct SBTLSM_LISTWORK SBTLSM_LISTWORK;
typedef struct SBTLSOUND_STATUSWORK SBTLSOUND_STATUSWORK;
typedef struct SBTLSTP_LISTWORK SBTLSTP_LISTWORK;
typedef struct SBTLTALK_WORK SBTLTALK_WORK;
typedef struct SBTLUNIT_LISTWORK SBTLUNIT_LISTWORK;
typedef struct SBTLUNIT_WORK SBTLUNIT_WORK;
typedef struct SBTLVIBE_WORK SBTLVIBE_WORK;
typedef struct SBTL_HITEFF SBTL_HITEFF;
typedef struct SBTL_MAGEFF SBTL_MAGEFF;
typedef struct SBTL_PACDATA_MOTIONSE SBTL_PACDATA_MOTIONSE;
typedef struct STATUS_BAR STATUS_BAR;
typedef struct SUMMON_CTRL SUMMON_CTRL;
typedef struct S_BLUR S_BLUR;
typedef struct _BARCTRL _BARCTRL;
typedef struct _RNDHIT _RNDHIT;
typedef struct _SKLPROC _SKLPROC;
typedef struct _S_KETTOU _S_KETTOU;
typedef struct dds3Basic_t dds3Basic_t;
typedef struct dds3ModelHandle_t dds3ModelHandle_t;
typedef struct dds3ProcessID_t dds3ProcessID_t;
typedef struct pacFileHandle_t pacFileHandle_t;
typedef struct plistHandle_t plistHandle_t;
typedef struct scrHandle_t scrHandle_t;
typedef struct sdatPlayerUnitWork_t sdatPlayerUnitWork_t;
typedef struct sdatUnitWork_t sdatUnitWork_t;

typedef void (*m_fpDecideDelegate)(s32 UnnamedParameter);
typedef void (*m_fpDrawBarDelegate)(s32 x, s32 y, s32 id, CROSS_MENU_ONE *pMenuBar);

struct SBTLDROP_WORK {
    s32 setflg;
    s32 exp;
    s32 nakama_exp;
    s32 mag;
    s32 chuusei;
    s32 tlev;
    s32 get_chuusei;
    s32 num;
    s32 gold;
    s32 *item[12];
    char *log;
    s32 eventitem[4];
};

struct SBTLVIBE_WORK {
    s32 in;
    s32 out;
    s32 life;
    s32 count;
    s8 st;
    u8 power;
};

struct SBTLSOUND_STATUSWORK {
    s32 skillLockNum;
    s32 enemyLockNum;
};

struct SBTLSCENE_WORK {
    SBTLCAMERA_WORK *camera;
    SBTLCAMERA_WORK *camerabk;
    u32 major;
    u32 minor;
    SBTLSCENE_ST status;
    s32 zoomlockID;
    s8 zoomlockflg;
    f32 zoom_x;
    f32 zoom_y;
    f32 zoom_z;
    s32 zoom_time;
    f32 zoom_bairitu;
    s32 zoomlocktime;
    s32 dummy0;
    s32 dummy1;
    s32 dummy2;
    s32 dummy3;
    s32 camCnt;
    s32 camCnt2;
};

struct SBTLEFF_PACFILE_EPL {
    void *pData;
    pacFileHandle_t *pacHandle;
    s32 setflg;
    s32 data_cnt;
};

struct HITEFFLIST {
    s32 lstIdx;
    s32 cnt;
    SBTL_HITEFF *aHitEff[16];
    SBTL_HITEFF *pHitEffBgn;
    SBTL_HITEFF *pHitEffEnd;
};

struct SBTLPACDATA_AT3 {
    s32 size;
};

struct SBTLPACDATA_WORK {
    SBTLPACDATA_AT3 *at3;
    SBTL_PACDATA_MOTIONSE *motionSE;
    SBTLSKLHIT_PACLIST *hitwk;
    MODELTYPE major;
    s32 minor;
    s32 devilid;
};

struct CROSS_MENU_ONE {
    m_fpDecideDelegate m_fpDecide;
    s32 m_bDecide;
    s32 m_dt;
    u16 dammy;
};

struct CROSS_MENU {
    s32 m_cDecide;
    CROSS_MENU_ONE *m_aBar[4];
    m_fpDrawBarDelegate m_fpDrawBar;
};

struct SBTL_MAGEFF {
    sdfVector4_t m_vPos;
    sdfVector4_t m_vSpd;
    sdfVector4_t m_vTgt;
    s32 m_cnt;
    f32 m_fAxl2Tgt;
    f32 m_fSpdKeep;
    f32 m_fScl;
    f32 m_fSclSpd;
    s32 m_Alp;
    s32 m_AlpSpd;
    s32 m_AnmCnt;
    s32 m_SprIdx;
    u32 m_Flg;
    s32 m_Type;
    s32 m_EndCnt;
    f32 m_TgtLen;
    s32 m_Tgt;
    SBTL_MAGEFF *m_pPrev;
    SBTL_MAGEFF *m_pNext;
    s32 m_mag;
    s32 m_index;
};

struct CMBSKL {
    SKLID sklId;
    SBTLUNIT_WORK *pNakama0;
    SBTLUNIT_WORK *pNakama1;
    SBTLUNIT_WORK *pNakama0org;
    SBTLUNIT_WORK *pNakama1org;
    s32 cnt;
    s8 step;
    s8 step2;
    bool bRun;
    bool bRun_DrawUI;
    s32 tgtId;
    s32 type;
    SKLID bullet;
    bool bulletLoad;
    s8 bulletNakama;
    bool dltReq;
    s32 tateLv;
    s32 tateStp;
    s32 tateCnt;
    s32 tateClr;
    bool tateLoad;
};

struct SUMMON_CTRL {
    s32 bNoOk;
    s32 stkId;
    s32 aprId;
    s32 io;
};

struct STATUS_BAR {
    s32 cnt;
    s32 x;
    s32 y;
};

struct _S_KETTOU {
    SBTLUNIT_WORK *m_pUnit;
    s32 m_stp;
    s32 m_cnt;
};

struct _BARCTRL {
    s32 barStart;
    s32 barLong;
    s32 moonX;
};

struct _RNDHIT {
    bool bFrm;
    s32 frm;
    s32 num;
    s32 frq;
    s32 cnt0;
    s32 cnt1;
    bool abTateHit[16];
};

struct _SKLPROC {
    bool bRun;
    s32 unitID;
    s32 timeStopID;
    s32 cnt;
    s32 stp;
};

struct S_BLUR {
    bool bRun;
    u16 alpha;
    u16 alphaEnd;
    s32 frm;
    s32 cnt;
};

struct SBATTLE_WORK {
    sdfVector4_t vPosBossEvent;
    sdfVector4_t avTateHitPos[16];
    sdfVector4_t avTateHitRot[16];
    sdfVector4_t vCmbPos0;
    sdfVector4_t vCmbPos1;
    sdfVector4_t vCmbRot0;
    sdfVector4_t vCmbRot1;
    sdfVector4_t camPos_t;
    sdfVector4_t camTgt_t;
    sdfVector4_t camPos_s;
    sdfVector4_t camTgt_s;
    sdfVector4_t gunTgtPos;
    sdfVector4_t scrVector;
    sdfVector4_t vAddEnemy;
    SBTLSCENE_WORK *scene;
    SBTLEFF_PACFILE_EPL *effOnRsc;
    bool bCamPosSlp;
    bool bCamTgtSlp;
    s32 camPosSlpCnt;
    s32 camTgtSlpCnt;
    s32 camPosSlpTime;
    s32 camTgtSlpTime;
    s16 effcnt;
    dds3ProcessID_t *MProc_ID;
    s32 syscnt;
    s32 endcnt;
    s32 scrollID;
    s16 equipsord;
    s16 equipgun;
    s32 equipbullet;
    SBTLMAIN status;
    SBTLMAIN2 status2;
    SBTLMAIN3 status3;
    u32 status3_param;
    SBTLMAIN4 status4;
    SBTLMAIN5 status5;
    u32 flg;
    s32 playerID;
    u16 hitmdl_serialID;
    SBTL_MODE battlemode;
    bool is_jyuso;
    s32 encountno;
    s32 evtEncountNo;
    s32 all_encount_cnt;
    s32 all_encount_max;
    s32 all_encount_tim;
    bool InfiniteSpringStop_flag;
    SBTLUNIT_LISTWORK *UnitMng;
    s32 loadListID;
    s32 cmnd_csr;
    s32 order_csr;
    s32 nego_gstat;
    s32 nego_chrid;
    s32 nego_alpha;
    s16 evtloadst;
    u8 *evtloadpData;
    s32 evtload_evtno;
    s16 eventno;
    s16 eventcounter;
    s16 eventgstat;
    s16 eventdeadflg;
    s32 eventListID;
    s32 tutorialMesCount;
    s32 eventTheworld;
    s32 eventSceneStop;
    dds3ProcessID_t *eventprocID;
    s16 summonindex[2];
    s16 returnindex[2];
    s32 summonindex_menu[2];
    s32 macter_csr;
    s32 macter_ofs;
    s32 useitemID;
    SKLID useitembk;
    s16 useitem_stock;
    s32 equipbulletbk;
    s32 stock_useskillp[32];
    SKLID *stock_useskill[11];
    s16 stock_skillnum;
    s32 tgt_csr;
    s32 tgt_ListID[32];
    SBTLUNIT_LISTWORK *tgtList;
    s32 enemy_csr;
    SBTLUNIT_LISTWORK *enemyList;
    s16 tgt_msgno;
    s32 stock_buffer[32];
    s32 stock_id[32];
    u32 stock_mask;
    s32 stock_num;
    s32 member_num;
    s32 summonnum;
    u8 summon[32];
    u8 summonflg[32];
    s32 summonID[32];
    u32 kuishibBit;
    u32 rKuishiUseBit;
    u32 deadbombBit;
    s32 stack_id[2];
    s16 stack_p[2];
    s32 unitpadID;
    s32 hitokoto1st;
    s32 hitokoto_spirit;
    SBTLVIBE_WORK *vibe[2];
    s32 vibe_startf[2];
    s32 vibe_frame[2];
    u8 vibe_power[2];
    u8 vibe_type[2];
    SBTLUNIT_LISTWORK *targetList;
    s32 target_p;
    s8 targetcsr_flg;
    SBTLDMG_LISTWORK *dmgList;
    SBTLDMG_HITLISTWORK *hitList;
    SBTLDMG_HITLISTWORK *dbghitList;
    SBTLEFF_LISTWORK *effList;
    SBTLUNIT_LISTWORK *friend_List;
    SBTLUNIT_LISTWORK *other_List;
    SBTLUNIT_LISTWORK *other_List2;
    SBTLITEM_LISTWORK *itemList;
    SBTLITEM_LISTWORK *bulletList;
    SBTLITEM_LISTWORK *katanaList;
    SBTLSM_LISTWORK *sysmsgList;
    SBTLEFF_DELLISTWORK *effdelList;
    SBTLDMG_HITWORK *huka2hwk;
    s32 enemy_num;
    bool enemy_zenmetu;
    s32 groupID;
    s32 SUMMONSKILL_Start;
    s32 hittargetID;
    SBTLMAIN_MODE mode;
    SBTLMAIN_MODE modebk;
    s16 mode2;
    SBTLPLAYER_MENUTYPE menutype;
    s16 gstat[2];
    s16 walk_counter;
    s16 wait_counter;
    s16 sgstat[2];
    s16 s_time;
    s32 mag;
    s32 magMax;
    s32 mag_counter;
    s32 gunskillid;
    s32 bullet;
    s32 hgun_num;
    s32 mgun_num;
    s32 sgun_num;
    s32 getmag;
    s32 gethp;
    s32 gethgunn;
    s32 getmgunn;
    s32 getsgunn;
    s16 anlog_cnt;
    s16 pad_old;
    s16 pad_now;
    s16 pad_cnt;
    f32 anlog_old;
    s32 sord_st;
    s32 sord_keycnt;
    s32 sord_actionf;
    s32 sord_keybk;
    s32 sord_counter;
    s32 sord_mode;
    s8 sord_cflg;
    bool sord_bugfix;
    s32 sord_timeoutcnt;
    SKLID sword_nextskill;
    s32 sword_skillcnt;
    s32 sword_chaincnt;
    s32 combo_gunbeforeskill;
    s32 combo_nextskill_rs_cooltimeidx;
    s32 sord_cst;
    s32 sord_cstat;
    s32 sord_ccnt;
    s32 sord_cmode;
    s8 sord_chrgemode;
    s32 gun_cstat;
    s32 gun_ccnt;
    s32 gun_cmode;
    s8 gun_chrgemode;
    s16 huumastat;
    s32 huumagauge_w;
    s32 huumagauge_counter;
    s32 huumagauge_counter_start;
    s32 huuma_counter;
    s32 huuma_keycnt;
    s32 huumagauge_cnt;
    s32 huumagauge_cmpcnt;
    s32 huumagauge_para;
    s32 huumagauge_pcnt;
    s32 huumagauge_pcmpcnt;
    s32 huumagauge_ppara;
    s32 huumagauge_mag;
    s16 huuma_txtno;
    s16 huumamagnone;
    bool huumacancel;
    bool huumaMiss;
    s32 huuma_status_up[4];
    s32 huuma_targetID;
    s32 huuma_devilID[12];
    GaugeType gaugeType;
    sdatUnitWork_t *huuma_getUnit;
    s32 huuma_return_cnt;
    bool initHuumaMag;
    f32 itemGetWaitCount;
    s32 huuma_st_motion_cnt;
    bool huuma_weakicon;
    s32 HuumaInfo;
    s32 sklCsr;
    s32 skillMax;
    s32 modeSq;
    s32 sklType;
    s16 escape_stat;
    s16 escape_cnt;
    s16 escapegauge_w;
    f32 escapegauge_counter;
    f32 escapegauge_cnt;
    f32 escapegauge_num0;
    bool escape_flag;
    SBTLDROP_WORK *drop;
    bool dlcItemGet;
    s32 selectSkill;
    SKLID nakama_soroUseSkill;
    s32 BossHpGaugeStatus[2];
    s16 mf_mode;
    s16 mf_counter;
    s16 mf_cmpcounter;
    u32 mf_abgr;
    u32 mf_abgr_s;
    s16 mf_r;
    s16 mf_g;
    s16 mf_b;
    s16 mfh_mode;
    s16 mfh_counter;
    s16 mfh_cmpcounter;
    u32 mfh_abgr;
    u32 mfh_abgr_s;
    s16 mfh_r;
    s16 mfh_g;
    s16 mfh_b;
    s32 sord_repcnt;
    s32 sord_repkcnt;
    s32 sord_newcnt;
    s8 accele_flg;
    f32 accele_length;
    s32 accele_cnt;
    s8 sord_forceflg;
    SBTLPANEL_WORK *panelwk;
    f32 bossoldhp;
    SBTLITEM_TBL *item_keep;
    SBTLTALK_WORK *talkwk;
    SBTLDVLTK_LISTWORK *dvltkList;
    SBTLEXP_LISTWORK *expList;
    s16 spirit_enemy;
    bool fast_dying;
    s32 sprit_waza;
    s32 sprit_waza_usecnt;
    f32 raidouWazaCool[3];
    f32 raidouCoolTime;
    s32 gouto_startlvl;
    s32 gouto_zouen;
    s32 hitCombDevilTalk_1;
    s32 hitCombDevilTalk_2;
    s32 deadDevilTalk;
    s32 deadDevilTalk_log1;
    s32 deadDevilTalk_log2;
    bool firstDevilTalk;
    s32 hitokoto_gunuse;
    SBTLSTP_LISTWORK *stpList;
    scrHandle_t *hAIScript;
    scrHandle_t *hDEADScript;
    SBTLUNIT_WORK *scrunit;
    SBTLUNIT_WORK *scrEventUnit;
    f32 scrZoomRatio;
    s32 scrZoomFrame;
    s32 scrZoomOutFrame;
    s32 scrCutinID;
    s32 scrMsgID;
    s32 scrStep;
    s32 scrLoadStat;
    s32 scrUnitNum;
    SBTLUNIT_WORK *scrUnitList[16];
    s32 scrCmpCnt;
    s32 scrCnt[4];
    s32 scrEncountNo;
    s32 scrFlag;
    s8 scr_flg;
    s32 enshutuCnt[8];
    s32 enshutuCmpCnt[8];
    s32 scrData[8];
    s32 scrWarp[4];
    s32 EscOdds;
    s32 support_ListID;
    s32 supportindex;
    s32 hitst_sttime;
    s32 hitst_stcnt;
    s32 hitst_cnt;
    s32 hitst_cmpcnt;
    s32 setsuma_pad_stop_sttime;
    s32 setsuma_pad_stop_stcnt;
    s32 setsuma_pad_stop_cnt;
    s32 setsuma_pad_stop_cmpcnt;
    s32 enemylastdead_stop_sttime;
    s32 enemylastdead_stop_stcnt;
    s32 enemylastdead_stop_cnt;
    s32 enemylastdead_stop_cmpcnt;
    f32 enemylastdead_stop_spd_player;
    f32 enemylastdead_stop_spd_enemy;
    s32 cameratype;
    SBTLANIM_HOKAN *hanimwk;
    s16 camera_mode;
    s16 collider_type;
    f32 collider_center_x;
    f32 collider_center_y;
    f32 collider_center_z;
    SBTLSOUND_STATUSWORK *se_status;
    bool fSEDistance;
    bool fSEDouji;
    bool fSEPan;
    s8 cmbAtkSt;
    f32 camTgtConsF;
    s32 camTgtConsI;
    SBTLUNIT_WORK *pCamTgt;
    s32 tgtUpCnt;
    bool bCamUE;
    bool bCamUE2;
    f32 camRotY;
    s32 gunTgtId;
    s8 nakamaAtkPos;
    s8 nakamaAtkPos0;
    s8 nakamaAtkPos1;
    bool bBfrBtlEnd;
    bool bNoUseSkl;
    s32 ctrlSmnIdx;
    CMBSKL *cmbSkl;
    s8 l1cnt;
    s8 r1cnt;
    s8 rsvCmbSklCnt;
    s32 rsvCmbSkl[2];
    s32 rsvCmbTgt[2];
    SBTLUNIT_WORK *ai_tgt;
    u32 ai_skl;
    bool bUseCrsMenu;
    CROSS_MENU *crsMenu;
    CROSS_MENU *crsMenu2;
    SUMMON_CTRL *smnCtrl;
    s32 mapmdl;
    dds3Basic_t *apMarkerUnit[8];
    dds3Basic_t *apMarkerUnitR[8];
    RED_GUAGE *aRedGuage[3];
    STATUS_BAR *aStatusBar[3];
    s32 grnCnt;
    _S_KETTOU *kettou;
    s32 magGgCnt;
    s32 magGgCntTgt;
    s32 aAiGgFlsAlpha[2];
    E_SBTLMAIN_STEP step;
    SKLID sword_eff_skl;
    s32 sword_eff_step;
    s32 sword_eff_kind;
    s32 sword_eff_nakama;
    f32 yure_pos_y;
    f32 yure_pow_y;
    f32 yure_spring;
    SBTLUNIT_WORK *pLoadingUnit;
    SBTLEFF_WORK *sword_eff;
    SBTLEFF_WORK *gun_effL;
    SBTLEFF_WORK *gun_effR;
    SBTLEFF_WORK *sword_eff_cmb;
    bool bEffStop;
    bool bEffNoDraw;
    s32 weaponId;
    s32 kochokuCnt;
    bool maigoEnc;
    bool saikaiEnc;
    bool hitStop;
    bool setsuma_pad_Stop;
    bool enemylastdead_Stop;
    void *dbgptr;
    bool effNoStop;
    bool effNoStop2;
    dds3ModelHandle_t *hMapMdl;
    dds3ModelHandle_t *hMapMdl2;
    u32 mapclr;
    u32 mapfadeclr;
    s32 mapfade;
    s32 bltNumDrwCnt;
    bool bEnemyFrcWait;
    s32 camSlpMode;
    s32 magUpCnt;
    s32 bltUpCnt;
    s32 viceUpCnt[2];
    s32 viceUpCntE;
    s32 vice1stKoufun;
    s32 chargeSdCnt;
    f32 chargeSdCnt2;
    s32 chargeLcCnt;
    f32 chargeLcCnt2;
    s32 chargeAxCnt;
    f32 chargeAxCnt2;
    s32 chargeGunCnt;
    s32 chargeGunCnt2;
    s32 rrCnt;
    s32 ComboLRU_Cnt;
    bool ComboLRU_StartOk;
    s32 CameraTgtSelect_Cnt;
    s32 bCameraTgtSelect1Cnt;
    bool bCameraGazeOffToOn_Press;
    bool bIsNoMoveBad;
    bool bRU;
    bool bRR;
    bool bRU_Assist;
    bool bRR_Assist;
    bool bChgSd;
    bool bChgSd0;
    bool bChgLc;
    bool bChgLc0;
    bool bChgAx;
    bool bChgAx0;
    bool bChgGun;
    bool bGun;
    bool bJump;
    bool bJump2;
    bool bGuard;
    bool bKaihi;
    bool bGunMode;
    bool bComboSRU;
    bool bComboSRU_NowChk;
    bool bComboLRU;
    bool bSetsuma;
    bool bRaiSkill_RU;
    bool bRaiSkill_RL;
    bool bRaiSkill_RD;
    bool bRaiSkill_RU_Pause;
    bool bRaiSkill_RL_Pause;
    bool bRaiSkill_RD_Pause;
    bool bSpiritSkill;
    s32 SpiritSkillNakamaIdx;
    bool bCameraTgtSelect1;
    bool bCameraTgtSelect2;
    bool bCameraTgtSelectU;
    bool bCameraTgtSelectD;
    bool bCameraTgtSelectR;
    bool bCameraTgtSelectL;
    bool bCameraTgtSelectUse;
    bool bCameraGazeOff;
    bool bHuumaCancel;
    s32 AttackBtn_NgTime;
    s32 ComboMotRetryCnt;
    bool ComboMotRetryUse;
    f32 ComboMotRetryOldFrame;
    bool NakamaShugouOn;
    bool NakamaTgtModeOn;
    bool bAssistAttackBtn;
    s32 hitComboNum;
    s32 GunLockOnNum;
    s32 GunLockOnTgtID[6];
    s32 GunLockOnTgtSubIdx[6];
    s32 GunLockOnTgtDone[6];
    s32 GunLockOnTgtPushPop[6];
    s32 GunRapidNum;
    s32 GunRapidCnt;
    SBTL_MAGEFF *aMagEff[100];
    s32 pMagEffListStart;
    s32 pMagEffNextSearch;
    HITEFFLIST *hitEffList;
    s32 aiBgnCnt;
    _BARCTRL *barCtrl;
    SKLID camSkl;
    SBTLUNIT_WORK *pCamSklUser;
    SBTLUNIT_WORK *pCamSklUser2;
    bool bCamSklNoWait;
    s32 camSklCnt;
    s32 aTateHitID[16];
    s32 aTateHitFlg[16];
    s32 tateHitCnt;
    s32 addEnemyCamCnt;
    u8 tateBg_pData;
    plistHandle_t *tateBg_hPartsList;
    SBTLEFF_WORK *pEffTateBg;
    bool bTateNoDmg;
    _RNDHIT *rndHit;
    _SKLPROC *sklProc;
    S_BLUR *sBlur;
    s16 kaiwa_txtno;
    s16 kaiwa_step;
    s16 kaiwa_result;
    s16 kaiwa_seltxtno;
    s16 kaiwa_item;
    s16 kaiwa_item_num;
    s32 kaiwa_money;
    s32 kaiwaselectID;
    s32 kaiwa_gstat;
    s16 kaiwa_mode;
    SBTLUNIT_WORK *sinwa_wk;
    s8 bosseveloadflg;
    s8 bosseventflg;
    s8 kaiwaflg;
    s8 kaiwapaneldisp0;
    s8 kaiwapaneldisp1;
    s8 timeflg;
    s8 timedrawflg;
    s8 countdownflg;
    s32 timecount;
    BTL_TIME timeresult;
    BOSSACT bossflow;
    bool bossflow_camdone;
    s32 aitimecount;
    s8 aitimeflg;
    s8 kaiwamemflg;
    s8 eventMemory[32];
    s16 event_actno;
    s16 event_icon;
    dds3ProcessID_t *event_cutID;
    s8 bosshpdrawnum;
    s8 geirinstep;
    s16 geirincnt;
    s16 sukacnt;
    s32 boss_eventID;
    s32 boss_devilID;
    s16 boss_timeno;
    bool bNoEndCam;
    bool bNoEnemyName;
    s8 senseimode;
    s32 rouletteId;
    s32 raido_magwaza_costnot;
    s32 start_debug_menu_on;
    s32 gStartBossCamCnt;
    s32 RouletteAfterTime;
    s32 RouletteUseCnt;
    u32 RouletteStBotKuda;
    u32 RouletteAns;
    u32 RouletteGoodOrBad;
    u32 NotCnt_R1R2;
    u32 NotCmbSkl_Cnt;
    u32 NotCmbSkl_Cnt2;
    u32 NotCmbSkl_Ex;
    u32 NotSinaba_Cnt;
    void *bsc;
    void *buc;
    void *readdvl;
    char *readmap;
    u32 fieldmap_use;
    bool encount_fieldmap_load_done;
    bool closedOkDisp[2];
    bool removeCallMark[2];
    bool CameraLockOn;
    s32 CameraLockOnTgtID;
    bool CameraLockOnNear;
    bool CameraLockAutoNextOn;
    f32 CameraLockAutoNextWaitTime;
    bool CameraGazeOff;
    bool CameraReset;
    s32 Camera_EnemyDeadNear_ListID;
    s32 Camera_EnemyDeadNear_UID;
    f32 PlayerBtlStartPosX;
    f32 PlayerBtlStartPosY;
    f32 PlayerBtlStartPosZ;
    f32 PlayerBtlStartDir;
    f32 NakamaBtlStartPosX[2];
    f32 NakamaBtlStartPosY[2];
    f32 NakamaBtlStartPosZ[2];
    f32 NakamaBtlStartDir[2];
    f32 CameraBtlStartX;
    f32 CameraBtlStartY;
    bool KaihiSetsuma;
    SKLID KaihiSetsuma_SkillId;
    bool BtlEnd_Boss_Sprit;
    bool BtlEnd_BossFedeOut;
    bool TipsDone_KATANA_S;
    bool TipsDone_ACT;
    bool TipsDone_DUDGE;
    bool TipsDone_COME_NAKAMA;
    bool TipsDone_WEAK_SHIELD;
    bool ChkNG_TutoEtc_AllOk;
    bool t1_3_nakama;
    bool tuto_r2_di;
    bool battlStopEff;
    s32 setsuma_BS_LASTB3_cnt;
    bool XAtkGouto1;
    s32 r2ng;
    bool BossDmgEffect_Hit;
    void *deadUnit;
    s32 callTips;
    void *huuinUnit;
};

struct SBATTLE_WORK2 {
    SBTLEFF_PACLIST *effpac[150];
    SBTLEFF_PACFILE_EPL *effOnRsc_P;
    s16 effpaccnt;
};

struct SBATTLE_WORK3 {
    SBTLPACDATA_WORK *pacdata[16];
    s16 pacdata_index;
};

extern char *ret_field_scene;
extern bool battle_map_loadend;
extern SBATTLE_WORK *wk;
extern SBATTLE_WORK2 *wk2;
extern SBATTLE_WORK3 *wk3;
extern SBTLMAIN_DATA *main_data;
extern SBTLEFF_DATAWORK *wkeffOnMem;
extern sdatPlayerUnitWork_t *tutorial_bk;
extern bool escape_checkflg;
extern bool kaiwa_btlendflg;
extern bool epl_otchkflg;
extern u32 frame_cnt;
extern u32 runtime_cnt;
extern u8 *ai_scr;
extern u8 *huuma_success_scr;

void LimitRange(s32 *x, s32 l, s32 h);
void LimitRange_2(s16 *x, s16 l, s16 h);
void LimitRange_3(u32 *x, u32 l, u32 h);
void LimitRange_4(s8 *x, s8 l, s8 h);
void LimitRange_5(f32 *x, s32 l, s32 h);
void EncountAiPackLoad(void);
void LoadTableData(void);
void ReloadDLCTableData(void);
void Printf(char *str, void *LegacyParamArray);
void Init(s32 mode, s32 encountno);
dds3ProcessFunc_t Proc(dds3ProcessID_t *id);
void Shutdown(dds3ProcessID_t *id);
dds3ProcessFunc_t DrawProc(dds3ProcessID_t *id);
dds3ProcessFunc_t DrawProc2(dds3ProcessID_t *id);
bool CheckEnd(void);
void HdBtlEndCam(void);
void ChkInochigoi(void);
bool ChkSensei(void);
bool ChkSenseiDamage(void);
bool ChkMyth(void);
bool Start(SBTLMAIN_DATA *data, s32 flg);
bool Exit(s32 type);
void MokutekiOFF(void);
void ClearFlgOnGameOver(void);
void Exit2(void);
void Exit3Set(void);
void Exit3(void);
void StopKey(void);
bool StopBattle(void);
bool IsSceanStop(void);
bool CheckStopBattle(void);
bool RestartBattle(void);
bool StopBattle_StopUV(void);
bool ReloadTableData(void);
bool LoadOnMemoryData(void);
void SmnCtrlRun(void);
bool CheckRun(void);

// macros
// 0x18f06d0: s32 GETITEMPARA_LOW(s32 ipara)
#define GETITEMPARA_LOW(ipara) ((u8)ipara)

// 0x18f06e0: s32 GETITEMPARA_HIGH(s32 ipara)
#define GETITEMPARA_HIGH(ipara) (BYTE1(ipara))

// 0x18f06f0: s32 GETITEMPARA(s32 ipara)
#define GETITEMPARA(ipara) (BYTE1(ipara) + (u8)ipara)

// 0x18f0700: void PRINTF(char *p)
#define PRINTF(p) do { \
    ; \
} while (0)

// 0x1ecd0b0: SBTL_ACTAIFLG ACTAIFLGMASK(void)
#define ACTAIFLGMASK() (33311)
