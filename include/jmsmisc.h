#pragma once
#include "types.h"
#include "kernel.h"

typedef struct dds3ProcessID_t dds3ProcessID_t;
typedef struct jmsSeqHandle_t jmsSeqHandle_t;
typedef struct jmsSeqUnit_t jmsSeqUnit_t;

extern char *szSeqNameNull;

void jmsInitSeqHandle(jmsSeqHandle_t *pSeqHandle);
void jmsSeqDestroyAll(jmsSeqHandle_t *pSeqHandle, dds3ProcessID_t *ID);
s32 jmsChkSeqChange(jmsSeqUnit_t *pSeqUnit);
dds3ProcessFunc_t jmsSeqChange(jmsSeqHandle_t *pSeqHandle, jmsSeqUnit_t *pSeqUnit, s32 Mode, dds3ProcessID_t *ID);
s32 jmsSeqChkLast(jmsSeqHandle_t *pSeqHandle, jmsSeqUnit_t *pSeqUnit);
void jmsSeqJump(jmsSeqUnit_t *pCurrentSeqUnit, jmsSeqUnit_t *pSeqUnit);
void jmsSeqJumpAndFree(jmsSeqUnit_t *pCurrentSeqUnit, jmsSeqUnit_t *pSeqUnit);
void jmsSeqJumpAndPop(jmsSeqUnit_t **pCurrentSeqUnit, jmsSeqUnit_t *pSeqUnit);
void jmsSeqReturn(jmsSeqHandle_t *pSeqHandle, jmsSeqUnit_t *pCurrentSeqUnit);
u32 jmsChkCommonInput(u32 ControlBit);
void jmsPageControlEx(void *pScrollBar, void *pCmdMenu, s32 *pPad);
void jmsPageControl(void *pCmdMenu, s32 pPad);
void jmsPlaySE(u32 Type, u32 PadBit, void *pCmdList);
