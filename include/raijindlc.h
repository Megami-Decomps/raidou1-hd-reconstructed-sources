#pragma once
#include "types.h"
#include "ITM.h"

bool Exists(char *name);
void DLC_ItemInit(void);
s32 GetPackItemMax(s32 pack_no);
s32 GetPackItemNo(s32 pack_no, s32 index);
s32 GetPackItemCnt(s32 pack_no, s32 index);
s32 GetPackItemPackNo(s32 pack_no, s32 index);
void DelBuyItem(s32 pack_no, ITM item_no, s32 del_val);
bool IsBuyItem(void);
bool IsRmegane(void);
bool DlcItemGetCheck(ITM _item);
bool DlcDevilSelCheck(s32 _devilID);
bool DlcDevilCheck(s32 _devilID);
bool GetDlcDevilKarteF(s32 _devilID);
void SetDlcDvlKarteF(s32 _devilID);
