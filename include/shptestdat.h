#pragma once
#include "types.h"

typedef struct tagSHPTDAT_ITEM_WK tagSHPTDAT_ITEM_WK;
typedef struct tagSHPTDAT_PLYITEM_WK tagSHPTDAT_PLYITEM_WK;
typedef struct tagSHPTDAT_SHPITEM_WK tagSHPTDAT_SHPITEM_WK;
typedef struct tagSHPTDAT_WK tagSHPTDAT_WK;
typedef struct tagSHP_GUEST_WK tagSHP_GUEST_WK;
typedef struct tagSHP_MASTER_WK tagSHP_MASTER_WK;

struct tagSHP_MASTER_WK {
    s16 intimacyRank;
    s16 intimacyPoint;
    s16 reserveItemNo;
    u16 bitTalkExtra;
    u32 bitTalkEnd;
};

struct tagSHPTDAT_ITEM_WK {
    s32 price;
    u32 stat;
};

struct tagSHPTDAT_PLYITEM_WK {
    s8 posse;
};

struct tagSHPTDAT_SHPITEM_WK {
    s8 stock;
    s8 stockType;
    u8 stat;
    s8 pad8;
};

struct tagSHPTDAT_WK {
    tagSHPTDAT_ITEM_WK *item[768];
    tagSHPTDAT_PLYITEM_WK *player[768];
    tagSHPTDAT_SHPITEM_WK *shop[768];
    tagSHP_MASTER_WK *master[2];
    tagSHP_GUEST_WK *guest[5];
    s16 reserveId;
};

extern tagSHPTDAT_WK *wk;

tagSHPTDAT_WK *shpGetWork(void);
s32 MakeIndexList(s32 a_listtype, s32 *a_pList);
void shpSetWorkRandParam(void);
tagSHP_GUEST_WK *GetAddrGuestWork(s32 a_guestId);
void Init(void);
void End(void);
