#pragma once
#include "types.h"

typedef enum {
    MOVE_FRAME = 15,
} NWDNEWS;

void nwdLoadSprite(void);
void nwdCallNext(void);
void nwdProcessStart(void);
void nwdProcessEnd(void);
bool nwdProcessCheck(void);
