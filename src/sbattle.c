#include "types.h"
#include "BST.h"
#include "BSTF.h"
#include "MODELTYPE.h"
#include "MOTION_FLG.h"
#include "SBTLDMG_HITFLG.h"
#include "SBTLMAIN4.h"
#include "SBTLUNIT_SIDE.h"
#include "SKLID.h"
#include "cmpraidouskill.h"
#include "dat.h"
#include "dds3_pad.h"
#include "dds3kernelcore.h"
#include "dds3kerneldraw.h"
#include "dds3objectbase.h"
#include "dds3scenebasic.h"
#include "dds3worldbasic.h"
#include "dvl.h"
#include "effpartslist.h"
#include "fld.h"
#include "g.h"
#include "kernel.h"
#include "mdl.h"
#include "sbattle.h"
#include "sbtl.h"
#include "sbtlaction.h"
#include "sbtlcalc.h"
#include "sbtlcamera.h"
#include "sbtldmg.h"
#include "sbtldraw.h"
#include "sbtleff.h"
#include "sbtlencount.h"
#include "sbtlexp.h"
#include "sbtlitem.h"
#include "sbtlmain.h"
#include "sbtlmenu.h"
#include "sbtlpanel.h"
#include "sbtlplayer.h"
#include "sbtlscene.h"
#include "sbtlscript.h"
#include "sbtlskill.h"
#include "sbtlsound.h"
#include "sbtlsub.h"
#include "sbtlunit.h"
#include "sbtlvisual.h"
#include "sbtlweapon.h"
#include "sdat.h"
#include "sdf_vu0.h"
#include "sdfdraw.h"
#include "sdfmodel.h"
#include "sdfquat.h"

#define SBTLEVTMES_00_00 0
#define SBTLEVTMES_00_01 1
#define SBTLEVTMES_00_02 2
#define SBTLEVTMES_00_03 3
#define NMLMES_000 0
#define NMLMES_004 1
#define NMLMES_00A 2
#define NMLMES_00B 3
#define NMLMES_00F 4
#define NMLMES_012 5
#define NOMES_000 0
#define NOMES_004 1
#define NOMES_00A 2
#define NOMES_00B 3
#define NOMES_00F 4
#define NOMES_012 5
#define SUMMONMES_00 0
#define SUMMONMES_01 1
#define SUMMONMES_02 2
#define SUMMONMES_03 3
#define SUMMONMES_04 4
#define SUMMONMES_05 5
#define SUMMONMES_06 6
#define SUMMONMES_07 7
#define SUMMONMES_08 8
#define SUMMONMES_09 9
#define SUMMONMES_0A 10
#define SUMMONMES_0B 11
#define SUMMONMES_0C 12
#define SUMMONMES_0D 13
#define SUMMONMES_0E 14
#define SUMMONMES_0F 15
#define SUMMONMES_10 16
#define SUMMONMES_11 17
#define VICEUPMES_000 0
#define VICEUPMES_00A 1
#define VICEUPMES_00B 2
#define VICEUPMES_00F 3
#define VICEDOWNMES_000 4
#define VICEDOWNMES_00A 5
#define VICEDOWNMES_00B 6
#define VICEDOWNMES_00F 7
#define YESMES_000 0
#define YESMES_004 1
#define YESMES_00A 2
#define YESMES_00B 3
#define YESMES_00F 4
#define YESMES_012 5
#define YOBIMES_000 0
#define YOBIMES_004 1
#define YOBIMES_00A 2
#define YOBIMES_00B 3
#define YOBIMES_00F 4
#define YOBIMES_012 5
#define FR_FONTCOL_NML 2694693760
#define FR_FONTCOL_NML_MSK 1296780152
#define FR_FONTCOL_SEL 1692838528
#define FR_FONTCOL_SEL_MSK 1349406840
#define FR_FONTCOL_DEAD 1967865216
#define FR_FONTCOL_HALF 3030410368
#define FR_FONTCOL_HALF_MSK 1515205240
#define FR_FONTCOL_MSK 1296780152
#define FR_FONTCOL_MSK2 1349406840
#define DBGMENU_SEIKAKU 12
#define DBGMENU_HGUNNUM 13
#define DBGMENU_MGUNNUM 14
#define DBGMENU_STOCKNUM 15
#define DBGMENU_GUNNO 16
#define DBGMENU_SORDNO 17
#define DBGMENU_MAGNUM 18
#define DBGMENU_POSRESET 19
#define DBGMENU_PARARESET 20
#define DBGMENU_ENCOUNTNO 21
#define SBDEBUG_EFFHITD_Y 27
#define SBDEBUG_EFFHITD_Y2 18
#define SBDEBUG_BEHAV_SPHERE 17
#define SBDEBUG_BEHAV_CYLINDER 18
#define SBDEBUG_BEHAV_RING 19
#define SBDEBUG_MDLBEHAV_SPHERE 14
#define SBDEBUG_MDLBEHAV_CYLINDER 14
#define SBDEBUG_MDLBEHAV_RING 15
#define SBDEBUG_FILEMENU_NUM 8
#define SBDEBUG_MDLCSR 6
#define SBDEBUG_MFLGTYPE_ONOFF 0
#define SBDEBUG_MFLGTYPE_NODE 1
#define SBDEBUG_MFLGTYPE_NUM 2
#define SBDEBUG_MFLGTYPE_ALLDEAD 3
#define SBDEBUG_MFLGTYPE_TIMEZERO 4
#define HORIZONTAL_COLOR 1347453008
#define VERTICAL_COLOR 1347440768
#define OUTER_COLOR 2155888704
#define SPHERE_COLOR 541077552
#define CURVE_COLOR 813727872
#define POINT_NUM 20
#define EFFVIEWER_ANALOG_SPACE 64
#define EFFVIEWER_ANALOG_N 128
#define BTLDEBUG_WC_HEIGHT 16
#define BTLDEBUG_WC_RING_POINT 16
#define BTLDEBUG_WS_HEIGHT 10
#define BTLDEBUG_WS_RING_POINT 11
#define BTLDEBUG_WS_NUMBER 2

typedef enum {
    TARGET_Y = 0,
    LENGTH = 1,
    SENSITIVITY_X = 2,
    SENSITIVITY_Y = 3,
    UP_MAXANGLE_Y = 4,
    DOWN_MAXANGLE_Y = 5,
    FOV = 6,
    INITROT_X = 7,
    INITROT_Y = 8,
    SENSITIVITY_MX = 9,
    SENSITIVITY_MY = 10,
    SAVE_ASSET = 11,
} CAMERA_DEBUGPAR;

typedef enum {
    TIME_ELAPSED = 0,
    REMAINING_TIME = 1,
} TIME_DEBUGPAR;

typedef enum {
    SBDEBUG_EFFHITMODE_OPEN = 0,
    SBDEBUG_EFFHITMODE_SAVE = 1,
    SBDEBUG_EFFHITMODE_LOAD = 2,
    SBDEBUG_EFFHITMODE_PAGELIST = 3,
    SBDEBUG_EFFHITMODE_HITTYPE = 4,
    SBDEBUG_EFFHITMODE_SELMENU = 5,
    SBDEBUG_EFFHITMODE_COPY = 6,
    SBDEBUG_EFFHITMODE_DELOK = 7,
    SBDEBUG_EFFHITMODE_GDELOK = 8,
    SBDEBUG_EFFHITMODE_EDIT = 9,
    SBDEBUG_EFFHITMODE_PB = 10,
    SBDEBUG_EFFHITMODE_PBLOADER = 11,
    SBDEBUG_EFFHITMODE_EPL = 12,
    SBDEBUG_EFFHITMODE_EPLLOADER = 13,
    SBDEBUG_EFFHITMODE_EPLMENU = 14,
    SBDEBUG_EFFHITMODE_EPLDELOK = 15,
    SBDEBUG_EFFHITMODE_EXITOK = 16,
} SBDEBUG_EFFHITMODE;

typedef struct DBG_SPIRIT_TABLE_t DBG_SPIRIT_TABLE_t;
typedef struct MOTIONDATA_WORK MOTIONDATA_WORK;
typedef struct SBDEBUG_CSRWORK SBDEBUG_CSRWORK;
typedef struct SBDEBUG_FILELISTWORK SBDEBUG_FILELISTWORK;
typedef struct SBDEBUG_FILEWORK SBDEBUG_FILEWORK;
typedef struct SBDEBUG_FLGWORK SBDEBUG_FLGWORK;
typedef struct SBDEBUG_PATHDATA SBDEBUG_PATHDATA;
typedef struct SBDEBUG_TIMEWORK SBDEBUG_TIMEWORK;
typedef struct SBTLDEBUG_WORK SBTLDEBUG_WORK;
typedef struct SBTLDMG_HITLISTWORK SBTLDMG_HITLISTWORK;
typedef struct SBTLDMG_HITWORK SBTLDMG_HITWORK;
typedef struct SBTLEFF_DATAWORK SBTLEFF_DATAWORK;
typedef struct SBTLEFF_EFFTIME SBTLEFF_EFFTIME;
typedef struct SBTLSKILLHIT_POSWORK SBTLSKILLHIT_POSWORK;
typedef struct SBTLSKILLHIT_TBL SBTLSKILLHIT_TBL;
typedef struct SBTLSKILLIDOU_WORK SBTLSKILLIDOU_WORK;
typedef struct SBTLSKLHIT_PACDATAWORK SBTLSKLHIT_PACDATAWORK;
typedef struct SBTLUNIT_WORK SBTLUNIT_WORK;
typedef struct VISUALDATA_WORK VISUALDATA_WORK;
typedef struct dds3Basic_t dds3Basic_t;
typedef struct dds3ModelHandle_t dds3ModelHandle_t;
typedef struct dds3PoseSet_t dds3PoseSet_t;
typedef struct dds3ProcessID_t dds3ProcessID_t;
typedef struct evtUnitHandle_t evtUnitHandle_t;

struct SBDEBUG_FLGWORK {
    u8 mode;
    SBDEBUG_MODE nextmodeno;
    SBDEBUG_MODE backmodeno;
    SBDEBUG_FLGTYPE sttype;
    SBDEBUG_FLG stflg;
};

struct DBG_SPIRIT_TABLE_t {
    s32 devilID;
    SKLID skillID;
    char *skillName;
};

struct SBDEBUG_TIMEWORK {
    f32 in_alpha;
    f32 alpha;
    f32 out_alpha;
};

struct SBTLDEBUG_WORK {
    SBDEBUG_FLG status;
    SBDEBUG_FLG unitst;
    SBDEBUG_FLG y_status;
    SBDEBUG_MODE mode;
    SBDEBUG_MODE l3modebk;
    s32 gstat0;
    s32 padmode;
    s32 unitmode;
    dds3Basic_t *pUnitBasic;
    MODELTYPE unitmajor;
    s32 vs_mode;
    s32 vs_saveflg;
    s32 vs_raceid;
    VISUALDATA_WORK *vsdata;
    s32 vs_posp;
    s32 vs_shadowflg;
    s32 vs_mtnno;
    u32 vs_mtnflg;
    s32 vs_shildflg;
    SBDEBUG_FILELISTWORK *fileList;
    s8 nef_checkflg;
    SBDEBUG_EFFHITMODE nef_mode;
    SBDEBUG_EFFHITMODE nef_modebk;
    s32 nef_gstat[2];
    s32 nef_filep;
    f32 nef_pathtime;
    f32 nef_addpathtime;
    f32 nef_timecnt;
    s32 nef_movetype;
    dds3Basic_t *path_pBasic;
    evtUnitHandle_t *path_hEveUnit;
    dds3ModelHandle_t *path_hModel;
    s32 path_motionno;
    s32 pagemode;
    SBDEBUG_CSRWORK *nef_modecsr;
    SBDEBUG_CSRWORK *nef_savecsr;
    SBDEBUG_CSRWORK *nef_loadcsr;
    SBDEBUG_CSRWORK *nef_pagecsr;
    SBDEBUG_CSRWORK *nef_htypecsr;
    SBDEBUG_CSRWORK *nef_selmenucsr;
    SBDEBUG_CSRWORK *nef_copycsr;
    SBDEBUG_CSRWORK *nef_delokcsr;
    SBDEBUG_CSRWORK *nef_gdelokcsr;
    SBDEBUG_CSRWORK *nef_pbloadcsr;
    SBDEBUG_CSRWORK *nef_eplloadcsr;
    SBDEBUG_CSRWORK *nef_eplmenucsr;
    SBDEBUG_CSRWORK *nef_epldelokcsr;
    SBDEBUG_CSRWORK *nef_exitokcsr;
    s32 nef_nowpage;
    s32 nef_poseture;
    f32 nef_sokudo;
    s32 ef_mode;
    s32 ef_id;
    s32 ef_num;
    s32 ef_nowpage;
    s32 ef_flgp;
    s32 ef_dirflgp;
    s32 ef_stendp;
    s8 ef_wkflg[16];
    SBTLSKLHIT_PACDATAWORK *ef_wk[16];
    SBTLEFF_DATAWORK *ef_dwk[16];
    s32 ef_dwksize[16];
    SBTLEFF_EFFTIME *ef_dtime[16];
    SBDEBUG_TIMEWORK *ef_dt[16];
    SBDEBUG_PATHDATA *ef_path[16];
    char *filename;
    s32 mdl_mode;
    s16 mdl_minor;
    s32 acterID;
    s32 targetID[9];
    s32 prev_cnt;
    s32 prev_setcnt;
    s32 prev_gstat;
    s32 prev_mode;
    s32 prev_motionno;
    SKLID prev_skillid;
    SKLID change_skillid;
    s32 skillchange_mode;
    s32 result_cnt;
    s16 resetencount;
    BST para_bstno;
    SBDEBUG_CSRWORK *maincsr;
    SBDEBUG_CSRWORK *mdlslcsr;
    SBDEBUG_CSRWORK *mdlmenucsr;
    SBDEBUG_CSRWORK *mtioncgcsr;
    SBDEBUG_CSRWORK *unitcsr;
    SBDEBUG_CSRWORK *visualcsr;
    SBDEBUG_CSRWORK *sklccsr;
    SBDEBUG_CSRWORK *opticsr;
    SBDEBUG_CSRWORK *setcsr;
    SBDEBUG_CSRWORK *effhitcsr;
    SBDEBUG_CSRWORK *modelhitcsr;
    SBDEBUG_CSRWORK *bstcsr;
    SBDEBUG_CSRWORK *paracsr;
    SBDEBUG_CSRWORK *aicsr;
    SBDEBUG_CSRWORK *cameraCsr;
    SBDEBUG_CSRWORK *weaponCsr;
    SBDEBUG_CSRWORK *timeCsr;
    sdfMatrix4_t mat;
    sdfMatrix4_t mat2;
    sdfMatrix4_t mat3;
    sdfMatrix4_t mat_h;
    s8 dvlStkPtn;
    u32 raidouP;
    s32 mapmdl;
    s32 weaponId;
    bool bKyousei;
    bool bBossDbg;
    s32 rouletteId;
    bool bCamMoveTgtLock;
    bool bPosDisp;
    bool testTblCam;
    s32 all_dead_raito;
    s32 enemy_stop_mode;
    s32 dlcsel;
    s32 CmbSklSet;
    s32 set_mag;
};

static SBTLDEBUG_WORK *sbtldbwk;
static sdfVector4_t debugcenterpos;
static u32 *sbtlDebug_TriIndex;
static char *pDummyFile;
static char *pDummyFile1;
static char *pDummyFile2;
static char *pDummyFile3;
static sdfVector4_t sbtldb_hitpos;
static sdfVector4_t sbtldb_hitpos2;
static s32 sbtldb_timecnt;
sbdebug_procmenuDelegate *sbdebug_procmenu;
sbdebug_drawmenuDelegate *sbdebug_drawmenu;
sBtlDebug_NEFMODE_FuncDelegate *sBtlDebug_NEFMODE_Func;
sBtlDebug_NMDLMODE_FuncDelegate *sBtlDebug_NMDLMODE_Func;
sBtlDebug_NMDLMVMODE_FuncDelegate *sBtlDebug_NMDLMVMODE_Func;
sBtlDebug_EffHitEditorDraw_FunctblDelegate *sBtlDebug_EffHitEditorDraw_Functbl;
sBtlDebug_MDLHitEditorDraw_FunctblDelegate *sBtlDebug_MDLHitEditorDraw_Functbl;
u32 *sBtlDebug_SetPathMotion_line_colors;
u8 *sBtlDebug_SetPathMotion_motion_savetbl;
u8 *sBtlDebug_SetPathMotion_motion_savetbl_p;
SBTLDMG_HITFLG *sBtlDebug_SetPathMotion_effhitset_flag;
static SBTLMAIN dbg_sbtl_wk_status;
static SBTLMAIN4 dbg_sbtl_wk_status4;
char *sbplayer_cmnd;
char *sbtarget_cmnd;
char *sblist_optimenu;
static SBDEBUG_FLGWORK *sbflg_optimenu;
char *sblist_setmenu_00;
char *sblist_setmenu_01;
bool *sblist_setmenu_flg;
char *encountInfo;
char **mapModelInfo;
static SBDEBUG_FLGWORK *sbflg_setmenu;
char *sblist_paramenu;
char *sblist_panel;
static SBDEBUG_FLGWORK *sbflg_panel;
static SBDEBUG_FLGWORK *sbflg_mdlselect;
char *sblist_modelmenu;
static SBDEBUG_FLGWORK *sbflg_cameraEdit;
static void *buffBattleCameraPar;
static bool battleCameraParSave;
char *sblistCameraMenu;
static SBDEBUG_FLGWORK *sbflg_swordSet;
static SBDEBUG_FLGWORK *sbflg_TimeSet;
char *sblistTimeMenu;
char *sblist_mdlmenupanel;
static SBDEBUG_FLGWORK *sbflg_mdlmenupanel;
char *sblist_mtioncgpanel_n;
char *sblist_mtioncgpanel_boss;
char *sblist_mtioncgpanel_p;
char *sblist_visualmenu00;
char *sblist_visualmenu01;
char *sblist_visualmenu02;
char *sblist_visualmenu01_e;
char *sblist_visualmenu02_e;
char *sblist_visualmenu03;
char *sblist_visualmenu04;
char *sblist_visualmenu05;
char *sblist_visualmenu06;
char *sblist_visualmenu06_0;
char *sblist_visualmenu07;
char *sblist_visualmenu08;
char *sblist_visualmenu09;
MOTION_FLG *motion_flg;
char *motion_tbl_new;
char *motion_tbl_player;
char *sblist_efhitmenu_open_move;
char *sblist_efhitmenu_open_mdl;
char *sblist_efhitmenu_open;
char *sblist_efhitmenu_page_00;
char *sblist_efhitmenu_page_01;
char *sblist_efhitmenu_page_02;
char *sblist_efhitmenu_selmenu;
char *sblist_efhitmenu_delok_00;
char *sblist_efhitmenu_exitok_00;
char *sblist_efhitmenu_delok_01;
char *sblist_efhitmenu_hittype;
char *sblist_efhitmenu_edit_page;
char *sblist_efhitmenu_edit_para00;
char *sblist_efhitmenu_edit_para00_0;
char *sblist_efhitmenu_edit_para00_1;
char *sblist_mdlhitmenu_edit_para00;
char *sblist_mdlhitmenu_edit_para00_0;
char *sblist_mdlhitmenu_edit_para00_1;
char *sblist_mdlhitmenu_edit_para02;
char *sblist_mdlhitmenu_edit_para03;
char *sblist_efhitmenu_edit_para01;
char *sblist_efhitmenu_edit_para01_1;
char *sblist_mdlmovemenu_edit_para00;
char *sblist_efhitmenu_edit_para02;
char *sblist_efhitmenu_edit_para02_0;
char *sblist_efhitmenu_edit_para03;
char *sblist_efhitmenu_edit_para03_0;
char *sblist_efhitmenu_edit_para03_1;
char *sblist_efhitmenu_edit_para04;
char *sblist_efhitmenu_edit_para05_00;
char *sblist_efhitmenu_edit_para05_01;
char *sblist_efhitmenu_edit_para06_00;
char *sblist_effhitemenu00;
char *sblist_effhitemenu01;
char *sblist_effhitemenu02;
char *sblist_effhitemenu03;
char *sblist_effhitemenu03_0;
char *sblist_effhitemenu03_a1;
char *sblist_effhitemenu03_a2;
char *sblist_effhitemenu04;
char *sblist_effhitemenu05;
static SBTLDMG_HITFLG *effhitset_flag;
static DBG_SPIRIT_TABLE_t *gDbg_Spirit_Table;
static bool gDbgBound_Use;
static s32 gDbgBound_WeakType;
static s32 gDbgBound_Step;
static s32 gDbgBound_Step_ListID;
static s32 gDbgBound_Step_OldDevilID;
static s32 gDbgBound_Step_NextDevilID;
static s32 gDbgBound_Step_NextLR;

static bool MainProc(dds3ProcessID_t *id);
static bool MainDraw(dds3ProcessID_t *id);
static bool ModelSelectProc(dds3ProcessID_t *id);
static bool ModelSelectDraw(dds3ProcessID_t *id);
static bool ModelMenuProc(dds3ProcessID_t *id);
static bool ModelMenuDraw(dds3ProcessID_t *id);
static bool MotionChngProc(dds3ProcessID_t *id);
static void sBtlDebug_SetStatusflg(s32 nowp, SBDEBUG_FLGWORK *wk, s8 flg);
static void sBtlDebug_DrawONOFFList(SBDEBUG_FLGWORK *wk, s32 num, s32 x, s32 y);

// macros
// 0x1905920: s32 SPR_X(s32 _val)
#define SPR_X(_val) (16 * val)

// 0x1905930: s32 SPR_Y(s32 _val)
#define SPR_Y(_val) (8 * val)

// 0x1905880
void sprDbgPrintStr(s32 X, s32 Y, u32 Z, s32 Attr, char *pStr, DDS3_OT OtNo, s32 _fontSize) {
  DbgText(X, Y, pStr, Attr, OtNo, fontSize, 0);
}

// 0x1905940
void sprDbgDrawWindowFrame(s32 X, s32 Y, u32 Z, s32 W, s32 H, u32 BgCol, u32 FrmCol, DDS3_OT OtNo) {
  ;
}

// 0x1905950
static bool MainProc(dds3ProcessID_t *id) {
  sBtlDebug_UnitPanelCursor(sbtldbwk->maincsr);
  return 1;
}

// 0x1906890
static bool MainDraw(dds3ProcessID_t *id) {
  if ((sbtldbwk->status & 1) == 0)
    return 1;
  sBtlDebug_DrawCursor(258, 10, sbtldbwk->maincsr);
  sBtlDebug_DrawNormalList(sblist_panel, 22, sbtldbwk->maincsr->point, 270, 10, 0);
  sBtlDebug_DrawONOFFList(sbflg_panel, 22, 450, 10);
  return 1;
}

// 0x1908460
static bool ModelSelectProc(dds3ProcessID_t *id) {
  SBDEBUG_CSRWORK *mdlslcsr;
  SBTLUNIT_WORK *Unit;
  s32 v14;
  s32 v16;
  s32 v19;
  u32 v21;
  s32 point;
  s32 v24;
  SBTLUNIT_WORK *v25;

  mdlslcsr = sbtldbwk->mdlslcsr;
  Unit = sbattleGetUnit(mdlslcsr->point);
  if (Unit)
  {
    if (Unit->pBasic)
      Unit->vstatus &= ~0x100u;
  }
  if (CHECK_TRIG(4096, 1))
  {
    sBtlDebug_SetStatusflg(0, sbflg_mdlselect, 0);
    return 1;
  }
  if (CHECK_TRIG(4097, 1))
  {
    if (sbtldbwk->mdlslcsr->dummy == 1)
    {
      v14 = 1;
    }
    else
    {
      v14 = 0;
    }
    sBtlDebug_SetStatusflg(v14, sbflg_mdlselect, 1);
    return 1;
  }
  if (CHECK_TRIG(4100, 1))
  {
    while (1)
    {
      v16 = mdlslcsr->point - 1;
      mdlslcsr->point = v16;
      if (v16 < 0)
        break;
LABEL_23:
      if (sbattleGetUnit(v16))
        goto LABEL_45;
    }
    v16 = wk->UnitMng->count - 1;
    mdlslcsr->point = v16;
    goto LABEL_23;
  }
  if (CHECK_TRIG(4101, 1))
  {
    do
    {
      v19 = mdlslcsr->point + 1;
      mdlslcsr->point = v19;
      if (v21)
      {
        if (v19 < wk->UnitMng->count)
          goto LABEL_40;
      }
      else
      {
        if (v19 < wk->UnitMng->count)
        {
LABEL_40:
          point = mdlslcsr->point;
          continue;
        }
      }
      point = 0;
      mdlslcsr->point = 0;
    }
    while (!sbattleGetUnit(point));
  }
LABEL_45:
  v24 = mdlslcsr->point;
  v25 = sbattleGetUnit(v24);
  if (!v25)
    return 1;
  v25->vstatus |= 0x100u;
  return 1;
}

// 0x1909b90
static bool ModelSelectDraw(dds3ProcessID_t *id) {
  SBTLUNIT_WORK *Unit;
  SBTLUNIT_WORK *v5;
  f32 *p_x;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  s32 v15;
  s32 v16;
  dds3ModelHandle_t *hModel;
  unsigned __int128 v20;
  sdfVector4_t v21;

  v20 = 0u;
  Unit = sbattleGetUnit(sbtldbwk->mdlslcsr->point);
  if (!Unit)
    return 1;
  v5 = Unit;
  sBtlGetChestPos(v5);
  sBtlChangeWorldtoScreenUnity(&v20);
  p_x = &vf00.x;
  x = p_x[4];
  y = p_x[5];
  z = p_x[6];
  w = p_x[7];
  v21.x = x;
  v21.y = y;
  v21.z = z;
  v21.w = w;
  sBtlDebug_DrawTCursor(v21, 0x80808040);
  if (*(f32 *)&v20 == INFINITY)
    v15 = 0x80000000;
  else
    v15 = *(f32 *)&v20;
  if (*((f32 *)&v20 + 1) == INFINITY)
    v16 = 0x80000000;
  else
    v16 = *((f32 *)&v20 + 1);
  sBtlDrawDevilName2(v5, v15, v16, 0, 0, v5->para->devilid);
  if (v5->pBasic)
  {
    hModel = v5->hModel;
    mdlSetColor(hModel, 0x80F0F0F0);
  }
  return 1;
}

// 0x190a100
static bool ModelMenuProc(dds3ProcessID_t *id) {
  SBDEBUG_CSRWORK *mdlmenucsr;
  s32 point;
  s32 v9;
  s32 v12;
  s32 v14;
  s32 v15;
  s32 v16;

  mdlmenucsr = sbtldbwk->mdlmenucsr;
  if (CHECK_TRIG2(4096))
  {
    point = mdlmenucsr->point;
    if (point == 2)
    {
      v9 = 2;
    }
    else
    {
      v9 = point;
    }
    sBtlDebug_SetStatusflg(v9, sbflg_mdlmenupanel, 0);
    return 1;
  }
  else
  {
    if (!CHECK_TRIG2(4097))
    {
      if (CHECK_REP2(4100))
      {
        v14 = mdlmenucsr->point - 1;
        mdlmenucsr->point = v14;
        if (v14 < 0)
        {
          mdlmenucsr->point = mdlmenucsr->maxp - 1;
          return 1;
        }
      }
      else if (CHECK_REP2(4101))
      {
        v15 = mdlmenucsr->point;
        if (v15 + 1 < mdlmenucsr->maxp)
          v16 = v15 + 1;
        else
          v16 = 0;
        mdlmenucsr->point = v16;
        return 1;
      }
      return 1;
    }
    v12 = mdlmenucsr->point;
    sBtlDebug_SetStatusflg(v12, sbflg_mdlmenupanel, 1);
    return 1;
  }
}

// 0x190a290
static bool ModelMenuDraw(dds3ProcessID_t *id) {
  s32 v4;
  u32 v5;
  s32 v7;
  u32 v8;
  s32 v10;
  u32 v11;
  s32 v13;
  u32 v14;
  s32 v16;
  u32 v17;
  s32 v19;
  u32 v20;
  s32 v22;
  u32 v23;
  s32 v25;
  u32 v26;
  s32 v28;
  u32 v29;

  sBtlDebug_DrawCursor_OFFSET(2, 268, 16, sbtldbwk->mdlmenucsr);
  sbattleDrawDebugMenu(32, 264, v4, v5, 0);
  sbattleDrawDebugMenu(32, 280, v7, v8, 1);
  sbattleDrawDebugMenu(32, 296, v10, v11, 2);
  sbattleDrawDebugMenu(32, 312, v13, v14, 3);
  sbattleDrawDebugMenu(32, 328, v16, v17, 4);
  sbattleDrawDebugMenu(32, 344, v19, v20, 5);
  sbattleDrawDebugMenu(32, 360, v22, v23, 6);
  sbattleDrawDebugMenu(32, 376, v25, v26, 7);
  sbattleDrawDebugMenu(32, 392, v28, v29, 8);
  return 1;
}

// 0x190a690
static bool MotionChngProc(dds3ProcessID_t *id) {
  SBDEBUG_CSRWORK *mtioncgcsr;
  SBTLUNIT_WORK *Unit;
  SBTLUNIT_WORK *v6;
  s32 v7;
  s32 point;
  s32 v11;
  s32 v12;
  s32 v13;

  mtioncgcsr = sbtldbwk->mtioncgcsr;
  Unit = sbattleGetUnit(sbtldbwk->mdlslcsr->point);
  v6 = Unit;
  if (Unit->major == 1)
  {
    if (Unit->minor <= 415)
      v7 = 16;
    else
      v7 = 27;
  }
  else
  {
    if (Unit->major)
      goto LABEL_12;
    v7 = 49;
  }
  mtioncgcsr->maxp = v7;
LABEL_12:
  if (CHECK_TRIG(4096, 1))
  {
    point = mtioncgcsr->point;
    sBtlSetMotion_ID(v6, point, 0, 0, 0);
    return 1;
  }
  if (!CHECK_TRIG(4097, 1))
  {
    if (CHECK_REP(4100, 1))
    {
      v11 = mtioncgcsr->point - 1;
      mtioncgcsr->point = v11;
      if (v11 < 0)
      {
        mtioncgcsr->point = mtioncgcsr->maxp - 1;
        return 1;
      }
    }
    else if (CHECK_REP(4101, 1))
    {
      v12 = mtioncgcsr->point;
      if (v12 + 1 < mtioncgcsr->maxp)
        v13 = v12 + 1;
      else
        v13 = 0;
      mtioncgcsr->point = v13;
      return 1;
    }
    return 1;
  }
  sbtldbwk->mode = 2;
  return 1;
}

// 0x190a870
bool sbattleMotionChngDraw(dds3ProcessID_t *id) {
  SBDEBUG_CSRWORK *mtioncgcsr;
  SBTLUNIT_WORK *Unit;
  s32 v6;
  s32 point;
  SBTLUNIT_WORK *v9;
  bool v10;
  s32 v11;
  s32 offset;
  s32 v14;
  s32 v15;
  s32 v16;
  u32 v17;
  Il2CppObject *v18;
  char *v19;
  s32 data;

  mtioncgcsr = sbtldbwk->mtioncgcsr;
  Unit = sbattleGetUnit(sbtldbwk->mdlslcsr->point);
  point = mtioncgcsr->point;
  v9 = Unit;
  v10 = __OFSUB__(point, 13);
  v11 = point - 13;
  if (v11 < 0 != v10)
    offset = 0;
  else
    offset = v11;
  mtioncgcsr->offset = offset;
  offset = mtioncgcsr->offset;
  v14 = 0;
  v15 = 8;
  v16 = 2 * (v9->major != 0);
  do
  {
    if (offset + v14 >= mtioncgcsr->maxp)
      break;
    v17 = v14 == mtioncgcsr->point - mtioncgcsr->offset ? 1692838528 : -1600273536;
    sbattleDrawMotionList(16, v15, v6, v17, v16, offset + v14++);
    v15 += 16;
  }
  while (v14 != 15);
  data = 0;
  v18 = Box(s32, &data);
  v19 = Format("FRAME::{0}\n", v18, 0);
  DbgText(4096, 32, v19, 0, 109, 24, 0);
  return 1;
}

// 0x190acf0
bool sbattleUnitChngProc(dds3ProcessID_t *id) {
  SBDEBUG_CSRWORK *unitcsr;
  SBTLUNIT_WORK *Unit;
  SBTLDEBUG_WORK *v7;
  s32 unitmode;
  dds3Basic_t *pBasic;
  SBTLDEBUG_WORK *v11;
  bool v12;
  s32 mode;
  s32 v17;
  dds3Basic_t *pUnitBasic;
  SBTLDEBUG_WORK *v19;
  s32 v22;
  s32 v23;
  s32 point;
  s32 v25;
  s32 v26;
  s32 maxp;
  bool v28;
  SBTLDEBUG_WORK *v31;

  unitcsr = sbtldbwk->unitcsr;
  Unit = sbattleGetUnit(sbtldbwk->mdlslcsr->point);
  v7 = sbtldbwk;
  switch (v7->unitmode)
  {
    case 1:
      unitmode = 1;
      v7->unitmode = unitmode + 1;
      goto LABEL_32;
    case 2:
      sBtlDeleteUnit_UnWork(Unit);
      pBasic = Unit->pBasic;
      v11 = sbtldbwk;
      v11->pUnitBasic = pBasic;
      v12 = 0;
      Unit->mode = 0;
      goto LABEL_16;
    case 3:
      v7 = sbtldbwk;
      sbattleSetModelData(Unit, v7->unitmajor, unitcsr->point);
      Unit->gstat = 0;
      Unit->mode = 1;
      sBtlDebug_SetVisualData(Unit);
      v12 = 0;
LABEL_16:
      ++sbtldbwk->unitmode;
      return v12;
    case 4:
      mode = Unit->mode;
      if (mode != 8 && mode != 4)
        return 0;
      v17 = 5;
      v7->unitmode = v17;
      Unit->mode = 8;
      return 0;
    case 5:
      v7 = sbtldbwk;
      pUnitBasic = v7->pUnitBasic;
      dds3SceneBasicDelete(pUnitBasic);
      v19 = sbtldbwk;
      v19->pUnitBasic = 0;
      sbtldbwk->unitmode = 0;
      return 0;
    default:
LABEL_32:
      if (CHECK_TRIG(4096, 1))
      {
        sbtldbwk->unitmode = 1;
        return 1;
      }
      if (CHECK_TRIG(4097, 1))
      {
        sbtldbwk->mode = 2;
        return 1;
      }
      if (CHECK_REP(4100, 1))
      {
        v22 = unitcsr->point - 1;
        unitcsr->point = v22;
        if (v22 < 0)
        {
          v23 = unitcsr->maxp - 1;
LABEL_49:
          unitcsr->point = v23;
          return 1;
        }
        return 1;
      }
      if (CHECK_REP(4101, 1))
      {
        point = unitcsr->point;
        if (point + 1 < unitcsr->maxp)
          v23 = point + 1;
        else
          v23 = 0;
        goto LABEL_49;
      }
      if (CHECK_REP(4105, 1))
      {
        v25 = unitcsr->point;
        unitcsr->point = v25 - 10;
        if (v25 - 10 < 0)
        {
          v23 = v25 + unitcsr->maxp - 11;
          goto LABEL_49;
        }
        return 1;
      }
      if (CHECK_REP(4108, 1))
      {
        v26 = unitcsr->point + 10;
        maxp = unitcsr->maxp;
        unitcsr->point = v26;
        v28 = __OFSUB__(v26, maxp);
        v23 = v26 - maxp;
        if (v23 < 0 == v28)
          goto LABEL_49;
        return 1;
      }
      if (!CHECK_TRIG(4103, 1))
      {
        v12 = 1;
        if (!CHECK_TRIG(4102, 1))
          return v12;
      }
      v31 = sbtldbwk;
      if (v31->unitmajor)
      {
        v31 = sbtldbwk;
        v31->unitmajor = 0;
        return 1;
      }
      else
      {
        v31 = sbtldbwk;
        v31->unitmajor = 1;
        return 1;
      }
  }
}

// 0x190b620
bool sbattleUnitChngDraw(dds3ProcessID_t *id) {
  sbattleDrawUnitChangeList(0, 8);
  return 1;
}

// 0x190ba30
bool sbattleSousaProc(dds3ProcessID_t *id) {
  SBTLUNIT_WORK *Unit;
  SBTLUNIT_WORK *v5;
  s64 status;
  dds3MoverBasicObjFunc_t v12;
  SBTLDEBUG_WORK *v14;
  SBTLUNIT_WORK *v15;
  SBTLUNIT_WORK *v16;

  goto LABEL_3;
LABEL_7:
  v5 = Unit;
  status = sbtldbwk->status;
  if ((status & 0x400) != 0)
    goto LABEL_9;
  v5->status &= 0xFFFFFFF9;
  status = sbtldbwk->status;
  sbtldbwk->status = status | 0x400;
  v5->vstatus |= 0x4000u;
  sBtlStatusBitOn(v5, 0x10u);
  sbtldbwk->padmode = 0;
  v12 = Allocate(dds3MoverBasicObjFunc_t);
  _ctor(v12, 0, Method_Project_sbattle_sBtlDebug_UnitPad__, 0);
  dds3ObjectBaseSetPadControl(&v5->pBasic, v12);
  if (!CHECK_TRIG(4097, 1))
    return 1;
  goto LABEL_17;
LABEL_3:
  Unit = sbattleGetUnit(sbtldbwk->mdlslcsr->point);
  if (Unit)
    goto LABEL_7;
LABEL_9:
  if (!CHECK_TRIG(4097, 1))
    return 1;
LABEL_17:
  v14 = sbtldbwk;
  v14->mode = 2;
  v14->status = v14->status & 0xFFFFFFFFFFFFFAFFLL | 0x100;
  v15 = sbattleGetUnit(v14->mdlslcsr->point);
  if (!v15)
    return 1;
  v16 = v15;
  v15->status |= 6u;
  dds3ObjectBaseSetPadControl(&v15->pBasic, 0);
  v16->vstatus &= ~0x4000u;
  sBtlStatusBitOff(v16, 0xFFFFFFEF);
  return 1;
}

// 0x190bcc0
bool sbattleSousaDraw(dds3ProcessID_t *id) {
  return 1;
}

// 0x190bcd0
bool sbattleVisualProc(dds3ProcessID_t *id) {
  SBDEBUG_CSRWORK *visualcsr;
  MOTIONDATA_WORK *v5;
  SBTLUNIT_WORK *Unit;
  s32 devilid;
  DEVILDATA_WORK *DevilData;
  DEVILDATA_WORK *v10;
  s32 v12;
  SBTLDEBUG_WORK *v14;
  u32 v15;
  s32 point;
  s32 v17;
  bool v18;
  s32 flg;
  s32 v22;
  u16 v23;
  s32 v24;
  s32 v25;
  bool v26;
  s32 v28;
  bool v29;
  SBTLUNIT_WORK *v30;
  SBDEBUG_CSRWORK *v31;
  s32 v32;
  u16 major;
  s32 minor;
  VISUALDATA_WORK *vsdata;
  VISUALDATA_WORK *v38;
  MOTIONDATA_WORK *v39;
  MOTIONDATA_WORK *v40;
  f32 v41;
  f32 v42;
  f32 v43;
  f32 v44;
  f32 v45;
  f32 *p_x;
  dds3PoseSet_t *poseset;
  sdfVector4_t *p_scl;
  f32 v51;
  SBTLACTAI_WORK *actaiwk;
  s32 v53;
  s32 vs_mtnno;

  visualcsr = sbtldbwk->visualcsr;
  v5 = sbtldbwk->vsdata->mwk[sbtldbwk->vs_mtnno];
  Unit = sbattleGetUnit(sbtldbwk->mdlslcsr->point);
  devilid = Unit->para->devilid;
  DevilData = sBtlGetDevilData(devilid, -1);
  if (sbtldbwk->vs_mode == 1)
  {
    if (CHECK_REP2(4100))
    {
      --sbtldbwk->vs_mtnflg;
    }
    else if (CHECK_REP2(4101))
    {
      v14 = sbtldbwk;
      v15 = v14->vs_mtnflg + 1;
      v14->vs_mtnflg = v15;
      if (v15 >= 2)
      {
        v14 = sbtldbwk;
        v14->vs_mtnflg = 0;
      }
    }
    else if (CHECK_REP2(4103) || CHECK_REP2(4102))
    {
      flg = v5->flg;
      v22 = motion_flg[sbtldbwk->vs_mtnflg];
      v18 = (v22 & flg) == 0;
      v23 = v5->flg;
      if (v18)
      {
        LOWORD(v22) = motion_flg[sbtldbwk->vs_mtnflg];
        v5->flg = v22 | v23;
      }
      else
      {
        LOWORD(v22) = motion_flg[sbtldbwk->vs_mtnflg];
        v5->flg = v23 & ~(u16)v22;
      }
    }
    else if (CHECK_REP2(4097))
    {
      sbtldbwk->vs_mode = 0;
    }
    return 1;
  }
  v10 = DevilData;
  if (CHECK_TRIG2(4097))
  {
    DeleteLine(0);
    v12 = 0;
    sbtldbwk->mode = 2;
    goto LABEL_83;
  }
  if (CHECK_REP2(4100))
  {
    point = visualcsr->point;
    v12 = 0;
    v17 = point - 1;
    v18 = point == 21 || point == 9;
    visualcsr->point = v17;
    if (v18)
    {
      visualcsr->point = point - 2;
    }
    else if (v17 < 0)
    {
      visualcsr->point = visualcsr->maxp - 1;
    }
    goto LABEL_83;
  }
  if (CHECK_REP2(4101))
  {
    v24 = visualcsr->point;
    v25 = v24 + 1;
    v26 = v24 == 19 || v24 == 7;
    visualcsr->point = v25;
    if (v26)
    {
      v25 = v24 + 2;
      visualcsr->point = v24 + 2;
    }
    if (v25 >= visualcsr->maxp)
    {
      v12 = 0;
      visualcsr->point = 0;
      goto LABEL_83;
    }
LABEL_46:
    v12 = 0;
    goto LABEL_83;
  }
  if (CHECK_REP2(4096))
  {
    v28 = visualcsr->point;
    v29 = v28 == 4 || v28 == 22;
    if (!v29 && v28 != visualcsr->maxp - 1)
      goto LABEL_46;
LABEL_55:
    v30 = Unit;
    v31 = visualcsr;
    v32 = 0;
    goto LABEL_82;
  }
  if (CHECK_REP2(4108) && CHECK_PRESS2(4103) || CHECK_PRESS2(4108) && CHECK_REP2(4103))
  {
    v30 = Unit;
    v31 = visualcsr;
    v32 = 4;
    goto LABEL_82;
  }
  if (CHECK_REP2(4105) && CHECK_PRESS2(4102) || CHECK_PRESS2(4105) && CHECK_REP2(4102))
  {
    v32 = 5;
    v30 = Unit;
    v31 = visualcsr;
    goto LABEL_82;
  }
  if (CHECK_REP2(4103) && !CHECK_REP2(4108))
  {
    if (visualcsr->point == 22)
      goto LABEL_46;
    goto LABEL_55;
  }
  if (!CHECK_REP2(4102) || CHECK_REP2(4105))
  {
    if (CHECK_REP2(4108) && !CHECK_REP2(4103))
    {
      v30 = Unit;
      v31 = visualcsr;
      v32 = 2;
    }
    else if (CHECK_REP2(4105) && !CHECK_REP2(4102))
    {
      v30 = Unit;
      v31 = visualcsr;
      v32 = 3;
    }
    else if (CHECK_REP2(4107))
    {
      v30 = Unit;
      v31 = visualcsr;
      v32 = 6;
    }
    else
    {
      if (!CHECK_REP2(4104))
        goto LABEL_46;
      v30 = Unit;
      v31 = visualcsr;
      v32 = 7;
    }
LABEL_82:
    sbattleSetVisualPara(v30, v31, v32);
    v12 = 1;
    goto LABEL_83;
  }
  if (visualcsr->point == 22)
    goto LABEL_46;
  v12 = 1;
  sbattleSetVisualPara(Unit, visualcsr, 1);
LABEL_83:
  major = Unit->major;
  minor = Unit->minor;
  sBtlGetVisualData(major, minor);
  vsdata = sbtldbwk->vsdata;
  v38 = Allocate(VISUALDATA_WORK);
  _ctor_26520096(v38, vsdata, 0);
  v39 = *(MOTIONDATA_WORK *)((u64)v38->mwk + 8 * sbtldbwk->vs_mtnno + 32);
  v40 = Allocate(MOTIONDATA_WORK);
  _ctor_26518880(v40, v39, 0);
  Unit->max_mvspd.z = v38->mv_spd;
  v41 = v38->scale;
  v42 = v38->rot_spd;
  Unit->scale.x = v41;
  Unit->max_mvrot = v42;
  v43 = v38->scale;
  Unit->scale.y = v43;
  v44 = v38->scale;
  Unit->scale.z = v44;
  v45 = v38->scale;
  Unit->scale.w = v45;
  p_x = &vf00.x;
  p_x[4] = v41;
  p_x[5] = v43;
  p_x[6] = v44;
  p_x[7] = v45;
  poseset = Unit->pBasic->poseset;
  p_scl = &poseset->scl;
  *p_scl = vct_A;
  v51 = v38->hit_area_r;
  Unit->size = v38->size;
  actaiwk = Unit->actaiwk;
  actaiwk->hit_area_r = v51;
  actaiwk->priv_area_r = v40->m_mv_area_r;
  *(u64 *)&actaiwk->frid_area_r = *(u64 *)&v10->frid_area_r;
  if (v12)
  {
    v53 = visualcsr->point;
    if (v53 != 22 && v53 >= 11 && v53 != visualcsr->maxp - 1)
    {
      vs_mtnno = sbtldbwk->vs_mtnno;
      sBtlSetMotion_ID(Unit, vs_mtnno, 0, 0, 0);
    }
  }
  return 1;
}

// 0x190ccc0
bool sbattleVisualDraw(dds3ProcessID_t *id) {
  char *v2;
  char *v3;
  char *v4;
  char *v5;
  u64 *v6;
  char *v7;
  char *v8;
  char *v9;
  char *v10;
  char *v11;
  u64 *v12;
  char *v13;
  char *v14;
  char *v15;
  char *v16;
  char *v17;
  char *v18;
  char *v19;
  VISUALDATA_WORK *vsdata;
  SBDEBUG_CSRWORK *visualcsr;
  SBTLUNIT_WORK *Unit;
  u16 major;
  s32 minor;
  V_POSITION_WORK *EffCylinderData;
  s32 v31;
  f32 x;
  f32 y;
  f32 v34;
  f32 v35;
  SBTLDEBUG_WORK *v37;
  char **p_sblist_visualmenu01_e;
  s32 v46;
  f32 v49;
  s32 point;
  f32 v54;
  char **p_sblist_visualmenu02_e;
  f32 v61;
  f32 v62;
  f32 *p_x;
  f32 hit_area_r;
  f32 v65;
  f32 v66;
  f32 v67;
  f32 cylinder;
  s32 v70;
  s32 v72;
  MOTIONDATA_WORK *v73;
  char *v76;
  char *v78;
  char *v80;
  char *v88;
  char *v90;
  char *v92;
  char **p_motion_tbl_new;
  s32 v107;
  char *v108;
  s32 v116;
  f32 v117;
  f32 v118;
  f32 m_mv_area_r;
  f32 v120;
  f32 v121;
  f32 m_hokanrate;
  char **p_sblist_visualmenu06_0;
  dds3ModelHandle_t *hModel;
  f32 MotionFrame;
  f32 MotionLength;
  Il2CppObject *v132;
  char *v133;
  Il2CppObject *v134;
  char *v135;
  char *v136;
  f32 v137;
  f32 *p_m_speed;
  f32 v139;
  Il2CppObject *v140;
  char *v141;
  Il2CppObject *v142;
  char *v143;
  char *v144;
  s64 v147;
  f32 v148;
  f32 z;
  f32 v150;
  f32 v151;
  f32 w;
  f32 v153;
  f32 v159;
  f32 height;
  f32 v161;
  f32 v162;
  f32 v163;
  f32 v165;
  f32 v166;
  f32 v167;
  f32 v168;
  u64 *v169;
  char **v170;
  MOTIONDATA_WORK *m_data;
  sdfMatrix4_t v172;
  sdfMatrix4_t v173;
  sdfMatrix4_t v174;
  sdfMatrix4_t v175;
  sdfMatrix4_t data;
  sdfVector4_t v177;
  sdfVector4_t v178;
  sdfVector4_t v179;
  sdfVector4_t v180;
  sdfVector4_t v182;

  v2 = NewSpecific(string, 1u);
  v3 = "     >>";
  v2[0] = "     >>";
  v170 = &v2[0];
  v4 = NewSpecific(string, 6u);
  v5 = "   NONE";
  v6 = v4;
  v4[0] = "   NONE";
  v7 = " SIZE S";
  v6[5] = " SIZE S";
  v8 = " SIZE M";
  v6[6] = " SIZE M";
  v9 = " SIZE L";
  v6[7] = " SIZE L";
  v10 = "SIZE LL";
  v6[8] = "SIZE LL";
  v11 = " HELPER";
  v6[9] = " HELPER";
  v12 = NewSpecific(string, 4u);
  v13 = " NORMAL";
  v12[4] = " NORMAL";
  v14 = "   STOP";
  v12[5] = "   STOP";
  v15 = "    END";
  v12[6] = "    END";
  v169 = v12;
  v16 = "   LOOP";
  v12[7] = "   LOOP";
  v17 = NewSpecific(string, 2u);
  v18 = "OFF";
  v17[0] = "OFF";
  v19 = "ON";
  v17[1] = "ON";
  vsdata = sbtldbwk->vsdata;
  visualcsr = sbtldbwk->visualcsr;
  m_data = vsdata->mwk[sbtldbwk->vs_mtnno];
  Unit = sbattleGetUnit(sbtldbwk->mdlslcsr->point);
  if (sbtldbwk->vs_posp)
  {
    major = Unit->major;
    minor = Unit->minor;
    EffCylinderData = sBtlGetEffCylinderData(major, minor);
    v31 = -10;
    x = Unit->hpPosition.x;
    y = Unit->hpPosition.y;
    v34 = Unit->weak_shild_pos.x;
    v35 = Unit->weak_shild_pos.y;
    if (!Unit->weak_shild)
    {
LABEL_9:
      goto LABEL_10;
    }
  }
  else
  {
    EffCylinderData = vsdata->nml;
    v31 = 0;
    x = Unit->hpPosition.x;
    y = Unit->hpPosition.y;
    v34 = Unit->weak_shild_pos.x;
    v35 = Unit->weak_shild_pos.y;
    if (!Unit->weak_shild)
      goto LABEL_9;
  }
  sbtldbwk->vs_shildflg = 1;
LABEL_10:
  v37 = sbtldbwk;
  if (sbtldbwk->vs_mode != 1)
  {
    goto LABEL_12;
  }
  v37 = sbtldbwk;
  sBtlDebug_DrawNormalList_Col(sblist_visualmenu05, 2, v37->vs_mtnflg, -1, 270, 234);
  sBtlDebug_DrawONOFFList_Motion(m_data, 414, 234, 2);
LABEL_12:
  sBtlDebug_DrawNormalList_Col(sblist_visualmenu00, 4, visualcsr->point, -1, 14, 10);
  sbattleDrawString(160, 12, v6[sbtldbwk->vs_shadowflg + 4], visualcsr->point, 0);
  sbattleDrawInt_Num(186, 24, 0, visualcsr->point, 1);
  sbattleDrawFloat_Num(186, 36, vsdata->scale, visualcsr->point, 2);
  sbattleDrawFloat_Num(186, 48, vsdata->hit_area_r, visualcsr->point, 3);
  if (sbtldbwk->vs_posp)
  {
    p_sblist_visualmenu01_e = &sblist_visualmenu01_e;
    v46 = v31;
  }
  else
  {
    v46 = 0;
    p_sblist_visualmenu01_e = &sblist_visualmenu01;
  }
  sBtlDebug_DrawNormalList_Col(*p_sblist_visualmenu01_e, 4, visualcsr->point - 4, v46, 14, 66);
  v49 = EffCylinderData->x;
  point = visualcsr->point;
  sbattleDrawFloat_Num(186, 76, v49, point, 5);
  sbattleDrawFloat_Num(186, 88, EffCylinderData->y, visualcsr->point, 6);
  sbattleDrawFloat_Num(186, 100, EffCylinderData->z, visualcsr->point, 7);
  v54 = 0.0;
  if (visualcsr->point != 3)
  {
    goto LABEL_32;
  }
  sBtlGetUnitHelperPos(Unit, 0);
  v167 = v34;
  v61 = v35;
  v62 = x;
  p_x = &vf00.x;
  hit_area_r = vsdata->hit_area_r;
  v65 = p_x[4];
  v66 = p_x[5];
  v67 = p_x[6];
  v54 = p_x[7];
  v178.y = v66;
  v178.z = v67;
  v178.w = v54;
  memset(&v174, 0, sizeof(v174));
  v178.x = v65;
  sbattleDraw3DSphere(v178, hit_area_r, 0x10604020u, 0, &v174);
  x = v62;
  v35 = v61;
  v34 = v167;
LABEL_32:
  if (sbtldbwk->vs_posp)
  {
    p_sblist_visualmenu02_e = &sblist_visualmenu02_e;
    goto LABEL_52;
  }
  v31 = 0;
  p_sblist_visualmenu02_e = &sblist_visualmenu02;
LABEL_52:
  sBtlDebug_DrawNormalList_Col(*p_sblist_visualmenu02_e, 3, visualcsr->point - 8, v31, 14, 122);
  cylinder = EffCylinderData->cylinder;
  v70 = visualcsr->point;
  sbattleDrawFloat_Num(186, 136, cylinder, v70, 9);
  sbattleDrawFloat_Num(186, 148, EffCylinderData->height, visualcsr->point, 10);
  v72 = visualcsr->point;
  if (v72 >= 4)
  {
    if ((u32)v72 > 0xA)
      goto LABEL_59;
    v165 = x;
    v166 = y;
    v147 = *(u64 *)&EffCylinderData->x;
    v168 = v34;
    v148 = v35;
    z = EffCylinderData->z;
    v150 = Unit->rot.x;
    v151 = Unit->rot.y;
    v153 = Unit->rot.z;
    w = Unit->rot.w;
    v180.x = v150;
    v180.y = v151;
    v180.z = v153;
    v180.w = w;
    sBtlGetRotateDeg(v180, 180.0);
    ToMatrix();
    *(u64 *)&vct_A.x = v147;
    vct_A.z = z;
    vct_A.w = v54;
    v35 = v148;
    v34 = v168;
    get_transpose(&data, &mtx_A, 0);
    v175 = data;
    v177 = op_Multiply_60923920(&v175, vct_A, 0);
    vct_A = v177;
    v159 = EffCylinderData->cylinder;
    height = EffCylinderData->height;
    v73 = m_data;
    v161 = vct_A.y + Unit->pos.y;
    v54 = vct_A.w;
    v162 = vct_A.x + Unit->pos.x;
    v163 = vct_A.z + Unit->pos.z;
    v182.y = v161;
    v182.z = v163;
    v182.w = v54;
    memset(&v173, 0, sizeof(v173));
    v182.x = v162;
    _3DCylinderDraw(v182, v159, height, 0x80101030, 0, &v173);
    x = v165;
    y = v166;
    goto LABEL_63;
  }
  if (v72 == 3)
  {
    v73 = m_data;
    goto LABEL_63;
  }
LABEL_59:
  v73 = m_data;
  DeleteLine(0);
LABEL_63:
  v76 = sblist_visualmenu07[0];
  DbgText(224, 1328, v76, 6, 109, 24, 0);
  v78 = sblist_visualmenu07[1];
  DbgText(224, 1424, v78, 6, 109, 24, 0);
  v80 = sblist_visualmenu07[2];
  DbgText(224, 1520, v80, 6, 109, 24, 0);
  sbattleDrawFloat_Num(186, 176, x, visualcsr->point, 11);
  sbattleDrawFloat_Num(186, 188, y, visualcsr->point, 12);
  sBtlDebug_DrawNormalList_Col(sblist_visualmenu08, 1, visualcsr->point - 13, -1, 14, 218);
  sbattleDrawString(160, 216, *(char **)((s64)(char *)v17 + 8 * sbtldbwk->vs_shildflg + 32), visualcsr->point, 13);
  v88 = sblist_visualmenu09[0];
  DbgText(224, 1936, v88, 6, 109, 24, 0);
  v90 = sblist_visualmenu09[1];
  DbgText(224, 2032, v90, 6, 109, 24, 0);
  v92 = sblist_visualmenu09[2];
  DbgText(224, 2128, v92, 6, 109, 24, 0);
  sbattleDrawFloat_Num(186, 252, v34, visualcsr->point, 14);
  sbattleDrawFloat_Num(186, 264, v35, visualcsr->point, 15);
  sBtlDebug_DrawNormalList_Col(sblist_visualmenu03, 4, visualcsr->point - 16, -1, 14, 290);
  sbattleDrawFloat_Num(186, 288, vsdata->m_speed, visualcsr->point, 16);
  sbattleDrawFloat_Num(186, 300, vsdata->rot_spd, visualcsr->point, 17);
  sbattleDrawFloat_Num(186, 312, vsdata->mv_spd, visualcsr->point, 18);
  sBtlDebug_DrawNormalList_Col(sblist_visualmenu04, 11, visualcsr->point - 20, 0, 14, 346);
  if (Unit->major)
  {
    p_motion_tbl_new = &motion_tbl_new;
  }
  else
  {
    p_motion_tbl_new = &motion_tbl_player;
  }
  sbattleDrawString(160, 360, (*p_motion_tbl_new)[sbtldbwk->vs_mtnno], visualcsr->point, 21);
  v107 = visualcsr->point;
  v108 = *v170;
  sbattleDrawString(160, 372, v108, v107, 22);
  sbattleDrawFloat_Num(186, 384, v73->e_startrate, visualcsr->point, 23);
  sbattleDrawFloat_Num(186, 396, v73->m_stoprate, visualcsr->point, 24);
  sbattleDrawString(160, 408, v169[v73->end_motionno + 4], visualcsr->point, 25);
  sbattleDrawFloat_Num(186, 420, v73->m_speed, visualcsr->point, 26);
  sbattleDrawFloat_Num(186, 432, v73->m_mv_area_r, visualcsr->point, 27);
  v116 = visualcsr->point;
  if (v116 == 27)
  {
    v117 = Unit->pos.x;
    v118 = Unit->pos.z;
    m_mv_area_r = v73->m_mv_area_r;
    v120 = vsdata->nml->height;
    v121 = Unit->pos.y + (f32)(v120 * -0.5);
    v179.y = v121;
    v179.z = v118;
    v179.w = v54;
    memset(&v172, 0, sizeof(v172));
    v179.x = v117;
    _3DCylinderDraw(v179, m_mv_area_r, v120, 0x80103010, 0, &v172);
    v116 = visualcsr->point;
  }
  m_hokanrate = v73->m_hokanrate;
  sbattleDrawFloat_Num(186, 444, m_hokanrate, v116, 28);
  sbattleDrawFloat_Num(186, 456, 0.0, visualcsr->point, 29);
  sbattleDrawFloat_Num(186, 468, (f32)v73->se_rate, visualcsr->point, 30);
  if (sbtldbwk->vs_posp)
  {
    p_sblist_visualmenu06_0 = &sblist_visualmenu06_0;
  }
  else
  {
    p_sblist_visualmenu06_0 = &sblist_visualmenu06;
  }
  sBtlDebug_DrawNormalList_Col(*p_sblist_visualmenu06_0, 1, visualcsr->point - 31, -1, 14, 502);
  hModel = Unit->hModel;
  MotionFrame = mdlGetMotionFrame(hModel);
  MotionLength = mdlGetMotionLength(Unit->hModel);
  data.m00 = MotionFrame;
  v132 = Box(f32, &data);
  v133 = Format("FRAME   :{0,4:f1}", v132, 0);
  v175.m00 = MotionLength;
  v134 = Box(f32, &v175);
  v135 = Format("{0,4:f1}", v134, 0);
  v136 = Concat_54832128(0, v133, "/", v135, 0);
  DbgText(1824, 3984, v136, 0, 109, 24, 0);
  v137 = mdlGetMotionFrame(Unit->hModel);
  if ((motion_flg[0] & m_data->flg) != 0)
    p_m_speed = &v73->m_speed;
  else
    p_m_speed = &vsdata->m_speed;
  v139 = v137 / *p_m_speed;
  data.m00 = v137 / (f32)(*p_m_speed + *p_m_speed);
  v140 = Box(f32, &data);
  v141 = Format("FRAME2   :{0,4:f1}", v140, 0);
  v175.m00 = v139;
  v142 = Box(f32, &v175);
  v143 = Format("{0,4:f1}", v142, 0);
  v144 = Concat_54832128(v136, v141, "/", v143, 0);
  DbgText(1824, 4112, v144, 0, 109, 24, 0);
  return 1;
}

// 0x19118e0
bool sbattleVisualHitProc(dds3ProcessID_t *id) {
  return 1;
}

// 0x19118f0
bool sbattleVisualHitDraw(dds3ProcessID_t *id) {
  return 1;
}

// 0x1911960
bool sbattleSkillChangeProc(dds3ProcessID_t *id) {
  SBDEBUG_CSRWORK *sklccsr;
  SBTLDEBUG_WORK *v6;
  s32 v10;
  s32 v11;
  s32 v12;
  s32 point;
  s32 v14;
  s32 v15;
  SBTLDEBUG_WORK *v17;

  sklccsr = sbtldbwk->sklccsr;
  sbattleGetUnit(sbtldbwk->mdlslcsr->point);
  if (CHECK_TRIG2(4096))
  {
    v6 = sbtldbwk;
    v6->change_skillid = sklccsr->point;
LABEL_13:
    v6->mode = 2;
    goto LABEL_14;
  }
  if (CHECK_TRIG2(4097))
  {
    v6 = sbtldbwk;
    goto LABEL_13;
  }
  if (CHECK_REP2(4105))
  {
    v10 = sklccsr->point - 10;
    sklccsr->point = v10;
    if (v10 >= 0)
      goto LABEL_14;
LABEL_22:
    sklccsr->point = sklccsr->maxp - 1;
    goto LABEL_14;
  }
  if (CHECK_REP2(4100))
  {
    v11 = sklccsr->point - 1;
    sklccsr->point = v11;
    if (v11 >= 0)
      goto LABEL_14;
    goto LABEL_22;
  }
  if (CHECK_REP2(4108))
  {
    v12 = sklccsr->point + 10;
    if (v12 >= sklccsr->maxp)
      v12 = 0;
    sklccsr->point = v12;
  }
  else if (CHECK_REP2(4101))
  {
    point = sklccsr->point;
    if (point + 1 < sklccsr->maxp)
      v14 = point + 1;
    else
      v14 = 0;
    sklccsr->point = v14;
  }
  else if (CHECK_REP2(4098))
  {
    v15 = sklccsr->point;
    if (sBtlCheckSABFile(v15) != -1)
    {
      v17 = sbtldbwk;
      v17->prev_skillid = sklccsr->point;
      v17->padmode = 1;
    }
  }
LABEL_14:
  sbattleSBtlDebug_Skill();
  return 1;
}

// 0x1912510
bool sbattleSkillChangeDraw(dds3ProcessID_t *id) {
  SBDEBUG_CSRWORK *sklccsr;
  s32 point;
  bool v8;
  s32 v9;
  s32 offset;
  s32 v11;
  s32 v12;
  s32 v13;
  char *v14;
  s32 v15;
  s32 v16;
  Il2CppObject *v17;
  char *v18;
  char *v19;
  char *v21;
  char *v22;
  char *SkillNameFont;
  char *v25;
  s32 unitmode;
  s32 data;

  sklccsr = sbtldbwk->sklccsr;
  sbattleGetUnit(sbtldbwk->mdlslcsr->point);
  unitmode = sbtldbwk->unitmode;
  if (!unitmode)
  {
    point = sklccsr->point;
    v8 = __OFSUB__(point, 24);
    v9 = point - 24;
    if (v9 < 0 != v8)
      offset = 0;
    else
      offset = v9;
    sklccsr->offset = offset;
    offset = sklccsr->offset;
    v11 = 0;
    v12 = 64;
    do
    {
      v16 = offset + v11;
      if (offset + v11 >= sklccsr->maxp)
        return unitmode == 0;
      data = v11 + sklccsr->offset;
      v17 = Box(s32, &data);
      v18 = Format("{0,0:X3}", v17, 0);
      v19 = Concat_54831728(0, "0x", v18, 0);
      if (v11 != sklccsr->point - sklccsr->offset)
      {
        SkillNameFont = sBtlGetSkillNameFont(v16);
        v25 = Concat_54831728(v19, " ", SkillNameFont, 0);
        v13 = v12;
        v14 = v25;
        v15 = -1600273536;
        goto LABEL_16;
      }
      v21 = sBtlGetSkillNameFont(v16);
      v22 = Concat_54831728(v19, " ", v21, 0);
      v13 = v12;
      v14 = v22;
      v15 = 1692838528;
LABEL_16:
      DbgText(48, v13, v14, v15, 109, 24, 0);
      ++v11;
      v12 += 128;
    }
    while (v11 != 26);
  }
  return unitmode == 0;
}

// 0x1912820
bool sbattleOptionProc(dds3ProcessID_t *id) {
  SBDEBUG_CSRWORK *opticsr;
  u64 v6;
  s64 point;
  s32 v12;
  s64 v15;
  SBTLDEBUG_WORK *v17;
  s32 v18;
  bool v19;
  s64 v21;
  SBTLDEBUG_WORK *v23;
  s32 v24;
  bool v25;
  s32 v30;
  s32 v31;
  SBTLDEBUG_WORK *v33;
  s32 v34;
  s32 v35;
  s32 v36;
  SBTLDEBUG_WORK *v39;
  s32 v40;
  SBTLDEBUG_WORK *v44;
  SBTLDEBUG_WORK *v46;
  s32 v47;
  SBTLDEBUG_WORK *v50;
  s32 v51;
  s32 v53;
  s32 v54;
  s32 v55;
  s32 v56;

  opticsr = sbtldbwk->opticsr;
  if (CHECK_PRESS2(4108) && CHECK_TRIG2(4097))
  {
    v6 = sbtldbwk->status & 0xFFFFFFFFFBF1BD31LL;
    sbtldbwk->y_status &= 0xFFFFFFFFFFFFFF8FLL;
    sbtldbwk->status = v6 | 0x40E0046;
    goto LABEL_11;
  }
LABEL_11:
  if (CHECK_TRIG2(4096))
  {
    point = (u32)opticsr->point;
    if ((s32)point < 3)
    {
LABEL_15:
      sBtlDebug_SetStatusflg(point, sbflg_optimenu, 0);
      return 1;
    }
    if ((u32)point <= 0x25)
    {
      if (((1 << point) & 0x2000D00000LL) != 0)
        goto LABEL_15;
      if (point == 35)
      {
        wk->mag = sbtldbwk->set_mag;
        return 1;
      }
    }
    return 1;
  }
  if (CHECK_TRIG2(4097))
  {
    v12 = opticsr->point;
    if (v12 > 2)
      return 1;
    sBtlDebug_SetStatusflg(v12, sbflg_optimenu, 1);
    return 1;
  }
  if (CHECK_TRIG2(4103))
  {
    v15 = (u32)opticsr->point;
    if ((s32)v15 < 3)
      goto LABEL_28;
    if ((u32)v15 <= 0x23)
    {
      if (((1 << v15) & 0x9A0800000LL) != 0)
      {
LABEL_28:
        if ((u32)v15 != 35)
          goto LABEL_29;
        goto LABEL_85;
      }
      if (v15 == 22)
        return 1;
    }
    sBtlDebug_SetStatusflg(v15, sbflg_optimenu, 0);
    LODWORD(v15) = opticsr->point;
    if ((u32)v15 != 35)
    {
LABEL_29:
      if ((u32)v15 != 1)
        return 1;
      v17 = sbtldbwk;
      v18 = v17->all_dead_raito + 1;
      v19 = v17->all_dead_raito - 100 < 0;
      v17->all_dead_raito = v18;
      if (v19 != __OFSUB__(v18, 101))
        return 1;
      goto LABEL_62;
    }
LABEL_85:
    v39 = sbtldbwk;
    v40 = v39->set_mag + 1;
    v39->set_mag = v40;
    goto LABEL_89;
  }
  if (CHECK_TRIG2(4102))
  {
    v21 = (u32)opticsr->point;
    if ((s32)v21 < 3)
      goto LABEL_38;
    if ((u32)v21 <= 0x23)
    {
      if (((1 << v21) & 0x9A0800000LL) != 0)
      {
LABEL_38:
        if ((u32)v21 != 35)
          goto LABEL_39;
LABEL_109:
        v50 = sbtldbwk;
        v51 = v50->set_mag - 1;
        v50->set_mag = v51;
        if (v51 >= 0)
          return 1;
        goto LABEL_112;
      }
      if (v21 == 22)
        return 1;
    }
    sBtlDebug_SetStatusflg(v21, sbflg_optimenu, 1);
    LODWORD(v21) = opticsr->point;
    if ((u32)v21 != 35)
    {
LABEL_39:
      if ((u32)v21 != 1)
        return 1;
      v23 = sbtldbwk;
      v24 = v23->all_dead_raito - 1;
      v25 = v23->all_dead_raito == 1;
      v23->all_dead_raito = v24;
      if (v24 >= 0 && !v25)
        return 1;
      goto LABEL_44;
    }
    goto LABEL_109;
  }
  if (CHECK_TRIG2(4107))
  {
    v30 = opticsr->point;
    if (v30 != 35)
    {
      if (v30 != 1)
        return 1;
      v17 = sbtldbwk;
      v31 = v17->all_dead_raito + 10;
      v19 = v17->all_dead_raito - 91 < 0;
      v17->all_dead_raito = v31;
      if (v19 != __OFSUB__(v31, 101))
        return 1;
LABEL_62:
      v17 = sbtldbwk;
      v17->all_dead_raito = 1;
      return 1;
    }
    v44 = sbtldbwk;
    v40 = v44->set_mag + 10;
    v44->set_mag = v40;
LABEL_89:
    if (v40 <= wk->magMax)
      return 1;
    sbtldbwk->set_mag = 0;
    return 1;
  }
  if (CHECK_TRIG2(4108))
  {
    if (opticsr->point != 11)
      return 1;
    v33 = sbtldbwk;
    v34 = v33->enemy_stop_mode + 1;
    v19 = v33->enemy_stop_mode - 1 < 0;
    v33->enemy_stop_mode = v34;
    if (v19 != __OFSUB__(v34, 2))
      return 1;
    v33 = sbtldbwk;
    v33->enemy_stop_mode = 0;
    return 1;
  }
  if (CHECK_TRIG2(4104))
  {
    v35 = opticsr->point;
    if (v35 != 35)
    {
      if (v35 != 1)
        return 1;
      v23 = sbtldbwk;
      v36 = v23->all_dead_raito - 10;
      v25 = v23->all_dead_raito == 10;
      v23->all_dead_raito = v36;
      if (v36 >= 0 && !v25)
        return 1;
LABEL_44:
      v23 = sbtldbwk;
      v23->all_dead_raito = 100;
      return 1;
    }
    v50 = sbtldbwk;
    v54 = v50->set_mag - 10;
    v50->set_mag = v54;
    if (v54 >= 0)
      return 1;
LABEL_112:
    v50 = sbtldbwk;
    v50->set_mag = wk->magMax;
    return 1;
  }
  if (!CHECK_TRIG2(4105))
  {
    if (CHECK_REP2(4100))
    {
      v53 = opticsr->point - 1;
      opticsr->point = v53;
      if (v53 < 0)
      {
        opticsr->point = opticsr->maxp - 1;
        return 1;
      }
    }
    else if (CHECK_REP2(4101))
    {
      v55 = opticsr->point;
      if (v55 + 1 < opticsr->maxp)
        v56 = v55 + 1;
      else
        v56 = 0;
      opticsr->point = v56;
      return 1;
    }
    return 1;
  }
  if (opticsr->point != 11)
    return 1;
  v46 = sbtldbwk;
  v47 = v46->enemy_stop_mode - 1;
  v46->enemy_stop_mode = v47;
  if (v47 >= 0)
    return 1;
  v46 = sbtldbwk;
  v46->enemy_stop_mode = 1;
  return 1;
}

// 0x1913080
bool sbattleOptionDraw(dds3ProcessID_t *id) {
  s32 encountno;

  NewSpecific(sbyte, 0x40u);
  if (!wk)
    return 0;
  if (!wk->UnitMng)
    return 0;
  if ((sbtldbwk->status & 0x10) == 0)
    return 0;
  MenuActive(0);
  sBtlDebug_DrawCursor(2, 10, sbtldbwk->opticsr);
  sBtlDebug_DrawNormalList(sblist_optimenu, 38, sbtldbwk->opticsr->point, 14, 10, 0);
  sBtlDebug_DrawONOFFList(sbflg_optimenu, 38, 194, 10);
  encountno = wk->encountno;
  if (encountno == 482)
    goto LABEL_30;
  if (encountno == 483)
    goto LABEL_30;
  encountno = wk->encountno;
  if (encountno != 484)
    return 1;
LABEL_30:
  return 1;
}

// 0x1913360
bool sbattleEffEditorProc(dds3ProcessID_t *id) {
  s64 status;

  status = sbtldbwk->status;
  sbtldbwk->mode = 10;
  sbtldbwk->status = status & 0xFFFFFFFFFFFFFFDFLL;
  RestartBattle();
  return 1;
}

// 0x1913420
bool sbattleEffEditorDraw(dds3ProcessID_t *id) {
  return 0;
}

// 0x1913430
bool sbattleEffHitEditorProc(dds3ProcessID_t *id) {
  s64 status;

  status = sbtldbwk->status;
  sbtldbwk->mode = 10;
  sbtldbwk->status = status & 0xFFFFFFFFFFFFFFDFLL;
  RestartBattle();
  return 1;
}

// 0x19134f0
bool sbattleEffHitEditorDraw(dds3ProcessID_t *id) {
  return 1;
}

// 0x1913500
bool sbattleMdlHitEditorProc(dds3ProcessID_t *id) {
  s64 status;

  status = sbtldbwk->status;
  sbtldbwk->mode = 10;
  sbtldbwk->status = status & 0xFFFFFFFFFFFFFFDFLL;
  RestartBattle();
  return 1;
}

// 0x19135c0
bool sbattleMdlHitEditorDraw(dds3ProcessID_t *id) {
  return 1;
}

// 0x19135d0
void sbattleSetSword(void) {
  SBATTLE_WORK *v5;
  s32 weaponId;
  sdatPlayerUnitWork_t *player;

  if (!sbtldbwk->weaponId)
    return;
  wk->weaponId = sbtldbwk->weaponId;
  v5 = wk;
  weaponId = v5->weaponId;
  GBWK->player->swordno = weaponId;
  v5->equipsord = weaponId;
  datSetPlayerSword((s16)weaponId, 0);
  player = GBWK->player;
  datCalcNowParam(player->para, player->swordno, 0);
  datDvlParaUpdate(0);
}

// 0x1913770
bool sbattleSetDebugMenuProc(dds3ProcessID_t *id) {
  sdatParaWork_t *v2;
  SBDEBUG_CSRWORK *setcsr;
  s32 resetencount;
  SB_ENCOUNTPAC *EncountPac;
  SBATTLE_WORK *v11;
  s64 encountno;
  SBTLSCENE_WORK *scene;
  SB_ENCOUNTPAC *v14;
  u32 start_map;
  bool v17;
  SBTLDEBUG_WORK *v18;
  s64 v19;
  SBATTLE_WORK *v22;
  SBTLDEBUG_WORK *v25;
  s32 v26;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLDEBUG_WORK *v29;
  s32 mapmdl;
  s32 weaponId;
  s64 status;
  s32 playerID;
  u32 v35;
  SBTLUNIT_WORK *v36;
  sdatUnitWork_t *para;
  sdatUnitWork_t *v41;
  int16x4_t v43;
  int16x4_t *backup;
  int16x4_t v46;
  u32 v47;
  SBTLUNIT_WORK *v49;
  sdatParaWork_t *now;
  sdatParaWork_t *v52;
  s32 maxhp;
  u32 v55;
  SBATTLE_WORK *v56;
  SBTLUNIT_LISTWORK *v58;
  s32 v59;
  SBTLUNIT_WORK *v60;
  SBTLUNIT_LISTWORK *v62;
  s32 v63;
  SBTLUNIT_WORK *v64;
  SBATTLE_WORK *v66;
  SBTLUNIT_LISTWORK *v67;
  s32 v68;
  f32 v69;
  s32 *p_encountno;
  SBTLDEBUG_WORK *v73;
  u64 v74;
  s32 i;
  SBATTLE_WORK *v79;
  s32 point;
  s8 v84;
  SBATTLE_WORK *v85;
  s64 v86;
  sdatUnitWork_t *v87;
  s32 devilid;
  DEVILDATA_WORK *DevilData;
  SKLID *haveskill;
  DEVILDATA_WORK *v91;
  s32 v92;
  SKLID *battleskill;
  s32 v94;
  s32 v95;
  s64 v96;
  char *v97;
  char *v98;
  s32 v99;
  s64 v100;
  char *v101;
  char *v102;
  s32 v103;
  s64 v104;
  char *v105;
  char *v106;
  s32 v107;
  s64 v108;
  char *v109;
  char *v110;
  s32 v111;
  s64 v112;
  char *v113;
  char *v114;
  s32 v115;
  s64 v116;
  char *v117;
  char *v118;
  s32 v119;
  s64 v120;
  char *v121;
  char *v122;
  SKLID *aRsvSkl;
  s32 skill;
  s32 v127;
  SBATTLE_WORK *v129;
  s8 v130;
  s32 v132;
  s32 v133;
  s32 v137;
  SBTLDEBUG_WORK *v140;
  u32 *p_raidouP;
  s32 v142;
  SBTLDEBUG_WORK *v144;
  s32 *p_mapmdl;
  s32 v146;
  SBTLDEBUG_WORK *v148;
  s32 *p_weaponId;
  s32 v150;
  SBATTLE_WORK *v152;
  s32 v153;
  SBTLDEBUG_WORK *v155;
  s32 v156;
  SBTLDEBUG_WORK *v159;
  s32 max_length;
  s32 v161;
  s32 v162;
  s32 *v166;
  s32 v167;
  SBTLDEBUG_WORK *v176;
  s32 v177;
  s32 v184;
  SBDEBUG_CSRWORK *v194;

  v2 = Allocate(sdatParaWork_t);
  *(_OWORD *)&v2->hp = xmmword_3CFBEB0;
  *(u64 *)&v2->str = 0x3000600050006LL;
  setcsr = sbtldbwk->setcsr;
  resetencount = (u16)sbtldbwk->resetencount;
  if (resetencount != 2)
    goto LABEL_5;
  v22 = wk;
  UnitMng = v22->UnitMng;
  v29 = sbtldbwk;
  mapmdl = v29->mapmdl;
  weaponId = v29->weaponId;
  status = v29->status;
  v29->mode = 0;
  wk->mapmdl = mapmdl;
  v22->weaponId = weaponId;
  playerID = v22->playerID;
  v29->status = status & 0xFFFFFFFF7FFFFFFFLL;
  if (!v35)
  v36 = sBtlSearchUnit_ID(UnitMng, playerID);
  if (v36)
  {
    v36->actwk->status = 10;
    v36->mode = 9;
  }
  para = GBWK->player->para;
  v41 = GBWK->player->para;
  v43.n64_u64[0] = *(u64 *)&v2->str;
  para->level = sbtldbwk->raidouP;
  backup = v41->backup;
  v46.n64_u64[0] = vdup_n_s16(v41->level >> 2).n64_u64[0];
  backup[4].n64_u64[0] = vadd_s16(v43, v46).n64_u64[0];
  if (v47)
  {
    sBtlSetPlayerData(0);
    goto LABEL_58;
  }
  else
  {
    sBtlSetPlayerData(0);
    goto LABEL_58;
  }
LABEL_58:
  v49 = sBtlSearchUnit_ID(wk->UnitMng, wk->playerID);
  datCalcNowParam(v49->para, 0, 0);
  now = v49->para->now;
  v52 = v49->para->backup;
  maxhp = v52->maxhp;
  now->hp = maxhp;
  now->maxhp = maxhp;
  v52->hp = maxhp;
  v56 = wk;
  if (v56->battlemode == 3)
  {
    if (v55)
    {
      v58 = v56->UnitMng;
      v59 = v56->playerID;
      goto LABEL_61;
    }
    else
    {
      v85 = wk;
      v58 = v85->UnitMng;
      v59 = v85->playerID;
LABEL_61:
      v60 = sBtlSearchUnit_ID(v58, v59);
      if (!v60)
        goto LABEL_117;
LABEL_115:
      v69 = -400.0;
LABEL_116:
      v60->pos.z = v60->pos.z + v69;
      goto LABEL_117;
    }
    v60 = sBtlSearchUnit_ID(v58, v59);
    if (!v60)
    {
LABEL_117:
      if (!sbtldbwk->bKyousei)
      {
LABEL_150:
LABEL_152:
        if (sbtldbwk->resetencount <= 0)
          goto LABEL_14;
        return 0;
LABEL_151:
        goto LABEL_152;
      }
      v194 = setcsr;
      v86 = 32;
      while (1)
      {
        v87 = *(sdatUnitWork_t *)((char *)&sBtlGetPlayerData()->stock_id->obj.klass + v86);
        devilid = v87->devilid;
        if (v87->devilid)
          break;
LABEL_122:
        v86 += 8;
        if (v86 == 288)
        {
          setcsr = v194;
          goto LABEL_150;
        }
      }
      DevilData = sBtlGetDevilData(devilid, -1);
      haveskill = DevilData->haveskill;
      v91 = DevilData;
      v92 = haveskill[0];
      if (v92)
      {
        battleskill = v87->battleskill;
        v94 = 0;
        v87->haveskill[0] = v92;
        battleskill[0] = v92;
        v95 = haveskill[1];
        if (v95)
          goto LABEL_128;
      }
      else
      {
        v94 = 1;
        v95 = haveskill[1];
        if (v95)
        {
LABEL_128:
          v96 = 4 * (v94 ^ 1u);
          v97 = (char *)v87->haveskill + v96;
          v98 = (char *)v87->battleskill + v96;
          *((u32 *)v97 + 8) = v95;
          *((u32 *)v98 + 8) = v95;
          v99 = haveskill[2];
          if (v99)
            goto LABEL_129;
          goto LABEL_143;
        }
      }
      ++v94;
      v99 = haveskill[2];
      if (v99)
      {
LABEL_129:
        v100 = 4 * (u32)(2 - v94);
        v101 = (char *)v87->haveskill + v100;
        v102 = (char *)v87->battleskill + v100;
        *((u32 *)v101 + 8) = v99;
        *((u32 *)v102 + 8) = v99;
        v103 = haveskill[3];
        if (v103)
          goto LABEL_130;
        goto LABEL_144;
      }
LABEL_143:
      ++v94;
      v103 = haveskill[3];
      if (v103)
      {
LABEL_130:
        v104 = 4 * (u32)(3 - v94);
        v105 = (char *)v87->haveskill + v104;
        v106 = (char *)v87->battleskill + v104;
        *((u32 *)v105 + 8) = v103;
        *((u32 *)v106 + 8) = v103;
        v107 = haveskill[4];
        if (v107)
          goto LABEL_131;
        goto LABEL_145;
      }
LABEL_144:
      ++v94;
      v107 = haveskill[4];
      if (v107)
      {
LABEL_131:
        v108 = 4 * (u32)(4 - v94);
        v109 = (char *)v87->haveskill + v108;
        v110 = (char *)v87->battleskill + v108;
        *((u32 *)v109 + 8) = v107;
        *((u32 *)v110 + 8) = v107;
        v111 = haveskill[5];
        if (v111)
          goto LABEL_132;
        goto LABEL_146;
      }
LABEL_145:
      ++v94;
      v111 = haveskill[5];
      if (v111)
      {
LABEL_132:
        v112 = 4 * (u32)(5 - v94);
        v113 = (char *)v87->haveskill + v112;
        v114 = (char *)v87->battleskill + v112;
        *((u32 *)v113 + 8) = v111;
        *((u32 *)v114 + 8) = v111;
        v115 = haveskill[6];
        if (v115)
          goto LABEL_133;
        goto LABEL_147;
      }
LABEL_146:
      ++v94;
      v115 = haveskill[6];
      if (v115)
      {
LABEL_133:
        v116 = 4 * (u32)(6 - v94);
        v117 = (char *)v87->haveskill + v116;
        v118 = (char *)v87->battleskill + v116;
        *((u32 *)v117 + 8) = v115;
        *((u32 *)v118 + 8) = v115;
        v119 = haveskill[7];
        if (!v119)
        {
LABEL_135:
          aRsvSkl = v87->aRsvSkl;
          aRsvSkl[2] = 0;
          *(u64 *)aRsvSkl = 0;
          skill = v91->memskill[0]->skill;
          v87->aOmoideSkill[0] = skill;
          datOmoideSkillSetMaster(v87, skill, 1);
          v127 = v91->memskill[1]->skill;
          v87->aOmoideSkill[1] = v127;
          datOmoideSkillSetMaster(v87, v127, 1);
          datNewCombiSkilAutoSet(v87);
          goto LABEL_122;
        }
LABEL_134:
        v120 = 4 * (u32)(7 - v94);
        v121 = (char *)v87->haveskill + v120;
        v122 = (char *)v87->battleskill + v120;
        *((u32 *)v121 + 8) = v119;
        *((u32 *)v122 + 8) = v119;
        goto LABEL_135;
      }
LABEL_147:
      ++v94;
      v119 = haveskill[7];
      if (!v119)
        goto LABEL_135;
      goto LABEL_134;
    }
    goto LABEL_115;
  }
  if (v55)
  {
    v62 = v56->UnitMng;
    v63 = v56->playerID;
    goto LABEL_65;
  }
  else
  {
    v129 = wk;
    v62 = v129->UnitMng;
    v63 = v129->playerID;
LABEL_65:
    v64 = sBtlSearchUnit_ID(v62, v63);
    if (!v64)
    {
LABEL_67:
      v66 = wk;
      if (v66->member_num < 1)
        goto LABEL_117;
      v66 = wk;
      v67 = v66->UnitMng;
      v68 = v66->summonID[v66->summonindex[0]];
      v60 = sBtlSearchUnit_ID(v67, v68);
      if (!v60)
        goto LABEL_117;
      v69 = -600.0;
      goto LABEL_116;
    }
LABEL_66:
    v64->pos.z = v64->pos.z + -400.0;
    goto LABEL_67;
  }
  v64 = sBtlSearchUnit_ID(v62, v63);
  if (!v64)
    goto LABEL_67;
  goto LABEL_66;
LABEL_5:
  if (resetencount != 1)
    goto LABEL_151;
  EncountPac = sBtlGetEncountPac(-1);
  v11 = wk;
  encountno = v11->encountno;
  scene = v11->scene;
  v14 = EncountPac[encountno];
  start_map = v14->start_map;
  LODWORD(v14) = v14->start_floor;
  scene->major = start_map;
  scene->minor = (u32)v14;
  ++sbtldbwk->resetencount;
  goto LABEL_152;
LABEL_14:
  if (CHECK_PRESS(4104, 1) && CHECK_PRESS(4107, 1) && CHECK_PRESS(4111, 1) && CHECK_PRESS(4110, 1))
  {
    v17 = 0;
    v18 = sbtldbwk;
    v19 = v18->status;
    v18->mode = 0;
    v18->status = v19 & 0xFFFFFFFF7FFFFFFFLL;
    return v17;
  }
  if (CHECK_TRIG(4099, 1))
  {
    dds3FadeIn(0x80u, 0x80u, 0x80u, 8u);
    v25 = sbtldbwk;
    v26 = ++v25->dvlStkPtn;
    if (v26 >= 6)
    {
      v25 = sbtldbwk;
      v25->dvlStkPtn = 0;
    }
    sBtlDebug_SetDuummyData(sbtldbwk->dvlStkPtn);
  }
  if (!CHECK_TRIG2(4108) || setcsr->point)
  {
    if (!CHECK_TRIG2(4105))
      goto LABEL_84;
    goto LABEL_40;
  }
  p_encountno = &wk->encountno;
  sBtlParaAdd(p_encountno, 256, 1024, 0);
  if (!CHECK_TRIG2(4105))
  {
LABEL_84:
    if (!CHECK_PRESS2(4108))
      goto LABEL_90;
LABEL_85:
    if (!CHECK_TRIG2(4097))
      goto LABEL_90;
    v17 = 1;
    v73 = sbtldbwk;
    v74 = v73->status & 0xFFFFFFFFFBF1BD31LL;
    v73->y_status &= 0xFFFFFFFFFFFFFF8FLL;
    v73->status = v74 | 0x40E0046;
    return v17;
  }
LABEL_40:
  if (setcsr->point)
    goto LABEL_84;
  sBtlDebug_SetEncountPara(1, 256);
  if (CHECK_PRESS2(4108))
    goto LABEL_85;
LABEL_90:
  if (CHECK_TRIG2(4096))
  {
    sbtldbwk->resetencount = 1;
    sbattleSetSword();
    mapObjClear();
    for (i = 1; i != 40; ++i)
    {
      if (i != 9)
      {
        datAddItem(i, 5);
      }
    }
    v79 = wk;
    if (v79->battlemode == 2)
    {
      v79 = wk;
      v17 = 1;
      v79->battlemode = 0;
      v79->is_jyuso = 1;
      return v17;
    }
    return 1;
  }
  if (CHECK_TRIG2(4097))
  {
    sbtldbwk->resetencount = 2;
    sbattleSetSword();
    return 1;
  }
  else if (CHECK_TRIG2(4107))
  {
    point = setcsr->point;
    v17 = 1;
    switch (point)
    {
      case 0:
        v84 = 0;
        goto LABEL_172;
      case 1:
        goto LABEL_202;
      case 13:
        goto LABEL_205;
      case 14:
        goto LABEL_208;
      case 15:
        v140 = sbtldbwk;
        p_raidouP = &v140->raidouP;
        v142 = v140->raidouP + 10;
        goto LABEL_300;
      case 16:
        v144 = sbtldbwk;
        p_mapmdl = &v144->mapmdl;
        v146 = v144->mapmdl + 10;
        goto LABEL_248;
      case 17:
        v148 = sbtldbwk;
        p_weaponId = &v148->weaponId;
        v150 = v148->weaponId + 10;
        goto LABEL_312;
      case 18:
        goto LABEL_194;
      case 20:
        goto LABEL_197;
      case 21:
        v152 = wk;
        p_weaponId = &v152->rouletteId;
        v153 = v152->rouletteId + 10;
        goto LABEL_319;
      case 22:
        goto LABEL_200;
      case 23:
        v155 = sbtldbwk;
        p_weaponId = &v155->dlcsel;
        v156 = v155->dlcsel + 10;
        goto LABEL_326;
      case 24:
        v159 = sbtldbwk;
        max_length = gDbg_Spirit_Table->max_length;
        v161 = v159->CmbSklSet + max_length + 10;
        goto LABEL_334;
      case 25:
      case 26:
        return v17;
      default:
        goto LABEL_212;
    }
  }
  else if (CHECK_TRIG2(4104))
  {
    v17 = 1;
    switch (setcsr->point)
    {
      case 0:
        v84 = 1;
LABEL_172:
        sBtlDebug_SetEncountPara(v84, 16);
        break;
      case 1:
        goto LABEL_202;
      case 0xD:
        goto LABEL_205;
      case 0xE:
        goto LABEL_208;
      case 0xF:
        v140 = sbtldbwk;
        p_raidouP = &v140->raidouP;
        v142 = v140->raidouP - 10;
        goto LABEL_300;
      case 0x10:
        v144 = sbtldbwk;
        p_mapmdl = &v144->mapmdl;
        v146 = v144->mapmdl - 10;
LABEL_248:
        v144->mapmdl = v146;
        v166 = p_mapmdl;
        v167 = 4;
        goto LABEL_330;
      case 0x11:
        v148 = sbtldbwk;
        p_weaponId = &v148->weaponId;
        v150 = v148->weaponId - 10;
        goto LABEL_312;
      case 0x12:
        goto LABEL_194;
      case 0x14:
        goto LABEL_197;
      case 0x15:
        v152 = wk;
        p_weaponId = &v152->rouletteId;
        v153 = v152->rouletteId - 10;
        goto LABEL_319;
      case 0x16:
        goto LABEL_200;
      case 0x17:
        v155 = sbtldbwk;
        p_weaponId = &v155->dlcsel;
        v156 = v155->dlcsel - 10;
        goto LABEL_326;
      case 0x18:
        v159 = sbtldbwk;
        max_length = gDbg_Spirit_Table->max_length;
        v161 = v159->CmbSklSet + max_length - 10;
        goto LABEL_334;
      default:
        return v17;
    }
  }
  else if (CHECK_TRIG2(4103))
  {
    point = setcsr->point;
    v17 = 1;
    switch (point)
    {
      case 0:
        v130 = 0;
        goto LABEL_186;
      case 1:
LABEL_202:
        sBtlDebug_SetBattleMode(0, (s32)v81);
        return v17;
      case 13:
LABEL_205:
        v137 = 0;
        goto LABEL_211;
      case 14:
LABEL_208:
        v137 = 1;
LABEL_211:
        sBtlDebug_SetNakamaNo(v137, 0, (s32)v82);
        break;
      case 15:
        v140 = sbtldbwk;
        p_raidouP = &v140->raidouP;
        v142 = v140->raidouP + 1;
        goto LABEL_300;
      case 16:
        v176 = sbtldbwk;
        p_weaponId = &sbtldbwk->mapmdl;
        v177 = *p_weaponId + 1;
        goto LABEL_306;
      case 17:
        v148 = sbtldbwk;
        p_weaponId = &v148->weaponId;
        v150 = v148->weaponId + 1;
        goto LABEL_312;
      case 18:
        goto LABEL_194;
      case 19:
        sBtlDebug_SetSenseiMode(0, (s32)v81);
        break;
      case 20:
        goto LABEL_197;
      case 21:
        v152 = wk;
        p_weaponId = &v152->rouletteId;
        v153 = v152->rouletteId + 1;
        goto LABEL_319;
      case 22:
        goto LABEL_200;
      case 23:
        v155 = sbtldbwk;
        p_weaponId = &v155->dlcsel;
        v156 = v155->dlcsel + 1;
        goto LABEL_326;
      case 24:
        v159 = sbtldbwk;
        max_length = gDbg_Spirit_Table->max_length;
        v161 = v159->CmbSklSet + max_length + 1;
        goto LABEL_334;
      case 25:
      case 26:
      case 27:
        return v17;
      default:
LABEL_212:
        sBtlDebug_SetStatusflg(point, sbflg_setmenu, 0);
        v17 = 1;
        break;
    }
  }
  else if (CHECK_TRIG2(4102))
  {
    v132 = setcsr->point;
    v17 = 1;
    switch (v132)
    {
      case 0:
        v130 = 1;
LABEL_186:
        sBtlDebug_SetEncountPara(v130, 1);
        return v17;
      case 1:
        sBtlDebug_SetBattleMode(1, (s32)v81);
        return v17;
      case 13:
        v184 = 0;
        goto LABEL_296;
      case 14:
        v184 = 1;
LABEL_296:
        sBtlDebug_SetNakamaNo(v184, 1, (s32)v131);
        return v17;
      case 15:
        v140 = sbtldbwk;
        p_raidouP = &v140->raidouP;
        v142 = v140->raidouP - 1;
LABEL_300:
        v140->raidouP = v142;
        LimitRange_3(p_raidouP, 1u, 0x63u);
        return v17;
      case 16:
        v176 = sbtldbwk;
        p_weaponId = &sbtldbwk->mapmdl;
        v177 = *p_weaponId - 1;
LABEL_306:
        v176->mapmdl = v177;
        v167 = LODWORD(mapModelInfo->max_length) - 1;
        goto LABEL_329;
      case 17:
        v148 = sbtldbwk;
        p_weaponId = &v148->weaponId;
        v150 = v148->weaponId - 1;
LABEL_312:
        v148->weaponId = v150;
        goto LABEL_320;
      case 18:
LABEL_194:
        sbtldbwk->bKyousei ^= 1u;
        return v17;
      case 19:
        sBtlDebug_SetSenseiMode(1, (s32)v81);
        return v17;
      case 20:
LABEL_197:
        sbtldbwk->bBossDbg ^= 1u;
        return v17;
      case 21:
        v152 = wk;
        p_weaponId = &v152->rouletteId;
        v153 = v152->rouletteId - 1;
LABEL_319:
        v152->rouletteId = v153;
LABEL_320:
        v167 = 99;
        goto LABEL_329;
      case 22:
LABEL_200:
        return v17;
      case 23:
        v155 = sbtldbwk;
        p_weaponId = &v155->dlcsel;
        v156 = v155->dlcsel - 1;
LABEL_326:
        v155->dlcsel = v156;
        v167 = 5;
LABEL_329:
        v166 = p_weaponId;
LABEL_330:
        LimitRange(v166, 0, v167);
        v17 = 1;
        break;
      case 24:
        v159 = sbtldbwk;
        max_length = gDbg_Spirit_Table->max_length;
        v161 = v159->CmbSklSet + max_length - 1;
LABEL_334:
        v159->CmbSklSet = v161 % max_length;
        sBtlDebug_SetDuummyData_Cmbskl(v161 % max_length);
        break;
      case 25:
      case 26:
      case 27:
        return v17;
      default:
        v17 = 1;
        sBtlDebug_SetStatusflg(v132, sbflg_setmenu, 1);
        break;
    }
  }
  else if (CHECK_REP2(4100))
  {
    v133 = setcsr->point;
    do
    {
      setcsr->point = --v133;
      if (v133 < 0)
      {
        v133 = setcsr->maxp - 1;
        setcsr->point = v133;
      }
      v133 = setcsr->point;
      v17 = 1;
    }
    while (!sblist_setmenu_flg[v133]);
  }
  else
  {
    if (!CHECK_REP2(4101))
      return 1;
    v162 = setcsr->point;
    v17 = 1;
    do
    {
      if (v162 + 1 < setcsr->maxp)
        ++v162;
      else
        v162 = 0;
      setcsr->point = v162;
      v162 = setcsr->point;
    }
    while (!sblist_setmenu_flg[v162]);
  }
  return v17;
}

// 0x1915d40
bool sbattleSetDebugMenuDraw(dds3ProcessID_t *id) {
  s32 weaponId;
  char *v13;
  s32 point;
  char *v18;
  char *v19;
  char *v21;

  if (!wk)
    return 0;
  if (!wk->UnitMng)
    return 0;
  if ((sbtldbwk->status & 0x80000000LL) == 0)
    return 0;
  sBtlDebug_DrawNormalList(sblist_setmenu_00, 1, 0, 174, 10, 0);
  sBtlDebug_DrawNormalList(sblist_setmenu_01, 29, sbtldbwk->setcsr->point, 174, 30, sblist_setmenu_flg);
  sBtlDebug_DrawONOFFList(sbflg_setmenu, 29, 362, 30);
  sBtlDebug_DevilNameListDraw(512, 270);
  weaponId = sbtldbwk->weaponId;
  v13 = sdatItemName(weaponId + 144);
  DbgText(0, 1920, v13, 0, 108, 24, 0);
  point = sbtldbwk->setcsr->point;
  if (point)
  {
    point = sbtldbwk->setcsr->point;
    if (point == 16)
    {
      v18 = mapModelInfo[sbtldbwk->mapmdl][0];
      DbgText(6400, 1792, v18, 0, 109, 24, 0);
    }
  }
  v19 = "Debug menu button changed from L3";
  DbgText(512, 3200, v19, 0, 109, 24, 0);
  v21 = "(PS4)L1 + SHARE  /  (Switch)L1 + -";
  DbgText(512, 3328, v21, 0, 109, 24, 0);
  return 1;
}

// 0x1916580
bool sbattleMdlMoveEditorProc(dds3ProcessID_t *id) {
  s64 status;

  status = sbtldbwk->status;
  sbtldbwk->mode = 10;
  sbtldbwk->status = status & 0xFFFFFFFFFFFFFFDFLL;
  RestartBattle();
  return 1;
}

// 0x1916640
bool sbattleMdlMoveEditorDraw(dds3ProcessID_t *id) {
  return 1;
}

// 0x1916650
bool sbattleBSTProc(dds3ProcessID_t *id) {
  SBDEBUG_CSRWORK *bstcsr;
  SBTLUNIT_WORK *Unit;
  s32 v8;
  s32 point;
  s32 v10;

  bstcsr = sbtldbwk->bstcsr;
  Unit = sbattleGetUnit(sbtldbwk->mdlslcsr->point);
  if (CHECK_TRIG(4096, 1))
  {
    if (Unit)
    {
      sBtlResetBadStatus(Unit, 0x3FFFF);
      sBtlSetMotion(Unit, 1, 0, 0, 0);
      sBtlSetBadStatus_No(Unit, 0, bstcsr->point, 0, -1);
      return 1;
    }
    LogError("ユニットデータが取得できない", 0);
    return 1;
  }
  else
  {
    if (!CHECK_TRIG(4097, 1))
    {
      if (CHECK_REP(4100, 1))
      {
        v8 = bstcsr->point - 1;
        bstcsr->point = v8;
        if (v8 < 0)
        {
          bstcsr->point = bstcsr->maxp - 1;
          return 1;
        }
      }
      else if (CHECK_REP(4101, 1))
      {
        point = bstcsr->point;
        if (point + 1 < bstcsr->maxp)
          v10 = point + 1;
        else
          v10 = 0;
        bstcsr->point = v10;
        return 1;
      }
      return 1;
    }
    sbtldbwk->mode = 2;
    return 1;
  }
}

// 0x19168a0
bool sbattleBSTDraw(dds3ProcessID_t *id) {
  SBDEBUG_CSRWORK *bstcsr;
  s32 point;
  bool v6;
  s32 v7;
  s32 offset;
  s32 v10;
  s32 v11;
  u32 v12;

  bstcsr = sbtldbwk->bstcsr;
  sbattleGetUnit(sbtldbwk->mdlslcsr->point);
  point = bstcsr->point;
  v6 = __OFSUB__(point, 13);
  v7 = point - 13;
  if (v7 < 0 != v6)
    offset = 0;
  else
    offset = v7;
  bstcsr->offset = offset;
  offset = bstcsr->offset;
  v10 = 0;
  v11 = 8;
  do
  {
    if (offset + v10 >= bstcsr->maxp)
      break;
    v12 = v10 == bstcsr->point - bstcsr->offset ? 1692838528 : -1600273536;
    sBtlDrawBSTName(16, v11, 0, v12, offset + v10++);
    v11 += 16;
  }
  while (v10 != 15);
  return 1;
}

// 0x19169f0
bool sbattleParaProc(dds3ProcessID_t *id) {
  SBDEBUG_CSRWORK *paracsr;
  SBTLUNIT_WORK *Unit;
  s32 v7;
  s32 point;
  s32 v9;
  s32 v11;
  SBTLUNIT_WORK *v12;
  s32 v13;
  sdatUnitWork_t *para;
  int32x4_t *now;
  s16 vice;
  SBATTLE_WORK *v24;

  paracsr = sbtldbwk->paracsr;
  Unit = sbattleGetUnit(sbtldbwk->mdlslcsr->point);
  if (CHECK_TRIG2(4097))
  {
    sbtldbwk->mode = 2;
    goto LABEL_42;
  }
  if (CHECK_REP2(4100))
  {
    v7 = paracsr->point - 1;
    paracsr->point = v7;
    if (v7 < 0)
      paracsr->point = paracsr->maxp - 1;
    goto LABEL_42;
  }
  if (CHECK_REP2(4101))
  {
    point = paracsr->point;
    if (point + 1 < paracsr->maxp)
      v9 = point + 1;
    else
      v9 = 0;
    paracsr->point = v9;
    goto LABEL_42;
  }
  if (CHECK_REP2(4108))
  {
    v11 = paracsr->point;
    v12 = Unit;
    v13 = 2;
LABEL_41:
    sbattleSetUnitPara(v12, v13, v11);
    goto LABEL_42;
  }
  if (CHECK_REP2(4103))
  {
    v11 = paracsr->point;
    v12 = Unit;
    v13 = 0;
    goto LABEL_41;
  }
  if (CHECK_REP2(4105))
  {
    v11 = paracsr->point;
    v12 = Unit;
    v13 = 3;
    goto LABEL_41;
  }
  if (CHECK_REP2(4102))
  {
    v11 = paracsr->point;
    v12 = Unit;
    v13 = 1;
    goto LABEL_41;
  }
  if (CHECK_REP2(4096))
  {
    v11 = paracsr->point;
    v12 = Unit;
    v13 = 4;
    goto LABEL_41;
  }
  if (CHECK_REP2(4099))
  {
    v11 = paracsr->point;
    v13 = 5;
    v12 = Unit;
    goto LABEL_41;
  }
  if (CHECK_PRESS(4108, 1) && CHECK_PRESS(4107, 1))
  {
    para = Unit->para;
    now = para->now;
    para->level = 99;
    now[1] = vdupq_n_s32(0x3E7u);
    now[2].n128_u64[0] = 0x28002800280028LL;
    para->vice = 4000;
    if ((Unit->side & 2) != 0)
    {
      vice = 4000;
      wk->spirit_enemy = vice;
      sBtlViceAddEnemyHD(Unit, 0, 0, 4000);
    }
    v24 = wk;
    v24->sprit_waza = 4000;
    *(u64 *)&v24->mag = 0x12C0000012CLL;
  }
LABEL_42:
  if (CHECK_TRIG2(4096) && paracsr->point == 9)
  {
    if (sbtldbwk->para_bstno != 22)
    {
      sBtlResetBadStatus(Unit, 0x3FFFF);
      sBtlSetMotion(Unit, 1, 0, 0, 0);
      sBtlSetBadStatus_No(Unit, 0, sbtldbwk->para_bstno, 0, -1);
    }
  }
  return 1;
}

// 0x19177f0
bool sbattleParaDraw(dds3ProcessID_t *id) {
  char *v2;
  char *v3;
  u64 *v4;
  char *v5;
  char *v6;
  char *v7;
  char *v8;
  char *v9;
  SBDEBUG_CSRWORK *paracsr;
  SBTLUNIT_WORK *Unit;
  s32 devilid;
  DEVILDATA_WORK *DevilData;
  f32 getchuusei;
  s32 getmoney;
  u32 para_bstno;
  u32 v40;
  s64 v42;
  s32 v43;
  s32 v45;
  char *v46;
  char *v47;
  char *v48;
  char *v49;
  char *v50;
  char *v51;
  char **v53;

  v2 = NewSpecific(string, 6u);
  v3 = "KYU";
  v4 = v2;
  v2[0] = "KYU";
  v53 = &v2[0];
  v5 = "MUK";
  v4[5] = "MUK";
  v6 = "WEK";
  v4[6] = "WEK";
  v7 = "NOK";
  v4[7] = "NOK";
  v8 = "BOF";
  v4[8] = "BOF";
  v9 = "HOF";
  v4[9] = "HOF";
  paracsr = sbtldbwk->paracsr;
  Unit = sbattleGetUnit(sbtldbwk->mdlslcsr->point);
  devilid = Unit->para->devilid;
  DevilData = sBtlGetDevilData(devilid, -1);
  sBtlDebug_DrawNormalList_Col(sblist_paramenu, 17, paracsr->point, -1, 18, 234);
  sbattleDrawInt_Num(96, 232, Unit->para->level, paracsr->point, 0);
  sbattleDrawInt_Num(96, 244, Unit->para->now->hp, paracsr->point, 1);
  sbattleDrawInt_Num(96, 256, Unit->para->now->maxhp, paracsr->point, 2);
  sbattleDrawInt_Num(96, 268, Unit->para->now->mp, paracsr->point, 3);
  sbattleDrawInt_Num(96, 280, Unit->para->now->maxmp, paracsr->point, 4);
  sbattleDrawInt_Num(96, 292, Unit->para->now->str, paracsr->point, 5);
  sbattleDrawInt_Num(96, 304, Unit->para->now->vit, paracsr->point, 6);
  sbattleDrawInt_Num(96, 316, Unit->para->now->tec, paracsr->point, 7);
  sbattleDrawInt_Num(96, 328, Unit->para->now->luck, paracsr->point, 8);
  sbattleDrawInt_Num(96, 340, Unit->para->vice, paracsr->point, 9);
  sbattleDrawInt_Num(96, 364, wk->mag, paracsr->point, 11);
  sbattleDrawInt_Num(96, 376, wk->magMax, paracsr->point, 12);
  sbattleDrawInt_Num(96, 388, wk->sprit_waza, paracsr->point, 13);
  getchuusei = DevilData->getchuusei;
  getmoney = DevilData->getmoney;
  sbattleDrawInt_Num(96, 400, DevilData->getexp, paracsr->point, 14);
  sbattleDrawInt_Num(96, 412, getmoney, paracsr->point, 15);
  sbattleDrawFloat_Num(96, 424, getchuusei, paracsr->point, 16);
  para_bstno = sbtldbwk->para_bstno;
  if (para_bstno == 22)
    goto LABEL_18;
  if (paracsr->point != 10)
  {
    v40 = -1600273536;
    goto LABEL_17;
  }
  para_bstno = sbtldbwk->para_bstno;
  v40 = 1692838528;
LABEL_17:
  sBtlDrawBSTName(96, 352, 0, v40, para_bstno);
LABEL_18:
  v42 = 0;
  v43 = 234;
  do
  {
    sBtlDrawAisyoName(162, v43, 0, 0xA09DC380, v42);
    v45 = Unit->para->aisyo->para[v42];
    if ((v45 & 0x2000) != 0)
    {
      v46 = *v53;
      sbattleDrawString(224, v43, v46, v42, -1);
      if ((v45 & 0x1000) == 0)
      {
LABEL_29:
        if ((v45 & 0x4000) == 0)
          goto LABEL_30;
        goto LABEL_40;
      }
    }
    else if ((v45 & 0x1000) == 0)
    {
      goto LABEL_29;
    }
    v47 = v4[5];
    sbattleDrawString(260, v43, v47, v42, -1);
    if ((v45 & 0x4000) == 0)
    {
LABEL_30:
      if ((v45 & 0x8000) == 0)
        goto LABEL_31;
      goto LABEL_43;
    }
LABEL_40:
    v48 = v4[6];
    sbattleDrawString(296, v43, v48, v42, -1);
    if ((v45 & 0x8000) == 0)
    {
LABEL_31:
      if ((v45 & 0x20000) == 0)
        goto LABEL_32;
      goto LABEL_46;
    }
LABEL_43:
    v49 = v4[7];
    sbattleDrawString(332, v43, v49, v42, -1);
    if ((v45 & 0x20000) == 0)
    {
LABEL_32:
      if ((v45 & 0x40000) == 0)
        goto LABEL_22;
LABEL_49:
      v51 = v4[9];
      sbattleDrawString(404, v43, v51, v42, -1);
      goto LABEL_22;
    }
LABEL_46:
    v50 = v4[8];
    sbattleDrawString(368, v43, v50, v42, -1);
    if ((v45 & 0x40000) != 0)
      goto LABEL_49;
LABEL_22:
    sbattleDrawInt_Num(440, v43, v45 & 0xFFF, v42++, -1);
    v43 += 18;
  }
  while (v42 != 11);
  return 1;
}

// 0x1917f20
bool sbattleAIProc(dds3ProcessID_t *id) {
  return 0;
}

// 0x1917f30
bool sbattleAIDraw(dds3ProcessID_t *id) {
  return 0;
}

// 0x1917f40
bool sbattleCameraEditorDraw(dds3ProcessID_t *id) {
  return 1;
}

// 0x1917f50
bool sbattleWeaponSetDraw(dds3ProcessID_t *id) {
  return 1;
}

// 0x1917f60
bool sbattleTimeLimitEditorDraw(dds3ProcessID_t *id) {
  return 1;
}

// 0x1917f70
void sbattleSaveFollowUpCameraParAsset(void) {
  ;
}

// 0x1917f80
bool sbattleCameraEditorProc(dds3ProcessID_t *id) {
  return 1;
}

// 0x1917f90
bool sbattleWeaponSetProc(dds3ProcessID_t *id) {
  return 1;
}

// 0x1917fa0
bool sbattleTimeLimitEditorProc(dds3ProcessID_t *id) {
  return 1;
}

// 0x1917fb0
bool sbattleNEFMODE_Func_Open(void) {
  SBDEBUG_CSRWORK *nef_modecsr;
  s32 MotionNum;
  u32 v8;
  SBTLDEBUG_WORK *v9;
  s32 v13;
  s32 point;
  s32 v15;
  s32 v16;
  SBTLDEBUG_WORK *v18;
  s32 v19;
  bool v20;
  SBTLDEBUG_WORK *v22;
  s32 v23;
  s32 v24;
  SBTLDEBUG_WORK *v26;
  s32 v27;
  SBTLDEBUG_WORK *v29;
  s32 v30;
  s32 v32;
  SBTLDEBUG_WORK *v34;
  SBTLDEBUG_WORK *v35;
  s64 status;
  u32 v38;

  if ((sbtldbwk->status & 0x200000) != 0)
  {
    sbattleDeletePrevModel();
    return 1;
  }
  nef_modecsr = sbtldbwk->nef_modecsr;
  MotionNum = sbattleGetMotionNum(sbtldbwk->acterID);
  v9 = sbtldbwk;
  if (v9->ef_mode == 4)
  {
    if (!v8)
    if (sBtlDebug_ChangeModel())
    {
      sbtldbwk->ef_mode = 0;
    }
    return 1;
  }
  if (!v8)
  {
    if (sbtldbwk->prev_mode)
      goto LABEL_21;
LABEL_28:
    if (CHECK_REP2(4100))
    {
      v13 = nef_modecsr->point - 1;
      nef_modecsr->point = v13;
      if (v13 < 0)
      {
        nef_modecsr->point = nef_modecsr->maxp - 1;
        return 1;
      }
    }
    else
    {
      if (CHECK_REP2(4101))
      {
        point = nef_modecsr->point;
        if (point + 1 < nef_modecsr->maxp)
          v15 = point + 1;
        else
          v15 = 0;
        nef_modecsr->point = v15;
        return 1;
      }
      if (CHECK_REP2(4103))
      {
        v16 = nef_modecsr->point;
        if (v16 == 3)
        {
          v18 = sbtldbwk;
          v19 = v18->prev_cnt + 1;
          v20 = v18->prev_cnt - 9 < 0;
          v18->prev_cnt = v19;
          if (v20 == __OFSUB__(v19, 10))
          {
            v18 = sbtldbwk;
            v18->prev_cnt = 0;
          }
          v16 = nef_modecsr->point;
        }
        if (v16 != -1)
          return 1;
        v22 = sbtldbwk;
        v23 = v22->prev_motionno + 1;
        v22->prev_motionno = v23;
        if (v23 < MotionNum)
          return 1;
        v22 = sbtldbwk;
        v22->prev_motionno = 0;
        return 1;
      }
      if (CHECK_REP2(4102))
      {
        v24 = nef_modecsr->point;
        if (v24 == 3)
        {
          v26 = sbtldbwk;
          v27 = v26->prev_cnt - 1;
          v26->prev_cnt = v27;
          if (v27 < 0)
          {
            v26 = sbtldbwk;
            v26->prev_cnt = 9;
          }
          v24 = nef_modecsr->point;
        }
        if (v24 != -1)
          return 1;
        v29 = sbtldbwk;
        v30 = v29->prev_motionno - 1;
        v29->prev_motionno = v30;
        if (v30 >= 0)
          return 1;
        v29 = sbtldbwk;
        v29->prev_motionno = MotionNum - 1;
        return 1;
      }
      if (CHECK_TRIG2(4096))
      {
        v32 = nef_modecsr->point;
        sbattleCheckOpenMenu(v32, 0);
        return 1;
      }
      if (CHECK_REP2(4097))
      {
        if (nef_modecsr->point != 3)
          goto LABEL_87;
        v34 = sbtldbwk;
        if (v34->acterID == -1)
        {
LABEL_87:
          v35 = sbtldbwk;
          status = v35->status;
          v35->mode = 10;
          v35->status = status & 0xFFFFFFFFFFFFF7FFLL;
          if (!v38)
          RestartBattle();
          return 1;
        }
        else
        {
          v34 = sbtldbwk;
          v34->status |= 0x200000u;
          return 1;
        }
      }
    }
    return 1;
  }
  if (!v9->prev_mode)
    goto LABEL_28;
LABEL_21:
  if (!sbattleSetPreViewModel())
    return 1;
  sbtldbwk->prev_mode = 0;
  return 1;
}

// 0x1919d20
bool sbattleNEFMODE_Func_Save(void) {
  SBDEBUG_CSRWORK *nef_savecsr;
  s32 v3;
  s32 point;
  s32 v6;

  nef_savecsr = sbtldbwk->nef_savecsr;
  if (CHECK_REP2(4100))
  {
    v3 = nef_savecsr->point - 1;
    nef_savecsr->point = v3;
    if (v3 >= 0)
      return 1;
    nef_savecsr->point = nef_savecsr->maxp - 1;
    return 1;
  }
  else if (CHECK_REP2(4101))
  {
    point = nef_savecsr->point;
    if (point + 1 < nef_savecsr->maxp)
      v6 = point + 1;
    else
      v6 = 0;
    nef_savecsr->point = v6;
    return 1;
  }
  else
  {
    if (!CHECK_REP2(4097))
      return 1;
    sbtldbwk->nef_mode = sbtldbwk->nef_modebk;
    return 1;
  }
}

// 0x1919e40
bool sbattleNEFMODE_Func_Load(void) {
  SBDEBUG_CSRWORK *nef_loadcsr;
  s32 v3;
  s32 point;
  s32 v6;
  s32 maxp;
  s32 v8;
  SBDEBUG_FILEWORK *wk;
  s32 v12;

  nef_loadcsr = sbtldbwk->nef_loadcsr;
  if (CHECK_REP2(4100))
  {
    v3 = nef_loadcsr->point - 1;
    nef_loadcsr->point = v3;
    if (v3 >= 0)
      return 1;
    maxp = nef_loadcsr->maxp;
    goto LABEL_16;
  }
  if (CHECK_REP2(4101))
  {
    point = nef_loadcsr->point;
    if (point + 1 < nef_loadcsr->maxp)
      v6 = point + 1;
    else
      v6 = 0;
    nef_loadcsr->point = v6;
    return 1;
  }
  if (CHECK_REP2(4105))
  {
    nef_loadcsr->point = (nef_loadcsr->point - 10) & ~((nef_loadcsr->point - 10) >> 31);
    return 1;
  }
  if (CHECK_REP2(4108))
  {
    v8 = nef_loadcsr->point + 10;
    maxp = nef_loadcsr->maxp;
    nef_loadcsr->point = v8;
    if (v8 < maxp)
      return 1;
LABEL_16:
    nef_loadcsr->point = maxp - 1;
    return 1;
  }
  if (CHECK_TRIG2(4096))
  {
    wk = sbtldbwk->fileList->wk;
    if (!wk)
      goto LABEL_52;
    v12 = nef_loadcsr->point + 1;
    while (--v12)
    {
      wk = wk->next;
      if (!wk)
        goto LABEL_52;
    }
    sbattleClearEffHitData(0);
    sbattleClearEffHitData(1);
    sbattleClearEffHitData(2);
    sbattleClearEffHitData(3);
    sbattleClearEffHitData(4);
    sbattleClearEffHitData(5);
    sbattleClearEffHitData(6);
    sbattleClearEffHitData(7);
    sbattleClearEffHitData(8);
    sbattleClearEffHitData(9);
    sbattleClearEffHitData(10);
    sbattleClearEffHitData(11);
    sbattleClearEffHitData(12);
    sbattleClearEffHitData(13);
    sbattleClearEffHitData(14);
    sbattleClearEffHitData(15);
LABEL_52:
    sbattleDeleteFileList(sbtldbwk->fileList);
    return 1;
  }
  if (!CHECK_REP2(4097))
    return 1;
  sbtldbwk->nef_mode = sbtldbwk->nef_modebk;
  sbattleDeleteFileList(sbtldbwk->fileList);
  return 1;
}

// 0x191a650
bool sbattleNEFMODE_Func_PageList(void) {
  SBTLSKILLP_TBL *v1;
  SBDEBUG_CSRWORK *nef_pagecsr;
  SBTLSKILLHIT_TBL *wk_local;
  u32 v7;
  SBATTLE_WORK *v11;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 playerID;
  SBTLDEBUG_WORK *v15;
  SBTLDEBUG_WORK *v17;
  s32 v18;
  SBTLUNIT_LISTWORK *v19;
  s32 acterID;
  SBTLUNIT_WORK *v23;
  SBTLSKILLP_TBL *Skilltbl;
  SBTLSKILLP_TBL *v25;
  s64 v27;
  char i;
  SBTLDEBUG_WORK *v29;
  SBTLEFF_EFFTIME *v30;
  SBTLSKLHIT_PACDATAWORK *v31;
  SBTLEFF_EFFTIME *v32;
  SBTLDEBUG_WORK *v33;
  SBTLSKLHIT_PACDATAWORK *v34;
  plistHandle_t_Resource *pData;
  SBTLDEBUG_WORK *v36;
  SBTLSKLHIT_PACDATAWORK *v37;
  plistHandle_t *hPartsList;
  SBTLSKILLHIT_POSWORK *start;
  void *v40;
  SBTLSKILLHIT_POSWORK *end;
  void *v42;
  s32 ListID;
  s32 acterside;
  SBTLDMG_HITLISTWORK *hitList;
  SBTLSKLHIT_PACDATAWORK *v47;
  SBTLSKILLHIT_TBL *v48;
  SBTLSKILLHIT_TBL *v49;
  SBTLSKILLHIT_POSWORK *v50;
  u32 iti;
  SBTLSKILLHIT_POSWORK *v52;
  u32 v53;
  s32 point;
  s32 v55;
  SBDEBUG_CSRWORK *v56;
  s32 v58;
  s32 maxp;
  SBDEBUG_CSRWORK *v61;
  s32 v63;
  s32 v64;
  SBDEBUG_CSRWORK *v66;
  SBDEBUG_CSRWORK *v68;
  SBDEBUG_CSRWORK *v70;
  SBDEBUG_CSRWORK *v72;
  s32 v74;
  s32 v75;
  s32 v81;
  s32 v82;
  SBTLDEBUG_WORK *v83;
  s32 nef_nowpage;
  SBDEBUG_CSRWORK *nef_htypecsr;
  SBTLDEBUG_WORK *v88;
  s32 v89;
  bool v90;
  SBTLDEBUG_WORK *v93;
  s32 v94;
  SBTLSKILLP_TBL *v95;

  v1 = Allocate(SBTLSKILLP_TBL);
  _ctor(v1, 0);
  if ((sbtldbwk->status & 0x200000) != 0)
  {
    sbattleDeletePrevModel();
    return 1;
  }
  nef_pagecsr = sbtldbwk->nef_pagecsr;
  wk_local = sbtldbwk->ef_wk[nef_pagecsr->point]->wk;
  if (sbtldbwk->ef_mode == 4)
  {
    if (!v7)
    if (sBtlDebug_ChangeModel())
    {
      sbtldbwk->ef_mode = 0;
    }
    return 1;
  }
  if (v7)
  {
    if (sbtldbwk->pagemode)
      goto LABEL_21;
LABEL_33:
    if (CHECK_TRIG2(4098))
    {
      v17 = sbtldbwk;
      if (!v17->pagemode)
      {
        v17 = sbtldbwk;
        v17->pagemode = 1;
      }
      return 1;
    }
    if (CHECK_REP2(4100))
    {
      v18 = nef_pagecsr->point - 1;
      nef_pagecsr->point = v18;
      if (v18 < 0)
        nef_pagecsr->point = nef_pagecsr->maxp + 4;
      return 1;
    }
    if (CHECK_REP2(4101))
    {
      point = nef_pagecsr->point;
      if (point + 1 < nef_pagecsr->maxp + 5)
        v55 = point + 1;
      else
        v55 = 0;
      nef_pagecsr->point = v55;
      return 1;
    }
    if (CHECK_REP2(4108) && CHECK_PRESS2(4103) || CHECK_PRESS2(4108) && CHECK_REP2(4103))
    {
      v58 = nef_pagecsr->point;
      maxp = nef_pagecsr->maxp;
      if (v58 < maxp)
      {
        if (sbtldbwk->nef_nowpage > 15 || nef_pagecsr->point != nef_pagecsr->maxp - 1)
        {
          sbattleSetEffHitPara_S(wk_local, v56, 4);
        }
        return 1;
      }
      goto LABEL_170;
    }
    if (CHECK_REP2(4105) && CHECK_PRESS2(4102) || CHECK_PRESS2(4105) && CHECK_REP2(4102))
    {
      v63 = nef_pagecsr->point;
      v64 = nef_pagecsr->maxp;
      if (v63 < v64)
      {
        if (sbtldbwk->nef_nowpage > 15 || nef_pagecsr->point != nef_pagecsr->maxp - 1)
        {
          sbattleSetEffHitPara_S(wk_local, v61, 5);
        }
        return 1;
      }
      goto LABEL_185;
    }
    if (CHECK_REP2(4103) && !CHECK_REP2(4108))
    {
      v58 = nef_pagecsr->point;
      maxp = nef_pagecsr->maxp;
      if (v58 < maxp)
      {
        if (sbtldbwk->nef_nowpage > 15 || nef_pagecsr->point != nef_pagecsr->maxp - 1)
        {
          sbattleSetEffHitPara_S(wk_local, v66, 0);
        }
        return 1;
      }
    }
    else
    {
      if (CHECK_REP2(4102) && !CHECK_REP2(4105))
      {
        v63 = nef_pagecsr->point;
        v64 = nef_pagecsr->maxp;
        if (v63 < v64)
        {
          if (sbtldbwk->nef_nowpage > 15 || nef_pagecsr->point != nef_pagecsr->maxp - 1)
          {
            sbattleSetEffHitPara_S(wk_local, v68, 1);
          }
          return 1;
        }
LABEL_185:
        if (v63 == v64 + 3)
        {
          v93 = sbtldbwk;
          v94 = v93->prev_cnt - 1;
          v93->prev_cnt = v94;
          if (v94 < 0)
          {
            v93 = sbtldbwk;
            v93->prev_cnt = 9;
          }
        }
        return 1;
      }
      if (!CHECK_REP2(4108) || CHECK_REP2(4103))
      {
        if (!CHECK_REP2(4105) || CHECK_REP2(4102))
        {
          if (CHECK_TRIG2(4097))
          {
            v74 = nef_pagecsr->point;
            v75 = nef_pagecsr->maxp;
            if (v74 >= v75 && v74 == v75 + 3)
            {
              sbtldbwk->status |= 0x200000u;
            }
            return 1;
          }
          if (!CHECK_TRIG2(4096))
            return 1;
          v81 = nef_pagecsr->point;
          v82 = nef_pagecsr->maxp;
          v83 = sbtldbwk;
          nef_nowpage = v83->nef_nowpage;
          if (nef_nowpage <= 15 && v81 == v82 - 1)
          {
            v83 = sbtldbwk;
            v83->nef_mode = 4;
            nef_htypecsr = v83->nef_htypecsr;
          }
          else
          {
            if (v81 >= v82)
            {
              nef_nowpage = sbtldbwk->nef_nowpage;
              sbattleCheckOpenMenu(v81 + ~nef_nowpage, 1);
              return 1;
            }
            v83 = sbtldbwk;
            v83->nef_mode = 5;
            nef_htypecsr = v83->nef_selmenucsr;
          }
          nef_htypecsr->point = 0;
          nef_htypecsr->maxp = 3;
          return 1;
        }
        v63 = nef_pagecsr->point;
        v64 = nef_pagecsr->maxp;
        if (v63 < v64)
        {
          if (sbtldbwk->nef_nowpage > 15 || nef_pagecsr->point != nef_pagecsr->maxp - 1)
          {
            sbattleSetEffHitPara_S(wk_local, v72, 3);
          }
          return 1;
        }
        goto LABEL_185;
      }
      v58 = nef_pagecsr->point;
      maxp = nef_pagecsr->maxp;
      if (v58 < maxp)
      {
        if (sbtldbwk->nef_nowpage > 15 || nef_pagecsr->point != nef_pagecsr->maxp - 1)
        {
          sbattleSetEffHitPara_S(wk_local, v70, 2);
        }
        return 1;
      }
    }
LABEL_170:
    if (v58 == maxp + 3)
    {
      v88 = sbtldbwk;
      v89 = v88->prev_cnt + 1;
      v90 = v88->prev_cnt - 9 < 0;
      v88->prev_cnt = v89;
      if (v90 == __OFSUB__(v89, 10))
      {
        v88 = sbtldbwk;
        v88->prev_cnt = 0;
      }
    }
    return 1;
  }
  if (!sbtldbwk->pagemode)
    goto LABEL_33;
LABEL_21:
  v11 = wk;
  UnitMng = v11->UnitMng;
  playerID = v11->playerID;
  sBtlSearchUnit_ID(UnitMng, playerID);
  v15 = sbtldbwk;
  switch (v15->pagemode)
  {
    case 1:
      if (sbattleSetPreViewModel())
        goto LABEL_88;
      return 1;
    case 2:
      if (sBtlForceDelete_EffectWork_ID(288, 1))
        goto LABEL_88;
      return 1;
    case 3:
      if (sBtlLoadEffectData_ID(288))
        goto LABEL_88;
      return 1;
    case 4:
      v19 = wk->UnitMng;
      acterID = sbtldbwk->acterID;
      v23 = sBtlSearchUnit_ID(v19, acterID);
      Skilltbl = sBtlGetSkilltbl(288);
      v25 = Allocate(SBTLSKILLP_TBL);
      _ctor_31315008(v25, Skilltbl, 0);
      v95 = v25;
      *(u32 *)&v25->type = -2147352575;
      v27 = 0;
      for (i = 0; ; i = 1)
      {
        v29 = sbtldbwk;
        if (v27 >= v29->nef_nowpage)
          break;
        v29 = sbtldbwk;
        if (v29->ef_dwk[v27]->pData)
        {
          v29 = sbtldbwk;
          v30 = v29->ef_dtime[v27];
          v31 = v29->ef_wk[v27];
          v32 = Allocate(SBTLEFF_EFFTIME);
          _ctor_32244272(v32, v30, 0);
          v31->time = v32;
          v33 = sbtldbwk;
          v34 = v33->ef_wk[v27];
          pData = v33->ef_dwk[v27]->pData;
          v34->EpData = pData;
          v36 = sbtldbwk;
          v37 = v36->ef_wk[v27];
          hPartsList = v36->ef_dwk[v27]->hPartsList;
          v37->hPartsList = hPartsList;
        }
        start = sbtldbwk->ef_wk[v27]->wk->start;
        v40 = NewSpecific(byte, 0x12u);
        InitializeArray_55364416(v40, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__E2170EDFF82D1B234EAC7F7E28AF54B98E969BFA23206AF39C3328FB55FAE35F, 0);
        start->iti = *((u8 *)&v40[2].klass + start->iti);
        end = sbtldbwk->ef_wk[v27]->wk->end;
        v42 = NewSpecific(byte, 0x12u);
        InitializeArray_55364416(v42, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__E2170EDFF82D1B234EAC7F7E28AF54B98E969BFA23206AF39C3328FB55FAE35F, 0);
        end->iti = *((u8 *)&v42[2].klass + end->iti);
        ListID = v23->ListID;
        acterside = v23->side;
        hitList = wk->hitList;
        v47 = sbtldbwk->ef_wk[v27];
        v48 = v47->wk;
        sBtlCreateHitC_New(hitList, v23, 0, ListID, 288, v95, v48, v47, acterside, -1);
        v49 = sbtldbwk->ef_wk[v27]->wk;
        v50 = v49->start;
        iti = v50->iti;
        if (iti >= 9 && iti - 128 <= 8)
          v50->iti = iti - 119;
        v52 = v49->end;
        v53 = v52->iti;
        if (v53 >= 9 && v53 - 128 <= 8)
          v52->iti = v53 - 119;
        ++v27;
      }
      if ((i & 1) != 0)
      {
        sBtlAddSerialID2();
LABEL_88:
      }
      ++sbtldbwk->pagemode;
      break;
    case 5:
      v15 = sbtldbwk;
      v15->pagemode = 0;
      return 1;
    default:
      return 1;
  }
  return 1;
}

// 0x191b500
bool sbattleNEFMODE_Func_Hittype(void) {
  SBDEBUG_CSRWORK *nef_htypecsr;
  SBTLSKILLHIT_TBL *wk;
  s32 v5;
  s32 point;
  s32 v8;
  SBTLDEBUG_WORK *v10;
  s32 v11;
  bool v12;
  SBDEBUG_CSRWORK *nef_pagecsr;
  s32 maxp;
  s32 *p_nef_nowpage;
  SBTLDEBUG_WORK *v17;

  nef_htypecsr = sbtldbwk->nef_htypecsr;
  wk = sbtldbwk->ef_wk[sbtldbwk->nef_pagecsr->point]->wk;
  if (!CHECK_REP2(4100))
  {
    if (CHECK_REP2(4101))
    {
      point = nef_htypecsr->point;
      if (point + 1 < nef_htypecsr->maxp)
        v8 = point + 1;
      else
        v8 = 0;
      nef_htypecsr->point = v8;
      return 1;
    }
    if (CHECK_TRIG2(4096))
    {
      v10 = sbtldbwk;
      v11 = v10->nef_nowpage + 1;
      v12 = v10->nef_nowpage - 14 < 0;
      v10->nef_nowpage = v11;
      if (v12 ^ __OFSUB__(v11, 15) | (v11 == 15))
      {
        v10 = sbtldbwk;
        nef_pagecsr = v10->nef_pagecsr;
        maxp = nef_pagecsr->maxp;
        nef_pagecsr->point = maxp;
        nef_pagecsr->maxp = maxp + 1;
      }
      p_nef_nowpage = &sbtldbwk->nef_nowpage;
      LimitRange(p_nef_nowpage, 0, 16);
      wk->type = nef_htypecsr->point;
      v17 = sbtldbwk;
      if (v17->mode == 13)
      {
        wk->flg |= 0x801u;
        wk->start->iti = 1;
      }
      goto LABEL_35;
    }
    else
    {
      if (!CHECK_TRIG2(4097))
        return 1;
    }
    v17 = sbtldbwk;
LABEL_35:
    v17->nef_mode = 3;
    return 1;
  }
  v5 = nef_htypecsr->point - 1;
  nef_htypecsr->point = v5;
  if (v5 >= 0)
    return 1;
  nef_htypecsr->point = nef_htypecsr->maxp - 1;
  return 1;
}

// 0x191b760
bool sbattleNEFMODE_Func_SelMenu(void) {
  SBDEBUG_CSRWORK *nef_selmenucsr;
  SBTLSKILLHIT_TBL *wk;
  s32 v5;
  s32 point;
  s32 v8;
  s32 v9;
  SBTLDEBUG_WORK *v11;
  SBDEBUG_CSRWORK *effhitcsr;
  u32 type;
  SBTLDEBUG_WORK *v14;
  s32 v15;
  SBTLDEBUG_WORK *v18;
  SBDEBUG_CSRWORK *nef_delokcsr;
  SBTLDEBUG_WORK *v21;
  s32 nef_nowpage;
  s32 v23;
  SBTLDEBUG_WORK *v24;
  s32 v25;
  bool v26;

  nef_selmenucsr = sbtldbwk->nef_selmenucsr;
  wk = sbtldbwk->ef_wk[sbtldbwk->nef_pagecsr->point]->wk;
  if (!CHECK_REP2(4100))
  {
    if (CHECK_REP2(4101))
    {
      point = nef_selmenucsr->point;
      if (point + 1 < nef_selmenucsr->maxp)
        v8 = point + 1;
      else
        v8 = 0;
      nef_selmenucsr->point = v8;
      return 1;
    }
    if (!CHECK_TRIG2(4096))
    {
      if (!CHECK_TRIG2(4097))
        return 1;
      sbtldbwk->nef_mode = 3;
      return 1;
    }
    v9 = nef_selmenucsr->point;
    if (v9 == 2)
    {
      v18 = sbtldbwk;
      if (v18->nef_nowpage < 2)
        return 1;
      v18 = sbtldbwk;
      v18->nef_mode = 7;
      nef_delokcsr = v18->nef_delokcsr;
      nef_delokcsr->point = 0;
      nef_delokcsr->maxp = 2;
      return 1;
    }
    if (v9 != 1)
    {
      if (v9)
        return 1;
      v11 = sbtldbwk;
      effhitcsr = v11->effhitcsr;
      v11->nef_mode = 9;
      effhitcsr->point = 0;
      type = wk->type;
      v14 = sbtldbwk;
      if (v14->mode == 12)
      {
        switch (type)
        {
          case 2u:
            if ((wk->flg & 0x100) != 0)
              v15 = 26;
            else
              v15 = 19;
            goto LABEL_63;
          case 1u:
            if ((wk->flg & 0x100) != 0)
              v15 = 25;
            else
              v15 = 18;
            goto LABEL_63;
          case 0u:
            if ((wk->flg & 0x100) != 0)
              v15 = 24;
            else
              v15 = 17;
            goto LABEL_63;
        }
        goto LABEL_50;
      }
      if (type <= 2)
      {
        v15 = dword_3E608C4[type];
LABEL_63:
        effhitcsr->maxp = v15;
        v14->ef_wkflg[v14->nef_pagecsr->point] = 1;
        wk->rad_area = 0.0;
        return 1;
      }
LABEL_50:
      v15 = 0;
      goto LABEL_63;
    }
    v21 = sbtldbwk;
    nef_nowpage = v21->nef_nowpage;
    if (nef_nowpage > 15)
      return 1;
    v23 = nef_nowpage + 1;
    v21->nef_nowpage = v23;
    if (v23 > 15)
      goto LABEL_44;
    goto LABEL_9001;
    if (!(v26 ^ __OFSUB__(v25, 15) | (v25 == 15)))
    {
LABEL_44:
LABEL_45:
      v24 = sbtldbwk;
      ClassCopy(v24->ef_wk[v24->nef_nowpage - 1], v24->ef_wk[v24->nef_pagecsr->point], 0);
      sbtldbwk->ef_wkflg[sbtldbwk->nef_nowpage
                                                                                - 1] = sbtldbwk->ef_wkflg[sbtldbwk->nef_pagecsr->point];
      return 1;
    }
LABEL_9001:
    v21 = sbtldbwk;
    ++v21->nef_pagecsr->maxp;
    goto LABEL_45;
  }
  v5 = nef_selmenucsr->point - 1;
  nef_selmenucsr->point = v5;
  if (v5 >= 0)
    return 1;
  nef_selmenucsr->point = nef_selmenucsr->maxp - 1;
  return 1;
}

// 0x191bba0
bool sbattleNEFMODE_Func_Delok(void) {
  SBDEBUG_CSRWORK *nef_delokcsr;
  s32 v3;
  s32 point;
  s32 v6;
  s32 v7;
  s32 v10;
  s64 i;
  char *v13;
  SBTLDEBUG_WORK *sbtldbwk_local;
  s32 v16;
  bool v17;
  SBDEBUG_CSRWORK *nef_pagecsr;
  s32 v19;
  s32 v20;

  nef_delokcsr = sbtldbwk->nef_delokcsr;
  if (!CHECK_REP2(4100))
  {
    if (CHECK_REP2(4101))
    {
      point = nef_delokcsr->point;
      if (point + 1 < nef_delokcsr->maxp)
        v6 = point + 1;
      else
        v6 = 0;
      nef_delokcsr->point = v6;
      return 1;
    }
    if (!CHECK_TRIG2(4096))
    {
      if (!CHECK_TRIG2(4097))
        return 1;
      goto LABEL_19;
    }
    v7 = nef_delokcsr->point;
    if (v7 != 1)
    {
      if (v7)
        return 1;
LABEL_19:
      v10 = 5;
LABEL_47:
      sbtldbwk->nef_mode = v10;
      return 1;
    }
    for (i = sbtldbwk->nef_pagecsr->point; ; ++i)
    {
      sbtldbwk_local = sbtldbwk;
      if (i >= sbtldbwk_local->nef_pagecsr->maxp)
        break;
      sbtldbwk_local = sbtldbwk;
      ClassCopy(sbtldbwk_local->ef_wk[i], sbtldbwk_local->ef_wk[i + 1], 0);
      v13 = (char *)sbtldbwk->ef_wkflg + i;
      v13[32] = v13[33];
    }
    sbtldbwk_local = sbtldbwk;
    v16 = sbtldbwk_local->nef_nowpage - 1;
    v17 = sbtldbwk_local->nef_nowpage - 2 < 0;
    sbtldbwk_local->nef_nowpage = v16;
    if (v17 != __OFSUB__(v16, 1))
    {
LABEL_44:
      v10 = 3;
      goto LABEL_47;
    }
    if (v16 == 15)
      goto LABEL_36;
    goto LABEL_9000;
    if (sbtldbwk_local->nef_nowpage == 15)
    {
LABEL_36:
      goto LABEL_37;
    }
LABEL_9000:
    sbtldbwk_local = sbtldbwk;
    --sbtldbwk_local->nef_pagecsr->maxp;
LABEL_37:
    nef_pagecsr = sbtldbwk->nef_pagecsr;
    v19 = nef_pagecsr->point;
    if (v19 <= nef_pagecsr->maxp)
    {
      nef_pagecsr = sbtldbwk->nef_pagecsr;
      v19 = nef_pagecsr->point;
      v20 = v19 - 1;
      nef_pagecsr->point = v20;
      if (v20 < 0)
      {
        nef_pagecsr = sbtldbwk->nef_pagecsr;
        nef_pagecsr->point = 0;
      }
    }
    goto LABEL_44;
  }
  v3 = nef_delokcsr->point - 1;
  nef_delokcsr->point = v3;
  if (v3 >= 0)
    return 1;
  nef_delokcsr->point = nef_delokcsr->maxp - 1;
  return 1;
}

// 0x191bec0
bool sbattleNEFMODE_Func_Edit(void) {
  s64 point;
  SBTLSKILLHIT_TBL *wk;
  SBDEBUG_PATHDATA *v5;
  u32 type;
  u32 v7;
  u32 v8;
  u32 v9;
  s32 v10;
  u32 v11;
  SBDEBUG_CSRWORK *effhitcsr;
  s32 ef_mode;
  u32 flg;
  u32 v17;
  bool v18;
  u32 v19;
  SBDEBUG_CSRWORK *v20;
  u32 v21;
  SBTLDEBUG_WORK *v22;
  s32 v23;
  SBTLDEBUG_WORK *v25;
  s32 v26;
  s32 v29;
  s32 nef_movetype;
  SBTLDEBUG_WORK *v34;
  s32 v35;
  bool v36;
  bool v37;
  s32 v39;
  SBTLSKILLHIT_TBL *v40;
  SBDEBUG_CSRWORK *v41;
  s32 v42;
  SBTLDEBUG_WORK *v44;
  s32 v45;
  s32 v46;
  s32 lifetime;
  f32 v48;
  s32 v50;
  s32 v52;
  s32 v53;
  SBTLDEBUG_WORK *v56;
  s32 v57;
  s32 v58;
  s32 v63;
  s32 v64;
  s32 v65;

  point = sbtldbwk->nef_pagecsr->point;
  wk = sbtldbwk->ef_wk[point]->wk;
  v5 = sbtldbwk->ef_path[point];
  type = wk->type;
  if (type > 2)
  {
    v7 = 0;
    v8 = 0;
    v11 = 0;
    v9 = 0;
    v10 = 0;
    effhitcsr = sbtldbwk->effhitcsr;
    goto LABEL_13;
  }
  v7 = type + 23;
  v8 = type + 17;
  v9 = type + 22;
  v10 = dword_3E608B8[wk->type];
  if (v5->nef_movetype == 1)
    v11 = type + 23;
  else
    v11 = 0;
  effhitcsr = sbtldbwk->effhitcsr;
LABEL_13:
  ef_mode = sbtldbwk->ef_mode;
  if (ef_mode == 3)
  {
    if (CHECK_TRIG2(4097))
      goto LABEL_44;
    if (CHECK_REP2(4100))
    {
      v25 = sbtldbwk;
      v26 = v25->nef_poseture - 1;
      v25->nef_poseture = v26;
      if (v26 < 0)
      {
        v25 = sbtldbwk;
        v25->nef_poseture = 2;
      }
      return 1;
    }
    if (CHECK_REP2(4101))
    {
      v34 = sbtldbwk;
      v35 = v34->nef_poseture + 1;
      v36 = v34->nef_poseture - 2 < 0;
      v34->nef_poseture = v35;
      if (v36 == __OFSUB__(v35, 3))
      {
        v34 = sbtldbwk;
        v34->nef_poseture = 0;
      }
      return 1;
    }
    if (CHECK_REP2(4108) && CHECK_PRESS2(4103) || CHECK_PRESS2(4108) && CHECK_REP2(4103))
    {
      sbattleSetEffHitPara(wk, effhitcsr, 4);
      v5->nef_pathtime = 1.0;
      lifetime = wk->lifetime;
      if (!lifetime)
        goto LABEL_115;
    }
    else if (CHECK_REP2(4105) && CHECK_PRESS2(4102) || CHECK_PRESS2(4105) && CHECK_REP2(4102))
    {
      sbattleSetEffHitPara(wk, effhitcsr, 5);
      v5->nef_pathtime = 1.0;
      lifetime = wk->lifetime;
      if (!lifetime)
        goto LABEL_115;
    }
    else if (CHECK_REP2(4103) && !CHECK_REP2(4108))
    {
      sbattleSetEffHitPara(wk, effhitcsr, 0);
      v5->nef_pathtime = 1.0;
      lifetime = wk->lifetime;
      if (!lifetime)
        goto LABEL_115;
    }
    else if (CHECK_REP2(4102) && !CHECK_REP2(4105))
    {
      sbattleSetEffHitPara(wk, effhitcsr, 1);
      v5->nef_pathtime = 1.0;
      lifetime = wk->lifetime;
      if (!lifetime)
        goto LABEL_115;
    }
    else if (CHECK_REP2(4108) && !CHECK_REP2(4103))
    {
      sbattleSetEffHitPara(wk, effhitcsr, 2);
      v5->nef_pathtime = 1.0;
      lifetime = wk->lifetime;
      if (!lifetime)
        goto LABEL_115;
    }
    else
    {
      if (!CHECK_REP2(4105) || CHECK_REP2(4102))
        return 1;
      sbattleSetEffHitPara(wk, effhitcsr, 3);
      v5->nef_pathtime = 1.0;
      lifetime = wk->lifetime;
      if (!lifetime)
        goto LABEL_115;
    }
    goto LABEL_228;
  }
  if (ef_mode == 2)
  {
    if (CHECK_TRIG2(4097))
      goto LABEL_44;
    if (CHECK_REP2(4100))
    {
      nef_movetype = v5->nef_movetype - 1;
      if (nef_movetype < 0)
        nef_movetype = 1;
    }
    else
    {
      v37 = CHECK_REP2(4101);
      nef_movetype = v5->nef_movetype;
      if (!v37)
        goto LABEL_82;
      if (nef_movetype + 1 < 2)
        ++nef_movetype;
      else
        nef_movetype = 0;
    }
    v5->nef_movetype = nef_movetype;
LABEL_82:
    if (!nef_movetype)
      wk->flg &= ~0x1000u;
    return 1;
  }
  if (ef_mode != 1)
  {
    if (CHECK_REP2(4100) && !CHECK_REP2(4108) && !CHECK_REP2(4105))
    {
      v46 = effhitcsr->point - 1;
      effhitcsr->point = v46;
      if (v46 < 0)
      {
        effhitcsr->point = effhitcsr->maxp - 1;
        goto LABEL_227;
      }
LABEL_113:
      goto LABEL_227;
    }
    if (CHECK_REP2(4101) && !CHECK_REP2(4108) && !CHECK_REP2(4105))
    {
      v50 = effhitcsr->point;
      if (v50 + 1 < effhitcsr->maxp)
        v52 = v50 + 1;
      else
        v52 = 0;
      effhitcsr->point = v52;
      goto LABEL_227;
    }
    if (CHECK_TRIG2(4096))
    {
      v29 = effhitcsr->point;
      if (v29 == v8 || v29 == v9 || !v29 || v29 == v10 || v29 == v11)
      {
        sbattleSetEffHitPara(wk, effhitcsr, 0);
        v5->nef_pathtime = 1.0;
        lifetime = wk->lifetime;
        if (!lifetime)
        {
LABEL_115:
          v48 = 0.0;
LABEL_229:
          v5->nef_addpathtime = v48;
          return 1;
        }
LABEL_228:
        v48 = 1.0 / (f32)lifetime;
        goto LABEL_229;
LABEL_227:
        v5->nef_pathtime = 1.0;
        lifetime = wk->lifetime;
        if (!lifetime)
          goto LABEL_115;
        goto LABEL_228;
      }
      goto LABEL_113;
    }
    if (CHECK_TRIG2(4097))
    {
      sbtldbwk->nef_mode = 5;
      return 1;
    }
    if (CHECK_REP2(4108) && CHECK_PRESS2(4103) || CHECK_PRESS2(4108) && CHECK_REP2(4103))
    {
      v39 = effhitcsr->point;
      if (v39 != v8 && v39 != v7 && v39 != v9 && v39 && v39 != v10)
      {
        v40 = wk;
        v41 = effhitcsr;
        v42 = 4;
LABEL_224:
        sbattleSetEffHitPara(v40, v41, v42);
      }
    }
    else if (CHECK_REP2(4105) && CHECK_PRESS2(4102) || CHECK_PRESS2(4105) && CHECK_REP2(4102))
    {
      v53 = effhitcsr->point;
      if (v53 != v8 && v53 != v7 && v53 != v9 && v53 && v53 != v10)
      {
        v42 = 5;
        v40 = wk;
        v41 = effhitcsr;
        goto LABEL_224;
      }
    }
    else if (CHECK_REP2(4103) && !CHECK_REP2(4108))
    {
      v63 = effhitcsr->point;
      if (v63 != v8 && v63 != v7 && v63 != v9 && v63 && v63 != v10)
      {
        v40 = wk;
        v41 = effhitcsr;
        v42 = 0;
        goto LABEL_224;
      }
    }
    else if (CHECK_REP2(4102) && !CHECK_REP2(4105))
    {
      v64 = effhitcsr->point;
      if (v64 != v8 && v64 != v7 && v64 != v9 && v64 && v64 != v10)
      {
        v40 = wk;
        v41 = effhitcsr;
        v42 = 1;
        goto LABEL_224;
      }
    }
    else if (CHECK_REP2(4108) && !CHECK_REP2(4103))
    {
      v65 = effhitcsr->point;
      if (v65 != v8 && v65 != v7 && v65 != v9 && v65 && v65 != v10)
      {
        v40 = wk;
        v41 = effhitcsr;
        v42 = 2;
        goto LABEL_224;
      }
    }
    else
    {
      if (!CHECK_REP2(4105) || CHECK_REP2(4102))
        return 1;
      v58 = effhitcsr->point;
      if (v58 != v8 && v58 != v7 && v58 != v9 && v58 && v58 != v10)
      {
        v40 = wk;
        v41 = effhitcsr;
        v42 = 3;
        goto LABEL_224;
      }
    }
    goto LABEL_227;
  }
  if (CHECK_TRIG2(4097))
  {
LABEL_44:
    sbtldbwk->ef_mode = 0;
    return 1;
  }
  if (CHECK_REP2(4103) || CHECK_REP2(4102))
  {
    flg = wk->flg;
    v17 = effhitset_flag[sbtldbwk->ef_flgp];
    v18 = (v17 & flg) == 0;
    v19 = wk->flg;
    if (v18)
    {
      v17 = effhitset_flag[sbtldbwk->ef_flgp];
      wk->flg = v17 | v19;
    }
    else
    {
      v17 = effhitset_flag[sbtldbwk->ef_flgp];
      wk->flg = v19 & ~v17;
    }
    v20 = sbtldbwk->effhitcsr;
    v21 = wk->type;
    v22 = sbtldbwk;
    if (v22->mode == 12)
    {
      switch (v21)
      {
        case 2u:
          if ((wk->flg & 0x100) != 0)
            v23 = 26;
          else
            v23 = 19;
          break;
        case 1u:
          if ((wk->flg & 0x100) != 0)
            v23 = 25;
          else
            v23 = 18;
          break;
        case 0u:
          if ((wk->flg & 0x100) != 0)
            v23 = 24;
          else
            v23 = 17;
          break;
        default:
LABEL_104:
          v23 = 0;
          break;
      }
LABEL_178:
      v20->maxp = v23;
      if ((wk->flg & 0x100) == 0)
      {
        v22 = sbtldbwk;
        v22->ef_stendp = 0;
      }
      return 1;
    }
    if (v21 <= 2)
    {
      v23 = dword_3E608C4[v21];
      goto LABEL_178;
    }
    goto LABEL_104;
  }
  if (CHECK_REP2(4100))
  {
    v44 = sbtldbwk;
    v45 = v44->ef_flgp - 1;
    v44->ef_flgp = v45;
    if (v45 < 0)
    {
      v44 = sbtldbwk;
      v44->ef_flgp = 12;
    }
  }
  else if (CHECK_REP2(4101))
  {
    v56 = sbtldbwk;
    v57 = v56->ef_flgp + 1;
    v36 = v56->ef_flgp - 12 < 0;
    v56->ef_flgp = v57;
    if (v36 == __OFSUB__(v57, 13))
    {
      v56 = sbtldbwk;
      v56->ef_flgp = 0;
    }
  }
  return 1;
}

// 0x191d660
bool sbattleNEFMODE_Func_PBLoad(void) {
  SBDEBUG_CSRWORK *nef_pbloadcsr;
  s32 v3;
  s32 point;
  s32 v6;
  s32 maxp;
  s32 v8;
  SBDEBUG_FILEWORK *wk;
  s32 v13;
  SBTLDEBUG_WORK *v16;
  SBTLSKLHIT_PACDATAWORK *v17;

  nef_pbloadcsr = sbtldbwk->nef_pbloadcsr;
  if (CHECK_REP2(4100))
  {
    v3 = nef_pbloadcsr->point - 1;
    nef_pbloadcsr->point = v3;
    if (v3 >= 0)
      return 1;
    maxp = nef_pbloadcsr->maxp;
    goto LABEL_16;
  }
  if (CHECK_REP2(4101))
  {
    point = nef_pbloadcsr->point;
    if (point + 1 < nef_pbloadcsr->maxp)
      v6 = point + 1;
    else
      v6 = 0;
    nef_pbloadcsr->point = v6;
    return 1;
  }
  else
  {
    if (CHECK_REP2(4105))
    {
      nef_pbloadcsr->point = (nef_pbloadcsr->point - 10) & ~((nef_pbloadcsr->point - 10) >> 31);
      return 1;
    }
    if (CHECK_REP2(4108))
    {
      v8 = nef_pbloadcsr->point + 10;
      maxp = nef_pbloadcsr->maxp;
      nef_pbloadcsr->point = v8;
      if (v8 < maxp)
        return 1;
LABEL_16:
      nef_pbloadcsr->point = maxp - 1;
      return 1;
    }
    if (CHECK_TRIG2(4096))
    {
      wk = sbtldbwk->fileList->wk;
      if (wk)
      {
        v13 = nef_pbloadcsr->point + 1;
        while (--v13)
        {
          wk = wk->next;
          if (!wk)
            goto LABEL_35;
        }
        v17 = sbtldbwk->ef_wk[sbtldbwk->nef_pagecsr->point];
        v17->BpData = 0;
      }
LABEL_35:
      sbattleDeleteFileList(sbtldbwk->fileList);
      return 1;
    }
    else
    {
      if (!CHECK_REP2(4097))
        return 1;
      v16 = sbtldbwk;
      v16->nef_mode = 9;
      sbattleDeleteFileList(v16->fileList);
      return 1;
    }
  }
}

// 0x191d8a0
bool sbattleNEFMODE_Func_PBLoader(void) {
  return 1;
}

// 0x191d910
bool sbattleNEFMODE_Func_EPLLoad(void) {
  SBDEBUG_CSRWORK *nef_eplloadcsr;
  s32 v3;
  s32 point;
  s32 v6;
  s32 maxp;
  s32 v8;

  nef_eplloadcsr = sbtldbwk->nef_eplloadcsr;
  if (CHECK_REP2(4100))
  {
    v3 = nef_eplloadcsr->point - 1;
    nef_eplloadcsr->point = v3;
    if (v3 >= 0)
      return 1;
    maxp = nef_eplloadcsr->maxp;
    goto LABEL_16;
  }
  if (CHECK_REP2(4101))
  {
    point = nef_eplloadcsr->point;
    if (point + 1 < nef_eplloadcsr->maxp)
      v6 = point + 1;
    else
      v6 = 0;
    nef_eplloadcsr->point = v6;
    return 1;
  }
  else
  {
    if (CHECK_REP2(4105))
    {
      nef_eplloadcsr->point = (nef_eplloadcsr->point - 10) & ~((nef_eplloadcsr->point - 10) >> 31);
      return 1;
    }
    if (CHECK_REP2(4108))
    {
      v8 = nef_eplloadcsr->point + 10;
      maxp = nef_eplloadcsr->maxp;
      nef_eplloadcsr->point = v8;
      if (v8 < maxp)
        return 1;
LABEL_16:
      nef_eplloadcsr->point = maxp - 1;
      return 1;
    }
    if (CHECK_TRIG2(4096))
    {
      sbattleDeleteFileList(sbtldbwk->fileList);
      return 1;
    }
    else
    {
      if (!CHECK_REP2(4097))
        return 1;
      sbtldbwk->nef_mode = 14;
      sbattleDeleteFileList(sbtldbwk->fileList);
      return 1;
    }
  }
}

// 0x191daf0
bool sbattleNEFMODE_Func_EPLLoader(void) {
  return 1;
}

// 0x191db60
bool sbattleNEFMODE_Func_EPLMenu(void) {
  SBDEBUG_CSRWORK *nef_eplmenucsr;
  s32 v3;
  s32 point;
  s32 v6;
  SBDEBUG_CSRWORK *nef_epldelokcsr;
  SBTLDEBUG_WORK *v12;

  nef_eplmenucsr = sbtldbwk->nef_eplmenucsr;
  if (CHECK_REP2(4100))
  {
    v3 = nef_eplmenucsr->point - 1;
    nef_eplmenucsr->point = v3;
    if (v3 >= 0)
      return 1;
    nef_eplmenucsr->point = nef_eplmenucsr->maxp - 1;
    return 1;
  }
  else if (CHECK_REP2(4101))
  {
    point = nef_eplmenucsr->point;
    if (point + 1 < nef_eplmenucsr->maxp)
      v6 = point + 1;
    else
      v6 = 0;
    nef_eplmenucsr->point = v6;
    return 1;
  }
  else if (CHECK_REP2(4097))
  {
    sbtldbwk->nef_mode = 9;
    return 1;
  }
  else
  {
    if (!CHECK_TRIG2(4096))
      return 1;
    if (nef_eplmenucsr->point)
    {
      if (!sbtldbwk->ef_dwksize[sbtldbwk->nef_pagecsr->point])
        return 1;
      sbtldbwk->nef_mode = 15;
      nef_epldelokcsr = sbtldbwk->nef_epldelokcsr;
      nef_epldelokcsr->point = 0;
      nef_epldelokcsr->maxp = 2;
      return 1;
    }
    else
    {
      v12 = sbtldbwk;
      v12->nef_mode = 12;
      v12->nef_eplloadcsr->maxp = v12->nef_loadcsr->maxp;
      return 1;
    }
  }
}

// 0x191dd60
bool sbattleNEFMODE_Func_EPLDelok(void) {
  SBDEBUG_CSRWORK *nef_epldelokcsr;
  s32 v3;
  s32 point;
  s32 v6;

  nef_epldelokcsr = sbtldbwk->nef_epldelokcsr;
  if (CHECK_REP2(4100))
  {
    v3 = nef_epldelokcsr->point - 1;
    nef_epldelokcsr->point = v3;
    if (v3 >= 0)
      return 1;
    nef_epldelokcsr->point = nef_epldelokcsr->maxp - 1;
    return 1;
  }
  else if (CHECK_REP2(4101))
  {
    point = nef_epldelokcsr->point;
    if (point + 1 < nef_epldelokcsr->maxp)
      v6 = point + 1;
    else
      v6 = 0;
    nef_epldelokcsr->point = v6;
    return 1;
  }
  else
  {
    if (!CHECK_TRIG(4097, 1) && !CHECK_TRIG2(4096))
      return 1;
    sbtldbwk->nef_mode = 14;
    return 1;
  }
}

// 0x191deb0
bool sbattleNEFMODE_Func_Exitok(void) {
  SBDEBUG_CSRWORK *nef_exitokcsr;
  s32 v3;
  s32 point;
  s32 v6;
  s64 status;

  nef_exitokcsr = sbtldbwk->nef_exitokcsr;
  if (!CHECK_REP2(4100))
  {
    if (CHECK_REP2(4101))
    {
      point = nef_exitokcsr->point;
      if (point + 1 < nef_exitokcsr->maxp)
        v6 = point + 1;
      else
        v6 = 0;
      nef_exitokcsr->point = v6;
      return 1;
    }
    if (!CHECK_TRIG(4097, 1))
    {
      if (!CHECK_TRIG2(4096))
        return 1;
      if (nef_exitokcsr->point)
      {
        status = sbtldbwk->status;
        sbtldbwk->mode = 10;
        sbtldbwk->nef_mode = 0;
        sbtldbwk->status = status & 0xFFFFFFFFFFFFF7FFLL;
        RestartBattle();
        return 1;
      }
    }
    sbtldbwk->nef_mode = sbtldbwk->nef_modebk;
    return 1;
  }
  v3 = nef_exitokcsr->point - 1;
  nef_exitokcsr->point = v3;
  if (v3 >= 0)
    return 1;
  nef_exitokcsr->point = nef_exitokcsr->maxp - 1;
  return 1;
}

// 0x191e060
bool sbattleMDLMODE_Func_Open(void) {
  SBDEBUG_CSRWORK *nef_modecsr;
  s32 MotionNum;
  u32 v8;
  SBTLDEBUG_WORK *v9;
  s32 v10;
  s32 v12;
  s32 v16;
  s32 point;
  s32 v18;
  s32 v19;
  SBTLDEBUG_WORK *v21;
  s32 v22;
  bool v23;
  SBTLDEBUG_WORK *v25;
  s32 v26;
  s32 v27;
  SBTLDEBUG_WORK *v29;
  s32 v30;
  SBTLDEBUG_WORK *v32;
  s32 v33;
  s32 v35;
  SBTLDEBUG_WORK *v37;
  SBTLDEBUG_WORK *v38;
  s64 status;
  u32 v41;

  if ((sbtldbwk->status & 0x200000) != 0)
  {
    sbattleDeletePrevModel();
    return 1;
  }
  nef_modecsr = sbtldbwk->nef_modecsr;
  MotionNum = sbattleGetMotionNum(sbtldbwk->acterID);
  v9 = sbtldbwk;
  if (v9->ef_mode == 4)
  {
    if (!v8)
    v10 = sBtlDebug_ChangeModel();
    if (v10)
    {
      v12 = v10;
      sbtldbwk->ef_mode = 0;
      if (v12 == 1)
      {
        sBtlDebug_LoadMHTData(1, 0);
      }
    }
    return 1;
  }
  if (!v8)
  {
    if (sbtldbwk->prev_mode)
      goto LABEL_24;
LABEL_31:
    if (CHECK_REP2(4100))
    {
      v16 = nef_modecsr->point - 1;
      nef_modecsr->point = v16;
      if (v16 < 0)
      {
        nef_modecsr->point = nef_modecsr->maxp - 1;
        return 1;
      }
    }
    else
    {
      if (CHECK_REP2(4101))
      {
        point = nef_modecsr->point;
        if (point + 1 < nef_modecsr->maxp)
          v18 = point + 1;
        else
          v18 = 0;
        nef_modecsr->point = v18;
        return 1;
      }
      if (CHECK_REP2(4103))
      {
        v19 = nef_modecsr->point;
        if (v19 == 4)
        {
          v21 = sbtldbwk;
          v22 = v21->prev_cnt + 1;
          v23 = v21->prev_cnt - 9 < 0;
          v21->prev_cnt = v22;
          if (v23 == __OFSUB__(v22, 10))
          {
            v21 = sbtldbwk;
            v21->prev_cnt = 0;
          }
          v19 = nef_modecsr->point;
        }
        if (v19 != 3)
          return 1;
        v25 = sbtldbwk;
        v26 = v25->prev_motionno + 1;
        v25->prev_motionno = v26;
        if (v26 < MotionNum)
          return 1;
        v25 = sbtldbwk;
        v25->prev_motionno = 0;
        return 1;
      }
      if (CHECK_REP2(4102))
      {
        v27 = nef_modecsr->point;
        if (v27 == 4)
        {
          v29 = sbtldbwk;
          v30 = v29->prev_cnt - 1;
          v29->prev_cnt = v30;
          if (v30 < 0)
          {
            v29 = sbtldbwk;
            v29->prev_cnt = 9;
          }
          v27 = nef_modecsr->point;
        }
        if (v27 != 3)
          return 1;
        v32 = sbtldbwk;
        v33 = v32->prev_motionno - 1;
        v32->prev_motionno = v33;
        if (v33 >= 0)
          return 1;
        v32 = sbtldbwk;
        v32->prev_motionno = MotionNum - 1;
        return 1;
      }
      if (CHECK_TRIG2(4096))
      {
        v35 = nef_modecsr->point;
        sbattleCheckOpenMenu(v35, 0);
        return 1;
      }
      if (CHECK_REP2(4097))
      {
        if (nef_modecsr->point != 3)
          goto LABEL_90;
        v37 = sbtldbwk;
        if (v37->acterID == -1)
        {
LABEL_90:
          v38 = sbtldbwk;
          status = v38->status;
          v38->mode = 10;
          v38->status = status & 0xFFFFFFFFFFFFF7FFLL;
          if (!v41)
          RestartBattle();
          return 1;
        }
        else
        {
          v37 = sbtldbwk;
          v37->status |= 0x200000u;
          return 1;
        }
      }
    }
    return 1;
  }
  if (!v9->prev_mode)
    goto LABEL_31;
LABEL_24:
  if (!sbattleSetPreViewModel())
    return 1;
  sbtldbwk->prev_mode = 0;
  return 1;
}

// 0x191e730
bool sbattleMDLMODE_Func_Edit(void) {
  SBTLSKILLHIT_TBL *wk_local;
  u64 type;
  s32 v5;
  SBDEBUG_CSRWORK *effhitcsr;
  s32 ef_mode;
  u32 flg;
  u32 v11;
  u32 v12;
  SBDEBUG_CSRWORK *v13;
  u32 v14;
  SBTLDEBUG_WORK *v15;
  s32 v16;
  s32 v20;
  bool v21;
  SBTLDEBUG_WORK *v23;
  s32 v24;
  SBTLDEBUG_WORK *v27;
  s32 v28;
  bool v29;
  s32 v31;
  s32 v33;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 acterID;
  SBTLUNIT_WORK *v38;
  SBTLUNIT_WORK *v39;
  s32 motionno;
  SBTLDEBUG_WORK *v42;
  s32 v43;
  s32 v44;
  s32 point;
  s32 v47;
  s32 v48;
  SBTLDEBUG_WORK *v51;
  s32 v52;
  s32 v53;
  s32 v57;
  s32 v58;
  s32 v59;

  wk_local = sbtldbwk->ef_wk[sbtldbwk->nef_pagecsr->point]->wk;
  type = wk_local->type;
  if (type > 2)
  {
    v5 = 0;
    effhitcsr = sbtldbwk->effhitcsr;
    goto LABEL_10;
  }
  else
  {
    v5 = dword_3E608B8[type];
    effhitcsr = sbtldbwk->effhitcsr;
    goto LABEL_10;
  }
LABEL_10:
  ef_mode = sbtldbwk->ef_mode;
  if (ef_mode == 3)
  {
    if (CHECK_TRIG2(4097))
      goto LABEL_32;
    if (CHECK_REP2(4100))
    {
      v23 = sbtldbwk;
      v24 = v23->nef_poseture - 1;
      v23->nef_poseture = v24;
      if (v24 >= 0)
        return 1;
      v23 = sbtldbwk;
      v23->nef_poseture = 2;
      return 1;
    }
    if (CHECK_REP2(4101))
    {
      v27 = sbtldbwk;
      v28 = v27->nef_poseture + 1;
      v29 = v27->nef_poseture - 2 < 0;
      v27->nef_poseture = v28;
      if (v29 != __OFSUB__(v28, 3))
        return 1;
      v27 = sbtldbwk;
      v27->nef_poseture = 0;
      return 1;
    }
    if (CHECK_REP2(4108) && CHECK_PRESS2(4103) || CHECK_PRESS2(4108) && CHECK_REP2(4103))
    {
      sbattleSetMDLHitPara(wk_local, effhitcsr, 4);
      return 1;
    }
    if (CHECK_REP2(4105) && CHECK_PRESS2(4102) || CHECK_PRESS2(4105) && CHECK_REP2(4102))
    {
      sbattleSetMDLHitPara(wk_local, effhitcsr, 5);
      return 1;
    }
    if (!CHECK_REP2(4103) || CHECK_REP2(4108))
    {
      if (CHECK_REP2(4102) && !CHECK_REP2(4105))
      {
        sbattleSetMDLHitPara(wk_local, effhitcsr, 1);
        return 1;
      }
      else if (CHECK_REP2(4108) && !CHECK_REP2(4103))
      {
        sbattleSetMDLHitPara(wk_local, effhitcsr, 2);
        return 1;
      }
      else
      {
        if (!CHECK_REP2(4105) || CHECK_REP2(4102))
          return 1;
        sbattleSetMDLHitPara(wk_local, effhitcsr, 3);
        return 1;
      }
    }
LABEL_48:
    sbattleSetMDLHitPara(wk_local, effhitcsr, 0);
    return 1;
  }
  if (ef_mode != 1)
  {
    if (CHECK_REP2(4100) && !CHECK_REP2(4108) && !CHECK_REP2(4105))
    {
      v44 = effhitcsr->point - 1;
      effhitcsr->point = v44;
      if (v44 < 0)
      {
        effhitcsr->point = effhitcsr->maxp - 1;
        return 1;
      }
      return 1;
    }
    if (CHECK_REP2(4101) && !CHECK_REP2(4108) && !CHECK_REP2(4105))
    {
      point = effhitcsr->point;
      if (point + 1 < effhitcsr->maxp)
        v47 = point + 1;
      else
        v47 = 0;
      effhitcsr->point = v47;
      return 1;
    }
    if (CHECK_TRIG2(4096))
    {
      v20 = effhitcsr->point;
      if (v20)
        v21 = v20 == v5;
      else
        v21 = 1;
      if (!v21)
        return 1;
      goto LABEL_48;
    }
    if (CHECK_TRIG2(4097))
    {
      sbtldbwk->nef_mode = 5;
      return 1;
    }
    if (CHECK_REP2(4108) && CHECK_PRESS2(4103) || CHECK_PRESS2(4108) && CHECK_REP2(4103))
    {
      v31 = effhitcsr->point;
      if (!v31 || v31 == v5)
        return 1;
      v33 = 4;
      goto LABEL_77;
    }
    else if (CHECK_REP2(4105) && CHECK_PRESS2(4102) || CHECK_PRESS2(4105) && CHECK_REP2(4102))
    {
      v48 = effhitcsr->point;
      if (!v48 || v48 == v5)
        return 1;
      v33 = 5;
      goto LABEL_77;
    }
    else if (CHECK_REP2(4103) && !CHECK_REP2(4108))
    {
      v57 = effhitcsr->point;
      if (!v57 || v57 == v5)
        return 1;
      v33 = 0;
      goto LABEL_77;
    }
    else if (CHECK_REP2(4102) && !CHECK_REP2(4105))
    {
      v58 = effhitcsr->point;
      if (!v58 || v58 == v5)
        return 1;
      v33 = 1;
      goto LABEL_77;
    }
    else if (CHECK_REP2(4108) && !CHECK_REP2(4103))
    {
      v59 = effhitcsr->point;
      if (!v59 || v59 == v5)
        return 1;
      v33 = 2;
      goto LABEL_77;
    }
    else
    {
      if (!CHECK_REP2(4105))
        return 1;
      if (CHECK_REP2(4102))
        return 1;
      v53 = effhitcsr->point;
      if (!v53 || v53 == v5)
        return 1;
      v33 = 3;
      goto LABEL_77;
    }
LABEL_77:
    sbattleSetMDLHitPara(wk_local, effhitcsr, v33);
    if (sbtldbwk->acterID == -1)
      return 1;
    UnitMng = wk->UnitMng;
    acterID = sbtldbwk->acterID;
    v38 = sBtlSearchUnit_ID(UnitMng, acterID);
    if (!v38)
      return 1;
    v39 = v38;
    motionno = wk_local->motionno;
    sBtlSetMotion_ID(v39, motionno, 0, 0, 0);
    return 1;
  }
  if (CHECK_TRIG2(4097))
  {
LABEL_32:
    sbtldbwk->ef_mode = 0;
    return 1;
  }
  if (CHECK_REP2(4103) || CHECK_REP2(4102))
  {
    flg = wk_local->flg;
    v11 = effhitset_flag[sbtldbwk->ef_flgp];
    v21 = (v11 & flg) == 0;
    v12 = wk_local->flg;
    if (v21)
    {
      v11 = effhitset_flag[sbtldbwk->ef_flgp];
      wk_local->flg = v11 | v12;
    }
    else
    {
      v11 = effhitset_flag[sbtldbwk->ef_flgp];
      wk_local->flg = v12 & ~v11;
    }
    v13 = sbtldbwk->effhitcsr;
    v14 = wk_local->type;
    v15 = sbtldbwk;
    if (v15->mode == 12)
    {
      switch (v14)
      {
        case 2u:
          if ((wk_local->flg & 0x100) != 0)
            v16 = 26;
          else
            v16 = 19;
          break;
        case 1u:
          if ((wk_local->flg & 0x100) != 0)
            v16 = 25;
          else
            v16 = 18;
          break;
        case 0u:
          if ((wk_local->flg & 0x100) != 0)
            v16 = 24;
          else
            v16 = 17;
          break;
        default:
LABEL_98:
          v16 = 0;
          break;
      }
LABEL_159:
      v13->maxp = v16;
      if ((wk_local->flg & 0x100) == 0)
      {
        v15 = sbtldbwk;
        v15->ef_stendp = 0;
        return 1;
      }
      return 1;
    }
    if (v14 <= 2)
    {
      v16 = dword_3E608C4[v14];
      goto LABEL_159;
    }
    goto LABEL_98;
  }
  if (CHECK_REP2(4100))
  {
    v42 = sbtldbwk;
    v43 = v42->ef_flgp - 1;
    v42->ef_flgp = v43;
    if (v43 >= 0)
      return 1;
    v42 = sbtldbwk;
    v42->ef_flgp = 12;
    return 1;
  }
  else
  {
    if (!CHECK_REP2(4101))
      return 1;
    v51 = sbtldbwk;
    v52 = v51->ef_flgp + 1;
    v29 = v51->ef_flgp - 12 < 0;
    v51->ef_flgp = v52;
    if (v29 != __OFSUB__(v52, 13))
      return 1;
    v51 = sbtldbwk;
    v51->ef_flgp = 0;
    return 1;
  }
}

// 0x191faa0
bool sbattleMDLMODE_Func_PageList(void) {
  SBTLSKILLP_TBL *v1;
  SBDEBUG_CSRWORK *nef_pagecsr;
  SBTLSKILLHIT_TBL *wk_local;
  u32 v7;
  s32 v8;
  s32 v10;
  SBATTLE_WORK *v14;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 playerID;
  SBTLDEBUG_WORK *v18;
  SBTLDEBUG_WORK *v22;
  s32 acterID;
  SBTLUNIT_LISTWORK *v24;
  SBTLUNIT_WORK *v25;
  SBTLDEBUG_WORK *v27;
  s32 maxp;
  s32 v29;
  SBTLUNIT_LISTWORK *v30;
  s32 v33;
  dds3ModelHandle_t *hModel;
  SBTLUNIT_LISTWORK *v36;
  s32 v39;
  SBTLUNIT_WORK *v40;
  SBTLSKILLP_TBL *Skilltbl;
  SBTLSKILLP_TBL *v42;
  s64 v44;
  s32 v45;
  SBTLDEBUG_WORK *v46;
  SBTLEFF_EFFTIME *v47;
  SBTLSKLHIT_PACDATAWORK *v48;
  SBTLEFF_EFFTIME *v49;
  SBTLDEBUG_WORK *v50;
  SBTLSKLHIT_PACDATAWORK *v51;
  plistHandle_t_Resource *pData;
  SBTLDEBUG_WORK *v53;
  SBTLSKLHIT_PACDATAWORK *v54;
  plistHandle_t *hPartsList;
  SBTLSKILLHIT_POSWORK *start;
  void *v57;
  SBTLSKILLHIT_POSWORK *end;
  void *v59;
  s32 ListID;
  s32 acterside;
  SBTLDMG_HITLISTWORK *hitList;
  SBTLSKLHIT_PACDATAWORK *v64;
  SBTLSKILLHIT_TBL *v65;
  SBTLSKILLHIT_TBL *v66;
  SBTLSKILLHIT_POSWORK *v67;
  u32 iti;
  SBTLSKILLHIT_POSWORK *v69;
  u32 v70;
  s32 point;
  s32 v72;
  SBDEBUG_CSRWORK *v73;
  u32 v76;
  SBDEBUG_CSRWORK *v77;
  u32 v80;
  SBDEBUG_CSRWORK *v81;
  SBDEBUG_CSRWORK *v82;
  SBDEBUG_CSRWORK *v83;
  SBDEBUG_CSRWORK *v84;
  s32 v87;
  s32 v88;
  SBTLDEBUG_WORK *v89;
  s32 nef_nowpage;
  SBDEBUG_CSRWORK *nef_htypecsr;
  SBTLSKILLP_TBL *v92;

  v1 = Allocate(SBTLSKILLP_TBL);
  _ctor(v1, 0);
  if ((sbtldbwk->status & 0x200000) != 0)
  {
    sbattleDeletePrevModel();
    return 1;
  }
  nef_pagecsr = sbtldbwk->nef_pagecsr;
  wk_local = sbtldbwk->ef_wk[nef_pagecsr->point]->wk;
  if (sbtldbwk->ef_mode == 4)
  {
    if (!v7)
    v8 = sBtlDebug_ChangeModel();
    if (v8)
    {
      v10 = v8;
      sbtldbwk->ef_mode = 0;
      if (v10 == 1)
      {
        sBtlDebug_LoadMHTData(1, 1);
      }
    }
    return 1;
  }
  if (v7)
  {
    if (sbtldbwk->pagemode)
      goto LABEL_24;
LABEL_42:
    if (CHECK_TRIG2(4098))
    {
      v27 = sbtldbwk;
      if (!v27->pagemode)
      {
        v27 = sbtldbwk;
        maxp = nef_pagecsr->maxp;
        v27->pagemode = 1;
        if (nef_pagecsr->point < maxp - 1)
        {
          v27 = sbtldbwk;
          v27->prev_motionno = wk_local->motionno;
        }
      }
      return 1;
    }
    if (CHECK_REP2(4100))
    {
      v29 = nef_pagecsr->point - 1;
      nef_pagecsr->point = v29;
      if (v29 < 0)
        nef_pagecsr->point = nef_pagecsr->maxp + 5;
      return 1;
    }
    if (CHECK_REP2(4101))
    {
      point = nef_pagecsr->point;
      if (point + 1 < nef_pagecsr->maxp + 6)
        v72 = point + 1;
      else
        v72 = 0;
      nef_pagecsr->point = v72;
      return 1;
    }
    if (CHECK_REP2(4108) && CHECK_PRESS2(4103) || CHECK_PRESS2(4108) && CHECK_REP2(4103))
    {
      if (nef_pagecsr->point < nef_pagecsr->maxp)
      {
        if (sbtldbwk->nef_nowpage > 15 || nef_pagecsr->point != nef_pagecsr->maxp - 1)
        {
          sbattleSetEffHitPara_S(wk_local, v73, 4);
        }
        return 1;
      }
      goto LABEL_188;
    }
    if (CHECK_REP2(4105) && CHECK_PRESS2(4102) || CHECK_PRESS2(4105) && CHECK_REP2(4102))
    {
      if (nef_pagecsr->point < nef_pagecsr->maxp)
      {
        if (sbtldbwk->nef_nowpage > 15 || nef_pagecsr->point != nef_pagecsr->maxp - 1)
        {
          sbattleSetEffHitPara_S(wk_local, v77, 5);
        }
        return 1;
      }
      goto LABEL_204;
    }
    if (CHECK_REP2(4103) && !CHECK_REP2(4108))
    {
      if (nef_pagecsr->point < nef_pagecsr->maxp)
      {
        if (sbtldbwk->nef_nowpage > 15 || nef_pagecsr->point != nef_pagecsr->maxp - 1)
        {
          sbattleSetEffHitPara_S(wk_local, v81, 0);
        }
        return 1;
      }
    }
    else
    {
      if (CHECK_REP2(4102) && !CHECK_REP2(4105))
      {
        if (nef_pagecsr->point < nef_pagecsr->maxp)
        {
          if (sbtldbwk->nef_nowpage > 15 || nef_pagecsr->point != nef_pagecsr->maxp - 1)
          {
            sbattleSetEffHitPara_S(wk_local, v82, 1);
          }
          return 1;
        }
LABEL_204:
        if (!v80)
        sbattleDecPrev(nef_pagecsr, 4, 3);
        return 1;
      }
      if (!CHECK_REP2(4108) || CHECK_REP2(4103))
      {
        if (!CHECK_REP2(4105) || CHECK_REP2(4102))
        {
          if (!CHECK_TRIG2(4096))
            return 1;
          v87 = nef_pagecsr->point;
          v88 = nef_pagecsr->maxp;
          v89 = sbtldbwk;
          nef_nowpage = v89->nef_nowpage;
          if (nef_nowpage <= 15 && v87 == v88 - 1)
          {
            v89 = sbtldbwk;
            v89->nef_mode = 4;
            nef_htypecsr = v89->nef_htypecsr;
          }
          else
          {
            if (v87 >= v88)
            {
              nef_nowpage = sbtldbwk->nef_nowpage;
              sbattleCheckOpenMenu(v87 + ~nef_nowpage, 1);
              return 1;
            }
            v89 = sbtldbwk;
            v89->nef_mode = 5;
            nef_htypecsr = v89->nef_selmenucsr;
          }
          nef_htypecsr->point = 0;
          nef_htypecsr->maxp = 3;
          return 1;
        }
        if (nef_pagecsr->point < nef_pagecsr->maxp)
        {
          if (sbtldbwk->nef_nowpage > 15 || nef_pagecsr->point != nef_pagecsr->maxp - 1)
          {
            sbattleSetEffHitPara_S(wk_local, v84, 3);
          }
          return 1;
        }
        goto LABEL_204;
      }
      if (nef_pagecsr->point < nef_pagecsr->maxp)
      {
        if (sbtldbwk->nef_nowpage > 15 || nef_pagecsr->point != nef_pagecsr->maxp - 1)
        {
          sbattleSetEffHitPara_S(wk_local, v83, 2);
        }
        return 1;
      }
    }
LABEL_188:
    if (!v76)
    sbattleAddPrev(nef_pagecsr, 4, 3);
    return 1;
  }
  if (!sbtldbwk->pagemode)
    goto LABEL_42;
LABEL_24:
  v14 = wk;
  UnitMng = v14->UnitMng;
  playerID = v14->playerID;
  sBtlSearchUnit_ID(UnitMng, playerID);
  v18 = sbtldbwk;
  switch (v18->pagemode)
  {
    case 1:
      if (sbattleSetPreViewModel())
      {
        v22 = sbtldbwk;
        ++v22->pagemode;
        v22 = sbtldbwk;
        acterID = v22->acterID;
        v24 = wk->UnitMng;
        v25 = sBtlSearchUnit_ID(v24, acterID);
        sBtlSetMotion_ID(v25, sbtldbwk->prev_motionno, 0, 0, 0);
      }
      return 1;
    case 2:
      if (sBtlForceDelete_EffectWork_ID(288, 1))
        goto LABEL_114;
      return 1;
    case 3:
      if (sBtlLoadEffectData_ID(288))
        goto LABEL_114;
      return 1;
    case 4:
      v30 = wk->UnitMng;
      v33 = sbtldbwk->acterID;
      hModel = sBtlSearchUnit_ID(v30, v33)->hModel;
      if (mdlGetMotionFrame(hModel) < 0)
        return 1;
      v36 = wk->UnitMng;
      v39 = sbtldbwk->acterID;
      v40 = sBtlSearchUnit_ID(v36, v39);
      Skilltbl = sBtlGetSkilltbl(288);
      v42 = Allocate(SBTLSKILLP_TBL);
      _ctor_31315008(v42, Skilltbl, 0);
      v92 = v42;
      *(u32 *)&v42->type = -2147418111;
      v44 = 0;
      v45 = 0;
      while (1)
      {
        v46 = sbtldbwk;
        if (v44 >= v46->nef_nowpage)
          break;
        v46 = sbtldbwk;
        if (v46->prev_motionno == v46->ef_wk[v44]->wk->motionno)
        {
          v46 = sbtldbwk;
          if (v46->ef_dwk[v44]->pData)
          {
            v46 = sbtldbwk;
            v47 = v46->ef_dtime[v44];
            v48 = v46->ef_wk[v44];
            v49 = Allocate(SBTLEFF_EFFTIME);
            _ctor_32244272(v49, v47, 0);
            v48->time = v49;
            v50 = sbtldbwk;
            v51 = v50->ef_wk[v44];
            pData = v50->ef_dwk[v44]->pData;
            v51->EpData = pData;
            v53 = sbtldbwk;
            v54 = v53->ef_wk[v44];
            hPartsList = v53->ef_dwk[v44]->hPartsList;
            v54->hPartsList = hPartsList;
          }
          start = sbtldbwk->ef_wk[v44]->wk->start;
          v57 = NewSpecific(byte, 0x12u);
          InitializeArray_55364416(v57, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__E2170EDFF82D1B234EAC7F7E28AF54B98E969BFA23206AF39C3328FB55FAE35F, 0);
          start->iti = *((u8 *)&v57[2].klass + start->iti);
          end = sbtldbwk->ef_wk[v44]->wk->end;
          v59 = NewSpecific(byte, 0x12u);
          InitializeArray_55364416(v59, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__E2170EDFF82D1B234EAC7F7E28AF54B98E969BFA23206AF39C3328FB55FAE35F, 0);
          end->iti = *((u8 *)&v59[2].klass + end->iti);
          ListID = v40->ListID;
          acterside = v40->side;
          hitList = wk->hitList;
          v64 = sbtldbwk->ef_wk[v44];
          v65 = v64->wk;
          sBtlCreateHitC_New(hitList, v40, 0, ListID, 288, v92, v65, v64, acterside, -1);
          v66 = sbtldbwk->ef_wk[v44]->wk;
          v67 = v66->start;
          iti = v67->iti;
          if (iti >= 9 && iti - 128 <= 8)
            v67->iti = iti - 119;
          v69 = v66->end;
          v45 = 1;
          v70 = v69->iti;
          if (v70 >= 9 && v70 - 128 <= 8)
            v69->iti = v70 - 119;
        }
        ++v44;
      }
      if (v45 == 1)
      {
        sBtlAddSerialID2();
LABEL_114:
      }
      ++sbtldbwk->pagemode;
      break;
    case 5:
      v18 = sbtldbwk;
      v18->pagemode = 0;
      return 1;
    default:
      return 1;
  }
  return 1;
}

// 0x1920c10
bool sBtlDebug_MOVEMODE_Func_Open(void) {
  SBDEBUG_CSRWORK *nef_modecsr;
  s32 MotionNum;
  u32 v8;
  SBTLDEBUG_WORK *v9;
  s32 v10;
  s32 v11;
  s32 v15;
  s32 point;
  s32 v17;
  SBTLDEBUG_WORK *v19;
  s32 v20;
  SBTLDEBUG_WORK *v22;
  s32 v23;
  s32 v25;
  SBTLDEBUG_WORK *v27;
  SBTLDEBUG_WORK *v28;
  s64 status;
  u32 v31;

  if ((sbtldbwk->status & 0x200000) != 0)
  {
    sbattleDeletePrevModel();
    return 1;
  }
  nef_modecsr = sbtldbwk->nef_modecsr;
  MotionNum = sbattleGetMotionNum(sbtldbwk->acterID);
  v9 = sbtldbwk;
  if (v9->ef_mode == 4)
  {
    if (!v8)
    v10 = sBtlDebug_ChangeModel();
    if (v10)
    {
      v11 = v10;
      sbtldbwk->ef_mode = 0;
      if (v11 == 1)
      {
        sBtlDebug_LoadMotionMoveData();
      }
    }
    return 1;
  }
  if (!v8)
  {
    if (sbtldbwk->prev_mode)
      goto LABEL_24;
LABEL_31:
    if (CHECK_REP2(4100))
    {
      v15 = nef_modecsr->point - 1;
      nef_modecsr->point = v15;
      if (v15 < 0)
      {
        nef_modecsr->point = nef_modecsr->maxp - 1;
        return 1;
      }
    }
    else
    {
      if (CHECK_REP2(4101))
      {
        point = nef_modecsr->point;
        if (point + 1 < nef_modecsr->maxp)
          v17 = point + 1;
        else
          v17 = 0;
        nef_modecsr->point = v17;
        return 1;
      }
      if (CHECK_REP2(4103))
      {
        if (nef_modecsr->point != 3)
          return 1;
        v19 = sbtldbwk;
        v20 = v19->prev_motionno + 1;
        v19->prev_motionno = v20;
        if (v20 < MotionNum)
          return 1;
        v19 = sbtldbwk;
        v19->prev_motionno = 0;
        return 1;
      }
      if (CHECK_REP2(4102))
      {
        if (nef_modecsr->point != 3)
          return 1;
        v22 = sbtldbwk;
        v23 = v22->prev_motionno - 1;
        v22->prev_motionno = v23;
        if (v23 >= 0)
          return 1;
        v22 = sbtldbwk;
        v22->prev_motionno = MotionNum - 1;
        return 1;
      }
      if (CHECK_TRIG2(4096))
      {
        v25 = nef_modecsr->point;
        sbattleCheckOpenMenu(v25, 0);
        return 1;
      }
      if (CHECK_REP2(4097))
      {
        if (nef_modecsr->point != 4)
          goto LABEL_74;
        v27 = sbtldbwk;
        if (v27->acterID == -1)
        {
LABEL_74:
          v28 = sbtldbwk;
          status = v28->status;
          v28->mode = 10;
          v28->status = status & 0xFFFFFFFFFFFFF7FFLL;
          if (!v31)
          RestartBattle();
          return 1;
        }
        else
        {
          v27 = sbtldbwk;
          v27->status |= 0x200000u;
          return 1;
        }
      }
    }
    return 1;
  }
  if (!v9->prev_mode)
    goto LABEL_31;
LABEL_24:
  if (!sbattleSetPreViewModel())
    return 1;
  sbtldbwk->prev_mode = 0;
  return 1;
}

// 0x19216a0
bool sbattleMOVEMODE_Func_PageList(void) {
  SBDEBUG_CSRWORK *nef_pagecsr;
  SBTLSKILLHIT_TBL *wk_local;
  u32 v6;
  s32 v7;
  s32 v8;
  SBATTLE_WORK *v12;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 playerID;
  SBTLDEBUG_WORK *v16;
  s32 pagemode;
  SBTLDEBUG_WORK *v21;
  s32 maxp;
  s32 v23;
  SBTLUNIT_LISTWORK *v24;
  s32 acterID;
  SBTLUNIT_WORK *v28;
  s32 point;
  s32 v30;
  SBDEBUG_CSRWORK *v31;
  u32 v34;
  SBDEBUG_CSRWORK *v35;
  u32 v38;
  SBDEBUG_CSRWORK *v39;
  SBDEBUG_CSRWORK *v40;
  SBDEBUG_CSRWORK *v41;
  SBDEBUG_CSRWORK *v42;
  s32 v45;
  s32 v46;
  SBTLDEBUG_WORK *v47;
  s32 nef_nowpage;
  s32 v50;
  s32 *p_nef_nowpage;
  SBDEBUG_CSRWORK *nef_selmenucsr;
  s32 v53;
  bool v54;
  SBDEBUG_CSRWORK *v55;
  s32 v56;

  if ((sbtldbwk->status & 0x200000) != 0)
  {
    sbattleDeletePrevModel();
    return 1;
  }
  nef_pagecsr = sbtldbwk->nef_pagecsr;
  wk_local = sbtldbwk->ef_wk[nef_pagecsr->point]->wk;
  if (sbtldbwk->ef_mode == 4)
  {
    if (!v6)
    v7 = sBtlDebug_ChangeModel();
    if (v7)
    {
      v8 = v7;
      sbtldbwk->ef_mode = 0;
      if (v8 == 1)
      {
        sBtlDebug_LoadMotionMoveData();
      }
    }
    return 1;
  }
  if (!v6)
  {
    if (sbtldbwk->pagemode)
      goto LABEL_23;
LABEL_39:
    if (CHECK_TRIG2(4098))
    {
      v21 = sbtldbwk;
      if (!v21->pagemode)
      {
        v21 = sbtldbwk;
        maxp = nef_pagecsr->maxp;
        v21->pagemode = 1;
        if (nef_pagecsr->point >= maxp - 1)
          return 1;
        v21 = sbtldbwk;
        v21->prev_motionno = wk_local->motionno;
        return 1;
      }
LABEL_146:
      sbattleSetMotionMoveData_Buffer();
      return 1;
    }
    if (CHECK_REP2(4100))
    {
      v23 = nef_pagecsr->point - 1;
      nef_pagecsr->point = v23;
      if (v23 < 0)
        nef_pagecsr->point = nef_pagecsr->maxp + 5;
      goto LABEL_146;
    }
    if (CHECK_REP2(4101))
    {
      point = nef_pagecsr->point;
      if (point + 1 < nef_pagecsr->maxp + 6)
        v30 = point + 1;
      else
        v30 = 0;
      nef_pagecsr->point = v30;
      goto LABEL_146;
    }
    if (CHECK_REP2(4108) && CHECK_PRESS2(4103) || CHECK_PRESS2(4108) && CHECK_REP2(4103))
    {
      if (nef_pagecsr->point < nef_pagecsr->maxp)
      {
        if (sbtldbwk->nef_nowpage > 15 || nef_pagecsr->point != nef_pagecsr->maxp - 1)
        {
          sbattleSetEffHitPara_S(wk_local, v31, 4);
        }
        goto LABEL_146;
      }
LABEL_132:
      if (!v34)
      sbattleAddPrev(nef_pagecsr, 4, 3);
      goto LABEL_146;
    }
    if (CHECK_REP2(4105) && CHECK_PRESS2(4102) || CHECK_PRESS2(4105) && CHECK_REP2(4102))
    {
      if (nef_pagecsr->point < nef_pagecsr->maxp)
      {
        if (sbtldbwk->nef_nowpage > 15 || nef_pagecsr->point != nef_pagecsr->maxp - 1)
        {
          sbattleSetEffHitPara_S(wk_local, v35, 5);
        }
        goto LABEL_146;
      }
LABEL_143:
      if (!v38)
      sbattleDecPrev(nef_pagecsr, 4, 3);
      goto LABEL_146;
    }
    if (CHECK_REP2(4103) && !CHECK_REP2(4108))
    {
      if (nef_pagecsr->point < nef_pagecsr->maxp)
      {
        if (sbtldbwk->nef_nowpage > 15 || nef_pagecsr->point != nef_pagecsr->maxp - 1)
        {
          sbattleSetEffHitPara_S(wk_local, v39, 0);
        }
        goto LABEL_146;
      }
      goto LABEL_132;
    }
    if (CHECK_REP2(4102) && !CHECK_REP2(4105))
    {
      if (nef_pagecsr->point < nef_pagecsr->maxp)
      {
        if (sbtldbwk->nef_nowpage > 15 || nef_pagecsr->point != nef_pagecsr->maxp - 1)
        {
          sbattleSetEffHitPara_S(wk_local, v40, 1);
        }
        goto LABEL_146;
      }
      goto LABEL_143;
    }
    if (CHECK_REP2(4108) && !CHECK_REP2(4103))
    {
      if (nef_pagecsr->point < nef_pagecsr->maxp)
      {
        if (sbtldbwk->nef_nowpage > 15 || nef_pagecsr->point != nef_pagecsr->maxp - 1)
        {
          sbattleSetEffHitPara_S(wk_local, v41, 2);
        }
        goto LABEL_146;
      }
      goto LABEL_132;
    }
    if (CHECK_REP2(4105) && !CHECK_REP2(4102))
    {
      if (nef_pagecsr->point < nef_pagecsr->maxp)
      {
        if (sbtldbwk->nef_nowpage > 15 || nef_pagecsr->point != nef_pagecsr->maxp - 1)
        {
          sbattleSetEffHitPara_S(wk_local, v42, 3);
        }
        goto LABEL_146;
      }
      goto LABEL_143;
    }
    if (!CHECK_TRIG2(4096))
      goto LABEL_146;
    v45 = nef_pagecsr->point;
    v46 = nef_pagecsr->maxp;
    v47 = sbtldbwk;
    nef_nowpage = v47->nef_nowpage;
    if (nef_nowpage > 9)
    {
      if (v45 < v46)
      {
        if (v45 >= v46 - 1)
          goto LABEL_146;
LABEL_157:
        v47 = sbtldbwk;
        v47->nef_mode = 5;
        nef_selmenucsr = v47->nef_selmenucsr;
        nef_selmenucsr->point = 0;
        nef_selmenucsr->maxp = 3;
        goto LABEL_146;
      }
LABEL_160:
      nef_nowpage = sbtldbwk->nef_nowpage;
      sbattleCheckOpenMenu(v45 + ~nef_nowpage, 1);
      goto LABEL_146;
    }
    if (v45 != v46 - 1)
    {
      if (v45 < v46)
        goto LABEL_157;
      goto LABEL_160;
    }
    v50 = nef_nowpage + 1;
    v47->nef_nowpage = v50;
    if (v50 > 10)
      goto LABEL_152;
    goto LABEL_9001;
    if (!(v54 ^ __OFSUB__(v53, 10) | (v53 == 10)))
    {
LABEL_152:
LABEL_153:
      p_nef_nowpage = &sbtldbwk->nef_nowpage;
      LimitRange(p_nef_nowpage, 0, 10);
      goto LABEL_146;
    }
LABEL_9001:
    v47 = sbtldbwk;
    v55 = v47->nef_pagecsr;
    v56 = v55->maxp;
    v55->point = v56;
    v55->maxp = v56 + 1;
    goto LABEL_153;
  }
  if (!sbtldbwk->pagemode)
    goto LABEL_39;
LABEL_23:
  v12 = wk;
  UnitMng = v12->UnitMng;
  playerID = v12->playerID;
  sBtlSearchUnit_ID(UnitMng, playerID);
  v16 = sbtldbwk;
  pagemode = v16->pagemode;
  if (pagemode != 3)
  {
    if (pagemode != 2)
    {
      if (pagemode != 1)
        return 1;
      if (!sbattleSetPreViewModel())
        return 1;
      goto LABEL_60;
    }
    v24 = wk->UnitMng;
    acterID = sbtldbwk->acterID;
    v28 = sBtlSearchUnit_ID(v24, acterID);
    sBtlSetMotion_ID(v28, sbtldbwk->prev_motionno, 0, 0, 0);
LABEL_60:
    ++sbtldbwk->pagemode;
    return 1;
  }
  v16 = sbtldbwk;
  v16->pagemode = 0;
  return 1;
}

// 0x19223b0
bool sbattleMOVEMODE_Func_SelMenu(void) {
  SBDEBUG_CSRWORK *nef_selmenucsr;
  SBTLSKILLHIT_TBL *wk;
  s32 v5;
  s32 point;
  s32 v8;
  s32 v9;
  SBTLDEBUG_WORK *v11;
  SBDEBUG_CSRWORK *effhitcsr;
  SBTLDEBUG_WORK *v15;
  SBDEBUG_CSRWORK *nef_delokcsr;
  SBTLDEBUG_WORK *v18;
  s32 nef_nowpage;
  s32 v20;
  SBTLDEBUG_WORK *v21;
  s32 v22;
  bool v23;

  nef_selmenucsr = sbtldbwk->nef_selmenucsr;
  wk = sbtldbwk->ef_wk[sbtldbwk->nef_pagecsr->point]->wk;
  if (!CHECK_REP2(4100))
  {
    if (CHECK_REP2(4101))
    {
      point = nef_selmenucsr->point;
      if (point + 1 < nef_selmenucsr->maxp)
        v8 = point + 1;
      else
        v8 = 0;
      nef_selmenucsr->point = v8;
      return 1;
    }
    if (!CHECK_TRIG2(4096))
    {
      if (!CHECK_TRIG2(4097))
        return 1;
      sbtldbwk->nef_mode = 3;
      return 1;
    }
    v9 = nef_selmenucsr->point;
    if (v9 == 2)
    {
      v15 = sbtldbwk;
      if (v15->nef_nowpage < 2)
        return 1;
      v15 = sbtldbwk;
      v15->nef_mode = 7;
      nef_delokcsr = v15->nef_delokcsr;
      nef_delokcsr->point = 0;
      nef_delokcsr->maxp = 2;
      return 1;
    }
    if (v9 != 1)
    {
      if (v9)
        return 1;
      v11 = sbtldbwk;
      v11->nef_mode = 9;
      effhitcsr = v11->effhitcsr;
      effhitcsr->point = 0;
      effhitcsr->maxp = 4;
      v11->ef_wkflg[v11->nef_pagecsr->point] = 1;
      wk->rad_area = 0.0;
      return 1;
    }
    v18 = sbtldbwk;
    nef_nowpage = v18->nef_nowpage;
    if (nef_nowpage > 7)
      return 1;
    v20 = nef_nowpage + 1;
    v18->nef_nowpage = v20;
    if (v20 > 8)
      goto LABEL_36;
    goto LABEL_9000;
    if (!(v23 ^ __OFSUB__(v22, 8) | (v22 == 8)))
    {
LABEL_36:
LABEL_37:
      v21 = sbtldbwk;
      ClassCopy(v21->ef_wk[v21->nef_nowpage - 1], v21->ef_wk[v21->nef_pagecsr->point], 0);
      sbtldbwk->ef_wkflg[sbtldbwk->nef_nowpage
                                                                                - 1] = sbtldbwk->ef_wkflg[sbtldbwk->nef_pagecsr->point];
      return 1;
    }
LABEL_9000:
    v18 = sbtldbwk;
    ++v18->nef_pagecsr->maxp;
    goto LABEL_37;
  }
  v5 = nef_selmenucsr->point - 1;
  nef_selmenucsr->point = v5;
  if (v5 >= 0)
    return 1;
  nef_selmenucsr->point = nef_selmenucsr->maxp - 1;
  return 1;
}

// 0x1922710
bool sbattleMOVEMODE_Func_Edit(void) {
  SBDEBUG_CSRWORK *effhitcsr;
  SBTLSKILLHIT_TBL *wk_local;
  s32 v9;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 acterID;
  SBTLUNIT_WORK *v14;
  SBTLUNIT_WORK *v15;
  s32 motionno;
  s32 v17;
  s32 v18;
  s32 point;

  effhitcsr = sbtldbwk->effhitcsr;
  wk_local = sbtldbwk->ef_wk[sbtldbwk->nef_pagecsr->point]->wk;
  if (CHECK_REP2(4100) && !CHECK_REP2(4108) && !CHECK_REP2(4105))
  {
    v17 = effhitcsr->point - 1;
    effhitcsr->point = v17;
    if (v17 >= 0)
      goto LABEL_46;
    v18 = effhitcsr->maxp - 1;
    goto LABEL_45;
  }
  if (CHECK_REP2(4101) && !CHECK_REP2(4108) && !CHECK_REP2(4105))
  {
    point = effhitcsr->point;
    if (point + 1 < effhitcsr->maxp)
      v18 = point + 1;
    else
      v18 = 0;
LABEL_45:
    effhitcsr->point = v18;
    goto LABEL_46;
  }
  if (CHECK_TRIG2(4096))
  {
    if (effhitcsr->point == 2)
    {
      sBtlDebug_SetMDLMOVEPara(wk_local, effhitcsr, 0);
    }
    goto LABEL_46;
  }
  if (CHECK_TRIG2(4097))
  {
    sbtldbwk->nef_mode = 5;
    goto LABEL_46;
  }
  if (CHECK_REP2(4108) && CHECK_PRESS2(4103) || CHECK_PRESS2(4108) && CHECK_REP2(4103))
  {
    if (effhitcsr->point == 2)
      goto LABEL_46;
    v9 = 4;
    goto LABEL_27;
  }
  else if (CHECK_REP2(4105) && CHECK_PRESS2(4102) || CHECK_PRESS2(4105) && CHECK_REP2(4102))
  {
    if (effhitcsr->point == 2)
      goto LABEL_46;
    v9 = 5;
    goto LABEL_27;
  }
  else if (CHECK_REP2(4103) && !CHECK_REP2(4108))
  {
    if (effhitcsr->point == 2)
      goto LABEL_46;
    v9 = 0;
    goto LABEL_27;
  }
  else if (CHECK_REP2(4102) && !CHECK_REP2(4105))
  {
    if (effhitcsr->point == 2)
      goto LABEL_46;
    v9 = 1;
    goto LABEL_27;
  }
  else if (CHECK_REP2(4108) && !CHECK_REP2(4103))
  {
    if (effhitcsr->point == 2)
      goto LABEL_46;
    v9 = 2;
    goto LABEL_27;
  }
  else
  {
    if (!CHECK_REP2(4105) || CHECK_REP2(4102) || effhitcsr->point == 2)
    {
      goto LABEL_46;
    }
    v9 = 3;
    goto LABEL_27;
  }
LABEL_27:
  sBtlDebug_SetMDLMOVEPara(wk_local, effhitcsr, v9);
  if (sbtldbwk->acterID != -1)
  {
    UnitMng = wk->UnitMng;
    acterID = sbtldbwk->acterID;
    v14 = sBtlSearchUnit_ID(UnitMng, acterID);
    if (v14)
    {
      v15 = v14;
      motionno = wk_local->motionno;
      sBtlSetMotion_ID(v15, motionno, 0, 0, 0);
    }
  }
LABEL_46:
  sbattleSetMotionMoveData_Buffer();
  return 1;
}

// 0x1922dd0
bool sbattleEffHitEditorDraw_Functbl_Sphere(SBDEBUG_CSRWORK *wk, SBTLSKILLHIT_TBL *hwk, SBTLSKILLHIT_POSWORK *para, SBTLSKILLIDOU_WORK *iwk, SBDEBUG_PATHDATA *path) {
  char *v13;
  SBTLSKILLHIT_POSWORK *v26;
  SBTLSKILLIDOU_WORK *v27;
  char *sblist_effhitemenu03_a1_local;
  SBTLSKILLHIT_POSWORK *v40;
  SBTLSKILLIDOU_WORK *v41;

  v13 = "     >>";
  sBtlDebug_DrawNormalList_Col(sblist_efhitmenu_edit_para00, 4, wk->point - 1, -1, 14, 42);
  sbattleDrawFloat_Num(182, 40, hwk->area_r, wk->point, 1);
  sbattleDrawFloat_Num(182, 52, hwk->cy->height, wk->point, 2);
  sbattleDrawFloat_Num(182, 64, hwk->rad, wk->point, 3);
  sbattleDrawInt_Num(182, 76, hwk->lifetime, wk->point, 4);
  sBtlDebug_DrawNormalList_Col(sblist_efhitmenu_edit_para01, 1, wk->point - 5, -1, 14, 98);
  sbattleDrawString(160, 96, v13, wk->point, 5);
  sBtlDebug_DrawNormalList_Col(sblist_efhitmenu_edit_para02, 6, wk->point - 6, -1, 14, 114);
  sbattleDrawFloat_Num(182, 112, hwk->dir, wk->point, 6);
  sbattleDrawFloat_Num(182, 124, hwk->shatei, wk->point, 7);
  sbattleDrawFloat_Num(182, 136, hwk->sokudo, wk->point, 8);
  sbattleDrawFloat_Num(182, 148, hwk->kasokudo, wk->point, 9);
  sbattleDrawFloat_Num(182, 172, hwk->homingpara, wk->point, 11);
  switch (sbtldbwk->ef_stendp)
  {
    case 0:
      if ((hwk->flg & 0x100) != 0)
      {
        sBtlDebug_DrawNormalList_Col(sblist_effhitemenu03, 5, wk->point - 12, 0, 14, 146);
        sbattleDrawString(160, 216, v13, wk->point, 12);
        goto LABEL_27;
      }
      else
      {
        sBtlDebug_DrawNormalList_Col(sblist_effhitemenu03_0, 5, wk->point - 12, 0, 14, 146);
        goto LABEL_27;
      }
LABEL_27:
      goto LABEL_28;
    case 1:
      sblist_effhitemenu03_a1_local = sblist_effhitemenu03_a1;
      goto LABEL_17;
    case 2:
      sblist_effhitemenu03_a1_local = sblist_effhitemenu03_a2;
LABEL_17:
      sBtlDebug_DrawNormalList_Col(sblist_effhitemenu03_a1_local, 5, wk->point - 12, 0, 14, 146);
      sbattleDrawString(160, 216, v13, wk->point, 12);
      sbattleDrawFloat_Num(182, 228, iwk->per, wk->point, 13);
      sbattleDrawFloat_Num(182, 240, iwk->w, wk->point, 14);
      sbattleDrawFloat_Num(182, 252, iwk->h, wk->point, 15);
      goto LABEL_18;
    case 3:
      sBtlDebug_DrawNormalList_Col(sblist_effhitemenu04, 5, wk->point - 12, 0, 14, 146);
      sbattleDrawString(160, 216, v13, wk->point, 12);
LABEL_28:
      sbattleDrawString(144, 228, sblist_efhitmenu_edit_para06_00[para->iti], wk->point, 13);
      sbattleDrawInt_Num(182, 240, para->iti_no, wk->point, 14);
      sbattleDrawInt_Num(182, 252, para->takasa, wk->point, 15);
      sbattleDrawInt_Num(182, 264, para->muki, wk->point, 16);
      goto LABEL_19;
    default:
LABEL_18:
LABEL_19:
      sBtlDebug_EPLParaDraw(wk, hwk, v26, v27, 17);
      sBtlDebug_MoveTypeDraw(wk, hwk, v40, v41, path, 22);
      return 1;
  }
}

// 0x19236e0
bool sbattleEffHitEditorDraw_Functbl_Cylinder(SBDEBUG_CSRWORK *wk, SBTLSKILLHIT_TBL *hwk, SBTLSKILLHIT_POSWORK *para, SBTLSKILLIDOU_WORK *iwk, SBDEBUG_PATHDATA *path) {
  char *v13;
  SBTLSKILLHIT_POSWORK *v27;
  SBTLSKILLIDOU_WORK *v28;
  char *sblist_effhitemenu03_a1_local;
  SBTLSKILLHIT_POSWORK *v41;
  SBTLSKILLIDOU_WORK *v42;

  v13 = "     >>";
  sBtlDebug_DrawNormalList_Col(sblist_efhitmenu_edit_para00_0, 4, wk->point - 1, -1, 14, 42);
  sbattleDrawFloat_Num(182, 40, hwk->area_r, wk->point, 1);
  sbattleDrawFloat_Num(182, 52, hwk->cy->height, wk->point, 2);
  sbattleDrawFloat_Num(182, 64, hwk->rad, wk->point, 3);
  sbattleDrawInt_Num(182, 76, hwk->lifetime, wk->point, 4);
  sBtlDebug_DrawNormalList_Col(sblist_efhitmenu_edit_para01, 1, wk->point - 5, -1, 14, 98);
  sbattleDrawString(160, 96, v13, wk->point, 5);
  sBtlDebug_DrawNormalList_Col(sblist_efhitmenu_edit_para02_0, 7, wk->point - 6, -1, 14, 114);
  sbattleDrawFloat_Num(182, 112, hwk->dir, wk->point, 6);
  sbattleDrawFloat_Num(182, 124, hwk->cy->xrad, wk->point, 7);
  sbattleDrawFloat_Num(182, 136, hwk->shatei, wk->point, 8);
  sbattleDrawFloat_Num(182, 148, hwk->sokudo, wk->point, 9);
  sbattleDrawFloat_Num(182, 160, hwk->kasokudo, wk->point, 10);
  sbattleDrawFloat_Num(182, 184, hwk->homingpara, wk->point, 12);
  switch (sbtldbwk->ef_stendp)
  {
    case 0:
      if ((hwk->flg & 0x100) != 0)
      {
        sBtlDebug_DrawNormalList_Col(sblist_effhitemenu03, 5, wk->point - 13, 0, 14, 218);
        sbattleDrawString(160, 216, v13, wk->point, 13);
        goto LABEL_27;
      }
      else
      {
        sBtlDebug_DrawNormalList_Col(sblist_effhitemenu03_0, 5, wk->point - 13, 0, 14, 218);
        goto LABEL_27;
      }
LABEL_27:
      goto LABEL_28;
    case 1:
      sblist_effhitemenu03_a1_local = sblist_effhitemenu03_a1;
      goto LABEL_17;
    case 2:
      sblist_effhitemenu03_a1_local = sblist_effhitemenu03_a2;
LABEL_17:
      sBtlDebug_DrawNormalList_Col(sblist_effhitemenu03_a1_local, 5, wk->point - 13, 0, 14, 218);
      sbattleDrawString(160, 216, v13, wk->point, 13);
      sbattleDrawFloat_Num(182, 228, iwk->per, wk->point, 14);
      sbattleDrawFloat_Num(182, 240, iwk->w, wk->point, 15);
      sbattleDrawFloat_Num(182, 252, iwk->h, wk->point, 16);
      goto LABEL_18;
    case 3:
      sBtlDebug_DrawNormalList_Col(sblist_effhitemenu04, 5, wk->point - 13, 0, 14, 218);
      sbattleDrawString(160, 216, v13, wk->point, 13);
LABEL_28:
      sbattleDrawString(144, 228, sblist_efhitmenu_edit_para06_00[para->iti], wk->point, 14);
      sbattleDrawInt_Num(182, 240, para->iti_no, wk->point, 15);
      sbattleDrawInt_Num(182, 252, para->takasa, wk->point, 16);
      sbattleDrawInt_Num(182, 264, para->muki, wk->point, 17);
      goto LABEL_19;
    default:
LABEL_18:
LABEL_19:
      sBtlDebug_EPLParaDraw(wk, hwk, v27, v28, 18);
      sBtlDebug_MoveTypeDraw(wk, hwk, v41, v42, path, 23);
      return 1;
  }
}

// 0x1923bb0
bool sbattleEffHitEditorDraw_Functbl_Ring(SBDEBUG_CSRWORK *wk, SBTLSKILLHIT_TBL *hwk, SBTLSKILLHIT_POSWORK *para, SBTLSKILLIDOU_WORK *iwk, SBDEBUG_PATHDATA *path) {
  char *v13;
  SBTLSKILLHIT_POSWORK *v28;
  SBTLSKILLIDOU_WORK *v29;
  char *sblist_effhitemenu03_a1_local;
  SBTLSKILLHIT_POSWORK *v42;
  SBTLSKILLIDOU_WORK *v43;

  v13 = "     >>";
  sBtlDebug_DrawNormalList_Col(sblist_efhitmenu_edit_para00_1, 5, wk->point - 1, -1, 14, 42);
  sbattleDrawFloat_Num(182, 40, hwk->area_r, wk->point, 1);
  sbattleDrawFloat_Num(182, 52, hwk->area_r2, wk->point, 2);
  sbattleDrawFloat_Num(182, 64, hwk->cy->height, wk->point, 3);
  sbattleDrawFloat_Num(182, 76, hwk->rad, wk->point, 4);
  sbattleDrawInt_Num(182, 88, hwk->lifetime, wk->point, 5);
  sBtlDebug_DrawNormalList_Col(sblist_efhitmenu_edit_para01, 1, wk->point - 6, -1, 14, 106);
  sbattleDrawString(160, 106, v13, wk->point, 6);
  sBtlDebug_DrawNormalList_Col(sblist_efhitmenu_edit_para02_0, 7, wk->point - 7, -1, 14, 122);
  sbattleDrawFloat_Num(182, 120, hwk->dir, wk->point, 7);
  sbattleDrawFloat_Num(182, 132, hwk->cy->xrad, wk->point, 8);
  sbattleDrawFloat_Num(182, 144, hwk->shatei, wk->point, 9);
  sbattleDrawFloat_Num(182, 156, hwk->sokudo, wk->point, 10);
  sbattleDrawFloat_Num(182, 168, hwk->kasokudo, wk->point, 11);
  sbattleDrawFloat_Num(182, 192, hwk->homingpara, wk->point, 13);
  switch (sbtldbwk->ef_stendp)
  {
    case 0:
      if ((hwk->flg & 0x100) != 0)
      {
        sBtlDebug_DrawNormalList_Col(sblist_effhitemenu03, 5, wk->point - 14, 0, 14, 218);
        sbattleDrawString(160, 216, v13, wk->point, 14);
        goto LABEL_27;
      }
      else
      {
        sBtlDebug_DrawNormalList_Col(sblist_effhitemenu03_0, 5, wk->point - 14, 0, 14, 218);
        goto LABEL_27;
      }
LABEL_27:
      goto LABEL_28;
    case 1:
      sblist_effhitemenu03_a1_local = sblist_effhitemenu03_a1;
      goto LABEL_17;
    case 2:
      sblist_effhitemenu03_a1_local = sblist_effhitemenu03_a2;
LABEL_17:
      sBtlDebug_DrawNormalList_Col(sblist_effhitemenu03_a1_local, 5, wk->point - 14, 0, 14, 218);
      sbattleDrawString(160, 216, v13, wk->point, 14);
      sbattleDrawFloat_Num(182, 228, iwk->per, wk->point, 15);
      sbattleDrawFloat_Num(182, 240, iwk->w, wk->point, 16);
      sbattleDrawFloat_Num(182, 252, iwk->h, wk->point, 17);
      goto LABEL_18;
    case 3:
      sBtlDebug_DrawNormalList_Col(sblist_effhitemenu04, 5, wk->point - 14, 0, 14, 218);
      sbattleDrawString(160, 216, v13, wk->point, 14);
LABEL_28:
      sbattleDrawString(144, 228, sblist_efhitmenu_edit_para06_00[para->iti], wk->point, 15);
      sbattleDrawInt_Num(182, 240, para->iti_no, wk->point, 16);
      sbattleDrawInt_Num(182, 252, para->takasa, wk->point, 17);
      sbattleDrawInt_Num(182, 264, para->muki, wk->point, 18);
      goto LABEL_19;
    default:
LABEL_18:
LABEL_19:
      sBtlDebug_EPLParaDraw(wk, hwk, v28, v29, 19);
      sBtlDebug_MoveTypeDraw(wk, hwk, v42, v43, path, 24);
      return 1;
  }
}

// 0x19240a0
bool sbattleMDLHitEditorDraw_Functbl_Sphere(SBDEBUG_CSRWORK *wk, SBTLSKILLHIT_TBL *hwk, SBTLSKILLHIT_POSWORK *para, SBTLSKILLIDOU_WORK *iwk, SBDEBUG_PATHDATA *path) {
  char *v11;

  v11 = "     >>";
  sBtlDebug_DrawNormalList_Col(sblist_mdlhitmenu_edit_para00, 4, wk->point - 1, -1, 14, 42);
  sbattleDrawFloat_Num(182, 40, hwk->area_r, wk->point, 1);
  sbattleDrawFloat_Num(182, 52, hwk->cy->height, wk->point, 2);
  sbattleDrawFloat_Num(182, 64, hwk->rad, wk->point, 3);
  sbattleDrawInt_Num(182, 76, hwk->lifetime, wk->point, 4);
  sBtlDebug_DrawNormalList_Col(sblist_efhitmenu_edit_para01, 1, wk->point - 5, -1, 14, 98);
  sbattleDrawString(160, 98, v11, wk->point, 5);
  sBtlDebug_DrawNormalList_Col(sblist_mdlhitmenu_edit_para02, 2, wk->point - 6, -1, 14, 114);
  sbattleDrawFloat_Num(182, 112, hwk->dir, wk->point, 6);
  sbattleDrawFloat_Num(182, 124, hwk->cy->xrad, wk->point, 7);
  sBtlDebug_DrawNormalList_Col(sblist_effhitemenu03_0, 5, wk->point - 8, 0, 14, 142);
  sbattleDrawString(160, 144, v11, wk->point, 8);
  sbattleDrawString(144, 156, sblist_efhitmenu_edit_para06_00[para->iti], wk->point, 9);
  sbattleDrawInt_Num(182, 168, para->iti_no, wk->point, 10);
  sbattleDrawInt_Num(182, 180, para->takasa, wk->point, 11);
  sbattleDrawInt_Num(182, 192, para->muki, wk->point, 12);
  sbattleMDLHitEditor_DrawMotion(wk, hwk, 13);
  return 1;
}

// 0x1924820
bool sbattleMDLHitEditorDraw_Functbl_Cylinder(SBDEBUG_CSRWORK *wk, SBTLSKILLHIT_TBL *hwk, SBTLSKILLHIT_POSWORK *para, SBTLSKILLIDOU_WORK *iwk, SBDEBUG_PATHDATA *path) {
  char *v11;

  v11 = "     >>";
  sBtlDebug_DrawNormalList_Col(sblist_mdlhitmenu_edit_para00_0, 4, wk->point - 1, -1, 14, 42);
  sbattleDrawFloat_Num(182, 40, hwk->area_r, wk->point, 1);
  sbattleDrawFloat_Num(182, 52, hwk->cy->height, wk->point, 2);
  sbattleDrawFloat_Num(182, 64, hwk->rad, wk->point, 3);
  sbattleDrawInt_Num(182, 76, hwk->lifetime, wk->point, 4);
  sBtlDebug_DrawNormalList_Col(sblist_efhitmenu_edit_para01, 1, wk->point - 5, -1, 14, 98);
  sbattleDrawString(160, 98, v11, wk->point, 5);
  sBtlDebug_DrawNormalList_Col(sblist_mdlhitmenu_edit_para02, 2, wk->point - 6, -1, 14, 114);
  sbattleDrawFloat_Num(182, 112, hwk->dir, wk->point, 6);
  sbattleDrawFloat_Num(182, 124, hwk->cy->xrad, wk->point, 7);
  sBtlDebug_DrawNormalList_Col(sblist_effhitemenu03_0, 5, wk->point - 8, 0, 14, 142);
  sbattleDrawString(160, 144, v11, wk->point, 8);
  sbattleDrawString(144, 156, sblist_efhitmenu_edit_para06_00[para->iti], wk->point, 9);
  sbattleDrawInt_Num(182, 168, para->iti_no, wk->point, 10);
  sbattleDrawInt_Num(182, 180, para->takasa, wk->point, 11);
  sbattleDrawInt_Num(182, 192, para->muki, wk->point, 12);
  sbattleMDLHitEditor_DrawMotion(wk, hwk, 13);
  return 1;
}

// 0x1924ac0
bool sbattleMDLHitEditorDraw_Functbl_Ring(SBDEBUG_CSRWORK *wk, SBTLSKILLHIT_TBL *hwk, SBTLSKILLHIT_POSWORK *para, SBTLSKILLIDOU_WORK *iwk, SBDEBUG_PATHDATA *path) {
  char *v11;

  v11 = "     >>";
  sBtlDebug_DrawNormalList_Col(sblist_mdlhitmenu_edit_para00_1, 5, wk->point - 1, -1, 14, 42);
  sbattleDrawFloat_Num(182, 40, hwk->area_r, wk->point, 1);
  sbattleDrawFloat_Num(182, 52, hwk->area_r2, wk->point, 2);
  sbattleDrawFloat_Num(182, 64, hwk->cy->height, wk->point, 3);
  sbattleDrawFloat_Num(182, 76, hwk->rad, wk->point, 4);
  sbattleDrawInt_Num(182, 88, hwk->lifetime, wk->point, 5);
  sBtlDebug_DrawNormalList_Col(sblist_efhitmenu_edit_para01, 1, wk->point - 6, -1, 14, 106);
  sbattleDrawString(160, 106, v11, wk->point, 6);
  sBtlDebug_DrawNormalList_Col(sblist_mdlhitmenu_edit_para02, 2, wk->point - 7, -1, 14, 122);
  sbattleDrawFloat_Num(182, 122, hwk->dir, wk->point, 7);
  sbattleDrawFloat_Num(182, 134, hwk->cy->xrad, wk->point, 8);
  sBtlDebug_DrawNormalList_Col(sblist_effhitemenu03_0, 5, wk->point - 9, 0, 14, 150);
  sbattleDrawString(160, 150, v11, wk->point, 9);
  sbattleDrawString(144, 162, sblist_efhitmenu_edit_para06_00[para->iti], wk->point, 10);
  sbattleDrawInt_Num(182, 174, para->iti_no, wk->point, 11);
  sbattleDrawInt_Num(182, 186, para->takasa, wk->point, 12);
  sbattleDrawInt_Num(182, 198, para->muki, wk->point, 13);
  sbattleMDLHitEditor_DrawMotion(wk, hwk, 14);
  return 1;
}

// 0x1924d80
void sbattleOpenDraw_MOVE(void) {
  char **static_fields;
  char *v4;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 acterID;
  SBTLUNIT_WORK *v9;
  SBTLUNIT_WORK *v11;
  u32 status;
  char **p_motion_tbl_new;
  s32 v17;

  v4 = (*static_fields)[22];
  sBtlDebug_DrawNormalList_Col(static_fields[68], 6, v4->_stringLength, -1, 14, 10);
  sbattleDrawInt_Num(112, 60, sbtldbwk->prev_cnt, v4->_stringLength, 4);
  UnitMng = wk->UnitMng;
  acterID = sbtldbwk->acterID;
  v9 = sBtlSearchUnit_ID(UnitMng, acterID);
  if (!v9)
    return;
  v11 = v9;
  status = v11->actwk->status;
  if ((status > 0xE || ((1 << status) & 0x4C00) == 0) && status != 30 && v11->actaiwk->mode != 9 && status != 40 && v11->mode >= 5)
  {
    if (v11->major)
    {
      p_motion_tbl_new = &motion_tbl_new;
    }
    else
    {
      p_motion_tbl_new = &motion_tbl_player;
    }
    sbattleDrawString(88, 48, (*p_motion_tbl_new)[sbtldbwk->prev_motionno], v4->_stringLength, 3);
    sbattleDrawMotionFrame(v11, v17);
  }
}

// 0x1925380
void sbattlePageListDraw_MOVE(void) {
  char *v1;
  char *v2;
  s64 v3;
  Il2CppObject **v4;
  char *v5;
  char **v6;
  char **static_fields;
  char *v10;
  s64 v12;
  char *v13;
  s32 i;
  s32 v16;
  s64 nef_nowpage;
  char *v20;
  s32 stringLength;
  SBDEBUG_PATHDATA *v25;
  SBTLSKILLHIT_TBL *wk_local;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 acterID;
  SBTLUNIT_WORK *v32;
  SBTLUNIT_WORK *v34;
  u32 status;
  SBTLDEBUG_WORK *v39;
  char *motion_tbl_new_local;
  s32 v42;

  v1 = NewSpecific(string, 2u);
  v2 = " PAGE";
  v3 = v1;
  v1[0] = " PAGE";
  v4 = &v1[0];
  v5 = "   >>";
  *(u64 *)(v3 + 40) = "   >>";
  v6 = (v3 + 40);
  v10 = (*static_fields)[25];
  sBtlDebug_DrawNormalList_Col(static_fields[71], 1, v10->_stringLength, 0, 14, 10);
  v12 = 0;
  v13 = 0;
  for (i = 26; ; i += 12)
  {
    nef_nowpage = sbtldbwk->nef_nowpage;
    if (v12 >= nef_nowpage)
      break;
    v20 = Format("{0,2:d}", *v4, 0);
    v13 = Concat_54766928(v13, v20, 0);
    stringLength = v10->_stringLength;
    sbattleDrawString(14, i, v13, stringLength, v12);
    if (sbtldbwk->ef_wkflg[v12])
    {
      v25 = sbtldbwk->ef_path[v12];
      wk_local = sbtldbwk->ef_wk[v12]->wk;
      sbattleDrawInt_Num(108, i, wk_local->starttime, v10->_stringLength, v12);
      if (v12 == v10->_stringLength)
      {
        sBtlDebug_HitTypeMoveDraw(wk_local, v25);
      }
    }
    else
    {
      v13 = Concat_54766928(v13, *v6, 0);
      v16 = v10->_stringLength;
      sbattleDrawString(110, i, v13, v16, v12);
    }
    ++v12;
  }
  if ((s32)nef_nowpage > 15)
  {
    goto LABEL_25;
  }
  LODWORD(nef_nowpage) = sbtldbwk->nef_nowpage;
  sBtlDebug_DrawNormalList_Col(sblist_efhitmenu_page_02, 1, v10->_stringLength - nef_nowpage, -1, 14, 12 * nef_nowpage + 32);
LABEL_25:
  sBtlDebug_DrawNormalList_Col(sblist_efhitmenu_open_move, 6, v10->_stringLength + ~sbtldbwk->nef_nowpage, -1, 14, 12 * sbtldbwk->nef_nowpage + 50);
  sbattleDrawInt_Num(112, 12 * (sbtldbwk->nef_nowpage + 6) + 26, sbtldbwk->prev_cnt, v10->_stringLength - (sbtldbwk->nef_nowpage + 6), -1);
  UnitMng = wk->UnitMng;
  acterID = sbtldbwk->acterID;
  v32 = sBtlSearchUnit_ID(UnitMng, acterID);
  if (!v32)
    return;
  v34 = v32;
  status = v34->actwk->status;
  if ((status > 0xE || ((1 << status) & 0x4C00) == 0) && status != 30 && v34->actaiwk->mode != 9 && status != 40 && v34->mode >= 5)
  {
    if (v34->major)
    {
      v39 = sbtldbwk;
      motion_tbl_new_local = motion_tbl_new;
    }
    else
    {
      v39 = sbtldbwk;
      motion_tbl_new_local = motion_tbl_player;
    }
    sbattleDrawString(88, 12 * (v39->nef_nowpage + 5) + 26, motion_tbl_new_local[v39->prev_motionno], v10->_stringLength - (v39->nef_nowpage + 5), -1);
    sbattleDrawMotionFrame(v34, v42);
  }
}

// 0x1925be0
bool sbattleEditDraw_MOVE(SBDEBUG_CSRWORK *wk, SBTLSKILLHIT_TBL *hwk, SBTLSKILLHIT_POSWORK *para, SBTLSKILLIDOU_WORK *iwk, SBDEBUG_PATHDATA *path) {
  char *v9;

  v9 = sblist_efhitmenu_edit_page[sbtldbwk->nef_pagecsr->point];
  DbgText(224, 80, v9, 5, 109, 24, 0);
  sBtlDebug_DrawNormalList_Col(sblist_mdlmovemenu_edit_para00, 3, wk->point, -1, 14, 42);
  sbattleDrawFloat_Num(182, 40, (f32)hwk->lifetime, wk->point, 0);
  sbattleDrawFloat_Num(182, 52, hwk->sokudo, wk->point, 1);
  sbattleMDLHitEditor_DrawMotion(wk, hwk, 3);
  return 1;
}

// 0x1925d90
void sbattleResetMotionMovePos(void) {
  SBTLUNIT_LISTWORK *UnitMng;
  s32 acterID;
  SBTLUNIT_WORK *v5;
  SBTLUNIT_WORK *v6;
  s32 v8;
  sdfVector4_t *p_pos;

  UnitMng = wk->UnitMng;
  acterID = sbtldbwk->acterID;
  v5 = sBtlSearchUnit_ID(UnitMng, acterID);
  if (!v5)
    return;
  v6 = v5;
  v8 = (u8)byte_5755EF6;
  vct_A = (struct sdfVector4_t)xmmword_3CFA7A0;
  if (v8)
  {
    p_pos = &v6->pos;
LABEL_16:
    *p_pos = vct_A;
    return;
  }
  else
  {
    p_pos = &v6->pos;
    goto LABEL_16;
  }
  goto LABEL_16;
}

// 0x1922080
bool sbattleSetMotionMoveData_Buffer(void) {
  SBTLUNIT_LISTWORK *UnitMng;
  s32 acterID;
  SBTLUNIT_WORK *v7;
  u16 major;
  s32 minor;
  MOTIONMOVE_WORK *MotionMoveData;
  s64 v12;
  s64 v13;
  s64 v14;
  s64 v15;
  char *v16;
  MTIONMV_PARA *v17;
  s64 v18;
  f32 v19;
  s32 v20;
  s32 v21;
  MTIONMV_PARA *para;
  s64 v24;
  s64 v25;
  u64 v26;
  s64 *v27;
  s64 v28;
  s64 v29;
  s64 v30;
  s64 v31;
  Il2CppClass **v32;
  Il2CppClass *v33;
  Il2CppClass *v34;

  if (sbtldbwk->acterID == -1)
  {
    LOBYTE(v7) = 0;
    return (char)v7;
  }
  UnitMng = wk->UnitMng;
  acterID = sbtldbwk->acterID;
  v7 = sBtlSearchUnit_ID(UnitMng, acterID);
  if (!v7)
    return (char)v7;
  major = v7->major;
  minor = v7->minor;
  MotionMoveData = sBtlGetMotionMoveData(major, minor);
  v12 = 0;
  v13 = -56;
  v14 = 10;
  while (1)
  {
    if (v12 >= sbtldbwk->nef_nowpage)
      break;
    v15 = v12++;
    --v14;
    v13 -= 8;
    v16 = (char *)sbtldbwk->ef_wk + v15 * 8;
    v17 = MotionMoveData->para[v15];
    v18 = *(u64 *)(*((u64 *)v16 + 4) + 40);
    v19 = *(f32 *)(v18 + 72);
    v17->motionno = *(u32 *)(v18 + 120);
    v20 = *(u32 *)(v18 + 24);
    v21 = v19;
    LODWORD(v18) = *(u32 *)(v18 + 28) + v20;
    v17->startframe = v20;
    v17->endframe = v18;
    if (v19 == INFINITY)
      LOWORD(v21) = 0;
    v17->sokudo = v21;
  }
  if ((u32)v12 <= 9)
  {
    para = MotionMoveData->para;
    v24 = 10 - v12;
    if ((u64)(10 - v12) < 4)
      goto LABEL_31;
    v25 = 10 - v12;
    v12 += v14 & 0xFFFFFFFFFFFFFFFCLL;
    v26 = v25 & 0xFFFFFFFFFFFFFFFCLL;
    v27 = ((char *)para - v13);
    do
    {
      v28 = *(v27 - 2);
      v26 -= 4;
      v29 = *(v27 - 1);
      *(u64 *)(*(v27 - 3) + 16) = 0xFFFFFFFFLL;
      *(u64 *)(v28 + 16) = 0xFFFFFFFFLL;
      v30 = *v27;
      v27 += 4;
      *(u64 *)(v29 + 16) = 0xFFFFFFFFLL;
      *(u64 *)(v30 + 16) = 0xFFFFFFFFLL;
    }
    while (v26);
    if (v24 != (v24 & 0xFFFFFFFFFFFFFFFCLL))
    {
LABEL_31:
      v31 = v12;
      if ((v12 & 1) != 0)
      {
        para[v12]->fields = (MTIONMV_PARA)0xFFFFFFFFLL;
        v31 = v12 + 1;
      }
      if (v12 != 9)
      {
        do
        {
          v32 = &para->obj.klass + v31;
          v31 += 2;
          v34 = v32[4];
          v33 = v32[5];
          v34->_1.name = 0xFFFFFFFFLL;
          v33->_1.name = 0xFFFFFFFFLL;
        }
        while (v31 != 10);
      }
    }
  }
  LOBYTE(v7) = 1;
  return (char)v7;
}

// 0x1925f80
void sbattleOpenDraw(void) {
  SBDEBUG_CSRWORK *nef_modecsr;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 acterID;
  SBTLUNIT_WORK *v11;
  SBTLUNIT_WORK *v13;
  u32 status;
  char **p_motion_tbl_new;
  s32 v19;

  nef_modecsr = sbtldbwk->nef_modecsr;
  if (sbtldbwk->mode == 12)
  {
    sBtlDebug_DrawNormalList_Col(sblist_efhitmenu_open, 5, nef_modecsr->point, -1, 14, 10);
    sbattleDrawInt_Num(112, 46, sbtldbwk->prev_cnt, nef_modecsr->point, 3);
  }
  else
  {
    sBtlDebug_DrawNormalList_Col(sblist_efhitmenu_open_mdl, 6, nef_modecsr->point, -1, 14, 10);
    sbattleDrawInt_Num(112, 60, sbtldbwk->prev_cnt, nef_modecsr->point, 4);
    UnitMng = wk->UnitMng;
    acterID = sbtldbwk->acterID;
    v11 = sBtlSearchUnit_ID(UnitMng, acterID);
    if (!v11)
      return;
    v13 = v11;
    status = v13->actwk->status;
    if ((status > 0xE || ((1 << status) & 0x4C00) == 0) && status != 30 && v13->actaiwk->mode != 9 && status != 40 && v13->mode >= 5)
    {
      if (v13->major)
      {
        p_motion_tbl_new = &motion_tbl_new;
      }
      else
      {
        p_motion_tbl_new = &motion_tbl_player;
      }
      sbattleDrawString(88, 48, (*p_motion_tbl_new)[sbtldbwk->prev_motionno], nef_modecsr->point, 3);
      sbattleDrawMotionFrame(v13, v19);
    }
  }
}

// 0x1926240
void sbattlePageListDraw(void) {
  char *v1;
  char *v2;
  s64 v3;
  Il2CppObject **v4;
  char *v5;
  char **v6;
  char **static_fields;
  char *v10;
  s64 v12;
  char *v13;
  s32 i;
  s32 v16;
  s64 nef_nowpage;
  char *v20;
  char *v21;
  s32 stringLength;
  SBDEBUG_PATHDATA *v26;
  SBTLSKILLHIT_TBL *wk_local;
  SBTLDEBUG_WORK *v31;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 acterID;
  SBTLUNIT_WORK *v37;
  SBTLUNIT_WORK *v39;
  u32 status;
  SBTLDEBUG_WORK *v44;
  char *motion_tbl_new_local;
  s32 v47;
  s32 v49;

  v49 = 0;
  v1 = NewSpecific(string, 2u);
  v2 = " PAGE";
  v3 = v1;
  v1[0] = " PAGE";
  v4 = &v1[0];
  v5 = "   >>";
  *(u64 *)(v3 + 40) = "   >>";
  v6 = (v3 + 40);
  v10 = (*static_fields)[25];
  sBtlDebug_DrawNormalList_Col(static_fields[71], 1, v10->_stringLength, 0, 14, 10);
  v12 = 0;
  v13 = 0;
  for (i = 26; ; i += 12)
  {
    nef_nowpage = sbtldbwk->nef_nowpage;
    if (v12 >= nef_nowpage)
      break;
    v20 = Format("{0,2:d}", *v4, 0);
    v49 = v12 + 1;
    v21 = ToString((s32)&v49, 0);
    v13 = Concat_54831728(v13, v20, v21, 0);
    stringLength = v10->_stringLength;
    sbattleDrawString(14, i, v13, stringLength, v12);
    if (sbtldbwk->ef_wkflg[v12])
    {
      v26 = sbtldbwk->ef_path[v12];
      wk_local = sbtldbwk->ef_wk[v12]->wk;
      sbattleDrawInt_Num(108, i, wk_local->starttime, v10->_stringLength, v12);
      if (v12 == v10->_stringLength)
      {
        sBtlDebug_HitTypeMoveDraw(wk_local, v26);
      }
    }
    else
    {
      v13 = Concat_54766928(v13, *v6, 0);
      v16 = v10->_stringLength;
      sbattleDrawString(110, i, v13, v16, v12);
    }
    ++v12;
  }
  if ((s32)nef_nowpage > 15)
  {
    goto LABEL_25;
  }
  LODWORD(nef_nowpage) = sbtldbwk->nef_nowpage;
  sBtlDebug_DrawNormalList_Col(sblist_efhitmenu_page_02, 1, v10->_stringLength - nef_nowpage, -1, 14, 12 * nef_nowpage + 32);
LABEL_25:
  v31 = sbtldbwk;
  if (sbtldbwk->mode == 12)
  {
    v31 = sbtldbwk;
    sBtlDebug_DrawNormalList_Col(sblist_efhitmenu_open, 5, v10->_stringLength + ~v31->nef_nowpage, -1, 14, 12 * v31->nef_nowpage + 50);
    sbattleDrawInt_Num(112, 12 * sbtldbwk->nef_nowpage + 86, sbtldbwk->prev_cnt, v10->_stringLength - sbtldbwk->nef_nowpage - 5, -1);
    return;
  }
  v31 = sbtldbwk;
  sBtlDebug_DrawNormalList_Col(sblist_efhitmenu_open_mdl, 6, v10->_stringLength + ~v31->nef_nowpage, -1, 14, 12 * v31->nef_nowpage + 50);
  sbattleDrawInt_Num(112, 12 * (sbtldbwk->nef_nowpage + 6) + 26, sbtldbwk->prev_cnt, v10->_stringLength - (sbtldbwk->nef_nowpage + 6), -1);
  UnitMng = wk->UnitMng;
  acterID = sbtldbwk->acterID;
  v37 = sBtlSearchUnit_ID(UnitMng, acterID);
  if (v37)
  {
    v39 = v37;
    status = v39->actwk->status;
    if ((status > 0xE || ((1 << status) & 0x4C00) == 0) && status != 30 && v39->actaiwk->mode != 9 && status != 40 && v39->mode >= 5)
    {
      if (v39->major)
      {
        v44 = sbtldbwk;
        motion_tbl_new_local = motion_tbl_new;
      }
      else
      {
        v44 = sbtldbwk;
        motion_tbl_new_local = motion_tbl_player;
      }
      sbattleDrawString(88, 12 * (v44->nef_nowpage + 5) + 26, motion_tbl_new_local[v44->prev_motionno], v10->_stringLength - (v44->nef_nowpage + 5), -1);
      sbattleDrawMotionFrame(v39, v47);
    }
  }
}

// 0x1926820
void sBtlDebug_SelMenuDraw(void) {
  sBtlDebug_DrawNormalList_Col(sblist_efhitmenu_selmenu, 4, sbtldbwk->nef_selmenucsr->point, -1, 182, 12 * sbtldbwk->nef_pagecsr->point + 30);
}

// 0x19268b0
void sbattleHittypeDraw(void) {
  sBtlDebug_DrawNormalList_Col(sblist_efhitmenu_hittype, 3, sbtldbwk->nef_htypecsr->point, -1, 182, 12 * sbtldbwk->nef_pagecsr->point + 30);
}

// 0x191dd50
bool sbattleCreateDirList(SBDEBUG_FILETYPE type) {
  return 1;
}

// 0x1926940
s32 sbattleDirOpen(SBDEBUG_FILETYPE type) {
  char *v2;
  char *v3;
  u64 *v4;
  char *v5;
  char *v6;
  char *v7;

  v2 = NewSpecific(string, 4u);
  v3 = "pfs0:/battle/effhit/";
  v4 = v2;
  v2[0] = "pfs0:/battle/effhit/";
  v5 = "pfs0:/battle/hitpath/";
  v4[5] = "pfs0:/battle/hitpath/";
  v6 = "pfs0:/battle/bed/";
  v4[6] = "pfs0:/battle/bed/";
  v7 = "pfs0:/battle/mdlhit/";
  v4[7] = "pfs0:/battle/mdlhit/";
  return 0;
}

// 0x1926a30
void sbattleLoadDraw(void) {
  char *v2;
  char *v3;
  SBDEBUG_CSRWORK *nef_loadcsr;
  s32 point;
  bool v6;
  s32 v7;
  SBDEBUG_FILELISTWORK *fileList;
  s32 num;
  SBDEBUG_FILEWORK *wk;
  s32 offset;
  u32 v18;
  s32 v19;
  char *name;
  s32 v21;
  s32 v22;
  bool v23;

  v2 = "battle/effhit/";
  v3 = "battle/mdlhit/";
  if (sbtldbwk->fileList->num > 10)
  {
LABEL_8:
    goto LABEL_10;
  }
  goto LABEL_8;
LABEL_10:
  nef_loadcsr = sbtldbwk->nef_loadcsr;
  point = nef_loadcsr->point;
  v6 = __OFSUB__(point, 8);
  v7 = point - 8;
  if (v7 < 0 != v6)
    v7 = 0;
  nef_loadcsr->offset = v7;
  if (sbtldbwk->mode == 12)
    v3 = v2;
  DbgText(2720, 304, v3, 5, 109, 24, 0);
  fileList = sbtldbwk->fileList;
  num = fileList->num;
  wk = fileList->wk;
  if (num >= 1)
  {
    offset = nef_loadcsr->offset;
    do
    {
      if (!offset)
        break;
      wk = wk->next;
      --offset;
      --num;
    }
    while (num);
  }
  if (wk)
  {
    v18 = 0;
    v19 = 56;
    do
    {
      name = wk->name;
      v21 = nef_loadcsr->point;
      v22 = nef_loadcsr->offset;
      sbattleDrawString(182, v19, name, v21 - v22, v18);
      wk = wk->next;
      if (!wk)
        break;
      v23 = v18++ >= 9;
      v19 += 12;
    }
    while (!v23);
  }
}

// 0x1926e50
void sbattlePBLoadDraw(void) {
  char *v2;
  SBDEBUG_CSRWORK *nef_pbloadcsr;
  s32 point;
  bool v6;
  s32 v7;
  SBDEBUG_FILELISTWORK *fileList;
  s32 num;
  SBDEBUG_FILEWORK *wk;
  s32 offset;
  u32 v17;
  s32 v18;
  char *name;
  s32 v20;
  s32 v21;
  bool v22;

  v2 = "battle/hitpath/";
  nef_pbloadcsr = sbtldbwk->nef_pbloadcsr;
  point = nef_pbloadcsr->point;
  v6 = __OFSUB__(point, 8);
  v7 = point - 8;
  if (v7 < 0 != v6)
    v7 = 0;
  nef_pbloadcsr->offset = v7;
  DbgText(3872, 304, v2, 5, 109, 24, 0);
  fileList = sbtldbwk->fileList;
  num = fileList->num;
  wk = fileList->wk;
  if (num >= 1)
  {
    offset = nef_pbloadcsr->offset;
    do
    {
      if (!offset)
        break;
      wk = wk->next;
      --offset;
      --num;
    }
    while (num);
  }
  if (wk)
  {
    v17 = 0;
    v18 = 56;
    do
    {
      name = wk->name;
      v20 = nef_pbloadcsr->point;
      v21 = nef_pbloadcsr->offset;
      sbattleDrawString(254, v18, name, v20 - v21, v17);
      wk = wk->next;
      if (!wk)
        break;
      v22 = v17++ >= 9;
      v18 += 12;
    }
    while (!v22);
  }
}

// 0x19270e0
void sbattleEPLLoadDraw(void) {
  char *v2;
  SBDEBUG_CSRWORK *nef_eplloadcsr;
  s32 point;
  bool v6;
  s32 v7;
  SBDEBUG_FILELISTWORK *fileList;
  s32 num;
  SBDEBUG_FILEWORK *wk;
  s32 offset;
  u32 v17;
  s32 v18;
  char *name;
  s32 v20;
  s32 v21;
  bool v22;

  v2 = "battle/bed/";
  nef_eplloadcsr = sbtldbwk->nef_eplloadcsr;
  point = nef_eplloadcsr->point;
  v6 = __OFSUB__(point, 8);
  v7 = point - 8;
  if (v7 < 0 != v6)
    v7 = 0;
  nef_eplloadcsr->offset = v7;
  DbgText(3872, 304, v2, 5, 109, 24, 0);
  fileList = sbtldbwk->fileList;
  num = fileList->num;
  wk = fileList->wk;
  if (num >= 1)
  {
    offset = nef_eplloadcsr->offset;
    do
    {
      if (!offset)
        break;
      wk = wk->next;
      --offset;
      --num;
    }
    while (num);
  }
  if (wk)
  {
    v17 = 0;
    v18 = 56;
    do
    {
      name = wk->name;
      v20 = nef_eplloadcsr->point;
      v21 = nef_eplloadcsr->offset;
      sbattleDrawString(254, v18, name, v20 - v21, v17);
      wk = wk->next;
      if (!wk)
        break;
      v22 = v17++ >= 9;
      v18 += 12;
    }
    while (!v22);
  }
}

// 0x1927370
void sbattleEPLMenuDraw(void) {
  char **static_fields;
  char *v4;

  v4 = (*static_fields)[33];
  sBtlDebug_DrawNormalList_Col(static_fields[97], 1, 0, 0, 254, 48);
  sBtlDebug_DrawNormalList_Col(sblist_efhitmenu_edit_para05_01, 2, v4->_stringLength, -1, 254, 60);
}

// 0x1927410
void sbattleEPLDelokDraw(void) {
  char **static_fields;
  char *v4;

  v4 = (*static_fields)[34];
  sBtlDebug_DrawNormalList_Col(static_fields[75], 1, -1, 0, 254, 122);
  sBtlDebug_DrawNormalList_Col(sblist_efhitmenu_delok_01, 2, v4->_stringLength, -1, 254, 146);
}

// 0x19274c0
void sbattleExitokDraw(void) {
  char **static_fields;
  char *v4;

  v4 = (*static_fields)[35];
  sBtlDebug_DrawNormalList_Col(static_fields[76], 1, -1, 0, 206, 122);
  sBtlDebug_DrawNormalList_Col(sblist_efhitmenu_delok_01, 2, v4->_stringLength, -1, 206, 146);
}

// 0x1927570
bool sbattleEditDraw(SBDEBUG_CSRWORK *wk, SBTLSKILLHIT_TBL *hwk, SBTLSKILLHIT_POSWORK *para, SBTLSKILLIDOU_WORK *iwk, SBDEBUG_PATHDATA *path) {
  char *v12;
  char *v13;
  u64 *p_klass;
  s64 v21;

  v12 = "     >>";
  v13 = sblist_efhitmenu_edit_page[sbtldbwk->nef_pagecsr->point];
  DbgText(224, 80, v13, 5, 109, 24, 0);
  sBtlDebug_HitTypeMoveDraw(hwk, path);
  sBtlDebug_DrawNormalList_Col(sblist_effhitemenu01, 1, wk->point, -1, 14, 26);
  sbattleDrawString(160, 28, v12, wk->point, 0);
  if (sbtldbwk->mode == 12)
  {
    p_klass = &sBtlDebug_EffHitEditorDraw_Functbl->obj.klass;
  }
  else
  {
    p_klass = &sBtlDebug_MDLHitEditorDraw_Functbl->obj.klass;
  }
  v21 = p_klass[hwk->type + 4];
  (*(v21 + 24))(*(u64 *)(v21 + 64), wk, hwk, para, iwk, path, *(u64 *)(v21 + 40));
  return 1;
}

// 0x19277b0
bool sbattleSetPathMotion(SBTLSKLHIT_PACDATAWORK *pac, s32 point) {
  void *BpData;
  s32 hitmdl_serialID;
  s32 v8;
  u32 v9;
  SBDEBUG_PATHDATA *v11;
  dds3Basic_t *v13;
  void *workdata;
  evtUnitHandle_t *klass;
  dds3ModelHandle_t *Model;
  dds3ModelHandle_t *p_path_hModel;
  dds3PoseSet_t *poseset;
  sdfVector4_t *p_scl;
  s32 path_motionno;
  dds3ModelHandle_t *v30;
  u16 v36;
  dds3Basic_t *pBasic;

  BpData = pac->BpData;
  hitmdl_serialID = wk->hitmdl_serialID;
  mdlPackDecode(7u, hitmdl_serialID, 257, BpData, 0);
  v8 = wk->hitmdl_serialID;
  v9 = UnitRegist(7u, v8);
  v11 = sbtldbwk->ef_path[point];
  pBasic = dds3GetActiveScene();
  v13 = dds3SceneBasicSearch(pBasic, v9, 5u);
  v11->path_pBasic = v13;
  workdata = v11->path_pBasic->workdata;
  klass = workdata[2].klass;
  v11->path_hEveUnit = klass;
  Model = v11->path_hEveUnit->Model;
  v11->path_hModel = Model;
  p_path_hModel = &v11->path_hModel;
  v11->path_hEveUnit->Flag |= 0x200000u;
  __asm { FMOV            V0.4S, #1.0 }
  vct_A = _Q0;
  poseset = v11->path_pBasic->poseset;
  p_scl = &poseset->scl;
  *p_scl = vct_A;
  mdlHide(v11->path_hModel);
  mdlSetMotionSpeed(v11->path_hModel, 1.0);
  if (mdlHasMotionEx(v11->path_hModel, 0))
  {
    path_motionno = 0;
    v11->path_motionno = 0;
    v30 = p_path_hModel;
    goto LABEL_26;
  }
  else
  {
    path_motionno = v11->path_motionno;
    v30 = p_path_hModel;
    goto LABEL_26;
  }
LABEL_26:
  mdlSmoothSingleMotion(v30, 0, path_motionno, 0.0, 0.0, 0.0);
  v11->nef_timecnt = 0.0;
  v36 = wk->hitmdl_serialID;
  pac->wk->flg |= 0x1000u;
  wk->hitmdl_serialID = v36 + 1;
  sbattleResetEPLData(sbtldbwk->nef_pagecsr->point);
  return 1;
}

// 0x1927bf0
bool sbattleResetEPLData(s32 i) {
  s64 v4;
  SBTLEFF_EFFTIME *v6;
  f32 fin_time;
  SBDEBUG_TIMEWORK *v9;
  f32 fout_time;
  f32 v11;

  v4 = i;
  if (sbtldbwk->ef_dwk[v4]->hPartsList)
  {
    v6 = sbtldbwk->ef_dtime[v4];
    v6->counter = 0.0;
    fin_time = v6->fin_time;
    v9 = sbtldbwk->ef_dt[sbtldbwk->nef_pagecsr->point];
    v9->alpha = 0.0;
    if (fin_time == 0.0)
    {
      v9->alpha = 128.0;
      v9->in_alpha = 128.0;
      fout_time = v6->fout_time;
      if (fout_time == 0.0)
      {
LABEL_10:
        v11 = 128.0;
LABEL_13:
        v9->out_alpha = v11;
        return 1;
      }
    }
    else
    {
      v9->in_alpha = 128.0 / fin_time;
      fout_time = v6->fout_time;
      if (fout_time == 0.0)
        goto LABEL_10;
    }
    v11 = 128.0 / fout_time;
    goto LABEL_13;
  }
  return 1;
}

// 0x1927d10
s32 sbattleCreateUnit(s16 minor, SBTLUNIT_SIDE side, const sdfVector4_t *pos) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  SBTLUNIT_WORK *Unit;
  s32 v12;
  SBTLACTION_WORK *actwk;
  sdatUnitWork_t *para;
  f32 *p_x;
  sdfVector4_t *p_pos;
  sdatUnitWork_t *v22;
  s32 devilid;
  DEVILDATA_WORK *DevilData;
  s32 minorno;
  VISUALDATA_WORK *VisualData;
  MOTIONDATA_WORK *MotionVisualData;
  s32 status;
  s32 v30;
  sdatUnitWork_t *v31;
  s64 v33;
  sdfVector4_t *p_rot;
  sdfVector4_t *p_rot_p;
  sdatUnitWork_t *v38;
  struct sdfVector4_t v39;
  SBTLACTAI_WORK *actaiwk;
  u32 v41;
  SKLID *haveskill;
  f32 rot_spd;
  sdatParaWork_t *now;
  SKLID *v45;

  w = pos->w;
  z = pos->z;
  y = pos->y;
  x = pos->x;
  Unit = sBtlCreateUnit(1u, minor, 1);
  v12 = sBtlEntryUnitList(wk->UnitMng, Unit);
  actwk = Unit->actwk;
  Unit->ListID = v12;
  actwk->status = 0;
  Unit->color = -2139062144;
  sBtlSetFade(Unit, 1, 0, 0, 64);
  para = Unit->para;
  Unit->major = 1;
  Unit->minor = minor;
  para->devilid = minor;
  p_x = &vf00.x;
  p_x[4] = x;
  p_x[5] = y;
  p_x[6] = z;
  p_x[7] = w;
  p_pos = &Unit->pos;
  v22 = Unit->para;
  Unit->side = side;
  *p_pos = vct_A;
  devilid = v22->devilid;
  DevilData = sBtlGetDevilData(devilid, -1);
  minorno = DevilData->minorno;
  VisualData = sBtlGetVisualData(1u, minorno);
  MotionVisualData = sBtlGetMotionVisualData(1u, DevilData->minorno, 0);
  Unit->bunriid = DevilData->bunriid;
  Unit->aisyoid = DevilData->aishou;
  if (DevilData->minorno_d)
  {
    Unit->minor_d = DevilData->minorno_d;
    status = Unit->status | 0x40;
  }
  else
  {
    status = Unit->status;
  }
  v30 = DevilData->stflg | status;
  v31 = Unit->para;
  v33 = *(u64 *)&DevilData->str;
  v31->seikaku = DevilData->seikaku;
  Unit->status = v30;
  *(u64 *)&v31->now->str = v33;
  vct_A = (struct sdfVector4_t)xmmword_3CFD5C0;
  p_rot = &Unit->rot;
  *p_rot = vct_A;
  p_rot_p = &Unit->rot_p;
  v38 = Unit->para;
  v39 = vct_A;
  Unit->mv_spd.z = 0.0;
  actaiwk = Unit->actaiwk;
  Unit->mv_rot = 0.0;
  *p_rot_p = v39;
  v39.x = VisualData->mv_spd;
  v41 = actaiwk->status & 0xFFFFFE7F;
  Unit->size = VisualData->size;
  Unit->max_mvspd.z = v39.x;
  haveskill = v38->haveskill;
  v39.x = VisualData->scale;
  rot_spd = VisualData->rot_spd;
  actaiwk->status = v41 | 0x168;
  now = v38->now;
  Unit->scale.x = v39.x;
  Unit->max_mvrot = rot_spd;
  Unit->scale.y = VisualData->scale;
  *(u64 *)&now->hp = *(u64 *)&DevilData->hp;
  v45 = DevilData->haveskill;
  LODWORD(v38) = v45[0];
  Unit->scale.z = VisualData->scale;
  v39.x = VisualData->scale;
  haveskill[2] = (s32)v38;
  LODWORD(v38) = v45[1];
  Unit->scale.w = v39.x;
  v39.x = VisualData->hit_area_r;
  haveskill[3] = (s32)v38;
  LODWORD(v38) = v45[2];
  actaiwk->hit_area_r = v39.x;
  v39.x = MotionVisualData->m_mv_area_r;
  haveskill[4] = (s32)v38;
  actaiwk->priv_area_r = v39.x;
  *(u64 *)&actaiwk->frid_area_r = *(u64 *)&DevilData->frid_area_r;
  haveskill[5] = v45[3];
  if ((side & 2) != 0)
  {
    ++wk->enemy_num;
  }
  return Unit->ListID;
}

// 0x1918fb0
bool sbattleSetPreViewModel(void) {
  void *v1;
  u32 prev_gstat;
  SBTLDEBUG_WORK *v6;
  s32 v7;
  s32 prev_setcnt;
  s32 *targetID;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 v13;
  SBTLUNIT_WORK *v14;
  s64 v16;
  SBTLUNIT_LISTWORK *v18;
  u32 v19;
  SBTLUNIT_WORK *pUnit;
  s32 acterID;
  SBTLUNIT_WORK *v23;
  SBTLACTAI_WORK *actaiwk;
  f32 *v27;
  f32 v28;
  f32 v29;
  s64 v30;
  sdfVector4_t v32;
  sdfVector4_t v33;

  v1 = NewSpecific(f32, 0x12u);
  InitializeArray_55364416(v1, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__93F99F2A3E012E18E3784C0AF3F6365D9893E185F58B2BB9B28E20DBF8F3EDC5, 0);
  prev_gstat = sbtldbwk->prev_gstat;
  if (prev_gstat > 3)
    return 0;
  switch (prev_gstat)
  {
    case 0u:
      if (sbtldbwk->acterID != -1)
      {
        goto LABEL_11;
      }
      v32.w = 1.0;
      v32.x = 0.0;
      v32.z = -600.0;
      v32.y = 0.0;
      sbtldbwk->acterID = sbattleCreateUnit(1, 1, v32);
LABEL_11:
      v6 = sbtldbwk;
      v7 = v6->prev_gstat;
      v6->prev_setcnt = 0;
LABEL_19:
      v6->prev_gstat = v7 + 1;
      return 0;
    case 1u:
      prev_setcnt = sbtldbwk->prev_setcnt;
      if (prev_setcnt < sbtldbwk->prev_cnt)
      {
        targetID = sbtldbwk->targetID;
        if (targetID[prev_setcnt] != -1)
        {
LABEL_18:
          v6 = sbtldbwk;
          v7 = v6->prev_gstat;
          goto LABEL_19;
        }
        v27 = (&v1->klass + prev_setcnt);
        v28 = v27[8];
        v29 = v27[9];
        v30 = prev_setcnt;
        v33.w = 1.0;
        v33.y = 0.0;
        v33.x = v28;
        v33.z = v29;
        targetID[v30] = sbattleCreateUnit(96, 2, v33);
        goto LABEL_18;
      }
      sbtldbwk->prev_gstat += 2;
      return 0;
    case 2u:
      UnitMng = wk->UnitMng;
      v13 = sbtldbwk->targetID[sbtldbwk->prev_setcnt];
      v14 = sBtlSearchUnit_ID(UnitMng, v13);
      if (v14->mode != 8)
        return 0;
      v14->damagecnt = 0;
      *(u64 *)&v14->damage_serialID = -1;
      *(int32x2_t *)&sbtldbwk->prev_setcnt = vadd_s32(*(int32x2_t *)&sbtldbwk->prev_setcnt, (int32x2_t)0xFFFFFFFF00000001LL);
      return 0;
    case 3u:
      v16 = 0;
      while (2)
      {
        v18 = wk->UnitMng;
        if (v16 < v18->number)
        {
          if (v19)
          {
            pUnit = v18->pUnitL[v16]->pUnit;
            if (!pUnit)
              goto LABEL_29;
          }
          else
          {
            pUnit = wk->UnitMng->pUnitL[v16]->pUnit;
            if (!pUnit)
            {
LABEL_29:
              ++v16;
              continue;
            }
          }
          if (pUnit->mode == 8)
          {
            pUnit->damagecnt = 0;
            *(u64 *)&pUnit->damage_serialID = -1;
          }
          goto LABEL_29;
        }
        break;
      }
      if (v19)
      {
        goto LABEL_41;
      }
      else
      {
        v18 = wk->UnitMng;
        goto LABEL_41;
      }
LABEL_41:
      acterID = sbtldbwk->acterID;
      v23 = sBtlSearchUnit_ID(v18, acterID);
      if (v23->mode != 8)
        return 0;
      v23->damagecnt = 0;
      actaiwk = v23->actaiwk;
      *(u64 *)&v23->damage_serialID = -1;
      actaiwk->targetID = -1;
      sbtldbwk->prev_gstat = 0;
      return 1;
    default:
      return 0;
  }
}

// 0x19184b0
bool sbattleDeletePrevModel(void) {
  SBTLUNIT_LISTWORK *UnitMng;
  s32 acterID;
  SBTLUNIT_WORK *v6;
  char v7;
  s64 i;
  SBTLUNIT_LISTWORK *v9;
  s32 v10;
  SBTLUNIT_WORK *v11;
  bool v12;

  if (sbtldbwk->acterID == -1)
    goto LABEL_17;
  UnitMng = wk->UnitMng;
  acterID = sbtldbwk->acterID;
  v6 = sBtlSearchUnit_ID(UnitMng, acterID);
  if (!v6)
  {
    sbtldbwk->acterID = -1;
LABEL_17:
    v7 = 1;
    goto LABEL_18;
  }
  v6->mode = 9;
  v7 = 0;
LABEL_18:
  for (i = 0; i != 9; ++i)
  {
    while (1)
    {
      if (sbtldbwk->targetID[i] == -1)
        break;
      v9 = wk->UnitMng;
      v10 = sbtldbwk->targetID[i];
      v11 = sBtlSearchUnit_ID(v9, v10);
      if (!v11)
      {
        sbtldbwk->targetID[i] = -1;
        break;
      }
      v7 = 0;
      v12 = 0;
      v11->mode = 9;
      if (i++ == 8)
        return v12;
    }
  }
  if ((v7 & 1) == 0)
    return 0;
  sbtldbwk->status &= ~0x200000u;
  return 1;
}

// 0x1920910
bool sbattleAddPrev(SBDEBUG_CSRWORK *swk, s32 prev, s32 motion) {
  s32 MotionNum;
  s32 v11;
  bool v12;
  SBTLDEBUG_WORK *v14;
  s32 v15;

  MotionNum = sbattleGetMotionNum(sbtldbwk->acterID);
  if (swk->point == swk->maxp + prev)
  {
    v11 = sbtldbwk->prev_cnt + 1;
    v12 = sbtldbwk->prev_cnt - 9 < 0;
    sbtldbwk->prev_cnt = v11;
    if (v12 == __OFSUB__(v11, 10))
    {
      sbtldbwk->prev_cnt = 0;
    }
  }
  if (swk->point == swk->maxp + motion)
  {
    v14 = sbtldbwk;
    v15 = v14->prev_motionno + 1;
    v14->prev_motionno = v15;
    if (v15 >= MotionNum)
    {
      v14 = sbtldbwk;
      v14->prev_motionno = 0;
    }
  }
  return 1;
}

// 0x1920a60
bool sbattleDecPrev(SBDEBUG_CSRWORK *swk, s32 prev, s32 motion) {
  s32 MotionNum;
  s32 v11;
  SBTLDEBUG_WORK *v13;
  s32 v14;

  MotionNum = sbattleGetMotionNum(sbtldbwk->acterID);
  if (swk->point == swk->maxp + prev)
  {
    v11 = sbtldbwk->prev_cnt - 1;
    sbtldbwk->prev_cnt = v11;
    if (v11 >= 0)
      goto LABEL_8;
    sbtldbwk->prev_cnt = 9;
    if (swk->point != swk->maxp + motion)
      return 1;
    goto LABEL_9;
  }
LABEL_8:
  if (swk->point != swk->maxp + motion)
    return 1;
LABEL_9:
  v13 = sbtldbwk;
  v14 = v13->prev_motionno - 1;
  v13->prev_motionno = v14;
  if (v14 >= 0)
    return 1;
  v13 = sbtldbwk;
  v13->prev_motionno = MotionNum - 1;
  return 1;
}

// 0x191a320
bool sbattleClearEffHitData(s32 id) {
  SBTLSKLHIT_PACDATAWORK *ef_wk;
  SBTLSKLHIT_PACDATAWORK *v5;
  Il2CppClass **v6;

  ef_wk = sbtldbwk->ef_wk;
  v5 = Allocate(SBTLSKLHIT_PACDATAWORK);
  _ctor(v5, 0);
  v6 = &ef_wk->obj.klass + id;
  v6[4] = v5;
  sbtldbwk->ef_wkflg[id] = 0;
  return 1;
}

// 0x191dea0
void sbattleDeleteEPLData(s32 id) {
  ;
}

// 0x1928230
void sbattleDeletePathData(s32 id) {
  dds3Basic_t *path_pBasic;
  s64 v6;
  SBDEBUG_PATHDATA *v7;
  SBDEBUG_PATHDATA *v8;
  SBDEBUG_PATHDATA *ef_path;
  SBTLSKILLHIT_TBL *wk;

  path_pBasic = sbtldbwk->ef_path[id]->path_pBasic;
  if (path_pBasic)
  {
    dds3SceneBasicDelete(path_pBasic);
    v6 = id;
    v7 = sbtldbwk->ef_path[v6];
    v7->path_pBasic = 0;
    v8 = sbtldbwk->ef_path[v6];
    v8->path_hEveUnit = 0;
    ef_path = sbtldbwk->ef_path;
    wk = sbtldbwk->ef_wk[v6]->wk;
    ef_path[v6]->nef_movetype = 0;
    wk->flg &= ~0x1000u;
    return;
  }
}

// 0x1918900
s32 sBtlDebug_ChangeModel(void) {
  SBDEBUG_CSRWORK *unitcsr;
  s32 v4;
  SBTLDEBUG_WORK *v5;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 acterID;
  SBTLUNIT_WORK *v10;
  SBTLUNIT_WORK *v11;
  dds3Basic_t *pBasic;
  SBTLDEBUG_WORK *v14;
  SBTLUNIT_LISTWORK *v16;
  s32 v17;
  SBTLUNIT_WORK *v18;
  SBTLUNIT_LISTWORK *v22;
  s32 v23;
  SBTLUNIT_WORK *v24;
  s32 mode;
  SBTLUNIT_WORK *v27;
  s32 result;
  dds3Basic_t *pUnitBasic;
  SBTLDEBUG_WORK *v32;
  s32 v33;
  s32 point;
  s32 v35;
  s32 v36;
  s32 v37;
  s32 maxp;
  bool v39;
  s32 v40;
  SBTLDEBUG_WORK *v43;

  unitcsr = sbtldbwk->unitcsr;
  switch (sbtldbwk->unitmode)
  {
    case 1:
      v4 = 2;
      goto LABEL_70;
    case 2:
      if ((sbtldbwk->status & 0x200000) != 0)
      {
        if (sbtldbwk->acterID != -1)
        {
          sbattleDeletePrevModel();
          v5 = sbtldbwk;
          v5->prev_cnt = 0;
          v5->prev_gstat = 0;
        }
      }
      goto LABEL_21;
    case 3:
      if (!sbattleSetPreViewModel())
        goto LABEL_57;
LABEL_21:
      goto LABEL_69;
    case 4:
      UnitMng = wk->UnitMng;
      acterID = sbtldbwk->acterID;
      v10 = sBtlSearchUnit_ID(UnitMng, acterID);
      if (!v10)
        return 1;
      v11 = v10;
      sBtlDeleteUnit_UnWork(v11);
      pBasic = v11->pBasic;
      v14 = sbtldbwk;
      v14->pUnitBasic = pBasic;
      v11->mode = 0;
LABEL_68:
LABEL_69:
      v4 = sbtldbwk->unitmode + 1;
LABEL_70:
      sbtldbwk->unitmode = v4;
      if (CHECK_TRIG(4096, 1))
      {
LABEL_58:
        result = 0;
        sbtldbwk->unitmode = 1;
      }
      else
      {
LABEL_71:
        if (CHECK_TRIG(4097, 1))
        {
          return 2;
        }
        else if (CHECK_REP(4100, 1))
        {
          result = 0;
          v33 = unitcsr->point - 1;
          unitcsr->point = v33;
          if (v33 < 0)
            unitcsr->point = unitcsr->maxp - 1;
        }
        else if (CHECK_REP(4101, 1))
        {
          point = unitcsr->point;
          result = 0;
          if (point + 1 < unitcsr->maxp)
            v35 = point + 1;
          else
            v35 = 0;
          unitcsr->point = v35;
        }
        else if (CHECK_REP(4105, 1))
        {
          v36 = unitcsr->point;
          result = 0;
          unitcsr->point = v36 - 10;
          if (v36 - 10 < 0)
            unitcsr->point = v36 + unitcsr->maxp - 11;
        }
        else if (CHECK_REP(4108, 1))
        {
          result = 0;
          v37 = unitcsr->point + 10;
          maxp = unitcsr->maxp;
          unitcsr->point = v37;
          v39 = __OFSUB__(v37, maxp);
          v40 = v37 - maxp;
          if (v40 < 0 == v39)
            unitcsr->point = v40;
        }
        else if (CHECK_TRIG(4103, 1) || CHECK_TRIG(4102, 1))
        {
          v43 = sbtldbwk;
          if (v43->unitmajor)
          {
            v43 = sbtldbwk;
            v43->unitmajor = 0;
            return 0;
          }
          else
          {
            v43 = sbtldbwk;
            v43->unitmajor = 1;
            return 0;
          }
        }
        else
        {
          return 0;
        }
      }
      return result;
    case 5:
      v16 = wk->UnitMng;
      v17 = sbtldbwk->acterID;
      v18 = sBtlSearchUnit_ID(v16, v17);
      sbattleSetModelData(v18, sbtldbwk->unitmajor, unitcsr->point);
      v18->gstat = 0;
      v18->mode = 2;
      sBtlDebug_SetVisualData(v18);
      goto LABEL_68;
    case 6:
      v22 = wk->UnitMng;
      v23 = sbtldbwk->acterID;
      v24 = sBtlSearchUnit_ID(v22, v23);
      mode = v24->mode;
      if (mode == 8 || mode == 4)
      {
        v27 = v24;
        ++sbtldbwk->unitmode;
        v27->mode = 8;
      }
      goto LABEL_57;
    case 7:
      pUnitBasic = sbtldbwk->pUnitBasic;
      dds3SceneBasicDelete(pUnitBasic);
      v32 = sbtldbwk;
      v32->pUnitBasic = 0;
      sbtldbwk->unitmode = 0;
      return 1;
    default:
LABEL_57:
      if (CHECK_TRIG(4096, 1))
        goto LABEL_58;
      goto LABEL_71;
  }
}

// 0x190b1d0
void sbattleSetModelData(SBTLUNIT_WORK *unit, MODELTYPE major, s32 point) {
  sdatUnitWork_t *para;
  s32 v9;

  para = unit->para;
  unit->major = major;
  unit->minor = point;
  para->devilid = point;
  sBtlGetDevilData((s16)point, -1);
  if (unit->major)
  {
    if (IsENEMYOFFSET(unit->para->devilid))
      v9 = 2;
    else
      v9 = 1;
  }
  else
  {
    v9 = 129;
  }
  unit->side = v9;
  Init(unit, 0);
  sBtlInitUnitSE(unit);
}

// 0x191b450
void sbattleSetEffHitPara_S(SBTLSKILLHIT_TBL *hwk, SBDEBUG_CSRWORK *wk, s32 flg) {
  s32 *p_starttime;
  s32 v8;
  u32 v9;
  s32 starttime;

  if ((u32)flg > 5)
  {
    starttime = hwk->starttime;
    p_starttime = &hwk->starttime;
    *p_starttime = starttime;
LABEL_7:
  }
  else
  {
    v8 = hwk->starttime;
    p_starttime = &hwk->starttime;
    *p_starttime = v8 + dword_3E608D0[flg];
    if (!v9)
      goto LABEL_7;
  }
  LimitRange(p_starttime, 0, 1000);
}

// 0x191cab0
bool sbattleSetEffHitPara(SBTLSKILLHIT_TBL *hwk, SBDEBUG_CSRWORK *wk, s32 flg) {
  SBTLEFF_EFFTIME *v7;
  s64 v10;
  s64 v11;
  s32 v12;
  f32 v13;
  f32 *v14;
  SBTLSKILLHIT_POSWORK *start;
  SBTLSKILLIDOU_WORK *apos1;
  s32 nef_poseture;
  f32 v18;
  s32 type;
  f32 *p_area_r;
  f32 area_r;
  f32 v22;
  f32 v23;
  f32 v24;
  f32 area_r2;
  SBTLDMG_CYLINDERWORK *v26;
  f32 *p_height;
  f32 height;
  s32 v30;
  f32 *v31;
  f32 v32;
  s32 *p_lifetime;
  s32 lifetime;
  f32 v36;
  f32 shatei;
  f32 sokudo;
  f32 v40;
  f32 *p_homingpara;
  f32 homingpara;
  s32 v44;
  u8 v45;
  s32 v46;
  s8 *p_takasa;
  s8 takasa;
  s8 v50;
  s8 *v51;
  s32 v52;
  s8 *p_muki;
  s8 muki;
  SBDEBUG_CSRWORK *nef_eplmenucsr;
  f32 *v57;
  f32 v58;
  f32 v59;
  f32 v60;
  u32 v62;
  s32 v63;
  f32 v64;
  f32 v65;
  SBTLDMG_CYLINDERWORK *cy;
  f32 v71;
  SBTLDMG_CYLINDERWORK *v73;
  f32 v74;
  s32 v75;
  SBTLDEBUG_WORK *v76;
  s32 v77;
  s32 v78;
  s32 ef_stendp;
  s32 v80;
  s32 v81;
  s32 v82;
  f32 v83;
  f32 v84;
  f32 v85;
  s32 v86;
  s32 x[2];

  *(u64 *)x = 0;
  v86 = 0;
  v7 = Allocate(SBTLEFF_EFFTIME);
  _ctor(v7, 0);
  v10 = (s64)sbtldbwk->ef_dtime + 8 * sbtldbwk->nef_pagecsr->point;
  if ((u32)flg > 5)
  {
    v12 = 0;
    v13 = 0.0;
    v14 = *(f32 **)(v10 + 32);
  }
  else
  {
    v11 = flg;
    v12 = dword_3E608D0[v11];
    v13 = *(f32 *)((char *)&unk_3E608E8 + v11 * 4);
    v14 = *(f32 **)(v10 + 32);
  }
  switch (sbtldbwk->ef_stendp)
  {
    case 0:
      start = hwk->start;
      apos1 = 0;
      goto LABEL_16;
    case 1:
      apos1 = hwk->apos1;
      start = 0;
      goto LABEL_16;
    case 2:
      apos1 = hwk->apos2;
      start = 0;
      goto LABEL_16;
    case 3:
      start = hwk->end;
      apos1 = 0;
      goto LABEL_16;
    default:
      apos1 = 0;
      start = 0;
      if (sbtldbwk->ef_mode != 3)
        goto LABEL_29;
LABEL_17:
      nef_poseture = sbtldbwk->nef_poseture;
      if (nef_poseture != 2)
      {
        if (nef_poseture == 1)
        {
          v24 = v13 + hwk->y;
          if (v24 <= -2000.0)
            v24 = -2000.0;
          hwk->y = v24;
          if (v24 >= 2000.0)
            hwk->y = 2000.0;
        }
        else if (!nef_poseture)
        {
          v18 = v13 + hwk->x;
          if (v18 <= -2000.0)
            v18 = -2000.0;
          hwk->x = v18;
          if (v18 >= 2000.0)
            hwk->x = 2000.0;
        }
        return 1;
      }
      v23 = v13 + hwk->z;
      if (v23 <= -2000.0)
        v23 = -2000.0;
      hwk->z = v23;
      if (v23 >= 2000.0)
        hwk->z = 2000.0;
      return 1;
LABEL_16:
      if (sbtldbwk->ef_mode == 3)
        goto LABEL_17;
LABEL_29:
      type = hwk->type;
      if (type != 2)
      {
        if (type == 1)
        {
          switch (wk->point)
          {
            case 0:
              goto LABEL_46;
            case 1:
              goto LABEL_132;
            case 2:
              goto LABEL_49;
            case 3:
              goto LABEL_52;
            case 4:
              goto LABEL_56;
            case 5:
              goto LABEL_59;
            case 6:
              goto LABEL_62;
            case 7:
              goto LABEL_137;
            case 8:
              goto LABEL_65;
            case 9:
              goto LABEL_69;
            case 0xA:
              goto LABEL_73;
            case 0xC:
              goto LABEL_77;
            case 0xD:
              goto LABEL_80;
            case 0xE:
              goto LABEL_84;
            case 0xF:
              ef_stendp = sbtldbwk->ef_stendp;
              if (ef_stendp)
              {
                ef_stendp = sbtldbwk->ef_stendp;
                if (ef_stendp != 3)
                  goto LABEL_181;
              }
              v80 = start->iti_no + v12;
              start->iti_no = v80;
              x[0] = v80;
              LimitRange(x, 0, 999);
              start->iti_no = x[0];
              break;
            case 0x10:
              goto LABEL_92;
            case 0x11:
              goto LABEL_101;
            case 0x12:
              goto LABEL_111;
            case 0x13:
              goto LABEL_114;
            case 0x14:
              goto LABEL_115;
            case 0x15:
              goto LABEL_118;
            case 0x16:
              goto LABEL_119;
            case 0x17:
              goto LABEL_126;
            case 0x18:
              goto LABEL_129;
            default:
              return 1;
          }
        }
        else if (!hwk->type)
        {
          switch (wk->point)
          {
            case 0:
              goto LABEL_46;
            case 1:
              area_r = hwk->area_r;
              p_area_r = &hwk->area_r;
              v22 = area_r;
              goto LABEL_66;
            case 2:
              goto LABEL_49;
            case 3:
              goto LABEL_52;
            case 4:
              goto LABEL_56;
            case 5:
              goto LABEL_59;
            case 6:
              goto LABEL_62;
            case 7:
              goto LABEL_65;
            case 8:
              goto LABEL_69;
            case 9:
              goto LABEL_73;
            case 0xB:
              goto LABEL_77;
            case 0xC:
              goto LABEL_80;
            case 0xD:
              goto LABEL_84;
            case 0xE:
              v77 = sbtldbwk->ef_stendp;
              if (v77)
              {
                v77 = sbtldbwk->ef_stendp;
                if (v77 != 3)
                  goto LABEL_181;
              }
              v78 = start->iti_no + v12;
              start->iti_no = v78;
              x[1] = v78;
              LimitRange(&x[1], 0, 999);
              start->iti_no = x[1];
              break;
            case 0xF:
              goto LABEL_92;
            case 0x10:
              goto LABEL_101;
            case 0x11:
              goto LABEL_111;
            case 0x12:
              goto LABEL_114;
            case 0x13:
              goto LABEL_115;
            case 0x14:
              goto LABEL_118;
            case 0x15:
              goto LABEL_119;
            case 0x16:
              goto LABEL_126;
            case 0x17:
              goto LABEL_129;
            default:
              return 1;
          }
        }
        return 1;
      }
      switch (wk->point)
      {
        case 0:
LABEL_46:
          sbtldbwk->ef_mode = 1;
          return 1;
        case 1:
LABEL_132:
          hwk->area_r = v13 + hwk->area_r;
          LimitRange_5(&hwk->area_r, 0, 4000);
          cy = hwk->cy;
          v30 = 4000;
          v71 = cy->area_r;
          v31 = &cy->area_r;
          *v31 = v13 + v71;
          goto LABEL_135;
        case 2:
          area_r2 = hwk->area_r2;
          p_area_r = &hwk->area_r2;
          v22 = area_r2;
          goto LABEL_66;
        case 3:
LABEL_49:
          v26 = hwk->cy;
          height = v26->height;
          p_height = &v26->height;
          *p_height = v13 + height;
          v30 = 4000;
          v31 = p_height;
          goto LABEL_135;
        case 4:
LABEL_52:
          v32 = v13 + hwk->rad;
          if (v32 >= 1.0)
            v32 = 1.0;
          hwk->rad = v32;
          if (v32 <= -1.0)
            hwk->rad = -1.0;
          return 1;
        case 5:
LABEL_56:
          lifetime = hwk->lifetime;
          p_lifetime = &hwk->lifetime;
          *p_lifetime = lifetime + v12;
          LimitRange(p_lifetime, 0, 3600);
          return 1;
        case 6:
LABEL_59:
          sbtldbwk->ef_mode = 3;
          return 1;
        case 7:
LABEL_62:
          v36 = v13 + hwk->dir;
          hwk->dir = v36;
          if (v36 >= 360.0)
          {
            hwk->dir = 0.0;
          }
          else if (v36 < 0.0)
          {
            hwk->dir = 360.0;
          }
          return 1;
        case 8:
LABEL_137:
          v73 = hwk->cy;
          v74 = v13 + v73->xrad;
          v73->xrad = v74;
          if (v74 >= 360.0)
          {
            v73->xrad = 0.0;
          }
          else if (v74 < 0.0)
          {
            v73->xrad = 360.0;
          }
          return 1;
        case 9:
LABEL_65:
          shatei = hwk->shatei;
          p_area_r = &hwk->shatei;
          v22 = shatei;
LABEL_66:
          *p_area_r = v13 + v22;
          v30 = 4000;
          goto LABEL_72;
        case 0xA:
LABEL_69:
          sokudo = hwk->sokudo;
          p_area_r = &hwk->sokudo;
          *p_area_r = v13 + sokudo;
          v30 = 1000;
LABEL_72:
          v31 = p_area_r;
          goto LABEL_135;
        case 0xB:
LABEL_73:
          v40 = v13 + hwk->kasokudo;
          if (v40 <= -200.0)
            v40 = -200.0;
          hwk->kasokudo = v40;
          if (v40 >= 200.0)
            hwk->kasokudo = 200.0;
          return 1;
        case 0xD:
LABEL_77:
          homingpara = hwk->homingpara;
          p_homingpara = &hwk->homingpara;
          *p_homingpara = v13 + homingpara;
          v31 = p_homingpara;
          v30 = 1;
LABEL_135:
          LimitRange_5(v31, 0, v30);
          return 1;
        case 0xE:
LABEL_80:
          if ((hwk->flg & 0x100) == 0)
          {
            sbtldbwk->ef_stendp = 0;
            return 1;
          }
          v75 = sbtldbwk->ef_stendp + v12;
          sbtldbwk->ef_stendp = v75;
          if (v75 >= 4)
          {
            sbtldbwk->ef_stendp = 0;
LABEL_145:
            v76 = sbtldbwk;
            if ((v76->ef_stendp & 0x80000000) == 0)
              return 1;
            goto LABEL_193;
          }
          {
            goto LABEL_145;
          }
          v76 = sbtldbwk;
          if ((v76->ef_stendp & 0x80000000) == 0)
            return 1;
LABEL_193:
          v76 = sbtldbwk;
          v76->ef_stendp = 3;
          break;
        case 0xF:
LABEL_84:
          v44 = sbtldbwk->ef_stendp;
          if (!v44)
            goto LABEL_90;
          v44 = sbtldbwk->ef_stendp;
          if (v44 != 3)
          {
            v83 = v13 + apos1->per;
            if (v83 >= 1.0)
              v83 = 1.0;
            apos1->per = v83;
            if (v83 <= -1.0)
              apos1->per = -1.0;
          }
          else
          {
LABEL_90:
            v45 = start->iti + v12;
            start->iti = v45;
            if (v45 == 0xFF)
            {
              start->iti = 17;
            }
            else if (v45 >= 0x12u)
            {
              start->iti = 0;
            }
          }
          return 1;
        case 0x10:
          v81 = sbtldbwk->ef_stendp;
          if (!v81)
            goto LABEL_173;
          v81 = sbtldbwk->ef_stendp;
          if (v81 != 3)
          {
LABEL_181:
            v84 = v13 + apos1->w;
            if (v84 >= 1000.0)
              v84 = 1000.0;
            apos1->w = v84;
            if (v84 <= -1000.0)
              apos1->w = -1000.0;
          }
          else
          {
LABEL_173:
            v82 = start->iti_no + v12;
            start->iti_no = v82;
            v86 = v82;
            LimitRange(&v86, 0, 999);
            start->iti_no = v86;
          }
          return 1;
        case 0x11:
LABEL_92:
          v46 = sbtldbwk->ef_stendp;
          if (!v46)
            goto LABEL_98;
          v46 = sbtldbwk->ef_stendp;
          if (v46 != 3)
          {
            v85 = v13 + apos1->h;
            if (v85 >= 1000.0)
              v85 = 1000.0;
            apos1->h = v85;
            if (v85 <= -1000.0)
              apos1->h = -1000.0;
          }
          else
          {
LABEL_98:
            takasa = start->takasa;
            p_takasa = &start->takasa;
            *p_takasa = takasa + v12;
            v50 = 5;
            v51 = p_takasa;
LABEL_110:
            LimitRange_4(v51, 0, v50);
          }
          return 1;
        case 0x12:
LABEL_101:
          v52 = sbtldbwk->ef_stendp;
          if (v52)
          {
            v52 = sbtldbwk->ef_stendp;
            if (v52 != 3)
              return 1;
          }
          muki = start->muki;
          p_muki = &start->muki;
          *p_muki = muki + v12;
          v51 = p_muki;
          v50 = 8;
          goto LABEL_110;
        case 0x13:
LABEL_111:
          sbtldbwk->nef_mode = 14;
          nef_eplmenucsr = sbtldbwk->nef_eplmenucsr;
          nef_eplmenucsr->point = 0;
          nef_eplmenucsr->maxp = 2;
          return 1;
        case 0x14:
LABEL_114:
          v58 = v14[5];
          v57 = v14 + 5;
          v59 = v58;
          goto LABEL_120;
        case 0x15:
LABEL_115:
          v60 = v14[6];
          v57 = v14 + 6;
          *v57 = v60 + (f32)v12;
          if (!v62)
          v63 = 600;
          goto LABEL_123;
        case 0x16:
LABEL_118:
          v64 = v14[7];
          v57 = v14 + 7;
          v59 = v64;
          goto LABEL_120;
        case 0x17:
LABEL_119:
          v65 = v14[8];
          v57 = v14 + 8;
          v59 = v65;
LABEL_120:
          *v57 = v59 + (f32)v12;
          v63 = 300;
LABEL_123:
          LimitRange_5(v57, 0, v63);
          sbattleResetEPLData(sbtldbwk->nef_pagecsr->point);
          return 1;
        case 0x18:
LABEL_126:
          sbtldbwk->ef_mode = 2;
          return 1;
        case 0x19:
LABEL_129:
          sbtldbwk->nef_mode = 10;
          sbtldbwk->nef_pbloadcsr->maxp = sbtldbwk->nef_loadcsr->maxp;
          return 1;
        default:
          return 1;
      }
      return 1;
  }
}

// 0x1922b80
bool sBtlDebug_SetMDLMOVEPara(SBTLSKILLHIT_TBL *hwk, SBDEBUG_CSRWORK *wk, s32 flg) {
  SBTLEFF_EFFTIME *v7;
  s64 v10;
  f32 v11;
  s32 v12;
  u32 point;
  bool result;
  s32 *p_lifetime;
  s32 lifetime;
  f32 *p_sokudo;
  f32 sokudo;
  s32 MotionNum;
  s32 motionno;

  v7 = Allocate(SBTLEFF_EFFTIME);
  _ctor(v7, 0);
  if ((u32)flg > 5)
  {
    v12 = 0;
    v11 = 0.0;
    point = wk->point;
    goto LABEL_9;
  }
  v10 = flg;
  v11 = *(f32 *)((char *)&unk_3E608E8 + v10 * 4);
  v12 = dword_3E608D0[v10];
  point = wk->point;
  if (point > 3)
    return 1;
LABEL_9:
  switch (point)
  {
    case 0u:
      lifetime = hwk->lifetime;
      p_lifetime = &hwk->lifetime;
      *p_lifetime = lifetime + v12;
      LimitRange(p_lifetime, 0, 300);
      return 1;
    case 1u:
      sokudo = hwk->sokudo;
      p_sokudo = &hwk->sokudo;
      *p_sokudo = v11 + sokudo;
      LimitRange_5(p_sokudo, -600, 600);
      return 1;
    case 2u:
      sbattleResetMotionMovePos();
      return 1;
    case 3u:
      hwk->motionno += v12;
      MotionNum = sbattleGetMotionNum(sbtldbwk->acterID);
      motionno = hwk->motionno;
      if (motionno >= MotionNum)
      {
        hwk->motionno = 0;
        result = 1;
      }
      else
      {
        if ((motionno & 0x80000000) == 0)
          return 1;
        hwk->motionno = MotionNum - 1;
        result = 1;
      }
      break;
    default:
      return 1;
  }
  return result;
}

// 0x1918790
s32 sbattleGetMotionNum(s32 id) {
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *v7;
  SBTLUNIT_WORK *v8;
  dds3ModelHandle_t *Model;

  UnitMng = wk->UnitMng;
  v7 = sBtlSearchUnit_ID(UnitMng, id);
  if (!v7)
    return 0;
  v8 = v7;
  if (!sBtlCheckDamageTarget(v8))
    return 0;
  Model = v8->hEveUnit->Model;
  return mdlGetNumOfCut(Model, 0);
}

// 0x191f250
bool sbattleSetMDLHitPara(SBTLSKILLHIT_TBL *hwk, SBDEBUG_CSRWORK *wk, s32 flg) {
  SBTLEFF_EFFTIME *v7;
  s64 v10;
  s32 v11;
  f32 v12;
  SBTLSKILLHIT_POSWORK *start;
  s32 nef_poseture;
  f32 v16;
  s32 type;
  f32 *p_area_r2;
  f32 v19;
  f32 v20;
  f32 v21;
  f32 v22;
  f32 area_r2;
  f32 *p_area_r;
  SBTLDMG_CYLINDERWORK *v26;
  f32 *p_height;
  f32 height;
  f32 v30;
  s32 v31;
  s8 *p_takasa;
  s8 takasa;
  s8 v35;
  s8 *v36;
  s32 v37;
  s8 *p_muki;
  s8 muki;
  f32 v41;
  SBTLDMG_CYLINDERWORK *v42;
  f32 v43;
  s32 MotionNum;
  s32 motionno;
  s32 *p_lifetime;
  s32 v47;
  s32 v49;
  SBTLDMG_CYLINDERWORK *cy;
  f32 area_r;
  s32 v53;
  s32 v54;
  s32 v55;
  s32 v56;
  s32 lifetime;
  s32 ef_stendp;
  s32 v61;
  f32 v62;
  f32 v63;
  s32 v64;
  s32 x[2];

  *(u64 *)x = 0;
  v64 = 0;
  v7 = Allocate(SBTLEFF_EFFTIME);
  _ctor(v7, 0);
  if ((u32)flg <= 5)
  {
    v10 = flg;
    v11 = dword_3E608D0[v10];
    v12 = *(f32 *)((char *)&unk_3E608E8 + v10 * 4);
    start = hwk->start;
    goto LABEL_6;
LABEL_18:
    type = hwk->type;
    if (type == 2)
    {
      switch (wk->point)
      {
        case 0:
LABEL_38:
          sbtldbwk->ef_mode = 1;
          return 1;
        case 1:
LABEL_86:
          hwk->area_r = v12 + hwk->area_r;
          LimitRange_5(&hwk->area_r, 0, 4000);
          cy = hwk->cy;
          area_r = cy->area_r;
          p_area_r = &cy->area_r;
          *p_area_r = v12 + area_r;
          goto LABEL_89;
        case 2:
          area_r2 = hwk->area_r2;
          p_area_r2 = &hwk->area_r2;
          v20 = area_r2;
LABEL_34:
          *p_area_r2 = v12 + v20;
          p_area_r = p_area_r2;
          goto LABEL_89;
        case 3:
LABEL_41:
          v26 = hwk->cy;
          height = v26->height;
          p_height = &v26->height;
          *p_height = v12 + height;
          p_area_r = p_height;
LABEL_89:
          LimitRange_5(p_area_r, 0, 4000);
          return 1;
        case 4:
LABEL_44:
          v30 = v12 + hwk->rad;
          if (v30 >= 1.0)
            v30 = 1.0;
          hwk->rad = v30;
          if (v30 <= -1.0)
            hwk->rad = -1.0;
          return 1;
        case 5:
          lifetime = hwk->lifetime;
          p_lifetime = &hwk->lifetime;
          *p_lifetime = lifetime + v11;
          v49 = 1000;
LABEL_115:
          LimitRange(p_lifetime, 0, v49);
          return 1;
        case 6:
LABEL_48:
          sbtldbwk->ef_mode = 3;
          return 1;
        case 7:
LABEL_72:
          v41 = v12 + hwk->dir;
          hwk->dir = v41;
          if (v41 >= 360.0)
          {
            hwk->dir = 0.0;
          }
          else if (v41 < 0.0)
          {
            hwk->dir = 360.0;
          }
          return 1;
        case 8:
LABEL_75:
          v42 = hwk->cy;
          v43 = v12 + v42->xrad;
          v42->xrad = v43;
          if (v43 >= 360.0)
          {
            v42->xrad = 0.0;
          }
          else if (v43 < 0.0)
          {
            v42->xrad = 360.0;
          }
          return 1;
        case 0xA:
LABEL_51:
          if (start->iti == 1)
          {
            start->iti = 10;
            hwk->flg |= 0x8000u;
          }
          else
          {
            start->iti = 1;
            hwk->flg &= ~0x8000u;
          }
          return 1;
        case 0xB:
          ef_stendp = sbtldbwk->ef_stendp;
          if (!ef_stendp)
            goto LABEL_123;
          ef_stendp = sbtldbwk->ef_stendp;
          if (ef_stendp != 3)
          {
LABEL_130:
            v63 = v12 + -61301800000000.0;
            if ((f32)(v12 + -61301800000000.0) >= 1000.0)
              v63 = 1000.0;
            locret_14 = LODWORD(v63);
            if (v63 <= -1000.0)
              locret_14 = -998637568;
          }
          else
          {
LABEL_123:
            v61 = start->iti_no + v11;
            start->iti_no = v61;
            v64 = v61;
            LimitRange(&v64, 0, 999);
            start->iti_no = v64;
          }
          return 1;
        case 0xC:
LABEL_53:
          v31 = sbtldbwk->ef_stendp;
          if (!v31)
            goto LABEL_59;
          v31 = sbtldbwk->ef_stendp;
          if (v31 != 3)
          {
            v62 = v12 + COERCE_FLOAT((u32)&xmmword_0);
            if ((f32)(v12 + COERCE_FLOAT((u32)&xmmword_0)) >= 1000.0)
              v62 = 1000.0;
            *(f32 *)&off_18 = v62;
            if (v62 <= -1000.0)
              LODWORD(off_18) = -998637568;
          }
          else
          {
LABEL_59:
            takasa = start->takasa;
            p_takasa = &start->takasa;
            *p_takasa = takasa + v11;
            v35 = 5;
            v36 = p_takasa;
LABEL_71:
            LimitRange_4(v36, 0, v35);
          }
          break;
        case 0xD:
LABEL_62:
          v37 = sbtldbwk->ef_stendp;
          if (v37)
          {
            v37 = sbtldbwk->ef_stendp;
            if (v37 != 3)
              return 1;
          }
          muki = start->muki;
          p_muki = &start->muki;
          *p_muki = muki + v11;
          v36 = p_muki;
          v35 = 8;
          goto LABEL_71;
        case 0xE:
LABEL_78:
          hwk->motionno += v11;
          MotionNum = sbattleGetMotionNum(sbtldbwk->acterID);
          motionno = hwk->motionno;
          if (motionno >= MotionNum)
          {
            hwk->motionno = 0;
          }
          else if (motionno < 0)
          {
            hwk->motionno = MotionNum - 1;
          }
          return 1;
        default:
          return 1;
      }
    }
    else if (type == 1)
    {
      switch (wk->point)
      {
        case 0:
          goto LABEL_38;
        case 1:
          goto LABEL_86;
        case 2:
          goto LABEL_41;
        case 3:
          goto LABEL_44;
        case 4:
LABEL_83:
          v47 = hwk->lifetime;
          p_lifetime = &hwk->lifetime;
          *p_lifetime = v47 + v11;
          v49 = 300;
          goto LABEL_115;
        case 5:
          goto LABEL_48;
        case 6:
          goto LABEL_72;
        case 7:
          goto LABEL_75;
        case 9:
          goto LABEL_51;
        case 0xA:
          v55 = sbtldbwk->ef_stendp;
          if (v55)
          {
            v55 = sbtldbwk->ef_stendp;
            if (v55 != 3)
              goto LABEL_130;
          }
          v56 = start->iti_no + v11;
          start->iti_no = v56;
          x[0] = v56;
          LimitRange(x, 0, 999);
          start->iti_no = x[0];
          break;
        case 0xB:
          goto LABEL_53;
        case 0xC:
          goto LABEL_62;
        case 0xD:
          goto LABEL_78;
        default:
          return 1;
      }
    }
    else if (!hwk->type)
    {
      switch (wk->point)
      {
        case 0:
          goto LABEL_38;
        case 1:
          v19 = hwk->area_r;
          p_area_r2 = &hwk->area_r;
          v20 = v19;
          goto LABEL_34;
        case 2:
          goto LABEL_41;
        case 3:
          goto LABEL_44;
        case 4:
          goto LABEL_83;
        case 5:
          goto LABEL_48;
        case 6:
          goto LABEL_72;
        case 7:
          goto LABEL_75;
        case 9:
          goto LABEL_51;
        case 0xA:
          v53 = sbtldbwk->ef_stendp;
          if (v53)
          {
            v53 = sbtldbwk->ef_stendp;
            if (v53 != 3)
              goto LABEL_130;
          }
          v54 = start->iti_no + v11;
          start->iti_no = v54;
          x[1] = v54;
          LimitRange(&x[1], 0, 999);
          start->iti_no = x[1];
          break;
        case 0xB:
          goto LABEL_53;
        case 0xC:
          goto LABEL_62;
        case 0xD:
          goto LABEL_78;
        default:
          return 1;
      }
    }
    return 1;
  }
  v11 = 0;
  v12 = 0.0;
  start = hwk->start;
LABEL_6:
  if (sbtldbwk->ef_mode != 3)
    goto LABEL_18;
  nef_poseture = sbtldbwk->nef_poseture;
  if (nef_poseture != 2)
  {
    if (nef_poseture == 1)
    {
      v22 = v12 + hwk->y;
      if (v22 <= -2000.0)
        v22 = -2000.0;
      hwk->y = v22;
      if (v22 >= 2000.0)
        hwk->y = 2000.0;
    }
    else if (!nef_poseture)
    {
      v16 = v12 + hwk->x;
      if (v16 <= -2000.0)
        v16 = -2000.0;
      hwk->x = v16;
      if (v16 >= 2000.0)
        hwk->x = 2000.0;
    }
    return 1;
  }
  v21 = v12 + hwk->z;
  if (v21 <= -2000.0)
    v21 = -2000.0;
  hwk->z = v21;
  if (v21 >= 2000.0)
    hwk->z = 2000.0;
  return 1;
}

// 0x19283a0
s32 sBtlDebug_DirClose(s32 hDir) {
  return 0;
}

// 0x19283b0
void sbattleSaveMotionMoveData(void) {
  ;
}

// 0x19283c0
void sBtlDebug_SaveEffHit(s8 path, s8 file) {
  ;
}

// 0x191a410
bool sbattleLoadEffHit(char *name, SBDEBUG_FILETYPE filetype) {
  return 0;
}

// 0x191b430
void sBtlDebug_DecordPos(SBTLSKILLHIT_POSWORK *pos) {
  u32 iti;

  iti = pos->iti;
  if (iti >= 9 && iti - 128 <= 8)
    pos->iti = iti - 119;
}

// 0x191b3a0
void sBtlDebug_ChangeDecordPos(SBTLSKILLHIT_POSWORK *pos) {
  void *v3;

  v3 = NewSpecific(byte, 0x12u);
  InitializeArray_55364416(v3, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__E2170EDFF82D1B234EAC7F7E28AF54B98E969BFA23206AF39C3328FB55FAE35F, 0);
  pos->iti = *((u8 *)&v3[2].klass + pos->iti);
}

// 0x190c590
void sbattleSetVisualPara(SBTLUNIT_WORK *unit, SBDEBUG_CSRWORK *wk, s32 flg) {
  s64 v7;
  s32 v8;
  f32 v9;
  VISUALDATA_WORK *vsdata;
  MOTIONDATA_WORK *v13;
  u16 major;
  s32 minor;
  V_POSITION_WORK *nml;
  u32 point;
  SBTLDEBUG_WORK *v19;
  s32 v20;
  SBTLDEBUG_WORK *v21;
  f32 *p_scale;
  f32 scale;
  f32 v24;
  f32 hit_area_r;
  s32 v26;
  f32 *p_x;
  f32 v28;
  f32 v29;
  f32 y;
  f32 z;
  f32 cylinder;
  f32 height;
  s32 v35;
  f32 *v36;
  f32 *p_hp_pos;
  SBTLDEBUG_WORK *v41;
  f32 m_speed;
  f32 *p_rot_spd;
  f32 rot_spd;
  u32 v46;
  f32 mv_spd;
  s32 ListID;
  s32 MotionNum;
  SBTLDEBUG_WORK *v54;
  SBTLDEBUG_WORK *v55;
  f32 *p_e_startrate;
  f32 e_startrate;
  f32 *p_m_stoprate;
  f32 m_stoprate;
  f32 v61;
  f32 v62;
  f32 m_mv_area_r;
  f32 m_hokanrate;
  s32 v66;
  s32 se_rate;
  s32 *p_se_rate;
  s32 x;

  x = 0;
  if ((u32)flg > 7)
  {
    v8 = 0;
    v9 = 0.0;
    goto LABEL_8;
  }
  else
  {
    v7 = 4 * flg;
    v8 = *(u32 *)((char *)&unk_3E607F8 + v7);
    v9 = *(f32 *)((char *)&unk_3E602D8 + v7);
    goto LABEL_8;
  }
LABEL_8:
  vsdata = sbtldbwk->vsdata;
  v13 = vsdata->mwk[sbtldbwk->vs_mtnno];
  if (!sbtldbwk->vs_posp)
  {
    nml = vsdata->nml;
    point = wk->point;
LABEL_14:
    switch (point)
    {
      case 0u:
        v19 = sbtldbwk;
        v20 = v19->vs_shadowflg + v8;
        v19->vs_shadowflg = v20;
        if (v20 >= 6)
        {
          v19 = sbtldbwk;
          v19->vs_shadowflg = 0;
LABEL_19:
          v21 = sbtldbwk;
          if ((v21->vs_shadowflg & 0x80000000) == 0)
            return;
          goto LABEL_97;
        }
        {
          goto LABEL_19;
        }
        v21 = sbtldbwk;
        if ((v21->vs_shadowflg & 0x80000000) == 0)
          return;
LABEL_97:
        v21 = sbtldbwk;
        v21->vs_shadowflg = 5;
        return;
      case 2u:
        scale = vsdata->scale;
        p_scale = &vsdata->scale;
        v24 = scale;
        goto LABEL_53;
      case 3u:
        hit_area_r = vsdata->hit_area_r;
        p_scale = &vsdata->hit_area_r;
        *p_scale = v9 + hit_area_r;
        v26 = 1000;
        goto LABEL_56;
      case 5u:
        v28 = nml->x;
        p_x = &nml->x;
        v29 = v28;
        goto LABEL_30;
      case 6u:
        y = nml->y;
        p_x = &nml->y;
        v29 = y;
        goto LABEL_30;
      case 7u:
        z = nml->z;
        p_x = &nml->z;
        v29 = z;
        goto LABEL_30;
      case 9u:
        cylinder = nml->cylinder;
        p_x = &nml->cylinder;
        v29 = cylinder;
        goto LABEL_30;
      case 0xAu:
        height = nml->height;
        p_x = &nml->height;
        v29 = height;
LABEL_30:
        *p_x = v9 + v29;
        v35 = -5000;
        v26 = 5000;
        v36 = p_x;
        goto LABEL_85;
      case 0xBu:
        p_hp_pos = &vsdata->hp_pos;
        unit->hpPosition.x = v9 + unit->hpPosition.x;
        goto LABEL_47;
      case 0xCu:
        unit->hpPosition.y = v9 + unit->hpPosition.y;
        p_hp_pos = &vsdata->hp_pos.y;
        goto LABEL_47;
      case 0xDu:
        v41 = sbtldbwk;
        if (v41->vs_shildflg)
        {
          v41 = sbtldbwk;
          v41->vs_shildflg = 0;
          unit->weak_shild = 0;
        }
        else
        {
          v41 = sbtldbwk;
          v41->vs_shildflg = 1;
          unit->weak_shild = 1;
        }
        return;
      case 0xEu:
        unit->weak_shild_pos.x = v9 + unit->weak_shild_pos.x;
        p_hp_pos = &vsdata->hp_pos.y;
        goto LABEL_47;
      case 0xFu:
        unit->weak_shild_pos.y = v9 + unit->weak_shild_pos.y;
        p_hp_pos = &vsdata->hp_pos.y;
LABEL_47:
        v35 = -5000;
        v26 = 5000;
        v36 = p_hp_pos;
        goto LABEL_85;
      case 0x10u:
        m_speed = vsdata->m_speed;
        p_scale = &vsdata->m_speed;
        v24 = m_speed;
        goto LABEL_53;
      case 0x11u:
        rot_spd = vsdata->rot_spd;
        p_rot_spd = &vsdata->rot_spd;
        *p_rot_spd = (f32)(v9 * 0.5) + rot_spd;
        if (!v46)
        v36 = p_rot_spd;
        v35 = 0;
        v26 = 1;
        goto LABEL_85;
      case 0x12u:
        mv_spd = vsdata->mv_spd;
        p_scale = &vsdata->mv_spd;
        v24 = mv_spd;
LABEL_53:
        *p_scale = v9 + v24;
        v26 = 100;
LABEL_56:
        v36 = p_scale;
        goto LABEL_84;
      case 0x14u:
        ListID = unit->ListID;
        sbtldbwk->vs_mtnno += v8;
        MotionNum = sbattleGetMotionNum(ListID);
        v54 = sbtldbwk;
        if (v54->vs_mtnno >= MotionNum)
        {
          v54 = sbtldbwk;
          v54->vs_mtnno = 0;
LABEL_61:
          v55 = sbtldbwk;
          if ((v55->vs_mtnno & 0x80000000) == 0)
            return;
          goto LABEL_104;
        }
        {
          goto LABEL_61;
        }
        v55 = sbtldbwk;
        if ((v55->vs_mtnno & 0x80000000) == 0)
          return;
LABEL_104:
        v55 = sbtldbwk;
        v55->vs_mtnno = MotionNum - 1;
        return;
      case 0x15u:
        sbtldbwk->vs_mode = 1;
        return;
      case 0x16u:
        e_startrate = v13->e_startrate;
        p_e_startrate = &v13->e_startrate;
        *p_e_startrate = v9 + e_startrate;
        v26 = 200;
        goto LABEL_83;
      case 0x17u:
        m_stoprate = v13->m_stoprate;
        p_m_stoprate = &v13->m_stoprate;
        *p_m_stoprate = v9 + m_stoprate;
        v35 = -1;
        v26 = 200;
        v36 = p_m_stoprate;
        goto LABEL_85;
      case 0x18u:
        x = v8 + v13->end_motionno;
        LimitRange(&x, 0, 3);
        v13->end_motionno = x;
        return;
      case 0x19u:
        v61 = v13->m_speed;
        p_e_startrate = &v13->m_speed;
        v62 = v61;
        goto LABEL_80;
      case 0x1Au:
        m_mv_area_r = v13->m_mv_area_r;
        p_e_startrate = &v13->m_mv_area_r;
        *p_e_startrate = v9 + m_mv_area_r;
        v26 = 1000;
        goto LABEL_83;
      case 0x1Bu:
        m_hokanrate = v13->m_hokanrate;
        p_e_startrate = &v13->m_hokanrate;
        v62 = m_hokanrate;
LABEL_80:
        *p_e_startrate = v9 + v62;
        v26 = 100;
LABEL_83:
        v36 = p_e_startrate;
LABEL_84:
        v35 = 0;
LABEL_85:
        LimitRange_5(v36, v35, v26);
        return;
      case 0x1Du:
        if (v9 <= 0.01 || v9 >= 1.0)
        {
          se_rate = v13->se_rate;
          if (v9 >= -0.01 || v9 <= -1.0)
            v66 = se_rate + (s32)v9;
          else
            v66 = se_rate - 1;
        }
        else
        {
          v66 = v13->se_rate + 1;
        }
        v13->se_rate = v66;
        p_se_rate = &v13->se_rate;
        LimitRange(p_se_rate, 0, 300);
        return;
      case 0x1Eu:
        return;
      default:
        return;
    }
  }
  major = unit->major;
  minor = unit->minor;
  nml = sBtlGetEffCylinderData(major, minor);
  point = wk->point;
  if (point <= 0x1E)
    goto LABEL_14;
}

// 0x19283e0
bool sBtlDebug_SaveEffCylinderData(SBTLUNIT_WORK *unit) {
  return 1;
}

// 0x19283d0
bool sBtlDebug_SaveMotionData(SBTLUNIT_WORK *unit) {
  return 1;
}

// 0x1911ba0
bool sbattleSBtlDebug_Skill(void) {
  SBTLUNIT_WORK *Unit;
  SBTLUNIT_WORK *v4;
  SBTLDEBUG_WORK *sbtldbwk_local;
  u32 v8;
  SBTLEFF_LISTWORK *effList;
  s32 prev_skillid;
  s32 v13;
  SBTLDEBUG_WORK *v15;
  s32 v16;
  SBTLACTAI_WORK *v17;
  s64 v18;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  dds3ModelHandle_t *hModel;
  SBTLACTAI_WORK *v23;
  SBTLEFF_LISTWORK *v26;
  s32 v29;
  bool EffectData_ID;
  SBTLEFF_LISTWORK *v33;
  s32 v36;
  SBTLEFF_LISTWORK *v38;
  s32 v41;
  bool v42;
  s32 v43;
  SBTLUNIT_LISTWORK *TargetList_Normal;
  SBTLUNIT_LISTWORK *v45;
  SBTLACTAI_WORK *actaiwk;
  s32 v49;
  struct sdfVector4_t pos;

  Unit = sbattleGetUnit(sbtldbwk->mdlslcsr->point);
  if (!Unit)
    return (char)Unit;
  v4 = Unit;
  Unit->mv_spd.z = 0.0;
  Unit->mv_rot = 0.0;
  pos = Unit->pos;
  vct_A = pos;
  sbtldbwk_local = sbtldbwk;
  v8 = sbtldbwk_local->padmode - 1;
  if (v8 > 5)
  {
LABEL_60:
    LOBYTE(Unit) = 1;
    return (char)Unit;
  }
  switch (v8)
  {
    case 0u:
      effList = wk->effList;
      prev_skillid = sbtldbwk->prev_skillid;
      if (sBtlSearchEffect_SAB(effList, prev_skillid, 1u))
        goto LABEL_82;
      v26 = wk->effList;
      v29 = sbtldbwk->prev_skillid;
      if (sBtlSearchEffect_SAB(v26, v29, 2u))
      {
LABEL_82:
        v38 = wk->effList;
        v41 = sbtldbwk->prev_skillid;
        sBtlDeleteEffectData_SkillID(v38, v41);
        goto LABEL_101;
      }
      v33 = wk->effList;
      v36 = sbtldbwk->prev_skillid;
      if (sBtlSearchEffect_SAB(v33, v36, 5u))
        goto LABEL_82;
      if (!sBtlCheckLoadEnd_EffectWork())
        goto LABEL_101;
      v49 = sbtldbwk->prev_skillid;
      if (sBtlForceDelete_EffectWork_ID(v49, 1))
        goto LABEL_116;
LABEL_101:
      LOBYTE(Unit) = 0;
      return (char)Unit;
LABEL_116:
      ++sbtldbwk->padmode;
      LOBYTE(Unit) = 0;
      return (char)Unit;
    case 1u:
      v13 = sbtldbwk_local->prev_skillid;
      if (v13 == 149)
      {
        ++sbtldbwk_local->padmode;
LABEL_92:
        v15 = sbtldbwk;
        if (v15->padmode == 2)
          goto LABEL_101;
        v15 = sbtldbwk;
        v43 = v15->prev_skillid;
        TargetList_Normal = sBtlCreateTargetList_Normal(v4, v43);
        v45 = TargetList_Normal;
        actaiwk = v4->actaiwk;
        if (TargetList_Normal->count < 1)
        {
          actaiwk->targetID = -1;
          goto LABEL_100;
        }
        else
        {
          actaiwk->targetID = TargetList_Normal->pUnitL[0]->pUnit->ListID;
LABEL_100:
          sBtlDeleteUnitList(v45, 0);
          goto LABEL_101;
        }
        goto LABEL_100;
LABEL_73:
        ++sbtldbwk->padmode;
        goto LABEL_92;
      }
      EffectData_ID = sBtlLoadEffectData_ID(v13);
      if (EffectData_ID)
        goto LABEL_71;
      goto LABEL_91;
      if (v42)
      {
LABEL_71:
        goto LABEL_73;
      }
LABEL_91:
      goto LABEL_92;
    case 2u:
      sbtldbwk_local = sbtldbwk;
      v16 = sbtldbwk_local->prev_skillid;
      v4->actwk->use_skillid = v16;
      v17 = v4->actaiwk;
      v17->cmpframe = 0;
      v17->mode = 16;
      v17->frame = 0;
      sBtlSetUseSkill(v4, v16, 0);
      v18 = 0;
      while (2)
      {
        UnitMng = wk->UnitMng;
        if (v18 >= UnitMng->number)
        {
LABEL_57:
          ++sbtldbwk->padmode;
          goto LABEL_60;
        }
        pUnit = UnitMng->pUnitL[v18]->pUnit;
        if (!pUnit)
          goto LABEL_43;
        goto LABEL_9007;
        if (!pUnit)
        {
LABEL_43:
          ++v18;
          continue;
        }
LABEL_9007:
        break;
      }
      if (pUnit->mode == 8)
      {
        pUnit->damagecnt = 0;
        *(u64 *)&pUnit->damage_serialID = -1;
      }
      goto LABEL_43;
    case 3u:
      hModel = v4->hModel;
      if (mdlGetMotionFrame(hModel) < 0)
        goto LABEL_60;
      v23 = v4->actaiwk;
      *(u64 *)&v23->frame = 0;
      v23->mode = 15;
      sBtlCheckMHTData(v4, v4->actwk->use_skillid);
      goto LABEL_57;
    case 4u:
    case 5u:
      sbtldbwk_local = sbtldbwk;
      sbtldbwk_local->padmode = 0;
      goto LABEL_60;
    default:
      goto LABEL_60;
  }
}

// 0x1928400
bool sBtlDebug_UnitPad(dds3PoseSet_t *pUpdatePoseSet, dds3Basic_t *pBasic) {
  SBTLUNIT_WORK *Unit;
  SBTLUNIT_WORK *v6;
  f32 *p_x;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  SBTLDEBUG_WORK *sbtldbwk_local;
  u32 v15;
  SBTLEFF_LISTWORK *effList;
  s32 prev_skillid;
  s32 v20;
  SBTLDEBUG_WORK *v22;
  s32 v23;
  SBTLACTAI_WORK *v24;
  s64 v25;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  dds3ModelHandle_t *hModel;
  SBTLACTAI_WORK *v30;
  bool v32;
  f32 v33;
  f32 v34;
  bool v35;
  bool v36;
  f32 *v39;
  f32 v40;
  f32 v41;
  f32 v42;
  f32 v44;
  f32 v45;
  SBTLDEBUG_WORK *v48;
  s32 v49;
  SBTLUNIT_WORK *v52;
  s32 v53;
  u16 major;
  s32 minor;
  f32 v57;
  f32 v58;
  f32 v59;
  f32 ScreenDir;
  f32 v61;
  s64 v64;
  struct sdfVector4_t v67;
  struct sdfVector4_t v68;
  u32 v70;
  f32 v72;
  f32 v73;
  f32 v74;
  f32 v75;
  f32 v76;
  f32 v78;
  f32 v79;
  f32 Radian;
  SBTLEFF_LISTWORK *v83;
  s32 v86;
  bool EffectData_ID;
  SBTLEFF_LISTWORK *v91;
  s32 v94;
  SBTLEFF_LISTWORK *v96;
  s32 v99;
  bool v100;
  s32 v101;
  SBTLUNIT_LISTWORK *TargetList_Normal;
  SBTLUNIT_LISTWORK *v103;
  SBTLACTAI_WORK *actaiwk;
  s32 v107;
  f32 per;
  f32 v111;
  f32 v112;
  f32 v114;
  f32 v119;
  struct sdfVector4_t pos;
  f32 v121;
  sdfMatrix4_t v122;
  sdfMatrix4_t v123;
  f32 v124;
  f32 v125;
  sdfVector4_t v126;
  sdfVector4_t v127;
  sdfVector4_t v128;
  sdfVector4_t v129;
  sdfVector4_t v130;
  sdfVector4_t v131;

  Unit = sbattleGetUnit(sbtldbwk->mdlslcsr->point);
  if (!Unit)
    return (char)Unit;
  v6 = Unit;
  Unit->mv_spd.z = 0.0;
  Unit->mv_rot = 0.0;
  pos = Unit->pos;
  vct_A = pos;
  p_x = &vf00.x;
  x = p_x[4];
  y = p_x[5];
  z = p_x[6];
  w = p_x[7];
  sbtldbwk_local = sbtldbwk;
  v15 = sbtldbwk_local->padmode - 1;
  if (v15 > 5)
    goto LABEL_60;
  switch (v15)
  {
    case 0u:
      effList = wk->effList;
      prev_skillid = sbtldbwk->prev_skillid;
      if (sBtlSearchEffect_SAB(effList, prev_skillid, 1u))
        goto LABEL_190;
      v83 = wk->effList;
      v86 = sbtldbwk->prev_skillid;
      if (sBtlSearchEffect_SAB(v83, v86, 2u))
      {
LABEL_190:
        v96 = wk->effList;
        v99 = sbtldbwk->prev_skillid;
        sBtlDeleteEffectData_SkillID(v96, v99);
        LOBYTE(Unit) = 0;
        return (char)Unit;
      }
      v91 = wk->effList;
      v94 = sbtldbwk->prev_skillid;
      if (sBtlSearchEffect_SAB(v91, v94, 5u))
        goto LABEL_190;
      v107 = sbtldbwk->prev_skillid;
      if (sBtlForceDelete_EffectWork_ID(v107, 1))
        goto LABEL_221;
LABEL_201:
      LOBYTE(Unit) = 0;
      return (char)Unit;
LABEL_221:
      ++sbtldbwk->padmode;
      LOBYTE(Unit) = 0;
      return (char)Unit;
    case 1u:
      v20 = sbtldbwk_local->prev_skillid;
      if (v20 == 149)
      {
        ++sbtldbwk_local->padmode;
LABEL_200:
        v22 = sbtldbwk;
        if (v22->padmode == 2)
          goto LABEL_201;
        v22 = sbtldbwk;
        v101 = v22->prev_skillid;
        TargetList_Normal = sBtlCreateTargetList_Normal(v6, v101);
        v103 = TargetList_Normal;
        actaiwk = v6->actaiwk;
        if (TargetList_Normal->count < 1)
        {
          actaiwk->targetID = -1;
          goto LABEL_209;
        }
        else
        {
          actaiwk->targetID = TargetList_Normal->pUnitL[0]->pUnit->ListID;
LABEL_209:
          sBtlDeleteUnitList(v103, 0);
          LOBYTE(Unit) = 0;
          return (char)Unit;
        }
        goto LABEL_209;
LABEL_163:
        ++sbtldbwk->padmode;
        goto LABEL_200;
      }
      EffectData_ID = sBtlLoadEffectData_ID(v20);
      if (EffectData_ID)
        goto LABEL_161;
      goto LABEL_199;
      if (v100)
      {
LABEL_161:
        goto LABEL_163;
      }
LABEL_199:
      goto LABEL_200;
    case 2u:
      sbtldbwk_local = sbtldbwk;
      v23 = sbtldbwk_local->prev_skillid;
      v6->actwk->use_skillid = v23;
      v24 = v6->actaiwk;
      v24->mode = 16;
      v24->cmpframe = 0;
      v24->frame = 0;
      sBtlSetUseSkill(v6, v23, 0);
      v25 = 0;
      while (2)
      {
        UnitMng = wk->UnitMng;
        if (v25 >= UnitMng->number)
        {
LABEL_57:
          ++sbtldbwk->padmode;
LABEL_60:
          if (IsSceanStop())
            goto LABEL_84;
          v32 = CHECK_PRESS2(4100);
          if (v32)
            v33 = 128.0;
          else
            v33 = 0.0;
          v34 = -128.0;
          v35 = CHECK_PRESS2(4101);
          if (v35)
            v33 = -128.0;
          v36 = CHECK_PRESS2(4103);
          if (!CHECK_PRESS2(4102))
          {
            v34 = v36 ? 128.0 : 0.0;
            if (!v36 && !v35 && !v32)
            {
LABEL_84:
              if (CHECK_TRIG(4099, 1))
              {
                v48 = sbtldbwk;
                v48->prev_skillid = 149;
                v49 = 2;
              }
              else if (CHECK_TRIG(4098, 1))
              {
                v48 = sbtldbwk;
                v48->prev_skillid = v48->change_skillid;
                v49 = 1;
              }
              else
              {
                if (!CHECK_TRIG(4096, 1))
                {
LABEL_97:
                  if (v6->next_motionID != 5)
                  {
LABEL_102:
                    v128.x = x;
                    v128.y = y;
                    v128.z = z;
                    v128.w = w;
                    CheckMapHit(v6, v128);
                    LOBYTE(Unit) = 1;
                    return (char)Unit;
                  }
                  v52 = v6;
                  v53 = 0;
LABEL_101:
                  sBtlSetMotion(v52, v53, 4, 0, 0);
                  goto LABEL_102;
                }
                v49 = 6;
                v48 = sbtldbwk;
              }
              v48->padmode = v49;
              goto LABEL_97;
            }
          }
          vct_A.x = v34;
          vct_A.y = 0.0;
          vct_A.z = v33;
          vct_A.w = 0.0;
          v39 = &vf00.x;
          v40 = v39[6];
          v41 = v39[4];
          v42 = v39[5];
          v44 = (f32)((f32)(v41 * v41) + (f32)(v42 * v42)) + (f32)(v40 * v40);
          sub_1949110(0);
          v45 = sqrtf(v44);
          if (v45 < 48.0)
            goto LABEL_84;
          major = v6->major;
          minor = v6->minor;
          v6->mv_spd.z = sBtlGetVisualData(major, minor)->mv_spd;
          v57 = v6->pos.x;
          v58 = v6->pos.y;
          v59 = v6->pos.z;
          ScreenDir = mapGetScreenDir(v57, v58, v59, 0.0);
          v61 = ScreenDir * -0.017453292;
          sub_1949280(0, ScreenDir * -0.017453292);
          get_transpose(&v123, &mtx_A, 0);
          v129 = vct_A;
          v122 = v123;
          v126 = op_Multiply_60923920(&v122, v129, 0);
          vct_A = v126;
          v67 = vct_A;
          vct_A = v67;
          v68 = v6->pos;
          vct_B = v68;
          vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
          v121 = x;
          v124 = z;
          v125 = y;
          v119 = w;
          if (v70)
          {
LABEL_137:
            v131.x = v6->rot.x;
            v72 = vct_A.x;
            v74 = v6->pos.x;
            v73 = v6->pos.y;
            v75 = v6->pos.z;
            v76 = v6->pos.w;
            v131.y = v6->rot.y;
            v78 = v6->rot.z;
            v79 = v6->rot.w;
            v112 = vct_A.x;
            v114 = v6->rot.x;
            v111 = v6->rot.y;
            v131.y = v111;
            v72 = v112;
            v131.x = v114;
            per = v72;
            v130.x = v74;
            v130.y = v73;
            v130.z = v75;
            v130.w = v76;
            v131.z = v78;
            v131.w = v79;
            *(u64 *)&v127.x = 0;
            *(u64 *)&v127.z = v64;
            Radian = sBtlGetRadian(v130, v131, v127, per);
            w = v119;
            x = v121;
            z = v124;
            v6->rot = vct_A;
            sBtlAddUnitDeg(v6, Radian);
            sBtlSetAction(v6, 2, 0);
            y = v125;
            if (!sBtlCheckMotionID(v6, 5))
              goto LABEL_102;
            v53 = 5;
            v52 = v6;
            goto LABEL_101;
          }
          goto LABEL_137;
        }
        pUnit = UnitMng->pUnitL[v25]->pUnit;
        if (!pUnit)
          goto LABEL_43;
        goto LABEL_9012;
        if (!pUnit)
        {
LABEL_43:
          ++v25;
          continue;
        }
LABEL_9012:
        break;
      }
      if (pUnit->mode == 8)
      {
        pUnit->damagecnt = 0;
        *(u64 *)&pUnit->damage_serialID = -1;
      }
      goto LABEL_43;
    case 3u:
      hModel = v6->hModel;
      if (mdlGetMotionFrame(hModel) < 0)
        goto LABEL_60;
      v30 = v6->actaiwk;
      v30->mode = 15;
      *(u64 *)&v30->frame = 0;
      sBtlCheckMHTData(v6, v6->actwk->use_skillid);
      goto LABEL_57;
    case 4u:
    case 5u:
      sbtldbwk_local = sbtldbwk;
      sbtldbwk_local->padmode = 0;
      goto LABEL_60;
    default:
      goto LABEL_60;
  }
}

// 0x1912ff0
void sBtlDebug_SetEffectSetTbl(void) {
  u64 v3;

  v3 = sbtldbwk->status & 0xFFFFFFFFFBF1BD31LL;
  sbtldbwk->y_status &= 0xFFFFFFFFFFFFFF8FLL;
  sbtldbwk->status = v3 | 0x40E0046;
}

// 0x19059d0
bool sBtlDebug_CheckFlg(void) {
  return 1;
}

// 0x1916170
void sBtlDebug_DevilNameListDraw(s32 ofsx, s32 ofsy) {
  void **v3;
  SB_ENCOUNTPAC *EncountPac;
  SB_ENCOUNTPAC *v8;
  Il2CppObject *v9;
  Il2CppObject *v10;
  char *scene_name;
  s32 v12;
  s32 v13;
  il2cpp_array_size_t max_length;
  u64 v15;
  s64 v16;
  SB_ENCOUNTPAC *v17;
  SB_ENCOUNT1 *v19;
  s16 v20;
  s16 *p_devil;
  s32 devil;
  void **v23;
  Il2CppObject *v24;
  char *v25;
  s32 v26;
  char *v27;
  char *v28;
  char *v29;
  s16 v30;
  s8 v31[4];
  s8 data[4];

  v3 = &sBtlEncount;
  EncountPac = sBtlGetEncountPac(-1);
  v8 = EncountPac[wk->encountno];
  data[0] = v8->start_map;
  v9 = Box(sbyte, data);
  v31[0] = v8->start_floor;
  v10 = Box(sbyte, v31);
  Format_54759776("MAP {0} {1}", v9, v10, 0);
  scene_name = v8->scene_name;
  v12 = 16 * ofsx + 320;
  v13 = 8 * ofsy;
  DbgText(v12, v13 - 160, scene_name, 0, 109, 24, 0);
  max_length = sBtlGetEncountPac(-1)[wk->encountno]->enc1->max_length;
  if ((s32)max_length >= 1)
  {
    v15 = 0;
    v16 = 8 * (u32)max_length;
    do
    {
      if (!*((u32 *)*v3 + 56))
      v17 = sBtlGetEncountPac(-1);
      v19 = v17[wk->encountno]->enc1[v15 / 8];
      devil = (u16)v19->devil;
      p_devil = &v19->devil;
      v20 = devil;
      if (devil)
      {
        v30 = v20;
        v23 = v3;
        v24 = Box(s16, &v30);
        Format("0x{0:X3}", v24, 0);
        v25 = ToString_55989008((s16)p_devil, "x3", 0);
        v26 = *p_devil;
        v27 = v25;
        v28 = sdatDevilName(v26, 0);
        v29 = Concat_54832128("0x", v27, ":", v28, 0);
        v3 = v23;
        DbgText(v12, v13, v29, 0, 109, 24, 0);
      }
      v15 += 8;
      v13 += 160;
    }
    while (v16 != v15);
  }
}

// 0x19059e0
void sBtlDebug_UnitPanelCursor(SBDEBUG_CSRWORK *wk) {
  s32 point;
  s32 v11;
  s64 v13;
  SBATTLE_WORK *v16;
  SBTLUNIT_LISTWORK *v17;
  SBTLUNIT_WORK *pUnit;
  s64 v19;
  SBTLUNIT_LISTWORK *v21;
  SBTLUNIT_WORK *v22;
  SBTLDEBUG_WORK *sbtldbwk_local;
  s32 playerID;
  SBTLUNIT_WORK *v27;
  s32 v29;
  SBTLUNIT_WORK *v32;
  sdatUnitWork_t *para;
  SBATTLE_WORK *v35;
  SBTLUNIT_LISTWORK *v36;
  s32 v37;
  SBTLUNIT_WORK *v38;
  SBTLUNIT_WORK *v39;
  sdatUnitWork_t *v40;
  s32 v44;
  s32 v45;
  s32 v46;
  s32 v47;
  SBATTLE_WORK *v49;
  u32 stock_mask;
  s32 v51;
  SBATTLE_WORK *v53;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 v55;
  SBTLUNIT_WORK *v56;
  SBTLUNIT_WORK *v57;
  s8 *p_seikaku;
  s16 *p_equipgun;
  s32 *p_mag;
  s32 v63;
  SBATTLE_WORK *v65;
  u32 v66;
  s32 v67;
  SBATTLE_WORK *v69;
  SBTLUNIT_LISTWORK *v70;
  s32 v71;
  SBTLUNIT_WORK *v72;
  SBTLUNIT_WORK *v73;
  s8 *v74;
  s16 *v76;
  s32 *v78;
  s32 *p_hgun_num;
  s32 hgun_num;
  s16 *p_equipsord;
  s8 v84;
  s8 v85;
  s32 *v87;
  s32 v88;
  s16 *v90;
  s32 v91;

  if (!sBtlDebug_CheckMainPanel(0))
    return;
  switch (sbtldbwk->gstat0)
  {
    case 0:
      if (CHECK_TRIG2(4103))
      {
        point = wk->point;
        if (point == 6)
          goto LABEL_107;
        v11 = point;
        goto LABEL_15;
      }
      if (CHECK_TRIG2(4102))
      {
        v29 = wk->point;
        if (v29 != 6)
        {
          sBtlDebug_SetStatusflg(v29, sbflg_panel, 1);
        }
      }
      else if (CHECK_TRIG2(4096))
      {
        if (wk->point == 6)
        {
          v11 = 6;
LABEL_15:
          sBtlDebug_SetStatusflg(v11, sbflg_panel, 0);
        }
      }
      else
      {
        if (CHECK_REP2(4100))
        {
          v44 = wk->point - 1;
          wk->point = v44;
          if (v44 >= 0)
            goto LABEL_107;
          v45 = wk->maxp - 1;
        }
        else
        {
          if (!CHECK_REP2(4101))
            goto LABEL_107;
          v46 = wk->point;
          if (v46 + 1 < wk->maxp)
            v45 = v46 + 1;
          else
            v45 = 0;
        }
        wk->point = v45;
      }
LABEL_107:
      if (CHECK_REP2(4103))
      {
        v47 = wk->point;
        if (v47 == 12)
        {
          v49 = wk;
          stock_mask = v49->stock_mask;
          v51 = v49->summonindex[0];
          if (sBtlCheckBit(stock_mask, v51))
          {
            v53 = wk;
            UnitMng = v53->UnitMng;
            v55 = v53->summonID[v53->summonindex[0]];
            v56 = sBtlSearchUnit_ID(UnitMng, v55);
            if (v56)
            {
              v57 = v56;
              p_seikaku = &v56->para->seikaku;
              sBtlParaAdd_8(p_seikaku, 1, 4, 0);
              v57->actcounter_max = sBtlGetDevilData(v57->para->devilid, -1)->actcounter;
              sBtlSetactcounter(v57);
              v57->actcounter = v57->actcounter_max;
            }
          }
          v47 = wk->point;
          if (v47 != 13)
          {
LABEL_125:
            if (v47 == 16)
              goto LABEL_126;
            goto LABEL_177;
          }
        }
        else if (v47 != 13)
        {
          goto LABEL_125;
        }
        p_hgun_num = &wk->hgun_num;
        sBtlParaAdd(p_hgun_num, 1, 6, 0);
        hgun_num = wk->hgun_num;
        sBtlSetGunNum(hgun_num);
        v47 = wk->point;
        if (v47 == 16)
        {
LABEL_126:
          p_equipgun = &wk->equipgun;
          sBtlParaAdd_16(p_equipgun, 1, 1, 0);
          v47 = wk->point;
          if (v47 != 17)
          {
LABEL_131:
            if (v47 == 18)
              goto LABEL_132;
            goto LABEL_183;
          }
LABEL_178:
          p_equipsord = &wk->equipsord;
          sBtlParaAdd_16(p_equipsord, 1, 1, 0);
          v47 = wk->point;
          if (v47 == 18)
          {
LABEL_132:
            p_mag = &wk->mag;
            sBtlParaAdd(p_mag, 1, 300, 0);
            if (wk->point == 21)
            {
LABEL_184:
              v84 = 0;
LABEL_210:
              sBtlDebug_SetEncountPara(v84, 1);
              goto LABEL_90;
            }
            goto LABEL_90;
          }
LABEL_183:
          if (v47 != 21)
            goto LABEL_90;
          goto LABEL_184;
        }
LABEL_177:
        if (v47 != 17)
          goto LABEL_131;
        goto LABEL_178;
      }
      if (CHECK_REP2(4102))
      {
        v63 = wk->point;
        if (v63 == 12)
        {
          v65 = wk;
          v66 = v65->stock_mask;
          v67 = v65->summonindex[0];
          if (sBtlCheckBit(v66, v67))
          {
            v69 = wk;
            v70 = v69->UnitMng;
            v71 = v69->summonID[v69->summonindex[0]];
            v72 = sBtlSearchUnit_ID(v70, v71);
            if (v72)
            {
              v73 = v72;
              v74 = &v72->para->seikaku;
              sBtlParaDec_8(v74, 1, 4);
              v73->actcounter_max = sBtlGetDevilData(v73->para->devilid, -1)->actcounter;
              sBtlSetactcounter(v73);
              v73->actcounter = v73->actcounter_max;
            }
          }
          v63 = wk->point;
          if (v63 != 13)
          {
LABEL_156:
            if (v63 == 16)
              goto LABEL_157;
            goto LABEL_200;
          }
        }
        else if (v63 != 13)
        {
          goto LABEL_156;
        }
        v87 = &wk->hgun_num;
        sBtlParaDec(v87, 1, 6);
        v88 = wk->hgun_num;
        sBtlSetGunNum(v88);
        v63 = wk->point;
        if (v63 == 16)
        {
LABEL_157:
          v76 = &wk->equipgun;
          sBtlParaDec_16(v76, 1, 1);
          v63 = wk->point;
          if (v63 != 17)
          {
LABEL_162:
            if (v63 == 18)
              goto LABEL_163;
            goto LABEL_206;
          }
LABEL_201:
          v90 = &wk->equipsord;
          sBtlParaDec_16(v90, 1, 1);
          v63 = wk->point;
          if (v63 == 18)
          {
LABEL_163:
            v78 = &wk->mag;
            sBtlParaDec(v78, 1, 300);
            if (wk->point == 21)
            {
LABEL_207:
              v84 = 1;
              goto LABEL_210;
            }
LABEL_90:
            if (wk->point == 21)
            {
              sBtlDebug_DevilNameListDraw(280, 270);
            }
            return;
          }
LABEL_206:
          if (v63 != 21)
            goto LABEL_90;
          goto LABEL_207;
        }
LABEL_200:
        if (v63 != 17)
          goto LABEL_162;
        goto LABEL_201;
      }
      if (CHECK_REP2(4108))
      {
        if (wk->point != 21)
          goto LABEL_90;
        v85 = 0;
LABEL_216:
        sBtlDebug_SetEncountPara(v85, 16);
        goto LABEL_90;
      }
      if (CHECK_REP2(4107))
      {
        if (wk->point != 21)
          goto LABEL_90;
        v85 = 1;
        goto LABEL_216;
      }
      if (!CHECK_TRIG2(4096))
        goto LABEL_90;
      v91 = wk->point;
      if (v91 != 21)
        goto LABEL_232;
      if ((sbtldbwk->status & 0x8000000) != 0)
        goto LABEL_231;
      if ((wk->status & 0x10000) != 0)
      {
        ++sbtldbwk->gstat0;
        sBtlDebug_ResetPos_PlayerSide();
        sBtlReLoadMap();
LABEL_231:
        v91 = wk->point;
LABEL_232:
        if (v91 == 19)
        {
          sBtlDebug_ResetPos_PlayerSide();
          v91 = wk->point;
        }
        if (v91 == 20)
        {
          sBtlDebug_ResetStockPara();
        }
        goto LABEL_90;
      }
      return;
    case 1:
      sBtlForceDelete_SkillFlag(0x500u);
      if (wk->effList->num > 0)
        goto LABEL_90;
      if (!sBtlForceDelete_EffectWork(0))
        goto LABEL_90;
      goto LABEL_86;
    case 2:
      v13 = 0;
      while (2)
      {
        v16 = wk;
        v17 = v16->UnitMng;
        if (v13 < v17->number)
        {
          pUnit = v17->pUnitL[v13]->pUnit;
          if (!pUnit)
            goto LABEL_26;
          goto LABEL_9000;
          if (!pUnit)
          {
LABEL_26:
            ++v13;
            continue;
          }
LABEL_9000:
          if ((pUnit->side & 2) != 0)
            pUnit->mode = 9;
          goto LABEL_26;
        }
        break;
      }
      playerID = v16->playerID;
      v27 = sBtlSearchUnit_ID(v17, playerID);
      if (v27)
      {
        v32 = v27;
        if (sBtlCheckDamageTarget(v32))
        {
          para = v32->para;
          sBtlGetBadStatus(para);
        }
      }
      v35 = wk;
      if (v35->member_num >= 1)
      {
        v35 = wk;
        v36 = v35->UnitMng;
        v37 = v35->summonID[v35->summonindex[0]];
        v38 = sBtlSearchUnit_ID(v36, v37);
        if (v38)
        {
          v39 = v38;
          if (sBtlCheckDamageTarget(v39))
          {
            v40 = v39->para;
            sBtlGetBadStatus(v40);
          }
        }
      }
      wk->status &= ~0x40000000u;
LABEL_86:
      sbtldbwk_local = sbtldbwk;
LABEL_89:
      ++sbtldbwk_local->gstat0;
      goto LABEL_90;
    case 3:
      v19 = 0;
      while (2)
      {
        v21 = wk->UnitMng;
        if (v19 >= v21->number)
          goto LABEL_46;
        v22 = v21->pUnitL[v19]->pUnit;
        if (!v22)
          goto LABEL_37;
        if ((v22->side & 2) != 0)
        {
LABEL_46:
          if (wk->UnitMng->number > (s32)v19)
            goto LABEL_90;
          sbtldbwk_local = sbtldbwk;
          sbtldbwk_local->status |= 0x8000000u;
          goto LABEL_89;
        }
LABEL_37:
        ++v19;
        continue;
      }
    default:
      goto LABEL_90;
  }
}

// 0x1915370
void sBtlDebug_SetBattleMode(s8 flg, s32 para) {
  SBATTLE_WORK *wk_local;
  s32 v6;
  s16 v7;
  s16 v8;
  s32 v9;

  if (flg == 1)
  {
    wk_local = wk;
    v9 = --wk_local->battlemode;
    if (v9 <= 0)
    {
      v7 = 3;
      v8 = 3;
      goto LABEL_10;
    }
  }
  else if (!flg)
  {
    wk_local = wk;
    v6 = ++wk_local->battlemode;
    if (v6 >= 4)
    {
      v7 = 0;
      v8 = 0;
LABEL_10:
      wk_local->battlemode = v8;
      return;
    }
  }
}

// 0x1915c20
void sBtlDebug_SetSenseiMode(s8 flg, s32 para) {
  SBATTLE_WORK *wk_local;
  s32 v6;
  s8 v7;

  if (flg == 1)
  {
    wk_local = wk;
    v7 = wk_local->senseimode - 1;
    wk_local->senseimode = v7;
    if ((v7 & 0x80) == 0)
      return;
    goto LABEL_13;
  }
  if (!flg)
  {
    wk_local = wk;
    v6 = ++wk_local->senseimode;
    if (v6 >= 3)
    {
LABEL_13:
      wk_local->senseimode = 0;
    }
  }
}

// 0x19151f0
void sBtlDebug_SetEncountPara(s8 flg, s32 para) {
  s32 *v6;
  SBATTLE_WORK *wk_local;
  s32 *p_encountno;

  if (flg == 1)
  {
    wk_local = wk;
    if (wk_local->encountno < 1)
      return;
    p_encountno = &wk_local->encountno;
    sBtlParaDec(p_encountno, para, 1024);
    return;
  }
  if (!flg)
  {
    v6 = &wk->encountno;
    sBtlParaAdd(v6, para, 1024, 0);
  }
}

// 0x1915490
void sBtlDebug_SetNakamaNo(s32 idx, s8 flg, s32 para) {
  s16 *v7;
  char *v8;
  s32 v9;
  s16 *stack_p;
  char *v12;
  s16 v13;

  if (flg == 1)
  {
    stack_p = GBWK->player->stack_p;
    v12 = (char *)stack_p + 2 * idx;
    v13 = *((u16 *)v12 + 16) - 1;
    *((u16 *)v12 + 16) = v13;
    if (v13 < 0)
    {
      stack_p = GBWK->player->stack_p;
      stack_p[idx] = 31;
    }
  }
  else if (!flg)
  {
    v7 = GBWK->player->stack_p;
    v8 = (char *)v7 + 2 * idx;
    v9 = (s16)++*((u16 *)v8 + 16);
    if (v9 >= 31)
    {
      v7 = GBWK->player->stack_p;
      v7[idx] = 0;
    }
  }
}

// 0x19155e0
void sBtlDebug_SetSpDbgParam(s8 flg, s32 para) {
  ;
}

// 0x1929ce0
bool sBtlDebug_ResetStockPara(void) {
  sdatPlayerUnitWork_t *PlayerData;
  s32 Gun_Num;
  SBATTLE_WORK *v7;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 playerID;
  SBTLUNIT_WORK *v10;
  sdatUnitWork_t *para;
  SBTLUNIT_WORK *v12;
  sdatParaWork_t *now;
  s32 maxmp;
  SBATTLE_WORK *v17;
  SBTLUNIT_LISTWORK *v18;
  s32 v19;
  SBTLUNIT_WORK *v20;
  sdatUnitWork_t *v21;
  SBTLUNIT_WORK *v22;
  sdatParaWork_t *v24;
  s32 v25;
  s32 i;
  sdatUnitWork_t *StockUnitData;
  sdatParaWork_t *v29;
  sdatUnitWork_t *v30;
  s32 v32;

  PlayerData = sBtlGetPlayerData();
  PlayerData->item[1] = 3;
  UpdateGetList(GBWK->sortSave, 1, 1, 0);
  Gun_Num = sBtlGetGun_Num();
  wk->hgun_num = Gun_Num;
  sBtlReleaseItemList(wk->itemList);
  sBtlEntryItemList(wk->itemList);
  sBtlReleaseItemList(wk->bulletList);
  sBtlEntryItemList_Type(wk->bulletList, 4u);
  v7 = wk;
  UnitMng = v7->UnitMng;
  playerID = v7->playerID;
  v10 = sBtlSearchUnit_ID(UnitMng, playerID);
  if (v10)
  {
    para = v10->para;
    v12 = v10;
    now = para->now;
    maxmp = now->maxmp;
    now->hp = now->maxhp;
    now->mp = maxmp;
    sBtlResetBadStatus(v12, 0x3FFFF);
    sBtlResetBadStatus_GB(PlayerData->para, 0x3FFFF);
  }
  v17 = wk;
  if (v17->member_num >= 1)
  {
    v17 = wk;
    v18 = v17->UnitMng;
    v19 = v17->summonID[v17->summonindex[0]];
    v20 = sBtlSearchUnit_ID(v18, v19);
    if (v20)
    {
      v21 = v20->para;
      v22 = v20;
      v24 = v21->now;
      v25 = v24->maxmp;
      v24->hp = v24->maxhp;
      v24->mp = v25;
      sBtlResetBadStatus(v22, 0x3FFFF);
    }
  }
  for (i = 0; ; ++i)
  {
    if (i >= wk->stock_num)
      break;
    StockUnitData = sBtlGetStockUnitData(i);
    if (StockUnitData)
    {
      v29 = StockUnitData->now;
      v30 = StockUnitData;
      v32 = v29->maxmp;
      v29->hp = v29->maxhp;
      v29->mp = v32;
      sBtlResetBadStatus_GB(v30, 0x3FFFF);
    }
  }
  return 1;
}

// 0x192a010
bool sBtlDebug_CheckLoadEncountData(void) {
  s32 gstat0;
  s32 encountno;
  SBTLDEBUG_WORK *v10;
  s32 v11;
  SBATTLE_WORK *v14;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 v16;
  SBTLUNIT_WORK *v17;
  SBTLUNIT_WORK *v18;
  s32 sklid;
  SBTLDEBUG_WORK *v23;
  s64 status;

  if ((sbtldbwk->status & 0x8000000) == 0)
    return 1;
  gstat0 = sbtldbwk->gstat0;
  if (gstat0 != 5)
  {
    if (gstat0 != 4)
      return 1;
    if (wk->enemy_num > 0)
      return 1;
    encountno = wk->encountno;
    sBtlSetEncountPacData(encountno);
    v10 = sbtldbwk;
    v11 = v10->gstat0;
    v10->result_cnt = 0;
    v10->gstat0 = v11 + 1;
    sBtlAllInit();
    return 1;
  }
  v14 = wk;
  if (v14->member_num >= 1)
  {
    v14 = wk;
    UnitMng = v14->UnitMng;
    v16 = v14->summonID[v14->summonindex[0]];
    v17 = sBtlSearchUnit_ID(UnitMng, v16);
    if (!v17)
      return 1;
    v18 = v17;
    if (!sBtlCheckDamageTarget(v18))
      return 1;
    if (!sBtlLoadEffectData(v18))
      return 1;
    sklid = sBtlGetItemtbl(wk->equipbullet)->sklid;
    goto LABEL_38;
  }
  v14 = wk;
  sklid = sBtlGetItemtbl(v14->equipbullet)->sklid;
LABEL_38:
  if (!sBtlLoadEffectData_IDMask(sklid, 0xCu))
    return 1;
  v23 = sbtldbwk;
  status = v23->status;
  v23->gstat0 = 0;
  v23->status = status & 0xFFFFFFFFF7FFFFFFLL;
  return 1;
}

// 0x192a3c0
void sBtlDebug_Shutdown(dds3ProcessID_t *id) {
  SBDEBUG_FILELISTWORK *fileList;
  SBTLDEBUG_WORK *sbtldbwk_local;
  s64 i;
  s64 v6;
  void *name;

  fileList = sbtldbwk->fileList;
  if (fileList)
  {
    fileList = sbtldbwk->fileList;
    sbattleDeleteFileList(fileList);
    sbtldbwk_local = sbtldbwk;
    sbtldbwk_local->fileList = 0;
  }
  for (i = 32; i != 160; i += 8)
  {
    name = (*(Il2CppClass **)((char *)&sbtldbwk->ef_wk->obj.klass + i))->_1.name;
    if (!op_Inequality(name, 0, 0))
      continue;
    v6 = *(s64 *)((char *)&sbtldbwk->ef_wk->obj.klass + i);
    *(u64 *)(v6 + 16) = 0;
  }
  if (sbtldbwk)
  {
    sbtldbwk = 0;
  }
}

// 0x19069b0
void sBtlDebug_DrawCursor(s32 x, s32 y, SBDEBUG_CSRWORK *wk) {
  char *v7;
  char *v8;
  char **v9;
  s32 point;
  s32 offset;
  char *v12;

  v7 = NewSpecific(string, 1u);
  v8 = ">";
  v7[0] = ">";
  v9 = &v7[0];
  point = wk->point;
  offset = wk->offset;
  v12 = *v9;
  DbgText(16 * x, 8 * (y + 12 * (point - offset)), v12, 5, 109, 24, 0);
}

// 0x190a430
void sBtlDebug_DrawCursor_OFFSET(s32 x, s32 y, s32 offsety, SBDEBUG_CSRWORK *wk) {
  char *v9;
  char *v10;
  char **v11;
  s32 point;
  s32 offset;
  char *v14;

  v9 = NewSpecific(string, 1u);
  v10 = ">";
  v9[0] = ">";
  v11 = &v9[0];
  point = wk->point;
  offset = wk->offset;
  v14 = *v11;
  DbgText(16 * x, 8 * (y + (point - offset) * offsety), v14, 5, 109, 24, 0);
}

// 0x1906ae0
void sBtlDebug_DrawNormalList(char *wk, s32 num, s32 nowpoint, s32 x, s32 y, bool *flg) {
  s32 v13;
  s64 v14;
  s64 v15;
  bool *m_Items;
  char **v17;
  s32 i;
  _BOOL4 v19;
  _BOOL4 v20;
  s32 v21;
  s32 v22;
  char *v23;
  char **v24;
  s32 v25;
  s32 v26;
  char *v27;

  if (num >= 1)
  {
    v13 = 16 * x;
    v14 = nowpoint;
    v15 = num;
    if (flg)
    {
      m_Items = flg;
      v17 = wk;
      for (i = 8 * y; ; i += 96)
      {
        v20 = *m_Items++;
        v19 = v20;
        if (v14)
          v21 = 0;
        else
          v21 = 5;
        if (v19)
          v22 = v21;
        else
          v22 = -1;
        v23 = *v17;
        DbgText(v13, i, v23, v22, 109, 24, 0);
        --v14;
        ++v17;
        if (!--v15)
          return;
      }
    }
    v24 = wk;
    v25 = 8 * y;
    do
    {
      if (v14)
        v26 = 0;
      else
        v26 = 5;
      v27 = *v24;
      DbgText(v13, v25, v27, v26, 109, 24, 0);
      ++v24;
      --v14;
      --v15;
      v25 += 96;
    }
    while (v15);
  }
}

// 0x190e110
void sBtlDebug_DrawNormalList_Col(char *wk, s32 num, s32 nowpoint, s32 point, s32 x, s32 y) {
  s32 v13;
  char **m_Items;
  s64 v15;
  s32 i;
  char *v17;
  char **v18;
  s64 v19;
  s64 v20;
  s64 v21;
  s32 v22;
  s32 v23;
  char *v24;

  if (num >= 1)
  {
    v13 = 16 * x;
    if (point == -10)
    {
      m_Items = wk;
      v15 = num;
      for (i = 8 * y; ; i += 96)
      {
        v17 = *m_Items;
        DbgText(v13, i, v17, 6, 109, 24, 0);
        ++m_Items;
        if (!--v15)
          return;
      }
    }
    v18 = wk;
    v19 = nowpoint;
    v20 = point;
    v21 = num;
    v22 = 8 * y;
    do
    {
      if (v20)
        v23 = 4 * (v19 == 0);
      else
        v23 = 5;
      v24 = *v18;
      DbgText(v13, v22, v24, v23, 109, 24, 0);
      --v20;
      --v19;
      ++v18;
      --v21;
      v22 += 96;
    }
    while (v21);
  }
}

// 0x19088e0
static void sBtlDebug_SetStatusflg(s32 nowp, SBDEBUG_FLGWORK *wk, s8 flg) {
  Il2CppClass **v7;
  Il2CppClass *v8;
  char *v9;
  Il2CppClass *v10;
  s32 namespaze_high;
  void *data;
  s64 y_status;
  s64 v16;
  s32 v17;
  s32 v19;
  SBTLDEBUG_WORK *v21;
  SBTLUNIT_WORK *Unit;
  s64 v24;
  SBATTLE_WORK *v26;
  s32 timecount;
  Il2CppClass *v31;
  s64 v32;
  s64 v33;
  s32 v34;
  u32 v38;
  bool v39;
  s64 v40;
  SBTLUNIT_LISTWORK *UnitMng;
  SBTLUNIT_WORK *pUnit;
  s32 v44;
  s32 all_dead_raito;
  SBTLSKILLP_TBL *Skilltbl;
  s32 attrtime;
  s32 maxhp;
  s32 v51;
  s32 v52;
  SBTLDEBUG_WORK *v59;
  SBTLDEBUG_WORK *v61;
  SBTLDEBUG_WORK *v63;
  SBTLDEBUG_WORK *v66;
  SBTLDEBUG_WORK *v68;
  SBDEBUG_CSRWORK *sklccsr;
  SBTLDEBUG_WORK *v71;
  SBTLDEBUG_WORK *v73;
  s64 status;
  SBTLDEBUG_WORK *v76;
  SBDEBUG_CSRWORK *effhitcsr;
  s32 v78;
  s32 v79;
  s32 v81;
  SBDEBUG_CSRWORK *nef_modecsr;
  SBTLDEBUG_WORK *v85;
  SBTLDEBUG_WORK *v87;
  SBTLUNIT_WORK *v88;
  SBTLDEBUG_WORK *v89;
  sdatUnitWork_t *para;
  SBTLDEBUG_WORK *v92;
  SBTLDEBUG_WORK *v95;
  SBDEBUG_CSRWORK *cameraCsr;
  il2cpp_array_size_t max_length;
  s64 v98;
  void *v99;
  void *p_buffBattleCameraPar;
  void *v104;
  SBDEBUG_CSRWORK *weaponCsr;
  SBTLDEBUG_WORK *v107;
  s64 v109;
  SBTLDEBUG_WORK *v113;
  s64 v114;
  SBTLUNIT_WORK *v116;
  u32 v118;
  SBTLDEBUG_WORK *v119;
  s32 devilid;
  u16 major;
  s32 minor;
  VISUALDATA_WORK *VisualData;
  SBTLDEBUG_WORK *v125;
  VISUALDATA_WORK *v126;
  s32 v128;
  _BOOL4 v129;
  SBDEBUG_CSRWORK *mdlslcsr;
  void *battleCameraPar_local;
  SBDEBUG_CSRWORK *unitcsr;

  v7 = &wk->obj.klass + nowp;
  v10 = v7[4];
  v9 = (v7 + 4);
  v8 = v10;
  switch (LOBYTE(v10->_1.name))
  {
    case 0:
      namespaze_high = HIDWORD(v8->_1.namespaze);
      switch (namespaze_high)
      {
        case 11:
          y_status = sbtldbwk->y_status;
          break;
        case 2:
          y_status = sbtldbwk->unitst;
          break;
        case 1:
          v8 = *(Il2CppClass **)v9;
          data = v8->_1.byval_arg.data;
          y_status = sbtldbwk->status;
          if (data == 0x40000000)
          {
            wk->fSEPan ^= 1u;
          }
          else if (data == 0x20000000)
          {
            wk->fSEDouji ^= 1u;
          }
          else if (data == 0x10000000)
          {
            wk->fSEDistance ^= 1u;
          }
          break;
        default:
          y_status = 0;
          break;
      }
      v31 = *(Il2CppClass **)v9;
      v32 = *(u64 *)(*(u64 *)v9 + 32);
      if ((v32 & y_status) != 0)
      {
        v33 = y_status & ~v32;
        v34 = HIDWORD(v31->_1.namespaze);
        if (v34 != 11)
        {
LABEL_47:
          if (v34 == 2)
          {
            sbtldbwk->unitst = v33;
          }
          else if (v34 == 1)
          {
            sbtldbwk->status = v33;
          }
          return;
        }
      }
      else
      {
        if (v32 == 0x100000)
          return;
        v33 = v32 | y_status;
        v34 = HIDWORD(v31->_1.namespaze);
        if (v34 != 11)
          goto LABEL_47;
      }
      sbtldbwk->y_status = v33;
      return;
    case 1:
      v16 = 24;
      if (!flg)
        v16 = 20;
      v17 = *(u32 *)((char *)&v8->_1.image + v16);
      switch (v17)
      {
        case 0:
          sbtldbwk->mode = 0;
          return;
        case 1:
          if (!flg)
          {
            v129 = LODWORD(v8->_1.namespaze) == 10;
            sbtldbwk->mdlslcsr->dummy = v129;
            sbtldbwk->mdlslcsr->point = 0;
          }
          mdlslcsr = sbtldbwk->mdlslcsr;
          mdlslcsr->maxp = wk->UnitMng->count;
          sbtldbwk->mode = 1;
          return;
        case 2:
          if (!flg)
          {
            sbtldbwk->mdlmenucsr->point = 0;
          }
          v59 = sbtldbwk;
          v59->mdlmenucsr->maxp = 9;
          v59->mode = 2;
          return;
        case 3:
          if (!flg)
          {
            sbtldbwk->mtioncgcsr->point = 0;
          }
          v61 = sbtldbwk;
          *(u64 *)&v61->mtioncgcsr->offset = 0x2700000000LL;
          v61->mode = 3;
          return;
        case 4:
          if (flg)
          {
            if (sbtldbwk->unitcsr->maxp)
            {
              goto LABEL_135;
            }
          }
          unitcsr = sbtldbwk->unitcsr;
          unitcsr->maxp = 544;
          *(u64 *)&unitcsr->point = 0;
LABEL_135:
          v63 = sbtldbwk;
          v63->unitmajor = 1;
          v63->unitmode = 0;
          v63->mode = 4;
          return;
        case 5:
          sbtldbwk->mode = 5;
          return;
        case 6:
        case 9:
          if (!flg)
          {
            sbtldbwk->visualcsr->point = 0;
          }
          v19 = v17 != 6;
          v21 = sbtldbwk;
          v21->mode = v17;
          v21->vs_posp = v19;
          Unit = sbattleGetUnit(sbtldbwk->mdlslcsr->point);
          if (!Unit)
            return;
          v116 = Unit;
          v119 = sbtldbwk;
          devilid = v116->para->devilid;
          if (v119->vs_raceid == devilid)
          {
            if (v118)
              goto LABEL_245;
            goto LABEL_244;
          }
          else if (v118)
          {
            goto LABEL_246;
          }
LABEL_244:
          v119 = sbtldbwk;
LABEL_245:
          devilid = v116->para->devilid;
LABEL_246:
          v119->vs_raceid = devilid;
          major = v116->major;
          minor = v116->minor;
          VisualData = sBtlGetVisualData(major, minor);
          v125 = sbtldbwk;
          v126 = Allocate(VISUALDATA_WORK);
          _ctor_26520096(v126, VisualData, 0);
          v125->vsdata = v126;
          sbtldbwk->vs_saveflg = 0;
          if ((VisualData->sdw_flg & 1) != 0)
          {
            v128 = 5;
            goto LABEL_254;
          }
          if ((VisualData->sdw_flg & 2) == 0)
          {
            v128 = 0;
            goto LABEL_254;
          }
          if ((VisualData->sdw_flg & 4) != 0)
          {
            v128 = 1;
            goto LABEL_254;
          }
          if ((VisualData->sdw_flg & 8) != 0)
          {
            v128 = 2;
            goto LABEL_254;
          }
          if ((VisualData->sdw_flg & 0x10) != 0)
          {
            v128 = 3;
            goto LABEL_254;
          }
          if ((VisualData->sdw_flg & 0x20) != 0)
            v128 = 4;
          else
            v128 = 1;
LABEL_254:
          sbtldbwk->vs_shadowflg = v128;
          *(u64 *)&sbtldbwk->visualcsr->offset = 0x2000000000LL;
          return;
        case 7:
          if (!flg)
          {
            sbtldbwk->modelhitcsr->point = 0;
          }
          v66 = sbtldbwk;
          v66->modelhitcsr->maxp = 5;
          v66->mode = 7;
          return;
        case 8:
          v68 = sbtldbwk;
          sklccsr = v68->sklccsr;
          v68->skillchange_mode = 0;
          sklccsr->maxp = 1600;
          v68->mode = 8;
          return;
        case 10:
          if (!flg)
          {
            sbtldbwk->opticsr->point = 0;
          }
          v71 = sbtldbwk;
          v71->opticsr->maxp = 38;
          v71->mode = 10;
          return;
        case 11:
          v73 = sbtldbwk;
          status = v73->status;
          v73->mode = 11;
          v73->status = status | 0x120;
          return;
        case 12:
          if (!flg)
          {
            sbtldbwk->effhitcsr->point = 0;
          }
          v76 = sbtldbwk;
          effhitcsr = v76->effhitcsr;
          v76->ef_num = 1;
          v78 = 16;
          v76->ef_mode = 0;
          v76->mode = 12;
          v79 = 5;
          goto LABEL_181;
        case 13:
          if (!flg)
          {
            sbtldbwk->effhitcsr->point = 0;
          }
          v81 = 13;
          v76 = sbtldbwk;
          v76->ef_num = 1;
          v76->ef_mode = 0;
          v78 = 16;
          goto LABEL_180;
        case 14:
          if (!flg)
          {
            sbtldbwk->effhitcsr->point = 0;
          }
          v81 = 14;
          v76 = sbtldbwk;
          v76->ef_num = 1;
          v78 = 8;
          v76->ef_mode = 0;
LABEL_180:
          effhitcsr = v76->effhitcsr;
          v76->mode = v81;
          v79 = 6;
LABEL_181:
          effhitcsr->maxp = v78;
          nef_modecsr = v76->nef_modecsr;
          nef_modecsr->point = 0;
          nef_modecsr->maxp = v79;
          v76->prev_cnt = 0;
          return;
        case 16:
          if (!flg)
          {
            sbtldbwk->bstcsr->point = 0;
          }
          v85 = sbtldbwk;
          v85->bstcsr->maxp = 21;
          v85->mode = 16;
          return;
        case 17:
          if (!flg)
          {
            sbtldbwk->paracsr->point = 0;
          }
          v87 = sbtldbwk;
          v87->paracsr->maxp = 14;
          v87->mode = 17;
          v88 = sbattleGetUnit(v87->mdlslcsr->point);
          v89 = sbtldbwk;
          para = v88->para;
          v89->para_bstno = sBtlGetBadStatus(para);
          return;
        case 18:
          if (!flg)
          {
            sbtldbwk->aicsr->point = 0;
          }
          v92 = sbtldbwk;
          v92->aicsr->maxp = 1;
          v92->mode = 18;
          return;
        case 20:
          if (!flg)
          {
            sbtldbwk->cameraCsr->point = 0;
          }
          v95 = sbtldbwk;
          cameraCsr = sbtldbwk->cameraCsr;
          max_length = sblistCameraMenu->max_length;
          v98 = v95->status;
          v95->mode = 20;
          cameraCsr->maxp = max_length;
          v95->status = v98 | 0x200000100LL;
          v99 = Allocate(BattleCameraPar);
          _ctor(v99, 0);
          p_buffBattleCameraPar = &buffBattleCameraPar;
          p_buffBattleCameraPar = v99;
          v104 = buffBattleCameraPar;
          battleCameraParSave = 0;
          battleCameraPar_local = battleCameraPar;
          buffBattleCameraPar->targetPosY = battleCameraPar_local->targetPosY;
          *(_OWORD *)&v104->length = *(_OWORD *)&battleCameraPar_local->length;
          *(_OWORD *)&v104->downMaxAngleY = *(_OWORD *)&battleCameraPar_local->downMaxAngleY;
          return;
        case 21:
          if (!flg)
          {
            sbtldbwk->weaponCsr->point = 0;
          }
          weaponCsr = sbtldbwk->weaponCsr;
          v107 = sbtldbwk;
          v109 = v107->status;
          v107->mode = 21;
          weaponCsr->maxp = tbl->max_length;
          v107->status = v109 | 0x400000100LL;
          return;
        case 22:
          if (wk->timeflg)
          {
            if (!flg)
            {
              sbtldbwk->timeCsr->point = 0;
            }
            v113 = sbtldbwk;
            v113->timeCsr->maxp = sblistTimeMenu->max_length;
            v114 = v113->status;
            v113->mode = 22;
            v113->status = v114 | 0x10100;
          }
          return;
        default:
          return;
      }
    case 3:
      if ((wk->status & 0x10000) == 0)
        return;
      v24 = 0;
      while (2)
      {
        UnitMng = wk->UnitMng;
        if (v24 >= UnitMng->number)
          return;
        pUnit = UnitMng->pUnitL[v24]->pUnit;
        if (!pUnit)
          goto LABEL_64;
        v44 = (u16)pUnit->para->devilid;
        if (v44 == 258 || v44 == 260)
          goto LABEL_64;
        if (sBtlCheckDamageTarget(pUnit))
        {
          if ((pUnit->side & 2) != 0)
          {
            if ((wk->status & 0x2000000) == 0)
            {
              all_dead_raito = sbtldbwk->all_dead_raito;
              if (all_dead_raito == 100)
              {
                v38 = (u16)pUnit->para->devilid - 258;
                v39 = v38 > 0x39;
                v40 = (1 << v38) & 0x300000000000001LL;
                if (v39 || v40 == 0)
                {
                  pUnit->actaiwk->status = pUnit->actaiwk->status & 0xFFFFFF9F | 0x40;
                  sBtlSetDeadDamage(pUnit, 0, 0);
                }
              }
              else
              {
                all_dead_raito = sbtldbwk->all_dead_raito;
                if (all_dead_raito == 1)
                {
                  Skilltbl = sBtlGetSkilltbl(1);
                  sBtlSetDeadWeak(pUnit, Skilltbl, 0x4000u);
                  sBtlSetMotion(pUnit, 1, 0, 0, 0);
                  attrtime = Skilltbl->attrtime;
                  sBtlSetAction(pUnit, 9, attrtime);
                }
                else
                {
                  maxhp = pUnit->para->now->maxhp;
                  all_dead_raito = sbtldbwk->all_dead_raito;
                  v51 = all_dead_raito * maxhp;
                  if ((u32)(v51 + 99) > 0xC6)
                    v52 = v51 / 100;
                  else
                    v52 = pUnit->para->now->hp - 1;
                  sBtlSetDamage(pUnit, 149, v52, 0);
                }
              }
            }
          }
        }
LABEL_64:
        ++v24;
        continue;
      }
    case 4:
      v26 = wk;
      timecount = v26->timecount;
      gb_btltime = timecount;
      return;
    default:
      return;
  }
}

// 0x190e320
void sBtlDebug_DrawONOFFList_Motion(MOTIONDATA_WORK *m_data, s32 x, s32 y, s32 num) {
  char *v8;
  char *v9;
  s64 v10;
  char **v11;
  char *v12;
  char *v13;
  s64 v14;
  s32 v15;
  s32 v16;
  u16 flg;
  char **v20;
  char *v21;

  v8 = NewSpecific(string, 3u);
  v9 = " ON";
  v10 = v8;
  v8[0] = " ON";
  v11 = &v8[0];
  v12 = "OFF";
  *(u64 *)(v10 + 40) = "OFF";
  v13 = "   ";
  *(u64 *)(v10 + 48) = "   ";
  if (num >= 1)
  {
    v14 = 0;
    v15 = 16 * x;
    v16 = 8 * y;
    do
    {
      flg = m_data->flg;
      v20 = (v10 + 40);
      if ((motion_flg[v14] & flg) != 0)
        v20 = v11;
      v21 = *v20;
      DbgText(v15, v16, v21, 0, 109, 24, 0);
      ++v14;
      v16 += 96;
    }
    while (num != v14);
  }
}

// 0x192a5b0
void sBtlDebug_DrawONOFFList_FLG(u32 flg, u32 *tbl, s32 x, s32 y, s32 num) {
  char *v11;
  char *v12;
  s64 v13;
  char **v14;
  char *v15;
  char **v16;
  char *v17;
  s64 v18;
  s32 v19;
  u32 *m_Items;
  s32 v21;
  s32 v22;
  char **v23;
  char *v24;

  v11 = NewSpecific(string, 3u);
  v12 = " ON";
  v13 = v11;
  v11[0] = " ON";
  v14 = &v11[0];
  v15 = "OFF";
  *(u64 *)(v13 + 40) = "OFF";
  v16 = (v13 + 40);
  v17 = "   ";
  *(u64 *)(v13 + 48) = "   ";
  if (num >= 1)
  {
    v18 = num;
    v19 = 16 * x;
    m_Items = tbl;
    v21 = 8 * y;
    do
    {
      v22 = *m_Items++;
      if ((v22 & flg) != 0)
        v23 = v14;
      else
        v23 = v16;
      v24 = *v23;
      DbgText(v19, v21, v24, 0, 109, 24, 0);
      --v18;
      v21 += 96;
    }
    while (v18);
  }
}

// 0x1906d00
static void sBtlDebug_DrawONOFFList(SBDEBUG_FLGWORK *wk, s32 num, s32 x, s32 y) {
  char *v9;
  char *v10;
  char *v11;
  s64 v12;
  char *v13;
  char *v14;
  u64 *v15;
  s32 v16;
  s64 v17;
  SBDEBUG_FLGWORK *m_Items;
  s32 v19;
  System_Int32_c **v20;
  SBDEBUG_FLGWORK *v21;
  char *v23;
  System_Int32_c **v25;
  char *v26;
  char *v27;
  char *v28;
  char *v29;
  u64 *v31;
  s64 stflg;
  char **v35;
  s32 enemy_stop_mode;
  char **v37;
  s32 hgun_num;
  s32 encountno;
  s32 mag;
  s16 equipgun;
  System_Int16_c *v48;
  Il2CppObject *v50;
  char **v51;
  SBATTLE_WORK *v53;
  u32 stock_mask;
  s32 v55;
  System_Int32_c *v57;
  sdatPlayerUnitWork_t *player;
  s32 v60;
  void **v63;
  bool bKyousei;
  void *v70;
  s32 rouletteId;
  s32 v73;
  char *v75;
  System_Int32_c *v78;
  Il2CppObject *v79;
  char *v80;
  System_Int32_c *v83;
  SBATTLE_WORK *v85;
  SBTLUNIT_LISTWORK *v86;
  s32 v87;
  SBTLUNIT_WORK *v88;
  Il2CppObject *v89;
  char *v90;
  s32 devilid;
  char **v93;
  System_Int32_c *v94;
  Il2CppObject *v95;
  Il2CppObject *v96;
  SBATTLE_WORK *v98;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 playerID;
  SBTLUNIT_WORK *v101;
  char *v102;
  System_Int32_c *v103;
  s32 v104;
  s32 v105;
  s32 v106;
  s32 v107;
  s32 v108;
  s32 v109;
  s32 v110;
  s32 v111;
  s32 v112;
  s32 v113;
  s32 v114;
  s32 v115;
  s32 v116;
  s32 v117;
  s32 v118;
  s32 v119;
  s32 v120;
  s32 v121;
  s32 v122;
  s32 v123;
  s32 v124;
  s32 v125;
  s32 v126;
  s32 v127;
  s32 v128;
  s32 v129;
  s32 v130;
  s32 v131;
  s32 v132;
  s32 v133;
  s32 v134;
  s32 v135;
  System_Int32_c *v136;
  System_Int32_c *v137;
  System_Int32_c *v138;
  System_Int32_c *v139;
  System_Int32_c *v140;
  System_Int32_c *v141;
  System_Int32_c *v142;
  System_Int32_c *v143;
  System_Int32_c *v144;
  System_Int32_c *v145;
  System_Int32_c *v146;
  System_Int32_c *v147;
  System_Int32_c *v148;
  System_Int32_c *v149;
  System_Int32_c *v150;
  System_Int32_c *v151;
  System_Int32_c *v152;
  System_Int32_c *v153;
  System_Int32_c *v154;
  System_Int32_c *v155;
  System_Int32_c *v156;
  System_Int32_c *v157;
  System_Int32_c *v158;
  System_Int32_c *v159;
  System_Int32_c *v160;
  System_Int32_c *v161;
  System_Int32_c *v162;
  System_Int32_c *v163;
  System_Int32_c *v164;
  System_Int32_c *v165;
  System_Int32_c *v166;
  System_Int32_c *v167;
  System_Int32_c *v168;
  char **v169;
  char **v170;
  u32 data;
  s32 Light;

  Light = 0;
  v9 = "";
  v10 = NewSpecific(string, 3u);
  v11 = " ON";
  v12 = v10;
  v10[0] = " ON";
  v170 = &v10[0];
  v13 = "OFF";
  *(u64 *)(v12 + 40) = "OFF";
  v169 = (v12 + 40);
  v14 = "   ";
  *(u64 *)(v12 + 48) = "   ";
  v15 = (v12 + 48);
  if (num >= 1)
  {
    v16 = 16 * x;
    v17 = num;
    m_Items = wk;
    v19 = 8 * y;
    v20 = &s32;
    while (1)
    {
      v21 = m_Items;
      switch (m_Items->sttype)
      {
        case 0:
          if (v21->mode == 3)
          {
            v23 = ToString_55996800((s32)&sbtldbwk->all_dead_raito, "d3", 0);
            v25 = v20;
            v26 = ToString((u32)fldGb + 108, 0);
            v27 = Concat_54831728(v23, " fld:", v26, 0);
            v28 = ToString((u32)fldGb + 116, 0);
            v29 = Concat_54831728(v27, " flw:", v28, 0);
            v31 = v15;
            v98 = wk;
            UnitMng = v98->UnitMng;
            playerID = v98->playerID;
            v101 = sBtlSearchUnit_ID(UnitMng, playerID);
            Light = mapGetLight(v101->pos.x, v101->pos.z);
            v102 = ToString((s32)&Light, 0);
            v80 = Concat_54831728(v29, " lightid:", v102, 0);
            v15 = v31;
            v20 = v25;
            goto LABEL_108;
          }
          v9 = *v15;
          goto LABEL_109;
        case 1:
          v21 = m_Items;
          stflg = v21->stflg;
          v35 = v170;
          if ((stflg & sbtldbwk->status) == 0)
            v35 = v169;
          v9 = *v35;
          if ((stflg & 0x40000) == 0)
            goto LABEL_109;
          enemy_stop_mode = sbtldbwk->enemy_stop_mode;
          if (enemy_stop_mode == 1)
          {
            v37 = &"(ZAKO)";
            goto LABEL_145;
          }
          if (!enemy_stop_mode)
          {
            v37 = &"(ALL)";
LABEL_145:
            v80 = Concat_54766928(v9, *v37, 0);
            goto LABEL_108;
          }
LABEL_109:
          DbgText(v16, v19, v9, 0, 109, 24, 0);
          ++m_Items;
          --v17;
          v19 += 96;
          if (!v17)
            return;
          break;
        case 2:
          if ((v21->stflg & sbtldbwk->unitst) == 0)
            goto LABEL_59;
          goto LABEL_27;
        case 3:
          hgun_num = wk->hgun_num;
          goto LABEL_98;
        case 4:
          hgun_num = wk->mgun_num;
          goto LABEL_98;
        case 5:
          encountno = wk->encountno;
          goto LABEL_63;
        case 6:
          mag = wk->mag;
          goto LABEL_50;
        case 7:
          equipgun = wk->equipgun;
          goto LABEL_46;
        case 8:
          equipgun = wk->equipsord;
LABEL_46:
          LOWORD(data) = equipgun;
          goto LABEL_51;
        case 9:
          mag = wk->stock_num;
LABEL_50:
          v48 = *v20;
          data = mag;
LABEL_51:
          v50 = Box(v48, &data);
          v51 = &"{0}";
          goto LABEL_106;
        case 0xA:
          v53 = wk;
          stock_mask = v53->stock_mask;
          v55 = v53->summonindex[0];
          if (!!sBtlCheckBit(stock_mask, v55))
          {
            v85 = wk;
            v86 = v85->UnitMng;
            v87 = v85->summonID[v85->summonindex[0]];
            v88 = sBtlSearchUnit_ID(v86, v87);
            if (v88)
            {
              LOBYTE(data) = v88->para->seikaku;
              v89 = Box(sbyte, &data);
              v90 = Format("{0:D3}", v89, 0);
              goto LABEL_135;
            }
          }
          v93 = &"NON";
LABEL_148:
          v9 = *v93;
          goto LABEL_109;
        case 0xB:
          if ((v21->stflg & sbtldbwk->y_status) != 0)
            goto LABEL_27;
          goto LABEL_9003;
          if ((m_Items->stflg & sbtldbwk->y_status) != 0)
          {
LABEL_27:
            v9 = *v170;
            goto LABEL_109;
          }
LABEL_9003:
LABEL_59:
          v9 = *v169;
          goto LABEL_109;
        case 0xC:
          encountno = wk->battlemode;
LABEL_63:
          v57 = *v20;
          data = encountno;
          v50 = Box(v57, &data);
          v51 = &"0x{0:X2}";
          goto LABEL_106;
        case 0xD:
          player = GBWK->player;
          v60 = player->stack_p[0];
          if (v60 < 0)
            goto LABEL_136;
          goto LABEL_131;
        case 0xE:
          player = GBWK->player;
          v60 = player->stack_p[1];
          if (v60 < 0)
            goto LABEL_136;
          goto LABEL_9004;
          if (v60 < 0)
          {
LABEL_136:
            v9 = "---";
            goto LABEL_109;
          }
LABEL_9004:
LABEL_131:
          devilid = player->stock_id[(s16)v60]->devilid;
          if (devilid < 0)
          {
            v93 = &"---";
            goto LABEL_148;
          }
          v94 = *v20;
          data = devilid;
          v95 = Box(v94, &data);
          v96 = sdatDevilName(devilid, 0);
          v90 = Format_54759776("0x{0:X2} {1:%s}", v95, v96, 0);
LABEL_135:
          v9 = v90;
          goto LABEL_109;
        case 0xF:
          data = sbtldbwk->raidouP;
          v63 = &uint;
          goto LABEL_89;
        case 0x10:
          hgun_num = sbtldbwk->mapmdl;
          goto LABEL_98;
        case 0x11:
          hgun_num = sbtldbwk->weaponId;
          goto LABEL_98;
        case 0x12:
          bKyousei = sbtldbwk->bKyousei;
          goto LABEL_88;
        case 0x13:
          LOBYTE(data) = wk->senseimode;
          v63 = &sbyte;
          goto LABEL_89;
        case 0x14:
          bKyousei = sbtldbwk->bBossDbg;
LABEL_88:
          LOBYTE(data) = bKyousei;
          v63 = &bool;
LABEL_89:
          v70 = *v63;
          goto LABEL_99;
        case 0x15:
          rouletteId = wk->rouletteId;
          switch (rouletteId)
          {
            case 1:
              v73 = 1;
              v136 = *v20;
              data = v73;
              v50 = Box(v136, &data);
              v51 = &"{0:D2} G KAISIN";
              break;
            case 2:
              v104 = 2;
              v137 = *v20;
              data = v104;
              v50 = Box(v137, &data);
              v51 = &"{0:D2} G MAG UP";
              break;
            case 3:
              v105 = 3;
              v138 = *v20;
              data = v105;
              v50 = Box(v138, &data);
              v51 = &"{0:D2} G EXP UP";
              break;
            case 4:
              v106 = 4;
              v139 = *v20;
              data = v106;
              v50 = Box(v139, &data);
              v51 = &"{0:D2} G CYUUSEI UP";
              break;
            case 5:
              v107 = 5;
              v140 = *v20;
              data = v107;
              v50 = Box(v140, &data);
              v51 = &"{0:D2} G NAME A";
              break;
            case 6:
              v108 = 6;
              v141 = *v20;
              data = v108;
              v50 = Box(v141, &data);
              v51 = &"{0:D2} G NAME KA";
              break;
            case 7:
              v109 = 7;
              v142 = *v20;
              data = v109;
              v50 = Box(v142, &data);
              v51 = &"{0:D2} G NAME SA";
              break;
            case 8:
              v110 = 8;
              v143 = *v20;
              data = v110;
              v50 = Box(v143, &data);
              v51 = &"{0:D2} G NAME TA";
              break;
            case 9:
              v111 = 9;
              v144 = *v20;
              data = v111;
              v50 = Box(v144, &data);
              v51 = &"{0:D2} G NAME NA";
              break;
            case 10:
              v112 = 10;
              v145 = *v20;
              data = v112;
              v50 = Box(v145, &data);
              v51 = &"{0:D2} G NAME HA";
              break;
            case 11:
              v113 = 11;
              v146 = *v20;
              data = v113;
              v50 = Box(v146, &data);
              v51 = &"{0:D2} G NAME MA";
              break;
            case 12:
              v114 = 12;
              v147 = *v20;
              data = v114;
              v50 = Box(v147, &data);
              v51 = &"{0:D2} G NAME YA";
              break;
            case 13:
              v115 = 13;
              v148 = *v20;
              data = v115;
              v50 = Box(v148, &data);
              v51 = &"{0:D2} G NAME RA";
              break;
            case 14:
              v116 = 14;
              v149 = *v20;
              data = v116;
              v50 = Box(v149, &data);
              v51 = &"{0:D2} G MONEY UP";
              break;
            case 15:
              v117 = 15;
              v150 = *v20;
              data = v117;
              v50 = Box(v150, &data);
              v51 = &"{0:D2} G ITEM UP";
              break;
            case 16:
              v118 = 16;
              v151 = *v20;
              data = v118;
              v50 = Box(v151, &data);
              v51 = &"{0:D2} G TALK UP";
              break;
            case 17:
              v119 = 17;
              v152 = *v20;
              data = v119;
              v50 = Box(v152, &data);
              v51 = &"{0:D2} G TENBATU";
              break;
            case 18:
              v120 = 18;
              v153 = *v20;
              data = v120;
              v50 = Box(v153, &data);
              v51 = &"{0:D2} B SUKA";
              break;
            case 19:
              v121 = 19;
              v154 = *v20;
              data = v121;
              v50 = Box(v154, &data);
              v51 = &"{0:D2} B BOUDO";
              break;
            case 20:
              v122 = 20;
              v155 = *v20;
              data = v122;
              v50 = Box(v155, &data);
              v51 = &"{0:D2} B MAIGO";
              break;
            case 21:
              v123 = 21;
              v156 = *v20;
              data = v123;
              v50 = Box(v156, &data);
              v51 = &"{0:D2} B K GUREN";
              break;
            case 22:
              v124 = 22;
              v157 = *v20;
              data = v124;
              v50 = Box(v157, &data);
              v51 = &"{0:D2} B K GINHYOU";
              break;
            case 23:
              v125 = 23;
              v158 = *v20;
              data = v125;
              v50 = Box(v158, &data);
              v51 = &"{0:D2} B K RAIDEN";
              break;
            case 24:
              v126 = 24;
              v159 = *v20;
              data = v126;
              v50 = Box(v159, &data);
              v51 = &"{0:D2} B K SIPUU";
              break;
            case 25:
              v127 = 25;
              v160 = *v20;
              data = v127;
              v50 = Box(v160, &data);
              v51 = &"{0:D2} B K BANRIKI";
              break;
            case 26:
              v128 = 26;
              v161 = *v20;
              data = v128;
              v50 = Box(v161, &data);
              v51 = &"{0:D2} B K GEHOU";
              break;
            case 27:
              v129 = 27;
              v162 = *v20;
              data = v129;
              v50 = Box(v162, &data);
              v51 = &"{0:D2} B K GIGEI";
              break;
            case 28:
              v130 = 28;
              v163 = *v20;
              data = v130;
              v50 = Box(v163, &data);
              v51 = &"{0:D2} B K SEIREI";
              break;
            case 29:
              v131 = 29;
              v164 = *v20;
              data = v131;
              v50 = Box(v164, &data);
              v51 = &"{0:D2} B K MITAMA";
              break;
            case 30:
              v132 = 30;
              v165 = *v20;
              data = v132;
              v50 = Box(v165, &data);
              v51 = &"{0:D2} B K MAJIN";
              break;
            case 31:
              v133 = 31;
              v166 = *v20;
              data = v133;
              v50 = Box(v166, &data);
              v51 = &"{0:D2} B K MAGATSU";
              break;
            case 32:
              v134 = 32;
              v167 = *v20;
              data = v134;
              v50 = Box(v167, &data);
              v51 = &"{0:D2} B NO ITEM";
              break;
            case 33:
              v135 = 33;
              v168 = *v20;
              data = v135;
              v50 = Box(v168, &data);
              v51 = &"{0:D2} B NO ESC";
              break;
            default:
              rouletteId = wk->rouletteId;
              v103 = *v20;
              data = rouletteId;
              v50 = Box(v103, &data);
              v51 = &"{0:D2}";
              break;
          }
          goto LABEL_106;
        case 0x16:
          hgun_num = sbtldbwk->dlcsel;
LABEL_98:
          v70 = *v20;
          data = hgun_num;
LABEL_99:
          v50 = Box(v70, &data);
          v75 = "{0:D3}";
          goto LABEL_107;
        case 0x17:
          v78 = *v20;
          data = sbtldbwk->CmbSklSet;
          v79 = Box(v78, &data);
          v80 = Format_54759776("{0:D2} {1:%s}", v79, gDbg_Spirit_Table[sbtldbwk->CmbSklSet]->skillName, 0);
          goto LABEL_108;
        case 0x1F:
          v83 = *v20;
          data = sbtldbwk->set_mag;
          v50 = Box(v83, &data);
          v51 = &"{0:D1}";
LABEL_106:
          v75 = *v51;
LABEL_107:
          v80 = Format(v75, v50, 0);
LABEL_108:
          v9 = v80;
          goto LABEL_109;
        default:
          goto LABEL_109;
      }
    }
  }
}

// 0x192a780
bool sbattleCheckDebugMode(SBDEBUG_MODE mode) {
  return sbtldbwk->mode == mode;
}

// 0x192a800
void sBtlDebug_ScreenPrintf(s32 x, s32 y, s32 attr, char *str, void *LegacyParamArray) {
  ;
}

// 0x192a810
void sbattleTextDraw(s32 x, s32 y, s32 attr, s8 str) {
  ;
}

// 0x19283f0
void sbattleInitRunTime(void) {
  ;
}

// 0x192a820
s32 sbattleSetRunTimeBase(void) {
  return 0;
}

// 0x192a830
s32 sBtlDebug_GetRunTime(void) {
  return 0;
}

// 0x192a840
s32 sbattlePrintfRunTime(char *str, void *LegacyParamArray) {
  return 0;
}

// 0x192a850
void sbattleRunTimePrint_Debug(void) {
  ;
}

// 0x192a860
void sbattleCreateFile_RunTime(void) {
  ;
}

// 0x192a870
bool sBtlDebug_UnitUPPanelDraw(SBTLUNIT_WORK *wk) {
  return 1;
}

// 0x192a880
bool sbattleDrawTriangle(const sdfVector4_t *pos0, const sdfVector4_t *pos1, const sdfVector4_t *pos2, s32 rgba0, s32 rgba1, s32 rgba2) {
  return 1;
}

// 0x192a900
bool sBtlDebug_DrawSphere_LineY(const sdfVector4_t *pos, f32 r, u32 rgba, f32 deg) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  f32 *p_x;
  f32 *v13;
  f32 v14;
  f32 v15;
  f32 v16;
  f32 v17;
  f32 v18;
  _OWORD *v20;
  f32 v21;
  f32 v22;
  f32 v23;
  f32 v24;
  s32 v25;
  f32 *v27;
  __int128 v29;
  _OWORD *v30;
  s32 v31;
  __int128 v32;
  f32 *v34;
  SBTLDEBUG_WORK *sbtldbwk_local;
  __int128 v38;
  __int128 v39;
  __int128 v41;
  _OWORD *v42;
  s32 v43;
  __int128 v44;
  f32 *v45;
  u32 v47;
  __int128 v48;
  _OWORD *v49;
  s32 v50;
  __int128 v51;
  f32 *v53;
  SBTLDEBUG_WORK *v54;
  __int128 v56;
  __int128 v57;
  __int128 v59;
  _OWORD *v60;
  s32 v61;
  __int128 v62;
  f32 *v64;
  u32 v65;
  __int128 v66;
  _OWORD *v67;
  s32 v68;
  __int128 v69;
  f32 *v70;
  struct sdfVector4_t v80;
  __int128 v82;
  __int128 v83;
  __int128 v84;
  __int128 v85;
  sdfMatrix4_t v86;
  sdfMatrix4_t v87;
  sdfVector4_t v88;
  sdfVector4_t v89;
  sdfVector4_t v90;
  sdfVector4_t v91;
  sdfVector4_t v92;
  sdfVector4_t v94;
  sdfVector4_t v95;
  sdfVector4_t v96;
  sdfVector4_t v97;

  w = pos->w;
  z = pos->z;
  y = pos->y;
  x = pos->x;
  p_x = &vf00.x;
  p_x[4] = x;
  p_x[5] = y;
  p_x[6] = z;
  p_x[7] = w;
  v13 = &vf00.x;
  v14 = v13[4];
  v15 = v13[5];
  v16 = v13[6];
  v17 = v13[7];
  v18 = deg * 0.017453292;
  sub_19493E0(0, v18);
  v20 = &vf00.x;
  v21 = 1.0;
  v22 = 0.0;
  v23 = 0.0;
  v24 = 0.0;
  v25 = 12;
  v82 = v20[4];
  v83 = v20[5];
  v84 = v20[6];
  v85 = v20[7];
  do
  {
    v27 = &vf00.x;
    v27[4] = v24;
    v27[5] = v23;
    v27[6] = v21;
    v27[7] = v22;
    *(_OWORD *)&v87.m00 = v82;
    *(_OWORD *)&v87.m01 = v83;
    *(_OWORD *)&v87.m02 = v84;
    *(_OWORD *)&v87.m03 = v85;
    v29 = *(_OWORD *)&v87.m01;
    v30 = &vf00.x;
    v31 = (u8)byte_5756085;
    v30[4] = *(_OWORD *)&v87.m00;
    v30[5] = v29;
    v32 = *(_OWORD *)&v87.m03;
    v30[6] = *(_OWORD *)&v87.m02;
    v30[7] = v32;
    if (v31)
    {
      goto LABEL_19;
    }
    else
    {
      goto LABEL_19;
    }
LABEL_19:
    get_transpose(&v87, &mtx_A, 0);
    v86 = v87;
    v88 = op_Multiply_60923920(&v86, vct_A, 0);
    vct_A = v88;
    vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, r);
    v34 = &vf00.x;
    v34[8] = v14;
    v34[9] = v15;
    v34[10] = v16;
    v34[11] = v17;
    vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    sbtldbwk_local = sbtldbwk;
    v38 = *(_OWORD *)&sbtldbwk_local->mat.m01;
    *(_OWORD *)&v87.m00 = *(_OWORD *)&sbtldbwk_local->mat.m00;
    *(_OWORD *)&v87.m01 = v38;
    v39 = *(_OWORD *)&sbtldbwk_local->mat.m03;
    *(_OWORD *)&v87.m02 = *(_OWORD *)&sbtldbwk_local->mat.m02;
    *(_OWORD *)&v87.m03 = v39;
    v41 = *(_OWORD *)&v87.m01;
    v42 = &vf00.x;
    v43 = (u8)byte_5755EF5;
    v42[4] = *(_OWORD *)&v87.m00;
    v42[5] = v41;
    v44 = *(_OWORD *)&v87.m03;
    v42[6] = *(_OWORD *)&v87.m02;
    v42[7] = v44;
    if (v43)
    {
      goto LABEL_33;
    }
    else
    {
      goto LABEL_33;
    }
LABEL_33:
    v45 = &vf00.x;
    v45[4] = v24;
    v45[5] = v23;
    v45[6] = v21;
    v45[7] = v22;
    get_transpose(&v87, &mtx_A, 0);
    v94 = vct_A;
    v86 = v87;
    v89 = op_Multiply_60923920(&v86, v94, 0);
    vct_A = v89;
    v80 = vct_A;
    *(_OWORD *)&v87.m00 = v82;
    *(_OWORD *)&v87.m01 = v83;
    *(_OWORD *)&v87.m02 = v84;
    *(_OWORD *)&v87.m03 = v85;
    if (v47)
    v48 = *(_OWORD *)&v87.m01;
    v49 = &vf00.x;
    v50 = (u8)byte_5756085;
    v49[4] = *(_OWORD *)&v87.m00;
    v49[5] = v48;
    v51 = *(_OWORD *)&v87.m03;
    v49[6] = *(_OWORD *)&v87.m02;
    v49[7] = v51;
    if (v50)
    {
      goto LABEL_41;
    }
    else
    {
      goto LABEL_41;
    }
LABEL_41:
    get_transpose(&v87, &mtx_A, 0);
    v95 = vct_A;
    v86 = v87;
    v90 = op_Multiply_60923920(&v86, v95, 0);
    vct_A = v90;
    vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, r);
    v53 = &vf00.x;
    v53[8] = v14;
    v53[9] = v15;
    v53[10] = v16;
    v53[11] = v17;
    vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    v54 = sbtldbwk;
    v56 = *(_OWORD *)&v54->mat.m01;
    *(_OWORD *)&v87.m00 = *(_OWORD *)&v54->mat.m00;
    *(_OWORD *)&v87.m01 = v56;
    v57 = *(_OWORD *)&v54->mat.m03;
    *(_OWORD *)&v87.m02 = *(_OWORD *)&v54->mat.m02;
    *(_OWORD *)&v87.m03 = v57;
    v59 = *(_OWORD *)&v87.m01;
    v60 = &vf00.x;
    v61 = (u8)byte_5755EF5;
    v60[4] = *(_OWORD *)&v87.m00;
    v60[5] = v59;
    v62 = *(_OWORD *)&v87.m03;
    v60[6] = *(_OWORD *)&v87.m02;
    v60[7] = v62;
    if (v61)
    {
      goto LABEL_54;
    }
    else
    {
LABEL_54:
      vct_A = v80;
      goto LABEL_55;
    }
    vct_A = v80;
LABEL_55:
    get_transpose(&v87, &mtx_A, 0);
    v96 = vct_A;
    v86 = v87;
    v91 = op_Multiply_60923920(&v86, v96, 0);
    vct_A = v91;
    v64 = &vf00.x;
    v24 = v64[4];
    v23 = v64[5];
    v21 = v64[6];
    v22 = v64[7];
    *(_OWORD *)&v87.m00 = v82;
    *(_OWORD *)&v87.m01 = v83;
    *(_OWORD *)&v87.m02 = v84;
    *(_OWORD *)&v87.m03 = v85;
    if (v65)
    v66 = *(_OWORD *)&v87.m01;
    v67 = &vf00.x;
    v68 = (u8)byte_5756085;
    v67[4] = *(_OWORD *)&v87.m00;
    v67[5] = v66;
    v69 = *(_OWORD *)&v87.m03;
    v67[6] = *(_OWORD *)&v87.m02;
    v67[7] = v69;
    if (v68)
    {
      goto LABEL_62;
    }
    else
    {
      goto LABEL_62;
    }
LABEL_62:
    get_transpose(&v87, &mtx_A, 0);
    v97 = vct_A;
    v86 = v87;
    v92 = op_Multiply_60923920(&v86, v97, 0);
    vct_A = v92;
    vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, r);
    v70 = &vf00.x;
    v70[8] = v14;
    v70[9] = v15;
    v70[10] = v16;
    v70[11] = v17;
    vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    --v25;
  }
  while (v25);
  return 1;
}

// 0x192b5a0
bool sBtlDebug_DrawSphere_LineZ(const sdfVector4_t *pos, f32 r, u32 rgba, f32 deg) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  f32 *p_x;
  f32 *v13;
  f32 v14;
  f32 v15;
  f32 v16;
  f32 v17;
  f32 v18;
  _OWORD *v20;
  f32 v21;
  f32 v22;
  f32 v23;
  f32 v24;
  s32 v25;
  f32 *v27;
  __int128 v29;
  _OWORD *v30;
  s32 v31;
  __int128 v32;
  f32 *v34;
  SBTLDEBUG_WORK *sbtldbwk_local;
  __int128 v38;
  __int128 v39;
  __int128 v41;
  _OWORD *v42;
  s32 v43;
  __int128 v44;
  f32 *v45;
  u32 v47;
  __int128 v48;
  _OWORD *v49;
  s32 v50;
  __int128 v51;
  f32 *v53;
  SBTLDEBUG_WORK *v54;
  __int128 v56;
  __int128 v57;
  __int128 v59;
  _OWORD *v60;
  s32 v61;
  __int128 v62;
  f32 *v64;
  u32 v65;
  __int128 v66;
  _OWORD *v67;
  s32 v68;
  __int128 v69;
  f32 *v70;
  struct sdfVector4_t v80;
  __int128 v82;
  __int128 v83;
  __int128 v84;
  __int128 v85;
  sdfMatrix4_t v86;
  sdfMatrix4_t v87;
  sdfVector4_t v88;
  sdfVector4_t v89;
  sdfVector4_t v90;
  sdfVector4_t v91;
  sdfVector4_t v92;
  sdfVector4_t v94;
  sdfVector4_t v95;
  sdfVector4_t v96;
  sdfVector4_t v97;

  w = pos->w;
  z = pos->z;
  y = pos->y;
  x = pos->x;
  p_x = &vf00.x;
  p_x[4] = x;
  p_x[5] = y;
  p_x[6] = z;
  p_x[7] = w;
  v13 = &vf00.x;
  v14 = v13[4];
  v15 = v13[5];
  v16 = v13[6];
  v17 = v13[7];
  v18 = deg * 0.017453292;
  sub_1949540(0, v18);
  v20 = &vf00.x;
  v21 = 1.0;
  v22 = 0.0;
  v23 = 0.0;
  v24 = 0.0;
  v25 = 12;
  v82 = v20[4];
  v83 = v20[5];
  v84 = v20[6];
  v85 = v20[7];
  do
  {
    v27 = &vf00.x;
    v27[4] = v24;
    v27[5] = v21;
    v27[6] = v23;
    v27[7] = v22;
    *(_OWORD *)&v87.m00 = v82;
    *(_OWORD *)&v87.m01 = v83;
    *(_OWORD *)&v87.m02 = v84;
    *(_OWORD *)&v87.m03 = v85;
    v29 = *(_OWORD *)&v87.m01;
    v30 = &vf00.x;
    v31 = (u8)byte_5756085;
    v30[4] = *(_OWORD *)&v87.m00;
    v30[5] = v29;
    v32 = *(_OWORD *)&v87.m03;
    v30[6] = *(_OWORD *)&v87.m02;
    v30[7] = v32;
    if (v31)
    {
      goto LABEL_19;
    }
    else
    {
      goto LABEL_19;
    }
LABEL_19:
    get_transpose(&v87, &mtx_A, 0);
    v86 = v87;
    v88 = op_Multiply_60923920(&v86, vct_A, 0);
    vct_A = v88;
    vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, r);
    v34 = &vf00.x;
    v34[8] = v14;
    v34[9] = v15;
    v34[10] = v16;
    v34[11] = v17;
    vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    sbtldbwk_local = sbtldbwk;
    v38 = *(_OWORD *)&sbtldbwk_local->mat2.m01;
    *(_OWORD *)&v87.m00 = *(_OWORD *)&sbtldbwk_local->mat2.m00;
    *(_OWORD *)&v87.m01 = v38;
    v39 = *(_OWORD *)&sbtldbwk_local->mat2.m03;
    *(_OWORD *)&v87.m02 = *(_OWORD *)&sbtldbwk_local->mat2.m02;
    *(_OWORD *)&v87.m03 = v39;
    v41 = *(_OWORD *)&v87.m01;
    v42 = &vf00.x;
    v43 = (u8)byte_5755EF5;
    v42[4] = *(_OWORD *)&v87.m00;
    v42[5] = v41;
    v44 = *(_OWORD *)&v87.m03;
    v42[6] = *(_OWORD *)&v87.m02;
    v42[7] = v44;
    if (v43)
    {
      goto LABEL_33;
    }
    else
    {
      goto LABEL_33;
    }
LABEL_33:
    v45 = &vf00.x;
    v45[4] = v24;
    v45[5] = v21;
    v45[6] = v23;
    v45[7] = v22;
    get_transpose(&v87, &mtx_A, 0);
    v94 = vct_A;
    v86 = v87;
    v89 = op_Multiply_60923920(&v86, v94, 0);
    vct_A = v89;
    v80 = vct_A;
    *(_OWORD *)&v87.m00 = v82;
    *(_OWORD *)&v87.m01 = v83;
    *(_OWORD *)&v87.m02 = v84;
    *(_OWORD *)&v87.m03 = v85;
    if (v47)
    v48 = *(_OWORD *)&v87.m01;
    v49 = &vf00.x;
    v50 = (u8)byte_5756085;
    v49[4] = *(_OWORD *)&v87.m00;
    v49[5] = v48;
    v51 = *(_OWORD *)&v87.m03;
    v49[6] = *(_OWORD *)&v87.m02;
    v49[7] = v51;
    if (v50)
    {
      goto LABEL_41;
    }
    else
    {
      goto LABEL_41;
    }
LABEL_41:
    get_transpose(&v87, &mtx_A, 0);
    v95 = vct_A;
    v86 = v87;
    v90 = op_Multiply_60923920(&v86, v95, 0);
    vct_A = v90;
    vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, r);
    v53 = &vf00.x;
    v53[8] = v14;
    v53[9] = v15;
    v53[10] = v16;
    v53[11] = v17;
    vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    v54 = sbtldbwk;
    v56 = *(_OWORD *)&v54->mat2.m01;
    *(_OWORD *)&v87.m00 = *(_OWORD *)&v54->mat2.m00;
    *(_OWORD *)&v87.m01 = v56;
    v57 = *(_OWORD *)&v54->mat2.m03;
    *(_OWORD *)&v87.m02 = *(_OWORD *)&v54->mat2.m02;
    *(_OWORD *)&v87.m03 = v57;
    v59 = *(_OWORD *)&v87.m01;
    v60 = &vf00.x;
    v61 = (u8)byte_5755EF5;
    v60[4] = *(_OWORD *)&v87.m00;
    v60[5] = v59;
    v62 = *(_OWORD *)&v87.m03;
    v60[6] = *(_OWORD *)&v87.m02;
    v60[7] = v62;
    if (v61)
    {
      goto LABEL_54;
    }
    else
    {
LABEL_54:
      vct_A = v80;
      goto LABEL_55;
    }
    vct_A = v80;
LABEL_55:
    get_transpose(&v87, &mtx_A, 0);
    v96 = vct_A;
    v86 = v87;
    v91 = op_Multiply_60923920(&v86, v96, 0);
    vct_A = v91;
    v64 = &vf00.x;
    v24 = v64[4];
    v21 = v64[5];
    v23 = v64[6];
    v22 = v64[7];
    *(_OWORD *)&v87.m00 = v82;
    *(_OWORD *)&v87.m01 = v83;
    *(_OWORD *)&v87.m02 = v84;
    *(_OWORD *)&v87.m03 = v85;
    if (v65)
    v66 = *(_OWORD *)&v87.m01;
    v67 = &vf00.x;
    v68 = (u8)byte_5756085;
    v67[4] = *(_OWORD *)&v87.m00;
    v67[5] = v66;
    v69 = *(_OWORD *)&v87.m03;
    v67[6] = *(_OWORD *)&v87.m02;
    v67[7] = v69;
    if (v68)
    {
      goto LABEL_62;
    }
    else
    {
      goto LABEL_62;
    }
LABEL_62:
    get_transpose(&v87, &mtx_A, 0);
    v97 = vct_A;
    v86 = v87;
    v92 = op_Multiply_60923920(&v86, v97, 0);
    vct_A = v92;
    vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, r);
    v70 = &vf00.x;
    v70[8] = v14;
    v70[9] = v15;
    v70[10] = v16;
    v70[11] = v17;
    vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    --v25;
  }
  while (v25);
  return 1;
}

// 0x192c240
bool sBtlDebug_DrawSphere_LineX(const sdfVector4_t *pos, f32 r, u32 rgba, f32 deg) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  f32 *p_x;
  f32 *v13;
  f32 v14;
  f32 v15;
  f32 v16;
  f32 v17;
  f32 v18;
  _OWORD *v20;
  f32 v21;
  f32 v22;
  f32 v23;
  f32 v24;
  s32 v25;
  f32 *v27;
  __int128 v29;
  _OWORD *v30;
  s32 v31;
  __int128 v32;
  f32 *v34;
  SBTLDEBUG_WORK *sbtldbwk_local;
  __int128 v38;
  __int128 v39;
  __int128 v41;
  _OWORD *v42;
  s32 v43;
  __int128 v44;
  f32 *v45;
  u32 v47;
  __int128 v48;
  _OWORD *v49;
  s32 v50;
  __int128 v51;
  f32 *v53;
  SBTLDEBUG_WORK *v54;
  __int128 v56;
  __int128 v57;
  __int128 v59;
  _OWORD *v60;
  s32 v61;
  __int128 v62;
  f32 *v64;
  u32 v65;
  __int128 v66;
  _OWORD *v67;
  s32 v68;
  __int128 v69;
  f32 *v70;
  struct sdfVector4_t v80;
  __int128 v82;
  __int128 v83;
  __int128 v84;
  __int128 v85;
  sdfMatrix4_t v86;
  sdfMatrix4_t v87;
  sdfVector4_t v88;
  sdfVector4_t v89;
  sdfVector4_t v90;
  sdfVector4_t v91;
  sdfVector4_t v92;
  sdfVector4_t v94;
  sdfVector4_t v95;
  sdfVector4_t v96;
  sdfVector4_t v97;

  w = pos->w;
  z = pos->z;
  y = pos->y;
  x = pos->x;
  p_x = &vf00.x;
  p_x[4] = x;
  p_x[5] = y;
  p_x[6] = z;
  p_x[7] = w;
  v13 = &vf00.x;
  v14 = v13[4];
  v15 = v13[5];
  v16 = v13[6];
  v17 = v13[7];
  v18 = deg * 0.017453292;
  sub_1949280(0, v18);
  v20 = &vf00.x;
  v21 = 1.0;
  v22 = 0.0;
  v23 = 0.0;
  v24 = 0.0;
  v25 = 12;
  v82 = v20[4];
  v83 = v20[5];
  v84 = v20[6];
  v85 = v20[7];
  do
  {
    v27 = &vf00.x;
    v27[4] = v24;
    v27[5] = v21;
    v27[6] = v23;
    v27[7] = v22;
    *(_OWORD *)&v87.m00 = v82;
    *(_OWORD *)&v87.m01 = v83;
    *(_OWORD *)&v87.m02 = v84;
    *(_OWORD *)&v87.m03 = v85;
    v29 = *(_OWORD *)&v87.m01;
    v30 = &vf00.x;
    v31 = (u8)byte_5756085;
    v30[4] = *(_OWORD *)&v87.m00;
    v30[5] = v29;
    v32 = *(_OWORD *)&v87.m03;
    v30[6] = *(_OWORD *)&v87.m02;
    v30[7] = v32;
    if (v31)
    {
      goto LABEL_19;
    }
    else
    {
      goto LABEL_19;
    }
LABEL_19:
    get_transpose(&v87, &mtx_A, 0);
    v86 = v87;
    v88 = op_Multiply_60923920(&v86, vct_A, 0);
    vct_A = v88;
    vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, r);
    v34 = &vf00.x;
    v34[8] = v14;
    v34[9] = v15;
    v34[10] = v16;
    v34[11] = v17;
    vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    sbtldbwk_local = sbtldbwk;
    v38 = *(_OWORD *)&sbtldbwk_local->mat3.m01;
    *(_OWORD *)&v87.m00 = *(_OWORD *)&sbtldbwk_local->mat3.m00;
    *(_OWORD *)&v87.m01 = v38;
    v39 = *(_OWORD *)&sbtldbwk_local->mat3.m03;
    *(_OWORD *)&v87.m02 = *(_OWORD *)&sbtldbwk_local->mat3.m02;
    *(_OWORD *)&v87.m03 = v39;
    v41 = *(_OWORD *)&v87.m01;
    v42 = &vf00.x;
    v43 = (u8)byte_5755EF5;
    v42[4] = *(_OWORD *)&v87.m00;
    v42[5] = v41;
    v44 = *(_OWORD *)&v87.m03;
    v42[6] = *(_OWORD *)&v87.m02;
    v42[7] = v44;
    if (v43)
    {
      goto LABEL_33;
    }
    else
    {
      goto LABEL_33;
    }
LABEL_33:
    v45 = &vf00.x;
    v45[4] = v24;
    v45[5] = v21;
    v45[6] = v23;
    v45[7] = v22;
    get_transpose(&v87, &mtx_A, 0);
    v94 = vct_A;
    v86 = v87;
    v89 = op_Multiply_60923920(&v86, v94, 0);
    vct_A = v89;
    v80 = vct_A;
    *(_OWORD *)&v87.m00 = v82;
    *(_OWORD *)&v87.m01 = v83;
    *(_OWORD *)&v87.m02 = v84;
    *(_OWORD *)&v87.m03 = v85;
    if (v47)
    v48 = *(_OWORD *)&v87.m01;
    v49 = &vf00.x;
    v50 = (u8)byte_5756085;
    v49[4] = *(_OWORD *)&v87.m00;
    v49[5] = v48;
    v51 = *(_OWORD *)&v87.m03;
    v49[6] = *(_OWORD *)&v87.m02;
    v49[7] = v51;
    if (v50)
    {
      goto LABEL_41;
    }
    else
    {
      goto LABEL_41;
    }
LABEL_41:
    get_transpose(&v87, &mtx_A, 0);
    v95 = vct_A;
    v86 = v87;
    v90 = op_Multiply_60923920(&v86, v95, 0);
    vct_A = v90;
    vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, r);
    v53 = &vf00.x;
    v53[8] = v14;
    v53[9] = v15;
    v53[10] = v16;
    v53[11] = v17;
    vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    v54 = sbtldbwk;
    v56 = *(_OWORD *)&v54->mat3.m01;
    *(_OWORD *)&v87.m00 = *(_OWORD *)&v54->mat3.m00;
    *(_OWORD *)&v87.m01 = v56;
    v57 = *(_OWORD *)&v54->mat3.m03;
    *(_OWORD *)&v87.m02 = *(_OWORD *)&v54->mat3.m02;
    *(_OWORD *)&v87.m03 = v57;
    v59 = *(_OWORD *)&v87.m01;
    v60 = &vf00.x;
    v61 = (u8)byte_5755EF5;
    v60[4] = *(_OWORD *)&v87.m00;
    v60[5] = v59;
    v62 = *(_OWORD *)&v87.m03;
    v60[6] = *(_OWORD *)&v87.m02;
    v60[7] = v62;
    if (v61)
    {
      goto LABEL_54;
    }
    else
    {
LABEL_54:
      vct_A = v80;
      goto LABEL_55;
    }
    vct_A = v80;
LABEL_55:
    get_transpose(&v87, &mtx_A, 0);
    v96 = vct_A;
    v86 = v87;
    v91 = op_Multiply_60923920(&v86, v96, 0);
    vct_A = v91;
    v64 = &vf00.x;
    v24 = v64[4];
    v21 = v64[5];
    v23 = v64[6];
    v22 = v64[7];
    *(_OWORD *)&v87.m00 = v82;
    *(_OWORD *)&v87.m01 = v83;
    *(_OWORD *)&v87.m02 = v84;
    *(_OWORD *)&v87.m03 = v85;
    if (v65)
    v66 = *(_OWORD *)&v87.m01;
    v67 = &vf00.x;
    v68 = (u8)byte_5756085;
    v67[4] = *(_OWORD *)&v87.m00;
    v67[5] = v66;
    v69 = *(_OWORD *)&v87.m03;
    v67[6] = *(_OWORD *)&v87.m02;
    v67[7] = v69;
    if (v68)
    {
      goto LABEL_62;
    }
    else
    {
      goto LABEL_62;
    }
LABEL_62:
    get_transpose(&v87, &mtx_A, 0);
    v97 = vct_A;
    v86 = v87;
    v92 = op_Multiply_60923920(&v86, v97, 0);
    vct_A = v92;
    vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, r);
    v70 = &vf00.x;
    v70[8] = v14;
    v70[9] = v15;
    v70[10] = v16;
    v70[11] = v17;
    vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    --v25;
  }
  while (v25);
  return 1;
}

// 0x192cee0
bool sBtlDebug_DrawCircle(const sdfVector4_t *pos, f32 r, u32 rgba, s32 flg) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  f32 *p_x;
  f32 *v12;
  f32 v13;
  f32 v14;
  f32 v15;
  f32 v16;
  s32 v17;
  f32 v18;
  f32 v19;
  f32 v20;
  f32 v21;
  f32 *v23;
  f32 *v24;
  SBTLDEBUG_WORK *sbtldbwk_local;
  __int128 v28;
  __int128 v29;
  _OWORD *v31;
  s32 v32;
  __int128 v33;
  __int128 v34;
  f32 *v35;
  f32 *v37;
  SBTLDEBUG_WORK *v38;
  __int128 v40;
  __int128 v41;
  _OWORD *v43;
  s32 v44;
  __int128 v45;
  __int128 v46;
  f32 *v47;
  f32 *v48;
  struct sdfVector4_t v57;
  sdfMatrix4_t v59;
  sdfMatrix4_t v60;
  sdfVector4_t v61;
  sdfVector4_t v62;
  sdfVector4_t v64;

  w = pos->w;
  z = pos->z;
  y = pos->y;
  x = pos->x;
  p_x = &vf00.x;
  p_x[4] = x;
  p_x[5] = y;
  p_x[6] = z;
  p_x[7] = w;
  v12 = &vf00.x;
  v13 = 1.0;
  v14 = 0.0;
  v15 = 0.0;
  v16 = 0.0;
  v17 = 12;
  v18 = v12[4];
  v19 = v12[5];
  v20 = v12[6];
  v21 = v12[7];
  do
  {
    v23 = &vf00.x;
    v23[4] = v16;
    v23[5] = v15;
    v23[6] = v13;
    v23[7] = v14;
    vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, r);
    v24 = &vf00.x;
    v24[8] = v18;
    v24[9] = v19;
    v24[10] = v20;
    v24[11] = v21;
    vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    sbtldbwk_local = sbtldbwk;
    v28 = *(_OWORD *)&sbtldbwk_local->mat.m01;
    *(_OWORD *)&v60.m00 = *(_OWORD *)&sbtldbwk_local->mat.m00;
    *(_OWORD *)&v60.m01 = v28;
    v29 = *(_OWORD *)&sbtldbwk_local->mat.m03;
    *(_OWORD *)&v60.m02 = *(_OWORD *)&sbtldbwk_local->mat.m02;
    *(_OWORD *)&v60.m03 = v29;
    v31 = &vf00.x;
    v32 = (u8)byte_5755EF5;
    v33 = *(_OWORD *)&v60.m01;
    v31[4] = *(_OWORD *)&v60.m00;
    v31[5] = v33;
    v34 = *(_OWORD *)&v60.m03;
    v31[6] = *(_OWORD *)&v60.m02;
    v31[7] = v34;
    if (v32)
    {
      goto LABEL_26;
    }
    else
    {
LABEL_26:
      v35 = &vf00.x;
      v35[4] = v16;
      v35[5] = v15;
      v35[6] = v13;
      v35[7] = v14;
      goto LABEL_27;
    }
    vct_A.x = v16;
    vct_A.y = v15;
    vct_A.z = v13;
    vct_A.w = v14;
LABEL_27:
    get_transpose(&v60, &mtx_A, 0);
    v59 = v60;
    v61 = op_Multiply_60923920(&v59, vct_A, 0);
    vct_A = v61;
    v57 = vct_A;
    vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, r);
    v37 = &vf00.x;
    v37[8] = v18;
    v37[9] = v19;
    v37[10] = v20;
    v37[11] = v21;
    vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    v38 = sbtldbwk;
    v40 = *(_OWORD *)&v38->mat.m01;
    *(_OWORD *)&v60.m00 = *(_OWORD *)&v38->mat.m00;
    *(_OWORD *)&v60.m01 = v40;
    v41 = *(_OWORD *)&v38->mat.m03;
    *(_OWORD *)&v60.m02 = *(_OWORD *)&v38->mat.m02;
    *(_OWORD *)&v60.m03 = v41;
    v43 = &vf00.x;
    v44 = (u8)byte_5755EF5;
    v45 = *(_OWORD *)&v60.m01;
    v43[4] = *(_OWORD *)&v60.m00;
    v43[5] = v45;
    v46 = *(_OWORD *)&v60.m03;
    v43[6] = *(_OWORD *)&v60.m02;
    v43[7] = v46;
    if (v44)
    {
      goto LABEL_43;
    }
    else
    {
LABEL_43:
      vct_A = v57;
      goto LABEL_44;
    }
    vct_A = v57;
LABEL_44:
    get_transpose(&v60, &mtx_A, 0);
    v64 = vct_A;
    v59 = v60;
    v62 = op_Multiply_60923920(&v59, v64, 0);
    vct_A = v62;
    v47 = &vf00.x;
    v16 = v47[4];
    v15 = v47[5];
    v13 = v47[6];
    v14 = v47[7];
    vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, r);
    v48 = &vf00.x;
    v48[8] = v18;
    v48[9] = v19;
    v48[10] = v20;
    v48[11] = v21;
    vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    --v17;
  }
  while (v17);
  return 1;
}

// 0x192d800
bool sBtlDebug_DrawCircle2(const sdfVector4_t *pos, const sdfVector4_t *rot, f32 r0, f32 r1, f32 r2, f32 r3, s32 alpha00, s32 alpha01, s32 alpha02, u32 rgb) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  f32 v15;
  f32 v16;
  f32 v17;
  f32 v18;
  u32 *v21;
  f32 *p_x;
  f32 *v24;
  f32 v25;
  f32 v26;
  f32 v27;
  f32 v28;
  f32 *v29;
  f32 v30;
  f32 v31;
  f32 v32;
  f32 *v33;
  s32 v34;
  f32 v35;
  f32 v36;
  f32 v37;
  f32 v38;
  s64 v39;
  u32 v40;
  u32 v41;
  u32 v42;
  u32 v43;
  u32 v44;
  u32 v45;
  f32 *v48;
  s64 v49;
  f32 v50;
  f32 *v51;
  SBTLDEBUG_WORK *sbtldbwk_local;
  __int128 v55;
  __int128 v56;
  _OWORD *v58;
  s32 v59;
  __int128 v60;
  __int128 v61;
  f32 *v62;
  f32 v64;
  f32 *v65;
  SBTLDEBUG_WORK *v66;
  __int128 v68;
  __int128 v69;
  __int128 v71;
  _OWORD *v72;
  s32 v73;
  __int128 v74;
  f32 *v75;
  f32 v76;
  f32 *v77;
  s32 v87;
  s64 v89;
  s32 *v93;
  struct sdfVector4_t v94;
  sdfMatrix4_t v99;
  sdfMatrix4_t v100;
  sdfVector4_t v101;
  sdfVector4_t v102;
  sdfVector4_t v104;

  w = rot->w;
  z = rot->z;
  y = rot->y;
  x = rot->x;
  v15 = pos->w;
  v16 = pos->z;
  v17 = pos->y;
  v18 = pos->x;
  v89 = NewSpecific(f32, 0xDu);
  v21 = NewSpecific(uint, 0xDu);
  v93 = NewSpecific(s32, 4u);
  p_x = &vf00.x;
  p_x[4] = x;
  p_x[5] = y;
  p_x[6] = z;
  p_x[7] = w;
  v24 = &vf00.x;
  v25 = v24[4];
  v26 = v24[5];
  v27 = v24[6];
  v28 = v24[7];
  v29 = &vf00.x;
  v29[4] = v18;
  v29[5] = v17;
  v29[6] = v16;
  v29[7] = v15;
  v30 = r2;
  v31 = r1;
  v32 = r0;
  v32 = r0;
  v30 = r2;
  v31 = r1;
  v33 = &vf00.x;
  v87 = alpha00;
  v34 = alpha02 + alpha00;
  v35 = v33[4];
  v36 = v33[5];
  v37 = v33[6];
  v38 = v33[7];
  *(f32 *)(v89 + 80) = v32;
  *(f32 *)(v89 + 32) = v32;
  *(f32 *)(v89 + 36) = v30 + v30;
  *(f32 *)(v89 + 72) = v30 * 1.15;
  *(f32 *)(v89 + 76) = v30 + v30;
  *(f32 *)(v89 + 40) = v30 * 1.15;
  *(f32 *)(v89 + 44) = v30;
  *(f32 *)(v89 + 56) = v31;
  *(f32 *)(v89 + 60) = v31 * 1.15;
  *(f32 *)(v89 + 64) = v31 + v31;
  *(f32 *)(v89 + 68) = v30;
  *(f32 *)(v89 + 48) = v31 + v31;
  *(f32 *)(v89 + 52) = v31 * 1.15;
  v93[8] = 70 * v34 / 100;
  LimitRange(v93 + 8, 0, 128);
  v93[9] = 30 * v34 / 100;
  LimitRange(v93 + 9, 0, 128);
  v93[10] = 70 * (alpha02 + alpha01) / 100;
  LimitRange(v93 + 10, 0, 128);
  v93[11] = 30 * (alpha02 + alpha01) / 100;
  LimitRange(v93 + 11, 0, 128);
  v39 = 0;
  v40 = rgb | (alpha02 << 24);
  v41 = rgb | (v87 << 24);
  v21[20] = v41;
  v21[8] = v41;
  v42 = rgb | (v93[8] << 24);
  v21[19] = v42;
  v21[9] = v42;
  v43 = rgb | (v93[9] << 24);
  v21[17] = v40;
  v21[18] = v43;
  v21[10] = v43;
  v21[11] = v40;
  v44 = rgb | (v93[10] << 24);
  v21[16] = v44;
  v21[12] = v44;
  v45 = rgb | (v93[11] << 24);
  v21[13] = v45;
  v21[14] = rgb | (alpha01 << 24);
  v21[15] = v45;
  do
  {
    v48 = &vf00.x;
    v48[4] = v25;
    v48[5] = v26;
    v48[6] = v27;
    v48[7] = v28;
    v49 = v89 + v39;
    v50 = *(f32 *)(v89 + v39 + 32);
    vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v50);
    v51 = &vf00.x;
    v51[8] = v35;
    v51[9] = v36;
    v51[10] = v37;
    v51[11] = v38;
    vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    sbtldbwk_local = sbtldbwk;
    v55 = *(_OWORD *)&sbtldbwk_local->mat.m01;
    *(_OWORD *)&v100.m00 = *(_OWORD *)&sbtldbwk_local->mat.m00;
    *(_OWORD *)&v100.m01 = v55;
    v56 = *(_OWORD *)&sbtldbwk_local->mat.m03;
    *(_OWORD *)&v100.m02 = *(_OWORD *)&sbtldbwk_local->mat.m02;
    *(_OWORD *)&v100.m03 = v56;
    v58 = &vf00.x;
    v59 = (u8)byte_5755EF5;
    v60 = *(_OWORD *)&v100.m01;
    v58[4] = *(_OWORD *)&v100.m00;
    v58[5] = v60;
    v61 = *(_OWORD *)&v100.m03;
    v58[6] = *(_OWORD *)&v100.m02;
    v58[7] = v61;
    if (v59)
    {
      goto LABEL_34;
    }
    else
    {
LABEL_34:
      v62 = &vf00.x;
      v62[4] = v25;
      v62[5] = v26;
      v62[6] = v27;
      v62[7] = v28;
      goto LABEL_35;
    }
    vct_A.x = v25;
    vct_A.y = v26;
    vct_A.z = v27;
    vct_A.w = v28;
LABEL_35:
    get_transpose(&v100, &mtx_A, 0);
    v99 = v100;
    v101 = op_Multiply_60923920(&v99, vct_A, 0);
    vct_A = v101;
    v64 = *(f32 *)(v49 + 32);
    v94 = vct_A;
    vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v64);
    v65 = &vf00.x;
    v65[8] = v35;
    v65[9] = v36;
    v65[10] = v37;
    v65[11] = v38;
    vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    v66 = sbtldbwk;
    v68 = *(_OWORD *)&v66->mat.m01;
    *(_OWORD *)&v100.m00 = *(_OWORD *)&v66->mat.m00;
    *(_OWORD *)&v100.m01 = v68;
    v69 = *(_OWORD *)&v66->mat.m03;
    *(_OWORD *)&v100.m02 = *(_OWORD *)&v66->mat.m02;
    *(_OWORD *)&v100.m03 = v69;
    v71 = *(_OWORD *)&v100.m01;
    v72 = &vf00.x;
    v73 = (u8)byte_5755EF5;
    v72[4] = *(_OWORD *)&v100.m00;
    v72[5] = v71;
    v74 = *(_OWORD *)&v100.m03;
    v72[6] = *(_OWORD *)&v100.m02;
    v72[7] = v74;
    if (v73)
    {
      goto LABEL_51;
    }
    else
    {
LABEL_51:
      vct_A = v94;
      goto LABEL_52;
    }
    vct_A = v94;
LABEL_52:
    get_transpose(&v100, &mtx_A, 0);
    v104 = vct_A;
    v99 = v100;
    v102 = op_Multiply_60923920(&v99, v104, 0);
    vct_A = v102;
    v75 = &vf00.x;
    v76 = *(f32 *)(v49 + 36);
    v25 = v75[4];
    v26 = v75[5];
    v27 = v75[6];
    v28 = v75[7];
    vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v76);
    v77 = &vf00.x;
    v77[8] = v35;
    v77[9] = v36;
    v77[10] = v37;
    v77[11] = v38;
    vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    v39 += 4;
  }
  while (v39 != 48);
  return 1;
}

// 0x192e490
bool sBtlDebug_DrawC(SBTLDMG_HITWORK *wk, u32 rgba, s32 start, s32 end, s32 flg, s32 mode) {
  f32 *p_x;
  f32 x;
  f32 y;
  f32 w;
  f32 z;
  u16 atype;
  SBTLDEBUG_WORK *sbtldbwk_local;
  _OWORD *p_m00;
  _OWORD *v25;
  __int128 v26;
  __int128 v27;
  __int128 v28;
  f32 v29;
  f32 v30;
  f32 v31;
  f32 v32;
  f32 *v33;
  f32 v35;
  f32 v36;
  f32 v37;
  f32 v38;
  u32 *v39;
  s32 v40;
  s32 v41;
  s32 v42;
  s32 v43;
  f32 v44;
  f32 v45;
  f32 v46;
  f32 rad_area;
  u32 *v48;
  u32 *v50;
  struct sdfVector4_t pos;
  f32 *v54;
  f32 v55;
  f32 v56;
  f32 v57;
  f32 v58;
  f32 *v60;
  s32 v63;
  f32 *v64;
  f32 v65;
  f32 v66;
  f32 v67;
  f32 v68;
  f32 *v69;
  SBTLDEBUG_WORK *v70;
  __int128 v72;
  __int128 v73;
  __int128 v75;
  _OWORD *v76;
  s32 v77;
  __int128 v78;
  f32 *v79;
  f32 *v82;
  struct sdfVector4_t v83;
  s32 v85;
  f32 *v86;
  f32 *v87;
  SBTLDEBUG_WORK *v88;
  __int128 v90;
  __int128 v91;
  __int128 v93;
  _OWORD *v94;
  s32 v95;
  __int128 v96;
  f32 *v97;
  s32 v99;
  f32 *v101;
  f32 area_r;
  f32 *v103;
  SBTLDEBUG_WORK *v105;
  __int128 v107;
  __int128 v108;
  __int128 v110;
  _OWORD *v111;
  s32 v112;
  __int128 v113;
  f32 *v114;
  f32 v116;
  f32 *v117;
  SBTLDEBUG_WORK *v118;
  __int128 v120;
  __int128 v121;
  __int128 v123;
  _OWORD *v124;
  s32 v125;
  __int128 v126;
  f32 *v127;
  f32 v128;
  f32 *v129;
  struct sdfVector4_t rot;
  struct sdfVector4_t rota;
  f32 rotc;
  f32 rotd;
  struct sdfVector4_t rotb;
  struct sdfVector4_t v151;
  sdfMatrix4_t v156;
  sdfMatrix4_t v157;
  sdfVector4_t v158;
  sdfVector4_t v159;
  sdfVector4_t v160;
  sdfVector4_t v161;
  sdfVector4_t v162;
  sdfVector4_t v163;
  sdfVector4_t v164;
  sdfVector4_t v165;
  sdfVector4_t v167;
  sdfVector4_t v169;
  sdfVector4_t v170;

  rot = wk->pos;
  vct_A = rot;
  p_x = &vf00.x;
  x = p_x[4];
  y = p_x[5];
  z = p_x[6];
  w = p_x[7];
  if (mode == 2)
    goto LABEL_24;
  if (mode != 1)
  {
    if (mode)
    {
      rota = wk->rot;
LABEL_18:
      vct_A = rota;
      goto LABEL_22;
    }
LABEL_24:
    sub_1949280(0, 0.07853982);
    goto LABEL_27;
  }
  sub_19493E0(0, 0.07853982);
LABEL_27:
  sbtldbwk_local = sbtldbwk;
  p_m00 = &sbtldbwk_local->mat_h.m00;
  v25 = &vf00.x;
  v26 = v25[5];
  v27 = v25[6];
  v28 = v25[7];
  *p_m00 = v25[4];
  p_m00[1] = v26;
  p_m00[2] = v27;
  p_m00[3] = v28;
  rota = wk->rot;
  goto LABEL_18;
LABEL_22:
  atype = wk->atype;
  if ((atype & 0x4000) == 0)
  {
LABEL_80:
    v48 = &vf00.x;
    v40 = v48[7];
    v41 = v48[6];
    v42 = v48[5];
    v43 = v48[4];
LABEL_81:
    vct_B = (struct sdfVector4_t)xmmword_3CFBEC0;
    goto LABEL_84;
  }
  v30 = wk->rot.x;
  v29 = wk->rot.y;
  v31 = wk->rot.z;
  v32 = wk->rot.w;
  if ((atype & 4) == 0)
  {
    v33 = &vf00.x;
    v33[4] = v30;
    v33[5] = v29;
    v33[6] = v31;
    v33[7] = v32;
    goto LABEL_42;
  }
  v163.x = v30;
  v163.y = v29;
  v163.z = v31;
  v163.w = v32;
  sBtlGetRotateDeg(v163, 180.0);
LABEL_42:
  if ((wk->atype & 8) == 0)
  {
LABEL_69:
    if ((wk->atype & 0x10) == 0)
      goto LABEL_70;
    v44 = wk->rot.x;
    v165.y = wk->rot.y;
    v45 = wk->rot.z;
    v46 = wk->rot.w;
    rad_area = wk->rad_area;
    rotd = wk->rot.y;
    v165.y = rotd;
    v165.x = v44;
    v165.z = v45;
    v165.w = v46;
    sBtlGetRotateDeg(v165, -rad_area);
    goto LABEL_80;
  }
  v164.x = wk->rot.x;
  v35 = wk->rot.y;
  v36 = wk->rot.z;
  v37 = wk->rot.w;
  v38 = wk->rad_area;
  rotc = wk->rot.x;
  v164.x = rotc;
  v164.y = v35;
  v164.z = v36;
  v164.w = v37;
  sBtlGetRotateDeg(v164, v38);
  goto LABEL_69;
LABEL_70:
  v39 = &vf00.x;
  v40 = v39[7];
  v41 = v39[6];
  v42 = v39[5];
  v43 = v39[4];
  goto LABEL_81;
LABEL_84:
  v50 = &vf00.x;
  v50[4] = v43;
  v50[5] = v42;
  v50[6] = v41;
  v50[7] = v40;
  ToMatrix();
  get_transpose(&v157, &mtx_A, 0);
  *(_OWORD *)&v156.m00 = *(_OWORD *)&v157.m00;
  *(_OWORD *)&v156.m01 = *(_OWORD *)&v157.m01;
  *(_OWORD *)&v156.m02 = *(_OWORD *)&v157.m02;
  *(_OWORD *)&v156.m03 = *(_OWORD *)&v157.m03;
  v158 = op_Multiply_60923920(&v156, vct_B, 0);
  vct_B = v158;
  pos = wk->pos;
  vct_A = pos;
  vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  v54 = &vf00.x;
  v56 = v54[4];
  v55 = v54[5];
  v58 = v54[6];
  v57 = v54[7];
  if (!flg)
  {
    v82 = &vf00.x;
    v82[4] = v56;
    v82[5] = v55;
    v82[6] = v58;
    v82[7] = v57;
    v83 = wk->pos;
    vct_B = v83;
    vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    sub_1949110(0);
LABEL_159:
    v85 = 2 * start;
    v86 = &vf00.x;
    v66 = v86[6];
    v65 = v86[7];
    v68 = v86[4];
    v67 = v86[5];
    if (2 * start < 1)
      goto LABEL_183;
    while (1)
    {
      v88 = sbtldbwk;
      v90 = *(_OWORD *)&v88->mat_h.m01;
      *(_OWORD *)&v157.m00 = *(_OWORD *)&v88->mat_h.m00;
      *(_OWORD *)&v157.m01 = v90;
      v91 = *(_OWORD *)&v88->mat_h.m03;
      *(_OWORD *)&v157.m02 = *(_OWORD *)&v88->mat_h.m02;
      *(_OWORD *)&v157.m03 = v91;
      v93 = *(_OWORD *)&v157.m01;
      v94 = &vf00.x;
      v95 = (u8)byte_5755EF5;
      v94[4] = *(_OWORD *)&v157.m00;
      v94[5] = v93;
      v96 = *(_OWORD *)&v157.m03;
      v94[6] = *(_OWORD *)&v157.m02;
      v94[7] = v96;
      if (v95)
      {
        goto LABEL_169;
      }
      else
      {
LABEL_169:
        v97 = &vf00.x;
        v97[4] = v68;
        v97[5] = v67;
        v97[6] = v66;
        v97[7] = v65;
        goto LABEL_170;
      }
      vct_A.x = v68;
      vct_A.y = v67;
      vct_A.z = v66;
      vct_A.w = v65;
LABEL_170:
      get_transpose(&v157, &mtx_A, 0);
      v156 = v157;
      v160 = op_Multiply_60923920(&v156, vct_A, 0);
      vct_A = v160;
      v87 = &vf00.x;
      --v85;
      v66 = v87[6];
      v65 = v87[7];
      v68 = v87[4];
      v67 = v87[5];
      if (!v85)
        goto LABEL_183;
    }
    goto LABEL_159;
  }
  rotb = wk->pos;
  vct_A = rotb;
  v60 = &vf00.x;
  v60[8] = v56;
  v60[9] = v55;
  v60[10] = v58;
  v60[11] = v57;
  vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  sub_1949110(0);
  v63 = 40 - 2 * end;
  v64 = &vf00.x;
  v66 = v64[6];
  v65 = v64[7];
  v68 = v64[4];
  v67 = v64[5];
  if (v63 >= 1)
  {
    do
    {
      v70 = sbtldbwk;
      v72 = *(_OWORD *)&v70->mat_h.m01;
      *(_OWORD *)&v157.m00 = *(_OWORD *)&v70->mat_h.m00;
      *(_OWORD *)&v157.m01 = v72;
      v73 = *(_OWORD *)&v70->mat_h.m03;
      *(_OWORD *)&v157.m02 = *(_OWORD *)&v70->mat_h.m02;
      *(_OWORD *)&v157.m03 = v73;
      v75 = *(_OWORD *)&v157.m01;
      v76 = &vf00.x;
      v77 = (u8)byte_5755EF5;
      v76[4] = *(_OWORD *)&v157.m00;
      v76[5] = v75;
      v78 = *(_OWORD *)&v157.m03;
      v76[6] = *(_OWORD *)&v157.m02;
      v76[7] = v78;
      if (v77)
      {
        goto LABEL_117;
      }
      else
      {
LABEL_117:
        v79 = &vf00.x;
        v79[4] = v68;
        v79[5] = v67;
        v79[6] = v66;
        v79[7] = v65;
        goto LABEL_118;
      }
      vct_A.x = v68;
      vct_A.y = v67;
      vct_A.z = v66;
      vct_A.w = v65;
LABEL_118:
      get_transpose(&v157, &mtx_A, 0);
      v167 = vct_A;
      v156 = v157;
      v159 = op_Multiply_60923920(&v156, v167, 0);
      vct_A = v159;
      v69 = &vf00.x;
      --v63;
      v66 = v69[6];
      v65 = v69[7];
      v68 = v69[4];
      v67 = v69[5];
    }
    while (v63);
  }
LABEL_183:
  v99 = end - start;
  if (end > start)
  {
    do
    {
      v101 = &vf00.x;
      v101[4] = v68;
      v101[5] = v67;
      v101[6] = v66;
      v101[7] = v65;
      area_r = wk->area_r;
      vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, area_r);
      v103 = &vf00.x;
      v103[8] = x;
      v103[9] = y;
      v103[10] = z;
      v103[11] = w;
      vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
      v105 = sbtldbwk;
      v107 = *(_OWORD *)&v105->mat_h.m01;
      *(_OWORD *)&v157.m00 = *(_OWORD *)&v105->mat_h.m00;
      *(_OWORD *)&v157.m01 = v107;
      v108 = *(_OWORD *)&v105->mat_h.m03;
      *(_OWORD *)&v157.m02 = *(_OWORD *)&v105->mat_h.m02;
      *(_OWORD *)&v157.m03 = v108;
      v110 = *(_OWORD *)&v157.m01;
      v111 = &vf00.x;
      v112 = (u8)byte_5755EF5;
      v111[4] = *(_OWORD *)&v157.m00;
      v111[5] = v110;
      v113 = *(_OWORD *)&v157.m03;
      v111[6] = *(_OWORD *)&v157.m02;
      v111[7] = v113;
      if (v112)
      {
        goto LABEL_203;
      }
      else
      {
LABEL_203:
        v114 = &vf00.x;
        v114[4] = v68;
        v114[5] = v67;
        v114[6] = v66;
        v114[7] = v65;
        goto LABEL_204;
      }
      vct_A.x = v68;
      vct_A.y = v67;
      vct_A.z = v66;
      vct_A.w = v65;
LABEL_204:
      get_transpose(&v157, &mtx_A, 0);
      v169 = vct_A;
      v156 = v157;
      v161 = op_Multiply_60923920(&v156, v169, 0);
      vct_A = v161;
      v116 = wk->area_r;
      v151 = vct_A;
      vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v116);
      v117 = &vf00.x;
      v117[8] = x;
      v117[9] = y;
      v117[10] = z;
      v117[11] = w;
      vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
      v118 = sbtldbwk;
      v120 = *(_OWORD *)&v118->mat_h.m01;
      *(_OWORD *)&v157.m00 = *(_OWORD *)&v118->mat_h.m00;
      *(_OWORD *)&v157.m01 = v120;
      v121 = *(_OWORD *)&v118->mat_h.m03;
      *(_OWORD *)&v157.m02 = *(_OWORD *)&v118->mat_h.m02;
      *(_OWORD *)&v157.m03 = v121;
      v123 = *(_OWORD *)&v157.m01;
      v124 = &vf00.x;
      v125 = (u8)byte_5755EF5;
      v124[4] = *(_OWORD *)&v157.m00;
      v124[5] = v123;
      v126 = *(_OWORD *)&v157.m03;
      v124[6] = *(_OWORD *)&v157.m02;
      v124[7] = v126;
      if (v125)
      {
        goto LABEL_220;
      }
      else
      {
LABEL_220:
        vct_A = v151;
        goto LABEL_221;
      }
      vct_A = v151;
LABEL_221:
      get_transpose(&v157, &mtx_A, 0);
      v170 = vct_A;
      v156 = v157;
      v162 = op_Multiply_60923920(&v156, v170, 0);
      vct_A = v162;
      v127 = &vf00.x;
      v128 = wk->area_r;
      v68 = v127[4];
      v67 = v127[5];
      v66 = v127[6];
      v65 = v127[7];
      vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v128);
      v129 = &vf00.x;
      v129[8] = x;
      v129[9] = y;
      v129[10] = z;
      v129[11] = w;
      vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
      --v99;
    }
    while (v99);
  }
  return 1;
}

// 0x190f730
void _3DCylinderDraw(const sdfVector4_t *pCenter, f32 radius, f32 height, u32 c, bool mat, const sdfMatrix4_t *pMat) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  _OWORD *v15;
  sdfDrawTag_t *v16;
  int32x4_t v17;
  f32 *v20;
  f32 *v21;
  f32 v22;
  f32 v23;
  f32 v24;
  f32 v25;
  __int128 v26;
  u32 v27;
  __int128 v28;
  __int128 v29;
  _OWORD *v30;
  s32 v31;
  __int128 v32;
  __int128 v35;
  __int128 v36;
  __int128 v37;
  __int128 v38;
  __int128 v39;
  _OWORD *p_x;
  s32 v41;
  __int128 v42;
  _OWORD *v44;
  f32 v45;
  s32 v46;
  s32 v47;
  sdfVector4_t *m_Items;
  f32 v49;
  _OWORD *v51;
  s32 v52;
  f32 v57;
  s32 v58;
  s32 v59;
  f32 v61;
  f32 v62;
  f32 v63;
  f32 v64;
  f32 v65;
  f32 v66;
  f32 v67;
  bool v68;
  f32 v69;
  f32 v70;
  f32 v71;
  f32 v72;
  f32 v73;
  f32 v74;
  f32 v76;
  f32 v77;
  f32 v79;
  f32 v84;
  _OWORD *v85;
  s64 v86;
  sdfVector4_t *v87;
  bool v88;
  f32 v89;
  f32 v90;
  f32 v91;
  f32 v92;
  f32 v93;
  f32 v94;
  f32 v95;
  f32 v96;
  f32 v97;
  f32 v100;
  f32 v101;
  f32 v103;
  f32 v104;
  f32 v110;
  f32 v111;
  f32 v113;
  f32 v118;
  s64 v119;
  _OWORD *v120;
  sdfVector4_t *v121;
  f32 v122;
  f32 v123;
  f32 v124;
  f32 v125;
  f32 v126;
  f32 v127;
  f32 v130;
  f32 v131;
  f32 v132;
  f32 v137;
  f32 v138;
  f32 v139;
  f32 v140;
  f32 v141;
  f32 v142;
  f32 v145;
  f32 v146;
  f32 v147;
  f32 v153;
  s64 v154;
  _OWORD *v155;
  sdfVector4_t *v156;
  f32 v157;
  f32 v158;
  f32 v159;
  f32 v160;
  f32 v161;
  f32 v162;
  f32 v165;
  f32 v166;
  f32 v167;
  f32 v172;
  f32 v173;
  f32 v174;
  f32 v175;
  f32 v176;
  f32 v177;
  f32 v180;
  f32 v181;
  f32 v182;
  sdfDrawTag_t *tag;
  s32 v195;
  f32 v196;
  f32 v197;
  sdfVector4_t *pos;
  __int128 v199;
  __int128 v200;
  __int128 v201;
  __int128 v202;
  sdfMatrix4_t v203;
  sdfMatrix4_t v204;
  sdfVector4_t v205;
  sdfVector4_t v206;
  sdfVector4_t v207;
  sdfVector4_t v208;
  sdfVector4_t v209;
  sdfVector4_t v210;
  sdfVector4_t v211;
  sdfVector4_t v212;
  sdfVector4_t v213;
  sdfVector4_t v214;
  sdfVector4_t v216;
  sdfVector4_t v217;
  sdfVector4_t v218;
  sdfVector4_t v219;
  sdfVector4_t v220;
  sdfVector4_t v221;
  sdfVector4_t v222;

  w = pCenter->w;
  z = pCenter->z;
  y = pCenter->y;
  x = pCenter->x;
  pos = NewSpecific(sdfVector4_t, 0x20u);
  v15 = NewSpecific(uint, 0x20u);
  v16 = Allocate(sdfDrawTag_t);
  _ctor(v16, 0);
  tag = v16;
  sdfDrawTagInit(v16);
  v17 = vdupq_n_s32(c);
  v15[2] = v17;
  v15[3] = v17;
  v15[4] = v17;
  v15[5] = v17;
  v15[6] = v17;
  v15[7] = v17;
  v15[8] = v17;
  v15[9] = v17;
  if (!mat)
  {
    v35 = *(_OWORD *)&identityMatrix.m00;
    v36 = *(_OWORD *)&identityMatrix.m01;
    v37 = *(_OWORD *)&identityMatrix.m02;
    v38 = *(_OWORD *)&identityMatrix.m03;
    *(_OWORD *)&v204.m00 = v35;
    *(_OWORD *)&v204.m01 = v36;
    *(_OWORD *)&v204.m02 = v37;
    *(_OWORD *)&v204.m03 = v38;
    v39 = *(_OWORD *)&v204.m01;
    p_x = &vf00.x;
    v41 = (u8)byte_5756094;
    p_x[4] = *(_OWORD *)&v204.m00;
    p_x[5] = v39;
    v42 = *(_OWORD *)&v204.m03;
    p_x[6] = *(_OWORD *)&v204.m02;
    p_x[7] = v42;
    if (v41)
    {
      goto LABEL_22;
    }
    else
    {
      goto LABEL_22;
    }
LABEL_22:
    v214.x = x;
    v214.y = y;
    v214.z = z;
    v214.w = w;
    SetRow(&mtx_A, 3, v214, 0);
    goto LABEL_23;
  }
  v20 = &vf00.x;
  v20[4] = x;
  v20[5] = y;
  v20[6] = z;
  v20[7] = w;
  v21 = &vf00.x;
  v22 = v21[4];
  v23 = v21[5];
  v24 = v21[6];
  v25 = v21[7];
  v26 = *(_OWORD *)&pMat->m01;
  *(_OWORD *)&v204.m00 = *(_OWORD *)&pMat->m00;
  *(_OWORD *)&v204.m01 = v26;
  v28 = *(_OWORD *)&pMat->m03;
  *(_OWORD *)&v204.m02 = *(_OWORD *)&pMat->m02;
  *(_OWORD *)&v204.m03 = v28;
  if (v27)
  v29 = *(_OWORD *)&v204.m01;
  v30 = &vf00.x;
  v31 = (u8)byte_5756094;
  v30[4] = *(_OWORD *)&v204.m00;
  v30[5] = v29;
  v32 = *(_OWORD *)&v204.m03;
  v30[6] = *(_OWORD *)&v204.m02;
  v30[7] = v32;
  if (v31)
  {
    goto LABEL_13;
  }
  else
  {
    goto LABEL_13;
  }
LABEL_13:
  v213.x = v22;
  v213.y = v23;
  v213.z = v24;
  v213.w = v25;
  SetRow(&mtx_A, 3, v213, 0);
LABEL_23:
  v44 = &vf00.x;
  v45 = -1.0;
  v46 = 0;
  v47 = 0;
  m_Items = pos;
  v199 = v44[4];
  v200 = v44[5];
  v49 = height * -0.5;
  v201 = v44[6];
  v202 = v44[7];
  v197 = height * -0.5;
  do
  {
    v51 = &vf00.x;
    v52 = (u8)byte_5755EF5;
    v51[4] = v199;
    v51[5] = v200;
    v51[6] = v201;
    v51[7] = v202;
    if (v52)
    {
      goto LABEL_33;
    }
    else
    {
      goto LABEL_33;
    }
LABEL_33:
    vct_A.x = radius;
    vct_A.y = v49;
    *(u64 *)&vct_A.z = 0;
    vct_A.w = 1.0;
    get_transpose(&v204, &mtx_A, 0);
    v203 = v204;
    v205 = op_Multiply_60923920(&v203, vct_A, 0);
    vct_A = v205;
    if (v47 < SLODWORD(pos->max_length))
    {
      m_Items[v47] = vct_A;
      goto LABEL_40;
    }
LABEL_40:
    v57 = 0.0;
    v58 = 0;
    v195 = v46;
    do
    {
      v59 = v47 + v58;
      if (v47 + v58 < SLODWORD(pos->max_length))
        m_Items[v59] = vct_A;
      v57 = v57 + 0.3926991;
      v61 = (f32)(v57 + 1.5708) * 0.15915494;
      v62 = (s32)v61;
      if (v61 == INFINITY)
        v62 = -2147500000.0;
      v63 = v61 - v62;
      v64 = v63 + 1.0;
      if (v63 >= -0.5)
        v64 = v63;
      if (v63 > 0.5)
        v65 = v63 + v45;
      else
        v65 = v64;
      v66 = -0.5 - v65;
      v67 = 0.5 - v65;
      if (v65 >= -0.25)
        v66 = v65;
      v68 = v65 <= 0.25;
      v69 = v57 * 0.15915494;
      if (v68)
        v70 = v66;
      else
        v70 = v67;
      v71 = (s32)v69;
      if (v69 == INFINITY)
        v71 = -2147500000.0;
      v72 = v69 - v71;
      if (v72 <= 0.5)
      {
        if (v72 < -0.5)
          v72 = v72 + 1.0;
      }
      else
      {
        v72 = v72 + v45;
      }
      v73 = -0.5 - v72;
      if (v72 >= -0.25)
        v73 = v72;
      if (v72 > 0.25)
        v74 = 0.5 - v72;
      else
        v74 = v73;
      v76 = v70 * 4.0;
      v77 = v74 * 4.0;
      vct_A.y = v49;
      vct_A.w = 0.0;
      v79 = v76 * v76;
      vct_A.x = (f32)((f32)((f32)((f32)((f32)((f32)(v70 * 4.0) * 1.5708) + (f32)((f32)(v76 * (f32)(v76 * v76)) * -0.6459637)) + (f32)((f32)((f32)(v76 * v76) * (f32)(v76 * (f32)(v76 * v76))) * 0.07968968)) + (f32)((f32)(v79 * (f32)(v79 * (f32)(v76 * (f32)(v76 * v76)))) * -0.0046737655)) + (f32)((f32)(v79 * (f32)(v79 * (f32)(v79 * (f32)(v76 * (f32)(v76 * v76))))) * 0.00015148419))
                          * radius;
      vct_A.z = (f32)((f32)((f32)((f32)((f32)((f32)(v74 * 4.0) * 1.5708) + (f32)((f32)(v77 * (f32)(v77 * v77)) * -0.6459637)) + (f32)((f32)((f32)(v77 * v77) * (f32)(v77 * (f32)(v77 * v77))) * 0.07968968)) + (f32)((f32)((f32)(v77 * v77) * (f32)((f32)(v77 * v77) * (f32)(v77 * (f32)(v77 * v77)))) * -0.0046737655)) + (f32)((f32)((f32)(v77 * v77) * (f32)((f32)(v77 * v77) * (f32)((f32)(v77 * v77) * (f32)(v77 * (f32)(v77 * v77))))) * 0.00015148419))
                          * radius;
      v45 = -1.0;
      vct_A.w = 1.0;
      get_transpose(&v204, &mtx_A, 0);
      v216 = vct_A;
      v203 = v204;
      v206 = op_Multiply_60923920(&v203, v216, 0);
      vct_A = v206;
      if (v59 + 1 < SLODWORD(pos->max_length))
      {
        m_Items[v59 + 1] = vct_A;
      }
      v58 += 2;
    }
    while (v58 != 32);
    v47 += 32;
    v49 = (f32)(height / 15.0) + v49;
    CleateLine(pos->max_length, pos, 0);
    v46 = v195 + 1;
  }
  while (v195 != 15);
  v84 = 0.0;
  v85 = &vf00.x;
  v86 = 0;
  v87 = &pos[1];
  v85[4] = v199;
  v85[5] = v200;
  v85[6] = v201;
  v85[7] = v202;
  v196 = height * 0.5;
  while (2)
  {
    v89 = (f32)(v84 + 1.5708) * 0.15915494;
    v90 = (s32)v89;
    if (v89 == INFINITY)
      v90 = -2147500000.0;
    v91 = v89 - v90;
    if ((f32)(v89 - v90) <= 0.5)
    {
      v92 = v89 - v90;
      if (v91 < -0.5)
        v92 = v91 + 1.0;
    }
    else
    {
      v92 = v91 + v45;
    }
    if (v92 <= 0.25)
    {
      if (v92 < -0.25)
        v92 = -0.5 - v92;
    }
    else
    {
      v92 = 0.5 - v92;
    }
    v93 = v84;
    v94 = v84 * 0.15915494;
    v95 = (s32)(v84 * 0.15915494);
    if ((f32)(v84 * 0.15915494) == INFINITY)
      v95 = -2147500000.0;
    v96 = v94 - v95;
    if ((f32)(v94 - v95) <= 0.5)
    {
      v97 = v94 - v95;
      if (v96 < -0.5)
        v97 = v96 + 1.0;
    }
    else
    {
      v97 = v96 + v45;
    }
    if (v97 <= 0.25)
    {
      if (v97 < -0.25)
      {
        v97 = -0.5 - v97;
      }
      else
      {
      }
LABEL_129:
      goto LABEL_131;
    }
    v97 = 0.5 - v97;
    goto LABEL_129;
LABEL_131:
    v100 = v92 * 4.0;
    v101 = v97 * 4.0;
    vct_A.w = 0.0;
    v103 = v100 * v100;
    vct_A.y = v197;
    vct_A.x = (f32)((f32)((f32)((f32)((f32)((f32)(v92 * 4.0) * 1.5708) + (f32)((f32)(v100 * (f32)(v100 * v100)) * -0.6459637)) + (f32)((f32)((f32)(v100 * v100) * (f32)(v100 * (f32)(v100 * v100))) * 0.07968968)) + (f32)((f32)(v103 * (f32)(v103 * (f32)(v100 * (f32)(v100 * v100)))) * -0.0046737655)) + (f32)((f32)(v103 * (f32)(v103 * (f32)(v103 * (f32)(v100 * (f32)(v100 * v100))))) * 0.00015148419))
                         * radius;
    vct_A.z = (f32)((f32)((f32)((f32)((f32)((f32)(v97 * 4.0) * 1.5708) + (f32)((f32)(v101 * (f32)(v101 * v101)) * -0.6459637)) + (f32)((f32)((f32)(v101 * v101) * (f32)(v101 * (f32)(v101 * v101))) * 0.07968968)) + (f32)((f32)((f32)(v101 * v101) * (f32)((f32)(v101 * v101) * (f32)(v101 * (f32)(v101 * v101)))) * -0.0046737655)) + (f32)((f32)((f32)(v101 * v101) * (f32)((f32)(v101 * v101) * (f32)((f32)(v101 * v101) * (f32)(v101 * (f32)(v101 * v101))))) * 0.00015148419))
                         * radius;
    v104 = v93;
    vct_A.w = 1.0;
    get_transpose(&v204, &mtx_A, 0);
    v217 = vct_A;
    v203 = v204;
    v207 = op_Multiply_60923920(&v203, v217, 0);
    vct_A = v207;
    if (v86 < SLODWORD(pos->max_length))
    {
      v87[-1] = vct_A;
    }
    if (v91 <= 0.5)
    {
      if (v91 < -0.5)
        v91 = v91 + 1.0;
    }
    else
    {
      v91 = v91 + v45;
    }
    if (v91 <= 0.25)
    {
      if (v91 < -0.25)
        v91 = -0.5 - v91;
    }
    else
    {
      v91 = 0.5 - v91;
    }
    if (v96 <= 0.5)
    {
      if (v96 < -0.5)
        v96 = v96 + 1.0;
    }
    else
    {
      v96 = v96 + v45;
    }
    if (v96 <= 0.25)
    {
      if (v96 < -0.25)
      {
        v96 = -0.5 - v96;
      }
      else
      {
      }
LABEL_155:
      goto LABEL_157;
    }
    v96 = 0.5 - v96;
    goto LABEL_155;
LABEL_157:
    v110 = v91 * 4.0;
    v111 = v96 * 4.0;
    vct_A.w = 0.0;
    v113 = v110 * v110;
    vct_A.x = (f32)((f32)((f32)((f32)((f32)((f32)(v91 * 4.0) * 1.5708) + (f32)((f32)(v110 * (f32)(v110 * v110)) * -0.6459637)) + (f32)((f32)((f32)(v110 * v110) * (f32)(v110 * (f32)(v110 * v110))) * 0.07968968)) + (f32)((f32)(v113 * (f32)(v113 * (f32)(v110 * (f32)(v110 * v110)))) * -0.0046737655)) + (f32)((f32)(v113 * (f32)(v113 * (f32)(v113 * (f32)(v110 * (f32)(v110 * v110))))) * 0.00015148419))
                         * radius;
    vct_A.y = v196;
    vct_A.z = (f32)((f32)((f32)((f32)((f32)((f32)(v96 * 4.0) * 1.5708) + (f32)((f32)(v111 * (f32)(v111 * v111)) * -0.6459637)) + (f32)((f32)((f32)(v111 * v111) * (f32)(v111 * (f32)(v111 * v111))) * 0.07968968)) + (f32)((f32)((f32)(v111 * v111) * (f32)((f32)(v111 * v111) * (f32)(v111 * (f32)(v111 * v111)))) * -0.0046737655)) + (f32)((f32)((f32)(v111 * v111) * (f32)((f32)(v111 * v111) * (f32)((f32)(v111 * v111) * (f32)(v111 * (f32)(v111 * v111))))) * 0.00015148419))
                         * radius;
    vct_A.w = 1.0;
    get_transpose(&v204, &mtx_A, 0);
    v218 = vct_A;
    v203 = v204;
    v208 = op_Multiply_60923920(&v203, v218, 0);
    vct_A = v208;
    if (v86 + 1 < SLODWORD(pos->max_length))
    {
      *v87 = vct_A;
    }
    v87 += 2;
    v88 = (u32)v86 == 30;
    v84 = v104 + 0.3926991;
    v86 += 2;
    if (!v88)
      continue;
    break;
  }
  CleateLine(pos->max_length, pos, 0);
  v118 = 0.0;
  v119 = 0;
  v120 = &vf00.x;
  v121 = &pos[1];
  v120[4] = v199;
  v120[5] = v200;
  v120[6] = v201;
  v120[7] = v202;
  while (2)
  {
    v122 = (f32)(v118 + 1.5708) * 0.15915494;
    v123 = (s32)v122;
    if (v122 == INFINITY)
      v123 = -2147500000.0;
    v124 = v122 - v123;
    if ((f32)(v122 - v123) <= 0.5)
    {
      if (v124 < -0.5)
        v124 = v124 + 1.0;
    }
    else
    {
      v124 = v124 + v45;
    }
    if (v124 <= 0.25)
    {
      if (v124 < -0.25)
        v124 = -0.5 - v124;
    }
    else
    {
      v124 = 0.5 - v124;
    }
    v125 = v118 * 0.15915494;
    v126 = (s32)(v118 * 0.15915494);
    if ((f32)(v118 * 0.15915494) == INFINITY)
      v126 = -2147500000.0;
    v127 = v125 - v126;
    if ((f32)(v125 - v126) <= 0.5)
    {
      if (v127 < -0.5)
        v127 = v127 + 1.0;
    }
    else
    {
      v127 = v127 + v45;
    }
    if (v127 <= 0.25)
    {
      if (v127 < -0.25)
      {
        v127 = -0.5 - v127;
      }
      else
      {
      }
LABEL_211:
      goto LABEL_213;
    }
    v127 = 0.5 - v127;
    goto LABEL_211;
LABEL_213:
    v130 = v124 * 4.0;
    v131 = v127 * 4.0;
    v132 = v130 * v130;
    vct_A.w = 0.0;
    vct_A.x = (f32)((f32)((f32)((f32)((f32)((f32)(v124 * 4.0) * 1.5708) + (f32)((f32)(v130 * (f32)(v130 * v130)) * -0.6459637)) + (f32)((f32)((f32)(v130 * v130) * (f32)(v130 * (f32)(v130 * v130))) * 0.07968968)) + (f32)((f32)(v132 * (f32)(v132 * (f32)(v130 * (f32)(v130 * v130)))) * -0.0046737655)) + (f32)((f32)(v132 * (f32)(v132 * (f32)(v132 * (f32)(v130 * (f32)(v130 * v130))))) * 0.00015148419))
                         * radius;
    vct_A.y = v197;
    vct_A.z = (f32)((f32)((f32)((f32)((f32)((f32)(v127 * 4.0) * 1.5708) + (f32)((f32)(v131 * (f32)(v131 * v131)) * -0.6459637)) + (f32)((f32)((f32)(v131 * v131) * (f32)(v131 * (f32)(v131 * v131))) * 0.07968968)) + (f32)((f32)((f32)(v131 * v131) * (f32)((f32)(v131 * v131) * (f32)(v131 * (f32)(v131 * v131)))) * -0.0046737655)) + (f32)((f32)((f32)(v131 * v131) * (f32)((f32)(v131 * v131) * (f32)((f32)(v131 * v131) * (f32)(v131 * (f32)(v131 * v131))))) * 0.00015148419))
                         * radius;
    vct_A.w = 1.0;
    get_transpose(&v204, &mtx_A, 0);
    v219 = vct_A;
    v203 = v204;
    v209 = op_Multiply_60923920(&v203, v219, 0);
    vct_A = v209;
    if (v119 < SLODWORD(pos->max_length))
    {
      v121[-1] = vct_A;
    }
    v137 = (f32)((f32)(v118 + 3.1415927) + 1.5708) * 0.15915494;
    v138 = (s32)v137;
    if (v137 == INFINITY)
      v138 = -2147500000.0;
    v139 = v137 - v138;
    if ((f32)(v137 - v138) <= 0.5)
    {
      if (v139 < -0.5)
        v139 = v139 + 1.0;
    }
    else
    {
      v139 = v139 + v45;
    }
    if (v139 <= 0.25)
    {
      if (v139 < -0.25)
        v139 = -0.5 - v139;
    }
    else
    {
      v139 = 0.5 - v139;
    }
    v140 = (f32)(v118 + 3.1415927) * 0.15915494;
    v141 = (s32)v140;
    if (v140 == INFINITY)
      v141 = -2147500000.0;
    v142 = v140 - v141;
    if ((f32)(v140 - v141) <= 0.5)
    {
      if (v142 < -0.5)
        v142 = v142 + 1.0;
    }
    else
    {
      v142 = v142 + v45;
    }
    if (v142 <= 0.25)
    {
      if (v142 < -0.25)
      {
        v142 = -0.5 - v142;
      }
      else
      {
      }
LABEL_241:
      goto LABEL_243;
    }
    v142 = 0.5 - v142;
    goto LABEL_241;
LABEL_243:
    v145 = v139 * 4.0;
    v146 = v142 * 4.0;
    v147 = v145 * v145;
    vct_A.w = 0.0;
    vct_A.x = (f32)((f32)((f32)((f32)((f32)((f32)(v139 * 4.0) * 1.5708) + (f32)((f32)(v145 * (f32)(v145 * v145)) * -0.6459637)) + (f32)((f32)((f32)(v145 * v145) * (f32)(v145 * (f32)(v145 * v145))) * 0.07968968)) + (f32)((f32)(v147 * (f32)(v147 * (f32)(v145 * (f32)(v145 * v145)))) * -0.0046737655)) + (f32)((f32)(v147 * (f32)(v147 * (f32)(v147 * (f32)(v145 * (f32)(v145 * v145))))) * 0.00015148419))
                         * radius;
    vct_A.y = v197;
    vct_A.z = (f32)((f32)((f32)((f32)((f32)((f32)(v142 * 4.0) * 1.5708) + (f32)((f32)(v146 * (f32)(v146 * v146)) * -0.6459637)) + (f32)((f32)((f32)(v146 * v146) * (f32)(v146 * (f32)(v146 * v146))) * 0.07968968)) + (f32)((f32)((f32)(v146 * v146) * (f32)((f32)(v146 * v146) * (f32)(v146 * (f32)(v146 * v146)))) * -0.0046737655)) + (f32)((f32)((f32)(v146 * v146) * (f32)((f32)(v146 * v146) * (f32)((f32)(v146 * v146) * (f32)(v146 * (f32)(v146 * v146))))) * 0.00015148419))
                         * radius;
    vct_A.w = 1.0;
    get_transpose(&v204, &mtx_A, 0);
    v220 = vct_A;
    v203 = v204;
    v210 = op_Multiply_60923920(&v203, v220, 0);
    vct_A = v210;
    if (v119 + 1 < SLODWORD(pos->max_length))
    {
      *v121 = vct_A;
    }
    v121 += 2;
    v88 = (u32)v119 == 14;
    v118 = v118 + 0.3926991;
    v119 += 2;
    if (!v88)
      continue;
    break;
  }
  CleateLine(SLODWORD(pos->max_length) / 2, pos, 0);
  v153 = 0.0;
  v154 = 0;
  v155 = &vf00.x;
  v156 = &pos[1];
  v155[4] = v199;
  v155[5] = v200;
  v155[6] = v201;
  v155[7] = v202;
  while (2)
  {
    v157 = (f32)(v153 + 1.5708) * 0.15915494;
    v158 = (s32)v157;
    if (v157 == INFINITY)
      v158 = -2147500000.0;
    v159 = v157 - v158;
    if ((f32)(v157 - v158) <= 0.5)
    {
      if (v159 < -0.5)
        v159 = v159 + 1.0;
    }
    else
    {
      v159 = v159 + v45;
    }
    if (v159 <= 0.25)
    {
      if (v159 < -0.25)
        v159 = -0.5 - v159;
    }
    else
    {
      v159 = 0.5 - v159;
    }
    v160 = v153 * 0.15915494;
    v161 = (s32)(v153 * 0.15915494);
    if ((f32)(v153 * 0.15915494) == INFINITY)
      v161 = -2147500000.0;
    v162 = v160 - v161;
    if ((f32)(v160 - v161) <= 0.5)
    {
      if (v162 < -0.5)
        v162 = v162 + 1.0;
    }
    else
    {
      v162 = v162 + v45;
    }
    if (v162 <= 0.25)
    {
      if (v162 < -0.25)
      {
        v162 = -0.5 - v162;
      }
      else
      {
      }
LABEL_297:
      goto LABEL_299;
    }
    v162 = 0.5 - v162;
    goto LABEL_297;
LABEL_299:
    v165 = v159 * 4.0;
    v166 = v162 * 4.0;
    v167 = v165 * v165;
    vct_A.w = 0.0;
    vct_A.x = (f32)((f32)((f32)((f32)((f32)((f32)(v159 * 4.0) * 1.5708) + (f32)((f32)(v165 * (f32)(v165 * v165)) * -0.6459637)) + (f32)((f32)((f32)(v165 * v165) * (f32)(v165 * (f32)(v165 * v165))) * 0.07968968)) + (f32)((f32)(v167 * (f32)(v167 * (f32)(v165 * (f32)(v165 * v165)))) * -0.0046737655)) + (f32)((f32)(v167 * (f32)(v167 * (f32)(v167 * (f32)(v165 * (f32)(v165 * v165))))) * 0.00015148419))
                         * radius;
    vct_A.y = v196;
    vct_A.z = (f32)((f32)((f32)((f32)((f32)((f32)(v162 * 4.0) * 1.5708) + (f32)((f32)(v166 * (f32)(v166 * v166)) * -0.6459637)) + (f32)((f32)((f32)(v166 * v166) * (f32)(v166 * (f32)(v166 * v166))) * 0.07968968)) + (f32)((f32)((f32)(v166 * v166) * (f32)((f32)(v166 * v166) * (f32)(v166 * (f32)(v166 * v166)))) * -0.0046737655)) + (f32)((f32)((f32)(v166 * v166) * (f32)((f32)(v166 * v166) * (f32)((f32)(v166 * v166) * (f32)(v166 * (f32)(v166 * v166))))) * 0.00015148419))
                         * radius;
    vct_A.w = 1.0;
    get_transpose(&v204, &mtx_A, 0);
    v221 = vct_A;
    v203 = v204;
    v211 = op_Multiply_60923920(&v203, v221, 0);
    vct_A = v211;
    if (v154 < SLODWORD(pos->max_length))
    {
      v156[-1] = vct_A;
    }
    v172 = (f32)((f32)(v153 + 3.1415927) + 1.5708) * 0.15915494;
    v173 = (s32)v172;
    if (v172 == INFINITY)
      v173 = -2147500000.0;
    v174 = v172 - v173;
    if ((f32)(v172 - v173) <= 0.5)
    {
      if (v174 < -0.5)
        v174 = v174 + 1.0;
    }
    else
    {
      v174 = v174 + v45;
    }
    if (v174 <= 0.25)
    {
      if (v174 < -0.25)
        v174 = -0.5 - v174;
    }
    else
    {
      v174 = 0.5 - v174;
    }
    v175 = (f32)(v153 + 3.1415927) * 0.15915494;
    v176 = (s32)v175;
    if (v175 == INFINITY)
      v176 = -2147500000.0;
    v177 = v175 - v176;
    if ((f32)(v175 - v176) <= 0.5)
    {
      if (v177 < -0.5)
        v177 = v177 + 1.0;
    }
    else
    {
      v177 = v177 + v45;
    }
    if (v177 <= 0.25)
    {
      if (v177 < -0.25)
      {
        v177 = -0.5 - v177;
      }
      else
      {
      }
LABEL_327:
      goto LABEL_329;
    }
    v177 = 0.5 - v177;
    goto LABEL_327;
LABEL_329:
    v180 = v174 * 4.0;
    v181 = v177 * 4.0;
    v182 = v180 * v180;
    vct_A.w = 0.0;
    vct_A.x = (f32)((f32)((f32)((f32)((f32)((f32)(v174 * 4.0) * 1.5708) + (f32)((f32)(v180 * (f32)(v180 * v180)) * -0.6459637)) + (f32)((f32)((f32)(v180 * v180) * (f32)(v180 * (f32)(v180 * v180))) * 0.07968968)) + (f32)((f32)(v182 * (f32)(v182 * (f32)(v180 * (f32)(v180 * v180)))) * -0.0046737655)) + (f32)((f32)(v182 * (f32)(v182 * (f32)(v182 * (f32)(v180 * (f32)(v180 * v180))))) * 0.00015148419))
                         * radius;
    vct_A.y = v196;
    vct_A.z = (f32)((f32)((f32)((f32)((f32)((f32)(v177 * 4.0) * 1.5708) + (f32)((f32)(v181 * (f32)(v181 * v181)) * -0.6459637)) + (f32)((f32)((f32)(v181 * v181) * (f32)(v181 * (f32)(v181 * v181))) * 0.07968968)) + (f32)((f32)((f32)(v181 * v181) * (f32)((f32)(v181 * v181) * (f32)(v181 * (f32)(v181 * v181)))) * -0.0046737655)) + (f32)((f32)((f32)(v181 * v181) * (f32)((f32)(v181 * v181) * (f32)((f32)(v181 * v181) * (f32)(v181 * (f32)(v181 * v181))))) * 0.00015148419))
                         * radius;
    vct_A.w = 1.0;
    get_transpose(&v204, &mtx_A, 0);
    v222 = vct_A;
    v203 = v204;
    v212 = op_Multiply_60923920(&v203, v222, 0);
    vct_A = v212;
    if (v154 + 1 < SLODWORD(pos->max_length))
    {
      *v156 = vct_A;
    }
    v156 += 2;
    v88 = (u32)v154 == 14;
    v153 = v153 + 0.3926991;
    v154 += 2;
    if (!v88)
      continue;
    break;
  }
  CleateLine(SLODWORD(pos->max_length) / 2, pos, 0);
  sdfDrawTagLinkOt(Ot[64], tag);
}

// 0x192fd90
void sbattleCylinderLineDraw(const sdfVector4_t *pCenter, f32 radius, f32 height, const sdfColor32_t *col, bool mat, const sdfMatrix4_t *pMat) {
  ;
}

// 0x192fda0
void sbattleSphereLineDraw(const sdfVector4_t *center, const sdfVector4_t *rot, f32 rad, f32 area_r1, f32 area_r2, const sdfColor32_t *col) {
  ;
}

// 0x192fdb0
void sbattleLineDraw(const sdfVector4_t *pos1, const sdfVector4_t *pos2, const sdfColor32_t *col) {
  f32 z;
  f32 y;
  f32 x;
  f32 v7;
  f32 v8;
  f32 v9;
  s32 rgba;
  sdfColor_t color;
  sdfVector3_t v12;
  sdfVector3_t v13;

  z = pos2->z;
  y = pos2->y;
  x = pos2->x;
  v7 = pos1->z;
  v8 = pos1->y;
  v9 = pos1->x;
  rgba = col->rgba;
  color.b = (f32)BYTE2(rgba) / 255.0;
  color.a = (f32)HIBYTE(rgba) / 255.0;
  color.r = (f32)(u8)rgba / 255.0;
  color.g = (f32)BYTE1(rgba) / 255.0;
  v13.z = z / -100.0;
  v13.y = y / -100.0;
  v13.x = x / -100.0;
  v12.z = v7 / -100.0;
  v12.y = v8 / -100.0;
  v12.x = v9 / -100.0;
  DrawLine(v12, v13, color, 0);
}

// 0x192feb0
bool sBtlDebug_GridDraw(void) {
  s64 status;

  status = sbtldbwk->status;
  InfoDisp((status & 4) != 0, 0);
  return 1;
}

// 0x192ff80
bool sbattleCreateHitC(SBTLDMG_HITLISTWORK *lwk, SBTLDMG_HITWORK *wk) {
  SBTLDMG_HITWORK *v5;
  s64 v6;
  SBTLDMG_HITWORK *next;
  SBTLDMG_HITWORK *v8;
  s32 v9;
  f32 rad;
  s32 side;
  f32 rad_area;
  u32 flg;
  s64 v15;
  s32 eListID;
  sdfVector4_t *v18;
  s32 v19;
  struct sdfVector4_t rot;
  s32 serialID;
  SBTLDMG_CYLINDERWORK fields;
  s32 v25;
  s32 v26;
  struct sdfVector4_t pos;
  struct sdfVector4_t v28;

  v5 = Allocate(SBTLDMG_HITWORK);
  _ctor(v5, 0);
  v6 = *(u64 *)&wk->acterID;
  v5->lwk = 0;
  *(u64 *)&v5->acterID = v6;
  v5->skillid = wk->skillid;
  *(u64 *)&v5->starttime = *(u64 *)&wk->starttime;
  v5->prev = 0;
  v5->next = 0;
  v5->hitlwk = 0;
  v5->pBasic = 0;
  v5->hEveUnit = 0;
  v5->hPartsList = 0;
  v5->hittype = wk->hittype;
  next = lwk->wk;
  if (next)
  {
    do
    {
      v8 = next;
      next = next->next;
    }
    while (next);
    v8->next = v5;
    v5->prev = v8;
    v9 = lwk->num + 1;
  }
  else
  {
    lwk->wk = v5;
    v9 = 1;
  }
  lwk->num = v9;
  v5->skillflg = wk->skillflg;
  *(u32 *)&v5->area = *(u32 *)&wk->area;
  rad = wk->rad;
  v5->attr_flg = wk->attr_flg;
  side = wk->side;
  v5->rad = rad;
  rad_area = wk->rad_area;
  v5->side = side;
  flg = wk->flg;
  v5->rad_area = rad_area;
  v15 = *(u64 *)&wk->area_r;
  v5->flg = flg;
  eListID = wk->eListID;
  *(u64 *)&v5->area_r = v15;
  v5->eListID = eListID;
  pos = wk->pos;
  vct_A = pos;
  v18 = &v5->pos;
  v19 = (u8)byte_5755EF5;
  *v18 = vct_A;
  rot = wk->rot;
  if (v19)
    goto LABEL_13;
  goto LABEL_22;
  if (v26)
  {
LABEL_13:
    goto LABEL_14;
  }
LABEL_22:
  v28 = rot;
  rot = v28;
LABEL_14:
  vct_A = rot;
  v5->st = 1;
  v5->rot = vct_A;
  serialID = lwk->serialID;
  fields = wk->cy->fields;
  v25 = wk->serialID;
  v5->eListID = wk->eListID;
  v5->serialID = v25;
  *(SBTLDMG_CYLINDERWORK *)((u64)v5->cy + 16) = fields;
  lwk->serialID = serialID + 1;
  return 1;
}

// 0x1930320
bool sBtlDebug_DeleteHitList(void) {
  SBTLDMG_HITLISTWORK *dbghitList;
  SBTLDMG_HITLISTWORK *p_dbghitList;

  if (!wk)
    return 1;
  dbghitList = wk->dbghitList;
  if (!dbghitList)
    return 1;
  dbghitList = wk->dbghitList;
  sBtlDeleteHitList(dbghitList);
  p_dbghitList = &wk->dbghitList;
  p_dbghitList = 0;
  return 1;
}

// 0x1930460
bool sbattleDrawHitList(SBTLDMG_HITLISTWORK *lwk) {
  SBTLDMG_HITWORK *wk_local;
  s32 serialID;
  SBTLDMG_HITLISTWORK *hitList;
  SBTLDMG_HITWORK *v8;
  s32 starttime;
  s32 counter;
  s32 v12;
  SBTLDMG_HITLISTWORK *v13;
  SBTLDMG_HITWORK *v14;
  SBTLDMG_HITWORK *v15;
  s32 v17;
  struct sdfVector4_t rot;
  sdfVector4_t *p_rot;
  s32 hittype;
  u16 atype;
  f32 xrad;
  _OWORD *p_x;
  __int128 v27;
  __int128 v28;
  __int128 v29;
  sdfMatrix4_t *v30;
  f32 v32;
  _OWORD *v34;
  __int128 v35;
  __int128 v36;
  __int128 v37;
  f32 height;
  struct sdfVector4_t v41;
  f32 y;
  f32 x;
  f32 w;
  f32 z;
  f32 *v48;
  f32 v50;
  f32 v51;
  f32 v52;
  f32 v53;
  f32 rad_area;
  f32 v56;
  f32 v57;
  f32 v58;
  f32 v59;
  f32 v60;
  struct sdfVector4_t pos;
  struct sdfVector4_t v62;
  struct sdfVector4_t v63;
  struct sdfVector4_t v64;
  struct sdfVector4_t v65;
  struct sdfVector4_t v66;
  _OWORD v69[4];
  sdfVector4_t v70;
  __int128 v71;
  __int128 v72;
  __int128 v73;
  sdfVector4_t v74;
  __int128 v75;
  __int128 v76;
  __int128 v77;
  sdfMatrix4_t v78;
  sdfMatrix4_t v79;
  sdfVector4_t v80;
  sdfVector4_t v82;
  sdfVector4_t v83;
  sdfVector4_t v84;

  if (!lwk->num)
    return 0;
  wk_local = lwk->wk;
  if (!wk_local)
    return 0;
  do
  {
    if (wk_local->st != 1)
      goto LABEL_7;
    if ((wk_local->flg & 0x1000) != 0)
    {
      serialID = wk_local->serialID;
      hitList = wk->hitList;
      v8 = sBtlSearchHit_SerialID(hitList, serialID);
      if (!v8)
        goto LABEL_17;
      if (v8->pathflg != 1)
        goto LABEL_7;
    }
LABEL_17:
    counter = wk_local->counter;
    starttime = wk_local->starttime;
    if (starttime > counter || wk_local->life + starttime <= counter && (wk_local->flg & 0x20000) == 0)
      goto LABEL_7;
    v12 = wk_local->serialID;
    v13 = wk->hitList;
    v14 = sBtlSearchHit_SerialID(v13, v12);
    if (!v14)
      goto LABEL_7;
    v15 = v14;
    pos = v14->pos;
    vct_A = pos;
    v17 = (u8)byte_5755EF5;
    wk_local->pos = vct_A;
    rot = v15->rot;
    if (v17)
    {
      goto LABEL_33;
    }
    else
    {
      v63 = v15->rot;
      rot = v63;
LABEL_33:
      vct_A = rot;
      goto LABEL_34;
    }
    v64 = rot;
    vct_A = v64;
LABEL_34:
    p_rot = &wk_local->rot;
    hittype = wk_local->hittype;
    wk_local->rot = vct_A;
    if (hittype == 2)
    {
      v65 = *p_rot;
      vct_A = v65;
      vct_B = vct_A;
      xrad = wk_local->cy->xrad;
      sub_1949540(0, xrad * 0.017453292);
      p_x = &vf00.x;
      v27 = p_x[5];
      v28 = p_x[6];
      v29 = p_x[7];
      v74 = (sdfVector4_t)p_x[4];
      v75 = v27;
      v76 = v28;
      v77 = v29;
      v30 = v69;
      v69[0] = v74;
      v69[1] = v75;
      v69[2] = v76;
      v69[3] = v77;
LABEL_77:
      sBtlGetQuatFromMatrix(v30);
      Mult();
      ToMatrix();
      vct_A = (struct sdfVector4_t)xmmword_3CFEDD0;
      get_transpose(&v79, &mtx_A, 0);
      v78 = v79;
      v80 = op_Multiply_60923920(&v78, vct_A, 0);
      vct_A = v80;
      height = wk_local->cy->height;
      vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, height * 0.5);
      v41 = wk_local->pos;
      vct_B = v41;
      vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
      goto LABEL_7;
    }
    if (hittype == 1)
    {
      v66 = *p_rot;
      vct_A = v66;
      vct_B = vct_A;
      v32 = wk_local->cy->xrad;
      sub_1949540(0, v32 * 0.017453292);
      v34 = &vf00.x;
      v35 = v34[5];
      v36 = v34[6];
      v37 = v34[7];
      v74 = (sdfVector4_t)v34[4];
      v75 = v35;
      v76 = v36;
      v77 = v37;
      v30 = &v70;
      v70 = v74;
      v71 = v75;
      v72 = v76;
      v73 = v77;
      goto LABEL_77;
    }
    if (hittype)
      goto LABEL_7;
    atype = wk_local->atype;
    if ((atype & 0x4000) == 0)
    {
      v62 = *p_rot;
      vct_A = v62;
      goto LABEL_139;
LABEL_158:
      goto LABEL_160;
LABEL_139:
      goto LABEL_160;
    }
    x = wk_local->rot.x;
    y = wk_local->rot.y;
    z = wk_local->rot.z;
    w = wk_local->rot.w;
    if ((atype & 4) != 0)
    {
      v82.x = x;
      v82.y = y;
      v82.z = z;
      v82.w = w;
      sBtlGetRotateDeg(v82, 180.0);
      goto LABEL_145;
    }
    v48 = &vf00.x;
    v48[4] = x;
    v48[5] = y;
    v48[6] = z;
    v48[7] = w;
LABEL_145:
    if ((wk_local->atype & 8) != 0)
    {
      v50 = wk_local->rot.x;
      v51 = wk_local->rot.y;
      v52 = wk_local->rot.z;
      v53 = wk_local->rot.w;
      rad_area = wk_local->rad_area;
      v83.x = v50;
      v83.y = v51;
      v83.z = v52;
      v83.w = v53;
      sBtlGetRotateDeg(v83, rad_area);
    }
    if ((wk_local->atype & 0x10) == 0)
      goto LABEL_160;
    v56 = wk_local->rot.x;
    v57 = wk_local->rot.y;
    v58 = wk_local->rot.z;
    v59 = wk_local->rot.w;
    v60 = wk_local->rad_area;
    v84.x = v56;
    v84.y = v57;
    v84.z = v58;
    v84.w = v59;
    sBtlGetRotateDeg(v84, -v60);
    goto LABEL_158;
LABEL_160:
LABEL_7:
    wk_local = wk_local->next;
  }
  while (wk_local);
  return 1;
}

// 0x190eb00
void sbattleDraw3DSphere(const sdfVector4_t *pCenter, f32 r, u32 c, bool mat, const sdfMatrix4_t *pMat) {
  sdfVector4_t *v9;
  u32 *v10;
  sdfDrawTag_t *v11;
  int32x4_t v12;
  __int128 v14;
  __int128 v16;
  __int128 v18;
  _OWORD *p_x;
  s32 v20;
  __int128 v21;
  sdfMatrix4_t *p_identityMatrix;
  __int128 v24;
  __int128 v25;
  s32 v26;
  f32 v27;
  _OWORD *v28;
  s32 v29;
  f32 v30;
  f32 v31;
  f32 v32;
  f32 v33;
  f32 v34;
  f32 v35;
  f32 v36;
  f32 v37;
  _OWORD *v40;
  s32 v41;
  f32 v43;
  f32 v44;
  f32 v45;
  f32 v47;
  f32 v48;
  f32 v50;
  s64 v51;
  sdfVector4_t *v52;
  bool v53;
  f32 v55;
  f32 v56;
  f32 v57;
  f32 v58;
  f32 v59;
  f32 v60;
  f32 v61;
  bool v62;
  f32 v63;
  f32 v64;
  f32 v65;
  f32 v66;
  f32 v67;
  f32 v68;
  f32 v70;
  f32 v71;
  f32 v72;
  _OWORD *v78;
  s32 v79;
  _OWORD *v80;
  __int128 v81;
  __int128 v82;
  __int128 v83;
  __int128 v84;
  __int128 v87;
  __int128 v88;
  __int128 v89;
  s32 v91;
  f32 v93;
  s32 v94;
  __int128 v95;
  __int128 v96;
  __int128 v97;
  __int128 v98;
  sdfMatrix4_t v99;
  sdfMatrix4_t v100;
  sdfMatrix4_t v101;
  sdfVector4_t v103;
  sdfVector4_t v105;

  v9 = NewSpecific(sdfVector4_t, 0x16u);
  v10 = NewSpecific(uint, 0x16u);
  v11 = Allocate(sdfDrawTag_t);
  _ctor(v11, 0);
  sdfDrawTagInit(v11);
  v12 = vdupq_n_s32(c);
  v10[20] = c;
  v10[21] = c;
  *(int32x4_t *)&v10[0] = v12;
  *(int32x4_t *)&v10[4] = v12;
  *(int32x4_t *)&v10[8] = v12;
  *(int32x4_t *)&v10[12] = v12;
  *(int32x4_t *)&v10[16] = v12;
  if (!mat)
  {
    goto LABEL_14;
  }
  v14 = *(_OWORD *)&pMat->m01;
  *(_OWORD *)&v101.m00 = *(_OWORD *)&pMat->m00;
  *(_OWORD *)&v101.m01 = v14;
  v16 = *(_OWORD *)&pMat->m03;
  *(_OWORD *)&v101.m02 = *(_OWORD *)&pMat->m02;
  *(_OWORD *)&v101.m03 = v16;
  v18 = *(_OWORD *)&v101.m01;
  p_x = &vf00.x;
  v20 = (u8)byte_575608E;
  p_x[4] = *(_OWORD *)&v101.m00;
  p_x[5] = v18;
  v21 = *(_OWORD *)&v101.m03;
  p_x[6] = *(_OWORD *)&v101.m02;
  p_x[7] = v21;
  if (!v20)
  {
    goto LABEL_10;
  }
LABEL_10:
LABEL_14:
  v24 = *(_OWORD *)&identityMatrix.m00;
  v25 = *(_OWORD *)&identityMatrix.m01;
  p_identityMatrix = &identityMatrix;
  v26 = 0;
  v27 = -1.0;
  v95 = v24;
  v96 = v25;
  v97 = *(_OWORD *)&p_identityMatrix->m02;
  v98 = *(_OWORD *)&p_identityMatrix->m03;
  do
  {
    v91 = v26;
    v29 = 0;
    v30 = 0.0;
    do
    {
      v31 = v30 + 0.31415927;
      v32 = (f32)(v31 + 1.5708) * 0.15915494;
      v33 = (s32)v32;
      if (v32 == INFINITY)
        v33 = -2147500000.0;
      v34 = v32 - v33;
      if ((f32)(v32 - v33) <= 0.5)
      {
        if (v34 < -0.5)
          v34 = v34 + 1.0;
      }
      else
      {
        v34 = v34 + v27;
      }
      if (v34 <= 0.25)
      {
        if (v34 < -0.25)
          v34 = -0.5 - v34;
      }
      else
      {
        v34 = 0.5 - v34;
      }
      v35 = v31 * 0.15915494;
      v36 = (s32)(v31 * 0.15915494);
      if ((f32)(v31 * 0.15915494) == INFINITY)
        v36 = -2147500000.0;
      v37 = v35 - v36;
      if ((f32)(v35 - v36) <= 0.5)
      {
        if (v37 < -0.5)
          v37 = v37 + 1.0;
      }
      else
      {
        v37 = v37 + v27;
      }
      v94 = v29;
      if (v37 <= 0.25)
      {
        if (v37 < -0.25)
        {
          v37 = -0.5 - v37;
LABEL_41:
          goto LABEL_42;
        }
        else
        {
          goto LABEL_41;
        }
      }
      else
      {
        v37 = 0.5 - v37;
        goto LABEL_41;
      }
LABEL_42:
      v40 = &vf00.x;
      v41 = (u8)byte_5756094;
      v40[4] = v95;
      v40[5] = v96;
      v40[6] = v97;
      v40[7] = v98;
      if (v41)
      {
        goto LABEL_45;
      }
      else
      {
        goto LABEL_45;
      }
LABEL_45:
      SetRow(&mtx_A, 3, pCenter, 0);
      v93 = v31;
      v43 = v34 * 4.0;
      v44 = v37 * 4.0;
      v45 = v43 * v43;
      *(u64 *)&vct_A.z = 0;
      v47 = (f32)((f32)((f32)((f32)((f32)((f32)(v34 * 4.0) * 1.5708) + (f32)((f32)(v43 * (f32)(v43 * v43)) * -0.6459637)) + (f32)((f32)((f32)(v43 * v43) * (f32)(v43 * (f32)(v43 * v43))) * 0.07968968)) + (f32)((f32)(v45 * (f32)(v45 * (f32)(v43 * (f32)(v43 * v43)))) * -0.0046737655)) + (f32)((f32)(v45 * (f32)(v45 * (f32)(v45 * (f32)(v43 * (f32)(v43 * v43))))) * 0.00015148419))
          * r;
      v48 = (f32)((f32)((f32)((f32)((f32)((f32)(v37 * 4.0) * 1.5708) + (f32)((f32)(v44 * (f32)(v44 * v44)) * -0.6459637)) + (f32)((f32)((f32)(v44 * v44) * (f32)(v44 * (f32)(v44 * v44))) * 0.07968968)) + (f32)((f32)((f32)(v44 * v44) * (f32)((f32)(v44 * v44) * (f32)(v44 * (f32)(v44 * v44)))) * -0.0046737655)) + (f32)((f32)((f32)(v44 * v44) * (f32)((f32)(v44 * v44) * (f32)((f32)(v44 * v44) * (f32)(v44 * (f32)(v44 * v44))))) * 0.00015148419))
          * r;
      vct_A.x = v48;
      vct_A.y = v47;
      vct_A.w = 1.0;
      get_transpose(&v101, &mtx_A, 0);
      v100 = v101;
      v50 = 0.0;
      v51 = 0;
      v52 = &v9[1];
      vct_A = op_Multiply_60923920(&v100, vct_A, 0);
      do
      {
        if (v51 < *(s32 *)((char *)v9 + 24))
          v52[-1] = vct_A;
        v50 = v50 + 0.5711987;
        v55 = (f32)(v50 + 1.5708) * 0.15915494;
        v56 = (s32)v55;
        if (v55 == INFINITY)
          v56 = -2147500000.0;
        v57 = v55 - v56;
        v58 = v57 + 1.0;
        if (v57 >= -0.5)
          v58 = v57;
        if (v57 > 0.5)
          v59 = v57 + v27;
        else
          v59 = v58;
        v60 = -0.5 - v59;
        v61 = 0.5 - v59;
        if (v59 >= -0.25)
          v60 = v59;
        v62 = v59 <= 0.25;
        v63 = v50 * 0.15915494;
        if (v62)
          v64 = v60;
        else
          v64 = v61;
        v65 = (s32)v63;
        if (v63 == INFINITY)
          v65 = -2147500000.0;
        v66 = v63 - v65;
        if (v66 <= 0.5)
        {
          if (v66 < -0.5)
            v66 = v66 + 1.0;
        }
        else
        {
          v66 = v66 + v27;
        }
        v67 = -0.5 - v66;
        if (v66 >= -0.25)
          v67 = v66;
        if (v66 > 0.25)
          v68 = 0.5 - v66;
        else
          v68 = v67;
        v70 = v64 * 4.0;
        v71 = v68 * 4.0;
        v72 = v70 * v70;
        vct_A.w = 0.0;
        vct_A.x = v48
                            * (f32)((f32)((f32)((f32)((f32)((f32)(v64 * 4.0) * 1.5708) + (f32)((f32)(v70 * (f32)(v70 * v70)) * -0.6459637)) + (f32)((f32)((f32)(v70 * v70) * (f32)(v70 * (f32)(v70 * v70))) * 0.07968968)) + (f32)((f32)(v72 * (f32)(v72 * (f32)(v70 * (f32)(v70 * v70)))) * -0.0046737655)) + (f32)((f32)(v72 * (f32)(v72 * (f32)(v72 * (f32)(v70 * (f32)(v70 * v70))))) * 0.00015148419));
        vct_A.y = v47;
        vct_A.z = v48
                            * (f32)((f32)((f32)((f32)((f32)((f32)(v68 * 4.0) * 1.5708) + (f32)((f32)(v71 * (f32)(v71 * v71)) * -0.6459637)) + (f32)((f32)((f32)(v71 * v71) * (f32)(v71 * (f32)(v71 * v71))) * 0.07968968)) + (f32)((f32)((f32)(v71 * v71) * (f32)((f32)(v71 * v71) * (f32)(v71 * (f32)(v71 * v71)))) * -0.0046737655)) + (f32)((f32)((f32)(v71 * v71) * (f32)((f32)(v71 * v71) * (f32)((f32)(v71 * v71) * (f32)(v71 * (f32)(v71 * v71))))) * 0.00015148419));
        v27 = -1.0;
        vct_A.w = 1.0;
        get_transpose(&v101, &mtx_A, 0);
        v105 = vct_A;
        v100 = v101;
        v103 = op_Multiply_60923920(&v100, v105, 0);
        vct_A = v103;
        if (v51 + 1 < *(s32 *)((char *)v9 + 24))
        {
          *v52 = vct_A;
        }
        v52 += 2;
        v53 = (u32)v51 == 20;
        v51 += 2;
      }
      while (!v53);
      CleateLine(*(u32 *)((char *)v9 + 24), v9, 0);
      v29 = v94 + 1;
      v30 = v93;
    }
    while (v94 != 8);
    sub_1949540(0, 1.5708);
    v78 = &vf00.x;
    v79 = (u8)byte_5756098;
    v78[8] = v95;
    v78[9] = v96;
    v78[10] = v97;
    v78[11] = v98;
    if (v79)
    {
      goto LABEL_118;
    }
    else
    {
    }
LABEL_118:
    v80 = &vf00.x;
    v81 = v80[9];
    *(_OWORD *)&v100.m00 = v80[8];
    *(_OWORD *)&v100.m01 = v81;
    v82 = v80[11];
    *(_OWORD *)&v100.m02 = v80[10];
    *(_OWORD *)&v100.m03 = v82;
    v83 = v80[5];
    *(_OWORD *)&v99.m00 = v80[4];
    *(_OWORD *)&v99.m01 = v83;
    v84 = v80[7];
    *(_OWORD *)&v99.m02 = v80[6];
    *(_OWORD *)&v99.m03 = v84;
    op_Multiply(&v101, &v100, &v99, 0);
    v87 = *(_OWORD *)&v101.m01;
    v88 = *(_OWORD *)&v101.m02;
    v89 = *(_OWORD *)&v101.m03;
    *(_OWORD *)&mtx_A.m00 = *(_OWORD *)&v101.m00;
    *(_OWORD *)&mtx_A.m01 = v87;
    *(_OWORD *)&mtx_A.m02 = v88;
    *(_OWORD *)&mtx_A.m03 = v89;
    v28 = &vf00.x;
    v26 = v91 + 1;
    v95 = v28[4];
    v96 = v28[5];
    v97 = v28[6];
    v98 = v28[7];
  }
  while (v91 != 1);
  sdfDrawTagLinkOt(Ot[64], v11);
}

// 0x1924fc0
bool sbattleCheckDamageTarget(SBTLUNIT_WORK *wk) {
  u32 status;
  bool v3;
  bool result;

  status = wk->actwk->status;
  v3 = status > 0xE || ((1 << status) & 0x4C00) == 0;
  result = false;
  if (v3 && status != 30 && wk->actaiwk->mode != 9 && status != 40 && wk->mode > 4)
    return true;
  return result;
}

// 0x1931070
void sbattleDrawMatrix(const sdfMatrix4_t *mat) {
  ;
}

// 0x192a8f0
void sbattleDrawPoly3(const sdfVector4_t *pos0, const sdfVector4_t *pos1, const sdfVector4_t *pos2, u32 col0, u32 col1, u32 col2, DDS3_OT otno) {
  ;
}

// 0x192e480
void sbattleDrawPoly4(const sdfVector4_t *pos0, const sdfVector4_t *pos1, const sdfVector4_t *pos2, const sdfVector4_t *pos3, u32 col0, u32 col1, u32 col2, u32 col3, DDS3_OT otno) {
  ;
}

// 0x1931080
void sBtlDebug_DrawAIDebug(void) {
  ;
}

// 0x190b2d0
void sBtlDebug_SetVisualData(SBTLUNIT_WORK *wk) {
  s32 devilid;
  DEVILDATA_WORK *DevilData;
  s32 minorno;
  VISUALDATA_WORK *VisualData;
  s32 v8;
  VISUALDATA_WORK *v9;
  u16 v10;
  u16 major;
  s32 minor;
  MOTIONDATA_WORK *MotionVisualData;
  sdatUnitWork_t *para;
  u32 stflg;
  s64 v16;
  u32 v17;
  sdatParaWork_t *now;
  SBTLACTAI_WORK *actaiwk;
  sdfVector4_t *p_searchpos;
  struct sdfVector4_t vct_A_local;
  sdfVector2_t *p_hpPosition;
  sdfVector4_t *p_movepos;
  SBTLACTAI_WORK *v28;
  sdatUnitWork_t *v29;
  SBTLACTAI_WORK *p_frid_area_r;
  int8x8_t *v31;
  f32 scale;
  SKLID *haveskill;
  SKLID *v34;

  devilid = wk->para->devilid;
  if (wk->major)
  {
    DevilData = sBtlGetDevilData(devilid, -1);
    minorno = DevilData->minorno;
    VisualData = sBtlGetVisualData(1u, minorno);
    v8 = DevilData->minorno;
    v9 = VisualData;
    v10 = 1;
  }
  else
  {
    DevilData = sBtlGetDevilData(devilid, -1);
    major = wk->major;
    minor = wk->minor;
    v9 = sBtlGetVisualData(major, minor);
    v8 = wk->minor;
    v10 = wk->major;
  }
  MotionVisualData = sBtlGetMotionVisualData(v10, v8, 0);
  para = wk->para;
  para->level = DevilData->level;
  stflg = DevilData->stflg;
  wk->bunriid = DevilData->bunriid;
  wk->aisyoid = DevilData->aishou;
  v16 = *(u64 *)&DevilData->str;
  v17 = stflg | wk->status;
  now = para->now;
  wk->status = v17;
  *(u64 *)&now->str = v16;
  para->seikaku = DevilData->seikaku;
  if ((v17 & 0x8000000) != 0)
  {
    wk->motion_setno = DevilData->setmotionno;
    actaiwk = wk->actaiwk;
    goto LABEL_19;
  }
  else
  {
    wk->motion_setno = 0;
    actaiwk = wk->actaiwk;
    goto LABEL_19;
  }
LABEL_19:
  p_searchpos = &actaiwk->searchpos;
  vct_A_local = vct_A;
  *p_searchpos = vct_A_local;
  p_hpPosition = &wk->hpPosition;
  p_movepos = &wk->actaiwk->movepos;
  vct_A_local.x = 0.0;
  *p_movepos = vct_A;
  v28 = wk->actaiwk;
  v29 = wk->para;
  p_frid_area_r = &v28->frid_area_r;
  v31 = v29->now;
  *(int32x2_t *)&v28->search_area_r = vrev64_s32(*(int32x2_t *)&DevilData->frid_area_r);
  v31[2].n64_u64[0] = vbsl_s8(vdup_lane_s32(vceq_s32(*(int32x2_t *)&DevilData->hp, *(int32x2_t *)&vct_A_local.x), 0), (int8x8_t)0x3200000032LL, *(int8x8_t *)&DevilData->hp).n64_u64[0];
  scale = v9->scale;
  wk->size = v9->size;
  wk->scale.x = scale;
  wk->scale.y = v9->scale;
  wk->scale.z = v9->scale;
  wk->scale.w = v9->scale;
  v28->hit_area_r = v9->hit_area_r;
  v28->priv_area_r = MotionVisualData->m_mv_area_r;
  haveskill = v29->haveskill;
  p_frid_area_r->klass = *(SBTLACTAI_WORK **)&DevilData->frid_area_r;
  v34 = DevilData->haveskill;
  haveskill[2] = v34[0];
  haveskill[3] = v34[1];
  haveskill[4] = v34[2];
  haveskill[5] = v34[3];
  *p_hpPosition = v9->hp_pos;
  p_hpPosition[12] = v9->shild_pos;
}

// 0x1916e40
void sbattleSetUnitPara(SBTLUNIT_WORK *unit, s32 flg, s32 point) {
  s32 v7;
  sdatUnitWork_t *para;
  u8 level;
  sdatParaWork_t *now;
  s32 hp;
  s32 v12;
  sdatParaWork_t *v13;
  s32 maxhp;
  s32 v15;
  sdatParaWork_t *v16;
  s32 mp;
  s32 v18;
  sdatParaWork_t *v19;
  s32 maxmp;
  s32 v21;
  sdatParaWork_t *v22;
  u16 tec;
  sdatUnitWork_t *v24;
  u16 vice;
  sdatParaWork_t *v28;
  u16 str;
  sdatParaWork_t *v30;
  u16 vit;
  sdatParaWork_t *v32;
  u16 luck;
  u32 v36;
  SBTLDEBUG_WORK *v37;
  s8 *p_level;
  s32 *p_hp;
  s32 v41;
  s32 *p_maxhp;
  s32 magMax;
  s16 *p_str;
  s16 *p_vice;
  s32 side;
  SBTLEXP_LISTWORK *expList;
  s32 v53;
  SBATTLE_WORK *wk_local;
  s32 *p_sprit_waza;

  if ((u32)flg > 3)
  {
    v7 = 0;
  }
  else
  {
    v7 = dword_3D04600[flg];
    if ((u32)point > 0xD)
      return;
  }
  switch (point)
  {
    case 0:
      if (flg == 4)
      {
        para = unit->para;
        level = para->level;
        LOBYTE(v7) = 2 * level;
      }
      else
      {
        para = unit->para;
        level = para->level;
        if (flg == 5)
          LOBYTE(v7) = -((u32)(char)(level + (level >> 7)) >> 1);
      }
      para->level = level + v7;
      p_level = &para->level;
      LimitRange_4(p_level, 1, 99);
      return;
    case 1:
      if (flg == 4)
      {
        now = unit->para->now;
        hp = now->hp;
        v7 = 2 * hp;
      }
      else if (flg == 5)
      {
        now = unit->para->now;
        hp = now->hp;
        if (hp >= 0)
          v12 = now->hp;
        else
          v12 = hp + 1;
        v7 = -(v12 >> 1);
      }
      else
      {
        now = unit->para->now;
        hp = now->hp;
      }
      now->hp = hp + v7;
      p_hp = &now->hp;
      goto LABEL_92;
    case 2:
      if (flg == 4)
      {
        v13 = unit->para->now;
        maxhp = v13->maxhp;
        v7 = 2 * maxhp;
      }
      else if (flg == 5)
      {
        v13 = unit->para->now;
        maxhp = v13->maxhp;
        if (maxhp >= 0)
          v15 = v13->maxhp;
        else
          v15 = maxhp + 1;
        v7 = -(v15 >> 1);
      }
      else
      {
        v13 = unit->para->now;
        maxhp = v13->maxhp;
      }
      v41 = maxhp + v7;
      v13->maxhp = maxhp + v7;
      p_maxhp = &v13->maxhp;
      goto LABEL_134;
    case 3:
      if (flg == 4)
      {
        v16 = unit->para->now;
        mp = v16->mp;
        v7 = 2 * mp;
      }
      else if (flg == 5)
      {
        v16 = unit->para->now;
        mp = v16->mp;
        if (mp >= 0)
          v18 = v16->mp;
        else
          v18 = mp + 1;
        v7 = -(v18 >> 1);
      }
      else
      {
        v16 = unit->para->now;
        mp = v16->mp;
      }
      v16->mp = mp + v7;
      p_hp = &v16->mp;
LABEL_92:
      magMax = p_hp[1];
      goto LABEL_94;
    case 4:
      if (flg == 4)
      {
        v19 = unit->para->now;
        maxmp = v19->maxmp;
        v7 = 2 * maxmp;
      }
      else if (flg == 5)
      {
        v19 = unit->para->now;
        maxmp = v19->maxmp;
        if (maxmp >= 0)
          v21 = v19->maxmp;
        else
          v21 = maxmp + 1;
        v7 = -(v21 >> 1);
      }
      else
      {
        v19 = unit->para->now;
        maxmp = v19->maxmp;
      }
      v41 = maxmp + v7;
      v19->maxmp = maxmp + v7;
      p_maxhp = &v19->maxmp;
      goto LABEL_134;
    case 5:
      if (flg == 4)
      {
        v28 = unit->para->now;
        str = v28->str;
        LOWORD(v7) = 2 * str;
      }
      else
      {
        v28 = unit->para->now;
        str = v28->str;
        if (flg == 5)
          LOWORD(v7) = -(s16)((u32)(s16)(str + (str >> 15)) >> 1);
      }
      v28->str = str + v7;
      p_str = &v28->str;
      goto LABEL_144;
    case 6:
      if (flg == 4)
      {
        v30 = unit->para->now;
        vit = v30->vit;
        LOWORD(v7) = 2 * vit;
      }
      else
      {
        v30 = unit->para->now;
        vit = v30->vit;
        if (flg == 5)
          LOWORD(v7) = -(s16)((u32)(s16)(vit + (vit >> 15)) >> 1);
      }
      v30->vit = vit + v7;
      p_str = &v30->vit;
      goto LABEL_144;
    case 7:
      if (flg == 4)
      {
        v22 = unit->para->now;
        tec = v22->tec;
        LOWORD(v7) = 2 * tec;
      }
      else
      {
        v22 = unit->para->now;
        tec = v22->tec;
        if (flg == 5)
          LOWORD(v7) = -(s16)((u32)(s16)(tec + (tec >> 15)) >> 1);
      }
      v22->tec = tec + v7;
      p_str = &v22->tec;
      goto LABEL_144;
    case 8:
      if (flg == 4)
      {
        v32 = unit->para->now;
        luck = v32->luck;
        LOWORD(v7) = 2 * luck;
      }
      else
      {
        v32 = unit->para->now;
        luck = v32->luck;
        if (flg == 5)
          LOWORD(v7) = -(s16)((u32)(s16)(luck + (luck >> 15)) >> 1);
      }
      v32->luck = luck + v7;
      p_str = &v32->luck;
LABEL_144:
      LimitRange_2(p_str, 0, 40);
      return;
    case 9:
      if (flg == 4)
      {
        v24 = unit->para;
        vice = v24->vice;
        LOWORD(v7) = 2 * vice;
      }
      else if (flg == 5)
      {
        v24 = unit->para;
        vice = v24->vice;
        LOWORD(v7) = -(s16)((u32)(s16)(vice + (vice >> 15)) >> 1);
      }
      else
      {
        v24 = unit->para;
        vice = v24->vice;
      }
      v24->vice = vice + v7;
      p_vice = &v24->vice;
      LimitRange_2(p_vice, 0, 4000);
      side = unit->side;
      if ((side & 2) != 0)
      {
        wk->spirit_enemy = unit->para->vice;
        sBtlViceAddEnemyHD(unit, 0, 0, 4000);
        side = unit->side;
      }
      if ((side & 0x81) == 1)
      {
        expList = wk->expList;
        v53 = unit->para->vice;
        sBtlSetVicePara(expList, v53);
      }
      return;
    case 10:
      v36 = sbtldbwk->para_bstno + v7;
      sbtldbwk->para_bstno = v36;
      if (v36 >= 0x15)
      {
        sbtldbwk->para_bstno = 20;
LABEL_64:
        v37 = sbtldbwk;
        if (v37->para_bstno)
          return;
        goto LABEL_75;
      }
      {
        goto LABEL_64;
      }
      v37 = sbtldbwk;
      if (v37->para_bstno)
        return;
LABEL_75:
      v37 = sbtldbwk;
      v37->para_bstno = 0;
      return;
    case 11:
      if (flg == 4)
      {
        v7 = 2 * wk->mag;
      }
      else if (flg == 5)
      {
        v7 = wk->mag / -2;
      }
      else
      {
      }
      wk_local = wk;
      magMax = wk_local->magMax;
      p_hp = &wk_local->mag;
      wk_local->mag += (s16)v7;
LABEL_94:
      LimitRange(p_hp, 0, magMax);
      return;
    case 12:
      if (flg == 4)
      {
        v7 = 2 * wk->magMax;
      }
      else if (flg == 5)
      {
        v7 = wk->magMax / -2;
      }
      else
      {
      }
      p_maxhp = &wk->magMax;
      v41 = *p_maxhp + v7;
      *p_maxhp = v41;
LABEL_134:
      LimitRange(p_maxhp, 1, v41);
      return;
    case 13:
      if (flg == 4)
      {
        v7 = 2 * wk->sprit_waza;
      }
      else if (flg == 5)
      {
        v7 = wk->sprit_waza / -2;
      }
      else
      {
      }
      p_sprit_waza = &wk->sprit_waza;
      *p_sprit_waza += (s16)v7;
      LimitRange(p_sprit_waza, 0, 4000);
      return;
    default:
      return;
  }
}

// 0x190a560
void sbattleDrawDebugMenu(s32 x, s32 y, s32 z, u32 rgba, s32 id) {
  char *v11;

  v11 = sblist_modelmenu[id];
  DbgText(16 * x, 8 * y, v11, 0, 109, 24, 0);
}

// 0x1931100
void sbattleDrawDebugMenuCamera(s32 x, s32 y, s32 z, u32 rgba, s32 id) {
  char *DebugMenuFontCamera;

  DebugMenuFontCamera = sbattleGetDebugMenuFontCamera(id);
  DbgText(16 * x, 8 * y, DebugMenuFontCamera, rgba, 109, 24, 0);
}

// 0x1931680
void sbattleDrawDebugMenuTime(s32 x, s32 y, s32 z, u32 rgba, s32 id) {
  char *DebugMenuFontTime;

  DebugMenuFontTime = sbattleGetDebugMenuFontTime(id);
  DbgText(16 * x, 8 * y, DebugMenuFontTime, rgba, 109, 24, 0);
}

// 0x190aa90
void sbattleDrawMotionList(s32 x, s32 y, s32 z, u32 rgba, s32 listid, s32 id) {
  s32 v13;
  s32 v16;
  s32 v17;
  char *v18;

  switch (listid)
  {
    case 3:
      if (rgba == 1692838528)
        v13 = 5;
      else
        v13 = 0;
      v16 = 16 * x;
      v17 = 8 * y;
      v18 = sblist_mtioncgpanel_boss[id];
      goto LABEL_42;
    case 2:
      if (rgba == 1692838528)
        v13 = 5;
      else
        v13 = 0;
      v16 = 16 * x;
      v17 = 8 * y;
      v18 = sblist_mtioncgpanel_n[id];
LABEL_42:
LABEL_44:
      DbgText(v16, v17, v18, v13, 109, 24, 0);
      return;
    case 0:
      if (rgba == 1692838528)
        v13 = 5;
      else
        v13 = 0;
      v16 = 16 * x;
      v17 = 8 * y;
      v18 = sblist_mtioncgpanel_p[id];
      goto LABEL_44;
  }
}

// 0x190e520
void sbattleDrawString(s32 x, s32 y, char *buff, s32 point, s32 flg) {
  s32 v11;
  s32 v12;
  s32 v14;
  s32 v16;
  s32 v17;
  char *v18;
  s32 v20;
  s32 v21;
  s32 v23;
  s32 v24;

  if (flg == -2)
  {
    v11 = 16 * x;
    v12 = 8 * y;
    v14 = 5;
    goto LABEL_13;
  }
  if (flg == -3)
  {
    v11 = 16 * x;
    v12 = 8 * y;
    v14 = -1;
LABEL_13:
    v16 = v11;
    v17 = v12;
    v18 = buff;
    goto LABEL_14;
  }
  if (point == flg)
  {
    v20 = 16 * x;
    v21 = 8 * y;
    v16 = v20;
    v17 = v21;
    v18 = buff;
    v14 = 4;
    goto LABEL_14;
  }
  v23 = 16 * x;
  v24 = 8 * y;
  v16 = v23;
  v17 = v24;
  v18 = buff;
  v14 = 0;
LABEL_14:
  DbgText(v16, v17, v18, v14, 109, 24, 0);
}

// 0x190e7b0
void sbattleDrawInt_Num(s32 x, s32 y, s32 data, s32 point, s32 flg) {
  char *v10;
  s32 v12;
  s32 v13;
  s32 v15;
  s32 v16;
  char *v17;
  s32 v18;
  s32 v19;
  s32 v20;
  s32 v21;

  v21 = data;
  v10 = ToString_55996800((s32)&v21, "D5", 0);
  if (point == flg)
  {
    v12 = 16 * x;
    v13 = 8 * y;
    v15 = v12;
    v16 = v13;
    v17 = v10;
    v18 = 4;
    goto LABEL_15;
  }
  v19 = 16 * x;
  v20 = 8 * y;
  v15 = v19;
  v16 = v20;
  v17 = v10;
  v18 = 0;
LABEL_15:
  DbgText(v15, v16, v17, v18, 109, 24, 0);
}

// 0x190e960
void sbattleDrawFloat_Num(s32 x, s32 y, f32 data, s32 point, s32 flg) {
  char *v10;
  s32 v12;
  s32 v13;
  s32 v15;
  s32 v16;
  char *v17;
  s32 v18;
  s32 v19;
  s32 v20;
  System_String_o format;

  *(f32 *)&format.klass = data;
  v10 = ToString_56097616(data, &format, "00000.0");
  if (point == flg)
  {
    v12 = 16 * x;
    v13 = 8 * y;
    v15 = v12;
    v16 = v13;
    v17 = v10;
    v18 = 4;
    goto LABEL_15;
  }
  v19 = 16 * x;
  v20 = 8 * y;
  v15 = v19;
  v16 = v20;
  v17 = v10;
  v18 = 0;
LABEL_15:
  DbgText(v15, v16, v17, v18, 109, 24, 0);
}

// 0x191d630
void sbattleGetPathAddTime(SBTLSKILLHIT_TBL *hwk, SBDEBUG_PATHDATA *path) {
  s32 lifetime;

  path->nef_pathtime = 1.0;
  lifetime = hwk->lifetime;
  if (lifetime)
    path->nef_addpathtime = 1.0 / (f32)lifetime;
  else
    path->nef_addpathtime = 0.0;
}

// 0x19318e0
void sBtlDebug_EffHitIdou(SBDEBUG_CSRWORK *wk, SBTLSKILLHIT_TBL *hwk, SBDEBUG_PATHDATA *path, const sdfVector4_t *poss, const sdfVector4_t *rott) {
  u32 flg;
  s32 v11;
  f32 v12;
  f32 v13;
  f32 v15;
  f32 v16;
  s64 v19;
  s64 v20;
  f32 *p_x;
  f32 v28;
  f32 v29;
  f32 v30;
  f32 dir;
  s64 v34;
  s64 v35;
  f32 shatei;
  f32 *v39;
  f32 x;
  s64 v42;
  f32 v44;
  f32 v45;
  f32 *v46;
  sdfVector4_t *v47;
  f32 v49;
  f32 *v51;
  f32 *v52;
  f32 v53;
  f32 v54;
  f32 v55;
  f32 v56;
  f32 *v59;
  f32 *v60;
  f32 *v61;
  struct sdfVector4_t v62;
  f32 z;
  f32 y;
  f32 v65;
  f32 *v66;
  f32 v67;
  struct sdfVector4_t v68;
  f32 *v69;
  f32 v70;
  f32 v71;
  f32 kasokudo;
  f32 v73;
  f32 Bezier;
  f32 v75;
  f32 v76;
  dds3ModelHandle_t *path_hModel;
  dds3ModelHandle_t *v79;
  dds3ModelHandle_t *v81;
  s32 path_motionno;
  f32 *v97;
  struct sdfVector4_t v98;
  f32 *v99;
  f32 v100;
  f32 v101;
  f32 v102;
  f32 v104;
  f32 v106;
  struct sdfVector4_t v107;
  f32 *v108;
  f32 v109;
  f32 v110;
  f32 v111;
  f32 *v112;
  struct sdfVector4_t v113;
  f32 *v114;
  f32 v115;
  f32 v116;
  f32 v117;
  f32 v119;
  f32 v121;
  struct sdfVector4_t v122;
  f32 *v123;
  f32 v124;
  f32 *v125;
  f32 *v126;
  f32 *v127;
  f32 v128;
  f32 v129;
  f32 v130;
  f32 v132;
  f32 homingpara;
  f32 v135;
  f32 *v136;
  f32 *v137;
  f32 sokudo;
  u32 v141;
  f32 nef_sokudo;
  f32 v143;
  f32 v144;
  f32 v145;
  s32 v147;
  f32 nef_pathtime;
  sdfVector4_t *p_sbtldb_hitpos;
  sdfVector4_t *p_sbtldb_hitpos2;
  f32 nef_addpathtime;
  struct sdfVector4_t sbtldb_hitpos2_local;
  f32 v163;
  float32x2_t *v165;
  float32x2_t v166;
  f32 v167;
  u32 v168;
  f32 v169;
  float32x2_t v170;
  float32x2_t v172;
  f32 v173;
  float32x2_t *v174;
  f32 *v176;
  f32 *v178;
  SBTLDEBUG_WORK *v186;
  f32 v187;
  float32x2_t *v203;
  float32x2_t v204;
  float32x2_t v205;
  u32 v206;
  f32 v207;
  f32 v208;
  f32 v209;
  float32x2_t v212;
  f32 v213;
  float32x2_t *v214;
  f32 v216;
  __int128 v217;
  f32 x2;
  f32 v222;
  f32 v223;
  f32 w;
  f32 x3;
  f32 x1;
  f32 v234;
  s64 v243;
  s64 v244;
  f32 v245;
  f32 x0;
  f32 startpos;
  SBTLSKILLHIT_TBL startpos_4;
  __int128 v251;
  __int128 v252;
  sdfVector4_t v253;
  sdfVector4_t v254;
  sdfVector4_t v255;
  sdfVector4_t v256;
  sdfVector4_t v258;
  sdfVector4_t v259;
  sdfVector4_t v260;
  sdfVector4_t v261;
  sdfVector4_t v262;
  sdfVector4_t v263;

  flg = hwk->flg;
  memset(&startpos_4, 0, 32);
  if ((~flg & 0x1100) != 0)
  {
    v13 = hwk->y + 0.0;
    v15 = hwk->x + 0.0;
    v16 = hwk->z + 0.0;
    if ((flg & 0x100) == 0)
    {
      vct_A = (struct sdfVector4_t)xmmword_3CFD5C0;
      v19 = *(u64 *)&vct_A.x;
      v20 = *(u64 *)&vct_A.z;
      ToMatrix();
      vct_A.x = v15;
      vct_A.y = v13;
      vct_A.z = v16;
      vct_A.w = 1.0;
      goto LABEL_296;
    }
    vct_A = (struct sdfVector4_t)xmmword_3CFD5C0;
    v217 = xmmword_3CFD5C0;
    ToMatrix();
    vct_A.x = v15;
    vct_A.y = v13;
    vct_A.z = v16;
    vct_A.w = 1.0;
    get_transpose(&startpos_4.apos2, &mtx_A, 0);
    *(_OWORD *)&startpos_4.x = *(_OWORD *)&startpos_4.apos2;
    *(_OWORD *)&startpos_4.area_r = *(_OWORD *)&startpos_4.motionno;
    *(_OWORD *)&startpos_4.z = v251;
    *(_OWORD *)&startpos_4.start = v252;
    v254 = op_Multiply_60923920(&startpos_4.x, vct_A, 0);
    vct_A = v254;
    p_x = &vf00.x;
    v28 = p_x[4];
    x0 = p_x[5];
    v29 = p_x[6];
    v30 = p_x[7];
    dir = hwk->dir;
    v258.w = 1.0;
    v258.x = 0.0;
    v258.y = 0.0;
    v258.z = 0.0;
    sBtlGetRotateDeg(v258, dir);
    v34 = *(u64 *)&vct_A.x;
    v35 = *(u64 *)&vct_A.z;
    ToMatrix();
    vct_A = (struct sdfVector4_t)xmmword_3CFBEC0;
    get_transpose(&startpos_4.apos2, &mtx_A, 0);
    v259 = vct_A;
    *(_OWORD *)&startpos_4.x = *(_OWORD *)&startpos_4.apos2;
    *(_OWORD *)&startpos_4.area_r = *(_OWORD *)&startpos_4.motionno;
    *(_OWORD *)&startpos_4.z = v251;
    *(_OWORD *)&startpos_4.start = v252;
    v255 = op_Multiply_60923920(&startpos_4.x, v259, 0);
    vct_A = v255;
    shatei = hwk->shatei;
    vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, shatei);
    v39 = &vf00.x;
    v39[10] = v29;
    v39[11] = v30;
    v39[8] = v28;
    v39[9] = x0;
    vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    v245 = v29;
    x = vct_A.x;
    v42 = *(u64 *)&vct_A.z;
    vct_A.x = x;
    vct_A.y = 0.0;
    *(u64 *)&vct_A.z = v42;
    v44 = v245;
    v45 = x0;
    v46 = &vf00.x;
    v46[8] = v28;
    v46[9] = v45;
    v46[10] = v44;
    v46[11] = v30;
    vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    sub_1949110(0);
    v49 = hwk->shatei;
    vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v49);
    v51 = &vf00.x;
    v51[8] = v28;
    v51[9] = v45;
    v51[10] = v44;
    v51[11] = v30;
    vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    v243 = v35;
    v244 = v34;
    startpos = v28;
    v52 = &vf00.x;
    v53 = v52[4];
    v54 = v52[5];
    v56 = v52[6];
    v55 = v52[7];
    v260.z = v44;
    v260.w = v30;
    v263.x = v53;
    v263.y = v54;
    v263.z = v56;
    v263.w = v55;
    *(u64 *)&v253.z = &startpos_4.fields;
    *(u64 *)&v253.x = hwk;
    v260.x = startpos;
    v260.y = v45;
    sBtlSetApos12(v260, v263, v253, &startpos_4, 0, v47);
    v59 = &vf00.x;
    v59[6] = v44;
    v59[7] = v30;
    v59[4] = startpos;
    v59[5] = v45;
    w = vct_A.w;
    v60 = &vf00.x;
    v60[4] = v53;
    v60[5] = v54;
    v60[6] = v56;
    v60[7] = v55;
    v61 = &vf00.x;
    v62 = *(sdfVector4_t *)&startpos_4.flg;
    z = v61[6];
    v65 = v61[4];
    y = v61[5];
    vct_A = v62;
    x3 = z;
    v66 = &vf00.x;
    v67 = v66[6];
    x1 = v66[4];
    v234 = v66[5];
    v68 = *(sdfVector4_t *)&startpos_4.klass;
    vct_A = v68;
    if ((hwk->flg & 0x400) == 0)
    {
      v69 = &vf00.x;
      v70 = 1.0;
      v71 = startpos;
      v20 = v243;
      v19 = v244;
      x2 = v69[4];
      v222 = v69[5];
      v223 = v69[6];
      kasokudo = hwk->kasokudo;
      if (kasokudo >= 0.1)
        goto LABEL_237;
LABEL_233:
      if (kasokudo > -0.1)
      {
        sokudo = hwk->sokudo;
        goto LABEL_241;
      }
LABEL_237:
      if (kasokudo <= -0.1)
      {
        if (!v141)
        {
          kasokudo = hwk->kasokudo;
        }
        v186 = sbtldbwk;
        v187 = v186->nef_sokudo + kasokudo;
        v186->nef_sokudo = v187;
        if (v187 < 0.0)
        {
          v186 = sbtldbwk;
          v186->nef_sokudo = 0.0;
        }
LABEL_242:
        nef_sokudo = sbtldbwk->nef_sokudo;
        if (nef_sokudo > 0.0)
        {
          v143 = v67;
          v144 = hwk->shatei;
          nef_sokudo = sbtldbwk->nef_sokudo;
          v145 = v144 / nef_sokudo;
          v67 = v143;
          path->nef_addpathtime = 1.0 / v145;
          goto LABEL_250;
        }
        path->nef_addpathtime = 0.0;
LABEL_250:
        v147 = sbtldb_timecnt + 1;
        sbtldb_timecnt = v147;
        if (v147 >= hwk->lifetime)
        {
          nef_addpathtime = path->nef_addpathtime;
          nef_pathtime = v70 + nef_addpathtime;
          path->nef_pathtime = v70 + nef_addpathtime;
          if ((f32)(v70 + nef_addpathtime) >= v70)
          {
LABEL_252:
            path->nef_pathtime = 0.0;
            sbtldb_timecnt = 0;
            vct_A = (struct sdfVector4_t)v217;
            p_sbtldb_hitpos = &sbtldb_hitpos;
            *p_sbtldb_hitpos = vct_A;
            p_sbtldb_hitpos2 = &sbtldb_hitpos2;
            *p_sbtldb_hitpos2 = vct_A;
            sbtldbwk->nef_sokudo = hwk->sokudo;
            sbattleResetEPLData(sbtldbwk->nef_pagecsr->point);
            nef_pathtime = path->nef_pathtime;
            vct_A = sbtldb_hitpos;
LABEL_270:
            sbtldb_hitpos2_local = sbtldb_hitpos2;
            vct_A = sbtldb_hitpos2_local;
            Bezier = sBtlGetBezier(v71, x1, x2, v65, nef_pathtime);
            v75 = sBtlGetBezier(x0, v234, v222, y, nef_pathtime);
            v163 = sBtlGetBezier(v245, v67, v223, x3, nef_pathtime);
            v73 = w;
            v76 = v163;
            goto LABEL_301;
LABEL_269:
            vct_A = sbtldb_hitpos;
            goto LABEL_270;
LABEL_268:
            goto LABEL_269;
LABEL_267:
            goto LABEL_268;
LABEL_266:
            goto LABEL_267;
          }
        }
        else
        {
          nef_pathtime = path->nef_pathtime + path->nef_addpathtime;
          path->nef_pathtime = nef_pathtime;
          if (nef_pathtime >= v70)
            goto LABEL_252;
        }
        goto LABEL_266;
      }
      if (!v141)
      {
        kasokudo = hwk->kasokudo;
      }
      sokudo = sbtldbwk->nef_sokudo + kasokudo;
LABEL_241:
      sbtldbwk->nef_sokudo = sokudo;
      goto LABEL_242;
    }
    v97 = &vf00.x;
    v97[4] = v53;
    v97[5] = v54;
    v98 = *(sdfVector4_t *)&startpos_4.flg;
    v97[6] = v56;
    v97[7] = v55;
    vct_B = v98;
    vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    v99 = &vf00.x;
    v100 = v99[6];
    v101 = v99[4];
    v102 = v99[5];
    sub_1949110(0);
    v104 = (f32)(sqrtf((f32)((f32)(v101 * v101) + (f32)(v102 * v102)) + (f32)(v100 * v100)) * hwk->apos1->per)
         * hwk->homingpara;
    v106 = v104 * 0.5;
    v106 = v104 * 0.5;
    vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v106);
    v107 = *(sdfVector4_t *)&startpos_4.flg;
    vct_B = v107;
    vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    v108 = &vf00.x;
    v110 = v108[4];
    v109 = v108[5];
    v111 = v108[6];
    v112 = &vf00.x;
    v112[4] = v53;
    v112[5] = v54;
    v113 = *(sdfVector4_t *)&startpos_4.klass;
    v112[6] = v56;
    v112[7] = v55;
    vct_B = v113;
    vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    v216 = v111;
    x1 = v110;
    v234 = v109;
    v114 = &vf00.x;
    v115 = v114[4];
    v116 = v114[5];
    v117 = v114[6];
    sub_1949110(0);
    v119 = (f32)(sqrtf((f32)((f32)(v115 * v115) + (f32)(v116 * v116)) + (f32)(v117 * v117)) * hwk->apos2->per)
         * hwk->homingpara;
    v121 = v119 * 0.7;
    v121 = v119 * 0.7;
    vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v121);
    v122 = *(sdfVector4_t *)&startpos_4.klass;
    vct_B = v122;
    vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    v123 = &vf00.x;
    v124 = v123[6];
    x2 = v123[4];
    v222 = v123[5];
    v125 = &vf00.x;
    v125[6] = v245;
    v125[7] = v30;
    v125[4] = startpos;
    v125[5] = x0;
    v126 = &vf00.x;
    v126[8] = v53;
    v126[9] = v54;
    v126[10] = v56;
    v126[11] = v55;
    vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    v223 = v124;
    v127 = &vf00.x;
    v128 = v127[4];
    v129 = v127[5];
    v130 = v127[6];
    v132 = sqrtf((f32)((f32)(v128 * v128) + (f32)(v129 * v129)) + (f32)(v130 * v130));
    sub_1949110(0);
    homingpara = hwk->homingpara;
    v135 = v132 * homingpara;
    v67 = v216;
    vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v135);
    v136 = &vf00.x;
    v136[8] = v53;
    v136[9] = v54;
    v136[10] = v56;
    v136[11] = v55;
    v20 = v243;
    v19 = v244;
    v70 = 1.0;
    v71 = startpos;
    vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    v137 = &vf00.x;
    v65 = v137[4];
    y = v137[5];
    x3 = v137[6];
    kasokudo = hwk->kasokudo;
    if (kasokudo >= 0.1)
      goto LABEL_237;
    goto LABEL_233;
  }
  if (!path->path_pBasic)
  {
    v19 = 0;
    v73 = 1.0;
    v20 = 0x3F80000000000000LL;
    Bezier = 0.0;
    v75 = 0.0;
    v76 = 0.0;
    goto LABEL_301;
  }
  v11 = sbtldb_timecnt + 1;
  sbtldb_timecnt = v11;
  if (v11 >= hwk->lifetime)
    v12 = 1.0;
  else
    v12 = path->nef_pathtime;
  path->nef_pathtime = v12 + path->nef_addpathtime;
  path_hModel = path->path_hModel;
  if (mdlChkMotionEnd(path_hModel))
    goto LABEL_96;
  if (path->nef_pathtime >= 1.0)
    goto LABEL_96;
  v79 = path->path_hModel;
  mdlSetMotionSpeed(v79, 1.0);
  sdfModelGetMarkPos(path->path_hModel->modelRoot, 0);
  v204.n64_u64[0] = *(u64 *)&hwk->x;
  v205.n64_u64[0] = v203[2].n64_u64[0];
  v207 = v203[3].n64_f32[0];
  v206 = v203[3].n64_u32[1];
  v209 = hwk->z;
  v208 = hwk->dir;
  v262.w = 1.0;
  v262.x = 0.0;
  v262.y = 0.0;
  v262.z = 0.0;
  sBtlGetRotateDeg(v262, v208);
  v19 = *(u64 *)&vct_A.x;
  v20 = *(u64 *)&vct_A.z;
  ToMatrix();
  v212.n64_u64[0] = vadd_f32(v205, v204).n64_u64[0];
  v213 = v207 + v209;
  v214[2].n64_u64[0] = v212.n64_u64[0];
  v214[3].n64_f32[0] = v213;
  v214[3].n64_u32[1] = v206;
LABEL_296:
  goto LABEL_298;
LABEL_96:
  v81 = path->path_hModel;
  path_motionno = path->path_motionno;
  mdlSmoothSingleMotion(v81, 0, path_motionno, 0.0, 0.0, 0.0);
  path->nef_timecnt = 0.0;
  path->nef_pathtime = 0.0;
  sbtldb_timecnt = 0;
  sbattleResetEPLData(sbtldbwk->nef_pagecsr->point);
  mdlSetMotionSpeed(path->path_hModel, 1.0);
  sdfModelGetMarkPos(path->path_hModel->modelRoot, 0);
  v166.n64_u64[0] = *(u64 *)&hwk->x;
  v167 = hwk->z;
  v169 = v165[3].n64_f32[0];
  v168 = v165[3].n64_u32[1];
  v170.n64_u64[0] = v165[2].n64_u64[0];
  vct_A = (struct sdfVector4_t)xmmword_3CFD5C0;
  v19 = *(u64 *)&vct_A.x;
  v20 = *(u64 *)&vct_A.z;
  ToMatrix();
  v172.n64_u64[0] = vadd_f32(v170, v166).n64_u64[0];
  v173 = v169 + v167;
  v174[2].n64_u64[0] = v172.n64_u64[0];
  v174[3].n64_f32[0] = v173;
  v174[3].n64_u32[1] = v168;
  goto LABEL_296;
LABEL_298:
  get_transpose(&startpos_4.apos2, &mtx_A, 0);
  v261 = vct_A;
  *(_OWORD *)&startpos_4.x = *(_OWORD *)&startpos_4.apos2;
  *(_OWORD *)&startpos_4.area_r = *(_OWORD *)&startpos_4.motionno;
  *(_OWORD *)&startpos_4.z = v251;
  *(_OWORD *)&startpos_4.start = v252;
  v256 = op_Multiply_60923920(&startpos_4.x, v261, 0);
  vct_A = v256;
  v176 = &vf00.x;
  Bezier = v176[4];
  v75 = v176[5];
  v76 = v176[6];
  v73 = v176[7];
LABEL_301:
  v178 = &vf00.x;
  v178[4] = Bezier;
  v178[5] = v75;
  v178[6] = v76;
  v178[7] = v73;
  *(u64 *)&vct_A.x = v19;
  *(u64 *)&vct_A.z = v20;
  return;
}

// 0x1933d10
void sBtlDebug_EffHitDraw(SBDEBUG_CSRWORK *wk, SBTLSKILLHIT_TBL *hwk, SBDEBUG_PATHDATA *path, const sdfVector4_t *center) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  f32 *p_x;
  f32 *v14;
  s32 type;
  f32 v16;
  f32 v17;
  f32 v18;
  f32 v19;
  f32 v20;
  f32 *v22;
  f32 v23;
  f32 v24;
  f32 v25;
  f32 v26;
  f32 dir;
  f32 v31;
  _OWORD *v34;
  __int128 v35;
  __int128 v36;
  f32 *v39;
  f32 rad;
  f32 area_r1;
  f32 area_r2;
  _OWORD *v45;
  __int128 v46;
  __int128 v47;
  f32 xrad;
  f32 v51;
  _OWORD *v53;
  __int128 v54;
  __int128 v55;
  sdfMatrix4_t *v56;
  _OWORD *v58;
  __int128 v59;
  __int128 v60;
  f32 v63;
  f32 v64;
  _OWORD *v66;
  __int128 v67;
  __int128 v68;
  s32 v70;
  f32 height;
  f32 v73;
  f32 *v74;
  f32 v77;
  f32 v78;
  f32 centera;
  _OWORD v80[4];
  sdfMatrix4_t v81;
  sdfVector4_t v82;
  __int128 v83;
  __int128 v84;
  __int128 v85;
  sdfVector4_t v86;
  __int128 v87;
  __int128 v88;
  __int128 v89;
  sdfMatrix4_t v90;
  sdfMatrix4_t v91;
  sdfMatrix4_t v92;
  sdfMatrix4_t v93;
  sdfVector4_t v94;
  sdfVector4_t v95;
  sdfVector4_t v96;
  sdfVector4_t v97;
  sdfVector4_t v98;
  sdfVector4_t v99;
  sdfVector4_t v100;
  sdfVector4_t v101;
  sdfVector4_t v103;

  w = center->w;
  z = center->z;
  y = center->y;
  x = center->x;
  p_x = &vf00.x;
  p_x[4] = x;
  p_x[5] = y;
  p_x[6] = z;
  p_x[7] = w;
  v14 = &vf00.x;
  type = hwk->type;
  v17 = v14[4];
  v16 = v14[5];
  v19 = v14[6];
  v18 = v14[7];
  if (type != 2)
    goto LABEL_8;
  if ((hwk->flg & 0x1000) == 0)
  {
    dir = hwk->dir;
    v96.w = 1.0;
    v96.x = 0.0;
    v96.y = 0.0;
    v96.z = 0.0;
    sBtlGetRotateDeg(v96, dir);
LABEL_65:
    vct_B = vct_A;
    xrad = hwk->cy->xrad;
    v51 = xrad * 0.017453292;
    sub_1949540(0, xrad * 0.017453292);
    v53 = &vf00.x;
    v54 = v53[5];
    v86 = (sdfVector4_t)v53[4];
    v87 = v54;
    v55 = v53[7];
    v88 = v53[6];
    v89 = v55;
    v56 = v80;
    v80[0] = v86;
    v80[1] = v87;
    v80[2] = v88;
    v80[3] = v89;
LABEL_96:
    sBtlGetQuatFromMatrix(v56);
    Mult();
    ToMatrix();
    v70 = (u8)byte_5756085;
    vct_A = (struct sdfVector4_t)xmmword_3CFEDD0;
    if (v70)
    {
      goto LABEL_102;
    }
    else
    {
      goto LABEL_102;
    }
LABEL_102:
    get_transpose(&v93, &mtx_A, 0);
    v92 = v93;
    v94 = op_Multiply_60923920(&v92, vct_A, 0);
    vct_A = v94;
    height = hwk->cy->height;
    v73 = height * 0.5;
    vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v73);
    v74 = &vf00.x;
    v74[8] = v17;
    v74[9] = v16;
    v74[10] = v19;
    v74[11] = v18;
    vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    return;
  }
  sdfModelGetMarkPosMatrix(path->path_hEveUnit->Model->modelRoot, 0);
  v45 = &vf00.x;
  v46 = v45[5];
  *(_OWORD *)&v93.m00 = v45[4];
  *(_OWORD *)&v93.m01 = v46;
  v47 = v45[7];
  *(_OWORD *)&v93.m02 = v45[6];
  *(_OWORD *)&v93.m03 = v47;
  v81 = v93;
  sBtlGetQuatFromMatrix(&v81);
  v100.w = 1.0;
  v100.y = 0.0;
  v100.z = 0.0;
  vct_B = vct_A;
  v100.x = 0.0;
  sBtlGetRotateDeg(v100, hwk->dir);
  Mult();
  goto LABEL_65;
LABEL_8:
  if (type == 1)
  {
    if ((hwk->flg & 0x1000) == 0)
    {
      v31 = hwk->dir;
      v97.w = 1.0;
      v97.x = 0.0;
      v97.y = 0.0;
      v97.z = 0.0;
      sBtlGetRotateDeg(v97, v31);
LABEL_88:
      vct_B = vct_A;
      v63 = hwk->cy->xrad;
      v64 = v63 * 0.017453292;
      sub_1949540(0, v63 * 0.017453292);
      v66 = &vf00.x;
      v67 = v66[5];
      v86 = (sdfVector4_t)v66[4];
      v87 = v67;
      v68 = v66[7];
      v88 = v66[6];
      v89 = v68;
      v56 = &v82;
      v82 = v86;
      v83 = v87;
      v84 = v88;
      v85 = v89;
      goto LABEL_96;
    }
    sdfModelGetMarkPosMatrix(path->path_hEveUnit->Model->modelRoot, 0);
    v58 = &vf00.x;
    v59 = v58[5];
    *(_OWORD *)&v93.m00 = v58[4];
    *(_OWORD *)&v93.m01 = v59;
    v60 = v58[7];
    *(_OWORD *)&v93.m02 = v58[6];
    *(_OWORD *)&v93.m03 = v60;
    v90 = v93;
    sBtlGetQuatFromMatrix(&v90);
    v101.w = 1.0;
    v101.y = 0.0;
    v101.z = 0.0;
    vct_B = vct_A;
    v101.x = 0.0;
    sBtlGetRotateDeg(v101, hwk->dir);
    Mult();
    goto LABEL_88;
  }
  if (type)
    return;
  v78 = v19;
  centera = v18;
  v77 = v17;
  if ((hwk->flg & 0x1000) != 0)
  {
    sdfModelGetMarkPosMatrix(path->path_hEveUnit->Model->modelRoot, 0);
    v34 = &vf00.x;
    v35 = v34[5];
    *(_OWORD *)&v93.m00 = v34[4];
    *(_OWORD *)&v93.m01 = v35;
    v36 = v34[7];
    *(_OWORD *)&v93.m02 = v34[6];
    *(_OWORD *)&v93.m03 = v36;
    v91 = v93;
    sBtlGetQuatFromMatrix(&v91);
    v98.w = 1.0;
    v98.y = 0.0;
    v98.z = 0.0;
    vct_B = vct_A;
    v98.x = 0.0;
    sBtlGetRotateDeg(v98, hwk->dir);
    v39 = &vf00.x;
    v23 = v39[4];
    v24 = v39[5];
    v25 = v39[6];
    v26 = v39[7];
    Mult();
    goto LABEL_47;
  }
  v20 = hwk->dir;
  v95.w = 1.0;
  v95.x = 0.0;
  v95.y = 0.0;
  v95.z = 0.0;
  sBtlGetRotateDeg(v95, v20);
  v22 = &vf00.x;
  v23 = v22[4];
  v24 = v22[5];
  v25 = v22[6];
  v26 = v22[7];
LABEL_47:
  area_r1 = hwk->area_r;
  rad = hwk->rad;
  area_r2 = hwk->cy->height;
  v99.x = v77;
  v99.z = v78;
  v99.y = v16;
  v99.w = centera;
  v103.x = v23;
  v103.y = v24;
  v103.z = v25;
  v103.w = v26;
  sBtlDebug_DrawHitCircle(v99, v103, rad, area_r1, area_r2);
}

// 0x1938c20
void sBtlDebug_MDLHitDraw(SBDEBUG_CSRWORK *wk, SBTLSKILLHIT_TBL *hwk, const sdfVector4_t *center) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  f32 *p_x;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 acterID;
  SBTLUNIT_WORK *v17;
  u32 v18;
  SBTLDMG_HITWORK *v20;
  s64 v21;
  void *v22;
  SBTLSKILLHIT_POSWORK *start;
  SBTLSKILLHIT_POSWORK *v26;
  float32x2_t v27;
  f32 v28;
  float32x2_t v31;
  f32 v32;
  float32x2_t *v33;
  float32x2_t *v35;
  s64 v36;
  f32 v38;
  SBTLDEBUG_WORK *v39;
  SBTLSKILLHIT_POSWORK *v40;
  u32 iti;
  s32 type;
  f32 area_r2;
  f32 v48;
  f32 v49;
  f32 v50;
  f32 v51;
  f32 v52;
  f32 rad;
  f32 area_r1;
  f32 xrad;
  f32 v57;
  _OWORD *v59;
  __int128 v60;
  __int128 v61;
  sdfMatrix4_t *v62;
  f32 v64;
  f32 v65;
  _OWORD *v67;
  __int128 v68;
  __int128 v69;
  s32 v71;
  f32 height;
  f32 v74;
  sdfVector4_t v75;
  f32 v76;
  SBTLUNIT_WORK *wka;
  SBTLUNIT_WORK *wkb[2];
  f32 wkc;
  f32 centerc;
  struct sdfVector4_t centera;
  struct sdfVector4_t centerb;
  _OWORD v86[4];
  sdfVector4_t v87;
  __int128 v88;
  __int128 v89;
  __int128 v90;
  sdfVector4_t v91;
  __int128 v92;
  __int128 v93;
  __int128 v94;
  sdfVector4_t rott;
  sdfVector4_t rot;
  sdfVector4_t pos;
  sdfMatrix4_t v98;
  sdfMatrix4_t v99;
  sdfVector4_t v100;
  sdfVector4_t v101;
  sdfVector4_t v103;
  sdfVector4_t v104;
  sdfVector4_t v105;

  w = center->w;
  z = center->z;
  y = center->y;
  x = center->x;
  *(u64 *)&rott.x = 0;
  *(u64 *)&rott.z = 0;
  *(u64 *)&pos.x = 0;
  *(u64 *)&pos.z = 0;
  *(u64 *)&rot.x = 0;
  *(u64 *)&rot.z = 0;
  goto LABEL_3;
  if (v18)
  {
LABEL_3:
    goto LABEL_4;
  }
LABEL_4:
  p_x = &vf00.x;
  p_x[4] = x;
  p_x[5] = y;
  p_x[6] = z;
  p_x[7] = w;
  UnitMng = wk->UnitMng;
  acterID = sbtldbwk->acterID;
  v17 = sBtlSearchUnit_ID(UnitMng, acterID);
  if (v17)
  {
    wka = v17;
    v20 = Allocate(SBTLDMG_HITWORK);
    _ctor(v20, 0);
    v21 = 0;
    v20->dir = hwk->dir;
    *(u64 *)&v20->x = *(u64 *)&hwk->x;
    v20->z = hwk->z;
    v20->flg = hwk->flg;
    while (1)
    {
      if (v21 >= sbtldbwk->nef_nowpage)
        break;
      start = sbtldbwk->ef_wk[v21]->wk->start;
      v22 = NewSpecific(byte, 0x12u);
      InitializeArray_55364416(v22, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__E2170EDFF82D1B234EAC7F7E28AF54B98E969BFA23206AF39C3328FB55FAE35F, 0);
      ++v21;
      start->iti = *((u8 *)&v22[2].klass + start->iti);
    }
    *(u64 *)&rott.x = 0;
    *(u64 *)&rott.z = 0;
    v26 = hwk->start;
    sBtlSetHitPos(wka, v20, 0, v26, &pos, &rot, &rott, 0);
    v27.n64_u64[0] = *(u64 *)&v20->x;
    v28 = v20->z;
    *(sdfVector4_t *)wkb = wka->rot;
    vct_A = *(sdfVector4_t *)wkb;
    ToMatrix();
    v31.n64_u64[0] = vadd_f32(v27, 0).n64_u64[0];
    v32 = v28 + 0.0;
    v33[2].n64_u64[0] = v31.n64_u64[0];
    v33[3].n64_f32[0] = v32;
    v33[3].n64_u32[1] = 1065353216;
    get_transpose(&v99, &mtx_A, 0);
    v98 = v99;
    v100 = op_Multiply_60923920(&v98, vct_A, 0);
    vct_A = v100;
    v36 = 0;
    v38 = v35[3].n64_f32[0];
    *(float32x2_t *)&pos.x = vadd_f32(v35[2], *(float32x2_t *)&pos.x);
    pos.z = v38 + pos.z;
    while (1)
    {
      v39 = sbtldbwk;
      if (v36 >= v39->nef_nowpage)
        break;
      v39 = sbtldbwk;
      v40 = v39->ef_wk[v36]->wk->start;
      iti = v40->iti;
      if (iti >= 9 && iti - 128 <= 8)
        v40->iti = iti - 119;
      ++v36;
    }
  }
  type = hwk->type;
  if (type == 2)
  {
    centera = rot;
    vct_A = centera;
    vct_B = vct_A;
    xrad = hwk->cy->xrad;
    v57 = xrad * 0.017453292;
    sub_1949540(0, xrad * 0.017453292);
    v59 = &vf00.x;
    v60 = v59[5];
    v91 = (sdfVector4_t)v59[4];
    v92 = v60;
    v61 = v59[7];
    v93 = v59[6];
    v94 = v61;
    v62 = v86;
    v86[0] = v91;
    v86[1] = v92;
    v86[2] = v93;
    v86[3] = v94;
LABEL_81:
    sBtlGetQuatFromMatrix(v62);
    Mult();
    ToMatrix();
    v71 = (u8)byte_5756085;
    vct_A = (struct sdfVector4_t)xmmword_3CFEDD0;
    if (v71)
    {
      goto LABEL_87;
    }
    else
    {
      goto LABEL_87;
    }
LABEL_87:
    get_transpose(&v99, &mtx_A, 0);
    v104 = vct_A;
    v98 = v99;
    v101 = op_Multiply_60923920(&v98, v104, 0);
    vct_A = v101;
    height = hwk->cy->height;
    v74 = height * 0.5;
    vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v74);
    v75 = pos;
    vct_B = v75;
    vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    return;
  }
  if (type == 1)
  {
    centerb = rot;
    vct_A = centerb;
    vct_B = vct_A;
    v64 = hwk->cy->xrad;
    v65 = v64 * 0.017453292;
    sub_1949540(0, v64 * 0.017453292);
    v67 = &vf00.x;
    v68 = v67[5];
    v91 = (sdfVector4_t)v67[4];
    v92 = v68;
    v69 = v67[7];
    v93 = v67[6];
    v94 = v69;
    v62 = &v87;
    v87 = v91;
    v88 = v92;
    v89 = v93;
    v90 = v94;
    goto LABEL_81;
  }
  if (!hwk->type)
  {
    area_r2 = hwk->cy->height;
    v103.x = pos.x;
    v103.y = pos.y;
    v103.z = pos.z;
    v48 = pos.w;
    v49 = rot.x;
    v50 = rot.y;
    v51 = rot.z;
    v52 = rot.w;
    area_r1 = hwk->area_r;
    rad = hwk->rad;
    centerc = pos.x;
    v76 = pos.z;
    wkc = pos.y;
    v103.z = v76;
    v103.y = wkc;
    v103.x = centerc;
    v103.w = v48;
    v105.x = v49;
    v105.y = v50;
    v105.z = v51;
    v105.w = v52;
    sBtlDebug_DrawHitCircle(v103, v105, rad, area_r1, area_r2);
  }
}

// 0x19398e0
void sBtlDebug_EffHitPathDraw(SBDEBUG_CSRWORK *wk, SBTLSKILLHIT_TBL *hwk) {
  u32 v4;
  float32x2_t v5;
  f32 dir;
  f32 z;
  float32x2_t v10;
  f32 v11;
  float32x2_t *static_fields;
  f32 *p_x;
  f32 v15;
  f32 shatei;
  f32 *v20;
  f32 x;
  s64 v23;
  f32 *v25;
  sdfVector4_t *v26;
  f32 v28;
  f32 *v30;
  f32 *v31;
  f32 v32;
  f32 v33;
  f32 v34;
  f32 v35;
  f32 v36;
  f32 v37;
  f32 *v39;
  f32 *v40;
  f32 Bezier;
  f32 y;
  f32 v43;
  f32 *v44;
  f32 *v45;
  struct sdfVector4_t v46;
  f32 v47;
  f32 v48;
  f32 v49;
  f32 *v50;
  struct sdfVector4_t v51;
  f32 *v52;
  f32 v58;
  f32 v59;
  f32 *v61;
  struct sdfVector4_t v62;
  f32 *v63;
  f32 v64;
  f32 v65;
  f32 v66;
  f32 v68;
  f32 v70;
  struct sdfVector4_t v71;
  f32 *v72;
  f32 *v73;
  struct sdfVector4_t v74;
  f32 *v75;
  f32 v76;
  f32 v77;
  f32 v78;
  f32 v80;
  f32 v82;
  struct sdfVector4_t v83;
  f32 *v84;
  f32 *v85;
  f32 *v86;
  f32 *v87;
  f32 v88;
  f32 v89;
  f32 v90;
  f32 v92;
  f32 homingpara;
  f32 v94;
  f32 *v95;
  f32 *v96;
  f32 sokudo;
  f32 v98;
  __int128 v99;
  s32 i;
  f32 kasokudo;
  f32 *v103;
  f32 *v106;
  f32 v114;
  f32 v116;
  f32 v117;
  f32 v118;
  f32 x2;
  f32 v127;
  f32 v128;
  f32 x1;
  f32 startpos;
  f32 v138;
  f32 x0;
  f32 v140;
  struct sdfVector4_t v145;
  f32 w;
  SBTLSKILLHIT_TBL hittbl;
  __int128 v148;
  __int128 v149;
  sdfVector4_t v150;
  sdfVector4_t v151;
  sdfVector4_t v152;
  sdfVector4_t v153;
  sdfVector4_t v155;
  sdfVector4_t v156;
  sdfVector4_t v157;
  sdfVector4_t v158;

  v4 = hwk->flg & 0x1100;
  memset(&hittbl, 0, 32);
  if (v4 != 256)
    return;
  v5.n64_u64[0] = *(u64 *)&hwk->x;
  z = hwk->z;
  dir = hwk->dir;
  v153.w = 1.0;
  v153.x = 0.0;
  v153.y = 0.0;
  v153.z = 0.0;
  sBtlGetRotateDeg(v153, dir);
  ToMatrix();
  v10.n64_u64[0] = vadd_f32(v5, 0).n64_u64[0];
  v11 = z + 0.0;
  static_fields[2].n64_u64[0] = v10.n64_u64[0];
  static_fields[3].n64_f32[0] = v11;
  static_fields[3].n64_u32[1] = 1065353216;
  get_transpose(&hittbl.apos2, &mtx_A, 0);
  *(_OWORD *)&hittbl.x = *(_OWORD *)&hittbl.apos2;
  *(_OWORD *)&hittbl.area_r = *(_OWORD *)&hittbl.motionno;
  *(_OWORD *)&hittbl.z = v148;
  *(_OWORD *)&hittbl.start = v149;
  v151 = op_Multiply_60923920(&hittbl.x, vct_A, 0);
  vct_A = v151;
  p_x = &vf00.x;
  v155.w = 1.0;
  v155.z = 0.0;
  v138 = p_x[5];
  x0 = p_x[4];
  v155.y = 0.0;
  v15 = p_x[7];
  startpos = p_x[6];
  v155.x = 0.0;
  sBtlGetRotateDeg(v155, hwk->dir);
  ToMatrix();
  vct_A = (struct sdfVector4_t)xmmword_3CFBEC0;
  get_transpose(&hittbl.apos2, &mtx_A, 0);
  v156 = vct_A;
  *(_OWORD *)&hittbl.x = *(_OWORD *)&hittbl.apos2;
  *(_OWORD *)&hittbl.area_r = *(_OWORD *)&hittbl.motionno;
  *(_OWORD *)&hittbl.z = v148;
  *(_OWORD *)&hittbl.start = v149;
  v152 = op_Multiply_60923920(&hittbl.x, v156, 0);
  vct_A = v152;
  shatei = hwk->shatei;
  vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, shatei);
  v20 = &vf00.x;
  v20[8] = x0;
  v20[9] = v138;
  v20[10] = startpos;
  v20[11] = v15;
  vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  x = vct_A.x;
  v23 = *(u64 *)&vct_A.z;
  vct_A.x = x;
  vct_A.y = 0.0;
  *(u64 *)&vct_A.z = v23;
  v25 = &vf00.x;
  v25[8] = x0;
  v25[9] = v138;
  v25[10] = startpos;
  v25[11] = v15;
  vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  sub_1949110(0);
  v28 = hwk->shatei;
  vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v28);
  v30 = &vf00.x;
  v30[8] = x0;
  v30[9] = v138;
  v30[10] = startpos;
  v30[11] = v15;
  vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  v31 = &vf00.x;
  v32 = v31[4];
  v33 = v31[5];
  v34 = v31[6];
  v35 = v31[7];
  v157.w = v15;
  v158.x = v32;
  v157.z = startpos;
  v158.y = v33;
  v158.z = v34;
  v158.w = v35;
  *(u64 *)&v150.z = &hittbl.fields;
  *(u64 *)&v150.x = hwk;
  v157.y = v138;
  v157.x = x0;
  sBtlSetApos12(v157, v158, v150, &hittbl, 0, v26);
  v36 = v33;
  v37 = v35;
  v39 = &vf00.x;
  v39[4] = x0;
  v39[5] = v138;
  v39[6] = startpos;
  v39[7] = v15;
  v114 = v15;
  v40 = &vf00.x;
  Bezier = v40[4];
  y = v40[5];
  v43 = v40[6];
  w = v40[7];
  v44 = &vf00.x;
  v44[4] = v32;
  v44[5] = v36;
  v44[6] = v34;
  v44[7] = v37;
  v140 = v37;
  v116 = v34;
  v45 = &vf00.x;
  v46 = *(sdfVector4_t *)&hittbl.flg;
  v47 = v45[6];
  v48 = v45[4];
  v49 = v45[5];
  vct_A = v46;
  v50 = &vf00.x;
  v128 = v50[5];
  x1 = v50[4];
  v127 = v50[6];
  v51 = *(sdfVector4_t *)&hittbl.klass;
  vct_A = v51;
  if ((hwk->flg & 0x400) == 0)
  {
    v52 = &vf00.x;
    v118 = v52[5];
    x2 = v52[4];
    v117 = v52[6];
    if (hwk->lifetime < 1)
      return;
    goto LABEL_173;
  }
  v58 = v116;
  v59 = v36;
  v61 = &vf00.x;
  v61[4] = v32;
  v61[5] = v59;
  v61[6] = v58;
  v61[7] = v140;
  v62 = *(sdfVector4_t *)&hittbl.flg;
  vct_B = v62;
  vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  v63 = &vf00.x;
  v64 = v63[6];
  v65 = v63[4];
  v66 = v63[5];
  sub_1949110(0);
  v68 = (f32)(sqrtf((f32)((f32)(v65 * v65) + (f32)(v66 * v66)) + (f32)(v64 * v64)) * hwk->apos1->per)
      * hwk->homingpara;
  v70 = v68 * 0.5;
  vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v70);
  v71 = *(sdfVector4_t *)&hittbl.flg;
  vct_B = v71;
  vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  v72 = &vf00.x;
  v128 = v72[5];
  x1 = v72[4];
  v127 = v72[6];
  v73 = &vf00.x;
  v73[4] = v32;
  v73[5] = v36;
  v73[6] = v116;
  v73[7] = v140;
  v74 = *(sdfVector4_t *)&hittbl.klass;
  vct_B = v74;
  vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  v75 = &vf00.x;
  v76 = v75[4];
  v77 = v75[5];
  v78 = v75[6];
  sub_1949110(0);
  v80 = (f32)(sqrtf((f32)((f32)(v76 * v76) + (f32)(v77 * v77)) + (f32)(v78 * v78)) * hwk->apos2->per)
      * hwk->homingpara;
  v82 = v80 * 0.7;
  vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v82);
  v83 = *(sdfVector4_t *)&hittbl.klass;
  vct_B = v83;
  vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  v84 = &vf00.x;
  v118 = v84[5];
  x2 = v84[4];
  v117 = v84[6];
  v85 = &vf00.x;
  v85[4] = x0;
  v85[5] = v138;
  v85[6] = startpos;
  v85[7] = v114;
  v86 = &vf00.x;
  v86[8] = v32;
  v86[9] = v36;
  v86[10] = v116;
  v86[11] = v140;
  vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  v87 = &vf00.x;
  v88 = v87[4];
  v89 = v87[5];
  v90 = v87[6];
  v92 = sqrtf((f32)((f32)(v88 * v88) + (f32)(v89 * v89)) + (f32)(v90 * v90));
  sub_1949110(0);
  homingpara = hwk->homingpara;
  v94 = v92 * homingpara;
  vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v94);
  v95 = &vf00.x;
  v95[8] = v32;
  v95[9] = v36;
  v95[10] = v116;
  v95[11] = v140;
  vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  v96 = &vf00.x;
  v48 = v96[4];
  v49 = v96[5];
  v47 = v96[6];
  if (hwk->lifetime >= 1)
  {
LABEL_173:
    sokudo = hwk->sokudo;
    v98 = 0.0;
    v99 = xmmword_3CFD5C0;
    for (i = 0; i < hwk->lifetime; ++i)
    {
      v145 = (struct sdfVector4_t)v99;
      kasokudo = hwk->kasokudo;
      if (kasokudo <= 0.0)
      {
        if (kasokudo < 0.0)
        {
          sokudo = sokudo + kasokudo;
          if (sokudo < 0.0)
            sokudo = 0.0;
        }
      }
      else
      {
        sokudo = sokudo + kasokudo;
      }
      if ((f32)(v98 + (f32)(1.0 / (f32)(hwk->shatei / sokudo))) < 1.0)
        v98 = v98 + (f32)(1.0 / (f32)(hwk->shatei / sokudo));
      else
        v98 = 1.0;
      v103 = &vf00.x;
      v103[4] = Bezier;
      v103[5] = y;
      v103[6] = v43;
      v103[7] = w;
      vct_A = v145;
      Bezier = sBtlGetBezier(x0, x1, x2, v48, v98);
      y = sBtlGetBezier(v138, v128, v118, v49, v98);
      v43 = sBtlGetBezier(startpos, v127, v117, v47, v98);
      v106 = &vf00.x;
      v106[4] = Bezier;
      v106[5] = y;
      v106[6] = v43;
      v106[7] = w;
      v99 = vct_A;
    }
  }
}

// 0x193b0c0
void sBtlDebug_DrawTri2Side(const sdfVector4_t *pos0, const sdfVector4_t *pos1, const sdfVector4_t *pos2, s32 color) {
  ;
}

// 0x193b0d0
void sBtlDebug_DrawPoly2(const sdfVector4_t *pos0, const sdfVector4_t *pos1, const sdfVector4_t *pos2, const sdfVector4_t *pos3, s32 color) {
  ;
}

// 0x1934970
void sBtlDebug_DrawHitCircle(const sdfVector4_t *center, const sdfVector4_t *rot, f32 rad, f32 area_r1, f32 area_r2) {
  f32 v6;
  f32 v7;
  f32 v8;
  f32 v9;
  f32 *p_x;
  f32 v12;
  f32 v13;
  u32 *v14;
  f32 *v15;
  s32 v17;
  u32 *v20;
  u32 *v24;
  f32 v25;
  f32 v26;
  f32 v27;
  f32 v28;
  f32 v29;
  f32 v30;
  f32 v31;
  f32 v32;
  f32 v33;
  f32 v34;
  f32 v35;
  f32 v36;
  f32 *v39;
  f32 v41;
  f32 v42;
  f32 v44;
  u32 *v46;
  u32 *v49;
  f32 v50;
  f32 v51;
  f32 v52;
  f32 v53;
  f32 v54;
  f32 v55;
  f32 v56;
  f32 v57;
  f32 v58;
  f32 v59;
  f32 v60;
  f32 v61;
  f32 *v64;
  f32 v66;
  f32 v67;
  f32 v69;
  f32 v70;
  u32 *v72;
  u32 *v75;
  f32 v76;
  f32 v77;
  f32 v78;
  f32 v79;
  f32 v80;
  f32 v81;
  f32 v82;
  f32 v83;
  f32 v84;
  f32 v85;
  f32 v86;
  f32 *v89;
  f32 v91;
  f32 v92;
  f32 v94;
  u32 *v96;
  u32 *v99;
  f32 v100;
  f32 v101;
  f32 v102;
  f32 v103;
  f32 v104;
  f32 v105;
  f32 v106;
  f32 v107;
  f32 v108;
  f32 v109;
  f32 v110;
  f32 *v113;
  f32 v115;
  f32 v116;
  f32 v118;
  u32 *v120;
  f32 v122;
  f32 v123;
  float32x4_t v126;
  u32 *v127;
  s32 v128;
  s32 v129;
  u32 *v130;
  f32 v131;
  f32 v132;
  f32 v134;
  f32 v135;
  f32 v136;
  f32 v137;
  f32 v138;
  f32 v139;
  f32 v140;
  f32 v141;
  f32 v142;
  f32 v143;
  f32 v144;
  f32 v145;
  u32 *v146;
  f32 v147;
  s64 v149;
  u32 *v150;
  sdfVector4_t *v151;
  f32 v153;
  f32 v154;
  f32 v155;
  f32 v156;
  f32 v157;
  f32 v158;
  f32 v159;
  f32 v160;
  f32 v161;
  f32 v162;
  f32 v163;
  f32 *v166;
  f32 v168;
  f32 v169;
  f32 v171;
  f32 v172;
  f32 v173;
  u32 *v175;
  f32 v176;
  f32 v177;
  f32 *v178;
  f32 v180;
  f32 v181;
  f32 v183;
  u32 *v185;
  f32 v186;
  f32 v187;
  f32 v188;
  f32 v189;
  f32 v190;
  f32 v191;
  f32 v192;
  f32 v193;
  f32 *v194;
  f32 v196;
  f32 v197;
  f32 v199;
  u32 *v201;
  float32x4_t v202;
  f32 *v203;
  f32 v204;
  f32 v205;
  f32 v206;
  f32 v207;
  f32 *v208;
  f32 v209;
  s64 v210;
  sdfVector4_t *v211;
  f32 v213;
  f32 v214;
  f32 v215;
  f32 v216;
  f32 v217;
  f32 v218;
  f32 v219;
  f32 v220;
  f32 v221;
  f32 v222;
  f32 v223;
  f32 v224;
  f32 v225;
  f32 v226;
  f32 *v227;
  s32 v230;
  s32 v231;
  s32 v232;
  s32 v233;
  struct sdfVector4_t v234;
  struct sdfVector4_t v235;
  struct sdfVector4_t v236;
  struct sdfVector4_t v237;
  struct sdfVector4_t v238;
  struct sdfVector4_t v239;
  struct sdfVector4_t v240;
  s32 v241;
  f32 v242;
  _OWORD *v243;
  f32 z;
  f32 w;
  f32 v246;
  f32 v247;
  s32 v248;
  s32 v249;
  s32 v250;
  s32 v251;
  f32 x;
  f32 y;
  struct sdfVector4_t v254;
  s32 v255;
  struct sdfVector4_t v256;
  struct sdfVector4_t v257;
  struct sdfVector4_t v258;
  struct sdfVector4_t v259;
  struct sdfVector4_t v260;
  struct sdfVector4_t v261;
  struct sdfVector4_t v262;
  struct sdfVector4_t v263;
  struct sdfVector4_t v264;
  struct sdfVector4_t v265;
  struct sdfVector4_t v266;
  _OWORD *v267;
  sdfMatrix4_t v268;
  sdfMatrix4_t v269;
  sdfVector4_t v270;
  sdfVector4_t v271;
  sdfVector4_t v272;
  sdfVector4_t v273;
  sdfVector4_t v274;
  sdfVector4_t v275;
  sdfVector4_t v276;
  sdfVector4_t v277;
  sdfVector4_t v279;
  sdfVector4_t v280;
  sdfVector4_t v281;
  sdfVector4_t v282;
  sdfVector4_t v283;
  sdfVector4_t v284;
  sdfVector4_t v285;

  z = rot->z;
  w = rot->w;
  x = rot->x;
  y = rot->y;
  v6 = center->w;
  v7 = center->z;
  v8 = center->y;
  v9 = center->x;
  v267 = NewSpecific(sdfVector4_t, 0x14u);
  v243 = NewSpecific(sdfVector4_t, 0x14u);
  p_x = &vf00.x;
  p_x[4] = v9;
  p_x[5] = v8;
  p_x[6] = v7;
  p_x[7] = v6;
  v13 = z;
  v12 = w;
  v14 = &vf00.x;
  v250 = v14[5];
  v251 = v14[4];
  v248 = v14[7];
  v249 = v14[6];
  v15 = &vf00.x;
  v15[6] = v13;
  v15[7] = v12;
  v15[4] = x;
  v15[5] = y;
  ToMatrix();
  v17 = (u8)byte_5756085;
  vct_A = (struct sdfVector4_t)xmmword_3CFBEC0;
  if (v17)
  {
    goto LABEL_14;
  }
  else
  {
    goto LABEL_14;
  }
LABEL_14:
  get_transpose(&v269, &mtx_A, 0);
  v268 = v269;
  v270 = op_Multiply_60923920(&v268, vct_A, 0);
  vct_A = v270;
  v247 = area_r1;
  vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, v247);
  v20 = &vf00.x;
  v20[8] = v251;
  v20[9] = v250;
  v20[10] = v249;
  v20[11] = v248;
  vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  v24 = &vf00.x;
  v232 = v24[5];
  v233 = v24[4];
  v230 = v24[7];
  v231 = v24[6];
  v25 = sub_188E3F0(rad);
  v26 = 0.0;
  do
  {
    v26 = v26 + 0.15707964;
    if (v26 > v25)
      v27 = v25;
    else
      v27 = v26;
    v28 = (s32)(v27 * 0.15915494);
    if ((f32)(v27 * 0.15915494) == INFINITY)
      v28 = -2147500000.0;
    v29 = (f32)(v27 * 0.15915494) - v28;
    v30 = v29 + 1.0;
    if (v29 >= -0.5)
      v30 = v29;
    if (v29 > 0.5)
      v31 = v29 + -1.0;
    else
      v31 = v30;
    v32 = -0.5 - v31;
    if (v31 >= -0.25)
      v32 = v31;
    if (v31 > 0.25)
      v33 = 0.5 - v31;
    else
      v33 = v32;
    v34 = (f32)(v27 + 1.5708) * 0.15915494;
    v35 = (s32)v34;
    if (v34 == INFINITY)
      v35 = -2147500000.0;
    v36 = v34 - v35;
    if ((f32)(v34 - v35) <= 0.5)
    {
      if (v36 < -0.5)
        v36 = v36 + 1.0;
    }
    else
    {
      v36 = v36 + -1.0;
    }
    if (v36 <= 0.25)
    {
      if (v36 < -0.25)
      {
        v36 = -0.5 - v36;
LABEL_80:
        goto LABEL_81;
      }
      else
      {
        goto LABEL_80;
      }
    }
    else
    {
      v36 = 0.5 - v36;
      goto LABEL_80;
    }
LABEL_81:
    v39 = &vf00.x;
    v39[6] = v13;
    v39[7] = v12;
    v39[4] = x;
    v39[5] = y;
    ToMatrix();
    v41 = v33 * 4.0;
    v42 = v36 * 4.0;
    vct_A.y = 0.0;
    vct_A.w = 1.0;
    v44 = v41 * v41;
    vct_A.x = -(f32)((f32)((f32)((f32)((f32)((f32)((f32)(v33 * 4.0) * 1.5708) + (f32)((f32)(v41 * (f32)(v41 * v41)) * -0.6459637)) + (f32)((f32)((f32)(v41 * v41) * (f32)(v41 * (f32)(v41 * v41))) * 0.07968968)) + (f32)((f32)(v44 * (f32)(v44 * (f32)(v41 * (f32)(v41 * v41)))) * -0.0046737655)) + (f32)((f32)(v44 * (f32)(v44 * (f32)(v44 * (f32)(v41 * (f32)(v41 * v41))))) * 0.00015148419)) * v247);
    vct_A.z = -(f32)((f32)((f32)((f32)((f32)((f32)((f32)(v36 * 4.0) * 1.5708) + (f32)((f32)(v42 * (f32)(v42 * v42)) * -0.6459637)) + (f32)((f32)((f32)(v42 * v42) * (f32)(v42 * (f32)(v42 * v42))) * 0.07968968)) + (f32)((f32)((f32)(v42 * v42) * (f32)((f32)(v42 * v42) * (f32)(v42 * (f32)(v42 * v42)))) * -0.0046737655)) + (f32)((f32)((f32)(v42 * v42) * (f32)((f32)(v42 * v42) * (f32)((f32)(v42 * v42) * (f32)(v42 * (f32)(v42 * v42))))) * 0.00015148419)) * v247);
    get_transpose(&v269, &mtx_A, 0);
    v279 = vct_A;
    v268 = v269;
    v271 = op_Multiply_60923920(&v268, v279, 0);
    vct_A = v271;
    v46 = &vf00.x;
    v46[8] = v251;
    v46[9] = v250;
    v46[10] = v249;
    v46[11] = v248;
    vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    v259 = vct_A;
    vct_A = v259;
    continue;
  }
  while (v26 <= v25);
  goto LABEL_119;
LABEL_120:
  v254 = vct_A;
  goto LABEL_121;
LABEL_119:
  goto LABEL_120;
LABEL_121:
  v49 = &vf00.x;
  v49[4] = v233;
  v49[5] = v232;
  v49[6] = v231;
  v49[7] = v230;
  v50 = -v25;
  v51 = 0.0;
  v246 = v25;
  while (2)
  {
    v51 = v51 + -0.15707964;
    if (v51 < v50)
      v52 = v50;
    else
      v52 = v51;
    v53 = (s32)(v52 * 0.15915494);
    if ((f32)(v52 * 0.15915494) == INFINITY)
      v53 = -2147500000.0;
    v54 = (f32)(v52 * 0.15915494) - v53;
    v55 = v54 + 1.0;
    if (v54 >= -0.5)
      v55 = v54;
    if (v54 > 0.5)
      v56 = v54 + -1.0;
    else
      v56 = v55;
    v57 = -0.5 - v56;
    if (v56 >= -0.25)
      v57 = v56;
    if (v56 > 0.25)
      v58 = 0.5 - v56;
    else
      v58 = v57;
    v59 = (f32)(v52 + 1.5708) * 0.15915494;
    v60 = (s32)v59;
    if (v59 == INFINITY)
      v60 = -2147500000.0;
    v61 = v59 - v60;
    if ((f32)(v59 - v60) <= 0.5)
    {
      if (v61 < -0.5)
        v61 = v61 + 1.0;
    }
    else
    {
      v61 = v61 + -1.0;
    }
    if (v61 <= 0.25)
    {
      if (v61 < -0.25)
      {
        v61 = -0.5 - v61;
      }
      else
      {
      }
LABEL_152:
      goto LABEL_154;
    }
    v61 = 0.5 - v61;
    goto LABEL_152;
LABEL_154:
    v64 = &vf00.x;
    v64[6] = v13;
    v64[7] = v12;
    v64[4] = x;
    v64[5] = y;
    ToMatrix();
    v66 = v58 * 4.0;
    v67 = v61 * 4.0;
    vct_A.y = 0.0;
    vct_A.w = 1.0;
    v69 = v66 * v66;
    vct_A.x = -(f32)((f32)((f32)((f32)((f32)((f32)((f32)(v58 * 4.0) * 1.5708) + (f32)((f32)(v66 * (f32)(v66 * v66)) * -0.6459637)) + (f32)((f32)((f32)(v66 * v66) * (f32)(v66 * (f32)(v66 * v66))) * 0.07968968)) + (f32)((f32)(v69 * (f32)(v69 * (f32)(v66 * (f32)(v66 * v66)))) * -0.0046737655)) + (f32)((f32)(v69 * (f32)(v69 * (f32)(v69 * (f32)(v66 * (f32)(v66 * v66))))) * 0.00015148419)) * v247);
    vct_A.z = -(f32)((f32)((f32)((f32)((f32)((f32)((f32)(v61 * 4.0) * 1.5708) + (f32)((f32)(v67 * (f32)(v67 * v67)) * -0.6459637)) + (f32)((f32)((f32)(v67 * v67) * (f32)(v67 * (f32)(v67 * v67))) * 0.07968968)) + (f32)((f32)((f32)(v67 * v67) * (f32)((f32)(v67 * v67) * (f32)(v67 * (f32)(v67 * v67)))) * -0.0046737655)) + (f32)((f32)((f32)(v67 * v67) * (f32)((f32)(v67 * v67) * (f32)((f32)(v67 * v67) * (f32)(v67 * (f32)(v67 * v67))))) * 0.00015148419)) * v247);
    v70 = v246;
    get_transpose(&v269, &mtx_A, 0);
    v280 = vct_A;
    v268 = v269;
    v272 = op_Multiply_60923920(&v268, v280, 0);
    vct_A = v272;
    v72 = &vf00.x;
    v72[8] = v251;
    v72[9] = v250;
    v72[10] = v249;
    v72[11] = v248;
    vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    v260 = vct_A;
    goto LABEL_166;
LABEL_167:
    vct_A = v260;
    goto LABEL_168;
LABEL_166:
    goto LABEL_167;
LABEL_168:
    if (v51 >= v50)
      continue;
    break;
  }
  goto LABEL_191;
LABEL_192:
  v240 = vct_A;
  goto LABEL_193;
LABEL_191:
  goto LABEL_192;
LABEL_193:
  v75 = &vf00.x;
  v75[4] = v233;
  v75[5] = v232;
  v75[6] = v231;
  v75[7] = v230;
  v76 = 0.0;
  while (2)
  {
    v76 = v76 + 0.15707964;
    if (v76 > v70)
      v77 = v70;
    else
      v77 = v76;
    v78 = (s32)(v77 * 0.15915494);
    if ((f32)(v77 * 0.15915494) == INFINITY)
      v78 = -2147500000.0;
    v79 = (f32)(v77 * 0.15915494) - v78;
    v80 = v79 + 1.0;
    if (v79 >= -0.5)
      v80 = v79;
    if (v79 > 0.5)
      v81 = v79 + -1.0;
    else
      v81 = v80;
    v82 = -0.5 - v81;
    if (v81 >= -0.25)
      v82 = v81;
    if (v81 > 0.25)
      v83 = 0.5 - v81;
    else
      v83 = v82;
    v84 = (f32)(v77 + 1.5708) * 0.15915494;
    v85 = (s32)v84;
    if (v84 == INFINITY)
      v85 = -2147500000.0;
    v86 = v84 - v85;
    if ((f32)(v84 - v85) <= 0.5)
    {
      if (v86 < -0.5)
        v86 = v86 + 1.0;
    }
    else
    {
      v86 = v86 + -1.0;
    }
    if (v86 <= 0.25)
    {
      if (v86 < -0.25)
      {
        v86 = -0.5 - v86;
      }
      else
      {
      }
LABEL_224:
      goto LABEL_226;
    }
    v86 = 0.5 - v86;
    goto LABEL_224;
LABEL_226:
    v89 = &vf00.x;
    v89[6] = v13;
    v89[7] = v12;
    v89[4] = x;
    v89[5] = y;
    ToMatrix();
    v91 = v83 * 4.0;
    v92 = v86 * 4.0;
    vct_A.x = 0.0;
    vct_A.w = 1.0;
    v94 = v91 * v91;
    vct_A.y = -(f32)((f32)((f32)((f32)((f32)((f32)((f32)(v83 * 4.0) * 1.5708) + (f32)((f32)(v91 * (f32)(v91 * v91)) * -0.6459637)) + (f32)((f32)((f32)(v91 * v91) * (f32)(v91 * (f32)(v91 * v91))) * 0.07968968)) + (f32)((f32)(v94 * (f32)(v94 * (f32)(v91 * (f32)(v91 * v91)))) * -0.0046737655)) + (f32)((f32)(v94 * (f32)(v94 * (f32)(v94 * (f32)(v91 * (f32)(v91 * v91))))) * 0.00015148419)) * area_r2);
    vct_A.z = -(f32)((f32)((f32)((f32)((f32)((f32)((f32)(v86 * 4.0) * 1.5708) + (f32)((f32)(v92 * (f32)(v92 * v92)) * -0.6459637)) + (f32)((f32)((f32)(v92 * v92) * (f32)(v92 * (f32)(v92 * v92))) * 0.07968968)) + (f32)((f32)((f32)(v92 * v92) * (f32)((f32)(v92 * v92) * (f32)(v92 * (f32)(v92 * v92)))) * -0.0046737655)) + (f32)((f32)((f32)(v92 * v92) * (f32)((f32)(v92 * v92) * (f32)((f32)(v92 * v92) * (f32)(v92 * (f32)(v92 * v92))))) * 0.00015148419)) * v247);
    v70 = v246;
    get_transpose(&v269, &mtx_A, 0);
    v281 = vct_A;
    v268 = v269;
    v273 = op_Multiply_60923920(&v268, v281, 0);
    vct_A = v273;
    v96 = &vf00.x;
    v96[8] = v251;
    v96[9] = v250;
    v96[10] = v249;
    v96[11] = v248;
    vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    v261 = vct_A;
    goto LABEL_238;
LABEL_239:
    vct_A = v261;
    goto LABEL_240;
LABEL_238:
    goto LABEL_239;
LABEL_240:
    if (v76 <= v70)
      continue;
    break;
  }
  goto LABEL_263;
LABEL_264:
  v236 = vct_A;
  goto LABEL_265;
LABEL_263:
  goto LABEL_264;
LABEL_265:
  v99 = &vf00.x;
  v99[4] = v233;
  v99[5] = v232;
  v99[6] = v231;
  v99[7] = v230;
  v100 = 0.0;
  while (2)
  {
    v100 = v100 + -0.15707964;
    if (v100 < v50)
      v101 = v50;
    else
      v101 = v100;
    v102 = (s32)(v101 * 0.15915494);
    if ((f32)(v101 * 0.15915494) == INFINITY)
      v102 = -2147500000.0;
    v103 = (f32)(v101 * 0.15915494) - v102;
    v104 = v103 + 1.0;
    if (v103 >= -0.5)
      v104 = v103;
    if (v103 > 0.5)
      v105 = v103 + -1.0;
    else
      v105 = v104;
    v106 = -0.5 - v105;
    if (v105 >= -0.25)
      v106 = v105;
    if (v105 > 0.25)
      v107 = 0.5 - v105;
    else
      v107 = v106;
    v108 = (f32)(v101 + 1.5708) * 0.15915494;
    v109 = (s32)v108;
    if (v108 == INFINITY)
      v109 = -2147500000.0;
    v110 = v108 - v109;
    if ((f32)(v108 - v109) <= 0.5)
    {
      if (v110 < -0.5)
        v110 = v110 + 1.0;
    }
    else
    {
      v110 = v110 + -1.0;
    }
    if (v110 <= 0.25)
    {
      if (v110 < -0.25)
      {
        v110 = -0.5 - v110;
      }
      else
      {
      }
LABEL_296:
      goto LABEL_298;
    }
    v110 = 0.5 - v110;
    goto LABEL_296;
LABEL_298:
    v113 = &vf00.x;
    v113[6] = v13;
    v113[7] = v12;
    v113[4] = x;
    v113[5] = y;
    ToMatrix();
    v115 = v107 * 4.0;
    v116 = v110 * 4.0;
    vct_A.x = 0.0;
    vct_A.w = 1.0;
    v118 = v115 * v115;
    vct_A.y = -(f32)((f32)((f32)((f32)((f32)((f32)((f32)(v107 * 4.0) * 1.5708) + (f32)((f32)(v115 * (f32)(v115 * v115)) * -0.6459637)) + (f32)((f32)((f32)(v115 * v115) * (f32)(v115 * (f32)(v115 * v115))) * 0.07968968)) + (f32)((f32)(v118 * (f32)(v118 * (f32)(v115 * (f32)(v115 * v115)))) * -0.0046737655)) + (f32)((f32)(v118 * (f32)(v118 * (f32)(v118 * (f32)(v115 * (f32)(v115 * v115))))) * 0.00015148419)) * area_r2);
    vct_A.z = -(f32)((f32)((f32)((f32)((f32)((f32)((f32)(v110 * 4.0) * 1.5708) + (f32)((f32)(v116 * (f32)(v116 * v116)) * -0.6459637)) + (f32)((f32)((f32)(v116 * v116) * (f32)(v116 * (f32)(v116 * v116))) * 0.07968968)) + (f32)((f32)((f32)(v116 * v116) * (f32)((f32)(v116 * v116) * (f32)(v116 * (f32)(v116 * v116)))) * -0.0046737655)) + (f32)((f32)((f32)(v116 * v116) * (f32)((f32)(v116 * v116) * (f32)((f32)(v116 * v116) * (f32)(v116 * (f32)(v116 * v116))))) * 0.00015148419)) * v247);
    get_transpose(&v269, &mtx_A, 0);
    v282 = vct_A;
    v268 = v269;
    v274 = op_Multiply_60923920(&v268, v282, 0);
    vct_A = v274;
    v120 = &vf00.x;
    v120[8] = v251;
    v120[9] = v250;
    v120[10] = v249;
    v120[11] = v248;
    vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    v262 = vct_A;
    goto LABEL_310;
LABEL_311:
    vct_A = v262;
    goto LABEL_312;
LABEL_310:
    goto LABEL_311;
LABEL_312:
    if (v100 >= v50)
      continue;
    break;
  }
  v122 = -0.5;
  v123 = -1.0;
  goto LABEL_335;
LABEL_336:
  vct_A = v254;
  goto LABEL_337;
LABEL_365:
  goto LABEL_366;
LABEL_367:
  goto LABEL_368;
LABEL_369:
  goto LABEL_370;
LABEL_335:
  goto LABEL_336;
LABEL_337:
  goto LABEL_365;
LABEL_366:
  v263 = vct_A;
  goto LABEL_367;
LABEL_368:
  vct_B = v240;
  goto LABEL_369;
LABEL_370:
  vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  v126.n128_u64[0] = 0x3F0000003F000000LL;
  v126.n128_u64[1] = 0x3F0000003F000000LL;
  vct_A = (struct sdfVector4_t)vmulq_f32((float32x4_t)vct_A, v126);
  v127 = &vf00.x;
  v128 = v127[7];
  v255 = v127[4];
  v129 = v127[6];
  v241 = v127[5];
  goto LABEL_376;
LABEL_377:
  goto LABEL_378;
LABEL_379:
  goto LABEL_380;
LABEL_381:
  goto LABEL_382;
LABEL_376:
  vct_A = v236;
  goto LABEL_377;
LABEL_378:
  v234 = vct_A;
  goto LABEL_379;
LABEL_380:
  vct_A = v263;
  goto LABEL_381;
LABEL_382:
  v130 = &vf00.x;
  v130[10] = v129;
  v130[11] = v128;
  v130[8] = v255;
  v130[9] = v241;
  vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  goto LABEL_386;
LABEL_387:
  goto LABEL_388;
LABEL_389:
  goto LABEL_390;
LABEL_386:
  v237 = vct_A;
  goto LABEL_387;
LABEL_388:
  vct_A = v234;
  goto LABEL_389;
LABEL_390:
  vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  v131 = 0.0;
  v235 = vct_A;
  while (2)
  {
    v131 = v131 + 0.15707964;
    if (v131 > 6.2831855)
      v132 = 6.2831855;
    else
      v132 = v131;
    vct_A = v237;
    v134 = (f32)(v132 + 1.5708) * 0.15915494;
    v135 = (s32)v134;
    if (v134 == INFINITY)
      v135 = -2147500000.0;
    v136 = v134 - v135;
    if (v136 <= 0.5)
    {
      if (v136 < v122)
        v136 = v136 + 1.0;
    }
    else
    {
      v136 = v136 + v123;
    }
    v137 = v122 - v136;
    if (v136 >= -0.25)
      v137 = v136;
    if (v136 > 0.25)
      v138 = 0.5 - v136;
    else
      v138 = v137;
    v139 = v138 * 4.0;
    v140 = v139 * (f32)(v139 * v139);
    vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, (f32)((f32)((f32)((f32)((f32)(v138 * 4.0) * 1.5708) + (f32)(v140 * -0.6459637)) + (f32)((f32)((f32)((f32)(v138 * 4.0) * (f32)(v138 * 4.0)) * v140) * 0.07968968)) + (f32)((f32)((f32)(v139 * v139) * (f32)((f32)(v139 * v139) * v140)) * -0.0046737655)) + (f32)((f32)((f32)((f32)(v138 * 4.0) * (f32)(v138 * 4.0)) * (f32)((f32)(v139 * v139) * (f32)((f32)(v139 * v139) * v140))) * 0.00015148419));
    v122 = -0.5;
    goto LABEL_415;
LABEL_416:
    goto LABEL_417;
LABEL_415:
    vct_B = vct_A;
    goto LABEL_416;
LABEL_417:
    vct_A = v235;
    v141 = v132 * 0.15915494;
    v142 = (s32)(v132 * 0.15915494);
    if ((f32)(v132 * 0.15915494) == INFINITY)
      v142 = -2147500000.0;
    v143 = v141 - v142;
    if ((f32)(v141 - v142) <= 0.5)
    {
      if (v143 < v122)
        v143 = v143 + 1.0;
    }
    else
    {
      v143 = v143 + v123;
    }
    if (v143 <= 0.25)
    {
      if (v143 < -0.25)
      {
        v143 = v122 - v143;
      }
      else if (!byte_575608A)
      {
        goto LABEL_466;
      }
LABEL_428:
      goto LABEL_429;
    }
    v143 = 0.5 - v143;
    goto LABEL_428;
LABEL_466:
LABEL_429:
    v144 = v143 * 4.0;
    v145 = v144 * (f32)(v144 * v144);
    vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, -(f32)((f32)((f32)((f32)((f32)((f32)(v143 * 4.0) * 1.5708) + (f32)(v145 * -0.6459637)) + (f32)((f32)((f32)((f32)(v143 * 4.0) * (f32)(v143 * 4.0)) * v145) * 0.07968968)) + (f32)((f32)((f32)(v144 * v144) * (f32)((f32)(v144 * v144) * v145)) * -0.0046737655)) + (f32)((f32)((f32)((f32)(v143 * 4.0) * (f32)(v143 * 4.0)) * (f32)((f32)(v144 * v144) * (f32)((f32)(v144 * v144) * v145))) * 0.00015148419)));
    vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    v146 = &vf00.x;
    v146[10] = v129;
    v146[11] = v128;
    v146[8] = v255;
    v146[9] = v241;
    vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    v264 = vct_A;
    goto LABEL_439;
LABEL_440:
    vct_A = v264;
    goto LABEL_441;
LABEL_439:
    goto LABEL_440;
LABEL_441:
    if (v131 <= 6.2831855)
      continue;
    break;
  }
  v147 = v246;
  v149 = 2;
  v150 = &vf00.x;
  v150[4] = v233;
  v150[5] = v232;
  v150[6] = v231;
  v150[7] = v230;
  while (2)
  {
    v151 = &v243[v149++];
    *v151 = vct_A;
    if (v149 != 22)
      continue;
    break;
  }
  v153 = 0.0;
  while (2)
  {
    v154 = v153 + 0.15707964;
    if (v154 > v147)
      v155 = v147;
    else
      v155 = v154;
    v156 = v155 * 0.15915494;
    v157 = (s32)(v155 * 0.15915494);
    if ((f32)(v155 * 0.15915494) == INFINITY)
      v157 = -2147500000.0;
    v158 = v156 - v157;
    if ((f32)(v156 - v157) <= 0.5)
    {
      v159 = v156 - v157;
      if (v158 < v122)
        v159 = v158 + 1.0;
    }
    else
    {
      v159 = v158 + v123;
    }
    v242 = v154;
    if (v159 <= 0.25)
    {
      if (v159 < -0.25)
        v159 = v122 - v159;
    }
    else
    {
      v159 = 0.5 - v159;
    }
    v160 = (f32)(v155 + 1.5708) * 0.15915494;
    v161 = (s32)v160;
    if (v160 == INFINITY)
      v161 = -2147500000.0;
    v162 = v160 - v161;
    if ((f32)(v160 - v161) <= 0.5)
    {
      v163 = v160 - v161;
      if (v162 < v122)
        v163 = v162 + 1.0;
    }
    else
    {
      v163 = v162 + v123;
    }
    if (v163 <= 0.25)
    {
      if (v163 < -0.25)
      {
        v163 = v122 - v163;
      }
      else
      {
      }
LABEL_507:
      goto LABEL_509;
    }
    v163 = 0.5 - v163;
    goto LABEL_507;
LABEL_509:
    v166 = &vf00.x;
    v166[4] = x;
    v166[5] = y;
    v166[6] = z;
    v166[7] = w;
    ToMatrix();
    v168 = v159 * 4.0;
    v169 = v163 * 4.0;
    vct_A.x = 0.0;
    vct_A.w = 1.0;
    v171 = v168 * v168;
    vct_A.y = -(f32)((f32)((f32)((f32)((f32)((f32)((f32)(v159 * 4.0) * 1.5708) + (f32)((f32)(v168 * (f32)(v168 * v168)) * -0.6459637)) + (f32)((f32)((f32)(v168 * v168) * (f32)(v168 * (f32)(v168 * v168))) * 0.07968968)) + (f32)((f32)(v171 * (f32)(v171 * (f32)(v168 * (f32)(v168 * v168)))) * -0.0046737655)) + (f32)((f32)(v171 * (f32)(v171 * (f32)(v171 * (f32)(v168 * (f32)(v168 * v168))))) * 0.00015148419)) * area_r2);
    vct_A.z = -(f32)((f32)((f32)((f32)((f32)((f32)((f32)(v163 * 4.0) * 1.5708) + (f32)((f32)(v169 * (f32)(v169 * v169)) * -0.6459637)) + (f32)((f32)((f32)(v169 * v169) * (f32)(v169 * (f32)(v169 * v169))) * 0.07968968)) + (f32)((f32)((f32)(v169 * v169) * (f32)((f32)(v169 * v169) * (f32)(v169 * (f32)(v169 * v169)))) * -0.0046737655)) + (f32)((f32)((f32)(v169 * v169) * (f32)((f32)(v169 * v169) * (f32)((f32)(v169 * v169) * (f32)(v169 * (f32)(v169 * v169))))) * 0.00015148419)) * v247);
    v173 = z;
    v172 = w;
    get_transpose(&v269, &mtx_A, 0);
    v283 = vct_A;
    v268 = v269;
    v275 = op_Multiply_60923920(&v268, v283, 0);
    vct_A = v275;
    v175 = &vf00.x;
    v175[8] = v251;
    v175[9] = v250;
    v175[10] = v249;
    v175[11] = v248;
    vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    goto LABEL_519;
LABEL_520:
    v176 = -1.0;
LABEL_553:
    v158 = v158 + v176;
    goto LABEL_9013;
LABEL_519:
    v265 = vct_A;
    if (v158 > 0.5)
      goto LABEL_520;
    if (v158 < -0.5)
    {
      v176 = 1.0;
      goto LABEL_553;
    }
LABEL_9013:
    if (v158 <= 0.25)
    {
      if (v158 < -0.25)
        v158 = -0.5 - v158;
    }
    else
    {
      v158 = 0.5 - v158;
    }
    if (v162 > 0.5)
    {
      v177 = -1.0;
      goto LABEL_562;
    }
    if (v162 < -0.5)
    {
      v177 = 1.0;
LABEL_562:
      v162 = v162 + v177;
    }
    if (v162 <= 0.25)
    {
      if (v162 < -0.25)
      {
        v162 = -0.5 - v162;
      }
      else if (!byte_5755EF5)
      {
        goto LABEL_763;
      }
LABEL_568:
      goto LABEL_569;
    }
    v162 = 0.5 - v162;
    goto LABEL_568;
LABEL_763:
LABEL_569:
    v178 = &vf00.x;
    v178[6] = v173;
    v178[7] = v172;
    v178[4] = x;
    v178[5] = y;
    ToMatrix();
    v180 = v158 * 4.0;
    v181 = v162 * 4.0;
    vct_A.y = 0.0;
    vct_A.w = 1.0;
    v183 = v180 * v180;
    vct_A.x = -(f32)((f32)((f32)((f32)((f32)((f32)((f32)(v158 * 4.0) * 1.5708) + (f32)((f32)(v180 * (f32)(v180 * v180)) * -0.6459637)) + (f32)((f32)((f32)(v180 * v180) * (f32)(v180 * (f32)(v180 * v180))) * 0.07968968)) + (f32)((f32)(v183 * (f32)(v183 * (f32)(v180 * (f32)(v180 * v180)))) * -0.0046737655)) + (f32)((f32)(v183 * (f32)(v183 * (f32)(v183 * (f32)(v180 * (f32)(v180 * v180))))) * 0.00015148419)) * v247);
    vct_A.z = -(f32)((f32)((f32)((f32)((f32)((f32)((f32)(v162 * 4.0) * 1.5708) + (f32)((f32)(v181 * (f32)(v181 * v181)) * -0.6459637)) + (f32)((f32)((f32)(v181 * v181) * (f32)(v181 * (f32)(v181 * v181))) * 0.07968968)) + (f32)((f32)((f32)(v181 * v181) * (f32)((f32)(v181 * v181) * (f32)(v181 * (f32)(v181 * v181)))) * -0.0046737655)) + (f32)((f32)((f32)(v181 * v181) * (f32)((f32)(v181 * v181) * (f32)((f32)(v181 * v181) * (f32)(v181 * (f32)(v181 * v181))))) * 0.00015148419)) * v247);
    get_transpose(&v269, &mtx_A, 0);
    v284 = vct_A;
    v268 = v269;
    v276 = op_Multiply_60923920(&v268, v284, 0);
    vct_A = v276;
    v185 = &vf00.x;
    v185[8] = v251;
    v185[9] = v250;
    v185[10] = v249;
    v185[11] = v248;
    vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    v186 = v155 * -0.15915494;
    v256 = vct_A;
    v187 = (s32)(v155 * -0.15915494);
    if ((f32)(v155 * -0.15915494) == INFINITY)
      v187 = -2147500000.0;
    v188 = v186 - v187;
    if ((f32)(v186 - v187) > 0.5)
    {
      v189 = -1.0;
      goto LABEL_585;
    }
    if (v188 < -0.5)
    {
      v189 = 1.0;
LABEL_585:
      v188 = v188 + v189;
    }
    if (v188 <= 0.25)
    {
      if (v188 < -0.25)
        v188 = -0.5 - v188;
    }
    else
    {
      v188 = 0.5 - v188;
    }
    v190 = (f32)(1.5708 - v155) * 0.15915494;
    v191 = (s32)v190;
    if (v190 == INFINITY)
      v191 = -2147500000.0;
    v192 = v190 - v191;
    if ((f32)(v190 - v191) > 0.5)
    {
      v193 = -1.0;
      goto LABEL_596;
    }
    if (v192 < -0.5)
    {
      v193 = 1.0;
LABEL_596:
      v192 = v192 + v193;
    }
    if (v192 <= 0.25)
    {
      if (v192 < -0.25)
      {
        v192 = -0.5 - v192;
      }
      else if (!byte_5755EF5)
      {
        goto LABEL_766;
      }
LABEL_602:
      goto LABEL_603;
    }
    v192 = 0.5 - v192;
    goto LABEL_602;
LABEL_766:
LABEL_603:
    v194 = &vf00.x;
    v194[6] = v173;
    v194[7] = v172;
    v194[4] = x;
    v194[5] = y;
    ToMatrix();
    v122 = -0.5;
    v196 = v188 * 4.0;
    v197 = v192 * 4.0;
    vct_A.y = 0.0;
    vct_A.w = 1.0;
    v199 = v196 * v196;
    vct_A.x = -(f32)((f32)((f32)((f32)((f32)((f32)((f32)(v188 * 4.0) * 1.5708) + (f32)((f32)(v196 * (f32)(v196 * v196)) * -0.6459637)) + (f32)((f32)((f32)(v196 * v196) * (f32)(v196 * (f32)(v196 * v196))) * 0.07968968)) + (f32)((f32)(v199 * (f32)(v199 * (f32)(v196 * (f32)(v196 * v196)))) * -0.0046737655)) + (f32)((f32)(v199 * (f32)(v199 * (f32)(v199 * (f32)(v196 * (f32)(v196 * v196))))) * 0.00015148419)) * v247);
    vct_A.z = -(f32)((f32)((f32)((f32)((f32)((f32)((f32)(v192 * 4.0) * 1.5708) + (f32)((f32)(v197 * (f32)(v197 * v197)) * -0.6459637)) + (f32)((f32)((f32)(v197 * v197) * (f32)(v197 * (f32)(v197 * v197))) * 0.07968968)) + (f32)((f32)((f32)(v197 * v197) * (f32)((f32)(v197 * v197) * (f32)(v197 * (f32)(v197 * v197)))) * -0.0046737655)) + (f32)((f32)((f32)(v197 * v197) * (f32)((f32)(v197 * v197) * (f32)((f32)(v197 * v197) * (f32)(v197 * (f32)(v197 * v197))))) * 0.00015148419)) * v247);
    get_transpose(&v269, &mtx_A, 0);
    v285 = vct_A;
    v268 = v269;
    v277 = op_Multiply_60923920(&v268, v285, 0);
    vct_A = v277;
    v201 = &vf00.x;
    v201[8] = v251;
    v201[9] = v250;
    v201[10] = v249;
    v201[11] = v248;
    vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    goto LABEL_613;
LABEL_614:
    goto LABEL_615;
LABEL_616:
    goto LABEL_617;
LABEL_618:
    goto LABEL_619;
LABEL_620:
    goto LABEL_621;
LABEL_613:
    v238 = vct_A;
    goto LABEL_614;
LABEL_615:
    vct_A = v256;
    goto LABEL_616;
LABEL_617:
    v257 = vct_A;
    goto LABEL_618;
LABEL_619:
    vct_B = v238;
    goto LABEL_620;
LABEL_621:
    vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    v202.n128_u64[0] = 0x3F0000003F000000LL;
    v202.n128_u64[1] = 0x3F0000003F000000LL;
    vct_A = (struct sdfVector4_t)vmulq_f32((float32x4_t)vct_A, v202);
    goto LABEL_625;
LABEL_626:
    goto LABEL_627;
LABEL_628:
    goto LABEL_629;
LABEL_630:
    goto LABEL_631;
LABEL_632:
    goto LABEL_633;
LABEL_625:
    v203 = &vf00.x;
    v204 = v203[4];
    v205 = v203[5];
    v207 = v203[6];
    v206 = v203[7];
    goto LABEL_626;
LABEL_627:
    vct_A = v265;
    goto LABEL_628;
LABEL_629:
    v239 = vct_A;
    goto LABEL_630;
LABEL_631:
    vct_A = v257;
    goto LABEL_632;
LABEL_633:
    v208 = &vf00.x;
    v208[8] = v204;
    v208[9] = v205;
    v208[10] = v207;
    v208[11] = v206;
    vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    goto LABEL_637;
LABEL_638:
    goto LABEL_639;
LABEL_640:
    goto LABEL_641;
LABEL_637:
    v266 = vct_A;
    goto LABEL_638;
LABEL_639:
    vct_A = v239;
    goto LABEL_640;
LABEL_641:
    vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    v209 = 0.0;
    v210 = 2;
    v258 = vct_A;
    while (2)
    {
      vct_A = v266;
      v209 = v209 + 0.31415927;
      v213 = (f32)(v209 + 1.5708) * 0.15915494;
      v214 = (s32)v213;
      if (v213 == INFINITY)
        v214 = -2147500000.0;
      v215 = v213 - v214;
      if (v215 > 0.5)
      {
        v216 = -1.0;
        goto LABEL_654;
      }
      if (v215 < v122)
      {
        v216 = 1.0;
LABEL_654:
        v215 = v215 + v216;
      }
      v217 = v122 - v215;
      if (v215 >= -0.25)
        v217 = v215;
      if (v215 > 0.25)
        v218 = 0.5 - v215;
      else
        v218 = v217;
      v219 = v218 * 4.0;
      v220 = v219 * (f32)(v219 * v219);
      vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, (f32)((f32)((f32)((f32)((f32)(v218 * 4.0) * 1.5708) + (f32)(v220 * -0.6459637)) + (f32)((f32)((f32)((f32)(v218 * 4.0) * (f32)(v218 * 4.0)) * v220) * 0.07968968)) + (f32)((f32)((f32)(v219 * v219) * (f32)((f32)(v219 * v219) * v220)) * -0.0046737655)) + (f32)((f32)((f32)((f32)(v218 * 4.0) * (f32)(v218 * 4.0)) * (f32)((f32)(v219 * v219) * (f32)((f32)(v219 * v219) * v220))) * 0.00015148419));
      goto LABEL_664;
LABEL_665:
      goto LABEL_666;
LABEL_664:
      vct_B = vct_A;
      goto LABEL_665;
LABEL_666:
      vct_A = v258;
      v221 = v209 * 0.15915494;
      v222 = (s32)(v209 * 0.15915494);
      if ((f32)(v209 * 0.15915494) == INFINITY)
        v222 = -2147500000.0;
      v223 = v221 - v222;
      if ((f32)(v221 - v222) > 0.5)
      {
        v224 = -1.0;
        goto LABEL_672;
      }
      if (v223 < -0.5)
      {
        v224 = 1.0;
LABEL_672:
        v223 = v223 + v224;
      }
      if (v223 <= 0.25)
      {
        if (v223 < -0.25)
        {
          v223 = -0.5 - v223;
        }
        else if (!byte_575608A)
        {
          goto LABEL_706;
        }
LABEL_678:
        goto LABEL_679;
      }
      v223 = 0.5 - v223;
      goto LABEL_678;
LABEL_706:
LABEL_679:
      v225 = v223 * 4.0;
      v226 = v225 * (f32)(v225 * v225);
      vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, -(f32)((f32)((f32)((f32)((f32)((f32)(v223 * 4.0) * 1.5708) + (f32)(v226 * -0.6459637)) + (f32)((f32)((f32)((f32)(v223 * 4.0) * (f32)(v223 * 4.0)) * v226) * 0.07968968)) + (f32)((f32)((f32)(v225 * v225) * (f32)((f32)(v225 * v225) * v226)) * -0.0046737655)) + (f32)((f32)((f32)((f32)(v223 * 4.0) * (f32)(v223 * 4.0)) * (f32)((f32)(v225 * v225) * (f32)((f32)(v225 * v225) * v226))) * 0.00015148419)));
      v122 = -0.5;
      vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
      goto LABEL_683;
LABEL_684:
      goto LABEL_685;
LABEL_683:
      v227 = &vf00.x;
      v227[8] = v204;
      v227[9] = v205;
      v227[10] = v207;
      v227[11] = v206;
      goto LABEL_684;
LABEL_685:
      vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
      v211 = &v267[v210++];
      *v211 = vct_A;
      if (v210 != 22)
        continue;
      break;
    }
    v123 = -1.0;
    v147 = v246;
    v153 = v242;
    v243[2] = v267[2];
    v243[3] = v267[3];
    v243[4] = v267[4];
    v243[5] = v267[5];
    v243[6] = v267[6];
    v243[7] = v267[7];
    v243[8] = v267[8];
    v243[9] = v267[9];
    v243[10] = v267[10];
    v243[11] = v267[11];
    v243[12] = v267[12];
    v243[13] = v267[13];
    v243[14] = v267[14];
    v243[15] = v267[15];
    v243[16] = v267[16];
    v243[17] = v267[17];
    v243[18] = v267[18];
    v243[19] = v267[19];
    v243[20] = v267[20];
    v243[21] = v267[21];
    if (v242 <= v246)
      continue;
    break;
  }
}

// 0x19258b0
void sBtlDebug_HitTypeMoveDraw(SBTLSKILLHIT_TBL *hwk, SBDEBUG_PATHDATA *path) {
  char *v6;
  char *v10;
  char *v13;

  v6 = sblist_efhitmenu_hittype[hwk->type];
  DbgText(4608, 80, v6, 0, 109, 24, 0);
  if ((hwk->flg & 0x100) == 0)
  {
    goto LABEL_11;
  }
  v13 = sblist_efhitmenu_edit_para03_1[path->nef_movetype];
  DbgText(6400, 80, v13, 0, 109, 24, 0);
LABEL_11:
  if (sbtldbwk->mode == 13)
    goto LABEL_12;
  return;
  if (sbtldbwk->mode == 13)
  {
LABEL_12:
    v10 = motion_tbl_new[hwk->motionno];
    DbgText(6400, 80, v10, 0, 109, 24, 0);
    return;
  }
}

// 0x193b0e0
void sBtlDebug_ShutdownCamera(dds3ProcessID_t *id) {
  dds3Basic_t *pUnitBasic;
  SBTLDEBUG_WORK *v6;

  if (!sbtldbwk)
    return;
  pUnitBasic = sbtldbwk->pUnitBasic;
  if (pUnitBasic)
  {
    dds3SceneBasicDelete(pUnitBasic);
    v6 = sbtldbwk;
    v6->pUnitBasic = 0;
    return;
  }
}

// 0x1929640
bool sBtlDebug_CheckMainPanel(SBTLUNIT_WORK *wk) {
  u64 **v6;
  s64 status;

  goto LABEL_5;
LABEL_11:
  if (gDbgBound_Step <= 0)
    goto LABEL_15;
  LOBYTE(v6) = 1;
  return (char)v6;
LABEL_5:
  if (gDbgBound_Use)
    goto LABEL_11;
LABEL_15:
  v6 = dds3SearchProcessName("sbtldebug_proc");
  if (!v6)
    return (char)v6;
  status = sbtldbwk->status;
  if ((status & 1) == 0)
    goto LABEL_19;
  if (wk && (wk->vstatus & 0x4000) != 0)
    goto LABEL_32;
LABEL_31:
  LOBYTE(v6) = 1;
  return (char)v6;
LABEL_19:
  if ((status & 0x30) == 0)
    goto LABEL_32;
  goto LABEL_9001;
  if ((sbtldbwk->status & 0x30) == 0)
  {
LABEL_32:
    LOBYTE(v6) = 0;
    return (char)v6;
  }
LABEL_9001:
  if (!wk || (wk->vstatus & 0x4000) == 0)
    goto LABEL_31;
  LOBYTE(v6) = *(u16 *)(*v6[23] + 326) == 3;
  return (char)v6;
}

// 0x193b2d0
bool sBtlDebug_CheckEffectEditor(void) {
  return (sbtldbwk->status & 0x30) != 0;
}

// 0x193b340
bool sbattleSbtlDebug_CheckFreeCameraFlg(void) {
  u64 **v2;

  v2 = dds3SearchProcessName("sbtldebug_proc");
  if (!v2)
    return (char)v2;
  LODWORD(v2) = (*(u8 *)(*v2[23] + 16) >> 1) & 1;
  return (char)v2;
}

// 0x19298a0
void sBtlDebug_ResetPos_PlayerSide(void) {
  SBTLUNIT_LISTWORK *UnitMng;
  s32 playerID;
  SBTLUNIT_WORK *v5;
  SBTLUNIT_WORK *v6;
  s32 v8;
  f32 *p_x;
  f32 v12;
  s64 i;
  u32 stock_mask;
  SBATTLE_WORK *v18;
  SBTLUNIT_LISTWORK *v19;
  s32 v20;
  SBTLUNIT_WORK *v21;
  SBTLUNIT_WORK *v22;
  SBTLUNIT_WORK *v24;
  f32 x;
  f32 y;
  f32 z;
  f32 w;
  SBTLEFF_LISTWORK *effList;
  sdfVector4_t v30;

  UnitMng = wk->UnitMng;
  playerID = wk->playerID;
  v5 = sBtlSearchUnit_ID(UnitMng, playerID);
  if (!v5)
    goto LABEL_17;
  v6 = v5;
  v8 = (u8)byte_5755EF6;
  vct_A = (struct sdfVector4_t)xmmword_3CFB7C0;
  if (v8)
  {
    p_x = &v6->pos.x;
LABEL_14:
    *(sdfVector4_t *)p_x = vct_A;
    v12 = *p_x;
    v6->pos.x = v12 + main_data->offset_x;
    v6->pos.z = v6->pos.z + main_data->offset_z;
    goto LABEL_17;
  }
  else
  {
    p_x = &v6->pos.x;
    goto LABEL_14;
  }
  goto LABEL_14;
LABEL_17:
  for (i = 0; i != 32; ++i)
  {
    stock_mask = wk->stock_mask;
    if (!sBtlCheckBit(stock_mask, i))
      continue;
    v18 = wk;
    if (v18->summonflg[i] == 2)
    {
      v18 = wk;
      v19 = v18->UnitMng;
      v20 = v18->summonID[i];
      v21 = sBtlSearchUnit_ID(v19, v20);
      if (!v21)
        continue;
      v22 = v21;
      if (!sBtlCheckDamageTarget(v21))
        continue;
      if ((v22->status & 0x800000) == 0)
      {
        wk->summonflg[i] = 3;
        v24 = sBtlResetSummon(i, 0);
        x = v24->pos.x;
        y = v24->pos.y;
        z = v24->pos.z;
        w = v24->pos.w;
        effList = wk->effList;
        v30.x = x;
        v30.y = y;
        v30.z = z;
        v30.w = w;
        sBtlCreateEff(effList, v24, 3, 0, v30, 0x80808080, 0, 1.0, 0);
        v24->actcounter = v24->actcounter_max;
      }
    }
  }
}

// 0x193b420
bool sBtlDebug_Init(void) {
  dds3ProcessID_t *v1;
  SBTLDEBUG_WORK *v2;
  SBTLDEBUG_WORK *sbtldbwk_local;
  s64 v6;
  s64 i;
  s64 v8;
  SBTLEFF_DATAWORK *ef_dwk;
  SBTLEFF_DATAWORK *v10;
  dds3ProcessFunc_t v12;
  shutdownfuncDelegate v13;
  SBTLDEBUG_WORK *v16;
  SBDEBUG_CSRWORK *maincsr;
  SBATTLE_WORK *wk_local;
  SBTLDMG_HITLISTWORK *HitList;
  SBTLDEBUG_WORK *v21;
  SBDEBUG_FILELISTWORK *v22;
  SBTLDEBUG_WORK *v23;
  SBDEBUG_CSRWORK *opticsr;
  s64 status;
  SBTLDEBUG_WORK *v26;
  _OWORD *p_m00;
  _OWORD *p_x;
  __int128 v30;
  __int128 v31;
  __int128 v32;
  SBTLDEBUG_WORK *v33;
  _OWORD *v35;
  _OWORD *v36;
  __int128 v37;
  __int128 v38;
  __int128 v39;
  SBTLDEBUG_WORK *v40;
  _OWORD *v42;
  _OWORD *v43;
  __int128 v45;
  __int128 v46;
  __int128 v47;
  SBTLDEBUG_WORK *v48;
  s64 v49;
  s32 *targetID;
  dds3ProcessFunc_t v51;
  shutdownfuncDelegate v52;
  SBTLDEBUG_WORK *v57;
  dds3ProcessID_t *target;

  v1 = Allocate(dds3ProcessID_t);
  _ctor(v1, 0);
  target = v1;
  v2 = Allocate(SBTLDEBUG_WORK);
  _ctor(v2, 0);
  sbtldbwk = v2;
  sbtldbwk_local = sbtldbwk;
  sbtldbwk_local->pUnitBasic = 0;
  v6 = 32;
  for (i = 32; i != 96; i += 4)
  {
    ef_dwk = sbtldbwk->ef_dwk;
    v10 = Allocate(SBTLEFF_DATAWORK);
    _ctor(v10, 0);
    *(Il2CppClass **)((char *)&ef_dwk->obj.klass + v6) = v10;
    v8 = *(s64 *)((char *)&sbtldbwk->ef_dwk->obj.klass + v6);
    *(u64 *)(v8 + 32) = 0;
    v6 += 8;
    *(u32 *)((char *)&sbtldbwk->ef_dwksize->obj.klass + i) = 0;
  }
  v12 = Allocate(dds3ProcessFunc_t);
  _ctor(v12, 0, Method_Project_sbattle_sBtlDebug_Proc__, 0);
  v13 = Allocate(shutdownfuncDelegate);
  _ctor(v13, 0, Method_Project_sbattle_sBtlDebug_Shutdown__, 0);
  target = dds3StartProcess("sbtldebug_proc", 1016, 1, 1, v12, v13, 0);
  dds3LinkProcess(&wk->MProc_ID, target);
  v16 = sbtldbwk;
  v16->mode = 0;
  maincsr = v16->maincsr;
  wk_local = wk;
  maincsr->point = 0;
  maincsr->maxp = 22;
  HitList = sBtlCreateHitList();
  wk_local->dbghitList = HitList;
  v21 = sbtldbwk;
  v22 = Allocate(SBDEBUG_FILELISTWORK);
  _ctor(v22, 0);
  v22->wk = 0;
  v21->fileList = v22;
  v23 = sbtldbwk;
  opticsr = v23->opticsr;
  status = v23->status;
  v23->resetencount = 0;
  opticsr->maxp = 38;
  opticsr->point = 0;
  v23->status = status | 8;
  sub_1949280(0, 0.2617994);
  v26 = sbtldbwk;
  p_m00 = &v26->mat.m00;
  p_x = &vf00.x;
  v30 = p_x[5];
  v31 = p_x[6];
  v32 = p_x[7];
  *p_m00 = p_x[4];
  p_m00[1] = v30;
  p_m00[2] = v31;
  p_m00[3] = v32;
  sub_19493E0(0, 0.2617994);
  v33 = sbtldbwk;
  v35 = &v33->mat2.m00;
  v36 = &vf00.x;
  v37 = v36[5];
  v38 = v36[6];
  v39 = v36[7];
  *v35 = v36[4];
  v35[1] = v37;
  v35[2] = v38;
  v35[3] = v39;
  sub_1949540(0, 0.2617994);
  v40 = sbtldbwk;
  v42 = &v40->mat3.m00;
  v43 = &vf00.x;
  v45 = v43[5];
  v46 = v43[6];
  v47 = v43[7];
  *v42 = v43[4];
  v42[1] = v45;
  v42[2] = v46;
  v42[3] = v47;
  v48 = sbtldbwk;
  v48->acterID = -1;
  *(u64 *)&v48->prev_skillid = 0x12000000120LL;
  v49 = v48->status;
  v48->sklccsr->point = 0;
  v48->y_status |= 0x70u;
  v48->status = v49 & 0xFFFFFFFFFE6F9DFFLL | 0x906200;
  targetID = v48->targetID;
  targetID[0] = -1;
  targetID[1] = -1;
  targetID[2] = -1;
  targetID[3] = -1;
  targetID[4] = -1;
  targetID[5] = -1;
  targetID[6] = -1;
  targetID[7] = -1;
  targetID[8] = -1;
  v51 = Allocate(dds3ProcessFunc_t);
  _ctor(v51, 0, Method_Project_sbattle_ProcCamera__, 0);
  v52 = Allocate(shutdownfuncDelegate);
  _ctor(v52, 0, Method_Project_sbattle_sBtlDebug_ShutdownCamera__, 0);
  target = dds3StartProcess("sbtldebug_cameraproc", 1035, 1, 1, v51, v52, 0);
  dds3LinkProcess(&wk->MProc_ID, target);
  v57 = sbtldbwk;
  sbtldbwk->status |= 0x30000000u;
  v57->raidouP = GBWK->player->para->level;
  return 1;
}

// 0x193bd90
bool sBtlDebug_Draw(void) {
  dds3ProcessID_t *v2;
  dds3ProcessID_t *v4;
  s64 status;
  sbdebug_drawmenuDelegate v10;

  v2 = dds3SearchProcessName("sbtldebug_proc");
  if (!v2)
    return 0;
  v4 = v2;
  status = sbtldbwk->status;
  if ((status & 0x100) == 0)
  {
    v10 = sbdebug_drawmenu[sbtldbwk->mode];
    return (v10->invoke_impl)(v10->method_code, v4, v10->method);
  }
  sbtldbwk->status = status & 0xFFFFFFFFFFFFFEFFLL;
  return 0;
}

// 0x1914da0
void sBtlDebug_SetDuummyData(s32 ptn) {
  u64 *v2;
  u32 *v3;
  u32 *v4;
  u32 *v5;
  u32 *v6;
  u32 *v7;
  u64 *v8;
  s64 v9;
  sdatPlayerUnitWork_t *PlayerData;
  s64 i;
  u32 v12;
  SBTLITEM_TBL *Itemtbl;
  s64 v16;
  s64 v17;
  SBTLAISYO_DATAWORK *Aisyotbl;
  s16 talkskill;
  SKLID *v20;
  SKLID *aRsvSkl;
  s32 v22;
  DEVILDATA_WORK *DevilData;
  s32 mp;
  s32 maxmp;
  s16 str;
  s16 vit;
  s16 tec;
  s16 luck;
  s32 aishou;
  sdatUnitWork_t *v31;
  s8 kuda_id;
  sdatParaWork_t *now;
  sdatParaWork_t *backup;
  s16 v35;
  s32 hp;
  s32 maxhp;
  SKLID *haveskill;
  SKLID *battleskill;
  sdatPlayerUnitWork_t *player;

  v2 = NewSpecific(s32, 3u);
  v2[4] = 0x450000000DLL;
  v3 = NewSpecific(s32, 2u);
  v3[8] = 13;
  v4 = NewSpecific(s32, 2u);
  v4[8] = 10;
  v5 = NewSpecific(s32, 2u);
  v5[8] = 27;
  v6 = NewSpecific(s32, 2u);
  v6[8] = 29;
  v7 = NewSpecific(s32, 2u);
  v7[8] = 58;
  v8 = NewSpecific(int__, 6u);
  v8[4] = v2;
  v8[5] = v3;
  v8[6] = v4;
  v8[7] = v5;
  v8[8] = v6;
  v8[9] = v7;
  v9 = v8[ptn + 4];
  PlayerData = sBtlGetPlayerData();
  for (i = 17; i != 784; ++i)
  {
    v12 = i - 16;
    Itemtbl = sBtlGetItemtbl((s32)i - 16);
    if ((Itemtbl->usetype & 2) != 0 && (Itemtbl->type & 4) == 0)
    {
      *((u16 *)&PlayerData->item->obj.klass + i) = 10;
      UpdateGetList(GBWK->sortSave, v12, 1, 0);
    }
    if (v12 <= 0x2E && ((1 << v12) & 0x600000780000LL) != 0)
    {
      *((u16 *)&PlayerData->item->obj.klass + i) = 0;
      UpdateGetList(GBWK->sortSave, v12, 1, 0);
    }
  }
  v16 = 0;
  v17 = v9 + 32;
  do
  {
    v22 = *(u32 *)(v17 + 4 * v16);
    if (!v22)
      break;
    DevilData = sBtlGetDevilData(v22, -1);
    mp = DevilData->mp;
    maxmp = DevilData->maxmp;
    str = DevilData->str;
    vit = DevilData->vit;
    tec = DevilData->tec;
    luck = DevilData->luck;
    aishou = DevilData->aishou;
    v31 = PlayerData->stock_id[v16];
    v31->flag = 5;
    kuda_id = DevilData->kuda_id;
    v31->vice = 100;
    now = v31->now;
    backup = v31->backup;
    v31->raceid = kuda_id;
    v35 = *(u32 *)(v17 + 4 * v16);
    now->mp = mp;
    now->maxmp = maxmp;
    backup->mp = mp;
    backup->maxmp = maxmp;
    now->str = str;
    now->vit = vit;
    now->tec = tec;
    now->luck = luck;
    backup->str = str;
    backup->vit = vit;
    backup->tec = tec;
    backup->luck = luck;
    v31->devilid = v35;
    v31->level = DevilData->level;
    v31->seikaku = DevilData->seikaku;
    hp = DevilData->hp;
    maxhp = DevilData->maxhp;
    now->hp = hp;
    now->maxhp = maxhp;
    backup->hp = hp;
    backup->maxhp = maxhp;
    haveskill = DevilData->haveskill;
    battleskill = v31->battleskill;
    v31->haveskill[0] = haveskill[0];
    battleskill[0] = haveskill[0];
    Aisyotbl = sBtlGetAisyotbl(aishou);
    ClassCopy(v31->aisyo, Aisyotbl, 0);
    talkskill = DevilData->talkskill;
    v20 = DevilData->haveskill;
    v31->iOmoideSkillCnt = 1;
    v31->talkskill = talkskill;
    aRsvSkl = v31->aRsvSkl;
    aRsvSkl[0] = v20[1];
    aRsvSkl[1] = v20[2];
    aRsvSkl[2] = v20[3];
    sBtlSetAutoSkill_GB(v31);
    sBtlCheckStockPara(v31);
    ++v16;
    v31->now->hp = v31->now->maxhp;
  }
  while (v16 != 5);
  player = GBWK->player;
  *(u32 *)player->stack_p = 0x10000;
  player->stock_max = 20;
}

// 0x19155f0
void sBtlDebug_SetDuummyData_Cmbskl(s32 ptn) {
  sdatPlayerUnitWork_t *PlayerData;
  s64 v7;
  s32 devilID;
  DEVILDATA_WORK *DevilData;
  s16 str;
  s32 mp;
  s32 maxmp;
  s16 vit;
  s16 tec;
  s16 luck;
  s32 aishou;
  sdatUnitWork_t *v19;
  s64 v20;
  s32 hp;
  s32 maxhp;
  sdatParaWork_t *now;
  sdatParaWork_t *backup;
  SKLID *haveskill;
  SKLID *v27;
  SKLID *battleskill;
  SBTLAISYO_DATAWORK *Aisyotbl;
  SKLID *v30;
  SKLID *aRsvSkl;
  s32 v34;
  DEVILDATA_WORK *v35;
  s32 v36;
  s32 v37;
  s16 v38;
  s16 v39;
  s16 v40;
  s32 v41;
  sdatUnitWork_t *v43;
  s64 v44;
  s8 seikaku;
  sdatParaWork_t *v46;
  sdatParaWork_t *v47;
  s64 v48;
  s32 v49;
  s32 v50;
  SKLID *v51;
  SKLID *v52;
  SKLID *v53;
  SBTLAISYO_DATAWORK *v54;
  SKLID *v55;
  SKLID *v56;
  sdatPlayerUnitWork_t *player;
  il2cpp_array_size_t max_length;
  s64 v65;
  s64 v66;
  s32 v67;
  s32 v69;

  PlayerData = sBtlGetPlayerData();
  if (ptn == 3)
  {
    sBtlDebug_SetStatusflg(6, sbflg_optimenu, 1);
    sBtlDebug_SetStatusflg(7, sbflg_optimenu, 1);
  }
  v7 = ptn;
  devilID = gDbg_Spirit_Table[ptn]->devilID;
  DevilData = sBtlGetDevilData(devilID, -1);
  str = DevilData->str;
  mp = DevilData->mp;
  maxmp = DevilData->maxmp;
  vit = DevilData->vit;
  tec = DevilData->tec;
  luck = DevilData->luck;
  aishou = DevilData->aishou;
  v19 = PlayerData->stock_id[0];
  v19->flag = 5;
  v19->vice = 100;
  v20 = (s64)gDbg_Spirit_Table + 8 * ptn;
  v19->raceid = DevilData->kuda_id;
  v19->level = DevilData->level;
  v19->seikaku = DevilData->seikaku;
  hp = DevilData->hp;
  maxhp = DevilData->maxhp;
  v19->devilid = *(u32 *)(*(u64 *)(v20 + 32) + 16);
  now = v19->now;
  backup = v19->backup;
  now->hp = hp;
  now->maxhp = maxhp;
  now->mp = mp;
  now->maxmp = maxmp;
  now->str = str;
  now->vit = vit;
  now->tec = tec;
  now->luck = luck;
  haveskill = DevilData->haveskill;
  backup->hp = hp;
  backup->maxhp = maxhp;
  backup->mp = mp;
  backup->maxmp = maxmp;
  v27 = v19->haveskill;
  battleskill = v19->battleskill;
  backup->str = str;
  backup->vit = vit;
  backup->tec = tec;
  backup->luck = luck;
  v27[0] = haveskill[0];
  battleskill[0] = haveskill[0];
  Aisyotbl = sBtlGetAisyotbl(aishou);
  ClassCopy(v19->aisyo, Aisyotbl, 0);
  v30 = DevilData->haveskill;
  v19->talkskill = DevilData->talkskill;
  aRsvSkl = v19->aRsvSkl;
  aRsvSkl[0] = v30[1];
  aRsvSkl[1] = v30[2];
  aRsvSkl[2] = v30[3];
  v19->iOmoideSkillCnt = 1;
  sBtlSetAutoSkill_GB(v19);
  wk->sprit_waza = 4000;
  sbtldbwk->y_status |= 0x200u;
  sBtlCheckStockPara(v19);
  v19->now->hp = v19->now->maxhp;
  if (ptn == 3)
  {
    v34 = gDbg_Spirit_Table[3]->devilID;
    v35 = sBtlGetDevilData(v34, -1);
    v36 = v35->mp;
    v37 = v35->maxmp;
    v38 = v35->str;
    v39 = v35->vit;
    v40 = v35->tec;
    v41 = v35->aishou;
    v43 = PlayerData->stock_id[1];
    v43->flag = 5;
    v43->vice = 100;
    v44 = (s64)gDbg_Spirit_Table + 8 * v7;
    v43->raceid = v35->kuda_id;
    seikaku = v35->seikaku;
    v43->level = v35->level;
    v43->seikaku = seikaku;
    v46 = v43->now;
    v47 = v43->backup;
    v46->mp = v36;
    v46->maxmp = v37;
    v47->mp = v36;
    v47->maxmp = v37;
    v46->str = v38;
    v46->vit = v39;
    v46->tec = v40;
    v47->str = v38;
    v47->vit = v39;
    v47->tec = v40;
    v48 = *(u64 *)(v44 + 32);
    v49 = v35->hp;
    v50 = v35->maxhp;
    v46->hp = v49;
    v46->maxhp = v50;
    v47->hp = v49;
    v47->maxhp = v50;
    v51 = v43->haveskill;
    v52 = v43->battleskill;
    v43->devilid = *(u32 *)(v48 + 16);
    LOWORD(v48) = v35->luck;
    v46->luck = v48;
    v47->luck = v48;
    v53 = v35->haveskill;
    v51[0] = v53[0];
    v52[0] = v53[0];
    v54 = sBtlGetAisyotbl(v41);
    ClassCopy(v43->aisyo, v54, 0);
    v55 = v35->haveskill;
    v43->talkskill = v35->talkskill;
    v56 = v43->aRsvSkl;
    v56[0] = v55[1];
    v56[1] = v55[2];
    v56[2] = v55[3];
    v43->iOmoideSkillCnt = 1;
    sBtlSetAutoSkill_GB(v43);
    wk->sprit_waza = 4000;
    sbtldbwk->y_status |= 0x200u;
    sBtlCheckStockPara(v43);
    v43->now->hp = v43->now->maxhp;
  }
  player = GBWK->player;
  *(u32 *)player->stack_p = 0x10000;
  player->stock_max = 20;
  wk->ChkNG_TutoEtc_AllOk = 1;
  GBWK->EventBit[65] |= 0x2000u;
  max_length = raidouSkillList->max_length;
  if ((s64)(max_length << 32) < 1)
    return;
  v65 = 0;
  v66 = (s32)max_length;
  v67 = 1;
  do
  {
    v69 = raidouSkillList[v65];
    datRaidouSkillSetMaster(PlayerData, v69, 1);
    v65 = v67++;
  }
  while (v66 > v65);
}

// 0x193bf10
void sBtlDebug_DrawHPGauge(SBTLUNIT_WORK *wk) {
  sdatParaWork_t *now;
  s32 maxhp;
  f32 v7;
  bool v8;
  s32 oldhp;
  f32 v10;
  f32 v11;
  s32 v13;
  unsigned __int128 v14;

  v14 = 0u;
  sBtlGetUnitHelperPos(wk, 2);
  sBtlChangeWorldtoScreen(&v14);
  now = wk->para->now;
  maxhp = now->maxhp;
  LODWORD(now) = now->hp;
  v7 = (s32)now;
  v8 = (s32)now < 1;
  oldhp = wk->oldhp;
  v10 = (f32)(v7 / (f32)maxhp) * 32.0;
  if (v8)
    v11 = v10;
  else
    v11 = 1.0;
  if (v10 < 1.0)
    v10 = v11;
  if (oldhp)
  {
    if (v10 >= (f32)oldhp)
    {
      return;
    }
    wk->oldhp = oldhp - 1;
  }
  else
  {
    v13 = v10;
    if (v10 == INFINITY)
      v13 = 0x80000000;
    wk->oldhp = v13;
  }
}

// 0x193c100
bool sBtlDebug_DrawCmndPara(void) {
  return 1;
}

// 0x1909e20
void sBtlDebug_DrawTCursor(const sdfVector4_t *pos, u32 rgba) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  u32 *v8;
  f32 *p_x;
  SBTLPANEL_WORK *panelwk;
  sprHandle_t *hPanelSpr4;
  s64 v15;
  s32 v16;
  s32 v17;
  s32 v18;
  s32 v19;
  unsigned __int128 v20;
  sdfVector4_t v21;

  w = pos->w;
  z = pos->z;
  y = pos->y;
  x = pos->x;
  v20 = 0u;
  v8 = NewSpecific(uint, 4u);
  InitializeArray_55364416(v8, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__25BEACE7A13A438533354F82FEA727E3FD55D0D0B4C0BF318773079368F580A6, 0);
  p_x = &vf00.x;
  p_x[4] = x;
  p_x[5] = y;
  p_x[6] = z;
  p_x[7] = w;
  sBtlChangeWorldtoScreenUnity(&v20);
  *(float32x2_t *)&v20 = vadd_f32(*(float32x2_t *)&v20, (float32x2_t)0xC2400000C1900000LL);
  *(int32x4_t *)&v8[0] = vdupq_n_s32(rgba);
  panelwk = wk->panelwk;
  if (panelwk)
  {
    panelwk = wk->panelwk;
    hPanelSpr4 = panelwk->hPanelSpr4;
    if (hPanelSpr4)
    {
      v15 = v20;
      hPanelSpr4 = wk->panelwk->hPanelSpr4;
      if (*(f32 *)&v15 == INFINITY)
        v16 = 0x80000000;
      else
        v16 = *(f32 *)&v15;
      if (*((f32 *)&v15 + 1) == INFINITY)
        v17 = 0x80000000;
      else
        v17 = *((f32 *)&v15 + 1);
      sBtlDrawSprite_RGBA2(v16, v17, v8, hPanelSpr4, 0, 44);
      if (*(f32 *)&v20 == INFINITY)
        v18 = 0x80000000;
      else
        v18 = *(f32 *)&v20;
      if (*((f32 *)&v20 + 1) == INFINITY)
        v19 = 0x80000000;
      else
        v19 = *((f32 *)&v20 + 1);
      sBtlDrawSprite_RGBA2(v18, v19, v8, wk->panelwk->hPanelSpr4, 1, 44);
    }
  }
  *(int8x8_t *)&v21.x = vbsl_s8(vceq_f32(*(float32x2_t *)&v20, vdup_n_s32(0x7F800000u)), (int8x8_t)0xCF000000CF000000LL, vcvt_f32_s32(vcvt_s32_f32(*(float32x2_t *)&v20)));
  v21.z = 0.0;
  v21.w = 0.0;
  TargetCursorDrawUnity(wk->bsc, v21, 0);
}

// 0x193c110
bool sBtlDebug_CheckDebugFlg(SBDEBUG_FLG flg, SBDEBUG_FLGTYPE sw) {
  if (!sbtldbwk)
    return 0;
  switch (sw)
  {
    case 11:
      if ((sbtldbwk->y_status & flg) == 0)
        return 0;
      return 1;
    case 2:
      if ((sbtldbwk->unitst & flg) == 0)
        return 0;
      return 1;
    case 1:
      return (sbtldbwk->status & flg) != 0;
  }
  return 0;
}

// 0x193c290
s32 sbattleGetEnemyStopMode(void) {
  return sbtldbwk->enemy_stop_mode;
}

// 0x190b680
bool sbattleDrawUnitChangeList(s32 x, s32 y) {
  SBDEBUG_CSRWORK *unitcsr;
  s32 point;
  bool v10;
  s32 v11;
  s32 offset;
  s32 v13;
  s32 v14;
  s32 v15;
  s32 v16;
  s32 v17;
  s32 v18;
  s32 v19;
  u32 v20;
  Il2CppObject *v21;
  char *v22;
  u32 v25;
  u32 v27;
  s32 v28;
  s32 v29;
  u32 v30;
  s32 v31;
  s32 unitmode;
  s32 data;

  unitcsr = sbtldbwk->unitcsr;
  sbattleGetUnit(sbtldbwk->mdlslcsr->point);
  unitmode = sbtldbwk->unitmode;
  if (!unitmode)
  {
    point = unitcsr->point;
    v10 = __OFSUB__(point, 32);
    v11 = point - 32;
    if (v11 < 0 != v10)
      offset = 0;
    else
      offset = v11;
    unitcsr->offset = offset;
    offset = unitcsr->offset;
    v13 = 0;
    v14 = x + 16;
    v15 = 10 * x + 480;
    v16 = 12 * y;
    v17 = 48;
    do
    {
      while (1)
      {
        v31 = offset + v13;
        if (offset + v13 >= unitcsr->maxp)
          return unitmode == 0;
        data = v13 + unitcsr->offset;
        v21 = Box(s32, &data);
        v22 = Format("{0,1:x3}", v21, 0);
        if (v13 != unitcsr->point - unitcsr->offset)
          break;
        DbgText(v14, v17, v22, 1692838528, 109, 24, 0);
        if (!sbtldbwk->unitmajor)
        {
          if (!v25)
          v28 = v15;
          v29 = v17;
          v30 = 1692838528;
          goto LABEL_41;
        }
        if (!v25)
        v18 = v15;
        v19 = v17;
        v20 = 1692838528;
LABEL_13:
        sBtlDrawDevilName(v18, v19, 0, v20, v31);
        ++v13;
        v17 += v16;
        if (v13 == 34)
          return unitmode == 0;
      }
      DbgText(v14, v17, v22, -1600273536, 109, 24, 0);
      if (sbtldbwk->unitmajor)
      {
        if (!v27)
        v18 = v15;
        v19 = v17;
        v20 = -1600273536;
        goto LABEL_13;
      }
      if (!v27)
      v28 = v15;
      v29 = v17;
      v30 = -1600273536;
LABEL_41:
      sBtlDrawPlayerName(v28, v29, 0, v30, v31);
      ++v13;
      v17 += v16;
    }
    while (v13 != 34);
  }
  return unitmode == 0;
}

// 0x1931090
char *sBtlDebug_GetDebugMenuFont(s32 id) {
  return sblist_modelmenu[id];
}

// 0x19311d0
char *sbattleGetDebugMenuFontCamera(s32 id) {
  f32 v2;
  char *v6;
  char *p_sensitivityX;
  char **v11;
  char *v15;
  char *v18;
  char *v20;
  char **v21;
  char *v22;
  f32 v24;
  f32 downMaxAngleY;
  char *p_format;
  char *v31;
  f32 v32;
  System_String_o format;

  format.klass = 0;
  switch (id)
  {
    case 0:
      p_targetPosY = &battleCameraPar->targetPosY;
      goto LABEL_24;
    case 1:
      p_targetPosY = &battleCameraPar->length;
      goto LABEL_24;
    case 2:
      p_sensitivityX = &battleCameraPar->sensitivityX;
      v11 = &"f2";
      goto LABEL_47;
    case 3:
      p_sensitivityX = &battleCameraPar->sensitivityY;
      v11 = &"f2";
      goto LABEL_47;
    case 4:
      p_targetPosY = &battleCameraPar->upMaxAngleY;
      goto LABEL_24;
    case 5:
      p_targetPosY = &battleCameraPar->downMaxAngleY;
LABEL_24:
      v15 = ToString(v2);
      goto LABEL_48;
    case 6:
      p_sensitivityX = &battleCameraPar->fov;
      v11 = &"f2";
      goto LABEL_47;
    case 7:
      v18 = ToString_56097616(v2, &battleCameraPar->initRotX, "f2");
      LODWORD(format.klass) = sub_188E3E0(wk->scene->camera->followUpAngle.x);
      v20 = ToString_56097616(*(f32 *)&format.klass, &format, "f2");
      v21 = &" nowRotX : ";
      v22 = v18;
      goto LABEL_55;
    case 8:
      v24 = sub_188E3E0(wk->scene->camera->followUpAngle.y + 360.0);
      *((f32 *)&format.klass + 1) = v24;
      if (v24 < 0.0)
        goto LABEL_39;
      downMaxAngleY = battleCameraPar->downMaxAngleY;
      if (v24 <= downMaxAngleY)
      {
        p_format = ((char *)&format.klass + 4);
      }
      else
      {
LABEL_39:
        p_format = &format;
        downMaxAngleY = v24 + -360.0;
        *(f32 *)&format.klass = v24 + -360.0;
      }
      v31 = ToString_56097616(downMaxAngleY, p_format, "f2");
      v22 = ToString_56097616(v32, &battleCameraPar->initRotY, "f2");
      v21 = &" nowRotY : ";
      v20 = v31;
LABEL_55:
      v6 = Concat_54832128(0, v22, *v21, v20, 0);
      return Concat_54766928(sblistCameraMenu[id], v6, 0);
    case 9:
      p_sensitivityX = &battleCameraPar->sensitivityMouseX;
      goto LABEL_46;
    case 10:
      p_sensitivityX = &battleCameraPar->sensitivityMouseY;
LABEL_46:
      v11 = &"f3";
LABEL_47:
      v15 = ToString_56097616(v2, p_sensitivityX, *v11);
LABEL_48:
      v6 = Concat_54766928(0, v15, 0);
      return Concat_54766928(sblistCameraMenu[id], v6, 0);
    default:
      v6 = 0;
      return Concat_54766928(sblistCameraMenu[id], v6, 0);
  }
}

// 0x1931750
char *sbattleGetDebugMenuFontTime(s32 id) {
  char *v3;
  s32 timecount;
  char *v8;
  s32 v11;

  v11 = 0;
  if (id == 1)
  {
    timecount = wk->timecount;
    v11 = (timecount - gb_btltime) / 60;
    v3 = ToString_55996800((s32)&v11, "D2", 0);
  }
  else
  {
    if (id)
    {
      v8 = 0;
      return Concat_54766928(sblistTimeMenu[id], v8, 0);
    }
    v3 = "ON";
  }
  v8 = Concat_54766928(0, v3, 0);
  return Concat_54766928(sblistTimeMenu[id], v8, 0);
}

// 0x193bd20
SBDEBUG_FILELISTWORK *sbattleCreateFileList(void) {
  SBDEBUG_FILELISTWORK *v1;

  v1 = (SBDEBUG_FILELISTWORK *)Allocate(SBDEBUG_FILELISTWORK);
  _ctor(v1, 0);
  v1->wk = 0;
  return v1;
}

// 0x193c320
SBDEBUG_FILEWORK *sbattleCreateFile(SBDEBUG_FILELISTWORK *lwk, s32 type) {
  SBDEBUG_FILEWORK *v5;
  SBDEBUG_FILEWORK *wk;
  SBDEBUG_FILEWORK *v7;

  v5 = (SBDEBUG_FILEWORK *)Allocate(SBDEBUG_FILEWORK);
  _ctor(v5, 0);
  v5->prev = 0;
  v5->next = 0;
  v5->type = type;
  wk = lwk->wk;
  if (wk)
  {
    do
    {
      v7 = wk;
      wk = wk->next;
    }
    while (wk);
    v7->next = v5;
    v5->prev = v7;
    ++lwk->num;
    return v5;
  }
  else
  {
    lwk->wk = v5;
    lwk->num = 1;
    return v5;
  }
}

// 0x191a580
bool sbattleDeleteFileList(SBDEBUG_FILELISTWORK *lwk) {
  SBDEBUG_FILEWORK *p_wk;
  SBDEBUG_FILEWORK *wk;
  SBDEBUG_FILEWORK *prev;
  SBDEBUG_FILEWORK *v6;
  SBDEBUG_FILEWORK *next;
  SBDEBUG_FILEWORK *v8;
  SBDEBUG_FILEWORK *v9;
  SBDEBUG_FILEWORK *v10;

  p_wk = &lwk->wk;
  wk = lwk->wk;
  if (wk)
  {
    while (1)
    {
      prev = wk->prev;
      if (prev)
        break;
      v8 = 0;
      next = wk->next;
      if (next)
        goto LABEL_6;
LABEL_7:
      if (!v8)
      {
        v9 = wk->next;
        p_wk = v9;
        v10 = p_wk;
        if (p_wk)
        {
          v10->prev = 0;
        }
      }
      wk = wk->next;
      --lwk->num;
      if (!wk)
        goto LABEL_12;
    }
    v6 = wk->next;
    prev->next = v6;
    v8 = wk->prev;
    next = wk->next;
    if (!next)
      goto LABEL_7;
LABEL_6:
    next->prev = v8;
    v8 = wk->prev;
    goto LABEL_7;
  }
LABEL_12:
  p_wk = 0;
  return 1;
}

// 0x1925020
bool sbattleDrawMotionFrame(SBTLUNIT_WORK *unit, s32 motionno) {
  u16 major;
  s32 minor;
  VISUALDATA_WORK *VisualData;
  MOTIONDATA_WORK *mwk;
  Il2CppClass **v9;
  dds3ModelHandle_t *hModel;
  Il2CppClass *v11;
  f32 MotionFrame;
  f32 MotionLength;
  Il2CppObject *v14;
  char *v15;
  Il2CppObject *v16;
  char *v17;
  char *v18;
  f32 v19;
  f32 *p_byval_arg;
  f32 v21;
  Il2CppObject *v22;
  char *v23;
  Il2CppObject *v24;
  char *v25;
  char *v26;
  f32 v29;
  f32 data;

  major = unit->major;
  minor = unit->minor;
  VisualData = sBtlGetVisualData(major, minor);
  mwk = VisualData->mwk;
  v9 = &mwk->obj.klass + sbtldbwk->prev_motionno;
  hModel = unit->hModel;
  v11 = v9[4];
  MotionFrame = mdlGetMotionFrame(hModel);
  MotionLength = mdlGetMotionLength(unit->hModel);
  data = MotionFrame;
  v14 = Box(f32, &data);
  v15 = Format("FRAME   :{0,4:f1}", v14, 0);
  v29 = MotionLength;
  v16 = Box(f32, &v29);
  v17 = Format("{0,4:f1}", v16, 0);
  v18 = Concat_54832128(0, v15, "/", v17, 0);
  DbgText(224, 2560, v18, 0, 109, 24, 0);
  v19 = mdlGetMotionFrame(unit->hModel);
  if ((motion_flg[0] & (s64)v11->_1.name) != 0)
    p_byval_arg = &v11->_1.byval_arg;
  else
    p_byval_arg = &VisualData->m_speed;
  v21 = v19 / *p_byval_arg;
  data = v19 / (f32)(*p_byval_arg + *p_byval_arg);
  v22 = Box(f32, &data);
  v23 = Format("FRAME   :{0,4:f1}", v22, 0);
  v29 = v21;
  v24 = Box(f32, &v29);
  v25 = Format("{0,4:f1}", v24, 0);
  v26 = Concat_54832128(v18, v23, "/", v25, 0);
  DbgText(224, 2816, v26, 0, 109, 24, 0);
  return 1;
}

// 0x1924340
bool sbattleMDLHitEditor_DrawMotion(SBDEBUG_CSRWORK *wk, SBTLSKILLHIT_TBL *hwk, s32 nowp) {
  SBTLUNIT_LISTWORK *UnitMng;
  s32 acterID;
  SBTLUNIT_WORK *v13;
  char **p_motion_tbl_new;
  u16 major;
  s32 minor;
  VISUALDATA_WORK *VisualData;
  MOTIONDATA_WORK *v22;
  dds3ModelHandle_t *hModel;
  f32 MotionFrame;
  f32 MotionLength;
  Il2CppObject *v26;
  char *v27;
  Il2CppObject *v28;
  char *v29;
  char *v30;
  f32 v31;
  f32 *p_m_speed;
  f32 v33;
  Il2CppObject *v34;
  char *v35;
  Il2CppObject *v36;
  char *v37;
  char *v38;
  f32 v41;
  f32 data;

  if (sbtldbwk->acterID == -1)
    return 1;
  UnitMng = wk->UnitMng;
  acterID = sbtldbwk->acterID;
  v13 = sBtlSearchUnit_ID(UnitMng, acterID);
  sBtlDebug_DrawNormalList_Col(sblist_mdlhitmenu_edit_para03, 1, wk->point - nowp, -1, 14, 230);
  if (v13->major)
  {
    p_motion_tbl_new = &motion_tbl_new;
  }
  else
  {
    p_motion_tbl_new = &motion_tbl_player;
  }
  sbattleDrawString(160, 228, (*p_motion_tbl_new)[hwk->motionno], wk->point - nowp, 0);
  major = v13->major;
  minor = v13->minor;
  VisualData = sBtlGetVisualData(major, minor);
  v22 = VisualData->mwk[hwk->motionno];
  hModel = v13->hModel;
  MotionFrame = mdlGetMotionFrame(hModel);
  MotionLength = mdlGetMotionLength(v13->hModel);
  data = MotionFrame;
  v26 = Box(f32, &data);
  v27 = Format("FRAME   :{0,4:f1}", v26, 0);
  v41 = MotionLength;
  v28 = Box(f32, &v41);
  v29 = Format("{0,4:f1}", v28, 0);
  v30 = Concat_54832128(0, v27, "/", v29, 0);
  DbgText(224, 2448, v30, 0, 109, 24, 0);
  v31 = mdlGetMotionFrame(v13->hModel);
  if ((motion_flg[0] & v22->flg) != 0)
    p_m_speed = &v22->m_speed;
  else
    p_m_speed = &VisualData->m_speed;
  v33 = v31 / *p_m_speed;
  data = v31 / (f32)(*p_m_speed + *p_m_speed);
  v34 = Box(f32, &data);
  v35 = Format("FRAME   :{0,4:f1}", v34, 0);
  v41 = v33;
  v36 = Box(f32, &v41);
  v37 = Format("{0,4:f1}", v36, 0);
  v38 = Concat_54832128(v30, v35, "/", v37, 0);
  DbgText(224, 2576, v38, 0, 109, 24, 0);
  return 1;
}

// 0x1923280
bool sBtlDebug_EPLParaDraw(SBDEBUG_CSRWORK *wk, SBTLSKILLHIT_TBL *hwk, SBTLSKILLHIT_POSWORK *para, SBTLSKILLIDOU_WORK *iwk, s32 point) {
  char *v11;
  char **static_fields;
  f32 *v13;
  f32 v16;
  s32 v17;
  f32 v19;
  s32 v20;
  f32 v22;
  s32 v23;
  f32 v25;
  s32 v26;

  if ((hwk->flg & 0x100) != 0)
  {
    v11 = "     >>";
    v13 = *((f32 **)&(*static_fields)[45][1].monitor + (*static_fields)[25]->_stringLength);
    sBtlDebug_DrawNormalList_Col(static_fields[96], 5, wk->point - point, 0, 14, 282);
    sbattleDrawString(160, 280, v11, wk->point, point);
    v16 = v13[5];
    if (v16 == INFINITY)
      v17 = 0x80000000;
    else
      v17 = v16;
    sbattleDrawInt_Num(182, 292, v17, wk->point, point + 1);
    v19 = v13[6];
    if (v19 == INFINITY)
      v20 = 0x80000000;
    else
      v20 = v19;
    sbattleDrawInt_Num(182, 304, v20, wk->point, point + 2);
    v22 = v13[7];
    if (v22 == INFINITY)
      v23 = 0x80000000;
    else
      v23 = v22;
    sbattleDrawInt_Num(182, 316, v23, wk->point, point + 3);
    v25 = v13[8];
    if (v25 == INFINITY)
      v26 = 0x80000000;
    else
      v26 = v25;
    sbattleDrawInt_Num(182, 328, v26, wk->point, point + 4);
  }
  return 1;
}

// 0x1923410
bool sBtlDebug_MoveTypeDraw(SBDEBUG_CSRWORK *wk, SBTLSKILLHIT_TBL *hwk, SBTLSKILLHIT_POSWORK *para, SBTLSKILLIDOU_WORK *iwk, SBDEBUG_PATHDATA *path, s32 point) {
  char *v12;
  char *v13;
  s32 v15;
  s32 v18;
  dds3ModelHandle_t *path_hModel;
  s32 MotionFrame;
  s32 MotionLength;
  f32 v23;
  f32 v25;

  if ((hwk->flg & 0x100) != 0)
  {
    v12 = "     >>";
    v13 = "   /";
    sBtlDebug_DrawNormalList_Col(sblist_efhitmenu_edit_para03, 1, wk->point - point, 0, 14, 354);
    sbattleDrawString(160, 352, v12, wk->point, point);
    v15 = point + 1;
    sbattleDrawString(14, 368, sblist_efhitmenu_edit_para03_0[path->nef_movetype], wk->point, v15);
    if (path->nef_movetype == 1)
    {
      v18 = wk->point;
      sbattleDrawString(160, 364, v12, v18, v15);
      if (path->path_pBasic)
      {
        path_hModel = path->path_hModel;
        MotionFrame = mdlGetMotionFrame(path_hModel);
        MotionLength = mdlGetMotionLength(path->path_hModel);
        v23 = MotionFrame;
        v25 = MotionLength;
        DbgText(2048, 3088, v13, 4, 109, 24, 0);
        sbattleDrawFloat_Num(96, 386, v23, 0, 0);
        sbattleDrawFloat_Num(192, 386, v25, 0, 0);
        return 1;
      }
    }
  }
  return 1;
}

// 0x193c430
bool sbattleEPLDraw(SBDEBUG_CSRWORK *wk, SBTLSKILLHIT_TBL *hwk, const sdfVector4_t *poss, const sdfVector4_t *rott) {
  f32 w;
  f32 z;
  f32 y;
  f32 x;
  f32 v9;
  f32 v10;
  f32 v11;
  f32 v12;
  s64 point;
  SBTLEFF_DATAWORK *v16;
  void *hPartsList;
  SBDEBUG_TIMEWORK *ef_dt;
  f32 *v19;
  f32 *v20;
  f32 v21;
  f32 v22;
  f32 v23;
  f32 v24;
  f32 v25;
  f32 v26;
  f32 v27;
  u32 v28;
  sdfVector4_t v30;
  sdfVector4_t v31;

  w = rott->w;
  z = rott->z;
  y = rott->y;
  x = rott->x;
  v9 = poss->w;
  v10 = poss->z;
  v11 = poss->y;
  v12 = poss->x;
  point = sbtldbwk->nef_pagecsr->point;
  v16 = sbtldbwk->ef_dwk[point];
  hPartsList = v16->hPartsList;
  if (hPartsList)
  {
    ef_dt = sbtldbwk->ef_dt;
    v19 = sbtldbwk->ef_dtime[point];
    v20 = ef_dt[point];
    v21 = v19[5];
    v22 = v19[4] + 1.0;
    if (v22 >= 32767.0)
      v22 = 32767.0;
    v19[4] = v22;
    if (v22 >= v21)
    {
      v23 = v19[6];
      if (v23 == 0.0 || v22 <= (f32)(v21 + v23))
      {
        v24 = v22 - v21;
        if (v24 >= 0.0 && v24 <= v19[7])
        {
          v25 = v20[5] + v20[4];
          v20[5] = v25;
          if (v25 >= 80.0)
            v20[5] = 80.0;
        }
        if (v23 != 0.0 && (f32)(v23 - v19[8]) <= v22)
        {
          v26 = v20[5] - v20[6];
          v20[5] = v26;
          if (v26 <= 0.0)
            v20[5] = 0.0;
        }
        v27 = v20[5];
        if (v27 == INFINITY)
          v28 = 8421504;
        else
          v28 = ((s32)v27 << 24) | 0x808080;
        effPartsColorSet(hPartsList, v28);
        v30.x = x;
        v30.y = y;
        v30.z = z;
        v30.w = w;
        effPartsRotateSet(v16->hPartsList, v30);
        effPartsScaleSet(v16->hPartsList, 1.0);
        v31.x = v12;
        v31.y = v11;
        v31.z = v10;
        v31.w = v9;
        effPartsPositionSet(v16->hPartsList, v31);
        effPartsDraw(v16->hPartsList);
      }
    }
  }
  return 1;
}

// 0x193c630
bool sbattleDrawPoseture(SBDEBUG_CSRWORK *wk, SBTLSKILLHIT_TBL *hwk, const sdfVector4_t *pose) {
  f32 z;
  f32 y;
  f32 x;
  float32x2_t v9;
  f32 v10;
  float32x2_t v13;
  f32 v14;
  float32x2_t *static_fields;
  f32 *p_x;
  f32 v19;
  f32 v20;
  f32 v21;
  f32 *v22;
  f32 v23;
  f32 v24;
  f32 v25;
  f32 *v27;
  f32 v28;
  f32 v29;
  f32 v30;
  f32 v32;
  u32 v33;
  sdfMatrix4_t v38;
  sdfMatrix4_t v39;
  sdfVector4_t v40;

  z = pose->z;
  y = pose->y;
  x = pose->x;
  v9.n64_u64[0] = *(u64 *)&hwk->x;
  v10 = hwk->z;
  vct_A = (struct sdfVector4_t)xmmword_3CFD5C0;
  ToMatrix();
  v13.n64_u64[0] = vadd_f32(v9, 0).n64_u64[0];
  v14 = v10 + 0.0;
  static_fields[2].n64_u64[0] = v13.n64_u64[0];
  static_fields[3].n64_f32[0] = v14;
  static_fields[3].n64_u32[1] = 1065353216;
  get_transpose(&v39, &mtx_A, 0);
  v38 = v39;
  v40 = op_Multiply_60923920(&v38, vct_A, 0);
  vct_A = v40;
  p_x = &vf00.x;
  v20 = p_x[4];
  v19 = p_x[5];
  v21 = p_x[6];
  v22 = &vf00.x;
  v22[4] = v20;
  v22[5] = 0.0;
  v22[6] = v21;
  v22[7] = 1.0;
  v23 = x + 0.0;
  v24 = y + 0.0;
  v25 = z + 0.0;
  vct_B.x = v23;
  vct_B.y = v24;
  vct_B.z = v25;
  vct_B.w = 1.0;
  vct_A = (struct sdfVector4_t)vsubq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
  v27 = &vf00.x;
  v28 = v27[6];
  v29 = v27[4];
  v30 = v27[5];
  v32 = sqrtf((f32)((f32)(v29 * v29) + (f32)(v30 * v30)) + (f32)(v28 * v28));
  v33 = sBtlDebug_DrawClrcle_Line(v23, v24, v25, v32, (u32)sbattle);
  sBtlDebug_DrawClrcle_Line(v23, v19, v25, v32, v33);
  return 1;
}

// 0x193cab0
bool sBtlDebug_DrawClrcle_Line(f32 x, f32 y, f32 z, f32 r, u32 rgba) {
  f32 v12;
  f32 w;
  _OWORD *p_x;
  f32 v15;
  f32 v16;
  s32 v17;
  f32 *v19;
  u32 v20;
  __int128 v21;
  _OWORD *v22;
  s32 v23;
  __int128 v24;
  SBTLDEBUG_WORK *sbtldbwk_local;
  __int128 v30;
  __int128 v31;
  __int128 v33;
  _OWORD *v34;
  s32 v35;
  __int128 v36;
  f32 *v37;
  u32 v39;
  __int128 v40;
  _OWORD *v41;
  s32 v42;
  __int128 v43;
  SBTLDEBUG_WORK *v46;
  __int128 v48;
  __int128 v49;
  __int128 v51;
  _OWORD *v52;
  s32 v53;
  __int128 v54;
  f32 *v56;
  u32 v57;
  __int128 v58;
  _OWORD *v59;
  s32 v60;
  __int128 v61;
  struct sdfVector4_t v70;
  __int128 v72;
  __int128 v73;
  __int128 v74;
  __int128 v75;
  sdfMatrix4_t v76;
  sdfMatrix4_t v77;
  sdfVector4_t v78;
  sdfVector4_t v79;
  sdfVector4_t v80;
  sdfVector4_t v81;
  sdfVector4_t v82;
  sdfVector4_t v84;
  sdfVector4_t v85;
  sdfVector4_t v86;
  sdfVector4_t v87;

  sub_1949280(0, 0.0);
  v12 = -1.0;
  w = 0.0;
  p_x = &vf00.x;
  v15 = 0.0;
  v16 = 0.0;
  v17 = 12;
  v72 = p_x[4];
  v73 = p_x[5];
  v74 = p_x[6];
  v75 = p_x[7];
  do
  {
    v19 = &vf00.x;
    v19[4] = v16;
    v19[5] = v15;
    v19[6] = v12;
    v19[7] = w;
    *(_OWORD *)&v77.m00 = v72;
    *(_OWORD *)&v77.m01 = v73;
    *(_OWORD *)&v77.m02 = v74;
    *(_OWORD *)&v77.m03 = v75;
    if (v20)
    v21 = *(_OWORD *)&v77.m01;
    v22 = &vf00.x;
    v23 = (u8)byte_5756085;
    v22[4] = *(_OWORD *)&v77.m00;
    v22[5] = v21;
    v24 = *(_OWORD *)&v77.m03;
    v22[6] = *(_OWORD *)&v77.m02;
    v22[7] = v24;
    if (v23)
    {
      goto LABEL_15;
    }
    else
    {
      goto LABEL_15;
    }
LABEL_15:
    get_transpose(&v77, &mtx_A, 0);
    v76 = v77;
    v78 = op_Multiply_60923920(&v76, vct_A, 0);
    vct_A = v78;
    vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, r);
    vct_B.x = x;
    vct_B.y = y;
    vct_B.z = z;
    vct_B.w = 1.0;
    vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    sbtldbwk_local = sbtldbwk;
    v30 = *(_OWORD *)&sbtldbwk_local->mat.m01;
    *(_OWORD *)&v77.m00 = *(_OWORD *)&sbtldbwk_local->mat.m00;
    *(_OWORD *)&v77.m01 = v30;
    v31 = *(_OWORD *)&sbtldbwk_local->mat.m03;
    *(_OWORD *)&v77.m02 = *(_OWORD *)&sbtldbwk_local->mat.m02;
    *(_OWORD *)&v77.m03 = v31;
    v33 = *(_OWORD *)&v77.m01;
    v34 = &vf00.x;
    v35 = (u8)byte_5755EF5;
    v34[4] = *(_OWORD *)&v77.m00;
    v34[5] = v33;
    v36 = *(_OWORD *)&v77.m03;
    v34[6] = *(_OWORD *)&v77.m02;
    v34[7] = v36;
    if (v35)
    {
      goto LABEL_29;
    }
    else
    {
LABEL_29:
      v37 = &vf00.x;
      v37[4] = v16;
      v37[5] = v15;
      v37[6] = v12;
      v37[7] = w;
      goto LABEL_30;
    }
    vct_A.x = v16;
    vct_A.y = v15;
    vct_A.z = v12;
    vct_A.w = w;
LABEL_30:
    get_transpose(&v77, &mtx_A, 0);
    v84 = vct_A;
    v76 = v77;
    v79 = op_Multiply_60923920(&v76, v84, 0);
    vct_A = v79;
    v70 = vct_A;
    *(_OWORD *)&v77.m00 = v72;
    *(_OWORD *)&v77.m01 = v73;
    *(_OWORD *)&v77.m02 = v74;
    *(_OWORD *)&v77.m03 = v75;
    if (v39)
    v40 = *(_OWORD *)&v77.m01;
    v41 = &vf00.x;
    v42 = (u8)byte_5756085;
    v41[4] = *(_OWORD *)&v77.m00;
    v41[5] = v40;
    v43 = *(_OWORD *)&v77.m03;
    v41[6] = *(_OWORD *)&v77.m02;
    v41[7] = v43;
    if (v42)
    {
      goto LABEL_37;
    }
    else
    {
      goto LABEL_37;
    }
LABEL_37:
    get_transpose(&v77, &mtx_A, 0);
    v85 = vct_A;
    v76 = v77;
    v80 = op_Multiply_60923920(&v76, v85, 0);
    vct_A = v80;
    vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, r);
    vct_B.x = x;
    vct_B.y = y;
    vct_B.z = z;
    vct_B.w = 1.0;
    vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    v46 = sbtldbwk;
    v48 = *(_OWORD *)&v46->mat.m01;
    *(_OWORD *)&v77.m00 = *(_OWORD *)&v46->mat.m00;
    *(_OWORD *)&v77.m01 = v48;
    v49 = *(_OWORD *)&v46->mat.m03;
    *(_OWORD *)&v77.m02 = *(_OWORD *)&v46->mat.m02;
    *(_OWORD *)&v77.m03 = v49;
    v51 = *(_OWORD *)&v77.m01;
    v52 = &vf00.x;
    v53 = (u8)byte_5755EF5;
    v52[4] = *(_OWORD *)&v77.m00;
    v52[5] = v51;
    v54 = *(_OWORD *)&v77.m03;
    v52[6] = *(_OWORD *)&v77.m02;
    v52[7] = v54;
    if (v53)
    {
      goto LABEL_50;
    }
    else
    {
LABEL_50:
      vct_A = v70;
      goto LABEL_51;
    }
    vct_A = v70;
LABEL_51:
    get_transpose(&v77, &mtx_A, 0);
    v86 = vct_A;
    v76 = v77;
    v81 = op_Multiply_60923920(&v76, v86, 0);
    vct_A = v81;
    v56 = &vf00.x;
    v16 = v56[4];
    v15 = v56[5];
    v12 = v56[6];
    w = v56[7];
    *(_OWORD *)&v77.m00 = v72;
    *(_OWORD *)&v77.m01 = v73;
    *(_OWORD *)&v77.m02 = v74;
    *(_OWORD *)&v77.m03 = v75;
    if (v57)
    v58 = *(_OWORD *)&v77.m01;
    v59 = &vf00.x;
    v60 = (u8)byte_5756085;
    v59[4] = *(_OWORD *)&v77.m00;
    v59[5] = v58;
    v61 = *(_OWORD *)&v77.m03;
    v59[6] = *(_OWORD *)&v77.m02;
    v59[7] = v61;
    if (v60)
    {
      goto LABEL_58;
    }
    else
    {
      goto LABEL_58;
    }
LABEL_58:
    get_transpose(&v77, &mtx_A, 0);
    v87 = vct_A;
    v76 = v77;
    v82 = op_Multiply_60923920(&v76, v87, 0);
    vct_A = v82;
    vct_A = (struct sdfVector4_t)vmulq_n_f32((float32x4_t)vct_A, r);
    vct_B.x = x;
    vct_B.y = y;
    vct_B.z = z;
    vct_B.w = 1.0;
    vct_A = (struct sdfVector4_t)vaddq_f32((float32x4_t)vct_A, (float32x4_t)vct_B);
    --v17;
  }
  while (v17);
  return 1;
}

// 0x1908770
SBTLUNIT_WORK *sbattleGetUnit(s32 point) {
  SBTLUNIT_WORK *wk_local;
  s64 v6;
  s32 v7;
  SBTLUNIT_LISTWORK *UnitMng;

  wk_local = (SBTLUNIT_WORK *)wk;
  if (!wk_local)
    return wk_local;
  wk_local = *(SBTLUNIT_WORK *)&wk_local->GroupID;
  if (!wk_local)
    return wk_local;
  v6 = 0;
  v7 = 0;
  while (1)
  {
    UnitMng = wk->UnitMng;
    if (v6 >= UnitMng->number)
      return 0;
    wk_local = UnitMng->pUnitL[v6]->pUnit;
    if (wk_local)
    {
      if ((wk_local->side & 7) != 0)
      {
        if (v7 == point)
          return wk_local;
        ++v7;
      }
    }
    ++v6;
  }
}

// 0x193d6a0
dds3ProcessFunc_t sbattleProcCamera(dds3ProcessID_t *id) {
  return 0;
}

// 0x193d6b0
dds3ProcessFunc_t sBtlDebug_Proc(dds3ProcessID_t *id) {
  sbdebug_procmenuDelegate v5;

  IconDraw = 1;
  v5 = sbdebug_procmenu[sbtldbwk->mode];
  (v5->invoke_impl)(v5->method_code, id, v5->method);
  if (sbtldbwk->mode)
  {
    IconDraw = 0;
  }
  sBtlDebug_CheckLoadEncountData();
  return 0;
}

// 0x1921080
bool sBtlDebug_LoadMotionMoveData(void) {
  SBTLUNIT_LISTWORK *UnitMng;
  s32 acterID;
  SBTLUNIT_WORK *v6;
  u16 major;
  s32 minor;
  MOTIONMOVE_WORK *MotionMoveData;
  MTIONMV_PARA *para;
  MOTIONMOVE_WORK *v12;
  s32 v14;
  s32 v15;
  bool v16;
  MTIONMV_PARA *v17;
  MTIONMV_PARA *v18;
  s32 motionno;
  s32 v21;
  s64 v22;
  SBDEBUG_CSRWORK *nef_pagecsr;
  SBDEBUG_CSRWORK *nef_selmenucsr;
  s64 v26;
  char *v27;
  s16 *v28;
  f32 v29;
  s32 v30;
  char *v31;
  s64 v32;
  SBTLDEBUG_WORK *v33;
  u32 v34;
  SBDEBUG_CSRWORK *effhitcsr;
  s32 v36;
  char **p_filename;
  SBTLDEBUG_WORK *v70;

  UnitMng = wk->UnitMng;
  acterID = sbtldbwk->acterID;
  v6 = sBtlSearchUnit_ID(UnitMng, acterID);
  major = v6->major;
  minor = v6->minor;
  MotionMoveData = sBtlGetMotionMoveData(major, minor);
  para = MotionMoveData->para;
  v12 = MotionMoveData;
  v14 = para[1]->motionno != -1;
  if (para[0]->motionno != -1)
    ++v14;
  if (para[2]->motionno == -1)
    v15 = v14;
  else
    v15 = v14 + 1;
  if (para[3]->motionno != -1)
    ++v15;
  if (para[4]->motionno != -1)
    ++v15;
  if (para[5]->motionno != -1)
    ++v15;
  if (para[6]->motionno != -1)
    ++v15;
  v16 = para[7]->motionno == -1;
  v18 = para[8];
  v17 = para[9];
  if (!v16)
    ++v15;
  motionno = v17->motionno;
  if (v18->motionno != -1)
    ++v15;
  v16 = motionno == -1;
  if (v16)
    v21 = v15;
  else
    v21 = v15 + 1;
  if (v21)
  {
    v22 = 0;
    nef_pagecsr = sbtldbwk->nef_pagecsr;
    sbtldbwk->nef_nowpage = v21;
    nef_selmenucsr = sbtldbwk->nef_selmenucsr;
    nef_pagecsr->maxp = v21 + 1;
    nef_pagecsr->point = 0;
    nef_selmenucsr->point = 0;
    nef_selmenucsr->maxp = 3;
    while (1)
    {
      v33 = sbtldbwk;
      if (v22 >= v33->nef_pagecsr->maxp)
        break;
      if (!v34)
      {
        v33 = sbtldbwk;
      }
      v26 = 8 * v22;
      v27 = (char *)v33->ef_wkflg + v22++;
      v27[32] = 1;
      v28 = *(s16 **)((char *)v12->para + v26);
      v29 = v28[11];
      v30 = v28[9];
      v31 = (char *)sbtldbwk->ef_wk + v26;
      LODWORD(v26) = v28[8];
      LODWORD(v28) = v28[10] - v30;
      v32 = *(u64 *)(*((u64 *)v31 + 4) + 40);
      *(u32 *)(v32 + 120) = v26;
      *(u32 *)(v32 + 24) = v30;
      *(u32 *)(v32 + 28) = (u32)v28;
      *(f32 *)(v32 + 72) = v29;
    }
    if (!v34)
    {
      v33 = sbtldbwk;
    }
    v33->nef_mode = 9;
    effhitcsr = v33->effhitcsr;
    v36 = 4;
LABEL_44:
    effhitcsr->point = 0;
    effhitcsr->maxp = v36;
    return 1;
  }
  sbattleClearEffHitData(0);
  sbattleClearEffHitData(1);
  sbattleClearEffHitData(2);
  sbattleClearEffHitData(3);
  sbattleClearEffHitData(4);
  sbattleClearEffHitData(5);
  sbattleClearEffHitData(6);
  sbattleClearEffHitData(7);
  sbattleClearEffHitData(8);
  sbattleClearEffHitData(9);
  sbattleClearEffHitData(10);
  sbattleClearEffHitData(11);
  sbattleClearEffHitData(12);
  sbattleClearEffHitData(13);
  sbattleClearEffHitData(14);
  sbattleClearEffHitData(15);
  p_filename = &sbtldbwk->filename;
  *p_filename = 0;
  v70 = sbtldbwk;
  if (!v70->nef_checkflg)
  {
    v70 = sbtldbwk;
    v70->nef_mode = 3;
    effhitcsr = v70->nef_pagecsr;
    v70->nef_nowpage = 1;
    v36 = 2;
    goto LABEL_44;
  }
  return 1;
}

// 0x191e580
bool sBtlDebug_LoadMHTData(s32 point, s32 flg) {
  SBTLUNIT_LISTWORK *UnitMng;
  s32 acterID;
  SBTLUNIT_WORK *v9;
  s32 minor;
  s32 *p_data;
  Il2CppObject *v13;
  char *v14;
  s32 v17;
  s32 data;

  UnitMng = wk->UnitMng;
  acterID = sbtldbwk->acterID;
  v9 = sBtlSearchUnit_ID(UnitMng, acterID);
  minor = v9->minor;
  if (v9->major)
  {
    p_data = &v17;
    v17 = minor;
  }
  else
  {
    data = minor;
    p_data = &data;
  }
  v13 = Box(s32, p_data);
  v14 = Format("P{0,3:X}+.MHT", v13, 0);
  Concat_54766928(0, v14, 0);
  sbattleCheckOpenMenu(point, flg);
  return 1;
}

// 0x1919540
bool sbattleCheckOpenMenu(s32 swt, s32 flg) {
  char *v5;
  char *v6;
  s32 mode;
  SBTLDEBUG_WORK *v42;
  char *v43;
  char **p_filename;
  s64 i;
  s64 v46;
  s32 nef_mode;
  SBDEBUG_CSRWORK *nef_exitokcsr;
  SBDEBUG_CSRWORK *unitcsr;
  u32 v52;
  SBTLDEBUG_WORK *v53;
  SBDEBUG_CSRWORK *nef_gdelokcsr;
  SBDEBUG_CSRWORK *nef_pagecsr;
  SBDEBUG_CSRWORK *nef_htypecsr;

  v5 = NewSpecific(string, 0x80u);
  v6 = "battle/mdlhit/";
  v5[0] = "battle/mdlhit/";
  mode = sbtldbwk->mode;
  if (mode == 12)
    goto LABEL_5;
LABEL_27:
  if (mode == 13)
  {
    switch (swt)
    {
      case 1:
        for (i = 0; i != 16; ++i)
        {
          sbattleClearEffHitData(i);
          v42 = sbtldbwk;
          v46 = (s64)v42->ef_wk + 8 * i;
          *(u8 *)(*(u64 *)(*(u64 *)(*(u64 *)(v46 + 32) + 40) + 80) + 16) = 1;
        }
        v42 = sbtldbwk;
        p_filename = &v42->filename;
        v43 = "";
        goto LABEL_64;
      case 2:
        goto LABEL_49;
      case 4:
        if (flg != 1)
          goto LABEL_97;
        if (!sbtldbwk->pagemode)
          goto LABEL_57;
        return 1;
      case 5:
        goto LABEL_41;
      default:
        return 1;
    }
  }
  switch (swt)
  {
    case 0:
      return 1;
    case 1:
      sbattleResetMotionMovePos();
      return 1;
    case 2:
LABEL_49:
      unitcsr = sbtldbwk->unitcsr;
      if (unitcsr->maxp)
      {
        goto LABEL_52;
      }
      unitcsr = sbtldbwk->unitcsr;
      *(u64 *)&unitcsr->point = 0;
      sbtldbwk->unitmode = 0;
      unitcsr->maxp = 544;
LABEL_52:
      sbtldbwk->ef_mode = 4;
      return 1;
    case 4:
      if (flg != 1)
        goto LABEL_97;
      if (sbtldbwk->pagemode)
        return 1;
      goto LABEL_60;
    case 5:
      goto LABEL_41;
    default:
      return 1;
  }
  mode = sbtldbwk->mode;
  if (mode != 12)
    goto LABEL_27;
LABEL_5:
  if (swt == 4)
  {
LABEL_41:
    nef_mode = sbtldbwk->nef_mode;
    sbtldbwk->nef_mode = 16;
    sbtldbwk->nef_modebk = nef_mode;
    nef_exitokcsr = sbtldbwk->nef_exitokcsr;
    nef_exitokcsr->point = 0;
    nef_exitokcsr->maxp = 2;
    return 0;
  }
  if (swt != 3)
  {
    if (swt == 2)
    {
      sbattleClearEffHitData(0);
      sbattleClearEffHitData(1);
      sbattleClearEffHitData(2);
      sbattleClearEffHitData(3);
      sbattleClearEffHitData(4);
      sbattleClearEffHitData(5);
      sbattleClearEffHitData(6);
      sbattleClearEffHitData(7);
      sbattleClearEffHitData(8);
      sbattleClearEffHitData(9);
      sbattleClearEffHitData(10);
      sbattleClearEffHitData(11);
      sbattleClearEffHitData(12);
      sbattleClearEffHitData(13);
      sbattleClearEffHitData(14);
      sbattleClearEffHitData(15);
LABEL_25:
      v42 = sbtldbwk;
      v43 = "";
      p_filename = &v42->filename;
LABEL_64:
      v42->filename = v43;
      v53 = sbtldbwk;
      if (v53->nef_checkflg)
      {
        if (!v52)
        {
          v53 = sbtldbwk;
        }
        v53->nef_mode = 8;
        nef_gdelokcsr = v53->nef_gdelokcsr;
        nef_gdelokcsr->point = 0;
        nef_gdelokcsr->maxp = 2;
        return 1;
      }
      else
      {
        if (!v52)
        {
          v53 = sbtldbwk;
        }
        v53->nef_nowpage = 0;
        v53->nef_mode = 4;
        nef_pagecsr = v53->nef_pagecsr;
        nef_htypecsr = v53->nef_htypecsr;
        nef_pagecsr->point = 0;
        nef_pagecsr->maxp = 1;
        nef_htypecsr->point = 0;
        nef_htypecsr->maxp = 3;
        return 1;
      }
      goto LABEL_25;
    }
    return 1;
  }
  if (flg != 1)
  {
LABEL_97:
    sbtldbwk->prev_mode = 1;
    return 0;
  }
  if (sbtldbwk->pagemode)
    return 1;
LABEL_57:
  sbtldbwk->prev_gstat = 0;
LABEL_60:
  sbtldbwk->pagemode = 1;
  return 1;
}

// 0x191a430
s32 sbattleGetHitPara_Max(SBTLSKILLHIT_TBL *hwk) {
  u32 type;

  type = hwk->type;
  if (sbtldbwk->mode != 12)
  {
    if (type <= 2)
      return dword_3E608C4[type];
    return 0;
  }
  switch (type)
  {
    case 2u:
      if ((hwk->flg & 0x100) != 0)
        return 26;
      else
        return 19;
    case 1u:
      if ((hwk->flg & 0x100) != 0)
        return 25;
      else
        return 18;
    case 0u:
      if ((hwk->flg & 0x100) != 0)
        return 24;
      else
        return 17;
    default:
      return 0;
  }
}

// 0x191a420
bool sbattleSetFilename(char *name) {
  return 1;
}

// 0x193d810
bool sbattleChk_DbgBound(void) {
  if (wk->battlemode == 3)
    return 0;
  return gDbgBound_Use;
}

// 0x193b210
bool sbattleChk_DbgBound_Loading(void) {
  if (!gDbgBound_Use)
    return 0;
  if (gDbgBound_Step > 0)
    return 1;
  return 0;
}

// 0x193d8e0
BSTF sbattleGet_DbgBound_BSTF(void) {
  if ((u32)gDbgBound_WeakType <= 5)
    return dword_3E60900[gDbgBound_WeakType];
  return 0;
}

// 0x193d980
void sbattleDbgBound_Proc(void) {
  s64 y_status;
  SBATTLE_WORK *v9;
  SBTLUNIT_LISTWORK *UnitMng;
  s32 playerID;
  SBTLUNIT_WORK *v12;
  SBTLUNIT_WORK *v13;
  dds3ProcessID_t *v15;
  s64 status;
  s32 targetID;
  SBTLUNIT_LISTWORK *v21;
  SBTLUNIT_WORK *v22;
  SBTLUNIT_WORK *v23;
  s32 v24;
  SBTLUNIT_LISTWORK *v26;
  SBTLUNIT_WORK *v27;
  SBTLUNIT_WORK *Unit;
  dds3Basic_t *pBasic;
  SBTLDEBUG_WORK *v30;
  SBTLUNIT_WORK *v31;
  SBTLUNIT_WORK *v35;
  s32 mode;
  SBTLUNIT_WORK *v37;
  dds3Basic_t *pUnitBasic;
  SBTLDEBUG_WORK *v40;
  s32 devilid;
  s32 v43;
  char *v44;
  char *v45;
  char *v47;
  bool v49;
  s32 v51;
  SBTLUNIT_WORK *v54;
  s32 ListID;
  s32 gDbgBound_Step_OldDevilID_local;
  s32 v61;
  bool v62;
  char **v63;
  u16 major;
  s32 minor;
  u16 v66;
  MOTIONDATA_WORK *v67;
  f32 v68;
  f32 v69;
  f32 m_stoprate;
  s32 v71;
  char *v72;
  char *v73;
  char *v75;
  f32 v76;
  f32 v77;
  char *v78;
  char *v80;
  u32 v81;
  char *v82;
  char *v83;
  char *v85;
  char *v86;
  s32 gDbgBound_Step_local;
  s32 Rebound[2];

  *(u64 *)Rebound = 0;
  gDbgBound_Step_local = 0;
  if (!dds3GetActiveScene())
    return;
  if (!wk)
    return;
  if (!wk->UnitMng)
    return;
  if ((wk->status & 8) != 0)
    return;
  if ((wk->status2 & 0x20000000) != 0)
    return;
  if (!sbtldbwk)
  {
    gDbgBound_Use = 0;
    return;
  }
  y_status = sbtldbwk->y_status;
  gDbgBound_Use = (y_status & 0x1000) != 0;
  if ((y_status & 0x1000) != 0)
  {
    v9 = wk;
    UnitMng = v9->UnitMng;
    playerID = v9->playerID;
    v12 = sBtlSearchUnit_ID(UnitMng, playerID);
    if (v12)
    {
      v13 = v12;
      if (v12->actwk->status != 42)
      {
        v15 = dds3SearchProcessName("sbtldebug_proc");
        if (!v15)
          goto LABEL_162;
        status = sbtldbwk->status;
        if ((status & 1) == 0)
        {
          status = sbtldbwk->status;
          if ((status & 0x30) == 0)
          {
LABEL_162:
            gDbgBound_Step_local = gDbgBound_Step;
            switch (gDbgBound_Step_local)
            {
              case 0:
                targetID = v13->actaiwk->targetID;
                if (targetID == -1)
                  return;
                v21 = wk->UnitMng;
                v22 = sBtlSearchUnit_ID(v21, targetID);
                if (!v22)
                  return;
                v23 = v22;
                devilid = v22->para->devilid;
                v43 = v22->para->devilid;
                devilid = v43;
                sBtlDrawDevilName(3680, 3888, 0, 0x64E6AA80u, devilid);
                v44 = ToString_55989008(LOWORD(v23->para) + 22, "X", 0);
                v45 = Concat_54766928("L2/R2 : 0x", v44, 0);
                v47 = v45;
                v45 = v47;
                sbattleDrawString(150, 486, v45, 0, 0);
                goto LABEL_89;
              case 1:
                v24 = v13->actaiwk->targetID;
                if (v24 == -1)
                  return;
                v26 = wk->UnitMng;
                v27 = sBtlSearchUnit_ID(v26, v24);
                if (!v27)
                  return;
                v54 = v27;
                ListID = v27->ListID;
                gDbgBound_Step_ListID = ListID;
                gDbgBound_Step_OldDevilID_local = v54->para->devilid;
                gDbgBound_Step_OldDevilID = gDbgBound_Step_OldDevilID_local;
                if (gDbgBound_Step_NextLR < 0)
                {
                  gDbgBound_Step_OldDevilID_local = gDbgBound_Step_OldDevilID;
                  v61 = gDbgBound_Step_OldDevilID_local - 1;
                }
                else
                {
                  gDbgBound_Step_OldDevilID_local = gDbgBound_Step_OldDevilID;
                  v61 = gDbgBound_Step_OldDevilID_local + 1;
                }
                gDbgBound_Step_NextDevilID = v61;
LABEL_69:
                ++gDbgBound_Step;
                return;
              case 2:
                Unit = sbattleGetUnit(gDbgBound_Step_ListID);
                sBtlDeleteUnit_UnWork(Unit);
                pBasic = Unit->pBasic;
                v30 = sbtldbwk;
                v30->pUnitBasic = pBasic;
                Unit->mode = 0;
                goto LABEL_68;
              case 3:
                v31 = sbattleGetUnit(gDbgBound_Step_ListID);
                sbattleSetModelData(v31, 1u, gDbgBound_Step_NextDevilID);
                v31->mode = 1;
                v31->gstat = 0;
                sBtlDebug_SetVisualData(v31);
LABEL_68:
                goto LABEL_69;
              case 4:
                v35 = sbattleGetUnit(gDbgBound_Step_ListID);
                mode = v35->mode;
                v37 = v35;
                if (mode == 8 || mode == 4)
                {
                  ++gDbgBound_Step;
                  v37->mode = 8;
                }
                return;
              case 5:
                pUnitBasic = sbtldbwk->pUnitBasic;
                dds3SceneBasicDelete(pUnitBasic);
                v40 = sbtldbwk;
                v40->pUnitBasic = 0;
                gDbgBound_Step = 0;
                return;
              default:
                v23 = 0;
LABEL_89:
                if (IsSceanStop())
                  return;
                v49 = CHECK_TRIG(20491, 1);
                if (v49)
                {
                  ++gDbgBound_WeakType;
                }
                gDbgBound_WeakType = (gDbgBound_WeakType + 5) % 5;
                if (v23->mode != 8)
                  goto LABEL_114;
                if (CHECK_TRIG(20489, 1))
                {
                  v51 = -1;
LABEL_102:
                  gDbgBound_Step_NextLR = v51;
                  gDbgBound_Step = 1;
                  goto LABEL_114;
                }
                v62 = CHECK_TRIG(20492, 1);
                if (v62)
                {
                  v51 = 1;
                  goto LABEL_102;
                }
LABEL_114:
                gDbgBound_Step_local = gDbgBound_WeakType;
                switch (gDbgBound_Step_local)
                {
                  case 0:
                    v63 = &"R1 : 金縛 弱点硬直(1/5)";
                    goto LABEL_133;
                  case 1:
                    v63 = &"R1 : 火炎 弱点硬直(2/5)";
                    goto LABEL_133;
                  case 2:
                    v63 = &"R1 : 氷結 弱点硬直(3/5)";
                    goto LABEL_133;
                  case 3:
                    v63 = &"R1 : 電撃 弱点硬直(4/5)";
                    goto LABEL_133;
                  case 4:
                    v63 = &"R1 : 衝撃 弱点硬直(5/5)";
LABEL_133:
                    sbattleDrawString(150, 510, *v63, 0, 1);
                    break;
                  default:
                    break;
                }
                major = v23->major;
                minor = v23->minor;
                v66 = v23->major;
                major = v66;
                v67 = sBtlGetVisualData(major, minor)->mwk[4];
                if (CHECK_TRIG2(20486))
                {
                  v68 = v67->m_stoprate + -1.0;
                  v67->m_stoprate = v68;
                  if (v68 < 0.0)
                    v67->m_stoprate = 0.0;
                }
                if (CHECK_TRIG2(20487))
                {
                  v67->m_stoprate = v67->m_stoprate + 1.0;
                  if (!CHECK_TRIG2(20484))
                  {
LABEL_141:
                    if (!CHECK_TRIG2(20485))
                      goto LABEL_147;
                    goto LABEL_145;
                  }
                }
                else if (!CHECK_TRIG2(20484))
                {
                  goto LABEL_141;
                }
                v67->cancelrate = v67->cancelrate + 1.0;
                if (!CHECK_TRIG2(20485))
                  goto LABEL_147;
LABEL_145:
                v69 = v67->cancelrate + -1.0;
                v67->cancelrate = v69;
                if (v69 < 0.0)
                  v67->cancelrate = 0.0;
LABEL_147:
                m_stoprate = v67->m_stoprate;
                v71 = m_stoprate;
                if (m_stoprate == INFINITY)
                  v71 = 0x80000000;
                gDbgBound_Step_local = v71;
                v72 = ToString((s32)&gDbgBound_Step_local, 0);
                v73 = Concat_54766928("L/R : 弱点硬直フレ : ", v72, 0);
                v75 = v73;
                v73 = v75;
                sbattleDrawString(350, 510, v73, 0, 1);
                sBtlGetBouncePow(v23, &Rebound[1], Rebound);
                v76 = *(f32 *)&Rebound[1];
                v78 = ToString(v77, &Rebound[1]);
                v80 = Concat_54766928("U/D : 打ち上げ値 : ", v78, 0);
                if (v76 >= 1.0)
                {
                  if (!v81)
                  sbattleDrawString(500, 510, v80, 0, -2);
                  v85 = ToString(Rebound, 0);
                  v86 = Concat_54766928("バウンド回数 : ", v85, 0);
                  sbattleDrawString(650, 510, v86, 0, -2);
                }
                else
                {
                  if (!v81)
                  sbattleDrawString(500, 510, v80, 0, 1);
                  v82 = ToString(Rebound, 0);
                  v83 = Concat_54766928("バウンド回数 : ", v82, 0);
                  sbattleDrawString(650, 510, v83, 0, 1);
                }
                break;
            }
          }
        }
      }
    }
  }
}

// 0x193e5a0
void sbattleDbgKaihiMuteki_Proc(void) {
  SBTLUNIT_LISTWORK *UnitMng;
  s32 playerID;
  SBTLUNIT_WORK *v6;
  SBTLUNIT_WORK *v7;
  s64 status;
  s32 flg;
  char *v13;
  char *v15;
  char *v17;
  char *v18;
  char *v20;
  char *v21;
  char *v23;
  char *v24;
  char *v26;
  char *v27;
  char *v29;
  dds3ModelHandle_t *hModel;
  f32 MotionFrameF;
  char *v34;
  char *v35;
  s32 Frame[2];

  *(u64 *)Frame = 0;
  if (!dds3GetActiveScene())
    return;
  if (wk)
  {
    if (wk->UnitMng)
    {
      if ((wk->status & 8) == 0)
      {
        if ((wk->status2 & 0x20000000) == 0)
        {
          UnitMng = wk->UnitMng;
          playerID = wk->playerID;
          v6 = sBtlSearchUnit_ID(UnitMng, playerID);
          if (v6)
          {
            v7 = v6;
            if (v6->actwk->status != 42)
            {
              if (!dds3SearchProcessName("sbtldebug_proc"))
                goto LABEL_34;
              status = sbtldbwk->status;
              if ((status & 1) == 0)
              {
                status = sbtldbwk->status;
                if ((status & 0x30) == 0)
                {
LABEL_34:
                  if ((v7->flg & 0x800) != 0)
                  {
                    sbattleDrawString(300, 0, "回避無敵", 0, 1);
LABEL_36:
                    if (!sBtlChkSetsuma_Just(&Frame[1], 0))
                      goto LABEL_37;
                    goto LABEL_46;
                  }
                  else
                  {
                    goto LABEL_36;
                  }
                  if (!sBtlChkSetsuma_Just(&Frame[1], 0))
                  {
LABEL_37:
                    if (!sBtlIsSetsumaPadStop())
                      goto LABEL_38;
                    goto LABEL_49;
                  }
LABEL_46:
                  v13 = ToString((s32)&Frame[1], 0);
                  v15 = Concat_54766928("ジャスト", v13, 0);
                  sbattleDrawString(400, 0, v15, 0, 1);
                  if (!sBtlIsSetsumaPadStop())
                  {
LABEL_38:
                    flg = v7->flg;
                    if ((flg & 0x100000) == 0)
                      goto LABEL_39;
                    goto LABEL_54;
                  }
LABEL_49:
                  v17 = ToString((u32)wk + 1604, 0);
                  v18 = ToString((u32)wk + 1608, 0);
                  v20 = Concat_54832128("殺魔入力", v17, "/", v18, 0);
                  sbattleDrawString(500, 0, v20, 0, 1);
                  flg = v7->flg;
                  if ((flg & 0x100000) == 0)
                  {
LABEL_39:
                    if ((flg & 0x200000) == 0)
                      goto LABEL_40;
                    goto LABEL_57;
                  }
LABEL_54:
                  v21 = ToString((s32)v7 + 1824, 0);
                  v23 = Concat_54766928("スロー解除後無敵", v21, 0);
                  sbattleDrawString(600, 0, v23, 0, 1);
                  if ((v7->flg & 0x200000) == 0)
                  {
LABEL_40:
                    if (v7->damagecnt < 1)
                    {
LABEL_63:
                      if ((wk->mode & 0xFFFFFFFE) == 0xE)
                      {
                        hModel = v7->hModel;
                        MotionFrameF = mdlGetMotionFrameF(hModel);
                        if (MotionFrameF >= 0.0)
                        {
                          *(f32 *)Frame = MotionFrameF + MotionFrameF;
                          v35 = ToString(MotionFrameF + MotionFrameF, Frame);
                          v34 = Concat_54766928("F:", v35, 0);
                        }
                        else
                        {
                          v34 = "F:補間中";
                        }
                        sbattleDrawString(200, 0, v34, 0, 1);
                      }
                      return;
                    }
LABEL_60:
                    v27 = ToString((u16)v7 + 952, 0);
                    v29 = Concat_54766928("ダメージ後無敵", v27, 0);
                    sbattleDrawString(800, 0, v29, 0, 1);
                    goto LABEL_63;
                  }
LABEL_57:
                  v24 = ToString((s32)v7 + 1828, 0);
                  v26 = Concat_54766928("殺魔一閃後無敵", v24, 0);
                  sbattleDrawString(700, 0, v26, 0, 1);
                  if (v7->damagecnt < 1)
                    goto LABEL_63;
                  goto LABEL_60;
                }
              }
            }
          }
        }
      }
    }
  }
}

// 0x193ec30
bool sbattleIsBattle(void) {
  return CheckRun();
}
