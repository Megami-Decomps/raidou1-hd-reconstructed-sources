#pragma once
#include "types.h"

typedef struct datUnitWork_t datUnitWork_t;
typedef struct dds3ModelHandle_t dds3ModelHandle_t;
typedef struct dds3ProcessID_t dds3ProcessID_t;

extern s32 gMsgID;
extern s8 gMsgFlag;
extern s32 gLastSelMsgPos;
extern s32 gSelMsgNo;
extern s32 gSelMsgPos;

s32 fclEncycRegist(datUnitWork_t *punit, s32 overwrite);
s32 fclSetModelLight(char *pKeyWord, dds3ModelHandle_t *Model);
void fclLoadStage(u32 MajorNo, u32 MinorNo);
void fclFilterOFF(void);
void fclFreeStage(void);
void fclInitPanelPos(s32 X, s32 Y, u32 Z, u16 W, u16 H, s32 Work, void *pPanelPos);
void fclScriptForcedEnd(dds3ProcessID_t *PID);
dds3ProcessID_t *fclScriptStart(void *pScriptData, s32 StartNo, dds3ProcessID_t *pPID);
s32 fclSort8u(void *op1, void *op2);
s32 fclReplaceBuf8u(u8 *pBuf, s32 BufSize, u8 TargetVal);
void fclShuffleBuf8u(u8 *pBuf, s32 BufSize, s32 ShuffleCount);
void fclLoadMessageData(s8 pFileName, void *pMsg);
void fclFreeMessageData(void *pMsg);
s32 fclInitMessage(void *pData);
s32 fclChangeMessageWindowAlpha(u32 Alpha);
void fclMassageWindowAlphaClear(void);
f32 fclGetMessageWindowAlpha(void);
s32 fclGetMsgId(void);
void fclSetPageUpdateCallBack(void *_func);
s32 fclStartMessage(s32 MsgNo);
s32 fclStartSelMessage(s32 SelMsgNo);
void fclSetSelMessagePos(s32 SelPos);
s32 fclGetDefaultSelMessagePos(void);
s32 fclGetSelMessagePos(void);
s32 fclGetLastSelMessagePos(void);
void fclSetSelCancelPos(s16 SelPos);
s32 fclEndMessageEx(s32 ClsMode);
s32 fclEndMessage(void);
s32 fclDestroyMessage(void);
s32 fclChkMessage(void);
s32 fclChkSelMessage(void);
void fclDelSelMessage(void);
void fclUpdateMessageEx(s32 ClsMode);
void fclUpdateMessage(void);
void fclSetMessageVar(s32 Index, char *pStr);
s32 fclChkMessageInvalid(void);
void fclSetMessageInvalid(s32 Mode);
void fclSetMessagePos(s32 X, s32 Y);
s32 fclChkMessageDraw(void);
s32 fclChkMessageDisp(void);
void fclClearSignal(s32 Idx);
s32 fclChkSignal(s32 Idx);
s32 fclSetVal(s32 Idx, s32 Val);
s32 fclChkVal(s32 Idx);
s32 fclSignal(void);
s32 fclGetVal(void);
