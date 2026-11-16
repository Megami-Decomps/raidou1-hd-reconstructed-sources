#pragma once
#include "types.h"
#include "kernel.h"

typedef struct SequenceParameter SequenceParameter;
typedef struct dds3ProcessID_t dds3ProcessID_t;
typedef struct fileLoadAsset_Request fileLoadAsset_Request;
typedef struct jmsData_t jmsData_t;
typedef struct sdf3DLightParallelPacket_t sdf3DLightParallelPacket_t;
typedef struct sprHandle_t sprHandle_t;

extern dds3ProcessID_t *GlobalPID;
extern char *s_szModelName;
extern s32 gCallFromSubMenu;
extern fileLoadAsset_Request *uiReq;
extern sdf3DLightParallelPacket_t *g_pLightPacket;
extern char *jms_asset_name;

sprHandle_t *jmsGetSpriteHandle(void);
s32 jmsGetModelDefaultMotion(s32 Index, jmsData_t *pData);
s32 jmsModelLoad(jmsData_t *pData);
void jmsModelFree(jmsData_t *pData);
void jmsModelMakeLightPacket(s32 setModel);
void jmsLoadBgModel(dds3ProcessID_t *ParentPID, jmsData_t *pData);
s32 jmsCheckBgModel(jmsData_t *pData);
void jmsFreeBgModel(jmsData_t *pData);
void jmsSetBgDisp(bool bo);
void jmsStartEtcProcess(dds3ProcessID_t *PID);
void jmsAddTalkMenu(jmsData_t *pData);
s32 jmsBgmLoad(jmsData_t *pData);
s32 jmsBgmPlay(jmsData_t *pData);
void jmsLoadLocalizeText(void);
dds3ProcessFunc_t jmsLoad2ndProcess(dds3ProcessID_t *PID);
bool jmsCheckUIReq(void);
dds3ProcessFunc_t jmsEventScrProcess(dds3ProcessID_t *PID);
dds3ProcessFunc_t jmsLoad0Process(dds3ProcessID_t *PID);
dds3ProcessFunc_t jmsLoad1stProcess(dds3ProcessID_t *PID);
jmsData_t *Init(void);
void jmsDestroy(dds3ProcessID_t *PID);
dds3ProcessID_t *jmsProcessStart(SequenceParameter *param);
void jmsProcessEnd(void);
void jmsReturnReadFlagData(void);
s32 jmsProcessCheck(void);
dds3ProcessID_t *jmsDebugProcessStart(SequenceParameter *param);
void jmsDebugProcessEnd(void);
s32 jmsDebugProcessCheck(void);
s32 jmsScrCmd_CALL_JIMUSYO(void);
s32 jmsScrCmd_JMS_MOTION(void);
s32 jmsScrCmd_JMS_GET_INDEX(void);
s32 jmsScrCmd_JMS_EXIT(void);
s32 jmsScrCmd_JMS_SET_MODE(void);
void jmsSetUI(void *ui);
bool jmsGetUI(void);
bool jmsCeckUIDISP(void);
