#pragma once
#include "types.h"

typedef struct RewardItem_t RewardItem_t;
typedef struct ZakuroReward_t ZakuroReward_t;

struct RewardItem_t {
    s32 _ItemID;
    s32 _Count;
};

struct ZakuroReward_t {
    s32 _lap;
    s32 _exorcism;
    RewardItem_t *RewardItem[4];
};
