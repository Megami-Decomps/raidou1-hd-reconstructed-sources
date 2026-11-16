#include "types.h"
#include "SaveResultType.h"
#include "cfg.h"
#include "cmpmain.h"
#include "dat.h"
#include "dds3_pad.h"
#include "dds3adminiprocess.h"
#include "dds3kernelcore.h"
#include "dds3kerneldraw.h"
#include "dds3kernelmain.h"
#include "dds3scenebasic.h"
#include "dds3worldbasic.h"
#include "evtmoon.h"
#include "fclmisc.h"
#include "fclmsg.h"
#include "file.h"
#include "fld.h"
#include "itf.h"
#include "kernel.h"
#include "lmap.h"
#include "localize.h"
#include "rstinit.h"
#include "slmain.h"
#include "sndat3.h"
#include "streaming.h"

#define L_KANJI_X0 46
#define L_KANJI_X1 70
#define L_KANJI_X2 142
#define L_KANJI_Y0 90
#define L_KANJI_Y1 114
#define L_KANJI_Y2 138
#define L_KANJI_Y3 162
#define L_KANJI_Y4 186
#define L_KANJI_Y5 210
#define L_KANJI_Y6 234
#define L_KANJI_Y7 258
#define L_KANJI_Y8 282
#define L_KANJI_Y9 306
#define SAVE_DATA_MAX 20
#define RAIDOU_CNT 2
#define SAVE_MIN_SIZE 102400
#define MH_SCROOL_SPEED 20
#define MH_KEYWAIT 4
#define SL_MEMOCA_LOAD_WAIT 60
#define SAVE_MSG_WAIT 60

typedef enum {
    MC_DATASTAT_OK = 1,
    MC_DATASTAT_DIR_EXIST = 2,
    MC_DATASTAT_FILE_EXIST = 4,
    MC_DATASTAT_ICON_EXIST = 8,
} MC_DATASTAT;

typedef enum {
    AUTOSAVE_PROC_INIT = 0,
    AUTOSAVE_PROC_SAVEINIT = 1,
    AUTOSAVE_PROC_SAVEWAIT = 2,
    AUTOSAVE_PROC_ENDWAIT = 3,
    AUTOSAVE_PROC_LAST = 4,
    AUTOSAVE_PROC_ERROR = 5,
    AUTOSAVE_PROC_END = 6,
} AUTOSAVE_PROC;

typedef enum {
    SUSPEND_PROC_INIT = 0,
    SUSPEND_PROC_SAVEINIT = 1,
    SUSPEND_PROC_SAVEWAIT = 2,
    SUSPEND_PROC_ENDWAIT = 3,
    SUSPEND_PROC_LAST = 4,
    SUSPEND_PROC_ERROR = 5,
    SUSPEND_PROC_END = 6,
} SUSPEND_PROC;

typedef enum {
    SAVELOAD_EITHER = 0,
    SAVELOAD_OVERWRITE = 1,
    SAVELOAD_CLERDATA = 2,
    SAVELOAD_CLER_OVERWRITE = 3,
    SAVELOAD_LOAD_NORMAL = 4,
    SAVELOAD_LOAD_SUSPEND = 5,
    SAVELOAD_LOAD_AUTO = 6,
    SAVELOAD_GOTITLE = 7,
    SAVELOAD_EXTRAMODE = 8,
    SAVELOAD_SAVECHECK = 9,
    SAVELOAD_NEXTSTORY = 10,
    SAVELOAD_SAVING = 11,
    SAVELOAD_LOADING = 12,
    SAVELOAD_SAVE_END = 13,
    SAVELOAD_LOAD_END = 14,
    SAVELOAD_MODE_EXTRA = 15,
    SAVELOAD_NAODATA_MAP1 = 16,
    SAVELOAD_NAODATA_MAP2 = 17,
    SAVELOAD_NAODATA_MAP3 = 18,
    SAVELOAD_CAPACITYSHORTAGE = 19,
    SAVELOAD_NAMELANG_DIFF = 20,
    SAVELOAD_CONVERT_CHK = 21,
    SAVELOAD_CONVERT_END = 22,
    SAVELOAD_INSTALL = 23,
    SAVELOAD_CONVERT_FA_ST = 24,
    SAVELOAD_CONVERT_FA_BR = 25,
    SAVELOAD_CONVERT_FA_SY = 26,
    SAVELOAD_TRIAL_UNABLELOAD = 27,
} SAVELOAD;

typedef struct FontReq_t FontReq_t;
typedef struct GameFileInfo_t GameFileInfo_t;
typedef struct __MC_GLOBALWORK __MC_GLOBALWORK;
typedef struct __MC_SELECTCURSORWORK __MC_SELECTCURSORWORK;
typedef struct __MC_UDCURSORWORK __MC_UDCURSORWORK;
typedef struct dds3AdditionWork_t dds3AdditionWork_t;
typedef struct dds3ProcessID_t dds3ProcessID_t;
typedef struct dds3SystemWork_t dds3SystemWork_t;
typedef struct fileHandle_t fileHandle_t;

typedef dds3ProcessFunc_t (*slHitAnyKeyNextFuncDelegate)(void);
typedef dds3ProcessFunc_t (*endFuncDelegate)(void);
typedef dds3ProcessFunc_t (*yesFuncDelegate)(void);
typedef dds3ProcessFunc_t (*noFuncDelegate)(void);

u8 saveVer;
static void *gSlBg;
static s32 gslDrawFlagBg;
static s32 gSlEndingMode;
static s32 gSlCampLoad;
static s32 gslLoadWait;
static s32 slProcShutDownFlg;
static s32 gslHardSelectWait;
static s32 gslDrawFlagFile;
static s32 slQueryYesNoMsg;
static s32 gslErrorCode;
static s32 gslAnimCnt;
static s32 gslErrorKeyFlag;
static s32 gslCheckCardWait;
static s32 gSlNowCardCheck;
static s32 gSlFileSelKyeFlg;
static s32 gslCursorSelect;
static s32 gslCursorTop;
static s32 gslMode;
static s32 gslChooseSaveIndex;
static s32 gSlMcAccessCnt;
static s32 gSlWindowCnt;
s32 gslInfoCode;
s32 gslExitType;
static s32 gslExitTitle;
static s32 gSlExitMode;
static s32 slExitWaitCnt;
static s32 gSlSaveMode;
static s32 slQueryYesNoCursor;
static s32 slQueryYesNoKeyFlag;
static s32 gslCursorZanzouCnt;
static f32 gslScrollY;
static fileHandle_t *baseIconFileHandle;
static void *baseIconPtr;
static s32 baseIconSize;
static s32 mcSlotNum;
static s32 bakCursorTop;
static s32 *gslStatFileInfo;
static GameFileInfo_t *gslInfo;
static GameFileInfo_t *gslInfo_back;
dds3ProcessFunc_t slProcPtr;
slQueryYesFuncDelegate slQueryYesFunc;
slQueryNoFuncDelegate slQueryNoFunc;
slSaveWriteFile_endFuncDelegate slSaveWriteFile_endFunc;
nextFuncDelegate slHitAnyKeyNextFunc;
nextFuncDelegate slExitWaitNextFunc;
__MC_GLOBALWORK *__mc_wk;
__MC_SELECTCURSORWORK *__mc_scwk;
__MC_UDCURSORWORK *__mc_udcwk;
static void *slSaveWriteFile_dataWaitPtr;
static void *slSaveWriteFile_buff;
static s32 slSaveWriteFile_size;
static bool saveDataInit;
s32 loadMode;
dds3SystemWork_t *SystemWork;
dds3AdditionWork_t *AdditionWork;
static s32 SlotDataTop;
static bool susendOpenFlg;
static bool autoSaveOpenFlg;
static s32 bakSelectCursor;
static bool slBlackScreenSet;
static s32 saveMsgCounter;
s32 gslErrorKeyNoWait;
s32 streamingMes;
static char *storyNow;
static char *storyEnd;
static char *storyName;
static char *difficName;
void *saveloadSystem;
s32 bakCursorSelect;
static void *icon_sys_ptr;
static s32 icon_sys_size;
static void *wk_ptr;
static s32 wk_size;
static s32 serialNumber;
static FontReq_t *slKanjiDraw3_handle;
static FontReq_t *slKanjiDrawH_handle;
static f32 slNextPageDraw_fc;
dds3ProcessFunc_t AutoSaveFunc;
static dds3ProcessID_t *AutoSaveID;
AUTOSAVE_PROC AutoSaveProc;
dds3ProcessFunc_t SuspendFunc;
static dds3ProcessID_t *SuspendID;
SUSPEND_PROC SuspendProc;
static bool mcMessageFlag;

static char *slFileLoadMsg(char *msg, s32 cnt);
static dds3ProcessFunc_t slLoadProc1st(dds3ProcessID_t *procId);
static dds3ProcessFunc_t slLoadProc1stBgm(dds3ProcessID_t *procId);
static dds3ProcessFunc_t slSaveProc1st(dds3ProcessID_t *procId);
static dds3ProcessFunc_t slSaveProcEp1st(dds3ProcessID_t *procId);
static dds3ProcessFunc_t slSaveProcEp1st1(dds3ProcessID_t *procId);
static dds3ProcessFunc_t slSaveProcEp1st2(void);
static dds3ProcessFunc_t slSaveProcEp1st3(void);
static dds3ProcessFunc_t slNextEpProc1st(dds3ProcessID_t *procId);
static dds3ProcessFunc_t slNextEpProc1st1(void);
static dds3ProcessFunc_t slNextEpProc1st2(void);
static dds3ProcessFunc_t slNextEpProcExit(void);
static dds3ProcessFunc_t slCalc(dds3ProcessID_t *id);
static dds3ProcessFunc_t slDraw(dds3ProcessID_t *id);
static dds3ProcessFunc_t slNoCard(void);
static dds3ProcessFunc_t slTop(void);
static dds3ProcessFunc_t slExit(void);
static dds3ProcessFunc_t slExit2(void);
static dds3ProcessFunc_t slExitToTitle(void);
static dds3ProcessFunc_t slExitToTitle3(void);
static dds3ProcessFunc_t slCardChk(void);
static dds3ProcessFunc_t slFileSel(void);
static dds3ProcessFunc_t slFileSelFade(dds3ProcessID_t *id);
static dds3ProcessFunc_t slEndingUpd2(void);
static dds3ProcessFunc_t slEndingExit(void);
static dds3ProcessFunc_t slSaveProc_CheckCard(dds3ProcessID_t *procId);
static dds3ProcessFunc_t slBootProc_CheckCard(dds3ProcessID_t *procId);
static dds3ProcessFunc_t slBootProc_CheckCardR(dds3ProcessID_t *procId);
static dds3ProcessFunc_t slErrorWaitMc(dds3ProcessID_t *procId);
static dds3ProcessFunc_t slErrorWait(dds3ProcessID_t *procId);
static dds3ProcessFunc_t slExitWaitProc(dds3ProcessID_t *procId);
static dds3ProcessFunc_t slHitAnyKey(nextFuncDelegate nextFunc);
static dds3ProcessFunc_t slHitAnyKeyProc(dds3ProcessID_t *procId);
static dds3ProcessFunc_t slHitAnyKeyNoChk(nextFuncDelegate nextFunc);
static dds3ProcessFunc_t slHitAnyKeyNoChkProc(dds3ProcessID_t *procId);
static dds3ProcessFunc_t slChooseData(void);
static dds3ProcessFunc_t slChooseData_B(void);
static dds3ProcessFunc_t slSaveData(void);
static dds3ProcessFunc_t slSaveData_chdir(void);
static dds3ProcessFunc_t slSaveProc_Write_mkdir(dds3ProcessID_t *procId);
static dds3ProcessFunc_t slSaveProc_Write_chdir(dds3ProcessID_t *procId);
static dds3ProcessFunc_t slSaveProc_Write_deleteIconSys(dds3ProcessID_t *procId);
static dds3ProcessFunc_t slSaveProc_doNothing(dds3ProcessID_t *procId);
static dds3ProcessFunc_t slSaveWriteEnd_iconSys(void);
static dds3ProcessFunc_t slSaveWriteEnd_baseIcon(void);
static dds3ProcessFunc_t slSaveWriteEnd_saveData(void);
static dds3ProcessFunc_t slSaveData_writeFile(bool init);
static dds3ProcessFunc_t slSaveData_deleteIconSys(void);
static dds3ProcessFunc_t slHeadLoad(void);
static dds3ProcessFunc_t slHeadLoadProc_openFile(dds3ProcessID_t *procId);
static dds3ProcessFunc_t slHeadLoadProc_readFile(dds3ProcessID_t *procId);
static dds3ProcessFunc_t slHeadLoadProc_closeFile(dds3ProcessID_t *procId);
static dds3ProcessFunc_t slLoadData(void);
static dds3ProcessFunc_t slLoadProc_openFile(dds3ProcessID_t *procId);
static dds3ProcessFunc_t slLoadProc_readFile(dds3ProcessID_t *procId);
static dds3ProcessFunc_t slLoadProc_closeFile(dds3ProcessID_t *procId);
static dds3ProcessFunc_t slLoadProc_closeFile_Wait(dds3ProcessID_t *procId);
static dds3ProcessFunc_t slFileSelCalc(dds3ProcessID_t *id);
static bool slFileFieldCheck(GameFileInfo_t *info);
static void slFileNumDraw(s32 numi, void *slot);
static dds3ProcessFunc_t slFileSelDraw(dds3ProcessID_t *id);
static dds3ProcessFunc_t slChooseData_getCardInfo(void);
static dds3ProcessFunc_t slChooseData_getCardInfo2(dds3ProcessID_t *procId);
static dds3ProcessFunc_t slChooseData_getCardInfo3(dds3ProcessID_t *procId);
static dds3ProcessFunc_t slChooseData_getCardInfoNext(void);
static dds3ProcessFunc_t slChooseData_getCardInfo_B(void);
static dds3ProcessFunc_t slChooseData_getCardInfo2_B(dds3ProcessID_t *procId);
static dds3ProcessFunc_t slChooseData_getCardInfo3_B(dds3ProcessID_t *procId);
static dds3ProcessFunc_t slChooseData_getCardInfoNext_B(void);
static dds3ProcessFunc_t slSaveWriteFile(char *filename, void *buff, s32 *size, slSaveWriteFile_endFuncDelegate endFunc, void *srcPtr);
static dds3ProcessFunc_t slQueryYesNoProc(dds3ProcessID_t *procId);
static dds3ProcessFunc_t slQueryYesNo(slQueryYesFuncDelegate yesFunc, slQueryNoFuncDelegate noFunc, s32 yesNoDefault, s16 cancelNum);
static void slQueryYesNoDraw(void);
static void slDrawError(void);
static void slDrawInfo(void);
static void slCheckMsgDraw(void);
static void slVersionConvert_Step1(void);
static s32 slVersionConvert_GetSize(void);
static void slVersionConvert_Step3(void);
static s32 slGetPadTrig(bool map);
static s32 slGetPadRep(bool map);
static void slKanjiDraw3(s32 x, s32 y, u32 rgba, char **moji, s32 ot);
static void slKanjiDrawH(s32 x, s32 y, s32 rgba, char **moji);
static void slKanjiDrawN3(s32 x, s32 y, s32 rgba, char **moji, s32 ot);
static void slNextPageDraw(void);
static void slMcAccessDraw(void);
static s32 slChkWindowOpenDone(void);
static s32 slChkWindowOpenDone2(void);
static s32 slDrawWindow(void);
static void slMCardClear(void);
static dds3ProcessFunc_t slExitWait(nextFuncDelegate nextFunc);
static dds3ProcessFunc_t slEndingTop(void);
static dds3ProcessFunc_t slBootTop(void);
static dds3ProcessFunc_t slBootRetry(void);
static dds3ProcessFunc_t slBootError(void);
static dds3ProcessFunc_t slBootError2(void);
static dds3ProcessFunc_t slExitToTitleSub(void);
static dds3ProcessFunc_t slExitToTitle2(void);
static dds3ProcessFunc_t slExitToTitle2sub(dds3ProcessID_t *procId);
static dds3ProcessFunc_t slCancel(void);
static dds3ProcessFunc_t slEndingProc1st(dds3ProcessID_t *procId);
static dds3ProcessFunc_t slBootProc1st(dds3ProcessID_t *procId);
static dds3ProcessFunc_t slHardSelect(void);
static dds3ProcessFunc_t slHardSelect1(void);
static dds3ProcessFunc_t slHardSelect2(void);
static dds3ProcessFunc_t slHardSelect2N(void);
static dds3ProcessFunc_t slHardSelect3(void);
static dds3ProcessFunc_t slHardSelect4(void);
static s32 sl1Ken(void);
static s32 slSizeChk(void);
static dds3ProcessFunc_t slErrorWaitToFileMc(dds3ProcessID_t *procId);
static dds3ProcessFunc_t slSaveProc_openFile(dds3ProcessID_t *procId);
static dds3ProcessFunc_t slSaveProc_writeFile(dds3ProcessID_t *procId);
static dds3ProcessFunc_t slSaveProc_closeFile(dds3ProcessID_t *procId);
static dds3ProcessFunc_t slSaveProc_waitDataReady(dds3ProcessID_t *procId);
static void __MC_SelectCursor_AlphaSet(s32 alpha);
static u32 __MC_RGBA_AlphaGet(u32 rgba, s32 alpha, u8 flg);
static void __MC_PanelFadeChk(void);
static void __MC_SelectCursor_AlphaAnim(void);
static void __MC_FileNumber_Draw(s32 number, s32 x, s32 y, s32 alpha);
static void __MC_MoveWindow_Set(u8 flg);
static void __MC_MoveWindow_AnimReset(void);
static void __MC_MoveWindow_Anim(void);
static void slMsgLoad(void);
static void slChoiceMsgDraw(s32 msgNum);
static void slInfoMsgDraw(s32 msgNum);
static void slMessageClose(void);
static void slMessageClear(void);
static bool slFileCheckNameLanguage(s32 select);
char *ChangeCharacter(char *sourceString, s32 charIndex, u16 newChar);

// 0x1b509e0
s32 slGetSaveDataMax(void) {
  return 20;
}

// 0x1b509f0
u8 *slUnicodeToIndexByte2(char *str) {
  void *Unicode;

  Unicode = get_Unicode(0);
  return ((u8 *(void *, char *, const MethodInfo *))Unicode->klass->vtable._16_GetBytes.methodPtr)(Unicode, str, Unicode->klass->vtable._16_GetBytes.method);
}

// 0x1b50a30
char *slByteToString(u8 *str) {
  void *Unicode;
  char *v4;

  Unicode = get_Unicode(0);
  v4 = (Unicode->klass->vtable._33_GetString.methodPtr)(Unicode, str, Unicode->klass->vtable._33_GetString.method);
  return Replace_54838864(v4, " ", "", 0);
}

// 0x1b50ac0
static char *slFileLoadMsg(char *msg, s32 cnt) {
  char *v5;
  char *v6;
  u64 *v7;
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
  s32 *v24;
  char *v25;
  char *v26;

  v5 = NewSpecific(string, 0xEu);
  v6 = "０";
  v7 = v5;
  v5[0] = "０";
  v8 = "１";
  v7[5] = "１";
  v9 = "２";
  v7[6] = "２";
  v10 = "３";
  v7[7] = "３";
  v11 = "４";
  v7[8] = "４";
  v12 = "５";
  v7[9] = "５";
  v13 = "６";
  v7[10] = "６";
  v14 = "７";
  v7[11] = "７";
  v15 = "８";
  v7[12] = "８";
  v16 = "９";
  v7[13] = "９";
  v17 = "１０";
  v7[14] = "１０";
  v18 = "１１";
  v7[15] = "１１";
  v19 = "１２";
  v7[16] = "１２";
  v20 = "１３";
  v7[17] = "１３";
  v21 = NewSpecific(string, 1u);
  v22 = "<V 0>";
  v21[0] = "<V 0>";
  v23 = Split_54845632(msg, v21, 0, 0);
  v24 = NewSpecific(s32, 2u);
  v24[0] = cnt / 10;
  v24[1] = cnt % 10;
  v25 = v23[0];
  if ((u32)(cnt + 9) >= 0x13)
    v25 = Concat_54766928(v25, v7[cnt / 10 + 4], 0);
  v26 = Concat_54766928(v25, v7[v24[1] + 4], 0);
  return Concat_54766928(v26, v23[1], 0);
}

// 0x1b50e00
void getPlayTimeToInt(u32 time, u32 **getTime) {
  u32 *v3;
  u32 v4;
  u64 v5;

  v3 = *getTime;
  if (time >= 0xCDFD7F0)
    v4 = 215996400;
  else
    v4 = time;
  v5 = (40722653 * (u64)v4) >> 43;
  v3[0] = v5;
  v3[1] = (v4 - 216000 * (u32)v5) / 0xE10;
  v3[2] = (2185 * (v4 - 3600 * ((u32)((305419897 * (u64)v4) >> 32) >> 8))) >> 17;
}

// 0x1b50e70
static dds3ProcessFunc_t slLoadProc1st(dds3ProcessID_t *procId) {
  return slTop();
}

// 0x1b51000
static dds3ProcessFunc_t slLoadProc1stBgm(dds3ProcessID_t *procId) {
  return slTop();
}

// 0x1b51070
static dds3ProcessFunc_t slSaveProc1st(dds3ProcessID_t *procId) {
  s32 tmnltype;
  Il2CppMethodPointer virtualMethodPointer;
  void *v8;
  dds3ProcessFunc_t v9;

  tmnltype = (u16)GBWK->fldSave->tmnltype;
  if (tmnltype == 2)
  {
    virtualMethodPointer = *((const MethodInfo *)slMain + 2).virtualMethodPointer;
    *((u8 *)virtualMethodPointer + 324) = 1;
    v8 = *(void *)(*((u64 *)virtualMethodPointer + 48) + 72);
    fldSetupObject(v8, 1);
    fldSetupObject(saveloadSystem->titleObj, 0);
    fldSetupObject(saveloadSystem->slotParent, 0);
    fldSetupObject(saveloadSystem->moveU, 0);
    fldSetupObject(saveloadSystem->moveD, 0);
    v9 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
    _ctor(v9, 0, Method_Project_slMain_slSaveProcEp1st__, 0);
    return v9;
  }
  else
  {
    return slTop();
  }
}

// 0x1b51250
static dds3ProcessFunc_t slSaveProcEp1st(dds3ProcessID_t *procId) {
  dds3ProcessFunc_t v3;

  slSetInfo(0);
  gslDrawFlagFile = 0;
  v3 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
  _ctor(v3, 0, Method_Project_slMain_slSaveProcEp1st1__, 0);
  return v3;
}

// 0x1b51450
static dds3ProcessFunc_t slSaveProcEp1st1(dds3ProcessID_t *procId) {
  void *titleObj;
  slQueryYesFuncDelegate v5;
  u8 *v6;
  slQueryYesFuncDelegate v7;
  intptr_t v8;
  s32 v9;
  s64 (__fastcall *method_ptr)();
  slQueryNoFuncDelegate v12;
  u8 *v13;
  slQueryNoFuncDelegate v14;
  intptr_t v15;
  s32 v16;
  s64 (__fastcall *v18)();
  void *v20;

  slQueryYesNoMsg = 11;
  titleObj = saveloadSystem->titleObj;
  fldSetupObject(titleObj, 0);
  fldSetupObject(saveloadSystem->slotParent, 0);
  fldSetupObject(saveloadSystem->moveU, 0);
  fldSetupObject(saveloadSystem->moveD, 0);
  v5 = Allocate(slQueryYesFuncDelegate);
  v6 = Method_Project_slMain_slSaveProcEp1st2__;
  v7 = v5;
  v8 = *((u64 *)Method_Project_slMain_slSaveProcEp1st2__ + 1);
  v5->method = Method_Project_slMain_slSaveProcEp1st2__;
  v5->method_ptr = v8;
  v5->m_target = 0;
  v9 = v6[82];
  v7->method_code = v7;
  if (!sub_3BDA00())
    goto LABEL_16;
  if (v9)
  {
    method_ptr = v7->method_ptr;
    v7->method_code = v7->m_target;
  }
  else
  {
    method_ptr = sub_86A0;
  }
  v7->invoke_impl = method_ptr;
  v7->extra_arg = sub_8640;
  v12 = Allocate(slQueryNoFuncDelegate);
  v13 = Method_Project_slMain_slSaveProcEp1st3__;
  v14 = v12;
  v15 = *((u64 *)Method_Project_slMain_slSaveProcEp1st3__ + 1);
  v12->method = Method_Project_slMain_slSaveProcEp1st3__;
  v12->method_ptr = v15;
  v12->m_target = 0;
  v16 = v13[82];
  v14->method_code = v14;
  if (!sub_3BDA00())
  {
LABEL_16:
    v20 = sub_3BDC90(0, "Delegate to an instance method cannot have null 'this'.");
  }
  if (v16)
  {
    v18 = v14->method_ptr;
    v14->method_code = v14->m_target;
  }
  else
  {
    v18 = sub_8770;
  }
  v14->invoke_impl = v18;
  v14->extra_arg = sub_8710;
  return slQueryYesNo(v7, v14, 0, 1);
}

// 0x1b51a10
static dds3ProcessFunc_t slSaveProcEp1st2(void) {
  return slTop();
}

// 0x1b51a80
static dds3ProcessFunc_t slSaveProcEp1st3(void) {
  dds3ProcessFunc_t v1;

  v1 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
  _ctor(v1, 0, Method_Project_slMain_slNextEpProc1st__, 0);
  return v1;
}

// 0x1b51b00
static dds3ProcessFunc_t slNextEpProc1st(dds3ProcessID_t *procId) {
  void *titleObj;
  slQueryYesFuncDelegate v5;
  u8 *v6;
  slQueryYesFuncDelegate v7;
  intptr_t v8;
  s32 v9;
  s64 (__fastcall *method_ptr)();
  slQueryNoFuncDelegate v12;
  u8 *v13;
  slQueryNoFuncDelegate v14;
  intptr_t v15;
  s32 v16;
  s64 (__fastcall *v18)();
  void *v20;

  slSetInfo(0);
  *(u64 *)&gslDrawFlagFile = 0xC00000000LL;
  slBlackScreenSet = 0;
  titleObj = saveloadSystem->titleObj;
  fldSetupObject(titleObj, 0);
  fldSetupObject(saveloadSystem->slotParent, 0);
  fldSetupObject(saveloadSystem->moveU, 0);
  fldSetupObject(saveloadSystem->moveD, 0);
  v5 = Allocate(slQueryYesFuncDelegate);
  v6 = Method_Project_slMain_slNextEpProc1st1__;
  v7 = v5;
  v8 = *((u64 *)Method_Project_slMain_slNextEpProc1st1__ + 1);
  v5->method = Method_Project_slMain_slNextEpProc1st1__;
  v5->method_ptr = v8;
  v5->m_target = 0;
  v9 = v6[82];
  v7->method_code = v7;
  if (!sub_3BDA00())
    goto LABEL_16;
  if (v9)
  {
    method_ptr = v7->method_ptr;
    v7->method_code = v7->m_target;
  }
  else
  {
    method_ptr = sub_86A0;
  }
  v7->invoke_impl = method_ptr;
  v7->extra_arg = sub_8640;
  v12 = Allocate(slQueryNoFuncDelegate);
  v13 = Method_Project_slMain_slNextEpProc1st2__;
  v14 = v12;
  v15 = *((u64 *)Method_Project_slMain_slNextEpProc1st2__ + 1);
  v12->method = Method_Project_slMain_slNextEpProc1st2__;
  v12->method_ptr = v15;
  v12->m_target = 0;
  v16 = v13[82];
  v14->method_code = v14;
  if (!sub_3BDA00())
  {
LABEL_16:
    v20 = sub_3BDC90(0, "Delegate to an instance method cannot have null 'this'.");
  }
  if (v16)
  {
    v18 = v14->method_ptr;
    v14->method_code = v14->m_target;
  }
  else
  {
    v18 = sub_8770;
  }
  v14->invoke_impl = v18;
  v14->extra_arg = sub_8710;
  return slQueryYesNo(v7, v14, 1, 1);
}

// 0x1b51d60
static dds3ProcessFunc_t slNextEpProc1st1(void) {
  nextFuncDelegate v2;
  u8 *v3;
  nextFuncDelegate v4;
  intptr_t v5;
  s32 v6;
  s64 (__fastcall *method_ptr)();
  void *v10;

  slSetInfo(0);
  v2 = Allocate(nextFuncDelegate);
  v3 = Method_Project_slMain_slExit__;
  v4 = v2;
  v5 = *((u64 *)Method_Project_slMain_slExit__ + 1);
  v2->method = Method_Project_slMain_slExit__;
  v2->method_ptr = v5;
  v2->m_target = 0;
  v6 = v3[82];
  v4->method_code = v4;
  if (!sub_3BDA00())
  {
    v10 = sub_3BDC90(0, "Delegate to an instance method cannot have null 'this'.");
  }
  if (v6)
  {
    method_ptr = v4->method_ptr;
    v4->method_code = v4->m_target;
  }
  else
  {
    method_ptr = sub_89E0;
  }
  v4->invoke_impl = method_ptr;
  v4->extra_arg = sub_8980;
  return slExitWait(v4);
}

// 0x1b52020
static dds3ProcessFunc_t slNextEpProc1st2(void) {
  dds3ProcessFunc_t v1;

  v1 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
  _ctor(v1, 0, Method_Project_slMain_slSaveProcEp1st__, 0);
  return v1;
}

// 0x1b520a0
static dds3ProcessFunc_t slNextEpProcExit(void) {
  void *titleObj;
  slQueryYesFuncDelegate v5;
  u8 *v6;
  slQueryYesFuncDelegate v7;
  intptr_t v8;
  s32 v9;
  s64 (__fastcall *method_ptr)();
  slQueryNoFuncDelegate v12;
  u8 *v13;
  slQueryNoFuncDelegate v14;
  intptr_t v15;
  s32 v16;
  s64 (__fastcall *v18)();
  void *v20;

  slSetInfo(0);
  gslErrorCode = 0;
  *(u64 *)&gslDrawFlagFile = 0xC00000000LL;
  slBlackScreenSet = 0;
  titleObj = saveloadSystem->titleObj;
  fldSetupObject(titleObj, 0);
  fldSetupObject(saveloadSystem->slotParent, 0);
  fldSetupObject(saveloadSystem->moveU, 0);
  fldSetupObject(saveloadSystem->moveD, 0);
  v5 = Allocate(slQueryYesFuncDelegate);
  v6 = Method_Project_slMain_slNextEpProc1st1__;
  v7 = v5;
  v8 = *((u64 *)Method_Project_slMain_slNextEpProc1st1__ + 1);
  v5->method = Method_Project_slMain_slNextEpProc1st1__;
  v5->method_ptr = v8;
  v5->m_target = 0;
  v9 = v6[82];
  v7->method_code = v7;
  if (!sub_3BDA00())
    goto LABEL_16;
  if (v9)
  {
    method_ptr = v7->method_ptr;
    v7->method_code = v7->m_target;
  }
  else
  {
    method_ptr = sub_86A0;
  }
  v7->invoke_impl = method_ptr;
  v7->extra_arg = sub_8640;
  v12 = Allocate(slQueryNoFuncDelegate);
  v13 = Method_Project_slMain_slNextEpProc1st2__;
  v14 = v12;
  v15 = *((u64 *)Method_Project_slMain_slNextEpProc1st2__ + 1);
  v12->method = Method_Project_slMain_slNextEpProc1st2__;
  v12->method_ptr = v15;
  v12->m_target = 0;
  v16 = v13[82];
  v14->method_code = v14;
  if (!sub_3BDA00())
  {
LABEL_16:
    v20 = sub_3BDC90(0, "Delegate to an instance method cannot have null 'this'.");
  }
  if (v16)
  {
    v18 = v14->method_ptr;
    v14->method_code = v14->m_target;
  }
  else
  {
    v18 = sub_8770;
  }
  v14->invoke_impl = v18;
  v14->extra_arg = sub_8710;
  return slQueryYesNo(v7, v14, 1, 1);
}

// 0x1b52300
static dds3ProcessFunc_t slCalc(dds3ProcessID_t *id) {
  fileHandle_t *v3;
  void *v6;
  dds3ProcessFunc_t v7;
  dds3ProcessFunc_t v8;
  Il2CppObject *topPtr;

  v3 = Allocate(fileHandle_t);
  _ctor(v3, 0);
  ++gslAnimCnt;
  slDraw(id);
  v6 = (slProcPtr->invoke_impl)(slProcPtr->method_code, id, slProcPtr->method);
  v7 = Allocate(dds3ProcessFunc_t);
  _ctor(v7, 0, Method_Project_Kernel_DDS3_PROC_END__, 0);
  if (op_Equality(v6, v7, 0))
  {
    v8 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
    _ctor(v8, 0, Method_Project_Kernel_DDS3_PROC_END__, 0);
    return v8;
  }
  if (v6)
  {
    slProcPtr = (dds3ProcessFunc_t)v6;
  }
  if (!baseIconFileHandle)
    return 0;
  v8 = 0;
  if (!fileCheckEnd(baseIconFileHandle))
    return v8;
  baseIconFileHandle = 0;
  topPtr = baseIconFileHandle->topPtr;
  baseIconPtr = topPtr;
  return 0;
}

// 0x1b52550
static dds3ProcessFunc_t slDraw(dds3ProcessID_t *id) {
  if (gslLoadWait < 1)
  {
LABEL_9:
    goto LABEL_11;
  }
  if (gslLoadWait > 599)
    goto LABEL_9;
  gslLoadWait = gslLoadWait + 1;
LABEL_11:
  if (gslDrawFlagFile)
  {
    slFileSelDraw(slMain);
  }
  slDrawInfo();
  slQueryYesNoDraw();
  slDrawError();
  return 0;
}

// 0x1b551a0
static dds3ProcessFunc_t slNoCard(void) {
  dds3ProcessFunc_t v4;

  slSetInfo(0);
  gslErrorCode = 1;
  gslErrorKeyFlag = 0;
  v4 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
  _ctor(v4, 0, Method_Project_slMain_slErrorWaitMc__, 0);
  return v4;
}

// 0x1b55270
void slGslInfoClear(void) {
  s64 v1;
  s64 i;
  s32 *gslInfo_local;
  GameFileInfo_t *v5;

  v1 = 0;
  for (i = 8; ; i += 2)
  {
    gslInfo_local = gslInfo;
    if (v1 >= gslInfo_local[6])
      break;
    if (!*(u64 *)&gslInfo_local[i])
    {
      v5 = Allocate(GameFileInfo_t);
      _ctor(v5, 0);
      if (!v5)
        goto LABEL_4;
      goto LABEL_9000;
      if (!v5)
      {
LABEL_4:
        *(u64 *)&gslInfo_local[i] = v5;
        goto LABEL_5;
      }
LABEL_9000:
      QueryInterface(v5, *(void **)(*(u64 *)gslInfo_local + 64));
      goto LABEL_4;
    }
LABEL_5:
    ++v1;
  }
}

// 0x1b50ee0
static dds3ProcessFunc_t slTop(void) {
  s32 *gslStatFileInfo_local;
  dds3ProcessFunc_t v6;

  gslStatFileInfo_local = gslStatFileInfo;
  *(u64 *)&gslStatFileInfo_local[8] = 0;
  *(_OWORD *)gslStatFileInfo_local = 0u;
  *(_OWORD *)&gslStatFileInfo_local[4] = 0u;
  *(u64 *)&gslCheckCardWait = 0x10000001ELL;
  slSetInfo(1);
  gslDrawFlagFile = 1;
  slGslInfoClear();
  cmpCmpGuideSet(44, 0, 90);
  v6 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
  _ctor(v6, 0, Method_Project_slMain_slSaveProc_CheckCard__, 0);
  return v6;
}

// 0x1b553c0
static dds3ProcessFunc_t slExit(void) {
  dds3ProcessFunc_t v4;

  slSetInfo(0);
  gslDrawFlagFile = 0;
  gslDrawFlagBg = 0;
  v4 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
  _ctor(v4, 0, Method_Project_Kernel_DDS3_PROC_END__, 0);
  return v4;
}

// 0x1b55480
static dds3ProcessFunc_t slExit2(void) {
  nextFuncDelegate v2;
  u8 *v3;
  nextFuncDelegate v4;
  intptr_t v5;
  s32 v6;
  s64 (__fastcall *method_ptr)();
  void *v10;

  slSetInfo(0);
  v2 = Allocate(nextFuncDelegate);
  v3 = Method_Project_slMain_slExit__;
  v4 = v2;
  v5 = *((u64 *)Method_Project_slMain_slExit__ + 1);
  v2->method = Method_Project_slMain_slExit__;
  v2->method_ptr = v5;
  v2->m_target = 0;
  v6 = v3[82];
  v4->method_code = v4;
  if (!sub_3BDA00())
  {
    v10 = sub_3BDC90(0, "Delegate to an instance method cannot have null 'this'.");
  }
  if (v6)
  {
    method_ptr = v4->method_ptr;
    v4->method_code = v4->m_target;
  }
  else
  {
    method_ptr = sub_89E0;
  }
  v4->invoke_impl = method_ptr;
  v4->extra_arg = sub_8980;
  return slExitWait(v4);
}

// 0x1b55590
static dds3ProcessFunc_t slExitToTitle(void) {
  dds3AdminiCallSequence2(2, 0, 0, 0);
  return 0;
}

// 0x1b55630
static dds3ProcessFunc_t slExitToTitle3(void) {
  dds3AdminiCallSequence2(2, 0, 0, 0);
  return 0;
}

// 0x1b556a0
static dds3ProcessFunc_t slCardChk(void) {
  slSetInfo(1);
  gslErrorCode = 0;
  gslDrawFlagFile = 0;
  return slTop();
}

// 0x1b55710
static dds3ProcessFunc_t slFileSel(void) {
  s64 v4;
  intptr_t *v12;
  dds3ProcessFunc_t v13;

  v4 = 0;
  gslDrawFlagFile = 1;
  gSlFileSelKyeFlg = 0;
  while (1)
  {
    if (v4 >= SLODWORD(gslInfo->max_length))
      break;
    gslStatFileInfo[v4] = 0;
    if (gslInfo[v4]->PlayTime)
    {
      gslStatFileInfo[v4] = 1;
    }
    ++v4;
  }
  checkFirstCursor(gslMode);
  if (GBWK->fldSave->tmnltype == 2)
  {
    if (!gslMode)
      goto LABEL_28;
    if (gslMode == 2)
      goto LABEL_28;
  }
  v12 = &Method_Project_slMain_slFileSelFade__;
  goto LABEL_33;
LABEL_28:
  slQueryYesNoKeyFlag = 0;
  v12 = &Method_Project_slMain_slFileSelCalc__;
LABEL_33:
  v13 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
  _ctor(v13, 0, *v12, 0);
  return v13;
}

// 0x1b55f00
static dds3ProcessFunc_t slFileSelFade(dds3ProcessID_t *id) {
  dds3ProcessFunc_t v3;

  dds3FadeIn(0, 0, 0, 8u);
  slQueryYesNoKeyFlag = 0;
  v3 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
  _ctor(v3, 0, Method_Project_slMain_slFileSelCalc__, 0);
  return v3;
}

// 0x1b55ff0
static dds3ProcessFunc_t slEndingUpd2(void) {
  slQueryYesFuncDelegate v3;
  u8 *v4;
  slQueryYesFuncDelegate v5;
  intptr_t v6;
  s32 v7;
  s64 (__fastcall *method_ptr)();
  slQueryNoFuncDelegate v10;
  u8 *v11;
  slQueryNoFuncDelegate v12;
  intptr_t v13;
  s32 v14;
  s64 (__fastcall *v16)();
  void *v18;

  slSetInfo(0);
  *(u64 *)&slQueryYesNoMsg = 9;
  v3 = Allocate(slQueryYesFuncDelegate);
  v4 = Method_Project_slMain_slSaveData__;
  v5 = v3;
  v6 = *((u64 *)Method_Project_slMain_slSaveData__ + 1);
  v3->method = Method_Project_slMain_slSaveData__;
  v3->method_ptr = v6;
  v3->m_target = 0;
  v7 = v4[82];
  v5->method_code = v5;
  if (!sub_3BDA00())
    goto LABEL_14;
  if (v7)
  {
    method_ptr = v5->method_ptr;
    v5->method_code = v5->m_target;
  }
  else
  {
    method_ptr = sub_86A0;
  }
  v5->invoke_impl = method_ptr;
  v5->extra_arg = sub_8640;
  v10 = Allocate(slQueryNoFuncDelegate);
  v11 = Method_Project_slMain_slFileSel__;
  v12 = v10;
  v13 = *((u64 *)Method_Project_slMain_slFileSel__ + 1);
  v10->method = Method_Project_slMain_slFileSel__;
  v10->method_ptr = v13;
  v10->m_target = 0;
  v14 = v11[82];
  v12->method_code = v12;
  if (!sub_3BDA00())
  {
LABEL_14:
    v18 = sub_3BDC90(0, "Delegate to an instance method cannot have null 'this'.");
  }
  if (v14)
  {
    v16 = v12->method_ptr;
    v12->method_code = v12->m_target;
  }
  else
  {
    v16 = sub_8770;
  }
  v12->invoke_impl = v16;
  v12->extra_arg = sub_8710;
  return slQueryYesNo(v5, v12, 1, 1);
}

// 0x1b561b0
static dds3ProcessFunc_t slEndingExit(void) {
  void *titleObj;
  slQueryYesFuncDelegate v5;
  u8 *v6;
  slQueryYesFuncDelegate v7;
  intptr_t v8;
  s32 v9;
  s64 (__fastcall *method_ptr)();
  slQueryNoFuncDelegate v12;
  u8 *v13;
  slQueryNoFuncDelegate v14;
  intptr_t v15;
  s32 v16;
  s64 (__fastcall *v18)();
  void *v20;

  slSetInfo(0);
  gslErrorCode = 0;
  *(u64 *)&gslDrawFlagFile = 0x800000000LL;
  slBlackScreenSet = 0;
  titleObj = saveloadSystem->titleObj;
  fldSetupObject(titleObj, 0);
  fldSetupObject(saveloadSystem->slotParent, 0);
  fldSetupObject(saveloadSystem->moveU, 0);
  fldSetupObject(saveloadSystem->moveD, 0);
  v5 = Allocate(slQueryYesFuncDelegate);
  v6 = Method_Project_slMain_slExitToTitle3__;
  v7 = v5;
  v8 = *((u64 *)Method_Project_slMain_slExitToTitle3__ + 1);
  v5->method = Method_Project_slMain_slExitToTitle3__;
  v5->method_ptr = v8;
  v5->m_target = 0;
  v9 = v6[82];
  v7->method_code = v7;
  if (!sub_3BDA00())
    goto LABEL_16;
  if (v9)
  {
    method_ptr = v7->method_ptr;
    v7->method_code = v7->m_target;
  }
  else
  {
    method_ptr = sub_86A0;
  }
  v7->invoke_impl = method_ptr;
  v7->extra_arg = sub_8640;
  v12 = Allocate(slQueryNoFuncDelegate);
  v13 = Method_Project_slMain_slEndingTop__;
  v14 = v12;
  v15 = *((u64 *)Method_Project_slMain_slEndingTop__ + 1);
  v12->method = Method_Project_slMain_slEndingTop__;
  v12->method_ptr = v15;
  v12->m_target = 0;
  v16 = v13[82];
  v14->method_code = v14;
  if (!sub_3BDA00())
  {
LABEL_16:
    v20 = sub_3BDC90(0, "Delegate to an instance method cannot have null 'this'.");
  }
  if (v16)
  {
    v18 = v14->method_ptr;
    v14->method_code = v14->m_target;
  }
  else
  {
    v18 = sub_8770;
  }
  v14->invoke_impl = v18;
  v14->extra_arg = sub_8710;
  return slQueryYesNo(v7, v14, 1, 1);
}

// 0x1b56410
static dds3ProcessFunc_t slSaveProc_CheckCard(dds3ProcessID_t *procId) {
  if (gslCheckCardWait >= 1)
  {
    gslCheckCardWait = gslCheckCardWait - 1;
    return 0;
  }
  return slChooseData();
}

// 0x1b565b0
static dds3ProcessFunc_t slBootProc_CheckCard(dds3ProcessID_t *procId) {
  if (gslCheckCardWait < 1)
    return 0;
  gslCheckCardWait = gslCheckCardWait - 1;
  return 0;
}

// 0x1b56680
static dds3ProcessFunc_t slBootProc_CheckCardR(dds3ProcessID_t *procId) {
  if (gslCheckCardWait < 1)
    return 0;
  gslCheckCardWait = gslCheckCardWait - 1;
  return 0;
}

// 0x1b56750
static dds3ProcessFunc_t slErrorWaitMc(dds3ProcessID_t *procId) {
  bool v5;
  bool v6;
  nextFuncDelegate v14;
  u8 *v15;
  intptr_t v16;
  s32 v17;
  s64 (__fastcall *method_ptr)();
  u32 v21;
  void *v23;

  gslDrawFlagFile = 0;
  if (gslErrorKeyFlag)
    goto LABEL_29;
  v5 = CHECK_TRIG(4096, 1);
  goto LABEL_9;
LABEL_13:
  if (slProcShutDownFlg != 1)
    goto LABEL_17;
LABEL_26:
  SE(1);
  gslErrorKeyFlag = 1;
  goto LABEL_29;
LABEL_9:
  if (v5)
    goto LABEL_13;
LABEL_17:
  v6 = CHECK_TRIG(4097, 1);
  if (!v6)
    goto LABEL_29;
  if (slProcShutDownFlg == 1)
    goto LABEL_26;
LABEL_29:
  if (gslErrorKeyFlag != 1)
    return 0;
  gslErrorCode = 0;
  gslDrawFlagFile = 0;
  if (gSlEndingMode)
  {
    return slEndingExit();
  }
  if (!gslMode)
    goto LABEL_45;
LABEL_43:
  if (gslMode == 5)
    goto LABEL_45;
  if (gSlCampLoad)
  {
    if (!v21)
    return slCancel();
  }
  else
  {
    if (!v21)
    return slExitToTitle2();
  }
  if (gslMode)
    goto LABEL_43;
LABEL_45:
  if (GBWK->fldSave->tmnltype == 2)
  {
    return slNextEpProcExit();
  }
  v14 = Allocate(nextFuncDelegate);
  v15 = Method_Project_slMain_slExit__;
  v16 = *((u64 *)Method_Project_slMain_slExit__ + 1);
  v14->method = Method_Project_slMain_slExit__;
  v14->method_ptr = v16;
  v14->m_target = 0;
  v17 = v15[82];
  v14->method_code = v14;
  if (!sub_3BDA00())
  {
    v23 = sub_3BDC90(0, "Delegate to an instance method cannot have null 'this'.");
  }
  if (v17)
  {
    method_ptr = v14->method_ptr;
    v14->method_code = v14->m_target;
  }
  else
  {
    method_ptr = sub_89E0;
  }
  v14->invoke_impl = method_ptr;
  v14->extra_arg = sub_8980;
  return slExitWait(v14);
}

// 0x1b56f40
static dds3ProcessFunc_t slErrorWait(dds3ProcessID_t *procId) {
  bool v2;
  bool v3;
  Il2CppMethodPointer virtualMethodPointer;

  v2 = CHECK_TRIG(4096, 1);
  if (v2)
  {
    if (slProcShutDownFlg == 1)
      goto LABEL_21;
  }
  v3 = CHECK_TRIG(4097, 1);
  if (!v3)
    return 0;
  if (slProcShutDownFlg == 1)
    goto LABEL_21;
  return 0;
LABEL_21:
  SE(0);
  virtualMethodPointer = *((const MethodInfo *)slMain + 2).virtualMethodPointer;
  *((u32 *)virtualMethodPointer + 12) = 0;
  *((u32 *)virtualMethodPointer + 10) = 0;
  return slTop();
}

// 0x1b570f0
static dds3ProcessFunc_t slExitWaitProc(dds3ProcessID_t *procId) {
  s32 v4;
  bool v5;
  dds3ProcessFunc_t v8;

  v4 = slExitWaitCnt - 1;
  v5 = slExitWaitCnt == 1;
  slExitWaitCnt = v4;
  if (v4 >= 0 && !v5)
    return 0;
  if (!slHitAnyKeyNextFunc)
  {
    v8 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
    _ctor(v8, 0, Method_Project_Kernel_DDS3_PROC_END__, 0);
    return v8;
  }
  return ((dds3ProcessFunc_t (intptr_t, intptr_t))slExitWaitNextFunc->invoke_impl)(slExitWaitNextFunc->method_code, slExitWaitNextFunc->method);
}

// 0x1b57230
static dds3ProcessFunc_t slHitAnyKey(nextFuncDelegate nextFunc) {
  dds3ProcessFunc_t v6;

  slHitAnyKeyNextFunc = nextFunc;
  gslErrorKeyFlag = 0;
  v6 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
  _ctor(v6, 0, Method_Project_slMain_slHitAnyKeyProc__, 0);
  return v6;
}

// 0x1b57300
static dds3ProcessFunc_t slHitAnyKeyProc(dds3ProcessID_t *procId) {
  bool v3;
  bool v4;
  nextFuncDelegate slHitAnyKeyNextFunc_local;
  dds3ProcessFunc_t v12;

  if (gslErrorKeyFlag)
    goto LABEL_44;
  v3 = CHECK_TRIG(4096, 1);
  if (v3)
  {
    if (slProcShutDownFlg == 1)
      goto LABEL_31;
  }
  v4 = CHECK_TRIG(4097, 1);
  if (v4)
  {
    if (slProcShutDownFlg == 1)
      goto LABEL_31;
  }
  if (gslErrorKeyNoWait != 1)
    goto LABEL_44;
LABEL_31:
  SE(0);
  gslErrorKeyFlag = 1;
  if (gslInfoCode == 31)
    goto LABEL_41;
  if (gslCursorSelect)
    goto LABEL_41;
  v12 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
  _ctor(v12, 0, Method_Project_Kernel_DDS3_PROC_END__, 0);
  return v12;
LABEL_41:
  gslErrorKeyNoWait = 0;
LABEL_44:
  if (gslErrorKeyFlag != 1)
    return 0;
  slSetInfo(0);
  gslErrorCode = 0;
  gslDrawFlagFile = 0;
  if (slHitAnyKeyNextFunc)
  {
    cmpCmpGuideSet(44, 0, 90);
    return ((dds3ProcessFunc_t (intptr_t, intptr_t))slHitAnyKeyNextFunc->invoke_impl)(slHitAnyKeyNextFunc->method_code, slHitAnyKeyNextFunc->method);
  }
  else
  {
    slHitAnyKeyNextFunc_local = 0;
    return slExitWait(slHitAnyKeyNextFunc_local);
  }
}

// 0x1b57720
static dds3ProcessFunc_t slHitAnyKeyNoChk(nextFuncDelegate nextFunc) {
  dds3ProcessFunc_t v6;

  slHitAnyKeyNextFunc = nextFunc;
  gslErrorKeyFlag = 0;
  v6 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
  _ctor(v6, 0, Method_Project_slMain_slHitAnyKeyNoChkProc__, 0);
  return v6;
}

// 0x1b577f0
static dds3ProcessFunc_t slHitAnyKeyNoChkProc(dds3ProcessID_t *procId) {
  nextFuncDelegate v8;

  slSetInfo(0);
  gslErrorCode = 0;
  if (slHitAnyKeyNextFunc)
  {
    return ((dds3ProcessFunc_t (intptr_t, intptr_t))slHitAnyKeyNextFunc->invoke_impl)(slHitAnyKeyNextFunc->method_code, slHitAnyKeyNextFunc->method);
  }
  else
  {
    v8 = 0;
    return slExitWait(v8);
  }
}

// 0x1b564f0
static dds3ProcessFunc_t slChooseData(void) {
  dds3ProcessFunc_t v2;

  gslChooseSaveIndex = 0;
  v2 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
  _ctor(v2, 0, Method_Project_slMain_slHeadLoadProc_closeFile__, 0);
  return v2;
}

// 0x1b57950
static dds3ProcessFunc_t slChooseData_B(void) {
  slSetInfo(1);
  gslDrawFlagFile = 0;
  gslChooseSaveIndex = 0;
  gslStatFileInfo[0] = 0;
  gslStatFileInfo[1] = 0;
  gslStatFileInfo[2] = 0;
  gslStatFileInfo[3] = 0;
  gslStatFileInfo[4] = 0;
  gslStatFileInfo[5] = 0;
  gslStatFileInfo[6] = 0;
  gslStatFileInfo[7] = 0;
  gslStatFileInfo[8] = 0;
  gslStatFileInfo[9] = 0;
  gslStatFileInfo[10] = 0;
  gslStatFileInfo[11] = 0;
  gslStatFileInfo[12] = 0;
  gslStatFileInfo[13] = 0;
  gslStatFileInfo[14] = 0;
  gslStatFileInfo[15] = 0;
  gslStatFileInfo[16] = 0;
  gslStatFileInfo[17] = 0;
  gslStatFileInfo[18] = 0;
  gslStatFileInfo[19] = 0;
  return slChooseData_getCardInfo_B();
}

// 0x1b57dc0
static dds3ProcessFunc_t slSaveData(void) {
  dds3ProcessFunc_t v3;

  slSetInfo(2);
  bakSelectCursor = gslCursorSelect;
  v3 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
  _ctor(v3, 0, Method_Project_slMain_slSaveProc_Write_mkdir__, 0);
  return v3;
}

// 0x1b57e80
static dds3ProcessFunc_t slSaveData_chdir(void) {
  dds3ProcessFunc_t v1;

  v1 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
  _ctor(v1, 0, Method_Project_slMain_slSaveProc_Write_chdir__, 0);
  return v1;
}

// 0x1b57f20
static dds3ProcessFunc_t slSaveProc_Write_mkdir(dds3ProcessID_t *procId) {
  dds3ProcessFunc_t v3;

  v3 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
  _ctor(v3, 0, Method_Project_slMain_slSaveProc_Write_chdir__, 0);
  return v3;
}

// 0x1b58030
static dds3ProcessFunc_t slSaveProc_Write_chdir(dds3ProcessID_t *procId) {
  dds3ProcessFunc_t v3;

  v3 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
  _ctor(v3, 0, Method_Project_slMain_slSaveProc_Write_deleteIconSys__, 0);
  return v3;
}

// 0x1b581e0
static dds3ProcessFunc_t slSaveProc_Write_deleteIconSys(dds3ProcessID_t *procId) {
  return slSaveData_writeFile(0);
}

// 0x1b58a50
SaveResultType slGetSaveResultType(void) {
  return saveData->saveResultType;
}

// 0x1b58ae0
static dds3ProcessFunc_t slSaveProc_doNothing(dds3ProcessID_t *procId) {
  s32 saveResultType;
  dds3ProcessFunc_t v9;
  nextFuncDelegate v12;
  u8 *v13;
  nextFuncDelegate v14;
  intptr_t v15;
  s32 v16;
  s64 (__fastcall *method_ptr)();
  void *v20;

  saveResultType = saveData->saveResultType;
  SE(26);
  if (!saveResultType)
  {
    slSetInfo(4);
    goto LABEL_9;
  }
  slMessageClose();
  gslErrorKeyNoWait = 1;
LABEL_9:
  if (gslMode == 5)
  {
    v9 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
    _ctor(v9, 0, Method_Project_Kernel_DDS3_PROC_END__, 0);
    return v9;
  }
  v12 = Allocate(nextFuncDelegate);
  v13 = Method_Project_slMain_slFileSel__;
  v14 = v12;
  v15 = *((u64 *)Method_Project_slMain_slFileSel__ + 1);
  v12->method = Method_Project_slMain_slFileSel__;
  v12->method_ptr = v15;
  v12->m_target = 0;
  v16 = v13[82];
  v14->method_code = v14;
  if (!sub_3BDA00())
  {
    v20 = sub_3BDC90(0, "Delegate to an instance method cannot have null 'this'.");
  }
  if (v16)
  {
    method_ptr = v14->method_ptr;
    v14->method_code = v14->m_target;
  }
  else
  {
    method_ptr = sub_89E0;
  }
  v14->invoke_impl = method_ptr;
  v14->extra_arg = sub_8980;
  return slHitAnyKey(v14);
}

// 0x1b58e50
static dds3ProcessFunc_t slSaveWriteEnd_iconSys(void) {
  dds3ProcessFunc_t v3;

  if (gslMode)
    goto LABEL_16;
  if (gslInfoCode == 2)
    goto LABEL_11;
LABEL_16:
  v3 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
  _ctor(v3, 0, Method_Project_slMain_slSaveProc_doNothing__, 0);
  return v3;
LABEL_11:
  if (saveMsgCounter > 59)
  {
LABEL_15:
    saveMsgCounter = 0;
    goto LABEL_16;
  }
  if (saveData->saveResultType)
  {
    goto LABEL_15;
  }
  return 0;
}

// 0x1b59040
static dds3ProcessFunc_t slSaveWriteEnd_baseIcon(void) {
  slSaveWriteFile_endFuncDelegate v3;
  u8 *v4;
  slSaveWriteFile_endFuncDelegate v5;
  intptr_t v6;
  s32 v7;
  _BOOL8 v8;
  s64 (__fastcall *method_ptr)();
  void *v13;

  v3 = Allocate(slSaveWriteFile_endFuncDelegate);
  v4 = Method_Project_slMain_slSaveWriteEnd_iconSys__;
  v5 = v3;
  v6 = *((u64 *)Method_Project_slMain_slSaveWriteEnd_iconSys__ + 1);
  v3->method = Method_Project_slMain_slSaveWriteEnd_iconSys__;
  v3->method_ptr = v6;
  v3->m_target = 0;
  v7 = v4[82];
  v5->method_code = v5;
  v8 = sub_3BDA00();
  if (!v8)
  {
    v13 = sub_3BDC90(0, "Delegate to an instance method cannot have null 'this'.");
  }
  if (v7)
  {
    method_ptr = v5->method_ptr;
    v5->method_code = v5->m_target;
  }
  else
  {
    method_ptr = sub_8840;
  }
  v5->invoke_impl = method_ptr;
  v5->extra_arg = sub_87E0;
  return slSaveWriteFile(v8, icon_sys_ptr, &icon_sys_size, v5, 0);
}

// 0x1b59330
static dds3ProcessFunc_t slSaveWriteEnd_saveData(void) {
  slSaveWriteFile_endFuncDelegate v3;
  u8 *v4;
  slSaveWriteFile_endFuncDelegate v5;
  intptr_t v6;
  s32 v7;
  _BOOL8 v8;
  s64 (__fastcall *method_ptr)();
  void *v13;

  v3 = Allocate(slSaveWriteFile_endFuncDelegate);
  v4 = Method_Project_slMain_slSaveWriteEnd_baseIcon__;
  v5 = v3;
  v6 = *((u64 *)Method_Project_slMain_slSaveWriteEnd_baseIcon__ + 1);
  v3->method = Method_Project_slMain_slSaveWriteEnd_baseIcon__;
  v3->method_ptr = v6;
  v3->m_target = 0;
  v7 = v4[82];
  v5->method_code = v5;
  v8 = sub_3BDA00();
  if (!v8)
  {
    v13 = sub_3BDC90(0, "Delegate to an instance method cannot have null 'this'.");
  }
  if (v7)
  {
    method_ptr = v5->method_ptr;
    v5->method_code = v5->m_target;
  }
  else
  {
    method_ptr = sub_8840;
  }
  v5->invoke_impl = method_ptr;
  v5->extra_arg = sub_87E0;
  return slSaveWriteFile(v8, baseIconPtr, &baseIconSize, v5, 0);
}

// 0x1b59470
dds3ProcessFunc_t slSystemDataProc(void) {
  slSaveWriteFile_endFuncDelegate v5;
  u8 *v6;
  slSaveWriteFile_endFuncDelegate v7;
  intptr_t v8;
  s32 v9;
  _BOOL8 v10;
  s64 (__fastcall *method_ptr)();
  void *v15;

  gslMode = 5;
  gslCursorSelect = -1;
  v5 = Allocate(slSaveWriteFile_endFuncDelegate);
  v6 = Method_Project_slMain_slSaveWriteEnd_iconSys__;
  v7 = v5;
  v8 = *((u64 *)Method_Project_slMain_slSaveWriteEnd_iconSys__ + 1);
  v5->method = Method_Project_slMain_slSaveWriteEnd_iconSys__;
  v5->method_ptr = v8;
  v5->m_target = 0;
  v9 = v6[82];
  v7->method_code = v7;
  v10 = sub_3BDA00();
  if (!v10)
  {
    v15 = sub_3BDC90(0, "Delegate to an instance method cannot have null 'this'.");
  }
  if (v9)
  {
    method_ptr = v7->method_ptr;
    v7->method_code = v7->m_target;
  }
  else
  {
    method_ptr = sub_8840;
  }
  v7->invoke_impl = method_ptr;
  v7->extra_arg = sub_87E0;
  return slSaveWriteFile(v10, wk_ptr, &wk_size, v7, 0);
}

// 0x1b595b0
void slInfoBackUp(void) {
  s64 v1;
  s64 i;
  u64 *v3;
  GameFileInfo_t *gslInfo_back_local;
  GameFileInfo_t *v7;

  v1 = 0;
  for (i = 32; ; i += 8)
  {
    if (v1 >= SLODWORD(gslInfo_back->max_length))
      break;
    if (!*(Il2CppClass **)((char *)&gslInfo->obj.klass + i))
    {
      v3 = ((char *)&gslInfo_back->obj.klass + i);
      *v3 = 0;
      goto LABEL_7;
    }
    gslInfo_back_local = gslInfo_back;
    v7 = Allocate(GameFileInfo_t);
    _ctor(v7, 0);
    *(Il2CppClass **)((char *)&gslInfo_back_local->obj.klass + i) = v7;
    ClassCopy(*(GameFileInfo_t *)((char *)&gslInfo_back->obj.klass + i), *(GameFileInfo_t *)((char *)&gslInfo->obj.klass + i), 0);
LABEL_7:
    ++v1;
  }
}

// 0x1b59730
void slInfoBackUpClear(void) {
  s64 v2;
  s64 i;
  u64 *v4;
  GameFileInfo_t *gslInfo_back_local;
  GameFileInfo_t *v6;

  v2 = 0;
  for (i = 32; ; i += 8)
  {
    gslInfo_back_local = gslInfo_back;
    if (v2 >= SLODWORD(gslInfo_back_local->max_length))
      break;
    v6 = *(GameFileInfo_t *)((char *)&gslInfo_back_local->obj.klass + i);
    if (v6)
    {
      v6 = *(GameFileInfo_t *)((char *)&gslInfo_back->obj.klass + i);
      ClassClear(v6, 0);
      v4 = ((char *)&gslInfo_back->obj.klass + i);
      *v4 = 0;
    }
    ++v2;
  }
}

// 0x1b59840
void slInfoBackUpRestore(void) {
  s64 v1;
  s64 i;
  GameFileInfo_t *gslInfo_back_local;
  GameFileInfo_t *gslInfo_local;
  GameFileInfo_t *v7;

  v1 = 0;
  for (i = 32; ; i += 8)
  {
    gslInfo_back_local = gslInfo_back;
    if (v1 >= SLODWORD(gslInfo_back_local->max_length))
      break;
    if (!!*(Il2CppClass **)((char *)&gslInfo_back_local->obj.klass + i))
    {
      gslInfo_local = gslInfo;
      v7 = Allocate(GameFileInfo_t);
      _ctor(v7, 0);
      *(Il2CppClass **)((char *)&gslInfo_local->obj.klass + i) = v7;
      ClassCopy(*(GameFileInfo_t *)((char *)&gslInfo->obj.klass + i), *(GameFileInfo_t *)((char *)&gslInfo_back->obj.klass + i), 0);
    }
    ++v1;
  }
}

// 0x1b58270
static dds3ProcessFunc_t slSaveData_writeFile(bool init) {
  bool v2;
  u16 *v5;
  char *String_54864672;
  GameFileInfo_t *GameFileInfo;
  f64 totalPlayTime;
  Save_t *fldSave;
  u8 tmnltype;
  f64 v14;
  s32 v15;
  u8 ConfigGAME;
  dds3GlobalWork_t *v19;
  sdatPlayerUnitWork_t *player;
  GameFileInfo_t *v21;
  SaveTimeInfo_t *saveTime;
  s32 Year;
  SaveTimeInfo_t *v25;
  s32 Month;
  SaveTimeInfo_t *v28;
  s32 Day;
  SaveTimeInfo_t *v31;
  s32 Hour;
  SaveTimeInfo_t *v34;
  s32 Minute;
  SaveTimeInfo_t *v37;
  s32 Second;
  dds3GlobalWork_t *v40;
  GameFileInfo_t *v41;
  char *player_first;
  dds3GlobalWork_t *v43;
  GameFileInfo_t *v44;
  char *player_family;
  s64 v46;
  dds3GlobalWork_t *v47;
  GameFileInfo_t *v48;
  GameFileInfo_t *v49;
  GameFileInfo_t *v51;
  GameFileInfo_t *v52;
  GameFileInfo_t *v55;
  u32 v57;
  GlobalWork_t *static_fields;
  s32 fieldID;
  s32 floorID;
  GameFileInfo_t *v62;
  GameFileInfo_t *v63;
  u32 v65;
  GameFileInfo_t *v66;
  GameFileInfo_t *v70;
  char *v71;
  GameFileInfo_t *v72;
  char *v73;
  dds3GlobalWork_t *v75;
  GameFileInfo_t *v76;
  GameFileInfo_t *v77;
  slSaveWriteFile_endFuncDelegate v80;
  u8 *v81;
  slSaveWriteFile_endFuncDelegate v82;
  intptr_t v83;
  s32 v84;
  _BOOL8 v85;
  s64 (__fastcall *method_ptr)();
  void *v89;
  u64 dateData;

  v2 = init;
  dateData = 0;
  v5 = NewSpecific(char, 0x44u);
  String_54864672 = CreateString_54864672(0, v5, 0);
  slInfoBackUp();
  saveDataInit = v2;
  GBWK->GameFileInfo->verstr[0] = 86;
  GBWK->GameFileInfo->verstr[1] = 69;
  GBWK->GameFileInfo->verstr[2] = 82;
  GameFileInfo = GBWK->GameFileInfo;
  totalPlayTime = GBWK->totalPlayTime;
  GameFileInfo->ver = 1;
  fldSave = GBWK->fldSave;
  tmnltype = fldSave->tmnltype;
  LOBYTE(fldSave) = fldSave->tmnlid;
  v14 = totalPlayTime * 60.0;
  GameFileInfo->TmnlMode = tmnltype;
  GameFileInfo->TmnlId = (u8)fldSave;
  v15 = v14;
  if (v14 >= 0.0)
    v15 = (u32)v14;
  GameFileInfo->PlayTime = v15;
  ConfigGAME = cfgGetConfigGAME(1, 0);
  GameFileInfo->Mode = ConfigGAME;
  v19 = GBWK;
  player = v19->player;
  v21 = v19->GameFileInfo;
  saveTime = v21->saveTime;
  v21->Lv = player->para->level;
  dateData = get_Now(0)._dateData;
  Year = get_Year((System_DateTime_o)&dateData, 0);
  saveTime->Year = Year;
  v25 = GBWK->GameFileInfo->saveTime;
  dateData = get_Now(0)._dateData;
  Month = get_Month((System_DateTime_o)&dateData, 0);
  v25->Month = Month;
  v28 = GBWK->GameFileInfo->saveTime;
  dateData = get_Now(0)._dateData;
  Day = get_Day((System_DateTime_o)&dateData, 0);
  v28->Day = Day;
  v31 = GBWK->GameFileInfo->saveTime;
  dateData = get_Now(0)._dateData;
  Hour = get_Hour((System_DateTime_o)&dateData, 0);
  v31->Hour = Hour;
  v34 = GBWK->GameFileInfo->saveTime;
  dateData = get_Now(0)._dateData;
  Minute = get_Minute((System_DateTime_o)&dateData, 0);
  v34->Minute = Minute;
  v37 = GBWK->GameFileInfo->saveTime;
  dateData = get_Now(0)._dateData;
  Second = get_Second((System_DateTime_o)&dateData, 0);
  v37->Second = Second;
  v40 = GBWK;
  v41 = v40->GameFileInfo;
  player_first = v40->player_first;
  v41->player_first = player_first;
  v43 = GBWK;
  v44 = v43->GameFileInfo;
  player_family = v43->player_family;
  v44->player_family = player_family;
  v46 = gslCursorSelect;
  v47 = GBWK;
  v48 = v47->GameFileInfo;
  v49 = gslInfo[gslCursorSelect];
  v48->nameLang = v47->name_language;
  v49->verstr[0] = v48->verstr[0];
  gslInfo[gslCursorSelect]->verstr[1] = GBWK->GameFileInfo->verstr[1];
  gslInfo[gslCursorSelect]->verstr[2] = GBWK->GameFileInfo->verstr[2];
  v51 = GBWK->GameFileInfo;
  v52 = gslInfo[gslCursorSelect];
  v52->PlayTime = v51->PlayTime;
  *(u32 *)&v52->endcnt = *(u32 *)&v51->endcnt;
  *(u32 *)&v52->ver = *(u32 *)&v51->ver;
  LOBYTE(v48) = v51->Lv;
  v52->chapter = v51->chapter;
  v52->Lv = (u8)v48;
  if ((u32)v51)
  {
    if (lmapwk)
      goto LABEL_15;
  }
  else
  {
    if (lmapwk)
    {
LABEL_15:
      v55 = GBWK->GameFileInfo;
      *(u32 *)&v55->fieldID = 0;
      LOWORD(static_fields) = *(u16 *)(*(u64 *)(*(u64 *)&call_map_now + 16) + 120);
      v55->basyoID = (s16)static_fields;
      if (v57)
      {
        LOWORD(fieldID) = 0;
        LOWORD(floorID) = 0;
      }
      else
      {
        LOWORD(fieldID) = 0;
        LOWORD(floorID) = 0;
        LOWORD(static_fields) = lmapwk->chrwk->basePointNo;
      }
      goto LABEL_30;
    }
  }
  v62 = GBWK->GameFileInfo;
  v63 = GBWK->GameFileInfo;
  static_fields = fldGb;
  LODWORD(static_fields) = basyo_name;
  v63->floorID = floorID;
  v63->basyoID = (s16)static_fields;
  v62->fieldID = fieldID;
  if (!v65)
  {
    static_fields = fldGb;
    LODWORD(static_fields) = basyo_name;
  }
LABEL_30:
  v66 = gslInfo[gslCursorSelect];
  v66->basyoID = (s16)static_fields;
  v66->fieldID = fieldID;
  v66->floorID = floorID;
  v70 = gslInfo[gslCursorSelect];
  v71 = GBWK->GameFileInfo->player_first;
  v70->player_first = v71;
  v72 = gslInfo[v46];
  v73 = GBWK->GameFileInfo->player_family;
  v72->player_family = v73;
  v75 = GBWK;
  v76 = v75->GameFileInfo;
  v77 = gslInfo[v46];
  wk_ptr = v75;
  v77->saveTime->fields = v76->saveTime->fields;
  v77->nameLang = v76->nameLang;
  v80 = Allocate(slSaveWriteFile_endFuncDelegate);
  v81 = Method_Project_slMain_slSaveWriteEnd_iconSys__;
  v82 = v80;
  v83 = *((u64 *)Method_Project_slMain_slSaveWriteEnd_iconSys__ + 1);
  v80->method = Method_Project_slMain_slSaveWriteEnd_iconSys__;
  v80->method_ptr = v83;
  v80->m_target = 0;
  v84 = v81[82];
  v82->method_code = v82;
  v85 = sub_3BDA00();
  if (!v85)
  {
    v89 = sub_3BDC90(0, "Delegate to an instance method cannot have null 'this'.");
  }
  if (v84)
  {
    method_ptr = v82->method_ptr;
    v82->method_code = v82->m_target;
  }
  else
  {
    method_ptr = sub_8840;
  }
  v82->invoke_impl = method_ptr;
  v82->extra_arg = sub_87E0;
  return slSaveWriteFile(v85, wk_ptr, &wk_size, v82, 0);
}

// 0x1b58140
static dds3ProcessFunc_t slSaveData_deleteIconSys(void) {
  dds3ProcessFunc_t v1;

  v1 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
  _ctor(v1, 0, Method_Project_slMain_slSaveProc_Write_deleteIconSys__, 0);
  return v1;
}

// 0x1b59990
static dds3ProcessFunc_t slHeadLoad(void) {
  u16 *v1;
  char *String_54864672;
  dds3ProcessFunc_t v3;

  v1 = NewSpecific(char, 0x44u);
  String_54864672 = CreateString_54864672(0, v1, 0);
  ChangeCharacter(String_54864672, 0, 0x2Fu);
  v3 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
  _ctor(v3, 0, Method_Project_slMain_slHeadLoadProc_openFile__, 0);
  return v3;
}

// 0x1b59a80
static dds3ProcessFunc_t slHeadLoadProc_openFile(dds3ProcessID_t *procId) {
  dds3ProcessFunc_t v2;

  v2 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
  _ctor(v2, 0, Method_Project_slMain_slHeadLoadProc_readFile__, 0);
  return v2;
}

// 0x1b59b10
static dds3ProcessFunc_t slHeadLoadProc_readFile(dds3ProcessID_t *procId) {
  dds3ProcessFunc_t v2;

  v2 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
  _ctor(v2, 0, Method_Project_slMain_slHeadLoadProc_closeFile__, 0);
  return v2;
}

// 0x1b59ba0
static dds3ProcessFunc_t slHeadLoadProc_closeFile(dds3ProcessID_t *procId) {
  s64 v4;

  if (gslChooseSaveIndex == 20)
  {
    v4 = 0;
    goto LABEL_13;
  }
  if (gslChooseSaveIndex == 21)
  {
    v4 = 1;
    goto LABEL_13;
  }
  else
  {
    v4 = gslChooseSaveIndex + 2;
    goto LABEL_13;
  }
LABEL_13:
  loadHeaderGameFileInfo(saveData, gslChooseSaveIndex, &gslInfo[v4], 0);
  return slChooseData_getCardInfoNext();
}

// 0x1b59df0
static dds3ProcessFunc_t slLoadData(void) {
  dds3ProcessFunc_t v6;

  gslLoadWait = 1;
  slSetInfo(3);
  bakSelectCursor = gslCursorSelect;
  v6 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
  _ctor(v6, 0, Method_Project_slMain_slLoadProc_openFile__, 0);
  return v6;
}

// 0x1b59f50
static dds3ProcessFunc_t slLoadProc_openFile(dds3ProcessID_t *procId) {
  s32 v10;
  dds3GlobalWork_t *p_GBWK;
  dds3AdditionWork_t *p_AdditionWork;
  s32 v16;
  dds3ProcessFunc_t v18;

  setAutoSaveDisable();
  if (!gslCursorSelect)
  {
    v10 = 20;
    p_GBWK = &GBWK;
    p_AdditionWork = &AdditionWork;
    goto LABEL_29;
  }
  if (gslCursorSelect == 1)
  {
    v10 = 21;
    p_GBWK = &GBWK;
    p_AdditionWork = &AdditionWork;
    goto LABEL_29;
  }
  v16 = gslCursorSelect;
  v10 = v16 - 2;
  p_AdditionWork = &AdditionWork;
  p_GBWK = &GBWK;
LABEL_29:
  loadMode = Load_30416560(saveData, v10, p_GBWK, p_AdditionWork, 0);
  v18 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
  _ctor(v18, 0, Method_Project_slMain_slLoadProc_readFile__, 0);
  return v18;
}

// 0x1b5a270
static dds3ProcessFunc_t slLoadProc_readFile(dds3ProcessID_t *procId) {
  dds3ProcessFunc_t v2;

  v2 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
  _ctor(v2, 0, Method_Project_slMain_slLoadProc_closeFile__, 0);
  return v2;
}

// 0x1b5a310
static dds3ProcessFunc_t slLoadProc_closeFile(dds3ProcessID_t *procId) {
  dds3ProcessFunc_t v2;

  v2 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
  _ctor(v2, 0, Method_Project_slMain_slLoadProc_closeFile_Wait__, 0);
  return v2;
}

// 0x1b5a3d0
static dds3ProcessFunc_t slLoadProc_closeFile_Wait(dds3ProcessID_t *procId) {
  s32 newfile;

  if (gslLoadWait < 60)
    return 0;
  SE(27);
  slSetInfo(13);
  sndBgmFadeOut();
  newfile = GBWK->GameFileInfo->newfile;
  if (newfile == 1)
  {
    return slHardSelect();
  }
  else
  {
    return slHitAnyKeyNoChk(0);
  }
}

// 0x1b5a6a0
static dds3ProcessFunc_t slFileSelCalc(dds3ProcessID_t *id) {
  s32 v5;
  __MC_GLOBALWORK *mc_wk;
  u32 cursorcnt;
  s32 v9;
  bool v11;
  s32 v12;
  __MC_GLOBALWORK *v15;
  s32 v16;
  bool v17;
  __MC_GLOBALWORK *v20;
  s32 v21;
  s32 v22;
  __MC_GLOBALWORK *v23;
  __MC_GLOBALWORK *v27;
  bool v28;
  __MC_GLOBALWORK *v31;
  s32 v32;
  __MC_GLOBALWORK *v34;
  s32 v37;
  s32 v39;
  bool v41;
  __MC_GLOBALWORK *v44;
  s32 v46;
  s32 v47;
  __MC_GLOBALWORK *v48;
  s32 v52;
  bool v53;
  u32 v54;
  u32 v57;
  s32 v58;
  s32 v59;
  bool v61;
  bool v64;
  s32 v66;
  bool v67;
  u32 v70;
  s32 v74;
  __MC_GLOBALWORK *v78;
  u32 v80;
  bool v82;
  u32 PlayTime;
  u32 v85;
  slQueryYesFuncDelegate v88;
  u8 *v89;
  intptr_t v90;
  s32 v91;
  s64 (__fastcall *method_ptr)();
  u8 *v93;
  intptr_t v94;
  s32 v95;
  s64 (__fastcall *v96)();
  slQueryNoFuncDelegate v99;
  u8 *v100;
  intptr_t v101;
  s32 v102;
  s64 (__fastcall *v104)();
  u32 v105;
  bool v107;
  nextFuncDelegate v110;
  u8 *v113;
  intptr_t v114;
  s32 v115;
  slQueryYesFuncDelegate v116;
  slQueryNoFuncDelegate v117;
  s32 v118;
  _BOOL4 v123;
  slQueryYesFuncDelegate v124;
  slQueryNoFuncDelegate v126;
  dds3ProcessFunc_t v128;
  void *v130;

  if (gSlFileSelKyeFlg)
    goto LABEL_211;
  v5 = gslCursorSelect;
  mc_wk = __mc_wk;
  cursorcnt = mc_wk->cursorcnt;
  mc_wk->cursorcnt = cursorcnt + 1;
  if (cursorcnt <= 0x7FFFFFFE)
  {
    if ((s32)(cursorcnt + 1) > 3)
    {
      v9 = 4;
      goto LABEL_17;
    }
  }
  v9 = __mc_wk->cursorcnt;
LABEL_17:
  mc_wk->cursorcnt = v9;
  v11 = CHECK_REP(4100, 1);
  v12 = v5 - gslCursorTop;
  if (!v11)
    goto LABEL_29;
  if (slProcShutDownFlg == 1)
    goto LABEL_27;
LABEL_29:
  v16 = 0;
  goto LABEL_30;
LABEL_27:
  v15 = __mc_wk;
  if (v15->cursorcnt < 4)
    goto LABEL_29;
  v15 = __mc_wk;
  v15->cursorcnt = 0;
  v22 = gslCursorTop;
  if (v22 <= SlotDataTop)
  {
    v12 -= v12 > 0;
  }
  else
  {
    if (v12 == 1)
    {
      v22 = gslCursorTop;
      gslCursorTop = v22 - 1;
      __MC_MoveWindow_Set(2u);
      __MC_SelectCursor_AlphaSet(128);
    }
    else if (v12 != 2)
    {
      goto LABEL_69;
    }
    v12 = 1;
  }
LABEL_69:
  v16 = -1;
LABEL_30:
  v17 = CHECK_REP(4101, 1);
  if (!v17)
    goto LABEL_77;
  if (slProcShutDownFlg == 1)
  {
    v20 = __mc_wk;
    if (v20->cursorcnt >= 4)
    {
      v20 = __mc_wk;
      v20->cursorcnt = 0;
      v21 = gslCursorTop;
      if (v21 > 18)
      {
        if (v12 < 2)
          ++v12;
        goto LABEL_76;
      }
      if (!v12)
      {
        v16 = 1;
        v12 = 1;
        goto LABEL_77;
      }
      if (v12 < 1)
        goto LABEL_76;
      gslCursorTop = v21 + 1;
      v23 = __mc_wk;
      v23->mvflg = 1;
      v23->mv_y = 0;
      *(u64 *)&v23->u_alpha = 116;
      v27 = __mc_wk;
      __mc_scwk->alpha = 128;
      v27->alpha = 128;
      v27->cnt = 0;
LABEL_76:
      v16 = 1;
      goto LABEL_77;
    }
  }
LABEL_77:
  v28 = CHECK_REP(4102, 1);
  if (!v28)
    goto LABEL_114;
  if (slProcShutDownFlg == 1)
  {
    v31 = __mc_wk;
    if (v31->cursorcnt >= 4)
    {
      v31 = __mc_wk;
      v31->cursorcnt = 0;
      v32 = gslCursorTop;
      bakCursorTop = v32;
      if (v32 <= SlotDataTop)
      {
        v12 -= v12 > 0;
        goto LABEL_113;
      }
      v34 = __mc_wk;
      v34->mvflg = 3;
      v34->mv_y = 0;
      *(u64 *)&v34->u_alpha = 0x7400000000LL;
      if (v12 == 1)
      {
        v39 = gslCursorTop - 3;
        gslCursorTop = v39;
        if (v39 >= SlotDataTop)
        {
          v12 = 1;
          goto LABEL_113;
        }
        gslCursorTop = SlotDataTop;
        v12 = v39 > SlotDataTop;
        goto LABEL_113;
      }
      if (v12 == 2)
      {
        v12 = 1;
        v37 = gslCursorTop - 2;
        gslCursorTop = v37;
      }
LABEL_113:
      v16 = -1;
      goto LABEL_114;
    }
  }
LABEL_114:
  v41 = CHECK_REP(4103, 1);
  goto LABEL_116;
LABEL_120:
  if (slProcShutDownFlg != 1)
    goto LABEL_126;
  v44 = __mc_wk;
  if (v44->cursorcnt < 4)
    goto LABEL_126;
  v44 = __mc_wk;
  v44->cursorcnt = 0;
  v47 = gslCursorTop;
  bakCursorTop = v47;
  if (v47 > 18)
  {
    if (v12 < 2)
      ++v12;
    goto LABEL_155;
  }
  v48 = __mc_wk;
  v48->mvflg = 3;
  v48->mv_y = 0;
  *(u64 *)&v48->u_alpha = 0x7400000000LL;
  if (!v12)
  {
    v16 = 1;
    v12 = 1;
    gslCursorTop += 2;
LABEL_127:
    v46 = gslCursorTop;
    gslCursorSelect = v46 + v12;
    if (autoSaveOpenFlg)
      goto LABEL_162;
    goto LABEL_157;
  }
  v52 = gslCursorTop + 3;
  v53 = gslCursorTop - 17 < 0;
  gslCursorTop = v52;
  if (v53 == __OFSUB__(v52, 20))
  {
    if (!v54)
    {
      v52 = gslCursorTop;
    }
    if (v52 + v12 >= SLODWORD(saveloadSystem->slotData->max_length))
      v12 = 2;
    gslCursorTop = 19;
  }
LABEL_155:
  v16 = 1;
  goto LABEL_127;
LABEL_116:
  if (v41)
    goto LABEL_120;
LABEL_126:
  goto LABEL_127;
LABEL_157:
  if (v46 != 1)
    goto LABEL_171;
  gslCursorTop += v16;
  goto LABEL_171;
LABEL_172:
  gslCursorSelect = v16 + 1;
LABEL_163:
  if (gslCursorSelect == gslCursorSelect)
    goto LABEL_164;
  goto LABEL_175;
LABEL_171:
  if (gslCursorSelect == 1)
    goto LABEL_172;
LABEL_162:
  goto LABEL_163;
  if (gslCursorSelect == gslCursorSelect)
  {
LABEL_164:
    goto LABEL_165;
  }
LABEL_175:
  SE(3);
LABEL_165:
  v58 = gslCursorSelect;
  if (gslCursorSelect > v58)
  {
    v59 = -12;
    if (v57)
    {
LABEL_168:
      gslCursorZanzouCnt = v59;
      goto LABEL_182;
    }
    goto LABEL_168;
  }
  if (!v57)
  {
    v58 = gslCursorSelect;
  }
  if (gslCursorSelect < v58)
  {
    v59 = 12;
    goto LABEL_168;
  }
LABEL_182:
  v61 = CHECK_TRIG(4096, 0);
  if (v61)
  {
    if (slProcShutDownFlg == 1)
    {
      v64 = slFileCheckNameLanguage(gslCursorSelect);
      if (v64)
        v66 = 1;
      else
        v66 = 20;
      gSlFileSelKyeFlg = v66;
    }
  }
  v67 = CHECK_TRIG(4097, 1);
  if (!v67)
    goto LABEL_211;
  if (slProcShutDownFlg == 1)
  {
    gSlFileSelKyeFlg = 2;
  }
LABEL_211:
  if (!gSlFileSelKyeFlg)
    return 0;
  if (gSlFileSelKyeFlg == 1)
    goto LABEL_215;
  if (v70)
  {
    if (gSlFileSelKyeFlg == 2)
      goto LABEL_223;
  }
  else
  {
    if (gSlFileSelKyeFlg == 2)
    {
LABEL_223:
      SE(1);
LABEL_226:
      v78 = __mc_wk;
      v78->mv_y = 0;
      v78->mvflg = 0;
      v78->cnt = 0;
      if (gSlEndingMode)
      {
        if (!v80)
        return slEndingExit();
      }
      else
      {
        if (gslMode)
        {
          if (gslMode != 2)
            goto LABEL_364;
        }
        if (GBWK->fldSave->tmnltype == 2)
        {
          return slNextEpProcExit();
        }
        else
        {
LABEL_364:
          return slCancel();
        }
      }
      goto LABEL_226;
    }
  }
  if (gSlFileSelKyeFlg != 21)
  {
LABEL_308:
    if (gSlFileSelKyeFlg == 20)
    {
      slSetInfo(20);
      gSlFileSelKyeFlg = 21;
      return 0;
    }
    return 0;
  }
  v82 = CHECK_TRIG(4096, 1);
  if (!v82)
    goto LABEL_308;
  if (slProcShutDownFlg == 1)
  {
    slSetInfo(0);
    gSlFileSelKyeFlg = 1;
  }
  goto LABEL_308;
LABEL_215:
  if (v70)
  {
    slSetInfo(0);
    v74 = gslMode;
    if (!v74)
      goto LABEL_245;
  }
  else
  {
    slSetInfo(0);
    v74 = gslMode;
    if (!v74)
      goto LABEL_245;
  }
  if (v74 == 2)
    goto LABEL_245;
  goto LABEL_243;
  if (v74 != 2)
  {
LABEL_243:
    if (v74 == 5)
      goto LABEL_245;
    if (!slFileFieldCheck(gslInfo[gslCursorSelect]))
    {
      SE(0);
      v110 = Allocate(nextFuncDelegate);
      _ctor(v110, 0);
      return slHitAnyKey(v110);
    }
    if (!SaveStremingCheck(gslInfo[gslCursorSelect]) || InstallCheck())
    {
      v107 = MesEnd();
      if (v107)
      {
LABEL_299:
        gSlFileSelKyeFlg = 0;
        streamingMes = 0;
LABEL_353:
        v128 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
        _ctor(v128, 0, Method_Project_slMain_slFileSelCalc__, 0);
        return v128;
      }
LABEL_342:
      if (gslInfo[gslCursorSelect]->PlayTime)
      {
        SE(0);
        slQueryYesNoMsg = 3;
        v123 = gslMode != 4;
        v124 = Allocate(slQueryYesFuncDelegate);
        _ctor(v124, 0);
        v126 = Allocate(slQueryNoFuncDelegate);
        _ctor(v126, 0);
        v116 = v124;
        v117 = v126;
        v118 = v123;
        return slQueryYesNo(v116, v117, v118, 1);
      }
      gSlFileSelKyeFlg = 0;
      SE(2);
      goto LABEL_353;
    }
    if (!streamingMes)
    {
      SE(0);
      CallMes();
      streamingMes = 1;
      return 0;
    }
    if (streamingMes != 1)
      goto LABEL_342;
    if (!MesCheck())
    {
      goto LABEL_299;
    }
    return 0;
  }
LABEL_245:
  PlayTime = gslInfo[gslCursorSelect]->PlayTime;
  SE(0);
  if (PlayTime)
  {
    if (v85)
    {
      if (gSlEndingMode)
        goto LABEL_250;
    }
    else
    {
      if (gSlEndingMode)
      {
LABEL_250:
        gSlSaveMode = 1;
        slQueryYesNoMsg = 1;
        v88 = Allocate(slQueryYesFuncDelegate);
        v89 = Method_Project_slMain_slEndingUpd2__;
        v90 = *((u64 *)Method_Project_slMain_slEndingUpd2__ + 1);
        v88->method = Method_Project_slMain_slEndingUpd2__;
        v88->method_ptr = v90;
        v88->m_target = 0;
        v91 = v89[82];
        v88->method_code = v88;
        if (sub_3BDA00())
        {
          if (v91)
          {
            method_ptr = v88->method_ptr;
            v88->method_code = v88->m_target;
          }
          else
          {
            method_ptr = sub_86A0;
          }
          v88->invoke_impl = method_ptr;
          v88->extra_arg = sub_8640;
          v99 = Allocate(slQueryNoFuncDelegate);
          v100 = Method_Project_slMain_slFileSel__;
          v101 = *((u64 *)Method_Project_slMain_slFileSel__ + 1);
          v99->method = Method_Project_slMain_slFileSel__;
          v99->method_ptr = v101;
          v99->m_target = 0;
          v102 = v100[82];
          v99->method_code = v99;
          if (sub_3BDA00())
          {
            if (v102)
            {
LABEL_282:
              v104 = v99->method_ptr;
              v99->method_code = v99->m_target;
LABEL_326:
              v99->invoke_impl = v104;
              v99->extra_arg = sub_8710;
              v116 = v88;
              v117 = v99;
              v118 = 1;
              return slQueryYesNo(v116, v117, v118, 1);
            }
LABEL_325:
            v104 = sub_8770;
            goto LABEL_326;
          }
        }
        goto LABEL_361;
      }
    }
    gSlSaveMode = 1;
    slQueryYesNoMsg = 1;
    v88 = Allocate(slQueryYesFuncDelegate);
    v93 = Method_Project_slMain_slSaveData__;
    v94 = *((u64 *)Method_Project_slMain_slSaveData__ + 1);
    v88->method = Method_Project_slMain_slSaveData__;
    v88->method_ptr = v94;
    v88->m_target = 0;
    v95 = v93[82];
    v88->method_code = v88;
    if (sub_3BDA00())
    {
      if (v95)
      {
        v96 = v88->method_ptr;
        v88->method_code = v88->m_target;
      }
      else
      {
        v96 = sub_86A0;
      }
      v88->invoke_impl = v96;
      v88->extra_arg = sub_8640;
      v99 = Allocate(slQueryNoFuncDelegate);
      v113 = Method_Project_slMain_slFileSel__;
      v114 = *((u64 *)Method_Project_slMain_slFileSel__ + 1);
      v99->method = Method_Project_slMain_slFileSel__;
      v99->method_ptr = v114;
      v99->m_target = 0;
      v115 = v113[82];
      v99->method_code = v99;
      if (sub_3BDA00())
      {
        if (v115)
          goto LABEL_282;
        goto LABEL_325;
      }
    }
LABEL_361:
    v130 = sub_3BDC90(0, "Delegate to an instance method cannot have null 'this'.");
  }
  if (v85)
  {
    gSlSaveMode = 0;
  }
  else
  {
    gSlSaveMode = 0;
    if (!v105)
  }
  return slSaveData();
}

// 0x1b5c100
static bool slFileFieldCheck(GameFileInfo_t *info) {
  s32 fieldID;

  fieldID = info->fieldID;
  switch (fieldID)
  {
    case 30:
      if (fldCheckDlcData(3))
        return 1;
      break;
    case 29:
      if (fldCheckDlcData(2))
        return 1;
      break;
    case 26:
      if (fldCheckDlcData(1))
        return 1;
      break;
    default:
      return 1;
  }
  slSetInfo(31);
  return 0;
}

// 0x1b5c2d0
dds3ProcessFunc_t slMsgWaitProc(void) {
  dds3ProcessFunc_t v4;

  gslDrawFlagFile = 1;
  gSlFileSelKyeFlg = 0;
  v4 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
  _ctor(v4, 0, Method_Project_slMain_slFileSelCalc__, 0);
  return v4;
}

// 0x1b5c390
dds3ProcessFunc_t slEnterMsgWaitProc(dds3ProcessFunc_t func) {
  bool v3;
  s32 v5;
  dds3ProcessFunc_t result;

  v3 = CHECK_TRIG(4096, 1);
  if (!v3)
    return 0;
  if (slProcShutDownFlg != 1)
    return 0;
  v5 = fclChkMessage();
  result = 0;
  if (v5)
    return result;
  slSetInfo(0);
  gSlFileSelKyeFlg = 0;
  streamingMes = 0;
  return func;
}

// 0x1b5c520
static void slFileNumDraw(s32 numi, void *slot) {
  s32 v5;
  void *v6;
  void *v7;
  void *v8;
  void *v9;
  void *v10;
  void *sprAuto;
  void *v12;
  void *gameObject;
  void *v14;
  void *v15;
  void *v16;
  void *v19;
  void *v20;
  void *v21;
  void *v22;
  s32 v24;
  void *v25;
  void *sprNo;

  v5 = numi - 1;
  if (numi == 1)
  {
    gameObject = get_gameObject(slot->numObj[0], 0);
    fldSetupObject(gameObject, 0);
    v14 = get_gameObject(slot->numObj[1], 0);
    fldSetupObject(v14, 1);
    v15 = get_gameObject(slot->numObj[2], 0);
    fldSetupObject(v15, 0);
    v16 = get_gameObject(slot->numSpr, 0);
    fldSetupObject(v16, 0);
    v10 = slot->numObj[1];
    sprAuto = slot->sprAuto;
    if (gslCursorSelect != 1)
      goto LABEL_9;
    goto LABEL_16;
  }
  if (!numi)
  {
    v6 = get_gameObject(slot->numObj[0], 0);
    fldSetupObject(v6, 1);
    v7 = get_gameObject(slot->numObj[1], 0);
    fldSetupObject(v7, 0);
    v8 = get_gameObject(slot->numObj[2], 0);
    fldSetupObject(v8, 0);
    v9 = get_gameObject(slot->numSpr, 0);
    fldSetupObject(v9, 0);
    v10 = slot->numObj[0];
    sprAuto = slot->sprChudan;
    if (gslCursorSelect)
    {
LABEL_9:
      v12 = sprAuto[0];
LABEL_10:
      set_sprite(v10, v12, 0);
      return;
    }
LABEL_16:
    v12 = sprAuto[1];
    goto LABEL_10;
  }
  v19 = get_gameObject(slot->numObj[0], 0);
  fldSetupObject(v19, 0);
  v20 = get_gameObject(slot->numObj[1], 0);
  fldSetupObject(v20, 0);
  v21 = get_gameObject(slot->numObj[2], 0);
  fldSetupObject(v21, 1);
  v22 = get_gameObject(slot->numSpr, 0);
  fldSetupObject(v22, 1);
  v24 = gslCursorSelect;
  v25 = slot->numObj[2];
  sprNo = slot->sprNo;
  if (v24 == numi)
  {
    set_sprite(v25, sprNo[1], 0);
    Set(slot->numSpr, v5, 1, 0);
  }
  else
  {
    set_sprite(v25, sprNo[0], 0);
    Set(slot->numSpr, v5, 0, 0);
  }
}

// 0x1b52690
static dds3ProcessFunc_t slFileSelDraw(dds3ProcessID_t *id) {
  u16 *v2;
  void *titleObj;
  s32 v10;
  s32 mvflg;
  u32 v19;
  s32 v20;
  s32 v21;
  s32 v22;
  s32 v23;
  u32 v24;
  s32 v25;
  u32 v26;
  s32 v28;
  void *v29;
  void *slotData;
  s32 v32;
  void *v34;
  void *v35;
  s32 v36;
  s32 v37;
  s32 v39;
  void *v40;
  s32 v41;
  s32 v42;
  s32 v44;
  void *v45;
  __MC_GLOBALWORK *mc_wk;
  void *v48;
  void *v50;
  s32 v51;
  s32 v54;
  s32 v55;
  void *v56;
  void *v60;
  bool v61;
  void *v62;
  u32 v66;
  Il2CppObject *v67;
  void *v69;
  s32 v70;
  s32 v71;
  s32 v72;
  s32 v73;
  u32 v75;
  s32 v76;
  bool v78;
  s32 v81;
  __MC_GLOBALWORK *v82;
  s32 mv_y;
  s32 v85;
  s32 v86;
  s32 *p_d_alpha;
  s32 v88;
  s64 v90;
  Il2CppObject *Component_object;
  void *v94;
  s32 v96;
  u32 v97;
  s32 v98;
  u32 v100;
  void *v101;
  void *v102;
  char *LocalizeText;
  void *p_monitor;
  s32 *monitor;
  s32 *v106;
  s64 v107;
  void *v108;
  s64 v109;
  void *v110;
  void *gameObject;
  s64 v113;
  void *klass;
  void *v115;
  void *v116;
  void *v118;
  u32 v119;
  void *v121;
  u32 endcnt;
  s32 v123;
  Il2CppObject *v124;
  char *v125;
  Il2CppClass *v126;
  char *v127;
  u32 *v128;
  s64 v130;
  Il2CppClass *v131;
  u32 PlayTime;
  s64 v133;
  char *v134;
  void *v135;
  char *v136;
  Il2CppClass *v137;
  char *v138;
  Il2CppClass *v139;
  char *v140;
  void *v141;
  char *v142;
  Il2CppClass *v143;
  char *v144;
  void *v145;
  char *v146;
  Il2CppClass *v147;
  char *v148;
  u32 v149;
  Il2CppClass *v150;
  char *v151;
  void *v152;
  char *v153;
  s64 v154;
  GameFileInfo_t *v156;
  void *v157;
  char *v158;
  Il2CppClass *v159;
  char *v160;
  void *v161;
  char *v162;
  Il2CppClass *v163;
  char *v164;
  void *v165;
  char *v166;
  void *v168;
  char *v169;
  GameFileInfo_t *v171;
  Il2CppClass *v172;
  char *v173;
  char *v174;
  void *v177;
  char *v178;
  char *v179;
  char *v180;
  char *v181;
  char *v182;
  GameFileInfo_t *v184;
  s32 v185;
  SaveTbl_t *v188;
  void *v189;
  char *name;
  char *v192;
  s32 nameLang;
  s32 Language;
  Il2CppClass *v195;
  s32 v197;
  char *v198;
  void *v199;
  char *v200;
  GameFileInfo_t *v205;
  FloorName_t *FloorName;
  void *v207;
  char **v208;
  char *v209;
  s16 basyoID;
  s32 MapId;
  void *v216;
  void *v220;
  void *v221;
  bool v222;
  void *moveU;
  void *moveD;
  s32 v226;
  s64 v227;
  s32 v228;
  int32x4_t *v229;
  s32 v230;
  s32 v231;
  s32 data;

  v2 = NewSpecific(char, 0x40u);
  CreateString_54864672(0, v2, 0);
  v229 = NewSpecific(s32, 4u);
  if (gSlNowCardCheck == 1)
    return 0;
  titleObj = saveloadSystem->titleObj;
  fldSetupObject(titleObj, 1);
  fldSetupObject(saveloadSystem->slotParent, 1);
  if (gslCursorZanzouCnt >= 1)
  {
    gslCursorZanzouCnt = gslCursorZanzouCnt - 1;
  }
  v10 = gslCursorZanzouCnt;
  if ((v10 & 0x80000000) != 0)
    gslCursorZanzouCnt = v10 + 1;
  gslScrollY = (f32)(-110 * gslCursorTop + 104);
  __MC_PanelFadeChk();
  __MC_SelectCursor_AlphaAnim();
  __MC_MoveWindow_Anim();
  mvflg = __mc_wk->mvflg;
  if (!__mc_wk->mvflg)
  {
    v21 = gslCursorTop;
    v22 = 3;
    v23 = 1;
    v230 = v21;
    goto LABEL_32;
  }
  if (mvflg == 1)
  {
    if (v19)
    {
      v20 = gslCursorTop;
      v230 = (v20 - 1) & ~((v20 - 1) >> 31);
    }
    else
    {
      v20 = gslCursorTop;
      v230 = (v20 - 1) & ~((v20 - 1) >> 31);
    }
    v226 = v20;
    if (!susendOpenFlg)
      goto LABEL_445;
    if (autoSaveOpenFlg)
      goto LABEL_445;
    if (gslCursorTop == 2)
    {
      v28 = 2;
      v60 = *((void *)&saveloadSystem->slotData->bounds + v28);
      fldSetupObject(v60, 0);
      v23 = 1;
      fldSetupObject(saveloadSystem->slotData[gslCursorTop + 1], 1);
      v35 = saveloadSystem->slotData[gslCursorTop
                                                                                           + 2];
    }
    else
    {
LABEL_445:
      v29 = saveloadSystem->slotData[gslCursorTop - 1];
      fldSetupObject(v29, 0);
      slotData = saveloadSystem->slotData;
      v32 = gslCursorTop + 2;
      if (v32 >= SLODWORD(slotData->max_length))
      {
        v22 = 4;
        v23 = 1;
        goto LABEL_161;
      }
      slotData = saveloadSystem->slotData;
      v32 = gslCursorTop + 2;
      v34 = slotData[v32];
      v23 = 1;
      v35 = v34;
    }
    v61 = 1;
    goto LABEL_159;
  }
  if (v19)
  {
    if (mvflg == 2)
      goto LABEL_36;
  }
  else
  {
    mvflg = __mc_wk->mvflg;
    if (mvflg == 2)
    {
LABEL_36:
      v25 = gslCursorTop;
      if (v25 < 1)
      {
        if (!v26)
        {
          v25 = gslCursorTop;
        }
      }
      else
      {
        if (!v26)
        {
          v25 = gslCursorTop;
        }
        --v25;
        v226 = v25;
        v230 = gslCursorTop;
        if (!susendOpenFlg)
          goto LABEL_121;
LABEL_118:
        if (!autoSaveOpenFlg)
        {
          v55 = gslCursorTop;
          if (v55 == 2)
            goto LABEL_446;
          v55 = gslCursorTop;
          if (!v55)
          {
LABEL_446:
            v56 = saveloadSystem->slotData[gslCursorTop];
            v23 = 1;
            fldSetupObject(v56, 1);
            fldSetupObject(saveloadSystem->slotData[gslCursorTop + 4], 0);
            if (gslCursorTop != 2)
              goto LABEL_160;
            v54 = 2;
            goto LABEL_155;
          }
        }
LABEL_121:
        v48 = saveloadSystem->slotData[gslCursorTop];
        v23 = 1;
        fldSetupObject(v48, 1);
        v50 = saveloadSystem->slotData;
        v51 = gslCursorTop + 3;
        if (v51 >= SLODWORD(v50->max_length))
          goto LABEL_160;
        goto LABEL_156;
LABEL_155:
        v50 = saveloadSystem->slotData;
        v51 = v54 + 3;
LABEL_156:
        v62 = v50[v51];
        v35 = v62;
        v61 = 0;
LABEL_159:
        fldSetupObject(v35, v61);
LABEL_160:
        v22 = 4;
        goto LABEL_161;
      }
      v226 = v25;
      v230 = gslCursorTop;
      if (!susendOpenFlg)
        goto LABEL_121;
      goto LABEL_118;
    }
  }
  if (!v24)
  {
    mvflg = __mc_wk->mvflg;
  }
  if (mvflg != 3)
  {
    v230 = 0;
    v23 = 0;
    v22 = 0;
    v226 = 0;
    goto LABEL_161;
  }
  v36 = 0;
  v37 = 0;
  v230 = gslCursorTop;
  do
  {
    v39 = v36 + bakCursorTop;
    if (v39 != 1)
    {
      if (v39)
        goto LABEL_88;
      if (susendOpenFlg)
        goto LABEL_88;
      goto LABEL_76;
    }
    if (autoSaveOpenFlg)
    {
LABEL_88:
      v40 = saveloadSystem->slotData[v39];
      fldSetupObject(v40, 0);
      ++v37;
    }
LABEL_76:
    ++v36;
  }
  while (v37 < 3);
  v41 = 0;
  v42 = 0;
  do
  {
    v44 = v41 + gslCursorTop;
    if (v44 != 1)
    {
      if (v44)
        goto LABEL_107;
      if (susendOpenFlg)
        goto LABEL_107;
      goto LABEL_95;
    }
    if (autoSaveOpenFlg)
    {
LABEL_107:
      v45 = saveloadSystem->slotData[v44];
      fldSetupObject(v45, 1);
      ++v42;
    }
LABEL_95:
    ++v41;
  }
  while (v42 < 3);
  goto LABEL_113;
LABEL_114:
  mc_wk = __mc_wk;
  mc_wk->mvflg = 0;
  mc_wk->mv_y = 0;
  goto LABEL_9002;
LABEL_113:
  goto LABEL_114;
LABEL_9002:
  v22 = 3;
  v23 = 1;
  *(u64 *)&mc_wk->u_alpha = 0x7400000000LL;
  v21 = v230;
LABEL_32:
  v226 = v21;
LABEL_161:
  if (bakCursorSelect != gslCursorSelect)
    goto LABEL_169;
LABEL_163:
  v66 = v230 - 1;
  if (v230 - 1 >= 0)
    goto LABEL_164;
LABEL_174:
  if (!v23)
    goto LABEL_412;
LABEL_175:
  v70 = 0;
  v71 = 0;
  v72 = 1692838528;
  if (v22 <= 1)
    v73 = 1;
  else
    v73 = v22;
  v228 = v73;
  while (1)
  {
    v76 = v70 + v230;
    v78 = !autoSaveOpenFlg && v76 == 1;
    if (v78 && v71 == 0)
      v71 = 1;
    v81 = v71 + v76;
    v82 = __mc_wk;
    mv_y = v82->mv_y;
    if (gslScrollY == INFINITY)
      v85 = 0x80000000;
    else
      v85 = gslScrollY;
    if (gslCursorSelect == v81)
      v86 = 1692838528;
    else
      v86 = v72;
    if (v75)
    {
      if (!v82->mvflg)
        goto LABEL_209;
    }
    else
    {
      v82 = __mc_wk;
      if (!v82->mvflg)
        goto LABEL_209;
    }
    if (v70 == 3)
    {
      v82 = __mc_wk;
      p_d_alpha = &v82->d_alpha;
    }
    else
    {
      if (v70)
      {
LABEL_209:
        v82 = __mc_wk;
        p_d_alpha = &v82->alpha;
        goto LABEL_215;
      }
      v82 = __mc_wk;
      p_d_alpha = &v82->u_alpha;
    }
LABEL_215:
    v88 = *p_d_alpha;
    if (v88 < (u8)v86)
      v86 = v88;
    v229[2] = vdupq_n_s32(v88 | 0x80808000);
    v231 = v86;
    if (!!gslStatFileInfo[v81])
    {
      if (v81 == 22)
        goto LABEL_180;
      goto LABEL_223;
    }
    if (v81 == 22)
      goto LABEL_180;
LABEL_223:
    v90 = v81;
    Component_object = GetComponent_object_(saveloadSystem->slotData[v81]);
    if (110 * (v70 + v226) + v85 + mv_y + 7 < 65)
    {
      goto LABEL_227;
    }
    v94 = NewSpecific(s32, 0x2Au);
    InitializeArray_55364416(v94, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__A43ED98E7AE0BA46F8C85738629728B22631D3AA815E79E0F59FC7642DBCB75D, 0);
    slFileNumDraw(v81, Component_object);
    if (gslCursorSelect != v81)
      goto LABEL_250;
    goto LABEL_234;
LABEL_227:
    if (gslCursorSelect != v81)
      goto LABEL_250;
LABEL_234:
    v96 = gslCursorZanzouCnt;
    if (v96 >= 1)
    {
      if (!v97)
      {
        v98 = 0;
        do
        {
          ++v98;
        }
        while (v98 < gslCursorZanzouCnt);
      }
      goto LABEL_250;
    }
    if (v97)
    {
      if ((v96 & 0x80000000) == 0)
        goto LABEL_250;
    }
    else
    {
      if ((gslCursorZanzouCnt & 0x80000000) == 0)
        goto LABEL_250;
    }
    v185 = 0;
    do
    {
      ++v185;
    }
    while (v185 < -gslCursorZanzouCnt);
LABEL_250:
    if (gslStatFileInfo[v81] != 1)
    {
      if (v100)
      {
        monitor = Component_object[10].monitor;
        if (monitor[6] < 1)
          goto LABEL_274;
      }
      else
      {
        monitor = Component_object[10].monitor;
        if (monitor[6] < 1)
        {
LABEL_274:
          (*(*(u64 *)Component_object[3].monitor + 1368))(Component_object[3].monitor, "", *(u64 *)(*(u64 *)Component_object[3].monitor + 1376));
          (*(Component_object[4].klass->_1.image + 171))(Component_object[4].klass, "", *((u64 *)Component_object[4].klass->_1.image + 172));
          (*(*(u64 *)Component_object[4].monitor + 1368))(Component_object[4].monitor, "", *(u64 *)(*(u64 *)Component_object[4].monitor + 1376));
          (*(Component_object[5].klass->_1.image + 171))(Component_object[5].klass, "", *((u64 *)Component_object[5].klass->_1.image + 172));
          (*(*(u64 *)Component_object[5].monitor + 1368))(Component_object[5].monitor, "", *(u64 *)(*(u64 *)Component_object[5].monitor + 1376));
          (*(Component_object[6].klass->_1.image + 171))(Component_object[6].klass, "", *((u64 *)Component_object[6].klass->_1.image + 172));
          (*(*(u64 *)Component_object[6].monitor + 1368))(Component_object[6].monitor, "", *(u64 *)(*(u64 *)Component_object[6].monitor + 1376));
          (*(Component_object[7].klass->_1.image + 171))(Component_object[7].klass, "", *((u64 *)Component_object[7].klass->_1.image + 172));
          (*(Component_object[8].klass->_1.image + 171))(Component_object[8].klass, "", *((u64 *)Component_object[8].klass->_1.image + 172));
          (*(*(u64 *)Component_object[8].monitor + 1368))(Component_object[8].monitor, "", *(u64 *)(*(u64 *)Component_object[8].monitor + 1376));
          (*(Component_object[9].klass->_1.image + 171))(Component_object[9].klass, "", *((u64 *)Component_object[9].klass->_1.image + 172));
          (*(*(u64 *)Component_object[9].monitor + 1368))(Component_object[9].monitor, "", *(u64 *)(*(u64 *)Component_object[9].monitor + 1376));
          (*(Component_object[10].klass->_1.image + 171))(Component_object[10].klass, "", *((u64 *)Component_object[10].klass->_1.image + 172));
          (*(*(u64 *)Component_object[7].monitor + 1368))(Component_object[7].monitor, "", *(u64 *)(*(u64 *)Component_object[7].monitor + 1376));
          gameObject = get_gameObject(Component_object[11].klass, 0);
          fldSetupObject(gameObject, 1);
          v113 = 32;
          if (gslCursorSelect == v81)
            v113 = 40;
          set_sprite(Component_object[11].klass, *(void *)((char *)Component_object[14].monitor + v113), 0);
          klass = Component_object[12].klass;
          fldSetupObject(klass, 0);
          goto LABEL_180;
        }
      }
      v109 = 0;
      do
      {
        v110 = *(void *)&monitor[2 * v109 + 8];
        fldSetupObject(v110, 0);
        monitor = Component_object[10].monitor;
        ++v109;
      }
      while (v109 < monitor[6]);
      goto LABEL_274;
    }
    if (v100)
    {
      v227 = v81;
      if (gslInfo[v81]->newfile)
        goto LABEL_255;
    }
    else
    {
      v227 = v81;
      if (gslInfo[v81]->newfile)
      {
LABEL_255:
        v101 = get_gameObject(Component_object[11].monitor, 0);
        fldSetupObject(v101, 1);
        v102 = Component_object[11].monitor;
        LocalizeText = GetLocalizeText("SAVELOAD_L0064", 1);
        (*(*(u64 *)v102 + 1368))(v102, LocalizeText, *(u64 *)(*(u64 *)v102 + 1376));
        (*(Component_object[5].klass->_1.image + 171))(Component_object[5].klass, "", *((u64 *)Component_object[5].klass->_1.image + 172));
        (*(*(u64 *)Component_object[3].monitor + 1368))(Component_object[3].monitor, "", *(u64 *)(*(u64 *)Component_object[3].monitor + 1376));
        (*(Component_object[4].klass->_1.image + 171))(Component_object[4].klass, "", *((u64 *)Component_object[4].klass->_1.image + 172));
        (*(*(u64 *)Component_object[4].monitor + 1368))(Component_object[4].monitor, "", *(u64 *)(*(u64 *)Component_object[4].monitor + 1376));
        (*(*(u64 *)Component_object[5].monitor + 1368))(Component_object[5].monitor, "", *(u64 *)(*(u64 *)Component_object[5].monitor + 1376));
        (*(*(u64 *)Component_object[7].monitor + 1368))(Component_object[7].monitor, "", *(u64 *)(*(u64 *)Component_object[7].monitor + 1376));
        fldSetupObject(*((void *)Component_object[10].monitor + 4), 0);
        fldSetupObject(*((void *)Component_object[10].monitor + 5), 0);
        fldSetupObject(*((void *)Component_object[10].monitor + 6), 1);
        fldSetupObject(*((void *)Component_object[10].monitor + 7), 1);
        fldSetupObject(*((void *)Component_object[10].monitor + 8), 1);
        fldSetupObject(*((void *)Component_object[10].monitor + 9), 1);
        fldSetupObject(*((void *)Component_object[10].monitor + 10), 1);
        fldSetupObject(*((void *)Component_object[10].monitor + 11), 1);
        fldSetupObject(*((void *)Component_object[10].monitor + 12), 1);
        fldSetupObject(*((void *)Component_object[10].monitor + 13), 0);
        v90 = v227;
        p_monitor = &Component_object[11];
        goto LABEL_285;
      }
    }
    v106 = Component_object[10].monitor;
    if (v106[6] >= 1)
    {
      v107 = 0;
      do
      {
        v108 = *(void *)&v106[2 * v107 + 8];
        fldSetupObject(v108, 1);
        v106 = Component_object[10].monitor;
        ++v107;
      }
      while (v107 < v106[6]);
    }
    v115 = get_gameObject(Component_object[11].klass, 0);
    fldSetupObject(v115, 0);
    p_monitor = &Component_object[11].monitor;
LABEL_285:
    v116 = get_gameObject(p_monitor, 0);
    fldSetupObject(v116, 0);
    v118 = Component_object[12].klass;
    if (gslInfo[v90]->endcnt)
    {
      if (!v119)
      fldSetupObject(v118, 1);
      v121 = Component_object[12].monitor;
      endcnt = gslInfo[v90]->endcnt;
      if (endcnt < 0x63)
        v123 = endcnt + 1;
      else
        v123 = 99;
      data = v123;
      v124 = Box(s32, &data);
      v125 = Format("{0:d}", v124, 0);
      (*(*(u64 *)v121 + 1368))(v121, v125, *(u64 *)(*(u64 *)v121 + 1376));
      v126 = Component_object[13].klass;
      v127 = GetLocalizeText("SAVELOAD_L0065", 1);
      (*(v126->_1.image + 171))(v126, v127, *((u64 *)v126->_1.image + 172));
    }
    else
    {
      if (!v119)
      fldSetupObject(v118, 0);
    }
    v128 = NewSpecific(uint, 3u);
    v130 = v227;
    v131 = Component_object[6].klass;
    PlayTime = gslInfo[v227]->PlayTime;
    if (PlayTime >= 0xCDFD7F0)
      PlayTime = 215996400;
    v128[2] = (2185 * (PlayTime - 3600 * ((u32)((305419897 * (u64)PlayTime) >> 32) >> 8))) >> 17;
    v133 = &v128[2];
    *(u32 *)(v133 - 8) = PlayTime / 0x34BC0;
    *(u32 *)(v133 - 4) = PlayTime % 0x34BC0 / 0xE10;
    v134 = ToString((s32)v133 - 8, 0);
    (*(v131->_1.image + 171))(v131, v134, *((u64 *)v131->_1.image + 172));
    v135 = Component_object[6].monitor;
    v136 = ToString_56146800((s32)v133 - 4, "D2", 0);
    (*(*(u64 *)v135 + 1368))(v135, v136, *(u64 *)(*(u64 *)v135 + 1376));
    v137 = Component_object[7].klass;
    v138 = ToString_56146800(v133, "D2", 0);
    (*(v137->_1.image + 171))(v137, v138, *((u64 *)v137->_1.image + 172));
    v139 = Component_object[8].klass;
    v140 = ToString_55996800(LODWORD(gslInfo[v130]->saveTime) + 16, "D4", 0);
    (*(v139->_1.image + 171))(v139, v140, *((u64 *)v139->_1.image + 172));
    v141 = Component_object[8].monitor;
    v142 = ToString_55996800((u32)gslInfo[v130]->saveTime + 20, "D2", 0);
    (*(*(u64 *)v141 + 1368))(v141, v142, *(u64 *)(*(u64 *)v141 + 1376));
    v143 = Component_object[9].klass;
    v144 = ToString_55996800((u32)gslInfo[v130]->saveTime + 24, "D2", 0);
    (*(v143->_1.image + 171))(v143, v144, *((u64 *)v143->_1.image + 172));
    v145 = Component_object[9].monitor;
    v146 = ToString_55996800((u32)gslInfo[v130]->saveTime + 28, "D2", 0);
    (*(*(u64 *)v145 + 1368))(v145, v146, *(u64 *)(*(u64 *)v145 + 1376));
    v147 = Component_object[10].klass;
    v148 = ToString_55996800((u32)gslInfo[v130]->saveTime + 32, "D2", 0);
    (*(v147->_1.image + 171))(v147, v148, *((u64 *)v147->_1.image + 172));
    if (gslInfo[v130]->newfile)
    {
      v150 = Component_object[16].klass;
      if (!v149)
      v151 = GetLocalizeText("SAVELOAD_L1001", 1);
      (*(v150->_1.image + 171))(v150, v151, *((u64 *)v150->_1.image + 172));
      v152 = Component_object[17].monitor;
      v153 = GetLocalizeText("SAVELOAD_L1004", 1);
      (*(*(u64 *)v152 + 1368))(v152, v153, *(u64 *)(*(u64 *)v152 + 1376));
      v154 = v227;
      goto LABEL_309;
    }
    v157 = Component_object[15].monitor;
    if (!v149)
    v158 = GetLocalizeText("SAVELOAD_L1000", 1);
    (*(*(u64 *)v157 + 1368))(v157, v158, *(u64 *)(*(u64 *)v157 + 1376));
    v159 = Component_object[16].klass;
    v160 = GetLocalizeText("SAVELOAD_L1001", 1);
    (*(v159->_1.image + 171))(v159, v160, *((u64 *)v159->_1.image + 172));
    v161 = Component_object[16].monitor;
    v162 = GetLocalizeText("SAVELOAD_L1002", 1);
    (*(*(u64 *)v161 + 1368))(v161, v162, *(u64 *)(*(u64 *)v161 + 1376));
    v163 = Component_object[17].klass;
    v164 = GetLocalizeText("SAVELOAD_L1003", 1);
    (*(v163->_1.image + 171))(v163, v164, *((u64 *)v163->_1.image + 172));
    v165 = Component_object[17].monitor;
    v166 = GetLocalizeText("SAVELOAD_L1004", 1);
    (*(*(u64 *)v165 + 1368))(v165, v166, *(u64 *)(*(u64 *)v165 + 1376));
    v168 = Component_object[7].monitor;
    v154 = v227;
    v169 = GetLocalizeText(difficName[gslInfo[v130]->Mode], 1);
    (*(*(u64 *)v168 + 1368))(v168, v169, *(u64 *)(*(u64 *)v168 + 1376));
    v171 = gslInfo[v130];
    if (v171->TmnlMode == 2)
    {
      v172 = Component_object[5].klass;
      v171 = gslInfo[v227];
      v173 = storyEnd[v171->chapter];
      v174 = GetLocalizeText(v173, 1);
      (*(v172->_1.image + 171))(v172, v174, *((u64 *)v172->_1.image + 172));
      (*(*(u64 *)Component_object[5].monitor + 1368))(Component_object[5].monitor, "", *(u64 *)(*(u64 *)Component_object[5].monitor + 1376));
      (*(Component_object[17].klass->_1.image + 171))(Component_object[17].klass, "", *((u64 *)Component_object[17].klass->_1.image + 172));
      v154 = v227;
LABEL_322:
      if (gslInfoCode != 2)
        goto LABEL_350;
      goto LABEL_346;
    }
    v171 = gslInfo[v227];
    v179 = storyNow[v171->chapter];
    v180 = GetLocalizeText(v179, 1);
    v181 = GetLocalizeText(storyName[gslInfo[v227]->chapter], 1);
    v182 = Concat_54831728(v180, " ", v181, 0);
    (*(Component_object[5].klass->_1.image + 171))(Component_object[5].klass, v182, *((u64 *)Component_object[5].klass->_1.image + 172));
    if (v81 >= 2)
    {
      v188 = GetfldSave(fldSaveTbl, gslInfo[v227]->TmnlId, 0);
      v189 = Component_object[5].monitor;
      name = v188->_name;
LABEL_344:
      v192 = GetLocalizeText(name, 1);
      (*(*(u64 *)v189 + 1368))(v189, v192, *(u64 *)(*(u64 *)v189 + 1376));
      goto LABEL_322;
    }
    v184 = gslInfo[v227];
    if (v184->fieldID)
      goto LABEL_365;
    v184 = gslInfo[v227];
    if (v184->floorID)
    {
LABEL_365:
      if (gslInfo[v227]->fieldID == 26)
      {
        if (fldCheckDlcData(1))
        {
          goto LABEL_372;
        }
      }
      else
      {
LABEL_372:
        if (gslInfo[v227]->fieldID == 29)
        {
          if (!fldCheckDlcData(2))
            goto LABEL_391;
        }
        if (gslInfo[v227]->fieldID != 30)
          goto LABEL_385;
        if (fldCheckDlcData(3))
        {
LABEL_385:
          v205 = gslInfo[v227];
          FloorName = GetFloorName(fldFloorNameTbl, v205->fieldID, v205->floorID, 0);
          v189 = Component_object[5].monitor;
          name = FloorName->_name;
          goto LABEL_344;
        }
      }
LABEL_391:
      v207 = Component_object[5].monitor;
      v208 = &"BASYONAME_L0162";
LABEL_394:
      v209 = GetLocalizeText(*v208, 1);
      (*(*(u64 *)v207 + 1368))(v207, v209, *(u64 *)(*(u64 *)v207 + 1376));
      goto LABEL_322;
    }
    basyoID = v184->basyoID;
    goto LABEL_9004;
    if (MapId == 2)
    {
LABEL_407:
      v207 = Component_object[5].monitor;
      v208 = &"SAVELOAD_L0080";
      goto LABEL_394;
    }
    goto LABEL_401;
LABEL_9004:
    MapId = lmapMapDat_GetMapId(basyoID);
    if (MapId == 2)
      goto LABEL_407;
LABEL_401:
    if (MapId == 1)
    {
      v207 = Component_object[5].monitor;
      v208 = &"SAVELOAD_L0079";
      goto LABEL_394;
    }
    (*(*(u64 *)Component_object[5].monitor + 1368))(Component_object[5].monitor, "", *(u64 *)(*(u64 *)Component_object[5].monitor + 1376));
    goto LABEL_322;
LABEL_346:
    if (gslCursorSelect == v81)
      goto LABEL_309;
LABEL_350:
    nameLang = gslInfo[v154]->nameLang;
    Language = GetLanguage();
    v195 = Component_object[4].klass;
    if (nameLang == Language)
      goto LABEL_354;
    goto LABEL_9005;
    if (nameLang == v197)
    {
LABEL_354:
      (*(v195->_1.image + 171))(v195, gslInfo[v130]->player_family, *((u64 *)v195->_1.image + 172));
      (*(*(u64 *)Component_object[4].monitor + 1368))(Component_object[4].monitor, gslInfo[v130]->player_first, *(u64 *)(*(u64 *)Component_object[4].monitor + 1376));
      goto LABEL_309;
    }
LABEL_9005:
    v198 = GetLocalizeText("SYSTEM_L0002", 1);
    (*(v195->_1.image + 171))(v195, v198, *((u64 *)v195->_1.image + 172));
    v199 = Component_object[4].monitor;
    v200 = GetLocalizeText("SYSTEM_L0003", 1);
    (*(*(u64 *)v199 + 1368))(v199, v200, *(u64 *)(*(u64 *)v199 + 1376));
LABEL_309:
    v156 = gslInfo[v154];
    if (!v156->newfile)
    {
      v177 = Component_object[3].monitor;
      v156 = gslInfo[v154];
      v178 = ToString((u8)v156 + 28, 0);
      (*(*(u64 *)v177 + 1368))(v177, v178, *(u64 *)(*(u64 *)v177 + 1376));
    }
LABEL_180:
    ++v70;
    v72 = v231;
    if (v70 == v228)
      goto LABEL_412;
  }
  if (bakCursorSelect == gslCursorSelect)
    goto LABEL_163;
LABEL_169:
  v69 = saveloadSystem->slotCur[bakCursorSelect];
  fldSetupObject(v69, 0);
  fldSetupObject(saveloadSystem->slotCur[gslCursorSelect], 1);
  bakCursorSelect = gslCursorSelect;
  v66 = v230 - 1;
  if (v230 - 1 < 0)
    goto LABEL_174;
LABEL_164:
  v67 = GetComponent_object_(saveloadSystem->slotData[v66]);
  slFileNumDraw(v66, v67);
  if (v23)
    goto LABEL_175;
LABEL_412:
  if (!gSlFileSelKyeFlg)
  {
    if (gslCursorTop > SlotDataTop)
      goto LABEL_418;
    moveU = saveloadSystem->moveU;
    fldSetupObject(moveU, 0);
LABEL_423:
    if (gslCursorTop > 18)
      goto LABEL_424;
    moveD = saveloadSystem->moveD;
    v221 = moveD;
    v222 = 1;
    goto LABEL_9007;
LABEL_418:
    v216 = saveloadSystem->moveU;
    fldSetupObject(v216, 1);
    goto LABEL_423;
LABEL_424:
    v220 = saveloadSystem->moveD;
    v221 = v220;
    v222 = 0;
LABEL_9007:
    fldSetupObject(v221, v222);
  }
  return 0;
}

// 0x1b578d0
static dds3ProcessFunc_t slChooseData_getCardInfo(void) {
  dds3ProcessFunc_t v1;

  v1 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
  _ctor(v1, 0, Method_Project_slMain_slHeadLoadProc_closeFile__, 0);
  return v1;
}

// 0x1b5d2b0
static dds3ProcessFunc_t slChooseData_getCardInfo2(dds3ProcessID_t *procId) {
  dds3ProcessFunc_t v2;

  v2 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
  _ctor(v2, 0, Method_Project_slMain_slChooseData_getCardInfo3__, 0);
  return v2;
}

// 0x1b5d340
static dds3ProcessFunc_t slChooseData_getCardInfo3(dds3ProcessID_t *procId) {
  return slHeadLoad();
}

// 0x1b59cd0
static dds3ProcessFunc_t slChooseData_getCardInfoNext(void) {
  s32 v3;
  dds3ProcessFunc_t v5;

  v3 = gslChooseSaveIndex + 1;
  gslChooseSaveIndex = v3;
  if (v3 == 22)
  {
    gSlNowCardCheck = 0;
    gslChooseSaveIndex = 0;
    return slFileSel();
  }
  else
  {
    v5 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
    _ctor(v5, 0, Method_Project_slMain_slHeadLoadProc_closeFile__, 0);
    return v5;
  }
}

// 0x1b57d00
static dds3ProcessFunc_t slChooseData_getCardInfo_B(void) {
  u16 *v1;
  char *String_54864672;
  dds3ProcessFunc_t v3;

  v1 = NewSpecific(char, 0x42u);
  String_54864672 = CreateString_54864672(0, v1, 0);
  ChangeCharacter(String_54864672, 0, 0x2Fu);
  v3 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
  _ctor(v3, 0, Method_Project_slMain_slChooseData_getCardInfo2_B__, 0);
  return v3;
}

// 0x1b5d3b0
static dds3ProcessFunc_t slChooseData_getCardInfo2_B(dds3ProcessID_t *procId) {
  dds3ProcessFunc_t v2;

  v2 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
  _ctor(v2, 0, Method_Project_slMain_slChooseData_getCardInfo3_B__, 0);
  return v2;
}

// 0x1b5d6d0
static dds3ProcessFunc_t slChooseData_getCardInfo3_B(dds3ProcessID_t *procId) {
  slChooseData_getCardInfoNext_B();
  return 0;
}

// 0x1b5d610
static dds3ProcessFunc_t slChooseData_getCardInfoNext_B(void) {
  slSetInfo(0);
  gslDrawFlagFile = 0;
  gslErrorCode = 0;
  dds3AdminiCallSequence2(2, 0, 0, 0);
  return 0;
}

// 0x1b59220
static dds3ProcessFunc_t slSaveWriteFile(char *filename, void *buff, s32 *size, slSaveWriteFile_endFuncDelegate endFunc, void *srcPtr) {
  Il2CppObject **p_slSaveWriteFile_buff;
  struct slMain *static_fields;
  s32 v13;
  void **p_slSaveWriteFile_dataWaitPtr;
  dds3ProcessFunc_t v15;

  p_slSaveWriteFile_buff = &slSaveWriteFile_buff;
  *p_slSaveWriteFile_buff = buff;
  v13 = *size;
  slSaveWriteFile_endFunc = endFunc;
  static_fields = ((char *)static_fields + 216);
  gSlNowCardCheck = v13;
  p_slSaveWriteFile_dataWaitPtr = &slSaveWriteFile_dataWaitPtr;
  *p_slSaveWriteFile_dataWaitPtr = srcPtr;
  v15 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
  _ctor(v15, 0, Method_Project_slMain_slSaveProc_openFile__, 0);
  return v15;
}

// 0x1b5d920
static dds3ProcessFunc_t slQueryYesNoProc(dds3ProcessID_t *procId) {
  bool v5;
  bool v9;
  s32 v12;
  Il2CppMethodPointer virtualMethodPointer;
  void *slQueryYesFunc_local;
  bool v17;
  bool v24;
  Il2CppMethodPointer v27;
  s32 SelMessagePos;
  s32 v31;

  goto LABEL_3;
LABEL_7:
  if (slQueryYesNoMsg == 6)
    goto LABEL_9;
  if (slQueryYesNoMsg == 4)
    goto LABEL_61;
  if (slQueryYesNoMsg == 8)
    goto LABEL_61;
  if (slQueryYesNoMsg == 10)
    goto LABEL_61;
  if (slQueryYesNoMsg == 11)
    goto LABEL_61;
  if (slQueryYesNoMsg == 12)
    goto LABEL_61;
  if (!slQueryYesNoKeyFlag)
  {
    if (!fclChkSelMessage())
    {
      SelMessagePos = fclGetSelMessagePos();
      if (SelMessagePos == 1)
      {
        v31 = 2;
LABEL_131:
        *((u32 *)*((MethodInfo *)slMain + 2).virtualMethodPointer + 31) = v31;
        slMessageClose();
        goto LABEL_132;
      }
      if (!SelMessagePos)
      {
        v31 = 1;
        goto LABEL_131;
      }
    }
  }
LABEL_132:
  if (slQueryYesNoKeyFlag != 2)
  {
    if (slQueryYesNoKeyFlag != 1)
      return 0;
    slQueryYesNoMsg = 0;
    slQueryYesNoCursor = -1;
LABEL_72:
    slQueryYesFunc_local = slQueryYesFunc;
    return (*((dds3ProcessFunc_t (u64, u64))slQueryYesFunc_local + 3))(*((u64 *)slQueryYesFunc_local + 8), *((u64 *)slQueryYesFunc_local + 5));
  }
  cmpCmpGuideSet(44, 0, 90);
  slQueryYesNoCursor = -1;
  slQueryYesNoMsg = 0;
LABEL_109:
  slQueryYesFunc_local = slQueryNoFunc;
  return (*((dds3ProcessFunc_t (u64, u64))slQueryYesFunc_local + 3))(*((u64 *)slQueryYesFunc_local + 8), *((u64 *)slQueryYesFunc_local + 5));
LABEL_61:
  if (fclChkSelMessage())
    return 0;
  v12 = fclGetSelMessagePos();
  if (v12 != 1)
  {
    if (v12)
      return 0;
    virtualMethodPointer = *((const MethodInfo *)slMain + 2).virtualMethodPointer;
    *((u32 *)virtualMethodPointer + 30) = -1;
    *((u32 *)virtualMethodPointer + 11) = 0;
    slMessageClose();
    goto LABEL_72;
  }
  v27 = *((const MethodInfo *)slMain + 2).virtualMethodPointer;
  *((u32 *)v27 + 30) = -1;
  *((u32 *)v27 + 11) = 0;
  slMessageClose();
  slBlackScreenSet = 1;
  goto LABEL_109;
LABEL_3:
  if (slQueryYesNoMsg != 5)
    goto LABEL_7;
LABEL_9:
  if (slQueryYesNoKeyFlag)
    return 0;
  v5 = CHECK_TRIG(4101, 1);
  goto LABEL_17;
LABEL_25:
  if (slProcShutDownFlg != 1)
    goto LABEL_36;
  if (slQueryYesNoCursor == 1)
  {
LABEL_30:
    slQueryYesNoCursor = 1;
    return 0;
  }
  SE(3);
  goto LABEL_30;
LABEL_17:
  if (v5)
    goto LABEL_25;
LABEL_36:
  v9 = CHECK_TRIG(4100, 1);
  goto LABEL_38;
LABEL_42:
  if (slProcShutDownFlg != 1)
    goto LABEL_74;
  if (slQueryYesNoCursor)
  {
    SE(3);
  }
  slQueryYesNoCursor = 0;
  return 0;
LABEL_38:
  if (v9)
    goto LABEL_42;
LABEL_74:
  v17 = CHECK_TRIG(4096, 1);
  if (!v17)
    goto LABEL_99;
  if (slProcShutDownFlg != 1)
  {
LABEL_99:
    v24 = CHECK_TRIG(4097, 1);
    if (slGetPadTrig(v24))
    {
      SE(1);
LABEL_105:
      slQueryYesNoKeyFlag = 2;
      return 0;
    }
    return 0;
  }
  if (slQueryYesNoCursor)
    goto LABEL_147;
  if (slQueryYesNoMsg != 1)
  {
LABEL_147:
  }
  SE(0);
  if (slQueryYesNoCursor)
  {
    goto LABEL_105;
  }
  slQueryYesNoKeyFlag = 1;
  return 0;
}

// 0x1b517e0
static dds3ProcessFunc_t slQueryYesNo(slQueryYesFuncDelegate yesFunc, slQueryNoFuncDelegate noFunc, s32 yesNoDefault, s16 cancelNum) {
  void *Instance;
  dds3ProcessFunc_t v17;

  slQueryYesFunc = yesFunc;
  slQueryNoFunc = noFunc;
  slQueryYesNoCursor = yesNoDefault;
  slQueryYesNoKeyFlag = 0;
  fclSetSelMessagePos(yesNoDefault);
  fclSetSelCancelPos(cancelNum);
  if (slQueryYesNoMsg != 4)
  {
    if (slQueryYesNoMsg == 8)
      goto LABEL_20;
  }
LABEL_20:
  cmpCmpGuideSet(45, 0, 90);
  Instance = get_Instance(0);
  ItfButtonGuideActive(Instance, 0, 0);
  v17 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
  _ctor(v17, 0, Method_Project_slMain_slQueryYesNoProc__, 0);
  return v17;
}

// 0x1b54cf0
static void slQueryYesNoDraw(void) {
  s32 v7;

  slCheckMsgDraw();
  if (slQueryYesNoCursor == -1)
    return;
  if (!slQueryYesNoMsg)
    return;
  v7 = slQueryYesNoMsg;
  slChoiceMsgDraw(v7);
}

// 0x1b5e710
void slShutDownProcess(dds3ProcessID_t *id) {
  fmShutDown();
}

// 0x1b54de0
static void slDrawError(void) {
  __MC_GLOBALWORK *mc_wk;

  if (!gslErrorCode)
    return;
  if (gslErrorCode != 1)
  {
    goto LABEL_10;
  }
  gslCursorSelect = 0;
  gslCursorTop = SlotDataTop;
  mc_wk = __mc_wk;
  mc_wk->mv_y = 0;
  mc_wk->mvflg = 0;
  mc_wk->cnt = 0;
  slNextPageDraw();
  gslDrawFlagFile = 0;
LABEL_10:
  if (gslErrorCode != 2)
  {
    goto LABEL_12;
  }
  slNextPageDraw();
  gslDrawFlagFile = 0;
LABEL_12:
  if (gslErrorCode != 3)
  {
    goto LABEL_14;
  }
  slNextPageDraw();
  gslDrawFlagFile = 0;
LABEL_14:
  if (gslErrorCode != 4)
  {
    goto LABEL_16;
  }
  slNextPageDraw();
  gslDrawFlagFile = 0;
LABEL_16:
  if (gslErrorCode != 5)
  {
    goto LABEL_18;
  }
  slNextPageDraw();
  gslDrawFlagFile = 0;
LABEL_18:
  if (gslErrorCode != 6)
  {
    goto LABEL_20;
  }
  slNextPageDraw();
  gslDrawFlagFile = 0;
LABEL_20:
  if (gslErrorCode != 7)
    return;
  slNextPageDraw();
  gslDrawFlagFile = 0;
}

// 0x1b54ba0
static void slDrawInfo(void) {
  s32 v7;

  slCheckMsgDraw();
  if (gslInfoCode)
    goto LABEL_4;
  return;
  if (gslInfoCode)
  {
LABEL_4:
    if (gslInfoCode != 2)
    {
LABEL_13:
LABEL_14:
      v7 = gslInfoCode;
      slInfoMsgDraw(v7);
      return;
    }
    if (gslMode)
      goto LABEL_13;
    ++saveMsgCounter;
    goto LABEL_14;
  }
}

// 0x1b5e0c0
static void slCheckMsgDraw(void) {
  void *msgBase;
  void *v10;
  void *v11;

  if (gslInfoCode == 2)
    goto LABEL_52;
  if (gslInfoCode == 3)
    goto LABEL_52;
  if (gslInfoCode == 4)
    goto LABEL_52;
  if (gslInfoCode == 13)
    goto LABEL_52;
  if (gslInfoCode == 30)
    goto LABEL_52;
  if (gslInfoCode == 100)
    goto LABEL_52;
  if (slQueryYesNoCursor != -1)
  {
    if (slQueryYesNoMsg == 1)
      goto LABEL_52;
    if (slQueryYesNoMsg == 3)
      goto LABEL_52;
    if (slQueryYesNoMsg == 4)
      goto LABEL_52;
    if (slQueryYesNoMsg == 8)
      goto LABEL_52;
    if (slQueryYesNoMsg == 9)
      goto LABEL_52;
    if (slQueryYesNoMsg == 10)
      goto LABEL_52;
    if (slQueryYesNoMsg == 11)
      goto LABEL_52;
    if (slQueryYesNoMsg == 12)
    {
LABEL_52:
      msgBase = saveloadSystem->msgBase;
      fldSetupObject(msgBase, 1);
      slBlackScreenSet = 0;
      return;
    }
  }
  if (slBlackScreenSet)
  {
    v10 = saveloadSystem->msgBase;
    fldSetupObject(v10, 1);
  }
  else
  {
    v11 = saveloadSystem->msgBase;
    fldSetupObject(v11, 0);
  }
}

// 0x1b5ee30
void mcMakeFileName(char **path, s32 num) {
  ;
}

// 0x1b59ef0
static void slVersionConvert_Step1(void) {

}

// 0x1b5a260
static s32 slVersionConvert_GetSize(void) {
  return 0;
}

// 0x1b5a3c0
static void slVersionConvert_Step3(void) {
  ;
}

// 0x1b56b90
static s32 slGetPadTrig(bool map) {
  if (!map)
    return 0;
  return slProcShutDownFlg == 1;
}

// 0x1b5bd90
static s32 slGetPadRep(bool map) {
  if (!map)
    return 0;
  return slProcShutDownFlg == 1;
}

// 0x1b5ee40
static void slKanjiDraw3(s32 x, s32 y, u32 rgba, char **moji, s32 ot) {
  frEnableMode(1);
  frDisableMode(1);
  frSetFontSpace(slKanjiDraw3_handle, 1);
  frSetDrawPosition(slKanjiDraw3_handle, 16 * x, 8 * y);
  frSetFontColor(slKanjiDraw3_handle, rgba);
  frDrawFontEx2(slKanjiDraw3_handle, 1, ot);
  frDestroyFontRequestAfter(slKanjiDraw3_handle);
}

// 0x1b5ef70
static void slKanjiDrawH(s32 x, s32 y, s32 rgba, char **moji) {
  frEnableMode(1);
  frSetFontColorNo(slKanjiDrawH_handle, 3u);
  frDisableMode(1);
  frSetFontSpace(slKanjiDrawH_handle, 1);
  frSetDrawPosition(slKanjiDrawH_handle, 16 * x, 8 * y);
  frDrawFontEx2(slKanjiDrawH_handle, 0, 0x70u);
  frDestroyFontRequestAfter(slKanjiDrawH_handle);
  gFontDrawOT = 110;
}

// 0x1b5f110
static void slKanjiDrawN3(s32 x, s32 y, s32 rgba, char **moji, s32 ot) {
  ;
}

// 0x1b5ea70
static void slNextPageDraw(void) {
  int32x4_t *v1;
  f32 v4;
  f32 v5;
  f32 v6;
  f32 v7;
  f32 v8;
  f32 v9;
  f32 v10;
  f32 v11;
  u32 v12;

  v1 = NewSpecific(s32, 4u);
  v4 = slNextPageDraw_fc + 0.05;
  v5 = v4 * 0.15915494;
  slNextPageDraw_fc = v4;
  v6 = -2147500000.0;
  if (v5 != INFINITY)
    v6 = (s32)v5;
  v7 = v5 - v6;
  v8 = 0.5;
  if (v7 <= 0.5)
  {
    if (v7 >= -0.5)
      goto LABEL_12;
    v9 = 1.0;
  }
  else
  {
    v9 = -1.0;
  }
  v7 = v7 + v9;
LABEL_12:
  if (v7 <= 0.25)
  {
    if (v7 >= -0.25)
      goto LABEL_16;
    v8 = -0.5;
  }
  v7 = v8 - v7;
LABEL_16:
  v10 = v7 * 4.0;
  v11 = (f32)((f32)((f32)((f32)((f32)(v10 * 1.5707963) + (f32)((f32)(v10 * (f32)(v10 * v10)) * -0.6459637)) + (f32)((f32)((f32)(v10 * v10) * (f32)(v10 * (f32)(v10 * v10))) * 0.07968968)) + (f32)((f32)((f32)(v10 * v10) * (f32)((f32)(v10 * v10) * (f32)(v10 * (f32)(v10 * v10)))) * -0.0046737655)) + (f32)((f32)((f32)(v10 * v10) * (f32)((f32)(v10 * v10) * (f32)((f32)(v10 * v10) * (f32)(v10 * (f32)(v10 * v10))))) * 0.00015148419))
      * 30.0;
  v12 = ((s32)v11 + 127) | 0x80808000;
  if (v11 == INFINITY)
    v12 = -2139062145;
  v1[2] = vdupq_n_s32(v12);
}

// 0x1b5f120
static void slMcAccessDraw(void) {
  ++gSlMcAccessCnt;
}

// 0x1b5e0b0
static s32 slChkWindowOpenDone(void) {
  return 1;
}

// 0x1b5f190
static s32 slChkWindowOpenDone2(void) {
  return 1;
}

// 0x1b5ea60
static s32 slDrawWindow(void) {
  return 1;
}

// 0x1b51310
void slSetInfo(s32 id) {
  if (!gslInfoCode)
    goto LABEL_4;
  slMessageClose();
LABEL_5:
  if (gslInfoCode)
    goto LABEL_6;
  gSlWindowCnt = 0;
  goto LABEL_7;
LABEL_4:
  goto LABEL_5;
LABEL_6:
LABEL_7:
  gslInfoCode = id;
  return;
}

// 0x1b55260
static void slMCardClear(void) {
  ;
}

// 0x1b51f10
static dds3ProcessFunc_t slExitWait(nextFuncDelegate nextFunc) {
  dds3ProcessFunc_t v6;

  dds3FadeOut(0, 0, 0, 0x1Eu);
  slExitWaitNextFunc = nextFunc;
  slExitWaitCnt = 40;
  v6 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
  _ctor(v6, 0, Method_Project_slMain_slExitWaitProc__, 0);
  return v6;
}

// 0x1b5f1a0
static dds3ProcessFunc_t slEndingTop(void) {
  void *titleObj;
  slQueryYesFuncDelegate v6;
  u8 *v7;
  slQueryYesFuncDelegate v8;
  intptr_t v9;
  s32 v10;
  s64 (__fastcall *method_ptr)();
  slQueryNoFuncDelegate v13;
  u8 *v14;
  slQueryNoFuncDelegate v15;
  intptr_t v16;
  s32 v17;
  s64 (__fastcall *v19)();
  void *v21;

  gslMode = 0;
  slSetInfo(0);
  gslErrorCode = 0;
  *(u64 *)&gslDrawFlagFile = 0x400000000LL;
  slBlackScreenSet = 0;
  titleObj = saveloadSystem->titleObj;
  fldSetupObject(titleObj, 0);
  fldSetupObject(saveloadSystem->slotParent, 0);
  fldSetupObject(saveloadSystem->moveU, 0);
  fldSetupObject(saveloadSystem->moveD, 0);
  v6 = Allocate(slQueryYesFuncDelegate);
  v7 = Method_Project_slMain_slTop__;
  v8 = v6;
  v9 = *((u64 *)Method_Project_slMain_slTop__ + 1);
  v6->method = Method_Project_slMain_slTop__;
  v6->method_ptr = v9;
  v6->m_target = 0;
  v10 = v7[82];
  v8->method_code = v8;
  if (!sub_3BDA00())
    goto LABEL_16;
  if (v10)
  {
    method_ptr = v8->method_ptr;
    v8->method_code = v8->m_target;
  }
  else
  {
    method_ptr = sub_86A0;
  }
  v8->invoke_impl = method_ptr;
  v8->extra_arg = sub_8640;
  v13 = Allocate(slQueryNoFuncDelegate);
  v14 = Method_Project_slMain_slEndingExit__;
  v15 = v13;
  v16 = *((u64 *)Method_Project_slMain_slEndingExit__ + 1);
  v13->method = Method_Project_slMain_slEndingExit__;
  v13->method_ptr = v16;
  v13->m_target = 0;
  v17 = v14[82];
  v15->method_code = v15;
  if (!sub_3BDA00())
  {
LABEL_16:
    v21 = sub_3BDC90(0, "Delegate to an instance method cannot have null 'this'.");
  }
  if (v17)
  {
    v19 = v15->method_ptr;
    v15->method_code = v15->m_target;
  }
  else
  {
    v19 = sub_8770;
  }
  v15->invoke_impl = v19;
  v15->extra_arg = sub_8710;
  return slQueryYesNo(v8, v15, 0, 1);
}

// 0x1b5f410
static dds3ProcessFunc_t slBootTop(void) {
  dds3ProcessFunc_t v3;

  slSetInfo(0);
  gslDrawFlagFile = 0;
  v3 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
  _ctor(v3, 0, Method_Project_slMain_slBootProc_CheckCard__, 0);
  return v3;
}

// 0x1b5f4d0
static dds3ProcessFunc_t slBootRetry(void) {
  dds3ProcessFunc_t v5;

  *(u64 *)&gslCheckCardWait = 0x10000003CLL;
  slSetInfo(1);
  gslDrawFlagBg = 1;
  gslDrawFlagFile = 1;
  v5 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
  _ctor(v5, 0, Method_Project_slMain_slBootProc_CheckCardR__, 0);
  return v5;
}

// 0x1b5d440
static dds3ProcessFunc_t slBootError(void) {
  slQueryYesFuncDelegate v4;
  u8 *v5;
  slQueryYesFuncDelegate v6;
  intptr_t v7;
  s32 v8;
  s64 (__fastcall *method_ptr)();
  slQueryNoFuncDelegate v11;
  u8 *v12;
  slQueryNoFuncDelegate v13;
  intptr_t v14;
  s32 v15;
  s64 (__fastcall *v17)();
  void *v19;

  gslDrawFlagBg = 1;
  slSetInfo(0);
  slQueryYesNoMsg = 5;
  v4 = Allocate(slQueryYesFuncDelegate);
  v5 = Method_Project_slMain_slExitToTitle__;
  v6 = v4;
  v7 = *((u64 *)Method_Project_slMain_slExitToTitle__ + 1);
  v4->method = Method_Project_slMain_slExitToTitle__;
  v4->method_ptr = v7;
  v4->m_target = 0;
  v8 = v5[82];
  v6->method_code = v6;
  if (!sub_3BDA00())
    goto LABEL_14;
  if (v8)
  {
    method_ptr = v6->method_ptr;
    v6->method_code = v6->m_target;
  }
  else
  {
    method_ptr = sub_86A0;
  }
  v6->invoke_impl = method_ptr;
  v6->extra_arg = sub_8640;
  v11 = Allocate(slQueryNoFuncDelegate);
  v12 = Method_Project_slMain_slBootRetry__;
  v13 = v11;
  v14 = *((u64 *)Method_Project_slMain_slBootRetry__ + 1);
  v11->method = Method_Project_slMain_slBootRetry__;
  v11->method_ptr = v14;
  v11->m_target = 0;
  v15 = v12[82];
  v13->method_code = v13;
  if (!sub_3BDA00())
  {
LABEL_14:
    v19 = sub_3BDC90(0, "Delegate to an instance method cannot have null 'this'.");
  }
  if (v15)
  {
    v17 = v13->method_ptr;
    v13->method_code = v13->m_target;
  }
  else
  {
    v17 = sub_8770;
  }
  v13->invoke_impl = v17;
  v13->extra_arg = sub_8710;
  return slQueryYesNo(v6, v13, 1, 1);
}

// 0x1b5d750
static dds3ProcessFunc_t slBootError2(void) {
  slQueryYesFuncDelegate v4;
  u8 *v5;
  slQueryYesFuncDelegate v6;
  intptr_t v7;
  s32 v8;
  s64 (__fastcall *method_ptr)();
  slQueryNoFuncDelegate v11;
  u8 *v12;
  slQueryNoFuncDelegate v13;
  intptr_t v14;
  s32 v15;
  s64 (__fastcall *v17)();
  void *v19;

  gslDrawFlagBg = 1;
  slSetInfo(0);
  slQueryYesNoMsg = 6;
  v4 = Allocate(slQueryYesFuncDelegate);
  v5 = Method_Project_slMain_slExitToTitle__;
  v6 = v4;
  v7 = *((u64 *)Method_Project_slMain_slExitToTitle__ + 1);
  v4->method = Method_Project_slMain_slExitToTitle__;
  v4->method_ptr = v7;
  v4->m_target = 0;
  v8 = v5[82];
  v6->method_code = v6;
  if (!sub_3BDA00())
    goto LABEL_14;
  if (v8)
  {
    method_ptr = v6->method_ptr;
    v6->method_code = v6->m_target;
  }
  else
  {
    method_ptr = sub_86A0;
  }
  v6->invoke_impl = method_ptr;
  v6->extra_arg = sub_8640;
  v11 = Allocate(slQueryNoFuncDelegate);
  v12 = Method_Project_slMain_slBootRetry__;
  v13 = v11;
  v14 = *((u64 *)Method_Project_slMain_slBootRetry__ + 1);
  v11->method = Method_Project_slMain_slBootRetry__;
  v11->method_ptr = v14;
  v11->m_target = 0;
  v15 = v12[82];
  v13->method_code = v13;
  if (!sub_3BDA00())
  {
LABEL_14:
    v19 = sub_3BDC90(0, "Delegate to an instance method cannot have null 'this'.");
  }
  if (v15)
  {
    v17 = v13->method_ptr;
    v13->method_code = v13->m_target;
  }
  else
  {
    v17 = sub_8770;
  }
  v13->invoke_impl = v17;
  v13->extra_arg = sub_8710;
  return slQueryYesNo(v6, v13, 1, 1);
}

// 0x1b55600
static dds3ProcessFunc_t slExitToTitleSub(void) {
  dds3AdminiCallSequence2(2, 0, 0, 0);
  return 0;
}

// 0x1b56e80
static dds3ProcessFunc_t slExitToTitle2(void) {
  dds3ProcessFunc_t v1;

  dds3FadeOut(0, 0, 0, 0x1Eu);
  v1 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
  _ctor(v1, 0, Method_Project_slMain_slExitToTitle2sub__, 0);
  return v1;
}

// 0x1b5f5a0
static dds3ProcessFunc_t slExitToTitle2sub(dds3ProcessID_t *procId) {
  if (dds3FadeCheck())
    return 0;
  *(u64 *)&gslExitType = 1;
  dds3AdminiCallSequence2(2, 2, 0, 0);
  return 0;
}

// 0x1b56c10
static dds3ProcessFunc_t slCancel(void) {
  nextFuncDelegate v5;
  u8 *v6;
  nextFuncDelegate v7;
  intptr_t v8;
  s32 v9;
  s64 (__fastcall *method_ptr)();
  void *v14;

  *(u64 *)&gslExitType = 2;
  if (gslMode != 1)
  {
    if (gslMode != 4)
      goto LABEL_21;
  }
  if (dds3SearchProcessName("fldProcSequence"))
    goto LABEL_21;
  if (!dds3SearchProcessName("lmpMainProc"))
    goto LABEL_18;
LABEL_21:
  slSetInfo(0);
  v5 = Allocate(nextFuncDelegate);
  v6 = Method_Project_slMain_slExit__;
  v7 = v5;
  v8 = *((u64 *)Method_Project_slMain_slExit__ + 1);
  v5->method = Method_Project_slMain_slExit__;
  v5->method_ptr = v8;
  v5->m_target = 0;
  v9 = v6[82];
  v7->method_code = v7;
  if (!sub_3BDA00())
  {
    v14 = sub_3BDC90(0, "Delegate to an instance method cannot have null 'this'.");
  }
  if (v9)
  {
    method_ptr = v7->method_ptr;
    v7->method_code = v7->m_target;
  }
  else
  {
    method_ptr = sub_89E0;
  }
  v7->invoke_impl = method_ptr;
  v7->extra_arg = sub_8980;
  return slExitWait(v7);
LABEL_18:
  if (dds3SearchProcessName("jimusyo_calc"))
    goto LABEL_21;
  return slExitToTitle2();
}

// 0x1b5f680
static dds3ProcessFunc_t slEndingProc1st(dds3ProcessID_t *procId) {
  return slEndingTop();
}

// 0x1b5f6f0
static dds3ProcessFunc_t slBootProc1st(dds3ProcessID_t *procId) {
  *(u64 *)&gslCheckCardWait = 0x100000000LL;
  slSetInfo(0);
  gslDrawFlagFile = 0;
  return slBootTop();
}

// 0x1b5a540
static dds3ProcessFunc_t slHardSelect(void) {
  nextFuncDelegate v4;
  u8 *v5;
  nextFuncDelegate v6;
  intptr_t v7;
  s32 v8;
  s64 (__fastcall *method_ptr)();
  void *v12;

  dds3FadeOut(0, 0, 0, 0x1Eu);
  slSetInfo(0);
  gslHardSelectWait = 0;
  gslDrawFlagFile = 0;
  v4 = Allocate(nextFuncDelegate);
  v5 = Method_Project_slMain_slHardSelect1__;
  v6 = v4;
  v7 = *((u64 *)Method_Project_slMain_slHardSelect1__ + 1);
  v4->method = Method_Project_slMain_slHardSelect1__;
  v4->method_ptr = v7;
  v4->m_target = 0;
  v8 = v5[82];
  v6->method_code = v6;
  if (!sub_3BDA00())
  {
    v12 = sub_3BDC90(0, "Delegate to an instance method cannot have null 'this'.");
  }
  if (v8)
  {
    method_ptr = v6->method_ptr;
    v6->method_code = v6->m_target;
  }
  else
  {
    method_ptr = sub_89E0;
  }
  v6->invoke_impl = method_ptr;
  v6->extra_arg = sub_8980;
  return slHitAnyKeyNoChk(v6);
}

// 0x1b5f770
static dds3ProcessFunc_t slHardSelect1(void) {
  dds3ProcessFunc_t v6;

  if (gslHardSelectWait > 29)
  {
    slQueryYesNoMsg = 10;
    slBlackScreenSet = 0;
    sndBgmStop();
    sndBgmFree();
    gslExitTitle = 1;
    dds3AdminiCallSequence2(2, 3, 0, 0);
    v6 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
    _ctor(v6, 0, Method_Project_Kernel_DDS3_PROC_END__, 0);
    return v6;
  }
  gslHardSelectWait = gslHardSelectWait + 1;
  return 0;
}

// 0x1b5f900
static dds3ProcessFunc_t slHardSelect2(void) {
  nextFuncDelegate v5;
  u8 *v6;
  nextFuncDelegate v7;
  intptr_t v8;
  s32 v9;
  s64 (__fastcall *method_ptr)();
  void *v13;

  GBWK->EventBit[92] |= 0x20000u;
  slSetInfo(30);
  v5 = Allocate(nextFuncDelegate);
  v6 = Method_Project_slMain_slHardSelect3__;
  v7 = v5;
  v8 = *((u64 *)Method_Project_slMain_slHardSelect3__ + 1);
  v5->method = Method_Project_slMain_slHardSelect3__;
  v5->method_ptr = v8;
  v5->m_target = 0;
  v9 = v6[82];
  v7->method_code = v7;
  if (!sub_3BDA00())
  {
    v13 = sub_3BDC90(0, "Delegate to an instance method cannot have null 'this'.");
  }
  if (v9)
  {
    method_ptr = v7->method_ptr;
    v7->method_code = v7->m_target;
  }
  else
  {
    method_ptr = sub_89E0;
  }
  v7->invoke_impl = method_ptr;
  v7->extra_arg = sub_8980;
  return slHitAnyKeyNoChk(v7);
}

// 0x1b5fa60
static dds3ProcessFunc_t slHardSelect2N(void) {
  nextFuncDelegate v7;
  u8 *v8;
  nextFuncDelegate v9;
  intptr_t v10;
  s32 v11;
  s64 (__fastcall *method_ptr)();
  void *v15;

  GBWK->EventBit[92] &= ~0x20000u;
  sndBgmFadeOut2();
  slSetInfo(0);
  gslErrorCode = 0;
  gslDrawFlagFile = 0;
  v7 = Allocate(nextFuncDelegate);
  v8 = Method_Project_slMain_slHardSelect4__;
  v9 = v7;
  v10 = *((u64 *)Method_Project_slMain_slHardSelect4__ + 1);
  v7->method = Method_Project_slMain_slHardSelect4__;
  v7->method_ptr = v10;
  v7->m_target = 0;
  v11 = v8[82];
  v9->method_code = v9;
  if (!sub_3BDA00())
  {
    v15 = sub_3BDC90(0, "Delegate to an instance method cannot have null 'this'.");
  }
  if (v11)
  {
    method_ptr = v9->method_ptr;
    v9->method_code = v9->m_target;
  }
  else
  {
    method_ptr = sub_89E0;
  }
  v9->invoke_impl = method_ptr;
  v9->extra_arg = sub_8980;
  return slExitWait(v9);
}

// 0x1b5fc00
static dds3ProcessFunc_t slHardSelect3(void) {
  nextFuncDelegate v4;
  u8 *v5;
  nextFuncDelegate v6;
  intptr_t v7;
  s32 v8;
  s64 (__fastcall *method_ptr)();
  void *v12;

  sndBgmFadeOut2();
  slSetInfo(0);
  gslErrorCode = 0;
  gslDrawFlagFile = 0;
  v4 = Allocate(nextFuncDelegate);
  v5 = Method_Project_slMain_slHardSelect4__;
  v6 = v4;
  v7 = *((u64 *)Method_Project_slMain_slHardSelect4__ + 1);
  v4->method = Method_Project_slMain_slHardSelect4__;
  v4->method_ptr = v7;
  v4->m_target = 0;
  v8 = v5[82];
  v6->method_code = v6;
  if (!sub_3BDA00())
  {
    v12 = sub_3BDC90(0, "Delegate to an instance method cannot have null 'this'.");
  }
  if (v8)
  {
    method_ptr = v6->method_ptr;
    v6->method_code = v6->m_target;
  }
  else
  {
    method_ptr = sub_89E0;
  }
  v6->invoke_impl = method_ptr;
  v6->extra_arg = sub_8980;
  return slExitWait(v6);
}

// 0x1b5fd50
static dds3ProcessFunc_t slHardSelect4(void) {
  dds3ProcessFunc_t v1;

  v1 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
  _ctor(v1, 0, Method_Project_Kernel_DDS3_PROC_END__, 0);
  return v1;
}

// 0x1b5fdd0
static s32 sl1Ken(void) {
  return 20;
}

// 0x1b5c0f0
static s32 slSizeChk(void) {
  return 1;
}

// 0x1b5fde0
static dds3ProcessFunc_t slErrorWaitToFileMc(dds3ProcessID_t *procId) {
  bool v3;
  bool v4;

  if (gslErrorKeyFlag)
    goto LABEL_29;
  v3 = CHECK_TRIG(4096, 1);
  goto LABEL_9;
LABEL_13:
  if (slProcShutDownFlg != 1)
    goto LABEL_17;
LABEL_26:
  SE(0);
  gslErrorKeyFlag = 1;
  goto LABEL_29;
LABEL_9:
  if (v3)
    goto LABEL_13;
LABEL_17:
  v4 = CHECK_TRIG(4097, 1);
  if (!v4)
    goto LABEL_29;
  if (slProcShutDownFlg == 1)
    goto LABEL_26;
LABEL_29:
  if (gslErrorKeyFlag != 1)
    return 0;
  gslErrorCode = 0;
  return slFileSel();
}

// 0x1b60010
static dds3ProcessFunc_t slSaveProc_openFile(dds3ProcessID_t *procId) {
  intptr_t *v4;
  s32 v12;
  FsSaveData *v18;
  dds3GlobalWork_t *v19;
  FsSaveData *v20;
  s32 v22;
  dds3ProcessFunc_t v25;

  if (!slSaveWriteFile_dataWaitPtr)
  {
LABEL_11:
    if (gslCursorSelect)
    {
      if (gslCursorSelect == 1)
      {
        v12 = 21;
LABEL_28:
        v18 = saveData;
        v19 = GBWK;
LABEL_35:
        Save(v18, v12, v19, saveDataInit, 0);
        v4 = &Method_Project_slMain_slSaveProc_writeFile__;
        goto LABEL_36;
      }
      v20 = saveData;
      v22 = gslCursorSelect;
      v12 = v22 - 2;
      v18 = v20;
      v19 = GBWK;
      goto LABEL_35;
    }
    v12 = 20;
    goto LABEL_28;
  }
  if (!slSaveWriteFile_dataWaitPtr[0])
    goto LABEL_11;
  v4 = &Method_Project_slMain_slSaveProc_waitDataReady__;
LABEL_36:
  v25 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
  _ctor(v25, 0, *v4, 0);
  return v25;
}

// 0x1b60330
static dds3ProcessFunc_t slSaveProc_writeFile(dds3ProcessID_t *procId) {
  dds3ProcessFunc_t v2;

  v2 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
  _ctor(v2, 0, Method_Project_slMain_slSaveProc_closeFile__, 0);
  return v2;
}

// 0x1b603d0
static dds3ProcessFunc_t slSaveProc_closeFile(dds3ProcessID_t *procId) {
  return ((dds3ProcessFunc_t (intptr_t, intptr_t))slSaveWriteFile_endFunc->invoke_impl)(slSaveWriteFile_endFunc->method_code, slSaveWriteFile_endFunc->method);
}

// 0x1b60450
static dds3ProcessFunc_t slSaveProc_waitDataReady(dds3ProcessID_t *procId) {
  dds3ProcessFunc_t v4;

  if (baseIconFileHandle)
    return 0;
  v4 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
  _ctor(v4, 0, Method_Project_slMain_slSaveProc_writeFile__, 0);
  return v4;
}

// 0x1b60530
void fmProcTrigSequence(s32 mode) {
  pacFileHandle_t *v3;
  sdfPacDecodeResrcHandle_t *v4;
  void *inited;
  void *Instance;
  dds3ProcessFunc_t v13;
  dds3ProcessFunc_t v17;
  GameFileInfo_t *GameFileInfo;
  dds3ProcessFunc_t v24;
  char *LocalizeText;
  char *v27;
  void *v30;
  void *v31;
  dds3ProcessFunc_t v32;
  dds3ProcessFunc_t v36;
  bool v40;
  void *v44;
  void *v47;
  bool v48;
  void *v52;
  void *v54;
  void *titel1;
  void *titel2;
  dds3ProcessFunc_t v58;
  shutdownfuncDelegate v59;
  dds3Basic_t *basic;

  basic = 0;
  v3 = Allocate(pacFileHandle_t);
  _ctor(v3, 0);
  v4 = Allocate(sdfPacDecodeResrcHandle_t);
  _ctor(v4, 0);
  evtMoonDisableDraw(1);
  inited = InitBG();
  gSlBg = inited;
  *(u64 *)&gslDrawFlagBg = 1;
  gSlCampLoad = 0;
  gslLoadWait = gslLoadWait + 1;
  Instance = get_Instance(0);
  ItfButtonGuideSet(Instance, 0, 0);
  slMsgLoad();
  switch (mode)
  {
    case 0:
      v13 = Allocate(dds3ProcessFunc_t);
      _ctor(v13, 0, Method_Project_slMain_slSaveProc1st__, 0);
      slProcPtr = v13;
      goto LABEL_26;
    case 1:
      v17 = Allocate(dds3ProcessFunc_t);
      _ctor(v17, 0, Method_Project_slMain_slLoadProc1st__, 0);
      slProcPtr = v17;
      gSlCampLoad = 1;
      goto LABEL_39;
    case 2:
      gSlEndingMode = 1;
      GBWK->EventBit[92] |= 0x10000u;
      GameFileInfo = GBWK->GameFileInfo;
      ++GameFileInfo->endcnt;
      GameFileInfo->newfile = 1;
      v24 = Allocate(dds3ProcessFunc_t);
      _ctor(v24, 0, Method_Project_slMain_slEndingProc1st__, 0);
      slProcPtr = v24;
LABEL_26:
      LocalizeText = GetLocalizeText("SAVELOAD_L0041", 1);
      v27 = GetLocalizeText("SAVELOAD_L0042", 1);
      SlotDataTop = 2;
      *(u16 *)&susendOpenFlg = 0;
      v30 = saveloadSystem->slotData[0];
      fldSetupObject(v30, 0);
      v31 = saveloadSystem->slotData[1];
LABEL_68:
      fldSetupObject(v31, 0);
      goto LABEL_70;
    case 4:
      v36 = Allocate(dds3ProcessFunc_t);
      _ctor(v36, 0, Method_Project_slMain_slLoadProc1stBgm__, 0);
      slProcPtr = v36;
      goto LABEL_39;
    default:
      v32 = Allocate(dds3ProcessFunc_t);
      _ctor(v32, 0, Method_Project_slMain_slBootProc1st__, 0);
      slProcPtr = v32;
      gslDrawFlagBg = 0;
      if (mode != 4)
      {
        v27 = "";
        LocalizeText = "";
        goto LABEL_70;
      }
LABEL_39:
      LocalizeText = GetLocalizeText("SAVELOAD_L0043", 1);
      v27 = GetLocalizeText("SAVELOAD_L0044", 1);
      SlotDataTop = 2;
      v40 = checkAutoSaveData(saveData, 0);
      if (v40)
      {
        autoSaveOpenFlg = 1;
        v44 = saveloadSystem->slotData[1];
        fldSetupObject(v44, 1);
        SlotDataTop = 1;
      }
      else
      {
        autoSaveOpenFlg = 0;
        v47 = saveloadSystem->slotData[1];
        fldSetupObject(v47, 0);
      }
      v48 = checkSuspendData(saveData, 0);
      if (!v48)
      {
        susendOpenFlg = 0;
        v54 = saveloadSystem->slotData[0];
        v31 = v54;
        goto LABEL_68;
      }
      susendOpenFlg = 1;
      v52 = saveloadSystem->slotData[0];
      fldSetupObject(v52, 1);
      SlotDataTop = 0;
LABEL_70:
      titel1 = saveloadSystem->titel1;
      (titel1->klass->vtable._66_set_text.methodPtr)(titel1, LocalizeText, titel1->klass->vtable._66_set_text.method);
      titel2 = saveloadSystem->titel2;
      (titel2->klass->vtable._66_set_text.methodPtr)(titel2, v27, titel2->klass->vtable._66_set_text.method);
      fldSetupObject(saveloadObj, 1);
      v58 = Allocate(dds3ProcessFunc_t);
      _ctor(v58, 0, Method_Project_slMain_slCalc__, 0);
      v59 = Allocate(shutdownfuncDelegate);
      _ctor(v59, 0, Method_Project_slMain_slShutDownProcess__, 0);
      dds3StartProcess("FileMentCalc", 11016, 0, 0, v58, v59, 0);
      slProcShutDownFlg = 1;
      if (gSlEndingMode)
      {
        dds3FadeIn(0, 0, 0, 8u);
      }
      slSetInfo(0);
      *(u64 *)&gSlSaveMode = 0xFFFFFFFF00000000LL;
      slExitWaitCnt = 0;
      *(u64 *)&gslExitTitle = 0;
      gslExitType = 0;
      *(u64 *)&gslErrorKeyFlag = 0;
      *(u64 *)&gSlNowCardCheck = 0;
      *(u64 *)&gslErrorCode = 0;
      gslMode = mode;
      slQueryYesNoKeyFlag = 0;
      *(u64 *)&gslDrawFlagFile = 0;
      *(u64 *)&gSlMcAccessCnt = 0;
      basic = dds3GetActiveScene();
      if (basic)
      {
        dds3SceneBasicVisible(basic, 0);
      }
      return;
  }
}

// 0x1b55970
void checkFirstCursor(s32 mode) {
  s32 v8;
  u32 v9;
  s32 v11;
  s32 v12;
  u32 v14;
  s32 gslCursorSelect_local;
  u32 v16;
  s64 i;
  void *v18;
  bool v19;
  s64 v21;
  bool v22;
  void *v25;
  bool v28;
  void *v29;
  u32 v31;
  void *v33;
  void *v35;

  if (!slQueryYesNoKeyFlag)
    goto LABEL_8;
  return;
  if (!slQueryYesNoKeyFlag)
  {
LABEL_8:
    switch (mode)
    {
      case 0:
      case 2:
        if (bakSelectCursor > 1)
        {
          gslCursorSelect = bakSelectCursor;
LABEL_13:
          if (gslCursorSelect > 1)
            goto LABEL_41;
          gslCursorTop = SlotDataTop;
          goto LABEL_40;
        }
        v11 = checkSelectCursor(2);
        gslCursorSelect = v11;
        goto LABEL_13;
      case 1:
      case 4:
        v8 = bakSelectCursor;
        if ((v8 & 0x80000000) == 0)
        {
          if (v9)
          {
            gslCursorSelect = v8;
            goto LABEL_19;
LABEL_33:
LABEL_40:
            gslCursorSelect = SlotDataTop;
LABEL_41:
            gslCursorSelect_local = gslCursorSelect;
            if (gslCursorSelect_local == SlotDataTop)
            {
              if (!v14)
              {
                gslCursorSelect_local = SlotDataTop;
              }
              goto LABEL_51;
            }
            if (!v14)
            {
              gslCursorSelect_local = gslCursorSelect;
            }
            if (gslCursorSelect_local <= LODWORD(saveloadSystem->slotData->max_length) - 3)
            {
              if (!v16)
              {
                gslCursorSelect_local = gslCursorSelect;
              }
              gslCursorTop = gslCursorSelect_local - 1;
              if (SlotDataTop)
                goto LABEL_52;
              gslCursorSelect_local = gslCursorSelect;
              if (gslCursorSelect_local != 2)
                goto LABEL_52;
              if (fmSlotCheck(1))
                goto LABEL_52;
              gslCursorSelect_local = 0;
            }
            else
            {
              gslCursorSelect_local = LODWORD(saveloadSystem->slotData->max_length) - 3;
              if (!v16)
              {
                gslCursorSelect_local = LODWORD(saveloadSystem->slotData->max_length) - 3;
              }
            }
LABEL_51:
            gslCursorTop = gslCursorSelect_local;
LABEL_52:
            for (i = 4; ; ++i)
            {
              v21 = i - 4;
              if (i - 4 >= SLODWORD(saveloadSystem->slotData->max_length))
                return;
              v22 = fmSlotCheck(i - 4);
              if (v22)
                goto LABEL_60;
              goto LABEL_9002;
              if (v28)
              {
LABEL_60:
                v25 = *((void *)&saveloadSystem->slotData->obj.klass + i);
                fldSetupObject(v25, 1);
                goto LABEL_72;
              }
LABEL_9002:
              v29 = *((void *)&saveloadSystem->slotData->obj.klass + i);
              fldSetupObject(v29, 0);
LABEL_72:
              if (v21 != gslCursorSelect)
              {
                if (v31)
                {
                  v35 = *((void *)&saveloadSystem->slotCur->obj.klass + i);
                }
                else
                {
                  v35 = *((void *)&saveloadSystem->slotCur->obj.klass + i);
                }
                v18 = v35;
                v19 = 0;
                goto LABEL_54;
              }
              if (v31)
              {
                v33 = *((void *)&saveloadSystem->slotCur->obj.klass + i);
              }
              else
              {
                v33 = *((void *)&saveloadSystem->slotCur->obj.klass + i);
              }
              v18 = v33;
              v19 = 1;
LABEL_54:
              fldSetupObject(v18, v19);
            }
          }
          gslCursorSelect = bakSelectCursor;
LABEL_19:
          if (gslCursorSelect > SlotDataTop)
            goto LABEL_41;
          goto LABEL_33;
        }
        if (!v9)
        v12 = checkSelectCursor(0);
        gslCursorSelect = v12;
        goto LABEL_19;
      default:
        goto LABEL_41;
    }
  }
}

// 0x1b61060
s32 checkSelectCursor(s32 start) {
  s64 v4;
  s32 v5;
  GameFileInfo_t *gslInfo_local;
  s64 v7;
  u32 *v8;
  s32 v9;
  s32 v10;
  s32 v11;
  s32 v12;
  s32 v13;
  s32 v14;
  s64 i;
  bool v16;
  GameFileInfo_t *v17;
  s64 v18;
  u32 *v19;
  s32 v20;
  s32 v21;
  s32 v22;
  s32 v23;
  s32 v24;
  s32 v25;
  System_DateTime_o v27;
  System_DateTime_o v28;

  v27._dateData = 0;
  v28._dateData = 0;
  v4 = start + 4;
  v5 = start;
  goto LABEL_5;
  while (1)
  {
LABEL_5:
    gslInfo_local = gslInfo;
    if (v4 - 4 >= SLODWORD(gslInfo_local->max_length))
    {
      v5 = start;
      goto LABEL_18;
    }
    gslInfo_local = gslInfo;
    v7 = *((u64 *)&gslInfo_local->obj.klass + v4);
    if (*(u32 *)(v7 + 32))
      break;
    ++v4;
    ++v5;
  }
  v7 = *((u64 *)&gslInfo->obj.klass + v4);
  v8 = *(u32 **)(v7 + 96);
  v9 = v8[4];
  v10 = v8[5];
  v11 = v8[6];
  v12 = v8[7];
  v13 = v8[8];
  v14 = v8[9];
  _ctor_54889472((System_DateTime_o)&v28, v9, v10, v11, v12, v13, v14, 0);
LABEL_18:
  for (i = v5 + 1 + 4; ; ++i)
  {
    v17 = gslInfo;
    if ((s32)i - 4 >= SLODWORD(v17->max_length))
      break;
    v18 = *((u64 *)&v17->obj.klass + i);
    if (!*(u32 *)(v18 + 32))
      continue;
    v18 = *((u64 *)&gslInfo->obj.klass + i);
    v19 = *(u32 **)(v18 + 96);
    v20 = v19[4];
    v21 = v19[5];
    v22 = v19[6];
    v23 = v19[7];
    v24 = v19[8];
    v25 = v19[9];
    _ctor_54889472((System_DateTime_o)&v27, v20, v21, v22, v23, v24, v25, 0);
    v16 = op_GreaterThan(v28, v27, 0);
    if (!v16)
    {
      v5 = i - 4;
      v28._dateData = v27._dateData;
      goto LABEL_18;
    }
  }
  return v5;
}

// 0x1b612d0
bool fmSlotCheck(s32 loop) {
  s32 v11;
  u32 v12;
  s32 v13;
  s32 v15;
  s32 v18;

  if (loop != 1)
  {
    if (loop)
    {
      v11 = LODWORD(saveloadSystem->slotData->max_length) - 3;
      if (gslCursorSelect <= v11)
      {
        if ((u32)(loop - 5) >= 0xFFFFFFFD && SlotDataTop == gslCursorSelect)
        {
          if (v12)
          {
            if (autoSaveOpenFlg)
              v13 = 3;
            else
              v13 = 4;
          }
          else
          {
            if (autoSaveOpenFlg)
              v13 = 3;
            else
              v13 = 4;
          }
          v18 = gslCursorSelect;
          if (v18 <= loop)
          {
            v18 = gslCursorSelect;
            if (v18 + v13 > loop)
              return 1;
          }
          return 0;
        }
        if (v12)
        {
          if (gslCursorSelect - 1 > loop)
            return 0;
        }
        else
        {
          if (gslCursorSelect - 1 > loop)
            return 0;
        }
        return gslCursorSelect + 2 > loop;
      }
      if (v11 > loop)
        return 0;
      return 1;
    }
    if (!susendOpenFlg)
      return 0;
    if (!autoSaveOpenFlg)
    {
LABEL_39:
      if (!autoSaveOpenFlg)
      {
        if (gslCursorSelect <= 2)
          return 1;
      }
      return 0;
    }
    if (gslCursorSelect >= 2)
      goto LABEL_39;
    return 1;
  }
  if (!autoSaveOpenFlg)
    return 0;
  if (!susendOpenFlg)
    goto LABEL_58;
  v15 = gslCursorSelect;
  if (v15 < 0)
  {
LABEL_58:
    if (susendOpenFlg)
      return 0;
    return gslCursorSelect <= 2;
  }
  if (v15 >= 3)
    goto LABEL_58;
  return 1;
}

// 0x1b61700
void fmShutDownFade(void) {
  ;
}

// 0x1b5e780
void fmShutDown(void) {
  dds3Basic_t *basic;

  if (!slProcShutDownFlg)
    return;
  slProcShutDownFlg = 0;
  if (!gSlBg)
  {
LABEL_13:
    basic = dds3GetActiveScene();
    if (basic)
    {
      dds3SceneBasicVisible(basic, 1);
    }
    if (!baseIconFileHandle)
    {
LABEL_25:
      dds3KillProcessName("FileMentCalc", 1);
      Delete(0);
      fldSetupObject(saveloadObj, 0);
      return;
    }
    fileSync(baseIconFileHandle);
    baseIconFileHandle = 0;
    goto LABEL_25;
  }
  rstDestroyBG(gSlBg);
  gSlBg = 0;
  goto LABEL_13;
}

// 0x1b61710
bool fmShutDown2(void) {
  setAutoSaveDisable();
  return 1;
}

// 0x1b61790
s32 fmProcessChk(void) {
  return dds3SearchProcessName("FileMentCalc") != 0;
}

// 0x1b61810
s32 slGetExitType(void) {
  return gslExitType;
}

// 0x1b61890
s32 slGetExitTitle(void) {
  return gslExitTitle;
}

// 0x1b61910
s32 slGetExitMode(void) {
  return gSlExitMode;
}

// 0x1b61990
void slSetTmnlID(s32 type, s32 id) {
  s16 v3;
  s16 v4;
  Save_t *fldSave;

  v3 = id;
  v4 = type;
  fldSave = GBWK->fldSave;
  fldSave->tmnltype = v4;
  fldSave->tmnlid = v3;
}

// 0x1b5bef0
static void __MC_SelectCursor_AlphaSet(s32 alpha) {
  __MC_GLOBALWORK *mc_wk;

  mc_wk = __mc_wk;
  __mc_scwk->alpha = alpha;
  mc_wk->cnt = 0;
  mc_wk->alpha = 128;
}

// 0x1b5d210
static u32 __MC_RGBA_AlphaGet(u32 rgba, s32 alpha, u8 flg) {
  u32 v4;
  u32 v5;

  v4 = rgba & 0xFFFFFF | ((u8)alpha << 24);
  v5 = rgba & 0xFFFFFF00 | alpha;
  if (alpha >= (s32)HIBYTE(rgba))
    v4 = rgba;
  if (alpha >= (u8)rgba)
    v5 = rgba;
  if (flg)
    return v4;
  else
    return v5;
}

// 0x1b5c860
static void __MC_PanelFadeChk(void) {
  __MC_GLOBALWORK *mc_wk;
  u32 cnt;
  __MC_GLOBALWORK *v4;
  s32 v5;
  bool v6;

  mc_wk = __mc_wk;
  cnt = mc_wk->cnt;
  mc_wk->cnt = cnt + 1;
  if (cnt <= 0x7FFFFFFE)
  {
    if ((s32)(cnt + 1) > 11)
      goto LABEL_8;
    goto LABEL_9000;
    if (__mc_wk->cnt > 11)
    {
LABEL_8:
      mc_wk->cnt = 12;
      goto LABEL_15;
    }
LABEL_9000:
  }
  mc_wk->cnt = __mc_wk->cnt;
LABEL_15:
  v4 = __mc_wk;
  if (v4->cnt < 7)
    return;
  v5 = v4->alpha + 48;
  v6 = v4->alpha + 47 < 0;
  v4->alpha = v5;
  if (v6 == __OFSUB__(v5, 1))
  {
    if (v5 > 127)
    {
      v4->alpha = 128;
      return;
    }
  }
  v4->alpha = __mc_wk->alpha;
}

// 0x1b5ca10
static void __MC_SelectCursor_AlphaAnim(void) {
  __MC_SELECTCURSORWORK *mc_scwk;
  s32 v3;
  bool v4;

  mc_scwk = __mc_scwk;
  v3 = mc_scwk->alpha - 16;
  v4 = mc_scwk->alpha - 17 < 0;
  mc_scwk->alpha = v3;
  if (v4 == __OFSUB__(v3, 1))
  {
    if (v3 > 127)
    {
      mc_scwk->alpha = 128;
      return;
    }
  }
  mc_scwk->alpha = __mc_scwk->alpha;
}

// 0x1b5d240
static void __MC_FileNumber_Draw(s32 number, s32 x, s32 y, s32 alpha) {
  void *v5;

  v5 = NewSpecific(s32, 0x2Au);
  InitializeArray_55364416(v5, (System_RuntimeFieldHandle_o)Field__PrivateImplementationDetails__A43ED98E7AE0BA46F8C85738629728B22631D3AA815E79E0F59FC7642DBCB75D, 0);
}

// 0x1b5be10
static void __MC_MoveWindow_Set(u8 flg) {
  u32 v4;
  int8x8_t *mc_wk;

  goto LABEL_3;
LABEL_7:
  mc_wk = __mc_wk;
  goto LABEL_4;
LABEL_3:
  mc_wk = __mc_wk;
  mc_wk[4].n64_u8[0] = flg;
  mc_wk[4].n64_u32[1] = 0;
  if (!v4)
    goto LABEL_7;
LABEL_4:
  mc_wk[5].n64_u64[0] = vbsl_s8(vcltz_s32(vshl_n_s32(vdup_n_s32(flg == 1), 0x1Fu)), (int8x8_t)116, (int8x8_t)0x7400000000LL).n64_u64[0];
}

// 0x1b5c260
static void __MC_MoveWindow_AnimReset(void) {
  __MC_GLOBALWORK *mc_wk;

  mc_wk = __mc_wk;
  mc_wk->mv_y = 0;
  mc_wk->mvflg = 0;
  mc_wk->cnt = 0;
}

// 0x1b5cae0
static void __MC_MoveWindow_Anim(void) {
  __MC_GLOBALWORK *mc_wk;
  s32 mvflg;
  s32 v4;
  bool v5;
  s32 v6;
  __MC_GLOBALWORK *v7;
  __MC_GLOBALWORK *v8;
  __MC_GLOBALWORK *v10;
  s32 v11;
  __MC_GLOBALWORK *v12;
  __MC_GLOBALWORK *v13;
  u32 v14;
  s32 v15;
  u32 v16;
  __MC_GLOBALWORK *v17;
  s32 v18;
  u32 v19;
  __MC_GLOBALWORK *v20;
  s32 v21;
  s32 v22;
  s32 v23;
  u32 v24;
  u32 v25;

  mc_wk = __mc_wk;
  mvflg = mc_wk->mvflg;
  if (mvflg != 2)
    goto LABEL_4;
  v6 = mc_wk->mv_y + 20;
  v5 = mc_wk->mv_y + 19 < 0;
  mc_wk->mv_y = v6;
  if (v5 != __OFSUB__(v6, 1))
    goto LABEL_26;
  if (v6 > 109)
    goto LABEL_23;
  goto LABEL_9000;
  if (__mc_wk->mv_y > 109)
  {
LABEL_23:
    mc_wk->mv_y = 110;
    goto LABEL_30;
  }
LABEL_9000:
LABEL_26:
  mc_wk->mv_y = __mc_wk->mv_y;
LABEL_30:
  v7 = __mc_wk;
  if (v7->mv_y >= 110)
  {
    v7 = __mc_wk;
    v7->mv_y = 0;
    v7->mvflg = 0;
LABEL_32:
    v8 = __mc_wk;
    if (v8->mv_y > 79)
      goto LABEL_33;
    goto LABEL_45;
  }
  {
    goto LABEL_32;
  }
  v8 = __mc_wk;
  if (v8->mv_y > 79)
  {
LABEL_33:
    if (v8->u_alpha > 15)
    {
      goto LABEL_36;
    }
    v8 = __mc_wk;
    v8->u_alpha = 16;
LABEL_36:
    v10 = __mc_wk;
    v11 = v10->u_alpha + 32;
    v5 = v10->u_alpha + 31 < 0;
    v10->u_alpha = v11;
    if (v5 == __OFSUB__(v11, 1))
    {
      if (v11 > 127)
        goto LABEL_39;
      goto LABEL_9002;
      if (__mc_wk->u_alpha > 127)
      {
LABEL_39:
        v10->u_alpha = 128;
        goto LABEL_93;
      }
LABEL_9002:
    }
    v10->u_alpha = __mc_wk->u_alpha;
LABEL_93:
    v17 = __mc_wk;
    v22 = v17->d_alpha - 32;
    v5 = v17->d_alpha - 33 < 0;
    v17->d_alpha = v22;
    if (v5 == __OFSUB__(v22, 1))
    {
      if (v22 <= 127)
        goto LABEL_116;
      v17->d_alpha = 128;
      return;
    }
    goto LABEL_116;
  }
LABEL_45:
  v8->u_alpha = 0;
  goto LABEL_9003;
  if (!v16)
  {
    v17 = __mc_wk;
    v8->u_alpha = v17->u_alpha;
    if (!v24)
    {
      v17 = __mc_wk;
    }
LABEL_72:
    v18 = v17->d_alpha - 32;
    v5 = v17->d_alpha - 33 < 0;
    v17->d_alpha = v18;
    if (v5 == __OFSUB__(v18, 1))
    {
      if (v18 <= 127)
        goto LABEL_116;
      v17->d_alpha = 128;
      return;
    }
LABEL_116:
    v17->d_alpha = __mc_wk->d_alpha;
    return;
  }
LABEL_9003:
  v8->u_alpha = 0;
  v17 = v8;
  goto LABEL_72;
LABEL_4:
  if (mvflg != 1)
    return;
  v4 = mc_wk->mv_y - 20;
  v5 = mc_wk->mv_y + 89 < 0;
  mc_wk->mv_y = v4;
  if (v5 != __OFSUB__(v4, -109))
    goto LABEL_48;
  if ((v4 & 0x80000000) == 0)
    goto LABEL_18;
  goto LABEL_9005;
  if ((__mc_wk->mv_y & 0x80000000) == 0)
  {
LABEL_18:
    mc_wk->mv_y = 0;
    goto LABEL_52;
  }
LABEL_9005:
LABEL_48:
  mc_wk->mv_y = __mc_wk->mv_y;
LABEL_52:
  v12 = __mc_wk;
  if (v12->mv_y <= -110)
  {
    v12 = __mc_wk;
    v12->mv_y = 0;
    v12->mvflg = 0;
LABEL_54:
    v13 = __mc_wk;
    if (v13->mv_y > -31)
      goto LABEL_55;
    goto LABEL_63;
  }
  {
    goto LABEL_54;
  }
  v13 = __mc_wk;
  if (v13->mv_y > -31)
  {
LABEL_55:
    if (v14)
    {
      v15 = v13->u_alpha - 32;
      v5 = v13->u_alpha - 33 < 0;
      v13->u_alpha = v15;
      if (v5 != __OFSUB__(v15, 1))
        goto LABEL_100;
    }
    else
    {
      v13 = __mc_wk;
      v15 = v13->u_alpha - 32;
      v5 = v13->u_alpha - 33 < 0;
      v13->u_alpha = v15;
      if (v5 != __OFSUB__(v15, 1))
        goto LABEL_100;
    }
    if (v15 > 127)
      goto LABEL_79;
    goto LABEL_9006;
    if (__mc_wk->u_alpha > 127)
    {
LABEL_79:
      v13->u_alpha = 128;
      goto LABEL_104;
    }
LABEL_9006:
LABEL_100:
    v13->u_alpha = __mc_wk->u_alpha;
LABEL_104:
    v17 = __mc_wk;
    v23 = v17->d_alpha + 16;
    v5 = v17->d_alpha + 15 < 0;
    v17->d_alpha = v23;
    if (v5 == __OFSUB__(v23, 1))
    {
      if (v23 <= 127)
        goto LABEL_116;
      v17->d_alpha = 128;
      return;
    }
    goto LABEL_116;
  }
LABEL_63:
  if (v14)
  {
    v13->u_alpha = 0;
LABEL_82:
    v13->u_alpha = 0;
    v20 = v13;
    goto LABEL_83;
  }
  v13 = __mc_wk;
  v13->u_alpha = 0;
  if (v19)
    goto LABEL_82;
  v20 = __mc_wk;
  v13->u_alpha = v20->u_alpha;
  if (!v25)
  {
    v20 = __mc_wk;
  }
LABEL_83:
  v21 = v20->d_alpha + 16;
  v5 = v20->d_alpha + 15 < 0;
  v20->d_alpha = v21;
  if (v5 == __OFSUB__(v21, 1))
  {
    if (v21 > 127)
    {
      v20->d_alpha = 128;
      return;
    }
  }
  v20->d_alpha = __mc_wk->d_alpha;
}

// 0x1b61a10
s32 slGetInfo(void) {
  return gslInfoCode;
}

// 0x1b61a90
void slSetKayWait(void) {
  slProcShutDownFlg = 1;
  return;
}

// 0x1b61b20
void slSuspendKill(void) {
  fmShutDown();
}

// 0x1b61bd0
dds3ProcessFunc_t slSuspendProc(void) {
  GameFileInfo_t *v5;

  gslMode = 0;
  gslCursorSelect = 0;
  bakSelectCursor = 0;
  v5 = Allocate(GameFileInfo_t);
  _ctor(v5, 0);
  gslInfo[0] = v5;
  GBWK->fldSave->tmnltype = 1;
  return slSaveData_writeFile(0);
}

// 0x1b61ce0
dds3ProcessFunc_t slAutoSaveProc(void) {
  GameFileInfo_t *gslInfo_local;
  GameFileInfo_t *v5;

  gslMode = 5;
  gslInfo_local = gslInfo;
  gslCursorSelect = 1;
  bakSelectCursor = 1;
  v5 = Allocate(GameFileInfo_t);
  _ctor(v5, 0);
  gslInfo_local[1] = v5;
  GBWK->fldSave->tmnltype = 1;
  return slSaveData_writeFile(0);
}

// 0x1b61e00
void slInitAutoSave(void) {
  dds3ProcessFunc_t *p_AutoSaveFunc;

  p_AutoSaveFunc = &AutoSaveFunc;
  *p_AutoSaveFunc = 0;
  AutoSaveProc = 0;
}

// 0x1b61e80
bool slUpdateAutoSave(void) {
  dds3ProcessFunc_t v4;
  dds3ProcessFunc_t *v5;
  dds3ProcessFunc_t v8;
  dds3ProcessID_t *v9;
  void *processfunc;
  dds3ProcessFunc_t v11;
  dds3ProcessFunc_t v15;
  dds3ProcessFunc_t *p_AutoSaveFunc;
  dds3ProcessID_t *AutoSaveID_local;
  dds3ProcessFunc_t v21;
  dds3ProcessFunc_t *v22;
  dds3ProcessFunc_t v25;
  dds3ProcessID_t *v26;

  if (AutoSaveProc > 5)
    return 0;
  switch (AutoSaveProc)
  {
    case 0u:
      SetDisp(ctrl, 1, 0.0, 0);
      AutoSaveProc = 1;
      return 0;
    case 1u:
      v15 = slAutoSaveProc();
      p_AutoSaveFunc = &AutoSaveFunc;
      *p_AutoSaveFunc = v15;
      if (AutoSaveFunc)
      {
        AutoSaveID_local = AutoSaveID;
        AutoSaveID_local->processfunc = AutoSaveFunc;
      }
      AutoSaveProc = 2;
      return 0;
    case 2u:
      v21 = (AutoSaveID->processfunc->invoke_impl)(AutoSaveID->processfunc->method_code);
      v22 = &AutoSaveFunc;
      *v22 = v21;
      v25 = AutoSaveFunc;
      if (v25)
      {
        v25 = AutoSaveFunc;
        v26 = AutoSaveID;
        v26->processfunc = v25;
      }
      if (gslInfoCode == 4)
      {
        AutoSaveProc = 3;
        if (gslErrorKeyNoWait == 1)
          goto LABEL_61;
        goto LABEL_57;
      }
      if (gslErrorKeyNoWait == 1)
        goto LABEL_61;
LABEL_57:
      if (gslInfoCode != 100)
        return 0;
LABEL_61:
      AutoSaveProc = 5;
      return 0;
    case 3u:
    case 5u:
      v4 = (AutoSaveID->processfunc->invoke_impl)(AutoSaveID->processfunc->method_code);
      v5 = &AutoSaveFunc;
      *v5 = v4;
      v8 = AutoSaveFunc;
      if (v8)
      {
        v8 = AutoSaveFunc;
        v9 = AutoSaveID;
        v9->processfunc = v8;
      }
      processfunc = AutoSaveID->processfunc;
      v11 = Allocate(dds3ProcessFunc_t);
      _ctor(v11, 0, Method_Project_Kernel_DDS3_PROC_END__, 0);
      if (!op_Equality(processfunc, v11, 0))
        return 0;
      AutoSaveProc = 4;
      return 0;
    case 4u:
      SetDisp(ctrl, 0, 1.0, 0);
      return 1;
    default:
      return 0;
  }
}

// 0x1b623b0
void slInitSuspend(void) {
  dds3ProcessFunc_t *p_SuspendFunc;

  p_SuspendFunc = &SuspendFunc;
  *p_SuspendFunc = 0;
  SuspendProc = 0;
}

// 0x1b62430
s32 slUpdateSuspend(void) {
  s32 v5;
  dds3ProcessFunc_t v7;
  dds3ProcessFunc_t *p_SuspendFunc;
  dds3ProcessID_t *SuspendID_local;
  dds3ProcessFunc_t v15;
  dds3ProcessFunc_t *v16;
  dds3ProcessFunc_t v19;
  dds3ProcessID_t *v20;

  if (SuspendProc != 2)
    goto LABEL_4;
  v7 = (SuspendID->processfunc->invoke_impl)(SuspendID->processfunc->method_code);
  p_SuspendFunc = &SuspendFunc;
  *p_SuspendFunc = v7;
  if (SuspendFunc)
  {
    SuspendID_local = SuspendID;
    SuspendID_local->processfunc = SuspendFunc;
  }
  v5 = gslInfoCode == 4;
  if (gslInfoCode != 100)
  {
    if (gslErrorKeyNoWait == 1)
    {
      gslErrorKeyNoWait = 0;
      v5 = 3;
      goto LABEL_52;
    }
    if (gslInfoCode != 4)
      return v5;
    goto LABEL_52;
  }
  v5 = 2;
LABEL_52:
  SetDisp(ctrl, 0, 0.0, 0);
  return v5;
LABEL_4:
  if (SuspendProc == 1)
  {
    v15 = slSuspendProc();
    v16 = &SuspendFunc;
    *v16 = v15;
    v19 = SuspendFunc;
    if (v19)
    {
      v19 = SuspendFunc;
      v20 = SuspendID;
      v20->processfunc = v19;
    }
    SuspendProc = 2;
    return 0;
  }
  else
  {
    if (!SuspendProc)
    {
      SetDisp(ctrl, 1, 0.0, 0);
      v5 = 0;
      SuspendProc = 1;
      return v5;
    }
    return 0;
  }
}

// 0x1b60f90
static void slMsgLoad(void) {
  Create(0);
  fclLoadData("mc_sys.bmd", "fld_common", 1);
  Reset(0);
  mcMessageFlag = 0;
}

// 0x1b5e460
static void slChoiceMsgDraw(s32 msgNum) {
  s32 v6;
  s32 v7;
  Il2CppObject *v9;
  char *v10;
  s32 data;

  fclUpdateMessage();
  if (fclChkMessage())
    return;
  if (fclGetMessageWindowAlpha() > 0.0)
    return;
  if (mcMessageFlag)
    return;
  v6 = msgNum - 1;
  v7 = 2;
  switch (v6)
  {
    case 0:
      v7 = 1;
      goto LABEL_35;
    case 2:
      if (gslCursorSelect)
      {
        if (gslCursorSelect == 1)
        {
          v7 = 6;
        }
        else
        {
          data = gslCursorSelect - 1;
          v9 = Box(s32, &data);
          v10 = Format("{0:D}", v9, 0);
          frSetVariableRequest(0, v10);
          v7 = 4;
        }
      }
      else
      {
        v7 = 5;
      }
      goto LABEL_35;
    case 3:
      goto LABEL_35;
    case 7:
      v7 = 7;
      goto LABEL_35;
    case 8:
      v7 = 3;
      goto LABEL_35;
    case 9:
      v7 = 8;
      goto LABEL_35;
    case 10:
      v7 = 9;
      goto LABEL_35;
    case 11:
      v7 = 10;
LABEL_35:
      fclSetMessageInvalid(0);
      fclStartMessage(v7);
      fclStartSelMessage(0);
      mcMessageFlag = 1;
      break;
    default:
      return;
  }
}

// 0x1b5ec40
static void slInfoMsgDraw(s32 msgNum) {
  s32 v5;
  s32 v7;

  fclUpdateMessage();
  if (mcMessageFlag)
    return;
  if (msgNum <= 20)
  {
    v7 = msgNum - 2;
    v5 = 12;
    switch (v7)
    {
      case 0:
        v5 = 11;
        goto LABEL_27;
      case 1:
        goto LABEL_25;
      case 2:
        v5 = 13;
        goto LABEL_27;
      case 11:
        v5 = 14;
LABEL_25:
        goto LABEL_27;
      case 18:
        v5 = 20;
        goto LABEL_27;
      default:
        return;
    }
  }
  if (msgNum == 30)
  {
    v5 = 15;
  }
  else if ((u32)(msgNum - 34) > 0xFFFFFFFC)
  {
    v5 = 16;
  }
  else
  {
    if (msgNum != 100)
      return;
    v5 = 19;
  }
LABEL_27:
  fclSetMessageInvalid(0);
  fclStartMessage(v5);
  mcMessageFlag = 1;
}

// 0x1b58d70
static void slMessageClose(void) {
  mcMessageFlag = 0;
  SelectYesSe = -1;
  fclEndMessage();
}

// 0x1b62810
static void slMessageClear(void) {
  mcMessageFlag = 0;
  fclDelSelMessage();
}

// 0x1b628d0
bool slSaveDataCheck(void) {
  GameFileInfo_t *v1;
  s32 *v2;
  s64 v3;
  char *v4;
  GameFileInfo_t *v5;
  s32 v7;
  bool result;

  v1 = NewSpecific(GameFileInfo_t, 0x16u);
  if (*(s32 *)((char *)v1 + 24) < 1)
    return 0;
  v2 = v1;
  v3 = 0;
  v4 = &v1[0];
  do
  {
    v5 = Allocate(GameFileInfo_t);
    _ctor(v5, 0);
    if (v5)
      QueryInterface(v5, *(void **)(*(u64 *)v2 + 64));
    *(u64 *)v4 = v5;
    loadHeaderGameFileInfo(saveData, v3, v4, 0);
    v7 = *(u32 *)(*(u64 *)v4 + 32);
    result = v7 != 0;
    if (v7)
      break;
    ++v3;
    v4 += 8;
  }
  while (v3 < v2[6]);
  return result;
}

// 0x1b5bf70
static bool slFileCheckNameLanguage(s32 select) {
  s32 nameLang;

  goto LABEL_3;
LABEL_7:
  if (gslMode == 4)
    goto LABEL_9;
  return 1;
LABEL_3:
  if (gslMode != 1)
    goto LABEL_7;
LABEL_9:
  if (!gslStatFileInfo[select])
    return 1;
  nameLang = gslInfo[select]->nameLang;
  return nameLang == GetLanguage();
}
