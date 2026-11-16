#include "types.h"
#include "SKLID.h"
#include "cmpitem.h"
#include "cmpmain.h"
#include "cmpstatus.h"
#include "dat.h"
#include "dds3kernelcore.h"
#include "dds3kerneldraw.h"
#include "fclmsg.h"
#include "rstgrowth.h"
#include "rstinit.h"
#include "sbtlsub.h"
#include "sdfsound.h"
#include "sndat3.h"

typedef struct _LvUpSkl _LvUpSkl;
typedef struct dds3ProcessID_t dds3ProcessID_t;
typedef struct sdatPlayerUnitWork_t sdatPlayerUnitWork_t;
typedef struct sdatUnitWork_t sdatUnitWork_t;
typedef struct tagRST_GROWTH_WORK tagRST_GROWTH_WORK;

char *rstAssetKey;
dds3ProcessID_t *g_mainPID;
sdatPlayerUnitWork_t *g_pSrc;
sdatPlayerUnitWork_t *g_pDst;
sdatUnitWork_t *g_pUnitSrc;
sdatUnitWork_t *g_pUnitDst;
s32 g_plyLevelUpNum;
s32 g_plyRankUpNum;
s32 *g_dvlLevelUpNum;
s8 *g_dvlCyuuseiMax;
SKLID *g_learnCombSkillID;
SKLID *g_learnAutoSkillID;
bool g_bEndFadeOut;
bool g_bEndBgmLoad;
s32 s_nowhp;
bool *s_bRegistMemSkill;
_LvUpSkl *g_aLvUpSkl;
s32 *s_arrLoyaltyBonusType;
s32 g_newSklCnt;
s32 rstGrowthSeqDevil_i;
s32 rstGrowthSeqDevil_j;

// 0x1dfb150
s32 rstGetNmlSklNum(_LvUpSkl *pLvUpSkl) {
  s32 *nmlSkl;
  s32 v3;
  s32 v4;
  s32 v5;
  _BOOL4 v6;
  s32 v7;

  nmlSkl = pLvUpSkl->nmlSkl;
  v3 = nmlSkl[0];
  v4 = nmlSkl[1];
  v5 = nmlSkl[2];
  v6 = v4 != 0;
  if (v3)
    v7 = v6 + 1;
  else
    v7 = v6;
  if (v5)
    return v7 + 1;
  else
    return v7;
}

// 0x1dfb180
s32 rstGetMemSklNum(_LvUpSkl *pLvUpSkl) {
  s32 *memSkl;
  s32 v3;
  s32 v4;

  memSkl = pLvUpSkl->memSkl;
  v3 = memSkl[0];
  v4 = memSkl[1] != 0;
  if (v3)
    return v4 + 1;
  else
    return v4;
}

// 0x1df9ad0
s32 rstChkGrowthNextDevil(s32 a_startStockNo) {
  s64 v2;

  LODWORD(v2) = a_startStockNo;
  if ((s32)v2 > 31)
    return 0;
  v2 = (s32)v2;
  while (1)
  {
    if (g_dvlLevelUpNum[v2])
      return 1;
    if (g_dvlCyuuseiMax[v2] > 0)
      break;
    if ((u32)++v2 == 32)
      return 0;
  }
  return 2;
}

// 0x1dfb1a0
void rstCallProcEnd(tagRST_GROWTH_WORK *wk) {
  ProcessEnd(0, 0);
  Delete(0);
  fclProcessEnd(wk->giftPID);
}

// 0x1dfa030
void rstRelease(tagRST_GROWTH_WORK *wk) {
  if (wk->scrPID)
  {
    dds3KillProcess(&wk->scrPID, 0);
    wk->scrPID = 0;
  }
  wk->pDatScr = 0;
}

// 0x1dfb220
dds3ProcessID_t *rstGetGiftMsgPID(void) {
  dds3ProcessID_t *ProcessData;
  s64 naturalAligment;

  ProcessData = (dds3ProcessID_t *)dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    return ProcessData[2];
  LOBYTE(ProcessData[2].shutdownfunc) < (u32)naturalAligment || *((tagRST_GROWTH_WORK **)(ProcessData)[1].next + naturalAligment - 1) != tagRST_GROWTH_WORK;
  return ProcessData[2];
}

// 0x1dfb330
void rstSetFlagPlayBgm(void) {
  Il2CppObject *ProcessData;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
  HIDWORD(ProcessData[3].monitor) |= 2u;
}

// 0x1dfb450
bool rstChkFlagPlayBgm(void) {
  u8 *ProcessData;

  ProcessData = dds3GetProcessData(g_mainPID);
  if (!ProcessData)
    return (ProcessData[60] >> 1) & 1;
  return (ProcessData[60] >> 1) & 1;
}

// 0x1dfa500
bool rstSetLvUpSkl(s32 i, s32 *pTmp) {
  void *v4;
  void *sklItemGuages;
  void *v7;
  _LvUpSkl *g_aLvUpSkl_local;
  _LvUpSkl *v9;
  Il2CppClass **v10;
  s64 v14;
  s32 level;
  s32 v18;
  s8 v19;
  s32 devilid;
  s32 v22;
  sdatUnitWork_t *v24;
  s32 v25;
  s32 v26;
  s32 v27;
  s32 v28;
  s32 v29;
  s32 v30;
  s32 v31;
  s32 v32;
  u64 v33;
  u64 v34;
  s64 v35;
  s64 v36;
  sdatUnitWork_t *v37;
  u64 *v38;
  s64 v39;
  s64 v40;
  s64 v41;
  SKLID *haveskill;
  s64 v43;
  s32 v46;
  void *v47;
  s32 v49;
  sdatUnitWork_t *v50;
  s32 v51;
  void *v52;
  void *v55;
  s32 v56;
  _LvUpSkl *v57;
  s64 v58;
  char *v59;
  s64 v61;
  s32 v62;
  s32 v64;
  s32 skill;
  s32 chuusei;
  s32 v69;
  void *v70;
  Il2CppObject *v71;
  s32 v74;
  sdatUnitWork_t *v75;
  s32 v76;
  s64 v77;
  char *v78;
  char v79;
  s64 v80;
  u32 v82;
  SKLID *aOmoideSkill;
  s32 v84;
  s64 v86;
  s64 v88;
  sdatUnitWork_t *v89;
  s64 v90;
  s64 v91;
  s64 v92;
  s32 v93;
  s32 *v95;
  sdatUnitWork_t *v96;
  u64 v99;
  s32 uSkillNo[2];
  s32 uSkillNoa;
  void *v102;
  s32 v103;
  s64 v105;

  v4 = Allocate(Project_rstGrowth___c__DisplayClass30_0);
  v4->skillid = 0;
  sklItemGuages = g_pUnitDst->sklItemGuages;
  v7 = Allocate(System_Collections_Generic_List_SklItemGuage_);
  __ctor_48217552(v7, sklItemGuages);
  g_aLvUpSkl_local = g_aLvUpSkl;
  v9 = Allocate(_LvUpSkl);
  LvUpSkl___ctor(v9, 0);
  v10 = &g_aLvUpSkl_local->obj.klass + i;
  v10[4] = v9;
  if ((g_pUnitSrc->flag & 1) == 0)
    return 1;
  if ((g_pUnitDst->flag & 1) == 0)
    return 1;
  v14 = i;
  v105 = i;
  level = g_pUnitDst->level;
  v18 = level - g_pUnitSrc->level;
  g_dvlLevelUpNum[i] = v18;
  if (v18 >= 1)
  {
    ++*pTmp;
    v19 = level;
    devilid = g_pUnitSrc->devilid;
    v22 = v19 - sBtlGetDevilData(devilid, -1)->level;
    v102 = v7;
    v24 = g_pUnitSrc;
    v25 = v24->level;
    v26 = v24->devilid;
    v27 = sBtlGetDevilData(v26, -1)->level;
    v28 = 0;
    if (v22 << 16 >= 0x40000)
      v29 = 3;
    else
      v29 = v22;
    v30 = v25 - v27;
    if ((v30 & 0x8000) != 0)
    {
      v14 = v105;
    }
    else
    {
      v14 = v105;
      v31 = v29 - v30;
      if (v31 << 16 >= 0x10000)
      {
        v32 = (u16)v30;
        v33 = 0;
        v28 = 0;
        v34 = (u16)v31;
        v35 = (u16)v30;
        v99 = v34;
        *(u64 *)uSkillNo = 8 * v105;
        do
        {
          v46 = g_pUnitSrc->aRsvSkl[v33 + v35];
          if (v46)
          {
            v46 = g_pUnitSrc->aRsvSkl[v33 + v35];
            v36 = (s64)g_aLvUpSkl + 8 * v14;
            v37 = g_pUnitDst;
            v38 = *(u64 **)(v36 + 32);
            v39 = v38[3];
            v40 = v38[2] + 4 * v33;
            *(u32 *)(v40 + 32) = v46;
            *(u32 *)(v39 + 4 * v33 + 32) = v32 + v33;
            v41 = v38[4];
            LODWORD(v38) = *(u32 *)(v40 + 32);
            *(u8 *)(v41 + v33 + 32) = 0;
            haveskill = v37->haveskill;
            v43 = (s64)v37->newSklDrwOff + 4 * v28++;
            haveskill[v33 + 1 + v35] = (s32)v38;
            *(u32 *)(v43 + 32) = *(u32 *)(v40 + 32);
          }
          else
          {
            v47 = Allocate(Project_rstGrowth___c__DisplayClass30_1);
            v49 = g_pUnitSrc->devilid;
            v50 = Allocate(sdatUnitWork_t);
            _ctor(v50, 0);
            datCreateDevilUnit(v49, v50);
            v51 = v50->aRsvSkl[v33 + v35];
            v47->skl = v51;
            if (v51)
            {
              v52 = Allocate(System_Predicate_SklItemGuage_);
              __ctor(v52, v47, Method_Project_rstGrowth___c__DisplayClass30_1__rstSetLvUpSkl_b__1__, 0);
              v14 = v105;
              if (_Find(v102, v52))
              {
                v55 = g_pUnitSrc->haveskill;
                (*(_LvUpSkl *)((char *)g_aLvUpSkl + *(u64 *)uSkillNo))->nmlSkl[v33] = v47->skl;
                v56 = IndexOf_Int32Enum_(v55, v47->skl);
                v14 = v105;
                v34 = v99;
                v57 = *(_LvUpSkl *)((char *)g_aLvUpSkl + *(u64 *)uSkillNo);
                v58 = (s64)v57->nmlSklPos + 4 * v33;
                v59 = (char *)v57->ofcSkl + v33;
                *(u32 *)(v58 + 32) = v56 - 1;
                v59[32] = 1;
              }
            }
            else
            {
              v14 = v105;
            }
          }
          ++v33;
        }
        while (v33 < v34);
      }
    }
    v7 = v102;
    g_pUnitDst->newSklCnt = v28;
    goto LABEL_52;
  }
LABEL_52:
  if (g_pUnitDst->chuusei >= 100)
  {
    if (g_pUnitSrc->chuusei <= 99)
    {
      v61 = 0;
      v62 = 0;
      do
      {
        v64 = g_pUnitSrc->devilid;
        skill = sBtlGetDevilData(v64, -1)->memskill[v61]->skill;
        v4->skillid = skill;
        if (!skill)
          goto LABEL_61;
        chuusei = g_pUnitDst->chuusei;
        v69 = g_pUnitSrc->devilid;
        if (chuusei < sBtlGetDevilData(v69, -1)->memskill[v61]->level)
          goto LABEL_61;
        v70 = Allocate(System_Predicate_SklItemGuage_);
        __ctor(v70, v4, Method_Project_rstGrowth___c__DisplayClass30_0__rstSetLvUpSkl_b__0__, 0);
        v71 = _Find(v7, v70);
        if (v71)
        {
          v74 = v4->skillid;
          v75 = g_pUnitDst;
          datOmoideSkillSetMaster(v75, v74, 0);
          datOmoideSkillSetMaster(g_pUnitSrc, v4->skillid, 0);
          v76 = IndexOf_Int32Enum_(g_pUnitSrc->aOmoideSkill, v4->skillid);
          if (v76 == -1)
          {
            v14 = v105;
            v79 = 1;
          }
          else
          {
            v14 = v105;
            v77 = v76;
            v78 = (char *)g_pUnitSrc->aOmoideSkill + v77 * 4;
            g_pUnitDst->aOmoideSkill[v77] = 0;
            *((u32 *)v78 + 8) = 0;
            v79 = 1;
          }
        }
        else
        {
          v79 = 0;
        }
        v80 = v62;
        g_aLvUpSkl[v14]->ofcMemSkl[v62] = v79;
        if (g_pUnitSrc->bOmoideLearned[v61])
          goto LABEL_61;
        g_pUnitDst->bOmoideLearned[v61] = 1;
        goto LABEL_9001;
        if (!v82)
        {
          v96 = g_pUnitSrc;
          v84 = v4->skillid;
          if (v96->aOmoideSkill[0] == v84)
            goto LABEL_61;
          v96 = g_pUnitSrc;
          v84 = v4->skillid;
          if (v96->aOmoideSkill[1] == v84)
            goto LABEL_61;
          v96 = g_pUnitSrc;
          v84 = v4->skillid;
          if (v96->aOmoideSkill[2] == v84)
            goto LABEL_61;
          v96 = g_pUnitSrc;
          v84 = v4->skillid;
          if (v96->aOmoideSkill[3] == v84)
            goto LABEL_61;
          v96 = g_pUnitSrc;
          v84 = v4->skillid;
          if (v96->aOmoideSkill[4] == v84)
            goto LABEL_61;
          v96 = g_pUnitSrc;
          v84 = v4->skillid;
          if (v96->aOmoideSkill[5] == v84)
            goto LABEL_61;
          v96 = g_pUnitSrc;
          v84 = v4->skillid;
          if (v96->aOmoideSkill[6] == v84)
            goto LABEL_61;
          v96 = g_pUnitSrc;
          v84 = v4->skillid;
          if (v96->aOmoideSkill[7] == v84)
            goto LABEL_61;
          v84 = v4->skillid;
LABEL_101:
          v103 = v62;
          v86 = v14;
          v88 = (s64)g_aLvUpSkl + 8 * v14;
          v89 = g_pUnitDst;
          v90 = *(u64 *)(v88 + 32);
          v92 = *(u64 *)(v90 + 40);
          v91 = *(u64 *)(v90 + 48);
          *(u32 *)(v92 + 4 * v80 + 32) = v84;
          *(u8 *)(v91 + v61 + 32) = 1;
          v93 = v4->skillid;
          uSkillNoa = v4->skillid;
          v93 = uSkillNoa;
          s_bRegistMemSkill[v80 + s_bRegistMemSkill->bounds[1].length * v86] = datOmoideSkillGetMaster(v89, v93);
          datOmoideSkillSetMaster(g_pUnitDst, g_aLvUpSkl[v86]->memSkl[v80], 1);
          v14 = v86;
          ++*pTmp;
          v95 = g_dvlLevelUpNum;
          if (!v95[v86])
          {
            v95 = g_dvlLevelUpNum;
            v95[v86] = -1;
          }
          v62 = v103 + 1;
          goto LABEL_61;
        }
LABEL_9001:
        aOmoideSkill = g_pUnitSrc->aOmoideSkill;
        v84 = v4->skillid;
        if (aOmoideSkill[0] != v84 && aOmoideSkill[1] != v84 && aOmoideSkill[2] != v84 && aOmoideSkill[3] != v84 && aOmoideSkill[4] != v84 && aOmoideSkill[5] != v84 && aOmoideSkill[6] != v84 && aOmoideSkill[7] != v84)
        {
          goto LABEL_101;
        }
LABEL_61:
        ++v61;
      }
      while (v61 != 2);
    }
  }
  return 1;
}

// 0x1dfb590
void rstInit(tagRST_GROWTH_WORK *wk, bool _talk) {
  void *p_Dependent;
  void *Dependent_local;
  void *Asset;
  sdfBinary *v12;
  u8 *data;
  dds3ProcessID_t *v14;
  tagRST_GROWTH_WORK *p_fields;
  dds3ProcessID_t *giftPID;
  dds3ProcessID_t *v17;
  dds3ProcessID_t *v19;
  void *v21;
  void *v23;

  if (talk)
  {
    goto LABEL_4;
  }
  Create(0);
  fclLoadData("rst_sys.bmd", rstAssetKey, 1);
  fclSkipNoEnd(g_mainPID, 1);
LABEL_4:
  p_Dependent = &Dependent;
  Dependent_local = p_Dependent;
  Load(Dependent_local, rstAssetKey, rstAssetKey);
  LoadSyncAll(_Ctrl_k__BackingField, 0);
  Asset = LoadAsset(_Ctrl_k__BackingField, rstAssetKey, "rst_sys_scr.bf", 0);
  v12 = Allocate(sdfBinary);
  _ctor(v12, Asset, 0);
  data = v12->data;
  wk->pDatScr = data;
  giftPID = wk->giftPID;
  p_fields = &wk->fields;
  v14 = giftPID;
  if (!giftPID)
  {
    v17 = fclProcessStart();
    p_fields->giftPID = v17;
    v14 = p_fields->giftPID;
  }
  fclSkipNoEnd(v14, 1);
  v19 = p_fields->giftPID;
  fclLoadDataEx(v19, "rst_gift.bmd", rstAssetKey, 1);
  if (talk)
  {
    goto LABEL_16;
  }
  fclGetLogStop(p_fields->giftPID, 1);
LABEL_16:
  v21 = &Dependent;
  v23 = v21;
  Unload(v23, rstAssetKey, 0);
}

// 0x1dfb8f0
dds3ProcessID_t *rstProcessStart(void) {
  sdatPlayerUnitWork_t *player;
  sdatPlayerUnitWork_t *PlayerUnit;
  void *Instance;
  tagRST_GROWTH_WORK *v10;
  Il2CppObject *v11;
  void *gameObject;
  Il2CppObject *v13;
  dds3ProcessFunc_t v14;
  shutdownfuncDelegate v15;
  dds3ProcessID_t *started;

  player = GBWK->player;
  g_pSrc = player;
  PlayerUnit = rstGetPlayerUnit();
  g_pDst = PlayerUnit;
  Instance = get_Instance(0);
  ItfButtonGuideActive(Instance, 0, 0);
  v10 = Allocate(tagRST_GROWTH_WORK);
  _ctor(v10, 0);
  if (((v10->klass->vtable._14_ChkInit.methodPtr)(v10, v10->klass->vtable._14_ChkInit.method) & 1) != 0)
  {
    v11 = _get_Instance();
    gameObject = get_gameObject(v11, 0);
    if (get_activeSelf(gameObject, 0))
    {
      v13 = _get_Instance();
      ResultActive(v13, 0, 0);
    }
    StatusSceneActive(1);
    cmpLoadLocalizeText();
    dds3FilterClear();
    v14 = Allocate(dds3ProcessFunc_t);
    _ctor(v14, v10, v10->klass->vtable._12_Process.0);
    v15 = Allocate(shutdownfuncDelegate);
    _ctor(v15, v10, v10->klass->vtable._15_Shutdown.0);
    started = dds3StartProcess("result_growth", 1028, 0, 0, v14, v15, v10);
    g_mainPID = started;
    rstInit(v10, 0);
    return g_mainPID;
  }
  else
  {
    g_mainPID = 0;
    return 0;
  }
}

// 0x1dfbdb0
dds3ProcessID_t *rstCmpItemGrowthStart(void) {
  sdatPlayerUnitWork_t *player;
  sdatPlayerUnitWork_t *rstPassUnit;
  void *v9;
  void *v10;
  void *v11;
  void *Instance;
  void *v13;
  sdatPlayerUnitWork_t *v14;
  void *v16;
  s32 inited;
  void *v20;
  dds3ProcessFunc_t v21;
  shutdownfuncDelegate v22;
  dds3ProcessID_t *started;

  player = GBWK->player;
  g_pSrc = player;
  CreatePassUnit(itmUpdateMg, 0);
  rstPassUnit = itmUpdateMg->rstPassUnit;
  g_pDst = rstPassUnit;
  Copy_56180528(g_pSrc->item, g_pDst->item, g_pSrc->item->max_length, 0);
  v9 = Allocate(Project_TagRST_GROWTH_WORK_ITM);
  _ctor(v9, 0);
  v10 = Allocate(rstData_t);
  _ctor(v10, 0);
  v9->rstData = v10;
  v11 = &v9->rstData;
  Instance = get_Instance(0);
  v9->prevBgm = GetPlayBGM_ID(Instance, 0);
  p2sdSndStopAll();
  sndBgmLoadId_XF(30);
  v13 = v11;
  v14 = Allocate(sdatPlayerUnitWork_t);
  _ctor(v14, 0);
  v13->PlayerPre = v14;
  ClassCopy(v11->PlayerPre, g_pDst, 0);
  ClassCopy(v11->Player, itmUpdateMg->rstPassUnit, 0);
  v16 = v11;
  inited = rstCalcRankUp(v16);
  v16->RankUp = inited;
  v9->oldMaxMag = GBWK->player->maxmag;
  if (((*(*(u64 *)v9 + 536))(v9, *(u64 *)(*(u64 *)v9 + 544)) & 1) == 0)
  {
    LogWarning("成長なし(キャンプデバッグモード以外は来ないはず)", 0);
    g_mainPID = 0;
    return 0;
  }
  v20 = v11;
  rstCalcGift(v20, 1);
  v21 = Allocate(dds3ProcessFunc_t);
  _ctor(v21, v9, *(u64 *)(*(u64 *)v9 + 512), 0);
  v22 = Allocate(shutdownfuncDelegate);
  _ctor(v22, v9, *(u64 *)(*(u64 *)v9 + 560), 0);
  started = dds3StartProcess("result_growth", 1028, 0, 0, v21, v22, v9);
  g_mainPID = started;
  rstInit(v9, 0);
  return g_mainPID;
}

// 0x1dfc7e0
void rstProcessEnd(void) {
  Il2CppObject *ProcessData;
  s32 monitor_high;

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
  monitor_high = HIDWORD(ProcessData[3].monitor);
  if ((monitor_high & 1) == 0)
  {
    WORD1(ProcessData[3].monitor) = 0;
    HIDWORD(ProcessData[3].monitor) = monitor_high | 1;
    LOBYTE(ProcessData[3].klass) = 3;
  }
}

// 0x1dfc9a0
bool rstProcessCheck(void) {
  if (!g_mainPID)
    return 0;
  if (dds3GetProcessStat(g_mainPID) != 3)
  {
    if (dds3GetProcessStat(g_mainPID))
    {
      return 1;
    }
  }
  g_mainPID = 0;
  return 0;
}
