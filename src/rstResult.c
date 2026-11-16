#include "types.h"
#include "achievement.h"
#include "dat.h"
#include "dds3_pad.h"
#include "dds3kernelcore.h"
#include "dds3kerneldraw.h"
#include "evtbit.h"
#include "fld.h"
#include "itf.h"
#include "jmsmisc.h"
#include "kernel.h"
#include "rstgrowth.h"
#include "rstinit.h"
#include "rstresult.h"
#include "rstresultdraw.h"
#include "sbtl.h"
#include "sbtlencount.h"
#include "sbtlmain.h"
#include "sbtlscene.h"
#include "sdfmem.h"
#include "sdfsound.h"
#include "slmain.h"
#include "sndat3.h"
#include "tips.h"

typedef struct dds3ProcessID_t dds3ProcessID_t;
typedef struct jmsSeqUnit_t jmsSeqUnit_t;

jmsSeqUnit_t *gohSeqUnit[4];

static void QuestZakuroFlg(void);

// 0x1e06a90
s32 rstEndInit(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  s32 nowKiretsuIdx;
  s64 v6;
  s64 naturalAligment;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  nowKiretsuIdx = fldGb->nowKiretsuIdx;
  if (nowKiretsuIdx != -1)
    goto LABEL_7;
LABEL_14:
  if (ProcessData->klass->_2.naturalAligment >= (u32)naturalAligment && (rstData_t_c *)ProcessData->klass->_2.typeHierarchy[naturalAligment - 1] == rstData_t)
  {
    goto LABEL_12;
  }
LABEL_16:
  nowKiretsuIdx = fldGb->nowKiretsuIdx;
  if (nowKiretsuIdx == -1)
    goto LABEL_14;
LABEL_7:
  if (ProcessData)
  {
    if (ProcessData->klass->_2.naturalAligment < (u32)v6 || ProcessData->klass->_2.typeHierarchy[v6 - 1] != rstData_t)
    {
      goto LABEL_16;
    }
  }
  if (nowKiretsuIdx > 49)
  {
LABEL_12:
    HIDWORD(ProcessData[9].klass) = 0;
    return 1;
  }
  if (sBtlCheckEndEscape() == 1)
    goto LABEL_12;
  fldSetKiretsuFlg(fldGb->nowKiretsuIdx);
  QuestZakuroFlg();
  HIDWORD(ProcessData[9].klass) = 0;
  return 1;
}

// 0x1e07040
s32 rstEndDestroy(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  u64 *monitor;
  dds3ProcessID_t *v6;
  u64 *v7;
  dds3ProcessID_t *v8;
  u64 *v9;
  dds3ProcessID_t *v10;
  u64 *v11;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  monitor = ProcessData[10].monitor;
  v6 = monitor[4];
  if (v6)
  {
    itfCountProcessEnd(v6);
    v7 = ProcessData[10].monitor;
    v7[4] = 0;
    monitor = ProcessData[10].monitor;
  }
  v8 = monitor[5];
  if (v8)
  {
    itfCountProcessEnd(v8);
    v9 = ProcessData[10].monitor;
    v9[5] = 0;
    monitor = ProcessData[10].monitor;
  }
  v10 = monitor[6];
  if (v10)
  {
    itfCountProcessEnd(v10);
    v11 = ProcessData[10].monitor;
    v11[6] = 0;
  }
  HIDWORD(ProcessData[9].klass) = 0;
  return 1;
}

// 0x1e071e0
dds3ProcessFunc_t rstEndCalcProcess(dds3ProcessID_t *PID) {
  void *ProcessData;
  jmsSeqUnit_t *p_pSeqUnit;
  jmsSeqHandle_t *SeqHandle;
  dds3ProcessID_t *v7;
  dds3ProcessFunc_t v9;
  s32 step;
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
  p_pSeqUnit = &ProcessData->pSeqUnit;
  SeqHandle = ProcessData->SeqHandle;
  v7 = id;
  v9 = jmsSeqChange(SeqHandle, &ProcessData->pSeqUnit, 0, v7);
  if (v9)
    return v9;
  step = ProcessData->step;
  if (step != 1)
  {
    if (!step)
    {
      if (rstCallLoadMapResourceFunc(ProcessData))
      {
        ProcessData->step = 1;
        return 0;
      }
    }
    return v9;
  }
  if (ProcessData->dvlReport && !evtBitCheck(10009))
  {
    tipsTIPSStart(25);
    return 0;
  }
  else
  {
    if (tipsProcessCheck() || !CHECK_TRIG(4096, 1) && !CHECK_TRIG(4097, 1))
    {
      return v9;
    }
    gohSeqUnit_local = gohSeqUnit;
    jmsSeqJumpAndFree(p_pSeqUnit, &gohSeqUnit_local[2]);
    return 0;
  }
}

// 0x1e076a0
dds3ProcessFunc_t rstEndDrawProcess(dds3ProcessID_t *PID) {
  void *ProcessData;
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
  rstResultResultDraw(ProcessData);
  rstResultResultGuideSet(0, 0, 90);
  SeqHandle = ProcessData->SeqHandle;
  v6 = id;
  return jmsSeqChange(SeqHandle, &ProcessData->pSeqUnit, 1, v6);
}

// 0x1e07810
dds3ProcessFunc_t rstEndUpdateProcess(dds3ProcessID_t *PID) {
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

// 0x1e07930
s32 rstBtlEndWaitInit(dds3ProcessID_t *PID) {
  void *ProcessData;
  dds3ProcessID_t *id;

  id = PID;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  if (rstMapReturnChkXFade(ProcessData))
  {
    dds3FadeOut(0, 0, 0, 0x14u);
    return 1;
  }
  dds3FadeOut(0, 0, 0, 0x14u);
  if (!rstCheckLevelUp(ProcessData))
    return 1;
  sndBgmLoadId_XF(30);
  return 1;
}

// 0x1e07d80
s32 rstBtlEndWaitDestroy(dds3ProcessID_t *PID) {
  return 1;
}

// 0x1e07d90
dds3ProcessFunc_t rstBtlEndWaitCalcProcess(dds3ProcessID_t *PID) {
  void *ProcessData;
  jmsSeqUnit_t *p_pSeqUnit;
  jmsSeqHandle_t *SeqHandle;
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
  p_pSeqUnit = &ProcessData->pSeqUnit;
  SeqHandle = ProcessData->SeqHandle;
  v7 = id;
  v8 = jmsSeqChange(SeqHandle, &ProcessData->pSeqUnit, 0, v7);
  if (v8)
    return v8;
  if (rstMapReturnChkXFade(ProcessData))
  {
    goto LABEL_29;
  }
  rstCheckLevelUp(ProcessData);
  if (dds3FadeCheck())
    return v8;
LABEL_29:
  if (CheckRun())
    return v8;
  if (!sBtlReLoadFldScene())
    return v8;
  gohSeqUnit_local = gohSeqUnit;
  jmsSeqJumpAndFree(p_pSeqUnit, &gohSeqUnit_local[3]);
  return 0;
}

// 0x1e080a0
dds3ProcessFunc_t rstBtlEndWaitDrawProcess(dds3ProcessID_t *PID) {
  void *ProcessData;
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
  rstResultResultDraw(ProcessData);
  SeqHandle = ProcessData->SeqHandle;
  v6 = id;
  return jmsSeqChange(SeqHandle, &ProcessData->pSeqUnit, 1, v6);
}

// 0x1e08200
dds3ProcessFunc_t rstBtlEndWaitUpdateProcess(dds3ProcessID_t *PID) {
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

// 0x1e08320
s32 rstLvUpWaitInit(dds3ProcessID_t *PID) {
  return 1;
}

// 0x1e08330
s32 rstLvUpWaitDestroy(dds3ProcessID_t *PID) {
  return 1;
}

// 0x1e08340
dds3ProcessFunc_t rstLvUpWaitCalcProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  jmsSeqHandle_t *monitor;
  dds3ProcessID_t *v6;
  dds3ProcessFunc_t v7;
  s32 klass;
  Il2CppObject *Instance;
  void *gameObject;
  Il2CppObject *v12;
  SB_ENCOUNTPAC *EncountPac;
  s32 v20;
  s32 v21;
  char *v22;
  Il2CppObject *v23;
  dds3ProcessFunc_t v24;
  s32 v25;
  dds3ProcessID_t *id;

  id = PID;
  v25 = 0;
  ProcessData = dds3GetProcessData(id);
  if (!ProcessData)
    goto LABEL_9;
  goto LABEL_7;
  if (!ProcessData)
LABEL_7:
LABEL_9:
  monitor = ProcessData[1].monitor;
  v6 = id;
  v7 = jmsSeqChange(monitor, &ProcessData[2], 0, v6);
  if (v7)
    return v7;
  klass = ProcessData[1].klass;
  if ((klass & 0x80) == 0)
  {
    LODWORD(ProcessData[1].klass) = klass | 0x80;
    rstProcessStart();
    return 0;
  }
  v7 = 0;
  if (rstProcessCheck())
    return v7;
  v7 = 0;
  if (dds3FadeCheck())
    return v7;
  Instance = _get_Instance();
  gameObject = get_gameObject(Instance, 0);
  if (get_activeSelf(gameObject, 0))
  {
    v12 = _get_Instance();
    ResultActive(v12, 0);
  }
  else
  {
    goto LABEL_31;
  }
LABEL_31:
  EncountPac = sBtlGetEncountPac(gGlobalDlcNo);
  gGlobalDlcNo = -1;
  gGlobalEncNo = (u32)gGlobalEncNo;
  v25 = gGlobalEncNo;
  if ((gGlobalEncNo & 0x80000000) != 0)
    goto LABEL_52;
  goto LABEL_44;
  if ((gGlobalEncNo & 0x80000000) != 0)
  {
LABEL_52:
    v22 = ToString((s32)&v25, 0);
    v23 = Concat_54766928("不正な値::", v22, 0);
    LogError(v23, 0);
    goto LABEL_55;
  }
LABEL_44:
  if ((s32)gGlobalEncNo >= SLODWORD(EncountPac->max_length))
    goto LABEL_52;
  if (EncountPac[gGlobalEncNo]->endtype == 1)
  {
    v20 = ProcessData[9].klass;
    if (!v20)
    {
      sndBgmFadeOut();
      v20 = ProcessData[9].klass;
    }
    v21 = v20 + 1;
    LODWORD(ProcessData[9].klass) = v21;
    if (v21 <= 59)
      return 0;
  }
LABEL_55:
  sdfMemResourcesRelease();
  v24 = (dds3ProcessFunc_t)Allocate(dds3ProcessFunc_t);
  _ctor(v24, 0, Method_Project_Kernel_DDS3_PROC_END__, 0);
  return v24;
}

// 0x1e08920
dds3ProcessFunc_t rstLvUpWaitDrawProcess(dds3ProcessID_t *PID) {
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

// 0x1e08a40
dds3ProcessFunc_t rstLvUpWaitUpdateProcess(dds3ProcessID_t *PID) {
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

// 0x1e07bb0
s32 rstCheckLevelUp(void *pData) {
  s32 level;
  s64 i;
  s32 v7;
  s64 v8;
  s32 v9;

  level = pData->PlayerPre->para->level;
  if (level > GBWK->player->para->level)
    return 1;
  if (rstCheckRankUp() != -1)
    return 1;
  for (i = 4; ; ++i)
  {
    if (i - 4 >= datGetStockDevilNums(0))
      break;
    v7 = *(char *)(*((u64 *)&pData->PlayerPre->stock_id->obj.klass + i) + 24);
    v8 = *((u64 *)&GBWK->player->stock_id->obj.klass + i);
    if (v7 > *(char *)(v8 + 24))
      return 1;
    v9 = *(s16 *)(*((u64 *)&pData->PlayerPre->stock_id->obj.klass + i) + 30);
    if (v9 <= *(s16 *)(v8 + 30))
      continue;
    if (*(u16 *)(*((u64 *)&pData->PlayerPre->stock_id->obj.klass + i) + 30) == 100)
      return 1;
  }
  return 0;
}

// 0x1e07480
s32 rstCallLoadMapResourceFunc(void *pData) {
  SB_ENCOUNTPAC *EncountPac;
  s32 v9;

  if ((pData->Flag & 0x20000) != 0)
    return 1;
  if (!wk)
    goto LABEL_12;
  if ((wk->status5 & 0x80) != 0)
    goto LABEL_12;
  return 0;
LABEL_12:
  if ((pData->Flag & 1) == 0)
    return 1;
  EncountPac = sBtlGetEncountPac(-1);
  if (((u16)EncountPac[gGlobalEncNo]->endtype | 2) != 2)
    return 1;
  v9 = rstCheckLevelUp(pData);
  return rstLoadMapResource(v9);
}

// 0x1e08b60
dds3ProcessFunc_t rstCalcProcess(dds3ProcessID_t *PID) {
  void *ProcessData;
  jmsSeqHandle_t *SeqHandle;
  dds3ProcessID_t *v6;
  dds3ProcessFunc_t result;
  s32 Flag;
  bool v10;
  s32 step;
  bool v12;
  s32 Timer;
  s32 v14;
  s32 v15;
  void *Reward;
  u32 lucktypef;
  s32 drawexp;
  dds3ProcessID_t *cntrPID;
  dds3ProcessID_t *v20;
  s32 v21;
  dds3ProcessID_t *v22;
  dds3ProcessID_t *v23;
  dds3ProcessID_t *v24;
  dds3ProcessID_t *v25;
  dds3ProcessID_t *v26;
  dds3ProcessID_t *v27;
  dds3ProcessID_t *v28;
  s32 v29;
  bool v30;
  s32 v31;
  bool v32;
  s32 v33;
  jmsSeqUnit_t *gohSeqUnit_local;
  s32 v36;
  s32 drawchu;
  s32 v38;
  dds3ProcessID_t *v39;
  dds3ProcessID_t *v40;
  s32 drawmon;
  s32 v42;
  dds3ProcessID_t *v43;
  dds3ProcessID_t *v44;
  s32 v45;
  u32 KiraTimer;
  s32 v47;
  _BOOL4 v49;
  s64 i;
  void *v51;
  s32 v54;
  sdatPlayerUnitWork_t *Player;
  s32 PlayerExp;
  sdatUnitWork_t *para;
  s32 v58;
  s32 v59;
  s32 v60;
  sdatUnitWork_t *v62;
  sdatUnitWork_t *v63;
  s32 level;
  Il2CppObject *Instance;
  void *v67;
  s64 v68;
  Il2CppObject *v69;
  void *v71;
  s32 v73;
  s32 v74;
  s32 v75;
  sdatUnitWork_t *v76;
  sdatUnitWork_t *v78;
  sdatUnitWork_t *v79;
  s32 v80;
  s32 v81;
  void *v82;
  Il2CppObject *v83;
  s64 v85;
  void *v86;
  s32 v89;
  s32 v90;
  sdatUnitWork_t *v91;
  s32 chuusei;
  sdatUnitWork_t *v93;
  s32 v94;
  void *v95;
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
  result = jmsSeqChange(SeqHandle, &ProcessData->pSeqUnit, 0, v6);
  if (result)
    return result;
  Flag = ProcessData->Flag;
  if ((Flag & 0x100) != 0)
  {
    ProcessData->AlphaRate = 256;
    v10 = dds3FadeCheck();
    result = 0;
    if (v10)
      return result;
    Flag = ProcessData->Flag;
  }
  if ((Flag & 0x20) == 0)
  {
    result = 0;
    if (ProcessData->AlphaRate <= 255)
      ProcessData->AlphaRate = 256;
    else
      ProcessData->Flag = Flag | 0x60;
    return result;
  }
  rstCallLoadMapResourceFunc(ProcessData);
  step = ProcessData->step;
  switch (step)
  {
    case 0:
      v12 = CHECK_TRIG(4096, 1);
      Timer = ProcessData->Timer;
      if (v12)
      {
        if (Timer <= 0)
          goto LABEL_67;
      }
      else if (Timer < 20)
      {
        goto LABEL_67;
      }
      if (ProcessData->Reward->lucktypef)
        v45 = 1;
      else
        v45 = 7;
      ProcessData->step = v45;
      ProcessData->Timer = 1;
      if (v45 >= 4)
        goto LABEL_102;
      return 0;
    case 1:
      v14 = ProcessData->Timer;
      if (v14 < 10)
        goto LABEL_34;
      v15 = 2;
      goto LABEL_32;
    case 2:
      v14 = ProcessData->Timer;
      if (v14 < 10)
        goto LABEL_34;
      v15 = 3;
LABEL_32:
      v14 = 0;
      ProcessData->step = v15;
LABEL_34:
      ProcessData->Timer = v14 + 1;
      return 0;
    case 3:
      v14 = ProcessData->Timer;
      if (v14 < 10)
        goto LABEL_34;
      ProcessData->Timer = 0;
      ProcessData->step = 7;
      if ((ProcessData->Reward->lucktypef & 7) == 0)
        goto LABEL_67;
      v31 = 4;
      goto LABEL_101;
    case 4:
      Reward = ProcessData->Reward;
      lucktypef = Reward->lucktypef;
      if ((lucktypef & 1) != 0 && (drawexp = Reward->drawexp, drawexp >= 1))
      {
        cntrPID = ProcessData->cntrPID;
        v20 = itfCountProcessStart(drawexp, 30, 2, 5);
        sub_C80(cntrPID, v20);
        cntrPID[0] = v20;
        itfCountSetData(ProcessData->cntrPID[0], ProcessData->Reward->drawexp, 2);
        Reward = ProcessData->Reward;
        v21 = 1;
        lucktypef = Reward->lucktypef;
      }
      else
      {
        v21 = 0;
      }
      if ((lucktypef & 2) != 0)
      {
        drawchu = Reward->drawchu;
        if (drawchu >= 1)
        {
          if (v21)
            v38 = -1;
          else
            v38 = 5;
          v39 = ProcessData->cntrPID;
          v40 = itfCountProcessStart(drawchu, 30, 2, v38);
          sub_C80(v39, v40);
          v39[1] = v40;
          itfCountSetData(ProcessData->cntrPID[1], ProcessData->Reward->drawchu, 2);
          Reward = ProcessData->Reward;
          v21 = 1;
          lucktypef = Reward->lucktypef;
        }
      }
      if ((lucktypef & 4) != 0 && (drawmon = Reward->drawmon, drawmon >= 1))
      {
        if (v21)
          v42 = -1;
        else
          v42 = 5;
        v43 = ProcessData->cntrPID;
        v44 = itfCountProcessStart(drawmon, 30, 2, v42);
        sub_C80(v43, v44);
        v43[2] = v44;
        itfCountSetData(ProcessData->cntrPID[2], ProcessData->Reward->drawmon, 2);
      }
      else if (!v21)
      {
LABEL_92:
        v31 = 6;
LABEL_101:
        ProcessData->step = v31;
        ProcessData->Timer = 1;
        goto LABEL_102;
      }
      v31 = 5;
      goto LABEL_101;
    case 5:
      if (!CHECK_TRIG(4096, 1) && ProcessData->Timer < 40)
        goto LABEL_67;
      v22 = ProcessData->cntrPID;
      v23 = v22[0];
      if (v23)
      {
        itfCountProcessEnd(v23);
        v24 = ProcessData->cntrPID;
        v24[0] = 0;
        v22 = ProcessData->cntrPID;
      }
      v25 = v22[1];
      if (v25)
      {
        itfCountProcessEnd(v25);
        v26 = ProcessData->cntrPID;
        v26[1] = 0;
        v22 = ProcessData->cntrPID;
      }
      v27 = v22[2];
      if (v27)
      {
        itfCountProcessEnd(v27);
        v28 = ProcessData->cntrPID;
        v28[2] = 0;
      }
      goto LABEL_92;
    case 6:
      v29 = ProcessData->Timer + 1;
      v30 = ProcessData->Timer - 50 < 0;
      ProcessData->Timer = v29;
      if (v30 != __OFSUB__(v29, 51))
        goto LABEL_67;
      v31 = 7;
      ProcessData->KiraTimer = 0;
      goto LABEL_101;
    case 7:
      v32 = CHECK_TRIG(4096, 1);
      v33 = ProcessData->Timer;
      if (v32)
      {
        if (v33 > 9 || ProcessData->step >= 8)
          ProcessData->Timer = 60;
      }
      else if (v33 > 60)
      {
        ProcessData->Timer = 0;
        ProcessData->step = 11;
        goto LABEL_102;
      }
      if (ProcessData->Reward->PlayerExp)
      {
        v49 = GBWK->player->para->level < 99;
      }
      else
      {
        v49 = 0;
      }
      for (i = 0; ; ++i)
      {
        if (i >= datGetStockDevilNums(0))
          break;
        v51 = ProcessData->Reward;
        if (v51->StockExp[i])
        {
          v51 = ProcessData->Reward;
          if (GBWK->player->stock_id[i]->level <= 98)
            v49 = 1;
        }
        if (v51->Cyuusei[i])
        {
          if (GBWK->player->stock_id[i]->chuusei <= 99)
            v49 = 1;
        }
      }
      if (!v49)
      {
        ProcessData->Timer = 60;
        ProcessData->step = 11;
        return 0;
      }
      v54 = ProcessData->Timer;
      if (v54 == 1)
      {
        SE(6);
        v54 = ProcessData->Timer;
      }
      Player = ProcessData->Player;
      PlayerExp = ProcessData->Reward->PlayerExp;
      para = Player->para;
      v58 = (u64)(2290649225LL * ((PlayerExp * v54) << 8)) >> 32;
      v59 = ((u32)v58 >> 31) + (v58 >> 13);
      v60 = ((u32)v58 >> 31) + (v58 >> 5);
      ProcessData->RewardWork->PlayerExp = PlayerExp - v59;
      v62 = para;
      v63 = GBWK->player->para;
      para->exp = v63->exp + v59;
      LODWORD(v63) = v60 + (v63->exp << 8);
      level = v62->level;
      ProcessData->PlayerMul->para->exp = (s32)v63;
      datGetPlayerLevelUpUnit(Player, Player);
      if (ProcessData->Player->para->level > level)
      {
        Instance = _get_Instance();
        LevelUpAnim(Instance, 0);
        v67 = ProcessData->aLevelUpAnimQue[0];
        rstResultAddLevelUpAnimQue(v67);
        SE(8);
      }
      v68 = 0;
      while (2)
      {
        if (v68 < datGetStockDevilNums(0))
        {
          v73 = ProcessData->Reward->StockExp[v68];
          v74 = (u64)(2290649225LL * ((v73 * ProcessData->Timer) << 8)) >> 32;
          v75 = ((v73 * ProcessData->Timer) << 8) / 15360;
          ProcessData->RewardWork->StockExp[v68] = v73 - v75;
          v76 = ProcessData->Player->stock_id[v68];
          v78 = ProcessData->Player->stock_id[v68];
          v79 = GBWK->player->stock_id[v68];
          v80 = v79->exp + v75;
          v81 = v78->level;
          v76->exp = v80;
          ProcessData->PlayerMul->stock_id[v68]->exp = ((u32)v74 >> 31)
                                                                                   + (v74 >> 5)
                                                                                   + (v79->exp << 8);
          datGetDevilLevelUpUnit(v78, v78);
          if (ProcessData->Player->stock_id[v68]->level <= v81)
            goto LABEL_142;
          v82 = ProcessData->Reward;
          if (v68 == v82->StockIndex0)
          {
            v69 = _get_Instance();
            LevelUpAnim(v69, 1);
            v71 = ProcessData->aLevelUpAnimQue[1];
          }
          else
          {
            if (v68 != v82->StockIndex1)
              goto LABEL_142;
            v83 = _get_Instance();
            LevelUpAnim(v83, 2);
            v71 = ProcessData->aLevelUpAnimQue[2];
          }
          rstResultAddLevelUpAnimQue(v71);
          SE(8);
LABEL_142:
          ++v68;
          continue;
        }
        break;
      }
      v85 = 0;
      break;
    case 11:
      ProcessData->drawMoney += ProcessData->addMoney;
      gohSeqUnit_local = gohSeqUnit;
      jmsSeqJumpAndFree(&ProcessData->pSeqUnit, &gohSeqUnit_local[1]);
      p2sdSndStop(6);
      goto LABEL_67;
    default:
      goto LABEL_68;
  }
  while (1)
  {
    if (v85 >= datGetStockDevilNums(0))
      break;
    v89 = ProcessData->Reward->Cyuusei[v85];
    v90 = ProcessData->Timer * v89 / 60;
    ProcessData->RewardWork->Cyuusei[v85] = v89 - v90;
    v91 = ProcessData->Player->stock_id[v85];
    chuusei = v91->chuusei;
    v93 = ProcessData->Player->stock_id[v85];
    v91->chuusei = GBWK->player->stock_id[v85]->chuusei + v90;
    v94 = v93->chuusei;
    if (v94 > 100)
    {
      v93->chuusei = 100;
      if (chuusei >= 100)
        goto LABEL_156;
    }
    else if (chuusei > 99 || v94 != 100)
    {
      goto LABEL_156;
    }
    v95 = ProcessData->Reward;
    if (v85 == v95->StockIndex0)
    {
      v86 = ProcessData->aCyuuseiMaxAnimQue[0];
      goto LABEL_155;
    }
    if (v85 == v95->StockIndex1)
    {
      v86 = ProcessData->aCyuuseiMaxAnimQue[1];
LABEL_155:
      rstResultAddCyuuseiMaxAnimQue(v86);
      SE(7);
    }
LABEL_156:
    ++v85;
  }
LABEL_67:
  step = ProcessData->step;
LABEL_68:
  if (step != 11)
  {
    v36 = ProcessData->Timer + 1;
    if (v36 >= 10000)
      v36 = 10000;
    ProcessData->Timer = v36;
    if (step < 4)
      return 0;
  }
LABEL_102:
  KiraTimer = ProcessData->KiraTimer;
  result = 0;
  if (KiraTimer + 1 < 0x1E)
    v47 = KiraTimer + 1;
  else
    v47 = 30;
  ProcessData->KiraTimer = v47;
  return result;
}

// 0x1e099e0
dds3ProcessFunc_t rstDrawProcess(dds3ProcessID_t *PID) {
  void *ProcessData;
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
  rstResultResultDraw(ProcessData);
  SeqHandle = ProcessData->SeqHandle;
  v6 = id;
  return jmsSeqChange(SeqHandle, &ProcessData->pSeqUnit, 1, v6);
}

// 0x1e09b40
dds3ProcessFunc_t rstUpdateProcess(dds3ProcessID_t *PID) {
  Il2CppObject *ProcessData;
  jmsSeqUnit_t *v5;
  jmsSeqHandle_t *monitor;
  dds3ProcessID_t *v7;
  dds3ProcessFunc_t v8;
  void *achievementTbl_k__BackingField;
  Project_DefineAchievementID_string__c *klass;
  s64 v15;
  Project_DefineAchievementID_string__c **p_offset;
  s64 v17;
  char *v18;
  dds3SystemWork_t *SystemWork_local;
  s16 v21;
  s32 nowKiretsuIdx;
  bool v26;
  long f64 v28;
  s64 v29;
  char *v30;
  s32 v31;
  long f64 v32;
  s64 v33;
  char *v34;
  s16 v36;
  void *v38;
  Project_DefineAchievementID_string__c *v39;
  s64 v40;
  Project_DefineAchievementID_string__c **v41;
  s64 v42;
  char *v43;
  bool v44;
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
  v8 = jmsSeqChange(monitor, v5, 2, v7);
  if (!v8)
    return v8;
  if (gGlobalEncNo == 512)
  {
    if (evtBitCheck(2097))
    {
      goto LABEL_22;
    }
  }
  achievementTbl_k__BackingField = _achievementTbl_k__BackingField;
  klass = achievementTbl_k__BackingField->klass;
  v15 = *(u16 *)&achievementTbl_k__BackingField->klass->_2.rank;
  if (*(u16 *)&achievementTbl_k__BackingField->klass->_2.rank)
  {
    p_offset = &klass->_1.interfaceOffsets->offset;
    while (*(p_offset - 1) != Project_DefineAchievementID_string_)
    {
      p_offset += 2;
      if (!--v15)
        goto LABEL_31;
    }
    v17 = &klass->vtable[*(u32 *)p_offset + 21];
  }
  else
  {
LABEL_31:
    v17 = sub_4227F4(_achievementTbl_k__BackingField, Project_DefineAchievementID_string_, 0x15u);
  }
  v18 = (*v17)(achievementTbl_k__BackingField, *(u64 *)(v17 + 8));
  Unlock_2(v18);
  if (fldGb->nowKiretsuIdx < 0)
    return v8;
  goto LABEL_38;
LABEL_22:
  if (fldGb->nowKiretsuIdx < 0)
    return v8;
LABEL_38:
  if (sBtlCheckEndEscape() == 1)
  {
    ZakuroRewordEve = 0;
    return v8;
  }
  SystemWork_local = SystemWork;
  v21 = ++SystemWork_local->sakemeCnt;
  if ((v21 & 0x100) != 0)
    goto LABEL_44;
  goto LABEL_9002;
  if ((v36 & 0x100) != 0)
  {
LABEL_44:
    goto LABEL_45;
  }
LABEL_9002:
  v38 = _achievementTbl_k__BackingField;
  v39 = v38->klass;
  v40 = *(u16 *)&v38->klass->_2.rank;
  if (*(u16 *)&v38->klass->_2.rank)
  {
    v41 = &v39->_1.interfaceOffsets->offset;
    while (*(v41 - 1) != Project_DefineAchievementID_string_)
    {
      v41 += 2;
      if (!--v40)
        goto LABEL_69;
    }
    v42 = &v39->vtable[*(u32 *)v41 + 19];
  }
  else
  {
LABEL_69:
    v42 = sub_4227F4(_achievementTbl_k__BackingField, Project_DefineAchievementID_string_, 0x13u);
  }
  v43 = (*v42)(v38, *(u64 *)(v42 + 8));
  Unlock_2(v43);
LABEL_45:
  ZakuroRewordEve = 0;
  nowKiretsuIdx = fldGb->nowKiretsuIdx;
  if (nowKiretsuIdx > 49)
  {
    nowKiretsuIdx = fldGb->nowKiretsuIdx;
    fldZakuroBitOn(nowKiretsuIdx);
    return v8;
  }
  nowKiretsuIdx = fldGb->nowKiretsuIdx;
  if (nowKiretsuIdx > 19)
    return v8;
  v26 = fldZakuroBitChk(nowKiretsuIdx);
  if (v26)
    goto LABEL_54;
  goto LABEL_9003;
  if (v44)
  {
LABEL_54:
    goto LABEL_55;
  }
LABEL_9003:
  ZakuroRewordEve = 1;
LABEL_55:
  fldZakuroBitOn(fldGb->nowKiretsuIdx);
  v29 = sub_1A24F60(0, v28);
  v30 = sub_8360(20, Project_DefineAchievementID_string_, v29);
  v31 = fldZakuroNowGet();
  ProgressUnlock_3(v30, v31, 20);
  if (!fldZakuroChkComp())
    return v8;
  v33 = sub_1A24F60(0, v32);
  v34 = sub_8360(20, Project_DefineAchievementID_string_, v33);
  Unlock_2(v34);
  return v8;
}

// 0x1e06c70
static void QuestZakuroFlg(void) {
  u32 nowKiretsuIdx;
  s32 *EventBit;
  s32 *v6;
  s32 *v8;
  s32 *v10;
  s32 *v12;
  s32 *v14;
  s32 *v16;

  nowKiretsuIdx = fldGb->nowKiretsuIdx;
  if (nowKiretsuIdx <= 0x15)
  {
    switch (nowKiretsuIdx)
    {
      case 0u:
        if (!evtBitCheck(12292))
        {
          EventBit = GBWK->EventBit;
          EventBit[384] |= 0x10u;
        }
        break;
      case 1u:
        if (!evtBitCheck(12294))
        {
          v6 = GBWK->EventBit;
          v6[384] |= 0x40u;
        }
        break;
      case 2u:
        if (!evtBitCheck(12296))
        {
          v8 = GBWK->EventBit;
          v8[384] |= 0x100u;
        }
        break;
      case 0x14u:
        if (evtBitCheck(12403))
        {
          v10 = GBWK->EventBit;
          v10[387] &= ~0x80000u;
        }
        break;
      case 0x15u:
        if (evtBitCheck(12331))
        {
          v12 = GBWK->EventBit;
          v12[385] &= ~0x800u;
        }
        break;
      default:
        break;
    }
  }
  if (!evtBitCheck(12290) && evtBitCheck(12292) && evtBitCheck(12294) && evtBitCheck(12296) && !evtBitCheck(12689))
  {
    v14 = GBWK->EventBit;
    v14[384] |= 4u;
  }
  if (evtBitCheck(12329) && !evtBitCheck(12331) && !evtBitCheck(12332))
  {
    v16 = GBWK->EventBit;
    v16[385] |= 0x400u;
  }
}
