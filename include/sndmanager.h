#pragma once
#include "types.h"

extern s32 PublicPan;
extern s32 PublicSE;

void sndInit(void);
bool sndIsCommonSMG(s32 smg_no);
s32 sndGetNumOfReq(void);
bool sndVoicePlayFile(char *pName, void *source);
bool sndIsVoicePlayFile(char *pName);
void sndVoiceSel(s32 sel);
void sndVoicePlayId(s32 id);
void sndVoiceGetFileName(s32 id, s32 idx, char **ptr);
s32 sndVoiceGetFileChk(s32 id, s32 idx);
void sndVoiceStop(void *source);
bool sndVoiceStatus(void *source);
void sndVoicePause(void);
s32 sndVoiceGetTime(void);
