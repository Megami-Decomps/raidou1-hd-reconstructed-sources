#include "types.h"
#include "RSkillTab.h"
#include "SKLID.h"
#include "buttonguide.h"
#include "cmpmain.h"
#include "cmpomoide.h"
#include "cmpraidouskill.h"
#include "cmpstatus.h"
#include "dat.h"
#include "dds3_pad.h"
#include "dds3kernelcore.h"
#include "kernel.h"
#include "localize.h"
#include "rspecialskill.h"
#include "rspecialskillstatus.h"
#include "sbtlplayer.h"
#include "sbtlskill.h"
#include "sdat.h"

#define POSSESSION_LIST_DISPLAY_MAX 6
#define BATTLE_SKL_LIST_MAX 3
#define SWORD_SKL_LIST_MAX 8
#define SET_SIDE_MIN_IDX 0
#define SET_SIDE_MAX_IDX 10
#define POSSESSION_SIDE_MIN_IDX 14
#define POSSESSION_SIDE_MAX_IDX 19

typedef struct MenuCsrUnity SpecialSkillCsr;
typedef struct dds3ProcessID_t dds3ProcessID_t;
typedef struct tagSPECIAL_SKILL_STATUS_WORK tagSPECIAL_SKILL_STATUS_WORK;

static sdfColor32_t NORMAL_COLOR;
static sdfColor32_t SELECT_COLOR;
static sdfColor32_t SET_COLOR;
static void *arrSwordSklID;
static void *arrBattleSklID;
static s32 m_change_pos;
s32 m_change_listTop;
static s32 m_chaneg_csrNo;
static LIST_SELECT m_change_list_side;
void *skillListSelect;
static bool m_is_btl_skill_sort;
static bool m_is_sword_skill_sort;
static s32 m_before_idx;
static SKLID *m_before_skl;
dds3ProcessID_t *g_mainPID;
static void *m_csr_save_list;
static bool isDrag;
static bool isCsrDrag;
static bool isCsrDragCalc;

static void SwordCsrUp(tagSPECIAL_SKILL_STATUS_WORK *wk, bool _trg, bool _rep);
static void SwordCsrDown(tagSPECIAL_SKILL_STATUS_WORK *wk, bool _trg, bool _rep);
static void ListChange(LIST_SELECT listSelect, bool isMouse);
static bool SameOriginal(tagSPECIAL_SKILL_STATUS_WORK *wk);
static bool SelectOtherSide(tagSPECIAL_SKILL_STATUS_WORK *wk);
static void ButtonGuideNormal(tagSPECIAL_SKILL_STATUS_WORK *wk);
static void ButtonGuideGoh(tagSPECIAL_SKILL_STATUS_WORK *wk);
static void SetSkillCsrUpdate(tagSPECIAL_SKILL_STATUS_WORK *wk);
static void BtlSetSideDecisionPattern(tagSPECIAL_SKILL_STATUS_WORK *wk);
static void SetSideDecisionPattern(tagSPECIAL_SKILL_STATUS_WORK *wk);
static void UpdateSetSkillNameColor(RSkillTab tab, s32 csrNo, s32 dispNo);
static bool IsAutoArrange(s32 startIdx);
static void SkillCsrUpdate(tagSPECIAL_SKILL_STATUS_WORK *wk);
static void PossessionSideDecisionPattern(tagSPECIAL_SKILL_STATUS_WORK *wk);
static void BtlPossessionSideDecisionPattern(tagSPECIAL_SKILL_STATUS_WORK *wk);
static void UpdateSkillNameColor(RSkillTab tab, s32 csrNo, s32 dispNo, SKLID id);
static void InitSkillNameColor(void);

// 0x1e1c560
static void SwordCsrUp(tagSPECIAL_SKILL_STATUS_WORK *wk, bool _trg, bool _rep) {
  SpecialSkillCsr *v5;
  s32 listMax;
  s32 nowMax;
  s32 listDrwNo;
  s32 csrNo;
  s32 listTop;
  s32 v11;
  s32 v12;
  bool v13;
  s32 v14;
  s32 v15;
  bool v16;
  s32 v17;

  v5 = wk->csr[wk->tab];
  listMax = v5->listMax;
  listDrwNo = v5->listDrwNo;
  nowMax = v5->nowMax;
  csrNo = v5->csrNo;
  listTop = v5->listTop;
  if (nowMax < listMax)
    listMax = v5->nowMax;
  if (!trg)
  {
    if (!rep)
      goto LABEL_47;
    v11 = csrNo - 2;
    if ((csrNo & 1) == 0)
    {
      if (v11 < 0)
      {
        v11 = 0;
        if (!csrNo)
          goto LABEL_47;
        goto LABEL_46;
      }
      goto LABEL_23;
    }
    if (v11 < 1)
    {
      v11 = 1;
      if (csrNo == 1)
        goto LABEL_47;
      goto LABEL_46;
    }
LABEL_40:
    if (listDrwNo - 2 <= 1)
      listDrwNo = 1;
    else
      listDrwNo -= 2;
    goto LABEL_46;
  }
  v11 = csrNo - 2;
  if ((csrNo & 1) == 0)
  {
    if (v11 < 0)
    {
      v12 = nowMax - 1;
      v13 = (listMax & 1) == 0;
      if ((listMax & 1) != 0)
        v14 = listMax - 1;
      else
        v14 = listMax - 2;
      if (v13)
        v12 = nowMax - 2;
      if (nowMax)
        listDrwNo = v14;
      else
        listDrwNo = 0;
      if (nowMax)
        v11 = v12;
      else
        v11 = 0;
      if (csrNo == v11)
        goto LABEL_47;
LABEL_46:
      SE(3);
      csrNo = v11;
      v5 = wk->csr[wk->tab];
      goto LABEL_47;
    }
LABEL_23:
    listDrwNo = (listDrwNo - 2) & ~((listDrwNo - 2) >> 31);
    goto LABEL_46;
  }
  if (v11 > 0)
    goto LABEL_40;
  v15 = nowMax - 2;
  v16 = (listMax & 1) == 0;
  if ((listMax & 1) != 0)
    v17 = listMax - 2;
  else
    v17 = listMax - 1;
  if (v16)
    v15 = nowMax - 1;
  if (nowMax >= 3)
    listDrwNo = v17;
  else
    listDrwNo = 1;
  if (nowMax >= 3)
    v11 = v15;
  else
    v11 = 1;
  if (csrNo != v11)
    goto LABEL_46;
LABEL_47:
  v5->listTop = listTop;
  v5->listDrwNo = listDrwNo;
  v5->csrNo = csrNo;
}

// 0x1e1c6b0
static void SwordCsrDown(tagSPECIAL_SKILL_STATUS_WORK *wk, bool _trg, bool _rep) {
  SpecialSkillCsr *v5;
  s32 listMax;
  s32 nowMax;
  s32 listDrwNo;
  s32 csrNo;
  s32 listTop;
  signed s32 v11;
  signed s32 v12;
  s32 v13;
  s32 v14;
  s32 v15;
  signed s32 v16;
  u32 v17;
  SpecialSkillCsr *v18;

  v5 = wk->csr[wk->tab];
  listMax = v5->listMax;
  listDrwNo = v5->listDrwNo;
  nowMax = v5->nowMax;
  csrNo = v5->csrNo;
  listTop = v5->listTop;
  if (nowMax < listMax)
    listMax = v5->nowMax;
  if (trg)
  {
    v11 = csrNo + 2;
    if ((csrNo & 1) == 0)
    {
      if (v11 > (s32)((nowMax | 0xFFFFFFFE) + nowMax))
      {
        listDrwNo = 0;
        v12 = 0;
        goto LABEL_16;
      }
LABEL_10:
      v13 = listMax + (listMax & 1);
      v14 = v13 - 1;
      v15 = v13 - 2;
      if (listDrwNo + 2 >= v14)
        listDrwNo = v15;
      else
        listDrwNo += 2;
      goto LABEL_21;
    }
    if (v11 > (s32)(v5->nowMax + (~LOBYTE(v5->nowMax) | 0xFFFFFFFE)))
    {
      listDrwNo = 1;
      v12 = 1;
      goto LABEL_16;
    }
LABEL_18:
    v16 = listMax & 0xFFFFFFFE;
    v17 = (listMax & 0xFFFFFFFE) - 1;
    if (listDrwNo + 2 >= v16)
      listDrwNo = v17;
    else
      listDrwNo += 2;
    goto LABEL_21;
  }
  if (!rep)
  {
LABEL_17:
    v5->listTop = listTop;
    v5->listDrwNo = listDrwNo;
    v5->csrNo = csrNo;
    return;
  }
  v11 = csrNo + 2;
  if ((csrNo & 1) != 0)
  {
    v12 = v5->nowMax + (~LOBYTE(v5->nowMax) | 0xFFFFFFFE);
    if (v11 <= v12)
      goto LABEL_18;
  }
  else
  {
    v12 = (nowMax | 0xFFFFFFFE) + nowMax;
    if (v11 <= v12)
      goto LABEL_10;
  }
LABEL_16:
  v11 = v12;
  if (csrNo == v12)
    goto LABEL_17;
LABEL_21:
  SE(3);
  v18 = wk->csr[wk->tab];
  v18->listTop = listTop;
  v18->listDrwNo = listDrwNo;
  v18->csrNo = v11;
}

// 0x1e1c7f0
void RSpecialSkillInit(tagSPECIAL_SKILL_STATUS_WORK *wk) {
  SpecialSkillCsr *v3;
  SpecialSkillCsr *v4;
  SpecialSkillCsr **p_skillCsr;
  SpecialSkillCsr *csr;
  SpecialSkillCsr *v7;
  SpecialSkillCsr *v8;
  SpecialSkillCsr *v9;
  SpecialSkillCsr *v10;
  SpecialSkillCsr *v11;
  SpecialSkillCsr *v12;
  SpecialSkillCsr *v13;
  __int128 v15;
  void *v18;
  s64 v21;
  s64 v23;
  s64 v24;
  void *v26;
  u64 *v30;
  void *v31;
  s64 size;
  void *items;
  void *v34;
  u64 *v35;
  s64 v36;
  void *v37;

  v3 = NewSpecific(SpecialSkillCsr, 2u);
  wk->csr = v3;
  v4 = NewSpecific(SpecialSkillCsr, 2u);
  wk->skillCsr = v4;
  p_skillCsr = &wk->skillCsr;
  csr = wk->csr;
  v7 = Allocate(SpecialSkillCsr);
  _ctor(v7, 0);
  csr[0] = v7;
  v8 = *p_skillCsr;
  v9 = Allocate(SpecialSkillCsr);
  _ctor(v9, 0);
  v8[0] = v9;
  v10 = wk->csr;
  v11 = Allocate(SpecialSkillCsr);
  _ctor(v11, 0);
  v10[1] = v11;
  v12 = *p_skillCsr;
  v13 = Allocate(SpecialSkillCsr);
  _ctor(v13, 0);
  v12[1] = v13;
  wk->possSkillCsr = 0;
  wk->sklCsr = 0;
  *(u64 *)&v15 = -1;
  *((u64 *)&v15 + 1) = -1;
  HIDWORD(skillListSelect) = 0;
  *(_OWORD *)&arrBattleSklID = v15;
  v18 = NewSpecific(SKLID, 3u);
  *(u64 *)&m_is_btl_skill_sort = v18;
  v21 = *(u64 *)&m_is_btl_skill_sort;
  *(u32 *)(v21 + 32) = 0;
  *(u32 *)(v21 + 32) = GBWK->player->raidouSkill[0];
  v23 = *(u64 *)&m_is_btl_skill_sort;
  *(u32 *)(v23 + 36) = 0;
  *(u32 *)(v23 + 36) = GBWK->player->raidouSkill[1];
  v24 = *(u64 *)&m_is_btl_skill_sort;
  *(u32 *)(v24 + 40) = 0;
  *(u32 *)(v24 + 40) = GBWK->player->raidouSkill[2];
  v26 = Allocate(System_Collections_Generic_List_LIST_SELECT_);
  __ctor_47784064(v26, 2);
  *(u64 *)&m_chaneg_csrNo = v26;
  v30 = Method_System_Collections_Generic_List_LIST_SELECT__Add__;
  v31 = *(void *)&m_chaneg_csrNo;
  size = v31->_size;
  ++v31->_version;
  items = v31->_items;
  if ((u32)size >= LODWORD(items->max_length))
  {
    _AddWithResize(v31, 0, *(const MethodInfo_2D92A30 **)(*(u64 *)(v30[4] + 192) + 112));
    goto LABEL_30;
  }
  else
  {
    v31->_size = size + 1;
    *((u32 *)items + size) = 0;
    goto LABEL_30;
  }
LABEL_30:
  v34 = *(void *)&m_chaneg_csrNo;
  v35 = Method_System_Collections_Generic_List_LIST_SELECT__Add__;
  v36 = v34->_size;
  ++v34->_version;
  v37 = v34->_items;
  if ((u32)v36 >= LODWORD(v37->max_length))
  {
    _AddWithResize(v34, 0, *(const MethodInfo_2D92A30 **)(*(u64 *)(v35[4] + 192) + 112));
  }
  else
  {
    v34->_size = v36 + 1;
    *((u32 *)v37 + v36) = 0;
  }
}

// 0x1e1ccb0
void Exit(tagSPECIAL_SKILL_STATUS_WORK *wk) {
  struct sdfColor32_t SET_COLOR_local;
  s64 v9;
  SpecialSkillCsr *csr;
  SpecialSkillCsr **p_csr;
  SpecialSkillCsr **p_skillCsr;
  SpecialSkillCsr *skillCsr;
  SpecialSkillCsr *v17;
  SpecialSkillCsr *v18;
  s32 v19;
  s32 v20;
  s32 v21;

  SET_COLOR_local = SET_COLOR;
  if (!*(u64 *)&SET_COLOR_local)
  {
    goto LABEL_5;
  }
  SET_COLOR_local = SET_COLOR;
  v19 = *(u32 *)(*(u64 *)&SET_COLOR_local + 28) + 1;
  SET_COLOR = 0;
  *(u32 *)(*(u64 *)&SET_COLOR_local + 24) = 0;
  *(u32 *)(*(u64 *)&SET_COLOR_local + 28) = v19;
LABEL_5:
  if (!arrSwordSklID)
  {
    goto LABEL_7;
  }
  v20 = arrSwordSklID->_version + 1;
  arrSwordSklID = 0;
  arrSwordSklID->_size = 0;
  arrSwordSklID->_version = v20;
LABEL_7:
  v9 = *(u64 *)&m_chaneg_csrNo;
  if (!v9)
  {
    goto LABEL_9;
  }
  v9 = *(u64 *)&m_chaneg_csrNo;
  v21 = *(u32 *)(v9 + 28) + 1;
  *(u64 *)&m_chaneg_csrNo = 0;
  *(u32 *)(v9 + 24) = 0;
  *(u32 *)(v9 + 28) = v21;
LABEL_9:
  *(u64 *)&m_is_btl_skill_sort = 0;
  if (g_mainPID)
  {
    object___Clear(g_mainPID);
    g_mainPID = 0;
  }
  if (wk)
  {
    p_csr = &wk->csr;
    csr = wk->csr;
    csr[0] = 0;
    skillCsr = wk->skillCsr;
    p_skillCsr = &wk->skillCsr;
    skillCsr[0] = 0;
    v17 = *p_csr;
    v17[1] = 0;
    v18 = *p_skillCsr;
    v18[1] = 0;
    *p_csr = 0;
    *p_skillCsr = 0;
  }
}

// 0x1e13430
dds3ProcessID_t *RSpecialSkillProcessStart(bool goh) {
  bool v3;
  tagSPECIAL_SKILL_STATUS_WORK *v4;
  dds3ProcessFunc_t v7;
  shutdownfuncDelegate v8;
  dds3ProcessID_t *started;
  dds3ProcessFunc_t v11;
  dds3ProcessID_t *v12;

  v3 = goh;
  v4 = Allocate(tagSPECIAL_SKILL_STATUS_WORK);
  _ctor(v4, 0);
  RSpecialSkillInit(v4);
  v4->goh = v3;
  v7 = Allocate(dds3ProcessFunc_t);
  _ctor(v7, 0, Method_Project_RSpecialSkillStatus_Process__, 0);
  v8 = Allocate(shutdownfuncDelegate);
  _ctor(v8, 0, Method_Project_RSpecialSkillStatus_Shutdown__, 0);
  started = dds3StartProcess("skill_status_main", 1023, 0, 0, v7, v8, v4);
  m_before_skl = (SKLID *)started;
  v11 = Allocate(dds3ProcessFunc_t);
  _ctor(v11, 0, Method_Project_RSpecialSkillStatus_DrawProcess__, 0);
  v12 = dds3StartProcess("skill_status_draw", 11029, 0, 0, v11, 0, v4);
  v4->drawPID = v12;
  RSpecialSkillLoadCsr();
  return (dds3ProcessID_t *)m_before_skl;
}

// 0x1e1d950
dds3ProcessFunc_t RSpecialSkillProcess(dds3ProcessID_t *PID) {
  return 0;
}

// 0x1e1d960
dds3ProcessFunc_t RSpecialSkillDrawProcess(dds3ProcessID_t *PID) {
  return 0;
}

// 0x1e1d970
void RSpecialSkillShutdown(dds3ProcessID_t *PID) {
  tagSPECIAL_SKILL_STATUS_WORK *ProcessData;
  dds3ProcessID_t *p_drawPID;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  Exit(ProcessData, tagSPECIAL_SKILL_STATUS_WORK);
  p_drawPID = &ProcessData->drawPID;
  if (dds3ExistProcess(p_drawPID))
  {
    dds3KillProcess(p_drawPID, 0);
    p_drawPID = 0;
  }
  m_before_skl = 0;
}

// 0x1e14e00
void RSpecialSkillResetCoolTime(void) {
  s32 v4;
  s32 v8;
  s32 v12;

  v4 = *(u32 *)(*(u64 *)&m_is_btl_skill_sort + 32);
  if (v4 == GBWK->player->raidouSkill[0])
  {
    goto LABEL_6;
  }
  sBtlRaidouWazaCoolTimeClr(0);
LABEL_6:
  v8 = *(u32 *)(*(u64 *)&m_is_btl_skill_sort + 36);
  if (v8 == GBWK->player->raidouSkill[1])
  {
    goto LABEL_9;
  }
  sBtlRaidouWazaCoolTimeClr(1);
LABEL_9:
  v12 = *(u32 *)(*(u64 *)&m_is_btl_skill_sort + 40);
  if (v12 != GBWK->player->raidouSkill[2])
  {
    sBtlRaidouWazaCoolTimeClr(2);
  }
}

// 0x1e1cf50
void RSpecialSkillLoadCsr(void) {
  tagCMP_WORK *Work;
  RskillCsr *v4;
  void *v5;
  System_RuntimeTypeHandle_o v8;
  void *v9;
  void *v10;
  void *v11;
  System_Collections_IEnumerator_c *v13;
  s64 v14;
  s32 *v15;
  s64 v16;
  void *v17;
  System_Collections_IEnumerator_c *v18;
  s64 v19;
  System_Collections_IEnumerator_c **v20;
  s64 v21;
  Il2CppObject *v22;
  System_RuntimeTypeHandle_o v23;
  void *v24;
  Il2CppObject *v25;
  s32 v26;
  RaidouSKillCsrSave *rSkillCsrSave;
  RaidouSKillCsrSave *v28;
  Il2CppObject *Item;
  u64 *v31;
  s64 v32;
  u64 *v33;
  s64 v34;
  s32 *v35;
  s64 v36;
  RskillCsr *v37;
  void *v39;
  System_RuntimeTypeHandle_o v42;
  void *TypeFromHandle;
  void *Values;
  void *v45;
  System_Collections_IEnumerator_c *klass;
  s64 v47;
  s32 *p_offset;
  s64 v49;
  void *v50;
  System_Collections_IEnumerator_c *v51;
  s64 v52;
  System_Collections_IEnumerator_c **v53;
  s64 v54;
  Il2CppObject *v55;
  System_RuntimeTypeHandle_o v56;
  void *v57;
  Il2CppObject *v58;
  s32 v59;
  u64 *Interface;
  s64 v62;
  u64 *v63;
  s64 v64;
  s32 *v65;
  s64 v66;
  s64 v67;
  void *p_Enumerator;
  u64 *v69;
  u64 *v70;
  void *Enumerator;

  v70 = 0;
  Enumerator = 0;
  dds3GetProcessData(m_before_skl);
  if (!cmpProcessCheck())
  {
    v37 = Allocate(RskillCsr);
    *(u64 *)&v37->csrNo = 0;
    v37->listDrwNo = 0;
    v39 = Allocate(System_Collections_Generic_Dictionary_RSkillCsrType__RskillCsr_);
    object____ctor(v39);
    g_mainPID = (dds3ProcessID_t *)v39;
    v42.value = Project_RSkillCsrType_var;
    TypeFromHandle = GetTypeFromHandle(v42, 0);
    Values = GetValues(TypeFromHandle, 0);
    Enumerator = GetEnumerator(Values, 0);
    v67 = 0;
    p_Enumerator = &Enumerator;
    v69 = &v70;
    while (1)
    {
      v45 = Enumerator;
      klass = Enumerator->klass;
      v47 = *(u16 *)&Enumerator->klass->_2.rank;
      if (*(u16 *)&Enumerator->klass->_2.rank)
      {
        p_offset = &klass->_1.interfaceOffsets->offset;
        while (*((System_Collections_IEnumerator_c **)p_offset - 1) != System_Collections_IEnumerator)
        {
          p_offset += 4;
          if (!--v47)
            goto LABEL_76;
        }
        v49 = &klass->vtable[*p_offset];
      }
      else
      {
LABEL_76:
        v49 = sub_4227F4(Enumerator, System_Collections_IEnumerator, 0);
      }
      if (((*v49)(v45, *(u64 *)(v49 + 8)) & 1) == 0)
      {
        Interface = QueryInterface(Enumerator, System_IDisposable);
        v70 = Interface;
        if (!Interface)
          return;
        v62 = *Interface;
        v63 = Interface;
        v64 = *(u16 *)(*Interface + 302);
        if (*(u16 *)(*Interface + 302))
        {
          v65 = (*(u64 *)(v62 + 176) + 8);
          while (*((System_IDisposable_c **)v65 - 1) != System_IDisposable)
          {
            v65 += 4;
            if (!--v64)
              goto LABEL_98;
          }
          v66 = v62 + 16 * *v65 + 312;
        }
        else
        {
LABEL_98:
          v66 = sub_4227F4(Interface, System_IDisposable, 0);
        }
        (*v66)(v63, *(u64 *)(v66 + 8));
        return;
      }
      v50 = Enumerator;
      v51 = Enumerator->klass;
      v52 = *(u16 *)&Enumerator->klass->_2.rank;
      if (*(u16 *)&Enumerator->klass->_2.rank)
      {
        v53 = &v51->_1.interfaceOffsets->offset;
        while (*(v53 - 1) != System_Collections_IEnumerator)
        {
          v53 += 2;
          if (!--v52)
            goto LABEL_83;
        }
        v54 = &v51->vtable[*(u32 *)v53 + 1];
      }
      else
      {
LABEL_83:
        v54 = sub_4227F4(Enumerator, System_Collections_IEnumerator, 1u);
      }
      v55 = (*v54)(v50, *(u64 *)(v54 + 8));
      v56.value = Project_RSkillCsrType_var;
      v57 = GetTypeFromHandle(v56, 0);
      v58 = ToObject(v57, v55, 0);
      if (!v58)
        break;
      v59 = *(u32 *)Unbox(v58);
      object___set_Item(g_mainPID, v59, v37);
    }
    v58 = ((s64 (*)(void))loc_3BDC60)();
  }
  Work = cmpGetWork();
  v4 = Allocate(RskillCsr);
  *(u64 *)&v4->csrNo = 0;
  v4->listDrwNo = 0;
  v5 = Allocate(System_Collections_Generic_Dictionary_RSkillCsrType__RskillCsr_);
  object____ctor(v5);
  g_mainPID = (dds3ProcessID_t *)v5;
  v8.value = Project_RSkillCsrType_var;
  v9 = GetTypeFromHandle(v8, 0);
  v10 = GetValues(v9, 0);
  Enumerator = GetEnumerator(v10, 0);
  v67 = 0;
  p_Enumerator = &Enumerator;
  v11 = Enumerator;
  v69 = &v70;
  while (1)
  {
    v13 = v11->klass;
    v14 = *(u16 *)&v11->klass->_2.rank;
    if (*(u16 *)&v11->klass->_2.rank)
    {
      v15 = &v13->_1.interfaceOffsets->offset;
      while (*((System_Collections_IEnumerator_c **)v15 - 1) != System_Collections_IEnumerator)
      {
        v15 += 4;
        if (!--v14)
          goto LABEL_24;
      }
      v16 = &v13->vtable[*v15];
    }
    else
    {
LABEL_24:
      v16 = sub_4227F4(v11, System_Collections_IEnumerator, 0);
    }
    if (((*v16)(v11, *(u64 *)(v16 + 8)) & 1) == 0)
      break;
    v17 = Enumerator;
    v18 = Enumerator->klass;
    v19 = *(u16 *)&Enumerator->klass->_2.rank;
    if (*(u16 *)&Enumerator->klass->_2.rank)
    {
      v20 = &v18->_1.interfaceOffsets->offset;
      while (*(v20 - 1) != System_Collections_IEnumerator)
      {
        v20 += 2;
        if (!--v19)
          goto LABEL_31;
      }
      v21 = &v18->vtable[*(u32 *)v20 + 1];
    }
    else
    {
LABEL_31:
      v21 = sub_4227F4(Enumerator, System_Collections_IEnumerator, 1u);
    }
    v22 = (*v21)(v17, *(u64 *)(v21 + 8));
    v23.value = Project_RSkillCsrType_var;
    v24 = GetTypeFromHandle(v23, 0);
    v25 = ToObject(v24, v22, 0);
    if (!v25)
    {
      v25 = ((s64 (*)(void))loc_3BDC60)();
    }
    v26 = *(u32 *)Unbox(v25);
    rSkillCsrSave = Work->rSkillCsrSave;
    if (object___ContainsKey(rSkillCsrSave->skillCsrSave, v26) && object___get_Item(rSkillCsrSave->skillCsrSave, v26))
    {
      v28 = Work->rSkillCsrSave;
      if (object___ContainsKey(v28->skillCsrSave, v26))
      {
        Item = object___get_Item(v28->skillCsrSave, v26);
      }
      else
      {
        Item = 0;
      }
      object___set_Item(g_mainPID, v26, Item);
      goto LABEL_19;
    }
    object___set_Item(g_mainPID, v26, v4);
LABEL_19:
    v11 = Enumerator;
  }
  v31 = QueryInterface(Enumerator, System_IDisposable);
  v70 = v31;
  if (v31)
  {
    v32 = *v31;
    v33 = v31;
    v34 = *(u16 *)(*v31 + 302);
    if (*(u16 *)(*v31 + 302))
    {
      v35 = (*(u64 *)(v32 + 176) + 8);
      while (*((System_IDisposable_c **)v35 - 1) != System_IDisposable)
      {
        v35 += 4;
        if (!--v34)
          goto LABEL_60;
      }
      v36 = v32 + 16 * *v35 + 312;
    }
    else
    {
LABEL_60:
      v36 = sub_4227F4(v31, System_IDisposable, 0);
    }
    (*v36)(v33, *(u64 *)(v36 + 8));
  }
}

// 0x1e144c0
void RSpecialSkillSaveRSkillCsr(void) {
  RaidouSKillCsrSave *rSkillCsrSave;
  RskillCsr *v4;
  Il2CppObject *Item;
  bool v7;
  void *skillCsrSave;
  Il2CppObject *v9;
  bool v10;
  void *v11;
  Il2CppObject *v12;
  bool v13;
  void *v14;
  Il2CppObject *v15;
  bool v16;
  void *v17;
  Il2CppObject *v18;
  bool v19;
  void *v20;
  Il2CppObject *v21;
  bool v22;
  void *v23;
  Il2CppObject *v24;
  bool v25;
  void *v26;
  Il2CppObject *v27;
  bool v28;
  void *v29;

  dds3GetProcessData(m_before_skl);
  if (!cmpProcessCheck())
    return;
  rSkillCsrSave = cmpGetWork()->rSkillCsrSave;
  v4 = Allocate(RskillCsr);
  *(u64 *)&v4->csrNo = 0;
  v4->listDrwNo = 0;
  RSpecialSkillSelectRememberCsr();
  Item = object___get_Item(g_mainPID, 4);
  v7 = object___ContainsKey(rSkillCsrSave->skillCsrSave, 4);
  skillCsrSave = rSkillCsrSave->skillCsrSave;
  if (v7)
    object___set_Item(skillCsrSave, 4, Item);
  else
    object___Add(skillCsrSave, 4, Item);
  v9 = object___get_Item(g_mainPID, 5);
  v10 = object___ContainsKey(rSkillCsrSave->skillCsrSave, 5);
  v11 = rSkillCsrSave->skillCsrSave;
  if (v10)
    object___set_Item(v11, 5, v9);
  else
    object___Add(v11, 5, v9);
  v12 = object___get_Item(g_mainPID, 6);
  v13 = object___ContainsKey(rSkillCsrSave->skillCsrSave, 6);
  v14 = rSkillCsrSave->skillCsrSave;
  if (v13)
    object___set_Item(v14, 6, v12);
  else
    object___Add(v14, 6, v12);
  v15 = object___get_Item(g_mainPID, 7);
  v16 = object___ContainsKey(rSkillCsrSave->skillCsrSave, 7);
  v17 = rSkillCsrSave->skillCsrSave;
  if (v16)
    object___set_Item(v17, 7, v15);
  else
    object___Add(v17, 7, v15);
  v18 = object___get_Item(g_mainPID, 0);
  v19 = object___ContainsKey(rSkillCsrSave->skillCsrSave, 0);
  v20 = rSkillCsrSave->skillCsrSave;
  if (v19)
    object___set_Item(v20, 0, v18);
  else
    object___Add(v20, 0, v18);
  v21 = object___get_Item(g_mainPID, 1);
  v22 = object___ContainsKey(rSkillCsrSave->skillCsrSave, 1);
  v23 = rSkillCsrSave->skillCsrSave;
  if (v22)
    object___set_Item(v23, 1, v21);
  else
    object___Add(v23, 1, v21);
  v24 = object___get_Item(g_mainPID, 2);
  v25 = object___ContainsKey(rSkillCsrSave->skillCsrSave, 2);
  v26 = rSkillCsrSave->skillCsrSave;
  if (v25)
    object___set_Item(v26, 2, v24);
  else
    object___Add(v26, 2, v24);
  v27 = object___get_Item(g_mainPID, 3);
  v28 = object___ContainsKey(rSkillCsrSave->skillCsrSave, 3);
  v29 = rSkillCsrSave->skillCsrSave;
  if (v28)
    object___set_Item(v29, 3, v27);
  else
    object___Add(v29, 3, v27);
}

// 0x1e1dae0
void RSpecialSkillGetRskillCsrData(RSkillCsrType saveType) {
  Il2CppObject *ProcessData;
  Il2CppObject *v6;
  s64 v9;
  s64 v10;
  char *klass;
  s64 v13;
  s64 v14;
  s64 *v15;
  u32 *data;
  u32 *v18;
  char *monitor;
  s64 v21;
  s64 v22;
  s64 v23;

  ProcessData = dds3GetProcessData(m_before_skl);
  v6 = ProcessData;
  switch (saveType)
  {
    case 0:
    case 2:
      v9 = *(u64 *)&v6[3].klass->_1.byval_arg.bits;
      *(u32 *)(v9 + 16) = object___get_Item(g_mainPID, saveType)[1].klass;
      v10 = *(u64 *)&v6[3].klass->_1.byval_arg.bits;
      *(u32 *)(v10 + 20) = HIDWORD(object___get_Item(g_mainPID, saveType)[1].klass);
      klass = v6[3].klass;
      goto LABEL_17;
    case 1:
    case 3:
      v13 = *((u64 *)v6[3].monitor + 5);
      *(u32 *)(v13 + 16) = object___get_Item(g_mainPID, saveType)[1].klass;
      v14 = *((u64 *)v6[3].monitor + 5);
      *(u32 *)(v14 + 20) = HIDWORD(object___get_Item(g_mainPID, saveType)[1].klass);
      klass = v6[3].monitor;
LABEL_17:
      v15 = (klass + 40);
      goto LABEL_25;
    case 4:
    case 6:
      data = v6[3].klass->_1.byval_arg.data;
      data[4] = object___get_Item(g_mainPID, saveType)[1].klass;
      v18 = v6[3].klass->_1.byval_arg.data;
      v18[5] = HIDWORD(object___get_Item(g_mainPID, saveType)[1].klass);
      monitor = v6[3].klass;
      goto LABEL_24;
    case 5:
    case 7:
      v21 = *((u64 *)v6[3].monitor + 4);
      *(u32 *)(v21 + 16) = object___get_Item(g_mainPID, saveType)[1].klass;
      v22 = *((u64 *)v6[3].monitor + 4);
      *(u32 *)(v22 + 20) = HIDWORD(object___get_Item(g_mainPID, saveType)[1].klass);
      monitor = v6[3].monitor;
LABEL_24:
      v15 = (monitor + 32);
LABEL_25:
      v23 = *v15;
      *(u32 *)(v23 + 24) = object___get_Item(g_mainPID, saveType)[1].monitor;
      break;
    default:
      return;
  }
}

// 0x1e1ddf0
void RSpecialSkillRememberRskillCsr(RSkillCsrType saveType) {
  Il2CppObject *ProcessData;
  Il2CppObject *v6;
  RskillCsr *v8;
  u64 *p_image;
  s64 v11;
  u64 *monitor;
  s64 v13;
  bool v14;

  ProcessData = dds3GetProcessData(m_before_skl);
  v6 = ProcessData;
  v8 = Allocate(RskillCsr);
  *(u64 *)&v8->csrNo = 0;
  v8->listDrwNo = 0;
  switch (saveType)
  {
    case 0:
    case 2:
      p_image = &v6[3].klass->_1.image;
      goto LABEL_13;
    case 1:
    case 3:
      p_image = v6[3].monitor;
LABEL_13:
      v11 = p_image[5];
      *(u64 *)&v8->csrNo = *(u64 *)(v11 + 16);
      v8->listDrwNo = *(u32 *)(v11 + 24);
      goto LABEL_19;
    case 4:
    case 6:
      monitor = &v6[3].klass->_1.image;
      goto LABEL_17;
    case 5:
    case 7:
      monitor = v6[3].monitor;
LABEL_17:
      v13 = monitor[4];
      *(u64 *)&v8->csrNo = *(u64 *)(v13 + 16);
      v8->listDrwNo = *(u32 *)(v13 + 24);
LABEL_19:
      v14 = object___ContainsKey(g_mainPID, saveType);
      if (v14)
      {
        object___set_Item(g_mainPID, saveType, v8);
      }
      else
      {
        object___Add(g_mainPID, saveType, v8);
      }
      break;
    default:
      return;
  }
}

// 0x1e17420
void RSpecialSkillGetCsrData(void) {
  Il2CppObject *ProcessData;
  s32 monitor_high;
  bool v8;
  s32 v11;
  s32 v12;
  s32 v13;
  s32 v15;
  s32 State;

  ProcessData = dds3GetProcessData(m_before_skl);
  if (!ProcessData)
    goto LABEL_11;
  goto LABEL_9;
  if (!ProcessData)
LABEL_9:
LABEL_11:
  monitor_high = HIDWORD(ProcessData[1].monitor);
  if (!monitor_high)
  {
    State = GetState();
    if (State == 1)
      v12 = 4;
    else
      v12 = 6;
    if (State == 1)
      v13 = 5;
    else
      v13 = 7;
    goto LABEL_21;
  }
  v8 = GetState() == 1;
  v11 = !v8;
  v12 = 2 * v11;
  if (v8)
    v13 = 1;
  else
    v13 = 3;
LABEL_21:
  RSpecialSkillGetRskillCsrData(v12);
  v15 = v13;
  RSpecialSkillGetRskillCsrData(v15);
}

// 0x1e1b190
void RSpecialSkillSelectGetCsrData(void) {
  Il2CppObject *ProcessData;
  Il2CppObject *v4;
  s32 monitor_high;
  s32 State;
  s32 monitor;
  u32 v13;
  s32 v14;
  s32 v15;
  s32 v16;
  u32 v17;
  s32 v18;

  ProcessData = dds3GetProcessData(m_before_skl);
  v4 = ProcessData;
  monitor_high = HIDWORD(ProcessData[1].monitor);
  if (monitor_high)
  {
    State = GetState();
    monitor = v4[1].monitor;
    if (State == 1)
    {
      v14 = monitor != 0;
      if (!v13)
      {
LABEL_34:
        v18 = v14;
        goto LABEL_29;
      }
    }
    else
    {
      if (monitor)
        v14 = 3;
      else
        v14 = 2;
      if (!v13)
        goto LABEL_34;
    }
  }
  else
  {
    v15 = GetState();
    v16 = v4[1].monitor;
    if (v15 == 1)
    {
      if (v16)
        v14 = 5;
      else
        v14 = 4;
      if (!v17)
        goto LABEL_34;
    }
    else
    {
      if (v16)
        v14 = 7;
      else
        v14 = 6;
      if (!v17)
        goto LABEL_34;
    }
  }
  v18 = v14;
LABEL_29:
  RSpecialSkillGetRskillCsrData(v18);
}

// 0x1e15d40
void RSpecialSkillSelectRememberCsr(void) {
  Il2CppObject *ProcessData;
  Il2CppObject *v4;
  s32 monitor_high;
  s32 State;
  s32 monitor;
  u32 v13;
  s32 v14;
  s32 v15;
  s32 v16;
  u32 v17;
  s32 v18;

  ProcessData = dds3GetProcessData(m_before_skl);
  v4 = ProcessData;
  monitor_high = HIDWORD(ProcessData[1].monitor);
  if (monitor_high)
  {
    State = GetState();
    monitor = v4[1].monitor;
    if (State == 1)
    {
      v14 = monitor != 0;
      if (!v13)
      {
LABEL_34:
        v18 = v14;
        goto LABEL_29;
      }
    }
    else
    {
      if (monitor)
        v14 = 3;
      else
        v14 = 2;
      if (!v13)
        goto LABEL_34;
    }
  }
  else
  {
    v15 = GetState();
    v16 = v4[1].monitor;
    if (v15 == 1)
    {
      if (v16)
        v14 = 5;
      else
        v14 = 4;
      if (!v17)
        goto LABEL_34;
    }
    else
    {
      if (v16)
        v14 = 7;
      else
        v14 = 6;
      if (!v17)
        goto LABEL_34;
    }
  }
  v18 = v14;
LABEL_29:
  RSpecialSkillRememberRskillCsr(v18);
}

// 0x1e14b80
void RSpecialSkillSaveRSkillTab(void) {
  Il2CppObject *ProcessData;
  Il2CppObject *v4;

  ProcessData = dds3GetProcessData(m_before_skl);
  v4 = ProcessData;
  if (!cmpProcessCheck())
    return;
  cmpGetWork()->rSkillTabSave = HIDWORD(v4[1].monitor);
}

// 0x1e15ca0
RSkillTab RSpecialSkillLoadTab(void) {
  if (!cmpProcessCheck())
    return 0;
  return cmpGetWork()->rSkillTabSave;
}

// 0x1e14cf0
void RSpecialSkillSaveRSkillListSide(RSkillTab tab) {
  void *skillListSelectSave;
  s32 SelectListState;

  if (cmpProcessCheck())
  {
    skillListSelectSave = cmpGetWork()->skillListSelectSave;
  }
  else
  {
    skillListSelectSave = *((void *)*((MethodInfo *)RSpecialSkillStatus + 2).virtualMethodPointer + 6);
  }
  SelectListState = RSpecialSkillGetSelectListState();
  _set_Item(skillListSelectSave, tab, SelectListState);
}

// 0x1e13a10
void RSpecialSkillLosdListSide(RSkillTab tab) {
  tagCMP_WORK *Work;
  s32 Item;
  s32 v8;

  dds3GetProcessData(m_before_skl);
  if (cmpProcessCheck())
  {
    Work = cmpGetWork();
    Item = _get_Item(Work->skillListSelectSave, tab);
    v8 = Item;
    goto LABEL_11;
  }
  v8 = _get_Item(*(void *)&m_chaneg_csrNo, tab);
LABEL_11:
  RSpecialSkillSelectChange(v8);
}

// 0x1e16b80
void RSpecialSkillSetTab(RSkillTab tab) {
  Il2CppObject *ProcessData;

  ProcessData = dds3GetProcessData(m_before_skl);
  if (!ProcessData)
  HIDWORD(ProcessData[1].monitor) = tab;
}

// 0x1e1e070
RSkillTab RSpecialSkillGetTab(void) {
  s32 *ProcessData;

  if (!m_before_skl)
    return 0;
  if (dds3ExistProcess(m_before_skl))
  {
    goto LABEL_7;
  }
  return 0;
LABEL_7:
  ProcessData = dds3GetProcessData(m_before_skl);
  if (!ProcessData)
    return ProcessData[7];
  return ProcessData[7];
}

// 0x1e16ca0
LIST_SELECT RSpecialSkillGetSelectListState(void) {
  s32 *ProcessData;

  if (!m_before_skl)
    return 0;
  if (dds3ExistProcess(m_before_skl))
  {
    goto LABEL_7;
  }
  return 0;
LABEL_7:
  ProcessData = dds3GetProcessData(m_before_skl);
  if (!ProcessData)
    return ProcessData[6];
  return ProcessData[6];
}

// 0x1e15820
void RSpecialSkillCsrUpdate(void) {
  MethodInfo *ProcessData;
  tagSPECIAL_SKILL_STATUS_WORK *v4;
  s32 SelectListState;
  bool v9;
  bool v10;
  bool v11;
  bool v12;
  SpecialSkillCsr *v13;
  SpecialSkillCsr *v14;

  ProcessData = dds3GetProcessData(m_before_skl);
  v4 = ProcessData;
  SelectListState = RSpecialSkillGetSelectListState();
  if (SelectListState)
  {
    if (RSpecialSkillGetSelectListState() != 1)
      return;
    v9 = CHECK_TRIG(4100, 1);
    v10 = CHECK_REP(4100, 1);
    v11 = CHECK_TRIG(4101, 1);
    v12 = CHECK_REP(4101, 1);
    v13 = v4->skillCsr[v4->tab];
    (v13->klass->vtable._7_CsrUp.methodPtr)(v13, v9, v10, v13->klass->vtable._7_CsrUp.method);
    v14 = v4->skillCsr[v4->tab];
    (v14->klass->vtable._8_CsrDown.methodPtr)(v14, v11, v12, v14->klass->vtable._8_CsrDown.method);
  }
  else
  {
    SetSkillCsrUpdate(v4);
  }
}

// 0x1e15a60
void subCsrUpdate(void) {
  MethodInfo *ProcessData;
  tagSPECIAL_SKILL_STATUS_WORK *v4;
  s32 SelectListState;
  bool v9;
  bool v10;
  bool v11;
  bool v12;
  SpecialSkillCsr *v13;
  SpecialSkillCsr *v14;

  ProcessData = dds3GetProcessData(m_before_skl);
  v4 = ProcessData;
  SelectListState = RSpecialSkillGetSelectListState();
  if (SelectListState)
  {
    if (RSpecialSkillGetSelectListState() != 1)
      return;
    v9 = CHECK_TRIG(4100, 1);
    v10 = CHECK_REP(4100, 1);
    v11 = CHECK_TRIG(4101, 1);
    v12 = CHECK_REP(4101, 1);
    v13 = v4->skillCsr[v4->tab];
    (v13->klass->vtable._7_CsrUp.methodPtr)(v13, v9, v10, v13->klass->vtable._7_CsrUp.method);
    v14 = v4->skillCsr[v4->tab];
    (v14->klass->vtable._8_CsrDown.methodPtr)(v14, v11, v12, v14->klass->vtable._8_CsrDown.method);
  }
  else
  {
    SetSkillCsrUpdate(v4);
  }
}

// 0x1e16070
void RSpecialSkillInitChangeSource(void) {
  arrBattleSklID = -1;
  *(u64 *)&m_change_pos = -1;
  return;
}

// 0x1e1ae70
void RSpecialSkillGetChangeSource(void) {
  Il2CppObject *ProcessData;
  Il2CppObject *v4;
  s32 monitor_high;
  s32 v7;
  s64 v9;
  s32 monitor;
  int32x2_t *static_fields;
  u64 *p_monitor;
  s64 v15;

  ProcessData = dds3GetProcessData(m_before_skl);
  v4 = ProcessData;
  monitor_high = HIDWORD(ProcessData[1].monitor);
  if (monitor_high == 1)
  {
    monitor = ProcessData[1].monitor;
    if (monitor != 1)
    {
      if (monitor)
        return;
      v9 = 1;
      goto LABEL_25;
    }
    v9 = 1;
    static_fields[5].n64_u32[1] = 1;
LABEL_30:
    p_monitor = &v4[3].monitor;
    goto LABEL_31;
  }
  if (monitor_high)
    return;
  v7 = ProcessData[1].monitor;
  if (v7 == 1)
  {
    v9 = 0;
    static_fields[5].n64_u32[1] = 1;
    goto LABEL_30;
  }
  if (v7)
    return;
  v9 = 0;
LABEL_25:
  p_monitor = &v4[3].klass;
  static_fields[5].n64_u32[1] = 0;
LABEL_31:
  v15 = *(u64 *)(*p_monitor + 8 * v9 + 32);
  static_fields[4].n64_u64[0] = vrev64_s32(*(int32x2_t *)(v15 + 20)).n64_u64[0];
  static_fields[5].n64_u32[0] = *(u32 *)(v15 + 16);
}

// 0x1e1b830
void RSpecialSkillSetChangeSource(void) {
  Il2CppObject *ProcessData;
  Il2CppObject *v4;
  s32 monitor_high;
  s64 v10;
  u64 *p_image;
  s64 v13;

  ProcessData = dds3GetProcessData(m_before_skl);
  v4 = ProcessData;
  monitor_high = HIDWORD(ProcessData[1].monitor);
  if (!monitor_high)
  {
    if (m_change_listTop)
      goto LABEL_23;
    v10 = *((u64 *)&v4[3].klass->_1.byval_arg.data + SHIDWORD(v4[1].monitor));
    p_image = &v4[3].klass->_1.image;
    goto LABEL_33;
LABEL_31:
    v13 = v10;
    goto LABEL_34;
  }
  if (monitor_high != 1)
  {
    goto LABEL_28;
  }
  if (!m_change_listTop)
  {
    v10 = *((u64 *)&v4[3].klass->_1.byval_arg.data + SHIDWORD(v4[1].monitor));
    goto LABEL_31;
  }
LABEL_23:
  if (m_change_listTop == 1)
  {
    v10 = *((u64 *)v4[3].monitor + SHIDWORD(v4[1].monitor) + 4);
    p_image = v4[3].monitor;
LABEL_33:
    v13 = p_image[SHIDWORD(v4[1].monitor) + 4];
LABEL_34:
    *(u32 *)(v10 + 20) = HIDWORD(arrBattleSklID);
    *(u32 *)(v13 + 24) = arrBattleSklID;
    *(u32 *)(v13 + 16) = m_change_pos;
    goto LABEL_29;
  }
LABEL_28:
LABEL_29:
  arrBattleSklID = -1;
  *(u64 *)&m_change_pos = -1;
}

// 0x1e1e430
s32 RSpecialSkillGetOriginalPos(void) {
  return (s32)arrBattleSklID;
}

// 0x1e1e4b0
LIST_SELECT RSpecialSkillGetOriginalSide(void) {
  return m_change_listTop;
}

// 0x1e15420
void RSpecialSkillSelectStateChaneg(void) {
  Il2CppObject *ProcessData;
  Il2CppObject *v4;
  s32 monitor_high;
  bool v7;
  s64 v9;
  s32 v10;
  s32 v11;
  s32 v13;
  void *v15;
  s32 v17;
  void *Instance;

  ProcessData = dds3GetProcessData(m_before_skl);
  v4 = ProcessData;
  monitor_high = HIDWORD(ProcessData[1].monitor);
  v7 = CHECK_TRIG(4102, 1);
  if (monitor_high != 1)
  {
    if (v7)
    {
      if (!RSpecialSkillGetSelectListState())
        return;
      goto LABEL_36;
    }
    if (!CHECK_TRIG(4103, 1))
      return;
    if (RSpecialSkillGetSelectListState() == 1)
      return;
    if (GetState() != 2 && !HIDWORD(v4[1].monitor))
    {
      if (LOBYTE(skillListSelect))
        goto LABEL_59;
    }
    goto LABEL_62;
  }
  if (!v7 && !CHECK_REP(4102, 1))
  {
    if (!CHECK_TRIG(4103, 1) && !CHECK_REP(4103, 1))
      return;
    if (RSpecialSkillGetSelectListState())
      return;
    v9 = *((u64 *)&v4[3].klass->_1.byval_arg.data + SHIDWORD(v4[1].monitor));
    v13 = *(u32 *)(v9 + 16);
    if ((v13 & 1) == 0)
    {
      *(u32 *)(v9 + 16) = v13 + 1;
      v11 = *(u32 *)(v9 + 24) + 1;
      goto LABEL_27;
    }
    if (GetState() != 2 && HIDWORD(v4[1].monitor) == 1)
    {
      if (BYTE1(skillListSelect))
      {
LABEL_59:
        Instance = get_Instance(0);
        ItfSortMenuActive(Instance, 1, 0);
      }
    }
LABEL_62:
    v17 = 1;
    goto LABEL_41;
  }
  if (RSpecialSkillGetSelectListState() != 1)
    goto LABEL_25;
LABEL_36:
  v15 = get_Instance(0);
  ItfSortMenuActive(v15, 0, 0);
  v17 = 0;
LABEL_41:
  ListChange(v17, 0);
  return;
LABEL_25:
  v9 = *((u64 *)&v4[3].klass->_1.byval_arg.data + SHIDWORD(v4[1].monitor));
  v10 = *(u32 *)(v9 + 16);
  if ((v10 & 1) != 0)
  {
    *(u32 *)(v9 + 16) = v10 - 1;
    v11 = *(u32 *)(v9 + 24) - 1;
LABEL_27:
    *(u32 *)(v9 + 24) = v11;
    SE(3);
  }
}

// 0x1e1e530
static void ListChange(LIST_SELECT listSelect, bool isMouse) {
  SE(3);
  RSpecialSkillSelectRememberCsr();
  RSpecialSkillSelectChange(listSelect);
  if (isMouse)
    return;
  RSpecialSkillGetCsrData();
}

// 0x1e1b070
void RSpecialSkillSelectChange(LIST_SELECT celect) {
  Il2CppObject *ProcessData;

  ProcessData = dds3GetProcessData(m_before_skl);
  if (!ProcessData)
  LODWORD(ProcessData[1].monitor) = celect;
  RSpecialSkillButtonGuideDraw();
}

// 0x1e1e610
void RSpecialSkillSetSwordSkill(void) {
  Il2CppObject *ProcessData;
  tagSPECIAL_SKILL_STATUS_WORK *v5;

  ProcessData = dds3GetProcessData(m_before_skl);
  v5 = ProcessData;
  if (m_change_listTop == 1)
  {
    PossessionSideDecisionPattern(v5);
  }
  else if (!m_change_listTop)
  {
    SetSideDecisionPattern(v5);
  }
}

// 0x1e1bd20
void RSpecialSkillSetBattleSkill(void) {
  Il2CppObject *ProcessData;
  tagSPECIAL_SKILL_STATUS_WORK *v5;

  ProcessData = dds3GetProcessData(m_before_skl);
  v5 = ProcessData;
  if (m_change_listTop == 1)
  {
    BtlPossessionSideDecisionPattern(v5);
  }
  else if (!m_change_listTop)
  {
    BtlSetSideDecisionPattern(v5);
  }
}

// 0x1e1ba90
bool RSpecialSkillConfigurable(void) {
  s32 *ProcessData;
  s32 *v5;

  ProcessData = dds3GetProcessData(m_before_skl);
  v5 = ProcessData;
  if (!RSpecialSkillIsHaveSKill(ProcessData[7], ProcessData[6]))
    return 0;
  if (v5[6])
    goto LABEL_25;
  if (m_change_listTop)
    goto LABEL_25;
  if (m_change_pos == *(u32 *)(*(u64 *)(*((u64 *)v5 + 6) + 8 * v5[7] + 32) + 16))
    return 0;
LABEL_25:
  if (m_change_listTop == 1)
    return v5[6] != 1;
  return 1;
}

// 0x1e1b620
bool RSpecialSkillIsHaveSKill(RSkillTab tab, LIST_SELECT selectState) {
  Il2CppObject *ProcessData;
  Il2CppObject *v8;
  s32 v10;
  s32 v12;

  ProcessData = dds3GetProcessData(m_before_skl);
  v8 = ProcessData;
  if (!selectState)
    return 1;
  if (selectState == 1)
  {
    if (tab == 1)
    {
      v12 = *(u32 *)(*((u64 *)ProcessData[3].monitor + SHIDWORD(ProcessData[1].monitor) + 4) + 16);
      if (v12 == -1)
        return 0;
      v12 = *(u32 *)(*((u64 *)v8[3].monitor + SHIDWORD(v8[1].monitor) + 4) + 16);
      if (!_get_Item(*(void *)&SET_COLOR, v12))
        return 0;
    }
    else
    {
      if (tab)
        return 0;
      v10 = *(u32 *)(*((u64 *)ProcessData[3].monitor + SHIDWORD(ProcessData[1].monitor) + 4) + 16);
      if (v10 == -1)
        return 0;
      v10 = *(u32 *)(*((u64 *)v8[3].monitor + SHIDWORD(v8[1].monitor) + 4) + 16);
      if (!_get_Item(arrSwordSklID, v10))
        return 0;
    }
    return 1;
  }
  return 0;
}

// 0x1e1f260
static bool SameOriginal(tagSPECIAL_SKILL_STATUS_WORK *wk) {
  if (wk->select_state)
    return 0;
  if (m_change_listTop)
    return 0;
  return m_change_pos == wk->csr[wk->tab]->csrNo;
}

// 0x1e1f340
static bool SelectOtherSide(tagSPECIAL_SKILL_STATUS_WORK *wk) {
  if (m_change_listTop != 1)
    return 0;
  return wk->select_state == 1;
}

// 0x1e1ab30
void RSpecialSkillDrawHelpText(void) {
  Il2CppObject *ProcessData;
  Il2CppObject *v4;
  s32 monitor_high;
  void *v8;
  SpecialSkillCsr *NowPossSkilCsr;
  s32 Item;
  s32 v11;
  s32 v12;
  char *v14;
  SKLID *spiritSkill;

  ProcessData = dds3GetProcessData(m_before_skl);
  v4 = ProcessData;
  monitor_high = HIDWORD(ProcessData[1].monitor);
  if (monitor_high == 1)
  {
    if (LODWORD(ProcessData[1].monitor))
    {
      v8 = *((void *)*((const MethodInfo *)RSpecialSkillStatus + 2).virtualMethodPointer + 2);
LABEL_20:
      NowPossSkilCsr = RSpecialSkillGetNowPossSkilCsr();
      Item = _get_Item(v8, *(u32 *)(*((u64 *)v4[3].monitor + SHIDWORD(v4[1].monitor) + 4) + 20) + NowPossSkilCsr->listDrwNo);
      v11 = (u8)byte_5757DE5;
      if (Item)
      {
        v12 = Item;
LABEL_23:
        v14 = sdatSkillHelp(v12, 1);
        SKillHelpTextDraw(instance, v14, 1, 0xA09DC380, 0);
        return;
      }
      goto LABEL_34;
    }
    spiritSkill = GBWK->player->spiritSkill;
  }
  else
  {
    if (monitor_high)
      return;
    if (LODWORD(ProcessData[1].monitor))
    {
      v8 = *((void *)*((const MethodInfo *)RSpecialSkillStatus + 2).virtualMethodPointer + 3);
      goto LABEL_20;
    }
    spiritSkill = GBWK->player->raidouSkill;
  }
  v12 = spiritSkill[RSpecialSkillGetNowSkillCsr()->listDrwNo];
  v11 = (u8)byte_5757DE5;
  if (v12)
  {
    goto LABEL_23;
  }
LABEL_34:
  SKillHelpTextDraw(instance, "", 0, 0xA09DC380, 0);
}

// 0x1e13bc0
void RSpecialSkillButtonGuideDraw(void) {
  Il2CppObject *ProcessData;
  tagSPECIAL_SKILL_STATUS_WORK *v5;

  ProcessData = dds3GetProcessData(m_before_skl);
  v5 = ProcessData;
  if (LOBYTE(ProcessData[2].klass))
  {
    ButtonGuideGoh(v5);
  }
  else
  {
    ButtonGuideNormal(v5);
  }
}

// 0x1e1f6c0
static void ButtonGuideNormal(tagSPECIAL_SKILL_STATUS_WORK *wk) {
  bool v4;
  s32 v7;
  s32 select_state;
  char **v10;

  v4 = cmpProcessCheck();
  if (v4)
    goto LABEL_4;
  if (GetState() == 1)
  {
    select_state = wk->select_state;
    if (select_state == 1)
    {
      v10 = &"CMP02";
    }
    else
    {
      if (select_state)
        return;
      v10 = &"CMP56";
    }
    goto LABEL_43;
  }
  if (GetState() != 2)
    return;
  v10 = &"CMP03";
LABEL_43:
  ButtonGuideDispSet(*v10, 0, 90);
  return;
LABEL_4:
  if (GetState() == 1)
  {
    v7 = wk->select_state;
    if (v7 == 1)
    {
      cmpCmpGuideSet(1, 0, 90);
    }
    else if (!v7)
    {
      cmpCmpGuideSet(56, 0, 90);
    }
    return;
  }
  if (GetState() != 2)
    return;
  cmpCmpGuideSet(2, 0, 90);
}

// 0x1e1f400
static void ButtonGuideGoh(tagSPECIAL_SKILL_STATUS_WORK *wk) {
  bool v4;
  s32 v7;
  s32 select_state;
  char **v10;

  v4 = cmpProcessCheck();
  if (v4)
    goto LABEL_4;
  if (GetState() == 1)
  {
    select_state = wk->select_state;
    if (select_state == 1)
    {
      v10 = &"CMP60";
    }
    else
    {
      if (select_state)
        return;
      v10 = &"CMP57";
    }
    goto LABEL_43;
  }
  if (GetState() != 2)
    return;
  v10 = &"CMP03";
LABEL_43:
  ButtonGuideDispSet(*v10, 0, 90);
  return;
LABEL_4:
  if (GetState() == 1)
  {
    v7 = wk->select_state;
    if (v7 == 1)
    {
      cmpCmpGuideSet(60, 0, 90);
    }
    else if (!v7)
    {
      cmpCmpGuideSet(57, 0, 90);
    }
    return;
  }
  if (GetState() != 2)
    return;
  cmpCmpGuideSet(2, 0, 90);
}

// 0x1e16ef0
SpecialSkillCsr *RSpecialSkillGetNowSkillCsr(void) {
  Il2CppObject *ProcessData;

  ProcessData = dds3GetProcessData(m_before_skl);
  if (!ProcessData)
    return *((SpecialSkillCsr *)&ProcessData[3].klass->_1.byval_arg.data + SHIDWORD(ProcessData[1].monitor));
  return *((SpecialSkillCsr *)&ProcessData[3].klass->_1.byval_arg.data + SHIDWORD(ProcessData[1].monitor));
}

// 0x1e1e220
static void SetSkillCsrUpdate(tagSPECIAL_SKILL_STATUS_WORK *wk) {
  bool v3;
  bool v4;
  bool v5;
  bool v6;
  s64 tab;
  bool v9;
  SpecialSkillCsr *v11;
  SpecialSkillCsr *v12;

  v3 = CHECK_TRIG(4100, 1);
  v4 = CHECK_REP(4100, 1);
  v5 = CHECK_TRIG(4101, 1);
  v6 = CHECK_REP(4101, 1);
  tab = wk->tab;
  v9 = v6;
  if ((u32)tab == 1)
  {
    SwordCsrUp(wk, v3, v4);
    SwordCsrDown(wk, v5, v9);
  }
  else
  {
    v11 = wk->csr[tab];
    (v11->klass->vtable._7_CsrUp.methodPtr)(v11, v3, v4, v11->klass->vtable._7_CsrUp.method);
    v12 = wk->csr[wk->tab];
    (v12->klass->vtable._8_CsrDown.methodPtr)(v12, v5, v9, v12->klass->vtable._8_CsrDown.method);
  }
}

// 0x1e1ed00
static void BtlSetSideDecisionPattern(tagSPECIAL_SKILL_STATUS_WORK *wk) {
  SKLID *raidouSkill;
  char *v7;
  s32 Item;
  u32 *v9;
  s32 v10;
  SKLID *v11;
  SKLID *v12;
  s32 v14;
  s64 v20;
  char *v21;
  u32 v22;
  s32 *p_m_change_pos;

  if (m_change_listTop == wk->select_state)
  {
    raidouSkill = GBWK->player->raidouSkill;
    v7 = (char *)raidouSkill + 4 * wk->csr[wk->tab]->csrNo;
    v10 = *((u32 *)v7 + 8);
    v9 = v7 + 32;
    Item = v10;
    v11 = GBWK->player->raidouSkill;
    p_m_change_pos = &m_change_pos;
    *v9 = raidouSkill[m_change_pos];
    goto LABEL_39;
  }
  v12 = GBWK->player->raidouSkill;
  v14 = v12[m_change_pos];
  if (v14 == _get_Item(arrSwordSklID, wk->skillCsr[wk->tab]->csrNo))
  {
    v11 = GBWK->player->raidouSkill;
    Item = 0;
  }
  else
  {
    Item = _get_Item(arrSwordSklID, wk->skillCsr[wk->tab]->csrNo);
    v20 = 0;
    while (1)
    {
      v11 = GBWK->player->raidouSkill;
      if (v20 >= SLODWORD(v11->max_length))
        break;
      if (!v22)
      {
        v11 = GBWK->player->raidouSkill;
      }
      v21 = (char *)v11 + 4 * v20++;
      if (*((u32 *)v21 + 8) == Item)
      {
        v11 = GBWK->player->raidouSkill;
        *((u32 *)&v11->max_length + v20 + 1) = 0;
        goto LABEL_36;
      }
    }
    if (!v22)
    {
      v11 = GBWK->player->raidouSkill;
    }
LABEL_36:
  }
  p_m_change_pos = &m_change_pos;
LABEL_39:
  v11[*p_m_change_pos] = Item;
}

// 0x1e1e780
static void SetSideDecisionPattern(tagSPECIAL_SKILL_STATUS_WORK *wk) {
  SKLID *spiritSkill;
  char *v7;
  s32 Item;
  u32 *v9;
  s32 v10;
  SKLID *v11;
  SKLID *v12;
  s32 v14;
  s64 v20;
  char *v21;
  u32 v22;
  sdatPlayerUnitWork_t *player;
  s32 *p_m_change_pos;

  if (m_change_listTop == wk->select_state)
  {
    spiritSkill = GBWK->player->spiritSkill;
    v7 = (char *)spiritSkill + 4 * wk->csr[wk->tab]->csrNo;
    v10 = *((u32 *)v7 + 8);
    v9 = v7 + 32;
    Item = v10;
    v11 = GBWK->player->spiritSkill;
    p_m_change_pos = &m_change_pos;
    *v9 = spiritSkill[m_change_pos];
    goto LABEL_36;
  }
  v12 = GBWK->player->spiritSkill;
  v14 = v12[m_change_pos];
  if (v14 == _get_Item(*(void *)&SET_COLOR, wk->skillCsr[wk->tab]->csrNo))
  {
    v11 = GBWK->player->spiritSkill;
    Item = 0;
  }
  else
  {
    Item = _get_Item(*(void *)&SET_COLOR, wk->skillCsr[wk->tab]->csrNo);
    v20 = 0;
    do
    {
      player = GBWK->player;
      if (v20 >= player->spiritCnt)
      {
        if (!v22)
        {
          player = GBWK->player;
        }
        v11 = player->spiritSkill;
        goto LABEL_35;
      }
      if (!v22)
      {
        player = GBWK->player;
      }
      v11 = player->spiritSkill;
      v21 = (char *)v11 + 4 * v20++;
    }
    while (*((u32 *)v21 + 8) != Item);
    *((u32 *)&v11->max_length + v20 + 1) = 0;
  }
LABEL_35:
  p_m_change_pos = &m_change_pos;
LABEL_36:
  v11[*p_m_change_pos] = Item;
}

// 0x1e181b0
void RSpecialSkillSetListDisplayLeft(void) {
  Il2CppObject *ProcessData;
  Il2CppObject *v3;
  s32 monitor_high;
  s64 i;
  s32 v9;
  bool v10;
  sdatPlayerUnitWork_t *player;
  s32 v13;
  char *v15;
  s64 v17;
  s32 v18;
  void *v19;
  char *v20;
  s64 v22;
  s32 v23;
  s64 v25;
  s32 v28;
  char *v30;
  s32 coolTime;
  s32 v32;
  s64 v34;
  s32 v35;
  char *LocalizeText;
  s32 v38;
  s64 v40;
  s32 v41;

  ProcessData = dds3GetProcessData(m_before_skl);
  v3 = ProcessData;
  monitor_high = HIDWORD(ProcessData[1].monitor);
  if (!monitor_high)
  {
    v25 = 8;
    while (1)
    {
      v28 = *((u32 *)&GBWK->player->raidouSkill->obj.klass + v25);
      if (!v28)
      {
        LocalizeText = GetLocalizeText("CMP_STATUS_L0018", 1);
        v38 = v25 - 8;
        SetBtlListText(instance, v25 - 8, LocalizeText, -1, 0, 0);
        v40 = SHIDWORD(v3[1].monitor);
        v41 = *(u32 *)(*((u64 *)&v3[3].klass->_1.byval_arg.data + v40) + 24);
        UpdateSetSkillNameColor(v40, v41, v38);
        SetBtlSkillIcon(instance, v38, 0, 0);
        if (++v25 == 11)
          return;
        goto LABEL_9001;
      }
      v30 = sdatSkillName(v28);
      coolTime = tbldata[*((s32 *)&GBWK->player->raidouSkill->obj.klass + v25)]->coolTime;
      v32 = v25 - 8;
      SetBtlListText(instance, v25 - 8, v30, coolTime, 1, 0);
      v34 = SHIDWORD(v3[1].monitor);
      v35 = *(u32 *)(*((u64 *)&v3[3].klass->_1.byval_arg.data + v34) + 24);
      UpdateSetSkillNameColor(v34, v35, v32);
      SetBtlSkillIcon(instance, v32, 1, 0);
      if (++v25 == 11)
        return;
LABEL_9001:
    }
  }
  if (monitor_high == 1)
  {
    for (i = 0; i != 8; ++i)
    {
      player = GBWK->player;
      if (i >= player->spiritCnt)
        continue;
      v13 = player->spiritSkill[i];
      if (!v13)
      {
        v19 = instance;
        v20 = GetLocalizeText("CMP_STATUS_L0018", 1);
        SetSwordListText(v19, i, v20, 0);
        v22 = SHIDWORD(v3[1].monitor);
        v23 = *(u32 *)(*((u64 *)&v3[3].klass->_1.byval_arg.data + v22) + 24);
        UpdateSetSkillNameColor(v22, v23, i);
        v9 = i;
        v10 = 0;
        goto LABEL_13;
      }
      v15 = sdatSkillName(v13);
      SetSwordListText(instance, i, v15, 0);
      v17 = SHIDWORD(v3[1].monitor);
      v18 = *(u32 *)(*((u64 *)&v3[3].klass->_1.byval_arg.data + v17) + 24);
      UpdateSetSkillNameColor(v17, v18, i);
      v9 = i;
      v10 = 1;
LABEL_13:
      SetSwordSkillIcon(instance, v9, v10, 0);
    }
  }
}

// 0x1e1f980
static void UpdateSetSkillNameColor(RSkillTab tab, s32 csrNo, s32 dispNo) {
  void *v13;
  sdfColor32_t v14;
  sdfColor32_t rgba;

  if (tab == 1)
  {
    if (!m_change_listTop)
    {
      if (m_change_pos == dispNo)
        goto LABEL_43;
    }
    if (csrNo != dispNo)
    {
      rgba = (sdfColor32_t)NORMAL_COLOR.rgba;
      goto LABEL_61;
    }
LABEL_43:
    if (GBWK->player->spiritSkill[dispNo])
    {
      rgba = (sdfColor32_t)(u32)SELECT_COLOR.rgba;
    }
    else
    {
      rgba = (sdfColor32_t)*(u32 *)&NORMAL_COLOR.r;
    }
LABEL_61:
    SetSwordListTextColor(instance, dispNo, rgba, 0);
    return;
  }
  if (!tab)
  {
    if (!m_change_listTop)
    {
      if (m_change_pos == dispNo)
        goto LABEL_22;
    }
    if (csrNo != dispNo)
    {
      v13 = instance;
      v14 = (sdfColor32_t)NORMAL_COLOR.rgba;
      goto LABEL_40;
    }
LABEL_22:
    if (GBWK->player->raidouSkill[dispNo])
    {
      v13 = instance;
      v14 = (sdfColor32_t)(u32)SELECT_COLOR.rgba;
    }
    else
    {
      v13 = instance;
      v14 = (sdfColor32_t)*(u32 *)&NORMAL_COLOR.r;
    }
LABEL_40:
    SetBtlListTextColor(v13, dispNo, v14, 0);
  }
}

// 0x1e196b0
void RSpecialSkillSkillCsrColorReset(void) {
  Il2CppObject *ProcessData;
  Il2CppObject *v4;
  s32 monitor_high;
  void *v11;
  void *v13;
  void *v15;
  void *v17;
  void *v19;
  void *v21;
  void *v23;
  s32 v25;
  u64 v26;
  u32 *p_SELECT_COLOR;
  void *v32;
  void *v35;
  void *v37;
  void *v39;
  s64 v40;
  void *v45;
  u32 *p_r;

  ProcessData = dds3GetProcessData(m_before_skl);
  v4 = ProcessData;
  if (GetState() == 1)
  {
    if (LODWORD(v4[1].monitor) == 1)
    {
      monitor_high = HIDWORD(v4[1].monitor);
      if (monitor_high)
      {
        if (monitor_high == 1)
        {
          SetSwordListTextColor(instance, 0, (sdfColor32_t)NORMAL_COLOR.rgba, 0);
          v11 = instance;
          SetSwordListTextColor(v11, 1, (sdfColor32_t)NORMAL_COLOR.rgba, 0);
          v13 = instance;
          SetSwordListTextColor(v13, 2, (sdfColor32_t)NORMAL_COLOR.rgba, 0);
          v15 = instance;
          SetSwordListTextColor(v15, 3, (sdfColor32_t)NORMAL_COLOR.rgba, 0);
          v17 = instance;
          SetSwordListTextColor(v17, 4, (sdfColor32_t)NORMAL_COLOR.rgba, 0);
          v19 = instance;
          SetSwordListTextColor(v19, 5, (sdfColor32_t)NORMAL_COLOR.rgba, 0);
          v21 = instance;
          SetSwordListTextColor(v21, 6, (sdfColor32_t)NORMAL_COLOR.rgba, 0);
          v23 = instance;
          SetSwordListTextColor(v23, 7, (sdfColor32_t)NORMAL_COLOR.rgba, 0);
        }
      }
      else
      {
        v35 = instance;
        SetBtlListTextColor(v35, 0, (sdfColor32_t)NORMAL_COLOR.rgba, 0);
        v37 = instance;
        SetBtlListTextColor(v37, 1, (sdfColor32_t)NORMAL_COLOR.rgba, 0);
        v39 = instance;
        SetBtlListTextColor(v39, 2, (sdfColor32_t)NORMAL_COLOR.rgba, 0);
      }
      return;
    }
  }
  if (GetState() != 2)
    return;
  if (LODWORD(v4[1].monitor) == 1)
  {
    v25 = HIDWORD(v4[1].monitor);
    if (v25)
    {
      if (v25 == 1)
      {
        v26 = 0;
        while (1)
        {
          if (m_change_listTop)
            goto LABEL_77;
          if (v26 != LODWORD(arrBattleSklID))
            goto LABEL_77;
          goto LABEL_9000;
          if (v26 != LODWORD(arrBattleSklID))
          {
LABEL_77:
            v32 = instance;
            goto LABEL_59;
          }
LABEL_9000:
          if (v26 > 5)
            goto LABEL_60;
          if (GBWK->player->spiritSkill[v26])
          {
            v32 = instance;
            p_SELECT_COLOR = &SELECT_COLOR;
          }
          else
          {
            if (GBWK->player->spiritSkill[v26])
              goto LABEL_60;
            v32 = instance;
            p_SELECT_COLOR = &NORMAL_COLOR.r;
          }
LABEL_59:
          SetSwordListTextColor(v32, v26, (sdfColor32_t)*p_SELECT_COLOR, 0);
LABEL_60:
          if (++v26 == 8)
            return;
        }
      }
      return;
    }
    v40 = 0;
    while (1)
    {
      if (m_change_listTop)
        goto LABEL_117;
      if (v40 != LODWORD(arrBattleSklID))
        goto LABEL_117;
      goto LABEL_9001;
      if (v40 != LODWORD(arrBattleSklID))
      {
LABEL_117:
        v45 = instance;
        goto LABEL_120;
      }
LABEL_9001:
      if (GBWK->player->raidouSkill[v40])
        break;
      if (GBWK->player->raidouSkill[v40])
        goto LABEL_121;
      v45 = instance;
      p_r = &NORMAL_COLOR.r;
LABEL_120:
      SetBtlListTextColor(v45, v40, (sdfColor32_t)*p_r, 0);
LABEL_121:
      if (++v40 == 3)
        return;
    }
    v45 = instance;
    p_r = &SELECT_COLOR;
    goto LABEL_120;
  }
}

// 0x1e1fd50
void RSpecialSkillSwordListAutoArrange(void) {
  s64 v2;
  sdatPlayerUnitWork_t *player;

  v2 = 0;
  while (1)
  {
    player = GBWK->player;
    if (v2 >= player->spiritCnt)
      break;
    if (!player->spiritSkill[v2])
    {
      if (!IsAutoArrange(v2))
        return;
    }
    ++v2;
  }
}

// 0x1e1fe60
static bool IsAutoArrange(s32 startIdx) {
  s32 v4;
  SKLID *spiritSkill;
  s32 v6;
  s32 v7;
  sdatPlayerUnitWork_t *player;
  s32 spiritCnt;
  s32 *m_Items;

  v4 = startIdx + 1;
  while (1)
  {
    v7 = v4;
    player = GBWK->player;
    spiritCnt = player->spiritCnt;
    if (v7 >= spiritCnt)
      break;
    player = GBWK->player;
    spiritSkill = player->spiritSkill;
    v4 = v7 + 1;
    v6 = spiritSkill[v7];
    if (v6)
    {
      spiritSkill = GBWK->player->spiritSkill;
      v6 = spiritSkill[v7];
      m_Items = spiritSkill;
      m_Items[startIdx] = v6;
      m_Items[v7] = 0;
      return v7 < spiritCnt;
    }
  }
  return v7 < spiritCnt;
}

// 0x1e1b360
void RSpecialSkillCancelSetting(void) {
  Il2CppObject *ProcessData;
  Il2CppObject *v4;
  s32 monitor_high;
  SKLID *spiritSkill;
  SKLID *v15;
  SpecialSkillCsr *NowSkillCsr;
  SKLID *raidouSkill;
  SKLID *v24;

  ProcessData = dds3GetProcessData(m_before_skl);
  v4 = ProcessData;
  if (!LODWORD(ProcessData[1].monitor))
  {
    if (GetState() != 1)
      return;
    monitor_high = HIDWORD(v4[1].monitor);
    if (monitor_high)
    {
      if (monitor_high != 1)
        return;
    }
    else
    {
      raidouSkill = GBWK->player->raidouSkill;
      if (raidouSkill[RSpecialSkillGetNowSkillCsr()->listDrwNo])
      {
        v24 = GBWK->player->raidouSkill;
        v24[RSpecialSkillGetNowSkillCsr()->listDrwNo] = 0;
        return;
      }
      if (HIDWORD(v4[1].monitor) != 1)
        return;
    }
    spiritSkill = GBWK->player->spiritSkill;
    if (spiritSkill[RSpecialSkillGetNowSkillCsr()->listDrwNo])
    {
      v15 = GBWK->player->spiritSkill;
      NowSkillCsr = RSpecialSkillGetNowSkillCsr();
      v15[NowSkillCsr->listDrwNo] = 0;
      RSpecialSkillSwordListAutoArrange();
    }
  }
}

// 0x1e1a030
void RSpecialSkillSKillCsrReset(void) {
  Il2CppObject *ProcessData;
  Il2CppObject *v4;
  s32 monitor_high;
  s32 v12;
  struct RSpecialSkillStatus *static_fields;
  s64 v18;
  sdatPlayerUnitWork_t *player;
  s32 v21;
  void *v24;
  s64 v25;
  char v26;
  sdatPlayerUnitWork_t *v28;
  s32 v30;
  void *v33;
  s32 v35;
  struct RSpecialSkillStatus *p_SELECT_COLOR;
  void *v40;
  s64 v41;
  SKLID *raidouSkill;
  s32 v44;
  void *v47;
  s64 v48;
  char v49;
  SKLID *v51;
  s32 v53;
  void *v56;

  ProcessData = dds3GetProcessData(m_before_skl);
  v4 = ProcessData;
  if (GetState() == 1)
  {
    if (!LODWORD(v4[1].monitor))
    {
      RSpecialSkillDrawScrollBar();
      RSpecialSkillSetListDisplayRight();
      InitSkillNameColor();
      return;
    }
  }
  if (GetState() != 2)
    return;
  if (!LODWORD(v4[1].monitor))
  {
    monitor_high = HIDWORD(v4[1].monitor);
    if (monitor_high)
    {
      if (monitor_high != 1)
        return;
      v12 = 0;
LABEL_30:
      if (RSpecialSkillGetSelectSourceCsrPos() == -1)
        goto LABEL_63;
      if (v12 != RSpecialSkillGetSelectSourceCsrPos())
        goto LABEL_63;
      if (m_change_listTop == 1)
      {
        SetListTextColor(instance, v12, (sdfColor32_t)*(u32 *)&NORMAL_COLOR.r, 0);
        v18 = 8;
        while (2)
        {
          player = GBWK->player;
          if (v18 - 8 >= player->spiritCnt)
            goto LABEL_29;
          v21 = *((u32 *)&player->spiritSkill->obj.klass + v18);
          if (v21)
          {
            if (v21 == _get_Item(*(void *)&SET_COLOR, *(u32 *)(*((u64 *)v4[3].monitor + SHIDWORD(v4[1].monitor) + 4) + 20) + v12))
            {
              v24 = instance;
              SetListTextColor(v24, v12, (sdfColor32_t)(u32)SELECT_COLOR.rgba, 0);
            }
          }
          ++v18;
          continue;
        }
      }
LABEL_63:
      v25 = 0;
      v26 = 0;
      while (1)
      {
        v28 = GBWK->player;
        if (v25 >= v28->spiritCnt)
        {
          if ((v26 & 1) == 0)
          {
            v33 = instance;
            goto LABEL_28;
          }
          v33 = instance;
          static_fields = &SELECT_COLOR;
LABEL_28:
          SetListTextColor(v33, v12, (sdfColor32_t)(u32)NORMAL_COLOR.rgba, 0);
LABEL_29:
          if (++v12 == 6)
            return;
          goto LABEL_30;
        }
        v30 = v28->spiritSkill[v25];
        if (v30 == _get_Item(*(void *)&SET_COLOR, *(u32 *)(*((u64 *)v4[3].monitor + SHIDWORD(v4[1].monitor) + 4) + 20) + v12))
        {
          v26 |= _get_Item(*(void *)&SET_COLOR, *(u32 *)(*((u64 *)v4[3].monitor + SHIDWORD(v4[1].monitor) + 4) + 20) + v12) != 0;
        }
        ++v25;
      }
    }
    v35 = 0;
LABEL_93:
    if (RSpecialSkillGetSelectSourceCsrPos() == -1)
      goto LABEL_126;
    if (v35 != RSpecialSkillGetSelectSourceCsrPos())
      goto LABEL_126;
    if (m_change_listTop == 1)
    {
      v40 = instance;
      SetListTextColor(v40, v35, (sdfColor32_t)*(u32 *)&NORMAL_COLOR.r, 0);
      v41 = 8;
      while (2)
      {
        raidouSkill = GBWK->player->raidouSkill;
        if (v41 - 8 >= SLODWORD(raidouSkill->max_length))
          goto LABEL_92;
        v44 = *((u32 *)&raidouSkill->obj.klass + v41);
        if (v44)
        {
          if (v44 == _get_Item(arrSwordSklID, *(u32 *)(*((u64 *)v4[3].monitor + SHIDWORD(v4[1].monitor) + 4) + 20) + v35))
          {
            v47 = instance;
            SetListTextColor(v47, v35, (sdfColor32_t)(u32)SELECT_COLOR.rgba, 0);
          }
        }
        ++v41;
        continue;
      }
    }
LABEL_126:
    v48 = 0;
    v49 = 0;
    while (1)
    {
      v51 = GBWK->player->raidouSkill;
      if (v48 >= SLODWORD(v51->max_length))
      {
        if ((v49 & 1) == 0)
        {
          v56 = instance;
          goto LABEL_91;
        }
        v56 = instance;
        p_SELECT_COLOR = &SELECT_COLOR;
LABEL_91:
        SetListTextColor(v56, v35, (sdfColor32_t)(u32)NORMAL_COLOR.rgba, 0);
LABEL_92:
        if (++v35 == 6)
          return;
        goto LABEL_93;
      }
      v53 = v51[v48];
      if (v53 == _get_Item(arrSwordSklID, *(u32 *)(*((u64 *)v4[3].monitor + SHIDWORD(v4[1].monitor) + 4) + 20) + v35))
      {
        v49 |= _get_Item(arrSwordSklID, *(u32 *)(*((u64 *)v4[3].monitor + SHIDWORD(v4[1].monitor) + 4) + 20) + v35) != 0;
      }
      ++v48;
    }
  }
}

// 0x1e17010
SpecialSkillCsr *RSpecialSkillGetNowPossSkilCsr(void) {
  Il2CppObject *ProcessData;

  ProcessData = dds3GetProcessData(m_before_skl);
  if (!ProcessData)
    return *((SpecialSkillCsr *)ProcessData[3].monitor + SHIDWORD(ProcessData[1].monitor) + 4);
  return *((SpecialSkillCsr *)ProcessData[3].monitor + SHIDWORD(ProcessData[1].monitor) + 4);
}

// 0x1e173b0
void RSpecialSkillInitListDisp(void) {
  RSpecialSkillSetListDisplayRight();
}

// 0x1e1e360
static void SkillCsrUpdate(tagSPECIAL_SKILL_STATUS_WORK *wk) {
  bool v3;
  bool v4;
  bool v5;
  bool v6;
  SpecialSkillCsr *v7;
  SpecialSkillCsr *v8;

  v3 = CHECK_TRIG(4100, 1);
  v4 = CHECK_REP(4100, 1);
  v5 = CHECK_TRIG(4101, 1);
  v6 = CHECK_REP(4101, 1);
  v7 = wk->skillCsr[wk->tab];
  (v7->klass->vtable._7_CsrUp.methodPtr)(v7, v3, v4, v7->klass->vtable._7_CsrUp.method);
  v8 = wk->skillCsr[wk->tab];
  (v8->klass->vtable._8_CsrDown.methodPtr)(v8, v5, v6, v8->klass->vtable._8_CsrDown.method);
}

// 0x1e20620
bool RSpecialSkillDragCheck(void) {
  return (bool)m_csr_save_list;
}

// 0x1e204e0
s32 RSpecialSkillGetSelectSourceCsrPos(void) {
  Il2CppObject *ProcessData;

  ProcessData = dds3GetProcessData(m_before_skl);
  if (!ProcessData)
    goto LABEL_11;
  goto LABEL_9;
  if (!ProcessData)
LABEL_9:
LABEL_11:
  if ((u32)(HIDWORD(arrBattleSklID) - *(u32 *)(*((u64 *)ProcessData[3].monitor + SHIDWORD(ProcessData[1].monitor) + 4) + 20) + LODWORD(arrBattleSklID)) >= 6)
    return -1;
  else
    return HIDWORD(arrBattleSklID)
         - *(u32 *)(*((u64 *)ProcessData[3].monitor + SHIDWORD(ProcessData[1].monitor) + 4) + 20)
         + LODWORD(arrBattleSklID);
}

// 0x1e17260
void RSpecialSkillSetBarLength(void) {
  Il2CppObject *ProcessData;
  Il2CppObject *v4;
  s64 v6;

  ProcessData = dds3GetProcessData(m_before_skl);
  v4 = ProcessData;
  v6 = (s64)v4[3].monitor + 8 * SHIDWORD(v4[1].monitor);
  SetScrollBarLength(instance, *(u32 *)(*(u64 *)(v6 + 32) + 32), *(u32 *)(*(u64 *)(v6 + 32) + 28), 0);
}

// 0x1e19520
void RSpecialSkillDrawScrollBar(void) {
  Il2CppObject *ProcessData;
  Il2CppObject *v4;
  s32 *v6;

  ProcessData = dds3GetProcessData(m_before_skl);
  v4 = ProcessData;
  v6 = *((s32 **)v4[3].monitor + SHIDWORD(v4[1].monitor) + 4);
  DrawScrollBar(instance, v6[8], v6[7], v6[5], 0);
  SetActiveArrowLight(instance, 0);
}

// 0x1e1eac0
static void PossessionSideDecisionPattern(tagSPECIAL_SKILL_STATUS_WORK *wk) {
  s32 Item;
  s64 csrNo;
  SKLID *spiritSkill;
  s64 v8;
  SKLID *v9;
  char *v10;
  sdatPlayerUnitWork_t *player;
  SpecialSkillCsr *m_Items;

  Item = _get_Item(*(void *)&SET_COLOR, m_change_pos);
  csrNo = wk->csr[wk->tab]->csrNo;
  spiritSkill = GBWK->player->spiritSkill;
  if (spiritSkill[csrNo] == Item)
  {
    csrNo = wk->csr[wk->tab]->csrNo;
    spiritSkill = GBWK->player->spiritSkill;
    spiritSkill[csrNo] = 0;
  }
  else
  {
    v8 = 0;
    while (1)
    {
      player = GBWK->player;
      if (v8 >= player->spiritCnt)
        break;
      player = GBWK->player;
      v9 = player->spiritSkill;
      v10 = (char *)v9 + 4 * v8++;
      if (*((u32 *)v10 + 8) == Item)
      {
        v9 = GBWK->player->spiritSkill;
        m_Items = wk->csr;
        *((u32 *)&v9->max_length + v8 + 1) = v9[m_Items[wk->tab]->csrNo];
        v9[m_Items[wk->tab]->csrNo] = Item;
        return;
      }
    }
    player = GBWK->player;
    player->spiritSkill[wk->csr[wk->tab]->csrNo] = Item;
  }
}

// 0x1e1f020
static void BtlPossessionSideDecisionPattern(tagSPECIAL_SKILL_STATUS_WORK *wk) {
  s32 Item;
  s64 csrNo;
  SKLID *raidouSkill;
  s64 v8;
  char *v9;
  SKLID *v11;
  SpecialSkillCsr *m_Items;

  Item = _get_Item(arrSwordSklID, m_change_pos);
  csrNo = wk->csr[wk->tab]->csrNo;
  raidouSkill = GBWK->player->raidouSkill;
  if (raidouSkill[csrNo] == Item)
  {
    csrNo = wk->csr[wk->tab]->csrNo;
    raidouSkill = GBWK->player->raidouSkill;
    raidouSkill[csrNo] = 0;
  }
  else
  {
    v8 = 0;
    while (1)
    {
      v11 = GBWK->player->raidouSkill;
      if (v8 >= SLODWORD(v11->max_length))
        break;
      v11 = GBWK->player->raidouSkill;
      v9 = (char *)v11 + 4 * v8++;
      if (*((u32 *)v9 + 8) == Item)
      {
        v11 = GBWK->player->raidouSkill;
        m_Items = wk->csr;
        *((u32 *)&v11->max_length + v8 + 1) = v11[m_Items[wk->tab]->csrNo];
        v11[m_Items[wk->tab]->csrNo] = Item;
        return;
      }
    }
    v11 = GBWK->player->raidouSkill;
    v11[wk->csr[wk->tab]->csrNo] = Item;
  }
}

// 0x1e166f0
void RSpecialSkillGetHaveBattleSkill(void) {
  void *DrawRaidouSkill;
  void *Instance;
  void *v7;
  s32 i;
  s32 Item;
  s64 size;
  u64 *v13;
  s32 *items;
  void *v15;
  void *v16;
  void *v17;
  void *IndexList;
  void *v19;
  s32 v20;
  s32 v22;

  DrawRaidouSkill = cmpGetDrawRaidouSkill(0, raidouSkillList->max_length, 0);
  arrSwordSklID = DrawRaidouSkill;
  Instance = get_Instance(0);
  SortSetting(Instance, 6, 0);
  v7 = Allocate(System_Collections_Generic_List_int_);
  __ctor(v7);
  for (i = 0; ; ++i)
  {
    if (i >= arrSwordSklID->_size)
      break;
    if (!_get_Item(arrSwordSklID, i))
      continue;
    Item = _get_Item(arrSwordSklID, i);
    size = v7->_size;
    v13 = Method_System_Collections_Generic_List_int__Add__;
    ++v7->_version;
    items = v7->_items;
    if ((u32)size >= LODWORD(items->max_length))
    {
      _AddWithResize(v7, Item, *(const MethodInfo_2D8F530 **)(*(u64 *)(v13[4] + 192) + 112));
    }
    else
    {
      v7->_size = size + 1;
      items[size] = Item;
    }
  }
  v15 = get_Instance(0);
  ListSet_object_(v15, v7);
  v16 = get_Instance(0);
  ListSort(v16, 0);
  v17 = get_Instance(0);
  IndexList = GetIndexList(v17, 0);
  if (IndexList->_size >= 1)
  {
    v19 = IndexList;
    v20 = 0;
    do
    {
      v22 = _get_Item(v19, v20);
      _set_Item(arrSwordSklID, v20++, v22);
    }
    while (v20 < v19->_size);
  }
}

// 0x1e206a0
void RSpecialSkillGetHaveSwordSkill(void) {
  void *DrawSpiritSkill;
  void *Instance;
  void *v7;
  s32 i;
  s32 Item;
  s64 size;
  u64 *v13;
  s32 *items;
  void *v15;
  void *v16;
  void *v17;
  void *IndexList;
  void *v19;
  s32 v20;
  s32 v22;

  DrawSpiritSkill = cmpGetDrawSpiritSkill(0, spiritList->max_length, 0);
  SET_COLOR = (struct sdfColor32_t)DrawSpiritSkill;
  Instance = get_Instance(0);
  SortSetting(Instance, 7, 0);
  v7 = Allocate(System_Collections_Generic_List_int_);
  __ctor(v7);
  for (i = 0; ; ++i)
  {
    if (i >= *(u32 *)(*(u64 *)&SET_COLOR + 24))
      break;
    if (!_get_Item(*(void *)&SET_COLOR, i))
      continue;
    Item = _get_Item(*(void *)&SET_COLOR, i);
    size = v7->_size;
    v13 = Method_System_Collections_Generic_List_int__Add__;
    ++v7->_version;
    items = v7->_items;
    if ((u32)size >= LODWORD(items->max_length))
    {
      _AddWithResize(v7, Item, *(const MethodInfo_2D8F530 **)(*(u64 *)(v13[4] + 192) + 112));
    }
    else
    {
      v7->_size = size + 1;
      items[size] = Item;
    }
  }
  v15 = get_Instance(0);
  ListSet_object_(v15, v7);
  v16 = get_Instance(0);
  ListSort(v16, 0);
  v17 = get_Instance(0);
  IndexList = GetIndexList(v17, 0);
  if (IndexList->_size >= 1)
  {
    v19 = IndexList;
    v20 = 0;
    do
    {
      v22 = _get_Item(v19, v20);
      _set_Item(SET_COLOR, v20++, v22);
    }
    while (v20 < v19->_size);
  }
}

// 0x1e17130
s32 RSpecialSkillGetBattleSkillCount(void) {
  s32 v2;
  s32 v3;
  bool v4;

  if (!arrSwordSklID)
    return 0;
  v2 = 0;
  v3 = 0;
  while (1)
  {
    if (v2 >= arrSwordSklID->_size)
      break;
    v4 = _get_Item(arrSwordSklID, v2) == 0;
    ++v2;
    if (!v4)
      ++v3;
  }
  if (v3 <= 6)
    return 6;
  else
    return v3;
}

// 0x1e20a30
s32 RSpecialSkillGetSwordSkillCount(void) {
  s32 v2;
  s32 v3;
  bool v4;

  if (!SET_COLOR)
    return 0;
  v2 = 0;
  v3 = 0;
  while (1)
  {
    if (v2 >= SET_COLOR->_size)
      break;
    v4 = _get_Item(SET_COLOR, v2) == 0;
    ++v2;
    if (!v4)
      ++v3;
  }
  if (v3 <= 6)
    return 6;
  else
    return v3;
}

// 0x1e188c0
void RSpecialSkillSetListDisplayRight(void) {
  Il2CppObject *ProcessData;
  Il2CppObject *v4;
  s32 monitor_high;
  s32 v7;
  s32 v8;
  s32 v9;
  void *v10;
  s32 v11;
  s32 v16;
  s32 Item;
  char *v18;
  s64 v19;
  s32 v20;
  s32 v21;
  void *v23;
  s32 v24;
  bool v27;
  s32 v29;
  s32 v30;
  char *v31;
  s32 coolTime;
  s64 v34;
  s32 v35;
  s32 v36;
  s32 v38;
  void *v39;
  s32 v40;
  void *v42;
  char *v43;
  void *v45;
  char *LocalizeText;
  void *v49;
  char *v50;
  void *v52;
  char *v53;
  void *v55;
  char *v56;
  void *v58;
  char *v59;
  void *v61;
  char *v62;
  s32 v63;

  ProcessData = dds3GetProcessData(m_before_skl);
  v4 = ProcessData;
  monitor_high = HIDWORD(ProcessData[1].monitor);
  if (monitor_high)
  {
    if (monitor_high != 1)
      goto LABEL_21;
    goto LABEL_18;
  }
  if (!arrSwordSklID)
    goto LABEL_89;
  monitor_high = HIDWORD(v4[1].monitor);
  if (monitor_high == 1)
  {
LABEL_18:
    if (SET_COLOR)
    {
      monitor_high = HIDWORD(v4[1].monitor);
      goto LABEL_21;
    }
LABEL_89:
    LocalizeText = GetLocalizeText("CMP_STATUS_L0018", 1);
    SetListText(instance, 0, LocalizeText, -1, 0, 0);
    SetSKillIcon(instance, 0, 0, 0);
    v49 = instance;
    v50 = GetLocalizeText("CMP_STATUS_L0018", 1);
    SetListText(v49, 1, v50, -1, 0, 0);
    SetSKillIcon(instance, 1, 0, 0);
    v52 = instance;
    v53 = GetLocalizeText("CMP_STATUS_L0018", 1);
    SetListText(v52, 2, v53, -1, 0, 0);
    SetSKillIcon(instance, 2, 0, 0);
    v55 = instance;
    v56 = GetLocalizeText("CMP_STATUS_L0018", 1);
    SetListText(v55, 3, v56, -1, 0, 0);
    SetSKillIcon(instance, 3, 0, 0);
    v58 = instance;
    v59 = GetLocalizeText("CMP_STATUS_L0018", 1);
    SetListText(v58, 4, v59, -1, 0, 0);
    SetSKillIcon(instance, 4, 0, 0);
    v61 = instance;
    v62 = GetLocalizeText("CMP_STATUS_L0018", 1);
    SetListText(v61, 5, v62, -1, 0, 0);
    SetSKillIcon(instance, 5, 0, 0);
    return;
  }
LABEL_21:
  v63 = *(u32 *)(*((u64 *)v4[3].monitor + monitor_high + 4) + 20);
  if (monitor_high)
  {
    if (monitor_high == 1)
    {
      v7 = 0;
      v8 = 0;
      while (1)
      {
        if (v7 >= SET_COLOR->_size)
          goto LABEL_73;
        if (_get_Item(SET_COLOR, v7) && v8 <= 5)
        {
          break;
        }
LABEL_25:
        ++v7;
      }
      v16 = v8 + v63;
      Item = _get_Item(*(void *)&SET_COLOR, v8 + v63);
      v18 = sdatSkillName(Item);
      SetListText(instance, v8, v18, -1, 0, 0);
      v19 = SHIDWORD(v4[1].monitor);
      v20 = *(u32 *)(*((u64 *)v4[3].monitor + v19 + 4) + 24);
      v21 = _get_Item(*(void *)&SET_COLOR, v16);
      UpdateSkillNameColor(v19, v20, v8, v21);
      SetSKillIcon(instance, v8, 1, 0);
      v9 = HIDWORD(v4[1].monitor);
      v10 = instance;
      v11 = _get_Item(*(void *)&SET_COLOR, v16);
      SetSkillSprite(v10, v9, v8++, v11, 0);
      goto LABEL_25;
    }
    v8 = 0;
    while (1)
    {
LABEL_78:
      v42 = instance;
      v43 = GetLocalizeText("CMP_STATUS_L0018", 1);
      SetListText(v42, v8, v43, -1, 0, 0);
      v45 = instance;
      SetListTextColor(v45, v8, (sdfColor32_t)NORMAL_COLOR.rgba, 0);
      SetSKillIcon(instance, v8++, 0, 0);
      if (v8 == 6)
        return;
    }
  }
  v8 = 0;
  while (1)
  {
    if (monitor_high >= arrSwordSklID->_size)
      break;
    if (_get_Item(arrSwordSklID, monitor_high))
    {
      v27 = v8 <= 5;
    }
    else
    {
      v27 = 0;
    }
    if (v27)
    {
      v29 = v8 + v63;
      v30 = _get_Item(arrSwordSklID, v8 + v63);
      v31 = sdatSkillName(v30);
      coolTime = tbldata[_get_Item(arrSwordSklID, v29)]->coolTime;
      SetListText(instance, v8, v31, coolTime, 1, 0);
      v34 = SHIDWORD(v4[1].monitor);
      v35 = *(u32 *)(*((u64 *)v4[3].monitor + v34 + 4) + 24);
      v36 = _get_Item(arrSwordSklID, v29);
      UpdateSkillNameColor(v34, v35, v8, v36);
      SetSKillIcon(instance, v8, 1, 0);
      v38 = HIDWORD(v4[1].monitor);
      v39 = instance;
      v40 = _get_Item(arrSwordSklID, v29);
      SetSkillSprite(v39, v38, v8, v40, 0);
      v23 = instance;
      v24 = _get_Item(arrSwordSklID, v29);
      SetUseButtonImage(v23, v24, v8++, 1, 0);
    }
    ++monitor_high;
  }
LABEL_73:
  if (v8 <= 5)
    goto LABEL_78;
}

// 0x1e20b60
static void UpdateSkillNameColor(RSkillTab tab, s32 csrNo, s32 dispNo, SKLID id) {
  s64 v9;
  char *v11;
  SKLID *raidouSkill;
  s64 v13;
  s32 v14;
  s64 v16;
  sdatPlayerUnitWork_t *player;
  s32 v18;
  u32 *p_SELECT_COLOR;

  if (tab != 1)
  {
    if (tab)
      goto LABEL_50;
    v9 = 0;
    while (1)
    {
      raidouSkill = GBWK->player->raidouSkill;
      if (v9 >= SLODWORD(raidouSkill->max_length))
        break;
      raidouSkill = GBWK->player->raidouSkill;
      v11 = (char *)raidouSkill + 4 * v9++;
      if (*((u32 *)v11 + 8) == id)
        tab = 1;
    }
    v18 = tab;
    if (RSpecialSkillGetSelectSourceCsrPos() == -1)
      goto LABEL_44;
    if (RSpecialSkillGetSelectSourceCsrPos() != dispNo)
      goto LABEL_44;
    goto LABEL_37;
  }
  v13 = 0;
  v14 = 0;
  while (1)
  {
    player = GBWK->player;
    if (v13 >= player->spiritCnt)
      break;
    player = GBWK->player;
    v16 = (s64)player->spiritSkill + 4 * v13++;
    if (*(u32 *)(v16 + 32) == id)
      v14 = 1;
  }
  v18 = v14 & 1;
  if (RSpecialSkillGetSelectSourceCsrPos() == -1)
    goto LABEL_44;
  if (RSpecialSkillGetSelectSourceCsrPos() != dispNo)
    goto LABEL_44;
LABEL_37:
  if (m_change_listTop != 1)
    goto LABEL_44;
  if (v18)
    goto LABEL_45;
  goto LABEL_51;
LABEL_44:
  if (v18)
  {
LABEL_45:
    p_SELECT_COLOR = &SELECT_COLOR;
    goto LABEL_61;
  }
LABEL_50:
  if (csrNo == dispNo)
  {
LABEL_51:
    p_SELECT_COLOR = &NORMAL_COLOR.r;
    goto LABEL_61;
  }
LABEL_61:
  SetListTextColor(instance, dispNo, (sdfColor32_t)*p_SELECT_COLOR, 0);
}

// 0x1e1ff70
static void InitSkillNameColor(void) {
  Il2CppObject *ProcessData;
  s64 monitor_high;
  s32 v6;
  s64 i;
  sdatPlayerUnitWork_t *player;
  s32 v12;
  void *v15;
  void *v17;
  s64 j;
  SKLID *raidouSkill;
  s32 v21;
  void *v24;
  s32 v25;

  ProcessData = dds3GetProcessData(m_before_skl);
  if (!ProcessData)
    goto LABEL_11;
  goto LABEL_9;
  if (!ProcessData)
LABEL_9:
LABEL_11:
  monitor_high = SHIDWORD(ProcessData[1].monitor);
  v25 = *(u32 *)(*((u64 *)ProcessData[3].monitor + monitor_high + 4) + 20);
  if ((u32)monitor_high)
  {
    if ((u32)monitor_high != 1)
      return;
    v6 = 0;
LABEL_15:
LABEL_17:
    SetListTextColor(instance, v6, (sdfColor32_t)NORMAL_COLOR.rgba, 0);
    for (i = 8; ; ++i)
    {
      player = GBWK->player;
      if (i - 8 >= player->spiritCnt)
      {
        if (++v6 == 6)
          return;
        goto LABEL_15;
      }
      v12 = *((u32 *)&player->spiritSkill->obj.klass + i);
      if (!v12)
        continue;
      if (v12 == _get_Item(*(void *)&SET_COLOR, v6 + v25))
      {
        v15 = instance;
        SetListTextColor(v15, v6, (sdfColor32_t)(u32)SELECT_COLOR.rgba, 0);
        continue;
      }
    }
    goto LABEL_17;
  }
  while (2)
  {
    v17 = instance;
    SetListTextColor(v17, monitor_high, (sdfColor32_t)NORMAL_COLOR.rgba, 0);
    for (j = 8; ; ++j)
    {
      raidouSkill = GBWK->player->raidouSkill;
      if (j - 8 >= SLODWORD(raidouSkill->max_length))
        break;
      v21 = *((u32 *)&raidouSkill->obj.klass + j);
      if (!v21)
        continue;
      if (v21 == _get_Item(arrSwordSklID, monitor_high + v25))
      {
        v24 = instance;
        SetListTextColor(v24, monitor_high, (sdfColor32_t)(u32)SELECT_COLOR.rgba, 0);
        continue;
      }
    }
    LODWORD(monitor_high) = monitor_high + 1;
    if ((u32)monitor_high != 6)
      continue;
    break;
  }
}

// 0x1e175e0
void RSpecialSkillSetInfo(void) {
  RSpecialSkillSetListDisplayRight();
  RSpecialSkillDrawScrollBar();
}

// 0x1e16a80
void RSpecialSkillIsBtlSkillSort(void) {
  s32 v1;
  s32 v2;

  v1 = 0;
  v2 = 0;
  while (1)
  {
    if (v1 >= arrSwordSklID->_size)
      break;
    if (_get_Item(arrSwordSklID, v1++))
    {
      ++v2;
    }
  }
  if (v2 >= 2)
  {
    LOBYTE(skillListSelect) = 1;
  }
}

// 0x1e20f10
void RSpecialSkillIsSwordSkillSort(void) {
  s32 v1;
  s32 v2;

  v1 = 0;
  v2 = 0;
  while (1)
  {
    if (v1 >= SET_COLOR->_size)
      break;
    if (_get_Item(SET_COLOR, v1++))
    {
      ++v2;
    }
  }
  if (v2 >= 2)
  {
    BYTE1(skillListSelect) = 1;
  }
}

// 0x1e21010
void RSpecialSkillSwordSkillSortFunc(void) {
  void *v1;
  s32 i;
  s32 Item;
  s64 size;
  u64 *v7;
  s32 *items;
  void *Instance;

  v1 = Allocate(System_Collections_Generic_List_int_);
  __ctor(v1);
  for (i = 0; ; ++i)
  {
    if (i >= *(u32 *)(*(u64 *)&SET_COLOR + 24))
      break;
    if (!_get_Item(*(void *)&SET_COLOR, i))
      continue;
    Item = _get_Item(*(void *)&SET_COLOR, i);
    size = v1->_size;
    v7 = Method_System_Collections_Generic_List_int__Add__;
    ++v1->_version;
    items = v1->_items;
    if ((u32)size >= LODWORD(items->max_length))
    {
      _AddWithResize(v1, Item, *(const MethodInfo_2D8F530 **)(*(u64 *)(v7[4] + 192) + 112));
    }
    else
    {
      v1->_size = size + 1;
      items[size] = Item;
    }
  }
  Instance = get_Instance(0);
  ListSet_object_(Instance, v1);
}

// 0x1e21210
void RSpecialSkillEndSwordSkillSortFunc(void) {
  void *v1;
  void *Instance;
  void *IndexList;
  void *v4;
  s32 v5;
  s32 Item;

  v1 = Allocate(System_Collections_Generic_List_int_);
  __ctor(v1);
  Instance = get_Instance(0);
  IndexList = GetIndexList(Instance, 0);
  if (IndexList->_size >= 1)
  {
    v4 = IndexList;
    v5 = 0;
    do
    {
      Item = _get_Item(v4, v5);
      _set_Item(SET_COLOR, v5++, Item);
    }
    while (v5 < v4->_size);
  }
  RSpecialSkillButtonGuideDraw();
}

// 0x1e21390
void RSpecialSkillBattleSkillSortFunc(void) {
  void *v1;
  s32 i;
  s32 Item;
  s64 size;
  u64 *v7;
  s32 *items;
  void *Instance;

  v1 = Allocate(System_Collections_Generic_List_int_);
  __ctor(v1);
  for (i = 0; ; ++i)
  {
    if (i >= arrSwordSklID->_size)
      break;
    if (!_get_Item(arrSwordSklID, i))
      continue;
    Item = _get_Item(arrSwordSklID, i);
    size = v1->_size;
    v7 = Method_System_Collections_Generic_List_int__Add__;
    ++v1->_version;
    items = v1->_items;
    if ((u32)size >= LODWORD(items->max_length))
    {
      _AddWithResize(v1, Item, *(const MethodInfo_2D8F530 **)(*(u64 *)(v7[4] + 192) + 112));
    }
    else
    {
      v1->_size = size + 1;
      items[size] = Item;
    }
  }
  Instance = get_Instance(0);
  ListSet_object_(Instance, v1);
}

// 0x1e21590
void RSpecialSkillEndBattleSkillSortFunc(void) {
  void *v1;
  void *Instance;
  void *IndexList;
  void *v4;
  s32 v5;
  s32 Item;

  v1 = Allocate(System_Collections_Generic_List_int_);
  __ctor(v1);
  Instance = get_Instance(0);
  IndexList = GetIndexList(Instance, 0);
  if (IndexList->_size >= 1)
  {
    v4 = IndexList;
    v5 = 0;
    do
    {
      Item = _get_Item(v4, v5);
      _set_Item(arrSwordSklID, v5++, Item);
    }
    while (v5 < v4->_size);
  }
  RSpecialSkillButtonGuideDraw();
}

// 0x1e16e50
void RSpecialSkillSetBeforeIdx(LIST_SELECT listSide) {
  s32 v3;

  if (listSide == 1)
  {
    listSide = 14;
    v3 = 14;
    v3 = listSide;
  }
  else
  {
    if (listSide)
      return;
    v3 = 0;
  }
  HIDWORD(skillListSelect) = v3;
}
