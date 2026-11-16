#include "types.h"
#include "buttonguide.h"
#include "cmpmodel.h"
#include "dat.h"
#include "dds3_pad.h"
#include "dds3adminiprocess.h"
#include "dds3areabasic.h"
#include "dds3basic.h"
#include "dds3effect.h"
#include "dds3kernelcore.h"
#include "dds3kerneldraw.h"
#include "dds3worldbasic.h"
#include "evtbit.h"
#include "fclmisc.h"
#include "fclmsg.h"
#include "file.h"
#include "fld.h"
#include "itf.h"
#include "jmsmain.h"
#include "kernel.h"
#include "localize.h"
#include "mdl.h"
#include "mjn.h"
#include "p2sdplay.h"
#include "raijindlc.h"
#include "sbtldvltk.h"
#include "sbtlsound.h"
#include "sbtlsub.h"
#include "sdat.h"
#include "sdf_vu0.h"
#include "sdfmem.h"
#include "sdfquat.h"
#include "sdfrand.h"
#include "sdfsound.h"
#include "sdfvu0.h"
#include "sndat3.h"
#include "sndmanager.h"

#define NONE 0
#define CROSS 1
#define INIT_END 65536
#define FREE 131072
#define POP 262144
#define REQ_TERM 1048576
#define TERM 2097152
#define RE_ENT 4194304
#define SYSMASK 4294901760

#define CALC_PROCESS_NAME "mjntips_calc"
#define DRAW_PROCESS_NAME "mjntips_calc"
#define UPDT_PROCESS_NAME "mjntips_calc"
#define MENU_MAINPROC_NAME "mjntips_menu_main"
#define MENU_DRAWPROC_NAME "mjntips_menu_draw"

#define MJN_MSG_TSUMO 0
#define MJN_MSG_RON 1
#define MJN_MSG_OYA 2
#define MJN_MSG_TOP 3
#define MJN_MSG_PON 4
#define MJN_MSG_CHI 5
#define MJN_MSG_KAN 6
#define MJN_MSG_REACH 7
#define MJN_MSG_START 8
#define MJN_CAMERA_EYE_DEFAULT_X 0
#define MJN_CAMERA_EYE_DEFAULT_Y -188
#define MJN_CAMERA_EYE_DEFAULT_Z -58
#define MJN_CAMERA_TARGET_DEFAULT_X 0
#define MJN_CAMERA_TARGET_DEFAULT_Y -80
#define MJN_CAMERA_TARGET_DEFAULT_Z 0
#define MJN_RENHO_NUM 8
#define MJN_AGARI_MAX 1024
#define MJN_ANALYSIS_MAX 1024
#define MJN_ANALYZE_NODE_MAX 2048
#define MJN_TYPE_JIHAI 0
#define MJN_TYPE_ROUTOU 1
#define MJN_TYPE_CHUNCHAN 2
#define SBTL_FRAMERATE 60
#define SBTL_MTION_DEFSPD 0.5
#define SBTL_TIMERATE 2
#define SBTL_DEFMOTION_FRAME 4
#define SBTLPLAYER_DUMMYTARGET -1
#define SBTL_DROPITEM_NUM 12
#define SBTL_DROPEITEM_NUM 4
#define SBTL_HOMINGP1 0.5
#define SBTL_HOMINGP2 0.7
#define SBTLSE_AREA_NUM 30
#define KEYCMND_NONE 0
#define KEYCMND_PRESS 2147483648
#define KEYCMND_TRIG 1073741824
#define KEYCMND_PRESST 536870912
#define KEYCMND_HALL 134217728
#define KEYCMND_U 4096
#define KEYCMND_D 8192
#define KEYCMND_R 16384
#define KEYCMND_L 32768
#define KEYCMND_RU 65536
#define KEYCMND_RD 131072
#define KEYCMND_RR 262144
#define KEYCMND_RL 524288
#define KEYCMND_MASK 268431360
#define KEYCMND_CNTMASK 4095
#define KEYEQ_DATAMASK 65535
#define KEYEQ_NORMAL 0
#define KEYEQ_ENDF 65536
#define KEYEND_CANCEL 1
#define KEYEND_MOTIONEND 2
#define KEYEND_ENDF 4
#define SBTLMAIN_DATA_TYPE_SYM 0
#define SBTLMAIN_DATA_TYPE_ENC 1
#define EFFPARTS_VERSION 200
#define EFFPARTSLIST_ITEM_COPY 1
#define EFFPARTSLIST_PARTS_SCALE 1
#define EFFPARTSLIST_POSE_TM 1
#define MJN_MEMDEBUG 0
#define MJN_DEBUG 0
#define MJN_DEBUG_PRINT 0
#define MJN_SUTEHAI_MAX 32
#define MJN_HAI_MODEL_MAX 160
#define MJN_NONE 0
#define MJN_TSUMO 1
#define MJN_REACH 2
#define MJN_ANKAN 4
#define MJN_KAKAN 8
#define MJN_RON 16
#define MJN_PON 32
#define MJN_MINKAN 64
#define MJN_UECHI 268435584
#define MJN_CHUCHI 268435712
#define MJN_SHITACHI 268435968
#define MJN_CHI 268435456
#define MJN_KYUSHU 4096
#define MJN_END 8192
#define MJN_AGARI 1
#define MJN_FURITEN 2
#define MJN_YAKUNASHI 3
#define MJN_RYUKYOKU 4
#define MJN_SUFON 6
#define MJN_ALLREACH 7
#define MJN_SUKAN 8
#define MJN_NOTENREACH 9
#define MJN_TATE 0
#define MJN_YOKO 1
#define MJN_DEBUGMENU_NUM 20
#define MJN_TSUMIKOMI_PATTERN_MAX 36
#define MJN_FLAG_NONE 0
#define MJN_FLAG_REACH_PRESUTE 1
#define MJN_FLAG_REACH_CHOOSE 2
#define MJN_SYS_YESNO 0
#define MJN_SYS_ASK 1
#define MJN_SYS_END_CONF 2
#define MJN_SYS_GAIN 3
#define MJN_SYS_LOSS 4
#define MJN_SYS_NARUMI 5
#define MJN_SYS_MONEY_MAX 6
#define SDF_FLOAT_1_INT 1065353216
#define MJN_MENU_PROCESS_NAME "mahjon menu process"
#define MJN_CUTIN_WAIT_FRAME 150
#define MJN_WANPAIINDEX_DORA 8
#define MJN_WANPAIINDEX_KANDORA00 6
#define MJN_WANPAIINDEX_KANDORA01 4
#define MJN_WANPAIINDEX_KANDORA02 2
#define MJN_WANPAIINDEX_KANDORA03 0
#define MJN_WANPAIINDEX_URADORA 9
#define MJN_WANPAIINDEX_URAKANDORA00 7
#define MJN_WANPAIINDEX_URAKANDORA01 5
#define MJN_WANPAIINDEX_URAKANDORA02 3
#define MJN_WANPAIINDEX_URAKANDORA03 1
#define MJN_WANPAI_MAX 14
#define MJN_WANPAI_INDEX_DORAHYOUJI 6
#define MJN_NAKIMENU_X 150
#define MJN_NAKIMENU_Y 250
#define MJN_NAKIMENU_W 200
#define MJN_NAKIMENU_COLOR 1075847200
#define MJN_AGARI_X 145
#define MJN_AGARI_Y 122
#define MJN_AGARI_NAME_OFFX 50
#define MJN_AGARI_TENSU_X 250
#define MJN_AGARI_W 200
#define MJN_AGARI_H 203
#define MJN_AGARI_BG_COLOR 1612718112
#define MJN_INFO_X 170
#define MJN_INFO_Y 136
#define MJN_INFO_W 178
#define MJN_INFO_H 68
#define MJN_INFO_TEXT_X 195
#define MJN_INFO_TEXT_Y 140
#define MJN_INFO_TENSU_X 110
#define MJN_INFO_BG_COLOR 1075847200
#define MJN_END_X 60
#define MJN_END_Y 120
#define MJN_WHITE 2164260863
#define MJN_BROWN 2149597280
#define MJN_HIGHLIGHT 1073741888
#define MJN_TEX_W 512
#define MJN_TEX_H 512
#define MJN_GREEN 2147500048
#define MJN_TABLE_LENGTH 50
#define MJN_TEHAI3D_OFFSIDE 27
#define MJN_TEHAI3D_OFFSIDE0 15
#define MJN_TEHAI3D_OFFBOTTOM 6
#define MJN_TEHAI3D_OFFBOTTOM0 20
#define MJN_TEHAI3D_HEIGHT -3
#define MJN_SUTEHAI_COLCOUNT 6
#define MJN_SUTEHAI_LASTLINE_LIMIT 18
#define MJN_SUTEHAI3D_OFFSIDE 35
#define MJN_SUTEHAI3D_OFFBOTTOM 30
#define MJN_SUTEHAI3D_OFFBOTTOM0 40
#define MJN_NAKI3D_OFFSIDE 10
#define MJN_NAKI3D_GAP 1
#define MJN_WANPAI3D_X -15
#define MJN_WANPAI3D_Z 0
#define MJN_RED 2147483776
#define MJN_OYA3D_SIZE 7
#define MJN_INFOUNIT_W 120
#define MJN_INFOUNIT_H 55
#define MJN_INFOUNIT_BG_COLOR 1612718112
#define MJN_INFOUNIT_X0 180
#define MJN_INFOUNIT_Y0 330
#define MJN_INFOUNIT_X1 360
#define MJN_INFOUNIT_Y1 150
#define MJN_INFOUNIT_Y2 10
#define MJN_INFOUNIT_X3 10
#define MJN_REACH3D_OFFSIDE 45
#define MJN_REACH3D_OFFBOTTOM 33
#define MJN_REACH3D_OFFBOTTOM0 43
#define MJN_OYA3D_OFFSIDE 28
#define MJN_OYA3D_OFFBOTTOM 20
#define MJN_TABLE_OFFSET 80
#define MJN_FONT_COLOR_BLUE 1862254784
#define MJN_FONT_COLOR_RED 1849704703
#define MJN_SPECIAL_FONT_COLOR 1849704703
#define MJN_NAME_WIDTH 110
#define MJN_HAI_WIDTH 4
#define MJN_HAI_HEIGHT 5.2
#define MJN_HAI_DEPTH 3
#define MJN_HAI_DIFF 1.1999998
#define MJN_AGARI_COUNT 90
#define MJN_AGARI_UIDRAW 30
#define MJN_PROCESS_NAME "mahjon main process"
#define MJN_DRAW_PROCESS_NAME "mahjon draw process"
#define MJN_TEX1_FILENAME "mahjong01.tmx"
#define MJN_TEXRULE_FILENAME "mjn_rule01.tmx"
#define MJN_TEXYAKU_FILENAME "mjn_rule02.tmx"
#define MJN_TEXRESULT_FILENAME "mjn_result.tmx"
#define MJN_HAPPY_JINGLE_FILENAME "mahjon07.at3"
#define MJN_SAD_JINGLE_FILENAME "mahjon08.at3"
#define MJN_CUTIN_SPRITE_FILENAME "nakama_win.spr"
#define MJN_SUMMON_FILENAME "SUMMON_NO.EPL"
#define MJN_VISUAL_FILENAME "MJN_VISUAL.TBL"
#define MJN_TSUMIKOMI_FILENAME "MJN_TMK.TBL"
#define MJN_HIGHLIGHTCOL_FILENAME "mjnHaiHighlightPar"
#define mjnKey "mahjon"
#define MJN_WAIT_FRAME 20
#define MJN_WAIT_FRAME2 1
#define MJN_MODEL_WAIT_BEFORE 30
#define MJN_MODEL_WAIT_AFTER 60
#define MJN_SUMMON_COUNT 500
#define MJN_SUMMON_EFFECT_COUNT 60
#define MJN_SMOOTH_BEFORE_FRAME 8
#define MJN_SMOOTH_FRAME 8
#define DVL_MJN_NARUMI 208
#define DVL_MJN_RAIDO 81
#define MJN_MAJOR 7
#define MJN_CAMERA_MOVE_COUNT 100
#define MJN_CAMERA_END_COUNT 300
#define MJN_BUTTONGUIDE_TIMER_MAX 120
#define MJN_SPR_FILENAME "sub.spr"
#define MJN_MENU_BACK_FILENAME "test_haikei.tmx"
#define MJN_MENU_MSG_FILENAME "mjnMenuMsg.bmd"
#define MJN_MENU_FADEOUT_COUNT 15
#define MJN_BRIDGE_PROCESS_NAME "mjn_bridge_process"
#define MJNMENU_BUTTONGUIDE_TIMER_MAX 120

typedef enum {
    MJN_ANALYZE_ROOT = 0,
    MJN_ANALYZE_SHUNTSU = 1,
    MJN_ANALYZE_KOTSU = 2,
    MJN_ANALYZE_TOITSU = 3,
    MJN_ANALYZE_KANCHAN = 4,
    MJN_ANALYZE_RYANMEN = 5,
    MJN_ANALYZE_NONE = 6,
} MJN_ANALYZE;

typedef enum {
    MJN_YAKU_PINFU = 0,
    MJN_YAKU_TANYAO = 1,
    MJN_YAKU_IPEIKO = 2,
    MJN_YAKU_REACH = 3,
    MJN_YAKU_IPPATSU = 4,
    MJN_YAKU_TSUMO = 5,
    MJN_YAKU_YAKUHAI = 6,
    MJN_YAKU_HAITEI = 7,
    MJN_YAKU_HOUTEI = 8,
    MJN_YAKU_RINSHAN = 9,
    MJN_YAKU_CHANKAN = 10,
    MJN_YAKU_DORA = 11,
    MJN_YAKU_CHITOI = 12,
    MJN_YAKU_CHANTA = 13,
    MJN_YAKU_ITTSU = 14,
    MJN_YAKU_SANSHOKUJUN = 15,
    MJN_YAKU_SANSHOKUPON = 16,
    MJN_YAKU_TOITOI = 17,
    MJN_YAKU_SANANKO = 18,
    MJN_YAKU_SANKANTSU = 19,
    MJN_YAKU_RYANPEIKO = 20,
    MJN_YAKU_HONITSU = 21,
    MJN_YAKU_JUNCHAN = 22,
    MJN_YAKU_SHOUSANGEN = 23,
    MJN_YAKU_HONROTO = 24,
    MJN_YAKU_RENHO = 25,
    MJN_YAKU_CHINITSU = 26,
    MJN_YAKU_DOUBLEREACH = 27,
    MJN_YAKU_SUANKO = 28,
    MJN_YAKU_SUKANTSU = 29,
    MJN_YAKU_DAISANGEN = 30,
    MJN_YAKU_KOKUSHI = 31,
    MJN_YAKU_TENHO = 32,
    MJN_YAKU_CHIHO = 33,
    MJN_YAKU_SUSHIHO = 34,
    MJN_YAKU_TSUISO = 35,
    MJN_YAKU_CHINROTO = 36,
    MJN_YAKU_RYUISO = 37,
    MJN_YAKU_CHUREN = 38,
    MJN_YAKU_MAX = 39,
} MJN_YAKU;

typedef enum {
    MJN_ANALYSIS_NORMAL = 0,
    MJN_ANALYSIS_CHITOI = 1,
    MJN_ANALYSIS_KOKUSHI = 2,
} MJN_ANALYSIS;

typedef enum {
    MJN_TYPE_MANZU = 0,
    MJN_TYPE_PINZU = 1,
    MJN_TYPE_SOZU = 2,
    MJN_TYPE_KAZE = 3,
    MJN_TYPE_SANGEN = 4,
} MJN_TYPE;

typedef enum {
    MJN_PHASE_INIT = 0,
    MJN_PHASE_SUMMON = 1,
    MJN_PHASE_ANALYSIS = 2,
    MJN_PHASE_MAIN = 3,
    MJN_PHASE_CHECKNAKI = 4,
    MJN_PHASE_NAKIWAIT = 5,
    MJN_PHASE_AGARI = 6,
    MJN_PHASE_ENDWAIT = 7,
    MJN_PHASE_END = 8,
    MJN_PHASE_MODEL = 9,
    MJN_PHASE_MSG = 10,
    MJN_PHASE_ENDHANCHAN = 11,
    MJN_PHASE_KAN = 12,
    MJN_PHASE_WAIT = 13,
} MJN_PHASE;

typedef enum {
    MJN_MODELPHASE_LOADSE = 0,
    MJN_MODELPHASE_INIT = 1,
    MJN_MODELPHASE_CAMERA = 2,
    MJN_MODELPHASE_WAIT_BEFORE = 3,
    MJN_MODELPHASE_MOTION = 4,
    MJN_MODELPHASE_WAIT_AFTER = 5,
} MJN_MODELPHASE;

typedef enum {
    MJN_SUMMONPHASE_INIT = 0,
    MJN_SUMMONPHASE_PROC = 1,
} MJN_SUMMONPHASE;

typedef enum {
    MJN_TSUMIKOMI_YAKUHAI1 = 0,
    MJN_TSUMIKOMI_YAKUHAI2 = 1,
    MJN_TSUMIKOMI_YAKUHAI3 = 2,
    MJN_TSUMIKOMI_YAKUHAI4 = 3,
    MJN_TSUMIKOMI_CHINITSU8 = 4,
    MJN_TSUMIKOMI_CHINITSU9 = 5,
    MJN_TSUMIKOMI_CHINITSU10 = 6,
    MJN_TSUMIKOMI_CHINITSU11 = 7,
    MJN_TSUMIKOMI_CHINITSU12 = 8,
    MJN_TSUMIKOMI_CHINITSU13 = 9,
    MJN_TSUMIKOMI_IPEIKO = 10,
    MJN_TSUMIKOMI_SANSHOKUJUN = 11,
    MJN_TSUMIKOMI_ITTSU = 12,
    MJN_TSUMIKOMI_YAKUHAI1CHINITSU9 = 13,
    MJN_TSUMIKOMI_YAKUHAI1CHINITSU10 = 14,
    MJN_TSUMIKOMI_KANTSU1 = 15,
    MJN_TSUMIKOMI_KANTSU2 = 16,
    MJN_TSUMIKOMI_TOITSU3 = 17,
    MJN_TSUMIKOMI_TOITSU4 = 18,
    MJN_TSUMIKOMI_TOITSU5 = 19,
    MJN_TSUMIKOMI_TOITSU6 = 20,
    MJN_TSUMIKOMI_KOTSU1 = 21,
    MJN_TSUMIKOMI_KOTSU2 = 22,
    MJN_TSUMIKOMI_KOTSU3 = 23,
    MJN_TSUMIKOMI_SHUNTSU1 = 24,
    MJN_TSUMIKOMI_SHUNTSU2 = 25,
    MJN_TSUMIKOMI_SHUNTSU3 = 26,
    MJN_TSUMIKOMI_KOKUSHI9 = 27,
    MJN_TSUMIKOMI_KOKUSHI10 = 28,
    MJN_TSUMIKOMI_KOKUSHI11 = 29,
    MJN_TSUMIKOMI_KOKUSHI12 = 30,
    MJN_TSUMIKOMI_KOKUSHI13 = 31,
    MJN_TSUMIKOMI_TOITSU3KOTSU1 = 32,
    MJN_TSUMIKOMI_RESV0 = 33,
    MJN_TSUMIKOMI_RESV1 = 34,
    MJN_TSUMIKOMI_RESV2 = 35,
} MJN_TSUMIKOMI;

typedef enum {
    MJN_MSG_PHASE_INIT = 0,
    MJN_MSG_PHASE_LOADING = 1,
    MJN_MSG_PHASE_READY = 2,
    MJN_MSG_PHASE_DRAWING = 3,
} MJN_MSG_PHASE;

typedef enum {
    MJN_AIM_CHINITSU_MANZU = 0,
    MJN_AIM_CHINITSU_PINZU = 1,
    MJN_AIM_CHINITSU_SOUZU = 2,
    MJN_AIM_HONITSU_MANZU = 3,
    MJN_AIM_HONITSU_PINZU = 4,
    MJN_AIM_HONITSU_SOUZU = 5,
    MJN_AIM_KOKUSHI = 6,
    MJN_AIM_MAX = 7,
} MJN_AIM;

typedef enum {
    MJN_PLAYERPHASE_TSUMORU = 0,
    MJN_PLAYERPHASE_ANALYZE = 1,
    MJN_PLAYERPHASE_CHOOSE = 2,
    MJN_PLAYERPHASE_CHOOSESUTEHAI = 3,
    MJN_PLAYERPHASE_SUTERU = 4,
    MJN_PLAYERPHASE_ANALYZEAFTER = 5,
    MJN_PLAYERPHASE_END = 6,
} MJN_PLAYERPHASE;

typedef enum {
    MJN_RSTSTEP_INIT = 0,
    MJN_RSTSTEP_MSG = 1,
    MJN_RSTSTEP_MAIN = 2,
    MJN_RSTSTEP_MSG_CALL = 3,
    MJN_RSTSTEP_MSG_WAIT = 4,
    MJN_RSTSTEP_FADEOUT = 5,
    MJN_RSTSTEP_DRAWEND = 6,
    MJN_RSTSTEP_DRAWFREE = 7,
    MJN_RSTSTEP_END = 8,
} MJN_RSTSTEP;

typedef enum {
    MJN_TIPS_STEP_MAIN = 0,
    MJN_TIPS_STEP_DRAW_OFF = 1,
    MJN_TIPS_STEP_RELEASE = 2,
    MJN_TIPS_STEP_END = 3,
} MJN_TIPS_STEP;

typedef enum {
    MJNTIPS_MENU_FLAG_RELEASE = 1,
    MJNTIPS_MENU_FLAG_LOAD_SPR = 2,
    MJNTIPS_MENU_FLAG_DRAW = 4,
    MJNTIPS_MENU_FLAG_CALL_DRAWBACK0 = 8,
    MJNTIPS_MENU_FLAG_CALL_DRAWBACK1 = 16,
    MJNTIPS_MENU_FLAG_DRAWBACK0 = 32,
    MJNTIPS_MENU_FLAG_DRAWBACK1 = 64,
} MJNTIPS_MENU_FLAG;

typedef enum {
    MJN_TIPSCALCSEQ_STAT_PUSH = 0,
    MJN_TIPSCALCSEQ_STAT_POP = 1,
    MJN_TIPSCALCSEQ_STAT_POPONLY = 2,
} MJN_TIPSCALCSEQ_STAT;

typedef enum {
    TIPS_MENU_ID_NONE = 0,
    TIPS_MENU_ID_RULE = 1,
    TIPS_MENU_ID_HOWTOPLAY = 2,
    TIPS_MENU_ID_HAI_INTRO = 3,
    TIPS_MENU_ID_YAKU_INTRO = 4,
    TIPS_MENU_ID_GLOSSARY = 5,
} TIPS_MENU_ID;

typedef enum {
    TIPS_SEQ_ROOT_WAIT = 0,
    TIPS_SEQ_ROOT = 1,
    TIPS_SEQ_HIERARCHY01 = 2,
    TIPS_SEQ_PANEL = 3,
    TIPS_SEQ_CALC = 0,
    TIPS_SEQ_DRAW = 1,
    TIPS_SEQ_UPDATE = 2,
} TIPS_SEQ;

typedef enum {
    TIPS_FLAG_NONE = 0,
    TIPS_FLAG_LOAD_NOW = 1,
    TIPS_FLAG_LOAD_END = 2,
    TIPS_FLAG_SPR_LOAD_NOW = 4,
    TIPS_FLAG_SPR_LOAD_END = 8,
    TIPS_FLAG_BG_LOAD_NOW = 16,
    TIPS_FLAG_BG_LOAD_END = 32,
    TIPS_FLAG_END_START = 64,
    TIPS_FLAG_END_NOW = 128,
    TIPS_FLAG_BGM_LOAD_NOW = 256,
    TIPS_FLAG_BGM_LOAD_END = 512,
    TIPS_FLAG_BGM_AFTER = 1024,
    TIPS_FLAG_BGM_CUSTOM = 2048,
    TIPS_FLAG_BGM_NONE = 4096,
    TIPS_FLAG_EVT_RUN = 8192,
} TIPS_FLAG;

typedef enum {
    MJNDEBUGCASE_OPENHAI = 0,
    MJNDEBUGCASE_EDIT01 = 1,
    MJNDEBUGCASE_EDIT02 = 2,
    MJNDEBUGCASE_EDIT03 = 3,
    MJNDEBUGCASE_EDIT04 = 4,
    MJNDEBUGCASE_TSUMOGIRI = 5,
    MJNDEBUGCASE_DEBUGAGARI = 6,
    MJNDEBUGCASE_CHONBOEDIT = 7,
    MJNDEBUGCASE_RYUKYOKUEDIT = 8,
    MJNDEBUGCASE_ALLSOLO = 9,
    MJNDEBUGCASE_DEBUGCAMERA = 10,
    MJNDEBUGCASE_DEBUGTARGET = 11,
    MJNDEBUGCASE_POSDIST = 12,
    MJNDEBUGCASE_CAMERATARGETHEIGHT = 13,
    MJNDEBUGCASE_CAMERADIST = 14,
    MJNDEBUGCASE_SCALE = 15,
    MJNDEBUGCASE_MODELMODE = 16,
    MJNDEBUGCASE_MESSAGETARGET = 17,
    MJNDEBUGCASE_MESSAGE = 18,
    MJNDEBUGCASE_WANTTSUMOHAI = 19,
} MJNDEBUGCASE;

typedef enum {
    MJN_MENU_STEP_NORMAL = 0,
    MJN_MENU_STEP_START = 1,
    MJN_MENU_STEP_END_CONF = 2,
    MJN_MENU_STEP_SETID = 3,
    MJN_MENU_STEP_INIT = 4,
    MJN_MENU_STEP_END = 5,
} MJN_MENU_STEP;

typedef enum {
    MJN_COLOR_SOUZU = 0,
    MJN_COLOR_MANZU = 1,
    MJN_COLOR_PINZU = 2,
    MJN_COLOR_JIHAI = 3,
} MJN_COLOR;

typedef enum {
    HIGHLIGHTID_DISABLE = -1,
    HIGHLIGHTID_NORMAL = 0,
    HIGHLIGHTID_NAKI = 1,
    HIGHLIGHTID_SUTE = 2,
    HIGHLIGHTID_PLDORA = 3,
} HIGHLIGHTID;

typedef enum {
    MJN_HAI_UP0 = 0,
    MJN_HAI_UP1 = 1,
    MJN_HAI_UP2 = 2,
    MJN_HAI_UP3 = 3,
    MJN_HAI_DOWN0 = 4,
    MJN_HAI_DOWN1 = 5,
    MJN_HAI_DOWN2 = 6,
    MJN_HAI_DOWN3 = 7,
    MJN_HAI_BACK = 8,
    MJN_HAI_BACK0 = 9,
    MJN_HAI_BACK1 = 10,
    MJN_HAI_BACK2 = 11,
    MJN_HAI_BACK3 = 12,
} MJN_HAI;

typedef enum {
    MJN_TMK_NONE = 0,
    MJN_TMK_RAIDO = 1,
    MJN_TMK_NARUMI = 2,
    MJN_TMK_SOME_1 = 3,
    MJN_TMK_SOME_2 = 4,
    MJN_TMK_SOME_3 = 5,
    MJN_TMK_KOTSU_1 = 6,
    MJN_TMK_KOTSU_2 = 7,
    MJN_TMK_KOTSU_3 = 8,
    MJN_TMK_SHUNTSU_1 = 9,
    MJN_TMK_SHUNTSU_2 = 10,
    MJN_TMK_SHUNTSU_3 = 11,
    MJN_TMK_SONOTA_1 = 12,
    MJN_TMK_SONOTA_2 = 13,
    MJN_TMK_SONOTA_3 = 14,
    MJN_TMK_RESERVE = 15,
} MJN_TMK;

typedef enum {
    MJN_MOT_WAIT = 0,
    MJN_MOT_SAD = 1,
    MJN_MOT_HAPPY = 2,
    MJN_MOT_SUMMON = 3,
    MJN_MOT_KIKAN = 4,
} MJN_MOT;

typedef enum {
    mjn_KEY_TYPE_NONE = -1,
    mjn_KEY_TYPE_UP = 0,
    mjn_KEY_TYPE_DOWN = 1,
    mjn_KEY_TYPE_RIGHT = 2,
    mjn_KEY_TYPE_LEFT = 3,
} mjn_KEY_TYPE;

typedef struct Agari_t Agari_t;
typedef struct AnalyzeNode_t AnalyzeNode_t;
typedef struct MJNTIPS_CLASS MJNTIPS_CLASS;
typedef struct MenuWork_t MenuWork_t;
typedef struct ModelLicense ModelLicense;
typedef struct NormalAnalysis_t NormalAnalysis_t;
typedef struct Player_t Player_t;
typedef struct Random_t Random_t;
typedef struct SeqHandle_t SeqHandle_t;
typedef struct SeqUnit_t SeqUnit_t;
typedef struct TehaiAnalysis_t TehaiAnalysis_t;
typedef struct TsumikomiHeader_t TsumikomiHeader_t;
typedef struct TsumikomiPattern_t TsumikomiPattern_t;
typedef struct Work_t Work_t;
typedef struct dds3ModelHandle_t dds3ModelHandle_t;
typedef struct dds3ProcessID_t dds3ProcessID_t;
typedef struct fileLoadAsset_Request fileLoadAsset_Request;
typedef struct mjn_tipsData_t mjn_tipsData_t;
typedef struct sdf3DLightParallelPacket_t sdf3DLightParallelPacket_t;
typedef struct tipsMenuWork_t tipsMenuWork_t;

typedef dds3ProcessFunc_t (*tipsFuncDelegate)(dds3ProcessID_t *ID);

struct TsumikomiHeader_t {
    u32 addr_tsumikomiProbTable;
    u32 addr_doraProbTable;
    u32 addr_devilTsumikomiTable;
    s32 size;
};

struct ModelLicense {
    dds3ModelHandle_t *modelhandle;
    bool license;
};

static s32 *mjn_tensuTableKoRon[10];
static s32 **mjn_tensuTableOyaRon;
static s32 **mjn_tensuTableKoTsumo;
static s32 **mjn_tensuTableOyaTsumo;
s32 *haiNumber;
s32 *pai_num;
static char *yakuMsgTable;
char *panel_rule_text;
char *panel_yaku_text;
static sdf3DLightParallelPacket_t *Highlight;
static sdf3DLightParallelPacket_t *Normallight;
static bool r_click;
s32 MJN_CHAIR;
bool MJN_GUIDEHELP_FLAG;
s32 MJN_BUTTONGUIDE_TIMER;
void *VisualDataTable;
void *TsumikomiDataTable;
void *TsumikomiProbTable;
void *DoraProbDataTable;
void *HilightCol;
void *ModelBuffer;
static bool butoonGuideAgariFlag;
static s32 MENU_DRAW_MAX;
static s32 MENU_PARENT_MAX;
char *spriteNameStr;
char *HaiIndexName;
static TsumikomiPattern_t *mjnTsumikomiPatternTable;
Work_t *Work;
s32 gMjnRun;
static s32 turnNum;
static s32 chipRecordNum;
static s32 *ChipRecord;
static char *mjn_scene_key;
fileLoadAsset_Request *sceneLoadReq;
bool TIPSOPEN;
static dds3ProcessID_t *TipsGlobalPID;
char *mjntipsDataAssetKey;
char *mjntipsDataAssetName;
char *titleLabel;
static SeqUnit_t *tipsSeqUnit;
char *szSeqNameNull;
static dds3ProcessID_t *g_mainPID;
MJNTIPS_CLASS *TIPSPAGE;
s32 *secondHi;
s32 *MenuParentID;
bool MenuActive;
void *MJN_SCENE;
s32 MJN_MENTSU_MENU_TOP_NUM;
s32 MJNMENU_BUTTONGUIDE_TIMER;
bool MJNMENU_GUIDEHELP_FLAG;
bool MjnMsgSetFlag;
static bool MenuMoveFlag;
s32 *DIDTable;
char *strMenu;
MenuWork_t *MenuWork;
static s32 gMjnDevil0;
static s32 gMjnDevil1;
static s32 gMjnDevil2;
static s32 gMjnLoadModelID;
static s32 gMjnCount;
static s32 gMjnLoadStat;
fileLoadAsset_Request *UIsceneLoadReq;
static void *debugmenu;
static char *mjnUI_scene_name;
static char *mahjonUIKey;
static char *mahjon_gKey;
static char *mahjonKey;
u8 **mjnDoraProbTable;
MJN_LV *DevilLevelTable;

static s32 CheckAgari(s32 playerIndex);
static s32 CheckAgariKokushi(s32 playerIndex);
static s32 CheckYakuhaiSub(s32 playerIndex, s32 hai);
static void PrintAnalysis(TehaiAnalysis_t *analysis);
static TehaiAnalysis_t *SetBestAnalysis(s32 playerIndex);
static s32 AIChooseSutehai(s32 playerIndex, TehaiAnalysis_t *analysis);
static void ApplyAgari(s32 playerIndex, s32 fromPlayerIndex);
static s32 CheckFuriten(s32 playerIndex);
static void ApplyChonbo(s32 playerIndex, s32 type);
static void UpdateTensu(Agari_t *agari);
static TehaiAnalysis_t *SetBestAnalysisSub(s32 playerIndex, TehaiAnalysis_t *bestAnalysis);
static void AnalyzeTehai(s32 playerIndex);
static s32 CheckYakuAri(s32 playerIndex, s32 tsumo, s32 agariHai);
static s32 CheckAgariSub(s32 *tehai34, s32 type);
static void CalcYaku(s32 playerIndex, NormalAnalysis_t *analysis, Agari_t *agari, s32 tsumo, s32 agariHai);
static void CalcYakuChitoi(s32 playerIndex, Agari_t *agari, s32 tsumo, s32 agariHai);
static void CalcYakuKokushi(s32 playerIndex, NormalAnalysis_t *analysis, Agari_t *agari, s32 tsumo, s32 agariHai);
static s32 GetHaiType(s32 hai);
static s32 CalcShanten(s32 playerIndex, NormalAnalysis_t *analysis);
static s32 HaiCountInTehai(s32 hai, s32 playerIndex);
static Agari_t *CalcAgari(s32 playerIndex, NormalAnalysis_t *analysis, s32 type);
static Agari_t *CalcAgariChack(s32 playerIndex, NormalAnalysis_t *analysis, s32 type, bool _bTsumo, s32 agariHai);
static NormalAnalysis_t *MakeAnalysis(s32 playerIndex, AnalyzeNode_t *node);
static void AnalyzeTehaiNormal(s32 playerIndex);
static void AnalyzeTehaiChitoi(s32 playerIndex);
static void AnalyzeTehaiKokushi(s32 playerIndex);
static void PrintAnalysisNormal(NormalAnalysis_t *analysis);
static s32 CheckAgariNormal(s32 playerIndex);
static s32 CheckAgariChitoi(s32 playerIndex);
static Agari_t *ChooseAgari(s32 playerIndex);
static AnalyzeNode_t *AnalyzeGetNextNode(AnalyzeNode_t *parent, s32 analyzeType);
static s32 AnalyzeCheckSubSequence(AnalyzeNode_t *node, AnalyzeNode_t *target);
static s32 AnalyzeTehaiSubTatsu(s32 playerIndex, s32 *tehai34, AnalyzeNode_t *node);
static s32 AnalyzeTehaiSubMentsu(s32 playerIndex, s32 *tehai34, AnalyzeNode_t *node);
static s32 CalcFu(s32 playerIndex, NormalAnalysis_t *analysis, s32 tsumo, s32 agariHai);
static void CalcTensu(s32 playerIndex, Agari_t *agari, s32 tsumo);
static s32 GetHaiColor(s32 hai);
static s32 GetMentsuType(s32 *mentsu);
static s32 CheckPinfu(s32 playerIndex, NormalAnalysis_t *analysis, s32 **tehai14, s32 agariHai);
static s32 CheckKuiPinfuGata(s32 playerIndex, NormalAnalysis_t *analysis, s32 agariHai);
static s32 CheckTanyao(s32 playerIndex, s32 *tehai14);
static s32 CheckReach(s32 playerIndex, s32 **tehai14);
static s32 CheckIppatsu(s32 playerIndex, s32 **tehai14);
static s32 CheckIpeiko(s32 playerIndex, NormalAnalysis_t *analysis, s32 **tehai14);
static s32 CheckYakuhai(s32 playerIndex, NormalAnalysis_t *analysis, s32 **tehai14);
static s32 CheckHaitei(s32 playerIndex, s32 tsumo);
static s32 CheckHoutei(s32 playerIndex, s32 tsumo);
static s32 CheckRinshan(s32 playerIndex, s32 **tehai14);
static s32 CheckChankan(void);
static s32 CheckDora(s32 playerIndex, s32 *tehai14);
static s32 CheckChanta(s32 playerIndex, NormalAnalysis_t *analysis, s32 **tehai14);
static s32 CheckTsumo(s32 playerIndex, s32 tsumo);
static s32 CheckIttsu(s32 playerIndex, NormalAnalysis_t *analysis, s32 **tehai14);
static s32 CheckSanshokujun(s32 playerIndex, NormalAnalysis_t *analysis, s32 **tehai14);
static s32 CheckSanshokupon(s32 playerIndex, NormalAnalysis_t *analysis, s32 **tehai14);
static s32 CheckToitoi(s32 playerIndex, NormalAnalysis_t *analysis, s32 **tehai14);
static s32 CheckSananko(s32 playerIndex, NormalAnalysis_t *analysis, s32 **tehai14, s32 tsumo, s32 agariHai);
static s32 CheckSankantsu(s32 playerIndex, NormalAnalysis_t *analysis, s32 **tehai14);
static s32 CheckRyanpeiko(s32 playerIndex, NormalAnalysis_t *analysis, s32 **tehai14);
static s32 CheckHonitsu(s32 playerIndex, s32 *tehai14);
static s32 CheckJunchan(s32 playerIndex, NormalAnalysis_t *analysis, s32 **tehai14);
static s32 CheckShousangen(s32 playerIndex, NormalAnalysis_t *analysis, s32 **tehai14);
static s32 CheckHonroto(s32 playerIndex, s32 *tehai14);
static s32 CheckChinitsu(s32 playerIndex, s32 *tehai14);
static s32 CheckDoubleReach(s32 playerIndex);
static s32 CheckRenho(s32 playerIndex, s32 tsumo);
static s32 CheckTenho(s32 playerIndex, s32 tsumo);
static s32 CheckChiho(s32 playerIndex, s32 tsumo);
static s32 CheckSuanko(s32 playerIndex, NormalAnalysis_t *analysis, s32 **tehai14, s32 tsumo, s32 agariHai);
static s32 CheckSukantsu(s32 playerIndex, NormalAnalysis_t *analysis, s32 **tehai14);
static s32 CheckDaisangen(s32 playerIndex, NormalAnalysis_t *analysis, s32 **tehai14);
static s32 CheckSushiho(s32 playerIndex, NormalAnalysis_t *analysis, s32 **tehai14);
static s32 CheckTsuiso(s32 playerIndex, s32 *tehai14);
static s32 CheckChinroto(s32 playerIndex, s32 *tehai14);
static s32 CheckRyuiso(s32 playerIndex, NormalAnalysis_t *analysis, s32 *tehai14);
static s32 CheckChuren(s32 playerIndex, NormalAnalysis_t *analysis, s32 **tehai14, s32 agariHai);
static TehaiAnalysis_t *SetBestAnalysisEx(s32 playerIndex, TehaiAnalysis_t *pAnalysis);
static s32 CalcHaiValue(s32 hai, s32 playerIndex);
static s32 CalcHaiValueTanki(s32 hai, s32 playerIndex);
static s32 CalcHaiValueChitoi(s32 hai, s32 playerIndex);
static s32 CheckYakunashi(Agari_t *agari);
static void PrintNode(AnalyzeNode_t *node);
static void PrintTree(AnalyzeNode_t *root);
static void StartCutin(s32 playerIndex, s32 msgID, s32 nextPhase, s32 flag, s32 hai);
static void ManageCutin(void);
static void Draw3D(void);
static bool RuleGuideClick(void);
static void DrawCalc(void);
static void InitCamera(void);
static void InitLight(void);
static void SetCamera(f32 posx, f32 posy, f32 posz, f32 targetx, f32 targety, f32 targetz);
static void KanjiDraw(s32 x, s32 y, s32 rgba, char **moji);
static void InitTenbouModel(void);
static void InitOyaModel(void);
static void DrawHai3DIndex(s32 index);
static void DrawHai3DModel(s32 index);
static void DrawHai3DTex(s32 index);
static void DrawNumber(s32 num, s32 offX, s32 offY, s32 sign, s32 rgba);
static void DrawNakiMenu(void);
static void KanjiDrawBig(s32 x, s32 y, s32 rgba, char **moji);
static void DrawName(s32 x, s32 y, s32 rgba, s32 playerIndex);
static void DrawAgariMessage(void);
static void DrawInfo(void);
static void DrawEndHanchan(void);
static void ApplyCamera(void);
static void DrawHai3DExCalc(f32 x, f32 y, f32 z, s32 hai, s32 direction, s32 highlight);
static void DrawHai3DCalc(f32 x, f32 z, s32 hai, s32 direction, s32 highlight);
static void DrawTable(void);
static void DrawTehai3DCalc(void);
static void DrawSutehai3DCalc(void);
static void DrawNakihai3DCalc(void);
static void DrawWanpai3DCalc(void);
static void setWanpaiDrawData(s32 index, MJN_HAI status);
static bool setWanpaiDrawFlag(MJN_HAI status);
static void DrawReach3D(void);
static void DrawOya3D(void);
static void DrawModel(void);
static void DrawYakuTex(void);
static void DrawRuleTex(void);
static void DrawInfoUnitEach(s32 playerIndex, s32 offX, s32 offY, s32 fAgari);
static void DrawInfoUnit(void);
static void InitEx(s32 devil0, s32 devil1, s32 devil2);
static void M_InitScene(void);
static dds3ProcessFunc_t MainLoop(dds3ProcessID_t *id);
static void Destroy(dds3ProcessID_t *id);
static dds3ProcessFunc_t DrawProcess(dds3ProcessID_t *id);
static void DrawDestroy(dds3ProcessID_t *id);
static void DrawMemFree(void);
static void ManageModelPhase(void);
static void PadDealer(void);
static void InitHanchan(void);
static void Tsumikomi(void);
static void TsumikomiDecide(Player_t *player);
static void TsumikomiHai(Player_t *player, s32 hai);
static void TsumikomiYakuhai(Player_t *player);
static void TsumikomiIpeiko(Player_t *player);
static void TsumikomiSanshokujun(Player_t *player);
static void TsumikomiIttsuSub(Player_t *player, s32 color);
static void TsumikomiIttsu(Player_t *player);
static void TsumikomiChinitsu(Player_t *player);
static void TsumikomiKantsu(Player_t *player);
static void TsumikomiToitsu(Player_t *player);
static void TsumikomiKotsu(Player_t *player);
static void TsumikomiShuntsu(Player_t *player);
static void TsumikomiKokushi(Player_t *player);
static void SwapRandom(Random_t *x, Random_t *y);
static void QsortRandom(Random_t **data, s32 firstIndex, s32 lastIndex);
static s32 DoraHyoujiToDora(s32 hyouji);
static void Kandora(void);
static void SetYama(void);
static void SetHaipai(void);
static void StartModelPhase(void);
static void NextKyoku(void);
static void InitKyoku(void);
static void EndHanchan(void);
static void Shukyoku(s32 renchan);
static void Ryukyoku(void);
static void TochuRyukyoku(s32 flag);
static void SetTehai14(s32 playerIndex);
static s32 TsumoruDora(s32 playerIndex);
static void Tsumoru(s32 playerIndex);
static void Suteru(s32 playerIndex, s32 haiIndex);
static void PlayerTurn(s32 playerIndex);
static void AITurn(s32 playerIndex);
static void Wait(void);
static void Dispatch(void);
static void Ignore(void);
static void NextTurn(void);
static void NakiWait(void);
static void CheckNaki(void);
static void ApplyRonNextTurn(s32 flag);
static void ApplyRonRyukyoku(s32 flag);
static s32 CheckPon(s32 playerIndex);
static s32 CheckAnkan(s32 playerIndex);
static s32 CheckAnkanReach(s32 playerIndex, s32 tsumoHai);
static s32 CheckKakan(s32 playerIndex);
static s32 CheckChi(s32 playerIndex);
static s32 CheckMinkan(s32 playerIndex);
static s32 CheckRon(s32 playerIndex);
static s32 CheckRonKokushi(s32 playerIndex);
static s32 CheckKyushu(s32 playerIndex);
static s32 CheckRon_Reach(s32 _hai, Player_t *_player);
static s32 AskReach(s32 playerIndex);
static s32 AskTsumo(s32 playerIndex);
static s32 AskRon(s32 playerIndex);
static s32 AskRonKokushi(s32 playerIndex);
static s32 AskPon(s32 playerIndex);
static s32 AskMinkan(s32 playerIndex);
static s32 AskChi(s32 playerIndex);
static s32 AskAnkan(s32 playerIndex);
static s32 AskKyushu(s32 playerIndex);
static void Agari(void);
static void ApplyTsumo(s32 playerIndex);
static void ApplyReach(s32 playerIndex);
static void ApplyReachEx(s32 playerIndex, s32 sutehaiIndex, s32 ichijunme);
static void ApplyAnkanEx(s32 playerIndex, s32 hai);
static void ApplyAnkanAI(s32 playerIndex, s32 hai);
static void ApplyAnkanPlayer(s32 playerIndex);
static void ApplyKakanEx(s32 playerIndex, s32 hai);
static void ApplyKakan(s32 playerIndex);
static void ApplyPon(s32 playerIndex, s32 fromPlayerIndex);
static void ApplyMinkan(s32 playerIndex, s32 fromPlayerIndex);
static void ApplyChi(s32 playerIndex, s32 chiType);
static void ApplyRon(s32 playerIndex, s32 fromPlayerIndex);
static void LoadTexToGSAll(void);
static void LoadJingleAll(void);
static void PlayJingle(s32 type);
static void FreeTexFromGSAll(void);
static void FreeEffect(void);
static void LoadTsumikomiData(void);
static void InitDevil(s32 playerIndex, s32 devilID);
static void FreeModel(void);
static void InitCameraSummon(void);
static void ManageSummonPhase(void);
static void InitInterface(void);
static void DestroyInterface(void);
static void CalcResult(void);
static void InitEndHanchan(void);
static void ManageEndHanchanPhase(void);
static void EndMahjong(void);
static dds3ModelHandle_t *ModelLoad(s32 major, s32 minor);
static void FreeModelEach(dds3ModelHandle_t *modelHandle);
static void PlaySE(s32 no);
static s32 Start(void);
static s32 ShutDown(void);
static mjn_tipsData_t *TipsInit(void);
static dds3ProcessFunc_t TipsProcess(dds3ProcessID_t *PID);
static void StartEtcProcess(dds3ProcessID_t *PID);
static void TipsDestroy(dds3ProcessID_t *PID);
static void CalcSeqHandle(s32 Mode, SeqUnit_t *pSeqUnit, SeqHandle_t *pSeqHandle, dds3ProcessID_t *ID);
static dds3ProcessFunc_t TipsMenuProcess(dds3ProcessID_t *PID);
static void Release(tipsMenuWork_t *wk);
static void TipsMenuShutdown(dds3ProcessID_t *PID);
static dds3ProcessFunc_t TipsDrawProcess(dds3ProcessID_t *PID);
static void CallProcEnd(tipsMenuWork_t *wk);
static u8 CheckProcEnd(tipsMenuWork_t *wk);
static void SetCommand(tipsMenuWork_t *wk);
static s32 CallFunc(void);
static void SetRootMenu(dds3ProcessID_t *PID, s32 MenuID, char *pStr);
static void SetMenu(dds3ProcessID_t *PID, s32 MenuID, s32 ParentMenuID, char *pStr);
static void SetFlagMenu(dds3ProcessID_t *PID, s32 MenuID, u32 Flag, bool Bool);
static s32 RootInit(dds3ProcessID_t *PID);
static s32 RootDestroy(dds3ProcessID_t *PID);
static dds3ProcessFunc_t RootCalcProcess(dds3ProcessID_t *PID);
static dds3ProcessFunc_t RootDrawProcess(dds3ProcessID_t *PID);
static dds3ProcessFunc_t RootUpdateProcess(dds3ProcessID_t *PID);
static s32 HierarchyInit(dds3ProcessID_t *PID);
static s32 HierarchyDestroy(dds3ProcessID_t *PID);
static dds3ProcessFunc_t HierarchyCalcProcess(dds3ProcessID_t *PID);
static dds3ProcessFunc_t HierarchyDrawProcess(dds3ProcessID_t *PID);
static dds3ProcessFunc_t HierarchyUpdateProcess(dds3ProcessID_t *PID);
static s32 PANELInit(dds3ProcessID_t *PID);
static s32 PANELDestroy(dds3ProcessID_t *PID);
static dds3ProcessFunc_t PANELCalcProcess(dds3ProcessID_t *PID);
static dds3ProcessFunc_t PANELDrawProcess(dds3ProcessID_t *PID);
static dds3ProcessFunc_t PANELUpdateProcess(dds3ProcessID_t *PID);
static void MenuInit(void);
static dds3ProcessFunc_t MenuLoop(dds3ProcessID_t *id);
static void MenuDestroy(dds3ProcessID_t *id);
static void MenuStartMahjon(void);
static s32 MenuPadFunc(void);
static void MenuDrawFunc(s32 a_id, s32 a_x, s32 a_y, s32 a_z, u32 a_fontColor, u8 a_alphaRate);
static dds3ProcessFunc_t BridgeLoop(dds3ProcessID_t *id);
static void BridgeDestroy(dds3ProcessID_t *id);
static void MenuDraw(void);
static void SetCommand_New(tipsMenuWork_t *wk);
static void SetRootMenu_New(tipsMenuWork_t *wk, s32 MenuID, s32 ChildNum, char *pStr);
static void SetMenu_New(tipsMenuWork_t *wk, s32 MenuID, s32 ParentMenuID, char *pStr);
static void SetCommondParent(tipsMenuWork_t *wk);
static void MenuMoveStartCtrl(tipsMenuWork_t *wk);
static bool MenuMoveCalc(tipsMenuWork_t *wk);
static void MenuCursorCtrlSub(tipsMenuWork_t *wk);
static void CursorUp(tipsMenuWork_t *wk);
static void CursorDown(tipsMenuWork_t *wk);
static void CursorLeft(tipsMenuWork_t *wk);
static void CursorRight(tipsMenuWork_t *wk);
static void DrawMenuBeforeAfterSave(tipsMenuWork_t *wk);
static void PanelTextCtrlSub(tipsMenuWork_t *wk);
static s32 RightStickCtrl(void);

// 0x1d01fc0
static s32 CheckAgari(s32 playerIndex) {
  if (CheckAgariNormal(playerIndex))
    return 1;
  if (CheckAgariChitoi(playerIndex))
    return 1;
  return CheckAgariKokushi(playerIndex) != 0;
}

// 0x1d025f0
static s32 CheckAgariKokushi(s32 playerIndex) {
  Player_t *v4;
  s64 v5;
  s32 tehaiNum;
  u64 v7;
  s32 v8;
  s64 m_Items;
  s32 v10;

  v4 = Work->players[playerIndex];
  if (!v4->menzen)
    return 0;
  v5 = playerIndex;
  tehaiNum = v4->tehaiNum;
  if (tehaiNum == 14)
    goto LABEL_14;
  if (tehaiNum == 13)
    goto LABEL_14;
  return 0;
LABEL_14:
  v7 = 0;
  v8 = 0;
  m_Items = Work->players[v5]->tehai34;
  do
  {
    v10 = *(u32 *)(m_Items + 4 * v7);
    if (v10 == 1)
    {
      if (v7 > 0x1A)
        goto LABEL_18;
      if ((((u32)v7 - 9 * ((477218589 * (u64)(u8)v7) >> 32)) & 7) != 0)
        return 0;
    }
    else
    {
      if (v10 == 2)
      {
        if (v7 <= 0x1A)
        {
          if (((u8)v7 - 9 * (u8)((477218589 * (u64)(u8)v7) >> 32)) & 7 | v8)
            return 0;
LABEL_30:
          v8 = 1;
          goto LABEL_18;
        }
        if (v8)
          return 0;
        goto LABEL_30;
      }
      if ((u32)(v10 - 3) < 2)
        return 0;
    }
LABEL_18:
    ++v7;
  }
  while (v7 != 34);
  return 1;
}

// 0x1d02850
static s32 CheckYakuhaiSub(s32 playerIndex, s32 hai) {
  Player_t *v7;
  s32 v8;
  bool v9;
  s32 v10;
  s32 v11;

  if (hai < 27)
    return 0;
  if ((u32)hai > 0x1E)
    return 1;
  v7 = Work->players[playerIndex];
  if (Work->kyoku <= 3)
    v8 = 27;
  else
    v8 = 28;
  v9 = v8 == hai;
  v10 = v8 == hai;
  if (v9)
    v11 = 2;
  else
    v11 = 1;
  if (v7->kaze == hai)
    return v11;
  else
    return v10;
}

// 0x1d02960
static void PrintAnalysis(TehaiAnalysis_t *analysis) {
  ;
}

// 0x1d02970
static TehaiAnalysis_t *SetBestAnalysis(s32 playerIndex) {
  s32 v7;

  AnalyzeTehaiNormal(playerIndex);
  AnalyzeTehaiChitoi(playerIndex);
  AnalyzeTehaiKokushi(playerIndex);
  return SetBestAnalysisSub(v7, Work->players[playerIndex]->analysis);
}

// 0x1d02d70
static s32 AIChooseSutehai(s32 playerIndex, TehaiAnalysis_t *analysis) {
  s64 v6;
  Player_t *v7;
  KokushiAnalysis_t *kokushiAnalysis;
  NormalAnalysis_t *normalAnalysis;
  ChitoiAnalysis_t *chitoiAnalysis;
  s32 v11;
  s32 fuyouNum;
  s32 v14;
  Player_t *v15;
  s32 v18;
  s32 v20;
  s64 v21;
  s64 v22;
  s32 v23;
  s32 v24;
  s32 v26;
  s32 v28;
  s64 v29;
  s64 v30;
  s32 v31;
  s32 v32;
  s32 v34;
  s32 v36;
  s64 v37;
  s64 v38;
  s32 v39;
  s32 v40;
  s32 **toitsuHai;
  s64 p_fuyouHai;
  s32 *fuyouHai;
  s32 v46;
  s32 v47;
  s32 v48;

  analysis->fAllowReach = 1;
  v6 = playerIndex;
  v7 = Work->players[playerIndex];
  if (analysis->shanten == -1)
  {
    v7 = Work->players[playerIndex];
    return v7->tehaiNum - 1;
  }
  kokushiAnalysis = analysis->kokushiAnalysis;
  if (analysis->type == 2)
  {
LABEL_9:
    fuyouNum = kokushiAnalysis->fuyouNum;
    analysis->fAllowReach = 0;
    if (fuyouNum)
    {
      v11 = kokushiAnalysis->fuyouHai[0];
      v14 = 0;
      goto LABEL_18;
    }
    v11 = kokushiAnalysis->amariHai[0];
LABEL_16:
    v14 = 0;
    goto LABEL_18;
  }
  normalAnalysis = analysis->normalAnalysis;
  chitoiAnalysis = analysis->chitoiAnalysis;
  v11 = v7->tehai14[0];
  if (v7->aim[6])
    goto LABEL_9;
  if (analysis->type)
  {
    if (chitoiAnalysis->fuyouNum)
    {
      v11 = chitoiAnalysis->fuyouHai[0];
      v18 = CalcHaiValueChitoi(v11, playerIndex);
      if (chitoiAnalysis->fuyouNum < 2)
        goto LABEL_16;
      v20 = v18;
      v21 = 9;
      while (1)
      {
        v23 = *((u32 *)&chitoiAnalysis->fuyouHai->obj.klass + v21);
        v24 = CalcHaiValueChitoi(v23, playerIndex);
        if (v24 < v20)
        {
          v20 = v24;
          v11 = *((u32 *)&chitoiAnalysis->fuyouHai->obj.klass + v21);
        }
        v22 = v21 - 7;
        ++v21;
        if (v22 >= chitoiAnalysis->fuyouNum)
          goto LABEL_16;
      }
    }
    v11 = chitoiAnalysis->toitsu[0];
    v34 = CalcHaiValue(v11, playerIndex);
    if (chitoiAnalysis->toitsuNum < 2)
      goto LABEL_16;
    v36 = v34;
    v37 = 9;
    while (1)
    {
      v39 = *((u32 *)&chitoiAnalysis->toitsu->obj.klass + v37);
      v40 = CalcHaiValueChitoi(v39, playerIndex);
      if (v40 < v36)
      {
        v36 = v40;
        v11 = *((u32 *)&chitoiAnalysis->toitsu->obj.klass + v37);
      }
      v38 = v37 - 7;
      ++v37;
      if (v38 >= chitoiAnalysis->toitsuNum)
        goto LABEL_16;
    }
  }
  if (normalAnalysis->shanten || normalAnalysis->toitsuNum)
  {
    if (normalAnalysis->fuyouNum)
    {
      v11 = normalAnalysis->fuyouHai[0];
      v26 = CalcHaiValue(v11, playerIndex);
      if (normalAnalysis->fuyouNum < 2)
        goto LABEL_16;
      v28 = v26;
      v29 = 9;
      while (1)
      {
        v31 = *((u32 *)&normalAnalysis->fuyouHai->obj.klass + v29);
        v32 = CalcHaiValue(v31, playerIndex);
        if (v32 < v28)
        {
          v28 = v32;
          v11 = *((u32 *)&normalAnalysis->fuyouHai->obj.klass + v29);
        }
        v30 = v29 - 7;
        ++v29;
        if (v30 >= normalAnalysis->fuyouNum)
          goto LABEL_16;
      }
    }
    if (normalAnalysis->toitsuNum >= 2)
    {
      toitsuHai = normalAnalysis->toitsuHai;
    }
    else
    {
      if (!normalAnalysis->tatsuNum)
        goto LABEL_16;
      toitsuHai = normalAnalysis->tatsuHai;
    }
    v11 = toitsuHai[0][0];
    v14 = 0;
    goto LABEL_18;
  }
  v7 = Work->players[playerIndex];
  v7->analysis->fAllowReach = 0;
  if (normalAnalysis->fuyouNum == 2)
  {
    fuyouHai = normalAnalysis->fuyouHai;
    p_fuyouHai = &normalAnalysis->fuyouHai;
    v11 = fuyouHai[0];
    v46 = CalcHaiValueTanki(v11, playerIndex);
  }
  else
  {
    if (normalAnalysis->tatsuNum != 1)
    {
      v48 = 101;
      v46 = 101;
      v47 = 101;
      v11 = 101;
      goto LABEL_80;
    }
    v11 = normalAnalysis->tatsuHai[0][0];
    v46 = CalcHaiValueTanki(v11, playerIndex);
    p_fuyouHai = normalAnalysis->tatsuHai;
  }
  v47 = *(u32 *)(*(u64 *)p_fuyouHai + 36);
  v48 = CalcHaiValueTanki(v47, playerIndex);
LABEL_80:
  if (v46 > v48)
    v11 = v47;
  v14 = 0;
LABEL_18:
  while (1)
  {
    v15 = Work->players[v6];
    if (v14 >= v15->tehaiNum)
      return 0;
    v15 = Work->players[v6];
    if (v15->tehai14[v14] == v11)
      return v14;
    ++v14;
  }
}

// 0x1d03b10
static void ApplyAgari(s32 playerIndex, s32 fromPlayerIndex) {
  s32 v6;
  s64 i;
  s32 v8;
  Work_t *Work_local;
  s32 v11;
  s32 *uraDora;
  s32 **p_uraDora;
  NormalAnalysis_t *v19;
  s64 j;
  u32 v23;
  Work_t *v24;
  Agari_t *v26;
  u32 v28;
  Work_t *v29;
  Player_t *v30;
  s32 *tehai14;
  s64 v32;
  Agari_t *p_pAgari;
  u32 v38;
  Work_t *v39;
  s32 oya;
  Work_t *v41;
  Player_t *v42;
  s32 v43;
  s32 *tehai34;
  s32 *v45;
  s64 v46;
  Work_t *v48;
  s32 v49;
  bool v50;
  s32 v51;
  s32 v52;
  s32 v53;

  if (Work->players[playerIndex]->reachIndex != -1)
  {
    v6 = 9;
    for (i = 8; ; ++i)
    {
      Work_local = Work;
      if (i - 8 >= Work_local->doraNum)
        break;
      Work_local = Work;
      v11 = Work_local->wanpai[v6];
      p_uraDora = &Work_local->uraDora;
      uraDora = Work_local->uraDora;
      *((u32 *)&p_uraDora[1]->obj.klass + i) = v11;
      v8 = 27;
      switch (v11)
      {
        case 8:
        case 17:
        case 26:
          v8 = v11 - 8;
          break;
        case 30:
          break;
        default:
          if (v11 == 33)
            v8 = 31;
          else
            v8 = v11 + 1;
          break;
      }
      *((u32 *)&uraDora->obj.klass + i) = v8;
      v6 -= 2;
    }
    Work_local = Work;
    Work_local->fDrawUraDora = 1;
  }
  Work->fShowTehai[playerIndex] = 1;
  p2sdPlaySE_Vol(4194310, 127);
  if (playerIndex == fromPlayerIndex)
  {
    goto LABEL_25;
  }
  else
  {
    v29 = Work;
    v30 = v29->players[playerIndex];
    tehai14 = v30->tehai14;
    v32 = (s64)v30->tehai34 + 4 * v29->lastSutehai;
    ++*(u32 *)(v32 + 32);
    tehai14[v30->tehaiNum++] = v29->lastSutehai;
LABEL_25:
    goto LABEL_26;
  }
LABEL_26:
  AnalyzeTehaiNormal(playerIndex);
  AnalyzeTehaiChitoi(playerIndex);
  AnalyzeTehaiKokushi(playerIndex);
  for (j = 4; ; ++j)
  {
    v24 = Work;
    if (j - 4 >= v24->analysisIndex)
      break;
    if (v23)
    {
      v19 = *((NormalAnalysis_t *)&v24->analysis->obj.klass + j);
      if (v19->shanten != -1)
        continue;
    }
    else
    {
      v19 = *((NormalAnalysis_t *)&Work->analysis->obj.klass + j);
      if (v19->shanten != -1)
        continue;
    }
    v19 = *((NormalAnalysis_t *)&Work->analysis->obj.klass + j);
    CalcAgari(playerIndex, v19, 0);
  }
  if (!v23)
  {
    if (Work->chitoiAnalysis->shanten == -1)
      goto LABEL_53;
LABEL_41:
    goto LABEL_42;
LABEL_43:
    goto LABEL_44;
LABEL_64:
    if (!v28)
    ApplyChonbo(playerIndex, 3);
    return;
  }
  if (v24->chitoiAnalysis->shanten != -1)
    goto LABEL_41;
LABEL_53:
  CalcAgari(playerIndex, 0, 1);
LABEL_42:
  if (Work->kokushiAnalysis->shanten != -1)
    goto LABEL_43;
  CalcAgari(playerIndex, 0, 2);
LABEL_44:
  v26 = ChooseAgari((s32)mjn);
  if (!v26)
    goto LABEL_64;
  if (v26->yakuNum == v26->yaku[11])
    goto LABEL_64;
  p_pAgari = &Work->pAgari;
  p_pAgari = v26;
  Work->fDrawAgari = 1;
  UpdateTensu(v26);
  v39 = Work;
  oya = v39->oya;
  if (oya != playerIndex)
  {
    if (v38)
    {
      v39->honba = 0;
    }
    else
    {
      Work->honba = 0;
    }
    goto LABEL_75;
  }
  if (v38)
  {
    ++v39->honba;
LABEL_75:
    v41 = Work;
    v41->reachBou = 0;
    if (playerIndex == fromPlayerIndex)
    {
      goto LABEL_77;
LABEL_78:
      if (oya == playerIndex)
        return;
      v48 = Work;
      ++v48->kyoku;
      v49 = v48->oya + 1;
      v51 = -v49;
      v50 = -v49 < 0;
      v52 = v49 & 3;
      v53 = v51 & 3;
      if (!v50)
        v52 = -v53;
      v48->oya = v52;
      return;
    }
  }
  else
  {
    ++Work->honba;
    goto LABEL_75;
  }
  v41 = Work;
  v42 = v41->players[playerIndex];
  v43 = v42->tehaiNum - 1;
  v42->tehaiNum = v43;
  v45 = v42->tehai14;
  tehai34 = v42->tehai34;
  v45[v43] = -1;
  v46 = (s64)tehai34 + 4 * v41->lastSutehai;
  --*(u32 *)(v46 + 32);
LABEL_77:
  goto LABEL_78;
}

// 0x1d04d20
static s32 CheckFuriten(s32 playerIndex) {
  s32 *v4;
  s64 v7;
  s64 v8;
  s32 v9;
  char *v10;
  Player_t *v11;
  s64 v12;
  s32 v13;
  s64 v14;
  s64 i;
  u32 *v16;
  s64 v17;
  s64 v18;
  s32 v19;
  s64 v20;
  s32 *v21;
  s64 v22;
  s64 v23;
  s32 v24;
  char *v25;

  v4 = NewSpecific(s32, 0xCu);
  if (Work->players[playerIndex]->fFuriten == 1)
    return 1;
  v7 = 0;
  while (1)
  {
    v11 = Work->players[playerIndex];
    if (v7 >= v11->sutehaiIndex)
      break;
    v11 = Work->players[playerIndex];
    v8 = v11->sutehai[v7];
    ++v11->tehai34[v8];
    v9 = CheckAgari(playerIndex);
    ++v7;
    v10 = (char *)Work->players[playerIndex]->tehai34
        + v8 * 4;
    --*((u32 *)v10 + 8);
    if (v9)
      return 1;
  }
  v12 = 0;
  v13 = 0;
  v14 = playerIndex;
  do
  {
    if (v12 != v14)
    {
      for (i = 4; ; ++i)
      {
        if (i - 4 >= Work->players[v12]->nakiNum)
        {
          v14 = playerIndex;
          goto LABEL_16;
        }
        v18 = *((u64 *)&Work->players[v12]->naki->obj.klass + i);
        if (*(u32 *)(v18 + 20) == playerIndex)
          break;
LABEL_23:
        ;
      }
      v18 = *((u64 *)&Work->players[v12]->naki->obj.klass + i);
      v19 = *(u32 *)(v18 + 16);
      if (v19 == 268435968)
        goto LABEL_50;
      if (v19 == 268435712)
      {
        v16 = (*(u64 *)(*((u64 *)&Work->players[v12]->naki->obj.klass + i) + 24) + 36);
        goto LABEL_22;
      }
      if (v19 != 268435584)
      {
LABEL_50:
        v16 = (*(u64 *)(*((u64 *)&Work->players[v12]->naki->obj.klass + i) + 24) + 32);
      }
      else
      {
        v16 = (*(u64 *)(*((u64 *)&Work->players[v12]->naki->obj.klass + i) + 24) + 40);
      }
LABEL_22:
      v17 = (s64)(char *)v4 + 4 * v13++;
      *(u32 *)(v17 + 32) = *v16;
      goto LABEL_23;
    }
LABEL_16:
    ++v12;
  }
  while (v12 != 4);
  if (v13 < 1)
    return 0;
  v20 = v13;
  v21 = &v4[0];
  v22 = playerIndex;
  while (1)
  {
    v23 = (s64)Work->players[v22]->tehai34 + 4 * *v21;
    ++*(u32 *)(v23 + 32);
    v24 = CheckAgari(playerIndex);
    v25 = (char *)Work->players[v22]->tehai34 + 4 * *v21;
    --*((u32 *)v25 + 8);
    if (v24)
      break;
    ++v21;
    if (!--v20)
      return 0;
  }
  return 1;
}

// 0x1d045e0
static void ApplyChonbo(s32 playerIndex, s32 type) {
  s32 *v5;
  int32x4_t *v7;
  s32 oya;
  Player_t *players;
  Player_t *v11;
  Player_t *v12;
  Player_t *v13;
  Player_t *v15;
  Work_t *v17;
  Agari_t *v18;
  Work_t *v20;
  s32 *tensu;
  Player_t *v22;
  Work_t *v23;
  Player_t *v24;
  Work_t *v25;
  Player_t *v26;
  Work_t *v27;
  Player_t *v28;
  Work_t *v30;
  s32 v31;
  bool v32;
  s32 v33;
  s32 v34;
  s32 v35;

  v5 = NewSpecific(s32, 4u);
  v7 = &v5[0];
  oya = Work->oya;
  if (oya == playerIndex)
  {
    v5[3] = 4000;
    *(int32x2_t *)&v5[1] = vdup_n_s32(0xFA0u);
    v7->n128_u32[0] = 4000;
    v5[playerIndex] = -12000;
LABEL_7:
    players = Work->players;
    v11 = players[1];
    players[0]->tensu += v5[0];
    v11->tensu += v5[1];
    v13 = players[2];
    v12 = players[3];
    v13->tensu += v5[2];
LABEL_16:
    v12->tensu += v5[3];
    goto LABEL_17;
  }
  else
  {
    *v7 = vdupq_n_s32(0x7D0u);
    *(u32 *)((s64)(char *)v5 + 4 * Work->oya + 32) = 4000;
    v5[playerIndex] = -8000;
    goto LABEL_7;
  }
  v15 = Work->players;
  v15[0]->tensu += v5[0];
  v15[1]->tensu += v5[1];
  v15[2]->tensu += v5[2];
  v12 = v15[3];
  goto LABEL_16;
LABEL_17:
  v17 = Work;
  v18 = v17->agari[0];
  v17->pAgari = v18;
  v20 = Work;
  tensu = v20->pAgari->tensu;
  tensu[0] = v5[0];
  tensu[1] = v5[1];
  tensu[2] = v5[2];
  tensu[3] = v5[3];
  v20->fDrawAgari = type;
  v20 = Work;
  v22 = v20->players[0];
  if (v22->reachIndex != -1)
  {
    v20 = Work;
    v22 = v20->players[0];
    v22->tensu += 1000;
    --v20->reachBou;
  }
  v23 = Work;
  v24 = v23->players[1];
  if (v24->reachIndex != -1)
  {
    v23 = Work;
    v24 = v23->players[1];
    v24->tensu += 1000;
    --v23->reachBou;
  }
  v25 = Work;
  v26 = v25->players[2];
  if (v26->reachIndex != -1)
  {
    v25 = Work;
    v26 = v25->players[2];
    v26->tensu += 1000;
    --v25->reachBou;
  }
  v27 = Work;
  v28 = v27->players[3];
  if (v28->reachIndex != -1)
  {
    v27 = Work;
    v28 = v27->players[3];
    v28->tensu += 1000;
    --v27->reachBou;
  }
  if (oya != playerIndex)
    return;
  v30 = Work;
  ++v30->kyoku;
  v31 = v30->oya + 1;
  v33 = -v31;
  v32 = -v31 < 0;
  v34 = v31 & 3;
  v35 = v33 & 3;
  if (!v32)
    v34 = -v35;
  v30->oya = v34;
}

// 0x1d04af0
static void UpdateTensu(Agari_t *agari) {
  s32 *tensu;
  Player_t *players;
  Player_t *v5;

  tensu = agari->tensu;
  players = Work->players;
  v5 = players[1];
  players[0]->tensu += tensu[0];
  v5->tensu += tensu[1];
  players[2]->tensu += tensu[2];
  players[3]->tensu += tensu[3];
}

// 0x1d02ad0
static TehaiAnalysis_t *SetBestAnalysisSub(s32 playerIndex, TehaiAnalysis_t *bestAnalysis) {
  s64 v5;
  NormalAnalysis_t *v6;
  Work_t *Work_local;
  s32 v9;
  ChitoiAnalysis_t *chitoiAnalysis;
  KokushiAnalysis_t *kokushiAnalysis;
  s32 *p_shanten;
  s32 v15;
  s32 shanten;
  Work_t *v17;
  Work_t *v18;
  s32 v19;
  ChitoiAnalysis_t *v21;

  v5 = 4;
  v6 = Work->analysis[0];
  while (1)
  {
    Work_local = Work;
    if (v5 - 4 >= Work_local->analysisIndex)
      break;
    Work_local = Work;
    v9 = *(u32 *)(*((u64 *)&Work_local->analysis->obj.klass + v5) + 80);
    if (v9 < v6->shanten)
    {
      v6 = *((NormalAnalysis_t *)&Work->analysis->obj.klass + v5);
    }
    ++v5;
  }
  bestAnalysis->normalAnalysis = v6;
  chitoiAnalysis = Work->chitoiAnalysis;
  bestAnalysis->chitoiAnalysis = chitoiAnalysis;
  kokushiAnalysis = Work->kokushiAnalysis;
  bestAnalysis->kokushiAnalysis = kokushiAnalysis;
  shanten = v6->shanten;
  p_shanten = &v6->shanten;
  v15 = shanten;
  v17 = Work;
  if (shanten <= v17->chitoiAnalysis->shanten)
  {
    if (v15 <= Work->kokushiAnalysis->shanten)
      goto LABEL_31;
  }
  v18 = Work;
  v19 = v18->chitoiAnalysis->shanten;
  if (v19 <= v18->kokushiAnalysis->shanten)
  {
    if (v19 < *p_shanten)
    {
      bestAnalysis->type = 1;
      bestAnalysis->shanten = v19;
      return bestAnalysis;
    }
  }
  bestAnalysis->type = 2;
  v21 = Work->kokushiAnalysis;
  p_shanten = &v21->shanten;
  goto LABEL_37;
LABEL_31:
  bestAnalysis->type = 0;
LABEL_37:
  bestAnalysis->shanten = *p_shanten;
  return bestAnalysis;
}

// 0x1d02a60
static void AnalyzeTehai(s32 playerIndex) {
  AnalyzeTehaiNormal(playerIndex);
  AnalyzeTehaiChitoi(playerIndex);
  AnalyzeTehaiKokushi(playerIndex);
}

// 0x1d05640
static s32 CheckYakuAri(s32 playerIndex, s32 tsumo, s32 agariHai) {
  TehaiAnalysis_t *analysis;
  MethodInfo *v8;
  s32 **v9;
  s32 *v11;
  Player_t *v13;
  s32 v14;
  s32 v16;
  s64 v18;
  NormalAnalysis_t *normalAnalysis;
  s64 i;
  s64 v22;
  Player_t *v23;
  s64 v24;
  s64 v25;
  s32 j;
  s64 v27;
  u32 *v28;
  Player_t *v30;
  s32 **v33;
  s32 **v35;
  s32 **v43;
  s32 **v45;
  s32 **v47;
  s32 **v49;
  s32 **v51;
  s32 **v53;
  s32 **v55;

  analysis = Allocate(TehaiAnalysis_t);
  _ctor(analysis, 0);
  v11 = NewSpecific(s32, 0xEu);
  v13 = Work->players[playerIndex];
  if (v13->reachIndex != -1)
    return 1;
  if (v13->menzen)
  {
    if (tsumo)
      return 1;
LABEL_18:
    v13 = Work->players[playerIndex];
    v18 = (s64)v13->tehai34 + 4 * agariHai;
    ++*(u32 *)(v18 + 32);
    SetTehai14(playerIndex);
    SetBestAnalysisEx(playerIndex, analysis);
    v16 = 1;
    if (analysis->kokushiAnalysis->shanten != -1)
      goto LABEL_21;
LABEL_17:
    goto LABEL_29;
  }
  if (!tsumo)
    goto LABEL_18;
  v13 = Work->players[playerIndex];
  analysis = v13->analysis;
  v16 = 0;
  if (analysis->kokushiAnalysis->shanten == -1)
    goto LABEL_17;
LABEL_21:
  if (analysis->chitoiAnalysis->shanten == -1)
  {
LABEL_29:
    v14 = 1;
LABEL_31:
    v24 = (s64)Work->players[playerIndex]->tehai34 + 4 * agariHai;
    --*(u32 *)(v24 + 32);
    SetTehai14(playerIndex);
    return v14;
  }
  normalAnalysis = analysis->normalAnalysis;
  for (i = 8; ; ++i)
  {
    v23 = Work->players[playerIndex];
    if (i - 8 >= v23->tehaiNum)
      break;
    v23 = Work->players[playerIndex];
    v22 = 4 * i;
    *(u32 *)((char *)&v11->obj.klass + v22) = *(u32 *)((char *)&v23->tehai14->obj.klass + v22);
  }
  v25 = 0;
  for (j = i - 6; ; j += 3)
  {
    v30 = Work->players[playerIndex];
    if (v25 >= v30->nakiNum)
      break;
    v30 = Work->players[playerIndex];
    v27 = (s64)v30->naki + 8 * v25++;
    v28 = *(u32 **)(*(u64 *)(v27 + 32) + 24);
    v11[j - 2] = v28[8];
    v11[j - 1] = v28[9];
    v11[j] = v28[10];
  }
  if (CheckPinfu(playerIndex, normalAnalysis, v9, agariHai))
    goto LABEL_93;
  if (CheckTanyao((s32)mjn, v11))
    goto LABEL_93;
  if (CheckIpeiko(playerIndex, normalAnalysis, v33))
    goto LABEL_93;
  if (CheckYakuhai(playerIndex, normalAnalysis, v35))
    goto LABEL_93;
  if (CheckHaitei((s32)mjn, tsumo))
    goto LABEL_93;
  if (CheckHoutei((s32)mjn, tsumo))
    goto LABEL_93;
  if (CheckRinshan(playerIndex, v8))
    goto LABEL_93;
  if (CheckChankan())
    goto LABEL_93;
  if (CheckChanta(playerIndex, normalAnalysis, v43))
    goto LABEL_93;
  if (CheckIttsu(playerIndex, normalAnalysis, v45))
    goto LABEL_93;
  if (CheckSanshokujun(playerIndex, normalAnalysis, v47))
    goto LABEL_93;
  if (CheckSanshokupon(playerIndex, normalAnalysis, v49))
    goto LABEL_93;
  if (CheckToitoi(playerIndex, normalAnalysis, v51))
    goto LABEL_93;
  if (CheckSananko(playerIndex, normalAnalysis, v53, tsumo, agariHai))
    goto LABEL_93;
  if (CheckSankantsu(playerIndex, v8, v55))
    goto LABEL_93;
  if (CheckHonitsu(playerIndex, v11))
    goto LABEL_93;
  if (CheckRenho(playerIndex, tsumo))
    goto LABEL_93;
  if (CheckTenho(playerIndex, tsumo))
  {
LABEL_93:
    v14 = 1;
    if (!v16)
      return v14;
LABEL_94:
    goto LABEL_31;
  }
  v14 = CheckChiho(playerIndex, tsumo) != 0;
  if (v16)
    goto LABEL_94;
  return v14;
}

// 0x1d09a80
static s32 CheckAgariSub(s32 *tehai34, s32 type) {
  s32 v5;
  s64 v6;
  s32 v7;
  s64 v8;
  s32 v9;
  s32 result;
  s32 v11;
  u32 v12;
  s32 *v13;
  s32 v14;
  s32 v15;
  s32 v16;
  s32 v17;
  s32 v18;
  s64 v20;
  s32 v21;
  u32 v22;
  s32 v23;
  s32 v24;
  s32 v25;
  bool v26;
  s32 *m_Items;
  s32 v29;
  s32 v30;
  s32 v31;
  s32 v32;
  s32 v33;
  s64 v35;
  s32 v37;
  s32 v38;
  s32 v39;
  s32 v40;
  s32 v41;

  if ((u32)type < 3)
  {
    v5 = 9 * type;
    v6 = 4 * (9 * type + 1) + 32;
    v7 = 9 * type;
    while (1)
    {
      v8 = v7;
      v9 = tehai34[v7];
      if (v9)
        break;
      v7 = v8 + 1;
      v6 += 4;
      if ((s32)v8 + 1 >= 9 * type + 9)
        return 1;
    }
    if (v9 >= 3)
    {
      m_Items = tehai34;
      tehai34[v8] = v9 - 3;
      result = CheckAgariSub(tehai34, type);
      v29 = m_Items[v8];
      v30 = v29 + 3;
      m_Items[v8] = v29 + 3;
      if (!result)
      {
        if ((s32)v8 >= v5 + 7)
          goto LABEL_52;
        v31 = *(u32 *)((char *)&tehai34->obj.klass + v6);
        if (!v31)
          goto LABEL_52;
        v32 = v8 + 2;
        v33 = tehai34[(s32)v8 + 2];
        if (!v33)
          goto LABEL_52;
        v35 = v32;
        m_Items[v8] = v29 + 2;
        *(u32 *)((char *)&tehai34->obj.klass + v6) = v31 - 1;
        m_Items[v32] = v33 - 1;
        result = CheckAgariSub(tehai34, type);
        v30 = m_Items[v8] + 1;
        m_Items[v8] = v30;
        ++*(u32 *)((char *)&tehai34->obj.klass + v6);
        ++m_Items[v35];
        if (!result)
        {
LABEL_52:
          m_Items[v8] = v30 - 2;
          result = 2 * (CheckAgariSub(tehai34, type) == 1);
          m_Items[v8] += 2;
        }
      }
    }
    else
    {
      if (v9 == 2)
      {
        v13 = tehai34;
        tehai34[v8] = 0;
        v14 = CheckAgariSub(tehai34, type);
        v15 = v13[v8];
        v13[v8] = v15 + 2;
        if (v14 == 1)
          return 2;
        if (v14 == 2)
          return 0;
        if ((s32)v8 >= v5 + 7)
          return 0;
        v16 = *(u32 *)((char *)&tehai34->obj.klass + v6);
        if (!v16)
          return 0;
        v17 = v8 + 2;
        v18 = tehai34[(s32)v8 + 2];
        if (!v18)
          return 0;
        v20 = v17;
        v13[v8] = v15 + 1;
        *(u32 *)((char *)&tehai34->obj.klass + v6) = v16 - 1;
        v13[v17] = v18 - 1;
      }
      else
      {
        if ((s32)v8 >= v5 + 7)
          return 0;
        v37 = *(u32 *)((char *)&tehai34->obj.klass + v6);
        if (!v37)
          return 0;
        v38 = v8 + 2;
        v39 = tehai34[(s32)v8 + 2];
        if (!v39)
          return 0;
        v13 = tehai34;
        v20 = v38;
        tehai34[v8] = v9 - 1;
        *(u32 *)((char *)&tehai34->obj.klass + v6) = v37 - 1;
        tehai34[v38] = v39 - 1;
      }
      result = CheckAgariSub(tehai34, type);
      ++v13[v8];
      ++*(u32 *)((char *)&tehai34->obj.klass + v6);
      ++v13[v20];
      if (!result)
        return 0;
    }
    return result;
  }
  if (type == 3)
  {
    v21 = tehai34[27];
    if (v21 != 1 && v21 != 4)
    {
      v22 = v21 == 2;
      v23 = tehai34[28];
      result = 0;
      if (v23 == 1 || v23 == 4)
        return result;
      if (v23 == 2)
        ++v22;
      v24 = tehai34[29];
      result = 0;
      if (v24 == 1 || v24 == 4)
        return result;
      if (v24 == 2)
        ++v22;
      v25 = tehai34[30];
      result = 0;
      if (v25 == 1 || v25 == 4)
        return result;
      if (v25 == 2)
        ++v22;
      v26 = v22 == 1;
      if (v22 > 1)
        return 0;
LABEL_73:
      if (v26)
        return 2;
      else
        return 1;
    }
    return 0;
  }
  if (type != 4)
    return 1;
  v11 = tehai34[31];
  v12 = 0;
  if (v11 == 1)
    return 0;
  if (v11 == 2)
  {
    v12 = 1;
  }
  else
  {
    result = 0;
    if (v11 == 4)
      return result;
  }
  v40 = tehai34[32];
  result = 0;
  if (v40 != 1 && v40 != 4)
  {
    if (v40 == 2)
      ++v12;
    v41 = tehai34[33];
    result = 0;
    if (v41 != 1 && v41 != 4)
    {
      if (v41 == 2)
        ++v12;
      v26 = v12 == 1;
      if (v12 > 1)
        return 0;
      goto LABEL_73;
    }
  }
  return result;
}

// 0x1d09f70
static void CalcYaku(s32 playerIndex, NormalAnalysis_t *analysis, Agari_t *agari, s32 tsumo, s32 agariHai) {
  s32 **v10;
  s32 *v12;
  s32 *yaku;
  Player_t *v15;
  s32 *m_Items;
  s64 v17;
  s64 v18;
  s64 v19;
  s64 v20;
  s64 v21;
  s64 v22;
  u32 *v23;
  s32 v24;
  s32 v25;
  s32 *v28;
  _BOOL4 v29;
  s32 *v31;
  s32 *v32;
  s32 **v33;
  s32 **v35;
  s32 *v37;
  s32 *v39;
  s32 *v40;
  bool v41;
  s32 v42;
  s32 *v43;
  s32 *v45;
  bool v47;
  s32 v48;
  s32 *v49;
  s32 *v50;
  s32 *v51;
  s32 *v52;
  s32 *v53;
  s32 **v54;
  s32 *v56;
  s32 **v57;
  s32 *v59;
  s32 **v60;
  s32 *v62;
  s32 **v63;
  s32 **v65;
  s32 *v67;
  s64 v69;
  s32 v70;
  s64 v71;
  Player_t *v72;
  s32 v73;
  s32 *v74;
  Naki_t *v75;
  s32 *v76;
  Player_t *v78;
  s64 nakiNum;
  Naki_t *naki;
  s64 v81;
  s32 v82;
  s32 *v83;
  s32 v84;
  s32 v85;
  s32 v86;
  s32 v87;
  Naki_t *v88;
  s64 v89;
  s64 v90;
  char type;
  s64 v92;
  s64 v93;
  Naki_t *v94;
  s64 v95;
  s32 menzen;
  s32 **shuntsuHai;
  s32 v98;
  s32 v99;
  s32 v100;
  s32 v101;
  s32 *v102;
  s32 *v103;
  s32 **v104;
  s32 **v106;
  s32 *v108;
  s32 v109;
  s32 *v110;
  s32 *v113;
  s32 **v114;
  s32 *v116;
  s32 *v118;
  s32 *v121;
  Work_t *v124;
  s32 *v125;
  Player_t *v127;
  s32 kotsuNum;
  s64 v129;
  Naki_t *v130;
  s64 v131;
  s32 v132;
  s32 v133;
  s32 v134;
  Naki_t *v135;
  s64 v136;
  s32 v137;
  Naki_t *v138;
  s32 v139;
  s32 v140;
  s64 v141;
  s64 v142;
  s64 v143;
  Naki_t *v144;
  Naki_t *v145;
  Naki_t *v146;
  s32 *v147;
  s32 v148;
  Player_t *v149;
  s64 v150;
  Naki_t *v151;
  s64 v152;
  s32 v153;
  s32 v154;
  s32 v155;
  s32 v156;
  s32 v157;
  s32 v158;
  Naki_t *v159;
  s64 v160;
  s64 v161;
  char v162;
  s64 v163;
  Naki_t *v164;
  s64 v165;
  Naki_t *v166;
  s64 v167;
  s32 *v168;
  s32 *v169;
  s32 **v170;
  s32 v172;
  s32 *v173;
  s32 v175;
  s32 *v176;
  NormalAnalysis_t *v178;
  s32 **v179;
  s32 *v181;
  s32 v182;
  u32 v183;
  u32 v184;
  u32 v185;
  u32 v186;
  u32 v187;
  u32 v188;
  u32 v189;
  u32 v190;
  u32 v191;
  u32 v192;
  u32 v193;
  u32 v194;
  u32 v195;
  u32 v196;
  int8x16_t v197;
  s32 *v198;
  s32 *v200;
  s32 v201;
  s32 v202;
  s32 v203;
  s32 v204;
  s32 v205;
  s32 v206;
  s32 v207;
  s32 v208;
  s32 v209;
  s32 v210;
  s32 v211;
  s32 v212;
  s32 v213;
  s32 v214;
  s32 v215;
  s32 v216;
  s32 v217;
  s32 v218;
  s32 v219;
  s32 v220;
  s32 v221;
  s32 v222;
  s32 v223;
  s32 v224;
  s32 v225;
  s32 v226;
  s32 v227;
  s32 v228;
  s32 v229;
  s32 v230;
  s32 v231;
  s32 v232;
  s32 v233;
  s32 v234;
  s32 v235;
  s32 v236;
  s32 v237;
  s32 v238;
  s32 v239;
  s32 v240;
  s32 v241;
  int32x4_t v242;
  s32 tsumoa;
  _BOOL4 v244;

  v12 = NewSpecific(s32, 0xEu);
  yaku = agari->yaku;
  v15 = Work->players[playerIndex];
  *(_OWORD *)yaku = 0u;
  m_Items = yaku;
  *(_OWORD *)(m_Items + 35) = 0u;
  *((_OWORD *)m_Items + 1) = 0u;
  *((_OWORD *)m_Items + 2) = 0u;
  *((_OWORD *)m_Items + 3) = 0u;
  *((_OWORD *)m_Items + 4) = 0u;
  *((_OWORD *)m_Items + 5) = 0u;
  *((_OWORD *)m_Items + 6) = 0u;
  *((_OWORD *)m_Items + 7) = 0u;
  *((_OWORD *)m_Items + 8) = 0u;
  if (v15->tehaiNum < 1)
  {
    LODWORD(v17) = 0;
    if (v15->nakiNum < 1)
      goto LABEL_13;
    goto LABEL_11;
  }
  v17 = 0;
  v18 = v15->tehai14;
  do
  {
    v19 = v17++;
    v12[v19] = *(u32 *)(v18 + v19 * 4);
  }
  while (v17 < v15->tehaiNum);
  if (v15->nakiNum >= 1)
  {
LABEL_11:
    v20 = 0;
    v21 = v15->naki;
    do
    {
      v22 = *(u64 *)(v21 + 8 * v20++);
      v23 = *(u32 **)(v22 + 24);
      v12[(s32)v17] = v23[8];
      v12[(s32)v17 + 1] = v23[9];
      v24 = v17 + 2;
      LODWORD(v17) = v17 + 3;
      v12[v24] = v23[10];
    }
    while (v20 < v15->nakiNum);
  }
LABEL_13:
  v25 = CheckPinfu(playerIndex, analysis, v10, agariHai);
  v28 = agari->yaku;
  *m_Items = v25;
  if (v28[0])
  {
    if (tsumo)
    {
      v29 = 0;
      agari->fu = 20;
      goto LABEL_25;
    }
LABEL_23:
    agari->fu = 30;
LABEL_24:
    v29 = 1;
    goto LABEL_25;
  }
  v29 = tsumo == 0;
  if (!tsumo && agari->fu == 20)
  {
    if (CheckKuiPinfuGata(playerIndex, analysis, agariHai) != 1)
      goto LABEL_24;
    goto LABEL_23;
  }
LABEL_25:
  v31 = agari->yaku;
  v31[1] = CheckTanyao((s32)mjn, v12);
  v32 = agari->yaku;
  v32[2] = CheckIpeiko(playerIndex, analysis, v33);
  v37 = agari->yaku;
  v37[3] = Work->players[playerIndex]->reachIndex != -1;
  v39 = agari->yaku;
  v39[4] = Work->players[playerIndex]->ippatsu != 0;
  v40 = agari->yaku;
  if (tsumo)
    v41 = Work->players[playerIndex]->menzen == 0;
  else
    v41 = 1;
  v42 = !v41;
  v40[5] = v42;
  v43 = agari->yaku;
  v43[6] = CheckYakuhai(playerIndex, analysis, v35);
  v45 = agari->yaku;
  if (tsumo)
    v47 = Work->yamaNum == 0;
  else
    v47 = 0;
  v48 = v47;
  v45[7] = v48;
  v49 = agari->yaku;
  v49[8] = (Work->yamaNum | tsumo) == 0;
  v50 = agari->yaku;
  v50[9] = Work->players[playerIndex]->rinshan != 0;
  v51 = agari->yaku;
  tsumoa = tsumo;
  v244 = v29;
  v51[10] = Work->chankan != 0;
  v52 = agari->yaku;
  v52[11] = CheckDora(playerIndex, v12);
  v53 = agari->yaku;
  v53[12] = 0;
  v53[13] = CheckChanta(playerIndex, analysis, v54);
  v56 = agari->yaku;
  v56[14] = CheckIttsu(playerIndex, analysis, v57);
  v59 = agari->yaku;
  v59[15] = CheckSanshokujun(playerIndex, analysis, v60);
  v62 = agari->yaku;
  v62[16] = CheckSanshokupon(playerIndex, analysis, v63);
  v67 = agari->yaku;
  v69 = 0;
  v70 = 0;
  while (1)
  {
    v72 = Work->players[playerIndex];
    if (v69 >= v72->nakiNum)
      break;
    v72 = Work->players[playerIndex];
    v71 = (s64)v72->naki + 8 * v69++;
    if ((*(u8 *)(*(u64 *)(v71 + 32) + 16) & 0x6C) != 0)
      ++v70;
  }
  v73 = analysis->kotsuNum + v70;
  v74 = agari->yaku;
  v67[17] = 2 * (v73 == 4);
  v74[18] = CheckSananko(playerIndex, analysis, v65, tsumoa, agariHai);
  v76 = agari->yaku;
  v78 = Work->players[playerIndex];
  nakiNum = (u32)v78->nakiNum;
  if ((s32)nakiNum >= 1)
  {
    naki = v78->naki;
    if ((u32)nakiNum >= 4)
    {
      v81 = nakiNum & 0x7FFFFFFC;
      v84 = 0;
      v85 = 0;
      v86 = 0;
      v87 = 0;
      v88 = &naki[3];
      v89 = (u32)nakiNum & 0xFFFFFFFC;
      do
      {
        v90 = *(v88 - 2);
        type = (*(v88 - 3))->type;
        v92 = *(v88 - 1);
        v75 = v88;
        v88 += 4;
        if ((type & 0x4C) != 0)
          ++v84;
        if ((*(u8 *)(v90 + 16) & 0x4C) != 0)
          ++v85;
        if ((*(u8 *)(v92 + 16) & 0x4C) != 0)
          ++v86;
        if ((v75->type & 0x4C) != 0)
          ++v87;
        v89 -= 4;
      }
      while (v89);
      v82 = v87 + v86 + v85 + v84;
      if (v81 == nakiNum)
      {
LABEL_101:
        v76[19] = 2 * (v82 > 2);
        v83 = agari->yaku;
        goto LABEL_103;
      }
    }
    else
    {
      v81 = 0;
      v82 = 0;
    }
    v93 = nakiNum - v81;
    v94 = &naki[v81];
    do
    {
      v95 = (s64)*v94++;
      if ((*(u8 *)(v95 + 16) & 0x4C) != 0)
        ++v82;
      --v93;
    }
    while (v93);
    goto LABEL_101;
  }
  v76[19] = 0;
  v83 = agari->yaku;
LABEL_103:
  menzen = Work->players[playerIndex]->menzen;
  if (menzen)
  {
    if (analysis->shuntsuNum == 4)
    {
      shuntsuHai = analysis->shuntsuHai;
      v98 = shuntsuHai[0][0];
      v99 = shuntsuHai[1][0];
      v100 = shuntsuHai[2][0];
      v101 = shuntsuHai[3][0];
      if (v98 == v99 && v100 == v101)
      {
        menzen = 3;
      }
      else
      {
        menzen = 3;
        if (v98 != v100 || v99 != v101)
        {
          if (v98 == v101 && v99 == v100)
            menzen = 3;
          else
            menzen = 0;
        }
      }
    }
    else
    {
      menzen = 0;
    }
  }
  v102 = agari->yaku;
  v83[20] = menzen;
  if (v102[20])
    v102[2] = 0;
  v102[21] = CheckHonitsu(playerIndex, v12);
  v103 = agari->yaku;
  v103[22] = CheckJunchan(playerIndex, analysis, v104);
  v108 = agari->yaku;
  if (v108[22])
    v108[13] = 0;
  v109 = CheckShousangen(playerIndex, analysis, v106);
  v108[23] = v109;
  v110 = agari->yaku;
  v110[24] = CheckHonroto(v109, v12);
  v113 = agari->yaku;
  if (v113[24])
    v113[13] = 0;
  v113[26] = CheckChinitsu(playerIndex, v12);
  v116 = agari->yaku;
  if (v116[26])
    v116[21] = 0;
  if (!v244)
  {
LABEL_136:
    v116[25] = 0;
    v118 = agari->yaku;
    goto LABEL_138;
  }
  if (!Work->players[playerIndex]->ichijunme)
    goto LABEL_136;
  v116[25] = 8;
  v118 = agari->yaku;
LABEL_138:
  if (v244)
    goto LABEL_156;
  if (Work->oya != playerIndex)
  {
LABEL_156:
    v118[32] = 0;
    v121 = agari->yaku;
    goto LABEL_158;
  }
  if (!Work->players[playerIndex]->ichijunme)
    goto LABEL_156;
  v118[32] = 13;
  v121 = agari->yaku;
LABEL_158:
  if (v244)
    goto LABEL_168;
  v124 = Work;
  if (v124->oya == playerIndex)
  {
LABEL_168:
    v121[33] = 0;
    v125 = agari->yaku;
    goto LABEL_170;
  }
  if (!v124->players[playerIndex]->ichijunme)
    goto LABEL_168;
  v121[33] = 13;
  v125 = agari->yaku;
LABEL_170:
  v127 = Work->players[playerIndex];
  kotsuNum = analysis->kotsuNum;
  v129 = (u32)v127->nakiNum;
  if ((s32)v129 >= 1)
  {
    v130 = v127->naki;
    if ((u32)v129 < 4)
    {
      v131 = 0;
LABEL_186:
      v141 = ~v131;
      if ((v129 & 1) != 0)
      {
        v142 = (s64)v130 + 8 * v131;
        v131 |= 1u;
        if (*(u32 *)(*(u64 *)(v142 + 32) + 16) == 4)
          ++kotsuNum;
      }
      if (v141 + v129)
      {
        v143 = v129 - v131;
        v144 = &v130[v131 + 1];
        do
        {
          v41 = (*(v144 - 1))->type == 4;
          v146 = v144;
          v144 += 2;
          v145 = v146;
          if (v41)
            ++kotsuNum;
          if (v145->type == 4)
            ++kotsuNum;
          v143 -= 2;
        }
        while (v143);
      }
      goto LABEL_196;
    }
    v131 = v129 & 0x7FFFFFFC;
    v132 = 0;
    v133 = 0;
    v134 = 0;
    v135 = &v130[3];
    v136 = (u32)v129 & 0xFFFFFFFC;
    do
    {
      v137 = (*(v135 - 3))->type;
      v138 = v135;
      v139 = (*(v135 - 2))->type;
      v140 = (*(v135 - 1))->type;
      v135 += 4;
      v114 = (u32)v138->type;
      if (v137 == 4)
        ++kotsuNum;
      if (v139 == 4)
        ++v132;
      if (v140 == 4)
        ++v133;
      if ((u32)v114 == 4)
        ++v134;
      v136 -= 4;
    }
    while (v136);
    kotsuNum += v134 + v133 + v132;
    if (v131 != v129)
      goto LABEL_186;
  }
LABEL_196:
  if (v244)
  {
    if (kotsuNum == 4 && analysis->toitsuHai[0][0] == agariHai)
    {
      v125[28] = 26;
      v147 = agari->yaku;
      goto LABEL_209;
    }
LABEL_207:
    v125[28] = 0;
    v147 = agari->yaku;
    goto LABEL_209;
  }
  if (kotsuNum != 4)
    goto LABEL_207;
  if (analysis->toitsuHai[0][0] == agariHai)
    v148 = 26;
  else
    v148 = 13;
  v125[28] = v148;
  v147 = agari->yaku;
LABEL_209:
  v149 = Work->players[playerIndex];
  v150 = (u32)v149->nakiNum;
  if ((s32)v150 < 1)
  {
    v154 = 0;
    goto LABEL_233;
  }
  v151 = v149->naki;
  if ((u32)v150 >= 4)
  {
    v152 = v150 & 0x7FFFFFFC;
    v155 = 0;
    v156 = 0;
    v157 = 0;
    v158 = 0;
    v159 = &v151[3];
    v160 = (u32)v150 & 0xFFFFFFFC;
    do
    {
      v161 = *(v159 - 2);
      v162 = (*(v159 - 3))->type;
      v163 = *(v159 - 1);
      v164 = v159;
      v159 += 4;
      if ((v162 & 0x4C) != 0)
        ++v155;
      if ((*(u8 *)(v161 + 16) & 0x4C) != 0)
        ++v156;
      if ((*(u8 *)(v163 + 16) & 0x4C) != 0)
        ++v157;
      if ((v164->type & 0x4C) != 0)
        ++v158;
      v160 -= 4;
    }
    while (v160);
    v153 = v158 + v157 + v156 + v155;
    if (v152 == v150)
      goto LABEL_230;
  }
  else
  {
    v152 = 0;
    v153 = 0;
  }
  v165 = v150 - v152;
  v166 = &v151[v152];
  do
  {
    v167 = (s64)*v166++;
    if ((*(u8 *)(v167 + 16) & 0x4C) != 0)
      ++v153;
    --v165;
  }
  while (v165);
LABEL_230:
  if (v153 == 4)
    v154 = 13;
  else
    v154 = 0;
LABEL_233:
  v168 = agari->yaku;
  v147[29] = v154;
  v168[30] = CheckDaisangen(playerIndex, analysis, v114);
  v169 = agari->yaku;
  v169[31] = 0;
  v172 = CheckSushiho(playerIndex, analysis, v170);
  v169[34] = v172;
  v173 = agari->yaku;
  v175 = CheckTsuiso(v172, v12);
  v173[35] = v175;
  v176 = agari->yaku;
  v176[36] = CheckChinroto(v175, v12);
  v181 = agari->yaku;
  v182 = 0;
  v183 = v12[0];
  if (v183 <= 0x20 && ((1 << v183) & 0x102B80000LL) != 0)
  {
    v184 = v12[1];
    v182 = 0;
    if (v184 <= 0x20 && ((1 << v184) & 0x102B80000LL) != 0)
    {
      v185 = v12[2];
      v182 = 0;
      if (v185 <= 0x20 && ((1 << v185) & 0x102B80000LL) != 0)
      {
        v186 = v12[3];
        v182 = 0;
        if (v186 <= 0x20 && ((1 << v186) & 0x102B80000LL) != 0)
        {
          v187 = v12[4];
          v182 = 0;
          if (v187 <= 0x20 && ((1 << v187) & 0x102B80000LL) != 0)
          {
            v188 = v12[5];
            v182 = 0;
            if (v188 <= 0x20 && ((1 << v188) & 0x102B80000LL) != 0)
            {
              v189 = v12[6];
              v182 = 0;
              if (v189 <= 0x20 && ((1 << v189) & 0x102B80000LL) != 0)
              {
                v190 = v12[7];
                v182 = 0;
                if (v190 <= 0x20 && ((1 << v190) & 0x102B80000LL) != 0)
                {
                  v191 = v12[8];
                  v182 = 0;
                  if (v191 <= 0x20 && ((1 << v191) & 0x102B80000LL) != 0)
                  {
                    v192 = v12[9];
                    v182 = 0;
                    if (v192 <= 0x20 && ((1 << v192) & 0x102B80000LL) != 0)
                    {
                      v193 = v12[10];
                      v182 = 0;
                      if (v193 <= 0x20 && ((1 << v193) & 0x102B80000LL) != 0)
                      {
                        v194 = v12[11];
                        v182 = 0;
                        if (v194 <= 0x20 && ((1 << v194) & 0x102B80000LL) != 0)
                        {
                          v195 = v12[12];
                          v182 = 0;
                          if (v195 <= 0x20 && ((1 << v195) & 0x102B80000LL) != 0)
                          {
                            v196 = v12[13] - 19;
                            if (v196 > 0xD)
                              v182 = 0;
                            else
                              v182 = dword_3E62EDC[v196];
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
      }
    }
  }
  v181[37] = v182;
  v181[38] = CheckChuren(playerIndex, v178, v179, agariHai);
  v198 = agari->yaku;
  v198[27] = 2 * (Work->players[playerIndex]->doubleReach != 0);
  v200 = agari->yaku;
  v201 = v200[27];
  if (v201)
    v200[3] = 0;
  if (v200[28] || v200[29] || v200[30] || v200[31] || v200[32] || v200[33] || v200[34] || v200[35] || v200[36] || v200[37] || v200[38])
  {
    *(_OWORD *)&v200[4] = 0u;
    *(_OWORD *)&v200[8] = 0u;
    v202 = v200[9];
    *(_OWORD *)&v200[12] = 0u;
    *(_OWORD *)&v200[16] = 0u;
    *(_OWORD *)v200 = 0u;
    *(_OWORD *)&v200[20] = 0u;
    *(_OWORD *)&v200[24] = 0u;
  }
  else
  {
    v241 = v200[25];
    if (v241)
    {
      v242.n128_u32[0] = v200[24];
      v197.n128_u64[0] = *(u64 *)&v200[33];
      v242.n128_u32[1] = v200[26];
      v242.n128_u64[1] = *(u64 *)&v200[29];
      if (vaddvq_s32(vaddq_s32(vaddq_s32(vaddq_s32(vaddq_s32(*(int32x4_t *)v200, *(int32x4_t *)&v200[16]), vaddq_s32(vaddq_s32(*(int32x4_t *)&v200[4], *(int32x4_t *)&v200[20]), vaddq_s32(*(int32x4_t *)&v200[12], vextq_s8(*(int8x16_t *)&v200[29], v197, 8u)))), *(int32x4_t *)&v200[35]), vaddq_s32(*(int32x4_t *)&v200[8], v242))) + v201 + v241 - 8 < 9)
      {
        v200[24] = 0;
        v200[38] = 0;
        *(_OWORD *)&v200[34] = 0u;
        *(_OWORD *)v200 = 0u;
        *(_OWORD *)&v200[4] = 0u;
        *(_OWORD *)&v200[8] = 0u;
        *(_OWORD *)&v200[12] = 0u;
        *(_OWORD *)&v200[16] = 0u;
        *(_OWORD *)&v200[20] = 0u;
        *(_OWORD *)&v200[26] = 0u;
        *(_OWORD *)&v200[30] = 0u;
        goto LABEL_282;
      }
      v202 = HIDWORD(*(u64 *)&v200[8]);
      v200[25] = 0;
    }
    else
    {
      v202 = v200[9];
    }
  }
  if (v202)
    v200[7] = 0;
LABEL_282:
  agari->yakuNum = 0;
  v203 = v200[0];
  agari->yakuNum = v203;
  v204 = v200[1] + v203;
  agari->yakuNum = v204;
  v205 = v200[2] + v204;
  agari->yakuNum = v205;
  v206 = v200[3] + v205;
  agari->yakuNum = v206;
  v207 = v200[4] + v206;
  agari->yakuNum = v207;
  v208 = v200[5] + v207;
  agari->yakuNum = v208;
  v209 = v200[6] + v208;
  agari->yakuNum = v209;
  v210 = v200[7] + v209;
  agari->yakuNum = v210;
  v211 = v200[8] + v210;
  agari->yakuNum = v211;
  v212 = v200[9] + v211;
  agari->yakuNum = v212;
  v213 = v200[10] + v212;
  agari->yakuNum = v213;
  v214 = v200[11] + v213;
  agari->yakuNum = v214;
  v215 = v200[12] + v214;
  agari->yakuNum = v215;
  v216 = v200[13] + v215;
  agari->yakuNum = v216;
  v217 = v200[14] + v216;
  agari->yakuNum = v217;
  v218 = v200[15] + v217;
  agari->yakuNum = v218;
  v219 = v200[16] + v218;
  agari->yakuNum = v219;
  v220 = v200[17] + v219;
  agari->yakuNum = v220;
  v221 = v200[18] + v220;
  agari->yakuNum = v221;
  v222 = v200[19] + v221;
  agari->yakuNum = v222;
  v223 = v200[20] + v222;
  agari->yakuNum = v223;
  v224 = v200[21] + v223;
  agari->yakuNum = v224;
  v225 = v200[22] + v224;
  agari->yakuNum = v225;
  v226 = v200[23] + v225;
  agari->yakuNum = v226;
  v227 = v200[24] + v226;
  agari->yakuNum = v227;
  v228 = v200[25] + v227;
  agari->yakuNum = v228;
  v229 = v200[26] + v228;
  agari->yakuNum = v229;
  v230 = v200[27] + v229;
  agari->yakuNum = v230;
  v231 = v200[28] + v230;
  agari->yakuNum = v231;
  v232 = v200[29] + v231;
  agari->yakuNum = v232;
  v233 = v200[30] + v232;
  agari->yakuNum = v233;
  v234 = v200[31] + v233;
  agari->yakuNum = v234;
  v235 = v200[32] + v234;
  agari->yakuNum = v235;
  v236 = v200[33] + v235;
  agari->yakuNum = v236;
  v237 = v200[34] + v236;
  agari->yakuNum = v237;
  v238 = v200[35] + v237;
  agari->yakuNum = v238;
  v239 = v200[36] + v238;
  agari->yakuNum = v239;
  v240 = v200[37] + v239;
  agari->yakuNum = v240;
  agari->yakuNum = v200[38] + v240;
}

// 0x1d0ef70
static void CalcYakuChitoi(s32 playerIndex, Agari_t *agari, s32 tsumo, s32 agariHai) {
  s32 *v9;
  s32 *yaku;
  s32 *tehai14;
  s32 *v14;
  s64 v16;
  s32 *v17;
  s32 *v18;
  s32 *v19;
  bool v20;
  s32 v21;
  char v22;
  bool v23;
  s32 v24;
  s32 *v25;
  s32 *v26;
  bool v27;
  s32 v28;
  s32 *v29;
  s32 *v30;
  s32 *v31;
  s32 v33;
  s32 *v34;
  s32 *v36;
  s32 *v39;
  s32 *v41;
  s32 *v43;
  Work_t *v44;
  s32 v45;
  s32 *v46;
  s32 v47;
  s32 *v48;
  int8x16_t v50;
  s32 *v51;
  s32 *v53;
  s32 v54;
  s32 v55;
  s32 v56;
  s32 v57;
  s32 v58;
  s32 v59;
  s32 v60;
  s32 v61;
  s32 v62;
  s32 v63;
  s32 v64;
  s32 v65;
  s32 v66;
  s32 v67;
  s32 v68;
  s32 v69;
  s32 v70;
  s32 v71;
  s32 v72;
  s32 v73;
  s32 v74;
  s32 v75;
  s32 v76;
  s32 v77;
  s32 v78;
  s32 v79;
  s32 v80;
  s32 v81;
  s32 v82;
  s32 v83;
  s32 v84;
  s32 v85;
  s32 v86;
  s32 v87;
  s32 v88;
  s32 v89;
  s32 v90;
  s32 v91;
  s32 v92;
  s32 v93;
  int32x4_t v94;

  v9 = NewSpecific(s32, 0xEu);
  yaku = agari->yaku;
  tehai14 = Work->players[playerIndex]->tehai14;
  v9[0] = tehai14[0];
  v9[1] = tehai14[1];
  v9[2] = tehai14[2];
  v9[3] = tehai14[3];
  v9[4] = tehai14[4];
  v9[5] = tehai14[5];
  v9[6] = tehai14[6];
  v9[7] = tehai14[7];
  v9[8] = tehai14[8];
  v9[9] = tehai14[9];
  v9[10] = tehai14[10];
  v9[11] = tehai14[11];
  v9[12] = tehai14[12];
  v9[13] = tehai14[13];
  *(_OWORD *)&yaku[35] = 0u;
  *(_OWORD *)&yaku[4] = 0u;
  *(_OWORD *)&yaku[8] = 0u;
  *(_OWORD *)&yaku[12] = 0u;
  *(_OWORD *)&yaku[16] = 0u;
  *(_OWORD *)&yaku[20] = 0u;
  *(_OWORD *)&yaku[24] = 0u;
  *(_OWORD *)&yaku[28] = 0u;
  *(_OWORD *)&yaku[32] = 0u;
  *(_OWORD *)yaku = 0u;
  yaku[1] = CheckTanyao((s32)mjn, v9);
  v14 = agari->yaku;
  v16 = playerIndex;
  v14[3] = Work->players[playerIndex]->reachIndex != -1;
  v17 = agari->yaku;
  v17[4] = Work->players[playerIndex]->ippatsu != 0;
  v18 = agari->yaku;
  v19 = agari->yaku;
  if (tsumo)
    v20 = Work->players[playerIndex]->menzen == 0;
  else
    v20 = 1;
  v21 = !v20;
  v18[5] = v21;
  v22 = 1;
  if (tsumo)
    v23 = Work->yamaNum == 0;
  else
    v23 = 0;
  v24 = v23;
  v19[7] = v24;
  v25 = agari->yaku;
  v26 = agari->yaku;
  if (tsumo)
    v27 = Work->yamaNum == 0;
  else
    v27 = 0;
  v28 = v27;
  v25[8] = v28;
  v26[9] = Work->players[playerIndex]->rinshan != 0;
  v29 = agari->yaku;
  v29[10] = Work->chankan != 0;
  v30 = agari->yaku;
  v30[11] = CheckDora(playerIndex, v9);
  v31 = agari->yaku;
  v31[12] = 2;
  v33 = CheckHonitsu(playerIndex, v9);
  v31[21] = v33;
  v34 = agari->yaku;
  v34[24] = CheckHonroto(v33, v9);
  v36 = agari->yaku;
  v36[26] = CheckChinitsu(playerIndex, v9);
  v39 = agari->yaku;
  if (v39[26])
    v39[21] = 0;
  if (tsumo)
    goto LABEL_67;
  if (!Work->players[playerIndex]->ichijunme)
  {
LABEL_67:
    v39[25] = 0;
    v41 = agari->yaku;
    goto LABEL_69;
  }
  v39[25] = 8;
  v41 = agari->yaku;
LABEL_69:
  if (!tsumo)
    goto LABEL_79;
  if (Work->oya != playerIndex)
  {
LABEL_79:
    v41[32] = 0;
    v43 = agari->yaku;
    goto LABEL_81;
  }
  if (!Work->players[playerIndex]->ichijunme)
    goto LABEL_79;
  v41[32] = 13;
  v43 = agari->yaku;
LABEL_81:
  if (tsumo)
  {
    v44 = Work;
    if (v44->oya == playerIndex)
      goto LABEL_90;
    if (v44->players[playerIndex]->ichijunme)
    {
      v45 = 13;
      goto LABEL_91;
    }
  }
LABEL_90:
  v45 = 0;
LABEL_91:
  v46 = agari->yaku;
  v43[33] = v45;
  v47 = CheckTsuiso((s32)mjn, v9);
  v46[35] = v47;
  v48 = agari->yaku;
  v48[36] = CheckChinroto(v47, v9);
  v51 = agari->yaku;
  v51[27] = 2 * (Work->players[v16]->doubleReach != 0);
  v53 = agari->yaku;
  v54 = v53[27];
  if (v54)
    v53[3] = 0;
  if (v53[28] || v53[29] || v53[30] || v53[31] || v53[32] || v53[33] || v53[34] || v53[35] || v53[36] || v53[37] || v53[38])
  {
    *(_OWORD *)&v53[4] = 0u;
    *(_OWORD *)&v53[8] = 0u;
    *(_OWORD *)v53 = 0u;
    *(_OWORD *)&v53[12] = 0u;
    *(_OWORD *)&v53[16] = 0u;
    *(_OWORD *)&v53[20] = 0u;
    *(_OWORD *)&v53[24] = 0u;
  }
  else
  {
    v93 = v53[25];
    if (v93)
    {
      v94.n128_u32[0] = v53[24];
      v50.n128_u64[0] = *(u64 *)&v53[33];
      v94.n128_u32[1] = v53[26];
      v94.n128_u64[1] = *(u64 *)&v53[29];
      if (vaddvq_s32(vaddq_s32(vaddq_s32(vaddq_s32(vaddq_s32(*(int32x4_t *)v53, *(int32x4_t *)&v53[16]), vaddq_s32(vaddq_s32(*(int32x4_t *)&v53[4], *(int32x4_t *)&v53[20]), vaddq_s32(*(int32x4_t *)&v53[12], vextq_s8(*(int8x16_t *)&v53[29], v50, 8u)))), *(int32x4_t *)&v53[35]), vaddq_s32(*(int32x4_t *)&v53[8], v94))) + v54 + v93 - 8 >= 9)
      {
        v53[25] = 0;
      }
      else
      {
        v53[24] = 0;
        v53[38] = 0;
        *(_OWORD *)&v53[34] = 0u;
        *(_OWORD *)v53 = 0u;
        *(_OWORD *)&v53[4] = 0u;
        *(_OWORD *)&v53[8] = 0u;
        *(_OWORD *)&v53[12] = 0u;
        *(_OWORD *)&v53[16] = 0u;
        *(_OWORD *)&v53[20] = 0u;
        *(_OWORD *)&v53[26] = 0u;
        *(_OWORD *)&v53[30] = 0u;
      }
    }
  }
  agari->yakuNum = 0;
  v55 = v53[0];
  agari->yakuNum = v55;
  v56 = v53[1] + v55;
  agari->yakuNum = v56;
  v57 = v53[2] + v56;
  agari->yakuNum = v57;
  v58 = v53[3] + v57;
  agari->yakuNum = v58;
  v59 = v53[4] + v58;
  agari->yakuNum = v59;
  v60 = v53[5] + v59;
  agari->yakuNum = v60;
  v61 = v53[6] + v60;
  agari->yakuNum = v61;
  v62 = v53[7] + v61;
  agari->yakuNum = v62;
  v63 = v53[8] + v62;
  agari->yakuNum = v63;
  v64 = v53[9] + v63;
  agari->yakuNum = v64;
  v65 = v53[10] + v64;
  agari->yakuNum = v65;
  v66 = v53[11] + v65;
  agari->yakuNum = v66;
  v67 = v53[12] + v66;
  agari->yakuNum = v67;
  v68 = v53[13] + v67;
  agari->yakuNum = v68;
  v69 = v53[14] + v68;
  agari->yakuNum = v69;
  v70 = v53[15] + v69;
  agari->yakuNum = v70;
  v71 = v53[16] + v70;
  agari->yakuNum = v71;
  v72 = v53[17] + v71;
  agari->yakuNum = v72;
  v73 = v53[18] + v72;
  agari->yakuNum = v73;
  v74 = v53[19] + v73;
  agari->yakuNum = v74;
  v75 = v53[20] + v74;
  agari->yakuNum = v75;
  v76 = v53[21] + v75;
  agari->yakuNum = v76;
  v77 = v53[22] + v76;
  agari->yakuNum = v77;
  v78 = v53[23] + v77;
  agari->yakuNum = v78;
  v79 = v53[24] + v78;
  agari->yakuNum = v79;
  v80 = v53[25] + v79;
  agari->yakuNum = v80;
  v81 = v53[26] + v80;
  agari->yakuNum = v81;
  v82 = v53[27] + v81;
  agari->yakuNum = v82;
  v83 = v53[28] + v82;
  agari->yakuNum = v83;
  v84 = v53[29] + v83;
  agari->yakuNum = v84;
  v85 = v53[30] + v84;
  agari->yakuNum = v85;
  v86 = v53[31] + v85;
  agari->yakuNum = v86;
  v87 = v53[32] + v86;
  agari->yakuNum = v87;
  v88 = v53[33] + v87;
  agari->yakuNum = v88;
  v89 = v53[34] + v88;
  agari->yakuNum = v89;
  v90 = v53[35] + v89;
  agari->yakuNum = v90;
  v91 = v53[36] + v90;
  agari->yakuNum = v91;
  v92 = v53[37] + v91;
  agari->yakuNum = v92;
  agari->yakuNum = v53[38] + v92;
}

// 0x1d0f940
static void CalcYakuKokushi(s32 playerIndex, NormalAnalysis_t *analysis, Agari_t *agari, s32 tsumo, s32 agariHai) {
  s32 *yaku;
  s32 *v13;
  Work_t *v15;
  s64 v16;
  s32 v17;
  Player_t *v18;
  u32 *v19;
  s32 *tehai34;
  s32 v21;
  s32 *v22;

  yaku = agari->yaku;
  *(_OWORD *)&yaku[35] = 0u;
  *(_OWORD *)&yaku[4] = 0u;
  *(_OWORD *)&yaku[8] = 0u;
  *(_OWORD *)yaku = 0u;
  *(_OWORD *)&yaku[12] = 0u;
  *(_OWORD *)&yaku[16] = 0u;
  *(_OWORD *)&yaku[20] = 0u;
  *(_OWORD *)&yaku[24] = 0u;
  *(_OWORD *)&yaku[28] = 0u;
  *(_OWORD *)&yaku[32] = 0u;
  if (!tsumo)
    goto LABEL_18;
  if (Work->oya != playerIndex)
  {
LABEL_18:
    yaku[32] = 0;
    v13 = agari->yaku;
    goto LABEL_20;
  }
  if (!Work->players[playerIndex]->ichijunme)
    goto LABEL_18;
  yaku[32] = 13;
  v13 = agari->yaku;
LABEL_20:
  if (!tsumo)
    goto LABEL_29;
  v15 = Work;
  if (v15->oya == playerIndex)
    goto LABEL_29;
  if (Work->players[playerIndex]->ichijunme)
    goto LABEL_27;
LABEL_29:
  v17 = 0;
  v16 = playerIndex;
  goto LABEL_30;
LABEL_27:
  v16 = playerIndex;
  v17 = 13;
LABEL_30:
  v13[33] = v17;
  v18 = Work->players[v16];
  v19 = NewSpecific(s32, 0x22u);
  tehai34 = v18->tehai34;
  v19[8] = tehai34[0];
  v19[9] = tehai34[1];
  v19[10] = tehai34[2];
  v19[11] = tehai34[3];
  v19[12] = tehai34[4];
  v19[13] = tehai34[5];
  v19[14] = tehai34[6];
  v19[15] = tehai34[7];
  v19[16] = tehai34[8];
  v19[17] = tehai34[9];
  v19[18] = tehai34[10];
  v19[19] = tehai34[11];
  v19[20] = tehai34[12];
  v19[21] = tehai34[13];
  v19[22] = tehai34[14];
  v19[23] = tehai34[15];
  v19[24] = tehai34[16];
  v19[25] = tehai34[17];
  v19[26] = tehai34[18];
  v19[27] = tehai34[19];
  v19[28] = tehai34[20];
  v19[29] = tehai34[21];
  v19[30] = tehai34[22];
  v19[31] = tehai34[23];
  v19[32] = tehai34[24];
  v19[33] = tehai34[25];
  v19[34] = tehai34[26];
  v19[35] = tehai34[27];
  v19[36] = tehai34[28];
  v19[37] = tehai34[29];
  v19[38] = tehai34[30];
  v19[39] = tehai34[31];
  v19[40] = tehai34[32];
  v19[41] = tehai34[33];
  --v19[agariHai + 8];
  if (v19[8] == 1 && v19[16] == 1 && v19[17] == 1 && v19[25] == 1 && v19[26] == 1 && v19[34] == 1 && v19[35] == 1 && v19[36] == 1 && v19[37] == 1 && v19[38] == 1 && v19[39] == 1 && v19[40] == 1 && v19[41] == 1)
  {
    v21 = 26;
  }
  else
  {
    v21 = 13;
  }
  v22 = agari->yaku;
  v22[31] = v21;
  agari->yakuNum = v22[33] + v22[32] + v21;
}

// 0x1d02810
static s32 GetHaiType(s32 hai) {
  if (hai > 26)
    return 0;
  if (((hai % 9) & 0xFFFFFFF7) != 0)
    return 2;
  return 1;
}

// 0x1d0fd90
static s32 CalcShanten(s32 playerIndex, NormalAnalysis_t *analysis) {
  NormalAnalysis_t *v7;
  s32 toitsuNum;
  s32 tatsuNum;
  u32 v11;
  s32 v12;
  u32 v13;
  s32 v14;
  s64 v15;
  s32 v16;
  s32 v17;
  NormalAnalysis_t *target;

  target = analysis;
  v7 = target;
  switch (target->shuntsuNum + target->kotsuNum + Work->players[playerIndex]->nakiNum)
  {
    case 0:
      goto LABEL_36;
    case 1:
      toitsuNum = target->toitsuNum;
      tatsuNum = target->tatsuNum;
      if (toitsuNum)
      {
        v11 = tatsuNum + toitsuNum - 1;
        if (v11 < 5)
          return dword_3E62F14[v11];
        goto LABEL_34;
      }
      if ((u32)(tatsuNum - 5) > 0xFFFFFFFD)
        return 3;
      if (tatsuNum != 7)
        return 6 - tatsuNum;
LABEL_34:
      v7 = target;
LABEL_36:
      tatsuNum = v7->tatsuNum;
      v17 = 8 - tatsuNum;
      goto LABEL_38;
    case 2:
      v12 = target->toitsuNum;
      v13 = target->tatsuNum;
      if (v12)
      {
        if (v13 + v12 - 1 < 3)
          return 4 - (v13 + v12);
        goto LABEL_44;
      }
      if (v13 < 4)
        return dword_3CFA7F0[v13];
LABEL_44:
      v12 = target->toitsuNum;
      v13 = target->tatsuNum;
      if (v12)
      {
        v11 = v13 + v12 - 1;
        if (v11 < 5)
          return dword_3E62F14[v11];
      }
      else
      {
        if (v13 - 5 > 0xFFFFFFFD)
          return 3;
        if (v13 != 7)
          return 6 - v13;
      }
      v13 = target->tatsuNum;
      v17 = 8 - v13;
LABEL_38:
      if (v17 <= 4)
        return 4;
      else
        return v17;
    case 3:
      v14 = target->toitsuNum;
      if (v14)
        goto LABEL_19;
LABEL_50:
      if (v7->tatsuNum)
        return 1;
      else
        return 2;
      v7 = target;
      v14 = target->toitsuNum;
      if (!v14)
        goto LABEL_50;
LABEL_19:
      if (v14 == 2)
      {
        if (v7->toitsuHai[0][0] != v7->toitsuHai[1][0])
          return 0;
        return 2;
      }
      else
      {
        return !v7->tatsuNum;
      }
    case 4:
      if (target->toitsuNum == 1)
        return -1;
      if (target->fuyouNum < 1)
        return v7->tatsuNum != 1;
      v15 = 0;
      while (1)
      {
        v16 = v7->fuyouHai[v15];
        if (HaiCountInTehai(v16, playerIndex) < 4)
          break;
        v7 = target;
        if (++v15 >= target->fuyouNum)
          return v7->tatsuNum != 1;
      }
      return 0;
    default:
      return 100;
  }
}

// 0x1d101a0
static s32 HaiCountInTehai(s32 hai, s32 playerIndex) {
  Player_t *v6;
  s64 tehaiNum;
  int32x4_t *tehai14;
  s64 v9;
  s32 result;
  int32x4_t v11;
  int32x4_t v12;
  int32x4_t *v13;
  s64 v14;
  int32x4_t v15;
  int32x4_t v16;
  int32x4_t v17;
  int32x4_t v18;
  int32x4_t v19;
  int32x4_t v20;
  int32x4_t v21;
  s64 v22;
  s32 *v23;
  s32 v24;
  s64 nakiNum;
  s64 m_Items;
  u32 v27;
  bool v28;
  s64 v29;
  s64 v31;
  u32 *v32;
  u32 v33;
  s64 v34;
  u32 v36;
  s64 v37;

  v6 = Work->players[playerIndex];
  tehaiNum = (u32)v6->tehaiNum;
  if ((s32)tehaiNum < 1)
  {
    result = 0;
    goto LABEL_16;
  }
  tehai14 = v6->tehai14;
  if ((u32)tehaiNum >= 0x10)
  {
    v11 = vdupq_n_s32(hai);
    v12 = 0u;
    v9 = (u32)tehaiNum & 0xFFFFFFF0;
    v13 = tehai14 + 5;
    v14 = v9;
    v15 = 0u;
    v16 = 0u;
    v17 = 0u;
    do
    {
      v14 -= 16;
      v18 = vceqq_s32(v13[-2], v11);
      v19 = vceqq_s32(v13[-3], v11);
      v20 = vceqq_s32(v13[-1], v11);
      v21 = vceqq_s32(*v13, v11);
      v13 += 4;
      v15 = vsubq_s32(v15, v18);
      v17 = vsubq_s32(v17, v21);
      v12 = vsubq_s32(v12, v19);
      v16 = vsubq_s32(v16, v20);
    }
    while (v14);
    result = vaddvq_s32(vaddq_s32(vaddq_s32(v17, v16), vaddq_s32(v15, v12)));
    if (v9 == tehaiNum)
      goto LABEL_16;
  }
  else
  {
    v9 = 0;
    result = 0;
  }
  v22 = tehaiNum - v9;
  v23 = (s32 *)&tehai14[2] + v9;
  do
  {
    v24 = *v23++;
    if (v24 == hai)
      ++result;
    --v22;
  }
  while (v22);
LABEL_16:
  nakiNum = (u32)v6->nakiNum;
  if ((s32)nakiNum >= 1)
  {
    m_Items = v6->naki;
    do
    {
      v31 = *(u64 *)m_Items;
      v32 = *(u32 **)(*(u64 *)m_Items + 24);
      if (v32[8] == hai)
      {
        v27 = *(u32 *)(v31 + 16) - 4;
        v28 = v27 > 0x3C;
        v29 = (1 << v27) & 0x1000000000000011LL;
        if (!v28 && v29 != 0)
          goto LABEL_22;
        ++result;
        if (v32[9] != hai)
          goto LABEL_33;
      }
      else if (v32[9] != hai)
      {
        goto LABEL_33;
      }
      v33 = *(u32 *)(v31 + 16) - 4;
      v28 = v33 > 0x3C;
      v34 = (1 << v33) & 0x1000000000000011LL;
      if (!v28 && v34 != 0)
        goto LABEL_22;
      ++result;
LABEL_33:
      if (v32[10] != hai)
        goto LABEL_23;
      v36 = *(u32 *)(v31 + 16) - 4;
      v28 = v36 > 0x3C;
      v37 = (1 << v36) & 0x1000000000000011LL;
      if (v28 || v37 == 0)
      {
        ++result;
        goto LABEL_23;
      }
LABEL_22:
      result += 4;
LABEL_23:
      m_Items += 8;
      --nakiNum;
    }
    while (nakiNum);
  }
  return result;
}

// 0x1d041f0
static Agari_t *CalcAgari(s32 playerIndex, NormalAnalysis_t *analysis, s32 type) {
  s64 agariIndex;
  Agari_t *v12;
  s32 v13;
  Player_t *v14;
  s32 lastSutehai;

  agariIndex = Work->agariIndex;
  v12 = Work->agari[agariIndex];
  Work->agariIndex = agariIndex + 1;
  if (Work->turn == playerIndex)
  {
    v13 = 1;
    v14 = Work->players[playerIndex];
    lastSutehai = v14->tehai14[v14->tehaiNum - 1];
    v12->tsumo = 1;
    v12->playerIndex = playerIndex;
    goto LABEL_12;
  }
  v13 = 0;
  lastSutehai = Work->lastSutehai;
  v12->tsumo = 0;
  v12->playerIndex = playerIndex;
LABEL_12:
  v12->fromPlayerIndex = Work->turn;
  switch (type)
  {
    case 2:
      v12->fu = 100;
      CalcYakuKokushi(playerIndex, analysis, v12, v13, lastSutehai);
      break;
    case 1:
      v12->fu = 25;
      CalcYakuChitoi(playerIndex, v12, v13, (s32)method);
      goto LABEL_24;
    case 0:
      v12->fu = CalcFu(playerIndex, analysis, v13, lastSutehai);
      CalcYaku(playerIndex, analysis, v12, v13, lastSutehai);
      goto LABEL_24;
  }
LABEL_24:
  CalcTensu(playerIndex, v12, v13);
  return v12;
}

// 0x1d113c0
static Agari_t *CalcAgariChack(s32 playerIndex, NormalAnalysis_t *analysis, s32 type, bool _bTsumo, s32 agariHai) {
  s32 v13;
  s64 agariIndex;
  s64 v16;
  Agari_t *v17;

  v13 = bTsumo;
  agariIndex = Work->agariIndex;
  v16 = (s64)Work->agari + 8 * agariIndex;
  Work->agariIndex = agariIndex + 1;
  v17 = *(Agari_t *)(v16 + 32);
  v17->tsumo = v13;
  v17->playerIndex = playerIndex;
  v17->fromPlayerIndex = Work->turn;
  if (type == 2)
  {
    v17->fu = 100;
    CalcYakuKokushi(playerIndex, analysis, v17, v13, agariHai);
    goto LABEL_17;
  }
  if (type == 1)
  {
    v17->fu = 25;
    CalcYakuChitoi(playerIndex, v17, v13, bTsumo);
    goto LABEL_19;
  }
  if (!type)
  {
    v17->fu = CalcFu(playerIndex, analysis, v13, agariHai);
    CalcYaku(playerIndex, analysis, v17, v13, agariHai);
    goto LABEL_19;
  }
LABEL_17:
LABEL_19:
  CalcTensu(playerIndex, v17, v13);
  return v17;
}

// 0x1d11580
static NormalAnalysis_t *MakeAnalysis(s32 playerIndex, AnalyzeNode_t *node) {
  NormalAnalysis_t *v5;
  u32 *v7;
  Work_t *Work_local;
  s32 *tehai34;
  s32 level;
  NormalAnalysis_t *v13;
  Work_t *v14;
  s64 v15;
  s64 v16;
  s32 *v17;
  s64 v18;
  u32 *v19;
  u32 *v20;
  Work_t *v21;
  s64 m_Items;
  s64 v23;
  s32 *haiInt;
  s64 v25;
  s64 v26;
  u32 *v27;
  Work_t *v28;
  s64 v29;
  s64 v30;
  s32 *v31;
  s64 v32;
  s64 v33;
  u32 *v34;
  Work_t *v35;
  s64 v36;
  s64 v37;
  s32 *v38;
  s64 v39;
  u32 *v40;
  s64 v41;
  u32 *v42;
  Work_t *v43;
  NormalAnalysis_t *analysis;
  NormalAnalysis_t *v45;
  NormalAnalysis_t *v46;
  NormalAnalysis_t *v47;
  s32 *p_analysisIndex;
  s32 v49;
  NormalAnalysis_t *v50;
  s32 v51;
  s64 v52;
  NormalAnalysis_t *v53;
  s32 v54;
  s64 v55;
  NormalAnalysis_t *v56;
  Work_t *v57;
  NormalAnalysis_t *v58;
  NormalAnalysis_t *v59;
  Work_t *v60;
  NormalAnalysis_t *v61;
  NormalAnalysis_t *v62;
  s32 v63;
  NormalAnalysis_t *v64;
  s32 v65;

  v5 = Allocate(NormalAnalysis_t);
  _ctor(v5, 0);
  v7 = NewSpecific(s32, 0x22u);
  Work_local = Work;
  ++Work_local->analysisIndex;
  tehai34 = Work_local->players[playerIndex]->tehai34;
  v7[8] = tehai34[0];
  v7[9] = tehai34[1];
  v7[10] = tehai34[2];
  v7[11] = tehai34[3];
  v7[12] = tehai34[4];
  v7[13] = tehai34[5];
  v7[14] = tehai34[6];
  v7[15] = tehai34[7];
  v7[16] = tehai34[8];
  v7[17] = tehai34[9];
  v7[18] = tehai34[10];
  v7[19] = tehai34[11];
  v7[20] = tehai34[12];
  v7[21] = tehai34[13];
  v7[22] = tehai34[14];
  v7[23] = tehai34[15];
  v7[24] = tehai34[16];
  v7[25] = tehai34[17];
  v7[26] = tehai34[18];
  v7[27] = tehai34[19];
  v7[28] = tehai34[20];
  v7[29] = tehai34[21];
  v7[30] = tehai34[22];
  v7[31] = tehai34[23];
  v7[32] = tehai34[24];
  v7[33] = tehai34[25];
  v7[34] = tehai34[26];
  v7[35] = tehai34[27];
  v7[36] = tehai34[28];
  v7[37] = tehai34[29];
  v7[38] = tehai34[30];
  v7[39] = tehai34[31];
  v7[40] = tehai34[32];
  v7[41] = tehai34[33];
  level = node->level;
  v13 = Work->analysis[Work->analysisIndex
                                                                          - 1];
  v13->shuntsuNum = 0;
  v13->kotsuNum = 0;
  v13->toitsuNum = 0;
  v13->tatsuNum = 0;
  v13->fuyouNum = 0;
  if (level >= 1)
  {
    do
    {
      switch (node->type)
      {
        case 1:
          v21 = Work;
          m_Items = v21->analysis;
          v23 = *(u64 *)(m_Items + 8 * (v21->analysisIndex - 1));
          haiInt = node->haiInt;
          *(u32 *)(*(u64 *)(*(u64 *)(v23 + 24) + 8 * *(s32 *)(v23 + 16) + 32) + 32) = haiInt[0];
          v25 = *(u64 *)(m_Items + 8 * (v21->analysisIndex - 1));
          *(u32 *)(*(u64 *)(*(u64 *)(v25 + 24) + 8 * *(s32 *)(v25 + 16) + 32) + 36) = haiInt[1];
          v26 = *(u64 *)(m_Items + 8 * (v21->analysisIndex - 1));
          *(u32 *)(*(u64 *)(*(u64 *)(v26 + 24) + 8 * *(s32 *)(v26 + 16) + 32) + 40) = haiInt[2];
          v27 = v7 + 8;
          v27[haiInt[0]] = v7[haiInt[0] + 8] - 1;
          v27[haiInt[1]] = v7[haiInt[1] + 8] - 1;
          v27[haiInt[2]] = v7[haiInt[2] + 8] - 1;
          v20 = (*(u64 *)(m_Items + 8 * (v21->analysisIndex - 1)) + 16);
          goto LABEL_10;
        case 2:
          v28 = Work;
          v29 = v28->analysis;
          v30 = *(u64 *)(v29 + 8 * (v28->analysisIndex - 1));
          v31 = node->haiInt;
          *(u32 *)(*(u64 *)(*(u64 *)(v30 + 40) + 8 * *(s32 *)(v30 + 32) + 32) + 32) = v31[0];
          v32 = *(u64 *)(v29 + 8 * (v28->analysisIndex - 1));
          *(u32 *)(*(u64 *)(*(u64 *)(v32 + 40) + 8 * *(s32 *)(v32 + 32) + 32) + 36) = v31[1];
          v33 = *(u64 *)(v29 + 8 * (v28->analysisIndex - 1));
          *(u32 *)(*(u64 *)(*(u64 *)(v33 + 40) + 8 * *(s32 *)(v33 + 32) + 32) + 40) = v31[2];
          v34 = v7 + 8;
          v34[v31[0]] = v7[v31[0] + 8] - 1;
          v34[v31[1]] = v7[v31[1] + 8] - 1;
          v34[v31[2]] = v7[v31[2] + 8] - 1;
          v20 = (*(u64 *)(v29 + 8 * (v28->analysisIndex - 1)) + 32);
          goto LABEL_10;
        case 3:
          v35 = Work;
          v36 = v35->analysis;
          v37 = *(u64 *)(v36 + 8 * (v35->analysisIndex - 1));
          v38 = node->haiInt;
          *(u32 *)(*(u64 *)(*(u64 *)(v37 + 56) + 8 * *(s32 *)(v37 + 48) + 32) + 32) = v38[0];
          v39 = *(u64 *)(v36 + 8 * (v35->analysisIndex - 1));
          *(u32 *)(*(u64 *)(*(u64 *)(v39 + 56) + 8 * *(s32 *)(v39 + 48) + 32) + 36) = v38[1];
          v40 = v7 + 8;
          v40[v38[0]] = v7[v38[0] + 8] - 1;
          v40[v38[1]] = v7[v38[1] + 8] - 1;
          v20 = (*(u64 *)(v36 + 8 * (v35->analysisIndex - 1)) + 48);
          goto LABEL_10;
        case 4:
        case 5:
          v14 = Work;
          v15 = v14->analysis;
          v16 = *(u64 *)(v15 + 8 * (v14->analysisIndex - 1));
          v17 = node->haiInt;
          *(u32 *)(*(u64 *)(*(u64 *)(v16 + 72) + 8 * *(s32 *)(v16 + 64) + 32) + 32) = v17[0];
          v18 = *(u64 *)(v15 + 8 * (v14->analysisIndex - 1));
          *(u32 *)(*(u64 *)(*(u64 *)(v18 + 72) + 8 * *(s32 *)(v18 + 64) + 32) + 36) = v17[1];
          v19 = v7 + 8;
          v19[v17[0]] = v7[v17[0] + 8] - 1;
          v19[v17[1]] = v7[v17[1] + 8] - 1;
          v20 = (*(u64 *)(v15 + 8 * (v14->analysisIndex - 1)) + 64);
LABEL_10:
          ++*v20;
          break;
        default:
          break;
      }
      node = node->parent;
      --level;
    }
    while (level);
  }
  v41 = 0;
  v42 = v7 + 8;
  do
  {
    switch (v42[v41])
    {
      case 1:
        v57 = Work;
        analysis = v57->analysis;
        p_analysisIndex = &v57->analysisIndex;
        v58 = analysis[v57->analysisIndex - 1];
        v55 = (s64)v58->fuyouHai + 4 * v58->fuyouNum;
        goto LABEL_30;
      case 2:
        v43 = Work;
        analysis = v43->analysis;
        v45 = analysis;
        v59 = analysis[v43->analysisIndex - 1];
        p_analysisIndex = &v43->analysisIndex;
        v52 = (s64)v59->fuyouHai + 4 * v59->fuyouNum;
        goto LABEL_28;
      case 3:
        v60 = Work;
        analysis = v60->analysis;
        p_analysisIndex = &v60->analysisIndex;
        v61 = analysis[v60->analysisIndex - 1];
        v61->fuyouHai[v61->fuyouNum] = v41;
        v62 = analysis[v60->analysisIndex - 1];
        v63 = v62->fuyouNum + 1;
        v62->fuyouNum = v63;
        v62->fuyouHai[v63] = v41;
        v53 = analysis[v60->analysisIndex - 1];
        goto LABEL_29;
      case 4:
        v43 = Work;
        analysis = v43->analysis;
        v45 = analysis;
        v46 = analysis[v43->analysisIndex - 1];
        v46->fuyouHai[v46->fuyouNum] = v41;
        v47 = analysis[v43->analysisIndex - 1];
        p_analysisIndex = &v43->analysisIndex;
        v49 = v47->fuyouNum + 1;
        v47->fuyouNum = v49;
        v47->fuyouHai[v49] = v41;
        v50 = analysis[v43->analysisIndex - 1];
        v51 = v50->fuyouNum + 1;
        v50->fuyouNum = v51;
        v52 = (s64)v50->fuyouHai + 4 * v51;
LABEL_28:
        *(u32 *)(v52 + 32) = v41;
        v53 = v45[v43->analysisIndex - 1];
LABEL_29:
        v54 = v53->fuyouNum + 1;
        v53->fuyouNum = v54;
        v55 = (s64)v53->fuyouHai + 4 * v54;
LABEL_30:
        *(u32 *)(v55 + 32) = v41;
        v56 = analysis[*p_analysisIndex - 1];
        ++v56->fuyouNum;
        break;
      default:
        break;
    }
    ++v41;
  }
  while (v41 != 34);
  v64 = Work->analysis[Work->analysisIndex - 1];
  v65 = CalcShanten(playerIndex, v64);
  v64->shanten = v65;
  return Work->analysis[Work->analysisIndex - 1];
}

// 0x1d05120
static void AnalyzeTehaiNormal(s32 playerIndex) {
  s32 *v4;
  s64 i;
  Work_t *Work_local;
  AnalyzeNode_t *NextNode;

  v4 = NewSpecific(s32, 0x22u);
  for (i = 32; i != 168; i += 4)
  {
    Work_local = Work;
    *(u32 *)((char *)&v4->obj.klass + i) = *(u32 *)((char *)&Work_local->players[playerIndex]->tehai34->obj.klass + i);
  }
  Work_local = Work;
  Work_local->analyzeNodeIndex = 0;
  Work_local->analysisIndex = 0;
  Work_local->agariIndex = 0;
  NextNode = AnalyzeGetNextNode(0, 0);
  AnalyzeTehaiSubMentsu(playerIndex, v4, NextNode);
}

// 0x1d05230
static void AnalyzeTehaiChitoi(s32 playerIndex) {
  Player_t *players;
  ChitoiAnalysis_t *chitoiAnalysis;
  Player_t *v7;
  s32 *tehai34;
  s64 v9;
  s32 v10;
  s32 *m_Items;
  s64 v12;
  s64 v13;
  s64 v14;
  s64 v15;
  s64 v16;
  s64 fuyouNum;
  s64 v18;
  s64 toitsuNum;
  s32 *toitsu;
  s64 v21;
  s64 v22;
  s32 v23;
  bool v24;
  s32 v25;

  players = Work->players;
  chitoiAnalysis = Work->chitoiAnalysis;
  v7 = players[playerIndex];
  if (v7->nakiNum)
  {
    chitoiAnalysis->shanten = 14;
  }
  else
  {
    tehai34 = v7->tehai34;
    v9 = 0;
    v10 = 0;
    chitoiAnalysis->toitsuNum = 0;
    chitoiAnalysis->fuyouNum = 0;
    m_Items = tehai34;
    do
    {
      switch (m_Items[v9])
      {
        case 1:
          fuyouNum = chitoiAnalysis->fuyouNum;
          v18 = (s64)chitoiAnalysis->fuyouHai + 4 * fuyouNum;
          chitoiAnalysis->fuyouNum = fuyouNum + 1;
          *(u32 *)(v18 + 32) = v9;
          v10 = 1;
          break;
        case 2:
          toitsuNum = chitoiAnalysis->toitsuNum;
          toitsu = chitoiAnalysis->toitsu;
          chitoiAnalysis->toitsuNum = toitsuNum + 1;
          goto LABEL_14;
        case 3:
          v21 = chitoiAnalysis->toitsuNum;
          v22 = (s64)chitoiAnalysis->toitsu + 4 * v21;
          chitoiAnalysis->toitsuNum = v21 + 1;
          *(u32 *)(v22 + 32) = v9;
          toitsu = chitoiAnalysis->fuyouHai;
          toitsuNum = chitoiAnalysis->fuyouNum;
          chitoiAnalysis->fuyouNum = toitsuNum + 1;
LABEL_14:
          toitsu[toitsuNum] = v9;
          break;
        case 4:
          v12 = chitoiAnalysis->toitsuNum;
          v13 = (s64)chitoiAnalysis->toitsu + 4 * v12;
          chitoiAnalysis->toitsuNum = v12 + 1;
          *(u32 *)(v13 + 32) = v9;
          v14 = chitoiAnalysis->fuyouNum;
          v15 = chitoiAnalysis->fuyouHai;
          chitoiAnalysis->fuyouNum = v14 + 1;
          *(u32 *)(v15 + 4 * v14) = v9;
          v16 = chitoiAnalysis->fuyouNum;
          chitoiAnalysis->fuyouNum = v16 + 1;
          *(u32 *)(v15 + 4 * v16) = v9;
          break;
        default:
          break;
      }
      ++v9;
    }
    while (v9 != 34);
    v23 = chitoiAnalysis->toitsuNum;
    v24 = v23 == 7;
    v25 = 7 - v10 - v23;
    if (v24)
      v25 = -1;
    chitoiAnalysis->shanten = v25;
  }
}

// 0x1d053f0
static void AnalyzeTehaiKokushi(s32 playerIndex) {
  s64 v5;
  KokushiAnalysis_t *kokushiAnalysis;
  s64 v7;
  s32 v8;
  u64 i;
  s64 v10;
  s64 v11;
  s64 amariNum;
  s64 m_Items;
  s64 v14;
  s64 v15;
  s64 v16;
  u32 *v17;
  s32 v18;
  s32 *fuyouHai;
  s32 v20;
  s64 fuyouNum;
  s64 kokushiNum;
  s32 *kokushiHai;
  s64 v24;
  s64 v25;
  s64 v26;
  s64 v27;
  s64 v28;
  s32 v29;

  v5 = (s64)Work->players + 8 * playerIndex;
  kokushiAnalysis = Work->kokushiAnalysis;
  v7 = *(u64 *)(v5 + 32);
  kokushiAnalysis->amariNum = 0;
  kokushiAnalysis->fuyouNum = 0;
  kokushiAnalysis->kokushiNum = 0;
  if (*(u32 *)(v7 + 72))
  {
    v8 = 14;
    goto LABEL_27;
  }
  for (i = 0; i != 34; ++i)
  {
    if (i >= 0x1B)
    {
      v15 = *(u64 *)(v7 + 32);
      goto LABEL_20;
    }
    v15 = *(u64 *)(v7 + 32);
    if ((((u8)i - 9 * (u8)((477218589 * (u64)(u8)i) >> 32)) & 7) != 0)
    {
      v16 = v15 + 4 * i;
      v18 = *(u32 *)(v16 + 32);
      v17 = (v16 + 32);
      if (v18 >= 1)
      {
        fuyouHai = kokushiAnalysis->fuyouHai;
        v20 = 0;
        do
        {
          fuyouNum = kokushiAnalysis->fuyouNum;
          ++v20;
          kokushiAnalysis->fuyouNum = fuyouNum + 1;
          fuyouHai[fuyouNum] = i;
        }
        while (v20 < *v17);
      }
      continue;
    }
LABEL_20:
    switch (*(u32 *)(v15 + 4 * i + 32))
    {
      case 1:
        kokushiNum = kokushiAnalysis->kokushiNum;
        kokushiHai = kokushiAnalysis->kokushiHai;
        kokushiAnalysis->kokushiNum = kokushiNum + 1;
        goto LABEL_23;
      case 2:
        v24 = kokushiAnalysis->kokushiNum;
        v25 = (s64)kokushiAnalysis->kokushiHai + 4 * v24;
        kokushiAnalysis->kokushiNum = v24 + 1;
        *(u32 *)(v25 + 32) = i;
        kokushiHai = kokushiAnalysis->amariHai;
        kokushiNum = kokushiAnalysis->amariNum;
        kokushiAnalysis->amariNum = kokushiNum + 1;
LABEL_23:
        kokushiHai[kokushiNum] = i;
        continue;
      case 3:
        v10 = kokushiAnalysis->kokushiNum;
        v11 = (s64)kokushiAnalysis->kokushiHai + 4 * v10;
        kokushiAnalysis->kokushiNum = v10 + 1;
        *(u32 *)(v11 + 32) = i;
        amariNum = kokushiAnalysis->amariNum;
        m_Items = kokushiAnalysis->amariHai;
        goto LABEL_9;
      case 4:
        v26 = kokushiAnalysis->kokushiNum;
        v27 = (s64)kokushiAnalysis->kokushiHai + 4 * v26;
        kokushiAnalysis->kokushiNum = v26 + 1;
        *(u32 *)(v27 + 32) = i;
        v28 = kokushiAnalysis->amariNum;
        m_Items = kokushiAnalysis->amariHai;
        kokushiAnalysis->amariNum = v28 + 1;
        *(u32 *)(m_Items + 4 * v28) = i;
        amariNum = kokushiAnalysis->amariNum;
LABEL_9:
        kokushiAnalysis->amariNum = amariNum + 1;
        *(u32 *)(m_Items + 4 * amariNum) = i;
        v14 = kokushiAnalysis->amariNum;
        kokushiAnalysis->amariNum = v14 + 1;
        *(u32 *)(m_Items + 4 * v14) = i;
        break;
      default:
        continue;
    }
  }
  v29 = kokushiAnalysis->kokushiNum;
  kokushiAnalysis->shanten = 13 - v29;
  if (kokushiAnalysis->amariNum)
  {
    v8 = 12 - v29;
LABEL_27:
    kokushiAnalysis->shanten = v8;
  }
}

// 0x1d041e0
static void PrintAnalysisNormal(NormalAnalysis_t *analysis) {
  ;
}

// 0x1d020b0
static s32 CheckAgariNormal(s32 playerIndex) {
  u32 *v4;
  s32 result;
  s32 v15;
  s32 v16;
  s32 v17;
  s32 v18;
  s32 v19;

  v4 = NewSpecific(s32, 5u);
  v4[8] = CheckAgariSub(Work->players[playerIndex]->tehai34, 0);
  v4[9] = CheckAgariSub(Work->players[playerIndex]->tehai34, 1);
  v4[10] = CheckAgariSub(Work->players[playerIndex]->tehai34, 2);
  v4[11] = CheckAgariSub(Work->players[playerIndex]->tehai34, 3);
  result = CheckAgariSub(Work->players[playerIndex]->tehai34, 4);
  v15 = v4[8];
  v4[12] = result;
  if (!v15)
    return 0;
  if (v15 == 2)
  {
    v16 = 0;
    v17 = 1;
    v18 = v4[9];
    if (v18)
      goto LABEL_16;
    return v18;
  }
  v17 = 0;
  v16 = 1;
  v18 = v4[9];
  if (!v18)
    return v18;
LABEL_16:
  if (v18 == 2)
  {
    if (!v16)
      return 0;
    ++v17;
  }
  v19 = v4[10];
  if (!v19)
    return v19;
  if (v19 == 2)
  {
    if (v17)
      return 0;
    v17 = 1;
  }
  v19 = v4[11];
  if (!v19)
    return v19;
  if (v19 == 2)
  {
    if (!v17)
    {
      v17 = 1;
      goto LABEL_31;
    }
    return 0;
  }
LABEL_31:
  if (result)
    return result != 2 || !v17;
  return result;
}

// 0x1d02330
static s32 CheckAgariChitoi(s32 playerIndex) {
  Player_t *v4;
  s32 *tehai34;

  v4 = Work->players[playerIndex];
  if (v4->menzen
&& !v4->nakiNum
&& (tehai34 = v4->tehai34, (tehai34[0] | 2) == 2)
&& (tehai34[1] | 2) == 2
&& (tehai34[2] | 2) == 2
&& (tehai34[3] | 2) == 2
&& (tehai34[4] | 2) == 2
&& (tehai34[5] | 2) == 2
&& (tehai34[6] | 2) == 2
&& (tehai34[7] | 2) == 2
&& (tehai34[8] | 2) == 2
&& (tehai34[9] | 2) == 2
&& (tehai34[10] | 2) == 2
&& (tehai34[11] | 2) == 2
&& (tehai34[12] | 2) == 2
&& (tehai34[13] | 2) == 2
&& (tehai34[14] | 2) == 2
&& (tehai34[15] | 2) == 2
&& (tehai34[16] | 2) == 2
&& (tehai34[17] | 2) == 2
&& (tehai34[18] | 2) == 2
&& (tehai34[19] | 2) == 2
&& (tehai34[20] | 2) == 2
&& (tehai34[21] | 2) == 2
&& (tehai34[22] | 2) == 2
&& (tehai34[23] | 2) == 2
&& (tehai34[24] | 2) == 2
&& (tehai34[25] | 2) == 2
&& (tehai34[26] | 2) == 2
&& (tehai34[27] | 2) == 2
&& (tehai34[28] | 2) == 2
    && (tehai34[29] | 2) == 2
    && (tehai34[30] | 2) == 2
    && (tehai34[31] | 2) == 2
    && (tehai34[32] | 2) == 2)
  {
    return (tehai34[33] & 0xFFFFFFFD) == 0;
  }
  else
  {
    return 0;
  }
}

// 0x1d043f0
static Agari_t *ChooseAgari(s32 playerIndex) {
  mjn *v2;
  s32 tensuGet;
  Agari_t *v4;
  s64 v5;
  mjn *v6;
  mjn *v7;
  s32 yakuNum;
  mjn *v9;
  Work_t *Work_local;
  s32 v12;

  tensuGet = -1;
  v4 = 0;
  v5 = 4;
  v6 = v2;
  v7 = v2;
  yakuNum = -1;
  while (1)
  {
    Work_local = Work;
    if (v5 - 4 >= Work_local->agariIndex)
      return v4;
    v12 = *(u32 *)(*((u64 *)&Work_local->agari->obj.klass + v5) + 40);
    if (v12 > yakuNum)
    {
      v9 = v2;
      goto LABEL_7;
    }
    v9 = v2;
    v2 = v6;
    if (v12 != yakuNum)
      goto LABEL_8;
    if (*(u32 *)(*((u64 *)&Work->agari->obj.klass + v5) + 56) > tensuGet)
    {
LABEL_7:
      v4 = *((Agari_t *)&Work->agari->obj.klass + v5);
      v7 = v2;
      yakuNum = v4->yakuNum;
      tensuGet = v4->tensuGet;
    }
LABEL_8:
    v6 = v2;
    ++v5;
    v2 = v9;
  }
}

// 0x1d11d80
static AnalyzeNode_t *AnalyzeGetNextNode(AnalyzeNode_t *parent, s32 analyzeType) {
  AnalyzeNode_t *v5;
  s64 analyzeNodeIndex;
  AnalyzeNode_t *v9;
  s32 v10;

  v5 = Allocate(AnalyzeNode_t);
  _ctor(v5, 0);
  analyzeNodeIndex = Work->analyzeNodeIndex;
  v9 = Work->analyzeNodes[analyzeNodeIndex];
  Work->analyzeNodeIndex = analyzeNodeIndex + 1;
  v9->index = analyzeNodeIndex;
  v9->parent = parent;
  if (parent)
    v10 = parent->level + 1;
  else
    v10 = 0;
  v9->level = v10;
  v9->shuntsu0 = 0;
  v9->shuntsu1 = 0;
  v9->shuntsu2 = 0;
  v9->kotsu = 0;
  v9->toitsu = 0;
  v9->ryanmen = 0;
  v9->kanchan = 0;
  v9->analysis = 0;
  v9->type = analyzeType;
  return v9;
}

// 0x1d12550
static s32 AnalyzeCheckSubSequence(AnalyzeNode_t *node, AnalyzeNode_t *target) {
  s32 type;
  u32 v6;
  AnalyzeNode_t *toitsu;
  AnalyzeNode_t *kanchan;
  AnalyzeNode_t *ryanmen;
  s32 result;
  AnalyzeNode_t *shuntsu0;
  AnalyzeNode_t *shuntsu1;
  AnalyzeNode_t *shuntsu2;

  if (!node)
    return 0;
  type = target->type;
  if (node->type == type && node->haiInt[0] == target->haiInt[0])
    return 1;
  v6 = type - 3;
  if (v6 <= 0xFFFFFFFD)
  {
    if (v6 >= 3)
      return 0;
    toitsu = node->toitsu;
    if (AnalyzeCheckSubSequence(toitsu, target))
      return 1;
    kanchan = node->kanchan;
    if (AnalyzeCheckSubSequence(kanchan, target))
      return 1;
    ryanmen = node->ryanmen;
    goto LABEL_29;
  }
  shuntsu0 = node->shuntsu0;
  if (!!AnalyzeCheckSubSequence(node->shuntsu0, target))
    return 1;
  shuntsu1 = node->shuntsu1;
  if (AnalyzeCheckSubSequence(shuntsu1, target))
    return 1;
  shuntsu2 = node->shuntsu2;
  if (AnalyzeCheckSubSequence(shuntsu2, target))
    return 1;
  ryanmen = node->kotsu;
LABEL_29:
  result = AnalyzeCheckSubSequence(ryanmen, target);
  if (result)
    return 1;
  return result;
}

// 0x1d12710
static s32 AnalyzeTehaiSubTatsu(s32 playerIndex, s32 *tehai34, AnalyzeNode_t *node) {
  AnalyzeNode_t *v7;
  s32 v9;
  AnalyzeNode_t *p_ryanmen;
  s64 v11;
  s32 *haiInt;
  AnalyzeNode_t *v14;
  AnalyzeNode_t *v16;
  s64 v17;
  int32x2_t *m_Items;
  s32 *v20;
  AnalyzeNode_t *toitsu;
  AnalyzeNode_t *v23;
  s32 v24;
  AnalyzeNode_t *NextNode;
  s32 *v26;
  AnalyzeNode_t *v27;
  s64 v28;
  AnalyzeNode_t *v30;
  s32 *v31;
  AnalyzeNode_t *v32;
  s64 v34;
  char *v35;
  bool v36;
  s32 *v38;
  AnalyzeNode_t *v39;
  AnalyzeNode_t *v41;
  NormalAnalysis_t *Analysis;
  AnalyzeNode_t *v44;
  s32 *v45;
  s32 v47;
  AnalyzeNode_t *target;

  v7 = Allocate(AnalyzeNode_t);
  _ctor(v7, 0);
  v9 = 0;
  p_ryanmen = &node->ryanmen;
  v11 = 8;
  target = &node->kanchan;
  while (1)
  {
    if (*((s32 *)&tehai34->obj.klass + v11) < 2)
      goto LABEL_6;
    haiInt = v7->haiInt;
    v7->type = 3;
    haiInt[0] = v11 - 8;
    haiInt[1] = v11 - 8;
    v14 = p_ryanmen;
    if (!AnalyzeCheckSubSequence(p_ryanmen, v7))
      goto LABEL_12;
LABEL_5:
    ++v9;
LABEL_6:
    if (++v11 == 42)
    {
      v47 = 0;
      goto LABEL_15;
    }
  }
  if (AnalyzeCheckSubSequence(v14, v7))
    goto LABEL_5;
LABEL_12:
  v16 = target;
  if (AnalyzeCheckSubSequence(v16, v7))
    goto LABEL_5;
  v24 = v11 - 8;
  NextNode = AnalyzeGetNextNode(node, 3);
  v26 = NextNode->haiInt;
  v27 = NextNode;
  v26[0] = v24;
  v26[1] = v24;
  node->toitsu = NextNode;
  v26[2] = -1;
  v28 = 4 * v11;
  *(u32 *)((char *)&tehai34->obj.klass + v28) -= 2;
  AnalyzeTehaiSubTatsu(playerIndex, tehai34, v27);
  *(u32 *)((char *)&tehai34->obj.klass + v28) += 2;
  v47 = 1;
LABEL_15:
  v17 = 0;
  m_Items = tehai34;
  while (2)
  {
    if (!m_Items->n64_u32[0] || !m_Items->n64_u32[1] || (u32)v17 / 9 != ((s32)v17 + 1) / 9u)
    {
LABEL_18:
      ++v17;
      m_Items = ((char *)m_Items + 4);
      if (v17 == 26)
        goto LABEL_34;
      continue;
    }
    break;
  }
  v7->type = 5;
  v20 = v7->haiInt;
  v20[0] = v17;
  v20[1] = v17 + 1;
  toitsu = node->toitsu;
  v20[2] = -1;
  if (!!AnalyzeCheckSubSequence(toitsu, v7))
    goto LABEL_17;
  v23 = target;
  if (AnalyzeCheckSubSequence(v23, v7))
  {
LABEL_17:
    ++v9;
    goto LABEL_18;
  }
  v30 = AnalyzeGetNextNode(node, 5);
  v31 = v30->haiInt;
  v32 = v30;
  node->ryanmen = v30;
  v31[0] = v17;
  v31[1] = v17 + 1;
  v31[2] = -1;
  m_Items->n64_u64[0] = vadd_s32((int32x2_t)m_Items->n64_u64[0], (int32x2_t)-1).n64_u64[0];
  AnalyzeTehaiSubTatsu(playerIndex, tehai34, v32);
  v47 = 1;
  m_Items->n64_u64[0] = vadd_s32((int32x2_t)m_Items->n64_u64[0], (int32x2_t)0x100000001LL).n64_u64[0];
LABEL_34:
  v34 = 0;
  while (2)
  {
    v35 = (char *)tehai34 + 4 * v34;
    if (!*((u32 *)v35 + 8) || (*((u32 *)v35 + 10) ? (v36 = (u32)v34 / 9 == ((s32)v34 + 2) / 9u) : (v36 = 0), !v36))
    {
LABEL_37:
      if (++v34 == 25)
      {
        if (!(v47 | v9))
        {
          Analysis = MakeAnalysis(playerIndex, node);
          node->analysis = Analysis;
        }
        return 0;
      }
      continue;
    }
    break;
  }
  v7->type = 4;
  v38 = v7->haiInt;
  v38[0] = v34;
  v38[1] = v34 + 2;
  v39 = node->toitsu;
  v38[2] = -1;
  if (!AnalyzeCheckSubSequence(v39, v7))
    goto LABEL_48;
LABEL_36:
  ++v9;
  goto LABEL_37;
LABEL_48:
  v41 = p_ryanmen;
  if (AnalyzeCheckSubSequence(v41, v7))
    goto LABEL_36;
  v44 = AnalyzeGetNextNode(node, 4);
  v45 = v44->haiInt;
  node->kanchan = v44;
  v45[0] = v34;
  v45[1] = v34 + 2;
  v45[2] = -1;
  --*((u32 *)v35 + 8);
  --*((u32 *)v35 + 10);
  AnalyzeTehaiSubTatsu(playerIndex, tehai34, v44);
  ++*((u32 *)v35 + 8);
  ++*((u32 *)v35 + 10);
  return 0;
}

// 0x1d11ef0
static s32 AnalyzeTehaiSubMentsu(s32 playerIndex, s32 *tehai34, AnalyzeNode_t *node) {
  AnalyzeNode_t *v6;
  u64 v9;
  char v10;
  s32 v11;
  AnalyzeNode_t *p_shuntsu0;
  s32 *v13;
  bool v14;
  u32 v15;
  AnalyzeNode_t *v16;
  s32 *haiInt;
  AnalyzeNode_t *v19;
  AnalyzeNode_t *v21;
  AnalyzeNode_t *v23;
  AnalyzeNode_t *NextNode;
  s32 *v25;
  AnalyzeNode_t *v26;
  u64 v27;
  u64 v29;
  s32 *v30;
  AnalyzeNode_t *v31;
  s32 *v32;
  AnalyzeNode_t *v33;
  u64 v34;
  s32 v36;
  u64 v37;
  s32 *v38;
  AnalyzeNode_t *v39;
  s32 *v40;
  u64 v41;
  u64 v43;
  s64 v44;
  s32 *v45;
  AnalyzeNode_t *v47;
  AnalyzeNode_t *v49;
  AnalyzeNode_t *v51;
  AnalyzeNode_t *v53;
  s32 v54;
  s32 v56;
  AnalyzeNode_t *v57;
  s32 *v58;
  s64 v59;
  s32 v61;
  s32 v62;
  s32 v63;
  AnalyzeNode_t *parent;
  AnalyzeNode_t *p_kotsu;
  AnalyzeNode_t *p_shuntsu2;
  AnalyzeNode_t *p_shuntsu1;

  v6 = Allocate(AnalyzeNode_t);
  _ctor(v6, 0);
  v9 = 0;
  parent = node;
  p_shuntsu1 = &node->shuntsu1;
  v10 = 0;
  v11 = 0;
  p_shuntsu0 = &node->shuntsu0;
  v13 = &tehai34[4];
  p_kotsu = &node->kotsu;
  p_shuntsu2 = &node->shuntsu2;
  while (1)
  {
    if (*(v13 - 4))
    {
      if (*(v13 - 3))
      {
        if (*(v13 - 2))
        {
          v15 = (u32)v9 / 9;
          if ((u32)v9 / 9 == ((s32)v9 + 2) / 9u)
            break;
        }
      }
    }
LABEL_6:
    v14 = v9++ > 0x17;
    ++v13;
    v10 = v14;
    if (v9 == 25)
      goto LABEL_39;
  }
  v16 = p_shuntsu0;
  v6->type = 1;
  haiInt = v6->haiInt;
  haiInt[0] = v9;
  haiInt[1] = v9 + 1;
  haiInt[2] = v9 + 2;
  if (AnalyzeCheckSubSequence(v16, v6))
    goto LABEL_5;
  v19 = p_shuntsu1;
  if (AnalyzeCheckSubSequence(p_shuntsu1, v6))
    goto LABEL_5;
  v21 = p_shuntsu2;
  if (!AnalyzeCheckSubSequence(v21, v6))
    goto LABEL_26;
LABEL_5:
  ++v11;
  goto LABEL_6;
LABEL_26:
  v23 = p_kotsu;
  if (AnalyzeCheckSubSequence(v23, v6))
    goto LABEL_5;
  v62 = v9 + 1;
  v63 = v9 + 2;
  NextNode = AnalyzeGetNextNode(parent, 1);
  v25 = NextNode->haiInt;
  v26 = NextNode;
  v25[0] = v9;
  v25[1] = v62;
  v25[2] = v63;
  parent->shuntsu0 = NextNode;
  v27 = vadd_s32(*(int32x2_t *)(v13 - 4), (int32x2_t)-1).n64_u64[0];
  --*(v13 - 2);
  *((u64 *)v13 - 2) = v27;
  AnalyzeTehaiSubMentsu(playerIndex, tehai34, v26);
  v29 = vadd_s32(*(int32x2_t *)(v13 - 4), (int32x2_t)0x100000001LL).n64_u64[0];
  ++*(v13 - 2);
  *((u64 *)v13 - 2) = v29;
  if (v15 == ((s32)v9 + 3) / 9 && *(v13 - 1))
  {
    v6->type = 1;
    v30 = v6->haiInt;
    v30[2] = v9 + 3;
    v30[0] = v62;
    v30[1] = v63;
    v61 = v9 + 3;
    v31 = AnalyzeGetNextNode(parent, 1);
    v32 = v31->haiInt;
    v33 = v31;
    v32[0] = v62;
    v32[1] = v63;
    v32[2] = v61;
    parent->shuntsu1 = v31;
    v34 = vadd_s32(*(int32x2_t *)(v13 - 3), (int32x2_t)-1).n64_u64[0];
    --*(v13 - 1);
    *(u64 *)(v13 - 3) = v34;
    AnalyzeTehaiSubMentsu(playerIndex, tehai34, v33);
    v36 = v9 + 4;
    v37 = vadd_s32(*(int32x2_t *)(v13 - 3), (int32x2_t)0x100000001LL).n64_u64[0];
    ++*(v13 - 1);
    *(u64 *)(v13 - 3) = v37;
    if (v15 == v36 / 9 && *v13)
    {
      v6->type = 1;
      v38 = v6->haiInt;
      v38[2] = v36;
      v38[0] = v63;
      v38[1] = v61;
      v39 = AnalyzeGetNextNode(parent, 1);
      v40 = v39->haiInt;
      parent->shuntsu2 = v39;
      v40[0] = v63;
      v40[1] = v61;
      v40[2] = v36;
      v41 = vadd_s32(*(int32x2_t *)(v13 - 1), (int32x2_t)-1).n64_u64[0];
      --*(v13 - 2);
      *(u64 *)(v13 - 1) = v41;
      AnalyzeTehaiSubMentsu(playerIndex, tehai34, v39);
      v43 = vadd_s32(*(int32x2_t *)(v13 - 1), (int32x2_t)0x100000001LL).n64_u64[0];
      ++*(v13 - 2);
      *(u64 *)(v13 - 1) = v43;
    }
  }
LABEL_39:
  v44 = 8;
  while (2)
  {
    if (*((s32 *)&tehai34->obj.klass + v44) >= 3)
    {
      v45 = v6->haiInt;
      v6->type = 2;
      v45[0] = v44 - 8;
      v45[1] = v44 - 8;
      v47 = p_shuntsu0;
      if (!AnalyzeCheckSubSequence(p_shuntsu0, v6))
      {
        v49 = p_shuntsu1;
        if (!AnalyzeCheckSubSequence(p_shuntsu1, v6))
        {
          v51 = p_shuntsu2;
          if (!AnalyzeCheckSubSequence(p_shuntsu2, v6))
            goto LABEL_56;
          goto LABEL_9000;
          if (!AnalyzeCheckSubSequence(v51, v6))
          {
LABEL_56:
            v53 = p_kotsu;
            if (!AnalyzeCheckSubSequence(v53, v6))
            {
              v56 = v44 - 8;
              v57 = AnalyzeGetNextNode(parent, 2);
              v58 = v57->haiInt;
              parent->kotsu = v57;
              v58[1] = v56;
              v58[2] = v56;
              v58[0] = v56;
              v59 = 4 * v44;
              *(u32 *)((char *)&tehai34->obj.klass + v59) -= 3;
              AnalyzeTehaiSubMentsu(playerIndex, tehai34, v57);
              v54 = playerIndex;
              *(u32 *)((char *)&tehai34->obj.klass + v59) += 3;
              goto LABEL_62;
            }
          }
LABEL_9000:
        }
      }
      ++v11;
    }
    if (++v44 != 42)
      continue;
    break;
  }
  if (((u8)v10 & (v11 == 0)) != 1)
    return 0;
  v54 = playerIndex;
LABEL_62:
  AnalyzeTehaiSubTatsu(v54, tehai34, parent);
  return 0;
}

// 0x1d104e0
static s32 CalcFu(s32 playerIndex, NormalAnalysis_t *analysis, s32 tsumo, s32 agariHai) {
  Player_t *v11;
  s32 v12;
  s64 shuntsuNum;
  s32 v14;
  s32 v15;
  s32 **m_Items;
  s32 v17;
  u32 v18;
  s32 v19;
  s32 v20;
  s32 **kotsuHai;
  s64 v22;
  s32 v23;
  s64 v24;
  s32 v25;
  s64 v26;
  Naki_t *v27;
  s32 type;
  s32 v29;
  s32 v30;
  s32 v31;
  s32 v32;
  bool v33;
  s32 v34;

  v11 = Work->players[playerIndex];
  if (tsumo)
  {
    v12 = 22;
    goto LABEL_10;
  }
  if (v11->menzen)
    v12 = 30;
  else
    v12 = 20;
LABEL_10:
  shuntsuNum = (u32)analysis->shuntsuNum;
  v14 = analysis->toitsuHai[0][0];
  v15 = 2 * (v14 == agariHai);
  if ((s32)shuntsuNum < 1)
    goto LABEL_35;
  m_Items = analysis->shuntsuHai;
  if (agariHai % 9 == 6)
  {
    while ((*m_Items)[1] != agariHai && (*m_Items)[0] != agariHai)
    {
      ++m_Items;
      if (!--shuntsuNum)
        goto LABEL_35;
    }
LABEL_23:
    v17 = v12 + 2;
    v18 = v14 - 31;
    if ((u32)(v14 - 31) <= 0xFFFFFFFB)
      goto LABEL_36;
LABEL_24:
    if (v14 == Work->kyoku / 4 + 27)
      v19 = v17 + 2;
    else
      v19 = v17;
    if (v14 == v11->kaze)
      v20 = v19 + 2;
    else
      v20 = v19;
    if (analysis->kotsuNum >= 1)
      goto LABEL_40;
    goto LABEL_56;
  }
  if (agariHai % 9 != 2)
  {
    while ((*m_Items)[1] != agariHai)
    {
      ++m_Items;
      if (!--shuntsuNum)
        goto LABEL_35;
    }
    goto LABEL_23;
  }
  while (1)
  {
    if ((*m_Items)[1] == agariHai)
      goto LABEL_23;
    if ((*m_Items)[2] == agariHai)
      break;
    ++m_Items;
    if (!--shuntsuNum)
      goto LABEL_35;
  }
  v15 = 2;
LABEL_35:
  v17 = v15 + v12;
  v18 = v14 - 31;
  if ((u32)(v14 - 31) > 0xFFFFFFFB)
    goto LABEL_24;
LABEL_36:
  if (v18 >= 3)
    v20 = v17;
  else
    v20 = v17 + 2;
  if (analysis->kotsuNum >= 1)
  {
LABEL_40:
    kotsuHai = analysis->kotsuHai;
    v22 = 4;
    do
    {
      v25 = *(u32 *)(*((u64 *)&kotsuHai->obj.klass + v22) + 32);
      if (v25 >= 27)
      {
        kotsuHai = analysis->kotsuHai;
        goto LABEL_52;
      }
      kotsuHai = analysis->kotsuHai;
      if (((v25 % 9) & 0xFFFFFFF7) != 0)
      {
        if (*(u32 *)(*((u64 *)&kotsuHai->obj.klass + v22) + 32) != agariHai || tsumo || v11->tehai34[agariHai] != 3)
        {
          goto LABEL_55;
        }
        v23 = 2;
        goto LABEL_42;
      }
LABEL_52:
      if (*(u32 *)(*((u64 *)&kotsuHai->obj.klass + v22) + 32) == agariHai && !tsumo && v11->tehai34[agariHai] == 3)
      {
LABEL_55:
        v23 = 4;
        goto LABEL_42;
      }
      v23 = 8;
LABEL_42:
      v20 += v23;
      v24 = v22 - 3;
      ++v22;
    }
    while (v24 < analysis->kotsuNum);
  }
LABEL_56:
  if (v11->nakiNum >= 1)
  {
    v26 = 0;
    while (1)
    {
      v27 = v11->naki[v26];
      type = v27->type;
      if (type <= 8)
        break;
      if (type == 64)
        goto LABEL_69;
      if (type == 32)
      {
        v29 = v27->hai[0];
        if (v29 > 26)
          goto LABEL_81;
        if (((v29 % 9) & 0xFFFFFFF7) == 0)
        {
LABEL_81:
          v20 += 4;
          goto LABEL_60;
        }
        v20 += 2;
      }
LABEL_60:
      if (++v26 >= v11->nakiNum)
        goto LABEL_84;
    }
    if (type == 4)
    {
      v31 = v27->hai[0];
      if (v31 > 26)
        goto LABEL_83;
      goto LABEL_9001;
      if (v31 > 26)
      {
LABEL_83:
        v20 += 32;
        goto LABEL_60;
      }
LABEL_9001:
      if (((v31 % 9) & 0xFFFFFFF7) == 0)
        goto LABEL_83;
    }
    else
    {
      if (type != 8)
        goto LABEL_60;
LABEL_69:
      v30 = v27->hai[0];
      if (v30 <= 26)
      {
        if (((v30 % 9) & 0xFFFFFFF7) != 0)
        {
          v20 += 8;
          goto LABEL_60;
        }
      }
    }
    v20 += 16;
    goto LABEL_60;
  }
LABEL_84:
  v32 = 10 * (v20 / 10);
  v33 = v20 == v32;
  v34 = v32 + 10;
  if (v33)
    return v20;
  else
    return v34;
}

// 0x1d109b0
static void CalcTensu(s32 playerIndex, Agari_t *agari, s32 tsumo) {
  s32 *v7;
  s32 yakuNum;
  int32x4_t *v9;
  char *v12;
  s32 fu;
  s32 v15;
  s32 v16;
  s32 oya;
  int32x4_t *v18;
  s32 v19;
  s32 v20;
  s32 v22;
  u32 v23;
  s32 v24;
  s32 v25;
  s32 v26;
  s32 v27;
  s32 v28;
  bool v29;
  s32 v30;
  s32 v31;
  s64 v32;
  s32 v33;
  s64 v34;
  s32 v35;
  s64 v36;
  s32 v37;
  s32 **mjn_tensuTableKoRon_local;
  s64 v39;
  s32 v40;
  s32 *yaku;
  int32x4_t v42;
  s32 v43;
  int32x4_t v44;
  s32 v45;
  s64 v46;
  s32 v47;
  s64 v48;
  int32x4_t v49;
  s32 v50;
  s64 v51;
  u16 v52;
  s32 v53;
  s64 v54;
  s32 v55;
  s32 v56;
  s64 v57;
  s32 *tensu;
  s32 v59;
  s32 *v60;
  char *v61;
  u32 *v62;
  s32 v63;
  s32 v64;
  s32 *p_honba;
  s32 v66;
  s32 *v67;
  s32 v68;
  s32 tensuGet;
  Work_t *v70;
  s32 honba;
  Player_t *v72;
  s32 v73;
  s32 v74;
  char *v75;
  s64 fromPlayerIndex;

  v7 = NewSpecific(s32, 4u);
  yakuNum = agari->yakuNum;
  v9 = v7;
  if (yakuNum == 1 && agari->fu == 20)
    agari->fu = 30;
  yakuNum = agari->yakuNum;
  v12 = (char *)v9 + 4 * playerIndex;
  fromPlayerIndex = agari->fromPlayerIndex;
  fu = agari->fu;
  if (yakuNum == 4)
    v15 = 5;
  else
    v15 = yakuNum;
  if (fu >= 120)
    v16 = v15;
  else
    v16 = yakuNum;
  oya = Work->oya;
  v9[2].n128_u64[0] = 0;
  v9[2].n128_u64[1] = 0;
  v18 = v9 + 2;
  switch (v16)
  {
    case 1:
    case 2:
    case 3:
    case 4:
      v19 = agari->fu;
      if (v19 == 25)
        v20 = 3;
      else
        v20 = fu / 10 - 2;
      v16 -= v19 == 25;
      if (oya != playerIndex)
      {
        if (tsumo)
        {
          v25 = *((u32 *)&mjn_tensuTableKoTsumo[v20]->max_length + v16 + 1);
          if (v25 >= 0)
            v26 = v25;
          else
            v26 = v25 + 1;
          v27 = v26 >> 1;
          v28 = 100 * (v27 / 100);
          v29 = v27 == v28;
          v30 = v28 + 100;
          if (v29)
            v31 = v27;
          else
            v31 = v30;
          *v18 = vdupq_n_s32(-v31);
          v9[2].n128_u32[Work->oya] = -v25;
          v24 = v25 + 2 * v31;
          goto LABEL_83;
        }
        mjn_tensuTableKoRon_local = mjn_tensuTableKoRon;
LABEL_68:
        v24 = *((u32 *)&mjn_tensuTableKoRon_local[v20]->max_length + v16 + 1);
        v9[2].n128_u32[fromPlayerIndex] = -v24;
        goto LABEL_83;
      }
      if (!tsumo)
      {
        mjn_tensuTableKoRon_local = mjn_tensuTableOyaRon;
        goto LABEL_68;
      }
      v22 = *((u32 *)&mjn_tensuTableOyaTsumo[v20]->max_length + v16 + 1);
      v23 = -v22;
      v24 = 3 * v22;
      *v18 = vdupq_n_s32(v23);
LABEL_83:
      *((u32 *)v12 + 8) = v24;
LABEL_84:
      yaku = agari->yaku;
      if (!yaku[28] && !yaku[29] && !yaku[30] && !yaku[31] && !yaku[32] && !yaku[33] && !yaku[34] && !yaku[35] && !yaku[36] && !yaku[37] && !yaku[38])
      {
        if (v16 < 13)
          goto LABEL_152;
        if (oya == playerIndex)
        {
          if (tsumo)
            *v18 = vdupq_n_s32(0xFFFFC180);
          else
            v9[2].n128_u32[fromPlayerIndex] = -48000;
          v55 = 48000;
        }
        else
        {
          if (tsumo)
          {
            *v18 = vdupq_n_s32(0xFFFFE0C0);
            v53 = -16000;
            v54 = Work->oya;
          }
          else
          {
            v54 = fromPlayerIndex;
            v53 = -32000;
          }
          v9[2].n128_u32[v54] = v53;
          v55 = 32000;
        }
        *((u32 *)v12 + 8) = v55;
        if ((u32)(v16 - 52) < 0xFFFFFFF3)
          goto LABEL_98;
        goto LABEL_141;
      }
      if ((u32)(v16 - 26) >= 0xFFFFFFF3)
      {
        if (oya == playerIndex)
        {
          if (tsumo)
          {
            v43 = 48000;
            *v18 = vdupq_n_s32(0xFFFFC180);
          }
          else
          {
            v9[2].n128_u32[fromPlayerIndex] = -48000;
            v43 = 48000;
          }
        }
        else
        {
          if (tsumo)
          {
            *v18 = vdupq_n_s32(0xFFFFE0C0);
            v45 = -16000;
            v46 = Work->oya;
          }
          else
          {
            v46 = fromPlayerIndex;
            v45 = -32000;
          }
          v9[2].n128_u32[v46] = v45;
          v43 = 32000;
        }
        goto LABEL_151;
      }
      if ((u32)(v16 - 39) < 0xFFFFFFF3)
      {
        if ((u32)(v16 - 52) < 0xFFFFFFF3)
        {
LABEL_98:
          if (v16 < 52)
            goto LABEL_152;
          if (oya == playerIndex)
          {
            if (tsumo)
            {
              v42.n128_u64[0] = 0xF9000000F9LL;
              v42.n128_u64[1] = 0xF9000000F9LL;
              v43 = 192000;
              *v18 = v42;
            }
            else
            {
              v9[2].n128_u32[fromPlayerIndex] = -192000;
              v43 = 192000;
            }
            goto LABEL_151;
          }
          if (tsumo)
          {
            v49.n128_u64[0] = 0x7C0000007CLL;
            v49.n128_u64[1] = 0x7C0000007CLL;
            *v18 = v49;
            v50 = -64000;
            v51 = Work->oya;
          }
          else
          {
            v51 = fromPlayerIndex;
            v50 = -128000;
          }
          v9[2].n128_u32[v51] = v50;
          v52 = -3072;
          goto LABEL_150;
        }
LABEL_141:
        if (oya == playerIndex)
        {
          if (tsumo)
          {
            v43 = 144000;
            *v18 = vdupq_n_s32(0xFFFF4480);
          }
          else
          {
            v9[2].n128_u32[fromPlayerIndex] = -144000;
            v43 = 144000;
          }
          goto LABEL_151;
        }
        if (tsumo)
        {
          *v18 = vdupq_n_s32(0xFFFFA240);
          v56 = -48000;
          v57 = Work->oya;
          goto LABEL_149;
        }
LABEL_148:
        v57 = fromPlayerIndex;
        v56 = -96000;
LABEL_149:
        v9[2].n128_u32[v57] = v56;
        v52 = 30464;
LABEL_150:
        v43 = v52 | 0x10000;
        goto LABEL_151;
      }
      if (oya != playerIndex)
      {
        if (tsumo)
        {
          *v18 = vdupq_n_s32(0xFFFFC180);
          v47 = -32000;
          v48 = Work->oya;
        }
        else
        {
          v48 = fromPlayerIndex;
          v47 = -64000;
        }
        v9[2].n128_u32[v48] = v47;
        v43 = 64000;
        goto LABEL_151;
      }
      if (!tsumo)
        goto LABEL_148;
      v44.n128_u64[0] = 0x7C0000007CLL;
      v44.n128_u64[1] = 0x7C0000007CLL;
      v43 = 96000;
      *v18 = v44;
LABEL_151:
      *((u32 *)v12 + 8) = v43;
LABEL_152:
      tensu = agari->tensu;
      agari->tensuGet = v9[2].n128_i32[playerIndex];
      v59 = v9[2].n128_i32[0];
      tensu[0] = v59;
      tensu[1] = v9[2].n128_i32[1];
      tensu[2] = v9[2].n128_i32[2];
      tensu[3] = v9[2].n128_i32[3];
      if (agari->tsumo)
      {
        v60 = tensu;
        v66 = -100;
        p_honba = &Work->honba;
        tensu[0] = v59 - 100 * *p_honba;
        v68 = v60[2];
        v60[1] -= 100 * *p_honba;
        v60[2] = v68 - 100 * *p_honba;
        v67 = &v60[3];
      }
      else
      {
        v61 = (char *)tensu + 4 * playerIndex;
        v64 = *((u32 *)v61 + 8);
        v62 = v61 + 32;
        v63 = v64;
        tensu = agari->tensu;
        p_honba = &Work->honba;
        v66 = -300;
        *v62 = v63 - 100 * *p_honba;
        v67 = &tensu[agari->fromPlayerIndex];
        v60 = tensu;
      }
      *v67 += *p_honba * v66;
      tensuGet = agari->tensuGet;
      v60 = agari->tensu;
      v70 = Work;
      honba = v70->honba;
      agari->tensuGet = tensuGet + 300 * honba;
      v60[playerIndex] += 400 * honba;
      if (!tsumo)
      {
        v70 = Work;
        v72 = v70->players[fromPlayerIndex];
        if (v72->reachIndex == v72->sutehaiIndex - 1)
        {
          v70 = Work;
          v72 = v70->players[fromPlayerIndex];
          if (v72->ippatsu == 1)
          {
            v70 = Work;
            v72 = v70->players[fromPlayerIndex];
            --v70->reachBou;
            v72->tensu += 1000;
          }
        }
      }
      v73 = agari->tensuGet;
      v74 = 1000 * Work->reachBou;
      agari->tensuGet = v74 + v73;
      v75 = (char *)agari->tensu + 4 * playerIndex;
      *((u32 *)v75 + 8) += v74;
      return;
    case 5:
      if (oya == playerIndex)
      {
        if (tsumo)
          *v18 = vdupq_n_s32(0xFFFFF060);
        else
          v9[2].n128_u32[fromPlayerIndex] = -12000;
        v16 = 5;
        v24 = 12000;
      }
      else
      {
        if (tsumo)
        {
          *v18 = vdupq_n_s32(0xFFFFF830);
          v39 = Work->oya;
          v40 = -4000;
        }
        else
        {
          v39 = fromPlayerIndex;
          v40 = -8000;
        }
        v9[2].n128_u32[v39] = v40;
        v16 = 5;
        v24 = 8000;
      }
      goto LABEL_83;
    case 6:
    case 7:
      if (oya == playerIndex)
      {
        if (tsumo)
        {
          v24 = 18000;
          *v18 = vdupq_n_s32(0xFFFFE890);
        }
        else
        {
          v9[2].n128_u32[fromPlayerIndex] = -18000;
          v24 = 18000;
        }
      }
      else
      {
        if (tsumo)
        {
          *v18 = vdupq_n_s32(0xFFFFF448);
          v34 = Work->oya;
          v35 = -6000;
        }
        else
        {
          v34 = fromPlayerIndex;
          v35 = -12000;
        }
        v9[2].n128_u32[v34] = v35;
        v24 = 12000;
      }
      goto LABEL_83;
    case 8:
    case 9:
    case 10:
      if (oya != playerIndex)
      {
        if (tsumo)
        {
          *v18 = vdupq_n_s32(0xFFFFF060);
          v32 = Work->oya;
          v33 = -8000;
        }
        else
        {
          v32 = fromPlayerIndex;
          v33 = -16000;
        }
        v9[2].n128_u32[v32] = v33;
        v24 = 16000;
        goto LABEL_83;
      }
      if (!tsumo)
        goto LABEL_59;
      *v18 = vdupq_n_s32(0xFFFFE0C0);
      goto LABEL_61;
    case 11:
    case 12:
      if (oya == playerIndex)
      {
        if (tsumo)
        {
          v24 = 36000;
          *v18 = vdupq_n_s32(0xFFFFD120);
        }
        else
        {
          v9[2].n128_u32[fromPlayerIndex] = -36000;
          v24 = 36000;
        }
      }
      else
      {
        if (tsumo)
        {
          *v18 = vdupq_n_s32(0xFFFFE890);
          v36 = Work->oya;
          v37 = -12000;
        }
        else
        {
LABEL_59:
          v36 = fromPlayerIndex;
          v37 = -24000;
        }
        v9[2].n128_u32[v36] = v37;
LABEL_61:
        v24 = 24000;
      }
      goto LABEL_83;
    default:
      goto LABEL_84;
  }
}

// 0x1d12bd0
static s32 GetHaiColor(s32 hai) {
  if ((u32)(hai / 9) >= 3)
    return 3;
  else
    return hai / 9;
}

// 0x1d12c00
static s32 GetMentsuType(s32 *mentsu) {
  s32 v4;
  s32 v5;
  s32 v7;

  v4 = mentsu[0];
  if (v4 > 26)
    return 0;
  if (((v4 % 9) & 0xFFFFFFF7) == 0)
    return 1;
  v5 = mentsu[2];
  if (v5 <= 26)
  {
    if (((v5 % 9) & 0xFFFFFFF7) == 0)
      return 1;
  }
  v7 = mentsu[1];
  if (v7 > 26)
    return 2;
  if (((v7 % 9) & 0xFFFFFFF7) != 0)
    return 2;
  return 1;
}

// 0x1d05e10
static s32 CheckPinfu(s32 playerIndex, NormalAnalysis_t *analysis, s32 **tehai14, s32 agariHai) {
  s32 v9;
  u32 v10;
  Player_t *v12;
  s64 shuntsuNum;
  s32 **i;
  s32 v15;
  s32 v16;

  if (analysis->shuntsuNum != 4)
    return 0;
  v9 = analysis->toitsuHai[0][0];
  v10 = v9 - 31;
  if ((u32)(v9 - 31) > 0xFFFFFFFB)
  {
    v12 = Work->players[playerIndex];
    if (v9 == Work->kyoku / 4 + 27 || v9 == v12->kaze)
      return 0;
    goto LABEL_13;
  }
  if (v10 < 3)
    return 0;
LABEL_13:
  shuntsuNum = (u32)analysis->shuntsuNum;
  if ((s32)shuntsuNum < 1)
    return 0;
  for (i = analysis->shuntsuHai; ; ++i)
  {
    v15 = (*i)[0];
    v16 = (*i)[2];
    if (v15 == agariHai && v16 % 9 != 8)
      break;
    if ((u32)(954437177 * v15 + 238609294) >= 0x1C71C71D && v16 == agariHai)
      break;
    if (!--shuntsuNum)
      return 0;
  }
  return 1;
}

// 0x1d0b320
static s32 CheckKuiPinfuGata(s32 playerIndex, NormalAnalysis_t *analysis, s32 agariHai) {
  Player_t *v9;
  s32 result;
  s32 nakiNum;
  Naki_t *naki;
  s64 v13;
  s32 v14;
  s32 type;
  bool v16;
  s32 shuntsuNum;
  s32 v19;
  s64 v20;
  s32 v21;
  s32 v24;
  s64 v27;
  s32 **i;
  s32 v29;
  s32 v30;

  v9 = Work->players[playerIndex];
  if (v9->menzen == 1)
    return 0;
  nakiNum = v9->nakiNum;
  if (nakiNum < 1)
  {
    shuntsuNum = analysis->shuntsuNum;
    if (shuntsuNum != 4)
      return 0;
  }
  else
  {
    naki = v9->naki;
    v13 = 0;
    v14 = 0;
    if (nakiNum != 1)
    {
      do
      {
        v20 = (s64)naki + 8 * v13;
        v21 = *(u32 *)(*(u64 *)(v20 + 32) + 16);
        if (v21 == 268435584 || v21 == 268435968 || v21 == 268435712)
          ++v14;
        v24 = *(u32 *)(*(u64 *)(v20 + 40) + 16);
        if (v24 == 268435584 || v24 == 268435968 || v24 == 268435712)
          ++v14;
        v13 += 2;
      }
      while ((nakiNum & 0xFFFFFFFE) != v13);
    }
    if ((nakiNum & 1) != 0)
    {
      type = naki[v13]->type;
      v16 = type == 268435584 || type == 268435968;
      if (v16 || type == 268435712)
        ++v14;
    }
    shuntsuNum = analysis->shuntsuNum;
    if (shuntsuNum + v14 != 4)
      return 0;
  }
  v19 = analysis->toitsuHai[0][0];
  if ((u32)(v19 - 31) > 0xFFFFFFFB)
  {
    if (v19 == Work->kyoku / 4 + 27)
      return 0;
    if (v19 == v9->kaze)
      return 0;
    shuntsuNum = analysis->shuntsuNum;
    if (shuntsuNum < 1)
      return 0;
  }
  else if ((u32)(v19 - 34) >= 0xFFFFFFFD || shuntsuNum < 1)
  {
    return 0;
  }
  v27 = shuntsuNum;
  for (i = analysis->shuntsuHai; ; ++i)
  {
    v29 = (*i)[0];
    v30 = (*i)[2];
    if (v29 == agariHai && v30 % 9 != 8)
      break;
    if ((u32)(954437177 * v29 + 238609294) >= 0x1C71C71D && v30 == agariHai)
      break;
    result = 0;
    if (!--v27)
      return result;
  }
  return 1;
}

// 0x1d05fc0
static s32 CheckTanyao(s32 playerIndex, s32 *tehai14) {
  s32 v4;
  s32 v5;
  s32 v6;
  s32 v7;
  s32 v8;
  s32 v9;
  s32 v10;
  s32 v11;
  s32 v12;
  s32 v13;
  s32 v14;
  s32 v15;
  s32 v16;
  s32 v17;

  v4 = tehai14[0];
  if (v4 < 27 && ((v4 % 9) & 0xFFFFFFF7) != 0)
  {
    v5 = tehai14[1];
    if (v5 <= 26 && ((v5 % 9) & 0xFFFFFFF7) != 0)
    {
      v6 = tehai14[2];
      if (v6 <= 26 && ((v6 % 9) & 0xFFFFFFF7) != 0)
      {
        v7 = tehai14[3];
        if (v7 <= 26 && ((v7 % 9) & 0xFFFFFFF7) != 0)
        {
          v8 = tehai14[4];
          if (v8 <= 26 && ((v8 % 9) & 0xFFFFFFF7) != 0)
          {
            v9 = tehai14[5];
            if (v9 <= 26 && ((v9 % 9) & 0xFFFFFFF7) != 0)
            {
              v10 = tehai14[6];
              if (v10 <= 26 && ((v10 % 9) & 0xFFFFFFF7) != 0)
              {
                v11 = tehai14[7];
                if (v11 <= 26 && ((v11 % 9) & 0xFFFFFFF7) != 0)
                {
                  v12 = tehai14[8];
                  if (v12 <= 26 && ((v12 % 9) & 0xFFFFFFF7) != 0)
                  {
                    v13 = tehai14[9];
                    if (v13 <= 26 && ((v13 % 9) & 0xFFFFFFF7) != 0)
                    {
                      v14 = tehai14[10];
                      if (v14 <= 26 && ((v14 % 9) & 0xFFFFFFF7) != 0)
                      {
                        v15 = tehai14[11];
                        if (v15 <= 26 && ((v15 % 9) & 0xFFFFFFF7) != 0)
                        {
                          v16 = tehai14[12];
                          if (v16 <= 26 && ((v16 % 9) & 0xFFFFFFF7) != 0)
                          {
                            v17 = tehai14[13];
                            if (v17 <= 26)
                              return ((v17 % 9) & 0xFFFFFFF7) != 0;
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
      }
    }
  }
  return 0;
}

// 0x1d0b5c0
static s32 CheckReach(s32 playerIndex, s32 **tehai14) {
  return Work->players[playerIndex]->reachIndex != -1;
}

// 0x1d0b640
static s32 CheckIppatsu(s32 playerIndex, s32 **tehai14) {
  return Work->players[playerIndex]->ippatsu != 0;
}

// 0x1d06600
static s32 CheckIpeiko(s32 playerIndex, NormalAnalysis_t *analysis, s32 **tehai14) {
  s32 shuntsuNum;
  s32 **v9;
  s32 v10;
  s32 v11;
  s32 **shuntsuHai;
  s32 v13;
  s32 v14;
  s32 v15;
  s32 v17;
  s32 v18;

  if (!Work->players[playerIndex]->menzen)
    return 0;
  shuntsuNum = analysis->shuntsuNum;
  switch (shuntsuNum)
  {
    case 4:
      shuntsuHai = analysis->shuntsuHai;
      v13 = shuntsuHai[0][0];
      v14 = shuntsuHai[1][0];
      if (v13 == v14)
      {
        return 1;
      }
      else
      {
        v17 = shuntsuHai[2][0];
        if (v13 == v17)
        {
          return 1;
        }
        else
        {
          v18 = shuntsuHai[3][0];
          return v14 == v17 || v13 == v18 || v14 == v18 || v17 == v18;
        }
      }
    case 3:
      v9 = analysis->shuntsuHai;
      v10 = v9[0][0];
      v11 = v9[1][0];
      if (v10 == v11)
      {
        return 1;
      }
      else
      {
        v15 = v9[2][0];
        return v11 == v15 || v15 == v10;
      }
    case 2:
      return analysis->shuntsuHai[0][0] == analysis->shuntsuHai[1][0];
    default:
      return 0;
  }
}

// 0x1d067a0
static s32 CheckYakuhai(s32 playerIndex, NormalAnalysis_t *analysis, s32 **tehai14) {
  s64 v7;
  Player_t *v8;
  s64 v9;
  s32 v10;
  s32 v11;
  s32 v12;
  Player_t *v14;
  s32 v15;
  bool v16;
  s32 v17;
  s64 i;
  s32 v19;
  s32 v20;
  Work_t *v21;
  Player_t *v22;
  s32 v23;
  s32 v24;

  v7 = playerIndex;
  v8 = Work->players[playerIndex];
  if (analysis->kotsuNum >= 1)
  {
    v9 = 0;
    v10 = 0;
    while (1)
    {
      v12 = analysis->kotsuHai[v9][0];
      if (v12 >= 27)
      {
        if ((u32)v12 > 0x1E)
        {
          v11 = 1;
        }
        else
        {
          v14 = Work->players[v7];
          if (Work->kyoku <= 3)
            v15 = 27;
          else
            v15 = 28;
          v16 = v15 == v12;
          v11 = v15 == v12;
          if (v16)
            v17 = 2;
          else
            v17 = 1;
          if (v14->kaze == v12)
            v11 = v17;
        }
        goto LABEL_8;
      }
      v11 = 0;
LABEL_8:
      v10 += v11;
      if (++v9 >= analysis->kotsuNum)
        goto LABEL_31;
    }
  }
  v10 = 0;
LABEL_31:
  if (v8->nakiNum >= 1)
  {
    for (i = 0; i < v8->nakiNum; ++i)
    {
      v20 = v8->naki[i]->hai[0];
      if (v20 >= 27)
      {
        if ((u32)v20 > 0x1E)
        {
          v19 = 1;
        }
        else
        {
          v21 = Work;
          v22 = v21->players[v7];
          v21 = Work;
          if (v21->kyoku <= 3)
            v23 = 27;
          else
            v23 = 28;
          v16 = v23 == v20;
          v19 = v23 == v20;
          if (v16)
            v24 = 2;
          else
            v24 = 1;
          if (v22->kaze == v20)
            v19 = v24;
        }
        goto LABEL_34;
      }
      v19 = 0;
LABEL_34:
      v10 += v19;
    }
  }
  return v10;
}

// 0x1d06a70
static s32 CheckHaitei(s32 playerIndex, s32 tsumo) {
  return tsumo && Work->yamaNum == 0;
}

// 0x1d06af0
static s32 CheckHoutei(s32 playerIndex, s32 tsumo) {
  return (Work->yamaNum | tsumo) == 0;
}

// 0x1d06b70
static s32 CheckRinshan(s32 playerIndex, s32 **tehai14) {
  return Work->players[playerIndex]->rinshan != 0;
}

// 0x1d06bf0
static s32 CheckChankan(void) {
  return Work->chankan != 0;
}

// 0x1d0b750
static s32 CheckDora(s32 playerIndex, s32 *tehai14) {
  Player_t *v6;
  s32 *v7;
  s32 nakiNum;
  s64 v9;
  s64 v10;
  u32 v11;
  s64 m_Items;
  s64 v13;
  u32 v14;
  bool v15;
  s64 v16;
  bool v17;
  s64 v18;
  s64 v19;
  s64 v20;
  s64 v22;
  s32 v23;
  u32 v26;
  int32x4_t v27;
  u8 v28;
  int32x4_t v29;
  char v30;
  u32 v31;
  u32 v32;
  s64 v49;
  s32 *v50;
  s32 v51;
  s32 v52;
  s64 v53;
  s32 *v54;
  Work_t *v55;
  u32 v56;
  int32x4_t v57;
  u8 v58;
  int32x4_t v59;
  char v60;
  u32 v61;
  u32 v62;
  s64 v79;
  s32 *v80;
  s32 v81;
  s32 v82;
  s64 v84;

  v6 = Work->players[playerIndex];
  v7 = NewSpecific(s32, 4u);
  nakiNum = v6->nakiNum;
  v9 = v7;
  if (nakiNum < 1)
  {
    v11 = 0;
  }
  else
  {
    v10 = 0;
    v11 = 0;
    m_Items = v6->naki;
    do
    {
      v13 = *(u64 *)(m_Items + 8 * v10);
      v14 = *(u32 *)(v13 + 16) - 4;
      v15 = v14 > 0x3C;
      v16 = (1 << v14) & 0x1000000000000011LL;
      v17 = v15 || v16 == 0;
      if (!v17)
      {
        v18 = (s64)(char *)v7 + 4 * (s32)v11++;
        *(u32 *)(v18 + 32) = *(u32 *)(*(u64 *)(v13 + 24) + 32);
        nakiNum = v6->nakiNum;
      }
      ++v10;
    }
    while (v10 < nakiNum);
  }
  v19 = playerIndex;
  v20 = v11;
  v84 = v19;
  v22 = 0;
  v23 = 0;
  while (1)
  {
    if (v22 >= Work->doraNum)
      break;
    v26 = Work->dora[v22];
    v27 = vdupq_n_s32(v26);
    v28 = vaddvq_s16(vandq_s8(vuzp1q_s16(vceqq_s32(*(int32x4_t *)tehai14, v27), vceqq_s32(*(int32x4_t *)&tehai14[4], v27)), (int8x16_t)xmmword_3D045F0));
    v29 = vandq_s8(vceqq_s32(*(int32x4_t *)&tehai14[8], v27), (int8x16_t)xmmword_3CFFD40);
    v30 = vaddvq_s32(v29);
    v29.n128_u32[0] = v28;
    v29.n128_u64[0] = vcnt_s8((int8x8_t)v29.n128_u64[0]).n64_u64[0];
    v29.n128_u16[0] = vaddlv_u8((uint8x8_t)v29.n128_u64[0]);
    v31 = v29.n128_u32[0];
    v29.n128_u32[0] = v30 & 0xF;
    v29.n128_u64[0] = vcnt_s8((int8x8_t)v29.n128_u64[0]).n64_u64[0];
    v29.n128_u16[0] = vaddlv_u8((uint8x8_t)v29.n128_u64[0]);
    v32 = v31 + v29.n128_u32[0];
    if (tehai14[12] == v26)
      ++v32;
    v23 += v32;
    if (tehai14[13] == v26)
      ++v23;
    if ((s32)v20 >= 1)
    {
      v49 = v20;
      v50 = (v9 + 32);
      do
      {
        v52 = *v50++;
        v51 = v52;
        if (v51 == Work->dora[v22])
          ++v23;
        --v49;
      }
      while (v49);
    }
    ++v22;
  }
  if (Work->players[v84]->reachIndex != -1)
  {
    v53 = 0;
    v54 = (v9 + 32);
    while (1)
    {
      v55 = Work;
      if (v53 >= v55->doraNum)
        return v23;
      v56 = v55->uraDora[v53];
      v57 = vdupq_n_s32(v56);
      v58 = vaddvq_s16(vandq_s8(vuzp1q_s16(vceqq_s32(*(int32x4_t *)tehai14, v57), vceqq_s32(*(int32x4_t *)&tehai14[4], v57)), (int8x16_t)xmmword_3D045F0));
      v59 = vandq_s8(vceqq_s32(*(int32x4_t *)&tehai14[8], v57), (int8x16_t)xmmword_3CFFD40);
      v60 = vaddvq_s32(v59);
      v59.n128_u32[0] = v58;
      v59.n128_u64[0] = vcnt_s8((int8x8_t)v59.n128_u64[0]).n64_u64[0];
      v59.n128_u16[0] = vaddlv_u8((uint8x8_t)v59.n128_u64[0]);
      v61 = v59.n128_u32[0];
      v59.n128_u32[0] = v60 & 0xF;
      v59.n128_u64[0] = vcnt_s8((int8x8_t)v59.n128_u64[0]).n64_u64[0];
      v59.n128_u16[0] = vaddlv_u8((uint8x8_t)v59.n128_u64[0]);
      v62 = v61 + v59.n128_u32[0];
      if (tehai14[12] == v56)
        ++v62;
      v23 += v62;
      if (tehai14[13] == v56)
        ++v23;
      if ((s32)v20 >= 1)
      {
        v79 = v20;
        v80 = v54;
        do
        {
          v82 = *v80++;
          v81 = v82;
          if (v81 == Work->uraDora[v53])
            ++v23;
          --v79;
        }
        while (v79);
      }
      ++v53;
    }
  }
  return v23;
}

// 0x1d06c60
static s32 CheckChanta(s32 playerIndex, NormalAnalysis_t *analysis, s32 **tehai14) {
  s64 v6;
  s32 *v7;
  s64 v8;
  s32 *v9;
  s64 toitsuNum;
  s64 v12;
  s32 v13;
  s64 i;
  s32 v15;
  Player_t *v17;
  s64 v18;
  s64 m_Items;
  s32 *v20;

  if (analysis->shuntsuNum >= 1)
  {
    v6 = 0;
    do
    {
      v7 = analysis->shuntsuHai[v6];
      if (GetMentsuType(v7) == 2)
        return 0;
    }
    while (++v6 < analysis->shuntsuNum);
  }
  if (analysis->kotsuNum >= 1)
  {
    v8 = 0;
    do
    {
      v9 = analysis->kotsuHai[v8];
      if (GetMentsuType(v9) == 2)
        return 0;
    }
    while (++v8 < analysis->kotsuNum);
  }
  toitsuNum = analysis->toitsuNum;
  if ((s32)toitsuNum >= 1)
  {
    v12 = 0;
    while (1)
    {
      v13 = analysis->toitsuHai[v12][0];
      if (v13 <= 26 && ((v13 % 9) & 0xFFFFFFF7) != 0)
        return 0;
      if (++v12 >= toitsuNum)
        goto LABEL_30;
    }
    for (i = 0; i < analysis->toitsuNum; ++i)
    {
      v15 = analysis->toitsuHai[i][0];
      if (v15 > 26)
        continue;
      if (((v15 % 9) & 0xFFFFFFF7) != 0)
        return 0;
    }
  }
LABEL_30:
  v17 = Work->players[playerIndex];
  if (v17->nakiNum >= 1)
  {
    v18 = 0;
    m_Items = v17->naki;
    do
    {
      v20 = *(s32 **)(*(u64 *)(m_Items + 8 * v18) + 24);
      if (GetMentsuType(v20) == 2)
        return 0;
    }
    while (++v18 < v17->nakiNum);
  }
  if (v17->menzen)
    return 2;
  else
    return 1;
}

// 0x1d0b6c0
static s32 CheckTsumo(s32 playerIndex, s32 tsumo) {
  bool v6;

  if (tsumo)
    v6 = Work->players[playerIndex]->menzen == 0;
  else
    v6 = 1;
  return !v6;
}

// 0x1d06ee0
static s32 CheckIttsu(s32 playerIndex, NormalAnalysis_t *analysis, s32 **tehai14) {
  u64 *v6;
  s32 *v7;
  Player_t *v9;
  s32 *v10;
  u64 *v11;
  s64 v12;
  u32 v13;
  s64 v14;
  void *v15;
  s32 v16;
  s32 v17;
  s64 v18;
  s32 v19;
  s32 v20;
  s32 nakiNum;
  s64 v22;
  u32 v23;
  void *v24;
  s64 v25;
  s64 v26;
  s64 v27;
  s32 v28;
  s32 v29;
  void *v30;
  s32 v31;
  s32 v32;
  s32 v33;
  s64 v35;

  v6 = NewSpecific(int__, 4u);
  v7 = NewSpecific(s32, 3u);
  v35 = v7;
  v9 = Work->players[playerIndex];
  *(u64 *)&v7[0] = 0;
  v10 = &v7[0];
  v7[2] = 0;
  if (analysis->shuntsuNum < 1)
  {
    v20 = 0;
    nakiNum = v9->nakiNum;
    if (nakiNum < 1)
      goto LABEL_23;
    goto LABEL_15;
  }
  v11 = v6 + 4;
  v12 = 4;
  do
  {
    v19 = *(u32 *)(*((u64 *)&analysis->shuntsuHai->obj.klass + v12) + 32);
    v13 = v19 / 9;
    if ((u32)(v19 / 9) >= 3)
      v13 = 3;
    v14 = v13;
    v15 = *((void **)&analysis->shuntsuHai->obj.klass + v12);
    v16 = v10[v14] + 1;
    *v11 = v15;
    v10[v14] = v16;
    v17 = v12 + 1;
    v18 = v12 - 3;
    ++v12;
    ++v11;
  }
  while (v18 < analysis->shuntsuNum);
  v20 = v17 - 4;
  nakiNum = v9->nakiNum;
  if (nakiNum >= 1)
  {
LABEL_15:
    v22 = 4;
    do
    {
      v27 = *((u64 *)&v9->naki->obj.klass + v22);
      if ((*(u8 *)(v27 + 19) & 0x10) != 0)
      {
        v28 = *(u32 *)(*(u64 *)(v27 + 24) + 32);
        v23 = v28 / 9;
        if ((u32)(v28 / 9) >= 3)
          v23 = 3;
        v24 = *(void **)(*((u64 *)&v9->naki->obj.klass + v22) + 24);
        ++v10[v23];
        v25 = v20;
        v6[v25 + 4] = v24;
        nakiNum = v9->nakiNum;
        ++v20;
      }
      v26 = v22 - 3;
      ++v22;
    }
    while (v26 < nakiNum);
  }
LABEL_23:
  if (*v10 > 2)
  {
    v29 = 0;
    if (v20 != 3)
      goto LABEL_30;
    goto LABEL_29;
  }
  if (*(s32 *)(v35 + 36) > 2)
  {
    v29 = 9;
    if (v20 != 3)
      goto LABEL_30;
LABEL_29:
    v30 = v6[4];
    v6[7] = v30;
    goto LABEL_30;
  }
  if (*(s32 *)(v35 + 40) < 3)
    return 0;
  v29 = 18;
  if (v20 == 3)
    goto LABEL_29;
LABEL_30:
  v31 = *(u32 *)(v6[4] + 32);
  if (v31 != v29 && *(u32 *)(v6[5] + 32) != v29 && *(u32 *)(v6[6] + 32) != v29 && *(u32 *)(v6[7] + 32) != v29)
  {
    return 0;
  }
  v32 = v29 + 3;
  if (v31 != v29 + 3 && *(u32 *)(v6[5] + 32) != v32 && *(u32 *)(v6[6] + 32) != v32 && *(u32 *)(v6[7] + 32) != v32)
  {
    return 0;
  }
  v33 = v29 + 6;
  if (v31 != v29 + 6 && *(u32 *)(v6[5] + 32) != v33 && *(u32 *)(v6[6] + 32) != v33 && *(u32 *)(v6[7] + 32) != v33)
  {
    return 0;
  }
  if (v9->menzen)
    return 2;
  else
    return 1;
}

// 0x1d07270
static s32 CheckSanshokujun(s32 playerIndex, NormalAnalysis_t *analysis, s32 **tehai14) {
  u64 *v6;
  Player_t *v8;
  s64 nakiNum;
  Naki_t *naki;
  s64 v11;
  s32 v12;
  s32 v13;
  s32 v14;
  s32 v15;
  s32 v16;
  Naki_t *v17;
  s64 v18;
  s64 v19;
  s64 v20;
  s64 v21;
  Naki_t *v22;
  s64 v23;
  s64 v24;
  s64 v25;
  Naki_t *v26;
  s32 v27;
  Naki_t *v28;
  s32 shuntsuNum;
  s32 **v30;
  s64 v31;
  s32 **v32;
  s32 *v33;
  s32 v34;
  s32 **v35;
  s64 v36;
  s32 **v37;
  s32 *v38;
  s32 v39;
  s64 v40;
  Naki_t *v41;
  s32 *v42;
  s64 v43;
  s32 v44;
  s32 v45;
  u64 v46;
  u32 v47;
  s32 v48;
  s32 v49;
  u64 v50;
  u32 v51;
  s32 v52;
  s32 v53;
  s32 v54;
  s32 v55;
  s32 v56;
  s64 v57;
  Naki_t *v58;
  s32 *hai;
  s64 v60;
  s32 v61;
  u32 v62;
  s32 v63;
  s32 v64;
  s32 v65;
  u32 v66;
  s32 v67;
  s32 v68;
  s32 v69;
  u32 v70;
  s32 v71;
  s32 v72;
  s32 v73;
  s32 v74;
  u32 v75;
  s32 v76;
  s32 v77;
  s32 v78;
  u32 v79;
  s32 v80;
  s32 v81;
  s32 v82;
  u32 v83;
  s32 v84;
  s32 v85;
  s32 v86;
  s32 v87;
  u32 v88;
  s32 v89;
  s32 v90;
  s32 v91;
  u32 v92;
  s32 v93;
  s32 v94;
  s32 v95;
  u32 v96;
  s32 v97;
  s32 v98;
  s32 v99;
  s32 v100;
  u32 v101;
  s32 v102;
  s32 v103;
  s32 v104;
  u32 v105;
  s32 v106;
  s32 v107;
  s32 v108;
  u32 v109;
  s32 v110;
  s32 v111;
  s32 v112;

  v6 = NewSpecific(int__, 4u);
  v8 = Work->players[playerIndex];
  nakiNum = (u32)v8->nakiNum;
  if ((s32)nakiNum < 1)
  {
    v12 = 0;
    goto LABEL_17;
  }
  naki = v8->naki;
  if ((u32)nakiNum >= 4)
  {
    v11 = nakiNum & 0x7FFFFFFC;
    v13 = 0;
    v14 = 0;
    v15 = 0;
    v16 = 0;
    v17 = &naki[3];
    v18 = (u32)nakiNum & 0xFFFFFFFC;
    do
    {
      v19 = *(v17 - 3);
      v20 = *(v17 - 2);
      v18 -= 4;
      v21 = *(v17 - 1);
      v22 = v17;
      v17 += 4;
      v13 += (*(u32 *)(v19 + 16) >> 28) & 1;
      v14 += (*(u32 *)(v20 + 16) >> 28) & 1;
      v15 += (*(u32 *)(v21 + 16) >> 28) & 1;
      v16 += ((u32)v22->type >> 28) & 1;
    }
    while (v18);
    v12 = v16 + v15 + v14 + v13;
    if (v11 == nakiNum)
      goto LABEL_17;
  }
  else
  {
    v11 = 0;
    v12 = 0;
  }
  v23 = ~v11;
  if ((nakiNum & 1) != 0)
  {
    v24 = (s64)naki + 8 * v11;
    v11 |= 1u;
    v12 += (*(u32 *)(*(u64 *)(v24 + 32) + 16) >> 28) & 1;
  }
  if (v23 + nakiNum)
  {
    v25 = nakiNum - v11;
    v26 = &naki[v11 + 1];
    do
    {
      v25 -= 2;
      v27 = (((u32)(*(v26 - 1))->type >> 28) & 1) + v12;
      v28 = v26;
      v26 += 2;
      v12 = (((u32)v28->type >> 28) & 1) + v27;
    }
    while (v25);
  }
LABEL_17:
  shuntsuNum = analysis->shuntsuNum;
  if (shuntsuNum + v12 == 4)
  {
    if (shuntsuNum < 1)
    {
      v39 = 0;
      if ((s32)nakiNum < 1)
        goto LABEL_68;
    }
    else
    {
      v35 = (v6 + 4);
      v36 = 0;
      v37 = (v6 + 4);
      do
      {
        v38 = analysis->shuntsuHai[v36];
        *v37++ = v38;
        ++v36;
        v35 = v37;
      }
      while (v36 < analysis->shuntsuNum);
      LODWORD(nakiNum) = v8->nakiNum;
      v39 = v36;
      if ((s32)nakiNum < 1)
        goto LABEL_68;
    }
    v57 = 0;
    do
    {
      v58 = v8->naki[v57];
      if ((v58->type & 0x10000000) != 0)
      {
        hai = v58->hai;
        v60 = v39;
        v6[v60 + 4] = hai;
        LODWORD(nakiNum) = v8->nakiNum;
        ++v39;
      }
      ++v57;
    }
    while (v57 < (s32)nakiNum);
LABEL_68:
    v61 = *(u32 *)(v6[4] + 32);
    v62 = v61 / 9;
    v63 = v61 % 9;
    if (v63 != *(u32 *)(v6[5] + 32) % 9 || v63 != *(u32 *)(v6[6] + 32) % 9)
      goto LABEL_183;
    v64 = *(u32 *)(v6[5] + 32);
    v65 = v62 >= 3 ? 3 : v62;
    v66 = v64 / 9;
    v67 = (u32)(v64 / 9) >= 3 ? 3 : v64 / 9;
    if (v65 == v67)
      goto LABEL_183;
    v68 = *(u32 *)(v6[6] + 32);
    v69 = v66 >= 3 ? 3 : v66;
    v70 = v68 / 9;
    v71 = (u32)(v68 / 9) >= 3 ? 3 : v68 / 9;
    if (v69 == v71)
      goto LABEL_183;
    v72 = v70 >= 3 ? 3 : v70;
    v73 = (u32)(*(u32 *)(v6[4] + 32) / 9) >= 3 ? 3 : *(u32 *)(v6[4] + 32) / 9;
    if (v72 == v73)
    {
LABEL_183:
      v74 = *(u32 *)(v6[4] + 32);
      v75 = v74 / 9;
      v76 = v74 % 9;
      if (v76 != *(u32 *)(v6[5] + 32) % 9 || v76 != *(u32 *)(v6[7] + 32) % 9)
        goto LABEL_190;
      v77 = *(u32 *)(v6[5] + 32);
      v78 = v75 >= 3 ? 3 : v75;
      v79 = v77 / 9;
      v80 = (u32)(v77 / 9) >= 3 ? 3 : v77 / 9;
      if (v78 == v80)
        goto LABEL_190;
      v81 = *(u32 *)(v6[7] + 32);
      v82 = v79 >= 3 ? 3 : v79;
      v83 = v81 / 9;
      v84 = (u32)(v81 / 9) >= 3 ? 3 : v81 / 9;
      if (v82 == v84)
        goto LABEL_190;
      v85 = v83 >= 3 ? 3 : v83;
      v86 = (u32)(*(u32 *)(v6[4] + 32) / 9) >= 3 ? 3 : *(u32 *)(v6[4] + 32) / 9;
      if (v85 == v86)
      {
LABEL_190:
        v87 = *(u32 *)(v6[4] + 32);
        v88 = v87 / 9;
        v89 = v87 % 9;
        if (v89 != *(u32 *)(v6[7] + 32) % 9 || v89 != *(u32 *)(v6[6] + 32) % 9)
          goto LABEL_191;
        v90 = *(u32 *)(v6[7] + 32);
        v91 = v88 >= 3 ? 3 : v88;
        v92 = v90 / 9;
        v93 = (u32)(v90 / 9) >= 3 ? 3 : v90 / 9;
        if (v91 == v93)
          goto LABEL_191;
        v94 = *(u32 *)(v6[6] + 32);
        v95 = v92 >= 3 ? 3 : v92;
        v96 = v94 / 9;
        v97 = (u32)(v94 / 9) >= 3 ? 3 : v94 / 9;
        if (v95 == v97)
          goto LABEL_191;
        v98 = v96 >= 3 ? 3 : v96;
        v99 = (u32)(*(u32 *)(v6[4] + 32) / 9) >= 3 ? 3 : *(u32 *)(v6[4] + 32) / 9;
        if (v98 == v99)
        {
LABEL_191:
          v100 = *(u32 *)(v6[7] + 32);
          v101 = v100 / 9;
          v102 = v100 % 9;
          if (v102 != *(u32 *)(v6[5] + 32) % 9 || v102 != *(u32 *)(v6[6] + 32) % 9)
            return 0;
          v103 = *(u32 *)(v6[5] + 32);
          v104 = v101 >= 3 ? 3 : v101;
          v105 = v103 / 9;
          v106 = (u32)(v103 / 9) >= 3 ? 3 : v103 / 9;
          if (v104 == v106)
            return 0;
          v107 = *(u32 *)(v6[6] + 32);
          v108 = v105 >= 3 ? 3 : v105;
          v109 = v107 / 9;
          v110 = (u32)(v107 / 9) >= 3 ? 3 : v107 / 9;
          if (v108 == v110)
            return 0;
          v111 = v109 >= 3 ? 3 : v109;
          v112 = (u32)(*(u32 *)(v6[7] + 32) / 9) >= 3 ? 3 : *(u32 *)(v6[7] + 32) / 9;
          if (v111 == v112)
            return 0;
        }
      }
    }
    goto LABEL_185;
  }
  if (shuntsuNum + v12 != 3)
    return 0;
  if (shuntsuNum < 1)
  {
    v34 = 0;
    if ((s32)nakiNum < 1)
      goto LABEL_34;
  }
  else
  {
    v30 = (v6 + 4);
    v31 = 0;
    v32 = (v6 + 4);
    do
    {
      v33 = analysis->shuntsuHai[v31];
      *v32++ = v33;
      ++v31;
      v30 = v32;
    }
    while (v31 < analysis->shuntsuNum);
    LODWORD(nakiNum) = v8->nakiNum;
    v34 = v31;
    if ((s32)nakiNum < 1)
      goto LABEL_34;
  }
  v40 = 0;
  do
  {
    v41 = v8->naki[v40];
    if ((v41->type & 0x10000000) != 0)
    {
      v42 = v41->hai;
      v43 = v34;
      v6[v43 + 4] = v42;
      LODWORD(nakiNum) = v8->nakiNum;
      ++v34;
    }
    ++v40;
  }
  while (v40 < (s32)nakiNum);
LABEL_34:
  v44 = *(u32 *)(v6[4] + 32);
  v45 = v44 / 9;
  if ((u32)(v44 / 9) >= 3)
    v45 = 3;
  v46 = 954437177 * *(s32 *)(v6[5] + 32);
  v47 = (v46 >> 63) + (SHIDWORD(v46) >> 1);
  if (v47 >= 3)
    v48 = 3;
  else
    v48 = (v46 >> 63) + (SHIDWORD(v46) >> 1);
  if (v45 == v48)
    return 0;
  v49 = v47 >= 3 ? 3 : v47;
  v50 = 954437177 * *(s32 *)(v6[6] + 32);
  v51 = (v50 >> 63) + (SHIDWORD(v50) >> 1);
  v52 = v51 >= 3 ? 3 : (v50 >> 63) + (SHIDWORD(v50) >> 1);
  if (v49 == v52)
    return 0;
  v53 = v51 >= 3 ? 3 : v51;
  v54 = *(u32 *)(v6[4] + 32);
  v55 = (u32)(v54 / 9) >= 3 ? 3 : v54 / 9;
  if (v53 == v55)
    return 0;
  v56 = v54 % 9;
  if (v56 != *(u32 *)(v6[5] + 32) % 9 || v56 != *(u32 *)(v6[6] + 32) % 9)
    return 0;
LABEL_185:
  if (v8->menzen)
    return 2;
  else
    return 1;
}

// 0x1d07c90
static s32 CheckSanshokupon(s32 playerIndex, NormalAnalysis_t *analysis, s32 **tehai14) {
  u64 *v6;
  Player_t *v8;
  s64 nakiNum;
  Naki_t *naki;
  s64 v11;
  s32 v12;
  s32 v13;
  s32 v14;
  s32 v15;
  s32 v16;
  Naki_t *v17;
  s64 v18;
  s64 v19;
  char type;
  s64 v21;
  Naki_t *v22;
  s64 v23;
  s64 v24;
  s64 *v25;
  s64 v26;
  s32 kotsuNum;
  s32 **v28;
  s64 v29;
  s32 **v30;
  s32 *v31;
  s32 v32;
  s32 **v33;
  s64 v34;
  s32 **v35;
  s32 *v36;
  s32 v37;
  s64 v38;
  Naki_t *v39;
  s32 *v40;
  s64 v41;
  s32 v42;
  u32 v43;
  s32 v44;
  s64 v45;
  Naki_t *v46;
  s32 *hai;
  s64 v48;
  s32 v49;
  u32 v50;
  s32 v51;
  s32 v52;
  s32 v53;
  s32 v54;
  s32 v55;
  u32 v56;
  s32 v57;
  s32 v58;
  s32 v59;
  s32 v60;
  u32 v61;
  s32 v62;
  s32 v63;
  s32 v64;
  s32 v66;
  u32 v67;
  s32 v68;
  s32 v69;
  s32 v70;

  v6 = NewSpecific(int__, 4u);
  v8 = Work->players[playerIndex];
  nakiNum = (u32)v8->nakiNum;
  if ((s32)nakiNum < 1)
  {
    v12 = 0;
    goto LABEL_24;
  }
  naki = v8->naki;
  if ((u32)nakiNum < 4)
  {
    v11 = 0;
    v12 = 0;
LABEL_20:
    v23 = (s64)naki + 8 * v11;
    v24 = nakiNum - v11;
    v25 = (v23 + 32);
    do
    {
      v26 = *v25++;
      if ((*(u8 *)(v26 + 16) & 0x6C) != 0)
        ++v12;
      --v24;
    }
    while (v24);
    goto LABEL_24;
  }
  v11 = nakiNum & 0x7FFFFFFC;
  v13 = 0;
  v14 = 0;
  v15 = 0;
  v16 = 0;
  v17 = &naki[3];
  v18 = (u32)nakiNum & 0xFFFFFFFC;
  do
  {
    v19 = *(v17 - 2);
    type = (*(v17 - 3))->type;
    v21 = *(v17 - 1);
    v22 = v17;
    v17 += 4;
    if ((type & 0x6C) != 0)
      ++v13;
    if ((*(u8 *)(v19 + 16) & 0x6C) != 0)
      ++v14;
    if ((*(u8 *)(v21 + 16) & 0x6C) != 0)
      ++v15;
    if ((v22->type & 0x6C) != 0)
      ++v16;
    v18 -= 4;
  }
  while (v18);
  v12 = v16 + v15 + v14 + v13;
  if (v11 != nakiNum)
    goto LABEL_20;
LABEL_24:
  kotsuNum = analysis->kotsuNum;
  if (kotsuNum + v12 == 4)
  {
    if (kotsuNum < 1)
    {
      v37 = 0;
      if ((s32)nakiNum < 1)
        goto LABEL_51;
    }
    else
    {
      v33 = (v6 + 4);
      v34 = 0;
      v35 = (v6 + 4);
      do
      {
        v36 = analysis->kotsuHai[v34];
        *v35++ = v36;
        ++v34;
        v33 = v35;
      }
      while (v34 < analysis->kotsuNum);
      LODWORD(nakiNum) = v8->nakiNum;
      v37 = v34;
      if ((s32)nakiNum < 1)
        goto LABEL_51;
    }
    v45 = 0;
    do
    {
      v46 = v8->naki[v45];
      if ((v46->type & 0x6C) != 0)
      {
        hai = v46->hai;
        v48 = v37;
        v6[v48 + 4] = hai;
        LODWORD(nakiNum) = v8->nakiNum;
        ++v37;
      }
      ++v45;
    }
    while (v45 < (s32)nakiNum);
LABEL_51:
    v49 = *(u32 *)(v6[4] + 32);
    v50 = v49 / 9;
    v51 = v49 % 9;
    if (v51 == *(u32 *)(v6[5] + 32) % 9 && v51 == *(u32 *)(v6[6] + 32) % 9)
    {
      if (v50 > 2)
        goto LABEL_68;
      v53 = *(u32 *)(v6[5] + 32);
      if ((u32)(v53 / 9) <= 2)
      {
        v54 = *(u32 *)(v6[6] + 32);
        if ((u32)(v54 / 9) < 3)
          return 2;
      }
    }
LABEL_68:
    v55 = *(u32 *)(v6[4] + 32);
    v56 = v55 / 9;
    v57 = v55 % 9;
    if (v57 != *(u32 *)(v6[5] + 32) % 9 || v57 != *(u32 *)(v6[7] + 32) % 9)
      goto LABEL_80;
    if (v56 > 2)
    {
LABEL_80:
      v60 = *(u32 *)(v6[4] + 32);
      v61 = v60 / 9;
      v62 = v60 % 9;
      if (v62 != *(u32 *)(v6[7] + 32) % 9 || v62 != *(u32 *)(v6[6] + 32) % 9)
        goto LABEL_93;
      if (v61 > 2)
        goto LABEL_93;
      v63 = *(u32 *)(v6[7] + 32);
      if ((u32)(v63 / 9) > 2)
        goto LABEL_93;
      v64 = *(u32 *)(v6[6] + 32);
      if ((u32)(v64 / 9) >= 3)
      {
LABEL_93:
        v66 = *(u32 *)(v6[7] + 32);
        v67 = v66 / 9;
        v68 = v66 % 9;
        if (v68 != *(u32 *)(v6[5] + 32) % 9 || v68 != *(u32 *)(v6[6] + 32) % 9)
          return 0;
        if (v67 > 2)
          return 0;
        v69 = *(u32 *)(v6[5] + 32);
        if ((u32)(v69 / 9) > 2)
          return 0;
        goto LABEL_101;
      }
      return 2;
    }
    v58 = *(u32 *)(v6[5] + 32);
    if ((u32)(v58 / 9) <= 2)
    {
      v59 = *(u32 *)(v6[7] + 32);
      if ((u32)(v59 / 9) < 3)
        return 2;
    }
    goto LABEL_80;
  }
  if (kotsuNum + v12 != 3)
    return 0;
  if (kotsuNum < 1)
  {
    v32 = 0;
    if ((s32)nakiNum < 1)
      goto LABEL_41;
  }
  else
  {
    v28 = (v6 + 4);
    v29 = 0;
    v30 = (v6 + 4);
    do
    {
      v31 = analysis->kotsuHai[v29];
      *v30++ = v31;
      ++v29;
      v28 = v30;
    }
    while (v29 < analysis->kotsuNum);
    LODWORD(nakiNum) = v8->nakiNum;
    v32 = v29;
    if ((s32)nakiNum < 1)
      goto LABEL_41;
  }
  v38 = 0;
  do
  {
    v39 = v8->naki[v38];
    if ((v39->type & 0x6C) != 0)
    {
      v40 = v39->hai;
      v41 = v32;
      v6[v41 + 4] = v40;
      LODWORD(nakiNum) = v8->nakiNum;
      ++v32;
    }
    ++v38;
  }
  while (v38 < (s32)nakiNum);
LABEL_41:
  v42 = *(u32 *)(v6[4] + 32);
  v43 = v42 / 9;
  v44 = v42 % 9;
  if (v44 != *(u32 *)(v6[5] + 32) % 9 || v44 != *(u32 *)(v6[6] + 32) % 9)
    return 0;
  if (v43 > 2)
    return 0;
  v52 = *(u32 *)(v6[5] + 32);
  if ((u32)(v52 / 9) > 2)
    return 0;
LABEL_101:
  v70 = *(u32 *)(v6[6] + 32);
  return 2 * ((u32)(v70 / 9) < 3);
}

// 0x1d08490
static s32 CheckToitoi(s32 playerIndex, NormalAnalysis_t *analysis, s32 **tehai14) {
  s64 v7;
  s32 v8;
  s64 v9;
  Player_t *v10;

  v7 = 0;
  v8 = 0;
  while (1)
  {
    v10 = Work->players[playerIndex];
    if (v7 >= v10->nakiNum)
      break;
    v10 = Work->players[playerIndex];
    v9 = (s64)v10->naki + 8 * v7++;
    if ((*(u8 *)(*(u64 *)(v9 + 32) + 16) & 0x6C) != 0)
      ++v8;
  }
  return 2 * (analysis->kotsuNum + v8 == 4);
}

// 0x1d08590
static s32 CheckSananko(s32 playerIndex, NormalAnalysis_t *analysis, s32 **tehai14, s32 tsumo, s32 agariHai) {
  s64 v11;
  s32 kotsuNum;
  s64 v13;
  s64 v14;
  s64 v15;
  s64 v16;
  s32 v17;
  s32 v18;
  s32 v19;
  s64 *v20;
  s64 v21;
  s32 v22;
  s64 v23;
  s32 v24;
  s32 v25;
  s32 v26;
  s64 v27;
  s64 v28;
  s64 v29;
  s64 *v30;
  s64 v31;
  s64 v32;
  s32 v33;
  s32 v34;
  s32 *v36;

  v11 = (s64)Work->players + 8 * playerIndex;
  kotsuNum = analysis->kotsuNum;
  v13 = *(u64 *)(v11 + 32);
  v14 = *(u32 *)(v13 + 72);
  if ((s32)v14 >= 1)
  {
    v15 = *(u64 *)(v13 + 80);
    if ((u32)v14 < 4)
    {
      v16 = 0;
LABEL_19:
      v27 = ~v16;
      if ((v14 & 1) != 0)
      {
        v28 = v15 + 8 * v16;
        v16 |= 1u;
        if (*(u32 *)(*(u64 *)(v28 + 32) + 16) == 4)
          ++kotsuNum;
      }
      if (v27 + v14)
      {
        v29 = v14 - v16;
        v30 = (v15 + 8 * v16 + 40);
        do
        {
          v31 = *(v30 - 1);
          v32 = *v30;
          v30 += 2;
          v33 = *(u32 *)(v32 + 16);
          if (*(u32 *)(v31 + 16) == 4)
            v34 = kotsuNum + 1;
          else
            v34 = kotsuNum;
          if (v33 == 4)
            kotsuNum = v34 + 1;
          else
            kotsuNum = v34;
          v29 -= 2;
        }
        while (v29);
      }
      goto LABEL_31;
    }
    v16 = v14 & 0x7FFFFFFC;
    v17 = 0;
    v18 = 0;
    v19 = 0;
    v20 = (v15 + 56);
    v21 = (u32)v14 & 0xFFFFFFFC;
    do
    {
      v22 = *(u32 *)(*(v20 - 3) + 16);
      v23 = *v20;
      v24 = *(u32 *)(*(v20 - 2) + 16);
      v25 = *(u32 *)(*(v20 - 1) + 16);
      v20 += 4;
      v26 = *(u32 *)(v23 + 16);
      if (v22 == 4)
        ++kotsuNum;
      if (v24 == 4)
        ++v17;
      if (v25 == 4)
        ++v18;
      if (v26 == 4)
        ++v19;
      v21 -= 4;
    }
    while (v21);
    kotsuNum += v19 + v18 + v17;
    if (v16 != v14)
      goto LABEL_19;
  }
LABEL_31:
  if (tsumo)
    return 2 * (kotsuNum > 2);
  if (kotsuNum == 4)
    return 2;
  if (kotsuNum != 3)
    return 0;
  if (analysis->shuntsuNum)
  {
    v36 = analysis->shuntsuHai[0];
    if (v36[0] == agariHai || v36[1] == agariHai || v36[2] == agariHai)
      return 2;
  }
  return 2 * (analysis->toitsuHai[0][0] == agariHai);
}

// 0x1d087d0
static s32 CheckSankantsu(s32 playerIndex, NormalAnalysis_t *analysis, s32 **tehai14) {
  Player_t *v6;
  s64 nakiNum;
  Naki_t *naki;
  s64 v9;
  s32 v10;
  s32 v12;
  s32 v13;
  s32 v14;
  s32 v15;
  Naki_t *v16;
  s64 v17;
  s64 v18;
  char type;
  s64 v20;
  Naki_t *v21;
  s64 v22;
  Naki_t *v23;
  s64 v24;

  v6 = Work->players[playerIndex];
  nakiNum = (u32)v6->nakiNum;
  if ((s32)nakiNum < 1)
    return 0;
  naki = v6->naki;
  if ((u32)nakiNum >= 4)
  {
    v9 = nakiNum & 0x7FFFFFFC;
    v12 = 0;
    v13 = 0;
    v14 = 0;
    v15 = 0;
    v16 = &naki[3];
    v17 = (u32)nakiNum & 0xFFFFFFFC;
    do
    {
      v18 = *(v16 - 2);
      type = (*(v16 - 3))->type;
      v20 = *(v16 - 1);
      v21 = v16;
      v16 += 4;
      if ((type & 0x4C) != 0)
        ++v12;
      if ((*(u8 *)(v18 + 16) & 0x4C) != 0)
        ++v13;
      if ((*(u8 *)(v20 + 16) & 0x4C) != 0)
        ++v14;
      if ((v21->type & 0x4C) != 0)
        ++v15;
      v17 -= 4;
    }
    while (v17);
    v10 = v15 + v14 + v13 + v12;
    if (v9 == nakiNum)
      return 2 * (v10 > 2);
  }
  else
  {
    v9 = 0;
    v10 = 0;
  }
  v22 = nakiNum - v9;
  v23 = &naki[v9];
  do
  {
    v24 = (s64)*v23++;
    if ((*(u8 *)(v24 + 16) & 0x4C) != 0)
      ++v10;
    --v22;
  }
  while (v22);
  return 2 * (v10 > 2);
}

// 0x1d0c080
static s32 CheckRyanpeiko(s32 playerIndex, NormalAnalysis_t *analysis, s32 **tehai14) {
  s32 **shuntsuHai;
  s32 v8;
  s32 v9;
  s32 v10;
  s32 result;
  s32 v12;

  if (!Work->players[playerIndex]->menzen || analysis->shuntsuNum != 4)
    return 0;
  shuntsuHai = analysis->shuntsuHai;
  v8 = shuntsuHai[0][0];
  v9 = shuntsuHai[1][0];
  v10 = shuntsuHai[2][0];
  if (v8 == v9 && v10 == shuntsuHai[3][0])
    return 3;
  result = 3;
  v12 = shuntsuHai[3][0];
  if (v8 != v10 || v9 != v12)
  {
    if (v8 == v12 && v9 == v10)
      return 3;
    else
      return 0;
  }
  return result;
}

// 0x1d08930
static s32 CheckHonitsu(s32 playerIndex, s32 *tehai14) {
  s32 v7;
  s32 menzen;

  v7 = tehai14[0];
  menzen = Work->players[playerIndex]->menzen;
  if ((u32)(v7 / 9 - 1) >= 2 && (u32)(tehai14[1] / 9 - 1) >= 2 && (u32)(tehai14[2] / 9 - 1) >= 2 && (u32)(tehai14[3] / 9 - 1) >= 2 && (u32)(tehai14[4] / 9 - 1) >= 2 && (u32)(tehai14[5] / 9 - 1) >= 2 && (u32)(tehai14[6] / 9 - 1) >= 2 && (u32)(tehai14[7] / 9 - 1) >= 2 && (u32)(tehai14[8] / 9 - 1) >= 2 && (u32)(tehai14[9] / 9 - 1) >= 2 && (u32)(tehai14[10] / 9 - 1) >= 2 && (u32)(tehai14[11] / 9 - 1) >= 2 && (u32)(tehai14[12] / 9 - 1) >= 2 && (u32)(tehai14[13] / 9 - 1) >= 2)
  {
    goto LABEL_133;
  }
  if (((tehai14[0] / 9) | 2) != 2 && ((tehai14[1] / 9) | 2) != 2 && ((tehai14[2] / 9) | 2) != 2 && ((tehai14[3] / 9) | 2) != 2 && ((tehai14[4] / 9) | 2) != 2 && ((tehai14[5] / 9) | 2) != 2 && ((tehai14[6] / 9) | 2) != 2 && ((tehai14[7] / 9) | 2) != 2 && ((tehai14[8] / 9) | 2) != 2 && ((tehai14[9] / 9) | 2) != 2 && ((tehai14[10] / 9) | 2) != 2 && ((tehai14[11] / 9) | 2) != 2 && ((tehai14[12] / 9) | 2) != 2 && ((tehai14[13] / 9) | 2) != 2)
  {
    goto LABEL_133;
  }
  if ((u32)(tehai14[0] / 9) < 2 || (u32)(tehai14[1] / 9) < 2 || (u32)(tehai14[2] / 9) < 2 || (u32)(tehai14[3] / 9) < 2 || (u32)(tehai14[4] / 9) < 2 || (u32)(tehai14[5] / 9) < 2 || (u32)(tehai14[6] / 9) < 2 || (u32)(tehai14[7] / 9) < 2 || (u32)(tehai14[8] / 9) < 2 || (u32)(tehai14[9] / 9) < 2 || (u32)(tehai14[10] / 9) < 2 || (u32)(tehai14[11] / 9) < 2 || (u32)(tehai14[12] / 9) < 2 || (u32)(tehai14[13] / 9) < 2)
  {
    return 0;
  }
LABEL_133:
  if (menzen)
    return 3;
  else
    return 2;
}

// 0x1d0c1a0
static s32 CheckJunchan(s32 playerIndex, NormalAnalysis_t *analysis, s32 **tehai14) {
  s64 v6;
  s32 *v7;
  s64 v8;
  s32 *v9;
  s64 toitsuNum;
  s64 v12;
  s32 v13;
  Player_t *v16;
  s64 v17;
  s64 m_Items;
  s32 *v19;

  if (analysis->shuntsuNum >= 1)
  {
    v6 = 0;
    do
    {
      v7 = analysis->shuntsuHai[v6];
      if (GetMentsuType(v7) == 2)
        return 0;
    }
    while (++v6 < analysis->shuntsuNum);
  }
  if (analysis->kotsuNum >= 1)
  {
    v8 = 0;
    do
    {
      v9 = analysis->kotsuHai[v8];
      if ((GetMentsuType(v9) | 2) == 2)
        return 0;
    }
    while (++v8 < analysis->kotsuNum);
  }
  toitsuNum = analysis->toitsuNum;
  if ((s32)toitsuNum >= 1)
  {
    v12 = 0;
    while (1)
    {
      v13 = analysis->toitsuHai[v12][0];
      if (v13 >= 27 || ((v13 % 9) & 0xFFFFFFF7) != 0)
        break;
      if (++v12 >= toitsuNum)
        goto LABEL_28;
    }
    return 0;
  }
LABEL_28:
  v16 = Work->players[playerIndex];
  if (v16->nakiNum >= 1)
  {
    v17 = 0;
    m_Items = v16->naki;
    do
    {
      v19 = *(s32 **)(*(u64 *)(m_Items + 8 * v17) + 24);
      if ((GetMentsuType(v19) | 2) == 2)
        return 0;
    }
    while (++v17 < v16->nakiNum);
  }
  if (v16->menzen)
    return 3;
  else
    return 2;
}

// 0x1d0c410
static s32 CheckShousangen(s32 playerIndex, NormalAnalysis_t *analysis, s32 **tehai14) {
  u32 v7;
  s64 v8;
  s32 v9;
  s32 v10;
  s32 v11;
  s64 kotsuNum;
  Player_t *v13;
  s32 **m_Items;
  s32 v15;
  s64 nakiNum;
  s64 v18;
  s32 v19;
  bool v20;

  v7 = analysis->toitsuHai[0][0] - 31;
  if (v7 > 2)
    return 0;
  v8 = 4 * (s32)v7;
  v9 = *(u32 *)((char *)&unk_3E62EB8 + v8);
  v10 = *(u32 *)((char *)&unk_3E62EC4 + v8);
  v11 = *(u32 *)((char *)&unk_3E62ED0 + v8);
  kotsuNum = (u32)analysis->kotsuNum;
  v13 = Work->players[playerIndex];
  if ((s32)kotsuNum >= 1)
  {
    m_Items = analysis->kotsuHai;
    do
    {
      v15 = (*m_Items)[0];
      switch (v15)
      {
        case 31:
          v11 = 1;
          break;
        case 32:
          v10 = 1;
          break;
        case 33:
          v9 = 1;
          break;
      }
      ++m_Items;
      --kotsuNum;
    }
    while (kotsuNum);
  }
  nakiNum = (u32)v13->nakiNum;
  if ((s32)nakiNum >= 1)
  {
    v18 = v13->naki;
    do
    {
      v19 = *(u32 *)(*(u64 *)(*(u64 *)v18 + 24) + 32);
      switch (v19)
      {
        case 31:
          v11 = 1;
          break;
        case 32:
          v10 = 1;
          break;
        case 33:
          v9 = 1;
          break;
      }
      v18 += 8;
      --nakiNum;
    }
    while (nakiNum);
  }
  if (v9)
    v20 = v10 == 0;
  else
    v20 = 1;
  if (v20 || v11 == 0)
    return 0;
  else
    return 2;
}

// 0x1d0c5d0
static s32 CheckHonroto(s32 playerIndex, s32 *tehai14) {
  s32 v4;
  s32 v6;
  s32 v7;
  s32 v9;
  s32 v10;
  s32 v12;
  s32 v14;
  s32 v16;
  s32 v19;
  s32 v21;
  s32 v23;
  s32 v25;
  s32 v27;
  s32 v29;

  v4 = tehai14[0];
  if (v4 <= 26 && ((v4 % 9) & 0xFFFFFFF7) != 0)
    return 0;
  v6 = tehai14[1];
  if (v6 <= 26 && ((v6 % 9) & 0xFFFFFFF7) != 0)
    return 0;
  v7 = tehai14[2];
  if (v7 <= 26 && ((v7 % 9) & 0xFFFFFFF7) != 0)
    return 0;
  v9 = tehai14[3];
  if (v9 <= 26 && ((v9 % 9) & 0xFFFFFFF7) != 0)
    return 0;
  v10 = tehai14[4];
  if (v10 <= 26 && ((v10 % 9) & 0xFFFFFFF7) != 0)
    return 0;
  v12 = tehai14[5];
  if (v12 <= 26 && ((v12 % 9) & 0xFFFFFFF7) != 0)
    return 0;
  v14 = tehai14[6];
  if (v14 <= 26 && ((v14 % 9) & 0xFFFFFFF7) != 0)
    return 0;
  v16 = tehai14[7];
  if (v16 <= 26 && ((v16 % 9) & 0xFFFFFFF7) != 0)
    return 0;
  v19 = tehai14[8];
  if (v19 <= 26 && ((v19 % 9) & 0xFFFFFFF7) != 0)
    return 0;
  v21 = tehai14[9];
  if (v21 <= 26 && ((v21 % 9) & 0xFFFFFFF7) != 0)
    return 0;
  v23 = tehai14[10];
  if (v23 <= 26 && ((v23 % 9) & 0xFFFFFFF7) != 0)
    return 0;
  v25 = tehai14[11];
  if (v25 <= 26 && ((v25 % 9) & 0xFFFFFFF7) != 0)
    return 0;
  v27 = tehai14[12];
  if (v27 <= 26 && ((v27 % 9) & 0xFFFFFFF7) != 0)
    return 0;
  v29 = tehai14[13];
  if (v29 <= 26 && ((v29 % 9) & 0xFFFFFFF7) != 0)
    return 0;
  return 2;
}

// 0x1d0cf10
static s32 CheckChinitsu(s32 playerIndex, s32 *tehai14) {
  s32 v7;
  s32 menzen;

  v7 = tehai14[0];
  menzen = Work->players[playerIndex]->menzen;
  if ((u32)(v7 + 8) <= 0x10 && (u32)(tehai14[1] + 8) <= 0x10 && (u32)(tehai14[2] + 8) <= 0x10 && (u32)(tehai14[3] + 8) <= 0x10 && (u32)(tehai14[4] + 8) <= 0x10 && (u32)(tehai14[5] + 8) <= 0x10 && (u32)(tehai14[6] + 8) <= 0x10 && (u32)(tehai14[7] + 8) <= 0x10 && (u32)(tehai14[8] + 8) <= 0x10 && (u32)(tehai14[9] + 8) <= 0x10 && (u32)(tehai14[10] + 8) <= 0x10 && (u32)(tehai14[11] + 8) <= 0x10 && (u32)(tehai14[12] + 8) <= 0x10 && (u32)(tehai14[13] + 8) < 0x11)
  {
    goto LABEL_136;
  }
  if ((u32)(tehai14[0] - 9) <= 8 && (u32)(tehai14[1] - 9) <= 8 && (u32)(tehai14[2] - 9) <= 8 && (u32)(tehai14[3] - 9) <= 8 && (u32)(tehai14[4] - 9) <= 8 && (u32)(tehai14[5] - 9) <= 8 && (u32)(tehai14[6] - 9) <= 8 && (u32)(tehai14[7] - 9) <= 8 && (u32)(tehai14[8] - 9) <= 8 && (u32)(tehai14[9] - 9) <= 8 && (u32)(tehai14[10] - 9) <= 8 && (u32)(tehai14[11] - 9) <= 8 && (u32)(tehai14[12] - 9) <= 8 && (u32)(tehai14[13] - 9) < 9)
  {
    goto LABEL_136;
  }
  if ((u32)(tehai14[0] - 18) > 8 || (u32)(tehai14[1] - 18) > 8 || (u32)(tehai14[2] - 18) > 8 || (u32)(tehai14[3] - 18) > 8 || (u32)(tehai14[4] - 18) > 8 || (u32)(tehai14[5] - 18) > 8 || (u32)(tehai14[6] - 18) > 8 || (u32)(tehai14[7] - 18) > 8 || (u32)(tehai14[8] - 18) > 8 || (u32)(tehai14[9] - 18) > 8 || (u32)(tehai14[10] - 18) > 8 || (u32)(tehai14[11] - 18) > 8 || (u32)(tehai14[12] - 18) > 8 || (u32)(tehai14[13] - 18) >= 9)
  {
    return 0;
  }
LABEL_136:
  if (menzen)
    return 6;
  else
    return 5;
}

// 0x1d0eee0
static s32 CheckDoubleReach(s32 playerIndex) {
  return 2 * (Work->players[playerIndex]->doubleReach != 0);
}

// 0x1d097f0
static s32 CheckRenho(s32 playerIndex, s32 tsumo) {
  if (tsumo)
    return 0;
  if (Work->players[playerIndex]->ichijunme)
    return 8;
  return 0;
}

// 0x1d098a0
static s32 CheckTenho(s32 playerIndex, s32 tsumo) {
  if (!tsumo)
    return 0;
  if (Work->oya != playerIndex)
    return 0;
  if (Work->players[playerIndex]->ichijunme)
    return 13;
  return 0;
}

// 0x1d09990
static s32 CheckChiho(s32 playerIndex, s32 tsumo) {
  if (!tsumo)
    return 0;
  if (Work->oya == playerIndex)
    return 0;
  if (Work->players[playerIndex]->ichijunme)
    return 13;
  return 0;
}

// 0x1d0d7b0
static s32 CheckSuanko(s32 playerIndex, NormalAnalysis_t *analysis, s32 **tehai14, s32 tsumo, s32 agariHai) {
  Player_t *v11;
  s32 kotsuNum;
  s64 nakiNum;
  Naki_t *naki;
  s64 v15;
  s32 v16;
  s32 v17;
  s32 v18;
  Naki_t *v19;
  s64 v20;
  s32 type;
  Naki_t *v22;
  s32 v23;
  s32 v24;
  s32 v25;
  s64 v26;
  s64 v27;
  s64 v28;
  Naki_t *v29;
  bool v30;
  Naki_t *v31;
  Naki_t *v32;

  v11 = Work->players[playerIndex];
  kotsuNum = analysis->kotsuNum;
  nakiNum = (u32)v11->nakiNum;
  if ((s32)nakiNum >= 1)
  {
    naki = v11->naki;
    if ((u32)nakiNum < 4)
    {
      v15 = 0;
LABEL_19:
      v26 = ~v15;
      if ((nakiNum & 1) != 0)
      {
        v27 = (s64)naki + 8 * v15;
        v15 |= 1u;
        if (*(u32 *)(*(u64 *)(v27 + 32) + 16) == 4)
          ++kotsuNum;
      }
      if (v26 + nakiNum)
      {
        v28 = nakiNum - v15;
        v29 = &naki[v15 + 1];
        do
        {
          v30 = (*(v29 - 1))->type == 4;
          v32 = v29;
          v29 += 2;
          v31 = v32;
          if (v30)
            ++kotsuNum;
          if (v31->type == 4)
            ++kotsuNum;
          v28 -= 2;
        }
        while (v28);
      }
      goto LABEL_29;
    }
    v15 = nakiNum & 0x7FFFFFFC;
    v16 = 0;
    v17 = 0;
    v18 = 0;
    v19 = &naki[3];
    v20 = (u32)nakiNum & 0xFFFFFFFC;
    do
    {
      type = (*(v19 - 3))->type;
      v22 = v19;
      v23 = (*(v19 - 2))->type;
      v24 = (*(v19 - 1))->type;
      v19 += 4;
      v25 = v22->type;
      if (type == 4)
        ++kotsuNum;
      if (v23 == 4)
        ++v16;
      if (v24 == 4)
        ++v17;
      if (v25 == 4)
        ++v18;
      v20 -= 4;
    }
    while (v20);
    kotsuNum += v18 + v17 + v16;
    if (v15 != nakiNum)
      goto LABEL_19;
  }
LABEL_29:
  if (!tsumo)
  {
    if (kotsuNum == 4 && analysis->toitsuHai[0][0] == agariHai)
      return 26;
    return 0;
  }
  if (kotsuNum != 4)
    return 0;
  if (analysis->toitsuHai[0][0] == agariHai)
    return 26;
  else
    return 13;
}

// 0x1d0d9a0
static s32 CheckSukantsu(s32 playerIndex, NormalAnalysis_t *analysis, s32 **tehai14) {
  Player_t *v6;
  s64 nakiNum;
  Naki_t *naki;
  s64 v9;
  s32 v10;
  s32 v12;
  s32 v13;
  s32 v14;
  s32 v15;
  Naki_t *v16;
  s64 v17;
  s64 v18;
  char type;
  s64 v20;
  Naki_t *v21;
  s64 v22;
  Naki_t *v23;
  s64 v24;

  v6 = Work->players[playerIndex];
  nakiNum = (u32)v6->nakiNum;
  if ((s32)nakiNum < 1)
    return 0;
  naki = v6->naki;
  if ((u32)nakiNum >= 4)
  {
    v9 = nakiNum & 0x7FFFFFFC;
    v12 = 0;
    v13 = 0;
    v14 = 0;
    v15 = 0;
    v16 = &naki[3];
    v17 = (u32)nakiNum & 0xFFFFFFFC;
    do
    {
      v18 = *(v16 - 2);
      type = (*(v16 - 3))->type;
      v20 = *(v16 - 1);
      v21 = v16;
      v16 += 4;
      if ((type & 0x4C) != 0)
        ++v12;
      if ((*(u8 *)(v18 + 16) & 0x4C) != 0)
        ++v13;
      if ((*(u8 *)(v20 + 16) & 0x4C) != 0)
        ++v14;
      if ((v21->type & 0x4C) != 0)
        ++v15;
      v17 -= 4;
    }
    while (v17);
    v10 = v15 + v14 + v13 + v12;
    if (v9 == nakiNum)
      goto LABEL_24;
  }
  else
  {
    v9 = 0;
    v10 = 0;
  }
  v22 = nakiNum - v9;
  v23 = &naki[v9];
  do
  {
    v24 = (s64)*v23++;
    if ((*(u8 *)(v24 + 16) & 0x4C) != 0)
      ++v10;
    --v22;
  }
  while (v22);
LABEL_24:
  if (v10 == 4)
    return 13;
  else
    return 0;
}

// 0x1d0db00
static s32 CheckDaisangen(s32 playerIndex, NormalAnalysis_t *analysis, s32 **tehai14) {
  s64 kotsuNum;
  Player_t *v8;
  s32 v9;
  s32 v10;
  s32 v11;
  s32 **m_Items;
  s32 v13;
  s64 nakiNum;
  s64 v15;
  s32 v16;
  bool v17;

  kotsuNum = (u32)analysis->kotsuNum;
  v8 = Work->players[playerIndex];
  if ((s32)kotsuNum < 1)
  {
    v11 = 0;
    v10 = 0;
    v9 = 0;
  }
  else
  {
    v9 = 0;
    v10 = 0;
    v11 = 0;
    m_Items = analysis->kotsuHai;
    do
    {
      v13 = (*m_Items)[0];
      switch (v13)
      {
        case 31:
          v9 = 1;
          break;
        case 32:
          v10 = 1;
          break;
        case 33:
          v11 = 1;
          break;
      }
      ++m_Items;
      --kotsuNum;
    }
    while (kotsuNum);
  }
  nakiNum = (u32)v8->nakiNum;
  if ((s32)nakiNum >= 1)
  {
    v15 = v8->naki;
    do
    {
      v16 = *(u32 *)(*(u64 *)(*(u64 *)v15 + 24) + 32);
      switch (v16)
      {
        case 31:
          v9 = 1;
          break;
        case 32:
          v10 = 1;
          break;
        case 33:
          v11 = 1;
          break;
      }
      v15 += 8;
      --nakiNum;
    }
    while (nakiNum);
  }
  if (v11)
    v17 = v10 == 0;
  else
    v17 = 1;
  if (v17 || v9 == 0)
    return 0;
  else
    return 13;
}

// 0x1d0dc70
static s32 CheckSushiho(s32 playerIndex, NormalAnalysis_t *analysis, s32 **tehai14) {
  Player_t *v7;
  s32 v8;
  s32 v9;
  s32 v10;
  s32 v11;
  char v12;
  s64 kotsuNum;
  s32 **m_Items;
  s32 v15;
  s64 nakiNum;
  s64 v17;
  s32 v18;

  v7 = Work->players[playerIndex];
  v8 = 0;
  v9 = 0;
  v10 = 0;
  v11 = 1;
  v12 = 1;
  switch (analysis->toitsuHai[0][0])
  {
    case 0x1B:
      goto LABEL_11;
    case 0x1C:
      v8 = 0;
      v9 = 0;
      v11 = 0;
      v10 = 1;
      kotsuNum = (u32)analysis->kotsuNum;
      if ((s32)kotsuNum < 1)
        goto LABEL_20;
      goto LABEL_12;
    case 0x1D:
      v8 = 0;
      v10 = 0;
      v11 = 0;
      v9 = 1;
LABEL_11:
      kotsuNum = (u32)analysis->kotsuNum;
      if ((s32)kotsuNum >= 1)
        goto LABEL_12;
      goto LABEL_20;
    case 0x1E:
      v9 = 0;
      v10 = 0;
      v11 = 0;
      v8 = 1;
      kotsuNum = (u32)analysis->kotsuNum;
      if ((s32)kotsuNum < 1)
        goto LABEL_20;
      goto LABEL_12;
    default:
      v8 = 0;
      v9 = 0;
      v10 = 0;
      v11 = 0;
      v12 = 0;
      kotsuNum = (u32)analysis->kotsuNum;
      if ((s32)kotsuNum >= 1)
      {
LABEL_12:
        m_Items = analysis->kotsuHai;
        while (2)
        {
          v15 = 1;
          switch ((*m_Items)[0])
          {
            case 0x1B:
              goto LABEL_15;
            case 0x1C:
              v10 = 1;
              goto LABEL_14;
            case 0x1D:
              v9 = 1;
              goto LABEL_14;
            case 0x1E:
              v8 = 1;
              goto LABEL_14;
            default:
LABEL_14:
              v15 = v11;
LABEL_15:
              ++m_Items;
              --kotsuNum;
              v11 = v15;
              if (kotsuNum)
                continue;
              goto LABEL_21;
          }
        }
      }
LABEL_20:
      v15 = v11;
LABEL_21:
      nakiNum = (u32)v7->nakiNum;
      if ((s32)nakiNum >= 1)
      {
        v17 = v7->naki;
        while (2)
        {
          v18 = 1;
          switch (*(u32 *)(*(u64 *)(*(u64 *)v17 + 24) + 32))
          {
            case 0x1B:
              goto LABEL_25;
            case 0x1C:
              v10 = 1;
              goto LABEL_24;
            case 0x1D:
              v9 = 1;
              goto LABEL_24;
            case 0x1E:
              v8 = 1;
              goto LABEL_24;
            default:
LABEL_24:
              v18 = v15;
LABEL_25:
              v17 += 8;
              --nakiNum;
              v15 = v18;
              if (nakiNum)
                continue;
              goto LABEL_30;
          }
        }
      }
      v18 = v15;
LABEL_30:
      if (!v18)
        v12 = 1;
      if ((v12 & 1) == 0 && v10 && v9)
      {
        if (v8)
          return 26;
      }
      else if (v18 && v10 && v9 && v8)
      {
        return 13;
      }
      return 0;
  }
}

// 0x1d0def0
static s32 CheckTsuiso(s32 playerIndex, s32 *tehai14) {
  s32 v4;

  v4 = tehai14[0];
  if (v4 < 27)
    return 0;
  if (tehai14[1] < 27)
    return 0;
  if (tehai14[2] < 27)
    return 0;
  if (tehai14[3] < 27)
    return 0;
  if (tehai14[4] < 27)
    return 0;
  if (tehai14[5] < 27)
    return 0;
  if (tehai14[6] < 27)
    return 0;
  if (tehai14[7] < 27)
    return 0;
  if (tehai14[8] < 27)
    return 0;
  if (tehai14[9] < 27)
    return 0;
  if (tehai14[10] < 27)
    return 0;
  if (tehai14[11] < 27)
    return 0;
  if (tehai14[12] < 27)
    return 0;
  if (tehai14[13] >= 27)
    return 13;
  return 0;
}

// 0x1d0e3a0
static s32 CheckChinroto(s32 playerIndex, s32 *tehai14) {
  s32 v4;
  s32 v5;
  s32 v6;
  s32 v7;
  s32 v8;
  s32 v9;
  s32 v10;
  s32 v11;
  s32 v12;
  s32 v13;
  s32 v14;
  s32 v15;
  s32 v16;
  s32 v17;
  s32 v18;

  v4 = tehai14[0];
  if (v4 < 27 && ((v4 % 9) & 0xFFFFFFF7) == 0)
  {
    v5 = tehai14[1];
    if (v5 <= 26 && ((v5 % 9) & 0xFFFFFFF7) == 0)
    {
      v6 = tehai14[2];
      if (v6 <= 26 && ((v6 % 9) & 0xFFFFFFF7) == 0)
      {
        v7 = tehai14[3];
        if (v7 <= 26 && ((v7 % 9) & 0xFFFFFFF7) == 0)
        {
          v8 = tehai14[4];
          if (v8 <= 26 && ((v8 % 9) & 0xFFFFFFF7) == 0)
          {
            v9 = tehai14[5];
            if (v9 <= 26 && ((v9 % 9) & 0xFFFFFFF7) == 0)
            {
              v10 = tehai14[6];
              if (v10 <= 26 && ((v10 % 9) & 0xFFFFFFF7) == 0)
              {
                v11 = tehai14[7];
                if (v11 <= 26 && ((v11 % 9) & 0xFFFFFFF7) == 0)
                {
                  v12 = tehai14[8];
                  if (v12 <= 26 && ((v12 % 9) & 0xFFFFFFF7) == 0)
                  {
                    v13 = tehai14[9];
                    if (v13 <= 26 && ((v13 % 9) & 0xFFFFFFF7) == 0)
                    {
                      v14 = tehai14[10];
                      if (v14 <= 26 && ((v14 % 9) & 0xFFFFFFF7) == 0)
                      {
                        v15 = tehai14[11];
                        if (v15 <= 26 && ((v15 % 9) & 0xFFFFFFF7) == 0)
                        {
                          v16 = tehai14[12];
                          if (v16 <= 26 && ((v16 % 9) & 0xFFFFFFF7) == 0)
                          {
                            v17 = tehai14[13];
                            if (v17 <= 26)
                            {
                              v18 = v17 % 9;
                              goto LABEL_86;
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
        }
      }
    }
  }
  return 0;
LABEL_86:
  if ((v18 & 0xFFFFFFF7) != 0)
    return 0;
  else
    return 13;
}

// 0x1d0e9c0
static s32 CheckRyuiso(s32 playerIndex, NormalAnalysis_t *analysis, s32 *tehai14) {
  u32 v4;
  s32 result;
  u32 v7;
  u32 v8;
  u32 v9;
  u32 v10;
  u32 v11;
  u32 v12;
  u32 v13;
  u32 v14;
  u32 v15;
  u32 v16;
  u32 v17;
  u32 v18;
  u32 v19;

  v4 = tehai14[0];
  result = 0;
  if (v4 <= 0x20 && ((1 << v4) & 0x102B80000LL) != 0)
  {
    v7 = tehai14[1];
    if (v7 <= 0x20 && ((1 << v7) & 0x102B80000LL) != 0)
    {
      v8 = tehai14[2];
      result = 0;
      if (v8 <= 0x20 && ((1 << v8) & 0x102B80000LL) != 0)
      {
        v9 = tehai14[3];
        result = 0;
        if (v9 <= 0x20 && ((1 << v9) & 0x102B80000LL) != 0)
        {
          v10 = tehai14[4];
          result = 0;
          if (v10 <= 0x20 && ((1 << v10) & 0x102B80000LL) != 0)
          {
            v11 = tehai14[5];
            result = 0;
            if (v11 <= 0x20 && ((1 << v11) & 0x102B80000LL) != 0)
            {
              v12 = tehai14[6];
              result = 0;
              if (v12 <= 0x20 && ((1 << v12) & 0x102B80000LL) != 0)
              {
                v13 = tehai14[7];
                result = 0;
                if (v13 <= 0x20 && ((1 << v13) & 0x102B80000LL) != 0)
                {
                  v14 = tehai14[8];
                  result = 0;
                  if (v14 <= 0x20 && ((1 << v14) & 0x102B80000LL) != 0)
                  {
                    v15 = tehai14[9];
                    result = 0;
                    if (v15 <= 0x20 && ((1 << v15) & 0x102B80000LL) != 0)
                    {
                      v16 = tehai14[10];
                      result = 0;
                      if (v16 <= 0x20 && ((1 << v16) & 0x102B80000LL) != 0)
                      {
                        v17 = tehai14[11];
                        result = 0;
                        if (v17 <= 0x20 && ((1 << v17) & 0x102B80000LL) != 0)
                        {
                          v18 = tehai14[12];
                          result = 0;
                          if (v18 <= 0x20 && ((1 << v18) & 0x102B80000LL) != 0)
                          {
                            v19 = tehai14[13] - 19;
                            if (v19 > 0xD)
                              return 0;
                            else
                              return dword_3E62EDC[v19];
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
      }
    }
  }
  return result;
}

// 0x1d0eb90
static s32 CheckChuren(s32 playerIndex, NormalAnalysis_t *analysis, s32 **tehai14, s32 agariHai) {
  u32 *v7;
  Player_t *v9;
  s32 *tehai34;

  v7 = NewSpecific(s32, 0x22u);
  v9 = Work->players[playerIndex];
  if (!v9->menzen)
    return 0;
  tehai34 = v9->tehai34;
  v7[8] = tehai34[0];
  v7[9] = tehai34[1];
  v7[10] = tehai34[2];
  v7[11] = tehai34[3];
  v7[12] = tehai34[4];
  v7[13] = tehai34[5];
  v7[14] = tehai34[6];
  v7[15] = tehai34[7];
  v7[16] = tehai34[8];
  v7[17] = tehai34[9];
  v7[18] = tehai34[10];
  v7[19] = tehai34[11];
  v7[20] = tehai34[12];
  v7[21] = tehai34[13];
  v7[22] = tehai34[14];
  v7[23] = tehai34[15];
  v7[24] = tehai34[16];
  v7[25] = tehai34[17];
  v7[26] = tehai34[18];
  v7[27] = tehai34[19];
  v7[28] = tehai34[20];
  v7[29] = tehai34[21];
  v7[30] = tehai34[22];
  v7[31] = tehai34[23];
  v7[32] = tehai34[24];
  v7[33] = tehai34[25];
  v7[34] = tehai34[26];
  v7[35] = tehai34[27];
  v7[36] = tehai34[28];
  v7[37] = tehai34[29];
  v7[38] = tehai34[30];
  v7[39] = tehai34[31];
  v7[40] = tehai34[32];
  v7[41] = tehai34[33];
  --v7[agariHai + 8];
  if (v7[8] != 3 || v7[9] != 1 || v7[10] != 1 || v7[11] != 1 || v7[12] != 1 || v7[13] != 1 || v7[14] != 1 || v7[15] != 1 || v7[16] != 3)
  {
    goto LABEL_32;
  }
  if (tehai34[0] < 3 || tehai34[1] < 1)
    return 0;
  if (tehai34[2] >= 1 && tehai34[3] >= 1 && tehai34[4] >= 1 && tehai34[5] >= 1 && tehai34[6] >= 1 && tehai34[7] >= 1 && tehai34[8] > 2)
  {
    return 26;
  }
LABEL_32:
  if (tehai34[0] < 3 || tehai34[1] < 1 || tehai34[2] < 1 || tehai34[3] < 1 || tehai34[4] < 1 || tehai34[5] < 1 || tehai34[6] < 1 || tehai34[7] < 1 || tehai34[8] <= 2)
  {
    return 0;
  }
  return 13;
}

// 0x1d05d30
static TehaiAnalysis_t *SetBestAnalysisEx(s32 playerIndex, TehaiAnalysis_t *pAnalysis) {
  s32 v9;

  AnalyzeTehaiNormal(playerIndex);
  AnalyzeTehaiChitoi(playerIndex);
  AnalyzeTehaiKokushi(playerIndex);
  return SetBestAnalysisSub(v9, pAnalysis);
}

// 0x1d03760
static s32 CalcHaiValue(s32 hai, s32 playerIndex) {
  s32 *tehai34;
  s32 v7;
  char *v8;
  s64 i;
  s64 v10;
  u32 v12;
  u32 v13;
  bool v15;

  tehai34 = Work->players[playerIndex]->tehai34;
  if (hai >= 27)
    v7 = -2;
  else
    v7 = 0;
  v8 = (char *)tehai34 + 4 * hai;
  if ((u32)hai <= 0x1A && ((1 << hai) & 0x4060301) != 0)
  {
    --v7;
  }
  else if (hai > 26)
  {
    goto LABEL_17;
  }
  if (hai % 9 != 8)
  {
    if (hai % 9 || !*((u32 *)v8 + 11))
      goto LABEL_17;
    goto LABEL_16;
  }
  if (*((u32 *)&tehai34->bounds + hai + 1))
LABEL_16:
    v7 -= 3;
LABEL_17:
  for (i = 0; ; ++i)
  {
    if (i >= Work->doraNum)
      break;
    v10 = (s64)Work->dora + 4 * i;
    if (*(u32 *)(v10 + 32) == hai)
      v7 += 4;
  }
  v12 = hai - 1;
  if (hai < 1 || *((s32 *)v8 + 8) > 1)
    goto LABEL_38;
  if (tehai34[v12])
  {
    v13 = v12 / 9;
    v15 = hai < 27 && v13 == hai / 9u;
    if ((u32)hai < 0x1A || v15)
      goto LABEL_38;
  }
  else if ((u32)hai <= 0x19)
  {
LABEL_38:
    v7 += 2;
  }
  return v7;
}

// 0x1d03290
static s32 CalcHaiValueTanki(s32 hai, s32 playerIndex) {
  NormalAnalysis_t *normalAnalysis;
  s32 *v7;
  s64 v8;
  s32 v9;
  s32 v10;
  s64 v11;
  u32 *v12;
  s64 m_Items;
  s32 v14;
  s32 v15;
  s32 v16;
  u32 *v17;
  u32 *v18;
  s32 shuntsuNum;
  s32 **shuntsuHai;
  u32 v21;
  s32 v22;
  u32 *v23;
  s32 v24;
  s32 v25;
  s64 v26;
  s32 **v27;
  s32 v28;
  u32 *v29;
  bool v30;
  bool v31;
  bool v32;
  s64 v33;
  s32 **v34;
  s32 v35;
  s64 i;
  s32 v38;
  s32 v40;
  s64 j;

  normalAnalysis = Work->players[playerIndex]->analysis->normalAnalysis;
  v7 = NewSpecific(s32, 0x22u);
  v8 = v7;
  *(u64 *)&v7[32] = 0;
  *(_OWORD *)&v7[0] = 0u;
  *(_OWORD *)&v7[4] = 0u;
  *(_OWORD *)&v7[8] = 0u;
  *(_OWORD *)&v7[12] = 0u;
  *(_OWORD *)&v7[16] = 0u;
  *(_OWORD *)&v7[28] = 0u;
  *(_OWORD *)&v7[20] = 0u;
  *(_OWORD *)&v7[24] = 0u;
  *(u32 *)((s64)&v7[0] + 4 * hai) = 1;
  if (hai <= 26)
  {
    if (normalAnalysis->kotsuNum >= 1)
    {
      v9 = hai - 1;
      v10 = hai - 2;
      v11 = 0;
      v12 = ((s64)&v7[0] + 4 * (hai - 2));
      m_Items = normalAnalysis->kotsuHai;
      v14 = (hai - 1) % 9;
      v15 = (hai + 1) % 9;
      do
      {
        v16 = *(u32 *)(*(u64 *)(m_Items + 8 * v11) + 32);
        if (v16 / 9 == hai / 9)
        {
          if (v16 == v9)
          {
            v17 = (v8 + 32 + 4 * (hai + 1));
            if (v14)
            {
              v17 = (v8 + 32 + 4 * v10);
              if (v14 != 7)
              {
                v17 = (v8 + 32 + 4 * (hai + 1));
                *v12 = 1;
              }
            }
            *v17 = 1;
          }
          if (v16 == hai + 1)
          {
            v18 = (v8 + 32 + 4 * (hai + 2));
            if (v15 != 1)
            {
              v18 = (v8 + 32 + 4 * v9);
              if (v15 != 8)
              {
                *(u32 *)(v8 + 32 + 4 * (hai + 2)) = 1;
                v18 = (v8 + 32 + 4 * v9);
              }
            }
          }
          else
          {
            v18 = (v8 + 32 + 4 * v9);
            if (v16 != v10)
            {
              v18 = (v8 + 32 + 4 * (hai + 1));
              if (v16 != hai + 2)
                goto LABEL_9;
            }
          }
          *v18 = 1;
        }
LABEL_9:
        ++v11;
      }
      while (v11 < normalAnalysis->kotsuNum);
    }
    shuntsuNum = normalAnalysis->shuntsuNum;
    if (shuntsuNum >= 1)
    {
      shuntsuHai = normalAnalysis->shuntsuHai;
      v21 = hai - 3;
      v22 = hai / 9;
      v23 = (v8 + 32 + 4 * (hai + 3));
      v24 = (hai + 3) / 9;
      v25 = hai + 1;
      if (hai - 3 < 0)
      {
        if (v24 == v22)
        {
          v33 = 0;
          v34 = shuntsuHai;
          do
          {
            v35 = v34[v33][0];
            if (v35 / 9 == v22 && (v35 == hai || v35 == v25))
              *v23 = 1;
            ++v33;
          }
          while (v33 < normalAnalysis->shuntsuNum);
        }
        else
        {
          for (i = 0; i < shuntsuNum; ++i)
          {
            v38 = shuntsuHai[i][0];
            if (v38 / 9 == v22 && v38 == v25)
            {
              *v23 = 1;
              shuntsuNum = normalAnalysis->shuntsuNum;
            }
          }
        }
      }
      else
      {
        v26 = 0;
        v27 = shuntsuHai;
        do
        {
          v28 = v27[v26][0];
          if (v28 / 9 == v22)
          {
            v29 = (v8 + 32 + 4 * v21);
            v30 = v21 / 9 == v22 && v28 == hai - 2;
            v31 = v30;
            if (v28 == v21 || (v29 = (v8 + 32 + 4 * v21), v31) || ((v29 = (v8 + 32 + 4 * (hai + 3)), v24 == v22) ? (v32 = v28 == hai) : (v32 = 0), v32 || (v29 = (v8 + 32 + 4 * (hai + 3)), v28 == v25)))
            {
              *v29 = 1;
            }
          }
          ++v26;
        }
        while (v26 < normalAnalysis->shuntsuNum);
      }
    }
  }
  v40 = 0;
  for (j = 32; j != 168; j += 4)
  {
    if (*(u32 *)(v8 + j) == 1)
    {
      v40 = v40
          - Work->visibleHai[hai]
          - Work->players[playerIndex]->tehai34[hai]
          + 4;
    }
  }
  if (hai >= 27)
  {
    v40 *= 2;
    if (v40 < 4)
      return v40;
    goto LABEL_73;
  }
  if (((hai % 9) | 8) == 8)
    v40 = 3 * v40 / 2;
  if (v40 >= 4)
  {
LABEL_73:
    Work->players[playerIndex]->analysis->fAllowReach = 1;
  }
  return v40;
}

// 0x1d03940
static s32 CalcHaiValueChitoi(s32 hai, s32 playerIndex) {
  Player_t *v7;
  s32 v8;
  s64 sutehaiIndex;
  s32 *m_Items;
  s32 v11;
  s32 v12;
  s32 v13;
  s32 v15;
  s64 v16;
  s32 v17;
  s64 v18;
  Work_t *v19;

  v7 = Work->players[playerIndex];
  v8 = v7->tehai34[hai];
  if (v8 <= 2)
  {
    sutehaiIndex = (u32)v7->sutehaiIndex;
    if ((s32)sutehaiIndex >= 1)
    {
      m_Items = v7->sutehai;
      do
      {
        v11 = *m_Items++;
        if (v11 == hai)
          return 0;
      }
      while (--sutehaiIndex);
    }
    v12 = v8 + Work->visibleHai[hai];
    if (v12 == 4)
      return 0;
    v15 = 2 * v12;
    v16 = 0;
    if (((hai % 9) & 0xFFFFFFF7) != 0)
      v17 = 8;
    else
      v17 = 9;
    if (hai > 26)
      v17 = 10;
    v13 = v17 - v15;
    while (1)
    {
      v19 = Work;
      if (v16 >= v19->doraNum)
        break;
      v19 = Work;
      v18 = (s64)v19->dora + 4 * v16++;
      if (*(u32 *)(v18 + 32) == hai)
        v13 += 4;
    }
    return v13;
  }
  return 0;
}

// 0x1d04ad0
static s32 CheckYakunashi(Agari_t *agari) {
  return agari->yakuNum == agari->yaku[11];
}

// 0x1d12d70
static void PrintNode(AnalyzeNode_t *node) {
  ;
}

// 0x1d12d80
static void PrintTree(AnalyzeNode_t *root) {

}

// 0x1d12de0
static void StartCutin(s32 playerIndex, s32 msgID, s32 nextPhase, s32 flag, s32 hai) {
  Player_t *v13;
  Work_t *v14;
  s32 v15;
  bool v16;
  Work_t *v17;
  s32 *reachShanten;
  Work_t *v21;
  bool v22;
  Work_t *v25;

  if (MJN_GUIDEHELP_FLAG)
  {
    ButtonGuideDispSet("MJN02", 0, 90);
    ButtonGuideDispOff();
    MJN_GUIDEHELP_FLAG = 0;
  }
  v13 = Work->players[playerIndex];
  if (flag != 0x2000)
  {
    Work->phase = 10;
  }
  v14 = Work;
  v14->nextPhase = nextPhase;
  v14->msgFlag = flag;
  v14->msgHai = hai;
  v14->msgPlayer = playerIndex;
  v14->waitCount = 0;
  v15 = 2;
  switch (msgID)
  {
    case 0:
      goto LABEL_34;
    case 1:
      v15 = 29;
      if (!playerIndex)
        goto LABEL_35;
      goto LABEL_68;
    case 3:
      v15 = 1;
      if (!playerIndex)
        goto LABEL_35;
      goto LABEL_68;
    case 4:
      v15 = 25;
      if (!playerIndex)
        goto LABEL_35;
      goto LABEL_68;
    case 5:
      v15 = 26;
LABEL_34:
      if (!playerIndex)
        goto LABEL_35;
      goto LABEL_68;
    case 6:
      v15 = 27;
      if (playerIndex)
        goto LABEL_68;
LABEL_35:
      v16 = evtBitCheck(2354);
      if (v16)
        goto LABEL_36;
      goto LABEL_68;
    case 7:
      if (playerIndex)
      {
        v15 = 28;
        goto LABEL_68;
      }
      v21 = Work;
      v21->reachShantenIndex = 0;
      reachShanten = v21->reachShanten;
      reachShanten[0] = -2;
      reachShanten[1] = -2;
      reachShanten[2] = -2;
      reachShanten[3] = -2;
      reachShanten[4] = -2;
      reachShanten[5] = -2;
      reachShanten[6] = -2;
      reachShanten[7] = -2;
      reachShanten[8] = -2;
      reachShanten[9] = -2;
      reachShanten[10] = -2;
      goto LABEL_64;
LABEL_65:
      reachShanten[12] = -2;
      goto LABEL_67;
LABEL_64:
      reachShanten[11] = -2;
      goto LABEL_65;
LABEL_67:
      reachShanten[13] = -2;
      v15 = 28;
      v22 = evtBitCheck(2354);
      if (v22)
      {
LABEL_36:
        v17 = Work;
        v17->msgStep = 1;
        v17->waitCount = 0;
        return;
      }
LABEL_68:
      v25 = Work;
      v25->msgReqDevilID = v13->devilID;
      v25->msgReqType = v15;
      v25->msgStep = 0;
      if (sBtlExt_ChkMes())
      {
        sBtlExt_EndMes();
      }
      return;
    default:
      if (v14->fDrawAgari == 2)
      {
        v14 = Work;
        v14->phase = 8;
        return;
      }
      dds3SetQuake(15, 0x14u);
      Work->phase = nextPhase;
      return;
  }
}

// 0x1d13450
static void ManageCutin(void) {
  TehaiAnalysis_t *v1;
  s32 *v3;
  s32 msgStep;
  Player_t *v7;
  void *Instance;
  void *v9;
  Work_t *v11;
  s32 msgReqDevilID;
  s32 msgReqType;
  Work_t *v14;
  s32 tehaiNum;
  s32 *tehai14;
  s64 v17;
  s64 v18;
  s64 v19;
  s32 v23;
  s32 v27;
  u32 v28;
  s64 v29;
  s64 m_Items;
  s64 v31;
  Work_t *v32;
  Work_t *v33;
  s32 v34;
  bool v35;
  Work_t *v39;
  s32 msgFlag;
  u32 v41;
  u32 v42;
  u32 v43;
  s64 i;
  s32 attentionFlag;
  s32 *Matihai;
  s32 v47;
  Work_t *v49;
  s64 v50;

  v1 = Allocate(TehaiAnalysis_t);
  _ctor(v1, 0);
  v3 = NewSpecific(s32, 0xEu);
  msgStep = Work->msgStep;
  if (msgStep != 1)
    goto LABEL_5;
  v7 = Work->players[0];
  if (Work->msgFlag != 2)
    goto LABEL_49;
  if (!Work->msgPlayer)
  {
    tehaiNum = v7->tehaiNum;
    if (Work->reachShantenIndex >= tehaiNum)
      goto LABEL_49;
    tehai14 = v7->tehai14;
    if (tehaiNum >= 1)
    {
      v17 = 0;
      do
      {
        v18 = v17++;
        *(u32 *)((s64)&v3[0] + v18 * 4) = tehai14[v18];
      }
      while (v17 < v7->tehaiNum);
    }
    v19 = tehai14[Work->reachShantenIndex];
    --v7->tehai34[v19];
    --v7->tehaiNum;
    SetTehai14(0);
    AnalyzeTehaiNormal(0);
    AnalyzeTehaiChitoi(0);
    AnalyzeTehaiKokushi(0);
    SetBestAnalysisSub(v23, v1);
    Work->reachShanten[Work->reachShantenIndex] = v1->shanten;
    v27 = CheckFuriten(0);
    if (Work->reachShanten[Work->reachShantenIndex])
    {
LABEL_43:
      ++v7->tehai34[v19];
      v28 = v7->tehaiNum;
      v7->tehaiNum = v28 + 1;
      if (v28 <= 0x7FFFFFFE)
      {
        v29 = 0;
        m_Items = v7->tehai14;
        do
        {
          v31 = 4 * v29++;
          *(u32 *)(m_Items + v31) = *(u32 *)((s64)&v3[0] + v31);
        }
        while (v29 < v7->tehaiNum);
      }
      ++Work->reachShantenIndex;
LABEL_61:
      v33 = Work;
      v34 = v33->waitCount + 1;
      v35 = v33->waitCount - 149 < 0;
      v33->waitCount = v34;
      if (v35 != __OFSUB__(v34, 150))
        return;
      v33 = Work;
      v33->phase = v33->nextPhase;
      sBtlExt_EndMes();
      v39 = Work;
      msgFlag = v39->msgFlag;
      if (msgFlag == 4)
      {
        v39 = Work;
        v39->fKokushiCheck = 1;
        return;
      }
      if (msgFlag == 8)
      {
        if (!v41)
        {
          v39 = Work;
        }
        v39->fChankanCheck = 1;
        return;
      }
      if (!v41)
      {
        v39 = Work;
        msgFlag = v39->msgFlag;
      }
      if (msgFlag == 64)
      {
        if (!v42)
        {
          v39 = Work;
        }
        mjnAfterConfirmationKan(v39->msgPlayer);
      }
      else
      {
        if (!v42)
        {
          v39 = Work;
          msgFlag = v39->msgFlag;
        }
        if (msgFlag == 0x2000)
        {
          if (!v43)
          {
            v39 = Work;
          }
          *(u64 *)&v39->waitCount = 0x200000000LL;
        }
        else
        {
          if (!v43)
          {
            v39 = Work;
            msgFlag = v39->msgFlag;
          }
          if (msgFlag == 2)
          {
            v39 = Work;
            if (!v39->msgPlayer)
            {
              v39 = Work;
              v39->players[0]->flag |= 2u;
              mjnTehaiCursorSet();
            }
          }
        }
      }
      return;
    }
    for (i = 8; ; ++i)
    {
      if (i - 8 >= SLODWORD(Work->reaceMatihai[Work->reachShantenIndex]->Matihai->max_length))
        goto LABEL_43;
      v47 = CheckRon_Reach(i - 8, v7);
      if (v47 == 16)
      {
        v49 = Work;
        v50 = v49->reaceMatihai;
        *(u32 *)(*(u64 *)(*(u64 *)(v50 + 8 * v49->reachShantenIndex) + 16) + 4 * i) = 1;
        Matihai = *(s32 **)(*(u64 *)(v50 + 8 * v49->reachShantenIndex) + 24);
        if (v27 == 1)
        {
          if (v49->attentionFlag != 2)
            goto LABEL_110;
          goto LABEL_9000;
          if (Work->attentionFlag != 2)
          {
LABEL_110:
            attentionFlag = 1;
            goto LABEL_94;
          }
LABEL_9000:
        }
        attentionFlag = Work->attentionFlag;
      }
      else
      {
        attentionFlag = 0;
        Matihai = Work->reaceMatihai[Work->reachShantenIndex]->Matihai;
      }
LABEL_94:
      *((u32 *)&Matihai->obj.klass + i) = attentionFlag;
    }
  }
LABEL_49:
  v32 = Work;
  if (v32->msgFlag == 2)
  {
    v32 = Work;
    if (!v32->msgPlayer)
    {
      v32 = Work;
      if (v32->reachShantenIndex == v7->tehaiNum)
      {
        SetBestAnalysis(0);
      }
    }
  }
  goto LABEL_61;
LABEL_5:
  if (msgStep)
    return;
  if (sBtlExt_ChkMes())
    return;
  Instance = get_Instance(0);
  if (!Active(Instance, 0))
  {
    v9 = get_Instance(0);
    if (!BgActive(v9, 0))
    {
      v11 = Work;
      msgReqDevilID = v11->msgReqDevilID;
      msgReqType = v11->msgReqType;
      sBtlExt_MesReq(msgReqDevilID, msgReqType);
      v14 = Work;
      v14->msgStep = 1;
      v14->waitCount = 0;
    }
  }
}

// 0x1d14940
static void Draw3D(void) {
  s32 v3;
  s32 fDrawAgari;
  s32 i;
  Work_t *v16;
  s32 phase;
  u32 v20;
  u32 v21;
  Work_t *v22;
  s32 agariCnt;
  u32 v24;
  s32 v25;
  u32 v26;
  s32 yakuListLength;
  char **v30;
  s32 v36;
  bool v37;
  Work_t *v41;

  if (!Work->fDrawAgari)
  {
LABEL_13:
    fDrawAgari = 0;
    goto LABEL_14;
  }
  if (Work->phase != 8)
    goto LABEL_13;
  v3 = sBtlExt_ChkMes();
  if (v3 == 1)
    goto LABEL_13;
  fDrawAgari = Work->fDrawAgari;
LABEL_14:
  if (Work->phase == 11)
  {
    MenuWin_agari_cent_SetActive(mjnUImanager, 0, 0);
    MenuWin_agari_sub_SetActive(mjnUImanager, 0, 0, 0);
    MenuWin_agari_sub_SetActive(mjnUImanager, 0, 1, 0);
    MenuWin_agari_sub_SetActive(mjnUImanager, 0, 2, 0);
    MenuWin_agari_sub_SetActive(mjnUImanager, 0, 3, 0);
    DrawEndHanchan();
    return;
  }
  ApplyCamera();
  DrawReach3D();
  DrawOya3D();
  for (i = 0; ; ++i)
  {
    if (i >= Work->haiModelIndex)
      break;
    DrawHai3DModel(i);
    DrawHai3DTex(i);
  }
  DrawModel(mjn);
  v16 = Work;
  phase = v16->phase;
  if (phase != 8)
  {
    if (phase == 9)
      goto LABEL_53;
    if (phase == 1)
      goto LABEL_53;
    v16 = Work;
    if (!v16->fDrawAgari)
    {
      DrawInfo();
      DrawNakiMenu();
      if (!fDrawAgari)
        goto LABEL_110;
LABEL_56:
      if (v20)
      {
        v22 = Work;
        if (v22->agariDrawFlag)
          goto LABEL_58;
      }
      else
      {
        v22 = Work;
        if (v22->agariDrawFlag)
        {
LABEL_58:
          if (v21)
          {
            agariCnt = v22->agariCnt;
            if (agariCnt < 31)
            {
LABEL_60:
              if (!v24)
              DrawInfoUnit();
              goto LABEL_63;
            }
          }
          else
          {
            if (Work->agariCnt < 31)
              goto LABEL_60;
          }
          if (v24)
          {
            goto LABEL_80;
          }
          else
          {
LABEL_80:
            if (CHECK_PRESS(43267, 1))
              goto LABEL_104;
            goto LABEL_101;
          }
          if (CHECK_PRESS(43267, 1))
          {
LABEL_104:
            MenuWin_agari_sub_SetActive(mjnUImanager, 0, 0, 0);
            MenuWin_agari_sub_SetActive(mjnUImanager, 0, 1, 0);
            MenuWin_agari_sub_SetActive(mjnUImanager, 0, 2, 0);
            MenuWin_agari_sub_SetActive(mjnUImanager, 0, 3, 0);
            goto LABEL_136;
          }
LABEL_101:
          if (r_click)
            goto LABEL_104;
          DrawInfoUnit();
LABEL_70:
          if (!Work->agariDrawFlag)
            return;
          if (MJN_GUIDEHELP_FLAG)
          {
            goto LABEL_74;
          }
          yakuListLength = Work->yakuListLength;
          v30 = &"MJN04";
          if (yakuListLength <= 9)
            v30 = &"MJN03";
          ButtonGuideDispSet(*v30, 1, 90);
          MJN_GUIDEHELP_FLAG = 1;
LABEL_74:
          DrawAgariMessage();
          MenuWin_agari_SetScrollBar(mjnUImanager, Work->yakuListLength, 0);
          MenuWin_agari_UpDateScrollBar(mjnUImanager, Work->yakuListLength, Work->yakuTopNo, 0);
          return;
        }
      }
      if (v21)
      {
        v25 = v22->agariCnt;
        if (v25 < 91)
        {
LABEL_67:
          if (v26)
          {
LABEL_68:
            v22->agariCnt = v25 + 1;
            goto LABEL_70;
          }
LABEL_63:
          v22 = Work;
          v25 = v22->agariCnt;
          goto LABEL_68;
        }
      }
      else
      {
        v22 = Work;
        v25 = v22->agariCnt;
        if (v25 < 91)
          goto LABEL_67;
      }
      if (!v26)
      {
        v22 = Work;
      }
      v22->agariCnt = 0;
      v22->agariDrawFlag = 1;
      goto LABEL_70;
    }
  }
LABEL_53:
  MenuWin_Play_SetActive_child(mjnUImanager, 0, 0);
  if (fDrawAgari)
    goto LABEL_56;
LABEL_110:
  if (v20)
  {
    v36 = Work->phase;
    if (v36 == 1)
      goto LABEL_129;
  }
  else
  {
    v36 = Work->phase;
    if (v36 == 1)
      goto LABEL_129;
  }
  if (v36 == 9)
    goto LABEL_129;
  v37 = CHECK_PRESS(43267, 1);
  if (!v37)
  {
    if (!r_click)
      goto LABEL_129;
  }
  if (!Work->fDrawAgari)
  {
    DrawInfoUnit();
  }
  else
  {
LABEL_129:
    MenuWin_agari_sub_SetActive(mjnUImanager, 0, 0, 0);
    MenuWin_agari_sub_SetActive(mjnUImanager, 0, 1, 0);
    MenuWin_agari_sub_SetActive(mjnUImanager, 0, 2, 0);
    MenuWin_agari_sub_SetActive(mjnUImanager, 0, 3, 0);
  }
  v41 = Work;
  v41->yakuTopNo = 0;
LABEL_136:
  MenuWin_agari_cent_SetActive(mjnUImanager, 0, 0);
}

// 0x1d179a0
static bool RuleGuideClick(void) {
  if (CHECK_PRESS(43267, 1))
    return 1;
  return r_click;
}

// 0x1d18d40
void mjnRuleGuideClickSet(void) {
  r_click = 1;
  return;
}

// 0x1d18dd0
bool mjnIsRuleGuideClick(void) {
  return r_click;
}

// 0x1d18e50
static void DrawCalc(void) {
  *(u32 *)(*((u64 *)*((const MethodInfo *)mjn + 2).virtualMethodPointer + 24) + 740) = 0;
  DrawTehai3DCalc();
  DrawSutehai3DCalc();
  DrawNakihai3DCalc();
  DrawWanpai3DCalc();
}

// 0x1d231d0
static void InitCamera(void) {
  dds3SetScreenFovy(0.628318);
  Work->cameraTargetPos = (struct sdfVector4_t)xmmword_3CFC700;
  Work->cameraEyePos = (struct sdfVector4_t)xmmword_3CFA7E0;
  Work->cameraUpVector = (struct sdfVector4_t)xmmword_3D05530;
  mapBgSetScrollReset();
}

// 0x1d232c0
static void InitLight(void) {
  sdfVector4_t *v1;
  sdfVector4_t *v2;
  sdfVector4_t v3;

  v1 = NewSpecific(sdfVector4_t, 3u);
  v1[2] = (sdfVector4_t)xmmword_3D05530;
  v1[3] = (sdfVector4_t)xmmword_3CFCDB0;
  v1[4] = (sdfVector4_t)xmmword_3CFA030;
  v2 = NewSpecific(sdfVector4_t, 4u);
  *(_OWORD *)&v2[0] = xmmword_3CFCDC0;
  *(_OWORD *)&v2[1] = xmmword_3CFFDD0;
  *(_OWORD *)&v2[2] = xmmword_3CFFDD0;
  *(_OWORD *)&v2[3] = xmmword_3CF97B0;
  v3.w = 0.0;
  v3.x = 0.6;
  v3.y = 0.6;
  v3.z = 0.6;
  dds3SetLightColor(0, 0, v3);
  dds3SetLightColor(0, 1u, v2[1]);
  dds3SetLightColor(0, 2u, v2[2]);
  dds3SetLightDir(0, 0, v1[2]);
  dds3SetLightDir(0, 1u, v1[3]);
  dds3SetLightDir(0, 2u, v1[4]);
  dds3SetAmbientColor(0, v2[3]);
}

// 0x1d23440
static void SetCamera(f32 posx, f32 posy, f32 posz, f32 targetx, f32 targety, f32 targetz) {
  Work[10] = posz;
  Work[4] = targetx;
  Work[5] = targety;
  Work[6] = targetz;
  Work[8] = posx;
  Work[9] = posy;
}

// 0x1d234f0
static void KanjiDraw(s32 x, s32 y, s32 rgba, char **moji) {
  ;
}

// 0x1d23500
static void InitTenbouModel(void) {
  dds3ModelHandle_t *v6;
  _OWORD *p_m00;
  __int128 v9;
  __int128 v10;
  __int128 v11;
  __int128 v16;
  __int128 v17;
  __int128 v18;
  u32 v21;
  sdfMatrix4_t v22;
  sdfVector4_t Row;
  sdfVector4_t v24;

  memset(&v22, 0, sizeof(v22));
  goto LABEL_3;
  if (v21)
  {
LABEL_3:
    goto LABEL_4;
  }
LABEL_4:
  vct_A = (struct sdfVector4_t)xmmword_3D03570;
  v6 = Work->tenbouModelHandle[0];
  mdlSetPosition(v6);
  mdlGetRotate(Work->tenbouModelHandle[0]);
  p_m00 = &IdentityMatrix.m00;
  v9 = p_m00[2];
  v10 = p_m00[3];
  v11 = p_m00[1];
  *(_OWORD *)&v22.m00 = *p_m00;
  *(_OWORD *)&v22.m01 = v11;
  *(_OWORD *)&v22.m02 = v9;
  *(_OWORD *)&v22.m03 = v10;
  Row = GetRow(&v22, 1, 0);
  vct_B = Row;
  FromRotation_B(1.5707964);
  Mult();
  mdlSetRotate(Work->tenbouModelHandle[0]);
  vct_A = (struct sdfVector4_t)xmmword_3D055E0;
  mdlSetPosition(Work->tenbouModelHandle[1]);
  vct_A = (struct sdfVector4_t)xmmword_3D03580;
  mdlSetPosition(Work->tenbouModelHandle[2]);
  mdlGetRotate(Work->tenbouModelHandle[2]);
  v16 = *(_OWORD *)&IdentityMatrix.m02;
  v17 = *(_OWORD *)&IdentityMatrix.m03;
  v18 = *(_OWORD *)&IdentityMatrix.m01;
  *(_OWORD *)&v22.m00 = *(_OWORD *)&IdentityMatrix.m00;
  *(_OWORD *)&v22.m01 = v18;
  *(_OWORD *)&v22.m02 = v16;
  *(_OWORD *)&v22.m03 = v17;
  v24 = GetRow(&v22, 1, 0);
  vct_B = v24;
  FromRotation_B(1.5707964);
  Mult();
  mdlSetRotate(Work->tenbouModelHandle[2]);
  vct_A = (struct sdfVector4_t)xmmword_3CFB810;
  mdlSetPosition(Work->tenbouModelHandle[3]);
}

// 0x1d23990
static void InitOyaModel(void) {
  u32 oya;
  _OWORD *p_m00;
  __int128 v7;
  __int128 v8;
  __int128 v9;
  dds3ModelHandle_t *v12;
  __int128 v15;
  __int128 v16;
  __int128 v17;
  __int128 v21;
  __int128 v22;
  __int128 v23;
  __int128 v27;
  __int128 v28;
  __int128 v29;
  f32 v32;
  f32 v33;
  _OWORD *v35;
  __int128 v36;
  __int128 v37;
  __int128 v38;
  dds3ModelHandle_t *v41;
  __int128 v44;
  __int128 v45;
  __int128 v46;
  __int128 v50;
  __int128 v51;
  __int128 v52;
  __int128 v56;
  __int128 v57;
  __int128 v58;
  _OWORD *v61;
  __int128 v62;
  __int128 v63;
  __int128 v64;
  dds3ModelHandle_t *v67;
  __int128 v70;
  __int128 v71;
  __int128 v72;
  __int128 v76;
  __int128 v77;
  __int128 v78;
  __int128 v82;
  __int128 v83;
  __int128 v84;
  _OWORD *v87;
  __int128 v88;
  __int128 v89;
  __int128 v90;
  dds3ModelHandle_t *v93;
  __int128 v96;
  __int128 v97;
  __int128 v98;
  __int128 v102;
  __int128 v103;
  __int128 v104;
  __int128 v108;
  __int128 v109;
  __int128 v110;
  f32 *p_x;
  sdfMatrix4_t v113;
  sdfVector4_t Row;
  sdfVector4_t v115;
  sdfVector4_t v116;
  sdfVector4_t v117;
  sdfVector4_t v118;
  sdfVector4_t v119;
  sdfVector4_t v120;
  sdfVector4_t v121;
  sdfVector4_t v122;
  sdfVector4_t v123;
  sdfVector4_t v124;
  sdfVector4_t v125;
  sdfVector4_t v126;
  sdfVector4_t v127;
  sdfVector4_t v128;
  sdfVector4_t v129;

  memset(&v113, 0, sizeof(v113));
  oya = Work->oya;
  if (oya <= 3)
  {
    switch (oya)
    {
      case 0u:
        p_m00 = &IdentityMatrix.m00;
        v7 = p_m00[2];
        v8 = p_m00[3];
        v9 = p_m00[1];
        *(_OWORD *)&v113.m00 = *p_m00;
        *(_OWORD *)&v113.m01 = v9;
        *(_OWORD *)&v113.m02 = v7;
        *(_OWORD *)&v113.m03 = v8;
        Row = GetRow(&v113, 1, 0);
        vct_A = Row;
        FromRotation(0.0);
        v12 = Work->oyaModelHandle[0];
        mdlSetRotate(v12);
        vct_A = (struct sdfVector4_t)xmmword_3CF8FE0;
        mdlSetPosition(Work->oyaModelHandle[0]);
        v15 = *(_OWORD *)&IdentityMatrix.m02;
        v16 = *(_OWORD *)&IdentityMatrix.m03;
        v17 = *(_OWORD *)&IdentityMatrix.m01;
        *(_OWORD *)&v113.m00 = *(_OWORD *)&IdentityMatrix.m00;
        *(_OWORD *)&v113.m01 = v17;
        *(_OWORD *)&v113.m02 = v15;
        *(_OWORD *)&v113.m03 = v16;
        v115 = GetRow(&v113, 1, 0);
        vct_A = v115;
        FromRotation(3.1415927);
        mdlSetRotate(Work->oyaModelHandle[1]);
        vct_A = (struct sdfVector4_t)xmmword_3D03ED0;
        mdlSetPosition(Work->oyaModelHandle[1]);
        v21 = *(_OWORD *)&IdentityMatrix.m02;
        v22 = *(_OWORD *)&IdentityMatrix.m03;
        v23 = *(_OWORD *)&IdentityMatrix.m01;
        *(_OWORD *)&v113.m00 = *(_OWORD *)&IdentityMatrix.m00;
        *(_OWORD *)&v113.m01 = v23;
        *(_OWORD *)&v113.m02 = v21;
        *(_OWORD *)&v113.m03 = v22;
        v116 = GetRow(&v113, 1, 0);
        vct_A = v116;
        FromRotation(4.712389);
        mdlSetRotate(Work->oyaModelHandle[2]);
        vct_A = (struct sdfVector4_t)xmmword_3D05DF0;
        mdlSetPosition(Work->oyaModelHandle[2]);
        v27 = *(_OWORD *)&IdentityMatrix.m02;
        v28 = *(_OWORD *)&IdentityMatrix.m03;
        v29 = *(_OWORD *)&IdentityMatrix.m01;
        *(_OWORD *)&v113.m00 = *(_OWORD *)&IdentityMatrix.m00;
        *(_OWORD *)&v113.m01 = v29;
        *(_OWORD *)&v113.m02 = v27;
        *(_OWORD *)&v113.m03 = v28;
        v117 = GetRow(&v113, 1, 0);
        vct_A = v117;
        FromRotation(1.5707964);
        mdlSetRotate(Work->oyaModelHandle[3]);
        v32 = -22.0;
        v33 = 30.0;
        goto LABEL_100;
      case 1u:
        v35 = &IdentityMatrix.m00;
        v36 = v35[2];
        v37 = v35[3];
        v38 = v35[1];
        *(_OWORD *)&v113.m00 = *v35;
        *(_OWORD *)&v113.m01 = v38;
        *(_OWORD *)&v113.m02 = v36;
        *(_OWORD *)&v113.m03 = v37;
        v118 = GetRow(&v113, 1, 0);
        vct_A = v118;
        FromRotation(1.5707964);
        v41 = Work->oyaModelHandle[0];
        mdlSetRotate(v41);
        vct_A = (struct sdfVector4_t)xmmword_3CFEE60;
        mdlSetPosition(Work->oyaModelHandle[0]);
        v44 = *(_OWORD *)&IdentityMatrix.m02;
        v45 = *(_OWORD *)&IdentityMatrix.m03;
        v46 = *(_OWORD *)&IdentityMatrix.m01;
        *(_OWORD *)&v113.m00 = *(_OWORD *)&IdentityMatrix.m00;
        *(_OWORD *)&v113.m01 = v46;
        *(_OWORD *)&v113.m02 = v44;
        *(_OWORD *)&v113.m03 = v45;
        v119 = GetRow(&v113, 1, 0);
        vct_A = v119;
        FromRotation(4.712389);
        mdlSetRotate(Work->oyaModelHandle[1]);
        vct_A = (struct sdfVector4_t)xmmword_3D05DF0;
        mdlSetPosition(Work->oyaModelHandle[1]);
        v50 = *(_OWORD *)&IdentityMatrix.m02;
        v51 = *(_OWORD *)&IdentityMatrix.m03;
        v52 = *(_OWORD *)&IdentityMatrix.m01;
        *(_OWORD *)&v113.m00 = *(_OWORD *)&IdentityMatrix.m00;
        *(_OWORD *)&v113.m01 = v52;
        *(_OWORD *)&v113.m02 = v50;
        *(_OWORD *)&v113.m03 = v51;
        v120 = GetRow(&v113, 1, 0);
        vct_A = v120;
        FromRotation(0.0);
        mdlSetRotate(Work->oyaModelHandle[2]);
        vct_A = (struct sdfVector4_t)xmmword_3CF8FE0;
        mdlSetPosition(Work->oyaModelHandle[2]);
        v56 = *(_OWORD *)&IdentityMatrix.m02;
        v57 = *(_OWORD *)&IdentityMatrix.m03;
        v58 = *(_OWORD *)&IdentityMatrix.m01;
        *(_OWORD *)&v113.m00 = *(_OWORD *)&IdentityMatrix.m00;
        *(_OWORD *)&v113.m01 = v58;
        *(_OWORD *)&v113.m02 = v56;
        *(_OWORD *)&v113.m03 = v57;
        v121 = GetRow(&v113, 1, 0);
        vct_A = v121;
        FromRotation(3.1415927);
        mdlSetRotate(Work->oyaModelHandle[3]);
        v32 = 30.0;
        v33 = 22.0;
LABEL_100:
        p_x = &vf00.x;
        p_x[5] = -80.0;
        p_x[4] = v33;
        p_x[6] = v32;
        p_x[7] = 1.0;
        mdlSetPosition(Work->oyaModelHandle[3]);
        return;
      case 2u:
        v61 = &IdentityMatrix.m00;
        v62 = v61[2];
        v63 = v61[3];
        v64 = v61[1];
        *(_OWORD *)&v113.m00 = *v61;
        *(_OWORD *)&v113.m01 = v64;
        *(_OWORD *)&v113.m02 = v62;
        *(_OWORD *)&v113.m03 = v63;
        v122 = GetRow(&v113, 1, 0);
        vct_A = v122;
        FromRotation(3.1415927);
        v67 = Work->oyaModelHandle[0];
        mdlSetRotate(v67);
        vct_A = (struct sdfVector4_t)xmmword_3D03ED0;
        mdlSetPosition(Work->oyaModelHandle[0]);
        v70 = *(_OWORD *)&IdentityMatrix.m02;
        v71 = *(_OWORD *)&IdentityMatrix.m03;
        v72 = *(_OWORD *)&IdentityMatrix.m01;
        *(_OWORD *)&v113.m00 = *(_OWORD *)&IdentityMatrix.m00;
        *(_OWORD *)&v113.m01 = v72;
        *(_OWORD *)&v113.m02 = v70;
        *(_OWORD *)&v113.m03 = v71;
        v123 = GetRow(&v113, 1, 0);
        vct_A = v123;
        FromRotation(0.0);
        mdlSetRotate(Work->oyaModelHandle[1]);
        vct_A = (struct sdfVector4_t)xmmword_3CF8FE0;
        mdlSetPosition(Work->oyaModelHandle[1]);
        v76 = *(_OWORD *)&IdentityMatrix.m02;
        v77 = *(_OWORD *)&IdentityMatrix.m03;
        v78 = *(_OWORD *)&IdentityMatrix.m01;
        *(_OWORD *)&v113.m00 = *(_OWORD *)&IdentityMatrix.m00;
        *(_OWORD *)&v113.m01 = v78;
        *(_OWORD *)&v113.m02 = v76;
        *(_OWORD *)&v113.m03 = v77;
        v124 = GetRow(&v113, 1, 0);
        vct_A = v124;
        FromRotation(1.5707964);
        mdlSetRotate(Work->oyaModelHandle[2]);
        vct_A = (struct sdfVector4_t)xmmword_3CFEE60;
        mdlSetPosition(Work->oyaModelHandle[2]);
        v82 = *(_OWORD *)&IdentityMatrix.m02;
        v83 = *(_OWORD *)&IdentityMatrix.m03;
        v84 = *(_OWORD *)&IdentityMatrix.m01;
        *(_OWORD *)&v113.m00 = *(_OWORD *)&IdentityMatrix.m00;
        *(_OWORD *)&v113.m01 = v84;
        *(_OWORD *)&v113.m02 = v82;
        *(_OWORD *)&v113.m03 = v83;
        v125 = GetRow(&v113, 1, 0);
        vct_A = v125;
        FromRotation(4.712389);
        mdlSetRotate(Work->oyaModelHandle[3]);
        v32 = 22.0;
        v33 = -30.0;
        goto LABEL_100;
      case 3u:
        v87 = &IdentityMatrix.m00;
        v88 = v87[2];
        v89 = v87[3];
        v90 = v87[1];
        *(_OWORD *)&v113.m00 = *v87;
        *(_OWORD *)&v113.m01 = v90;
        *(_OWORD *)&v113.m02 = v88;
        *(_OWORD *)&v113.m03 = v89;
        v126 = GetRow(&v113, 1, 0);
        vct_A = v126;
        FromRotation(4.712389);
        v93 = Work->oyaModelHandle[0];
        mdlSetRotate(v93);
        vct_A = (struct sdfVector4_t)xmmword_3D05DF0;
        mdlSetPosition(Work->oyaModelHandle[0]);
        v96 = *(_OWORD *)&IdentityMatrix.m02;
        v97 = *(_OWORD *)&IdentityMatrix.m03;
        v98 = *(_OWORD *)&IdentityMatrix.m01;
        *(_OWORD *)&v113.m00 = *(_OWORD *)&IdentityMatrix.m00;
        *(_OWORD *)&v113.m01 = v98;
        *(_OWORD *)&v113.m02 = v96;
        *(_OWORD *)&v113.m03 = v97;
        v127 = GetRow(&v113, 1, 0);
        vct_A = v127;
        FromRotation(1.5707964);
        mdlSetRotate(Work->oyaModelHandle[1]);
        vct_A = (struct sdfVector4_t)xmmword_3CFEE60;
        mdlSetPosition(Work->oyaModelHandle[1]);
        v102 = *(_OWORD *)&IdentityMatrix.m02;
        v103 = *(_OWORD *)&IdentityMatrix.m03;
        v104 = *(_OWORD *)&IdentityMatrix.m01;
        *(_OWORD *)&v113.m00 = *(_OWORD *)&IdentityMatrix.m00;
        *(_OWORD *)&v113.m01 = v104;
        *(_OWORD *)&v113.m02 = v102;
        *(_OWORD *)&v113.m03 = v103;
        v128 = GetRow(&v113, 1, 0);
        vct_A = v128;
        FromRotation(3.1415927);
        mdlSetRotate(Work->oyaModelHandle[2]);
        vct_A = (struct sdfVector4_t)xmmword_3D03ED0;
        mdlSetPosition(Work->oyaModelHandle[2]);
        v108 = *(_OWORD *)&IdentityMatrix.m02;
        v109 = *(_OWORD *)&IdentityMatrix.m03;
        v110 = *(_OWORD *)&IdentityMatrix.m01;
        *(_OWORD *)&v113.m00 = *(_OWORD *)&IdentityMatrix.m00;
        *(_OWORD *)&v113.m01 = v110;
        *(_OWORD *)&v113.m02 = v108;
        *(_OWORD *)&v113.m03 = v109;
        v129 = GetRow(&v113, 1, 0);
        vct_A = v129;
        FromRotation(0.0);
        mdlSetRotate(Work->oyaModelHandle[3]);
        v33 = -22.0;
        v32 = -22.0;
        goto LABEL_100;
      default:
        return;
    }
  }
}

// 0x1d15f10
static void DrawHai3DIndex(s32 index) {
  DrawHai3DModel(index);
  DrawHai3DTex(index);
}

// 0x1d24e20
static void DrawHai3DModel(s32 index) {
  dds3ModelHandle_t *v4;
  sdfModelOt_t *v6;

  v4 = Work->haiModelHandle[index];
  v6 = ModelOt[0];
  Link(v4, v6);
}

// 0x1d24f20
static void DrawHai3DTex(s32 index) {
  HaiDrawData_t *v6;
  void *HilightCol_local;
  dds3ModelHandle_t *v8;
  s64 v9;
  s64 v10;
  void *v12;
  void *v13;
  void *v14;
  void *v15;
  s64 v16;
  s64 v17;
  sdfVector4_t v18;

  v6 = Work->haiDrawData[index];
  if (v6->fDrawTex)
  {
    switch (v6->highlight)
    {
      case 0xFFFFFFFF:
        HilightCol_local = HilightCol;
        v8 = Work->haiModelHandle[index];
        v9 = *(u64 *)&HilightCol_local->DisableCol.x;
        v10 = *(u64 *)&HilightCol_local->DisableCol.z;
        break;
      case 1:
        v13 = HilightCol;
        v8 = Work->haiModelHandle[index];
        v9 = *(u64 *)&v13->NakiCol.x;
        v10 = *(u64 *)&v13->NakiCol.z;
        break;
      case 2:
        v14 = HilightCol;
        v8 = Work->haiModelHandle[index];
        v9 = *(u64 *)&v14->SelSuteCol.x;
        v10 = *(u64 *)&v14->SelSuteCol.z;
        break;
      case 3:
        v15 = HilightCol;
        v8 = Work->haiModelHandle[index];
        v9 = *(u64 *)&v15->PlDoraCol.x;
        v10 = *(u64 *)&v15->PlDoraCol.z;
        break;
      default:
        v12 = HilightCol;
        v8 = Work->haiModelHandle[index];
        v9 = *(u64 *)&v12->NormalCol.x;
        v10 = *(u64 *)&v12->NormalCol.z;
        v16 = v9;
        v17 = v10;
        v9 = v16;
        v10 = v17;
        break;
    }
    *(u64 *)&v18.x = v9;
    *(u64 *)&v18.z = v10;
    SetColor(v8, v18);
  }
}

// 0x1d25160
static void DrawNumber(s32 num, s32 offX, s32 offY, s32 sign, s32 rgba) {

}

// 0x1d169f0
static void DrawNakiMenu(void) {
  char *v1;
  char *v2;
  u64 *v3;
  char *v4;
  char *v5;
  char *v6;
  char *v7;
  char *v8;
  char *v9;
  char *v10;
  char *v11;
  char *v12;
  char *v13;
  char *v14;
  char *v15;
  u64 *v16;
  char *v17;
  u64 *v18;
  char *v19;
  char *v20;
  char *v21;
  char *v22;
  char *v23;
  char *v24;
  char *v25;
  char *v26;
  char *v27;
  char *v28;
  char *v29;
  char *v30;
  char *v31;
  char *v32;
  char *v33;
  char *v34;
  char *v35;
  char *v36;
  char *v37;
  char *v38;
  char *v39;
  char *v40;
  char *v41;
  char *v42;
  char *v43;
  char *v44;
  char *v45;
  char *v46;
  char *v47;
  char *v48;
  char *v49;
  char *v50;
  char *v51;
  char *v52;
  char *v53;
  s32 phase;
  s64 i;
  u32 v62;
  s64 nakiMenuNum;
  s32 v65;
  bool v66;
  char *v67;
  char *v68;
  u64 *v70;
  char *v71;
  char *v72;
  char *v73;
  char *v74;
  s32 *Chi_Sav_R;
  char *v77;
  char *v78;
  char *v80;
  char *v81;
  char *v82;
  char *v83;
  char *v84;
  char *v86;
  char *v87;
  char *v88;
  char *v89;
  char *v90;
  char *v91;
  char *v92;
  char *v93;
  char *v94;
  char *LocalizeText;
  s32 v97;
  char **v101;
  char **v102;
  char **v103;
  char **v104;
  char **v105;
  char **v106;
  char **v107;
  char **v108;
  char **v109;

  v1 = NewSpecific(string, 0xDu);
  v2 = "MJN_NAKIMSG_L0000";
  v3 = v1;
  v1[0] = "MJN_NAKIMSG_L0000";
  v109 = &v1[0];
  v4 = "MJN_NAKIMSG_L0001";
  v3[5] = "MJN_NAKIMSG_L0001";
  v105 = (v3 + 5);
  v5 = "MJN_NAKIMSG_L0002";
  v3[6] = "MJN_NAKIMSG_L0002";
  v104 = (v3 + 6);
  v6 = "MJN_NAKIMSG_L0003";
  v3[7] = "MJN_NAKIMSG_L0003";
  v103 = (v3 + 7);
  v7 = "MJN_NAKIMSG_L0004";
  v3[8] = "MJN_NAKIMSG_L0004";
  v102 = (v3 + 8);
  v8 = "MJN_NAKIMSG_L0005";
  v3[9] = "MJN_NAKIMSG_L0005";
  v101 = (v3 + 9);
  v9 = "MJN_NAKIMSG_L0006";
  v3[10] = "MJN_NAKIMSG_L0006";
  v108 = (v3 + 10);
  v10 = "MJN_NAKIMSG_L0007";
  v3[11] = "MJN_NAKIMSG_L0007";
  v107 = (v3 + 11);
  v11 = "MJN_NAKIMSG_L0008";
  v3[12] = "MJN_NAKIMSG_L0008";
  v12 = "MJN_NAKIMSG_L0009";
  v3[13] = "MJN_NAKIMSG_L0009";
  v13 = "MJN_NAKIMSG_L0010";
  v3[14] = "MJN_NAKIMSG_L0010";
  v14 = "MJN_NAKIMSG_L0011";
  v3[15] = "MJN_NAKIMSG_L0011";
  v106 = (v3 + 15);
  v15 = "MJN_NAKIMSG_L0012";
  v3[16] = "MJN_NAKIMSG_L0012";
  v16 = v3 + 16;
  v17 = "sprite name=";
  v18 = NewSpecific(string, 0x23u);
  v19 = "mj_par_1wan";
  v18[4] = "mj_par_1wan";
  v20 = "mj_par_2wan";
  v18[5] = "mj_par_2wan";
  v21 = "mj_par_3wan";
  v18[6] = "mj_par_3wan";
  v22 = "mj_par_4wan";
  v18[7] = "mj_par_4wan";
  v23 = "mj_par_5wan";
  v18[8] = "mj_par_5wan";
  v24 = "mj_par_6wan";
  v18[9] = "mj_par_6wan";
  v25 = "mj_par_7wan";
  v18[10] = "mj_par_7wan";
  v26 = "mj_par_8wan";
  v18[11] = "mj_par_8wan";
  v27 = "mj_par_9wan";
  v18[12] = "mj_par_9wan";
  v28 = "mj_par_1pin";
  v18[13] = "mj_par_1pin";
  v29 = "mj_par_2pin";
  v18[14] = "mj_par_2pin";
  v30 = "mj_par_3pin";
  v18[15] = "mj_par_3pin";
  v31 = "mj_par_4pin";
  v18[16] = "mj_par_4pin";
  v32 = "mj_par_5pin";
  v18[17] = "mj_par_5pin";
  v33 = "mj_par_6pin";
  v18[18] = "mj_par_6pin";
  v34 = "mj_par_7pin";
  v18[19] = "mj_par_7pin";
  v35 = "mj_par_8pin";
  v18[20] = "mj_par_8pin";
  v36 = "mj_par_9pin";
  v18[21] = "mj_par_9pin";
  v37 = "mj_par_1so";
  v18[22] = "mj_par_1so";
  v38 = "mj_par_2so";
  v18[23] = "mj_par_2so";
  v39 = "mj_par_3so";
  v18[24] = "mj_par_3so";
  v40 = "mj_par_4so";
  v18[25] = "mj_par_4so";
  v41 = "mj_par_5so";
  v18[26] = "mj_par_5so";
  v42 = "mj_par_6so";
  v18[27] = "mj_par_6so";
  v43 = "mj_par_7so";
  v18[28] = "mj_par_7so";
  v44 = "mj_par_8so";
  v18[29] = "mj_par_8so";
  v45 = "mj_par_9so";
  v18[30] = "mj_par_9so";
  v46 = "mj_par_ton";
  v18[31] = "mj_par_ton";
  v47 = "mj_par_nan";
  v18[32] = "mj_par_nan";
  v48 = "mj_par_sha";
  v18[33] = "mj_par_sha";
  v49 = "mj_par_pe";
  v18[34] = "mj_par_pe";
  v50 = "mj_par_haku";
  v18[35] = "mj_par_haku";
  v51 = "mj_par_hatsu";
  v18[36] = "mj_par_hatsu";
  v52 = "mj_par_chun";
  v18[37] = "mj_par_chun";
  v53 = "mj_par_pai";
  v18[38] = "mj_par_pai";
  phase = Work->phase;
  if (phase != 5)
  {
    selMenu_play_SetActive(mjnUImanager, 0, 0);
    return;
  }
  selMenu_play_SetActive(mjnUImanager, 1, 0);
  if (!TIPSOPEN)
  {
    if (!MJN_GUIDEHELP_FLAG)
    {
      ButtonGuideDispSet("MJN06", 1, 90);
      ButtonGuideDispOn();
      MJN_GUIDEHELP_FLAG = 1;
    }
  }
  for (i = 0; ; ++i)
  {
    nakiMenuNum = Work->nakiMenuNum;
    if (i >= nakiMenuNum)
      break;
    if (v62)
    {
      v65 = Work->nakiMenu[i];
      v66 = (u32)v65 > 0x40;
      if (v65 <= 64)
        goto LABEL_48;
    }
    else
    {
      v65 = Work->nakiMenu[i];
      v66 = (u32)v65 > 0x40;
      if (v65 <= 64)
      {
LABEL_48:
        if (v66)
        {
LABEL_50:
          v77 = *v109;
        }
        else
        {
          switch (v65)
          {
            case 0:
            case 3:
            case 5:
            case 6:
            case 7:
            case 9:
            case 10:
            case 11:
            case 12:
            case 13:
            case 14:
            case 15:
              goto LABEL_50;
            case 1:
              v77 = *v105;
              goto LABEL_73;
            case 2:
              v77 = *v104;
              goto LABEL_73;
            case 4:
              v77 = *v103;
              goto LABEL_73;
            case 8:
              v77 = *v102;
              goto LABEL_73;
            case 16:
              v77 = *v101;
              goto LABEL_73;
            default:
              if (v65 == 32)
              {
                v77 = *v108;
                goto LABEL_73;
              }
              else
              {
                if (v65 != 64)
                  goto LABEL_50;
                v77 = *v107;
                goto LABEL_73;
              }
              break;
          }
        }
LABEL_73:
        LocalizeText = GetLocalizeText(v77, 1);
        goto LABEL_25;
      }
    }
    if ((u32)v65 <= 0x10000080)
    {
      if (v65 == 4096)
      {
        v77 = *v106;
        goto LABEL_73;
      }
      if (v65 != 268435584)
        goto LABEL_50;
      v67 = NewSpecific(string, 0xAu);
      v78 = "<";
      v67[0] = "<";
      v67[1] = v17;
      v70 = v18 + 4;
      v80 = v18[Work->Chi_Sav_R[0] + 4];
      v67[2] = v80;
      v81 = "> <";
      v67[3] = "> <";
      v67[4] = v17;
      v82 = v18[Work->Chi_Sav_R[1] + 4];
      v67[5] = v82;
      v83 = "> <";
      v67[6] = "> <";
      v67[7] = v17;
      Chi_Sav_R = Work->Chi_Sav_R;
    }
    else if (v65 == 268435712)
    {
      v67 = NewSpecific(string, 0xAu);
      v84 = "<";
      v67[0] = "<";
      v67[1] = v17;
      v70 = v18 + 4;
      v86 = v18[Work->Chi_Sav_C[0] + 4];
      v67[2] = v86;
      v87 = "> <";
      v67[3] = "> <";
      v67[4] = v17;
      v88 = v18[Work->Chi_Sav_C[1] + 4];
      v67[5] = v88;
      v89 = "> <";
      v67[6] = "> <";
      v67[7] = v17;
      Chi_Sav_R = Work->Chi_Sav_C;
    }
    else
    {
      if (v65 != 268435968)
        goto LABEL_50;
      v67 = NewSpecific(string, 0xAu);
      v68 = "<";
      v67[0] = "<";
      v67[1] = v17;
      v70 = v18 + 4;
      v71 = v18[Work->Chi_Sav_L[0] + 4];
      v67[2] = v71;
      v72 = "> <";
      v67[3] = "> <";
      v67[4] = v17;
      v73 = v18[Work->Chi_Sav_L[1] + 4];
      v67[5] = v73;
      v74 = "> <";
      v67[6] = "> <";
      v67[7] = v17;
      Chi_Sav_R = Work->Chi_Sav_L;
    }
    v90 = v70[Chi_Sav_R[2]];
    v67[8] = v90;
    v91 = ">";
    v67[9] = ">";
    v92 = Concat_54832608(v67, 0);
    v93 = *v16;
    v94 = GetLocalizeText(v93, 1);
    LocalizeText = Concat_54831728(v94, "  ", v92, 0);
LABEL_25:
    selMenu_play_SetParam(mjnUImanager, i, LocalizeText, 0);
  }
  if (v62)
  {
    if ((s32)nakiMenuNum > 7)
      goto LABEL_82;
  }
  else
  {
    LODWORD(nakiMenuNum) = Work->nakiMenuNum;
    if ((s32)nakiMenuNum > 7)
      goto LABEL_82;
  }
  LODWORD(nakiMenuNum) = Work->nakiMenuNum;
  v97 = nakiMenuNum - 1;
  if ((s32)nakiMenuNum - 1 <= 5)
  {
    do
    {
      selMenuBar_play_SetFalse(mjnUImanager, v97++, 0);
    }
    while (v97 != 6);
  }
LABEL_82:
  selMenuBar_play_SetCursor(mjnUImanager, Work->nakiCursor, 0);
}

// 0x1d251c0
static void KanjiDrawBig(s32 x, s32 y, s32 rgba, char **moji) {
  ;
}

// 0x1d251d0
static void DrawName(s32 x, s32 y, s32 rgba, s32 playerIndex) {
  ;
}

// 0x1d17b00
static void DrawAgariMessage(void) {
  char *v1;
  char *v2;
  char *v3;
  char *v4;
  char *v5;
  char *v6;
  char *v7;
  char *v8;
  char *v9;
  char *v10;
  char *v11;
  char *v12;
  char *v13;
  char *v14;
  char *v15;
  char *v16;
  char *v17;
  char *v18;
  char *v19;
  char *v20;
  char *v21;
  char *v22;
  char *v23;
  char *v24;
  char *v25;
  char *v26;
  char *v27;
  char *v28;
  char *v29;
  char *v30;
  char *v31;
  char *v32;
  char *v33;
  char *v34;
  char *v35;
  char *v36;
  char *v37;
  char *v38;
  char *v39;
  char *v40;
  char *v41;
  char *v42;
  char *v43;
  char *v44;
  char *v47;
  char *v48;
  u64 *v49;
  char *v50;
  char *v51;
  char *v52;
  char *v53;
  char *v54;
  char *v55;
  char *v56;
  char *v57;
  char *v58;
  char *v59;
  char *v60;
  char *v61;
  char **v62;
  char *v63;
  char **v64;
  char *v65;
  char **v66;
  char *v67;
  char **v68;
  char *v69;
  char **v70;
  char *v71;
  char **v72;
  char *v73;
  char **v74;
  char *v75;
  char **v76;
  char *v77;
  u64 *v78;
  s32 fDrawAgari;
  char *v83;
  char *LocalizeText;
  Agari_t *v85;
  s32 *yaku;
  char *v87;
  char *v89;
  char *v90;
  char *v92;
  char *v94;
  char *v95;
  void *v98;
  char *v99;
  char *v100;
  char *v101;
  char *v102;
  Player_t *m_Items;
  bool v104;
  s32 yakuNum;
  s32 v106;
  char **v107;
  char *v109;
  char *v110;
  u64 v112;
  s32 v113;
  char *v114;
  Il2CppObject *v115;
  char *v116;
  char *v117;
  s32 v118;
  char **v119;
  char *v121;
  char *v122;
  u32 v124;
  char *v125;
  char *v126;
  char *v127;
  Work_t *Work_local;
  u32 v133;
  s32 fu;
  void *p_mjnUImanager;
  void *v137;
  Il2CppObject *v138;
  char *v139;
  char *v140;
  char *v141;
  char *v142;
  Il2CppObject *v143;
  char *v144;
  char *v145;
  char *v146;
  char *v147;
  void *v149;
  Il2CppObject *v150;
  Agari_t *v151;
  char *v152;
  char *v153;
  char *v154;
  char *v155;
  Il2CppObject *v156;
  char *v157;
  char *v158;
  char *v159;
  char **v160;
  char **v161;
  char **v162;
  char **v163;
  char **v164;
  char **v165;
  char **v166;
  char **v167;
  char **v168;
  char **v169;
  char **v170;
  char **v171;
  s64 v172;
  Agari_t *pAgari;
  s32 v174;
  s32 data;

  v1 = NewSpecific(string, 0x2Au);
  v2 = "";
  v3 = v1;
  v1[0] = "";
  v172 = &v1[0];
  v4 = "";
  v3[1] = "";
  v5 = "";
  v3[2] = "";
  v6 = "";
  v3[3] = "";
  v7 = "";
  v3[4] = "";
  v8 = "";
  v3[5] = "";
  v9 = "";
  v3[6] = "";
  v10 = "";
  v3[7] = "";
  v11 = "";
  v3[8] = "";
  v12 = "";
  v3[9] = "";
  v13 = "";
  v3[10] = "";
  v14 = "";
  v3[11] = "";
  v15 = "";
  v3[12] = "";
  v16 = "";
  v3[13] = "";
  v17 = "";
  v3[14] = "";
  v18 = "";
  v3[15] = "";
  v19 = "";
  v3[16] = "";
  v20 = "";
  v3[17] = "";
  v21 = "";
  v3[18] = "";
  v22 = "";
  v3[19] = "";
  v23 = "";
  v3[20] = "";
  v24 = "";
  v3[21] = "";
  v25 = "";
  v3[22] = "";
  v26 = "";
  v3[23] = "";
  v27 = "";
  v3[24] = "";
  v28 = "";
  v3[25] = "";
  v29 = "";
  v3[26] = "";
  v30 = "";
  v3[27] = "";
  v31 = "";
  v3[28] = "";
  v32 = "";
  v3[29] = "";
  v33 = "";
  v3[30] = "";
  v34 = "";
  v3[31] = "";
  v35 = "";
  v3[32] = "";
  v36 = "";
  v3[33] = "";
  v37 = "";
  v3[34] = "";
  v38 = "";
  v3[35] = "";
  v39 = "";
  v3[36] = "";
  v40 = "";
  v3[37] = "";
  v41 = "";
  v3[38] = "";
  v42 = "";
  v3[39] = "";
  v43 = "";
  v3[40] = "";
  v44 = "";
  v3[41] = "";
  MenuWin_agari_cent_SetActive(mjnUImanager, 1, 0);
  pAgari = Work->pAgari;
  v47 = NewSpecific(string, 0x15u);
  v48 = "MJN_AGARIMSG_L0000";
  v49 = v47;
  v47[0] = "MJN_AGARIMSG_L0000";
  v171 = &v47[0];
  v50 = "MJN_AGARIMSG_L0001";
  v49[5] = "MJN_AGARIMSG_L0001";
  v169 = (v49 + 5);
  v51 = "MJN_AGARIMSG_L0002";
  v49[6] = "MJN_AGARIMSG_L0002";
  v161 = (v49 + 6);
  v52 = "MJN_AGARIMSG_L0003";
  v49[7] = "MJN_AGARIMSG_L0003";
  v162 = (v49 + 7);
  v53 = "MJN_AGARIMSG_L0004";
  v49[8] = "MJN_AGARIMSG_L0004";
  v165 = (v49 + 8);
  v54 = "MJN_AGARIMSG_L0005";
  v49[9] = "MJN_AGARIMSG_L0005";
  v164 = (v49 + 9);
  v55 = "MJN_AGARIMSG_L0006";
  v49[10] = "MJN_AGARIMSG_L0006";
  v166 = (v49 + 10);
  v56 = "MJN_AGARIMSG_L0007";
  v49[11] = "MJN_AGARIMSG_L0007";
  v163 = (v49 + 11);
  v57 = "MJN_AGARIMSG_L0008";
  v49[12] = "MJN_AGARIMSG_L0008";
  v170 = (v49 + 12);
  v58 = "MJN_AGARIMSG_L0009";
  v49[13] = "MJN_AGARIMSG_L0009";
  v168 = (v49 + 13);
  v59 = "MJN_AGARIMSG_L0010";
  v49[14] = "MJN_AGARIMSG_L0010";
  v167 = (v49 + 14);
  v60 = "MJN_AGARIMSG_L0011";
  v49[15] = "MJN_AGARIMSG_L0011";
  v160 = (v49 + 15);
  v61 = "MJN_AGARIMSG_L0012";
  v49[16] = "MJN_AGARIMSG_L0012";
  v62 = (v49 + 16);
  v63 = "MJN_AGARIMSG_L0013";
  v49[17] = "MJN_AGARIMSG_L0013";
  v64 = (v49 + 17);
  v65 = "MJN_AGARIMSG_L0014";
  v49[18] = "MJN_AGARIMSG_L0014";
  v66 = (v49 + 18);
  v67 = "MJN_AGARIMSG_L0015";
  v49[19] = "MJN_AGARIMSG_L0015";
  v68 = (v49 + 19);
  v69 = "MJN_AGARIMSG_L0016";
  v49[20] = "MJN_AGARIMSG_L0016";
  v70 = (v49 + 20);
  v71 = "MJN_AGARIMSG_L0017";
  v49[21] = "MJN_AGARIMSG_L0017";
  v72 = (v49 + 21);
  v73 = "MJN_AGARIMSG_L0018";
  v49[22] = "MJN_AGARIMSG_L0018";
  v74 = (v49 + 22);
  v75 = "MJN_AGARIMSG_L0019";
  v49[23] = "MJN_AGARIMSG_L0019";
  v76 = (v49 + 23);
  v77 = "MJN_AGARIMSG_L0020";
  v49[24] = "MJN_AGARIMSG_L0020";
  v78 = v49 + 24;
  fDrawAgari = Work->fDrawAgari;
  switch (fDrawAgari)
  {
    case 1:
      if (pAgari->tsumo)
      {
        v83 = *v171;
        LocalizeText = GetLocalizeText(v83, 1);
        v85 = pAgari;
        MenuWin_agari_cent_SetParam_Tsumo(mjnUImanager, LocalizeText, Work->players[pAgari->playerIndex]->name, 0);
        yaku = pAgari->yaku;
        if (yaku[28])
          goto LABEL_57;
      }
      else
      {
        v98 = mjnUImanager;
        v99 = *v169;
        v100 = GetLocalizeText(v99, 1);
        v101 = GetLocalizeText(*v76, 1);
        v102 = v100;
        v85 = pAgari;
        m_Items = Work->players;
        MenuWin_agari_cent_SetParam_Ron(v98, v102, v101, m_Items[pAgari->playerIndex]->devilID, m_Items[pAgari->fromPlayerIndex]->devilID, 0);
        yaku = pAgari->yaku;
        if (yaku[28])
          goto LABEL_57;
      }
      if (yaku[29] || yaku[30] || yaku[31] || yaku[32] || yaku[33] || yaku[34] || yaku[35])
      {
LABEL_57:
        v104 = 0;
        yakuNum = v85->yakuNum;
        v106 = yakuNum - 3;
        goto LABEL_58;
      }
      if (yaku[36] || yaku[37])
      {
        v104 = 0;
        v85 = pAgari;
        yakuNum = pAgari->yakuNum;
        v106 = yakuNum - 3;
        if ((u32)(yakuNum - 3) > 0x31)
          goto LABEL_141;
LABEL_58:
        switch (v106)
        {
          case 0:
            fu = v85->fu;
            if (fu < 70)
              goto LABEL_126;
            goto LABEL_132;
          case 1:
            fu = v85->fu;
            if (fu >= 40)
              goto LABEL_132;
LABEL_126:
            fu = v85->fu;
            p_mjnUImanager = &mjnUImanager;
            data = fu;
            v137 = p_mjnUImanager;
            v138 = Box(s32, &data);
            v139 = Format("{0}", v138, 0);
            v140 = *v161;
            v141 = GetLocalizeText(v140, 1);
            v142 = Concat_54766928(v139, v141, 0);
            v174 = pAgari->yakuNum;
            v143 = Box(s32, &v174);
            v144 = Format("{0}", v143, 0);
            v145 = GetLocalizeText(*v162, 1);
            v146 = Concat_54766928(v144, v145, 0);
            v147 = v142;
            v85 = pAgari;
            MenuWin_agari_cent_FuHan(v137, v147, v146, 0);
            goto LABEL_65;
          case 2:
LABEL_132:
            v107 = v165;
            goto LABEL_60;
          case 3:
          case 4:
            v107 = v164;
            goto LABEL_60;
          case 5:
          case 6:
          case 7:
            v107 = v166;
            goto LABEL_60;
          case 8:
          case 9:
            v107 = v163;
            goto LABEL_60;
          case 10:
          case 11:
          case 12:
          case 13:
          case 14:
          case 15:
          case 16:
          case 17:
          case 18:
          case 19:
          case 20:
          case 21:
          case 22:
            v107 = v170;
            goto LABEL_60;
          case 23:
          case 24:
          case 25:
          case 26:
          case 27:
          case 28:
          case 29:
          case 30:
          case 31:
          case 32:
          case 33:
          case 34:
          case 35:
            if (v104)
              goto LABEL_118;
            v109 = *v168;
            if (!v133)
              break;
            goto LABEL_62;
          case 36:
          case 37:
          case 38:
          case 39:
          case 40:
          case 41:
          case 42:
          case 43:
          case 44:
          case 45:
          case 46:
          case 47:
          case 48:
            if (v104)
              goto LABEL_118;
            v109 = *v167;
            if (!v133)
              break;
            goto LABEL_62;
          case 49:
            if (v104)
            {
LABEL_118:
              v109 = *v170;
              if (v133)
                goto LABEL_62;
            }
            else
            {
              v109 = *v160;
              if (v133)
                goto LABEL_62;
            }
            break;
          default:
            goto LABEL_141;
        }
LABEL_62:
        v110 = GetLocalizeText(v109, 1);
        MenuWin_agari_cent_Topyaku(mjnUImanager, v110, 0);
        goto LABEL_65;
      }
      v104 = yaku[38] == 0;
      v85 = pAgari;
      yakuNum = pAgari->yakuNum;
      v106 = yakuNum - 3;
      if ((u32)(yakuNum - 3) <= 0x31)
        goto LABEL_58;
LABEL_141:
      if (yakuNum >= 52)
      {
        v107 = v160;
LABEL_60:
        v109 = *v107;
        goto LABEL_62;
      }
      v149 = mjnUImanager;
      data = v85->fu;
      v150 = Box(s32, &data);
      v151 = v85;
      v152 = Format("{0}", v150, 0);
      v153 = *v161;
      v154 = GetLocalizeText(v153, 1);
      v155 = Concat_54766928(v152, v154, 0);
      v174 = v151->yakuNum;
      v156 = Box(s32, &v174);
      v157 = Format("{0}", v156, 0);
      v158 = GetLocalizeText(*v162, 1);
      v159 = Concat_54766928(v157, v158, 0);
      MenuWin_agari_cent_FuHan(v149, v155, v159, 0);
      v85 = v151;
LABEL_65:
      v112 = 0;
      v113 = 0;
      do
      {
        v118 = v85->yaku[v112];
        if (v118)
        {
          if ((u32)v112 == 11 || (u32)v112 == 6)
          {
            v119 = (v172 + 8 * v113);
            v121 = *v119;
            v122 = yakuMsgTable[v112];
            v114 = GetLocalizeText(v122, 1);
            data = pAgari->yaku[v112];
            v115 = Box(s32, &data);
            v116 = Format("{0}", v115, 0);
            v117 = Concat_54831728(v121, v114, v116, 0);
LABEL_67:
            *v119 = v117;
            ++v113;
            v85 = pAgari;
            goto LABEL_68;
          }
          if (v112 <= 0x1F)
          {
            if ((u32)v112 == 28)
            {
              v119 = (v172 + 8 * v113);
              v125 = *v119;
              if (v118 == 26)
              {
                v126 = yakuMsgTable[41];
                goto LABEL_92;
              }
              goto LABEL_103;
            }
            if ((u32)v112 == 31)
            {
              v119 = (v172 + 8 * v113);
              v125 = *v119;
              if (v118 == 26)
              {
                v126 = yakuMsgTable[43];
                goto LABEL_92;
              }
              goto LABEL_103;
            }
          }
          else
          {
            if ((u32)v112 == 34)
            {
              v119 = (v172 + 8 * v113);
              v125 = *v119;
              if (v118 == 26)
              {
                v126 = yakuMsgTable[39];
              }
              else
              {
                v126 = yakuMsgTable[40];
              }
              goto LABEL_92;
            }
            if ((u32)v112 == 38)
            {
              v119 = (v172 + 8 * v113);
              v125 = *v119;
              if (v118 == 26)
              {
                v126 = yakuMsgTable[42];
                goto LABEL_92;
              }
LABEL_103:
              if (v124)
                goto LABEL_91;
              goto LABEL_90;
            }
          }
          v119 = (v172 + 8 * v113);
          v125 = *v119;
LABEL_91:
          v126 = yakuMsgTable[v112];
LABEL_92:
          v127 = GetLocalizeText(v126, 1);
          v117 = Concat_54766928(v125, v127, 0);
          goto LABEL_67;
LABEL_90:
          goto LABEL_91;
        }
LABEL_68:
        ++v112;
      }
      while (v112 != 39);
      Work_local = Work;
      Work_local->yakuListLength = v113;
      Work_local->yakuList = v3;
      MenuWin_agari_cent_SetYaku(mjnUImanager, Work->yakuTopNo, Work->yakuList, 0);
      return;
    case 2:
      v89 = *v62;
      v90 = GetLocalizeText(v89, 1);
      MenuWin_agari_Huriten(mjnUImanager, v90, 0);
      return;
    case 3:
      v87 = *v64;
      goto LABEL_27;
    case 4:
      v87 = *v66;
      goto LABEL_27;
    case 5:
      return;
    case 6:
      v87 = *v70;
      goto LABEL_27;
    case 7:
      v87 = *v72;
      goto LABEL_27;
    case 8:
      v87 = *v74;
      goto LABEL_27;
    case 9:
      v94 = *v78;
      v95 = GetLocalizeText(v94, 1);
      MenuWin_agari_cent_Special(mjnUImanager, v95, 0);
      MenuWin_agari_GrayRaido(mjnUImanager, 0);
      return;
    default:
      if (fDrawAgari != 4096)
        return;
      v87 = *v68;
LABEL_27:
      v92 = GetLocalizeText(v87, 1);
      MenuWin_agari_cent_Special(mjnUImanager, v92, 0);
      return;
  }
}

// 0x1d163e0
static void DrawInfo(void) {
  char *v1;
  char *v2;
  char **v3;
  char **v4;
  char *v5;
  char *v6;
  char **v7;
  char *v8;
  char **v9;
  char *v10;
  char *v11;
  char **v12;
  char *v13;
  char *v14;
  char *v18;
  s32 v20;
  Il2CppObject *v21;
  char *v22;
  char *v23;
  char *LocalizeText;
  char *v25;
  Il2CppObject *v26;
  char *v27;
  char *v28;
  char *v29;
  char *v31;
  char *v33;
  Il2CppObject *v35;
  char *v36;
  char *v37;
  char *v38;
  s32 reachBou;
  char *v42;
  char *v43;
  s32 v45;
  Il2CppObject *v46;
  char *v47;
  Il2CppObject *v48;
  char *v49;
  char *v50;
  Il2CppObject *v51;
  char *v52;
  char *ba_;
  s32 honba;
  s32 data;

  v1 = NewSpecific(string, 8u);
  v2 = "MJN_INFOMSG_L0000";
  v3 = v1;
  v1[0] = "MJN_INFOMSG_L0000";
  v4 = &v1[0];
  v5 = "MJN_INFOMSG_L0001";
  v3[5] = "MJN_INFOMSG_L0001";
  v6 = "MJN_INFOMSG_L0002";
  v3[6] = "MJN_INFOMSG_L0002";
  v7 = v3 + 6;
  v8 = "MJN_INFOMSG_L0003";
  v3[7] = "MJN_INFOMSG_L0003";
  v9 = v3 + 7;
  v10 = "MJN_INFOMSG_L0004";
  v3[8] = "MJN_INFOMSG_L0004";
  v11 = "MJN_INFOMSG_L0005";
  v3[9] = "MJN_INFOMSG_L0005";
  v12 = v3 + 9;
  v13 = "MJN_INFOMSG_L0006";
  v3[10] = "MJN_INFOMSG_L0006";
  v14 = "MJN_INFOMSG_L0007";
  v3[11] = "MJN_INFOMSG_L0007";
  MenuWin_play_SetActive(mjnUImanager, 1, 0);
  if (Work->kyoku <= 3)
  {
    v18 = *v4;
    goto LABEL_12;
  }
  else
  {
    v18 = v3[5];
    goto LABEL_12;
  }
LABEL_12:
  ba_ = GetLocalizeText(v18, 1);
  if (GetLanguageTYPE())
  {
    v20 = Work->kyoku & 3;
    if (Work->kyoku <= 0)
      v20 = -(-LOBYTE(Work->kyoku) & 3);
    data = v20 + 1;
    v21 = Box(s32, &data);
    v22 = Format("{0}", v21, 0);
    v23 = *v7;
    LocalizeText = GetLocalizeText(v23, 1);
    v25 = Concat_54766928(v22, LocalizeText, 0);
    honba = Work->honba;
    v26 = Box(s32, &honba);
    v27 = Format("{0}", v26, 0);
    v28 = GetLocalizeText(*v9, 1);
    v29 = Concat_54766928(v27, v28, 0);
  }
  else
  {
    v42 = *v7;
    v43 = GetLocalizeText(v42, 1);
    v45 = Work->kyoku & 3;
    if (Work->kyoku <= 0)
      v45 = -(-LOBYTE(Work->kyoku) & 3);
    data = v45 + 1;
    v46 = Box(s32, &data);
    v47 = Format("{0}", v46, 0);
    v25 = Concat_54831728(v43, " ", v47, 0);
    honba = Work->honba;
    v48 = Box(s32, &honba);
    v49 = Format("{0}", v48, 0);
    v50 = GetLocalizeText(*v9, 1);
    v29 = Concat_54831728(v49, " ", v50, 0);
  }
  v31 = v3[8];
  v33 = GetLocalizeText(v31, 1);
  data = Work->yamaNum;
  v35 = Box(s32, &data);
  v36 = Format("{0}", v35, 0);
  v37 = GetLocalizeText(*v12, 1);
  v38 = "{0}";
  if (Work->hideReachBou == -1)
  {
    reachBou = Work->reachBou;
  }
  else
  {
    reachBou = Work->reachBou - 1;
  }
  data = reachBou;
  v51 = Box(s32, &data);
  v52 = Format(v38, v51, 0);
  MenuWin_play_SetInfo(mjnUImanager, ba_, v25, v29, v33, v36, v37, v52, 0);
}

// 0x1d15310
static void DrawEndHanchan(void) {
  char *LocalizeText;
  s64 v6;
  Player_t *v7;
  s32 tensu;
  s32 tensu2;
  void *p_mjnUImanager;
  void *v13;
  Work_t *v15;
  s64 v16;
  Player_t *v17;
  s32 v18;
  s32 v19;
  void *v21;
  void *v23;
  Work_t *v25;
  s64 v26;
  Player_t *v27;
  s32 v28;
  s32 v29;
  void *v31;
  void *v33;
  Work_t *v35;
  s64 v36;
  Player_t *v37;
  s32 v38;
  s32 v39;
  void *v41;
  void *v43;

  LocalizeText = GetLocalizeText("MJN_INFOMSG_L0008", 1);
  Result_RankingList_setActive(mjnUImanager, 1, LocalizeText, 0);
  v6 = Work->ranking[0];
  v7 = Work->players[v6];
  tensu = v7->tensu;
  tensu2 = v7->tensu2;
  p_mjnUImanager = &mjnUImanager;
  v13 = p_mjnUImanager;
  Result_RankBar_SetParam(v13, 0, Work->players[v6]->name, 20000, tensu, tensu2, v6, 0);
  v15 = Work;
  v16 = v15->ranking[1];
  v17 = v15->players[v16];
  v18 = v17->tensu;
  v19 = v17->tensu2;
  v21 = &mjnUImanager;
  v23 = v21;
  Result_RankBar_SetParam(v23, 1, Work->players[v16]->name, 10000, v18, v19, v16, 0);
  v25 = Work;
  v26 = v25->ranking[2];
  v27 = v25->players[v26];
  v28 = v27->tensu;
  v29 = v27->tensu2;
  v31 = &mjnUImanager;
  v33 = v31;
  Result_RankBar_SetParam(v33, 2, Work->players[v26]->name, -10000, v28, v29, v26, 0);
  v35 = Work;
  v36 = v35->ranking[3];
  v37 = v35->players[v36];
  v38 = v37->tensu;
  v39 = v37->tensu2;
  v41 = &mjnUImanager;
  v43 = v41;
  Result_RankBar_SetParam(v43, 3, Work->players[v36]->name, -20000, v38, v39, v36, 0);
}

// 0x1d251e0
void mjnTextDraw(s32 panelNo, s32 TextPosX, s32 TextPosY, s32 TextSizeW, s32 TextSizeH, const sdfColor_t *col, char *str, s32 cursor) {
  f32 a;
  f32 b;
  f32 g;
  f32 r;
  s32 v21;
  sdfColor_t v22;

  a = col->a;
  b = col->b;
  g = col->g;
  r = col->r;
  v22.b = b;
  v22.a = a;
  if (cursor + 1 == panelNo)
    v21 = TextPosX + 24;
  else
    v21 = TextPosX;
  v22.r = r;
  v22.g = g;
  SetTextPartsDataList((f32)v21, (f32)(TextPosY - 28 * panelNo), (f32)TextSizeW, (f32)TextSizeH, v22, str, 0);
}

// 0x1d157c0
static void ApplyCamera(void) {
  CameraTargetPos = Work->cameraTargetPos;
  CameraEyePos = Work->cameraEyePos;
  CameraUpVector = Work->cameraUpVector;
}

// 0x1d252d0
static void DrawHai3DExCalc(f32 x, f32 y, f32 z, s32 hai, s32 direction, s32 highlight) {
  dds3ModelHandle_t *haiModelYama;
  Work_t *v16;
  dds3ModelHandle_t *haiModelHandle;
  s64 v18;
  void *v19;
  s64 v20;
  Work_t *v21;
  s64 v22;
  float32x2_t *v23;
  dds3ModelHandle_t *v24;
  f32 v25;
  int32x2_t v26;
  float32x2_t v27;
  f32 v28;
  f32 v29;
  f32 v30;
  f32 v31;
  Work_t *v32;
  dds3ModelHandle_t *v33;
  s64 haiModelIndex;
  dds3ModelHandle_t *v36;
  Il2CppClass **v37;
  f32 v38;
  f32 v39;
  f32 v40;
  f32 v42;
  float32x2_t v43;
  f32 v45;
  float32x2_t v47;
  f32 v48;
  u64 *v49;
  f32 v50;
  f32 v51;
  f32 v52;
  f32 *v53;
  f32 *v54;
  f32 v55;
  f32 *v56;
  f32 *v57;
  f32 *v58;
  f32 *v59;
  f32 *v60;
  f32 *v61;
  f32 *v62;
  f32 *v63;
  f32 *v64;
  f32 *v65;
  f32 *v66;
  f32 *v67;
  f32 *v68;
  f32 *v69;
  f32 *v70;
  f32 *v71;
  f32 *v72;
  f32 v73;
  f32 *v74;
  f32 v75;
  f32 *v76;
  f32 *v77;
  f32 *v78;
  f32 *v79;
  f32 *v80;
  f32 *v81;
  f32 v82;
  f32 *v83;
  f32 *v84;
  f32 *v85;
  f32 *v86;
  f32 *v87;
  f32 *v88;
  f32 *v89;
  f32 *v90;
  f32 v91;
  f32 *v92;
  f32 *v93;
  f32 *v94;
  f32 *v95;
  f32 *v96;
  f32 *v97;
  f32 *v98;
  f32 *v99;
  f32 *v100;
  f32 *v101;
  f32 *v102;
  f32 *v103;
  f32 *v104;
  f32 *v105;
  f32 *v106;
  f32 *v107;
  f32 *v108;
  f32 *v109;
  f32 *v110;
  f32 *v111;
  f32 *v112;
  f32 *v113;
  f32 *v114;
  f32 *v115;
  s64 v116;
  s64 v117;
  s64 v119;
  s64 v120;
  s64 v121;
  s64 v122;
  Work_t *v123;
  HaiDrawData_t *haiDrawData;
  s64 v125;
  s64 v126;
  Work_t *v127;
  dds3ModelHandle_t *v128;
  s64 v129;
  Il2CppClass **v130;
  f32 v132;
  float32x2_t v133;
  f32 v134;

  haiModelYama = Work->haiModelYama;
  Work->HaiIndex[Work->haiModelIndex] = hai;
  if (*((u64 *)&haiModelYama[hai] + haiModelYama->bounds[1].length * Work->haiModelIndex))
  {
    goto LABEL_7;
  }
  mjnModelLoadBuff(hai);
  v32 = Work;
  v33 = v32->haiModelYama;
  haiModelIndex = v32->haiModelIndex;
  v36 = ModelLoad(8);
  v37 = &v33->obj.klass + hai + v33->bounds[1].length * haiModelIndex;
  v37[4] = v36;
LABEL_7:
  v16 = Work;
  haiModelHandle = v16->haiModelHandle;
  v18 = v16->haiModelIndex;
  v19 = *((void **)&v16->haiModelYama[hai] + v16->haiModelYama->bounds[1].length * v18);
  v20 = (s64)haiModelHandle + 8 * v18;
  *(u64 *)(v20 + 32) = v19;
  v21 = Work;
  v22 = v21->haiModelIndex;
  v23 = v21->haiDrawData[v22];
  v24 = v21->haiModelHandle[v22];
  v25 = y + -80.0;
  v26.n64_u32[0] = hai % 9;
  v26.n64_u32[1] = hai / 9;
  v27.n64_u64[0] = vcvt_f32_s32(v26).n64_u64[0];
  FromEuler(0.0, 0.0, 0.0);
  v28 = x;
  v29 = v25;
  v30 = z;
  switch (direction)
  {
    case 0:
      break;
    case 1:
      FromEuler(0.0, 4.712389, 0.0);
      v38 = -4.0;
      goto LABEL_19;
    case 2:
      FromEuler(0.0, 3.1415927, 0.0);
      v28 = x + 4.0;
      v39 = -3.0;
      goto LABEL_21;
    case 3:
      FromEuler(0.0, 1.5707964, 0.0);
      v40 = 3.0;
      goto LABEL_23;
    case 4:
      FromEuler(4.712389, 0.0, 0.0);
      v38 = -5.2;
LABEL_19:
      v30 = z + v38;
      v28 = x;
      v29 = v25;
      break;
    case 5:
      FromEuler(4.712389, 4.712389, 0.0);
      v28 = x + 5.2;
      v39 = -4.0;
LABEL_21:
      v30 = z + v39;
      v29 = v25;
      break;
    case 6:
      FromEuler(4.712389, 3.1415927, 0.0);
      v40 = 4.0;
LABEL_23:
      v28 = x + v40;
      v29 = v25;
      goto LABEL_29;
    case 7:
      FromEuler(4.712389, 1.5707964, 0.0);
      v28 = x;
      v29 = v25;
      goto LABEL_29;
    case 8:
    case 9:
      FromEuler(1.5707964, 0.0, 0.0);
      v31 = -3.0;
      v28 = x;
      goto LABEL_28;
    case 10:
      FromEuler(1.5707964, 4.712389, 0.0);
      v28 = x;
      v29 = v25 + -3.0;
      v30 = z + -4.0;
      break;
    case 11:
      FromEuler(1.5707964, 3.1415927, 0.0);
      v28 = x + 4.0;
      v29 = v25 + -3.0;
      v30 = z + -5.2;
      break;
    case 12:
      FromEuler(1.5707964, 1.5707964, 0.0);
      v28 = x + 5.2;
      v31 = -3.0;
LABEL_28:
      v29 = v25 + v31;
LABEL_29:
      v30 = z;
      break;
    default:
      v28 = 0.0;
      v29 = 0.0;
      v30 = 0.0;
      break;
  }
  v133.n64_u64[0] = vmul_f32(v27, (float32x2_t)0x4290000042580000LL).n64_u64[0];
  mdlSetRotate(v24);
  v132 = v25;
  v42 = z;
  v43.n64_u64[0] = vadd_f32(v133, (float32x2_t)0x4290000042580000LL).n64_u64[0];
  v45 = x;
  vct_A.x = v28;
  vct_A.y = v29;
  v47.n64_u64[0] = vmul_f32(v43, (float32x2_t)0x3B0000003B000000LL).n64_u64[0];
  vct_A.z = v30;
  vct_A.w = 1.0;
  v48 = 0.001953125 * v133.n64_f32[0];
  v134 = vmuls_lane_f32(0.001953125, v133, 1);
  mdlSetPosition(v24);
  switch (direction)
  {
    case 0:
      v49 = v23[2].n64_u64[0];
      v75 = v42 + -3.0;
      v76 = v49[4];
      v77 = v49[5];
      v76[8] = v45;
      v76[9] = v132;
      v76[10] = v42;
      v77[8] = v45 + 4.0;
      v77[9] = v132;
      v77[10] = v42;
      v78 = v49[6];
      v79 = v49[7];
      v78[8] = v45;
      v78[9] = v132;
      v78[10] = v42 + -3.0;
      v79[8] = v45 + 4.0;
      v79[9] = v132;
      v79[10] = v42 + -3.0;
      v80 = v49[8];
      v81 = v49[9];
      v80[10] = v42;
      v82 = v132 + -5.2;
      v80[8] = v45;
      v80[9] = v132 + -5.2;
      v81[8] = v45 + 4.0;
      v81[9] = v132 + -5.2;
      v81[10] = v42;
      v83 = v49[10];
      v84 = v49[11];
      v83[8] = v45;
      v83[9] = v132 + -5.2;
      v83[10] = v42 + -3.0;
      v84[8] = v45 + 4.0;
      goto LABEL_52;
    case 1:
      v49 = v23[2].n64_u64[0];
      v85 = v49[4];
      v86 = v49[5];
      v85[8] = v45;
      v85[9] = v132;
      v85[10] = v42 + -4.0;
      v86[8] = v45;
      v86[9] = v132;
      v86[10] = v42;
      v87 = v49[6];
      v88 = v49[7];
      v87[8] = v45 + 3.0;
      v87[9] = v132;
      v87[10] = v42 + -4.0;
      v88[8] = v45 + 3.0;
      v88[9] = v132;
      v88[10] = v42;
      v89 = v49[8];
      v90 = v49[9];
      v89[10] = v42 + -4.0;
      v91 = v132 + -5.2;
      v89[8] = v45;
      v89[9] = v132 + -5.2;
      v90[8] = v45;
      v90[9] = v132 + -5.2;
      v90[10] = v42;
      v92 = v49[10];
      v93 = v49[11];
      v92[8] = v45 + 3.0;
      v92[9] = v132 + -5.2;
      v92[10] = v42 + -4.0;
      v93[8] = v45 + 3.0;
      goto LABEL_50;
    case 2:
      v49 = v23[2].n64_u64[0];
      v94 = v49[4];
      v95 = v49[5];
      v94[8] = v45 + 4.0;
      v94[9] = v132;
      v94[10] = v42 + -3.0;
      v95[8] = v45;
      v95[9] = v132;
      v95[10] = v42 + -3.0;
      v96 = v49[6];
      v97 = v49[7];
      v96[8] = v45 + 4.0;
      v96[9] = v132;
      v96[10] = v42;
      v97[8] = v45;
      v97[9] = v132;
      v97[10] = v42;
      v98 = v49[8];
      v99 = v49[9];
      v98[10] = v42 + -3.0;
      v91 = v132 + -5.2;
      v98[8] = v45 + 4.0;
      v98[9] = v132 + -5.2;
      v99[8] = v45;
      v99[9] = v132 + -5.2;
      v99[10] = v42 + -3.0;
      v100 = v49[10];
      v93 = v49[11];
      v100[8] = v45 + 4.0;
      v100[9] = v132 + -5.2;
      v100[10] = v42;
      v93[8] = v45;
LABEL_50:
      v93[9] = v91;
      v93[10] = v42;
      goto LABEL_54;
    case 3:
      v49 = v23[2].n64_u64[0];
      v75 = v42 + -4.0;
      v101 = v49[4];
      v102 = v49[5];
      v101[8] = v45 + 3.0;
      v101[9] = v132;
      v101[10] = v42;
      v102[8] = v45 + 3.0;
      v102[9] = v132;
      v102[10] = v42 + -4.0;
      v103 = v49[6];
      v104 = v49[7];
      v103[8] = v45;
      v103[9] = v132;
      v103[10] = v42;
      v104[8] = v45;
      v104[9] = v132;
      v104[10] = v42 + -4.0;
      v105 = v49[8];
      v106 = v49[9];
      v105[10] = v42;
      v82 = v132 + -5.2;
      v105[8] = v45 + 3.0;
      v105[9] = v132 + -5.2;
      v106[8] = v45 + 3.0;
      v106[9] = v132 + -5.2;
      v106[10] = v42 + -4.0;
      v107 = v49[10];
      v84 = v49[11];
      v107[8] = v45;
      v107[9] = v132 + -5.2;
      v107[10] = v42;
      v84[8] = v45;
LABEL_52:
      v84[9] = v82;
      v84[10] = v75;
      goto LABEL_54;
    case 4:
    case 9:
      v49 = v23[2].n64_u64[0];
      v50 = v45;
      v51 = v132;
      v52 = v42;
      v53 = v49[4];
      v54 = v49[5];
      v53[8] = v45;
      v53[9] = v132;
      v45 = v45 + 4.0;
      v55 = v132 + -3.0;
      v53[10] = v42 + -5.2;
      v54[10] = v42 + -5.2;
      v54[8] = v45;
      v54[9] = v132;
      v56 = v49[6];
      v57 = v49[7];
      v56[8] = v50;
      v56[9] = v132 + -3.0;
      v56[10] = v42 + -5.2;
      v58 = v49[8];
      v57[8] = v45;
      v57[9] = v132 + -3.0;
      v57[10] = v42 + -5.2;
      v58[8] = v50;
      goto LABEL_45;
    case 5:
    case 10:
      v49 = v23[2].n64_u64[0];
      v52 = v42;
      v50 = v45;
      v51 = v132;
      v59 = v49[4];
      v60 = v49[5];
      v42 = v42 + -4.0;
      v59[8] = v45 + 5.2;
      v59[9] = v132;
      v55 = v132 + -3.0;
      v59[10] = v42;
      v60[8] = v45 + 5.2;
      v60[9] = v132;
      v60[10] = v52;
      v61 = v49[6];
      v62 = v49[7];
      v61[8] = v45 + 5.2;
      v61[9] = v132 + -3.0;
      v61[10] = v42;
      v58 = v49[8];
      v62[8] = v45 + 5.2;
      v62[9] = v132 + -3.0;
      v62[10] = v52;
      goto LABEL_44;
    case 6:
    case 11:
      v49 = v23[2].n64_u64[0];
      v51 = v132;
      v55 = v132 + -3.0;
      v63 = v49[4];
      v64 = v49[5];
      v63[8] = v45 + 4.0;
      v63[9] = v132;
      v63[10] = v42;
      v64[8] = v45;
      v64[9] = v132;
      v64[10] = v42;
      v65 = v49[6];
      v66 = v49[7];
      v50 = v45 + 4.0;
      v65[8] = v45 + 4.0;
      v65[9] = v132 + -3.0;
      v65[10] = v42;
      v66[8] = v45;
      v66[9] = v132 + -3.0;
      v66[10] = v42;
      v58 = v49[8];
      v58[8] = v45 + 4.0;
      v42 = v42 + -5.2;
      v52 = v42;
      goto LABEL_45;
    case 7:
    case 12:
      v49 = v23[2].n64_u64[0];
      v51 = v132;
      v55 = v132 + -3.0;
      v67 = v49[4];
      v68 = v49[5];
      v67[8] = v45;
      v67[9] = v132;
      v67[10] = v42;
      v68[8] = v45;
      v68[9] = v132;
      v68[10] = v42 + -4.0;
      v69 = v49[6];
      v70 = v49[7];
      v52 = v42 + -4.0;
      v69[8] = v45;
      v69[9] = v132 + -3.0;
      v69[10] = v42;
      v70[8] = v45;
      v70[9] = v132 + -3.0;
      v70[10] = v42 + -4.0;
      v58 = v49[8];
      v45 = v45 + 5.2;
      v50 = v45;
LABEL_44:
      v58[8] = v45;
LABEL_45:
      v58[9] = v51;
      v58[10] = v42;
      v71 = v49[9];
      v72 = v49[10];
      v73 = v134;
      v71[8] = v45;
      v71[9] = v51;
      v71[10] = v52;
      v74 = v49[11];
      v72[8] = v50;
      v72[9] = v55;
      v72[10] = v42;
      v74[8] = v45;
      v74[9] = v55;
      v74[10] = v52;
      goto LABEL_55;
    case 8:
      v49 = v23[2].n64_u64[0];
      v108 = v49[4];
      v109 = v49[5];
      v108[8] = v45 + 4.0;
      v108[9] = v132 + -3.0;
      v108[10] = v42 + -5.2;
      v109[8] = v45;
      v109[9] = v132 + -3.0;
      v109[10] = v42 + -5.2;
      v110 = v49[6];
      v111 = v49[7];
      v110[8] = v45 + 4.0;
      v110[9] = v132;
      v110[10] = v42 + -5.2;
      v111[8] = v45;
      v111[9] = v132;
      v111[10] = v42 + -5.2;
      v112 = v49[8];
      v113 = v49[9];
      v112[8] = v45 + 4.0;
      v112[9] = v132 + -3.0;
      v112[10] = v42;
      v113[8] = v45;
      v113[9] = v132 + -3.0;
      v113[10] = v42;
      v114 = v49[10];
      v115 = v49[11];
      v114[8] = v45 + 4.0;
      v114[9] = v132;
      v114[10] = v42;
      v115[8] = v45;
      v115[9] = v132;
      v115[10] = v42;
      goto LABEL_54;
    default:
      v49 = v23[2].n64_u64[0];
LABEL_54:
      v73 = v134;
LABEL_55:
      v116 = v49[4];
      v117 = v49[5];
      v23[3].n64_f32[0] = v48;
      v23[3].n64_f32[1] = v73;
      v23[4].n64_u64[0] = v47.n64_u64[0];
      *(u32 *)(v116 + 44) = 1065353216;
      *(u32 *)(v117 + 44) = 1065353216;
      v119 = v49[7];
      *(u32 *)(v49[6] + 44) = 1065353216;
      *(u32 *)(v119 + 44) = 1065353216;
      v120 = v49[9];
      *(u32 *)(v49[8] + 44) = 1065353216;
      v122 = v49[10];
      v121 = v49[11];
      *(u32 *)(v120 + 44) = 1065353216;
      *(u32 *)(v122 + 44) = 1065353216;
      *(u32 *)(v121 + 44) = 1065353216;
      v23[5].n64_u32[0] = highlight;
      v23[5].n64_u32[1] = 1;
      v123 = Work;
      haiDrawData = v123->haiDrawData;
      v125 = v123->haiModelIndex;
      v126 = (s64)haiDrawData + 8 * v125;
      *(u64 *)(v126 + 32) = v23;
      v127 = Work;
      v128 = v127->haiModelHandle;
      v129 = v127->haiModelIndex;
      v130 = &v128->obj.klass + v129;
      v130[4] = v24;
      ++Work->haiModelIndex;
      return;
  }
}

// 0x1d26060
static void DrawHai3DCalc(f32 x, f32 z, s32 hai, s32 direction, s32 highlight) {
  DrawHai3DExCalc(x, 0.0, z, hai, direction, highlight);
}

// 0x1d26100
static void DrawTable(void) {
  dds3ModelHandle_t *tableModelHandle;
  dds3ModelHandle_t *v7;

  vct_A = (struct sdfVector4_t)xmmword_3CFD5C0;
  tableModelHandle = Work->tableModelHandle;
  mdlSetPosition(tableModelHandle);
  v7 = Work->tableModelHandle;
  Link(v7, ModelOt[0]);
}

// 0x1d18ec0
static void DrawTehai3DCalc(void) {
  Player_t *v3;
  s64 v4;
  s32 v5;
  f32 v6;
  f32 v7;
  s32 v9;
  s64 i;
  Work_t *Work_local;
  s32 v12;
  s32 v13;
  s64 v14;
  s64 v15;
  Work_t *v16;
  s32 v17;
  Work_t *v18;
  Player_t *v19;
  s32 tehaiNum;
  s64 v21;
  bool v22;
  s32 v24;
  s64 j;
  Work_t *v26;
  s32 v27;
  s32 v29;
  s32 v30;
  Player_t *v32;
  s32 v33;
  s64 v34;
  s32 v35;
  s64 k;
  Work_t *v38;
  s32 v39;
  s32 v40;
  s32 v41;
  s32 v42;
  Player_t *v43;
  s64 v44;
  s32 v45;
  s64 m;
  Work_t *v48;
  s32 v49;
  s32 v50;
  s32 v51;
  s32 v52;

  v3 = Work->players[0];
  if (v3->tehaiNum >= 1)
  {
    v4 = 0;
    while (1)
    {
      v9 = 0;
      for (i = 8; ; ++i)
      {
        Work_local = Work;
        if (i - 8 >= Work_local->doraNum)
          break;
        v12 = v3->tehai14[v4];
        if (v12 == *((u32 *)&Work_local->dora->obj.klass + i))
          goto LABEL_12;
        v13 = v3->tehai14[v4];
        if (v13 != *((u32 *)&Work->uraDora->obj.klass + i))
          continue;
        if (!Work->agariPlayerIndex)
          goto LABEL_12;
        goto LABEL_9000;
        if (!Work->agariPlayerIndex)
        {
LABEL_12:
          v9 = 3;
          continue;
        }
LABEL_9000:
      }
      Work_local = Work;
      if (Work_local->phase != 12)
      {
        if ((v3->flag & 2) == 0)
          goto LABEL_45;
        if (Work_local->reachShanten[v4])
        {
          v9 = -1;
          goto LABEL_45;
        }
        if (v9 == 3)
          v9 = 3;
        else
          v9 = 0;
        goto LABEL_46;
      }
      v14 = 0;
      v9 = -1;
      while (1)
      {
        v16 = Work;
        if (v14 >= v16->kanNum)
          break;
        v17 = v3->tehai14[v4];
        v16 = Work;
        v15 = (s64)v16->kanHai + 4 * v14++;
        if (v17 == *(u32 *)(v15 + 32))
          v9 = 0;
      }
LABEL_45:
LABEL_46:
      v18 = Work;
      if (v4 != v18->tehaiCursor)
        goto LABEL_7;
      v18 = Work;
      if (v18->phase != 3)
        goto LABEL_66;
      if (v18->turn)
        goto LABEL_66;
      if (v18->playerPhase != 2)
        goto LABEL_66;
LABEL_70:
      v5 = v3->tehai14[v4];
      v6 = (f32)((f32)(s32)v4 * 4.0) + -35.0;
      v7 = -3.0;
      goto LABEL_10;
LABEL_66:
      if (Work->phase == 12)
        goto LABEL_70;
LABEL_7:
      v5 = v3->tehai14[v4];
      v6 = (f32)((f32)(s32)v4 * 4.0) + -35.0;
      v7 = 0.0;
LABEL_10:
      DrawHai3DExCalc(v6 + -2.0, v7, -27.0, v5, 4, v9);
      if (++v4 >= v3->tehaiNum)
      {
        break;
      }
    }
  }
  v19 = Work->players[1];
  tehaiNum = v19->tehaiNum;
  v21 = (u32)(tehaiNum - 1);
  if (tehaiNum - 1 < 0)
    goto LABEL_118;
LABEL_81:
  while (2)
  {
    if (!Work->fShowTehai[1])
      goto LABEL_106;
    goto LABEL_83;
    if (Work->fShowTehai[1])
    {
LABEL_83:
      v24 = 0;
      for (j = 8; ; ++j)
      {
        v26 = Work;
        v27 = v19->tehai14[v21];
        if (j - 8 >= v26->doraNum)
        {
          DrawHai3DExCalc(37.399998, 0.0, (f32)((f32)((f32)tehaiNum * 4.0) + -23.0) + -6.0, v27, 5, v24);
          tehaiNum = v21;
          v22 = v21-- <= 0;
          if (v22)
            goto LABEL_117;
          goto LABEL_81;
        }
        if (v27 == *((u32 *)&v26->dora->obj.klass + j))
          goto LABEL_84;
        v29 = v19->tehai14[v21];
        if (v29 != *((u32 *)&Work->uraDora->obj.klass + j))
          continue;
        if (Work->agariPlayerIndex == 1)
          goto LABEL_84;
        goto LABEL_9001;
        if (Work->agariPlayerIndex == 1)
        {
LABEL_84:
          v24 = 3;
          continue;
        }
LABEL_9001:
      }
    }
LABEL_106:
    v30 = v19->tehai14[v21];
    DrawHai3DExCalc(39.6, 0.0, (f32)((f32)((f32)tehaiNum * 4.0) + -23.0) + -6.0, v30, 1, 0);
    tehaiNum = v21;
    v22 = v21-- <= 0;
    if (!v22)
      continue;
    break;
  }
LABEL_117:
LABEL_118:
  v32 = Work->players[2];
  v33 = v32->tehaiNum;
  v34 = (u32)(v33 - 1);
  if (v33 - 1 >= 0)
  {
    v35 = 0;
    while (1)
    {
      if (Work->fShowTehai[2])
        break;
      v41 = 2;
      v42 = v32->tehai14[v34];
LABEL_148:
      DrawHai3DExCalc((f32)((f32)((f32)v33 * -4.0) + 23.0) + 9.0, 0.0, 44.0, v42, v41, v35);
      v33 = v34;
      v22 = v34-- <= 0;
      if (v22)
      {
        goto LABEL_154;
      }
    }
    v35 = 0;
    for (k = 8; ; ++k)
    {
      v38 = Work;
      if (k - 8 >= v38->doraNum)
      {
        v41 = 6;
        v42 = v32->tehai14[v34];
        goto LABEL_148;
      }
      v39 = v32->tehai14[v34];
      if (v39 == *((u32 *)&v38->dora->obj.klass + k))
        goto LABEL_128;
      v40 = v32->tehai14[v34];
      if (v40 != *((u32 *)&Work->uraDora->obj.klass + k))
        continue;
      if (Work->agariPlayerIndex == 2)
        goto LABEL_128;
      goto LABEL_9003;
      if (Work->agariPlayerIndex == 2)
      {
LABEL_128:
        v35 = 3;
        continue;
      }
LABEL_9003:
    }
  }
LABEL_154:
  v43 = Work->players[3];
  if (v43->tehaiNum >= 1)
  {
    v44 = 0;
    v45 = 0;
    while (1)
    {
      if (Work->fShowTehai[3])
        break;
      v51 = 3;
      v52 = v43->tehai14[v44];
LABEL_184:
      DrawHai3DExCalc(-43.0, 0.0, (f32)((f32)((f32)(s32)v44++ * -4.0) + 23.0) + 12.8, v52, v51, v45);
      if (v44 >= v43->tehaiNum)
        return;
    }
    v45 = 0;
    for (m = 8; ; ++m)
    {
      v48 = Work;
      if (m - 8 >= v48->doraNum)
      {
        v51 = 7;
        v52 = v43->tehai14[v44];
        goto LABEL_184;
      }
      v49 = v43->tehai14[v44];
      if (v49 == *((u32 *)&v48->dora->obj.klass + m))
        goto LABEL_164;
      v50 = v43->tehai14[v44];
      if (v50 != *((u32 *)&Work->uraDora->obj.klass + m))
        continue;
      if (Work->agariPlayerIndex == 3)
        goto LABEL_164;
      goto LABEL_9004;
      if (Work->agariPlayerIndex == 3)
      {
LABEL_164:
        v45 = 3;
        continue;
      }
LABEL_9004:
    }
  }
}

// 0x1d19aa0
static void DrawSutehai3DCalc(void) {
  Player_t *v3;
  f32 v4;
  u64 v5;
  s32 v6;
  s64 reachIndex;
  f32 v8;
  s32 v9;
  s32 v10;
  bool v11;
  f32 v12;
  Work_t *v14;
  Work_t *v15;
  s32 tehaiCursor;
  s32 v17;
  s64 v18;
  s64 v19;
  Work_t *v20;
  s32 v21;
  Player_t *v23;
  f32 v24;
  u64 v25;
  bool v27;
  f32 v28;
  Work_t *v29;
  Work_t *v30;
  s32 v31;
  s32 v32;
  Work_t *v34;
  s32 v35;
  s32 v36;
  s64 v37;
  s64 v38;
  Work_t *v39;
  s32 v40;
  Player_t *v41;
  u64 v42;
  bool v44;
  Work_t *v45;
  Work_t *v46;
  s32 v47;
  s32 v48;
  u32 v49;
  f32 v50;
  Work_t *v51;
  s32 v52;
  s32 v53;
  s64 i;
  s64 v55;
  Work_t *v56;
  s32 v57;
  Player_t *v58;
  u64 v59;
  bool v61;
  f32 v62;
  f32 v63;
  Work_t *v64;
  Work_t *v65;
  s32 v66;
  s32 v67;
  u32 v68;
  Work_t *v69;
  s32 v70;
  s32 v71;
  s64 v72;
  s64 v73;
  Work_t *v74;
  s32 v75;

  v3 = Work->players[0];
  if (v3->sutehaiIndex >= 1)
  {
    v4 = 0.0;
    v5 = 0;
    while (1)
    {
      if ((u32)v5 % 6)
        v11 = 1;
      else
        v11 = v5 > 0x11;
      if (!v11)
        v4 = -15.0;
      if (v5 <= 0x11)
        v12 = (f32)((f32)((u32)v5 / 6) * -5.3999996) + -10.0;
      else
        v12 = -20.8;
      if (Work->phase != 5)
        goto LABEL_36;
      if (Work->turn)
        goto LABEL_36;
      if (v3->tehaiNum % 3 != 2)
        goto LABEL_7;
LABEL_36:
      v14 = Work;
      if (!v14->fDrawAgari)
        goto LABEL_49;
      if (v14->pAgari->tsumo)
        goto LABEL_49;
      if (v14->turn)
        goto LABEL_49;
      if (v5 == v3->sutehaiIndex - 1)
      {
LABEL_7:
        v6 = Work->fDrawAgari != 4;
        goto LABEL_10;
      }
LABEL_49:
      v15 = Work;
      tehaiCursor = v15->tehaiCursor;
      if (tehaiCursor < 0)
      {
        v6 = 0;
        v18 = 0;
        goto LABEL_66;
      }
      v17 = v3->sutehai[v5];
      v15 = Work;
      tehaiCursor = v15->tehaiCursor;
      if (v17 == v15->players[0]->tehai14[tehaiCursor])
      {
        if (!v15->turn)
        {
          v15 = Work;
          v18 = 0;
          v6 = 2 * (v15->playerPhase == 2);
          goto LABEL_66;
        }
        v6 = 0;
        v18 = 0;
      }
      else
      {
        v6 = 0;
        v18 = 0;
      }
      while (1)
      {
LABEL_66:
        v20 = Work;
        if (v18 >= v20->doraNum)
          break;
        v21 = v3->sutehai[v5];
        v20 = Work;
        v19 = (s64)v20->dora + 4 * v18++;
        if (v21 == *(u32 *)(v19 + 32))
          v6 = 3;
      }
LABEL_10:
      reachIndex = (u32)v3->reachIndex;
      if (v5 == reachIndex)
        v8 = 5.2;
      else
        v8 = 4.0;
      if (v5 == reachIndex)
        v9 = 5;
      else
        v9 = 4;
      v10 = v3->sutehai[v5];
      DrawHai3DExCalc(v4, 0.0, v12, v10, v9, v6);
      v4 = v4 + v8;
      if ((s64)++v5 >= v3->sutehaiIndex)
      {
        goto LABEL_73;
      }
    }
  }
  v4 = 0.0;
LABEL_73:
  v23 = Work->players[1];
  if (v23->sutehaiIndex >= 1)
  {
    v24 = 0.0;
    v25 = 0;
    while (1)
    {
      if ((u32)v25 % 6)
        v27 = 1;
      else
        v27 = v25 > 0x11;
      if (!v27)
        v24 = -15.0;
      if (v25 <= 0x11)
        v28 = (f32)((f32)((u32)v25 / 6) * 5.3999996) + 20.0;
      else
        v28 = 30.8;
      v29 = Work;
      if (v29->phase != 5)
        goto LABEL_95;
      if (v29->turn != 1)
        goto LABEL_95;
      if (v25 == v23->sutehaiIndex - 1)
        goto LABEL_108;
LABEL_95:
      v30 = Work;
      if (!v30->fDrawAgari)
        goto LABEL_116;
      if (v30->pAgari->tsumo)
        goto LABEL_116;
      if (v30->turn != 1)
        goto LABEL_116;
      if (v25 == v23->sutehaiIndex - 1)
      {
LABEL_108:
        v31 = Work->fDrawAgari != 4;
        goto LABEL_111;
      }
LABEL_116:
      v34 = Work;
      v35 = v34->tehaiCursor;
      if (v35 < 0)
      {
        v31 = 0;
        v37 = 0;
        goto LABEL_133;
      }
      v36 = v23->sutehai[v25];
      v34 = Work;
      v35 = v34->tehaiCursor;
      if (v36 == v34->players[0]->tehai14[v35])
      {
        if (!v34->turn)
        {
          v34 = Work;
          v37 = 0;
          v31 = 2 * (v34->playerPhase == 2);
          goto LABEL_133;
        }
        v31 = 0;
        v37 = 0;
      }
      else
      {
        v31 = 0;
        v37 = 0;
      }
      while (1)
      {
LABEL_133:
        v39 = Work;
        if (v37 >= v39->doraNum)
          break;
        v40 = v23->sutehai[v25];
        v39 = Work;
        v38 = (s64)v39->dora + 4 * v37++;
        if (v40 == *(u32 *)(v38 + 32))
          v31 = 3;
      }
LABEL_111:
      v32 = v23->sutehai[v25];
      if (v25 == v23->reachIndex)
      {
        v24 = v24 + 5.2;
        DrawHai3DExCalc(v28, 0.0, v24, v32, 4, v31);
        if ((s64)++v25 >= v23->sutehaiIndex)
          goto LABEL_138;
      }
      else
      {
        v24 = v24 + 4.0;
        DrawHai3DExCalc(v28, 0.0, v24, v32, 5, v31);
        if ((s64)++v25 >= v23->sutehaiIndex)
        {
LABEL_138:
          goto LABEL_140;
        }
      }
    }
  }
  v24 = 0.0;
LABEL_140:
  v41 = Work->players[2];
  if (v41->sutehaiIndex < 1)
    goto LABEL_206;
  v42 = 0;
  do
  {
    while (1)
    {
      if ((u32)v42 % 6)
        v44 = 1;
      else
        v44 = v42 > 0x11;
      if (!v44)
        v4 = 15.0;
      v45 = Work;
      if (v45->phase != 5)
        goto LABEL_159;
      if (v45->turn == 2)
        goto LABEL_158;
      goto LABEL_9004;
      if (Work->turn == 2)
      {
LABEL_158:
        if (v42 == v41->sutehaiIndex - 1)
          goto LABEL_172;
      }
LABEL_9004:
LABEL_159:
      v46 = Work;
      if (!v46->fDrawAgari)
        goto LABEL_183;
      if (v46->pAgari->tsumo)
        goto LABEL_183;
      if (v46->turn != 2)
        goto LABEL_183;
      if (v42 != v41->sutehaiIndex - 1)
      {
LABEL_183:
        v51 = Work;
        v52 = v51->tehaiCursor;
        if ((v52 & 0x80000000) == 0)
          goto LABEL_185;
        v47 = 0;
        for (i = 0; ; ++i)
        {
LABEL_200:
          v56 = Work;
          if (i >= v56->doraNum)
            break;
          v57 = v41->sutehai[v42];
          v56 = Work;
          v55 = (s64)v56->dora + 4 * i;
          if (v57 == *(u32 *)(v55 + 32))
            v47 = 3;
        }
        goto LABEL_175;
LABEL_185:
        v53 = v41->sutehai[v42];
        v51 = Work;
        v52 = v51->tehaiCursor;
        if (v53 != v51->players[0]->tehai14[v52])
        {
          v47 = 0;
          i = 0;
          goto LABEL_200;
        }
        if (v51->turn)
        {
          v47 = 0;
          i = 0;
          goto LABEL_200;
        }
        v51 = Work;
        i = 0;
        v47 = 2 * (v51->playerPhase == 2);
        goto LABEL_200;
      }
LABEL_172:
      v47 = Work->fDrawAgari != 4;
LABEL_175:
      v48 = v41->sutehai[v42];
      v50 = v42 <= 0x11 ? (f32)((f32)(s32)((u32)v42 / 6 + 1) * 5.3999996) + 20.0 : 36.199997;
      if (v42 != v41->reachIndex)
        break;
      if (!v49)
      v4 = v4 + -5.2;
      DrawHai3DExCalc(v4, 0.0, v50 + -1.1999998, v48, 5, v47);
      if ((s64)++v42 >= v41->sutehaiIndex)
        goto LABEL_205;
    }
    if (!v49)
    v4 = v4 + -4.0;
    DrawHai3DExCalc(v4, 0.0, v50, v48, 6, v47);
    ++v42;
  }
  while ((s64)v42 < v41->sutehaiIndex);
LABEL_205:
LABEL_206:
  v58 = Work->players[3];
  if (v58->sutehaiIndex >= 1)
  {
    v59 = 0;
    while (1)
    {
      if ((u32)v59 % 6)
        v61 = 1;
      else
        v61 = v59 > 0x11;
      if (v61)
        v62 = v24;
      else
        v62 = 15.0;
      if (v59 <= 0x11)
        v63 = (f32)((f32)(s32)((u32)v59 / 6 + 1) * -5.3999996) + -20.0;
      else
        v63 = -36.199997;
      v64 = Work;
      if (v64->phase != 5)
        goto LABEL_231;
      if (v64->turn != 3)
        goto LABEL_231;
      if (v59 == v58->sutehaiIndex - 1)
        goto LABEL_244;
LABEL_231:
      v65 = Work;
      if (!v65->fDrawAgari)
        goto LABEL_252;
      if (v65->pAgari->tsumo)
        goto LABEL_252;
      if (v65->turn != 3)
        goto LABEL_252;
      if (v59 == v58->sutehaiIndex - 1)
      {
LABEL_244:
        v66 = Work->fDrawAgari != 4;
        goto LABEL_247;
      }
LABEL_252:
      v69 = Work;
      v70 = v69->tehaiCursor;
      if (v70 < 0)
      {
        v66 = 0;
        v72 = 0;
        goto LABEL_269;
      }
      v71 = v58->sutehai[v59];
      v69 = Work;
      v70 = v69->tehaiCursor;
      if (v71 == v69->players[0]->tehai14[v70])
      {
        if (!v69->turn)
        {
          v69 = Work;
          v72 = 0;
          v66 = 2 * (v69->playerPhase == 2);
          goto LABEL_269;
        }
        v66 = 0;
        v72 = 0;
      }
      else
      {
        v66 = 0;
        v72 = 0;
      }
      while (1)
      {
LABEL_269:
        v74 = Work;
        if (v72 >= v74->doraNum)
          break;
        v75 = v58->sutehai[v59];
        v74 = Work;
        v73 = (s64)v74->dora + 4 * v72++;
        if (v75 == *(u32 *)(v73 + 32))
          v66 = 3;
      }
LABEL_247:
      v67 = v58->sutehai[v59];
      if (v59 == v58->reachIndex)
      {
        if (!v68)
        DrawHai3DExCalc(v63 + 1.1999998, 0.0, v62, v67, 6, v66);
        v24 = v62 + -5.2;
        if ((s64)++v59 >= v58->sutehaiIndex)
          return;
      }
      else
      {
        if (!v68)
        DrawHai3DExCalc(v63, 0.0, v62, v67, 7, v66);
        v24 = v62 + -4.0;
        if ((s64)++v59 >= v58->sutehaiIndex)
          return;
      }
    }
  }
}

// 0x1d1ab50
static void DrawNakihai3DCalc(void) {
  Player_t *v3;
  Naki_t *naki;
  s64 v5;
  f32 v6;
  s64 v7;
  s64 v8;
  s64 v9;
  s64 v10;
  s32 v11;
  s32 v13;
  s64 v14;
  Work_t *v15;
  s32 v16;
  u32 v17;
  s32 v18;
  s32 v20;
  s64 v21;
  Work_t *Work_local;
  s32 v23;
  s32 v25;
  s32 v27;
  s64 i;
  Work_t *v29;
  s32 v30;
  u32 v31;
  s32 v32;
  s32 v33;
  s32 v35;
  s64 v36;
  Work_t *v37;
  s32 v38;
  u32 v39;
  s32 v40;
  s32 v41;
  s64 v43;
  Work_t *v44;
  s32 v45;
  u32 v46;
  s32 v47;
  s32 v50;
  s32 v52;
  s32 v53;
  s32 v55;
  s64 v56;
  Work_t *v57;
  s32 v58;
  u32 v59;
  s32 v60;
  s32 v64;
  s64 v65;
  Work_t *v66;
  s32 v67;
  u32 v68;
  s32 v69;
  s32 v70;
  s32 v72;
  s64 v73;
  Work_t *v74;
  s32 v75;
  u32 v76;
  s32 v77;
  s32 v81;
  s64 v82;
  Work_t *v83;
  s32 v84;
  u32 v85;
  s32 v86;
  s32 v90;
  s64 v91;
  Work_t *v92;
  s32 v93;
  u32 v94;
  s32 v95;
  f32 v97;
  s64 v100;
  Work_t *v101;
  s32 v102;
  u32 v103;
  s32 v104;
  s64 v106;
  Work_t *v107;
  s32 v108;
  s64 v110;
  Work_t *v111;
  s32 v112;
  f32 v113;
  f32 v114;
  s32 v115;
  s32 v116;
  s64 v119;
  Work_t *v120;
  s32 v121;
  u32 v122;
  s32 v123;
  s64 v125;
  Work_t *v126;
  s32 v127;
  u32 v128;
  s32 v129;
  s32 v132;
  s32 v134;
  s32 v135;
  s64 v137;
  Work_t *v138;
  s32 v139;
  u32 v140;
  s32 v141;
  f32 v143;
  s32 v144;
  f32 v145;
  s32 v148;
  s32 v150;
  s32 v153;
  s64 v155;
  Work_t *v156;
  u32 v157;
  s32 v158;
  s32 v161;
  f32 v162;
  s32 v163;
  s32 v164;
  f32 v165;
  s32 v167;
  f32 v168;
  s64 v170;
  Work_t *v171;
  s32 v172;
  u32 v173;
  s32 v174;
  s64 v176;
  Work_t *v177;
  s32 v178;
  u32 v179;
  s32 v180;
  s32 v183;
  f32 v184;
  s32 v185;
  s32 v186;
  f32 v187;
  f32 v188;
  s32 v190;
  s32 v192;
  s32 v194;
  f32 v195;
  f32 v196;
  s32 v197;
  s32 v198;
  s32 v201;
  s32 v203;
  s32 v204;
  Player_t *v205;
  Naki_t *v206;
  s64 v207;
  f32 v208;
  f32 v209;
  f32 v210;
  s32 v211;
  s32 v212;
  f32 v213;
  s64 v214;
  s64 v215;
  s64 v216;
  s64 v217;
  s32 v218;
  s32 v220;
  s64 v221;
  Work_t *v222;
  s32 v223;
  u32 v224;
  s32 v225;
  s32 v227;
  s64 v228;
  Work_t *v229;
  s32 v230;
  u32 v231;
  s32 v232;
  s32 v234;
  s64 j;
  Work_t *v236;
  s32 v237;
  u32 v238;
  s32 v239;
  s32 v240;
  s32 v242;
  s64 v243;
  Work_t *v244;
  s32 v245;
  u32 v246;
  s32 v247;
  s32 v248;
  s32 v250;
  s64 v251;
  Work_t *v252;
  s32 v253;
  u32 v254;
  s32 v255;
  s32 v258;
  s32 v260;
  s32 v262;
  s32 v264;
  s64 v265;
  Work_t *v266;
  s32 v267;
  u32 v268;
  s32 v269;
  s32 v273;
  s64 v274;
  Work_t *v275;
  s32 v276;
  u32 v277;
  s32 v278;
  s32 v282;
  s64 v283;
  Work_t *v284;
  s32 v285;
  u32 v286;
  s32 v287;
  s32 v291;
  s64 v292;
  Work_t *v293;
  s32 v294;
  u32 v295;
  s32 v296;
  s64 v300;
  Work_t *v301;
  s32 v302;
  u32 v303;
  s32 v304;
  s64 v306;
  Work_t *v307;
  s32 v308;
  s64 v310;
  Work_t *v311;
  s32 v312;
  f32 v313;
  f32 v314;
  s32 v315;
  s32 v316;
  s64 v318;
  Work_t *v319;
  s32 v320;
  u32 v321;
  s32 v322;
  s64 v324;
  Work_t *v325;
  s32 v326;
  u32 v327;
  s32 v328;
  s32 v331;
  s32 v333;
  f32 v334;
  s32 v337;
  s32 v339;
  s32 v340;
  s32 v343;
  s32 v344;
  s64 v347;
  Work_t *v348;
  s32 v349;
  u32 v350;
  s32 v351;
  s32 v354;
  s32 v355;
  s64 v357;
  Work_t *v358;
  s32 v359;
  u32 v360;
  s32 v361;
  s32 v364;
  s32 v367;
  Player_t *v368;
  Naki_t *v369;
  s64 v370;
  f32 v371;
  f32 v372;
  s32 v373;
  s32 v374;
  f32 v375;
  s64 v376;
  s64 v377;
  s64 v378;
  s64 v379;
  s32 v380;
  s32 v382;
  s64 v383;
  Work_t *v384;
  s32 v385;
  u32 v386;
  s32 v387;
  s32 v389;
  s64 v390;
  Work_t *v391;
  s32 v392;
  u32 v393;
  s32 v394;
  s32 v396;
  s64 k;
  Work_t *v398;
  s32 v399;
  u32 v400;
  s32 v401;
  s32 v402;
  s32 v404;
  s64 v405;
  Work_t *v406;
  s32 v407;
  u32 v408;
  s32 v409;
  s32 v410;
  s32 v412;
  s64 v413;
  Work_t *v414;
  s32 v415;
  u32 v416;
  s32 v417;
  s32 v420;
  s32 v422;
  s32 v424;
  s32 v426;
  s64 v427;
  Work_t *v428;
  s32 v429;
  u32 v430;
  s32 v431;
  s32 v435;
  s64 v436;
  Work_t *v437;
  s32 v438;
  u32 v439;
  s32 v440;
  s32 v444;
  s64 v445;
  Work_t *v446;
  s32 v447;
  u32 v448;
  s32 v449;
  s32 v453;
  s64 v454;
  Work_t *v455;
  s32 v456;
  u32 v457;
  s32 v458;
  s64 v462;
  Work_t *v463;
  s32 v464;
  u32 v465;
  s32 v466;
  s64 v468;
  Work_t *v469;
  s32 v470;
  s64 v472;
  Work_t *v473;
  s32 v474;
  f32 v475;
  s32 v476;
  s32 v477;
  s64 v479;
  Work_t *v480;
  s32 v481;
  u32 v482;
  s32 v483;
  s64 v485;
  Work_t *v486;
  s32 v487;
  u32 v488;
  s32 v489;
  s32 v492;
  s32 v494;
  f32 v495;
  s32 v498;
  s32 v499;
  s32 v502;
  s32 v504;
  s32 v505;
  s64 v508;
  Work_t *v509;
  s32 v510;
  u32 v511;
  s32 v512;
  s32 v515;
  s64 v517;
  Work_t *v518;
  s32 v519;
  u32 v520;
  s32 v521;
  s32 v524;
  s32 v525;
  s32 v528;
  Player_t *v529;
  Naki_t *v530;
  s64 v531;
  f32 v532;
  f32 v533;
  s32 v534;
  s32 v535;
  f32 v536;
  s64 v537;
  s64 v538;
  s64 v539;
  s64 v540;
  s32 v541;
  s32 v543;
  s64 v544;
  Work_t *v545;
  s32 v546;
  u32 v547;
  s32 v548;
  s32 v550;
  s64 v551;
  Work_t *v552;
  s32 v553;
  u32 v554;
  s32 v555;
  s32 v557;
  s64 m;
  Work_t *v559;
  s32 v560;
  u32 v561;
  s32 v562;
  s32 v563;
  s32 v565;
  s64 v566;
  Work_t *v567;
  s32 v568;
  u32 v569;
  s32 v570;
  s32 v571;
  s32 v573;
  s64 v574;
  Work_t *v575;
  s32 v576;
  u32 v577;
  s32 v578;
  s32 v581;
  s32 v583;
  s32 v585;
  s32 v587;
  s64 v588;
  Work_t *v589;
  s32 v590;
  u32 v591;
  s32 v592;
  s32 v596;
  s64 v597;
  Work_t *v598;
  s32 v599;
  u32 v600;
  s32 v601;
  s32 v605;
  s64 v606;
  Work_t *v607;
  s32 v608;
  u32 v609;
  s32 v610;
  s32 v614;
  s64 v615;
  Work_t *v616;
  s32 v617;
  u32 v618;
  s32 v619;
  f32 v621;
  s64 v624;
  Work_t *v625;
  s32 v626;
  u32 v627;
  s32 v628;
  s64 v630;
  Work_t *v631;
  s32 v632;
  s64 v634;
  Work_t *v635;
  s32 v636;
  f32 v637;
  s32 v638;
  s32 v639;
  s64 v641;
  Work_t *v642;
  s32 v643;
  u32 v644;
  s32 v645;
  s64 v647;
  Work_t *v648;
  s32 v649;
  u32 v650;
  s32 v651;
  s32 v654;
  s32 v655;
  s32 v656;
  f32 v657;
  f32 v658;
  s32 v660;
  s32 v662;
  s32 v663;
  s32 v666;
  s32 v668;
  s32 v669;
  s64 v672;
  Work_t *v673;
  s32 v674;
  u32 v675;
  s32 v676;
  s32 v679;
  s64 v681;
  Work_t *v682;
  s32 v683;
  u32 v684;
  s32 v685;
  s32 v688;
  f32 v689;
  s32 v690;
  s32 v693;

  v3 = Work->players[0];
  if (v3->nakiNum >= 1)
  {
    naki = v3->naki;
    v5 = 0;
    v6 = 42.5;
    while (1)
    {
      v7 = (s64)naki + 8 * v5;
      v10 = *(u64 *)(v7 + 32);
      v9 = v7 + 32;
      v8 = v10;
      v11 = *(u32 *)(v10 + 16);
      if (v11 <= 32)
      {
        if (v11 != 32)
        {
          if (v11 != 8)
          {
            if (v11 != 4)
              goto LABEL_10;
            v20 = 0;
            v21 = 8;
            while (2)
            {
              Work_local = Work;
              v23 = *(u32 *)(*(u64 *)(*(u64 *)v9 + 24) + 32);
              if (v21 - 8 >= Work_local->doraNum)
              {
                DrawHai3DExCalc(v6 + -4.0, 0.0, -33.0, v23, 4, v20);
                v50 = *(u32 *)(*(u64 *)(*(u64 *)v9 + 24) + 32);
                DrawHai3DExCalc(v6 + -8.0, 0.0, -33.0, v50, 9, v20);
                v52 = *(u32 *)(*(u64 *)(*(u64 *)v9 + 24) + 32);
                DrawHai3DExCalc(v6 + -12.0, 0.0, -33.0, v52, 9, v20);
                v53 = *(u32 *)(*(u64 *)(*(u64 *)v9 + 24) + 32);
                v6 = v6 + -16.0;
                DrawHai3DExCalc(v6, 0.0, -33.0, v53, 4, v20);
                goto LABEL_10;
              }
              if (v23 == *((u32 *)&Work_local->dora->obj.klass + v21))
                break;
              v25 = *(u32 *)(*(u64 *)(*(u64 *)v9 + 24) + 32);
              if (v25 != *((u32 *)&Work->uraDora->obj.klass + v21))
                goto LABEL_39;
              if (!Work->agariPlayerIndex)
                break;
LABEL_39:
              ++v21;
              continue;
            }
            v20 = 3;
            goto LABEL_39;
          }
          v33 = *(u32 *)(v8 + 20);
          if (v33 != 1)
          {
            if (v33 != 3)
            {
              if (v33 != 2)
                goto LABEL_490;
              v35 = 0;
              v36 = 8;
              while (2)
              {
                v37 = Work;
                v38 = *(u32 *)(*(u64 *)(*(u64 *)v9 + 24) + 32);
                if (v36 - 8 >= v37->doraNum)
                {
                  if (v39)
                  {
                    goto LABEL_360;
                  }
                  else
                  {
LABEL_360:
                  }
                  DrawHai3DExCalc(v6 + -4.0, 0.0, -33.0, v38, 4, v35);
                  v132 = *(u32 *)(*(u64 *)(*(u64 *)v9 + 24) + 32);
                  DrawHai3DExCalc((f32)(v6 + -5.2) + -4.0, 0.0, -34.2, v132, 7, v35);
                  v134 = *(u32 *)(*(u64 *)(*(u64 *)v9 + 24) + 32);
                  DrawHai3DExCalc((f32)(v6 + -5.2) + -4.0, 0.0, -30.2, v134, 7, v35);
                  v135 = *(u32 *)(*(u64 *)(*(u64 *)v9 + 24) + 40);
                  v113 = (f32)(v6 + -5.2) + -8.0;
LABEL_488:
                  v114 = -33.0;
                  v115 = v135;
                  v116 = 4;
                  goto LABEL_489;
                }
                if (v39)
                {
                  if (v38 == *((u32 *)&v37->dora->obj.klass + v36))
                    break;
LABEL_90:
                  v40 = *(u32 *)(*(u64 *)(*(u64 *)v9 + 24) + 32);
                  if (v40 != *((u32 *)&Work->uraDora->obj.klass + v36))
                    goto LABEL_82;
                  if (!Work->agariPlayerIndex)
                    break;
LABEL_82:
                  ++v36;
                  continue;
                }
                else
                {
                  if (v38 != *((u32 *)&Work->dora->obj.klass + v36))
                    goto LABEL_90;
                }
                break;
              }
              v35 = 3;
              goto LABEL_82;
            }
            v35 = 0;
            v125 = 8;
            while (2)
            {
              v126 = Work;
              v127 = *(u32 *)(*(u64 *)(*(u64 *)v9 + 24) + 32);
              if (v125 - 8 >= v126->doraNum)
              {
                if (v128)
                {
                  goto LABEL_421;
                }
                else
                {
LABEL_421:
                }
                DrawHai3DExCalc(v6 + -4.0, 0.0, -33.0, v127, 4, v35);
                v148 = *(u32 *)(*(u64 *)(*(u64 *)v9 + 24) + 32);
                DrawHai3DExCalc(v6 + -8.0, 0.0, -33.0, v148, 4, v35);
                v150 = *(u32 *)(*(u64 *)(*(u64 *)v9 + 24) + 32);
                DrawHai3DExCalc((f32)(v6 + -5.2) + -8.0, 0.0, -34.2, v150, 7, v35);
                v102 = *(u32 *)(*(u64 *)(*(u64 *)v9 + 24) + 32);
                v114 = -30.2;
                v113 = (f32)(v6 + -5.2) + -8.0;
                goto LABEL_314;
              }
              if (v128)
              {
                if (v127 == *((u32 *)&v126->dora->obj.klass + v125))
                  break;
LABEL_349:
                v129 = *(u32 *)(*(u64 *)(*(u64 *)v9 + 24) + 32);
                if (v129 != *((u32 *)&Work->uraDora->obj.klass + v125))
                  goto LABEL_341;
                if (!Work->agariPlayerIndex)
                  break;
LABEL_341:
                ++v125;
                continue;
              }
              else
              {
                if (v127 != *((u32 *)&Work->dora->obj.klass + v125))
                  goto LABEL_349;
              }
              break;
            }
            v35 = 3;
            goto LABEL_341;
          }
          v35 = 0;
          v119 = 8;
          while (2)
          {
            v120 = Work;
            v121 = *(u32 *)(*(u64 *)(*(u64 *)v9 + 24) + 32);
            if (v119 - 8 >= v120->doraNum)
            {
              if (v122)
              {
                goto LABEL_413;
              }
              else
              {
LABEL_413:
              }
              v143 = v6 + -5.2;
              DrawHai3DExCalc(v6 + -5.2, 0.0, -34.2, v121, 7, v35);
              v144 = *(u32 *)(*(u64 *)(*(u64 *)v9 + 24) + 32);
              v145 = -30.2;
LABEL_478:
              DrawHai3DExCalc(v143, 0.0, v145, v144, 7, v35);
              v167 = *(u32 *)(*(u64 *)(*(u64 *)v9 + 24) + 32);
              v165 = v143 + -4.0;
              v162 = -33.0;
              v163 = v167;
              v164 = 4;
LABEL_483:
              DrawHai3DExCalc(v165, 0.0, v162, v163, v164, v35);
              v135 = *(u32 *)(*(u64 *)(*(u64 *)v9 + 24) + 32);
              v113 = v143 + -8.0;
              goto LABEL_488;
            }
            if (v122)
            {
              if (v121 == *((u32 *)&v120->dora->obj.klass + v119))
                break;
LABEL_330:
              v123 = *(u32 *)(*(u64 *)(*(u64 *)v9 + 24) + 32);
              if (v123 != *((u32 *)&Work->uraDora->obj.klass + v119))
                goto LABEL_322;
              if (!Work->agariPlayerIndex)
                break;
LABEL_322:
              ++v119;
              continue;
            }
            else
            {
              if (v121 != *((u32 *)&Work->dora->obj.klass + v119))
                goto LABEL_330;
            }
            break;
          }
          v35 = 3;
          goto LABEL_322;
        }
        v41 = *(u32 *)(v8 + 20);
        if (v41 != 1)
        {
          if (v41 != 3)
          {
            if (v41 != 2)
              goto LABEL_490;
            v35 = 0;
            v43 = 8;
            while (2)
            {
              v44 = Work;
              v45 = *(u32 *)(*(u64 *)(*(u64 *)v9 + 24) + 32);
              if (v43 - 8 >= v44->doraNum)
              {
                if (v46)
                {
                  goto LABEL_468;
                }
                else
                {
LABEL_468:
                }
                DrawHai3DExCalc(v6 + -4.0, 0.0, -33.0, v45, 4, v35);
                v161 = *(u32 *)(*(u64 *)(*(u64 *)v9 + 24) + 32);
                v162 = -34.2;
                v163 = v161;
                v164 = 7;
                v143 = v6 + -5.2;
                v165 = (f32)(v6 + -5.2) + -4.0;
                goto LABEL_483;
              }
              if (v46)
              {
                if (v45 == *((u32 *)&v44->dora->obj.klass + v43))
                  break;
LABEL_112:
                v47 = *(u32 *)(*(u64 *)(*(u64 *)v9 + 24) + 32);
                if (v47 != *((u32 *)&Work->uraDora->obj.klass + v43))
                  goto LABEL_104;
                if (!Work->agariPlayerIndex)
                  break;
LABEL_104:
                ++v43;
                continue;
              }
              else
              {
                if (v45 != *((u32 *)&Work->dora->obj.klass + v43))
                  goto LABEL_112;
              }
              break;
            }
            v35 = 3;
            goto LABEL_104;
          }
          v35 = 0;
          v137 = 8;
          while (2)
          {
            v138 = Work;
            v139 = *(u32 *)(*(u64 *)(*(u64 *)v9 + 24) + 32);
            if (v137 - 8 >= v138->doraNum)
            {
              if (v140)
              {
                goto LABEL_437;
              }
              else
              {
LABEL_437:
              }
              DrawHai3DExCalc(v6 + -4.0, 0.0, -33.0, v139, 4, v35);
              v153 = *(u32 *)(*(u64 *)(*(u64 *)v9 + 24) + 32);
              DrawHai3DExCalc(v6 + -8.0, 0.0, -33.0, v153, 4, v35);
              v102 = *(u32 *)(*(u64 *)(*(u64 *)v9 + 24) + 32);
              v113 = (f32)(v6 + -5.2) + -8.0;
              goto LABEL_313;
            }
            if (v140)
            {
              if (v139 == *((u32 *)&v138->dora->obj.klass + v137))
                break;
LABEL_384:
              v141 = *(u32 *)(*(u64 *)(*(u64 *)v9 + 24) + 32);
              if (v141 != *((u32 *)&Work->uraDora->obj.klass + v137))
                goto LABEL_376;
              if (!Work->agariPlayerIndex)
                break;
LABEL_376:
              ++v137;
              continue;
            }
            else
            {
              if (v139 != *((u32 *)&Work->dora->obj.klass + v137))
                goto LABEL_384;
            }
            break;
          }
          v35 = 3;
          goto LABEL_376;
        }
        v35 = 0;
        v155 = 8;
        while (2)
        {
          v156 = Work;
          v144 = *(u32 *)(*(u64 *)(*(u64 *)v9 + 24) + 32);
          if (v155 - 8 >= v156->doraNum)
          {
            if (v157)
            {
              goto LABEL_476;
            }
            else
            {
LABEL_476:
            }
            v145 = -34.2;
            v143 = v6 + -5.2;
            goto LABEL_478;
          }
          if (v157)
          {
            if (v144 == *((u32 *)&v156->dora->obj.klass + v155))
              break;
LABEL_457:
            v158 = *(u32 *)(*(u64 *)(*(u64 *)v9 + 24) + 32);
            if (v158 != *((u32 *)&Work->uraDora->obj.klass + v155))
              goto LABEL_449;
            if (!Work->agariPlayerIndex)
              break;
LABEL_449:
            ++v155;
            continue;
          }
          else
          {
            if (v144 != *((u32 *)&Work->dora->obj.klass + v155))
              goto LABEL_457;
          }
          break;
        }
        v35 = 3;
        goto LABEL_449;
      }
      if ((u32)v11 > 0x10000080)
      {
        if (v11 != 268435712)
        {
          if (v11 != 268435968)
            goto LABEL_10;
          v13 = 0;
          v14 = 8;
          while (2)
          {
            v15 = Work;
            v16 = *(u32 *)(*(u64 *)(*(u64 *)v9 + 24) + 40);
            if (v14 - 8 >= v15->doraNum)
            {
              if (v17)
              {
                goto LABEL_155;
              }
              else
              {
LABEL_155:
              }
              DrawHai3DExCalc(v6 + -4.0, 0.0, -33.0, v16, 4, v13);
              v64 = 0;
              v65 = 8;
              while (2)
              {
                v66 = Work;
                v67 = *(u32 *)(*(u64 *)(*(u64 *)v9 + 24) + 36);
                if (v65 - 8 >= v66->doraNum)
                {
                  if (v68)
                  {
                    goto LABEL_243;
                  }
                  else
                  {
LABEL_243:
                  }
                  v97 = v6 + -8.0;
                  DrawHai3DExCalc(v6 + -8.0, 0.0, -33.0, v67, 4, v64);
                  v35 = 0;
                  v100 = 8;
                  while (2)
                  {
                    v101 = Work;
                    v102 = *(u32 *)(*(u64 *)(*(u64 *)v9 + 24) + 32);
                    if (v100 - 8 >= v101->doraNum)
                      goto LABEL_307;
                    if (v103)
                    {
                      if (v102 == *((u32 *)&v101->dora->obj.klass + v100))
                        break;
LABEL_254:
                      v104 = *(u32 *)(*(u64 *)(*(u64 *)v9 + 24) + 32);
                      if (v104 != *((u32 *)&Work->uraDora->obj.klass + v100))
                        goto LABEL_246;
                      if (!Work->agariPlayerIndex)
                        break;
LABEL_246:
                      ++v100;
                      continue;
                    }
                    else
                    {
                      if (v102 != *((u32 *)&Work->dora->obj.klass + v100))
                        goto LABEL_254;
                    }
                    break;
                  }
                  v35 = 3;
                  goto LABEL_246;
                }
                if (v68)
                {
                  if (v67 == *((u32 *)&v66->dora->obj.klass + v65))
                    break;
LABEL_166:
                  v69 = *(u32 *)(*(u64 *)(*(u64 *)v9 + 24) + 36);
                  if (v69 != *((u32 *)&Work->uraDora->obj.klass + v65))
                    goto LABEL_158;
                  if (!Work->agariPlayerIndex)
                    break;
LABEL_158:
                  ++v65;
                  continue;
                }
                else
                {
                  if (v67 != *((u32 *)&Work->dora->obj.klass + v65))
                    goto LABEL_166;
                }
                break;
              }
              v64 = 3;
              goto LABEL_158;
            }
            if (v17)
            {
              if (v16 == *((u32 *)&v15->dora->obj.klass + v14))
                break;
LABEL_25:
              v18 = *(u32 *)(*(u64 *)(*(u64 *)v9 + 24) + 40);
              if (v18 != *((u32 *)&Work->uraDora->obj.klass + v14))
                goto LABEL_17;
              if (!Work->agariPlayerIndex)
                break;
LABEL_17:
              ++v14;
              continue;
            }
            else
            {
              if (v16 != *((u32 *)&Work->dora->obj.klass + v14))
                goto LABEL_25;
            }
            break;
          }
          v13 = 3;
          goto LABEL_17;
        }
        v55 = 0;
        v56 = 8;
        while (2)
        {
          v57 = Work;
          v58 = *(u32 *)(*(u64 *)(*(u64 *)v9 + 24) + 40);
          if (v56 - 8 >= v57->doraNum)
          {
            if (v59)
            {
              goto LABEL_221;
            }
            else
            {
LABEL_221:
            }
            DrawHai3DExCalc(v6 + -4.0, 0.0, -33.0, v58, 4, v55);
            v90 = 0;
            v91 = 8;
            while (2)
            {
              v92 = Work;
              v93 = *(u32 *)(*(u64 *)(*(u64 *)v9 + 24) + 32);
              if (v91 - 8 >= v92->doraNum)
              {
                if (v94)
                {
                  goto LABEL_287;
                }
                else
                {
LABEL_287:
                }
                v97 = v6 + -8.0;
                DrawHai3DExCalc(v6 + -8.0, 0.0, -33.0, v93, 4, v90);
                v35 = 0;
                v110 = 8;
                while (2)
                {
                  v111 = Work;
                  v102 = *(u32 *)(*(u64 *)(*(u64 *)v9 + 24) + 36);
                  if (v110 - 8 >= v111->doraNum)
                    goto LABEL_307;
                  if (v103)
                  {
                    if (v102 == *((u32 *)&v111->dora->obj.klass + v110))
                      break;
LABEL_298:
                    v112 = *(u32 *)(*(u64 *)(*(u64 *)v9 + 24) + 36);
                    if (v112 != *((u32 *)&Work->uraDora->obj.klass + v110))
                      goto LABEL_290;
                    if (!Work->agariPlayerIndex)
                      break;
LABEL_290:
                    ++v110;
                    continue;
                  }
                  else
                  {
                    if (v102 != *((u32 *)&Work->dora->obj.klass + v110))
                      goto LABEL_298;
                  }
                  break;
                }
                v35 = 3;
                goto LABEL_290;
              }
              if (v94)
              {
                if (v93 == *((u32 *)&v92->dora->obj.klass + v91))
                  break;
LABEL_232:
                v95 = *(u32 *)(*(u64 *)(*(u64 *)v9 + 24) + 32);
                if (v95 != *((u32 *)&Work->uraDora->obj.klass + v91))
                  goto LABEL_224;
                if (!Work->agariPlayerIndex)
                  break;
LABEL_224:
                ++v91;
                continue;
              }
              else
              {
                if (v93 != *((u32 *)&Work->dora->obj.klass + v91))
                  goto LABEL_232;
              }
              break;
            }
            v90 = 3;
            goto LABEL_224;
          }
          if (v59)
          {
            if (v58 == *((u32 *)&v57->dora->obj.klass + v56))
              break;
LABEL_144:
            v60 = *(u32 *)(*(u64 *)(*(u64 *)v9 + 24) + 40);
            if (v60 != *((u32 *)&Work->uraDora->obj.klass + v56))
              goto LABEL_136;
            if (!Work->agariPlayerIndex)
              break;
LABEL_136:
            ++v56;
            continue;
          }
          else
          {
            if (v58 != *((u32 *)&Work->dora->obj.klass + v56))
              goto LABEL_144;
          }
          break;
        }
        v55 = 3;
        goto LABEL_136;
      }
      if (v11 == 64)
      {
        v70 = *(u32 *)(v8 + 20);
        if (v70 != 1)
        {
          if (v70 != 3)
          {
            if (v70 != 2)
              goto LABEL_572;
            v72 = 0;
            v73 = 8;
            while (2)
            {
              v74 = Work;
              v75 = *(u32 *)(*(u64 *)(*(u64 *)v9 + 24) + 32);
              if (v73 - 8 >= v74->doraNum)
              {
                if (v76)
                {
                  goto LABEL_532;
                }
                else
                {
LABEL_532:
                }
                DrawHai3DExCalc(v6 + -4.0, 0.0, -33.0, v75, 4, v72);
                v183 = *(u32 *)(*(u64 *)(*(u64 *)v9 + 24) + 32);
                v184 = -34.2;
                v185 = v183;
                v186 = 7;
                v187 = v6 + -5.2;
                v188 = (f32)(v6 + -5.2) + -4.0;
LABEL_546:
                DrawHai3DExCalc(v188, 0.0, v184, v185, v186, v72);
                v192 = *(u32 *)(*(u64 *)(*(u64 *)v9 + 24) + 32);
                DrawHai3DExCalc(v187 + -8.0, 0.0, -33.0, v192, 4, v72);
                v194 = *(u32 *)(*(u64 *)(*(u64 *)v9 + 24) + 32);
                v195 = v187 + -12.0;
                v196 = -33.0;
                v197 = v194;
                v198 = 4;
LABEL_571:
                DrawHai3DExCalc(v195, 0.0, v196, v197, v198, v72);
LABEL_572:
                v168 = -17.2;
                goto LABEL_491;
              }
              if (v76)
              {
                if (v75 == *((u32 *)&v74->dora->obj.klass + v73))
                  break;
LABEL_188:
                v77 = *(u32 *)(*(u64 *)(*(u64 *)v9 + 24) + 32);
                if (v77 != *((u32 *)&Work->uraDora->obj.klass + v73))
                  goto LABEL_180;
                if (!Work->agariPlayerIndex)
                  break;
LABEL_180:
                ++v73;
                continue;
              }
              else
              {
                if (v75 != *((u32 *)&Work->dora->obj.klass + v73))
                  goto LABEL_188;
              }
              break;
            }
            v72 = 3;
            goto LABEL_180;
          }
          v72 = 0;
          v176 = 8;
          while (2)
          {
            v177 = Work;
            v178 = *(u32 *)(*(u64 *)(*(u64 *)v9 + 24) + 32);
            if (v176 - 8 >= v177->doraNum)
            {
              if (v179)
              {
                goto LABEL_557;
              }
              else
              {
LABEL_557:
              }
              DrawHai3DExCalc(v6 + -4.0, 0.0, -33.0, v178, 4, v72);
              v201 = *(u32 *)(*(u64 *)(*(u64 *)v9 + 24) + 32);
              DrawHai3DExCalc(v6 + -8.0, 0.0, -33.0, v201, 4, v72);
              v203 = *(u32 *)(*(u64 *)(*(u64 *)v9 + 24) + 32);
              DrawHai3DExCalc(v6 + -12.0, 0.0, -33.0, v203, 4, v72);
              v204 = *(u32 *)(*(u64 *)(*(u64 *)v9 + 24) + 32);
              v196 = -34.2;
              v197 = v204;
              v198 = 7;
              v195 = (f32)(v6 + -5.2) + -12.0;
              goto LABEL_571;
            }
            if (v179)
            {
              if (v178 == *((u32 *)&v177->dora->obj.klass + v176))
                break;
LABEL_521:
              v180 = *(u32 *)(*(u64 *)(*(u64 *)v9 + 24) + 32);
              if (v180 != *((u32 *)&Work->uraDora->obj.klass + v176))
                goto LABEL_513;
              if (!Work->agariPlayerIndex)
                break;
LABEL_513:
              ++v176;
              continue;
            }
            else
            {
              if (v178 != *((u32 *)&Work->dora->obj.klass + v176))
                goto LABEL_521;
            }
            break;
          }
          v72 = 3;
          goto LABEL_513;
        }
        v72 = 0;
        v170 = 8;
        while (2)
        {
          v171 = Work;
          v172 = *(u32 *)(*(u64 *)(*(u64 *)v9 + 24) + 32);
          if (v170 - 8 >= v171->doraNum)
          {
            if (v173)
            {
              goto LABEL_540;
            }
            else
            {
LABEL_540:
            }
            v187 = v6 + -5.2;
            DrawHai3DExCalc(v6 + -5.2, 0.0, -34.2, v172, 7, v72);
            v190 = *(u32 *)(*(u64 *)(*(u64 *)v9 + 24) + 32);
            v188 = v187 + -4.0;
            v184 = -33.0;
            v185 = v190;
            v186 = 4;
            goto LABEL_546;
          }
          if (v173)
          {
            if (v172 == *((u32 *)&v171->dora->obj.klass + v170))
              break;
LABEL_502:
            v174 = *(u32 *)(*(u64 *)(*(u64 *)v9 + 24) + 32);
            if (v174 != *((u32 *)&Work->uraDora->obj.klass + v170))
              goto LABEL_494;
            if (!Work->agariPlayerIndex)
              break;
LABEL_494:
            ++v170;
            continue;
          }
          else
          {
            if (v172 != *((u32 *)&Work->dora->obj.klass + v170))
              goto LABEL_502;
          }
          break;
        }
        v72 = 3;
        goto LABEL_494;
      }
      if (v11 != 268435584)
        goto LABEL_10;
      v27 = 0;
      for (i = 8; ; ++i)
      {
        v29 = Work;
        v30 = *(u32 *)(*(u64 *)(*(u64 *)v9 + 24) + 36);
        if (i - 8 >= v29->doraNum)
          break;
        if (v31)
        {
          if (v30 == *((u32 *)&v29->dora->obj.klass + i))
            goto LABEL_59;
        }
        else
        {
          if (v30 == *((u32 *)&Work->dora->obj.klass + i))
            goto LABEL_59;
        }
        v32 = *(u32 *)(*(u64 *)(*(u64 *)v9 + 24) + 36);
        if (v32 != *((u32 *)&Work->uraDora->obj.klass + i))
          continue;
        if (!Work->agariPlayerIndex)
          goto LABEL_59;
        goto LABEL_9001;
        if (!Work->agariPlayerIndex)
        {
LABEL_59:
          v27 = 3;
          continue;
        }
LABEL_9001:
      }
      if (v31)
      {
        goto LABEL_199;
      }
      else
      {
LABEL_199:
      }
      DrawHai3DExCalc(v6 + -4.0, 0.0, -33.0, v30, 4, v27);
      v81 = 0;
      v82 = 8;
      while (2)
      {
        v83 = Work;
        v84 = *(u32 *)(*(u64 *)(*(u64 *)v9 + 24) + 32);
        if (v82 - 8 < v83->doraNum)
        {
          if (v85)
          {
            if (v84 == *((u32 *)&v83->dora->obj.klass + v82))
              goto LABEL_201;
LABEL_210:
            v86 = *(u32 *)(*(u64 *)(*(u64 *)v9 + 24) + 32);
            if (v86 != *((u32 *)&Work->uraDora->obj.klass + v82))
              goto LABEL_202;
            if (!Work->agariPlayerIndex)
              goto LABEL_201;
LABEL_202:
            ++v82;
            continue;
          }
          else
          {
            if (v84 != *((u32 *)&Work->dora->obj.klass + v82))
              goto LABEL_210;
          }
LABEL_201:
          v81 = 3;
          goto LABEL_202;
        }
        break;
      }
      if (v85)
      {
        goto LABEL_265;
      }
      else
      {
LABEL_265:
      }
      v97 = v6 + -8.0;
      DrawHai3DExCalc(v6 + -8.0, 0.0, -33.0, v84, 4, v81);
      v35 = 0;
      v106 = 8;
      while (2)
      {
        v107 = Work;
        v102 = *(u32 *)(*(u64 *)(*(u64 *)v9 + 24) + 40);
        if (v106 - 8 < v107->doraNum)
        {
          if (v103)
          {
            if (v102 == *((u32 *)&v107->dora->obj.klass + v106))
              goto LABEL_267;
LABEL_276:
            v108 = *(u32 *)(*(u64 *)(*(u64 *)v9 + 24) + 40);
            if (v108 != *((u32 *)&Work->uraDora->obj.klass + v106))
              goto LABEL_268;
            if (!Work->agariPlayerIndex)
              goto LABEL_267;
LABEL_268:
            ++v106;
            continue;
          }
          else
          {
            if (v102 != *((u32 *)&Work->dora->obj.klass + v106))
              goto LABEL_276;
          }
LABEL_267:
          v35 = 3;
          goto LABEL_268;
        }
        break;
      }
LABEL_307:
      v113 = v97 + -5.2;
LABEL_313:
      v114 = -34.2;
LABEL_314:
      v115 = v102;
      v116 = 7;
LABEL_489:
      DrawHai3DExCalc(v113, 0.0, v114, v115, v116, v35);
LABEL_490:
      v168 = -13.2;
LABEL_491:
      v6 = v6 + v168;
LABEL_10:
      if (++v5 >= v3->nakiNum)
      {
        break;
      }
    }
  }
  v205 = Work->players[1];
  if (v205->nakiNum >= 1)
  {
    v206 = v205->naki;
    v207 = 0;
    v208 = 44.0;
    while (1)
    {
      v214 = (s64)v206 + 8 * v207;
      v217 = *(u64 *)(v214 + 32);
      v216 = v214 + 32;
      v215 = v217;
      v218 = *(u32 *)(v217 + 16);
      if (v218 <= 32)
      {
        if (v218 != 32)
        {
          if (v218 != 8)
          {
            if (v218 != 4)
              goto LABEL_611;
            v227 = 0;
            v228 = 8;
            while (2)
            {
              v229 = Work;
              v230 = *(u32 *)(*(u64 *)(*(u64 *)v216 + 24) + 32);
              if (v228 - 8 >= v229->doraNum)
              {
                if (v231)
                {
                  goto LABEL_724;
                }
                else
                {
LABEL_724:
                }
                DrawHai3DExCalc(38.8, 0.0, v208, v230, 5, v227);
                v258 = *(u32 *)(*(u64 *)(*(u64 *)v216 + 24) + 32);
                DrawHai3DExCalc(38.8, 0.0, v208 + -4.0, v258, 10, v227);
                v260 = *(u32 *)(*(u64 *)(*(u64 *)v216 + 24) + 32);
                DrawHai3DExCalc(38.8, 0.0, v208 + -8.0, v260, 10, v227);
                v262 = *(u32 *)(*(u64 *)(*(u64 *)v216 + 24) + 32);
                DrawHai3DExCalc(38.8, 0.0, v208 + -12.0, v262, 5, v227);
                v208 = v208 + -16.0;
                goto LABEL_611;
              }
              if (v231)
              {
                if (v230 == *((u32 *)&v229->dora->obj.klass + v228))
                  goto LABEL_639;
LABEL_648:
                v232 = *(u32 *)(*(u64 *)(*(u64 *)v216 + 24) + 32);
                if (v232 == *((u32 *)&Work->uraDora->obj.klass + v228))
                {
                  if (Work->agariPlayerIndex != 1)
                    goto LABEL_640;
LABEL_639:
                  v227 = 3;
                }
LABEL_640:
                ++v228;
                continue;
              }
              break;
            }
            if (v230 != *((u32 *)&Work->dora->obj.klass + v228))
              goto LABEL_648;
            goto LABEL_639;
          }
LABEL_678:
          v240 = *(u32 *)(v215 + 20);
          if (v240)
          {
            if (v240 != 2)
            {
              if (v240 != 3)
                goto LABEL_609;
              v242 = 0;
              v243 = 8;
              while (2)
              {
                v244 = Work;
                v245 = *(u32 *)(*(u64 *)(*(u64 *)v216 + 24) + 32);
                if (v243 - 8 >= v244->doraNum)
                {
                  if (v246)
                  {
                    goto LABEL_935;
                  }
                  else
                  {
LABEL_935:
                  }
                  DrawHai3DExCalc(38.8, 0.0, v208, v245, 5, v242);
                  v331 = *(u32 *)(*(u64 *)(*(u64 *)v216 + 24) + 32);
                  DrawHai3DExCalc(40.0, 0.0, v208 + -4.0, v331, 4, v242);
                  v333 = *(u32 *)(*(u64 *)(*(u64 *)v216 + 24) + 32);
                  v334 = v208 + -5.2;
LABEL_972:
                  DrawHai3DExCalc(38.8, 0.0, v334 + -4.0, v333, 5, v242);
                  v344 = *(u32 *)(*(u64 *)(*(u64 *)v216 + 24) + 32);
                  v209 = v334 + -8.0;
                  v210 = 38.8;
                  v211 = v344;
                  v212 = 5;
LABEL_608:
                  DrawHai3DExCalc(v210, 0.0, v209, v211, v212, v242);
LABEL_609:
                  v213 = -17.2;
                  goto LABEL_610;
                }
                if (v246)
                {
                  if (v245 == *((u32 *)&v244->dora->obj.klass + v243))
                    goto LABEL_682;
LABEL_691:
                  v247 = *(u32 *)(*(u64 *)(*(u64 *)v216 + 24) + 32);
                  if (v247 == *((u32 *)&Work->uraDora->obj.klass + v243))
                  {
                    if (Work->agariPlayerIndex != 1)
                      goto LABEL_683;
LABEL_682:
                    v242 = 3;
                  }
LABEL_683:
                  ++v243;
                  continue;
                }
                break;
              }
              if (v245 != *((u32 *)&Work->dora->obj.klass + v243))
                goto LABEL_691;
              goto LABEL_682;
            }
            v242 = 0;
            v324 = 8;
            while (2)
            {
              v325 = Work;
              v326 = *(u32 *)(*(u64 *)(*(u64 *)v216 + 24) + 32);
              if (v324 - 8 >= v325->doraNum)
              {
                if (v327)
                {
                  goto LABEL_963;
                }
                else
                {
LABEL_963:
                }
                DrawHai3DExCalc(40.0, 0.0, v208, v326, 4, v242);
                v343 = *(u32 *)(*(u64 *)(*(u64 *)v216 + 24) + 32);
                v334 = v208 + -5.2;
                DrawHai3DExCalc(38.8, 0.0, v208 + -5.2, v343, 5, v242);
                v333 = *(u32 *)(*(u64 *)(*(u64 *)v216 + 24) + 32);
                goto LABEL_972;
              }
              if (v327)
              {
                if (v326 == *((u32 *)&v325->dora->obj.klass + v324))
                  goto LABEL_915;
LABEL_924:
                v328 = *(u32 *)(*(u64 *)(*(u64 *)v216 + 24) + 32);
                if (v328 == *((u32 *)&Work->uraDora->obj.klass + v324))
                {
                  if (Work->agariPlayerIndex != 1)
                    goto LABEL_916;
LABEL_915:
                  v242 = 3;
                }
LABEL_916:
                ++v324;
                continue;
              }
              break;
            }
            if (v326 != *((u32 *)&Work->dora->obj.klass + v324))
              goto LABEL_924;
            goto LABEL_915;
          }
          v242 = 0;
          v318 = 8;
          while (2)
          {
            v319 = Work;
            v320 = *(u32 *)(*(u64 *)(*(u64 *)v216 + 24) + 32);
            if (v318 - 8 >= v319->doraNum)
            {
              if (v321)
              {
                goto LABEL_947;
              }
              else
              {
LABEL_947:
              }
              DrawHai3DExCalc(38.8, 0.0, v208, v320, 5, v242);
              v337 = *(u32 *)(*(u64 *)(*(u64 *)v216 + 24) + 32);
              DrawHai3DExCalc(38.8, 0.0, v208 + -4.0, v337, 5, v242);
              v339 = *(u32 *)(*(u64 *)(*(u64 *)v216 + 24) + 32);
              DrawHai3DExCalc(38.8, 0.0, v208 + -8.0, v339, 5, v242);
              v340 = *(u32 *)(*(u64 *)(*(u64 *)v216 + 24) + 32);
              v209 = v208 + -12.0;
              v210 = 40.0;
              v211 = v340;
              v212 = 4;
              goto LABEL_608;
            }
            if (v321)
            {
              if (v320 == *((u32 *)&v319->dora->obj.klass + v318))
                goto LABEL_896;
LABEL_905:
              v322 = *(u32 *)(*(u64 *)(*(u64 *)v216 + 24) + 32);
              if (v322 == *((u32 *)&Work->uraDora->obj.klass + v318))
              {
                if (Work->agariPlayerIndex != 1)
                  goto LABEL_897;
LABEL_896:
                v242 = 3;
              }
LABEL_897:
              ++v318;
              continue;
            }
            break;
          }
          if (v320 != *((u32 *)&Work->dora->obj.klass + v318))
            goto LABEL_905;
          goto LABEL_896;
        }
        v248 = *(u32 *)(v215 + 20);
        if (v248)
        {
          if (v248 != 2)
          {
            if (v248 != 3)
              goto LABEL_892;
            v250 = 0;
            v251 = 8;
            while (2)
            {
              v252 = Work;
              v253 = *(u32 *)(*(u64 *)(*(u64 *)v216 + 24) + 32);
              if (v251 - 8 >= v252->doraNum)
              {
                if (v254)
                {
                  goto LABEL_1047;
                }
                else
                {
LABEL_1047:
                }
                DrawHai3DExCalc(38.8, 0.0, v208, v253, 5, v250);
                v364 = *(u32 *)(*(u64 *)(*(u64 *)v216 + 24) + 32);
                DrawHai3DExCalc(40.0, 0.0, v208 + -4.0, v364, 4, v250);
                v355 = *(u32 *)(*(u64 *)(*(u64 *)v216 + 24) + 32);
                v313 = (f32)(v208 + -5.2) + -4.0;
LABEL_1057:
                v314 = 38.8;
                v315 = v355;
                v316 = 5;
                goto LABEL_891;
              }
              if (v254)
              {
                if (v253 == *((u32 *)&v252->dora->obj.klass + v251))
                  goto LABEL_704;
LABEL_713:
                v255 = *(u32 *)(*(u64 *)(*(u64 *)v216 + 24) + 32);
                if (v255 == *((u32 *)&Work->uraDora->obj.klass + v251))
                {
                  if (Work->agariPlayerIndex != 1)
                    goto LABEL_705;
LABEL_704:
                  v250 = 3;
                }
LABEL_705:
                ++v251;
                continue;
              }
              break;
            }
            if (v253 != *((u32 *)&Work->dora->obj.klass + v251))
              goto LABEL_713;
            goto LABEL_704;
          }
          v250 = 0;
          v347 = 8;
          while (2)
          {
            v348 = Work;
            v349 = *(u32 *)(*(u64 *)(*(u64 *)v216 + 24) + 32);
            if (v347 - 8 >= v348->doraNum)
            {
              if (v350)
              {
                goto LABEL_1016;
              }
              else
              {
LABEL_1016:
              }
              DrawHai3DExCalc(40.0, 0.0, v208, v349, 4, v250);
              v354 = *(u32 *)(*(u64 *)(*(u64 *)v216 + 24) + 32);
              DrawHai3DExCalc(38.8, 0.0, v208 + -5.2, v354, 5, v250);
              v355 = *(u32 *)(*(u64 *)(*(u64 *)v216 + 24) + 32);
              v313 = (f32)(v208 + -5.2) + -4.0;
              goto LABEL_1057;
            }
            if (v350)
            {
              if (v349 == *((u32 *)&v348->dora->obj.klass + v347))
                goto LABEL_978;
LABEL_987:
              v351 = *(u32 *)(*(u64 *)(*(u64 *)v216 + 24) + 32);
              if (v351 == *((u32 *)&Work->uraDora->obj.klass + v347))
              {
                if (Work->agariPlayerIndex != 1)
                  goto LABEL_979;
LABEL_978:
                v250 = 3;
              }
LABEL_979:
              ++v347;
              continue;
            }
            break;
          }
          if (v349 != *((u32 *)&Work->dora->obj.klass + v347))
            goto LABEL_987;
          goto LABEL_978;
        }
        v250 = 0;
        v357 = 8;
        while (2)
        {
          v358 = Work;
          v359 = *(u32 *)(*(u64 *)(*(u64 *)v216 + 24) + 32);
          if (v357 - 8 >= v358->doraNum)
          {
            if (v360)
            {
              goto LABEL_1060;
            }
            else
            {
LABEL_1060:
            }
            DrawHai3DExCalc(38.8, 0.0, v208, v359, 5, v250);
            v367 = *(u32 *)(*(u64 *)(*(u64 *)v216 + 24) + 32);
            DrawHai3DExCalc(38.8, 0.0, v208 + -4.0, v367, 5, v250);
            v302 = *(u32 *)(*(u64 *)(*(u64 *)v216 + 24) + 32);
            goto LABEL_888;
          }
          if (v360)
          {
            if (v359 == *((u32 *)&v358->dora->obj.klass + v357))
              goto LABEL_1027;
LABEL_1036:
            v361 = *(u32 *)(*(u64 *)(*(u64 *)v216 + 24) + 32);
            if (v361 == *((u32 *)&Work->uraDora->obj.klass + v357))
            {
              if (Work->agariPlayerIndex != 1)
                goto LABEL_1028;
LABEL_1027:
              v250 = 3;
            }
LABEL_1028:
            ++v357;
            continue;
          }
          break;
        }
        if (v359 != *((u32 *)&Work->dora->obj.klass + v357))
          goto LABEL_1036;
        goto LABEL_1027;
      }
      if ((u32)v218 > 0x10000080)
      {
        if (v218 != 268435712)
        {
          if (v218 != 268435968)
            goto LABEL_611;
          v220 = 0;
          v221 = 8;
          while (2)
          {
            v222 = Work;
            v223 = *(u32 *)(*(u64 *)(*(u64 *)v216 + 24) + 40);
            if (v221 - 8 >= v222->doraNum)
            {
              if (v224)
              {
                goto LABEL_759;
              }
              else
              {
LABEL_759:
              }
              DrawHai3DExCalc(38.8, 0.0, v208, v223, 5, v220);
              v273 = 0;
              v274 = 8;
              while (2)
              {
                v275 = Work;
                v276 = *(u32 *)(*(u64 *)(*(u64 *)v216 + 24) + 36);
                if (v274 - 8 >= v275->doraNum)
                {
                  if (v277)
                  {
                    goto LABEL_821;
                  }
                  else
                  {
LABEL_821:
                  }
                  DrawHai3DExCalc(38.8, 0.0, v208 + -4.0, v276, 5, v273);
                  v250 = 0;
                  v300 = 8;
                  while (2)
                  {
                    v301 = Work;
                    v302 = *(u32 *)(*(u64 *)(*(u64 *)v216 + 24) + 32);
                    if (v300 - 8 >= v301->doraNum)
                      goto LABEL_885;
                    if (v303)
                    {
                      if (v302 == *((u32 *)&v301->dora->obj.klass + v300))
                        goto LABEL_823;
LABEL_832:
                      v304 = *(u32 *)(*(u64 *)(*(u64 *)v216 + 24) + 32);
                      if (v304 == *((u32 *)&Work->uraDora->obj.klass + v300))
                      {
                        if (Work->agariPlayerIndex != 1)
                          goto LABEL_824;
LABEL_823:
                        v250 = 3;
                      }
LABEL_824:
                      ++v300;
                      continue;
                    }
                    break;
                  }
                  if (v302 != *((u32 *)&Work->dora->obj.klass + v300))
                    goto LABEL_832;
                  goto LABEL_823;
                }
                if (v277)
                {
                  if (v276 == *((u32 *)&v275->dora->obj.klass + v274))
                    goto LABEL_761;
LABEL_770:
                  v278 = *(u32 *)(*(u64 *)(*(u64 *)v216 + 24) + 36);
                  if (v278 != *((u32 *)&Work->uraDora->obj.klass + v274))
                    goto LABEL_762;
LABEL_761:
                  v273 = 3;
LABEL_762:
                  ++v274;
                  continue;
                }
                break;
              }
              if (v276 != *((u32 *)&Work->dora->obj.klass + v274))
                goto LABEL_770;
              goto LABEL_761;
            }
            if (v224)
            {
              if (v223 == *((u32 *)&v222->dora->obj.klass + v221))
                goto LABEL_617;
LABEL_626:
              v225 = *(u32 *)(*(u64 *)(*(u64 *)v216 + 24) + 40);
              if (v225 == *((u32 *)&Work->uraDora->obj.klass + v221))
              {
                if (Work->agariPlayerIndex != 1)
                  goto LABEL_618;
LABEL_617:
                v220 = 3;
              }
LABEL_618:
              ++v221;
              continue;
            }
            break;
          }
          if (v223 != *((u32 *)&Work->dora->obj.klass + v221))
            goto LABEL_626;
          goto LABEL_617;
        }
        v264 = 0;
        v265 = 8;
        while (2)
        {
          v266 = Work;
          v267 = *(u32 *)(*(u64 *)(*(u64 *)v216 + 24) + 40);
          if (v265 - 8 >= v266->doraNum)
          {
            if (v268)
            {
              goto LABEL_799;
            }
            else
            {
LABEL_799:
            }
            DrawHai3DExCalc(38.8, 0.0, v208, v267, 5, v264);
            v291 = 0;
            v292 = 8;
            while (2)
            {
              v293 = Work;
              v294 = *(u32 *)(*(u64 *)(*(u64 *)v216 + 24) + 32);
              if (v292 - 8 >= v293->doraNum)
              {
                if (v295)
                {
                  goto LABEL_865;
                }
                else
                {
LABEL_865:
                }
                DrawHai3DExCalc(38.8, 0.0, v208 + -4.0, v294, 5, v291);
                v250 = 0;
                v310 = 8;
                while (2)
                {
                  v311 = Work;
                  v302 = *(u32 *)(*(u64 *)(*(u64 *)v216 + 24) + 36);
                  if (v310 - 8 >= v311->doraNum)
                    goto LABEL_885;
                  if (v303)
                  {
                    if (v302 == *((u32 *)&v311->dora->obj.klass + v310))
                      goto LABEL_867;
LABEL_876:
                    v312 = *(u32 *)(*(u64 *)(*(u64 *)v216 + 24) + 36);
                    if (v312 == *((u32 *)&Work->uraDora->obj.klass + v310))
                    {
                      if (Work->agariPlayerIndex != 1)
                        goto LABEL_868;
LABEL_867:
                      v250 = 3;
                    }
LABEL_868:
                    ++v310;
                    continue;
                  }
                  break;
                }
                if (v302 != *((u32 *)&Work->dora->obj.klass + v310))
                  goto LABEL_876;
                goto LABEL_867;
              }
              if (v295)
              {
                if (v294 == *((u32 *)&v293->dora->obj.klass + v292))
                  goto LABEL_801;
LABEL_810:
                v296 = *(u32 *)(*(u64 *)(*(u64 *)v216 + 24) + 32);
                if (v296 == *((u32 *)&Work->uraDora->obj.klass + v292))
                {
                  if (Work->agariPlayerIndex != 1)
                    goto LABEL_802;
LABEL_801:
                  v291 = 3;
                }
LABEL_802:
                ++v292;
                continue;
              }
              break;
            }
            if (v294 != *((u32 *)&Work->dora->obj.klass + v292))
              goto LABEL_810;
            goto LABEL_801;
          }
          if (v268)
          {
            if (v267 == *((u32 *)&v266->dora->obj.klass + v265))
              goto LABEL_739;
LABEL_748:
            v269 = *(u32 *)(*(u64 *)(*(u64 *)v216 + 24) + 40);
            if (v269 == *((u32 *)&Work->uraDora->obj.klass + v265))
            {
              if (Work->agariPlayerIndex != 1)
                goto LABEL_740;
LABEL_739:
              v264 = 3;
            }
LABEL_740:
            ++v265;
            continue;
          }
          break;
        }
        if (v267 != *((u32 *)&Work->dora->obj.klass + v265))
          goto LABEL_748;
        goto LABEL_739;
      }
      if (v218 == 64)
        goto LABEL_678;
      if (v218 != 268435584)
        goto LABEL_611;
      v234 = 0;
      for (j = 8; ; ++j)
      {
        v236 = Work;
        v237 = *(u32 *)(*(u64 *)(*(u64 *)v216 + 24) + 36);
        if (j - 8 >= v236->doraNum)
          break;
        if (v238)
        {
          if (v237 == *((u32 *)&v236->dora->obj.klass + j))
            goto LABEL_660;
        }
        else
        {
          if (v237 == *((u32 *)&Work->dora->obj.klass + j))
            goto LABEL_660;
        }
        v239 = *(u32 *)(*(u64 *)(*(u64 *)v216 + 24) + 36);
        if (v239 != *((u32 *)&Work->uraDora->obj.klass + j))
          continue;
        if (Work->agariPlayerIndex == 1)
          goto LABEL_660;
        goto LABEL_9002;
        if (Work->agariPlayerIndex == 1)
        {
LABEL_660:
          v234 = 3;
          continue;
        }
LABEL_9002:
      }
      if (v238)
      {
        goto LABEL_777;
      }
      else
      {
LABEL_777:
      }
      DrawHai3DExCalc(38.8, 0.0, v208, v237, 5, v234);
      v282 = 0;
      v283 = 8;
      while (2)
      {
        v284 = Work;
        v285 = *(u32 *)(*(u64 *)(*(u64 *)v216 + 24) + 32);
        if (v283 - 8 < v284->doraNum)
        {
          if (v286)
          {
            if (v285 == *((u32 *)&v284->dora->obj.klass + v283))
              goto LABEL_779;
LABEL_788:
            v287 = *(u32 *)(*(u64 *)(*(u64 *)v216 + 24) + 32);
            if (v287 == *((u32 *)&Work->uraDora->obj.klass + v283))
            {
              if (Work->agariPlayerIndex != 1)
                goto LABEL_780;
LABEL_779:
              v282 = 3;
            }
LABEL_780:
            ++v283;
            continue;
          }
          if (v285 != *((u32 *)&Work->dora->obj.klass + v283))
            goto LABEL_788;
          goto LABEL_779;
        }
        break;
      }
      if (v286)
      {
        goto LABEL_843;
      }
      else
      {
LABEL_843:
      }
      DrawHai3DExCalc(38.8, 0.0, v208 + -4.0, v285, 5, v282);
      v250 = 0;
      v306 = 8;
      while (2)
      {
        v307 = Work;
        v302 = *(u32 *)(*(u64 *)(*(u64 *)v216 + 24) + 40);
        if (v306 - 8 < v307->doraNum)
        {
          if (v303)
          {
            if (v302 == *((u32 *)&v307->dora->obj.klass + v306))
              goto LABEL_845;
LABEL_854:
            v308 = *(u32 *)(*(u64 *)(*(u64 *)v216 + 24) + 40);
            if (v308 == *((u32 *)&Work->uraDora->obj.klass + v306))
            {
              if (Work->agariPlayerIndex != 1)
                goto LABEL_846;
LABEL_845:
              v250 = 3;
            }
LABEL_846:
            ++v306;
            continue;
          }
          if (v302 != *((u32 *)&Work->dora->obj.klass + v306))
            goto LABEL_854;
          goto LABEL_845;
        }
        break;
      }
LABEL_885:
      if (!v303)
      {
        goto LABEL_888;
      }
LABEL_888:
      v313 = v208 + -8.0;
      v314 = 40.0;
      v315 = v302;
      v316 = 4;
LABEL_891:
      DrawHai3DExCalc(v314, 0.0, v313, v315, v316, v250);
LABEL_892:
      v213 = -13.2;
LABEL_610:
      v208 = v208 + v213;
LABEL_611:
      if (++v207 >= v205->nakiNum)
      {
        break;
      }
    }
  }
  v368 = Work->players[2];
  if (v368->nakiNum >= 1)
  {
    v369 = v368->naki;
    v370 = 0;
    v371 = -42.0;
    while (1)
    {
      v376 = (s64)v369 + 8 * v370;
      v379 = *(u64 *)(v376 + 32);
      v378 = v376 + 32;
      v377 = v379;
      v380 = *(u32 *)(v379 + 16);
      if (v380 <= 32)
      {
        if (v380 != 32)
        {
          if (v380 != 8)
          {
            if (v380 != 4)
              goto LABEL_1096;
            v389 = 0;
            v390 = 8;
            while (2)
            {
              v391 = Work;
              v392 = *(u32 *)(*(u64 *)(*(u64 *)v378 + 24) + 32);
              if (v390 - 8 >= v391->doraNum)
              {
                if (v393)
                {
                  goto LABEL_1209;
                }
                else
                {
LABEL_1209:
                }
                DrawHai3DExCalc(v371, 0.0, 44.0, v392, 6, v389);
                v420 = *(u32 *)(*(u64 *)(*(u64 *)v378 + 24) + 32);
                DrawHai3DExCalc(v371 + 4.0, 0.0, 44.0, v420, 11, v389);
                v422 = *(u32 *)(*(u64 *)(*(u64 *)v378 + 24) + 32);
                DrawHai3DExCalc(v371 + 8.0, 0.0, 44.0, v422, 11, v389);
                v424 = *(u32 *)(*(u64 *)(*(u64 *)v378 + 24) + 32);
                DrawHai3DExCalc(v371 + 12.0, 0.0, 44.0, v424, 6, v389);
                v371 = v371 + 16.0;
                goto LABEL_1096;
              }
              if (v393)
              {
                if (v392 == *((u32 *)&v391->dora->obj.klass + v390))
                  goto LABEL_1124;
LABEL_1133:
                v394 = *(u32 *)(*(u64 *)(*(u64 *)v378 + 24) + 32);
                if (v394 == *((u32 *)&Work->uraDora->obj.klass + v390))
                {
                  if (Work->agariPlayerIndex != 2)
                    goto LABEL_1125;
LABEL_1124:
                  v389 = 3;
                }
LABEL_1125:
                ++v390;
                continue;
              }
              break;
            }
            if (v392 != *((u32 *)&Work->dora->obj.klass + v390))
              goto LABEL_1133;
            goto LABEL_1124;
          }
LABEL_1163:
          v402 = *(u32 *)(v377 + 20);
          if (v402 != 3)
          {
            if (v402 != 1)
            {
              if (v402)
                goto LABEL_1094;
              v404 = 0;
              v405 = 8;
              while (2)
              {
                v406 = Work;
                v407 = *(u32 *)(*(u64 *)(*(u64 *)v378 + 24) + 32);
                if (v405 - 8 >= v406->doraNum)
                {
                  if (v408)
                  {
                    goto LABEL_1424;
                  }
                  else
                  {
LABEL_1424:
                  }
                  DrawHai3DExCalc(v371, 0.0, 44.0, v407, 6, v404);
                  v492 = *(u32 *)(*(u64 *)(*(u64 *)v378 + 24) + 32);
                  DrawHai3DExCalc(v371 + 4.0, 0.0, 44.0, v492, 5, v404);
                  v494 = *(u32 *)(*(u64 *)(*(u64 *)v378 + 24) + 32);
                  v495 = v371 + 5.2;
LABEL_1445:
                  DrawHai3DExCalc(v495 + 4.0, 0.0, 44.0, v494, 6, v404);
                  v499 = *(u32 *)(*(u64 *)(*(u64 *)v378 + 24) + 32);
                  v372 = v495 + 8.0;
                  v373 = v499;
                  v374 = 6;
LABEL_1093:
                  DrawHai3DExCalc(v372, 0.0, 44.0, v373, v374, v404);
LABEL_1094:
                  v375 = 17.2;
                  goto LABEL_1095;
                }
                if (v408)
                {
                  if (v407 == *((u32 *)&v406->dora->obj.klass + v405))
                    goto LABEL_1167;
LABEL_1176:
                  v409 = *(u32 *)(*(u64 *)(*(u64 *)v378 + 24) + 32);
                  if (v409 == *((u32 *)&Work->uraDora->obj.klass + v405))
                  {
                    if (Work->agariPlayerIndex != 2)
                      goto LABEL_1168;
LABEL_1167:
                    v404 = 3;
                  }
LABEL_1168:
                  ++v405;
                  continue;
                }
                break;
              }
              if (v407 != *((u32 *)&Work->dora->obj.klass + v405))
                goto LABEL_1176;
              goto LABEL_1167;
            }
            v404 = 0;
            v485 = 8;
            while (2)
            {
              v486 = Work;
              v487 = *(u32 *)(*(u64 *)(*(u64 *)v378 + 24) + 32);
              if (v485 - 8 >= v486->doraNum)
              {
                if (v488)
                {
                  goto LABEL_1449;
                }
                else
                {
LABEL_1449:
                }
                DrawHai3DExCalc(v371, 0.0, 44.0, v487, 6, v404);
                v502 = *(u32 *)(*(u64 *)(*(u64 *)v378 + 24) + 32);
                DrawHai3DExCalc(v371 + 4.0, 0.0, 44.0, v502, 6, v404);
                v504 = *(u32 *)(*(u64 *)(*(u64 *)v378 + 24) + 32);
                DrawHai3DExCalc(v371 + 8.0, 0.0, 44.0, v504, 6, v404);
                v505 = *(u32 *)(*(u64 *)(*(u64 *)v378 + 24) + 32);
                v372 = v371 + 12.0;
                v373 = v505;
                v374 = 5;
                goto LABEL_1093;
              }
              if (v488)
              {
                if (v487 == *((u32 *)&v486->dora->obj.klass + v485))
                  goto LABEL_1404;
LABEL_1413:
                v489 = *(u32 *)(*(u64 *)(*(u64 *)v378 + 24) + 32);
                if (v489 == *((u32 *)&Work->uraDora->obj.klass + v485))
                {
                  if (Work->agariPlayerIndex != 2)
                    goto LABEL_1405;
LABEL_1404:
                  v404 = 3;
                }
LABEL_1405:
                ++v485;
                continue;
              }
              break;
            }
            if (v487 != *((u32 *)&Work->dora->obj.klass + v485))
              goto LABEL_1413;
            goto LABEL_1404;
          }
          v404 = 0;
          v479 = 8;
          while (2)
          {
            v480 = Work;
            v481 = *(u32 *)(*(u64 *)(*(u64 *)v378 + 24) + 32);
            if (v479 - 8 >= v480->doraNum)
            {
              if (v482)
              {
                goto LABEL_1436;
              }
              else
              {
LABEL_1436:
              }
              DrawHai3DExCalc(v371, 0.0, 44.0, v481, 5, v404);
              v498 = *(u32 *)(*(u64 *)(*(u64 *)v378 + 24) + 32);
              v495 = v371 + 5.2;
              DrawHai3DExCalc(v371 + 5.2, 0.0, 44.0, v498, 6, v404);
              v494 = *(u32 *)(*(u64 *)(*(u64 *)v378 + 24) + 32);
              goto LABEL_1445;
            }
            if (v482)
            {
              if (v481 == *((u32 *)&v480->dora->obj.klass + v479))
                goto LABEL_1385;
LABEL_1394:
              v483 = *(u32 *)(*(u64 *)(*(u64 *)v378 + 24) + 32);
              if (v483 == *((u32 *)&Work->uraDora->obj.klass + v479))
              {
                if (Work->agariPlayerIndex != 2)
                  goto LABEL_1386;
LABEL_1385:
                v404 = 3;
              }
LABEL_1386:
              ++v479;
              continue;
            }
            break;
          }
          if (v481 != *((u32 *)&Work->dora->obj.klass + v479))
            goto LABEL_1394;
          goto LABEL_1385;
        }
        v410 = *(u32 *)(v377 + 20);
        if (v410 != 3)
        {
          if (v410 != 1)
          {
            if (v410)
              goto LABEL_1381;
            v412 = 0;
            v413 = 8;
            while (2)
            {
              v414 = Work;
              v415 = *(u32 *)(*(u64 *)(*(u64 *)v378 + 24) + 32);
              if (v413 - 8 >= v414->doraNum)
              {
                if (v416)
                {
                  goto LABEL_1533;
                }
                else
                {
LABEL_1533:
                }
                DrawHai3DExCalc(v371, 0.0, 44.0, v415, 6, v412);
                v524 = *(u32 *)(*(u64 *)(*(u64 *)v378 + 24) + 32);
                DrawHai3DExCalc(v371 + 4.0, 0.0, 44.0, v524, 5, v412);
                v525 = *(u32 *)(*(u64 *)(*(u64 *)v378 + 24) + 32);
                v475 = (f32)(v371 + 5.2) + 4.0;
LABEL_1555:
                v476 = v525;
                v477 = 6;
                goto LABEL_1380;
              }
              if (v416)
              {
                if (v415 == *((u32 *)&v414->dora->obj.klass + v413))
                  goto LABEL_1189;
LABEL_1198:
                v417 = *(u32 *)(*(u64 *)(*(u64 *)v378 + 24) + 32);
                if (v417 == *((u32 *)&Work->uraDora->obj.klass + v413))
                {
                  if (Work->agariPlayerIndex != 2)
                    goto LABEL_1190;
LABEL_1189:
                  v412 = 3;
                }
LABEL_1190:
                ++v413;
                continue;
              }
              break;
            }
            if (v415 != *((u32 *)&Work->dora->obj.klass + v413))
              goto LABEL_1198;
            goto LABEL_1189;
          }
          v412 = 0;
          v508 = 8;
          while (2)
          {
            v509 = Work;
            v510 = *(u32 *)(*(u64 *)(*(u64 *)v378 + 24) + 32);
            if (v508 - 8 >= v509->doraNum)
            {
              if (v511)
              {
                goto LABEL_1505;
              }
              else
              {
LABEL_1505:
              }
              DrawHai3DExCalc(v371, 0.0, 44.0, v510, 6, v412);
              v515 = *(u32 *)(*(u64 *)(*(u64 *)v378 + 24) + 32);
              DrawHai3DExCalc(v371 + 4.0, 0.0, 44.0, v515, 6, v412);
              v464 = *(u32 *)(*(u64 *)(*(u64 *)v378 + 24) + 32);
              goto LABEL_1377;
            }
            if (v511)
            {
              if (v510 == *((u32 *)&v509->dora->obj.klass + v508))
                goto LABEL_1467;
LABEL_1476:
              v512 = *(u32 *)(*(u64 *)(*(u64 *)v378 + 24) + 32);
              if (v512 == *((u32 *)&Work->uraDora->obj.klass + v508))
              {
                if (Work->agariPlayerIndex != 2)
                  goto LABEL_1468;
LABEL_1467:
                v412 = 3;
              }
LABEL_1468:
              ++v508;
              continue;
            }
            break;
          }
          if (v510 != *((u32 *)&Work->dora->obj.klass + v508))
            goto LABEL_1476;
          goto LABEL_1467;
        }
        v412 = 0;
        v517 = 8;
        while (2)
        {
          v518 = Work;
          v519 = *(u32 *)(*(u64 *)(*(u64 *)v378 + 24) + 32);
          if (v517 - 8 >= v518->doraNum)
          {
            if (v520)
            {
              goto LABEL_1545;
            }
            else
            {
LABEL_1545:
            }
            DrawHai3DExCalc(v371, 0.0, 44.0, v519, 5, v412);
            v528 = *(u32 *)(*(u64 *)(*(u64 *)v378 + 24) + 32);
            DrawHai3DExCalc(v371 + 5.2, 0.0, 44.0, v528, 6, v412);
            v525 = *(u32 *)(*(u64 *)(*(u64 *)v378 + 24) + 32);
            v475 = (f32)(v371 + 5.2) + 4.0;
            goto LABEL_1555;
          }
          if (v520)
          {
            if (v519 == *((u32 *)&v518->dora->obj.klass + v517))
              goto LABEL_1513;
LABEL_1522:
            v521 = *(u32 *)(*(u64 *)(*(u64 *)v378 + 24) + 32);
            if (v521 == *((u32 *)&Work->uraDora->obj.klass + v517))
            {
              if (Work->agariPlayerIndex != 2)
                goto LABEL_1514;
LABEL_1513:
              v412 = 3;
            }
LABEL_1514:
            ++v517;
            continue;
          }
          break;
        }
        if (v519 != *((u32 *)&Work->dora->obj.klass + v517))
          goto LABEL_1522;
        goto LABEL_1513;
      }
      if ((u32)v380 > 0x10000080)
      {
        if (v380 != 268435712)
        {
          if (v380 != 268435968)
            goto LABEL_1096;
          v382 = 0;
          v383 = 8;
          while (2)
          {
            v384 = Work;
            v385 = *(u32 *)(*(u64 *)(*(u64 *)v378 + 24) + 40);
            if (v383 - 8 >= v384->doraNum)
            {
              if (v386)
              {
                goto LABEL_1244;
              }
              else
              {
LABEL_1244:
              }
              DrawHai3DExCalc(v371, 0.0, 44.0, v385, 6, v382);
              v435 = 0;
              v436 = 8;
              while (2)
              {
                v437 = Work;
                v438 = *(u32 *)(*(u64 *)(*(u64 *)v378 + 24) + 36);
                if (v436 - 8 >= v437->doraNum)
                {
                  if (v439)
                  {
                    goto LABEL_1310;
                  }
                  else
                  {
LABEL_1310:
                  }
                  DrawHai3DExCalc(v371 + 4.0, 0.0, 44.0, v438, 6, v435);
                  v412 = 0;
                  v462 = 8;
                  while (2)
                  {
                    v463 = Work;
                    v464 = *(u32 *)(*(u64 *)(*(u64 *)v378 + 24) + 32);
                    if (v462 - 8 >= v463->doraNum)
                      goto LABEL_1374;
                    if (v465)
                    {
                      if (v464 == *((u32 *)&v463->dora->obj.klass + v462))
                        goto LABEL_1312;
LABEL_1321:
                      v466 = *(u32 *)(*(u64 *)(*(u64 *)v378 + 24) + 32);
                      if (v466 == *((u32 *)&Work->uraDora->obj.klass + v462))
                      {
                        if (Work->agariPlayerIndex != 2)
                          goto LABEL_1313;
LABEL_1312:
                        v412 = 3;
                      }
LABEL_1313:
                      ++v462;
                      continue;
                    }
                    break;
                  }
                  if (v464 != *((u32 *)&Work->dora->obj.klass + v462))
                    goto LABEL_1321;
                  goto LABEL_1312;
                }
                if (v439)
                {
                  if (v438 == *((u32 *)&v437->dora->obj.klass + v436))
                    goto LABEL_1246;
LABEL_1255:
                  v440 = *(u32 *)(*(u64 *)(*(u64 *)v378 + 24) + 36);
                  if (v440 == *((u32 *)&Work->uraDora->obj.klass + v436))
                  {
                    if (Work->agariPlayerIndex != 2)
                      goto LABEL_1247;
LABEL_1246:
                    v435 = 3;
                  }
LABEL_1247:
                  ++v436;
                  continue;
                }
                break;
              }
              if (v438 != *((u32 *)&Work->dora->obj.klass + v436))
                goto LABEL_1255;
              goto LABEL_1246;
            }
            if (v386)
            {
              if (v385 == *((u32 *)&v384->dora->obj.klass + v383))
                goto LABEL_1102;
LABEL_1111:
              v387 = *(u32 *)(*(u64 *)(*(u64 *)v378 + 24) + 40);
              if (v387 == *((u32 *)&Work->uraDora->obj.klass + v383))
              {
                if (Work->agariPlayerIndex != 2)
                  goto LABEL_1103;
LABEL_1102:
                v382 = 3;
              }
LABEL_1103:
              ++v383;
              continue;
            }
            break;
          }
          if (v385 != *((u32 *)&Work->dora->obj.klass + v383))
            goto LABEL_1111;
          goto LABEL_1102;
        }
        v426 = 0;
        v427 = 8;
        while (2)
        {
          v428 = Work;
          v429 = *(u32 *)(*(u64 *)(*(u64 *)v378 + 24) + 40);
          if (v427 - 8 >= v428->doraNum)
          {
            if (v430)
            {
              goto LABEL_1288;
            }
            else
            {
LABEL_1288:
            }
            DrawHai3DExCalc(v371, 0.0, 44.0, v429, 6, v426);
            v453 = 0;
            v454 = 8;
            while (2)
            {
              v455 = Work;
              v456 = *(u32 *)(*(u64 *)(*(u64 *)v378 + 24) + 32);
              if (v454 - 8 >= v455->doraNum)
              {
                if (v457)
                {
                  goto LABEL_1354;
                }
                else
                {
LABEL_1354:
                }
                DrawHai3DExCalc(v371 + 4.0, 0.0, 44.0, v456, 6, v453);
                v412 = 0;
                v472 = 8;
                while (2)
                {
                  v473 = Work;
                  v464 = *(u32 *)(*(u64 *)(*(u64 *)v378 + 24) + 36);
                  if (v472 - 8 >= v473->doraNum)
                    goto LABEL_1374;
                  if (v465)
                  {
                    if (v464 == *((u32 *)&v473->dora->obj.klass + v472))
                      goto LABEL_1356;
LABEL_1365:
                    v474 = *(u32 *)(*(u64 *)(*(u64 *)v378 + 24) + 36);
                    if (v474 == *((u32 *)&Work->uraDora->obj.klass + v472))
                    {
                      if (Work->agariPlayerIndex != 2)
                        goto LABEL_1357;
LABEL_1356:
                      v412 = 3;
                    }
LABEL_1357:
                    ++v472;
                    continue;
                  }
                  break;
                }
                if (v464 != *((u32 *)&Work->dora->obj.klass + v472))
                  goto LABEL_1365;
                goto LABEL_1356;
              }
              if (v457)
              {
                if (v456 == *((u32 *)&v455->dora->obj.klass + v454))
                  goto LABEL_1290;
LABEL_1299:
                v458 = *(u32 *)(*(u64 *)(*(u64 *)v378 + 24) + 32);
                if (v458 == *((u32 *)&Work->uraDora->obj.klass + v454))
                {
                  if (Work->agariPlayerIndex != 2)
                    goto LABEL_1291;
LABEL_1290:
                  v453 = 3;
                }
LABEL_1291:
                ++v454;
                continue;
              }
              break;
            }
            if (v456 != *((u32 *)&Work->dora->obj.klass + v454))
              goto LABEL_1299;
            goto LABEL_1290;
          }
          if (v430)
          {
            if (v429 == *((u32 *)&v428->dora->obj.klass + v427))
              goto LABEL_1224;
LABEL_1233:
            v431 = *(u32 *)(*(u64 *)(*(u64 *)v378 + 24) + 40);
            if (v431 == *((u32 *)&Work->uraDora->obj.klass + v427))
            {
              if (Work->agariPlayerIndex != 2)
                goto LABEL_1225;
LABEL_1224:
              v426 = 3;
            }
LABEL_1225:
            ++v427;
            continue;
          }
          break;
        }
        if (v429 != *((u32 *)&Work->dora->obj.klass + v427))
          goto LABEL_1233;
        goto LABEL_1224;
      }
      if (v380 == 64)
        goto LABEL_1163;
      if (v380 != 268435584)
        goto LABEL_1096;
      v396 = 0;
      for (k = 8; ; ++k)
      {
        v398 = Work;
        v399 = *(u32 *)(*(u64 *)(*(u64 *)v378 + 24) + 36);
        if (k - 8 >= v398->doraNum)
          break;
        if (v400)
        {
          if (v399 == *((u32 *)&v398->dora->obj.klass + k))
            goto LABEL_1145;
        }
        else
        {
          if (v399 == *((u32 *)&Work->dora->obj.klass + k))
            goto LABEL_1145;
        }
        v401 = *(u32 *)(*(u64 *)(*(u64 *)v378 + 24) + 36);
        if (v401 != *((u32 *)&Work->uraDora->obj.klass + k))
          continue;
        if (Work->agariPlayerIndex == 2)
          goto LABEL_1145;
        goto LABEL_9003;
        if (Work->agariPlayerIndex == 2)
        {
LABEL_1145:
          v396 = 3;
          continue;
        }
LABEL_9003:
      }
      if (v400)
      {
        goto LABEL_1266;
      }
      else
      {
LABEL_1266:
      }
      DrawHai3DExCalc(v371, 0.0, 44.0, v399, 6, v396);
      v444 = 0;
      v445 = 8;
      while (2)
      {
        v446 = Work;
        v447 = *(u32 *)(*(u64 *)(*(u64 *)v378 + 24) + 32);
        if (v445 - 8 < v446->doraNum)
        {
          if (v448)
          {
            if (v447 == *((u32 *)&v446->dora->obj.klass + v445))
              goto LABEL_1268;
LABEL_1277:
            v449 = *(u32 *)(*(u64 *)(*(u64 *)v378 + 24) + 32);
            if (v449 == *((u32 *)&Work->uraDora->obj.klass + v445))
            {
              if (Work->agariPlayerIndex != 2)
                goto LABEL_1269;
LABEL_1268:
              v444 = 3;
            }
LABEL_1269:
            ++v445;
            continue;
          }
          if (v447 != *((u32 *)&Work->dora->obj.klass + v445))
            goto LABEL_1277;
          goto LABEL_1268;
        }
        break;
      }
      if (v448)
      {
        goto LABEL_1332;
      }
      else
      {
LABEL_1332:
      }
      DrawHai3DExCalc(v371 + 4.0, 0.0, 44.0, v447, 6, v444);
      v412 = 0;
      v468 = 8;
      while (2)
      {
        v469 = Work;
        v464 = *(u32 *)(*(u64 *)(*(u64 *)v378 + 24) + 40);
        if (v468 - 8 < v469->doraNum)
        {
          if (v465)
          {
            if (v464 == *((u32 *)&v469->dora->obj.klass + v468))
              goto LABEL_1334;
LABEL_1343:
            v470 = *(u32 *)(*(u64 *)(*(u64 *)v378 + 24) + 40);
            if (v470 == *((u32 *)&Work->uraDora->obj.klass + v468))
            {
              if (Work->agariPlayerIndex != 2)
                goto LABEL_1335;
LABEL_1334:
              v412 = 3;
            }
LABEL_1335:
            ++v468;
            continue;
          }
          if (v464 != *((u32 *)&Work->dora->obj.klass + v468))
            goto LABEL_1343;
          goto LABEL_1334;
        }
        break;
      }
LABEL_1374:
      if (!v465)
      {
        goto LABEL_1377;
      }
LABEL_1377:
      v475 = v371 + 8.0;
      v476 = v464;
      v477 = 5;
LABEL_1380:
      DrawHai3DExCalc(v475, 0.0, 44.0, v476, v477, v412);
LABEL_1381:
      v375 = 13.2;
LABEL_1095:
      v371 = v371 + v375;
LABEL_1096:
      if (++v370 >= v368->nakiNum)
      {
        break;
      }
    }
  }
  v529 = Work->players[3];
  if (v529->nakiNum >= 1)
  {
    v530 = v529->naki;
    v531 = 0;
    v532 = -38.0;
    do
    {
      v537 = (s64)v530 + 8 * v531;
      v540 = *(u64 *)(v537 + 32);
      v539 = v537 + 32;
      v538 = v540;
      v541 = *(u32 *)(v540 + 16);
      if (v541 <= 32)
      {
        if (v541 != 32)
        {
          if (v541 != 8)
          {
            if (v541 != 4)
              goto LABEL_1585;
            v550 = 0;
            v551 = 8;
            while (2)
            {
              v552 = Work;
              v553 = *(u32 *)(*(u64 *)(*(u64 *)v539 + 24) + 32);
              if (v551 - 8 >= v552->doraNum)
              {
                if (v554)
                {
                  goto LABEL_1698;
                }
                else
                {
LABEL_1698:
                }
                DrawHai3DExCalc(-44.0, 0.0, v532 + 4.0, v553, 7, v550);
                v581 = *(u32 *)(*(u64 *)(*(u64 *)v539 + 24) + 32);
                DrawHai3DExCalc(-44.0, 0.0, v532 + 8.0, v581, 12, v550);
                v583 = *(u32 *)(*(u64 *)(*(u64 *)v539 + 24) + 32);
                DrawHai3DExCalc(-44.0, 0.0, v532 + 12.0, v583, 12, v550);
                v585 = *(u32 *)(*(u64 *)(*(u64 *)v539 + 24) + 32);
                v532 = v532 + 16.0;
                DrawHai3DExCalc(-44.0, 0.0, v532, v585, 7, v550);
                goto LABEL_1585;
              }
              if (v554)
              {
                if (v553 == *((u32 *)&v552->dora->obj.klass + v551))
                  goto LABEL_1613;
LABEL_1622:
                v555 = *(u32 *)(*(u64 *)(*(u64 *)v539 + 24) + 32);
                if (v555 == *((u32 *)&Work->uraDora->obj.klass + v551))
                {
                  if (Work->agariPlayerIndex != 3)
                    goto LABEL_1614;
LABEL_1613:
                  v550 = 3;
                }
LABEL_1614:
                ++v551;
                continue;
              }
              break;
            }
            if (v553 != *((u32 *)&Work->dora->obj.klass + v551))
              goto LABEL_1622;
            goto LABEL_1613;
          }
LABEL_1652:
          v563 = *(u32 *)(v538 + 20);
          if (v563)
          {
            if (v563 != 2)
            {
              if (v563 != 1)
                goto LABEL_1583;
              v565 = 0;
              v566 = 8;
              while (2)
              {
                v567 = Work;
                v568 = *(u32 *)(*(u64 *)(*(u64 *)v539 + 24) + 32);
                if (v566 - 8 >= v567->doraNum)
                {
                  if (v569)
                  {
                    goto LABEL_1914;
                  }
                  else
                  {
LABEL_1914:
                  }
                  DrawHai3DExCalc(-44.0, 0.0, v532 + 4.0, v568, 7, v565);
                  v654 = *(u32 *)(*(u64 *)(*(u64 *)v539 + 24) + 32);
                  v655 = v654;
                  v656 = 6;
                  v657 = v532 + 5.2;
                  v658 = (f32)(v532 + 5.2) + 4.0;
LABEL_1928:
                  DrawHai3DExCalc(-44.0, 0.0, v658, v655, v656, v565);
                  v662 = *(u32 *)(*(u64 *)(*(u64 *)v539 + 24) + 32);
                  DrawHai3DExCalc(-44.0, 0.0, v657 + 8.0, v662, 7, v565);
                  v663 = *(u32 *)(*(u64 *)(*(u64 *)v539 + 24) + 32);
                  v533 = v657 + 12.0;
                  v534 = v663;
                  v535 = 7;
LABEL_1582:
                  DrawHai3DExCalc(-44.0, 0.0, v533, v534, v535, v565);
LABEL_1583:
                  v536 = 17.2;
                  goto LABEL_1584;
                }
                if (v569)
                {
                  if (v568 == *((u32 *)&v567->dora->obj.klass + v566))
                    goto LABEL_1656;
LABEL_1665:
                  v570 = *(u32 *)(*(u64 *)(*(u64 *)v539 + 24) + 32);
                  if (v570 == *((u32 *)&Work->uraDora->obj.klass + v566))
                  {
                    if (Work->agariPlayerIndex != 3)
                      goto LABEL_1657;
LABEL_1656:
                    v565 = 3;
                  }
LABEL_1657:
                  ++v566;
                  continue;
                }
                break;
              }
              if (v568 != *((u32 *)&Work->dora->obj.klass + v566))
                goto LABEL_1665;
              goto LABEL_1656;
            }
            v565 = 0;
            v647 = 8;
            while (2)
            {
              v648 = Work;
              v649 = *(u32 *)(*(u64 *)(*(u64 *)v539 + 24) + 32);
              if (v647 - 8 >= v648->doraNum)
              {
                if (v650)
                {
                  goto LABEL_1936;
                }
                else
                {
LABEL_1936:
                }
                DrawHai3DExCalc(-44.0, 0.0, v532 + 4.0, v649, 7, v565);
                v666 = *(u32 *)(*(u64 *)(*(u64 *)v539 + 24) + 32);
                DrawHai3DExCalc(-44.0, 0.0, v532 + 8.0, v666, 7, v565);
                v668 = *(u32 *)(*(u64 *)(*(u64 *)v539 + 24) + 32);
                DrawHai3DExCalc(-44.0, 0.0, v532 + 12.0, v668, 7, v565);
                v669 = *(u32 *)(*(u64 *)(*(u64 *)v539 + 24) + 32);
                v534 = v669;
                v535 = 6;
                v533 = (f32)(v532 + 5.2) + 12.0;
                goto LABEL_1582;
              }
              if (v650)
              {
                if (v649 == *((u32 *)&v648->dora->obj.klass + v647))
                  goto LABEL_1894;
LABEL_1903:
                v651 = *(u32 *)(*(u64 *)(*(u64 *)v539 + 24) + 32);
                if (v651 == *((u32 *)&Work->uraDora->obj.klass + v647))
                {
                  if (Work->agariPlayerIndex != 3)
                    goto LABEL_1895;
LABEL_1894:
                  v565 = 3;
                }
LABEL_1895:
                ++v647;
                continue;
              }
              break;
            }
            if (v649 != *((u32 *)&Work->dora->obj.klass + v647))
              goto LABEL_1903;
            goto LABEL_1894;
          }
          v565 = 0;
          v641 = 8;
          while (2)
          {
            v642 = Work;
            v643 = *(u32 *)(*(u64 *)(*(u64 *)v539 + 24) + 32);
            if (v641 - 8 >= v642->doraNum)
            {
              if (v644)
              {
                goto LABEL_1922;
              }
              else
              {
LABEL_1922:
              }
              v657 = v532 + 5.2;
              DrawHai3DExCalc(-44.0, 0.0, v532 + 5.2, v643, 6, v565);
              v660 = *(u32 *)(*(u64 *)(*(u64 *)v539 + 24) + 32);
              v658 = v657 + 4.0;
              v655 = v660;
              v656 = 7;
              goto LABEL_1928;
            }
            if (v644)
            {
              if (v643 == *((u32 *)&v642->dora->obj.klass + v641))
                goto LABEL_1875;
LABEL_1884:
              v645 = *(u32 *)(*(u64 *)(*(u64 *)v539 + 24) + 32);
              if (v645 == *((u32 *)&Work->uraDora->obj.klass + v641))
              {
                if (Work->agariPlayerIndex != 3)
                  goto LABEL_1876;
LABEL_1875:
                v565 = 3;
              }
LABEL_1876:
              ++v641;
              continue;
            }
            break;
          }
          if (v643 != *((u32 *)&Work->dora->obj.klass + v641))
            goto LABEL_1884;
          goto LABEL_1875;
        }
        v571 = *(u32 *)(v538 + 20);
        if (v571)
        {
          if (v571 != 2)
          {
            if (v571 != 1)
              goto LABEL_1871;
            v573 = 0;
            v574 = 8;
            while (2)
            {
              v575 = Work;
              v576 = *(u32 *)(*(u64 *)(*(u64 *)v539 + 24) + 32);
              if (v574 - 8 >= v575->doraNum)
              {
                if (v577)
                {
                  goto LABEL_2023;
                }
                else
                {
LABEL_2023:
                }
                DrawHai3DExCalc(-44.0, 0.0, v532 + 4.0, v576, 7, v573);
                v688 = *(u32 *)(*(u64 *)(*(u64 *)v539 + 24) + 32);
                v689 = v532 + 5.2;
                DrawHai3DExCalc(-44.0, 0.0, (f32)(v532 + 5.2) + 4.0, v688, 6, v573);
                v690 = *(u32 *)(*(u64 *)(*(u64 *)v539 + 24) + 40);
LABEL_2039:
                v637 = v689 + 8.0;
                v638 = v690;
                v639 = 7;
                goto LABEL_1870;
              }
              if (v577)
              {
                if (v576 == *((u32 *)&v575->dora->obj.klass + v574))
                  goto LABEL_1678;
LABEL_1687:
                v578 = *(u32 *)(*(u64 *)(*(u64 *)v539 + 24) + 32);
                if (v578 == *((u32 *)&Work->uraDora->obj.klass + v574))
                {
                  if (Work->agariPlayerIndex != 3)
                    goto LABEL_1679;
LABEL_1678:
                  v573 = 3;
                }
LABEL_1679:
                ++v574;
                continue;
              }
              break;
            }
            if (v576 != *((u32 *)&Work->dora->obj.klass + v574))
              goto LABEL_1687;
            goto LABEL_1678;
          }
          v573 = 0;
          v672 = 8;
          while (2)
          {
            v673 = Work;
            v674 = *(u32 *)(*(u64 *)(*(u64 *)v539 + 24) + 32);
            if (v672 - 8 >= v673->doraNum)
            {
              if (v675)
              {
                goto LABEL_1992;
              }
              else
              {
LABEL_1992:
              }
              DrawHai3DExCalc(-44.0, 0.0, v532 + 4.0, v674, 7, v573);
              v679 = *(u32 *)(*(u64 *)(*(u64 *)v539 + 24) + 32);
              DrawHai3DExCalc(-44.0, 0.0, v532 + 8.0, v679, 7, v573);
              v626 = *(u32 *)(*(u64 *)(*(u64 *)v539 + 24) + 32);
              v637 = (f32)(v532 + 5.2) + 8.0;
              goto LABEL_1869;
            }
            if (v675)
            {
              if (v674 == *((u32 *)&v673->dora->obj.klass + v672))
                goto LABEL_1954;
LABEL_1963:
              v676 = *(u32 *)(*(u64 *)(*(u64 *)v539 + 24) + 32);
              if (v676 == *((u32 *)&Work->uraDora->obj.klass + v672))
              {
                if (Work->agariPlayerIndex != 3)
                  goto LABEL_1955;
LABEL_1954:
                v573 = 3;
              }
LABEL_1955:
              ++v672;
              continue;
            }
            break;
          }
          if (v674 != *((u32 *)&Work->dora->obj.klass + v672))
            goto LABEL_1963;
          goto LABEL_1954;
        }
        v573 = 0;
        v681 = 8;
        while (2)
        {
          v682 = Work;
          v683 = *(u32 *)(*(u64 *)(*(u64 *)v539 + 24) + 32);
          if (v681 - 8 >= v682->doraNum)
          {
            if (v684)
            {
              goto LABEL_2032;
            }
            else
            {
LABEL_2032:
            }
            v689 = v532 + 5.2;
            DrawHai3DExCalc(-44.0, 0.0, v532 + 5.2, v683, 6, v573);
            v693 = *(u32 *)(*(u64 *)(*(u64 *)v539 + 24) + 32);
            DrawHai3DExCalc(-44.0, 0.0, v689 + 4.0, v693, 7, v573);
            v690 = *(u32 *)(*(u64 *)(*(u64 *)v539 + 24) + 32);
            goto LABEL_2039;
          }
          if (v684)
          {
            if (v683 == *((u32 *)&v682->dora->obj.klass + v681))
              goto LABEL_2003;
LABEL_2012:
            v685 = *(u32 *)(*(u64 *)(*(u64 *)v539 + 24) + 32);
            if (v685 == *((u32 *)&Work->uraDora->obj.klass + v681))
            {
              if (Work->agariPlayerIndex != 3)
                goto LABEL_2004;
LABEL_2003:
              v573 = 3;
            }
LABEL_2004:
            ++v681;
            continue;
          }
          break;
        }
        if (v683 != *((u32 *)&Work->dora->obj.klass + v681))
          goto LABEL_2012;
        goto LABEL_2003;
      }
      if ((u32)v541 > 0x10000080)
      {
        if (v541 != 268435712)
        {
          if (v541 != 268435968)
            goto LABEL_1585;
          v543 = 0;
          v544 = 8;
          while (2)
          {
            v545 = Work;
            v546 = *(u32 *)(*(u64 *)(*(u64 *)v539 + 24) + 40);
            if (v544 - 8 >= v545->doraNum)
            {
              if (v547)
              {
                goto LABEL_1733;
              }
              else
              {
LABEL_1733:
              }
              DrawHai3DExCalc(-44.0, 0.0, v532 + 4.0, v546, 7, v543);
              v596 = 0;
              v597 = 8;
              while (2)
              {
                v598 = Work;
                v599 = *(u32 *)(*(u64 *)(*(u64 *)v539 + 24) + 36);
                if (v597 - 8 >= v598->doraNum)
                {
                  if (v600)
                  {
                    goto LABEL_1799;
                  }
                  else
                  {
LABEL_1799:
                  }
                  v621 = v532 + 8.0;
                  DrawHai3DExCalc(-44.0, 0.0, v532 + 8.0, v599, 7, v596);
                  v573 = 0;
                  v624 = 8;
                  while (2)
                  {
                    v625 = Work;
                    v626 = *(u32 *)(*(u64 *)(*(u64 *)v539 + 24) + 32);
                    if (v624 - 8 >= v625->doraNum)
                      goto LABEL_1863;
                    if (v627)
                    {
                      if (v626 == *((u32 *)&v625->dora->obj.klass + v624))
                        goto LABEL_1801;
LABEL_1810:
                      v628 = *(u32 *)(*(u64 *)(*(u64 *)v539 + 24) + 32);
                      if (v628 == *((u32 *)&Work->uraDora->obj.klass + v624))
                      {
                        if (Work->agariPlayerIndex != 3)
                          goto LABEL_1802;
LABEL_1801:
                        v573 = 3;
                      }
LABEL_1802:
                      ++v624;
                      continue;
                    }
                    break;
                  }
                  if (v626 != *((u32 *)&Work->dora->obj.klass + v624))
                    goto LABEL_1810;
                  goto LABEL_1801;
                }
                if (v600)
                {
                  if (v599 == *((u32 *)&v598->dora->obj.klass + v597))
                    goto LABEL_1735;
LABEL_1744:
                  v601 = *(u32 *)(*(u64 *)(*(u64 *)v539 + 24) + 36);
                  if (v601 == *((u32 *)&Work->uraDora->obj.klass + v597))
                  {
                    if (Work->agariPlayerIndex != 3)
                      goto LABEL_1736;
LABEL_1735:
                    v596 = 3;
                  }
LABEL_1736:
                  ++v597;
                  continue;
                }
                break;
              }
              if (v599 != *((u32 *)&Work->dora->obj.klass + v597))
                goto LABEL_1744;
              goto LABEL_1735;
            }
            if (v547)
            {
              if (v546 == *((u32 *)&v545->dora->obj.klass + v544))
                goto LABEL_1591;
LABEL_1600:
              v548 = *(u32 *)(*(u64 *)(*(u64 *)v539 + 24) + 40);
              if (v548 == *((u32 *)&Work->uraDora->obj.klass + v544))
              {
                if (Work->agariPlayerIndex != 3)
                  goto LABEL_1592;
LABEL_1591:
                v543 = 3;
              }
LABEL_1592:
              ++v544;
              continue;
            }
            break;
          }
          if (v546 != *((u32 *)&Work->dora->obj.klass + v544))
            goto LABEL_1600;
          goto LABEL_1591;
        }
        v587 = 0;
        v588 = 8;
        while (2)
        {
          v589 = Work;
          v590 = *(u32 *)(*(u64 *)(*(u64 *)v539 + 24) + 40);
          if (v588 - 8 >= v589->doraNum)
          {
            if (v591)
            {
              goto LABEL_1777;
            }
            else
            {
LABEL_1777:
            }
            DrawHai3DExCalc(-44.0, 0.0, v532 + 4.0, v590, 7, v587);
            v614 = 0;
            v615 = 8;
            while (2)
            {
              v616 = Work;
              v617 = *(u32 *)(*(u64 *)(*(u64 *)v539 + 24) + 32);
              if (v615 - 8 >= v616->doraNum)
              {
                if (v618)
                {
                  goto LABEL_1843;
                }
                else
                {
LABEL_1843:
                }
                v621 = v532 + 8.0;
                DrawHai3DExCalc(-44.0, 0.0, v532 + 8.0, v617, 7, v614);
                v573 = 0;
                v634 = 8;
                while (2)
                {
                  v635 = Work;
                  v626 = *(u32 *)(*(u64 *)(*(u64 *)v539 + 24) + 36);
                  if (v634 - 8 >= v635->doraNum)
                    goto LABEL_1863;
                  if (v627)
                  {
                    if (v626 == *((u32 *)&v635->dora->obj.klass + v634))
                      goto LABEL_1845;
LABEL_1854:
                    v636 = *(u32 *)(*(u64 *)(*(u64 *)v539 + 24) + 36);
                    if (v636 == *((u32 *)&Work->uraDora->obj.klass + v634))
                    {
                      if (Work->agariPlayerIndex != 3)
                        goto LABEL_1846;
LABEL_1845:
                      v573 = 3;
                    }
LABEL_1846:
                    ++v634;
                    continue;
                  }
                  break;
                }
                if (v626 != *((u32 *)&Work->dora->obj.klass + v634))
                  goto LABEL_1854;
                goto LABEL_1845;
              }
              if (v618)
              {
                if (v617 == *((u32 *)&v616->dora->obj.klass + v615))
                  goto LABEL_1779;
LABEL_1788:
                v619 = *(u32 *)(*(u64 *)(*(u64 *)v539 + 24) + 32);
                if (v619 == *((u32 *)&Work->uraDora->obj.klass + v615))
                {
                  if (Work->agariPlayerIndex != 3)
                    goto LABEL_1780;
LABEL_1779:
                  v614 = 3;
                }
LABEL_1780:
                ++v615;
                continue;
              }
              break;
            }
            if (v617 != *((u32 *)&Work->dora->obj.klass + v615))
              goto LABEL_1788;
            goto LABEL_1779;
          }
          if (v591)
          {
            if (v590 == *((u32 *)&v589->dora->obj.klass + v588))
              goto LABEL_1713;
LABEL_1722:
            v592 = *(u32 *)(*(u64 *)(*(u64 *)v539 + 24) + 40);
            if (v592 == *((u32 *)&Work->uraDora->obj.klass + v588))
            {
              if (Work->agariPlayerIndex != 3)
                goto LABEL_1714;
LABEL_1713:
              v587 = 3;
            }
LABEL_1714:
            ++v588;
            continue;
          }
          break;
        }
        if (v590 != *((u32 *)&Work->dora->obj.klass + v588))
          goto LABEL_1722;
        goto LABEL_1713;
      }
      if (v541 == 64)
        goto LABEL_1652;
      if (v541 != 268435584)
        goto LABEL_1585;
      v557 = 0;
      for (m = 8; ; ++m)
      {
        v559 = Work;
        v560 = *(u32 *)(*(u64 *)(*(u64 *)v539 + 24) + 36);
        if (m - 8 >= v559->doraNum)
          break;
        if (v561)
        {
          if (v560 == *((u32 *)&v559->dora->obj.klass + m))
            goto LABEL_1634;
        }
        else
        {
          if (v560 == *((u32 *)&Work->dora->obj.klass + m))
            goto LABEL_1634;
        }
        v562 = *(u32 *)(*(u64 *)(*(u64 *)v539 + 24) + 36);
        if (v562 != *((u32 *)&Work->uraDora->obj.klass + m))
          continue;
        if (Work->agariPlayerIndex == 3)
          goto LABEL_1634;
        goto LABEL_9004;
        if (Work->agariPlayerIndex == 3)
        {
LABEL_1634:
          v557 = 3;
          continue;
        }
LABEL_9004:
      }
      if (v561)
      {
        goto LABEL_1755;
      }
      else
      {
LABEL_1755:
      }
      DrawHai3DExCalc(-44.0, 0.0, v532 + 4.0, v560, 7, v557);
      v605 = 0;
      v606 = 8;
      while (2)
      {
        v607 = Work;
        v608 = *(u32 *)(*(u64 *)(*(u64 *)v539 + 24) + 32);
        if (v606 - 8 < v607->doraNum)
        {
          if (v609)
          {
            if (v608 == *((u32 *)&v607->dora->obj.klass + v606))
              goto LABEL_1757;
LABEL_1766:
            v610 = *(u32 *)(*(u64 *)(*(u64 *)v539 + 24) + 32);
            if (v610 == *((u32 *)&Work->uraDora->obj.klass + v606))
            {
              if (Work->agariPlayerIndex != 3)
                goto LABEL_1758;
LABEL_1757:
              v605 = 3;
            }
LABEL_1758:
            ++v606;
            continue;
          }
          if (v608 != *((u32 *)&Work->dora->obj.klass + v606))
            goto LABEL_1766;
          goto LABEL_1757;
        }
        break;
      }
      if (v609)
      {
        goto LABEL_1821;
      }
      else
      {
LABEL_1821:
      }
      v621 = v532 + 8.0;
      DrawHai3DExCalc(-44.0, 0.0, v532 + 8.0, v608, 7, v605);
      v573 = 0;
      v630 = 8;
      while (2)
      {
        v631 = Work;
        v626 = *(u32 *)(*(u64 *)(*(u64 *)v539 + 24) + 40);
        if (v630 - 8 < v631->doraNum)
        {
          if (v627)
          {
            if (v626 == *((u32 *)&v631->dora->obj.klass + v630))
              goto LABEL_1823;
LABEL_1832:
            v632 = *(u32 *)(*(u64 *)(*(u64 *)v539 + 24) + 40);
            if (v632 == *((u32 *)&Work->uraDora->obj.klass + v630))
            {
              if (Work->agariPlayerIndex != 3)
                goto LABEL_1824;
LABEL_1823:
              v573 = 3;
            }
LABEL_1824:
            ++v630;
            continue;
          }
          if (v626 != *((u32 *)&Work->dora->obj.klass + v630))
            goto LABEL_1832;
          goto LABEL_1823;
        }
        break;
      }
LABEL_1863:
      v637 = v621 + 5.2;
LABEL_1869:
      v638 = v626;
      v639 = 6;
LABEL_1870:
      DrawHai3DExCalc(-44.0, 0.0, v637, v638, v639, v573);
LABEL_1871:
      v536 = 13.2;
LABEL_1584:
      v532 = v532 + v536;
LABEL_1585:
      ++v531;
    }
    while (v531 < v529->nakiNum);
  }
}

// 0x1d22990
static void DrawWanpai3DCalc(void) {
  s32 v5;
  u32 v8;
  s32 v23;
  u32 v26;
  s32 v27;
  u32 v30;
  s32 v31;
  u32 v34;
  s32 v35;
  s32 v44;
  u32 v47;
  s32 v50;
  u32 v53;
  s32 v54;
  u32 v57;
  s32 v58;
  u32 v61;
  s32 v62;
  u32 v79;
  void *v80;
  s32 v81;

  if (!Work->fDrawUraDora)
  {
    setWanpaiDrawData(1, 8);
    setWanpaiDrawData(3, 8);
    setWanpaiDrawData(5, 8);
    setWanpaiDrawData(7, 8);
    setWanpaiDrawData(9, 8);
    setWanpaiDrawData(11, 8);
    goto LABEL_61;
  }
  if (Work->doraNum <= 4)
    v5 = 8;
  else
    v5 = 4;
  setWanpaiDrawData(1, v5);
  if (Work->doraNum + 1 <= 4)
    v23 = 8;
  else
    v23 = 4;
  if (v8)
  {
    setWanpaiDrawData(3, v23);
    if (v26)
      goto LABEL_32;
    goto LABEL_31;
  }
  setWanpaiDrawData(3, v23);
  if (!v26)
  {
LABEL_31:
  }
LABEL_32:
  if (Work->doraNum + 2 <= 4)
    v27 = 8;
  else
    v27 = 4;
  if (v26)
  {
    setWanpaiDrawData(5, v27);
    if (v30)
      goto LABEL_38;
    goto LABEL_37;
  }
  setWanpaiDrawData(5, v27);
  if (!v30)
  {
LABEL_37:
  }
LABEL_38:
  if (Work->doraNum + 3 <= 4)
    v31 = 8;
  else
    v31 = 4;
  if (v30)
  {
    setWanpaiDrawData(7, v31);
    if (v34)
      goto LABEL_44;
    goto LABEL_43;
  }
  setWanpaiDrawData(7, v31);
  if (!v34)
  {
LABEL_43:
  }
LABEL_44:
  if (Work->doraNum + 4 <= 4)
    v35 = 8;
  else
    v35 = 4;
  if (v34)
  {
    setWanpaiDrawData(9, v35);
    goto LABEL_58;
  }
  else
  {
    setWanpaiDrawData(9, v35);
    goto LABEL_58;
  }
LABEL_58:
  setWanpaiDrawData(11, 8);
LABEL_61:
  setWanpaiDrawData(13, 8);
  if (Work->doraNum <= 4)
    v44 = 8;
  else
    v44 = 4;
  setWanpaiDrawData(0, v44);
  if (Work->doraNum + 1 <= 4)
    v50 = 8;
  else
    v50 = 4;
  if (v47)
  {
    setWanpaiDrawData(2, v50);
    if (v53)
      goto LABEL_79;
    goto LABEL_78;
  }
  setWanpaiDrawData(2, v50);
  if (!v53)
  {
LABEL_78:
  }
LABEL_79:
  if (Work->doraNum + 2 <= 4)
    v54 = 8;
  else
    v54 = 4;
  if (!v53)
  setWanpaiDrawData(4, v54);
  if (Work->doraNum + 3 <= 4)
    v58 = 8;
  else
    v58 = 4;
  if (v57)
  {
    setWanpaiDrawData(6, v58);
    if (v61)
      goto LABEL_92;
    goto LABEL_91;
  }
  setWanpaiDrawData(6, v58);
  if (!v61)
  {
LABEL_91:
  }
LABEL_92:
  if (Work->doraNum + 4 <= 4)
    v62 = 8;
  else
    v62 = 4;
  if (v61)
  {
    setWanpaiDrawData(8, v62);
    goto LABEL_104;
  }
  else
  {
    setWanpaiDrawData(8, v62);
    goto LABEL_104;
  }
  setWanpaiDrawData(10, 8);
  goto LABEL_116;
LABEL_104:
  setWanpaiDrawData(10, 8);
LABEL_116:
  setWanpaiDrawData(12, 8);
  if (Work->fDrawUraDora)
    goto LABEL_118;
  if (v79)
  {
LABEL_125:
    DoraWin_Front_SetData(mjnUImanager, Work->wanpai_U, 0);
    v81 = 1;
    goto LABEL_126;
  }
  else
  {
    goto LABEL_125;
  }
  goto LABEL_125;
LABEL_118:
  if (!v79)
  {
    v80 = mjnUImanager;
    goto LABEL_121;
  }
  v80 = mjnUImanager;
LABEL_121:
  DoraWin_Front_SetData(v80, Work->wanpai_U, 0);
  DoraWin_Back_SetData(mjnUImanager, Work->wanpai_D, 0);
  v81 = 2;
LABEL_126:
  DoraWin_SetActive(mjnUImanager, v81, 0);
}

// 0x1d26280
static void setWanpaiDrawData(s32 index, MJN_HAI status) {
  wanpaiUIData *wanpai_U;
  s32 v7;
  bool *enable;
  s32 *hai;
  wanpaiUIData *wanpai_D;
  s32 v14;
  Work_t *v16;
  bool *v17;
  s32 *v18;
  wanpaiUIData *v20;
  s32 v21;
  Work_t *v23;
  bool *v24;
  s32 *v25;
  wanpaiUIData *v27;
  s32 v28;
  Work_t *v30;
  bool *v31;
  s32 *v32;
  wanpaiUIData *v34;
  s32 v35;
  Work_t *v37;
  bool *v38;
  s32 *v39;

  switch (index)
  {
    case 0:
      wanpai_U = Work->wanpai_U;
      v7 = Work->wanpai[0];
      goto LABEL_10;
    case 1:
      wanpai_U = Work->wanpai_D;
      v7 = Work->wanpai[1];
LABEL_10:
      hai = wanpai_U->hai;
      enable = wanpai_U->enable;
      hai[4] = v7;
      enable[4] = status == 4;
      return;
    case 2:
      wanpai_D = Work->wanpai_U;
      v14 = Work->wanpai[2];
      goto LABEL_17;
    case 3:
      v16 = Work;
      wanpai_D = v16->wanpai_D;
      v14 = v16->wanpai[3];
LABEL_17:
      v18 = wanpai_D->hai;
      v17 = wanpai_D->enable;
      v18[3] = v14;
      v17[3] = status == 4;
      return;
    case 4:
      v20 = Work->wanpai_U;
      v21 = Work->wanpai[4];
      goto LABEL_24;
    case 5:
      v23 = Work;
      v20 = v23->wanpai_D;
      v21 = v23->wanpai[5];
LABEL_24:
      v25 = v20->hai;
      v24 = v20->enable;
      v25[2] = v21;
      v24[2] = status == 4;
      return;
    case 6:
      v27 = Work->wanpai_U;
      v28 = Work->wanpai[6];
      goto LABEL_31;
    case 7:
      v30 = Work;
      v27 = v30->wanpai_D;
      v28 = v30->wanpai[7];
LABEL_31:
      v32 = v27->hai;
      v31 = v27->enable;
      v32[1] = v28;
      v31[1] = status == 4;
      return;
    case 8:
      v34 = Work->wanpai_U;
      v35 = Work->wanpai[8];
      goto LABEL_38;
    case 9:
      v37 = Work;
      v34 = v37->wanpai_D;
      v35 = v37->wanpai[9];
LABEL_38:
      v39 = v34->hai;
      v38 = v34->enable;
      v39[0] = v35;
      v38[0] = status == 4;
      break;
    default:
      return;
  }
}

// 0x1d26570
static bool setWanpaiDrawFlag(MJN_HAI status) {
  return status == 4;
}

// 0x1d158d0
static void DrawReach3D(void) {
  dds3ModelHandle_t *v3;
  sdfModelOt_t *v5;
  Work_t *v6;
  Work_t *v7;
  Work_t *v8;
  dds3ModelHandle_t *v9;
  sdfModelOt_t *v11;
  dds3ModelHandle_t *v12;
  sdfModelOt_t *v14;
  dds3ModelHandle_t *v15;
  sdfModelOt_t *v17;

  if (Work->players[0]->reachIndex != -1)
  {
    if (Work->hideReachBou)
    {
      v3 = Work->tenbouModelHandle[0];
      v5 = ModelOt[0];
      Link(v3, v5);
    }
  }
  v6 = Work;
  if (v6->players[1]->reachIndex != -1)
  {
    v6 = Work;
    if (v6->hideReachBou != 1)
      goto LABEL_33;
  }
  goto LABEL_23;
LABEL_33:
  v6 = Work;
  v9 = v6->tenbouModelHandle[1];
  v11 = ModelOt[0];
  Link(v9, v11);
LABEL_23:
  v7 = Work;
  if (v7->players[2]->reachIndex == -1)
    goto LABEL_26;
  if (v7->hideReachBou == 2)
    goto LABEL_26;
  goto LABEL_9000;
  if (v7->hideReachBou == 2)
  {
LABEL_26:
    goto LABEL_28;
  }
LABEL_9000:
  v7 = Work;
  v12 = v7->tenbouModelHandle[2];
  v14 = ModelOt[0];
  Link(v12, v14);
LABEL_28:
  v8 = Work;
  if (v8->players[3]->reachIndex == -1)
    return;
  if (v8->hideReachBou == 3)
    return;
  v8 = Work;
  v15 = v8->tenbouModelHandle[3];
  v17 = ModelOt[0];
  Link(v15, v17);
}

// 0x1d15c90
static void DrawOya3D(void) {
  dds3ModelHandle_t *v2;
  sdfModelOt_t *v4;
  dds3ModelHandle_t *v6;
  sdfModelOt_t *v8;
  dds3ModelHandle_t *v10;
  sdfModelOt_t *v12;
  dds3ModelHandle_t *v14;
  sdfModelOt_t *v16;

  v2 = Work->oyaModelHandle[0];
  v4 = ModelOt[0];
  Link(v2, v4);
  v6 = Work->oyaModelHandle[1];
  v8 = ModelOt[0];
  Link(v6, v8);
  v10 = Work->oyaModelHandle[2];
  v12 = ModelOt[0];
  Link(v10, v12);
  v14 = Work->oyaModelHandle[3];
  v16 = ModelOt[0];
  Link(v14, v16);
}

// 0x1d15f80
static void DrawModel(void) {
  s32 phase;
  u32 v5;
  dds3ModelHandle_t *v6;
  sdfModelOt_t *v8;
  Work_t *v9;
  dds3ModelHandle_t *modelHandle;
  dds3ModelHandle_t *v13;
  sdfModelOt_t *v16;
  Work_t *v17;
  sdfModelOt_t *v20;
  dds3ModelHandle_t *v22;
  sdfModelOt_t *v25;

  phase = Work->phase;
  if (phase == 9)
  {
    if (Work->pAgari->playerIndex == 2)
      goto LABEL_29;
    if (!Work->PlayWithNarumi)
    {
LABEL_29:
      v17 = Work;
      modelHandle = v17->players[v17->pAgari->playerIndex]->modelHandle;
      goto LABEL_32;
    }
    v13 = Work->players[2]->modelHandle;
    v16 = ModelOt[0];
    Link(v13, v16);
    goto LABEL_29;
  }
  if (phase == 1)
    goto LABEL_11;
  if (v5)
  {
    if (!Work->PlayWithNarumi)
      return;
  }
  else
  {
    if (!Work->PlayWithNarumi)
      return;
  }
  modelHandle = Work->players[2]->modelHandle;
LABEL_32:
  v20 = ModelOt[0];
  Link(modelHandle, v20);
  return;
LABEL_11:
  if (v5)
  {
    if (Work->cameraCount < 60)
      goto LABEL_13;
LABEL_43:
    v22 = Work->players[1]->modelHandle;
    v25 = ModelOt[0];
    Link(v22, v25);
    goto LABEL_14;
  }
  if (Work->cameraCount >= 60)
    goto LABEL_43;
LABEL_13:
LABEL_14:
  v6 = Work->players[2]->modelHandle;
  v8 = ModelOt[0];
  Link(v6, v8);
  v9 = Work;
  if (v9->cameraCount >= 120)
  {
    v9 = Work;
    modelHandle = v9->players[3]->modelHandle;
    goto LABEL_32;
  }
}

// 0x1d26580
static void DrawYakuTex(void) {
  ;
}

// 0x1d26590
static void DrawRuleTex(void) {
  ;
}

// 0x1d265a0
static void DrawInfoUnitEach(s32 playerIndex, s32 offX, s32 offY, s32 fAgari) {
  Agari_t *pAgari;
  Player_t *v11;
  s64 v16;
  s32 v17;

  pAgari = Work->pAgari;
  MenuWin_agari_sub_SetActive(mjnUImanager, 1, playerIndex, 0);
  v11 = Work->players[playerIndex];
  if (fAgari)
  {
    v16 = playerIndex;
    v17 = pAgari->tensu[v16];
    MenuWin_agari_SetText(mjnUImanager, 1, playerIndex, v11->name, v11->tensu - v17, v17, v11->tensu, 0);
    return;
  }
  MenuWin_agari_SetText(mjnUImanager, 0, playerIndex, v11->name, 0, 0, v11->tensu, 0);
}

// 0x1d17a50
static void DrawInfoUnit(void) {
  s32 v1;
  s32 v2;
  s32 v5;
  s32 v6;
  s32 v8;
  s32 v9;
  s32 v11;
  s32 v12;

  DrawInfoUnitEach(0, v1, v2, Work->fDrawAgari);
  DrawInfoUnitEach(1, v5, v6, Work->fDrawAgari);
  DrawInfoUnitEach(2, v8, v9, Work->fDrawAgari);
  DrawInfoUnitEach(3, v11, v12, Work->fDrawAgari);
}

// 0x1d26830
static void InitEx(s32 devil0, s32 devil1, s32 devil2) {
  sdf3DFogParam_t *v6;
  void *Asset;
  s64 naturalAligment;
  void *v13;
  void *v14;
  void *p_HilightCol;
  fileLoadAsset_Request *Asset__AllSceneAsync;
  s64 v24;
  Work_t *Work_local;
  s32 *players;
  Player_t *v27;
  s32 *v28;
  s64 v29;
  s64 i;
  s32 *naki;
  Naki_t *v32;
  s64 v34;
  s64 j;
  s32 *agari;
  Agari_t *v37;
  s64 v38;
  s64 k;
  s32 *analyzeNodes;
  AnalyzeNode_t *v41;
  s64 v42;
  s64 m;
  s32 *randomArray;
  Random_t *v45;
  s64 v46;
  s64 v47;
  s32 *analysis;
  NormalAnalysis_t *v49;
  s64 v50;
  s64 n;
  Work_t *v52;
  s32 *pVisualDataTable;
  Visual_t *v54;
  s32 v55;
  s64 v56;
  Work_t *v57;
  char *v58;
  Work_t *v60;
  s32 *remainingMax;
  dds3ModelHandle_t *oyaModelHandle;
  dds3ModelHandle_t *v63;
  dds3ModelHandle_t *v64;
  dds3ModelHandle_t *v65;
  dds3ModelHandle_t *v67;
  dds3ModelHandle_t *v68;
  dds3ModelHandle_t *v69;
  dds3ModelHandle_t *v71;
  dds3ModelHandle_t *v72;
  dds3ModelHandle_t *v73;
  dds3ModelHandle_t *v75;
  dds3ModelHandle_t *v76;
  dds3ModelHandle_t *tenbouModelHandle;
  dds3ModelHandle_t *v80;
  dds3ModelHandle_t *v81;
  dds3ModelHandle_t *v84;
  dds3ModelHandle_t *v85;
  dds3ModelHandle_t *v86;
  dds3ModelHandle_t *v89;
  dds3ModelHandle_t *v90;
  dds3ModelHandle_t *v91;
  dds3ModelHandle_t *v94;
  dds3ModelHandle_t *v95;
  dds3ModelHandle_t *v96;
  Work_t *v98;
  dds3ModelHandle_t *v100;
  void *v102;
  sdfBinary *v103;
  s64 ii;
  s64 v106;
  MJNVISUALCLASS *TblDate;
  s64 v110;
  MJNVISUALCLASS *v111;
  s64 v114;
  MJNVISUALCLASS *v115;
  s64 v118;
  MJNVISUALCLASS *v119;
  s32 v125;
  sdfPacDecodeResrcHandle_t *v128;
  pacFileHandle_t *pSummonData;
  sdfPacDecodeResrcHandle_t *Resrc;
  effHandle_t *hPartsList;
  void *v132;
  effHandle_t *EPL;
  effHandle_t *v135;
  s64 v136;
  effHandle_t *v137;
  effHandle_t *v138;
  effHandle_t *v139;
  s64 v140;
  effHandle_t *v141;
  effHandle_t *v142;
  _BOOL8 v143;
  s64 v146;
  s64 v147;
  s32 *reaceMatihai;
  reaceMati *v149;
  void *Instance;
  void *v153;
  Work_t *v155;
  dds3ProcessFunc_t v156;
  shutdownfuncDelegate v157;
  dds3ProcessFunc_t v159;
  shutdownfuncDelegate v160;
  sdf3DFogParam_t *fog;
  s32 devilID;
  s32 v163;

  v6 = Allocate(sdf3DFogParam_t);
  _ctor(v6, 0);
  Load(Dependent, "mahjon", "mahjon");
  fog = v6;
  LoadSyncAll(_Ctrl_k__BackingField, 0);
  Asset = LoadAsset(_Ctrl_k__BackingField, "mahjon", "mjnHaiHighlightPar", 0);
  v163 = devil1;
  devilID = devil0;
  if (Asset)
  {
    if (Asset->klass->_2.naturalAligment >= (u32)naturalAligment)
    {
      if (Asset->klass->_2.typeHierarchy[naturalAligment - 1] == Project_mjnHaiHighlightPar)
        v13 = Asset;
      else
        v13 = 0;
    }
    else
    {
      v13 = 0;
    }
    HilightCol = (void *)v13;
    p_HilightCol = &HilightCol;
    if (Asset->klass->_2.naturalAligment >= (u32)naturalAligment)
    {
      if (Asset->klass->_2.typeHierarchy[naturalAligment - 1] == Project_mjnHaiHighlightPar)
        v14 = Asset;
      else
        v14 = 0;
    }
    else
    {
      v14 = 0;
    }
    goto LABEL_27;
  }
  v14 = 0;
  HilightCol = 0;
  p_HilightCol = &HilightCol;
LABEL_27:
  Asset__AllSceneAsync = AllSceneAsync(mjn_scene_key, 0);
  sceneLoadReq = Asset__AllSceneAsync;
  M_InitScene();
  mjnModelLoadBuffStart();
  v24 = 0;
  Work_local = Work;
  Work_local->fWaitPhase = 1;
  *(u64 *)&Work_local->fKokushiCheck = 0;
  Work_local->tipsPhase = 0;
  while (1)
  {
    players = Work->players;
    if (v24 >= players[6])
      break;
    v27 = Allocate(Player_t);
    _ctor(v27, 0);
    if (v27)
    {
      if (!QueryInterface(v27, *(void **)(*(u64 *)players + 64)))
        goto LABEL_47;
    }
    v28 = &players[2 * v24];
    *((u64 *)v28 + 4) = v27;
    v29 = 0;
    for (i = 8; ; i += 2)
    {
      naki = Work->players[v24]->naki;
      if (v29 >= naki[6])
        break;
      v32 = Allocate(Naki_t);
      _ctor(v32, 0);
      if (v32)
      {
        if (!QueryInterface(v32, *(void **)(*(u64 *)naki + 64)))
          goto LABEL_47;
      }
      *(u64 *)&naki[i] = v32;
      ++v29;
    }
    ++v24;
  }
  v34 = 0;
  for (j = 8; ; j += 2)
  {
    agari = Work->agari;
    if (v34 >= agari[6])
      break;
    v37 = Allocate(Agari_t);
    _ctor(v37, 0);
    if (v37)
    {
      if (!QueryInterface(v37, *(void **)(*(u64 *)agari + 64)))
        goto LABEL_47;
    }
    *(u64 *)&agari[j] = v37;
    ++v34;
  }
  v38 = 0;
  for (k = 8; ; k += 2)
  {
    analyzeNodes = Work->analyzeNodes;
    if (v38 >= analyzeNodes[6])
      break;
    v41 = Allocate(AnalyzeNode_t);
    _ctor(v41, 0);
    if (v41)
    {
      if (!QueryInterface(v41, *(void **)(*(u64 *)analyzeNodes + 64)))
        goto LABEL_47;
    }
    *(u64 *)&analyzeNodes[k] = v41;
    ++v38;
  }
  v42 = 0;
  for (m = 8; ; m += 2)
  {
    randomArray = Work->randomArray;
    if (v42 >= randomArray[6])
      break;
    randomArray = Work->randomArray;
    v45 = Allocate(Random_t);
    _ctor(v45, 0, 0, 0);
    if (v45 && !QueryInterface(v45, *(void **)(*(u64 *)randomArray + 64)))
      goto LABEL_47;
    *(u64 *)&randomArray[m] = v45;
    ++v42;
  }
  v46 = 0;
  v47 = 8;
  while (2)
  {
    analysis = Work->analysis;
    if (v46 < analysis[6])
    {
      v49 = Allocate(NormalAnalysis_t);
      _ctor(v49, 0);
      if (!v49)
        goto LABEL_81;
      goto LABEL_9001;
      if (!v49)
      {
LABEL_81:
        *(u64 *)&analysis[v47] = v49;
        ++v46;
        v47 += 2;
        continue;
      }
LABEL_9001:
      if (!QueryInterface(v49, *(void **)(*(u64 *)analysis + 64)))
        goto LABEL_47;
      goto LABEL_81;
    }
    break;
  }
  v50 = 0;
  for (n = 8; ; n += 2)
  {
    v52 = Work;
    pVisualDataTable = v52->pVisualDataTable;
    if (v50 >= pVisualDataTable[6])
      break;
    pVisualDataTable = Work->pVisualDataTable;
    v54 = Allocate(Visual_t);
    _ctor(v54, 150.0, 140.0, 160.0, 1.0, 0);
    if (v54 && !QueryInterface(v54, *(void **)(*(u64 *)pVisualDataTable + 64)))
      goto LABEL_47;
    *(u64 *)&pVisualDataTable[n] = v54;
    ++v50;
  }
  v55 = devil2 == -1;
  Work->PlayWithNarumi = v55;
  v56 = 0;
  v57 = Work;
  v57->cnt = 0;
  v57->seed = 0;
  while (1)
  {
    v60 = Work;
    remainingMax = v60->remainingMax;
    if (v56 >= SLODWORD(remainingMax->max_length))
      break;
    remainingMax = Work->remainingMax;
    v58 = (char *)remainingMax + 4 * v56++;
    *((u32 *)v58 + 8) = 0;
  }
  v60 = Work;
  oyaModelHandle = v60->oyaModelHandle;
  v60->attentionFlag = -1;
  v63 = ModelLoad(8, 512);
  v64 = v63;
  oyaModelHandle[0] = v64;
  v65 = Work->oyaModelHandle;
  v67 = ModelLoad(8, 514);
  v68 = v67;
  v65[1] = v68;
  v69 = Work->oyaModelHandle;
  v71 = ModelLoad(8, 516);
  v72 = v71;
  v69[2] = v72;
  v73 = Work->oyaModelHandle;
  v75 = ModelLoad(8, 515);
  v76 = v75;
  v73[3] = v76;
  tenbouModelHandle = Work->tenbouModelHandle;
  v80 = ModelLoad(8, 513);
  v81 = v80;
  tenbouModelHandle[0] = v81;
  v84 = Work->tenbouModelHandle;
  v85 = ModelLoad(8, 513);
  v86 = v85;
  v84[1] = v86;
  v89 = Work->tenbouModelHandle;
  v90 = ModelLoad(8, 513);
  v91 = v90;
  v89[2] = v91;
  v94 = Work->tenbouModelHandle;
  v95 = ModelLoad(8, 513);
  v96 = v95;
  v94[3] = v96;
  InitTenbouModel();
  v98 = Work;
  v100 = ModelLoad(7, 79);
  v98->tableModelHandle = v100;
  v102 = LoadAsset(_Ctrl_k__BackingField, "mahjon", "MJN_VISUAL.TBL", 0);
  v103 = Allocate(sdfBinary);
  _ctor(v103, v102, 0);
  for (ii = 4; ; ++ii)
  {
    if (ii - 4 >= SLODWORD(Work->pVisualDataTable->max_length))
      break;
    ReadFloat(v103, 0);
    ReadFloat(v103, 0);
    ReadFloat(v103, 0);
    ReadFloat(v103, 0);
    v106 = *((u64 *)&Work->pVisualDataTable->obj.klass + ii);
    TblDate = GetTblDate(VisualDataTable, (s32)ii - 4, 0);
    *(f32 *)(v106 + 16) = TblDate->posDist;
    v110 = *((u64 *)&Work->pVisualDataTable->obj.klass + ii);
    v111 = GetTblDate(VisualDataTable, (s32)ii - 4, 0);
    *(f32 *)(v110 + 20) = v111->cameraTargetHeight;
    v114 = *((u64 *)&Work->pVisualDataTable->obj.klass + ii);
    v115 = GetTblDate(VisualDataTable, (s32)ii - 4, 0);
    *(f32 *)(v114 + 24) = v115->cameraEyeDist;
    v118 = *((u64 *)&Work->pVisualDataTable->obj.klass + ii);
    v119 = GetTblDate(VisualDataTable, (s32)ii - 4, 0);
    *(f32 *)(v118 + 28) = v119->scale;
  }
  LoadTsumikomiData();
  InitDevil(0, 209);
  InitDevil(1, devilID);
  if (Work->PlayWithNarumi)
    v125 = 208;
  else
    v125 = devil2;
  InitDevil(2, v125);
  InitDevil(3, v163);
  v128 = Allocate(sdfPacDecodeResrcHandle_t);
  _ctor(v128, 0);
  pSummonData = Work->pSummonData;
  Resrc = pacGetResrc(pSummonData);
  hPartsList = Work->hPartsList;
  v132 = *(void *)((Resrc->unit->klass->vtable._5_GetExtUnits.methodPtr)(Resrc->unit, Resrc->unit->klass->vtable._5_GetExtUnits.method) + 32);
  EPL = dds3EffectLoadEPL(v132);
  if (!EPL)
    goto LABEL_169;
LABEL_168:
LABEL_47:
  EPL = dds3EffectLoadEPL(v132);
  if (EPL)
    goto LABEL_168;
LABEL_169:
  hPartsList[0] = EPL;
  v135 = Work->hPartsList;
  v136 = (Resrc->unit->klass->vtable._5_GetExtUnits.methodPtr)(Resrc->unit, Resrc->unit->klass->vtable._5_GetExtUnits.method);
  v137 = dds3EffectLoadEPL(*(void *)(v136 + 32));
  v138 = v137;
  v135[1] = v138;
  v139 = Work->hPartsList;
  v140 = (Resrc->unit->klass->vtable._5_GetExtUnits.methodPtr)(Resrc->unit, Resrc->unit->klass->vtable._5_GetExtUnits.method);
  v141 = dds3EffectLoadEPL(*(void *)(v140 + 32));
  v142 = v141;
  v139[2] = v142;
  v143 = pacHandleFree(Work->pSummonData);
  InitCameraSummon();
  InitLight();
  v146 = 0;
  v147 = 8;
  butoonGuideAgariFlag = 0;
  while (1)
  {
    reaceMatihai = Work->reaceMatihai;
    if (v146 >= reaceMatihai[6])
      break;
    v149 = Allocate(reaceMati);
    _ctor(v149, 0);
    if (v149)
    {
      if (!QueryInterface(v149, *(void **)(*(u64 *)reaceMatihai + 64)))
        goto LABEL_47;
    }
    *(u64 *)&reaceMatihai[v147] = v149;
    ++v146;
    v147 += 2;
  }
  fog->color = 6312000;
  *(_OWORD *)&fog->fogMax = xmmword_3D02D70;
  dds3SetFog(fog);
  InitInterface();
  InitHanchan();
  Instance = get_Instance(0);
  ItfButtonGuideActive(Instance, 1, 0);
  v153 = get_Instance(0);
  ItfButtonGuideSet(v153, 0, 0);
  v155 = Work;
  v155->phase = 1;
  v155->summonPhase = 0;
  Unload(Dependent, "mahjon", 0);
  v156 = Allocate(dds3ProcessFunc_t);
  _ctor(v156, 0, Method_Project_mjn_MainLoop__, 0);
  v157 = Allocate(shutdownfuncDelegate);
  _ctor(v157, 0, Method_Project_mjn_Destroy__, 0);
  dds3StartProcess("mahjon main process", 1017, 0, 0, v156, v157, 0);
  Work->fDrawAll = 1;
  v159 = Allocate(dds3ProcessFunc_t);
  _ctor(v159, 0, Method_Project_mjn_DrawProcess__, 0);
  v160 = Allocate(shutdownfuncDelegate);
  _ctor(v160, 0, Method_Project_mjn_DrawDestroy__, 0);
  dds3StartProcess("mahjon draw process", 11020, 0, 0, v159, v160, 0);
}

// 0x1d27bf0
static void M_InitScene(void) {
  u32 v1;
  dds3Basic_t *scene;

  scene = dds3AddScene();
  dds3SetControlScene(scene);
  dds3SetActiveScene(scene);
  v1 = dds3SerializeID();
  dds3AreaBasicAdd(v1, "mahjon");
}

// 0x1d29790
static dds3ProcessFunc_t MainLoop(dds3ProcessID_t *id) {
  if (!sceneLoadReq->isDone)
    return 0;
  {
    mjnSetChair();
  }
  ++Work->cnt;
  PadDealer();
  Dispatch();
  if (Work->fDrawAll != 1)
    return 0;
  *(u32 *)(*((u64 *)*((MethodInfo *)mjn + 2).virtualMethodPointer + 24) + 740) = 0;
  DrawTehai3DCalc();
  DrawSutehai3DCalc();
  DrawNakihai3DCalc();
  DrawWanpai3DCalc();
  return 0;
}

// 0x1d29910
void mjnSetChair(void) {
  s32 PlayWithNarumi;
  void *v4;
  bool activeSelf;
  void *v6;
  bool v7;

  if (MJN_CHAIR)
    return;
  PlayWithNarumi = Work->PlayWithNarumi;
  v4 = Find("isu_base");
  activeSelf = get_activeSelf(v4, 0);
  if (PlayWithNarumi)
  {
    if (!activeSelf)
    {
      v6 = v4;
      v7 = 1;
LABEL_14:
      SetActive(v6, v7, 0);
    }
  }
  else if (activeSelf)
  {
    v6 = v4;
    v7 = 0;
    goto LABEL_14;
  }
  MJN_CHAIR = 1;
}

// 0x1d2ad50
static void Destroy(dds3ProcessID_t *id) {
  s32 v2;
  s64 v3;
  u64 *v5;
  Il2CppClass **implementedInterfaces;
  s64 v8;
  u32 DevilSESub;
  s64 v13;
  s64 v14;
  dds3ModelHandle_t *v15;
  Il2CppClass **v16;
  dds3ModelHandle_t *haiModelYama;
  il2cpp_array_size_t v18;
  dds3ModelHandle_t *v20;
  dds3ModelHandle_t *v22;
  Il2CppClass **v24;
  dds3ModelHandle_t *tableModelHandle;
  Work_t *Work_local;
  dds3ModelHandle_t *v28;
  dds3ModelHandle_t *tenbouModelHandle;
  dds3ModelHandle_t *v31;
  dds3ModelHandle_t *v32;
  dds3ModelHandle_t *v34;
  dds3ModelHandle_t *v35;
  dds3ModelHandle_t *v37;
  dds3ModelHandle_t *v38;
  dds3ModelHandle_t *v40;
  dds3ModelHandle_t *oyaModelHandle;
  dds3ModelHandle_t *v43;
  dds3ModelHandle_t *v44;
  dds3ModelHandle_t *v46;
  dds3ModelHandle_t *v47;
  dds3ModelHandle_t *v49;
  dds3ModelHandle_t *v50;
  DvlFaceSet *dvlFaceSet;
  DvlFaceSet *p_dvlFaceSet;
  dds3Basic_t *scene;

  v2 = 1;
  v3 = 40;
  do
  {
    implementedInterfaces = (*(Il2CppClass **)((char *)&Work->players->obj.klass + v3))->_1.implementedInterfaces;
    if (implementedInterfaces)
    {
      mdlSetLight(implementedInterfaces, 0);
      Free((*(Il2CppClass **)((char *)&Work->players->obj.klass + v3))->_1.implementedInterfaces);
      v8 = *(s64 *)((char *)&Work->players->obj.klass + v3);
      *(u64 *)(v8 + 168) = 0;
      if (v2)
      {
        if (v2 != 2)
        {
          goto LABEL_21;
        }
        if (Work->PlayWithNarumi)
          goto LABEL_16;
LABEL_21:
        p2sdUnLoadSMGFile(DevilSESub, 1);
LABEL_4:
        v5 = ((char *)&Work->players->obj.klass + v3);
        *v5 = 0;
        goto LABEL_5;
      }
LABEL_16:
      goto LABEL_4;
    }
LABEL_5:
    v3 += 8;
    ++v2;
  }
  while (v3 != 64);
  v13 = 0;
  v14 = 0;
  goto LABEL_37;
  while (2)
  {
    while (2)
    {
LABEL_37:
      haiModelYama = Work->haiModelYama;
      v18 = v14 + haiModelYama->bounds[1].length * v13;
      if (haiModelYama[v18])
      {
        v20 = haiModelYama[v18];
        Free(v20);
        v15 = Work->haiModelYama;
        v16 = &v15->obj.klass + v14 + v13 * v15->bounds[1].length;
        v16[4] = 0;
      }
      if (++v14 != 34)
      {
        goto LABEL_37;
      }
      break;
    }
    v22 = Work->haiModelHandle[v13];
    if (!v22)
    {
      if (++v13 == 160)
        goto LABEL_55;
LABEL_51:
      v14 = 0;
      goto LABEL_37;
    }
    break;
  }
  Free(v22);
  v24 = &Work->haiModelHandle->obj.klass + v13;
  v24[4] = 0;
  if (++v13 != 160)
    goto LABEL_51;
LABEL_55:
  mjnModelLoadBuffEnd();
  tableModelHandle = Work->tableModelHandle;
  Free(tableModelHandle);
  Work_local = Work;
  Work_local->tableModelHandle = 0;
  v28 = Work->tenbouModelHandle[0];
  Free(v28);
  tenbouModelHandle = Work->tenbouModelHandle;
  tenbouModelHandle[0] = 0;
  v31 = Work->tenbouModelHandle[1];
  Free(v31);
  v32 = Work->tenbouModelHandle;
  v32[1] = 0;
  v34 = Work->tenbouModelHandle[2];
  Free(v34);
  v35 = Work->tenbouModelHandle;
  v35[2] = 0;
  v37 = Work->tenbouModelHandle[3];
  Free(v37);
  v38 = Work->tenbouModelHandle;
  v38[3] = 0;
  v40 = Work->oyaModelHandle[0];
  Free(v40);
  oyaModelHandle = Work->oyaModelHandle;
  oyaModelHandle[0] = 0;
  v43 = Work->oyaModelHandle[1];
  Free(v43);
  v44 = Work->oyaModelHandle;
  v44[1] = 0;
  v46 = Work->oyaModelHandle[2];
  Free(v46);
  v47 = Work->oyaModelHandle;
  v47[2] = 0;
  v49 = Work->oyaModelHandle[3];
  Free(v49);
  v50 = Work->oyaModelHandle;
  v50[3] = 0;
  UIDestroy(mjnUImanager, 0);
  sceneLoadReq = 0;
  DestroyInterface();
  goto LABEL_97;
LABEL_98:
  goto LABEL_99;
LABEL_97:
  scene = dds3GetControlScene();
  if (!scene)
    goto LABEL_98;
  dds3DeleteScene(scene);
LABEL_99:
  Unload(Dependent, "mahjon", 0);
  if (!op_Inequality(VisualDataTable, 0, 0))
    goto LABEL_101;
  VisualDataTable = 0;
LABEL_102:
  goto LABEL_103;
LABEL_104:
  goto LABEL_105;
LABEL_106:
  if (!op_Inequality(TsumikomiProbTable, 0, 0))
    goto LABEL_107;
  TsumikomiProbTable = 0;
LABEL_108:
  goto LABEL_109;
LABEL_110:
  goto LABEL_111;
LABEL_112:
  goto LABEL_113;
LABEL_101:
  goto LABEL_102;
LABEL_103:
  if (!op_Inequality(TsumikomiDataTable, 0, 0))
    goto LABEL_104;
  TsumikomiDataTable = 0;
LABEL_105:
  goto LABEL_106;
LABEL_107:
  goto LABEL_108;
LABEL_109:
  if (!op_Inequality(DoraProbDataTable, 0, 0))
    goto LABEL_110;
  DoraProbDataTable = 0;
LABEL_111:
  dvlFaceSet = Work->dvlFaceSet;
  if (!dvlFaceSet)
    goto LABEL_112;
  dvlFaceSet = Work->dvlFaceSet;
  (dvlFaceSet->klass->vtable._4_Clear.methodPtr)(dvlFaceSet, dvlFaceSet, dvlFaceSet->klass->vtable._4_Clear.method);
  p_dvlFaceSet = &Work->dvlFaceSet;
  p_dvlFaceSet = 0;
  Work->sprFlag &= 0xFFFFFFFC;
LABEL_113:
  p2sdUnLoadSMGFile(0x400000, 1);
  Work = 0;
  MJN_CHAIR = 0;
  sdfMemRelease();
  if (dds3AdminiGetActiveSequence() == 17)
    return;
  if (dds3AdminiGetActiveSequence() != 41)
    dds3AdminiCallSequence(0, 0, 0);
}

// 0x1d2be20
void mjnDeleteScene(void) {
  dds3Basic_t *scene;

  scene = dds3GetControlScene();
  if (!scene)
    return;
  dds3DeleteScene(scene);
}

// 0x1d27cf0
void mjnModelLoadBuffStart(void) {
  void *v1;
  s32 size;
  s32 v6;

  v1 = Allocate(System_Collections_Generic_List_string_);
  __ctor_48217280(v1, 34);
  ModelBuffer = v1;
  size = ModelBuffer->_size;
  v6 = ModelBuffer->_version + 1;
  ModelBuffer->_size = 0;
  ModelBuffer->_version = v6;
  if (size >= 1)
    Clear(ModelBuffer->_items, 0, size, 0);
}

// 0x1d25dc0
void mjnModelLoadBuff(s32 num) {
  Il2CppObject *ModelName;
  void *ModelBuffer_local;
  u64 *v7;
  s64 size;
  void *items;
  Il2CppClass **v10;

  ModelName = mdlGetModelName(8u, num);
  if (_Contains(ModelBuffer, ModelName))
  {
    return;
  }
  Load(Dependent, ModelName, ModelName);
  ModelBuffer_local = ModelBuffer;
  v7 = Method_System_Collections_Generic_List_string__Add__;
  size = ModelBuffer_local->_size;
  ++ModelBuffer_local->_version;
  items = ModelBuffer_local->_items;
  if ((u32)size >= LODWORD(items->max_length))
  {
    _AddWithResize(ModelBuffer_local, ModelName, *(const MethodInfo_2DFC660 **)(*(u64 *)(v7[4] + 192) + 112));
  }
  else
  {
    v10 = &items->obj.klass + size;
    ModelBuffer_local->_size = size + 1;
    v10[4] = ModelName;
  }
}

// 0x1d2ba00
void mjnModelLoadBuffEnd(void) {
  Il2CppObject *current;
  void *v7;
  s32 size;
  s32 v9;
  System_Collections_Generic_List_Enumerator_T__o v10;

  memset(&v10, 0, sizeof(v10));
  if (!ModelBuffer)
    return;
  _GetEnumerator(&v10, ModelBuffer);
  while (_MoveNext(&v10))
  {
    current = v10._current;
    Unload(Dependent, current, 0);
  }
  _Dispose(&v10);
  v7 = ModelBuffer;
  size = v7->_size;
  v9 = v7->_version + 1;
  v7->_size = 0;
  v7->_version = v9;
  if (size >= 1)
  {
    Clear(v7->_items, 0, size, 0);
  }
  ModelBuffer = 0;
}

// 0x1d2bed0
static dds3ProcessFunc_t DrawProcess(dds3ProcessID_t *id) {
  if (Work->fDrawAll != 1)
    return 0;
  Draw3D();
  return 0;
}

// 0x1d2bf90
static void DrawDestroy(dds3ProcessID_t *id) {
  ;
}

// 0x1d2bfa0
static void DrawMemFree(void) {
  FreeEffect();
}

// 0x1d2c320
static void ManageModelPhase(void) {
  s64 playerIndex;
  Player_t *v4;
  Work_t *v6;
  dds3ModelHandle_t *modelHandle;
  s32 devilID;
  u32 DevilSESub;
  Work_t *v14;
  s32 v16;
  struct sdfVector4_t cameraTargetPos;
  Work_t *v18;
  s32 v19;
  Player_t *v20;
  f32 cameraTargetDistance;
  f32 cameraEyeDistance;
  s32 cameraCount;
  float32x2_t v24;
  f32 z;
  float32x2_t v26;
  f32 v27;
  float32x2_t v28;
  f32 v29;
  float32x2_t v30;
  f32 v31;
  f32 v32;
  u64 v33;
  u64 v34;
  f32 v35;
  s32 v36;
  s32 v37;
  bool v38;
  dds3ModelHandle_t *v39;
  Player_t *v40;
  dds3ModelHandle_t *v41;
  Work_t *v45;
  dds3ModelHandle_t *v46;
  s32 v47;
  dds3ModelHandle_t *v50;
  dds3ModelHandle_t *v51;
  Work_t *v52;
  dds3ModelHandle_t *v53;
  dds3ModelHandle_t *v54;
  f32 v55;
  f32 v56;
  f32 v57;
  f32 v58;
  Work_t *v59;
  s32 v60;

  playerIndex = Work->pAgari->playerIndex;
  if ((u32)playerIndex)
    goto LABEL_4;
  Work->phase = 0;
LABEL_17:
  InitCamera();
  NextKyoku();
  return;
LABEL_4:
  v4 = Work->players[playerIndex];
  if (CHECK_REP(43266, 1))
  {
    v6 = Work;
    if (v6->modelPhase)
    {
      v6 = Work;
      modelHandle = v6->players[1]->modelHandle;
      mdlSmoothLoopMotion(modelHandle, 0, 0, 8.0, 8.0, 0.0);
      mdlSmoothLoopMotion(Work->players[2]->modelHandle, 0, 0, 8.0, 8.0, 0.0);
      mdlSmoothLoopMotion(Work->players[3]->modelHandle, 0, 0, 8.0, 8.0, 0.0);
      Work->phase = 0;
      InitCamera();
      NextKyoku();
      butoonGuideAgariFlag = 0;
      return;
    }
  }
  devilID = v4->devilID;
  DevilSESub = sBtlGetDevilSESub(devilID, 13);
  v14 = Work;
  switch (v14->modelPhase)
  {
    case 0:
      v14 = Work;
      v14->modelPhase = 1;
      if ((u32)playerIndex == 2 && v14->PlayWithNarumi != 0)
      {
LABEL_133:
        v36 = 1;
        goto LABEL_134;
LABEL_132:
        v14 = Work;
        goto LABEL_133;
      }
      v16 = p2sdLoadCheckMidi(DevilSESub);
      if (v16 == 1)
      {
        goto LABEL_132;
      }
      if (!v16)
      {
        p2sdLoadSMGFile(DevilSESub);
      }
      return;
    case 1:
      v14 = Work;
      cameraTargetPos = v14->cameraTargetPos;
      v14->cameraCount = 0;
      v14->cameraTargetPosStart = cameraTargetPos;
      Work->cameraEyePosStart = Work->cameraEyePos;
      v18 = Work;
      v19 = v18->pAgari->playerIndex;
      v20 = v18->players[playerIndex];
      v18->cameraTargetPosEnd.y = v20->cameraTargetHeight;
      v18->cameraEyePosEnd.y = v20->cameraEyeHeight;
      switch (v19)
      {
        case 0:
          v18 = Work;
          v20 = v18->players[playerIndex];
          v18->cameraTargetPosEnd.x = 0.0;
          cameraTargetDistance = v20->cameraTargetDistance;
          v18->cameraEyePosEnd.x = 10.0;
          v18->cameraTargetPosEnd.z = -cameraTargetDistance;
          cameraEyeDistance = v20->cameraEyeDistance;
          goto LABEL_119;
        case 1:
          v18 = Work;
          v20 = v18->players[playerIndex];
          v55 = v20->cameraTargetDistance;
          v18->cameraTargetPosEnd.z = 0.0;
          v18->cameraTargetPosEnd.x = v55;
          v56 = -v20->cameraEyeDistance;
          goto LABEL_118;
        case 2:
          v18 = Work;
          v20 = v18->players[playerIndex];
          v18->cameraTargetPosEnd.x = 0.0;
          v57 = v20->cameraTargetDistance;
          v18->cameraEyePosEnd.x = 0.0;
          v18->cameraTargetPosEnd.z = v57;
          cameraEyeDistance = -v20->cameraEyeDistance;
          goto LABEL_119;
        case 3:
          v18 = Work;
          v20 = v18->players[playerIndex];
          v58 = v20->cameraTargetDistance;
          v18->cameraTargetPosEnd.z = 0.0;
          v18->cameraTargetPosEnd.x = -v58;
          v56 = v20->cameraEyeDistance;
LABEL_118:
          v18->cameraEyePosEnd.x = v56;
          cameraEyeDistance = 0.0;
LABEL_119:
          v18->cameraEyePosEnd.z = cameraEyeDistance;
          break;
        default:
          break;
      }
      v59 = Work;
      v59->modelPhase = 2;
      if ((u32)playerIndex == 2)
        goto LABEL_126;
      v59 = Work;
      if (!v59->PlayWithNarumi)
      {
LABEL_126:
        v60 = (devilID << 16) + 0x2000000;
        p2sdPlaySE_Vol(v60, 127);
      }
      return;
    case 2:
      v14 = Work;
      cameraCount = v14->cameraCount;
      v24.n64_u64[0] = *(u64 *)&v14->cameraEyePosEnd.x;
      z = v14->cameraEyePosEnd.z;
      v26.n64_u64[0] = *(u64 *)&v14->cameraTargetPosEnd.x;
      v27 = v14->cameraTargetPosEnd.z;
      v28.n64_u64[0] = *(u64 *)&v14->cameraEyePosStart.x;
      v29 = v14->cameraEyePosStart.z;
      v30.n64_u64[0] = *(u64 *)&v14->cameraTargetPosStart.x;
      v31 = (f32)cameraCount++;
      v14->cameraCount = cameraCount;
      v32 = v31 / 100.0;
      v33 = vadd_f32(vmul_n_f32(v28, 1.0 - v32), vmul_n_f32(v24, v32)).n64_u64[0];
      v24.n64_f32[0] = (f32)((f32)(1.0 - v32) * v29) + (f32)(v32 * z);
      v34 = vadd_f32(vmul_n_f32(v30, 1.0 - v32), vmul_n_f32(v26, v32)).n64_u64[0];
      v35 = (f32)((f32)(1.0 - v32) * v14->cameraTargetPosStart.z) + (f32)(v32 * v27);
      *(u64 *)&v14->cameraEyePos.x = v33;
      LODWORD(v14->cameraEyePos.z) = v24.n64_u32[0];
      *(u64 *)&v14->cameraTargetPos.x = v34;
      v14->cameraTargetPos.z = v35;
      if (cameraCount == 100)
      {
        v14 = Work;
        v36 = 3;
        v14->waitCount = 0;
LABEL_134:
        v14->modelPhase = v36;
      }
      return;
    case 3:
      v14 = Work;
      v37 = v14->waitCount + 1;
      v38 = v14->waitCount - 30 < 0;
      v14->waitCount = v37;
      if (v38 != __OFSUB__(v37, 31))
        return;
      v14 = Work;
      v14->modelPhase = 4;
      if ((u32)playerIndex == 2)
      {
        v14 = Work;
        if (v14->PlayWithNarumi)
        {
          v14 = Work;
          v39 = v14->players[playerIndex]->modelHandle;
          mdlSmoothSingleMotion(v39, 0, 2, 8.0, 8.0, 0.0);
          v40 = Work->players[playerIndex];
LABEL_102:
          mdlSetMotionSpeedEx(v40->modelHandle, 0, 0.5);
          return;
        }
      }
      v51 = Work->players[playerIndex]->modelHandle;
      mdlSmoothSingleMotion(v51, 0, 7, 8.0, 8.0, 0.0);
      mdlSetMotionSpeedEx(Work->players[playerIndex]->modelHandle, 0, 0.5);
      v52 = Work;
      if (v52->PlayWithNarumi)
      {
        v52 = Work;
        v53 = v52->players[2]->modelHandle;
        mdlSmoothSingleMotion(v53, 0, 3, 8.0, 8.0, 0.0);
        v40 = Work->players[2];
        goto LABEL_102;
      }
      break;
    case 4:
      v14 = Work;
      v41 = v14->players[playerIndex]->modelHandle;
      if (mdlChkMotionEndEx(v41, 0))
      {
        v45 = Work;
        v45->modelPhase = 5;
        v46 = v45->players[playerIndex]->modelHandle;
        mdlSmoothLoopMotion(v46, 0, 0, 8.0, 8.0, 0.0);
        Work->waitCount = 0;
      }
      else
      {
        if ((u32)playerIndex != 2)
          goto LABEL_103;
        if (Work->PlayWithNarumi)
        {
          v50 = v4->modelHandle;
          if (mdlGetMotionFrameEx(v50, 0) == 30)
          {
            sndVoicePlayFile("PVA03_55_000", 0);
          }
        }
        else
        {
LABEL_103:
          v54 = v4->modelHandle;
          if (mdlGetMotionFrameEx(v54, 0) == 30)
          {
            sBtlPlaySE(DevilSESub);
          }
        }
      }
      return;
    case 5:
      v14 = Work;
      v47 = v14->waitCount + 1;
      v38 = v14->waitCount - 60 < 0;
      v14->waitCount = v47;
      if (v38 != __OFSUB__(v47, 61))
        return;
      v14 = Work;
      v14->phase = 0;
      butoonGuideAgariFlag = 0;
      goto LABEL_17;
    default:
      return;
  }
}

// 0x1d29a30
static void PadDealer(void) {
  bool v2;
  s32 phase;
  Player_t *v6;
  bool v7;
  Work_t *v8;
  Work_t *v11;
  s32 v12;
  s32 nakiCursor;
  Work_t *v16;
  s32 v17;
  Work_t *v21;
  s32 v22;
  s32 v23;
  s32 v24;
  u32 v25;
  Work_t *v27;
  s32 yakuListLength;
  s32 v29;
  s32 v30;
  s32 v32;
  Work_t *v33;
  s32 v34;
  u32 v35;
  Work_t *v36;
  s32 v37;
  s64 i;
  Work_t *v39;
  Work_t *v40;
  s32 v41;
  Work_t *v43;
  s32 fDrawAgari;
  u32 v45;
  s32 v46;
  s32 v47;
  s64 tehaiCursor;
  Work_t *v49;
  Player_t *players;
  u32 v52;
  Player_t *v53;

  if (TIPSOPEN)
    return;
  CHECK_TRIG(4098, 1);
  v2 = CHECK_TRIG(4096, 1);
  phase = Work->phase;
  if (phase == 11)
    return;
  v6 = Work->players[0];
  phase = Work->phase;
  if (phase != 1)
  {
    phase = Work->phase;
    if (phase != 10)
    {
      phase = Work->phase;
      if (phase != 9)
      {
        phase = Work->phase;
        if (phase != 8)
        {
          v7 = CHECK_TRIG(43275, 1);
          if (v7)
          {
            (loc_1D50160)(1, 0);
            Work->tipsPhase = 1;
          }
        }
      }
    }
  }
  v8 = Work;
  if (v8->phase == 3)
  {
    v8 = Work;
    if (!v8->turn)
    {
      v8 = Work;
      if (v8->playerPhase == 2)
        goto LABEL_42;
    }
  }
  if (Work->phase != 12)
    goto LABEL_39;
LABEL_42:
  mjnTehaiCursorMoveMain();
  mjnMatihaiTextDraw(Work->tehaiCursor);
  if (!CHECK_REP(4100, 1))
    goto LABEL_79;
  goto LABEL_45;
LABEL_39:
  if (!CHECK_REP(4100, 1))
    goto LABEL_79;
LABEL_45:
  v11 = Work;
  v12 = v11->phase;
  if (v12 != 8)
  {
    if (v12 != 5)
      goto LABEL_79;
    v11 = Work;
    nakiCursor = v11->nakiCursor;
    if (nakiCursor >= 1)
    {
      v11 = Work;
      nakiCursor = v11->nakiCursor;
      goto LABEL_193;
    }
    if (nakiCursor)
      goto LABEL_77;
    goto LABEL_9001;
    if (v11->nakiCursor)
    {
LABEL_77:
LABEL_78:
      p2sdPlaySE_Vol(4194307, 127);
      goto LABEL_79;
    }
LABEL_9001:
    v11 = Work;
    nakiCursor = v11->nakiMenuNum;
LABEL_193:
    v11->nakiCursor = nakiCursor - 1;
    goto LABEL_78;
  }
  v11 = Work;
  if (v11->fDrawAgari)
  {
    v11 = Work;
    if (v11->phase == 8)
    {
      if (sBtlExt_ChkMes() != 1)
      {
        v16 = Work;
        if (v16->fDrawAgari)
        {
          v16 = Work;
          if (v16->yakuListLength >= 10)
          {
            v16 = Work;
            v17 = v16->yakuTopNo - 1;
            v16->yakuTopNo = v17;
            if (v17 < 0)
            {
              v16 = Work;
              v16->yakuTopNo = 0;
            }
          }
        }
      }
    }
  }
LABEL_79:
  if (!CHECK_REP(4101, 1))
    goto LABEL_117;
  v21 = Work;
  v22 = v21->phase;
  if (v22 != 8)
  {
    if (v22 != 5)
      goto LABEL_117;
    v21 = Work;
    v23 = v21->nakiMenuNum - 1;
    v24 = v21->nakiCursor;
    if (v24 < v23)
    {
      if (!v25)
      {
        v21 = Work;
        v24 = v21->nakiCursor;
      }
      v21->nakiCursor = v24 + 1;
      goto LABEL_116;
    }
    if (v25)
    {
      if (v24 != v23)
        goto LABEL_114;
    }
    else
    {
      v21 = Work;
      if (v21->nakiCursor != v21->nakiMenuNum - 1)
      {
LABEL_114:
LABEL_116:
        p2sdPlaySE_Vol(4194307, 127);
        goto LABEL_117;
      }
    }
    v21 = Work;
    v21->nakiCursor = 0;
    goto LABEL_116;
  }
  v21 = Work;
  if (v21->fDrawAgari)
  {
    v21 = Work;
    if (v21->phase == 8)
    {
      if (sBtlExt_ChkMes() != 1)
      {
        v27 = Work;
        if (v27->fDrawAgari)
        {
          v27 = Work;
          yakuListLength = v27->yakuListLength;
          if (yakuListLength >= 10)
          {
            v27 = Work;
            yakuListLength = v27->yakuListLength;
            v29 = yakuListLength - 9;
            v30 = v27->yakuTopNo + 1;
            v27->yakuTopNo = v30;
            if (v30 > v29)
            {
              v27 = Work;
              v29 = v27->yakuListLength - 9;
              v27->yakuTopNo = v29;
            }
          }
        }
      }
    }
  }
LABEL_117:
  if (!v2)
    goto LABEL_265;
  if (Work->phase == 8)
  {
    v32 = sBtlExt_ChkMes();
    if (v32 != 1)
    {
      v43 = Work;
      if (v43->agariDrawFlag)
      {
        v43 = Work;
        fDrawAgari = v43->fDrawAgari;
        if (fDrawAgari == 1)
        {
          if (!v45)
          StartModelPhase();
        }
        else
        {
          if (!v45)
          NextKyoku();
        }
      }
      return;
    }
  }
  v33 = Work;
  v34 = v33->phase;
  if (v34 == 8)
    return;
  v33 = Work;
  v34 = v33->phase;
  if (v34 == 3)
  {
    v33 = Work;
    if (v33->playerPhase == 2)
    {
      v33 = Work;
      if (!v33->turn)
      {
        v33 = Work;
        if ((v33->players[0]->flag & 2) != 0)
        {
          if (!v35)
          {
            v33 = Work;
          }
          tehaiCursor = v33->tehaiCursor;
          if (!v33->reachShanten[tehaiCursor])
          {
            v33 = Work;
            LODWORD(tehaiCursor) = v33->tehaiCursor;
            v33->playerSutehai = tehaiCursor;
            v33->playerPhase = 4;
          }
          return;
        }
        if (!v35)
        {
          v33 = Work;
        }
        v33->playerSutehai = v33->tehaiCursor;
        v33->playerPhase = 4;
      }
    }
  }
  v36 = Work;
  v37 = v36->phase;
  if (v37 != 12)
  {
    v36 = Work;
    v37 = v36->phase;
    if (v37 != 5)
      goto LABEL_265;
    v36 = Work;
    v46 = v36->nakiMenu[v36->nakiCursor];
    if (v46 > 64)
    {
      if ((u32)v46 <= 0x10000080)
      {
        if (v46 == 4096)
        {
          TochuRyukyoku(4096);
        }
        else if (v46 == 268435584)
        {
          ApplyChi(0, 268435584);
        }
        goto LABEL_265;
      }
      if (v46 == 268435712)
      {
        v47 = 268435712;
        goto LABEL_228;
      }
      if (v46 == 268435968)
      {
        v47 = 268435968;
LABEL_228:
        ApplyChi(0, v47);
      }
LABEL_265:
      if (!butoonGuideAgariFlag)
      {
        mjnCheckButtonGuide();
      }
      return;
    }
    if ((u32)v46 > 0x40)
      goto LABEL_265;
    switch (v46)
    {
      case 0:
        if (v36->turn)
        {
          goto LABEL_217;
LABEL_262:
          Ignore();
          goto LABEL_265;
        }
        v36 = Work;
        v53 = v36->players[0];
        if (v53->reachIndex == -1)
        {
          if (!v52)
          {
            v36 = Work;
          }
          *(u64 *)&v36->phase = 0x200000003LL;
          v36->tehaiCursor = v6->tehaiNum - 1;
          matiChack();
        }
        else
        {
          if (!v52)
          {
            v36 = Work;
            v53 = v36->players[0];
          }
          v36->playerSutehai = v53->tehaiNum - 1;
          *(u64 *)&v36->phase = 0x400000003LL;
        }
LABEL_217:
        if (!Work->turn)
          goto LABEL_265;
        goto LABEL_262;
      case 1:
        ApplyTsumo(0);
        goto LABEL_265;
      case 2:
        ApplyReach(0);
        v49 = Work;
        v49->nextPhase = 3;
        players = v49->players;
        v49->turn = 0;
        v49->tehaiCursor = players[0]->tehaiNum - 1;
        mjnTehaiCursorSet();
        Work->playerPhase = 2;
        goto LABEL_265;
      case 3:
      case 5:
      case 6:
      case 7:
      case 9:
      case 10:
      case 11:
      case 12:
      case 13:
      case 14:
      case 15:
        goto LABEL_265;
      case 4:
        ApplyAnkanPlayer(0);
        goto LABEL_265;
      case 8:
        ApplyKakan(0);
        goto LABEL_265;
      case 16:
        v36 = Work;
        ApplyRon(0, v36->turn);
        goto LABEL_265;
      default:
        if (v46 == 32)
        {
          v36 = Work;
          ApplyPon(0, v36->turn);
        }
        else if (v46 == 64)
        {
          v36 = Work;
          ApplyMinkan(0, v36->turn);
        }
        goto LABEL_265;
    }
  }
  for (i = 0; ; ++i)
  {
    v40 = Work;
    if (i >= v40->kanNum)
      break;
    v40 = Work;
    if (v40->players[0]->tehai14[v40->tehaiCursor] == v40->kanHai[i])
    {
      v40 = Work;
      v41 = v40->nakiFlag[0];
      if (v41 == 4)
      {
        ApplyAnkanEx(0, Work->players[0]->tehai14[Work->tehaiCursor]);
        return;
      }
      v39 = Work;
      if (v39->nakiFlag[0] == 8)
      {
        v39 = Work;
        ApplyKakanEx(0, v39->players[0]->tehai14[v39->tehaiCursor]);
        return;
      }
    }
  }
}

// 0x1d2feb0
void mjnCheckButtonGuide(void) {
  s32 v4;
  bool v5;

  if (!CHECK_PRESS(4102, 1) && !CHECK_PRESS(4103, 1) && !CHECK_PRESS(4100, 1) && !CHECK_PRESS(4101, 1) && !CHECK_PRESS(4099, 1) && !CHECK_PRESS(4096, 1) && !CHECK_PRESS(4098, 1) && !CHECK_PRESS(4097, 1) && !CHECK_PRESS(4104, 1) && !CHECK_PRESS(4105, 1) && !CHECK_PRESS(4107, 1) && !CHECK_PRESS(4108, 1) && !CHECK_PRESS(4110, 1) && !CHECK_PRESS(4111, 1) && !CHECK_PRESS(4106, 1) && !CHECK_PRESS(4109, 1))
  {
LABEL_22:
    if (MJN_GUIDEHELP_FLAG)
      goto LABEL_23;
    goto LABEL_30;
  }
  ButtonGuideDispOut();
  MJN_BUTTONGUIDE_TIMER = 0;
  goto LABEL_22;
  if (MJN_GUIDEHELP_FLAG)
  {
LABEL_23:
    v4 = MJN_BUTTONGUIDE_TIMER + 1;
    v5 = MJN_BUTTONGUIDE_TIMER - 119 < 0;
    MJN_BUTTONGUIDE_TIMER = v4;
    if (v5 != __OFSUB__(v4, 120))
      return;
    MJN_BUTTONGUIDE_TIMER = 120;
    ButtonGuideDispOn();
    return;
  }
LABEL_30:
  MJN_BUTTONGUIDE_TIMER = 0;
}

// 0x1d294e0
static void InitHanchan(void) {
  u32 *v;
  u32 v5;
  s32 v6;
  u32 v7;
  s32 v8;
  s32 v9;
  Work_t *v13;
  s32 oya;
  Player_t *players;
  Player_t *v16;
  Player_t *v17;
  Player_t *v18;
  Work_t *v22;

  sdfInitByTime(0);
  v = sdfDefaultRandCB->v;
  v5 = v[0];
  v6 = *(u64 *)v >> 30;
  v7 = v[2];
  v8 = *(u64 *)&v[2] >> 31;
  v[2] = v[1];
  v[3] = v7;
  v9 = v8 ^ v6;
  v[0] = v8 ^ v6;
  v[1] = v5;
  Init(0, v8 ^ v6, 0);
  Work->seed = v9;
  Work->oya = sub_1905740(4, 0);
  v13 = Work;
  oya = v13->oya;
  v13->kyoku = 0;
  v13->chicha = oya;
  players = v13->players;
  v16 = players[1];
  players[0]->tensu = 25000;
  v18 = players[2];
  v17 = players[3];
  v16->tensu = 25000;
  v18->tensu = 25000;
  v17->tensu = 25000;
  v22 = Work;
  *(u64 *)&v22->honba = 0;
  v22->fDraw3D = 1;
  InitKyoku();
}

// 0x1d30710
static void Tsumikomi(void) {
  Player_t *player;

  player = Work->players[0];
  TsumikomiDecide(player);
  TsumikomiYakuhai(player);
  TsumikomiChinitsu(player);
  TsumikomiIpeiko(player);
  TsumikomiSanshokujun(player);
  TsumikomiIttsu(player);
  TsumikomiKantsu(player);
  TsumikomiToitsu(player);
  TsumikomiKotsu(player);
  TsumikomiShuntsu(player);
  TsumikomiKokushi(player);
  player = Work->players[1];
  TsumikomiDecide(player);
  TsumikomiYakuhai(player);
  TsumikomiChinitsu(player);
  TsumikomiIpeiko(player);
  TsumikomiSanshokujun(player);
  TsumikomiIttsu(player);
  TsumikomiKantsu(player);
  TsumikomiToitsu(player);
  TsumikomiKotsu(player);
  TsumikomiShuntsu(player);
  TsumikomiKokushi(player);
  player = Work->players[2];
  TsumikomiDecide(player);
  TsumikomiYakuhai(player);
  TsumikomiChinitsu(player);
  TsumikomiIpeiko(player);
  TsumikomiSanshokujun(player);
  TsumikomiIttsu(player);
  TsumikomiKantsu(player);
  TsumikomiToitsu(player);
  TsumikomiKotsu(player);
  TsumikomiShuntsu(player);
  TsumikomiKokushi(player);
  player = Work->players[3];
  TsumikomiDecide(player);
  TsumikomiYakuhai(player);
  TsumikomiChinitsu(player);
  TsumikomiIpeiko(player);
  TsumikomiSanshokujun(player);
  TsumikomiIttsu(player);
  TsumikomiKantsu(player);
  TsumikomiToitsu(player);
  TsumikomiKotsu(player);
  TsumikomiShuntsu(player);
  TsumikomiKokushi(player);
}

// 0x1d30960
static void TsumikomiDecide(Player_t *player) {
  u8 *v3;
  u32 v4;
  u8 *v5;
  u32 v6;
  s32 v7;
  u8 v8;
  u8 v9;
  u8 v10;
  char v11;
  u8 v12;
  u8 v13;
  char v14;
  char v15;
  u8 v16;
  u32 v17;
  Player_t *v18;
  u64 v19;
  s64 i;
  s32 v21;
  s64 v22;
  s32 v23;
  s32 v24;
  s32 v25;
  char *v26;
  s64 v27;
  s64 v28;
  char v29;
  Player_t *v31;
  TsumikomiPattern_t *v32;

  v3 = NewSpecific(byte, 0x24u);
  v4 = sub_1905740(256, 0);
  player->doraTsumikomiNum = 0;
  v3[32] = 0;
  v5 = v3 + 32;
  v6 = player->doraProb[0];
  v3[32] = v6;
  if (v4 < v6)
  {
    v7 = 1;
LABEL_11:
    player->doraTsumikomiNum = v7;
    goto LABEL_12;
  }
  v3[33] = 0;
  v8 = player->doraProb[0];
  v3[33] = v8;
  v9 = player->doraProb[1] + v8;
  v3[33] = v9;
  if (v4 < v9)
  {
    v7 = 2;
    goto LABEL_11;
  }
  v3[34] = 0;
  v10 = player->doraProb[0];
  v3[34] = v10;
  v11 = player->doraProb[1] + v10;
  v3[34] = v11;
  v12 = player->doraProb[2] + v11;
  v3[34] = v12;
  if (v4 < v12)
  {
    v7 = 3;
    goto LABEL_11;
  }
  v3[35] = 0;
  v13 = player->doraProb[0];
  v3[35] = v13;
  v14 = player->doraProb[1] + v13;
  v3[35] = v14;
  v15 = player->doraProb[2] + v14;
  v3[35] = v15;
  v16 = player->doraProb[3] + v15;
  v3[35] = v16;
  if (v4 < v16)
  {
    v7 = 4;
    goto LABEL_11;
  }
LABEL_12:
  v17 = sub_1905740(256, 0);
  v18 = player;
  v18->tsumikomiPattern = 0;
  v19 = 0;
  for (i = 1; ; ++i)
  {
    v3[v19 + 32] = 0;
    if (v19 >= 3)
    {
      v21 = 0;
      v22 = 0;
      do
      {
        v23 = player->tsumikomiProb[v22] + v21;
        v5[v19] = v23;
        v24 = player->tsumikomiProb[v22 + 1] + v23;
        v5[v19] = v24;
        v25 = player->tsumikomiProb[v22 + 2] + v24;
        v5[v19] = v25;
        v26 = (char *)(player)->tsumikomiProb + v22;
        v22 += 4;
        v21 = (u8)v26[35] + v25;
        v5[v19] = v21;
      }
      while ((i & 0xFFFFFFFFFFFFFFFCLL) != v22);
    }
    else
    {
      LOBYTE(v21) = 0;
      v22 = 0;
    }
    v27 = i & 3;
    if ((i & 3) != 0)
    {
      v28 = v22 + 32;
      do
      {
        --v27;
        v29 = *((u8 *)&player->tsumikomiProb->obj.klass + v28++);
        LOBYTE(v21) = v29 + v21;
        v5[v19] = v21;
      }
      while (v27);
    }
    if (v17 < (u8)v21)
      break;
    if (++v19 == 36)
      return;
  }
  v31 = player;
  v32 = mjnTsumikomiPatternTable[v19];
  v31->tsumikomiPattern = v32;
}

// 0x1d34b50
static void TsumikomiHai(Player_t *player, s32 hai) {
  Player_t *v5;
  s64 v7;
  Work_t *Work_local;

  v5 = player;
  if (player->tehaiNum == 13)
    return;
  v5 = player;
  v7 = hai;
  Work_local = Work;
  --Work_local->yama34[v7];
  --Work_local->yamaNum;
  ++v5->tehai34[v7];
  ++v5->tehaiNum;
}

// 0x1d30c50
static void TsumikomiYakuhai(Player_t *player) {
  s32 *v3;
  TsumikomiPattern_t *tsumikomiPattern;
  s32 yakuhai;
  int32x4_t *v6;
  int32x4_t *v7;
  s64 v10;
  s32 *yama34;
  s32 v12;
  int32x4_t v13;
  uint8x8_t v14;
  u32 v15;
  s32 v16;
  u32 *v17;
  s32 v18;
  s32 v19;
  u32 *v;
  u32 v23;
  s32 v24;
  u32 v25;
  s32 v26;
  s32 v27;
  s32 v28;
  s32 v29;
  s32 v30;
  s64 v31;
  int32x4_t *v32;
  Player_t *v34;
  char v36;
  Work_t *v37;
  char v39;
  Work_t *v40;
  Work_t *v42;
  u32 *v43;
  u32 *v44;
  int32x4_t *v45;
  u32 *v46;
  u32 *v47;

  v3 = NewSpecific(s32, 7u);
  tsumikomiPattern = player->tsumikomiPattern;
  if (!tsumikomiPattern)
    return;
  yakuhai = tsumikomiPattern->yakuhai;
  if (!tsumikomiPattern->yakuhai)
    return;
  v6 = v3;
  *(u64 *)&v3[0] = 0;
  v7 = &v3[0];
  v3[6] = 0;
  *(u64 *)&v3[2] = 0;
  *(u64 *)&v3[4] = 0;
  v10 = 8;
  if (Work->kyoku > 3)
    v10 = 9;
  v6->n128_u32[v10] = 1;
  *((u32 *)&v6[-4] + player->kaze - 3) = 1;
  v6[3].n128_u32[2] = 1;
  v44 = &v6[3].n128_u32[2];
  v6[3].n128_u64[0] = 0x100000001LL;
  v45 = v6 + 3;
  yama34 = Work->yama34;
  if (yama34[27] > 2)
  {
    goto LABEL_12;
  }
  v7->n128_u32[0] = 0;
LABEL_12:
  if (yama34[28] > 2)
  {
    goto LABEL_14;
  }
  v6[2].n128_u32[1] = 0;
LABEL_14:
  if (yama34[29] > 2)
  {
    goto LABEL_16;
  }
  v6[2].n128_u32[2] = 0;
LABEL_16:
  if (yama34[30] > 2)
  {
    goto LABEL_18;
  }
  v6[2].n128_u32[3] = 0;
LABEL_18:
  if (yama34[31] > 2)
  {
    v43 = &v6[3].n128_u32[1];
    goto LABEL_20;
  }
  v45->n128_u32[0] = 0;
  v43 = &v6[3].n128_u32[1];
LABEL_20:
  if (yama34[32] > 2)
  {
    goto LABEL_22;
  }
  *v43 = 0;
LABEL_22:
  if (yama34[33] >= 3)
  {
    v12 = *v44 != 0;
    goto LABEL_38;
  }
  v12 = 0;
  *v44 = 0;
LABEL_38:
  v13 = vbicq_s8((int8x16_t)xmmword_3CFFD40, vceqzq_s32(v6[2]));
  v13.n128_u32[0] = vaddvq_s32(v13) & 0xF;
  v14.n64_u64[0] = vcnt_s8((int8x8_t)v13.n128_u64[0]).n64_u64[0];
  v14.n64_u16[0] = vaddlv_u8(v14);
  v15 = v14.n64_u32[0];
  if (v6[3].n128_u32[0])
    v15 = v14.n64_u32[0] + 1;
  if (v6[3].n128_u32[1])
    ++v12;
  v16 = v15 + v12;
  if (v15 + v12)
  {
    v17 = &v6[2].n128_u32[1];
    v46 = &v6[2].n128_u32[3];
    v47 = &v6[2].n128_u32[2];
    if (v16 >= yakuhai)
      v18 = yakuhai;
    else
      v18 = v15 + v12;
    if (v18 <= 1)
      v19 = 1;
    else
      v19 = v18;
    do
    {
      v = sdfDefaultRandCB->v;
      v23 = v[0];
      v24 = *(u64 *)v >> 30;
      v25 = v[2];
      v26 = *(u64 *)&v[2] >> 31;
      v[2] = v[1];
      v[3] = v25;
      v27 = v26 ^ v24;
      v[0] = v27;
      v[1] = v23;
      v28 = v27 % v16;
      if (v27 % v16 >= 0)
        v29 = v27 % v16;
      else
        v29 = -v28;
      if (v7->n128_u32[0])
      {
        if (!v28)
        {
          v31 = 27;
          v32 = v7;
          goto LABEL_95;
        }
        v30 = 1;
        if (!*v17)
        {
LABEL_59:
          if (!*v47)
            goto LABEL_60;
          goto LABEL_74;
        }
      }
      else
      {
        v30 = 0;
        if (!*v17)
          goto LABEL_59;
      }
      if (v29 == v30)
      {
        v31 = 28;
        v32 = ((char *)v6 + 36);
        goto LABEL_95;
      }
      ++v30;
      if (!*v47)
      {
LABEL_60:
        if (!*v46)
          goto LABEL_61;
        goto LABEL_80;
      }
LABEL_74:
      if (v29 == v30)
      {
        v32 = ((char *)v6 + 40);
        v31 = 29;
        goto LABEL_95;
      }
      ++v30;
      if (!*v46)
      {
LABEL_61:
        if (!v45->n128_u32[0])
          goto LABEL_62;
        goto LABEL_84;
      }
LABEL_80:
      if (v29 == v30)
      {
        v32 = ((char *)v6 + 44);
        v31 = 30;
        goto LABEL_95;
      }
      ++v30;
      if (!v45->n128_u32[0])
      {
LABEL_62:
        if (!*v43)
          goto LABEL_63;
        goto LABEL_88;
      }
LABEL_84:
      if (v29 == v30)
      {
        v32 = v6 + 3;
        v31 = 31;
        goto LABEL_95;
      }
      ++v30;
      if (!*v43)
      {
LABEL_63:
        if (!*v44)
          goto LABEL_115;
LABEL_92:
        if (v29 == v30)
        {
          v32 = ((char *)v6 + 56);
          v31 = 33;
LABEL_95:
          v34 = player;
          if (player->tehaiNum == 13)
          {
LABEL_104:
            if (v34->tehaiNum != 13)
            {
              v39 = 1;
              v40 = Work;
              --v40->yama34[v31];
              --v40->yamaNum;
              ++v34->tehai34[v31];
              ++v34->tehaiNum;
              if ((v39 & 1) == 0)
              {
                v34 = player;
              }
            }
            if (v34->tehaiNum != 13)
            {
              v34 = player;
              v42 = Work;
              --v42->yama34[v31];
              --v42->yamaNum;
              ++v34->tehai34[v31];
              ++v34->tehaiNum;
            }
            --v16;
            v32->n128_u32[0] = 0;
            goto LABEL_115;
          }
          v36 = 1;
          v37 = Work;
          --v37->yama34[v31];
          --v37->yamaNum;
          ++v34->tehai34[v31];
          ++v34->tehaiNum;
          if ((v36 & 1) == 0)
          {
            v34 = player;
          }
          goto LABEL_104;
        }
        goto LABEL_115;
      }
LABEL_88:
      if (v29 == v30)
      {
        v32 = v43;
        v31 = 32;
        goto LABEL_95;
      }
      ++v30;
      if (*v44)
        goto LABEL_92;
LABEL_115:
      --v19;
    }
    while (v19);
  }
}

// 0x1d319d0
static void TsumikomiIpeiko(Player_t *player) {
  s32 *v3;
  TsumikomiPattern_t *tsumikomiPattern;
  s64 v5;
  s64 v6;
  s32 v7;
  s32 *yama34;
  s64 v10;
  u32 *v;
  u32 v16;
  u32 v17;
  s32 v18;
  s32 v19;
  s32 v20;
  s32 v21;
  s64 v22;
  Player_t *v23;
  s64 v24;
  char v26;
  Work_t *Work_local;
  char v29;
  Work_t *v30;
  s32 v31;
  char v33;
  s64 v34;
  Work_t *v35;
  char v37;
  s64 v38;
  Work_t *v39;
  s32 v40;
  char v42;
  s64 v43;
  Work_t *v44;
  s64 v46;
  Work_t *v47;

  v3 = NewSpecific(s32, 0x19u);
  tsumikomiPattern = player->tsumikomiPattern;
  if (!tsumikomiPattern || !tsumikomiPattern->ipeiko)
    return;
  v5 = v3;
  v6 = 0;
  v7 = 0;
  do
  {
    if ((u32)v6 % 9 - 7 >= 2)
    {
      yama34 = Work->yama34;
      if (yama34[v6] >= 2)
      {
        if (yama34[v6 + 1] < 2)
          goto LABEL_6;
        if (yama34[v6 + 2] < 2)
          goto LABEL_6;
        v10 = v5 + 4 * v7++;
        *(u32 *)(v10 + 32) = v6;
      }
    }
LABEL_6:
    ++v6;
  }
  while (v6 != 25);
  if (v7)
  {
    goto LABEL_23;
LABEL_24:
    goto LABEL_25;
LABEL_23:
    goto LABEL_24;
LABEL_25:
    v = sdfDefaultRandCB->v;
    v16 = v[0];
    v17 = v[2];
    v18 = *(u64 *)v >> 30;
    v19 = *(u64 *)&v[2] >> 31;
    v[2] = v[1];
    v[3] = v17;
    v20 = v19 ^ v18;
    v[0] = v20;
    v[1] = v16;
    if (v20 >= 0)
      v21 = v20;
    else
      v21 = -v20;
    v22 = *(s32 *)(v5 + 4 * (v21 % v7) + 32);
    v23 = player;
    v24 = v22;
    if (player->tehaiNum != 13)
    {
      v26 = 1;
      Work_local = Work;
      --Work_local->yama34[v24];
      --Work_local->yamaNum;
      ++v23->tehai34[v24];
      ++v23->tehaiNum;
      if ((v26 & 1) == 0)
      {
        v23 = player;
      }
    }
    if (v23->tehaiNum != 13)
    {
      v29 = 1;
      v30 = Work;
      --v30->yama34[v24];
      --v30->yamaNum;
      ++v23->tehai34[v24];
      ++v23->tehaiNum;
      if ((v29 & 1) == 0)
      {
        v23 = player;
      }
    }
    v31 = v22 + 1;
    if (v23->tehaiNum != 13)
    {
      v33 = 1;
      v34 = v31;
      v35 = Work;
      --v35->yama34[v34];
      --v35->yamaNum;
      ++v23->tehai34[v34];
      ++v23->tehaiNum;
      if ((v33 & 1) == 0)
      {
        v23 = player;
      }
    }
    if (v23->tehaiNum != 13)
    {
      v37 = 1;
      v38 = v31;
      v39 = Work;
      --v39->yama34[v38];
      --v39->yamaNum;
      ++v23->tehai34[v38];
      ++v23->tehaiNum;
      if ((v37 & 1) == 0)
      {
        v23 = player;
      }
    }
    v40 = v22 + 2;
    if (v23->tehaiNum != 13)
    {
      v42 = 1;
      v43 = v40;
      v44 = Work;
      --v44->yama34[v43];
      --v44->yamaNum;
      ++v23->tehai34[v43];
      ++v23->tehaiNum;
      if ((v42 & 1) == 0)
      {
        v23 = player;
      }
    }
    if (v23->tehaiNum != 13)
    {
      v23 = player;
      v46 = v40;
      v47 = Work;
      --v47->yama34[v46];
      --v47->yamaNum;
      ++v23->tehai34[v46];
      ++v23->tehaiNum;
    }
  }
}

// 0x1d32010
static void TsumikomiSanshokujun(Player_t *player) {
  s32 *v3;
  TsumikomiPattern_t *tsumikomiPattern;
  s64 v5;
  s64 v6;
  s32 v7;
  s64 v9;
  s64 v10;
  u32 *v;
  u32 v16;
  u32 v17;
  s32 v18;
  s32 v19;
  s32 v20;
  s32 v21;
  s64 v22;
  Player_t *v23;
  char v25;
  Work_t *Work_local;
  char v28;
  s64 v29;
  Work_t *v30;
  char v32;
  s64 v33;
  Work_t *v34;
  char v36;
  s64 v37;
  Work_t *v38;
  char v40;
  s64 v41;
  Work_t *v42;
  char v44;
  s64 v45;
  Work_t *v46;
  char v48;
  s64 v49;
  Work_t *v50;
  char v52;
  s64 v53;
  Work_t *v54;
  s32 v56;
  s64 v57;
  Work_t *v58;

  v3 = NewSpecific(s32, 7u);
  tsumikomiPattern = player->tsumikomiPattern;
  if (!tsumikomiPattern || !tsumikomiPattern->sanshokujun)
    return;
  v5 = v3;
  v6 = 0;
  v7 = 0;
  do
  {
    if (!Work->yama34[v6])
    {
      v9 = v6 + 1;
      goto LABEL_7;
    }
    v9 = v6 + 1;
    if (Work->yama34[v6 + 1])
    {
      if (!Work->yama34[v6 + 2])
        goto LABEL_7;
      if (!Work->yama34[v6 + 9])
        goto LABEL_7;
      if (!Work->yama34[v6 + 10])
        goto LABEL_7;
      if (!Work->yama34[v6 + 11])
        goto LABEL_7;
      if (Work->yama34[v6 + 18])
      {
        if (Work->yama34[v6 + 19])
        {
          if (Work->yama34[v6 + 20])
          {
            v10 = v5 + 4 * v7++;
            *(u32 *)(v10 + 32) = v6;
          }
        }
      }
    }
LABEL_7:
    v6 = v9;
  }
  while (v9 != 7);
  if (v7)
  {
    goto LABEL_44;
LABEL_45:
    goto LABEL_46;
LABEL_44:
    goto LABEL_45;
LABEL_46:
    v = sdfDefaultRandCB->v;
    v16 = v[0];
    v17 = v[2];
    v18 = *(u64 *)v >> 30;
    v19 = *(u64 *)&v[2] >> 31;
    v[2] = v[1];
    v[3] = v17;
    v20 = v19 ^ v18;
    v[0] = v20;
    v[1] = v16;
    if (v20 >= 0)
      v21 = v20;
    else
      v21 = -v20;
    v22 = *(s32 *)(v5 + 4 * (v21 % v7) + 32);
    v23 = player;
    if (player->tehaiNum != 13)
    {
      v25 = 1;
      Work_local = Work;
      --Work_local->yama34[v22];
      --Work_local->yamaNum;
      ++v23->tehai34[v22];
      ++v23->tehaiNum;
      if ((v25 & 1) == 0)
      {
        v23 = player;
      }
    }
    if (v23->tehaiNum != 13)
    {
      v28 = 1;
      v29 = (s32)v22 + 1;
      v30 = Work;
      --v30->yama34[v29];
      --v30->yamaNum;
      ++v23->tehai34[v29];
      ++v23->tehaiNum;
      if ((v28 & 1) == 0)
      {
        v23 = player;
      }
    }
    if (v23->tehaiNum != 13)
    {
      v32 = 1;
      v33 = (s32)v22 + 2;
      v34 = Work;
      --v34->yama34[v33];
      --v34->yamaNum;
      ++v23->tehai34[v33];
      ++v23->tehaiNum;
      if ((v32 & 1) == 0)
      {
        v23 = player;
      }
    }
    if (v23->tehaiNum != 13)
    {
      v36 = 1;
      v37 = (s32)v22 + 9;
      v38 = Work;
      --v38->yama34[v37];
      --v38->yamaNum;
      ++v23->tehai34[v37];
      ++v23->tehaiNum;
      if ((v36 & 1) == 0)
      {
        v23 = player;
      }
    }
    if (v23->tehaiNum != 13)
    {
      v40 = 1;
      v41 = (s32)v22 + 10;
      v42 = Work;
      --v42->yama34[v41];
      --v42->yamaNum;
      ++v23->tehai34[v41];
      ++v23->tehaiNum;
      if ((v40 & 1) == 0)
      {
        v23 = player;
      }
    }
    if (v23->tehaiNum != 13)
    {
      v44 = 1;
      v45 = (s32)v22 + 11;
      v46 = Work;
      --v46->yama34[v45];
      --v46->yamaNum;
      ++v23->tehai34[v45];
      ++v23->tehaiNum;
      if ((v44 & 1) == 0)
      {
        v23 = player;
      }
    }
    if (v23->tehaiNum != 13)
    {
      v48 = 1;
      v49 = (s32)v22 + 18;
      v50 = Work;
      --v50->yama34[v49];
      --v50->yamaNum;
      ++v23->tehai34[v49];
      ++v23->tehaiNum;
      if ((v48 & 1) == 0)
      {
        v23 = player;
      }
    }
    if (v23->tehaiNum != 13)
    {
      v52 = 1;
      v53 = (s32)v22 + 19;
      v54 = Work;
      --v54->yama34[v53];
      --v54->yamaNum;
      ++v23->tehai34[v53];
      ++v23->tehaiNum;
      if ((v52 & 1) == 0)
      {
        v23 = player;
      }
    }
    if (v23->tehaiNum != 13)
    {
      v56 = v22 + 20;
      v23 = player;
      v57 = v56;
      v58 = Work;
      --v58->yama34[v57];
      --v58->yamaNum;
      ++v23->tehai34[v57];
      ++v23->tehaiNum;
    }
  }
}

// 0x1d34c40
static void TsumikomiIttsuSub(Player_t *player, s32 color) {
  s32 v5;
  s64 v6;
  s64 v7;
  s64 v8;
  Work_t *Work_local;
  s64 v10;
  Player_t *v11;

  v5 = 9 * color;
  if (9 * color <= 2147483638)
  {
    v6 = v5 + 9;
    v7 = v5 + 8;
    do
    {
      v11 = player;
      if (player->tehaiNum != 13)
      {
        v11 = player;
        v8 = 4 * v7;
        Work_local = Work;
        *(u32 *)((char *)&Work_local->yama34->obj.klass + v8) = *((u32 *)&Work_local->yama34->obj.klass + v7)
                                                                  - 1;
        --Work_local->yamaNum;
        *(u32 *)((char *)&v11->tehai34->obj.klass + v8) = *((u32 *)&v11->tehai34->obj.klass + v7)
                                                                  + 1;
        ++v11->tehaiNum;
      }
      v10 = v7 - 7;
      ++v7;
    }
    while (v10 < v6);
  }
}

// 0x1d32950
static void TsumikomiIttsu(Player_t *player) {
  TsumikomiPattern_t *tsumikomiPattern;
  u32 *v;
  u32 v8;
  u32 v9;
  s32 v10;
  s32 v11;
  s32 v12;
  s32 v14;
  s64 v15;
  u64 v16;
  s32 *yama34;
  s64 v18;
  u64 v19;
  s64 v22;
  u32 *v23;

  tsumikomiPattern = player->tsumikomiPattern;
  if (!tsumikomiPattern || !tsumikomiPattern->ittsu)
    return;
  v = sdfDefaultRandCB->v;
  v8 = v[0];
  v9 = v[2];
  v10 = *(u64 *)v >> 30;
  v11 = *(u64 *)&v[2] >> 31;
  v[2] = v[1];
  v[3] = v9;
  v12 = v11 ^ v10;
  v[0] = v12;
  v[1] = v8;
  if (v12 % 3 >= 0)
    v14 = v12 % 3;
  else
    v14 = -(v12 % 3);
  v15 = (u32)(9 * v14);
  v16 = (u32)(v15 + 9);
  yama34 = Work->yama34;
  while (yama34[v15])
  {
    if (++v15 >= v16)
      goto LABEL_37;
  }
  v14 = (v14 + 1) % 3u;
  LODWORD(v18) = 9 * v14;
  LODWORD(v19) = 9 * v14 + 9;
  v18 = (u32)v18;
  while (yama34[v18])
  {
    if (++v18 >= (u64)(u32)v19)
      goto LABEL_37;
  }
  if (v14 == 2)
    v14 = 0;
  else
    ++v14;
  v22 = (u32)(9 * v14);
  if (yama34[(u32)v22])
  {
    v23 = ((char *)yama34 + 4 * v22);
    if (v23[9])
    {
      if (v23[10] && v23[11] && v23[12] && v23[13] && v23[14] && v23[15] && v23[16])
LABEL_37:
        TsumikomiIttsuSub(player, v14);
    }
  }
  return;
}

// 0x1d31410
static void TsumikomiChinitsu(Player_t *player) {
  s32 *v3;
  TsumikomiPattern_t *tsumikomiPattern;
  s32 chinitsu;
  s32 v9;
  u32 *v;
  u32 v11;
  s32 v12;
  u32 v13;
  s32 v14;
  s32 v16;
  s32 v17;
  u64 v18;
  u64 v19;
  s64 v20;
  s32 v21;
  s32 v22;
  s64 v23;
  s32 v24;
  s32 v25;
  s32 v26;
  s64 i;
  s64 v28;
  u32 *v32;
  u32 v33;
  u32 v34;
  s32 v35;
  s32 v36;
  s32 v37;
  s32 v38;
  s64 j;
  s32 *v41;
  s64 v42;
  Work_t *Work_local;
  s64 v44;
  s64 v45;
  Player_t *v46;
  s32 *v48;
  s32 *m_Items;
  s32 *aim;
  s32 *v51;
  s32 *v52;
  s32 v53;
  s32 v54;
  s32 *v55;

  v3 = NewSpecific(s32, 0x24u);
  v55 = NewSpecific(s32, 0x24u);
  tsumikomiPattern = player->tsumikomiPattern;
  if (!tsumikomiPattern)
    return;
  chinitsu = tsumikomiPattern->chinitsu;
  if (!tsumikomiPattern->chinitsu)
    return;
  v9 = 0;
  v = sdfDefaultRandCB->v;
  v11 = v[0];
  v12 = *(u64 *)v >> 30;
  v13 = v[2];
  v14 = *(u64 *)&v[2] >> 31;
  v[2] = v[1];
  v[3] = v13;
  v16 = v14 ^ v12;
  v[0] = v16;
  v[1] = v11;
  if (v16 % 3 >= 0)
    v17 = v16 % 3;
  else
    v17 = -(v16 % 3);
  v18 = (u32)(9 * v17);
  v54 = v17;
  v19 = (u32)(v18 + 9);
  do
  {
    switch (Work->yama34[v18])
    {
      case 1:
        v23 = (s64)(char *)v3 + 4 * v9++;
        *(u32 *)(v23 + 32) = v18;
        break;
      case 2:
        v20 = &v3[0];
        v22 = v9 + 1;
        *(u32 *)((s64)&v3[0] + 4 * v9) = v18;
        v9 += 2;
        goto LABEL_14;
      case 3:
        v24 = v9 + 1;
        v25 = v9 + 2;
        *(u32 *)((s64)&v3[0] + 4 * v9) = v18;
        v9 += 3;
        *(u32 *)((s64)&v3[0] + 4 * v24) = v18;
        *(u32 *)((s64)&v3[0] + 4 * v25) = v18;
        break;
      case 4:
        v20 = &v3[0];
        v21 = v9 + 2;
        *(u32 *)((s64)&v3[0] + 4 * v9) = v18;
        *(u32 *)((s64)&v3[0] + 4 * (v9 + 1)) = v18;
        v22 = v9 + 3;
        v9 += 4;
        *(u32 *)((s64)&v3[0] + 4 * v21) = v18;
LABEL_14:
        *(u32 *)(v20 + 4 * v22) = v18;
        break;
      default:
        break;
    }
    ++v18;
  }
  while (v18 < v19);
  if (v9)
  {
    if (v9 >= chinitsu)
      v26 = chinitsu;
    else
      v26 = v9;
    v53 = v26;
    if (v9 >= 1)
    {
      for (i = 0; v9 != i; ++i)
      {
        Work->randomArray[i]->index = i;
        v32 = sdfDefaultRandCB->v;
        v33 = v32[0];
        v34 = v32[2];
        v35 = *(u64 *)v32 >> 30;
        v36 = *(u64 *)&v32[2] >> 31;
        v32[2] = v32[1];
        v32[3] = v34;
        v37 = v36 ^ v35;
        v32[0] = v37;
        v32[1] = v33;
        if (v37 >= 0)
          v38 = v37;
        else
          v38 = -v37;
        v28 = (s64)Work->randomArray + 8 * i;
        *(u32 *)(*(u64 *)(v28 + 32) + 20) = v38;
      }
    }
    QsortRandom(&Work->randomArray, 0, v9 - 1);
    if (v9 >= 1)
    {
      for (j = 0; j != v9; ++j)
      {
        *(u32 *)((s64)&v55[0] + 4 * j) = *(u32 *)((s64)(char *)v3 + 4 * Work->randomArray[j]->index + 32);
      }
      v41 = &v55[0];
      if (v53 <= 1)
        v42 = 1;
      else
        v42 = v53;
      do
      {
        v45 = *v41++;
        v44 = v45;
        v46 = player;
        if (player->tehaiNum != 13)
        {
          v46 = player;
          Work_local = Work;
          --Work_local->yama34[v44];
          --Work_local->yamaNum;
          ++v46->tehai34[v44];
          ++v46->tehaiNum;
        }
        --v42;
      }
      while (v42);
    }
    if (v54 == 2)
    {
      aim = player->aim;
      v51 = &aim[2];
      m_Items = &aim[5];
      if (!player->tsumikomiPattern->yakuhai)
        m_Items = v51;
    }
    else if (v54 == 1)
    {
      v52 = player->aim;
      if (player->tsumikomiPattern->yakuhai)
        m_Items = &v52[4];
      else
        m_Items = &v52[1];
    }
    else
    {
      if (v54)
        return;
      v48 = player->aim;
      if (player->tsumikomiPattern->yakuhai)
        m_Items = &v48[3];
      else
        m_Items = v48;
    }
    *m_Items = 2;
  }
}

// 0x1d32e00
static void TsumikomiKantsu(Player_t *player) {
  s32 *v2;
  TsumikomiPattern_t *tsumikomiPattern;
  s32 kantsu;
  s64 v5;
  s64 v6;
  s32 v7;
  s64 v9;
  s32 v10;
  u32 *v;
  u32 v12;
  s32 v13;
  u32 v14;
  s32 v15;
  u32 v16;
  s64 v17;
  u32 *v18;
  s64 v19;
  s64 v20;
  Player_t *v24;
  char v26;
  Work_t *Work_local;
  char v29;
  Work_t *v30;
  char v32;
  Work_t *v33;
  Work_t *v35;
  s32 v36;
  s32 v37;

  v2 = NewSpecific(s32, 0x22u);
  tsumikomiPattern = player->tsumikomiPattern;
  if (tsumikomiPattern)
  {
    kantsu = tsumikomiPattern->kantsu;
    if (tsumikomiPattern->kantsu)
    {
      v5 = v2;
      v6 = 0;
      v7 = 0;
      do
      {
        if (Work->yama34[v6] == 4)
        {
          v9 = v5 + 4 * v7++;
          *(u32 *)(v9 + 32) = v6;
        }
        ++v6;
      }
      while (v6 != 34);
      if (v7 >= 1)
      {
        if (v7 >= kantsu)
          v10 = kantsu;
        else
          v10 = v7;
        if (v10 <= 1)
          v10 = 1;
        v36 = v10;
        v37 = 0;
LABEL_21:
LABEL_23:
        goto LABEL_19;
        while (1)
        {
          goto LABEL_23;
LABEL_19:
          v = sdfDefaultRandCB->v;
          v12 = v[0];
          v13 = *(u64 *)v >> 30;
          v14 = v[2];
          v15 = *(u64 *)&v[2] >> 31;
          v[2] = v[1];
          v[3] = v14;
          v16 = v15 ^ v13;
          v[0] = v16;
          v[1] = v12;
          v17 = v5 + 4 * (u8)(v16 % v7);
          v20 = *(s32 *)(v17 + 32);
          v18 = (v17 + 32);
          v19 = v20;
          if ((u32)v20 == -1)
          {
            goto LABEL_21;
          }
          v24 = player;
          if (player->tehaiNum != 13)
          {
            v26 = 1;
            Work_local = Work;
            --Work_local->yama34[v19];
            --Work_local->yamaNum;
            ++v24->tehai34[v19];
            ++v24->tehaiNum;
            if ((v26 & 1) == 0)
            {
              v24 = player;
            }
          }
          if (v24->tehaiNum != 13)
          {
            v29 = 1;
            v30 = Work;
            --v30->yama34[v19];
            --v30->yamaNum;
            ++v24->tehai34[v19];
            ++v24->tehaiNum;
            if ((v29 & 1) == 0)
            {
              v24 = player;
            }
          }
          if (v24->tehaiNum != 13)
          {
            v32 = 1;
            v33 = Work;
            --v33->yama34[v19];
            --v33->yamaNum;
            ++v24->tehai34[v19];
            ++v24->tehaiNum;
            if ((v32 & 1) == 0)
            {
              v24 = player;
            }
          }
          if (v24->tehaiNum != 13)
          {
            v24 = player;
            v35 = Work;
            --v35->yama34[v19];
            --v35->yamaNum;
            ++v24->tehai34[v19];
            ++v24->tehaiNum;
          }
          *v18 = -1;
          if (v37 + 1 == v36)
            return;
          ++v37;
          goto LABEL_21;
        }
      }
    }
  }
}

// 0x1d33350
static void TsumikomiToitsu(Player_t *player) {
  s32 *v2;
  TsumikomiPattern_t *tsumikomiPattern;
  s32 toitsu;
  s64 v5;
  s64 v6;
  s32 v7;
  s64 v9;
  s32 v10;
  s32 v11;
  u32 *v;
  u32 v13;
  s32 v14;
  u32 v15;
  s32 v16;
  u32 v17;
  s64 v18;
  u32 *v19;
  s64 v20;
  s64 v21;
  Player_t *v25;
  char v27;
  Work_t *Work_local;
  Work_t *v30;
  s32 v31;

  v2 = NewSpecific(s32, 0x22u);
  tsumikomiPattern = player->tsumikomiPattern;
  if (tsumikomiPattern)
  {
    toitsu = tsumikomiPattern->toitsu;
    if (tsumikomiPattern->toitsu)
    {
      v5 = v2;
      v6 = 0;
      v7 = 0;
      do
      {
        if (Work->yama34[v6] >= 2)
        {
          v9 = v5 + 4 * v7++;
          *(u32 *)(v9 + 32) = v6;
        }
        ++v6;
      }
      while (v6 != 34);
      if (v7 >= 1)
      {
        if (v7 >= toitsu)
          v10 = toitsu;
        else
          v10 = v7;
        v11 = 0;
        if (v10 <= 1)
          v10 = 1;
        v31 = v10;
        while (1)
        {
          v = sdfDefaultRandCB->v;
          v13 = v[0];
          v14 = *(u64 *)v >> 30;
          v15 = v[2];
          v16 = *(u64 *)&v[2] >> 31;
          v[2] = v[1];
          v[3] = v15;
          v17 = v16 ^ v14;
          v[0] = v17;
          v[1] = v13;
          v18 = v5 + 4 * (u8)(v17 % v7);
          v21 = *(s32 *)(v18 + 32);
          v19 = (v18 + 32);
          v20 = v21;
          if ((u32)v21 != -1)
          {
            v25 = player;
            if (player->tehaiNum != 13)
            {
              v27 = 1;
              Work_local = Work;
              --Work_local->yama34[v20];
              --Work_local->yamaNum;
              ++v25->tehai34[v20];
              ++v25->tehaiNum;
              if ((v27 & 1) == 0)
              {
                v25 = player;
              }
            }
            if (v25->tehaiNum != 13)
            {
              v25 = player;
              v30 = Work;
              --v30->yama34[v20];
              --v30->yamaNum;
              ++v25->tehai34[v20];
              ++v25->tehaiNum;
            }
            ++v11;
            *v19 = -1;
            if (v11 == v31)
              return;
          }
        }
      }
    }
  }
}

// 0x1d33740
static void TsumikomiKotsu(Player_t *player) {
  s32 *v2;
  TsumikomiPattern_t *tsumikomiPattern;
  s32 kotsu;
  s64 v5;
  s64 v6;
  s32 v7;
  s64 v9;
  s32 v10;
  s32 v11;
  u32 *v;
  u32 v13;
  s32 v14;
  u32 v15;
  s32 v16;
  u32 v17;
  s64 v18;
  u32 *v19;
  s64 v20;
  s64 v21;
  Player_t *v25;
  char v27;
  Work_t *Work_local;
  char v30;
  Work_t *v31;
  Work_t *v33;
  s32 v34;

  v2 = NewSpecific(s32, 0x22u);
  tsumikomiPattern = player->tsumikomiPattern;
  if (tsumikomiPattern)
  {
    kotsu = tsumikomiPattern->kotsu;
    if (tsumikomiPattern->kotsu)
    {
      v5 = v2;
      v6 = 0;
      v7 = 0;
      do
      {
        if (Work->yama34[v6] >= 3)
        {
          v9 = v5 + 4 * v7++;
          *(u32 *)(v9 + 32) = v6;
        }
        ++v6;
      }
      while (v6 != 34);
      if (v7 >= 1)
      {
        if (v7 >= kotsu)
          v10 = kotsu;
        else
          v10 = v7;
        v11 = 0;
        if (v10 <= 1)
          v10 = 1;
        v34 = v10;
        while (1)
        {
          v = sdfDefaultRandCB->v;
          v13 = v[0];
          v14 = *(u64 *)v >> 30;
          v15 = v[2];
          v16 = *(u64 *)&v[2] >> 31;
          v[2] = v[1];
          v[3] = v15;
          v17 = v16 ^ v14;
          v[0] = v17;
          v[1] = v13;
          v18 = v5 + 4 * (u8)(v17 % v7);
          v21 = *(s32 *)(v18 + 32);
          v19 = (v18 + 32);
          v20 = v21;
          if ((u32)v21 != -1)
          {
            v25 = player;
            if (player->tehaiNum != 13)
            {
              v27 = 1;
              Work_local = Work;
              --Work_local->yama34[v20];
              --Work_local->yamaNum;
              ++v25->tehai34[v20];
              ++v25->tehaiNum;
              if ((v27 & 1) == 0)
              {
                v25 = player;
              }
            }
            if (v25->tehaiNum != 13)
            {
              v30 = 1;
              v31 = Work;
              --v31->yama34[v20];
              --v31->yamaNum;
              ++v25->tehai34[v20];
              ++v25->tehaiNum;
              if ((v30 & 1) == 0)
              {
                v25 = player;
              }
            }
            if (v25->tehaiNum != 13)
            {
              v25 = player;
              v33 = Work;
              --v33->yama34[v20];
              --v33->yamaNum;
              ++v25->tehai34[v20];
              ++v25->tehaiNum;
            }
            ++v11;
            *v19 = -1;
            if (v11 == v34)
              return;
          }
        }
      }
    }
  }
}

// 0x1d33bf0
static void TsumikomiShuntsu(Player_t *player) {
  s32 *v3;
  TsumikomiPattern_t *tsumikomiPattern;
  s32 shuntsu;
  s64 v6;
  s32 v7;
  s64 v8;
  Work_t *v9;
  s64 v10;
  s32 v11;
  s32 *yama34;
  s64 v14;
  u32 *v;
  u32 v20;
  u32 v21;
  s32 v22;
  s32 v23;
  s32 v24;
  s32 v25;
  s64 v26;
  Player_t *v27;
  char v29;
  Work_t *Work_local;
  char v32;
  s64 v33;
  Work_t *v34;

  v3 = NewSpecific(s32, 0x19u);
  tsumikomiPattern = player->tsumikomiPattern;
  if (tsumikomiPattern)
  {
    shuntsu = tsumikomiPattern->shuntsu;
    if (tsumikomiPattern->shuntsu)
    {
      v6 = v3;
      v7 = 0;
      while (1)
      {
        v10 = 0;
        v11 = 0;
        do
        {
          if ((u32)v10 % 9 - 7 >= 2)
          {
            yama34 = Work->yama34;
            if (yama34[v10] >= 1)
            {
              if (yama34[v10 + 1] < 1)
                goto LABEL_9;
              if (Work->yama34[v10 + 2] < 1)
                goto LABEL_9;
              v14 = v6 + 4 * v11++;
              *(u32 *)(v14 + 32) = v10;
              goto LABEL_9;
            }
          }
LABEL_9:
          ++v10;
        }
        while (v10 != 25);
        if (v11)
        {
          goto LABEL_26;
LABEL_27:
          goto LABEL_28;
LABEL_26:
          goto LABEL_27;
LABEL_28:
          v = sdfDefaultRandCB->v;
          v20 = v[0];
          v21 = v[2];
          v22 = *(u64 *)v >> 30;
          v23 = *(u64 *)&v[2] >> 31;
          v[2] = v[1];
          v[3] = v21;
          v24 = v23 ^ v22;
          v[0] = v24;
          v[1] = v20;
          v25 = v24 >= 0 ? v24 : -v24;
          v26 = *(s32 *)(v6 + 4 * (v25 % v11) + 32);
          v27 = player;
          if (player->tehaiNum != 13)
          {
            v29 = 1;
            Work_local = Work;
            --Work_local->yama34[v26];
            --Work_local->yamaNum;
            ++v27->tehai34[v26];
            ++v27->tehaiNum;
            if ((v29 & 1) == 0)
            {
              v27 = player;
            }
          }
          if (v27->tehaiNum != 13)
          {
            v32 = 1;
            v33 = (s32)v26 + 1;
            v34 = Work;
            --v34->yama34[v33];
            --v34->yamaNum;
            ++v27->tehai34[v33];
            ++v27->tehaiNum;
            if ((v32 & 1) == 0)
            {
              v27 = player;
            }
          }
          if (v27->tehaiNum != 13)
          {
            v27 = player;
            v8 = (s32)v26 + 2;
            v9 = Work;
            --v9->yama34[v8];
            --v9->yamaNum;
            ++v27->tehai34[v8];
            ++v27->tehaiNum;
          }
          if (++v7 != shuntsu)
            continue;
        }
        return;
      }
    }
  }
}

// 0x1d34080
static void TsumikomiKokushi(Player_t *player) {
  s32 *v3;
  s32 *v4;
  TsumikomiPattern_t *tsumikomiPattern;
  s64 v6;
  u32 *v7;
  u32 *v;
  u32 v11;
  u32 v12;
  u32 v13;
  s32 *yama34;
  u32 v16;
  s64 v17;
  s64 v18;
  s64 v19;
  s64 v20;
  s64 v21;
  s64 v22;
  s64 v23;
  s64 v24;
  s64 v25;
  s64 v26;
  s64 v27;
  Random_t *v29;
  Random_t *v31;
  Random_t *v33;
  Random_t *v35;
  Random_t *v37;
  Random_t *v39;
  Random_t *v41;
  Random_t *v43;
  Random_t *v45;
  Random_t *v47;
  Random_t *v49;
  Random_t *v51;
  Random_t *v53;
  s64 v57;
  s32 *v58;
  Work_t *Work_local;
  s64 v60;
  s64 v61;
  Player_t *v62;

  v3 = NewSpecific(s32, 0x24u);
  v4 = NewSpecific(s32, 0x24u);
  tsumikomiPattern = player->tsumikomiPattern;
  if (!tsumikomiPattern)
    return;
  LODWORD(v6) = tsumikomiPattern->kokushi;
  if (!tsumikomiPattern->kokushi)
    return;
  v7 = v4;
  v = sdfDefaultRandCB->v;
  v11 = v[0];
  v12 = v[1];
  v13 = v[2];
  v[0] = (*(u64 *)&v[2] >> 31) ^ (*(u64 *)v >> 30);
  v[1] = v11;
  v[2] = v12;
  v[3] = v13;
  yama34 = Work->yama34;
  if (yama34[0])
  {
    v16 = 1;
    v3[0] = 0;
    goto LABEL_13;
  }
  v16 = 0;
  yama34 = Work->yama34;
LABEL_13:
  if (yama34[8])
  {
    v17 = (s64)(char *)v3 + 4 * v16++;
    *(u32 *)(v17 + 32) = 8;
  }
  yama34 = Work->yama34;
  if (yama34[9])
  {
    v18 = (s64)(char *)v3 + 4 * v16++;
    *(u32 *)(v18 + 32) = 9;
  }
  yama34 = Work->yama34;
  if (yama34[17])
  {
    v19 = (s64)(char *)v3 + 4 * v16++;
    *(u32 *)(v19 + 32) = 17;
  }
  yama34 = Work->yama34;
  if (yama34[18])
  {
    v20 = (s64)(char *)v3 + 4 * v16++;
    *(u32 *)(v20 + 32) = 18;
  }
  yama34 = Work->yama34;
  if (yama34[26])
  {
    v21 = (s64)(char *)v3 + 4 * v16++;
    *(u32 *)(v21 + 32) = 26;
  }
  yama34 = Work->yama34;
  if (yama34[27])
  {
    v22 = (s64)(char *)v3 + 4 * v16++;
    *(u32 *)(v22 + 32) = 27;
  }
  yama34 = Work->yama34;
  if (yama34[28])
  {
    v23 = (s64)(char *)v3 + 4 * v16++;
    *(u32 *)(v23 + 32) = 28;
  }
  yama34 = Work->yama34;
  if (yama34[29])
  {
    v24 = (s64)(char *)v3 + 4 * v16++;
    *(u32 *)(v24 + 32) = 29;
  }
  yama34 = Work->yama34;
  if (yama34[30])
  {
    v25 = (s64)(char *)v3 + 4 * v16++;
    *(u32 *)(v25 + 32) = 30;
  }
  yama34 = Work->yama34;
  if (yama34[31])
  {
    v26 = (s64)(char *)v3 + 4 * v16++;
    *(u32 *)(v26 + 32) = 31;
  }
  yama34 = Work->yama34;
  if (yama34[32])
  {
    v27 = (s64)(char *)v3 + 4 * v16++;
    *(u32 *)(v27 + 32) = 32;
  }
  yama34 = Work->yama34;
  if (yama34[33])
  {
    v3[v16] = 33;
    if (v16 == 12)
    {
      v29 = Work->randomArray[0];
      v29->index = 0;
      v29->value = sub_1905740(0x7FFFFFFF, 0);
      v31 = Work->randomArray[1];
      v31->index = 1;
      v31->value = sub_1905740(0x7FFFFFFF, 0);
      v33 = Work->randomArray[2];
      v33->index = 2;
      v33->value = sub_1905740(0x7FFFFFFF, 0);
      v35 = Work->randomArray[3];
      v35->index = 3;
      v35->value = sub_1905740(0x7FFFFFFF, 0);
      v37 = Work->randomArray[4];
      v37->index = 4;
      v37->value = sub_1905740(0x7FFFFFFF, 0);
      v39 = Work->randomArray[5];
      v39->index = 5;
      v39->value = sub_1905740(0x7FFFFFFF, 0);
      v41 = Work->randomArray[6];
      v41->index = 6;
      v41->value = sub_1905740(0x7FFFFFFF, 0);
      v43 = Work->randomArray[7];
      v43->index = 7;
      v43->value = sub_1905740(0x7FFFFFFF, 0);
      v45 = Work->randomArray[8];
      v45->index = 8;
      v45->value = sub_1905740(0x7FFFFFFF, 0);
      v47 = Work->randomArray[9];
      v47->index = 9;
      v47->value = sub_1905740(0x7FFFFFFF, 0);
      v49 = Work->randomArray[10];
      v49->index = 10;
      v49->value = sub_1905740(0x7FFFFFFF, 0);
      v51 = Work->randomArray[11];
      v51->index = 11;
      v51->value = sub_1905740(0x7FFFFFFF, 0);
      v53 = Work->randomArray[12];
      v53->index = 12;
      v53->value = sub_1905740(0x7FFFFFFF, 0);
      QsortRandom(&Work->randomArray, 0, 12);
      v7[8] = *(u32 *)((s64)(char *)v3 + 4 * Work->randomArray[0]->index + 32);
      v7[9] = *(u32 *)((s64)(char *)v3 + 4 * Work->randomArray[1]->index + 32);
      v7[10] = *(u32 *)((s64)(char *)v3 + 4 * Work->randomArray[2]->index + 32);
      v7[11] = *(u32 *)((s64)(char *)v3 + 4 * Work->randomArray[3]->index + 32);
      v7[12] = *(u32 *)((s64)(char *)v3 + 4 * Work->randomArray[4]->index + 32);
      v7[13] = *(u32 *)((s64)(char *)v3 + 4 * Work->randomArray[5]->index + 32);
      v7[14] = *(u32 *)((s64)(char *)v3 + 4 * Work->randomArray[6]->index + 32);
      v7[15] = *(u32 *)((s64)(char *)v3 + 4 * Work->randomArray[7]->index + 32);
      v7[16] = *(u32 *)((s64)(char *)v3 + 4 * Work->randomArray[8]->index + 32);
      v7[17] = *(u32 *)((s64)(char *)v3 + 4 * Work->randomArray[9]->index + 32);
      v7[18] = *(u32 *)((s64)(char *)v3 + 4 * Work->randomArray[10]->index + 32);
      v7[19] = *(u32 *)((s64)(char *)v3 + 4 * Work->randomArray[11]->index + 32);
      if ((u32)v6 <= 1)
        v6 = 1;
      else
        v6 = (u32)v6;
      v57 = (s64)(char *)v3 + 4 * Work->randomArray[12]->index;
      v58 = v7 + 8;
      v7[20] = *(u32 *)(v57 + 32);
      while (1)
      {
        v61 = *v58++;
        v60 = v61;
        v62 = player;
        if (player->tehaiNum != 13)
        {
          v62 = player;
          Work_local = Work;
          --Work_local->yama34[v60];
          --Work_local->yamaNum;
          ++v62->tehai34[v60];
          ++v62->tehaiNum;
        }
        if (!--v6)
        {
          v62->aim[6] = 2;
          return;
        }
      }
    }
  }
}

// 0x1d34f60
static void SwapRandom(Random_t *x, Random_t *y) {
  s32 index;
  s32 value;
  Random_t *v7;
  s32 v8;
  s32 v9;
  Random_t *v10;
  s32 v11;
  s32 v12;
  Random_t *v13;

  index = x->index;
  value = x->value;
  v7 = Allocate(Random_t);
  _ctor(v7, index, value, 0);
  v8 = y->index;
  v9 = y->value;
  v10 = Allocate(Random_t);
  _ctor(v10, v8, v9, 0);
  x = v10;
  v11 = v7->index;
  v12 = v7->value;
  v13 = Allocate(Random_t);
  _ctor(v13, v11, v12, 0);
  y = v13;
}

// 0x1d34d90
static void QsortRandom(Random_t **data, s32 firstIndex, s32 lastIndex) {
  s32 v4;
  s64 v7;
  Random_t *v10;
  s32 v11;
  Il2CppClass **v12;
  s32 v13;
  s32 name_high;
  Il2CppClass **v15;
  s64 v16;
  char *v17;
  s64 v18;
  s64 v19;
  Il2CppClass **v20;
  s32 v21;
  s64 v22;
  s64 v25;
  s32 v26;

  v4 = lastIndex;
  v7 = lastIndex;
  while (1)
  {
    if (firstIndex >= SLODWORD(Work->randomArray->max_length))
      return;
    if (firstIndex >= v4)
      break;
    v10 = *data;
    v26 = firstIndex;
    v25 = firstIndex;
    v11 = v4;
    v12 = &(*data)->obj.klass + firstIndex;
    v13 = firstIndex + 1;
    name_high = HIDWORD(v12[4]->_1.name);
    while (1)
    {
      v15 = &v10->obj.klass + v13;
      v16 = v13--;
      v17 = (v15 + 3);
      do
      {
        v19 = *((u64 *)v17 + 1);
        v17 += 8;
        v18 = v19;
        ++v13;
        if (v16 >= v7)
          break;
        ++v16;
      }
      while (*(u32 *)(v18 + 20) < name_high);
      do
      {
        v20 = &v10->obj.klass + v11;
        v21 = v11--;
      }
      while (SHIDWORD(v20[4]->_1.name) > name_high);
      v22 = v21;
      if (v11 + 1 <= v13)
        break;
      SwapRandom(v17, &v10[v22]);
      v10 = *data;
      ++v11;
    }
    SwapRandom(&v10[v25], &v10[v22]);
    QsortRandom(data, v26, v11);
    v4 = lastIndex;
    firstIndex = v11 + 2;
  }
}

// 0x1d04180
static s32 DoraHyoujiToDora(s32 hyouji) {
  s32 v2;
  s32 result;

  v2 = 27;
  switch (hyouji)
  {
    case 8:
    case 17:
    case 26:
      result = hyouji - 8;
      break;
    case 30:
      goto LABEL_6;
    default:
      if (hyouji == 33)
        v2 = 31;
      else
        v2 = hyouji + 1;
LABEL_6:
      result = v2;
      break;
  }
  return result;
}

// 0x1d35050
static void Kandora(void) {
  Work_t *Work_local;
  s32 *dora;
  s64 m_Items;
  s64 v5;
  s64 doraNum;
  s32 v7;
  s32 v8;

  Work_local = Work;
  dora = Work_local->dora;
  m_Items = Work_local->doraHyouji;
  *(u32 *)(m_Items + 4 * Work_local->doraNum) = Work_local->wanpai[8 - 2 * Work_local->doraNum];
  v5 = (s64)Work_local->visibleHai + 4 * *(s32 *)(m_Items + 4 * Work_local->doraNum);
  ++*(u32 *)(v5 + 32);
  doraNum = Work_local->doraNum;
  v7 = *(u32 *)(m_Items + 4 * doraNum);
  v8 = 27;
  switch (v7)
  {
    case 8:
    case 17:
    case 26:
      v8 = v7 - 8;
      break;
    case 30:
      break;
    default:
      if (v7 == 33)
        v8 = 31;
      else
        v8 = v7 + 1;
      break;
  }
  dora[doraNum] = v8;
  ++Work_local->doraNum;
}

// 0x1d35150
static void SetYama(void) {
  s32 *v2;
  s64 i;
  s64 v5;
  Work_t *Work_local;
  s64 yamaNum;
  u32 *v;
  u32 v13;
  u32 v14;
  s32 v15;
  s32 v16;
  s32 v17;
  s32 v18;
  s64 v20;
  s32 v21;
  s32 v22;
  s32 v23;
  s64 j;
  s64 v25;
  s64 v26;
  Work_t *v27;
  s64 k;
  s32 *dora;
  s32 **p_dora;
  s64 v31;
  Work_t *v32;
  u32 v33;
  s32 v34;
  s32 v35;
  s32 *doraHyouji;
  s32 *v37;
  s32 v38;
  s64 v39;
  s64 v40;
  s32 *uraDoraHyouji;
  s64 v42;
  u32 v43;
  Work_t *v44;
  s32 *uraDora;
  s32 v46;
  s32 *wanpai;
  s32 *yama136;
  u32 v49;
  s32 v50;

  v2 = NewSpecific(s32, 0x88u);
  for (i = 4; ; ++i)
  {
    Work_local = Work;
    yamaNum = Work_local->yamaNum;
    if (i - 4 >= yamaNum)
      break;
    *(u32 *)(*((u64 *)&Work_local->randomArray->obj.klass + i) + 16) = i - 4;
    v = sdfDefaultRandCB->v;
    v13 = v[0];
    v14 = v[2];
    v15 = *(u64 *)v >> 30;
    v16 = *(u64 *)&v[2] >> 31;
    v[2] = v[1];
    v[3] = v14;
    v17 = v16 ^ v15;
    v[0] = v17;
    v[1] = v13;
    if (v17 >= 0)
      v18 = v17;
    else
      v18 = -v17;
    v5 = *((u64 *)&Work->randomArray->obj.klass + i);
    *(u32 *)(v5 + 20) = v18;
  }
  Work_local = Work;
  LODWORD(yamaNum) = Work_local->yamaNum;
  QsortRandom(&Work_local->randomArray, 0, yamaNum - 1);
  v20 = 0;
  v21 = 0;
  v22 = 0;
  goto LABEL_30;
  while (1)
  {
LABEL_30:
    while (1)
    {
      v23 = v21 + v22;
      if (v22 >= Work->yama34[v20])
        break;
      ++v22;
      v2[v23] = v20;
    }
    ++v20;
    v21 += v22;
    if (v20 == 34)
      break;
    v22 = 0;
  }
  for (j = 0; ; ++j)
  {
    v27 = Work;
    if (j >= v27->yamaNum)
      break;
    v27 = Work;
    v25 = (s64)v27->yama136 + 4 * j;
    v26 = (s64)v27->randomArray + 8 * j;
    *(u32 *)(v25 + 32) = *(u32 *)((s64)(char *)v2 + 4 * *(s32 *)(*(u64 *)(v26 + 32) + 16) + 32);
  }
  for (k = 8; ; ++k)
  {
    v32 = Work;
    if (k - 8 >= SLODWORD(v32->uraDora->max_length))
      break;
    if (!v33)
    {
      v32 = Work;
    }
    p_dora = &v32->dora;
    dora = v32->dora;
    v31 = 4 * k;
    *(u32 *)((char *)&p_dora[1]->obj.klass + v31) = -1;
    *(u32 *)((char *)&dora->obj.klass + v31) = -1;
  }
  if (!v33)
  {
    v32 = Work;
  }
  v34 = v32->yamaNum;
  v32->doraNum = 1;
  v35 = *((u32 *)&v32->yama136->obj.monitor + v34);
  v37 = v32->dora;
  doraHyouji = v32->doraHyouji;
  doraHyouji[0] = v35;
  v38 = 27;
  switch (v35)
  {
    case 8:
    case 17:
    case 26:
      v38 = v35 - 8;
      break;
    case 30:
      break;
    default:
      if (v35 == 33)
        v38 = 31;
      else
        v38 = v35 + 1;
      break;
  }
  v37[0] = v38;
  v39 = 8;
  v40 = (s64)v32->visibleHai + 4 * doraHyouji[0];
  ++*(u32 *)(v40 + 32);
  while (1)
  {
    v44 = Work;
    uraDora = v44->uraDora;
    if (v39 - 8 >= SLODWORD(uraDora->max_length))
      break;
    if (!v43)
    {
      v44 = Work;
      uraDora = v44->uraDora;
    }
    uraDoraHyouji = v44->uraDoraHyouji;
    v42 = 4 * v39++;
    *(u32 *)((char *)&uraDora->obj.klass + v42) = -1;
    *(u32 *)((char *)&uraDoraHyouji->obj.klass + v42) = -1;
  }
  if (v43)
  {
    v46 = v44->yamaNum - 14;
    v44->yamaNum = v46;
    yama136 = v44->yama136;
    wanpai = v44->wanpai;
    wanpai[0] = yama136[v46];
  }
  else
  {
    v44 = Work;
    v50 = v44->yamaNum - 14;
    v44->yamaNum = v50;
    if (v49)
    {
      yama136 = v44->yama136;
      wanpai = v44->wanpai;
      wanpai[0] = yama136[v50];
    }
    else
    {
      v44 = Work;
      yama136 = v44->yama136;
      wanpai = v44->wanpai;
      wanpai[0] = yama136[v44->yamaNum];
      v44 = Work;
      yama136 = v44->yama136;
      wanpai = v44->wanpai;
    }
  }
  wanpai[1] = yama136[v44->yamaNum + 1];
  v44 = Work;
  yama136 = v44->yama136;
  wanpai = v44->wanpai;
  wanpai[2] = yama136[v44->yamaNum + 2];
  v44 = Work;
  yama136 = v44->yama136;
  wanpai = v44->wanpai;
  wanpai[3] = yama136[v44->yamaNum + 3];
  v44 = Work;
  yama136 = v44->yama136;
  wanpai = v44->wanpai;
  wanpai[4] = yama136[v44->yamaNum + 4];
  v44 = Work;
  yama136 = v44->yama136;
  wanpai = v44->wanpai;
  wanpai[5] = yama136[v44->yamaNum + 5];
  v44 = Work;
  yama136 = v44->yama136;
  wanpai = v44->wanpai;
  wanpai[6] = yama136[v44->yamaNum + 6];
  v44 = Work;
  yama136 = v44->yama136;
  wanpai = v44->wanpai;
  wanpai[7] = yama136[v44->yamaNum + 7];
  v44 = Work;
  yama136 = v44->yama136;
  wanpai = v44->wanpai;
  wanpai[8] = yama136[v44->yamaNum + 8];
  v44 = Work;
  yama136 = v44->yama136;
  wanpai = v44->wanpai;
  wanpai[9] = yama136[v44->yamaNum + 9];
  v44 = Work;
  yama136 = v44->yama136;
  wanpai = v44->wanpai;
  wanpai[10] = yama136[v44->yamaNum + 10];
  v44 = Work;
  yama136 = v44->yama136;
  wanpai = v44->wanpai;
  wanpai[11] = yama136[v44->yamaNum + 11];
  v44 = Work;
  yama136 = v44->yama136;
  wanpai = v44->wanpai;
  wanpai[12] = yama136[v44->yamaNum + 12];
  v44 = Work;
  yama136 = v44->yama136;
  wanpai = v44->wanpai;
  wanpai[13] = yama136[v44->yamaNum + 13];
  v44 = Work;
  v44->tsumoIndex = 0;
}

// 0x1d358d0
static void SetHaipai(void) {
  s64 v2;
  s32 v3;
  Player_t *v5;
  Work_t *Work_local;
  s64 tsumoIndex;
  s64 v8;
  s64 v9;
  s64 v10;
  s64 v11;
  s64 v12;

  v2 = 0;
  v3 = 1;
  while (2)
  {
    v5 = Work->players[v2];
    if (v5->tehaiNum > 12)
    {
LABEL_8:
      goto LABEL_4;
    }
    do
    {
      while (1)
      {
        if (v5->doraTsumikomiNum >= 1 && v3 == 1)
          break;
        Work_local = Work;
        tsumoIndex = Work_local->tsumoIndex;
        v8 = (s64)Work_local->players + 8 * v2;
        v9 = Work_local->yama136[tsumoIndex];
        Work_local->tsumoIndex = tsumoIndex + 1;
        v10 = *(u64 *)(v8 + 32);
        v11 = *(u64 *)(v10 + 24);
        v12 = *(u64 *)(v10 + 32);
        --Work_local->yamaNum;
        *(u32 *)(v11 + 4 * *(s32 *)(v10 + 16) + 32) = v9;
        ++*(u32 *)(v12 + 4 * v9 + 32);
        Work_local->lastTsumohai = v9;
        ++*(u32 *)(v10 + 16);
        if (v5->tehaiNum >= 13)
          goto LABEL_8;
      }
      v3 = TsumoruDora(v2);
      --v5->doraTsumikomiNum;
    }
    while (v5->tehaiNum < 13);
LABEL_4:
    SetTehai14(v2++);
    if (v2 != 4)
      continue;
    break;
  }
}

// 0x1d2e1e0
static void StartModelPhase(void) {
  if (Work->pAgari->playerIndex)
  {
    ButtonGuideDispOn();
    ButtonGuideDispSet("MJN05", 0, 90);
    butoonGuideAgariFlag = 1;
  }
  Work->phase = 9;
  Work->fDrawAgari = 0;
  Work->modelPhase = 0;
}

// 0x1d2cde0
static void NextKyoku(void) {
  s64 v1;
  s64 v2;
  dds3ModelHandle_t *v4;
  Il2CppClass **v5;
  dds3ModelHandle_t *haiModelYama;
  il2cpp_array_size_t v7;
  dds3ModelHandle_t *v9;
  Player_t *v12;
  Player_t *players;

  v1 = 0;
  v2 = 0;
  goto LABEL_9;
  while (1)
  {
    while (1)
    {
LABEL_9:
      haiModelYama = Work->haiModelYama;
      v7 = v2 + haiModelYama->bounds[1].length * v1;
      if (haiModelYama[v7])
      {
        v9 = haiModelYama[v7];
        Free(v9);
        v4 = Work->haiModelYama;
        v5 = &v4->obj.klass + v2 + v1 * v4->bounds[1].length;
        v5[4] = 0;
      }
      if (++v2 == 34)
        break;
    }
    if (++v1 == 160)
      break;
    v2 = 0;
  }
  if (sBtlExt_ChkMes() == 1)
    goto LABEL_27;
  goto LABEL_21;
  if (players[2]->tensu < 0)
  {
LABEL_48:
    goto LABEL_50;
  }
  players = Work->players;
  if ((players[3]->tensu & 0x80000000) == 0)
  {
    goto LABEL_45;
  }
  goto LABEL_48;
LABEL_27:
  sBtlExt_EndMes();
LABEL_21:
  v12 = Work->players;
  if (v12[0]->tensu < 0 || v12[1]->tensu < 0 || v12[2]->tensu < 0 || v12[3]->tensu < 0)
  {
LABEL_50:
    *(u32 *)(*((u64 *)*((const MethodInfo *)mjn + 2).virtualMethodPointer + 24) + 424) = 11;
    InitEndHanchan();
    return;
  }
LABEL_45:
  if (Work->kyoku == 4)
  {
    goto LABEL_50;
  }
  InitKyoku();
}

// 0x1d301b0
static void InitKyoku(void) {
  s64 v2;
  s64 v3;
  s32 *fShowTehai;
  s32 *haiDrawData;
  HaiDrawData_t *v7;
  s64 i;
  Work_t *v10;
  Player_t *v11;
  s32 *tehai34;
  s32 oya;
  TsumikomiPattern_t *p_tsumikomiPattern;
  s32 v15;
  bool v16;
  s32 v17;
  s32 v18;
  s32 v19;
  s64 v20;
  Work_t *v22;
  Player_t *v23;
  s32 *v24;
  s32 v25;
  TsumikomiPattern_t *v26;
  s32 v27;
  s32 v28;
  s32 v29;
  s32 v30;
  s64 v31;
  Work_t *v33;
  Player_t *v34;
  s32 *v35;
  s32 v36;
  TsumikomiPattern_t *v37;
  s32 v38;
  s32 v39;
  s32 v40;
  s32 v41;
  s64 v42;
  Work_t *v44;
  Player_t *v45;
  s32 *v46;
  s32 v47;
  TsumikomiPattern_t *v48;
  s32 v49;
  s32 v50;
  s32 v51;
  s32 v52;
  s64 v53;
  s64 v54;
  Work_t *v56;
  Work_t *v60;
  s32 v61;

  v2 = 0;
  v3 = 8;
  Work->tehaiCursor = 13;
  Work->fDrawUraDora = 0;
  Work->fDrawAgari = 0;
  Work->nakiAri = 1;
  fShowTehai = Work->fShowTehai;
  Work->chankan = 0;
  *(_OWORD *)fShowTehai = xmmword_3D00E20;
  Work->fRyukyoku = 0;
  Work->agariPlayerIndex = -1;
  Work->hideReachBou = -1;
  while (1)
  {
    haiDrawData = Work->haiDrawData;
    if (v2 >= haiDrawData[6])
      break;
    v7 = Allocate(HaiDrawData_t);
    _ctor(v7, 0);
    if (v7)
      QueryInterface(v7, *(void **)(*(u64 *)haiDrawData + 64));
    *(u64 *)&haiDrawData[v3] = v7;
    ++v2;
    v3 += 2;
  }
  for (i = 32; i != 168; i += 4)
  {
    v10 = Work;
    *(u32 *)((char *)&v10->visibleHai->obj.klass + i) = 0;
  }
  v10 = Work;
  v11 = v10->players[0];
  tehai34 = v11->tehai34;
  *(_OWORD *)&v11->menzen = xmmword_3D06540;
  v11->nakiNum = 0;
  v11->fFuriten = 0;
  v11->tehaiNum = 0;
  *(u64 *)&v11->ichijunme = 1;
  *(u64 *)&tehai34[32] = 0;
  *(_OWORD *)tehai34 = 0u;
  *(_OWORD *)&tehai34[4] = 0u;
  *(_OWORD *)&tehai34[8] = 0u;
  *(_OWORD *)&tehai34[12] = 0u;
  *(_OWORD *)&tehai34[16] = 0u;
  *(_OWORD *)&tehai34[20] = 0u;
  *(_OWORD *)&tehai34[24] = 0u;
  *(_OWORD *)&tehai34[28] = 0u;
  v11->sutehaiIndex = 0;
  if (!(u32)tehai34)
  {
    v10 = Work;
  }
  oya = v10->oya;
  v11->tsumikomiPattern = 0;
  p_tsumikomiPattern = &v11->tsumikomiPattern;
  oya = 4 - oya;
  v15 = oya & 3;
  v17 = -oya;
  v16 = v17 < 0;
  v18 = v17 & 3;
  if (v16)
    v19 = v15;
  else
    v19 = -v18;
  *((u32 *)p_tsumikomiPattern - 14) = v19 + 27;
  v20 = *(p_tsumikomiPattern - 3);
  *(u64 *)(v20 + 32) = 0;
  *(u64 *)(v20 + 40) = 0;
  *(u32 *)(v20 + 56) = 0;
  *(u64 *)(v20 + 48) = 0;
  v22 = Work;
  v23 = v22->players[1];
  v24 = v23->tehai34;
  *(_OWORD *)&v23->menzen = xmmword_3D06540;
  v23->nakiNum = 0;
  *(u64 *)&v23->ichijunme = 1;
  v23->fFuriten = 0;
  v23->tehaiNum = 0;
  *(u64 *)&v24[32] = 0;
  *(_OWORD *)v24 = 0u;
  *(_OWORD *)&v24[4] = 0u;
  *(_OWORD *)&v24[8] = 0u;
  *(_OWORD *)&v24[12] = 0u;
  *(_OWORD *)&v24[16] = 0u;
  *(_OWORD *)&v24[20] = 0u;
  *(_OWORD *)&v24[24] = 0u;
  *(_OWORD *)&v24[28] = 0u;
  v23->sutehaiIndex = 0;
  if (!(u32)v24)
  {
    v22 = Work;
  }
  v25 = v22->oya;
  v23->tsumikomiPattern = 0;
  v26 = &v23->tsumikomiPattern;
  v25 = 5 - v25;
  v27 = v25 & 3;
  v28 = -v25;
  v16 = v28 < 0;
  v29 = v28 & 3;
  if (v16)
    v30 = v27;
  else
    v30 = -v29;
  *((u32 *)v26 - 14) = v30 + 27;
  v31 = *(v26 - 3);
  *(u64 *)(v31 + 32) = 0;
  *(u64 *)(v31 + 40) = 0;
  *(u32 *)(v31 + 56) = 0;
  *(u64 *)(v31 + 48) = 0;
  v33 = Work;
  v34 = v33->players[2];
  v35 = v34->tehai34;
  *(_OWORD *)&v34->menzen = xmmword_3D06540;
  v34->nakiNum = 0;
  *(u64 *)&v34->ichijunme = 1;
  v34->fFuriten = 0;
  v34->tehaiNum = 0;
  *(u64 *)&v35[32] = 0;
  *(_OWORD *)v35 = 0u;
  *(_OWORD *)&v35[4] = 0u;
  *(_OWORD *)&v35[8] = 0u;
  *(_OWORD *)&v35[12] = 0u;
  *(_OWORD *)&v35[16] = 0u;
  *(_OWORD *)&v35[20] = 0u;
  *(_OWORD *)&v35[24] = 0u;
  *(_OWORD *)&v35[28] = 0u;
  v34->sutehaiIndex = 0;
  if (!(u32)v35)
  {
    v33 = Work;
  }
  v36 = v33->oya;
  v34->tsumikomiPattern = 0;
  v37 = &v34->tsumikomiPattern;
  v36 = 6 - v36;
  v38 = v36 & 3;
  v39 = -v36;
  v16 = v39 < 0;
  v40 = v39 & 3;
  if (v16)
    v41 = v38;
  else
    v41 = -v40;
  *((u32 *)v37 - 14) = v41 + 27;
  v42 = *(v37 - 3);
  *(u64 *)(v42 + 32) = 0;
  *(u64 *)(v42 + 40) = 0;
  *(u32 *)(v42 + 56) = 0;
  *(u64 *)(v42 + 48) = 0;
  v44 = Work;
  v45 = v44->players[3];
  v46 = v45->tehai34;
  *(_OWORD *)&v45->menzen = xmmword_3D06540;
  v45->nakiNum = 0;
  *(u64 *)&v45->ichijunme = 1;
  v45->fFuriten = 0;
  v45->tehaiNum = 0;
  *(u64 *)&v46[32] = 0;
  *(_OWORD *)v46 = 0u;
  *(_OWORD *)&v46[4] = 0u;
  *(_OWORD *)&v46[8] = 0u;
  *(_OWORD *)&v46[12] = 0u;
  *(_OWORD *)&v46[16] = 0u;
  *(_OWORD *)&v46[20] = 0u;
  *(_OWORD *)&v46[24] = 0u;
  *(_OWORD *)&v46[28] = 0u;
  v45->sutehaiIndex = 0;
  if (!(u32)v46)
  {
    v44 = Work;
  }
  v47 = v44->oya;
  v45->tsumikomiPattern = 0;
  v48 = &v45->tsumikomiPattern;
  v47 = 7 - v47;
  v49 = v47 & 3;
  v50 = -v47;
  v16 = v50 < 0;
  v51 = v50 & 3;
  if (v16)
    v52 = v49;
  else
    v52 = -v51;
  *((u32 *)v48 - 14) = v52 + 27;
  v53 = *(v48 - 3);
  v54 = 32;
  *(u64 *)(v53 + 32) = 0;
  *(u64 *)(v53 + 40) = 0;
  *(u32 *)(v53 + 56) = 0;
  *(u64 *)(v53 + 48) = 0;
  do
  {
    v56 = Work;
    *(u32 *)((char *)&v56->yama34->obj.klass + v54) = 4;
    v54 += 4;
  }
  while (v54 != 168);
  v56 = Work;
  v56->yamaNum = 136;
  Tsumikomi();
  SetYama();
  SetHaipai();
  InitOyaModel();
  v60 = Work;
  *(u64 *)&v60->phase = 2;
  v61 = v60->oya;
  v60->agariDrawFlag = 0;
  v60->agariCnt = 0;
  v60->turn = v61;
}

// 0x1d35d90
static void EndHanchan(void) {
  *(u32 *)(*((u64 *)*((const MethodInfo *)mjn + 2).virtualMethodPointer + 24) + 424) = 11;
  InitEndHanchan();
}

// 0x1d04c80
static void Shukyoku(s32 renchan) {
  Work_t *Work_local;
  s32 v5;
  bool v6;
  s32 v7;
  s32 v8;
  s32 v9;

  if (renchan)
    return;
  Work_local = Work;
  ++Work_local->kyoku;
  v5 = Work_local->oya + 1;
  v7 = -v5;
  v6 = -v5 < 0;
  v8 = v5 & 3;
  v9 = v7 & 3;
  if (!v6)
    v8 = -v9;
  Work_local->oya = v8;
}

// 0x1d35f60
static void Ryukyoku(void) {
  u32 *v1;
  u32 *v2;
  s32 *v3;
  u32 *v6;
  Player_t *v7;
  u32 *v8;
  s32 v9;
  s32 v10;
  Player_t *v11;
  Player_t *v12;
  Player_t *v13;
  s32 v14;
  s64 v16;
  s32 v17;
  s32 v18;
  s32 v19;
  s32 v20;
  s32 v21;
  Work_t *v23;
  Agari_t *v24;
  Agari_t *pAgari;
  s32 *tensu;
  struct mjn *static_fields;
  Work_t *v30;
  Work_t *v33;
  s32 v34;
  bool v35;
  s32 v36;
  s32 v37;
  s32 v38;

  v1 = NewSpecific(s32, 4u);
  v2 = NewSpecific(s32, 4u);
  v3 = NewSpecific(s32, 4u);
  Work->phase = 8;
  *(u64 *)&v3[0] = 0;
  *(u64 *)&v3[2] = 0;
  v6 = &v3[0];
  v7 = Work->players[0];
  v8 = v2 + 8;
  if (!v7->analysis->shanten)
  {
    v9 = 1;
    goto LABEL_32;
  }
  *v8 = 0;
  v7 = Work->players[0];
  v9 = 0;
  v10 = 0;
  v8 = &v3[0];
  if (v7->reachIndex != -1)
  {
LABEL_32:
    v10 = v9;
    *v8 = 1;
    goto LABEL_12;
  }
LABEL_12:
  v11 = Work->players[1];
  if (!v11->analysis->shanten)
  {
    ++v10;
    v2[9] = 1;
    goto LABEL_18;
  }
  v2[9] = 0;
  v11 = Work->players[1];
  if (v11->reachIndex != -1)
    v3[1] = 1;
LABEL_18:
  v12 = Work->players[2];
  if (!v12->analysis->shanten)
  {
    ++v10;
    v2[10] = 1;
    goto LABEL_24;
  }
  v2[10] = 0;
  v12 = Work->players[2];
  if (v12->reachIndex != -1)
    v3[2] = 1;
LABEL_24:
  v13 = Work->players[3];
  if (v13->analysis->shanten)
  {
    v2[11] = 0;
    v13 = Work->players[3];
    if (v13->reachIndex != -1)
      v3[3] = 1;
    if (!v2[8])
    {
LABEL_39:
      if (!*v6)
        goto LABEL_43;
    }
  }
  else
  {
    ++v10;
    v2[11] = 1;
    if (!v2[8])
      goto LABEL_39;
  }
  Work->fShowTehai[0] = 1;
LABEL_43:
  if (v2[9] || v3[1])
  {
    Work->fShowTehai[1] = 1;
  }
  if (v2[10] || v3[2])
  {
    Work->fShowTehai[2] = 1;
  }
  if (v2[11] || v3[3])
  {
    Work->fShowTehai[3] = 1;
  }
  if (*v6)
  {
    v14 = 0;
    goto LABEL_67;
  }
  if (v3[1])
  {
    v14 = 1;
    goto LABEL_67;
  }
  if (v3[2])
  {
    v14 = 2;
LABEL_67:
    p2sdPlaySE_Vol(4194310, 127);
    ApplyChonbo(v14, 9);
    return;
  }
  if (v3[3])
  {
    v14 = 3;
    goto LABEL_67;
  }
  if ((u32)(v10 - 1) > 2)
  {
    v17 = 0;
    v18 = 0;
  }
  else
  {
    v16 = 4 * (v10 - 1);
    v17 = *(u32 *)((char *)&unk_3E62F28 + v16);
    v18 = *(u32 *)((char *)&unk_3E62F34 + v16);
  }
  if (v2[8])
    v19 = v18;
  else
    v19 = v17;
  v1[8] = v19;
  if (v2[9])
    v20 = v18;
  else
    v20 = v17;
  v1[9] = v20;
  if (v2[10])
    v21 = v18;
  else
    v21 = v17;
  v1[10] = v21;
  if (v2[11])
    v17 = v18;
  v1[11] = v17;
  v23 = Work;
  v24 = v23->agari[0];
  v23->pAgari = v24;
  pAgari = Work->pAgari;
  tensu = pAgari->tensu;
  tensu[0] = v1[8];
  tensu[1] = v1[9];
  tensu[2] = v1[10];
  tensu[3] = v1[11];
  UpdateTensu(pAgari);
  v30 = Work;
  MJN_GUIDEHELP_FLAG = 0;
  LODWORD(static_fields) = v30->honba;
  v30->fDrawAgari = 4;
  v30->honba = (u32)static_fields + 1;
  if (v10)
  {
    p2sdPlaySE_Vol(4194310, 127);
  }
  if (!v2[Work->oya + 8])
  {
    v33 = Work;
    ++v33->kyoku;
    v34 = v33->oya + 1;
    v36 = -v34;
    v35 = -v34 < 0;
    v37 = v34 & 3;
    v38 = v36 & 3;
    if (!v35)
      v37 = -v38;
    v33->oya = v37;
    return;
  }
  return;
}

// 0x1d2fcd0
static void TochuRyukyoku(s32 flag) {
  Work_t *Work_local;
  s32 *v5;
  s32 *fShowTehai;
  Work_t *v8;
  Agari_t *agari;
  Agari_t *v10;
  Work_t *v13;
  s32 *tensu;
  Work_t *v15;
  s32 v16;
  bool v17;
  s32 v18;
  s32 v19;
  s32 v20;

  goto LABEL_3;
LABEL_10:
  Work_local = Work;
  fShowTehai = Work_local->fShowTehai;
  *(u64 *)fShowTehai = 0x100000001LL;
  fShowTehai[2] = 1;
  v5 = &fShowTehai[3];
  goto LABEL_13;
LABEL_3:
  Work_local = Work;
  Work_local->phase = 8;
  if (flag == 7)
    goto LABEL_10;
  if (flag != 4096)
    goto LABEL_14;
  Work_local = Work;
  v5 = &Work_local->fShowTehai[Work_local->turn];
LABEL_13:
  *v5 = 1;
  p2sdPlaySE_Vol(4194310, 127);
LABEL_14:
  v8 = Work;
  agari = v8->agari;
  v8->fDrawAgari = flag;
  v10 = agari[0];
  v8->pAgari = v10;
  v13 = Work;
  tensu = v13->pAgari->tensu;
  *(u64 *)tensu = 0;
  *(u64 *)&tensu[2] = 0;
  MJN_GUIDEHELP_FLAG = 0;
  ++v13->honba;
  v15 = Work;
  ++v15->kyoku;
  v16 = v15->oya + 1;
  v18 = -v16;
  v17 = -v16 < 0;
  v19 = v16 & 3;
  v20 = v18 & 3;
  if (!v17)
    v19 = -v20;
  v15->oya = v19;
}

// 0x1d05c10
static void SetTehai14(s32 playerIndex) {
  s64 v4;
  s32 v5;
  s32 v6;
  s32 v7;
  Player_t *v8;

  v4 = 0;
  v5 = 0;
  v6 = 0;
  goto LABEL_9;
  while (1)
  {
LABEL_9:
    while (1)
    {
      v7 = v5 + v6;
      v8 = Work->players[playerIndex];
      if (v6 >= v8->tehai34[v4])
        break;
      v8 = Work->players[playerIndex];
      ++v6;
      v8->tehai14[v7] = v4;
    }
    ++v4;
    v5 += v6;
    if (v4 == 34)
      break;
    v6 = 0;
  }
}

// 0x1d35ab0
static s32 TsumoruDora(s32 playerIndex) {
  s32 v4;
  s32 tsumoIndex;
  s32 v6;
  s32 *yama136;
  s32 *dora;
  s32 v11;
  Work_t *v13;
  s64 v14;
  s64 v15;
  s64 v16;
  s64 v17;
  s64 v18;
  s64 v19;
  s32 *m_Items;

  v4 = 0;
  while (1)
  {
    if (v4 >= Work->yamaNum + 14)
      break;
    tsumoIndex = Work->tsumoIndex;
    v6 = v4 + tsumoIndex;
    yama136 = Work->yama136;
    ++v4;
    dora = Work->dora;
    if (yama136[v6] == dora[0])
    {
      v19 = v6;
      yama136 = Work->yama136;
      tsumoIndex = Work->tsumoIndex;
      dora = Work->dora;
      m_Items = yama136;
      m_Items[v19] = m_Items[tsumoIndex];
      m_Items[Work->tsumoIndex] = dora[0];
      v11 = 1;
      goto LABEL_14;
    }
  }
  v11 = 0;
LABEL_14:
  v13 = Work;
  v14 = v13->tsumoIndex;
  v15 = (s64)v13->players + 8 * playerIndex;
  v16 = v13->yama136[v14];
  v13->tsumoIndex = v14 + 1;
  v17 = *(u64 *)(v15 + 32);
  --v13->yamaNum;
  v18 = *(u64 *)(v17 + 32);
  *(u32 *)(*(u64 *)(v17 + 24) + 4 * *(s32 *)(v17 + 16) + 32) = v16;
  ++*(u32 *)(v18 + 4 * v16 + 32);
  v13->lastTsumohai = v16;
  ++*(u32 *)(v17 + 16);
  return v11;
}

// 0x1d35cc0
static void Tsumoru(s32 playerIndex) {
  Work_t *Work_local;
  s64 tsumoIndex;
  s64 v6;
  s64 v7;
  s64 v8;
  s64 v9;
  s64 v10;

  Work_local = Work;
  tsumoIndex = Work_local->tsumoIndex;
  v6 = (s64)Work_local->players + 8 * playerIndex;
  v7 = Work_local->yama136[tsumoIndex];
  Work_local->tsumoIndex = tsumoIndex + 1;
  v8 = *(u64 *)(v6 + 32);
  v9 = *(u64 *)(v8 + 24);
  v10 = *(u64 *)(v8 + 32);
  --Work_local->yamaNum;
  *(u32 *)(v9 + 4 * *(s32 *)(v8 + 16) + 32) = v7;
  ++*(u32 *)(v10 + 4 * v7 + 32);
  Work_local->lastTsumohai = v7;
  ++*(u32 *)(v8 + 16);
}

// 0x1d365d0
static void Suteru(s32 playerIndex, s32 haiIndex) {
  s64 v6;
  Player_t *v8;
  s64 sutehaiIndex;
  s32 *tehai34;
  s64 v11;
  char *v12;
  Player_t *v14;
  s32 reachIndex;
  Player_t *v18;

  v6 = playerIndex;
  v8 = Work->players[v6];
  sutehaiIndex = v8->sutehaiIndex;
  tehai34 = v8->tehai34;
  v11 = v8->tehai14[haiIndex];
  v8->sutehaiIndex = sutehaiIndex + 1;
  v8->sutehai[sutehaiIndex] = v11;
  Work->lastSutehai = v11;
  v11 *= 4;
  v12 = (char *)Work->visibleHai + v11;
  --*(s32 *)((char *)tehai34 + v11);
  --v8->tehaiNum;
  ++*((u32 *)v12 + 8);
  SetTehai14(playerIndex);
  v14 = Work->players[v6];
  reachIndex = v14->reachIndex;
  v14->ichijunme = 0;
  if (reachIndex != -1)
  {
    if ((v14->flag & 1) == 0)
      goto LABEL_8;
    goto LABEL_9000;
    if ((Work->players[playerIndex]->flag & 1) == 0)
    {
LABEL_8:
      goto LABEL_9;
    }
LABEL_9000:
  }
  Work->players[playerIndex]->fFuriten = 0;
LABEL_9:
  v18 = Work->players[playerIndex];
  v18->flag &= 0xFFFFFFFC;
  MatiObjCtrl(mjnUImanager, 0, 0);
  p2sdPlaySE_Vol(4194306, 127);
}

// 0x1d367d0
static void PlayerTurn(s32 playerIndex) {
  Player_t *v8;
  Work_t *v11;
  s64 tsumoIndex;
  Player_t *v13;
  s64 v14;
  s32 *tehai34;
  s64 v16;
  TehaiAnalysis_t *v20;
  Work_t *v23;
  Player_t *v24;
  s32 v25;
  Player_t *v26;
  Work_t *v27;
  s32 playerSutehai;
  Work_t *v30;
  Work_t *v31;
  Player_t *v32;
  s64 v33;
  s32 v34;
  Player_t *v36;
  Work_t *v37;
  s32 v40;
  s64 v42;
  s64 v45;
  s64 v48;

  Work->nakiFlag[playerIndex] = 0;
  switch (Work->playerPhase)
  {
    case 0:
      p2sdPlaySE_Vol(4194305, 127);
      v8 = Work->players[playerIndex];
      if (v8->reachIndex == -1)
      {
        v8 = Work->players[playerIndex];
        v8->fFuriten = 0;
LABEL_10:
        goto LABEL_11;
      }
      {
        goto LABEL_10;
      }
LABEL_11:
      v11 = Work;
      tsumoIndex = v11->tsumoIndex;
      v13 = v11->players[playerIndex];
      v14 = v11->yama136[tsumoIndex];
      v11->tsumoIndex = tsumoIndex + 1;
      tehai34 = v13->tehai34;
      v16 = (s64)v13->tehai14 + 4 * v13->tehaiNum;
      --v11->yamaNum;
      *(u32 *)(v16 + 32) = v14;
      ++tehai34[v14];
      v11->lastTsumohai = v14;
      LODWORD(v11) = v13->tehaiNum;
      butoonGuideAgariFlag = 0;
      v13->tehaiNum = (u32)v11 + 1;
      ButtonGuideDispSet("MJN02", 1, 90);
      MJN_GUIDEHELP_FLAG = 1;
      goto LABEL_15;
    case 1:
LABEL_15:
      v20 = SetBestAnalysis(playerIndex);
      if (v20->shanten == -1)
      {
        v31 = Work;
        v31->nakiFlag[playerIndex] |= 1u;
        v32 = v31->players[playerIndex];
        if (v32->menzen)
        {
          v31 = Work;
          v32 = v31->players[playerIndex];
          if (v32->reachIndex == -1)
          {
            v31 = Work;
            if (v31->yamaNum >= 4)
            {
              v31 = Work;
              if (v31->players[playerIndex]->tensu >= 1000)
              {
                v31 = Work;
                v33 = (s64)v31->nakiFlag + 4 * playerIndex;
                v34 = *(u32 *)(v33 + 32) | 2;
                goto LABEL_99;
              }
            }
          }
        }
        goto LABEL_100;
      }
      v23 = Work;
      v24 = v23->players[playerIndex];
      if (v24->reachIndex != -1)
      {
        v23 = Work;
        v24 = v23->players[playerIndex];
        v25 = 2;
        v23->playerSutehai = v24->tehaiNum - 1;
        v23->playerPhase = 4;
        goto LABEL_102;
      }
      if (v20->shanten)
        goto LABEL_60;
      v23 = Work;
      v24 = v23->players[playerIndex];
      if (!v24->menzen)
        goto LABEL_60;
      v23 = Work;
      if (v23->yamaNum < 4)
        goto LABEL_60;
      v23 = Work;
      v36 = v23->players[playerIndex];
      if (v36->tensu < 1000)
      {
LABEL_60:
        v25 = 0;
        goto LABEL_102;
      }
      v23 = Work;
      v36 = v23->players[playerIndex];
      v23->nakiFlag[playerIndex] |= 2u;
      if (v36->reachIndex != -1)
      {
        v23 = Work;
        if (CheckAnkanReach(playerIndex, v23->lastTsumohai))
          goto LABEL_96;
      }
      if (Work->players[playerIndex]->reachIndex != -1)
      {
LABEL_100:
        v25 = 1;
        goto LABEL_102;
      }
      if (CheckAnkan(playerIndex))
      {
LABEL_96:
        v33 = (s64)Work->nakiFlag + 4 * playerIndex;
        v34 = *(u32 *)(v33 + 32) | 4;
LABEL_99:
        *(u32 *)(v33 + 32) = v34;
        goto LABEL_100;
      }
      v25 = 1;
LABEL_102:
      v37 = Work;
      if (v37->players[playerIndex]->reachIndex != -1)
      {
        if (CheckAnkanReach(playerIndex, v37->lastTsumohai))
          goto LABEL_126;
      }
      if (Work->players[playerIndex]->reachIndex == -1)
      {
        if (!CheckAnkan(playerIndex))
        {
          goto LABEL_112;
        }
LABEL_126:
        v25 = 1;
        v45 = (s64)Work->nakiFlag + 4 * playerIndex;
        *(u32 *)(v45 + 32) |= 4u;
LABEL_112:
        v40 = CheckKakan(playerIndex);
        if (v40)
          goto LABEL_113;
        goto LABEL_131;
      }
      goto LABEL_112;
LABEL_113:
      v25 = 1;
      v42 = (s64)Work->nakiFlag + 4 * playerIndex;
      *(u32 *)(v42 + 32) |= 8u;
      if (!CheckKyushu(playerIndex))
        goto LABEL_117;
LABEL_132:
      v48 = (s64)Work->nakiFlag + 4 * playerIndex;
      *(u32 *)(v48 + 32) |= 0x1000u;
LABEL_121:
      NakiWait();
      return;
LABEL_131:
      if (CheckKyushu(playerIndex))
        goto LABEL_132;
LABEL_117:
      if (v25)
      {
        if (v25 == 1)
        {
          goto LABEL_121;
        }
      }
      else
      {
        *(u32 *)(*((u64 *)*((const MethodInfo *)mjn + 2).virtualMethodPointer + 24) + 428) = 2;
        matiChack();
        if (!MJN_GUIDEHELP_FLAG)
        {
          ButtonGuideDispSet("MJN02", 1, 90);
          MJN_GUIDEHELP_FLAG = 1;
        }
        Work->tehaiCursor = Work->players[playerIndex]->tehaiNum
                                                     - 1;
      }
      return;
    case 2:
      if (MJN_GUIDEHELP_FLAG)
        return;
      ButtonGuideDispSet("MJN02", 1, 90);
      MJN_GUIDEHELP_FLAG = 1;
      return;
    case 4:
      v26 = Work->players[playerIndex];
      if (v26->reachIndex != v26->sutehaiIndex)
      {
        v26 = Work->players[playerIndex];
        v26->ippatsu = 0;
      }
      v27 = Work;
      playerSutehai = v27->playerSutehai;
      v27->players[playerIndex]->rinshan = 0;
      Suteru(playerIndex, playerSutehai);
      Work->playerPhase = 5;
      return;
    case 5:
      SetBestAnalysis(0);
      Work->playerPhase = 0;
      v30 = Work;
      v30->waitCount = 0;
      v30->phase = 13;
      return;
    default:
      return;
  }
}

// 0x1d38160
static void AITurn(s32 playerIndex) {
  u32 playerPhase;
  Work_t *v10;
  s64 tsumoIndex;
  s64 v12;
  s64 v13;
  s64 v14;
  s64 v15;
  s32 v17;
  s32 v19;
  s32 v21;
  Player_t *v22;
  s32 sutehaiIndex;
  s32 ichijunme;
  s32 v28;
  Work_t *v30;
  Work_t *v32;
  Work_t *v37;
  Work_t *v40;
  Player_t *v41;
  u32 v42;
  s32 v47;

  playerPhase = Work->playerPhase;
  if (playerPhase > 6)
    return;
  switch (playerPhase)
  {
    case 0u:
      v10 = Work;
      tsumoIndex = v10->tsumoIndex;
      v12 = (s64)v10->players + 8 * playerIndex;
      v13 = v10->yama136[tsumoIndex];
      v10->tsumoIndex = tsumoIndex + 1;
      v14 = *(u64 *)(v12 + 32);
      --v10->yamaNum;
      v15 = *(u64 *)(v14 + 32);
      *(u32 *)(*(u64 *)(v14 + 24) + 4 * *(s32 *)(v14 + 16) + 32) = v13;
      ++*(u32 *)(v15 + 4 * v13 + 32);
      v10->lastTsumohai = v13;
      ++*(u32 *)(v14 + 16);
      v17 = AskKyushu(playerIndex);
      if (v17)
      {
        TochuRyukyoku(4096);
        return;
      }
      v47 = AskAnkan(playerIndex);
      if (v47 == -1)
        goto LABEL_8;
      ApplyAnkanEx(playerIndex, v47);
      return;
    case 1u:
    case 2u:
LABEL_8:
      if (SetBestAnalysis(playerIndex)->shanten == -1)
      {
        if (CheckYakuAri(playerIndex, 1, Work->lastTsumohai))
        {
          MenuWin_agari_cent_SetAgariBarIcon(mjnUImanager, playerIndex, 0);
          v37 = Work;
          v37->fromPlayerIndex = playerIndex;
          v37->agariPlayerIndex = playerIndex;
          v37->phase = 6;
          return;
        }
      }
      v40 = Work;
      v41 = v40->players[playerIndex];
      v41->ippatsu = 0;
      v41->rinshan = 0;
      if (v41->reachIndex != -1)
      {
        if (!v42)
        {
          v41 = Work->players[playerIndex];
        }
        Suteru(playerIndex, v41->tehaiNum - 1);
        SetBestAnalysis(playerIndex);
        v21 = 5;
        goto LABEL_54;
      }
      if (!v42)
      {
        v40 = Work;
      }
      v40->playerPhase = 3;
      if (MJN_GUIDEHELP_FLAG)
      {
        ButtonGuideDispSet("MJN02", 1, 90);
        MJN_GUIDEHELP_FLAG = 0;
      }
      return;
    case 3u:
      v19 = AIChooseSutehai(playerIndex, Work->players[playerIndex]->analysis);
      v21 = 4;
      Work->AIsutehai = v19;
LABEL_54:
      Work->playerPhase = v21;
      return;
    case 4u:
      v22 = Work->players[playerIndex];
      sutehaiIndex = v22->sutehaiIndex;
      ichijunme = v22->ichijunme;
      Suteru(playerIndex, Work->AIsutehai);
      SetBestAnalysis(playerIndex);
      v28 = AskReach(playerIndex);
      if (v28)
      {
        ApplyReachEx(playerIndex, sutehaiIndex, ichijunme);
        v30 = Work;
        v30->turn = playerIndex;
        v30->nextPhase = 3;
      }
      goto LABEL_33;
    case 5u:
      SetBestAnalysis(playerIndex);
LABEL_33:
      Work->playerPhase = 6;
      return;
    case 6u:
      Work->playerPhase = 0;
      v32 = Work;
      v32->waitCount = 0;
      v32->phase = 13;
      return;
    default:
      return;
  }
}

// 0x1d380f0
static void Wait(void) {
  Work->waitCount = 0;
  Work->phase = 13;
}

// 0x1d393e0
void mjnSetTIPSOPEN(bool bo) {
  TIPSOPEN = bo;
}

// 0x1d39450
void mjnTipsDispatch(void) {
  u32 v3;
  s32 phase;
  s32 v6;

  v3 = Work->tipsPhase - 1;
  if (v3 <= 4)
  {
    switch (v3)
    {
      case 0u:
        phase = Work->phase;
        if (phase != 1)
        {
          phase = Work->phase;
          if (phase != 10)
          {
            phase = Work->phase;
            if (phase != 9)
            {
              dds3FadeOut(0, 0, 0, 0x1Eu);
              v6 = 2;
              goto LABEL_46;
            }
          }
        }
        return;
      case 1u:
        if (!dds3FadeCheck())
        {
          MjnTipsMenuSetActive(mjnUImanager, 1, 0);
          SetTipsBack(mjnUImanager, 1, 0);
          v6 = 3;
          goto LABEL_46;
        }
        return;
      case 2u:
        mjnTipsProcessStart();
        v6 = 4;
        goto LABEL_46;
      case 3u:
        goto LABEL_36;
LABEL_50:
        MjnTipsMenuSetActive(mjnUImanager, 0, 0);
        SetTipsBack(mjnUImanager, 0, 0);
        v6 = 5;
LABEL_46:
        Work->tipsPhase = v6;
        return;
LABEL_36:
        if (dds3SearchProcessName("mjntips_calc"))
          return;
        goto LABEL_50;
      case 4u:
        dds3FadeIn(0, 0, 0, 0xFu);
        TIPSOPEN = 0;
        ButtonGuideDispSet("MJN02", 1, 90);
        v6 = 0;
        goto LABEL_46;
      default:
        return;
    }
  }
}

// 0x1d2a850
static void Dispatch(void) {
  s32 phase;
  Work_t *v8;
  s32 v9;
  bool v10;
  s32 v11;
  s32 v12;
  s32 v13;
  s32 oya;
  s32 hideReachBou;
  s32 turn;
  s32 waitCount;
  s32 v22;

  if (!TIPSOPEN)
    goto LABEL_17;
  phase = Work->phase;
  if (phase == 1)
    goto LABEL_17;
  if (phase == 10)
    goto LABEL_17;
  if (phase == 9)
    goto LABEL_17;
  mjnTipsDispatch();
  return;
LABEL_17:
  switch (Work->phase)
  {
    case 0:
      ButtonGuideDispSet("MJN02", 0, 90);
      return;
    case 1:
      ManageSummonPhase();
      return;
    case 2:
      SetBestAnalysis(Work->turn);
      v8 = Work;
      v9 = v8->turn + 1;
      v11 = -v9;
      v10 = -v9 < 0;
      v12 = v9 & 3;
      v13 = v11 & 3;
      if (!v10)
        v12 = -v13;
      oya = v8->oya;
      v8->turn = v12;
      if (v12 == oya)
      {
        v8 = Work;
        v8->phase = 3;
      }
      return;
    case 3:
      hideReachBou = Work->hideReachBou;
      if (hideReachBou != -1)
      {
        hideReachBou = Work->hideReachBou;
        if (hideReachBou != Work->turn)
        {
          Work->hideReachBou = -1;
        }
      }
      turn = Work->turn;
      if (turn)
      {
        turn = Work->turn;
        AITurn(turn);
      }
      else
      {
        PlayerTurn(0);
      }
      return;
    case 4:
      CheckNaki();
      return;
    case 6:
      Agari();
      return;
    case 7:
      dds3SetQuake(20, 0x50u);
      Work->phase = 8;
      return;
    case 9:
      ManageModelPhase();
      return;
    case 0xA:
      GuideDispStop(0);
      ManageCutin();
      return;
    case 0xB:
      MJN_GUIDEHELP_FLAG = 0;
      ManageEndHanchanPhase();
      return;
    case 0xD:
      if (Work->fWaitPhase)
      {
        waitCount = Work->waitCount;
        Work->waitCount = waitCount + 1;
        if (waitCount < 21)
          return;
LABEL_88:
        Work->phase = 4;
        return;
      }
      v22 = Work->waitCount;
      Work->waitCount = v22 + 1;
      if (v22 >= 2)
        goto LABEL_88;
      break;
    default:
      return;
  }
}

// 0x1d2ea40
static void Ignore(void) {
  Work_t *v5;
  s32 *nakiFlag;
  s32 v7;
  s32 *v8;
  Work_t *v9;
  Work_t *v11;
  s32 v12;
  s32 fRyukyoku;
  s32 v14;
  Work_t *v16;
  s32 v17;
  bool v18;
  s32 v19;
  s32 v20;
  s32 v21;

  if ((Work->nakiFlag[0] & 0x10) == 0)
  {
    goto LABEL_5;
  }
  Work->players[0]->fFuriten = 1;
LABEL_5:
  v5 = Work;
  if (v5->fKokushiCheck)
    goto LABEL_15;
  if (v5->fChankanCheck)
    goto LABEL_15;
  goto LABEL_9002;
  if (v5->fChankanCheck)
  {
LABEL_15:
    nakiFlag = v5->nakiFlag;
    if ((nakiFlag[1] & 0x10) != 0)
    {
      v7 = 1;
      goto LABEL_53;
    }
    if ((nakiFlag[2] & 0x10) != 0)
    {
      v7 = 2;
      goto LABEL_53;
    }
    if ((nakiFlag[3] & 0x10) != 0)
    {
      v7 = 3;
LABEL_53:
      ApplyRon(v7, Work->turn);
      return;
    }
LABEL_27:
    mjnAfterConfirmationKan(0);
    v9 = Work;
    *(u64 *)&v9->fKokushiCheck = 0;
    v9->chankan = 0;
    *(u64 *)&v9->phase = 3;
    return;
    if ((v8[2] & 0x10) == 0)
    {
      if ((v8[3] & 0x10) == 0)
        goto LABEL_25;
      goto LABEL_9001;
      if ((Work->nakiFlag[3] & 0x10) == 0)
      {
LABEL_25:
        goto LABEL_27;
      }
LABEL_9001:
      v7 = 3;
      goto LABEL_53;
    }
    v7 = 2;
LABEL_51:
    goto LABEL_53;
  }
LABEL_9002:
  v7 = 1;
  while (1)
  {
    v11 = Work;
    if (v7 >= v11->turn)
      break;
    v12 = AskRon(v7);
    if (v12)
      goto LABEL_51;
    ++v7;
  }
  v11 = Work;
  fRyukyoku = v11->fRyukyoku;
  switch (fRyukyoku)
  {
    case 8:
      v14 = 8;
      goto LABEL_60;
    case 7:
      v14 = 7;
LABEL_60:
      TochuRyukyoku(v14);
      return;
    case 4:
      Ryukyoku();
      return;
  }
  v16 = Work;
  v16->phase = 3;
  v17 = v16->turn + 1;
  v19 = -v17;
  v18 = -v17 < 0;
  v20 = v17 & 3;
  v21 = v19 & 3;
  if (!v18)
    v20 = -v21;
  v16->turn = v20;
}

// 0x1d3c8d0
static void NextTurn(void) {
  s32 v3;
  bool v4;
  s32 v5;
  s32 v6;
  s32 v7;

  Work->phase = 3;
  v3 = Work->turn + 1;
  v5 = -v3;
  v4 = -v3 < 0;
  v6 = v3 & 3;
  v7 = v5 & 3;
  if (!v4)
    v6 = -v7;
  Work->turn = v6;
}

// 0x1d37c00
static void NakiWait(void) {
  s32 *nakiFlag;
  u32 v5;
  Work_t *v6;
  u32 v7;
  Work_t *v8;
  s32 *nakiMenu;
  s32 *v10;
  Work_t *v11;
  Work_t *v12;
  Work_t *v13;
  Work_t *v14;
  Work_t *v15;
  Work_t *v16;
  Work_t *v17;
  Work_t *v18;
  s64 v19;
  char *v20;
  s64 v21;
  s64 v22;
  s64 v23;
  s64 v24;
  s64 v25;
  s64 v26;
  s64 v27;
  s64 v28;

  MJN_GUIDEHELP_FLAG = 0;
  nakiFlag = Work->nakiFlag;
  Work->phase = 5;
  Work->nakiCursor = 0;
  if ((nakiFlag[0] & 0x10) == 0)
  {
    v5 = 0;
    goto LABEL_12;
  }
  v5 = 1;
  Work->nakiMenu[0] = 16;
LABEL_12:
  v6 = Work;
  if ((v6->nakiFlag[0] & 1) == 0)
  {
    goto LABEL_14;
  }
  v6 = Work;
  v19 = (s64)v6->nakiMenu + 4 * v5++;
  *(u32 *)(v19 + 32) = 1;
LABEL_14:
  v7 = v5 + 1;
  v8 = Work;
  nakiMenu = v8->nakiMenu;
  v10 = v8->nakiFlag;
  nakiMenu[v5] = 0;
  if ((v10[0] & 2) != 0)
  {
    nakiMenu = Work->nakiMenu;
    v20 = (char *)nakiMenu + 4 * v7;
    v7 = v5 + 2;
    *((u32 *)v20 + 8) = 2;
LABEL_16:
    v11 = Work;
    if ((v11->nakiFlag[0] & 4) == 0)
      goto LABEL_17;
    goto LABEL_41;
  }
  {
    goto LABEL_16;
  }
  v11 = Work;
  if ((v11->nakiFlag[0] & 4) == 0)
  {
LABEL_17:
    goto LABEL_18;
  }
LABEL_41:
  v11 = Work;
  v21 = (s64)v11->nakiMenu + 4 * v7++;
  *(u32 *)(v21 + 32) = 4;
LABEL_18:
  v12 = Work;
  if ((v12->nakiFlag[0] & 8) == 0)
  {
    goto LABEL_20;
  }
  v12 = Work;
  v22 = (s64)v12->nakiMenu + 4 * v7++;
  *(u32 *)(v22 + 32) = 8;
LABEL_20:
  v13 = Work;
  if ((v13->nakiFlag[0] & 0x20) == 0)
  {
    goto LABEL_22;
  }
  v13 = Work;
  v23 = (s64)v13->nakiMenu + 4 * v7++;
  *(u32 *)(v23 + 32) = 32;
LABEL_22:
  v14 = Work;
  if ((v14->nakiFlag[0] & 0x40) == 0)
  {
    goto LABEL_24;
  }
  v14 = Work;
  v24 = (s64)v14->nakiMenu + 4 * v7++;
  *(u32 *)(v24 + 32) = 64;
LABEL_24:
  v15 = Work;
  if ((v15->nakiFlag[0] & 0x80) != 0)
  {
    v15 = Work;
    v25 = (s64)v15->nakiMenu + 4 * v7++;
    *(u32 *)(v25 + 32) = 268435584;
LABEL_26:
    v16 = Work;
    if ((v16->nakiFlag[0] & 0x100) == 0)
      goto LABEL_27;
    goto LABEL_61;
  }
  {
    goto LABEL_26;
  }
  v16 = Work;
  if ((v16->nakiFlag[0] & 0x100) == 0)
  {
LABEL_27:
    goto LABEL_28;
  }
LABEL_61:
  v16 = Work;
  v26 = (s64)v16->nakiMenu + 4 * v7++;
  *(u32 *)(v26 + 32) = 268435712;
LABEL_28:
  v17 = Work;
  if ((v17->nakiFlag[0] & 0x200) == 0)
  {
    goto LABEL_30;
  }
  v17 = Work;
  v27 = (s64)v17->nakiMenu + 4 * v7++;
  *(u32 *)(v27 + 32) = 268435968;
LABEL_30:
  v18 = Work;
  if ((v18->nakiFlag[0] & 0x1000) == 0)
  {
    goto LABEL_32;
  }
  v18 = Work;
  v28 = (s64)v18->nakiMenu + 4 * v7++;
  *(u32 *)(v28 + 32) = 4096;
LABEL_32:
  Work->nakiMenuNum = v7;
}

// 0x1d3acd0
static void CheckNaki(void) {
  s32 *nakiFlag;
  s32 v6;
  u32 v7;
  s32 yamaNum;
  u32 v9;
  s32 v10;
  Player_t *players;
  s32 lastSutehai;
  Work_t *v13;
  Work_t *v14;
  Work_t *v15;
  Player_t *v16;
  s64 v17;
  s64 v18;
  s32 v19;
  s32 v20;
  s32 v21;
  s32 v22;
  s32 v23;
  s32 v28;
  s32 v29;
  s32 v31;
  u32 v32;
  s32 v34;
  u32 v35;
  s32 v37;
  u32 v39;
  Work_t *v40;
  s32 *v41;
  s32 v42;
  s32 *v43;
  s32 v44;
  s32 *v46;
  s32 v47;
  s32 v49;
  s32 *v50;
  s32 v51;
  s32 *v52;
  s32 v53;
  s32 *v55;
  s32 v56;
  mjn *v58;
  s32 v60;
  u32 v61;
  s32 v63;
  u32 v65;
  Work_t *v66;
  s32 *v67;
  s32 v68;
  s32 *v69;
  s32 v70;
  s32 v72;
  s32 *v73;
  s32 v74;
  s32 *v75;
  s32 v76;
  s32 v80;
  u32 v81;
  s32 v83;
  u32 v85;
  Work_t *v86;
  s32 *v87;
  s32 v88;
  s32 *v89;
  s32 v90;
  s32 v92;
  s32 *v93;
  s32 v94;
  s32 *v95;
  s32 v96;
  s32 v98;
  u32 v99;
  s32 v101;
  u32 v102;
  s32 v103;
  s32 v107;
  s32 v108;
  s32 v110;
  u32 v111;
  s32 v113;
  u32 v114;
  s32 v116;
  u32 v117;
  s32 v119;
  u32 v120;
  s32 v122;
  u32 v123;
  s32 v125;
  u32 v126;
  Work_t *v127;
  s32 *v128;
  s32 v129;
  s32 *v130;
  s32 v131;
  s32 v133;
  Work_t *v134;
  s32 *v135;
  s32 v136;
  s32 *v137;
  s32 v138;
  s32 v140;
  s32 *v141;
  Work_t *v142;
  s32 *v143;
  s32 v144;
  s32 *v145;
  s32 v146;
  s32 *v148;
  s32 v149;
  s32 v151;

  {
    nakiFlag = Work->nakiFlag;
    nakiFlag[0] = 0;
    goto LABEL_6;
  }
  else
  {
    nakiFlag = Work->nakiFlag;
    nakiFlag[0] = 0;
LABEL_6:
    nakiFlag[1] = 0;
    goto LABEL_7;
  }
  nakiFlag = Work->nakiFlag;
  nakiFlag[1] = 0;
LABEL_7:
  nakiFlag[2] = 0;
  nakiFlag[3] = 0;
  if (Work->fKokushiCheck)
  {
    v6 = 0;
LABEL_13:
    ApplyRonNextTurn(v6);
    return;
  }
  if (Work->fChankanCheck)
  {
    if (!v7)
    v6 = 1;
    goto LABEL_13;
  }
  if (v7)
  {
    yamaNum = Work->yamaNum;
    if (yamaNum)
      goto LABEL_27;
LABEL_31:
    if (!v9)
    v10 = 4;
LABEL_34:
    ApplyRonRyukyoku(v10);
    return;
  }
  yamaNum = Work->yamaNum;
  if (!yamaNum)
    goto LABEL_31;
LABEL_27:
  if (!v9)
  {
    if (Work->yamaNum != 66)
      goto LABEL_75;
LABEL_36:
    players = Work->players;
    if (!players[0]->nakiNum)
    {
      players = Work->players;
      if (!players[1]->nakiNum)
      {
        players = Work->players;
        if (!players[2]->nakiNum)
        {
          players = Work->players;
          if (!players[3]->nakiNum)
          {
            players = Work->players;
            lastSutehai = players[0]->sutehai[0];
            if (lastSutehai == Work->lastSutehai)
            {
              v13 = Work;
              players = v13->players;
              lastSutehai = v13->lastSutehai;
              if (players[1]->sutehai[0] == lastSutehai)
              {
                v14 = Work;
                players = v14->players;
                lastSutehai = v14->lastSutehai;
                if (players[2]->sutehai[0] == lastSutehai)
                {
                  v15 = Work;
                  players = v15->players;
                  lastSutehai = v15->lastSutehai;
                  if (players[3]->sutehai[0] == lastSutehai)
                  {
                    lastSutehai = Work->lastSutehai;
                    if (lastSutehai == 27)
                      goto LABEL_324;
                    lastSutehai = Work->lastSutehai;
                    if (lastSutehai == 28)
                      goto LABEL_324;
                    lastSutehai = Work->lastSutehai;
                    if (lastSutehai == 29)
                      goto LABEL_324;
                    lastSutehai = Work->lastSutehai;
                    if (lastSutehai == 30)
                    {
LABEL_324:
                      TochuRyukyoku(6);
                      return;
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
    goto LABEL_75;
  }
  if (yamaNum == 66)
    goto LABEL_36;
LABEL_75:
  v16 = Work->players;
  if (v16[0]->reachIndex != -1)
  {
    v16 = Work->players;
    if (v16[1]->reachIndex != -1)
    {
      v16 = Work->players;
      if (v16[2]->reachIndex != -1)
      {
        v16 = Work->players;
        if (v16[3]->reachIndex != -1)
        {
          v10 = 7;
          goto LABEL_34;
        }
      }
    }
  }
  if (Work->doraNum == 5)
  {
    v17 = 32;
    while (1)
    {
      v18 = *(s64 *)((char *)&Work->players->obj.klass + v17);
      if (*(u32 *)(v18 + 72) != 4)
        goto LABEL_95;
      v19 = *(u32 *)(*(u64 *)(*(u64 *)(v18 + 80) + 32) + 16);
      if (v19 == 4)
        goto LABEL_110;
      if (v19 == 8)
        goto LABEL_110;
      if (*((u32 *)(*(Il2CppClass **)((char *)&Work->players->obj.klass + v17))->_1.declaringType->_1.byval_arg.data + 4) != 64)
        goto LABEL_95;
LABEL_110:
      v20 = *(u32 *)(*(u64 *)&(*(Il2CppClass **)((char *)&Work->players->obj.klass + v17))->_1.declaringType->_1.byval_arg.bits + 16);
      if (v20 != 4)
      {
        if (v20 != 8)
          goto LABEL_117;
        goto LABEL_9000;
        if (*(u32 *)(*(u64 *)&(*(Il2CppClass **)((char *)&Work->players->obj.klass + v17))->_1.declaringType->_1.byval_arg.bits + 16) != 8)
        {
LABEL_117:
          if (*(u32 *)(*(u64 *)&(*(Il2CppClass **)((char *)&Work->players->obj.klass + v17))->_1.declaringType->_1.byval_arg.bits + 16) != 64)
            goto LABEL_95;
        }
LABEL_9000:
      }
      v21 = *((u32 *)(*(Il2CppClass **)((char *)&Work->players->obj.klass + v17))->_1.declaringType->_1.this_arg.data + 4);
      if (v21 == 4)
        goto LABEL_130;
      if (v21 == 8)
        goto LABEL_130;
      if (*((u32 *)(*(Il2CppClass **)((char *)&Work->players->obj.klass + v17))->_1.declaringType->_1.this_arg.data + 4) == 64)
      {
LABEL_130:
        v22 = *(u32 *)(*(u64 *)&(*(Il2CppClass **)((char *)&Work->players->obj.klass + v17))->_1.declaringType->_1.this_arg.bits + 16);
        if (v22 == 4)
          break;
        v22 = *(u32 *)(*(u64 *)&(*(Il2CppClass **)((char *)&Work->players->obj.klass + v17))->_1.declaringType->_1.this_arg.bits + 16);
        if (v22 == 8)
          break;
        if (*(u32 *)(*(u64 *)&(*(Il2CppClass **)((char *)&Work->players->obj.klass + v17))->_1.declaringType->_1.this_arg.bits + 16) == 64)
          break;
      }
LABEL_95:
      v17 += 8;
      if (v17 == 64)
      {
        v10 = 8;
        goto LABEL_34;
      }
    }
  }
  switch (Work->turn)
  {
    case 0:
      v23 = 1;
      if (AskRon(1))
        goto LABEL_325;
      v23 = 2;
      if (AskRon(2))
        goto LABEL_325;
      v23 = 3;
      if (AskRon(3))
      {
LABEL_325:
        v28 = v23;
        v29 = 0;
        goto LABEL_153;
      }
      v103 = 1;
      if (AskPon(1))
        goto LABEL_326;
      v103 = 2;
      if (AskPon(2))
        goto LABEL_326;
      v103 = 3;
      if (AskPon(3))
      {
LABEL_326:
        v107 = v103;
        v108 = 0;
        goto LABEL_247;
      }
      goto LABEL_321;
    case 1:
      v31 = AskRon(2);
      if (v31)
      {
        if (!v32)
        v28 = 2;
LABEL_188:
        v29 = 1;
        goto LABEL_153;
      }
      if (!v32)
      v60 = AskRon(3);
      if (v60)
      {
        if (!v61)
        v28 = 3;
        goto LABEL_188;
      }
      if (!v61)
      v83 = CheckRon(0);
      if (v83)
      {
        v86 = Work;
        v87 = v86->nakiFlag;
        v88 = v87[0] | 0x10;
        v87[0] = v88;
        if (v86->nakiAri)
        {
          v87 = Work->nakiFlag;
          v88 = v87[0];
          v87[0] = CheckPon(0) | v88;
          v89 = Work->nakiFlag;
          v90 = v89[0];
          v92 = CheckMinkan(0) | v90;
          v89[0] = v92;
        }
        v93 = Work->nakiFlag;
        v94 = v93[2];
        v93[2] = AskPon(2) | v94;
LABEL_219:
        v95 = Work->nakiFlag;
        v96 = v95[3];
        v58 = AskPon(3);
        v95[3] = (u32)v58 | v96;
        goto LABEL_181;
      }
      if (!v85)
      v110 = AskPon(2);
      if (v110)
      {
        if (!v111)
        v107 = 2;
LABEL_272:
        v108 = 1;
        goto LABEL_247;
      }
      if (!v111)
      v119 = AskPon(3);
      if (v119)
      {
        if (!v120)
        v107 = 3;
        goto LABEL_272;
      }
      v127 = Work;
      if (v127->nakiAri)
      {
        v127 = Work;
        v128 = v127->nakiFlag;
        v129 = v128[0];
        v128[0] = CheckPon(0) | v129;
        v130 = Work->nakiFlag;
        v131 = v130[0];
        v133 = CheckMinkan(0) | v131;
        v130[0] = v133;
        if (Work->nakiFlag[0])
          goto LABEL_313;
      }
LABEL_317:
      goto LABEL_321;
    case 2:
      v34 = AskRon(3);
      if (v34)
      {
        if (!v35)
        v28 = 3;
        v29 = 2;
        goto LABEL_153;
      }
      if (!v35)
      v63 = CheckRon(0);
      if (v63)
      {
        v66 = Work;
        v67 = v66->nakiFlag;
        v68 = v67[0] | 0x10;
        v67[0] = v68;
        if (v66->nakiAri)
        {
          v67 = Work->nakiFlag;
          v68 = v67[0];
          v67[0] = CheckPon(0) | v68;
          v69 = Work->nakiFlag;
          v70 = v69[0];
          v72 = CheckMinkan(0) | v70;
          v69[0] = v72;
        }
        v73 = Work->nakiFlag;
        v74 = v73[1];
        v73[1] = AskRon(1) | v74;
        v75 = Work->nakiFlag;
        v76 = v75[1];
        v75[1] = AskPon(1) | v76;
        goto LABEL_219;
      }
      if (!v65)
      v98 = AskRon(1);
      if (v98)
      {
        if (!v99)
        v28 = 1;
        v29 = 2;
        goto LABEL_153;
      }
      if (!v99)
      v113 = AskPon(1);
      if (v113)
      {
        if (!v114)
        v107 = 1;
        v108 = 2;
        goto LABEL_247;
      }
      if (!v114)
      v122 = AskPon(3);
      if (v122)
      {
        if (!v123)
        v107 = 3;
        v108 = 2;
        goto LABEL_247;
      }
      v134 = Work;
      if (!v134->nakiAri)
        goto LABEL_317;
      v134 = Work;
      v135 = v134->nakiFlag;
      v136 = v135[0];
      v135[0] = CheckPon(0) | v136;
      v137 = Work->nakiFlag;
      v138 = v137[0];
      v140 = CheckMinkan(0) | v138;
      v137[0] = v140;
      v141 = Work->nakiFlag;
      if (!v141[0])
        goto LABEL_317;
      v141 = Work->nakiFlag;
      v141[0] |= 0x20u;
      goto LABEL_181;
    case 3:
      v37 = CheckRon(0);
      if (v37)
      {
        v40 = Work;
        v41 = v40->nakiFlag;
        v42 = v41[0] | 0x10;
        v41[0] = v42;
        if (v40->nakiAri)
        {
          v41 = Work->nakiFlag;
          v42 = v41[0];
          v41[0] = CheckPon(0) | v42;
          v43 = Work->nakiFlag;
          v44 = v43[0];
          v43[0] = CheckMinkan(0) | v44;
          v46 = Work->nakiFlag;
          v47 = v46[0];
          v49 = CheckChi(0) | v47;
          v46[0] = v49;
        }
        v50 = Work->nakiFlag;
        v51 = v50[1];
        v50[1] = AskRon(1) | v51;
        v52 = Work->nakiFlag;
        v53 = v52[1];
        v52[1] = AskPon(1) | v53;
        v55 = Work->nakiFlag;
        v56 = v55[2];
        v58 = AskPon(2);
        v55[2] = (u32)v58 | v56;
        goto LABEL_181;
      }
      if (!v39)
      v80 = AskRon(1);
      if (v80)
      {
        if (!v81)
        v28 = 1;
        v29 = 3;
LABEL_153:
        ApplyRon(v28, v29);
        return;
      }
      if (!v81)
      v101 = AskRon(2);
      if (v101)
      {
        if (!v102)
        v28 = 2;
        v29 = 3;
        goto LABEL_153;
      }
      if (!v102)
      v116 = AskPon(1);
      if (v116)
      {
        if (!v117)
        v107 = 1;
        v108 = 3;
LABEL_247:
        ApplyPon(v107, v108);
        return;
      }
      if (!v117)
      v125 = AskPon(2);
      if (v125)
      {
        if (!v126)
        v107 = 2;
        v108 = 3;
        goto LABEL_247;
      }
      v142 = Work;
      if (v142->nakiAri)
      {
        v142 = Work;
        v143 = v142->nakiFlag;
        v144 = v143[0];
        v143[0] = CheckPon(0) | v144;
        v145 = Work->nakiFlag;
        v146 = v145[0];
        v145[0] = CheckChi(0) | v146;
        v148 = Work->nakiFlag;
        v149 = v148[0];
        v151 = CheckMinkan(0) | v149;
        v148[0] = v151;
        if (Work->nakiFlag[0])
        {
LABEL_313:
LABEL_181:
          NakiWait();
          return;
        }
      }
LABEL_321:
      NextTurn();
      break;
    default:
      return;
  }
}

// 0x1d3c950
static void ApplyRonNextTurn(s32 flag) {
  mjn *v3;
  s32 v6;
  s32 v9;
  u32 v10;
  s32 v11;
  s32 v13;
  s32 v15;
  s32 v16;
  Work_t *v17;
  s32 v19;
  s32 v21;
  u32 v22;
  s32 v23;
  s32 v25;
  Work_t *v27;
  Player_t *v28;
  s64 v29;
  s32 v31;
  u32 v33;
  s32 *v34;
  s32 v35;
  Work_t *v37;
  Player_t *v38;
  s64 v39;
  s32 v41;
  u32 v43;
  s32 *v44;
  s32 v45;
  s32 *v46;
  s32 v49;
  s32 v51;
  s32 turn;
  s32 v54;
  Player_t *v57;
  s64 lastSutehai;
  s32 v60;
  u32 v62;
  s32 *v63;
  s32 v64;
  Work_t *v66;
  Player_t *v67;
  s64 v68;
  s32 v70;
  u32 v72;
  s32 *v73;
  s32 v74;
  s32 *v75;
  s32 v78;
  s32 v79;
  s32 v81;
  s32 v84;
  s32 v86;
  s32 v87;
  s32 v88;
  s32 *nakiFlag;
  s32 v90;

  if (!flag)
  {
    switch (Work->turn)
    {
      case 0:
        v13 = AskRonKokushi(1);
        if (v13)
          goto LABEL_108;
        v15 = AskRonKokushi(2);
        if (v15)
          goto LABEL_66;
        if (!v10)
        v11 = AskRonKokushi(3);
LABEL_29:
        v16 = v11;
        if (!v16)
          goto LABEL_33;
        goto LABEL_101;
      case 1:
        v49 = AskRonKokushi(2);
        if (v49)
        {
LABEL_66:
          if (v10)
            goto LABEL_68;
          goto LABEL_67;
        }
        if (!v10)
        v81 = AskRonKokushi(3);
        if (v81)
        {
LABEL_99:
LABEL_101:
          v51 = 3;
          turn = Work->turn;
          goto LABEL_69;
        }
        if (!v22)
        v23 = CheckRonKokushi(0);
LABEL_129:
        v88 = v23;
        if (v88)
        {
          nakiFlag = Work->nakiFlag;
          nakiFlag[0] |= 0x10u;
          goto LABEL_55;
        }
        goto LABEL_33;
      case 2:
        v54 = AskRonKokushi(3);
        if (v54)
          goto LABEL_99;
        if (v22)
        {
          goto LABEL_75;
        }
        else
        {
LABEL_75:
          goto LABEL_76;
        }
LABEL_76:
        v57 = Work->players[0];
        lastSutehai = Work->lastSutehai;
        ++v57->tehai34[lastSutehai];
        v60 = CheckAgariKokushi(0);
        --v57->tehai34[lastSutehai];
        if (v60)
        {
          v63 = Work->nakiFlag;
          v64 = v63[1];
          v63[0] |= 0x10u;
          v3 = AskRonKokushi(1);
          v63[1] = (u32)v3 | v64;
LABEL_55:
          NakiWait();
          return;
        }
        if (!v62)
        v86 = AskRonKokushi(1);
LABEL_123:
        v87 = v86;
        if (!v87)
          goto LABEL_33;
        goto LABEL_110;
      case 3:
        v66 = Work;
        v67 = v66->players[0];
        v68 = v66->lastSutehai;
        ++v67->tehai34[v68];
        v70 = CheckAgariKokushi(0);
        --v67->tehai34[v68];
        if (v70)
        {
          v73 = Work->nakiFlag;
          v74 = v73[1];
          v73[0] |= 0x10u;
          v73[1] = AskRonKokushi(1) | v74;
          v75 = Work->nakiFlag;
          LODWORD(v73) = v75[2];
          v3 = AskRonKokushi(2);
          v75[2] = (u32)v3 | (u32)v73;
          goto LABEL_55;
        }
        if (!v72)
        v84 = AskRonKokushi(1);
        if (!v84)
        {
          v79 = AskRonKokushi(2);
          goto LABEL_136;
        }
LABEL_108:
LABEL_110:
        v51 = 1;
        turn = Work->turn;
LABEL_69:
        ApplyRon(v51, turn);
        return;
      default:
        goto LABEL_33;
    }
  }
  if (flag != 1)
  {
    goto LABEL_33;
  }
  switch (Work->turn)
  {
    case 0:
      v6 = AskRon(1);
      if (v6)
        goto LABEL_108;
      v9 = AskRon(2);
      if (v9)
        goto LABEL_66;
      if (!v10)
      v11 = AskRon(3);
      goto LABEL_29;
    case 1:
      v19 = AskRon(2);
      if (v19)
        goto LABEL_66;
      if (!v10)
      v21 = AskRon(3);
      if (v21)
        goto LABEL_99;
      if (!v22)
      v23 = CheckRon(0);
      goto LABEL_129;
    case 2:
      v25 = AskRon(3);
      if (v25)
        goto LABEL_99;
      if (v22)
      {
        goto LABEL_50;
      }
      else
      {
LABEL_50:
        goto LABEL_51;
      }
LABEL_51:
      v27 = Work;
      v28 = v27->players[0];
      v29 = v27->lastSutehai;
      ++v28->tehai34[v29];
      v31 = CheckAgari(0);
      --v28->tehai34[v29];
      if (v31)
      {
        v34 = Work->nakiFlag;
        v35 = v34[1];
        v34[0] |= 0x10u;
        v3 = AskRon(1);
        v34[1] = (u32)v3 | v35;
        goto LABEL_55;
      }
      if (!v33)
      v86 = AskRon(1);
      goto LABEL_123;
    case 3:
      v37 = Work;
      v38 = v37->players[0];
      v39 = v37->lastSutehai;
      ++v38->tehai34[v39];
      v41 = CheckAgari(0);
      --v38->tehai34[v39];
      if (v41)
      {
        v44 = Work->nakiFlag;
        v45 = v44[1];
        v44[0] |= 0x10u;
        v44[1] = AskRon(1) | v45;
        v46 = Work->nakiFlag;
        LODWORD(v44) = v46[2];
        v3 = AskRon(2);
        v46[2] = (u32)v3 | (u32)v44;
        goto LABEL_55;
      }
      if (!v43)
      v78 = AskRon(1);
      if (v78)
        goto LABEL_108;
      v79 = AskRon(2);
      break;
    default:
      goto LABEL_33;
  }
LABEL_136:
  v90 = v79;
  if (v90)
  {
LABEL_67:
LABEL_68:
    v51 = 2;
    turn = Work->turn;
    goto LABEL_69;
  }
LABEL_33:
  mjnAfterConfirmationKan(Work->turn);
  v17 = Work;
  *(u64 *)&v17->fKokushiCheck = 0;
  v17->chankan = 0;
  *(u64 *)&v17->phase = 3;
}

// 0x1d3d1f0
static void ApplyRonRyukyoku(s32 flag) {
  Player_t *v6;
  s64 lastSutehai;
  s32 v8;
  s32 *nakiFlag;
  s32 v10;
  s32 *v11;
  s32 v12;
  s32 *v14;
  s32 v15;
  s32 v19;
  s32 v21;
  s32 turn;
  s32 v25;

  if (!Work->turn)
  {
LABEL_14:
    if (Work->turn == 1)
    {
LABEL_28:
      if (Work->turn != 2)
      {
        v25 = AskRon(2);
        if (v25)
        {
          v21 = 2;
          turn = Work->turn;
          goto LABEL_26;
        }
      }
      if (Work->turn == 3)
      {
LABEL_48:
        if (flag == 4)
        {
          Ryukyoku();
        }
        else
        {
          TochuRyukyoku(flag);
        }
        return;
      }
      if (!AskRon(3))
        goto LABEL_48;
      v21 = 3;
      turn = Work->turn;
LABEL_26:
      ApplyRon(v21, turn);
      return;
    }
    v19 = AskRon(1);
    if (!v19)
      goto LABEL_28;
    v21 = 1;
    turn = Work->turn;
    goto LABEL_26;
  }
  v6 = Work->players[0];
  lastSutehai = Work->lastSutehai;
  ++v6->tehai34[lastSutehai];
  v8 = CheckAgari(0);
  --v6->tehai34[lastSutehai];
  if (!v8)
    goto LABEL_14;
  nakiFlag = Work->nakiFlag;
  v10 = nakiFlag[1];
  nakiFlag[0] |= 0x10u;
  nakiFlag[1] = AskRon(1) | v10;
  v11 = Work->nakiFlag;
  v12 = v11[2];
  v11[2] = AskRon(2) | v12;
  v14 = Work->nakiFlag;
  v15 = v14[3];
  v17 = AskRon(3);
  v14[3] = (u32)v17 | v15;
  Work->fRyukyoku = flag;
  NakiWait();
}

// 0x1d3d8f0
static s32 CheckPon(s32 playerIndex) {
  Player_t *v5;
  s32 *tehai34;

  v5 = Work->players[playerIndex];
  if (v5->reachIndex != -1)
    return 0;
  tehai34 = v5->tehai34;
  return 32 * (tehai34[Work->lastSutehai] > 1);
}

// 0x1d37410
static s32 CheckAnkan(s32 playerIndex) {
  s32 *tehai34;

  if (!Work->yamaNum)
    return 0;
  if (Work->doraNum == 5)
    return 0;
  tehai34 = Work->players[playerIndex]->tehai34;
  if (tehai34[0] == 4)
    return 4;
  if (tehai34[1] == 4)
    return 4;
  if (tehai34[2] == 4)
    return 4;
  if (tehai34[3] == 4)
    return 4;
  if (tehai34[4] == 4)
    return 4;
  if (tehai34[5] == 4)
    return 4;
  if (tehai34[6] == 4)
    return 4;
  if (tehai34[7] == 4)
    return 4;
  if (tehai34[8] == 4)
    return 4;
  if (tehai34[9] == 4)
    return 4;
  if (tehai34[10] == 4)
    return 4;
  if (tehai34[11] == 4)
    return 4;
  if (tehai34[12] == 4)
    return 4;
  if (tehai34[13] == 4)
    return 4;
  if (tehai34[14] == 4)
    return 4;
  if (tehai34[15] == 4)
    return 4;
  if (tehai34[16] == 4)
    return 4;
  if (tehai34[17] == 4)
    return 4;
  if (tehai34[18] == 4)
    return 4;
  if (tehai34[19] == 4)
    return 4;
  if (tehai34[20] == 4)
    return 4;
  if (tehai34[21] == 4)
    return 4;
  if (tehai34[22] == 4)
    return 4;
  if (tehai34[23] == 4)
    return 4;
  if (tehai34[24] == 4)
    return 4;
  if (tehai34[25] == 4)
    return 4;
  if (tehai34[26] == 4)
    return 4;
  if (tehai34[27] == 4)
    return 4;
  if (tehai34[28] == 4)
    return 4;
  if (tehai34[29] == 4)
    return 4;
  if (tehai34[30] == 4)
    return 4;
  if (tehai34[31] == 4)
    return 4;
  if (tehai34[32] == 4)
    return 4;
  return 4 * (tehai34[33] == 4);
}

// 0x1d371c0
static s32 CheckAnkanReach(s32 playerIndex, s32 tsumoHai) {
  Player_t *v7;
  s64 i;
  NormalAnalysis_t *v9;
  Work_t *v10;
  s64 shuntsuNum;
  s64 m_Items;
  s64 v13;
  s64 tatsuNum;
  s64 v15;

  if (!Work->yamaNum)
    return 0;
  if (Work->doraNum != 5)
  {
    v7 = Work->players[playerIndex];
    if (v7->tehai34[tsumoHai] != 4 || v7->analysis->shanten == -1)
      return 0;
    for (i = 0; ; ++i)
    {
      v10 = Work;
      if (i >= v10->analysisIndex)
        return 4;
      v9 = v10->analysis[i];
      if (v9->shanten)
        continue;
      shuntsuNum = (u32)v9->shuntsuNum;
      if ((s32)shuntsuNum >= 1)
      {
        m_Items = v9->shuntsuHai;
        do
        {
          v13 = *(u64 *)m_Items;
          if (*(u32 *)(*(u64 *)m_Items + 32) == tsumoHai || *(u32 *)(v13 + 36) == tsumoHai || *(u32 *)(v13 + 40) == tsumoHai)
          {
            return 0;
          }
          m_Items += 8;
        }
        while (--shuntsuNum);
      }
      if (v9->fuyouNum != 1 || v9->fuyouHai[0] == tsumoHai)
      {
        tatsuNum = (u32)v9->tatsuNum;
        if ((s32)tatsuNum >= 1)
        {
          v15 = v9->tatsuHai;
          while (*(u32 *)(*(u64 *)v15 + 32) != tsumoHai && *(u32 *)(*(u64 *)v15 + 36) != tsumoHai)
          {
            v15 += 8;
            if (!--tatsuNum)
              goto LABEL_17;
          }
          return 0;
        }
      }
LABEL_17:
      ;
    }
  }
  return 0;
}

// 0x1d37950
static s32 CheckKakan(s32 playerIndex) {
  Player_t *v5;
  s64 nakiNum;
  s64 i;

  if (!Work->yamaNum)
    return 0;
  if (Work->doraNum == 5)
    return 0;
  v5 = Work->players[playerIndex];
  nakiNum = (u32)v5->nakiNum;
  if ((s32)nakiNum < 1)
    return 0;
  for (i = v5->naki; *(u32 *)(*(u64 *)i + 16) != 32 || !v5->tehai34[*(s32 *)(*(u64 *)(*(u64 *)i + 24) + 32)]; i += 8)
  {
    if (!--nakiNum)
      return 0;
  }
  return 8;
}

// 0x1d3db10
static s32 CheckChi(s32 playerIndex) {
  Player_t *v5;
  s64 lastSutehai;
  bool v7;
  bool v8;
  s32 *tehai34;
  s64 v11;
  s32 v12;
  s64 v13;
  s32 *Chi_Sav_C;
  s64 v15;
  u32 *v16;
  s32 v17;
  s32 *v18;
  s32 v20;
  s64 v21;
  s32 v22;
  s64 v23;

  v5 = Work->players[playerIndex];
  if (v5->reachIndex != -1)
    return 0;
  lastSutehai = (u32)Work->lastSutehai;
  v7 = (u32)lastSutehai >= 0x1A;
  v8 = (u32)lastSutehai == 26;
  if ((s32)lastSutehai > 26)
    return 0;
  tehai34 = v5->tehai34;
  if (v8 || !v7)
  {
    switch ((s32)lastSutehai)
    {
      case 0:
      case 9:
      case 18:
        v11 = (s64)tehai34 + 4 * lastSutehai;
        if (!*(u32 *)(v11 + 36) || !*(u32 *)(v11 + 40))
          return 0;
        mjnSetChi_L(lastSutehai);
        return 268435968;
      case 1:
      case 10:
      case 19:
        v13 = (s64)&tehai34->obj.klass + 4 * lastSutehai + 4;
        if (tehai34[(u32)(lastSutehai - 1)] && *(u32 *)(v13 + 32))
        {
          Chi_Sav_C = Work->Chi_Sav_C;
          Chi_Sav_C[0] = lastSutehai - 1;
          Chi_Sav_C[1] = lastSutehai;
          Chi_Sav_C[2] = lastSutehai + 1;
          v12 = 268435712;
          goto LABEL_37;
        }
        v12 = 0;
LABEL_37:
        if (!*(u32 *)(v13 + 32) || !tehai34[lastSutehai + 2])
          return v12;
        goto LABEL_63;
      case 2:
      case 3:
      case 4:
      case 5:
      case 6:
      case 11:
      case 12:
      case 13:
      case 14:
      case 15:
      case 20:
      case 21:
      case 22:
      case 23:
      case 24:
        goto LABEL_48;
      case 7:
      case 16:
      case 25:
        v15 = (s64)tehai34 + 4 * (u32)(lastSutehai - 1);
        v17 = *(u32 *)(v15 + 32);
        v16 = (v15 + 32);
        if (v17 && tehai34[lastSutehai + 1])
        {
          v18 = Work->Chi_Sav_C;
          v18[0] = lastSutehai - 1;
          v18[1] = lastSutehai;
          v18[2] = lastSutehai + 1;
          v12 = 268435712;
          goto LABEL_43;
        }
        v12 = 0;
LABEL_43:
        if (!tehai34[(u32)(lastSutehai - 2)] || !*v16)
          return v12;
        mjnSetChi_R(lastSutehai);
        v20 = 268435584;
        break;
      case 8:
      case 17:
      case 26:
        if (!tehai34[(u32)(lastSutehai - 1)] || !tehai34[(u32)(lastSutehai - 2)])
          return 0;
        v12 = 268435584;
        mjnSetChi_R(lastSutehai);
        return v12;
      default:
        return 0;
    }
    return v12 | v20;
  }
LABEL_48:
  v21 = (s64)tehai34 + 4 * (s32)lastSutehai - 4;
  if (tehai34[(s32)lastSutehai - 2] && *(u32 *)(v21 + 32))
  {
    mjnSetChi_R(lastSutehai);
    v12 = 268435584;
  }
  else
  {
    v12 = 0;
  }
  v22 = *(u32 *)(v21 + 32);
  v23 = (s64)&tehai34->obj.klass + 4 * (s32)lastSutehai + 4;
  if (v22 && *(u32 *)(v23 + 32))
  {
    mjnSetChi_C(lastSutehai);
    v12 |= 0x10000100u;
  }
  if (*(u32 *)(v23 + 32) && tehai34[(s32)lastSutehai + 2])
  {
LABEL_63:
    mjnSetChi_L(lastSutehai);
    v20 = 268435968;
    return v12 | v20;
  }
  return v12;
}

// 0x1d3e1a0
void mjnSetChi_R(s32 hai) {
  int32x2_t *Chi_Sav_R;

  Chi_Sav_R = Work->Chi_Sav_R;
  Chi_Sav_R[5].n64_u32[0] = hai;
  Chi_Sav_R[4].n64_u64[0] = vadd_s32(vdup_n_s32(hai), (int32x2_t)-2).n64_u64[0];
}

// 0x1d3e230
void mjnSetChi_C(s32 hai) {
  s32 *Chi_Sav_C;

  Chi_Sav_C = Work->Chi_Sav_C;
  Chi_Sav_C[0] = hai - 1;
  Chi_Sav_C[1] = hai;
  Chi_Sav_C[2] = hai + 1;
}

// 0x1d3e110
void mjnSetChi_L(s32 hai) {
  s32 *Chi_Sav_L;

  Chi_Sav_L = Work->Chi_Sav_L;
  Chi_Sav_L[0] = hai;
  *(int32x2_t *)&Chi_Sav_L[1] = vadd_s32(vdup_n_s32(hai), (int32x2_t)0x200000001LL);
}

// 0x1d3d9c0
static s32 CheckMinkan(s32 playerIndex) {
  Player_t *v5;
  s32 *tehai34;

  if (!Work->yamaNum)
    return 0;
  v5 = Work->players[playerIndex];
  if (Work->doraNum == 5)
    return 0;
  if (v5->reachIndex != -1)
    return 0;
  tehai34 = v5->tehai34;
  return (tehai34[Work->lastSutehai] == 3) << 6;
}

// 0x1d3d830
static s32 CheckRon(s32 playerIndex) {
  s64 lastSutehai;
  Player_t *v6;
  s32 result;

  lastSutehai = Work->lastSutehai;
  v6 = Work->players[playerIndex];
  ++v6->tehai34[lastSutehai];
  result = 16 * (CheckAgari(playerIndex) != 0);
  --v6->tehai34[lastSutehai];
  return result;
}

// 0x1d3e050
static s32 CheckRonKokushi(s32 playerIndex) {
  s64 lastSutehai;
  Player_t *v6;
  s32 result;

  lastSutehai = Work->lastSutehai;
  v6 = Work->players[playerIndex];
  ++v6->tehai34[lastSutehai];
  result = 16 * (CheckAgariKokushi(playerIndex) != 0);
  --v6->tehai34[lastSutehai];
  return result;
}

// 0x1d37ac0
static s32 CheckKyushu(s32 playerIndex) {
  Player_t *v4;
  s32 *tehai34;
  s32 v6;
  bool v7;
  int32x4_t v8;
  _BOOL4 v9;
  s32 v10;
  int32x4_t v11;
  s32 v12;
  s32 v13;
  s32 v14;
  int16x8_t v15;
  uint8x8_t v16;
  u32 v17;

  v4 = Work->players[playerIndex];
  if (!v4->ichijunme)
    return 0;
  tehai34 = v4->tehai34;
  v6 = tehai34[0];
  v7 = v6 == 0;
  v8 = vceqzq_s32(*(int32x4_t *)&tehai34[27]);
  v9 = v6 != 0;
  if (v7)
    v10 = 1;
  else
    v10 = 2;
  if (tehai34[8])
    v9 = v10;
  v11.n128_u32[2] = tehai34[18];
  v11.n128_u32[3] = tehai34[26];
  v11.n128_u32[1] = tehai34[17];
  v11.n128_u32[0] = tehai34[9];
  v12 = tehai34[31];
  v13 = tehai34[32];
  v14 = tehai34[33] != 0;
  v15 = vbicq_s8((int8x16_t)xmmword_3D045F0, vuzp1q_s16(vceqzq_s32(v11), v8));
  v15.n128_u32[0] = (u8)vaddvq_s16(v15);
  v16.n64_u64[0] = vcnt_s8((int8x8_t)v15.n128_u64[0]).n64_u64[0];
  v16.n64_u16[0] = vaddlv_u8(v16);
  v17 = v16.n64_u32[0];
  if (v12)
    v17 = v16.n64_u32[0] + 1;
  if (v13)
    ++v14;
  return (v17 + v14 + v9 > 8) << 12;
}

// 0x1d13c90
static s32 CheckRon_Reach(s32 _hai, Player_t *_player) {
  s32 *v5;
  s64 tehaiNum;
  s64 v8;
  s32 *tehai14;
  s64 v10;
  s32 v11;
  int32x4_t v12;
  int32x4_t v13;
  int32x4_t *v14;
  s64 v15;
  int32x4_t v16;
  int32x4_t v17;
  int32x4_t v18;
  int32x4_t v19;
  int32x4_t v20;
  int32x4_t v21;
  int32x4_t v22;
  char *v23;
  s64 v24;
  s32 *v25;
  s32 v26;
  s64 nakiNum;
  Naki_t *m_Items;
  u32 v29;
  bool v30;
  s64 v31;
  Naki_t *v33;
  s32 *v34;
  u32 v35;
  s64 v36;
  u32 v38;
  s64 v39;
  s64 v41;
  s32 *v42;
  s64 v43;
  char *v44;
  s64 v46;
  s32 v49;
  Agari_t *v51;
  s32 v52;
  Player_t *v53;
  s32 ichijunme;
  s32 v55;
  s64 i;
  Work_t *Work_local;
  NormalAnalysis_t *v63;
  u32 v64;
  Work_t *v65;
  s64 agariIndex;
  s64 v67;
  s32 *yaku;
  s32 v74;
  bool v75;
  s64 v76;
  s32 *v77;
  s64 v78;
  s64 v79;
  s32 v80;

  v5 = NewSpecific(s32, 0xEu);
  tehaiNum = (u32)player->tehaiNum;
  v8 = v5;
  if ((s32)tehaiNum < 1)
  {
    v11 = 0;
    goto LABEL_14;
  }
  tehai14 = player->tehai14;
  if ((u32)tehaiNum >= 0x10)
  {
    v12 = vdupq_n_s32(hai);
    v13 = 0u;
    v10 = (u32)tehaiNum & 0xFFFFFFF0;
    v14 = &tehai14[12];
    v15 = v10;
    v16 = 0u;
    v17 = 0u;
    v18 = 0u;
    do
    {
      v15 -= 16;
      v19 = vceqq_s32(v14[-2], v12);
      v20 = vceqq_s32(v14[-3], v12);
      v21 = vceqq_s32(v14[-1], v12);
      v22 = vceqq_s32(*v14, v12);
      v14 += 4;
      v16 = vsubq_s32(v16, v19);
      v18 = vsubq_s32(v18, v22);
      v13 = vsubq_s32(v13, v20);
      v17 = vsubq_s32(v17, v21);
    }
    while (v15);
    v11 = vaddvq_s32(vaddq_s32(vaddq_s32(v18, v17), vaddq_s32(v16, v13)));
    if (v10 == tehaiNum)
      goto LABEL_14;
  }
  else
  {
    v10 = 0;
    v11 = 0;
  }
  v23 = (char *)tehai14 + 4 * v10;
  v24 = tehaiNum - v10;
  v25 = (v23 + 32);
  do
  {
    v26 = *v25++;
    if (v26 == hai)
      ++v11;
    --v24;
  }
  while (v24);
LABEL_14:
  nakiNum = (u32)player->nakiNum;
  if ((s32)nakiNum >= 1)
  {
    m_Items = player->naki;
    do
    {
      v33 = m_Items;
      v34 = m_Items->hai;
      if (v34[0] == hai)
      {
        v29 = v33->type - 4;
        v30 = v29 > 0x3C;
        v31 = (1 << v29) & 0x1000000000000011LL;
        if (!v30 && v31 != 0)
          goto LABEL_20;
        ++v11;
        if (v34[1] != hai)
          goto LABEL_31;
      }
      else if (v34[1] != hai)
      {
        goto LABEL_31;
      }
      v35 = v33->type - 4;
      v30 = v35 > 0x3C;
      v36 = (1 << v35) & 0x1000000000000011LL;
      if (!v30 && v36 != 0)
        goto LABEL_20;
      ++v11;
LABEL_31:
      if (v34[2] != hai)
        goto LABEL_21;
      v38 = v33->type - 4;
      v30 = v38 > 0x3C;
      v39 = (1 << v38) & 0x1000000000000011LL;
      if (v30 || v39 == 0)
      {
        ++v11;
        goto LABEL_21;
      }
LABEL_20:
      v11 += 4;
LABEL_21:
      ++m_Items;
      --nakiNum;
    }
    while (nakiNum);
  }
  if (v11 > 3)
    return 0;
  if ((s32)tehaiNum >= 1)
  {
    v41 = 0;
    v42 = player->tehai14;
    do
    {
      v43 = v41++;
      *(u32 *)((s64)&v5[0] + v43 * 4) = v42[v43];
    }
    while (v41 < player->tehaiNum);
  }
  v44 = (char *)player->tehai34 + 4 * hai;
  ++*((u32 *)v44 + 8);
  ++player->tehaiNum;
  v46 = hai;
  SetTehai14(0);
  v49 = CheckAgari(0);
  Work->attentionFlag = 0;
  if (v49)
  {
    v51 = 0;
    v52 = 0;
    v79 = v8;
    v80 = 0;
    while (1)
    {
      v53 = Work->players[0];
      ichijunme = v53->ichijunme;
      v53->ichijunme = 0;
      v55 = v52 != 0;
      AnalyzeTehaiNormal(0);
      AnalyzeTehaiChitoi(0);
      AnalyzeTehaiKokushi(0);
      for (i = 4; ; ++i)
      {
        Work_local = Work;
        if (i - 4 >= Work_local->analysisIndex)
          break;
        v63 = *((NormalAnalysis_t *)&Work_local->analysis->obj.klass + i);
        if (v63->shanten != -1)
          continue;
        if (v64)
        v65 = Work;
        agariIndex = v65->agariIndex;
        v67 = (s64)v65->agari + 8 * agariIndex;
        v65->agariIndex = agariIndex + 1;
        v51 = *(Agari_t *)(v67 + 32);
        v51->tsumo = v55;
        v51->playerIndex = 0;
        if (v64)
        {
          v51->fromPlayerIndex = v65->turn;
        }
        else
        {
          v51->fromPlayerIndex = Work->turn;
        }
        v51->fu = CalcFu(0, v63, v55, hai);
        CalcYaku(0, v63, v51, v55, hai);
        CalcTensu(0, v51, v55);
      }
        if (Work_local->chitoiAnalysis->shanten != -1)
          goto LABEL_78;
        v51 = CalcAgariChack(0, 0, 1, v52 != 0, hai);
LABEL_79:
        if (Work->kokushiAnalysis->shanten != -1)
          goto LABEL_80;
        v51 = CalcAgariChack(0, 0, 2, v52 != 0, hai);
LABEL_81:
        Work->players[0]->ichijunme = ichijunme;
        if (!v51)
          goto LABEL_92;
LABEL_97:
        yaku = v51->yaku;
        if (v51->yakuNum == yaku[11])
          goto LABEL_101;
        if (!yaku[0]
&& !yaku[1]
&& !yaku[2]
&& !yaku[3]
&& !yaku[4]
&& !yaku[6]
&& !yaku[7]
&& !yaku[8]
&& !yaku[9]
&& !yaku[10]
&& !yaku[12]
&& !yaku[13]
&& !yaku[14]
&& !yaku[15]
&& !yaku[16]
&& !yaku[17]
&& !yaku[18]
&& !yaku[19]
&& !yaku[20]
&& !yaku[21]
&& !yaku[22]
&& !yaku[23]
&& !yaku[24]
&& !yaku[25]
&& !yaku[26]
&& !yaku[27]
&& !yaku[28]
&& !yaku[29]
&& !yaku[30]
&& !yaku[31]
&& !yaku[32]
          && !yaku[33]
          && !yaku[34]
          && !yaku[35]
          && !yaku[36]
          && !yaku[37]
          && !yaku[38])
        {
LABEL_101:
          ++v80;
          goto LABEL_46;
        }
      goto LABEL_9001;
LABEL_78:
      goto LABEL_79;
LABEL_80:
      goto LABEL_81;
LABEL_92:
      v51 = ChooseAgari((s32)mjn);
      if (v51)
        goto LABEL_97;
LABEL_46:
      Work->attentionFlag = 2;
LABEL_9001:
      if (++v52 == 2)
      {
        v8 = v79;
        v46 = hai;
        if (v80 == 1)
        {
          Work->attentionFlag = 3;
        }
        break;
      }
    }
  }
  --player->tehai34[v46];
  v74 = player->tehaiNum - 1;
  v75 = player->tehaiNum - 2 < 0;
  player->tehaiNum = v74;
  if (v75 == __OFSUB__(v74, 1))
  {
    v76 = 0;
    v77 = player->tehai14;
    do
    {
      v78 = v76++;
      v77[v78] = *(u32 *)(v8 + 32 + v78 * 4);
    }
    while (v76 < player->tehaiNum);
  }
  return 16 * (v49 != 0);
}

// 0x1d391f0
static s32 AskReach(s32 playerIndex) {
  Player_t *v5;
  TehaiAnalysis_t *analysis;

  v5 = Work->players[playerIndex];
  analysis = v5->analysis;
  if (analysis->shanten || !v5->menzen)
    return 0;
  return Work->yamaNum >= 4
      && v5->reachIndex == -1
      && analysis->fAllowReach
      && v5->tensu > 999;
}

// 0x1d39170
static s32 AskTsumo(s32 playerIndex) {
  return CheckYakuAri(playerIndex, 1, Work->lastTsumohai) != 0;
}

// 0x1d3c760
static s32 AskRon(s32 playerIndex) {
  Player_t *v4;
  s64 lastSutehai;
  Player_t *v7;
  s32 result;

  v4 = Work->players[playerIndex];
  lastSutehai = Work->lastSutehai;
  v7 = Work->players[playerIndex];
  ++v7->tehai34[lastSutehai];
  result = CheckAgari(playerIndex);
  --v7->tehai34[lastSutehai];
  if (!result)
    return result;
  if (!CheckFuriten(playerIndex))
    goto LABEL_14;
LABEL_17:
  v4->fFuriten = 1;
  return 0;
LABEL_14:
  result = CheckYakuAri(playerIndex, 0, Work->lastSutehai);
  if (result != 1)
    goto LABEL_17;
  return result;
}

// 0x1d3df00
static s32 AskRonKokushi(s32 playerIndex) {
  Player_t *v4;
  s64 lastSutehai;
  Player_t *v7;
  s32 result;

  v4 = Work->players[playerIndex];
  lastSutehai = Work->lastSutehai;
  v7 = Work->players[playerIndex];
  ++v7->tehai34[lastSutehai];
  result = CheckAgariKokushi(playerIndex);
  --v7->tehai34[lastSutehai];
  if (result)
  {
    if (CheckFuriten(playerIndex))
    {
      result = 0;
      v4->fFuriten = 1;
      return result;
    }
    return 16;
  }
  return result;
}

// 0x1d3d600
static s32 AskPon(s32 playerIndex) {
  Player_t *v5;
  s32 result;
  s64 lastSutehai;
  s32 v8;
  TehaiAnalysis_t *analysis;
  NormalAnalysis_t *normalAnalysis;
  Work_t *v12;
  Player_t *v13;
  s32 v14;
  s64 toitsuNum;
  s64 i;

  v5 = Work->players[playerIndex];
  if (v5->reachIndex != -1)
    return 0;
  if (v5->aim[6])
    return 0;
  lastSutehai = Work->lastSutehai;
  v8 = v5->tehai34[lastSutehai];
  if (v8 < 2)
    return 0;
  analysis = v5->analysis;
  normalAnalysis = analysis->normalAnalysis;
  if (!analysis->shanten && v5->tehaiNum != 4)
    return 0;
  if (v8 != 2)
    goto LABEL_29;
  goto LABEL_14;
LABEL_15:
  if ((s32)lastSutehai < 27)
    goto LABEL_29;
  if ((u32)lastSutehai > 0x1E)
    return 32;
  v12 = Work;
  v13 = v12->players[playerIndex];
  v12 = Work;
  if (v13->kaze == (u32)lastSutehai)
    return 32;
  v14 = v12->kyoku <= 3 ? 27 : 28;
  if (v14 == (u32)lastSutehai)
    return 32;
  goto LABEL_29;
LABEL_14:
  goto LABEL_15;
LABEL_29:
  if (!v5->menzen)
  {
    toitsuNum = (u32)normalAnalysis->toitsuNum;
    if ((s32)toitsuNum >= 2)
    {
      for (i = normalAnalysis->toitsuHai; *(u32 *)(*(u64 *)i + 32) != (u32)lastSutehai; i += 8)
      {
        result = 0;
        if (!--toitsuNum)
          return result;
      }
      return 32;
    }
  }
  return 0;
}

// 0x1d3d810
static s32 AskMinkan(s32 playerIndex) {
  return 0;
}

// 0x1d3d820
static s32 AskChi(s32 playerIndex) {
  return 0;
}

// 0x1d389c0
static s32 AskAnkan(s32 playerIndex) {
  Player_t *v8;
  s32 *tehai34;

  if (!CheckAnkan(playerIndex))
    return -1;
  v8 = Work->players[playerIndex];
  if (v8->reachIndex != -1)
    return -1;
  if (!v8->analysis->shanten)
    return -1;
  v8 = Work->players[playerIndex];
  if (!!v8->aim[6])
    return -1;
  v8 = Work->players[playerIndex];
  if (v8->reachIndex == -1)
  {
    tehai34 = v8->tehai34;
    if (tehai34[0] == 4)
    {
      return 0;
    }
    else if (tehai34[1] == 4)
    {
      return 1;
    }
    else if (tehai34[2] == 4)
    {
      return 2;
    }
    else if (tehai34[3] == 4)
    {
      return 3;
    }
    else if (tehai34[4] == 4)
    {
      return 4;
    }
    else if (tehai34[5] == 4)
    {
      return 5;
    }
    else if (tehai34[6] == 4)
    {
      return 6;
    }
    else if (tehai34[7] == 4)
    {
      return 7;
    }
    else if (tehai34[8] == 4)
    {
      return 8;
    }
    else if (tehai34[9] == 4)
    {
      return 9;
    }
    else if (tehai34[10] == 4)
    {
      return 10;
    }
    else if (tehai34[11] == 4)
    {
      return 11;
    }
    else if (tehai34[12] == 4)
    {
      return 12;
    }
    else if (tehai34[13] == 4)
    {
      return 13;
    }
    else if (tehai34[14] == 4)
    {
      return 14;
    }
    else if (tehai34[15] == 4)
    {
      return 15;
    }
    else if (tehai34[16] == 4)
    {
      return 16;
    }
    else if (tehai34[17] == 4)
    {
      return 17;
    }
    else if (tehai34[18] == 4)
    {
      return 18;
    }
    else if (tehai34[19] == 4)
    {
      return 19;
    }
    else if (tehai34[20] == 4)
    {
      return 20;
    }
    else if (tehai34[21] == 4)
    {
      return 21;
    }
    else if (tehai34[22] == 4)
    {
      return 22;
    }
    else if (tehai34[23] == 4)
    {
      return 23;
    }
    else if (tehai34[24] == 4)
    {
      return 24;
    }
    else if (tehai34[25] == 4)
    {
      return 25;
    }
    else if (tehai34[26] == 4)
    {
      return 26;
    }
    else if (tehai34[27] == 4)
    {
      return 27;
    }
    else if (tehai34[28] == 4)
    {
      return 28;
    }
    else if (tehai34[29] == 4)
    {
      return 29;
    }
    else if (tehai34[30] == 4)
    {
      return 30;
    }
    else if (tehai34[31] == 4)
    {
      return 31;
    }
    else if (tehai34[32] == 4)
    {
      return 32;
    }
    else if (tehai34[33] == 4)
    {
      return 33;
    }
    else
    {
      return -1;
    }
  }
  else
  {
    if (!CheckAnkanReach(playerIndex, Work->lastTsumohai))
      return -1;
    return Work->lastTsumohai;
  }
}

// 0x1d38830
static s32 AskKyushu(s32 playerIndex) {
  s32 result;
  Player_t *v7;
  s32 *tehai34;
  s32 v9;
  bool v10;
  int32x4_t v11;
  _BOOL4 v12;
  s32 v13;
  int32x4_t v14;
  s32 v15;
  s32 v16;
  s32 v17;
  int16x8_t v18;
  uint8x8_t v19;
  u32 v20;

  result = CheckKyushu(playerIndex);
  if (!result)
    return result;
  v7 = Work->players[playerIndex];
  if (v7->aim[6])
    return 0;
  tehai34 = v7->tehai34;
  v9 = tehai34[0];
  v10 = v9 == 0;
  v11 = vceqzq_s32(*(int32x4_t *)&tehai34[27]);
  v12 = v9 != 0;
  if (v10)
    v13 = 1;
  else
    v13 = 2;
  if (tehai34[8])
    v12 = v13;
  v14.n128_u32[2] = tehai34[18];
  v14.n128_u32[3] = tehai34[26];
  v14.n128_u32[1] = tehai34[17];
  v14.n128_u32[0] = tehai34[9];
  v15 = tehai34[31];
  v16 = tehai34[32];
  v17 = tehai34[33] != 0;
  v18 = vbicq_s8((int8x16_t)xmmword_3D045F0, vuzp1q_s16(vceqzq_s32(v14), v11));
  v18.n128_u32[0] = (u8)vaddvq_s16(v18);
  v19.n64_u64[0] = vcnt_s8((int8x8_t)v18.n128_u64[0]).n64_u64[0];
  v19.n64_u16[0] = vaddlv_u8(v19);
  v20 = v19.n64_u32[0];
  if (v15)
    v20 = v19.n64_u32[0] + 1;
  if (v16)
    ++v17;
  return (v20 + v17 + v12 < 0xB) << 12;
}

// 0x1d3bfa0
static void Agari(void) {
  s32 agariPlayerIndex;
  s32 fromPlayerIndex;
  s32 v9;
  s32 v10;
  u32 v14;
  s32 v15;
  s32 v17;

  agariPlayerIndex = Work->agariPlayerIndex;
  fromPlayerIndex = Work->fromPlayerIndex;
  if (agariPlayerIndex == fromPlayerIndex)
  {
    ApplyAgari(agariPlayerIndex, agariPlayerIndex);
    v9 = agariPlayerIndex;
    v10 = 0;
LABEL_19:
    v15 = 8;
    goto LABEL_14;
  }
  v17 = CheckFuriten(agariPlayerIndex);
  if (!v17)
  {
    if (!v14)
    ApplyAgari(agariPlayerIndex, fromPlayerIndex);
    v9 = agariPlayerIndex;
    v10 = 1;
    goto LABEL_19;
  }
  if (!v14)
  ApplyChonbo(agariPlayerIndex, 2);
  v9 = agariPlayerIndex;
  v10 = 1;
  v15 = 7;
LABEL_14:
  StartCutin(v9, v10, v15, 0, 0);
}

// 0x1d2ee00
static void ApplyTsumo(s32 playerIndex) {
  MenuWin_agari_cent_SetAgariBarIcon(mjnUImanager, playerIndex, 0);
  Work->fromPlayerIndex = playerIndex;
  Work->agariPlayerIndex = playerIndex;
  Work->phase = 6;
}

// 0x1d2eee0
static void ApplyReach(s32 playerIndex) {
  Player_t *v6;
  s32 flag;
  s32 reachBou;
  s32 phase;

  v6 = Work->players[playerIndex];
  flag = v6->flag;
  v6->tensu -= 1000;
  v6->reachIndex = v6->sutehaiIndex;
  v6->ippatsu = 1;
  v6->flag = flag | 1;
  if (v6->ichijunme)
    v6->doubleReach = 1;
  reachBou = Work->reachBou;
  phase = Work->phase;
  Work->hideReachBou = playerIndex;
  Work->reachBou = reachBou + 1;
  StartCutin(playerIndex, 7, phase, 2, 0);
  p2sdPlaySE_Vol(4194308, 127);
}

// 0x1d392e0
static void ApplyReachEx(s32 playerIndex, s32 sutehaiIndex, s32 ichijunme) {
  Player_t *v10;
  s32 tensu;
  s32 reachBou;
  s32 phase;

  v10 = Work->players[playerIndex];
  tensu = v10->tensu;
  v10->reachIndex = sutehaiIndex;
  v10->ippatsu = 1;
  v10->tensu = tensu - 1000;
  v10->flag |= 1u;
  if (ichijunme)
    v10->doubleReach = 1;
  reachBou = Work->reachBou;
  phase = Work->phase;
  Work->hideReachBou = playerIndex;
  Work->reachBou = reachBou + 1;
  StartCutin(playerIndex, 7, phase, 0, 0);
  p2sdPlaySE_Vol(4194308, 127);
}

// 0x1d2e330
static void ApplyAnkanEx(s32 playerIndex, s32 hai) {
  Player_t *v6;
  Naki_t *v7;
  s32 *v9;
  s64 v10;
  s32 *visibleHai;
  Work_t *v15;

  v6 = Work->players[playerIndex];
  p2sdPlaySE_Vol(4194309, 127);
  v7 = v6->naki[v6->nakiNum];
  v7->type = 4;
  v7->fromPlayerIndex = playerIndex;
  v9 = v7->hai;
  v10 = hai;
  Work->lastSutehai = hai;
  visibleHai = Work->visibleHai;
  v9[0] = hai;
  v9[1] = hai;
  v9[2] = hai;
  v6->tehai34[v10] -= 4;
  v6->tehaiNum -= 4;
  ++v6->nakiNum;
  visibleHai[v10] += 4;
  SetTehai14(playerIndex);
  if (!playerIndex)
  {
    Work->tehaiCursor = v6->tehaiNum - 1;
  }
  v15 = Work;
  v15->turn = playerIndex;
  *(u64 *)&v15->phase = 3;
  StartCutin(playerIndex, 6, 4, 4, 0);
}

// 0x1d390e0
static void ApplyAnkanAI(s32 playerIndex, s32 hai) {
  s32 v6;
  s32 v7;

  v6 = playerIndex;
  v7 = hai;
  ApplyAnkanEx(v6, v7);
}

// 0x1d2efe0
static void ApplyAnkanPlayer(s32 playerIndex) {
  s64 v5;
  Player_t *players;
  Player_t *v8;
  Work_t *v9;
  s32 lastTsumohai;
  s32 v12;
  u32 v13;
  Work_t *v14;

  v5 = 0;
  players = Work->players;
  Work->kanNum = 0;
  v8 = players[playerIndex];
  do
  {
    if (v8->tehai34[v5] == 4)
    {
      v9 = Work;
      v9->kanHai[v9->kanNum++] = v5;
    }
    ++v5;
  }
  while (v5 != 34);
  if (v8->reachIndex != -1)
  {
    lastTsumohai = Work->lastTsumohai;
    v12 = playerIndex;
LABEL_15:
    ApplyAnkanEx(v12, lastTsumohai);
    return;
  }
  v14 = Work;
  if (v14->kanNum == 1)
  {
    if (!v13)
    {
      v14 = Work;
    }
    lastTsumohai = v14->kanHai[0];
    v12 = playerIndex;
    goto LABEL_15;
  }
  if (!v13)
  {
    v14 = Work;
  }
  v14->nakiFlag[0] = 4;
  v14->phase = 12;
  mjnTehaiCursorSet();
}

// 0x1d2e4b0
static void ApplyKakanEx(s32 playerIndex, s32 hai) {
  Player_t *players;
  Player_t *v8;
  s64 nakiNum;
  Naki_t *naki;
  s64 v11;
  s32 v12;
  Naki_t *v13;
  s64 v14;
  s64 v15;
  Work_t *v18;

  players = Work->players;
  Work->lastSutehai = hai;
  v8 = players[playerIndex];
  Work->chankan = 1;
  nakiNum = (u32)v8->nakiNum;
  naki = v8->naki;
  if ((s32)nakiNum < 1)
  {
    v12 = -1;
  }
  else
  {
    v11 = 0;
    v12 = -1;
    do
    {
      v13 = naki[v11];
      if (v13->type == 32 && v13->hai[0] == hai)
        v12 = v11;
      ++v11;
    }
    while (nakiNum != v11);
  }
  naki[v12]->type = 8;
  v14 = (s64)v8->tehai34 + 4 * hai;
  --*(u32 *)(v14 + 32);
  --v8->tehaiNum;
  v15 = (s64)Work->visibleHai + 4 * hai;
  ++*(u32 *)(v15 + 32);
  SetTehai14(playerIndex);
  if (!playerIndex)
  {
    Work->tehaiCursor = v8->tehaiNum - 1;
  }
  v18 = Work;
  v18->turn = playerIndex;
  *(u64 *)&v18->phase = 3;
  StartCutin(playerIndex, 6, 4, 8, 0);
  p2sdPlaySE_Vol(4194309, 127);
}

// 0x1d2f190
static void ApplyKakan(s32 playerIndex) {
  Player_t *players;
  Player_t *v7;
  s32 nakiNum;
  Naki_t *naki;
  s64 v10;
  Work_t *v11;
  s64 v12;
  s64 v13;
  Work_t *v15;

  players = Work->players;
  Work->kanNum = 0;
  v7 = players[playerIndex];
  nakiNum = v7->nakiNum;
  if (nakiNum >= 1)
  {
    naki = v7->naki;
    v10 = 4;
    do
    {
      v13 = *((u64 *)&naki->obj.klass + v10);
      if (*(u32 *)(v13 + 16) == 32 && v7->tehai34[*(s32 *)(*(u64 *)(v13 + 24) + 32)])
      {
        naki = v7->naki;
        v11 = Work;
        v11->kanHai[v11->kanNum++] = *(u32 *)(*(u64 *)(*((u64 *)&naki->obj.klass + v10) + 24) + 32);
        nakiNum = v7->nakiNum;
      }
      v12 = v10 - 3;
      ++v10;
    }
    while (v12 < nakiNum);
  }
  v15 = Work;
  if (v15->kanNum == 1)
  {
    v15 = Work;
    ApplyKakanEx(playerIndex, v15->kanHai[0]);
    return;
  }
  v15 = Work;
  v15->nakiFlag[0] = 8;
  v15->phase = 12;
  v15->tehaiCursor = v15->players[0]->tehaiNum - 1;
}

// 0x1d2f450
static void ApplyPon(s32 playerIndex, s32 fromPlayerIndex) {
  Player_t *players;
  s64 lastSutehai;
  Player_t *v9;
  s64 v10;
  Naki_t *v11;
  s32 *hai;
  Player_t *v13;
  s32 v14;
  Player_t *v15;
  Player_t *v16;
  Player_t *v17;
  Player_t *v18;
  Player_t *v20;
  Player_t *v21;
  Player_t *v22;
  Player_t *v24;
  Player_t *v25;
  Work_t *v26;
  Work_t *v28;

  players = Work->players;
  lastSutehai = Work->lastSutehai;
  v9 = players[playerIndex];
  v10 = (s64)v9->tehai34 + 4 * lastSutehai;
  v11 = v9->naki[v9->nakiNum];
  v11->type = 32;
  v11->fromPlayerIndex = fromPlayerIndex;
  hai = v11->hai;
  hai[0] = lastSutehai;
  hai[1] = lastSutehai;
  hai[2] = lastSutehai;
  v13 = players[fromPlayerIndex];
  *(u32 *)(v10 + 32) -= 2;
  v9->menzen = 0;
  v14 = v9->nakiNum + 1;
  v9->tehaiNum -= 2;
  v9->nakiNum = v14;
  if ((u32)v10)
  {
    v15 = players[0];
    v16 = players[1];
    v15->ippatsu = 0;
    v15->ichijunme = 0;
    v18 = players[2];
    v17 = players[3];
    v16->ippatsu = 0;
    v16->ichijunme = 0;
    v18->ippatsu = 0;
    v18->ichijunme = 0;
    v17->ippatsu = 0;
    v17->ichijunme = 0;
    --v13->sutehaiIndex;
    goto LABEL_13;
  }
  v20 = Work->players;
  v21 = v20[0];
  v21->ippatsu = 0;
  v21->ichijunme = 0;
  v22 = v20[1];
  v22->ippatsu = 0;
  v22->ichijunme = 0;
  v24 = v20[2];
  v24->ippatsu = 0;
  v24->ichijunme = 0;
  v25 = v20[3];
  v25->ippatsu = 0;
  v25->ichijunme = 0;
  --v13->sutehaiIndex;
LABEL_13:
  v26 = Work;
  v26->visibleHai[lastSutehai] += 2;
  v26->hideReachBou = -1;
  SetTehai14(playerIndex);
  if (playerIndex)
  {
    goto LABEL_15;
  }
  Work->tehaiCursor = Work->players[0]->tehaiNum
                                               - 1;
LABEL_15:
  v28 = Work;
  v28->turn = playerIndex;
  *(u64 *)&v28->phase = 0x200000003LL;
  matiChack();
  StartCutin(playerIndex, 4, 3, 0, 0);
  p2sdPlaySE_Vol(4194309, 127);
}

// 0x1d2f700
static void ApplyMinkan(s32 playerIndex, s32 fromPlayerIndex) {
  s64 lastSutehai;
  s64 m_Items;
  s64 v9;
  s64 v10;
  s64 v11;
  u32 *v12;
  Work_t *v15;

  lastSutehai = Work->lastSutehai;
  m_Items = Work->players;
  v9 = *(u64 *)(m_Items + 8 * playerIndex);
  v10 = *(u64 *)(m_Items + 8 * fromPlayerIndex);
  v11 = *(u64 *)(*(u64 *)(v9 + 80) + 8 * *(s32 *)(v9 + 72) + 32);
  *(u32 *)(v11 + 16) = 64;
  *(u32 *)(v11 + 20) = fromPlayerIndex;
  v12 = *(u32 **)(v11 + 24);
  v12[8] = lastSutehai;
  v12[9] = lastSutehai;
  v12[10] = lastSutehai;
  lastSutehai *= 4;
  *(u32 *)(*(u64 *)(v9 + 32) + lastSutehai + 32) -= 3;
  *(u32 *)(v9 + 92) = 0;
  *(u32 *)(v9 + 16) -= 3;
  ++*(u32 *)(v9 + 72);
  --*(u32 *)(v10 + 48);
  *(s32 *)((char *)Work->visibleHai + lastSutehai) += 3;
  Work->hideReachBou = -1;
  SetTehai14(playerIndex);
  if (!playerIndex)
  {
    Work->tehaiCursor = *(u32 *)(v9 + 16) - 1;
  }
  v15 = Work;
  v15->turn = playerIndex;
  *(u64 *)&v15->phase = 3;
  StartCutin(playerIndex, 6, 3, 64, 0);
  p2sdPlaySE_Vol(4194309, 127);
}

// 0x1d2f890
static void ApplyChi(s32 playerIndex, s32 chiType) {
  s32 lastSutehai;
  s64 m_Items;
  s64 v9;
  Player_t *v10;
  s64 nakiNum;
  s32 v12;
  s32 v13;
  s32 *tehai34;
  s32 v15;
  s32 v16;
  s64 v17;
  u32 *v18;
  Player_t *players;
  Player_t *v20;
  s32 *hai;
  s32 v22;
  Player_t *v23;
  Player_t *v24;
  Player_t *v25;
  Player_t *v26;
  Work_t *v34;
  s64 v35;
  Work_t *v37;

  lastSutehai = Work->lastSutehai;
  m_Items = Work->players;
  v9 = *(u64 *)(m_Items + 8 * Work->turn);
  v10 = *(Player_t *)(m_Items + 8 * playerIndex);
  nakiNum = v10->nakiNum;
  v10->naki[nakiNum]->type = chiType;
  switch (chiType)
  {
    case 268435968:
      v16 = lastSutehai + 1;
      v13 = lastSutehai + 2;
      v10 = Work->players[playerIndex];
      v15 = lastSutehai + 2;
      v12 = lastSutehai;
      v17 = v10->tehai34;
      v18 = (v17 + 4 * v16);
LABEL_18:
      --*v18;
      --*(u32 *)(v17 + 4 * v13);
      goto LABEL_20;
    case 268435712:
      v12 = lastSutehai - 1;
      v13 = lastSutehai + 1;
      v10 = Work->players[playerIndex];
      tehai34 = v10->tehai34;
      v15 = lastSutehai + 1;
      v16 = lastSutehai;
      goto LABEL_17;
    case 268435584:
      v12 = lastSutehai - 2;
      v13 = lastSutehai - 1;
      v10 = Work->players[playerIndex];
      tehai34 = v10->tehai34;
      v15 = lastSutehai;
      v16 = lastSutehai - 1;
LABEL_17:
      v17 = tehai34;
      v18 = (v17 + 4 * v12);
      goto LABEL_18;
  }
  v15 = 0;
  v16 = 0;
  v12 = 0;
LABEL_20:
  players = Work->players;
  v20 = players[playerIndex];
  hai = v20->naki[nakiNum]->hai;
  hai[0] = v12;
  hai[1] = v16;
  hai[2] = v15;
  v20->menzen = 0;
  v22 = v20->nakiNum + 1;
  v20->tehaiNum -= 2;
  v20->nakiNum = v22;
  v23 = players[0];
  v24 = players[1];
  v23->ippatsu = 0;
  v23->ichijunme = 0;
  v26 = players[2];
  v25 = players[3];
  v24->ippatsu = 0;
  v24->ichijunme = 0;
  v26->ippatsu = 0;
  v26->ichijunme = 0;
  v25->ippatsu = 0;
  v25->ichijunme = 0;
  --*(u32 *)(v9 + 48);
  v34 = Work;
  v35 = v34->visibleHai;
  --*(u32 *)(v35 + 4 * lastSutehai);
  ++*(u32 *)(v35 + 4 * v12);
  ++*(u32 *)(v35 + 4 * v16);
  ++*(u32 *)(v35 + 4 * v15);
  v34->hideReachBou = -1;
  SetTehai14(playerIndex);
  if (playerIndex)
  {
    goto LABEL_32;
  }
  Work->tehaiCursor = Work->players[0]->tehaiNum
                                               - 1;
LABEL_32:
  v37 = Work;
  v37->turn = playerIndex;
  *(u64 *)&v37->phase = 0x200000003LL;
  matiChack();
  StartCutin(playerIndex, 5, 3, 0, 0);
  p2sdPlaySE_Vol(4194309, 127);
}

// 0x1d2f350
static void ApplyRon(s32 playerIndex, s32 fromPlayerIndex) {
  MenuWin_agari_cent_SetAgariBarIcon(mjnUImanager, playerIndex, 0);
  MenuWin_agari_cent_SetHoujuBarIcon(mjnUImanager, fromPlayerIndex, 0);
  Work->agariPlayerIndex = playerIndex;
  Work->fromPlayerIndex = fromPlayerIndex;
  Work->phase = 6;
}

// 0x1d27df0
static void LoadTexToGSAll(void) {
  ;
}

// 0x1d3e2b0
static void LoadJingleAll(void) {
  ;
}

// 0x1d3e2c0
static void PlayJingle(s32 type) {
  s32 v3;

  sndSeStop(-1, 0);
  if (type)
    v3 = 135;
  else
    v3 = 134;
  sndSeLoadId(v3);
  sndSePlay(0);
}

// 0x1d3e3a0
static void FreeTexFromGSAll(void) {
  ;
}

// 0x1d2c010
static void FreeEffect(void) {
  effHandle_t *v2;
  effHandle_t *hPartsList;
  effHandle_t *v5;
  Work_t *Work_local;
  effHandle_t *v7;
  Work_t *v8;
  effHandle_t *v10;
  effHandle_t *v12;

  v2 = Work->hPartsList[0];
  if (v2)
  {
    Delete(v2);
    hPartsList = Work->hPartsList;
    hPartsList[0] = 0;
    goto LABEL_9;
  }
LABEL_9:
  v5 = Work->hPartsList[1];
  if (!v5)
  {
    goto LABEL_12;
  }
  Delete(v5);
  v10 = Work->hPartsList;
  v10[1] = 0;
LABEL_12:
  Work_local = Work;
  if (!Work_local->pSummonData)
  {
    goto LABEL_14;
  }
  Work_local = Work;
  Work_local->pSummonData = 0;
LABEL_14:
  v7 = Work->hPartsList[2];
  if (!v7)
  {
    goto LABEL_16;
  }
  Delete(v7);
  v12 = Work->hPartsList;
  v12[2] = 0;
LABEL_16:
  v8 = Work;
  if (!v8->pSummonData)
    return;
  v8 = Work;
  v8->pSummonData = 0;
}

// 0x1d27e00
static void LoadTsumikomiData(void) {
  TsumikomiHeader_t *v1;
  void *Asset;
  sdfBinary *v4;
  s64 v5;
  MJNTSUMIKOMIPROBTABLECLASS *TblDate;
  s64 v8;
  u8 *p_chin8;
  u8 *p_yakuhai4;
  u8 *p_yakuhai3;
  u8 *p_yakuhai2;
  MJNTSUMIKOMIPROBTABLECLASS *p_fields;
  u8 *p_yakuhai1;
  s64 v16;
  MJNDORAPROBTABLECLASS *v17;
  s64 v18;
  u8 *p_chin9;
  u8 *p_chin10;
  u8 *p_chin11;
  u8 *p_chin12;
  u8 *p_chin13;
  u8 *p_ipeiko;
  u8 *p_sansyoku;
  u8 *p_ikki;
  u8 *p_yakuhai1chin9;
  u8 *p_yakuhai1chin10;
  u8 *p_kantsu1;
  u8 *p_kantsu2;
  u8 *p_toitsu3;
  u8 *p_toitsu4;
  u8 *p_toitsu5;
  u8 *p_toitsu6;
  u8 *p_anko1;
  u8 *p_anko2;
  u8 *p_anko3;
  u8 *p_syuntsu1;
  u8 *p_syuntsu2;
  u8 *p_syuntsu3;
  u8 *p_kokushi9;
  u8 *p_kokushi10;
  u8 *p_kokushi11;
  u8 *p_kokushi12;
  u8 *p_kokushi13;
  u8 *p_toitsu3anko1;
  u8 *p_reserve1;
  u8 *p_reserve2;
  u8 *p_reserve3;

  v1 = Allocate(TsumikomiHeader_t);
  _ctor(v1, 0);
  Asset = LoadAsset(_Ctrl_k__BackingField, "mahjon", "MJN_TMK.TBL", 0);
  v4 = Allocate(sdfBinary);
  _ctor(v4, Asset, 0);
  v1->addr_tsumikomiProbTable = ReadU32(v4, 0);
  v1->addr_doraProbTable = ReadU32(v4, 0);
  v1->addr_devilTsumikomiTable = ReadU32(v4, 0);
  v5 = 0;
  v1->size = ReadS32(v4, 0);
  do
  {
    TblDate = GetTblDate(TsumikomiProbTable, v5, 0);
    v8 = 0;
    p_reserve2 = &TblDate->reserve2;
    p_reserve3 = &TblDate->reserve3;
    p_toitsu3anko1 = &TblDate->toitsu3anko1;
    p_reserve1 = &TblDate->reserve1;
    p_chin8 = &TblDate->chin8;
    p_kokushi12 = &TblDate->kokushi12;
    p_kokushi13 = &TblDate->kokushi13;
    p_yakuhai4 = &TblDate->yakuhai4;
    p_yakuhai3 = &TblDate->yakuhai3;
    p_kokushi10 = &TblDate->kokushi10;
    p_kokushi11 = &TblDate->kokushi11;
    p_yakuhai2 = &TblDate->yakuhai2;
    p_fields = &TblDate->fields;
    p_syuntsu3 = &TblDate->syuntsu3;
    p_kokushi9 = &TblDate->kokushi9;
    p_syuntsu1 = &TblDate->syuntsu1;
    p_syuntsu2 = &TblDate->syuntsu2;
    p_anko2 = &TblDate->anko2;
    p_anko3 = &TblDate->anko3;
    p_toitsu6 = &TblDate->toitsu6;
    p_anko1 = &TblDate->anko1;
    p_toitsu4 = &TblDate->toitsu4;
    p_toitsu5 = &TblDate->toitsu5;
    p_kantsu2 = &TblDate->kantsu2;
    p_toitsu3 = &TblDate->toitsu3;
    p_yakuhai1chin10 = &TblDate->yakuhai1chin10;
    p_kantsu1 = &TblDate->kantsu1;
    p_ikki = &TblDate->ikki;
    p_yakuhai1chin9 = &TblDate->yakuhai1chin9;
    p_ipeiko = &TblDate->ipeiko;
    p_sansyoku = &TblDate->sansyoku;
    p_chin12 = &TblDate->chin12;
    p_chin13 = &TblDate->chin13;
    p_chin10 = &TblDate->chin10;
    p_chin11 = &TblDate->chin11;
    p_chin9 = &TblDate->chin9;
    do
    {
      switch ((s32)v8)
      {
        case 0:
          p_yakuhai1 = &p_fields->yakuhai1;
          goto LABEL_84;
        case 1:
          p_yakuhai1 = p_yakuhai2;
          goto LABEL_84;
        case 2:
          p_yakuhai1 = p_yakuhai3;
          goto LABEL_84;
        case 3:
          p_yakuhai1 = p_yakuhai4;
          goto LABEL_84;
        case 4:
          p_yakuhai1 = p_chin8;
          goto LABEL_84;
        case 5:
          p_yakuhai1 = p_chin9;
          goto LABEL_84;
        case 6:
          p_yakuhai1 = p_chin10;
          goto LABEL_84;
        case 7:
          p_yakuhai1 = p_chin11;
          goto LABEL_84;
        case 8:
          p_yakuhai1 = p_chin12;
          goto LABEL_84;
        case 9:
          p_yakuhai1 = p_chin13;
          goto LABEL_84;
        case 10:
          p_yakuhai1 = p_ipeiko;
          goto LABEL_84;
        case 11:
          p_yakuhai1 = p_sansyoku;
          goto LABEL_84;
        case 12:
          p_yakuhai1 = p_ikki;
          goto LABEL_84;
        case 13:
          p_yakuhai1 = p_yakuhai1chin9;
          goto LABEL_84;
        case 14:
          p_yakuhai1 = p_yakuhai1chin10;
          goto LABEL_84;
        case 15:
          p_yakuhai1 = p_kantsu1;
          goto LABEL_84;
        case 16:
          p_yakuhai1 = p_kantsu2;
          goto LABEL_84;
        case 17:
          p_yakuhai1 = p_toitsu3;
          goto LABEL_84;
        case 18:
          p_yakuhai1 = p_toitsu4;
          goto LABEL_84;
        case 19:
          p_yakuhai1 = p_toitsu5;
          goto LABEL_84;
        case 20:
          p_yakuhai1 = p_toitsu6;
          goto LABEL_84;
        case 21:
          p_yakuhai1 = p_anko1;
          goto LABEL_84;
        case 22:
          p_yakuhai1 = p_anko2;
          goto LABEL_84;
        case 23:
          p_yakuhai1 = p_anko3;
          goto LABEL_84;
        case 24:
          p_yakuhai1 = p_syuntsu1;
          goto LABEL_84;
        case 25:
          p_yakuhai1 = p_syuntsu2;
          goto LABEL_84;
        case 26:
          p_yakuhai1 = p_syuntsu3;
          goto LABEL_84;
        case 27:
          p_yakuhai1 = p_kokushi9;
          goto LABEL_84;
        case 28:
          p_yakuhai1 = p_kokushi10;
          goto LABEL_84;
        case 29:
          p_yakuhai1 = p_kokushi11;
          goto LABEL_84;
        case 30:
          p_yakuhai1 = p_kokushi12;
          goto LABEL_84;
        case 31:
          p_yakuhai1 = p_kokushi13;
          goto LABEL_84;
        case 32:
          p_yakuhai1 = p_toitsu3anko1;
          goto LABEL_84;
        case 33:
          p_yakuhai1 = p_reserve1;
          goto LABEL_84;
        case 34:
          p_yakuhai1 = p_reserve2;
          goto LABEL_84;
        case 35:
          p_yakuhai1 = p_reserve3;
LABEL_84:
          Work->tsumikomiProbTable[v5][v8] = *p_yakuhai1;
          break;
        default:
          break;
      }
      ++v8;
    }
    while (v8 != 36);
    ++v5;
  }
  while (v5 != 16);
  v16 = 4;
  do
  {
    v17 = GetTblDate(DoraProbDataTable, (s32)v16 - 4, 0);
    v18 = 8 * v16++;
    LOBYTE((*(Il2CppClass **)((char *)&Work->doraProbTable->obj.klass + v18))->_1.byval_arg.data) = v17->_1;
    BYTE1((*(Il2CppClass **)((char *)&Work->doraProbTable->obj.klass + v18))->_1.byval_arg.data) = v17->_2;
    BYTE2((*(Il2CppClass **)((char *)&Work->doraProbTable->obj.klass + v18))->_1.byval_arg.data) = v17->_3;
    BYTE3((*(Il2CppClass **)((char *)&Work->doraProbTable->obj.klass + v18))->_1.byval_arg.data) = v17->_4;
  }
  while (v16 != 12);
}

// 0x1d284b0
static void InitDevil(s32 playerIndex, s32 devilID) {
  s32 v8;
  Player_t *v9;
  Visual_t *pVisualData;
  MJNVISUALCLASS *TblDataInID;
  u64 v12;
  Visual_t *v15;
  MJNVISUALCLASS *v16;
  Visual_t *v19;
  MJNVISUALCLASS *v20;
  Visual_t *v23;
  Player_t *v27;
  u8 **tsumikomiProbTable;
  MJNTSUMIKOMICLASS *v29;
  Work_t *v31;
  u8 **doraProbTable;
  Player_t *v33;
  MJNTSUMIKOMICLASS *v34;
  u32 tData;
  s32 v37;
  s32 v39;
  s32 v40;
  Work_t *v41;
  Work_t *v42;
  Player_t *v43;
  dds3ModelHandle_t *v44;
  Player_t *v45;
  s32 v46;
  Player_t *v47;
  dds3ModelHandle_t *v48;
  char *v49;
  dds3ModelHandle_t *modelHandle;
  Work_t *v52;
  dds3ModelHandle_t *v53;
  u32 v54;
  dds3ModelHandle_t *v55;
  Player_t *v56;
  char *v57;
  dds3ModelHandle_t *v58;
  Player_t *v62;
  Visual_t *v63;
  f32 posDist;
  f32 scale;
  float32x4_t *v67;
  dds3ModelHandle_t *v69;
  f32 v71;
  Work_t *v72;
  Player_t *v73;
  f32 posHeight;
  f32 posDistance;
  dds3ModelHandle_t *v77;
  _OWORD *p_m00;
  __int128 v80;
  __int128 v81;
  __int128 v82;
  f32 v84;
  s64 v88;
  sdfVector4_t *v90;
  dds3ModelHandle_t *v91;
  f32 v93;
  dds3ModelHandle_t *v94;
  _OWORD *v96;
  __int128 v97;
  __int128 v98;
  __int128 v99;
  sdfMatrix4_t v103;
  sdfVector4_t Row;
  sdfVector4_t v105;

  memset(&v103, 0, sizeof(v103));
  if (playerIndex)
    v8 = devilID;
  else
    v8 = 81;
  v9 = Work->players[playerIndex];
  v9->flag = 0;
  v9 = Work->players[playerIndex];
  pVisualData = v9->pVisualData;
  TblDataInID = GetTblDataInID(VisualDataTable, v8, 0);
  v12 = playerIndex;
  pVisualData->posDist = TblDataInID->posDist;
  v15 = Work->players[v12]->pVisualData;
  v16 = GetTblDataInID(VisualDataTable, v8, 0);
  v15->cameraEyeDist = v16->cameraEyeDist;
  v19 = Work->players[v12]->pVisualData;
  v20 = GetTblDataInID(VisualDataTable, v8, 0);
  v19->cameraTargetHeight = v20->cameraTargetHeight;
  v23 = Work->players[v12]->pVisualData;
  v23->scale = GetTblDataInID(VisualDataTable, v8, 0)->scale;
  v27 = Work->players[v12];
  v27->devilID = devilID;
  tsumikomiProbTable = Work->tsumikomiProbTable;
  v29 = GetTblDataInID(TsumikomiDataTable, v8, 0);
  set_tsumikomiProb(v27, tsumikomiProbTable[v29->tData], 0);
  v31 = Work;
  doraProbTable = v31->doraProbTable;
  v33 = v31->players[v12];
  v34 = GetTblDataInID(TsumikomiDataTable, v8, 0);
  set_doraProb(v33, doraProbTable[v34->dData], 0);
  tData = GetTblDataInID(TsumikomiDataTable, v8, 0)->tData;
  if (tData > 0xE)
    goto LABEL_121;
  v37 = 1 << tData;
  if ((v37 & 0x2490) == 0)
  {
    if ((v37 & 0x4920) != 0)
    {
      v39 = 2;
      v40 = 2;
      goto LABEL_17;
    }
LABEL_121:
    v39 = 0;
    v40 = 0;
    goto LABEL_17;
  }
  v39 = 1;
  v40 = 1;
  v40 = v39;
LABEL_17:
  Work->players[playerIndex]->rank = v40;
  if (playerIndex == 2)
  {
    v41 = Work;
    if (v41->PlayWithNarumi)
    {
      v41 = Work;
      v41->players[2]->rank = 2;
    }
    v42 = Work;
    if (!v42->PlayWithNarumi)
      goto LABEL_28;
    v42 = Work;
    v47 = v42->players[v12];
    v48 = ModelLoad(8, 768);
    v47->modelHandle = v48;
    v45 = Work->players[v12];
    v46 = 240;
LABEL_41:
    v49 = sdatDevilName(v46, 0);
    v45->name = v49;
    modelHandle = Work->players[playerIndex]->modelHandle;
    mdlSmoothLoopMotion(modelHandle, 0, 0, 8.0, 8.0, 0.0);
    mdlSetMotionSpeedEx(Work->players[playerIndex]->modelHandle, 0, 0.5);
    v52 = Work;
    if (v52->PlayWithNarumi && (playerIndex | 2) != 3)
    {
      v52 = Work;
      v58 = v52->players[playerIndex]->modelHandle;
      v55 = v58;
      v54 = -2139062144;
    }
    else
    {
      v52 = Work;
      v53 = v52->players[playerIndex]->modelHandle;
      v54 = 8421504;
      v55 = v53;
    }
    mdlSetColor(v55, v54);
    v62 = Work->players[playerIndex];
    v63 = v62->pVisualData;
    posDist = v63->posDist;
    v62->posHeight = 0.0;
    v62->cameraEyeHeight = -160.0;
    v62->posDistance = posDist;
    v62->cameraEyeDistance = v63->cameraEyeDist;
    v62->cameraTargetHeight = -v63->cameraTargetHeight;
    v62->cameraTargetDistance = posDist;
    v62->scale = v63->scale;
LABEL_67:
    vct_A = (struct sdfVector4_t)xmmword_3D06BB0;
    scale = Work->players[playerIndex]->scale;
    v67[1] = vmulq_n_f32(v67[1], scale);
    v69 = Work->players[playerIndex]->modelHandle;
    mdlSetScale(v69);
    v71 = 0.0;
    v72 = Work;
    v73 = v72->players[playerIndex];
    posHeight = v73->posHeight;
    switch (playerIndex)
    {
      case 1:
        v73 = Work->players[playerIndex];
        posDistance = v73->posDistance;
        v77 = v73->modelHandle;
        mdlGetRotate(v77);
        p_m00 = &IdentityMatrix.m00;
        v80 = p_m00[2];
        v81 = p_m00[3];
        v82 = p_m00[1];
        *(_OWORD *)&v103.m00 = *p_m00;
        *(_OWORD *)&v103.m01 = v82;
        *(_OWORD *)&v103.m02 = v80;
        *(_OWORD *)&v103.m03 = v81;
        Row = GetRow(&v103, 1, 0);
        vct_B = Row;
        v84 = 4.712389;
        goto LABEL_117;
      case 2:
        posDistance = 0.0;
        if (v72->PlayWithNarumi)
        {
          goto LABEL_93;
        }
        v72 = Work;
        v71 = v72->players[playerIndex]->posDistance + 0.0;
        goto LABEL_93;
      case 3:
        v73 = Work->players[playerIndex];
        v93 = v73->posDistance;
        v94 = v73->modelHandle;
        mdlGetRotate(v94);
        v96 = &IdentityMatrix.m00;
        v97 = v96[2];
        v98 = v96[3];
        v99 = v96[1];
        *(_OWORD *)&v103.m00 = *v96;
        *(_OWORD *)&v103.m01 = v99;
        *(_OWORD *)&v103.m02 = v97;
        *(_OWORD *)&v103.m03 = v98;
        v105 = GetRow(&v103, 1, 0);
        posDistance = -v93;
        vct_B = v105;
        v84 = 1.5707964;
LABEL_117:
        FromRotation_B(v84);
        Mult();
        mdlSetRotate(Work->players[playerIndex]->modelHandle);
LABEL_93:
        goto LABEL_9003;
LABEL_95:
        vct_A.x = posDistance;
        vct_A.y = posHeight;
        vct_A.z = v71;
        vct_A.w = 1.0;
        v88 = (s64)Work->playerPos + 16 * playerIndex;
        v90 = (v88 + 32);
        *v90 = vct_A;
        v91 = Work->players[playerIndex]->modelHandle;
        mdlSetPosition(Work->players[playerIndex]->modelHandle);
        SetDevilFaceIcon(mjnUImanager, playerIndex, devilID, 0);
        MenuWin_agari_SetDevilLevel(mjnUImanager, playerIndex, devilID, 0);
        MenuWin_agari_SetNameAndID(mjnUImanager, playerIndex, Work->players[playerIndex]->name, devilID, 0);
        return;
LABEL_9003:
        goto LABEL_95;
      default:
        posDistance = 0.0;
        goto LABEL_93;
    }
    goto LABEL_67;
LABEL_28:
    v43 = Work->players[v12];
    v44 = ModelLoad(7);
    v43->modelHandle = v44;
    v45 = Work->players[v12];
    v46 = devilID;
    goto LABEL_41;
  }
  if (playerIndex)
    goto LABEL_28;
  v56 = Work->players[0];
  v57 = sdatDevilName(241, 0);
  v56->name = v57;
}

// 0x1d3e3b0
static void FreeModel(void) {
  dds3ModelHandle_t *modelHandle;
  Player_t *v4;
  dds3ModelHandle_t *v5;
  dds3ModelHandle_t *v6;
  Player_t *v8;
  Player_t *v10;
  s64 i;
  u64 *v12;
  Work_t *Work_local;
  dds3ModelHandle_t *tenbouModelHandle;
  dds3ModelHandle_t *v19;
  dds3ModelHandle_t *v21;
  dds3ModelHandle_t *v23;
  dds3ModelHandle_t *oyaModelHandle;
  dds3ModelHandle_t *v27;
  dds3ModelHandle_t *v29;
  dds3ModelHandle_t *v31;

  modelHandle = Work->players[1]->modelHandle;
  if (modelHandle)
  {
    mdlSetLight(modelHandle, 0);
    v4 = Work->players[1];
    v4->modelHandle = 0;
    goto LABEL_9;
  }
LABEL_9:
  v5 = Work->players[2]->modelHandle;
  if (!v5)
  {
    goto LABEL_12;
  }
  mdlSetLight(v5, 0);
  v8 = Work->players[2];
  v8->modelHandle = 0;
LABEL_12:
  v6 = Work->players[3]->modelHandle;
  if (v6)
  {
    mdlSetLight(v6, 0);
    v10 = Work->players[3];
    v10->modelHandle = 0;
  }
  for (i = 32; i != 1312; i += 8)
  {
    v12 = ((char *)&Work->haiModelHandle->obj.klass + i);
    *v12 = 0;
  }
  Work_local = Work;
  Work_local->tableModelHandle = 0;
  tenbouModelHandle = Work->tenbouModelHandle;
  tenbouModelHandle[0] = 0;
  v19 = Work->tenbouModelHandle;
  v19[1] = 0;
  v21 = Work->tenbouModelHandle;
  v21[2] = 0;
  v23 = Work->tenbouModelHandle;
  v23[3] = 0;
  oyaModelHandle = Work->oyaModelHandle;
  oyaModelHandle[0] = 0;
  v27 = Work->oyaModelHandle;
  v27[1] = 0;
  v29 = Work->oyaModelHandle;
  v29[2] = 0;
  v31 = Work->oyaModelHandle;
  v31[3] = 0;
}

// 0x1d29300
static void InitCameraSummon(void) {
  dds3SetScreenFovy(0.628318);
  Work->cameraTargetPos = (struct sdfVector4_t)xmmword_3CFC700;
  Work->cameraEyePos = (struct sdfVector4_t)xmmword_3CFAFD0;
  Work->cameraUpVector = (struct sdfVector4_t)xmmword_3D05530;
  mapBgSetScrollReset();
}

// 0x1d39ac0
static void ManageSummonPhase(void) {
  u64 *v1;
  u8 *v2;
  Player_t *v3;
  u64 *v4;
  Player_t *v5;
  u64 *v6;
  Player_t *v7;
  void *v8;
  s32 summonPhase;
  dds3ModelHandle_t *v10;
  f32 *p_x;
  f32 v14;
  f32 v15;
  f32 v16;
  f32 v17;
  effHandle_t *v18;
  dds3ModelHandle_t *v21;
  f32 *v24;
  f32 v26;
  f32 v27;
  f32 v28;
  f32 v29;
  effHandle_t *v30;
  dds3ModelHandle_t *v33;
  f32 *v36;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  effHandle_t *v42;
  Work_t *Work_local;
  Work_t *v52;
  s32 cameraCount;
  bool v54;
  dds3ModelHandle_t *modelHandle;
  Work_t *v56;
  dds3ModelHandle_t *v57;
  Work_t *v58;
  s32 v59;
  bool v60;
  s32 v61;
  s32 v62;
  u32 v63;
  dds3ModelHandle_t *v64;
  effHandle_t *v65;
  s32 v66;
  s32 v67;
  s32 v68;
  u32 v69;
  dds3ModelHandle_t *v70;
  effHandle_t *v71;
  Work_t *v72;
  u32 v73;
  Work_t *v74;
  Work_t *v75;
  s32 v76;
  s32 v77;
  u32 v78;
  dds3ModelHandle_t *v79;
  effHandle_t *v80;
  s32 v81;
  dds3ModelHandle_t *v82;
  Player_t *v84;
  dds3ModelHandle_t *v85;
  dds3ModelHandle_t *v86;
  dds3ModelHandle_t *v88;
  Work_t *v90;
  dds3ModelHandle_t *v91;
  bool v92;
  dds3ModelHandle_t *v93;
  Work_t *v94;
  dds3ModelHandle_t *v95;
  bool v96;
  dds3ModelHandle_t *v97;
  float32x2_t *v98;
  f32 v99;
  f32 v100;
  f32 v101;
  sdfVector4_t v103;
  sdfVector4_t v104;
  sdfVector4_t v105;

  v1 = NewSpecific(Player_t, 3u);
  v2 = NewSpecific(byte, 3u);
  v3 = Work->players[1];
  if (v3)
  {
    if (!QueryInterface(v3, *(void **)(*v1 + 64)))
      goto LABEL_232;
  }
  v1[4] = v3;
  v4 = v1 + 4;
  v5 = Work->players[3];
  {
LABEL_232:
  }
  v1[6] = v7;
  v8 = v1 + 6;
  summonPhase = Work->summonPhase;
  if (summonPhase != 1)
  {
    if (summonPhase)
      return;
    v10 = *(dds3ModelHandle_t *)(*v4 + 168);
    mdlGetPosition(v10);
    p_x = &vf00.x;
    v14 = p_x[4];
    v15 = p_x[5];
    v16 = p_x[6];
    v17 = p_x[7];
    v18 = Work->hPartsList[0];
    v103.x = v14;
    v103.y = v15;
    v103.z = v16;
    v103.w = v17;
    dds3EffectSetPosition(v18, v103);
    mdlGetRotate(*(dds3ModelHandle_t *)(*v4 + 168));
    v21 = *(dds3ModelHandle_t *)(*v6 + 168);
    mdlGetPosition(v21);
    v24 = &vf00.x;
    v26 = v24[4];
    v27 = v24[5];
    v28 = v24[6];
    v29 = v24[7];
    v30 = Work->hPartsList[1];
    v104.x = v26;
    v104.y = v27;
    v104.z = v28;
    v104.w = v29;
    dds3EffectSetPosition(v30, v104);
    mdlGetRotate(*(dds3ModelHandle_t *)(*v6 + 168));
    v33 = *(dds3ModelHandle_t *)(*(u64 *)v8 + 168);
    mdlGetPosition(v33);
    v36 = &vf00.x;
    x = v36[4];
    y = v36[5];
    z = v36[6];
    w = v36[7];
    v42 = Work->hPartsList[2];
    v105.x = x;
    v105.y = y;
    v105.z = z;
    v105.w = w;
    dds3EffectSetPosition(v42, v105);
    mdlGetRotate(*(dds3ModelHandle_t *)(*(u64 *)v8 + 168));
    dds3FadeIn(0, 0, 0, 0xFu);
    Work_local = Work;
    Work_local->cameraEyePosStart.z = -800.0;
    Work_local->cameraCount = 0;
    Work_local->summonPhase = 1;
    *(u64 *)&Work_local->cameraEyePosStart.x = 0xC33C000000000000LL;
    *(u64 *)&Work_local->cameraEyePosEnd.x = 0xC33C000000000000LL;
    Work_local->cameraEyePosEnd.z = -58.0;
    return;
  }
  if (dds3FadeCheck())
    return;
  v52 = Work;
  cameraCount = v52->cameraCount;
  if (cameraCount == 500)
  {
    v52 = Work;
    v52->phase = 2;
LABEL_76:
    InitCamera();
    return;
  }
  if (cameraCount >= 180)
  {
    v54 = CHECK_REP(4097, 1);
    if (v54)
    {
      modelHandle = Work->players[1]->modelHandle;
      mdlSmoothLoopMotion(modelHandle, 0, 0, 8.0, 8.0, 0.0);
      mdlSmoothLoopMotion(Work->players[3]->modelHandle, 0, 0, 8.0, 8.0, 0.0);
      v56 = Work;
      v56 = Work;
      v57 = v56->players[2]->modelHandle;
      mdlSmoothLoopMotion(v57, 0, 0, 8.0, 8.0, 0.0);
      Work->phase = 2;
      goto LABEL_76;
    }
  }
  v58 = Work;
  v59 = v58->cameraCount + 1;
  v60 = v58->cameraCount - 60 < 0;
  v58->cameraCount = v59;
  if (v60 == __OFSUB__(v59, 61))
  {
    v59 = Work->cameraCount;
    if (v59 <= 120)
    {
      v59 = Work->cameraCount;
      v61 = (u64)(2290649225LL * ((v59 << 7) - 7680)) >> 32;
      v62 = (v61 >> 5) + ((u32)v61 >> 31);
      v2[32] = v62;
      v63 = (v62 << 24) | 0x808080;
      v64 = Work->players[1]->modelHandle;
      mdlSetColor(v64, v63);
      v65 = Work->hPartsList[0];
      if (v65)
      {
        v65 = Work->hPartsList[0];
        dds3EffectDraw(v65);
      }
    }
  }
  v66 = Work->cameraCount;
  if (v66 >= 121)
  {
    v66 = Work->cameraCount;
    if (v66 <= 180)
    {
      v66 = Work->cameraCount;
      v67 = (u64)(2290649225LL * ((v66 << 7) - 15360)) >> 32;
      v68 = (v67 >> 5) + ((u32)v67 >> 31);
      v2[33] = v68;
      v69 = (v68 << 24) | 0x808080;
      v70 = Work->players[3]->modelHandle;
      mdlSetColor(v70, v69);
      v71 = Work->hPartsList[1];
      if (v71)
      {
        v71 = Work->hPartsList[1];
        dds3EffectDraw(v71);
      }
    }
  }
  v72 = Work;
  if (!v72->PlayWithNarumi)
  {
    v72 = Work;
    v76 = v72->cameraCount;
    if (v76 >= 1)
    {
      v76 = Work->cameraCount;
      if (v76 <= 60)
      {
        v76 = Work->cameraCount;
        v77 = (v76 << 7) / 60;
        v2[34] = v77;
        v78 = (v77 << 24) | 0x808080;
        v79 = Work->players[2]->modelHandle;
        mdlSetColor(v79, v78);
        v80 = Work->hPartsList[2];
        if (v80)
        {
          v80 = Work->hPartsList[2];
          dds3EffectDraw(v80);
        }
      }
    }
  }
  v74 = Work;
  if (v74->PlayWithNarumi)
  {
    if (v73)
    {
      if (v74->cameraCount != 30)
        goto LABEL_134;
    }
    else
    {
      v74 = Work;
      if (v74->cameraCount != 30)
      {
LABEL_134:
        goto LABEL_135;
      }
    }
    v74 = Work;
    v85 = v74->players[2]->modelHandle;
    mdlSingleMotion(v85, 0, 3);
LABEL_135:
    v75 = Work;
    if (v75->cameraCount < 31)
      goto LABEL_183;
    v75 = Work;
    v86 = v75->players[2]->modelHandle;
    if (mdlChkMotionEnd(v86))
    {
      v84 = Work->players[2];
LABEL_180:
      v88 = v84->modelHandle;
      mdlSmoothLoopMotion(v88, 0, 0, 8.0, 8.0, 0.0);
      goto LABEL_183;
    }
    goto LABEL_183;
  }
  if (!v73)
  {
    v74 = Work;
  }
  v81 = v74->cameraCount;
  if (v81 < 1)
    goto LABEL_183;
  if (v81 != 10)
    goto LABEL_158;
  goto LABEL_9004;
  if (Work->cameraCount != 10)
  {
LABEL_158:
    goto LABEL_159;
  }
LABEL_9004:
  p2sdPlaySE_Vol(65561, 127);
LABEL_159:
  v82 = Work->players[3]->modelHandle;
  if (mdlChkMotionEnd(v82))
  {
    v84 = Work->players[3];
    goto LABEL_180;
  }
LABEL_183:
  if (Work->cameraCount != 60)
  {
    goto LABEL_186;
  }
  p2sdPlaySE_Vol(65561, 127);
LABEL_186:
  v90 = Work;
  if (v90->cameraCount >= 61)
  {
    v90 = Work;
    v91 = v90->players[1]->modelHandle;
    v92 = mdlChkMotionEnd(v91);
    if (v92)
    {
      v93 = Work->players[1]->modelHandle;
      mdlSmoothLoopMotion(v93, 0, 0, 8.0, 8.0, 0.0);
    }
  }
  if (Work->cameraCount != 120)
  {
    goto LABEL_206;
  }
  p2sdPlaySE_Vol(65561, 127);
LABEL_206:
  v94 = Work;
  if (v94->cameraCount >= 121)
  {
    v94 = Work;
    v95 = v94->players[3]->modelHandle;
    v96 = mdlChkMotionEnd(v95);
    if (v96)
    {
      v97 = Work->players[3]->modelHandle;
      mdlSmoothLoopMotion(v97, 0, 0, 8.0, 8.0, 0.0);
    }
  }
  v98 = Work;
  v99 = (f32)v98[30].n64_i32[0] / 500.0;
  v100 = (f32)(1.0 - v99) * v98[13].n64_f32[0];
  v101 = v98[15].n64_f32[0];
  v98[4].n64_u64[0] = vadd_f32(vmul_n_f32(v98[12], 1.0 - v99), vmul_n_f32(v98[14], v99)).n64_u64[0];
  v98[5].n64_f32[0] = v100 + (f32)(v99 * v101);
}

// 0x1d293f0
static void InitInterface(void) {
  Create(0);
  fclLoadData("mjnMenuMsg.bmd", "mahjon", 1);
  Reset(0);
  Work->interface->dummy = 0;
  Unload(Dependent, "mahjon", 0);
}

// 0x1d2bc50
static void DestroyInterface(void) {
}

// 0x1d3e810
static void CalcResult(void) {
  s32 *v1;
  s32 v2;
  s64 v3;
  s64 v5;
  s64 v6;
  s32 v7;
  s32 v8;
  s64 m_Items;
  s64 v10;
  s32 v12;
  s32 v13;
  s32 v15;
  Work_t *v17;
  s32 *ranking;
  Player_t *players;
  Player_t *v20;
  Player_t *v21;
  Player_t *v22;
  Player_t *v23;
  s32 tensu2;
  s64 rank;
  s32 v28;
  sdatPlayerUnitWork_t *player;
  s32 gold;
  sdatPlayerUnitWork_t *v31;
  Work_t *v32;
  s32 money;
  u32 v34;
  s32 v35;
  s64 v36;
  s32 v37;

  v1 = NewSpecific(s32, 4u);
  v2 = 0;
  v3 = 3;
  *(_OWORD *)&v1[0] = xmmword_3CFBEA0;
LABEL_5:
  if (v2 != 3)
  {
    v5 = 0;
    while (1)
    {
      v6 = (s64)(char *)v1 + 4 * v5;
      v8 = *(u32 *)(v6 + 32);
      v7 = *(u32 *)(v6 + 36);
      m_Items = Work->players;
      if (*(u32 *)(*(u64 *)(m_Items + 8 * v8) + 64) >= *(u32 *)(*(u64 *)(m_Items + 8 * v7) + 64))
      {
        v10 = v8;
        if (Work->players[v10]->tensu != Work->players[v7]->tensu)
          goto LABEL_8;
        v12 = v8 - Work->chicha;
        v13 = v12 >= 0 ? v8 - Work->chicha : v12 + 4;
        v15 = v7 - Work->chicha;
        if (v13 <= v15 + (v15 < 0 ? 4 : 0))
          goto LABEL_8;
        v8 = *(u32 *)(v6 + 32);
        v7 = *(u32 *)(v6 + 36);
      }
      *(u32 *)(v6 + 32) = v7;
      *(u32 *)(v6 + 36) = v8;
LABEL_8:
      if (v3 == ++v5)
      {
        ++v2;
        --v3;
        if (v2 != 4)
          goto LABEL_5;
        break;
      }
    }
  }
  v17 = Work;
  ranking = v17->ranking;
  ranking[0] = v1[0];
  ranking[1] = v1[1];
  ranking[2] = v1[2];
  ranking[3] = v1[3];
  players = v17->players;
  v20 = players[v1[0]];
  v20->tensu += 1000 * v17->reachBou;
  v21 = players[v1[1]];
  v21->tensu2 = v21->tensu - 15000;
  v22 = players[v1[2]];
  v22->tensu2 = v22->tensu - 35000;
  v23 = players[v1[3]];
  v23->tensu2 = v23->tensu - 45000;
  players[v1[0]]->tensu2 = -players[v1[3]]->tensu2
                                                     - (players[v1[1]]->tensu2 + players[v1[2]]->tensu2);
  tensu2 = players[0]->tensu2;
  if (tensu2 < 1)
  {
    if (tensu2 < 0)
    {
      v17 = Work;
      v17->money = -(-tensu2 / 5u);
      goto LABEL_54;
    }
    else
    {
      v17 = Work;
      v17->money = 0;
      goto LABEL_54;
    }
    goto LABEL_54;
  }
  rank = players[1]->rank;
  if ((u32)rank > 2)
    return;
  v28 = dword_3E62F40[rank];
  if (players[2]->rank > 2u)
    return;
  v17 = Work;
  players = v17->players;
  v36 = players[3]->rank;
  if ((u32)v36 > 2)
    return;
  v37 = dword_3E62F40[v36];
  v17 = Work;
  v17->money = (v37 + v28) * tensu2 / 30;
LABEL_54:
  player = GBWK->player;
  gold = player->gold;
  v31 = GBWK->player;
  v32 = Work;
  money = v32->money;
  v32->money_max = 0;
  player->gold = money + gold;
  v35 = v31->gold;
  if (v35 < 0)
  {
    if (!v34)
    {
      v31 = GBWK->player;
    }
    v31->gold = 0;
  }
  else
  {
    if (v34)
    {
      if (v35 <= 9999999)
        return;
    }
    else
    {
      v31 = GBWK->player;
      if (v31->gold <= 9999999)
        return;
    }
    v31 = GBWK->player;
    v31->gold = 9999999;
    Work->money_max = 1;
  }
}

// 0x1d35e00
static void InitEndHanchan(void) {
  s32 money;

  *(u64 *)(*((u64 *)*((const MethodInfo *)mjn + 2).virtualMethodPointer + 24) + 548) = 0;
  CalcResult();
  GuideDispStop(0);
  MenuWin_play_SetActive(mjnUImanager, 0, 0);
  MenuWin_agari_cent_SetActive(mjnUImanager, 0, 0);
  sndBgmFadeOut2();
  money = Work->money;
  PlayJingle(money < 1);
}

// 0x1d3c0d0
static void ManageEndHanchanPhase(void) {
  Work_t *Work_local;
  u32 rstStep;
  Work_t *v6;
  s32 money;
  s32 waitCount;
  s64 v14;
  u32 v16;
  Il2CppObject *v17;
  char *v18;
  char *v19;
  Il2CppObject *v22;
  char *v23;
  char *v24;
  s32 data;
  s32 v26;

  Work_local = Work;
  rstStep = Work_local->rstStep;
  if (rstStep > 8)
    return;
  switch (rstStep)
  {
    case 0u:
      ButtonGuideDispOut();
      UnloadSceneAsync(mahjon_gKey, 0);
      v6 = Work;
      v6->rstStep = 1;
      StartCutin(v6->ranking[0], 3, 11, 0x2000, 0);
      return;
    case 1u:
      ManageCutin();
      return;
    case 2u:
      if (Work_local->waitCount < 210)
      {
LABEL_21:
        goto LABEL_35;
      }
      Work_local = Work;
      Work_local->rstStep = 3;
      goto LABEL_21;
    case 3u:
      money = Work_local->money;
      Reset(0);
      if (money < 0)
      {
        data = -money;
        v17 = Box(s32, &data);
        v18 = Format("{0}", v17, 0);
        v19 = itfConvertToDelimitedNum(v18);
        fclSetMessageVar(0, v19);
        fclStart1(4, 0);
      }
      else
      {
        if (Work->money_max)
        {
          fclStart1(6, 0);
          goto LABEL_28;
        }
        v26 = money;
        v22 = Box(s32, &v26);
        v23 = Format("{0}", v22, 0);
        v24 = itfConvertToDelimitedNum(v23);
        fclSetMessageVar(0, v24);
        fclStart1(3, 0);
      }
LABEL_28:
      Work->rstStep = 4;
      return;
    case 4u:
      if (Update())
        return;
      dds3FadeOut(0, 0, 0, 0xFu);
      v14 = 0x500000000LL;
LABEL_64:
      *(u64 *)&Work->waitCount = v14;
      return;
    case 5u:
      waitCount = Work_local->waitCount;
      if (waitCount < 15)
      {
        goto LABEL_44;
LABEL_34:
LABEL_35:
        ++Work->waitCount;
        return;
      }
      Work_local = Work;
      *(u64 *)&Work_local->waitCount = 0x600000000LL;
      return;
    case 6u:
      Work_local = Work;
      Work_local->fDrawAll = 0;
      dds3KillProcessName("mahjon draw process", 0);
      v14 = 0x700000000LL;
      goto LABEL_64;
    case 7u:
      Work_local = Work;
      waitCount = Work_local->waitCount;
      if (waitCount < 5)
        goto LABEL_43;
      if (v16)
      {
        goto LABEL_72;
      }
      else
      {
LABEL_72:
LABEL_73:
        FreeEffect();
        Work->rstStep = 8;
        return;
      }
      goto LABEL_73;
LABEL_43:
      if (!v16)
        goto LABEL_34;
LABEL_44:
      Work_local->waitCount = waitCount + 1;
      return;
    case 8u:
      EndMahjong();
      return;
    default:
      return;
  }
}

// 0x1d3ee70
static void EndMahjong(void) {
  gMjnRun = 0;
  dds3KillProcessName("mahjon main process", 1);
}

// 0x1d25f80
static dds3ModelHandle_t *ModelLoad(s32 major, s32 minor) {
  u16 v4;
  dds3ModelHandle_t *v5;
  dds3ModelHandle_t *v6;

  v4 = major;
  v5 = Allocate(dds3ModelHandle_t);
  _ctor(v5, 0);
  v6 = mdlLoad(v4, minor);
  if (mdlHasMotion(v6))
  {
    mdlSingleMotion(v6, 0, 0);
  }
  return v6;
}

// 0x1d3e800
static void FreeModelEach(dds3ModelHandle_t *modelHandle) {
  ;
}

// 0x1d041d0
static void PlaySE(s32 no) {
  p2sdPlaySE_Vol(no, 127);
}

// 0x1d3ef30
static s32 Start(void) {
  gMjnRun = 1;
  sdfMemRelease();
  MenuInit();
  return 0;
}

// 0x1d3fe90
static s32 ShutDown(void) {
  MJN_GUIDEHELP_FLAG = 0;
  dds3KillProcessName("mahjon menu process", 1);
  dds3KillProcessName("mahjon main process", 1);
  return 0;
}

// 0x1d3ff70
void mjnTIpsMenuProcessEnd(void) {
  dds3KillProcessName("mjntips_calc", 0);
  dds3KillProcessName("mjntips_calc", 0);
  dds3KillProcessName("mjntips_calc", 0);
}

// 0x1d398a0
dds3ProcessID_t *mjnTipsProcessStart(void) {
  dds3ProcessID_t *v1;
  Il2CppObject *v3;
  dds3ProcessFunc_t v4;
  shutdownfuncDelegate v5;
  dds3ProcessID_t *started;

  v1 = Allocate(dds3ProcessID_t);
  _ctor(v1, 0);
  v3 = TipsInit(mjn);
  v4 = Allocate(dds3ProcessFunc_t);
  _ctor(v4, 0, Method_Project_mjn_TipsProcess__, 0);
  v5 = Allocate(shutdownfuncDelegate);
  _ctor(v5, 0, Method_Project_mjn_TipsDestroy__, 0);
  started = dds3StartProcess("mjntips_calc", 1023, 0, 1, v4, v5, v3);
  TipsGlobalPID = started;
  return started;
}

// 0x1d39a40
s32 mjnTipsProcessCheck(void) {
  return dds3SearchProcessName("mjntips_calc") != 0;
}

// 0x1d40000
static mjn_tipsData_t *TipsInit(void) {
  void *p_Dependent;
  void *Dependent_local;
  void *Asset;
  void *v8;
  s64 size;
  mjn_tipsData_t *v10;
  s32 *SeqParent;
  s64 v12;
  MJNTIPS_CLASS *v13;
  s64 v14;
  MJNTIPS_CLASS *v15;
  s64 v16;
  MJNTIPS_CLASS *TblDate;
  MJNTIPS_CLASS *v18;
  MJNTIPS_CLASS **p_TIPSPAGE;
  SeqHandle_t *v22;

  p_Dependent = &Dependent;
  Dependent_local = p_Dependent;
  Load(Dependent_local, mjntipsDataAssetKey, mjntipsDataAssetKey);
  LoadSyncAll(_Ctrl_k__BackingField, 0);
  Asset = LoadAsset(_Ctrl_k__BackingField, mjntipsDataAssetKey, mjntipsDataAssetName, 0);
    v8 = Asset;
  else
    v8 = 0;
  size = (u32)v8->_arrPanel->_size;
  v10 = (mjn_tipsData_t *)Allocate(mjn_tipsData_t);
  _ctor(v10, 0);
  v10->nowHierarchy = 0;
  v10->MenuFade = 1;
  SeqParent = v10->SeqParent;
  *(u64 *)SeqParent = 0;
  *(u64 *)&SeqParent[2] = 0;
  v12 = NewSpecific(MJNTIPS_CLASS, size);
  v13 = v12;
  if ((s32)size >= 1)
  {
    v14 = 0;
    v15 = (v12 + 32);
    do
    {
      TblDate = GetTblDate(v8, v14, 0);
      v18 = TblDate;
      v15 = v18;
      v16 = (s64)*v15++;
      ++v14;
      *(u32 *)(v16 + 36) = 0;
    }
    while (size != v14);
  }
  p_TIPSPAGE = &TIPSPAGE;
  *p_TIPSPAGE = v13;
  v22 = Allocate(SeqHandle_t);
  _ctor(v22, 0);
  Unload(Dependent, mjntipsDataAssetKey, 0);
  ButtonGuideDispSet("DBOOK01", 0, 90);
  ButtonGuideDispOn();
  return v10;
}

// 0x1d40400
static dds3ProcessFunc_t TipsProcess(dds3ProcessID_t *PID) {
  dds3ProcessID_t *v3;
  dds3ProcessFunc_t v5;
  dds3ProcessID_t *id;

  id = PID;
  dds3GetProcessData(id);
  v3 = id;
  StartEtcProcess(v3);
  mjnTipsMenuProcessStart();
  v5 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
  _ctor(v5, 0, Method_Project_mjn_TipsRootWaitCalcProcess__, 0);
  return v5;
}

// 0x1d40500
static void StartEtcProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  dds3ProcessID_t *v5;
  dds3ProcessFunc_t v6;
  dds3ProcessFunc_t v7;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  v5 = Allocate(dds3ProcessID_t);
  _ctor(v5, 0);
  dds3FadeIn(0, 0, 0, 0x1Eu);
  v6 = Allocate(dds3ProcessFunc_t);
  _ctor(v6, 0, Method_Project_mjn_TipsRootWaitDrawProcess__, 0);
  dds3StartProcess("mjntips_calc", 11028, 0, 0, v6, 0, ProcessData);
  v7 = Allocate(dds3ProcessFunc_t);
  _ctor(v7, 0, Method_Project_mjn_TipsRootWaitUpdateProcess__, 0);
  dds3StartProcess("mjntips_calc", 21009, 0, 0, v7, 0, ProcessData);
}

// 0x1d40d20
static void TipsDestroy(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  Il2CppObject *v4;
  mjn *v6;
  u32 *monitor;
  dds3ProcessID_t *v8;
  s32 v9;
  s64 i;
  Il2CppClass **v13;
  MJNTIPS_CLASS *TIPSPAGE_local;
  s64 v15;
  dds3ProcessID_t *id;

  id = PID;
  goto LABEL_3;
LABEL_14:
  goto LABEL_15;
LABEL_3:
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_14;
  v4 = ProcessData;
  dds3KillProcessName("mjntips_calc", 0);
  dds3KillProcessName("mjntips_calc", 0);
  monitor = v4[1].monitor;
  v8 = id;
  goto LABEL_10;
  do
  {
LABEL_28:
    v9 = monitor[4];
    if (!v9)
      break;
    v15 = *(u64 *)(*(u64 *)(*((u64 *)monitor + 3) + 8 * --v9 + 32) + 32);
    if (v15)
    {
      v6 = (*(v15 + 24))(*(u64 *)(v15 + 64), v8, *(u64 *)(v15 + 40));
      v9 = monitor[4] - 1;
    }
    monitor[4] = v9;
  }
  while (v9);
  goto LABEL_20;
LABEL_10:
  v9 = monitor[4];
  if (v9)
    goto LABEL_28;
LABEL_20:
  mjnTipsMenuProcessEnd();
  for (i = 0; ; ++i)
  {
    TIPSPAGE_local = TIPSPAGE;
    if (i >= SLODWORD(TIPSPAGE_local->max_length))
      break;
    TIPSPAGE_local = TIPSPAGE;
    v13 = &TIPSPAGE_local->obj.klass + i;
    HIDWORD(v13[4]->_1.byval_arg.data) = 0;
  }
LABEL_15:
  TipsGlobalPID = 0;
}

// 0x1d403b0
void mjnInitSeqHandle(SeqHandle_t *pSeqHandle) {
  SeqHandle_t *v2;

  v2 = Allocate(SeqHandle_t);
  _ctor(v2, 0);
}

// 0x1d41210
static void CalcSeqHandle(s32 Mode, SeqUnit_t *pSeqUnit, SeqHandle_t *pSeqHandle, dds3ProcessID_t *ID) {
  SeqHandle_t *v5;
  s32 UnitCnt;
  s32 v9;
  tipsInt32Delegate pDestroy;
  tipsInt32Delegate pInit;
  s64 v13;
  s64 v14;
  SeqUnit_t *pUnit;
  Il2CppClass **v16;
  s32 v17;
  SeqUnit_t *v18;
  void **v19;
  SeqUnit_t *v20;
  void *v21;
  SeqHandle_t *v22;
  SeqUnit_t *v23;
  char *v24;

  v5 = pSeqHandle;
  if (pSeqHandle)
  {
    if (Mode)
    {
      if ((u32)(Mode - 3) >= 0xFFFFFFFE)
      {
        UnitCnt = v5->UnitCnt;
        if (UnitCnt)
        {
          v9 = UnitCnt - 1;
          if (Mode == 1)
          {
            pDestroy = v5->pUnit[v9]->pDestroy;
            if (pDestroy)
            {
              (pDestroy->invoke_impl)(pDestroy->method_code, ID, pDestroy->ID);
              v5 = pSeqHandle;
              v9 = pSeqHandle->UnitCnt - 1;
            }
          }
          v5->UnitCnt = v9;
        }
      }
    }
    else
    {
      pInit = pSeqUnit->pInit;
      if (pInit)
      {
        if (pSeqUnit->pDestroy)
        {
          LODWORD(v13) = v5->UnitCnt;
          if ((s32)v13 < 1)
          {
LABEL_15:
            pUnit = v5->pUnit;
            v5->UnitCnt = v13 + 1;
            v16 = &pUnit->obj.klass + (s32)v13;
            v16[4] = pSeqUnit;
            if ((pSeqUnit->Stat & 0x20000) != 0)
            {
              v17 = pSeqHandle->UnitCnt;
              if (v17 >= 2)
              {
                v18 = pSeqHandle->pUnit;
                v19 = &v18[v17 - 1];
                v20 = v18[v17 - 2];
                v21 = *v19;
                sub_C80(v18, v20);
                *v19 = v20;
                v22 = pSeqHandle;
                v23 = pSeqHandle->pUnit;
                LODWORD(v19) = v22->UnitCnt;
                sub_C80(v23, v21);
                v24 = (char *)v23 + 8 * (s32)v19 - 16;
                *((u64 *)v24 + 4) = v21;
              }
            }
            (pSeqUnit->pInit->invoke_impl)(pSeqUnit->pInit->method_code, ID, pSeqUnit->pInit->method);
          }
          else
          {
            v14 = 0;
            while (!op_Equality(pSeqUnit->pInit, v5->pUnit[v14]->pInit, 0))
            {
              v5 = pSeqHandle;
              ++v14;
              v13 = pSeqHandle->UnitCnt;
              if (v14 >= v13)
                goto LABEL_15;
            }
          }
        }
        else
        {
          (pInit->invoke_impl)(pInit->method_code, ID, pInit->method);
        }
      }
    }
  }
}

// 0x1d40f90
void mjnSeqDestroyAll(SeqHandle_t *pSeqHandle, dds3ProcessID_t *ID) {
  s32 i;
  tipsInt32Delegate pDestroy;

  for (i = pSeqHandle->UnitCnt; i; pSeqHandle->UnitCnt = i)
  {
    i = pSeqHandle->UnitCnt;
    if (!i)
      break;
    pDestroy = pSeqHandle->pUnit[--i]->pDestroy;
    if (pDestroy)
    {
      (pDestroy->invoke_impl)(pDestroy->method_code, ID, pDestroy->method);
      i = pSeqHandle->UnitCnt - 1;
    }
  }
}

// 0x1d41410
dds3ProcessFunc_t mjnSeqChange(SeqHandle_t *pSeqHandle, SeqUnit_t *pSeqUnit, s32 Mode, dds3ProcessID_t *ID) {
  dds3ProcessFunc_t v5;
  SeqUnit_t *v9;
  s64 Stat;
  tipsInt32Delegate pCheck;
  s64 v12;
  s32 v13;
  char v14;
  dds3ProcessFunc_t pCalc;
  dds3ProcessFunc_t v18;
  s32 UnitCnt;
  SeqUnit_t *pLastSeqUnit;
  SeqUnit_t *v21;
  SeqUnit_t *v22;
  SeqUnit_t *v23;
  dds3ProcessFunc_t pUpdate;
  SeqHandle_t *pSeqHandlea;

  v5 = (dds3ProcessFunc_t)ID;
  pSeqHandlea = pSeqHandle;
  if (!v5)
    return v5;
  v9 = pSeqUnit;
  if (!pSeqUnit)
    return 0;
  Stat = v9->Stat;
  if ((Stat & 0x400000) != 0)
    return 0;
  if (Mode != 2)
  {
    if (Mode != 1)
    {
      if (!Mode)
      {
        pCheck = v9->pCheck;
        v12 = Stat | 0x100000;
        v9->Stat = v12;
        if (pCheck && (v13 = (pCheck->invoke_impl)(pCheck->method_code, v5, pCheck->ID), v9 = pSeqUnit, v12 = pSeqUnit->Stat, !v13))
        {
          if ((v12 & 0x10001) != 1)
          {
LABEL_34:
            if ((v12 & 1) == 0)
              return 0;
            v9->Stat = v12 | 0x400000;
            pCalc = v9->pCalc;
            goto LABEL_38;
          }
          v14 = 1;
        }
        else
        {
          if ((v12 & 0x10000) != 0)
            goto LABEL_36;
          v14 = 0;
        }
        CalcSeqHandle(0, v9, pSeqHandlea, v5);
        v9 = pSeqUnit;
        v12 = pSeqUnit->Stat | 0x10000;
        pSeqUnit->Stat = v12;
        if ((v14 & 1) != 0)
          goto LABEL_34;
LABEL_36:
        v18 = v9->pCalc;
        v9->Stat = v12 | 0x200000;
        return v18;
      }
      return 0;
    }
    if ((Stat & 0x100000) == 0)
      return 0;
    if ((Stat & 0x200000) != 0)
      return v9->pDraw;
    if ((Stat & 1) == 0)
      return 0;
    v9->Stat = Stat | 0x400000;
    pCalc = v9->pDraw;
LABEL_38:
    (pCalc->invoke_impl)(pCalc->method_code, v5, pCalc->ID);
    pSeqUnit->Stat &= ~0x400000u;
    return 0;
  }
  if ((Stat & 0x100000) == 0)
    return 0;
  if ((Stat & 0x200000) == 0)
  {
    if ((Stat & 1) == 0)
      return 0;
    v9->Stat = Stat | 0x400000;
    pCalc = v9->pUpdate;
    goto LABEL_38;
  }
  if ((Stat & 0x20000) != 0)
  {
    if ((Stat & 0x40000) != 0)
    {
      if (pSeqHandle)
      {
        UnitCnt = pSeqHandle->UnitCnt;
        if (UnitCnt)
          pSeqHandle->UnitCnt = UnitCnt - 1;
      }
    }
    else
    {
      CalcSeqHandle(1, 0, pSeqHandlea, v5);
    }
  }
  pLastSeqUnit = pSeqHandle->pLastSeqUnit;
  v21 = pLastSeqUnit[1];
  pSeqUnit->Stat &= 0xFFFFFFFF0000FFFFLL;
  sub_C80(pLastSeqUnit, v21);
  pLastSeqUnit[0] = v21;
  v22 = pSeqHandle->pLastSeqUnit;
  v23 = pSeqUnit;
  sub_C80(v22, pSeqUnit);
  v22[1] = v23;
  pUpdate = pSeqUnit->pUpdate;
  pSeqUnit = 0;
  return pUpdate;
}

// 0x1d416f0
void mjnSeqJump(SeqUnit_t *pCurrentSeqUnit, SeqUnit_t *pSeqUnit) {
  SeqUnit_t *v4;

  v4 = pSeqUnit;
  pCurrentSeqUnit = v4;
  pSeqUnit->Stat = LOWORD(pSeqUnit->Stat);
}

// 0x1d41730
void mjnSeqJumpAndFree(SeqUnit_t *pCurrentSeqUnit, SeqUnit_t *pSeqUnit) {
  SeqUnit_t *v4;

  v4 = pSeqUnit;
  pCurrentSeqUnit = v4;
  pSeqUnit->Stat = LOWORD(pSeqUnit->Stat) | 0x20000;
}

// 0x1d41770
s32 mjnAnimFunc(s32 mode) {
  void *p_mjnUImanager;
  s32 v8;

  if (mode == 1)
  {
    p_mjnUImanager = &mjnUImanager;
    v8 = 2;
    goto LABEL_14;
  }
  if (mode)
    return 1;
  if (MenuActive)
  {
    p_mjnUImanager = &mjnUImanager;
    v8 = 3;
LABEL_14:
    AnimSet(p_mjnUImanager, v8, 0);
    return 1;
  }
  AnimSet(mjnUImanager, 0, 0);
  MenuActive = 1;
  return 1;
}

// 0x1d40720
void mjnTipsMenuProcessStart(void) {
  tipsMenuWork_t *v1;
  dds3ProcessFunc_t v2;
  shutdownfuncDelegate v3;
  dds3ProcessID_t *started;
  dds3ProcessID_t *p_g_mainPID;
  dds3ProcessFunc_t v7;
  dds3ProcessID_t *v8;
  s32 *parentID;
  s64 v10;
  s64 v11;
  mjn_tipsMenuWork_t_ChildSave *child_save;
  mjn_tipsMenuWork_t_ChildSave *v14;
  s64 v16;
  s64 i;
  char *draw_text;
  s32 *id_save;
  s32 flag;
  s64 v24;
  s64 j;
  s64 v26;
  s32 v27;
  s32 v28;
  s64 v29;
  s32 *menu_draw;
  s64 v32;
  s32 *menu_After;
  s32 v34;
  s32 v35;
  s32 v36;
  s32 *menu_Before;
  u64 v38;
  u64 v39;
  s32 v40;
  s64 v41;
  s64 v42;
  s32 *v43;
  s64 v44;
  s32 v45;

  v1 = Allocate(tipsMenuWork_t);
  _ctor(v1, 0);
  v2 = Allocate(dds3ProcessFunc_t);
  _ctor(v2, 0, Method_Project_mjn_TipsMenuProcess__, 0);
  v3 = Allocate(shutdownfuncDelegate);
  _ctor(v3, 0, Method_Project_mjn_TipsMenuShutdown__, 0);
  started = dds3StartProcess("mjntips_menu_main", 1023, 0, 0, v2, v3, v1);
  p_g_mainPID = &g_mainPID;
  p_g_mainPID = started;
  v7 = Allocate(dds3ProcessFunc_t);
  _ctor(v7, 0, Method_Project_mjn_TipsDrawProcess__, 0);
  v8 = dds3StartProcess("mjntips_menu_draw", 11029, 0, 0, v7, 0, v1);
  v1->drawPID = v8;
  parentID = v1->parentID;
  if (SLODWORD(parentID->max_length) >= 1)
  {
    v10 = 0;
    v11 = 32;
    do
    {
      parentID[v10] = -1;
      child_save = v1->child_save;
      v14 = Allocate(mjn_tipsMenuWork_t_ChildSave);
      _ctor(v14, 0);
      *(Il2CppClass **)((char *)&child_save->obj.klass + v11) = v14;
      parentID = v1->parentID;
      ++v10;
      v11 += 8;
    }
    while (v10 < SLODWORD(parentID->max_length));
  }
  v16 = 32;
  for (i = 32; i != 544; i += 4)
  {
    draw_text = v1->draw_text;
    if (!*(Il2CppClass **)((char *)&draw_text->obj.klass + v16))
    {
      *(Il2CppClass **)((char *)&draw_text->obj.klass + v16) = 0;
      id_save = v1->id_save;
      *(u32 *)((char *)&v1->parent_save->obj.klass + i) = -1;
      *(u32 *)((char *)&id_save->obj.klass + i) = -1;
    }
    v16 += 8;
  }
  TipsActiveOnOff(mjnUImanager, 1, 0);
  SetCommand_New(v1);
  MenuAnimSetCtrl(mjnUImanager, 0, 0);
  PANELMAIN_SetAnim_new(mjnUImanager, 1, 0);
  flag = v1->flag;
  v1->cursor = 0;
  v1->cursor_old = 0;
  v1->cursor_ID = -1;
  v1->top = 0;
  v1->index = 0;
  v1->flag = flag | 4;
  Menu_CursorChange(mjnUImanager, 0, 1, 0);
  v24 = 0;
  goto LABEL_23;
  while (1)
  {
LABEL_23:
    if (v24 >= MENU_PARENT_MAX)
    {
      j = 0;
      goto LABEL_30;
    }
    if (v1->parentID[v24] == v1->cursor_old)
      break;
    ++v24;
    v1->cursor_parent = -1;
  }
  v1->cursor_parent = v24;
  for (j = 0; ; ++j)
  {
LABEL_30:
    if (j >= MENU_DRAW_MAX)
      break;
    v26 = (s64)v1->menu_draw + 4 * j;
    v27 = j + v1->top;
    *(u32 *)(v26 + 32) = v27;
  }
  v28 = -1;
  v29 = 8;
  while (1)
  {
    if (v29 - 8 >= MENU_DRAW_MAX)
      break;
    menu_draw = v1->menu_draw;
    v32 = 4 * v29;
    menu_After = v1->menu_After;
    v34 = v28 + menu_draw[0];
    --v28;
    if (v34 < 1)
      v34 = -1;
    *((u32 *)&v1->menu_Before->obj.klass + v29) = v34;
    v35 = v29++ + menu_draw[11];
    v36 = v35 - 7;
    if (v36 >= v1->menu_num)
      v36 = -1;
    *(u32 *)((char *)&menu_After->obj.klass + v32) = v36;
  }
  menu_Before = v1->menu_Before;
  v38 = (u32)menu_Before[0];
  if ((v38 & 0x80000000) == 0)
  {
    if ((s32)v38 < (s32)MENU_DRAW_MAX)
    {
      v39 = 0;
      while ((s64)v39 < MENU_DRAW_MAX)
      {
        if (v39 > v38)
          v40 = -1;
        else
          v40 = v39;
        v41 = (s64)v1->menu_Before + 4 * v39++;
        *(u32 *)(v41 + 32) = v40;
      }
      goto LABEL_59;
    }
    v42 = 0;
    v43 = &menu_Before[11];
    while (v42 < MENU_DRAW_MAX)
    {
      v44 = (s64)v1->menu_Before + 4 * v42++;
      v45 = *v43--;
      *(u32 *)(v44 + 32) = v45;
    }
  }
LABEL_59:
  selMenuSetScrollBar(mjnUImanager, v1->menu_num, 0);
  selMenuScrollBarMove(mjnUImanager, v1->menu_num, v1->top, 0);
}

// 0x1d41b20
static dds3ProcessFunc_t TipsMenuProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  s32 monitor_low;
  char v7;
  Il2CppObject *v10;
  dds3ProcessID_t *v11;
  dds3ProcessFunc_t v12;
  dds3ProcessID_t *v14;
  dds3ProcessID_t *klass;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
  switch (LOBYTE(ProcessData[2].klass))
  {
    case 0:
      if (CHECK_TRIG(4097, 1))
      {
        dds3FadeOut(0, 0, 0, 0x1Eu);
        LOWORD(ProcessData[2].monitor) = 0;
        LOBYTE(ProcessData[2].klass) = 1;
        SE(18);
      }
      else
      {
        v14 = id;
        mjnMenuCursorCtrl(v14);
        mjnPanelTextCtrl(id);
      }
      return 0;
    case 1:
      monitor_low = SLOWORD(ProcessData[2].monitor);
      if (!LOWORD(ProcessData[2].monitor))
      {
        HIDWORD(ProcessData[2].klass) &= ~4u;
        goto LABEL_29;
      }
      if (monitor_low < 2)
        goto LABEL_29;
      v7 = 2;
      goto LABEL_38;
    case 2:
      if (LOWORD(ProcessData[2].monitor))
      {
        goto LABEL_19;
      }
      klass = ProcessData[1].klass;
      itfMenuProcessEnd(klass);
LABEL_19:
      v10 = ProcessData + 1;
      v11 = ProcessData[1].klass;
      if (itfMenuProcessCheck(v11))
      {
        LOWORD(monitor_low) = ProcessData[2].monitor;
LABEL_29:
        LOWORD(ProcessData[2].monitor) = monitor_low + 1;
        return 0;
      }
      ProcessData[1].klass = 0;
      v7 = 3;
LABEL_38:
      LOWORD(ProcessData[2].monitor) = 0;
      LOBYTE(ProcessData[2].klass) = v7;
      return 0;
    case 3:
      v12 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
      _ctor(v12, 0, Method_Project_Kernel_DDS3_PROC_END__, 0);
      return v12;
    default:
      return 0;
  }
}

// 0x1d422d0
static void Release(tipsMenuWork_t *wk) {
  mjnResetUI();
  MenuAnimSetCtrl(mjnUImanager, 1, 0);
  PANELMAIN_SetAnim_new(mjnUImanager, 2, 0);
  MjnTipsMenuSetActive(mjnUImanager, 0, 0);
  TipsActiveOnOff(mjnUImanager, 0, 0);
  MenuActive = 0;
}

// 0x1d42530
static void TipsMenuShutdown(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  dds3ProcessID_t *p_monitor;
  dds3ProcessID_t *p_g_mainPID;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  Release(mjn);
  p_monitor = &ProcessData[1].monitor;
  if (!!dds3ExistProcess(p_monitor))
    dds3KillProcess(p_monitor, 0);
  p_monitor = 0;
  p_g_mainPID = &g_mainPID;
  p_g_mainPID = 0;
}

// 0x1d426c0
static dds3ProcessFunc_t TipsDrawProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  dds3ProcessID_t *v6;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  if ((BYTE4(ProcessData[2].klass) & 4) != 0)
  {
    v6 = id;
    mjnUniDrawMenu_New(v6);
  }
  return 0;
}

// 0x1d42a60
void mjnUniDrawMenu(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  dds3ProcessID_t *v5;
  Il2CppObject *v6;
  Il2CppObject *v7;
  s64 v9;
  s64 v10;
  s64 v12;
  s64 v13;
  dds3ProcessID_t *v15;
  s32 v16;
  s32 SelectID;
  s32 v21;
  s32 size;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
  v5 = &ProcessData[1];
  v6 = dds3GetProcessData(&ProcessData[1]);
  v7 = v6;
  if (!LOBYTE(ProcessData[2].klass) && (BYTE5(v6[13].klass) & 8) != 0)
  {
    if (SHIDWORD(v6[8].klass) >= 1)
    {
      v9 = 0;
      while (1)
      {
        v13 = *((u64 *)&v7[5].klass->_1.byval_arg.data + v9);
        if (!*(u64 *)(v13 + 24))
          goto LABEL_36;
        MENU_SetActive(mjnUImanager, v9, 1, 0);
        Menu_SetTaxt(mjnUImanager, v9, *(char **)(*(u64 *)(v13 + 24) + 48), 0);
        v15 = v5;
        v16 = *(u32 *)(*(u64 *)(v13 + 24) + 16);
        SelectID = itfMenuGetSelectID(v15);
        if (v16 == SelectID)
        {
          Menu_SetCursor(mjnUImanager, v9, 1, 0);
          if ((~*(u32 *)(*(u64 *)(v13 + 24) + 28) & 3) != 0)
            v21 = 2;
          else
            v21 = 1;
          goto LABEL_35;
        }
        else
        {
          Menu_SetCursor(mjnUImanager, v9, 0, 0);
          v21 = 2 * ((~*(u32 *)(*(u64 *)(v13 + 24) + 28) & 3) != 0);
          goto LABEL_35;
        }
LABEL_35:
        Menu_TextModeChange(mjnUImanager, v9, v21, 0);
LABEL_36:
        if (!v9)
        {
          TIPSMenu_SetScrollBar(mjnUImanager, TIPSPAGE[MenuParentID[*(s32 *)(*(u64 *)(v13 + 24) + 16)]]->childs, 0);
          v10 = *(s32 *)(*(u64 *)(v13 + 24) + 16);
          v12 = MenuParentID[v10];
          TIPSMenu_UpDateScrollBar(mjnUImanager, TIPSPAGE[v12]->childs, v12, v10, 0);
        }
        if (++v9 >= SHIDWORD(v7[8].klass))
          goto LABEL_43;
      }
    }
    LODWORD(v9) = 0;
LABEL_43:
    size = mjnUImanager->MenuList->_size;
    if ((s32)v9 < size)
    {
      do
      {
        MENU_SetActive(mjnUImanager, v9, 0, 0);
        LODWORD(v9) = v9 + 1;
      }
      while (size != (u32)v9);
    }
  }
}

// 0x1d42180
static void CallProcEnd(tipsMenuWork_t *wk) {
  dds3ProcessID_t *menuPID;

  menuPID = wk->menuPID;
  itfMenuProcessEnd(menuPID);
}

// 0x1d42210
static u8 CheckProcEnd(tipsMenuWork_t *wk) {
  tipsMenuWork_t *p_fields;
  dds3ProcessID_t *v5;
  dds3ProcessID_t *menuPID;

  menuPID = wk->menuPID;
  p_fields = &wk->fields;
  v5 = menuPID;
  if (itfMenuProcessCheck(v5))
    return 1;
  p_fields->menuPID = 0;
  return 0;
}

// 0x1d42ed0
void mjnTipsSetFocus(bool a_bFocus) {
  Il2CppObject *ProcessData;
  dds3ProcessID_t *klass;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    goto LABEL_11;
  goto LABEL_9;
  if (!ProcessData)
LABEL_9:
LABEL_11:
  klass = ProcessData[1].klass;
  itfMenuSetFlag(klass, 8, a_bFocus);
}

// 0x1d43020
static void SetCommand(tipsMenuWork_t *wk) {
  dds3ProcessID_t *menuPID;
  s64 i;
  MJNTIPS_CLASS *TIPSPAGE_local;
  s64 v7;
  char *v10;
  char *v11;
  s64 v12;
  s32 v14;
  char *v16;
  char *LocalizeText;
  itfMoverFunc_t v19;

  menuPID = wk->menuPID;
  itfMenuSetMenuTitle(menuPID, "", "");
  for (i = 5; ; ++i)
  {
    TIPSPAGE_local = TIPSPAGE;
    if (i - 4 >= SLODWORD(TIPSPAGE_local->max_length))
      break;
    v7 = *((u64 *)&TIPSPAGE_local->obj.klass + i);
    if (*(u32 *)(v7 + 48) == -1)
    {
      v16 = *(char **)(v7 + 56);
      LocalizeText = GetLocalizeText(v16, 1);
      SetRootMenu(menuPID, *(u32 *)(*((u64 *)&TIPSPAGE->obj.klass + i) + 16), LocalizeText);
      continue;
    }
    v10 = *(char **)(v7 + 56);
    v11 = GetLocalizeText(v10, 1);
    v12 = *((u64 *)&TIPSPAGE->obj.klass + i);
    SetMenu(menuPID, *(u32 *)(v12 + 16), *(u32 *)(v12 + 48), v11);
    v14 = *(u32 *)(*((u64 *)&TIPSPAGE->obj.klass + i) + 16);
    itfMenuSetFlagMenu(menuPID, v14, 64, 0);
  }
  v19 = Allocate(itfMoverFunc_t);
  _ctor(v19, 0, Method_Project_mjn_AnimFunc__, 0);
  itfMoverSetMenu(menuPID, v19);
  itfMenuSetMoveAppear(menuPID, 1);
  itfMenuSetMoveDisappear(menuPID, 1);
}

// 0x1d43680
static s32 CallFunc(void) {
  Il2CppObject *ProcessData;
  Il2CppObject *v4;
  dds3ProcessID_t *klass;

  ProcessData = dds3GetProcessData(g_mainPID);
  v4 = ProcessData;
  klass = ProcessData[1].klass;
  HIDWORD(v4[2].monitor) = itfMenuGetSelectID(klass);
  return 1;
}

// 0x1d43340
static void SetRootMenu(dds3ProcessID_t *PID, s32 MenuID, char *pStr) {
  itfMenuFunc_t v7;

  v7 = Allocate(itfMenuFunc_t);
  _ctor(v7, 0, Method_Project_mjn_CallFunc__, 0);
  itfMenuSetRootMenu(PID, MenuID, pStr, v7, "");
}

// 0x1d43430
static void SetMenu(dds3ProcessID_t *PID, s32 MenuID, s32 ParentMenuID, char *pStr) {
  s64 v12;
  MJNTIPS_CLASS *v14;
  itfMenuFunc_t v15;

  MenuParentID[MenuID] = ParentMenuID;
  v12 = ParentMenuID;
  SetIDTable(mjnUImanager, MenuID, ParentMenuID, TIPSPAGE[v12]->childs, 0);
  v14 = TIPSPAGE[v12];
  v14->childID[v14->childs++] = MenuID;
  v15 = Allocate(itfMenuFunc_t);
  _ctor(v15, 0, Method_Project_mjn_CallFunc__, 0);
  itfMenuSetMenu(PID, MenuID, ParentMenuID, pStr, v15, "");
}

// 0x1d435f0
static void SetFlagMenu(dds3ProcessID_t *PID, s32 MenuID, u32 Flag, bool Bool) {
  itfMenuSetFlagMenu(PID, MenuID, Flag, Bool);
}

// 0x1d41050
void mjnTipsMenuProcessEnd(void) {
  Il2CppObject *ProcessData;
  s32 klass_high;

  if (!g_mainPID)
    return;
  if (!dds3ExistProcess(g_mainPID))
    return;
  goto LABEL_15;
LABEL_19:
  goto LABEL_21;
LABEL_15:
  ProcessData = dds3GetProcessData(g_mainPID);
  if (ProcessData)
    goto LABEL_19;
LABEL_21:
  klass_high = HIDWORD(ProcessData[2].klass);
  if ((klass_high & 1) == 0)
  {
    LOWORD(ProcessData[2].monitor) = 0;
    HIDWORD(ProcessData[2].klass) = klass_high | 1;
    LOBYTE(ProcessData[2].klass) = 1;
  }
}

// 0x1d437c0
dds3ProcessFunc_t mjnTipsRootWaitCalcProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  SeqUnit_t *v6;
  SeqHandle_t *monitor;
  dds3ProcessID_t *v8;
  dds3ProcessFunc_t result;
  SeqUnit_t *v12;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  v6 = &ProcessData[2];
  monitor = ProcessData[1].monitor;
  v8 = id;
  result = mjnSeqChange(monitor, v6, 0, v8);
  if (!result)
  {
    v12 = tipsSeqUnit[1];
    v6 = v12;
    tipsSeqUnit[1]->Stat = LOWORD(tipsSeqUnit[1]->Stat);
    return 0;
  }
  return result;
}

// 0x1d43940
dds3ProcessFunc_t mjnTipsRootWaitDrawProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  dds3ProcessID_t *v5;
  Il2CppClass *klass;
  const char *name;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  v5 = id;
  if (!v5)
    return 0;
  klass = ProcessData[2].klass;
  if (!klass)
    return 0;
  name = klass->_1.name;
  if (((u64)name & 0x500000) != 0x100000)
    return 0;
  if (((u32)name & 0x200000) != 0)
    return (dds3ProcessFunc_t)klass->_1.this_arg.data;
  if (((u8)name & 1) == 0)
    return 0;
  klass->_1.name = ((u64)name | 0x400000);
  (*(klass->_1.this_arg.data + 3))(*((u64 *)klass->_1.this_arg.data + 8), v5, *((u64 *)klass->_1.this_arg.data + 5));
  ProcessData[2].klass->_1.name = ((u64)ProcessData[2].klass->_1.name & ~0x400000u);
  return 0;
}

// 0x1d43b00
dds3ProcessFunc_t mjnTipsRootWaitUpdateProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  SeqHandle_t *monitor;
  dds3ProcessID_t *v7;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  monitor = ProcessData[1].monitor;
  v7 = id;
  return mjnSeqChange(monitor, &ProcessData[2], 2, v7);
}

// 0x1d43c20
void mjnTipsMenuStart(void) {
  dds3ProcessID_t *ProcessData;
  dds3ProcessID_t *v4;
  s64 naturalAligment;
  dds3ProcessID_t *v6;
  s32 v7;

  ProcessData = dds3GetProcessData(g_mainPID);
  v4 = ProcessData;
  if (ProcessData)
  {
    LOBYTE(ProcessData[2].shutdownfunc) < (u32)naturalAligment || *((tipsMenuWork_t **)(ProcessData)[1].next + naturalAligment - 1) != tipsMenuWork_t;
  }
  v6 = ProcessData[2];
  itfMenuStart(ProcessData[2]);
  v7 = *((u32 *)v4 + 9);
  *((u32 *)v4 + 11) = 0;
  if ((v7 & 0x20) != 0)
    return;
  *((u32 *)v4 + 9) = v7 | 8;
  return;
}

// 0x1d43d90
s32 mjnGetSelectIndex(void) {
  s32 *ProcessData;

  if (!g_mainPID)
    return -1;
  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    return ProcessData[11];
  return ProcessData[11];
}

// 0x1d43ed0
s32 mjnGoParent(mjn_tipsData_t *data) {
  mjn_tipsData_t *v2;
  s32 *m_Items;
  s32 v4;
  s64 v5;

  v2 = data;
  m_Items = data->SeqParent;
  m_Items[data->nowHierarchy] = 1;
  v4 = v2->nowHierarchy - 1;
  v2->nowHierarchy = v4;
  v5 = v4;
  v2->nowSeq = m_Items[v5];
  return m_Items[v5];
}

// 0x1d43f10
void mjnSetSeqParent(mjn_tipsData_t *data, s32 parentID) {
  mjn_tipsData_t *v3;

  v3 = data;
  data->SeqParent[data->nowHierarchy] = parentID;
  ++v3->nowHierarchy;
}

// 0x1d43f40
s32 mjnCheckMovePrev(void) {
  dds3ProcessID_t *ProcessData;
  dds3ProcessID_t *v4;
  s64 naturalAligment;
  dds3ProcessID_t *v6;
  dds3ProcessID_t *v8;

  if (!g_mainPID)
    return 0;
  ProcessData = dds3GetProcessData(g_mainPID);
  v4 = ProcessData;
  if (ProcessData)
  {
    LOBYTE(ProcessData[2].shutdownfunc) < (u32)naturalAligment || *((tipsMenuWork_t **)(ProcessData)[1].next + naturalAligment - 1) != tipsMenuWork_t;
  }
  v6 = ProcessData[2];
  if (itfMenuGetCtrlType(ProcessData[2]) == 3)
    return 1;
  v8 = v4[2];
  return itfMenuGetCtrlType(v8) == 5;
}

// 0x1d44110
s32 mjnCheckPageEnable(s32 nowIndex, s32 nextIndex) {
  s64 v6;
  s32 *v9;
  char *v10;
  char *v11;
  s32 v14;
  s64 v15;

  v6 = (u32)(nextIndex + nowIndex);
  if ((s32)v6 < 1)
    return 0;
  if ((s32)v6 >= SLODWORD(TIPSPAGE->max_length))
    return 0;
  if (nextIndex == -1)
  {
    v14 = MenuParentID[nowIndex];
    while (1)
    {
      v15 = (u32)v6;
      if (v14 == MenuParentID[(u32)v6])
        break;
      LODWORD(v6) = v6 - 1;
      if ((s32)v15 <= 1)
        return 0;
    }
    return TIPSPAGE[v15]->parentID != -1;
  }
  else
  {
    if (nextIndex == 1)
    {
      while (1)
      {
        if (v6 >= SLODWORD(TIPSPAGE->max_length))
          break;
        v9 = MenuParentID;
        v10 = (char *)v9 + 4 * nowIndex;
        v11 = (char *)v9 + 4 * v6++;
        if (*((u32 *)v10 + 8) == *((u32 *)v11 + 8))
        {
          v15 = v6 - 1;
          return TIPSPAGE[v15]->parentID != -1;
        }
      }
    }
    return 0;
  }
}

// 0x1d44310
void mjnCallDrawBack(void) {
  Il2CppObject *ProcessData;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
  HIDWORD(ProcessData[2].klass) |= 0x10u;
}

// 0x1d44430
void mjnPageJump(mjn_tipsData_t *data, s32 nextSeq) {
  char *titleID;
  char *LocalizeText;

  data->nowSeq = nextSeq;
  PANELMAIN_SetAnim(mjnUImanager, 1, 0);
  titleID = TIPSPAGE[data->nowSeq]->titleID;
  LocalizeText = GetLocalizeText(titleID, 1);
  PANEL_SetTitleText(mjnUImanager, LocalizeText, 0);
}

// 0x1d44550
s32 mjnGetNextPage(mjn_tipsData_t *data) {
  s32 v3;
  s64 m_Items;
  s32 v6;
  s32 v7;
  s32 v8;
  MJNTIPS_CLASS *v10;

  v3 = data->nowSeq + 1;
  do
  {
    v8 = v3;
    if (v8 >= SLODWORD(TIPSPAGE->max_length))
      return 0;
    m_Items = MenuParentID;
    v6 = *(u32 *)(m_Items + 4 * data->nowSeq);
    v7 = *(u32 *)(m_Items + 4 * v8);
    v3 = v8 + 1;
  }
  while (v6 != v7);
  v10 = TIPSPAGE[v8];
  if (v10->parentID == -1)
    return 0;
  v10 = TIPSPAGE[v8];
  return v10->ID;
}

// 0x1d44690
s32 mjnGetPrevPage(mjn_tipsData_t *data) {
  s32 nowSeq;
  s32 v4;
  s64 m_Items;
  s32 v7;
  s32 v8;
  u32 v10;
  MJNTIPS_CLASS *v11;

  nowSeq = data->nowSeq;
  v4 = nowSeq - 1;
  do
  {
    if (v4 < 0)
      return 0;
    v10 = v4;
    nowSeq = data->nowSeq;
    m_Items = MenuParentID;
    v7 = *(u32 *)(m_Items + 4 * nowSeq);
    v8 = *(u32 *)(m_Items + 4 * v10);
    v4 = v10 - 1;
  }
  while (v7 != v8);
  v11 = TIPSPAGE[v10];
  if (v11->parentID == -1)
    return 0;
  v11 = TIPSPAGE[v10];
  return v11->ID;
}

// 0x1d447c0
void mjnDrawPANELMessage(MJNTIPS_CLASS *tips_) {
  PANEL_SetMessage(mjnUImanager, tips_->Text, 0);
}

// 0x1d44830
static s32 RootInit(dds3ProcessID_t *PID) {
  char *LocalizeText;
  dds3ProcessID_t *id;

  id = PID;
  dds3GetProcessData(id);
  ButtonGuideDispSet("DBOOK01", 0, 90);
  LocalizeText = GetLocalizeText(titleLabel, 1);
  SetKanban(mjnUImanager, LocalizeText, 0);
  return 1;
}

// 0x1d449b0
static s32 RootDestroy(dds3ProcessID_t *PID) {
  return 1;
}

// 0x1d449c0
static dds3ProcessFunc_t RootCalcProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  SeqHandle_t *monitor;
  dds3ProcessID_t *v7;
  dds3ProcessFunc_t result;
  dds3ProcessFunc_t v13;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  monitor = ProcessData[1].monitor;
  v7 = id;
  result = mjnSeqChange(monitor, &ProcessData[2], 0, v7);
  if (!result)
  {
    SelectIndex = mjnGetSelectIndex();
    if (mjnGetSelectIndex() != -1)
    {
      LODWORD(ProcessData[3].klass) = 0;
      return 0;
    }
    ButtonGuideDispOut();
    EndKanban(mjnUImanager, 0);
    v13 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
    _ctor(v13, 0, Method_Project_mjn_TipsMenuEndProcess__, 0);
    return v13;
  }
  return result;
}

// 0x1d44c10
static dds3ProcessFunc_t RootDrawProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  dds3ProcessID_t *v5;
  Il2CppClass *klass;
  const char *name;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  v5 = id;
  if (!v5)
    return 0;
  klass = ProcessData[2].klass;
  if (!klass)
    return 0;
  name = klass->_1.name;
  if (((u64)name & 0x500000) != 0x100000)
    return 0;
  if (((u32)name & 0x200000) != 0)
    return (dds3ProcessFunc_t)klass->_1.this_arg.data;
  if (((u8)name & 1) == 0)
    return 0;
  klass->_1.name = ((u64)name | 0x400000);
  (*(klass->_1.this_arg.data + 3))(*((u64 *)klass->_1.this_arg.data + 8), v5, *((u64 *)klass->_1.this_arg.data + 5));
  ProcessData[2].klass->_1.name = ((u64)ProcessData[2].klass->_1.name & ~0x400000u);
  return 0;
}

// 0x1d44dd0
static dds3ProcessFunc_t RootUpdateProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  SeqHandle_t *monitor;
  dds3ProcessID_t *v7;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  monitor = ProcessData[1].monitor;
  v7 = id;
  return mjnSeqChange(monitor, &ProcessData[2], 2, v7);
}

// 0x1d44ef0
static s32 HierarchyInit(dds3ProcessID_t *PID) {
  mjnTipsMenuStart();
  return 1;
}

// 0x1d44f70
static s32 HierarchyDestroy(dds3ProcessID_t *PID) {
  return 1;
}

// 0x1d44f80
static dds3ProcessFunc_t HierarchyCalcProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  Il2CppObject *v6;
  SeqHandle_t *monitor;
  dds3ProcessID_t *v8;
  dds3ProcessFunc_t v9;
  s32 SelectIndex;
  s64 v13;
  s64 v17;
  SeqUnit_t *tipsSeqUnit_local;
  s32 v19;
  s64 v20;
  Il2CppClass *v21;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  v6 = ProcessData + 2;
  monitor = ProcessData[1].monitor;
  v8 = id;
  v9 = mjnSeqChange(monitor, &ProcessData[2], 0, v8);
  if (v9)
    return v9;
  SelectIndex = mjnGetSelectIndex();
  if (SelectIndex != -1)
  {
    LODWORD(ProcessData[8].klass) = SelectIndex;
    *((u32 *)ProcessData[7].monitor + HIDWORD(ProcessData[7].klass)++ + 8) = 2;
    v13 = &tipsSeqUnit[3];
    goto LABEL_25;
  }
  if (!mjnCheckMovePrev())
    return v9;
  v17 = (s64)ProcessData[7].monitor + 32;
  tipsSeqUnit_local = tipsSeqUnit;
  *(u32 *)(v17 + 4 * SHIDWORD(ProcessData[7].klass)) = 1;
  v19 = HIDWORD(ProcessData[7].klass) - 1;
  HIDWORD(ProcessData[7].klass) = v19;
  v20 = 4 * v19;
  LODWORD(ProcessData[8].klass) = *(u32 *)(v17 + v20);
  v13 = &tipsSeqUnit_local[*(s32 *)(v17 + v20)];
LABEL_25:
  v21 = *(Il2CppClass **)v13;
  v6->klass = *(Il2CppClass **)v13;
  *(u64 *)(*(u64 *)v13 + 16) = *(u16 *)(*(u64 *)v13 + 16) | 0x20000;
  return 0;
}

// 0x1d451d0
static dds3ProcessFunc_t HierarchyDrawProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  dds3ProcessID_t *v5;
  Il2CppClass *klass;
  const char *name;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  v5 = id;
  if (!v5)
    return 0;
  klass = ProcessData[2].klass;
  if (!klass)
    return 0;
  name = klass->_1.name;
  if (((u64)name & 0x500000) != 0x100000)
    return 0;
  if (((u32)name & 0x200000) != 0)
    return (dds3ProcessFunc_t)klass->_1.this_arg.data;
  if (((u8)name & 1) == 0)
    return 0;
  klass->_1.name = ((u64)name | 0x400000);
  (*(klass->_1.this_arg.data + 3))(*((u64 *)klass->_1.this_arg.data + 8), v5, *((u64 *)klass->_1.this_arg.data + 5));
  ProcessData[2].klass->_1.name = ((u64)ProcessData[2].klass->_1.name & ~0x400000u);
  return 0;
}

// 0x1d45390
static dds3ProcessFunc_t HierarchyUpdateProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  SeqHandle_t *monitor;
  dds3ProcessID_t *v7;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  monitor = ProcessData[1].monitor;
  v7 = id;
  return mjnSeqChange(monitor, &ProcessData[2], 2, v7);
}

// 0x1d454b0
static s32 PANELInit(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  s32 klass;
  s32 v9;
  char **v11;
  u32 *monitor;
  char *titleID;
  char *LocalizeText;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  klass = ProcessData[8].klass;
  if (mjnCheckPageEnable(klass, 1))
    goto LABEL_15;
  v9 = ProcessData[8].klass;
  if (mjnCheckPageEnable(v9, -1))
    goto LABEL_15;
  goto LABEL_9001;
  if (mjnCheckPageEnable(v9, -1))
  {
LABEL_15:
    v11 = &"DBOOK03";
    goto LABEL_17;
  }
LABEL_9001:
  v11 = &"DBOOK02";
LABEL_17:
  ButtonGuideDispSet(*v11, 0, 90);
  monitor = ProcessData[6].monitor;
  monitor[8] = 0;
  monitor[5] = 0;
  mjnCallDrawBack();
  titleID = TIPSPAGE[SLODWORD(ProcessData[8].klass)]->titleID;
  LocalizeText = GetLocalizeText(titleID, 1);
  PANEL_SetTitleText(mjnUImanager, LocalizeText, 0);
  PANEL_TextScrollReset(mjnUImanager, 0);
  PANEL_SetActive(mjnUImanager, 1, 0);
  PANELMAIN_SetAnim(mjnUImanager, 1, 0);
  return 1;
}

// 0x1d457a0
static s32 PANELDestroy(dds3ProcessID_t *PID) {
  mjnCallDrawBack();
  PANEL_SetActive(mjnUImanager, 0, 0);
  PANEL_TextScrollReset(mjnUImanager, 0);
  return 1;
}

// 0x1d45870
static dds3ProcessFunc_t PANELCalcProcess(dds3ProcessID_t *PID) {
  mjn_tipsData_t *ProcessData;
  SeqHandle_t *SeqHandle;
  dds3ProcessID_t *v7;
  dds3ProcessFunc_t v9;
  Panel_t *CyousaPanel;
  f32 AlphaRate;
  Panel_t *v15;
  s32 NextPage;
  Panel_t *v21;
  s32 nowSeq;
  bool v23;
  s32 v26;
  Panel_t *v27;
  s32 v28;
  Panel_t *v31;
  f32 LCursorAlphaRate;
  s32 RCursorFadeFlag;
  Panel_t *v36;
  f32 RCursorAlphaRate;
  s32 v39;
  Panel_t *v41;
  Panel_t *v44;
  f32 UCursorAlphaRate;
  s32 DCursorFadeFlag;
  Panel_t *v49;
  f32 DCursorAlphaRate;
  bool v52;
  Panel_t *v53;
  s32 v56;
  Panel_t *v57;
  s32 v60;
  Panel_t *v64;
  s64 m_Items;
  SeqUnit_t *tipsSeqUnit_local;
  s32 v68;
  s64 v69;
  Il2CppClass **v70;
  SeqUnit_t *v71;
  mjn_tipsData_t *data;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  SeqHandle = ProcessData->SeqHandle;
  data = ProcessData;
  v7 = id;
  v9 = mjnSeqChange(SeqHandle, &ProcessData->pSeqUnit, 0, v7);
  if (!v9)
  {
    CyousaPanel = ProcessData->CyousaPanel;
    AlphaRate = CyousaPanel->AlphaRate;
    if (CyousaPanel->FadeFlag)
    {
      if (AlphaRate == 0.0)
      {
        if (CyousaPanel->RjumpFlag)
        {
          PANEL_TextScrollReset(mjnUImanager, 0);
          v15 = ProcessData->CyousaPanel;
          v15->FadeFlag = 0;
          v15->RjumpFlag = 0;
          NextPage = mjnGetNextPage(ProcessData);
LABEL_148:
          mjnPageJump(data, NextPage);
          return v9;
        }
        if (CyousaPanel->LjumpFlag)
        {
          PANEL_TextScrollReset(mjnUImanager, 0);
          v64 = ProcessData->CyousaPanel;
          v64->FadeFlag = 0;
          v64->LjumpFlag = 0;
          NextPage = mjnGetPrevPage(ProcessData);
          goto LABEL_148;
        }
        m_Items = ProcessData->SeqParent;
        tipsSeqUnit_local = tipsSeqUnit;
        *(u32 *)(m_Items + 4 * ProcessData->nowHierarchy) = 1;
        v68 = ProcessData->nowHierarchy - 1;
        ProcessData->nowHierarchy = v68;
        v69 = 4 * v68;
        ProcessData->nowSeq = *(u32 *)(m_Items + v69);
        v70 = &tipsSeqUnit_local->obj.klass + *(s32 *)(m_Items + v69);
        v71 = v70[4];
        ProcessData->pSeqUnit = v71;
        v70[4]->_1.name = (LOWORD(v70[4]->_1.name) | 0x20000);
        v21 = ProcessData->CyousaPanel;
        nowSeq = ProcessData->nowSeq;
        goto LABEL_42;
      }
      if (AlphaRate <= 0.0)
      {
        if (AlphaRate >= 0.0)
          goto LABEL_40;
      }
      else
      {
        AlphaRate = AlphaRate + -0.0625;
      }
      if (AlphaRate < 0.0)
        AlphaRate = 0.0;
      CyousaPanel->AlphaRate = AlphaRate;
LABEL_40:
      v21 = ProcessData->CyousaPanel;
      nowSeq = ProcessData->nowSeq;
      goto LABEL_42;
    }
    if (AlphaRate >= 1.0)
    {
      if (AlphaRate <= 1.0)
        goto LABEL_27;
    }
    else
    {
      AlphaRate = AlphaRate + 0.0625;
    }
    if (AlphaRate > 1.0)
      AlphaRate = 1.0;
    CyousaPanel->AlphaRate = AlphaRate;
LABEL_27:
    if (CHECK_TRIG(4097, 1))
    {
      ProcessData->CyousaPanel->FadeFlag = 1;
      ButtonGuideDispSet("DBOOK01", 0, 90);
      PANELMAIN_SetAnim(mjnUImanager, 2, 0);
      SE(1);
      v21 = ProcessData->CyousaPanel;
      nowSeq = ProcessData->nowSeq;
LABEL_42:
      v23 = mjnCheckPageEnable(nowSeq, -1) == 0;
      v26 = v23;
      v21->LCursorFadeFlag = v26;
      v27 = ProcessData->CyousaPanel;
      v28 = ProcessData->nowSeq;
      v27->RCursorFadeFlag = mjnCheckPageEnable(v28, 1) == 0;
      if (ProcessData->CyousaPanel->LCursorFadeFlag)
      {
        PANEL_ArrowAnim_L(mjnUImanager, 2, 0);
        v31 = ProcessData->CyousaPanel;
        LCursorAlphaRate = v31->LCursorAlphaRate;
        if (LCursorAlphaRate <= 0.0)
        {
          if (LCursorAlphaRate >= 0.0)
            goto LABEL_64;
        }
        else
        {
          LCursorAlphaRate = LCursorAlphaRate + -0.0625;
        }
        if (LCursorAlphaRate < 0.0)
          LCursorAlphaRate = 0.0;
      }
      else
      {
        PANEL_ArrowAnim_L(mjnUImanager, 1, 0);
        v31 = ProcessData->CyousaPanel;
        LCursorAlphaRate = v31->LCursorAlphaRate;
        if (LCursorAlphaRate >= 1.0)
        {
          if (LCursorAlphaRate <= 1.0)
            goto LABEL_64;
        }
        else
        {
          LCursorAlphaRate = LCursorAlphaRate + 0.0625;
        }
        if (LCursorAlphaRate > 1.0)
          LCursorAlphaRate = 1.0;
      }
      v31->LCursorAlphaRate = LCursorAlphaRate;
LABEL_64:
      RCursorFadeFlag = v31->RCursorFadeFlag;
      if (RCursorFadeFlag)
      {
        PANEL02_ArrowAnim_R(mjnUImanager, 2, 0);
        v36 = ProcessData->CyousaPanel;
        RCursorAlphaRate = v36->RCursorAlphaRate;
        if (RCursorAlphaRate <= 0.0)
        {
          if (RCursorAlphaRate >= 0.0)
            goto LABEL_81;
        }
        else
        {
          RCursorAlphaRate = RCursorAlphaRate + -0.0625;
        }
        if (RCursorAlphaRate < 0.0)
          RCursorAlphaRate = 0.0;
      }
      else
      {
        PANEL02_ArrowAnim_R(mjnUImanager, 1, 0);
        v36 = ProcessData->CyousaPanel;
        RCursorAlphaRate = v36->RCursorAlphaRate;
        if (RCursorAlphaRate >= 1.0)
        {
          if (RCursorAlphaRate <= 1.0)
            goto LABEL_81;
        }
        else
        {
          RCursorAlphaRate = RCursorAlphaRate + 0.0625;
        }
        if (RCursorAlphaRate > 1.0)
          RCursorAlphaRate = 1.0;
      }
      v36->RCursorAlphaRate = RCursorAlphaRate;
LABEL_81:
      v39 = PANEL_CheckTextScroll_U(mjnUImanager, 0);
      v36->UCursorFadeFlag = v39;
      v41 = ProcessData->CyousaPanel;
      v41->DCursorFadeFlag = PANEL_CheckTextScroll_D(mjnUImanager, 0);
      if (ProcessData->CyousaPanel->UCursorFadeFlag)
      {
        PANEL02_ArrowAnim_U(mjnUImanager, 1, 0);
        v44 = ProcessData->CyousaPanel;
        UCursorAlphaRate = v44->UCursorAlphaRate;
        if (UCursorAlphaRate >= 1.0)
        {
          if (UCursorAlphaRate <= 1.0)
            goto LABEL_100;
        }
        else
        {
          UCursorAlphaRate = UCursorAlphaRate + 0.0625;
        }
        if (UCursorAlphaRate > 1.0)
          UCursorAlphaRate = 1.0;
      }
      else
      {
        PANEL02_ArrowAnim_U(mjnUImanager, 2, 0);
        v44 = ProcessData->CyousaPanel;
        UCursorAlphaRate = v44->UCursorAlphaRate;
        if (UCursorAlphaRate <= 0.0)
        {
          if (UCursorAlphaRate >= 0.0)
            goto LABEL_100;
        }
        else
        {
          UCursorAlphaRate = UCursorAlphaRate + -0.0625;
        }
        if (UCursorAlphaRate < 0.0)
          UCursorAlphaRate = 0.0;
      }
      v44->UCursorAlphaRate = UCursorAlphaRate;
LABEL_100:
      DCursorFadeFlag = v44->DCursorFadeFlag;
      if (DCursorFadeFlag)
      {
        PANEL02_ArrowAnim_D(mjnUImanager, 1, 0);
        v49 = ProcessData->CyousaPanel;
        DCursorAlphaRate = v49->DCursorAlphaRate;
        if (DCursorAlphaRate >= 1.0)
        {
          if (DCursorAlphaRate <= 1.0)
            goto LABEL_117;
        }
        else
        {
          DCursorAlphaRate = DCursorAlphaRate + 0.0625;
        }
        if (DCursorAlphaRate > 1.0)
          DCursorAlphaRate = 1.0;
      }
      else
      {
        PANEL02_ArrowAnim_D(mjnUImanager, 2, 0);
        v49 = ProcessData->CyousaPanel;
        DCursorAlphaRate = v49->DCursorAlphaRate;
        if (DCursorAlphaRate <= 0.0)
        {
          if (DCursorAlphaRate >= 0.0)
            goto LABEL_117;
        }
        else
        {
          DCursorAlphaRate = DCursorAlphaRate + -0.0625;
        }
        if (DCursorAlphaRate < 0.0)
          DCursorAlphaRate = 0.0;
      }
      v49->DCursorAlphaRate = DCursorAlphaRate;
LABEL_117:
      if (CHECK_REP(4101, 1) && ProcessData->CyousaPanel->DCursorFadeFlag)
      {
        PANEL_TextScrollCtrl(mjnUImanager, 1, 0);
      }
      v52 = CHECK_REP(4100, 1);
      v53 = ProcessData->CyousaPanel;
      if (v52 && v53->UCursorFadeFlag)
      {
        PANEL_TextScrollCtrl(mjnUImanager, -1, 0);
        v53 = ProcessData->CyousaPanel;
      }
      if (v53->AlphaRate == 1.0)
      {
        if (CHECK_REP(4107, 1))
        {
          v56 = ProcessData->nowSeq;
          if (mjnCheckPageEnable(v56, 1))
          {
            v57 = ProcessData->CyousaPanel;
            v57->FadeFlag = 1;
            v57->RjumpFlag = 1;
            PANELMAIN_SetAnim(mjnUImanager, 2, 0);
            SE(4259852);
          }
        }
        if (CHECK_REP(4104, 1))
        {
          v60 = ProcessData->nowSeq;
          if (mjnCheckPageEnable(v60, -1))
          {
            *(u64 *)&ProcessData->CyousaPanel->FadeFlag = 0x100000001LL;
            PANELMAIN_SetAnim(mjnUImanager, 2, 0);
            SE(4259852);
          }
        }
      }
      return v9;
    }
    goto LABEL_40;
  }
  return v9;
}

// 0x1d46190
static dds3ProcessFunc_t PANELDrawProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  MJNTIPS_CLASS *v6;
  dds3ProcessID_t *v8;
  Il2CppClass *klass;
  const char *name;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  v6 = TIPSPAGE[SLODWORD(ProcessData[8].klass)];
  PANEL_SetMessage(mjnUImanager, v6->Text, 0);
  v8 = id;
  if (!v8)
    return 0;
  klass = ProcessData[2].klass;
  if (!klass)
    return 0;
  name = klass->_1.name;
  if (((u64)name & 0x500000) != 0x100000)
    return 0;
  if (((u32)name & 0x200000) != 0)
    return (dds3ProcessFunc_t)klass->_1.this_arg.data;
  if (((u8)name & 1) == 0)
    return 0;
  klass->_1.name = ((u64)name | 0x400000);
  (*(klass->_1.this_arg.data + 3))(*((u64 *)klass->_1.this_arg.data + 8), v8, *((u64 *)klass->_1.this_arg.data + 5));
  ProcessData[2].klass->_1.name = ((u64)ProcessData[2].klass->_1.name & ~0x400000u);
  return 0;
}

// 0x1d463b0
static dds3ProcessFunc_t PANELUpdateProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  SeqHandle_t *monitor;
  dds3ProcessID_t *v7;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  monitor = ProcessData[1].monitor;
  v7 = id;
  return mjnSeqChange(monitor, &ProcessData[2], 2, v7);
}

// 0x1d464d0
dds3ProcessFunc_t mjnTipsMenuEndProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  s32 klass;
  s32 v7;
  bool v8;
  dds3ProcessFunc_t v10;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  LODWORD(ProcessData[3].klass) = 1;
  klass = ProcessData[1].klass;
  if ((klass & 0x40) == 0)
  {
    HIDWORD(ProcessData[8].klass) = 0;
    LODWORD(ProcessData[1].klass) = klass | 0x40;
    return 0;
  }
  v7 = HIDWORD(ProcessData[8].klass) + 1;
  v8 = HIDWORD(ProcessData[8].klass) - 29 < 0;
  HIDWORD(ProcessData[8].klass) = v7;
  if (!(v8 ^ __OFSUB__(v7, 30) | (v7 == 30)))
    return 0;
  if (dds3FadeCheck())
    return 0;
  mjnTipsMenuProcessEnd();
  v10 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
  _ctor(v10, 0, Method_Project_Kernel_DDS3_PROC_END__, 0);
  return v10;
}

// 0x1d2d180
void mjnTehaiCursorMoveMain(void) {
  Work_t *v4;
  Player_t *v5;
  Work_t *v6;
  Work_t *v7;
  Player_t *v8;
  u32 tehaiNum;
  Work_t *v10;
  bool v11;
  Work_t *v15;
  s32 tehaiCursor;
  Player_t *v17;
  Work_t *v18;
  Work_t *v19;
  s32 v20;
  Player_t *v21;
  Work_t *v22;
  s64 v23;
  Work_t *v24;
  bool v26;
  u32 v27;
  s32 v29;
  bool v31;
  Work_t *v32;
  s32 v33;
  Work_t *v34;
  bool v36;
  s64 v37;
  Work_t *v38;

  if (!CHECK_REP(4102, 1))
    goto LABEL_60;
  if (Work->tehaiCursor < 1)
  {
LABEL_17:
    v4 = Work;
    if (v4->tehaiCursor)
      goto LABEL_31;
    if (v4->LastPush)
      goto LABEL_31;
    v4 = Work;
    v5 = v4->players[0];
    if ((v5->flag & 2) == 0)
    {
      v4 = Work;
      v5 = v4->players[0];
      v4->tehaiCursor = v5->tehaiNum - 1;
      goto LABEL_59;
    }
LABEL_31:
    v6 = Work;
    if (v6->tehaiCursor < 1)
    {
LABEL_37:
      v7 = Work;
      if (v7->tehaiCursor)
        goto LABEL_60;
      v7 = Work;
      if (!v7->LastPush)
      {
        v7 = Work;
        v8 = v7->players[0];
        if ((v8->flag & 2) != 0)
        {
          v8 = Work->players[0];
          tehaiNum = v8->tehaiNum;
          while ((--tehaiNum & 0x80000000) == 0)
          {
            v10 = Work;
            if (!v10->reachShanten[tehaiNum])
            {
              v10 = Work;
              v10->tehaiCursor = tehaiNum;
              mjnMatihaiTextDraw(tehaiNum);
              goto LABEL_13;
            }
          }
LABEL_14:
          goto LABEL_59;
        }
      }
      goto LABEL_60;
    }
    if ((v6->players[0]->flag & 2) == 0)
      goto LABEL_37;
    v11 = mjnTehaiCursorMove(0);
    if (v11)
      goto LABEL_57;
    goto LABEL_9000;
    if (v31)
    {
LABEL_57:
LABEL_59:
      p2sdPlaySE_Vol(4194307, 127);
      goto LABEL_60;
    }
LABEL_9000:
    v32 = Work;
    if (!v32->LastPush)
    {
      v32 = Work;
      v33 = v32->players[0]->tehaiNum;
      while (--v33 >= 0)
      {
        v34 = Work;
        if (!v34->reachShanten[v33])
        {
          v34 = Work;
          v34->tehaiCursor = v33;
          p2sdPlaySE_Vol(4194307, 127);
          mjnMatihaiTextDraw(Work->tehaiCursor);
          goto LABEL_60;
        }
      }
    }
    goto LABEL_60;
  }
  if ((Work->players[0]->flag & 2) != 0)
    goto LABEL_17;
  if (mjnTehaiCursorMove(0))
  {
LABEL_13:
    goto LABEL_14;
  }
LABEL_60:
  if (!CHECK_REP(4103, 1))
    goto LABEL_115;
  v15 = Work;
  tehaiCursor = v15->tehaiCursor;
  v17 = v15->players[0];
  if (tehaiCursor < v17->tehaiNum - 1)
  {
    if ((v17->flag & 2) == 0)
      goto LABEL_66;
    goto LABEL_9001;
    if ((Work->players[0]->flag & 2) == 0)
    {
LABEL_66:
      if (mjnTehaiCursorMove(1))
      {
LABEL_69:
        goto LABEL_70;
      }
      goto LABEL_115;
    }
LABEL_9001:
  }
  v18 = Work;
  if (v18->tehaiCursor == v18->players[0]->tehaiNum - 1)
  {
    if (v18->LastPush)
      goto LABEL_86;
    v18 = Work;
    if ((v18->players[0]->flag & 2) == 0)
    {
      v18 = Work;
      v18->tehaiCursor = 0;
      goto LABEL_114;
    }
  }
LABEL_86:
  v19 = Work;
  v20 = v19->tehaiCursor;
  v21 = v19->players[0];
  if (v20 < v21->tehaiNum - 1)
  {
    if ((v21->flag & 2) == 0)
      goto LABEL_91;
    v26 = mjnTehaiCursorMove(1);
    if (v26)
      goto LABEL_112;
    goto LABEL_9002;
    if (v36)
    {
LABEL_112:
      if (!v27)
LABEL_114:
      p2sdPlaySE_Vol(4194307, 127);
      goto LABEL_115;
    }
LABEL_9002:
    if (!Work->LastPush)
    {
      v37 = 0;
      while (1)
      {
        v38 = Work;
        if (v37 >= v38->players[0]->tehaiNum)
          break;
        v38 = Work;
        if (!v38->reachShanten[v37])
        {
          v38 = Work;
          v38->tehaiCursor = v37;
          mjnMatihaiTextDraw(v37);
          goto LABEL_114;
        }
        ++v37;
      }
    }
    goto LABEL_115;
  }
LABEL_91:
  v22 = Work;
  if (v22->tehaiCursor == v22->players[0]->tehaiNum - 1)
  {
    v22 = Work;
    if (!v22->LastPush)
    {
      v22 = Work;
      if ((v22->players[0]->flag & 2) != 0)
      {
        v23 = 0;
        while (1)
        {
          v24 = Work;
          if (v23 >= v24->players[0]->tehaiNum)
            break;
          v24 = Work;
          if (!v24->reachShanten[v23])
          {
            v24 = Work;
            v24->tehaiCursor = v23;
            mjnMatihaiTextDraw(v23);
            goto LABEL_69;
          }
          ++v23;
        }
LABEL_70:
        goto LABEL_114;
      }
    }
  }
LABEL_115:
  if (CHECK_PRESS(4102, 1) || CHECK_PRESS(4103, 1))
  {
    v29 = 1;
LABEL_118:
    Work->LastPush = v29;
    return;
  }
  else
  {
    v29 = 0;
    goto LABEL_118;
  }
  Work->LastPush = v29;
}

// 0x1d2da10
void mjnMatihaiTextDraw(s32 _cursor) {
  s64 v3;
  char *v4;
  s32 v5;
  s32 v7;
  char v8;
  s32 v9;
  s64 v10;
  s32 v11;
  s32 *Matihai;
  char *v13;
  char *v14;
  char *v17;
  char *v18;
  s64 i;
  char *v21;
  s32 *remainingMax;
  Player_t *players;
  s64 v26;
  char *v27;
  s32 v28;
  Work_t *v29;
  s32 v30;
  Work_t *v31;
  s32 v32;
  s32 *v33;
  s32 *yama136;
  s32 v35;
  char *v36;
  Work_t *v37;
  s64 j;
  char *v39;
  s64 v40;
  Work_t *v41;
  s32 *wanpai;
  s64 k;
  s64 v44;
  u32 v45;
  Work_t *v46;
  s32 *doraHyouji;
  s32 *v48;
  char *v51;
  Work_t *v52;
  s32 v53;
  void *v56;
  char *v57;
  s32 v59;

  v59 = 0;
  v3 = 0;
  v4 = "";
  v5 = 0;
  v7 = 0;
  v8 = 0;
  v9 = 0;
  v10 = cursor;
  while (1)
  {
    Matihai = Work->reaceMatihai[v10]->Matihai;
    if (v3 >= SLODWORD(Matihai->max_length))
      break;
    if (Matihai[v3] != 1)
      goto LABEL_10;
    v13 = NewSpecific(string, 5u);
    v13[0] = v4;
    v14 = " <";
    v13[1] = " <";
    v13[2] = spriteNameStr;
    v17 = HaiIndexName[v3];
    v13[3] = v17;
    v18 = ">";
    v13[4] = ">";
    v4 = Concat_54832608(v13, 0);
    for (i = 0; ; ++i)
    {
      remainingMax = Work->remainingMax;
      if (i >= SLODWORD(remainingMax->max_length))
        break;
      remainingMax = Work->remainingMax;
      v21 = (char *)remainingMax + 4 * i;
      *((u32 *)v21 + 8) = 0;
    }
    remainingMax = Work->remainingMax;
    players = Work->players;
    v26 = v3;
    v27 = (char *)remainingMax + 4 * v3;
    v28 = players[1]->tehai34[v3] + *((u32 *)v27 + 8);
    *((u32 *)v27 + 8) = v28;
    v29 = Work;
    remainingMax = v29->remainingMax;
    players = v29->players;
    v28 = remainingMax[v3];
    v30 = players[2]->tehai34[v26] + v28;
    remainingMax[v26] = v30;
    v31 = Work;
    remainingMax = v31->remainingMax;
    players = v31->players;
    v30 = remainingMax[v3];
    v32 = 0;
    remainingMax[v26] = players[3]->tehai34[v26] + v30;
    while (1)
    {
      v37 = Work;
      if (v32 >= v37->yamaNum)
        break;
      v37 = Work;
      v33 = v37->remainingMax;
      yama136 = v37->yama136;
      v35 = v32 + v37->tsumoIndex;
      ++v32;
      v36 = (char *)v33 + 4 * yama136[v35];
      ++*((u32 *)v36 + 8);
    }
    for (j = 0; ; ++j)
    {
      v41 = Work;
      wanpai = v41->wanpai;
      if (j >= SLODWORD(wanpai->max_length))
        break;
      v41 = Work;
      wanpai = v41->wanpai;
      v39 = (char *)wanpai + 4 * j;
      v40 = (s64)v41->remainingMax + 4 * *((s32 *)v39 + 8);
      ++*(u32 *)(v40 + 32);
    }
    for (k = 8; ; ++k)
    {
      v46 = Work;
      doraHyouji = v46->doraHyouji;
      if (k - 8 >= SLODWORD(doraHyouji->max_length))
        break;
      if (v45)
      {
        if (*((u32 *)&doraHyouji->obj.klass + k) == -1)
          continue;
      }
      else
      {
        if (*((u32 *)&Work->doraHyouji->obj.klass + k) == -1)
          continue;
      }
      v44 = (s64)Work->remainingMax
          + 4 * *((s32 *)&Work->doraHyouji->obj.klass + k);
      --*(u32 *)(v44 + 32);
    }
    if (v45)
    {
      v48 = v46->remainingMax;
      if (v48[v3] < 5)
        goto LABEL_61;
LABEL_68:
      v48 = Work->remainingMax;
      v48[v3] = 4;
LABEL_62:
      goto LABEL_63;
    }
    v48 = Work->remainingMax;
    if (v48[v3] >= 5)
      goto LABEL_68;
LABEL_61:
    goto LABEL_62;
LABEL_63:
    v51 = ToString_55996800(LODWORD(Work->remainingMax) + (s32)(v26 * 4) + 32, "D1", 0);
    MatiRemainingTextSet(mjnUImanager, v9, v51, 0);
    MatiRemainingObjSet(mjnUImanager, v9, 1, 0);
    v52 = Work;
    v59 += v52->remainingMax[v26];
    v11 = v52->reaceMatihai[v10]->Attention_hai[v26];
    switch (v11)
    {
      case 0:
        ++v5;
        if (v7 == 2)
          v11 = 3;
        else
          v11 = v7;
        break;
      case 1:
        if (v7 == 2)
          v53 = 3;
        else
          v53 = v7;
        ++v5;
        if ((v7 & 0xFFFFFFFE) == 2)
          v11 = v53;
        else
          v11 = 1;
        break;
      case 2:
        if (v7 == 3)
          v11 = 3;
        else
          v11 = 2;
        if (v5)
          v11 = 3;
        break;
      case 3:
        break;
      default:
        v11 = v7;
        break;
    }
    ++v9;
    v8 = 1;
    v7 = v11;
LABEL_10:
    ++v3;
  }
  if ((v8 & 1) != 0)
  {
    MatiObjCtrl(mjnUImanager, 1, 0);
    v56 = mjnUImanager;
    v57 = ToString_55996800((s32)&v59, "D1", 0);
    MatiRemainingTotalTextSet(v56, v57, 0);
    MatiTextSet(mjnUImanager, v4, 0);
    MatiAttentionTextSet(mjnUImanager, v7, 0);
    if (v9 <= 12)
    {
      do
      {
        MatiRemainingObjSet(mjnUImanager, v9++, 0, 0);
      }
      while (v9 != 13);
    }
  }
  else
  {
    MatiObjCtrl(mjnUImanager, 0, 0);
  }
}

// 0x1d2e690
void matiChack(void) {
  TehaiAnalysis_t *v1;
  s32 *v3;
  Player_t *v5;
  s32 tehaiNum;
  s64 v7;
  s64 v8;
  s64 v9;
  s64 v10;
  s64 v11;
  s32 v16;
  s32 v20;
  s64 i;
  s32 attentionFlag;
  s32 *Attention_hai;
  s32 v24;
  reaceMati *v27;
  u32 v28;
  s64 v29;
  s64 m_Items;
  s64 v31;
  s32 v32;
  s32 *tehai14;

  v1 = Allocate(TehaiAnalysis_t);
  _ctor(v1, 0);
  v3 = NewSpecific(s32, 0xEu);
  v5 = Work->players[0];
  tehaiNum = v5->tehaiNum;
  if (tehaiNum >= 1)
  {
    v7 = 0;
    v8 = &v3[0];
    do
    {
      while (2)
      {
        tehai14 = v5->tehai14;
        if (tehaiNum >= 1)
        {
          v10 = 0;
          do
          {
            v9 = v10++;
            *(u32 *)(v8 + v9 * 4) = tehai14[v9];
          }
          while (v10 < v5->tehaiNum);
        }
        v11 = tehai14[v7];
        --v5->tehai34[v11];
        --v5->tehaiNum;
        SetTehai14(0);
        AnalyzeTehaiNormal(0);
        AnalyzeTehaiChitoi(0);
        AnalyzeTehaiKokushi(0);
        SetBestAnalysisSub(v16, v1);
        Work->reachShanten[v7] = v1->shanten;
        v20 = CheckFuriten(0);
        for (i = 8; ; ++i)
        {
          if (i - 8 >= SLODWORD(Work->reaceMatihai[v7]->Matihai->max_length))
            break;
          v24 = CheckRon_Reach(i - 8, v5);
          if (v24 == 16)
          {
            v27 = Work->reaceMatihai[v7];
            Attention_hai = v27->Attention_hai;
            *((u32 *)&v27->Matihai->obj.klass + i) = 1;
            if (v20 == 1)
            {
              if (Work->attentionFlag != 2)
              {
                attentionFlag = 1;
                goto LABEL_17;
              }
            }
            attentionFlag = Work->attentionFlag;
          }
          else
          {
            attentionFlag = 0;
            Attention_hai = Work->reaceMatihai[v7]->Matihai;
          }
LABEL_17:
          *((u32 *)&Attention_hai->obj.klass + i) = attentionFlag;
        }
        ++v5->tehai34[v11];
        v28 = v5->tehaiNum;
        tehaiNum = v28 + 1;
        v5->tehaiNum = v28 + 1;
        if (v28 >= 0x7FFFFFFF)
        {
          if (++v7 >= tehaiNum)
            return;
          continue;
        }
        break;
      }
      v29 = 0;
      m_Items = v5->tehai14;
      do
      {
        v31 = 4 * v29++;
        *(u32 *)(m_Items + v31) = *(u32 *)(v8 + v31);
        v32 = v5->tehaiNum;
      }
      while (v29 < v32);
      tehaiNum = v5->tehaiNum;
      ++v7;
    }
    while (v7 < v32);
  }
}

// 0x1d466c0
bool mjnTehaiCursorMove(TEHAICURSORMOVE moving) {
  s32 tehaiCursor;
  s64 v5;
  Player_t *v7;
  s64 v9;
  Work_t *v10;
  s64 v11;
  bool v12;
  s32 v14;
  s64 v16;
  s64 v17;
  s32 v19;

  if (moving == 1)
  {
    LODWORD(v5) = Work->tehaiCursor;
    while (1)
    {
      while (1)
      {
        LODWORD(v5) = v5 + 1;
        v7 = Work->players[0];
        if ((s32)v5 >= v7->tehaiNum)
          return 0;
        break;
LABEL_11:
        if (!Work->reachShanten[(s32)v5])
          goto LABEL_31;
        goto LABEL_9000;
        if (!Work->reachShanten[(s32)v5])
        {
LABEL_31:
          Work->tehaiCursor = v5;
          mjnMatihaiTextDraw(v5);
          return 1;
        }
LABEL_9000:
      }
      if ((v7->flag & 2) != 0)
        goto LABEL_11;
      if (Work->phase != 12)
      {
        v19 = Work->tehaiCursor + 1;
LABEL_65:
        Work->tehaiCursor = v19;
        return 1;
      }
      v9 = 0;
      while (1)
      {
        if (v9 >= Work->kanNum)
          break;
        v10 = Work;
        v11 = (s64)v10->kanHai + 4 * v9++;
        if (v10->players[0]->tehai14[(s32)v5] == *(u32 *)(v11 + 32))
        {
LABEL_56:
          v10 = Work;
          v10->tehaiCursor = v5;
          return 1;
        }
      }
    }
  }
  if (!moving)
  {
    tehaiCursor = Work->tehaiCursor;
    v5 = (u32)(tehaiCursor - 1);
    if (tehaiCursor - 1 >= 0)
      goto LABEL_36;
    goto LABEL_9001;
    if (v14 - 1 >= 0)
    {
      while (1)
      {
LABEL_36:
        if ((Work->players[0]->flag & 2) != 0)
        {
          if (!Work->reachShanten[v5])
            goto LABEL_31;
        }
        else
        {
          if (Work->phase != 12)
          {
            v19 = Work->tehaiCursor - 1;
            goto LABEL_65;
          }
          v16 = 0;
          while (1)
          {
            if (v16 >= Work->kanNum)
              break;
            v10 = Work;
            v17 = (s64)v10->kanHai + 4 * v16++;
            if (v10->players[0]->tehai14[v5] == *(u32 *)(v17 + 32))
              goto LABEL_56;
          }
        }
        v12 = 0;
        if (v5-- <= 0)
          return v12;
      }
    }
LABEL_9001:
  }
  return 0;
}

// 0x1d146f0
void mjnTehaiCursorSet(void) {
  s64 v3;
  s32 v4;
  Player_t *v9;
  u32 v10;
  s64 i;
  Work_t *v12;
  Player_t *players;
  s64 v14;

  v3 = 0;
  v4 = 0;
  while (1)
  {
    v9 = Work->players[0];
    if (v3 >= v9->tehaiNum)
      break;
    if ((v9->flag & 2) == 0)
      goto LABEL_13;
    goto LABEL_9000;
    if ((Work->players[0]->flag & 2) == 0)
    {
LABEL_13:
      if (v10)
      {
        if (Work->phase != 12)
          goto LABEL_6;
      }
      else
      {
        if (Work->phase != 12)
          goto LABEL_6;
      }
      for (i = 0; ; ++i)
      {
        if (i >= Work->kanNum)
          break;
        v12 = Work;
        players = v12->players;
        v14 = (s64)v12->kanHai + 4 * i;
        if (players[0]->tehai14[v3] == *(u32 *)(v14 + 32))
          v4 = v3;
      }
      goto LABEL_7;
    }
LABEL_9000:
    if (v10)
    {
      if (!Work->reachShanten[v3])
        goto LABEL_30;
    }
    else
    {
      if (!Work->reachShanten[v3])
      {
LABEL_30:
        mjnMatihaiTextDraw(v3);
        MatiObjCtrl(mjnUImanager, 1, 0);
LABEL_6:
        v4 = v3;
      }
    }
LABEL_7:
    ++v3;
  }
  Work->tehaiCursor = v4;
}

// 0x1d14570
void mjnAfterConfirmationKan(s32 playerIndex) {
  Player_t *players;
  Player_t *v5;
  Player_t *v6;
  Player_t *v7;
  Player_t *v8;
  u32 v18;

  players = Work->players;
  v5 = players[0];
  v6 = players[1];
  v5->ippatsu = 0;
  v5->ichijunme = 0;
  v8 = players[2];
  v7 = players[3];
  v6->ippatsu = 0;
  v6->ichijunme = 0;
  v8->ippatsu = 0;
  v8->ichijunme = 0;
  v7->ippatsu = 0;
  v7->ichijunme = 0;
  goto LABEL_11;
  if (!v18)
LABEL_11:
  Kandora();
  Work->players[playerIndex]->rinshan = 1;
}

// 0x1d3f000
static void MenuInit(void) {
  Work_t *v1;
  Work_t *Work_local;
  DvlFaceSet *v5;
  void *Asset;
  s64 naturalAligment;
  void *v12;
  void *p_VisualDataTable;
  void *v16;
  void *v18;
  s64 v20;
  void *v21;
  void *p_TsumikomiDataTable;
  void *v25;
  void *v27;
  s64 v29;
  void *v30;
  void *p_TsumikomiProbTable;
  void *v34;
  void *v36;
  s64 v38;
  void *v39;
  void *v40;
  void *p_DoraProbDataTable;
  fileLoadAsset_Request *Asset__AllSceneAsync;
  fileLoadAsset_Request *p_UIsceneLoadReq;
  struct sdfVector4_t zeroVector_local;
  MenuWork_t *v51;
  MenuWork_t *p_MenuWork;
  MenuWork_t *MenuWork_local;
  s32 *selectID;
  dds3ProcessID_t *v56;
  s64 i;
  s64 v59;
  s32 v60;
  s64 v62;
  dds3ProcessID_t *v63;
  itfMenuDrawFunc_t v64;
  sdatUnitWork_t *v66;
  s32 devilid;
  dds3ProcessID_t *menuPID;
  char *v72;
  itfMenuFunc_t v73;
  dds3ProcessID_t *v75;
  char *v76;
  dds3ProcessFunc_t v78;
  shutdownfuncDelegate v79;
  struct sdfVector4_t v81;

  v1 = Allocate(Work_t);
  _ctor(v1, 0);
  Work = v1;
  Work_local = Work;
  v5 = Allocate(DvlFaceSet);
  _ctor(v5, 0);
  Work_local->dvlFaceSet = v5;
  Load(Dependent, mahjonUIKey, mahjonUIKey);
  Load(Dependent, mahjon_gKey, mahjon_gKey);
  Load(Dependent, mahjonKey, mahjonKey);
  Load(Dependent, "mahjon", "mahjon");
  LoadSyncAll(_Ctrl_k__BackingField, 0);
  Asset = LoadAsset(_Ctrl_k__BackingField, "mahjon", "mjnVisualDataTable", 0);
  if (!Asset)
  {
    VisualDataTable = 0;
    goto LABEL_32;
  }
  if (Asset->klass->_2.naturalAligment >= (u32)naturalAligment)
  {
    if (Asset->klass->_2.typeHierarchy[naturalAligment - 1] == Project_mjnVisualDataTable)
      v12 = Asset;
    else
      v12 = 0;
  }
  else
  {
    v12 = 0;
  }
  VisualDataTable = (void *)v12;
  p_VisualDataTable = &VisualDataTable;
  if (Asset->klass->_2.naturalAligment < (u32)naturalAligment)
  {
    goto LABEL_32;
  }
  if (Asset->klass->_2.typeHierarchy[naturalAligment - 1] == Project_mjnVisualDataTable)
    v16 = Asset;
  else
    v16 = 0;
LABEL_32:
  v18 = LoadAsset(_Ctrl_k__BackingField, "mahjon", "mjnTsumikomiDataTable", 0);
  if (!v18)
  {
    TsumikomiDataTable = 0;
    goto LABEL_50;
  }
  if (v18->klass->_2.naturalAligment >= (u32)v20)
  {
    if (v18->klass->_2.typeHierarchy[v20 - 1] == Project_mjnTsumikomiDataTable)
      v21 = v18;
    else
      v21 = 0;
  }
  else
  {
    v21 = 0;
  }
  TsumikomiDataTable = (void *)v21;
  p_TsumikomiDataTable = &TsumikomiDataTable;
  if (v18->klass->_2.naturalAligment < (u32)v20)
  {
    goto LABEL_50;
  }
  if (v18->klass->_2.typeHierarchy[v20 - 1] == Project_mjnTsumikomiDataTable)
    v25 = v18;
  else
    v25 = 0;
LABEL_50:
  v27 = LoadAsset(_Ctrl_k__BackingField, "mahjon", "mjnTsumikomiProbTable", 0);
  if (v27)
  {
    if (v27->klass->_2.naturalAligment >= (u32)v29)
    {
      if (v27->klass->_2.typeHierarchy[v29 - 1] == Project_mjnTsumikomiProbTable)
        v30 = v27;
      else
        v30 = 0;
    }
    else
    {
      v30 = 0;
    }
    TsumikomiProbTable = (void *)v30;
    p_TsumikomiProbTable = &TsumikomiProbTable;
    if (v27->klass->_2.naturalAligment >= (u32)v29)
    {
      if (v27->klass->_2.typeHierarchy[v29 - 1] == Project_mjnTsumikomiProbTable)
        v34 = v27;
      else
        v34 = 0;
      goto LABEL_68;
    }
  }
  else
  {
    TsumikomiProbTable = 0;
  }
LABEL_68:
  v36 = LoadAsset(_Ctrl_k__BackingField, "mahjon", "mjnDoraProbTable", 0);
  if (v36)
  {
    if (v36->klass->_2.naturalAligment >= (u32)v38)
    {
      if (v36->klass->_2.typeHierarchy[v38 - 1] == Project_mjnDoraProbDataTable)
        v39 = v36;
      else
        v39 = 0;
    }
    else
    {
      v39 = 0;
    }
    DoraProbDataTable = (void *)v39;
    p_DoraProbDataTable = &DoraProbDataTable;
    if (v36->klass->_2.naturalAligment >= (u32)v38)
    {
      if (v36->klass->_2.typeHierarchy[v38 - 1] == Project_mjnDoraProbDataTable)
        v40 = v36;
      else
        v40 = 0;
    }
    else
    {
      v40 = 0;
    }
  }
  else
  {
    v40 = 0;
    DoraProbDataTable = 0;
    p_DoraProbDataTable = &DoraProbDataTable;
  }
  Asset__AllSceneAsync = AllSceneAsync(mahjonUIKey, 0);
  p_UIsceneLoadReq = &UIsceneLoadReq;
  p_UIsceneLoadReq = Asset__AllSceneAsync;
  zeroVector_local = zeroVector;
  v81 = zeroVector;
  zeroVector_local = v81;
  BackColor = zeroVector_local;
  fclFilterOFF();
  dds3FadeIn(0, 0, 0, 0x1Eu);
  *(u64 *)&gMjnCount = 0;
  v51 = Allocate(MenuWork_t);
  _ctor(v51, 0);
  p_MenuWork = &MenuWork;
  p_MenuWork = v51;
  MenuWork_local = MenuWork;
  selectID = MenuWork_local->selectID;
  *(u64 *)selectID = -1;
  selectID[2] = -1;
  MenuWork_local->step = 0;
  MenuWork_local->selectNum = 0;
  MenuWork_local->PlayWithNarumi = 0;
  v56 = itfMenuProcessStart();
  MenuWork_local->menuPID = v56;
  itfMenuSetFlag(MenuWork->menuPID, 64, 1);
  for (i = 32; i != 288; i += 8)
  {
    v59 = *(s64 *)((char *)&GBWK->player->stock_id->obj.klass + i);
    if (Exists("new_devil"))
      continue;
    v60 = *(s16 *)(v59 + 22);
    sBtlIsDLCDevil(v60);
  }
  v62 = 0;
  MenuWork->stockNum = 0;
  while (2)
  {
    v66 = GBWK->player->stock_id[v62];
    if ((v66->flag & 1) != 0)
    {
      devilid = v66->devilid;
      goto LABEL_111;
LABEL_119:
      menuPID = MenuWork->menuPID;
      DIDTable[v62] = devilid;
      v72 = sdatDevilName(devilid, 0);
      v73 = Allocate(itfMenuFunc_t);
      _ctor(v73, 0, Method_Project_mjn_MenuPadFunc__, 0);
      itfMenuSetRootMenu(menuPID, v62, v72, v73, "");
      v63 = MenuWork->menuPID;
      v64 = Allocate(itfMenuDrawFunc_t);
      _ctor(v64, 0, Method_Project_mjn_MenuDrawFunc__, 0);
      itfMenuSetDrawFunc(v63, v62, v64, 0);
      itfMenuSetFlagMenu(MenuWork->menuPID, v62, 512, 1);
      ++MenuWork->stockNum;
      goto LABEL_9001;
LABEL_111:
      if (Exists("new_devil"))
        goto LABEL_119;
      if (!sBtlIsDLCDevil(devilid))
        goto LABEL_119;
LABEL_9001:
    }
    if (++v62 != 32)
      continue;
    break;
  }
  v75 = MenuWork->menuPID;
  v76 = strMenu[0];
  itfMenuSetMenuTitle(v75, v76, "");
  itfMenuSetDrawParam(MenuWork->menuPID, 32, 1);
  itfMenuSetFlag(MenuWork->menuPID, 8, 0);
  MenuMoveFlag = 0;
  itfMenuStart(MenuWork->menuPID);
  gMjnLoadModelID = -1;
  Init();
  MjnMsgSetFlag = 0;
  Create(0);
  fclLoadData("mjnMenuMsg.bmd", "mahjon", 1);
  Reset(0);
  MenuWork->step = 4;
  v78 = Allocate(dds3ProcessFunc_t);
  _ctor(v78, 0, Method_Project_mjn_MenuLoad__, 0);
  v79 = Allocate(shutdownfuncDelegate);
  _ctor(v79, 0, Method_Project_mjn_MenuDestroy__, 0);
  dds3StartProcess("mahjon menu process", 11031, 0, 0, v78, v79, 0);
  Unload(Dependent, "mahjon", 0);
  Unload(Dependent, mahjonUIKey, 0);
  Unload(Dependent, mahjon_gKey, 0);
  Unload(Dependent, mahjonKey, 0);
}

// 0x1d46ab0
s32 mjnSpriteLoadUnity(Work_t *pData) {
  s32 sprFlag;
  DvlFaceSet *klass;
  s32 v5;
  s32 result;

  sprFlag = pData->sprFlag;
  if ((sprFlag & 2) != 0)
    return 0;
  klass = pData->dvlFaceSet->klass;
  if ((sprFlag & 1) != 0)
  {
    if (((u32 (*)(void))klass->vtable._6_DvlFaceSprLoadCalcUnity.methodPtr)())
      return 1;
    result = 2;
    goto LABEL_9;
  }
  v5 = ((s64 (*)(void))klass->vtable._5_CreateFaceHandleList.methodPtr)();
  result = 1;
  if (!v5)
  {
LABEL_9:
    pData->sprFlag |= result;
    return 1;
  }
  return result;
}

// 0x1d46b40
dds3ProcessFunc_t mjnMenuLoad(dds3ProcessID_t *id) {
  s32 sprFlag;
  DvlFaceSet *klass;
  s32 v7;

  goto LABEL_3;
LABEL_9:
  MenuLoop(mjn);
  return 0;
LABEL_3:
  sprFlag = Work->sprFlag;
  if ((sprFlag & 2) != 0)
    goto LABEL_9;
  klass = Work->dvlFaceSet->klass;
  if ((sprFlag & 1) != 0)
  {
    if (((u32 (*)(void))klass->vtable._6_DvlFaceSprLoadCalcUnity.methodPtr)())
      return 0;
    v7 = 2;
  }
  else
  {
    if (((u32 (*)(void))klass->vtable._5_CreateFaceHandleList.methodPtr)())
      return 0;
    v7 = 1;
  }
  Work->sprFlag |= v7;
  return 0;
}

// 0x1d46c50
static dds3ProcessFunc_t MenuLoop(dds3ProcessID_t *id) {
  s32 step;
  s32 v11;
  s32 v12;
  s64 i;
  s64 v15;
  s32 v17;
  s32 v20;
  s32 v21;
  s32 v22;
  s32 StockDevilNums;
  MenuWork_t *v29;
  u32 v30;
  s32 cnt;
  s32 v32;
  void *Instance;
  void *v35;
  bool v41;
  dds3ProcessID_t *v44;
  s32 v45;
  MenuWork_t *v47;
  dds3ProcessID_t *v48;
  s32 v49;
  s32 v55;
  u32 v56;
  dds3ProcessID_t *v58;
  MenuWork_t *v60;
  s32 *selectID;
  dds3ProcessID_t *v63;
  MenuWork_t *v65;
  dds3ProcessID_t *v66;
  MenuWork_t *v68;
  void *v70;
  void *v71;
  MenuWork_t *v73;
  dds3ProcessID_t *menuPID;
  MenuWork_t *v76;
  dds3ProcessID_t *v77;
  fileLoadAsset_Request *v78;
  fileLoadAsset_Request *p_UIsceneLoadReq;
  DvlFaceSet *dvlFaceSet;
  DvlFaceSet *p_dvlFaceSet;

  if (UIsceneLoadReq)
  {
    if (!UIsceneLoadReq->isDone)
      return 0;
  }
  selMenu_men_SetActive(mjnUImanager, 1, 0);
  selMenu_men_AnimSet(mjnUImanager, 1, 0);
  selMenu_men_AnimSet_sub(mjnUImanager, 1, 0);
  cmpDrawEffect();
  MenuDraw();
  step = MenuWork->step;
  if (step == 4)
  {
    MenuWork->step = 3;
    return 0;
  }
  step = MenuWork->step;
  if (step == 3)
    goto LABEL_20;
  if (step)
  {
    if (step == 1)
    {
      cnt = MenuWork->cnt;
      if (cnt >= 15)
      {
        selMenu_men_SetActive(mjnUImanager, 0, 0);
        MenuStartMahjon();
        return 0;
      }
      cnt = MenuWork->cnt;
      v32 = cnt + 1;
LABEL_72:
      MenuWork->cnt = v32;
      return 0;
    }
    if (!v30)
    {
      step = MenuWork->step;
    }
    if (step == 2)
    {
      v45 = Update();
      if (v45 == 1)
      {
        v73 = MenuWork;
        v73->step = 0;
        menuPID = v73->menuPID;
        itfMenuSetFlag(menuPID, 8, 1);
        MJNMENU_GUIDEHELP_FLAG = 1;
        return 0;
      }
      if (!v45)
      {
        v76 = MenuWork;
        v76->step = 5;
        v76->cnt = 0;
        v77 = v76->menuPID;
        itfMenuSetFlag(v77, 8, 0);
        dds3FadeOut(0, 0, 0, 0xFu);
        MJNMENU_GUIDEHELP_FLAG = 1;
        return 0;
      }
      goto LABEL_131;
    }
    step = MenuWork->step;
    if (step != 5)
      return 0;
    v55 = MenuWork->cnt;
    if (v55 < 15)
    {
      if (!v56)
      {
        v55 = MenuWork->cnt;
      }
      v32 = v55 + 1;
      goto LABEL_72;
    }
    v78 = UIsceneLoadReq;
    if (v78)
    {
      v78 = UIsceneLoadReq;
      AllSceneUnload(v78, 0);
      p_UIsceneLoadReq = &UIsceneLoadReq;
      p_UIsceneLoadReq = 0;
    }
    if (dds3AdminiGetActiveSequence() != 17 && dds3AdminiGetActiveSequence() != 41)
    {
      dds3AdminiCallSequence(0, 0, 0);
    }
    dvlFaceSet = Work->dvlFaceSet;
    if (dvlFaceSet)
    {
      dvlFaceSet = Work->dvlFaceSet;
      (dvlFaceSet->klass->vtable._4_Clear.methodPtr)(dvlFaceSet, dvlFaceSet, dvlFaceSet->klass->vtable._4_Clear.method);
      p_dvlFaceSet = &Work->dvlFaceSet;
      p_dvlFaceSet = 0;
      Work->sprFlag &= 0xFFFFFFFC;
    }
    if (!op_Inequality(VisualDataTable, 0, 0))
    {
      goto LABEL_218;
    }
    VisualDataTable = 0;
LABEL_218:
    if (!op_Inequality(TsumikomiDataTable, 0, 0))
    {
      goto LABEL_221;
    }
    TsumikomiDataTable = 0;
LABEL_221:
    if (!op_Inequality(TsumikomiProbTable, 0, 0))
    {
      goto LABEL_224;
    }
    TsumikomiProbTable = 0;
LABEL_224:
    if (!op_Inequality(DoraProbDataTable, 0, 0))
    {
LABEL_227:
      gMjnRun = 0;
      dds3KillProcessName("mahjon menu process", 1);
      return 0;
    }
    DoraProbDataTable = 0;
    goto LABEL_227;
  }
  v41 = dds3FadeCheck();
  if (!v41)
  {
    if (!MenuMoveFlag)
    {
      v44 = MenuWork->menuPID;
      itfMenuSetFlag(v44, 8, 1);
      MenuMoveFlag = 1;
    }
  }
  mjnDrawMenuHD(mjn);
  v45 = Update();
  if (v45 == 1)
  {
    v58 = MenuWork->menuPID;
    itfMenuSetFlag(v58, 8, 1);
    v60 = MenuWork;
    selectID = v60->selectID;
    *(u64 *)selectID = -1;
    selectID[2] = -1;
    v60->selectNum = 0;
    selMenu_men_ResetTextMode(mjnUImanager, 0);
    itfMenuSetFlagMenu(MenuWork->menuPID, -1, 2, 1);
    return 0;
  }
  if (!v45)
  {
    v47 = MenuWork;
    v47->step = 1;
    v47->cnt = 0;
    v48 = v47->menuPID;
    itfMenuSetFlag(v48, 8, 0);
    dds3FadeOut(0, 0, 0, 0xFu);
    return 0;
  }
LABEL_131:
  if (v45 == -1)
  {
    MJNMENU_GUIDEHELP_FLAG = 0;
  }
  return 0;
LABEL_20:
  v11 = 0;
  v12 = 0;
  for (i = 4; (u32)i != 36; ++i)
  {
    v15 = *((u64 *)&GBWK->player->stock_id->obj.klass + i);
    if ((*(u8 *)(v15 + 16) & 1) == 0)
      break;
    v17 = *(s16 *)(v15 + 22);
    if (Exists("new_devil"))
      goto LABEL_35;
    if (!sBtlIsDLCDevil(v17))
      goto LABEL_35;
    goto LABEL_9004;
    if (!sBtlIsDLCDevil(v17))
    {
LABEL_35:
      GetLevelInID(TsumikomiDataTable, v17, 0);
      ++v12;
      v20 = i - v11 - 4;
      selMenu_men_SetID(mjnUImanager, v20, v20, 0);
      v21 = selMenu_men_SearchMenuBar_forID(mjnUImanager, v20, 0);
      if (v20 <= 15)
      {
        v22 = v21;
        selMenu_men_SetName(mjnUImanager, v17, v22, 0);
      }
      continue;
    }
LABEL_9004:
    ++v11;
  }
  if (!dds3FadeCheck())
  {
    if (!MjnMsgSetFlag)
    {
      if (!NarumiIsHere)
        goto LABEL_51;
      if (datGetStockDevilNums(0) >= 3)
      {
        v63 = MenuWork->menuPID;
        itfMenuSetFlag(v63, 8, 0);
        Reset(0);
        SetMessagePos(0);
        fclStart2(5, 0, 0);
        MjnMsgSetFlag = 1;
      }
    }
  }
LABEL_51:
  goto LABEL_53;
LABEL_54:
  if (NarumiIsHere)
    goto LABEL_55;
  v29 = MenuWork;
  v29->PlayWithNarumi = 0;
LABEL_79:
  v29->step = 0;
  v29->cnt = 0;
  Instance = get_Instance(0);
  ItfButtonGuideActive(Instance, 1, 0);
  v35 = get_Instance(0);
  ItfButtonGuideSet(v35, 0, 0);
  ButtonGuideDispSet("MJN01", 0, 90);
  ButtonGuideDispOn();
  MJNMENU_GUIDEHELP_FLAG = 1;
  goto LABEL_9006;
LABEL_53:
  goto LABEL_54;
LABEL_55:
  StockDevilNums = datGetStockDevilNums(0);
  if (StockDevilNums < 3)
  {
    v29 = MenuWork;
    v29->PlayWithNarumi = 1;
    goto LABEL_79;
  }
  if (MjnMsgSetFlag)
  {
    v49 = Update();
    if (v49 == 1)
    {
      v65 = MenuWork;
      v65->PlayWithNarumi = 0;
      v65->step = 0;
      v65->cnt = 0;
      v66 = v65->menuPID;
    }
    else
    {
      if (v49)
      {
        if (v49 == -1)
        {
          MJNMENU_GUIDEHELP_FLAG = 0;
        }
        goto LABEL_84;
      }
      v68 = MenuWork;
      v68->PlayWithNarumi = 1;
      v68->step = 0;
      v68->cnt = 0;
      v66 = v68->menuPID;
    }
    itfMenuSetFlag(v66, 8, 1);
    MJNMENU_GUIDEHELP_FLAG = 1;
    v70 = get_Instance(0);
    ItfButtonGuideActive(v70, 1, 0);
    v71 = get_Instance(0);
    ItfButtonGuideSet(v71, 0, 0);
    ButtonGuideDispSet("MJN01", 0, 90);
    ButtonGuideDispOn();
  }
LABEL_9006:
LABEL_84:
  if (v12 <= 16)
  {
    selMenu_men_DelBar(mjnUImanager, v12, 0);
  }
  else
  {
  }
  selMenu_men_SetScrollBar(mjnUImanager, v12, 0);
  return 0;
}

// 0x1d489e0
void mjnCheckMenuButtonGuide(void) {
  s32 v4;
  bool v5;

  if (!CHECK_PRESS(4102, 1) && !CHECK_PRESS(4103, 1) && !CHECK_PRESS(4100, 1) && !CHECK_PRESS(4101, 1) && !CHECK_PRESS(4099, 1) && !CHECK_PRESS(4096, 1) && !CHECK_PRESS(4098, 1) && !CHECK_PRESS(4097, 1) && !CHECK_PRESS(4104, 1) && !CHECK_PRESS(4105, 1) && !CHECK_PRESS(4107, 1) && !CHECK_PRESS(4108, 1) && !CHECK_PRESS(4110, 1) && !CHECK_PRESS(4111, 1) && !CHECK_PRESS(4106, 1) && !CHECK_PRESS(4109, 1))
  {
LABEL_22:
    if (MJNMENU_GUIDEHELP_FLAG)
      goto LABEL_23;
    goto LABEL_30;
  }
  ButtonGuideDispOff();
  MJNMENU_BUTTONGUIDE_TIMER = 0;
  goto LABEL_22;
  if (MJNMENU_GUIDEHELP_FLAG)
  {
LABEL_23:
    v4 = MJNMENU_BUTTONGUIDE_TIMER + 1;
    v5 = MJNMENU_BUTTONGUIDE_TIMER - 119 < 0;
    MJNMENU_BUTTONGUIDE_TIMER = v4;
    if (v5 != __OFSUB__(v4, 120))
      return;
    MJNMENU_BUTTONGUIDE_TIMER = 120;
    ButtonGuideDispOn();
    return;
  }
LABEL_30:
  MJNMENU_BUTTONGUIDE_TIMER = 0;
}

// 0x1d48350
void mjnDrawMenuHD(dds3ProcessID_t *PID) {
  dds3ProcessID_t *p_menuPID;
  Il2CppObject *ProcessData;
  s64 v8;
  s64 v9;
  s32 v12;
  dds3ProcessID_t *menuPID;
  s32 SelectID;
  s32 v18;
  void *v20;
  void *v22;

  p_menuPID = &MenuWork->menuPID;
  ProcessData = dds3GetProcessData(p_menuPID);
  if (!ProcessData)
  if (!MenuWork->step && (BYTE5(ProcessData[13].klass) & 8) != 0)
  {
    if (SHIDWORD(ProcessData[8].klass) >= 1)
    {
      v8 = 0;
      while (1)
      {
        v9 = *((u64 *)&ProcessData[5].klass->_1.byval_arg.data + v8);
        if (!*(u64 *)(v9 + 24))
          goto LABEL_35;
        selMenu_men_SetName(mjnUImanager, DIDTable[*(s32 *)(*(u64 *)(v9 + 24) + 16)], v8, 0);
        v12 = *(u32 *)(*(u64 *)(v9 + 24) + 16);
        menuPID = MenuWork->menuPID;
        SelectID = itfMenuGetSelectID(menuPID);
        if (v12 == SelectID)
        {
          selMenu_men_CursorActive(mjnUImanager, v8, 1, 0);
          if ((~*(u32 *)(*(u64 *)(v9 + 24) + 28) & 3) != 0)
            v18 = 2;
          else
            v18 = 1;
          goto LABEL_34;
        }
        else
        {
          selMenu_men_CursorActive(mjnUImanager, v8, 0, 0);
          selMenu_men_SetTextMode_Ex(mjnUImanager, v8, 0, 0);
          v18 = 2 * ((~*(u32 *)(*(u64 *)(v9 + 24) + 28) & 3) != 0);
          goto LABEL_34;
        }
LABEL_34:
        selMenu_men_SetTextMode_Ex(mjnUImanager, v8, v18, 0);
LABEL_35:
        if (!v8)
        {
          v20 = mjnUImanager;
          selMenu_men_SetScrollBar(v20, MenuWork->stockNum, 0);
          selMenu_men_UpDateScrollBar(mjnUImanager, MenuWork->stockNum, *((u32 *)ProcessData[9].monitor + SBYTE4(ProcessData[5].monitor) + 8), 0);
        }
        if (++v8 >= SHIDWORD(ProcessData[8].klass))
          goto LABEL_44;
      }
    }
    LODWORD(v8) = 0;
LABEL_44:
    v22 = mjnUImanager;
    if ((s32)v8 >= v22->MenuList->_size)
      return;
    v22 = mjnUImanager;
    selMenu_men_DelBar(v22, v8, 0);
  }
}

// 0x1d48ce0
static void MenuDestroy(dds3ProcessID_t *id) {
  dds3ProcessID_t *menuPID;

  cmpDeleteEffect();
  End();
  MJNMENU_BUTTONGUIDE_TIMER = 0;
  MJNMENU_GUIDEHELP_FLAG = 0;
  GuideObjClr();
  menuPID = MenuWork->menuPID;
  itfMenuProcessEnd(menuPID);
  Delete(0);
  if (MenuWork)
  {
    MenuWork = 0;
  }
}

// 0x1d487e0
static void MenuStartMahjon(void) {
  s32 *selectID;
  s32 PlayWithNarumi;
  s32 v8;
  dds3ProcessFunc_t v10;
  shutdownfuncDelegate v11;

  dds3KillProcessName("mahjon menu process", 1);
  selectID = MenuWork->selectID;
  gMjnDevil0 = DIDTable[selectID[8]];
  gMjnDevil1 = DIDTable[selectID[9]];
  PlayWithNarumi = MenuWork->PlayWithNarumi;
  if (PlayWithNarumi)
  {
    v8 = -1;
  }
  else
  {
    selectID = MenuWork->selectID;
    v8 = DIDTable[selectID[10]];
  }
  gMjnDevil2 = v8;
  v10 = Allocate(dds3ProcessFunc_t);
  _ctor(v10, 0, Method_Project_mjn_BridgeLoop__, 0);
  v11 = Allocate(shutdownfuncDelegate);
  _ctor(v11, 0, Method_Project_mjn_BridgeDestroy__, 0);
  dds3StartProcess("mjn_bridge_process", 11031, 0, 0, v10, v11, 0);
}

// 0x1d48e30
static s32 MenuPadFunc(void) {
  u32 v4;
  MenuWork_t *v5;
  s32 v6;
  u32 v7;
  dds3ProcessID_t *v8;
  s32 v9;
  MenuWork_t *v10;
  dds3ProcessID_t *v11;
  s32 v12;
  MenuWork_t *v13;
  dds3ProcessID_t *v14;
  MenuWork_t *v15;
  dds3ProcessID_t *v16;
  MenuWork_t *MenuWork_local;
  s32 selectNum;
  MenuWork_t *v22;
  dds3ProcessID_t *v23;
  s32 v24;
  dds3ProcessID_t *v25;
  s32 SelectID;
  MenuWork_t *v27;
  dds3ProcessID_t *v28;
  s32 v29;
  dds3ProcessID_t *v30;
  s32 v31;
  MenuWork_t *v32;
  dds3ProcessID_t *v33;
  s32 v34;
  MenuWork_t *v35;
  dds3ProcessID_t *v36;
  s32 v37;
  MenuWork_t *v38;
  dds3ProcessID_t *v39;
  dds3ProcessID_t *menuPID;

  if (MenuWork->step)
    return 1;
  if (!CHECK_TRIG(4096, 1))
  {
    if (!CHECK_TRIG(4097, 1))
      return 1;
    MenuWork_local = MenuWork;
    selectNum = MenuWork_local->selectNum;
    if (selectNum < 1)
    {
      MenuWork_local = MenuWork;
      menuPID = MenuWork_local->menuPID;
      itfMenuSetFlag(menuPID, 8, 0);
      Reset(0);
      SetMessagePos(0);
      fclSetSelCancelPos(1);
      fclStart2(2, 0, 0);
      MenuWork->step = 2;
    }
    else
    {
      MenuWork_local = MenuWork;
      selectNum = MenuWork_local->selectNum;
      MenuWork_local->selectID[selectNum] = -1;
      --MenuWork_local->selectNum;
      selMenu_men_ResetTextMode(mjnUImanager, 0);
      v22 = MenuWork;
      v23 = v22->menuPID;
      v24 = v22->selectID[v22->selectNum];
      itfMenuSetFlagMenu(v23, v24, 2, 1);
    }
    v29 = 1;
    goto LABEL_79;
  }
  v5 = MenuWork;
  v6 = v5->selectNum;
  if (v6)
    goto LABEL_10;
  if (!v4)
  {
    v5 = MenuWork;
  }
  v25 = v5->menuPID;
  SelectID = itfMenuGetSelectID(v25);
  v27 = MenuWork;
  v27->selectID[v27->selectNum] = SelectID;
  v28 = v27->menuPID;
  ++v27->selectNum;
LABEL_46:
  itfMenuSetFlagMenu(v28, SelectID, 2, 0);
  v29 = 0;
LABEL_79:
  SE(v29);
  return 1;
LABEL_10:
  if (!v4)
  {
    v5 = MenuWork;
    v6 = v5->selectNum;
    if (v6 == 1)
      goto LABEL_12;
    goto LABEL_48;
  }
  if (v6 != 1)
  {
LABEL_48:
    if (!v7)
    {
      v5 = MenuWork;
      v6 = v5->selectNum;
    }
    if (v6 != 2)
      return 1;
    v5 = MenuWork;
    if (v5->PlayWithNarumi)
      return 1;
    v5 = MenuWork;
    v30 = v5->menuPID;
    v31 = itfMenuGetSelectID(v30);
    v32 = MenuWork;
    if (v31 == v32->selectID[0])
      return 1;
    v32 = MenuWork;
    v33 = v32->menuPID;
    v34 = itfMenuGetSelectID(v33);
    v35 = MenuWork;
    if (v34 == v35->selectID[1])
      return 1;
    v35 = MenuWork;
    v36 = v35->menuPID;
    v37 = itfMenuGetSelectID(v36);
    v38 = MenuWork;
    v38->selectID[v38->selectNum] = v37;
    v39 = v38->menuPID;
    ++v38->selectNum;
    itfMenuSetFlag(v39, 8, 0);
    Reset(0);
    SetMessagePos(0);
    fclSetSelCancelPos(1);
    fclStart2(1, 0, 0);
    SelectID = v37;
    v28 = MenuWork->menuPID;
    goto LABEL_46;
  }
LABEL_12:
  if (!v7)
  {
    v5 = MenuWork;
  }
  v8 = v5->menuPID;
  v9 = itfMenuGetSelectID(v8);
  v10 = MenuWork;
  if (v9 == v10->selectID[0])
    return 1;
  v10 = MenuWork;
  v11 = v10->menuPID;
  v12 = itfMenuGetSelectID(v11);
  v13 = MenuWork;
  v13->selectID[v13->selectNum] = v12;
  v14 = v13->menuPID;
  ++v13->selectNum;
  itfMenuSetFlagMenu(v14, v12, 2, 0);
  SE(0);
  v15 = MenuWork;
  if (!v15->PlayWithNarumi)
    return 1;
  v15 = MenuWork;
  v16 = v15->menuPID;
  itfMenuSetFlag(v16, 8, 0);
  Reset(0);
  SetMessagePos(0);
  fclSetSelCancelPos(1);
  fclStart2(1, 0, 0);
  itfMenuSetFlagMenu(MenuWork->menuPID, v12, 2, 0);
  return 1;
}

// 0x1d49530
static void MenuDrawFunc(s32 a_id, s32 a_x, s32 a_y, s32 a_z, u32 a_fontColor, u8 a_alphaRate) {
  dds3ProcessID_t *menuPID;
  sdfModelOt_t *v16;
  s32 v17;

  if (UIsceneLoadReq)
  {
    if (!UIsceneLoadReq->isDone)
      return;
  }
  menuPID = MenuWork->menuPID;
  if (itfMenuGetSelectID(menuPID) != a_id)
    return;
  if (cmpChkStatusModelLoadStat())
    return;
  if (gMjnLoadModelID != a_id)
  {
    v17 = DIDTable[a_id];
    Setup(v17, 0);
    gMjnLoadModelID = a_id;
    return;
  }
  v16 = ModelOt[0];
  cmpDrawStatusModel(v16);
  return;
}

// 0x1d497d0
static dds3ProcessFunc_t BridgeLoop(dds3ProcessID_t *id) {
  dds3ProcessFunc_t result;
  Work_t *Work_local;
  pacFileHandle_t *v9;
  pacFileHandle_t *pSummonData;
  s32 v12;

  if (gMjnCount < 5)
  {
    gMjnCount = gMjnCount + 1;
    return 0;
  }
  switch (gMjnLoadStat)
  {
    case 0:
      sndBgmLoadId_XF(20);
      Work_local = Work;
      v9 = pacLoad("fld_all", "SUMMON_M");
      Work_local->pSummonData = v9;
      gMjnLoadStat = 1;
      return 0;
    case 1:
      pSummonData = Work->pSummonData;
      if (!pacCheckEnd(pSummonData))
        return 0;
      if ((sndBgmStatus_XF() & 0xFFFFFFFE) != 2)
        return 0;
      gMjnLoadStat = 2;
      sndBgmPlay(0, 0);
      return 0;
    case 2:
      v12 = p2sdLoadCheckMidi(0x400000);
      if (v12 == 1)
      {
        gMjnLoadStat = 3;
        result = 0;
      }
      else
      {
        if (v12)
          return 0;
        p2sdLoadSMGFile(0x400000);
        result = 0;
      }
      break;
    case 3:
      dds3KillProcessName("mjn_bridge_process", 1);
      InitEx(gMjnDevil0, gMjnDevil1, gMjnDevil2);
      return 0;
    default:
      return 0;
  }
  return result;
}

// 0x1d49b60
static void BridgeDestroy(dds3ProcessID_t *id) {
  ;
}

// 0x1d47e00
static void MenuDraw(void) {
  char *v2;
  void *SpSprData;
  char *v7;
  char *LocalizeText;
  char *v9;
  s64 v10;
  s64 i;
  char *v12;
  char *v13;
  s32 v17;
  char *v18;
  void *SprData;
  void *v25;
  char *v26;
  void *v27;
  char *v28;
  char *v29;
  char *v30;

  if (MenuWork->PlayWithNarumi)
  {
    v2 = sdatDevilName(240, 0);
    SpSprData = GetSpSprData(mjnUImanager, 1, 0);
    v7 = strMenu[1];
    LocalizeText = GetLocalizeText(v7, 1);
    v9 = GetLocalizeText(strMenu[0], 1);
    MenuWin_men_SetActive(mjnUImanager, 1, 0, v2, LocalizeText, v9, SpSprData, 0);
    SetNarumiIconData(mjnUImanager, 0);
    MenuWin_men_SetNarumiLv(mjnUImanager, 0);
    v10 = 2;
  }
  else
  {
    v10 = 3;
  }
  for (i = 0; i != v10; MenuWin_men_SetLv(mjnUImanager, v17, i, 0))
  {
    while (1)
    {
      if (i < MenuWork->selectNum)
        goto LABEL_20;
LABEL_29:
      v18 = " ";
      SprData = GetSprData(mjnUImanager, -1, 0);
      v17 = -1;
      goto LABEL_32;
LABEL_38:
      v27 = mjnUImanager;
      v28 = strMenu[1];
      v29 = GetLocalizeText(v28, 1);
      v30 = GetLocalizeText(strMenu[0], 1);
      MenuWin_men_SetActive(v27, 1, i, v18, v29, v30, SprData, 0);
      MenuWin_men_SetLv(mjnUImanager, v17, i++, 0);
      if (i == v10)
        return;
    }
    if (i >= MenuWork->selectNum)
      goto LABEL_29;
LABEL_20:
    v17 = DIDTable[MenuWork->selectID[i]];
    v18 = sdatDevilName(v17, 0);
    SprData = GetSprData(mjnUImanager, DIDTable[MenuWork->selectID[i]], 0);
LABEL_32:
    if (!MenuWork->PlayWithNarumi)
      goto LABEL_38;
    v25 = mjnUImanager;
    v26 = strMenu[1];
    v12 = GetLocalizeText(v26, 1);
    v13 = GetLocalizeText(strMenu[0], 1);
    MenuWin_men_SetActive(v25, 1, ++i, v18, v12, v13, SprData, 0);
  }
}

// 0x1d418a0
static void SetCommand_New(tipsMenuWork_t *wk) {
  s64 v3;
  char *LocalizeText;
  char *v7;
  s64 v8;
  MJNTIPS_CLASS *TIPSPAGE_local;
  s64 v11;
  char *v13;
  s64 i;
  char *v15;
  char *v17;
  s64 v18;
  MJNTIPS_CLASS *v20;
  s64 v21;
  char *v23;

  v3 = 5;
  while (1)
  {
    TIPSPAGE_local = TIPSPAGE;
    if (v3 - 4 >= SLODWORD(TIPSPAGE_local->max_length))
      break;
    v11 = *((u64 *)&TIPSPAGE_local->obj.klass + v3);
    if (*(u32 *)(v11 + 48) != -1)
    {
      v13 = *(char **)(v11 + 56);
      LocalizeText = GetLocalizeText(v13, 1);
      v7 = mjnChangeTextPLTF(LocalizeText);
      v8 = *((u64 *)&TIPSPAGE->obj.klass + v3);
      SetMenu_New(wk, *(u32 *)(v8 + 16), *(u32 *)(v8 + 48), v7);
    }
    ++v3;
  }
  for (i = 5; ; ++i)
  {
    v20 = TIPSPAGE;
    if (i - 4 >= SLODWORD(v20->max_length))
      break;
    v21 = *((u64 *)&v20->obj.klass + i);
    if (*(u32 *)(v21 + 48) == -1)
    {
      *(u32 *)(v21 + 64) = 0;
      v23 = *(char **)(v21 + 56);
      v15 = GetLocalizeText(v23, 1);
      v17 = mjnChangeTextPLTF(v15);
      v18 = *((u64 *)&TIPSPAGE->obj.klass + i);
      SetRootMenu_New(wk, *(u32 *)(v18 + 16), *(u32 *)(v18 + 36), v17);
      continue;
    }
  }
}

// 0x1d49f20
static void SetRootMenu_New(tipsMenuWork_t *wk, s32 MenuID, s32 ChildNum, char *pStr) {
  s32 openStatus;

  openStatus = TIPSPAGE[MenuID]->openStatus;
  ParentMenu_SetTaxt(mjnUImanager, MenuID, pStr, 0);
  ChildMenuObjCtrl(mjnUImanager, MenuID, ChildNum, 0, 0);
  MenuObjSave(mjnUImanager, wk, MenuID, ChildNum, openStatus, pStr, 0);
}

// 0x1d49d70
static void SetMenu_New(tipsMenuWork_t *wk, s32 MenuID, s32 ParentMenuID, char *pStr) {
  s64 v12;
  s32 v13;
  MJNTIPS_CLASS *v14;
  s64 v15;
  Il2CppClass **v16;
  mjn_tipsMenuWork_t_ChildSave *v18;
  MJNTIPS_CLASS *v19;

  MenuParentID[MenuID] = ParentMenuID;
  v12 = ParentMenuID;
  v13 = ParentMenuID - 1;
  SetIDTable(mjnUImanager, MenuID, ParentMenuID, TIPSPAGE[v12]->childs, 0);
  v14 = TIPSPAGE[v12];
  v14->childID[v14->childs] = MenuID;
  ChildMenuTextChange(mjnUImanager, ParentMenuID, v14->childs, pStr, 0);
  v15 = ParentMenuID - 1;
  v16 = &wk->child_save[v15]->text->obj.klass
      + TIPSPAGE[v12]->childs;
  v16[4] = pStr;
  v18 = wk->child_save[v15];
  v18->parent = v13;
  v19 = TIPSPAGE[v12];
  v18->ID[v19->childs++] = MenuID;
}

// 0x1d4a030
static void SetCommondParent(tipsMenuWork_t *wk) {
  s64 i;
  char *LocalizeText;
  char *v8;
  s64 v9;
  MJNTIPS_CLASS *TIPSPAGE_local;
  s64 v12;
  char *v14;

  MenuObjReset(mjnUImanager, 0);
  for (i = 5; ; ++i)
  {
    TIPSPAGE_local = TIPSPAGE;
    if (i - 4 >= SLODWORD(TIPSPAGE_local->max_length))
      break;
    v12 = *((u64 *)&TIPSPAGE_local->obj.klass + i);
    if (*(u32 *)(v12 + 48) == -1)
    {
      v14 = *(char **)(v12 + 56);
      LocalizeText = GetLocalizeText(v14, 1);
      v8 = mjnChangeTextPLTF(LocalizeText);
      v9 = *((u64 *)&TIPSPAGE->obj.klass + i);
      SetRootMenu_New(wk, *(u32 *)(v9 + 16), *(u32 *)(v9 + 36), v8);
      continue;
    }
  }
}

// 0x1d41ef0
void mjnMenuCursorCtrl(dds3ProcessID_t *PID) {
  tipsMenuWork_t *ProcessData;
  tipsMenuWork_t *v4;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    return;
  v4 = ProcessData;
  if (ProcessData->menu_move)
  {
    if (MenuMoveCalc(ProcessData))
      return;
  }
  MenuCursorCtrlSub(v4);
}

// 0x1d4a9d0
static void MenuMoveStartCtrl(tipsMenuWork_t *wk) {
  s32 v3;
  MJNTIPS_CLASS *v5;
  s32 openStatus;
  s32 v12;
  s64 v13;
  s32 *parentID;
  il2cpp_array_size_t max_length;
  s32 *child_NumMax;
  u64 v17;
  s64 v18;
  __int128 v19;
  s32 *v20;
  s32 *v21;
  s64 v22;
  char v23;
  s64 v24;
  s64 v25;
  u64 v26;
  s64 v27;
  u32 *v28;
  u32 *v29;
  char *draw_text;
  s64 v31;
  s64 v32;
  _BOOL4 open_flag;
  void *v39;
  s32 v40;
  s32 v41;
  void *v42;
  s32 top;
  s32 *menu_drawOld;
  s32 v45;
  s32 v46;
  s32 v47;
  s32 v48;
  s32 v49;
  s32 v50;
  s32 v51;
  s32 v52;
  s32 v53;
  s32 v54;
  s32 v55;
  s32 v56;
  s32 v57;
  s32 v58;
  s32 *menu_Before;
  s32 v60;
  s32 v61;
  s32 *menu_After;
  s32 *v63;
  s32 v64;
  s32 v65;
  s32 v66;
  s32 v67;
  s32 v68;
  s32 v69;
  s32 v70;
  s32 v71;
  s32 v72;
  s32 v73;
  s32 v74;
  s32 v75;
  s32 v76;
  s32 v77;
  s32 v78;
  s32 v79;
  s32 v80;
  s32 v81;
  s32 v82;
  s32 v83;
  s32 v84;
  s32 v85;

  if (wk->cursor_parent != -1 && CHECK_TRIG(4096, 1))
  {
    v3 = wk->cursor_parent + 1;
    v5 = TIPSPAGE[v3];
    openStatus = v5->openStatus;
    if (openStatus)
    {
      MenuChildAnimSetCtrl(mjnUImanager, wk->cursor_parent, 1, 0);
      wk->open_flag = 0;
      TIPSPAGE[v3]->openStatus = 0;
    }
    else
    {
      MenuChildAnimSetCtrl(mjnUImanager, wk->cursor_parent, 0, 0);
      v12 = wk->top + 11;
      v13 = (s64)TIPSPAGE + 8 * v3;
      wk->open_flag = 1;
      *(u32 *)(*(u64 *)(v13 + 32) + 64) = 1;
      if (v12 == wk->cursor)
        wk->open_move = 1;
    }
    parentID = wk->parentID;
    *(u64 *)&wk->parentID_Befor = 0;
    wk->menu_num = 0;
    max_length = parentID->max_length;
    if ((s32)max_length >= 1)
    {
      child_NumMax = wk->child_NumMax;
      v17 = (u32)parentID->max_length;
      v18 = 0;
      if (v17 < 0x10)
        goto LABEL_26;
      if ((u64)((char *)child_NumMax - (char *)parentID) < 0x40)
        goto LABEL_26;
      *(u64 *)&v19 = -1;
      *((u64 *)&v19 + 1) = -1;
      v18 = v17 - (parentID->max_length & 0xF);
      v20 = &child_NumMax[12];
      v21 = &parentID[4];
      v22 = v18;
      do
      {
        *((_OWORD *)v21 - 1) = v19;
        *(_OWORD *)v21 = v19;
        v22 -= 16;
        *((_OWORD *)v21 + 1) = v19;
        *((_OWORD *)v21 + 2) = v19;
        v21 += 16;
        *((_OWORD *)v20 - 3) = 0u;
        *((_OWORD *)v20 - 2) = 0u;
        *((_OWORD *)v20 - 1) = 0u;
        *(_OWORD *)v20 = 0u;
        v20 += 16;
      }
      while (v22);
      if ((max_length & 0xF) != 0)
      {
LABEL_26:
        v23 = max_length - v18;
        v24 = v18 + 1;
        if ((v23 & 1) != 0)
        {
          v25 = v18;
          parentID[v25] = -1;
          child_NumMax[v25] = 0;
          v18 = v24;
        }
        if (v17 != v24)
        {
          v26 = v17 - v18;
          v27 = 4 * v18 + 36;
          v28 = ((char *)child_NumMax + v27);
          v29 = ((char *)parentID + v27);
          do
          {
            *(v29 - 1) = -1;
            v26 -= 2;
            *(v28 - 1) = 0;
            *v29 = -1;
            v29 += 2;
            *v28 = 0;
            v28 += 2;
          }
          while (v26);
        }
      }
    }
    draw_text = wk->draw_text;
    if (SLODWORD(draw_text->max_length) >= 1)
    {
      v31 = 0;
      v32 = 32;
      do
      {
        *(Il2CppClass **)((char *)&draw_text->obj.klass + v32) = 0;
        draw_text = wk->draw_text;
        ++v31;
        v32 += 8;
      }
      while (v31 < SLODWORD(draw_text->max_length));
    }
    SetCommondParent(wk);
    wk->menu_move = 1;
    open_flag = wk->open_flag;
    wk->menu_child = TIPSPAGE[v3]->childs;
    if (open_flag)
    {
      v39 = mjnUImanager;
      v40 = v3;
      v41 = 0;
    }
    else
    {
      v42 = mjnUImanager;
      v39 = v42;
      v40 = v3;
      v41 = 1;
    }
    MenuCursorAlpha(v39, v40, TIPSPAGE[v3]->childs, v41, 0);
    top = wk->top;
    menu_drawOld = wk->menu_drawOld;
    if (top >= wk->menu_num)
      top = -1;
    menu_drawOld[0] = top;
    v45 = wk->top;
    if (v45 + 1 < wk->menu_num)
      v46 = v45 + 1;
    else
      v46 = -1;
    menu_drawOld[1] = v46;
    v47 = wk->top + 2;
    if (v47 >= wk->menu_num)
      v47 = -1;
    menu_drawOld[2] = v47;
    v48 = wk->top + 3;
    if (v48 >= wk->menu_num)
      v48 = -1;
    menu_drawOld[3] = v48;
    v49 = wk->top + 4;
    if (v49 >= wk->menu_num)
      v49 = -1;
    menu_drawOld[4] = v49;
    v50 = wk->top + 5;
    if (v50 >= wk->menu_num)
      v50 = -1;
    menu_drawOld[5] = v50;
    v51 = wk->top + 6;
    if (v51 >= wk->menu_num)
      v51 = -1;
    menu_drawOld[6] = v51;
    v52 = wk->top + 7;
    if (v52 >= wk->menu_num)
      v52 = -1;
    menu_drawOld[7] = v52;
    v53 = wk->top + 8;
    if (v53 >= wk->menu_num)
      v53 = -1;
    menu_drawOld[8] = v53;
    v54 = wk->top + 9;
    if (v54 >= wk->menu_num)
      v54 = -1;
    menu_drawOld[9] = v54;
    v55 = wk->top + 10;
    if (v55 >= wk->menu_num)
      v55 = -1;
    menu_drawOld[10] = v55;
    v56 = wk->top + 11;
    if (v56 >= wk->menu_num)
      v56 = -1;
    menu_drawOld[11] = v56;
    if (wk->menu_num <= 12)
    {
      v57 = wk->top;
      wk->top = 0;
      wk->topOld = v57;
    }
    v58 = menu_drawOld[0] - 1;
    menu_Before = wk->menu_Before;
    if (v58 < 0)
      v58 = -1;
    menu_Before[0] = v58;
    v60 = menu_drawOld[11];
    if (v60 + 1 < wk->menu_num)
      v61 = v60 + 1;
    else
      v61 = -1;
    v63 = wk->menu_Before;
    menu_After = wk->menu_After;
    menu_After[0] = v61;
    v64 = menu_drawOld[0] - 2;
    if (v64 < 0)
      v64 = -1;
    menu_Before[1] = v64;
    v65 = menu_drawOld[11] + 2;
    if (v65 >= wk->menu_num)
      v65 = -1;
    menu_After[1] = v65;
    v66 = menu_drawOld[0] - 3;
    if (v66 < 0)
      v66 = -1;
    menu_Before[2] = v66;
    v67 = menu_drawOld[11] + 3;
    if (v67 >= wk->menu_num)
      v67 = -1;
    menu_After[2] = v67;
    v68 = menu_drawOld[0] - 4;
    if (v68 < 0)
      v68 = -1;
    wk->menu_Before[3] = v68;
    v69 = menu_drawOld[11] + 4;
    if (v69 >= wk->menu_num)
      v69 = -1;
    wk->menu_After[3] = v69;
    v70 = menu_drawOld[0] - 5;
    if (v70 < 0)
      v70 = -1;
    wk->menu_Before[4] = v70;
    v71 = menu_drawOld[11] + 5;
    if (v71 >= wk->menu_num)
      v71 = -1;
    wk->menu_After[4] = v71;
    v72 = menu_drawOld[0] - 6;
    if (v72 < 0)
      v72 = -1;
    wk->menu_Before[5] = v72;
    v73 = menu_drawOld[11] + 6;
    if (v73 >= wk->menu_num)
      v73 = -1;
    wk->menu_After[5] = v73;
    v74 = menu_drawOld[0] - 7;
    if (v74 < 0)
      v74 = -1;
    wk->menu_Before[6] = v74;
    v75 = menu_drawOld[11] + 7;
    if (v75 >= wk->menu_num)
      v75 = -1;
    wk->menu_After[6] = v75;
    v76 = menu_drawOld[0] - 8;
    if (v76 < 0)
      v76 = -1;
    wk->menu_Before[7] = v76;
    v77 = menu_drawOld[11] + 8;
    if (v77 >= wk->menu_num)
      v77 = -1;
    wk->menu_After[7] = v77;
    v78 = menu_drawOld[0] - 9;
    if (v78 < 0)
      v78 = -1;
    wk->menu_Before[8] = v78;
    v79 = menu_drawOld[11] + 9;
    if (v79 >= wk->menu_num)
      v79 = -1;
    wk->menu_After[8] = v79;
    v80 = menu_drawOld[0] - 10;
    if (v80 < 0)
      v80 = -1;
    wk->menu_Before[9] = v80;
    v81 = menu_drawOld[11] + 10;
    if (v81 >= wk->menu_num)
      v81 = -1;
    wk->menu_After[9] = v81;
    v82 = menu_drawOld[0] - 11;
    if (v82 < 0)
      v82 = -1;
    wk->menu_Before[10] = v82;
    v83 = menu_drawOld[11] + 11;
    if (v83 >= wk->menu_num)
      v83 = -1;
    wk->menu_After[10] = v83;
    v84 = menu_drawOld[0] - 12;
    if (v84 < 0)
      v84 = -1;
    v63[11] = v84;
    v85 = menu_drawOld[11] + 12;
    if (v85 >= wk->menu_num)
      v85 = -1;
    wk->menu_After[11] = v85;
    SE(0);
  }
}

// 0x1d4a1e0
static bool MenuMoveCalc(tipsMenuWork_t *wk) {
  s32 moveCount;
  s32 menu_child;
  s32 v7;
  s32 v8;
  s32 draw;
  s32 *menu_draw;
  s32 v11;
  s32 v12;
  s32 v13;
  s32 v14;
  s32 v15;
  s32 v16;
  s32 v17;
  s32 v18;
  s32 v19;
  s32 v20;
  s32 v21;
  s32 v22;
  s32 v23;
  s32 v24;
  s32 *menu_drawOld;
  s32 topOld;
  char v27;
  s64 max_length;
  s32 *m_Items;
  s32 v30;
  s32 menu_num;
  bool v32;
  bool v33;
  s32 top;
  s32 v35;
  s32 v36;
  s32 v37;
  s32 v38;
  s32 v39;
  s32 v40;
  s32 v41;
  s32 v42;
  s32 v43;
  s32 v44;
  s32 v45;
  s32 v48;
  s32 v49;
  s32 v50;
  s32 v51;
  s32 v52;
  s32 v53;
  s32 v54;
  s32 v55;
  s32 v56;
  s32 v57;
  s32 v58;
  s32 v59;
  s32 v60;
  s32 v61;
  s32 v62;

  moveCount = wk->moveCount;
  if (moveCount <= 14)
  {
    if (wk->open_flag)
    {
      MenuPosCtrl(mjnUImanager, wk->cursor_parent, wk->menu_child, 0, 0);
      if (wk->open_move)
      {
        if (wk->menu_child >= 13)
          menu_child = 11;
        else
          menu_child = wk->menu_child;
        MenuPosCtrl(mjnUImanager, -1, menu_child, 1, 0);
        wk->menu_topChange = 1;
        wk->draw = menu_child;
      }
LABEL_85:
      ++wk->moveCount;
      return moveCount < 15;
    }
    menu_drawOld = wk->menu_drawOld;
    if ((s32)menu_drawOld->max_length < 1)
    {
      if (wk->menu_num > 12)
        goto LABEL_78;
    }
    else
    {
      topOld = 0;
      v27 = 0;
      max_length = (u32)menu_drawOld->max_length;
      m_Items = menu_drawOld;
      do
      {
        v30 = *m_Items++;
        if (v30 == -1)
        {
          menu_num = wk->menu_num;
          v32 = menu_num <= 12;
          v33 = menu_num > 12;
          if (!v32)
            ++topOld;
          v27 |= v33;
        }
        --max_length;
      }
      while (max_length);
      if (wk->menu_num > 12)
      {
        if ((v27 & 1) != 0)
          goto LABEL_82;
LABEL_78:
        MenuPosCtrl(mjnUImanager, wk->cursor_parent, wk->menu_child, 1, 0);
        goto LABEL_85;
      }
    }
    topOld = wk->topOld;
LABEL_82:
    MenuPosCtrl(mjnUImanager, wk->cursor_parent, wk->menu_child, 1, 0);
    MenuPosCtrl(mjnUImanager, -1, topOld, 0, 0);
    wk->draw = topOld;
    wk->menu_topChange = 1;
    goto LABEL_85;
  }
  if (wk->menu_topChange)
  {
    v7 = wk->menu_num;
    if (v7 <= 12)
    {
      menu_draw = wk->menu_draw;
      if (wk->top >= v7)
        top = -1;
      else
        top = wk->top;
      menu_draw[0] = top;
      v35 = wk->top;
      if (v35 + 1 < wk->menu_num)
        v36 = v35 + 1;
      else
        v36 = -1;
      menu_draw[1] = v36;
      v37 = wk->top + 2;
      if (v37 >= wk->menu_num)
        v37 = -1;
      menu_draw[2] = v37;
      v38 = wk->top + 3;
      if (v38 >= wk->menu_num)
        v38 = -1;
      menu_draw[3] = v38;
      v39 = wk->top + 4;
      if (v39 >= wk->menu_num)
        v39 = -1;
      menu_draw[4] = v39;
      v40 = wk->top + 5;
      if (v40 >= wk->menu_num)
        v40 = -1;
      menu_draw[5] = v40;
      v41 = wk->top + 6;
      if (v41 >= wk->menu_num)
        v41 = -1;
      menu_draw[6] = v41;
      v42 = wk->top + 7;
      if (v42 >= wk->menu_num)
        v42 = -1;
      menu_draw[7] = v42;
      v43 = wk->top + 8;
      if (v43 >= wk->menu_num)
        v43 = -1;
      menu_draw[8] = v43;
      v44 = wk->top + 9;
      if (v44 >= wk->menu_num)
        v44 = -1;
      menu_draw[9] = v44;
      v45 = wk->top + 10;
      if (v45 >= wk->menu_num)
        v45 = -1;
      menu_draw[10] = v45;
      v24 = wk->top;
    }
    else
    {
      v8 = wk->top;
      draw = wk->draw;
      menu_draw = wk->menu_draw;
      if (wk->open_move)
      {
        v11 = v8 + draw;
        if (v11 >= v7)
          v12 = -1;
        else
          v12 = v11;
        menu_draw[0] = v12;
        v13 = wk->top + wk->draw;
        if (v13 + 1 < wk->menu_num)
          v14 = v13 + 1;
        else
          v14 = -1;
        menu_draw[1] = v14;
        v15 = wk->top + wk->draw + 2;
        if (v15 >= wk->menu_num)
          v15 = -1;
        menu_draw[2] = v15;
        v16 = wk->top + wk->draw + 3;
        if (v16 >= wk->menu_num)
          v16 = -1;
        menu_draw[3] = v16;
        v17 = wk->top + wk->draw + 4;
        if (v17 >= wk->menu_num)
          v17 = -1;
        menu_draw[4] = v17;
        v18 = wk->top + wk->draw + 5;
        if (v18 >= wk->menu_num)
          v18 = -1;
        menu_draw[5] = v18;
        v19 = wk->top + wk->draw + 6;
        if (v19 >= wk->menu_num)
          v19 = -1;
        menu_draw[6] = v19;
        v20 = wk->top + wk->draw + 7;
        if (v20 >= wk->menu_num)
          v20 = -1;
        menu_draw[7] = v20;
        v21 = wk->top + wk->draw + 8;
        if (v21 >= wk->menu_num)
          v21 = -1;
        menu_draw[8] = v21;
        v22 = wk->top + wk->draw + 9;
        if (v22 >= wk->menu_num)
          v22 = -1;
        menu_draw[9] = v22;
        v23 = wk->top + wk->draw + 10;
        if (v23 >= wk->menu_num)
          v23 = -1;
        menu_draw[10] = v23;
        v24 = wk->top + wk->draw;
      }
      else
      {
        v48 = v8 - draw;
        if (v48 >= v7)
          v49 = -1;
        else
          v49 = v48;
        menu_draw[0] = v49;
        v50 = wk->top - wk->draw;
        if (v50 + 1 < wk->menu_num)
          v51 = v50 + 1;
        else
          v51 = -1;
        menu_draw[1] = v51;
        v52 = wk->top - wk->draw + 2;
        if (v52 >= wk->menu_num)
          v52 = -1;
        menu_draw[2] = v52;
        v53 = wk->top - wk->draw + 3;
        if (v53 >= wk->menu_num)
          v53 = -1;
        menu_draw[3] = v53;
        v54 = wk->top - wk->draw + 4;
        if (v54 >= wk->menu_num)
          v54 = -1;
        menu_draw[4] = v54;
        v55 = wk->top - wk->draw + 5;
        if (v55 >= wk->menu_num)
          v55 = -1;
        menu_draw[5] = v55;
        v56 = wk->top - wk->draw + 6;
        if (v56 >= wk->menu_num)
          v56 = -1;
        menu_draw[6] = v56;
        v57 = wk->top - wk->draw + 7;
        if (v57 >= wk->menu_num)
          v57 = -1;
        menu_draw[7] = v57;
        v58 = wk->top - wk->draw + 8;
        if (v58 >= wk->menu_num)
          v58 = -1;
        menu_draw[8] = v58;
        v59 = wk->top - wk->draw + 9;
        if (v59 >= wk->menu_num)
          v59 = -1;
        menu_draw[9] = v59;
        v60 = wk->top - wk->draw + 10;
        if (v60 >= wk->menu_num)
          v60 = -1;
        menu_draw[10] = v60;
        v24 = wk->top - wk->draw;
      }
    }
    v61 = wk->menu_num;
    v62 = v24 + 11;
    wk->menu_topChange = 0;
    if (v62 >= v61)
      v62 = -1;
    menu_draw[11] = v62;
    wk->top = menu_draw[0];
  }
  selMenuSetScrollBar(mjnUImanager, wk->menu_num, 0);
  selMenuScrollBarMove(mjnUImanager, wk->menu_num, wk->top, 0);
  *(u16 *)&wk->open_move = 0;
  wk->moveCount = 0;
  return moveCount < 15;
}

// 0x1d4a860
static void MenuCursorCtrlSub(tipsMenuWork_t *wk) {
  bool v7;

  if (CHECK_REP(4100, 1))
  {
    CursorUp(wk);
  }
  else if (CHECK_REP(4101, 1))
  {
    CursorDown(wk);
  }
  else if (CHECK_REP(43526, 1))
  {
    CursorLeft(wk);
  }
  else
  {
    v7 = CHECK_REP(43527, 1);
    if (v7)
    {
      CursorRight(wk);
    }
    else
    {
      MenuMoveStartCtrl(wk);
    }
  }
}

// 0x1d4b110
static void CursorUp(tipsMenuWork_t *wk) {
  s32 cursor;
  bool v4;
  s32 v5;
  s32 top;
  s32 v7;
  s32 child_move;
  s32 v11;
  s64 v16;
  s32 *m_Items;
  s32 *id_save;
  int32x4_t v20;
  s32 *menu_draw;
  s32 v24;
  s32 v25;
  s64 v26;
  char *v27;

  cursor = wk->cursor;
  if (cursor)
  {
    v5 = cursor - 1;
    v4 = cursor - 1 < 0;
    top = wk->top;
    if (v4)
    {
      v5 = 0;
      v7 = wk->top;
      child_move = wk->child_move;
      v11 = -child_move;
      if (wk->move_flag)
        goto LABEL_14;
    }
    else
    {
      if (v5 < top)
      {
        v7 = top - 1;
        if (top <= 2147483635)
        {
          v24 = top + 12;
          v25 = top - 1;
          do
          {
            v26 = 0;
            while (4 * (MENU_PARENT_MAX & (u32)~(MENU_PARENT_MAX >> 31)) != v26)
            {
              v27 = (char *)wk->parentID + v26;
              v26 += 4;
              if (v25 == *((u32 *)v27 + 8))
                goto LABEL_8;
            }
            ++v25;
          }
          while (v25 < v24);
        }
LABEL_8:
        MenuCorsorPosCtrl(mjnUImanager, 1, 0, 0);
        child_move = wk->child_move;
        v11 = v5 - child_move;
        if (!wk->move_flag)
          goto LABEL_16;
LABEL_14:
        wk->move_flag = 0;
        goto LABEL_18;
      }
      v7 = wk->top;
      child_move = wk->child_move;
      v11 = v5 - child_move;
      if (wk->move_flag)
        goto LABEL_14;
    }
LABEL_16:
    if ((u32)(child_move + 1) <= 1)
      wk->child_move = 0;
LABEL_18:
    Menu_CursorChange(mjnUImanager, v11, 1, 0);
    wk->cursor_old = v5;
    MENU_PARENT_MAX = (u32)MENU_PARENT_MAX;
    if ((s32)MENU_PARENT_MAX >= 1)
    {
      v16 = 0;
      m_Items = wk->parentID;
      while (m_Items[v16] != v5)
      {
        id_save = wk->id_save;
        wk->cursor_parent = -1;
        ++v16;
        wk->cursor_ID = id_save[v5];
        if (MENU_PARENT_MAX == v16)
          goto LABEL_33;
      }
      wk->cursor_parent = v16;
      wk->cursor_ID = -1;
      wk->parentCursor_save = v16;
    }
LABEL_33:
    v20 = vdupq_n_s32(v7);
    menu_draw = wk->menu_draw;
    menu_draw[0] = v7;
    *(int32x4_t *)&menu_draw[1] = vaddq_s32(v20, (int32x4_t)xmmword_3D07320);
    *(int32x4_t *)&menu_draw[5] = vaddq_s32(v20, (int32x4_t)xmmword_3D01E30);
    menu_draw[11] = v7 + 11;
    *(int32x2_t *)&menu_draw[9] = vadd_s32((int32x2_t)v20.n128_u64[0], (int32x2_t)0xA00000009LL);
    DrawMenuBeforeAfterSave(wk);
    selMenuScrollBarMove(mjnUImanager, wk->menu_num, v7, 0);
    wk->change_flag = 0;
    wk->textChangeStep = 0;
    wk->cursor = v5;
    wk->top = v7;
    SE(3);
    return;
  }
}

// 0x1d4b4b0
static void CursorDown(tipsMenuWork_t *wk) {
  s32 cursor;
  s32 v4;
  s32 v5;
  s32 top;
  s32 v9;
  s64 v14;
  s32 *m_Items;
  s32 *id_save;
  int32x4_t v18;
  s32 *menu_draw;
  s32 v22;
  s64 v23;
  char *v24;

  cursor = wk->cursor;
  v4 = wk->menu_num - 1;
  if (cursor != v4)
  {
    v5 = cursor + 1;
    top = wk->top;
    if (cursor + 1 <= v4)
    {
      if (v5 - top >= 12)
      {
        if (top <= 2147483634)
        {
          v22 = wk->top;
          do
          {
            v23 = 0;
            while (4 * (MENU_PARENT_MAX & (u32)~(MENU_PARENT_MAX >> 31)) != v23)
            {
              v24 = (char *)wk->parentID + v23;
              v23 += 4;
              if (v22 == *((u32 *)v24 + 8))
                goto LABEL_9;
            }
            ++v22;
          }
          while (v22 < top + 13);
        }
LABEL_9:
        ++top;
        MenuCorsorPosCtrl(mjnUImanager, 1, 1, 0);
      }
    }
    else
    {
      v5 = wk->menu_num - 1;
    }
    v9 = v5 - wk->child_move;
    if (wk->move_flag)
      wk->move_flag = 0;
    Menu_CursorChange(mjnUImanager, v9, 1, 0);
    wk->cursor_old = v5;
    MENU_PARENT_MAX = (u32)MENU_PARENT_MAX;
    if ((s32)MENU_PARENT_MAX >= 1)
    {
      v14 = 0;
      m_Items = wk->parentID;
      while (m_Items[v14] != v5)
      {
        id_save = wk->id_save;
        wk->cursor_parent = -1;
        ++v14;
        wk->cursor_ID = id_save[v5];
        if (MENU_PARENT_MAX == v14)
          goto LABEL_29;
      }
      wk->cursor_parent = v14;
      wk->cursor_ID = -1;
      wk->parentCursor_save = v14;
    }
LABEL_29:
    v18 = vdupq_n_s32(top);
    menu_draw = wk->menu_draw;
    menu_draw[0] = top;
    *(int32x4_t *)&menu_draw[1] = vaddq_s32(v18, (int32x4_t)xmmword_3D07320);
    *(int32x4_t *)&menu_draw[5] = vaddq_s32(v18, (int32x4_t)xmmword_3D01E30);
    menu_draw[11] = top + 11;
    *(int32x2_t *)&menu_draw[9] = vadd_s32((int32x2_t)v18.n128_u64[0], (int32x2_t)0xA00000009LL);
    DrawMenuBeforeAfterSave(wk);
    selMenuScrollBarMove(mjnUImanager, wk->menu_num, top, 0);
    wk->change_flag = 0;
    wk->textChangeStep = 0;
    wk->cursor = v5;
    wk->top = top;
    SE(3);
    return;
  }
}

// 0x1d4b820
static void CursorLeft(tipsMenuWork_t *wk) {
  s32 top;
  s32 menu_num;
  s32 cursor;
  s32 *v6;
  s64 v7;
  s32 v8;
  bool v9;
  s64 v10;
  s32 v11;
  s32 v12;
  s64 v13;
  s64 v15;
  s32 v16;
  s32 *v17;
  s64 v19;
  s32 *v20;
  s32 v21;
  s64 v22;
  s32 v23;
  s32 v25;
  s32 v26;
  s64 v31;
  s32 *m_Items;
  s32 *id_save;
  int32x4_t v35;
  s32 *menu_draw;

  top = wk->top;
  menu_num = wk->menu_num;
  cursor = wk->cursor;
  v6 = NewSpecific(s32, 0xCu);
  if (cursor && menu_num >= 13)
  {
    v7 = v6;
    v8 = cursor - 12;
    v9 = v8 < 0 || top - 12 <= 0;
    v10 = 0;
    v11 = (top - 12) & ~((top - 12) >> 31) & ~(v8 >> 31);
    v12 = !v9;
    v13 = &v6[0];
    while (v10 < MENU_DRAW_MAX)
    {
      *(u32 *)(v13 + 4 * v10) = v11 + v10;
      ++v10;
    }
    v15 = 0;
    v16 = 0;
    v17 = (v7 + 32);
    while (1)
    {
      if (v15 >= MENU_DRAW_MAX)
        break;
      v19 = (u32)MENU_DRAW_MAX & ~((s32)MENU_DRAW_MAX >> 31);
      v20 = v17;
      while (v19)
      {
        --v19;
        v21 = *v20++;
        if (wk->menu_draw[v15] == v21)
          goto LABEL_18;
      }
      goto LABEL_9000;
      while (1)
      {
        if (v22 >= MENU_DRAW_MAX)
          break;
        v23 = v17[v22++];
        if (wk->menu_draw[v15] == v23)
        {
LABEL_18:
          ++v16;
          break;
        }
      }
LABEL_9000:
      ++v15;
    }
    if (!v12)
      v8 = 0;
    v25 = MENU_DRAW_MAX - v16;
    MenuCorsorPosCtrl(mjnUImanager, v25, 0, 0);
    v26 = v8 - wk->child_move;
    if (wk->move_flag)
      wk->move_flag = 0;
    Menu_CursorChange(mjnUImanager, v26, 1, 0);
    wk->cursor_old = v8;
    MENU_PARENT_MAX = (u32)MENU_PARENT_MAX;
    if ((s32)MENU_PARENT_MAX >= 1)
    {
      v31 = 0;
      m_Items = wk->parentID;
      while (m_Items[v31] != v8)
      {
        id_save = wk->id_save;
        wk->cursor_parent = -1;
        ++v31;
        wk->cursor_ID = id_save[v8];
        if (MENU_PARENT_MAX == v31)
          goto LABEL_57;
      }
      wk->cursor_parent = v31;
      wk->cursor_ID = -1;
      wk->parentCursor_save = v31;
    }
LABEL_57:
    v35 = vdupq_n_s32(v11);
    menu_draw = wk->menu_draw;
    menu_draw[0] = v11;
    *(int32x4_t *)&menu_draw[1] = vaddq_s32(v35, (int32x4_t)xmmword_3D07320);
    menu_draw[11] = v11 + 11;
    *(int32x4_t *)&menu_draw[5] = vaddq_s32(v35, (int32x4_t)xmmword_3D01E30);
    *(int32x2_t *)&menu_draw[9] = vadd_s32(vdup_n_s32(v11), (int32x2_t)0xA00000009LL);
    DrawMenuBeforeAfterSave(wk);
    selMenuScrollBarMove(mjnUImanager, wk->menu_num, v11, 0);
    wk->change_flag = 0;
    wk->textChangeStep = 0;
    wk->cursor = v8;
    wk->top = v11;
    SE(3);
    return;
  }
}

// 0x1d4bc50
static void CursorRight(tipsMenuWork_t *wk) {
  s32 top;
  s32 menu_num;
  s32 cursor;
  s32 *v6;
  s32 v7;
  s32 v8;
  s64 v9;
  s32 v10;
  u32 v11;
  s64 v12;
  s64 v14;
  s32 v15;
  s32 *v16;
  s64 v19;
  s32 *v20;
  s32 v21;
  s64 v22;
  s32 v23;
  s32 v25;
  s32 v26;
  s64 v31;
  s32 *m_Items;
  s32 *id_save;
  int32x4_t v35;
  s32 *menu_draw;

  top = wk->top;
  menu_num = wk->menu_num;
  cursor = wk->cursor;
  v6 = NewSpecific(s32, 0xCu);
  if (menu_num >= 13)
  {
    v7 = menu_num - 1;
    if (cursor != menu_num - 1)
    {
      v8 = top + 12;
      v9 = v6;
      if (top + 12 >= menu_num)
      {
        v11 = menu_num - 12;
      }
      else
      {
        v10 = menu_num - 12;
        if (v8 >= menu_num - 12)
          v11 = menu_num - 12;
        else
          v11 = top + 12;
        if (v8 < v10)
          v7 = cursor + 12;
      }
      v12 = 0;
      while (v12 < MENU_DRAW_MAX)
      {
        *(u32 *)(v9 + 32 + 4 * v12) = v11 + v12;
        ++v12;
      }
      v14 = 0;
      v15 = 0;
      v16 = (v9 + 32);
      while (1)
      {
        if (v14 >= MENU_DRAW_MAX)
          break;
        v19 = (u32)MENU_DRAW_MAX & ~((s32)MENU_DRAW_MAX >> 31);
        v20 = v16;
        while (v19)
        {
          --v19;
          v21 = *v20++;
          if (wk->menu_draw[v14] == v21)
            goto LABEL_20;
        }
        goto LABEL_9000;
        while (1)
        {
          if (v22 >= MENU_DRAW_MAX)
            break;
          v23 = v16[v22++];
          if (wk->menu_draw[v14] == v23)
          {
LABEL_20:
            ++v15;
            break;
          }
        }
LABEL_9000:
        ++v14;
      }
      v25 = MENU_DRAW_MAX - v15;
      MenuCorsorPosCtrl(mjnUImanager, v25, 1, 0);
      v26 = v7 - wk->child_move;
      if (wk->move_flag)
        wk->move_flag = 0;
      Menu_CursorChange(mjnUImanager, v26, 1, 0);
      wk->cursor_old = v7;
      MENU_PARENT_MAX = (u32)MENU_PARENT_MAX;
      if ((s32)MENU_PARENT_MAX >= 1)
      {
        v31 = 0;
        m_Items = wk->parentID;
        while (m_Items[v31] != v7)
        {
          id_save = wk->id_save;
          wk->cursor_parent = -1;
          ++v31;
          wk->cursor_ID = id_save[v7];
          if (MENU_PARENT_MAX == v31)
            goto LABEL_57;
        }
        wk->cursor_parent = v31;
        wk->cursor_ID = -1;
        wk->parentCursor_save = v31;
      }
LABEL_57:
      v35 = vdupq_n_s32(v11);
      menu_draw = wk->menu_draw;
      menu_draw[0] = v11;
      *(int32x4_t *)&menu_draw[1] = vaddq_s32(v35, (int32x4_t)xmmword_3D07320);
      menu_draw[11] = v11 + 11;
      *(int32x4_t *)&menu_draw[5] = vaddq_s32(v35, (int32x4_t)xmmword_3D01E30);
      *(int32x2_t *)&menu_draw[9] = vadd_s32(vdup_n_s32(v11), (int32x2_t)0xA00000009LL);
      DrawMenuBeforeAfterSave(wk);
      selMenuScrollBarMove(mjnUImanager, wk->menu_num, v11, 0);
      wk->change_flag = 0;
      wk->textChangeStep = 0;
      wk->cursor = v7;
      wk->top = v11;
      SE(3);
      return;
    }
  }
}

// 0x1d4c090
static void DrawMenuBeforeAfterSave(tipsMenuWork_t *wk) {
  s32 v4;
  s64 v5;
  s32 *menu_draw;
  s64 v8;
  s32 *menu_After;
  s32 v10;
  s32 v11;
  s32 v12;
  u64 v13;
  u64 v14;
  s32 v15;
  char *v16;
  s64 v17;
  s64 v18;
  char *v19;
  s32 v20;

  v4 = -1;
  v5 = 8;
  while (1)
  {
    if (v5 - 8 >= MENU_DRAW_MAX)
      break;
    menu_draw = wk->menu_draw;
    v8 = 4 * v5;
    menu_After = wk->menu_After;
    v10 = v4 + menu_draw[0];
    --v4;
    if (v10 < 0)
      v10 = -1;
    *((u32 *)&wk->menu_Before->obj.klass + v5) = v10;
    *((u32 *)&wk->Before_Save->obj.klass + v5) = v10;
    v11 = v5++ + menu_draw[11];
    v12 = v11 - 7;
    if (v12 >= wk->menu_num)
      v12 = -1;
    *(u32 *)((char *)&menu_After->obj.klass + v8) = v12;
  }
  v13 = (u32)wk->menu_Before[0];
  if ((v13 & 0x80000000) == 0)
  {
    if ((s32)v13 < (s32)MENU_DRAW_MAX)
    {
      v14 = 0;
      while ((s64)v14 < MENU_DRAW_MAX)
      {
        if (v14 > v13)
          v15 = -1;
        else
          v15 = v14;
        v16 = (char *)wk->menu_Before + 4 * v14++;
        *((u32 *)v16 + 8) = v15;
      }
      return;
    }
    v17 = 0;
    v18 = 76;
    while (v17 < MENU_DRAW_MAX)
    {
      v19 = (char *)wk->menu_Before + 4 * v17;
      v20 = *(u32 *)((char *)&wk->Before_Save->obj.klass + v18);
      ++v17;
      v18 -= 4;
      *((u32 *)v19 + 8) = v20;
    }
  }
}

// 0x1d49b70
char *mjnChangeTextPLTF(char *text) {
  char *PlatformString;
  char *v4;
  char *v5;
  char *v6;
  char *v7;
  char *v8;
  char *v9;
  char *v10;
  char *v11;
  char *v12;
  char *v13;
  char *v14;
  char *v15;

  PlatformString = itfGetPlatformString(0);
  v4 = Replace_54838864(text, "<PT 0>", PlatformString, 0);
  v5 = itfGetPlatformString(1);
  v6 = Replace_54838864(v4, "<PT 1>", v5, 0);
  v7 = itfGetPlatformString(2);
  v8 = Replace_54838864(v6, "<PT 2>", v7, 0);
  v9 = itfGetPlatformString(3);
  v10 = Replace_54838864(v8, "<PT 3>", v9, 0);
  v11 = itfGetPlatformString(4);
  v12 = Replace_54838864(v10, "<PT 4>", v11, 0);
  v13 = itfGetPlatformString(5);
  v14 = Replace_54838864(v12, "<PT 5>", v13, 0);
  v15 = itfGetPlatformString(6);
  return Replace_54838864(v14, "<PT 6>", v15, 0);
}

// 0x1d427d0
void mjnUniDrawMenu_New(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  tipsMenuWork_t *v4;
  char *v8;
  void *Instance;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    return;
  v4 = ProcessData;
  if (!BYTE1(ProcessData[5].monitor))
  {
    if (LODWORD(ProcessData[5].klass) == -1)
    {
      v8 = "";
      Instance = get_Instance(0);
      ItfButtonGuideActive(Instance, 1, 0);
      ButtonGuideDispSet("DBOOK01", 0, 90);
      PANEL02_SetMessage(mjnUImanager, v8, 0, 0);
      PANEL_TitleTextSet(mjnUImanager, v8, 0);
      v4->change_flag = 1;
    }
    else
    {
      PANEL_TitleTextSet(mjnUImanager, v4->draw_text[v4->cursor], 0);
      mjnPANEL2Process(v4);
    }
  }
}

// 0x1d4c240
void mjnPANEL2Process(tipsMenuWork_t *wk) {
  void *Instance;
  bool active;
  char **v10;

  switch (wk->textChangeStep)
  {
    case 0:
      PANEL02_TextScrollReset(mjnUImanager, 0);
      PANEL02_SetActive(mjnUImanager, 1, 0);
      PANEL02_AlphaCtrl(mjnUImanager, 0, 0);
      mjnDrawPANELMessage_New(TIPSPAGE[wk->id_save[wk->cursor]]);
      goto LABEL_14;
    case 1:
      wk->textChangeStep = 2;
      return;
    case 2:
      wk->textChangeStep = 3;
      return;
    case 3:
      PANEL02_TextScrollReset(mjnUImanager, 0);
LABEL_14:
      ++wk->textChangeStep;
      return;
    case 4:
      Instance = get_Instance(0);
      ItfButtonGuideActive(Instance, 1, 0);
      active = PANEL02_ScrollBarActiveChack(mjnUImanager, 0);
      v10 = &"MJN07";
      if (!active)
        v10 = &"DBOOK02";
      ButtonGuideDispSet(*v10, 0, 90);
      ButtonLineHelpDispSet(0);
      PANEL02_AlphaCtrl(mjnUImanager, 1, 0);
      wk->change_flag = 1;
      return;
    default:
      return;
  }
}

// 0x1d4c510
void mjnDrawPANELMessage_New(MJNTIPS_CLASS *tips_) {
  void *p_mjnUImanager;
  char *Text;
  void *mjnUImanager_local;
  char *LocalizeText;

  p_mjnUImanager = &mjnUImanager;
  Text = tips_->Text;
  mjnUImanager_local = p_mjnUImanager;
  LocalizeText = GetLocalizeText(Text, 1);
  PANEL02_SetMessage(mjnUImanager_local, LocalizeText, 0, 0);
}

// 0x1d42060
void mjnPanelTextCtrl(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    return;
  PanelTextCtrlSub(mjn);
}

// 0x1d4c5f0
static void PanelTextCtrlSub(tipsMenuWork_t *wk) {
  s32 v2;

  if (CHECK_PRESS(43284, 1))
  {
    v2 = 0;
  }
  else
  {
    if (CHECK_PRESS(43285, 1))
      v2 = 1;
    else
      v2 = -1;
  }
  PANEL02_TextScrollNew(mjnUImanager, v2, 0);
}

// 0x1d4c6c0
static s32 RightStickCtrl(void) {
  if (CHECK_PRESS(43284, 1))
    return 0;
  if (CHECK_PRESS(43285, 1))
    return 1;
  return -1;
}

// 0x1d423e0
void mjnResetUI(void) {
  MenuChildAnimSetCtrl(mjnUImanager, 0, 1, 0);
  MenuChildAnimSetCtrl(mjnUImanager, 1, 1, 0);
  MenuChildAnimSetCtrl(mjnUImanager, 2, 1, 0);
  MenuChildAnimSetCtrl(mjnUImanager, 3, 1, 0);
  MenuChildAnimSetCtrl(mjnUImanager, 4, 1, 0);
  MenuPosReset(mjnUImanager, 0);
  MenuObjReset(mjnUImanager, 0);
}
