#pragma once
#include "types.h"
#include "CutInType.h"
#include "EVT_PICTURE_TYPE.h"
#include "callbackDelegate.h"
#include "kernel.h"

typedef struct dds3ProcessID_t dds3ProcessID_t;
typedef struct evtPictureProcessData_t evtPictureProcessData_t;
typedef struct fileHandle_t fileHandle_t;

extern s32 msg_logFlag;
extern DDS3_OT gPictureOtEx;

void evtPictureSetUI(void *obj);
bool *evtPictureGameObjDisp(bool disp, bool *act);
void evtPictureDrawOn(dds3ProcessID_t *id);
void evtPictureDrawOff(dds3ProcessID_t *id);
void KillProcess(dds3ProcessID_t *id);
void evtPictureOtEx(DDS3_OT ot);
void evtPictureAchievementUnlock(evtPictureProcessData_t *data);
void evtPictureSetDrawPosOffSet(dds3ProcessID_t *id, f32 ox, f32 oy);
dds3ProcessID_t *StartProcess(DDS3_PRIORITY priority, char *texpath);
dds3ProcessID_t *evtPictureStartProcess2(DDS3_PRIORITY priority, u8 *texdata);
fileHandle_t *evtPictureLoadStartTexFile(char *pFileName, char *pBundle, evtPictureProcessData_t *data);
bool evtPictureLoadCheckProcess(dds3ProcessID_t *id);
s32 evtPictureSetDrawPos(dds3ProcessID_t *id, s32 x, s32 y);
s32 evtPictureSetDrawCol(dds3ProcessID_t *id, s32 r, s32 g, s32 b, s32 a);
s32 evtPictureSetEndProcess(dds3ProcessID_t *id);
dds3ProcessID_t *evtPictureStartProcess3(DDS3_PRIORITY priority, char *texpath, char *bname);
dds3ProcessID_t *evtPictureStartProcess4(s32 x, s32 y, DDS3_PRIORITY priority, s32 start, s32 end, s32 *p_now, EVT_PICTURE_TYPE type, u32 uid, callbackDelegate callback, char *texpath, char *bname, s32 ui_mode, CutInType cutInType);
void evtPictureApeGouto(void);
void evtPictureExtGouto(void);
s32 evtPictureUseGoutoAnim(void);
