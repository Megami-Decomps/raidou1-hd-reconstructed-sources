#pragma once
#include "types.h"

typedef struct ItemTable_t ItemTable_t;
typedef struct RateTable_t RateTable_t;
typedef struct scrCommandTable_t scrCommandTable_t;

struct RateTable_t {
    u8 Cyuusei;
    u8 Rate;
};

struct ItemTable_t {
    s32 ItemID;
    u8 Nums;
    u8 Rate;
};

extern scrCommandTable_t *tbl;
extern void *item_takumi_table;
extern RateTable_t *rate_teisatu_table;
extern ItemTable_t *item_teisatu_table;

s32 mphCommand_BUSTUP_LOAD(void);
s32 mphCommand_BUSTUP_LOAD_WAIT(void);
s32 mphCommand_BUSTUP_ON(void);
s32 mphCommand_BUSTUP_OFF(void);
s32 datCommand_CLEAR_STOCK(void);
s32 datCommand_PLAYER_LUCK_STEP(void);
s32 datCommand_GET_BATTLE_RESULT(void);
s32 nimCommand_NIM_INPUT(void);
s32 nimCommand_NIM_CHECK(void);
s32 datCommand_PLAYER_LUCK_SET(void);
s32 cmpCommand_INIT_LUCKPOINT(void);
s32 cmpCommand_UPDATE_LUCKPOINT(void);
s32 datCommand_CHECK_DEVIL_ID(void);
s32 itfMesMngSelect_NEW_SEL(void);
s32 itfInitRegistMessage(void);
s32 itfRegistMessage(void);
s32 itfDispRegistMessage(void);
s32 nmeScrCmd_GET_DREAM_COMPARE(void);
void scrFldObjOutReset(void);
bool scrIsMoonOut(void);
void scrSetMovieCancel(s32 Mode);
bool scrCheckEnableMovieCancel(void);
s32 scrGetAfterSkipBgmFlag(void);
