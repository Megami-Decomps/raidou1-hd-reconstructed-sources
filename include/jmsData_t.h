#pragma once
#include "types.h"

typedef enum {
    JMS_CAMP_INIT = 0,
    JMS_CAMP_START_WAIT = 1,
    JMS_CAMP_START = 2,
    JMS_CAMP_MAIN = 3,
    JMS_CAMP_END_WAIT = 4,
    JMS_CAMP_MCLOADWAIT = 5,
} JMS_CAMP;

typedef struct DlcItem_t DlcItem_t;
typedef struct dds3ModelHandle_t dds3ModelHandle_t;
typedef struct dds3ProcessID_t dds3ProcessID_t;
typedef struct jmsCyousaPanel_t jmsCyousaPanel_t;
typedef struct jmsData_t jmsData_t;
typedef struct jmsModelCursor_t jmsModelCursor_t;
typedef struct jmsSeqHandle_t jmsSeqHandle_t;
typedef struct jmsSeqUnit_t jmsSeqUnit_t;
typedef struct sdfIVector2_t sdfIVector2_t;
typedef struct sprHandle_t sprHandle_t;

struct DlcItem_t {
    s32 _ItemID;
    s32 _Count;
};

struct jmsData_t {
    s32 Flag;
    jmsSeqHandle_t *SeqHandle;
    jmsSeqUnit_t *pSeqUnit;
    dds3ProcessID_t *PmvPID;
    dds3ModelHandle_t *Model[3];
    s32 ModelIndex[3];
    sdfIVector2_t *ModelCursorPos[3];
    jmsModelCursor_t *ModelCursor;
    u8 *pScrData;
    s32 ScrReq;
    dds3ProcessID_t *ScrPID;
    u8 *pEvtScrData;
    dds3ProcessID_t *EvtScrPID;
    u8 *pEvt2ScrData;
    dds3ProcessID_t *Evt2ScrPID;
    s32 MenuFade;
    s32 ExitFlag;
    s32 ModelTableIndex;
    s32 ModelLoadCnt;
    s32 TalkIndex;
    u8 *pCyousaMsg;
    s32 CyousaFileIndex;
    s32 MahjanStat;
    s32 MahjanErr;
    s32 SaveStat;
    u8 *pMsgData;
    sprHandle_t *pSpr;
    jmsCyousaPanel_t *CyousaPanel;
    s32 BgmNo;
    u8 *pBekkenScrData;
    dds3ProcessID_t *BekkenScrPID;
    s32 DBOOKstep;
    JMS_CAMP CAMPstep;
    void *jmsModel;
    u8 textChangeStep;
    s32 MjnFinishCnt;
    s32 cutNo;
    s32 jmsStepSave;
    s32 menuWait;
    bool menuFlag;
    DlcItem_t *dlcitem_pac1[20];
    DlcItem_t *dlcitem_pac2[20];
    DlcItem_t *dlcitem_pac3[20];
    s32 dlcState;
    s32 dlc_mes_No;
    s32 dlc_itemNum1;
    s32 dlc_itemNum2;
    s32 dlc_itemNum3;
};
