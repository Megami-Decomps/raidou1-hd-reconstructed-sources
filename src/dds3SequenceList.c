#include "types.h"
#include "cmpmain.h"
#include "dds3adminiprocess.h"
#include "dds3kernelcore.h"
#include "dds3kerneldraw.h"
#include "dds3sequencelist.h"
#include "ditectivebook.h"
#include "evt.h"
#include "evtsky.h"
#include "fld.h"
#include "gohinit.h"
#include "jmsinit.h"
#include "kernel.h"
#include "lmap.h"
#include "rstinit.h"
#include "sbtl.h"
#include "shpmain.h"
#include "slmain.h"
#include "staffmain.h"
#include "titlemain.h"

typedef struct SequenceParameter SequenceParameter;
typedef struct dds3AdminiList_t dds3AdminiList_t;

dds3AdminiList_t *AdminiList[44];

static void CallDebug(DDS3_ADMINI_CALL flg, SequenceParameter *param);
static s32 ExitDebug(void);
static bool CheckDebug(void);
static void CallBootMc(DDS3_ADMINI_CALL flg, SequenceParameter *param);
static s32 ExitBootMc(void);
static bool CheckBootMc(void);
static void CallTitle(DDS3_ADMINI_CALL flg, SequenceParameter *param);
static s32 ExitTitle(void);
static bool CheckTitle(void);
static void CallLoad(DDS3_ADMINI_CALL flg, SequenceParameter *param);
static s32 ExitLoad(void);
static bool CheckLoad(void);
static void CallSave(DDS3_ADMINI_CALL flg, SequenceParameter *param);
static s32 ExitSave(void);
static bool CheckSave(void);
static void CallStaff(DDS3_ADMINI_CALL flg, SequenceParameter *param);
static s32 ExitStaff(void);
static bool CheckStaff(void);
static void CallEndSave(DDS3_ADMINI_CALL flg, SequenceParameter *param);
static s32 ExitEndSave(void);
static bool CheckEndSave(void);
static void CallEpSave(DDS3_ADMINI_CALL flg, SequenceParameter *param);
static s32 ExitEpSave(void);
static bool CheckEpSave(void);
static void CallField(DDS3_ADMINI_CALL flg, SequenceParameter *param);
static s32 ExitField(void);
static bool CheckField(void);
static void CallFieldMcLoad(DDS3_ADMINI_CALL flg, SequenceParameter *param);
static s32 ExitFieldMcLoad(void);
static bool CheckFieldMcLoad(void);
static void CallNewBattle(DDS3_ADMINI_CALL flg, SequenceParameter *param);
static s32 ExitNewBattle(void);
static bool CheckNewBattle(void);
static void CallEvent(DDS3_ADMINI_CALL flg, SequenceParameter *param);
static s32 ExitEvent(void);
static bool CheckEvent(void);
static void CallCamp(DDS3_ADMINI_CALL flg, SequenceParameter *param);
static s32 ExitCamp(void);
static bool CheckCamp(void);
static void CallShop(DDS3_ADMINI_CALL flg, SequenceParameter *param);
static s32 ExitShop(void);
static bool CheckShop(void);
static void CallResult2(DDS3_ADMINI_CALL flg, SequenceParameter *param);
static s32 ExitResult2(void);
static bool CheckResult2(void);
static void CallConfig(DDS3_ADMINI_CALL flg, SequenceParameter *param);
static s32 ExitConfig(void);
static bool CheckConfig(void);
static void CallDitectiveBook(DDS3_ADMINI_CALL flg, SequenceParameter *param);
static s32 ExitDitectiveBook(void);
static bool CheckDitectiveBook(void);
static void CallJimusyo(DDS3_ADMINI_CALL flg, SequenceParameter *param);
static s32 ExitJimusyo(void);
static bool CheckJimusyo(void);
static void CallNewBattleTest(DDS3_ADMINI_CALL flg, SequenceParameter *param);
static s32 ExitNewBattleTest(void);
static bool CheckNewBattleTest(void);
static void CallBattleFieldTest(DDS3_ADMINI_CALL flg, SequenceParameter *param);
static s32 ExitBattleFieldTest(void);
static bool CheckBattleFieldTest(void);
static void CallEventTest(DDS3_ADMINI_CALL flg, SequenceParameter *param);
static s32 ExitEventTest(void);
static bool CheckEventTest(void);
static void CallEventViewer(DDS3_ADMINI_CALL flg, SequenceParameter *param);
static s32 ExitEventViewer(void);
static bool CheckEventViewer(void);
static void CallInterfaceTest(DDS3_ADMINI_CALL flg, SequenceParameter *param);
static s32 ExitInterfaceTest(void);
static bool CheckInterfaceTest(void);
static void CallCampTest(DDS3_ADMINI_CALL flg, SequenceParameter *param);
static s32 ExitCampTest(void);
static bool CheckCampTest(void);
static void CallShopTest(DDS3_ADMINI_CALL flg, SequenceParameter *param);
static s32 ExitShopTest(void);
static bool CheckShopTest(void);
static void CallTerminalTest(DDS3_ADMINI_CALL flg, SequenceParameter *param);
static s32 ExitTerminalTest(void);
static bool CheckTerminalTest(void);
static void CallResult2Test(DDS3_ADMINI_CALL flg, SequenceParameter *param);
static s32 ExitResult2Test(void);
static bool CheckResult2Test(void);
static void CallModelViewerTest(DDS3_ADMINI_CALL flg, SequenceParameter *param);
static s32 ExitModelViewerTest(void);
static bool CheckModelViewerTest(void);
static void CallSoundTest(DDS3_ADMINI_CALL flg, SequenceParameter *param);
static s32 ExitSoundTest(void);
static bool CheckSoundTest(void);
static void CallFontTest(DDS3_ADMINI_CALL flg, SequenceParameter *param);
static s32 ExitFontTest(void);
static bool CheckFontTest(void);
static void CallMovieViewerTest(DDS3_ADMINI_CALL flg, SequenceParameter *param);
static s32 ExitMovieViewerTest(void);
static bool CheckMovieViewerTest(void);
static void CallSprMotEditTest(DDS3_ADMINI_CALL flg, SequenceParameter *param);
static s32 ExitSprMotEditTest(void);
static bool CheckSprMotEditTest(void);
static void CallLmap(DDS3_ADMINI_CALL flg, SequenceParameter *param);
static s32 ExitLmap(void);
static bool CheckLmap(void);
static void CallMahjon(DDS3_ADMINI_CALL flg, SequenceParameter *param);
static s32 ExitMahjon(void);
static bool CheckMahjon(void);
static void CallMorph(DDS3_ADMINI_CALL flg, SequenceParameter *param);
static s32 ExitMorph(void);
static bool CheckMorph(void);
static void CallCtnTest(DDS3_ADMINI_CALL flg, SequenceParameter *param);
static s32 ExitCtnTest(void);
static bool CheckCtnTest(void);
static void CallNameEntryTest(DDS3_ADMINI_CALL flg, SequenceParameter *param);
static s32 ExitNameEntryTest(void);
static bool CheckNameEntryTest(void);
static void CallNameEntry(DDS3_ADMINI_CALL flg, SequenceParameter *param);
static s32 ExitNameEntry(void);
static bool CheckNameEntry(void);
static void CallSEffect(DDS3_ADMINI_CALL flg, SequenceParameter *param);
static s32 ExitSEffect(void);
static bool CheckSEffect(void);
static void CallWater(DDS3_ADMINI_CALL flg, SequenceParameter *param);
static s32 ExitWater(void);
static bool CheckWater(void);
static void CallHanafudaTest(DDS3_ADMINI_CALL flg, SequenceParameter *param);
static s32 ExitHanafudaTest(void);
static bool CheckHanafudaTest(void);
static void CallGomaden(DDS3_ADMINI_CALL flg, SequenceParameter *param);
static s32 ExitGomaden(void);
static bool CheckGomaden(void);
static void CallJimusyoTest(DDS3_ADMINI_CALL flg, SequenceParameter *param);
static s32 ExitJimusyoTest(void);
static bool CheckJimusyoTest(void);
static void CallStorySelect(DDS3_ADMINI_CALL flg, SequenceParameter *param);
static s32 ExitStorySelect(void);
static bool CheckStorySelect(void);
void Start(s32 aFieldNo);
void ShutDown(void);

// 0x2299f40
static void CallDebug(DDS3_ADMINI_CALL flg, SequenceParameter *param) {
  ;
}

// 0x2299f50
static s32 ExitDebug(void) {
  return 1;
}

// 0x2299f60
static bool CheckDebug(void) {
  return 0;
}

// 0x2299f70
static void CallBootMc(DDS3_ADMINI_CALL flg, SequenceParameter *param) {
  ;
}

// 0x2299f80
static s32 ExitBootMc(void) {
  return -1;
}

// 0x2299f90
static bool CheckBootMc(void) {
  return 0;
}

// 0x2299fa0
static void CallTitle(DDS3_ADMINI_CALL flg, SequenceParameter *param) {
  if (param)
    LODWORD(param) = param->CallData2;
  TitleProcessStart((s32)param);
}

// 0x229a020
static s32 ExitTitle(void) {
  TitleProcessEnd();
  return 0;
}

// 0x229a0a0
static bool CheckTitle(void) {
  return !TitleProcessCheck();
}

// 0x229a100
static void CallLoad(DDS3_ADMINI_CALL flg, SequenceParameter *param) {
  fmProcTrigSequence(4);
}

// 0x229a180
static s32 ExitLoad(void) {
  fmShutDownFade();
  fmShutDown();
  if (!fmShutDown2())
    return -1;
  mapRetuenFromLoad();
  return 0;
}

// 0x229a230
static bool CheckLoad(void) {
  return fmProcessChk() == 0;
}

// 0x229a290
static void CallSave(DDS3_ADMINI_CALL flg, SequenceParameter *param) {
  fmProcTrigSequence(0);
}

// 0x229a310
static s32 ExitSave(void) {
  fmShutDownFade();
  fmShutDown();
  if (!fmShutDown2())
    return -1;
  mapRetuenFromSave();
  return 0;
}

// 0x229a3c0
static bool CheckSave(void) {
  return fmProcessChk() == 0;
}

// 0x229a420
static void CallStaff(DDS3_ADMINI_CALL flg, SequenceParameter *param) {
  ProcessStart(0);
}

// 0x229a490
static s32 ExitStaff(void) {
  ProcessEnd();
  return 0;
}

// 0x229a510
static bool CheckStaff(void) {
  ProcessCheck();
  return 0;
}

// 0x229a590
static void CallEndSave(DDS3_ADMINI_CALL flg, SequenceParameter *param) {
  fmProcTrigSequence(2);
}

// 0x229a610
static s32 ExitEndSave(void) {
  fmShutDownFade();
  fmShutDown();
  return fmShutDown2() - 1;
}

// 0x229a680
static bool CheckEndSave(void) {
  return fmProcessChk() == 0;
}

// 0x229a6e0
static void CallEpSave(DDS3_ADMINI_CALL flg, SequenceParameter *param) {
  GBWK->fldSave->tmnltype = 2;
  fmProcTrigSequence(0);
}

// 0x229a790
static s32 ExitEpSave(void) {
  fmShutDownFade();
  fmShutDown();
  return fmShutDown2() - 1;
}

// 0x229a800
static bool CheckEpSave(void) {
  return fmProcessChk() == 0;
}

// 0x229a860
static void CallField(DDS3_ADMINI_CALL flg, SequenceParameter *param) {
  SceneParam_t *CallData4;

  if (!param || (CallData4 = param->CallData4) == 0)
  {
    if (!flg)
      return;
    CallData4 = 0;
  }
  dds3BistaIn(0);
  fldProcTrigSequence(CallData4, flg);
}

// 0x229a940
static s32 ExitField(void) {
  fldAllShutDown(0);
  if (!fldProcShutDown2())
    return -1;
  if (!gMapCampMcLoadEnd)
    return 0;
  mapRetuenFromLoad();
  return 0;
}

// 0x229aa70
static bool CheckField(void) {
  return 0;
}

// 0x229aa80
static void CallFieldMcLoad(DDS3_ADMINI_CALL flg, SequenceParameter *param) {
  mapRetuenFromLoad();
}

// 0x229aaf0
static s32 ExitFieldMcLoad(void) {
  return 0;
}

// 0x229ab00
static bool CheckFieldMcLoad(void) {
  return 0;
}

// 0x229ab10
static void CallNewBattle(DDS3_ADMINI_CALL flg, SequenceParameter *param) {
  dds3BistaIn(0);
}

// 0x229ab90
static s32 ExitNewBattle(void) {
  return 0;
}

// 0x229aba0
static bool CheckNewBattle(void) {
  return 0;
}

// 0x229abb0
static void CallEvent(DDS3_ADMINI_CALL flg, SequenceParameter *param) {
  s32 CallData2;

  if (flg != 1)
  {
    if (flg)
      return;
    if (!param)
      return;
    CallData2 = param->CallData2;
    if (CallData2 < 1)
      return;
    goto LABEL_11;
  }
  CallData2 = NextEventNo;
  if (CallData2 >= 1)
  {
LABEL_11:
    if ((u32)CallData2 <= 0x63)
    {
      mapStartMap(CallData2);
    }
    else
    {
      evtInit();
      evtStartEvent(CallData2);
    }
  }
}

// 0x229acf0
static s32 ExitEvent(void) {
  Exit();
  return 0;
}

// 0x229ad10
static bool CheckEvent(void) {
  return 0;
}

// 0x229ad20
static void CallCamp(DDS3_ADMINI_CALL flg, SequenceParameter *param) {
  cmpProcessStart();
}

// 0x229ad90
static s32 ExitCamp(void) {
  cmpProcessEnd();
  return 0;
}

// 0x229ae10
static bool CheckCamp(void) {
  return !cmpProcessCheck();
}

// 0x229ae70
static void CallShop(DDS3_ADMINI_CALL flg, SequenceParameter *param) {
  s32 CallData2;

  CallData2 = param->CallData2;
  shpProcessStart(CallData2);
}

// 0x229af00
static s32 ExitShop(void) {
  shpProcessEnd();
  return 0;
}

// 0x229af80
static bool CheckShop(void) {
  return !shpProcessCheck();
}

// 0x229afe0
static void CallResult2(DDS3_ADMINI_CALL flg, SequenceParameter *param) {
  ;
}

// 0x229aff0
static s32 ExitResult2(void) {
  return 0;
}

// 0x229b000
static bool CheckResult2(void) {
  return 1;
}

// 0x229b010
static void CallConfig(DDS3_ADMINI_CALL flg, SequenceParameter *param) {
  ;
}

// 0x229b020
static s32 ExitConfig(void) {
  return 0;
}

// 0x229b030
static bool CheckConfig(void) {
  return 0;
}

// 0x229b040
static void CallDitectiveBook(DDS3_ADMINI_CALL flg, SequenceParameter *param) {
  GBWK->fldSave->tmnltype = 0;
  DebugProcessStart();
}

// 0x229b0e0
static s32 ExitDitectiveBook(void) {
  ProcessEnd();
  return 0;
}

// 0x229b160
static bool CheckDitectiveBook(void) {
  return ProcessCheck() == 0;
}

// 0x229b1c0
static void CallJimusyo(DDS3_ADMINI_CALL flg, SequenceParameter *param) {
  GBWK->fldSave->tmnltype = 0;
  jmsProcessStart(param);
}

// 0x229b280
static s32 ExitJimusyo(void) {
  jmsProcessEnd();
  return 0;
}

// 0x229b300
static bool CheckJimusyo(void) {
  return jmsProcessCheck() == 0;
}

// 0x229b360
static void CallNewBattleTest(DDS3_ADMINI_CALL flg, SequenceParameter *param) {
  SBTLMAIN_DATA *v5;

  if (param)
    param = param->CallData5;
  v5 = Allocate(SBTLMAIN_DATA);
  _ctor(v5, 0);
  if (flg)
  {
    dds3AdminiExitSequence();
  }
  else
  {
    Start(param, 1, 0);
  }
}

// 0x229b410
static s32 ExitNewBattleTest(void) {
  return Exit(1, 0) - 1;
}

// 0x229b480
static bool CheckNewBattleTest(void) {
  if (dds3SearchProcessName("sbattle"))
    return 0;
  if (dds3SearchProcessPriority(1017))
    return 0;
  return ProcessCheck() == 0;
}

// 0x229b5a0
static void CallBattleFieldTest(DDS3_ADMINI_CALL flg, SequenceParameter *param) {
  ;
}

// 0x229b5b0
static s32 ExitBattleFieldTest(void) {
  return 0;
}

// 0x229b5c0
static bool CheckBattleFieldTest(void) {
  return 0;
}

// 0x229b5d0
static void CallEventTest(DDS3_ADMINI_CALL flg, SequenceParameter *param) {
  ;
}

// 0x229b5e0
static s32 ExitEventTest(void) {
  return 1;
}

// 0x229b5f0
static bool CheckEventTest(void) {
  return 0;
}

// 0x229b600
static void CallEventViewer(DDS3_ADMINI_CALL flg, SequenceParameter *param) {
  ;
}

// 0x229b610
static s32 ExitEventViewer(void) {
  return 0;
}

// 0x229b620
static bool CheckEventViewer(void) {
  return 0;
}

// 0x229b630
static void CallInterfaceTest(DDS3_ADMINI_CALL flg, SequenceParameter *param) {
  ;
}

// 0x229b640
static s32 ExitInterfaceTest(void) {
  return 0;
}

// 0x229b650
static bool CheckInterfaceTest(void) {
  return 0;
}

// 0x229b660
static void CallCampTest(DDS3_ADMINI_CALL flg, SequenceParameter *param) {
  ;
}

// 0x229b670
static s32 ExitCampTest(void) {
  return 0;
}

// 0x229b680
static bool CheckCampTest(void) {
  return 0;
}

// 0x229b690
static void CallShopTest(DDS3_ADMINI_CALL flg, SequenceParameter *param) {
  ;
}

// 0x229b6a0
static s32 ExitShopTest(void) {
  return 0;
}

// 0x229b6b0
static bool CheckShopTest(void) {
  return 0;
}

// 0x229b6c0
static void CallTerminalTest(DDS3_ADMINI_CALL flg, SequenceParameter *param) {
  ;
}

// 0x229b6d0
static s32 ExitTerminalTest(void) {
  return 0;
}

// 0x229b6e0
static bool CheckTerminalTest(void) {
  return 0;
}

// 0x229b6f0
static void CallResult2Test(DDS3_ADMINI_CALL flg, SequenceParameter *param) {
  ;
}

// 0x229b700
static s32 ExitResult2Test(void) {
  return 0;
}

// 0x229b710
static bool CheckResult2Test(void) {
  return 0;
}

// 0x229b720
static void CallModelViewerTest(DDS3_ADMINI_CALL flg, SequenceParameter *param) {
  ;
}

// 0x229b730
static s32 ExitModelViewerTest(void) {
  return 0;
}

// 0x229b740
static bool CheckModelViewerTest(void) {
  return 0;
}

// 0x229b750
static void CallSoundTest(DDS3_ADMINI_CALL flg, SequenceParameter *param) {
  ;
}

// 0x229b760
static s32 ExitSoundTest(void) {
  return 0;
}

// 0x229b770
static bool CheckSoundTest(void) {
  return 0;
}

// 0x229b780
static void CallFontTest(DDS3_ADMINI_CALL flg, SequenceParameter *param) {
  ;
}

// 0x229b790
static s32 ExitFontTest(void) {
  return 0;
}

// 0x229b7a0
static bool CheckFontTest(void) {
  return 0;
}

// 0x229b7b0
static void CallMovieViewerTest(DDS3_ADMINI_CALL flg, SequenceParameter *param) {
  ;
}

// 0x229b7c0
static s32 ExitMovieViewerTest(void) {
  return 1;
}

// 0x229b7d0
static bool CheckMovieViewerTest(void) {
  return 0;
}

// 0x229b7e0
static void CallSprMotEditTest(DDS3_ADMINI_CALL flg, SequenceParameter *param) {
  ;
}

// 0x229b7f0
static s32 ExitSprMotEditTest(void) {
  return 0;
}

// 0x229b800
static bool CheckSprMotEditTest(void) {
  return 0;
}

// 0x229b810
static void CallLmap(DDS3_ADMINI_CALL flg, SequenceParameter *param) {
  if (param)
    LODWORD(param) = param->CallData2;
  Start((s32)param, 0);
}

// 0x229b890
static s32 ExitLmap(void) {
  ShutDown();
  if (!gLMapCampMcLoadEnd)
    return 0;
  mapRetuenFromLoad();
  return 0;
}

// 0x229b9c0
static bool CheckLmap(void) {
  return 0;
}

// 0x229b9d0
static void CallMahjon(DDS3_ADMINI_CALL flg, SequenceParameter *param) {
  ;
}

// 0x229b9e0
static s32 ExitMahjon(void) {
  return 0;
}

// 0x229b9f0
static bool CheckMahjon(void) {
  return 0;
}

// 0x229ba00
static void CallMorph(DDS3_ADMINI_CALL flg, SequenceParameter *param) {
  ;
}

// 0x229ba10
static s32 ExitMorph(void) {
  return 0;
}

// 0x229ba20
static bool CheckMorph(void) {
  return 0;
}

// 0x229ba30
static void CallCtnTest(DDS3_ADMINI_CALL flg, SequenceParameter *param) {
  ;
}

// 0x229ba40
static s32 ExitCtnTest(void) {
  return 0;
}

// 0x229ba50
static bool CheckCtnTest(void) {
  return 0;
}

// 0x229ba60
static void CallNameEntryTest(DDS3_ADMINI_CALL flg, SequenceParameter *param) {
  ;
}

// 0x229ba70
static s32 ExitNameEntryTest(void) {
  return 0;
}

// 0x229ba80
static bool CheckNameEntryTest(void) {
  return 0;
}

// 0x229ba90
static void CallNameEntry(DDS3_ADMINI_CALL flg, SequenceParameter *param) {
  ;
}

// 0x229baa0
static s32 ExitNameEntry(void) {
  return 0;
}

// 0x229bab0
static bool CheckNameEntry(void) {
  return 0;
}

// 0x229bac0
static void CallSEffect(DDS3_ADMINI_CALL flg, SequenceParameter *param) {
  ;
}

// 0x229bad0
static s32 ExitSEffect(void) {
  return 0;
}

// 0x229bae0
static bool CheckSEffect(void) {
  return 0;
}

// 0x229baf0
static void CallWater(DDS3_ADMINI_CALL flg, SequenceParameter *param) {
  ;
}

// 0x229bb00
static s32 ExitWater(void) {
  return 0;
}

// 0x229bb10
static bool CheckWater(void) {
  return 0;
}

// 0x229bb20
static void CallHanafudaTest(DDS3_ADMINI_CALL flg, SequenceParameter *param) {
  ;
}

// 0x229bb30
static s32 ExitHanafudaTest(void) {
  return 0;
}

// 0x229bb40
static bool CheckHanafudaTest(void) {
  return 0;
}

// 0x229bb50
static void CallGomaden(DDS3_ADMINI_CALL flg, SequenceParameter *param) {
  u32 CallData2;

  if (!param)
  {
    CallData2 = 1;
    goto LABEL_5;
  }
  CallData2 = param->CallData2;
LABEL_5:
  gohStartSequence(CallData2);
}

// 0x229bbe0
static s32 ExitGomaden(void) {
  gohStopSequence();
  return 0;
}

// 0x229bc60
static bool CheckGomaden(void) {
  return gohCheckSequence() != 0;
}

// 0x229bcc0
static void CallJimusyoTest(DDS3_ADMINI_CALL flg, SequenceParameter *param) {
  ;
}

// 0x229bcd0
static s32 ExitJimusyoTest(void) {
  return 0;
}

// 0x229bce0
static bool CheckJimusyoTest(void) {
  return 0;
}

// 0x229bcf0
static void CallStorySelect(DDS3_ADMINI_CALL flg, SequenceParameter *param) {
  ;
}

// 0x229bd00
static s32 ExitStorySelect(void) {
  return 0;
}

// 0x229bd10
static bool CheckStorySelect(void) {
  return 0;
}
