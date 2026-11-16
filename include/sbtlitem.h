#pragma once
#include "types.h"

typedef struct SBTLITEM_LISTWORK SBTLITEM_LISTWORK;
typedef struct SBTLITEM_TBL SBTLITEM_TBL;

extern SBTLITEM_TBL *tbldata[768];

SBTLITEM_TBL *sBtlGetItemtbl(s32 id);
bool sBtlSetDropItem(s32 itemid, s32 num, s16 per, s32 luck);
SBTLITEM_LISTWORK *sBtlCreateItemList(void);
bool sBtlEntryItemList(SBTLITEM_LISTWORK *lwk);
bool sBtlEntryKatanaList(SBTLITEM_LISTWORK *lwk);
bool sBtlEntryItemList_Type(SBTLITEM_LISTWORK *lwk, u16 type);
bool sBtlReleaseItemList(SBTLITEM_LISTWORK *lwk);
bool sBtlDeleteItemList(SBTLITEM_LISTWORK *lwk);
