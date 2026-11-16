#pragma once
#include "types.h"
#include "ITM_ICON_TYPE.h"
#include "SKLID.h"

typedef enum {
    SORT_SUB_NONE = 999,
    SORT_SUB_RECV = 1,
    SORT_SUB_UP = 2,
    SORT_SUB_EXP = 3,
    SORT_SUB_SAKE = 4,
    SORT_SUB_SP = 5,
    SORT_SUB_BOOK = 6,
    SORT_SUB_SWORD = 7,
    SORT_SUB_MONEY = 8,
} SORT_SUB;

typedef enum {
    SORT_KON_NONE = 999,
    SORT_KON_MONEY = 1,
    SORT_KON_RECV = 2,
    SORT_KON_UP = 3,
    SORT_KON_EXP = 4,
    SORT_KON_SAKE = 5,
    SORT_KON_SP = 6,
    SORT_KON_BOOK = 7,
    SORT_KON_SWORD = 8,
} SORT_KON;

typedef enum {
    SORT_MASYOU_NONE = 999,
    SORT_MASYOU_GUREN = 1,
    SORT_MASYOU_GINHYO = 2,
    SORT_MASYOU_RAIDEN = 3,
    SORT_MASYOU_SHIPPU = 4,
    SORT_MASYOU_BANRIKI = 5,
    SORT_MASYOU_GEHO = 6,
    SORT_MASYOU_GIGEI = 7,
    SORT_MASYOU_OTHER = 8,
} SORT_MASYOU;

typedef struct SBTLITEM_TBL SBTLITEM_TBL;

struct SBTLITEM_TBL {
    u32 usetype;
    u32 flg;
    u16 side;
    u16 type;
    SKLID sklid;
    s32 gold;
    s32 max_num;
    ITM_ICON_TYPE iconType;
    s32 sortid;
    SORT_SUB sortSub;
    SORT_KON sortKon;
    SORT_MASYOU sortMasyou;
};
