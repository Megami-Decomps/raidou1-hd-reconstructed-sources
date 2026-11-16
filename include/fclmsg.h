#pragma once
#include "types.h"

typedef struct dds3ProcessID_t dds3ProcessID_t;

extern dds3ProcessID_t *g_mainPID;

void fclLoadDataEx(dds3ProcessID_t *PID, char *filename, char *assetName, bool assetUnload);
void fclLoadData(char *filename, char *assetName, bool assetUnload);
void fclLinkDataEx(dds3ProcessID_t *PID, u8 *a_pDatMsg);
void fclLinkData(u8 *a_pDatMsg);
void fclResetEx(dds3ProcessID_t *PID);
bool fclStart(dds3ProcessID_t *PID, s32 a_type, s32 a_no, bool skip_enable);
void fclSetSelInvild(dds3ProcessID_t *PID, bool _flag);
void fclSelMesSpeedMax(dds3ProcessID_t *PID, bool _flag);
void fclSetSelMes(dds3ProcessID_t *PID, s32 _selMes);
void fclSkipNoEnd(dds3ProcessID_t *PID, bool _flag);
void fclGetLogStop(dds3ProcessID_t *PID, bool _flag);
void fclDirectCallMesClear(void);
bool fclStart1(s32 a_no, bool skip_enable);
bool fclStart2(s32 a_no, bool skip_enable, bool _invild);
s32 fclGetSelect(void);
void fclSetMessagePosEx(dds3ProcessID_t *PID, u8 a_pos);
void SetMessagePos(u8 a_pos);
void fclSetClsModeEx(dds3ProcessID_t *PID, s32 a_mode);
void fclSetClsMode(s32 a_mode);
bool ChkMessage(void *wk);
s32 fclUpdateEx(dds3ProcessID_t *PID);
s32 Update(void);
void Create(void);
dds3ProcessID_t *getID(void);
void fclFlagFalse(dds3ProcessID_t *PID);
void Delete(void);
bool fclCheck(void);
dds3ProcessID_t *fclProcessStart(void);
void fclProcessEnd(dds3ProcessID_t *PID);
bool fclProcessCheck(dds3ProcessID_t *PID);
