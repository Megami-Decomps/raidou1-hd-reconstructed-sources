#pragma once
#include "types.h"
#include "kernel.h"

typedef enum {
    STAFF_FLAG_NONE = 0,
    STAFF_FLAG_LOAD_NOW = 1,
    STAFF_FLAG_LOAD_END = 2,
    STAFF_FLAG_SPR_LOAD_NOW = 4,
    STAFF_FLAG_SPR_LOAD_END = 8,
    STAFF_FLAG_BG_LOAD_NOW = 16,
    STAFF_FLAG_BG_LOAD_END = 32,
    STAFF_FLAG_END_START = 64,
    STAFF_FLAG_END_NOW = 128,
    STAFF_FLAG_BGM_LOAD_NOW = 256,
    STAFF_FLAG_BGM_LOAD_END = 512,
} STAFF_FLAG;

typedef enum {
    FADE_TYPE_FIRST = 0,
    FADE_TYPE_WAIT = 1,
    FADE_TYPE_FADEIN = 2,
    FADE_TYPE_FADEOUT = 3,
    FADE_TYPE_XFADE = 4,
} FADE_TYPE;

typedef struct StaffCredit_t StaffCredit_t;
typedef struct Staff_t Staff_t;
typedef struct Time_t Time_t;
typedef struct dds3ProcessID_t dds3ProcessID_t;
typedef struct staffData_t staffData_t;
typedef struct staffSeqHandle_t staffSeqHandle_t;
typedef struct staffSeqUnit_t staffSeqUnit_t;

typedef s32 (*staffInt32Delegate)(dds3ProcessID_t *ID);

struct staffData_t {
    STAFF_FLAG Flag;
    staffSeqHandle_t *SeqHandle;
    staffSeqHandle_t *pSeqUnit;
    dds3ProcessID_t *PmvPID;
    dds3ProcessID_t *drawPID;
    Time_t *time;
    Staff_t *staff;
    s32 CreditCount;
    s32 Nomber;
    s32 Count;
    s32 FadeCount;
    f32 ObjAlhaIn;
    f32 ObjAlhaOut;
    char *CaptionText;
    char *NameText;
};

struct Time_t {
    f32 WaitTimer;
    FADE_TYPE fade;
    s32 CutNomber;
};

struct Staff_t {
    char *left_caption;
    char *rigth_name;
};

struct StaffCredit_t {
    char *caption;
    char *name1;
    char *name2;
    s32 dispControlFlg;
};

struct staffSeqUnit_t {
    s64 Stat;
    staffInt32Delegate pInit;
    staffInt32Delegate pDestroy;
    dds3ProcessFunc_t pCalc;
    dds3ProcessFunc_t pDraw;
    dds3ProcessFunc_t pUpdate;
    staffInt32Delegate pCheck;
};

struct staffSeqHandle_t {
    s32 UnnitCnt;
    staffSeqUnit_t *pUnit[16];
    staffSeqUnit_t *pLastSeqUnit[2];
};

extern char *staff_scene_name;
extern bool first;
extern Time_t *stafftime;
extern Staff_t *StaffData;
extern StaffCredit_t *StaffData2;

void LoadStaffUI(staffData_t *pData);
s32 CheckStaffUi(staffData_t *pData);
void FreeStaffUi(staffData_t *pData);
void UnloadStaffUI(void);
s32 GetStaffRollTableMax(void);
void NewStaffDataLoad(dds3ProcessID_t *PID);
dds3ProcessFunc_t CutChange(Time_t *pTime, dds3ProcessID_t *PID);
void StaffDataTextLoad(Staff_t *staff, dds3ProcessID_t *PID);
void StaffRollOn(dds3ProcessID_t *PID);
void ProcessStart(void);
void ProcessEnd(void);
bool ProcessCheck(void);
s32 GetTableMax(void);
void StaffTimeJumpAndFree(Time_t *pCurrenTime, Time_t *pTime);
s32 GetStaffTableMax(void);
