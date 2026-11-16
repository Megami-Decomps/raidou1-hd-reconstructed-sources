#include "types.h"
#include "CMP_STATUS_TYPE.h"
#include "buttonguide.h"
#include "cfg.h"
#include "cmpitem.h"
#include "cmpmain.h"
#include "cmpmodel.h"
#include "cmpraidouskill.h"
#include "cmpstatus.h"
#include "dat.h"
#include "dds3_pad.h"
#include "dds3kernelcore.h"
#include "dds3kerneldraw.h"
#include "dds3scenebasic.h"
#include "dds3worldbasic.h"
#include "ditectivebook.h"
#include "evtbit.h"
#include "evtmoon.h"
#include "evtviewer.h"
#include "fclmisc.h"
#include "fclmsg.h"
#include "fld.h"
#include "gohaccident.h"
#include "gohcalc.h"
#include "gohcombinetbl.h"
#include "gohcombunity.h"
#include "gohdraw.h"
#include "gohinit.h"
#include "gohmain.h"
#include "gohmenu.h"
#include "gohrenken.h"
#include "gohswordhistory.h"
#include "gohswordtree.h"
#include "itf.h"
#include "jms_cmdmenu.h"
#include "jmscmdmenu.h"
#include "jmsmisc.h"
#include "kernel.h"
#include "localize.h"
#include "mdl.h"
#include "raijindlc.h"
#include "sbtlsound.h"
#include "sbtlsub.h"
#include "sbtlweapon.h"
#include "scr.h"
#include "sdat.h"
#include "sdfmem.h"
#include "sdfsound.h"
#include "tips.h"

typedef enum {
    OK_1 = 0,
    OK_2 = 1,
    OK_1_2 = 2,
    ERR_1 = 3,
    ERR_2 = 4,
    ERR_1_2 = 5,
} GOH_CYUUSEI;

typedef enum {
    GOH_SEQ_ROOT_WAIT = 0,
    GOH_SEQ_ROOT = 1,
    GOH_SEQ_CMBSEL = 2,
    GOH_SEQ_CMB1 = 3,
    GOH_SEQ_CMB2 = 4,
    GOH_SEQ_CMB_SEARCHI = 5,
    GOH_SEQ_SEARCHI_ERR = 6,
    GOH_SEQ_SEARCHI_RESULT = 7,
    GOH_SEQ_SEARCHI_CMB = 8,
    GOH_SEQ_SWORD = 9,
    GOH_SEQ_SWORD2 = 10,
    GOH_SEQ_SWORD_TREE = 11,
    GOH_SEQ_STAT = 12,
    GOH_SEQ_CONFIRM = 13,
    GOH_SEQ_CYUUSEI = 14,
    GOH_SEQ_ACCIDENT = 15,
    GOH_SEQ_KARTE_ROOT = 16,
    GOH_SEQ_RECOVER = 17,
    GOH_SEQ_TALK = 18,
    GOH_SEQ_MISC = 19,
    GOH_SEQ_SINAN = 20,
    GOH_SEQ_COMB_CNT = 21,
    GOH_SEQ_ERROR = 22,
    GOH_SEQ_DIRECTION = 23,
    GOH_SEQ_BOOK = 24,
    GOH_SEQ_SWORD_SHORTCUT = 25,
    GOH_SEQ_NEW_SWORD_SKL_SET = 26,
    GOH_SEQ_EQUIP_SWORD = 27,
    GOH_SEQ_COMB_SHORTCUT = 28,
    GOH_SEQ_OMOIDE_SKILL = 29,
} GOH_SEQ;

typedef struct dds3ProcessID_t dds3ProcessID_t;
typedef struct gohData_t gohData_t;
typedef struct jmsSeqUnit_t jmsSeqUnit_t;
typedef struct sdatUnitWork_t sdatUnitWork_t;

char *sceneName;
char *uiSceneName;
char *textAssetName;
u8 s_bDrawBack;
u8 s_bEndCmb;
s32 g_count;
jmsSeqUnit_t *gohSeqUnit;

static void LoadLocalizeText(void);
u32 GetDevilSE(s32 devilID, s32 motionID);

// 0x1bc9640
void gohSetDispButtonGuide(GOH_GUIDE _guide, bool _status, bool _d) {
  Il2CppObject *Item;
  bool v13;

  if (logdispwk)
  {
    if (logdispwk->start)
      return;
  }
  if (status)
  {
    if (tipsProcessCheck())
      return;
    goto LABEL_15;
  }
  if (tipsProcessCheck())
    return;
  v13 = !d;
  ButtonLineHelpDispSet(v13);
LABEL_15:
  if (object___ContainsKey(gohGuides, guide))
  {
    Item = object___get_Item(gohGuides, guide);
    gohGohGuideSet(Item, 0, 90);
  }
  else
  {
    LogWarning("不明なボタンガイドID", 0);
  }
}

// 0x1bc98c0
void gohUnloadScene(char *_sceneName) {
  UnityEngine_SceneManagement_Scene_o v3;
  UnityEngine_SceneManagement_Scene_o scene;

  scene.m_Handle = GetSceneByName(sceneName, 0).m_Handle;
  if (IsValid((UnityEngine_SceneManagement_Scene_o)&scene, 0))
  {
    v3.m_Handle = scene.m_Handle;
    UnloadSceneAsync_61083440(v3, 0);
  }
}

// 0x1bc9960
static void LoadLocalizeText(void) {
  void *p_Dependent;
  void *Dependent_local;

  p_Dependent = &Dependent;
  Dependent_local = p_Dependent;
  Load(Dependent_local, textAssetName, textAssetName);
  LoadSyncAll(_Ctrl_k__BackingField, 0);
  LoadLocalizeText_2(textAssetName, "GOH_MENU");
  LoadLocalizeText_2(textAssetName, "GOH_CAPTION");
  LoadLocalizeText_2(textAssetName, "GOH_BST");
  LoadLocalizeText_2(textAssetName, "GOH_SEARCHI");
  LoadLocalizeText_2(textAssetName, "GOH_SEARCHI_HELP");
  LoadLocalizeText_2(textAssetName, "GOH_CONDITION");
  LoadLocalizeText_2(textAssetName, "GOH_SORT");
  LoadLocalizeText_2(textAssetName, "GOH_RENKEN");
  LoadLocalizeText_2(textAssetName, "GOH_KARTE");
  Unload(Dependent, textAssetName, 0);
}

// 0x1bc9c80
s32 gohCmbSearchiInit(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  void *monitor;
  void **p_monitor;
  s32 klass;
  bool *v13;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  monitor = ProcessData[28].monitor;
  HIDWORD(ProcessData[20].monitor) = 0;
  if (monitor)
  {
    p_monitor = &ProcessData[28].monitor;
    if (((instance->klass->vtable._11_CombCreateTblSettingSet.methodPtr)(instance, *p_monitor, instance->klass->vtable._11_CombCreateTblSettingSet.method) & 1) != 0)
      LODWORD(ProcessData[1].klass) &= ~0x100000u;
    *p_monitor = 0;
  }
  klass = ProcessData[1].klass;
  if ((klass & 0x100000) == 0)
  {
    (instance->klass->vtable._7_CreateSearchiTbl.methodPtr)(instance, instance->klass->vtable._7_CreateSearchiTbl.method);
    goto LABEL_22;
  }
  LODWORD(ProcessData[1].klass) = klass & 0xFFEFFFFF;
LABEL_22:
  resultCsr = 0;
  sortCsr = 0;
  v13 = NewSpecific(bool, 6u);
  sortSets = v13;
  sortSets[0] = 1;
  GohLoadConditionTbl();
  if (!s_bDrawBack)
  {
    gohCallDrawBack();
    s_bDrawBack = 1;
  }
  s_bEndCmb = 0;
  return 1;
}

// 0x1bca020
s32 gohCmbSearchiDestroy(dds3ProcessID_t *PID) {
  dds3ProcessID_t *id;

  id = PID;
  dds3GetProcessData(id);
  if (!s_bDrawBack)
    return 1;
  if (!s_bEndCmb)
    return 1;
  gohCallDrawBack();
  *(u16 *)&s_bDrawBack = 0;
  return 1;
}

// 0x1bca1a0
dds3ProcessFunc_t gohCmbSearchiCalcProcess(dds3ProcessID_t *PID) {
  gohData_t *ProcessData;
  char v5;
  jmsSeqUnit_t *p_pSeqUnit;
  dds3ProcessFunc_t v8;
  jmsSeqUnit_t *v12;
  SearchiCtrl *v15;
  s64 v22;
  SearchiCtrl *v23;
  Il2CppObject *Item;
  s64 v26;
  void *v27;
  s32 Status;
  jmsSeqUnit_t *v30;
  s64 v31;
  SearchiCtrl *v32;
  s64 v33;
  s64 csrNo;
  void *TextList;
  MenuCsrUnitySp *v37;
  s64 v39;
  jmsSeqUnit_t *gohSeqUnit_local;
  s64 v42;
  SearchiCtrl *v43;
  bool Par_bool;
  bool v46;
  s64 v47;
  SearchiCtrl *v48;
  s64 v50;
  MenuCsrUnitySp *conditionCsr_local;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  v5 = jmsChkCommonInput(0xFu);
  p_pSeqUnit = &ProcessData->pSeqUnit;
  v8 = jmsSeqChange(ProcessData->SeqHandle, &ProcessData->pSeqUnit, 0, id);
  if (v8)
    return v8;
  if (gohStopStatusDraw(ProcessData, 0, 0) < 2)
    return v8;
  evtMoonDisableDraw(1);
  if (ProcessData->WorkStat)
    goto LABEL_18;
  if (CHECK_TRIG(46339, 1))
  {
    if (!condition)
    {
      v27 = (loc_1BE49C0)(0);
      Status = GetStatus(v27, 0);
      switch (Status)
      {
        case 3:
          gohSeqUnit_local = gohSeqUnit;
          jmsSeqJumpAndFree(p_pSeqUnit, &gohSeqUnit_local[6]);
          break;
        case 2:
          SE(1);
          return v8;
        case 0:
          ProcessData->m_eCombineType2 = 3;
          v30 = gohSeqUnit;
          jmsSeqJumpAndFree(&ProcessData->pSeqUnit, &v30[7]);
          SE(0);
          v31 = (loc_1BE49C0)(0);
          v32 = (*(*(u64 *)v31 + 472))(v31, *(u64 *)(*(u64 *)v31 + 480));
          ProcessData->backSearch = v32;
          break;
      }
      goto LABEL_102;
    }
  }
  if (!CHECK_TRIG(46338, 1))
    goto LABEL_39;
  if (!condition)
  {
    v33 = (loc_1BE49C0)(0);
    (*(*(u64 *)v33 + 456))(v33, *(u64 *)(*(u64 *)v33 + 464));
  }
  else
  {
LABEL_39:
    if ((v5 & 1) == 0)
    {
      if ((v5 & 2) != 0)
      {
        if (condition)
        {
          SE(1);
          condition = 0;
        }
        else
        {
          v39 = (loc_1BE49C0)(0);
          (*(*(u64 *)v39 + 568))(v39, *(u64 *)(*(u64 *)v39 + 576));
          ProcessData->WorkStat = 1;
        }
      }
      goto LABEL_102;
    }
    if (condition)
    {
      v22 = (loc_1BE49C0)(0);
      v23 = (*(*(u64 *)v22 + 408))(v22, *(u64 *)(*(u64 *)v22 + 416));
      Item = _get_Item(conditionList, conditionCsr->csrNo);
      SetPar_int_(v23, (s32)Item[1].monitor, decisionType);
      v26 = (loc_1BE49C0)(0);
      (*(*(u64 *)v26 + 424))(v26, *(u64 *)(*(u64 *)v26 + 432));
      condition = 0;
      goto LABEL_101;
    }
    csrNo = searchiCsr->csrNo;
    if (searchiDrawSet[csrNo])
    {
      LODWORD(csrNo) = searchiCsr->csrNo;
      decisionType = csrNo;
      TextList = GohGetTextList(csrNo);
      conditionList = TextList;
      v37 = Allocate(MenuCsrUnitySp);
      _ctor(v37, 0);
      conditionCsr = v37;
      (conditionCsr->klass->vtable._5_SetMaxPar.methodPtr)(conditionCsr, (u32)conditionList->_size, 10, conditionCsr->klass->vtable._5_SetMaxPar.method);
      condition = 1;
      goto LABEL_101;
    }
    v42 = (loc_1BE49C0)(0);
    v43 = (*(*(u64 *)v42 + 408))(v42, *(u64 *)(*(u64 *)v42 + 416));
    Par_bool = GetPar_bool_(v43, searchiCsr->csrNo);
    v46 = !Par_bool;
    v47 = (loc_1BE49C0)(0);
    v48 = (*(*(u64 *)v47 + 408))(v47, *(u64 *)(*(u64 *)v47 + 416));
    SetPar_bool_(v48, v46, searchiCsr->csrNo);
  }
  v50 = (loc_1BE49C0)(0);
  (*(*(u64 *)v50 + 424))(v50, *(u64 *)(*(u64 *)v50 + 432));
LABEL_101:
  SE(0);
LABEL_102:
  if (condition)
  {
    (conditionCsr->klass->vtable._5_SetMaxPar.methodPtr)(conditionCsr, (u32)conditionList->_size, 10, conditionCsr->klass->vtable._5_SetMaxPar.method);
    conditionCsr_local = conditionCsr;
  }
  else
  {
    (searchiCsr->klass->vtable._5_SetMaxPar.methodPtr)(searchiCsr, 13, 10, searchiCsr->klass->vtable._5_SetMaxPar.method);
    conditionCsr_local = searchiCsr;
  }
  (conditionCsr_local->klass->vtable._10_CsrUpdate.methodPtr)(conditionCsr_local, conditionCsr_local->klass->vtable._10_CsrUpdate.method);
  return v8;
LABEL_18:
  if (!*(u32 *)((instance->klass->vtable._6_GetSearchiCtrl.methodPtr)(instance, instance->klass->vtable._6_GetSearchiCtrl.method) + 20))
  {
    v12 = gohSeqUnit;
    jmsSeqJumpAndFree(&ProcessData->pSeqUnit, &v12[2]);
    ProcessData->WorkStat = 0;
    s_bEndCmb = 1;
    SE(1);
    v15 = (instance->klass->vtable._10_CombCreateTblSettingGet.methodPtr)(instance, instance->klass->vtable._10_CombCreateTblSettingGet.method);
    ProcessData->backSearch = v15;
    return v8;
  }
  return v8;
}

// 0x1bcadc0
dds3ProcessFunc_t gohCmbSearchiDrawProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  jmsSeqUnit_t *v5;
  jmsSeqHandle_t *monitor;
  dds3ProcessID_t *v7;
  dds3ProcessFunc_t v8;
  Il2CppObject *Instance;
  void *v10;
  void *name;
  void *v12;
  void *v13;
  char *v15;
  char *LocalizeText;
  s64 v17;
  char *v18;
  s64 v19;
  char *v20;
  s64 v21;
  Il2CppObject *v23;
  char *v24;
  const char *namespaze;
  char *v26;
  s32 size;
  s32 v29;
  Il2CppClass *klass;
  void *v31;
  Il2CppObject *v32;
  char *v33;
  s32 listTop;
  char *v36;
  Il2CppObject *v39;
  s32 v44;
  Il2CppObject *v45;
  Il2CppObject *v46;
  Il2CppObject *v47;
  s32 v49;
  char data[4];
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  v5 = &ProcessData[2];
  monitor = ProcessData[1].monitor;
  v7 = id;
  v8 = jmsSeqChange(monitor, v5, 1, v7);
  if (!v8)
  {
    Instance = _get_Instance();
    CombBackActive(Instance, 0, 0);
    v10 = *((void *)_get_Instance()[18].monitor + 2);
    if (get_activeSelf(v10, 0))
      SetActive(v10, 0, 0);
    name = _get_Instance()[20].klass->_1.name;
    if (!get_activeSelf(name, 0))
      SetActive(name, 1, 0);
    v12 = *((void *)_get_Instance()[19].monitor + 2);
    if (!get_activeSelf(v12, 0))
      SetActive(v12, 1, 0);
    v13 = _get_Instance()[17].monitor;
    v15 = strGohMenu[21];
    LocalizeText = GetLocalizeText(v15, 1);
    TitleDraw(v13, 0, LocalizeText, 0);
    v17 = *((u64 *)_get_Instance()[19].monitor + 4);
    v18 = GetLocalizeText("GOH_CAPTION_L0043", 1);
    (*(*(u64 *)v17 + 1368))(v17, v18, *(u64 *)(*(u64 *)v17 + 1376));
    v19 = *((u64 *)_get_Instance()[19].monitor + 5);
    v20 = GetLocalizeText("GOH_CAPTION_L0036", 1);
    (*(*(u64 *)v19 + 1368))(v19, v20, *(u64 *)(*(u64 *)v19 + 1376));
    v21 = *((u64 *)_get_Instance()[19].monitor + 3);
    data[0] = GBWK->player->para->level;
    v23 = Box(sbyte, data);
    v24 = Format("{0}", v23, 0);
    (*(*(u64 *)v21 + 1368))(v21, v24, *(u64 *)(*(u64 *)v21 + 1376));
    namespaze = _get_Instance()[20].klass->_1.namespaze;
    v26 = GetLocalizeText("GOH_SEARCHI_L0012", 1);
    (*(*(u64 *)namespaze + 1368))(namespaze, v26, *(u64 *)(*(u64 *)namespaze + 1376));
    size = instance->searchCombTbls->_size;
    if (size >= 500)
      size = 500;
    v29 = size & ~(size >> 31);
    klass = _get_Instance()[20].klass;
    v49 = v29;
    v31 = klass->_1.byval_arg.data;
    v32 = Box(s32, &v49);
    v33 = Format("{0}", v32, 0);
    (*(*(u64 *)v31 + 1368))(v31, v33, *(u64 *)(*(u64 *)v31 + 1376));
    listTop = searchiCsr->listTop;
    gohScrollBar(0, 0, 5, 238, listTop, 10, 13, 4);
    gohSearchiListDraw();
    v36 = searchiHelpText[searchiCsr->csrNo];
    ButtonLineHelpTextSet(v36, 0, 1, 0xA09DC380, 1);
    if (condition)
    {
      v39 = _get_Instance();
      CombConditionActive(v39[20].klass, 1, 0);
      gohConditionListDraw();
      gohScrollBar(0, 0, 5, 238, conditionCsr->listTop, 10, conditionList->_size, 5);
      gohSetDispButtonGuide(22, 0, 0);
LABEL_53:
      v46 = _get_Instance();
      SetImageColorChangeActive(v46[20].klass->_1.this_arg.data, condition, 0);
      v47 = _get_Instance();
      SetImageColorChangeActive(*(void *)&v47[20].klass->_1.byval_arg.bits, !condition, 0);
      return v8;
    }
    if (GetStatus(instance, 0) == 1)
      v44 = 21;
    else
      v44 = 20;
    gohSetDispButtonGuide(v44, 0, 0);
    v45 = _get_Instance();
    CombConditionActive(v45[20].klass, 0, 0);
    goto LABEL_53;
  }
  return v8;
}

// 0x1bcb590
dds3ProcessFunc_t gohCmbSearchiUpdateProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  jmsSeqHandle_t *monitor;
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
  monitor = ProcessData[1].monitor;
  v6 = id;
  return jmsSeqChange(monitor, &ProcessData[2], 2, v6);
}

// 0x1bcb6b0
s32 gohSearchiErrorInit(dds3ProcessID_t *PID) {
  dds3ProcessID_t *id;

  id = PID;
  dds3GetProcessData(id);
  fclSetMessageInvalid(1);
  fclStartMessage(29);
  return 1;
}

// 0x1bcb7a0
s32 gohSearchiErrorDestroy(dds3ProcessID_t *PID) {
  dds3ProcessID_t *id;

  id = PID;
  dds3GetProcessData(id);
  return 1;
}

// 0x1bcb820
dds3ProcessFunc_t gohSearchiErrorCalcProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  jmsSeqUnit_t *v5;
  jmsSeqHandle_t *monitor;
  dds3ProcessID_t *v7;
  dds3ProcessFunc_t v8;
  jmsSeqUnit_t *gohSeqUnit_local;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  v5 = &ProcessData[2];
  monitor = ProcessData[1].monitor;
  v7 = id;
  v8 = jmsSeqChange(monitor, &ProcessData[2], 0, v7);
  if (v8)
    return v8;
  if (!!fclChkMessage())
    return v8;
  LODWORD(ProcessData[1].klass) |= 0x100000u;
  gohSeqUnit_local = gohSeqUnit;
  jmsSeqJumpAndFree(v5, &gohSeqUnit_local[5]);
  return 0;
}

// 0x1bcba10
dds3ProcessFunc_t gohSearchiErrorDrawProcess(dds3ProcessID_t *PID) {
  gohData_t *ProcessData;
  jmsSeqHandle_t *SeqHandle;
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
  gohModel(ProcessData);
  SeqHandle = ProcessData->SeqHandle;
  v6 = id;
  return jmsSeqChange(SeqHandle, &ProcessData->pSeqUnit, 1, v6);
}

// 0x1bcbb70
dds3ProcessFunc_t gohSearchiErrorUpdateProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  jmsSeqHandle_t *monitor;
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
  fclUpdateMessage();
  monitor = ProcessData[1].monitor;
  v6 = id;
  return jmsSeqChange(monitor, &ProcessData[2], 2, v6);
}

// 0x1bcbcd0
s32 gohSearchiResultInit(dds3ProcessID_t *PID) {
  gohData_t *ProcessData;
  s64 naturalAligment;
  MenuCsrUnity *v9;
  MenuCsrUnity *v11;
  MenuCsrUnity *v12;
  MenuCsrUnity *v14;
  MenuCsrUnity *v15;
  const MethodInfo_32670E0 *v17;
  Il2CppObject *Instance;
  Il2CppObject *v19;
  Il2CppObject *v23;
  ResultCsr *v24;
  MenuCsrUnity *v27;
  bool *v30;
  s64 v33;
  dds3ProcessID_t *v34;
  dds3ProcessID_t *PIDa;
  dds3ProcessID_t *id;

  id = PID;
  PIDa = 0;
  ProcessData = dds3GetProcessData(id);
  if (ProcessData)
  {
    if (ProcessData->klass->_2.naturalAligment < (u32)naturalAligment || ProcessData->klass->_2.typeHierarchy[naturalAligment - 1] != gohData_t)
    {
      v23 = ProcessData;
      goto LABEL_81;
    }
  }
  if (ProcessData->m_eCombineType2 != 3 || ProcessData->searchi)
  {
    goto LABEL_13;
  }
  (instance->klass->vtable._9_CombCreateTblSettingClear.methodPtr)(instance, instance->klass->vtable._9_CombCreateTblSettingClear.method);
  (instance->klass->vtable._7_CreateSearchiTbl.methodPtr)(instance, instance->klass->vtable._7_CreateSearchiTbl.method);
LABEL_13:
  resultUnit_t = 0;
  GohResultCalcSortSetting(ProcessData);
  if (resultCsr)
  {
    goto LABEL_15;
  }
  else
  {
    v24 = Allocate(ResultCsr);
    _ctor(v24, 0);
    resultCsr = v24;
LABEL_15:
    if (sortCsr)
      goto LABEL_16;
    goto LABEL_41;
  }
  if (sortCsr)
  {
LABEL_16:
    goto LABEL_17;
  }
LABEL_41:
  v27 = Allocate(MenuCsrUnity);
  _ctor(v27, 0);
  sortCsr = v27;
LABEL_17:
  v9 = Allocate(MenuCsrUnity);
  _ctor(v9, 0);
  resultStatusCsr[0] = v9;
  v11 = resultStatusCsr;
  v12 = Allocate(MenuCsrUnity);
  _ctor(v12, 0);
  v11[1] = v12;
  v14 = resultStatusCsr;
  v15 = Allocate(MenuCsrUnity);
  _ctor(v15, 0);
  v14[2] = v15;
  if (sortSets)
  {
    goto LABEL_30;
  }
  v30 = NewSpecific(bool, 6u);
  sortSets = v30;
  sortSets[0] = 1;
LABEL_30:
  resultSort = 0;
  ProcessData->resultSelDevil = 0;
  ProcessData->combiDevil1 = 0;
  ProcessData->cmbBackStatus = 2;
  ProcessData->combiDevil2 = 0;
  ProcessData->combiBarthDevil = 0;
  v17 = Method_Project_SingletonMonoBehaviour_GohCanvasManager__get_Instance__;
  ProcessData->WorkStat = 0;
  Instance = _get_Instance(v17);
  CombBackActive(Instance, 1, 0);
  v19 = _get_Instance();
  TitleOff(v19[17].monitor, 0);
  if (s_bDrawBack)
    goto LABEL_32;
  gohCallDrawBack();
  s_bDrawBack = 1;
LABEL_33:
  s_bEndCmb = 0;
  goto LABEL_34;
LABEL_32:
  goto LABEL_33;
LABEL_34:
  PIDa = gohGetMenuPID();
  v23 = dds3GetProcessData(PIDa);
  if (!v23)
    return 1;
  if (v23->klass->_2.naturalAligment < (u32)v33 || v23->klass->_2.typeHierarchy[v33 - 1] != Menu_t)
  {
LABEL_81:
  }
  if (!BYTE4(v23[5].monitor))
  {
    BYTE4(v23[5].monitor) = 1;
    v34 = PIDa;
    itfMenuUpdateLink(v34);
  }
  return 1;
}

// 0x1bcc430
s32 gohSearchiResultDestroy(dds3ProcessID_t *PID) {
  void *Instance;
  dds3ProcessID_t *id;

  id = PID;
  dds3GetProcessData(id);
  if (!s_bDrawBack)
    goto LABEL_15;
  if (s_bEndCmb)
  {
    gohCallDrawBack();
    s_bDrawBack = 0;
    goto LABEL_15;
  }
LABEL_15:
  Instance = get_Instance(0);
  ItfSortMenuActive(Instance, 0, 0);
  return 1;
}

// 0x1bcc5e0
dds3ProcessFunc_t gohSearchiResultCalcProcess(dds3ProcessID_t *PID) {
  gohData_t *ProcessData;
  s16 v5;
  jmsSeqUnit_t *p_pSeqUnit;
  dds3ProcessFunc_t v8;
  _BOOL4 searchi;
  void *Instance;
  void *v14;
  void *v15;
  void *DvlList;
  s64 cmbBackStatus;
  MenuCsrUnity *v28;
  ResultCsr *v36;
  MenuCsrUnity *v37;
  s32 v40;
  jmsSeqUnit_t *v43;
  s32 v44;
  bool v45;
  s32 v46;
  s32 v47;
  void *v48;
  jmsSeqUnit_t *gohSeqUnit_local;
  Il2CppObject *Item;
  sdatUnitWork_t *DevilFormatDevil;
  jmsSeqUnit_t *v55;
  u32 v57;
  void *v58;
  bool v59;
  s32 listMaxCnt;
  s32 cursorMax;
  dds3ProcessID_t *id;

  id = PID;
  cursorMax = 0;
  listMaxCnt = 0;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  v5 = jmsChkCommonInput(0x130Fu);
  p_pSeqUnit = &ProcessData->pSeqUnit;
  v8 = jmsSeqChange(ProcessData->SeqHandle, &ProcessData->pSeqUnit, 0, id);
  if (v8)
    return v8;
  if (resultUnit_t)
    goto LABEL_20;
  if (GetStatus(instance, 0) == 1)
    goto LABEL_20;
  goto LABEL_26;
  if (GetStatus(instance, 0) == 1)
  {
LABEL_20:
    goto LABEL_21;
  }
LABEL_26:
  searchi = ProcessData->searchi;
  if (!GohCreateResultTbl(searchi))
  {
    (instance->klass->vtable._9_CombCreateTblSettingClear.methodPtr)(instance, instance->klass->vtable._9_CombCreateTblSettingClear.method);
    (instance->klass->vtable._7_CreateSearchiTbl.methodPtr)(instance, instance->klass->vtable._7_CreateSearchiTbl.method);
    return v8;
  }
  Instance = get_Instance(0);
  ListSet_object_(Instance, resultUnit_t);
  v14 = get_Instance(0);
  ListSort(v14, 0);
  v15 = get_Instance(0);
  DvlList = GetDvlList(v15, 0, 0);
  resultUnit_t = DvlList;
LABEL_21:
  if (gohStopStatusDraw(ProcessData, 0, 0) < 2)
    return v8;
  evtMoonEnableDraw();
  if (!resultUnit_t)
    return v8;
  if (resultUnit_t->_size >= 1)
  {
    cursorMax = 0;
    listMaxCnt = 0;
    GohResultGetStatusCsrCnt(ProcessData, &cursorMax, &listMaxCnt);
    if (resultSort)
    {
      goto LABEL_48;
    }
    else
    {
      (resultCsr->klass->vtable._5_SetMaxPar.methodPtr)(resultCsr, (u32)resultUnit_t->_size, 16, resultCsr->klass->vtable._5_SetMaxPar.method);
      SetWidthPar(resultCsr, 4, 1, 0);
      (resultCsr->klass->vtable._10_CsrUpdate.methodPtr)(resultCsr, resultCsr->klass->vtable._10_CsrUpdate.method);
LABEL_48:
      if (!resultCsr->statusCsr)
        goto LABEL_68;
      goto LABEL_62;
    }
    if (!resultCsr->statusCsr)
      goto LABEL_68;
LABEL_62:
    if (!resultSort)
    {
      cmbBackStatus = ProcessData->cmbBackStatus;
      v28 = resultStatusCsr[cmbBackStatus];
      GohSetStatusCsrCollider(cmbBackStatus, v28);
      (v28->klass->vtable._5_SetMaxPar.methodPtr)(v28, cursorMax, listMaxCnt, v28->klass->vtable._5_SetMaxPar.method);
      (v28->klass->vtable._10_CsrUpdate.methodPtr)(v28, v28->klass->vtable._10_CsrUpdate.method);
    }
LABEL_68:
    if ((v5 & 1) == 0)
      goto LABEL_74;
    if (resultCsr->statusCsr)
    {
LABEL_74:
      if ((v5 & 2) != 0)
      {
        if (resultSort)
          goto LABEL_148;
        if (resultCsr->statusCsr)
        {
          resultCsr->statusCsr = 0;
          v40 = 1;
        }
        else if (ProcessData->searchi)
        {
          ProcessData->Flag |= 0x100000u;
          gohSeqUnit_local = gohSeqUnit;
          jmsSeqJumpAndFree(p_pSeqUnit, &gohSeqUnit_local[5]);
          v40 = 1;
        }
        else
        {
          v55 = gohSeqUnit;
          jmsSeqJumpAndFree(p_pSeqUnit, &v55[2]);
          v40 = 1;
          s_bEndCmb = 1;
        }
        goto LABEL_147;
      }
      if (CHECK_TRIG(46083, 1))
      {
        if (!resultCsr->statusCsr)
        {
          if (!resultSort)
          {
            Item = _get_Item(resultUnit_t, resultCsr->csrNo);
            DevilFormatDevil = GohCreateDevilFormatDevil(SHIWORD(Item[1].klass));
            ProcessData->combiBarthDevil = DevilFormatDevil;
            CombStatusCheck(ProcessData, 2);
            goto LABEL_148;
          }
        }
      }
      if ((v5 & 0x100) == 0)
        goto LABEL_162;
      if (!resultSort)
      {
        v44 = ProcessData->cmbBackStatus;
        v45 = __OFSUB__(v44, 1);
        v46 = v44 - 1;
        if (v46 < 0 != v45)
          v46 = 2;
      }
      else
      {
LABEL_162:
        if ((v5 & 0x200) == 0)
          goto LABEL_97;
        if (resultSort)
        {
LABEL_97:
          if (!CHECK_TRIG(46082, 1))
            goto LABEL_148;
          if (resultSort)
            goto LABEL_148;
          v36 = resultCsr;
          if (v36->statusCsr || cursorMax < 1)
            goto LABEL_148;
          v36 = resultCsr;
          v36->statusCsr = 1;
          v37 = resultStatusCsr[ProcessData->cmbBackStatus];
          (v37->klass->vtable._4_CsrClear.methodPtr)(v37, v37->klass->vtable._4_CsrClear.method);
          goto LABEL_123;
        }
        v47 = ProcessData->cmbBackStatus;
        if (v47 <= 1)
          v46 = v47 + 1;
        else
          v46 = 0;
      }
      ProcessData->cmbBackStatus = v46;
      SE(9);
      v48 = *((void *)_get_Instance()[20].monitor + 3);
      MenuChange(v48, animChengeTbl[ProcessData->cmbBackStatus], 0);
      goto LABEL_148;
    }
    if (resultSort)
      goto LABEL_148;
    ProcessData->resultSelDevil = SHIWORD(_get_Item(resultUnit_t, resultCsr->csrNo)[1].klass);
    ProcessData->m_eCombineType2 = 4;
    combiCsr = 0;
    v43 = gohSeqUnit;
    jmsSeqJumpAndFree(p_pSeqUnit, &v43[8]);
LABEL_123:
    v40 = 0;
LABEL_147:
    SE(v40);
LABEL_148:
    if (resultCsr->statusCsr)
    {
      if (!v57)
      v58 = get_Instance(0);
      v59 = 0;
    }
    else
    {
      if (!v57)
      v58 = get_Instance(0);
      v59 = 1;
    }
    ItfSortMenuActive(v58, v59, 0);
  }
  return v8;
}

// 0x1bcd0c0
dds3ProcessFunc_t gohSearchiResultDrawProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  jmsSeqHandle_t *monitor;
  dds3ProcessID_t *v6;
  dds3ProcessFunc_t v7;
  Il2CppObject *Instance;
  Il2CppObject *v10;
  void *name;
  void *v12;
  s64 v13;
  char *LocalizeText;
  s64 v15;
  char *v16;
  s64 v17;
  Il2CppObject *v19;
  char *v20;
  s32 klass_low;
  Il2CppObject *Item;
  sdatUnitWork_t *DevilFormatDevil;
  MenuCsrUnity *v27;
  Il2CppObject *v28;
  void *v29;
  Il2CppObject *v30;
  s32 klass;
  struct GohCombUnity *v32;
  f32 v34;
  s32 v35;
  s32 listTop;
  f32 v37;
  f32 v39;
  s32 v40;
  bool v43;
  bool v44;
  Il2CppObject *v45;
  Il2CppObject *v46;
  Il2CppObject *v48;
  char *v50;
  char data[4];
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
  v6 = id;
  v7 = jmsSeqChange(monitor, &ProcessData[2], 1, v6);
  if (!v7)
  {
    Instance = _get_Instance();
    CombiActive(Instance, 0, 0);
    v10 = _get_Instance();
    CombBackActive(v10, 1, 0);
    name = _get_Instance()[20].klass->_1.name;
    if (get_activeSelf(name, 0))
      SetActive(name, 0, 0);
    v12 = *((void *)_get_Instance()[19].monitor + 2);
    if (!get_activeSelf(v12, 0))
      SetActive(v12, 1, 0);
    v13 = *((u64 *)_get_Instance()[19].monitor + 4);
    LocalizeText = GetLocalizeText("GOH_CAPTION_L0043", 1);
    (*(*(u64 *)v13 + 1368))(v13, LocalizeText, *(u64 *)(*(u64 *)v13 + 1376));
    v15 = *((u64 *)_get_Instance()[19].monitor + 5);
    v16 = GetLocalizeText("GOH_CAPTION_L0036", 1);
    (*(*(u64 *)v15 + 1368))(v15, v16, *(u64 *)(*(u64 *)v15 + 1376));
    v17 = *((u64 *)_get_Instance()[19].monitor + 3);
    data[0] = GBWK->player->para->level;
    v19 = Box(sbyte, data);
    v20 = Format("{0}", v19, 0);
    (*(*(u64 *)v17 + 1368))(v17, v20, *(u64 *)(*(u64 *)v17 + 1376));
    if (resultUnit_t)
    {
      if (resultUnit_t->_size >= 1)
      {
        klass_low = LOBYTE(ProcessData[31].klass);
        Item = _get_Item(resultUnit_t, resultCsr->csrNo);
        DevilFormatDevil = GohCreateDevilFormatDevil(SHIWORD(Item[1].klass));
        gohResultDevilDraw(klass_low == 0);
        v27 = resultStatusCsr[SLODWORD(ProcessData[28].klass)];
        v28 = _get_Instance();
        CombBackStatus(v28[20].monitor, (s32)ProcessData[28].klass, DevilFormatDevil, v27, resultCsr->statusCsr, klass_low == 0, 0);
        if (!HIDWORD(ProcessData[20].monitor))
        {
          v29 = *((void *)_get_Instance()[20].monitor + 3);
          if (IsDraw(v29, 0))
          {
            MenuChange(v29, 1, 0);
          }
          else
          {
            v30 = _get_Instance();
            InfoClear(v30[20].monitor, 0);
            MenuOpne(v29, 2, 1, 0);
          }
          ++HIDWORD(ProcessData[20].monitor);
        }
        klass = ProcessData[28].klass;
        CombBackGuideSet(klass, klass_low == 0);
        LODWORD(v32) = resultUnit_t->_size;
        v34 = (s32)v32;
        v35 = (u8)v32 & 3;
        listTop = resultCsr->listTop;
        v37 = v34 * 0.25;
        if (v37 <= 4.0 || v35 == 0)
          v39 = v37;
        else
          v39 = v37 + 1.0;
        if (v39 == INFINITY)
          v40 = 0x80000000;
        else
          v40 = v39;
        gohScrollBar(0, 0, 0, 0, listTop / 4, 4, v40, 6);
        if (!resultCsr->statusCsr)
        {
          if (!resultSort)
          {
            v44 = 0;
            v43 = 1;
            goto LABEL_59;
          }
        }
        v43 = 0;
        v44 = !resultSort;
LABEL_59:
        v45 = _get_Instance();
        SetScrollBarColorChangeActive(*(void *)(*((u64 *)v45[20].monitor + 3) + 96), v44, 0);
        v46 = _get_Instance();
        SetImageColorChangeActive(*(void *)(*((u64 *)v46[20].monitor + 4) + 40), v43, 0);
        if (resultCsr->statusCsr)
        {
          goto LABEL_62;
        }
        v48 = _get_Instance();
        CombBackStatusCsrOff(v48[20].monitor, (s32)ProcessData[28].klass, 0);
LABEL_62:
        if (resultCsr->statusCsr)
          return v7;
        v50 = gohCaption[19];
        ButtonLineHelpTextSet(v50, 0, 1, 0xA09DC380, 1);
      }
    }
  }
  return v7;
}

// 0x1bcd850
dds3ProcessFunc_t gohSearchiResultUpdateProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  jmsSeqHandle_t *monitor;
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
  monitor = ProcessData[1].monitor;
  v6 = id;
  return jmsSeqChange(monitor, &ProcessData[2], 2, v6);
}

// 0x1bcd970
void gohMoveCmbCsrFunc(void) {
  gohData_t *GohData;
  gohData_t *v3;
  s32 cmbBackStatus;
  MenuCsrUnity *v7;

  GohData = GohGetGohData();
  if (!GohData)
    return;
  v3 = GohData;
  if (!resultStatusCsr)
    return;
  cmbBackStatus = v3->cmbBackStatus;
  if (cmbBackStatus >= SLODWORD(resultStatusCsr->max_length))
    return;
  v7 = resultStatusCsr[v3->cmbBackStatus];
  (v7->klass->vtable._4_CsrClear.methodPtr)(v7, v7->klass->vtable._4_CsrClear.method);
}

// 0x1bcdaa0
s32 gohSearchiCmbInit(dds3ProcessID_t *PID) {
  gohData_t *ProcessData;
  bool *v7;
  CombiCsr *v10;
  CsrUnityMoveFunc v14;
  MenuCsrUnity *v15;
  MenuCsrUnity *v21;
  MenuCsrUnity *v23;
  MenuCsrUnity *v24;
  MenuCsrUnity *v26;
  MenuCsrUnity *v27;
  const MethodInfo_32670E0 *v28;
  void *v29;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  GohCreateCombiTbl(ProcessData);
  GohCmbCalcSortSetting(ProcessData);
  if (sortSets)
  {
    goto LABEL_13;
  }
  else
  {
    v7 = NewSpecific(bool, 6u);
    sortSets = v7;
    sortSets[0] = 1;
LABEL_13:
    if (combiCsr)
      goto LABEL_14;
    goto LABEL_22;
  }
  if (combiCsr)
  {
LABEL_14:
    goto LABEL_15;
  }
LABEL_22:
  v10 = Allocate(CombiCsr);
  _ctor(v10, 0);
  combiCsr = v10;
  v14 = Allocate(CsrUnityMoveFunc);
  _ctor(v14, 0, Method_Project_gohMain_MoveCmbCsrFunc__, 0);
  (combiCsr->klass->vtable._6_SetMoveFunc.methodPtr)(combiCsr, v14, combiCsr->klass->vtable._6_SetMoveFunc.method);
LABEL_15:
  if (!sortCsr)
  {
    v15 = Allocate(MenuCsrUnity);
    _ctor(v15, 0);
    sortCsr = v15;
  }
  resultSort = 0;
  v21 = Allocate(MenuCsrUnity);
  _ctor(v21, 0);
  resultStatusCsr[0] = v21;
  v23 = resultStatusCsr;
  v24 = Allocate(MenuCsrUnity);
  _ctor(v24, 0);
  v23[1] = v24;
  v26 = resultStatusCsr;
  v27 = Allocate(MenuCsrUnity);
  _ctor(v27, 0);
  v26[2] = v27;
  v28 = Method_Project_SingletonMonoBehaviour_GohCanvasManager__get_Instance__;
  ProcessData->cmbBackStatus = 2;
  v29 = *((void *)_get_Instance(v28)[20].monitor + 3);
  if (IsDraw(v29, 0))
    MenuChange(v29, 1, 0);
  else
    MenuOpne(v29, 2, 1, 0);
  return 1;
}

// 0x1bcdf50
s32 gohSearchiCmbDestroy(dds3ProcessID_t *PID) {
  void *Instance;
  dds3ProcessID_t *id;

  id = PID;
  dds3GetProcessData(id);
  Instance = get_Instance(0);
  ItfSortMenuActive(Instance, 0, 0);
  return 1;
}

// 0x1bce030
dds3ProcessFunc_t gohSearchiCmbCalcProcess(dds3ProcessID_t *PID) {
  gohData_t *ProcessData;
  s16 v5;
  dds3ProcessFunc_t v7;
  Il2CppObject *Instance;
  struct GohCombUnity *v13;
  s32 v14;
  s32 v15;
  s32 v19;
  s64 cmbBackStatus;
  MenuCsrUnity *v21;
  Il2CppClass *klass;
  Il2CppObject *Item;
  jmsSeqUnit_t *gohSeqUnit_local;
  Il2CppObject *v33;
  sdatUnitWork_t *DevilFormatDevil;
  s32 v35;
  Il2CppClass *v36;
  sdatUnitWork_t *monitor;
  MenuCsrUnity *v42;
  s32 v43;
  s32 v44;
  s32 v45;
  bool v46;
  void *v47;
  _BOOL4 statusCsr;
  void *v51;
  sdatUnitWork_t *devil1;
  s32 listMaxCnt;
  s32 cursorMax;
  dds3ProcessID_t *id;

  id = PID;
  cursorMax = 0;
  listMaxCnt = 0;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  v5 = jmsChkCommonInput(0x130Fu);
  v7 = jmsSeqChange(ProcessData->SeqHandle, &ProcessData->pSeqUnit, 0, id);
  if (!v7)
  {
    if (gohStopStatusDraw(ProcessData, 0, 0) < 2)
      return v7;
    if (s_bDrawBack)
    {
      if (!s_bEndCmb)
      {
        Instance = _get_Instance();
        ChangeAnim(Instance[16].monitor, 0, 0);
      }
    }
    evtMoonEnableDraw();
    cursorMax = 0;
    listMaxCnt = 0;
    LODWORD(v13) = combiCsr->csrNo;
    v14 = (s32)v13 / 3;
    v15 = (s32)v13 % 3;
    GohCombiGetStatusCsrCnt(ProcessData, (s32)v13 % 3, (s32)v13 / 3, &cursorMax, &listMaxCnt);
    if (resultSort)
    {
      goto LABEL_29;
    }
    else
    {
      (combiCsr->klass->vtable._5_SetMaxPar.methodPtr)(combiCsr, (u32)(3 * combiTbl->_size), 12, combiCsr->klass->vtable._5_SetMaxPar.method);
      SetWidthPar(combiCsr, 3, 1, 0);
      (combiCsr->klass->vtable._10_CsrUpdate.methodPtr)(combiCsr, combiCsr->klass->vtable._10_CsrUpdate.method);
LABEL_29:
      if (!combiCsr->statusCsr)
        goto LABEL_41;
      goto LABEL_35;
    }
    if (!combiCsr->statusCsr)
      goto LABEL_41;
LABEL_35:
    if (!resultSort)
    {
      v19 = v15;
      cmbBackStatus = ProcessData->cmbBackStatus;
      v21 = resultStatusCsr[cmbBackStatus];
      GohSetStatusCsrCollider(cmbBackStatus, v21);
      (v21->klass->vtable._5_SetMaxPar.methodPtr)(v21, cursorMax, listMaxCnt, v21->klass->vtable._5_SetMaxPar.method);
      (v21->klass->vtable._10_CsrUpdate.methodPtr)(v21, v21->klass->vtable._10_CsrUpdate.method);
      v15 = v19;
    }
LABEL_41:
    if ((v5 & 1) != 0)
    {
      if (!combiCsr->statusCsr)
      {
        if (!resultSort)
        {
          devil1 = _get_Item(combiTbl, v14)[1].monitor;
          klass = _get_Item(combiTbl, v14)[2].klass;
          Item = _get_Item(combiTbl, v14);
          GohDisableComb(ProcessData, devil1, klass, Item[2].monitor);
          SE(0);
        }
      }
    }
    if ((v5 & 2) != 0)
    {
      if (!resultSort)
      {
        if (combiCsr->statusCsr)
        {
          combiCsr->statusCsr = 0;
        }
        else
        {
          ProcessData->m_eCombineType2 = 3;
          gohSeqUnit_local = gohSeqUnit;
          jmsSeqJumpAndFree(&ProcessData->pSeqUnit, &gohSeqUnit_local[7]);
        }
      }
      SE(1);
    }
    if (CHECK_TRIG(46083, 1))
    {
      if (!combiCsr->statusCsr)
      {
        if (!resultSort)
        {
          if (v15 == 1)
          {
            v36 = _get_Item(combiTbl, v14)[2].klass;
            ProcessData->combiDevil2 = (sdatUnitWork_t *)v36;
            v35 = 1;
          }
          else if (v15 == 2)
          {
            v33 = _get_Item(combiTbl, v14);
            DevilFormatDevil = GohCreateDevilFormatDevil(*((s16 *)v33[2].monitor + 11));
            ProcessData->combiBarthDevil = DevilFormatDevil;
            v35 = 2;
          }
          else
          {
            monitor = _get_Item(combiTbl, v14)[1].monitor;
            ProcessData->combiDevil1 = monitor;
            v35 = 0;
          }
          CombStatusCheck(ProcessData, v35);
        }
      }
    }
    if ((v5 & 0x200) == 0)
      goto LABEL_121;
    if (!resultSort)
    {
      v43 = ProcessData->cmbBackStatus;
      if (v43 <= 1)
        v44 = v43 + 1;
      else
        v44 = 0;
    }
    else
    {
LABEL_121:
      if ((v5 & 0x100) == 0)
        goto LABEL_94;
      if (resultSort)
      {
LABEL_94:
        if (CHECK_TRIG(46082, 1))
        {
          if (!resultSort)
          {
            if (!combiCsr->statusCsr)
            {
              v42 = resultStatusCsr[ProcessData->cmbBackStatus];
              (v42->klass->vtable._4_CsrClear.methodPtr)(v42, v42->klass->vtable._4_CsrClear.method);
              combiCsr->statusCsr = 1;
              SE(0);
            }
          }
        }
LABEL_112:
        statusCsr = combiCsr->statusCsr;
        v51 = get_Instance(0);
        ItfSortMenuActive(v51, !statusCsr, 0);
        return v7;
      }
      v45 = ProcessData->cmbBackStatus;
      v46 = __OFSUB__(v45, 1);
      v44 = v45 - 1;
      if (v44 < 0 != v46)
        v44 = 2;
    }
    ProcessData->cmbBackStatus = v44;
    SE(9);
    v47 = *((void *)_get_Instance()[20].monitor + 3);
    MenuChange(v47, animChengeTbl[ProcessData->cmbBackStatus], 0);
    goto LABEL_112;
  }
  return v7;
}

// 0x1bce900
dds3ProcessFunc_t gohSearchiCmbDrawProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  jmsSeqHandle_t *monitor;
  dds3ProcessID_t *v6;
  dds3ProcessFunc_t v7;
  Il2CppObject *Instance;
  void *v11;
  Il2CppObject *v12;
  s64 v13;
  char *LocalizeText;
  s64 v15;
  char *v16;
  s64 v17;
  Il2CppObject *v19;
  char *v20;
  struct GohCombUnity *static_fields;
  MenuCsrUnity *v24;
  s32 v25;
  s32 v26;
  sdatUnitWork_t *DevilFormatDevil;
  Il2CppObject *Item;
  sdatUnitWork_t *p_monitor;
  s32 v32;
  Il2CppObject *v35;
  s32 klass_low;
  Il2CppObject *v37;
  s32 klass;
  s32 size;
  s32 v41;
  bool v44;
  Il2CppObject *v45;
  Il2CppObject *v46;
  Il2CppObject *v48;
  char *v50;
  Il2CppObject *v51;
  Il2CppObject *v52;
  u8 data[4];
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
  v6 = id;
  v7 = jmsSeqChange(monitor, &ProcessData[2], 1, v6);
  if (!v7)
  {
    if (combiTbl)
    {
      Instance = _get_Instance();
      AllCardOff(*((void *)Instance[20].monitor + 4), 0);
      v11 = *(void *)(*((u64 *)_get_Instance()[20].monitor + 4) + 24);
      if (get_enabled(v11, 0))
        set_enabled(v11, 0, 0);
      v12 = _get_Instance();
      CombiActive(v12, 1, 0);
      gohCombiListDraw();
      v13 = *((u64 *)_get_Instance()[19].monitor + 4);
      LocalizeText = GetLocalizeText("GOH_CAPTION_L0043", 1);
      (*(*(u64 *)v13 + 1368))(v13, LocalizeText, *(u64 *)(*(u64 *)v13 + 1376));
      v15 = *((u64 *)_get_Instance()[19].monitor + 5);
      v16 = GetLocalizeText("GOH_CAPTION_L0036", 1);
      (*(*(u64 *)v15 + 1368))(v15, v16, *(u64 *)(*(u64 *)v15 + 1376));
      v17 = *((u64 *)_get_Instance()[19].monitor + 3);
      data[0] = GBWK->player->para->level;
      v19 = Box(sbyte, data);
      v20 = Format("{0}", v19, 0);
      (*(*(u64 *)v17 + 1368))(v17, v20, *(u64 *)(*(u64 *)v17 + 1376));
      LODWORD(static_fields) = combiCsr->csrNo;
      v24 = resultStatusCsr[SLODWORD(ProcessData[28].klass)];
      v25 = (s32)static_fields / 3;
      v26 = (s32)static_fields % 3;
      DevilFormatDevil = Allocate(sdatUnitWork_t);
      _ctor(DevilFormatDevil, 0);
      if (v26 == 2)
      {
        Item = _get_Item(combiTbl, v25);
        DevilFormatDevil = GohCreateDevilFormatDevil(*((s16 *)Item[2].monitor + 11));
        p_monitor = &_get_Item(combiTbl, v25)[2].monitor;
        v32 = 2;
LABEL_41:
        ClassCopy(DevilFormatDevil, p_monitor, 0);
LABEL_42:
        klass_low = LOBYTE(ProcessData[31].klass);
        v37 = _get_Instance();
        CombiStatus(v37[20].monitor, (s32)ProcessData[28].klass, DevilFormatDevil, v24, v32, 0);
        klass = ProcessData[28].klass;
        GohCombiGuideSet(klass, klass_low == 0, v32);
        size = combiTbl->_size;
        v41 = combiCsr->listTop / 3;
        gohScrollBar(0, 0, 0, 0, v41, 4, size, 7);
        if (combiCsr->statusCsr)
          goto LABEL_65;
        if (resultSort)
        {
LABEL_65:
          v44 = !resultSort;
          v45 = _get_Instance();
          SetScrollBarColorChangeActive(*(void *)(*((u64 *)v45[20].monitor + 3) + 96), v44, 0);
          v46 = _get_Instance();
          SetImageColorChangeActive(*(void *)(*((u64 *)v46[20].monitor + 5) + 32), 0, 0);
          goto LABEL_54;
        }
        else
        {
          v51 = _get_Instance();
          SetImageColorChangeActive(*(void *)(*((u64 *)v51[20].monitor + 5) + 32), 1, 0);
          v52 = _get_Instance();
          SetScrollBarColorChangeActive(*(void *)(*((u64 *)v52[20].monitor + 3) + 96), 0, 0);
LABEL_54:
          if (!combiCsr->statusCsr)
          {
            v48 = _get_Instance();
            CombBackStatusCsrOff(v48[20].monitor, (s32)ProcessData[28].klass, 0);
            v50 = gohCaption[28];
            ButtonLineHelpTextSet(v50, 0, 1, 0xA09DC380, 1);
          }
          return v7;
        }
        goto LABEL_54;
      }
      if (v25 < combiTbl->_size)
      {
        if (v26)
        {
          p_monitor = &_get_Item(combiTbl, v25)[2];
          v32 = 1;
        }
        else
        {
          v35 = _get_Item(combiTbl, v25);
          v32 = 0;
          p_monitor = &v35[1].monitor;
        }
        goto LABEL_41;
      }
      v32 = -1;
      goto LABEL_42;
    }
  }
  return v7;
}

// 0x1bcf090
dds3ProcessFunc_t gohSearchiCmbUpdateProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  jmsSeqHandle_t *monitor;
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
  monitor = ProcessData[1].monitor;
  v6 = id;
  return jmsSeqChange(monitor, &ProcessData[2], 2, v6);
}

// 0x1bcf1b0
s32 gohCmbSelInit(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  s32 klass;
  void *monitor;
  char *v7;
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
  klass = ProcessData[13].klass;
  HIDWORD(ProcessData[13].klass) = 0;
  if (klass == 2)
    return 1;
  if (!gohCheckOpen(21))
    goto LABEL_14;
LABEL_17:
  gohStart();
  monitor = _get_Instance()[17].monitor;
  v7 = strGohMenu[1];
  LocalizeText = GetLocalizeText(v7, 1);
  TitleDraw(monitor, 0, LocalizeText, 0);
  return 1;
LABEL_14:
  if (gohCheckOpen(22))
    goto LABEL_17;
  return 1;
}

// 0x1bcf390
s32 gohCmbSelDestroy(dds3ProcessID_t *PID) {
  return 1;
}

// 0x1bcf3a0
dds3ProcessFunc_t gohCmbSelCalcProcess(dds3ProcessID_t *PID) {
  gohData_t *ProcessData;
  jmsSeqUnit_t *p_pSeqUnit;
  jmsSeqHandle_t *SeqHandle;
  dds3ProcessID_t *v7;
  dds3ProcessFunc_t v8;
  Il2CppObject *Instance;
  Il2CppObject *v11;
  Il2CppObject *v14;
  tagGOH_MENU_WORK *v15;
  s32 m_eCombineType;
  char *v18;
  Il2CppObject *v19;
  s32 SelectIndex;
  s32 v22;
  s32 CalcStep;
  u32 v26;
  u32 v27;
  jmsSeqUnit_t *gohSeqUnit_local;
  jmsSeqUnit_t *v30;
  jmsSeqUnit_t *v32;
  jmsSeqUnit_t *v34;
  bool *v38;
  Il2CppObject *v40;
  jmsSeqUnit_t *v42;
  MenuCsrUnitySp *v43;
  MenuCsrUnitySp *v46;
  Il2CppObject *v48;
  jmsSeqUnit_t *v49;
  System_Enum_o v50;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  p_pSeqUnit = &ProcessData->pSeqUnit;
  SeqHandle = ProcessData->SeqHandle;
  v7 = id;
  v8 = jmsSeqChange(SeqHandle, &ProcessData->pSeqUnit, 0, v7);
  if (!v8)
  {
    if (!ProcessData->CalcStep)
    {
      ProcessData->m_eCombineType = 0;
      ProcessData->m_eCombineType2 = 1;
      if (!ProcessData->searchi)
      {
        Instance = _get_Instance();
        AllListClear(Instance[19].klass->_1.events, 0);
        v11 = _get_Instance();
        AllListClear(v11[19].klass->_1.typeMetadataHandle, 0);
      }
    }
    evtMoonDisableDraw(1);
    if (!dds3ExistProcess(g_mainPID))
      goto LABEL_36;
    v14 = dds3GetProcessData(g_mainPID);
    if (!v14)
      goto LABEL_36;
    v15 = v14;
    if (v14[1].monitor)
    {
      gohChkEnableSelect(v15);
    }
LABEL_36:
    m_eCombineType = ProcessData->m_eCombineType;
    if (m_eCombineType)
      goto LABEL_37;
    if (!gohCheckOpen(21))
    {
      if (!gohCheckOpen(22))
        goto LABEL_57;
    }
    SelectIndex = gohGetSelectIndex();
    if (SelectIndex == -1)
    {
      if (!gohCheckMovePrev())
        return v8;
      gohSeqUnit_local = gohSeqUnit;
      v30 = &gohSeqUnit_local[1];
      goto LABEL_111;
    }
    v22 = gohGetSelectIndex();
    switch (v22)
    {
      case 22:
        ProcessData->searchi = 0;
        ProcessData->m_eCombineType = 1;
        ProcessData->m_eCombineType2 = 3;
        resultCsr = 0;
        sortCsr = 0;
        v38 = NewSpecific(bool, 6u);
        sortSets = v38;
        sortSets[0] = 1;
        v40 = _get_Instance();
        TitleOff(v40[17].monitor, 0);
        v42 = gohSeqUnit;
        jmsSeqJumpAndFree(&ProcessData->pSeqUnit, &v42[7]);
        break;
      case 21:
        ProcessData->searchi = 1;
        ProcessData->m_eCombineType = 1;
        v43 = Allocate(MenuCsrUnitySp);
        _ctor(v43, 0);
        searchiCsr = v43;
        v46 = Allocate(MenuCsrUnitySp);
        _ctor(v46, 0);
        conditionCsr = v46;
        break;
      case 6:
        ProcessData->searchi = 0;
LABEL_57:
        ProcessData->m_eCombineType = 1;
        goto LABEL_58;
    }
    m_eCombineType = ProcessData->m_eCombineType;
    if (!m_eCombineType)
      return v8;
LABEL_37:
    if (m_eCombineType != 1)
    {
      *(u32 *)&v50.System_ValueType_Fields = m_eCombineType;
      v50.klass = (System_Enum_c *)GOH_COMBINE_TYPE;
      v50.monitor = -1;
      v18 = ToString(&v50, 0);
      v19 = Concat_54766928("来ないはず", v18, 0);
      LogError(v19, 0);
      return v8;
    }
LABEL_58:
    if (ProcessData->searchi)
    {
      CalcStep = ProcessData->CalcStep;
      if (CalcStep == 1)
      {
        if (!GohCreateAllUnitSortTbl(ProcessData))
          return v8;
LABEL_83:
        ProcessData->CalcStep = 2;
        return v8;
      }
      if (!CalcStep)
      {
        if (!GohCreateAllUnitSortTbl(ProcessData))
        {
          ProcessData->CalcStep = 1;
          return v8;
        }
        goto LABEL_83;
      }
      v32 = gohSeqUnit;
      v30 = &v32[5];
    }
    else
    {
      if (datGetStockDevilNums(0) <= 1)
      {
        ProcessData->ErrorType = 0;
        v34 = gohSeqUnit;
        v30 = &v34[22];
      }
      else
      {
        v26 = ProcessData->CalcStep;
        if (v26 <= 6)
        {
          if (!v27)
          gohCreateCombineResult(ProcessData, v26);
          ++ProcessData->CalcStep;
          return v8;
        }
        if (!v27)
        gohCreateDevSelList(ProcessData);
        v48 = _get_Instance();
        TitleOff(v48[17].monitor, 0);
        v49 = gohSeqUnit;
        v30 = &v49[3];
      }
    }
LABEL_111:
    jmsSeqJumpAndFree(p_pSeqUnit, v30);
    return v8;
  }
  return v8;
}

// 0x1bd0100
dds3ProcessFunc_t gohCmbSelDrawProcess(dds3ProcessID_t *PID) {
  gohData_t *ProcessData;
  jmsSeqHandle_t *SeqHandle;
  dds3ProcessID_t *v6;
  dds3ProcessFunc_t result;
  void *name;
  void *v10;
  void *v11;
  Il2CppObject *Instance;
  void *v13;
  Il2CppObject *v14;
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
  v6 = id;
  result = jmsSeqChange(SeqHandle, &ProcessData->pSeqUnit, 1, v6);
  if (!result)
  {
    if (ProcessData->m_eCombineType != 2)
    {
      gohUnityDraw(1);
    }
    gohSetDispButtonGuide(1, 0, 0);
    gohModel(ProcessData);
    name = _get_Instance()[19].klass->_1.name;
    if (get_activeSelf(name, 0))
      SetActive(name, 0, 0);
    v10 = _get_Instance()[20].klass->_1.name;
    if (get_activeSelf(v10, 0))
      SetActive(v10, 0, 0);
    v11 = *((void *)_get_Instance()[18].monitor + 2);
    if (get_activeSelf(v11, 0))
      SetActive(v11, 0, 0);
    Instance = _get_Instance();
    CombBackActive(Instance, 0, 0);
    v13 = *((void *)_get_Instance()[19].monitor + 2);
    if (get_activeSelf(v13, 0))
      SetActive(v13, 0, 0);
    v14 = _get_Instance();
    BackObjActive(v14, 1, 0);
    return 0;
  }
  return result;
}

// 0x1bd03e0
dds3ProcessFunc_t gohCmbSelUpdateProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  jmsSeqHandle_t *monitor;
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
  monitor = ProcessData[1].monitor;
  v6 = id;
  return jmsSeqChange(monitor, &ProcessData[2], 2, v6);
}

// 0x1bd0500
s32 gohCmb1Init(dds3ProcessID_t *PID) {
  Il2CppObject *Instance;
  Il2CppObject *ProcessData;
  dds3ProcessID_t *v9;
  dds3ProcessID_t *id;

  id = 0;
  fclEndMessageEx(2);
  if (!s_bDrawBack)
  {
    gohCallDrawBack();
    s_bDrawBack = 1;
  }
  s_bEndCmb = 0;
  Instance = _get_Instance();
  ResultSetActive(Instance[19].klass, 0, 0);
  id = gohGetMenuPID();
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    return 1;
  if (BYTE4(ProcessData[5].monitor))
    return 1;
  BYTE4(ProcessData[5].monitor) = 1;
  v9 = id;
  itfMenuUpdateLink(v9);
  return 1;
}

// 0x1bd07c0
s32 gohCmb1Destroy(dds3ProcessID_t *PID) {
  dds3ProcessID_t *id;

  id = PID;
  dds3GetProcessData(id);
  if (!s_bDrawBack)
    return 1;
  if (!s_bEndCmb)
    return 1;
  gohCallDrawBack();
  *(u16 *)&s_bDrawBack = 0;
  return 1;
}

// 0x1bd0940
dds3ProcessFunc_t gohCmb1CalcProcess(dds3ProcessID_t *PID) {
  gohData_t *ProcessData;
  s32 v5;
  u32 v6;
  char v7;
  jmsSeqHandle_t *SeqHandle;
  dds3ProcessID_t *v9;
  dds3ProcessFunc_t v11;
  sdatUnitWork_t *v14;
  s32 devilid;
  jmsSeqUnit_t *gohSeqUnit_local;
  void *m_pDevSelList1;
  s32 m_iDevColumn;
  s32 v22;
  jmsSeqUnit_t *v24;
  s32 v26;
  jmsSeqUnit_t *v30;
  s32 v31;
  bool v32;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  v5 = ITEMIDX(ProcessData->m_pDevSelList1);
  if (ProcessData->m_eCombineType == 1)
    v6 = 4107;
  else
    v6 = 7;
  v7 = jmsChkCommonInput(v6);
  SeqHandle = ProcessData->SeqHandle;
  v9 = id;
  v11 = jmsSeqChange(SeqHandle, &ProcessData->pSeqUnit, 0, v9);
  if (v11)
    return v11;
  if (gohStopStatusDraw(ProcessData, 0, 0) < 2)
    return v11;
  evtMoonEnableDraw();
  if ((v7 & 1) != 0)
  {
    v14 = GBWK->player->stock_id[v5];
    devilid = v14->devilid;
    if (!DlcDevilSelCheck(devilid))
      return v11;
    if (v14->now->hp >= 1 && (v14->badstatus & 0x120000) == 0)
    {
      gohSeqUnit_local = gohSeqUnit;
      jmsSeqJumpAndFree(&ProcessData->pSeqUnit, &gohSeqUnit_local[4]);
      SE(0);
    }
  }
  if ((v7 & 2) != 0)
  {
    v24 = gohSeqUnit;
    jmsSeqJumpAndFree(&ProcessData->pSeqUnit, &v24[2]);
    s_bEndCmb = 1;
    SE(1);
    if (!CHECK_TRIG(42766, 1))
    {
LABEL_39:
      if (!CHECK_TRIG(46083, 1))
        goto LABEL_40;
      goto LABEL_53;
    }
  }
  else if (!CHECK_TRIG(42766, 1))
  {
    goto LABEL_39;
  }
  ProcessData->Flag ^= 0x80000u;
  SE(0);
  if (!CHECK_TRIG(46083, 1))
  {
LABEL_40:
    m_pDevSelList1 = ProcessData->m_pDevSelList1;
    goto LABEL_42;
  }
LABEL_53:
  v26 = GBWK->player->stock_id[v5]->devilid;
  if (!DlcDevilSelCheck(v26))
    return v11;
  ProcessData->m_iStatusType = 0;
  resultCheck = 0;
  v30 = gohSeqUnit;
  jmsSeqJumpAndFree(&ProcessData->pSeqUnit, &v30[12]);
  SE(0);
  m_pDevSelList1 = ProcessData->m_pDevSelList1;
LABEL_42:
  gohSelectMenuUpdate(m_pDevSelList1);
  if (CHECK_REP(4103, 1))
  {
    m_iDevColumn = ProcessData->m_iDevColumn;
    if (m_iDevColumn < datGetStockDevilNums(0) - 12)
    {
      v22 = ProcessData->m_iDevColumn + 1;
LABEL_65:
      ProcessData->m_iDevColumn = v22;
      SE(3);
    }
  }
  else if (CHECK_REP(4102, 1))
  {
    v31 = ProcessData->m_iDevColumn;
    v32 = __OFSUB__(v31, 1);
    v22 = v31 - 1;
    if (v22 < 0 == v32)
      goto LABEL_65;
  }
  return v11;
}

// 0x1bd1030
dds3ProcessFunc_t gohCmb1DrawProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  void *v5;
  void *v6;
  void *v7;
  s32 klass;
  s32 Index;
  s32 v11;
  s32 devilid;
  bool v15;
  Il2CppObject *Instance;
  s32 v19;
  Il2CppObject *v20;
  void *v21;
  jmsSeqHandle_t *monitor;
  jmsSeqUnit_t *v23;
  dds3ProcessID_t *v24;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  v5 = HEAD(ProcessData[13].monitor);
  TAIL(ProcessData[13].monitor);
  v6 = LISTTOP(ProcessData[13].monitor);
  v7 = CURRENT(ProcessData[13].monitor);
  klass = ProcessData[1].klass;
  if (v5)
  {
    LODWORD(v5) = v6->Index;
    Index = v7->Index;
    v11 = ProcessData[1].klass;
    goto LABEL_11;
  }
  Index = 0;
  v11 = ProcessData[1].klass;
LABEL_11:
  if ((v11 & 0x40000) == 0)
    return 0;
  gohModel(ProcessData);
  gohCaption(0, 0, 0, (klass & 0x80000) == 0);
  gohCombineListFrameA(0, (s32)v5, Index, ProcessData);
  if (LODWORD(ProcessData[13].klass) != 1)
    goto LABEL_38;
  devilid = GBWK->player->stock_id[Index]->devilid;
  v15 = DlcDevilSelCheck(devilid);
  if ((BYTE2(ProcessData[1].klass) & 8) == 0)
  {
    Instance = _get_Instance();
    CombineHelpActive(Instance[19].klass, 0, 0);
    if (v15)
      v19 = 2;
    else
      v19 = 4;
    goto LABEL_37;
  }
  gohCombineIconHelp();
  v20 = _get_Instance();
  CombineHelpActive(v20[19].klass, 1, 0);
  v21 = *((void *)_get_Instance()[18].monitor + 2);
  if (get_activeSelf(v21, 0))
    SetActive(v21, 0, 0);
  if (v15)
    v19 = 3;
  else
    v19 = 5;
LABEL_37:
  gohSetDispButtonGuide(v19, 0, 1);
LABEL_38:
  monitor = ProcessData[1].monitor;
  v23 = &ProcessData[2];
  v24 = id;
  return jmsSeqChange(monitor, v23, 1, v24);
}

// 0x1bd1410
dds3ProcessFunc_t gohCmb1UpdateProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  jmsSeqHandle_t *monitor;
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
  monitor = ProcessData[1].monitor;
  v6 = id;
  return jmsSeqChange(monitor, &ProcessData[2], 2, v6);
}

// 0x1bd1530
s32 gohCmb2Init(dds3ProcessID_t *PID) {
  dds3ProcessID_t *id;

  id = PID;
  g_count = 0;
  dds3GetProcessData(id);
  return 1;
}

// 0x1bd1610
s32 gohCmb2Destroy(dds3ProcessID_t *PID) {
  dds3ProcessID_t *id;

  id = PID;
  dds3GetProcessData(id);
  return 1;
}

// 0x1bd1690
dds3ProcessFunc_t gohCmb2CalcProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  gohResult_t *v5;
  u32 v6;
  char v7;
  jmsSeqHandle_t *monitor;
  dds3ProcessID_t *v9;
  dds3ProcessFunc_t v11;
  Il2CppObject *Instance;
  void *v16;
  s32 v17;
  void *klass;
  s32 v19;
  s64 m_Items;
  s64 v22;
  s32 v23;
  s16 v25;
  sdatUnitWork_t *v26;
  sdatUnitWork_t *v27;
  s32 v28;
  jmsSeqUnit_t *gohSeqUnit_local;
  void *v33;
  jmsSeqUnit_t *v35;
  void *v36;
  s64 v37;
  s32 devilid;
  Il2CppObject *v40;
  jmsSeqUnit_t *v43;
  sdatUnitWork_t *pDevil1;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  v5 = Allocate(gohResult_t);
  _ctor(v5, 0);
  if (LODWORD(ProcessData[13].klass) == 1)
    v6 = 4107;
  else
    v6 = 7;
  v7 = jmsChkCommonInput(v6);
  monitor = ProcessData[1].monitor;
  v9 = id;
  v11 = jmsSeqChange(monitor, &ProcessData[2], 0, v9);
  if (v11)
    return v11;
  if (gohStopStatusDraw(ProcessData, 0, 0) < 2)
    return v11;
  if (s_bDrawBack)
  {
    if (!s_bEndCmb)
    {
      Instance = _get_Instance();
      ChangeAnim(Instance[16].monitor, 0, 0);
    }
  }
  evtMoonEnableDraw();
  if ((v7 & 1) == 0)
    goto LABEL_60;
  v16 = ProcessData[13].monitor;
  if (v16)
  {
    v17 = ITEMIDX(v16);
    klass = ProcessData[14].klass;
    if (klass)
      goto LABEL_36;
  }
  else
  {
    v17 = -1;
    klass = ProcessData[14].klass;
    if (klass)
    {
LABEL_36:
      v19 = ITEMIDX(klass);
      goto LABEL_41;
    }
  }
  v19 = -1;
LABEL_41:
  m_Items = GBWK->player->stock_id;
  pDevil1 = *(sdatUnitWork_t *)(m_Items + 8 * v17);
  v22 = *(u64 *)(m_Items + 8 * v19);
  v23 = *(s16 *)(v22 + 22);
  if (!DlcDevilSelCheck(v23))
    return v11;
  LODWORD(ProcessData[27].klass) = pDevil1->uniq_code;
  HIDWORD(ProcessData[27].klass) = *(u32 *)(v22 + 280);
  if (*(u16 *)(*(u64 *)(*((u64 *)ProcessData[17].monitor + v17 + *(u64 *)(*((u64 *)ProcessData[17].monitor + 2) + 16) * v19 + 4) + 32) + 22) && v17 != v19 && *(s32 *)(*(u64 *)(v22 + 40) + 16) >= 1 && (*(u8 *)(v22 + 146) & 0x12) == 0)
  {
    resultCheck = 0;
    gohResultUnit(v5, ProcessData, pDevil1, v22);
    if (gohGift(v5, v5->Devil, pDevil1, v22))
    {
      HIWORD(ProcessData[11].monitor) = v5->m_iDevilNo;
      v25 = v5->m_iMesNo;
      LODWORD(ProcessData[12].klass) = *(u32 *)&v5->m_iItemNo;
      WORD1(ProcessData[36].klass) = v5->m_iDvlReport;
    }
    else
    {
      v25 = 0;
    }
    WORD2(ProcessData[11].monitor) = v25;
    v26 = Allocate(sdatUnitWork_t);
    _ctor(v26, 0);
    ProcessData[36].monitor = v26;
    v27 = Allocate(sdatUnitWork_t);
    _ctor(v27, 0);
    ProcessData[37].klass = v27;
    ClassCopy(ProcessData[36].monitor, pDevil1, 0);
    ClassCopy(ProcessData[37].klass, v22, 0);
    ClassCopy(ProcessData[16].monitor, v5->Devil, 0);
    v28 = v5->m_iType;
    LODWORD(ProcessData[27].monitor) = 0;
    HIDWORD(ProcessData[11].klass) = 2;
    LODWORD(ProcessData[11].monitor) = v28;
    gohSeqUnit_local = gohSeqUnit;
    jmsSeqJumpAndFree(&ProcessData[2], &gohSeqUnit_local[12]);
    SE(0);
  }
LABEL_60:
  if ((v7 & 2) != 0)
  {
    v35 = gohSeqUnit;
    jmsSeqJumpAndFree(&ProcessData[2], &v35[3]);
    SE(1);
    if (!CHECK_TRIG(42766, 1))
    {
LABEL_62:
      if (!CHECK_TRIG(46083, 1))
        goto LABEL_63;
      goto LABEL_72;
    }
  }
  else if (!CHECK_TRIG(42766, 1))
  {
    goto LABEL_62;
  }
  LODWORD(ProcessData[1].klass) ^= 0x80000u;
  SE(0);
  if (!CHECK_TRIG(46083, 1))
  {
LABEL_63:
    v33 = ProcessData[14].klass;
LABEL_65:
    gohSelectMenuUpdate(v33);
    return v11;
  }
LABEL_72:
  v36 = ProcessData[14].klass;
  if (v36)
  {
    v37 = ITEMIDX(v36);
    goto LABEL_77;
  }
  v37 = -1;
LABEL_77:
  devilid = GBWK->player->stock_id[v37]->devilid;
  if (DlcDevilSelCheck(devilid))
  {
    v40 = _get_Instance();
    (*(*(u64 *)v40[10].monitor + 536))(v40[10].monitor, 0, *(u64 *)(*(u64 *)v40[10].monitor + 544));
    resultCheck = 0;
    HIDWORD(ProcessData[11].klass) = 1;
    v43 = gohSeqUnit;
    jmsSeqJumpAndFree(&ProcessData[2], &v43[12]);
    SE(0);
    v33 = ProcessData[14].klass;
    goto LABEL_65;
  }
  return v11;
}

// 0x1bd1e90
dds3ProcessFunc_t gohCmb2DrawProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  s32 klass;
  f32 v9;
  void *v11;
  void *v12;
  s32 Index;
  s32 v14;
  s32 v15;
  s32 devilid;
  bool v18;
  Il2CppObject *Instance;
  s32 v22;
  Il2CppObject *v23;
  void *v24;
  jmsSeqHandle_t *monitor;
  jmsSeqUnit_t *v26;
  dds3ProcessID_t *v27;
  dds3ProcessFunc_t result;
  Il2CppObject *v29;
  Il2CppObject *v30;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  klass = ProcessData[1].klass;
  if ((klass & 0x40000) == 0)
    return 0;
  gohModel(ProcessData);
  if (g_count > 5)
  {
    v9 = 1.0;
    goto LABEL_24;
  }
  g_count = g_count + 1;
  v9 = (f32)g_count / 5.0;
LABEL_24:
  gohCaption(0, 0, 1, (klass & 0x80000) == 0);
  gohSelDevilName(0, 0, 0, v9, ProcessData);
  v11 = LISTTOP(ProcessData[14].klass);
  v12 = CURRENT(ProcessData[14].klass);
  Index = v11->Index;
  v14 = v12->Index;
  v15 = ITEMIDX(ProcessData[13].monitor);
  gohCombineListFrameB(0, v15, Index, v14, ProcessData);
  if (LODWORD(ProcessData[13].klass) == 1)
  {
    devilid = GBWK->player->stock_id[v14]->devilid;
    v18 = DlcDevilSelCheck(devilid);
    if ((BYTE2(ProcessData[1].klass) & 8) == 0)
    {
      Instance = _get_Instance();
      CombineHelpActive(Instance[19].klass, 0, 0);
      if (v18)
        v22 = 10;
      else
        v22 = 4;
      goto LABEL_46;
    }
    gohCombineIconHelp();
    v23 = _get_Instance();
    CombineHelpActive(v23[19].klass, 1, 0);
    v24 = *((void *)_get_Instance()[18].monitor + 2);
    if (get_activeSelf(v24, 0))
      SetActive(v24, 0, 0);
    if (v18)
      v22 = 11;
    else
      v22 = 5;
LABEL_46:
    gohSetDispButtonGuide(v22, 0, 1);
  }
  monitor = ProcessData[1].monitor;
  v26 = &ProcessData[2];
  v27 = id;
  result = jmsSeqChange(monitor, v26, 1, v27);
  if (!result)
  {
    v29 = _get_Instance();
    ResultSetActive(v29[19].klass, 1, 0);
    v30 = _get_Instance();
    CombinationListActive(v30[19].klass, 0, 0);
    return 0;
  }
  return result;
}

// 0x1bd2340
dds3ProcessFunc_t gohCmb2UpdateProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  jmsSeqHandle_t *monitor;
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
  monitor = ProcessData[1].monitor;
  v6 = id;
  return jmsSeqChange(monitor, &ProcessData[2], 2, v6);
}

// 0x1bd2460
s32 gohSwordInit(dds3ProcessID_t *PID) {
  return 1;
}

// 0x1bd2470
s32 gohSwordDestroy(dds3ProcessID_t *PID) {
  return 1;
}

// 0x1bd2480
dds3ProcessFunc_t gohSwordCalcProcess(dds3ProcessID_t *PID) {
  return 0;
}

// 0x1bd2490
dds3ProcessFunc_t gohSwordDrawProcess(dds3ProcessID_t *PID) {
  return 0;
}

// 0x1bd24a0
dds3ProcessFunc_t gohSwordUpdateProcess(dds3ProcessID_t *PID) {
  return 0;
}

// 0x1bd24b0
s32 gohSword2Init(dds3ProcessID_t *PID) {
  return 1;
}

// 0x1bd24c0
s32 gohSword2Destroy(dds3ProcessID_t *PID) {
  return 1;
}

// 0x1bd24d0
dds3ProcessFunc_t gohSword2CalcProcess(dds3ProcessID_t *PID) {
  return 0;
}

// 0x1bd24e0
dds3ProcessFunc_t gohSword2DrawProcess(dds3ProcessID_t *PID) {
  return 0;
}

// 0x1bd24f0
dds3ProcessFunc_t gohSword2UpdateProcess(dds3ProcessID_t *PID) {
  return 0;
}

// 0x1bd2500
s32 gohSwordTreeInit(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  bool v7;
  Il2CppClass *klass;
  u32 Count;
  void *monitor;
  u32 v12;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  fclEndMessageEx(2);
  BYTE1(ProcessData[33].monitor) = 1;
  if (!s_bDrawBack)
  {
    gohCallDrawBack();
    s_bDrawBack = 1;
  }
  LOBYTE(ProcessData[33].klass) = 0;
  HIDWORD(ProcessData[33].klass) = 0;
  s_bEndCmb = 0;
  v7 = evtBitCheck(2960);
  BYTE2(ProcessData[33].monitor) = v7;
  klass = ProcessData[32].klass;
  Count = datSpiritSkillGetCount(GBWK->player);
  (*(klass->_1.image + 49))(klass, Count, 4, *((u64 *)klass->_1.image + 50));
  monitor = ProcessData[32].monitor;
  v12 = datRaidouSkillGetCount(GBWK->player);
  (*(*(u64 *)monitor + 392))(monitor, v12, 4, *(u64 *)(*(u64 *)monitor + 400));
  return 1;
}

// 0x1bd2790
s32 gohSwordTreeDestroy(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  s64 v6;
  s64 naturalAligment;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (s_bDrawBack)
    goto LABEL_7;
LABEL_17:
  if (ProcessData->klass->_2.naturalAligment >= (u32)naturalAligment && (gohData_t *)ProcessData->klass->_2.typeHierarchy[naturalAligment - 1] == gohData_t)
  {
    goto LABEL_19;
  }
LABEL_22:
  if (!s_bDrawBack)
    goto LABEL_17;
LABEL_7:
  if (ProcessData)
  {
    if (ProcessData->klass->_2.naturalAligment < (u32)v6 || ProcessData->klass->_2.typeHierarchy[v6 - 1] != gohData_t)
    {
      goto LABEL_22;
    }
  }
  if (s_bEndCmb)
  {
    gohCallDrawBack();
    s_bEndCmb = 0;
    BYTE6(ProcessData[26].klass) = 0;
    return 1;
  }
LABEL_19:
  BYTE6(ProcessData[26].klass) = 0;
  return 1;
}

// 0x1bd2950
dds3ProcessFunc_t gohSwordTreeCalcProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  s32 *monitor;
  void *TypeList;
  s16 v7;
  jmsSeqUnit_t *v8;
  dds3ProcessFunc_t v10;
  Il2CppObject *v15;
  s32 v16;
  s32 ItmSwordNo;
  s16 v18;
  Il2CppObject *Item;
  s32 v20;
  s32 m_hojo;
  s32 v22;
  jmsSeqUnit_t *gohSeqUnit_local;
  jmsSeqUnit_t *v29;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
  monitor = ProcessData[31].monitor;
  TypeList = GetTypeList(ProcessData[17].klass->_1.parent, monitor[4], monitor[7], 0);
  v7 = jmsChkCommonInput(0x30Fu);
  v8 = &ProcessData[2];
  v10 = jmsSeqChange(ProcessData[1].monitor, &ProcessData[2], 0, id);
  if (!v10)
  {
    if (gohStopStatusDraw(ProcessData, 0, 0) < 2)
      return v10;
    if (!op_Equality(instance, 0, 0))
    {
      if (!dds3FadeCheck())
      {
        if (BYTE6(ProcessData[26].klass))
        {
          dds3FadeIn(0, 0, 0, 0xAu);
          BYTE6(ProcessData[26].klass) = 0;
          return v10;
        }
        if (s_bDrawBack)
        {
          if (!s_bEndCmb)
          {
            v15 = _get_Instance();
            ChangeAnim(v15[16].monitor, 0, 0);
          }
        }
        GohCsrUpdate(ProcessData);
        GohLrChangeUpdate(ProcessData);
        GohCreateCheckSword(ProcessData);
        if ((v7 & 2) != 0)
        {
          if (LOBYTE(ProcessData[33].monitor))
          {
            v22 = 1;
            LOWORD(ProcessData[33].monitor) = 256;
          }
          else
          {
            gohSeqUnit_local = gohSeqUnit;
            jmsSeqJumpAndFree(&ProcessData[2], &gohSeqUnit_local[1]);
            LODWORD(ProcessData[13].klass) = 0;
            HIDWORD(ProcessData[27].monitor) = 0;
            v22 = 1;
            s_bEndCmb = 1;
          }
          goto LABEL_67;
        }
        if (CHECK_TRIG(46083, 1) && !LOBYTE(ProcessData[33].monitor))
        {
          HIDWORD(ProcessData[11].klass) = 4;
          LOWORD(ProcessData[22].monitor) = GBWK->player->swordno;
          goto LABEL_62;
        }
        if ((v7 & 0x200) != 0)
        {
          GohTreeMenuTypeAdd(ProcessData);
          return v10;
        }
        if ((v7 & 0x100) != 0)
        {
          GohTreeMenuTypeSub(ProcessData);
          return v10;
        }
        if ((v7 & 1) != 0)
        {
          v16 = *((u32 *)ProcessData[31].monitor + 6);
          if (v16 != 145)
          {
            if (LOBYTE(ProcessData[33].klass))
            {
              ItmSwordNo = GetItmSwordNo(v16, 0);
              v18 = ItmSwordNo;
              gohOnSword(ItmSwordNo);
              Item = _get_Item(TypeList, monitor[5]);
              v20 = _get_Item(Item[1].monitor, 0);
              HIWORD(ProcessData[22].klass) = GetItmSwordNo(v20, 0);
              LOWORD(ProcessData[22].monitor) = v18;
              BYTE6(ProcessData[33].monitor) = gohCheckSwordHave(v18);
              m_hojo = tbl[SLOWORD(ProcessData[22].monitor)]->m_hojo;
              BYTE3(ProcessData[33].monitor) = RaidouSklCheck(m_hojo);
              HIDWORD(ProcessData[11].klass) = 5;
LABEL_62:
              v29 = gohSeqUnit;
              jmsSeqJumpAndFree(v8, &v29[12]);
              v22 = 0;
LABEL_67:
              SE(v22);
            }
          }
        }
      }
    }
  }
  return v10;
}

// 0x1bd2f10
dds3ProcessFunc_t gohSwordTreeDrawProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  dds3ProcessFunc_t v5;
  Il2CppObject *Instance;
  Il2CppObject *v7;
  void *monitor;
  char *LocalizeText;
  s32 klass_high;
  s32 v13;
  jmsSeqHandle_t *v14;
  dds3ProcessID_t *v15;
  Il2CppObject *v17;
  s32 v19;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  if ((BYTE2(ProcessData[1].klass) & 4) == 0)
    return 0;
  Instance = _get_Instance();
  v5 = 0;
  if (!AnimeEndCheck(Instance[18].klass, 0))
    return v5;
  v7 = _get_Instance();
  ArrTreeOnOff(v7[16].klass, 1, BYTE2(ProcessData[33].monitor), 0);
  gohModel(ProcessData);
  gohCaption(0, 0, 6, 1);
  monitor = _get_Instance()[17].monitor;
  LocalizeText = GetLocalizeText("GOH_CAPTION_L0006", 1);
  TitleDraw(monitor, 0, LocalizeText, 0);
  DrawTree(ProcessData);
  DrawSwordDetails(ProcessData);
  klass_high = HIDWORD(ProcessData[33].klass);
  if (klass_high == 2)
  {
    gohTreeSpiritDraw(ProcessData);
    goto LABEL_28;
  }
  if (klass_high != 1)
  {
    if (!klass_high)
    {
      gohTreeMaterialDraw(ProcessData);
      if (!LOBYTE(ProcessData[33].monitor))
        goto LABEL_43;
LABEL_29:
      v13 = 27;
      goto LABEL_31;
    }
LABEL_28:
    if (!LOBYTE(ProcessData[33].monitor))
      goto LABEL_43;
    goto LABEL_29;
  }
  gohTreeBattleDraw(ProcessData);
  if (LOBYTE(ProcessData[33].monitor))
    goto LABEL_29;
LABEL_43:
  v19 = HIDWORD(ProcessData[33].klass);
  if (!v19)
  {
    v13 = 28;
    goto LABEL_31;
  }
  if (v19 == 1)
  {
    v13 = 29;
    goto LABEL_31;
  }
  if (v19 != 2)
    goto LABEL_32;
  v13 = 30;
LABEL_31:
  gohSetDispButtonGuide(v13, 0, 0);
LABEL_32:
  v14 = ProcessData[1].monitor;
  v15 = id;
  v5 = jmsSeqChange(v14, &ProcessData[2], 1, v15);
  if (v5)
  {
    if (s_bEndCmb == 1)
    {
      v17 = _get_Instance();
      ArrTreeOnOff(v17[16].klass, 0, BYTE2(ProcessData[33].monitor), 0);
    }
  }
  return v5;
}

// 0x1bd32e0
dds3ProcessFunc_t gohSwordTreeUpdateProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  jmsSeqHandle_t *monitor;
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
  monitor = ProcessData[1].monitor;
  v6 = id;
  return jmsSeqChange(monitor, &ProcessData[2], 2, v6);
}

// 0x1bd3400
s32 gohStatInit(dds3ProcessID_t *PID) {
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
  HIDWORD(ProcessData[21].klass) = 0;
  cmpEquipSwordNoHelp(0);
  nativeSkillStep = 0;
  LODWORD(ProcessData[38].monitor) = 16;
  return 1;
}

// 0x1bd3570
s32 gohStatDestroy(dds3ProcessID_t *PID) {
  return 1;
}

// 0x1bd3580
dds3ProcessFunc_t gohStatCalcProcess(dds3ProcessID_t *PID) {
  gohData_t *ProcessData;
  char v5;
  jmsSeqUnit_t *p_pSeqUnit;
  dds3ProcessFunc_t v8;
  jmsSeqUnit_t *v10;
  jmsSeqUnit_t *v11;
  s32 m_eCombineType2;
  jmsSeqUnit_t *gohSeqUnit_local;
  s32 v15;
  jmsSeqUnit_t *v17;
  jmsSeqUnit_t *v20;
  s32 v23;
  s32 v27;
  jmsSeqUnit_t *v29;
  jmsSeqUnit_t *v31;
  s32 combStSeq;
  Il2CppObject *Instance;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  v5 = jmsChkCommonInput(3u);
  p_pSeqUnit = &ProcessData->pSeqUnit;
  v8 = jmsSeqChange(ProcessData->SeqHandle, &ProcessData->pSeqUnit, 0, id);
  if (!v8)
  {
    switch (ProcessData->m_iStatusType)
    {
      case 0:
        if ((v5 & 2) == 0)
          goto LABEL_83;
        if (cmpGetModeSq())
          goto LABEL_83;
        m_eCombineType2 = ProcessData->m_eCombineType2;
        if (m_eCombineType2 == 4)
          goto LABEL_108;
        if (m_eCombineType2 == 3)
          goto LABEL_40;
        gohSeqUnit_local = gohSeqUnit;
        v11 = &gohSeqUnit_local[3];
        goto LABEL_118;
      case 1:
        if ((v5 & 2) == 0)
          goto LABEL_83;
        if (cmpGetModeSq())
          goto LABEL_83;
        v15 = ProcessData->m_eCombineType2;
        if (v15 == 4)
          goto LABEL_108;
        if (v15 == 3)
          goto LABEL_40;
        goto LABEL_113;
      case 4:
        goto LABEL_14;
      case 5:
      case 6:
        if ((v5 & 1) == 0)
        {
LABEL_14:
          if ((v5 & 2) != 0)
          {
            if (!cmpGetModeSq())
            {
              v10 = gohSeqUnit;
              v11 = &v10[11];
              goto LABEL_118;
            }
          }
          goto LABEL_83;
        }
        if (cmpGetModeSq() == 2)
          return v8;
        goto LABEL_62;
      default:
        if (CHECK_TRIG(42752, 1) && !CHECK_PRESS(42756, 1) && !CHECK_PRESS(42757, 1))
        {
          if (GohNaitiveSklMove(ProcessData))
          {
            ProcessData->noPartVoice = 1;
            gohReturnBarthDevil(ProcessData);
            if (!gohCheckDevilError(ProcessData))
            {
              SE(0);
              cmpSklTypeSet(0, 1);
              ProcessData->combStSeq = 1;
            }
            return v8;
          }
        }
        if ((v5 & 1) == 0 || CHECK_PRESS(42756, 1) || CHECK_PRESS(42757, 1))
        {
          goto LABEL_77;
        }
        if (GohNaitiveSklMove(ProcessData))
          goto LABEL_77;
        if (resultCheck)
          goto LABEL_77;
        if (cmpGetModeSq())
          goto LABEL_77;
        combStSeq = ProcessData->combStSeq;
        if (combStSeq)
        {
          if (combStSeq == 2)
          {
LABEL_122:
            ProcessData->noPartVoice = 1;
LABEL_62:
            gohReturnBarthDevil(ProcessData);
            v20 = gohSeqUnit;
            jmsSeqJumpAndFree(p_pSeqUnit, &v20[13]);
            return v8;
          }
          goto LABEL_77;
        }
        if (!GohNaitiveSklSetting(ProcessData))
          goto LABEL_135;
        if (!gohGetErrorType(ProcessData) && ProcessData->combStSeq == 2)
        {
          goto LABEL_133;
        }
        else
        {
LABEL_135:
          ProcessData->noPartVoice = 1;
LABEL_133:
          gohReturnBarthDevil(ProcessData);
          if (gohCheckDevilError(ProcessData))
            return v8;
          goto LABEL_137;
        }
        gohReturnBarthDevil(ProcessData);
        if (gohCheckDevilError(ProcessData))
          return v8;
LABEL_137:
        if (!GohNaitiveSklSetting(ProcessData))
        {
          ProcessData->combStSeq = 2;
          goto LABEL_122;
        }
        if (ProcessData->combStSeq == 2)
          goto LABEL_122;
LABEL_77:
        if ((v5 & 2) == 0)
          goto LABEL_83;
        if (cmpGetModeSq() || CHECK_PRESS(42756, 1) || CHECK_PRESS(42757, 1))
        {
LABEL_83:
          gohStartBirthDevilStatus(ProcessData);
          return v8;
        }
        v23 = ProcessData->combStSeq;
        if (v23 == 1)
        {
          if (nativeSkillStep != 3)
          {
            if (!setNativeSkillEndCnt)
            {
              Instance = _get_Instance();
              (*(*(u64 *)Instance[10].monitor + 536))(Instance[10].monitor, 0, *(u64 *)(*(u64 *)Instance[10].monitor + 544));
              ProcessData->combStSeq = 0;
LABEL_119:
              SE(1);
              return v8;
            }
          }
          v23 = ProcessData->combStSeq;
        }
        if (v23)
        {
          if (!resultCheck)
          {
            if ((u32)(ProcessData->DevilStatusFlag - 1) <= 1)
            {
              gohReturnBarthDevil(ProcessData);
            }
            GohReturnNativeSklSet(ProcessData);
            GohInitSkillChange(ProcessData, 0);
          }
        }
        else
        {
          v27 = ProcessData->m_eCombineType2;
          if (v27 == 3)
          {
LABEL_40:
            v17 = gohSeqUnit;
            v11 = &v17[7];
          }
          else if (v27 == 4)
          {
LABEL_108:
            v29 = gohSeqUnit;
            v11 = &v29[8];
          }
          else
          {
LABEL_113:
            v31 = gohSeqUnit;
            v11 = &v31[4];
          }
LABEL_118:
          jmsSeqJumpAndFree(p_pSeqUnit, v11);
        }
        goto LABEL_119;
    }
  }
  return v8;
}

// 0x1bd5000
dds3ProcessFunc_t gohStatDrawProcess(dds3ProcessID_t *PID) {
  gohData_t *ProcessData;
  jmsSeqHandle_t *SeqHandle;
  dds3ProcessID_t *v6;
  dds3ProcessFunc_t result;
  sdatUnitWork_t *BirthDevil;
  s32 m_iStatusType;
  s32 v11;
  bool v12;
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
  v6 = id;
  result = jmsSeqChange(SeqHandle, &ProcessData->pSeqUnit, 1, v6);
  if (!result)
  {
    if (ProcessData->combStSeq == 1)
    {
      BirthDevil = ProcessData->BirthDevil;
      gohNativeSkillListDraw(BirthDevil);
    }
    m_iStatusType = ProcessData->m_iStatusType;
    if (m_iStatusType == 4)
    {
      v11 = 33;
LABEL_20:
      gohSetDispButtonGuide(v11, 1, 0);
      return 0;
    }
    if ((u32)(m_iStatusType - 5) <= 1)
    {
      v12 = cmpGetModeSq() == 2;
      if (v12)
      {
        v11 = 31;
      }
      else
      {
        v11 = 32;
      }
      goto LABEL_20;
    }
    CombGuideDraw(ProcessData);
    return 0;
  }
  return result;
}

// 0x1bd5290
dds3ProcessFunc_t gohStatUpdateProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  jmsSeqHandle_t *monitor;
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
  monitor = ProcessData[1].monitor;
  v6 = id;
  return jmsSeqChange(monitor, &ProcessData[2], 2, v6);
}

// 0x1bd3da0
void gohReturnBarthDevil(gohData_t *pData) {
  s32 Flag;

  Flag = pData->Flag;
  pData->DevilStatusFlag = 0;
  pData->Flag = Flag & 0xFFFEFFFF;
  gohStartBirthDevilStatus(pData);
}

// 0x1bd53b0
void gohStartConfirmMes(gohData_t *pData) {
  Il2CppObject *v3;
  char *v4;
  char *v5;
  s32 data;

  if (pData->BirthDevil->restoreMoney && pData->m_eCombineType2 == 4)
  {
    data = pData->BirthDevil->restoreMoney;
    v3 = Box(s32, &data);
    v4 = Format("{0}", v3, 0);
    v5 = itfConvertToDelimitedNum(v4);
    fclSetMessageVar(0, v5);
    fclStart2(17, 0, 1);
    SetMessagePos(0);
    fclSetSelMes(g_mainPID, 40);
  }
  else
  {
    fclStart2(1, 0, 1);
    SetMessagePos(0);
    fclSetSelMes(g_mainPID, 2);
  }
  fclSetSelCancelPos(1);
  pData->WorkStat = 101;
}

// 0x1bd5570
s32 gohConfirmInit(dds3ProcessID_t *PID) {
  gohData_t *ProcessData;
  s32 m_eCombineType;
  u8 *m_pScrData;
  dds3ProcessID_t *started;
  dds3ProcessID_t *p_m_ScrPID;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  m_eCombineType = ProcessData->m_eCombineType;
  ProcessData->WorkStat = 0;
  if (m_eCombineType == 2)
  {
    cmpEquipSwordNoHelp(1);
    m_pScrData = ProcessData->m_pScrData;
    started = scrStartScript2(1, m_pScrData, 5, 1);
    ProcessData->m_ScrPID = started;
    p_m_ScrPID = &ProcessData->m_ScrPID;
    *((u8 *)p_m_ScrPID + 221) = 0;
    return 1;
  }
  if (ProcessData->m_eResultType != 5)
    goto LABEL_18;
  if (evtMoonGetAge() == 8)
  {
LABEL_18:
    gohStartConfirmMes(ProcessData);
    return 1;
  }
  fclSetMessageInvalid(1);
  fclStart1(43, 0);
  ProcessData->WorkStat = 100;
  return 1;
}

// 0x1bd57d0
s32 gohConfirmDestroy(dds3ProcessID_t *PID) {
  return 1;
}

// 0x1bd57e0
dds3ProcessFunc_t gohConfirmCalcProcess(dds3ProcessID_t *PID) {
  gohData_t *ProcessData;
  jmsSeqUnit_t *p_pSeqUnit;
  jmsSeqHandle_t *SeqHandle;
  dds3ProcessID_t *v7;
  dds3ProcessFunc_t v8;
  dds3ProcessID_t *m_ScrPID;
  s32 WorkStat;
  s32 v13;
  jmsSeqUnit_t *gohSeqUnit_local;
  dds3ProcessID_t *ID;
  dds3ProcessID_t *id;

  ID = PID;
  ProcessData = dds3GetProcessData(ID);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  p_pSeqUnit = &ProcessData->pSeqUnit;
  SeqHandle = ProcessData->SeqHandle;
  v7 = ID;
  v8 = jmsSeqChange(SeqHandle, &ProcessData->pSeqUnit, 0, v7);
  if (!v8)
  {
    m_ScrPID = ProcessData->m_ScrPID;
    if (!m_ScrPID)
    {
      if (fclChkMessage())
        return v8;
      WorkStat = ProcessData->WorkStat;
      if (WorkStat == 100)
      {
        if (!Update())
        {
          gohStartConfirmMes(ProcessData);
        }
        return v8;
      }
      if (WorkStat != 101)
        return v8;
      v13 = Update();
      if (v13 != 1)
      {
        if (v13)
          return v8;
        goto LABEL_37;
      }
      goto LABEL_42;
    }
    id = ProcessData->m_ScrPID;
    if (dds3GetProcessStat(id) != 3)
    {
      if (dds3GetProcessStat(id))
        return v8;
    }
    ProcessData->m_ScrPID = 0;
    if (ProcessData->m_bCompsitionFlag)
    {
LABEL_37:
      gohSeqUnit_local = gohSeqUnit;
      jmsSeqJumpAndFree(p_pSeqUnit, &gohSeqUnit_local[14]);
      return v8;
    }
LABEL_42:
    gohSeqReturn(ProcessData);
  }
  return v8;
}

// 0x1bd5d60
dds3ProcessFunc_t gohConfirmDrawProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  jmsSeqHandle_t *monitor;
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
  monitor = ProcessData[1].monitor;
  v6 = id;
  return jmsSeqChange(monitor, &ProcessData[2], 1, v6);
}

// 0x1bd5e80
dds3ProcessFunc_t gohConfirmUpdateProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  jmsSeqHandle_t *monitor;
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
  monitor = ProcessData[1].monitor;
  v6 = id;
  return jmsSeqChange(monitor, &ProcessData[2], 2, v6);
}

// 0x1bd5fa0
s32 gohCyuuseiInit(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  void *monitor;
  s32 klass;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  monitor = ProcessData[13].monitor;
  if (monitor)
    ITEMIDX(monitor);
  klass = ProcessData[13].klass;
  HIDWORD(ProcessData[20].monitor) = 0;
  BYTE2(ProcessData[20].monitor) = 2 * (klass != 2);
  return 1;
}

// 0x1bd6100
s32 gohCyuuseiDestroy(dds3ProcessID_t *PID) {
  return 1;
}

// 0x1bd6110
dds3ProcessFunc_t gohCyuuseiCalcProcess(dds3ProcessID_t *PID) {
  gohData_t *ProcessData;
  jmsSeqHandle_t *SeqHandle;
  dds3ProcessID_t *v6;
  dds3ProcessFunc_t v10;
  dds3ProcessFunc_t result;
  sdatUnitWork_t *p_combiDevil1;
  void *m_pDevSelList1;
  s32 v16;
  u32 CyuuseiError;
  sdatUnitWork_t *combiDevil2;
  sdatUnitWork_t *v20;
  s8 v21;
  void *m_pDevSelList2;
  s32 v23;
  s32 WorkStat;
  s32 devilid;
  char *v27;
  s32 v28;
  Il2CppObject *v30;
  s32 v32;
  s32 v33;
  s32 v34;
  char *v35;
  s32 *p_WorkStat;
  s32 v38;
  char *v39;
  s32 v40;
  s32 v41;
  char *v42;
  s32 v43;
  s32 v45;
  gohData_t *v47;
  sdatUnitWork_t *v48;
  s32 v49;
  bool v50;
  s32 v52;
  s32 v53;
  char *v54;
  s32 WorkstatCnt;
  s32 v56;
  s32 v58;
  s32 v60;
  s32 v61;
  char *v62;
  s32 v64;
  Il2CppObject *Instance;
  dds3ProcessID_t *v66;
  s32 v67;
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
  v6 = id;
  v10 = jmsSeqChange(SeqHandle, &ProcessData->pSeqUnit, 0, v6);
  if (v10)
    return v10;
  if (ProcessData->m_eCombineType != 2)
  {
    if (ProcessData->m_eCombineType2 == 4)
    {
      p_combiDevil1 = &ProcessData->combiDevil1;
LABEL_27:
      CyuuseiError = ProcessData->CyuuseiError;
      combiDevil2 = 0;
      v20 = p_combiDevil1;
      v21 = ProcessData->CyuuseiError;
      if (CyuuseiError > 5 || ((1 << CyuuseiError) & 0x36) == 0)
      {
LABEL_37:
        switch (v21)
        {
          case 0:
            WorkStat = ProcessData->WorkStat;
            if (WorkStat == 1)
              goto LABEL_83;
            if (WorkStat)
              return v10;
            devilid = v20->devilid;
            v27 = sdatDevilName(devilid, 0);
            fclSetMessageVar(0, v27);
            v28 = ProcessData->m_aiGoodbyMesNo[0];
            goto LABEL_110;
          case 1:
            v33 = ProcessData->WorkStat;
            if (v33 != 1)
            {
              if (v33)
                return v10;
              v34 = combiDevil2->devilid;
              v35 = sdatDevilName(v34, 0);
              fclSetMessageVar(0, v35);
              v28 = ProcessData->m_aiGoodbyMesNo[1];
LABEL_110:
              fclStartMessage(v28);
LABEL_111:
              v43 = ProcessData->WorkStat;
LABEL_112:
              v32 = v43 + 1;
              goto LABEL_113;
            }
LABEL_83:
            if (fclChkMessage())
              return v10;
            goto LABEL_57;
          case 2:
            p_WorkStat = &ProcessData->WorkStat;
            switch (ProcessData->WorkStat)
            {
              case 0:
                dds3FadeOut(0, 0, 0, 0xAu);
                goto LABEL_175;
              case 1:
                if (dds3FadeCheck())
                  return v10;
                if (cfgGetConfigGAME(14, 0) != 1)
                  goto LABEL_175;
                if (gohStopStatusDraw(ProcessData, 0, 0) < 2)
                  return v10;
                v45 = 13;
                goto LABEL_182;
              case 2:
                ProcessData->Flag &= ~0x10000u;
                cmpSetGoodByMode(1);
                v47 = ProcessData;
                v48 = v20;
                goto LABEL_153;
              case 3:
                v49 = ProcessData->WorkstatCnt + 1;
                v50 = ProcessData->WorkstatCnt - 40 < 0;
                ProcessData->WorkstatCnt = v49;
                if (v50 != __OFSUB__(v49, 41))
                  return v10;
                v45 = 4;
                goto LABEL_182;
              case 4:
                if (!cmpCheckStepGoodbyMessage())
                  return v10;
                v52 = v20->devilid;
                gohGoodbyPartVoicePlay(v52);
                v53 = v20->devilid;
                v54 = sdatDevilName(v53, 0);
                fclSetMessageVar(0, v54);
                fclStart1(ProcessData->m_aiGoodbyMesNo[0], 1);
                fclSkipNoEnd(g_mainPID, 1);
                goto LABEL_154;
              case 5:
                WorkstatCnt = ProcessData->WorkstatCnt;
                if (WorkstatCnt)
                {
                  v56 = WorkstatCnt + 1;
                  ProcessData->WorkstatCnt = v56;
                  if (v56 < 30)
                    return v10;
                }
                else
                {
                  if (Update())
                    return v10;
                  v67 = ProcessData->WorkstatCnt + 1;
                  v50 = ProcessData->WorkstatCnt - 29 < 0;
                  ProcessData->WorkstatCnt = v67;
                  if (v50 != __OFSUB__(v67, 30))
                    return v10;
                }
                End();
LABEL_175:
                v45 = *p_WorkStat + 1;
LABEL_182:
                *p_WorkStat = v45;
                result = 0;
                break;
              case 6:
                if (gohStopStatusDraw(ProcessData, 0, 1) < 2)
                  return v10;
                goto LABEL_175;
              case 7:
                ProcessData->Flag &= ~0x10000u;
                v47 = ProcessData;
                v48 = combiDevil2;
LABEL_153:
                gohStartStatusDraw(v47, v48, 0x40000000, 0);
LABEL_154:
                v43 = ProcessData->WorkStat;
                ProcessData->WorkstatCnt = 0;
                goto LABEL_112;
              case 8:
                v58 = ProcessData->WorkstatCnt + 1;
                v50 = ProcessData->WorkstatCnt - 40 < 0;
                ProcessData->WorkstatCnt = v58;
                if (v50 != __OFSUB__(v58, 41))
                  return v10;
                v45 = 9;
                goto LABEL_182;
              case 9:
                if (!cmpCheckStepGoodbyMessage())
                  return v10;
                v60 = combiDevil2->devilid;
                gohGoodbyPartVoicePlay(v60);
                v61 = combiDevil2->devilid;
                v62 = sdatDevilName(v61, 0);
                fclSetMessageVar(0, v62);
                fclStart1(ProcessData->m_aiGoodbyMesNo[1], 1);
                goto LABEL_111;
              case 0xA:
                if (Update())
                  return v10;
                goto LABEL_175;
              case 0xB:
                if (gohStopStatusDraw(ProcessData, 0, 0) < 2)
                  return v10;
                scrEventSkipEnd(0, g_mainPID);
                goto LABEL_175;
              case 0xC:
                v64 = ProcessData->WorkstatCnt + 1;
                v50 = ProcessData->WorkstatCnt - 30 < 0;
                ProcessData->WorkstatCnt = v64;
                if (v50 != __OFSUB__(v64, 31))
                  return v10;
                *(u64 *)p_WorkStat = 13;
                return 0;
              case 0xD:
                *p_WorkStat = 14;
                cmpSetGoodByMode(0);
                return 0;
              case 0xE:
                v45 = 15;
                goto LABEL_182;
              case 0xF:
                gohCyuuseiCombLastCalc(ProcessData);
                Instance = _get_Instance();
                CombineProductUiOff(Instance, 0);
                v66 = g_mainPID;
                scrEventSkipEnd(0, v66);
                scrLogEnd(g_mainPID);
                fclSkipNoEnd(g_mainPID, 0);
                return 0;
              default:
                return v10;
            }
            return result;
          case 3:
            switch (ProcessData->WorkStat)
            {
              case 0:
                goto LABEL_97;
              case 1:
                goto LABEL_79;
              case 2:
                goto LABEL_88;
              case 3:
                goto LABEL_91;
              default:
                return v10;
            }
          case 4:
            switch (ProcessData->WorkStat)
            {
              case 0:
                goto LABEL_102;
              case 1:
                goto LABEL_79;
              case 2:
                goto LABEL_88;
              case 3:
                goto LABEL_91;
              default:
                return v10;
            }
          case 5:
            switch (ProcessData->WorkStat)
            {
              case 0:
LABEL_97:
                v38 = v20->devilid;
                v39 = sdatDevilName(v38, 0);
                fclSetMessageVar(0, v39);
                v40 = v20->devilid;
                goto LABEL_107;
              case 1:
              case 3:
LABEL_79:
                if (!fclChkMessage())
                  goto LABEL_111;
                return v10;
              case 2:
LABEL_102:
                v41 = combiDevil2->devilid;
                v42 = sdatDevilName(v41, 0);
                fclSetMessageVar(0, v42);
                v40 = combiDevil2->devilid;
LABEL_107:
                v28 = 7 * sBtlGetDevilData(v40, -1)->kucyo + 44;
                goto LABEL_110;
              case 4:
LABEL_88:
                v28 = 5;
                goto LABEL_110;
              case 5:
LABEL_91:
                if (fclChkMessage())
                  return v10;
                gohSeqReturn(ProcessData);
                return 0;
              default:
                return v10;
            }
          default:
            return v10;
        }
        goto LABEL_56;
      }
      if (ProcessData->m_eCombineType2 == 4)
      {
        combiDevil2 = ProcessData->combiDevil2;
        goto LABEL_37;
      }
      m_pDevSelList2 = ProcessData->m_pDevSelList2;
      if (m_pDevSelList2)
      {
        v23 = ITEMIDX(m_pDevSelList2);
LABEL_36:
        combiDevil2 = GBWK->player->stock_id[v23];
        v21 = ProcessData->CyuuseiError;
        goto LABEL_37;
      }
      else
      {
        v23 = -1;
        goto LABEL_36;
      }
      goto LABEL_36;
    }
    m_pDevSelList1 = ProcessData->m_pDevSelList1;
    if (m_pDevSelList1)
    {
      v16 = ITEMIDX(m_pDevSelList1);
LABEL_26:
      p_combiDevil1 = &GBWK->player->stock_id[v16];
      goto LABEL_27;
    }
    else
    {
      v16 = -1;
      goto LABEL_26;
    }
    goto LABEL_26;
  }
  if (cfgGetConfigGAME(15, 0) == 1)
  {
    if (ProcessData->haveSword && ProcessData->m_eCombineType == 2)
      goto LABEL_55;
  }
  if (ProcessData->WorkStat)
  {
    if (dds3FadeCheck())
      return v10;
    v30 = _get_Instance();
    CombineProductUiOff(v30, 0);
LABEL_55:
LABEL_57:
    gohCyuuseiCombLastCalc(ProcessData);
    return 0;
LABEL_56:
    goto LABEL_57;
  }
  dds3FadeOut(0, 0, 0, 0xFu);
  v32 = 1;
LABEL_113:
  ProcessData->WorkStat = v32;
  return 0;
}

// 0x1bd78c0
dds3ProcessFunc_t gohCyuuseiDrawProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  jmsSeqHandle_t *monitor;
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
  monitor = ProcessData[1].monitor;
  v6 = id;
  return jmsSeqChange(monitor, &ProcessData[2], 1, v6);
}

// 0x1bd79e0
dds3ProcessFunc_t gohCyuuseiUpdateProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  jmsSeqHandle_t *monitor;
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
  fclUpdateMessage();
  monitor = ProcessData[1].monitor;
  v6 = id;
  return jmsSeqChange(monitor, &ProcessData[2], 2, v6);
}

// 0x1bd7740
void gohGoodbyPartVoicePlay(s32 _devilID) {
  s32 v5;
  u32 DevilSE;

  if (scrIsEventSkip(g_mainPID))
    return;
  if (devilID == 382 || devilID == 11)
  {
    if (cfgGetConfigAUDIO(6, 0))
      v5 = 4;
    else
      v5 = 14;
    goto LABEL_16;
  }
  else
  {
    v5 = 14;
    goto LABEL_16;
  }
LABEL_16:
  DevilSE = GetDevilSE(devilID, v5);
  sBtlStopSE(DevilSE);
  sBtlPlaySESub(DevilSE, 127);
  return;
}

// 0x1bd7b40
s32 gohAccidentInit(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  u8 *klass;
  dds3ProcessID_t *started;
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
  started = scrStartScript2(1, klass, 0, 1);
  ProcessData[8].monitor = started;
  gohCallDrawBack();
  return 1;
}

// 0x1bd7ca0
s32 gohAccidentDestroy(dds3ProcessID_t *PID) {
  return 1;
}

// 0x1bd7cb0
dds3ProcessFunc_t gohAccidentCalcProcess(dds3ProcessID_t *PID) {
  gohData_t *ProcessData;
  jmsSeqHandle_t *SeqHandle;
  dds3ProcessID_t *v6;
  dds3ProcessFunc_t v8;
  dds3ProcessID_t *m_ScrPID;
  dds3ProcessID_t *ID;
  dds3ProcessID_t *id;

  ID = PID;
  ProcessData = dds3GetProcessData(ID);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  SeqHandle = ProcessData->SeqHandle;
  v6 = ID;
  v8 = jmsSeqChange(SeqHandle, &ProcessData->pSeqUnit, 0, v6);
  if (v8)
    return v8;
  if (gohStopStatusDraw(ProcessData, 0, 0) < 2)
    return v8;
  evtMoonEnableDraw();
  m_ScrPID = ProcessData->m_ScrPID;
  if (!m_ScrPID)
  {
    gohCyuuseiStartDirection(ProcessData);
    return v8;
  }
  id = ProcessData->m_ScrPID;
  if (dds3GetProcessStat(id) == 3)
  {
LABEL_33:
    ProcessData->m_ScrPID = 0;
    if (gohGetKindNo())
    {
      gohAccidentDevil(ProcessData);
    }
    return v8;
  }
  if (!dds3GetProcessStat(id))
    goto LABEL_33;
  return v8;
}

// 0x1bd81d0
dds3ProcessFunc_t gohAccidentDrawProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  jmsSeqHandle_t *monitor;
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
  monitor = ProcessData[1].monitor;
  v6 = id;
  return jmsSeqChange(monitor, &ProcessData[2], 1, v6);
}

// 0x1bd82f0
dds3ProcessFunc_t gohAccidentUpdateProcess(dds3ProcessID_t *PID) {
  gohData_t *ProcessData;
  jmsSeqHandle_t *SeqHandle;
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
  gohModel(ProcessData);
  SeqHandle = ProcessData->SeqHandle;
  v6 = id;
  return jmsSeqChange(SeqHandle, &ProcessData->pSeqUnit, 2, v6);
}

// 0x1bd8450
s32 gohRecoverInit(dds3ProcessID_t *PID) {
  fclEndMessageEx(2);
  gohCallDrawBack();
  return 1;
}

// 0x1bd8520
s32 gohRecoverDestroy(dds3ProcessID_t *PID) {
  gohCallDrawBack();
  return 1;
}

// 0x1bd85a0
dds3ProcessFunc_t gohRecoverCalcProcess(dds3ProcessID_t *PID) {
  gohData_t *ProcessData;
  char v5;
  dds3ProcessFunc_t v7;
  s32 v8;
  jmsSeqUnit_t *gohSeqUnit_local;
  jmsSeqUnit_t *v12;
  void *m_pSelList;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  v5 = jmsChkCommonInput(3u);
  v7 = jmsSeqChange(ProcessData->SeqHandle, &ProcessData->pSeqUnit, 0, id);
  if (v7)
    return v7;
  if ((v5 & 1) != 0)
  {
    v8 = gohRecoverExec(ProcessData);
    if (v8 != -1)
    {
      if (!v8)
      {
        gohSeqUnit_local = gohSeqUnit;
        jmsSeqJumpAndFree(&ProcessData->pSeqUnit, &gohSeqUnit_local[1]);
      }
      SE(20);
    }
  }
  if ((v5 & 2) != 0)
  {
    v12 = gohSeqUnit;
    jmsSeqJumpAndFree(&ProcessData->pSeqUnit, &v12[1]);
    SE(1);
    goto LABEL_27;
  }
LABEL_27:
  m_pSelList = ProcessData->m_pSelList;
  gohSelectMenuUpdate(m_pSelList);
  if (CHECK_REP(43527, 1))
  {
    if (!CmdListItemMoveNextPage(ProcessData->m_pSelList->pCmdList))
      return v7;
    goto LABEL_34;
  }
  if (CHECK_REP(43526, 1) && CmdListItemMovePrevPage(ProcessData->m_pSelList->pCmdList))
  {
LABEL_34:
    SE(3);
  }
  return v7;
}

// 0x1bd8a50
dds3ProcessFunc_t gohRecoverDrawProcess(dds3ProcessID_t *PID) {
  gohData_t *ProcessData;
  void *v5;
  void *v6;
  void *v7;
  void *v8;
  s32 v10;
  s32 Index;
  s32 v12;
  gohGeneralList_t *GeneralList;
  jmsSeqHandle_t *SeqHandle;
  jmsSeqUnit_t *p_pSeqUnit;
  dds3ProcessID_t *v17;
  dds3ProcessFunc_t v18;
  void *v19;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  v5 = HEAD(ProcessData->m_pSelList);
  v6 = TAIL(ProcessData->m_pSelList);
  v7 = LISTTOP(ProcessData->m_pSelList);
  v8 = CURRENT(ProcessData->m_pSelList);
  gohModel(ProcessData);
  if (v5)
  {
    v10 = v6->Index - v5->Index;
    Index = v7->Index;
    v12 = v8->Index;
    if (v10 + 1 < 10)
      LODWORD(v5) = v10 + 1;
    else
      LODWORD(v5) = 10;
    goto LABEL_16;
  }
  v12 = 0;
  Index = 0;
LABEL_16:
  gohSetDispButtonGuide(36, 0, 0);
  GeneralList = ProcessData->GeneralList;
  gohRecoverList(GeneralList, (s32)v5, Index, v12);
  SeqHandle = ProcessData->SeqHandle;
  p_pSeqUnit = &ProcessData->pSeqUnit;
  v17 = id;
  v18 = jmsSeqChange(SeqHandle, p_pSeqUnit, 1, v17);
  if (v18)
  {
    v19 = *((void *)_get_Instance()[21].monitor + 2);
    if (get_activeSelf(v19, 0))
      SetActive(v19, 0, 0);
  }
  return v18;
}

// 0x1bd8d10
dds3ProcessFunc_t gohRecoverUpdateProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  jmsSeqHandle_t *monitor;
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
  monitor = ProcessData[1].monitor;
  v6 = id;
  return jmsSeqChange(monitor, &ProcessData[2], 2, v6);
}

// 0x1bd8e30
s32 gohTalkInit(dds3ProcessID_t *PID) {
  gohStart();
  return 1;
}

// 0x1bd8eb0
s32 gohTalkDestroy(dds3ProcessID_t *PID) {
  return 1;
}

// 0x1bd8ec0
dds3ProcessFunc_t gohTalkCalcProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  jmsSeqUnit_t *v5;
  jmsSeqHandle_t *monitor;
  dds3ProcessID_t *v7;
  dds3ProcessFunc_t v8;
  s32 SelectIndex;
  s32 v12;
  jmsSeqUnit_t *v14;
  jmsSeqUnit_t *v15;
  jmsSeqUnit_t *gohSeqUnit_local;
  jmsSeqUnit_t *v19;
  jmsSeqUnit_t *v21;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  v5 = &ProcessData[2];
  monitor = ProcessData[1].monitor;
  v7 = id;
  v8 = jmsSeqChange(monitor, v5, 0, v7);
  if (v8)
    return v8;
  SelectIndex = gohGetSelectIndex();
  if (SelectIndex == -1)
  {
    if (gohCheckMovePrev())
    {
      gohSeqUnit_local = gohSeqUnit;
      v15 = &gohSeqUnit_local[1];
      goto LABEL_44;
    }
    return v8;
  }
  v12 = gohGetSelectIndex();
  if (v12 == 12)
  {
    v19 = gohSeqUnit;
    v15 = &v19[21];
    goto LABEL_44;
  }
  if (v12 == 11)
  {
    v21 = gohSeqUnit;
    v15 = &v21[20];
    goto LABEL_44;
  }
  if (v12 != 10)
    return v8;
  v14 = gohSeqUnit;
  v15 = &v14[19];
LABEL_44:
  jmsSeqJumpAndFree(v5, v15);
  return 0;
}

// 0x1bd9190
dds3ProcessFunc_t gohTalkDrawProcess(dds3ProcessID_t *PID) {
  gohData_t *ProcessData;
  void *monitor;
  char *v7;
  char *LocalizeText;
  jmsSeqHandle_t *SeqHandle;
  dds3ProcessID_t *v11;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  gohUnityDraw(1);
  gohModel(ProcessData);
  monitor = _get_Instance()[17].monitor;
  v7 = strGohMenu[4];
  LocalizeText = GetLocalizeText(v7, 1);
  TitleDraw(monitor, 0, LocalizeText, 0);
  gohSetDispButtonGuide(60, 0, 0);
  SeqHandle = ProcessData->SeqHandle;
  v11 = id;
  return jmsSeqChange(SeqHandle, &ProcessData->pSeqUnit, 1, v11);
}

// 0x1bd93d0
dds3ProcessFunc_t gohTalkUpdateProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  jmsSeqHandle_t *monitor;
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
  monitor = ProcessData[1].monitor;
  v6 = id;
  return jmsSeqChange(monitor, &ProcessData[2], 2, v6);
}

// 0x1bd94f0
s32 gohMiscInit(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  fclEndMessage();
  if (!ProcessData)
  LODWORD(ProcessData[5].klass) = 2;
  cmpMemCheckRelease();
  return 1;
}

// 0x1bd9620
s32 gohMiscDestroy(dds3ProcessID_t *PID) {
  void *Instance;

  Instance = get_Instance(0);
  ItfButtonGuideSet(Instance, 0, 0);
  return 1;
}

// 0x1bd9690
dds3ProcessFunc_t gohMiscCalcProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  jmsSeqUnit_t *v5;
  jmsSeqHandle_t *monitor;
  dds3ProcessID_t *v7;
  dds3ProcessFunc_t v9;
  dds3ProcessID_t *v11;
  jmsSeqUnit_t *gohSeqUnit_local;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  v5 = &ProcessData[2];
  monitor = ProcessData[1].monitor;
  v7 = id;
  v9 = jmsSeqChange(monitor, v5, 0, v7);
  if (v9)
    return v9;
  v11 = id;
  if (!!gohScrControl(id))
    return v9;
  gohSeqUnit_local = gohSeqUnit;
  jmsSeqJumpAndFree(v5, &gohSeqUnit_local[18]);
  return 0;
}

// 0x1bd9c10
dds3ProcessFunc_t gohMiscDrawProcess(dds3ProcessID_t *PID) {
  gohData_t *ProcessData;
  void *monitor;
  char *v7;
  char *LocalizeText;
  jmsSeqHandle_t *SeqHandle;
  dds3ProcessID_t *v12;
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
  monitor = _get_Instance()[17].monitor;
  v7 = strGohMenu[10];
  LocalizeText = GetLocalizeText(v7, 1);
  TitleDraw(monitor, 0, LocalizeText, 0);
  gohModel(ProcessData);
  if (logdispwk->start)
  {
    SeqHandle = ProcessData->SeqHandle;
    v12 = id;
    return jmsSeqChange(SeqHandle, &ProcessData->pSeqUnit, 1, v12);
  }
  Instance = get_Instance(0);
  ItfButtonGuideActive(Instance, 0, 0);
  SeqHandle = ProcessData->SeqHandle;
  v12 = id;
  return jmsSeqChange(SeqHandle, &ProcessData->pSeqUnit, 1, v12);
}

// 0x1bd9ec0
dds3ProcessFunc_t gohMiscUpdateProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  jmsSeqHandle_t *monitor;
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
  monitor = ProcessData[1].monitor;
  v6 = id;
  return jmsSeqChange(monitor, &ProcessData[2], 2, v6);
}

// 0x1bd9fe0
s32 gohSinanInit(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  fclSetMessageInvalid(0);
  fclStartMessage(28);
  HIDWORD(ProcessData[20].monitor) = 0;
  return 1;
}

// 0x1bda0e0
s32 gohSinanDestroy(dds3ProcessID_t *PID) {
  return 1;
}

// 0x1bda0f0
dds3ProcessFunc_t gohSinanCalcProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  jmsSeqUnit_t *v5;
  jmsSeqHandle_t *monitor;
  dds3ProcessID_t *v7;
  dds3ProcessFunc_t v8;
  u64 *p_monitor;
  dds3ProcessID_t *v11;
  u8 *klass;
  dds3ProcessID_t *started;
  void *Instance;
  jmsSeqUnit_t *gohSeqUnit_local;
  dds3ProcessID_t *ID;
  dds3ProcessID_t *id;

  ID = PID;
  ProcessData = dds3GetProcessData(ID);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  v5 = &ProcessData[2];
  monitor = ProcessData[1].monitor;
  v7 = ID;
  v8 = jmsSeqChange(monitor, &ProcessData[2], 0, v7);
  if (!v8)
  {
    if (HIDWORD(ProcessData[20].monitor) == 1)
    {
      p_monitor = &ProcessData[9].monitor;
      v11 = ProcessData[9].monitor;
      if (!v11)
      {
        if (!fclChkMessageDraw())
        {
          cmpMemCheckRelease();
          klass = ProcessData[9].klass;
          started = scrStartScript2(1, klass, 0, 1);
          *p_monitor = started;
        }
        return v8;
      }
      id = ProcessData[9].monitor;
      if (dds3GetProcessStat(id) != 3)
      {
        if (dds3GetProcessStat(id))
          return v8;
      }
      fclSetMessageInvalid(0);
      fclStartMessage(28);
      gohStart();
      Instance = get_Instance(0);
      ItfButtonGuideSet(Instance, 0, 0);
      HIDWORD(ProcessData[20].monitor) = 0;
      ProcessData[9].monitor = 0;
      return v8;
    }
    gohGetSelectIndex();
    if (gohGetSelectIndex() == 13)
      goto LABEL_70;
    if (gohGetSelectIndex() == 14)
      goto LABEL_70;
    if (gohGetSelectIndex() != 15)
    {
      if (gohGetSelectIndex() != 16)
      {
        if (gohGetSelectIndex() != 17)
        {
          if (gohGetSelectIndex() != 18)
          {
            if (gohGetSelectIndex() != 19)
            {
              if (gohGetSelectIndex() == 20)
                goto LABEL_70;
              goto LABEL_67;
            }
          }
        }
      }
    }
LABEL_70:
    fclEndMessage();
    LODWORD(ProcessData[25].monitor) = gohGetSelectIndex() - 13;
    HIDWORD(ProcessData[20].monitor) = 1;
    if (!gohCheckMovePrev())
      return v8;
    goto LABEL_74;
LABEL_67:
    if (!gohCheckMovePrev())
      return v8;
LABEL_74:
    fclEndMessage();
    gohSeqUnit_local = gohSeqUnit;
    jmsSeqJumpAndFree(v5, &gohSeqUnit_local[18]);
  }
  return v8;
}

// 0x1bda6c0
dds3ProcessFunc_t gohSinanDrawProcess(dds3ProcessID_t *PID) {
  gohData_t *ProcessData;
  s32 WorkStat;
  void *monitor;
  char *v9;
  char *v10;
  jmsSeqHandle_t *SeqHandle;
  dds3ProcessID_t *v13;
  char *v16;
  char *LocalizeText;
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
  gohUnityDraw(1);
  gohModel(ProcessData);
  WorkStat = ProcessData->WorkStat;
  monitor = _get_Instance()[17].monitor;
  if (!WorkStat)
  {
    v16 = strGohMenu[4];
    LocalizeText = GetLocalizeText(v16, 1);
    TitleDraw(monitor, 0, LocalizeText, 0);
    gohSetDispButtonGuide(61, 0, 1);
    SeqHandle = ProcessData->SeqHandle;
    v13 = id;
    return jmsSeqChange(SeqHandle, &ProcessData->pSeqUnit, 1, v13);
  }
  v9 = strGohMenu[ProcessData->SinanMenuIndex + 13];
  v10 = GetLocalizeText(v9, 1);
  TitleDraw(monitor, 0, v10, 0);
  if (logdispwk->start)
  {
    SeqHandle = ProcessData->SeqHandle;
    v13 = id;
    return jmsSeqChange(SeqHandle, &ProcessData->pSeqUnit, 1, v13);
  }
  Instance = get_Instance(0);
  ItfButtonGuideActive(Instance, 0, 0);
  SeqHandle = ProcessData->SeqHandle;
  v13 = id;
  return jmsSeqChange(SeqHandle, &ProcessData->pSeqUnit, 1, v13);
}

// 0x1bdaa30
dds3ProcessFunc_t gohSinanUpdateProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  jmsSeqHandle_t *monitor;
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
  fclUpdateMessage();
  monitor = ProcessData[1].monitor;
  v6 = id;
  return jmsSeqChange(monitor, &ProcessData[2], 2, v6);
}

// 0x1bdab90
s32 gohCombCntInit(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  fclEndMessage();
  if (!ProcessData)
  LODWORD(ProcessData[5].klass) = 3;
  return 1;
}

// 0x1bdac90
s32 gohCombCntDestroy(dds3ProcessID_t *PID) {
  void *Instance;

  Instance = get_Instance(0);
  ItfButtonGuideSet(Instance, 0, 0);
  return 1;
}

// 0x1bdad00
dds3ProcessFunc_t gohCombCntCalcProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  jmsSeqUnit_t *v5;
  jmsSeqHandle_t *monitor;
  dds3ProcessID_t *v7;
  dds3ProcessFunc_t v9;
  dds3ProcessID_t *v11;
  jmsSeqUnit_t *gohSeqUnit_local;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  v5 = &ProcessData[2];
  monitor = ProcessData[1].monitor;
  v7 = id;
  v9 = jmsSeqChange(monitor, v5, 0, v7);
  if (v9)
    return v9;
  v11 = id;
  if (!!gohScrControl(id))
    return v9;
  gohSeqUnit_local = gohSeqUnit;
  jmsSeqJumpAndFree(v5, &gohSeqUnit_local[18]);
  return 0;
}

// 0x1bdaed0
dds3ProcessFunc_t gohCombCntDrawProcess(dds3ProcessID_t *PID) {
  gohData_t *ProcessData;
  jmsSeqHandle_t *SeqHandle;
  dds3ProcessID_t *v8;
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
  gohModel(ProcessData);
  if (logdispwk->start)
  {
    SeqHandle = ProcessData->SeqHandle;
    v8 = id;
    return jmsSeqChange(SeqHandle, &ProcessData->pSeqUnit, 1, v8);
  }
  Instance = get_Instance(0);
  ItfButtonGuideActive(Instance, 0, 0);
  SeqHandle = ProcessData->SeqHandle;
  v8 = id;
  return jmsSeqChange(SeqHandle, &ProcessData->pSeqUnit, 1, v8);
}

// 0x1bdb0e0
dds3ProcessFunc_t gohCombCntUpdateProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  jmsSeqHandle_t *monitor;
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
  monitor = ProcessData[1].monitor;
  v6 = id;
  return jmsSeqChange(monitor, &ProcessData[2], 2, v6);
}

// 0x1bdb200
s32 gohErrorInit(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  s32 klass;
  s32 v6;
  s32 result;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  klass = ProcessData[11].klass;
  HIDWORD(ProcessData[20].monitor) = 0;
  switch (klass)
  {
    case 0:
      fclSetMessageInvalid(1);
      v6 = 3;
      goto LABEL_32;
    case 1:
      fclSetMessageInvalid(1);
      v6 = 20;
      goto LABEL_32;
    case 2:
      fclSetMessageInvalid(1);
      v6 = 4;
      goto LABEL_32;
    case 3:
      fclSetMessageInvalid(1);
      v6 = 6;
      goto LABEL_32;
    case 4:
      fclEndMessageEx(2);
      goto LABEL_25;
    case 5:
      fclSetMessageInvalid(1);
      v6 = 19;
      goto LABEL_32;
    case 6:
      fclSetMessageInvalid(1);
      v6 = 21;
LABEL_32:
      fclStartMessage(v6);
      result = 1;
      break;
    default:
LABEL_25:
      result = 1;
      break;
  }
  return result;
}

// 0x1bdb450
s32 gohErrorDestroy(dds3ProcessID_t *PID) {
  return 1;
}

// 0x1bdb460
dds3ProcessFunc_t gohErrorCalcProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  jmsSeqUnit_t *v5;
  jmsSeqHandle_t *monitor;
  dds3ProcessID_t *v7;
  dds3ProcessFunc_t v8;
  u32 klass;
  jmsSeqUnit_t *gohSeqUnit_local;
  jmsSeqUnit_t *v13;
  jmsSeqUnit_t *v16;
  jmsSeqUnit_t *v18;
  jmsSeqUnit_t *v19;
  s32 monitor_high;
  jmsSeqUnit_t *v22;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  v5 = &ProcessData[2];
  monitor = ProcessData[1].monitor;
  v7 = id;
  v8 = jmsSeqChange(monitor, &ProcessData[2], 0, v7);
  if (v8)
    return v8;
  if (fclChkMessage())
    return v8;
  klass = ProcessData[11].klass;
  if (klass > 6)
    return v8;
  if (((1 << klass) & 0x6E) != 0)
  {
    if (LODWORD(ProcessData[13].klass) == 2)
    {
      gohSeqUnit_local = gohSeqUnit;
      v13 = &gohSeqUnit_local[9];
    }
    else
    {
      if (HIDWORD(ProcessData[27].monitor) == 4)
      {
        v16 = gohSeqUnit;
        v13 = &v16[8];
      }
      else
      {
        v19 = gohSeqUnit;
        v13 = &v19[4];
      }
    }
LABEL_42:
    jmsSeqJumpAndFree(v5, v13);
    return 0;
  }
  if (!klass)
  {
    v18 = gohSeqUnit;
    v13 = &v18[2];
    goto LABEL_42;
  }
  monitor_high = HIDWORD(ProcessData[20].monitor);
  if (monitor_high == 2)
  {
    HIDWORD(ProcessData[20].monitor) = 0;
    v22 = gohSeqUnit;
    v13 = &v22[1];
    goto LABEL_42;
  }
  if (monitor_high == 1)
  {
    if (!fclChkMessage())
    {
      HIDWORD(ProcessData[20].monitor) = 2;
      return 0;
    }
    return v8;
  }
  if (monitor_high)
    return v8;
  fclSetMessageInvalid(1);
  fclStartMessage(27);
  HIDWORD(ProcessData[20].monitor) = 1;
  return 0;
}

// 0x1bdb800
dds3ProcessFunc_t gohErrorDrawProcess(dds3ProcessID_t *PID) {
  gohData_t *ProcessData;
  void *Instance;
  jmsSeqHandle_t *SeqHandle;
  jmsSeqUnit_t *p_pSeqUnit;
  dds3ProcessID_t *v8;
  dds3ProcessFunc_t v9;
  void *v10;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  if ((ProcessData->ErrorType & 0xFFFFFFFE) != 2)
  {
    Instance = get_Instance(0);
    ItfButtonGuideActive(Instance, 0, 0);
    gohModel(ProcessData);
  }
  SeqHandle = ProcessData->SeqHandle;
  p_pSeqUnit = &ProcessData->pSeqUnit;
  v8 = id;
  v9 = jmsSeqChange(SeqHandle, p_pSeqUnit, 1, v8);
  if (v9)
  {
    v10 = get_Instance(0);
    ItfButtonGuideActive(v10, 1, 0);
  }
  return v9;
}

// 0x1bdb9e0
dds3ProcessFunc_t gohErrorUpdateProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  jmsSeqHandle_t *monitor;
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
  fclUpdateMessage();
  monitor = ProcessData[1].monitor;
  v6 = id;
  return jmsSeqChange(monitor, &ProcessData[2], 2, v6);
}

// 0x1bdbb40
s32 gohBookInit(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  dds3FadeOut(0, 0, 0, 0xAu);
  *(void **)((char *)&ProcessData[20].monitor + 4) = 0;
  return 1;
}

// 0x1bdbc40
s32 gohBookDestroy(dds3ProcessID_t *PID) {
  return 1;
}

// 0x1bdbc50
dds3ProcessFunc_t gohBookCalcProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  s32 klass;
  s32 v6;
  Il2CppObject *Instance;
  s32 monitor_high;
  jmsSeqHandle_t *monitor;
  dds3ProcessID_t *v11;
  jmsSeqUnit_t *gohSeqUnit_local;
  Il2CppObject *v15;
  void *v16;
  dds3Basic_t *ActiveScene;
  dds3ProcessID_t *id;

  id = PID;
  ActiveScene = 0;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
  switch (HIDWORD(ProcessData[20].monitor))
  {
    case 0:
      klass = ProcessData[21].klass;
      if (klass < 11)
        goto LABEL_25;
      v6 = 1;
      goto LABEL_24;
    case 1:
      ActiveScene = dds3GetActiveScene();
      dds3SceneBasicVisible(ActiveScene, 0);
      Instance = _get_Instance();
      CanvasActive(Instance, 0, 0);
      ProcessStart(3);
      monitor_high = HIDWORD(ProcessData[20].monitor);
      goto LABEL_45;
    case 2:
      if (!ProcessCheck())
        goto LABEL_36;
LABEL_26:
      monitor = ProcessData[1].monitor;
      v11 = id;
      return jmsSeqChange(monitor, &ProcessData[2], 0, v11);
LABEL_36:
      v15 = _get_Instance();
      CanvasActive(v15, 1, 0);
      ActiveScene = dds3GetActiveScene();
      dds3SceneBasicVisible(ActiveScene, 1);
      v16 = get_Instance(0);
      ItfButtonGuideSet(v16, 0, 0);
      dds3FadeIn(0, 0, 0, 0xAu);
      monitor_high = HIDWORD(ProcessData[20].monitor);
      LODWORD(ProcessData[21].klass) = 0;
LABEL_45:
      HIDWORD(ProcessData[20].monitor) = monitor_high + 1;
      monitor = ProcessData[1].monitor;
      v11 = id;
      return jmsSeqChange(monitor, &ProcessData[2], 0, v11);
    case 3:
      klass = ProcessData[21].klass;
      if (klass >= 11)
      {
        v6 = 4;
LABEL_24:
        HIDWORD(ProcessData[20].monitor) = v6;
      }
LABEL_25:
      LODWORD(ProcessData[21].klass) = klass + 1;
      goto LABEL_26;
    case 4:
      gohSeqUnit_local = gohSeqUnit;
      jmsSeqJumpAndFree(&ProcessData[2], &gohSeqUnit_local[1]);
      monitor = ProcessData[1].monitor;
      v11 = id;
      return jmsSeqChange(monitor, &ProcessData[2], 0, v11);
    default:
      goto LABEL_26;
  }
}

// 0x1bdc040
dds3ProcessFunc_t gohBookDrawProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  jmsSeqHandle_t *monitor;
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
  monitor = ProcessData[1].monitor;
  v6 = id;
  return jmsSeqChange(monitor, &ProcessData[2], 1, v6);
}

// 0x1bdc160
dds3ProcessFunc_t gohBookUpdateProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  jmsSeqHandle_t *monitor;
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
  monitor = ProcessData[1].monitor;
  v6 = id;
  return jmsSeqChange(monitor, &ProcessData[2], 2, v6);
}

// 0x1bd7f90
s32 gohCyuuseiStartDirection(gohData_t *pData) {
  s32 result;
  s32 v6;
  bool v7;
  jmsSeqUnit_t *p_pSeqUnit;
  jmsSeqUnit_t *gohSeqUnit_local;

  if (cmpChkStatusModelLoadStat() == 1)
    return 0;
  fclDestroyMessage();
  ProcessEnd();
  if (ProcessCheck())
    return 0;
  v6 = gohStopStatusDraw(pData, 1, 0);
  result = 0;
  if (v6 >= 2)
  {
    ProcessEnd(0, 0);
    v7 = ProcessCheck();
    result = 0;
    if (!v7)
    {
      ModelFree(pData);
      p_pSeqUnit = &pData->pSeqUnit;
      gohSeqUnit_local = gohSeqUnit;
      jmsSeqJumpAndFree(p_pSeqUnit, &gohSeqUnit_local[23]);
      return 1;
    }
  }
  return result;
}

// 0x1bd5b20
s32 gohCheckScrRun(dds3ProcessID_t *PID) {
  dds3ProcessID_t *id;

  id = PID;
  if (dds3GetProcessStat(id) == 3)
    return 0;
  return dds3GetProcessStat(id) != 0;
}

// 0x1bd9860
s32 gohScrControl(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  void **p_monitor;
  dds3ProcessID_t *monitor;
  dds3ProcessID_t *v8;
  s32 klass;
  s32 v11;
  s32 *v12;
  s64 v13;
  dds3ModelHandle_t *v14;
  u8 *v16;
  dds3ProcessID_t *started;
  dds3ProcessID_t *v18;
  dds3ProcessID_t *id;

  v18 = PID;
  ProcessData = dds3GetProcessData(v18);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  p_monitor = &ProcessData[7].monitor;
  monitor = ProcessData[7].monitor;
  if (monitor)
  {
    id = ProcessData[7].monitor;
    if (dds3GetProcessStat(id) == 3)
      goto LABEL_45;
    goto LABEL_24;
    if (dds3GetProcessStat(id) == 3)
    {
LABEL_45:
      *p_monitor = 0;
      return 1;
    }
LABEL_24:
    if (!dds3GetProcessStat(id))
      goto LABEL_45;
    return 1;
  }
  p_monitor = &ProcessData[5].monitor;
  v8 = ProcessData[5].monitor;
  if (v8)
  {
    id = ProcessData[5].monitor;
    if (dds3GetProcessStat(id) == 3)
    {
LABEL_38:
      v12 = ProcessData[3].monitor;
      if (v12[6] >= 1)
      {
        v13 = 0;
        do
        {
          v14 = *(dds3ModelHandle_t *)&v12[2 * v13 + 8];
          if (v14)
          {
            mdlSmoothLoopMotion(v14, 0, 0, 15.0, 15.0, 0.0);
            v12 = ProcessData[3].monitor;
          }
          ++v13;
        }
        while (v13 < v12[6]);
      }
      goto LABEL_45;
    }
    if (dds3GetProcessStat(id))
      return 1;
    goto LABEL_38;
  }
  klass = ProcessData[5].klass;
  if (klass < 0 || HIDWORD(ProcessData[10].klass))
    return 0;
  LODWORD(ProcessData[10].klass) = 1;
  v16 = ProcessData[4].monitor;
  v11 = 1;
  started = scrStartScript2(1, v16, klass, 1);
  ProcessData[5].monitor = started;
  LODWORD(ProcessData[5].klass) = -1;
  return v11;
}

// 0x1bcfbd0
void gohCreateCombineResult(gohData_t *pSelf, s32 Step) {
  s32 StockDevilNums;
  gohResult_t *v7;
  s64 v8;
  s64 i;
  gohResult_t *Result;
  gohResult_t *v11;
  Il2CppClass **v12;
  u32 v13;
  s32 v14;
  s64 v15;
  s64 v16;
  s64 v17;
  s64 v19;
  sdatUnitWork_t *stock_id;
  sdatUnitWork_t *v22;
  sdatUnitWork_t *v23;
  gohResult_t *v24;
  __int128 v25;

  StockDevilNums = datGetStockDevilNums(0);
  goto LABEL_4;
  if ((u32)Step > 6)
  {
LABEL_11:
    v13 = 28;
    if (StockDevilNums >= 32)
      v14 = 32;
    else
      v14 = StockDevilNums;
    if (v14 <= 28)
      return;
LABEL_50:
    v15 = v13;
    v16 = v14;
    v17 = 0;
    while (1)
    {
LABEL_60:
      if (v17 < datGetStockDevilNums(0))
        goto LABEL_54;
      while (1)
      {
        if (++v15 == v16)
          return;
        v17 = 0;
        break;
        while (1)
        {
          if (v17 >= datGetStockDevilNums(0))
            break;
LABEL_54:
          if (v15 == v17)
          {
            v19 = *((u64 *)&pSelf->Result[v15] + v15 * pSelf->Result->bounds[1].length);
            *(u32 *)(v19 + 24) = 0;
            *(u16 *)(*(u64 *)(v19 + 32) + 22) = 0;
            ++v17;
            goto LABEL_60;
          }
          else
          {
            stock_id = GBWK->player->stock_id;
            v22 = stock_id[v17];
            v23 = stock_id[v15];
            v24 = *(&pSelf->Result[v15] + pSelf->Result->bounds[1].length * v17);
            gohResultUnit(v24, pSelf, v23, v22);
            ++v17;
            goto LABEL_60;
          }
        }
      }
    }
  }
LABEL_4:
  switch (Step)
  {
    case 0:
      v25 = xmmword_3D00540;
      v7 = sub_3BD9D0(Project_gohResult_t_, &v25);
      pSelf->Result = v7;
      v8 = 0;
      for (i = 0; ; i = 0)
      {
        do
        {
          Result = pSelf->Result;
          v11 = Allocate(gohResult_t);
          _ctor(v11, 0);
          v12 = &Result->obj.klass + i + v8 * Result->bounds[1].length;
          v12[4] = v11;
          ++i;
        }
        while (i != 32);
        if (++v8 == 32)
          break;
      }
      v13 = 0;
      if (StockDevilNums >= 4)
        v14 = 4;
      else
        v14 = StockDevilNums;
      if (v14 > 0)
        goto LABEL_50;
      break;
    case 1:
      v13 = 4;
      if (StockDevilNums >= 8)
        v14 = 8;
      else
        v14 = StockDevilNums;
      if (v14 > 4)
        goto LABEL_50;
      break;
    case 2:
      v13 = 8;
      if (StockDevilNums >= 12)
        v14 = 12;
      else
        v14 = StockDevilNums;
      if (v14 > 8)
        goto LABEL_50;
      break;
    case 3:
      v13 = 12;
      if (StockDevilNums >= 16)
        v14 = 16;
      else
        v14 = StockDevilNums;
      if (v14 > 12)
        goto LABEL_50;
      break;
    case 4:
      v13 = 16;
      if (StockDevilNums >= 20)
        v14 = 20;
      else
        v14 = StockDevilNums;
      if (v14 > 16)
        goto LABEL_50;
      break;
    case 5:
      v13 = 20;
      if (StockDevilNums >= 24)
        v14 = 24;
      else
        v14 = StockDevilNums;
      if (v14 > 20)
        goto LABEL_50;
      break;
    case 6:
      v13 = 24;
      if (StockDevilNums >= 28)
        v14 = 28;
      else
        v14 = StockDevilNums;
      if (v14 > 24)
        goto LABEL_50;
      break;
    default:
      goto LABEL_11;
  }
}

// 0x1bdc280
void *gohCreateCombineResultAllAsync(gohData_t *pSelf) {
  System_Runtime_CompilerServices_AsyncTaskMethodBuilder_o v5;
  Project_gohMain__CreateCombineResultAllAsync_d__126_o v6;

  memset(&v6, 0, sizeof(v6));
  Create(&v5, 0);
  v6.__t__builder = v5;
  v6.pSelf = pSelf;
  v6.__1__state = -1;
  Start_gohMain__CreateCombineResultAllAsync_d__126_(&v6.__t__builder, &v6);
  return get_Task(&v6.__t__builder, 0);
}

// 0x1bdc370
void gohCreateCombineResultAll(gohData_t *pSelf) {
  gohResult_t *v3;
  gohResult_t **p_Result2;
  s64 v5;
  s64 i;
  gohResult_t *v7;
  gohResult_t *v8;
  Il2CppClass **v9;
  s32 StockDevilNums;
  s64 v11;
  s64 v12;
  s64 j;
  gohResult_t *v14;
  il2cpp_array_size_t v15;
  gohResult_t *v16;
  sdatUnitWork_t *stock_id;
  sdatUnitWork_t *v19;
  sdatUnitWork_t *v20;
  s32 devilid;
  s32 v22;
  bool v23;
  gohResult_t *v24;
  sdatUnitWork_t *Devil;
  __int128 v26;

  v26 = xmmword_3D00540;
  v3 = sub_3BD9D0(Project_gohResult_t_, &v26);
  p_Result2 = &pSelf->Result2;
  pSelf->Result2 = v3;
  v5 = 0;
  for (i = 0; ; i = 0)
  {
    do
    {
      v7 = *p_Result2;
      v8 = Allocate(gohResult_t);
      _ctor(v8, 0);
      v9 = &v7->obj.klass + i + v5 * v7->bounds[1].length;
      v9[4] = v8;
      ++i;
    }
    while (i != 32);
    if (++v5 == 32)
      break;
  }
  StockDevilNums = datGetStockDevilNums(0);
  if (StockDevilNums < 1)
    return;
  goto LABEL_11;
  if (StockDevilNums >= 1)
  {
LABEL_11:
    v11 = 0;
    v12 = StockDevilNums;
    do
    {
      for (j = 0; j != v12; ++j)
      {
        while (1)
        {
          while (v11 == j)
          {
            v14 = *p_Result2;
            v15 = v11 + v11 * (*p_Result2)->bounds[1].length;
LABEL_15:
            v16 = v14[v15];
            v16->m_iType = 0;
            v16->Devil->devilid = 0;
            if (v12 == ++j)
              goto LABEL_12;
          }
          stock_id = GBWK->player->stock_id;
          v19 = stock_id[v11];
          v20 = stock_id[j];
          devilid = v19->devilid;
          if (!DlcDevilSelCheck(devilid))
          {
            v14 = *p_Result2;
            v15 = v11 + (*p_Result2)->bounds[1].length * j;
            goto LABEL_15;
          }
          v22 = v20->devilid;
          v23 = DlcDevilSelCheck(v22);
          v24 = *(&(*p_Result2)[v11] + (*p_Result2)->bounds[1].length * j);
          if (v23)
            break;
          Devil = v24->Devil;
          v24->m_iType = 0;
          Devil->devilid = 0;
          if (v12 == ++j)
            goto LABEL_12;
        }
        gohResultUnit(v24, pSelf, v19, v20);
      }
LABEL_12:
      ++v11;
    }
    while (v11 != v12);
  }
}

// 0x1bd0ed0
s32 gohSelectMenuUpdate(void *pCmdMenu) {
  u32 v3;
  bool v5;
  void *v6;
  void *pCmdList;

  v3 = jmsChkCommonInput(0x30u);
  if (CHECK_TRIG(4096, 1) || CHECK_TRIG(4097, 1))
    return 1;
  if (cmpGetModeSq())
    return 1;
  CmdMenuMoveUnlock(pCmdMenu);
  if ((v3 & 0x10) == 0)
  {
    if ((v3 & 0x20) == 0)
      return 1;
    v5 = 0;
    goto LABEL_17;
  }
  v6 = CmdMenuItemMovePrev(pCmdMenu);
  v5 = v6 != 0;
  if ((v3 & 0x20) != 0)
  {
LABEL_17:
    if (!CmdMenuItemMoveNext(pCmdMenu) && !v5)
      return 1;
    goto LABEL_19;
  }
  if (!v6)
    return 1;
LABEL_19:
  pCmdList = pCmdMenu->pCmdList;
  jmsPlaySE(0, v3, pCmdList);
  return 1;
}

// 0x1bd1e60
s32 gohGetSelDevilStockIndex(gohData_t *pData, s32 Index) {
  void *m_pDevSelList2;

  if (Index == 1)
  {
    m_pDevSelList2 = pData->m_pDevSelList2;
    if (m_pDevSelList2)
      return ITEMIDX(m_pDevSelList2);
  }
  else if (!Index)
  {
    m_pDevSelList2 = pData->m_pDevSelList1;
    if (m_pDevSelList2)
      return ITEMIDX(m_pDevSelList2);
  }
  return -1;
}

// 0x1bdc660
s32 gohGetSelSwordIndex(gohData_t *pData) {
  void *m_pSelList;

  m_pSelList = pData->m_pSelList;
  if (m_pSelList)
    ITEMIDX(m_pSelList);
  return -1;
}

// 0x1bdc690
s32 gohGetSelDevilID(gohData_t *pData, s32 Type) {
  void *m_pDevSelList2;
  s32 v7;
  u32 v8;

  goto LABEL_3;
LABEL_9:
  m_pDevSelList2 = pData->m_pDevSelList2;
  if (!m_pDevSelList2)
    return (s32)m_pDevSelList2;
  goto LABEL_10;
LABEL_3:
  if (Type == 1)
    goto LABEL_9;
  if (Type)
  {
LABEL_14:
    LODWORD(m_pDevSelList2) = 0;
    return (s32)m_pDevSelList2;
  }
  m_pDevSelList2 = pData->m_pDevSelList1;
  if (!m_pDevSelList2)
    return (s32)m_pDevSelList2;
LABEL_10:
  v7 = ITEMIDX(m_pDevSelList2);
  if (v7 < 0)
    goto LABEL_14;
  v8 = v7;
  LODWORD(m_pDevSelList2) = *(s16 *)(*(u64 *)(*((u64 *)m_pDevSelList2[1].pScrollBar[20].klass->_1.typeMetadataHandle + 16) + 8 * v8 + 32) + 22);
  return (s32)m_pDevSelList2;
}

// 0x1bdc7a0
void gohSceneOffFunc(void) {
  gohData_t *GohData;
  Il2CppObject *Instance;
  Il2CppObject *v4;
  Il2CppObject *v5;
  dds3Basic_t *basic;

  basic = 0;
  GohData = GohGetGohData();
  if (GohData)
  {
    basic = GohData->gouScene;
    dds3SceneBasicVisible(basic, 0);
  }
  evtMoonDisableDraw(1);
  Instance = _get_Instance();
  if (!op_Inequality(Instance, 0, 0))
    return;
  v4 = _get_Instance();
  MenuClose(*((void *)v4[20].monitor + 3), 0);
  v5 = _get_Instance();
  CanvasActive(v5, 0, 0);
  return;
}

// 0x1bd7420
void gohStartStatusDraw(gohData_t *pData, sdatUnitWork_t *pUnit, CMP_STATUS_TYPE Mode, s32 SwordNo) {
  s64 v11;
  s64 max_length;
  _BOOL4 v13;
  dds3Basic_t *ActiveScene;
  void *v15;

  if ((pData->Flag & 0x10000) == 0)
  {
    cmpLoadLocalizeText();
    Start(pUnit, 0);
    SetType(Mode, SwordNo, resultCheck);
    if ((Mode & 0x20000000) == 0 && pData->m_iStatusType == 2 && pData->noPartVoice)
    {
      cmpNoCallVoiceSet();
      pData->noPartVoice = 0;
    }
    if ((Mode & 0x8000000) != 0)
    {
      cmpStartMemSet(pUnit, 1);
      if ((Mode & 0x40000000) != 0)
        goto LABEL_40;
    }
    else
    {
      if (pUnit->devilid)
      {
        if ((Mode & 0x40000000) == 0)
          goto LABEL_19;
LABEL_40:
        cmpStartGoodby(pUnit);
        goto LABEL_20;
      }
      cmpSklTypeSet(0, 0);
      if ((Mode & 0x40000000) != 0)
        goto LABEL_40;
    }
LABEL_19:
LABEL_20:
    dds3FilterClear();
    pData->Flag = pData->Flag & 0xFFFAFFFF | 0x10000;
    if ((s32)pData->m_abActSkillFlag->max_length >= 1)
    {
      v11 = 0;
      if ((u32)pData->m_abActSkillFlag->max_length <= 1u)
        max_length = 1;
      else
        max_length = (u32)pData->m_abActSkillFlag->max_length;
      do
      {
        v13 = pData->m_abActSkillFlag[v11];
        cmpSetLightUpSkl(v11++, v13);
      }
      while (max_length != v11);
    }
    ActiveScene = dds3GetActiveScene();
    pData->gouScene = ActiveScene;
    v15 = Allocate(System_Action);
    _ctor(v15, 0, Method_Project_gohMain_SceneOffFunc__, 0);
    cmpSetStartStatusSetting(1, v15);
    StatusSceneActive(1);
    return;
  }
}

// 0x1bcaaf0
s32 gohStopStatusDraw(gohData_t *pData, s32 Mode, bool _cmpNoEnd) {
  s32 Flag;
  dds3ProcessID_t *PmvPID;
  Il2CppObject *v9;
  Il2CppObject *v10;
  void *v11;
  Il2CppObject *Instance;
  void *gameObject;
  Il2CppObject *v15;
  s32 bgDrawWait;
  bool v17;
  char v18;
  s32 v19;
  dds3Basic_t *basic;

  Flag = pData->Flag;
  if ((Flag & 0x10000) != 0)
  {
    End();
    pData->Flag &= ~0x10000u;
    Instance = _get_Instance();
    gameObject = get_gameObject(Instance, 0);
    if (get_activeSelf(gameObject, 0))
    {
      v15 = _get_Instance();
      if (cmpNoEnd)
        StatusUiGoobyOff(v15, 0);
      else
        StatusUiOff(v15, 0);
      return 0;
    }
    else
    {
      return 0;
    }
  }
  else
  {
    if ((Flag & 0x40000) == 0)
    {
      if (cmpChkEnd())
      {
        if (!Mode)
        {
          PmvPID = pData->PmvPID;
          evtSetFrame(PmvPID, 0);
          basic = dds3GetActiveScene();
          dds3SceneBasicVisible(basic, 1);
          if (!cmpNoEnd)
          {
            v9 = _get_Instance();
            CallEnd(v9, 0);
          }
          v10 = _get_Instance();
          CanvasActive(v10, 1, 0);
          v11 = get_Instance(0);
          ItfButtonGuideSet(v11, 0, 0);
          pData->bgDrawWait = 5;
        }
        pData->Flag |= 0x40000u;
        return 2;
      }
      return 1;
    }
    bgDrawWait = pData->bgDrawWait;
    v17 = __OFSUB__(bgDrawWait, 1);
    v19 = bgDrawWait - 1;
    v18 = (v19 < 0) ^ v17;
    if (v18)
      v19 = 0;
    pData->bgDrawWait = v19;
    if (v18)
      return 4;
    else
      return 3;
  }
}

// 0x1bd1400
s32 gohCheckBgDraw(gohData_t *pData) {
  return ((u32)pData->Flag >> 18) & 1;
}

// 0x1bcff90
void gohCreateDevSelList(gohData_t *pData) {
  s32 StockDevilNums;
  void *m_pDevSelList1;
  void *p_m_pDevSelList1;
  void *m_pDevSelList2;
  void *p_m_pDevSelList2;
  void *CmdMenu;
  s32 v9;
  void *v10;
  void *v11;

  StockDevilNums = datGetStockDevilNums(0);
  p_m_pDevSelList1 = &pData->m_pDevSelList1;
  m_pDevSelList1 = pData->m_pDevSelList1;
  if (m_pDevSelList1)
    jmsDestroyCmdMenu(m_pDevSelList1);
  p_m_pDevSelList2 = &pData->m_pDevSelList2;
  m_pDevSelList2 = pData->m_pDevSelList2;
  if (m_pDevSelList2)
    jmsDestroyCmdMenu(m_pDevSelList2);
  CmdMenu = jmsCreateCmdMenu(0, 0, 0, 12, 22);
  pData->m_pDevSelList1 = CmdMenu;
  pData->m_iDevColumn = 0;
  if (StockDevilNums < 1)
  {
    v11 = jmsCreateCmdMenu(0, 0, 0, 12, 22);
    p_m_pDevSelList2 = v11;
  }
  else
  {
    v9 = StockDevilNums;
    do
    {
      jmsAddCmdMenuItem(p_m_pDevSelList1, 0);
      --v9;
    }
    while (v9);
    v10 = jmsCreateCmdMenu(0, 0, 0, 12, 22);
    p_m_pDevSelList2 = v10;
    do
    {
      jmsAddCmdMenuItem(p_m_pDevSelList2, 0);
      --StockDevilNums;
    }
    while (StockDevilNums);
  }
}

// 0x1bdc950
s32 gohCreateSwordList(gohData_t *pData) {
  s32 m_iSwordCnt;
  void *m_pSelList;
  void *p_m_pSelList;
  void *CmdMenu;
  s32 v6;

  m_iSwordCnt = pData->m_sRenkenSelSword->m_iSwordCnt;
  if (m_iSwordCnt)
  {
    p_m_pSelList = &pData->m_pSelList;
    m_pSelList = pData->m_pSelList;
    if (m_pSelList)
      jmsDestroyCmdMenu(m_pSelList);
    CmdMenu = jmsCreateCmdMenu(0, 0, 0, 11, 22);
    p_m_pSelList = CmdMenu;
    if (m_iSwordCnt >= 1)
    {
      v6 = m_iSwordCnt;
      do
      {
        jmsAddCmdMenuItem(p_m_pSelList, 0);
        --v6;
      }
      while (v6);
    }
  }
  return m_iSwordCnt;
}

// 0x1bdc9f0
s32 gohCreateRecoverList(gohData_t *pData) {
  s32 RecoverUnit;
  void *v4;
  void *p_m_pSelList;
  void *m_pSelList;
  void *CmdMenu;
  void *v8;
  void *v9;
  s32 v10;

  RecoverUnit = gohCreateRecoverUnit(&pData->GeneralList);
  if (RecoverUnit)
  {
    m_pSelList = pData->m_pSelList;
    p_m_pSelList = &pData->m_pSelList;
    v4 = m_pSelList;
    if (m_pSelList)
      jmsDestroyCmdMenu(v4);
    CmdMenu = jmsCreateCmdMenu(0, 0, 0, 10, 22);
    p_m_pSelList = CmdMenu;
    v8 = p_m_pSelList;
    v9 = *((void *)_get_Instance()[21].monitor + 10);
    v8->scrollBarUi = v9;
    if (RecoverUnit >= 1)
    {
      v10 = RecoverUnit;
      do
      {
        jmsAddCmdMenuItem(p_m_pSelList, 0);
        --v10;
      }
      while (v10);
    }
  }
  return RecoverUnit;
}

// 0x1bdcae0
dds3ProcessFunc_t gohRootWaitCalcProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  jmsSeqUnit_t *v5;
  jmsSeqHandle_t *monitor;
  dds3ProcessID_t *v7;
  dds3ProcessFunc_t v8;
  dds3ProcessFunc_t v11;
  dds3ProcessID_t *v12;
  void *Instance;
  jmsSeqUnit_t *gohSeqUnit_local;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  v5 = &ProcessData[2];
  monitor = ProcessData[1].monitor;
  v7 = id;
  v8 = jmsSeqChange(monitor, &ProcessData[2], 0, v7);
  if (v8)
    return v8;
  v8 = 0;
  if (dds3FadeCheck())
    return v8;
  if (HIDWORD(ProcessData[10].klass))
  {
    v11 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
    _ctor(v11, 0, Method_Project_gohMain_EndProcess__, 0);
    return v11;
  }
  v12 = id;
  if (!gohScrControl(v12))
  {
    if (evtBitCheck(10019))
    {
      goto LABEL_25;
    }
    else
    {
      tipsTIPSStart(35);
LABEL_25:
      v8 = 0;
      if (!tipsProcessCheck())
        goto LABEL_31;
      return v8;
    }
    v8 = 0;
    if (!tipsProcessCheck())
    {
LABEL_31:
      LoadLocalizeText();
      ProcessStart(0);
      gohSetFocus(0);
      fclSetMessageInvalid(0);
      fclStartMessage(0);
      Instance = get_Instance(0);
      ItfButtonGuideSet(Instance, 1, 0);
      gohSeqUnit_local = gohSeqUnit;
      jmsSeqJump(v5, &gohSeqUnit_local[1]);
      sdfMemSetAllocated();
      return 0;
    }
    return v8;
  }
  return 0;
}

// 0x1bdcec0
dds3ProcessFunc_t gohRootWaitDrawProcess(dds3ProcessID_t *PID) {
  gohData_t *ProcessData;
  jmsSeqHandle_t *SeqHandle;
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
  gohModel(ProcessData);
  SeqHandle = ProcessData->SeqHandle;
  v6 = id;
  return jmsSeqChange(SeqHandle, &ProcessData->pSeqUnit, 1, v6);
}

// 0x1bdd020
dds3ProcessFunc_t gohRootWaitUpdateProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  jmsSeqHandle_t *monitor;
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
  monitor = ProcessData[1].monitor;
  v6 = id;
  return jmsSeqChange(monitor, &ProcessData[2], 2, v6);
}

// 0x1bdd140
s32 gohRootInit(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  Il2CppObject *Instance;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  gohStart();
  Instance = _get_Instance();
  AllUiActive(Instance, 1, 0);
  GohSkillChangeSettingDestroy();
  if (!ProcessData)
  LODWORD(ProcessData[1].klass) &= ~0x80000u;
  miniMapDispSet(0);
  return 1;
}

// 0x1bdd2d0
s32 gohRootDestroy(dds3ProcessID_t *PID) {
  return 1;
}

// 0x1bdd2e0
dds3ProcessFunc_t gohRootCalcProcess(dds3ProcessID_t *PID) {
  gohData_t *ProcessData;
  jmsSeqHandle_t *SeqHandle;
  dds3ProcessID_t *v6;
  dds3ProcessFunc_t v8;
  s32 SelectIndex;
  s32 v12;
  char v17;
  s32 v18;
  void *Instance;
  jmsSeqUnit_t *v21;
  jmsSeqUnit_t *v22;
  jmsSeqUnit_t *gohSeqUnit_local;
  jmsSeqUnit_t *v25;
  jmsSeqUnit_t *v26;
  jmsSeqUnit_t *v27;
  jmsSeqUnit_t *v29;
  gohRenkenSelSwordList_t *m_sRenkenSelSword;
  jmsSeqUnit_t *v32;
  jmsSeqUnit_t *v34;
  jmsSeqUnit_t *v36;
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
  v6 = id;
  v8 = jmsSeqChange(SeqHandle, &ProcessData->pSeqUnit, 0, v6);
  if (!v8)
  {
    gohSetDispButtonGuide(0, 0, 0);
    v8 = 0;
    if (fclChkMessage())
      return v8;
    if (g_mainPID)
    {
      gohSetFocus(1);
      evtMoonDisableDraw(1);
      SelectIndex = gohGetSelectIndex();
      if (SelectIndex == -1)
      {
        if (!gohCheckMovePrev())
          goto LABEL_104;
LABEL_41:
        Instance = get_Instance(0);
        ItfButtonGuideActive(Instance, 0, 0);
        fclEndMessage();
        ProcessData->m_TalkScrReq = 1;
        v8 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
        _ctor(v8, 0, Method_Project_gohMain_EndProcess__, 0);
        return v8;
      }
      v12 = gohGetSelectIndex();
      if (v12 > 23)
      {
        if (v12 == 24)
        {
          gohSeqUnit_local = ProcessData->gohKarte2Seq->gohSeqUnit;
          jmsSeqJumpAndFree(&ProcessData->pSeqUnit, &gohSeqUnit_local[1]);
        }
        else if (v12 == 28)
        {
          if (gCallFromMenu == 2)
          {
            v17 = 0;
            v18 = 4;
          }
          else
          {
            v17 = 0;
            v18 = 3;
          }
          gCallFromMenu = v18;
          goto LABEL_94;
        }
        v17 = 1;
        goto LABEL_94;
      }
      v17 = 1;
      switch (v12)
      {
        case 1:
          v21 = gohSeqUnit;
          v22 = &v21[2];
          goto LABEL_82;
        case 2:
          if (gohCreateRecoverList(ProcessData))
          {
            v25 = gohSeqUnit;
            v26 = &v25[17];
          }
          else
          {
            ProcessData->ErrorType = 4;
            v36 = gohSeqUnit;
            v26 = &v36[22];
          }
          goto LABEL_93;
        case 3:
          v27 = ProcessData->gohKarteSeq->gohSeqUnit;
          v26 = &v27[1];
          goto LABEL_93;
        case 4:
          v29 = gohSeqUnit;
          v26 = &v29[18];
          goto LABEL_93;
        case 5:
          v17 = 0;
          break;
        case 7:
          gohClear();
          m_sRenkenSelSword = ProcessData->m_sRenkenSelSword;
          ProcessData->m_eCombineType = 2;
          gohSelSwordList(m_sRenkenSelSword);
          v32 = gohSeqUnit;
          v22 = &v32[11];
LABEL_82:
          jmsSeqJumpAndFree(&ProcessData->pSeqUnit, v22);
          v17 = 1;
          *(u16 *)&s_bDrawBack = 0;
          break;
        case 23:
          v34 = gohSeqUnit;
          v26 = &v34[24];
LABEL_93:
          jmsSeqJumpAndFree(&ProcessData->pSeqUnit, v26);
          break;
        default:
          break;
      }
LABEL_94:
      if (gohGetSelectIndex() != 5)
      {
        if (gohGetSelectIndex() != 28)
        {
          fclEndMessage();
        }
      }
      if ((v17 & 1) != 0)
      {
LABEL_104:
        v8 = 0;
        ProcessData->MenuFade = 0;
        return v8;
      }
      goto LABEL_41;
    }
    return 0;
  }
  return v8;
}

// 0x1bdd920
dds3ProcessFunc_t gohRootDrawProcess(dds3ProcessID_t *PID) {
  gohData_t *ProcessData;
  jmsSeqHandle_t *SeqHandle;
  dds3ProcessID_t *v6;
  dds3ProcessFunc_t v7;
  Il2CppObject *Instance;
  void *v9;
  Il2CppObject *v10;
  Il2CppObject *v11;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  gohModel(ProcessData);
  SeqHandle = ProcessData->SeqHandle;
  v6 = id;
  v7 = jmsSeqChange(SeqHandle, &ProcessData->pSeqUnit, 1, v6);
  if (!v7)
  {
    Instance = _get_Instance();
    if (!op_Inequality(Instance, 0, 0))
      return v7;
    if (ProcessData->PmvPID)
    {
      gohUnityDraw(1);
      v9 = *((void *)_get_Instance()[18].monitor + 2);
      if (get_activeSelf(v9, 0))
        SetActive(v9, 0, 0);
      v10 = _get_Instance();
      BackObjActive(v10, 1, 0);
      v11 = _get_Instance();
      TitleDraw(v11[17].monitor, 1, 0, 0);
    }
  }
  return v7;
}

// 0x1bddb90
dds3ProcessFunc_t gohRootUpdateProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  jmsSeqHandle_t *monitor;
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
  fclUpdateMessage();
  monitor = ProcessData[1].monitor;
  v6 = id;
  return jmsSeqChange(monitor, &ProcessData[2], 2, v6);
}

// 0x1bd4100
s32 gohGetErrorType(gohData_t *pData) {
  sdatUnitWork_t *BirthDevil;
  bool *cmbTblErrorType;
  s32 level;

  if ((u32)(pData->m_eCombineType2 - 3) >= 2)
  {
    gohGetSelDevilID(pData, 0);
    gohGetSelDevilID(pData, 1);
    if (pData->combStSeq == 1)
      return 0;
    goto LABEL_10;
  }
  if (pData->combStSeq == 1)
    return 0;
LABEL_10:
  BirthDevil = pData->BirthDevil;
  cmbTblErrorType = BirthDevil->cmbTblErrorType;
  if (cmbTblErrorType[1])
    return 1;
  if (cmbTblErrorType[0])
    return 1;
  if (cmbTblErrorType[3])
    return 1;
  if (pData->m_eResultType == 5)
    return 0;
  level = BirthDevil->level;
  return level > GBWK->player->para->level && pData->m_eResultType != 5;
}

// 0x1bd3e30
s32 gohCheckDevilError(gohData_t *pData) {
  sdatUnitWork_t *BirthDevil;
  bool *cmbTblErrorType;
  jmsSeqUnit_t *p_pSeqUnit;
  jmsSeqUnit_t *gohSeqUnit_local;
  s32 restoreMoney;
  Il2CppObject *v12;
  char *v13;
  char *v14;
  s32 level;
  s32 data;

  if ((u32)(pData->m_eCombineType2 - 3) >= 2)
  {
    gohGetSelDevilID(pData, 0);
    gohGetSelDevilID(pData, 1);
    if (pData->combStSeq == 1)
      return 0;
    goto LABEL_10;
  }
  if (pData->combStSeq == 1)
    return 0;
LABEL_10:
  BirthDevil = pData->BirthDevil;
  cmbTblErrorType = BirthDevil->cmbTblErrorType;
  if (cmbTblErrorType[1])
  {
    pData->ErrorType = 1;
    p_pSeqUnit = &pData->pSeqUnit;
  }
  else
  {
    if (cmbTblErrorType[0])
    {
      restoreMoney = BirthDevil->restoreMoney;
      pData->ErrorType = 5;
      data = restoreMoney;
      v12 = Box(s32, &data);
      v13 = Format("{0}", v12, 0);
      v14 = itfConvertToDelimitedNum(v13);
      fclSetMessageVar(0, v14);
      p_pSeqUnit = &pData->pSeqUnit;
      goto LABEL_13;
    }
    if (cmbTblErrorType[3])
    {
      pData->ErrorType = 6;
      p_pSeqUnit = &pData->pSeqUnit;
      goto LABEL_13;
    }
    if (pData->m_eResultType == 5)
      return 0;
    level = BirthDevil->level;
    if (level <= GBWK->player->para->level || pData->m_eResultType == 5)
      return 0;
    pData->ErrorType = 2;
    p_pSeqUnit = &pData->pSeqUnit;
  }
LABEL_13:
  gohSeqUnit_local = gohSeqUnit;
  jmsSeqJumpAndFree(p_pSeqUnit, &gohSeqUnit_local[22]);
  return 1;
}

// 0x1bd4290
void gohStartBirthDevilStatus(gohData_t *pData) {
  u32 v3;
  s32 m_iStatusType;
  u32 v6;
  char v7;
  s32 v8;
  bool v9;
  s32 v10;
  s32 v11;
  sdatUnitWork_t *combiDevil1;
  s32 m_iSelectNewSwordNo;
  s64 v14;
  s32 stInputWait;
  s32 ModeSq;
  s32 m_eCombineType2;
  bool v19;
  s32 v20;
  s32 v23;
  s32 combStSeq;
  sdatPlayerUnitWork_t *Player;
  sdatPlayerUnitWork_t *v28;
  sdatPlayerUnitWork_t *v31;
  sdatPlayerUnitWork_t *v34;
  char v39;
  s32 v40;
  char v41;
  s32 DevilStatusFlag;
  sdatUnitWork_t *stock_id;
  void *m_pDevSelList1;
  s32 v46;
  sdatUnitWork_t *v48;
  void *m_pDevSelList2;
  s32 v50;
  s32 v53;
  s32 v54;
  sdatUnitWork_t *v56;
  void *v57;
  s32 v58;
  sdatUnitWork_t *v60;
  void *v61;
  s32 v62;
  Il2CppClass **v63;
  Il2CppClass **v64;
  void *v65;
  s32 v66;
  void *v67;
  s32 v68;
  s32 m_eCombineType;
  sdatUnitWork_t *v72;
  sdatUnitWork_t *v73;
  s32 devilid;
  s32 v75;
  sdatUnitWork_t *combiDevil2;
  s32 v77;

  v3 = jmsChkCommonInput(0x3FFu);
  m_iStatusType = pData->m_iStatusType;
  v6 = v3;
  if ((u32)m_iStatusType >= 2)
  {
    if (m_iStatusType == 2)
    {
      v7 = 0;
      stInputWait = pData->stInputWait;
      v9 = __OFSUB__(stInputWait, 1);
      v10 = stInputWait - 1;
      if (v10 < 0 != v9)
        goto LABEL_10;
    }
    else
    {
      m_iStatusType = 0;
      v7 = 1;
      v20 = pData->stInputWait;
      v9 = __OFSUB__(v20, 1);
      v10 = v20 - 1;
      if (v10 < 0 != v9)
        goto LABEL_10;
    }
LABEL_9:
    pData->stInputWait = v10;
    goto LABEL_10;
  }
  cmpUDHelpNon(1);
  v7 = 0;
  m_iStatusType = 2;
  v8 = pData->stInputWait;
  v9 = __OFSUB__(v8, 1);
  v10 = v8 - 1;
  if (v10 < 0 == v9)
    goto LABEL_9;
LABEL_10:
  if ((v7 & 1) != 0)
    goto LABEL_11;
  ModeSq = cmpGetModeSq();
  if (ModeSq != 2)
  {
    if (ModeSq != 1)
    {
      if (ModeSq)
        goto LABEL_11;
      cmpMouseSetSklType();
      m_eCombineType2 = pData->m_eCombineType2;
      if (m_eCombineType2 == 1)
      {
        v19 = 1;
        if (pData->combStSeq != 1)
          goto LABEL_101;
      }
      else if (m_eCombineType2 == 4)
      {
        v19 = !resultCheck;
        if (pData->combStSeq != 1)
        {
LABEL_101:
          if (CHECK_REP(42756, 1))
          {
            if (pData->stInputWait > 0)
              return;
            v39 = !v19;
            if (pData->m_iStatusType != 2)
              v39 = 1;
            if ((v39 & 1) != 0)
              goto LABEL_11;
            v40 = pData->DevilStatusFlag - 1;
            if (v40 < 0)
              v40 = m_iStatusType;
            goto LABEL_117;
          }
          if (CHECK_REP(42757, 1))
          {
            if (pData->stInputWait > 0)
              return;
            v41 = !v19;
            if (pData->m_iStatusType != 2)
              v41 = 1;
            if ((v41 & 1) != 0)
              goto LABEL_11;
            DevilStatusFlag = pData->DevilStatusFlag;
            if (DevilStatusFlag + 1 <= m_iStatusType)
              v40 = DevilStatusFlag + 1;
            else
              v40 = 0;
LABEL_117:
            pData->DevilStatusFlag = v40;
            pData->Flag &= ~0x10000u;
            SE(3);
            goto LABEL_11;
          }
          if ((v6 & 0x100) == 0)
          {
            if ((v6 & 0x200) == 0)
            {
              if (!CHECK_TRIG(46082, 1))
                goto LABEL_11;
              goto LABEL_124;
            }
            goto LABEL_210;
          }
          goto LABEL_179;
        }
      }
      else
      {
        v19 = 0;
        if (pData->combStSeq != 1)
          goto LABEL_101;
      }
      if (resultCheck)
        goto LABEL_101;
      if (nativeSkillStep)
      {
        goto LABEL_130;
      }
      nativeSkillStep = 1;
LABEL_130:
      GohSkillChangeUpdate(pData);
      if (pData->combStSeq == 1)
        return;
      goto LABEL_11;
    }
    if (pData->combStSeq == 1)
    {
      GohNativeSkillSet(pData, v6);
      goto LABEL_11;
    }
    cmpSklCsrMouse(0);
    cmpMouseSetSklType();
    if ((v6 & 0x10) != 0)
    {
      cmpSklCsrU();
    }
    else if ((v6 & 0x20) != 0)
    {
      cmpSklCsrD();
    }
    else if ((v6 & 0x40) != 0)
    {
      cmpSklCsrL();
    }
    else if ((v6 & 0x80) != 0)
    {
      cmpSklCsrR();
    }
    else
    {
      if ((v6 & 0x100) != 0)
      {
LABEL_179:
        cmpSklTypeSub();
        goto LABEL_11;
      }
      if ((v6 & 0x200) != 0)
      {
LABEL_210:
        cmpSklTypeAdd();
        goto LABEL_11;
      }
      if ((!CHECK_TRIG(45571, 1) || (u32)(pData->m_iStatusType - 5) > 2) && (!CHECK_TRIG(45826, 1) || (u32)(pData->m_iStatusType - 5) < 3))
      {
        if ((v6 & 2) == 0)
          goto LABEL_11;
        goto LABEL_46;
      }
      if (cmpOpenOmoedeLog())
      {
LABEL_124:
        cmpIncModeSq(0);
        goto LABEL_11;
      }
    }
    goto LABEL_11;
  }
  if ((v6 & 2) != 0)
  {
LABEL_46:
    cmpDecModeSq(0);
    goto LABEL_11;
  }
  cmpMemSklCurUpdate();
LABEL_11:
  if ((pData->Flag & 0x10000) == 0)
  {
    switch (pData->m_iStatusType)
    {
      case 0:
        v11 = pData->m_eCombineType2;
        if (v11 != 4 && v11 != 3)
        {
          stock_id = GBWK->player->stock_id;
          m_pDevSelList1 = pData->m_pDevSelList1;
          if (m_pDevSelList1)
            v46 = ITEMIDX(m_pDevSelList1);
          else
            v46 = -1;
          v63 = &stock_id->obj.klass + v46;
          m_iSelectNewSwordNo = 0;
          v14 = 513;
          goto LABEL_221;
        }
        combiDevil1 = pData->combiDevil1;
        m_iSelectNewSwordNo = 0;
        v14 = 513;
        goto LABEL_222;
      case 1:
        v23 = pData->m_eCombineType2;
        if (v23 == 4 || v23 == 3)
        {
          combiDevil1 = pData->combiDevil2;
          m_iSelectNewSwordNo = 0;
          v14 = 514;
        }
        else
        {
          v48 = GBWK->player->stock_id;
          m_pDevSelList2 = pData->m_pDevSelList2;
          if (m_pDevSelList2)
            v50 = ITEMIDX(m_pDevSelList2);
          else
            v50 = -1;
          v64 = &v48->obj.klass + v50;
          v65 = pData->m_pDevSelList1;
          combiDevil1 = v64[4];
          if (v65)
            v66 = ITEMIDX(v65);
          else
            v66 = -1;
          v67 = pData->m_pDevSelList2;
          if (v67)
            v68 = ITEMIDX(v67);
          else
            v68 = -1;
          m_iSelectNewSwordNo = 0;
          if (v66 == v68)
            v14 = 513;
          else
            v14 = 514;
        }
        goto LABEL_222;
      case 3:
        combiDevil1 = pData->BirthDevil;
        m_iSelectNewSwordNo = 0;
        v14 = 0x8000000;
        goto LABEL_222;
      case 4:
        Player = pData->Player;
        v14 = 268697601;
        ClassCopy(Player, GBWK->player, 0);
        m_iSelectNewSwordNo = pData->m_iSelectNewSwordNo;
        datSetPlayerUnitSword(pData->Player, m_iSelectNewSwordNo, 0);
        combiDevil1 = pData->Player->para;
        goto LABEL_222;
      case 5:
        v28 = pData->Player;
        ClassCopy(v28, GBWK->player, 0);
        m_iSelectNewSwordNo = pData->m_iSelectNewSwordNo;
        g_equipNo = m_iSelectNewSwordNo;
        combiDevil1 = pData->Player->para;
        v14 = 268697856;
        goto LABEL_222;
      case 6:
        v31 = pData->Player;
        ClassCopy(v31, GBWK->player, 0);
        m_iSelectNewSwordNo = pData->m_iSelectNewSwordNo;
        v14 = 0x110040100LL;
        g_equipNo = m_iSelectNewSwordNo;
        combiDevil1 = pData->Player->para;
        goto LABEL_222;
      case 7:
        v34 = pData->Player;
        ClassCopy(v34, GBWK->player, 0);
        m_iSelectNewSwordNo = pData->m_iSelectNewSwordNo;
        v14 = 402915329;
        g_equipNo = m_iSelectNewSwordNo;
        combiDevil1 = pData->Player->para;
        goto LABEL_222;
      default:
        combStSeq = pData->combStSeq;
        if (combStSeq)
        {
          if (combStSeq == 1)
          {
            if (!resultCheck)
            {
              GohInitSkillChange(pData, 1);
              goto LABEL_163;
            }
          }
          else
          {
          }
          if (resultCheck)
          {
            v53 = setNativeSkillList->_version + 1;
            setNativeSkillList->_size = 0;
            setNativeSkillList->_version = v53;
          }
        }
        else
        {
          GohNativeSkillSetAllClear(pData);
        }
LABEL_163:
        v54 = pData->DevilStatusFlag;
        if (pData->m_eCombineType2 == 4)
        {
          if (v54 == 1)
          {
            combiDevil1 = pData->combiDevil1;
            m_iSelectNewSwordNo = 0;
            v14 = 1;
            goto LABEL_222;
          }
          if (v54 == 2)
          {
            combiDevil1 = pData->combiDevil2;
            m_iSelectNewSwordNo = 0;
LABEL_218:
            v14 = 2;
            goto LABEL_222;
          }
        }
        else
        {
          if (v54 == 1)
          {
            v60 = GBWK->player->stock_id;
            v61 = pData->m_pDevSelList1;
            if (v61)
              v62 = ITEMIDX(v61);
            else
              v62 = -1;
            v63 = &v60->obj.klass + v62;
            m_iSelectNewSwordNo = 0;
            v14 = 1;
LABEL_221:
            combiDevil1 = v63[4];
LABEL_222:
            m_eCombineType = pData->m_eCombineType;
            if (m_eCombineType == 2)
            {
              cmpSetMitamaCombDvl(0);
              v14 |= 0x10040000u;
              goto LABEL_226;
            }
            if (m_eCombineType != 1)
            {
              if (m_eCombineType)
              {
LABEL_226:
                gohStartStatusDraw(pData, combiDevil1, v14, m_iSelectNewSwordNo);
                return;
              }
              goto LABEL_236;
            }
            if (pData->m_eResultType != 5)
              goto LABEL_235;
            if (!resultCheck)
            {
              v14 |= 0x10020000u;
              if (combiDevil1->restoreMoney)
              {
                v73 = pData->combiDevil1;
                if (v73)
                {
                  if (pData->combiDevil2)
                  {
                    devilid = v73->devilid;
                    v75 = sub_1B6D720(devilid);
                    combiDevil2 = pData->combiDevil2;
                    if (v75 != 9)
                    {
                      v77 = combiDevil2->devilid;
                      if ((u32)sub_1B6D720(v77) != 9)
                        goto LABEL_236;
                      combiDevil2 = pData->combiDevil1;
                    }
                    v72 = combiDevil2;
LABEL_239:
                    cmpSetMitamaCombDvl(v72);
                    goto LABEL_226;
                  }
                }
              }
            }
            else
            {
LABEL_235:
              v14 |= 0x10010000u;
            }
LABEL_236:
            v72 = 0;
            goto LABEL_239;
          }
          if (v54 == 2)
          {
            v56 = GBWK->player->stock_id;
            v57 = pData->m_pDevSelList2;
            if (v57)
              v58 = ITEMIDX(v57);
            else
              v58 = -1;
            m_iSelectNewSwordNo = 0;
            combiDevil1 = v56[v58];
            goto LABEL_218;
          }
        }
        combiDevil1 = pData->BirthDevil;
        m_iSelectNewSwordNo = 0;
        v14 = 256;
        goto LABEL_222;
    }
  }
}

// 0x1bd5bf0
void gohSeqReturn(gohData_t *pData) {
  jmsSeqUnit_t *v3;
  jmsSeqUnit_t *v5;
  jmsSeqUnit_t *p_pSeqUnit;
  jmsSeqUnit_t *gohSeqUnit_local;

  if (pData->m_eCombineType != 2)
  {
    GohReturnNativeSklSet(pData);
    GohInitSkillChange(pData, 0);
    p_pSeqUnit = &pData->pSeqUnit;
    resultCheck = 0;
    gohSeqUnit_local = gohSeqUnit;
    jmsSeqJumpAndFree(p_pSeqUnit, &gohSeqUnit_local[12]);
    return;
  }
  v3 = &pData->pSeqUnit;
  v5 = gohSeqUnit;
  jmsSeqJumpAndFree(v3, &v5[11]);
}

// 0x1bddcf0
void gohAppendNewDevil(gohData_t *pData) {
  s32 devilid;
  s32 SelDevilID;
  u32 devilUniq1;
  s32 v9;
  s32 kuda_id;
  s32 *v13;
  s32 *EventBit;
  sdatUnitWork_t *BirthDevil;
  void *DevilReportStok;
  s32 v19;
  s32 size;
  bool v21;
  bool v24;
  void *CombineResultAllAsync;

  if (pData->m_eCombineType2 == 4)
  {
    devilid = pData->combiDevil1->devilid;
    SelDevilID = pData->combiDevil2->devilid;
    devilUniq1 = pData->devilUniq1;
    goto LABEL_10;
  }
  devilid = gohGetSelDevilID(pData, 0);
  SelDevilID = gohGetSelDevilID(pData, 1);
  devilUniq1 = pData->devilUniq1;
LABEL_10:
  datDelDevil(devilid, devilUniq1);
  datDelDevil(SelDevilID, pData->devilUniq2);
  v9 = pData->BirthDevil->devilid;
  kuda_id = sBtlGetDevilData(v9, -1)->kuda_id;
  if (kuda_id == 8)
  {
    EventBit = GBWK->EventBit;
    EventBit[65] |= 0x4000u;
    goto LABEL_28;
  }
  if (kuda_id != 9)
  {
    goto LABEL_28;
  }
  v13 = GBWK->EventBit;
  v13[65] |= 0x8000u;
LABEL_28:
  BirthDevil = pData->BirthDevil;
  BirthDevil->vice = 0;
  DevilReportStok = BirthDevil->DevilReportStok;
  BirthDevil->restoreMoney = 0;
  v19 = GBWK->nakama_uniq_cnt + 1;
  GBWK->nakama_uniq_cnt = v19;
  size = DevilReportStok->_size;
  LODWORD(GBWK) = DevilReportStok->_version;
  BirthDevil->uniq_code = v19;
  DevilReportStok->_size = 0;
  DevilReportStok->_version = (u32)GBWK + 1;
  if (size >= 1)
  {
    Clear(DevilReportStok->_items, 0, size, 0);
    BirthDevil = pData->BirthDevil;
  }
  *(u16 *)&BirthDevil->TakaraCnt = 0;
  BirthDevil->TakumiCnt = 0;
  datAddDevilUnit(BirthDevil);
  v21 = (pData->gohKarteSeq->klass->vtable._70_RegistDevilSub.methodPtr)(pData->gohKarteSeq, pData->BirthDevil, pData->gohKarteSeq->klass->vtable._70_RegistDevilSub.method) == -1;
  v24 = !v21;
  pData->combKarteNewReg = v24;
  pData->resultTblChange = 0;
  allUnitTblCreated = 0;
  pData->Flag &= ~0x100000u;
  CombineResultAllAsync = gohCreateCombineResultAllAsync(pData);
  pData->result2Task = CombineResultAllAsync;
  pData->SelDevil1 = devilid;
  pData->SelDevil2 = SelDevilID;
}

// 0x1bd6f90
void gohCyuuseiCombLastCalc(gohData_t *pData) {
  jmsSeqUnit_t *gohSeqUnit_local;
  sdatUnitWork_t *combiDevil1;
  sdatUnitWork_t *combiDevil2;
  s32 restoreMoney;
  s32 v8;
  s32 devilid;
  void *m_pDevSelList1;
  void *m_pDevSelList2;
  jmsSeqUnit_t *p_pSeqUnit;
  jmsSeqUnit_t *v18;

  if ((pData->Flag & 0x20000) != 0)
  {
    if (gohGetKindNo())
      goto LABEL_4;
    goto LABEL_37;
  }
  pData->BonusFlag = -1;
  if (pData->m_eCombineType != 2)
  {
    GohSetNativeSkill(pData);
    if (pData->m_eCombineType2 == 4)
    {
      combiDevil1 = pData->combiDevil1;
      combiDevil2 = pData->combiDevil2;
      gohChkAccident(pData);
      pData->SelDevil1 = combiDevil1->devilid;
      restoreMoney = combiDevil1->restoreMoney;
      pData->SelDevil2 = combiDevil2->devilid;
      v8 = combiDevil2->restoreMoney;
      datAddMoney(-(restoreMoney + v8));
      devilid = combiDevil1->devilid;
      SetDlcDvlKarteF(devilid);
      SetDlcDvlKarteF(combiDevil2->devilid);
LABEL_35:
      gohAddCombiCount(1);
      goto LABEL_36;
    }
    m_pDevSelList1 = pData->m_pDevSelList1;
    if (m_pDevSelList1)
      ITEMIDX(m_pDevSelList1);
    m_pDevSelList2 = pData->m_pDevSelList2;
    if (m_pDevSelList2)
      ITEMIDX(m_pDevSelList2);
    gohChkAccident(pData);
    pData->SelDevil1 = gohGetSelDevilID(pData, 0);
    pData->SelDevil2 = gohGetSelDevilID(pData, 1);
    goto LABEL_35;
  }
  frSetVariableRequest(4, 0);
  gohAppendSword(pData->m_iSelectNewSwordNo, 1);
LABEL_36:
  pData->Flag |= 0x20000u;
  if (gohGetKindNo())
  {
LABEL_4:
    gohSeqUnit_local = gohSeqUnit;
    jmsSeqJumpAndFree(&pData->pSeqUnit, &gohSeqUnit_local[15]);
LABEL_60:
    pData->Flag &= ~0x20000u;
    return;
  }
LABEL_37:
  if (gohGetTypeCnt() && !gohGetEndFlag())
  {
    gohAccidentDevil(pData);
  }
  if (cfgGetConfigGAME(15, 0) == 1)
  {
    if (pData->haveSword && pData->m_eCombineType == 2)
    {
      pData->Flag &= ~0x20000u;
      p_pSeqUnit = &pData->pSeqUnit;
      v18 = gohSeqUnit;
      jmsSeqJumpAndFree(p_pSeqUnit, &v18[25]);
      return;
    }
  }
  if (gohCyuuseiStartDirection(pData))
    goto LABEL_60;
}

// 0x1bd8860
s32 gohRecoverExec(gohData_t *pData) {
  s32 v3;
  gohGeneralList_t *GeneralList;
  sdatPlayerUnitWork_t *m_pPlayer;
  bool v6;
  s32 v7;
  s32 m_PlayerVal;
  gohGeneralList_t *v10;
  sdatUnitWork_t *v11;
  sdatParaWork_t *v12;
  sdatUnitWork_t *para;
  sdatParaWork_t *now;
  gohGeneralList_t *v16;
  void *m_pSelList;
  gohGeneralList_t *v19;
  sdatPlayerUnitWork_t *v20;
  s32 m_DevilCnt;

  v3 = ITEMIDX(pData->m_pSelList);
  GeneralList = pData->GeneralList;
  m_pPlayer = GeneralList->m_pPlayer;
  if (m_pPlayer)
    v6 = v3 == 0;
  else
    v6 = 0;
  if (v6)
  {
    m_PlayerVal = GeneralList->m_PlayerVal;
    if (GBWK->player->gold < m_PlayerVal)
      return -1;
    para = m_pPlayer->para;
    para->badstatus = 0;
    now = para->now;
    v16 = pData->GeneralList;
    LODWORD(para) = now->maxhp;
    v16->m_pPlayer = 0;
    now->hp = (s32)para;
    goto LABEL_19;
  }
  v7 = v3 - (m_pPlayer != 0);
  m_PlayerVal = GeneralList->m_DevilVal[v7];
  if (GBWK->player->gold < m_PlayerVal)
    return -1;
  v10 = pData->GeneralList;
  v11 = v10->m_pDevil[v7];
  v12 = v11->now;
  v11->badstatus = 0;
  v12->hp = v12->maxhp;
  v12->mp = v12->maxmp;
  gohDelDevilFromGeneralList(v10, v7);
LABEL_19:
  m_pSelList = pData->m_pSelList;
  GBWK->player->gold -= m_PlayerVal;
  jmsDelCmdMenuItem(m_pSelList);
  v19 = pData->GeneralList;
  v20 = v19->m_pPlayer;
  m_DevilCnt = v19->m_DevilCnt;
  if (v20)
    return m_DevilCnt + 1;
  else
    return m_DevilCnt;
}

// 0x1bde070
dds3ProcessFunc_t EndProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  dds3ProcessID_t *v7;
  s32 v10;
  dds3ProcessID_t *monitor;
  u32 v12;
  dds3ProcessFunc_t v15;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  if (cmpChkStatusModelLoadStat() == 1)
    return 0;
  v7 = id;
  if (gohScrControl(id))
    return 0;
  LODWORD(ProcessData[10].klass) = 1;
  if (((s64)ProcessData[1].klass & 0x40) == 0)
  {
    dds3FadeOut(0, 0, 0, 0x1Eu);
    v10 = LODWORD(ProcessData[1].klass) | 0x40;
LABEL_22:
    LODWORD(ProcessData[1].klass) = v10;
    return 0;
  }
  if (dds3FadeCheck())
    return 0;
  monitor = ProcessData[2].monitor;
  if (monitor)
  {
    if (((s64)ProcessData[1].klass & 0x80) == 0)
    {
      if (!v12)
      evtEnd(monitor);
      v10 = LODWORD(ProcessData[1].klass) | 0x80;
      goto LABEL_22;
    }
    if (!v12)
    if (evtCheckProcess())
      return 0;
    ProcessData[2].monitor = 0;
  }
  fclFilterOFF();
  p2sdUnLoadAllSMGFile();
  RemoveKey(textAssetName);
  v15 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
  _ctor(v15, 0, Method_Project_Kernel_DDS3_PROC_END__, 0);
  return v15;
}

// 0x1bd6ec0
bool gohSwordShortCutCheck(gohData_t *pData, bool typeChk) {
  bool result;

  if (cfgGetConfigGAME(15, 0) != 1)
    return 0;
  result = pData->haveSword;
  if (pData->haveSword && typeChk)
    return pData->m_eCombineType == 2;
  return result;
}

// 0x1bde420
s32 gohBakNmlInit(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  dds3ProcessID_t *MenuPID;
  Il2CppObject *Instance;
  Il2CppObject *v7;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  GohSkillChangeSettingDestroy();
  if (!ProcessData)
  HIDWORD(ProcessData[13].klass) = 0;
  *(u16 *)&s_bDrawBack = 0;
  MenuPID = gohGetMenuPID();
  itfMenuSetInitSelectID(MenuPID, 6);
  gohSetSelectIndex(6);
  Instance = _get_Instance();
  AllListClear(Instance[19].klass->_1.events, 0);
  v7 = _get_Instance();
  AllListClear(v7[19].klass->_1.typeMetadataHandle, 0);
  return 1;
}

// 0x1bde600
s32 gohBakNmlDestroy(dds3ProcessID_t *PID) {
  dds3ProcessID_t *id;

  id = PID;
  dds3GetProcessData(id);
  return 1;
}

// 0x1bde680
dds3ProcessFunc_t gohBakNmlCalcProcess(dds3ProcessID_t *PID) {
  gohData_t *ProcessData;
  jmsSeqUnit_t *p_pSeqUnit;
  jmsSeqHandle_t *SeqHandle;
  dds3ProcessID_t *v7;
  dds3ProcessFunc_t v8;
  u32 CalcStep;
  Il2CppObject *Instance;
  jmsSeqUnit_t *gohSeqUnit_local;
  jmsSeqUnit_t *v15;
  jmsSeqUnit_t *v17;
  dds3ProcessID_t *MenuPID;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  p_pSeqUnit = &ProcessData->pSeqUnit;
  SeqHandle = ProcessData->SeqHandle;
  v7 = id;
  v8 = jmsSeqChange(SeqHandle, &ProcessData->pSeqUnit, 0, v7);
  if (!v8)
  {
    if (datGetStockDevilNums(0) > 1)
    {
      MenuPID = gohGetMenuPID();
      dds3GetProcessData(MenuPID);
      CalcStep = ProcessData->CalcStep;
      if (CalcStep)
      {
        if (CalcStep > 6)
        {
          gohCreateDevSelList(ProcessData);
          Instance = _get_Instance();
          TitleOff(Instance[17].monitor, 0);
          gohSeqUnit_local = gohSeqUnit;
          v15 = &gohSeqUnit_local[3];
          goto LABEL_27;
        }
        goto LABEL_31;
      }
      ProcessData->searchi = 0;
      ProcessData->m_eCombineType = 1;
      ProcessData->m_eCombineType2 = 1;
LABEL_31:
      gohCreateCombineResult(ProcessData, CalcStep);
      ++ProcessData->CalcStep;
      return v8;
    }
    v17 = gohSeqUnit;
    v15 = &v17[2];
LABEL_27:
    jmsSeqJumpAndFree(p_pSeqUnit, v15);
    return v8;
  }
  return v8;
}

// 0x1bde9c0
dds3ProcessFunc_t gohBakNmlDrawProcess(dds3ProcessID_t *PID) {
  gohData_t *ProcessData;
  jmsSeqHandle_t *SeqHandle;
  dds3ProcessID_t *v6;
  dds3ProcessFunc_t result;
  void *name;
  void *v9;
  void *v10;
  Il2CppObject *Instance;
  Il2CppObject *v12;
  void *v13;
  Il2CppObject *v14;
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
  v6 = id;
  result = jmsSeqChange(SeqHandle, &ProcessData->pSeqUnit, 1, v6);
  if (!result)
  {
    gohModel(ProcessData);
    name = _get_Instance()[19].klass->_1.name;
    if (get_activeSelf(name, 0))
      SetActive(name, 0, 0);
    v9 = _get_Instance()[20].klass->_1.name;
    if (get_activeSelf(v9, 0))
      SetActive(v9, 0, 0);
    v10 = *((void *)_get_Instance()[18].monitor + 2);
    if (get_activeSelf(v10, 0))
      SetActive(v10, 0, 0);
    Instance = _get_Instance();
    CombBackActive(Instance, 0, 0);
    v12 = _get_Instance();
    CombiActive(v12, 0, 0);
    v13 = *((void *)_get_Instance()[19].monitor + 2);
    if (get_activeSelf(v13, 0))
      SetActive(v13, 0, 0);
    v14 = _get_Instance();
    BackObjActive(v14, 1, 0);
    return 0;
  }
  return result;
}

// 0x1bdec50
dds3ProcessFunc_t gohBakNmlUpdateProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  jmsSeqHandle_t *monitor;
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
  monitor = ProcessData[1].monitor;
  v6 = id;
  return jmsSeqChange(monitor, &ProcessData[2], 2, v6);
}

// 0x1bded70
s32 gohBakBakInit(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  dds3ProcessID_t *MenuPID;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  GohSkillChangeSettingDestroy();
  if (!ProcessData)
  HIDWORD(ProcessData[13].klass) = 0;
  *(u16 *)&s_bDrawBack = 0;
  MenuPID = gohGetMenuPID();
  itfMenuSetInitSelectID(MenuPID, 22);
  gohSetSelectIndex(22);
  return 1;
}

// 0x1bdef30
s32 gohBakBakDestroy(dds3ProcessID_t *PID) {
  dds3ProcessID_t *id;

  id = PID;
  dds3GetProcessData(id);
  return 1;
}

// 0x1bdefb0
dds3ProcessFunc_t gohBakBakCalcProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  jmsSeqUnit_t *v5;
  jmsSeqHandle_t *monitor;
  dds3ProcessID_t *v7;
  dds3ProcessFunc_t v8;
  Il2CppObject *v13;
  bool *v17;
  Il2CppObject *Instance;
  jmsSeqUnit_t *gohSeqUnit_local;
  jmsSeqUnit_t *v22;
  tagGOH_MENU_WORK *v23;
  jmsSeqUnit_t *v26;
  dds3ProcessID_t *MenuPID;
  dds3ProcessID_t *id;

  id = PID;
  MenuPID = 0;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  v5 = &ProcessData[2];
  monitor = ProcessData[1].monitor;
  v7 = id;
  v8 = jmsSeqChange(monitor, &ProcessData[2], 0, v7);
  if (v8)
    return v8;
  if (!dds3ExistProcess(g_mainPID))
  {
    goto LABEL_16;
  }
  v13 = dds3GetProcessData(g_mainPID);
  if (!v13)
    return v8;
  v23 = v13;
  if (!v13[1].monitor)
    return v8;
  gohChkEnableSelect(v23);
LABEL_16:
  MenuPID = gohGetMenuPID();
  dds3GetProcessData(MenuPID);
  if (gohCheckOpen(21))
    goto LABEL_62;
  if (gohCheckOpen(22))
  {
LABEL_62:
    if (datGetStockDevilNums(0) >= 2)
    {
      if (gohBackCombMenuCheck())
      {
        LOBYTE(ProcessData[31].klass) = 0;
        LODWORD(ProcessData[13].klass) = 1;
        HIDWORD(ProcessData[27].monitor) = 3;
        resultCsr = 0;
        sortCsr = 0;
        v17 = NewSpecific(bool, 6u);
        sortSets = v17;
        sortSets[0] = 1;
        Instance = _get_Instance();
        TitleOff(Instance[17].monitor, 0);
        gohSeqUnit_local = gohSeqUnit;
        v22 = &gohSeqUnit_local[7];
        goto LABEL_56;
      }
    }
    v26 = gohSeqUnit;
    v22 = &v26[2];
LABEL_56:
    jmsSeqJumpAndFree(v5, v22);
  }
  return v8;
}

// 0x1bdf4a0
dds3ProcessFunc_t gohBakBakDrawProcess(dds3ProcessID_t *PID) {
  gohData_t *ProcessData;
  jmsSeqHandle_t *SeqHandle;
  dds3ProcessID_t *v6;
  dds3ProcessFunc_t result;
  void *name;
  void *v9;
  void *v10;
  Il2CppObject *Instance;
  Il2CppObject *v12;
  void *v13;
  Il2CppObject *v14;
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
  v6 = id;
  result = jmsSeqChange(SeqHandle, &ProcessData->pSeqUnit, 1, v6);
  if (!result)
  {
    gohModel(ProcessData);
    name = _get_Instance()[19].klass->_1.name;
    if (get_activeSelf(name, 0))
      SetActive(name, 0, 0);
    v9 = _get_Instance()[20].klass->_1.name;
    if (get_activeSelf(v9, 0))
      SetActive(v9, 0, 0);
    v10 = *((void *)_get_Instance()[18].monitor + 2);
    if (get_activeSelf(v10, 0))
      SetActive(v10, 0, 0);
    Instance = _get_Instance();
    CombBackActive(Instance, 0, 0);
    v12 = _get_Instance();
    CombiActive(v12, 0, 0);
    v13 = *((void *)_get_Instance()[19].monitor + 2);
    if (get_activeSelf(v13, 0))
      SetActive(v13, 0, 0);
    v14 = _get_Instance();
    BackObjActive(v14, 1, 0);
    return 0;
  }
  return result;
}

// 0x1bdf730
dds3ProcessFunc_t gohBakBakUpdateProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  jmsSeqHandle_t *monitor;
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
  monitor = ProcessData[1].monitor;
  v6 = id;
  return jmsSeqChange(monitor, &ProcessData[2], 2, v6);
}

// 0x1bdf850
s32 gohBakSearchInit(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  dds3ProcessID_t *MenuPID;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  GohSkillChangeSettingDestroy();
  if (!ProcessData)
  HIDWORD(ProcessData[13].klass) = 0;
  *(u16 *)&s_bDrawBack = 0;
  MenuPID = gohGetMenuPID();
  itfMenuSetInitSelectID(MenuPID, 21);
  gohSetSelectIndex(21);
  return 1;
}

// 0x1bdfa10
s32 gohBakSearchDestroy(dds3ProcessID_t *PID) {
  dds3ProcessID_t *id;

  id = PID;
  dds3GetProcessData(id);
  return 1;
}

// 0x1bdfa90
dds3ProcessFunc_t gohBakSearchCalcProcess(dds3ProcessID_t *PID) {
  gohData_t *ProcessData;
  jmsSeqUnit_t *p_pSeqUnit;
  jmsSeqHandle_t *SeqHandle;
  dds3ProcessID_t *v7;
  dds3ProcessFunc_t v8;
  MenuCsrUnitySp *v13;
  MenuCsrUnitySp *v16;
  s32 CalcStep;
  Il2CppObject *v20;
  jmsSeqUnit_t *gohSeqUnit_local;
  tagGOH_MENU_WORK *v23;
  dds3ProcessID_t *MenuPID;
  dds3ProcessID_t *id;

  id = PID;
  MenuPID = 0;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  p_pSeqUnit = &ProcessData->pSeqUnit;
  SeqHandle = ProcessData->SeqHandle;
  v7 = id;
  v8 = jmsSeqChange(SeqHandle, &ProcessData->pSeqUnit, 0, v7);
  if (v8)
    return v8;
  if (!dds3ExistProcess(g_mainPID))
  {
    goto LABEL_17;
  }
  v20 = dds3GetProcessData(g_mainPID);
  if (!v20)
    return v8;
  v23 = v20;
  if (!v20[1].monitor)
    return v8;
  gohChkEnableSelect(v23);
LABEL_17:
  MenuPID = gohGetMenuPID();
  dds3GetProcessData(MenuPID);
  if (gohCheckOpen(21))
    goto LABEL_22;
  if (gohCheckOpen(22))
  {
LABEL_22:
    ProcessData->searchi = 1;
    ProcessData->m_eCombineType = 1;
    v13 = Allocate(MenuCsrUnitySp);
    _ctor(v13, 0);
    searchiCsr = v13;
    v16 = Allocate(MenuCsrUnitySp);
    _ctor(v16, 0);
    conditionCsr = v16;
    CalcStep = ProcessData->CalcStep;
    if (CalcStep == 1)
    {
      if (!GohCreateAllUnitSortTbl(ProcessData))
        return v8;
    }
    else
    {
      if (CalcStep)
      {
        gohSeqUnit_local = gohSeqUnit;
        jmsSeqJumpAndFree(p_pSeqUnit, &gohSeqUnit_local[5]);
        return v8;
      }
      if (!GohCreateAllUnitSortTbl(ProcessData))
      {
        ProcessData->CalcStep = 1;
        return v8;
      }
    }
    ProcessData->CalcStep = 2;
  }
  return v8;
}

// 0x1bdff00
dds3ProcessFunc_t gohBakSearchDrawProcess(dds3ProcessID_t *PID) {
  gohData_t *ProcessData;
  jmsSeqHandle_t *SeqHandle;
  dds3ProcessID_t *v6;
  dds3ProcessFunc_t result;
  void *name;
  void *v9;
  void *v10;
  Il2CppObject *Instance;
  Il2CppObject *v12;
  void *v13;
  Il2CppObject *v14;
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
  v6 = id;
  result = jmsSeqChange(SeqHandle, &ProcessData->pSeqUnit, 1, v6);
  if (!result)
  {
    gohModel(ProcessData);
    name = _get_Instance()[19].klass->_1.name;
    if (get_activeSelf(name, 0))
      SetActive(name, 0, 0);
    v9 = _get_Instance()[20].klass->_1.name;
    if (get_activeSelf(v9, 0))
      SetActive(v9, 0, 0);
    v10 = *((void *)_get_Instance()[18].monitor + 2);
    if (get_activeSelf(v10, 0))
      SetActive(v10, 0, 0);
    Instance = _get_Instance();
    CombBackActive(Instance, 0, 0);
    v12 = _get_Instance();
    CombiActive(v12, 0, 0);
    v13 = *((void *)_get_Instance()[19].monitor + 2);
    if (get_activeSelf(v13, 0))
      SetActive(v13, 0, 0);
    v14 = _get_Instance();
    BackObjActive(v14, 1, 0);
    return 0;
  }
  return result;
}

// 0x1be0190
dds3ProcessFunc_t gohBakSearchUpdateProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  jmsSeqHandle_t *monitor;
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
  monitor = ProcessData[1].monitor;
  v6 = id;
  return jmsSeqChange(monitor, &ProcessData[2], 2, v6);
}

// 0x1be02b0
s32 gohBakTreeInit(dds3ProcessID_t *PID) {
  dds3ProcessID_t *MenuPID;
  dds3ProcessID_t *id;

  id = PID;
  dds3GetProcessData(id);
  MenuPID = gohGetMenuPID();
  itfMenuSetInitSelectID(MenuPID, 7);
  gohSetSelectIndex(7);
  return 1;
}

// 0x1be03c0
s32 gohBakTreeDestroy(dds3ProcessID_t *PID) {
  dds3ProcessID_t *id;

  id = PID;
  dds3GetProcessData(id);
  return 1;
}

// 0x1be0440
dds3ProcessFunc_t gohBakTreeCalcProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  jmsSeqHandle_t *monitor;
  dds3ProcessID_t *v6;
  dds3ProcessFunc_t result;
  gohRenkenSelSwordList_t *klass;
  jmsSeqUnit_t *gohSeqUnit_local;
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
  v6 = id;
  result = jmsSeqChange(monitor, &ProcessData[2], 0, v6);
  if (!result)
  {
    gohClear();
    klass = ProcessData[23].klass;
    LODWORD(ProcessData[13].klass) = 2;
    gohSelSwordList(klass);
    gohSeqUnit_local = gohSeqUnit;
    jmsSeqJumpAndFree(&ProcessData[2], &gohSeqUnit_local[11]);
    *(u16 *)&s_bDrawBack = 0;
    return 0;
  }
  return result;
}

// 0x1be0620
dds3ProcessFunc_t gohBakTreeDrawProcess(dds3ProcessID_t *PID) {
  gohData_t *ProcessData;
  jmsSeqHandle_t *SeqHandle;
  dds3ProcessID_t *v6;
  dds3ProcessFunc_t result;
  void *name;
  void *v9;
  void *v10;
  Il2CppObject *Instance;
  Il2CppObject *v12;
  void *v13;
  Il2CppObject *v14;
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
  v6 = id;
  result = jmsSeqChange(SeqHandle, &ProcessData->pSeqUnit, 1, v6);
  if (!result)
  {
    gohModel(ProcessData);
    name = _get_Instance()[19].klass->_1.name;
    if (get_activeSelf(name, 0))
      SetActive(name, 0, 0);
    v9 = _get_Instance()[20].klass->_1.name;
    if (get_activeSelf(v9, 0))
      SetActive(v9, 0, 0);
    v10 = *((void *)_get_Instance()[18].monitor + 2);
    if (get_activeSelf(v10, 0))
      SetActive(v10, 0, 0);
    Instance = _get_Instance();
    CombBackActive(Instance, 0, 0);
    v12 = _get_Instance();
    CombiActive(v12, 0, 0);
    v13 = *((void *)_get_Instance()[19].monitor + 2);
    if (get_activeSelf(v13, 0))
      SetActive(v13, 0, 0);
    v14 = _get_Instance();
    BackObjActive(v14, 1, 0);
    return 0;
  }
  return result;
}

// 0x1be08b0
dds3ProcessFunc_t gohBakTreeUpdateProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  jmsSeqHandle_t *monitor;
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
  monitor = ProcessData[1].monitor;
  v6 = id;
  return jmsSeqChange(monitor, &ProcessData[2], 2, v6);
}

// 0x1be09d0
s32 gohSwordShortCutInit(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  s32 v5;
  sdatPlayerUnitWork_t *v8;
  sdatPlayerUnitWork_t *player;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  *(void **)((char *)&ProcessData[20].monitor + 4) = 0;
  v5 = BYTE3(ProcessData[33].monitor);
  BYTE5(ProcessData[33].monitor) = 0;
  if (!v5)
  {
    player = GBWK->player;
    if (!datSpiritSkillGetMaster(player, tbl[SLOWORD(ProcessData[22].monitor)]->m_hojo))
      return 1;
    goto LABEL_14;
  }
  v8 = GBWK->player;
  if (datRaidouSkillGetMaster(v8, tbl[SLOWORD(ProcessData[22].monitor)]->m_hojo))
  {
LABEL_14:
    BYTE5(ProcessData[33].monitor) = 1;
  }
  return 1;
}

// 0x1be0c50
s32 gohSwordShortCutDestroy(dds3ProcessID_t *PID) {
  dds3ProcessID_t *id;

  id = PID;
  dds3GetProcessData(id);
  return 1;
}

// 0x1be0cd0
dds3ProcessFunc_t gohSwordShortCutCalcProcess(dds3ProcessID_t *PID) {
  gohData_t *ProcessData;
  jmsSeqUnit_t *p_pSeqUnit;
  jmsSeqHandle_t *SeqHandle;
  dds3ProcessID_t *v7;
  dds3ProcessFunc_t v8;
  jmsSeqUnit_t *gohSeqUnit_local;
  jmsSeqUnit_t *v15;
  s32 v16;
  jmsSeqUnit_t *v19;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  p_pSeqUnit = &ProcessData->pSeqUnit;
  SeqHandle = ProcessData->SeqHandle;
  v7 = id;
  v8 = jmsSeqChange(SeqHandle, &ProcessData->pSeqUnit, 0, v7);
  if (v8)
    return v8;
  switch (ProcessData->WorkStat)
  {
    case 0:
      gohCallDrawBack();
      s_bDrawBack = 1;
      if (ProcessData->sklHave)
      {
        cmpChangeWaitMode();
        gohSeqUnit_local = gohSeqUnit;
        v15 = &gohSeqUnit_local[27];
LABEL_39:
        jmsSeqJumpAndFree(p_pSeqUnit, v15);
        return 0;
      }
      ProcessData->sklSet = 1;
      dds3FadeOut(0, 0, 0, 0xAu);
      v16 = 1;
LABEL_43:
      ProcessData->WorkStat = v16;
      return 0;
    case 1:
      if (dds3FadeCheck())
        return v8;
      v16 = 2;
      goto LABEL_43;
    case 2:
      if (dds3FadeCheck())
        return v8;
      if (gohStopStatusDraw(ProcessData, 1, 0) < 2)
        return v8;
      v16 = 3;
      goto LABEL_43;
    case 3:
      v19 = gohSeqUnit;
      v15 = &v19[26];
      goto LABEL_39;
    default:
      return v8;
  }
}

// 0x1be1070
dds3ProcessFunc_t gohSwordShortCutDrawProcess(dds3ProcessID_t *PID) {
  gohData_t *ProcessData;
  jmsSeqHandle_t *SeqHandle;
  dds3ProcessID_t *v6;
  dds3ProcessFunc_t result;
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
  v6 = id;
  result = jmsSeqChange(SeqHandle, &ProcessData->pSeqUnit, 1, v6);
  if (!result)
  {
    gohModel(ProcessData);
    return 0;
  }
  return result;
}

// 0x1be11f0
dds3ProcessFunc_t gohSwordShortCutUpdateProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  jmsSeqHandle_t *monitor;
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
  monitor = ProcessData[1].monitor;
  v6 = id;
  return jmsSeqChange(monitor, &ProcessData[2], 2, v6);
}

// 0x1be1310
s32 gohCombShortCutInit(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
  *(void **)((char *)&ProcessData[20].monitor + 4) = 0;
  if (LODWORD(ProcessData[13].klass) != 2 && ProcessData[16].monitor)
  {
    gohAppendNewDevil(ProcessData);
  }
  return 1;
}

// 0x1be1440
s32 gohCombShortCutDestroy(dds3ProcessID_t *PID) {
  dds3ProcessID_t *id;

  id = PID;
  dds3GetProcessData(id);
  return 1;
}

// 0x1be14c0
dds3ProcessFunc_t gohCombShortCutCalcProcess(dds3ProcessID_t *PID) {
  gohData_t *ProcessData;
  jmsSeqUnit_t *p_pSeqUnit;
  jmsSeqHandle_t *SeqHandle;
  dds3ProcessID_t *v7;
  dds3ProcessFunc_t v8;
  dds3ProcessID_t *PmvPID;
  jmsSeqUnit_t *gohSeqUnit_local;
  dds3Basic_t *basic;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  p_pSeqUnit = &ProcessData->pSeqUnit;
  SeqHandle = ProcessData->SeqHandle;
  v7 = id;
  v8 = jmsSeqChange(SeqHandle, &ProcessData->pSeqUnit, 0, v7);
  if (!v8)
  {
    if (ModelLoad(ProcessData))
      return v8;
    basic = dds3GetActiveScene();
    if (basic)
    {
      dds3SceneBasicVisible(basic, 1);
    }
    ProcessData->combStSeq = 0;
    PmvPID = ProcessData->PmvPID;
    evtIgnoreFade(PmvPID);
    ProcessData->pDirData = 0;
    ProcessStart(0);
    ProcessStart(0);
    fclLinkData(ProcessData->pMsgData);
    gohSeqUnit_local = gohSeqUnit;
    jmsSeqJumpAndFree(p_pSeqUnit, &gohSeqUnit_local[29]);
  }
  return v8;
}

// 0x1be17b0
dds3ProcessFunc_t gohCombShortCutDrawProcess(dds3ProcessID_t *PID) {
  gohData_t *ProcessData;
  jmsSeqHandle_t *SeqHandle;
  dds3ProcessID_t *v6;
  dds3ProcessFunc_t result;
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
  v6 = id;
  result = jmsSeqChange(SeqHandle, &ProcessData->pSeqUnit, 1, v6);
  if (!result)
  {
    gohModel(ProcessData);
    return 0;
  }
  return result;
}

// 0x1be1930
dds3ProcessFunc_t gohCombShortCutUpdateProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  jmsSeqHandle_t *monitor;
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
  monitor = ProcessData[1].monitor;
  v6 = id;
  return jmsSeqChange(monitor, &ProcessData[2], 2, v6);
}
