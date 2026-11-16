#include "types.h"
#include "shpdattable.h"

typedef struct shpItemTable_t shpItemTable_t;

struct shpItemTable_t {
    s32 Flag;
    s32 ItemNo;
};

s32 arrKnyGoodRank[10];
s32 *arrNwdGoodRank;
s32 *arrKnyPriceRatioBuy;
s32 *arrKnyPriceRatioSell;
f32 *arrNwdMagRatioTrade;
s32 **arrKnyArrivalFlag;
s32 **arrNwdArrivalFlag;
s32 **arrKnyArrivalRank;
s32 **arrNwdArrivalRank;
