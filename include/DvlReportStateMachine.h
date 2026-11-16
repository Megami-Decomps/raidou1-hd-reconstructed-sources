#pragma once
#include "types.h"

typedef enum {
    FadeInStep_FadeOut = 0,
    FadeInStep_StartStatus = 1,
    FadeInStep_FadeOutWait = 2,
} FadeInStep;

typedef enum {
    ScriptStep_FadeIn = 0,
    ScriptStep_Start = 1,
    ScriptStep_Update = 2,
    ScriptStep_End = 3,
} ScriptStep;

typedef struct DvlReportEndShortState DvlReportEndShortState;
typedef struct DvlReportEndState DvlReportEndState;
typedef struct DvlReportFadeInState DvlReportFadeInState;
typedef struct DvlReportFadeOutState DvlReportFadeOutState;
typedef struct DvlReportInitState DvlReportInitState;
typedef struct DvlReportScriptState DvlReportScriptState;
typedef struct DvlReportShortInitState DvlReportShortInitState;
typedef struct DvlReportShortScriptState DvlReportShortScriptState;
typedef struct DvlReportStateMachine DvlReportStateMachine;
typedef struct StockDevil StockDevil;
typedef struct sdatUnitWork_t sdatUnitWork_t;
typedef struct tagCMP_WORK tagCMP_WORK;

struct DvlReportEndState {
    tagCMP_WORK *wk;
    DvlReportStateMachine *machine;
    s32 count;
};

struct DvlReportFadeInState {
    tagCMP_WORK *wk;
    DvlReportStateMachine *machine;
    s32 count;
    FadeInStep step;
};

struct DvlReportFadeOutState {
    tagCMP_WORK *wk;
    DvlReportStateMachine *machine;
    s32 count;
};

struct DvlReportInitState {
    tagCMP_WORK *wk;
    DvlReportStateMachine *machine;
    s32 count;
};

struct DvlReportScriptState {
    tagCMP_WORK *wk;
    DvlReportStateMachine *machine;
    bool scriptEnd;
    ScriptStep step;
};

struct DvlReportEndShortState {
    tagCMP_WORK *wk;
    DvlReportStateMachine *machine;
    s32 count;
};

struct DvlReportShortInitState {
    tagCMP_WORK *wk;
    DvlReportStateMachine *machine;
    s32 count;
};

struct DvlReportShortScriptState {
    s32 step;
    tagCMP_WORK *wk;
    DvlReportStateMachine *machine;
    s32 count;
};

struct DvlReportStateMachine {
    void *_CurrentState_k__BackingField;
    void *StateChanged;
    bool end;
    s32 _OldState_k__BackingField;
    s32 _NowState_k__BackingField;
    DvlReportInitState *init;
    DvlReportFadeInState *fadeIn;
    DvlReportScriptState *script;
    DvlReportFadeOutState *fadeOut;
    DvlReportEndState *endState;
    DvlReportShortInitState *shortInit;
    DvlReportShortScriptState *shortScript;
    DvlReportEndShortState *shortEndState;
    void *reprtDvlList;
    sdatUnitWork_t *calcReportDvl;
    StockDevil *summonDevil;
};

struct StockDevil {
    s32 devilId;
    u32 uniqCode;
};
