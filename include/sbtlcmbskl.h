#pragma once
#include "types.h"

typedef enum {
    eCmbSklDraw_Raidou = -2147483648,
    eCmbSklDraw_EnemyHit = 1073741824,
    eCmbSklDraw_EnemyNoHit = 536870912,
    eCmbSklDraw_Nakama0 = 268435456,
    eCmbSklDraw_Nakama1 = 134217728,
    eCmbSklDraw_Nakama0_NoBAD = 67108864,
    eCmbSklDraw_Nakama1_NoBAD = 33554432,
    eCmbSklDraw_RaiHit = -1073741824,
    eCmbSklDraw_Enemy = 1610612736,
    eCmbSklDraw_Nakama = 402653184,
    eCmbSklDraw_Party = -1744830464,
    eCmbSklDraw_CMBALL = -671088640,
    eCmbSklDraw_ALL = -134217728,
    eCmbSklDraw_Nakama2 = 100663296,
    eCmbSklDraw_Party2 = -2046820352,
    eCmbSklDraw_CMBALL2 = -973078528,
} eCmbSklDraw;

void sBtlSetCmbBfrPos(void);
void sBtlSetPosCmbBfrPos(void);
void sBtlSetDrawChar(eCmbSklDraw flg);
