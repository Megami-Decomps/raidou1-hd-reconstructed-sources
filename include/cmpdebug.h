#pragma once
#include "types.h"
#include "ITM.h"

typedef enum {
    ChangeParType_NOW = 0,
    ChangeParType_BACK = 1,
    ChangeParType_ITM = 2,
    ChangeParType_ERR = 3,
    ChangeParType_DVL_F = 4,
    ChangeParType_BTL = 5,
    ChangeParType_HUUMA = 6,
    ChangeParType_PARAM = 7,
    ChangeParType_MAX = 8,
} ChangeParType;

typedef enum {
    ItemAllType_ALL_ITEM = 0,
    ItemAllType_ALL_NOMAL = 1,
    ItemAllType_ALL_KANKIN = 2,
    ItemAllType_ALL_KICHOU = 3,
    ItemAllType_ALL_SWORD = 4,
    ItemAllType_ALL_MATERI = 5,
    ItemAllType_ALL_SKL = 6,
    ItemAllType_ALL_EXP = 7,
    ItemAllType_MAX = 8,
} ItemAllType;

typedef enum {
    DEBUG_FLG_NONE = 0,
    DEBUG_FLG_LOG = 1,
} DEBUG_FLG;

typedef enum {
    DEBUG_MODE_MAIN = 0,
    DEBUG_MODE_STOCK = 1,
    DEBUG_MODE_PARAM = 2,
    DEBUG_MODE_ITEM = 3,
    DEBUG_MODE_SKILL = 4,
    DEBUG_MODE_OMOIDE = 5,
    DEBUG_MODE_MONEY = 6,
    DEBUG_MODE_RECOOVER = 7,
    DEBUG_MODE_MOON = 8,
    DEBUG_MODE_STOCK_MAX = 9,
    DEBUG_MODE_LOG = 10,
    DEBUG_MODE_DEVIL_REPORT = 11,
    DEBUG_MODE_AWARD_COUNT = 12,
    DEBUG_MODE_NAME_CHG = 13,
} DEBUG_MODE;

typedef struct DEBUG_CSRWORK DEBUG_CSRWORK;
typedef struct cmpDebugDate cmpDebugDate;

struct DEBUG_CSRWORK {
    s32 point;
    s32 offset;
    s32 maxp;
};

struct cmpDebugDate {
    DEBUG_MODE mode;
    s32 step;
    s32 par[3];
    DEBUG_CSRWORK *cmpCurWk[3];
    bool charMenuInitFlag;
    ChangeParType parType;
    ItemAllType ItemAllType;
    void *drawIdList;
};

extern char *debugMainMenu;
extern char *debugMenuOnOff;
extern char *CMP_DEBUG_ASSETNAME;
extern char *CMP_DEBUG_PROCESS_NAME;
extern DEBUG_FLG flag;
extern cmpDebugDate *debugData;
extern s32 *testAddDevil;
extern ITM *noUseItemList;
