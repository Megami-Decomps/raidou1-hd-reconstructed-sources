#include "types.h"
#include "dds3kernelcore.h"
#include "dds3kerneldraw.h"
#include "dds3scenebasic.h"
#include "dds3worldbasic.h"
#include "eve.h"
#include "evt.h"
#include "fclmisc.h"
#include "itf.h"
#include "mdl.h"
#include "scr.h"
#include "sdfrand.h"

typedef struct datUnitWork_t datUnitWork_t;
typedef struct dds3ModelHandle_t dds3ModelHandle_t;
typedef struct dds3ProcessID_t dds3ProcessID_t;

static s8 gFclSignal[8];
static s32 *gFclVal;
s32 gMsgID;
s8 gMsgFlag;
static s8 gMsgInvFlag;
s32 gSelMsgNo;
s32 gSelMsgPos;
s32 gLastSelMsgPos;
static s16 gSelCancelNum;

bool MsgWndActiveSelf(s32 i);

// 0x1b3d4b0
s32 fclEncycRegist(datUnitWork_t *punit, s32 overwrite) {
  return -1;
}

// 0x1b3d4c0
s32 fclSetModelLight(char *pKeyWord, dds3ModelHandle_t *Model) {
  dds3Basic_t *ControlScene;
  dds3Basic_t *v8;
  void *workdata;
  sdf3DLightParallelPacket_t *monitor;

  ControlScene = dds3GetControlScene();
  v8 = dds3SceneBasicSearchNameAndType(ControlScene, 9u, pKeyWord);
  if (!v8)
    return (s32)v8;
  workdata = v8->workdata;
  monitor = workdata[5].monitor;
  mdlSetLight(Model, monitor);
  LODWORD(v8) = 1;
  return (s32)v8;
}

// 0x1b3d650
void fclLoadStage(u32 MajorNo, u32 MinorNo) {
  u32 v5;
  dds3Basic_t *scene;

  scene = dds3GetControlScene();
  v5 = MinorNo + (MajorNo << 16);
  if (dds3GetMapNo(scene) == (u64)v5)
    return;
  evtLoadMap(MajorNo, MinorNo);
}

// 0x1b3d770
void fclFilterOFF(void) {
  dds3SetBlur(0, 0, 0);
  _Off(MultiBlur, 0);
  _Off(DistBlur, 0);
  dds3FilterClear();
  (Blur->klass->vtable._5_OFF.methodPtr)(Blur, Blur->klass->vtable._5_OFF.method);
  (PartialMultiBlur->klass->vtable._5_OFF.methodPtr)(PartialMultiBlur, PartialMultiBlur->klass->vtable._5_OFF.method);
  (PartialMultiFilter->klass->vtable._5_OFF.methodPtr)(PartialMultiFilter, PartialMultiFilter->klass->vtable._5_OFF.method);
  (DistortionBlur->klass->vtable._5_OFF.methodPtr)(DistortionBlur, DistortionBlur->klass->vtable._5_OFF.method);
  (Filter->klass->vtable._5_OFF.methodPtr)(Filter, Filter->klass->vtable._5_OFF.method);
}

// 0x1b3d8e0
void fclFreeStage(void) {
  FIELD_CLS();
  fclFilterOFF();
}

// 0x1b3d960
void fclInitPanelPos(s32 X, s32 Y, u32 Z, u16 W, u16 H, s32 Work, void *pPanelPos) {
  pPanelPos->X = X;
  pPanelPos->Y = Y;
  pPanelPos->Z = Z;
  pPanelPos->W = W;
  pPanelPos->H = H;
  pPanelPos->Work = Work;
}

// 0x1b3d980
void fclScriptForcedEnd(dds3ProcessID_t *PID) {
  dds3ProcessID_t *id;

  id = PID;
  if (PID)
  {
    if (dds3GetProcessStat(id))
    {
      dds3KillProcess(id, 0);
    }
  }
}

// 0x1b3da20
dds3ProcessID_t *fclScriptStart(void *pScriptData, s32 StartNo, dds3ProcessID_t *pPID) {
  dds3ProcessID_t *v7;
  u8 *Interface;
  dds3ProcessID_t *started;
  dds3ProcessID_t *id;

  v7 = Allocate(dds3ProcessID_t);
  _ctor(v7, 0);
  if (!pPID)
    goto LABEL_8;
  id = pPID;
  goto LABEL_7;
LABEL_8:
  goto LABEL_9;
LABEL_7:
  if (!dds3GetProcessStat(id))
    goto LABEL_8;
  dds3KillProcess(id, 0);
LABEL_9:
  if (!pScriptData)
  {
    Interface = 0;
    goto LABEL_20;
  }
  Interface = QueryInterface(pScriptData, byte);
LABEL_20:
  started = scrStartScript2(2000, Interface, StartNo, 1);
  gFclSignal[0] = 0;
  return started;
}

// 0x1b3dcd0
s32 fclSort8u(void *op1, void *op2) {
  Il2CppObject *v4;
  Il2CppObject *v5;
  Il2CppClass ***v6;
  u32 klass_low;
  u32 v8;
  bool v9;
  s32 v10;

  v4 = op1;
  if (!v4)
    goto LABEL_14;
  v5 = v4;
  v6 = off_4EE5828;
  if (v4->klass->_1.element_class != *((Il2CppClass **)*off_4EE5828 + 8))
    goto LABEL_15;
  op1 = Unbox(v4);
  if (!op2)
  {
LABEL_14:
    v5 = (loc_3BDC60)(op1, op2);
LABEL_15:
  }
  klass_low = LOBYTE(op1->klass);
  v8 = *(u8 *)Unbox(op2);
  v9 = klass_low > v8;
  if (klass_low >= v8)
    v10 = 0;
  else
    v10 = -1;
  if (v9)
    return 1;
  else
    return v10;
}

// 0x1b3dd90
s32 fclReplaceBuf8u(u8 *pBuf, s32 BufSize, u8 TargetVal) {
  s32 v4;
  s64 v5;
  u8 *m_Items;
  s32 v7;
  char *v8;

  if (BufSize < 1)
    return 0;
  v4 = 0;
  v5 = BufSize;
  m_Items = pBuf;
  do
  {
    v7 = *m_Items;
    if (v7 != TargetVal)
    {
      v8 = (char *)pBuf + v4++;
      *m_Items = 0;
      v8[32] = v7;
    }
    ++m_Items;
    --v5;
  }
  while (v5);
  return v4;
}

// 0x1b3ddf0
void fclShuffleBuf8u(u8 *pBuf, s32 BufSize, s32 ShuffleCount) {
  s32 v4;
  u8 *m_Items;
  u32 *v7;
  u32 v8;
  u32 v9;
  s32 v10;
  s32 v11;
  s32 v12;
  s64 v13;
  s64 v14;
  u32 *v;
  u32 v18;
  s32 v19;
  u32 v20;
  s32 v21;
  s32 v22;

  if (ShuffleCount >= 1)
  {
    v4 = ShuffleCount;
    m_Items = pBuf;
    do
    {
      v = sdfDefaultRandCB->v;
      v18 = v[0];
      v19 = *(u64 *)v >> 30;
      v20 = v[2];
      v21 = *(u64 *)&v[2] >> 31;
      v[2] = v[1];
      v[3] = v20;
      v22 = v21 ^ v19;
      v[0] = v21 ^ v19;
      v[1] = v18;
      --v4;
      v7 = sdfDefaultRandCB->v;
      v8 = v7[0];
      v9 = v7[2];
      v10 = *(u64 *)v7 >> 30;
      v11 = *(u64 *)&v7[2] >> 31;
      v7[2] = v7[1];
      v7[3] = v9;
      v12 = v11 ^ v10;
      v7[0] = v12;
      v7[1] = v8;
      v13 = v22 % BufSize;
      v14 = v12 % BufSize;
      LOBYTE(v8) = m_Items[v13];
      m_Items[v13] = m_Items[v14];
      m_Items[v14] = v8;
    }
    while (v4);
  }
}

// 0x1b3dfb0
void fclLoadMessageData(s8 pFileName, void *pMsg) {
  ;
}

// 0x1b3dfc0
void fclFreeMessageData(void *pMsg) {
  ;
}

// 0x1b3a8e0
s32 fclInitMessage(void *pData) {
  s32 v5;

  if ((gMsgID & 0x80000000) == 0)
    return 0;
  v5 = itfMesMngInitialize(pData, 0, 0);
  gMsgID = v5;
  itfMesMngChangeWindowType(v5, 2, 0);
  return 1;
}

// 0x1b3dfd0
s32 fclChangeMessageWindowAlpha(u32 Alpha) {
  if ((gMsgID & 0x80000000) == 0)
  {
    itfMesMngChangeWindowType(gMsgID, 0, Alpha);
    return 1;
  }
  return 0;
}

// 0x1b3e0d0
void fclMassageWindowAlphaClear(void) {
  itfMesWinAlphaClear();
}

// 0x1b3e140
f32 fclGetMessageWindowAlpha(void) {
  return itfGetMesWinAlpha();
}

// 0x1b3e1b0
s32 fclGetMsgId(void) {
  return gMsgID;
}

// 0x1b3e230
void fclSetPageUpdateCallBack(void *_func) {
  if ((gMsgID & 0x80000000) == 0)
    goto LABEL_4;
  return;
  if ((gMsgID & 0x80000000) == 0)
  {
LABEL_4:
    itfSetPageUpdateCallBack(gMsgID, func);
    return;
  }
}

// 0x1b3c1f0
s32 fclStartMessage(s32 MsgNo) {
  if ((gMsgID & 0x80000000) == 0)
  {
    itfMesMngMarkBitStat(gMsgID, 0x200000u);
    itfMesMngRequestMessage(gMsgID, MsgNo, 0, 0, 0);
    itfMesMngSetSelPhase(gMsgID, -1);
    gMsgFlag = 1;
    return 1;
  }
  return 0;
}

// 0x1b3c330
s32 fclStartSelMessage(s32 SelMsgNo) {
  if (gMsgID < 0)
    return 0;
  gSelMsgNo = SelMsgNo;
  gLastSelMsgPos = fclGetSelMessagePos();
  return 1;
}

// 0x1b3c400
void fclSetSelMessagePos(s32 SelPos) {
  if (gMsgID < 0)
    return;
  gSelMsgPos = SelPos;
}

// 0x1b3e320
s32 fclGetDefaultSelMessagePos(void) {
  return gSelMsgPos;
}

// 0x1b3c900
s32 fclGetSelMessagePos(void) {
  if ((gMsgID & 0x80000000) != 0)
    return -1;
  return itfMesMngGetSelectNo(gMsgID);
}

// 0x1b3e3a0
s32 fclGetLastSelMessagePos(void) {
  return gLastSelMsgPos;
}

// 0x1b3e420
void fclSetSelCancelPos(s16 SelPos) {
  if (gMsgID < 0)
    return;
  gSelCancelNum = SelPos;
}

// 0x1b3e4e0
s32 fclEndMessageEx(s32 ClsMode) {
  s32 v9;
  s32 v13;

  if ((gMsgID & 0x80000000) == 0)
  {
    itfMesMngSetPhase(gMsgID, 0);
    if (!ClsMode)
    {
      goto LABEL_8;
    }
    v13 = gMsgID;
    itfMesMngMsgWndCls(v13);
LABEL_8:
    v9 = gMsgID;
    itfMesMngRequestMessageRelease(v9, 0);
    fclSetMessageInvalid(1);
    gMsgFlag = 0;
    return 1;
  }
  return 0;
}

// 0x1b3e6c0
s32 fclEndMessage(void) {
  return fclEndMessageEx(1);
}

// 0x1b3ad70
s32 fclDestroyMessage(void) {
  if ((gMsgID & 0x80000000) == 0)
  {
    itfMesMngRelease(gMsgID);
    gMsgID = -1;
    *(u16 *)&gMsgFlag = 0;
    return 1;
  }
  return 0;
}

// 0x1b3bc40
s32 fclChkMessage(void) {
  if ((gMsgID & 0x80000000) != 0)
    return 0;
  if (gMsgInvFlag != 1)
    goto LABEL_15;
  if (gMsgFlag != 2)
    goto LABEL_15;
  return 0;
LABEL_15:
  if (fclChkMessageDisp())
    return 1;
  return gMsgFlag;
}

// 0x1b3c7c0
s32 fclChkSelMessage(void) {
  if ((gMsgID & 0x80000000) != 0)
    return 0;
  if (itfMesMngGetSelPhase(gMsgID) < 0)
    return 0;
  gLastSelMsgPos = fclGetSelMessagePos();
  return 1;
}

// 0x1b3e850
void fclDelSelMessage(void) {
  if ((gMsgID & 0x80000000) == 0)
    goto LABEL_4;
  return;
  if ((gMsgID & 0x80000000) == 0)
  {
LABEL_4:
    itfMesMngRequestSelectRelease(gMsgID);
    return;
  }
}

// 0x1b3c4c0
void fclUpdateMessageEx(s32 ClsMode) {
  s32 v9;

  if (gMsgID < 0)
    return;
  if (gMsgFlag == 3)
  {
    fclEndMessageEx(ClsMode);
    return;
  }
  if (gMsgFlag != 2)
  {
    if (gMsgFlag != 1)
      return;
    if ((itfMesMngGetPhase(gMsgID) & 0x80000000) == 0)
      return;
    gMsgFlag = 2;
    return;
  }
  if ((gSelMsgNo & 0x80000000) == 0)
  {
    scrEventSkipEnd(1, 0);
    v9 = gMsgID;
    itfMesMngSetSelectDefKey(v9, 3, 1);
    itfMesMngSetSelect(gMsgID, gSelMsgPos, gSelCancelNum);
    itfMesMngRequestSelect(gMsgID, gSelMsgNo);
    gSelMsgNo = -1;
    gSelCancelNum = -1;
  }
  if (!gMsgInvFlag)
  {
    if (!fclChkSelMessage())
    {
      gMsgFlag = 3;
      scrEventSkipRestart();
    }
  }
}

// 0x1b3e950
void fclUpdateMessage(void) {
  fclUpdateMessageEx(1);
}

// 0x1b3e9c0
void fclSetMessageVar(s32 Index, char *pStr) {
  itfMesMngSetVarImmediate(gMsgID, Index, pStr);
}

// 0x1b3ea90
s32 fclChkMessageInvalid(void) {
  return gMsgInvFlag;
}

// 0x1b3b5c0
void fclSetMessageInvalid(s32 Mode) {
  s32 v7;
  s32 v9;

  if (Mode)
  {
    itfMesMngClearBitStat(gMsgID, 0x800000u);
    itfMesMngClearBitStat(gMsgID, 0x100000u);
    v7 = gMsgID;
    gMsgInvFlag = 0;
    itfMesMngSetPhase(v7, 1);
    gMsgFlag = 1;
    return;
  }
  v9 = gMsgID;
  itfMesMngMarkBitStat(v9, 0x800000u);
  itfMesMngMarkBitStat(gMsgID, 0x100000u);
  gMsgInvFlag = 1;
}

// 0x1b3eb10
void fclSetMessagePos(s32 X, s32 Y) {
  s32 v9;

  v9 = 8 * Y;
  itfMesMngSetMesPosition(gMsgID, 16 * X, v9);
  itfMesMngSetOffsetY1(gMsgID, v9 - 2808);
}

// 0x1b3ec00
s32 fclChkMessageDraw(void) {
  if ((gMsgID & 0x80000000) == 0)
  {
    return itfMesMngGetStat(gMsgID) != 0;
  }
  return 0;
}

// 0x1b3e730
s32 fclChkMessageDisp(void) {
  s32 PrefMesWin;
  s32 v5;

  PrefMesWin = itfGetPrefMesWin();
  if (MsgWndActiveSelf(PrefMesWin))
    goto LABEL_4;
  return 0;
  if (MsgWndActiveSelf(v5))
  {
LABEL_4:
    return itfGetMesWinAlpha() > 0.0;
  }
  return 0;
}

// 0x1b3dc60
void fclClearSignal(s32 Idx) {
  gFclSignal[Idx] = 0;
}

// 0x1b3ed00
s32 fclChkSignal(s32 Idx) {
  return gFclSignal[Idx] != 0;
}

// 0x1b3ed80
s32 fclSetVal(s32 Idx, s32 Val) {
  if (Idx > 15)
    return 0;
  gFclVal[Idx] = Val;
  return 1;
}

// 0x1b3ee20
s32 fclChkVal(s32 Idx) {
  s32 v4;

  if (Idx >= 15)
    v4 = 15;
  else
    v4 = Idx;
  return gFclVal[v4];
}

// 0x1b3eea0
s32 fclSignal(void) {
  s32 IntPara;

  IntPara = scrGetIntPara(0);
  gFclSignal[IntPara] = 1;
  return 1;
}

// 0x1b3ef40
s32 fclGetVal(void) {
  s32 IntPara;
  s32 v2;
  s32 v4;

  IntPara = scrGetIntPara(0);
  if (IntPara >= 15)
    v2 = 15;
  else
    v2 = IntPara;
  v4 = gFclVal[v2];
  scrSetIntReturnValue(v4);
  return 1;
}
