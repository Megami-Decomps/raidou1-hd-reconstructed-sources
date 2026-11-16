#pragma once
#include "types.h"
#include "SBTLPNL_MENU.h"
#include "SKLID.h"

typedef enum {
    SBTLPANEL_MODE_INIT = 0,
    SBTLPANEL_MODE_PROC = 1,
    SBTLPANEL_MODE_FADEOUT = 2,
    SBTLPANEL_MODE_SUSPEND = 3,
} SBTLPANEL_MODE;

typedef enum {
    DATALOAD = 1,
    DATALOADEND = 2,
} SBTLPANEL_ST;

typedef struct SBTLPANEL_WORK SBTLPANEL_WORK;
typedef struct SBTLPNL_SETDATA SBTLPNL_SETDATA;
typedef struct SBTLPNL_WORK SBTLPNL_WORK;
typedef struct sprHandle_t sprHandle_t;

struct SBTLPNL_SETDATA {
    s8 flg;
    s16 target_p;
    SBTLPNL_MENU select_no;
    s16 meirei_no;
    SKLID skillid;
    s32 itemid;
    s32 targetid;
};

struct SBTLPANEL_WORK {
    sprHandle_t *hPanelSpr;
    sprHandle_t *hPanelSpr2;
    sprHandle_t *hPanelSpr3;
    sprHandle_t *hPanelSpr4;
    sprHandle_t *hPanelSpr5;
    SBTLPANEL_MODE mode;
    SBTLPANEL_ST status;
    s32 alpha;
    s32 acounter;
    s32 ofsx;
    s32 ofsy;
    s32 gstat0;
    s32 gstat1;
    s32 astat0;
    s32 astat1;
    s32 acnt0;
    s32 acnt1;
    SBTLPNL_WORK *mds_waku0;
    SBTLPNL_WORK *mds_waku1;
    SBTLPNL_WORK *mds_light;
    SBTLPNL_WORK *menu0[12];
    SBTLPNL_WORK *menu1[12];
    SBTLPNL_WORK *kettei;
    SBTLPNL_SETDATA *data[2];
};
