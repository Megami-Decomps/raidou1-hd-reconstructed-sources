#pragma once
#include "types.h"

typedef enum {
    FLOORMODEL_OFF = 1,
    ANIM_ALL_STOP = 2,
} TNEFFECT_FLAG;

extern TNEFFECT_FLAG Flag;
extern void *texture;

void tnInit(void);
void tnFlagSet(TNEFFECT_FLAG flag);
void tnFlagClear(TNEFFECT_FLAG flag);
void tnFlagAllClear(void);
