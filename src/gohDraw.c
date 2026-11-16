#include "types.h"
#include "BST.h"
#include "CMP_STATUS_MODE.h"
#include "CMP_STATUS_SEQ_TYPE.h"
#include "CMP_STATUS_TYPE.h"
#include "GOH_KARTE_SORTMODE.h"
#include "GOH_RESULT_TYPE.h"
#include "ITM_ICON_TYPE.h"
#include "KUDA.h"
#include "SKLID.h"
#include "UiParType.h"
#include "buttonguide.h"
#include "cmdevilresps2_cs.h"
#include "cmpmain.h"
#include "cmpmisc.h"
#include "cmpstatus.h"
#include "dat.h"
#include "dds3kernelcore.h"
#include "dds3kerneldraw.h"
#include "evtbit.h"
#include "evtmoon.h"
#include "fclmisc.h"
#include "fld.h"
#include "gohcalc.h"
#include "gohcombunity.h"
#include "gohdraw.h"
#include "gohinit.h"
#include "gohmain.h"
#include "gohmenu.h"
#include "gohrenken.h"
#include "gohswordhistory.h"
#include "gohswordtree.h"
#include "itf.h"
#include "localize.h"
#include "mdl.h"
#include "raijindlc.h"
#include "sbtlcalc.h"
#include "sbtlitem.h"
#include "sbtlskill.h"
#include "sbtlsub.h"
#include "sdat.h"
#include "sdf3d.h"
#include "spweapon.h"

#define GOH_PANEL_COL 96
#define GOH_CURSOR_COL 1077968960
#define createDevilHelpTextNo 19
#define combiDevilHelpTextNo 28
#define sortHelpOfs 21

typedef struct BarthListPassPar BarthListPassPar;
typedef struct BarthMasyouPassPar BarthMasyouPassPar;
typedef struct CombMenuListPassPar CombMenuListPassPar;
typedef struct GohTextPassManager GohTextPassManager;
typedef struct GohTextUnity GohTextUnity;
typedef struct KarteDevilPassPar KarteDevilPassPar;
typedef struct MaterialListPassPar MaterialListPassPar;
typedef struct PassResultPar PassResultPar;
typedef struct RecoverPassPar RecoverPassPar;
typedef struct RecoverStatusPassPar RecoverStatusPassPar;
typedef struct TreeDetails TreeDetails;
typedef struct TreeIcon TreeIcon;
typedef struct gohData_t gohData_t;
typedef struct gohGeneralList_t gohGeneralList_t;
typedef struct gohRenkenSelMaterialItem_t gohRenkenSelMaterialItem_t;
typedef struct gohRenkenSword_t gohRenkenSword_t;
typedef struct sdatPlayerUnitWork_t sdatPlayerUnitWork_t;
typedef struct sdatUnitWork_t sdatUnitWork_t;
typedef struct sprHandle_t sprHandle_t;
typedef struct tagGOH_MENU_WORK tagGOH_MENU_WORK;

struct GohTextUnity {
    char *text;
    u32 col;
};

struct CombMenuListPassPar {
    GohTextUnity *lv;
    KUDA kuda;
    GohTextUnity *name;
    s32 devilId;
};

struct MaterialListPassPar {
    GohTextUnity *no;
    GohTextUnity *name;
    GohTextUnity *skillName;
    GohTextUnity *str;
    GohTextUnity *num;
    s32 type;
};

struct BarthListPassPar {
    bool newText;
    GohTextUnity *name;
    GohTextUnity *skill;
    GohTextUnity *atkNum;
    GohTextUnity *haveNum;
    s32 type;
};

struct BarthMasyouPassPar {
    ITM_ICON_TYPE itmType;
    GohTextUnity *materialName;
    GohTextUnity *haveNum;
    GohTextUnity *reuiredNum;
    bool slash;
};

struct RecoverPassPar {
    GohTextUnity *haveManay;
    GohTextUnity *recoverMoney;
};

struct RecoverStatusPassPar {
    s32 devilID;
    GohTextUnity *name;
    GohTextUnity *hp;
    GohTextUnity *maxHp;
    GohTextUnity *bstName;
    BST bst;
};

struct KarteDevilPassPar {
    bool namePlate;
    s32 devlid;
    GohTextUnity *name;
    KUDA category;
    GohTextUnity *lv;
    GohTextUnity *maxHp;
    bool karte;
    bool kartePro;
    GohTextUnity *summonMoney;
    bool dvlLock;
    bool fav;
};

struct PassResultPar {
    GohTextUnity *name;
    GohTextUnity *lv;
    KUDA attri;
    GohTextUnity *gold;
    s32 devilId;
    bool comb;
    bool unregistered;
    bool max;
};

struct GohTextPassManager {
    CombMenuListPassPar *cmbMenuList;
    BarthListPassPar *barthList;
    MaterialListPassPar *materialList;
    BarthMasyouPassPar *barthMasyou;
    RecoverPassPar *recover;
    RecoverStatusPassPar *recoverStatus;
    KarteDevilPassPar *karteDevil;
    PassResultPar *result;
};

static sdatPlayerUnitWork_t *player;
static GohTextPassManager *gohTextPassMgr;
void *gohGuides;
char *gohCaption;
char *strBstName;

// 0x1ba56b0
void gohGohGuideSet(char *_name, bool _timer, s32 _waitTimer) {
  void *Instance;

  if (!op_Inequality(GuideName, name, 0))
    return;
  Instance = get_Instance(0);
  ItfButtonGuideActive(Instance, 1, 0);
  ButtonGuideDispSet(name, timer, waitTimer);
}

// 0x1ba5810
void gohAllDrawCalc(void) {
  Il2CppObject *ProcessData;

  if (!GlobalPID)
    return;
  goto LABEL_9;
LABEL_13:
  goto LABEL_15;
LABEL_9:
  ProcessData = dds3GetProcessData(GlobalPID);
  if (ProcessData)
    goto LABEL_13;
LABEL_15:
  if ((BYTE2(ProcessData[1].klass) & 4) != 0)
  {
    fldFacilityMistDraw(0);
  }
}

// 0x1ba59a0
void gohUnityDraw(bool _csr) {
  tagGOH_MENU_WORK *ProcessData;
  tagGOH_MENU_WORK *v7;
  Il2CppObject *Instance;

  if (!dds3ExistProcess(g_mainPID))
    return;
  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    return;
  v7 = ProcessData;
  if (ProcessData->menuPID)
  {
    gohMainMenuDraw(ProcessData);
    if (csr)
    {
      gohMenuCursorMove(v7);
      return;
    }
    Instance = _get_Instance();
    MenuCursorMove(Instance[18].klass, -1, 0);
  }
}

// 0x1ba5bd0
void gohMainMenuDraw(tagGOH_MENU_WORK *_wk) {
  dds3ProcessID_t *p_menuPID;
  Il2CppObject *ProcessData;
  s64 v7;
  u32 TextColor;
  Il2CppObject *Instance;
  s64 v10;
  u32 klass;
  MenuMover_t *v12;
  Il2CppObject *v13;

  p_menuPID = &wk->menuPID;
  ProcessData = dds3GetProcessData(p_menuPID);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  if (SHIDWORD(ProcessData[8].klass) >= 1)
  {
    v7 = 0;
    do
    {
      klass = ProcessData[13].klass;
      v12 = *((MenuMover_t *)&ProcessData[5].klass->_1.byval_arg.data + v7);
      TextColor = itfGetTextColor(v12, klass);
      Instance = _get_Instance();
      v10 = *(u64 *)(*((u64 *)&ProcessData[5].klass->_1.byval_arg.data + v7) + 24);
      MenuTextDraw(Instance[18].klass, v7++, *(char **)(v10 + 48), TextColor, *(char **)(v10 + 56), 0);
    }
    while (v7 < SHIDWORD(ProcessData[8].klass));
  }
  v13 = _get_Instance();
  MenuPanelDraw(v13[18].klass, HIDWORD(ProcessData[7].monitor), 0);
}

// 0x1ba5d90
void gohMenuCursorMove(tagGOH_MENU_WORK *_wk) {
  dds3ProcessID_t *p_menuPID;
  Il2CppObject *ProcessData;
  Il2CppObject *Instance;

  p_menuPID = &wk->menuPID;
  ProcessData = dds3GetProcessData(p_menuPID);
  if (!ProcessData)
  Instance = _get_Instance();
  MenuCursorMove(Instance[18].klass, *((u32 *)&ProcessData[9].klass->_1.byval_arg.data + SBYTE4(ProcessData[5].monitor)), 0);
}

// 0x1ba5eb0
void gohNativeSkillListDraw(sdatUnitWork_t *_barthDevil) {
  u64 *monitor;
  s64 v4;
  char *TitleText;
  s64 v7;
  u32 i;
  s32 v12;
  void *nativeSkillList;
  NativeSkillCsr *v15;
  s32 klass;
  NativeSkillCsr *v18;
  s64 v19;
  void (__fastcall *v20)(u64 *, u64, s64, s64);
  void *v22;
  s32 klass_high;
  void *v25;
  s32 v26;
  NativeSkillCsr *v27;
  s32 csrNo;
  u32 v29;
  void *v30;
  void *v31;
  u32 listDrwNo;
  Il2CppObject *Item;
  s32 v34;
  SBTLSKILLP_TBL *Skilltbl;
  s32 para;
  SBTLSKILLP_TBL *v37;
  s32 v40;
  char *v41;
  u32 SkillIconType;
  f32 v43;

  monitor = _get_Instance()[10].monitor;
  (*(*monitor + 552))(monitor, 0xFFFFFFFFLL, 0, 0, *(u64 *)(*monitor + 560));
  (*(*monitor + 536))(monitor, 1, *(u64 *)(*monitor + 544));
  (*(*monitor + 440))(monitor, 1, *(u64 *)(*monitor + 448));
  v4 = monitor[4];
  TitleText = cmpGetTitleText(3);
  (*(*(u64 *)v4 + 1368))(v4, TitleText, *(u64 *)(*(u64 *)v4 + 1376));
  v7 = monitor[8];
  (*(*(u64 *)v7 + 376))(v7, (u32)nativeSkillCsr->listMax, (u32)nativeSkillCsr->nowMax, (u32)nativeSkillCsr->listTop, *(u64 *)(*(u64 *)v7 + 384));
  for (i = 0; i != 8; ++i)
  {
    while (1)
    {
      if (i != nativeSkillCsr->listDrwNo)
        goto LABEL_33;
      if (nativeSkillCsr->endCursorOn)
        goto LABEL_33;
      if (nativeSkillStep == 2)
        goto LABEL_33;
      v12 = GohGohNativeSq();
      if (v12 != 1)
        goto LABEL_33;
      nativeSkillList = barthDevil->nativeSkillList;
      v15 = nativeSkillCsr;
      if (v15->csrNo < nativeSkillList->_size)
      {
        v15 = nativeSkillCsr;
        klass = _get_Item(nativeSkillList, i + v15->listTop)[1].klass;
        drawMiscHelp(0, klass);
      }
LABEL_33:
      (*(*monitor + 456))(monitor, nativeSkillCsr->endCursorOn, *(u64 *)(*monitor + 464));
      v18 = nativeSkillCsr;
      if (v18->endCursorOn)
      {
        ButtonLineHelpDispSet(0);
      }
      else
      {
        csrNo = v18->csrNo;
        if (csrNo < 0)
          goto LABEL_39;
        v31 = barthDevil->nativeSkillList;
        if (csrNo >= v31->_size)
          goto LABEL_39;
        v18 = nativeSkillCsr;
        v31 = barthDevil->nativeSkillList;
        csrNo = v18->csrNo;
        listDrwNo = v18->listDrwNo;
        Item = _get_Item(v31, csrNo);
        (*(*monitor + 424))(monitor, listDrwNo, HIDWORD(Item[1].klass), *(u64 *)(*monitor + 432));
      }
LABEL_39:
      v20 = *(*monitor + 504);
      v19 = *(u64 *)(*monitor + 512);
      if ((signed s32)i < barthDevil->nativeSkillList->_size)
        break;
      v20(monitor, i++, 0, v19);
      if (i == 8)
        return;
    }
    v20(monitor, i, 2, v19);
    v22 = barthDevil->nativeSkillList;
    klass_high = HIDWORD(_get_Item(v22, i + nativeSkillCsr->listTop)[1].klass);
    if (!klass_high)
    {
      v29 = 1296780109;
      v30 = barthDevil->nativeSkillList;
      goto LABEL_69;
    }
    v25 = barthDevil->nativeSkillList;
    v26 = HIDWORD(_get_Item(v25, i + nativeSkillCsr->listTop)[1].klass);
    if (v26 != 1)
    {
      v29 = 1;
      v30 = barthDevil->nativeSkillList;
      goto LABEL_69;
    }
    v27 = nativeSkillCsr;
    if (i == v27->listDrwNo)
    {
      if (!nativeSkillCsr->endCursorOn)
        goto LABEL_89;
    }
    v29 = -1600273536;
    v30 = barthDevil->nativeSkillList;
    goto LABEL_69;
LABEL_89:
    v29 = 1692838528;
    v30 = barthDevil->nativeSkillList;
LABEL_69:
    v34 = _get_Item(v30, i + nativeSkillCsr->listTop)[1].klass;
    Skilltbl = sBtlGetSkilltbl(v34);
    para = Skilltbl->para;
    v37 = Skilltbl;
    if (!sBtlGetSpiritSkillChk(1450))
    {
      goto LABEL_72;
    }
    para <<= (v37->flg & 0x200001) == 1;
LABEL_72:
    if (!sBtlGetSpiritSkillChk(1447))
    {
      goto LABEL_74;
    }
    v43 = (f32)para * 0.8;
    if (v43 == INFINITY)
      para = 0x80000000;
    else
      para = v43;
LABEL_74:
    v40 = datCheckSkillType(v34);
    v41 = sdatSkillName(v34);
    (*(*monitor + 472))(monitor, i, v41, v29, para, v40 == 2, 0xFFFFFFFFLL, *(u64 *)(*monitor + 480));
    SkillIconType = cmpGetSkillIconType(v37, v34);
    (*(*monitor + 520))(monitor, SkillIconType, i, *(u64 *)(*monitor + 528));
  }
}

// 0x1ba6660
void gohSearchiListDraw(void) {
  Il2CppClass *klass;
  s32 i;
  u32 v5;
  char *v6;
  char *LocalizeText;
  s32 v8;
  SearchiCtrl *v11;
  char *ParText;
  char *v14;
  u32 v15;
  SearchiCtrl *v17;
  bool Par_bool;
  char *v22;

  klass = _get_Instance()[20].klass;
  for (i = 0; i != 10; ++i)
  {
    if (i != searchiCsr->listDrwNo)
    {
      v5 = -1600273536;
      goto LABEL_17;
    }
    if (condition)
      v5 = 1;
    else
      v5 = 1692838528;
LABEL_17:
    v6 = *(&searchiText[i] + searchiCsr->listTop);
    LocalizeText = GetLocalizeText(v6, 1);
    v8 = searchiDrawSet[i
                                                                             + searchiCsr->listTop];
    if (v8 == 1)
    {
      v11 = (instance->klass->vtable._6_GetSearchiCtrl.methodPtr)(instance, instance->klass->vtable._6_GetSearchiCtrl.method);
      ParText = GetParText(v11, i + searchiCsr->listTop, 0);
      if (ParText)
      {
        v14 = ParText;
        v15 = 1;
        goto LABEL_40;
      }
      v22 = conditionText[0];
      v14 = GetLocalizeText(v22, 1);
      v15 = v5;
LABEL_40:
      SearchiListDraw(klass, i, LocalizeText, v5, 1, v14, v15, 0, 0);
      goto LABEL_4;
    }
    v17 = (instance->klass->vtable._6_GetSearchiCtrl.methodPtr)(instance, instance->klass->vtable._6_GetSearchiCtrl.method);
    Par_bool = GetPar_bool_(v17, i + searchiCsr->listTop);
    SearchiListDraw(klass, i, LocalizeText, v5, v8, 0, v5, Par_bool, 0);
LABEL_4:
    SearchiListCursor(klass, searchiCsr->listDrwNo, condition, 0);
  }
}

// 0x1ba6a70
void gohConditionListDraw(void) {
  s32 i;
  Il2CppClass *klass;
  Il2CppObject *Instance;
  s32 listTop;
  u32 v7;
  s32 v9;
  Il2CppClass *v15;

  for (i = 0; i != 10; ++i)
  {
    listTop = conditionCsr->listTop;
    if (i == conditionCsr->listDrwNo)
      v7 = 1692838528;
    else
      v7 = -1600273536;
    v9 = listTop + i;
    if (listTop + i >= conditionList->_size)
    {
      klass = 0;
      goto LABEL_5;
    }
    v9 = i + conditionCsr->listTop;
    klass = _get_Item(conditionList, v9)[1].klass;
LABEL_5:
    Instance = _get_Instance();
    ConditionListDraw(Instance[20].klass, i, klass, v7, "", 0);
  }
  v15 = _get_Instance()[20].klass;
  ConditionListCursor(v15, conditionCsr->listDrwNo, 0);
}

// 0x1ba6c70
void gohResultDevilDraw(bool _back) {
  s32 v3;
  s32 v4;
  bool v5;
  Il2CppObject *Instance;
  u32 v9;
  ResultCsr *v11;
  s32 v13;
  Il2CppObject *Item;
  s32 klass_high;
  GohTextUnity *name;
  char *v19;
  s32 v20;
  GohTextUnity *lv;
  Il2CppObject *v22;
  char *v23;
  s32 v24;
  PassResultPar *result;
  bool v26;
  bool *klass;
  PassResultPar *v29;
  bool v30;
  s32 monitor_high;
  const MethodInfo_32670E0 *v32;
  void *monitor;
  PassResultPar *v35;
  s32 listDrwNo;
  Il2CppObject *v38;
  u16 data;

  v3 = *(u32 *)(*(u64 *)(*((u64 *)_get_Instance()[20].monitor + 4) + 32) + 24);
  if (v3 >= 1)
  {
    v4 = 0;
    v5 = back;
    while (1)
    {
      if (v4 == resultCsr->listDrwNo)
      {
        if (resultCsr->statusCsr)
          v9 = 1;
        else
          v9 = 1692838528;
        goto LABEL_18;
      }
      v9 = -1600273536;
LABEL_18:
      v11 = resultCsr;
      v13 = v11->listTop + v4;
      if (v13 >= resultUnit_t->_size)
      {
        Instance = _get_Instance();
        CombBackListDrawOff(Instance[20].monitor, v4++, 0);
        if (v3 == v4)
          break;
      }
      else
      {
        v13 = v4 + resultCsr->listTop;
        Item = _get_Item(resultUnit_t, v13);
        klass_high = SHIWORD(Item[1].klass);
        name = gohTextPassMgr->result->name;
        v19 = sdatDevilName(klass_high, 0);
        SetText(name, v19, v9, 0);
        v20 = SHIWORD(Item[1].klass);
        lv = gohTextPassMgr->result->lv;
        data = sBtlGetDevilData(v20, -1)->level;
        v22 = Box(ushort, &data);
        v23 = Format("{0}", v22, 0);
        SetText(lv, v23, v9, 0);
        v24 = SHIWORD(Item[1].klass);
        result = gohTextPassMgr->result;
        result->attri = SBYTE4(Item[1].klass);
        result->devilId = v24;
        v26 = gohKarteAllRegCheck(v24);
        gohTextPassMgr->result->unregistered = !v26;
        klass = Item[16].klass;
        v29 = gohTextPassMgr->result;
        v30 = CombCheck(klass);
        monitor_high = HIWORD(Item[1].monitor);
        v29->comb = v30;
        v32 = Method_Project_SingletonMonoBehaviour_GohCanvasManager__get_Instance__;
        gohTextPassMgr->result->max = monitor_high == 100;
        monitor = _get_Instance(v32)[20].monitor;
        v35 = gohTextPassMgr->result;
        CombBackListDraw(monitor, v4++, v35, resultCsr->listTop, v5, "", 0);
        if (v3 == v4)
          break;
      }
    }
  }
  listDrwNo = resultCsr->listDrwNo;
  v38 = _get_Instance();
  CombBackCursorDraw(v38[20].monitor, listDrwNo, 0);
}

// 0x1ba7120
void gohCombiListDraw(void) {
  s32 v1;
  s32 i;
  Il2CppObject *v3;
  Il2CppObject *Instance;
  u32 *monitor;
  s32 v8;
  u32 j;
  u32 v11;
  Il2CppObject *v13;
  s16 *klass;
  s32 v18;
  GohTextUnity *gold;
  Il2CppObject *v22;
  char *v23;
  s32 v26;
  GohTextUnity *name;
  char *v28;
  GohTextUnity *lv;
  Il2CppObject *v30;
  char *v31;
  s32 v33;
  bool *v34;
  PassResultPar *result;
  bool v37;
  s32 v38;
  s32 v39;
  bool v40;
  void *v42;
  PassResultPar *v44;
  s32 v45;
  s32 v46;
  char v47[4];
  s32 data;

  v45 = *(u32 *)(*(u64 *)(*((u64 *)_get_Instance()[20].monitor + 5) + 24) + 24);
  if (v45 >= 1)
  {
    v1 = 0;
    for (i = 0; i != v45; ++i)
    {
      Instance = _get_Instance();
      monitor = _get_Item(*(void *)(*((u64 *)Instance[20].monitor + 5) + 24), i)[3].monitor;
      v46 = monitor[6];
      v8 = combiCsr->listTop / 3 + i;
      if (v8 >= combiTbl->_size)
      {
        v3 = _get_Instance();
        CombiListDrawOff(v3[20].monitor, i, 0);
      }
      else if (v46 >= 1)
      {
        for (j = 0; v46 != j; ++j)
        {
          v11 = -1600273536;
          if (v1 + j == combiCsr->listDrwNo)
          {
            if (combiCsr->statusCsr)
              v11 = 1;
            else
              v11 = 1692838528;
            v13 = _get_Instance();
            CombiListCursorDraw(v13[20].monitor, i, j, 0);
          }
          if (j == 1)
          {
            klass = _get_Item(combiTbl, v8)[2].klass;
            if (!klass)
              goto LABEL_40;
          }
          else if (j)
          {
            klass = _get_Item(combiTbl, v8)[2].monitor;
            if (!klass)
              goto LABEL_40;
          }
          else
          {
            klass = _get_Item(combiTbl, v8)[1].monitor;
            if (!klass)
              goto LABEL_40;
          }
          v18 = *((u32 *)klass + 63);
          if (v18)
          {
            v18 = *((u32 *)klass + 63);
            data = v18;
            gold = gohTextPassMgr->result->gold;
            v22 = Box(s32, &data);
            v23 = Format("{0}", v22, 0);
            SetText(gold, v23, v11, 0);
            goto LABEL_43;
          }
LABEL_40:
          SetText(gohTextPassMgr->result->gold, 0, v11, 0);
          if (!klass)
            continue;
LABEL_43:
          v26 = klass[11];
          name = gohTextPassMgr->result->name;
          v28 = sdatDevilName(v26, 0);
          SetText(name, v28, v11, 0);
          lv = gohTextPassMgr->result->lv;
          v47[0] = *((u8 *)klass + 24);
          v30 = Box(sbyte, v47);
          v31 = Format("{0}", v30, 0);
          SetText(lv, v31, v11, 0);
          v33 = klass[11];
          v34 = *((bool **)klass + 32);
          result = gohTextPassMgr->result;
          result->attri = *((char *)klass + 20);
          result->devilId = v33;
          v37 = CombCheck(v34);
          v38 = (u16)klass[15];
          result->comb = v37;
          v39 = klass[11];
          gohTextPassMgr->result->max = v38 == 100;
          v40 = gohKarteAllRegCheck(v39);
          gohTextPassMgr->result->unregistered = !v40;
          v42 = _get_Instance()[20].monitor;
          v44 = gohTextPassMgr->result;
          CombiListDraw(v42, i, j, v44, combiCsr->listTop, j > 1, 0);
        }
      }
      v1 += 3;
    }
  }
}

// 0x1ba7730
void DrawTree(gohData_t *_gohDate) {
  void *swordTree;
  s32 v4;
  Il2CppObject *i;
  void *WeaponList;
  void *v7;
  s32 v8;
  void *WeaponIconList;
  Il2CppObject *Item;
  Il2CppObject *v11;
  s32 klass;
  s32 v13;
  Il2CppObject *v14;
  s32 v15;
  bool v16;
  bool v17;
  s32 ItmSwordNo;
  s32 v20;
  Il2CppObject *v22;
  void *v23;
  s32 v24;
  s32 v25;
  Il2CppRuntimeInterfaceOffsetPair *interfaceOffsets;

  swordTree = gohDate->Table->swordTree;
  GetTypeList(swordTree, gohDate->treeCsr->stage, gohDate->treeCsr->type, 0);
  interfaceOffsets = _get_Instance()[16].klass->_1.interfaceOffsets;
  DrawFamilyText(interfaceOffsets, 0);
  if (gohDate->drawTreeUpdate)
  {
    if (swordTree->treeList->_size >= 1)
    {
      v25 = 0;
      v23 = swordTree;
      v4 = 0;
      for (i = _get_Item(swordTree->treeList, 0); ; i = _get_Item(v23->treeList, v25))
      {
        WeaponList = GetWeaponList(i, v4, 0);
        if (WeaponList->_size >= 1)
        {
          v7 = WeaponList;
          v8 = 0;
          v24 = v4;
          do
          {
            WeaponIconList = GetWeaponIconList(interfaceOffsets, v4, 0);
            if (WeaponIconList)
            {
              Item = _get_Item(WeaponIconList, v25);
              v11 = _get_Item(Item, v8);
              klass = _get_Item(v7, v8)[1].klass;
              v13 = 144;
              if (klass != 145)
              {
                v14 = _get_Item(v7, v8);
                v13 = _get_Item(v14[1].monitor, 0);
              }
              v15 = gohDate->treeCsr->item;
              v16 = v15 == klass && (gohDate->gohTreeMenuType || gohDate->spritCheck);
              v17 = GohCreateCheckSelSword(gohDate, v13, klass);
              ItmSwordNo = GetItmSwordNo(klass, 0);
              if (ItmSwordNo == GBWK->player->swordno)
                v20 = 2;
              else
                v20 = v17;
              DrawCursor(v11, v15 == klass, v16, 0);
              v22 = _get_Item(v7, v8);
              DrawTreeIcon(gohDate, v22, v11, v15 == klass, v20);
              v4 = v24;
            }
            ++v8;
          }
          while (v8 < v7->_size);
        }
        if (++v4 == 4)
        {
          if (++v25 >= v23->treeList->_size)
            break;
          v4 = 0;
        }
      }
    }
    gohDate->drawTreeUpdate = 0;
  }
}

// 0x1ba7aa0
void DrawTreeIcon(gohData_t *_gohData, TreeDetails *_treeDetails, TreeIcon *_icon, bool _enable, GohTreeAnimType _type) {
  u32 ItmSwordNo;
  s64 v12;
  s32 v13;
  s32 Item;
  s64 v16;
  void *v17;
  s64 v18;
  s32 swordno;
  _BOOL4 v20;
  bool v22;
  s32 v23;
  void *v24;
  bool v25;
  void *v26;
  bool v27;
  void *gameObject;
  void *v29;
  void *v30;
  void *v31;
  bool v32;
  void *v33;
  bool activeSelf;

  ItmSwordNo = GetItmSwordNo(treeDetails->id, 0);
  v12 = (s_pcInst->klass->vtable._24_GetWeaponTable.methodPtr)(s_pcInst, ItmSwordNo, s_pcInst->klass->vtable._24_GetWeaponTable.method);
  if (treeDetails->id == 145)
  {
    v13 = 0;
  }
  else
  {
    Item = _get_Item(treeDetails->source, 0);
    v13 = GetItmSwordNo(Item, 0);
  }
  v16 = 24;
  if (enable)
    v16 = 32;
  v17 = *(void ***)((char *)&icon->klass + v16);
  v18 = *(u32 *)(v12 + 20);
  swordno = GBWK->player->swordno;
  v20 = ItmSwordNo != swordno;
  (v17[18].monitor)(v17, v18, ItmSwordNo == swordno, v17[18].m_CachedPtr);
  if (IndexOf_Int32Enum_(tbl, treeDetails->id) == -1 || gohData->spSword)
  {
    v22 = gohCheckSwordHave(v13);
    if (!v22)
    {
      gameObject = get_gameObject(v17[5], 0);
      if (get_activeSelf(gameObject, 0))
        SetActive(gameObject, 0, 0);
LABEL_33:
      gohCheckSword(ItmSwordNo);
      v32 = gohCheckSwordHave(ItmSwordNo) || !v22;
      v33 = get_gameObject(v17[6], 0);
      activeSelf = get_activeSelf(v33, 0);
      if (v32)
      {
        if (!activeSelf)
          goto LABEL_38;
      }
      else if (activeSelf)
      {
LABEL_38:
        (v17[17].m_CachedPtr)(v17, v20, v17[18].klass);
        (v17[17].klass)(v17, type, v17[17].monitor);
        return;
      }
      SetActive(v33, !v32, 0);
      goto LABEL_38;
    }
    v23 = gohCheckComposition(ItmSwordNo, v13);
    v24 = get_gameObject(v17[5], 0);
    v25 = get_activeSelf(v24, 0);
    if (v23)
    {
      if (v25)
      {
        v26 = v24;
        v27 = 0;
LABEL_31:
        SetActive(v26, v27, 0);
      }
    }
    else if (!v25)
    {
      v26 = v24;
      v27 = 1;
      goto LABEL_31;
    }
    v20 = 0;
    goto LABEL_33;
  }
  v29 = get_gameObject(v17[7], 0);
  if (get_activeSelf(v29, 0))
    SetActive(v29, 0, 0);
  v30 = get_gameObject(v17[5], 0);
  if (get_activeSelf(v30, 0))
    SetActive(v30, 0, 0);
  v31 = get_gameObject(v17[6], 0);
  if (get_activeSelf(v31, 0))
    SetActive(v31, 0, 0);
  (v17[17].m_CachedPtr)(v17, ItmSwordNo != swordno, v17[18].klass);
}

// 0x1ba7e30
void DrawSwordDetails(gohData_t *_gohDate) {
  Il2CppObject *Instance;
  TreeCsr *treeCsr;
  Il2CppClass *klass;
  s32 ItmSwordNo;
  u32 v8;
  s64 v9;
  s64 v10;
  char *LocalizeText;
  void *v12;
  void *v13;
  bool v14;
  void *gameObject;
  s32 item;
  s64 v17;
  char *v18;
  s32 v19;
  s32 ItemNum;
  Il2CppClass **nestedTypes;
  Il2CppClass *v22;
  Il2CppObject *v23;
  char *v24;
  s32 v25;
  bool Master;
  void *v27;
  bool activeSelf;
  _BOOL4 spritCheck;
  void *v30;
  bool v31;
  void *v32;
  u32 v33;
  void *v34;
  s32 v35;
  s64 v36;
  char *v37;
  s32 v38;
  s32 v39;
  Il2CppClass **v40;
  Il2CppClass *v41;
  Il2CppObject *v42;
  char *v43;
  bool v44;
  void *v45;
  bool v46;
  _BOOL4 v47;
  void *v48;
  bool v49;
  void *v50;
  void *v51;
  void *v52;
  s64 v53;
  char *v54;
  s64 v55;
  char *v56;
  char *v57;
  void *v58;
  void *v59;
  s32 v61;
  CMDevilResPs2 *v63;
  s32 v65;
  bool v66;
  _BOOL4 v67;
  s32 v68;
  s32 v69;
  CMDevilResPs2 *v71;
  s32 v73;
  _BOOL4 v74;
  s32 v75;
  s32 v76;
  CMDevilResPs2 *v78;
  s32 v80;
  _BOOL4 v81;
  s32 v82;
  s32 v83;
  CMDevilResPs2 *v85;
  s32 v87;
  _BOOL4 v88;
  s32 v89;
  s32 v90;
  CMDevilResPs2 *v92;
  s32 v94;
  _BOOL4 v95;
  s32 v96;
  s32 v97;
  CMDevilResPs2 *v99;
  s32 v101;
  _BOOL4 v102;
  s32 v103;
  s64 v104;
  char *v105;
  s64 v106;
  char *v107;
  char *v108;
  void *v109;
  char *v110;
  void *v111;
  SBTLSKILLP_TBL *Skilltbl;
  s32 SkillIconType;
  void *v114;
  void *v115;
  void *v116;
  void *SklIconSpr;
  s32 data;
  s32 v119;

  Instance = _get_Instance();
  treeCsr = gohDate->treeCsr;
  klass = Instance[16].klass;
  GetTypeList(gohDate->Table->swordTree, treeCsr->stage, treeCsr->type, 0);
  ItmSwordNo = GetItmSwordNo(treeCsr->item, 0);
  v8 = GetItmSwordNo(treeCsr->item, 0);
  v9 = (s_pcInst->klass->vtable._24_GetWeaponTable.methodPtr)(s_pcInst, v8, s_pcInst->klass->vtable._24_GetWeaponTable.method);
  v10 = *((u64 *)klass->_1.nestedTypes + 3);
  LocalizeText = GetLocalizeText("GOH_RENKEN_L0012", 1);
  (*(*(u64 *)v10 + 1368))(v10, LocalizeText, *(u64 *)(*(u64 *)v10 + 1376));
  WeaponIconDraw(klass->_1.nestedTypes, *(u32 *)(v9 + 20), 0);
  if (!gohDate->swordDetails)
  {
    gameObject = get_gameObject(*((void *)klass->_1.nestedTypes + 6), 0);
    if (get_activeSelf(gameObject, 0))
      SetActive(gameObject, 0, 0);
    item = treeCsr->item;
    v17 = *((u64 *)klass->_1.nestedTypes + 4);
    v18 = sdatItemName(item);
    (*(*(u64 *)v17 + 1368))(v17, v18, *(u64 *)(*(u64 *)v17 + 1376));
    v19 = gohDate->treeCsr->item;
    ItemNum = datGetItemNum(v19);
    nestedTypes = klass->_1.nestedTypes;
    data = ItemNum;
    v22 = nestedTypes[14];
    v23 = Box(s32, &data);
    v24 = Format("{0}", v23, 0);
    (*(v22->_1.image + 171))(v22, v24, *((u64 *)v22->_1.image + 172));
    v25 = *(u32 *)(v9 + 32);
    Master = datSwordSklGetMaster(GBWK->player, v25);
    v27 = get_gameObject(*((void *)klass->_1.nestedTypes + 7), 0);
    activeSelf = get_activeSelf(v27, 0);
    if (Master)
    {
      if (!activeSelf)
      {
LABEL_23:
        spritCheck = gohDate->spritCheck;
        v30 = get_gameObject(*((void *)klass->_1.nestedTypes + 10), 0);
        v31 = get_activeSelf(v30, 0);
        if (spritCheck)
        {
          if (!v31)
            SetActive(v30, 1, 0);
          v32 = get_gameObject(*((void *)klass->_1.nestedTypes + 11), 0);
          if (!get_activeSelf(v32, 0))
            SetActive(v32, 1, 0);
          v33 = 1692838528;
          itfDrawMiscHelp(0xA09DC380, 1.0, 0, v25, 2);
        }
        else
        {
          if (v31)
            SetActive(v30, 0, 0);
          v52 = get_gameObject(*((void *)klass->_1.nestedTypes + 11), 0);
          v33 = -1600273536;
          if (get_activeSelf(v52, 0))
          {
            SetActive(v52, 0, 0);
            v33 = -1600273536;
          }
        }
        if (!gohDate->gohTreeMenuType)
        {
          if (v25 == 1024)
          {
            ButtonLineHelpTextSet(0, 0, 1, 0xA09DC380, 1);
          }
          else
          {
            itfDrawMiscHelp(0xA09DC380, 1.0, 0, v25, 2);
          }
        }
        v104 = *((u64 *)klass->_1.nestedTypes + 8);
        v105 = GetLocalizeText("GOH_RENKEN_L0013", 1);
        (*(*(u64 *)v104 + 1368))(v104, v105, *(u64 *)(*(u64 *)v104 + 1376));
        v106 = *((u64 *)klass->_1.nestedTypes + 13);
        v107 = GetLocalizeText("GOH_RENKEN_L0003", 1);
        (*(*(u64 *)v106 + 1368))(v106, v107, *(u64 *)(*(u64 *)v106 + 1376));
        if (v25 == 1024)
        {
          v108 = GetLocalizeText("CMP_STATUS_L0018", 1);
          v109 = *((void *)klass->_1.nestedTypes + 9);
          itfFontColorTextUnity2(v108, v33, v109, 0, 1, "");
LABEL_157:
          v61 = *(u32 *)(v9 + 16);
          goto LABEL_81;
        }
LABEL_146:
        v110 = sdatSkillName(v25);
        v111 = *((void *)klass->_1.nestedTypes + 9);
        itfFontColorTextUnity2(v110, v33, v111, 0, 1, "");
        Skilltbl = sBtlGetSkilltbl(v25);
        SkillIconType = cmpGetSkillIconType(Skilltbl, v25);
        v114 = get_gameObject(*((void *)klass->_1.nestedTypes + 12), 0);
        if (!get_activeSelf(v114, 0))
          SetActive(v114, 1, 0);
        v115 = *((void *)klass->_1.nestedTypes + 12);
        v116 = get_Instance(0);
        SklIconSpr = GetSklIconSpr(v116, SkillIconType, 0);
        set_sprite(v115, SklIconSpr, 0);
        goto LABEL_157;
      }
    }
    else if (activeSelf)
    {
      goto LABEL_23;
    }
    SetActive(v27, !Master, 0);
    goto LABEL_23;
  }
  if (gohCheckSwordHave(ItmSwordNo) || treeCsr->item == 145)
  {
    v12 = get_gameObject(*((void *)klass->_1.nestedTypes + 6), 0);
    if (!get_activeSelf(v12, 0))
      goto LABEL_34;
    v13 = v12;
    v14 = 0;
  }
  else
  {
    v34 = get_gameObject(*((void *)klass->_1.nestedTypes + 6), 0);
    if (get_activeSelf(v34, 0))
      goto LABEL_34;
    v13 = v34;
    v14 = 1;
  }
  SetActive(v13, v14, 0);
LABEL_34:
  v35 = treeCsr->item;
  v36 = *((u64 *)klass->_1.nestedTypes + 4);
  v37 = sdatItemName(v35);
  (*(*(u64 *)v36 + 1368))(v36, v37, *(u64 *)(*(u64 *)v36 + 1376));
  v38 = gohDate->treeCsr->item;
  v39 = datGetItemNum(v38);
  v40 = klass->_1.nestedTypes;
  v119 = v39;
  v41 = v40[14];
  v42 = Box(s32, &v119);
  v43 = Format("{0}", v42, 0);
  (*(v41->_1.image + 171))(v41, v43, *((u64 *)v41->_1.image + 172));
  v25 = *(u32 *)(v9 + 32);
  v44 = datSwordSklGetMaster(GBWK->player, v25);
  v45 = get_gameObject(*((void *)klass->_1.nestedTypes + 7), 0);
  v46 = get_activeSelf(v45, 0);
  if (!v44)
  {
    if (v46)
      goto LABEL_43;
    goto LABEL_42;
  }
  if (v46)
LABEL_42:
    SetActive(v45, !v44, 0);
LABEL_43:
  v47 = gohDate->spritCheck;
  v48 = get_gameObject(*((void *)klass->_1.nestedTypes + 10), 0);
  v49 = get_activeSelf(v48, 0);
  if (v47)
  {
    if (!v49)
      SetActive(v48, 1, 0);
    v50 = get_gameObject(*((void *)klass->_1.nestedTypes + 11), 0);
    if (!get_activeSelf(v50, 0))
      SetActive(v50, 1, 0);
    v33 = 1692838528;
    itfDrawMiscHelp(0xA09DC380, 1.0, 0, v25, 2);
  }
  else
  {
    if (v49)
      SetActive(v48, 0, 0);
    v51 = get_gameObject(*((void *)klass->_1.nestedTypes + 11), 0);
    v33 = -1600273536;
    if (get_activeSelf(v51, 0))
    {
      SetActive(v51, 0, 0);
      v33 = -1600273536;
    }
  }
  if (!gohDate->gohTreeMenuType)
  {
    if (v25 == 1024)
    {
      ButtonLineHelpTextSet(0, 0, 1, 0xA09DC380, 1);
    }
    else
    {
      itfDrawMiscHelp(0xA09DC380, 1.0, 0, v25, 2);
    }
  }
  v53 = *((u64 *)klass->_1.nestedTypes + 8);
  v54 = GetLocalizeText("GOH_RENKEN_L0013", 1);
  (*(*(u64 *)v53 + 1368))(v53, v54, *(u64 *)(*(u64 *)v53 + 1376));
  v55 = *((u64 *)klass->_1.nestedTypes + 13);
  v56 = GetLocalizeText("GOH_RENKEN_L0003", 1);
  (*(*(u64 *)v55 + 1368))(v55, v56, *(u64 *)(*(u64 *)v55 + 1376));
  if (v25 != 1024)
    goto LABEL_146;
  v57 = GetLocalizeText("CMP_STATUS_L0018", 1);
  v58 = *((void *)klass->_1.nestedTypes + 9);
  itfFontColorTextUnity2(v57, v33, v58, 0, 1, "");
  v59 = get_gameObject(*((void *)klass->_1.nestedTypes + 12), 0);
  if (get_activeSelf(v59, 0))
  {
    SetActive(v59, 0, 0);
    v61 = *(u32 *)(v9 + 16);
LABEL_81:
    goto LABEL_82;
  }
  v61 = *(u32 *)(v9 + 16);
  goto LABEL_81;
LABEL_82:
  v63 = s_pcInst;
  v65 = *(u32 *)((v63->klass->vtable._24_GetWeaponTable.methodPtr)(v63, (u32)GBWK->player->swordno, v63->klass->vtable._24_GetWeaponTable.method) + 16);
  v66 = v65 < v61;
  v67 = v65 > v61;
  if (v66)
    v68 = 2;
  else
    v68 = v67;
  DrawSwordPar(5, v61, v68, 0);
  v69 = *(u32 *)(*(u64 *)(v9 + 24) + 16);
  v71 = s_pcInst;
  v73 = *(u32 *)(*(u64 *)((v71->klass->vtable._24_GetWeaponTable.methodPtr)(v71, (u32)GBWK->player->swordno, v71->klass->vtable._24_GetWeaponTable.method) + 24) + 16);
  v66 = v73 < v69;
  v74 = v73 > v69;
  if (v66)
    v75 = 2;
  else
    v75 = v74;
  DrawSwordPar(4, v69, v75, 0);
  v76 = *(s16 *)(*(u64 *)(v9 + 24) + 32);
  v78 = s_pcInst;
  v80 = *(s16 *)(*(u64 *)((v78->klass->vtable._24_GetWeaponTable.methodPtr)(v78, (u32)GBWK->player->swordno, v78->klass->vtable._24_GetWeaponTable.method) + 24) + 32);
  v66 = v80 < v76;
  v81 = v80 > v76;
  if (v66)
    v82 = 2;
  else
    v82 = v81;
  DrawSwordPar(0, v76, v82, 0);
  v83 = *(s16 *)(*(u64 *)(v9 + 24) + 36);
  v85 = s_pcInst;
  v87 = *(s16 *)(*(u64 *)((v85->klass->vtable._24_GetWeaponTable.methodPtr)(v85, (u32)GBWK->player->swordno, v85->klass->vtable._24_GetWeaponTable.method) + 24) + 36);
  v66 = v87 < v83;
  v88 = v87 > v83;
  if (v66)
    v89 = 2;
  else
    v89 = v88;
  DrawSwordPar(1, v83, v89, 0);
  v90 = *(s16 *)(*(u64 *)(v9 + 24) + 34);
  v92 = s_pcInst;
  v94 = *(s16 *)(*(u64 *)((v92->klass->vtable._24_GetWeaponTable.methodPtr)(v92, (u32)GBWK->player->swordno, v92->klass->vtable._24_GetWeaponTable.method) + 24) + 34);
  v66 = v94 < v90;
  v95 = v94 > v90;
  if (v66)
    v96 = 2;
  else
    v96 = v95;
  DrawSwordPar(2, v90, v96, 0);
  v97 = *(s16 *)(*(u64 *)(v9 + 24) + 38);
  v99 = s_pcInst;
  v101 = *(s16 *)(*(u64 *)((v99->klass->vtable._24_GetWeaponTable.methodPtr)(v99, (u32)GBWK->player->swordno, v99->klass->vtable._24_GetWeaponTable.method) + 24) + 38);
  v66 = v101 < v97;
  v102 = v101 > v97;
  if (v66)
    v103 = 2;
  else
    v103 = v102;
  DrawSwordPar(3, v97, v103, 0);
}

// 0x1ba8ec0
SWORD_UPDOWN gohGetSwordEquipPar(UiParType _para, s32 _newPar) {
  s64 v7;
  s32 v8;
  bool v9;
  s32 v10;

  v7 = (s_pcInst->klass->vtable._24_GetWeaponTable.methodPtr)(s_pcInst, (u32)GBWK->player->swordno, s_pcInst->klass->vtable._24_GetWeaponTable.method);
  switch (para)
  {
    case 0:
      v8 = *(s16 *)(*(u64 *)(v7 + 24) + 32);
      break;
    case 1:
      v8 = *(s16 *)(*(u64 *)(v7 + 24) + 36);
      break;
    case 2:
      v8 = *(s16 *)(*(u64 *)(v7 + 24) + 34);
      break;
    case 3:
      v8 = *(s16 *)(*(u64 *)(v7 + 24) + 38);
      break;
    case 4:
      v8 = *(u32 *)(*(u64 *)(v7 + 24) + 16);
      break;
    case 5:
      v8 = *(u32 *)(v7 + 16);
      break;
    default:
      v8 = 0;
      break;
  }
  v9 = v8 < newPar;
  v10 = v8 > newPar;
  if (v9)
    return 2;
  else
    return v10;
}

// 0x1ba9000
void DrawSwordPar(UiParType _para, s32 _parNum, SWORD_UPDOWN _upDown, bool _details) {
  Il2CppClass *klass;
  void *v9;
  s32 v10;
  u32 v11;
  Il2CppObject *Item;
  char *LocalizeText;
  Il2CppObject *v14;
  char *v15;
  Il2CppObject *v16;
  char *v17;
  Il2CppObject *v18;
  char *v19;
  Il2CppObject *v20;
  char *v21;
  Il2CppObject *v22;
  char *v23;
  Il2CppObject *v24;
  Il2CppObject *v25;
  char *v26;
  char *v27;
  char *v28;
  s32 data;

  klass = _get_Instance()[16].klass;
  v9 = *(void *)(*((u64 *)klass->_1.nestedTypes + 15) + 16);
  if (!get_activeSelf(v9, 0))
    SetActive(v9, 1, 0);
  if (upDown == 2)
    v10 = 1853947776;
  else
    v10 = -1600273536;
  if (upDown == 1)
    v11 = 1849704703;
  else
    v11 = v10;
  Item = _get_Item(*(void *)(*((u64 *)klass->_1.nestedTypes + 15) + 24), 0);
  LocalizeText = GetLocalizeText("GOH_CAPTION_L0066", 1);
  (Item->klass->vtable[66].methodPtr)(Item, LocalizeText, Item->klass->vtable[66].method);
  v14 = _get_Item(*(void *)(*((u64 *)klass->_1.nestedTypes + 15) + 24), 1);
  v15 = GetLocalizeText("GOH_CAPTION_L0058", 1);
  (v14->klass->vtable[66].methodPtr)(v14, v15, v14->klass->vtable[66].method);
  v16 = _get_Item(*(void *)(*((u64 *)klass->_1.nestedTypes + 15) + 24), 2);
  v17 = GetLocalizeText("GOH_CAPTION_L0044", 1);
  (v16->klass->vtable[66].methodPtr)(v16, v17, v16->klass->vtable[66].method);
  v18 = _get_Item(*(void *)(*((u64 *)klass->_1.nestedTypes + 15) + 24), 3);
  v19 = GetLocalizeText("GOH_CAPTION_L0045", 1);
  (v18->klass->vtable[66].methodPtr)(v18, v19, v18->klass->vtable[66].method);
  v20 = _get_Item(*(void *)(*((u64 *)klass->_1.nestedTypes + 15) + 24), 4);
  v21 = GetLocalizeText("GOH_CAPTION_L0046", 1);
  (v20->klass->vtable[66].methodPtr)(v20, v21, v20->klass->vtable[66].method);
  v22 = _get_Item(*(void *)(*((u64 *)klass->_1.nestedTypes + 15) + 24), 5);
  v23 = GetLocalizeText("GOH_CAPTION_L0047", 1);
  (v22->klass->vtable[66].methodPtr)(v22, v23, v22->klass->vtable[66].method);
  v24 = 0;
  if ((u32)para <= 5)
    v24 = _get_Item(*(void *)(*((u64 *)klass->_1.nestedTypes + 15) + 32), dword_3E60BAC[para]);
  if (parNum)
  {
    data = parNum;
    v25 = Box(s32, &data);
    v26 = Format("{0}", v25, 0);
    v27 = Concat_54766928(0, v26, 0);
    itfFontColorTextUnity2(v27, v11, v24, 1, 0, "");
  }
  else
  {
    v28 = GetLocalizeText("HUUMAINFO_L0013", 1);
    itfFontColorTextUnity2(v28, v11, v24, 1, 0, "");
  }
}

// 0x1ba9490
void gohTreeMaterialDraw(gohData_t *_gohDate) {
  Il2CppClass *klass;
  void *v4;
  TreeCsr *treeCsr;
  s64 v6;
  char *LocalizeText;
  s64 v8;
  char *v9;
  s64 v10;
  char *v11;
  s64 v12;
  char *v13;
  gohRenkenSelMaterial_t *p_m_sRenkenSelMaterial;
  s32 ItmSwordNo;
  s32 v16;
  s32 v18;
  s64 v19;
  gohRenkenSelMaterialItem_t *v20;
  s32 m_iGold;
  u32 v23;
  s32 *p_data;
  s64 v25;
  gohRenkenSelMaterialItem_t *v26;
  s32 v28;
  void *v29;
  Il2CppObject *v30;
  char *v31;
  char *v32;
  s64 v33;
  char *v34;
  void *v35;
  s64 v36;
  char *v37;
  s32 data;
  s32 v39;

  klass = _get_Instance()[16].klass;
  v4 = *((void *)klass->_1.properties + 2);
  if (!get_activeSelf(v4, 0))
    SetActive(v4, 1, 0);
  (*(*(u64 *)klass->_1.methods + 536))(klass->_1.methods, 0, *(u64 *)(*(u64 *)klass->_1.methods + 544));
  treeCsr = gohDate->treeCsr;
  v6 = *((u64 *)klass->_1.properties + 3);
  LocalizeText = GetLocalizeText("GOH_RENKEN_L0011", 1);
  (*(*(u64 *)v6 + 1368))(v6, LocalizeText, *(u64 *)(*(u64 *)v6 + 1376));
  v8 = *((u64 *)klass->_1.properties + 4);
  v9 = GetLocalizeText("GOH_RENKEN_L0004", 1);
  (*(*(u64 *)v8 + 1368))(v8, v9, *(u64 *)(*(u64 *)v8 + 1376));
  v10 = *((u64 *)klass->_1.properties + 5);
  v11 = GetLocalizeText("GOH_RENKEN_L0003", 1);
  (*(*(u64 *)v10 + 1368))(v10, v11, *(u64 *)(*(u64 *)v10 + 1376));
  v12 = *((u64 *)klass->_1.properties + 6);
  v13 = GetLocalizeText("GOH_RENKEN_L0005", 1);
  (*(*(u64 *)v12 + 1368))(v12, v13, *(u64 *)(*(u64 *)v12 + 1376));
  p_m_sRenkenSelMaterial = &gohDate->m_sRenkenSelMaterial;
  ItmSwordNo = GetItmSwordNo(gohDate->treeCsr->item, 0);
  gohSelMaterial(&gohDate->m_sRenkenSelMaterial, ItmSwordNo);
  v18 = *(u32 *)(*((u64 *)klass->_1.properties + 7) + 24);
  if (gohDate->swordDetails)
  {
    if (v18 >= 1)
    {
      v19 = 0;
      do
      {
        v20 = p_m_sRenkenSelMaterial->m_asMatrial[v19];
        gohBaseItemParamSimple(v20, v16, v19++);
      }
      while (v19 < *(s32 *)(*((u64 *)klass->_1.properties + 7) + 24));
    }
    m_iGold = p_m_sRenkenSelMaterial->m_iGold;
    if (m_iGold <= GBWK->player->gold)
      v23 = -1600273536;
    else
      v23 = 1849704703;
    if (treeCsr->item != 145)
    {
      p_data = &v39;
      v39 = p_m_sRenkenSelMaterial->m_iGold;
LABEL_35:
      v30 = Box(s32, p_data);
      v31 = Format("{0,7:d}", v30, 0);
      v32 = Concat_54766928(0, v31, 0);
      v33 = *((u64 *)klass->_1.properties + 8);
      v34 = GetLocalizeText("GOH_RENKEN_L0008", 1);
      (*(*(u64 *)v33 + 1368))(v33, v34, *(u64 *)(*(u64 *)v33 + 1376));
      v35 = *((void *)klass->_1.properties + 9);
      itfFontColorTextUnity2(v32, v23, v35, 1, 0, "");
      v36 = *((u64 *)klass->_1.properties + 10);
      v37 = GetLocalizeText("GOH_CAPTION_L0057", 1);
      (*(*(u64 *)v36 + 1368))(v36, v37, *(u64 *)(*(u64 *)v36 + 1376));
      return;
    }
  }
  else
  {
    if (v18 >= 1)
    {
      v25 = 0;
      do
      {
        v26 = p_m_sRenkenSelMaterial->m_asMatrial[v25];
        gohBaseItemParamSimple(v26, v16, v25++);
      }
      while (v25 < *(s32 *)(*((u64 *)klass->_1.properties + 7) + 24));
    }
    v28 = p_m_sRenkenSelMaterial->m_iGold;
    if (v28 <= GBWK->player->gold)
      v23 = -1600273536;
    else
      v23 = 1849704703;
    if (treeCsr->item != 145)
    {
      p_data = &data;
      data = p_m_sRenkenSelMaterial->m_iGold;
      goto LABEL_35;
    }
  }
  (*(**((u64 **)klass->_1.properties + 8) + 1368))(*((u64 *)klass->_1.properties + 8), 0, *(u64 *)(**((u64 **)klass->_1.properties + 8) + 1376));
  v29 = *((void *)klass->_1.properties + 9);
  itfFontColorTextUnity2(0, 0xA09DC380, v29, 1, 0, "");
  (*(**((u64 **)klass->_1.properties + 10) + 1368))(*((u64 *)klass->_1.properties + 10), 0, *(u64 *)(**((u64 **)klass->_1.properties + 10) + 1376));
}

// 0x1ba9da0
void gohTreeBattleDraw(gohData_t *_gohDate) {
  Il2CppClass *klass;
  u64 **methods;
  void *v5;
  void *v6;
  MenuCsrUnity *treeBattleCsr;
  u32 listTop;
  s32 listDrwNo;
  u32 v10;
  u32 v11;
  void *DrawRaidouSkill;
  void *v13;
  s32 v14;
  void *v15;
  s32 v17;
  s32 v18;
  u32 v19;
  char *v20;
  s32 v22;
  u32 v23;
  u32 v25;
  u32 v26;
  char *v27;
  s32 v28;
  s32 v29;
  char *v31;
  u64 *v32;
  char *TitleText;
  char *v34;
  s32 listMax;
  s32 nowMax;

  klass = _get_Instance()[16].klass;
  methods = _get_Instance()[16].klass->_1.methods;
  v5 = *((void *)klass->_1.properties + 2);
  if (get_activeSelf(v5, 0))
    SetActive(v5, 0, 0);
  v6 = *((void *)klass->_1.methods + 2);
  if (!get_activeSelf(v6, 0))
    SetActive(v6, 1, 0);
  treeBattleCsr = gohDate->treeBattleCsr;
  listTop = treeBattleCsr->listTop;
  listDrwNo = treeBattleCsr->listDrwNo;
  nowMax = treeBattleCsr->nowMax;
  listMax = treeBattleCsr->listMax;
  v10 = -1600273536;
  v11 = 1692838528;
  DrawRaidouSkill = cmpGetDrawRaidouSkill(listTop, 4, 1);
  v13 = _ToArray(DrawRaidouSkill);
  v14 = v13[0];
  v15 = v13;
  if (!listDrwNo)
  {
    (*(*(u64 *)klass->_1.methods + 424))(klass->_1.methods, 0, 1, *(u64 *)(*(u64 *)klass->_1.methods + 432));
    v10 = 1692838528;
  }
  ((*methods)[63])(methods, 0, 1, (*methods)[64]);
  if (v14)
  {
    DrawSpiritSkillName(v14, 0, v10, 1);
  }
  if (listDrwNo)
  {
    v17 = v15[1];
    if (listDrwNo == 1)
    {
      v18 = 1;
      (*(*(u64 *)klass->_1.methods + 424))(klass->_1.methods, 1, 1, *(u64 *)(*(u64 *)klass->_1.methods + 432));
      v19 = 1692838528;
      goto LABEL_26;
    }
  }
  else
  {
    if (!gohDate->spritCheck)
    {
      v20 = sdatSkillHelp(v14, 1);
      ButtonLineHelpTextSet(v20, 0, 1, 0xA09DC380, 1);
    }
    v17 = v15[1];
  }
  v18 = 0;
  v19 = -1600273536;
LABEL_26:
  ((*methods)[63])(methods, 1, 1, (*methods)[64]);
  if (v17)
  {
    DrawSpiritSkillName(v17, 1, v19, 1);
  }
  if (!v18 || gohDate->spritCheck)
  {
    v22 = v15[2];
    v23 = -1600273536;
    if (listDrwNo != 2)
      goto LABEL_34;
    goto LABEL_33;
  }
  v34 = sdatSkillHelp(v17, 1);
  ButtonLineHelpTextSet(v34, 0, 1, 0xA09DC380, 1);
  v22 = v15[2];
  v23 = -1600273536;
  if (listDrwNo == 2)
  {
LABEL_33:
    (*(*(u64 *)klass->_1.methods + 424))(klass->_1.methods, 2, 1, *(u64 *)(*(u64 *)klass->_1.methods + 432));
    v23 = 1692838528;
  }
LABEL_34:
  ((*methods)[63])(methods, 2, 1, (*methods)[64]);
  if (v22)
  {
    DrawSpiritSkillName(v22, 2, v23, 1);
  }
  if (listDrwNo == 2)
  {
    v25 = nowMax;
    v26 = listMax;
    if (!gohDate->spritCheck)
    {
      v27 = sdatSkillHelp(v22, 1);
      ButtonLineHelpTextSet(v27, 0, 1, 0xA09DC380, 1);
    }
    v28 = v15[3];
    v29 = 0;
    v11 = -1600273536;
  }
  else
  {
    v28 = v15[3];
    if (listDrwNo == 3)
    {
      v29 = 1;
      (*(*(u64 *)klass->_1.methods + 424))(klass->_1.methods, 3, 1, *(u64 *)(*(u64 *)klass->_1.methods + 432));
    }
    else
    {
      v29 = 0;
      v11 = -1600273536;
    }
    v25 = nowMax;
    v26 = listMax;
  }
  ((*methods)[63])(methods, 3, 1, (*methods)[64]);
  if (v28)
  {
    DrawSpiritSkillName(v28, 3, v11, 1);
  }
  if (v29 && !gohDate->spritCheck)
  {
    v31 = sdatSkillHelp(v28, 1);
    ButtonLineHelpTextSet(v31, 0, 1, 0xA09DC380, 1);
  }
  (*(*methods[8] + 376))(methods[8], v26, v25, listTop, *(u64 *)(*methods[8] + 384));
  v32 = methods[12];
  TitleText = cmpGetTitleText(7);
  (*(*v32 + 1368))(v32, TitleText, *(u64 *)(*v32 + 1376));
}

// 0x1baa530
void gohTreeSpiritDraw(gohData_t *_gohDate) {
  Il2CppClass *klass;
  u64 **methods;
  void *v5;
  void *v6;
  MenuCsrUnity *treeSpiritCsr;
  u32 listTop;
  s32 listDrwNo;
  u32 v10;
  u32 v11;
  void *DrawSpiritSkill;
  void *v13;
  s32 v14;
  void *v15;
  s32 v17;
  s32 v18;
  u32 v19;
  char *v20;
  s32 v22;
  u32 v23;
  u32 v25;
  u32 v26;
  char *v27;
  s32 v28;
  s32 v29;
  char *v31;
  u64 *v32;
  char *TitleText;
  char *v34;
  s32 listMax;
  s32 nowMax;

  klass = _get_Instance()[16].klass;
  methods = _get_Instance()[16].klass->_1.methods;
  v5 = *((void *)klass->_1.properties + 2);
  if (get_activeSelf(v5, 0))
    SetActive(v5, 0, 0);
  v6 = *((void *)klass->_1.methods + 2);
  if (!get_activeSelf(v6, 0))
    SetActive(v6, 1, 0);
  treeSpiritCsr = gohDate->treeSpiritCsr;
  listTop = treeSpiritCsr->listTop;
  listDrwNo = treeSpiritCsr->listDrwNo;
  nowMax = treeSpiritCsr->nowMax;
  listMax = treeSpiritCsr->listMax;
  v10 = -1600273536;
  v11 = 1692838528;
  DrawSpiritSkill = cmpGetDrawSpiritSkill(listTop, 4, 1);
  v13 = _ToArray(DrawSpiritSkill);
  v14 = v13[0];
  v15 = v13;
  if (!listDrwNo)
  {
    (*(*(u64 *)klass->_1.methods + 424))(klass->_1.methods, 0, 1, *(u64 *)(*(u64 *)klass->_1.methods + 432));
    v10 = 1692838528;
  }
  ((*methods)[63])(methods, 0, 1, (*methods)[64]);
  if (v14)
  {
    DrawSpiritSkillName(v14, 0, v10, 0);
  }
  if (listDrwNo)
  {
    v17 = v15[1];
    if (listDrwNo == 1)
    {
      v18 = 1;
      (*(*(u64 *)klass->_1.methods + 424))(klass->_1.methods, 1, 1, *(u64 *)(*(u64 *)klass->_1.methods + 432));
      v19 = 1692838528;
      goto LABEL_26;
    }
  }
  else
  {
    if (!gohDate->spritCheck)
    {
      v20 = sdatSkillHelp(v14, 1);
      ButtonLineHelpTextSet(v20, 0, 1, 0xA09DC380, 1);
    }
    v17 = v15[1];
  }
  v18 = 0;
  v19 = -1600273536;
LABEL_26:
  ((*methods)[63])(methods, 1, 1, (*methods)[64]);
  if (v17)
  {
    DrawSpiritSkillName(v17, 1, v19, 0);
  }
  if (!v18 || gohDate->spritCheck)
  {
    v22 = v15[2];
    v23 = -1600273536;
    if (listDrwNo != 2)
      goto LABEL_34;
    goto LABEL_33;
  }
  v34 = sdatSkillHelp(v17, 1);
  ButtonLineHelpTextSet(v34, 0, 1, 0xA09DC380, 1);
  v22 = v15[2];
  v23 = -1600273536;
  if (listDrwNo == 2)
  {
LABEL_33:
    (*(*(u64 *)klass->_1.methods + 424))(klass->_1.methods, 2, 1, *(u64 *)(*(u64 *)klass->_1.methods + 432));
    v23 = 1692838528;
  }
LABEL_34:
  ((*methods)[63])(methods, 2, 1, (*methods)[64]);
  if (v22)
  {
    DrawSpiritSkillName(v22, 2, v23, 0);
  }
  if (listDrwNo == 2)
  {
    v25 = nowMax;
    v26 = listMax;
    if (!gohDate->spritCheck)
    {
      v27 = sdatSkillHelp(v22, 1);
      ButtonLineHelpTextSet(v27, 0, 1, 0xA09DC380, 1);
    }
    v28 = v15[3];
    v29 = 0;
    v11 = -1600273536;
  }
  else
  {
    v28 = v15[3];
    if (listDrwNo == 3)
    {
      v29 = 1;
      (*(*(u64 *)klass->_1.methods + 424))(klass->_1.methods, 3, 1, *(u64 *)(*(u64 *)klass->_1.methods + 432));
    }
    else
    {
      v29 = 0;
      v11 = -1600273536;
    }
    v25 = nowMax;
    v26 = listMax;
  }
  ((*methods)[63])(methods, 3, 1, (*methods)[64]);
  if (v28)
  {
    DrawSpiritSkillName(v28, 3, v11, 0);
  }
  if (v29 && !gohDate->spritCheck)
  {
    v31 = sdatSkillHelp(v28, 1);
    ButtonLineHelpTextSet(v31, 0, 1, 0xA09DC380, 1);
  }
  (*(*methods[8] + 376))(methods[8], v26, v25, listTop, *(u64 *)(*methods[8] + 384));
  v32 = methods[12];
  TitleText = cmpGetTitleText(6);
  (*(*v32 + 1368))(v32, TitleText, *(u64 *)(*v32 + 1376));
}

// 0x1baa370
void DrawSpiritSkillName(SKLID a_id, s32 cnt, u32 a_rgba, bool raidou) {
  void *methods;
  char *LocalizeText;
  char **v11;
  char *v12;
  SBTLSKILLP_TBL *Skilltbl;
  u32 SkillIconType;
  s64 coolTime;

  methods = _get_Instance()[16].klass->_1.methods;
  if (a_id < 0)
  {
    v11 = &"CMP_STATUS_L0018";
    goto LABEL_14;
  }
  if (!a_id)
  {
    v11 = &"CMP_STATUS_L0019";
LABEL_14:
    LocalizeText = GetLocalizeText(*v11, 1);
    goto LABEL_15;
  }
  LocalizeText = sdatSkillName(a_id);
LABEL_15:
  v12 = LocalizeText;
  Skilltbl = sBtlGetSkilltbl(a_id);
  SkillIconType = cmpGetSkillIconType(Skilltbl, a_id);
  (*(*(u64 *)methods + 520))(methods, SkillIconType, cnt, *(u64 *)(*(u64 *)methods + 528));
  if (raidou)
    coolTime = (u32)Skilltbl->coolTime;
  else
    coolTime = 0xFFFFFFFFLL;
  (*(*(u64 *)methods + 472))(methods, cnt, v12, a_rgba, 0, 0, coolTime, *(u64 *)(*(u64 *)methods + 480));
}

// 0x1baab00
void gohScrollBar(s32 a_x, s32 a_y, s32 a_w, s32 a_h, s32 a_topNo, s32 a_drawNum, s32 a_listNum, ScrollBarType _barType) {
  Il2CppObject *Instance;

  Instance = _get_Instance();
  ScrollBarDraw(Instance, a_drawNum, a_listNum, a_topNo, barType, 0);
}

// 0x1baab80
void gohKarteParts(GOH_KARTE_TYPE a_type, GOH_KARTE_SORTMODE a_sort) {
  Il2CppObject *v7;
  char *v8;
  char *v9;
  Il2CppObject *Instance;
  Il2CppObject *v11;
  s32 data;

  gohGetSpriteHandle();
  if (a_type != 1)
  {
    if (!a_type)
    {
      itfIconDrawSprite(397, 83, 0, 0xFFu, 14, 109);
      itfIconDrawSprite(352, 413, 0, 0xFFu, 13, 109);
      itfIconDrawSprite(422, 413, 0, 0xFFu, 12, 109);
    }
    return;
  }
  data = GBWK->player->gold;
  v7 = Box(s32, &data);
  v8 = Format("{0,7:d}", v7, 0);
  v9 = Concat_54766928(0, v8, 0);
  Instance = _get_Instance();
  KarteRestoreHaveMoney(Instance[21].klass, v9, 0);
  v11 = _get_Instance();
  KarteRestoreTab(v11[21].klass->_1.declaringType, a_sort, 0);
  itfIconDrawSprite(96, 413, 0, 0xFFu, 15, 109);
  itfIconDrawSprite(212, 415, 0, 0xFFu, 53, 109);
  itfIconDrawSprite(244, 415, 0, 0xFFu, 54, 109);
  itfIconDrawSprite(360, 413, 0, 0xFFu, 11, 109);
  itfIconDrawSprite(422, 413, 0, 0xFFu, 13, 109);
}

// 0x1baae60
void gohKarteList(sdatUnitWork_t *pUnit, s32 UnitNums, s32 TopIndex, s32 CurrentIndex, GOH_KARTE_TYPE Type, GOH_KARTE_SORTMODE SortMode, bool _pro) {
  void *klass;
  s64 v17;
  s64 v18;
  s32 v19;
  Il2CppObject *Instance;
  s64 v22;
  s32 v23;
  sdatUnitWork_t *v25;
  void *registrationsUi;
  s32 KarteProUnitCnt;
  s32 KarteNotDlcChkCnt;
  f32 v32;
  f32 v33;
  bool v34;
  f32 v35;

  klass = _get_Instance()[21].klass;
  gohGetSpriteHandle();
  if (UnitNums >= 10)
    LODWORD(v17) = 10;
  else
    LODWORD(v17) = UnitNums;
  gohKarteParts(Type, SortMode);
  v18 = (u32)(CurrentIndex - TopIndex);
  RestoreCursorMove(klass, v18, 0);
  if (UnitNums)
  {
    if (Type)
      v19 = 2;
    else
      v19 = 1;
    Instance = _get_Instance();
    ScrollBarDraw(Instance, v17, UnitNums, TopIndex, v19, 0);
    if (UnitNums >= 1)
    {
      v22 = 0;
      v23 = TopIndex;
      if ((s32)v17 <= 1)
        v17 = 1;
      else
        v17 = (u32)v17;
      do
      {
        v25 = *(&pUnit[v23] + (s32)v22);
        gohKarteDevilParam((s32)gohDraw, v22, v25, Type, v18 == v22, pro);
        ++v22;
      }
      while (v17 != v22);
    }
    if (pro)
    {
      registrationsUi = klass->registrationsUi;
      KarteProUnitCnt = gohGetKarteProUnitCnt(GBWK->karte_list);
      Draw(registrationsUi, KarteProUnitCnt, GBWK->karte_list->karte2WakuCnt, 0);
    }
    else if (Type == 1)
    {
      if (GetKarteNotDlcChkCnt(GBWK->karte_list, 0) < 1)
      {
        v35 = 0.0;
      }
      else
      {
        KarteNotDlcChkCnt = GetKarteNotDlcChkCnt(GBWK->karte_list, 0);
        v32 = 100.0;
        v33 = (f32)((f32)KarteNotDlcChkCnt / 127.0) * 100.0;
        if (v33 <= 100.0)
          v32 = (f32)((f32)KarteNotDlcChkCnt / 127.0) * 100.0;
        v34 = v33 < 0.0;
        v35 = 0.0;
        if (!v34)
          v35 = v32;
      }
      Draw(klass->registrationRateUi, v35, 0);
    }
    return;
  }
}

// 0x1bab950
void gohModel(gohData_t *pData) {
  s32 ModelLoadCnt;
  s64 i;
  dds3ModelHandle_t *v10;
  sdfModelOt_t *v12;

  sdf3SetCamera(ScreenParam, &CameraTM, cameraObject);
  ModelLoadCnt = pData->ModelLoadCnt;
  if (ModelLoadCnt >= 1)
  {
    for (i = 0; i < ModelLoadCnt; ++i)
    {
      v10 = pData->Model[i];
      if (!v10)
        continue;
      v12 = ModelOt[0];
      Link(v10, v12);
      ModelLoadCnt = pData->ModelLoadCnt;
    }
  }
}

// 0x1babae0
char *gohRaceName(s32 a_raceID) {
  return sdatRaceName(a_raceID + 34);
}

// 0x1babb70
void gohCaption(s32 X, s32 Y, s32 No, bool _nonIconHelp) {
  s32 v8;
  char *a_str;
  const char *namespaze;
  char *v11;
  char *LocalizeText;
  Il2CppObject *v14;
  char *v15;
  char *v16;
  void *v17;
  u64 *monitor;
  s64 v20;
  Il2CppObject *v21;
  char *v22;
  s64 v23;
  char *v24;
  s64 v25;
  char *v26;
  Il2CppObject *v28;
  char *v29;
  char *v30;
  s32 gold;
  char v32[4];
  char data[4];

  gohGetSpriteHandle();
  if ((u32)(No - 5) >= 2)
    v8 = 95;
  else
    v8 = 4;
  a_str = gohCaption[No];
  itfDrawFont(0, v8, 20, 0, 0, 0, 0xA09DC380, 255.0, 108, a_str);
  namespaze = _get_Instance()[19].klass->_1.namespaze;
  v11 = gohCaption[No];
  LocalizeText = GetLocalizeText(v11, 1);
  (*(*(u64 *)namespaze + 1368))(namespaze, LocalizeText, *(u64 *)(*(u64 *)namespaze + 1376));
  data[0] = GBWK->player->para->level;
  v14 = Box(sbyte, data);
  v15 = Format("{0,2:d}", v14, 0);
  v16 = Concat_54766928(0, v15, 0);
  itfDrawFont(4, 468, 32, 0, 0, 0, 0xA09DC380, 255.0, 109, v16);
  if (No != 6 && nonIconHelp)
  {
    v17 = *((void *)_get_Instance()[18].monitor + 2);
    if (!get_activeSelf(v17, 0))
      SetActive(v17, 1, 0);
    monitor = _get_Instance()[18].monitor;
    v20 = monitor[3];
    v32[0] = GBWK->player->para->level;
    v21 = Box(sbyte, v32);
    v22 = Format("{0,2:d}", v21, 0);
    (*(*(u64 *)v20 + 1368))(v20, v22, *(u64 *)(*(u64 *)v20 + 1376));
    v23 = monitor[5];
    v24 = GetLocalizeText("GOH_CAPTION_L0068", 1);
    (*(*(u64 *)v23 + 1368))(v23, v24, *(u64 *)(*(u64 *)v23 + 1376));
    v25 = monitor[4];
    v26 = GetLocalizeText("GOH_CAPTION_L0043", 1);
    (*(*(u64 *)v25 + 1368))(v25, v26, *(u64 *)(*(u64 *)v25 + 1376));
  }
  if ((u32)No >= 2)
  {
    gold = GBWK->player->gold;
    v28 = Box(s32, &gold);
    v29 = Format("{0,7:d}", v28, 0);
    v30 = Concat_54766928(v16, v29, 0);
    itfDrawFont(3, 410, 58, 0, 0, 0, 0xA09DC380, 255.0, 109, v30);
  }
}

// 0x1bac010
void gohMagCost(s32 cost, f32 a_ratio) {
  f32 v5;
  s32 v6;
  Il2CppObject *v7;
  char *v8;
  char *a_str;
  s32 data;

  gohGetSpriteHandle();
  v5 = 128.0 - (f32)(a_ratio * 128.0);
  if (v5 == INFINITY)
    v6 = -2147483303;
  else
    v6 = (s32)v5 + 345;
  if (cost < 0)
  {
    itfDrawFont(0, v6 + 130, 75, 0, 0, 0, 0xA09DC380, (f32)(u8)(s32)(f32)(a_ratio * 255.0), 109, "?");
  }
  else
  {
    data = cost;
    v7 = Box(s32, &data);
    v8 = Format("{0,4:d}", v7, 0);
    a_str = Concat_54766928(0, v8, 0);
    itfDrawFont(3, v6 + 103, 78, 0, 0, 0, 0xA09DC380, (f32)(u8)(s32)(f32)(a_ratio * 255.0), 109, a_str);
  }
}

// 0x1bac1e0
void gohSelDevilName(s32 X, s32 Y, s32 No, f32 Ratio, gohData_t *pData) {
  s32 SelDevilStockIndex;
  s32 devilid;
  s32 kuda_id;
  s64 v13;
  CombMenuListPassPar *cmbMenuList;
  GohTextUnity *name;
  u32 v18;
  char *v19;
  Il2CppObject *v20;
  char *v21;
  char *v22;
  Il2CppObject *Instance;
  s32 data;

  gohGetSpriteHandle();
  SelDevilStockIndex = gohGetSelDevilStockIndex(pData, 0);
  devilid = GBWK->player->stock_id[SelDevilStockIndex]->devilid;
  kuda_id = sBtlGetDevilData(devilid, -1)->kuda_id;
  v13 = SelDevilStockIndex;
  cmbMenuList = gohTextPassMgr->cmbMenuList;
  cmbMenuList->kuda = kuda_id;
  name = cmbMenuList->name;
  v18 = (u8)vcvts_n_s32_f32(Ratio, 7u) | 0x64E6AA00;
  v19 = sdatDevilName(devilid, 0);
  SetText(name, v19, v18, 0);
  data = GBWK->player->stock_id[v13]->level;
  v20 = Box(s32, &data);
  v21 = Format("{0,2:d}", v20, 0);
  v22 = Concat_54766928(0, v21, 0);
  SetText(gohTextPassMgr->cmbMenuList->lv, v22, v18, 0);
  Instance = _get_Instance();
  ResultRootDevilName(Instance[19].klass, gohTextPassMgr->cmbMenuList, 0);
}

// 0x1bac4b0
void gohCalcWidth(sprHandle_t *a_hSpr, s32 a_sprNo, s32 a_num, s32 a_max) {
  ;
}

// 0x1bac4c0
bool gohCheckEnableCombine(GOHDRAW_COMBTYPE a_combtype, sdatUnitWork_t *pUnit) {
  s32 devilid;

  if ((pUnit->badstatus & 0x120000) != 0)
    return 0;
  devilid = pUnit->devilid;
  if (!DlcDevilSelCheck(devilid))
    return 0;
  return (~a_combtype & 0x12) != 0 || pUnit->chuusei >= 1;
}

// 0x1bac590
void gohDevilParamSimple(s32 X, s32 Y, sdatUnitWork_t *pUnit, s32 Mode, bool bSelect, bool bEnable, GOHDRAW_COMBTYPE _combType) {
  s32 devilid;
  s32 kuda_id;
  s32 v18;
  bool v19;
  s32 v20;
  s32 v21;
  bool v22;
  u32 v23;
  Il2CppObject *Instance;
  s8 *p_data;
  Il2CppObject *v26;
  char *v27;
  char *v28;
  char *v29;
  s32 v32;
  s32 v35;
  CombMenuListPassPar *v36;
  GohTextUnity *name;
  char *v38;
  Il2CppObject *v39;
  char *LocalizeText;
  char *v41;
  s32 v44;
  CombMenuListPassPar *cmbMenuList;
  GohTextUnity *lv;
  Il2CppObject *v47;
  s32 Age16;
  s32 v53;
  sdatPlayerUnitWork_t *v54;
  s32 swordatk;
  Il2CppObject *v59;
  char *v60;
  sdatPlayerUnitWork_t *v62;
  s32 v63;
  s8 data;
  s8 level;

  gohGetSpriteHandle();
  devilid = pUnit->devilid;
  kuda_id = sBtlGetDevilData(devilid, -1)->kuda_id;
  v18 = pUnit->devilid;
  v19 = DlcDevilSelCheck(v18);
  if (bSelect)
    v20 = 1692838528;
  else
    v20 = -1600273536;
  if (bSelect)
    v21 = 1349079155;
  else
    v21 = 1296780109;
  v22 = v19;
  if (bEnable)
    v23 = v20;
  else
    v23 = v21;
  switch (Mode)
  {
    case 0:
      Instance = _get_Instance();
      LoyaltyGaugeDraw(Instance[19].klass, Y, pUnit->chuusei, 0);
      p_data = &level;
      level = pUnit->level;
      goto LABEL_28;
    case 1:
      p_data = &data;
      data = pUnit->level;
LABEL_28:
      v26 = Box(sbyte, p_data);
      v27 = Format("{0,2:d}", v26, 0);
      v28 = Concat_54766928(0, v27, 0);
      if (v22)
        v29 = v28;
      else
        v29 = "";
      SetText(gohTextPassMgr->cmbMenuList->lv, v29, v23, 0);
      goto LABEL_34;
    case 2:
      LocalizeText = GetLocalizeText("CMP_STATUS_L0018", 1);
      v41 = Concat_54766928(0, LocalizeText, 0);
      SetText(gohTextPassMgr->cmbMenuList->name, v41, v23, 0);
      if (v22)
        v44 = kuda_id;
      else
        v44 = 0;
      cmbMenuList = gohTextPassMgr->cmbMenuList;
      lv = cmbMenuList->lv;
      cmbMenuList->kuda = v44;
      SetText(lv, 0, v23, 0);
      v47 = _get_Instance();
      CombineMenuList(v47[19].klass, Y, gohTextPassMgr->cmbMenuList, v23, combType, 0);
      return;
    case 3:
      ClassCopy(player, GBWK->player, 0);
      Age16 = evtMoonGetAge16();
      if (!Age16)
      {
        v62 = player;
        datSetPlayerUnitSword(v62, 0, 0);
        goto LABEL_63;
      }
      v53 = pUnit->devilid;
      v54 = player;
      datSetPlayerUnitSword(v54, v53, 0);
LABEL_63:
      swordatk = player->swordatk;
      v63 = swordatk - GBWK->player->swordatk;
      v59 = Box(s32, &v63);
      v60 = Format("{0,3:d}", v59, 0);
      Concat_54766928(0, v60, 0);
      return;
    default:
LABEL_34:
      if (v22)
        v32 = kuda_id;
      else
        v32 = 0;
      v35 = pUnit->devilid;
      v36 = gohTextPassMgr->cmbMenuList;
      v36->kuda = v32;
      name = v36->name;
      v38 = sdatDevilName(v35, 0);
      SetText(name, v38, v23, 0);
      gohTextPassMgr->cmbMenuList->devilId = pUnit->devilid;
      v39 = _get_Instance();
      CombineMenuList(v39[19].klass, Y, gohTextPassMgr->cmbMenuList, v23, combType, 0);
      return;
  }
}

// 0x1bacc60
void gohSwordParamSimple(gohRenkenSword_t *psSword, s32 X, s32 Y, bool bSelect, bool bEnable) {
  s32 v9;
  s32 v10;
  u32 v11;
  Il2CppObject *v12;
  char *v13;
  char *v14;
  GohTextUnity *no;
  Il2CppObject *v17;
  char *v18;
  char *v19;
  char *v20;
  Il2CppObject *v21;
  char *v22;
  char *v23;
  GohTextUnity *str;
  Il2CppObject *v25;
  char *v26;
  s32 m_iCnt;
  Il2CppObject *v28;
  char *v29;
  GohTextUnity *num;
  Il2CppObject *v33;
  char *v34;
  s16 v35[2];
  s16 m_iPower;
  s32 m_iIdx;
  s32 data;

  gohGetSpriteHandle();
  if (bSelect)
    v9 = 1692838528;
  else
    v9 = -1600273536;
  if (bSelect)
    v10 = 1349079155;
  else
    v10 = 1296780109;
  if (bEnable)
    v11 = v9;
  else
    v11 = v10;
  data = psSword->m_iIdx;
  v12 = Box(s32, &data);
  v13 = Format("{0,2:d}", v12, 0);
  v14 = Concat_54766928(0, v13, 0);
  no = gohTextPassMgr->materialList->no;
  m_iIdx = psSword->m_iIdx;
  v17 = Box(s32, &m_iIdx);
  v18 = Format("{0,2:d}", v17, 0);
  SetText(no, v18, v11, 0);
  v19 = Concat_54766928(v14, psSword->m_szSwordName, 0);
  SetText(gohTextPassMgr->materialList->name, psSword->m_szSwordName, v11, 0);
  gohTextPassMgr->materialList->type = psSword->m_iType;
  v20 = Concat_54766928(v19, psSword->m_szSkillName, 0);
  SetText(gohTextPassMgr->materialList->skillName, psSword->m_szSkillName, v11, 0);
  m_iPower = psSword->m_iPower;
  v21 = Box(s16, &m_iPower);
  v22 = Format("{0,3:d}", v21, 0);
  v23 = Concat_54766928(v20, v22, 0);
  str = gohTextPassMgr->materialList->str;
  v35[0] = psSword->m_iPower;
  v25 = Box(s16, v35);
  v26 = Format("{0,3:d}", v25, 0);
  SetText(str, v26, v11, 0);
  m_iCnt = psSword->m_iCnt;
  data = m_iCnt;
  v28 = Box(s32, &data);
  v29 = Format("{0,2:d}", v28, 0);
  Concat_54766928(v23, v29, 0);
  m_iIdx = m_iCnt;
  num = gohTextPassMgr->materialList->num;
  v33 = Box(s32, &m_iIdx);
  v34 = Format("{0,2:d}", v33, 0);
  SetText(num, v34, v11, 0);
}

// 0x1bacfe0
void gohSwordParamSimpleMake(gohData_t *pData, gohRenkenSword_t *psSword, s32 X, s32 Y, bool bSelect, bool bEnable) {
  s32 v10;
  s32 v11;
  u32 v12;
  bool v13;
  bool v15;
  char *m_szSwordName;
  char *v17;
  char *m_szSkillName;
  char *v20;
  Il2CppObject *v21;
  char *v22;
  char *v23;
  GohTextUnity *atkNum;
  Il2CppObject *v25;
  char *v26;
  s32 m_iCnt;
  Il2CppObject *v28;
  char *v29;
  GohTextUnity *haveNum;
  Il2CppObject *v33;
  char *v34;
  s32 v35;
  s32 v36;
  s16 v37[2];
  s16 data;

  gohGetSpriteHandle();
  if (bSelect)
    v10 = 1692838528;
  else
    v10 = -1600273536;
  if (bSelect)
    v11 = 1349079155;
  else
    v11 = 1296780109;
  if (bEnable)
    v12 = v10;
  else
    v12 = v11;
  v13 = gohCheckSword(psSword->m_iSwordNo);
  v15 = !v13;
  m_szSwordName = psSword->m_szSwordName;
  gohTextPassMgr->barthList->newText = v15;
  v17 = Concat_54766928(0, m_szSwordName, 0);
  SetText(gohTextPassMgr->barthList->name, psSword->m_szSwordName, v12, 0);
  m_szSkillName = psSword->m_szSkillName;
  gohTextPassMgr->barthList->type = psSword->m_iType;
  v20 = Concat_54766928(v17, m_szSkillName, 0);
  SetText(gohTextPassMgr->barthList->skill, psSword->m_szSkillName, v12, 0);
  data = psSword->m_iPower;
  v21 = Box(s16, &data);
  v22 = Format("{0,3:d}", v21, 0);
  v23 = Concat_54766928(v20, v22, 0);
  atkNum = gohTextPassMgr->barthList->atkNum;
  v37[0] = psSword->m_iPower;
  v25 = Box(s16, v37);
  v26 = Format("{0,3:d}", v25, 0);
  SetText(atkNum, v26, v12, 0);
  m_iCnt = psSword->m_iCnt;
  v36 = m_iCnt;
  v28 = Box(s32, &v36);
  v29 = Format("{0:D}", v28, 0);
  Concat_54766928(v23, v29, 0);
  v35 = m_iCnt;
  haveNum = gohTextPassMgr->barthList->haveNum;
  v33 = Box(s32, &v35);
  v34 = Format("{0:D}", v33, 0);
  SetText(haveNum, v34, v12, 0);
}

// 0x1ba9a60
void gohBaseItemParamSimple(gohRenkenSelMaterialItem_t *psItem, s32 X, s32 Y) {
  Il2CppClass *klass;
  s32 iconType;
  s32 v11;
  BarthMasyouPassPar *barthMasyou;
  u32 v13;
  s32 m_iPossessionNum;
  u32 v16;
  GohTextUnity *haveNum;
  Il2CppObject *v19;
  char *v20;
  GohTextUnity *reuiredNum;
  Il2CppObject *v22;
  char *v23;
  bool v25;
  void *properties;
  Il2CppObject *Item;
  s32 m_iNum;
  s32 data;

  klass = _get_Instance()[16].klass;
  iconType = tbldata[psItem->m_iNo]->iconType;
  v11 = psItem->m_iPossessionNum - psItem->m_iNum;
  barthMasyou = gohTextPassMgr->barthMasyou;
  barthMasyou->itmType = iconType;
  if (v11 < 0)
    v13 = 1849704703;
  else
    v13 = -1600273536;
  barthMasyou = gohTextPassMgr->barthMasyou;
  SetText(barthMasyou->materialName, psItem->m_szName, v13, 0);
  m_iPossessionNum = psItem->m_iPossessionNum;
  if (m_iPossessionNum - psItem->m_iNum < 0)
    v16 = 1849704703;
  else
    v16 = -1600273536;
  m_iPossessionNum = psItem->m_iPossessionNum;
  data = m_iPossessionNum;
  haveNum = gohTextPassMgr->barthMasyou->haveNum;
  v19 = Box(s32, &data);
  v20 = Format("{0}", v19, 0);
  SetText(haveNum, v20, v16, 0);
  reuiredNum = gohTextPassMgr->barthMasyou->reuiredNum;
  m_iNum = psItem->m_iNum;
  v22 = Box(s32, &m_iNum);
  v23 = Format("{0}", v22, 0);
  SetText(reuiredNum, v23, 0xA09DC380, 0);
  v25 = psItem->m_szName != 0;
  gohTextPassMgr->barthMasyou->slash = v25;
  if (!psItem->m_iNum)
  {
    if (!psItem->m_iPossessionNum)
    {
      Item = _get_Item(*((void *)klass->_1.properties + 7), Y);
      AllContentsClear(Item, 0);
      return;
    }
  }
  properties = klass->_1.properties;
  BarthMasyouDraw(properties, Y, gohTextPassMgr->barthMasyou, 0);
}

// 0x1bad310
void gohResultIcon(GOH_RESULT_TYPE a_type, s32 a_x, s32 a_y, bool a_bEnable) {
  Il2CppObject *Instance;

  gohGetSpriteHandle();
  Instance = _get_Instance();
  ResultRootDevilIconDraw(Instance[19].klass, a_y, a_type, 0);
}

// 0x1bad3b0
void gohCombineListFrameNormalANumber(sprHandle_t *hSpr, s32 iX, s32 iY, s32 iValue) {
  ;
}

// 0x1bad3c0
void gohCombineListFrameNormalA(s32 TopIndex, s32 SelIndex, gohData_t *pData) {
  s32 m_iDevColumn;
  void *name;
  void **v9;
  Il2CppObject *Instance;
  Il2CppObject *v11;
  Il2CppObject *v12;
  s32 v13;
  Il2CppObject *v14;
  s32 v15;
  s32 v16;
  s32 v17;
  Il2CppObject *v18;
  void *num;
  Il2CppObject *v20;
  char *v21;
  Il2CppObject *v22;
  Il2CppObject *Item;
  Il2CppObject *v24;
  char *v25;
  s64 v27;
  dat **v28;
  char *v29;
  s32 v30;
  s32 v31;
  dat *v32;
  s32 v33;
  s64 v34;
  dat **v35;
  char *v36;
  void **v37;
  s32 v38;
  s32 v39;
  s64 v40;
  s32 v41;
  s64 i;
  s32 v43;
  Il2CppObject *v44;
  s64 v45;
  s32 v46;
  s32 v47;
  s32 v48;
  s32 v49;
  s32 data;

  gohGetSpriteHandle();
  m_iDevColumn = pData->m_iDevColumn;
  name = _get_Instance()[19].klass->_1.name;
  if (!get_activeSelf(name, 0))
    SetActive(name, 1, 0);
  v9 = &gohDraw;
  Instance = _get_Instance();
  RootDevilMenuActive(Instance[19].klass, 1, 0);
  v11 = _get_Instance();
  CombinationListActive(v11[19].klass, 1, 0);
  v12 = _get_Instance();
  v13 = SelIndex - TopIndex;
  RootDevilMenuCorsor(v12[19].klass, v13, 0);
  v14 = _get_Instance();
  v47 = v13;
  CombinationListCorsor(v14[19].klass, v13, 0);
  v15 = 0;
  v46 = TopIndex;
  v16 = TopIndex + 1;
  v17 = m_iDevColumn + 1;
  v48 = m_iDevColumn;
  do
  {
    v18 = _get_Instance();
    num = GetComBineMenu1ListSet(v18[19].klass, v15, 0)->num;
    data = v16 + v15;
    v20 = Box(s32, &data);
    v21 = Format("{0}", v20, 0);
    (num->klass->vtable._66_set_text.methodPtr)(num, v21, num->klass->vtable._66_set_text.method);
    v22 = _get_Instance();
    Item = _get_Item(v22[19].klass->_1.klass->_1.name, v15);
    v49 = v17 + v15;
    v24 = Box(s32, &v49);
    v25 = Format("{0}", v24, 0);
    (Item->klass->vtable[66].methodPtr)(Item, v25, Item->klass->vtable[66].method);
    ++v15;
  }
  while (v15 != 12);
  v27 = 0;
  v28 = &dat;
  v29 = &byte_5757000;
  v30 = 18;
  v31 = v47;
  do
  {
    v32 = *v28;
    v34 = *((u64 *)&GBWK->player->stock_id[v46] + (s32)v27);
    if (*(s16 *)(v34 + 22) >= 1)
    {
      if (*((u32 *)*v9 + 56))
      {
        if ((v29[12] & 1) == 0)
          goto LABEL_26;
      }
      else
      {
        if ((v29[12] & 1) == 0)
        {
LABEL_26:
          v29[12] = 1;
        }
      }
      if ((*(u8 *)(v34 + 146) & (u8)v30) != 0)
      {
        v33 = 0;
      }
      else
      {
        v35 = v28;
        v36 = v29;
        v37 = v9;
        v38 = v30;
        v39 = *(s16 *)(v34 + 22);
        v33 = DlcDevilSelCheck(v39);
        v30 = v38;
        v9 = v37;
        v29 = v36;
        v28 = v35;
        v31 = v47;
      }
      gohDevilParamSimple(v33, v27, v34, 0, v31 == (u32)v27, v33 & 1, 8);
      v32 = *v28;
    }
    ++v27;
  }
  while (v27 != 12);
  v40 = 0;
  v41 = -v48;
  do
  {
    for (i = 0; i != 12; ++i)
    {
      v45 = *((u64 *)&pData->Result[v48] + (s32)v40 + pData->Result->bounds[1].length * (v46 + (s32)i));
      if (*(u16 *)(*(u64 *)(v45 + 32) + 22))
      {
        v43 = *(u32 *)(v45 + 24);
      }
      else if (v46 + v41 + (u32)i)
      {
        v43 = 0;
      }
      else
      {
        v43 = 6;
      }
      v44 = _get_Instance();
      CombinationListDraw(v44[19].klass, i, v40, v43, 0);
    }
    ++v40;
    --v41;
  }
  while (v40 != 12);
}

// 0x1bad830
void gohCombineListFrameNormalB(s32 SelIndex1, s32 TopIndex2, s32 SelIndex2, gohData_t *pData) {
  Il2CppObject *Instance;
  s32 v10;
  s32 i;
  Il2CppObject *v12;
  void *num;
  Il2CppObject *v14;
  char *v15;
  sdatUnitWork_t *v18;
  s32 devilid;
  s32 v20;
  s64 v21;
  s64 v22;
  Il2CppObject *v23;
  s32 v25;
  s64 v26;
  s32 v27;
  bool v29;
  bool v30;
  s32 v31;
  s64 v32;
  s32 v33;
  Il2CppObject *v35;
  sdatUnitWork_t *v37;
  s32 v38;
  sdatUnitWork_t *v39;
  bool v40;
  s32 v41;
  Il2CppObject *v42;
  sdatUnitWork_t *v43;
  s32 v44;
  bool v45;
  s32 data;

  gohGetSpriteHandle();
  Instance = _get_Instance();
  v10 = SelIndex2 - TopIndex2;
  ComBine2Corsor(Instance[19].klass, v10, 0);
  for (i = 0; i != 12; ++i)
  {
    v12 = _get_Instance();
    num = GetComBineMenu1ListSet(v12[19].klass, i, 0)->num;
    data = TopIndex2 + 1 + i;
    v14 = Box(s32, &data);
    v15 = Format("{0}", v14, 0);
    (num->klass->vtable._66_set_text.methodPtr)(num, v15, num->klass->vtable._66_set_text.method);
  }
  v18 = GBWK->player->stock_id[SelIndex1];
  goto LABEL_13;
LABEL_17:
  devilid = v18->devilid;
  v45 = DlcDevilSelCheck(devilid);
  goto LABEL_20;
LABEL_13:
  if ((v18->badstatus & 0x120000) == 0)
    goto LABEL_17;
  v45 = 0;
LABEL_20:
  v20 = TopIndex2;
  v21 = 0;
  v22 = SelIndex1;
  v44 = TopIndex2 - SelIndex1;
  do
  {
    v25 = v20 + v21;
    v26 = *((u64 *)&GBWK->player->stock_id[v20] + (s32)v21);
    if (*(s16 *)(v26 + 22) < 1)
    {
      v23 = _get_Instance();
      ResultRootDevilIconDraw(v23[19].klass, v21, -1, 0);
      goto LABEL_22;
    }
    v27 = v44 + v21;
    if (v45)
    {
      if ((*(u8 *)(v26 + 146) & 0x12) != 0)
      {
        v29 = 0;
        goto LABEL_38;
      }
      v31 = *(s16 *)(v26 + 22);
      v29 = DlcDevilSelCheck(v31);
LABEL_38:
      v30 = v27 != 0 && v29;
      goto LABEL_40;
    }
    v30 = 0;
LABEL_40:
    gohDevilParamSimple((s32)gohDraw, v21, v26, 0, v10 == (u32)v21, v30, 8);
    v32 = *((u64 *)&pData->Result[v25] + pData->Result->bounds[1].length * v22);
    if (!*(u16 *)(*(u64 *)(v32 + 32) + 22))
    {
      v42 = _get_Instance();
      ResultRootDevilIconDraw(v42[19].klass, v21, 0, 0);
      v43 = *(sdatUnitWork_t *)(*((u64 *)&pData->Result[v22] + pData->Result->bounds[1].length * v25) + 32);
      v38 = v21;
      v39 = v43;
      v40 = v10 == (u32)v21;
      v41 = 2;
      goto LABEL_51;
    }
    v33 = *(u32 *)(v32 + 24);
    gohGetSpriteHandle();
    v35 = _get_Instance();
    ResultRootDevilIconDraw(v35[19].klass, v21, v33, 0);
    if (!v27)
      goto LABEL_22;
    v37 = *(sdatUnitWork_t *)(*((u64 *)&pData->Result[v22] + pData->Result->bounds[1].length * v25) + 32);
    v38 = v21;
    v39 = v37;
    v40 = v10 == (u32)v21;
    v41 = 1;
LABEL_51:
    gohDevilParamSimple((s32)gohDraw, v38, v39, v41, v40, v30, 16);
LABEL_22:
    ++v21;
  }
  while (v21 != 12);
}

// 0x1baddb0
void gohHelpKeyAssign(sprHandle_t *hSpr, s32 iSX, s32 iSY, s32 iIconNo, s32 iMesNo) {
  itfIconDrawSprite(iSX, iSY, 0, 0xFFu, iIconNo, 109);
}

// 0x1bade40
void gohCombineListFrameSword(s32 UnitNums, s32 TopIndex, s32 SelIndex, gohData_t *pData) {
  s32 v9;
  s32 v10;
  s32 v12;
  s64 v13;
  s32 v14;
  s64 v15;
  gohRenkenSword_t *v16;
  Il2CppObject *Instance;

  gohGetSpriteHandle();
  if (UnitNums >= 11)
    v12 = 11;
  else
    v12 = UnitNums;
  if (UnitNums >= 1)
  {
    v13 = (u32)(SelIndex - TopIndex);
    v14 = TopIndex;
    if (v12 <= 1)
      v15 = 1;
    else
      v15 = v12;
    do
    {
      v16 = pData->m_sRenkenSelSword->m_asSword[v14];
      gohSwordParamSimple(v16, v9, v10, v13-- == 0, 1);
      ++v14;
      --v15;
    }
    while (v15);
  }
  Instance = _get_Instance();
  ScrollBarDraw(Instance, v12, UnitNums, TopIndex, 0, 0);
  itfIconDrawSprite(350, 413, 0, 0xFFu, 14, 109);
  itfIconDrawSprite(422, 413, 0, 0xFFu, 13, 109);
}

// 0x1bae0c0
void gohCombineListSwordMaterial(gohData_t *pData, s32 UnitNums, s32 SelIndex) {
  s32 v7;
  s32 v8;
  s32 v10;
  u64 v11;
  s64 v12;
  s64 v13;
  gohRenkenSword_t *v15;
  u16 *v16;
  char *String_54864672;
  s32 v18;
  gohRenkenSelMaterial_t *m_sRenkenSelMaterial;
  char *v21;
  s64 v22;
  gohRenkenSelMaterialItem_t *v23;
  Il2CppObject *v24;
  char *v25;
  s32 data;

  gohGetSpriteHandle();
  if (UnitNums >= 12)
    v10 = 5;
  else
    v10 = UnitNums;
  if (v10 >= 1)
  {
    v11 = 0;
    v12 = 8 * (u32)SelIndex;
    v13 = 8 * (u32)v10;
    do
    {
      v15 = pData->m_sRenkenNewSword->m_asSword[v11 / 8];
      gohSwordParamSimpleMake(gohDraw, v15, v7, v8, v12 == v11, 1);
      v11 += 8;
    }
    while (v13 != v11);
  }
  v16 = NewSpecific(char, 0x20u);
  String_54864672 = CreateString_54864672(0, v16, 0);
  m_sRenkenSelMaterial = pData->m_sRenkenSelMaterial;
  v21 = String_54864672;
  if (m_sRenkenSelMaterial->m_iMatrialCnt >= 1)
  {
    v22 = 0;
    do
    {
      v23 = m_sRenkenSelMaterial->m_asMatrial[v22];
      gohBaseItemParamSimple(v23, v18, v22);
      m_sRenkenSelMaterial = pData->m_sRenkenSelMaterial;
      ++v22;
    }
    while (v22 < m_sRenkenSelMaterial->m_iMatrialCnt);
  }
  data = m_sRenkenSelMaterial->m_iGold;
  v24 = Box(s32, &data);
  v25 = Format("{0,7:d}", v24, 0);
  Concat_54766928(v21, v25, 0);
  itfIconDrawSprite(422, 413, 0, 0xFFu, 13, 109);
}

// 0x1bae360
void gohCombineListFrameA(s32 Y, s32 TopIndex, s32 SelIndex, gohData_t *pData) {
  gohGetSpriteHandle();
  if (pData->m_eCombineType == 1)
  {
    gohCombineListFrameNormalA(TopIndex, SelIndex, pData);
    itfIconDrawSprite(196, 413, 0, 0xFFu, 14, 109);
  }
  itfIconDrawSprite(359, 413, 0, 0xFFu, 11, 109);
  itfIconDrawSprite(422, 413, 0, 0xFFu, 13, 109);
}

// 0x1bae4b0
void gohCombineListFrameB(s32 Y, s32 SelIndex1, s32 TopIndex2, s32 SelIndex2, gohData_t *pData) {
  gohGetSpriteHandle();
  if (pData->m_eCombineType == 1)
  {
    gohCombineListFrameNormalB(SelIndex1, TopIndex2, SelIndex2, pData);
    itfIconDrawSprite(196, 413, 0, 0xFFu, 14, 109);
  }
  itfIconDrawSprite(359, 413, 0, 0xFFu, 11, 109);
  itfIconDrawSprite(422, 413, 0, 0xFFu, 13, 109);
}

// 0x1bab1a0
void gohKarteDevilParam(s32 X, s32 Y, sdatUnitWork_t *pUnit, GOH_KARTE_TYPE Type, bool bSelect, bool _pro) {
  s32 devilid;
  s32 v15;
  bool v16;
  u32 uniq_code;
  bool v18;
  s32 v19;
  s32 v20;
  u32 v21;
  s32 RestoreCost;
  s32 gold;
  Il2CppObject *v28;
  char *v29;
  char *v30;
  s32 v31;
  char *v32;
  s32 v33;
  u32 v34;
  KarteDevilPassPar *karteDevil;
  s32 v37;
  GohTextUnity *name;
  char *v39;
  Il2CppObject *v40;
  char *v41;
  char *v42;
  char *v43;
  GohTextUnity *summonMoney;
  char *v47;
  KarteDevilPassPar *v49;
  KarteDevilPassPar *v50;
  Il2CppObject *v51;
  char *v52;
  char *v53;
  char *v54;
  bool v56;
  char v58;
  bool v59;
  s32 v61;
  u32 v62;
  char v64;
  bool v65;
  Il2CppClass *klass;
  bool v68;
  s32 kuda_id;
  s32 cnt;
  s32 v71;
  s32 maxhp;
  s8 v73[4];
  s32 data;

  gohGetSpriteHandle();
  devilid = pUnit->devilid;
  kuda_id = sBtlGetDevilData(devilid, -1)->kuda_id;
  v15 = pUnit->devilid;
  v16 = DlcDevilSelCheck(v15);
  if (pro)
  {
    uniq_code = pUnit->uniq_code;
    v18 = 1;
  }
  else
  {
    uniq_code = -1;
    v18 = 0;
  }
  cnt = Y;
  v71 = gohChkKarteState(pUnit->devilid, uniq_code, v18);
  v68 = pro;
  if (bSelect)
    v19 = 1692838528;
  else
    v19 = -1600273536;
  if (Type == 1)
  {
    RestoreCost = gohKarteGetRestoreCost(pUnit);
    data = RestoreCost;
    gold = GBWK->player->gold;
    v28 = Box(s32, &data);
    v29 = Format("{0,7:d}", v28, 0);
    v30 = Concat_54766928(0, v29, 0);
    if (v16)
      v31 = v19;
    else
      v31 = 1296780109;
    if (v16)
      v32 = v30;
    else
      v32 = "";
    if (RestoreCost <= gold)
      v33 = -1600273536;
    else
      v33 = 1967865216;
    if (RestoreCost <= gold)
      v21 = v31;
    else
      v21 = 1296780109;
    if (v21 == 1296780109)
      v34 = v33;
    else
      v34 = v21;
    Type = 1;
    v20 = kuda_id;
    SetText(gohTextPassMgr->karteDevil->summonMoney, v32, v34, 0);
    pro = v68;
  }
  else
  {
    v20 = kuda_id;
    if (v16)
      v21 = v19;
    else
      v21 = 1296780109;
  }
  if (!v16)
    v20 = 0;
  karteDevil = gohTextPassMgr->karteDevil;
  karteDevil->devlid = pUnit->devilid;
  karteDevil = gohTextPassMgr->karteDevil;
  karteDevil->category = v20;
  if (Type == 1 && !pro && !v71)
  {
    LogError("閲覧では来ないはず", 0);
  }
  v37 = pUnit->devilid;
  name = gohTextPassMgr->karteDevil->name;
  v39 = sdatDevilName(v37, 0);
  SetText(name, v39, v21, 0);
  v73[0] = pUnit->level;
  v40 = Box(sbyte, v73);
  v41 = Format("{0,2:d}", v40, 0);
  v42 = Concat_54766928(0, v41, 0);
  if (v16)
    v43 = v42;
  else
    v43 = "";
  SetText(gohTextPassMgr->karteDevil->lv, v43, v21, 0);
  if (Type)
  {
    if (Type == 1)
    {
      if (!v71 && !v68)
      {
        summonMoney = gohTextPassMgr->karteDevil->summonMoney;
        v47 = sdatRaceName(57);
        SetText(summonMoney, v47, v21, 0);
        LogError("来ないはず", 0);
      }
      v49 = gohTextPassMgr->karteDevil;
      v49->dvlLock = gohGetKarteLock(pUnit, v68);
      v50 = gohTextPassMgr->karteDevil;
      v50->fav = gohGetKarteFav(pUnit, v68);
    }
  }
  else
  {
    maxhp = pUnit->now->maxhp;
    v51 = Box(s32, &maxhp);
    v52 = Format("{0,3:d}", v51, 0);
    v53 = Concat_54766928(0, v52, 0);
    if (v16)
      v54 = v53;
    else
      v54 = "";
    SetText(gohTextPassMgr->karteDevil->maxHp, v54, v21, 0);
    v56 = gohChkKarteState(pUnit->devilid, pUnit->uniq_code, 0) == 0;
    v58 = !v56;
    v59 = v16 & v58;
    v61 = pUnit->devilid;
    v62 = pUnit->uniq_code;
    gohTextPassMgr->karteDevil->karte = v59;
    v56 = gohChkKarteState(v61, v62, 1) == 0;
    v64 = !v56;
    v65 = v16 & v64;
    gohTextPassMgr->karteDevil->kartePro = v65;
  }
  klass = _get_Instance()[21].klass;
  KarteDevilParDraw(klass, Type, cnt, gohTextPassMgr->karteDevil, 0);
}

// 0x1bae610
void gohRecoverParam(sdatUnitWork_t *unit, s32 X, s32 Y, bool bSelect) {
  s32 devilid;
  u32 v10;
  RecoverStatusPassPar *recoverStatus;
  GohTextUnity *name;
  char *v15;
  sdatParaWork_t *now;
  s32 maxhp;
  s32 hp;
  s32 v19;
  s32 v20;
  u32 v21;
  Il2CppObject *v22;
  char *v23;
  char *v24;
  Il2CppObject *v26;
  char *v27;
  char *v28;
  Il2CppObject *Instance;
  u32 BstNo;
  s64 v31;
  GohTextUnity *bstName;
  char *v35;
  char *LocalizeText;
  const MethodInfo_32670E0 *v39;
  Il2CppObject *v40;
  s32 v42;
  s32 data;

  gohGetSpriteHandle();
  if ((unit->flag & 2) != 0)
    devilid = 0;
  else
    devilid = unit->devilid;
  if (bSelect)
    v10 = 1692838528;
  else
    v10 = -1600273536;
  recoverStatus = gohTextPassMgr->recoverStatus;
  recoverStatus->devilID = devilid;
  if (devilid)
  {
    name = recoverStatus->name;
    goto LABEL_17;
  }
  {
    devilid = 241;
    name = recoverStatus->name;
  }
  else
  {
    devilid = 241;
    name = gohTextPassMgr->recoverStatus->name;
  }
LABEL_17:
  v15 = sdatDevilName(devilid, 0);
  SetText(name, v15, v10, 0);
  now = unit->now;
  hp = now->hp;
  maxhp = now->maxhp;
  data = hp;
  if (hp >= maxhp >> 2)
    v19 = -1264556928;
  else
    v19 = 1967865216;
  if (hp >= maxhp >> 1)
    v20 = -1600273536;
  else
    v20 = v19;
  if (bSelect)
    v21 = 1692838528;
  else
    v21 = v20;
  v22 = Box(s32, &data);
  v23 = Format("{0,3:d}", v22, 0);
  v24 = Concat_54766928(0, v23, 0);
  SetText(gohTextPassMgr->recoverStatus->hp, v24, v21, 0);
  v42 = unit->now->maxhp;
  v26 = Box(s32, &v42);
  v27 = Format("{0,3:d}", v26, 0);
  v28 = Concat_54766928(0, v27, 0);
  SetText(gohTextPassMgr->recoverStatus->maxHp, v28, v10, 0);
  Instance = _get_Instance();
  RecoverHpGaugeDraw(Instance[21].monitor, Y, unit->now->hp, unit->now->maxhp, 0);
  BstNo = cmpGetBstNo(unit->badstatus);
  if (BstNo != 22)
  {
    itfIconDrawBadStatus((X >> 4) + 260, (Y >> 3) - 1, 0, 0xFFu, BstNo, 109);
    switch (BstNo)
    {
      case 0xAu:
        v31 = 1;
        break;
      case 0xBu:
        v31 = 2;
        break;
      case 0x11u:
        v31 = 0;
        break;
      default:
        goto LABEL_52;
    }
    bstName = gohTextPassMgr->recoverStatus->bstName;
    v35 = strBstName[v31];
    LocalizeText = GetLocalizeText(v35, 1);
    SetText(bstName, LocalizeText, 0xA09DC380, 0);
  }
LABEL_52:
  v39 = Method_Project_SingletonMonoBehaviour_GohCanvasManager__get_Instance__;
  gohTextPassMgr->recoverStatus->bst = BstNo;
  v40 = _get_Instance(v39);
  RecoverStatusParDraw(v40[21].monitor, gohTextPassMgr->recoverStatus, Y, 0);
}

// 0x1baeab0
void gohRecoverList(gohGeneralList_t *pGeneralList, s32 ListNums, s32 TopIndex, s32 CurrentIndex) {
  void *monitor;
  char *v11;
  char *LocalizeText;
  void *v13;
  s32 v14;
  _BOOL4 v16;
  s32 m_DevilCnt;
  Il2CppObject *v18;
  char *v19;
  char *v20;
  Il2CppObject *Instance;
  Il2CppObject *v23;
  s32 v25;
  s64 v26;
  s64 v27;
  s64 v28;
  Il2CppObject *v29;
  char *v30;
  sdatPlayerUnitWork_t *m_pPlayer;
  sdatUnitWork_t *para;
  s32 *v33;
  sdatUnitWork_t *v35;
  Il2CppObject *v36;
  Il2CppObject *Item;
  Il2CppObject *v39;
  s32 v40;
  s32 Y;
  s32 v42;
  s32 m_PlayerVal;
  s32 data;

  monitor = _get_Instance()[17].monitor;
  v11 = strGohMenu[2];
  LocalizeText = GetLocalizeText(v11, 1);
  TitleDraw(monitor, 0, LocalizeText, 0);
  v13 = *((void *)_get_Instance()[21].monitor + 2);
  if (!get_activeSelf(v13, 0))
    SetActive(v13, 1, 0);
  gohGetSpriteHandle();
  v14 = CurrentIndex;
  v16 = pGeneralList->m_pPlayer != 0;
  if (pGeneralList->m_pPlayer)
    m_DevilCnt = pGeneralList->m_DevilCnt + 1;
  else
    m_DevilCnt = pGeneralList->m_DevilCnt;
  data = GBWK->player->gold;
  v18 = Box(s32, &data);
  v19 = Format("{0,7:d}", v18, 0);
  v20 = Concat_54766928(0, v19, 0);
  SetText(gohTextPassMgr->recover->haveManay, v20, 0xA09DC380, 0);
  Instance = _get_Instance();
  RecoverCursorMove(Instance[21].monitor, v14 - TopIndex, 0);
  if (!m_DevilCnt)
    return;
  v23 = _get_Instance();
  ScrollBarDraw(v23, ListNums, m_DevilCnt, TopIndex, 3, 0);
  v25 = TopIndex + ListNums;
  if (TopIndex + ListNums > TopIndex)
  {
    v26 = 0;
    Y = -TopIndex;
    v27 = v14 - (s64)TopIndex;
    v28 = -(s64)TopIndex;
    v40 = TopIndex - v16;
    do
    {
      if (v28 == v26 && (m_pPlayer = pGeneralList->m_pPlayer) != 0)
      {
        para = m_pPlayer->para;
        gohRecoverParam(para, 0, Y, v27 == v26);
        if (v27 != v26)
          goto LABEL_23;
        v33 = &m_PlayerVal;
        m_PlayerVal = pGeneralList->m_PlayerVal;
      }
      else
      {
        v35 = *(&pGeneralList->m_pDevil[v40] + (s32)v26);
        gohRecoverParam(v35, 0, v26, v27 == v26);
        if (v27 != v26)
          goto LABEL_23;
        v33 = &v42;
        v42 = pGeneralList->m_DevilVal[v40 + (s32)v26];
      }
      v29 = Box(s32, v33);
      v30 = Format("{0,7:d}", v29, 0);
      v20 = Concat_54766928(0, v30, 0);
LABEL_23:
      ++v26;
    }
    while (ListNums != (u32)v26);
  }
  for (; v25 < *(u32 *)(*((u64 *)_get_Instance()[21].monitor + 11) + 24); ++v25)
  {
    v36 = _get_Instance();
    Item = _get_Item(*((void *)v36[21].monitor + 11), v25);
    ListContentsClear(Item, 0);
  }
  SetText(gohTextPassMgr->recover->recoverMoney, v20, 0xA09DC380, 0);
  itfIconDrawSprite(422, 413, 0, 0xFFu, 13, 109);
  v39 = _get_Instance();
  RecoverParDraw(v39[21].monitor, gohTextPassMgr->recover, 0);
}

// 0x1baf020
void gohCombineIconHelpHatena(sprHandle_t *hSpr, s32 x, s32 y) {
  ;
}

// 0x1baf030
void gohCombineIconHelp(void) {
  gohGetSpriteHandle();
  evtBitCheck(2094);
  evtBitCheck(2095);
}

// 0x1baf0a0
void gohStatusHelp(CMP_STATUS_SEQ_TYPE a_seqtype, CMP_STATUS_TYPE a_type, CMP_STATUS_MODE a_mode, u8 a_alphaRate) {
  signed s64 v10;
  s32 v12;
  s32 v13;
  u32 v14;
  s32 v15;
  void *namespaze;
  void *data;
  char **v18;
  void *v19;
  Il2CppObject *Instance;
  Il2CppObject *v22;
  void *v23;
  void *v24;
  void *v25;
  void *v26;
  char *LocalizeText;

  gohGetSpriteHandle();
  if (a_seqtype != 18546688)
  {
    if (a_seqtype)
      return;
  }
  v10 = a_type & 0xFFFFFFFFFFFFFDFFLL;
  if ((a_type & 0x30000000) != 0 && (a_type & 0x280000) == 0x80000)
  {
    fclChkMessageDraw();
  }
  if (v10 <= 268566529)
  {
    if (v10 != 268500993)
    {
      if (v10 == 268500994)
        goto LABEL_47;
      if (v10 != 268566529)
        goto LABEL_39;
    }
    namespaze = _get_Instance()[10].klass->_1.namespaze;
    if (!get_activeSelf(namespaze, 0))
      SetActive(namespaze, 1, 0);
    data = _get_Instance()[10].klass->_1.byval_arg.data;
    v18 = &"GOH_CAPTION_L0048";
    goto LABEL_64;
  }
  if ((u64)v10 <= 0x10080001)
  {
    if (v10 != 268566530)
    {
      if (v10 == 268959745)
      {
        v19 = _get_Instance()[10].klass->_1.namespaze;
        if (!get_activeSelf(v19, 0))
          SetActive(v19, 1, 0);
        data = _get_Instance()[10].klass->_1.byval_arg.data;
        v18 = &"GOH_CAPTION_L0050";
        goto LABEL_64;
      }
      goto LABEL_39;
    }
LABEL_47:
    v23 = _get_Instance()[10].klass->_1.namespaze;
    if (!get_activeSelf(v23, 0))
      SetActive(v23, 1, 0);
    data = _get_Instance()[10].klass->_1.byval_arg.data;
    v18 = &"GOH_CAPTION_L0049";
    goto LABEL_64;
  }
  if (v10 == 268959746)
  {
    v24 = _get_Instance()[10].klass->_1.namespaze;
    if (!get_activeSelf(v24, 0))
      SetActive(v24, 1, 0);
    data = _get_Instance()[10].klass->_1.byval_arg.data;
    v18 = &"GOH_CAPTION_L0051";
    goto LABEL_64;
  }
  if (v10 != 537919488)
  {
LABEL_39:
    if ((a_type & 0x100) == 0)
      goto LABEL_65;
    if ((a_type & 0x40000) != 0)
    {
      v25 = _get_Instance()[10].klass->_1.namespaze;
      if (get_activeSelf(v25, 0))
        SetActive(v25, 0, 0);
      v26 = _get_Instance()[8].klass->_1.namespaze;
      if (!get_activeSelf(v26, 0))
        SetActive(v26, 1, 0);
      data = _get_Instance()[8].klass->_1.byval_arg.data;
      v18 = &"GOH_RENKEN_L0009";
    }
    else
    {
      if (resultCheck)
      {
LABEL_65:
        goto LABEL_66;
      }
      Instance = _get_Instance();
      sub_1BB07C0(Instance[8].klass->_1.namespaze, 0, 0);
      v22 = _get_Instance();
      sub_1BB07C0(v22[10].klass->_1.namespaze, 1, 0);
      data = _get_Instance()[10].klass->_1.byval_arg.data;
      v18 = &"GOH_CAPTION_L0052";
    }
LABEL_64:
    LocalizeText = GetLocalizeText(*v18, 1);
    (*(*(u64 *)data + 1368))(data, LocalizeText, *(u64 *)(*(u64 *)data + 1376));
    goto LABEL_65;
  }
  if (fclChkMessageDraw() == 1)
    goto LABEL_65;
  if (a_mode == 2)
  {
    itfIconDrawSprite(80, 413, 0, a_alphaRate, 84, 109);
    itfIconDrawSprite(143, 414, 0, a_alphaRate, 85, 109);
    itfIconDrawSprite(215, 409, 0, a_alphaRate, 86, 109);
    v12 = 315;
    v13 = 414;
    v14 = a_alphaRate;
    v15 = 14;
  }
  else
  {
    itfIconDrawSprite(230, 413, 0, a_alphaRate, 11, 109);
    itfIconDrawSprite(297, 413, 0, a_alphaRate, 14, 109);
    v12 = 361;
    v13 = 413;
    v14 = a_alphaRate;
    v15 = 12;
  }
  itfIconDrawSprite(v12, v13, 0, v14, v15, 109);
  if (fclChkMessageDraw())
    return;
  goto LABEL_73;
LABEL_66:
  if (fclChkMessageDraw())
    return;
LABEL_73:
  if (v10 == 268697856)
  {
    itfIconDrawSprite(361, 413, 0, a_alphaRate, 12, 109);
  }
  if ((a_type & 0x11B0000) == 0)
  {
    itfIconDrawSprite(422, 413, 0, a_alphaRate, 13, 109);
  }
}
