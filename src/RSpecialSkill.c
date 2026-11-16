#include "types.h"
#include "RSkillTab.h"
#include "battleskill.h"
#include "cmpmain.h"
#include "cmpmodel.h"
#include "cmpstatus.h"
#include "dds3_pad.h"
#include "dds3kernelcore.h"
#include "dds3kerneldraw.h"
#include "kernel.h"
#include "localize.h"
#include "rspecialskill.h"
#include "rspecialskillstatus.h"
#include "sdfmem.h"
#include "swordskill.h"

typedef enum {
    R_SSKILL_FLAG_NONE = 0,
    R_SSKILL_FLAG_SCENE_LOAD_NOW = 1,
    R_SSKILL_FLAG_SCENE_LOAD_END = 2,
} R_SSKILL_FLAG;

typedef struct SPECIAL_SKILL_WORK SPECIAL_SKILL_WORK;
typedef struct SSkillData_t SSkillData_t;
typedef struct dds3ProcessID_t dds3ProcessID_t;

static dds3ProcessID_t *GlobalPID;
char *skill_scene_name;
static char *rs_skill_asset_name;
static dds3ProcessID_t *g_mainPID;

static dds3ProcessFunc_t LoadProcess(dds3ProcessID_t *PID);
static dds3ProcessFunc_t Load1stProcess(dds3ProcessID_t *PID);
static SSkillData_t *Init(void);
static void Destroy(dds3ProcessID_t *PID);
static void SakuraEffectDraw(void);
static dds3ProcessFunc_t Process(dds3ProcessID_t *PID);
static dds3ProcessFunc_t DrawProcess(dds3ProcessID_t *PID);
void NormalUpdate(void);
void SelectUpdate(void);

// 0x1e12030
void LoadUIScene(SSkillData_t *pData) {
  char *v5;
  void *SceneAsync;

  if ((pData->flag & 3) != 0)
    return;
  v5 = "UI_RSpecialSkill";
  skill_scene_name = "UI_RSpecialSkill";
  Load(Dependent, rs_skill_asset_name, rs_skill_asset_name);
  LoadSyncAll(_Ctrl_k__BackingField, 0);
  SceneAsync = LoadSceneAsync(_Ctrl_k__BackingField, skill_scene_name, 0);
  scene_asyncLoad = SceneAsync;
  pData->flag |= 1u;
  return;
}

// 0x1e12220
s32 ChackScene(SSkillData_t *pData) {
  if (!scene_asyncLoad)
    goto LABEL_9;
  goto LABEL_7;
  if (!scene_asyncLoad)
  {
LABEL_9:
    pData->flag |= 2u;
    return 1;
  }
LABEL_7:
  if (get_isDone(scene_asyncLoad, 0))
    goto LABEL_9;
  return 0;
}

// 0x1e12310
void FreeScene(SSkillData_t *pData) {
  pData->flag &= 0xFFFFFFFC;
}

// 0x1e12330
static dds3ProcessFunc_t LoadProcess(dds3ProcessID_t *PID) {
  SSkillData_t *ProcessData;
  s32 tab;
  _BOOL4 goh;
  dds3ProcessFunc_t v13;
  SSkillData_t *v14;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  v14 = ProcessData;
  LoadUIScene(v14);
  if (scene_asyncLoad)
  {
    if (!get_isDone(scene_asyncLoad, 0))
      return 0;
  }
  tab = ProcessData->tab;
  ProcessData->flag |= 2u;
  goh = ProcessData->goh;
  SkillProcessStart(tab, goh);
  v13 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
  _ctor(v13, 0, Method_Project_RSpecialSkill_Load1stProcess__, 0);
  return v13;
}

// 0x1e12a00
static dds3ProcessFunc_t Load1stProcess(dds3ProcessID_t *PID) {
  return 0;
}

// 0x1e12a10
static SSkillData_t *Init(void) {
  SSkillData_t *v1;
  SSkillData_t *v2;

  v1 = Allocate(SSkillData_t);
  v1->tab = -1;
  v2 = v1;
  _ctor(v1, 0);
  if (ProcessCheck())
    return v2;
  cmpLoadEffect();
  return v2;
}

// 0x1e12b10
static void Destroy(dds3ProcessID_t *PID) {
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
  LODWORD(ProcessData[1].klass) &= 0xFFFFFFFC;
}

// 0x1e12c20
dds3ProcessID_t *ProcessStart(RSkillTab tab, bool goh) {
  bool v5;
  dds3ProcessID_t *v6;
  SSkillData_t *v8;
  dds3ProcessFunc_t v9;
  shutdownfuncDelegate v10;
  dds3ProcessID_t *started;

  v5 = goh;
  v6 = Allocate(dds3ProcessID_t);
  _ctor(v6, 0);
  v8 = Init();
  v8->tab = tab;
  v8->goh = v5;
  v9 = Allocate(dds3ProcessFunc_t);
  _ctor(v9, 0, Method_Project_RSpecialSkill_LoadProcess__, 0);
  v10 = Allocate(shutdownfuncDelegate);
  _ctor(v10, 0, Method_Project_RSpecialSkill_Destroy__, 0);
  started = dds3StartProcess("RSpecialSkill_Calc", 1023, 0, 0, v9, v10, v8);
  GlobalPID = started;
  return started;
}

// 0x1e12de0
void ProcessEnd(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  bool v3;
  s64 naturalAligment;
  s64 v7;
  UnityEngine_SceneManagement_Scene_o v11;
  UnityEngine_SceneManagement_Scene_o scene;
  dds3ProcessID_t *id;

  id = PID;
  scene.m_Handle = 0;
  ProcessData = dds3GetProcessData(id);
  BackObjSetAnim(instance, 1, 0);
  v3 = ProcessCheck();
  if (v3)
  {
    if (ProcessData)
    {
      if (ProcessData->klass->_2.naturalAligment < (u32)naturalAligment || ProcessData->klass->_2.typeHierarchy[naturalAligment - 1] != SPECIAL_SKILL_WORK)
      {
        goto LABEL_41;
      }
    }
    goto LABEL_20;
  }
  if (ProcessData)
  {
    if (ProcessData->klass->_2.naturalAligment < (u32)v7 || ProcessData->klass->_2.typeHierarchy[v7 - 1] != SPECIAL_SKILL_WORK)
    {
LABEL_41:
    }
  }
  cmpDeleteEffect();
  End();
LABEL_20:
  Unload(Dependent, rs_skill_asset_name, 0);
  ManageRelease(instance, 0);
  dds3KillProcessName("RSpecialSkill_Calc", 0);
  dds3KillProcessName("special_skill_draw", 0);
  dds3KillProcessName("skill_status_main", 0);
  scene.m_Handle = GetSceneByName(skill_scene_name, 0).m_Handle;
  if (IsValid((UnityEngine_SceneManagement_Scene_o)&scene, 0))
  {
    v11.m_Handle = scene.m_Handle;
    UnloadSceneAsync_61083440(scene, 0);
    skill_scene_name = 0;
    scene_asyncLoad = 0;
    goto LABEL_32;
  }
LABEL_32:
  ProcessData[1].klass = 0;
  GlobalPID = 0;
  g_mainPID = 0;
  sdfMemResourcesRelease();
}

// 0x1e13210
s32 ProcessCheck(void) {
  return dds3SearchProcessName("RSpecialSkill_Calc") != 0;
}

// 0x1e13290
void Init_2(SPECIAL_SKILL_WORK *wk) {
  bool v4;
  char *LocalizeText;

  wk->tab = -1;
  *(u64 *)&wk->count = 0x100000000LL;
  v4 = cmpProcessCheck();
  wk->step = 1;
  if (v4)
    return;
  LocalizeText = GetLocalizeText("CMP_MENU_L0047", 1);
  SetSubTitle(instance, LocalizeText, 0);
}

// 0x1e12590
void SkillProcessStart(s32 tab, bool goh) {
  SPECIAL_SKILL_WORK *v4;
  dds3ProcessID_t *v5;
  dds3ProcessFunc_t v8;
  shutdownfuncDelegate v9;
  dds3ProcessID_t *started;
  dds3ProcessFunc_t v12;
  dds3ProcessID_t *v13;
  s32 v18;
  void *Instance;

  v4 = Allocate(SPECIAL_SKILL_WORK);
  v5 = Allocate(dds3ProcessID_t);
  _ctor(v5, 0);
  v4->drawPID = v5;
  _ctor(v4, 0);
  Init_2(v4);
  RSpecialSkillProcessStart(goh);
  v8 = Allocate(dds3ProcessFunc_t);
  _ctor(v8, 0, Method_Project_RSpecialSkill_Process__, 0);
  v9 = Allocate(shutdownfuncDelegate);
  _ctor(v9, 0, Method_Project_RSpecialSkill_ProcessEnd__, 0);
  started = dds3StartProcess("special_skill_main", 1023, 0, 1, v8, v9, v4);
  g_mainPID = started;
  v12 = Allocate(dds3ProcessFunc_t);
  _ctor(v12, 0, Method_Project_RSpecialSkill_DrawProcess__, 0);
  v13 = dds3StartProcess("special_skill_draw", 11029, 0, 0, v12, 0, v4);
  v4->drawPID = v13;
  Init(instance, 0);
  if (tab == -1)
  {
    TabChange(1, 1);
    v18 = v4->tab;
  }
  else
  {
    TabChange(tab + 1, 1, 1);
    v18 = v4->tab;
  }
  RSpecialSkillLosdListSide(v18);
  BackObjSetAnim(instance, 1, 0);
  SetAnim(instance, 1, 0);
  ChangePanel(instance, v4->tab, 0);
  if (cmpProcessCheck())
  {
    goto LABEL_23;
  }
  Instance = get_Instance(0);
  ItfButtonGuideSet(Instance, 0, 0);
LABEL_23:
  RSpecialSkillButtonGuideDraw();
}

// 0x1e13d10
static void SakuraEffectDraw(void) {
  if (ProcessCheck())
    return;
  cmpEffectSetRGBA(0x80808080);
  cmpDrawEffect();
}

// 0x1e13dd0
static dds3ProcessFunc_t Process(dds3ProcessID_t *PID) {
  SPECIAL_SKILL_WORK *ProcessData;
  s32 count;
  void *v10;
  s32 v11;
  void *v12;
  s32 v13;
  void *v14;
  dds3ProcessFunc_t v16;
  void *Instance;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
  switch (ProcessData->step)
  {
    case 1:
      count = ProcessData->count;
      if (!count)
      {
        dds3FadeIn(0, 0, 0, 0xAu);
        goto LABEL_50;
      }
      if (count < 10)
        goto LABEL_51;
      ProcessData->count = 0;
      ProcessData->step = 3;
      return 0;
    case 2:
      if (!cmpProcessCheck())
      {
        Instance = get_Instance(0);
        ItfSortMenuActive(Instance, 0, 0);
        RSpecialSkillResetCoolTime();
        SetAnim(instance, 2, 0);
        DeleteSubTitle(instance, 0);
        v11 = ProcessData->count;
        if (v11)
          goto LABEL_21;
        goto LABEL_47;
      }
      RSpecialSkillSaveRSkillCsr();
      RSpecialSkillSaveRSkillTab();
      RSpecialSkillSaveRSkillListSide(ProcessData->tab);
      v10 = get_Instance(0);
      ItfSortMenuActive(v10, 0, 0);
      SetAnim(instance, 2, 0);
      v11 = ProcessData->count;
      if (v11)
      {
LABEL_21:
        if (v11 >= 10)
          ProcessData->step = 4;
        goto LABEL_50;
      }
LABEL_47:
      dds3FadeOut(0, 0, 0, 0xAu);
LABEL_50:
      count = ProcessData->count;
LABEL_51:
      ProcessData->count = count + 1;
      return 0;
    case 3:
      if (ProcessData->state == 1 && CHECK_TRIG(4097, 1))
      {
        v12 = get_Instance(0);
        if (!GetItfSortSysActive(v12, 0))
        {
          if (cmpProcessCheck())
            v13 = 1;
          else
            v13 = 18;
          SE(v13);
          ProcessData->step = 2;
        }
      }
      v14 = get_Instance(0);
      if (GetItfSortSysActive(v14, 0))
        return 0;
      MainInput();
      TabUpdate();
      return 0;
    case 4:
      v16 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
      _ctor(v16, 0, Method_Project_Kernel_DDS3_PROC_END__, 0);
      return v16;
    default:
      return 0;
  }
}

// 0x1e15060
static dds3ProcessFunc_t DrawProcess(dds3ProcessID_t *PID) {
  s32 *ProcessData;
  void *v6;
  s32 v11;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  SakuraEffectDraw();
  v6 = get_Instance(0);
  if (GetItfSortSysActive(v6, 0))
    return 0;
  v11 = ProcessData[9];
  if (v11 == 1)
  {
    Draw();
    goto LABEL_21;
  }
  if (!v11)
    Draw();
LABEL_21:
  TabCsrDraw(instance, ProcessData[9], 0);
  return 0;
}

// 0x1e14410
void TabUpdate(SPECIAL_SKILL_WORK *wk) {
  s32 tab;

  tab = wk->tab;
  if (tab == 1)
  {
    Update();
    return;
  }
  if (!tab)
  {
    State = GetState();
    if ((u32)State != 2)
    {
      if ((u32)State == 1)
        NormalUpdate();
      return;
    }
    SelectUpdate();
  }
}

// 0x1e15260
void TabDraw(SPECIAL_SKILL_WORK *wk) {
  s32 tab;

  tab = wk->tab;
  if (tab == 1)
  {
    Draw();
  }
  else if (!tab)
  {
    Draw();
  }
}

// 0x1e142a0
void MainInput(SPECIAL_SKILL_WORK *wk) {
  s32 v4;
  s32 state;

  if (CHECK_TRIG(4104, 1))
  {
    v4 = -1;
    goto LABEL_6;
  }
  if (!CHECK_TRIG(4107, 1))
  {
    goto LABEL_10;
  }
  v4 = 1;
LABEL_6:
  TabChange(v4, 0);
  RSpecialSkillSelectStateChaneg();
  state = wk->state;
  if (state == 2)
    goto LABEL_16;
  goto LABEL_11;
LABEL_10:
  RSpecialSkillSelectStateChaneg();
  state = wk->state;
  if (state == 2)
  {
LABEL_16:
    subCsrUpdate();
    return;
  }
LABEL_11:
  if (state == 1)
  {
    RSpecialSkillCsrUpdate();
  }
}

// 0x1e13660
void TabChange(s32 cnt, bool isInit, bool isSetTab) {
  Il2CppObject *ProcessData;
  Il2CppObject *v10;
  void *Work;
  s32 v15;
  _BOOL4 v16;
  s32 klass_high;
  s32 v19;
  s32 monitor_high;
  s64 v22;

  ProcessData = dds3GetProcessData(g_mainPID);
  v10 = ProcessData;
  Work = cmpProcessCheck();
  if (((u8)Work & 1) == 0 || !isInit || isSetTab)
  {
    v15 = HIDWORD(v10[2].klass) + cnt;
    v16 = v15 < 2;
    if ((v15 & 0x80000000) == 0)
      goto LABEL_25;
    goto LABEL_24;
  }
  Work = cmpProcessCheck();
  if (((u8)Work & 1) != 0)
    goto LABEL_16;
  klass_high = 0;
  if (!HIDWORD(v10[2].klass))
    return;
LABEL_34:
  if (isInit || isSetTab)
  {
LABEL_39:
    monitor_high = HIDWORD(v10[1].monitor);
    HIDWORD(v10[2].klass) = klass_high;
    if (monitor_high == 2)
    {
      ChangeState(1);
      v22 = *((u64 *)Work + 23);
      *(u64 *)(v22 + 32) = -1;
      *(u64 *)(v22 + 40) = -1;
      klass_high = HIDWORD(v10[2].klass);
    }
    if (klass_high)
      Init();
    else
      Init();
    return;
  }
  SE(9);
  v19 = HIDWORD(v10[2].klass);
  RSpecialSkillSaveRSkillListSide(v19);
  RSpecialSkillSelectRememberCsr();
  ResetTimeObj(instance, 0);
  goto LABEL_39;
LABEL_16:
  Work = cmpGetWork();
  v15 = *((u32 *)Work + 56);
  v16 = v15 < 2;
  if (v15 < 0)
LABEL_24:
    v15 = 1;
LABEL_25:
  if (v16)
    klass_high = v15;
  else
    klass_high = 0;
  if (HIDWORD(v10[2].klass) != klass_high)
    goto LABEL_34;
}

// 0x1e15f10
void ChangeState(RSKILL_STATE state) {
  Il2CppObject *ProcessData;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    return;
  HIDWORD(ProcessData[1].monitor) = state;
  RSpecialSkillButtonGuideDraw();
}

// 0x1e164d0
RSKILL_STATE GetState(void) {
  Il2CppObject *ProcessData;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    return (s32)ProcessData;
  LODWORD(ProcessData) = HIDWORD(ProcessData[1].monitor);
  return (s32)ProcessData;
}
