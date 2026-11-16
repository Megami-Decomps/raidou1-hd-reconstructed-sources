#pragma once
#include "types.h"
#include "kernel.h"

typedef struct dds3ProcessID_t dds3ProcessID_t;

extern char *GuideName;
extern s32 GuideNowAnm;

void ButtonGuideInit(void);
void GuideObjSet(void *GuideObj, bool SetLineHelp);
void GuideObjClr(void);
dds3ProcessFunc_t ButtonGuideMain(dds3ProcessID_t *id);
void ButtonGuideDispSet(char *name, bool timer, s32 waitTimer);
void ButtonAliasGuideDispSet(char *name, bool timer, s32 waitTimer);
void ButtonGuideTimerReset(void);
void ButtonGuideDispOn(void);
void ButtonGuideDispIn(void);
void ButtonGuideDispOff(void);
void ButtonGuideDispOut(void);
void CheckPlayerCtrl(void);
bool ButtonIsGuideButtonHit(void);
void SetTypeClose(bool flg);
void ButtonGuideDispDel(void);
char *GuideNameGet(void);
void GuideDispStop(bool disp);
void ButtonLineHelpSet(void *HelpObj, bool setup);
void ButtonLineHelpDispSet(bool setup);
void ButtonLineHelpTextSetNoConvert(char *newText, u32 color);
char *ButtonLineHelpTextSet(char *text, bool mark, bool tag, u32 color, bool _textSet);
char *ButtonLineHelpAddTextSet(char *_addTextLabel, bool tag, s32 _empty, bool _textSet);
void ButtonTmpGuideObjSet(void *GuideObj, bool SetLineHelp);
void ButtonTmpLineHelpSet(void *HelpObj, bool setup);
void ButtonTmpLineHelpDispSet(bool setup);
void ButtonTmpGuideDispOff(void);
void ButtonTmpGuideObjClr(void);
dds3ProcessFunc_t ButtonTmpGuideMain(dds3ProcessID_t *id);
void ButtonShutDown(dds3ProcessID_t *id);
void ButtonTmpGuideDispSet(char *name, bool timer, s32 waitTimer);
void ButtonTmpGuideDispIn(void);
void ButtonTmpGuideDispOut(void);
void ButtonTmpGuideTimerReset(void);
void ButtonTmpGuideDispOn(void);
void *ButtonGetConfigToSetSpr(s32 setSpr, s32 org_setSpr, s32 setSprSub, s32 org_setSprSub);
