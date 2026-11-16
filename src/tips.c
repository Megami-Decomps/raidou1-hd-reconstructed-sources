#include "types.h"
#include "buttonguide.h"
#include "cfg.h"
#include "cmpmain.h"
#include "dat.h"
#include "dds3_pad.h"
#include "dds3kernelcore.h"
#include "ditectivebook.h"
#include "evtbit.h"
#include "gohinit.h"
#include "itf.h"
#include "kernel.h"
#include "lmap.h"
#include "localize.h"
#include "rstinit.h"
#include "sbattle.h"
#include "sbtl.h"
#include "sbtlplayer.h"
#include "scr.h"
#include "sdfsound.h"
#include "tips.h"

typedef enum {
} TIPS_PAGEID;

typedef enum {
    TIPS_STAT_INIT = 0,
    TIPS_STAT_FADEIN = 1,
    TIPS_STAT_MAIN = 2,
    TIPS_STAT_PAGECHANGE = 3,
    TIPS_STAT_FADEOUT = 4,
    TIPS_STAT_END = 5,
} TIPS_STAT;

typedef enum {
    KEYTYPE_NONE = -1,
    KEYTYPE_UP = 0,
    KEYTYPE_DOWN = 1,
    KEYTYPE_RIGHT = 2,
    KEYTYPE_LEFT = 3,
} KEYTYPE;

typedef struct dds3ProcessID_t dds3ProcessID_t;
typedef struct fileLoadAsset_Request fileLoadAsset_Request;
typedef struct tipsPanelData tipsPanelData;
typedef struct tipsPanelDataAll tipsPanelDataAll;
typedef struct tips_tipsData_t tips_tipsData_t;

typedef void (*TipsCallBack)(void);

s32 pageCnt;
s32 TIPS_ID;
tipsPanelData *TIPS_ID_TABLE;
tipsPanelDataAll *TIPS_ID_TABLE_ALL;
dds3ProcessID_t *GlobalPID;
fileLoadAsset_Request *SceneLoadReq;
tips_tipsData_t *mainData;
s32 tipsMode;
bool tipsCanselFlag;
bool tipsCanselIDFlg;
char *TIPS_ASSET_NAME;
char *TIPSDATA_ASSET_NAME;
char *TIPSDATATABLE_NAME;
char *tipsProcessName;
char *tipsAllProcessName;
bool tutorialFlag;
s32 TIPS_MAX;
static s32 MENU_DRAW_MAX;
static s32 MENU_PARENT_MAX;
s32 childCnt;
s32 childSave;
s32 *parentID;
s32 *openStatus;
static TipsCallBack OnEvent;
static TipsCallBack OffEvent;
s32 *tutorialTIPS_All;
s32 *SortOderUpTIPS;
bool OderUpFlag;
static char *strMenuTitleText;
static char *strMenuHelpText;
static s32 now_Dest;

static void ButtonCommond(tips_tipsData_t *data, bool _boAll);
static void SetCommond(tips_tipsData_t *data);
static void SetCommondParent(tips_tipsData_t *data);
static bool MenuMoveCalc(tips_tipsData_t *wk);
static void MenuMoveStartCtrl(tips_tipsData_t *wk);
static void MenuCursorCtrlSub(tips_tipsData_t *wk);
static void CursorUp(tips_tipsData_t *wk);
static void CursorDown(tips_tipsData_t *wk);
static void CursorLeft(tips_tipsData_t *wk);
static void CursorRight(tips_tipsData_t *wk);
static void DrawMenuBeforeAfterSave(tips_tipsData_t *wk);
static void TextChangeCtrl(tips_tipsData_t *data, s32 _num);
static s32 RightStickCtrl(void);

// macros
// 0x2218100: s32 CALL_TIPS(void)
static inline s32 CALL_TIPS(void) {
  s32 IntPara;
  dds3ProcessID_t *v10;
  u32 v11;
  char *v15;

  IntPara = scrGetIntPara(0);
  if (!(!tutorialFlag || IntPara != 8))
  {
    tutorialFlag = 0;
    return 1;
  }
  tutorialFlag = 0;
  v10 = dds3SearchProcessName(tipsProcessName);
  if (v10)
  {
    if (v11)
    {
      goto LABEL_18;
    }
    else
    {
LABEL_18:
      goto LABEL_19;
    }
LABEL_19:
    v15 = tipsProcessName;
    if (!dds3SearchProcessName(v15))
      return 0;
    return mainData->mainStep == 5;
  }
  if (!v11)
  tipsTIPSStart(IntPara);
  return 0;
}

// 0x2218480: s32 CHACK_TRIAL(void)
static inline s32 CHACK_TRIAL(void) {
  scrSetIntReturnValue(0);
  return 1;
}

// 0x22184e0: s32 TIPS_WAIT_END(void)
#define TIPS_WAIT_END() (dds3SearchProcessName(tipsProcessName) == 0)

// 0x22159e0
dds3ProcessID_t *tipsTIPSStart_ALL(void) {
  dds3ProcessID_t *v1;
  tips_tipsData_t *v3;
  dds3ProcessFunc_t v8;
  shutdownfuncDelegate v9;
  dds3ProcessID_t *started;
  tips_tipsData_t *v14;
  s32 flag;
  s32 v16;
  tips_tipsData_t *v18;
  s32 *menu_draw;
  s64 v20;
  s32 v21;
  tips_tipsData_t *v22;
  s32 v23;
  tips_tipsData_t *v24;
  s32 v25;
  u32 v26;
  s32 *menu_Before;
  u64 v28;
  s64 v29;
  s32 *j;
  s32 v31;
  s64 v32;
  u64 i;
  s64 v37;
  s64 v38;
  tips_tipsData_t *v39;
  s64 v40;
  s64 v41;
  s64 v42;
  char *draw_text;

  v1 = Allocate(dds3ProcessID_t);
  _ctor(v1, 0);
  v3 = tipsTIPSInit_ALL();
  mainData = v3;
  tipsMode = 1;
  tipsCanselFlag = 0;
  v8 = Allocate(dds3ProcessFunc_t);
  _ctor(v8, 0, Method_Project_tips_TIPS_ALLProcess__, 0);
  v9 = Allocate(shutdownfuncDelegate);
  _ctor(v9, 0, Method_Project_tips_TIPSDestroy__, 0);
  started = dds3StartProcess(tipsAllProcessName, 1023, 0, 1, v8, v9, mainData);
  GlobalPID = started;
  v14 = mainData;
  flag = v14->flag;
  v14->cursor = 0;
  v14->cursor_old = 0;
  v14->index = 0;
  v14->top = 0;
  v14->flag = flag | 4;
  if (!!v14->parentID[0])
  {
    v16 = -1;
    v14->cursor_parent = -1;
    if (v14->parentID[1] != v14->cursor_old)
    {
      goto LABEL_23;
    }
    v16 = 1;
    goto LABEL_22;
  }
  v16 = 0;
LABEL_22:
  v14 = mainData;
LABEL_23:
  v14->cursor_parent = v16;
  v18 = mainData;
  menu_draw = v18->menu_draw;
  menu_draw[0] = v18->top;
  menu_draw[1] = v18->top + 1;
  menu_draw[2] = v18->top + 2;
  menu_draw[3] = v18->top + 3;
  menu_draw[4] = v18->top + 4;
  menu_draw[5] = v18->top + 5;
  menu_draw[6] = v18->top + 6;
  menu_draw[7] = v18->top + 7;
  menu_draw[8] = v18->top + 8;
  menu_draw[9] = v18->top + 9;
  menu_draw[10] = v18->top + 10;
  v20 = 8;
  v21 = -1;
  menu_draw[11] = v18->top + 11;
  do
  {
    while (1)
    {
      v22 = mainData;
      v23 = v21 + v22->menu_draw[0] < 1 ? -1 : v21 + v22->menu_draw[0];
      *((u32 *)&v22->menu_Before->obj.klass + v20) = v23;
      v24 = mainData;
      v25 = v20 + v24->menu_draw[11] - 7;
      if (v25 < v24->menu_num)
      {
        if (v26)
          goto LABEL_38;
        goto LABEL_37;
      }
      v25 = -1;
      if (v26)
        break;
LABEL_37:
LABEL_38:
      --v21;
      *((u32 *)&mainData->menu_After->obj.klass + v20++) = v25;
      if (v20 == 20)
        goto LABEL_54;
    }
    --v21;
    *((u32 *)&v24->menu_After->obj.klass + v20++) = -1;
  }
  while (v20 != 20);
LABEL_54:
  menu_Before = mainData->menu_Before;
  v28 = (u32)menu_Before[0];
  if ((v28 & 0x80000000) == 0)
  {
    if ((u32)v28 < 0xC)
    {
      for (i = 0; ; ++i)
      {
        if ((s64)i >= MENU_DRAW_MAX)
          break;
        if (i > v28)
        {
          mainData->menu_Before[i] = -1;
        }
        else
        {
          mainData->menu_Before[i] = i;
        }
      }
    }
    else
    {
      v29 = 0;
      for (j = &menu_Before[11]; ; --j)
      {
        if (v29 >= MENU_DRAW_MAX)
          break;
        v31 = *j;
        v32 = (s64)mainData->menu_Before + 4 * v29++;
        *(u32 *)(v32 + 32) = v31;
      }
    }
  }
  v37 = 0;
  v38 = 32;
  while (2)
  {
    draw_text = mainData->draw_text;
    if (!draw_text[v37])
    {
      draw_text = mainData->draw_text;
      draw_text[v37] = 0;
      v39 = mainData;
      v40 = (s64)v39->parent_save + 4 * v37;
      v41 = (s64)v39->id_save + 4 * v37;
      v42 = (s64)v39->type_save + 4 * v37;
      *(u32 *)(v40 + 32) = -1;
      *(u32 *)(v41 + 32) = -1;
      *(u32 *)(v42 + 32) = -1;
    }
    ++v37;
    v38 += 8;
    if (v37 != 128)
      continue;
    return started;
  }
}

// 0x2216bb0
void tipsTISPStartCalc(s32 TIPSID) {
  if (!OnEvent)
    goto LABEL_5;
  goto LABEL_4;
  if (OnEvent)
LABEL_4:
    (OnEvent->invoke_impl)(OnEvent->method_code, OnEvent->method);
LABEL_5:
  switch (TIPSID)
  {
    case 4:
      datRaidouSkillSetMaster(GBWK->player, 8, 1);
      GBWK->player->raidouSkill[1] = 8;
      goto LABEL_24;
    case 12:
      datRaidouSkillSetMaster(GBWK->player, 23, 1);
      GBWK->player->raidouSkill[0] = 23;
      goto LABEL_24;
    case 21:
      datRaidouSkillSetMaster(GBWK->player, 39, 1);
      GBWK->player->raidouSkill[2] = 39;
      goto LABEL_24;
    case 23:
      datRaidouSkillSetMaster(GBWK->player, 55, 1);
LABEL_24:
      sBtlRaidouWazaCoolTimeInit();
      break;
    default:
      return;
  }
}

// 0x2216e40
void tipsDestCall(s32 TIPSID) {
  s32 v4;
  s32 v6;

  now_Dest = 0;
  v4 = TIPSID - 1;
  if ((u32)(TIPSID - 1) <= 0x11)
  {
    switch (v4)
    {
      case 0:
        lmapSetBattleDestFlag(9);
        now_Dest = 1;
        return;
      case 2:
        lmapSetBattleDestFlag(11);
        now_Dest = 3;
        return;
      case 5:
        lmapSetBattleDestFlag(13);
        now_Dest = 6;
        return;
      case 7:
        if (cfgGetConfigGAME(7, 0))
          v6 = 19;
        else
          v6 = 15;
        lmapSetBattleDestFlag(v6);
        now_Dest = 8;
        return;
      case 17:
        lmapSetBattleDestFlag(17);
        now_Dest = 18;
        return;
      default:
        return;
    }
  }
}

// 0x2217170
void tipsReDestCall(void) {
  s32 v5;
  s32 encountno;

  if (!sbattleIsBattle())
    return;
  if (now_Dest)
  {
    v5 = now_Dest;
    tipsDestCall(v5);
    return;
  }
  encountno = wk->encountno;
  if (encountno != 514)
  {
    if (encountno != 513)
      return;
  }
  lmapSetBattleDestText();
}

// 0x2217330
void tipsReDestEnd(void) {
  now_Dest = 0;
  return;
}

// 0x22173b0
dds3ProcessID_t *tipsTIPSStart(s32 TIPSID) {
  dds3ProcessID_t *v3;
  s32 TIPS_ID_local;
  bool v8;
  s32 v10;
  s32 v12;
  s32 v13;
  s64 v15;
  s64 v16;
  s32 v20;
  tips_tipsData_t *v22;
  dds3ProcessFunc_t v27;
  shutdownfuncDelegate v28;
  dds3ProcessID_t *started;

  v3 = Allocate(dds3ProcessID_t);
  _ctor(v3, 0);
  tipsTISPStartCalc(TIPSID);
  TIPS_ID = TIPSID;
  if (TIPSID == 100)
    goto LABEL_33;
  TIPS_ID_local = TIPSID;
  TIPS_ID_local = TIPS_ID;
  v8 = evtBitCheck(TIPS_ID_local + 9984);
  if (!v8)
  {
    v10 = TIPS_ID;
    if (v10 <= 47)
      goto LABEL_22;
  }
  if (evtBitCheck(TIPS_ID + 9992))
    goto LABEL_33;
  v12 = TIPS_ID;
  if (v12 < 48)
    goto LABEL_33;
  v13 = v12 + 9992;
  if (!v13)
    goto LABEL_33;
  if ((u32)(v12 + 7374) >= 0xFFFFFFC6)
    evtBitKityouItemAdd(v13);
  LOBYTE(v10) = v13;
  goto LABEL_32;
LABEL_22:
  v13 = v10 + 9984;
  if (!v13)
    goto LABEL_33;
  if ((u32)(v10 + 7366) >= 0xFFFFFFC6)
    evtBitKityouItemAdd(v13);
LABEL_32:
  v15 = (s64)GBWK->EventBit + 4 * (v13 / 32);
  *(u32 *)(v15 + 32) |= 1 << v10;
LABEL_33:
  v16 = 0;
  while (1)
  {
    if (v16 >= SLODWORD(SortOderUpTIPS->max_length))
      break;
    v20 = SortOderUpTIPS[v16];
    if (v20 == TIPSID)
    {
      OderUpFlag = 1;
      break;
    }
    ++v16;
    OderUpFlag = 0;
  }
  v22 = tipsTIPSInit(TIPSID);
  mainData = v22;
  tipsMode = 0;
  tipsCanselFlag = 0;
  scrEventSkipEnd(0, 0);
  v27 = Allocate(dds3ProcessFunc_t);
  _ctor(v27, 0, Method_Project_tips_TIPS_Process__, 0);
  v28 = Allocate(shutdownfuncDelegate);
  _ctor(v28, 0, Method_Project_tips_TIPSDestroy__, 0);
  started = dds3StartProcess(tipsProcessName, 1023, 0, 1, v27, v28, mainData);
  GlobalPID = started;
  return started;
}

// 0x22185f0
void tipsTIPSDestroy(dds3ProcessID_t *PID) {
  struct tips *v4;
  char *tipsAllProcessName_local;
  UnityEngine_SceneManagement_Scene_o v17;

  tipsDestCall(TIPS_ID);
  GlobalPID = 0;
  TIPS_ID_TABLE = 0;
  v4 = ((char *)v4 + 8);
  *(&v4[-1].now_Dest + 1) = -1;
  SceneLoadReq = 0;
  pageCnt = 0;
  tipsCanselFlag = 0;
  OderUpFlag = 0;
  DeleteInsertImages(UI);
  UIDestroy(UI);
  v17.m_Handle = GetSceneByName("tips", 0).m_Handle;
  UnloadSceneAsync_61083440(v17, 0);
  if (tipsMode == 1)
  {
    tipsAllProcessName_local = tipsAllProcessName;
    goto LABEL_17;
  }
  if (tipsMode)
    goto LABEL_18;
  tipsAllProcessName_local = tipsProcessName;
LABEL_17:
  dds3KillProcessName(tipsAllProcessName_local, 0);
LABEL_18:
  tipsInit_Unload();
  tipsMode = 0;
  if (!OffEvent)
    return;
  goto LABEL_20;
  if (OffEvent)
LABEL_20:
    (OffEvent->invoke_impl)(OffEvent->method_code, OffEvent->method);
}

// 0x22183c0
s32 tipsProcessCheck(void) {
  return dds3SearchProcessName(tipsProcessName) != 0;
}

// 0x2218bc0
s32 tipsProcessCheck_tipsAll(void) {
  return dds3SearchProcessName(tipsAllProcessName) != 0;
}

// 0x2217880
tips_tipsData_t *tipsTIPSInit(s32 ID) {
  tips_tipsData_t *v2;
  void *Asset;
  s64 naturalAligment;
  void *v10;
  tipsPanelData *v11;
  tipsPanelData *v12;
  char *v13;
  char *v14;
  char *v15;
  tipsPanelData *panel;
  char *v17;
  tipsPanelData *v18;
  char *v19;
  char *v20;
  fileLoadAsset_Request *Asset__AllSceneAsync;
  s64 size;
  s64 v25;
  tipsPanelData *v26;
  tipsPanelData *TblDate;
  tipsPanelData *v28;
  u32 **v29;
  u32 *v31;
  s32 v33;
  u64 *v34;
  s32 v35;
  tipsPanelData *v36;
  s32 **p_panel_new;
  s32 *panel_new;
  s64 v39;
  s64 v40;
  tipsPanelData *v41;
  char *v42;
  char *v43;
  tipsPanelData *v45;
  s64 v47;
  s64 i;
  tipsPanelData *TIPS_ID_TABLE_local;
  Il2CppClass *v53;
  tipsPanelData *v54;
  s64 v57;
  s64 j;
  tipsPanelData *v60;
  Il2CppClass *v61;
  tipsPanelData *target;
  tips_tipsData_t *v64;
  s64 v65;

  v2 = Allocate(tips_tipsData_t);
  _ctor(v2);
  Load(Dependent, TIPSDATA_ASSET_NAME, TIPSDATA_ASSET_NAME);
  LoadSyncAll(_Ctrl_k__BackingField, 0);
  Asset = LoadAsset(_Ctrl_k__BackingField, TIPSDATA_ASSET_NAME, TIPSDATATABLE_NAME, 0);
  {
    if (Asset->klass->_2.typeHierarchy[naturalAligment - 1] == Project_TipsPanelDataTable)
      v10 = Asset;
    else
      v10 = 0;
  }
  else
  {
    v10 = 0;
  }
  v11 = NewSpecific(tipsPanelData, 0x80u);
  v65 = NewSpecific(tipsPanelData, 0x80u);
  v12 = Allocate(tipsPanelData);
  v13 = "";
  v12->text = "";
  v12->parent = -1;
  _ctor(v12, 0);
  v14 = "";
  v12->ID = -1;
  v12->title = v14;
  v15 = "";
  v12->page = -1;
  v12->text = v15;
  v12->parent = -1;
  v2->panel = v12;
  panel = v2->panel;
  v17 = "";
  panel->title = "";
  panel = ((char *)panel + 24);
  panel[-1].parent = -1;
  LODWORD(panel->monitor) = -1;
  v18 = v2->panel;
  v19 = "";
  v18->text = "";
  v20 = "tips";
  target = &v2->panel;
  *(u64 *)&v2->panel->image = -1;
  v2->nowpage = 0;
  v2->textChangeStep = 0;
  Asset__AllSceneAsync = AllSceneAsync(v20, 0);
  SceneLoadReq = Asset__AllSceneAsync;
  v64 = v2;
  size = (u32)v10->_arrPanel->_size;
  if ((s32)size > 0)
  {
    v25 = 0;
    v26 = &v11[0];
    do
    {
      TblDate = GetTblDate(v10, v25);
      v28 = TblDate;
      if (TblDate && !QueryInterface(TblDate, *(void **)(*(u64 *)v11 + 64)))
        goto LABEL_90;
      v26 = v28;
      ++v25;
      ++v26;
    }
    while (size != v25);
    v29 = &v11[0];
    while (1)
    {
      v31 = *v29;
      if (v31[4] == ID)
      {
        v33 = v31[8];
        if (v33 == pageCnt)
        {
          v34 = (v65 + 32 + 8 * pageCnt);
          *v34 = v31;
          ++pageCnt;
        }
      }
      ++v29;
      if (!--size)
        goto LABEL_47;
    }
  }
LABEL_47:
  v35 = pageCnt;
  if (v35 < 2)
    goto LABEL_59;
  v35 = pageCnt;
  v36 = NewSpecific(tipsPanelData, v35);
  v64->panel_new = v36;
  p_panel_new = &v64->panel_new;
  panel_new = v64->panel_new;
  if (panel_new[6] >= 1)
  {
    v39 = 0;
    v40 = 8;
    while (1)
    {
      v41 = Allocate(tipsPanelData);
      v42 = "";
      v43 = "";
      v43 = "";
      v41->text = v43;
      v41->parent = -1;
      _ctor(v41, 0);
      v41->ID = 0;
      v41->title = v42;
      v41->page = 0;
      v41->text = v42;
      v41->parent = -1;
      *(u64 *)&v41->image = -1;
      if (!QueryInterface(v41, *(void **)(*(u64 *)panel_new + 64)))
        break;
      *(u64 *)&panel_new[v40] = v41;
      panel_new = *p_panel_new;
      ++v39;
      v40 += 2;
      if (v39 >= (*p_panel_new)[6])
        goto LABEL_59;
    }
LABEL_90:
  }
LABEL_59:
  v45 = NewSpecific(tipsPanelData, pageCnt);
  TIPS_ID_TABLE = v45;
  v47 = 0;
  for (i = 32; ; i += 8)
  {
    if (v47 >= pageCnt)
      break;
    TIPS_ID_TABLE_local = TIPS_ID_TABLE;
    v53 = *(Il2CppClass **)(v65 + i);
    if (!v53)
    *(Il2CppClass **)((char *)&TIPS_ID_TABLE_local->obj.klass + i) = v53;
    ++v47;
  }
  v54 = TIPS_ID_TABLE[0];
  target = v54;
  if (pageCnt >= 2)
  {
    v57 = 0;
    for (j = 32; ; j += 8)
    {
      if (v57 >= pageCnt)
        break;
      v60 = v64->panel_new;
      v61 = *(Il2CppClass **)((char *)&TIPS_ID_TABLE->obj.klass + j);
      if (!v61)
      *(Il2CppClass **)((char *)&v60->obj.klass + j) = v61;
      ++v57;
    }
  }
  if (ID == 10)
  {
    ReceiptSet(9338);
  }
  return v64;
}

// 0x2218ad0
void tipsInit_Unload(void) {
  void *p_Dependent;
  void *Dependent_local;

  p_Dependent = &Dependent;
  Dependent_local = p_Dependent;
  Unload(Dependent_local, TIPS_ASSET_NAME, 0);
  Unload(Dependent, TIPSDATA_ASSET_NAME, 0);
}

// 0x2216240
tips_tipsData_t *tipsTIPSInit_ALL(void) {
  tips_tipsData_t *v1;
  void *Asset;
  s64 naturalAligment;
  void *v9;
  tipsPanelData *v10;
  tipsPanelDataAll *v11;
  s32 *v12;
  s64 v13;
  tipsPanelDataAll *v14;
  tipsPanelDataAll *v15;
  tips_tipsData_t_ChildSave *child_save;
  tips_tipsData_t_ChildSave *v20;
  tips_tipsData_t_ChildSave *v25;
  tips_tipsData_t_ChildSave *v26;
  tipsPanelData *v28;
  char *v29;
  char *v30;
  char *v31;
  tipsPanelData *panel;
  char *v33;
  tipsPanelData *v34;
  char *v35;
  char *v36;
  fileLoadAsset_Request *Asset__AllSceneAsync;
  s64 size;
  s64 v42;
  tipsPanelData *v43;
  tipsPanelData *TblDate;
  tipsPanelData *v45;
  s64 v46;
  s64 v47;
  s32 *v48;
  s64 *v55;
  void *v56;
  s64 v57;
  void *v58;
  s64 v59;
  s64 v62;
  s32 v65;
  s64 v66;
  s64 v67;
  tipsPanelDataAll *v68;
  s64 v70;
  s64 i;
  s32 *TIPS_ID_TABLE_ALL_local;
  tipsPanelDataAll *v74;
  s64 v76;
  s64 v77;
  u64 *v78;
  s64 v79;
  void *v80;
  s32 v81;
  s64 v82;
  void *v83;
  s32 v84;
  s64 v85;
  tips_tipsData_t *v89;
  s64 v90;

  v1 = Allocate(tips_tipsData_t);
  _ctor(v1);
  Load(Dependent, TIPSDATA_ASSET_NAME, TIPSDATA_ASSET_NAME);
  LoadSyncAll(_Ctrl_k__BackingField, 0);
  Asset = LoadAsset(_Ctrl_k__BackingField, TIPSDATA_ASSET_NAME, TIPSDATATABLE_NAME, 0);
  {
    if (Asset->klass->_2.typeHierarchy[naturalAligment - 1] == Project_TipsPanelDataTable)
      v9 = Asset;
    else
      v9 = 0;
  }
  else
  {
    v9 = 0;
  }
  v10 = NewSpecific(tipsPanelData, 0x80u);
  v11 = NewSpecific(tipsPanelDataAll, 0x80u);
  v12 = v11;
  if (*(s32 *)((char *)v11 + 24) >= 1)
  {
    v13 = 0;
    v14 = &v11[0];
    while (1)
    {
      v15 = Allocate(tipsPanelDataAll);
      _ctor_35738864(v15, 0, "", 0, "", -1, -1, -1, -1);
      if (v15)
      {
        if (!QueryInterface(v15, *(void **)(*(u64 *)v12 + 64)))
          break;
      }
      v14 = v15;
      ++v13;
      ++v14;
      if (v13 >= v12[6])
        goto LABEL_27;
    }
LABEL_87:
  }
LABEL_27:
  child_save = v1->child_save;
  parentID[0] = -1;
  v20 = Allocate(tips_tipsData_t_ChildSave);
  _ctor(v20);
  child_save[0] = v20;
  v25 = v1->child_save;
  parentID[1] = -1;
  v26 = Allocate(tips_tipsData_t_ChildSave);
  _ctor(v26);
  v25[1] = v26;
  v28 = Allocate(tipsPanelData);
  v29 = "";
  v28->text = "";
  v28->parent = -1;
  _ctor(v28, 0);
  v30 = "";
  v28->ID = -1;
  v28->title = v30;
  v31 = "";
  v28->page = -1;
  v28->text = v31;
  v28->parent = -1;
  v1->panel = v28;
  panel = v1->panel;
  v33 = "";
  panel->title = "";
  panel = ((char *)panel + 24);
  panel[-1].parent = -1;
  LODWORD(panel->monitor) = -1;
  v34 = v1->panel;
  v35 = "";
  v34->text = "";
  v36 = "tips";
  *(u64 *)&v1->panel->image = -1;
  v1->nowpage = 0;
  v1->textChangeStep = 0;
  Asset__AllSceneAsync = AllSceneAsync(v36, 0);
  SceneLoadReq = Asset__AllSceneAsync;
  v89 = v1;
  size = (u32)v9->_arrPanel->_size;
  if ((s32)size >= 1)
  {
    v42 = 0;
    v43 = &v10[0];
    while (1)
    {
      TblDate = GetTblDate(v9, v42);
      v45 = TblDate;
      if (TblDate)
      {
        if (!QueryInterface(TblDate, *(void **)(*(u64 *)v10 + 64)))
          goto LABEL_87;
      }
      v43 = v45;
      ++v42;
      ++v43;
      if (size == v42)
        goto LABEL_49;
    }
  }
  LODWORD(size) = 0;
LABEL_49:
  v46 = (u32)size;
  v47 = 0;
  v48 = v12 + 8;
  v90 = (u32)size;
  while (1)
  {
    if (v47 >= SLODWORD(tutorialTIPS_All->max_length))
      break;
    if (!!evtBitCheck(tutorialTIPS_All[v47] + 9984))
    {
      childCnt = 0;
      if ((u32)v46)
      {
        v55 = &v10[0];
        do
        {
          v62 = *v55;
          v65 = tutorialTIPS_All[v47];
          if (*(u32 *)(v62 + 16) == v65)
          {
            v66 = *(u64 *)&v48[2 * pageCnt];
            *(u32 *)(v66 + 16) = v65;
            v67 = *(u64 *)(v66 + 40);
            *(u64 *)(v66 + 48) = *(u64 *)(v62 + 48);
            v56 = *(void **)(v62 + 40);
            v57 = v67 + 8 * childCnt;
            *(u64 *)(v57 + 32) = v56;
            v58 = *(void **)(v62 + 24);
            v59 = *(u64 *)&v48[2 * pageCnt];
            *(u64 *)(v59 + 24) = v58;
            *(u32 *)(*(u64 *)&v48[2 * pageCnt] + 60) = childCnt;
            childCnt = childCnt + 1;
          }
          ++v55;
          --v46;
        }
        while (v46);
      }
      v46 = v90;
      ++pageCnt;
      ++childSave;
    }
    ++v47;
  }
  v68 = NewSpecific(tipsPanelDataAll, pageCnt);
  TIPS_ID_TABLE_ALL = v68;
  v70 = 0;
  for (i = 8; ; i += 2)
  {
    TIPS_ID_TABLE_ALL_local = TIPS_ID_TABLE_ALL;
    if (v70 >= TIPS_ID_TABLE_ALL_local[6])
      break;
    TIPS_ID_TABLE_ALL_local = TIPS_ID_TABLE_ALL;
    v74 = Allocate(tipsPanelDataAll);
    _ctor_35738864(v74, 0, "", 0, "", -1, -1, -1, -1);
    if (v74 && !QueryInterface(v74, *(void **)(*(u64 *)TIPS_ID_TABLE_ALL_local + 64)))
      goto LABEL_87;
    *(u64 *)&TIPS_ID_TABLE_ALL_local[i] = v74;
    ++v70;
  }
  v76 = 4;
  while (1)
  {
    if (v76 - 4 >= pageCnt)
      break;
    v77 = 2 * v76;
    v78 = *((u64 **)&TIPS_ID_TABLE_ALL->obj.klass + v76);
    v79 = *(u64 *)&v12[2 * v76];
    v80 = *(void **)(v79 + 40);
    v81 = *(u32 *)(v79 + 16);
    v78[5] = v80;
    v78 += 5;
    *((u32 *)v78 - 6) = v81;
    v78[1] = *(u64 *)(v79 + 48);
    v82 = *((u64 *)&TIPS_ID_TABLE_ALL->obj.klass + v76);
    v83 = *(void **)(*(u64 *)&v12[2 * v76] + 24);
    *(u64 *)(v82 + 24) = v83;
    v84 = v76++ - 4;
    v85 = *(s64 *)((char *)&TIPS_ID_TABLE_ALL->obj.klass + v77 * 4);
    *(u32 *)(v85 + 32) = v84;
    *(u64 *)(v85 + 56) = *(u64 *)(*(u64 *)&v12[v77] + 56);
  }
  return v89;
}

// 0x2218fd0
void tipsSetPanelDataTableSub(tipsPanelData *PanelDataTable, tipsPanelData *PanelDataTableSub, s32 ID) {
  s32 page;

  if (PanelDataTable->ID == ID)
  {
    page = PanelDataTable->page;
    if (page != pageCnt)
      return;
    PanelDataTableSub = PanelDataTable;
    ++pageCnt;
  }
}

// 0x2219180
void tipsSetPanelDataTable_ALL(tips_tipsData_t *data, tipsPanelData *PanelDataTable, tipsPanelDataAll *PanelDataTableSub, s32 ID) {
  tipsPanelDataAll *v8;
  char *text_all;
  char *text;
  Il2CppClass **v12;
  tipsPanelDataAll *v13;
  char *title;

  if (PanelDataTable->ID != ID)
    return;
  v8 = PanelDataTableSub;
  v8->ID = ID;
  text_all = v8->text_all;
  *(u64 *)&v8->image = *(u64 *)&PanelDataTable->image;
  text = PanelDataTable->text;
  v12 = &text_all->obj.klass + childCnt;
  v12[4] = text;
  v13 = PanelDataTableSub;
  title = PanelDataTable->title;
  v13->title = title;
  PanelDataTableSub->child = childCnt;
  childCnt = childCnt + 1;
}

// 0x2219270
s32 tipsGetTIPSID(void) {
  return TIPS_ID;
}

// 0x22192f0
dds3ProcessFunc_t tipsTIPS_Process(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  dds3ProcessFunc_t v7;
  char *v9;
  s32 v13;
  void *v16;
  s32 v17;
  f32 v18;
  s32 v19;
  char *v21;
  char *LocalizeText;
  char *v24;
  char *v27;
  char *v28;
  void *v34;
  s64 i;
  char *v38;
  char *v39;
  char *v41;
  char *v42;
  void *Instance;
  void *v45;
  char **v47;
  bool v48;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
  v7 = 0;
  switch (LODWORD(ProcessData[1].klass))
  {
    case 0:
      v9 = "";
      if (!SceneLoadReq->isDone)
        return 0;
      if (OderUpFlag)
        set_sortingOrder(UI->canvas, 41, 0);
      switch (HIDWORD(ProcessData[3].klass))
      {
        case 0:
          MenuActiveOnOff(UI, 0);
          set_sprite(UI->PanelImage, UI->PanelSpr[1], 0);
          v21 = *((char **)ProcessData[1].monitor + 3);
          LocalizeText = GetLocalizeText(v21, 1);
          v24 = tipsChangeTextPLTF(LocalizeText);
          PANEL_TitleTextSet(UI, v24);
          if (pageCnt >= 2)
          {
            for (i = 4; ; ++i)
            {
              if (i - 4 >= pageCnt)
                break;
              v38 = *(char **)(*((u64 *)&ProcessData[2].klass->_1.image + i) + 40);
              v39 = GetLocalizeText(v38, 1);
              v9 = Concat_54766928(v9, v39, 0);
              PANEL02_SetMessage(UI, v9, *(char **)(*((u64 *)&ProcessData[2].klass->_1.image + i) + 40));
              if (i - 4 < pageCnt - 1)
              {
                v41 = Concat_54766928(v9, "\n", 0);
                v42 = Concat_54766928(v41, "\n", 0);
                v9 = Concat_54766928(v42, "\n", 0);
              }
            }
          }
          else
          {
            v27 = *((char **)ProcessData[1].monitor + 5);
            v28 = GetLocalizeText(v27, 1);
            PANEL02_SetMessage(UI, v28, *((char **)ProcessData[1].monitor + 5));
          }
          SE(43);
          PANEL02_SetActive(UI, 1);
          set_alpha(UI->PANEL02->group, 0.0, 0);
          if (OderUpFlag)
          {
            ButtonGuideSet(UI);
          }
          else
          {
            Instance = get_Instance(0);
            ItfButtonGuideSet(Instance, 0, 0);
          }
          p2sdLoadSMGFile(4259840);
          goto LABEL_100;
        case 1:
          PANEL02_SpriteAssetCtrl(UI, 1);
          TextTagChange_next(UI, UI->PANEL02->message->messageText->TMProUGUI);
          goto LABEL_100;
        case 2:
          TagImageInsert(UI, tips_tipsData_t);
          goto LABEL_100;
        case 3:
          PANEL02_TextScrollReset(UI, tips_tipsData_t);
LABEL_100:
          v7 = 0;
          ++HIDWORD(ProcessData[3].klass);
          return v7;
        case 4:
          if (OderUpFlag)
          {
            ButtonGuideActive(UI, 1);
          }
          else
          {
            v45 = get_Instance(0);
            ItfButtonGuideActive(v45, 1, 0);
          }
          if (*((u32 *)ProcessData[1].monitor + 4) == 45)
          {
            v47 = &"TIPS02";
            goto LABEL_113;
          }
          v48 = !get_activeSelf(UI->PANEL02->message->scrollbar, 0);
          if (v48)
            v47 = &"TIPS01";
          else
            v47 = &"TIPS03";
LABEL_113:
          ButtonGuideDispSet(*v47, 0, 90);
          v19 = 1;
          v7 = 0;
LABEL_26:
          LODWORD(ProcessData[1].klass) = v19;
          break;
        case 5:
          v7 = 0;
          HIDWORD(ProcessData[3].klass) = 0;
          return v7;
        default:
          return 0;
      }
      return v7;
    case 1:
      *(f32 *)&ProcessData[2].monitor = *(f32 *)&ProcessData[2].monitor + 0.06666667;
      v13 = StringToHash("anim", 0);
      SetInteger_60664208(UI->PanelAnimStat, v13, 1, 0);
      set_alpha(UI->PANEL02->group, 1.0, 0);
      v7 = 0;
      if (*(f32 *)&ProcessData[2].monitor >= 0.99)
      {
        LODWORD(ProcessData[2].monitor) = 1065353216;
        LODWORD(ProcessData[1].klass) = 2;
        v7 = 0;
        tipsCanselFlag = 1;
      }
      return v7;
    case 2:
      if (CHECK_PRESS(41236, 1))
      {
        PANEL02_ScrollUp(UI);
        goto LABEL_58;
      }
      if (CHECK_PRESS(41237, 1))
        PANEL02_ScrollDown(UI);
LABEL_58:
      if (*((u32 *)ProcessData[1].monitor + 4) == 45)
      {
        v7 = 0;
        if (!CHECK_TRIG(4096, 1))
          return v7;
      }
      else
      {
        v7 = 0;
        if (!CHECK_TRIG(4097, 1))
          return v7;
      }
      LODWORD(ProcessData[1].klass) = 4;
      SE(44);
      return 0;
    case 4:
      DeleteInsertImages(UI, tips_tipsData_t);
      v16 = UI;
      v17 = StringToHash("anim", 0);
      SetInteger_60664208(v16->PanelAnimStat, v17, 2, 0);
      v7 = 0;
      v18 = *(f32 *)&ProcessData[2].monitor + -0.06666667;
      *(f32 *)&ProcessData[2].monitor = v18;
      if (v18 > 0.02)
        return v7;
      v19 = 5;
      v7 = 0;
      LODWORD(ProcessData[2].monitor) = 0;
      goto LABEL_26;
    case 5:
      if (gohProcessCheck())
      {
        goto LABEL_30;
      }
      p2sdUnLoadSMGFile(4259840, 1);
LABEL_30:
      if (OderUpFlag)
      {
        GuideDispStop(0);
        goto LABEL_74;
      }
      if (tipsGuideOffCheck())
      {
        v34 = get_Instance(0);
        ItfButtonGuideActive(v34, 0, 0);
      }
LABEL_74:
      v7 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
      _ctor(v7, 0, Method_Project_Kernel_DDS3_PROC_END__, 0);
      return v7;
    default:
      return v7;
  }
}

// 0x221aa20
dds3ProcessFunc_t tipsTIPS_ALLProcess(dds3ProcessID_t *PID) {
  tips_tipsData_t *ProcessData;
  s32 v9;
  s32 v10;
  f32 v11;
  void *Instance;
  dds3ProcessFunc_t v16;
  s32 v21;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
  switch (ProcessData->mainStep)
  {
    case 0:
      if (!SceneLoadReq->isDone)
        return 0;
      SetCommond(ProcessData);
      ProcessData->mainStep = 1;
      return 0;
    case 1:
      ProcessData->alpha = ProcessData->alpha + 0.06666667;
      v9 = StringToHash("anim", 0);
      SetInteger_60664208(UI->PanelAnimStat, v9, 1, 0);
      set_alpha(UI->PANEL02->group, 1.0, 0);
      if (ProcessData->alpha < 0.99)
        return 0;
      ProcessData->alpha = 1.0;
      v10 = 2;
      goto LABEL_23;
    case 2:
      if (!ProcessData->menu_move)
        goto LABEL_43;
      if (!MenuMoveCalc(ProcessData))
        goto LABEL_43;
      return 0;
LABEL_43:
      TextChangeCtrl(ProcessData, 1);
      MenuCursorCtrlSub(ProcessData);
      if (CHECK_PRESS(41236, 1))
      {
        PANEL02_ScrollUp(UI);
      }
      else if (CHECK_PRESS(41237, 1))
      {
        PANEL02_ScrollDown(UI);
      }
      if (ProcessData->panel->ID == 45)
      {
        if (CHECK_TRIG(4096, 1))
        {
          v21 = 44;
LABEL_54:
          ProcessData->mainStep = 4;
          SE(v21);
          return 0;
        }
      }
      else if (CHECK_TRIG(4097, 1))
      {
        v21 = 18;
        goto LABEL_54;
      }
      return 0;
    case 4:
      v11 = ProcessData->alpha + -0.06666667;
      ProcessData->alpha = v11;
      if (v11 > 0.02)
        return 0;
      v10 = 5;
      ProcessData->alpha = 0.0;
LABEL_23:
      ProcessData->mainStep = v10;
      return 0;
    case 5:
      if (gohProcessCheck())
      {
        goto LABEL_27;
      }
      p2sdUnLoadSMGFile(4259840, 1);
LABEL_27:
      if (!!tipsGuideOffCheck())
      {
        Instance = get_Instance(0);
        ItfButtonGuideActive(Instance, 0, 0);
      }
      v16 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
      _ctor(v16, 0, Method_Project_Kernel_DDS3_PROC_END__, 0);
      return v16;
    default:
      return 0;
  }
}

// 0x221a890
static void ButtonCommond(tips_tipsData_t *data, bool _boAll) {
  s32 v4;

  if (data->panel->ID == 45)
  {
    if (!CHECK_TRIG(4096, 1))
      return;
    v4 = 44;
    data->mainStep = 4;
    goto LABEL_4;
  }
  if (CHECK_TRIG(4097, 1))
  {
    data->mainStep = 4;
    if (boAll)
      v4 = 18;
    else
      v4 = 44;
LABEL_4:
    SE(v4);
  }
}

// 0x221af50
static void SetCommond(tips_tipsData_t *data) {
  void *v5;
  s32 v6;
  void *v9;
  s64 i;
  char *LocalizeText;
  char *v14;
  tipsPanelDataAll *TIPS_ID_TABLE_ALL_local;
  char *v21;
  void *v22;
  s64 cursor;
  s64 v24;
  s64 j;
  void *v26;
  void *Instance;
  void *v30;

  if (!get_activeSelf(UI->TIPS_MENU, 0))
    SetActive(UI->TIPS_MENU, 1, 0);
  v5 = UI;
  v6 = StringToHash("anim", 0);
  if (GetInteger_60663792(v5->MenuAnimStat, v6, 0) != 1)
    SetInteger_60664208(v5->MenuAnimStat, v6, 1, 0);
  set_sprite(UI->PanelImage, UI->PanelSpr[0], 0);
  v9 = UI;
  TipsMenuObj(v9, TIPS_ID_TABLE_ALL->max_length, 0);
  TipsMenuCursorAlpha(UI, TIPS_ID_TABLE_ALL->max_length, 0);
  for (i = 4; ; ++i)
  {
    TIPS_ID_TABLE_ALL_local = TIPS_ID_TABLE_ALL;
    if (i - 4 >= SLODWORD(TIPS_ID_TABLE_ALL_local->max_length))
      break;
    v21 = *(char **)(*((u64 *)&TIPS_ID_TABLE_ALL_local->obj.klass + i) + 24);
    LocalizeText = GetLocalizeText(v21, 1);
    v14 = tipsChangeTextPLTF(LocalizeText);
    TipsMenuTextChange(UI, i - 4, v14);
    TipsMenuObjSave(UI, data, i - 4, *(u32 *)(*((u64 *)&TIPS_ID_TABLE_ALL->obj.klass + i) + 16));
  }
  v22 = UI;
  cursor = (u32)mainData->cursor;
  v24 = -cursor;
  for (j = 4; j != 132; ++j)
  {
    v26 = *((void *)&v22->MenuObjList->obj.klass + j);
    if (op_Equality(v26, 0, 0))
      break;
    SetActive(*(void *)(*((u64 *)&v22->MenuObjList->obj.klass + j) + 48), v24 + j == 4, 0);
  }
  PANEL_TitleTextSet(UI, "");
  selMenuSetScrollBar(UI, data->menu_num);
  Instance = get_Instance(0);
  ItfButtonGuideSet(Instance, 0, 0);
  v30 = get_Instance(0);
  ItfButtonGuideActive(v30, 1, 0);
}

// 0x221cb60
static void SetCommondParent(tips_tipsData_t *data) {
  s64 v2;
  void *UI_local;
  u64 *v4;
  s64 i;
  void *v7;
  void *v8;
  char *title;
  char *LocalizeText;
  void *v12;
  void *TMProUGUI;
  char *v14;
  void *v16;
  tipsPanelDataAll *v17;
  s32 j;
  s32 v20;
  tipsPanelDataAll *TIPS_ID_TABLE_ALL_local;
  s64 v22;
  char *v24;
  char *v25;
  void *v26;
  s64 parent;
  Il2CppObject *Item;
  char *v29;
  Il2CppObject *v30;
  tipsPanelDataAll *v33;
  s32 child;
  char *v36;

  v2 = 32;
  UI_local = UI;
  do
  {
    v4 = ((char *)&UI_local->MenuObjList->obj.klass + v2);
    *v4 = 0;
    v2 += 8;
  }
  while (v2 != 1056);
  for (i = 0; i != 2; ++i)
  {
    if (parentID[i] == -1)
      continue;
    v8 = UI;
    if (!get_activeSelf(v8->MenuList[i]->menuObj, 0))
      SetActive(v8->MenuList[i]->menuObj, 1, 0);
    title = TIPS_ID_TABLE_ALL[parentID[i]]->title;
    LocalizeText = GetLocalizeText(title, 1);
    v12 = UI;
    TMProUGUI = v12->MenuList[i]->menuUIParent->messageParent->TMProUGUI;
    v14 = (TMProUGUI->klass->vtable._65_get_text.methodPtr)(TMProUGUI, TMProUGUI->klass->vtable._65_get_text.method);
    v36 = LocalizeText;
    if (op_Inequality(v14, LocalizeText, 0))
    {
      v16 = v12->MenuList[i]->menuUIParent->messageParent->TMProUGUI;
      (v16->klass->vtable._66_set_text.methodPtr)(v16, LocalizeText, v16->klass->vtable._66_set_text.method);
    }
    v17 = TIPS_ID_TABLE_ALL[parentID[i]];
    ChildMenuObjCtrl(UI, v17->parent, v17->child, 0);
    for (j = 1; ; ++j)
    {
      v20 = j - 1;
      TIPS_ID_TABLE_ALL_local = TIPS_ID_TABLE_ALL;
      v22 = parentID[i];
      v33 = TIPS_ID_TABLE_ALL_local[v22];
      child = v33->child;
      if (j - 1 >= child)
        break;
      TIPS_ID_TABLE_ALL_local = TIPS_ID_TABLE_ALL;
      LODWORD(v22) = parentID[i];
      v24 = *(char **)(*((u64 *)&TIPS_ID_TABLE_ALL_local[(s32)v22] + j) + 24);
      v25 = GetLocalizeText(v24, 1);
      v26 = UI;
      parent = TIPS_ID_TABLE_ALL[parentID[i]]->parent;
      Item = _get_Item(v26->MenuList[parent]->menuUIChild, v20);
      v29 = (*(*(u64 *)Item[4].klass->_1.namespaze + 1352))(Item[4].klass->_1.namespaze, *(u64 *)(*(u64 *)Item[4].klass->_1.namespaze + 1360));
      if (op_Inequality(v29, v25, 0))
      {
        v30 = _get_Item(v26->MenuList[parent]->menuUIChild, v20);
        (*(*(u64 *)v30[4].klass->_1.namespaze + 1368))(v30[4].klass->_1.namespaze, v25, *(u64 *)(*(u64 *)v30[4].klass->_1.namespaze + 1376));
      }
    }
    v7 = UI;
    v33 = TIPS_ID_TABLE_ALL[parentID[i]];
    child = v33->child;
    MenuObjSave(v7, data, v33->parent, child, openStatus[i], v36);
  }
}

// 0x221b330
static bool MenuMoveCalc(tips_tipsData_t *wk) {
  s32 moveCount;
  s32 v4;
  s64 v5;
  void *UI_local;
  f32 v7;
  bool v8;
  s32 top;
  s32 draw;
  s32 v11;
  s32 *menu_draw;
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
  s32 v25;
  s32 menu_child;
  void *v27;
  tipsUI_MENU_BAR_NEW *MenuList;
  s32 *menu_drawOld;
  char v31;
  s64 max_length;
  s32 *m_Items;
  s32 v34;
  s32 menu_num;
  bool v36;
  bool v37;
  s32 v38;
  s32 v39;
  s32 v40;
  s32 v41;
  s32 v42;
  s32 v43;
  s32 v44;
  s32 v45;
  s32 v46;
  s32 v47;
  s32 v48;
  s32 v49;
  s32 v50;
  s32 v51;
  s32 v52;
  s64 v53;
  void *v54;
  f32 v55;
  s32 v56;
  s64 v57;
  void *v58;
  f32 v59;
  void *v60;
  sdfVector2_t anchoredPosition;
  sdfVector2_t v63;
  sdfVector2_t v64;
  sdfVector2_t v65;
  sdfVector2_t v66;
  sdfVector2_t v67;
  sdfVector2_t v68;
  sdfVector2_t v69;
  sdfVector2_t v70;

  moveCount = wk->moveCount;
  if (moveCount <= 14)
  {
    if (wk->open_flag)
    {
      v4 = wk->cursor_parent + 1;
      if (v4 <= 1)
      {
        v5 = v4 + 4;
        UI_local = UI;
        v7 = (45 * wk->menu_child / 15);
        do
        {
          if (get_activeSelf(*(void *)(*((u64 *)&UI_local->MenuList->obj.klass + v5) + 16), 0))
          {
            anchoredPosition = get_anchoredPosition(*(void *)(*((u64 *)&UI_local->MenuList->obj.klass + v5) + 24), 0);
            v67.x = anchoredPosition.x;
            v67.y = anchoredPosition.y - v7;
            set_anchoredPosition(*(void *)(*((u64 *)&UI_local->MenuList->obj.klass + v5) + 24), v67, 0);
          }
          v8 = (u32)v5++ == 5;
        }
        while (!v8);
      }
      if (!wk->open_move)
        goto LABEL_92;
      if (wk->menu_child >= 13)
        menu_child = 11;
      else
        menu_child = wk->menu_child;
      v27 = UI;
      if (!get_activeSelf(v27->MenuList[1]->menuObj, 0))
      {
LABEL_91:
        wk->draw = menu_child;
        wk->menu_topChange = 1;
LABEL_92:
        ++wk->moveCount;
        return moveCount < 15;
      }
      v63 = get_anchoredPosition(v27->MenuList[1]->menuRect, 0);
      v68.x = v63.x;
      MenuList = v27->MenuList;
      v68.y = v63.y + (f32)(45 * menu_child / 15);
    }
    else
    {
      menu_drawOld = wk->menu_drawOld;
      if ((s32)menu_drawOld->max_length < 1)
        goto LABEL_83;
      menu_child = 0;
      v31 = 0;
      max_length = (u32)menu_drawOld->max_length;
      m_Items = menu_drawOld;
      do
      {
        v34 = *m_Items++;
        if (v34 == -1)
        {
          menu_num = wk->menu_num;
          v36 = menu_num <= 12;
          v37 = menu_num > 12;
          if (!v36)
            ++menu_child;
          v31 |= v37;
        }
        --max_length;
      }
      while (max_length);
      if ((v31 & 1) == 0)
      {
LABEL_83:
        v56 = wk->cursor_parent + 1;
        if (v56 <= 1)
        {
          v57 = v56 + 4;
          v58 = UI;
          v59 = (45 * wk->menu_child / 15);
          do
          {
            if (get_activeSelf(*(void *)(*((u64 *)&v58->MenuList->obj.klass + v57) + 16), 0))
            {
              v65 = get_anchoredPosition(*(void *)(*((u64 *)&v58->MenuList->obj.klass + v57) + 24), 0);
              v70.x = v65.x;
              v70.y = v65.y + v59;
              set_anchoredPosition(*(void *)(*((u64 *)&v58->MenuList->obj.klass + v57) + 24), v70, 0);
            }
            v8 = (u32)v57++ == 5;
          }
          while (!v8);
        }
        goto LABEL_92;
      }
      v52 = wk->cursor_parent + 1;
      if (v52 <= 1)
      {
        v53 = v52 + 4;
        v54 = UI;
        v55 = (45 * wk->menu_child / 15);
        do
        {
          if (get_activeSelf(*(void *)(*((u64 *)&v54->MenuList->obj.klass + v53) + 16), 0))
          {
            v64 = get_anchoredPosition(*(void *)(*((u64 *)&v54->MenuList->obj.klass + v53) + 24), 0);
            v69.x = v64.x;
            v69.y = v64.y + v55;
            set_anchoredPosition(*(void *)(*((u64 *)&v54->MenuList->obj.klass + v53) + 24), v69, 0);
          }
          v8 = (u32)v53++ == 5;
        }
        while (!v8);
      }
      v60 = UI;
      if (!get_activeSelf(v60->MenuList[1]->menuObj, 0))
        goto LABEL_91;
      v66 = get_anchoredPosition(v60->MenuList[1]->menuRect, 0);
      v68.x = v66.x;
      MenuList = v60->MenuList;
      v68.y = v66.y - (f32)(45 * menu_child / 15);
    }
    set_anchoredPosition(MenuList[1]->menuRect, v68, 0);
    goto LABEL_91;
  }
  if (wk->menu_topChange)
  {
    top = wk->top;
    draw = wk->draw;
    v11 = wk->menu_num;
    menu_draw = wk->menu_draw;
    if (wk->open_move)
    {
      v13 = top + draw;
      if (v13 >= v11)
        v13 = -1;
      menu_draw[0] = v13;
      v14 = wk->top + wk->draw;
      if (v14 + 1 < wk->menu_num)
        v15 = v14 + 1;
      else
        v15 = -1;
      menu_draw[1] = v15;
      v16 = wk->top + wk->draw + 2;
      if (v16 >= wk->menu_num)
        v16 = -1;
      menu_draw[2] = v16;
      v17 = wk->top + wk->draw + 3;
      if (v17 >= wk->menu_num)
        v17 = -1;
      menu_draw[3] = v17;
      v18 = wk->top + wk->draw + 4;
      if (v18 >= wk->menu_num)
        v18 = -1;
      menu_draw[4] = v18;
      v19 = wk->top + wk->draw + 5;
      if (v19 >= wk->menu_num)
        v19 = -1;
      menu_draw[5] = v19;
      v20 = wk->top + wk->draw + 6;
      if (v20 >= wk->menu_num)
        v20 = -1;
      menu_draw[6] = v20;
      v21 = wk->top + wk->draw + 7;
      if (v21 >= wk->menu_num)
        v21 = -1;
      menu_draw[7] = v21;
      v22 = wk->top + wk->draw + 8;
      if (v22 >= wk->menu_num)
        v22 = -1;
      menu_draw[8] = v22;
      v23 = wk->top + wk->draw + 9;
      if (v23 >= wk->menu_num)
        v23 = -1;
      menu_draw[9] = v23;
      v24 = wk->top + wk->draw + 10;
      if (v24 >= wk->menu_num)
        v24 = -1;
      menu_draw[10] = v24;
      v25 = wk->top + wk->draw;
    }
    else
    {
      v38 = top - draw;
      if (v38 >= v11)
        v38 = -1;
      menu_draw[0] = v38;
      v39 = wk->top - wk->draw;
      if (v39 + 1 < wk->menu_num)
        v40 = v39 + 1;
      else
        v40 = -1;
      menu_draw[1] = v40;
      v41 = wk->top - wk->draw + 2;
      if (v41 >= wk->menu_num)
        v41 = -1;
      menu_draw[2] = v41;
      v42 = wk->top - wk->draw + 3;
      if (v42 >= wk->menu_num)
        v42 = -1;
      menu_draw[3] = v42;
      v43 = wk->top - wk->draw + 4;
      if (v43 >= wk->menu_num)
        v43 = -1;
      menu_draw[4] = v43;
      v44 = wk->top - wk->draw + 5;
      if (v44 >= wk->menu_num)
        v44 = -1;
      menu_draw[5] = v44;
      v45 = wk->top - wk->draw + 6;
      if (v45 >= wk->menu_num)
        v45 = -1;
      menu_draw[6] = v45;
      v46 = wk->top - wk->draw + 7;
      if (v46 >= wk->menu_num)
        v46 = -1;
      menu_draw[7] = v46;
      v47 = wk->top - wk->draw + 8;
      if (v47 >= wk->menu_num)
        v47 = -1;
      menu_draw[8] = v47;
      v48 = wk->top - wk->draw + 9;
      if (v48 >= wk->menu_num)
        v48 = -1;
      menu_draw[9] = v48;
      v49 = wk->top - wk->draw + 10;
      if (v49 >= wk->menu_num)
        v49 = -1;
      menu_draw[10] = v49;
      v25 = wk->top - wk->draw;
    }
    v50 = wk->menu_num;
    v51 = v25 + 11;
    wk->menu_topChange = 0;
    if (v51 >= v50)
      v51 = -1;
    menu_draw[11] = v51;
    wk->top = menu_draw[0];
  }
  *(u16 *)&wk->open_move = 0;
  wk->moveCount = 0;
  return moveCount < 15;
}

// 0x221d700
static void MenuMoveStartCtrl(tips_tipsData_t *wk) {
  s64 cursor_parent;
  s64 v5;
  s32 v7;
  s32 v11;
  s64 v12;
  s32 *parentID_local;
  char *draw_text;
  s64 v15;
  s64 v16;
  s32 v21;
  s32 *v22;
  void *v24;
  s32 top;
  s32 *menu_drawOld;
  s32 v29;
  s32 v30;
  s32 v31;
  s32 v32;
  s32 v33;
  s32 v34;
  s32 v35;
  s32 v36;
  s32 v37;
  s32 v38;
  s32 v39;
  s32 v40;
  s32 *menu_Before;
  s32 v42;
  s32 v43;
  s32 v44;
  s32 *v45;
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
  s32 v59;
  s32 v60;
  s32 v61;
  s32 v62;
  s32 v63;
  s32 v64;
  s32 v65;
  s32 v66;
  s32 v67;

  if (wk->cursor_parent != -1 && CHECK_TRIG(4096, 1))
  {
    cursor_parent = wk->cursor_parent;
    v5 = wk->cursor_parent;
    if (openStatus[cursor_parent])
    {
      v7 = StringToHash("up_down", 0);
      if (GetInteger_60663792(UI->MenuList[v5]->menuSubAnim, v7, 0) != 2)
        SetInteger_60664208(UI->MenuList[v5]->menuSubAnim, v7, 2, 0);
      wk->open_flag = 0;
      openStatus[cursor_parent] = 0;
    }
    else
    {
      v11 = StringToHash("up_down", 0);
      if (GetInteger_60663792(UI->MenuList[v5]->menuSubAnim, v11, 0) != 1)
        SetInteger_60664208(UI->MenuList[v5]->menuSubAnim, v11, 1, 0);
      v12 = (s64)openStatus + 4 * cursor_parent;
      wk->open_flag = 1;
      *(u32 *)(v12 + 32) = 1;
      if (wk->top + 11 == wk->cursor)
        wk->open_move = 1;
    }
    parentID_local = wk->parentID;
    *(u64 *)&wk->parentID_Befor = 0;
    wk->menu_num = 0;
    if ((s32)parentID_local->max_length >= 1)
      sub_188E3B0(parentID_local, 255, 4 * (u32)parentID_local->max_length);
    draw_text = wk->draw_text;
    if (SLODWORD(draw_text->max_length) >= 1)
    {
      v15 = 0;
      v16 = 32;
      do
      {
        *(Il2CppClass **)((char *)&draw_text->obj.klass + v16) = 0;
        draw_text = wk->draw_text;
        ++v15;
        v16 += 8;
      }
      while (v15 < SLODWORD(draw_text->max_length));
    }
    SetCommondParent(wk);
    wk->menu_move = 1;
    v21 = !wk->open_flag;
    v22 = parentID;
    wk->menu_child = TIPS_ID_TABLE_ALL[v22[cursor_parent]]->child;
    v24 = UI;
    v22 = parentID;
    MenuCursorAlpha(v24, cursor_parent, TIPS_ID_TABLE_ALL[v22[cursor_parent]]->child, v21);
    if (wk->top >= wk->menu_num)
      top = -1;
    else
      top = wk->top;
    menu_drawOld = wk->menu_drawOld;
    menu_drawOld[0] = top;
    v29 = wk->top;
    if (v29 + 1 < wk->menu_num)
      v30 = v29 + 1;
    else
      v30 = -1;
    menu_drawOld[1] = v30;
    v31 = wk->top + 2;
    if (v31 >= wk->menu_num)
      v31 = -1;
    menu_drawOld[2] = v31;
    v32 = wk->top + 3;
    if (v32 >= wk->menu_num)
      v32 = -1;
    menu_drawOld[3] = v32;
    v33 = wk->top + 4;
    if (v33 >= wk->menu_num)
      v33 = -1;
    menu_drawOld[4] = v33;
    v34 = wk->top + 5;
    if (v34 >= wk->menu_num)
      v34 = -1;
    menu_drawOld[5] = v34;
    v35 = wk->top + 6;
    if (v35 >= wk->menu_num)
      v35 = -1;
    menu_drawOld[6] = v35;
    v36 = wk->top + 7;
    if (v36 >= wk->menu_num)
      v36 = -1;
    menu_drawOld[7] = v36;
    v37 = wk->top + 8;
    if (v37 >= wk->menu_num)
      v37 = -1;
    menu_drawOld[8] = v37;
    v38 = wk->top + 9;
    if (v38 >= wk->menu_num)
      v38 = -1;
    menu_drawOld[9] = v38;
    v39 = wk->top + 10;
    if (v39 >= wk->menu_num)
      v39 = -1;
    menu_drawOld[10] = v39;
    v40 = wk->top + 11;
    menu_Before = wk->menu_Before;
    if (v40 >= wk->menu_num)
      v40 = -1;
    menu_drawOld[11] = v40;
    v42 = menu_drawOld[0] - 1;
    if (v42 < 0)
      v42 = -1;
    menu_Before[0] = v42;
    v43 = menu_drawOld[11];
    if (v43 + 1 < wk->menu_num)
      v44 = v43 + 1;
    else
      v44 = -1;
    v45 = wk->menu_Before;
    wk->menu_After[0] = v44;
    v46 = menu_drawOld[0] - 2;
    if (v46 < 0)
      v46 = -1;
    wk->menu_Before[1] = v46;
    v47 = menu_drawOld[11] + 2;
    if (v47 >= wk->menu_num)
      v47 = -1;
    wk->menu_After[1] = v47;
    v48 = menu_drawOld[0] - 3;
    if (v48 < 0)
      v48 = -1;
    wk->menu_Before[2] = v48;
    v49 = menu_drawOld[11] + 3;
    if (v49 >= wk->menu_num)
      v49 = -1;
    wk->menu_After[2] = v49;
    v50 = menu_drawOld[0] - 4;
    if (v50 < 0)
      v50 = -1;
    wk->menu_Before[3] = v50;
    v51 = menu_drawOld[11] + 4;
    if (v51 >= wk->menu_num)
      v51 = -1;
    wk->menu_After[3] = v51;
    v52 = menu_drawOld[0] - 5;
    if (v52 < 0)
      v52 = -1;
    wk->menu_Before[4] = v52;
    v53 = menu_drawOld[11] + 5;
    if (v53 >= wk->menu_num)
      v53 = -1;
    wk->menu_After[4] = v53;
    v54 = menu_drawOld[0] - 6;
    if (v54 < 0)
      v54 = -1;
    wk->menu_Before[5] = v54;
    v55 = menu_drawOld[11] + 6;
    if (v55 >= wk->menu_num)
      v55 = -1;
    wk->menu_After[5] = v55;
    v56 = menu_drawOld[0] - 7;
    if (v56 < 0)
      v56 = -1;
    wk->menu_Before[6] = v56;
    v57 = menu_drawOld[11] + 7;
    if (v57 >= wk->menu_num)
      v57 = -1;
    wk->menu_After[6] = v57;
    v58 = menu_drawOld[0] - 8;
    if (v58 < 0)
      v58 = -1;
    wk->menu_Before[7] = v58;
    v59 = menu_drawOld[11] + 8;
    if (v59 >= wk->menu_num)
      v59 = -1;
    wk->menu_After[7] = v59;
    v60 = menu_drawOld[0] - 9;
    if (v60 < 0)
      v60 = -1;
    wk->menu_Before[8] = v60;
    v61 = menu_drawOld[11] + 9;
    if (v61 >= wk->menu_num)
      v61 = -1;
    wk->menu_After[8] = v61;
    v62 = menu_drawOld[0] - 10;
    if (v62 < 0)
      v62 = -1;
    wk->menu_Before[9] = v62;
    v63 = menu_drawOld[11] + 10;
    if (v63 >= wk->menu_num)
      v63 = -1;
    wk->menu_After[9] = v63;
    v64 = menu_drawOld[0] - 11;
    if (v64 < 0)
      v64 = -1;
    wk->menu_Before[10] = v64;
    v65 = menu_drawOld[11] + 11;
    if (v65 >= wk->menu_num)
      v65 = -1;
    wk->menu_After[10] = v65;
    v66 = menu_drawOld[0] - 12;
    if (v66 < 0)
      v66 = -1;
    v45[11] = v66;
    v67 = menu_drawOld[11] + 12;
    if (v67 >= wk->menu_num)
      v67 = -1;
    wk->menu_After[11] = v67;
    selMenuSetScrollBar(UI, wk->menu_num);
    selMenuScrollBarMove(UI, wk->menu_num, wk->top);
  }
}

// 0x221c290
static void MenuCursorCtrlSub(tips_tipsData_t *wk) {
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
  else if (CHECK_REP(43527, 1))
  {
    CursorRight(wk);
  }
}

// 0x221e200
static void CursorUp(tips_tipsData_t *wk) {
  s32 cursor;
  s32 v5;
  s32 top;
  s32 child_move;
  u32 v8;
  void *UI_local;
  s64 v10;
  s64 i;
  void *v12;
  s32 *parentID;
  s32 v15;
  s32 *id_save;
  char *v17;
  s32 *v18;
  s32 v19;
  s32 v20;
  int32x4_t v21;
  s32 *menu_draw;

  cursor = wk->cursor;
  if (cursor)
  {
    v5 = cursor - 1;
    top = wk->top;
    if (cursor - 1 < 0)
    {
      v5 = 0;
      child_move = wk->child_move;
      if (wk->move_flag)
      {
LABEL_8:
        wk->move_flag = 0;
        goto LABEL_13;
      }
    }
    else
    {
      if (v5 < top)
      {
        --top;
        TipsMenuCorsorPosCtrl(UI, 1, 0);
      }
      child_move = wk->child_move;
      if (wk->move_flag)
        goto LABEL_8;
    }
    if ((u32)(child_move + 1) <= 1)
      wk->child_move = 0;
LABEL_13:
    v8 = v5 - child_move;
    UI_local = UI;
    v10 = -(s64)v8;
    for (i = 4; i != 132; ++i)
    {
      v12 = *((void *)&UI_local->MenuObjList->obj.klass + i);
      if (op_Equality(v12, 0, 0))
        break;
      SetActive(*(void *)(*((u64 *)&UI_local->MenuObjList->obj.klass + i) + 48), v10 + i == 4, 0);
    }
    parentID = wk->parentID;
    wk->cursor_old = v5;
    if (parentID[0] == v5)
    {
      v15 = 0;
    }
    else
    {
      id_save = wk->id_save;
      wk->cursor_parent = -1;
      v17 = (char *)id_save + 4 * v5;
      v19 = *((u32 *)v17 + 8);
      v18 = (v17 + 32);
      wk->cursor_ID = v19;
      if (parentID[1] != v5)
      {
        wk->cursor_parent = -1;
        v20 = *v18;
        goto LABEL_26;
      }
      v15 = 1;
    }
    wk->cursor_parent = v15;
    v20 = -1;
    wk->parentCursor_save = v15;
LABEL_26:
    v21 = vdupq_n_s32(top);
    wk->cursor_ID = v20;
    menu_draw = wk->menu_draw;
    menu_draw[0] = top;
    *(int32x4_t *)&menu_draw[1] = vaddq_s32(v21, (int32x4_t)xmmword_3D07320);
    *(int32x4_t *)&menu_draw[5] = vaddq_s32(v21, (int32x4_t)xmmword_3D01E30);
    menu_draw[11] = top + 11;
    *(int32x2_t *)&menu_draw[9] = vadd_s32((int32x2_t)v21.n128_u64[0], (int32x2_t)0xA00000009LL);
    DrawMenuBeforeAfterSave(wk);
    selMenuScrollBarMove(UI, wk->menu_num, top);
    wk->change_flag = 0;
    wk->textChangeStep = 0;
    DeleteInsertImages(UI);
    wk->cursor = v5;
    wk->top = top;
    SE(3);
  }
}

// 0x221e4a0
static void CursorDown(tips_tipsData_t *wk) {
  s32 cursor;
  s32 v5;
  s32 v6;
  s32 top;
  s32 child_move;
  u32 v9;
  void *UI_local;
  s64 v11;
  s64 i;
  void *v13;
  s32 *parentID;
  s32 v16;
  s32 *id_save;
  char *v18;
  s32 *v19;
  s32 v20;
  s32 v21;
  int32x4_t v22;
  s32 *menu_draw;

  cursor = wk->cursor;
  v5 = wk->menu_num - 1;
  if (cursor != v5)
  {
    v6 = cursor + 1;
    top = wk->top;
    if (cursor + 1 <= v5)
    {
      if (v6 - top >= 12)
      {
        ++top;
        TipsMenuCorsorPosCtrl(UI, 1, 1);
      }
    }
    else
    {
      v6 = wk->menu_num - 1;
    }
    child_move = wk->child_move;
    if (wk->move_flag)
      wk->move_flag = 0;
    v9 = v6 - child_move;
    UI_local = UI;
    v11 = -(s64)v9;
    for (i = 4; i != 132; ++i)
    {
      v13 = *((void *)&UI_local->MenuObjList->obj.klass + i);
      if (op_Equality(v13, 0, 0))
        break;
      SetActive(*(void *)(*((u64 *)&UI_local->MenuObjList->obj.klass + i) + 48), v11 + i == 4, 0);
    }
    parentID = wk->parentID;
    wk->cursor_old = v6;
    if (parentID[0] == v6)
    {
      v16 = 0;
    }
    else
    {
      id_save = wk->id_save;
      wk->cursor_parent = -1;
      v18 = (char *)id_save + 4 * v6;
      v20 = *((u32 *)v18 + 8);
      v19 = (v18 + 32);
      wk->cursor_ID = v20;
      if (parentID[1] != v6)
      {
        wk->cursor_parent = -1;
        v21 = *v19;
        goto LABEL_23;
      }
      v16 = 1;
    }
    wk->cursor_parent = v16;
    v21 = -1;
    wk->parentCursor_save = v16;
LABEL_23:
    v22 = vdupq_n_s32(top);
    wk->cursor_ID = v21;
    menu_draw = wk->menu_draw;
    menu_draw[0] = top;
    *(int32x4_t *)&menu_draw[1] = vaddq_s32(v22, (int32x4_t)xmmword_3D07320);
    *(int32x4_t *)&menu_draw[5] = vaddq_s32(v22, (int32x4_t)xmmword_3D01E30);
    menu_draw[11] = top + 11;
    *(int32x2_t *)&menu_draw[9] = vadd_s32((int32x2_t)v22.n128_u64[0], (int32x2_t)0xA00000009LL);
    DrawMenuBeforeAfterSave(wk);
    selMenuScrollBarMove(UI, wk->menu_num, top);
    wk->change_flag = 0;
    wk->textChangeStep = 0;
    DeleteInsertImages(UI);
    wk->cursor = v6;
    wk->top = top;
    SE(3);
  }
}

// 0x221e730
static void CursorLeft(tips_tipsData_t *wk) {
  s32 top;
  s32 menu_num;
  s32 cursor;
  s32 *v6;
  s64 v8;
  s32 v9;
  s32 v10;
  bool v11;
  s64 v12;
  s32 v13;
  s32 v14;
  s64 v15;
  s64 v17;
  s32 v18;
  s32 *v19;
  s64 v21;
  s32 *v22;
  s32 v23;
  s64 v24;
  s32 v25;
  s32 child_move;
  u32 v27;
  void *UI_local;
  s64 v29;
  s64 i;
  void *v31;
  s64 v35;
  s32 *m_Items;
  s32 *id_save;
  int32x4_t v39;
  s32 *menu_draw;

  top = wk->top;
  menu_num = wk->menu_num;
  cursor = wk->cursor;
  v6 = NewSpecific(s32, 0xCu);
  if (cursor && menu_num >= 13)
  {
    v8 = v6;
    v9 = cursor - 12;
    v10 = top - 12;
    v11 = v9 < 0 || v10 <= 0;
    v12 = 0;
    v13 = v10 & ~(v10 >> 31) & ~(v9 >> 31);
    v14 = !v11;
    v15 = &v6[0];
    while (v12 < MENU_DRAW_MAX)
    {
      *(u32 *)(v15 + 4 * v12) = v13 + v12;
      ++v12;
    }
    v17 = 0;
    v18 = 0;
    v19 = (v8 + 32);
    while (1)
    {
      if (v17 >= MENU_DRAW_MAX)
        break;
      v21 = (u32)MENU_DRAW_MAX & ~((s32)MENU_DRAW_MAX >> 31);
      v22 = v19;
      while (v21)
      {
        --v21;
        v23 = *v22++;
        if (wk->menu_draw[v17] == v23)
          goto LABEL_18;
      }
      goto LABEL_9000;
      while (1)
      {
        if (v24 >= MENU_DRAW_MAX)
          break;
        v25 = v19[v24++];
        if (wk->menu_draw[v17] == v25)
        {
LABEL_18:
          ++v18;
          break;
        }
      }
LABEL_9000:
      ++v17;
    }
    if (!v14)
      v9 = 0;
    LODWORD(MENU_DRAW_MAX) = MENU_DRAW_MAX;
    TipsMenuCorsorPosCtrl(UI, MENU_DRAW_MAX - v18, 0);
    child_move = wk->child_move;
    if (wk->move_flag)
      wk->move_flag = 0;
    v27 = v9 - child_move;
    UI_local = UI;
    v29 = -(s64)v27;
    for (i = 4; i != 132; ++i)
    {
      v31 = *((void *)&UI_local->MenuObjList->obj.klass + i);
      if (op_Equality(v31, 0, 0))
        break;
      SetActive(*(void *)(*((u64 *)&UI_local->MenuObjList->obj.klass + i) + 48), v29 + i == 4, 0);
    }
    wk->cursor_old = v9;
    MENU_PARENT_MAX = (u32)MENU_PARENT_MAX;
    if ((s32)MENU_PARENT_MAX >= 1)
    {
      v35 = 0;
      m_Items = wk->parentID;
      while (m_Items[v35] != v9)
      {
        id_save = wk->id_save;
        wk->cursor_parent = -1;
        ++v35;
        wk->cursor_ID = id_save[v9];
        if (MENU_PARENT_MAX == v35)
          goto LABEL_60;
      }
      wk->cursor_parent = v35;
      wk->cursor_ID = -1;
      wk->parentCursor_save = v35;
    }
LABEL_60:
    v39 = vdupq_n_s32(v13);
    menu_draw = wk->menu_draw;
    menu_draw[0] = v13;
    *(int32x4_t *)&menu_draw[1] = vaddq_s32(v39, (int32x4_t)xmmword_3D07320);
    menu_draw[11] = v13 + 11;
    *(int32x4_t *)&menu_draw[5] = vaddq_s32(v39, (int32x4_t)xmmword_3D01E30);
    *(int32x2_t *)&menu_draw[9] = vadd_s32(vdup_n_s32(v13), (int32x2_t)0xA00000009LL);
    DrawMenuBeforeAfterSave(wk);
    selMenuScrollBarMove(UI, wk->menu_num, v13);
    wk->change_flag = 0;
    wk->textChangeStep = 0;
    DeleteInsertImages(UI);
    wk->cursor = v9;
    wk->top = v13;
    SE(3);
  }
}

// 0x221eb80
static void CursorRight(tips_tipsData_t *wk) {
  s32 top;
  s32 menu_num;
  s32 cursor;
  s32 *v6;
  s32 v8;
  s32 v9;
  s64 v10;
  s32 v11;
  u32 v12;
  s64 v13;
  s64 v15;
  s32 v16;
  s32 *v17;
  s64 v20;
  s32 *v21;
  s32 v22;
  s64 v23;
  s32 v24;
  s32 child_move;
  u32 v26;
  void *UI_local;
  s64 v28;
  s64 i;
  void *v30;
  s32 *parentID;
  s32 v33;
  s32 *id_save;
  char *v35;
  s32 *v36;
  s32 v37;
  s32 v38;
  int32x4_t v39;
  s32 *menu_draw;

  top = wk->top;
  menu_num = wk->menu_num;
  cursor = wk->cursor;
  v6 = NewSpecific(s32, 0xCu);
  if (menu_num >= 13)
  {
    v8 = menu_num - 1;
    if (cursor != menu_num - 1)
    {
      v9 = top + 12;
      v10 = v6;
      if (top + 12 >= menu_num)
      {
        v12 = menu_num - 12;
      }
      else
      {
        v11 = menu_num - 12;
        if (v9 >= menu_num - 12)
          v12 = menu_num - 12;
        else
          v12 = top + 12;
        if (v9 < v11)
          v8 = cursor + 12;
      }
      v13 = 0;
      while (v13 < MENU_DRAW_MAX)
      {
        *(u32 *)(v10 + 32 + 4 * v13) = v12 + v13;
        ++v13;
      }
      v15 = 0;
      v16 = 0;
      v17 = (v10 + 32);
      while (1)
      {
        if (v15 >= MENU_DRAW_MAX)
          break;
        v20 = (u32)MENU_DRAW_MAX & ~((s32)MENU_DRAW_MAX >> 31);
        v21 = v17;
        while (v20)
        {
          --v20;
          v22 = *v21++;
          if (wk->menu_draw[v15] == v22)
            goto LABEL_20;
        }
        goto LABEL_9000;
        while (1)
        {
          if (v23 >= MENU_DRAW_MAX)
            break;
          v24 = v17[v23++];
          if (wk->menu_draw[v15] == v24)
          {
LABEL_20:
            ++v16;
            break;
          }
        }
LABEL_9000:
        ++v15;
      }
      LODWORD(MENU_DRAW_MAX) = MENU_DRAW_MAX;
      TipsMenuCorsorPosCtrl(UI, MENU_DRAW_MAX - v16, 1);
      child_move = wk->child_move;
      if (wk->move_flag)
        wk->move_flag = 0;
      v26 = v8 - child_move;
      UI_local = UI;
      v28 = -(s64)v26;
      for (i = 4; i != 132; ++i)
      {
        v30 = *((void *)&UI_local->MenuObjList->obj.klass + i);
        if (op_Equality(v30, 0, 0))
          break;
        SetActive(*(void *)(*((u64 *)&UI_local->MenuObjList->obj.klass + i) + 48), v28 + i == 4, 0);
      }
      parentID = wk->parentID;
      wk->cursor_old = v8;
      if (parentID[0] == v8)
      {
        v33 = 0;
      }
      else
      {
        id_save = wk->id_save;
        wk->cursor_parent = -1;
        v35 = (char *)id_save + 4 * v8;
        v37 = *((u32 *)v35 + 8);
        v36 = (v35 + 32);
        wk->cursor_ID = v37;
        if (parentID[1] != v8)
        {
          wk->cursor_parent = -1;
          v38 = *v36;
          goto LABEL_53;
        }
        v33 = 1;
      }
      v38 = -1;
      wk->cursor_parent = v33;
      wk->parentCursor_save = v33;
LABEL_53:
      v39 = vdupq_n_s32(v12);
      wk->cursor_ID = v38;
      menu_draw = wk->menu_draw;
      menu_draw[0] = v12;
      *(int32x4_t *)&menu_draw[1] = vaddq_s32(v39, (int32x4_t)xmmword_3D07320);
      menu_draw[11] = v12 + 11;
      *(int32x4_t *)&menu_draw[5] = vaddq_s32(v39, (int32x4_t)xmmword_3D01E30);
      *(int32x2_t *)&menu_draw[9] = vadd_s32(vdup_n_s32(v12), (int32x2_t)0xA00000009LL);
      DrawMenuBeforeAfterSave(wk);
      selMenuScrollBarMove(UI, wk->menu_num, v12);
      wk->change_flag = 0;
      wk->textChangeStep = 0;
      DeleteInsertImages(UI);
      wk->cursor = v8;
      wk->top = v12;
      SE(3);
    }
  }
}

// 0x221f1b0
static void DrawMenuBeforeAfterSave(tips_tipsData_t *wk) {
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

// 0x221ba60
static void TextChangeCtrl(tips_tipsData_t *data, s32 _num) {
  char *v6;
  s64 v8;
  s32 v11;
  void *v13;
  void *v15;
  void *v16;
  void *v18;
  void *Instance;
  bool activeSelf;
  char **v22;
  void *v23;
  void *PANEL02_BarRect;
  char *title;
  char *LocalizeText;
  char *v28;
  char *text_all;
  char *v33;
  char *v34;
  char *v35;
  s64 v36;
  s64 i;
  char *v39;
  char *v42;
  char *v43;
  char *v44;
  char *v46;
  sdfVector2_t v47;
  sdfVector2_t v48;

  v6 = "";
  if (num)
  {
    if (data->id_save[data->cursor] != -1)
    {
      switch (data->textChangeStep)
      {
        case 0:
          if (!get_activeSelf(UI->PANEL02->gameobject, 0))
            SetActive(UI->PANEL02->gameobject, 1, 0);
          set_alpha(UI->PANEL02->group, 0.0, 0);
          v8 = 0;
          while (1)
          {
            do
            {
              if (v8 >= SLODWORD(TIPS_ID_TABLE_ALL->max_length))
                goto LABEL_73;
              v11 = data->id_save[data->cursor];
              if (v11 == TIPS_ID_TABLE_ALL[v8]->ID)
              {
LABEL_73:
                title = TIPS_ID_TABLE_ALL[v8]->title;
                LocalizeText = GetLocalizeText(title, 1);
                v28 = tipsChangeTextPLTF(LocalizeText);
                PANEL_TitleTextSet(UI, v28);
                text_all = TIPS_ID_TABLE_ALL[v8]->text_all;
                if (SLODWORD(text_all->max_length) >= 1)
                {
                  text_all = TIPS_ID_TABLE_ALL[v8]->text_all;
                  if (op_Inequality(text_all[0], "", 0))
                  {
                    v33 = TIPS_ID_TABLE_ALL[v8]->text_all[0];
                    v34 = GetLocalizeText(v33, 1);
                    v35 = Concat_54766928(v6, v34, 0);
                    v36 = v8;
                    PANEL02_SetMessage(UI, v35, TIPS_ID_TABLE_ALL[v36]->text_all[0]);
                    for (i = 5; ; ++i)
                    {
                      v42 = TIPS_ID_TABLE_ALL[v36]->text_all;
                      if (i - 4 >= SLODWORD(v42->max_length))
                        break;
                      v42 = TIPS_ID_TABLE_ALL[v36]->text_all;
                      if (!op_Inequality(*((char **)&v42->obj.klass + i), "", 0))
                        break;
                      v43 = Concat_54766928(v35, "\n", 0);
                      v44 = Concat_54766928(v43, "\n", 0);
                      v46 = *((char **)&TIPS_ID_TABLE_ALL[v36]->text_all->obj.klass + i);
                      v39 = GetLocalizeText(v46, 1);
                      v35 = Concat_54766928(v44, v39, 0);
                      PANEL02_SetMessage(UI, v35, *((char **)&TIPS_ID_TABLE_ALL[v36]->text_all->obj.klass + i));
                    }
                  }
                }
                p2sdLoadSMGFile(4259840);
                goto LABEL_70;
              }
              ++v8;
            }
          }
        case 1:
          v15 = UI;
          v16 = *(void *)&v15->PANEL02->message->messageText->TMProUGUI->m_fontColorGradient.bottomRight.a;
          if (op_Equality(v16, 0, 0))
            set_spriteAsset(v15->PANEL02->message->messageText->TMProUGUI, v15->tmp_SpriteAsset, 0);
          TextTagChange_next(UI, UI->PANEL02->message->messageText->TMProUGUI);
          goto LABEL_70;
        case 2:
          v18 = UI;
          TagImageInsertMain(v18, v18->PANEL02->message->messageText->TMProUGUI);
          TagRawImageInsertMain(v18, v18->PANEL02->message->messageText->TMProUGUI);
          goto LABEL_70;
        case 3:
          Instance = get_Instance(0);
          ItfButtonGuideActive(Instance, 1, 0);
          activeSelf = get_activeSelf(UI->PANEL02->message->scrollbar, 0);
          v22 = &"DBOOK03";
          if (!activeSelf)
            v22 = &"DBOOK02";
          ButtonGuideDispSet(*v22, 0, 90);
          ButtonLineHelpDispSet(0);
          v47.x = 0.0;
          v47.y = 0.0;
          v23 = UI;
          PANEL02_BarRect = v23->PANEL02_BarRect;
          v23->PANEL02->topLineNum = 0;
          set_anchoredPosition(PANEL02_BarRect, v47, 0);
          v48.x = 0.0;
          v48.y = 0.0;
          set_anchoredPosition(v23->PANEL02->message->messageText->rect, v48, 0);
          set_value(v23->PANEL02->message->scrollbarVertical, 1.0, 0);
          set_alpha(UI->PANEL02->group, 1.0, 0);
LABEL_70:
          ++data->textChangeStep;
          break;
        case 5:
          data->textChangeStep = 0;
          break;
        default:
          return;
      }
    }
  }
  else
  {
    PANEL02_SetMessage(UI, "", 0);
    PANEL_TitleTextSet(UI, "");
    v13 = get_Instance(0);
    ItfButtonGuideActive(v13, 1, 0);
    ButtonGuideDispSet("DBOOK01", 0, 90);
    ButtonLineHelpDispSet(1);
    ButtonLineHelpTextSet(strMenuHelpText[data->cursor_parent], 0, 1, 0xA09DC380, 1);
  }
}

// 0x221a930
bool tipsGuideOffCheck(void) {
  bool v1;
  s32 v2;

  v1 = cmpProcessCheck();
  v2 = ProcessCheck();
  return (gohProcessCheck() | v2) == 0 && !v1;
}

// 0x221a810
static s32 RightStickCtrl(void) {
  if (CHECK_PRESS(41236, 1))
    return 0;
  if (CHECK_PRESS(41237, 1))
    return 1;
  return -1;
}

// 0x2219e40
char *tipsChangeTextPLTF(char *text) {
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
