#include "types.h"
#include "cfg.h"
#include "dat.h"
#include "dds3adminiprocess.h"
#include "dds3kernelcore.h"
#include "dds3kerneldraw.h"
#include "dds3randomize.h"
#include "evtbit.h"
#include "evtmoon.h"
#include "fld.h"
#include "jmsmisc.h"
#include "kernel.h"
#include "localize.h"
#include "rstgrowth.h"
#include "rstinit.h"
#include "rstresultdraw.h"
#include "sbtl.h"
#include "sbtlencount.h"
#include "sbtlevent.h"
#include "sbtlmain.h"
#include "sbtlsub.h"
#include "sbtlunit.h"
#include "scr.h"
#include "sdat.h"
#include "sdfsound.h"
#include "sndat3.h"

typedef struct dds3ProcessID_t dds3ProcessID_t;
typedef struct sdatPlayerUnitWork_t sdatPlayerUnitWork_t;
typedef struct sprHandle_t sprHandle_t;

dds3ProcessID_t *gGlobalPID;
s32 gGlobalFlag;
void *gGlobalReward;
s32 gGlobalEncNo;
s32 gGlobalDlcNo;
char *textAssetName;
s32 gRstMapLoad;
s32 gRstMapLoadTime;
s32 gRstMapReturn_XFade;
s32 gRstMapReturn_LvUp;
s8 *rstRankUpKudaAddNumTbl;

static void Destroy(dds3ProcessID_t *PID);

// 0x1dfce10
void rstLoadLocalizeText(void) {
  void *p_Dependent;
  void *Dependent_local;

  p_Dependent = &Dependent;
  Dependent_local = p_Dependent;
  Load(Dependent_local, textAssetName, textAssetName);
  LoadSyncAll(_Ctrl_k__BackingField, 0);
  LoadLocalizeText_2(textAssetName, "RESULT_TOP");
  Unload(Dependent, textAssetName, 0);
}

// 0x1dfcfc0
dds3ProcessFunc_t rstResultStartWaitProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  s32 klass;
  void *Instance;
  s32 v8;
  dds3ProcessFunc_t v9;
  dds3ProcessFunc_t v10;
  intptr_t *v11;
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
  if ((klass & 0x10000) != 0)
  {
    Instance = get_Instance(0);
    ItfButtonGuideActive(Instance, 0, 0);
    v8 = ProcessData[1].klass;
    LODWORD(ProcessData[1].klass) = v8 | 0x20;
    if ((v8 & 0x40) == 0)
    {
      LODWORD(ProcessData[1].klass) = v8 | 0x60;
      return 0;
    }
    v9 = Allocate(dds3ProcessFunc_t);
    v10 = v9;
    v11 = &Method_Project_Kernel_DDS3_PROC_END__;
  }
  else
  {
    if ((klass & 2) == 0)
      return 0;
    v9 = Allocate(dds3ProcessFunc_t);
    v10 = v9;
    v11 = &Method_Project_rstInit_ResultLoadWaitProcess__;
  }
  _ctor(v9, 0, *v11, 0);
  return v10;
}

// 0x1dfd1a0
dds3ProcessFunc_t rstResultLoadWaitProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  s32 klass;
  sprHandle_t *monitor;
  void *v7;
  Il2CppObject *Instance;
  bool v9;
  dds3ProcessFunc_t v10;
  Il2CppObject *v12;
  void *v16;
  void *v17;
  dds3ProcessFunc_t v19;
  dds3ProcessFunc_t v20;
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
  if ((klass & 4) != 0)
  {
    v10 = 0;
    LODWORD(ProcessData[1].klass) = klass | 4;
    return v10;
  }
  if ((klass & 8) != 0)
  {
    v10 = 0;
    LODWORD(ProcessData[1].klass) = klass | 8;
    return v10;
  }
  monitor = ProcessData[6].monitor;
  v7 = Allocate(rstBG_t);
  _ctor(v7, 0);
  v7->pSpr = monitor;
  ProcessData[7].monitor = v7;
  Instance = _get_Instance();
  v9 = op_Equality(Instance, 0, 0);
  v10 = 0;
  if (!v9)
  {
    if (!uiLoad)
      return 0;
    v12 = _get_Instance();
    ResultActive(v12, 1, 0);
    rstLoadLocalizeText();
    LODWORD(ProcessData[1].klass) |= 0x10u;
    if (fadergba.w != 1.0)
      goto LABEL_37;
    goto LABEL_34;
    if (fadergba.w != 1.0)
    {
LABEL_37:
      evtMoonDisableDraw(1);
      v16 = get_Instance(0);
      CloseDevilMes(v16, 0);
      v17 = get_Instance(0);
      ItfButtonGuideSet(v17, 0, 0);
      rstResultResultGuideSet(0, 0, 90);
      v19 = Allocate(dds3ProcessFunc_t);
      _ctor(v19, 0, Method_Project_rstResult_DrawProcess__, 0);
      dds3StartProcess("result_draw", 11026, 0, 1, v19, 0, ProcessData);
      v20 = Allocate(dds3ProcessFunc_t);
      _ctor(v20, 0, Method_Project_rstResult_UpdateProcess__, 0);
      dds3StartProcess("result_updt", 21007, 0, 1, v20, 0, ProcessData);
      v10 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
      _ctor(v10, 0, Method_Project_rstResult_CalcProcess__, 0);
      return v10;
    }
LABEL_34:
    dds3FadeIn2(8u);
    LODWORD(ProcessData[1].klass) |= 0x100u;
    goto LABEL_37;
  }
  return v10;
}

// 0x1dfda30
s32 rstLoadMapResource(s32 RetType) {
  s32 result;

  ++gRstMapLoadTime;
  if (!gRstMapLoad)
  {
    fldPlayerALoadStart();
    gRstMapLoad = 1;
    return 0;
  }
  if (gRstMapLoad != 1)
    goto LABEL_6;
  result = fldPlayerALoadEndCheck();
  if (!result)
    return result;
  gRstMapLoad = 2;
LABEL_7:
  if (gRstMapLoad != 2)
    goto LABEL_8;
  fldNakamaCashLoad_RndEncRetStart();
  gRstMapLoad = 3;
LABEL_9:
  if (gRstMapLoad != 3)
    goto LABEL_10;
  goto LABEL_48;
LABEL_6:
  goto LABEL_7;
LABEL_8:
  goto LABEL_9;
  if (gRstMapLoad != 3)
  {
LABEL_10:
    goto LABEL_11;
  }
LABEL_48:
  result = fldNakamaCashLoad_EndCheck();
  if (!result)
    return result;
  gRstMapLoad = 4;
LABEL_11:
  if (gRstMapLoad != 4)
  {
    goto LABEL_13;
    if (gRstMapLoad != 5)
    {
LABEL_14:
      goto LABEL_15;
    }
    goto LABEL_62;
  }
  fldAiboCashLoad_RndEncRetStart();
  gRstMapLoad = 5;
LABEL_13:
  if (gRstMapLoad != 5)
    goto LABEL_14;
LABEL_62:
  result = fldAiboCashLoad_EndCheck();
  if (result)
  {
    gRstMapLoad = 6;
LABEL_15:
    if (gRstMapLoad != 6)
    {
      goto LABEL_17;
      if (gRstMapLoad != 7)
      {
LABEL_18:
        if (RetType != 1)
          goto LABEL_19;
        goto LABEL_76;
      }
LABEL_74:
      gRstMapLoad = 8;
      if (RetType == 1)
      {
LABEL_76:
        gRstMapReturn_LvUp = 1;
        return 1;
      }
LABEL_19:
      if (RetType)
        return 1;
      result = 1;
      gRstMapReturn_XFade = 1;
      return result;
    }
    gRstMapLoad = 7;
LABEL_17:
    if (gRstMapLoad != 7)
      goto LABEL_18;
    goto LABEL_74;
  }
  return result;
}

// 0x1dfdf50
s32 rstMapReturnChkXFade(void *pData) {
  if ((pData->Flag & 0x20000) != 0)
    return 0;
  return gRstMapReturn_XFade;
}

// 0x1dfd6a0
void *InitBgCore(sprHandle_t *pSpr) {
  void *v3;

  v3 = (void *)Allocate(rstBG_t);
  _ctor(v3, 0);
  v3->pSpr = pSpr;
  return v3;
}

// 0x1dfe050
void *InitBG(void) {
  return 0;
}

// 0x1dfe060
void rstDestroyBG(void *pBG) {
  ;
}

// 0x1dfe070
void rstEndNext(void *pData) {
  SequenceParameter *v3;
  SB_ENCOUNTPAC *EncountPac;
  s32 endtype;
  SB_ENCOUNTPAC *v8;
  char *end_scrip;
  SB_ENCOUNTPAC *v11;
  s32 *EventBit;
  SB_ENCOUNTPAC *v17;
  s64 v19;
  s32 end_playerpos;
  SB_ENCOUNTPAC *v21;
  s32 end_map;
  s32 end_floor;
  SB_ENCOUNTPAC *v25;
  char *script_label;

  v3 = Allocate(SequenceParameter);
  _ctor(v3, 0);
  v3->CallData2 = 0;
  p2sdSndStop(4);
  if ((pData->Flag & 1) == 0)
    return;
  EncountPac = sBtlGetEncountPac(-1);
  endtype = EncountPac[gGlobalEncNo]->endtype;
  if (endtype == 2)
  {
    v11 = sBtlGetEncountPac(-1);
    script_label = v11[gGlobalEncNo]->end_scrip;
    if ((u32)gGlobalEncNo == 512 && evtBitCheck(2097))
      script_label = 0;
    if (gGlobalEncNo == 517 && evtBitCheck(2097))
    {
      EventBit = GBWK->EventBit;
      EventBit[65] |= 0x400000u;
    }
    v17 = sBtlGetEncountPac(-1);
    v19 = gGlobalEncNo;
    end_playerpos = v17[v19]->end_playerpos;
    if ((u32)v19 == 482 && sBtlCheckEndEscape())
      end_playerpos = 4098;
    v21 = sBtlGetEncountPac(-1);
    end_map = v21[gGlobalEncNo]->end_map;
    end_floor = sBtlGetEncountPac(-1)[gGlobalEncNo]->end_floor;
    mapSetSceneParam_BattleReturn(end_map, end_floor, end_playerpos, &script_label);
  }
  else if (endtype == 1)
  {
    v25 = sBtlGetEncountPac(-1);
    v3->CallData2 = v25[gGlobalEncNo]->end_eveno;
    dds3AdminiCallSequence(9, v3, 0);
    scrAllReleaseScript();
  }
  else if (!EncountPac[gGlobalEncNo]->endtype)
  {
    v8 = sBtlGetEncountPac(-1);
    end_scrip = v8[gGlobalEncNo]->end_scrip;
    mapReturnFromRndEncBattle(end_scrip);
  }
}

// 0x1dfc5d0
void rstCalcGift(void *pData, bool _item) {
  sdatPlayerUnitWork_t *PlayerPre;
  sdatUnitWork_t *stock_id;
  void *Reward;
  char *dropLog;
  char *v9;
  s64 v10;
  bool v11;
  sdatUnitWork_t *v14;
  s32 level;
  s32 v16;
  s32 v17;

  PlayerPre = pData->PlayerPre;
  pData->dvlReport = 0;
  stock_id = PlayerPre->stock_id;
  if (evtBitCheck(42))
  {
    Reward = pData->Reward;
    dropLog = Reward->dropLog;
    Reward = ((char *)Reward + 96);
    v9 = Concat_54766928(dropLog, "Gift =================================================\n", 0);
    Reward->klass = (rstReward_t_c *)v9;
    v10 = 0;
    v11 = item;
    while (1)
    {
      if (v10 >= datGetStockDevilNums(0))
        return;
      v14 = GBWK->player->stock_id[v10];
      if (v14->devilid)
      {
        level = v14->level;
        v16 = stock_id[v10]->level;
        if (level >= v16)
          goto LABEL_5;
        v17 = v16 - (char)level;
        if (v17 < 1)
          goto LABEL_5;
        do
        {
          rstDevilGiftCalc(pData, v10, v11);
          --v17;
        }
        while (v17);
      }
LABEL_5:
      ++v10;
    }
  }
}

// 0x1dfe4f0
void rstDevilGiftCalc(void *_pData, s32 _stockNo, bool _item) {
  void *Reward;
  char **p_dropLog;
  char *v9;
  char *dropLog;
  s64 v12;
  s32 devilid;
  char *v14;
  char *v15;
  s32 v16;
  void *v17;
  void *v18;
  s32 v19;
  s32 v20;
  sdatLvUpDevilGift_t *LvUpDevilGift;
  char *v22;
  char *v23;
  char **v24;
  char *v25;
  char *v26;
  char *v27;
  s32 v28;
  s32 Level;
  s32 Rate;
  f32 v32;
  s64 size;
  u64 *v34;
  f32 *items;
  void *v36;
  void *v37;
  char **v38;
  char *v39;
  char *v40;
  f32 v41;
  s64 v42;
  u64 *v43;
  f32 *v44;
  u64 *p_klass;
  char *v46;
  char *v47;
  u64 *v48;
  char *v49;
  char *v50;
  char *v51;
  f32 *v52;
  s32 v53;
  char **v54;
  char *v55;
  char *v56;
  char **v57;
  s32 v58;
  void *v59;
  u32 v60;
  void *Gift;
  void *v62;
  s64 v63;
  u32 v64;
  void *v65;
  sdatLvUpDevilGift_t *v66;
  char **v67;
  char *v68;
  char *v69;
  char *v70;
  char *v71;
  char *v72;
  char *v73;
  char *v74;
  char *v75;
  u8 v76;
  char *v77;
  char *v78;
  char *v79;
  char *v80;
  char *v81;
  sdatUnitWork_t *v83;
  void *v84;
  s32 v85;
  sdatUnitWork_t *v87;
  s64 p_g_pDst;
  void *v90;
  sdatUnitWork_t *v91;
  void *v92;
  char **v93;
  char *v94;
  char *v95;
  void *v96;
  char **v97;
  char *v98;
  char *v99;
  s32 ID;
  char *v101;
  bool v102;
  void *v103;
  s64 v104;
  s32 v105;

  Reward = pData->Reward;
  v104 = 0;
  v105 = 0;
  dropLog = Reward->dropLog;
  p_dropLog = &Reward->dropLog;
  v9 = dropLog;
  v103 = pData;
  v102 = item;
  v12 = stockNo;
  devilid = GBWK->player->stock_id[stockNo]->devilid;
  v14 = sdatDevilName(devilid, 0);
  v15 = Concat_54832128(v9, " Devil :", v14, "\n", 0);
  *p_dropLog = v15;
  v16 = 4 * GBWK->player->stock_id[v12]->devilid;
  v17 = Allocate(System_Collections_Generic_List_float_);
  __ctor(v17);
  v18 = v103;
  v19 = 0;
  v20 = 0;
  do
  {
    v28 = v16 + v19;
    Level = sdatGetLvUpDevilGift(v16 + v19)->Level;
    if (Level <= GBWK->player->stock_id[v12]->level)
    {
      Rate = sdatGetLvUpDevilGift(v28)->Rate;
      v105 = Rate;
      v32 = Rate;
      size = v17->_size;
      v34 = Method_System_Collections_Generic_List_float__Add__;
      ++v17->_version;
      items = v17->_items;
      if ((u32)size >= LODWORD(items->max_length))
      {
        _AddWithResize(v17, v32, *(const MethodInfo_2E30340 **)(*(u64 *)(v34[4] + 192) + 112));
        v20 += Rate;
        if (v105 < 1)
          goto LABEL_9;
      }
      else
      {
        v17->_size = size + 1;
        items[size] = v32;
        v20 += Rate;
        if (Rate < 1)
          goto LABEL_9;
      }
      v36 = v18->Reward;
      v37 = v18;
      v40 = v36->dropLog;
      v38 = &v36->dropLog;
      v39 = v40;
      LvUpDevilGift = sdatGetLvUpDevilGift(v28);
      v22 = sdatItemName(LvUpDevilGift->ItemID);
      v23 = Concat_54831728(v39, " Item : ", v22, 0);
      *v38 = v23;
      v24 = v37->Reward;
      v25 = v24[12];
      v24 += 12;
      v26 = ToString((s32)&v105, 0);
      v27 = Concat_54832128(v25, " Rate :", v26, "\n", 0);
      *v24 = v27;
      v18 = v37;
    }
LABEL_9:
    ++v19;
  }
  while (v19 != 4);
  if (v20 <= 99)
  {
    v41 = (100 - v20);
    v42 = v17->_size;
    v43 = Method_System_Collections_Generic_List_float__Add__;
    ++v17->_version;
    v44 = v17->_items;
    if ((u32)v42 >= LODWORD(v44->max_length))
    {
      _AddWithResize(v17, v41, *(const MethodInfo_2E30340 **)(*(u64 *)(v43[4] + 192) + 112));
    }
    else
    {
      v17->_size = v42 + 1;
      v44[v42] = v41;
    }
    p_klass = &v103->Reward->klass;
    v46 = p_klass[12];
    p_klass += 12;
    v47 = Concat_54766928(v46, " Item : failure", 0);
    *p_klass = v47;
    v48 = &v103->Reward->klass;
    HIDWORD(v104) = 100 - v20;
    v18 = v103;
    v49 = v48[12];
    v48 += 12;
    v50 = ToString((s32)&v104 + 4, 0);
    v51 = Concat_54832128(v49, " Rate :", v50, "\n", 0);
    *v48 = v51;
  }
  v52 = _ToArray(v17);
  v53 = dds3Choose(v52);
  if (v20 <= 99 && v53 == v17->_size - 1)
  {
    v54 = v18->Reward;
    v55 = v54[12];
    v54 += 12;
    v56 = Concat_54766928(v55, " Get :False\n", 0);
    *v54 = v56;
    v57 = v54;
    goto LABEL_57;
  }
  v58 = v53 + v16;
  if (sdatGetLvUpDevilGift(v58)->NumMax)
  {
    v59 = v18->Gift[v12];
    v59->ID = sdatGetLvUpDevilGift(v58)->ItemID;
    v60 = RAND(0);
    Gift = v18->Gift;
    v62 = v18;
    v63 = v12;
    v64 = v60;
    LODWORD(v104) = v60;
    v65 = Gift[v12];
    v66 = sdatGetLvUpDevilGift(v58);
    v67 = v62->Reward;
    v65->Nums = v64 % v66->NumMax + 1;
    v68 = NewSpecific(string, 0xAu);
    v69 = v67[12];
    v67 += 12;
    v70 = v68;
    v68[0] = v69;
    v71 = "DropNum :";
    v70[1] = "DropNum :";
    v72 = ToString((u32)v62->Gift[v12] + 20, 0);
    v70[2] = v72;
    v73 = "  rnd : (";
    v70[3] = "  rnd : (";
    v74 = ToString((u32)&v104, 0);
    v70[4] = v74;
    v75 = " % ";
    v70[5] = " % ";
    v76 = sdatGetLvUpDevilGift(v58);
    v77 = ToString(v76 + 22, 0);
    v70[6] = v77;
    v78 = ") + ";
    v70[7] = ") + ";
    HIDWORD(v104) = 1;
    v79 = ToString((s32)&v104 + 4, 0);
    v70[8] = v79;
    v80 = "\n";
    v70[9] = "\n";
    v81 = Concat_54832608(v70, 0);
    *v67 = v81;
    v83 = GBWK->player->stock_id[v12];
    if (!sBtlChkHaveMemSkl(v83, 46))
    {
      v87 = GBWK->player->stock_id[v12];
      if (sBtlChkHaveMemSkl(v87, 47))
      {
        v84 = v103->Gift[v12];
        v85 = 3 * v84->Nums;
        goto LABEL_48;
      }
      goto LABEL_9000;
    }
    v84 = v103->Gift[v12];
    v85 = 2 * v84->Nums;
LABEL_48:
    v84->Nums = v85;
LABEL_9000:
    if (v102)
    {
      p_g_pDst = &g_pDst;
      v90 = v103;
    }
    else
    {
      v90 = v103;
      p_g_pDst = &v103->Player;
    }
    v91 = *(sdatUnitWork_t *)(*(u64 *)(*(u64 *)p_g_pDst + 128) + v63 * 8 + 32);
    v92 = v90->Gift[v63];
    AddReportStok(v91, 4, v92->ID, v92->Nums, 0);
    v93 = v90->Reward;
    v90->dvlReport = 1;
    v94 = v93[12];
    v93 += 12;
    v95 = Concat_54766928(v94, " Get :True", 0);
    *v93 = v95;
    v96 = v90->Reward;
    v99 = v96->dropLog;
    v97 = &v96->dropLog;
    v98 = v99;
    ID = v90->Gift[v63]->ID;
    v101 = sdatItemName(ID);
    v56 = Concat_54832128(v98, " Item : ", v101, "\n", 0);
    *v97 = v56;
    v57 = v97;
LABEL_57:
  }
}

// 0x1dfc260
s32 rstCalcRankUp(void *pData) {
  s32 Flag;
  il2cpp_array_size_t max_length;
  s64 v7;
  s64 v8;
  u32 ChkFlag;
  sdatUnitWork_t *para;
  char *v13;
  s32 v14;
  s32 *EventBit;
  u32 SummonerRank;

  GBWK->EventBit[66] &= ~8u;
  Flag = pData->Flag;
  if (!evtBitCheck(43) && (Flag & 0x20000) == 0)
    return -1;
  max_length = sdatLvUpPlayerRankUp->max_length;
  if ((s32)max_length < 1)
    return -1;
  v7 = 0;
  v8 = (u32)max_length;
  while (1)
  {
    ChkFlag = sdatLvUpPlayerRankUp[v7]->ChkFlag;
    if (!ChkFlag)
    {
      goto LABEL_18;
    }
    ChkFlag = sdatLvUpPlayerRankUp[v7]->ChkFlag;
    if (!evtBitCheck(ChkFlag))
      return -1;
LABEL_18:
    if (!evtBitCheck(sdatLvUpPlayerRankUp[v7]->GetFlag))
    {
      para = pData->Player->para;
      if (datGetTotalCyuusei(para) >= sdatLvUpPlayerRankUp[v7]->Cyuusei)
        break;
    }
    if (v8 == ++v7)
      return -1;
  }
  v13 = (char *)rstRankUpKudaAddNumTbl + v7;
  v14 = v13[32];
  if (v13[32])
  {
    EventBit = GBWK->EventBit;
    EventBit[66] |= 8u;
  }
  else
  {
  }
  datAddStock(v14);
  pData->Player->stock_max = GBWK->player->stock_max;
  if ((pData->Flag & 0x10000) != 0)
  {
    SummonerRank = datGetSummonerRank();
    datSetSummonerRank(SummonerRank + 1);
  }
  return v7 + 2;
}

// 0x1dfee60
void rstPreCalcUnit(void *pData) {
  sdatPlayerUnitWork_t *PlayerPre;
  s64 v5;
  Il2CppClass **v6;
  char *v7;
  Il2CppClass *v8;
  s32 v9;
  sdatUnitWork_t *v11;
  s32 ExCyuusei;
  sdatUnitWork_t *para;
  s32 v14;
  s64 i;
  s64 v17;
  s32 v18;
  sdatUnitWork_t *v19;

  PlayerPre = pData->PlayerPre;
  PlayerPre->para->exp += pData->Reward->PlayerExp;
  datGetPlayerLevelUpUnit(PlayerPre, PlayerPre);
  v5 = 0;
  while (1)
  {
    if (v5 >= datGetStockDevilNums(0))
      break;
    v11 = pData->PlayerPre->stock_id[v5];
    v11->exp += pData->Reward->StockExp[v5];
    datGetDevilLevelUpUnit(v11, v11);
    v6 = &pData->PlayerPre->stock_id->obj.klass + v5;
    v7 = (char *)pData->Reward->Cyuusei + 4 * v5++;
    v8 = v6[4];
    v9 = (s16)(HIWORD(v8->_1.namespaze) + *((u16 *)v7 + 16));
    if (v9 >= 100)
      LOWORD(v9) = 100;
    HIWORD(v8->_1.namespaze) = v9;
  }
  ExCyuusei = pData->Reward->ExCyuusei;
  if (ExCyuusei)
  {
    para = pData->Player->para;
    v14 = ExCyuusei - datGetTotalCyuusei(para);
  }
  else
  {
    v14 = 0;
  }
  for (i = 4; ; ++i)
  {
    if (i - 4 >= datGetStockDevilNums(0))
      break;
    v18 = *(s16 *)(*((u64 *)&pData->PlayerPre->stock_id->obj.klass + i) + 30);
    v17 = *((u64 *)&GBWK->player->stock_id->obj.klass + i);
    v14 = v14 + v18 - *(s16 *)(v17 + 30);
  }
  v19 = pData->Player->para;
  datAddTotalCyuusei(v19, v14);
  rstCalcGift(pData, 0);
  pData->RankUp = rstCalcRankUp(pData);
}

// 0x1dff0e0
void *Init(void *pReward) {
  void *v3;
  void *Reward;
  s32 Flag;
  rstData_t_Fields *p_gGlobalFlag;
  signed s32 v8;
  s32 Cyuusei;
  void *v12;
  s64 v13;
  s32 StockDevilNums;
  void *v16;
  s32 *v17;
  s64 v18;
  s16 *stack_p;
  s32 v21;
  s32 v22;
  void *HankoWork;
  void *v24;
  void *v25;
  void *v26;
  s32 *StockExp;
  s32 v28;
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
  s32 v53;
  s32 v54;
  s32 v55;
  s32 v56;
  s32 v57;
  s32 v58;
  s32 v59;
  void *RewardWork;
  sdatPlayerUnitWork_t *Player;
  s64 v63;
  s64 v65;
  sdatPlayerUnitWork_t *PlayerPre;
  jmsSeqHandle_t *SeqHandle;

  v3 = (void *)Allocate(rstData_t);
  _ctor(v3, 0);
  if (pReward)
  {
    ClassCopy(v3->Reward, pReward, 0);
    Reward = v3->Reward;
    Reward->ExCyuusei = 0;
    Flag = v3->Flag;
    Reward = v3->Reward;
    p_gGlobalFlag = &gGlobalFlag;
    goto LABEL_28;
  }
  v8 = datGetSummonerRank() - 1;
  if (v8 < SLODWORD(sdatLvUpPlayerRankUp->max_length))
  {
    Cyuusei = sdatLvUpPlayerRankUp[v8]->Cyuusei;
    v3->KiraTimer = 0;
    goto LABEL_16;
  }
  Cyuusei = 0;
  v3->KiraTimer = 0;
LABEL_16:
  GBWK->EventBit[1] |= 0x400u;
  if (evtBitCheck(42))
    v3->Flag |= 0x20000u;
  v12 = v3->Reward;
  v13 = 8;
  v12->Money = 1000;
  *(u64 *)&v12->Item[0]->ID = 0x100000001LL;
  *(u64 *)&v12->ExpAll = 0;
  v12->ExCyuusei = Cyuusei;
  v12->Mag = 10;
  while (1)
  {
    StockDevilNums = datGetStockDevilNums(0);
    v16 = v3->Reward;
    if (v13 - 8 >= StockDevilNums)
      break;
    v17 = v16->Cyuusei;
    v18 = 4 * v13++;
    *(u32 *)((char *)&v16->StockExp->obj.klass + v18) = 200;
    *(u32 *)((char *)&v17->obj.klass + v18) = 50;
  }
  Reward = v3->Reward;
  Flag = 2;
  stack_p = GBWK->player->stack_p;
  v21 = stack_p[0];
  Reward->StockIndex1 = stack_p[1];
  p_gGlobalFlag = &v3->fields;
  v16->StockIndex0 = v21;
LABEL_28:
  v22 = p_gGlobalFlag->Flag;
  v3->KiraTimer = 0;
  v3->Flag = v22 | Flag;
  HankoWork = v3->HankoWork;
  v24 = HankoWork[1];
  HankoWork[0]->cnt = 0;
  v26 = HankoWork[2];
  v25 = HankoWork[3];
  v24->cnt = 0;
  v26->cnt = 0;
  v25->cnt = 0;
  Reward->PlayerExp += Reward->ExpAll;
  StockExp = Reward->StockExp;
  v28 = StockExp[0];
  if (v28 >= 1)
    StockExp[0] = Reward->ExpAll + v28;
  v29 = StockExp[1];
  if (v29 >= 1)
    StockExp[1] = Reward->ExpAll + v29;
  v30 = StockExp[2];
  if (v30 >= 1)
    StockExp[2] = Reward->ExpAll + v30;
  v31 = StockExp[3];
  if (v31 >= 1)
    StockExp[3] = Reward->ExpAll + v31;
  v32 = StockExp[4];
  if (v32 >= 1)
    StockExp[4] = Reward->ExpAll + v32;
  v33 = StockExp[5];
  if (v33 >= 1)
    StockExp[5] = Reward->ExpAll + v33;
  v34 = StockExp[6];
  if (v34 >= 1)
    StockExp[6] = Reward->ExpAll + v34;
  v35 = StockExp[7];
  if (v35 >= 1)
    StockExp[7] = Reward->ExpAll + v35;
  v36 = StockExp[8];
  if (v36 >= 1)
    StockExp[8] = Reward->ExpAll + v36;
  v37 = StockExp[9];
  if (v37 >= 1)
    StockExp[9] = Reward->ExpAll + v37;
  v38 = StockExp[10];
  if (v38 >= 1)
    StockExp[10] = Reward->ExpAll + v38;
  v39 = StockExp[11];
  if (v39 >= 1)
    StockExp[11] = Reward->ExpAll + v39;
  v40 = StockExp[12];
  if (v40 >= 1)
    StockExp[12] = Reward->ExpAll + v40;
  v41 = StockExp[13];
  if (v41 >= 1)
    StockExp[13] = Reward->ExpAll + v41;
  v42 = StockExp[14];
  if (v42 >= 1)
    StockExp[14] = Reward->ExpAll + v42;
  v43 = StockExp[15];
  if (v43 >= 1)
    StockExp[15] = Reward->ExpAll + v43;
  v44 = StockExp[16];
  if (v44 >= 1)
    StockExp[16] = Reward->ExpAll + v44;
  v45 = StockExp[17];
  if (v45 >= 1)
    StockExp[17] = Reward->ExpAll + v45;
  v46 = StockExp[18];
  if (v46 >= 1)
    StockExp[18] = Reward->ExpAll + v46;
  v47 = StockExp[19];
  if (v47 >= 1)
    StockExp[19] = Reward->ExpAll + v47;
  v48 = StockExp[20];
  if (v48 >= 1)
    StockExp[20] = Reward->ExpAll + v48;
  v49 = StockExp[21];
  if (v49 >= 1)
    StockExp[21] = Reward->ExpAll + v49;
  v50 = StockExp[22];
  if (v50 >= 1)
    StockExp[22] = Reward->ExpAll + v50;
  v51 = StockExp[23];
  if (v51 >= 1)
    StockExp[23] = Reward->ExpAll + v51;
  v52 = StockExp[24];
  if (v52 >= 1)
    StockExp[24] = Reward->ExpAll + v52;
  v53 = StockExp[25];
  if (v53 >= 1)
    StockExp[25] = Reward->ExpAll + v53;
  v54 = StockExp[26];
  if (v54 >= 1)
    StockExp[26] = Reward->ExpAll + v54;
  v55 = StockExp[27];
  if (v55 >= 1)
    StockExp[27] = Reward->ExpAll + v55;
  v56 = StockExp[28];
  if (v56 >= 1)
    StockExp[28] = Reward->ExpAll + v56;
  v57 = StockExp[29];
  if (v57 >= 1)
    StockExp[29] = Reward->ExpAll + v57;
  v58 = StockExp[30];
  if (v58 >= 1)
    StockExp[30] = Reward->ExpAll + v58;
  v59 = StockExp[31];
  if (v59 >= 1)
    StockExp[31] = Reward->ExpAll + v59;
  RewardWork = v3->RewardWork;
  Reward->ExpAll = 0;
  ClassCopy(RewardWork, Reward, 0);
  Player = v3->Player;
  ClassCopy(Player, GBWK->player, 0);
  ClassCopy(v3->PlayerMul, GBWK->player, 0);
  v63 = 0;
  v3->PlayerMul->para->exp <<= 8;
  while (v63 < datGetStockDevilNums(0))
  {
    v65 = (s64)v3->PlayerMul->stock_id + 8 * v63++;
    *(u32 *)(*(u64 *)(v65 + 32) + 36) <<= 8;
  }
  PlayerPre = v3->PlayerPre;
  ClassCopy(PlayerPre, GBWK->player, 0);
  rstPreCalcUnit(v3);
  SeqHandle = v3->SeqHandle;
  jmsInitSeqHandle(SeqHandle);
  *(u64 *)&gRstMapLoad = 0;
  *(u64 *)&gRstMapReturn_XFade = 0;
  return v3;
}

// 0x1dff820
static void Destroy(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  Il2CppClass *klass;
  sdatUnitWork_t *castClass;
  sdatParaWork_t *now;
  sdatParaWork_t *backup;
  s16 v10;
  sdatParaWork_t *v12;
  s16 v13;
  s16 vit;
  s16 v16;
  sdatUnitWork_t *para;
  sdatParaWork_t *v18;
  sdatParaWork_t *v19;
  s16 str;
  s16 tec;
  s32 luck;
  s32 v23;
  s32 v24;
  Il2CppClass *v25;
  s32 data_high;
  s32 v27;
  s32 v28;
  s32 v29;
  s32 v30;
  s32 v31;
  Il2CppClass *v32;
  sdatPlayerUnitWork_t *player;
  void *v34;
  u64 *v35;
  u32 *v36;
  s32 v37;
  s32 v38;
  u32 *v39;
  s32 v40;
  s32 v41;
  u32 *v42;
  s32 v43;
  s32 v44;
  u32 *v45;
  s32 v46;
  s32 v47;
  u32 *v48;
  s32 v49;
  s32 v50;
  u32 *v51;
  s32 v52;
  s32 v53;
  u32 *v54;
  s32 v55;
  s32 v56;
  u32 *v57;
  s32 v58;
  s32 v59;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  klass = ProcessData[4].klass;
  castClass = klass->_1.castClass;
  now = castClass->now;
  backup = castClass->backup;
  v10 = now->str + backup->str;
  backup->str = v10;
  v12 = backup;
  v13 = now->tec + v12->tec;
  vit = v12->vit;
  v12->tec = v13;
  v16 = now->vit + vit;
  v12->vit = v16;
  para = GBWK->player->para;
  v19 = para->now;
  v18 = para->backup;
  str = v19->str;
  tec = v19->tec;
  LOWORD(v19) = v19->vit;
  backup->str = v10 - str;
  v12->vit = v16 - (u16)v19;
  luck = v18->luck;
  v23 = v12->luck;
  v12->tec = v13 - tec;
  if (luck < v23)
  {
    v24 = GETITEMPARA(castClass->pitem->luck);
    v25 = ProcessData[4].klass->_1.castClass;
    data_high = SHIWORD(v25->_1.element_class->_1.byval_arg.data);
    v27 = SHIWORD(v25->_1.castClass->_1.byval_arg.data);
    v28 = v24 + v23 + data_high + v27 + sBtlGetCorrectionParamLuck();
    if (v28 <= 1)
      v29 = 1;
    else
      v29 = v28;
    klass = ProcessData[4].klass;
    castClass = klass->_1.castClass;
    v30 = castClass->now->luck;
    if (v29 <= v30)
      castClass->backup->luck += v30 - v29;
  }
  v31 = SWORD1(klass->_1.declaringType);
  datCalcNowParam(castClass, v31, 0);
  v32 = ProcessData[4].klass;
  player = GBWK->player;
  v34 = *(void **)&player->mag;
  WORD2(v32->_1.interfaceOffsets) = player->battleResult;
  v32->_1.this_arg.data = v34;
  ClassCopy(player, v32, 0);
  datDvlParaUpdate(0);
  datAddMoney(*((u32 *)ProcessData[2].monitor + 4));
  v35 = *((u64 **)ProcessData[2].monitor + 3);
  v36 = v35[4];
  v37 = v36[4];
  if (v37)
  {
    v38 = v36[6] + v36[5];
    if (v38 >= 1)
    {
      datAddItem(v37, v38);
      v35 = *((u64 **)ProcessData[2].monitor + 3);
    }
  }
  v39 = v35[5];
  v40 = v39[4];
  if (v40)
  {
    v41 = v39[6] + v39[5];
    if (v41 >= 1)
    {
      datAddItem(v40, v41);
      v35 = *((u64 **)ProcessData[2].monitor + 3);
    }
  }
  v42 = v35[6];
  v43 = v42[4];
  if (v43)
  {
    v44 = v42[6] + v42[5];
    if (v44 >= 1)
    {
      datAddItem(v43, v44);
      v35 = *((u64 **)ProcessData[2].monitor + 3);
    }
  }
  v45 = v35[7];
  v46 = v45[4];
  if (v46)
  {
    v47 = v45[6] + v45[5];
    if (v47 >= 1)
    {
      datAddItem(v46, v47);
      v35 = *((u64 **)ProcessData[2].monitor + 3);
    }
  }
  v48 = v35[8];
  v49 = v48[4];
  if (v49)
  {
    v50 = v48[6] + v48[5];
    if (v50 >= 1)
    {
      datAddItem(v49, v50);
      v35 = *((u64 **)ProcessData[2].monitor + 3);
    }
  }
  v51 = v35[9];
  v52 = v51[4];
  if (v52)
  {
    v53 = v51[6] + v51[5];
    if (v53 >= 1)
    {
      datAddItem(v52, v53);
      v35 = *((u64 **)ProcessData[2].monitor + 3);
    }
  }
  v54 = v35[10];
  v55 = v54[4];
  if (v55)
  {
    v56 = v54[6] + v54[5];
    if (v56 >= 1)
    {
      datAddItem(v55, v56);
      v35 = *((u64 **)ProcessData[2].monitor + 3);
    }
  }
  v57 = v35[11];
  v58 = v57[4];
  if (v58)
  {
    v59 = v57[6] + v57[5];
    if (v59 >= 1)
    {
      datAddItem(v58, v59);
    }
  }
  sBtlCheckTutorialEnd();
  dds3KillProcessName("result_draw", 0);
  dds3KillProcessName("result_updt", 0);
  rstProcessEnd();
  if ((BYTE2(ProcessData[1].klass) & 2) == 0)
  {
    rstEndNext(ProcessData);
  }
  Exit2();
  Exit3();
  RemoveKey(textAssetName);
  if (!cfgGetConfigGAME(1, 0))
    datPartyRecovery();
  gGlobalPID = 0;
}

// 0x1dfff30
s32 rstCheckTaiitsu(void) {
  return evtBitCheck(202) && !evtBitCheck(205);
}

// 0x1dfff70
dds3ProcessID_t *ProcessStart(void) {
  dds3ProcessID_t *v1;
  SequenceParameter *v2;
  void *gGlobalReward_local;
  dds3ProcessID_t *started;
  dds3ProcessID_t *v14;
  void *inited;
  dds3ProcessFunc_t v17;
  shutdownfuncDelegate v18;

  v1 = (dds3ProcessID_t *)Allocate(dds3ProcessID_t);
  _ctor(v1, 0);
  v2 = Allocate(SequenceParameter);
  _ctor(v2, 0);
  v2->CallData2 = 0;
  if (gGlobalPID)
  {
    return gGlobalPID;
  }
  if ((gGlobalFlag & 0x40000) == 0)
  {
    if ((gGlobalFlag & 1) == 0)
    {
      gGlobalReward_local = 0;
      goto LABEL_29;
    }
    gGlobalReward_local = gGlobalReward;
LABEL_29:
    inited = Init();
    if ((inited->Flag & 0x10000) == 0)
    {
      sndBgmPlay(30, 0);
    }
    v17 = Allocate(dds3ProcessFunc_t);
    _ctor(v17, 0, Method_Project_rstInit_ResultStartWaitProcess__, 0);
    v18 = Allocate(shutdownfuncDelegate);
    _ctor(v18, 0, Method_Project_rstInit_Destroy__, 0);
    started = dds3StartProcess("result_calc", 1028, 0, 1, v17, v18, inited);
    v1 = started;
    v14 = started;
    goto LABEL_21;
  }
  fldBgTexClear();
  if ((gGlobalFlag & 0x20000) != 0)
    goto LABEL_19;
  if (!evtBitCheck(202))
  {
LABEL_44:
    if ((gGlobalFlag & 0x80000) != 0)
    {
      mapRetuenFromNakamDead();
      started = 0;
      v14 = 0;
      goto LABEL_21;
    }
LABEL_47:
    v2->CallData2 = 696;
    dds3AdminiCallSequence(9, v2, 0);
    started = 0;
    v14 = 0;
    goto LABEL_21;
  }
  if (!evtBitCheck(205))
    goto LABEL_47;
  goto LABEL_44;
LABEL_19:
  started = 0;
  v14 = 0;
  v14 = started;
LABEL_21:
  gGlobalPID = v14;
  gGlobalFlag = 0;
  return v1;
}

// 0x1e003c0
void ProcessEnd(void) {
  dds3KillProcessName("result_calc", 0);
  dds3KillProcessName("result_draw", 0);
  dds3KillProcessName("result_updt", 0);
}

// 0x1e00480
s32 ProcessCheck(void) {
  return dds3SearchProcessName("result_calc") != 0;
}

// 0x1e00500
void rstSetReward(void *pReward) {
  if (pReward)
  {
    ClassCopy(gGlobalReward, pReward, 0);
    gGlobalFlag |= 1u;
  }
}

// 0x1e00590
void rstSetEncountDlcID(s32 _dlcID) {
  gGlobalDlcNo = dlcID;
  return;
}

// 0x1e00620
s32 rstGetEncountDlcID(void) {
  return gGlobalDlcNo;
}

// 0x1e006a0
void rstSetEncountNo(s32 EncountNo) {
  gGlobalEncNo = EncountNo;
  return;
}

// 0x1e00730
s32 rstGetGlobalEncountNo(void) {
  return gGlobalEncNo;
}

// 0x1e007b0
void rstSetFlag(s32 Flag) {
  gGlobalFlag |= Flag;
}

// 0x1e00820
s32 rstCheckFlag(s32 Flag) {
  Il2CppObject *ProcessData;

  if (gGlobalPID)
  {
    ProcessData = dds3GetProcessData(gGlobalPID);
    if (!ProcessData)
      return ((s64)ProcessData[1].klass & Flag) != 0;
    return ((s64)ProcessData[1].klass & Flag) != 0;
  }
  return (gGlobalFlag & Flag) != 0;
}

// 0x1e009c0
void rstResultStart(void) {
  Il2CppObject *ProcessData;

  if (gGlobalPID)
  {
    ProcessData = dds3GetProcessData(gGlobalPID);
    if (!ProcessData)
      goto LABEL_17;
    goto LABEL_15;
    if (!ProcessData)
    {
LABEL_17:
      LODWORD(ProcessData[1].klass) |= 2u;
      return;
    }
LABEL_15:
    goto LABEL_17;
  }
  gGlobalFlag |= 2u;
}

// 0x1e00b20
s32 rstResultFadeCheck(void) {
  Il2CppObject *ProcessData;

  if (!gGlobalPID)
    return 0;
  goto LABEL_6;
LABEL_13:
  goto LABEL_15;
LABEL_6:
  ProcessData = dds3GetProcessData(gGlobalPID);
  if (ProcessData)
    goto LABEL_13;
LABEL_15:
  if (((s64)ProcessData[1].klass & 0x20) != 0)
    return 2;
  else
    return 1;
}

// 0x1dfbc70
sdatPlayerUnitWork_t *rstGetPlayerUnit(void) {
  sdatPlayerUnitWork_t *ProcessData;
  s64 naturalAligment;

  if (!gGlobalPID)
    return 0;
  ProcessData = (sdatPlayerUnitWork_t *)dds3GetProcessData(gGlobalPID);
  if (!ProcessData)
    return ProcessData[8];
  LOBYTE(ProcessData[1].mag) < (u32)naturalAligment || *(rstData_t_c **)(*(u64 *)&ProcessData->spiritCnt + 8 * naturalAligment - 8) != rstData_t;
  return ProcessData[8];
}

// 0x1e00c70
s32 rstGetGiftItem(s32 StockIndex) {
  Il2CppObject *ProcessData;

  if (!gGlobalPID)
    return 0;
  ProcessData = dds3GetProcessData(gGlobalPID);
  if (!ProcessData)
    return *(u32 *)(*((u64 *)ProcessData[5].monitor + StockIndex + 4) + 16);
  return *(u32 *)(*((u64 *)ProcessData[5].monitor + StockIndex + 4) + 16);
}

// 0x1e00dd0
s32 rstGetGiftItemNums(s32 StockIndex) {
  Il2CppObject *ProcessData;

  if (!gGlobalPID)
    return 0;
  ProcessData = dds3GetProcessData(gGlobalPID);
  if (!ProcessData)
    return *(u32 *)(*((u64 *)ProcessData[5].monitor + StockIndex + 4) + 20);
  return *(u32 *)(*((u64 *)ProcessData[5].monitor + StockIndex + 4) + 20);
}

// 0x1e00f30
s32 rstCheckRankUp(void) {
  s32 *ProcessData;

  if (!gGlobalPID)
    return -1;
  ProcessData = dds3GetProcessData(gGlobalPID);
  if (!ProcessData)
    return ProcessData[24];
  return ProcessData[24];
}
