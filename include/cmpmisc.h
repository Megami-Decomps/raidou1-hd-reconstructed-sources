#pragma once
#include "types.h"
#include "BST.h"
#include "BSTF.h"
#include "itf.h"

typedef struct Menu_t Menu_t;
typedef struct dds3ProcessID_t dds3ProcessID_t;
typedef struct sprHandle_t sprHandle_t;

bool cmpChkDevilStockExist(s32 a_stockID);
bool cmpDelDevilStock(s32 a_stockID);
s32 cmpGetDevilStockDevilID(s32 a_stockID);
BST cmpGetBstNo(BSTF a_bst);
void cmpUpdateBulletNum(void);
void cmpPartyDrawFunc(s32 a_id, s32 a_x, s32 a_y, s32 a_z, u32 a_fontColor, u8 a_alphaRate);
void cmpStockDrawFunc(s32 a_id, s32 a_x, s32 a_y, s32 a_z, u32 a_fontColor, u8 a_alphaRate);
s32 cmpCharMoveFunc(Menu_t *wk, MENU_KEY_TYPE _key, bool _loop);
dds3ProcessID_t *cmpPartyListProcessStart(void);
s32 cmpStockMoveFunc(Menu_t *wk, MENU_KEY_TYPE _key, bool _loop);
dds3ProcessID_t *cmpStockListProcessStart(void);
s32 cmpPartyAnimFunc(s32 mode);
s32 cmpStockAnimFunc(s32 mode);
void cmpPartyListMake(dds3ProcessID_t *PID);
void cmpStockListMake(dds3ProcessID_t *PID, bool _sort);
void cmpStockListRecreate(bool _sort);
void cmpPartyListSetImage(dds3ProcessID_t *PID, sprHandle_t *a_phSpr);
