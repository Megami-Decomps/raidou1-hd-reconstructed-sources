#pragma once
#include "types.h"
#include "BSTF.h"
#include "MODELTYPE.h"
#include "MOTION_FLG.h"
#include "SBTLDMG_HITFLG.h"
#include "SBTLUNIT_SIDE.h"
#include "kernel.h"

typedef enum {
    SBDEBUG_MODE_MAIN = 0,
    SBDEBUG_MODE_MODELSEL = 1,
    SBDEBUG_MODE_MODELMENU = 2,
    SBDEBUG_MODE_MOTIONCHNG = 3,
    SBDEBUG_MODE_UNITCHNG = 4,
    SBDEBUG_MODE_SOUSA = 5,
    SBDEBUG_MODE_VISUAL = 6,
    SBDEBUG_MODE_ATARI = 7,
    SBDEBUG_MODE_SKILLCHANGE = 8,
    SBDEBUG_MODE_EFFCYLINDER = 9,
    SBDEBUG_MODE_OPTION = 10,
    SBDEBUG_MODE_EFFEDITOR = 11,
    SBDEBUG_MODE_EFFHITE = 12,
    SBDEBUG_MODE_MODELHITE = 13,
    SBDEBUG_MODE_MODELMOVE = 14,
    SBDEBUG_MODE_SETMENU = 15,
    SBDEBUG_MODE_BST_K = 16,
    SBDEBUG_MODE_PARA = 17,
    SBDEBUG_MODE_AI = 18,
    SBDEBUG_MODE_TIME = 19,
    SBDEBUG_MODE_CAMERA_EDITOR = 20,
    SBDEBUG_MODE_WEAPON_SET = 21,
    SBDEBUG_MODE_TIME_LIMIT = 22,
} SBDEBUG_MODE;

typedef enum {
    SBDEBUG_FILETYPE_EHT = 0,
    SBDEBUG_FILETYPE_PB = 1,
    SBDEBUG_FILETYPE_EPL = 2,
    SBDEBUG_FILETYPE_MHT = 3,
} SBDEBUG_FILETYPE;

typedef enum {
    SBDEBUG_FLGTYPE_NONE = 0,
    SBDEBUG_FLGTYPE_ALL = 1,
    SBDEBUG_FLGTYPE_UNIT = 2,
    SBDEBUG_FLGTYPE_HGUN = 3,
    SBDEBUG_FLGTYPE_MGUN = 4,
    SBDEBUG_FLGTYPE_ECNT = 5,
    SBDEBUG_FLGTYPE_MAG = 6,
    SBDEBUG_FLGTYPE_EQPG = 7,
    SBDEBUG_FLGTYPE_EQPS = 8,
    SBDEBUG_FLGTYPE_STCK = 9,
    SBDEBUG_FLGTYPE_SEIKAKU = 10,
    SBDEBUG_FLGTYPE_YALL = 11,
    SBDEBUG_FLGTYPE_BMODE = 12,
    SBDEBUG_FLGTYPE_NAKAMA1 = 13,
    SBDEBUG_FLGTYPE_NAKAMA2 = 14,
    SBDEBUG_FLGTYPE_RAIDOUP = 15,
    SBDEBUG_FLGTYPE_MAPMDL = 16,
    SBDEBUG_FLGTYPE_WEAPON = 17,
    SBDEBUG_FLGTYPE_KYOUSEI = 18,
    SBDEBUG_FLGTYPE_SENSEI = 19,
    SBDEBUG_FLGTYPE_BOSSDBG = 20,
    SBDEBUG_FLGTYPE_ROUKETTE = 21,
    SBDEBUG_FLGTYPE_DLC = 22,
    SBDEBUG_FLGTYPE_CMBSKL = 23,
    SBDEBUG_FLGTYPE_NBS = 24,
    SBDEBUG_FLGTYPE_NGD = 25,
    SBDEBUG_FLGTYPE_TS = 26,
    SBDEBUG_FLGTYPE_DROP = 27,
    SBDEBUG_FLGTYPE_DMG_FIX = 28,
    SBDEBUG_FLGTYPE_HUUMA_TK = 29,
    SBDEBUG_FLGTYPE_SETSUMA = 30,
    SBDEBUG_FLGTYPE_MAGSET = 31,
    SBDEBUG_FLGTYPE_SPDBGPARAM = 32,
} SBDEBUG_FLGTYPE;

typedef enum {
    SBDEBUG_FLG_PANEL = 1,
    SBDEBUG_FLG_CAMERA = 2,
    SBDEBUG_FLG_GRID = 4,
    SBDEBUG_FLG_DANGAN = 8,
    SBDEBUG_FLG_OPTI_MENU = 16,
    SBDEBUG_FLG_EFFEDITOR = 32,
    SBDEBUG_FLG_HITDRAW = 64,
    SBDEBUG_FLG_CAMERALOCK = 128,
    SBDEBUG_FLG_KOUSHIN = 256,
    SBDEBUG_FLG_INTERFACE = 512,
    SBDEBUG_FLG_UNITPAD = 1024,
    SBDEBUG_FLG_EFFHITE = 2048,
    SBDEBUG_FLG_WEAKUP = 4096,
    SBDEBUG_FLG_MODEFACE = 8192,
    SBDEBUG_FLG_DAMAGE = 16384,
    SBDEBUG_FLG_BADST = 32768,
    SBDEBUG_FLG_DOWN = 65536,
    SBDEBUG_FLG_EFFTEST = 131072,
    SBDEBUG_FLG_ENEMYSTOP = 262144,
    SBDEBUG_FLG_ALLSKILL = 524288,
    SBDEBUG_FLG_BGM = 1048576,
    SBDEBUG_FLG_PREVDEL = 2097152,
    SBDEBUG_FLG_HITEDITOR = 4194304,
    SBDEBUG_FLG_DAMAGE_S = 8388608,
    SBDEBUG_FLG_HPGAUGE = 16777216,
    SBDEBUG_FLG_BSTNAME = 33554432,
    SBDEBUG_FLG_RESULT = 67108864,
    SBDEBUG_FLG_E_LOAD = 134217728,
    SBDEBUG_FLG_SEDISTANCE = 268435456,
    SBDEBUG_FLG_SEDOUJI = 536870912,
    SBDEBUG_FLG_SEPAN = 1073741824,
    SBDEBUG_FLG_DEBUGSET = 2147483648,
    SBDEBUG_FLG_FOLLOWUP_CAMERA = 4294967296,
    SBDEBUG_FLG_FOLLOWUP_CAMERA_EDITOR = 8589934592,
    SBDEBUG_FLG_WEAPON_SET = 17179869184,
    SBDEBUG_FLG_SP_DBG_PARAM = 34359738368,
    SBDEBUG_FLG_USERDMG = 1,
    SBDEBUG_FLG_CMNDPARA = 2,
    SBDEBUG_FLG_WEAKON = 4,
    SBDEBUG_FLG_TIME = 8,
    SBDEBUG_FLG_PLAYERDMG = 16,
    SBDEBUG_FLG_NAKAMADMG = 32,
    SBDEBUG_FLG_ENEMYDMG = 64,
    SBDEBUG_FLG_HUUMASUCCESS = 128,
    SBDEBUG_FLG_USEMAG = 256,
    SBDEBUG_FLG_COOLTIME = 512,
    SBDEBUG_FLG_NEWHIRUMI = 1024,
    SBDEBUG_FLG_BST_INFINITE = 2048,
    SBDEBUG_FLG_DROP = 4096,
    SBDEBUG_FLG_SPIRIT_SWORD = 8192,
    SBDEBUG_FLG_NAKAMAGUARD = 16384,
    SBDEBUG_FLG_ENEMYGUARD = 32768,
    SBDEBUG_FLG_TIME_SET = 65536,
    SBDEBUG_FLG_U_NONE = 0,
    SBDEBUG_FLG_U_UPPANEL = 1,
    SBDEBUG_FLG_U_AREA_H = 2,
    SBDEBUG_FLG_U_AREA_P = 4,
    SBDEBUG_FLG_U_AREA_F = 8,
    SBDEBUG_FLG_U_AREA_E = 16,
    SBDEBUG_FLG_U_AIPANEL = 32,
} SBDEBUG_FLG;

typedef struct MOTIONDATA_WORK MOTIONDATA_WORK;
typedef struct SBDEBUG_CSRWORK SBDEBUG_CSRWORK;
typedef struct SBDEBUG_FILELISTWORK SBDEBUG_FILELISTWORK;
typedef struct SBDEBUG_FILEWORK SBDEBUG_FILEWORK;
typedef struct SBDEBUG_PATHDATA SBDEBUG_PATHDATA;
typedef struct SBTLDMG_HITLISTWORK SBTLDMG_HITLISTWORK;
typedef struct SBTLDMG_HITWORK SBTLDMG_HITWORK;
typedef struct SBTLSKILLHIT_POSWORK SBTLSKILLHIT_POSWORK;
typedef struct SBTLSKILLHIT_TBL SBTLSKILLHIT_TBL;
typedef struct SBTLSKILLIDOU_WORK SBTLSKILLIDOU_WORK;
typedef struct SBTLSKLHIT_PACDATAWORK SBTLSKLHIT_PACDATAWORK;
typedef struct SBTLUNIT_WORK SBTLUNIT_WORK;
typedef struct dds3Basic_t dds3Basic_t;
typedef struct dds3ModelHandle_t dds3ModelHandle_t;
typedef struct dds3PoseSet_t dds3PoseSet_t;
typedef struct dds3ProcessID_t dds3ProcessID_t;
typedef struct evtUnitHandle_t evtUnitHandle_t;

typedef bool (*sbdebug_procmenuDelegate)(dds3ProcessID_t *UnnamedParameter);
typedef bool (*sbdebug_drawmenuDelegate)(dds3ProcessID_t *UnnamedParameter);
typedef bool (*sBtlDebug_NEFMODE_FuncDelegate)(void);
typedef bool (*sBtlDebug_NMDLMODE_FuncDelegate)(void);
typedef bool (*sBtlDebug_NMDLMVMODE_FuncDelegate)(void);
typedef bool (*sBtlDebug_EffHitEditorDraw_FunctblDelegate)(SBDEBUG_CSRWORK *UnnamedParameter, SBTLSKILLHIT_TBL *UnnamedParameter2, SBTLSKILLHIT_POSWORK *UnnamedParameter3, SBTLSKILLIDOU_WORK *UnnamedParameter4, SBDEBUG_PATHDATA *UnnamedParameter5);
typedef bool (*sBtlDebug_MDLHitEditorDraw_FunctblDelegate)(SBDEBUG_CSRWORK *UnnamedParameter, SBTLSKILLHIT_TBL *UnnamedParameter2, SBTLSKILLHIT_POSWORK *UnnamedParameter3, SBTLSKILLIDOU_WORK *UnnamedParameter4, SBDEBUG_PATHDATA *UnnamedParameter5);

struct SBDEBUG_CSRWORK {
    s32 point;
    s32 offset;
    s32 maxp;
    s32 dummy;
};

struct SBDEBUG_FILEWORK {
    char *name;
    s32 len;
    s32 type;
    SBDEBUG_FILEWORK *prev;
    SBDEBUG_FILEWORK *next;
};

struct SBDEBUG_FILELISTWORK {
    s32 num;
    SBDEBUG_FILEWORK *wk;
};

struct SBDEBUG_PATHDATA {
    f32 nef_pathtime;
    f32 nef_addpathtime;
    f32 nef_timecnt;
    s32 nef_movetype;
    dds3Basic_t *path_pBasic;
    evtUnitHandle_t *path_hEveUnit;
    dds3ModelHandle_t *path_hModel;
    s32 path_motionno;
};

extern sbdebug_procmenuDelegate *sbdebug_procmenu;
extern sbdebug_drawmenuDelegate *sbdebug_drawmenu;
extern sBtlDebug_NEFMODE_FuncDelegate *sBtlDebug_NEFMODE_Func;
extern sBtlDebug_NMDLMODE_FuncDelegate *sBtlDebug_NMDLMODE_Func;
extern sBtlDebug_NMDLMVMODE_FuncDelegate *sBtlDebug_NMDLMVMODE_Func;
extern sBtlDebug_EffHitEditorDraw_FunctblDelegate *sBtlDebug_EffHitEditorDraw_Functbl;
extern sBtlDebug_MDLHitEditorDraw_FunctblDelegate *sBtlDebug_MDLHitEditorDraw_Functbl;
extern u32 *sBtlDebug_SetPathMotion_line_colors;
extern u8 *sBtlDebug_SetPathMotion_motion_savetbl;
extern u8 *sBtlDebug_SetPathMotion_motion_savetbl_p;
extern SBTLDMG_HITFLG *sBtlDebug_SetPathMotion_effhitset_flag;
extern char *sbplayer_cmnd;
extern char *sbtarget_cmnd;
extern char *sblist_optimenu;
extern char *sblist_setmenu_00;
extern char *sblist_setmenu_01;
extern bool *sblist_setmenu_flg;
extern char *encountInfo;
extern char **mapModelInfo;
extern char *sblist_paramenu;
extern char *sblist_panel;
extern char *sblist_modelmenu;
extern char *sblistCameraMenu;
extern char *sblistTimeMenu;
extern char *sblist_mdlmenupanel;
extern char *sblist_mtioncgpanel_n;
extern char *sblist_mtioncgpanel_boss;
extern char *sblist_mtioncgpanel_p;
extern char *sblist_visualmenu00;
extern char *sblist_visualmenu01;
extern char *sblist_visualmenu02;
extern char *sblist_visualmenu01_e;
extern char *sblist_visualmenu02_e;
extern char *sblist_visualmenu03;
extern char *sblist_visualmenu04;
extern char *sblist_visualmenu05;
extern char *sblist_visualmenu06;
extern char *sblist_visualmenu06_0;
extern char *sblist_visualmenu07;
extern char *sblist_visualmenu08;
extern char *sblist_visualmenu09;
extern MOTION_FLG *motion_flg;
extern char *motion_tbl_new;
extern char *motion_tbl_player;
extern char *sblist_efhitmenu_open_move;
extern char *sblist_efhitmenu_open_mdl;
extern char *sblist_efhitmenu_open;
extern char *sblist_efhitmenu_page_00;
extern char *sblist_efhitmenu_page_01;
extern char *sblist_efhitmenu_page_02;
extern char *sblist_efhitmenu_selmenu;
extern char *sblist_efhitmenu_delok_00;
extern char *sblist_efhitmenu_exitok_00;
extern char *sblist_efhitmenu_delok_01;
extern char *sblist_efhitmenu_hittype;
extern char *sblist_efhitmenu_edit_page;
extern char *sblist_efhitmenu_edit_para00;
extern char *sblist_efhitmenu_edit_para00_0;
extern char *sblist_efhitmenu_edit_para00_1;
extern char *sblist_mdlhitmenu_edit_para00;
extern char *sblist_mdlhitmenu_edit_para00_0;
extern char *sblist_mdlhitmenu_edit_para00_1;
extern char *sblist_mdlhitmenu_edit_para02;
extern char *sblist_mdlhitmenu_edit_para03;
extern char *sblist_efhitmenu_edit_para01;
extern char *sblist_efhitmenu_edit_para01_1;
extern char *sblist_mdlmovemenu_edit_para00;
extern char *sblist_efhitmenu_edit_para02;
extern char *sblist_efhitmenu_edit_para02_0;
extern char *sblist_efhitmenu_edit_para03;
extern char *sblist_efhitmenu_edit_para03_0;
extern char *sblist_efhitmenu_edit_para03_1;
extern char *sblist_efhitmenu_edit_para04;
extern char *sblist_efhitmenu_edit_para05_00;
extern char *sblist_efhitmenu_edit_para05_01;
extern char *sblist_efhitmenu_edit_para06_00;
extern char *sblist_effhitemenu00;
extern char *sblist_effhitemenu01;
extern char *sblist_effhitemenu02;
extern char *sblist_effhitemenu03;
extern char *sblist_effhitemenu03_0;
extern char *sblist_effhitemenu03_a1;
extern char *sblist_effhitemenu03_a2;
extern char *sblist_effhitemenu04;
extern char *sblist_effhitemenu05;

void sprDbgPrintStr(s32 X, s32 Y, u32 Z, s32 Attr, char *pStr, DDS3_OT OtNo, s32 _fontSize);
void sprDbgDrawWindowFrame(s32 X, s32 Y, u32 Z, s32 W, s32 H, u32 BgCol, u32 FrmCol, DDS3_OT OtNo);
bool sbattleMotionChngDraw(dds3ProcessID_t *id);
bool sbattleUnitChngProc(dds3ProcessID_t *id);
bool sbattleUnitChngDraw(dds3ProcessID_t *id);
bool sbattleSousaProc(dds3ProcessID_t *id);
bool sbattleSousaDraw(dds3ProcessID_t *id);
bool sbattleVisualProc(dds3ProcessID_t *id);
bool sbattleVisualDraw(dds3ProcessID_t *id);
bool sbattleVisualHitProc(dds3ProcessID_t *id);
bool sbattleVisualHitDraw(dds3ProcessID_t *id);
bool sbattleSkillChangeProc(dds3ProcessID_t *id);
bool sbattleSkillChangeDraw(dds3ProcessID_t *id);
bool sbattleOptionProc(dds3ProcessID_t *id);
bool sbattleOptionDraw(dds3ProcessID_t *id);
bool sbattleEffEditorProc(dds3ProcessID_t *id);
bool sbattleEffEditorDraw(dds3ProcessID_t *id);
bool sbattleEffHitEditorProc(dds3ProcessID_t *id);
bool sbattleEffHitEditorDraw(dds3ProcessID_t *id);
bool sbattleMdlHitEditorProc(dds3ProcessID_t *id);
bool sbattleMdlHitEditorDraw(dds3ProcessID_t *id);
void sbattleSetSword(void);
bool sbattleSetDebugMenuProc(dds3ProcessID_t *id);
bool sbattleSetDebugMenuDraw(dds3ProcessID_t *id);
bool sbattleMdlMoveEditorProc(dds3ProcessID_t *id);
bool sbattleMdlMoveEditorDraw(dds3ProcessID_t *id);
bool sbattleBSTProc(dds3ProcessID_t *id);
bool sbattleBSTDraw(dds3ProcessID_t *id);
bool sbattleParaProc(dds3ProcessID_t *id);
bool sbattleParaDraw(dds3ProcessID_t *id);
bool sbattleAIProc(dds3ProcessID_t *id);
bool sbattleAIDraw(dds3ProcessID_t *id);
bool sbattleCameraEditorDraw(dds3ProcessID_t *id);
bool sbattleWeaponSetDraw(dds3ProcessID_t *id);
bool sbattleTimeLimitEditorDraw(dds3ProcessID_t *id);
void sbattleSaveFollowUpCameraParAsset(void);
bool sbattleCameraEditorProc(dds3ProcessID_t *id);
bool sbattleWeaponSetProc(dds3ProcessID_t *id);
bool sbattleTimeLimitEditorProc(dds3ProcessID_t *id);
bool sbattleNEFMODE_Func_Open(void);
bool sbattleNEFMODE_Func_Save(void);
bool sbattleNEFMODE_Func_Load(void);
bool sbattleNEFMODE_Func_PageList(void);
bool sbattleNEFMODE_Func_Hittype(void);
bool sbattleNEFMODE_Func_SelMenu(void);
bool sbattleNEFMODE_Func_Delok(void);
bool sbattleNEFMODE_Func_Edit(void);
bool sbattleNEFMODE_Func_PBLoad(void);
bool sbattleNEFMODE_Func_PBLoader(void);
bool sbattleNEFMODE_Func_EPLLoad(void);
bool sbattleNEFMODE_Func_EPLLoader(void);
bool sbattleNEFMODE_Func_EPLMenu(void);
bool sbattleNEFMODE_Func_EPLDelok(void);
bool sbattleNEFMODE_Func_Exitok(void);
bool sbattleMDLMODE_Func_Open(void);
bool sbattleMDLMODE_Func_Edit(void);
bool sbattleMDLMODE_Func_PageList(void);
bool sBtlDebug_MOVEMODE_Func_Open(void);
bool sbattleMOVEMODE_Func_PageList(void);
bool sbattleMOVEMODE_Func_SelMenu(void);
bool sbattleMOVEMODE_Func_Edit(void);
bool sbattleEffHitEditorDraw_Functbl_Sphere(SBDEBUG_CSRWORK *wk, SBTLSKILLHIT_TBL *hwk, SBTLSKILLHIT_POSWORK *para, SBTLSKILLIDOU_WORK *iwk, SBDEBUG_PATHDATA *path);
bool sbattleEffHitEditorDraw_Functbl_Cylinder(SBDEBUG_CSRWORK *wk, SBTLSKILLHIT_TBL *hwk, SBTLSKILLHIT_POSWORK *para, SBTLSKILLIDOU_WORK *iwk, SBDEBUG_PATHDATA *path);
bool sbattleEffHitEditorDraw_Functbl_Ring(SBDEBUG_CSRWORK *wk, SBTLSKILLHIT_TBL *hwk, SBTLSKILLHIT_POSWORK *para, SBTLSKILLIDOU_WORK *iwk, SBDEBUG_PATHDATA *path);
bool sbattleMDLHitEditorDraw_Functbl_Sphere(SBDEBUG_CSRWORK *wk, SBTLSKILLHIT_TBL *hwk, SBTLSKILLHIT_POSWORK *para, SBTLSKILLIDOU_WORK *iwk, SBDEBUG_PATHDATA *path);
bool sbattleMDLHitEditorDraw_Functbl_Cylinder(SBDEBUG_CSRWORK *wk, SBTLSKILLHIT_TBL *hwk, SBTLSKILLHIT_POSWORK *para, SBTLSKILLIDOU_WORK *iwk, SBDEBUG_PATHDATA *path);
bool sbattleMDLHitEditorDraw_Functbl_Ring(SBDEBUG_CSRWORK *wk, SBTLSKILLHIT_TBL *hwk, SBTLSKILLHIT_POSWORK *para, SBTLSKILLIDOU_WORK *iwk, SBDEBUG_PATHDATA *path);
void sbattleOpenDraw_MOVE(void);
void sbattlePageListDraw_MOVE(void);
bool sbattleEditDraw_MOVE(SBDEBUG_CSRWORK *wk, SBTLSKILLHIT_TBL *hwk, SBTLSKILLHIT_POSWORK *para, SBTLSKILLIDOU_WORK *iwk, SBDEBUG_PATHDATA *path);
void sbattleResetMotionMovePos(void);
bool sbattleSetMotionMoveData_Buffer(void);
void sbattleOpenDraw(void);
void sbattlePageListDraw(void);
void sBtlDebug_SelMenuDraw(void);
void sbattleHittypeDraw(void);
bool sbattleCreateDirList(SBDEBUG_FILETYPE type);
s32 sbattleDirOpen(SBDEBUG_FILETYPE type);
void sbattleLoadDraw(void);
void sbattlePBLoadDraw(void);
void sbattleEPLLoadDraw(void);
void sbattleEPLMenuDraw(void);
void sbattleEPLDelokDraw(void);
void sbattleExitokDraw(void);
bool sbattleEditDraw(SBDEBUG_CSRWORK *wk, SBTLSKILLHIT_TBL *hwk, SBTLSKILLHIT_POSWORK *para, SBTLSKILLIDOU_WORK *iwk, SBDEBUG_PATHDATA *path);
bool sbattleSetPathMotion(SBTLSKLHIT_PACDATAWORK *pac, s32 point);
bool sbattleResetEPLData(s32 i);
s32 sbattleCreateUnit(s16 minor, SBTLUNIT_SIDE side, const sdfVector4_t *pos);
bool sbattleSetPreViewModel(void);
bool sbattleDeletePrevModel(void);
bool sbattleAddPrev(SBDEBUG_CSRWORK *swk, s32 prev, s32 motion);
bool sbattleDecPrev(SBDEBUG_CSRWORK *swk, s32 prev, s32 motion);
bool sbattleClearEffHitData(s32 id);
void sbattleDeleteEPLData(s32 id);
void sbattleDeletePathData(s32 id);
s32 sBtlDebug_ChangeModel(void);
void sbattleSetModelData(SBTLUNIT_WORK *unit, MODELTYPE major, s32 point);
void sbattleSetEffHitPara_S(SBTLSKILLHIT_TBL *hwk, SBDEBUG_CSRWORK *wk, s32 flg);
bool sbattleSetEffHitPara(SBTLSKILLHIT_TBL *hwk, SBDEBUG_CSRWORK *wk, s32 flg);
bool sBtlDebug_SetMDLMOVEPara(SBTLSKILLHIT_TBL *hwk, SBDEBUG_CSRWORK *wk, s32 flg);
s32 sbattleGetMotionNum(s32 id);
bool sbattleSetMDLHitPara(SBTLSKILLHIT_TBL *hwk, SBDEBUG_CSRWORK *wk, s32 flg);
s32 sBtlDebug_DirClose(s32 hDir);
void sbattleSaveMotionMoveData(void);
void sBtlDebug_SaveEffHit(s8 path, s8 file);
bool sbattleLoadEffHit(char *name, SBDEBUG_FILETYPE filetype);
void sBtlDebug_DecordPos(SBTLSKILLHIT_POSWORK *pos);
void sBtlDebug_ChangeDecordPos(SBTLSKILLHIT_POSWORK *pos);
void sbattleSetVisualPara(SBTLUNIT_WORK *unit, SBDEBUG_CSRWORK *wk, s32 flg);
bool sBtlDebug_SaveEffCylinderData(SBTLUNIT_WORK *unit);
bool sBtlDebug_SaveMotionData(SBTLUNIT_WORK *unit);
bool sbattleSBtlDebug_Skill(void);
bool sBtlDebug_UnitPad(dds3PoseSet_t *pUpdatePoseSet, dds3Basic_t *pBasic);
void sBtlDebug_SetEffectSetTbl(void);
bool sBtlDebug_CheckFlg(void);
void sBtlDebug_DevilNameListDraw(s32 ofsx, s32 ofsy);
void sBtlDebug_UnitPanelCursor(SBDEBUG_CSRWORK *wk);
void sBtlDebug_SetBattleMode(s8 flg, s32 para);
void sBtlDebug_SetSenseiMode(s8 flg, s32 para);
void sBtlDebug_SetEncountPara(s8 flg, s32 para);
void sBtlDebug_SetNakamaNo(s32 idx, s8 flg, s32 para);
void sBtlDebug_SetSpDbgParam(s8 flg, s32 para);
bool sBtlDebug_ResetStockPara(void);
bool sBtlDebug_CheckLoadEncountData(void);
void sBtlDebug_Shutdown(dds3ProcessID_t *id);
void sBtlDebug_DrawCursor(s32 x, s32 y, SBDEBUG_CSRWORK *wk);
void sBtlDebug_DrawCursor_OFFSET(s32 x, s32 y, s32 offsety, SBDEBUG_CSRWORK *wk);
void sBtlDebug_DrawNormalList(char *wk, s32 num, s32 nowpoint, s32 x, s32 y, bool *flg);
void sBtlDebug_DrawNormalList_Col(char *wk, s32 num, s32 nowpoint, s32 point, s32 x, s32 y);
void sBtlDebug_DrawONOFFList_Motion(MOTIONDATA_WORK *m_data, s32 x, s32 y, s32 num);
void sBtlDebug_DrawONOFFList_FLG(u32 flg, u32 *tbl, s32 x, s32 y, s32 num);
bool sbattleCheckDebugMode(SBDEBUG_MODE mode);
void sBtlDebug_ScreenPrintf(s32 x, s32 y, s32 attr, char *str, void *LegacyParamArray);
void sbattleTextDraw(s32 x, s32 y, s32 attr, s8 str);
void sbattleInitRunTime(void);
s32 sbattleSetRunTimeBase(void);
s32 sBtlDebug_GetRunTime(void);
s32 sbattlePrintfRunTime(char *str, void *LegacyParamArray);
void sbattleRunTimePrint_Debug(void);
void sbattleCreateFile_RunTime(void);
bool sBtlDebug_UnitUPPanelDraw(SBTLUNIT_WORK *wk);
bool sbattleDrawTriangle(const sdfVector4_t *pos0, const sdfVector4_t *pos1, const sdfVector4_t *pos2, s32 rgba0, s32 rgba1, s32 rgba2);
bool sBtlDebug_DrawSphere_LineY(const sdfVector4_t *pos, f32 r, u32 rgba, f32 deg);
bool sBtlDebug_DrawSphere_LineZ(const sdfVector4_t *pos, f32 r, u32 rgba, f32 deg);
bool sBtlDebug_DrawSphere_LineX(const sdfVector4_t *pos, f32 r, u32 rgba, f32 deg);
bool sBtlDebug_DrawCircle(const sdfVector4_t *pos, f32 r, u32 rgba, s32 flg);
bool sBtlDebug_DrawCircle2(const sdfVector4_t *pos, const sdfVector4_t *rot, f32 r0, f32 r1, f32 r2, f32 r3, s32 alpha00, s32 alpha01, s32 alpha02, u32 rgb);
bool sBtlDebug_DrawC(SBTLDMG_HITWORK *wk, u32 rgba, s32 start, s32 end, s32 flg, s32 mode);
void _3DCylinderDraw(const sdfVector4_t *pCenter, f32 radius, f32 height, u32 c, bool mat, const sdfMatrix4_t *pMat);
void sbattleCylinderLineDraw(const sdfVector4_t *pCenter, f32 radius, f32 height, const sdfColor32_t *col, bool mat, const sdfMatrix4_t *pMat);
void sbattleSphereLineDraw(const sdfVector4_t *center, const sdfVector4_t *rot, f32 rad, f32 area_r1, f32 area_r2, const sdfColor32_t *col);
void sbattleLineDraw(const sdfVector4_t *pos1, const sdfVector4_t *pos2, const sdfColor32_t *col);
bool sBtlDebug_GridDraw(void);
bool sbattleCreateHitC(SBTLDMG_HITLISTWORK *lwk, SBTLDMG_HITWORK *wk);
bool sBtlDebug_DeleteHitList(void);
bool sbattleDrawHitList(SBTLDMG_HITLISTWORK *lwk);
void sbattleDraw3DSphere(const sdfVector4_t *pCenter, f32 r, u32 c, bool mat, const sdfMatrix4_t *pMat);
bool sbattleCheckDamageTarget(SBTLUNIT_WORK *wk);
void sbattleDrawMatrix(const sdfMatrix4_t *mat);
void sbattleDrawPoly3(const sdfVector4_t *pos0, const sdfVector4_t *pos1, const sdfVector4_t *pos2, u32 col0, u32 col1, u32 col2, DDS3_OT otno);
void sbattleDrawPoly4(const sdfVector4_t *pos0, const sdfVector4_t *pos1, const sdfVector4_t *pos2, const sdfVector4_t *pos3, u32 col0, u32 col1, u32 col2, u32 col3, DDS3_OT otno);
void sBtlDebug_DrawAIDebug(void);
void sBtlDebug_SetVisualData(SBTLUNIT_WORK *wk);
void sbattleSetUnitPara(SBTLUNIT_WORK *unit, s32 flg, s32 point);
void sbattleDrawDebugMenu(s32 x, s32 y, s32 z, u32 rgba, s32 id);
void sbattleDrawDebugMenuCamera(s32 x, s32 y, s32 z, u32 rgba, s32 id);
void sbattleDrawDebugMenuTime(s32 x, s32 y, s32 z, u32 rgba, s32 id);
void sbattleDrawMotionList(s32 x, s32 y, s32 z, u32 rgba, s32 listid, s32 id);
void sbattleDrawString(s32 x, s32 y, char *buff, s32 point, s32 flg);
void sbattleDrawInt_Num(s32 x, s32 y, s32 data, s32 point, s32 flg);
void sbattleDrawFloat_Num(s32 x, s32 y, f32 data, s32 point, s32 flg);
void sbattleGetPathAddTime(SBTLSKILLHIT_TBL *hwk, SBDEBUG_PATHDATA *path);
void sBtlDebug_EffHitIdou(SBDEBUG_CSRWORK *wk, SBTLSKILLHIT_TBL *hwk, SBDEBUG_PATHDATA *path, const sdfVector4_t *poss, const sdfVector4_t *rott);
void sBtlDebug_EffHitDraw(SBDEBUG_CSRWORK *wk, SBTLSKILLHIT_TBL *hwk, SBDEBUG_PATHDATA *path, const sdfVector4_t *center);
void sBtlDebug_MDLHitDraw(SBDEBUG_CSRWORK *wk, SBTLSKILLHIT_TBL *hwk, const sdfVector4_t *center);
void sBtlDebug_EffHitPathDraw(SBDEBUG_CSRWORK *wk, SBTLSKILLHIT_TBL *hwk);
void sBtlDebug_DrawTri2Side(const sdfVector4_t *pos0, const sdfVector4_t *pos1, const sdfVector4_t *pos2, s32 color);
void sBtlDebug_DrawPoly2(const sdfVector4_t *pos0, const sdfVector4_t *pos1, const sdfVector4_t *pos2, const sdfVector4_t *pos3, s32 color);
void sBtlDebug_DrawHitCircle(const sdfVector4_t *center, const sdfVector4_t *rot, f32 rad, f32 area_r1, f32 area_r2);
void sBtlDebug_HitTypeMoveDraw(SBTLSKILLHIT_TBL *hwk, SBDEBUG_PATHDATA *path);
void sBtlDebug_ShutdownCamera(dds3ProcessID_t *id);
bool sBtlDebug_CheckMainPanel(SBTLUNIT_WORK *wk);
bool sBtlDebug_CheckEffectEditor(void);
bool sbattleSbtlDebug_CheckFreeCameraFlg(void);
void sBtlDebug_ResetPos_PlayerSide(void);
bool sBtlDebug_Init(void);
bool sBtlDebug_Draw(void);
void sBtlDebug_SetDuummyData(s32 ptn);
void sBtlDebug_SetDuummyData_Cmbskl(s32 ptn);
void sBtlDebug_DrawHPGauge(SBTLUNIT_WORK *wk);
bool sBtlDebug_DrawCmndPara(void);
void sBtlDebug_DrawTCursor(const sdfVector4_t *pos, u32 rgba);
bool sBtlDebug_CheckDebugFlg(SBDEBUG_FLG flg, SBDEBUG_FLGTYPE sw);
s32 sbattleGetEnemyStopMode(void);
bool sbattleDrawUnitChangeList(s32 x, s32 y);
char *sBtlDebug_GetDebugMenuFont(s32 id);
char *sbattleGetDebugMenuFontCamera(s32 id);
char *sbattleGetDebugMenuFontTime(s32 id);
SBDEBUG_FILELISTWORK *sbattleCreateFileList(void);
SBDEBUG_FILEWORK *sbattleCreateFile(SBDEBUG_FILELISTWORK *lwk, s32 type);
bool sbattleDeleteFileList(SBDEBUG_FILELISTWORK *lwk);
bool sbattleDrawMotionFrame(SBTLUNIT_WORK *unit, s32 motionno);
bool sbattleMDLHitEditor_DrawMotion(SBDEBUG_CSRWORK *wk, SBTLSKILLHIT_TBL *hwk, s32 nowp);
bool sBtlDebug_EPLParaDraw(SBDEBUG_CSRWORK *wk, SBTLSKILLHIT_TBL *hwk, SBTLSKILLHIT_POSWORK *para, SBTLSKILLIDOU_WORK *iwk, s32 point);
bool sBtlDebug_MoveTypeDraw(SBDEBUG_CSRWORK *wk, SBTLSKILLHIT_TBL *hwk, SBTLSKILLHIT_POSWORK *para, SBTLSKILLIDOU_WORK *iwk, SBDEBUG_PATHDATA *path, s32 point);
bool sbattleEPLDraw(SBDEBUG_CSRWORK *wk, SBTLSKILLHIT_TBL *hwk, const sdfVector4_t *poss, const sdfVector4_t *rott);
bool sbattleDrawPoseture(SBDEBUG_CSRWORK *wk, SBTLSKILLHIT_TBL *hwk, const sdfVector4_t *pose);
bool sBtlDebug_DrawClrcle_Line(f32 x, f32 y, f32 z, f32 r, u32 rgba);
SBTLUNIT_WORK *sbattleGetUnit(s32 point);
dds3ProcessFunc_t sbattleProcCamera(dds3ProcessID_t *id);
dds3ProcessFunc_t sBtlDebug_Proc(dds3ProcessID_t *id);
bool sBtlDebug_LoadMotionMoveData(void);
bool sBtlDebug_LoadMHTData(s32 point, s32 flg);
bool sbattleCheckOpenMenu(s32 swt, s32 flg);
s32 sbattleGetHitPara_Max(SBTLSKILLHIT_TBL *hwk);
bool sbattleSetFilename(char *name);
bool sbattleChk_DbgBound(void);
bool sbattleChk_DbgBound_Loading(void);
BSTF sbattleGet_DbgBound_BSTF(void);
void sbattleDbgBound_Proc(void);
void sbattleDbgKaihiMuteki_Proc(void);
bool sbattleIsBattle(void);
