#include "types.h"
#include "cmpmodel.h"
#include "dds3kernelcore.h"
#include "dds3kerneldraw.h"
#include "evtviewer.h"
#include "fclmisc.h"
#include "kernel.h"
#include "sndat3.h"
#include "staffmain.h"

#define FRAME_RATE 60
#define STAFF_MAX 1024
#define STAFF_TAIME_TABLE 25

typedef struct StaffCredit_t StaffCredit_t;
typedef struct Staff_t Staff_t;
typedef struct Time_t Time_t;
typedef struct dds3ProcessID_t dds3ProcessID_t;
typedef struct staffData_t staffData_t;

static s32 endrolls_item_count;
char *staff_scene_name;
bool first;
static dds3ProcessID_t *g_mainPID;
Time_t *stafftime;
Staff_t *StaffData;
StaffCredit_t *StaffData2;

static dds3ProcessFunc_t FirstCalcProcess(dds3ProcessID_t *PID);
static dds3ProcessFunc_t FirstCalcProcess2(dds3ProcessID_t *PID);
static dds3ProcessFunc_t FirstDrawProcess(dds3ProcessID_t *PID);
static dds3ProcessFunc_t CalcProcess(dds3ProcessID_t *PID);
static dds3ProcessFunc_t DrawProcess(dds3ProcessID_t *PID);
static void DrawStaff(void);
static s32 At3Load(staffData_t *pData);
static s32 At3Play(staffData_t *pData);
static s32 At3Stop(staffData_t *pData);
static staffData_t *Init(void);
static void Destroy(dds3ProcessID_t *PID);
static void SakuraEffectDraw(void);
static void EndSkip(dds3ProcessID_t *PID);

// 0x21f86d0
void LoadStaffUI(staffData_t *pData) {
  char *v4;
  char *v7;
  void *SceneAsync;
  dds3ProcessID_t *PmvPID;

  v4 = "UI_staff";
  staff_scene_name = "UI_staff";
  v7 = "staff";
  Load(Dependent, v7, v7);
  LoadSyncAll(_Ctrl_k__BackingField, 0);
  SceneAsync = LoadSceneAsync(_Ctrl_k__BackingField, staff_scene_name, 0);
  scene_asyncLoad = SceneAsync;
  cmpLoadEffect();
  PmvPID = pData->PmvPID;
  first = 1;
  endrolls_item_count = 0;
  evtIgnoreFade(PmvPID);
}

// 0x21f8910
s32 CheckStaffUi(staffData_t *pData) {
  if (!scene_asyncLoad)
  {
LABEL_5:
    scene_asyncLoad = 0;
    return 1;
  }
  if (get_isDone(scene_asyncLoad, 0))
  {
    goto LABEL_5;
  }
  return 0;
}

// 0x21f8a10
void FreeStaffUi(staffData_t *pData) {
  staffData_t *v3;
  dds3ProcessID_t *PmvPID;
  staffData_t *v5;

  v3 = pData;
  PmvPID = pData->PmvPID;
  if (PmvPID)
  {
    evtEnd(PmvPID);
    v3 = pData;
  }
  v3->PmvPID = 0;
  v5 = pData;
  v5->drawPID = 0;
}

// 0x21f8aa0
void UnloadStaffUI(void) {
  UnityEngine_SceneManagement_Scene_o v5;

  if (IsNullOrEmpty(staff_scene_name, 0))
    return;
  v5.m_Handle = GetSceneByName(staff_scene_name, 0).m_Handle;
  UnloadSceneAsync_61083440(v5, 0);
  staff_scene_name = 0;
  return;
}

// 0x21f8bc0
static dds3ProcessFunc_t FirstCalcProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  dds3ProcessFunc_t v7;
  staffData_t *pData;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  pData = ProcessData;
  LoadStaffUI(pData);
  if ((BYTE1(ProcessData[1].klass) & 1) == 0)
  {
    sndBgmLoadId_XF(23);
    LODWORD(ProcessData[1].klass) |= 0x100u;
  }
  v7 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
  _ctor(v7, 0, Method_Project_StaffMain_FirstCalcProcess2__, 0);
  return v7;
}

// 0x21f8e40
static dds3ProcessFunc_t FirstCalcProcess2(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  dds3ProcessFunc_t v9;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  if (!CheckStaffUi(StaffMain))
    return 0;
  if ((BYTE1(ProcessData[1].klass) & 2) != 0)
    goto LABEL_26;
  if (sndBgmStatus_XF() == 2)
  {
    sndBgmFadeIn(0, 0);
    LODWORD(ProcessData[1].klass) |= 0x200u;
    goto LABEL_26;
  }
  return 0;
LABEL_26:
  v9 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
  _ctor(v9, 0, Method_Project_StaffMain_CalcProcess__, 0);
  return v9;
}

// 0x21f9130
static dds3ProcessFunc_t FirstDrawProcess(dds3ProcessID_t *PID) {
  dds3ProcessFunc_t v2;
  dds3ProcessID_t *id;

  id = PID;
  dds3GetProcessData(id);
  v2 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
  _ctor(v2, 0, Method_Project_StaffMain_DrawProcess__, 0);
  return v2;
}

// 0x21f91f0
static dds3ProcessFunc_t CalcProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  Time_t *monitor;
  dds3ProcessID_t *v7;
  dds3ProcessFunc_t v8;
  dds3ProcessFunc_t result;
  void *Instance;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  monitor = ProcessData[3].monitor;
  v7 = id;
  v8 = CutChange(monitor, v7);
  cmpEffectSetRGBA(0x80808080);
  cmpDrawEffect();
  result = 0;
  if (SLODWORD(ProcessData[5].klass) >= 691)
  {
    Instance = get_Instance(Project_staffUI);
    NewStaffScroll(Instance, (s32)ProcessData[4].monitor);
    return v8;
  }
  return result;
}

// 0x21f9ec0
static dds3ProcessFunc_t DrawProcess(dds3ProcessID_t *PID) {
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
  if (CheckStaffUi(StaffMain))
  {
    DrawStaff();
  }
  return 0;
}

// 0x21f9fe0
static void DrawStaff(void) {
  s32 dispControlFlg;
  void *Instance;
  void *logoImage;
  void *m_Sprite;
  void *v14;
  void *v15;
  void *v18;
  s32 v19;
  void *v20;
  void *v22;
  void *v25;
  f32 v26;
  f32 pos_y;
  char *moji;

  pos_y = 0.0;
  moji = "";
  while (1)
  {
    if (endrolls_item_count >= SLODWORD(StaffData2->max_length))
      return;
    dispControlFlg = StaffData2[endrolls_item_count]->dispControlFlg;
    if (dispControlFlg == 1)
    {
      Instance = get_Instance(StaffMain);
      logoImage = Instance->staffSet->logoImage;
      m_Sprite = logoImage[logoobj_cnt]->m_Sprite;
      if (!op_Equality(m_Sprite, 0, 0))
        return;
      v14 = instance;
      DrawLogoImage(v14, StaffData2[endrolls_item_count], &moji);
LABEL_5:
      goto LABEL_6;
    }
    v15 = instance;
    if (!CheckBlank(v15, StaffData2[endrolls_item_count]))
      return;
    pos_y = 0.0;
    if (StaffData2[endrolls_item_count]->caption)
    {
      v18 = instance;
      DrawText(v18, StaffData2[endrolls_item_count], 0, &pos_y);
      v19 = 1;
      goto LABEL_37;
    }
    v19 = 0;
LABEL_37:
    if (!!StaffData2[endrolls_item_count]->name1)
    {
      v20 = instance;
      v19 = 1;
      DrawText(v20, StaffData2[endrolls_item_count], 1, &pos_y);
    }
    if (StaffData2[endrolls_item_count]->name2)
      break;
    if (v19)
      goto LABEL_69;
    v22 = instance;
    init_positoin_y = init_positoin_y - v22->between_line;
    goto LABEL_5;
LABEL_6:
    ++endrolls_item_count;
  }
  v25 = instance;
  DrawText(v25, StaffData2[endrolls_item_count], 2, &pos_y);
LABEL_69:
  v26 = pos_y;
  goto LABEL_71;
LABEL_72:
  init_positoin_y = v26;
  goto LABEL_9004;
LABEL_71:
  goto LABEL_72;
LABEL_9004:
  ++endrolls_item_count;
}

// 0x21fa620
s32 GetStaffRollTableMax(void) {
  return StaffData2->max_length;
}

// 0x21fb030
void NewStaffDataLoad(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  il2cpp_array_size_t max_length;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  max_length = StaffData2->max_length;
  if (!ProcessData)
  LODWORD(ProcessData[4].monitor) = max_length;
}

// 0x21f93a0
dds3ProcessFunc_t CutChange(Time_t *pTime, dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  s32 *v9;
  dds3ProcessID_t *v10;
  Time_t *v13;
  s32 klass_high;
  void *Instance;
  dds3ProcessFunc_t v20;
  f32 v21;
  f32 v26;
  void *v29;
  u32 v32;
  void *v33;
  void *movie;
  u32 v36;
  void *v37;
  void *v40;
  Time_t *v44;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
  if (pTime->WaitTimer <= (f32)SLODWORD(ProcessData[5].klass))
  {
    v9 = (s32 *)&ProcessData[4].monitor + 1;
    if (SHIDWORD(ProcessData[4].monitor) <= 25)
    {
      switch (pTime->fade)
      {
        case 0:
          v10 = id;
          NewStaffDataLoad(v10);
          goto LABEL_59;
        case 2:
          dds3FadeIn(0, 0, 0, 0x3Cu);
          v13 = stafftime[*v9];
          ProcessData[3].monitor = v13;
          OnCut(instance, pTime->CutNomber + 1);
          goto LABEL_60;
        case 3:
          v9 = (s32 *)&ProcessData[5].klass + 1;
          klass_high = HIDWORD(ProcessData[5].klass);
          if (klass_high < 180)
            goto LABEL_61;
          Instance = get_Instance(Project_staffUI);
          ActiveOnOff(Instance, Instance->staffSet->CutFrame);
          *v9 = 0;
          pTime->fade = 1;
          v20 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
          _ctor(v20, 0, Method_Project_Kernel_DDS3_PROC_END__, 0);
          return v20;
        case 4:
          v21 = *((f32 *)&ProcessData[5].monitor + 1) + -0.016666668;
          if (v21 < 0.05)
            v21 = 0.0;
          *((f32 *)&ProcessData[5].monitor + 1) = v21;
          v21 = *((f32 *)&ProcessData[5].monitor + 1);
          ImageSet(instance, pTime->CutNomber - 1, v21);
          v26 = *(f32 *)&ProcessData[5].monitor + 0.016666668;
          if (v26 > 0.95)
            v26 = 1.0;
          *(f32 *)&ProcessData[5].monitor = v26;
          if (first)
          {
            v29 = instance;
            (v29->staffSet->FrameImage->klass->vtable._22_get_color.methodPtr)(v29->staffSet->FrameImage, v29->staffSet->FrameImage->klass->vtable._22_get_color.method);
            (v29->staffSet->FrameImage->klass->vtable._23_set_color.methodPtr)(v29->staffSet->FrameImage, v29->staffSet->FrameImage->klass->vtable._23_set_color.method);
          }
          CutNomber = (u32)pTime->CutNomber;
          if ((s32)CutNomber <= 21)
          {
            if (!v32)
            {
              LODWORD() = pTime->CutNomber;
            }
            ImageSet(instance, (s32)*(f32 *)&ProcessData[5].monitor);
          }
          else
          {
            v33 = instance;
            movie = v33->staffSet->movie;
            if (!movie->play)
              movie->play = 1;
            MovieSet(v33, *(f32 *)&ProcessData[5].monitor);
          }
          if (*(f32 *)&ProcessData[5].monitor != 1.0 || *((f32 *)&ProcessData[5].monitor + 1) != 0.0)
            break;
          if (pTime->CutNomber <= 20)
          {
            if (!v36)
            v40 = get_Instance(Project_staffUI);
            OffCut(v40, pTime->CutNomber - 1);
            OnCut(instance, pTime->CutNomber + 1);
          }
          else
          {
            if (!v36)
            v37 = get_Instance(Project_staffUI);
            OffCut(v37, pTime->CutNomber - 1);
            get_Instance();
          }
          ProcessData[5].monitor = 0x3F80000000000000LL;
          first = 0;
LABEL_59:
          v44 = stafftime[SHIDWORD(ProcessData[4].monitor)];
          ProcessData[3].monitor = v44;
LABEL_60:
          klass_high = *v9;
LABEL_61:
          *v9 = klass_high + 1;
          break;
        default:
          break;
      }
    }
  }
  v20 = 0;
  ++LODWORD(ProcessData[5].klass);
  return v20;
}

// 0x21fb530
void StaffDataTextLoad(Staff_t *staff, dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  char **v6;
  char **p_monitor;
  s64 v8;
  char **v9;
  char *v10;
  char *v11;
  char *v12;
  Staff_t *StaffData_local;
  char *v15;
  char *v16;
  char **v17;
  char *v18;
  char *v19;
  char *v21;
  char *v23;
  char *v24;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
  v6 = &ProcessData[6];
  p_monitor = &ProcessData[6].monitor;
  v8 = 4;
  {
LABEL_15:
    StaffData_local = StaffData;
    if (v8 - 4 >= SLODWORD(StaffData_local->max_length))
      goto LABEL_34;
    v15 = *v6;
    v16 = *(char **)(*((u64 *)&StaffData_local->obj.klass + v8) + 16);
    if (!v16)
    {
      v17 = &" ";
      goto LABEL_27;
    }
    goto LABEL_28;
LABEL_27:
    v16 = *v17;
LABEL_28:
    v18 = Concat_54766928(v15, v16, 0);
    *v6 = v18;
    v19 = Concat_54766928(*v6, "\n", 0);
    *v6 = v19;
    v21 = *p_monitor;
    v10 = *(char **)(*((u64 *)&StaffData->obj.klass + v8) + 24);
    if (!v10)
    {
      v9 = &" ";
      goto LABEL_11;
    }
    goto LABEL_12;
LABEL_11:
    v10 = *v9;
LABEL_12:
    v11 = Concat_54766928(v21, v10, 0);
    *p_monitor = v11;
    v12 = Concat_54766928(*p_monitor, "\n", 0);
    *p_monitor = v12;
    if (++v8 == 1028)
      return;
  }
  goto LABEL_15;
LABEL_34:
  v23 = *v6;
  v24 = *p_monitor;
  (instance->staffSet->captionTMProUGUI->klass->vtable._66_set_text.methodPtr)(instance->staffSet->captionTMProUGUI, v23, instance->staffSet->captionTMProUGUI->klass->vtable._66_set_text.method);
  (instance->staffSet->nameTMProUGUI->klass->vtable._66_set_text.methodPtr)(instance->staffSet->nameTMProUGUI, v24, instance->staffSet->nameTMProUGUI->klass->vtable._66_set_text.method);
}

// 0x21fb9a0
void StaffRollOn(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  void *Instance;
  void *gameObject;
  void *v9;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  if (HIDWORD(ProcessData[4].monitor) == 2)
  {
    Instance = get_Instance(Project_staffUI);
    gameObject = get_gameObject(Instance->staffSet->captionTMProUGUI, 0);
    ActiveOnOff(gameObject, gameObject, 1);
    v9 = get_gameObject(Instance->staffSet->nameTMProUGUI, 0);
    ActiveOnOff(v9, v9, 1);
  }
}

// 0x21f8db0
static s32 At3Load(staffData_t *pData) {
  if ((byte_5759091 & 1) == 0)
  {
    if ((pData->Flag & 0x100) == 0)
      goto LABEL_3;
    return 1;
  }
  if ((pData->Flag & 0x100) != 0)
    return 1;
LABEL_3:
  sndBgmLoadId_XF(23);
  pData->Flag |= 0x100u;
  return 0;
}

// 0x21f9070
static s32 At3Play(staffData_t *pData) {
  if ((pData->Flag & 0x200) != 0)
    return 1;
  if (sndBgmStatus_XF() == 2)
  {
    sndBgmFadeIn(0, 0);
    pData->Flag |= 0x200u;
    return 1;
  }
  return 0;
}

// 0x21fbb40
static s32 At3Stop(staffData_t *pData) {
  sndBgmStop();
  sndBgmFree();
  pData->Flag &= 0xFFFFFCFF;
  return 0;
}

// 0x21fbbc0
static staffData_t *Init(void) {
  staffData_t *v1;
  Time_t *v3;

  v1 = Allocate(staffData_t);
  _ctor(v1);
  v3 = v1->time;
  *(u64 *)&v1->FadeCount = 0;
  *(u64 *)&v1->Nomber = 0;
  *(u32 *)&v1->ObjAlhaOut = 1065353216;
  *(u32 *)&v3->WaitTimer = 0;
  *(u64 *)&v3->fade = 0xFFFFFFFF00000000LL;
  return v1;
}

// 0x21fbc40
static void Destroy(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  char *v7;
  dds3ProcessID_t *monitor;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  v7 = "staff_draw";
  endrolls_item_count = 0;
  dds3KillProcessName(v7, 0);
  cmpDeleteEffect();
  End();
  UnloadStaffUI();
  monitor = ProcessData[2].monitor;
  if (monitor)
  {
    evtEnd(monitor);
  }
  ProcessData[2].monitor = 0;
  ProcessData[3].klass = 0;
  sndBgmStop();
  sndBgmFree();
  LODWORD(ProcessData[1].klass) &= 0xFFFFFCFF;
  fclFilterOFF();
  g_mainPID = 0;
}

// 0x21fbec0
void ProcessStart(void) {
  dds3ProcessID_t *v1;
  staffData_t *v2;
  Time_t *v4;
  dds3ProcessFunc_t v6;
  shutdownfuncDelegate v7;
  dds3ProcessID_t *started;
  dds3ProcessFunc_t v10;
  dds3ProcessID_t *v11;

  ENABLE_MOVIESKIP();
  v1 = Allocate(dds3ProcessID_t);
  _ctor(v1, 0);
  v2 = Allocate(staffData_t);
  _ctor(v2);
  v4 = v2->time;
  *(u64 *)&v2->FadeCount = 0;
  *(u64 *)&v2->Nomber = 0;
  *(u32 *)&v2->ObjAlhaOut = 1065353216;
  *(u32 *)&v4->WaitTimer = 0;
  *(u64 *)&v4->fade = 0xFFFFFFFF00000000LL;
  v6 = Allocate(dds3ProcessFunc_t);
  _ctor(v6, 0, Method_Project_StaffMain_FirstCalcProcess__, 0);
  v7 = Allocate(shutdownfuncDelegate);
  _ctor(v7, 0, Method_Project_StaffMain_Destroy__, 0);
  started = dds3StartProcess("staff_calc", 1031, 0, 1, v6, v7, v2);
  g_mainPID = started;
  v10 = Allocate(dds3ProcessFunc_t);
  _ctor(v10, 0, Method_Project_StaffMain_FirstDrawProcess__, 0);
  v11 = dds3StartProcess("staff_draw", 11031, 0, 0, v10, 0, v2);
  v2->drawPID = v11;
}

// 0x21fc150
void ProcessEnd(void) {
  dds3KillProcessName("staff_calc", 0);
  dds3KillProcessName("staff_draw", 0);
  cmpDeleteEffect();
  End();
  UnloadStaffUI();
}

// 0x21fc260
bool ProcessCheck(void) {
  return dds3SearchProcessName("staff_calc") != 0;
}

// 0x21fc2e0
s32 GetTableMax(void) {
  return stafftime->max_length;
}

// 0x21fb140
void StaffTimeJumpAndFree(Time_t *pCurrenTime, Time_t *pTime) {
  Time_t *v3;

  v3 = pTime;
  pCurrenTime = v3;
}

// 0x21fb8c0
s32 GetStaffTableMax(void) {
  return StaffData->max_length;
}

// 0x21f98d0
static void SakuraEffectDraw(void) {
  cmpEffectSetRGBA(0x80808080);
  cmpDrawEffect();
}

// 0x21fc370
static void EndSkip(dds3ProcessID_t *PID) {
  dds3ProcessID_t *id;

  id = PID;
  dds3GetProcessData(id);
}
