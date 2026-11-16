#pragma once
#include "types.h"
#include "BSTF.h"
#include "BackRaiAnim.h"
#include "CMP_MENU_ID.h"
#include "CMP_MODE.h"
#include "CmpTitle.h"
#include "ITM_ICON_TYPE.h"
#include "PanelFocus.h"
#include "RSkillTab.h"
#include "SkillIcon.h"
#include "ecmpKudaCMU.h"
#include "ecmpKudaDecideFilter.h"
#include "ecmpKudaSelectMode.h"

typedef enum {
    CMP_STEP_INIT = 0,
    CMP_STEP_FADEIN = 1,
    CMP_STEP_SELECT = 2,
    CMP_STEP_SELECT_MAP = 3,
    CMP_STEP_SPR_LOAD_WAIT = 4,
    CMP_STEP_CONTENT = 5,
    CMP_STEP_RAIDOU_SKL = 6,
    CMP_STEP_POCKET_BOOK = 7,
    CMP_STEP_SP_ORDER = 8,
    CMP_STEP_DVL_REPORT = 9,
    CMP_STEP_CONFIG = 10,
    CMP_STEP_SELECT_SUSPEND = 11,
    CMP_STEP_END_MES = 12,
    CMP_STEP_SPR_FREE_WAIT = 13,
    CMP_STEP_FADEOUT = 14,
    CMP_STEP_RELEASE = 15,
    CMP_STEP_END_WAIT = 16,
    CMP_STEP_END = 17,
    CMP_STEP_AUTOSAVE = 18,
} CMP_STEP;

typedef enum {
    CMP_STAT_MENU_RELEASE = 1,
    CMP_STAT_MENU_LOAD_BGM_START = 2,
    CMP_STAT_MENU_LOAD_BGM_END = 4,
    CMP_STAT_MENU_DRAW = 8,
    CMP_STAT_MENU_DRAWHELP = 16,
    CMP_STAT_MENU_DRAWBACK = 32,
    CMP_STAT_MENU_LOADJMSSPRMEM = 64,
    CMP_STAT_MENU_LOADJMSSPRHND = 128,
} CMP_STAT_MENU;

typedef enum {
    CMP_SYS_EITHER = 0,
    CMP_SYS_PART_CONF = 1,
    CMP_SYS_SUMMON_CONF = 2,
    CMP_SYS_N_SUMMON_CONF = 3,
    CMP_SYS_THROW_CONF = 4,
    CMP_SYS_N_EQUIP_BLT = 5,
    CMP_SYS_SUSPEND_GAME = 6,
    CMP_SYS_SUSPEND_END = 7,
    CMP_SYS_SUSPEND_ERROR = 8,
    CMP_SYS_CONFIG_CHANGE = 9,
    CMP_SYS_CONFIG_KEY_CHANGE = 10,
    CMP_SYS_CONFIG_SAVE = 11,
    CMP_SYS_CONFIG_ERROR = 12,
    CMP_SYS_CONFIG_TAB = 13,
    CMP_SYS_CONFIG_TAB_K = 14,
    CMP_SYS_CONFIG_DEFAULT = 15,
    CMP_SYS_CONFIG_BACK = 16,
    CMP_SYS_SKLITM_OMO_CHG = 17,
    CMP_SYS_SKLITM_CHK = 18,
    CMP_SYS_SKLITM_CHK_OMO = 19,
    CMP_SYS_SKLITM_UP = 20,
    CMP_SYS_SKLITM_ADD = 21,
    CMP_SYS_SKLITM_TMP = 22,
    CMP_SYS_SKLITM_OFC = 23,
    CMP_SYS_TITLE_CHK = 24,
    CMP_SYS_END_CHK = 25,
    CMP_SYS_QUEST_REWARD_NOT = 26,
    CMP_SYS_QUEST_REWARD_ITEM = 27,
    CMP_SYS_QUEST_REWARD_MONEY = 28,
} CMP_SYS;

typedef struct CmpCsrSave CmpCsrSave;
typedef struct CmpSubMenuPass CmpSubMenuPass;
typedef struct DvlReportStateMachine DvlReportStateMachine;
typedef struct RaidouSKillCsrSave RaidouSKillCsrSave;
typedef struct dds3ProcessID_t dds3ProcessID_t;
typedef struct sdatPlayerUnitWork_t sdatPlayerUnitWork_t;
typedef struct sdatUnitWork_t sdatUnitWork_t;
typedef struct tagCMP_WORK tagCMP_WORK;

struct CmpCsrSave {
    void *csrSave;
    void *savePanel;
};

struct tagCMP_WORK {
    dds3ProcessID_t *drawPID;
    dds3ProcessID_t *menuPID;
    dds3ProcessID_t *charPID;
    dds3ProcessID_t *stockPID;
    dds3ProcessID_t *listPID;
    dds3ProcessID_t *submPID;
    CMP_STEP step;
    CMP_STAT_MENU stat;
    CMP_MODE runmode;
    s8 drawmode;
    CMP_MENU_ID menuID;
    s32 markID;
    s32 count;
    s32 countMotMoya;
    s16 tabpage;
    s16 tabpagemax;
    s16 tabpagestockmax;
    s16 summonpos;
    s8 tabNoDisp;
    s8 helpNoDisp;
    s8 helpDispflg;
    sdatUnitWork_t *psUse;
    ecmpKudaSelectMode eSelMode;
    ecmpKudaDecideFilter eDecFilter;
    ecmpKudaCMU iAttrId;
    ecmpKudaCMU iSelectAttrId;
    ecmpKudaCMU iDecideAttrId;
    BSTF iBadStatus;
    s32 iTabEnableCnt;
    s32 workStat;
    CMP_SYS endMesType;
    sdatPlayerUnitWork_t *playerUnit;
    CmpSubMenuPass *menuPass;
    PanelFocus changeActivePanel;
    PanelFocus stockPanelActive;
    PanelFocus oldActive;
    BackRaiAnim nowBackRaiAnim;
    CmpTitle nowTitle;
    bool tips;
    CmpCsrSave *csrSave;
    DvlReportStateMachine *dvlReportMachine;
    RaidouSKillCsrSave *rSkillCsrSave;
    RSkillTab rSkillTabSave;
    void *skillListSelectSave;
};

struct CmpSubMenuPass {
    s32 menuNum;
    char *str;
    char *tag;
    u32 color;
    CMP_MENU_ID id;
    SkillIcon sklSprNo;
    ITM_ICON_TYPE itmType;
    s32 devilID;
};

struct RaidouSKillCsrSave {
    void *skillCsrSave;
};
