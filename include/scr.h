#pragma once
#include "types.h"
#include "kernel.h"

#define VARIABLE_MAX 256
#define STACK_SIZE 28
#define USE_STACK 27
#define REG_STACK 27

typedef enum {
    SCR_DATATYPE_PROCTABLE = 0,
    SCR_DATATYPE_LABELTABLE = 1,
    SCR_DATATYPE_SCRDATA = 2,
    SCR_DATATYPE_MESSAGE = 3,
    SCR_DATATYPE_STRINGS = 4,
    SCR_DATATYPE_MAX = 5,
} SCR_DATATYPE;

typedef enum {
    CODE_TYPE_PUSHI = 0,
    CODE_TYPE_PUSHF = 1,
    CODE_TYPE_PUSHIX = 2,
    CODE_TYPE_PUSHFX = 3,
    CODE_TYPE_PUSHREG = 4,
    CODE_TYPE_POPIX = 5,
    CODE_TYPE_POPFX = 6,
    CODE_TYPE_PROC = 7,
    CODE_TYPE_COMM = 8,
    CODE_TYPE_END = 9,
    CODE_TYPE_JUMP = 10,
    CODE_TYPE_CALL = 11,
    CODE_TYPE_RUN = 12,
    CODE_TYPE_GOTO = 13,
    CODE_TYPE_ADD = 14,
    CODE_TYPE_SUB = 15,
    CODE_TYPE_MUL = 16,
    CODE_TYPE_DIV = 17,
    CODE_TYPE_MINUS = 18,
    CODE_TYPE_NOT = 19,
    CODE_TYPE_OR = 20,
    CODE_TYPE_AND = 21,
    CODE_TYPE_EQ = 22,
    CODE_TYPE_NEQ = 23,
    CODE_TYPE_S = 24,
    CODE_TYPE_L = 25,
    CODE_TYPE_SE = 26,
    CODE_TYPE_LE = 27,
    CODE_TYPE_IF = 28,
    CODE_TYPE_PUSHIS = 29,
    CODE_TYPE_PUSHLIX = 30,
    CODE_TYPE_PUSHLFX = 31,
    CODE_TYPE_POPLIX = 32,
    CODE_TYPE_POPLFX = 33,
    CODE_TYPE_PUSHSTR = 34,
    CODE_TYPE_MAX = 35,
} CODE_TYPE;

typedef enum {
    CODE_RET_END = 0,
    CODE_RET_NEXT = 1,
    CODE_RET_SYNC = 2,
} CODE_RET;

typedef enum {
    SCR_RESULT_ERROR = 0,
    SCR_RESULT_CONTINUE = 1,
    SCR_RESULT_END = 2,
} SCR_RESULT;

typedef struct LOGDISP_PARAM LOGDISP_PARAM;
typedef struct NEW_MSGLOG NEW_MSGLOG;
typedef struct NEW_MSGLOG_FS NEW_MSGLOG_FS;
typedef struct SCRLOG SCRLOG;
typedef struct dds3ProcessID_t dds3ProcessID_t;
typedef struct instanceMes_tag instanceMes_tag;
typedef struct scrCode_t scrCode_t;
typedef struct scrCommandTable_t scrCommandTable_t;
typedef struct scrHandle_t scrHandle_t;
typedef struct scrHeader_t scrHeader_t;
typedef struct scrLabelTable_t scrLabelTable_t;
typedef struct scrProcTable_t scrProcTable_t;
typedef struct scrTypeTable_t scrTypeTable_t;

typedef s32 (*commDelegate)(void);

struct scrCommandTable_t {
    commDelegate comm;
    s32 paranum;
};

struct scrHeader_t {
    s8 FileType;
    s8 FileFormat;
    s16 UserID;
    s32 FileSize;
    u32 MagicCode;
    s32 ExpandSize;
    s32 TypeTableCount;
    s16 LocalIntCount;
    s16 LocalFloatCount;
    s32 Reserve2;
    s32 Reserve3;
};

struct scrTypeTable_t {
    s32 Type;
    s32 ItemSize;
    s32 ItemCount;
    s32 ItemAddress;
};

struct scrProcTable_t {
    char *Name;
    s32 CodeAddress;
    s32 Reserve1;
};

struct scrLabelTable_t {
    char *Name;
    s32 CodeAddress;
    s32 Reserve1;
};

struct scrCode_t {
    s32 im;
    f32 fm;
    s16 s0;
    s16 s1;
    s8 c0;
    s8 c1;
    s8 c2;
    s8 c3;
    dds3ProcessID_t *id;
    sdfVector4_t vec;
};

struct SCRLOG {
    s32 start;
    dds3ProcessID_t *pid;
    void *msglog;
    void *spklog;
    void *voicelog;
    s32 msg1st;
    s32 skip;
    s32 restart;
    bool is_field;
};

struct NEW_MSGLOG {
    s32 msglog_write_top;
    s32 msglog_write_page;
    s32 msglog_read_top;
    char *meslog_mesTag[30];
    char *meslog_spkTag[30];
    char *meslog_voiceTag[30];
    char *meslog_key[30];
    char *meslog_filename[30];
    s32 msglog_sel_result[30];
    char *gVarStr[30];
    s32 *gParam[30];
};

struct NEW_MSGLOG_FS {
    s32 msglog_write_top;
    s32 msglog_write_page;
    s32 msglog_read_top;
    u8 meslog_mesTag[15360];
    u8 meslog_spkTag[1920];
    u8 meslog_voiceTag[1920];
    u8 meslog_key[15360];
    u8 meslog_filename[15360];
    s32 msglog_sel_result[30];
    u8 gVarStr[30720];
    s32 gParam[240];
};

extern scrHandle_t *s_hNowpWork;

void scrLogInit(void);
void scrLogStart(dds3ProcessID_t *pid);
void scrLogSetId(dds3ProcessID_t *pid);
void scrLogSave(char *msg_text, char *spk_text, char *voice_text, void *tag_list, instanceMes_tag *pinst, void *sel_list, char *sel_text, char *mes_save, bool *add_flag);
void scrLogSaveSel(char *sel_text, bool flag, void *sel_list, char **mes_save, bool *add_flag);
void scrLogSelIDSave(LOGDISP_PARAM *logwk);
bool scrIsLogSave(void);
void *scrGetMsgLogList(void);
void *scrGetSpeakerLogList(void);
void *scrGetVoiceLogList(void);
s32 scrGetLogListCount(void);
SCRLOG *scrLogCheck(dds3ProcessID_t *pid);
void scrLogEnd(dds3ProcessID_t *pid);
void scrLogEndAll(void);
void scrLogFlgReset(void);
bool scrEventSkipChk(void);
bool scrIsEventSkip(dds3ProcessID_t *pid);
void scrEventSkipMsg1st(void);
void scrEndEventSkipMsg1st(void);
void scrEventSkipEnd(bool _restart, dds3ProcessID_t *pid);
void scrEventSkipRestart(void);
void scrEventSkipRestartFlagChange(void);
void scrNewLogSaveSelLabel(void *sel_label);
void scrNewLogSaveSel(s32 sel_result);
void scrLoadLocalizeTextSave(s32 wtop);
void scrLoadLocalizeMsgLog(void);
void scrRemoveLocalizeMsgLog(void);
void scrInitGlobalWork(void);
dds3ProcessID_t *scrStartScript3(s32 priority, char *asset_name, char *filename, s32 startproc, bool skip_enable);
scrHandle_t *scrRegistScript3(char *asset_name, char *filename);
dds3ProcessID_t *scrStartScript2(s32 priority, u8 *scrdata, s32 startproc, bool skip_enable);
scrHandle_t *scrRegistScript2(u8 *scrdata);
dds3ProcessID_t *scrStartScript1(s32 priority, scrHeader_t *header, scrTypeTable_t *typetable, scrProcTable_t *proctable, scrLabelTable_t *labeltable, scrCode_t *code, u8 *mesdata, u8 *stringdata, s32 startproc);
scrHandle_t *scrRegistScript1(scrHeader_t *header, scrTypeTable_t *typetable, scrProcTable_t *proctable, scrLabelTable_t *labeltable, scrCode_t *code, u8 *mesdata, u8 *stringdata);
void scrReleaseScript(scrHandle_t *h);
void scrAllReleaseScript(void);
s32 scrSetStartProc(scrHandle_t *h, s32 startproc);
scrHandle_t *scrSearchScriptName(char *scriptname);
s32 scrSearchProcedureName(u8 *scrdata, char *procname);
void scrSetUserData(dds3ProcessID_t *id, void *p);
void *scrGetUserData(dds3ProcessID_t *id);
s32 scrRunScript(scrHandle_t *h);
dds3ProcessFunc_t scrProcess(dds3ProcessID_t *id);
s32 scrGetScriptHandleCount(void);
void scrGetRunningScripts(void *scripts);
bool scrCheckScriptPlaying(void);
s32 scrTraceCode(scrHandle_t *pwork);
s32 scrGetIntPara(s32 n);
f32 scrGetFloatPara(s32 n);
char *scrGetStrPara(s32 n);
dds3ProcessID_t *scrGetdds3ProcessIDPara(s32 n);
sdfVector4_t scrGetVector4Para(s32 n);
void scrSetIntReturnValue(s32 i);
void scrSetFloatReturnValue(f32 f);
void scrSetdds3ProcessIDReturnValue(dds3ProcessID_t *id);
void SetFloatReturnValue(const sdfVector4_t *v);
s32 scrGetLabelCodeAddress(s32 labelindex);
void scrSetCodePointer(s32 cp);
s32 scrGetCommandTimer(void);
s32 scrGetMessageHandle(void);
scrHandle_t *scrGetScriptHandle(void);
void *scrGetData(void);
