#pragma once
#include "types.h"

typedef struct LightPacketClass LightPacketClass;
typedef struct jmsModelTable_t jmsModelTable_t;
typedef struct sdfIVector2_t sdfIVector2_t;

struct jmsModelTable_t {
    s32 Minor;
    s32 DefMotion;
    f32 Angle;
    f32 Pos[3];
    sdfIVector2_t CursorPos;
    void *Flag[13];
    LightPacketClass *lunchLight;
    LightPacketClass *eveningLight;
    LightPacketClass *nightLight;
};

struct LightPacketClass {
    sdfVector4_t Col[3];
    sdfVector4_t Dir[3];
    sdfVector4_t Ambient;
};

extern jmsModelTable_t *jmsModelTable[6];
